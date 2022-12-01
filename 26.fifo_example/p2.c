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

    // open a FIFO
    ffd = open(fpath, O_RDONLY);

    printf("P2: You will see message below...., ctrl+c to exit\n\n");

    // read from FIFO
    while(1)
    {
        
        if(read(ffd, buf, 100) != 0) // if P1 is still writing
            printf("From P1: %s\n", buf);
 
    }
    
    close(ffd);
    return 0;

}