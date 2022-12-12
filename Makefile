INCLUDES=-I includes/ -I src/ -I tests/ -I catch2/

CXXFLAGS=-std=c++20 $(INCLUDES)

ERRORFLAGS=-Wall -Wextra -Werror -pedantic

CXX=clang++

COMPILE=$(CXX) $(CXXFLAGS)

# EXECUTABLE_SOURCE:=src/main.cpp
# TESTSUITE_SOURCE:=tests/test.cpp
# COMMON_SOURCES:=$(filter-out $(EXECUTABLE_SOURCE) $(TESTSUITE_SOURCE),src/*.cpp tests/*.cpp)

main: bin/main.out
	$<

test: bin/test.out
	

clean:
	rm -f bin/*

bin/main.out: src/*.cpp
	$(COMPILE) $^ -o $@

bin/test.out: $(filter-out src/main.cpp,$(wildcard src/*.cpp tests/*.cpp))
	$(COMPILE) $^ catch2/catch_amalgamated.cpp -o $@

gen: data/index.cpp
	$(CXX) -S -mllvm --x86-asm-syntax=intel $< -o data/index.s

.DEFAULT_GOAL := main
.PHONY: main test clean