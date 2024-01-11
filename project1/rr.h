#include "process.h"
#include "queue.h"

#pragma once

typedef struct rr {
  int no_of_processes;
  int time_quantum;
  Process *processes;
  Queue *queue;
  int *gantt_chart;
  int *timestamps;
  int context_switches;
  double avg_tat_time;
  double avg_wt_time;
  double avg_rt_time;
} RR;

RR *createRR(int no_of_processes, int time_quantum);
void calculate_gt_rr(RR *rr);
void calculate_tat_rr(RR *rr);
void calculate_wt_rr(RR *rr);
void calculate_rt_rr(RR *rr);
void display_rr(RR *rr);
void display_gantt_rr(RR *rr);
void display_table_rr(RR *rr, Process *processes);
void display_rr(RR *rr);
void divider_rr();
