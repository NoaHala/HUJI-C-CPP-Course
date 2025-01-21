#include "tests.h"
#include <string.h>
#include <stdio.h>

#define K_3 3
#define K_2 2
#define K_M1 (-1)
#define K_M3 (-3)
#define K_29 29

// See full documentation in header file
int test_encode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  encode (in, K_3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "w, x, y, z";
  char out[] = "y, z, a, b";
  encode (in, K_2);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "cd-ef";
  char out[] = "bc-de";
  encode (in, K_M1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_negative_k ()
{
  char in[] = "bcd";
  char out[] = "yza";
  encode (in, K_M3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_upper_case_positive_k ()
{
  char in[] = "YZA";
  char out[] = "BCD";
  encode (in, K_29);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def";
  char out[] = "abc";
  decode (in, K_3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "y, z, a, b";
  char out[] = "w, x, y, z";
  decode (in, K_2);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "bc-de";
  char out[] = "cd-ef";
  decode (in, K_M1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_negative_k ()
{
  char in[] = "yza";
  char out[] = "bcd";
  decode (in, K_M3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_upper_case_positive_k ()
{
  char in[] = "BCD";
  char out[] = "YZA";
  decode (in, K_29);
  return strcmp (in, out) != 0;
}
