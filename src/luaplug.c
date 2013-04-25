/* PL/SQL Developer Lua Plug-In: Proxy DLL */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

#include "luaplsql.h"


#define PLUGIN_DLL_NAME	"luaplsql.dll"

/* Exported functions */
typedef PLUGIN_API char *(*tPlugInShortName)(void);
typedef PLUGIN_API char *(*tIdentifyPlugIn)(int id);
typedef PLUGIN_API void (*tOnCreate)(void);
typedef PLUGIN_API void (*tOnDestroy)(void);
typedef PLUGIN_API void (*tRegisterCallback)(int i, PLSQL_Function func);
typedef PLUGIN_API void (*tOnActivate)(void);
typedef PLUGIN_API void (*tOnDeactivate)(void);
typedef PLUGIN_API const char *(*tCreateMenuItem)(int i);
typedef PLUGIN_API void (*tOnMenuClick)(int i);
typedef PLUGIN_API BOOL (*tCanClose)(void);
typedef PLUGIN_API void (*tAfterStart)(void);
typedef PLUGIN_API void (*tOnBrowserChange)(void);
typedef PLUGIN_API void (*tOnWindowChange)(void);
typedef PLUGIN_API void (*tOnWindowCreate)(int win_type);
typedef PLUGIN_API void (*tOnWindowCreated)(int win_type);
typedef PLUGIN_API int (*tOnWindowClose)(int win_type, BOOL changed);
typedef PLUGIN_API BOOL (*tBeforeExecuteWindow)(int win_type);
typedef PLUGIN_API void (*tAfterExecuteWindow)(int win_type, int result);
typedef PLUGIN_API void (*tOnConnectionChange)(void);
typedef PLUGIN_API void (*tOnWindowConnectionChange)(void);
typedef PLUGIN_API void (*tOnPopup)(char *obj_type, char *obj_name);
typedef PLUGIN_API void (*tOnMainMenu)(char *menu_name);
typedef PLUGIN_API BOOL (*tOnTemplate)(char *filename, const char **data);
typedef PLUGIN_API void (*tOnFileLoaded)(int win_type, int mode);
typedef PLUGIN_API void (*tOnFileSaved)(int win_type, int mode);
typedef PLUGIN_API const char *(*tAbout)(void);
typedef PLUGIN_API void (*tCommandLine)(int handle, char *command, char *params);
typedef PLUGIN_API const char *(*tRegisterExport)(void);
typedef PLUGIN_API BOOL (*tExportInit)(void);
typedef PLUGIN_API void (*tExportFinished)(void);
typedef PLUGIN_API BOOL (*tExportPrepare)(void);
typedef PLUGIN_API BOOL (*tExportData)(char *value);

static tPlugInShortName			vPlugInShortName;
static tIdentifyPlugIn			vIdentifyPlugIn;
static tOnCreate			vOnCreate;
static tOnDestroy			vOnDestroy;
static tRegisterCallback		vRegisterCallback;
static tOnActivate			vOnActivate;
static tOnDeactivate			vOnDeactivate;
static tCreateMenuItem			vCreateMenuItem;
static tOnMenuClick			vOnMenuClick;
static tCanClose			vCanClose;
static tAfterStart			vAfterStart;
static tOnBrowserChange			vOnBrowserChange;
static tOnWindowChange			vOnWindowChange;
static tOnWindowCreate			vOnWindowCreate;
static tOnWindowCreated			vOnWindowCreated;
static tOnWindowClose			vOnWindowClose;
static tBeforeExecuteWindow		vBeforeExecuteWindow;
static tAfterExecuteWindow		vAfterExecuteWindow;
static tOnConnectionChange		vOnConnectionChange;
static tOnWindowConnectionChange	vOnWindowConnectionChange;
static tOnPopup				vOnPopup;
static tOnMainMenu			vOnMainMenu;
static tOnTemplate			vOnTemplate;
static tOnFileLoaded			vOnFileLoaded;
static tOnFileSaved			vOnFileSaved;
static tAbout				vAbout;
static tCommandLine			vCommandLine;
static tRegisterExport			vRegisterExport;
static tExportInit			vExportInit;
static tExportFinished			vExportFinished;
static tExportPrepare			vExportPrepare;
static tExportData			vExportData;

/* Global Lua DLL Handle */
static HINSTANCE g_DLLHandle;


BOOL WINAPI
DllMain (HANDLE hmodule, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH) {
		char env[16384];
		char path[2 * MAX_PATH];
		int n = GetModuleFileName(hmodule, &path[1], MAX_PATH);
		char *sep;

		if (!n) return FALSE;

		path[0] = ';';
		path[++n] = '\0';
		sep = strrchr(path, '\\');
		if (sep)
			*sep = '\0';
		else
			sep = &path[n];
		strcat(sep, "\\lua");
		SetEnvironmentVariable(PLUGIN_ENV, &path[1]);

		GetEnvironmentVariable("PATH", env, sizeof(env));
		strcat(sep, "\\clibs");
		strcat(env, path);
		SetEnvironmentVariable("PATH", env);
	}
	return TRUE;
}

