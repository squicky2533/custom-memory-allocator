
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC = src/allocator.c
TEST = test/test_allocator.c

OUT = allocator

all: $(OUT)

$(OUT):
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)