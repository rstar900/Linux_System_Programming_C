#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
int main(int argc, char** argv)
{
    int cpid, retval, cpid_ret;

    char* argvec[10] = {"arg1", "arg2", "arg3", NULL};
    char* environvec[10] = {"ENV_VAR_1=CLASS_1", "ENV_VAR_2=CLASS_2", "ENV_VAR_3=CLASS_3", NULL};

    printf("Welcome to P1 with pid (%i)\n", getpid());

    cpid = fork();

    if (cpid == -1)
    {
        perror("Error");
        exit(-1);
    }

    else if (cpid == 0)
    {
        printf("Child process with pid (%i) before exec\n", getpid());
        execve("./p2", argvec, environvec);
        printf("This will not be printed\n");
    }

    else
    {
        printf("Parent process with pid (%i)\n", getpid());
        cpid_ret = wait(&retval);
        printf("Child process with pid (%i) returned with status (%i)\n", cpid_ret, retval);
    }

    return 0;
}