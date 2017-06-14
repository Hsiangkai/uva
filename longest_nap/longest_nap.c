#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256
#define NUM_EVENT 120
#define START_TIME 600 /* 10:00 */
#define END_TIME 1080  /* 18:00 */

struct event {
  int start_min;
  int end_min;
};

static int input(struct event *events)
{
  int n;
  char buf[BUFSIZE];
  int i;
  int start_hour;
  int start_min;
  int end_hour;
  int end_min;
  char *ret;

  ret = fgets (buf, BUFSIZE, stdin);
  if (ret == NULL)
    return -1;
  if (buf[0] == '\n')
    return -1;
  n = atoi (buf);

  i = 0;
  while (i < n) {
    fgets (buf, BUFSIZE, stdin);
    sscanf (buf, "%d:%d %d:%d",
	&start_hour, &start_min, &end_hour, &end_min);
    events[i].start_min = start_hour * 60 + start_min;
    events[i].end_min = end_hour * 60 + end_min;
    i++;
  }

  return n;
}

static int cmp(const void *a, const void *b)
{
  struct event *val_a = (struct event *)a;
  struct event *val_b = (struct event *)b;

  if (val_a->start_min < val_b->start_min)
    return -1;
  else if (val_a->start_min > val_b->start_min)
    return 1;
  else
    return 0;
}

static void process(struct event *events, int n)
{
  int i;
  int max_nap;
  int max_hour;
  int max_min;
  int max_start_min;
  int max_start_hour;
  int max_end_min;
  int gap;
  int current_end;

  qsort (events, n, sizeof(struct event), cmp);
  events[n].start_min = END_TIME;
  events[n].end_min = END_TIME;

  max_nap = events[0].start_min - START_TIME;
  max_start_min = START_TIME;
  max_end_min = events[0].start_min;

  current_end = events[0].end_min;
  for (i = 1; i <= n; i++) {
    if (events[i].end_min < current_end)
      continue;

    if (events[i].start_min < current_end) {
      current_end = events[i].end_min;
    } else {
      gap = events[i].start_min - current_end;
      if (gap > max_nap) {
        max_nap = gap;
        max_start_min = current_end;
        max_end_min = events[i].start_min;
      }
      current_end = events[i].end_min;
    }
  }
  max_start_hour = max_start_min / 60;
  max_start_min = max_start_min % 60;
  max_hour = max_nap / 60;
  max_min = max_nap % 60;

  printf ("the longest nap starts at %02d:%02d and will last for ",
      max_start_hour, max_start_min);
  if (max_hour != 0)
    printf ("%d hours and ", max_hour);
  printf ("%d minutes.\n", max_min);
}

int main()
{
  int n;
  int i;
  struct event events[NUM_EVENT];

  i = 1;
  while (1) {
    n = input(events);
    if (n == -1)
      break;
    printf ("Day #%d: ", i);
    process(events, n);
    i++;
  }

  return 0;
}
