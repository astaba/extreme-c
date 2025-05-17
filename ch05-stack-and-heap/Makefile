# ==============================================================================
# Chapter 05: Stack and Heap
# ==============================================================================
# Compiler and linker flags
.PHONY: all clean debug
.DELETE_ON_ERROR:

CC = gcc
CFLAGS = -Wall
# CFLAGS = -Wall -Wextra -Werror
LDFLAGS =
# DBGFLAGS=
# Source and executable definitions
SOURCES = ExtremeC_example5_1.c \
		  ExtremeC_example5_2.c \
		  ExtremeC_example5_3.c \
		  ExtremeC_example5_4.c \
		  ExtremeC_example5_5.c \
		  ExtremeC_example5_6.c
# _SOURCES = $(subst ExtremeC_example,ex, $(SOURCES))
# Executables
BINARIES = $(SOURCES:.c=.out)

# Default target
all: $(BINARIES)

$(BINARIES): %.out: %.c
	$(CC) $(CFLAGS) $< -o $@

debug: CFLAGS += -g3 -O0 -DDEBUG
debug: all

# Clean up generated files
clean:
	rm -fv *.out
