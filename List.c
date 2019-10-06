/*
Ruhi Kore

List.c

This List ADT contains access and manipulation functions that are being used by the Graph ADT. 
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

//Structs -------------------------------------

//private NodeObj typedef
typedef struct NodeObj
{
  int data;
  struct NodeObj* prev;
  struct NodeObj* next;
} NodeObj;

//private Node typedef
typedef NodeObj* Node;

//private ListObj type
typedef struct ListObj
{
  Node front;
  Node back;
  Node cursor;
  int index;
  int length;
} ListObj;

//Constructors-Destructors ---------------------

//newNode()
//Returns refrence to new Node Object. Initializes next and data fields.
//Private.
Node newNode(int data)
{
  Node newNode = malloc(sizeof(NodeObj));
  newNode->data = data;
  newNode->next = NULL;
  return(newNode);
}

//freeNode()
//Frees heap memory pointed to by *pN, sets *pN to NULL.
//Private.
void freeNode(Node* pN)
{
  if( pN != NULL && *pN != NULL)
  {
    free(*pN);
    *pN = NULL;
  }
}

//newList()
//Returns refrence to new empty list object
List newList(void)
{
  List L;
  L = malloc(sizeof(ListObj));
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
  L->index = -1;
  return(L);
}

//freeList()
//Frees all heap memory associated with list *pL and sets *pL to NULL.
void freeList(List* pL)
{
  if(pL != NULL && *pL != NULL)
  {
    Node currNode = (*pL)->front;
    while(currNode != NULL)
    {
      deleteFront(*pL);
      currNode = (*pL)->front;
    }
    free(currNode);
  }
  free(*pL);
  *pL = NULL;
}

//Access Functions --------------------------------------

//Returns the length of the List
int length(List L)
{
  if(L == NULL)
  {
    printf("List Error: calling length() on NULL List Ref");
    exit(1);
  }
  return(L->length);
}

//Returns the index of the cursor element
int index(List L)
{
  if(L == NULL)
  {
    printf("List Error: calling index() on NULL List Ref");
    exit(1);
  }
  return(L->index);
}

//returns the front elements data.
int front(List L)
{
  if(L == NULL)
  {
    printf("List Error: calling front() on NULL List Ref");
    exit(1);
  }
  return(L->front->data);
}

//Returns the back element's data
int back(List L)
{
  if(L == NULL)
  {
    printf("List Error: calling back() on NULL List Ref");
    exit(1);
  }
  return(L->back->data);
}

//Returns the cursor's data
int get(List L)
{
  if(L == NULL || L->cursor == NULL)
  {
    printf("List Error: calling get() on NULL List Ref or List->cursor is NULL");
    exit(1);
  }
  return(L->cursor->data);
}

// Returns 1 if this List and L are the same integer
// sequence. Returns 0 in any other case.  The cursor
// is ignored in both lists.
int equals(List A, List B)
{
  if(A == NULL || B == NULL)
  {
    printf("List Error: Calling equals() on NULL List Ref");
    exit(1);
  }

  if(length(A) != length(B))
    return(0);

  Node aNode = A->front;
  Node bNode = B->front;

  while(aNode != NULL)
  {
    if(aNode->data != bNode->data)
    {
      aNode = bNode = NULL;
      return(0);
    }
    else 
    {
      aNode = aNode->next;
      bNode = bNode->next;
    }
  }
  return(1);
}

//Manipulation procedures ------------------------
// Resets List to its original empty state.
void clear(List L)
{
  if(L == NULL)
  {
    printf("List Error: Caling clear() on NULL List Ref");
    exit(1);
  }
  Node currNode = L->front;
  while(currNode != NULL)
  {
    deleteFront(L);
    currNode = L->front;
  }
  freeNode(&currNode);
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
  L->index = -1;
}

void moveFront(List L)
{// If List is non-empty, places the cursor under the front element, otherwise does nothing.
  if(L == NULL)
  {
    printf("List Error: Calling moveFront() on NULL List ref");
    exit(1);
  }
  if(L->length != 0)
  { //if length is not 0.
    L->cursor = L->front;
    L->index = 0;
  }
}

void moveBack(List L)
{// If List is non-empty, places the cursor under the back element, otherwise does nothing.
  if(L == NULL)
  {
    printf("List Error: Calling moveBack() on NULL List ref");
    exit(1);
  }
  if(L->length != 0)
  {
    L->cursor = L->back;
    L->index = L->length - 1;
  }
}

// If 0<getIndex()<=length()-1, moves the cursor one step toward the
// front of the list. If getIndex()==0, cursor becomes undefined.
// If getIndex()==-1, cursor remains undefined. This operation is
// equivalent to moveTo(getIndex()-1).
void movePrev(List L){
  if(L == NULL)
  {
    printf("List Error: Calling movePrev() on NULL List ref");
    exit(1);
  }
  if(L->cursor != NULL && L->index != 0)
  {//somewhere in the middle
    L->cursor = L->cursor->prev;
    L->index--;
  }
  else if(L->cursor != NULL && L->index == 0)
  {//at the front
    L->cursor = NULL;
    L->index = -1;
  }
}

// If 0<=getIndex()<length()-1, moves the cursor one step toward the
// back of the list. If getIndex()==length()-1, cursor becomes
// undefined. If index==-1, cursor remains undefined. This
// operation is equivalent to moveTo(getIndex()+1).
void moveNext(List L)
{
  if(L == NULL)
  {
    printf("List Error: Calling moveNext() on NULL List ref");
    exit(1);
  }
  if(L->cursor != NULL && L->index != L->length - 1)
  {//if cursor exits and not at the end
    L->cursor = L->cursor->next;
    L->index++;
  }
  else if(L->cursor != NULL && L->index == L->length - 1)
  {//if cursor exists and AT the end
    L->index = -1;
    L->cursor = NULL ;
  }
  else if(L->cursor == NULL){} //do nothing
}

// Inserts new element before front element in this List.
void prepend(List L,int data){
  // Insert new element into this List. If List is non-empty, insertion takes place before front element.
  if(L == NULL){
   printf("List Error: Calling prepend() on NULL List ref");
   exit(1);
  }
  Node nNode = newNode(data);
  nNode->prev = NULL;
  nNode->next = L->front;
  if(L->length > 0)
    L->front->prev = nNode;
  L->front = nNode;
  L->length++;
  if(L->cursor != NULL)//if cursor is defined
    L->index++;
  if(L->length == 1)//only one node in the list
    L->back = nNode;
}

// Inserts new element after back element in this List.
void append(List L, int data){// Insert new element into this List. If List is non-empty,
 // insertion takes place after back element.
  if(L == NULL){
    printf("List Error: Calling append() on NULL List ref");
    exit(1);
  }
  Node nNode = newNode(data);

  if(L->length == 0){//if nothing in list
    L->front = nNode;
    L->back = nNode;
    L->length++;
  }
  else
  {
    L->back->next = nNode;
    nNode->prev = L->back;
    L->back = nNode;
    L->length++;
  }
}

// Inserts new element before cursor element in this
// List. Pre: length()>0, getIndex()>=0
void insertBefore(List L, int data)
{//insert before cursor
  if(L == NULL || L->cursor == NULL)
  {
    printf("List Error: Calling insertBefore() on NULL List ref OR L->cursor");
    exit(1);
  }
  if(L->index == 0)
    prepend(L,data);
  else
  {
    Node nNode = newNode(data);
    nNode->prev = L->cursor->prev;
    nNode->next = L->cursor;
    L->cursor->prev->next = nNode;
    L->cursor->prev = nNode;
    L->index++;
    L->length++;
  }
}

// Inserts new element after cursor element in this
// List. Pre: length()>0, getIndex()>=0
void insertAfter(List L, int data)
{//insert element after cursor
  if(L == NULL || L->cursor == NULL)
  {
    printf("List Error: Calling insertAfter() on NULL List ref OR L->cursor");
    exit(1);
  }
  if(L->index == L->length - 1)
  {//index is at the end of the list
    append(L,data);
  }
  else 
  {
    Node nNode = newNode(data);
    L->cursor->next->prev = nNode;
    nNode->next = L->cursor->next;
    L->cursor->next = nNode;
    nNode->prev = L->cursor;
    L->length++;
  }
}

// Deletes the front element in this List. Pre: length()>0
void deleteFront(List L)
{//delete Front of list.
  if(L == NULL)
  {
    printf("List Error: Calling deleteFront() on NULL List ref");
    exit(1);
  }
  if(L->length == 0)
  {
    printf("List Error: Calling deleteFront() on empty List");
    exit(1);
  }
  Node nNode = L->front;

  if(L->length > 1)
  {
    L->front = L->front->next;
  } else{
    L->front = L->back = NULL;
  }
  freeNode(&nNode);
  L->length--;
  if(L->index == 0)
  {//if cursor is at the beginning, set to undefined.
    L->index = -1;
    L->cursor = NULL;
  }
  if(L->cursor != NULL) // if cursor exists
    L->index--;
}

// Deletes the back element in this List. Pre: length()>0
void deleteBack(List L)
{
  if(L == NULL)
  {
    fprintf(stderr, "ERROR: calling deleteBack() on a NULL list\n");
    exit(1);
  }
  else if(L -> length == 0)
  {
    printf("List Error: calling deleteBack() on an empty list\n");
    exit(1);
  }
  else if(L -> length == 1)
  {//if just one element in list
    if(L -> index == 0)
    { //if cursor is defined in a one elemnt list, delete cursor
      L -> index = -1;
      L -> cursor = NULL;
    }
    freeNode(&L->front);//deleting only element
    L -> front = NULL;
    L -> back = NULL;
    L -> length = 0;
  }
  else
  {
    if(L -> cursor == L->back)
    {
      L -> cursor = NULL;
      L -> index = -1;
    }
    Node nNode = L->back;
    L -> back = L -> back -> prev;
    L->back->next = NULL;
    freeNode(&nNode);
    L->length--;
  }
}

// Deletes cursor element in this List. Cursor is undefined after this
// operation. Pre: length()>0, getIndex()>=0
void delete(List L)
{
  if(L == NULL || L->cursor == NULL)
  {
    fprintf(stderr, "List Error: Calling delete() on NULL List ref OR L->cursor");
    exit(1);
  }

  if(L -> index == 0)//cursor is at the first element
    deleteFront(L);
  else
  {
    Node oldNode = L -> cursor;
    oldNode -> prev -> next = oldNode -> next;
    if(L -> index == L -> length - 1)//if cursor is last element
      L -> back = oldNode -> prev;
    else
      oldNode -> next -> prev = oldNode -> prev;
    freeNode(&oldNode);
    L -> cursor = NULL;
    L -> length--;
    L -> index = -1;
  }
}

// Prints data elements in L on a single line to stdout.
void printList(FILE *out, List L)
{
  moveFront(L);
  while(L -> cursor != NULL)
  {
    fprintf(out, "%d ",get(L));
    moveNext(L);
  }
}

// Returns a new list representing the same integer sequence as this
// list. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L)
{
  if(L == NULL)
  {
    fprintf(stderr, "ERROR: Calling copyList() on NULL List ref");
    exit(1);
  }
  List nList = newList();
  Node currNode = L -> front;
  while(currNode != NULL)
  {
    append(nList,currNode -> data);
    currNode = currNode -> next;
  }
  return(nList);
}
