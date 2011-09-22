/* PL/SQL Developer Lua Plug-In */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

#define LUA_LIB

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "luaplsql.h"


#define PLUGIN_DESCR	"Lua Plug-In"

/* Pl/Sql Developer Window Handle */
static HWND g_WindowHandle;

#define ShowMessage(msg)	MessageBox(g_WindowHandle, msg, PLUGIN_DESCR, 0)


/* Global Lua Plug-In Identifier */
static int g_PlugInId;

/* Pl/Sql Developer Functions */
#define NFUNCTIONS	256

static PLSQL_Function plsqldev_func[NFUNCTIONS];


/* Global Lua State */
static lua_State *g_L;

/* Number of nested function calls */
static int g_LNCalls;

/* References to registry */
static struct {
	int traceback;  /* traceback function */
	int addons;  /* addons table */
	int template;  /* template data */
	int timers;  /* timers table */
} g_Ref;

#define PLUGIN_TRACEBACK_IDX	1
#define PLUGIN_ADDONS_IDX	2


/* Addon functions */
static unsigned int g_Funcs;

/* Popup menu items */
static unsigned int g_PopupMenus;

#define MAX_ADDONS		1000
#define MAX_MENUS		98

/* Default menus */
#define PLUGIN_MENU_RELOAD	99

enum {
	Func_Start = 0,

	Func_OnActivate,
	Func_OnDeactivate,
	Func_CanClose,
	Func_AfterStart,
	Func_AfterReload,
	Func_OnBrowserChange,
	Func_OnWindowChange,
	Func_OnWindowCreate,
	Func_OnWindowCreated,
	Func_OnWindowClose,
	Func_BeforeExecuteWindow,
	Func_AfterExecuteWindow,
	Func_OnConnectionChange,
	Func_OnPopup,
	Func_OnMainMenu,
	Func_OnTemplate,
	Func_OnFileLoaded,
	Func_OnFileSaved,
	Func_About,
	Func_CommandLine,
	Func_RegisterExport,
	Func_ExportInit,
	Func_ExportFinished,
	Func_ExportPrepare,
	Func_ExportData,

	Func_End
};

#define callback_exist(func)		((g_Funcs & (1 << func)) != 0)

/* Default behaviour on window close */
static int g_WindowCloseAction = WINCLOSE_DEFAULT;


static int push_traceback_addons (int nargs);


#include "plsql_ide.c"
#include "plsql_sql.c"
#include "plsql_sys.c"
#include "plsql.c"


static int
traceback (lua_State *L)
{
	lua_getfield(L, LUA_GLOBALSINDEX, "debug");
	if (!lua_istable(L, -1)) {
		lua_pop(L, 1);
		return 1;
	}
	lua_getfield(L, -1, "traceback");
	if (!lua_isfunction(L, -1)) {
		lua_pop(L, 2);
		return 1;
	}
	lua_pushvalue(L, 1);  /* pass error message */
	lua_pushinteger(L, 2);  /* skip this function and traceback */
	lua_call(L, 2, 1);  /* call debug.traceback */
	return 1;
}

static int
load_addons (void)
{
	int i;

	// load main lua file
	{
		char path[2 * MAX_PATH];

		GetEnvironmentVariable(PLUGIN_ENV, path, sizeof(path));
		strcat(path, "\\main.lua");
		if (luaL_loadfile(g_L, path))
			return 0;
	}

	lua_pushinteger(g_L, MAX_ADDONS);
	lua_pushinteger(g_L, MAX_MENUS);
	if (lua_pcall(g_L, 2, 1, PLUGIN_TRACEBACK_IDX))
		return 0;

	if (!lua_istable(g_L, PLUGIN_ADDONS_IDX)) {
		lua_pushliteral(g_L, "Functions table expected");
		return 0;
	}

	/* set available functions */
	for (i = Func_Start + 1; i < Func_End; ++i) {
		lua_rawgeti(g_L, PLUGIN_ADDONS_IDX, i * MAX_ADDONS);
		if (lua_isfunction(g_L, -1))
			g_Funcs |= 1 << i;
		lua_pop(g_L, 1);
	}
	return 1;
}

