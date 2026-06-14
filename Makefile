CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g
SRC     = pokemon.c typechart.c
HEADERS = pokemon.h typechart.h

# binário principal
TARGET  = poke
# binário de testes
TEST    = test_typechart

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): main.c $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) main.c $(SRC) -o $(TARGET)

$(TEST): test_typechart.c $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) test_typechart.c $(SRC) -o $(TEST)

run: $(TARGET)
	./$(TARGET)

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(TARGET) $(TEST)
