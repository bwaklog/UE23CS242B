#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUFFER_SIZE 100

int main() {
  char buff[BUFFER_SIZE] = "";
  char myfifo[BUFFER_SIZE] = "/tmp/myfifo";

  while (1) {
    int fd = open(myfifo, O_RDONLY);
    read(fd, buff, BUFFER_SIZE);
    if (!strcasecmp(buff, "q")) {
      close(fd);
      return 0;
    }
    printf("read from fifo: %s\n", buff);
    strcpy(buff, "");
    close(fd);
  }

  return 0;

}
