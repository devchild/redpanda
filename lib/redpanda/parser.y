%defines
%locations
%define api.pure full
%define parse.error verbose

%lex-param   { yyscan_t scanner }
%parse-param { yyscan_t scanner }
%parse-param { node_callback_t callback }

%code requires {

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <redpanda.h>

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
  typedef void *yyscan_t;
#endif

#ifdef _WIN32
#   include <io.h>
#   ifdef _MSC_VER
#     define isatty _isatty
#     define fileno _fileno
// '_isatty' : inconsistent dll linkage.  dllexport assumed.
#     pragma warning( disable : 4273 )
#   endif
#endif

}

%code {
#include <scanner.h>
int yyerror(YYLTYPE * location, yyscan_t scanner, node_callback_t callback, const char *msg) {
    fprintf(stderr, "(Ln %d: Col %d - Ln %d: Col %d) %s\n", location->first_line, location->first_column, location->last_line, location->last_column, msg);
  	return 0;
}
}

%union {
   int int_const;
   float float_const;

   int type_specifier;
   char *identifier;

   struct ast_node *node;
   struct ast_declaration *declaration;
   struct ast_expression *expression;
   struct ast_statement_list *statement_list;
   struct ast_selection_statement *selection_statement;
   struct ast_while_statement *while_statement;
   struct ast_compound_statement *compound_statement;
   struct ast_compile_unit *compile_unit;
}

%token        				END      0 					"end-of-file"
%token						EOL							"end-of-line"	
%token						T_INDENT					"indentation"	
%token						T_DEDENT					"dedentation"			
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
%token						T_SCOLON	  				"';'"
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


%type <compile_unit>     					compile_unit
%type <statement_list>						compile_unit_member_list_opt	

%start compile_unit

%%

compile_unit: compile_unit_member_list_opt { $$ = create_compile_unit($1); callback($$); }
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
	| additive_expression T_PLUS multiplicative_expression 	{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
	| additive_expression T_MINUS multiplicative_expression { 
																// $$ = val_append0($2, $1, $3, 0);
															}
;

multiplicative_expression: power_expression
	| multiplicative_expression T_MULTIPLY power_expression { 
																// $$ = val_append0($2, $1, $3, 0); 
															}
	| multiplicative_expression T_DIVIDE power_expression 	{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
;

power_expression: unary_expression
	| power_expression T_POW unary_expression				{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
	| power_expression T_SQRT unary_expression 				{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
;

binary_operator_expression: conditional_and_expression
	| binary_operator_expression OP_OROR conditional_and_expression  	
															{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
;

conditional_and_expression: inclusive_or_expression	
	| conditional_and_expression OP_ANDAND inclusive_or_expression
															{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
;

inclusive_or_expression: exclusive_or_expression
	| inclusive_or_expression T_OR exclusive_or_expression 	{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
;

exclusive_or_expression: and_expression
	| exclusive_or_expression T_XOR and_expression 			{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
;

and_expression: equality_expression						
	| and_expression T_AND equality_expression				{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
;

equality_expression: relational_expression
	| equality_expression T_EQ relational_expression		{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
	| equality_expression T_NEQ relational_expression  		{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
;

relational_expression: shift_expression						
	| relational_expression T_LT shift_expression 			{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
	| relational_expression T_GT shift_expression 			{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
	| relational_expression OP_LESS_THAN_OR_EQUAL shift_expression 	
															{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
	| relational_expression OP_GREATER_THAN_OR_EQUAL shift_expression 	
															{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
;

shift_expression: additive_expression 					
	| shift_expression OP_SHIFT_LEFT additive_expression 	{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
	| shift_expression OP_SHIFT_RIGHT additive_expression 	{ 
																// $$ = val_append0($2, $1, $3, 0); 
															}
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

return_statement: T_RETURN expression 	{ /* $$ = val_return($2); */ }
;

condition_statement: T_IF binary_operator_expression T_COLON statement_list BLOCK_END
	| T_IF binary_operator_expression statement_list ELSE statement_list BLOCK_END
;

statement: expression_statement
	| condition_statement
	| return_statement
;

statement_list: statement				{	 }
	| statement_list statement			{	 }
	| statement_list error statement 	{	 }
;

statement_list_opt:
	%empty
	| statement_list
;

method:
	T_DEF T_IDENT T_LEFTP T_RIGHTP T_COLON T_INDENT statement_list T_DEDENT {
	// $$ = val_fun($2, $5);
	}
;

%%


