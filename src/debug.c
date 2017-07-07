/* PL/SQL Developer Lua Plug-In: Debug */

#include <stdio.h>

static void
LOG (const char * const fmt, ...)
{
	static FILE *g_LogFile = NULL;

	if (!DEBUG) return;

	if (!g_LogFile) {
		g_LogFile = fopen("Debug_LuaPlSql.txt", "a");
		if (!g_LogFile) g_LogFile = stderr;
	}

	{
		va_list args;
		va_start(args, fmt);
		fprintf(g_LogFile, args);
		va_end(args);
	}
	fputc('\n', g_LogFile);
	fflush(g_LogFile);
}
