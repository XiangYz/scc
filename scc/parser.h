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
	SC_GLOBAL = 0x00f0,		// �������������ͳ������ַ��������ַ�������,ȫ�ֱ���,��������          
	SC_LOCAL = 0x00f1,		// ջ�б���
	SC_LLOCAL = 0x00f2,       // �Ĵ���������ջ��
	SC_CMP = 0x00f3,       // ʹ�ñ�־�Ĵ���
	SC_VALMASK = 0x00ff,       // �洢��������             
	SC_LVAL = 0x0100,       // ��ֵ       
	SC_SYM = 0x0200,       // ����	

	SC_ANOM = 0x10000000,     // ��������
	SC_STRUCT = 0x20000000,     // �ṹ�����
	SC_MEMBER = 0x40000000,     // �ṹ��Ա����
	SC_PARAMS = 0x80000000,     // ��������
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