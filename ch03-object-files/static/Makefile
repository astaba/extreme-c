# ==============================================================================
# Static Library: Archive of ELF Relocatble Object Files (like -lm)
# ==============================================================================
# Compiler and linker flags
.PHONY: all clean run
.DELETE_ON_ERROR:

CC = gcc
CFLAGS = -Wall
LDFLAGS = -L$(STATIC_LIB_DIR) -l$(STATIC_LIB_NAME) -lm
# Library path and file definitions
VPATH = ..
RELATIVE_ROOT = ./opt
STATIC_LIB_NAME = geometry
STATIC_LIB_DIR = $(RELATIVE_ROOT)/${STATIC_LIB_NAME}
STATIC_LIB = $(STATIC_LIB_DIR)/lib$(STATIC_LIB_NAME).a
# Header file
HEADERS = ExtremeC_examples_chapter3_2_geometry.h
# Source and executable definitions
SOURCES = ExtremeC_examples_chapter3_3.c \
		  ExtremeC_examples_chapter3_2_trigon.c \
		  ExtremeC_examples_chapter3_2_2d.c \
		  ExtremeC_examples_chapter3_2_3d.c
# List of object files
OBJECTS = $(subst .c,.o,$(SOURCES))
# Executable file
BINARY = $(subst .c,.out,$(word 1,$(SOURCES)))

# Default target
all: $(BINARY)

# Link the final executable
$(BINARY): $(word 1, $(OBJECTS)) $(STATIC_LIB)
	$(CC) $< -o $@ $(LDFLAGS)

# Build the static library
$(STATIC_LIB): $(filter-out $(word 1, $(OBJECTS)),$(OBJECTS))
	mkdir -p $(@D) && ar crs $@ $^

# Compile temporary (relocatable) object files
%.o: $(VPATH)/%.c $(VPATH)/$(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the executable
run: $(BINARY)
	./$(BINARY)

# Clean up generated files
clean:
	rm -fv *.o $(BINARY)
	@echo "You're about to clean $(RELATIVE_ROOT) ? [y/n]"; \
	read ans; \
	if [ "$$ans" = "y" ]; then \
		rm -rv $(RELATIVE_ROOT); \
	fi

