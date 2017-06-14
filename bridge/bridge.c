#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PEOPLE 1000
#define BUFSIZE 32
#define PATH_LEN 40000

static int input(int *data)
{
  char buf[BUFSIZE];
  char *ret;
  int i = 0;
  int n;

  fgets(buf, BUFSIZE, stdin);
  n = atoi(buf);

  while (1) {
    ret = fgets(buf, BUFSIZE, stdin);
    if ((buf[0] == '\n') || (ret == NULL))
      break;

    data[i++] = atoi(buf);
  }

  return n;
}

static int cmp(const void *a, const void *b)
{
  int val_a = *(int *)a;
  int val_b = *(int *)b;
  if (val_a > val_b)
    return 1;
  else if (val_a < val_b)
    return -1;
  else
    return 0;
}

static void process(int *data, int n)
{
  int cost;
  char path[PATH_LEN];
  char buf[BUFSIZE];
  int case1, case2;

  qsort (data, n, sizeof(int), cmp);

  cost = 0;
  path[0] = '\0';
  while (n > 4) {
    case1 = data[n-1] + data[0] + data[n-2] + data[0];
    case2 = data[1] + data[0] + data[n-1] + data[1];

    if (case1 >= case2) {
      sprintf (buf, "%d %d\n", data[0], data[1]);
      strcat (path, buf);
      sprintf (buf, "%d\n", data[0]);
      strcat (path, buf);
      sprintf (buf, "%d %d\n", data[n-2], data[n-1]);
      strcat (path, buf);
      sprintf (buf, "%d\n", data[1]);
      strcat (path, buf);
      cost += case2;
    } else {
      sprintf (buf, "%d %d\n", data[0], data[n-1]);
      strcat (path, buf);
      sprintf (buf, "%d\n", data[0]);
      strcat (path, buf);
      sprintf (buf, "%d %d\n", data[0], data[n-2]);
      strcat (path, buf);
      sprintf (buf, "%d\n", data[0]);
      strcat (path, buf);
      cost += case1;
    }
    n -= 2;
  }

  if (n == 1) {
    sprintf (buf, "%d\n", data[0]);
    strcat (path, buf);
    cost += data[0];
  } else if (n == 2) {
    sprintf (buf, "%d %d\n", data[0], data[1]);
    strcat (path, buf);
    cost += data[1];
  } else if (n == 3) {
    sprintf (buf, "%d %d\n", data[0], data[2]);
    strcat (path, buf);
    sprintf (buf, "%d\n", data[0]);
    strcat (path, buf);
    sprintf (buf, "%d %d\n", data[0], data[1]);
    strcat (path, buf);
    cost += (data[2] + data[0] + data[1]);
  } else if (n == 4) {
    case1 = data[3] + data[0] + data[2] + data[0] + data[1];
    case2 = data[1] + data[0] + data[3] + data[1] + data[1];
    if (case1 >= case2) {
      sprintf (buf, "%d %d\n", data[0], data[1]);
      strcat (path, buf);
      sprintf (buf, "%d\n", data[0]);
      strcat (path, buf);
      sprintf (buf, "%d %d\n", data[2], data[3]);
      strcat (path, buf);
      sprintf (buf, "%d\n", data[1]);
      strcat (path, buf);
      sprintf (buf, "%d %d\n", data[0], data[1]);
      strcat (path, buf);
      cost += case2;
    } else {
      sprintf (buf, "%d %d\n", data[0], data[3]);
      strcat (path, buf);
      sprintf (buf, "%d\n", data[0]);
      strcat (path, buf);
      sprintf (buf, "%d %d\n", data[0], data[2]);
      strcat (path, buf);
      sprintf (buf, "%d\n", data[0]);
      strcat (path, buf);
      sprintf (buf, "%d %d\n", data[0], data[1]);
      strcat (path, buf);
      cost += case1;
    }
  }

  printf ("%d\n", cost);
  printf ("%s", path);
}

int main()
{
  int cases;
  char buf[BUFSIZE];
  int data[NUM_PEOPLE];
  int n;

  fgets(buf, BUFSIZE, stdin);
  cases = atoi(buf);
  fgets(buf, BUFSIZE, stdin);
  
  while (cases) {
    n = input(data);
    process(data, n);

    cases--;
    if (cases)
      printf ("\n");
  }

  return 0;
}
