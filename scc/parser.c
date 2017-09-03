#include "parser.h"
#include "error.h"
#include "lexer.h"
#include "DynArray.h"
#include "DynString.h"
#include "parser.h"
#include "error.h"


int syntax_level;
int syntax_state;

void syntax_indent();

void translation_unit()
{
	while (token != TK_EOF)
	{
		external_declaration(SC_GLOBAL);
	}
}


void external_declaration(int l)
{
	if (!type_specifier())
	{
		expect("<type specifier>");
	}

	if (token == TK_SEMICOLON)
	{
		get_token();
		return;
	}


	while (1)
	{
		declarator();
		if (token == TK_BEGIN)
		{
			if (l == SC_LOCAL)
				error("illegal function definetion");
			funcbody();
			break;
		}
		else
		{
			if (token == TK_ASSIGN)
			{
				get_token();
				initializer();
			}
		}

		if (token == TK_COMMA)
		{
			get_token();
		}
		else
		{
			syntax_state = SNTX_LF_HT;
			skip(TK_SEMICOLON);
			break;
		}
	} // while
}

int type_specifier()
{
	int type_found = 0;

	switch (token)
	{
	case KW_CHAR:
		type_found = 1;
		syntax_state = SNTX_SP;
		get_token();
		break;
	case KW_SHORT:
		type_found = 1;
		syntax_state = SNTX_SP;
		get_token();
		break;
	case KW_VOID:
		type_found = 1;
		syntax_state = SNTX_SP;
		get_token();
		break;
	case KW_INT:
		syntax_state = SNTX_SP;
		type_found = 1;
		get_token();
		break;
	case KW_STRUCT:
		syntax_state = SNTX_SP;
		struct_specifier();
		type_found = 1;
		break;
	default:
		break;
	} // switch

	return type_found;
}


void struct_specifier()
{
	int v;

	get_token();
	v = token;

	syntax_state = SNTX_DELAY;
	get_token();

	if (token == TK_BEGIN)
		syntax_state = SNTX_LF_HT;
	else if (token == TK_CLOSEPA)
		syntax_state = SNTX_NUL;
	else
		syntax_state = SNTX_SP;

	syntax_indent();

	if (v < TK_IDENT)
		expect("struct name");

	if (token == TK_BEGIN)
	{
		struct_declaration_list();
	}
}


void struct_declaration_list()
{
	int maxalign, offset;

	syntax_state = SNTX_LF_HT;
	syntax_level++;

	get_token();
	while (token != TK_END)
	{
		struct_declaration(&maxalign, &offset);
	}
	skip(TK_END);

	syntax_state = SNTX_LF_HT;
}


void struct_declaration()
{
	type_specifier();
	while (1)
	{
		declarator();

		if (token == TK_SEMICOLON)
			break;
		skip(TK_COMMA);
	}

	syntax_state = SNTX_LF_HT;
	skip(TK_SEMICOLON);
}


void function_calling_convention(int* fc)
{
	*fc = KW_CDECL;
	if (token == KW_CDECL || token == KW_STDCALL)
	{
		*fc = token;
		syntax_state = SNTX_SP;
		get_token();
	}
}


void struct_member_alignment()
{
	if (token == KW_ALIGN)
	{
		get_token();
		skip(TK_OPENPA);
		if (token == TK_CINT)
		{
			get_token();
		}
		else
			expect("const int");
		skip(TK_CLOSEPA);
	}
}

void declarator()
{
	int fc;
	while (token == TK_STAR)
	{
		get_token();
	}

	function_calling_convention(&fc);
	struct_member_alignment();
	direct_declarator();
}

void direct_declarator()
{
	if (token > TK_IDENT)
	{
		get_token();
	}
	else
	{
		expect("identifier");
	}

	direct_declarator_postfix(); 
}


void direct_declarator_postfix()
{
	int n;

	if (token == TK_OPENPA)
	{
		parameter_type_list(0);
	}
	else if (token == TK_OPENBR)
	{
		get_token();
		if (token == TK_CINT)
		{
			get_token();
			n = tkvalue;
		}
		skip(TK_CLOSEBR);
		direct_declarator_postfix();
	}
}

void parameter_type_list(int func_call)
{
	get_token();
	while (token != TK_CLOSEPA)
	{
		if (!type_specifier())
		{
			error("ineffcient type specifier");
		}
		declarator();
		if (token == TK_CLOSEPA)
			break;
		skip(TK_COMMA);
		if (token == TK_ELLIPSIS)
		{
			func_call = KW_CDECL;
			get_token();
			break;
		}
	} // while

	syntax_state = SNTX_DELAY;
	skip(TK_CLOSEPA);
	if (token == TK_BEGIN)
		syntax_state = SNTX_LF_HT;
	else
		syntax_state = SNTX_NUL;
	syntax_indent();
}


void funcbody()
{
	compound_statement();
}

void initializer()
{
	assignment_expression();
}

void statement(int* bsym, int* csym)
{
	switch (token)
	{
	case TK_BEGIN:
		compound_statement(bsym, csym);
		break;
	case KW_IF:
		if_statement(bsym, csym);
		break;
	case KW_RETURN:
		return_statement();
		break;
	case KW_BREAK:
		break_statement(bsym);
		break;
	case KW_CONTINUE:
		continue_statement(csym);
		break;
	case KW_FOR:
		for_statement(bsym, csym);
		break;
	default:
		expression_statement();
		break;

	}// switch
}



