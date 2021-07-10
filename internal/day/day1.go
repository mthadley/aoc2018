package day

import (
	"fmt"
	"log"
	"strconv"

	"github.com/mthadley/aoc2018/internal/input"
)

func Day1() Day {
	lines := input.Readlines("day1.txt")

	return Day{
		Part1: Part{Actual: part1(lines), Expected: "400"},
		Part2: Part{Actual: part2(lines), Expected: "232"},
	}
}

func part1(lines []string) string {
	freq := 0

	for _, line := range lines {
		num, err := strconv.ParseInt(line, 0, 0)
		if err != nil {
			log.Fatal(err)
		}

		freq += int(num)
	}

	return fmt.Sprint(freq)
}

func part2(lines []string) string {
	seen := map[int]bool{}
	freq := 0

	for {
		for _, line := range lines {
			num, err := strconv.ParseInt(line, 0, 0)
			if err != nil {
				log.Fatal(err)
			}
			freq += int(num)

			if seen[freq] {
				return fmt.Sprint(freq)
			}

			seen[freq] = true
		}
	}
}
