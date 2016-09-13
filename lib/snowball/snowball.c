#include <snowball.h>
#include "parser.h"
#include "scanner.h"


int parser_parse(FILE* in, FILE* out) {
    
    int result;
    yyscan_t scanner;
    yylex_init(&scanner);
    yyset_in(in, scanner);
    yyset_out(out, scanner);
    
    
    result = (yyparse(scanner));
    yylex_destroy(scanner);
    return (result);
}