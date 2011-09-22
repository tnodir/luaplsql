/* PL/SQL Developer Lua Plug-In: Auxiliary Functions */

#include <commdlg.h>


/*
 * Arguments: message (string)
 */
static int
plsql_ShowMessage (lua_State *L)
{
	const char *msg = lua_tostring(L, 1);

	ShowMessage(msg);
	return 0;
}

/*
 * Arguments: window_handle (number)
 * Returns: boolean
 */
static int
plsql_SetForegroundWindow (lua_State *L)
{
	const HWND hwnd = (HWND) luaL_checkinteger(L, 1);

	lua_pushboolean(L, SetForegroundWindow(hwnd));
	return 1;
}

/*
 * Returns: window_handle (number)
 */
static int
plsql_GetForegroundWindow (lua_State *L)
{
	lua_pushinteger(L, (int) GetForegroundWindow());
	return 1;
}

/*
 * Arguments: window_handle (number), key_code (number)
 */
static int
plsql_KeyDown (lua_State *L)
{
	const HWND hwnd = (HWND) luaL_checkinteger(L, 1);
	const int key = luaL_checkinteger(L, 2);

	PostMessage(hwnd, WM_KEYDOWN, key, 0);
	return 0;
}

/*
 * Arguments: window_handle (number),
 *	x (number), y (number), width (number), height (number)
 */
static int
plsql_SetWindowPos (lua_State *L)
{
	const HWND hwnd = (HWND) luaL_checkinteger(L, 1);
	const int x = lua_tointeger(L, 2);
	const int y = lua_tointeger(L, 3);
	const int w = lua_tointeger(L, 4);
	const int h = lua_tointeger(L, 5);

	SetWindowPos(hwnd, NULL, x, y, w, h, SWP_NOACTIVATE);
	return 0;
}

/*
 * Arguments: window_handle (number)
 * Returns: [x (number), y (number), width (number), height (number)]
 */
static int
plsql_GetWindowPos (lua_State *L)
{
	const HWND hwnd = (HWND) luaL_checkinteger(L, 1);
	RECT r;

	if (GetWindowRect(hwnd, &r)) {
		lua_pushinteger(L, r.left);
		lua_pushinteger(L, r.top);
		lua_pushinteger(L, r.right - r.left);
		lua_pushinteger(L, r.bottom - r.top);
		return 4;
	}
	return 0;
}

/*
 * Arguments: window_handle (number)
 * Returns: [width (number), height (number)]
 */
static int
plsql_GetWindowArea (lua_State *L)
{
	const HWND hwnd = (HWND) luaL_checkinteger(L, 1);
	RECT r;

	if (GetClientRect(hwnd, &r)) {
		lua_pushinteger(L, r.right);
		lua_pushinteger(L, r.bottom);
		return 2;
	}
	return 0;
}

/*
 * Arguments: window_handle (number), options (string) ...
 */
static int
plsql_ShowWindow (lua_State *L)
{
	static const int show_flags[] = {
		SW_HIDE, SW_MAXIMIZE, SW_MINIMIZE, SW_RESTORE
	};
	static const char *const show_names[] = {
		"hide", "maximize", "minimize", "restore", NULL
	};
	const HWND hwnd = (HWND) luaL_checkinteger(L, 1);
	int i, flags = 0;

#undef OPT_START
#define OPT_START	2

	for (i = lua_gettop(L); i >= OPT_START; --i) {
		flags |= show_flags[luaL_checkoption(L, i, NULL, show_names)];
	}
	ShowWindow(hwnd, flags);
	return 0;
}

/*
 * Arguments: message (string), [title (string),
 *	buttons (string), icon (string: "Warn", "Info", "Question", "Error")]
 * Returns: [string]
 */
