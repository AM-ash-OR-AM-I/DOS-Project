#include "inputs.h"
#include "process.h"
#include "queue.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

void divider_rr();

void get_inputs_rr(RR *rr, int n) {
  int process_ids[n], arrival_times[n], burst_times[n];
  inputArr(process_ids, n, "Enter the process ids: ");
  inputArr(arrival_times, n, "Enter the arrival times: ");
  inputArr(burst_times, n, "Enter the burst times: ");

  for (int i = 0; i < n; i++) {
    rr->processes[i].pid = process_ids[i];
    rr->processes[i].burst_time = burst_times[i];
    rr->processes[i].rem_time = burst_times[i];
    rr->processes[i].arrival_time = arrival_times[i];
    rr->processes[i].allocation_time = -1;
  }
}

// Allocating memory
RR *createRR(int no_of_processes, int time_quantum) {
  RR *rr;
  rr->no_of_processes = no_of_processes;
  rr->time_quantum = time_quantum;
  rr->processes = (Process *)malloc(sizeof(Process) * no_of_processes);
  rr->gantt_chart = (int *)calloc(100, sizeof(int));
  rr->timestamps = (int *)calloc(100, sizeof(int));
  rr->queue = create_queue(100);
  get_inputs_rr(rr, no_of_processes);
  return rr;
}

// Calculate Gantt Chart
void calculate_gt_rr(RR *rr) {
  Process *processes = rr->processes;
  int *timestamps = rr->timestamps;
  Queue *queue = rr->queue;

  // Add first process to ready queue
  enqueue(queue, &processes[0]);
  int curr_time = processes[0].arrival_time;
  int i = 0;
  rr->context_switches = 0;

  while (!is_empty(queue)) {
    rr->context_switches++;

    Process *curr_process = get_first(queue);
    if (curr_process->allocation_time < 0)
      curr_process->allocation_time = curr_time;

    int duration = (curr_process->rem_time < rr->time_quantum)
                       ? curr_process->rem_time
                       : rr->time_quantum;

    rr->timestamps[rr->context_switches - 1] = curr_time;
    curr_time += duration;

    rr->gantt_chart[rr->context_switches - 1] = curr_process->pid;

    curr_process->rem_time -= duration;

    dequeue(queue);
    while (processes[i + 1].arrival_time <= curr_time &&
           i < rr->no_of_processes - 1 &&
           processes[i + 1].allocation_time < 0) {
      enqueue(queue,
              &processes[++i]); // Add all arrived processes in ready queue that
                                // are not allocated before
    }
    if (curr_process->rem_time == 0) {
      curr_process->completion_time = curr_time;
    } else {
      // Add current process at last if it has rem time
      enqueue(queue, curr_process);
    }
    rr->timestamps[rr->context_switches] = curr_time;
    // display_queue(queue);
  }
}

// Calculate Completion Time
void calculate_ct_rr(RR *rr) {
  Process *processes = rr->processes;
  int curr_time = processes[0].arrival_time;
}

// Calculate turnaround time
void calculate_tat_rr(RR *rr) {
  double sum_tat = 0, tat;
  Process *processes = rr->processes;
  int n = rr->no_of_processes;
  for (int i = 0; i < n; i++) {
    tat = processes[i].completion_time - processes[i].arrival_time;
    processes[i].turnaround_time = tat;
    sum_tat += tat;
  }
  rr->avg_tat_time = sum_tat / n;
}

// Calculate waiting time
void calculate_wt_rr(RR *rr) {
  Process *processes = rr->processes;
  double sum_wt = 0, wt;
  int n = rr->no_of_processes;
  for (int i = 0; i < n; i++) {
    wt = processes[i].turnaround_time - processes[i].burst_time;
    processes[i].waiting_time = wt;
    sum_wt += wt;
  }
  rr->avg_wt_time = sum_wt / n;
}

// Calculate response time
void calculate_rt_rr(RR *rr) {
  Process *processes = rr->processes;
  double sum_rt = 0, rt;
  int n = rr->no_of_processes;
  processes[0].response_time = 0;
  for (int i = 1; i < n; i++) {
    rt = processes[i - 1].completion_time - processes[i].arrival_time;
    processes[i].response_time = rt;
    sum_rt += rt;
  }
  rr->avg_rt_time = sum_rt / n;
}

void display_gantt_rr(RR *rr) {
  printf("Gantt Chart:\n");
  divider();
  for (int i = 0; i < rr->context_switches; i++) {
    printf("%d\t|", rr->gantt_chart[i]);
  }
  printf("\n");
  divider();
  printf("t=%d\t", rr->timestamps[0]);
  for (int i = 1; i < rr->context_switches + 1; i++) {
    printf("%d\t ", rr->timestamps[i]);
  }
  printf("\n\n");
}

void display_table_rr(RR *rr, Process *processes) {
  for (int i = 0; i < rr->no_of_processes; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid,
           processes[i].arrival_time, processes[i].burst_time,
           processes[i].completion_time, processes[i].turnaround_time,
           processes[i].waiting_time, processes[i].response_time);
  }
}

void display_rr(RR *rr) {
  divider();
  printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
  divider();
  Process *processes = rr->processes;
  display_table_rr(rr, processes);
  divider();
  printf("Avg. Turn-around time = %lf\nAvg. Waiting Time = %lf\nAvg. "
         "Response Time = %lf\n",
         rr->avg_tat_time, rr->avg_wt_time, rr->avg_rt_time);
  display_gantt_rr(rr);
}

void divider_rr() {
  for (int i = 0; i < chars; i++)
    printf("-");
  printf("\n");
}
