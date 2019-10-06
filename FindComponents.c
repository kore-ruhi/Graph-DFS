/*
Ruhi Kore
 
FindComponents.c

This module, when given a digraph, identifies all the strongly connected components of the graph.
*/
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

int main (int argc, char* argv[])
{
    if(argc > 3 || argc < 3)
    {
        fprintf(stderr, "Usage: <input file> <output file>\n");
        exit(1);
    }

    FILE *input;
    FILE *output;
  
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    if(input == NULL)
    {
        fprintf(stderr, "ERROR: Can't open file %s for reading input.\n", argv[1]);
        exit(1);
    }

if(output == NULL)
{
    printf("ERROR: Unable to open file %s for writing\n",argv[2]);
    exit(1);
}

  char line[100];

  fgets(line,100,input);

  int numVertices = atoi(line);

  Graph G = newGraph(numVertices);

  //Populating the graph
  while(fgets(line,100,input) != NULL)
  {
    char *token;
    token = strtok(line, " ");

    int a = atoi(token);

    token = strtok(NULL, " ");

    int b = atoi(token);

    if(a == 0 && b == 0)
      break;
    else addArc(G, a, b);
  }

    fprintf(output, "Adjacency list representation of G:\n");
    printGraph(output, G);

    List mainList = newList();

    for(int x = 1; x <= getOrder(G); x++)
    {
        append(mainList,x);
    }
    printList(stdout,mainList);
    printf("\n");
    DFS(G,mainList);

    printList(stdout,mainList);
    printf("\n");

    Graph transposeGraph = transpose(G);

    DFS(transposeGraph,mainList);
    printList(stdout,mainList);
    printf("\n");
    int numComponents = 0;

    for(int i = 1; i < getOrder(G) + 1; i++)
    {
        if(getParent(transposeGraph,i) == NIL)
            numComponents++;
    }

    fprintf(output, "\nG contains %d strongly connected components:\n", numComponents);

    List tempList = newList();
    moveBack(mainList);

    int x = 1;
    while(index(mainList) > -1)
    {
        prepend(tempList, get(mainList));
        if(getParent(transposeGraph, get(mainList)) == NIL)
        {
            fprintf(output, "Component %d: ", x);
            printList(output, tempList);
            fprintf(output,"\n");
            x++;
            clear(tempList);
        }
        movePrev(mainList);
    }


    fclose(input);
    fclose(output);

    freeList(&mainList);
    freeList(&tempList);
    freeGraph(&G);
    freeGraph(&transposeGraph);
}

/*fprintf(output, "Adjacency list representation of G:\n");
  printGraph(output, G);

  List S = newList();

  for(int i = 1; i < getOrder(G) + 1; i++){
    append(S,i);
  }
  printList(stdout,S);
  printf("\n");
  DFS(G,S);

  printList(stdout,S);
  printf("\n");
  //graphTransposse;
  Graph tGraph = transpose(G);

  //S now contains the discovery times from largest to smallest.
  DFS(tGraph,S);
  printList(stdout,S);
  printf("\n");
  int numComponets = 0;

  for(int i = 1; i < getOrder(G) + 1; i++){
    if(getParent(tGraph,i) == NIL)
      numComponets++;
  }

  fprintf(output, "\nG contains %d strongly connected components:\n", numComponets);

  //since the "stack" isn't an actual stack, we need to reverse the order of it.
  List tempList = newList();
  moveBack(S);

  int x = 1;
  while(index(S) != -1){
    prepend(tempList, get(S));
    if(getParent(tGraph, get(S)) == NIL){
      fprintf(output, "Component %d: ", x);
      printList(output, tempList);
      fprintf(output,"\n");
      clear(tempList);
      x++;
    }
    movePrev(S);
  }


  fclose(input);
  fclose(output);

  freeGraph(&G);
  freeGraph(&tGraph);
  freeList(&S);
  freeList(&tempList); */
