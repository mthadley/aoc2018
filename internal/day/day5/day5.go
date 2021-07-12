package day5

import (
	"fmt"
	"strings"
	"unicode"

	"github.com/mthadley/aoc2018/internal/day"
	"github.com/mthadley/aoc2018/internal/input"
)

func Day() day.Day {
	line := input.Read("day5.txt")
	line = strings.TrimSpace(line)

	return day.Day{
		Part1: day.Part{Actual: part1(line), Expected: "11668"},
	}
}

func part1(line string) string {
	return fmt.Sprint(len(react(line)))
}

func react(line string) string {
	for i, r := range line {
		if i+1 >= len(line) {
			continue
		}

		otherR := line[i+1]
		if reactsWith(r, rune(otherR)) {
			return react(line[:i] + line[i+2:])
		}
	}

	return line
}

func reactsWith(r, otherR rune) bool {
	return unicode.ToLower(r) == unicode.ToLower(otherR) &&
		((unicode.IsLower(r) && unicode.IsUpper(otherR)) ||
			(unicode.IsUpper(r) && unicode.IsLower(otherR)))
}
