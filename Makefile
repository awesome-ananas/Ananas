CC=clang
PROGRAM=ananas
OBJECTS=main.o error.o parse.o util.o vector.o
DIST=$(PROGRAM)
INCLUDE=-Isrc/include
CFLAGS=$(INCLUDE) -O3 --std=c11 -Wall -Werror
DEBUG_CFLAGS = $(CFLAGS) -g

.PHONY: debug run clean

default: $(OBJECTS)
	$(CC) -o $(PROGRAM) $(OBJECTS)
	rm ./*.o

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

error.o: src/error/error.c
	$(CC) $(CFLAGS) -c src/error/error.c

parse.o: src/parse/parse.c
	$(CC) $(CFLAGS) -c src/parse/parse.c

util.o: src/util/freeSelfPointer.c
	$(CC) $(CFLAGS) -c src/util/freeSelfPointer.c -o util.o

vector.o: src/vector/vector.c
	$(CC) $(CFLAGS) -c src/vector/vector.c

run: default
	./$(DIST)

clean:
	rm ./$(DIST)
