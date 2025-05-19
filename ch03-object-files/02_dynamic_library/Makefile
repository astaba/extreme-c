# ch03-object-files/02_dynamic_library/Makefile
# ==============================================================================
# Dynamic Library: ELF Shared Object Files
# ==============================================================================
.PHONY: \
	all \
	2_link_s_o_files \
	30_test_linking_with_new_dynamic_library \
	31_test_running_failure \
	32_run_executble \
	clean
.DELETE_ON_ERROR:
# ******************************************************************************
CC = gcc
VPATH= ..
# ******************************************************************************
RELATIVE_ROOT = ./opt
DYNAMIC_LIB_NAME = geometry
DYNAMIC_LIB_DIR = $(RELATIVE_ROOT)/${DYNAMIC_LIB_NAME}
# As relative path
DYNAMIC_LIB = $(DYNAMIC_LIB_DIR)/lib$(DYNAMIC_LIB_NAME).so
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
2_link_s_o_files: $(DYNAMIC_LIB)

# Build the dynamic library as an ELF shared object file
$(DYNAMIC_LIB): $(LIB_OBJS)
	mkdir -p $(@D)
	$(CC) -shared -o $@ $^
	tree .
	@echo ""
	@echo "======================================================================"
	@echo -e "==  INFORMATION  ==\nLooking at the commands, you can see that we have passed an extra option,-fPIC, to gcc while compiling the sources. This option is mandatory if you are going to create a shared object file out of some relocatable object files. PIC stands for position independent code. As we explained before, if a relocatable object file is position independent, it simply means that the instructions within it don't have fixed addresses. Instead, they have relative addresses; hence they can obtain different addresses in different processes.\n\nThis is a requirement because of the way we use shared object files. There is no guarantee that the loader program will load a shared object file at the same address in different processes. In fact, the loader creates memory mappings to the shared object files, and the address ranges for those mappings can be different. If the instruction addresses were absolute, we couldn't load the same shared object file in various processes, and in various memory regions, at the same time."
	@echo "======================================================================"
	@echo ""
	@echo -e "==  INFORMATION  ==\nUnlike a static library file, which is a simple archive, a shared object file is an object file itself. Therefore, they should be created by the same linker program, for instance ld, that we used to produce the relocatable object files. However, it is strongly recommended not to use it directly but to let gcc deal with it."
	@echo "======================================================================"

# Compile temporary object files as Position Independent Code
$(LIB_OBJS): %.o: $(VPATH)/%.c $(VPATH)/$(LIB_API)
	$(CC) -c -o $@ $< -fPIC

# ******************************************************************************
30_test_linking_with_new_dynamic_library: $(BINARY)

$(BINARY): $(MAIN_OBJ) $(DYNAMIC_LIB)
	$(CC) -o $@ $<  -L$(DYNAMIC_LIB_DIR) -l$(DYNAMIC_LIB_NAME) -lm
	@echo ""
	@echo "======================================================================"
	@echo -e "==  INFORMATION  ==\nBy linking an executable with several shared object files, as we did before, we tell the system that this executable file needs a number of shared libraries to be found and loaded at runtime. Therefore, before running the executable, the loader searches for those shared object files automatically, and the required symbols are mapped to the proper addresses that are accessible by the process. Only then can the processor begin the execution."
	@echo "======================================================================"

$(MAIN_OBJ): %.o: $(VPATH)/%.c $(VPATH)/$(LIB_API)
	$(CC) -c -o $@ $<

# ******************************************************************************
31_test_running_failure: $(BINARY)
	@echo "======================================================================"
	@echo -e "==  WARNING  ==\nThe $(BINARY) executable file depends on libgeometry.so. That's because some of the definitions it needs can only be found inside that shared object file. We should note that this is not true for the static library libgeometry.a. An executable file linked with a static library can be run on its own as a standalone executable, since it has copied everything from the static library file, and therefore, doesn't rely on its existence anymore.\n\nThis is not true for the shared object files. We received the error because the program loader (dynamic linker) could not find libgeometry.so in its default search paths. Therefore, we need to add $(DYNAMIC_LIB_DIR) to its search paths, so that it finds the libgeometry.so file there. To do this, we will update the environment variable LD_LIBRARY_PATH to point to the current directory.\n\nexport LD_LIBRARY_PATH=<library_path>:$LD_LIBRARY_PATH\n./$(BINARY)\n\nOr directely on the prompt.\n\nLD_LIBRARY_PATH=\"$$PWD/$(DYNAMIC_LIB_DIR):$$LD_LIBRARY_PATH\" ./$(BINARY)"
	@echo "======================================================================"
	@echo ""
	./$(BINARY)

# ******************************************************************************
32_run_executble: $(BINARY)
	LD_LIBRARY_PATH="$(DYNAMIC_LIB_DIR):$$LD_LIBRARY_PATH" ./$(BINARY)

# ******************************************************************************
# Clean up generated files
clean:
	rm -fv *.o *.out
	rm -rv $(RELATIVE_ROOT);
