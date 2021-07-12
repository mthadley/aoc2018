package main

import (
	"fmt"
	"runtime"

	"github.com/mthadley/aoc2018/internal/day"
	"github.com/mthadley/aoc2018/internal/day/day1"
	"github.com/mthadley/aoc2018/internal/day/day2"
	"github.com/mthadley/aoc2018/internal/day/day3"
	"github.com/mthadley/aoc2018/internal/day/day4"
	"github.com/mthadley/aoc2018/internal/day/day5"
)

type dayFn = func() day.Day

var allDays = [...]dayFn{
	day1.Day,
	day2.Day,
	day3.Day,
	day4.Day,
	day5.Day,
}

type answer struct {
	dayNum int
	day    day.Day
}

func main() {
	runAllDays()
}

func runAllDays() {
	problems := make(chan int, len(allDays))
	answers := make(chan answer, len(allDays))

	startWorkers(problems, answers)
	for i, _ := range allDays {
		problems <- i
	}

	for i, day := range collectAnswers(answers) {
		printDay(i+1, day)
		fmt.Println()
	}
}

func startWorkers(problems <-chan int, answers chan<- answer) {
	for i := 0; i < runtime.NumCPU(); i++ {
		go func() {
			for dayNum := range problems {
				day := allDays[dayNum]()
				answers <- answer{dayNum: dayNum, day: day}
			}
		}()
	}
}

func collectAnswers(answers <-chan answer) (results []day.Day) {
	results = make([]day.Day, len(allDays))
	for range allDays {
		answer := <-answers
		results[answer.dayNum] = answer.day
	}

	return
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
