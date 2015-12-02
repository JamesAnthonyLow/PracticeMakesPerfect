#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph graphNode, *graphP;
typedef struct edges edge, *edgePtr;

struct graph {
  int numOfNodes;
  int name;
  bool visited;
  edgePtr adjacents;
};

struct edges {
  graphNode * data;
  struct edges * next;  
};

void err(char * errorMessage);

edgePtr createEdgePtr(graphNode * newData);

void addEdge(graphP graph, int from, int to);

graphP createGraph(int numOfNodes);

graphNode createNode(int name);

void destroyGraph(graphP graph);

void displayGraph(graphP graph);

int main(){
  graphP myGraph = createGraph(7);
  addEdge(myGraph, 0, 1);
  addEdge(myGraph, 0, 4);
  addEdge(myGraph, 2, 4);
  addEdge(myGraph, 4, 6);
  addEdge(myGraph, 5, 6);
  addEdge(myGraph, 6, 5);
  addEdge(myGraph, 6, 3);

  displayGraph(myGraph);
  destroyGraph(myGraph);

  exit(EXIT_SUCCESS);
}

graphP createGraph(int numOfNodes){
  graphP newGraph = malloc(numOfNodes * sizeof(graphNode));

  if(!newGraph) 
    err("Not enough memory to create graph! Aborting...\n");

  for(int i=0; i < numOfNodes; i++){
    newGraph[i] = createNode(i);
  }

  newGraph->numOfNodes = numOfNodes;

  return newGraph;
}

graphNode createNode(int name){
  graphNode newNode;

  newNode.name = name;
  newNode.visited = false;
  newNode.adjacents = malloc(sizeof(edge));

  return newNode;
}

edgePtr createEdgePtr(graphNode * newData){
  edgePtr newEdge = malloc(sizeof(edge));

  if(!newEdge)
    err("Not enough memory for edge pointer. Aborting...\n");

  newEdge->data = newData;

  return newEdge;
}

void addEdge(graphP graph, int from, int to){

  if(!graph[from].adjacents->data){
    graph[from].adjacents = createEdgePtr(&graph[to]);
  } else {
    edgePtr newEdge = createEdgePtr(&graph[to]);
    newEdge->next = graph[from].adjacents;
    graph[from].adjacents = newEdge;
  }

}

void destroyGraph(graphP graph){
  edgePtr tmp1 = malloc(sizeof(edge));
  edgePtr tmp2 = malloc(sizeof(edge));

  if(!(tmp1 && tmp2))
    err("Not enough memory for edge pointers, everyone run for the hills!\n");

  for(int i = 0; i < graph->numOfNodes; i++){
    tmp1 = graph[i].adjacents->next;
    free(graph[i].adjacents);
    while(tmp1){
     tmp2 = tmp1->next;
     free(tmp1);
     tmp1 = tmp2;
     tmp2 = NULL;
    }
  }

  free(tmp2);
  free(graph);
}

void displayGraph(graphP graph){
  edge tmp;

  for(int i = 0; i < graph->numOfNodes; i++){
    printf("Node %d Edges: ", i);
    tmp = *graph[i].adjacents;
    for(;;){

      if(tmp.data) printf("%d ", tmp.data->name);

      if(tmp.next == NULL) break;

      tmp = *tmp.next;
    }
    printf("\n");
  }
}

void err(char * errorMessage){

  fprintf(stderr, errorMessage);

  exit(EXIT_FAILURE);
}


