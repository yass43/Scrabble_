#ifndef _SCRABBLE_H_
#define _SCRABBLE_H_

#include "LinkedList.h"
 
 /** Scrabble dictionary (opaque) structure */
typedef struct ScrabbleDict_t ScrabbleDict;

/**
 * Creates a scrabble dictionary from a list of words.
 * Returns a pointer to the created dictionary.
 *
 * PARAMETERS
 * words        A pointer to a list of words
 */
ScrabbleDict* scrabbleCreateDict(List* words);

/**
 * Frees a scrabble dictionary, but not the stored words.
 *
 * PARAMETERS
 * sd           A pointer to a dictionary
 */
void scrabbleFreeDict(ScrabbleDict* sd);

/**
 * Finds the longest word matching a set of letters in a scrabble dictionary.
 *
 * PARAMETERS
 * sd           A pointer to a dictionary
 * letters      A string of letters
 */
char* scrabbleFindLongestWord(ScrabbleDict* sd, const char* letters);

#endif // !_SCRABBLE_H_
