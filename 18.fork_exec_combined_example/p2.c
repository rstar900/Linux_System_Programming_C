#include <stdio.h>
#include <unistd.h>

extern char** environ;

int main(int argc, char** argv)
{

    printf("Welcome to P2 with pid (%i)\n", getpid());

    printf("\n");

    // Printing the args
    for (int i = 0; argv[i] != NULL; i++)
    {
        printf("arg[%i] = %s\n", i, argv[i]);
    }

    printf("\n");

    // Printing the args
    for (int i = 0; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }

    printf("\nGonna sleep for a while now\n");
    sleep(10);
    printf("Exiting....\n");

    return 0;
}