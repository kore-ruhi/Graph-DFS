/*
Ruhi Kore

Graph.c

Thile file contains a list of manipulation and access functions that allow us to interact with the Graph abstract data type.
It implements Graphs through the List ADT.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj
{
    List* neighbors;
    int* color;   
    int* parent;  
    int* distance;
    int* discover;
    int* finish;
    int order;    
    int size;     
    int source;   
}   GraphObj;

typedef GraphObj* Graph;

/****************************************************************** Constructors-Destructors ******************************************************************/

/*
Function: newGraph (int n)

Description:
Returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges

Pre-Conditions:
None
*/
Graph newGraph (int n)
{
    Graph G;
    G = malloc (sizeof (GraphObj));
    G -> neighbors = malloc( (n + 1) * sizeof(List));
    G -> color = malloc( (n + 1) * sizeof(int));
    G -> parent = malloc( (n + 1) * sizeof(int));
    G -> discover = calloc(n + 1, sizeof(int));
    G -> finish = calloc(n + 1, sizeof(int));    
    
    G -> order = n;
    G -> size = NIL;

    for (int x = 1; x <= n; x++)
    {
        G -> neighbors[x] = newList();
        G -> color[x] = WHITE;
        G -> parent[x] = NIL;
        G -> discover[x] = UNDEF;
        G -> finish[x] = UNDEF;
    }
    return G;
}

/*
Function: freeGraph (Graph* pG)

Description:
Frees all dynamic memory associated with the Graph *pG,then sets the handle *pG to NULL

Pre-Conditions:
None
*/
void freeGraph (Graph* pG)
{
    for (int i = 1; i <= getOrder (*pG); i++)
    {
        freeList(& (*pG) -> neighbors[i]);
        free((*pG) -> neighbors[i]);
    }
    free((*pG) -> neighbors);
    (*pG) -> neighbors = NULL;
    free((*pG)->color);
    (*pG) -> color = NULL;
    free((*pG)->parent);
    (*pG) -> parent = NULL;
    free((*pG)->discover);
    (*pG) -> discover = NULL;
    free((*pG)->finish);
    (*pG) -> finish = NULL;
    free(*pG);
    *pG = NULL;
}

/*
Function: transpose (Graph G)

Description:
Returns a reference to a new graph object representing the transpose of G

Pre-Conditions:
None
*/
Graph transpose(Graph G)
{
    Graph nGraph = newGraph(G -> order);

    for (int n = 1; n <= getOrder(G); n++)
    {
        moveFront(G -> neighbors[n]);
        List nGraph2 = G -> neighbors[n];
        if (index(nGraph2) >= 0)
        {
            while (index(nGraph2) >= 0)
            {
                int x = get(nGraph2);
                addArc(nGraph, x, n);
                moveNext(nGraph2);
            }
        }
    }
    return nGraph;
}

/*
Function: copyGraph (Graph G)

Description:
Returns a reference to a new graph which is a copy of G

Pre-Conditions:
None
*/
Graph copyGraph(Graph G) 
{
    Graph temp = newGraph(getOrder(G));
    for (int x = 1; x <= getOrder(G); x++) 
    {
        moveFront(G -> neighbors[x]);
        if (length(G -> neighbors[x]) != 0)
        {
            return NULL;
        }
        while (index(G -> neighbors[x]) >= 0) 
        {
            addArc(temp, x, get(G -> neighbors[x]));
            moveNext(G -> neighbors[x]);
        }
    }
    return temp;
}
/****************************************************************** Access functions ******************************************************************/

/*
Function: getOrder (Graph G)

Description:
Returns the "order" field value

Pre-Conditions:
None
*/
int getOrder (Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "ERROR: G is NULL. Function: getOrder()\n");
        exit(1);
    }
    else
    {
        return G -> order;
    }
}

