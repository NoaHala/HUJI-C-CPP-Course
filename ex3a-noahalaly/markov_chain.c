#include "markov_chain.h"

// See full documentation in header file
bool is_word_ends_sentence (Node *cur_node)
{
  if (cur_node != NULL)
  {
    if (cur_node->data != NULL)
    {
      if (cur_node->data->data != NULL)
      {
        char *cur_word = cur_node->data->data;
        size_t len = strlen (cur_word);
        if (cur_word[len - 1] == '.')
        {
          return true;
        }
      }
    }
  }
  return false;
}

// See full documentation in header file
bool is_markov_chain_empty (MarkovChain *markov_chain)
{
  if (markov_chain->database == NULL)
  {
    return true;
  }
  return false;
}

// See full documentation in header file
Node *add_to_database (MarkovChain *markov_chain, char *data_ptr)
{
  //checks if the node already exists
  Node *node_with_this_data = get_node_from_database (markov_chain, data_ptr);
  if (node_with_this_data != NULL)
  {
    return node_with_this_data;
  }

  // create new markov node with the string from the args
  MarkovNode *new_markov_node = malloc (sizeof (MarkovNode));
  if (new_markov_node == NULL)
  {
    printf (ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  new_markov_node->data = data_ptr;
  new_markov_node->frequencies_list = NULL;
  new_markov_node->frequencies_list_length = 0;

  //checks if markov_chain->database is null (if it's the first node)
  if (is_markov_chain_empty (markov_chain))
  {
    LinkedList *new_linked_list = malloc (sizeof (LinkedList));
    if (new_linked_list == NULL)
    {
      free (new_markov_node);
      new_markov_node = NULL;
      printf (ALLOCATION_ERROR_MASSAGE);
      return NULL;
    }
    new_linked_list->size = 0;
    new_linked_list->first = NULL;
    new_linked_list->last = NULL;
    markov_chain->database = new_linked_list;
  }

  if (add (markov_chain->database, new_markov_node) == 1)
  {
    free (new_markov_node);
    new_markov_node = NULL;
    free (markov_chain->database);
    markov_chain->database = NULL;
    printf (ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  return markov_chain->database->last;
}

// See full documentation in header file
Node *get_node_from_database (MarkovChain *markov_chain, char *data_ptr)
{
  if (!is_markov_chain_empty (markov_chain) && markov_chain != NULL)
  {
    if (markov_chain->database->first != NULL)
    {
      Node *current_node = markov_chain->database->first;
      for (int i = 0; i < (markov_chain->database->size); i++)
      {
        if (current_node->data != NULL)
        {
          MarkovNode current_markov_node = *(current_node->data);
          if (strcmp (current_markov_node.data, data_ptr) == 0)
          {
            return current_node;
          }
        }
        current_node = current_node->next;
      }
    }
  }
  return NULL;
}

bool alloc_problem ()
{
  printf (ALLOCATION_ERROR_MASSAGE);
  return false;
}

// See full documentation in header file
bool add_node_to_frequencies_list (MarkovNode *first_node, MarkovNode
*second_node)
{
  MarkovNodeFrequency **current_freq_list_ptr = first_node->frequencies_list;
  MarkovNodeFrequency *current_freq_list;
  // checks if frequency list does not exists
  if (current_freq_list_ptr == NULL)
  {
    current_freq_list_ptr = malloc (sizeof (MarkovNodeFrequency *));
    if (current_freq_list_ptr == NULL)
    { return alloc_problem (); }
    first_node->frequencies_list = current_freq_list_ptr;
    //allocate new frequency list
    current_freq_list = malloc (sizeof (MarkovNodeFrequency));
    if (current_freq_list == NULL)
    { return alloc_problem (); }
    *current_freq_list_ptr = current_freq_list;
  }
  else // if the frequency list do exists
  {
    current_freq_list = (*current_freq_list_ptr);
    //loop on each MarkovNodeFrequency in the frequency list
    for (int i = 0; i < first_node->frequencies_list_length; i++)
    {
      if (strcmp (current_freq_list[i].markov_node->data, second_node->data)
          == 0) // if second_node is already in the list
      {
        current_freq_list[i].frequency++;
        return true;
      }
    }
    // if second node is not inside the frequency list
    MarkovNodeFrequency *temp = realloc (current_freq_list,
                                         sizeof (MarkovNodeFrequency) *
                                         (first_node->frequencies_list_length
                                          + 1));
    if (temp == NULL)
    { return alloc_problem (); }

    (*current_freq_list_ptr) = temp;
    current_freq_list = temp;
  }
  first_node->frequencies_list_length++;
  current_freq_list[first_node->frequencies_list_length - 1].frequency = 1;
  current_freq_list[first_node->frequencies_list_length
                    - 1].markov_node = second_node;
  return true;
}

// See full documentation in header file
void free_database (MarkovChain **ptr_chain)
{
  if (ptr_chain != NULL && (*ptr_chain) != NULL)
  {
    if ((*ptr_chain)->database != NULL)
    {
      LinkedList *ll_helper = (*ptr_chain)->database;
      if (ll_helper->first != NULL)
      {
        Node *current_node = ll_helper->first;
        for (int i = 0; i < (ll_helper->size); i++)
        {
          MarkovNode *current_markov_node = current_node->data;
          if (current_markov_node != NULL)
          {
            //free (current_markov_node->data);
            //current_markov_node->data = NULL;
            if (current_markov_node->frequencies_list != NULL)
            {
              free (*(current_markov_node->frequencies_list));
              *(current_markov_node->frequencies_list) = NULL;
              free (current_markov_node->frequencies_list);
              current_markov_node->frequencies_list = NULL;
            }
            free (current_markov_node);
            current_markov_node = NULL;
          }
          Node *temp_node = current_node;
          current_node = current_node->next;
          free (temp_node);
          temp_node = NULL;
        }
      }
      free (ll_helper);
      ll_helper = NULL;
    }
    free (*ptr_chain);
    *ptr_chain = NULL;
  }
}

// See full documentation in header file
int get_random_number (int max_number)
{
  return rand () % max_number;
}

// See full documentation in header file
MarkovNode *get_first_random_node (MarkovChain *markov_chain)
{
  MarkovNode temp = (MarkovNode) {".", NULL, 0};
  Node temp2 = (Node) {&temp, NULL};
  Node *chosen_node = &temp2;


  while (is_word_ends_sentence (chosen_node))
  {
    int rand_num = get_random_number (markov_chain->database->size);
    chosen_node = markov_chain->database->first;
    for (int i = 0; i < rand_num; i++)
    {
      chosen_node = chosen_node->next;
    }
  }
  return chosen_node->data;
}

/**
 * Choose randomly the next state, depend on it's occurrence frequency.
 * @param state_struct_ptr MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode *get_next_random_node (MarkovNode *state_struct_ptr)
{
  // if the word ends a sentence
  if (state_struct_ptr->frequencies_list_length == 0)
  {
    return NULL;
  }

  int options_counter = 0;
  int words_num = state_struct_ptr->frequencies_list_length;

  for (int i = 0; i < words_num; i++)
  {
    options_counter = options_counter +
                      (*(state_struct_ptr->frequencies_list))[i].frequency;
  }

  int rand_num = get_random_number (options_counter);
  int wanted_index = rand_num;
  int sub_list_len = 0;

  for (int i = 0; i < words_num; i++)
  {
    sub_list_len = sub_list_len + (*(state_struct_ptr->frequencies_list))[i]
        .frequency;
    if (sub_list_len > wanted_index)
    {
      return (*(state_struct_ptr->frequencies_list))[i].markov_node;
    }
  }

  //unexpected behavior alert
  printf ("ERROR - unexpected 1\n");
  return NULL;
}

/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with,
 *                   if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_tweet (MarkovChain *markov_chain, MarkovNode *
first_node, int max_length)
{
  // node to start with
  MarkovNode *cur_node = NULL;
  if (first_node != NULL)
  {
    cur_node = first_node;
    printf ("%s", cur_node->data);
  }
  else
  {
    cur_node = get_first_random_node (markov_chain);
  }

  //build a sentence
  for (int i = 1; i < max_length; i++)
  {
    cur_node = get_next_random_node (cur_node);
    if (cur_node == NULL)
    {
      break;
    }
    printf (" %s", cur_node->data);
  }
  printf ("\n");
}