/*
Ruhi Kore

GraphClient.c

This program tests and serves as the client for Graph.c.
*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
   int n = 8;
   List S = newList();
   Graph G = newGraph(n);
   for(int i = 1; i<=n; i++){
      append(S, i);
   }
   addArc(G, 1, 2);
   addArc(G, 2, 3);
   addArc(G, 2, 5);
   addArc(G, 2, 6);
   addArc(G, 3, 4);
   addArc(G, 3, 7);
   addArc(G, 4, 3);
   addArc(G, 4, 8);
   addArc(G, 5, 1);
   addArc(G, 5, 6);
   addArc(G, 6, 7);
   
   Graph T = transpose(G);
   Graph C = copyGraph(G);
   fprintf(stdout, "\n");
   fprintf(stdout, "Adjacency list representation of G (and its copy, C):\n");
   printGraph(stdout, C);
   
   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "1st call to DFS:\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(int i=1; i<=n; i++){
     fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "List S (after first call to DFS):\n");
   printList(stdout, S);
   fprintf(stdout, "\n");
   
   fprintf(stdout, "\n");
   fprintf(stdout, "Adjacency list representation of Transpose(G):\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "2nd call to DFS:\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(int i=1; i<=n; i++){
     fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "List S (after second call to DFS):\n");
   printList(stdout, S);
   fprintf(stdout, "\n");
   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}
