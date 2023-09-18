#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Scrabble.h"


struct ScrabbleDict_t {
    List* words;
};

static size_t maximum(size_t a, size_t b);


static bool match(const char* letters, char* word) {
    

    size_t nbLetters = strlen(letters);
    size_t lengthWord = strlen(word);
    if (lengthWord > nbLetters)
        return false;
    
    size_t occ_letters[26]={0};
    size_t occ_word[26]={0};
    size_t max =  maximum(nbLetters,lengthWord);
    //We count the number of occurrences of each letter for the word and for the letters set
    for(size_t i=0; i< max;i++){
        if(i<nbLetters){
            occ_letters[letters[i]-97]++;
        }
        if(i<lengthWord){
            occ_word[word[i]-97]++;
        }
    }
    //To build the word, we need every for every letter occ_set(letter)>=occ_word(letter)
    for(size_t i=0;i<26;i++){
        if(occ_word[i]>occ_letters[i])
            return false;
    }
    return true;
}

/*
A function to compute the maximum between two size_t.
*/
static size_t maximum(size_t a, size_t b){
    if(a==b)
        return a;
    if(a<b)
        return b;
    else 
        return a;
}

ScrabbleDict* scrabbleCreateDict(List* words) {
    ScrabbleDict* sd = malloc(sizeof(ScrabbleDict));
    if (!sd)
        return NULL;

    sd->words = words;

    return sd;
}

void scrabbleFreeDict(ScrabbleDict* sd) {
    free(sd);
}

char* scrabbleFindLongestWord(ScrabbleDict* dict, const char* letters) {
    char* longestWord = NULL;
    size_t longestLength = 0;

    for (Node* p = llHead(dict->words); p != NULL; p = llNext(p)) {
        char* word = llData(p);

        if (match(letters, word)) {
            size_t length = strlen(word);

            if (length > longestLength) {
                longestWord = word;
                longestLength = length;
            }
        }
    }

    return longestWord;
}
