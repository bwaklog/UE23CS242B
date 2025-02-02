#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	int pid;
	pid = fork();
	if (pid < 0) {
		printf("fork failure\n");
		exit(1);
	} else if (pid == 0) {
		printf("the clid process\n");
		printf("id of parent proc: %d | the child process id: %d\n", getpid(), getpid());
	} else {
		wait(NULL);
		printf("parent process");
		printf("id of parent: %d | id of the child process: %d\n", getpid(), pid);
	}

	return 0;
}
