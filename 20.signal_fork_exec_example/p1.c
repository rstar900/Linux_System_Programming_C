#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

static void signal_handler(int signo)
{
    printf("Parent: SIGUSR1 received!\n");
}

int main()
{

    pid_t cpid;

    // Register the signal_handler callback function with the corresponding user-defined signal 1
    if (signal(SIGUSR1, signal_handler) == SIG_ERR) // Instead of signal_handler, SIG_IGN -> ignore, SIG_DFLT -> default signal handler
    {
        fprintf(stderr, "SIGUSR1 could not be registered to its handler\n");
        exit(EXIT_FAILURE);
    }

    else if ((cpid = fork()) == -1)
    {
        fprintf(stderr, "Cannot fork\n");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    {
        printf("Child: Before executing execl\n");

        if (execl("./p2", "Welcome", "to", "p2", NULL) == -1)
        {
            fprintf(stderr, "Cannot do execl\n");
            exit(EXIT_FAILURE);
        }

    }

    else
    {
        printf("Parent: Before sending SIGUSR2 to child (PID = %i)\n", cpid);
        sleep(5);
        printf("Parent: Sending SIGUSR2 to child (PID = %i)\n", cpid);
        kill(cpid, SIGUSR2);
        wait(NULL);
        printf("Parent: Exiting....\n");
    }

    return 0;
}