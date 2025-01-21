#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NAME_LEN 21
#define SUCCESS_VALUE 1
#define FAILURE_VALUE 0

/**
 * defining the struct BusLine which contain the name,distance and duration
 * of given bus line.
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;

/**
 * enum SortType for more readable code
 */
typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;

/**
 * tests if the first string appear before the second one in the dictionary
 * @param string1 - first string
 * @param string2 - second string
 * @return 1 upon success and 0 otherwise
 */
int is_string1_before_string2 (char string1[], char string2[]);

/**
 * swap the content of the two BusLines pointers
 * @param obj1 - first object
 * @param obj2 - second object
 */
void swap (BusLine *obj1, BusLine *obj2);

/**
 * bubble sorting an array of BusLines according to it's name value
 * @param start - a pointer that points the array's start
 * @param end - a pointer that points the array's end (after the last object)
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * quick sorting an array of BusLines according to it's SortType value
 * @param start - a pointer that points the array's start
 * @param end - a pointer that points the array's end (after the last object)
 * @param sort_type - the value we want to sort by: duration or distance
 */
void quick_sort (BusLine *start, BusLine *end, SortType sort_type);

/**
 * chooses a random pivot from the BusLine array and then rearranges the
 * array such that all the elements with larger sort_type value than the
 * one of the pivot will be placed after it, and the elements with the
 * smaller value, will be placed before.
 * @param start - a pointer that points the array's start
 * @param end - a pointer that points the array's end (after the last object)
 * @param sort_type - the value we want to sort by: duration or distance
 * @return BusLine pivot
 */
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);

// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
