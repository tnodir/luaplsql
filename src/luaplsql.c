/* PL/SQL Developer Lua Plug-In */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

#define LUA_LIB

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "luaplsql.h"
#include "version.h"


#if LUA_VERSION_NUM < 502
#define lua_rawlen		lua_objlen
#define lua_resume(L,from,n)	lua_resume((L), (n))
#define luaL_setfuncs(L,l,n)	luaL_register((L), NULL, (l))

#ifndef luaL_newlib
#define luaL_newlibtable(L,l) \
    lua_createtable(L, 0, sizeof(l) / sizeof((l)[0]) - 1)
#define luaL_newlib(L,l) \
    (luaL_newlibtable((L), (l)), luaL_setfuncs((L), (l), 0))
#endif

#define lua_rawgetp(L,idx,p) \
    (lua_pushlightuserdata((L), (p)), \
     lua_rawget((L), (idx) - ((idx) < 0 && (idx) > -99 ? 1 : 0)))
#define lua_rawsetp(L,idx,p) \
    (lua_pushlightuserdata((L), (p)), lua_insert((L), -2), \
     lua_rawset((L), (idx) - ((idx) < 0 && (idx) > -99 ? 1 : 0)))

#define luai_writestringerror(s,p) \
    (fprintf(stderr, (s), (p)), fflush(stderr))

#define lua_absindex(L,idx) \
    ((idx) < 0 && (idx) > -99 ? lua_gettop(L) + (idx) + 1 : (idx))

#else
#define luaL_register(L,n,l)	luaL_newlib((L), (l))
#define lua_setfenv		lua_setuservalue
#define lua_getfenv		lua_getuservalue
#endif


#define MAX_FUNCTIONS	256  /* Pl/Sql Developer Functions */
#define MAX_ADDONS	1000
#define MAX_MENUS	96

/* Default menus */
#define PLUGIN_MENU_TAB		97
#define PLUGIN_MENU_GROUP	98
#define PLUGIN_MENU_RELOAD	99

#define ShowMessage(msg)	MessageBox(GetWindowHandle(), msg, APP_NAME, 0)

/* Addon callback functions */
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
	Func_OnWindowConnectionChange,
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

	Func_CreateMenuItem,
	Func_OnMenuClick,

	Func_End
};

/* Global Lua Plug-In */
static struct {
	unsigned int is_active		: 1;  /* Is PlugIn activated? */
	unsigned int win_close_action	: 3;  /* Default behaviour on window close */
	unsigned int use_ribbon_menu	: 1;  /* Use Ribbon Menu with Pl/Sql Developer v12+ */

	int id;  /* Plug-In Identifier */

	unsigned int cb_bits;  /* Addon callback functions bits */

	/* References to registry */
	int ref_traceback;  /* traceback function */
	int ref_addons;  /* addons table */
	int ref_template;  /* template string */
	int ref_about;  /* about string */
	int ref_timers;  /* timers table */

	int ncalls;  /* Number of nested function calls */
	lua_State *L;

	char menus[1 + MAX_MENUS];  /* Menu/Ribbon indexes mapping */
	PLSQL_Function funcs[MAX_FUNCTIONS];
} g_PlugIn;

#define g_IsActive		g_PlugIn.is_active
#define g_WindowCloseAction	g_PlugIn.win_close_action
#define g_UseRibbonMenu		g_PlugIn.use_ribbon_menu

#define g_PlugInId		g_PlugIn.id

#define g_LNCalls		g_PlugIn.ncalls
#define g_L			g_PlugIn.L

#define PLSQL_MENU		g_PlugIn.menus
#define PLSQL_FUNC		g_PlugIn.funcs

#define g_NMenus		PLSQL_MENU[0]

#define callback_exists(cb)	((g_PlugIn.cb_bits & (1 << cb)) != 0)

#define PLUGIN_TRACEBACK_IDX	1
#define PLUGIN_ADDONS_IDX	2
#define PLUGIN_MENUS_IDX	3


static int push_traceback_addons (int nargs);


#include "debug.c"
#include "plsql_ide.c"
#include "plsql_sql.c"
#include "plsql_sys.c"
#include "plsql.c"


