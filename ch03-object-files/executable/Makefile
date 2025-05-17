# ==============================================================================
# ELF Relocatble Object Files vs ELF Executable Object Files
# Content Comparison
# ==============================================================================
.PHONY: all clean read
.DELETE_ON_ERROR:

# Compiler and linker flags
CC = gcc
VPATH = ..

SOURCES = ExtremeC_examples_chapter3_1.c \
		  ExtremeC_examples_chapter3_1_funcs.c
OBJECTS = $(subst .c,.o,$(SOURCES))
BINARY = $(subst .c,.out,$(word 1,$(SOURCES)))

# Default target
all: $(BINARY)

# Link the final executable
$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(CPPLAGS) $(LDFLAGS) $^ -o $@

# Compile temporary object files
%.o: $(VPATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

read: $(BINARY)
	readelf -hS $(word 1,$(OBJECTS)) > main_hS.txt
	readelf -hS $(word 2,$(OBJECTS)) > funcs_hS.txt
	readelf -s $(word 1,$(OBJECTS)) > main_s.txt
	readelf -s $(word 2,$(OBJECTS)) > funcs_s.txt
	readelf -s $(BINARY) > ex_s.txt

# Clean up generated files
clean:
	@rm -fv *.o $(BINARY) *.txt
