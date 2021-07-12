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
	i := 0
	prev := 0
	result := ""

	for i < len(line) {
		if i+1 >= len(line) {
			result += line[prev : i+1]
			break
		}

		r, otherR := rune(line[i]), rune(line[i+1])

		if reactsWith(r, otherR) {
			result += line[prev:i]
			i += 2
			prev = i
		} else {
			i++
		}
	}

	if len(result) < len(line) {
		return react(result)
	}

	return result
}

func reactsWith(r, otherR rune) bool {
	return unicode.ToLower(r) == unicode.ToLower(otherR) &&
		((unicode.IsLower(r) && unicode.IsUpper(otherR)) ||
			(unicode.IsUpper(r) && unicode.IsLower(otherR)))
}
