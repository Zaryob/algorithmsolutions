#include <stdio.h>
#include <stdlib.h>

void set_down(int array[],int counter)
{
  int counter2,temp,size,flag=1;
  size=array[0];
  while(2*counter<=size && flag==1)
    {
      counter2=2*counter;
      if(counter2+1<=size && array[counter2+1] > array[counter2])
	    counter2=counter2+1;
      if(array[counter] > array[counter2])
	    flag=0;
      else
	  {
	    temp=array[counter];
	    array[counter]=array[counter2];
	    array[counter2]=temp;
	    counter=counter2;
	  }
    }
}

void form(int array[])
{
  int counter,size;
  size=array[0];
  for(counter=size/2;counter>=1;counter--)
    set_down(array,counter);
}


int main()
{
  int counter, total_count, size, end, temp;
    
  int array[]={21,232,34,43,23,1,56,43}; // Integer array
    
  int size = sizeof array / sizeof array[0]; // lenght of array


  printf("Below is the list of elements not sorted order:\n");

  for (counter = 0; counter < size; counter++)
    printf("%d, ", array[counter]);
  printf("\n");
    
  array[0]=size;
  form(array);
  while(array[0] > 1)
    {
      end=array[0];
      temp=array[1];
      array[1]=array[end];
      array[end]=temp;
      array[0]--;
      set_down(array,1);
    }
  printf("\n Output generated after using heap sort \n");
  for(counter=1;counter<=size;counter++)
    printf("%d ",array[counter]);
  printf("\n");
}
