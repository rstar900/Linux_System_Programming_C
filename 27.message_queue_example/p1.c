// Need to use -lrt to link with rt lib during compilation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>

int main(int argc, char** argv)
{

    mqd_t queue; // queue descriptor
    struct mq_attr attrs; // attribute struct

    if (argc != 3)
    {
        printf("Usage: p1 </name_of_queue> <message>\n");
        exit(EXIT_FAILURE);
    }

    // Open or create a message queue
    queue = mq_open(argv[1], O_WRONLY | O_CREAT, 0660); // an attribute struct can also be passed as a pointer to give pre-defined properties

    if (queue == -1)
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // Get attributes
    if (mq_getattr(queue, &attrs) == -1)
    {
        perror("mq_getattr");
        exit(EXIT_FAILURE);
    }
    
    printf("The attributes are: (queue size: %li), (message size: %li)\n", attrs.mq_maxmsg, attrs.mq_msgsize);

    // Check if the message given by user is within the max size
    if(strlen(argv[2]) > attrs.mq_msgsize)
    {
        printf("Error: The message given is bigger than the supported message size\n");
        exit(EXIT_FAILURE);
    }

    // Send message every 2 seconds
    while(1)
    {
        printf("Sending: %s, ctrl+c to exit\n", argv[2]);

        if (mq_send(queue, argv[2], strlen(argv[2]) + 1, 0) == -1) // message priority is zero
        {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }

        sleep(2);
    }

    mq_close(queue); // mq_unlink() can be used before to delete queue in case no process is using it

    return 0;

}

    