# ch03-object-files/03_dynamic_lazy_loading/Makefile
# ==============================================================================
# Dynamic Library for LAZY LOADING: ELF Shared Object Files
# ==============================================================================
.PHONY: \
	all \
	2_link_s_o_files_against_dependency_dl \
	40_test_linking_with_new_dynamic_library \
	41_run_executble \
	clean
.DELETE_ON_ERROR:
# ******************************************************************************
CC = gcc
VPATH = ..
# ******************************************************************************
RELATIVE_ROOT = ./opt
DYNAMIC_LIB_NAME = geometry
DYNAMIC_LIB_DIR = $(RELATIVE_ROOT)/$(DYNAMIC_LIB_NAME)
# As relative path
DYNAMIC_LIB = $(DYNAMIC_LIB_DIR)/lib$(DYNAMIC_LIB_NAME).so
# ******************************************************************************
LIB_API = ExtremeC_examples_chapter3_2_geometry.h
LIB_SRCS = ExtremeC_examples_chapter3_2_trigon.c \
		  ExtremeC_examples_chapter3_2_2d.c \
		  ExtremeC_examples_chapter3_2_3d.c
LIB_OBJS = $(subst .c,.o,$(LIB_SRCS))
MAIN_SRC = ExtremeC_examples_chapter3_4.c
MAIN_OBJ = $(subst .c,.o,$(MAIN_SRC))
BINARY = $(subst .c,.out,$(MAIN_SRC))

# ******************************************************************************
all:
	@echo "After \"make␣\" Trigger auto completion for available commands."

# ******************************************************************************
2_link_s_o_files_against_dependency_dl: $(DYNAMIC_LIB)

$(DYNAMIC_LIB): $(LIB_OBJS)
	mkdir -p $(@D)
	$(CC) -shared -o $@ $^ -lm
	tree .
	@echo "======================================================================"
	@echo -e "==  INFORMATION  ==\nLooking at the preceding command, you can see a new option, -lm, which tells the linker to link the shared object file against the standard math library, libm.so. That is done because when we load libgeometry.so manually, its dependencies should, somehow, be loaded automatically. If they're not, then we will get errors about the symbols that are required by libgeometry.so itself, such as cos or sqrt. Note that we won't link the final executable file with the math standard library, and it will be resolved automatically by the loader when loading libgeometry.so."
	@echo "======================================================================"
	@echo ""

# Compile temporary object files as Position Independent Code
$(LIB_OBJS): %.o: $(VPATH)/%.c $(VPATH)/$(LIB_API)
	$(CC) -c -o $@ $< -fPIC

# ******************************************************************************
40_test_linking_with_new_dynamic_library: $(DYNAMIC_LIB) $(BINARY)

# NOTE: Link the final executable with -ldl for dynamic lazy loading
$(BINARY): $(MAIN_OBJ)
	$(CC) -o $@ $< -ldl
	@echo "======================================================================"
	@echo -e "==  INFORMATION  ==\nAs you can see, we did not link the program with the file libgeometry.so. We didn't do this because we want to instead load it manually when it is needed. This method is often referred to as the lazy loading of shared object files. Yet, despite the name, in certain scenarios, lazy loading the shared object files can be really useful.\n\nOne such case is when you have different shared object files for different implementations or versions of the same library. Lazy loading gives you increased freedom to load the desired shared objects according to your own logic and when it is needed, instead of having them automatically loaded at load time, where you have less control over them."
	@echo "======================================================================"
	@echo ""

# Compile main relocatable object file
$(MAIN_OBJ): %.o: $(VPATH)/%.c $(VPATH)/$(LIB_API)
	$(CC) -c -o $@ $<
	@echo "======================================================================"
	@echo -e "==  INFORMATION  ==\nIt is worth noting that the source code must searche for the shared object file in $(DYNAMIC_LIB_DIR), and if there is no such object file, then an error message is shown."
	@echo "======================================================================"
	@echo ""

# ******************************************************************************
41_run_executble: $(DYNAMIC_LIB) $(BINARY)
	./$(BINARY)

# ******************************************************************************
# Clean up generated files
clean:
	rm -fv *.o *.out
	rm -rv $(RELATIVE_ROOT);
