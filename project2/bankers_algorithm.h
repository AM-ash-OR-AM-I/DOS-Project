#pragma once

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