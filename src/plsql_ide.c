/* PL/SQL Developer Lua Plug-In: IDE Functions */

#include <richedit.h>


typedef void (*IDE_MenuState)(int ID, int Index, BOOL Enabled);
typedef BOOL (*IDE_Connected)();
typedef void (*IDE_GetConnectionInfo)(char **Username, char **Password, char **Database);
typedef void (*IDE_GetBrowserInfo)(char **ObjectType, char **ObjectOwner, char **ObjectName);
typedef int (*IDE_GetWindowType)();
typedef HANDLE (*IDE_GetAppHandle)();
typedef HWND (*IDE_GetWindowHandle)();
typedef HWND (*IDE_GetClientHandle)();
typedef HWND (*IDE_GetChildHandle)();
typedef int (*IDE_Refresh)();
typedef void (*IDE_CreateWindow)(int WindowType, const char *Text, BOOL Execute);
typedef BOOL (*IDE_OpenFile)(int WindowType, const char *Filename);
typedef BOOL (*IDE_SaveFile)();
typedef char *(*IDE_Filename)();
typedef void (*IDE_CloseFile)();
typedef void (*IDE_SetReadOnly)(BOOL ReadOnly);
typedef BOOL (*IDE_GetReadOnly)();
typedef BOOL (*IDE_ExecuteSQLReport)(const char *SQL, const char *Title, BOOL Updateable);
typedef BOOL (*IDE_ReloadFile)();
typedef void (*IDE_SetFilename)(const char *Filename);
typedef char *(*IDE_GetText)();
typedef char *(*IDE_GetSelectedText)();
typedef char *(*IDE_GetCursorWord)();
typedef HWND (*IDE_GetEditorHandle)();
typedef BOOL (*IDE_SetText)(const char *Text);
typedef BOOL (*IDE_SetStatusMessage)(const char *Text);
typedef BOOL (*IDE_SetErrorPosition)(int Line, int Col);
typedef void (*IDE_ClearErrorPositions)();
typedef int (*IDE_GetCursorWordPosition)();
typedef BOOL (*IDE_Perform)(int Param);
typedef char *(*IDE_GetCustomKeywords)();
typedef void (*IDE_SetCustomKeywords)(const char *Keywords);
typedef void (*IDE_SetKeywords)(int ID, int Style, const char *Keywords);
typedef void (*IDE_ActivateKeywords)();
typedef void (*IDE_RefreshMenus)(int ID);
typedef void (*IDE_SetMenuName)(int ID, int Index, const char *Name);
typedef void (*IDE_SetMenuCheck)(int ID, int Index, BOOL Checked);
typedef void (*IDE_SetMenuVisible)(int ID, int Index, BOOL Visible);
typedef char *(*IDE_GetMenulayout)();
typedef void (*IDE_CreatePopupItem)(int ID, int Index, const char *Name, const char *ObjectType);
typedef BOOL (*IDE_SetConnection)(const char *Username, const char *Password, const char *Database);
typedef void (*IDE_GetObjectInfo)(const char *AnObject, char **ObjectType, char **ObjectOwner,
	char **ObjectName, char **SubObject);
typedef char *(*IDE_GetBrowserItems)(const char *Node, BOOL GetItems);
typedef void (*IDE_RefreshBrowser)(const char *Node);
typedef void (*IDE_GetPopupObject)(char **ObjectType, char **ObjectOwner,
	char **ObjectName, char **SubObject);
typedef char *(*IDE_GetPopupBrowserRoot)();
typedef void (*IDE_RefreshObject)(const char *ObjectType, const char *ObjectOwner,
	const char *ObjectName, int Action);
typedef BOOL (*IDE_FirstSelectedObject)(char **ObjectType, char **ObjectOwner,
	char **ObjectName, char **SubObject);
typedef BOOL (*IDE_NextSelectedObject)(char **ObjectType, char **ObjectOwner,
	char **ObjectName, char **SubObject);
typedef char *(*IDE_GetObjectSource)(const char *ObjectType, const char *ObjectOwner,
	const char *ObjectName);
typedef int (*IDE_GetWindowCount)();
typedef BOOL (*IDE_SelectWindow)(int Index);
typedef BOOL (*IDE_ActivateWindow)(int Index);
typedef BOOL (*IDE_IsWindowModified)();
typedef BOOL (*IDE_IsWindowRunning)();
typedef int (*IDE_WindowPin)(int Pin);
typedef void (*IDE_SplashCreate)(int ProgressMax);
typedef void (*IDE_SplashHide)();
typedef void (*IDE_SplashWrite)(const char *Text);
typedef void (*IDE_SplashWriteLn)(const char *Text);
typedef void (*IDE_SplashProgress)(int Progress);
typedef char *(*IDE_TemplatePath)();
typedef BOOL (*IDE_ExecuteTemplate)(const char *Template, BOOL NewWindow);
typedef char *(*IDE_GetConnectAs)();
typedef BOOL (*IDE_SetConnectionAs)(const char *Username, const char *Password,
	const char *Database, const char *ConnectAs);
typedef char *(*IDE_GetFileOpenMenu)(int MenuIndex, int *WindowType);
typedef BOOL (*IDE_CanSaveWindow)();
typedef void (*IDE_OpenFileExternal)(int WindowType, const char *Data,
	const char *FileSystem, const char *FileTag,
	const char *Filename);
typedef char *(*IDE_GetFileTypes)(int WindowType);
typedef char *(*IDE_GetDefaultExtension)(int WindowType);
typedef char *(*IDE_GetFileData)();
typedef void (*IDE_FileSaved)(const char *FileSystem, const char *FileTag, const char *Filename);
typedef BOOL (*IDE_ShowHTML)(const char *Url, const char *Hash,
	const char *Title, const char *ID);
typedef BOOL (*IDE_RefreshHTML)(const char *Url, const char *ID, BOOL BringToFront);
typedef char *(*IDE_GetProcEditExtension)(const char *ObjectType);
typedef BOOL (*IDE_GetWindowObject)(char **ObjectType, char **ObjectOwner,
	char **ObjectName, char **SubObject);
typedef char *(*IDE_FirstSelectedFile)(BOOL Files, BOOL Directories);
typedef char *(*IDE_NextSelectedFile)();
typedef void (*IDE_RefreshFileBrowser)();
typedef void (*IDE_KeyPress)(int Key, int Shift);
typedef int (*IDE_GetMenuItem)(const char *MenuName);
typedef BOOL (*IDE_SelectMenu)(int MenuItem);
typedef char *(*IDE_TranslationFile)();
typedef char *(*IDE_TranslationLanguage)();
typedef char *(*IDE_GetTranslatedMenuLayout)();
typedef char *(*IDE_MainFont)();
typedef char *(*IDE_TranslateItems)(const char *Group);
typedef char *(*IDE_TranslateString)(const char *ID, const char *Default,
	const char *Param1, const char *Param2);
typedef BOOL (*IDE_SaveRecoveryFiles)();
typedef int (*IDE_GetCursorX)();
typedef int (*IDE_GetCursorY)();
typedef void (*IDE_SetCursor)(int X, int Y);
typedef int (*IDE_SetBookmark)(int Index, int X, int Y);
typedef int (*IDE_ClearBookmark)(int Index);
typedef int (*IDE_GotoBookmark)(int Index);
typedef BOOL (*IDE_GetBookmark)(int Index, int *X, int *Y);
typedef char *(*IDE_TabInfo)(int Index);
typedef int (*IDE_TabIndex)(int Index);
typedef void (*IDE_CreateToolButton)(int ID, int Index, const char *Name,
	const char *BitmapFile, int BitmapHandle);
typedef BOOL (*IDE_WindowHasEditor)(BOOL CodeEditor);
typedef int (*IDE_BeautifierOptions)();
typedef BOOL (*IDE_BeautifyWindow)();
typedef char *(*IDE_BeautifyText)(const char *Text);
typedef BOOL (*IDE_ObjectAction)(const char *Action, const char *ObjectType,
	const char *ObjectOwner, const char *ObjectName);
typedef BOOL (*IDE_ShowDialog)(const char *Dialog, const char *Param);
typedef void (*IDE_DebugLog)(const char *Message);
typedef char *(*IDE_GetParamString)(const char *Name);
typedef BOOL (*IDE_GetParamBool)(const char *Name);
typedef void (*IDE_GetBrowserFilter)(int Index, char **Name, char **WhereClause,
	char **OrderByClause, char **User, BOOL *Active);
typedef void (*IDE_CommandFeedback)(int FeedbackHandle, const char *Text);
typedef int (*IDE_ResultGridRowCount)();
typedef int (*IDE_ResultGridColCount)();
typedef char *(*IDE_ResultGridCell)(int Col, int Row);
typedef BOOL (*IDE_Authorized)(const char *Category, const char *Name, const char *SubName);
typedef BOOL (*IDE_WindowAllowed)(int WindowType, BOOL ShowErrorMessage);
typedef BOOL (*IDE_Authorization)();
typedef char *(*IDE_AuthorizationItems)(const char *Category);
typedef void (*IDE_AddAuthorizationItem)(int PlugInID, const char *Name);
typedef char *(*IDE_GetPersonalPrefSets)();
typedef char *(*IDE_GetDefaultPrefSets)();
typedef char *(*IDE_GetPrefAsString)(int PlugInID, const char *PrefSet,
	const char *Name, const char *Default);
typedef int (*IDE_GetPrefAsInteger)(int PlugInID, const char *PrefSet,
	const char *Name, int Default);
typedef BOOL (*IDE_GetPrefAsBool)(int PlugInID, const char *PrefSet,
	const char *Name, BOOL Default);
typedef BOOL (*IDE_SetPrefAsString)(int PlugInID, const char *PrefSet,
	const char *Name, const char *Value);
typedef BOOL (*IDE_SetPrefAsInteger)(int PlugInID, const char *PrefSet,
	const char *Name, int Value);
typedef BOOL (*IDE_SetPrefAsBool)(int PlugInID, const char *PrefSet,
	const char *Name, BOOL Value);
typedef char *(*IDE_GetGeneralPref)(const char *Name);
typedef BOOL (*IDE_PlugInSetting)(int PlugInID, const char *Setting, const char *Value);
typedef int (*IDE_GetProcOverloadCount)(const char *Owner, const char *PackageName,
	const char *ProcedureName);
