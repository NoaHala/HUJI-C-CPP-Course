#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

#define EMPTY (-1)
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60
#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20
#define TWO_ARGS 3

/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8,  30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell
{
    int number; // Cell number 1-100
    int ladder_to;  // ladder_to represents the jump of the ladder in
    // case there is one from this square
    int snake_to;  // snake_to represents the jump of the snake in
    // case there is one from this square
    //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

/** Error handler **/
static int handle_error (char *error_msg, MarkovChain **database)
{
  printf ("%s", error_msg);
  if (database != NULL)
  {
    free_database (database);
  }
  return EXIT_FAILURE;
}

static int create_board (Cell *cells[BOARD_SIZE])
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    cells[i] = malloc (sizeof (Cell));
    if (cells[i] == NULL)
    {
      for (int j = 0; j < i; j++)
      {
        free (cells[j]);
      }
      handle_error (ALLOCATION_ERROR_MASSAGE, NULL);
      return EXIT_FAILURE;
    }
    *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
  }

  for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
  {
    int from = transitions[i][0];
    int to = transitions[i][1];
    if (from < to)
    {
      cells[from - 1]->ladder_to = to;
    }
    else
    {
      cells[from - 1]->snake_to = to;
    }
  }
  return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int fill_database (MarkovChain *markov_chain)
{
  Cell *cells[BOARD_SIZE];
  if (create_board (cells) == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }
  MarkovNode *from_node = NULL, *to_node = NULL;
  size_t index_to;
  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
    add_to_database (markov_chain, cells[i]);
  }

  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
    from_node = get_node_from_database (markov_chain, cells[i])->data;

    if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
    {
      index_to = MAX(cells[i]->snake_to, cells[i]->ladder_to) - 1;
      to_node = get_node_from_database (markov_chain, cells[index_to])
          ->data;
      add_node_to_frequencies_list (from_node, to_node, markov_chain);
    }
    else
    {
      for (int j = 1; j <= DICE_MAX; j++)
      {
        index_to = ((Cell *) (from_node->data))->number + j - 1;
        if (index_to >= BOARD_SIZE)
        {
          break;
        }
        to_node = get_node_from_database (markov_chain, cells[index_to])
            ->data;
        add_node_to_frequencies_list (from_node, to_node, markov_chain);
      }
    }
  }
  // free temp arr
  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
    free (cells[i]);
  }
  return EXIT_SUCCESS;
}

/**
 * checks if received 3 or 4 args
 * @param argc - amount of args
 * @return true if 3 or 4, false otherwise
 */
static bool valid_arg_num (int argc)
{
  if (argc != TWO_ARGS)
  {
    printf ("Usage: 2 arguments only\n");
    return false;
  }
  return true;
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
static int converting_args_to_int (unsigned int *seed_val, int *path_num,
                                   char *argv[])
{
  if (sscanf (argv[1], "%u", seed_val) != 1 ||
      sscanf (argv[2], "%d", path_num) != 1)
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/**
 * prints the wanted value with relevant symbols.
 * @param cell_as_void - pointer to a cell (as void)
**/
static void adapt_print (void *cell_as_void)
{
  Cell *cur_cell = cell_as_void;
  int cell_val = cur_cell->number;
  printf ("[%d]", cell_val);
  if (cell_val != BOARD_SIZE)
  {
    if (cur_cell->ladder_to != EMPTY)
    {
      printf ("-ladder to %d -> ", cur_cell->ladder_to);
    }
    else if (cur_cell->snake_to != EMPTY)
    {
      printf ("-snake to %d -> ", cur_cell->snake_to);
    }
    else
    {
      printf (" -> ");
    }
  }
}

/**
 * check if the two given cells are the same (by their number value)
 * @param object1 - pointer to the first cell (as void)
 * @param object2 - pointer to the second cell (as void)
 * @return - 0 if equal, other number if not
**/
static int adapt_compare (void *object1, void *object2)
{
  Cell *cell_num1 = object1;
  Cell *cell_num2 = object2;
  return (cell_num1->number - cell_num2->number);
}

/**
 * free the memory in the pointer
 * @param cell_to_free - pointer to free
**/
static void adapt_free (void *cell_to_free)
{
  free (cell_to_free);
}

/**
 * copy the data in pointer to a new allocated place
 * @param cell_to_copy_as_void - pointer to a cell (as void)
 * @return - pointer (void*) to a new allocated cell if succeeded, NULL if
 * allocation failed
**/
static void *adapt_copy (void *cell_to_copy_as_void)
{
  Cell *cell_to_copy = cell_to_copy_as_void;
  Cell *new_cell = malloc (sizeof (Cell));
  if (new_cell == NULL)
  {
    return NULL;
  }
  new_cell->number = cell_to_copy->number;
  new_cell->ladder_to = cell_to_copy->ladder_to;
  new_cell->snake_to = cell_to_copy->snake_to;
  return new_cell;
}

/**
 * check if the given cell is the last in the board (number value is 100)
 * @param data - pointer to a cell (as void)
 * @return - true if is the last in the board, false otherwise
**/
static bool adapt_is_last (void *data)
{
  Cell *cur_cell = data;
  if (cur_cell->number == BOARD_SIZE)
  {
    return true;
  }
  return false;
}

/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int main (int argc, char *argv[])
{
  // checking if the parameters are valid
  if (!valid_arg_num (argc))
  {
    return EXIT_FAILURE;
  }

  // converting numeric parameters from string to int
  int path_num = 0;
  unsigned int seed_val = 0;
  if (converting_args_to_int (&seed_val, &path_num,
                              argv))
  {
    return EXIT_FAILURE;
  }

  //defining the seed for rand
  srand (seed_val);
  // creates new MarkovChain
  MarkovChain *markov_chain = new_markov_chain (adapt_print,
                                                adapt_copy,
                                                adapt_compare,
                                                adapt_free,
                                                adapt_is_last);

  if (markov_chain == NULL)
  {
    return EXIT_FAILURE;
  }

  // upload words to the new MarkovChain
  bool problem_to_fill = fill_database (markov_chain);
  if (problem_to_fill)
  {
    free_database (&markov_chain);
    return EXIT_FAILURE;
  }

  // printing the wanted amount of paths
  for (int i = 0; i < path_num; ++i)
  {
    printf ("Random Walk %d: ", i + 1);
    generate_tweet (markov_chain, markov_chain->database->first->data,
                    MAX_GENERATION_LENGTH);
  }

  // free all the used memory and finish
  free_database (&markov_chain);
  return EXIT_SUCCESS;
}
