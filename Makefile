SRC = $(shell find src -iname "*.c")
INPUTS = $(shell find input -iname "*.txt")

aoc: $(SRC) $(INPUTS:.txt=.h)
	gcc -o $@ $^ -Wall -Werror

input/%.h: input/%.txt
	xxd -i $< $@

.PHONY: clean
clean:
	rm -fr aoc

.PHONY: watch
watch:
	find src input | SHELL=bash entr -cs "make && ./aoc"
