#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <glib.h>

#include "day.h"
#include "day1.h"
#include "../input/day1.h"

static size_t part1();
static size_t part2();

struct Day day1() {
  return (struct Day){
    .part1 = { .actual = part1(), .expected = 400 },
    .part2 = { .actual = part2(), .expected = 232 }
  };
}

static size_t part1() {
  size_t total = 0;

  char** lines = g_strsplit((gchar*)input_day1_txt, "\n", 0);
  char* line;

  for (int line_n = 0; (line = lines[line_n]); line_n++) {
    if (line[0] == '\0') continue;

    total += atoi(line);
  }

  return total;
}

static size_t part2() {
  GHashTable* seen = g_hash_table_new(g_int_hash, g_int_equal);
  char** lines = g_strsplit((gchar*)input_day1_txt, "\n", 0);
  size_t total = 0;

  while (true) {
    char* line;

    for (int line_n = 0; (line = lines[line_n]); line_n++) {
      if (line[0] == '\0') continue;

      total += atoi(line);

      if (g_hash_table_lookup_extended(seen, &total, NULL, NULL)) {
        return total;
      } else {
        g_hash_table_insert(seen, &total, NULL);
      }
    }
  }

  return 0;
}
