#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int a_ext = 1; /* Initialised Data Section         */
int b_ext;     /* Uninitialised Data Section (BSS) */

void add(int a, int b)
{
    static int count = 0; /* Static data stored in data section */
    int result = a + b;   /* Stack frame of add()               */

    ++count;
    printf("Result: %d\n", result);
    printf("add() is called %d time(s)\n", count);

    return;
}

int main()
{
    // a and b both go into stack frame for main()
    int a = 12;
    int b;

    char* pstr = malloc(10);   /* pstr goes into stack frame for main(), but it points to location in heap */
    char* pstr2 = "*Strong*";  /* pstr2 goes in stack frame for main() but what it points to is in text section */
    char pbuf[10] = {"Hello"}; /* pbuf and the string it points to, both go into stack frame for main() */

    strcpy(pstr, "*PSTR*");     // Success
    //strcpy(pstr2, "*PSTR2*"); // Fail (segmentation fault during runtime), data in text section is read only
    strcpy(pbuf, "*PSTR3*");    // Success

    printf("Content of pstr : <%s>\n", pstr);
    printf("Content of pstr2 : <%s>\n", pstr2);
    printf("Content of pbuf : <%s>\n", pbuf);

    b = 13; // Stack frame data access
    b_ext = 2; // Accessing data in data section (BSS)

    // Due to static variable stored in add function, it should increment in data section
    printf("\n");
    add(a,b);
    printf("\n");
    add(a_ext, b_ext);

    return 0;
}