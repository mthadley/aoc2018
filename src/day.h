#pragma once

#include <stdlib.h>

struct Answer {
  size_t expected;
  size_t actual;
};

struct Day {
  struct Answer part1;
  struct Answer part2;
};