static int
push_traceback_addons (int nargs)
{
	const int top = lua_gettop(g_L);

	lua_rawgeti(g_L, LUA_REGISTRYINDEX, g_Ref.traceback);
	lua_rawgeti(g_L, LUA_REGISTRYINDEX, g_Ref.addons);
	if (nargs) {
		lua_insert(g_L, top + 1);
		lua_insert(g_L, top + 1);
	}
	return top;
}

static int
call_addons (int cb, int nargs, int oneshot,
	void (*arg_func)(void *), void *data)
{
	int top = 0;
	int i, res;

	if (g_LNCalls++)
		top = push_traceback_addons(nargs);

	res = 0;
	for (i = cb * MAX_ADDONS; ; ++i) {
		int j;

		/* function */
		lua_rawgeti(g_L, top + PLUGIN_ADDONS_IDX, i);
		if (lua_isnil(g_L, -1))
			break;
		/* arguments */
		for (j = 1; j <= nargs; ++j) {
			lua_pushvalue(g_L, top + PLUGIN_ADDONS_IDX + j);
		}
		if (lua_pcall(g_L, nargs, 1, top + PLUGIN_TRACEBACK_IDX)) {
			ShowMessage(lua_tostring(g_L, -1));
		} else {
			const int is_nil = lua_isnil(g_L, -1);

			if (arg_func)
				arg_func(data);  /* arguments handler */
			res |= is_nil ? 1
				: lua_isboolean(g_L, -1) ? lua_toboolean(g_L, -1)
				: lua_tointeger(g_L, -1);
			if (oneshot && !is_nil)
				break;
		}
		lua_pop(g_L, 1);
	}
	lua_settop(g_L, --g_LNCalls ? top : PLUGIN_ADDONS_IDX);
	return res;
}


PLUGIN_API char *
PlugInShortName (void)
{
	return "lua";
}

PLUGIN_API char *
IdentifyPlugIn (int id)
{
	g_PlugInId = id;
	return PLUGIN_DESCR;
}

/*
 * Startup sequence: IdentifyPlugIn, OnCreate, RegisterCallback, CreateMenuItem, OnActivate, ...
 * Therefore, here Pl/Sql functions are not available.
 */
PLUGIN_API void
OnCreate (void)
{
	if (!g_WindowHandle) {
		IDE_GetWindowHandle func = (IDE_GetWindowHandle) plsqldev_func[16];

		g_WindowHandle = func ? func() : NULL;
	}

	if (g_L || !(g_L = lua_open()))
		return;

	/* open libraries */
	luaL_openlibs(g_L);

	luaL_register(g_L, "plsql", plsqllib);
	luaL_register(g_L, "plsql.sys", plsql_syslib);
	luaL_register(g_L, "plsql.ide", plsql_idelib);
	luaL_register(g_L, "plsql.sql", plsql_sqllib);

	lua_settop(g_L, 0);
	lua_pushcfunction(g_L, traceback);

	if (!load_addons()) {
		ShowMessage(lua_tostring(g_L, -1));
		lua_close(g_L);
		g_L = NULL;
		return;
	}

	/* addons table */
	lua_pushvalue(g_L, -1);
	g_Ref.addons = luaL_ref(g_L, LUA_REGISTRYINDEX);

	/* traceback function */
	lua_pushvalue(g_L, -2);
	g_Ref.traceback = luaL_ref(g_L, LUA_REGISTRYINDEX);

	/* template data */
	lua_pushnil(g_L);
	g_Ref.template = luaL_ref(g_L, LUA_REGISTRYINDEX);

	/* timers table */
	lua_newtable(g_L);
	g_Ref.timers = luaL_ref(g_L, LUA_REGISTRYINDEX);

	g_LNCalls = 0;
}

PLUGIN_API void
OnDestroy (void)
{
	if (g_L) {
		lua_close(g_L);
		g_L = NULL;
		g_Funcs = 0;
	}
}

PLUGIN_API void
RegisterCallback (int i, PLSQL_Function func)
{
	if (i < NFUNCTIONS)
		plsqldev_func[i] = func;
}

