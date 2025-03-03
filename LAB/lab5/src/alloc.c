#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Process {
  int pid;
  int max_req;
  int cur;
  int completed;
} Process;

int main() {
  int processes_count; // number of processes
  int resource_count;  // number of resources
  Process *processes;  // this is a circular queue

  printf("processes: ");
  scanf("%d", &processes_count);

  processes = calloc(processes_count, sizeof(Process));

  printf("resources: ");
  scanf("%d", &resource_count);

  for (int i = 0; i < processes_count; i++) {
    Process temp;
    printf("max alloc + current alloc");
    scanf("%d %d", &temp.max_req, &temp.cur);
    temp.pid = i + 1;
    temp.completed = 0;

    processes[i] = temp;
  }

  return 0;
}
