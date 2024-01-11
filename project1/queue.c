#include "queue.h"
#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementing Process Queue

Queue *create_queue(int capacity) {
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  queue->capacity = capacity;
  queue->curr_size = 0;

  queue->processes = (Process **)malloc(queue->capacity * sizeof(Process *));
  return queue;
}

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

int is_empty(Queue *queue) { return queue->curr_size == 0; }
int is_full(Queue *queue) { return queue->curr_size == queue->capacity; }
Process *get_first(Queue *queue) { return queue->processes[queue->first]; }