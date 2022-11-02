#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("The process id is %d\n\n", getpid());
    printf("The parent (creator) process id is %d\n\n", getppid());

    return 0;
}