#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) { 
  pid_t pid;

  pid = fork(); // we create a fork of the
		// parent proc

  if (pid < 0) {
    perror("fork creation failed\n");
    return 1;
  } else if (pid == 0) {
    printf("child proc(%d) with parent(%d)\n", 
		    getpid(), getppid());
    execl("/bin/ps", "ps", NULL);
  } else {
    int status;
    wait(&status);
    execl("/bin/ls", "ls", "-lah", NULL);
    printf("parent proc(%d) completed", getpid());
  }
  return 0;
}
