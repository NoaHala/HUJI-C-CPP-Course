#include "sort_bus_lines.h"
#include "test_bus_lines.h"

#define MAX_INPUT_LEN 60
#define MAX_ARG_LEN 20
#define MAX_DISTANCE 1000
#define MAX_DURATION 100
#define MIN_DURATION 10
#define FIRST_ASCII_NUM 48
#define LAST_ASCII_NUM 57
#define FIRST_ASCII_LOWER_LETTER 97
#define LAST_ASCII_LOWER_LETTER 122

/**
 * prints the BusLines' array
 * @param bl_dynamic_array - BusLines dynamic array
 * @param num_of_lines - the length of the bl_dynamic_array
 */
void print_bl_array (BusLine *bl_dynamic_array, int num_of_lines)
{
  for (int i = 0; i < num_of_lines; i++)
  {
    printf ("%s,%d,%d\n", bl_dynamic_array[i].name,
            bl_dynamic_array[i].distance, bl_dynamic_array[i].duration);
  }
}

/**
 * sort the BusLine array according to its duration value and prints it
 * @param bl_dynamic_array - BusLines dynamic array
 * @param num_of_lines - the length of the bl_dynamic_array
 */
void by_duration (BusLine *bl_dynamic_array, int num_of_lines)
{
  quick_sort (bl_dynamic_array, &bl_dynamic_array[num_of_lines],
              DURATION);
  print_bl_array (bl_dynamic_array, num_of_lines);
}

/**
 * sort the BusLine array according to its distance value and prints it
 * @param bl_dynamic_array - BusLines dynamic array
 * @param num_of_lines - the length of the bl_dynamic_array
 */
void by_distance (BusLine *bl_dynamic_array, int num_of_lines)
{
  quick_sort (bl_dynamic_array, &bl_dynamic_array[num_of_lines],
              DISTANCE);
  print_bl_array (bl_dynamic_array, num_of_lines);
}

/**
 * sort the BusLine array according to its name value and prints it
 * @param bl_dynamic_array - BusLines' dynamic array
 * @param num_of_lines - the length of the bl_dynamic_array
 */
void by_name (BusLine *bl_dynamic_array, int num_of_lines)
{
  bubble_sort (bl_dynamic_array, &bl_dynamic_array[num_of_lines]);
  print_bl_array (bl_dynamic_array, num_of_lines);
}

/**
 * runs the first two tests - checks for mistakes in quick_sort by distance
 * @param bl_dynamic_array - the BusLines dynamic array before sorting
 * @param bl_arr_copy - the BusLines dynamic array after sorting
 * @param num_of_lines - the length of the bl_dynamic_array
 */
void tests_1_2 (BusLine *bl_dynamic_array, BusLine *bl_arr_copy, int
num_of_lines)
{
  // first sort
  quick_sort (bl_arr_copy, &bl_arr_copy[num_of_lines], DISTANCE);

  // TEST 1
  if (is_sorted_by_distance (bl_arr_copy,
                             &bl_arr_copy[num_of_lines]))
  {
    printf ("TEST 1 PASSED: quick sort the array by its distance value\n");
  }
  else
  {
    printf ("TEST 1 FAILED: quick sort the array by its distance value\n");
  }

  // TEST 2
  if (is_equal (bl_arr_copy, &bl_arr_copy[num_of_lines],
                bl_dynamic_array, &bl_dynamic_array[num_of_lines]))
  {
    printf ("TEST 2 PASSED: array after quick sort (by distance) has the same "
            "objects\n");
  }
  else
  {
    printf ("TEST 2 FAILED: array after quick sort (by distance)"
            " hasn't the same objects\n");
  }

}

/**
 * runs the second two tests - checks for mistakes in quick_sort by duration
 * @param bl_dynamic_array - the BusLines dynamic array before sorting
 * @param bl_arr_copy - the BusLines dynamic array after sorting
 * @param num_of_lines - the length of the bl_dynamic_array
 */
void tests_3_4 (BusLine *bl_dynamic_array, BusLine *bl_arr_copy, int
num_of_lines)
{
  // second sort
  quick_sort (bl_arr_copy, &bl_arr_copy[num_of_lines], DURATION);

  // TEST 3
  if (is_sorted_by_duration (bl_arr_copy,
                             &bl_arr_copy[num_of_lines]))
  {
    printf ("TEST 3 PASSED: quick sort the array by its duration value\n");
  }
  else
  {
    printf ("TEST 3 FAILED: quick sort the array by its duration value\n");
  }

  // TEST 4
  if (is_equal (bl_arr_copy, &bl_arr_copy[num_of_lines], bl_dynamic_array,
                &bl_dynamic_array[num_of_lines]))
  {
    printf ("TEST 4 PASSED: array after quick sort (by duration) has the same "
            "objects\n");
  }
  else
  {
    printf ("TEST 4 FAILED: array after quick sort (by duration) hasn't the "
            "same objects\n");
  }

}

