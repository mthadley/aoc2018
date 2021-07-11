package day4

import (
	"errors"
	"fmt"
	"log"
	"regexp"
	"sort"
	"time"

	"github.com/mthadley/aoc2018/internal/day"
	"github.com/mthadley/aoc2018/internal/input"
)

func Day() day.Day {
	lines := input.Readlines("day4.txt")
	logEntries := make([]logEntry, len(lines))

	for i, line := range lines {
		logEntry, err := parseLogEntry(line)
		if err != nil {
			log.Fatal(err)
		}

		logEntries[i] = logEntry
	}

	summary := newMinutesSummary(logEntries)

	return day.Day{
		Part1: day.Part{Actual: part1(summary), Expected: "63509"},
		Part2: day.Part{Actual: part2(summary), Expected: "47910"},
	}
}

func part1(summary minutesSummary) string {
	var mostAsleepGuard int
	mostMinutes := 0

	for _, id := range summary.ids() {
		total := summary.minutesAsleep(id)

		if total > mostMinutes {
			mostAsleepGuard = id
			mostMinutes = total
		}
	}

	minute, _ := summary.mostSleptMinute(mostAsleepGuard)

	return fmt.Sprint(minute * mostAsleepGuard)
}

func part2(summary minutesSummary) string {
	var mostAsleepGuard, mostMinute int
	mostMinutes := 0

	for _, id := range summary.ids() {
		minute, total := summary.mostSleptMinute(id)

		if total > mostMinutes {
			mostMinute = minute
			mostAsleepGuard = id
			mostMinutes = total
		}
	}

	return fmt.Sprint(mostMinute * mostAsleepGuard)
}

type minutesSummary struct {
	minutes map[int]map[int]int
}

func newMinutesSummary(entries []logEntry) minutesSummary {
	sort.Slice(entries, func(i, j int) bool {
		return entries[i].ts.Before(entries[j].ts)
	})

	var currentId int
	var asleepAt time.Time
	minutesById := map[int]map[int]int{}

	for _, entry := range entries {
		switch entry.event {
		case startedShift:
			currentId = entry.id
		case fellAsleep:
			asleepAt = entry.ts
		case wokeup:
			for i := asleepAt.Minute(); i < entry.ts.Minute(); i++ {
				if minutesById[currentId] == nil {
					minutesById[currentId] = map[int]int{}
				}
				minutesById[currentId][i]++
			}
		}
	}

	return minutesSummary{minutes: minutesById}
}

func (summary *minutesSummary) forId(id int) map[int]int {
	return summary.minutes[id]
}

func (summary *minutesSummary) ids() (ids []int) {
	i := 0
	ids = make([]int, len(summary.minutes))

	for id := range summary.minutes {
		ids[i] = id
		i++
	}
	return
}

func (summary *minutesSummary) minutesAsleep(id int) int {
	total := 0

	for _, v := range summary.minutes[id] {
		total += v
	}

	return total
}

func (summary *minutesSummary) mostSleptMinute(id int) (int, int) {
	mostMinute := 0
	total := 0

	for minute, minuteTotal := range summary.minutes[id] {
		if minuteTotal > total {
			mostMinute = minute
			total = minuteTotal
		}
	}

	return mostMinute, total
}

type logEntry struct {
	ts    time.Time
	id    int
	event Event
}

type Event int

const (
	startedShift Event = iota
	fellAsleep
	wokeup
)

var logEntryRegex *regexp.Regexp
var tsRegex *regexp.Regexp

func parseLogEntry(line string) (logEntry, error) {
	if logEntryRegex == nil {
		logEntryRegex = regexp.MustCompile("(?P<asleep>falls asleep)|(?P<wakes>wakes up)|(?P<begin>Guard #(?P<id>\\d+) begins shift)")
	}
	if tsRegex == nil {
		tsRegex = regexp.MustCompile("\\[(?P<ts>.*)]")
	}

	entry := logEntry{}

	logEntryMatches := logEntryRegex.FindStringSubmatch(line)
	if logEntryMatches == nil {
		return logEntry{}, errors.New("Failed to match clain with line: " + line)
	}

	switch {
	case logEntryMatches[logEntryRegex.SubexpIndex("asleep")] != "":
		entry.event = fellAsleep
	case logEntryMatches[logEntryRegex.SubexpIndex("wakes")] != "":
		entry.event = wokeup
	case logEntryMatches[logEntryRegex.SubexpIndex("begin")] != "":
		entry.event = startedShift
		entry.id = input.MustBeInt(logEntryMatches[logEntryRegex.SubexpIndex("id")])
	default:
		return entry, errors.New("Unrecognized event.")
	}

	tsMatches := tsRegex.FindStringSubmatch(line)
	if tsMatches == nil {
		return logEntry{}, errors.New("Failed to match clain with line: " + line)
	}

	time, err := time.Parse("2006-01-2 15:04", tsMatches[tsRegex.SubexpIndex("ts")])
	if err != nil {
		return entry, err
	}

	entry.ts = time

	return entry, nil
}
