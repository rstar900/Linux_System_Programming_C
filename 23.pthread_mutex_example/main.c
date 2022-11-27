// compile with lpthread
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int count = 0;

void* threadFunc1(void* args)
{
    printf("threadFunc1: Welcome!\n");

    // Need to lock mutex before modifying global variable count and unlock afterwards
    pthread_mutex_lock(&mtx);
    for (int i = 0; i < 10000; i++){count++;};
    pthread_mutex_unlock(&mtx);
    
}

void* threadFunc2(void* args)
{
    printf("threadFunc2: Welcome!\n");

    // Need to lock mutex before modifying global variable count and unlock afterwards
    pthread_mutex_lock(&mtx);
    for (int i = 0; i < 10000; i++){count++;};
    pthread_mutex_unlock(&mtx);
    
}

int main()
{
    pthread_t tid, tid2;
    
    pthread_create(&tid, NULL, threadFunc1, NULL);
    pthread_create(&tid2, NULL, threadFunc2, NULL);

    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);

    printf("The value of count after execution of 2 threads is: %i\n", count);

    return 0;
}