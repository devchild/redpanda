#include <stdio.h>
#include <stdlib.h>

extern FILE* yyin;
extern int yyparse();

int main() {
	yyin = stdin;
	do { 
		yyparse();
	} while(!feof(yyin));
	return 0;
}
