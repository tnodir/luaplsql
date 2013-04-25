#ifndef LUAPLSQL_H
#define LUAPLSQL_H

#define PLUGIN_ENV	"LUAPLSQL_PATH"

#define PLUGIN_API	__declspec(dllexport)

typedef void (*PLSQL_Function)();

#ifdef __cplusplus
extern "C" {
#endif

PLUGIN_API char *PlugInShortName (void);
PLUGIN_API char *IdentifyPlugIn (int id);
PLUGIN_API void OnCreate (void);
PLUGIN_API void OnDestroy (void);
PLUGIN_API void RegisterCallback (int i, PLSQL_Function func);
PLUGIN_API void OnActivate (void);
PLUGIN_API void OnDeactivate (void);
PLUGIN_API const char *CreateMenuItem (int i);
PLUGIN_API void OnMenuClick (int i);
PLUGIN_API BOOL CanClose (void);
PLUGIN_API void AfterStart (void);
PLUGIN_API void OnBrowserChange (void);
PLUGIN_API void OnWindowChange (void);
PLUGIN_API void OnWindowCreate (int win_type);
PLUGIN_API void OnWindowCreated (int win_type);
PLUGIN_API int OnWindowClose (int win_type, BOOL changed);
PLUGIN_API BOOL BeforeExecuteWindow (int win_type);
PLUGIN_API void AfterExecuteWindow (int win_type, int result);
PLUGIN_API void OnConnectionChange (void);
PLUGIN_API void OnWindowConnectionChange (void);
PLUGIN_API void OnPopup (char *obj_type, char *obj_name);
PLUGIN_API void OnMainMenu (char *menu_name);
PLUGIN_API BOOL OnTemplate (char *filename, const char **data);
PLUGIN_API void OnFileLoaded (int win_type, int mode);
PLUGIN_API void OnFileSaved (int win_type, int mode);
PLUGIN_API const char *About (void);
PLUGIN_API void CommandLine (int handle, char *command, char *params);

PLUGIN_API const char *RegisterExport (void);
PLUGIN_API BOOL ExportInit (void);
PLUGIN_API void ExportFinished (void);
PLUGIN_API BOOL ExportPrepare (void);
PLUGIN_API BOOL ExportData (char *value);

/* Window Close Behaviour */
#define WINCLOSE_DEFAULT	0
#define WINCLOSE_CONFIRM	1
#define WINCLOSE_QUIET		2

/* Window Execute Result */
#define WINEXEC_ERROR		0
#define WINEXEC_CONTINUE	1
#define WINEXEC_SUCCESS		2

#ifdef __cplusplus
}
#endif

#endif
