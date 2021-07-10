package main

import (
	"fmt"

	"github.com/mthadley/aoc2018/internal/day"
	"github.com/mthadley/aoc2018/internal/day/day1"
	"github.com/mthadley/aoc2018/internal/day/day2"
)

type dayFn = func() day.Day

var allDays = [...]dayFn{
	day1.Day,
	day2.Day,
}

func main() {
	for i, day := range allDays {
		printDay(i+1, day())
		fmt.Println()
	}
}

func printDay(num int, day day.Day) {
	fmt.Printf("Day %d\n", num)
	fmt.Println("===============================")
	printPart(1, day.Part1)
	printPart(2, day.Part2)
}

func printPart(num int, part day.Part) {
	var status string
	switch part.Passed() {
	case day.Unknown:
		status = "❔"
	case day.Passed:
		status = "✅"
	case day.Failed:
		status = "❌"
	}

	fmt.Printf("Part %d: %s %s\n", num, part.Actual, status)
}
