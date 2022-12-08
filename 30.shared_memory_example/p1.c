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
    int sfd, len;
    char* shared_memory_pointer;


    if (argc != 3)
    {
        printf("Usage: p1 <memory_size_in_bytes> <message>\n");
        exit(EXIT_FAILURE);
    }

    len = atoi(argv[1]);

    // Step 1 -> Create or open existing shared memory file descriptor
    sfd = shm_open("/sh1", O_RDWR | O_CREAT, 0660);

    if (sfd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Step 2 -> Allocate memory to this shared memory
    if(ftruncate(sfd, (off_t)len + 1) == -1)
    {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Step 3 -> Map this memory to virtual memory of the process
    shared_memory_pointer = mmap(NULL, (size_t)len + 1, PROT_WRITE, MAP_SHARED, sfd, 0);

    if (shared_memory_pointer == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Step 4 -> Write data to this shared memory
    strcpy(shared_memory_pointer, argv[2]);

    printf("P1: Write success!\n");

    return 0;

}