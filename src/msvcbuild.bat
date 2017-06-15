@rem Open "Visual Studio .NET Command Prompt" to run this script

@setlocal
@set LUA=../../luajit-2.0
@set LSCOMPILE=cl /nologo /c /LD /MD /O2 /W3 /D_CRT_SECURE_NO_DEPRECATE /I%LUA%/src
@set LSLINK=link /nologo
@set LSPLUG_FLAGS=/DYNAMICBASE:NO /FIXED:NO /NXCOMPAT:NO

%LSCOMPILE% /DLUA_BUILD_AS_DLL luaplug.c
@if errorlevel 1 goto :END
%LSLINK% %LSPLUG_FLAGS% /DLL /OUT:luaplug.dll luaplug.obj %LUA%/src/lua*.lib kernel32.lib user32.lib
@if errorlevel 1 goto :END

%LSCOMPILE% /DLUA_BUILD_AS_DLL luaplsql.c
@if errorlevel 1 goto :END
%LSLINK% /DLL /OUT:luaplsql.dll luaplsql.obj %LUA%/src/lua*.lib kernel32.lib user32.lib comdlg32.lib
@if errorlevel 1 goto :END

@del *.obj *.manifest *.lib *.exp

@move /Y luaplug.dll ..\PlugIns
@mkdir ..\PlugIns\lua\clibs
@move /Y luaplsql.dll ..\PlugIns\lua\clibs

:END
