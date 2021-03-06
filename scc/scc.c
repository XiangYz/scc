#include "DynArray.h"
#include "DynString.h"
#include "hash.h"
#include "Token.h"
#include "lexer.h"
#include "error.h"
#include "parser.h"

#include <Windows.h>

void init()
{
	line_num = 1;
	init_lex();
}

void cleanup()
{
	int i;
	printf("\ntktable.count = %d\n", tktable.count);
	for (i = TK_IDENT; i < tktable.count; i++)
	{
		free(tktable.data[i]);
	}

	free(tktable.data);
}

void color_token(int lex_state)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char* p;
	switch (lex_state)
	{
	case LEX_NORMAL:
	{
		if (token >= TK_IDENT)
		{
			SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
		}
		else if (token >= KW_CHAR)
		{
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else if (token >= TK_CINT)
		{
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);
		}
		else
		{
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		}

		p = get_tkstr(token);
		printf("%s", p);
		break;
	}
	case LEX_SEP:
		printf("%c", ch);
		break;
	}
}


void print_tab(int n)
{
	int i = 0;
	for (; i < n; ++i)
		printf("\t");
}

void syntax_indent()
{
	switch (syntax_state)
	{
	case SNTX_NUL:
		color_token(LEX_NORMAL);
		break;
	case SNTX_SP:
		printf(" ");
		color_token(LEX_NORMAL);
		break;
	case SNTX_LF_HT:
	{
		if (token == TK_END)
			syntax_level--;
		printf("\n");
		print_tab(syntax_level);
	}
	color_token(LEX_NORMAL);
	break;
	case SNTX_DELAY:
		break;

	} // switch

	syntax_state = SNTX_NUL;
}



int main(int argc, char* argv[])
{
	fin = fopen(argv[1], "rb");
	if (!fin)
	{
		printf("cannot open source file!\n");
		return 0;
	}

	init();

	getch();
	/*
	do
	{
		get_token();
		color_token(LEX_NORMAL);
	} while (token != TK_EOF);
	printf("\nline number: %d\n", line_num);
	*/

	get_token();
	translation_unit();

	cleanup();
	fclose(fin);
	printf("\n%s parse finished!", argv[1]);

	

	return 0;
}