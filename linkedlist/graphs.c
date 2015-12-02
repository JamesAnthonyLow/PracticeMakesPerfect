#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph graphNode, *graphP;
typedef struct edges edge, *edgesP;

struct graph {
  int numOfNodes;
  int name;
  bool visited;
  edgesP adjacents;
};

struct edges {
  graphNode * data;
  struct edges * next;  
};

void err(char * errorMessage){
  fprintf(stderr, errorMessage);
  exit(EXIT_FAILURE);
}

graphNode createNode(int name);

edge * createEdgePtr(graphNode * newData);
void addEdge(graphP graph, int from, int to);

graphP createGraph(int numOfNodes);
void destroyGraph(graphP graph);
void displayGraph(graphP graph);

int main(){

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
  return newNode;
}

edge * createEdgePtr(graphNode * newData){
  edge * newEdge = malloc(sizeof(edge));
  if(!newEdge)
    err("Not enough memory for edge pointer. Aborting...\n");
  newEdge->data = newData;
  //free(newData);
  return newEdge;
}

void addEdge(graphP graph, int from, int to){
  if(!graph[from].adjacents->data){
    graph[from].adjacents = createEdgePtr(&graph[to]);
  } else {
    graph[from].adjacents->next = createEdgePtr(&graph[to]);
    graph[from].adjacents = graph[from].adjacents->next;
  }
}

void destroyGraph(graphP graph){
  edge * tmp1 = malloc(sizeof(edge));
  edge * tmp2 = malloc(sizeof(edge));
  if(!(tmp1 && tmp2))
    err("Not enough memory for edge pointers, everyone run for the hills!\n");
  for(int i = 0; i < graph->numOfNodes; i++){
    tmp1 = graph[i].adjacents->next;
    free(graph[i].adjacents);
    while(tmp1){
     tmp2 = tmp1->next;
     free(tmp1);
     tmp1 = tmp2;
    }
  }
  free(graph);
}

void displayGraph(graphP graph){
  edge * tmp;
  for(int i = 0; i < graph->numOfNodes; i++){
    printf("Node %d Edges:", i);
    tmp = graph[i].adjacents;
    while(tmp){
      printf("%d", tmp->data->name);
      tmp = tmp->next;
    }
    printf("\n");
  }
  free(tmp);
}
