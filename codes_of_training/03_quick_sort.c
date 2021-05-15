#include <stdio.h>
#include <stdlib.h>

void quicksort_method(int array[], int low, int high)
{
  int pivot, value1, value2, temp;
  if (low < high)
    {
      pivot = low;
      value1 = low;
      value2 = high;
      while (value1 < value2)
    {
      while (array[value1] <= array[pivot] && value1 <= high)
        {
          value1++;
        }
      while (array[value2] > array[pivot] && value2 >= low)
        {
          value2--;
        }
      if (value1 < value2)
        {
          temp = array[value1];
          array[value1] = array[value2];
          array[value2] = temp;
        }
    }
      temp = array[value2];
      array[value2] = array[pivot];
      array[pivot] = temp;
      quicksort_method(array, low, value2 - 1);
      quicksort_method(array, value2 + 1, high);
    }
}

int main()
{
  int counter;
    
  int array[]={21,232,34,43,23,1,56,43}; // Integer array
    
  int size = sizeof array / sizeof array[0]; // lenght of array

  printf("Below is the list of elements not sorted order:\n");

  for (counter = 0; counter < size; counter++)
    printf("%d, ", array[counter]);
  printf("\n");
    
  quicksort_method(array, 0, size - 1);

  printf("Below is the list of elements sorted in ascending order:\n");

  for (counter = 0; counter < size; counter++)
  {
    printf("%d ", array[counter]);
  }
  printf("\n");
  return 0;
}

