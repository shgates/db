CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
BUILD_DIR = build
EXECUTABLE = itp-db

SOURCE_FILES = $(wildcard $(SRC_DIR)/*.c)

OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCE_FILES))

UNAME_S = $(shell uname)

ifeq ($(UNAME_S), Linux)
	OS_IS_UNIX := true
else ifeq ($(UNAME_S), Darwin)
	OS_IS_UNIX := true
else
	OS_IS_UNIX := false
endif

.PHONY: all clean cleandb

all: clean cleandb $(BUILD_DIR) $(EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
ifeq ($(OS_IS_UNIX), true)
	rm -rf $(BUILD_DIR) $(EXECUTABLE)
else 
	rmdir /S /Q $(BUILD_DIR) $(EXECUTABLE)
endif

cleandb:
ifeq ($(OS_IS_UNIX), true)
	rm -rf db/*
else 
	rmdir /S /Q  db/*
endif


ifeq ($(OS_IS_UNIX), true)
	if [ ! -d "db" ]; then \
        mkdir db; \
	fi
else
	if not exist "db" mkdir db
endif

	touch db/listoftables.txt

