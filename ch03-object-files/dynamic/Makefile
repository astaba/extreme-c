# ==============================================================================
# Dynamic Library: ELF Shared Object Files
# ==============================================================================
# Compiler and linker flags
CC = gcc
CFLAGS = -c -Wall
LDFLAGS = -L$(DYLIB_PATH) -l$(DYLIB_NAME) -lm
# Library path and file definitions
PARENT=..
DYLIB_DIR = ./opt
DYLIB_NAME = geometry
DYLIB_PATH = $(DYLIB_DIR)/${DYLIB_NAME}
DYLIB = $(DYLIB_PATH)/lib$(DYLIB_NAME).so
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
$(EXEC): main.o $(DYLIB)
	$(CC) $< $(LDFLAGS) -o $@

# Build the dynamic library as an ELF shared object file
$(DYLIB): $(OBJS)
	mkdir -p $(@D)
	$(CC) -shared $^ -o $@
# Compile temporary object files as Position Independent Code
# for dynamic library
$(word 1, $(OBJS)): $(PARENT)/$(word 1, $(SRC)) $(HDR_F)
	$(CC) $(CFLAGS) -fPIC $< -o $@
$(word 2, $(OBJS)): $(PARENT)/$(word 2, $(SRC)) $(HDR_F)
	$(CC) $(CFLAGS) -fPIC $< -o $@
$(word 3, $(OBJS)): $(PARENT)/$(word 3, $(SRC)) $(HDR_F)
	$(CC) $(CFLAGS) -fPIC $< -o $@

# Compile main relocatable object file
main.o: $(PARENT)/ExtremeC_examples_chapter3_3.c $(HDR_F)
	$(CC) $(CFLAGS) $< -o $@

# Populate dynamic loader accessory path either with
# `export LD_LIBRARY_PATH=<library_path>:$LD_LIBRARY_PATH` or:
run: $(EXEC)
	LD_LIBRARY_PATH="$(DYLIB_PATH):$$LD_LIBRARY_PATH" ./$(EXEC)

# Clean up generated files
clean:
	rm -fv *.o $(EXEC)
	rm -rfv $(DYLIB_DIR)