void compound_statement()
{
	syntax_state = SNTX_LF_HT;
	syntax_level++;

	get_token();
	while (is_type_specifier(token))
	{
		external_declaration(SC_LOCAL);
	}

	while (token != TK_END)
	{
		statement(NULL, NULL);
	}

	syntax_state = SNTX_LF_HT;
	get_token();
}

int is_type_specifier(int v)
{
	switch (v)
	{
	case KW_CHAR:
	case KW_SHORT:
	case KW_INT:
	case KW_VOID:
	case KW_STRUCT:
		return 1;
	default:
		break;
	}

	return 0;
}

void expression_statement()
{
	if (token != TK_SEMICOLON)
	{
		expression();
	}

	syntax_state = SNTX_LF_HT;
	skip(TK_SEMICOLON);
}

void if_statement()
{
	syntax_state = SNTX_SP;
	get_token();
	skip(TK_OPENPA);
	expression();
	syntax_state = SNTX_LF_HT;
	skip(TK_CLOSEPA);
	statement(NULL, NULL);
	if (token == KW_ELSE)
	{
		syntax_state = SNTX_LF_HT;
		get_token();
		statement(NULL, NULL);
	}
}

void for_statement()
{
	get_token();
	skip(TK_OPENPA);
	if (token != TK_SEMICOLON)
	{
		expression();
	}
	skip(TK_SEMICOLON);
	if (token != TK_SEMICOLON)
	{
		expression();
	}
	skip(TK_SEMICOLON);
	if (token != TK_CLOSEPA)
	{
		expression();
	}

	syntax_state = SNTX_LF_HT;
	skip(TK_CLOSEPA);
	statement(NULL, NULL);
}

void continue_statement()
{
	get_token();
	syntax_state = SNTX_LF_HT;
	skip(TK_SEMICOLON);
}

void break_statement()
{
	get_token();
	syntax_state = SNTX_LF_HT;
	skip(TK_SEMICOLON);
}

void return_statement()
{
	syntax_state = SNTX_DELAY;
	get_token();
	if (token == TK_SEMICOLON)
		syntax_state = SNTX_NUL;
	else
		syntax_state = SNTX_SP;
	syntax_indent();

	if (token != TK_SEMICOLON)
	{
		expression();
	}

	syntax_state = SNTX_LF_HT;
	skip(TK_SEMICOLON);
}

void expression()
{
	while (1)
	{
		assignment_expression();
		if (token != TK_COMMA)
			break;
		get_token();
	}
}

void assignment_expression()
{
	equality_expression();
	if (token == TK_ASSIGN)
	{
		get_token();
		assignment_expression();
	}
}

void equality_expression()
{
	relational_expression();
	while (token == TK_EQ || token == TK_NEQ)
	{
		get_token();
		relational_expression();
	}
}

void relational_expression()
{
	additive_expression();
	while (token == TK_LT || token == TK_LEQ || token == TK_GT || token == TK_GEQ)
	{
		get_token();
		additive_expression();
	}
}

void additive_expression()
{
	multiplicative_expression();
	while (token == TK_PLUS || token == TK_MINUS)
	{
		get_token();
		multiplicative_expression();
	}
}


void multiplicative_expression()
{
	unary_expression();
	while (token == TK_STAR || token == TK_DIVIDE || token == TK_MOD)
	{
		get_token();
		unary_expression();
	}
}

void unary_expression()
{
	switch (token)
	{
	case TK_AND:
		get_token();
		unary_expression();
		break;
	case TK_STAR:
		get_token();
		unary_expression();
		break;
	case TK_MINUS:
		get_token();
		unary_expression();
		break;
	case TK_PLUS:
		get_token();
		unary_expression();
		break;
	case KW_SIZEOF:
		sizeof_expression();
		break;
	default:
		postfix_expression();
		break;

	} // token
}

void sizeof_expression()
{
	get_token();
	skip(TK_OPENPA);
	type_specifier();
	skip(TK_CLOSEPA);
}


void postfix_expression()
{
	primary_expression();
	while (1)
	{
		if (token == TK_DOT || token == TK_POINTSTO)
		{
			get_token();
			token |= SC_MEMBER;
			get_token();
		}
		else if (token == TK_OPENBR)
		{
			get_token();
			expression();
			skip(TK_CLOSEBR);
		}
		else if (token == TK_OPENPA)
		{
			argument_expression_list();
		}
		else
			break;

	} // while
}


void primary_expression()
{
	int t;
	switch (token)
	{
	case TK_CINT:
	case TK_CCHAR:
		get_token();
		break;
	case TK_CSTR:
		get_token();
		break;
	case TK_OPENPA:
		get_token();
		expression();
		skip(TK_CLOSEPA);
		break;
	default:
		t = token;
		get_token();
		if (t < TK_IDENT)
			expect("identifier or constant");
		break;
	}
}

void argument_expression_list()
{
	get_token();
	if (token != TK_CLOSEPA)
	{
		for (; ; )
		{
			assignment_expression();
			if (token == TK_CLOSEPA)
				break;
			skip(TK_COMMA);
		}
	}

	skip(TK_CLOSEPA);
}

