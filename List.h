/*
Ruhi Kore

List.h

This file serves as the header file for the List.c file. The List functions are being used by the Graph ADT.
*/

#include <stdio.h>

#ifndef LIST_H_INCLUDE
#define LIST_H_INCLUDE

/* Exported type -------------------------------------------------------------- */
typedef struct NodeObj* Node;
typedef struct ListObj* List;

/* Constructors-Destructors --------------------------------------------------- */
Node newNode( int data);					//function description + preconditions (if any) are specified in List.c
void freeNode( Node* pN);					//function description + preconditions (if any) are specified in List.c
List newList(void);					//function description + preconditions (if any) are specified in List.c
void freeList(List* pL);					//function description + preconditions (if any) are specified in List.c

/* Access functions ----------------------------------------------------------- */
int length(List L);					//function description + preconditions (if any) are specified in List.c
int index(List L);					//function description + preconditions (if any) are specified in List.c
int front(List L);					//function description + preconditions (if any) are specified in List.c
int back(List L);					//function description + preconditions (if any) are specified in List.c
int get(List L);					//function description + preconditions (if any) are specified in List.c
int equals(List A, List B);					//function description + preconditions (if any) are specified in List.c
int isEmpty(List L);					//function description + preconditions (if any) are specified in List.c

/* Manipulation procedures ---------------------------------------------------- */
void clear(List L);					//function description + preconditions (if any) are specified in List.c
void moveFront(List L);					//function description + preconditions (if any) are specified in List.c
void moveBack(List L);					//function description + preconditions (if any) are specified in List.c
void movePrev(List L);					//function description + preconditions (if any) are specified in List.c
void moveNext(List L);					//function description + preconditions (if any) are specified in List.c
void prepend(List L, int data);					//function description + preconditions (if any) are specified in List.c
void append(List L, int data);					//function description + preconditions (if any) are specified in List.c
void insertBefore(List L, int data);					//function description + preconditions (if any) are specified in List.c
void insertAfter(List L, int data);					//function description + preconditions (if any) are specified in List.c
void deleteFront(List L);					//function description + preconditions (if any) are specified in List.c
void deleteBack(List L);					//function description + preconditions (if any) are specified in List.c
void delete(List L);					//function description + preconditions (if any) are specified in List.c

/* Other operations ----------------------------------------------------------- */
void printList(FILE* out, List L);					//function description + preconditions (if any) are specified in List.c
List copyList(List L);					//function description + preconditions (if any) are specified in List.c
#endif