static int
plsql_MessageBox (lua_State *L)
{
	static const int btn_flags[] = {
		MB_ABORTRETRYIGNORE, MB_OK, MB_OKCANCEL,
		MB_RETRYCANCEL, MB_YESNO, MB_YESNOCANCEL
	};
	static const char *const btn_names[] = {
		"AbortRetryIgnore", "Ok", "OkCancel",
		"RetryCancel", "YesNo", "YesNoCancel", NULL
	};
	const char *msg = luaL_checkstring(L, 1);
	const char *title = lua_tostring(L, 2);
	const char *btn = lua_tostring(L, 3);
	const char *icon = lua_tostring(L, 4);
	const char *s;
	int flags = 0;

	if (btn)
		flags |= btn_flags[luaL_checkoption(L, 3, NULL, btn_names)];
	if (icon)
		switch (*icon) {
		case 'W': flags |= MB_ICONWARNING; break;
		case 'I': flags |= MB_ICONINFORMATION; break;
		case 'Q': flags |= MB_ICONQUESTION; break;
		case 'E': flags |= MB_ICONERROR; break;
		}

	switch (MessageBox(g_WindowHandle, msg, title, flags)) {
	case IDABORT:	s = "Abort"; break;
	case IDCANCEL:	s = "Cancel"; break;
	case IDIGNORE:	s = "Ignore"; break;
	case IDNO:	s = "No"; break;
	case IDOK:	s = "Ok"; break;
	case IDRETRY:	s = "Retry"; break;
	case IDYES:	s = "Yes"; break;
	default:	s = NULL;
	}
	lua_pushstring(L, s);
	return 1;
}

/*
 * Arguments: [text (string)]
 * Returns: [boolean]
 */
static int
plsql_SetClipboardText (lua_State *L)
{
	int len;
	const char *s = lua_tolstring(L, 1, &len);
	HGLOBAL hmem;
	char *pmem;
	int res = 0;

	if (!OpenClipboard(g_WindowHandle)) return 0;

	if (EmptyClipboard() && s != NULL) {
		++len; /* include '\0' */
		hmem = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, len);
		if (!hmem) goto err;
		pmem = GlobalLock(hmem);
		memcpy(pmem, s, len);
		GlobalUnlock(hmem);

		res = SetClipboardData(CF_TEXT, hmem) != NULL;
		if (!res) GlobalFree(hmem);
	}
 err:
	CloseClipboard();
	lua_pushboolean(L, res);
	return 1;
}

/*
 * Returns: [string]
 */
static int
plsql_GetClipboardText (lua_State *L)
{
	HGLOBAL hmem;
	char *pmem;

	if (!OpenClipboard(g_WindowHandle)) return 0;

	hmem = GetClipboardData(CF_TEXT);
	if (!hmem)
		lua_pushnil(L);
	else {
		pmem = GlobalLock(hmem);
		lua_pushstring(L, pmem);
		GlobalUnlock(hmem);
	}
	CloseClipboard();
	return 1;
}

/*
 * Returns: string
 */
static int
plsql_RootPath (lua_State *L)
{
	char path[MAX_PATH];
	const int n = GetEnvironmentVariable(PLUGIN_ENV, path, sizeof(path));

	lua_pushlstring(L, path, n);
	return 1;
}

/*
 * Returns: string
 */
static int
plsql_ExePath (lua_State *L)
{
	char path[MAX_PATH];
	int n = GetModuleFileName(NULL, path, sizeof(path));

	if (n) {
		while (path[--n] != '\\')
			continue;
	}
	lua_pushlstring(L, path, n);
	return 1;
}

/*
 * Arguments: [initial_filename (string),
 *	filters (string: "Name\0Extensions\0 .. \0\0"),
 *	title (string), initial_dir (string)]
 * Returns: [path (string), filter_index (number), readonly (boolean)]
 */
