#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

/** Node (opaque) structure */
typedef struct Node_t Node;

/** List (opaque) structure */
typedef struct List_t List;

/**
 * Creates a node referencing data and returns a pointer to it.
 *
 * PARAMETERS
 * data         A pointer to data
 */
Node* llCreateNode(void* data);

/**
 * Returns the data referenced by a node.
 *
 * PARAMETERS
 * node         A pointer to a node
 */
void* llData(Node* node);

/**
 * Returns the pointer to the node following a node in a list.
 *
 * PARAMETERS
 * node         A pointer to a node
 */
Node* llNext(Node* node);

/**
 * Creates an empty list and returns a pointer to it.
 */
List* llCreateEmpty(void);

/**
 * Returns a pointer to the head node of a list.
 *
 * PARAMETERS
 * list         A pointer to a list
 */
Node* llHead(const List* list);

/**
 * Returns a pointer to the tail node of a list.
 *
 * PARAMETERS
 * list         A pointer to a list
 */
Node* llTail(const List* list);

/**
 * Returns the number of nodes in a list.
 *
 * PARAMETERS
 * list         A pointer to a list
 */
size_t llLength(const List* list);

/**
 * Frees a linked list and all its nodes, but not the data.
 *
 * PARAMETERS
 * list         A pointer to a list
 */
void llFree(List* list);

/**
 * Frees a linked list, all its nodes and data.
 *
 * PARAMETERS
 * list         A pointer to a list
 */
void llFreeData(List* list);

/**
 * Inserts the node at the start of a list.
 *
 * PARAMETERS
 * list         A pointer to a list
 * node         A pointer to a node
 */
void llInsertFirst(List* list, Node* node);

/**
 * Removes the node at the start of a list and returns a pointer
 * to the removed node.
 *
 * PARAMETERS
 * list         A pointer to a list
 */
Node* llPopFirst(List* list);

/**
 * Inserts the node at the end of a list.
 *
 * PARAMETERS
 * list         A pointer to a list
 * node         A pointer to a node
 */
void llInsertLast(List* list, Node* node);

#endif // !_LINKED_LIST_H_
