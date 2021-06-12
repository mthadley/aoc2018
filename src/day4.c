#include <stdio.h>
#include <glib.h>

#include "day.h"
#include "day4.h"
#include "../input/day4.h"

struct Timestamp {
  unsigned int hour;
  unsigned int minute;
};

enum Event {
  StartedShift,
  FellAsleep,
  WokeUp
};

struct LogEntry {
  struct Timestamp ts;
  unsigned int id;
  enum Event event;
};

static struct LogEntry log_entry_from_s(char*, unsigned int);

#define TS_REGEX "\\[\\d+-\\d+-\\d+\\s(?<hour>\\d+):(?<minute>\\d+)\\]"
#define EVENT_REGEX "(?<asleep>falls asleep)|(?<wakes>wakes up)|(?<begin>Guard #(?<id>\\d+) begins shift)"

static GRegex* ts_regex;
static GRegex* event_regex;


struct Day day4() {
  struct Day day = {};

  char** lines = g_strsplit((gchar*)input_day4_txt, "\n", 0);
  char* line;
  unsigned int previous_id = 0;
  for (int line_n = 0; (line = lines[line_n]); line_n++) {
    if (line[0] == '\0') continue;

    struct LogEntry entry = log_entry_from_s(line, previous_id);
    previous_id = entry.id;
    printf("Entry #%u, event %u\n", entry.id, entry.event);
  }

  free(ts_regex);
  free(event_regex);

  return day;
}

static GRegex* compile_regex_or_die(char* source) {
  GError* error = NULL;
  GRegex* regex = g_regex_new(source, 0, 0, &error);

  if (!regex) {
    fprintf(stderr, "Failed to compile regex: %s", error->message);
    exit(EXIT_FAILURE);
  }

  return regex;
}

static int fetch_named_int(GMatchInfo* match_info, char* name) {
  return atoi(g_match_info_fetch_named(match_info, name));
}

static struct LogEntry log_entry_from_s(char* s, unsigned int previous_id) {
  if (!ts_regex) ts_regex = compile_regex_or_die(TS_REGEX);
  if (!event_regex) event_regex = compile_regex_or_die(EVENT_REGEX);


  GMatchInfo* match_info;

  if (!g_regex_match(ts_regex, s, 0, &match_info)) {
    fprintf(stderr, "Line did not match ts regex: %s\n", s);
    exit(EXIT_FAILURE);
  }

  struct Timestamp ts = {
    .hour = fetch_named_int(match_info, "hour"),
    .minute = fetch_named_int(match_info, "minute")
  };

  free(match_info);
  if (!g_regex_match(event_regex, s, 0, &match_info)) {
    fprintf(stderr, "Line did not match ts regex: %s\n", s);
    exit(EXIT_FAILURE);
  }

  struct LogEntry entry = {
    .ts = ts,
  };

  if (*g_match_info_fetch_named(match_info, "asleep")) {
    entry.event = FellAsleep;
    entry.id = previous_id;
  } else if (*g_match_info_fetch_named(match_info, "wakes")) {
    entry.event = WokeUp;
    entry.id = previous_id;
  } else if (*g_match_info_fetch_named(match_info, "begin")) {
    entry.event = StartedShift;
    entry.id = fetch_named_int(match_info, "id");
  } else {
    fprintf(stderr, "Unregcognized event: %s\n", s);
    exit(EXIT_FAILURE);
  }

  free(match_info);

  return entry;
}
