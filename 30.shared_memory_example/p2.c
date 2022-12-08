// Link using -lrt during the compilation

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>       
#include <fcntl.h>  

int main(int argc, char** argv)
{
    int sfd;
    struct stat len;
    char* shared_memory_pointer;


    // Step 1 -> Create or open existing shared memory file descriptor
    sfd = shm_open("/sh1", O_RDONLY, 0);

    if (sfd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

   // Step 2 -> get the size of the shared memory
    fstat(sfd, &len);

    // Step 3 -> Map this memory to virtual memory of the process
    shared_memory_pointer = mmap(NULL, (size_t)len.st_size, PROT_READ, MAP_SHARED, sfd, 0);

    if (shared_memory_pointer == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Step 4 -> Read data to this shared memory
    printf("P2: Read success! Read -> (%s)\n", shared_memory_pointer);

    // Unlink to free space
    shm_unlink("/sh1");

    return 0;

}