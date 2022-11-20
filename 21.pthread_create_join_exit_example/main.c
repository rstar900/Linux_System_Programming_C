/*
Note:
Build with -lpthread as an addition parameter for linking pthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 100

static void* threadFunc(void* args)
{
    printf("threadFunc: Welcome!\n");

    int counter;

    for (counter = 0; counter < MAX; counter++);
        
    sleep(5);

    printf("threadFunc: Counter = %i, Pid = %i\n, arg = %s\n", counter, getpid(), (char*)args);
    printf("threadFunc: Bye!\n");   

    char* result = "Bye from the new thread!";

    // Exit from thread and return the arg string back
    pthread_exit((void*)result);
}

int main()
{
    void* retval; // return value of the thread
    pthread_t tid;

    printf("mainThread: Welcome!\n");

    // Create a thread and call it, tid will get thread id and tstatus = 0 if no error is there
    if(pthread_create(&tid, NULL, threadFunc, "Hello from the new thread!") != 0)
    {
        perror("pthread_create error:");
    }

    // Wait for thread return and store return value in retval
    if (pthread_join(tid, &retval) != 0)
    {
        perror("pthread_join error:");
    }

    printf("mainThread: thread exited with return value = %s\n", (char*)retval);
    printf("mainThread: Bye!\n");

    // If called without join, the child thread keeps running, but return kills it
    //pthread_exit(NULL);
    return 0;
}