#include "process.h"
#pragma once

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