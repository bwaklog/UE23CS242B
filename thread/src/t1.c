#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int g = 0;

void *mythreadfunc(void *varargs) {
  int *my_id = (int *)varargs;
  static int s = 0;
  int l = 0;

  ++l;
  ++s;
  ++g;

  printf("thread id %d | local %d | static %d | global %d\n", *my_id, l, s, g);
  pthread_exit(NULL);
}

int main() {
  int i;
  pthread_t tid;
  for (i = 0; i <= 3; i++) {
    pthread_create(&tid, NULL, mythreadfunc, (void *)&i);
    pthread_join(tid, NULL);
  }
  printf("in main\n");
  return 0;
}
