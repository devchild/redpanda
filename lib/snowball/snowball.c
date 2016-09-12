#include <snowball.h>
#include "parser.h"

extern FILE* yyin;
extern FILE* yyout;

int parser_parse(FILE* in, FILE* out) {
	yyin = in;
	yyout = out;
	return yyparse();
}