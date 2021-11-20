# Makefile
CC := gcc
INCLUDE := -I ./include
WININCLUDE := -IC:\SDL2_x64\include
WINLINKER := -LC:\SDL2_x64\lib
SRC := ./src
CFLAGSO := -Wall -c ${INCLUDE}
WINCFLAGSO := -Wall -m64 -c ${INCLUDE} ${WININCLUDE}
CFLAGSB := -s -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
WINCFLAGSB := -s -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

ifeq ($(OS), Windows_NT)
	CFLAGSO = ${WINCFLAGSO}
	CFLAGSB = ${WINLINKER} ${WINCFLAGSB} -mwindows
	# -mwindows flag removes the cmd when executing binary
endif

all: main

main: Event.o Init.o Food.o main.o Render.o Snake.o Sound.o
	${CC} $^ -o $@ ${CFLAGSB}

%.o: ${SRC}/%.c
	${CC} ${CFLAGSO} $^

clean:
	rm -rf *.o main
