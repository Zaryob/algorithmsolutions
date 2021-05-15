#include <stdio.h>
#include <stdlib.h>

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
  int counter;
    
  int array[]={21,232,34,43,23,1,56,43}; // Integer array
    
  int size = sizeof array / sizeof array[0]; // lenght of array

  algo_merge_sort(array,0,size-1);
    
  printf("Below is the list of elements not sorted order:\n");

  for (counter = 0; counter < size; counter++)
    printf("%d, ", array[counter]);
  printf("\n");
    
  printf("Below is the list of elements sorted in ascending order:\n");
  
  for(counter=0;counter<size;counter++)
    printf("%d ",val[counter]);
  
  printf("\n");

  return 0;
}