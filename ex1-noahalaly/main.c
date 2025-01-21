#include "cipher.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1025
#define DECIMAL 10
#define FOUR_ARGS 5
#define ONE_ARG 2

// according to the command, encode/decode the text in input_file with shift
//value of k, and write the outcome in output_file.
int ciphering (char command[], int k, FILE *input_file, FILE *output_file)
{
  char one_line[MAX_LINE_LENGTH] = {0};

  if (strcmp (command, "encode") == 0)
  {
    while (fgets (one_line, MAX_LINE_LENGTH, input_file))
    {
      encode (one_line, k);
      fputs (one_line, output_file);
    }
  }

  if (strcmp (command, "decode") == 0)
  {
    while (fgets (one_line, MAX_LINE_LENGTH, input_file))
    {
      decode (one_line, k);
      fputs (one_line, output_file);
    }
  }

  fclose (input_file);
  fclose (output_file);

  return EXIT_SUCCESS;
}


//runs all the tests on the cipher functions, if all passed - returns 0
int testing ()
{
  if (test_encode_non_cyclic_lower_case_positive_k () ||
      test_encode_cyclic_lower_case_special_char_positive_k () ||
      test_encode_non_cyclic_lower_case_special_char_negative_k () ||
      test_encode_cyclic_lower_case_negative_k () ||
      test_encode_cyclic_upper_case_positive_k () ||
      test_decode_non_cyclic_lower_case_positive_k () ||
      test_decode_cyclic_lower_case_special_char_positive_k () ||
      test_decode_non_cyclic_lower_case_special_char_negative_k () ||
      test_decode_cyclic_lower_case_negative_k () ||
      test_decode_cyclic_upper_case_positive_k ())
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

//checks if all the args are valid and if they are, runs the ciphering
int cipher_option (char *argv[])
{
  // first - checks that all the args are valid

  //checking the first argument - the command
  if ((strcmp (argv[1], "encode") != 0) &&
      (strcmp (argv[1], "decode") != 0))
  {
    fprintf (stderr, "The given command is invalid.\n");
    return EXIT_FAILURE;
  }

  //checking the second argument - the shift num - k
  int k = strtol (argv[2], NULL, DECIMAL);
  double float_k = strtod (argv[2], NULL);
  if (((strcmp (argv[2], "0")) != 0) && (strcmp (argv[2], "-0")) != 0)
  {
    if ((k == 0) || (float_k != (int) float_k))
    {
      fprintf (stderr, "The given shift value is invalid.\n");
      return EXIT_FAILURE;
    }
  }

  //checking the third argument - the input file
  char *input_file_path = argv[3];
  FILE *input_file = fopen (input_file_path, "r");
  if (input_file == NULL)
  {
    fprintf (stderr, "The given file is invalid.\n");
    return EXIT_FAILURE;
  }

  //checking the forth argument - the output file
  char *output_file_path = argv[4];
  FILE *output_file = fopen ((output_file_path), "w");
  if (output_file == NULL)
  {
    fprintf (stderr, "The given file is invalid.\n");
    fclose (input_file);
    return EXIT_FAILURE;
  }

  // second - if all args valid, call ciphering
  return ciphering (argv[1], k, input_file, output_file);
}

//checks if the arg is valid and if it is, runs the tests
int test_option (char *argv[])
{
  // first - checks that the arg is valid
  if (strcmp (argv[1], "test") != 0)
  {
    fprintf (stderr, "Usage: cipher test\n");
    return EXIT_FAILURE;
  }

  // second - if all args valid, call testing
  return testing ();
}

// main
int main (int argc, char *argv[])
{
  //checks if 1 arg received and if it did, trys the test option
  if (argc == ONE_ARG)
  {
    return test_option (argv);
  }

  //checks if 4 arg received and if it did, trys the cipher option
  if (argc == FOUR_ARGS)
  {
    return cipher_option (argv);
  }

  fprintf (stderr, "The program receives 1 or 4 arguments only.\n");
  return EXIT_FAILURE;
}
