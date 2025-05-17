# ==============================================================================
# Dynamic Library for LAZY LOADING: ELF Shared Object Files
# ==============================================================================
# Compiler and linker flags
.PHONY: all clean run
.DELETE_ON_ERROR:

CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
# Library path and file definitions
VPATH = ..
RELATIVE_ROOT = ./opt
DYNAMIC_LIB_NAME = geometry
DYNAMIC_LIB_DIR = $(RELATIVE_ROOT)/$(DYNAMIC_LIB_NAME)
DYNAMIC_LIB = $(DYNAMIC_LIB_DIR)/lib$(DYNAMIC_LIB_NAME).so
# Header file
HEADERS = ExtremeC_examples_chapter3_2_geometry.h
# Source and executable definitions
SOURCES = ExtremeC_examples_chapter3_4.c \
		  ExtremeC_examples_chapter3_2_trigon.c \
		  ExtremeC_examples_chapter3_2_2d.c \
		  ExtremeC_examples_chapter3_2_3d.c
# List of object files
OBJECTS = $(subst .c,.o,$(SOURCES))
DEPENDENCY_O = $(filter-out $(word 1, $(OBJECTS)),$(OBJECTS))
# Executable file
BINARY = $(subst .c,.out,$(word 1,$(SOURCES)))

# Default target
all: $(BINARY)

# NOTE: Link the final executable with -ldl for dynamic lazy loading
$(BINARY): $(word 1, $(OBJECTS)) $(DYNAMIC_LIB)
	$(CC) $< -ldl -o $@

# NOTE: When building dynamic library to be lazy loaded by executable,
# make sure to use the -l option to link to libraries that could be
# required by the loading library at run-time.
$(DYNAMIC_LIB): $(DEPENDENCY_O)
	mkdir -p $(@D) && $(CC) -shared $^ -o $@ $(LDFLAGS) 

# Compile temporary object files as Position Independent Code
$(DEPENDENCY_O): %.o: $(VPATH)/%.c $(VPATH)/$(HEADERS)
	$(CC) $(CFLAGS) -c $< -fPIC -o $@

# Compile main relocatable object file
$(word 1, $(OBJECTS)): %.o: $(VPATH)/%.c $(VPATH)/$(HEADERS)
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

