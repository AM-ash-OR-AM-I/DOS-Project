// Implement Round Robin  & FCFS scheduling
#include "fcfs.c"
#include "rr.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char choice;
  while (1) {
    printf("Choose Option:\n"
           "1. FCFS\n"
           "2. RR\n"
           "3. Exit\n"
           "Enter your choice: ");
    scanf("%c", &choice);
    int n;
    switch (choice) {
    case '1': { // Braces are required to declare/allocate memory
      printf("Enter the numnber of processes: ");
      scanf("%d", &n);
      FCFS *fcfs = createFCFS(n);
      calculate_ct(fcfs);
      calculate_tat(fcfs);
      calculate_wt(fcfs);
      calculate_rt(fcfs);
      display(fcfs);
      break;
    }
    case '2': {
      printf("Enter the numnber of processes: ");
      scanf("%d", &n);
      printf("Enter the time quantum: ");
      int time_quantum;
      scanf("%d", &time_quantum);
      RR *rr = createRR(n, time_quantum);
      calculate_gt_rr(rr);
      calculate_ct_rr(rr);
      calculate_tat_rr(rr);
      calculate_wt_rr(rr);
      calculate_rt_rr(rr);
      display_rr(rr);
      break;
    }
    case '3':
      printf("Exiting..");
      return 1;
    default:
      printf("Invalid Choice: %c\n", choice);
      break;
    }
    fflush(stdin); // Flush stdin to prevent catching new line as input.
  }
}