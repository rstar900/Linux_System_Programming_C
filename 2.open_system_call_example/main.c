#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main() 
{
    // Get a file descriptor by making a file
    // Error when file already exists
    // Set permissions as 0760 
    // In Read-Write mode
    int fd = open("./example.log", O_RDWR | O_CREAT | O_EXCL, S_IRWXU | S_IRGRP | S_IWGRP);

    // -1 means error
    if (fd == -1)
    {
        printf("Cannot create the file\n");
        perror("Error");
    }
    else
    {
        printf("File creation successful!\n");
    }

    return 0;
}