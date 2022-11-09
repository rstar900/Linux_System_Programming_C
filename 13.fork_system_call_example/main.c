#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int global_data = 10;

int main()
{
    int id;
    int stack_data = 111;

    // Create a duplicate child process
    id = fork();

    switch(id)
    {
        case -1 :
            printf("Error: Cannot create a child process!\n");
            exit(-1);

        case 0 : 
            printf("(CHILD) I am the child process created with process id (%i)\n", getpid());
            global_data *= 3;
            stack_data *= 6;
            printf("(CHILD) global_data = %i, stack_data = %i, id = %i\n", global_data, stack_data, id);
            sleep(5);
            exit(0);

        default:
            printf("(PARENT) I am the parent process with process id (%i) and created child with process id (%i)\n", getpid(), id);
            sleep(5);
            printf("(PARENT) global_data = %i, stack_data = %i, id = %i\n", global_data, stack_data, id);
            exit(0);        
    }

    return 0;
}