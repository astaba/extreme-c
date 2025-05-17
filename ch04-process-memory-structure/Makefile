# Compiler and flags
.PHONY: all clean
.DELETE_ON_ERROR:

CC = gcc
CFLAGS = -Wall
LDFLAGS =

# Source files
SOURCES = $(wildcard *.c)
# _SOURCES = $(subst ExtremeC_examples_chapter,ex,$(SOURCES))
# Executables
BINARIES = $(SOURCES:.c=.out)

# Default target
all: $(BINARIES)

# Rule to build each executable
$(BINARIES): %.out: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Clean target to remove built files
clean:
	@rm -fv $(BINARIES)
