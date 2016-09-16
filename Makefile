#!/usr/bin/env make

VERSION := $(shell git rev-parse --short HEAD)

CYAN := "\033[0;36m"
LIGHT_CYAN := "\033[1;36m"
LIGHT_GREEN := "\033[1;32m"
NO_COLOUR := "\033[0m"
WHITE := "\033[1;37m"

DATDIR := data
OBJDIR := build
OUTDIR := bin

TARGET := $(OUTDIR)/$(shell basename `pwd`)

CFLAGS := -O2 -std=c11 -Wall -Wextra -Wshadow -Wno-pointer-arith -Wcast-qual
CFLAGS += -Wuninitialized -Werror=return-type -Werror=shadow
LDFLAGS :=


CFLAGS += -D'__VERSION="$(VERSION)"'

SRCS := $(wildcard common/*.c) $(wildcard client/*.c)
_OBJS := $(SRCS:.c=.o)
OBJS := $(subst common,$(OBJDIR),$(_OBJS))
OBJS := $(subst client,$(OBJDIR),$(OBJS))


all: directories debug

debug: CFLAGS += -g -DDEBUG
debug: release

release: $(OBJS)
	@echo -e $(NO_COLOUR)Linking $(LIGHT_GREEN)$(TARGET)$(NO_COLOUR)
	@$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

$(OBJS): $(SRCS)

$(OBJDIR)/%.o: client/%.c
	@echo -e $(NO_COLOUR)Building $(CYAN)$@$(NO_COLOUR) from $(CYAN)$<$(NO_COLOUR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/%.o: common/%.c
	@echo -e $(NO_COLOUR)Building $(CYAN)$@$(NO_COLOUR) from $(CYAN)$<$(NO_COLOUR)
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	@echo -e Cleaning...
	@rm -rf $(OBJDIR)/*.o $(TARGET)

.PHONY: directories
directories:
	@if [ ! -d $(OBJDIR) -a ! -d $(OUTDIR) ]; then \
		mkdir -p $(OBJDIR) $(OUTDIR); \
	fi
