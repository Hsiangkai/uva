#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 3000
#define NUM_PANCAKE 31

static int input(int *pancakes)
{
  char buf[BUFSIZE];
  char *elem;
  int i;

  if (fgets(buf, BUFSIZE, stdin) == NULL)
    return 0;

  elem = strtok(buf, " ");
  pancakes[1] = atoi(elem);
  i = 2;
  while (1) {
    elem = strtok(NULL, " ");
    if (elem == NULL)
      break;

    pancakes[i] = atoi(elem);
    i++;
  }

  return i - 1;
}

static void reverse(int *pancakes, int start, int end)
{
  int buffer[NUM_PANCAKE];
  int i, k;

  for (i = end, k = 0; i >= start; i--, k++) {
    buffer[k] = pancakes[i];
  }

  for (i = start,k = 0; i <= end; i++, k++) {
    pancakes[i] = buffer[k];
  }
}

static void process(int *pancakes, int n)
{
  int i, j;
  int max;
  int sort;

  for (i = 1; i <= n - 1; i++) {
    printf ("%d ", pancakes[i]);
  }
  printf ("%d\n", pancakes[n]);

  reverse(pancakes, 1, n);

  for (i = n, sort = 1; i >= 1; i--, sort++) {
    max = n;
    for (j = n-1; j >= sort; j--) {
      if (pancakes[j] >= pancakes[max])
	max = j;
    }

    if (max == sort)
      continue;
    else if (max == n) {
      reverse(pancakes, sort, n);
      printf ("%d ", sort);
    } else {
      reverse(pancakes, max, n);
      printf ("%d ", max);
      reverse(pancakes, sort, n);
      printf ("%d ", sort);
    }
  }
  printf ("0\n");
}

int main()
{
  int pancakes[NUM_PANCAKE];
  int num;

  while ((num = input(pancakes))) {
    process(pancakes, num);
  }

  return 0;
}
