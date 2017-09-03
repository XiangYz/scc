#ifndef _PARSER_
#define _PARSER_

#include <stdio.h>

extern int syntax_level;
extern int syntax_state;


enum e_SynTaxState
{
	SNTX_NUL,
	SNTX_SP,
	SNTX_LF_HT,
	SNTX_DELAY
};

enum e_StorageClass
{
	SC_GLOBAL = 0x00f0,		// 包括：包括整型常量，字符常量、字符串常量,全局变量,函数定义          
	SC_LOCAL = 0x00f1,		// 栈中变量
	SC_LLOCAL = 0x00f2,       // 寄存器溢出存放栈中
	SC_CMP = 0x00f3,       // 使用标志寄存器
	SC_VALMASK = 0x00ff,       // 存储类型掩码             
	SC_LVAL = 0x0100,       // 左值       
	SC_SYM = 0x0200,       // 符号	

	SC_ANOM = 0x10000000,     // 匿名符号
	SC_STRUCT = 0x20000000,     // 结构体符号
	SC_MEMBER = 0x40000000,     // 结构成员变量
	SC_PARAMS = 0x80000000,     // 函数参数
};


void translation_unit();
void external_declaration(int l);
int type_specifier();
void struct_specifier();
void struct_declaration_list();
void struct_declaration();
void function_calling_convention(int* fc);
void struct_member_alignment();
void declarator();
void direct_declarator();
void direct_declarator_postfix();
void parameter_type_list(int func_call);
void funcbody();
void initializer();
void statement(int* bsym, int* csym);
void compound_statement();
int is_type_specifier(int v);
void expression_statement();
void if_statement();
void for_statement();
void continue_statement();
void break_statement();
void return_statement();
void expression();
void assignment_expression();
void equality_expression();
void relational_expression();
void additive_expression();
void multiplicative_expression();
void unary_expression();
void sizeof_expression();
void postfix_expression();
void primary_expression();
void argument_expression_list();

#endif