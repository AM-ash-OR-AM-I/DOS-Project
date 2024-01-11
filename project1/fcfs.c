// #include "fcfs.h"
#include "fcfs.h"
#include "inputs.h"
#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int chars = 50;

void get_inputs(FCFS *fcfs, int n) {
  int process_ids[n], arrival_times[n], burst_times[n];
  inputArr(process_ids, n, "Enter the process ids: ");
  inputArr(arrival_times, n, "Enter the arrival times: ");
  inputArr(burst_times, n, "Enter the burst times: ");

  for (int i = 0; i < n; i++) {
    fcfs->processes[i].pid = process_ids[i];
    fcfs->processes[i].burst_time = burst_times[i];
    fcfs->processes[i].arrival_time = arrival_times[i];
  }
}

// Allocating memory
FCFS *createFCFS(int no_of_processes) {
  FCFS *fcfs;
  fcfs->no_of_processes = no_of_processes;
  fcfs->processes = (Process *)malloc(sizeof(Process) * no_of_processes);
  get_inputs(fcfs, no_of_processes);
  return fcfs;
}

// Calculate Completion Time
void calculate_ct(FCFS *fcfs) {
  Process *processes = fcfs->processes;
  int curr_time = processes[0].arrival_time;
  for (int i = 0; i < fcfs->no_of_processes; i++) {
    curr_time += processes[i].burst_time;
    processes[i].completion_time = curr_time;
  }
}

// Calculate turnaround time
void calculate_tat(FCFS *fcfs) {
  double sum_tat = 0, tat;
  Process *processes = fcfs->processes;
  int n = fcfs->no_of_processes;
  for (int i = 0; i < n; i++) {
    tat = processes[i].completion_time - processes[i].arrival_time;
    processes[i].turnaround_time = tat;
    sum_tat += tat;
  }
  fcfs->avg_tat_time = sum_tat / n;
}

// Calculate waiting time
void calculate_wt(FCFS *fcfs) {
  Process *processes = fcfs->processes;
  double sum_wt = 0, wt;
  int n = fcfs->no_of_processes;
  for (int i = 0; i < n; i++) {
    wt = processes[i].turnaround_time - processes[i].burst_time;
    processes[i].waiting_time = wt;
    sum_wt += wt;
  }
  fcfs->avg_wt_time = sum_wt / n;
}

// Calculate response time
void calculate_rt(FCFS *fcfs) {
  Process *processes = fcfs->processes;
  double sum_rt = 0, rt;
  int n = fcfs->no_of_processes;
  processes[0].response_time = 0;
  for (int i = 1; i < n; i++) {
    rt = processes[i - 1].completion_time - processes[i].arrival_time;
    processes[i].response_time = rt;
    sum_rt += rt;
  }
  fcfs->avg_rt_time = sum_rt / n;
}

void display(FCFS *fcfs) {
  divider();
  printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
  divider();
  Process *processes = fcfs->processes;
  display_table(fcfs, processes);
  divider();
  printf("Avg. Turn-around time = %lf\nAvg. Waiting Time = %lf\nAvg. "
         "Response Time = %lf\n",
         fcfs->avg_tat_time, fcfs->avg_wt_time, fcfs->avg_rt_time);
  display_gantt(fcfs);
}

void divider() {
  for (int i = 0; i < chars; i++)
    printf("-");
  printf("\n");
}

void display_gantt(FCFS *fcfs) {
  printf("Gantt Chart:\n");
  divider();
  for (int i = 0; i < fcfs->no_of_processes; i++) {
    printf("%d\t|", fcfs->processes[i].pid);
  }
  printf("\n");
  divider();
  printf("t=0\t");
  for (int i = 1; i < fcfs->no_of_processes; i++) {
    printf("%d\t ", fcfs->processes[i - 1].completion_time);
  }
  printf("\n\n");
}

void display_table(FCFS *fcfs, Process *processes) {
  for (int i = 0; i < fcfs->no_of_processes; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid,
           processes[i].arrival_time, processes[i].burst_time,
           processes[i].completion_time, processes[i].turnaround_time,
           processes[i].waiting_time, processes[i].response_time);
  }
}
