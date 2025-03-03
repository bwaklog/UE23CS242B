#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "msg.h"

typedef struct RW_Lock {
  int readers;
  sem_t *rw;
  sem_t *mutex;
} RW_Lock;

typedef struct DiskRequest {
  int is_write;
  char content[1024];
} DiskRequest;

typedef struct Queue {
  pthread_mutex_t mutex;
} Queue;

typedef struct db_file_t {
  RW_Lock *rw_lock;
  char db_file[1024];
  Queue *q;
} db_file_t;

db_file_t *db_file;

RW_Lock *rw_lock_init(int max_readers) {
  RW_Lock *r = malloc(sizeof(RW_Lock));
  r->rw = 0;

  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);

  r->mutex = sem_open("/tmp/server_mutex", O_CREAT, 0644, 1);
  r->rw = sem_open("/tmp/server_rw", O_CREAT, 0644, 1);
  return r;
}

void write_lock(RW_Lock *rw_lock) {
  sem_wait(rw_lock->rw);
  printf("[DEBUG][%s:%s:%d] aquire write lock\n", __FILE_NAME__, __func__,
         __LINE__);
  return;
}

void write_unlock(RW_Lock *rw_lock) {
  sem_post(rw_lock->rw);
  printf("[DEBUG][%s:%s:%d] release write lock\n", __FILE_NAME__, __func__,
         __LINE__);
  return;
}

void read_lock(RW_Lock *rw_lock) {
  sem_wait(rw_lock->mutex);
  rw_lock->readers++;
  printf("[DEBUG][%s:%s:%d] aquire read lock with %d readers\n", __FILE_NAME__,
         __func__, __LINE__, rw_lock->readers);
  if (rw_lock->readers == 1)
    sem_wait(rw_lock->rw);
  sem_post(rw_lock->mutex);
}

void read_unlock(RW_Lock *rw_lock) {
  sem_wait(rw_lock->mutex);
  rw_lock->readers--;
  if (rw_lock->readers == 0)
    sem_post(rw_lock->rw);

  printf("[DEBUG][%s:%s:%d] release read lock with %d readers\n", __FILE_NAME__,
         __func__, __LINE__, rw_lock->readers);

  sem_post(rw_lock->mutex);
}

Queue *init_queue() {
  Queue *q = calloc(1, sizeof(Queue));
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutex_init(&q->mutex, &attr);
  return q;
}

db_file_t *db_init(char *file) {
  RW_Lock *rw_lock = rw_lock_init(INT_MAX);

  db_file_t *db_file = calloc(1, sizeof(db_file_t));
  db_file->rw_lock = rw_lock;
  strcpy(db_file->db_file, file);

  FILE *fp = fopen(file, "w");
  if (fp == NULL) {
    printf("failed to create a file");
    exit(1);
  }
  fflush(fp);
  fclose(fp);

  printf("created file %s\n", file);

  Queue *q = init_queue();
  db_file->q = q;

  return db_file;
}

void *handle_request(void *arg) {
  msg_t *msg = (msg_t *)arg;
  printf("[DEBUG][%s:%s:%d] handling request id %d\n", __FILE_NAME__, __func__,
         __LINE__, msg->req_id);

  if (msg->is_write) {
    write_lock(db_file->rw_lock);

    FILE *fp = fopen(db_file->db_file, "w");
    printf("[DEBUG][%s:%s:%d] writing to file %s\n", __FILE_NAME__, __func__,
           __LINE__, msg->content);
    fputs(msg->content, fp);
    fflush(fp);
    fclose(fp);

    write_unlock(db_file->rw_lock);
  } else {
    read_lock(db_file->rw_lock);

    FILE *fp = fopen(db_file->db_file, "r");
    char read_content[1024];
    fgets(read_content, 1024, fp);
    fclose(fp);

    printf("[DEBUG][%s:%s:%d] read contents: %s\n", __FILE_NAME__, __func__,
           __LINE__, read_content);

    char resp_file_path[1024];
    sprintf(resp_file_path, "/tmp/read_%d", msg->req_id);
    int resp_file = open(resp_file_path, O_WRONLY);

    write(resp_file, read_content, 1024);
    close(resp_file);

    read_unlock(db_file->rw_lock);
  }

  return NULL;
}

int main(int argc, char **argv) {

  int fd;
  char *fifo_path = "/tmp/db_client_fifo";
  mkfifo(fifo_path, 0666);

  if (argc != 2) {
    printf("USAGE ./file <filename>\n");
    return 1;
  }

  db_file = db_init(argv[1]);

  int fifo_fd = open(fifo_path, O_RDONLY);
  if (fifo_fd < 0) {
    printf("failed to open fifo queue\n");
    exit(1);
  }

  while (1) {
    msg_t buffer;
    int bytes_read = read(fifo_fd, &buffer, sizeof(msg_t));
    if (bytes_read > 0) {
      pthread_t thread;
      pthread_attr_t attr;
      pthread_attr_init(&attr);

      pthread_create(&thread, NULL, handle_request, &buffer);
    }
  }
}
