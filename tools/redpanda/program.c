#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <redpanda.h>

int main(int argc, char *argv[]) {  
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
