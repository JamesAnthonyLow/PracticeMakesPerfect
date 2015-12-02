#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graphQueue {
  void * data;
  struct graphNode * head;
  struct graphNode * tail;
} graphNode;

