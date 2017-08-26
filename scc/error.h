#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

enum e_ErrorLevel
{
	LEVEL_WARNING,
	LEVEL_ERROR,
};

enum e_WorkStage
{
	STAGE_COMPILE,
	STAGE_LINK,
};


void handle_exception(int stage, int level, char* fmt, va_list ap);
void warning(char* fmt, ...);
void error(char* fmt, ...);
void except(char* msg);
void skip(int c);
char* get_tkstr(int v);
void link_error(char* fmt, ...);


#endif
