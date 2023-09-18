#include <stdlib.h>
#include <string.h>

#include<stdio.h>
extern char* strdup(const char*);  // strdup not declared in C99

#include "Dict.h"
static Dict* dictResize(Dict* d, size_t newSize);
static Dict* dictCreateEmpty2(size_t size);


typedef struct Node_t {
    char* key;
    void* data;
    struct Node_t* next;
} Node;

struct Dict_t {
    size_t size;
    size_t nbKeys;
    Node** array;
};


static size_t hash(const char* key) {
    size_t length = strlen(key);
    size_t sum = 0, base = 1, mod = 1000000007;

    for (size_t i = 0; i < length; i++) {
        sum = (sum + base * key[i]) % mod;
        base = (base * 256) % mod;
    }

    return sum;
}

Dict* dictCreateEmpty() {
    Dict* d = malloc(sizeof(Dict));
    if (!d)
        return NULL;

    d->size = 1000;
    d->nbKeys = 0;
    d->array = calloc(d->size, sizeof(Node*));
    if (!d->array) {
        free(d);
        return NULL;
    }

    return d;
}

size_t dictNbKeys(Dict *d) {
  return d->nbKeys;
}

void dictFree(Dict* d) {
    Node* a;
    Node* b;

    for (size_t i = 0; i < d->size; i++) {
        a = d->array[i];

        while (a) {
            b = a->next;
            free(a->key);
            free(a);
            a = b;
        }
    }

    free(d->array);
    free(d);
}

static Node* dictGet(Dict* d, const char* key) { //Returns the whose node.key = key
    Node* n = d->array[hash(key) % d->size];

    while (n && strcmp(n->key, key) != 0)
        n = n->next;

    return n;
}

int dictContains(Dict* d, const char* key) {
    return dictGet(d, key) != NULL;
}

void* dictSearch(Dict* d, const char* key) {
    Node* n = dictGet(d, key);

    if (n)
        return n->data;
    else
        return NULL;
}

void dictInsert(Dict* d, const char* key, void* data) {
    Node* n = dictGet(d, key);

    if (n) //if node with node.key=key already exists, just update its data
        n->data = data;
    else {
        size_t i = hash(key) % d->size;

        n = malloc(sizeof(Node)); //create node
        n->key = strdup(key);
        n->data = data;
        n->next = d->array[i];
        d->array[i] = n;
	d->nbKeys++;
    }
    //We double the size of the array if the load factor becomes larger than 75%. (We insert the value beforehand)
    //by creating a double size dictionnary (or a double size array?)
    if(d->nbKeys/d->size >= 0.75){
        //Dict* d2 = dictCreateEmpty2(2*d->size);
        //printf("initial size was %d\n ", d->size);
        //Dict** temp = dictResize(&d,(d->size))
        
        Dict* dico = dictResize(d,d->size*2);
        *d = *dico;
        //printf("new size is %d\n",d->size);
    }
}

static Dict* dictResize(Dict* d, size_t newSize){
    
    Dict* dico = dictCreateEmpty2(newSize);
    for(size_t i=0 ; i<d->size ; i++){
        Node* n = d->array[i];
        while(n){
            Node* tmp = n;
            tmp = malloc(sizeof(Node));
            tmp->key = strdup(n->key);
            tmp->data = n->data;
            printf("%s\n",(char *)tmp->data);
            size_t tmp_index = hash(tmp->key) % newSize;
            // We put the node in the new array (whether there is already a node at tmp_index does not matter)
            tmp->next = dico->array[tmp_index];
            dico->array[tmp_index] = tmp;
            dico->nbKeys++;
            n=n->next;
        }
    }
    printf("Created a new dico of size %d\n",dico->size);
    printf("Resize : The new dico has %d keys\n",dico->nbKeys);
    printf("Resize : The initial dico had %d keys\n",d->nbKeys);
    dictFree(d);//not sure
    return dico;
}

static Dict* dictCreateEmpty2(size_t size) {
    Dict* d = malloc(sizeof(Dict));
    if (!d)
        return NULL;

    d->size = size;
    d->nbKeys = 0;
    d->array = calloc(d->size, sizeof(Node*));
    if (!d->array) {
        free(d);
        return NULL;
    }

    return d;
}
//void dictInsert(Dict* d, const char* key, void* data)
//void* dictSearch(Dict* d, const char* key)
int main(){

    Dict* d =  dictCreateEmpty(5);
    printf("current dico size is %d\n", d->size);
    printf("current dico nbKeys is %d\n", d->nbKeys);
    dictInsert(d,"aertw","water");
    //printf("%s\n ", (char *) dictSearch(d, "aertw"));

    dictInsert(d,"aaabbb","bababa");
    //printf("%s\n ", (char *) dictSearch(d, "aaabbb"));
    
    dictInsert(d,"belu","blue");
    //printf("%s\n ", (char *) dictSearch(d, "belu"));

    dictInsert(d,"der","red");
    //printf("%s\n ", (char *) dictSearch(d, "der"));
    printf("current dico size is %d\n" ,d->size);
    printf("current dico nbKeys is %d\n" ,d->nbKeys);
    
    dictInsert(d,"ddzjkbe","problem");
    //printf("%s\n ", (char *) dictSearch(d, "aertw"));
    //printf("%s\n ", (char *) dictSearch(d, "aaabbb"));
    //printf("%s\n ", (char *) dictSearch(d, "belu"));
    //printf("%s\n ", (char *) dictSearch(d, "der"));
    //printf("%s\n ", (char *) dictSearch(d, "ddzjkbe"));
    //dictInsert(d,"abc","bac");
    //printf("%s\n ", (char *) dictSearch(d, "abc"));

    printf("current dico size is %d\n" ,d->size);
    printf("current dico nbKeys is %d\n" ,d->nbKeys);

    

    return 0;
}