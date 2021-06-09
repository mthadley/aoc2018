#include <glib.h>
#include <stdio.h>

#include "day.h"
#include "day3.h"
#include "../input/day3.h"

struct Claim {
  int x;
  int y;
  unsigned int width;
  unsigned int height;
};

struct Claim claim_from_s(char* s);

struct Day day3() {
  struct Day day = {};

  char** lines = g_strsplit((gchar*)input_day3_txt, "\n", 0);

  char* line;
  for (int line_n = 0; (line = lines[line_n]); line_n++) {
    if (line[0] == '\0') continue;

    struct Claim claim = claim_from_s(line);
  }


  free(lines);

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
    .x = fetch_named_int(match_info, "x"),
    .y = fetch_named_int(match_info, "y"),
    .width = fetch_named_int(match_info, "width"),
    .height = fetch_named_int(match_info, "height"),
  };

  free(match_info);

  return claim;
}
