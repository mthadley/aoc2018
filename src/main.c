#include <stdio.h>

#include "day1.h"
#include "day.h"

#define MAX_DAYS 1

typedef struct Day (*DAY_FN)(void);

const DAY_FN days[MAX_DAYS] = {
  day1
};

void print_part(const struct Answer* answer, int part);
void run_day(int day);

int main() {
  for (int i = 0; i < MAX_DAYS; i++) {
    run_day(i);

    if (i + 1 < MAX_DAYS) puts("\n");
  }

  return 0;
}

void run_day(int day_n) {
  struct Day day = days[day_n]();

  printf("Day %i\n", day_n + 1);
  puts("================");
  print_part(&day.part1, 1);
  print_part(&day.part2, 2);
}

void print_part(const struct Answer* answer, int part) {
  printf("Part %i: %zu ", part, answer->actual);

  if (!answer->expected) {
    puts("❓");
  } else {
    if (answer->expected == answer->actual) {
      puts("✅");
    } else {
      puts("❌");
    }
  }
}
