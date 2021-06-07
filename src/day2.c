#include <stdbool.h>
#include <glib.h>
#include <stdio.h>

#include "day.h"
#include "day2.h"
#include "../input/day2.h"

struct CountState {
  bool counted_two;
  bool counted_three;
};

static void count_occurrences(gpointer key_p __attribute__((unused)),
                              gpointer count_p,
                              gpointer cs_p) {
  unsigned int* count = count_p;
  struct CountState* cs = cs_p;

  if (*count == 2 && !cs->counted_two) cs->counted_two = true;
  if (*count == 3 && !cs->counted_three) cs->counted_three = true;
}

struct Day day2() {
  struct Day day = {
    .part1 = { .expected = 5166 }
  };

  unsigned int with_two = 0;
  unsigned int with_three = 0;

  char** lines = g_strsplit((gchar*)input_day2_txt, "\n", 0);

  char* line;
  for (int line_n = 0; (line = lines[line_n]); line_n++) {
    GHashTable* seen = g_hash_table_new(g_int_hash, g_int_equal);

    char c;
    for (int char_n = 0; (c = line[char_n]); char_n++) {
      int* current_count = g_hash_table_lookup(seen, &c);

      if (current_count == NULL) {
        unsigned int* count_p = malloc(sizeof(int));
        *count_p = 1;

        g_hash_table_insert(seen, &c, count_p);
      } else {
        (*current_count)++;
      };
    }

    struct CountState cs = { .counted_two = false, .counted_three = false };
    g_hash_table_foreach(seen, count_occurrences, &cs);

    if (cs.counted_two) with_two++;
    if (cs.counted_three) with_three++;
  }

  day.part1.actual = with_two * with_three;

  return day;
}
