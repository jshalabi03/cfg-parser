INCLUDES=-I includes/ -I src/ -I tests/

CXXFLAGS=-std=c++20 $(INCLUDES)

ERRORFLAGS=-Wall -Wextra -Werror -pedantic

CXX=clang++

COMPILE=$(CXX) $(CXXFLAGS)

main: bin/main.out
	$<

test: bin/test.out
	$<

clean:
	rm -f bin/*

bin/main.out: src/*.cpp
	$(COMPILE) $^ -o $@

bin/test.out: tests/*.cpp
	$(COMPILE) $^ -o $@

gen: data/index.cpp
	$(CXX) -S -mllvm --x86-asm-syntax=intel $< -o data/index.s

.DEFAULT_GOAL := main
.PHONY: main test clean