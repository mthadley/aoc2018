#include <stdio.h>

#include "day1.h"
#include "day.h"

void print_part(const struct Answer* answer, int part);

int main() {
  struct Day day = day1();

  puts("Answer for Day 1");
  puts("================");
  print_part(&day.part1, 1);
  print_part(&day.part2, 2);

  return 0;
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
