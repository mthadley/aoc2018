#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "day1.h"
#include "day2.h"
#include "day.h"

#define MAX_DAYS 2

typedef struct Day (*DAY_FN)(void);

const DAY_FN days[MAX_DAYS] = {
  day1,
  day2
};

void print_part(const struct Answer* answer, int part);
void run_day(int day);

int main(int argc, char* argv[]) {
  int day_to_run = 0;
  char opt;

  while ((opt = getopt(argc, argv, "d:")) != -1) {
    switch (opt) {
      case 'd':
        day_to_run = atoi(optarg);
        break;
    }
  }

  if (day_to_run > 0) {
    if (day_to_run > MAX_DAYS) {
      fprintf(stderr, "Day number cannot be greater than %i\n", MAX_DAYS);
      exit(1);
    }

    run_day(day_to_run);
  } else {
    for (int i = 0; i < MAX_DAYS; i++) {
      run_day(i + 1);

      if (i != MAX_DAYS - 1) puts("");
    }
  }

  return 0;
}

void run_day(int day_n) {
  struct Day day = days[day_n - 1]();

  printf("Day %i\n", day_n);
  puts("================");
  print_part(&day.part1, 1);
  print_part(&day.part2, 2);
}

void print_part(const struct Answer* answer, int part) {
  char* sym;

  if (!answer->expected) {
    sym = "❓";
  } else {
    if (answer->expected == answer->actual) {
      sym = "✅";
    } else {
      sym = "❌";
    }
  }

  printf("Part %i: %zu %s\n", part, answer->actual, sym);
}
