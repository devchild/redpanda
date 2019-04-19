#include <redpanda.h>
#include <parser.h>
#include <scanner.h>
#include <stdio.h>
#include <ast_printer.h>

int yyparse_callback(ast_compile_unit *val) {
    printf("callback called\n");
    ast_printer * printer = ast_printer__new();
    ast_node__accept(val, printer);
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
