#ifndef _DICT_H_
#define _DICT_H_

/** Dictionary (opaque) structure */
typedef struct Dict_t Dict;

/**
 * Creates an empty dictionary and returns a pointer to it.
 */
Dict* dictCreateEmpty(void);

/**
 * Frees a dictionary, but not the data.
 *
 * PARAMETERS
 * dict         A pointer to a dictionary
 */
void dictFree(Dict* dict);

/**
 * Returns the number of keys stored in the dictionary
 *
 * PARAMETERS
 * dict         A pointer to a dictionary
 */
size_t dictNbKeys(Dict* dict);

/**
 * Returns 1 if key is associated to data in a dictionary, 0 otherwise.
 *
 * PARAMETERS
 * dict         A pointer to a dictionary
 * key          A key
 */
int dictContains(Dict* d, const char* key);

/**
 * Searches and returns the pointer to data associated to a key
 * in a dictionary. If no data is associated to that key, returns a
 * null pointer.
 *
 * PARAMETERS
 * dict         A pointer to a dictionary
 * key          A key
 */
void* dictSearch(Dict* d, const char* key);

/**
 * Searches and returns the pointer to data associated to the longest key
 * in the dictionary, whose letters are contained in the letters string
 * given as argument. If no such key exists, returns a null pointer.
 *
 * /!\ This method should only be implemented for 'Trie.c'.
 *
 * PARAMETERS
 * dict         A pointer to a dictionary
 * letters      A string of sorted letters
 */
void* dictSearchLongest(Dict* d, const char* letters);

/**
 * Inserts data at a given key in a dictionary.
 *
 * PARAMETERS
 * dict         A pointer to a dictionary
 * key          A key
 * data         A pointer to data
 */
void dictInsert(Dict* d, const char* key, void* data);

#endif // !_DICT_H_
