SRC = $(wildcard src/*.c)

run: build
	./main

build:
	gcc -Wall $(SRC) -o main 