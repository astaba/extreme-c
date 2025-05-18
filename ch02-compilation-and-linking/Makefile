# extreme_c/ch02-compilation-and-linking/Makefile

.PHONY: \
	all \
	clean \
	1_compilation_pipeline \
	20_preprocessing \
	21_compiler_frontend \
	3_examin_the_content_of_relocatable_object_files \
	40_compile_sources_2_4_to_relocatable_object_files \
	41_look_at_symbol_tables \
	420_linker_missing_multiply \
	421_linker_missing_add \
	422_linker_missing__start \
	43_linking_process \
	5_linker_can_be_fooled \
	60_disassembly_of_overload_functions_symbols \
	61_g++compiled_object_files_symbol_tables \
	62_g++prevent_linker_confusion
.DELETE_ON_ERROR:

CC       = gcc
CFLAGS   =
# This cpp (C Pre-Processor) flag removes "#lines"
CPPFLAGS = -P
# **************************  EXAMPLE 1  ***************************************
HRD_21 = ExtremeC_examples_chapter2_1.h
SRC_21 = ExtremeC_examples_chapter2_1_main.c \
				 ExtremeC_examples_chapter2_1.c
# Translation unit
TRU_21 = $(subst .c,.i,$(SRC_21))
# Assembly code
ASS_21 = $(subst .c,.s,$(SRC_21))
# Intermadiate relocatable object files
OBJ_21 = $(subst .c,.o,$(SRC_21))
# Executable object file of example_2_1
EXE_21 = main2_1.out
# **************************  EXAMPLE X  ***************************************
SRC_2X = ExtremeC_examples_chapter2_x.c
TRU_2X = $(subst .c,.i,$(SRC_2X))
# **************************  EXAMPLE 2  ***************************************
SRC_22 = ExtremeC_examples_chapter2_2.c
# **************************  EXAMPLE 3  ***************************************
SRC_23 = ExtremeC_examples_chapter2_3.c
OBJ_23 = $(subst .c,.o,$(SRC_23))
# **************************  EXAMPLE 4  ***************************************
HRD_24 = ExtremeC_examples_chapter2_4_decls.h
SRC_24 = ExtremeC_examples_chapter2_4_main.c \
				 ExtremeC_examples_chapter2_4_add.c \
				 ExtremeC_examples_chapter2_4_multiply.c
OBJ_24 = main2_4.o add2_4.o multiply2_4.o 
EXE_24 = $(subst .o,.out,$(word 1,$(OBJ_24)))
# **************************  EXAMPLE 5  ***************************************
SRC_25 = ExtremeC_examples_chapter2_5_main.c \
				 ExtremeC_examples_chapter2_5_add.c
OBJ_25 = main2_5.o add2_5.o
EXE_25 = $(subst .o,.out,$(word 1,$(OBJ_25)))
# **************************  EXAMPLE 6  ***************************************
SRC_26 = ExtremeC_examples_chapter2_6_add_1.c \
				 ExtremeC_examples_chapter2_6_add_2.c
EXAMPLE_26_STEM = ExtremeC_examples_chapter2_6_
_OBJ_26 = $(subst .c,.o,$(SRC_26))
OBJ_26 = $(subst $(EXAMPLE_26_STEM),,$(_OBJ_26))
# **************************  EXAMPLE 6_1  *************************************
OBJ_26pp = add_1pp.o add_2pp.o
# ******************************************************************************

all:
	@echo "After \"make␣\" Trigger auto completion for available commands."

# **************************  EXAMPLE 1  ***************************************
# GENERAL PRESENTATION OF THE COMPILATION PIPELINE
# Preprocessing, Compiling, Assembly and Linking.
# With the right commands the tree first steps can be incrementally avoided.
# ******************************************************************************
1_compilation_pipeline: $(EXE_21)

# Linking object files to generate executable
$(EXE_21): $(OBJ_21)
	$(CC) -o $@ $^

# Assembly to generate relocatable object code
# as -o $@ $<
# It is recommmended to let the compiler (gcc\clang) call as
$(OBJ_21): %.o: %.s
	$(CC) -c $<

# Compiling (compiler backend output) to generate assembly code
$(ASS_21): %.s: %.i
	$(CC) -S $<

