#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <redpanda.h>
#include <ast_node.h>
#include <ast_binary_expression.h>

int main(int argc, char *argv[]) {
    
    AstNode* node = g_object_new(AST_TYPE_NODE, NULL);
    AstBinaryExpression* bin_exp = g_object_new(AST_TYPE_BINARY_EXPRESSION, NULL);

    GValue strval = G_VALUE_INIT;
    g_value_init (&strval, G_TYPE_STRING);
    g_value_set_string (&strval, "dit is een test");
    g_object_set_property (G_OBJECT (node), "Text", &strval);
    g_value_unset (&strval);

    g_value_init (&strval, G_TYPE_STRING);
    g_object_get_property (G_OBJECT (node), "Text", &strval);
    g_print ("text: %s\n", g_value_dup_string(&strval));

    GValue strval2 = G_VALUE_INIT;
    g_value_init (&strval2, G_TYPE_STRING);
    g_value_set_string (&strval2, "dit is een tweede test");
    g_object_set_property (G_OBJECT (bin_exp), "Text", &strval2);
    g_value_unset (&strval2);

    g_value_init (&strval2, G_TYPE_STRING);
    g_object_get_property (G_OBJECT (bin_exp), "Text", &strval2);
    g_print ("text: %s\n", g_value_dup_string(&strval2));

    if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename\n", argv[0] );
        int i = 0;
    }
    else
    {
        // We assume argv[1] is a filename to open
        FILE *file = fopen( argv[1], "r" );
    
        /* fopen returns 0, the NULL pointer, on failure */
        if ( file == 0 )
        {
            printf( "Could not open file\n" );
        }
        else
        {
            FILE* yyout = stdout;
            int ret = parser_parse(file, yyout);
            if (ret == 0)
                printf("Parsing successfull.\n");
            else if( ret == 1)
                printf("Error while parsing: syntax error.\n");
            else if (ret == 2)
                printf("Error while parsing: out of memory.\n");
            else
                printf("Error while parsing: unknown error.\n");
        }
        
        fclose(file);
    }
    
    printf("Press Any Key to Continue\n");
    getchar();
	return 0;
}
