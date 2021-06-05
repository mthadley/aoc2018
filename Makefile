SRC = $(shell find src -iname "*.c")

aoc: $(SRC)
	gcc -o $@ $^ -Wall -Werror

.PHONY: clean
clean:
	rm -fr aoc

.PHONY: watch
watch:
	find src input | SHELL=bash entr -cs "make && ./aoc"
