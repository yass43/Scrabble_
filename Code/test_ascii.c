#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Dict.h"
#include "LinkedList.h"
#include "Scrabble.h"


struct ScrabbleDict_t {
    Dict* wordis;// à compléter
};


static char* sorter(const char my_word[]){
    char* string = strdup(my_word);
	char temp;
	int i, j;
	int n = strlen(string);
	for (i = 0; i < n-1; i++) {
		for (j = i+1; j < n; j++) {
			if (string[i] > string[j]) {
                temp = string[i];
                string[i] = string[j];
                string[j] = temp;
            }
		}
	}
    return string;
}

void generateAllSubsets(const char* letters, int n, int index,int sizesubset, char* subset, 
                        int i, List* my_list){
    if (index == sizesubset){
        llInsertLast(my_list, llCreateNode(strdup(subset)));
        return;
    }
    if (i >= n){
        return;
    }
    subset[index] = letters[i];
    generateAllSubsets(letters, n, index+1, sizesubset, subset, i+1, my_list);
    generateAllSubsets(letters, n,index, sizesubset, subset, i+1, my_list);
}


ScrabbleDict* scrabbleCreateDict(List* words) {
    ScrabbleDict* sd = malloc(sizeof(ScrabbleDict));// à compléter
    if (!sd)
        return NULL;
    sd->wordis = dictCreateEmpty();
    // printf("huh?\n");
    // dictInsert(sd->wordis, "a", "a");
    //for each element in list insert element in dictionnary
    Node* element = llHead(words);
    // printf("HERE\n");
    while (element){
        // printf("IS\n");
        // printf("key: %s\n",sorter(llData(element)));
        // printf("key: %s\n",(char*)llData(element));
        dictInsert(sd->wordis, sorter(llData(element)), llData(element));
        // printf("MEE\n");
        element = llNext(element);
    }
    return sd;
}

void scrabbleFreeDict(ScrabbleDict* sd) {
    dictFree(sd->wordis);// à compléter
}

char* scrabbleFindLongestWord(ScrabbleDict* sd, const char* letters) {
    size_t nbLetters = strlen(letters);// à compléter
    size_t nbSubLetters = nbLetters;
    letters = strdup(sorter(letters));
    if (dictContains(sd->wordis, letters) == 1){
        return dictSearch(sd->wordis, letters);
    }
    while(nbSubLetters>0){
        char subset[20];
        List* jad_list = llCreateEmpty();
        generateAllSubsets(letters, nbLetters, 0, nbSubLetters,subset,0,jad_list);
        Node* now = llHead(jad_list);
        while (!dictContains(sd->wordis, llData(now))){
            now = llNext(now);
            if (!now){
                break;
            }
        }
        if (now != NULL && dictContains(sd->wordis, llData(now))==1){
            return dictSearch(sd->wordis, llData(now));
        }
        else{
            subset[nbSubLetters-1] = '\0';
            nbSubLetters = nbSubLetters-1;
        }
    }return 0;
}