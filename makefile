CC=gcc
CFLAGS=-Wall -Wextra -g
SOURCES=main.c frame_validator.c score_calculator.c game_display.c
OBJECTS=$(SOURCES:.c=.o)
DEPS=bowling_game.h frame_validator.h score_calculator.h game_display.h
TARGET=bowling_game

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean all
