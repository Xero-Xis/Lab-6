#include<stdio.h> 
#include<limits.h>
#include<stdlib.h>
#include "process.h"
#include "util.h"

// Function to find the waiting time for all processes
void findWaitingTimeRR(ProcessType plist[], int n,int quantum) 
{ 
  int rem_bt[n]; // Array to store remaining burst times
  for (int i = 0; i < n; i++) {
    rem_bt[i] = plist[i].bt; // Copy burst times
  }

  int wt[n]; // Array to store waiting times
  for (int i = 0; i < n; i++) {
    wt[i] = 0; // Initialize waiting times to 0
  }

  int t = 0; // Current time

  while (true) {
    bool all_done = true; // Flag to check if all processes are finished

    for (int i = 0; i < n; i++) {
      if (rem_bt[i] > 0) { // Process not finished
        all_done = false;

        if (rem_bt[i] > quantum) { // Execute for quantum time
          t += quantum;
          rem_bt[i] -= quantum;
        } else { // Process finishes within quantum
          t += rem_bt[i];
          rem_bt[i] = 0;
          wt[i] = t - plist[i].bt; // Calculate waiting time
        }
      }
    }

    if (all_done) {
      break; // All processes finished
    }
  }

  // Print waiting times
  printf("\nWaiting times for RR (quantum %d):\n", quantum);
  for (int i = 0; i < n; i++) {
    printf("Process %d: %d\n", plist[i].pid, wt[i]);
  }
} 

void findWaitingTimeSJF(ProcessType plist[], int n)
{ 
  int current_time = 0;
  int completed_processes = 0;

  while (completed_processes < n) {
    int min_index = -1;
    int min_remaining_time = INT_MAX;
    for (int i = 0; i < n; i++) {
      if (plist[i].art <= current_time && !plist[i].wt) { // Only consider arrived and not completed processes
        if (plist[i].bt < min_remaining_time) {
          min_index = i;
          min_remaining_time = plist[i].bt;
        }
      }
    }

    if (min_index == -1) {
      current_time++;
      continue;
    }

    plist[min_index].bt--;

    if (plist[min_index].bt == 0) {
      plist[min_index].wt = current_time - plist[min_index].art;
      completed_processes++;
    }

    current_time++;
  }

  // Print waiting times
  printf("\nWaiting times for SJF:\n");
  for (int i = 0; i < n; i++) {
    printf("Process %d: %d\n", plist[i].pid, plist[i].wt);
  }
} 

void findWaitingTime(ProcessType plist[], int n)
{ 
  plist[0].wt = 0 +  plist[0].art; 
  for (int i = 1; i < n ; i++) 
    plist[i].wt =  plist[i-1].bt + plist[i-1].wt; 
} 

void findTurnAroundTime( ProcessType plist[], int n)
{ 
  for (int i = 0; i < n ; i++) 
    plist[i].tat = plist[i].bt + plist[i].wt; 
} 

int my_comparer(const void *this, const void *that)
{ 
  ProcessType *p1 = (ProcessType *)this;
  ProcessType *p2 = (ProcessType *)that;
  return p1->pri - p2->pri;
} 

