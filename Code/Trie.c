#include <stdlib.h>
#include <string.h>

extern char* strdup(const char*);  // strdup not declared in C99

#include "Dict.h"

/*
A node structure definition where isLeaf is an int (should be bool) 
telling whether the node itself contains some data or not, 
whether it marks the end of a key
*/
struct TrieNode{
    void* data;
    int isLeaf;            
    struct TrieNode* children[26];
};
typedef struct TrieNode TrieNode;

static char* stringSort(const char string[]);
static TrieNode* make_TrieNode(void* data);
static void free_TrieNode(TrieNode* node);
static void insert(TrieNode* root, const char* key, void* data);
static void* search(TrieNode* root, const char* key);
static void* dictSearchLongest2(TrieNode* node, char* letters, size_t start_index, char* best_word);


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

/*
A function to create a TrieNode
*/
static TrieNode* make_TrieNode(void* data){
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if(node == NULL){
        return NULL;
    }
    for (int i=0; i<26; i++)
        node->children[i] = NULL;
    node->isLeaf = 0;
    node->data = data;
    return node;
}
/*
A function to free a TrieNode and all its descendants
*/
static void free_TrieNode(TrieNode* node){
    for (int i=0; i<26; i++){
        if(node->children[i]!= NULL){
            free_TrieNode(node->children[i]); //avant de free un node, on doit free tous ses enfants et leurs enfants...
        }
    }
    free(node);
}
/*
A function to insert a key and data defined over several nodes but starting at "root"
*/

static void insert(TrieNode* root, const char* key, void* data){
    TrieNode* current_node = root;
    for(size_t i=0; key[i] != '\0'; i++){
        int a_ascii = 'a';
        int letter_ascii = key[i];
        int index = letter_ascii-a_ascii;
        if(current_node->children[index]==NULL){ //no path for that prefix so far
            current_node->children[index] = make_TrieNode(NULL);
        }
        //else : node with prefix key[0]key[1]...key[i] exists
        current_node = current_node->children[index];
    }

    current_node->isLeaf = 1;
    current_node->data = data;
}

/*
A function to search for a key in the trees or subtrees starting at "root"
*/
static void* search(TrieNode* root, const char* key){
    TrieNode* current_node = root;
    for(int i=0; key[i] != '\0'; i++){
        int a_ascii = 'a';
        int letter_ascii = key[i];
        int index = letter_ascii-a_ascii; // from 97 to 122
        if(current_node->children[index]==NULL)
            return NULL;
        current_node = current_node->children[index];
    }
    if(current_node->isLeaf==1 && current_node != NULL){ //retirer != NULL
        return current_node->data;
    }
    return NULL;  
}


struct Dict_t {
    TrieNode* root;
    size_t nbKeys;
};


Dict* dictCreateEmpty() {
    Dict* d = malloc(sizeof(Dict));
    if (!d)
        return NULL;
    d-> root = make_TrieNode(NULL); //NULL?
    d-> nbKeys = 0;
    return d;

}

size_t dictNbKeys(Dict *d) {
    return d->nbKeys;
}

void dictFree(Dict* d) {
    free_TrieNode(d->root);
    free(d);
}

int dictContains(Dict* d, const char* key) {
    return dictSearch(d,key) != NULL;
}
void* dictSearch(Dict* d, const char* key) {
    return search(d->root,key);
}

void* dictSearchLongest(Dict* d, const char* letters) {
    //letters should be sorted
    TrieNode* root = d->root;
    char*  long_word = "";
    char* letterz = stringSort(letters);
    return dictSearchLongest2(root,letterz,0,long_word);
}
/*
An auxiliary function to find the longest constructible word located in the subtrees of "node"
*/
static void* dictSearchLongest2(TrieNode* node, char* letters, size_t start_index, char* best_word){
    if(node->isLeaf==1){
        char* word = node->data;
        if(strlen(word)>strlen(best_word)){
            best_word=word;
        }
    }
    size_t len = strlen(letters);
    int a_ascii = 'a';
    for(size_t i = start_index ; i<len ;i++){
        int letter_ascii = letters[i];
        int index = letter_ascii-a_ascii;
        if(node->children[index]!=NULL){
            best_word = dictSearchLongest2(node->children[index],letters,i+1,best_word);
        }        
    }
    return best_word;
}

void dictInsert(Dict* d, const char* key, void* data) {
    insert(d->root,key,data);
    d->nbKeys++;
}   

