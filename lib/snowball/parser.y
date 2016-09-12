%define parse.error verbose
%define api.pure true
%locations

%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(const char* s);

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



%token<cval> T_INT
%token<cval> T_FLOAT
%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_LEFT T_RIGHT T_POW
%token T_END T_IDENT T_COLON T_RETURN T_DEF

%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE
%left NEG

%left T_OR
%left T_AND

%right T_POW
%right T_NOT

%start compile_unit



%%

compile_unit: compile_unit_member_list_opt
;

compile_unit_member: method
				   | statement
;

compile_unit_member_list: compile_unit_member
						 | compile_unit_member_list compile_unit_member
;

compile_unit_member_list_opt: 
	 | compile_unit_member_list
;

expression: T_FLOAT                 		 	
	  | T_INT									
	  | method_invoke_expression				
	  | expression T_PLUS expression	 		
	  | expression T_MINUS expression	 		
	  | expression T_MULTIPLY expression		
	  | expression T_DIVIDE expression	 		
	  | T_MINUS expression %prec NEG			
	  | expression T_POW expression				
	  | T_LEFT expression T_RIGHT				
;

method_invoke_expression:
	T_IDENT T_LEFT T_RIGHT
;

statement: expression
	 | T_RETURN expression
	 | T_RETURN
;

statement_list: statement
	      | statement_list statement
;

statement_list_opt:
		  | statement_list
;

method:
	T_DEF T_IDENT T_LEFT T_RIGHT T_COLON statement_list_opt T_END
;

%%

void yyerror (YYLTYPE *locp, char const *msg);
	printf("Parse error: %s\n", msg);
}
