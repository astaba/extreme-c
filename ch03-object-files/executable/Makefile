# ==============================================================================
# ELF Relocatble Object Files vs ELF Executable Object Files
#
# Content Comparison
#
# ==============================================================================
# Compiler and linker flags
CC = gcc
CFLAGS = -c
EXEC = ex3_1.out

PARENT=..
# List of object files
OBJS = main.o funcs.o

.PHONY: all clean read

# Default target
all: $(EXEC)

# Link the final executable
$(EXEC): $(OBJS)
	$(CC) $^ -o $@

# Compile temporary object files
main.o: $(PARENT)/ExtremeC_examples_chapter3_1.c
	$(CC) $(CFLAGS) $< -o $@
funcs.o: $(PARENT)/ExtremeC_examples_chapter3_1_funcs.c
	$(CC) $(CFLAGS) $< -o $@

read: $(EXEC) $(OBJS)
	readelf -hS main.o > main_hS.txt
	readelf -hS funcs.o > funcs_hS.txt
	readelf -s main.o > main_s.txt
	readelf -s funcs.o > funcs_s.txt
	readelf -s $(EXEC) > ex_s.txt

# Clean up generated files
clean:
	rm -fv *.o $(EXEC) *.txt
