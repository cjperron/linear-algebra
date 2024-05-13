CC = gcc
CFLAGS = -Wall -Wextra -Ilib -MMD -MP -std=c2x -O3
LDFLAGS = -Llib
LDLIBS = -lm -lquadmath

SRC_DIR = ../src
TESTS_DIR = ../tests
BIN_DIR = bin
LIB_DIR = ../lib

SRCS = $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS = $(wildcard $(TESTS_DIR)/*.c)
LIB_SRCS = $(wildcard $(LIB_DIR)/**/*.c)
MAIN_OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:$(TESTS_DIR)/%.c=$(BIN_DIR)/%.o) $(LIB_SRCS:$(LIB_DIR)/%.c=$(BIN_DIR)/%.o)

EXECUTABLE = $(BIN_DIR)/main
# TEST_EXECUTABLES = $(TEST_SRCS:$(TESTS_DIR)/%.c=$(BIN_DIR)/%.exe)

TEST_REALNUMS = $(BIN_DIR)/realnum_test

DEPS = $(OBJS:.o=.d)

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(MAIN_OBJS) $(BIN_DIR)/lib.a
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BIN_DIR)/lib.a: $(LIB_SRCS:$(LIB_DIR)/%.c=$(BIN_DIR)/%.o)
	ar rcs $@ $^

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(TESTS_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(LIB_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)
