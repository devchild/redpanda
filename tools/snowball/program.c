#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#   include "fmemopen.h"
#endif

#include "snowball.h"

static char buffer[] = "def test_function (): "
						"return 2+2 "
						"end";

int main() {
	FILE* stream = fmemopen(buffer, strlen(buffer), "r");
	if (stream == NULL)
		printf("error");
	fseek(stream, 0, SEEK_SET);

	FILE* yyout = stdout;

	do { 
		parser_parse(stream, yyout);
	} while (!feof(stream));

	scanf("continue");
	return 0;
}
