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

    if (argc != 2)
    {
        printf("Usage: p2 </name_of_queue>\n");
        exit(EXIT_FAILURE);
    }

    // Open or create a message queue 
    queue = mq_open(argv[1], O_RDONLY | O_CREAT, 0660); // an attribute struct can also be passed as a pointer to give pre-defined properties

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

    // Allocate a buffer of size equal to maximum size of a single message
    char* msg_buf = calloc(1, attrs.mq_msgsize);

    // read message every 2 seconds
    while(1)
    {

        if (mq_receive(queue, msg_buf, attrs.mq_msgsize, 0) == -1) // message priority is zero
        {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }

        printf("Receiving: %s, ctrl+c to exit\n", msg_buf);

        sleep(2);
    }

    mq_close(queue); // mq_unlink() can be used before to delete queue in case no process is using it

    return 0;

}

    