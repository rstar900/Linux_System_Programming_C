#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void signal_handler(int signo)
{
    printf("Child: SIGUSR2 received!\n");   
    sleep(5);
    printf("Child: Sending SIGUSR1 to parent\n");
    kill(getppid(), SIGUSR1);
    printf("Child: Exiting....\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
    // Register the signal_handler callback function with the user-defined signal 2
    if (signal(SIGUSR2, signal_handler) == SIG_ERR) // Instead of signal_handler, SIG_IGN -> ignore, SIG_DFLT -> default signal handler
    {
        fprintf(stderr, "SIGUSR2 could not be registered to its handler\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; argv[i] != NULL; i++)
        printf("%s\n", argv[i]);

    printf("\n");

    // Keep waiting for SIGUSR2 from parent
    while(1);
}