#include "sort_bus_lines.h"

// See full documentation in header file
int is_string1_before_string2 (char string1[], char string2[])
{
  int min_len = (strlen (string1) < strlen (string2) ?
                 (int) strlen (string1) : (int) strlen (string2));
  for (int i = 0; i < min_len; i++)
  {
    if (*(string1 + i) > *(string2 + i))
    {
      return FAILURE_VALUE;
    }
    if (*(string1 + i) < *(string2 + i))
    {
      return SUCCESS_VALUE;
    }
  }
  if (strlen (string1) > strlen (string2))
  {
    return FAILURE_VALUE;
  }
  else
  {
    return SUCCESS_VALUE;
  }
}

// See full documentation in header file
void swap (BusLine *obj1, BusLine *obj2)
{
  BusLine temp = *obj1;
  *obj1 = *obj2;
  *obj2 = temp;
}

// See full documentation in header file
void bubble_sort (BusLine *start, BusLine *end)
{
  int arr_len = (int) (end - start);
  for (int i = 0; i < arr_len - 1; i++)
  {
    for (int a = 0; a < arr_len - i - 1; a++)
    {
      if (is_string1_before_string2 ((start + a + 1)->name, (start + a)->name))
      {
        swap ((start + a), (start + a + 1));
      }
    }
  }
}

// See full documentation in header file
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type)
{
  //choosing pivot as last index
  int pivot_index = (int) (end - start) - 1;

  int arr_len = (int) (end - start);
  int index_of_smaller_element = -1;

  for (int j = 0; j < arr_len - 1; j++)
  {
    // case 1 - sort_type is duration
    if (sort_type == DURATION)
    {
      if ((start + j)->duration < (start + pivot_index)->duration)
      {
        index_of_smaller_element++;
        swap ((start + index_of_smaller_element), (start + j));
      }
    }

    // case 2 - sort_type is distance
    if (sort_type == DISTANCE)
    {
      if ((start + j)->distance < (start + pivot_index)->distance)
      {
        index_of_smaller_element++;
        swap ((start + index_of_smaller_element), (start + j));
      }
    }
  }
  swap ((start + pivot_index), (start + index_of_smaller_element + 1));
  return start + index_of_smaller_element + 1;
}

// See full documentation in header file
void quick_sort (BusLine *start, BusLine *end, SortType sort_type)
{
  size_t arr_len = (size_t) (end - start);
  if (arr_len > 1)
  {
    BusLine *pivot = partition (start, end, sort_type);
    quick_sort (start, pivot, sort_type);
    quick_sort (pivot + 1, end, sort_type);
  }
}