static int
traceback (lua_State *L)
{
#if LUA_VERSION_NUM < 502
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
#else
	const char *msg = lua_tostring(L, 1);
	if (msg)
		luaL_traceback(L, L, msg, 1);
	else if (!lua_isnoneornil(L, 1)) {  /* is there an error object? */
		if (!luaL_callmeta(L, 1, "__tostring"))	 /* try its 'tostring' metamethod */
			lua_pushliteral(L, "(no error message)");
	}
	return 1;
#endif
}

static int
load_addons (void)
{
	int i;

	/* load main lua file */
	{
		char path[2 * MAX_PATH];
		const int n = GetEnvironmentVariable(PLUGIN_ENV_ROOT, path, sizeof(path));

		strcat(path + n, "\\main.lua");
		if (luaL_loadfile(g_L, path))
			return 0;
	}

	lua_pushinteger(g_L, MAX_ADDONS);
	lua_pushinteger(g_L, MAX_MENUS);
	if (lua_pcall(g_L, 2, 2, PLUGIN_TRACEBACK_IDX))
		return 0;

	if (!lua_istable(g_L, PLUGIN_ADDONS_IDX)) {
		lua_pushliteral(g_L, "Functions table expected");
		return 0;
	}

	if (!lua_istable(g_L, PLUGIN_MENUS_IDX)) {
		lua_pushliteral(g_L, "Menu indexes table expected");
		return 0;
	}

	/* set available functions */
	for (i = Func_Start + 1; i < Func_End; ++i) {
		lua_rawgeti(g_L, PLUGIN_ADDONS_IDX, i * MAX_ADDONS);
		if (lua_isfunction(g_L, -1)) {
			g_PlugIn.cb_bits |= (1 << i);
		}
		lua_pop(g_L, 1);
	}

	/* set menu/ribbon indexes */
	for (i = 0; i <= MAX_MENUS; ++i) {
		lua_rawgeti(g_L, PLUGIN_MENUS_IDX, i);
		PLSQL_MENU[i] = (char) lua_tointeger(g_L, -1);
		lua_pop(g_L, 1);
	}
	lua_pop(g_L, 1);

	return 1;
}

static int
push_traceback_addons (int nargs)
{
	const int top = lua_gettop(g_L);

	lua_rawgeti(g_L, LUA_REGISTRYINDEX, g_PlugIn.ref_traceback);
	lua_rawgeti(g_L, LUA_REGISTRYINDEX, g_PlugIn.ref_addons);
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
			res |= is_nil ? 1 : (lua_isboolean(g_L, -1)
				? lua_toboolean(g_L, -1)
				: lua_tointeger(g_L, -1));
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
	return APP_NAME;
}

/*
 * Startup sequence: IdentifyPlugIn, OnCreate, RegisterCallback, CreateMenuItem, OnActivate, ...
 * Therefore, 1-st time here Pl/Sql functions are not available.
 */
PLUGIN_API void
OnCreate (void)
{
	if (!g_IsActive) return;

	if (g_L || !(g_L = luaL_newstate()))
		return;

	/* open libraries */
	luaL_openlibs(g_L);

	luaL_newlib(g_L, plsqllib);
	luaL_newlib(g_L, plsql_syslib);
	lua_setfield(g_L, -2, "sys");
	luaL_newlib(g_L, plsql_idelib);
	lua_setfield(g_L, -2, "ide");
	luaL_newlib(g_L, plsql_sqllib);
	lua_setfield(g_L, -2, "sql");
	lua_setglobal(g_L, "plsql");

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
	g_PlugIn.ref_addons = luaL_ref(g_L, LUA_REGISTRYINDEX);

	/* traceback function */
	lua_pushvalue(g_L, -2);
	g_PlugIn.ref_traceback = luaL_ref(g_L, LUA_REGISTRYINDEX);

	/* template string */
	lua_pushnil(g_L);
	g_PlugIn.ref_template = luaL_ref(g_L, LUA_REGISTRYINDEX);

	/* about string */
	lua_pushnil(g_L);
	g_PlugIn.ref_about = luaL_ref(g_L, LUA_REGISTRYINDEX);

	/* timers table */
	lua_newtable(g_L);
	g_PlugIn.ref_timers = luaL_ref(g_L, LUA_REGISTRYINDEX);
}

PLUGIN_API void
OnDestroy (void)
{
	if (g_L) {
		lua_close(g_L);
		g_L = NULL;
		g_LNCalls = 0;
		g_PlugIn.cb_bits = 0;
	}
}

