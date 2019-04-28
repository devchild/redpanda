#include <redpanda.h>
#include <parser.h>
#include <scanner.h>
#include <stdio.h>
#include <ast_printer.h>
#include <code_generator.h>

const char* assembler_output_filename;

void strip_ext(char *fname)
{
    char *end = fname + strlen(fname);

    while (end > fname && *end != '.' && *end != '\\' && *end != '/') {
        --end;
    }
    if ((end > fname && *end == '.') &&
        (*(end - 1) != '\\' && *(end - 1) != '/')) {
        *end = '\0';
    }
}

int yyparse_callback(ast_compile_unit *val) {
    printf("callback called\n");
    ast_printer * printer = ast_printer__new();
    ast_node__accept((ast_node*)val, (ast_node_visitor*)printer);


    FILE * out;
    if ((out = fopen(assembler_output_filename, "w")) != NULL) {
        code_generator * cg = code_generator__new(out);
        ast_node__accept((ast_node*)val, (ast_node_visitor*)cg);
    }
    else {
        printf("Can't open file: %s", assembler_output_filename);
    }
    fclose(out);

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

int compiler__compile(const char* fileName) {
    int ret = 0;
    char* _fileName = strdup(fileName);
    char* assembler = strdup(fileName);
    strip_ext(assembler);
    strcat(assembler, ".s");
    assembler_output_filename = strdup(assembler);

    FILE *file = fopen(_fileName, "r" );
    /* fopen returns 0, the NULL pointer, on failure */
    if ( file == 0 )
    {
        ret = 999;
        printf( "Could not open file\n" );
    }
    else
    {
        FILE* yyout = stdout;
        ret = parser_parse(file, yyout);
        if (ret == 0){
            printf("Parsing successfull.\n");
        }
        else if( ret == 1)
            printf("Error while parsing: syntax error.\n");
        else if (ret == 2)
            printf("Error while parsing: out of memory.\n");
        else
            printf("Error while parsing: unknown error.\n");
    }

    fclose(file);
    return ret;
}
