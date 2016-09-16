#!/usr/bin/env make

CYAN := "\033[0;36m"
LIGHT_CYAN := "\033[1;36m"
LIGHT_GREEN := "\033[1;32m"
NO_COLOUR := "\033[0m"
WHITE := "\033[1;37m"

# Configurable settings
TARGET ?= $(shell basename `pwd`)
BUILD_DIR ?= build
SRC_DIRS ?= client common

SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

VERSION := $(shell git rev-parse --short HEAD)
CFLAGS_BASE := -O2 -std=c11 -pipe -ffast-math -pedantic
CFLAGS_gcc := -Wall -Wextra -Wshadow
CFLAGS_clang := -Weverything -Wno-documentation-unknown-command
CFLAGS := $(CFLAGS_BASE) $(CFLAGS_$(notdir $(CC))) -D'__VERSION="$(VERSION)"'
LDFLAGS :=

all: debug

debug: CFLAGS += -g -DDEBUG
debug: $(BUILD_DIR)/$(TARGET_EXEC)

release: CFLAGS += -Werror
release: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@echo $(NO_COLOUR)Linking $(LIGHT_GREEN)$(TARGET)$(NO_COLOUR)
	@$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/%.c.o: %.c
	@echo $(NO_COLOUR)Building $(CYAN)$@$(NO_COLOUR) from $(CYAN)$<$(NO_COLOUR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@echo Cleaning...
	@rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEPS)