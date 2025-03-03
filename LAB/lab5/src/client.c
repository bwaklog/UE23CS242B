#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "msg.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("USAGE ./client <1 write/0 read>");
    exit(1);
  }

  int fd;
  char *fifo_path = "/tmp/db_client_fifo";

  int req = atoi(argv[1]);
  fd = open(fifo_path, O_WRONLY);

  switch (req) {
  case 0: {
    msg_t temp;
    temp.is_write = 0;
    temp.req_id = time(NULL);

    printf("sending read req id %d\n", temp.req_id);
    write(fd, &temp, sizeof(msg_t));
    close(fd);

    char recv_file_path[1024];
    sprintf(recv_file_path, "/tmp/read_%d", temp.req_id);
    mkfifo(recv_file_path, 0666);

    int recv_file = open(recv_file_path, O_RDONLY);
    char buffer[1024];

    read(recv_file, buffer, 1024);
    close(recv_file);
    unlink(recv_file_path);

    printf("recieved: %s\n", buffer);

    break;
  }
  case 1: {
    if (argc != 3) {
      exit(1);
    }
    msg_t temp;
    temp.is_write = 1;
    temp.req_id = time(NULL);
    strcpy(temp.content, argv[2]);

    printf("sending write req id %d\n", temp.req_id);
    write(fd, &temp, sizeof(msg_t));
    close(fd);
    break;
  }
  default: {
    break;
  }
  }

  close(fd);
  return 0;
}
