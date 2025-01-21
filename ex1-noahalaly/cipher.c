#include "cipher.h"
#define FIRST_UPPER_LETTER  65
#define LAST_UPPER_LETTER  90
#define FIRST_LOWER_LETTER  97
#define LAST_LOWER_LETTER  122
#define ALPHABET_LEN  26

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.


// See full documentation in header file
void encode (char s[], int k)
{
  int i = 0;
  while (s[i] != '\0')
  {
    int new_letter_value = (int) s[i] + (k % ALPHABET_LEN);

    // checking if cyclic shifts are required on lower case letters
    if (s[i] >= FIRST_LOWER_LETTER && s[i] <= LAST_LOWER_LETTER)
    {
      if (new_letter_value < FIRST_LOWER_LETTER)
      {
        new_letter_value += ALPHABET_LEN;
      }
      if (new_letter_value > LAST_LOWER_LETTER)
      {
        new_letter_value -= ALPHABET_LEN;
      }
      s[i] = (char) new_letter_value;
    }

    // checking if cyclic shifts are required on upper case letters
    if (s[i] <= LAST_UPPER_LETTER && s[i] >= FIRST_UPPER_LETTER)
    {
      if (new_letter_value < FIRST_UPPER_LETTER)
      {
        new_letter_value += ALPHABET_LEN;
      }
      if (new_letter_value > LAST_UPPER_LETTER)
      {
        new_letter_value -= ALPHABET_LEN;
      }
      s[i] = (char) new_letter_value;
    }

    i++;
  }
}

// See full documentation in header file
void decode (char s[], int k)
{
  int minus_k = (-1) * k;
  encode (s, minus_k);
}
