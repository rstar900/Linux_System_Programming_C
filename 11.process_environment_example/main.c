#include <stdio.h>
#include <stdlib.h>

// An array of strings holding environment variables
// in "environment_variable = value" fashion
extern char** environ;

void another_func()
{
    printf("The value of PING is %s inside another_func()\n", getenv("PING"));
}

int main(int argc, char** argv)
{
    /* Print all environment variables along with their values for this process
    char** ep;

    for(ep = environ; *ep != NULL; ep++)
    {
        printf("(%s)\n", *ep);
    }

    return 0;
    */

    //create an environment variable and it is accesible in every function
    putenv("PING");

    // set the value of PING to PONG
    setenv("PING", "PONG", 0);

    // retrieve value of PING in main()
    printf("The value of PING is %s inside main()\n", getenv("PING"));


    // Trying to retrieve it in another function
    another_func(); 

    return 0;
}