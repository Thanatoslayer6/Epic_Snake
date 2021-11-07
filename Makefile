# Makefile
CC := gcc
INCLUDE := ./include
SRC := ./src
CFLAGSO := -Wall -c -I ${INCLUDE}
CFLAGSB := -s -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: main

main: Event.o Init.o Food.o main.o Render.o Snake.o Sound.o 
	${CC} $^ -o $@ ${CFLAGSB}

%.o: ${SRC}/%.c
	${CC} ${CFLAGSO} $^

clean:
	rm -rf *.o main
