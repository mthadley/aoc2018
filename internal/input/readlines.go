package input

import (
	"bufio"
	"log"
	"os"
)

func Readlines(filename string) (lines []string) {
	file, err := os.Open("input/" + filename)
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}

	return
}
