// link using -lpthread while compilation

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>           
#include <sys/stat.h>

sem_t s;
int sval;
int glob = 0;

static void* threadFunc(void* arg)
{
    printf("Welcome to %s\n", (char*)arg);
    sleep(1);
    printf("Value of semaphore: %i\n", sem_getvalue(&s, &sval));

    sem_wait(&s);

    printf("%s entered critical section\n", (char*)arg);

    // increment glob by 10000
    for(int i = 0; i < 10000; i++)
        glob++;

    sem_post(&s);

    return NULL;    
}

int main()
{  

    pthread_t t1, t2, t3; 
    int sstat;
    // Open a new unnamed semaphore
    sstat = sem_init(&s, 0, 1); // pshared is 0 for threads

    if (sstat == -1)
    {
        perror("sem_init");
        exit(EXIT_FAILURE);
    }

    // initiate 3 threads t1, t2, t3
    if(pthread_create(&t1, NULL, threadFunc, (void*)"t1") == -1 || 
        pthread_create(&t2, NULL, threadFunc, (void*)"t2") == -1 || 
        pthread_create(&t3, NULL, threadFunc, (void*)"t3") == -1)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);            
    }

    // wait for each thread to end
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("The final value of glob is %i\n", glob);

    sem_close(&s); // can also use sem_unlink() before this

    return 0;
}