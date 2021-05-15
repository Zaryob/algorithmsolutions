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

    
  quicksort_method(array, 0, total_count - 1);

  printf("Below is the list of elements sorted in ascending order:\n");

  for (counter = 0; counter < total_count; counter++)
  {
    printf("%d ", array[counter]);
  }
  printf("\n");
  return 0;
}

