#include <unistd.h>
#include <string.h>

int main()
{
    // variables
    int msg_len;
    char msg_buf[100];

    // copy message string into a buffer
    strncpy(msg_buf, "This code uses write() syscall instead of printf() standard library function.\n", 99);

    // extract the length of the string in the buffer
    msg_len = strlen(msg_buf);

    // use the write() syscall to print output to stdout (1) [stdin -> 0, stderr -> 2]
    write(1, msg_buf, msg_len);

    return 0;

}