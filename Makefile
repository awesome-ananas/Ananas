CC=clang
PROGRAM=ananas
MAIN=src/main.c
DIST=dist/$(PROGRAM)
CFLAGS=$(MAIN) --std=c11 -Wall -Werror -o $(DIST)

.PHONY: debug

default:
	$(CC) $(CFLAGS)

debug:
	$(CC) -g $(CFLAGS)
