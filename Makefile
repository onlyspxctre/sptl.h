.PHONY: all clean

CC := clang
CFLAGS := -Wall -Wextra -std=c11 -pedantic -g

LIBS := -lcmocka

build:
	$(CC) $(CFLAGS) -o sptl sptl.c $(LIBS)
