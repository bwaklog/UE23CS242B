#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *mythread(void *arg) {
  printf("%s\n", (char *)arg);
  return NULL;
}

int main() {
  pthread_t p1, p2;
  int rc;
  pthread_create(&p1, NULL, mythread, "A");
  pthread_create(&p2, NULL, mythread, "B");

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  return 0;
}
