#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int age;
    int salary;

} Employee; 

int main()
{
    // Allocate an array of 10 Employee objects in heap
    Employee* employees = (Employee*) malloc (10 * sizeof(Employee)); 

    // Allocation using calloc would look like this
    //Employee* employees = (Employee*) calloc (10, sizeof(Employee));

    // Check if memory is allocated properly
    if (employees == NULL)
    {
        printf("Error allocating memory, exiting ...\n");
        exit(1);
    }

    // Give values to 10 members
    for (int i = 0; i < 10; i++)
    {
        employees[i].age = i;
        employees[i].salary = i * 1000; 
    }

    // Print before reallocating

    printf("Before reallocation\n");

    for (int i = 0; i < 10; i++)
    {
        printf("Employee (%i) age : %i\n", i, employees[i].age);
        printf("Employee (%i) salary : %i\n", i, employees[i].salary); 
    }

    printf("\nAfter reallocation\n");

    employees = realloc(employees, 15 * sizeof(Employee));

   for (int i = 10; i < 15; i++)
    {
        employees[i].age = i;
        employees[i].salary = i * 1000; 
    }    

       for (int i = 0; i < 15; i++)
    {
        printf("Employee (%i) age : %i\n", i, employees[i].age);
        printf("Employee (%i) salary : %i\n", i, employees[i].salary); 
    }

    // Free the memory taken up by employees for reuse by another thing
    free(employees);

    return 0;

}