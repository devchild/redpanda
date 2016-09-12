%option bison-bridge
%option bison-locations
%option ecs
%option nodefault
%option noyywrap
%option reentrant
%option stack
%option warn
%option yylineno

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

char* strdup(const char* str);

%}

%option nounistd noyywrap

%%

[ \t\n]					; // ignore all whitespace
[0-9]*\.[0-9]+ 			{ yylval.cval = strdup(yytext); return T_FLOAT;}
[0-9]+					{ yylval.cval = strdup(yytext); return T_INT;}
"end"					{ return T_END;  }
"return"				{ return T_RETURN; }
"def"					{ return T_DEF; }
"&"						{ return T_AND; }
"|"						{ return T_OR; }

[A-Za-z_][A-Za-z0-9_]*	{ return T_IDENT;} 
"+"						{ return T_PLUS;}
"-"						{ return T_MINUS;}
"*"						{ return T_MULTIPLY;}
"/"						{ return T_DIVIDE;}
"^"						{ return T_POW;}
"("						{ return T_LEFT;}
")"						{ return T_RIGHT;}
":"						{ return T_COLON;}
"!"						{ return T_NOT;}


%%

char* strdup(const char* str)
{
      char* newstr = (char*) malloc( strlen( str) + 1);

      if (newstr) {
          strcpy( newstr, str);
      }

      return newstr;
}

