#include "test_bus_lines.h"

// See full documentation in header file
int is_sorted_by_distance (BusLine *start, BusLine *end)
{
  int counter = 1;
  while (&start[counter] != end)
  {
    if (start[counter - 1].distance > start[counter].distance)
    {
      return FAILURE_VALUE;
    }
    counter++;
  }
  return SUCCESS_VALUE;
}

// See full documentation in header file
int is_sorted_by_duration (BusLine *start, BusLine *end)
{
  int counter = 0;
  int former_duration = start[0].duration;
  while (&start[counter] != end)
  {
    if (former_duration > start[counter].duration)
    {
      return FAILURE_VALUE;
    }
    former_duration = start[counter].duration;
    counter++;
  }
  return SUCCESS_VALUE;
}

// See full documentation in header file
int is_sorted_by_name (BusLine *start, BusLine *end)
{
  int counter = 1;
  while (&start[counter] != end)
  {
    if (is_string1_before_string2 (start[counter].name,
                                   start[counter - 1].name))
    {
      return FAILURE_VALUE;
    }
    counter++;
  }
  return SUCCESS_VALUE;
}

// See full documentation in header file
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original)
{
  if ((end_original - start_original) != (end_sorted - start_sorted))
  {
    return FAILURE_VALUE;
  }

  int array_length = (int) (end_original - start_original);
  int match_counter = 0;
  for (int i = 0; i < array_length; i++)
  {
    for (int j = 0; j < array_length; j++)
    {
      if (strcmp (start_original[i].name, start_sorted[j].name) == 0)
      {
        match_counter++;
      }
    }
    if (match_counter != 1)
    {
      return FAILURE_VALUE;
    }
    match_counter = 0;
  }
  return SUCCESS_VALUE;
}

