CC=clang
PROGRAM=ananas
OBJECTS=main.o error.o parse.o util.o vector.o lexer.o
DIST=$(PROGRAM)
INCLUDE=-Isrc/include
CFLAGS=$(INCLUDE) -O3 --std=c11 -Wall
DEBUG_CFLAGS = $(CFLAGS) -g

.PHONY: debug run clean

default: $(OBJECTS)
	$(CC) -o $(PROGRAM) $(OBJECTS)
	rm ./*.o

main.o: src/main.c
	$(CC) $(CFLAGS) -c -o obj/$(@F) $^

error.o: src/error/error.c
	$(CC) $(CFLAGS) -c -o obj/$(@F) $^

parse.o: src/parse/parse.c
	$(CC) $(CFLAGS) -c -o obj/$(@F) $^

util.o: src/util/freeSelfPointer.c
	$(CC) $(CFLAGS) -c src/util/freeSelfPointer.c -o obj/util.o

vector.o: src/vector/vector.c
	$(CC) $(CFLAGS) -c -o obj/$(@F) $^

lexer.o: src/lexer/lexer.c
	$(CC) $(CFLAGS) -c -o obj/$(@F) $^

tokenlist.o: src/tokenlist/tokenlist.c
	$(CC) $(CFLAGS) -c -o obj/$(@F) $^

run: default
	./$(DIST)

clean:
	rm -rf ./obj/*
