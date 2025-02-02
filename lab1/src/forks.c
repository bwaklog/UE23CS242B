#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
	pid_t proc_id = fork();
	int status;
	if (proc_id < 0) {
		printf("failed to create a child proc\n");
		exit(1);
	} else if (proc_id) {
		printf("Entered parent process\n");
		waitpid(proc_id, &status, 0);
	} else {
		// this is the child proc
		printf("started child process\n");
		execl("/bin/ls", "ls", "-la", NULL);
	}
	return 0;
}