# Preprocessing to expand to translation unit
$(TRU_21): %.i: %.c $(HRD_21)
	$(CC) -E -o $@ $<

# **************************  EXAMPLE X  ***************************************
# PREPROCESSING: A SIMPLE TEXT SUBSTITUTION
# Preprocessors know nothing about C syntax
# ******************************************************************************
20_preprocessing: $(TRU_2X)

$(TRU_2X): $(SRC_2X)
	cpp $(CPPFLAGS) $< > $@

# **************************  EXAMPLE 2  ***************************************
# COMPILING: COMPILER FRONTEND AND BACKEND
# Before the compiler backend generates assembly code the compiler frontend
# must turn the translation unit into an architecture-independent three-like
# structure based on C grammar and called:
# **************  ABSTRACT SYNTAX THREE (AST) **********************************
21_compiler_frontend:
	clang -Xclang -ast-dump -fsyntax-only $(SRC_22)

# **************************  EXAMPLE 3  ***************************************
# ASSEMBLY: EXAMIN THE CONTENT OF RELOCATABLE OBJECT FILES
# Possible output artifacts of building a C project are:
# executable files, static libraries, dynamic libraries of shared object
# file, and all of them are objects files. Although relocatable object files
# are never output product we need to examin their internal structure
# to better understand the linking business.
# ******************************************************************************
3_examin_the_content_of_relocatable_object_files: $(OBJ_23)
	@echo "== SOURCE CODE ======================================================="
	cat $(SRC_23)
	@echo "== SYMBOLS ==========================================================="
	nm $<
	@echo "== SYMBOL TABLE ======================================================"
	readelf -s $<
	@echo "== DISASSEMBLY OF MACHINE LEVEL INSTRUCTIONS ========================="
	objdump -d $<

$(OBJ_23): $(SRC_23)
	$(CC) -c $<

# **************************  EXAMPLE 4  ***************************************
# LINKING: PROCESS AND PITFALLS
# ******************************************************************************
43_linking_process: $(EXE_24)

$(EXE_24): $(OBJ_24)
	$(CC) -o $@ $^

420_linker_missing_multiply: $(word 1,$(OBJ_24)) $(word 2,$(OBJ_24))
	@echo "== LINKIN ONLY add.o and main.o  ====================================="
	$(CC) $(word 1,$(OBJ_24)) $(word 2,$(OBJ_24))
421_linker_missing_add: $(word 1,$(OBJ_24)) $(word 3,$(OBJ_24))
	@echo "== LINKIN ONLY multiply.o and main.o  ================================"
	$(CC) $(word 1,$(OBJ_24)) $(word 3,$(OBJ_24))
422_linker_missing__start: $(word 2,$(OBJ_24)) $(word 3,$(OBJ_24))
	@echo "== LINKIN ONLY add.o and multiply.o  ================================="
	$(CC) $(word 2,$(OBJ_24)) $(word 3,$(OBJ_24))

41_look_at_symbol_tables: $(OBJ_24)
	@echo "== SOURCE CODE ======================================================="
	cat $(word 3,$(SRC_24))
	@echo "== SYMBOLS ==========================================================="
	readelf -s $(word 3,$(OBJ_24))
	@echo "== SOURCE CODE ======================================================="
	cat $(word 2,$(SRC_24))
	@echo "== SYMBOLS ==========================================================="
	readelf -s $(word 2,$(OBJ_24))
	@echo "== SOURCE CODE ======================================================="
	cat $(word 1,$(SRC_24))
	@echo "== SYMBOLS ==========================================================="
	readelf -s $(word 1,$(OBJ_24))

40_compile_sources_2_4_to_relocatable_object_files: $(OBJ_24)

$(word 1,$(OBJ_24)): $(word 1,$(SRC_24)) $(HRD_24)
	$(CC) -c -o $@ $<
$(word 2,$(OBJ_24)): $(word 2,$(SRC_24)) $(HRD_24)
	$(CC) -c -o $@ $<
$(word 3,$(OBJ_24)): $(word 3,$(SRC_24)) $(HRD_24)
	$(CC) -c -o $@ $<

