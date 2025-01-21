#include "markov_chain.h"

#define LINE_LEN 1001
#define MAX_TWEET_LEN 20
#define THREE_ARGS 4
#define FOUR_ARGS 5

/**
 * gets string, allocates place in heap and puts copy of string inside
 * @param str_to_copy - given string
 * @return string copy in the heap
 */
char *str_alloc (char *str_to_copy)
{
  int str_len = (int) strlen (str_to_copy);
  char *new_str = malloc (str_len + 1);
  if (new_str == NULL)
  {
    printf (ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  strcpy (new_str, str_to_copy);
  return new_str;
}

/**
 * the function fill MarkovChain's data structure with words from given file
 * @param fp - given text file
 * @param words_to_read - the number of words to read from the file and add to
 * the database
 * @param markov_chain - a pointer to MarkovChain's data structure that will
 * contain the new information
 * @return o upon success, 1 otherwise
 */
int fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain)
{
  char current_line[LINE_LEN];
  int words_counter = 0;

  // loop all lines in file
  while (fgets (current_line, LINE_LEN, fp) != NULL)
  {
    //checks if it reached the max amount of words and stop
    if (words_to_read != 0)
    {
      if (words_counter >= words_to_read)
      { break; }
    }
    //loop on all the words in the line
    char *current_word = strtok (current_line, " \n");
    Node *current_node = NULL;
    Node *previous_node = NULL;
    while (current_word != NULL)
    {
      if (words_to_read != 0)
      {
        if (words_counter >= words_to_read)
        { break; }
      }
      words_counter++;
      //adding the word to the MarkovChain
      previous_node = current_node;
      // allocating string and put the copy inside.
      current_node = get_node_from_database (markov_chain, current_word);
      if (current_node == NULL)
      {
        char *str_copy = str_alloc(current_word);
        current_node = add_to_database (markov_chain,str_copy);

//        char *str_cpy = str_alloc (current_word);
//        current_node = add_to_database (markov_chain, str_cpy);
//        if (current_node == NULL)
//        { return EXIT_FAILURE; }
      }
      // if previous_node exists and not ending sentence, adds it to
      // the frequency list of the current_node
      if (previous_node != NULL && !is_word_ends_sentence (previous_node))
      {
        if (current_node->data == NULL)
        { return EXIT_FAILURE; }
        if (!add_node_to_frequencies_list (previous_node->data,
                                           current_node->data))
        { return EXIT_FAILURE; }
      }
      current_word = strtok (NULL, " \n");
    }
  }
  return EXIT_SUCCESS;
}

/**
 * checks if received 3 or 4 args
 * @param argc - amount of args
 * @return true if 3 or 4, false otherwise
 */
bool valid_arg_num (int argc)
{
  if (argc != THREE_ARGS && argc != FOUR_ARGS)
  {
    printf ("3 or 4 arguments only\n");
    return false;
  }
  return true;
}

/**
 * gets path to file, open it and return pointer to that file
 * @param path - the path-to-file string
 * @return pointer to the file if succeeded to open it, NULL otherwise.
 */
FILE *get_file (char *path)
{
  FILE *file = fopen (path, "r");
  if (file == NULL)
  {
    printf ("Error: file is not valid\n");
    return NULL;
  }
  return file;
}

/**
 * take the arguments from the CLI as string, converts them to type int or
 * unsigned ind and assign them in the relevant pointer
 * @param argc - amount of args received
 * @param argv - list of string args
 * @param seed_val - pointer to the chosen seed variable
 * @param tweet_num - pointer to the chosen number-of-tweets variable
 * @param seed_val - pointer to the chosen max_words_to_read variable
 * @return 0 if success and 1 otherwise
 */
int converting_args_to_int (unsigned int *seed_val, int *tweet_num, int
*words_to_read, char *argv[], int argc)
{
  if (sscanf (argv[1], "%u", seed_val) != 1 ||
      sscanf (argv[2], "%d", tweet_num) != 1)
  {
    return EXIT_FAILURE;
  }
  if (argc == FOUR_ARGS)
  {
    if (sscanf (argv[4], "%d", words_to_read) != 1)
    {
      return EXIT_FAILURE;
    }
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
  // checking if the parameters are valid
  if (!valid_arg_num (argc))
  { return EXIT_FAILURE; }
  // converting numeric parameters from string to int
  int words_to_read = 0, tweet_num = 0;
  unsigned int seed_val = 0;
  if (converting_args_to_int (&seed_val, &tweet_num, &words_to_read,
                              argv, argc))
  { return EXIT_FAILURE; }
  //defining the seed for rand
  srand (seed_val);
  // file check
  FILE *file = get_file (argv[3]);
  if (file == NULL)
  { return EXIT_FAILURE; }
  // creates new MarkovChain
  MarkovChain *markov_chain = malloc (sizeof (MarkovChain));
  if (markov_chain == NULL)
  {
    printf (ALLOCATION_ERROR_MASSAGE);
    return EXIT_FAILURE;
  }
  markov_chain->database = NULL;
  // upload words to the new MarkovChain
  bool problem_to_fill = fill_database (file, words_to_read, markov_chain);
  if (problem_to_fill)
  {
    free_database (&markov_chain);
    printf (ALLOCATION_ERROR_MASSAGE);
    return EXIT_FAILURE;
  }
  // printing the wanted amount of tweets
  for (int i = 0; i < tweet_num; ++i)
  {
    printf ("Tweet %d: ", i + 1);
    MarkovNode *chosen_mn = get_first_random_node (markov_chain);
    generate_tweet (markov_chain, chosen_mn, MAX_TWEET_LEN);
  }
  // free all the used memory
  free_database (&markov_chain);
  fclose (file);

  return EXIT_SUCCESS;
}