CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
BUILD_DIR = build
EXECUTABLE = itp-db

SOURCE_FILES = $(wildcard $(SRC_DIR)/*.c)

OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCE_FILES))

OS = $(shell uname)

.PHONY: all clean cleandb

all: clean cleandb $(BUILD_DIR) $(EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
ifeq ($(OS), Windows_NT)
	rmdir /S /Q $(BUILD_DIR) $(EXECUTABLE)
else 
	rm -rf $(BUILD_DIR) $(EXECUTABLE)
endif

cleandb:
ifeq ($(OS), Windows_NT)
	rmdir /S /Q  db/*
else 
	rm -rf db/*
endif

	if [ ! -d "db" ]; then \
        mkdir db; \
	fi
	touch db/listoftables.txt

