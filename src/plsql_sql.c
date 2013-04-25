/* PL/SQL Developer Lua Plug-In: SQL Functions */

typedef int (*SQL_Execute)(const char *SQL);
typedef int (*SQL_FieldCount)();
typedef BOOL (*SQL_Eof)();
typedef int (*SQL_Next)();
typedef char *(*SQL_Field)(int Field);
typedef char *(*SQL_FieldName)(int Field);
typedef int (*SQL_FieldIndex)(const char *FieldName);
typedef int (*SQL_FieldType)(int Field);
typedef char *(*SQL_ErrorMessage)();
typedef BOOL (*SQL_UsePlugInSession)(int PlugInID);
typedef void (*SQL_UseDefaultSession)(int PlugInID);
typedef BOOL (*SQL_CheckConnection)();
typedef char *(*SQL_GetDBMSOutput)();
typedef void (*SQL_SetVariable)(const char *Name, const char *Value);
typedef char *(*SQL_GetVariable)(const char *Name);
typedef void (*SQL_ClearVariables)();
typedef BOOL (*SQL_SetPlugInSession)(int PlugInID, const char *Username,
	const char *Password, const char *Database, const char *ConnectAs);


/*
 * Arguments: SQL (string)
 * Returns: [number]
 */
static int
plsql_sql_Execute (lua_State *L)
{
	SQL_Execute func = (SQL_Execute) plsqldev_func[40];

	if (func) {
		const char *sql = luaL_checkstring(L, 1);

		lua_pushinteger(L, func(sql));
		return 1;
	}
	return 0;
}

/*
 * Returns: [number]
 */
static int
plsql_sql_FieldCount (lua_State *L)
{
	SQL_FieldCount func = (SQL_FieldCount) plsqldev_func[41];

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
plsql_sql_Eof (lua_State *L)
{
	SQL_Eof func = (SQL_Eof) plsqldev_func[42];

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
plsql_sql_Next (lua_State *L)
{
	SQL_Next func = (SQL_Next) plsqldev_func[43];

	if (func) {
		lua_pushinteger(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Field (number)
 * Returns: [string]
 */
static int
plsql_sql_Field (lua_State *L)
{
	SQL_Field func = (SQL_Field) plsqldev_func[44];

	if (func) {
		const int field = luaL_checkinteger(L, 1) - 1;

		lua_pushstring(L, func(field));
		return 1;
	}
	return 0;
}

/*
 * Arguments: Field (number)
 * Returns: [string]
 */
static int
plsql_sql_FieldName (lua_State *L)
{
	SQL_FieldName func = (SQL_FieldName) plsqldev_func[45];

	if (func) {
		const int field = luaL_checkinteger(L, 1) - 1;

		lua_pushstring(L, func(field));
		return 1;
	}
	return 0;
}

/*
 * Arguments: FieldName (string)
 * Returns: [number]
 */
static int
plsql_sql_FieldIndex (lua_State *L)
{
	SQL_FieldIndex func = (SQL_FieldIndex) plsqldev_func[46];

	if (func) {
		const char *name = luaL_checkstring(L, 1);

		lua_pushinteger(L, func(name) + 1);
		return 1;
	}
	return 0;
}

/*
 * Arguments: Field (number)
 * Returns: [number]
 */
static int
plsql_sql_FieldType (lua_State *L)
{
	SQL_FieldType func = (SQL_FieldType) plsqldev_func[47];

	if (func) {
		const int field = luaL_checkinteger(L, 1) - 1;

		lua_pushinteger(L, func(field));
		return 1;
	}
	return 0;
}

/*
 * Returns: [string]
 */
static int
plsql_sql_ErrorMessage (lua_State *L)
{
	SQL_ErrorMessage func = (SQL_ErrorMessage) plsqldev_func[48];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Returns: [boolean]
 */
static int
plsql_sql_UsePlugInSession (lua_State *L)
{
	SQL_UsePlugInSession func = (SQL_UsePlugInSession) plsqldev_func[50];

	if (func) {
		lua_pushboolean(L, func(g_PlugInId));
		return 1;
	}
	return 0;
}

static int
plsql_sql_UseDefaultSession (lua_State *L)
{
	SQL_UseDefaultSession func = (SQL_UseDefaultSession) plsqldev_func[51];

	(void) L;

	if (func) {
		func(g_PlugInId);
	}
	return 0;
}

/*
 * Returns: [boolean]
 */
static int
plsql_sql_CheckConnection (lua_State *L)
{
	SQL_CheckConnection func = (SQL_CheckConnection) plsqldev_func[52];

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
plsql_sql_GetDBMSOutput (lua_State *L)
{
	SQL_GetDBMSOutput func = (SQL_GetDBMSOutput) plsqldev_func[53];

	if (func) {
		lua_pushstring(L, func());
		return 1;
	}
	return 0;
}

/*
 * Arguments: Name (string), Value (string)
 */
static int
plsql_sql_SetVariable (lua_State *L)
{
	SQL_SetVariable func = (SQL_SetVariable) plsqldev_func[54];

	if (func) {
		const char *name = luaL_checkstring(L, 1);
		const char *val = luaL_checkstring(L, 2);

		func(name, val);
	}
	return 0;
}

/*
 * Arguments: Name (string)
 * Returns: [string]
 */
static int
plsql_sql_GetVariable (lua_State *L)
{
	SQL_GetVariable func = (SQL_GetVariable) plsqldev_func[55];

	if (func) {
		const char *name = luaL_checkstring(L, 1);

		lua_pushstring(L, func(name));
		return 1;
	}
	return 0;
}

static int
plsql_sql_ClearVariables (lua_State *L)
{
	SQL_ClearVariables func = (SQL_ClearVariables) plsqldev_func[56];

	(void) L;

	if (func) {
		func();
	}
	return 0;
}

/*
 * Arguments: Username (string), Password (string),
 *	Database (string), ConnectAs (string)
 * Returns: [boolean]
 */
static int
plsql_sql_SetPlugInSession (lua_State *L)
{
	SQL_SetPlugInSession func = (SQL_SetPlugInSession) plsqldev_func[57];

	if (func) {
		const char *usr = luaL_checkstring(L, 1);
		const char *pwd = luaL_checkstring(L, 2);
		const char *db = luaL_checkstring(L, 3);
		const char *role = luaL_checkstring(L, 4);

		lua_pushboolean(L, func(g_PlugInId, usr, pwd, db, role));
		return 1;
	}
	return 0;
}


static luaL_Reg plsql_sqllib[] = {
    {"Execute",			plsql_sql_Execute},
    {"FieldCount",		plsql_sql_FieldCount},
    {"Eof",			plsql_sql_Eof},
    {"Next",			plsql_sql_Next},
    {"Field",			plsql_sql_Field},
    {"FieldName",		plsql_sql_FieldName},
    {"FieldIndex",		plsql_sql_FieldIndex},
    {"FieldType",		plsql_sql_FieldType},
    {"ErrorMessage",		plsql_sql_ErrorMessage},
    {"UsePlugInSession",	plsql_sql_UsePlugInSession},
    {"UseDefaultSession",	plsql_sql_UseDefaultSession},
    {"CheckConnection",		plsql_sql_CheckConnection},
    {"GetDBMSOutput",		plsql_sql_GetDBMSOutput},
    {"SetVariable",		plsql_sql_SetVariable},
    {"GetVariable",		plsql_sql_GetVariable},
    {"ClearVariables",		plsql_sql_ClearVariables},
    {"SetPlugInSession",	plsql_sql_SetPlugInSession},
    {NULL, NULL}
};
