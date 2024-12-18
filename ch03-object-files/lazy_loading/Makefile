# ==============================================================================
# Dynamic Library for LAZY LOADING: ELF Shared Object Files
# ==============================================================================
# Compiler and linker flags
CC = gcc
CFLAGS = -c -Wall
LDFLAGS = -lm
# Library path and file definitions
PARENT=..
LIB_ROOT = ./opt
LIB_PATH = $(LIB_ROOT)/geometry
LIB_NAME = geometry
DYN_LIB = $(LIB_PATH)/lib$(LIB_NAME).so
# Header file
HDR_F = $(PARENT)/ExtremeC_examples_chapter3_2_geometry.h
# Source and executable definitions
EXEC = ex3_4.out
SRC = ExtremeC_examples_chapter3_2_trigon.c \
      ExtremeC_examples_chapter3_2_2d.c \
      ExtremeC_examples_chapter3_2_3d.c
_SRC = $(subst ExtremeC_examples_chapter3_2_,,$(SRC))
# List of object files
OBJS = $(_SRC:.c=.o)

.PHONY: all clean run

# Default target
all: $(EXEC)

# NOTE: Link the final executable with -ldl for dynamic lazy loading
$(EXEC): main.o $(DYN_LIB)
	$(CC) $< -ldl -o $@

# NOTE: When building dynamic library to be lazy loaded by executable,
# make sure to use the -l option to link to libraries
# that could be required by the loading library at run-time.
$(DYN_LIB): $(OBJS)
	mkdir -p $(@D)
	$(CC) -shared $^ $(LDFLAGS) -o $@

# Compile temporary object files as Position Independent Code
# for dynamic library
$(word 1, $(OBJS)): $(PARENT)/$(word 1, $(SRC)) $(HDR_F)
	$(CC) $(CFLAGS) $< -fPIC -o $@
$(word 2, $(OBJS)): $(PARENT)/$(word 2, $(SRC)) $(HDR_F)
	$(CC) $(CFLAGS) $< -fPIC -o $@
$(word 3, $(OBJS)): $(PARENT)/$(word 3, $(SRC)) $(HDR_F)
	$(CC) $(CFLAGS) $< -fPIC -o $@

# Compile main relocatable object file
main.o: $(PARENT)/ExtremeC_examples_chapter3_4.c $(HDR_F)
	$(CC) $(CFLAGS) $< -o $@

# Run the executable
run: $(EXEC)
	./$(EXEC)

# Clean up generated files
clean:
	rm -fv *.o $(EXEC)
	rm -rfv $(LIB_ROOT)
