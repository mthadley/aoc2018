package day4

import (
	"errors"
	"fmt"
	"log"
	"regexp"
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

	fmt.Println(len(logEntries))

	return day.Day{}
}

type logEntry struct {
	ts    time.Time
	id    int
	event Event
}

type Event int

const (
	startedShift = iota
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
