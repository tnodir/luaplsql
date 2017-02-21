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
	SQL_Execute func = (SQL_Execute) PLSQL_FUNC[40];

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
	SQL_FieldCount func = (SQL_FieldCount) PLSQL_FUNC[41];

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
	SQL_Eof func = (SQL_Eof) PLSQL_FUNC[42];

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
	SQL_Next func = (SQL_Next) PLSQL_FUNC[43];

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
	SQL_Field func = (SQL_Field) PLSQL_FUNC[44];

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
	SQL_FieldName func = (SQL_FieldName) PLSQL_FUNC[45];

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
	SQL_FieldIndex func = (SQL_FieldIndex) PLSQL_FUNC[46];

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
	SQL_FieldType func = (SQL_FieldType) PLSQL_FUNC[47];

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
	SQL_ErrorMessage func = (SQL_ErrorMessage) PLSQL_FUNC[48];

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
	SQL_UsePlugInSession func = (SQL_UsePlugInSession) PLSQL_FUNC[50];

	if (func) {
		lua_pushboolean(L, func(g_PlugInId));
		return 1;
	}
	return 0;
}

static int
plsql_sql_UseDefaultSession (lua_State *L)
{
	SQL_UseDefaultSession func = (SQL_UseDefaultSession) PLSQL_FUNC[51];

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
	SQL_CheckConnection func = (SQL_CheckConnection) PLSQL_FUNC[52];

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
	SQL_GetDBMSOutput func = (SQL_GetDBMSOutput) PLSQL_FUNC[53];

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
	SQL_SetVariable func = (SQL_SetVariable) PLSQL_FUNC[54];

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
	SQL_GetVariable func = (SQL_GetVariable) PLSQL_FUNC[55];

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
	SQL_ClearVariables func = (SQL_ClearVariables) PLSQL_FUNC[56];

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
	SQL_SetPlugInSession func = (SQL_SetPlugInSession) PLSQL_FUNC[57];

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
