#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <glib.h>

#include "day.h"
#include "day1.h"
#include "../input/day1.h"

struct Day day1() {
  struct Day day = {
    .part1 = { .expected = 400 },
    .part2 = { .expected = 232 }
  };

  size_t total = 0;
  bool first_pass = true;

  GHashTable* seen = g_hash_table_new(g_int_hash, g_int_equal);
  char** lines = g_strsplit((gchar*)input_day1_txt, "\n", 0);

  while (true) {
    char* line;

    for (int line_n = 0; (line = lines[line_n]); line_n++) {
      if (line[0] == '\0') continue;

      total += atoi(line);

      if (g_hash_table_lookup_extended(seen, &total, NULL, NULL)) {
        day.part2.actual = total;

        return day;
      } else {
        g_hash_table_insert(seen, &total, NULL);
      }
    }

    if (first_pass) {
      day.part1.actual = total;
      first_pass = false;
    }
  }
}
