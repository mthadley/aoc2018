package day2

import (
	"fmt"

	"github.com/mthadley/aoc2018/internal/day"
	"github.com/mthadley/aoc2018/internal/input"
)

func Day() day.Day {
	lines := input.Readlines("day2.txt")

	return day.Day{
		Part1: day.Part{Actual: part1(lines), Expected: "5166"},
		Part2: day.Part{Actual: part2(lines), Expected: "cypueihajytordkgzxfqplbwn"},
	}
}

func part1(lines []string) string {
	two := 0
	three := 0

	for _, line := range lines {
		addedTwo := false
		addedThree := false

		for _, v := range counts(line) {
			if v == 2 && !addedTwo {
				two++
				addedTwo = true
			}

			if v == 3 && !addedThree {
				three++
				addedThree = true
			}
		}
	}

	return fmt.Sprint(two * three)
}

func part2(lines []string) string {
	for i, line := range lines {
		for _, otherLine := range lines[i+1:] {
			diffCount, diffAt := diff(line, otherLine)

			if diffCount == 1 {
				return line[0:diffAt] + line[diffAt+1:]
			}
		}
	}

	return ""
}

func diff(line string, other string) (int, int) {
	diffAt := 0
	diffCount := 0

	for i, r := range line {
		if byte(r) != other[i] {
			diffCount++
			diffAt = i
		}
	}

	return diffCount, diffAt
}

func counts(line string) map[rune]int {
	runes := map[rune]int{}

	for _, r := range line {
		runes[r]++
	}

	return runes
}