# **************************  EXAMPLE 5  ***************************************
# LINKER CAN BE FOOLED!
# Defining overload functions in ths source codes: function with the same 
# pointer variable name but different arguments signature.
# ******************************************************************************
5_linker_can_be_fooled: $(EXE_25)
	./$(EXE_25)
	@echo "== COMPARE RESULT WITH SOURCE CODE  =================================="
	cat $(word 1,$(SRC_25))

$(EXE_25): $(OBJ_25)
	$(CC) -o $@ $^

$(word 1,$(OBJ_25)): $(word 1,$(SRC_25))
	$(CC) -c -o $@ $<
$(word 2,$(OBJ_25)): $(word 2,$(SRC_25))
	$(CC) -c -o $@ $<

# **************************  EXAMPLE 6  ***************************************
# WHAT FOOLED THE LINKER ??? DISASSEMBLY OF OVERLOAD FUNCTION
# ******************************************************************************

60_disassembly_of_overload_functions_symbols: $(OBJ_26)
	objdump -d $(word 1,$(OBJ_26))
	@echo "======================================================================"
	objdump -d $(word 2,$(OBJ_26))
	@echo "======================================================================"
	@echo "CPU register %rbp is the one that points to the current stack frame."
	@echo "Looking to it you can clearly see how the arguments are collected"
	@echo "from the stack frame. These instructions copy four values for add_1.o"
	@echo "and two values for add_2.o from the memory addresses, which have"
	@echo "been pointed to by the %rbp, and put them into the local registers."
	@echo "The main function only puts two values into the stack frame, but"
	@echo "the add function, expecting four arguments, goes beyond that stack"
	@echo "frame reading two allocted spaces resulting in wrong computation."

$(OBJ_26): %.o: $(EXAMPLE_26_STEM)%.c
	$(CC) -c -o $@ $<

# **************************  EXAMPLE 6_1  *************************************
# C++ NAME MANGLING
# When overload functions are compiled with g++ (instead of gcc) the compiler
# named them specifically to avoid confusion while the linker is reading the
# relocatable object file. That is some advantages of C++.
# ******************************************************************************
61_g++compiled_object_files_symbol_tables: $(OBJ_26) $(OBJ_26pp)
	@echo "==  GCC COMPILED OBJECT FILES SYMBOL TABLES  ========================="
	readelf -s $(word 1,$(OBJ_26)) && readelf -s $(word 2,$(OBJ_26))
	@echo ""
	@echo "======================================================================"
	@echo "==  WHY GCC-PRODUCED RELOCATABLES FOOL LD LINKER  ===================="
	@echo "Source codes compiled and assembled with gcc produce relocatable object files,"
	@echo "in which symbol tables, overload functions have the same symbolic name."
	@echo "As a result when gcc pass those confusing object files to ld,"
	@echo "the linker produces a broken executable without throwing any exception."
	@echo "======================================================================"
	@echo ""
	@echo "==  G++ COMPILED OBJECT FILES SYMBOL TABLES  ========================="
	@echo "==  FUNCTION NAME MANGLING PREVENT LINKING CONFUSION  ================"
	@echo "======================================================================"
	readelf -s $(word 1,$(OBJ_26pp)) && readelf -s $(word 2,$(OBJ_26pp))

$(word 1,$(OBJ_26pp)): $(word 1,$(SRC_26))
	g++ -c -o $@ $<
$(word 2,$(OBJ_26pp)): $(word 2,$(SRC_26))
	g++ -c -o $@ $<

# **************************  EXAMPLE 6_2  *************************************
# Try linking with g++ a main() function confusely calling overload functions.
# PROVIDED relocatable object files are assembled with g++, name mangling
# will detect function overload and abort the linking.
# As a result main2_5pp.out is never built.
# Compare with 5_linker_can_be_fooled
# ******************************************************************************
62_g++prevent_linker_confusion: main2_5pp.out

main2_5pp.out: main2_5pp.o $(word 1,$(OBJ_26pp))
	g++ -o $@ $^

main2_5pp.o: $(word 1,$(SRC_25))
	g++ -c -o $@ $<

# ******************************************************************************
clean:
	@rm -vf *.i *.s *.o *.out