/*
Function: getSize (Graph G)

Description:
Returns the "size" field value

Pre-Conditions:
None
*/
int getSize (Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "ERROR: G is NULL. Function: getSize()\n");
        exit(1);
    }
    else
    {
        return G -> size;
    }
}

/*
Function: getParent (Graph G, int u)

Description:
Returns the parent of vertex u in the Breadth- First tree created by BFS(), or NIL if BFS() has not yet been called

Pre-Conditions:
1 <= u <= getOrder(G)
*/
int getParent (Graph G, int u)
{
    if (G == NULL)
    {
        fprintf(stderr, "ERROR: G is NULL. Function: getParent()\n");
        exit(1);
    }
    else if (u >= 1 && u <= getOrder(G))
        return G -> parent[u];
    else
    {
        fprintf(stderr, "ERROR: Pre-Conditions not met. Function: getParent()\n");
        exit(1);
    }
}

/*
Function: getDiscover (Graph G, int u)

Description:
Returns the "discover" field value.

Pre-Conditions:
1 <= u <= getOrder(G)
*/
int getDiscover (Graph G, int u)
{
    if (G != NULL)
    {
        if (u >= 1 && u <= getOrder(G))
        {
            return G -> discover[u];
        }
        else
        {
            fprintf(stderr, "ERROR: u is out of bounds. Function: getDiscover()\n");
            exit(1);
        }
    }
    else
    {
        fprintf(stderr, "ERROR: G is NULL. Function: getDiscover()\n");
        exit(1);
    }
}

/*
Function: getFinish (Graph G, int u)

Description:
Returns the "finish" field value.

Pre-Conditions:
1 <= u <= getOrder(G)
*/
int getFinish (Graph G, int u)       //NEED TO DO
{
    if (G != NULL)
    {
        if (u >= 1 && u <= getOrder(G))
        {
            return G -> finish[u];
        }
        else
        {
            fprintf(stderr, "ERROR: u is out of bounds. Function: getDiscover()\n");
            exit(1);
        }
    }
    else
    {
        fprintf(stderr, "ERROR: G is NULL. Function: getDiscover()\n");
        exit(1);
    }
}

/****************************************************************** Manipulation procedures ******************************************************************/
/*
Function: addEdge (Graph G, int u, int v)

Description:
Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u

Pre-Conditions:
two int arguments must lie in the range 1 to getOrder(G)
*/
void addEdge(Graph G, int u, int v)
{
    if(G == NULL)
    {
        fprintf(stderr, "ERROR: G is NULL. Function: addEdge()\n");
        exit(1);
    }
    else if (u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G))
    {
        fprintf(stderr, "ERROR: Pre-Conditions not met. Function: addEdge()\n");
        exit(1);
    }
    else
    {
        addArcHelper (G -> neighbors[u], v); // inserting v into row u
        addArcHelper (G -> neighbors[v], u); // inserting u into row v
        (G -> size)++;
    }
}

/*
Function: addArc

Description:
Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)

Pre-Conditions:
Two int arguments must lie in the range 1 to getOrder(G)
*/
void addArc(Graph G, int u, int v)      //DONE
{
    if (G != NULL)
    {
        if (1 <= u && u <= getOrder(G))
        {
            if (1 <= v && v <= getOrder(G))
            {
                List tempList = G -> neighbors[u];
                int condition = addArcHelper(tempList, v);
                if (condition != -1)
                {
                    G->size++;
                }
            }
            else
            {
                fprintf(stdout, "ERROR: v is out of bounds. Function: addArc()\n\n");
                exit(1);   
            }
        }
        else
        {
            fprintf(stdout, "ERROR: u is out of bounds. Function: addArc()\n\n");
            exit(1);   
        }
    }
    else
    {
        fprintf(stdout, "ERROR: G is NULL. Function: addArc()\n\n");
        exit(1);   
    }
}


