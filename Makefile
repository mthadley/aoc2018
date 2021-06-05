SRC = $(shell find src -iname "*.c")

aoc: $(SRC)
	gcc -o $@ $< -Wall -Werror

.PHONY: clean
clean:
	rm -fr aoc
