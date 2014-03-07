
LuaPlSql is a Lua Plug-In framework for Pl/Sql Developer IDE.

You can program your own Addons for Lua Plug-In to extend the functionality of PL/SQL Developer.

Functions in a Addon can be added to the PL/SQL Developer menu,
and can perform any kind of action: access the database, the Object Browser,
the current window and editor and so on.

Pl/Sql Developer: http://www.allroundautomations.com/plsqldev.html


Building:

- Download LuaPlSql (https://github.com/tnodir/luaplsql/archive/master.zip)
- Download LuaSys (https://github.com/tnodir/luasys/archive/master.zip)
- Download LuaJIT (http://luajit.org/download.html)

- Compile each of them in "Visual Studio .NET Command Prompt" by src/msvcbuild.bat

- Copy lua51.dll from "luajit/src" into "luaplsql/PlugIns/lua/clibs"
- Copy sys.dll from "luasys/src" into "luaplsql/PlugIns/lua/clibs"


Installation:

- Copy "luaplsql/PlugIns" into "C:\Program Files\PLSQL Developer\"


Useful modules:

- IUP: http://luaforge.net/projects/iup/
- LPeg: http://www.inf.puc-rio.br/~roberto/lpeg.html


Thanks to:

- Alexey Matveev, <matveev_alexey@mail.ru>
- Grzegorz Zagorski, <Grzegorz.Zagorski@hansemerkur.de>

--
Nodir Temirkhodjaev, <nodir.temir@gmail.com>
