CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC = $(wildcard src/*.c)
TARGET = pokemon

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

run: $(TARGET)
	./$(TARGET)

test:
	$(CC) $(CFLAGS) test/test_typechart.c src/typechart.c src/pokemon.c -o test_typechart
	./test_typechart

clean:
	rm -f $(TARGET) test_typechart