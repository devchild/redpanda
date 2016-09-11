%{
#include <stdio.h>

#define YY_DECL int yylex()

#include "parser.h"

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

%option nounistd noyywrap

%%

[ \t]	; // ignore all whitespace
[0-9]*\.[0-9]+ 		{yylval.fval = atof(yytext); return T_FLOAT;}
[0-9]+			{yylval.ival = atoi(yytext); return T_INT;}
"exit"			{return T_QUIT;}
"quit"			{return T_QUIT; }
"end"			{return T_END;  }
"return"		{return T_RETURN; }

[A-Za-z_][A-Za-z0-9_]*	{return T_IDENT;} 
\n			{return T_NEWLINE;}
"+"			{return T_PLUS;}
"-"			{return T_MINUS;}
"*"			{return T_MULTIPLY;}
"/"			{return T_DIVIDE;}
"^"			{return T_POW;}
"("			{return T_LEFT;}
")"			{return T_RIGHT;}
":"			{return T_COLON;}


%%

