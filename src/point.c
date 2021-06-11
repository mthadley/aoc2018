#include <stdio.h>
#include <stdbool.h>
#include <glib.h>

#include "point.h"

bool point_equal(struct Point* a, struct Point* b) {
  return a->x == b->x && a->y == b->y;
}

gboolean point_hash_equal(gconstpointer a, gconstpointer b) {
  return point_equal((struct Point*)a, (struct Point*) b);
}

unsigned int point_hash(struct Point* point) {
  char str_p[3];
  str_p[0] = point->x;
  str_p[1] = ',';
  str_p[2] = point->y;

  return g_str_hash(str_p);
}

guint point_hash_hash(gconstpointer point) {
  return point_hash((struct Point*) point);
}
