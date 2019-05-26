# Lua PL/SQL Developer Plug-In

[![Release](https://img.shields.io/github/release/tnodir/luaplsql.svg)](https://github.com/tnodir/luaplsql/releases/latest) [![Downloads](https://img.shields.io/github/downloads/tnodir/luaplsql/total.svg?maxAge=86400)](https://github.com/tnodir/luaplsql/releases) [![License](https://img.shields.io/github/license/tnodir/luaplsql.svg)](https://www.gnu.org/licenses/gpl-3.0)

LuaPlSql is a Lua Plug-In framework for PL/SQL Developer IDE.

You can program your own Addons for Lua Plug-In to extend the functionality of PL/SQL Developer.

Functions in an Addon can be added to the PL/SQL Developer menu,
and can perform any kind of action: access the database, the Object Browser,
the current window and editor and so on.

PL/SQL Developer: http://www.allroundautomations.com/plsqldev.html

## Building:

- Download LuaPlSql (https://github.com/tnodir/luaplsql/archive/master.zip)
- Download LuaSys (https://github.com/tnodir/luasys/archive/master.zip)
- Download LuaJIT (http://luajit.org/download.html)

- Compile each of them in "Visual Studio .NET Command Prompt" by src/msvcbuild.bat

- Copy lua51.dll from "luajit/src" into "luaplsql/PlugIns/lua/clibs"
- Copy sys.dll from "luasys/src" into "luaplsql/PlugIns/lua/clibs"

## Installation:

- Copy "luaplsql/PlugIns" into "C:\Program Files\PLSQL Developer\"

## Useful modules:

- IUP: http://luaforge.net/projects/iup/
- LPeg: http://www.inf.puc-rio.br/~roberto/lpeg.html

lua5.1.dll for LuaJIT and IUP: https://github.com/tnodir/luajit-windows/

## Thanks to:

- Alexey Matveev
- Grzegorz Zagorski
- David Wilkie

--
Nodir Temirkhodjaev, <nodir.temir@gmail.com>
