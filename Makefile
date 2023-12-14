NAME=nbody01
CC=g++
CFLAGS=$(shell pkg-config --cflags raylib)
LDFLAGS=$(shell pkg-config --libs raylib) -lm
OBJECTS=nbody01.o body.o world.o

$(NAME): $(OBJECTS)

