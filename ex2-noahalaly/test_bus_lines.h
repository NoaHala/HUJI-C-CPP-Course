#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
// EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"

/**
 * tests if an array of BusLine is sorted by it's distance
 * @param start - a pointer that points the array's start
 * @param end - a pointer that points the array's end (after the last object)
 * @return 1 upon success and 0 otherwise
 */
int is_sorted_by_distance (BusLine *start, BusLine *end);

/**
 * tests if an array of BusLine is sorted by it's duration
 * @param start - a pointer that points the array's start
 * @param end - a pointer that points the array's end (after the last object)
 * @return 1 upon success and 0 otherwise
 */
int is_sorted_by_duration (BusLine *start, BusLine *end);

/**
 * tests if an array of BusLine is sorted by it's name
 * @param start - a pointer that points the array's start
 * @param end - a pointer that points the array's end (after the last object)
 * @return 1 upon success and 0 otherwise
 */
int is_sorted_by_name (BusLine *start, BusLine *end);

/**
 * tests if 2 arrays of BusLine include the same objects (without
 * considering the objects' order)
 * @param start_original - a pointer that points the first array's start
 * @param end_original - a pointer that points the first array's end (after
 * the last object)
 * @param start_sorted - a pointer that points the second array's start
 * @param end_sorted - a pointer that points the second array's end (after the
 * last object)
 * @return 1 upon success and 0 otherwise
 */
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);

// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
// EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
