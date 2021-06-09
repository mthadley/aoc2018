#pragma once

#include <stdbool.h>
#include <glib.h>

struct Point {
  int x;
  int y;
};

struct Point point_new(int, int);
bool point_equal(struct Point*, struct Point*);
gboolean point_hash_equal(gconstpointer, gconstpointer);
unsigned int point_hash(struct Point*);
guint point_hash_hash(gconstpointer);
