# ch03-object-files/01_static_library/Makefile
# ==============================================================================
# Static Library: Archive of ELF Relocatble Object Files (like -lm)
# ==============================================================================
.PHONY: \
	all \
	20_build_static_library \
	21_listing_the_content_of_the_static_library \
	30_test_linking_with_new_static_library \
	31_run_executble \
	clean
.DELETE_ON_ERROR:
# ******************************************************************************
CC = gcc
VPATH = ..
# ******************************************************************************
RELATIVE_ROOT = ./opt
STATIC_LIB_NAME = geometry
STATIC_LIB_DIR = $(RELATIVE_ROOT)/${STATIC_LIB_NAME}
# As relative path
STATIC_LIB = $(STATIC_LIB_DIR)/lib$(STATIC_LIB_NAME).a
# ******************************************************************************
LIB_API = ExtremeC_examples_chapter3_2_geometry.h
LIB_SRCS = ExtremeC_examples_chapter3_2_trigon.c \
		  ExtremeC_examples_chapter3_2_2d.c \
		  ExtremeC_examples_chapter3_2_3d.c
LIB_OBJS = $(subst .c,.o,$(LIB_SRCS))
MAIN_SRC = ExtremeC_examples_chapter3_3.c
MAIN_OBJ = $(subst .c,.o,$(MAIN_SRC))
BINARY = $(subst .c,.out,$(MAIN_SRC))

# ******************************************************************************
all:
	@echo "After \"make␣\" Trigger auto completion for available commands."

# ******************************************************************************
# ar command flags:
# c create in case fo update
# r replace
# s create sorted index of relocatable object files
# ******************************************************************************
20_build_static_library: $(STATIC_LIB)

$(STATIC_LIB): $(LIB_OBJS)
	mkdir -p $(@D)
	ar crs $@ $^
	tree .
	@echo "======================================================================"
	@echo -e "==  INFORMATION  ==\nA static library is simply a Unix archive made from the relocatable object files. Such a library is usually linked together with other object files to form an executable object file.\n\nNote that a static library itself is not considered as an object file, rather it is a container for them. In other words, static libraries are not ELF files in Linux systems, nor are they Mach-O files in macOS systems. They are simply archived files that have been created by the Unix ar utility."
	@echo "======================================================================"
	@echo ""

$(LIB_OBJS): %.o: $(VPATH)/%.c $(VPATH)/$(LIB_API)
	$(CC) -c -o $@ $<

# ******************************************************************************
21_listing_the_content_of_the_static_library: $(STATIC_LIB)
	ar -t $(STATIC_LIB)

# ******************************************************************************
30_test_linking_with_new_static_library: $(BINARY)

$(BINARY): $(MAIN_OBJ) $(STATIC_LIB)
	$(CC) -o $@ $< -L$(STATIC_LIB_DIR) -l$(STATIC_LIB_NAME) -lm
	@echo "======================================================================"
	@echo -e "==  INFORMATION  ==\nNote that there will not be any dependency on the existence of the static library file after linking, as everything is embedded inside the executable file itself. In other words, the final executable file can be run on its own without needing the static library to be present.\n\nHowever, executable files produced from the linkage of many static libraries usually have huge sizes. The more static libraries and the more relocatable object files inside them, the bigger the size of the final executable. Sometimes it can go up to several hundred megabytes or even a few gigabytes.\n\nIt is a trade-off between the size of the binary and the dependencies it might have. You can have a smaller binary, but by using shared libraries. It means that the final binary is not complete and cannot be run if the external shared libraries do not exist or cannot be found. We talk more about this in the upcoming sections."
	@echo "======================================================================"
	@echo ""

$(MAIN_OBJ): %.o: $(VPATH)/%.c $(VPATH)/$(LIB_API)
	$(CC) -c -o $@ $<

# ******************************************************************************
31_run_executble: $(BINARY)
	./$(BINARY)

# ******************************************************************************
# Clean up generated files
clean:
	rm -fv *.o *.out
	rm -rv $(RELATIVE_ROOT);

