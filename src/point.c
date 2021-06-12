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

#define POINT_HASH_MAX 50

unsigned int point_hash(struct Point* point) {
  char point_hash_buf[POINT_HASH_MAX];

  int size = snprintf(point_hash_buf,
                      POINT_HASH_MAX,
                      "%i,%i",
                      point->x,
                      point->y);

  if (size >= POINT_HASH_MAX) {
    fprintf(stderr,
            "Hit max point hash size with (%i, %i)",
            point->x,
            point->y);
    exit(EXIT_FAILURE);
  }

  return g_str_hash(point_hash_buf);
}

guint point_hash_hash(gconstpointer point) {
  return point_hash((struct Point*) point);
}
