
#include AddBackslash(SourcePath) + "..\src\version.h"

#define IconPath	(AddBackslash(SourcePath) + "..\src\Lua.ico")

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppMutex={#APP_NAME}
AppName={#APP_NAME}
AppVersion={#APP_VERSION_STR}
VersionInfoVersion={#APP_VERSION_STR}
AppVerName={#APP_NAME}
AppCopyright={#APP_LEGALCOPYRIGHT}
AppPublisher={#APP_PUBLISHER}
AppPublisherURL={#APP_URL}
AppSupportURL={#APP_URL}
AppUpdatesURL={#APP_URL}
DefaultGroupName={#APP_NAME}
DefaultDirName={pf}\PLSQL Developer\PlugIns
DirExistsWarning=no
EnableDirDoesntExistWarning=yes
AlwaysShowDirOnReadyPage=yes
AlwaysShowGroupOnReadyPage=yes
AllowNoIcons=yes
SetupIconFile={#IconPath}
OutputBaseFilename=LuaPlSql-{#APP_VERSION_STR}
Uninstallable=no
ArchitecturesInstallIn64BitMode=x64
Compression=lzma2/ultra
SolidCompression=yes

[Languages]
Name: en; MessagesFile: "compiler:Default.isl"

[Files]
Source: "..\PlugIns\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
