#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd, offset = 5;
    char* replace_word = "Mohan";

    // Open a file named author.txt
    fd = open("author.txt", O_WRONLY);

    // Check for error in opening file
    if (fd == -1)
    {
        perror("Error");
        exit(1);
    }

    // set the read/write pointer to point to the starting of Rohan (END - 5)
    lseek(fd, -offset, SEEK_END);

    //Now replace Rohan by Mohan
    write(fd, replace_word, strlen(replace_word));

    close(fd);

    return 0;
}