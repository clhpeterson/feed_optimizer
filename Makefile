CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -g3

SOURCES = optimizer.c

OBJECTS = $(SOURCES:.c=.o) ./getLine.o ./optimizer.o
TARGET = optimizer

$(TARGET): $(OBJECTS)
	${CC} ${CFLAGS} -o $@ $^

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