typedef int (*IDE_SelectProcOverloading)(const char *Owner, const char *PackageName,
	const char *ProcedureName);
typedef char *(*IDE_GetSessionValue)(const char *Name);
typedef BOOL (*IDE_CheckDBVersion)(const char *Version);
typedef BOOL (*IDE_GetConnectionInfoEx)(int Index, char **Username, char **Password,
	char **Database, char **ConnectAs);
typedef int (*IDE_FindConnection)(const char *Username, const char *Database);
typedef int (*IDE_AddConnection)(const char *Username, const char *Password,
	const char *Database, const char *ConnectAs);
typedef BOOL (*IDE_ConnectConnection)(int Index);
typedef BOOL (*IDE_SetMainConnection)(int Index);
typedef int (*IDE_GetWindowConnection)();
typedef BOOL (*IDE_SetWindowConnection)(int Index);
typedef BOOL (*IDE_GetConnectionTree)(int Index, char **Description, char **Username,
	char **Password, char **Database, char **ConnectAs, int *ID, int *ParentID);
typedef BOOL (*IDE_GetConnectionInfoEx10)(int Index, char **Username, char **Password,
	char **Database, char **ConnectAs, char **Edition, char **Workspace);
typedef int (*IDE_FindConnectionEx10)(const char *Username, const char *Database,
	const char *Edition, const char *Workspace);
typedef int (*IDE_AddConnectionEx10)(const char *Username, const char *Password,
	const char *Database, const char *ConnectAs,
	const char *Edition, const char *Workspace);
typedef BOOL (*IDE_GetConnectionTreeEx10)(int Index, char **Description, char **Username,
	char **Password, char **Database, char **ConnectAs,
	char **Edition, char **Workspace, int *ID, int *ParentID);


/*
 * Arguments: Index (number), Enabled (boolean)
 * Returns: [number]
 */
static int
plsql_ide_MenuState (lua_State *L)
{
	IDE_MenuState func = (IDE_MenuState) PLSQL_FUNC[10];

	if (func) {
		const int i = luaL_checkint(L, 1);
		const int enabled = lua_toboolean(L, 2);

		func(g_PlugInId, PLSQL_MENU[i], enabled);
	}
	return 0;
}

/*
 * Returns: [boolean]
 */
