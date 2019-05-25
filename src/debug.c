/* PL/SQL Developer Lua Plug-In: Debug */

#include <stdio.h>

static void
LOG (const char * const fmt, ...)
{
	static FILE *g_LogFile = NULL;

	if (!g_LogFile) {
		g_LogFile = fopen("LuaPlSql_Log.txt", "a");
		if (!g_LogFile) {
			g_LogFile = stderr;
		}

		fprintf(g_LogFile, "\n--\n");
	}

	{
		va_list args;
		va_start(args, fmt);
		vfprintf(g_LogFile, fmt, args);
		va_end(args);
	}
	fputc('\n', g_LogFile);
	fflush(g_LogFile);
}

#if defined(DEBUG) && DEBUG
#define DBG	LOG
#else
static void
DBG (const char * const fmt, ...)
{
	(void) fmt;
}
#endif
