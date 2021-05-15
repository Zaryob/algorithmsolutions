#include <stdio.h>
#include <stdlib.h>

int main()
{
  
  int counter, total_count, end, temp;
    
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

  for (counter = 0; counter < total_count; counter++)
    scanf("%d", &array[counter]);
    
  for(counter1=1;counter1<=size-1;counter1++)
    {
      temp_val=array[counter1];
      counter2=counter1-1;
      while((temp_val<array[counter2])&&(counter2>=0))
	{
	  array[counter2+1]=array[counter2];
	  counter2=counter2-1;
	}
      array[counter2+1]=temp_val;
    }
  printf("\n Output generated after using insertion sort \n");
  for(counter1=0;counter1<size;counter1++)
    {
      printf("%d ",array[counter1]);
    }
  return 0;
}
