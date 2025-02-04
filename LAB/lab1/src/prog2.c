#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// orphaned proc demostration
int main(int argc, char **argv) {
  pid_t pid = fork();

  if (pid > 0) {
    printf("this parent(%d) will exit\n", getpid());
    exit(0);
  } else if (pid == 0) {
    sleep(30);
    printf("child proc(%d) with parent (%d)\n", getpid(), getppid());
  }

  return 0;
}
