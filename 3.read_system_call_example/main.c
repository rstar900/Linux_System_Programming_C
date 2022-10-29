#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd, bytes_read;
    char buffer[30] = {};

    fd = open("example.txt", O_RDONLY);

    if (fd < 0)
    {
        perror("Error");
        exit(1);
    }

    // Read 10 bytes
    bytes_read = read(fd, buffer, 10);
    buffer[bytes_read] = '\0';

    printf("Read %d bytes\n", bytes_read);
    printf("content: <%s>\n", buffer);

    // Read next 30 bytes
    bytes_read = read(fd, buffer, 30);
    buffer[bytes_read] = '\0';

    printf("\nRead %d bytes\n", bytes_read);
    printf("content: <%s>\n", buffer);

    // Should reach EOF
    bytes_read = read(fd, buffer, 10);
    buffer[bytes_read] = '\0';

    printf("\nRead %d bytes\n", bytes_read);
    printf("content: <%s>\n", buffer); 

    if(bytes_read == 0)
    {
        printf("Reached EOF\n");
    }  

    return 0;
}