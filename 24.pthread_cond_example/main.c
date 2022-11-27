// compile with lpthread
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // condition variable

int count = 0;
int countModified = 0;

void* threadFunc1(void* args) // producer
{
    printf("threadFunc1: Welcome!\n");

    // Need to lock mutex before modifying global variable count and unlock afterwards
    pthread_mutex_lock(&mtx);
    for (int i = 0; i < 10000; i++){count++;};
    countModified = 1;
    pthread_mutex_unlock(&mtx);
    
    pthread_cond_signal(&cond); // signal using condition variable that operation is finished
    
}

// We make sure that threadFunc2 uses or modifies count only after threadFunc1 using condition variable
void* threadFunc2(void* args) // consumer
{
    printf("threadFunc2: Welcome!\n");

    // Need to lock mutex before accessing  global variable count and unlock afterwards
    pthread_mutex_lock(&mtx);
    
    if (countModified == 0) // if threadFunc1 has not executed yet
    {
        // Wait for signal from threadFunc1 and unlock mutex for it
        pthread_cond_wait(&cond, &mtx);
    }

    printf("threadFunc2: got a value of %i from threadFunc1\n", count);

    // Now modify count
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