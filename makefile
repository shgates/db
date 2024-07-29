CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
BUILD_DIR = build
EXECUTABLE = db

SOURCE_FILES = $(wildcard $(SRC_DIR)/*.c)

OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCE_FILES))

.PHONY: all clean cleandb

all: clean $(BUILD_DIR) $(EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

cleandb:
	rm -rf db/*
	touch db/ListOfTables.txt

