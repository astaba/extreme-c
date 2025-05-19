# ch03-object-files/00_ELF_object_files/Makefile
# ==============================================================================
# ELF Relocatble Object Files vs ELF Executable Object Files
# ==============================================================================
.PHONY: \
	all \
	10_investigate_the_content_of_relocatable_object_files \
	11_dump_symbol_tables_of_relocatable_object_files \
	12_examin_content_of_ELF_executable_object_files \
	13_examin_the_symbol_table_in_ELF_executable \
	clean
.DELETE_ON_ERROR:
# ******************************************************************************
CC = gcc
VPATH = ..
# ******************************************************************************
SOURCES = ExtremeC_examples_chapter3_1.c \
		  ExtremeC_examples_chapter3_1_funcs.c
OBJECTS = main.o funcs.o
BINARY = $(subst .o,.out,$(word 1,$(OBJECTS)))
# ******************************************************************************

all:
	@echo "After \"make␣\" Trigger auto completion for available commands."

# ******************************************************************************
# readelf -h: displays headers of the ELF object file
# readelf -S: displays section headers
# readelf -s: displays entries in symbol tables
# readelf -l: displays segments headers (useless for relocatable)
# ******************************************************************************
10_investigate_the_content_of_relocatable_object_files: $(word 2,$(OBJECTS))
	readelf -hS $(word 2,$(OBJECTS))
	@echo ""
	@echo "======================================================================"
	@echo -e "==  EXPLANATION  ==\nAs you can see in the preceding shell box, the relocatable object file has 12 sections. The .text, .data, .bss and .symtab sections are the sections that we have introduced as items existing in an object file. The .text section contains all the machine-level instructions for the translation unit. The .data and .bss sections contain the values for initialized global variables, and the number of bytes required for uninitialized global variables respectively. The .symtab section contains the symbol table."
	@echo "======================================================================"

# ******************************************************************************
11_dump_symbol_tables_of_relocatable_object_files: $(OBJECTS) 
	readelf -s $(word 2,$(OBJECTS))
	@echo ""
	@echo "======================================================================"
	@echo -e "==  EXPLANATION  ==\nAs you can see in the value column the address assigned to max is O and the address assigned to max_3 is 27 (0x1b). This means that the instruction related to these symbols are adjacent and their addresses start from 0. These symbols, and their corresponding machine-level instruction are ready to be relocated in other places in the final executable."
	@echo "======================================================================"
	@echo ""
	readelf -s $(word 1,$(OBJECTS))
	@echo ""
	@echo "======================================================================"
	@echo -e "==  EXPLANATION  ==\nAs you can see, the symbols associated with global variables a and b, as well as the symbol for the main function are put at addresses that don't seem to be the final addresses that they should be placed at."
	@echo "======================================================================"

# ******************************************************************************
12_examin_content_of_ELF_executable_object_files: $(BINARY)
	@echo "======================================================================"
	@echo -e "==  EXPLANATION  ==\nWhile examining ELF relocatable object files, we spoke about sections being present in an ELF object file. We should say that more sections exist in an ELF executable object file, but together with some segments. Every ELF executable object file, and as you will see later in this chapter, every ELF shared object file, has a number of segments in addition to sections. Each segment consists of a number of sections (zero or more), and the sections are put into segments based on their content.\n\nFor example, all sections containing machine-level instructions go into the same segment. You will see in Chapter 4, Process Memory Structure, that these segments nicely map to static memory segments found in the memory layout of a running process."
	@echo "======================================================================"
	@echo ""
	readelf -hSl $(BINARY)
	@echo ""
	@echo "======================================================================"
	@echo -e "== EXPLANATION ==\nThere are multiple notes about the above output:\n\n1. We can see that the type of object file from the ELF point of vew, is a shared object file. In other words, in ELF, an executable object file is a shared object file that has some specific segments like INTERP. This segment (actually the .interp section which is referred to by this segment) is used by the loader program to load and execute the executable object file.\n\n2. Among the most relevant segments, the first one refers to the INTERP segment (index 01) which is explained in the previous bullet point. The second one is the TEXT segment (index 02). It contains all the section having machine-level instructions. From segment 03 to 05 are the DATA segments that contains all the values that should be used to initialize the global variables and other early structures. Segment 06 refers to the section that dynamic linking related information can be found. For instance, the shared object files that need to be loaded as part of the execution.\n\n3. As you see, we've got more sections in comparison to a relocatable shared object, probably filled with data required to load and execute the object file.\n\nAs we explained in the previous section, the symbols found in the symbol table of a relocatable object file do not have any absolute and determined addresses. That's because the sections containing machine-level instructions are not linked yet. In a deeper sense, linking a number of relocatable object files is actually to collect all similar sections from the given relocatable object files and put them together to form a bigger section, and finally put the resulting section into the output executable or the shared object file. Therefore, only after this step, the symbols can be finalized and obtain the addresses that are not going to change. In executable object files, the addresses are absolute, while in shared object files, the relative addresses are absolute. We will discuss this more in the section dedicated to dynamic libraries."
	@echo "======================================================================"

# ******************************************************************************
13_examin_the_symbol_table_in_ELF_executable: $(BINARY)
	readelf -s $(BINARY)
	@echo ""
	@echo "======================================================================"
	@echo -e "== EXPLANATION ==\nAs you see in the preceding shell box, we have two different symbol tables in an executable object file. The first one, .dynsym, contains the symbols that should be resolved when loading the executable, but the second symbol table, .symtab, contains all the resolved symbols together with unresolved symbols brought from the dynamic symbol table. In other words, the symbol table contains the unresolved symbols from the dynamic table as well.\n\nAs you see, the resolved symbols in the symbol table have absolute corresponding addresses that they have obtained after the linking step. The addresses for max and max_3 symbols are shown in bold font."
	@echo "======================================================================"

# ******************************************************************************
$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

$(word 1,$(OBJECTS)): %.o: $(VPATH)/$(word 1,$(SOURCES))
	$(CC) -c -o $@ $<
$(word 2,$(OBJECTS)): %.o: $(VPATH)/$(word 2,$(SOURCES))
	$(CC) -c -o $@ $<

# ******************************************************************************
clean:
	@rm -vf *.o *.out
