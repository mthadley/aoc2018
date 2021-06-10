#include <stdbool.h>
#include <glib.h>
#include <stdio.h>
#include <string.h>

#include "day.h"
#include "day2.h"
#include "../input/day2.h"

struct CountState {
  bool counted_two;
  bool counted_three;
};

static char* part1(char** lines);
static char* part2(char** lines);

struct Day day2() {
  char** lines = g_strsplit((gchar*)input_day2_txt, "\n", 0);

  struct Day day = {
    .part1 = { .actual = part1(lines), .expected = "5166" },
    .part2 = { .actual = part2(lines), .expected = "cypueihajytordkgzxfqplbwn" }
  };

  free(lines);

  return day;
}

static void count_occurrences(gpointer key_p __attribute__((unused)),
                              gpointer count_p,
                              gpointer cs_p) {
  unsigned int* count = count_p;
  struct CountState* cs = cs_p;

  if (*count == 2 && !cs->counted_two) cs->counted_two = true;
  if (*count == 3 && !cs->counted_three) cs->counted_three = true;
}

static char* part1(char** lines) {
  unsigned int with_two = 0;
  unsigned int with_three = 0;

  char* line;
  for (int line_n = 0; (line = lines[line_n]); line_n++) {
    GHashTable* seen = g_hash_table_new_full(g_int_hash,
                                             g_int_equal,
                                             NULL,
                                             g_free);

    int c;
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

    g_hash_table_destroy(seen);
  }

  return g_strdup_printf("%i", with_two * with_three);
}

static char* part2(char** lines) {
  char* line;
  for (int line_n = 0; (line = lines[line_n]); line_n++) {
    char* other_line;
    for (int oline_n = line_n + 1; (other_line = lines[oline_n]); oline_n++) {
      int c_n = 0;
      int diff_index = 0;
      int diff_count = 0;

      while (true) {
        int c = line[c_n];
        int other_c = other_line[c_n];

        if (!c) break;

        if (c != other_c) {
          diff_count++;
          diff_index = c_n;
        }

        c_n++;
      }

      if (diff_count == 1) {
        int len = strlen(line);
        char* id_str = malloc((len - 1) * sizeof(char));

        memcpy(id_str, line, diff_index);
        strncat(id_str, &line[diff_index + 1], 100);

        return id_str;
      }
    }
  }

  return "";
}
