#ifndef _TOKEN_
#define _TOKEN_

#define MAXKEY 1024





typedef struct TkWord
{
	int tkcode;
	struct TkWord* next;
	char* spelling;
	struct Symbol* sym_struct;
	struct Symbol* sym_identifier;
}TkWord;

enum TK_WORD
{

	TK_PLUS = 0,
	TK_MINUS,
	TK_STAR,
	TK_DIVIDE,
	TK_MOD,
	TK_EQ,
	TK_NEQ,
	TK_LT,
	TK_LEQ,
	TK_GT,
	TK_GEQ,
	TK_ASSIGN,
	TK_POINTSTO,
	TK_DOT,
	TK_AND,
	TK_OPENPA,
	TK_CLOSEPA,
	TK_OPENBR,
	TK_CLOSEBR,
	TK_BEGIN,
	TK_END,
	TK_SEMICOLON,
	TK_COMMA,
	TK_ELLIPSIS,
	TK_EOF,
	TK_CINT,
	TK_CCHAR,
	TK_CSTR,
	KW_CHAR,
	KW_SHORT,
	KW_INT,
	KW_VOID,
	KW_STRUCT,
	KW_IF,
	KW_ELSE,
	KW_FOR,
	KW_CONTINUE,
	KW_BREAK,
	KW_RETURN,
	KW_SIZEOF,
	KW_ALIGN,
	KW_CDECL,
	KW_STDCALL,


	TK_IDENT
};

#endif