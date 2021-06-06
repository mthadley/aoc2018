SRC = $(shell find src -iname "*.c")
INPUTS = $(shell find input -iname "*.txt")

aoc: $(SRC) $(INPUTS:.txt=.h)
	gcc -Wall -Werror -o $@ $^ $(shell pkg-config --cflags --libs glib-2.0)

input/%.h: input/%.txt
	xxd -i $< $@

.PHONY: clean
clean:
	rm -fr aoc

.PHONY: watch
watch:
	find src input | SHELL=bash entr -rcs "make && ./aoc"
