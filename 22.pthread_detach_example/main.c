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

    // Detach the thread, so if it ends before main thread, no pthread_join is required to clean up otherwise it will be zombie
    pthread_detach(pthread_self());

    int counter;

    for (counter = 0; counter < MAX; counter++);
        
    sleep(2);

    printf("threadFunc: Counter = %i, Pid = %i\n, arg = %s\n", counter, getpid(), (char*)args);
    printf("threadFunc: Bye!\n");   

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

    // If pthread_cancel is used, it will kill the thread
    //pthread_cancel(tid);
    sleep(5);

    printf("mainThread: Bye!\n");

    // If called without join, the child thread keeps running, but return kills it
    //pthread_exit(NULL);
    return 0;
}