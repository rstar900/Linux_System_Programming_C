#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void signal_handler(int signo)
{
    printf("Alarm expired!\n");
    alarm(2);
}

int main()
{
    // Register the signal_handler callback function with the corresponding alarm signal
    if (signal(SIGALRM, signal_handler) == SIG_ERR) // Instead of signal_handler, SIG_IGN -> ignore, SIG_DFLT -> default signal handler
    {
        fprintf(stderr, "The alarm signal could not be registered to its handler\n");
        exit(EXIT_FAILURE);
    }

    // Set the alarm to be expired in 2 seconds
    alarm(2);

    // Keep the program running
    while(1);

    return 0;
}