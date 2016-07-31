%{
#include <stdio.h>
#include <string.h>
#include "parser.h"
%}

%%

[[:space:]]+	; // ignore all whitespace
[[:digit:]]*\.[[:digit:]]+ 	{	yylval.fval = atof(yytext); return T_FLOAT;}
[[:digit:]]+			{	yylval.ival = atoi(yytext); return T_INT;}
[[:alpha:]_][[:alnum:]_]* {
			char * copy = strndup(yytext, yyleng);
			yylval.cval = copy; 
			return T_IDENT;
		}
\n		{	return T_NEWLINE;	}
"+"		{	return T_PLUS;		}
"-"		{	return T_MINUS;		}
"*"		{	return T_MULTIPLY;	}
"/"		{	return T_DIVIDE;	}
"("		{	return T_LEFT;		}
")"		{	return T_RIGHT;		}
"exit"		{	return T_QUIT;		}
"quit"		{	return T_QUIT;		}

%%

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

int yywrap() {
   // open next reference or source file and start scanning
   /*if((yyin = compiler->getNextFile()) != NULL) {
      line = 0; // reset line counter for next source file
      return 0;
   }*/
   return 0;
}
