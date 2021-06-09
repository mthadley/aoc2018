#include <glib.h>
#include <stdio.h>

#include "day.h"
#include "day3.h"
#include "../input/day3.h"
#include "point.h"

struct Claim {
  unsigned int id;
  int x;
  int y;
  unsigned int width;
  unsigned int height;
};

struct Claim claim_from_s(char*);
void claim_add_points(struct Claim*, GHashTable*);

struct Day day3() {
  struct Day day = {
    .part1 = { .expected = "111485" }
  };

  char** lines = g_strsplit((gchar*)input_day3_txt, "\n", 0);
  GHashTable* grid = g_hash_table_new_full(point_hash_hash,
                                           point_hash_equal,
                                           NULL,
                                           g_free);

  char* line;
  for (int line_n = 0; (line = lines[line_n]); line_n++) {
    if (line[0] == '\0') continue;

    struct Claim claim = claim_from_s(line);
    claim_add_points(&claim, grid);
  }

  GHashTableIter iter;
  gpointer h_value;
  int total_overlapping = 0;

  g_hash_table_iter_init(&iter, grid);
  while(g_hash_table_iter_next(&iter, NULL, &h_value)) {
    int num_overlapping_claims = *(int*)h_value;

    if (num_overlapping_claims > 1) total_overlapping++;
  }

  day.part1.actual = g_strdup_printf("%i", total_overlapping);

  free(lines);
  g_hash_table_destroy(grid);

  return day;
}

#define CLAIM_REGEX "^#(?<id>\\d+)\\s+@\\s+(?<x>\\d+),(?<y>\\d+):\\s+(?<width>\\d+)x(?<height>\\d+)$"

GRegex* claim_regex;

int fetch_named_int(GMatchInfo* match_info, char* name) {
  return atoi(g_match_info_fetch_named(match_info, name));
}

struct Claim claim_from_s(char* s) {
  if (!claim_regex) {
    claim_regex = g_regex_new(CLAIM_REGEX, 0, 0, NULL);

    if (!claim_regex) {
      fputs("Failed to compile Claim regex.", stderr);
      exit(EXIT_FAILURE);
    }
  }

  GMatchInfo* match_info;

  if (!g_regex_match(claim_regex, s, 0, &match_info)) {
    fprintf(stderr, "Line did not match claim regex: %s\n", s);
    exit(EXIT_FAILURE);
  }

  struct Claim claim = {
    .id = fetch_named_int(match_info, "id"),
    .x = fetch_named_int(match_info, "x"),
    .y = fetch_named_int(match_info, "y"),
    .width = fetch_named_int(match_info, "width"),
    .height = fetch_named_int(match_info, "height"),
  };

  free(match_info);

  return claim;
}

void claim_add_points(struct Claim* claim, GHashTable* points) {
  for (unsigned int x = claim->x; x < (claim->x + claim->width); x++) {
    for (unsigned int y = claim->y; y < (claim->y + claim->height); y++) {
      struct Point point = point_new(x, y);

      int* current_count = g_hash_table_lookup(points, &point);

      if (current_count) {
        (*current_count)++;
      } else {
        unsigned int* count = malloc(sizeof(unsigned int));
        *count = 1;

        g_hash_table_insert(points, &point, count);
      }
    }
  }
}
