#pragma once
typedef struct process {
  int pid;
  int arrival_time;
  int burst_time;
  int rem_time;
  int allocation_time;
  int completion_time;
  int turnaround_time;
  int waiting_time;
  int response_time;
} Process;