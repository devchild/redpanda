#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <redpanda.h>
#include <code_generator.h>

int main(int argc, char *argv[]) {
    if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename\n", argv[0] );
    }
    else
    {
        compiler__compile(argv[1]);
    }
    
    printf("Press Any Key to Continue\n");
    getchar();
	return 0;
}
