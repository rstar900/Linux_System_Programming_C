#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    // Print all command line args
    for (int i = 0; i < argc; i++)
    {
        printf ("(%d)th argument is %s\n", i, argv[i]);
    }

    printf("\n");

    // If 1st arg is add, then add, If sub, then subtract. else throw error
    if (strcmp(argv[1], "add") == 0)
    {
        printf("Addition of %i and %i gives %i\n", atoi(argv[2]), atoi(argv[3]), atoi(argv[2]) + atoi(argv[3]));
    }
    else if (strcmp(argv[1], "sub") == 0)
    {
        printf("Subtraction of %i and %i gives %i\n", atoi(argv[2]), atoi(argv[3]), atoi(argv[2]) - atoi(argv[3]));
    }
    else
    {
        printf("Invalid command\n");
    }

    return 0;
}