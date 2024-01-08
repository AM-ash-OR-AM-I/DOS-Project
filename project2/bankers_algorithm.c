#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct process {
  int *alloted;
  int *claim;
  int *need;
  int completed;
} process;

typedef struct bankers {
  int n_process;
  int n_resource;
  int *resource_vector;
  int *available_vector;
  int *safe_sequence;
  process **process_list;
} bankers;

void get_resource_vector(bankers *bankers);
void get_matrix(bankers *bankers);
void calculate_available_vector(bankers *bankers);
int calculate_safe_sequence(bankers *bankers);
void display_all_info(bankers *bankers);
void display_allocation(int n_process, int n_resource, process **process_list);
void display_claim(int n_process, int n_resource, process **process_list);
void display_need(int n_process, int n_resource, process **process_list);
void display_vectors(int n_resource, bankers *bankers);
void display_safe_seq(bankers *bankers);

int main() {
  bankers *bankers;
  printf("Enter number of process: ");
  scanf("%d", &(bankers->n_process));
  printf("Enter number of resources: ");
  scanf("%d", &(bankers->n_resource));
  printf("Enter the instances available for R1,R2...: ");
  get_resource_vector(bankers);
  get_matrix(bankers);
  calculate_available_vector(bankers);
  display_all_info(bankers);
  if (!calculate_safe_sequence(bankers)) {
    printf("Safe state not possible!\n");
    display_safe_seq(bankers);
  } else {
    printf("System is in safe state\n");
    display_safe_seq(bankers);
  }
}

void get_resource_vector(bankers *bankers) {
  int n_resource = bankers->n_resource;
  bankers->resource_vector = malloc(sizeof(int) * n_resource);
  for (int i = 0; i < n_resource; i++) {
    scanf("%d", &(bankers->resource_vector[i]));
  }
}

void get_matrix(bankers *bankers) {
  int n_process = bankers->n_process, n_resource = bankers->n_resource;
  process **process_list = malloc(sizeof(process *) * n_process);
  printf("Enter the Allocation matrix:\n");

  // Allocate pointer to each process
  for (int i = 0; i < n_process; i++) {
    process *p = malloc(sizeof(process));
    process_list[i] = p;
  }

  // Get allocation matrix
  for (int i = 0; i < n_process; i++) {
    // Allocate memory to allocation matrix
    process_list[i]->alloted = (int *)malloc(sizeof(int) * n_resource);
    process_list[i]->completed = 0;
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

  bankers->process_list = process_list;

  for (int i = 0; i < n_process; i++) {
    // Allocate memory to need matrix
    process_list[i]->need = (int *)malloc(sizeof(int) * n_resource);
    for (int j = 0; j < n_resource; j++) {
      process_list[i]->need[j] =
          process_list[i]->claim[j] - process_list[i]->alloted[j];
    }
  }

  bankers->process_list = process_list;
}

void calculate_available_vector(bankers *bankers) {
  int n_process = bankers->n_process, n_resource = bankers->n_resource;
  bankers->available_vector = (int *)malloc(sizeof(int) * n_process);
  process **process_list = bankers->process_list;
  for (int i = 0; i < n_process; i++) {
    int allocated_resource = 0;
    for (int j = 0; j < n_resource; j++) {
      allocated_resource += process_list[j]->alloted[i];
    }
    bankers->available_vector[i] =
        bankers->resource_vector[i] - allocated_resource;
  }
}

int calculate_safe_sequence(bankers *bankers) {
  int n_process = bankers->n_process, n_resource = bankers->n_resource;
  process **process_list = bankers->process_list;
  int safe = 0;
  int *safe_seq = malloc(sizeof(int) * n_process);
  int index = -1;
  for (int i = 0; i < n_process; i++) {
    int can_run = 1;
    if (process_list[i]->completed) {
      continue;
    }
    for (int j = 0; j < n_resource; j++) {
      if (process_list[i]->need[j] > bankers->available_vector[j]) {
        can_run = 0;
        break;
      }
    }

    if (can_run) {
      process_list[i]->completed = 1;
      for (int j = 0; j < n_resource; j++) {
        bankers->available_vector[j] += process_list[i]->alloted[j];
        // process_list[i]->need[j] = 0;
        // process_list[i]->alloted[j] = 0;
      }
      // display_vectors(n_resource, bankers);
      safe_seq[++index] = i + 1;
      i = 0; // Reset & scan from beg
    }
  }

  bankers->safe_sequence = safe_seq;
  for (int i = 0; i < n_process; i++) {
    if (process_list[i]->completed) {
      continue;
    }
    return 0;
  }

  return 1;
}

void display_all_info(bankers *bankers) {
  int n_process = bankers->n_process, n_resource = bankers->n_resource;
  process **process_list = bankers->process_list;
  display_allocation(n_process, n_resource, process_list);
  display_claim(n_process, n_resource, process_list);
  display_need(n_process, n_resource, process_list);
  display_vectors(n_resource, bankers);
}

void display_allocation(int n_process, int n_resource, process **process_list) {
  printf("PID\tALLOCATION\n");
  for (int i = 0; i < n_process; i++) {
    printf("%d\t", i + 1);
    for (int j = 0; j < n_resource; j++) {
      printf("%d ", process_list[i]->alloted[j]);
    }
    printf("\n");
  }
  printf("\n");
}

void display_claim(int n_process, int n_resource, process **process_list) {
  printf("PID\tCLAIM\n");
  for (int i = 0; i < n_process; i++) {
    printf("%d\t", i + 1);
    for (int j = 0; j < n_resource; j++) {
      printf("%d ", process_list[i]->claim[j]);
    }
    printf("\n");
  }
  printf("\n");
}

void display_need(int n_process, int n_resource, process **process_list) {
  printf("PID\tNEED\n");
  for (int i = 0; i < n_process; i++) {
    printf("%d\t", i + 1);
    for (int j = 0; j < n_resource; j++) {
      printf("%d ", process_list[i]->need[j]);
    }
    printf("\n");
  }
  printf("\n");
}

void display_vectors(int n_resource, bankers *bankers) {
  printf("Resource Vector:\n");
  for (int i = 0; i < n_resource; i++) {
    printf("%d | ", bankers->resource_vector[i]);
  }
  printf("\n");
  printf("Available Vector:\n");
  for (int i = 0; i < n_resource; i++) {
    printf("%d | ", bankers->available_vector[i]);
  }
  printf("\n");
}

void display_safe_seq(bankers *bankers) {
  int n_process = bankers->n_process;
  printf("Safe Sequence:\n");
  for (int i = 0; i < n_process; i++) {
    printf("%d | ", bankers->safe_sequence[i]);
  }
}
