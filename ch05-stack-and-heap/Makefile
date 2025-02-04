# ==============================================================================
# Chapter 05: Stack and Heap
# ==============================================================================
# Compiler and linker flags
CC = gcc
CFLAGS =
# CFLAGS = -Wall -Wextra
# CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -Werror=return-local-addr
LDFLAGS =
DBGFLAGS= -g3 -O0 -DDEBUG
# Source and executable definitions
# EXEC = ex3_3.out
SRC = ExtremeC_example5_1.c \
      ExtremeC_example5_2.c \
      ExtremeC_example5_3.c \
      ExtremeC_example5_4.c \
      ExtremeC_example5_5.c \
      ExtremeC_example5_6.c
_SRC = $(subst ExtremeC_example,ex, $(SRC))
# Executables
EXECS = $(_SRC:.c=.out)
# Executables for debug
DBUGS = $(subst .out,_dbg.out, $(EXECS))

.PHONY: all clean debug

# Default target
all: $(EXECS) $(DBUGS)

$(word 1, $(EXECS)): $(word 1, $(SRC))
	$(CC) $(CFLAGS) $< -o $@

$(word 2, $(EXECS)): $(word 2, $(SRC))
	$(CC) $(CFLAGS) $< -o $@

$(word 3, $(EXECS)): $(word 3, $(SRC))
	$(CC) $(CFLAGS) $< -o $@

$(word 4, $(EXECS)): $(word 4, $(SRC))
	$(CC) $(CFLAGS) $< -o $@

$(word 5, $(EXECS)): $(word 5, $(SRC))
	$(CC) $(CFLAGS) $< -o $@

$(word 6, $(EXECS)): $(word 6, $(SRC))
	$(CC) $(CFLAGS) $< -o $@

debug: $(DBUGS)

$(word 1, $(DBUGS)): $(word 1, $(SRC))
	$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

$(word 2, $(DBUGS)): $(word 2, $(SRC))
	$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

$(word 3, $(DBUGS)): $(word 3, $(SRC))
	$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

$(word 4, $(DBUGS)): $(word 4, $(SRC))
	$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

$(word 5, $(DBUGS)): $(word 5, $(SRC))
	$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

$(word 6, $(DBUGS)): $(word 6, $(SRC))
	$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

# Clean up generated files
clean:
	rm -fv *.out
