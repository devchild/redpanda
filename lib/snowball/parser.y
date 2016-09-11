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
	int ival;
	float fval;
	double dval;
}

%token<ival> T_INT
%token<fval> T_FLOAT
%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_LEFT T_RIGHT T_POW
%token T_NEWLINE T_QUIT T_END T_IDENT T_COLON T_RETURN
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE
%left NEG
%right T_POW

%type<ival> expression

%start calculation

%%

calculation: lines_opt
;

line: T_NEWLINE
    | function
    | expression T_NEWLINE { printf("\tResult: %i\n", $1); } 
    | T_QUIT T_NEWLINE { printf("bye!\n"); exit(0); }
;

lines: line
     | lines line
;

lines_opt: 
	 | lines
;

expression: T_FLOAT                 		 	 { $$ = $1; }
	  | T_INT					 { $$ = $1; }
	  | expression T_PLUS expression	 	 { $$ = $1 + $3; }
	  | expression T_MINUS expression	 	 { $$ = $1 - $3; }
	  | expression T_MULTIPLY expression		 { $$ = $1 * $3; }
	  | expression T_DIVIDE expression	 	 { $$ = $1 / $3; }
	  | T_MINUS expression %prec NEG		 { $$ = -$2; }
	  | expression T_POW expression			 { $$ = pow($1, $3); } 
	  | T_LEFT expression T_RIGHT			 { $$ = $2; }
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

function:
	T_IDENT T_LEFT T_RIGHT T_COLON statement_list_opt T_END
;

%%

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