static int
plsql_GetFileName (lua_State *L, BOOL (APIENTRY * func)(LPOPENFILENAME), int flags)
{
	size_t len;
	const char *filename = lua_tolstring(L, 1, &len);
	const char *filters = lua_tostring(L, 2);
	const char *title = lua_tostring(L, 3);
	const char *dir = lua_tostring(L, 4);
	char path[MAX_PATH];
	OPENFILENAME ofn;

	if (filename && len < sizeof(path))
		memcpy(path, filename, len + 1);
	else
		path[0] = '\0';

	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_WindowHandle;
	ofn.lpstrFilter = filters;
	if (filters) {
		ofn.lpstrDefExt = strchr(filters + strlen(filters) + 1, '.');
		if (ofn.lpstrDefExt) ofn.lpstrDefExt++;
	}
	ofn.lpstrFile = path;
	ofn.nMaxFile = sizeof(path);
	ofn.lpstrInitialDir = dir;
	ofn.lpstrTitle = title;
	ofn.Flags = flags | OFN_NOCHANGEDIR;

	if (func(&ofn)) {
		lua_pushstring(L, path);
		lua_pushinteger(L, ofn.nFilterIndex);
		lua_pushboolean(L, ofn.Flags & OFN_READONLY);
		return 3;
	}
	return 0;
}

static int
plsql_GetSaveFileName (lua_State *L)
{
	return plsql_GetFileName(L, GetSaveFileName, OFN_OVERWRITEPROMPT);
}

static int
plsql_GetOpenFileName (lua_State *L)
{
	return plsql_GetFileName(L, GetOpenFileName, 0);
}


static void CALLBACK
plsql_timer_handler (HWND hwnd,	int msg, int id, DWORD time)
{
	int top = 0;

	if (g_LNCalls++ != 0)
		top = push_traceback_addons(0);

	lua_rawgeti(g_L, LUA_REGISTRYINDEX, g_Ref.timers);
	lua_rawgeti(g_L, -1, id);
	lua_remove(g_L, -2);

	lua_pushinteger(g_L, id);
	if (lua_pcall(g_L, 1, 0, top + PLUGIN_TRACEBACK_IDX))
		ShowMessage(lua_tostring(g_L, -1));
	lua_settop(g_L, --g_LNCalls ? top : PLUGIN_ADDONS_IDX);
}

/*
 * Arguments: milliseconds (number), callback (function)
 * Returns: [timer_id (number)]
 */
static int
plsql_SetTimer (lua_State *L)
{
	const int elapse = luaL_checkinteger(L, 1);
	int id;

	luaL_checktype(L, 2, LUA_TFUNCTION);

	id = SetTimer(NULL, 0, elapse, (TIMERPROC) plsql_timer_handler);
	if (id) {
		lua_rawgeti(L, LUA_REGISTRYINDEX, g_Ref.timers);
		lua_pushvalue(L, 2);  /* callback function */
		lua_rawseti(L, -2, id);

		lua_pushinteger(L, id);
		return 1;
	}
	return 0;
}

/*
 * Arguments: timer_id (number)
 * Returns: boolean
 */
static int
plsql_KillTimer (lua_State *L)
{
	const int id = luaL_checkinteger(L, 1);

	lua_rawgeti(L, LUA_REGISTRYINDEX, g_Ref.timers);
	lua_pushnil(L);
	lua_rawseti(L, -2, id);

	lua_pushboolean(L, KillTimer(NULL, id));
	return 1;
}


static luaL_reg plsqllib[] = {
    {"ShowMessage",		plsql_ShowMessage},
    {"SetForegroundWindow",	plsql_SetForegroundWindow},
    {"GetForegroundWindow",	plsql_GetForegroundWindow},
    {"KeyDown",			plsql_KeyDown},
    {"SetWindowPos",		plsql_SetWindowPos},
    {"GetWindowPos",		plsql_GetWindowPos},
    {"GetWindowArea",		plsql_GetWindowArea},
    {"ShowWindow",		plsql_ShowWindow},
    {"MessageBox",		plsql_MessageBox},
    {"SetClipboardText",	plsql_SetClipboardText},
    {"GetClipboardText",	plsql_GetClipboardText},
    {"RootPath",		plsql_RootPath},
    {"ExePath",			plsql_ExePath},
    {"GetSaveFileName",		plsql_GetSaveFileName},
    {"GetOpenFileName",		plsql_GetOpenFileName},
    {"SetTimer",		plsql_SetTimer},
    {"KillTimer",		plsql_KillTimer},
    {NULL, NULL}
};
