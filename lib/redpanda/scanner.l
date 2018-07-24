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
#include <unistd.h>
#include <stack.h>
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
/* Initialize LOC. */
# define LOCATION_RESET(Loc)                                \
    (Loc).first_column = (Loc).first_line = 1;              \
    (Loc).last_column =  (Loc).last_line = 1;

# define LOCATION_COLUMNS(Loc, Num)                         \
    (Loc).last_column += Num;

/* Advance of NUM lines. */
# define LOCATION_LINES(Loc, Num)                           \
    (Loc).last_column = 1;                                  \
    (Loc).last_line += Num;

/* Restart: move the first cursor to the last position. */
# define LOCATION_STEP(Loc)                                 \
    (Loc).first_column = (Loc).last_column;                 \
    (Loc).first_line = (Loc).last_line;

#define YY_USER_ACTION                                      \
    yylloc->last_column += yyleng;

int current_line_indent = 0;
struct node* head = NULL;
%}

%x INDENTSTATE COMMENTS
%option stack debug
%%
%{
  /* At each yylex invocation, mark the current position as the
     start of the next token.  */
  LOCATION_STEP (*yylloc);
%}
{string_literal}		{ /* *yylval = val_new_s(yytext); return T_STRING; */ }
"##"				    { BEGIN(COMMENTS); }
<COMMENTS>"##"			{ BEGIN(INITIAL); }
<COMMENTS>[\t ]+	    { LOCATION_STEP (*yylloc); }   // ignore all whitespace
<COMMENTS>\n+		    { LOCATION_LINES (*yylloc, yyleng); LOCATION_STEP (*yylloc); }
<COMMENTS>. 			;

"#"[^\n]*				{ /* consume //-comment */ }

[0-9]*\.[0-9]+ 			{ /* *yylval = val_new_int(yytext); return T_FLOAT; */ return T_FLOAT; }
[0-9]+					{ /* *yylval = val_new_int(yytext); return T_INT; */ return T_INT; }
"end"					{ return BLOCK_END;  }
"return"				{ return T_RETURN; }
"else"					{ return ELSE; }
"def"					{ return T_DEF; }
"if"					{ return T_IF; }

[A-Za-z_][A-Za-z0-9_]*	{ yylval->identifier = strdup(yytext); return T_IDENT; }

"&"						{ return T_AND; }
"|"						{ return T_OR; }
"?"						{ return T_QM; }

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
";"						{ return T_SCOLON; }
"!"						{ return T_NOT; }

<INITIAL>[ \t\r]+ 					{
                                        LOCATION_STEP (*yylloc);
										/* gobble up white-spaces */
									}
<INITIAL>\n               			{
										yyless(0);
                                        LOCATION_COLUMNS(*yylloc, -1)
                                        BEGIN(INDENTSTATE);
                                       	// return (token::EOL);
                                    }
<INITIAL><<EOF>>           			{
										if (!empty(head))
                                        {
                                            int element;
                                        	head = pop(head, &element);
                                            unput(0);
                                            return(T_DEDENT);
                                        }
                                        else
                                        {
                                        	yyterminate();
                                        }
                                    }
<INITIAL>. 							{
										/* pass all other characters up to bison */
									    return yytext[0];
									}
<INDENTSTATE>[ ]+ 					{
										current_line_indent += yyleng;
									}
<INDENTSTATE>\n 					{
                                        LOCATION_LINES (*yylloc, yyleng); 
                                        LOCATION_STEP (*yylloc);
										current_line_indent = 0;
									}
<INDENTSTATE><<EOF>>       			{
										if (!empty(head))
                                        {
                                            int element;
                                            head = pop(head, &element);
                                            unput(0);
                                            return(T_DEDENT);
                                        }
                                        else
                                        {
                                        	yyterminate();
                                        }
                                    }
<INDENTSTATE>.                      {
										yyless(0);
                                        LOCATION_COLUMNS(*yylloc, -1)
                                        int current_indent = current_line_indent;
                                        int previous_indent = 0;
                                        if (!empty(head))
                                            previous_indent = head->data;

                                        if (current_indent > previous_indent) {
                                            head = push(head, current_indent);
	                                        return (T_INDENT);
                                        }

                                        if (current_indent < previous_indent) {
                                            int element;
                                        	head = pop(head, &element);
	                                        return (T_DEDENT);
                                        }
                                        BEGIN(INITIAL);
                                    }
%%
