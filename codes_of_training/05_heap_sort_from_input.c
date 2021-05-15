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

  array[0]=total_count;
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
  for(counter=1;counter<=total_count;counter++)
    printf("%d ",array[counter]);

  printf("\n");

}