/**
 * runs the last two tests - checks for mistakes in bubble_sort by name
 * @param bl_dynamic_array - the BusLines dynamic array before sorting
 * @param bl_arr_copy - the BusLines dynamic array after sorting
 * @param num_of_lines - the length of the bl_dynamic_array
 */
void tests_5_6 (BusLine *bl_dynamic_array, BusLine *bl_arr_copy, int
num_of_lines){
  // third sort
  bubble_sort (bl_arr_copy, &bl_arr_copy[num_of_lines]);

  // TEST 5
  if (is_sorted_by_name (bl_arr_copy, &bl_arr_copy[num_of_lines]))
  {
    printf ("TEST 5 PASSED: bubble sort the array by its name value\n");
  }
  else
  {
    printf ("TEST 5 FAILED: bubble sort the array by its name value\n");
  }

  // TEST 6
  if (is_equal (bl_arr_copy, &bl_arr_copy[num_of_lines], bl_dynamic_array,
                &bl_dynamic_array[num_of_lines]))
  {
    printf ("TEST 6 PASSED: array after bubble sort (by name)"
            " has the same objects\n");
  }
  else
  {
    printf ("TEST 6 FAILED: array after bubble sort (by name) hasn't the "
            "same objects\n");
  }
}

/**
 * runs the tests for the sorting functions on a given BusLines' array
 * @param bl_dynamic_array - BusLines dynamic array
 * @param num_of_lines - the length of the bl_dynamic_array
 */
int test (BusLine *bl_dynamic_array, int num_of_lines)
{
  // copy the array for the tests
  BusLine *bl_arr_copy = malloc (sizeof (BusLine) * num_of_lines);
  if (!bl_arr_copy)
  {
    free (bl_arr_copy);
    bl_arr_copy = NULL;
    return EXIT_FAILURE;
  }
  memcpy (bl_arr_copy, bl_dynamic_array,
          sizeof (BusLine) * num_of_lines);

  // first two tests (quick sort by distance)
  tests_1_2 (bl_dynamic_array, bl_arr_copy, num_of_lines);

  // second two tests (quick sort by duration)
  tests_3_4 (bl_dynamic_array, bl_arr_copy, num_of_lines);

  // last two tests (bubble sort by name)
  tests_5_6 (bl_dynamic_array, bl_arr_copy, num_of_lines);

  return EXIT_SUCCESS;
}

/**
 * interacts with the user for getting the number of bus lines
 * @return number of bus lines (integer)
 */
int get_lines_number ()
{
  char input_str[MAX_INPUT_LEN] = {0};
  int num_of_lines = 0;
  printf ("Enter number of lines. Then enter\n");
  fgets (input_str, MAX_INPUT_LEN, stdin);
  while (sscanf (input_str, "%d", &num_of_lines) != 1)
  {
    printf ("ERROR: number of lines should be a positive integer\n");
    printf ("Enter number of lines. Then enter");
    fgets (input_str, MAX_INPUT_LEN, stdin);
  }
  if (num_of_lines > 0)
  {
    return num_of_lines;
  }
  else
  {
    printf ("ERROR: number of lines should be a positive integer\n");
    return get_lines_number ();
  }
}

/**
 * checks if line name is valid
 * @param line_name - the line's name
 */
int is_name_valid (char line_name[])
{
  if (strlen (line_name) < 1 || strlen (line_name) > MAX_ARG_LEN)
  {
    return FAILURE_VALUE;
  }
  for (int i = 0; i < (int) strlen (line_name); i++)
  {
    if (FIRST_ASCII_NUM > line_name[i] ||
        (LAST_ASCII_NUM < line_name[i] &&
         line_name[i] < FIRST_ASCII_LOWER_LETTER) ||
        line_name[i] > LAST_ASCII_LOWER_LETTER)
    {
      return FAILURE_VALUE;
    }
  }
  return SUCCESS_VALUE;
}

/**
 * interacts with the user for getting one bus line's information and
 * saves it in a given location in a dynamic array.
 * @param designated_location - pointer to the designated place for the new
 * information in the array
 */
