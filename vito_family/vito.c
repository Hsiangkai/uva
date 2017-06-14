#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 3000

struct relatives
{
  int n;
  int *streets;
};

static void input_one_case(struct relatives *input)
{
  char buf[BUFSIZE];
  char *data;
  int i;

  fgets(buf, BUFSIZE, stdin);

  data = strtok(buf, " ");
  input->n = atoi(data);
  input->streets = malloc(sizeof(int) * input->n);

  i = 0;
  while (1) {
    data = strtok(NULL, " ");
    if (data == NULL)
      break;
    input->streets[i] = atoi(data);
    i++;
  }
}

int cmp(const void *a, const void *b)
{
  int *val_a = (int *)a;
  int *val_b = (int *)b;

  if (*val_a > *val_b)
    return 1;
  else if (*val_a < *val_b)
    return -1;
  else
    return 0;
}

static void process(struct relatives *input)
{
  int x;
  int i;
  int dist;
  int sum;

  qsort(input->streets, input->n, sizeof(int), cmp);

  if (input->n % 2)
    x = input->streets[input->n/2];
  else
    x = (input->streets[input->n/2] + input->streets[input->n/2 -1]) / 2;

  for (i = 0, sum = 0; i < input->n; i++) {
    if (x >= input->streets[i])
      dist = x - input->streets[i];
    else
      dist = input->streets[i] - x;
    sum += dist;
  }
  printf ("%d\n", sum);
}

int main()
{
  struct relatives input;
  char buf[BUFSIZE];
  int cases;
  
  fgets(buf, BUFSIZE, stdin);

  cases = atoi(buf);

  while (cases) {
    input_one_case(&input);
    process(&input);
    free(input.streets);

    cases--;
  }

  return 0;
}
