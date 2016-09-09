#include <stdio.h>
#include <stdlib.h>

#include "snowball.h"

int main() {
	FILE* yyin = stdin;
	FILE* yyout = stdout;

	do { 
		parser_parse(yyin, yyout);
	} while(!feof(yyin));
	return 0;
}
