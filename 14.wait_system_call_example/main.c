#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    // Store child process id and return value
    int cpid, cpid2, retval, cpid_wait_ret;

    cpid = fork();

    if (cpid == -1)
    {
        perror("Error");
        exit(1);
    }
    else if (cpid == 0)
    {
        printf("Welcome to the 1st child process with pid %i\n", getpid());
        sleep(10);
        printf("1st child process finished.\n");
        exit(3);
    }
    else
    {
        // fork another process
        printf("Parent process before forking another process\n");
        cpid2 = fork();
        
        if(cpid2 == -1)
        {
            perror("Error");
            exit(1);
        }
        else if (cpid2 == 0)
        {
            printf("Welcome to the 2nd child process with pid %i\n", getpid());
            sleep(5);
            printf("2nd child process finished.\n");
            exit(6);
        }
        else
        {
            // Wait for one of the processes to exit
            cpid_wait_ret = wait(&retval); 
            printf("Child process with pid (%i) exited with status (%i)\n", cpid_wait_ret, retval);
            printf("Parent process finished.\n");
        }
    }

    return 0;
}