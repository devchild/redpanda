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
%token						ELSE						"'else''"
%token						T_IF						"'if''"

%token						T_IDENT	  					"identifier"
%token						T_INT	  					"integer"
%token						T_FLOAT	  					"float"
%token						T_STRING					"string"

%token						T_AND   					"'&'"
%token						T_XOR   					"'^'"
%token						T_OR   						"'|'"
%token						T_PLUS   					"'+'"
%token						T_MINUS   					"'-'"
%token						T_MULTIPLY   				"'*'"
%token						T_DIVIDE	  				"'/'"
%token						T_EQ	  					"'='"
%token						T_NOT	  					"'!'"
%token						T_COLON	  					"':'"
%token						T_LEFTP	  					"'('"
%token						T_RIGHTP	  				"')'"
%token						T_POW	  					"'**'"
%token						T_SQRT	  					"'//'"
%token						T_LT	  					"'<'"
%token						T_GT	  					"'>'"
%token						OP_LESS_THAN_OR_EQUAL	  	"'<='"
%token						OP_GREATER_THAN_OR_EQUAL	"'>='"

%token						T_QM						"'?'"
%token						OP_SHIFT_RIGHT				"'>>''"
%token						OP_SHIFT_LEFT				"'<<''"
%token						T_NEQ						"'!=''"
%token						OP_OROR						"'||'"
%token						OP_ANDAND					"'&&'"

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

expression:  non_assign_expression
;

non_assign_expression: conditional_expression 
;

assign_expression: variable_reference_expression T_EQ expression
;

conditional_expression: binary_operator_expression				
	| binary_operator_expression T_QM expression T_COLON expression
;

variable_reference_expression: T_IDENT
;

unary_expression: primary_expression
	| T_PLUS unary_expression
	| T_MINUS unary_expression 
	| T_LEFTP expression T_RIGHTP
;

primary_expression: primitive_expression
	| method_invoke_expression
	| variable_reference_expression
;

primitive_expression: T_INT
	| T_FLOAT
	| T_STRING
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

binary_operator_expression: conditional_and_expression
	| binary_operator_expression OP_OROR conditional_and_expression
;

conditional_and_expression: inclusive_or_expression	
	| conditional_and_expression OP_ANDAND inclusive_or_expression
;

inclusive_or_expression: exclusive_or_expression
	| inclusive_or_expression T_OR exclusive_or_expression
;

exclusive_or_expression: and_expression
	| exclusive_or_expression T_XOR and_expression
;

and_expression: equality_expression						
	| and_expression T_AND equality_expression
;

equality_expression: relational_expression
	| equality_expression T_EQ relational_expression
	| equality_expression T_NEQ relational_expression
;

relational_expression: shift_expression						
	| relational_expression T_LT shift_expression
	| relational_expression T_GT shift_expression
	| relational_expression OP_LESS_THAN_OR_EQUAL shift_expression
	| relational_expression OP_GREATER_THAN_OR_EQUAL shift_expression
;

shift_expression: additive_expression 					
	| shift_expression OP_SHIFT_LEFT additive_expression
	| shift_expression OP_SHIFT_RIGHT additive_expression
;

method_invoke_expression: method_reference_expression T_LEFTP T_RIGHTP
;

method_reference_expression: T_IDENT
;

expression_statement: statement_expression
;

statement_expression: method_invoke_expression 
	| assign_expression
;

return_statement: T_RETURN expression
;

condition_statement: T_IF binary_operator_expression statement_list BLOCK_END
	| T_IF binary_operator_expression statement_list ELSE statement_list BLOCK_END
;

statement: expression_statement
	| condition_statement
	| return_statement
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
	T_DEF T_IDENT T_LEFTP T_RIGHTP statement_list_opt BLOCK_END 
;

%%

int yyerror (YYLTYPE *locp, void* scanner, char const *msg)
{
  printf ("(%d:%d) %s\n", locp->first_line, locp->first_column, msg);

  //printf ("%s\n", msg);
  return 0;
}