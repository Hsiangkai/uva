#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 32
#define NUM_ORDER 1001

struct order
{
  int index;
  int time;
  int penalty;
};

static int input(struct order *orders)
{
  char buf[BUFSIZE];
  int n;
  char *ret;
  char *token;
  int time;
  int penalty;
  int i;

  fgets (buf, BUFSIZE, stdin);
  n = atoi (buf);

  i = 0;
  while (1) {
    ret = fgets (buf, BUFSIZE, stdin);
    if (ret == NULL)
      break;
    if (ret[0] == '\n')
      break;

    token = strtok (buf, " ");
    time = atoi (token);
    token = strtok (NULL, " ");
    penalty = atoi (token);
    orders[i].index = i + 1;
    orders[i].time = time;
    orders[i].penalty = penalty;

    i++;
  }

  return n;
}

static int cmp(const void *a, const void *b)
{
  struct order *val_a = (struct order *)a;
  struct order *val_b = (struct order *)b;

  int indicator_a = val_a->time * val_b->penalty;
  int indicator_b = val_b->time * val_a->penalty;
  if (indicator_a > indicator_b)
    return 1;
  else if (indicator_a < indicator_b)
    return -1;
  else
    return 0;
}

static void process(struct order *orders, const int n)
{
  int i;
  
  qsort (orders, n, sizeof(struct order), cmp);

  for (i = 0; i < n; i++) {
    printf ("%d", orders[i].index);
    if (i < n - 1)
      printf (" ");
  }
  printf ("\n");
}

int main()
{
  struct order orders[NUM_ORDER];
  int n;
  int cases;
  char buf[BUFSIZE];

  fgets (buf, BUFSIZE, stdin);
  cases = atoi (buf);
  fgets (buf, BUFSIZE, stdin);

  while (cases) {
    n = input(orders);

    process (orders, n);

    cases--;
    if (cases)
      printf ("\n");
  }

  return 0;
}
