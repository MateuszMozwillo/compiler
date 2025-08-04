SRC = $(wildcard src/*.c)

run: build
	./main

build:
	gcc $(SRC) -o main -lraylib -lopengl32 -lgdi32 -lwinmm