static void
load_library (void)
{
	if (g_DLLHandle) return;

	g_DLLHandle = LoadLibrary(PLUGIN_DLL_NAME);
	if (!g_DLLHandle) return;

	vPlugInShortName = (tPlugInShortName) GetProcAddress(g_DLLHandle, "PlugInShortName");
	vIdentifyPlugIn = (tIdentifyPlugIn) GetProcAddress(g_DLLHandle, "IdentifyPlugIn");
	vOnCreate = (tOnCreate) GetProcAddress(g_DLLHandle, "OnCreate");
	vOnDestroy = (tOnDestroy) GetProcAddress(g_DLLHandle, "OnDestroy");
	vRegisterCallback = (tRegisterCallback) GetProcAddress(g_DLLHandle, "RegisterCallback");
	vOnActivate = (tOnActivate) GetProcAddress(g_DLLHandle, "OnActivate");
	vOnDeactivate = (tOnDeactivate) GetProcAddress(g_DLLHandle,"OnDeactivate");
	vCreateMenuItem = (tCreateMenuItem) GetProcAddress(g_DLLHandle,"CreateMenuItem");
	vOnMenuClick = (tOnMenuClick) GetProcAddress(g_DLLHandle, "OnMenuClick");
	vCanClose = (tCanClose) GetProcAddress(g_DLLHandle, "CanClose");
	vAfterStart = (tAfterStart) GetProcAddress(g_DLLHandle, "AfterStart");
	vOnBrowserChange = (tOnBrowserChange) GetProcAddress(g_DLLHandle, "OnBrowserChange");
	vOnWindowChange = (tOnWindowChange) GetProcAddress(g_DLLHandle, "OnWindowChange");
	vOnWindowCreate = (tOnWindowCreate) GetProcAddress(g_DLLHandle, "OnWindowCreate");
	vOnWindowCreated = (tOnWindowCreated) GetProcAddress(g_DLLHandle, "OnWindowCreated");
	vOnWindowClose = (tOnWindowClose) GetProcAddress(g_DLLHandle, "OnWindowClose");
	vBeforeExecuteWindow = (tBeforeExecuteWindow) GetProcAddress(g_DLLHandle, "BeforeExecuteWindow");
	vAfterExecuteWindow = (tAfterExecuteWindow) GetProcAddress(g_DLLHandle, "AfterExecuteWindow");
	vOnConnectionChange = (tOnConnectionChange) GetProcAddress(g_DLLHandle, "OnConnectionChange");
	vOnWindowConnectionChange = (tOnWindowConnectionChange) GetProcAddress(g_DLLHandle, "OnWindowConnectionChange");
	vOnPopup = (tOnPopup) GetProcAddress(g_DLLHandle, "OnPopup");
	vOnMainMenu = (tOnMainMenu) GetProcAddress(g_DLLHandle, "OnMainMenu");
	vOnTemplate = (tOnTemplate) GetProcAddress(g_DLLHandle, "OnTemplate");
	vOnFileLoaded = (tOnFileLoaded) GetProcAddress(g_DLLHandle, "OnFileLoaded");
	vOnFileSaved = (tOnFileSaved) GetProcAddress(g_DLLHandle, "OnFileSaved");
	vAbout = (tAbout) GetProcAddress(g_DLLHandle, "About");
	vCommandLine = (tCommandLine) GetProcAddress(g_DLLHandle, "CommandLine");
	vRegisterExport = (tRegisterExport) GetProcAddress(g_DLLHandle, "RegisterExport");
	vExportInit = (tExportInit) GetProcAddress(g_DLLHandle, "ExportInit");
	vExportFinished = (tExportFinished) GetProcAddress(g_DLLHandle, "ExportFinished");
	vExportPrepare = (tExportPrepare) GetProcAddress(g_DLLHandle, "ExportPrepare");
	vExportData = (tExportData) GetProcAddress(g_DLLHandle, "ExportData");
}

static void
free_library (void)
{
	if (!g_DLLHandle) return;

	FreeLibrary(g_DLLHandle);
	g_DLLHandle = NULL;

	vPlugInShortName = NULL;
	vIdentifyPlugIn = NULL;
	vOnCreate = NULL;
	vOnDestroy = NULL;
	vRegisterCallback = NULL;
	vOnActivate = NULL;
	vOnDeactivate = NULL;
	vCreateMenuItem = NULL;
	vOnMenuClick = NULL;
	vCanClose = NULL;
	vAfterStart = NULL;
	vOnBrowserChange = NULL;
	vOnWindowChange = NULL;
	vOnWindowCreate = NULL;
	vOnWindowCreated = NULL;
	vOnWindowClose = NULL;
	vBeforeExecuteWindow = NULL;
	vAfterExecuteWindow = NULL;
	vOnConnectionChange = NULL;
	vOnWindowConnectionChange = NULL;
	vOnPopup = NULL;
	vOnMainMenu = NULL;
	vOnTemplate = NULL;
	vOnFileLoaded = NULL;
	vOnFileSaved = NULL;
	vAbout = NULL;
	vCommandLine = NULL;
	vRegisterExport = NULL;
	vExportInit = NULL;
	vExportFinished = NULL;
	vExportPrepare = NULL;
	vExportData = NULL;
}


