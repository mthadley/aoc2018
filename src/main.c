#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day.h"

#define MAX_DAYS 4

typedef struct Day (*DAY_FN)(void);

static const DAY_FN days[MAX_DAYS] = {
  day1,
  day2,
  day3,
  day4
};

void print_part(const struct Answer* answer, int part);
void run_day(int day);

int main(int argc, char* argv[]) {
  int day_to_run = 0;
  char opt;

  while ((opt = getopt(argc, argv, "d:")) != (char)-1) {
    switch (opt) {
      case 'd':
        day_to_run = atoi(optarg);
        break;
      default:
        fprintf(stderr, "Unrecognized option: %c", opt);
        exit(EXIT_FAILURE);
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
  puts("=====================");
  print_part(&day.part1, 1);
  print_part(&day.part2, 2);
}

void print_part(const struct Answer* answer, int part) {
  char* sym;

  if (!answer->expected) {
    sym = "❓";
  } else {
    if (strcmp(answer->expected, answer->actual) == 0) {
      sym = "✅";
    } else {
      sym = "❌";
    }
  }

  char* result = answer->actual;
  if (result == NULL) result = "";

  printf("Part %i: %s %s\n", part, result, sym);
}
