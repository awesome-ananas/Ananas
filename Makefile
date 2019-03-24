CC=clang
PROGRAM=ananas
MAIN=src/main.c
DIST=dist/ananas
CFLAGS=$(MAIN) --std=c11 -Wall -Werror -o $(DIST)

default:
	$(CC) $(CFLAGS)

debug:
	$(CC) -g $(CFLAGS)