PLUGIN_API void
RegisterCallback (int i, PLSQL_Function func)
{
	if (i < MAX_FUNCTIONS)
		PLSQL_FUNC[i] = func;
}

static void
AfterReload (void)
{
	const int cb = Func_AfterReload;

	if (callback_exists(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnActivate (void)
{
	static unsigned int g_ActivateCount = 0;

	const int cb = Func_OnActivate;

	g_IsActive = 1;

	OnCreate();

	RefreshMenus();  /* add menus */

	if (callback_exists(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}

	if (g_ActivateCount++) {
		AfterReload();
	}
}

PLUGIN_API void
OnDeactivate (void)
{
	const int cb = Func_OnDeactivate;

	if (callback_exists(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}

	OnDestroy();

	g_IsActive = 0;

	RefreshMenus();  /* remove menus */
}

static void
CreateMenuItemArgs (const char **data)
{
	*data = lua_tostring(g_L, -1);
}

PLUGIN_API const char *
CreateMenuItem (int i)
{
	const int cb = Func_CreateMenuItem;
	const char *s = NULL;

	if (i == 1) {
		g_UseRibbonMenu = (Version() >= 1200);
	}

	if (i > MAX_MENUS) {
		/* Plugin menus */
		if (g_UseRibbonMenu) {
			if (i == PLUGIN_MENU_TAB)
				s = "TAB=Lua";
			else if (i == PLUGIN_MENU_GROUP)
				s = "GROUP=Plug-In";
			else if (i == PLUGIN_MENU_RELOAD)
				s = "ITEM=Reload Plug-In";
		} else {
			if (i == PLUGIN_MENU_RELOAD)
				s = "Lua / Reload Plug-In";
		}
	}
	else if (i <= g_NMenus && callback_exists(cb)) {
		lua_pushinteger(g_L, i);
		call_addons(cb, 1, 1, CreateMenuItemArgs, (void *) &s);
	}
	return s;
}

static void
Reload (void)
{
	OnDeactivate();
	OnActivate();
	RegisterExport();
}

PLUGIN_API void
OnMenuClick (int i)
{
	const int cb = Func_OnMenuClick;

	/* Plugin menus */
	if (i == PLUGIN_MENU_RELOAD) {
		Reload();
		return;
	}

	if (callback_exists(cb)) {
		lua_pushinteger(g_L, i);
		call_addons(cb, 1, 1, NULL, NULL);
	}
}

/* If any Addon returns true then IDE cannot be closed */
PLUGIN_API BOOL
CanClose (void)
{
	const int cb = Func_CanClose;

	return callback_exists(cb)
		? call_addons(cb, 0, 1, NULL, NULL) : TRUE;
}

PLUGIN_API void
AfterStart (void)
{
	const int cb = Func_AfterStart;

	if (callback_exists(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnBrowserChange (void)
{
	const int cb = Func_OnBrowserChange;

	if (callback_exists(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnWindowChange (void)
{
	const int cb = Func_OnWindowChange;

	if (callback_exists(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnWindowCreate (int win_type)
{
	const int cb = Func_OnWindowCreate;

	if (callback_exists(cb)) {
		lua_pushinteger(g_L, win_type);
		call_addons(cb, 1, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnWindowCreated (int win_type)
{
	const int cb = Func_OnWindowCreated;

	if (callback_exists(cb)) {
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
			|| !callback_exists(cb))
		return g_WindowCloseAction;

	lua_pushinteger(g_L, win_type);
	lua_pushboolean(g_L, changed);
	res = call_addons(cb, 2, 0, NULL, NULL);

	return (res & WINCLOSE_CONFIRM)
		? WINCLOSE_CONFIRM : res & WINCLOSE_QUIET;
}

PLUGIN_API BOOL
BeforeExecuteWindow (int win_type)
{
	const int cb = Func_BeforeExecuteWindow;

	if (callback_exists(cb)) {
		lua_pushinteger(g_L, win_type);
		return call_addons(cb, 1, 1, NULL, NULL);
	}
	return TRUE;
}

PLUGIN_API void
AfterExecuteWindow (int win_type, int result)
{
	const int cb = Func_AfterExecuteWindow;

	if (callback_exists(cb)) {
		lua_pushinteger(g_L, win_type);
		lua_pushinteger(g_L, result);
		call_addons(cb, 2, 1, NULL, NULL);
	}
}

PLUGIN_API void
OnConnectionChange (void)
{
	const int cb = Func_OnConnectionChange;

	if (callback_exists(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnWindowConnectionChange (void)
{
	const int cb = Func_OnWindowConnectionChange;

	if (callback_exists(cb)) {
		call_addons(cb, 0, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnPopup (char *obj_type, char *obj_name)
{
	const int cb = Func_OnPopup;

	if (callback_exists(cb)) {
		lua_pushstring(g_L, obj_type);
		lua_pushstring(g_L, obj_name);
		call_addons(cb, 2, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnMainMenu (char *menu_name)
{
	const int cb = Func_OnMainMenu;

	if (callback_exists(cb)) {
		lua_pushstring(g_L, menu_name);
		call_addons(cb, 1, 1, NULL, NULL);
	}
}

static void
OnTemplateArgs (const char **data)
{
	if (!lua_isstring(g_L, -1))
		return;

	*data = lua_tostring(g_L, -1);

	/* prevent string to be collected by GC */
	lua_pushvalue(g_L, -1);
	lua_rawseti(g_L, LUA_REGISTRYINDEX, g_PlugIn.ref_template);

	/* replace 2-nd argument with the result string */
	lua_remove(g_L, -2);
	lua_pushboolean(g_L, 1);
}

PLUGIN_API BOOL
OnTemplate (char *filename, const char **data)
{
	const int cb = Func_OnTemplate;

	if (callback_exists(cb)) {
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

	if (callback_exists(cb)) {
		lua_pushinteger(g_L, win_type);
		lua_pushinteger(g_L, mode);
		call_addons(cb, 2, 0, NULL, NULL);
	}
}

PLUGIN_API void
OnFileSaved (int win_type, int mode)
{
	const int cb = Func_OnFileSaved;

	if (callback_exists(cb)) {
		lua_pushinteger(g_L, win_type);
		lua_pushinteger(g_L, mode);
		call_addons(cb, 2, 0, NULL, NULL);
	}
}

static void
AboutArgs (const char **data)
{
	if (!lua_isstring(g_L, -1))
		return;

	if (!*data)
		lua_pushliteral(g_L, "Lua Addons v" APP_VERSION_STR ":");
	else
		lua_rawgeti(g_L, LUA_REGISTRYINDEX, g_PlugIn.ref_about);

	lua_pushliteral(g_L, "\n- ");

	lua_pushvalue(g_L, -3);
	lua_concat(g_L, 3);
	*data = lua_tostring(g_L, -1);

	lua_rawseti(g_L, LUA_REGISTRYINDEX, g_PlugIn.ref_about);
}

PLUGIN_API const char *
About (void)
{
	const int cb = Func_About;
	const char *s = NULL;

	if (callback_exists(cb)) {
		call_addons(cb, 0, 0, AboutArgs, (void *) &s);
	}
	return s ? s : "Lua Addons not loaded";
}

PLUGIN_API void
CommandLine (int handle, char *command, char *params)
{
	const int cb = Func_CommandLine;

	if (callback_exists(cb)) {
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

	if (callback_exists(cb)) {
		call_addons(cb, 0, 1, NULL, NULL);
	}
	return "Via Lua";
}

PLUGIN_API BOOL
ExportInit (void)
{
	const int cb = Func_ExportInit;

	return callback_exists(cb)
		? call_addons(cb, 0, 1, NULL, NULL) : TRUE;
}

PLUGIN_API void
ExportFinished (void)
{
	const int cb = Func_ExportFinished;

	if (callback_exists(cb)) {
		call_addons(cb, 0, 1, NULL, NULL);
	}
}

PLUGIN_API BOOL
ExportPrepare (void)
{
	const int cb = Func_ExportPrepare;

	return callback_exists(cb)
		? call_addons(cb, 0, 1, NULL, NULL) : TRUE;
}

PLUGIN_API BOOL
ExportData (char *value)
{
	const int cb = Func_ExportData;

	if (callback_exists(cb)) {
		lua_pushstring(g_L, value);
		return call_addons(cb, 1, 1, NULL, NULL);
	}
	return FALSE;
}

