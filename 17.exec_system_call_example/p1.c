#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    char* argvec[10] = {"arg1", "arg2", "arg3", NULL};
    char* environvec[10] = {"ENV_VAR_1=CLASS_1", "ENV_VAR_2=CLASS_2", "ENV_VAR_3=CLASS_3", NULL};

    printf("Welcome to P1 with pid (%i)\n", getpid());

    // execl -> takes command line arguments explicitly
    // execv -> takes command line arguments as array
    // execve -> same as execv but also takes environment variable array
    //execl("./p2", "arg1", "arg2", "arg3", NULL); 
    //execv("./p2", argvec);
    execve("./p2", argvec, environvec);

    printf("This will not be printed\n");
    return 0;
}