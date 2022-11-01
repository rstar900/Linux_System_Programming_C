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

    // No neec of closing STDIO in this example, as dup2 does that for us
    // duplicate the file descriptor of the file to 1, so printf will print to file
    // instead of screen
    newfd = dup2(fd, 1);

    printf("This will print to example.log instead of the screen :)\n");

    return 0;
}