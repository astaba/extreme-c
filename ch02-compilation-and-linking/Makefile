# extreme_c/ch02-compilation-and-linking/Makefile

.PHONY: \
	all \
	clean \
	1_compilation_pipeline \
	2_preprocessing \
	3_compiler_frontend \
	4_relocatable_symbols \
	50_compile_sources_2_4_to_relocatable_object_files \
	51_look_at_symbol_tables \
	520_linker_missing_multiply \
	521_linker_missing_add \
	522_linker_missing__start \
	53_linking_process
.DELETE_ON_ERROR:

CC       = gcc
CFLAGS   =
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
EXE_21 = $(subst .c,.out,$(word 1,$(SRC_21)))
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
EXAMPLE_24_STEM = ExtremeC_examples_chapter2_4_
_OBJ_24 = $(subst .c,.o,$(SRC_24))
OBJ_24 = $(subst $(EXAMPLE_24_STEM),,$(_OBJ_24))

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
# PREPROCESSING AS A SIMPLE TEXT SUBSTITUTION
# Preprocessors know nothing about C syntax
# ******************************************************************************
2_preprocessing: $(SRC_2X)
	cpp $(CPPFLAGS) $< > $(TRU_2X)

# **************************  EXAMPLE 2  ***************************************
# COMPILER FRONTEND AND BACKEND
# Before the compiler backend generates assembly code the compiler frontend
# must turn the translation unit into an architecture-independent three-like
# structure based on C grammar and called:
# **************  ABSTRACT SYNTAX THREE (AST) **********************************
3_compiler_frontend:
	clang -Xclang -ast-dump -fsyntax-only $(SRC_22)

# **************************  EXAMPLE 3  ***************************************
# EXAMIN THE CONTENT OF RELOCATABLE OBJECT FILES
# Possible output artifacts of building a C project are:
# executable files, static libraries, dynamic libraries of shared object
# file, and all of them are objects files. Although relocatable object files
# are never output product we need to examin their internal structure
# to better understand the linking business.
# ******************************************************************************
4_relocatable_symbols: $(OBJ_23)
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
# LINKING
# ******************************************************************************
53_linking_process: $(OBJ_24)
	$(CC) $^

520_linker_missing_multiply: $(word 1,$(OBJ_24)) $(word 2,$(OBJ_24))
	@echo "== LINKIN ONLY add.o and main.o  ====================================="
	$(CC) $(word 1,$(OBJ_24)) $(word 2,$(OBJ_24))
521_linker_missing_add: $(word 1,$(OBJ_24)) $(word 3,$(OBJ_24))
	@echo "== LINKIN ONLY multiply.o and main.o  ================================"
	$(CC) $(word 1,$(OBJ_24)) $(word 3,$(OBJ_24))
522_linker_missing__start: $(word 2,$(OBJ_24)) $(word 3,$(OBJ_24))
	@echo "== LINKIN ONLY add.o and multiply.o  ================================="
	$(CC) $(word 2,$(OBJ_24)) $(word 3,$(OBJ_24))

51_look_at_symbol_tables: $(OBJ_24)
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

50_compile_sources_2_4_to_relocatable_object_files: $(OBJ_24)

$(OBJ_24): %.o: $(EXAMPLE_24_STEM)%.c $(HRD_24)
	$(CC) -c -o $@ $<

# ******************************************************************************

clean:
	@rm -vf *.i *.s *.o *.out

