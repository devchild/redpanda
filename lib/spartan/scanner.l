%option bison-bridge
%option bison-locations
%option nounistd
%option reentrant
%option noyywrap
%option yylineno

hex_digit              				[0-9A-Fa-f]

uni_esc_seq1        			   	\\u{hex_digit}{4}
uni_esc_seq2           				\\U{hex_digit}{8}
uni_esc_seq            				{uni_esc_seq1}|{uni_esc_seq2}

simple_esc_seq         				\\[\'\"\\0abfnrtv]
hex_esc_seq            				\\x{hex_digit}{1,4}
single_string_char     				[^\\\"]
reg_string_char        				{single_string_char}|{simple_esc_seq}|{hex_esc_seq}|{uni_esc_seq}
regular_string         				\"{reg_string_char}*\"
single_verbatim_char   				[^\"]
quote_esc_seq          				\"\"
verb_string_char       				{single_verbatim_char}|{quote_esc_seq}
verbatim_string        				@\"{verb_string_char}*\"
string_literal         				{regular_string}|{verbatim_string}

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

#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line; \
    yylloc->first_column = yylloc->last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
        if(yytext[i] == '\n') { \
            yylloc->last_line++; \
            yylloc->last_column = 0; \
        } \
        else { \
            yylloc->last_column++; \
        } \
    }

char* strdup(const char* str);

%}

%x COMMENTS

%%



{string_literal}		{ yylval->cval = strdup(yytext); return T_STRING; }
"##"				    { BEGIN(COMMENTS); }
<COMMENTS>"##"			{ BEGIN(INITIAL); }
<COMMENTS>[ \t\n]		; // ignore all whitespace
<COMMENTS>. 			;

"#"[^\n]*				{ /* consume //-comment */ }

[ \t\n]					; // ignore all whitespace
[0-9]*\.[0-9]+ 			{ yylval->cval = strdup(yytext); return T_FLOAT; }
[0-9]+					{ yylval->cval = strdup(yytext); return T_INT; }
"end"					{ return BLOCK_END;  }
"return"				{ return T_RETURN; }
"else"					{ return ELSE; }
"def"					{ return T_DEF; }
"if"					{ return T_IF; }
"&"						{ return T_AND; }
"|"						{ return T_OR; }
"?"						{ return T_QM; }

[A-Za-z_][A-Za-z0-9_]*	{ return T_IDENT; }

"**"					{ return T_POW; }
"//"					{ return T_SQRT; }

"||"					{ return OP_OROR; }
"&&"					{ return OP_ANDAND; }

"<="					{ return OP_LESS_THAN_OR_EQUAL; }
">="					{ return OP_GREATER_THAN_OR_EQUAL; }
">>"					{ return OP_SHIFT_RIGHT; }
"<<"					{ return OP_SHIFT_LEFT; }
"!="					{ return T_NEQ; }


"+"						{ return T_PLUS; }
"-"						{ return T_MINUS; }
"*"						{ return T_MULTIPLY; }
"/"						{ return T_DIVIDE; }
"="						{ return T_EQ; }
">"						{ return T_GT; }
"<"						{ return T_LT; }
"^"						{ return T_XOR; }

"("						{ return T_LEFTP; }
")"						{ return T_RIGHTP; }
":"						{ return T_COLON; }
"!"						{ return T_NOT; }
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