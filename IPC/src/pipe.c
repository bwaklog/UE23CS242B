#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 20

int main()  {
  char write_buff[BUFFER_SIZE] = "Hello World!";
  char read_buff[BUFFER_SIZE] = "";
  int fd[2];
  pid_t p1;

  // creating a pipe
  if (pipe(fd) == -1) {
    printf("failed to create a pipe.\n");
    exit(1);
  }

  p1 = fork();
  if (p1 > 0) {
    // this is the parent process
    // so we are gonna close the 
    close(fd[0]);
    write(fd[1], write_buff, strlen(write_buff) + 1);
    printf("parent: sent %s down pipe\n", write_buff);
    close(fd[1]);
  } else if (p1 == 0) {
    close(fd[1]);
    read(fd[0], read_buff, BUFFER_SIZE);
    printf("child: recieved %s\n", read_buff);
  } else {
    printf("failed to create a child\n");
    exit(1);
  }

  return 0;
}