PLUGIN_API void
OnActivate (void)
{
	const int cb = Func_OnActivate;

	OnCreate();

	if (callback_exist(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnDeactivate (void)
{
	const int cb = Func_OnDeactivate;

	if (callback_exist(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}

	OnDestroy();
}

PLUGIN_API const char *
CreateMenuItem (int i)
{
	const char *s = NULL;

	/* Plugin menus */
	if (i == PLUGIN_MENU_RELOAD)
		return "&Lua / Re&load Plug-In";

	/* Addon menus */
	if (g_L) {
		int top = 0;

		if (g_LNCalls++)
			top = push_traceback_addons(0);

		lua_rawgeti(g_L, PLUGIN_ADDONS_IDX, -i);
		s = lua_tostring(g_L, -1);
		lua_settop(g_L, --g_LNCalls ? top : PLUGIN_ADDONS_IDX);
	}
	return s;
}

static void
Reload (void)
{
	const int cb = Func_AfterReload;

	OnDeactivate();
	OnCreate();

	plsql_ide_RefreshMenus(NULL);

	OnActivate();
	RegisterExport();

	if (callback_exist(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnMenuClick (int i)
{
	if (!g_L) return;

	/* Plugin menus */
	if (i == PLUGIN_MENU_RELOAD) {
		Reload();
		return;
	}

	/* Addon menus */
	{
		int top = 0;

		if (g_LNCalls++ != 0)
			top = push_traceback_addons(0);

		lua_rawgeti(g_L, top + PLUGIN_ADDONS_IDX, -(i + MAX_MENUS));
		if (lua_isfunction(g_L, -1)) {
			lua_pushinteger(g_L, i);
			if (lua_pcall(g_L, 1, 0, top + PLUGIN_TRACEBACK_IDX))
				ShowMessage(lua_tostring(g_L, -1));
		}
		lua_settop(g_L, --g_LNCalls ? top : PLUGIN_ADDONS_IDX);
	}
}

/* If any Addon returns true then IDE cannot be closed */
PLUGIN_API BOOL
CanClose (void)
{
	const int cb = Func_CanClose;

	return callback_exist(cb)
		? call_addons(cb, 0, 1, NULL, NULL) : TRUE;
}

PLUGIN_API void
AfterStart (void)
{
	const int cb = Func_AfterStart;

	if (callback_exist(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnBrowserChange (void)
{
	const int cb = Func_OnBrowserChange;

	if (callback_exist(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnWindowChange (void)
{
	const int cb = Func_OnWindowChange;

	if (callback_exist(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnWindowCreate (int win_type)
{
	const int cb = Func_OnWindowCreate;

	if (callback_exist(cb)) {
		lua_pushinteger(g_L, win_type);
		call_addons(cb, 1, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnWindowCreated (int win_type)
{
	const int cb = Func_OnWindowCreated;

	if (callback_exist(cb)) {
		lua_pushinteger(g_L, win_type);
		call_addons(cb, 1, 0, NULL, NULL);
	}
}

/* Addon results priority: confirm user, quietly close, default behaviour */
PLUGIN_API int
OnWindowClose (int win_type, BOOL changed)
{
	const int cb = Func_OnWindowClose;
	int res;

	if (g_WindowCloseAction != WINCLOSE_DEFAULT
		|| !callback_exist(cb))
		return g_WindowCloseAction;

	lua_pushinteger(g_L, win_type);
	lua_pushboolean(g_L, changed);
	res = call_addons(cb, 2, 0, NULL, NULL);
	return (res & WINCLOSE_CONFIRM) ? WINCLOSE_CONFIRM : res & WINCLOSE_QUIET;
}

PLUGIN_API BOOL
BeforeExecuteWindow (int win_type)
{
	const int cb = Func_BeforeExecuteWindow;

	if (callback_exist(cb)) {
		lua_pushinteger(g_L, win_type);
		return call_addons(cb, 1, 1, NULL, NULL);
	}
	return TRUE;
}

PLUGIN_API void
AfterExecuteWindow (int win_type, int result)
{
	const int cb = Func_AfterExecuteWindow;

	if (callback_exist(cb)) {
		lua_pushinteger(g_L, win_type);
		lua_pushinteger(g_L, result);
		call_addons(cb, 2, 1, NULL, NULL);
	}
}

PLUGIN_API void
OnConnectionChange (void)
{
	const int cb = Func_OnConnectionChange;

	if (callback_exist(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnPopup (char *obj_type, char *obj_name)
{
	const int cb = Func_OnPopup;

	if (callback_exist(cb)) {
		lua_pushstring(g_L, obj_type);
		lua_pushstring(g_L, obj_name);
		call_addons(cb, 2, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnMainMenu (char *menu_name)
{
	const int cb = Func_OnMainMenu;

	if (callback_exist(cb)) {
		lua_pushstring(g_L, menu_name);
		call_addons(cb, 1, 1, NULL, NULL);
	}
}

static void
OnTemplateArgs (const char **data)
{
	if (lua_isstring(g_L, -1)) {
		*data = lua_tostring(g_L, -1);

		/* prevent string to be collected by GC */
		lua_pushvalue(g_L, -1);
		lua_rawseti(g_L, LUA_REGISTRYINDEX, g_Ref.template);

		/* replace 2-nd argument with the result string */
		lua_remove(g_L, -2);
		lua_pushboolean(g_L, 1);
	}
}

PLUGIN_API BOOL
OnTemplate (char *filename, const char **data)
{
	const int cb = Func_OnTemplate;

	if (callback_exist(cb)) {
		lua_pushstring(g_L, filename);
		lua_pushstring(g_L, *data);
		return call_addons(cb, 2, 1, OnTemplateArgs, (void *) data);
	}
	return TRUE;
}

PLUGIN_API void
OnFileLoaded (int win_type, int mode)
{
	const int cb = Func_OnFileLoaded;

	if (callback_exist(cb)) {
		lua_pushinteger(g_L, win_type);
		lua_pushinteger(g_L, mode);
		call_addons(cb, 2, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnFileSaved (int win_type, int mode)
{
	const int cb = Func_OnFileSaved;

	if (callback_exist(cb)) {
		lua_pushinteger(g_L, win_type);
		lua_pushinteger(g_L, mode);
		call_addons(cb, 2, 0, NULL, NULL);
	}
}

PLUGIN_API const char *
About (void)
{
	const int cb = Func_About;
	const char *s;
	int top = 0;
	int i;

	if (!callback_exist(cb))
		return "Lua Addons not loaded";

	if (g_LNCalls++ != 0)
		top = push_traceback_addons(0);

	lua_pushliteral(g_L, "Lua Addons:");
	for (i = cb * MAX_ADDONS; ; ++i) {
		lua_pushliteral(g_L, "\n- ");
		/* function */
		lua_rawgeti(g_L, top + PLUGIN_ADDONS_IDX, i);
		if (lua_isnil(g_L, -1)) {
			lua_pop(g_L, 2);
			break;
		}
		lua_pcall(g_L, 0, 1, top + PLUGIN_TRACEBACK_IDX);
		if (lua_isstring(g_L, -1))
			lua_concat(g_L, 3);
		else
			lua_pop(g_L, 2);
	}
	s = lua_tostring(g_L, -1);
	lua_settop(g_L, --g_LNCalls ? top : PLUGIN_ADDONS_IDX);
	return s;
}

PLUGIN_API void
CommandLine (int handle, char *command, char *params)
{
	const int cb = Func_CommandLine;

	if (callback_exist(cb)) {
		lua_pushinteger(g_L, handle);
		lua_pushstring(g_L, command);
		lua_pushstring(g_L, params);
		call_addons(cb, 3, 1, NULL, NULL);
	}
}

PLUGIN_API const char *
RegisterExport (void)
{
	const int cb = Func_RegisterExport;

	if (callback_exist(cb)) {
		call_addons(cb, 0, 1, NULL, NULL);
	}
	return "Via Lua";
}

PLUGIN_API BOOL
ExportInit (void)
{
	const int cb = Func_ExportInit;

	return callback_exist(cb)
		? call_addons(cb, 0, 1, NULL, NULL) : TRUE;
}

PLUGIN_API void
ExportFinished (void)
{
	const int cb = Func_ExportFinished;

	if (callback_exist(cb)) {
		call_addons(cb, 0, 1, NULL, NULL);
	}
}

PLUGIN_API BOOL
ExportPrepare (void)
{
	const int cb = Func_ExportPrepare;

	return callback_exist(cb)
		? call_addons(cb, 0, 1, NULL, NULL) : TRUE;
}

PLUGIN_API BOOL
ExportData (char *value)
{
	const int cb = Func_ExportData;

	if (callback_exist(cb)) {
		lua_pushstring(g_L, value);
		return call_addons(cb, 1, 1, NULL, NULL);
	}
	return FALSE;
}

