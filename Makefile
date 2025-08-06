SRC = $(wildcard src/*.c)

run: build
	./main

build:
	gcc $(SRC) -o main 