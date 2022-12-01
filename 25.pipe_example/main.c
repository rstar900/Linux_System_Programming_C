#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 80

int main(int argc, char** argv)
{
    char msg_buf[BUFFER_SIZE];

    int pfd[2]; // pfd[0] -> read end, pfd[1] -> write end

    // Create a pipe
    if (pipe(pfd) == -1)
    {
        perror("Parent: Pipe_Error");
        exit(1);
    }

    // Create a child process
    switch(fork())
    {
        case -1:
            perror("Parent: Fork_Error");
            exit(1);
            break;

        // Child process
        case 0:
            if (close(pfd[1]) == -1) // close the write end
            {
                perror("Child");
                exit(1);
            } 
            while(1)
            {
                int r_status;

                if((r_status = read(pfd[0], msg_buf, BUFFER_SIZE)) == -1)
                {
                    perror("Child");
                    exit(1);
                }
                else if (r_status == 0)
                {
                    printf("Child: Parent closed the pipe, exiting....\n"); 
                    exit(0);
                }
                else
                {
                    printf("Child: received -> (%s)\n", msg_buf);
                    exit(0);
                }
                
            }
            break;

        // Parent process
        default:
            printf("Parent: Sending %s to child\n", argv[1]);
            if (close(pfd[0]) == -1) // close the read end
            {
                perror("Parent");
                exit(1);
            }
           
            if (write(pfd[1], argv[1], BUFFER_SIZE) == -1) 
            {
                perror("Parent");
                exit(1);
            }
            /*
              sleep(2);
            if (write(pfd[1], argv[1], BUFFER_SIZE) == -1) // if child would have closed the reading end, SIGPIPE would have killed parent
            {
                perror("Parent");
                exit(1);
            } */
            
            printf("Parent: Sent and exiting....\n");
            sleep(1); 
            close(pfd[1]);     
    }
    
}