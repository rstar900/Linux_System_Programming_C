#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd, bytes_written;
    char* buf = "Wrote to file using append\n";

    // Create and append each time the same message at the end of the file

    fd = open("example.txt", O_WRONLY | O_APPEND | O_CREAT, 0774);

    if (fd < 0)
    {
        perror("Error");
        exit(1);
    }

    bytes_written = write(fd, buf, strlen(buf));
    printf("Written %d bytes.\n", bytes_written);
    
    close(fd);

    return 0;
}