#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

extern char* strdup(const char*);  // strdup not declared in C99

#include "LinkedList.h"
#include "Scrabble.h"

const size_t BUFFER_SIZE = 256;
const size_t EXPERIMENTS = 1000;
const size_t MIN_LENGTH = 5;
const size_t MAX_LENGTH = 15;

const char* ALPHABET = "abcdefghijklmnopqrstuvwxyz";

/**
 * Creates a word of a given length with random letters.
 *
 * PARAMETERS
 * lenght       A positive integer
 */
static char* randomWord(size_t length) {
    char *letters = malloc((length + 1) * sizeof(char));
    if (!letters) {
        fprintf(stderr, "Allocation error in 'randomWord'.\n");
        exit(1);
    }

    letters[length] = '\0';
    for (size_t i = 0; i < length; i++)
        letters[i] = ALPHABET[rand() % 26];

    return letters;
}

/**
 * Returns the elapsed time, in seconds, with respect to a starting point.
 *
 * PARAMETERS
 * start        A starting point in clock ticks
 */
static double elapsed(clock_t start) {
    return ((double) (clock() - start)) / CLOCKS_PER_SEC;
}

int main(int argc, char **argv) {
    // Arguments
    char* letters = NULL;
    char* filename = "words_small.txt";//change to words_large

    if (argc > 1)
        letters = argv[1];

    if (argc > 2)
        filename = argv[2];

    // Load words in a linked list
    char buffer[BUFFER_SIZE];

    List* words = llCreateEmpty();
    if (!words) {
        fprintf(stderr, "Allocation error in 'llCreateEmpty'.\n");
        exit(1);
    }

    FILE* fp = fopen(filename, "r");

    while (fgets(buffer, BUFFER_SIZE, fp)) {
        size_t length = strlen(buffer);

        if (buffer[length - 1] == '\n')
            buffer[--length] = '\0';

        llInsertLast(words, llCreateNode(strdup(buffer)));
    }

    fclose(fp);
    printf("Read %li words in '%s'.\n", llLength(words), filename);

    // Create the scrabble dictionary
    clock_t start = clock();

    ScrabbleDict* sd = scrabbleCreateDict(words);
    if (!sd) {
        fprintf(stderr, "Allocation error in 'scrabbleCreateDict'.\n");
        exit(1);
    }

    printf("ScrabbleDict created in %f seconds.\n", elapsed(start));

    // Search for the longest word(s)
    if (letters) {
        start = clock();
        char* word = scrabbleFindLongestWord(sd, letters);

        if (word)
            printf("Longest matching word is '%s' (length=%li) (in %f seconds).\n", word, strlen(word), elapsed(start));
        else
            printf("No matching word found (in %f seconds).\n", elapsed(start));
    } else {
        //printf("no letters given dummy");
        char* tab[EXPERIMENTS];
        for (size_t i = 0; i < EXPERIMENTS; i++)
            tab[i] = randomWord(MIN_LENGTH + rand() % (MAX_LENGTH - MIN_LENGTH + 1));

        start = clock();
        //printf("we good 1\n");
        for (size_t i = 0; i < EXPERIMENTS; i++){
            //printf("tab is :  %s\n",tab[i]);
            //printf("%d\n",i);
            scrabbleFindLongestWord(sd, tab[i]);
            //printf("we good 2,%d\n",i);

        }

        printf("%f seconds to find %li words (length in [%li, %li]).\n",
               elapsed(start), EXPERIMENTS, MIN_LENGTH, MAX_LENGTH);

        for (size_t i = 0; i < EXPERIMENTS; i++)
            free(tab[i]);
    }

    // Free
    scrabbleFreeDict(sd);
    llFreeData(words);

    return 0;
}