void get_one_busline_info (BusLine *designated_location)
{
  char input_str[MAX_INPUT_LEN] = {0};
  char line_name[MAX_ARG_LEN + 1] = {0};
  int distance = 0;
  int duration = 0;

  printf ("Enter line info. Then enter\n");
  fgets (input_str, MAX_INPUT_LEN, stdin);
  while (sscanf (input_str, "%[^,],%d,%d", line_name, &distance, &duration)
         != 3)
  {

    printf ("ERROR: input should be in a format of "
            "<line_name>,<distance>,<duration>\n");
    printf ("Enter line info. Then enter\n");
    fgets (input_str, MAX_INPUT_LEN, stdin);
  }

  if (!is_name_valid (line_name))
  {
    printf ("ERROR: bus name should contain only digits and small chars "
            "(max length - 20 characters)\n");
    get_one_busline_info (designated_location);
  }
  else if (distance < 0 || distance > MAX_DISTANCE)
  {
    printf ("ERROR: distance should be an integer between 0 to 1000 "
            "(include)\n");
    get_one_busline_info (designated_location);
  }
  else if (duration < MIN_DURATION || duration > MAX_DURATION)
  {
    printf ("ERROR: duration should be an integer between 10 to 100 "
            "(include)\n");
    get_one_busline_info (designated_location);
  }
  else
  {
    strcpy (designated_location->name, line_name);
    designated_location->distance = distance;
    designated_location->duration = duration;
  }
}

/**
 * interacts with the user for getting all the bus line's information and
 * saves it in a given dynamic array.
 * @param bl_dynamic_array - empty BusLine's dynamic array
 * @param num_of_lines - the number of required lines and the size of the
 * given bl_dynamic_array
 */
void get_buslines_info (BusLine *bl_dynamic_array, int num_of_lines)
{
  for (int i = 0; i < num_of_lines; i++)
  {
    get_one_busline_info (&bl_dynamic_array[i]);
  }
}

int is_command_not_valid (int argc, char *argv[])
{
  if (argc != 2 ||
      (strcmp (argv[1], "by_duration") != 0 &&
       strcmp (argv[1], "by_distance") != 0 &&
       strcmp (argv[1], "by_name") != 0 &&
       strcmp (argv[1], "test") != 0))
  {
    printf ("USAGE: INVALID COMMAND, THE OPTIONS ARE: "
            "(1) by_duration "
            "(2) by_distance "
            "(3) by_name "
            "(4) test ");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/**
 * main function of the program
 * gets a list of BusLines and a command and runs different sort types on the
 * list according to that command
 * @param argc - the amount of arguments passed to the program
 * @param argv - array of the arguments that passed to the program
 * @return o upon success, 1 otherwise
 */
int main (int argc, char *argv[])
{
  // checks if command is invalid
  if (is_command_not_valid (argc, argv))
  {
    return EXIT_FAILURE;
  }
  // asking the user for number of lines
  int num_of_lines = get_lines_number ();
  // allocating a dynamic array of size num_of_lines
  BusLine *bl_dynamic_array = malloc (sizeof (BusLine) * num_of_lines);
  if (!bl_dynamic_array)
  {
    free (bl_dynamic_array);
    bl_dynamic_array = NULL;
    return EXIT_FAILURE;
  }
  // getting the bus lines' information from the user and saving in the array
  get_buslines_info (bl_dynamic_array, num_of_lines);
  //checks if the command is "by_duration" and if so, calls by_duration func
  if (strcmp (argv[1], "by_duration") == 0)
  {
    by_duration (bl_dynamic_array, num_of_lines);
  }
  //checks if the command is "by_distance" and if so, calls by_distance func
  if (strcmp (argv[1], "by_distance") == 0)
  {
    by_distance (bl_dynamic_array, num_of_lines);
  }
  //checks if the command is "by_name" and if so, calls the by_name function
  if (strcmp (argv[1], "by_name") == 0)
  {
    by_name (bl_dynamic_array, num_of_lines);
  }
  //checks if the command is "test" and if so, calls the test function
  if (strcmp (argv[1], "test") == 0)
  {
    if (!test (bl_dynamic_array, num_of_lines))
    {
      free (bl_dynamic_array);
      bl_dynamic_array = NULL;
      return EXIT_FAILURE;
    }
  }
  free (bl_dynamic_array);
  bl_dynamic_array = NULL;
  return EXIT_SUCCESS;
}
