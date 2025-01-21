#ifndef _MARKOV_CHAIN_H_
#define _MARKOV_CHAIN_H_

#include "linked_list.h"
#include <stdio.h>  // For printf(), sscanf()
#include <stdlib.h> // For exit(), malloc()
#include <stdbool.h> // for bool
#include <string.h> // strcmp

#define ALLOCATION_ERROR_MASSAGE "Allocation failure: Failed to allocate"\
            "new memory\n"

typedef struct MarkovNode MarkovNode;

/**
 * data structure for Markov chain model.
 * @var database - a pointer to a linked list that contains    all the unique
 * words in a given text as pointers to variables from MarkovNode type.
 */
typedef struct MarkovChain
{
    LinkedList *database;
} MarkovChain;


/**
 * data structure for analyzing word1's following words.
 * @var markov_node - a pointer to the following word's (word2) markov node.
 * @var frequency - a counter that counts all the scenerios in which word2
 * appear after word1.
 */
typedef struct MarkovNodeFrequency
{
    MarkovNode *markov_node;
    int frequency;

} MarkovNodeFrequency;

/**
 * data structure for Markov node model.
 * @var data - a pointer to a word.
 * @var list_frequencies - a pointer to a MarkovNodeFrequency's dynamic array.
 */
struct MarkovNode
{
    char *data;
    MarkovNodeFrequency **frequencies_list;
    int frequencies_list_length;
};

/**
 * Get random number between 0 and max_number [0 , max_number).
 * @param max_number - maximal number to return (not including)
 * @return random number
 */
int get_random_number (int max_number);

/**
 * check if the word in the given node ends with period
 * @param cur_node - given node
 * @return - true if ends with period, false otherwise
**/
bool is_word_ends_sentence (Node *cur_node);

/**
 * assuming that markov chain is not null,
 * checks if its database is not null
 * @return - true if null, false otherwise
**/
bool is_markov_chain_empty (MarkovChain *markov_chain);

/**
* If data_ptr in markov_chain, return it's node. Otherwise, create new
 * node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return markov_node wrapping given data_ptr in given chain's database,
 * returns NULL in case of memory allocation failure.
 */
Node *add_to_database (MarkovChain *markov_chain, char *data_ptr);


/**
 *Check if data_ptr is in database. If so, return the markov_node wrapping
 * it in the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node *get_node_from_database (MarkovChain *markov_chain, char *data_ptr);

/**
 * Add the second markov_node to the frequency list of the first markov_node.
 * If already in list, update it's occurrence frequency value.
 * @param first_node
 * @param second_node
 * @return success/failure: true if the process was successful, false if in
 * case of allocation error.
 */
bool
add_node_to_frequencies_list (MarkovNode *first_node, MarkovNode *second_node);

/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_chain to free
 */
void free_database (MarkovChain **ptr_chain);

/**
 * Get one random state from the given markov_chain's database.
 * @param markov_chain
 * @return
 */
MarkovNode *get_first_random_node (MarkovChain *markov_chain);

/**
 * Choose randomly the next state, depend on it's occurrence frequency.
 * @param state_struct_ptr MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode *get_next_random_node (MarkovNode *state_struct_ptr);

/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with,
 *                   if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_tweet (MarkovChain *markov_chain, MarkovNode *
first_node, int max_length);

#endif /* _MARKOV_CHAIN_H_ */