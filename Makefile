CC=clang
PROGRAM=ananas
MAIN=src/main.c
DIST=dist/$(PROGRAM)
INCLUDE=-Isrc/include
CFLAGS=$(MAIN) $(INCLUDE) -O3 --std=c11 -Wall -Werror -o $(DIST)

.PHONY: debug run clean

default:
	$(CC) $(CFLAGS)

debug:
	$(CC) -g $(CFLAGS)

run: default
	./$(DIST)
