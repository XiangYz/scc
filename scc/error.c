#include "error.h"
#include "Token.h"
#include "lexer.h"

char filename[256] = { 0 };


void handle_exception(int stage, int level, char* fmt, va_list ap)
{
	char buf[1024];
	vsprintf(buf, fmt, ap);

	if (stage == STAGE_COMPILE)
	{
		if (level == LEVEL_WARNING)
			printf("%s( %d): compile warning: %s!\n", filename, line_num, buf);
		else
		{
			printf("%s( %d): compile error: %s!\n", filename, line_num, buf);
			exit(-1);
		}
	}
	else
	{
		printf("link error: %s!\n", buf);
		exit(-1);
	}
}


void warning(char* fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	handle_exception(STAGE_COMPILE, LEVEL_WARNING, fmt, ap);
	va_end(ap);
}

void error(char* fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	handle_exception(STAGE_COMPILE, LEVEL_ERROR, fmt, ap);
	va_end(ap);
}


void expect(char* msg)
{
	error("need %s", msg);
}

void skip(int c)
{
	if (token != c)
	{
		error("need '%s", get_tkstr(c));
	}
	get_token();
}


char* get_tkstr(int v)
{
	if (v > tktable.count)
	{
		return NULL;
	}
	else if (v >= TK_CINT && v <= TK_CSTR)
	{
		return sourcestr.data;
	}
	else
	{
		return ((TkWord*)tktable.data[v])->spelling;
	}
}

void link_error(char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	handle_exception(STAGE_LINK, LEVEL_ERROR, fmt, ap);
	va_end(ap);
}
