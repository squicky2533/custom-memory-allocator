CC = gcc

CFLAGS = -Wall -Wextra -g

TARGET = allocator

SRC = src/allocator.c test/test_allocator.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)