// link using -lpthread while compilation

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>           
#include <sys/stat.h>

int main()
{
    sem_t* s;
    int sval;

    // Open a new named semaphore with read/write permission, and create one in case it does not exist (initial value 2)
    s = sem_open("/myNamedSemaphore", O_RDWR | O_CREAT, 0660, 2);

    if (s == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Print the value of the semaphore
    sem_getvalue(s, &sval);

    printf("Value of semaphore: %i\n", sval);

    // Wait before the critical section is entered and then decrement the semaphore
    sem_wait(s);

    printf("P2 entering critical section\n");
    sleep(5);
    printf("P2 exiting critical section\n");

    // release (or simply increment) the semaphore
    sem_post(s);

    sem_close(s); // can also use sem_unlink() before this

    return 0;
}