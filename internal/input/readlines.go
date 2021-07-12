package input

import (
	"bufio"
	"io/ioutil"
	"log"
	"os"
)

func Readlines(filename string) (lines []string) {
	file, err := os.Open(inputPath(filename))
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

func Read(filename string) string {
	content, err := ioutil.ReadFile(inputPath(filename))
	if err != nil {
		log.Fatal(err)
	}

	return string(content)
}

func inputPath(filename string) string {
	return "input/" + filename
}
