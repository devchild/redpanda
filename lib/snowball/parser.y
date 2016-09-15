%defines
%locations
%define api.pure full
%define parse.error verbose

%lex-param {void *scanner}
%parse-param {void *scanner}

%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _WIN32
#   include <io.h>
#   ifdef _MSC_VER
#     define isatty _isatty
#     define fileno _fileno
// '_isatty' : inconsistent dll linkage.  dllexport assumed.
#     pragma warning( disable : 4273 )
#   endif
#endif

%}

%union {
	char* cval;
}

%token        				END      0 					"end-of-file"
%token						EOL							"end-of-line"			
%token						BLOCK_END   				"keyword end"
%token						T_DEF   					"keyword def"
%token						T_RETURN	  				"keyword return"

%token						T_IDENT	  					"identifier"
%token						T_INT	  					"integer"
%token						T_FLOAT	  					"float"

%token						T_AND   					"'&'"
%token						T_OR   						"'|'"
%token						T_PLUS   					"'+'"
%token						T_MINUS   					"'-'"
%token						T_MULTIPLY   				"'*'"
%token						T_DIVIDE	  				"'/'"
%token						T_NOT	  					"'!'"
%token						T_COLON	  					"':'"
%token						T_LEFTP	  					"'('"
%token						T_RIGHTP	  				"')'"
%token						T_POW	  					"'**'"
%token						T_SQRT	  					"'//'"

%start compile_unit

%%

compile_unit: compile_unit_member_list_opt
;

compile_unit_member: method
					| method_invoke_expression
;

compile_unit_member_list: compile_unit_member
						 | compile_unit_member_list compile_unit_member
						 | compile_unit_member_list error compile_unit_member
;

compile_unit_member_list_opt: 
	 %empty
	 | compile_unit_member_list
;

expression: additive_expression 
;

primitive_expression: T_INT
	| T_FLOAT
;
	
primary_expression: method_invoke_expression
	| primitive_expression
	| T_LEFTP expression T_RIGHTP		
;

unary_expression: primary_expression
	| T_PLUS unary_expression
	| T_MINUS unary_expression 
;

additive_expression: multiplicative_expression
	| additive_expression T_PLUS multiplicative_expression
	| additive_expression T_MINUS multiplicative_expression
;

multiplicative_expression: power_expression
	| multiplicative_expression T_MULTIPLY power_expression
	| multiplicative_expression T_DIVIDE power_expression
;

power_expression: unary_expression
	| power_expression T_POW unary_expression
	| power_expression T_SQRT unary_expression
;

method_invoke_expression: T_IDENT T_LEFTP T_RIGHTP
;

statement: T_RETURN expression
;

statement_list: statement
				| statement_list statement
				| statement_list error statement
;

statement_list_opt:
		  %empty
		  | statement_list
;

method:
	T_DEF T_IDENT T_LEFTP T_RIGHTP T_COLON statement_list_opt BLOCK_END 
;

%%

int yyerror (YYLTYPE *locp, void* scanner, char const *msg)
{
  printf ("(%d:%d) %s\n", locp->first_line, locp->first_column, msg);

  //printf ("%s\n", msg);
  return 0;
}