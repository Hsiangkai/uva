#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 100
#define NUM_TURTLE 300

struct turtle
{
  char name[BUFSIZE];
};

static int input(struct turtle *turtles, struct turtle *expected)
{
  char buf[BUFSIZE];
  int n;
  int i, j;

  fgets (buf, BUFSIZE, stdin);
  n = atoi (buf);

  i = 0;
  while (i < n) {
    fgets (turtles[i].name, BUFSIZE, stdin);
    i++;
  }

  i = 0;
  while (i < n) {
    fgets (expected[i].name, BUFSIZE, stdin);
    i++;
  }

  return n;
}

static void process (struct turtle *turtles, struct turtle *expected, const int n)
{
  int i, j, k;
  int different_set[NUM_TURTLE];
  int c, d;

  for (i = n - 1, j = n - 1, k = 0; j >= 0; i--) {
    if (strcmp(turtles[i].name, expected[j].name) == 0) {
      j--;
    } else {
      /* check expected[j] is in different set or not */
      for (c = 0; c < k; c++) {
	if (strcmp(expected[j].name, turtles[different_set[c]].name) == 0) {
	  /* find the first one must sort. */
	  for (d = j; d >= 0; d--) {
	    printf ("%s", expected[d].name);
	  }
	  return;
	}
      }
      different_set[k++] = i;
    }
  }
}

int main()
{
  int n;
  int cases;
  char buf[BUFSIZE];
  struct turtle turtles[NUM_TURTLE];
  struct turtle expected[NUM_TURTLE];

  fgets (buf, BUFSIZE, stdin);
  cases = atoi (buf);

  while (cases) {
    n = input(turtles, expected);
    process(turtles, expected, n);
    cases--;
    printf ("\n");
  }

  return 0;
}
