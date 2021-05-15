#include <stdio.h>
#include <stdlib.h>

int main()
{
    int counter, counter1, swap_var;
    
    int array[]={21,232,34,43,23,1,56,43}; // Integer array
    
    int size = sizeof array / sizeof array[0]; // lenght of array
    
    printf("Below is the list of elements not sorted order:\n");
    
    for (counter = 0; counter < size; counter++)
        printf("%d, ", array[counter]);
    printf("\n");
    for (counter = 0 ; counter < size - 1; counter++)
    {
        for (counter1 = 0 ; counter1 < size - counter - 1; counter1++)
        {
            if (array[counter1] > array[counter1+1])
                {
                    swap_var          = array[counter1];
                    array[counter1]   = array[counter1+1];
                    array[counter1+1] = swap_var;
                }
        }
    }
    
    printf("Below is the list of elements sorted in ascending order:\n");
    
    for (counter = 0; counter < size; counter++)
        printf("%d, ", array[counter]);
    
    printf("\n");

    return 0;
}
