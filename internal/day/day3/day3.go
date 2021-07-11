package day3

import (
	"errors"
	"fmt"
	"log"
	"regexp"
	"strconv"

	"github.com/mthadley/aoc2018/internal/day"
	"github.com/mthadley/aoc2018/internal/input"
	"github.com/mthadley/aoc2018/internal/point"
)

func Day() day.Day {
	lines := input.Readlines("day3.txt")
	claims := make([]claim, len(lines))

	for i, line := range lines {
		claim, err := parseClaim(line)
		if err != nil {
			log.Fatal(err)
		}

		claims[i] = claim
	}

	points := claimPoints(claims)
	fmt.Println(len(points))

	return day.Day{
		Part1: day.Part{Actual: part1(points), Expected: "111485"},
		Part2: day.Part{Actual: part2(points, claims), Expected: "113"},
	}
}

func part1(points map[point.Point]int) string {
	total := 0

	for _, count := range points {
		if count > 1 {
			total++
		}
	}

	return fmt.Sprint(total)
}

func part2(points map[point.Point]int, claims []claim) string {
	for _, claim := range claims {
		anyOverlapping := false

		for _, point := range claim.points() {
			if points[point] > 1 {
				anyOverlapping = true
				break
			}
		}

		if !anyOverlapping {
			return fmt.Sprint(claim.id)
		}
	}

	return ""
}

func claimPoints(claims []claim) map[point.Point]int {
	points := map[point.Point]int{}

	for _, claim := range claims {
		for _, point := range claim.points() {
			points[point]++
		}
	}

	return points
}

type claim struct {
	id     int
	loc    point.Point
	width  int
	height int
}

func (claim *claim) points() (points []point.Point) {
	points = make([]point.Point, 0)

	for x := 0; x < claim.width; x++ {
		for y := 0; y < claim.height; y++ {
			offset := point.New(x, y)
			points = append(points, claim.loc.Add(offset))
		}
	}

	return
}

var claimRegex *regexp.Regexp

func parseClaim(line string) (claim, error) {
	if claimRegex == nil {
		claimRegex = regexp.MustCompile("^#(?P<id>\\d+)\\s+@\\s+(?P<x>\\d+),(?P<y>\\d+):\\s+(?P<width>\\d+)x(?P<height>\\d+)$")
	}

	matches := claimRegex.FindStringSubmatch(line)
	if matches == nil {
		return claim{}, errors.New("Failed to match claim with line: " + line)
	}

	return claim{
		id: mustBeInt(matches[claimRegex.SubexpIndex("id")]),
		loc: point.New(
			mustBeInt(matches[claimRegex.SubexpIndex("x")]),
			mustBeInt(matches[claimRegex.SubexpIndex("y")]),
		),
		width:  mustBeInt(matches[claimRegex.SubexpIndex("width")]),
		height: mustBeInt(matches[claimRegex.SubexpIndex("height")]),
	}, nil
}

func mustBeInt(str string) int {
	num, err := strconv.ParseInt(str, 0, 64)
	if err != nil {
		log.Fatal(err)
	}

	return int(num)
}
