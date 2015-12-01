#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;

typedef struct stack {
  int data;
  struct stack * next;
} Node;

void raise_exception_if_empty(struct stack * headRef);
bool isEmpty(struct stack * headRef);
int peek(struct stack * headRef);
Node * pop(struct stack ** headRef);
void push(struct stack ** headRef, int newData);

int main(){
  Node * myStack = malloc(sizeof(Node));
  myStack = NULL;

  push(&myStack, 3);
  push(&myStack, 2);
  push(&myStack, 1);

  //just some demonstration of use
  printf("Peeking... %d\n", peek(myStack));
  printf("Popped: %d\n", pop(&myStack)->data);
  printf("Empty?: %d\n", isEmpty(myStack));
  printf("Popped: %d\n", pop(&myStack)->data);
  printf("Peeking... %d\n", peek(myStack));
  printf("Popped: %d\n", pop(&myStack)->data);
  printf("Empty?: %d\n", isEmpty(myStack));

  //either should raise error
  //peek(myStack);
  //pop(&myStack);

  exit(EXIT_SUCCESS);
}

void raise_exception_if_empty(struct stack * headRef){
  if(isEmpty(headRef)) {
    fprintf(stderr, "Stack is empty! Aborting...\n");
    exit(EXIT_FAILURE);
  }
}

bool isEmpty(struct stack * headRef){
  return !headRef;
}

int peek(struct stack * headRef){
  raise_exception_if_empty(headRef);
  return headRef->data; 
}

Node * pop(struct stack ** headRef){
  raise_exception_if_empty(*headRef);
  Node * top = *headRef;
  *headRef = top->next;
  return top;
}

void push(struct stack ** headRef, int newData){
  Node * newNode = malloc(sizeof(Node));
  newNode->data = newData;
  newNode->next = *headRef;
  *headRef = newNode;
}
