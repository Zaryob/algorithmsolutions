#include<stdio.h>
#include<stdlib.h>

int main()
{
    int counter1, counter2, minimum, swap_var;
    
    int array[]={21,232,34,43,23,1,56,43}; // Integer array
    
    int size = sizeof array / sizeof array[0]; // lenght of array
    
    printf("Below is the list of elements not sorted order:\n");
    
    for (counter1 = 0; counter1 < size; counter1++)
        printf("%d, ", array[counter1]);
    printf("\n");

    
    for(counter1=0;counter1<size-1;counter1++)
    {
        minimum=counter1;
        for(counter2=counter1+1;counter2<size;counter2++)
        {
            if(array[minimum]>array[counter2])
                minimum=counter2;
        }
        if(minimum!=counter1)
        {
            swap_var=array[counter1];
            array[counter1]=array[minimum];
            array[minimum]=swap_var;
        }
    }
    
    printf("Below is the list of elements sorted in ascending order:\n");
    
    for(counter1=0;counter1<size;counter1++)
        printf("%d, ",array[counter1]);
    printf("\n");
    return 0;
}