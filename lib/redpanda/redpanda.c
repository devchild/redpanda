#include <redpanda.h>
#include <parser.h>
#include <scanner.h>
#include <stdio.h>

int yyparse_callback(struct ast_compile_unit *val) {
    printf("callback called\n");
    return 0;    
}

int parser_parse(FILE* in, FILE* out) {
	int result = 0;
    yyscan_t scanner;
    if (yylex_init(&scanner)) {
	    result = 1;
    }
    else {
      yyset_in(in, scanner);
      yyset_out(out, scanner);
    
	    result = yyparse(scanner, yyparse_callback);
    	yylex_destroy(scanner);
    }

    return (result);
}
