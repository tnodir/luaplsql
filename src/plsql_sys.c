/* PL/SQL Developer Lua Plug-In: SYS Functions */

typedef int (*SYS_Version)();
typedef char *(*SYS_Registry)();
typedef char *(*SYS_RootDir)();
typedef char *(*SYS_OracleHome)();
typedef char *(*SYS_TNSNAMES)(const char *Param);


static int
Version (void)
{
	static int g_Version = 0;  // Pl/Sql Developer Version

	if (!g_Version) {
		SYS_Version func = (SYS_Version) plsqldev_func[1];

		if (func) {
			g_Version = func();
		}
	}
	return g_Version;
}

/*
 * Returns: [number]
 */
static int
plsql_sys_Version (lua_State *L)
{
	lua_pushinteger(L, Version());
	return 1;
}

/*
 * Returns: [string]
 */
static int
plsql_sys_Registry (lua_State *L)
{
	SYS_Registry func = (SYS_Registry) plsqldev_func[2];

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
plsql_sys_RootDir (lua_State *L)
{
	SYS_RootDir func = (SYS_RootDir) plsqldev_func[3];

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
plsql_sys_OracleHome (lua_State *L)
{
	SYS_OracleHome func = (SYS_OracleHome) plsqldev_func[4];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: [Param (string)]
 * Returns: [string]
 */
static int
plsql_sys_TNSNAMES (lua_State *L)
{
	SYS_TNSNAMES func = (SYS_TNSNAMES) plsqldev_func[8];

	if (func) {
		const char *param = lua_tostring(L, 1);

		lua_pushstring(L, func(param));
		return 1;
	}
	return 0;
}


static luaL_Reg plsql_syslib[] = {
    {"Version",		plsql_sys_Version},
    {"Registry",	plsql_sys_Registry},
    {"RootDir",		plsql_sys_RootDir},
    {"OracleHome",	plsql_sys_OracleHome},
    {"TNSNAMES",	plsql_sys_TNSNAMES},
    {NULL, NULL}
};
