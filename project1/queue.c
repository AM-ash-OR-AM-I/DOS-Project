#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementing Process Queue

typedef struct {
  int first, last;
  int curr_size;
  int capacity;
  Process **processes;
} Queue;

Queue *create_queue(int capacity);
Process *dequeue(Queue *queue);
Process *get_first(Queue *queue);
void enqueue(Queue *queue, Process *process);
void display_queue(Queue *queue);
int is_empty(Queue *queue);
int is_full(Queue *queue);

Queue *create_queue(int capacity) {
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  queue->capacity = capacity;
  queue->curr_size = 0;

  queue->processes = (Process **)malloc(queue->capacity * sizeof(Process *));
  return queue;
}

int is_empty(Queue *queue) { return queue->curr_size == 0; }
int is_full(Queue *queue) { return queue->curr_size == queue->capacity; }

void enqueue(Queue *queue, Process *process) {
  if (is_full(queue)) {
    return;
  } else if (is_empty(queue)) {
    queue->first = queue->last = 0;
  } else {
    queue->last++;
  }
  queue->curr_size++;
  queue->processes[queue->last] = process;
}

Process *dequeue(Queue *queue) {
  if (is_empty(queue)) {
    exit(0);
  }
  queue->curr_size--;
  queue->first++;
  return queue->processes[queue->first];
}

void display_queue(Queue *queue) {
  if (is_empty(queue)) {
    printf("Queue is empty!");
    return;
  }
  for (int i = queue->first; i <= queue->last; i++) {
    printf("%d <- ", queue->processes[i]->pid);
  }
  printf("\n");
}

Process *get_first(Queue *queue) { return queue->processes[queue->first]; }

// int main() {
//   Queue *queue = create_queue(100);
//   Process pr1 = {1, 2, 3, 4, 5, 6, 7, 8};
//   Process *p1 = &pr1;
//   Process pr2 = {2, 3, 4, 5, 6, 7, 8, 9};
//   Process *p2 = &pr2;
//   enqueue(queue, p1);
//   display_queue(queue);
//   enqueue(queue, p2);
//   display_queue(queue);
//   p2->pid = 3423;
//   dequeue(queue);
//   display_queue(queue);
//   dequeue(queue);
//   display_queue(queue);
//   // q.size = 10;
// }