static int
plsql_ide_Connected (lua_State *L)
{
	IDE_Connected func = (IDE_Connected) PLSQL_FUNC[11];

	if (func) {
		lua_pushboolean(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [Username (string), Password (string), Database (string)]
 */
static int
plsql_ide_GetConnectionInfo (lua_State *L)
{
	IDE_GetConnectionInfo func = (IDE_GetConnectionInfo) PLSQL_FUNC[12];

	if (func) {
		char *usr, *pwd, *db;

		func(&usr, &pwd, &db);
		lua_pushstring(L, usr);
		lua_pushstring(L, pwd);
		lua_pushstring(L, db);
		return 3;
	}
	return 0;
}

/*
 * Returns: [ObjectType (string), ObjectOwner (string), ObjectName (string)]
 */
static int
plsql_ide_GetBrowserInfo (lua_State *L)
{
	IDE_GetBrowserInfo func = (IDE_GetBrowserInfo) PLSQL_FUNC[13];

	if (func) {
		char *type, *owner, *name;

		func(&type, &owner, &name);
		lua_pushstring(L, type);
		lua_pushstring(L, owner);
		lua_pushstring(L, name);
		return 3;
	}
	return 0;
}

/*
 * Returns: [WindowType (number)]
 */
static int
plsql_ide_GetWindowType (lua_State *L)
{
	IDE_GetWindowType func = (IDE_GetWindowType) PLSQL_FUNC[14];

	if (func) {
		lua_pushinteger(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: number
 */
static int
plsql_ide_GetAppHandle (lua_State *L)
{
	IDE_GetAppHandle func = (IDE_GetAppHandle) PLSQL_FUNC[15];

	lua_pushinteger(L, (lua_Integer) func());
	return 1;
}

static HWND
GetWindowHandle (void)
{
	static HWND g_WindowHandle = NULL;  /* Pl/Sql Developer Window Handle */

	if (!g_WindowHandle) {
		IDE_GetWindowHandle func = (IDE_GetWindowHandle) PLSQL_FUNC[16];

		if (func) {
			g_WindowHandle = func();
		}
	}
	return g_WindowHandle;
}

/*
 * Arguments: number
 */
static int
plsql_ide_GetWindowHandle (lua_State *L)
{
	lua_pushinteger(L, (lua_Integer) GetWindowHandle());
	return 1;
}

/*
 * Arguments: number
 */
static int
plsql_ide_GetClientHandle (lua_State *L)
{
	IDE_GetClientHandle func = (IDE_GetClientHandle) PLSQL_FUNC[17];

	lua_pushinteger(L, (lua_Integer) func());
	return 1;
}

/*
 * Arguments: number
 */
static int
plsql_ide_GetChildHandle (lua_State *L)
{
	IDE_GetChildHandle func = (IDE_GetChildHandle) PLSQL_FUNC[18];

	lua_pushinteger(L, (lua_Integer) func());
	return 1;
}

static int
plsql_ide_Refresh (lua_State *L)
{
	IDE_Refresh func = (IDE_Refresh) PLSQL_FUNC[19];

	(void) L;

	if (func) {
		func();
	}
	return 0;
}

/*
 * Arguments: WindowType (number), Text (string), Execute (boolean)
 */
static int
plsql_ide_CreateWindow (lua_State *L)
{
	IDE_CreateWindow func = (IDE_CreateWindow) PLSQL_FUNC[20];

	if (func) {
		const int wt = luaL_checkint(L, 1);
		const char *text = luaL_checkstring(L, 2);
		const int exec = lua_toboolean(L, 3);

		func(wt, text, exec);
	}
	return 0;
}

/*
 * Arguments: WindowType (number), Filename (string)
 * Returns: [boolean]
 */
static int
plsql_ide_OpenFile (lua_State *L)
{
	IDE_OpenFile func = (IDE_OpenFile) PLSQL_FUNC[21];

	if (func) {
		const int wt = luaL_checkint(L, 1);
		const char *path = luaL_checkstring(L, 2);

		lua_pushboolean(L, func(wt, path));
		return 1;
	}
	return 0;
}

/*
 * Returns: [boolean]
 */
static int
plsql_ide_SaveFile (lua_State *L)
{
	IDE_SaveFile func = (IDE_SaveFile) PLSQL_FUNC[22];

	if (func) {
		lua_pushboolean(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_Filename (lua_State *L)
{
	IDE_Filename func = (IDE_Filename) PLSQL_FUNC[23];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: [CloseAction (number)]
 */
static int
plsql_ide_CloseFile (lua_State *L)
{
	IDE_CloseFile func = (IDE_CloseFile) PLSQL_FUNC[24];

	(void) L;

	if (func) {
		const int old = g_WindowCloseAction;

		if (lua_gettop(L))
			g_WindowCloseAction = (int) lua_tointeger(L, 1);
		func();
		g_WindowCloseAction = old;
	}
	return 0;
}

/*
 * Arguments: ReadOnly (boolean)
 */
static int
plsql_ide_SetReadOnly (lua_State *L)
{
	IDE_SetReadOnly func = (IDE_SetReadOnly) PLSQL_FUNC[25];

	if (func) {
		const int ro = lua_toboolean(L, 1);

		func(ro);
	}
	return 0;
}

/*
 * Returns: [boolean]
 */
static int
plsql_ide_GetReadOnly (lua_State *L)
{
	IDE_GetReadOnly func = (IDE_GetReadOnly) PLSQL_FUNC[26];

	if (func) {
		lua_pushboolean(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: SQL (string), Title (string), Updateable (boolean)
 * Returns: [boolean]
 */
static int
plsql_ide_ExecuteSQLReport (lua_State *L)
{
	IDE_ExecuteSQLReport func = (IDE_ExecuteSQLReport) PLSQL_FUNC[27];

	if (func) {
		const char *sql = luaL_checkstring(L, 1);
		const char *title = luaL_checkstring(L, 2);
		const int upd = lua_toboolean(L, 3);

		lua_pushboolean(L, func(sql, title, upd));
		return 1;
	}
	return 0;
}

/*
 * Returns: [boolean]
 */
static int
plsql_ide_ReloadFile (lua_State *L)
{
	IDE_ReloadFile func = (IDE_ReloadFile) PLSQL_FUNC[28];

	if (func) {
		lua_pushboolean(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Filename (string)
 */
static int
plsql_ide_SetFilename (lua_State *L)
{
	IDE_SetFilename func = (IDE_SetFilename) PLSQL_FUNC[29];

	if (func) {
		const char *path = luaL_checkstring(L, 1);

		func(path);
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_GetText (lua_State *L)
{
	IDE_GetText func = (IDE_GetText) PLSQL_FUNC[30];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_GetSelectedText (lua_State *L)
{
	IDE_GetSelectedText func = (IDE_GetSelectedText) PLSQL_FUNC[31];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_GetCursorWord (lua_State *L)
{
	IDE_GetCursorWord func = (IDE_GetCursorWord) PLSQL_FUNC[32];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: number
 */
static int
plsql_ide_GetEditorHandle (lua_State *L)
{
	IDE_GetEditorHandle func = (IDE_GetEditorHandle) PLSQL_FUNC[33];

	lua_pushinteger(L, (lua_Integer) func());
	return 1;
}

/*
 * Arguments: Text (string)
 * Returns: [boolean]
 */
static int
plsql_ide_SetText (lua_State *L)
{
	IDE_SetText func = (IDE_SetText) PLSQL_FUNC[34];

	if (func) {
		const char *text = luaL_checkstring(L, 1);

		lua_pushboolean(L, func(text));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Text (string)
 * Returns: [boolean]
 */
static int
plsql_ide_SetStatusMessage (lua_State *L)
{
	IDE_SetStatusMessage func = (IDE_SetStatusMessage) PLSQL_FUNC[35];

	if (func) {
		const char *text = luaL_checkstring(L, 1);

		lua_pushboolean(L, func(text));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Line (number), Col (number)
 * Returns: [boolean]
 */
static int
plsql_ide_SetErrorPosition (lua_State *L)
{
	IDE_SetErrorPosition func = (IDE_SetErrorPosition) PLSQL_FUNC[36];

	if (func) {
		const int line = luaL_checkint(L, 1);
		const int col = luaL_checkint(L, 2);

		lua_pushboolean(L, func(line, col));
		return 1;
	}
	return 0;
}

static int
plsql_ide_ClearErrorPositions (lua_State *L)
{
	IDE_ClearErrorPositions func = (IDE_ClearErrorPositions) PLSQL_FUNC[37];

	(void) L;

	if (func) {
		func();
	}
	return 0;
}

/*
 * Returns: [number]
 */
static int
plsql_ide_GetCursorWordPosition (lua_State *L)
{
	IDE_GetCursorWordPosition func = (IDE_GetCursorWordPosition) PLSQL_FUNC[38];

	if (func) {
		lua_pushinteger(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Param (number)
 * Returns: [boolean]
 */
static int
plsql_ide_Perform (lua_State *L)
{
	IDE_Perform func = (IDE_Perform) PLSQL_FUNC[39];

	if (func) {
		const int param = luaL_checkint(L, 1);

		lua_pushboolean(L, func(param));
		return 1;
	}
	return 0;
}

/*
 * Returns: string
 */
static int
plsql_ide_GetCustomKeywords (lua_State *L)
{
	IDE_GetCustomKeywords func = (IDE_GetCustomKeywords) PLSQL_FUNC[60];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Keywords (string)
 */
static int
plsql_ide_SetCustomKeywords (lua_State *L)
{
	IDE_SetCustomKeywords func = (IDE_SetCustomKeywords) PLSQL_FUNC[61];

	if (func) {
		const char *s = luaL_checkstring(L, 1);

		func(s);
	}
	return 0;
}

/*
 * Arguments: Style (number), Keywords (string)
 */
static int
plsql_ide_SetKeywords (lua_State *L)
{
	IDE_SetKeywords func = (IDE_SetKeywords) PLSQL_FUNC[62];

	if (func) {
		const int style = luaL_checkint(L, 1);
		const char *s = luaL_checkstring(L, 2);

		func(g_PlugInId, style, s);
	}
	return 0;
}

static int
plsql_ide_ActivateKeywords (lua_State *L)
{
	IDE_ActivateKeywords func = (IDE_ActivateKeywords) PLSQL_FUNC[63];

	(void) L;

	if (func) {
		func();
	}
	return 0;
}

static void
RefreshMenus (void)
{
	IDE_RefreshMenus func = (IDE_RefreshMenus) PLSQL_FUNC[64];

	if (func) {
		func(g_PlugInId);
	}
}

static int
plsql_ide_RefreshMenus (lua_State *L)
{
	(void) L;

	RefreshMenus();
	return 0;
}

/*
 * Arguments: Index (number), Name (string)
 */
static int
plsql_ide_SetMenuName (lua_State *L)
{
	IDE_SetMenuName func = (IDE_SetMenuName) PLSQL_FUNC[65];

	if (func) {
		const int i = luaL_checkint(L, 1);
		const char *name = luaL_checkstring(L, 2);

		func(g_PlugInId, PLSQL_MENU[i], name);
	}
	return 0;
}

/*
 * Arguments: Index (number), Checked (boolean)
 */
static int
plsql_ide_SetMenuCheck (lua_State *L)
{
	IDE_SetMenuCheck func = (IDE_SetMenuCheck) PLSQL_FUNC[66];

	if (func) {
		const int i = luaL_checkint(L, 1);
		const int checked = lua_toboolean(L, 2);

		func(g_PlugInId, PLSQL_MENU[i], checked);
	}
	return 0;
}

/*
 * Arguments: Index (number), Visible (boolean)
 */
static int
plsql_ide_SetMenuVisible (lua_State *L)
{
	IDE_SetMenuVisible func = (IDE_SetMenuVisible) PLSQL_FUNC[67];

	if (func) {
		const int i = luaL_checkint(L, 1);
		const int visible = lua_toboolean(L, 2);

		func(g_PlugInId, PLSQL_MENU[i], visible);
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_GetMenulayout (lua_State *L)
{
	IDE_GetMenulayout func = (IDE_GetMenulayout) PLSQL_FUNC[68];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Index (number), Name (string), ObjectType (string)
 */
static int
plsql_ide_CreatePopupItem (lua_State *L)
{
	IDE_CreatePopupItem func = (IDE_CreatePopupItem) PLSQL_FUNC[69];

	if (func) {
		const int i = luaL_checkint(L, 1);
		const char *name = luaL_checkstring(L, 2);
		const char *type = luaL_checkstring(L, 3);

		func(g_PlugInId, PLSQL_MENU[i], name, type);
	}
	return 0;
}

/*
 * Arguments: Username (string), Password (string), Database (string)
 * Returns: [boolean]
 */
static int
plsql_ide_SetConnection (lua_State *L)
{
	IDE_SetConnection func = (IDE_SetConnection) PLSQL_FUNC[70];

	if (func) {
		const char *usr = luaL_checkstring(L, 1);
		const char *pwd = luaL_checkstring(L, 2);
		const char *db = luaL_checkstring(L, 3);

		lua_pushboolean(L, func(usr, pwd, db));
		return 1;
	}
	return 0;
}

/*
 * Arguments: AnObject (string)
 * Returns: [ObjectType (string), ObjectOwner (string), ObjectName (string), SubObject (string)]
 */
static int
plsql_ide_GetObjectInfo (lua_State *L)
{
	IDE_GetObjectInfo func = (IDE_GetObjectInfo) PLSQL_FUNC[71];

	if (func) {
		const char *obj = luaL_checkstring(L, 1);
		char *type, *owner, *name, *sub;

		func(obj, &type, &owner, &name, &sub);
		lua_pushstring(L, type);
		lua_pushstring(L, owner);
		lua_pushstring(L, name);
		lua_pushstring(L, sub);
		return 4;
	}
	return 0;
}

/*
 * Arguments: Node (string), GetItems (boolean)
 * Returns: [string]
 */
static int
plsql_ide_GetBrowserItems (lua_State *L)
{
	IDE_GetBrowserItems func = (IDE_GetBrowserItems) PLSQL_FUNC[72];

	if (func) {
		const char *node = luaL_checkstring(L, 1);
		const int get = lua_toboolean(L, 2);

		lua_pushstring(L, func(node, get));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Node (string)
 */
static int
plsql_ide_RefreshBrowser (lua_State *L)
{
	IDE_RefreshBrowser func = (IDE_RefreshBrowser) PLSQL_FUNC[73];

	if (func) {
		const char *node = luaL_checkstring(L, 1);

		func(node);
	}
	return 0;
}

/*
 * Returns: [ObjectType (string), ObjectOwner (string), ObjectName (string), SubObject (string)]
 */
static int
plsql_ide_GetPopupObject (lua_State *L)
{
	IDE_GetPopupObject func = (IDE_GetPopupObject) PLSQL_FUNC[74];

	if (func) {
		char *type, *owner, *name, *sub;

		func(&type, &owner, &name, &sub);
		lua_pushstring(L, type);
		lua_pushstring(L, owner);
		lua_pushstring(L, name);
		lua_pushstring(L, sub);
		return 4;
	}
	return 0;
}

/*
 * Returns: [ObjectType (string), ObjectOwner (string), ObjectName (string), SubObject (string)]
 */
static int
plsql_ide_GetPopupBrowserRoot (lua_State *L)
{
	IDE_GetPopupBrowserRoot func = (IDE_GetPopupBrowserRoot) PLSQL_FUNC[75];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: ObjectType (string), ObjectOwner (string), ObjectName (string), Action (number)
 */
static int
plsql_ide_RefreshObject (lua_State *L)
{
	IDE_RefreshObject func = (IDE_RefreshObject) PLSQL_FUNC[76];

	if (func) {
		const char *type = luaL_checkstring(L, 1);
		const char *owner = luaL_checkstring(L, 2);
		const char *name = luaL_checkstring(L, 3);
		const int action = luaL_checkint(L, 4);

		func(type, owner, name, action);
	}
	return 0;
}

/*
 * Returns: [ObjectType (string), ObjectOwner (string), ObjectName (string), SubObject (string)]
 */
static int
plsql_ide_FirstSelectedObject (lua_State *L)
{
	IDE_FirstSelectedObject func = (IDE_FirstSelectedObject) PLSQL_FUNC[77];

	if (func) {
		char *type, *owner, *name, *sub;

		if (func(&type, &owner, &name, &sub)) {
			lua_pushstring(L, type);
			lua_pushstring(L, owner);
			lua_pushstring(L, name);
			lua_pushstring(L, sub);
			return 4;
		}
	}
	return 0;
}

/*
 * Returns: [ObjectType (string), ObjectOwner (string), ObjectName (string), SubObject (string)]
 */
static int
plsql_ide_NextSelectedObject (lua_State *L)
{
	IDE_NextSelectedObject func = (IDE_NextSelectedObject) PLSQL_FUNC[78];

	if (func) {
		char *type, *owner, *name, *sub;

		if (func(&type, &owner, &name, &sub)) {
			lua_pushstring(L, type);
			lua_pushstring(L, owner);
			lua_pushstring(L, name);
			lua_pushstring(L, sub);
			return 4;
		}
	}
	return 0;
}

/*
 * Arguments: ObjectType (string), ObjectOwner (string), ObjectName (string)
 * Returns: [string]
 */
static int
plsql_ide_GetObjectSource (lua_State *L)
{
	IDE_GetObjectSource func = (IDE_GetObjectSource) PLSQL_FUNC[79];

	if (func) {
		const char *type = luaL_checkstring(L, 1);
		const char *owner = luaL_checkstring(L, 2);
		const char *name = luaL_checkstring(L, 3);

		lua_pushstring(L, func(type, owner, name));
		return 1;
	}
	return 0;
}

/*
 * Returns: [number]
 */
static int
plsql_ide_GetWindowCount (lua_State *L)
{
	IDE_GetWindowCount func = (IDE_GetWindowCount) PLSQL_FUNC[80];

	if (func) {
		lua_pushinteger(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Index (number)
 * Returns: [boolean]
 */
static int
plsql_ide_SelectWindow (lua_State *L)
{
	IDE_SelectWindow func = (IDE_SelectWindow) PLSQL_FUNC[81];

	if (func) {
		const int i = luaL_checkint(L, 1);

		lua_pushboolean(L, func(i));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Index (number)
 * Returns: [boolean]
 */
static int
plsql_ide_ActivateWindow (lua_State *L)
{
	IDE_ActivateWindow func = (IDE_ActivateWindow) PLSQL_FUNC[82];

	if (func) {
		const int i = luaL_checkint(L, 1);

		lua_pushboolean(L, func(i));
		return 1;
	}
	return 0;
}

/*
 * Returns: [boolean]
 */
static int
plsql_ide_IsWindowModified (lua_State *L)
{
	IDE_IsWindowModified func = (IDE_IsWindowModified) PLSQL_FUNC[83];

	if (func) {
		lua_pushboolean(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [boolean]
 */
static int
plsql_ide_IsWindowRunning (lua_State *L)
{
	IDE_IsWindowRunning func = (IDE_IsWindowRunning) PLSQL_FUNC[84];

	if (func) {
		lua_pushboolean(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: [Pin (boolean)]
 * Returns: boolean
 */
static int
plsql_ide_WindowPin (lua_State *L)
{
	IDE_WindowPin func = (IDE_WindowPin) PLSQL_FUNC[85];

	if (func) {
		const int pin = lua_isnoneornil(L, 1) ? 2
		 : (lua_toboolean(L, 1) ? 1 : 0);

		lua_pushboolean(L, func(pin));
		return 1;
	}
	return 0;
}

/*
 * Arguments: ProgressMax (number)
 */
static int
plsql_ide_SplashCreate (lua_State *L)
{
	IDE_SplashCreate func = (IDE_SplashCreate) PLSQL_FUNC[90];

	if (func) {
		const int max = luaL_checkint(L, 1);

		func(max);
	}
	return 0;
}

static int
plsql_ide_SplashHide (lua_State *L)
{
	IDE_SplashHide func = (IDE_SplashHide) PLSQL_FUNC[91];

	(void) L;

	if (func) {
		func();
	}
	return 0;
}

/*
 * Arguments: Text (string)
 */
static int
plsql_ide_SplashWrite (lua_State *L)
{
	IDE_SplashWrite func = (IDE_SplashWrite) PLSQL_FUNC[92];

	if (func) {
		const char *text = luaL_checkstring(L, 1);

		func(text);
	}
	return 0;
}

/*
 * Arguments: Text (string)
 */
static int
plsql_ide_SplashWriteLn (lua_State *L)
{
	IDE_SplashWriteLn func = (IDE_SplashWriteLn) PLSQL_FUNC[93];

	if (func) {
		const char *text = luaL_checkstring(L, 1);

		func(text);
	}
	return 0;
}

/*
 * Arguments: Progress (number)
 */
static int
plsql_ide_SplashProgress (lua_State *L)
{
	IDE_SplashProgress func = (IDE_SplashProgress) PLSQL_FUNC[94];

	if (func) {
		const int num = luaL_checkint(L, 1);

		func(num);
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_TemplatePath (lua_State *L)
{
	IDE_TemplatePath func = (IDE_TemplatePath) PLSQL_FUNC[95];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Template (string), NewWindow (boolean)
 * Returns: [boolean]
 */
static int
plsql_ide_ExecuteTemplate (lua_State *L)
{
	IDE_ExecuteTemplate func = (IDE_ExecuteTemplate) PLSQL_FUNC[96];

	if (func) {
		const char *templ = luaL_checkstring(L, 1);
		const int new = lua_toboolean(L, 2);

		lua_pushboolean(L, func(templ, new));
		return 1;
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_GetConnectAs (lua_State *L)
{
	IDE_GetConnectAs func = (IDE_GetConnectAs) PLSQL_FUNC[97];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Username (string), Password (string), Database (string), ConnectAs (string)
 */
static int
plsql_ide_SetConnectionAs (lua_State *L)
{
	IDE_SetConnectionAs func = (IDE_SetConnectionAs) PLSQL_FUNC[98];

	if (func) {
		const char *usr = luaL_checkstring(L, 1);
		const char *pwd = luaL_checkstring(L, 2);
		const char *db = luaL_checkstring(L, 3);
		const char *as = luaL_checkstring(L, 4);

		lua_pushboolean(L, func(usr, pwd, db, as));
		return 1;
	}
	return 0;
}

/*
 * Arguments: MenuIndex (number)
 * Returns: [string]
 */
static int
plsql_ide_GetFileOpenMenu (lua_State *L)
{
	IDE_GetFileOpenMenu func = (IDE_GetFileOpenMenu) PLSQL_FUNC[100];

	if (func) {
		const int i = luaL_checkint(L, 1);
		int wt;

		lua_pushstring(L, func(i, &wt));
		lua_pushinteger(L, wt);
		return 2;
	}
	return 0;
}

/*
 * Returns: [boolean]
 */
static int
plsql_ide_CanSaveWindow (lua_State *L)
{
	IDE_CanSaveWindow func = (IDE_CanSaveWindow) PLSQL_FUNC[101];

	if (func) {
		lua_pushboolean(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: WindowType (number), Data (string), FileSystem (string),
 *	FileTag (string), Filename (string)
 */
static int
plsql_ide_OpenFileExternal (lua_State *L)
{
	IDE_OpenFileExternal func = (IDE_OpenFileExternal) PLSQL_FUNC[102];

	if (func) {
		const int wt = luaL_checkint(L, 1);
		const char *data = luaL_checkstring(L, 2);
		const char *fs = luaL_checkstring(L, 3);
		const char *tag = luaL_checkstring(L, 4);
		const char *path = luaL_checkstring(L, 5);

		func(wt, data, fs, tag, path);
	}
	return 0;
}

/*
 * Arguments: WindowType (number)
 * Returns: [string]
 */
static int
plsql_ide_GetFileTypes (lua_State *L)
{
	IDE_GetFileTypes func = (IDE_GetFileTypes) PLSQL_FUNC[103];

	if (func) {
		const int wt = luaL_checkint(L, 1);

		lua_pushstring(L, func(wt));
		return 1;
	}
	return 0;
}

/*
 * Arguments: WindowType (number)
 * Returns: [string]
 */
static int
plsql_ide_GetDefaultExtension (lua_State *L)
{
	IDE_GetDefaultExtension func = (IDE_GetDefaultExtension) PLSQL_FUNC[104];

	if (func) {
		const int wt = luaL_checkint(L, 1);

		lua_pushstring(L, func(wt));
		return 1;
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_GetFileData (lua_State *L)
{
	IDE_GetFileData func = (IDE_GetFileData) PLSQL_FUNC[105];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Filename (string), [FileSystem (string), FileTag (string)]
 */
static int
plsql_ide_FileSaved (lua_State *L)
{
	IDE_FileSaved func = (IDE_FileSaved) PLSQL_FUNC[106];

	if (func) {
		const char *path = luaL_checkstring(L, 1);
		const char *fs = lua_tostring(L, 2);
		const char *tag = lua_tostring(L, 3);

		func(fs, tag, path);
	}
	return 0;
}

/*
 * Arguments: Url (string), Hash (string), Title (string), ID (string)
 * Returns: [boolean]
 */
static int
plsql_ide_ShowHTML (lua_State *L)
{
	IDE_ShowHTML func = (IDE_ShowHTML) PLSQL_FUNC[107];

	if (func) {
		const char *url = luaL_checkstring(L, 1);
		const char *hash = luaL_checkstring(L, 2);
		const char *title = luaL_checkstring(L, 3);
		const char *id = luaL_checkstring(L, 4);

		lua_pushboolean(L, func(url, hash, title, id));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Url (string), ID (string), BringToFront (boolean)
 * Returns: [boolean]
 */
static int
plsql_ide_RefreshHTML (lua_State *L)
{
	IDE_RefreshHTML func = (IDE_RefreshHTML) PLSQL_FUNC[108];

	if (func) {
		const char *url = luaL_checkstring(L, 1);
		const char *id = luaL_checkstring(L, 2);
		const int front = lua_toboolean(L, 3);

		lua_pushboolean(L, func(url, id, front));
		return 1;
	}
	return 0;
}

/*
 * Arguments: ObjectType (string)
 * Returns: [string]
 */
static int
plsql_ide_GetProcEditExtension (lua_State *L)
{
	IDE_GetProcEditExtension func = (IDE_GetProcEditExtension) PLSQL_FUNC[109];

	if (func) {
		const char *type = luaL_checkstring(L, 1);

		lua_pushstring(L, func(type));
		return 1;
	}
	return 0;
}

/*
 * Returns: [ObjectType (string), ObjectOwner (string), ObjectName (string), SubObject (string)]
 */
static int
plsql_ide_GetWindowObject (lua_State *L)
{
	IDE_GetWindowObject func = (IDE_GetWindowObject) PLSQL_FUNC[110];

	if (func) {
		char *type, *owner, *name, *sub;

		if (func(&type, &owner, &name, &sub)) {
			lua_pushstring(L, type);
			lua_pushstring(L, owner);
			lua_pushstring(L, name);
			lua_pushstring(L, sub);
			return 4;
		}
	}
	return 0;
}

/*
 * Arguments: Files (boolean), Directories (boolean)
 * Returns: [string]
 */
static int
plsql_ide_FirstSelectedFile (lua_State *L)
{
	IDE_FirstSelectedFile func = (IDE_FirstSelectedFile) PLSQL_FUNC[111];

	if (func) {
		const int files = lua_toboolean(L, 1);
		const int dirs = lua_toboolean(L, 2);

		lua_pushstring(L, func(files, dirs));
		return 1;
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_NextSelectedFile (lua_State *L)
{
	IDE_NextSelectedFile func = (IDE_NextSelectedFile) PLSQL_FUNC[112];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

static int
plsql_ide_RefreshFileBrowser (lua_State *L)
{
	IDE_RefreshFileBrowser func = (IDE_RefreshFileBrowser) PLSQL_FUNC[113];

	(void) L;

	if (func) {
		func();
	}
	return 0;
}

/*
 * Arguments: Key (number), [Shift (number)]
 */
static int
plsql_ide_KeyPress (lua_State *L)
{
	IDE_KeyPress func = (IDE_KeyPress) PLSQL_FUNC[120];

	if (func) {
		const int key = luaL_checkint(L, 1);
		const int shift = (int) lua_tointeger(L, 2);

		func(key, shift);
	}
	return 0;
}

/*
 * Arguments: MenuName (string)
 * Returns: [number]
 */
static int
plsql_ide_GetMenuItem (lua_State *L)
{
	IDE_GetMenuItem func = (IDE_GetMenuItem) PLSQL_FUNC[121];

	if (func) {
		const char *menu = luaL_checkstring(L, 1);

		lua_pushinteger(L, func(menu));
		return 1;
	}
	return 0;
}

/*
 * Arguments: MenuItem (number)
 * Returns: [boolean]
 */
static int
plsql_ide_SelectMenu (lua_State *L)
{
	IDE_SelectMenu func = (IDE_SelectMenu) PLSQL_FUNC[122];

	if (func) {
		const int menu = luaL_checkint(L, 1);

		lua_pushinteger(L, func(menu));
		return 1;
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_TranslationFile (lua_State *L)
{
	IDE_TranslationFile func = (IDE_TranslationFile) PLSQL_FUNC[130];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_TranslationLanguage (lua_State *L)
{
	IDE_TranslationLanguage func = (IDE_TranslationLanguage) PLSQL_FUNC[131];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_GetTranslatedMenuLayout (lua_State *L)
{
	IDE_GetTranslatedMenuLayout func = (IDE_GetTranslatedMenuLayout) PLSQL_FUNC[132];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_MainFont (lua_State *L)
{
	IDE_MainFont func = (IDE_MainFont) PLSQL_FUNC[133];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Group (string)
 * Returns: [string]
 */
static int
plsql_ide_TranslateItems (lua_State *L)
{
	IDE_TranslateItems func = (IDE_TranslateItems) PLSQL_FUNC[134];

	if (func) {
		const char *group = luaL_checkstring(L, 1);

		lua_pushstring(L, func(group));
		return 1;
	}
	return 0;
}

/*
 * Arguments: ID (string), Default (string), Param1 (string), Param2 (string)
 * Returns: [string]
 */
static int
plsql_ide_TranslateString (lua_State *L)
{
	IDE_TranslateString func = (IDE_TranslateString) PLSQL_FUNC[135];

	if (func) {
		const char *id = luaL_checkstring(L, 1);
		const char *def = luaL_checkstring(L, 2);
		const char *par1 = luaL_checkstring(L, 3);
		const char *par2 = luaL_checkstring(L, 4);

		lua_pushstring(L, func(id, def, par1, par2));
		return 1;
	}
	return 0;
}

/*
 * Returns: [boolean]
 */
static int
plsql_ide_SaveRecoveryFiles (lua_State *L)
{
	IDE_SaveRecoveryFiles func = (IDE_SaveRecoveryFiles) PLSQL_FUNC[140];

	if (func) {
		lua_pushboolean(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [number]
 */
static int
plsql_ide_GetCursorX (lua_State *L)
{
	IDE_GetCursorX func = (IDE_GetCursorX) PLSQL_FUNC[141];

	if (func) {
		lua_pushinteger(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [number]
 */
static int
plsql_ide_GetCursorY (lua_State *L)
{
	IDE_GetCursorY func = (IDE_GetCursorY) PLSQL_FUNC[142];

	if (func) {
		lua_pushinteger(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: X (number), Y (number)
 */
static int
plsql_ide_SetCursor (lua_State *L)
{
	IDE_SetCursor func = (IDE_SetCursor) PLSQL_FUNC[143];

	if (func) {
		const int x = luaL_checkint(L, 1);
		const int y = luaL_checkint(L, 2);

		func(x, y);
	}
	return 0;
}

/*
 * Arguments: Index (number), X (number), Y (number)
 * Returns: [number]
 */
static int
plsql_ide_SetBookmark (lua_State *L)
{
	IDE_SetBookmark func = (IDE_SetBookmark) PLSQL_FUNC[144];

	if (func) {
		const int i = luaL_checkint(L, 1);
		const int x = luaL_checkint(L, 2);
		const int y = luaL_checkint(L, 3);

		lua_pushinteger(L, func(i, x, y));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Index (number)
 */
static int
plsql_ide_ClearBookmark (lua_State *L)
{
	IDE_ClearBookmark func = (IDE_ClearBookmark) PLSQL_FUNC[145];

	if (func) {
		const int i = luaL_checkint(L, 1);

		func(i);
	}
	return 0;
}

/*
 * Arguments: Index (number)
 */
static int
plsql_ide_GotoBookmark (lua_State *L)
{
	IDE_GotoBookmark func = (IDE_GotoBookmark) PLSQL_FUNC[146];

	if (func) {
		const int i = luaL_checkint(L, 1);

		func(i);
	}
	return 0;
}

/*
 * Arguments: Index (number)
 * Returns: [X (number), Y (number)]
 */
static int
plsql_ide_GetBookmark (lua_State *L)
{
	IDE_GetBookmark func = (IDE_GetBookmark) PLSQL_FUNC[147];

	if (func) {
		const int i = luaL_checkint(L, 1);
		int x, y;

		if (func(i, &x, &y)) {
			lua_pushinteger(L, x);
			lua_pushinteger(L, y);
			return 1;
		}
	}
	return 0;
}

/*
 * Arguments: Index (number)
 * Returns: [string]
 */
static int
plsql_ide_TabInfo (lua_State *L)
{
	IDE_TabInfo func = (IDE_TabInfo) PLSQL_FUNC[148];

	if (func) {
		const int i = luaL_checkint(L, 1);

		lua_pushstring(L, func(i));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Index (number)
 * Returns: [number]
 */
static int
plsql_ide_TabIndex (lua_State *L)
{
	IDE_TabIndex func = (IDE_TabIndex) PLSQL_FUNC[149];

	if (func) {
		const int i = luaL_checkint(L, 1);

		lua_pushinteger(L, func(i));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Index (number), Name (string), BitmapFile (string)
 */
static int
plsql_ide_CreateToolButton (lua_State *L)
{
	IDE_CreateToolButton func = (IDE_CreateToolButton) PLSQL_FUNC[150];

	if (func) {
		const int i = luaL_checkint(L, 1);
		const char *name = luaL_checkstring(L, 2);
		const char *path = luaL_checkstring(L, 3);

		func(g_PlugInId, PLSQL_MENU[i], name, path, -1);
	}
	return 0;
}

/*
 * Arguments: CodeEditor (boolean)
 * Returns: [boolean]
 */
static int
plsql_ide_WindowHasEditor (lua_State *L)
{
	IDE_WindowHasEditor func = (IDE_WindowHasEditor) PLSQL_FUNC[153];

	if (func) {
		const int code = lua_toboolean(L, 1);

		lua_pushboolean(L, func(code));
		return 1;
	}
	return 0;
}

/*
 * Returns: [number]
 */
static int
plsql_ide_BeautifierOptions (lua_State *L)
{
	IDE_BeautifierOptions func = (IDE_BeautifierOptions) PLSQL_FUNC[160];

	if (func) {
		lua_pushinteger(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [boolean]
 */
static int
plsql_ide_BeautifyWindow (lua_State *L)
{
	IDE_BeautifyWindow func = (IDE_BeautifyWindow) PLSQL_FUNC[161];

	if (func) {
		lua_pushboolean(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Text (string)
 * Returns: [string]
 */
static int
plsql_ide_BeautifyText (lua_State *L)
{
	IDE_BeautifyText func = (IDE_BeautifyText) PLSQL_FUNC[162];

	if (func) {
		const char *text = luaL_checkstring(L, 1);

		lua_pushstring(L, func(text));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Action (string), ObjectType (string), ObjectOwner (string), ObjectName (string)
 * Returns: [boolean]
 */
static int
plsql_ide_ObjectAction (lua_State *L)
{
	IDE_ObjectAction func = (IDE_ObjectAction) PLSQL_FUNC[165];

	if (func) {
		const char *action = luaL_checkstring(L, 1);
		const char *type = luaL_checkstring(L, 2);
		const char *owner = luaL_checkstring(L, 3);
		const char *name = luaL_checkstring(L, 4);

		lua_pushboolean(L, func(action, type, owner, name));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Dialog (string), [Param (string)]
 * Returns: [boolean]
 */
static int
plsql_ide_ShowDialog (lua_State *L)
{
	IDE_ShowDialog func = (IDE_ShowDialog) PLSQL_FUNC[166];

	if (func) {
		const char *dlg = luaL_checkstring(L, 1);
		const char *par = lua_tostring(L, 2);

		lua_pushboolean(L, func(dlg, par));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Message (string)
 * Returns: [boolean]
 */
static int
plsql_ide_DebugLog (lua_State *L)
{
	IDE_DebugLog func = (IDE_DebugLog) PLSQL_FUNC[173];

	if (func) {
		const char *msg = luaL_checkstring(L, 1);

		func(msg);
	}
	return 0;
}

/*
 * Arguments: Name (string)
 * Returns: [string]
 */
static int
plsql_ide_GetParamString (lua_State *L)
{
	IDE_GetParamString func = (IDE_GetParamString) PLSQL_FUNC[174];

	if (func) {
		const char *name = luaL_checkstring(L, 1);

		lua_pushstring(L, func(name));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Name (string)
 * Returns: [boolean]
 */
static int
plsql_ide_GetParamBool (lua_State *L)
{
	IDE_GetParamBool func = (IDE_GetParamBool) PLSQL_FUNC[175];

	if (func) {
		const char *name = luaL_checkstring(L, 1);

		lua_pushboolean(L, func(name));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Index (number)
 * Returns: [Name (string), WhereClause (string), OrderByClause (string),
 *	User (string), Active (boolean)]
 */
static int
plsql_ide_GetBrowserFilter (lua_State *L)
{
	IDE_GetBrowserFilter func = (IDE_GetBrowserFilter) PLSQL_FUNC[176];

	if (func) {
		const int i = luaL_checkint(L, 1);
		char *name, *where, *order, *user;
		int active;

		func(i, &name, &where, &order, &user, &active);
		lua_pushstring(L, name);
		lua_pushstring(L, where);
		lua_pushstring(L, order);
		lua_pushstring(L, user);
		lua_pushboolean(L, active);
		return 5;
	}
	return 0;
}

/*
 * Arguments: FeedbackHandle (number), Text (string)
 */
static int
plsql_ide_CommandFeedback (lua_State *L)
{
	IDE_CommandFeedback func = (IDE_CommandFeedback) PLSQL_FUNC[180];

	if (func) {
		const int feedback = luaL_checkint(L, 1);
		const char *text = luaL_checkstring(L, 2);

		func(feedback, text);
	}
	return 0;
}

/*
 * Returns: [number]
 */
static int
plsql_ide_ResultGridRowCount (lua_State *L)
{
	IDE_ResultGridRowCount func = (IDE_ResultGridRowCount) PLSQL_FUNC[190];

	if (func) {
		lua_pushinteger(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [number]
 */
static int
plsql_ide_ResultGridColCount (lua_State *L)
{
	IDE_ResultGridColCount func = (IDE_ResultGridColCount) PLSQL_FUNC[191];

	if (func) {
		lua_pushinteger(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Col (number), Row (number)
 * Returns: [string]
 */
static int
plsql_ide_ResultGridCell (lua_State *L)
{
	IDE_ResultGridCell func = (IDE_ResultGridCell) PLSQL_FUNC[192];

	if (func) {
		const int col = luaL_checkint(L, 1);
		const int row = luaL_checkint(L, 2);

		lua_pushstring(L, func(col, row));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Category (string), Name (string), SubName (string)
 * Returns: [boolean]
 */
static int
plsql_ide_Authorized (lua_State *L)
{
	IDE_Authorized func = (IDE_Authorized) PLSQL_FUNC[200];

	if (func) {
		const char *cat = luaL_checkstring(L, 1);
		const char *name = luaL_checkstring(L, 2);
		const char *sub = luaL_checkstring(L, 3);

		lua_pushboolean(L, func(cat, name, sub));
		return 1;
	}
	return 0;
}

/*
 * Arguments: WindowType (number), ShowErrorMessage (boolean)
 * Returns: [boolean]
 */
static int
plsql_ide_WindowAllowed (lua_State *L)
{
	IDE_WindowAllowed func = (IDE_WindowAllowed) PLSQL_FUNC[201];

	if (func) {
		const int wt = luaL_checkint(L, 1);
		const int err = lua_toboolean(L, 2);

		lua_pushboolean(L, func(wt, err));
		return 1;
	}
	return 0;
}

/*
 * Returns: [boolean]
 */
static int
plsql_ide_Authorization (lua_State *L)
{
	IDE_Authorization func = (IDE_Authorization) PLSQL_FUNC[202];

	if (func) {
		lua_pushboolean(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Category (string)
 * Returns: [string]
 */
static int
plsql_ide_AuthorizationItems (lua_State *L)
{
	IDE_AuthorizationItems func = (IDE_AuthorizationItems) PLSQL_FUNC[203];

	if (func) {
		const char *cat = luaL_checkstring(L, 1);

		lua_pushstring(L, func(cat));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Name (string)
 */
static int
plsql_ide_AddAuthorizationItem (lua_State *L)
{
	IDE_AddAuthorizationItem func = (IDE_AddAuthorizationItem) PLSQL_FUNC[204];

	if (func) {
		const char *name = luaL_checkstring(L, 1);

		func(g_PlugInId, name);
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_GetPersonalPrefSets (lua_State *L)
{
	IDE_GetPersonalPrefSets func = (IDE_GetPersonalPrefSets) PLSQL_FUNC[210];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_ide_GetDefaultPrefSets (lua_State *L)
{
	IDE_GetDefaultPrefSets func = (IDE_GetDefaultPrefSets) PLSQL_FUNC[211];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: PrefSet (string), Name (string), Default (string)
 * Returns: [string]
 */
static int
plsql_ide_GetPrefAsString (lua_State *L)
{
	IDE_GetPrefAsString func = (IDE_GetPrefAsString) PLSQL_FUNC[212];

	if (func) {
		const char *pref = luaL_checkstring(L, 1);
		const char *name = luaL_checkstring(L, 2);
		const char *def = luaL_checkstring(L, 3);

		lua_pushstring(L, func(g_PlugInId, pref, name, def));
		return 1;
	}
	return 0;
}

/*
 * Arguments: PrefSet (string), Name (string), Default (number)
 * Returns: [number]
 */
static int
plsql_ide_GetPrefAsInteger (lua_State *L)
{
	IDE_GetPrefAsInteger func = (IDE_GetPrefAsInteger) PLSQL_FUNC[213];

	if (func) {
		const char *pref = luaL_checkstring(L, 1);
		const char *name = luaL_checkstring(L, 2);
		const int def = luaL_checkint(L, 3);

		lua_pushinteger(L, func(g_PlugInId, pref, name, def));
		return 1;
	}
	return 0;
}

/*
 * Arguments: PrefSet (string), Name (string), Default (boolean)
 * Returns: [boolean]
 */
static int
plsql_ide_GetPrefAsBool (lua_State *L)
{
	IDE_GetPrefAsBool func = (IDE_GetPrefAsBool) PLSQL_FUNC[214];

	if (func) {
		const char *pref = luaL_checkstring(L, 1);
		const char *name = luaL_checkstring(L, 2);
		const BOOL def = lua_toboolean(L, 3);

		lua_pushboolean(L, func(g_PlugInId, pref, name, def));
		return 1;
	}
	return 0;
}

/*
 * Arguments: PrefSet (string), Name (string), Value (string)
 * Returns: [boolean]
 */
static int
plsql_ide_SetPrefAsString (lua_State *L)
{
	IDE_SetPrefAsString func = (IDE_SetPrefAsString) PLSQL_FUNC[215];

	if (func) {
		const char *pref = luaL_checkstring(L, 1);
		const char *name = luaL_checkstring(L, 2);
		const char *val = luaL_checkstring(L, 3);

		lua_pushboolean(L, func(g_PlugInId, pref, name, val));
		return 1;
	}
	return 0;
}

/*
 * Arguments: PrefSet (string), Name (string), Value (number)
 * Returns: [boolean]
 */
static int
plsql_ide_SetPrefAsInteger (lua_State *L)
{
	IDE_SetPrefAsInteger func = (IDE_SetPrefAsInteger) PLSQL_FUNC[216];

	if (func) {
		const char *pref = luaL_checkstring(L, 1);
		const char *name = luaL_checkstring(L, 2);
		const int val = luaL_checkint(L, 3);

		lua_pushboolean(L, func(g_PlugInId, pref, name, val));
		return 1;
	}
	return 0;
}

/*
 * Arguments: PrefSet (string), Name (string), Value (boolean)
 * Returns: [boolean]
 */
static int
plsql_ide_SetPrefAsBool (lua_State *L)
{
	IDE_SetPrefAsBool func = (IDE_SetPrefAsBool) PLSQL_FUNC[217];

	if (func) {
		const char *pref = luaL_checkstring(L, 1);
		const char *name = luaL_checkstring(L, 2);
		const int val = lua_toboolean(L, 3);

		lua_pushboolean(L, func(g_PlugInId, pref, name, val));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Name (string)
 * Returns: [string]
 */
static int
plsql_ide_GetGeneralPref (lua_State *L)
{
	IDE_GetGeneralPref func = (IDE_GetGeneralPref) PLSQL_FUNC[218];

	if (func) {
		const char *name = luaL_checkstring(L, 1);

		lua_pushstring(L, func(name));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Setting (string), Value (boolean)
 * Returns: [boolean]
 */
static int
plsql_ide_PlugInSetting (lua_State *L)
{
	IDE_PlugInSetting func = (IDE_PlugInSetting) PLSQL_FUNC[219];

	if (func) {
		const char *setting = luaL_checkstring(L, 1);
		const char *val = luaL_checkstring(L, 2);

		lua_pushboolean(L, func(g_PlugInId, setting, val));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Owner (string), PackageName (string), ProcedureName (string)
 * Returns: [number]
 */
static int
plsql_ide_GetProcOverloadCount (lua_State *L)
{
	IDE_GetProcOverloadCount func = (IDE_GetProcOverloadCount) PLSQL_FUNC[220];

	if (func) {
		const char *owner = luaL_checkstring(L, 1);
		const char *pkg = luaL_checkstring(L, 2);
		const char *proc = luaL_checkstring(L, 3);

		lua_pushinteger(L, func(owner, pkg, proc));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Owner (string), PackageName (string), ProcedureName (string)
 * Returns: [number]
 */
static int
plsql_ide_SelectProcOverloading (lua_State *L)
{
	IDE_SelectProcOverloading func = (IDE_SelectProcOverloading) PLSQL_FUNC[221];

	if (func) {
		const char *owner = luaL_checkstring(L, 1);
		const char *pkg = luaL_checkstring(L, 2);
		const char *proc = luaL_checkstring(L, 3);

		lua_pushinteger(L, func(owner, pkg, proc));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Name (string)
 * Returns: [string]
 */
static int
plsql_ide_GetSessionValue (lua_State *L)
{
	IDE_GetSessionValue func = (IDE_GetSessionValue) PLSQL_FUNC[230];

	if (func) {
		const char *name = luaL_checkstring(L, 1);

		lua_pushstring(L, func(name));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Version (boolean)
 * Returns: [boolean]
 */
static int
plsql_ide_CheckDBVersion (lua_State *L)
{
	IDE_CheckDBVersion func = (IDE_CheckDBVersion) PLSQL_FUNC[231];

	if (func) {
		const char *ver = luaL_checkstring(L, 1);

		lua_pushboolean(L, func(ver));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Index (number)
 * Returns: [Username (string), Password (string),
 *	Database (string), ConnectAs (string),
 *	Edition (string), Workspace (string)]
 */
static int
plsql_ide_GetConnectionInfoEx (lua_State *L)
{
	IDE_GetConnectionInfoEx func = (IDE_GetConnectionInfoEx) PLSQL_FUNC[240];
	IDE_GetConnectionInfoEx10 func10 = (IDE_GetConnectionInfoEx10) PLSQL_FUNC[250];

	if (func10 || func) {
		const int ix = luaL_checkint(L, 1);
		char *usr, *pwd, *db, *role;
		char *edt = NULL, *wspc = NULL;

		if (func10 ? func10(ix, &usr, &pwd, &db, &role, &edt, &wspc)
		 : func(ix, &usr, &pwd, &db, &role)) {
			lua_pushstring(L, usr);
			lua_pushstring(L, pwd);
			lua_pushstring(L, db);
			lua_pushstring(L, role);
			lua_pushstring(L, edt);
			lua_pushstring(L, wspc);
			return 6;
		}
	}
	return 0;
}

/*
 * Arguments: Username (string), Database (string),
 *	Edition (string), Workspace (string)
 * Returns: [Index (number)]
 */
static int
plsql_ide_FindConnection (lua_State *L)
{
	IDE_FindConnection func = (IDE_FindConnection) PLSQL_FUNC[241];
	IDE_FindConnectionEx10 func10 = (IDE_FindConnectionEx10) PLSQL_FUNC[251];

	if (func10 || func) {
		const char *usr = luaL_checkstring(L, 1);
		const char *db = luaL_checkstring(L, 2);
		const char *edt = func10 ? luaL_checkstring(L, 3) : NULL;
		const char *wspc = func10 ? luaL_checkstring(L, 4) : NULL;
		const int ix = func10 ? func10(usr, db, edt, wspc)
		 : func(usr, db);

		if (ix != -1) {
			lua_pushinteger(L, ix);
			return 1;
		}
	}
	return 0;
}

/*
 * Arguments: Username (string), Password (string),
 *	Database (string), ConnectAs (string),
 *	Edition (string), Workspace (string)
 * Returns: Index (number)
 */
static int
plsql_ide_AddConnection (lua_State *L)
{
	IDE_AddConnection func = (IDE_AddConnection) PLSQL_FUNC[242];
	IDE_AddConnectionEx10 func10 = (IDE_AddConnectionEx10) PLSQL_FUNC[252];

	if (func10 || func) {
		const char *usr = luaL_checkstring(L, 1);
		const char *pwd = luaL_checkstring(L, 2);
		const char *db = luaL_checkstring(L, 3);
		const char *role = luaL_checkstring(L, 4);
		const char *edt = func10 ? luaL_checkstring(L, 5) : NULL;
		const char *wspc = func10 ? luaL_checkstring(L, 6) : NULL;
		const int ix = func10 ? func10(usr, pwd, db, role, edt, wspc)
		 : func(usr, pwd, db, role);

		if (ix != -1) {
			lua_pushinteger(L, ix);
			return 1;
		}
	}
	return 0;
}

/*
 * Arguments: Index (number)
 * Returns: [boolean]
 */
static int
plsql_ide_ConnectConnection (lua_State *L)
{
	IDE_ConnectConnection func = (IDE_ConnectConnection) PLSQL_FUNC[243];

	if (func) {
		const int ix = luaL_checkint(L, 1);

		lua_pushboolean(L, func(ix));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Index (number)
 * Returns: [boolean]
 */
static int
plsql_ide_SetMainConnection (lua_State *L)
{
	IDE_SetMainConnection func = (IDE_SetMainConnection) PLSQL_FUNC[244];

	if (func) {
		const int ix = luaL_checkint(L, 1);

		lua_pushboolean(L, func(ix));
		return 1;
	}
	return 0;
}

/*
 * Returns: [Index (number)]
 */
static int
plsql_ide_GetWindowConnection (lua_State *L)
{
	IDE_GetWindowConnection func = (IDE_GetWindowConnection) PLSQL_FUNC[245];

	if (func) {
		lua_pushinteger(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Index (number)
 * Returns: [boolean]
 */
static int
plsql_ide_SetWindowConnection (lua_State *L)
{
	IDE_SetWindowConnection func = (IDE_SetWindowConnection) PLSQL_FUNC[246];

	if (func) {
		const int ix = luaL_checkint(L, 1);

		lua_pushboolean(L, func(ix));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Index (number)
 * Returns: [Description (string), Username (string), Password (string),
 *	Database (string), ConnectAs (string),
 *	Edition (string), Workspace (string),
 *	ID (number), ParentID (number)]
 */
static int
plsql_ide_GetConnectionTree (lua_State *L)
{
	IDE_GetConnectionTree func = (IDE_GetConnectionTree) PLSQL_FUNC[247];
	IDE_GetConnectionTreeEx10 func10 = (IDE_GetConnectionTreeEx10) PLSQL_FUNC[253];

	if (func10 || func) {
		const int ix = luaL_checkint(L, 1);
		char *descr, *usr, *pwd, *db, *role;
		char *edt = NULL, *wspc = NULL;
		int id, pid;

		if (func10 ? func10(ix, &descr, &usr, &pwd, &db, &role, &edt, &wspc, &id, &pid)
		 : func(ix, &descr, &usr, &pwd, &db, &role, &id, &pid)) {
			lua_pushstring(L, descr);
			lua_pushstring(L, usr);
			lua_pushstring(L, pwd);
			lua_pushstring(L, db);
			lua_pushstring(L, role);
			lua_pushstring(L, edt);
			lua_pushstring(L, wspc);
			lua_pushinteger(L, id);
			lua_pushinteger(L, pid);
			return 9;
		}
	}
	return 0;
}


/*
 * Arguments: action (number)
 */
static int
plsql_ide_SetWindowCloseAction (lua_State *L)
{
	g_WindowCloseAction = luaL_checkint(L, 1);
	return 0;
}

/*
 * Returns: number
 */
static int
plsql_ide_GetWindowCloseAction (lua_State *L)
{
	lua_pushinteger(L, g_WindowCloseAction);
	return 1;
}

/*
 * Returns: boolean
 */
static int
plsql_ide_UseRibbonMenu (lua_State *L)
{
	lua_pushboolean(L, g_UseRibbonMenu);
	return 1;
}

/*
 * Arguments: text (string)
 */
static int
plsql_ide_InsertText (lua_State *L)
{
	const HWND hwnd = ((IDE_GetEditorHandle) PLSQL_FUNC[33])();
	const char *s = luaL_checkstring(L, 1);

	SendMessage(hwnd, EM_REPLACESEL, (WPARAM) TRUE, (LPARAM) s);
	return 0;
}

/*
 * Returns: number
 */
static int
plsql_ide_GetFirstVisibleLine (lua_State *L)
{
	const HWND hwnd = ((IDE_GetEditorHandle) PLSQL_FUNC[33])();

	lua_pushinteger(L, SendMessage(hwnd, EM_GETFIRSTVISIBLELINE, 0, 0));
	return 1;
}

/*
 * Returns: number
 */
static int
plsql_ide_GetLineCount (lua_State *L)
{
	const HWND hwnd = ((IDE_GetEditorHandle) PLSQL_FUNC[33])();

	lua_pushinteger(L, SendMessage(hwnd, EM_GETLINECOUNT, 0, 0));
	return 1;
}

/*
 * Arguments: StartPosition (number), EndPosition (number)
 */
static int
plsql_ide_SetSelection (lua_State *L)
{
	const HWND hwnd = ((IDE_GetEditorHandle) PLSQL_FUNC[33])();
	const int start = (int) lua_tointeger(L, 1);
	const int end = (int) lua_tointeger(L, 2);
	CHARRANGE range;

	range.cpMin = start;
	range.cpMax = (end != -1 || start == -1) ? end
		: ((unsigned int) -1 >> 1);
	SendMessage(hwnd, EM_EXSETSEL, 0, (LPARAM) &range);
	return 0;
}

/*
 * Returns: StartPosition (number), EndPosition (number)
 */
static int
plsql_ide_GetSelection (lua_State *L)
{
	const HWND hwnd = ((IDE_GetEditorHandle) PLSQL_FUNC[33])();
	CHARRANGE range;

	SendMessage(hwnd, EM_EXGETSEL, 0, (LPARAM) &range);
	lua_pushinteger(L, range.cpMin);
	lua_pushinteger(L, range.cpMax);
	return 2;
}

/*
 * Arguments: Position (number)
 * Returns: number
 */
static int
plsql_ide_LineFromChar (lua_State *L)
{
	const HWND hwnd = ((IDE_GetEditorHandle) PLSQL_FUNC[33])();
	const int pos = (int) lua_tointeger(L, 1);

	lua_pushinteger(L, SendMessage(hwnd, EM_EXLINEFROMCHAR, 0, pos));
	return 1;
}

/*
 * Arguments: Line (number)
 * Returns: number
 */
static int
plsql_ide_LineIndex (lua_State *L)
{
	const HWND hwnd = ((IDE_GetEditorHandle) PLSQL_FUNC[33])();
	const int line = (int) lua_tointeger(L, 1);

	lua_pushinteger(L, SendMessage(hwnd, EM_LINEINDEX, line, 0));
	return 1;
}

/*
 * Arguments: Position (number)
 * Returns: number
 */
static int
plsql_ide_LineLength (lua_State *L)
{
	const HWND hwnd = ((IDE_GetEditorHandle) PLSQL_FUNC[33])();
	const int pos = (int) lua_tointeger(L, 1);

	lua_pushinteger(L, SendMessage(hwnd, EM_LINELENGTH, pos, 0));
	return 1;
}

/*
 * Arguments: XOffset (number), YOffset (number)
 * Returns: number
 */
static int
plsql_ide_LineScroll (lua_State *L)
{
	const HWND hwnd = ((IDE_GetEditorHandle) PLSQL_FUNC[33])();
	const int x_off = (int) lua_tointeger(L, 1);
	const int y_off = (int) lua_tointeger(L, 2);

	SendMessage(hwnd, EM_LINESCROLL, x_off, y_off);
	return 0;
}

static int
plsql_ide_Undo (lua_State *L)
{
	const HWND hwnd = ((IDE_GetEditorHandle) PLSQL_FUNC[33])();

	SendMessage(hwnd, EM_UNDO, 0, 0);
	return 0;
}

static int
plsql_ide_EmptyUndoBuffer (lua_State *L)
{
	const HWND hwnd = ((IDE_GetEditorHandle) PLSQL_FUNC[33])();

	SendMessage(hwnd, EM_EMPTYUNDOBUFFER, 0, 0);
	return 0;
}


static luaL_Reg plsql_idelib[] = {
    {"MenuState",		plsql_ide_MenuState},
    {"Connected",		plsql_ide_Connected},
    {"GetConnectionInfo",	plsql_ide_GetConnectionInfo},
    {"GetBrowserInfo",		plsql_ide_GetBrowserInfo},
    {"GetWindowType",		plsql_ide_GetWindowType},
    {"GetAppHandle",		plsql_ide_GetAppHandle},
    {"GetWindowHandle",		plsql_ide_GetWindowHandle},
    {"GetClientHandle",		plsql_ide_GetClientHandle},
    {"GetChildHandle",		plsql_ide_GetChildHandle},
    {"Refresh",			plsql_ide_Refresh},
    {"CreateWindow",		plsql_ide_CreateWindow},
    {"OpenFile",		plsql_ide_OpenFile},
    {"SaveFile",		plsql_ide_SaveFile},
    {"Filename",		plsql_ide_Filename},
    {"CloseFile",		plsql_ide_CloseFile},
    {"SetReadOnly",		plsql_ide_SetReadOnly},
    {"GetReadOnly",		plsql_ide_GetReadOnly},
    {"ExecuteSQLReport",	plsql_ide_ExecuteSQLReport},
    {"ReloadFile",		plsql_ide_ReloadFile},
    {"SetFilename",		plsql_ide_SetFilename},
    {"GetText",			plsql_ide_GetText},
    {"GetSelectedText",		plsql_ide_GetSelectedText},
    {"GetCursorWord",		plsql_ide_GetCursorWord},
    {"GetEditorHandle",		plsql_ide_GetEditorHandle},
    {"SetText",			plsql_ide_SetText},
    {"SetStatusMessage",	plsql_ide_SetStatusMessage},
    {"SetErrorPosition",	plsql_ide_SetErrorPosition},
    {"ClearErrorPositions",	plsql_ide_ClearErrorPositions},
    {"GetCursorWordPosition",	plsql_ide_GetCursorWordPosition},
    {"Perform",			plsql_ide_Perform},
    {"GetCustomKeywords",	plsql_ide_GetCustomKeywords},
    {"SetCustomKeywords",	plsql_ide_SetCustomKeywords},
    {"SetKeywords",		plsql_ide_SetKeywords},
    {"ActivateKeywords",	plsql_ide_ActivateKeywords},
    {"RefreshMenus",		plsql_ide_RefreshMenus},
    {"SetMenuName",		plsql_ide_SetMenuName},
    {"SetMenuCheck",		plsql_ide_SetMenuCheck},
    {"SetMenuVisible",		plsql_ide_SetMenuVisible},
    {"GetMenulayout",		plsql_ide_GetMenulayout},
    {"CreatePopupItem",		plsql_ide_CreatePopupItem},
    {"SetConnection",		plsql_ide_SetConnection},
    {"GetObjectInfo",		plsql_ide_GetObjectInfo},
    {"GetBrowserItems",		plsql_ide_GetBrowserItems},
    {"RefreshBrowser",		plsql_ide_RefreshBrowser},
    {"GetPopupObject",		plsql_ide_GetPopupObject},
    {"GetPopupBrowserRoot",	plsql_ide_GetPopupBrowserRoot},
    {"RefreshObject",		plsql_ide_RefreshObject},
    {"FirstSelectedObject",	plsql_ide_FirstSelectedObject},
    {"NextSelectedObject",	plsql_ide_NextSelectedObject},
    {"GetObjectSource",		plsql_ide_GetObjectSource},
    {"GetWindowCount",		plsql_ide_GetWindowCount},
    {"SelectWindow",		plsql_ide_SelectWindow},
    {"ActivateWindow",		plsql_ide_ActivateWindow},
    {"IsWindowModified",	plsql_ide_IsWindowModified},
    {"IsWindowRunning",		plsql_ide_IsWindowRunning},
    {"WindowPin",		plsql_ide_WindowPin},
    {"SplashCreate",		plsql_ide_SplashCreate},
    {"SplashHide",		plsql_ide_SplashHide},
    {"SplashWrite",		plsql_ide_SplashWrite},
    {"SplashWriteLn",		plsql_ide_SplashWriteLn},
    {"SplashProgress",		plsql_ide_SplashProgress},
    {"TemplatePath",		plsql_ide_TemplatePath},
    {"ExecuteTemplate",		plsql_ide_ExecuteTemplate},
    {"GetConnectAs",		plsql_ide_GetConnectAs},
    {"SetConnectionAs",		plsql_ide_SetConnectionAs},
    {"GetFileOpenMenu",		plsql_ide_GetFileOpenMenu},
    {"CanSaveWindow",		plsql_ide_CanSaveWindow},
    {"OpenFileExternal",	plsql_ide_OpenFileExternal},
    {"GetFileTypes",		plsql_ide_GetFileTypes},
    {"GetDefaultExtension",	plsql_ide_GetDefaultExtension},
    {"GetFileData",		plsql_ide_GetFileData},
    {"FileSaved",		plsql_ide_FileSaved},
    {"ShowHTML",		plsql_ide_ShowHTML},
    {"RefreshHTML",		plsql_ide_RefreshHTML},
    {"GetProcEditExtension",	plsql_ide_GetProcEditExtension},
    {"GetWindowObject",		plsql_ide_GetWindowObject},
    {"FirstSelectedFile",	plsql_ide_FirstSelectedFile},
    {"NextSelectedFile",	plsql_ide_NextSelectedFile},
    {"RefreshFileBrowser",	plsql_ide_RefreshFileBrowser},
    {"KeyPress",		plsql_ide_KeyPress},
    {"GetMenuItem",		plsql_ide_GetMenuItem},
    {"SelectMenu",		plsql_ide_SelectMenu},
    {"TranslationFile",		plsql_ide_TranslationFile},
    {"TranslationLanguage",	plsql_ide_TranslationLanguage},
    {"GetTranslatedMenuLayout",	plsql_ide_GetTranslatedMenuLayout},
    {"MainFont",		plsql_ide_MainFont},
    {"TranslateItems",		plsql_ide_TranslateItems},
    {"TranslateString",		plsql_ide_TranslateString},
    {"SaveRecoveryFiles",	plsql_ide_SaveRecoveryFiles},
    {"GetCursorX",		plsql_ide_GetCursorX},
    {"GetCursorY",		plsql_ide_GetCursorY},
    {"SetCursor",		plsql_ide_SetCursor},
    {"SetBookmark",		plsql_ide_SetBookmark},
    {"ClearBookmark",		plsql_ide_ClearBookmark},
    {"GotoBookmark",		plsql_ide_GotoBookmark},
    {"GetBookmark",		plsql_ide_GetBookmark},
    {"TabInfo",			plsql_ide_TabInfo},
    {"TabIndex",		plsql_ide_TabIndex},
    {"CreateToolButton",	plsql_ide_CreateToolButton},
    {"WindowHasEditor",		plsql_ide_WindowHasEditor},
    {"BeautifierOptions",	plsql_ide_BeautifierOptions},
    {"BeautifyWindow",		plsql_ide_BeautifyWindow},
    {"BeautifyText",		plsql_ide_BeautifyText},
    {"ObjectAction",		plsql_ide_ObjectAction},
    {"ShowDialog",		plsql_ide_ShowDialog},
    {"DebugLog",		plsql_ide_DebugLog},
    {"GetParamString",		plsql_ide_GetParamString},
    {"GetParamBool",		plsql_ide_GetParamBool},
    {"GetBrowserFilter",	plsql_ide_GetBrowserFilter},
    {"CommandFeedback",		plsql_ide_CommandFeedback},
    {"ResultGridRowCount",	plsql_ide_ResultGridRowCount},
    {"ResultGridColCount",	plsql_ide_ResultGridColCount},
    {"ResultGridCell",		plsql_ide_ResultGridCell},
    {"Authorized",		plsql_ide_Authorized},
    {"WindowAllowed",		plsql_ide_WindowAllowed},
    {"Authorization",		plsql_ide_Authorization},
    {"AuthorizationItems",	plsql_ide_AuthorizationItems},
    {"AddAuthorizationItem",	plsql_ide_AddAuthorizationItem},
    {"GetPersonalPrefSets",	plsql_ide_GetPersonalPrefSets},
    {"GetDefaultPrefSets",	plsql_ide_GetDefaultPrefSets},
    {"GetPrefAsString",		plsql_ide_GetPrefAsString},
    {"GetPrefAsInteger",	plsql_ide_GetPrefAsInteger},
    {"GetPrefAsBool",		plsql_ide_GetPrefAsBool},
    {"SetPrefAsString",		plsql_ide_SetPrefAsString},
    {"SetPrefAsInteger",	plsql_ide_SetPrefAsInteger},
    {"SetPrefAsBool",		plsql_ide_SetPrefAsBool},
    {"GetGeneralPref",		plsql_ide_GetGeneralPref},
    {"PlugInSetting",		plsql_ide_PlugInSetting},
    {"GetProcOverloadCount",	plsql_ide_GetProcOverloadCount},
    {"SelectProcOverloading",	plsql_ide_SelectProcOverloading},
    {"GetSessionValue",		plsql_ide_GetSessionValue},
    {"CheckDBVersion",		plsql_ide_CheckDBVersion},
    {"GetConnectionInfoEx",	plsql_ide_GetConnectionInfoEx},
    {"FindConnection",		plsql_ide_FindConnection},
    {"AddConnection",		plsql_ide_AddConnection},
    {"ConnectConnection",	plsql_ide_ConnectConnection},
    {"SetMainConnection",	plsql_ide_SetMainConnection},
    {"GetWindowConnection",	plsql_ide_GetWindowConnection},
    {"SetWindowConnection",	plsql_ide_SetWindowConnection},
    {"GetConnectionTree",	plsql_ide_GetConnectionTree},
    {"SetWindowCloseAction",	plsql_ide_SetWindowCloseAction},
    {"GetWindowCloseAction",	plsql_ide_GetWindowCloseAction},
    {"UseRibbonMenu",		plsql_ide_UseRibbonMenu},
    {"InsertText",		plsql_ide_InsertText},
    {"GetFirstVisibleLine",	plsql_ide_GetFirstVisibleLine},
    {"GetLineCount",		plsql_ide_GetLineCount},
    {"SetSelection",		plsql_ide_SetSelection},
    {"GetSelection",		plsql_ide_GetSelection},
    {"LineFromChar",		plsql_ide_LineFromChar},
    {"LineIndex",		plsql_ide_LineIndex},
    {"LineLength",		plsql_ide_LineLength},
    {"LineScroll",		plsql_ide_LineScroll},
    {"Undo",			plsql_ide_Undo},
    {"EmptyUndoBuffer",		plsql_ide_EmptyUndoBuffer},
    {NULL, NULL}
};
