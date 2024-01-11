#include "process.h"
#pragma once

typedef struct fcfs {
  int no_of_processes;
  Process *processes;
  double avg_tat_time;
  double avg_wt_time;
  double avg_rt_time;
} FCFS;

FCFS *createFCFS(int no_of_processes);
void calculate_ct(FCFS *fcfs);
void calculate_tat(FCFS *fcfs);
void calculate_wt(FCFS *fcfs);
void calculate_rt(FCFS *fcfs);
void display(FCFS *fcfs);
void divider();
void display_gantt(FCFS *fcfs);
void display_table(FCFS *fcfs, Process *processes);