# ==============================================================================
# Static Library: Archive of ELF Relocatble Object Files
# ==============================================================================
# Compiler and linker flags
CC = gcc
CFLAGS = -c -Wall
LDFLAGS = -L$(STLIB_PATH) -l$(STLIB_NAME) -lm
# Library path and file definitions
PARENT=..
STLIB_DIR = ./opt
STLIB_NAME = geometry
STLIB_PATH = $(STLIB_DIR)/${STLIB_NAME}
STLIB = $(STLIB_PATH)/lib$(STLIB_NAME).a
# Header file
HDR_F = $(PARENT)/ExtremeC_examples_chapter3_2_geometry.h
# Source and executable definitions
EXEC = ex3_3.out
SRC = ExtremeC_examples_chapter3_2_trigon.c \
      ExtremeC_examples_chapter3_2_2d.c \
      ExtremeC_examples_chapter3_2_3d.c
_SRC = $(subst ExtremeC_examples_chapter3_2_,,$(SRC))
# List of object files
OBJS = $(_SRC:.c=.o)

.PHONY: all clean run

# Default target
all: $(EXEC)

# Link the final executable
$(EXEC): main.o $(STLIB)
	$(CC) $< $(LDFLAGS) -o $@

# Build the static library
$(STLIB): $(OBJS)
	mkdir -p $(@D)
	ar crs $@ $^

# Compile temporary object files for static library
$(word 1, $(OBJS)): $(PARENT)/$(word 1, $(SRC)) $(HDR_F)
	$(CC) $(CFLAGS) $< -o $@
$(word 2, $(OBJS)): $(PARENT)/$(word 2, $(SRC)) $(HDR_F)
	$(CC) $(CFLAGS) $< -o $@
$(word 3, $(OBJS)): $(PARENT)/$(word 3, $(SRC)) $(HDR_F)
	$(CC) $(CFLAGS) $< -o $@

# Compile main relocatable object file
main.o: $(PARENT)/ExtremeC_examples_chapter3_3.c $(HDR_F)
	$(CC) $(CFLAGS) $< -o $@

# Run the executable
run: $(EXEC)
	./$(EXEC)

# Clean up generated files
clean:
	rm -fv *.o $(EXEC)
	rm -rfv $(STLIB_DIR)
