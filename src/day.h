#pragma once

#include <stdlib.h>

struct Answer {
  char* expected;
  char* actual;
};

struct Day {
  struct Answer part1;
  struct Answer part2;
};
