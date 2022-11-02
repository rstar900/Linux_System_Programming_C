#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    int fd, newfd;

    fd = open("./example.log", O_RDWR | O_CREAT, 0767);

    // check for error in opening the file
    if (fd == -1)
    {
        printf("Cannot open file error no: %d\n", errno);
        perror("Error");
        exit(1);
    }

    // Close the STDIO (1), so that it's file descriptor becomes available for our file
    close(1);

    // duplicate the file descriptor of the file to 1, so printf will print to file
    // instead of screen
    newfd = dup(fd);

    printf("This will print to example.log instead of the screen :)\n");

    return 0;
}