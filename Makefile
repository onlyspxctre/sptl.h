.PHONY: all clean

CC := clang
CFLAGS := -Wall -Wextra -std=c11 -pedantic -g

LIBS := -lcmocka

all: sptl

sptl: sptl.c sptl.h
	$(CC) $(CFLAGS) -o $@ sptl.c $(LIBS)
