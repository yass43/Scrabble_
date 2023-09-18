#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
extern char* strdup(const char*);  // strdup not declared in C99

#include <math.h> //for pow(a,b)
#include "Dict.h"
#include "LinkedList.h"
#include "Scrabble.h"

static char* stringSort(const char string[]);
static size_t countSetBits(int n);


struct ScrabbleDict_t {
    // à compléter
    Dict* dict;
};

/*
A function to sort a string mostly copied from 
https://codescracker.com/c/program/c-program-sort-string.htm
*/
static char* stringSort(const char string[]){
    int i, j, len;
    len = strlen(string);
    char* str = strdup(string);
    char chTemp;
    for(i=0; i<len; i++)
    {
        for(j=0; j<(len-1); j++)
        {
            if(str[j]>str[j+1])
            {
                chTemp = str[j];
                str[j] = str[j+1];
                str[j+1] = chTemp;
            }
        }
    }  
    return str;
}

ScrabbleDict* scrabbleCreateDict(List* words) {
    ScrabbleDict* sd = malloc(sizeof(ScrabbleDict));
    if(sd == NULL){
        return NULL;
    }
    sd->dict = dictCreateEmpty();
    Node* tmp = llHead(words);
    char* word = NULL;//check
    char* key = NULL;
    while(tmp){
        word = llData(tmp);
        key = stringSort(word);
        dictInsert(sd->dict,key,word);
        tmp = llNext(tmp);
    }
    return sd; 
}

void scrabbleFreeDict(ScrabbleDict* sd) {
    dictFree(sd->dict);
    free(sd);
}

char* scrabbleFindLongestWord(ScrabbleDict* sd, const char* letters) {
    letters = strdup(stringSort(letters));
    char* current_best_word = malloc(strlen(letters)*sizeof(char));
    size_t n = strlen(letters);
    size_t nb_of_subsets = pow(2,n);
    size_t index,i;
    char* word = NULL;
    size_t counter=0;
    size_t subset_size=0;
    for(index=0; index < nb_of_subsets; index++){ //index = 1 2 3 ...2^n
        subset_size = countSetBits(index);
        char* subset = malloc((subset_size+1)*sizeof(char));
        counter=0;
        if(subset==NULL){
            return NULL;
        }
        for(i = 0; i < n; i++){
            if(index & (1<<i) && counter < subset_size ){//checks if the i-th bit of index is 1.
                subset[counter]=letters[i];//writing too far?
                counter++;
            }
        }
        if(dictContains(sd->dict,subset)){
            word = dictSearch(sd->dict,subset);
            if(strlen(word)>strlen(current_best_word)){
                current_best_word = strdup(word);
            }  
        }
        free(subset);
    }
    return current_best_word;
}

/*
A function to compute the number of bits turned on in the binary representation of an integer
e.g : countSetBits(5)=2 since bin(5)=101 contains 2 "1".
*/
static size_t countSetBits(int n){
    size_t count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}

