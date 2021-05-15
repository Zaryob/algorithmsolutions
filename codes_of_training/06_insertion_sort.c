#include <stdio.h>
#include <stdlib.h>

int main()
{
    
  int counter1, counter2, temp_val, end, temp;
    
  int array[]={21,232,34,43,23,1,56,43}; // Integer array
    
  int size = sizeof array / sizeof array[0]; // lenght of array


  printf("Below is the list of elements not sorted order:\n");

  for (counter1 = 0; counter1 < size; counter1++)
    printf("%d, ", array[counter1]);
  printf("\n");
    
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
