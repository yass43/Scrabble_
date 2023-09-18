#include <stdlib.h>
#include <string.h>
#include <stdio.h> //for testing
#include "Dict.h"



struct TrieNode{
    char set_of_letters[20]; //useless as if node->children[3] != NULL, it means we know that a "d" is there
    void* data;
    int isLeaf;            
    struct TrieNode* children[26];
};
typedef struct TrieNode TrieNode;

static TrieNode* make_TrieNode(char* set_of_letters, void* data){//struct TrieNode*?
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    for (int i=0; i<26; i++)
        node->children[i] = NULL;
    node->isLeaf = 0;
    node->data = data;
    int length = strlen(set_of_letters);
    for(int i=0; i < length ;i++){
        node->set_of_letters[i]=set_of_letters[i];
    }
    /*
      maybe always insert "\" and when insert() almost finishes, change its data to data
    */
    return node;
}

static void free_TrieNode(TrieNode* node){
    for (int i=0; i<26; i++){
        if(node->children[i]!= NULL){
            free_TrieNode(node->children[i]); //avant de free un node, on doit free tous ses enfants et leurs enfants...
        }
    }
    free(node);
}

static void insert(TrieNode* root, const char* key, void* data){
    TrieNode* current_node = root;
    for(int i=0; key[i] != '\0'; i++){
        //printf("%c",key[i]);
        int a_ascii = 'a';
        int letter_ascii = key[i];
        int index = letter_ascii-a_ascii; // from 97 to 122
        if(current_node->children[index]==NULL){ //no path for that prefix so far
            //printf("no path so far\n");
            current_node->children[index] = make_TrieNode("",NULL);//make_TrieNode(key[i],data); maketrienode(key[i:])
        }
        //else : node with prefix key[0]key[1]...key[i] exists
        current_node = current_node->children[index];
    }
    //We inserted the whole world, check if it works when we try to insert a word already present
    current_node->isLeaf = 1;
    current_node->data = data;
    printf("Insertion succeded\n");
}

static void* search(TrieNode* root, const char* key){
    int length = strlen(key);
    TrieNode* current_node = root;
    for(int i=0; i < length; i++){
        //printf("%c",key[i]);
        int a_ascii = 'a';
        int letter_ascii = key[i];
        int index = letter_ascii-a_ascii; // from 97 to 122
        if(current_node->children[index]==NULL)
            return NULL;
        current_node = current_node->children[index];
        //printf("%p\n",current_node->data);
    }
    if(current_node->isLeaf==1 && current_node != NULL){ //retirer != NULL
        printf("found key\n");//ok it works but output is weird
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
    d-> root = make_TrieNode("",NULL); //NULL?
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
    //
}

void dictInsert(Dict* d, const char* key, void* data) {
    insert(d->root,key,data);
    d->nbKeys++;
}
 

//testing

int main()
{
    

    Dict* d =  dictCreateEmpty();
    dictInsert(d, "eholl","hello");
    printf("%s\n ", (char *) dictSearch(d, "eholl"));       
    dictInsert(d, "aaabbb","bababa");
    printf("%s\n ", (char *) dictSearch(d, "aaabbb"));
  
    /*
    Dict* d = dictCreateEmpty();
    dictInsert(d, "hello","");
    printf("%s ", (char *) dictSearch(d, "hello"));

    printf("%zu",d->nbKeys);
    
printf("dico size should be 2");
    free_TrieNode(head);
    printf("%zu",head)
    if(head==NULL){
        printf("head is null\n");
    }



    printf("%p ", search(head, "helll"));      
 
    insert(head, "hell",NULL);
    printf("%p ", search(head, "hell"));       
 
    insert(head, "h",NULL);
    printf("%p \n", search(head, "h"));         
 
    if (head == NULL) {
        printf("Trie empty!!\n");               // Trie is empty now
    }
    */
 
    return 0;
}
//testing

