/*
Ruhi Kore

Graph.h
 
This file is the header file for Graph.c. It contains all the function and struct definitions that are written in Graph.c.
*/

#ifndef _GRAPHH_INCLUDE_
#define _GRAPHH_INCLUDE_

#include <stdio.h>
#include "List.h"

typedef struct GraphObj* Graph;	//defines a type called Graph that points to the GraphObj struct

#define NIL 0
#define INF -1
#define UNDEF -1

/*** Constructors-Destructors ***/
Graph newGraph(int n);							//returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
void freeGraph(Graph* pG);						//frees all dynamic memory associated with the Graph *pG,then sets the handle *pG to NULL
Graph transpose(Graph G);						//returns a reference to a new graph object representing the transpose of G
Graph copyGraph(Graph G);						//returns a reference to a new graph which is a copy of G

/*** Access functions ***/
int getOrder(Graph G);							//returns the "order" field value
int getSize(Graph G);							//returns the "size" field value
int getParent(Graph G, int u);					//returns the parent of vertex u in the Breadth- First tree created by BFS(), or NIL if BFS() has not yet been called
												//precondition 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u); 				//returns the "discover" field value
												//precondition 1 <= u <= getOrder(G)
int getFinish(Graph G, int u); 					//returns the "finish" field value
												//precondition 1 <= u <= getOrder(G)
/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);			//inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u
												//has the precondition that their two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v);				//addArc() inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)
												//has the precondition that their two int arguments must lie in the range 1 to getOrder(G)
int addArcHelper (List L, int x);				//helper function for addArc
void DFS(Graph G, List s);						//runs the DFS algorithm on the Graph G
void visit(Graph G, List S, int u, int *time);	//helper function for the DFS algorithm

/*** Other operations ***/
void printGraph(FILE* out, Graph G);			//prints the adjacency list representation of G to the file pointed to by out

#endif
