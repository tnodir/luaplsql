/* PL/SQL Developer Lua Plug-In: Debug */

#include <stdio.h>

static FILE *g_LogFile = NULL;

#define LOG(fmt, ...) \
	do { if (DEBUG) { \
		if (!g_LogFile) {\
			g_LogFile = fopen("Debug_LuaPlSql.txt", "a"); \
			if (!g_LogFile) g_LogFile = stderr; \
		} \
		fprintf(g_LogFile, fmt, __VA_ARGS__); \
		fputc('\n', g_LogFile); \
		fflush(g_LogFile); \
	} } while (0)
