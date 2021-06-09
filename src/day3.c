#include <glib.h>

#include "day.h"
#include "day3.h"
#include "../input/day3.h"

struct Day day3() {
  char** lines = g_strsplit((gchar*)input_day3_txt, "\n", 0);

  struct Day day = {};

  free(lines);

  return day;
}
