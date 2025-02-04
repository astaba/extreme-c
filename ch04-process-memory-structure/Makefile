# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =

# Source files
SRC = \
  ExtremeC_examples_chapter4_1.c \
  ExtremeC_examples_chapter4_2.c \
  ExtremeC_examples_chapter4_3.c \
  ExtremeC_examples_chapter4_4.c \
  ExtremeC_examples_chapter4_5.c \
  ExtremeC_examples_chapter4_6.c \
  ExtremeC_examples_chapter4_7.c \
  ExtremeC_examples_chapter4_8.c
_SRC = $(subst ExtremeC_examples_chapter,ex,$(SRC))
# Executables
EXECS = $(_SRC:.c=.out)

# Default target
all: $(EXECS)

# Rule to build each executable
$(word 1, $(EXECS)): $(word 1, $(SRC))
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(word 2, $(EXECS)): $(word 2, $(SRC))
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(word 3, $(EXECS)): $(word 3, $(SRC))
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(word 4, $(EXECS)): $(word 4, $(SRC))
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(word 5, $(EXECS)): $(word 5, $(SRC))
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(word 6, $(EXECS)): $(word 6, $(SRC))
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(word 7, $(EXECS)): $(word 7, $(SRC))
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(word 8, $(EXECS)): $(word 8, $(SRC))
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Clean target to remove built files
clean:
	rm -fv $(EXECS)
