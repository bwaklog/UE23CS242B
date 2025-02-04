#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int pid;
	int status;

	pid = fork();
	if (pid < 0) {
		printf("fork failed\n");
		return 1;
	} else if (pid == 0) {
		printf("child process created\n");
		printf("parent PID %d | child PID = %d\n", getpid(), getpid());
	} else {
		printf("parent created\n");
		printf("parent PID %d | child PID %d\n", getpid(), pid);
		wait(&status);
		printf("completed\n");
	}
	return 0;
}
