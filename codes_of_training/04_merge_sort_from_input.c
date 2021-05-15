#include<stdio.h>
#include<stdlib.h>

void perfrom_merge(int val[],int counter11,int counter12,int counter22,int counter21)
{
  int temp_val[50];
  int c1,c2,c3;
  c1=counter11;
  c2=counter22;
  c3=0;
  while(c1<=counter12 && c2<=counter21)
    {
      if(val[c1]<val[c2])
	temp_val[c3++]=val[c1++];
      else
	temp_val[c3++]=val[c2++];
    }
  while(c1<=counter12)
    temp_val[c3++]=val[c1++];
  while(c2<=counter21)
    temp_val[c3++]=val[c2++];
  for(c1=counter11,c2=0;c1<=counter21;c1++,c2++)
    val[c1]=temp_val[c2];
}


void algo_merge_sort(int val[],int counter1,int counter2)
{
  int mid;
  if(counter1<counter2)
    {
      mid=(counter1+counter2)/2;
      algo_merge_sort(val,counter1,mid);
      algo_merge_sort(val,mid+1,counter2);
      perfrom_merge(val,counter1,mid,mid+1,counter2);
    }
}



int main()
{
  int counter, total_count;
    
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

    
  algo_merge_sort(array,0,total_count-1);
    
  printf("Below is the list of elements sorted in ascending order:\n");
  
  for(counter=0;counter<total_count;counter++)
    printf("%d ",array[counter]);
  printf("\n");
  return 0;
}