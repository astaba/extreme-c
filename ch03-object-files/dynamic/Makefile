# ==============================================================================
# Dynamic Library: ELF Shared Object Files
# ==============================================================================
# Compiler and linker flags
.PHONY: all clean run
.DELETE_ON_ERROR:

CC = gcc
CFLAGS = -Wall
LDFLAGS = -L$(DYNAMIC_LIB_DIR) -l$(DYNAMIC_LIB_NAME) -lm
# Library path and file definitions
VPATH= ..
RELATIVE_ROOT = ./opt
DYNAMIC_LIB_NAME = geometry
DYNAMIC_LIB_DIR = $(RELATIVE_ROOT)/${DYNAMIC_LIB_NAME}
DYNAMIC_LIB = $(DYNAMIC_LIB_DIR)/lib$(DYNAMIC_LIB_NAME).so
# Header file
HEADERS = ExtremeC_examples_chapter3_2_geometry.h
# Source and executable definitions
SOURCES = ExtremeC_examples_chapter3_3.c \
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

# Link the final executable
$(BINARY): $(word 1, $(OBJECTS)) $(DYNAMIC_LIB)
	$(CC) $< -o $@ $(LDFLAGS) 

# Build the dynamic library as an ELF shared object file
$(DYNAMIC_LIB): $(DEPENDENCY_O)
	mkdir -p $(@D) && $(CC) -shared $^ -o $@

# Compile temporary object files as Position Independent Code
$(DEPENDENCY_O): %.o: $(VPATH)/%.c $(VPATH)/$(HEADERS)
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

# Compile main relocatable object file
$(word 1, $(OBJECTS)): %.o: $(VPATH)/%.c $(VPATH)/$(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Populate dynamic loader accessory path either with
# `export LD_LIBRARY_PATH=<library_path>:$LD_LIBRARY_PATH` or:
run: $(BINARY)
	LD_LIBRARY_PATH="$(DYNAMIC_LIB_DIR):$$LD_LIBRARY_PATH" ./$(BINARY)

# Clean up generated files
clean:
	rm -fv *.o $(BINARY)
	@echo "You're about to clean $(RELATIVE_ROOT) ? [y/n]"; \
	read ans; \
	if [ "$$ans" = "y" ]; then \
		rm -rv $(RELATIVE_ROOT); \
	fi

