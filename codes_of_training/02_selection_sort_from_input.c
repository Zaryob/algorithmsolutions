#include<stdio.h>
#include<stdlib.h>

int main()
{
    int total_count, counter1, counter2, minimum, swap_var;
    int *array;
    printf("How many number you want to input?\n");

    scanf("%d", &total_count);
        
    array = (int*) malloc(total_count * sizeof(int));
    if(array == NULL)
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
    
    printf("Please enter %d integers that has to be sorted\n", total_count);
    
    for (counter1 = 0; counter1 < total_count; counter1++)
        scanf("%d", &array[counter1]);
        
    for(counter1=0;counter1<total_count-1;counter1++)
    {
        minimum=counter1;
        for(counter2=counter1+1;counter2<total_count;counter2++)
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

    for(counter1=0;counter1<total_count;counter1++)
        printf("%d, ",array[counter1]);

    printf("\n");

    return 0;
}
