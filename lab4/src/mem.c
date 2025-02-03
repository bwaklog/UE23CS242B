#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Point {
  int x;
  int y;
} Point;

const int MAX_POINTS = 10;
int n;

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Invalid usage\n");
    return EXIT_FAILURE;
  }

  int i;

  n = atoi(argv[1]);
  if (n > MAX_POINTS) {
    exit(1);
  }

  Point *space = calloc(n, sizeof(Point));

  for (i = 0; i < n; i++) {
    Point temp;
    printf("> ");
    scanf("%d %d", &temp.x, &temp.y);
    space[i] = temp;
  }

  printf("[ ");
  for (i = 0; i < n; i++) {
    printf("(%d, %d) ", space[i].x, space[i].y);
  }
  printf(" ]\n");

  printf("PID = %d\n", getpid());

  return EXIT_SUCCESS;
}
