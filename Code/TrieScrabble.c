#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

extern char* strdup(const char*);  // strdup not declared in C99

#include "Dict.h"
#include "LinkedList.h"
#include "Scrabble.h"


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
    char* word = NULL;
    char* key = NULL;
    while(tmp){
        word = llData(tmp);
        key = stringSort(word);
        dictInsert(sd->dict,key,word);//Problem here
        tmp = llNext(tmp);
    }


    return sd; 
}


void scrabbleFreeDict(ScrabbleDict* sd) {
    dictFree(sd->dict);
    free(sd);
}

 
char* scrabbleFindLongestWord(ScrabbleDict* sd, const char* letters) {
    return dictSearchLongest(sd->dict,letters);
}