package input

import (
	"log"
	"strconv"
)

func MustBeInt(str string) int {
	num, err := strconv.ParseInt(str, 0, 64)
	if err != nil {
		log.Fatal(err)
	}

	return int(num)
}
