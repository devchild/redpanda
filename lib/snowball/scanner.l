%option bison-bridge
%option bison-locations
%option nounistd
%option reentrant
%option noyywrap
%option yylineno

%{
#include <stdio.h>

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

// support locationtracking
#define YY_USER_ACTION	yylloc->first_line = yylloc->last_line = yyget_lineno(yyscanner); \
						yylloc->first_column = yyget_column(yyscanner); \
						yylloc->last_column = yyget_column(yyscanner) + yyget_leng(yyscanner) - 1; \
						yyset_column(yyget_column(yyscanner) + yyget_leng(yyscanner), yyscanner);

char* strdup(const char* str);

%}

%%

[ \t\n]					; // ignore all whitespace
[0-9]*\.[0-9]+ 			{ yylval->cval = strdup(yytext); return T_FLOAT;}
[0-9]+					{ yylval->cval = strdup(yytext); return T_INT;}
"end"					{ return BLOCK_END;  }
"return"				{ return T_RETURN; }
"def"					{ return T_DEF; }
"&"						{ return T_AND; }
"|"						{ return T_OR; }

[A-Za-z_][A-Za-z0-9_]*	{ return T_IDENT;} 

"**"						{ return T_POW;}
"//"						{ return T_SQRT;}

"+"						{ return T_PLUS;}
"-"						{ return T_MINUS;}
"*"						{ return T_MULTIPLY;}
"/"						{ return T_DIVIDE;}
"="						{ return T_EQ;}



"("						{ return T_LEFTP;}
")"						{ return T_RIGHTP;}
":"						{ return T_COLON;}
"!"						{ return T_NOT;}
.						{ return yytext[0]; }

%%

char* strdup(const char* str)
{
      char* newstr = (char*) malloc( strlen( str) + 1);

      if (newstr) {
          strcpy( newstr, str);
      }

      return newstr;
}