/*
Function: addArcHelper

Description:
Inserts vertices into a list. Serves as a helper function for addEdge and addArc

Pre-Conditions:
None
*/
int addArcHelper (List L, int x)
{
    int count = 0;
    if (length(L) == 0)
    {
        append(L, x);
        count = 1;
    }
    else
    {
        moveFront(L);
        while (index(L) != -1)
        {
            int count = get(L);
            if (x < count)
            {
                insertBefore(L, x);
                count = 1;
                break;
            }
            else if (x == count)
            {
                count = NIL;
                break;
            } 
            else
            {
                moveNext(L);
            }
        }
        if (index(L) == -1)
        {
            append(L, x);
            count = 1;
        }
    }
    return count;
}

/*
Function: DFS

Description:
Runs the DFS algorithm on the Graph G

Pre-Conditions:
None
*/
void DFS(Graph G, List S) 
{
    if (G != NULL)
    {
        if (S != NULL)
        {
            if (length(S) == getOrder(G))
            {
                for (int n = 1; n <= getOrder(G); n++) 
                {
                    G -> color[n] = WHITE;
                    G -> parent[n] = NIL;
                }
                int time = 0;
                moveFront(S);
                while (index(S) >= 0) 
                {
                    int u = get(S);
                    if (G -> color[u] == WHITE) 
                    {
                        visit(G, S, u, &time);
                    }
                    moveNext(S);
                }
                for (int n = 0; n < getOrder(G); n++) 
                {
                    deleteBack(S);
                }
            }
            else
            {
                fprintf(stderr, "length(S) != getOrder(G). Function: DFS()\n");
                exit(1);
            }
        }
        else
        {
            fprintf(stderr, "ERROR: S is NULL. Function: DFS()\n");
            exit(1); 
        }
    }
    else
    {
        fprintf(stderr, "ERROR: G is NULL. Function: DFS()\n");
        exit(1);   
    }
}
 
/*
Function: DFS

Description:
Helper function for DFS

Pre-Conditions:
None
*/
void visit(Graph G, List S, int u, int *time) 
{
    if (G != NULL)
    {
        if (S != NULL)
        {
            G->discover[u] = ++*time;
            G->color[u] = GRAY;
            moveFront(G->neighbors[u]);
            while (index(G->neighbors[u]) >= 0) 
            {
                int y = get(G->neighbors[u]);
                //printf("int visit(): y is: %d\n", y);
                //printf("in visit(): G->parent[y] is: %d\n", G->parent[y]);
                if (G->color[y] == WHITE) 
                {
                    G->parent[y] = u;
                    //printf("in visit(): u is: %d\n", u);
                    //printf("in visit(): G->parent[y] is: %d\n", G->parent[y]);
                    visit(G, S, y, time);
                }
                moveNext(G->neighbors[u]);
            }
            G->color[u] = BLACK;
            G->finish[u] = ++*time;
            prepend(S, u);
        }
        else
        {
            fprintf(stderr, "ERROR: S is NULL. Function: visit()\n");
            exit(1); 
        }
    }
    else
    {
        fprintf(stderr, "ERROR: G is NULL. Function: visit()\n");
        exit(1); 
    }
}

/****************************************************************** Other operations ******************************************************************/
/*
Function: printGraph (FILE* out, Graph G)

Description:
Prints the adjacency list representation of G to the file pointed to by out

Pre-Conditions:
None
*/
void printGraph(FILE* out, Graph G)
{
    if(G == NULL)
    {
        fprintf(stderr, "ERROR: G is NULL. Function: printGraph()\n");
        exit(1);
    }
    else if(out == NULL)
    {
        fprintf(stderr, "ERROR: Output file is NULL. Function: printGraph()\n");
        exit(1);
    }
    for (int i = 1; i <= getOrder(G); i++)
    {
        List temp = G -> neighbors[i];
        fprintf(out, "%d:", i);
        moveFront(temp);
        while (index(temp) >= 0)
        {
            fprintf(out, " %d", get(temp));
            moveNext(temp);
        }
        fprintf(out, "\n");
    }
}
