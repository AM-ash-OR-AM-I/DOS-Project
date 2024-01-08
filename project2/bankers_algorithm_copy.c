#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n_process, n_resource;

typedef struct process {
  int *alloted;
  int *claim;
  int *need;
  int completed;
} process;

process **get_inputs(process **process_list);
void calculate_need(process **process_list);
void display_all_mat(process **process_list);

int main() {
  printf("Enter number of process: ");
  scanf("%d", &n_process);
  printf("Enter number of resources: ");
  scanf("%d", &n_resource);
  process **process_list = malloc(sizeof(process *) * n_process);
  get_inputs(process_list);
  calculate_need(process_list);
  display_all_mat(process_list);
}

process **get_inputs(process **process_list) {
  printf("Enter the Allocation matrix:\n");

  // Get allocation matrix
  for (int i = 0; i < n_process; i++) {
    // Allocate memory to each process pointer.
    process_list[i] = malloc(sizeof(process));

    // Allocate memory to allocation matrix
    process_list[i]->alloted = (int *)malloc(sizeof(int) * n_resource);
    for (int j = 0; j < n_resource; j++) {
      scanf("%d", &(process_list[i]->alloted[j]));
    }
  }

  printf("Enter the Claim matrix:\n");
  // Get Claim matrix
  for (int i = 0; i < n_process; i++) {
    // Allocate memory to claim matrix
    process_list[i]->claim = (int *)malloc(sizeof(int) * n_resource);
    for (int j = 0; j < n_resource; j++) {
      scanf("%d", &(process_list[i]->claim[j]));
    }
  }

  return process_list;
}

void calculate_need(process **process_list) {
  for (int i = 0; i < n_process; i++) {
    // Allocate memory to need matrix
    process_list[i]->need = (int *)malloc(sizeof(int) * n_resource);
    for (int j = 0; j < n_resource; j++) {
      process_list[i]->need[j] =
          process_list[i]->claim[j] - process_list[i]->alloted[j];
    }
  }
}

void display_all_mat(process **process_list) {
  printf("PID\tALLOCATION\n");
  for (int i = 0; i < n_process; i++) {
    printf("%d\t", i);
    for (int j = 0; j < n_resource; j++) {
      printf("%d ", process_list[i]->alloted[j]);
    }
    printf("\n");
  }
  printf("\n");
  printf("PID\tCLAIM\n");
  for (int i = 0; i < n_process; i++) {
    printf("%d\t", i);
    for (int j = 0; j < n_resource; j++) {
      printf("%d ", process_list[i]->claim[j]);
    }
    printf("\n");
  }
  printf("\n");

  printf("PID\tNEED\n");
  for (int i = 0; i < n_process; i++) {
    printf("%d\t", i);
    for (int j = 0; j < n_resource; j++) {
      printf("%d ", process_list[i]->need[j]);
    }
    printf("\n");
  }
  printf("\n");
}