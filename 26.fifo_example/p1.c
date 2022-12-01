#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    
    char buf[100];
    char* fpath = "./myFifo";
    int ffd;

    // make a FIFO with 660 as permission
    mkfifo(fpath, 0660);

    // Open FIFO for write
    ffd = open(fpath, O_WRONLY);
   
    // Write from stdin to the fifo
    while(1)
    {
        printf("P1: Type something...., ctrl+c to exit\n\n");
        fgets(buf, 100, stdin);
        write(ffd, buf, strlen(buf) + 1);
    }
    
    close(ffd);
    return 0;
}