PLUGIN_API char *
PlugInShortName (void)
{
	if (vPlugInShortName)
		return vPlugInShortName();
	return NULL;
}

PLUGIN_API char *
IdentifyPlugIn (int id)
{
	load_library();

	if (vIdentifyPlugIn)
		return vIdentifyPlugIn(id);
	return NULL;
}

PLUGIN_API void
OnCreate (void)
{
	load_library();

	if (vOnCreate)
		vOnCreate();
}

PLUGIN_API void
OnDestroy (void)
{
	if (vOnDestroy)
		vOnDestroy();

	free_library();
}

PLUGIN_API void
RegisterCallback (int i, PLSQL_Function func)
{
	if (vRegisterCallback)
		vRegisterCallback(i, func);
}

PLUGIN_API void
OnActivate (void)
{
	if (vOnActivate)
		vOnActivate();
}

PLUGIN_API void
OnDeactivate (void)
{
	if (vOnDeactivate)
		vOnDeactivate();
}

PLUGIN_API const char *
CreateMenuItem (int i)
{
	if (vCreateMenuItem)
		return vCreateMenuItem(i);
	return NULL;
}

PLUGIN_API void
OnMenuClick (int i)
{
	if (vOnMenuClick)
		vOnMenuClick(i);
}

PLUGIN_API BOOL
CanClose (void)
{
	if (vCanClose)
		return vCanClose();
	return TRUE;
}

PLUGIN_API void
AfterStart (void)
{
	if (vAfterStart)
		vAfterStart();
}

PLUGIN_API void
OnBrowserChange (void)
{
	if (vOnBrowserChange)
		vOnBrowserChange();
}

PLUGIN_API void
OnWindowChange (void)
{
	if (vOnWindowChange)
		vOnWindowChange();
}

PLUGIN_API void
OnWindowCreate (int win_type)
{
	if (vOnWindowCreate)
		vOnWindowCreate(win_type);
}

PLUGIN_API void
OnWindowCreated (int win_type)
{
	if (vOnWindowCreated)
		vOnWindowCreated(win_type);
}

PLUGIN_API int
OnWindowClose (int win_type, BOOL changed)
{
	if (vOnWindowClose)
		return vOnWindowClose(win_type, changed);
	return WINCLOSE_DEFAULT;
}

PLUGIN_API BOOL
BeforeExecuteWindow (int win_type)
{
	if (vBeforeExecuteWindow)
		return vBeforeExecuteWindow(win_type);
	return TRUE;
}

PLUGIN_API void
AfterExecuteWindow (int win_type, int result)
{
	if (vAfterExecuteWindow)
		vAfterExecuteWindow(win_type, result);
}

PLUGIN_API void
OnConnectionChange (void)
{
	if (vOnConnectionChange)
		vOnConnectionChange();
}

PLUGIN_API void
OnWindowConnectionChange (void)
{
	if (vOnWindowConnectionChange)
		vOnWindowConnectionChange();
}

PLUGIN_API void
OnPopup (char *obj_type, char *obj_name)
{
	if (vOnPopup)
		vOnPopup(obj_type, obj_name);
}

PLUGIN_API void
OnMainMenu (char *menu_name)
{
	if (vOnMainMenu)
		vOnMainMenu(menu_name);
}

PLUGIN_API BOOL
OnTemplate (char *filename, const char **data)
{
	if (vOnTemplate)
		return vOnTemplate(filename, data);
	return TRUE;
}

PLUGIN_API void
OnFileLoaded (int win_type, int mode)
{
	if (vOnFileLoaded)
		vOnFileLoaded(win_type, mode);
}

PLUGIN_API void
OnFileSaved (int win_type, int mode)
{
	if (vOnFileSaved)
		vOnFileSaved(win_type, mode);
}

PLUGIN_API const char *
About (void)
{
	if (vAbout)
		return vAbout();
	return NULL;
}

PLUGIN_API void
CommandLine (int handle, char *command, char *params)
{
	if (vCommandLine)
		vCommandLine(handle, command, params);
}

PLUGIN_API const char *
RegisterExport (void)
{
	if (vRegisterExport)
		return vRegisterExport();
	return NULL;
}

PLUGIN_API BOOL
ExportInit (void)
{
	if (vExportInit)
		return vExportInit();
	return TRUE;
}

PLUGIN_API void
ExportFinished (void)
{
	if (vExportFinished)
		vExportFinished();
}

PLUGIN_API BOOL
ExportPrepare (void)
{
	if (vExportPrepare)
		return vExportPrepare();
	return TRUE;
}

PLUGIN_API BOOL
ExportData (char *value)
{
	if (vExportData)
		return vExportData(value);
	return FALSE;
}

