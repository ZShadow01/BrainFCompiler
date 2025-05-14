CC := gcc
CFLAGS := -Wall -O2

SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := obj

ifeq ($(OS),Windows_NT)
	TARGET_FILE := brainf.exe
	TARGET := $(BIN_DIR)/brainf.exe
	PATH_SEP := \\
	DEL := del /Q
else
	TARGET_FILE := brainf
	TARGET := $(BIN_DIR)/brainf
	DEL := rm
	PATH_SEP := /
endif

SRC_FILES := main.c tokenizer.c parser.c errors.c ast.c codegen.c
OBJ_FILES := $(SRC_FILES:%.c=%.o)

SRC := $(SRC_FILES:%.c=$(SRC_DIR)/%.c)
OBJ := $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

#################################################################

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $^


$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(DEL) $(BIN_DIR)$(PATH_SEP)$(TARGET_FILE)
	$(DEL) $(OBJ_DIR)$(PATH_SEP)*.o
