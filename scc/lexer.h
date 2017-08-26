#ifndef _LEX_
#define _LEX_

#include "Token.h"
#include "DynArray.h"
#include "DynString.h"
#include <string.h>
#include <stdlib.h>

extern int token;
extern TkWord* tk_hashtable[];
extern DynArray tktable;



extern DynString tkstr;
extern DynString sourcestr;

extern int tkvalue;


extern char ch;

extern int line_num;

extern FILE* fin;



enum e_LexState
{
	LEX_NORMAL,
	LEX_SEP
};


void getch();
TkWord* tkword_direct_insert(TkWord* tp);
TkWord* tkword_find(char* p, int keyno);
void* mallocz(int size);
TkWord* tkword_insert(char* p);
void init_lex();
void get_token();
void preprocess();
void parse_comment();
void skip_white_space();
int is_nodigit(char c);
int is_digit(char c);
void parse_identifier();
void parse_num();
void parse_string(char sep);

#endif