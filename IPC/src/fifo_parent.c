#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>

#define BUFFER_SIZE 100

int main() {
  char buff[BUFFER_SIZE] = "";
  char myfifo[BUFFER_SIZE] = "/tmp/myfifo";

  mkfifo(myfifo, 0666);

  while (1) {
    printf("(q quit)> ");
    scanf("%s", buff);
    int fd = open(myfifo, O_WRONLY);
    write(fd, buff, sizeof(buff) + 1);
    if (!strcasecmp(buff, "q")) {
      close(fd);
      return 0;
    }
    close(fd);
  }


  return 0;
}
