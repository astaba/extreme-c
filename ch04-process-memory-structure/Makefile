# ch04-process-memory-structure/Makefile
# ==============================================================================
# PROCESS MEMORY STRUCTURE
# ==============================================================================
# ● Static memory layout: Hard set in executable ELF:
# 	• BSS segment: Global variables with 0 or no init value. Dynamic update.
# 	  (Block Started by Symbols)
# 	• Data segment: Initialized global variables. Dynamic update.
# 	• Text segment: Program instructions. Purely static.
# ● Dynamic memory layout: Spawn at run time by the system:
# 	• Stack segment: Function calls turn over and local variables. Dynamic.
# 	• Heap segment: Dynamically allocated memory. Dynamic.
# ==============================================================================
.PHONY: \
	all \
	1_static_memory_layout \
	2_BSS_segment \
	30_data_segment \
	31_NOTE_static_variables_in_functions \
	4_data_segment_content \
	5_text_segment \
	60_NOTE_dynamic_or_static \
	61_PROCEDURE_stack_memory_mapping \
	62_EXPLANATION_memory_mapping \
	63_NOTE_stack_segment \
	7_PROCEDURE_heap_memory_mapping \
	8_pointers_to_interact_with_the_heap \
	clean
.DELETE_ON_ERROR:
# ******************************************************************************
CC       = gcc
GDBFLAGS = -g3 -O0 -DDEBUG
# ******************************************************************************
SOURCES  = $(wildcard *.c)
_SOURCES = $(subst ExtremeC_examples_chapter,ex,$(SOURCES))
BINARIES = $(subst .c,.out,$(_SOURCES))
# ******************************************************************************
all:
	@echo "After \"make␣\" Trigger auto completion for available commands."

# ******************************************************************************
# PROBING THE STATIC MEMORY LAYOUT
# ******************************************************************************
1_static_memory_layout: $(word 1,$(BINARIES))
	@echo "======================================================================"
	@echo -e "==  EXPLANATION  ==\nStatic and dynamic memory layouts both have a predetermined set of segments. The content of the static memory layout is prewritten into the executable object file by the compiler, when compiling the source code. On the other hand, the content of the dynamic memory layout is written by the process instructions allocating memory for variables and arrays, and modifying them according to the program's logic.\n\nThe size command is the first tool that we want to introduce. It can be used to print the static memory layout of an executable object file."
	@echo "======================================================================"
	@echo ""
	size $(word 1,$(BINARIES))
	@echo ""
	@echo "======================================================================"
	@echo -e "==  EXPLANATION  ==\nAs you see, we have Text, Data, and BSS segments as part of the static layout. The shown sizes are in bytes.\n\nUsing the size command on a Microsoft System we would have:\n\n>size ex4_1-ms.exe\n>\ttext    data   bss   dec     hex    filename\n>\t10264   2572   384   13220   33a4   ex4_1-ms.exe\n\nDespite these little differences between Linux and MS, we can see that both platforms have the Text, Data, and BSS segments as part of their static layout. From now on, we gradually explain what each of these segments are used for. In the upcoming sections, we'll discuss each segment separately and we give an example slightly different from example 4.1 for each, in order to see how differently each segment responds to the minor changes in the code."
	@echo "======================================================================"

# ******************************************************************************
2_BSS_segment: $(word 1,$(BINARIES)) $(word 2,$(BINARIES))
	size $(word 1,$(BINARIES))
	size $(word 2,$(BINARIES))
	@echo ""
	@echo "======================================================================"
	@echo -e "==  EXPLANATION  ==\nIf you compare the preceding output with a similar output from example 4.1, you will notice that the size of the BSS segment has changed. In C, global and static variables initialized to 0 are treated the same as uninitialized variables — they go into .bss segment. These special global variables are part of the static layout and they become preallocated when a process is loading, and they never get deallocated until the process is alive. In other words, they have a static lifetime.\n\nNOTE:\nBecause of design concerns, we usually prefer to use local variables in our algorithms. Having too many global variables can increase the binary size. In addition, keeping sensitive data in the global scope, it can introduce security concerns. Concurrency issues, especially data races, namespace pollution, unknown ownership, and having too many variables in the global scope, are some of the complications that global variables introduce.\n\nHACK: If you want to see exact memory layout compile with debug infoand use:\n\n\treadelf -S ExtremeC_examples_chapter4_2.out\nor\n\tobjdump -t ExtremeC_examples_chapter4_2.out"
	@echo "======================================================================"

# ******************************************************************************
30_data_segment: $(word 3,$(BINARIES))
	size $(word 3,$(BINARIES))
	@echo ""
	@echo "======================================================================"
	@echo -e "==  EXPLANATION  ==\nWe know that the Data segment is used to store the initialized global variables set to a non-zero value. If you compare the output of the size command for examples 4.2 and 4.3, you can easily see that the Data segment is increased by 9 bytes, which is the sum of the sizes of the two newly added global variables (one 8-byte double and one 1-byte char)."
	@echo "======================================================================"

31_NOTE_static_variables_in_functions:
	@echo "======================================================================"
	@echo -e "==  INFORMATION  ==\nOther than global variables, we can have some static variables declared inside a function. These variables retain their values while calling the same function multiple times. These variables can be stored either in the Data segment or the BSS segment depending on the platform and whether they are initialized or not. The following code box demonstrates how to declare some static variables within a function:\n\n\tvoid func() {\n\t\tstatic int i;\n\t\tstatic int j = 1;\n\t\t...\n\t}\n\nAs you see in Code Box 4-4, the i and j variables are static. The i variable is uninitialized and the j variable is initialized with value 1. It doesn't matter how many times you enter and leave the func function, these variables keep their most recent values.\n\nTo elaborate more on how this is done, at runtime, the func function has access to these variables located in either the Data segment or the BSS segment, which has a static lifetime. That's basically why these variables are called static. We know that the j variable is located in the Data segment simply because it has an initial value, and the i variable is supposed to be inside the BSS segment since it is not initialized."
	@echo "======================================================================"

# ******************************************************************************
4_data_segment_content: $(word 4,$(BINARIES))
	objdump -s -j .data $(word 4,$(BINARIES))
	@echo "======================================================================"
	readelf -x .data $(word 4,$(BINARIES))
	@echo ""
	@echo "======================================================================"
	@echo -e "==  EXPLANATION  ==\nLet's explain how the preceding output, and especially the contents of the section .data, should be read. The first column on the left is the address column. The next four columns are the contents, and each of them is showing 4 bytes of data. So, in each row, we have the contents of 16 bytes. The last column on the right shows the ASCII representation of the same bytes shown in the middle columns. A dot character means that the character cannot be shown using alphanumerical characters. Note that the option -s tells objdump to show the full content of thechosen section and the option -j .data tells it to show the content of the section .data.\n\nThe first line is 16 bytes filled by zeros. There is no variable stored here, so nothing special for us. The second line shows the contents of the Data segment starting with the address 0x601030. The first 4 bytes is the value stored in the x variable found in example 4.4. The next 4 bytes also contain the value for the y variable. The final 6 bytes are the characters inside the z array. The contents of z can be clearly seen in the last column.\n\nIf you pay enough attention to the content shown in Shell Box 4-9, you see that despite the fact that we write 33, in decimal base, as 0x00000021, in hexadecimal base it is stored differently in the segment. It is stored as 0x21000000. This is also true for the content of the y variable. We have written it as 0x12153467, but it is stored differently as 0x67341512. It seems that the order of bytes is reversed.\n\nThe effect explained is because of the endianness concept. Generally, we have two different types of endianness, big-endian and little-endian. The value 0x12153467 is the big-endian representation for the number 0x12153467, as the biggest byte, 0x12, comes first. But the value 0x67341512 is the little-endian representation for the number 0x12153467, as the smallest byte, 0x67, comes first.\n\nNo matter what the endianness is, we always read the correct value in C. Endianness is a property of the CPU and with a different CPU you may get a different byte order in your final object files. This is one of the reasons why you cannot run an executable object file on hardware with different endianness."
	@echo "======================================================================"

# ******************************************************************************
5_text_segment: $(word 5,$(BINARIES))
	objdump -S $(word 5,$(BINARIES))
	@echo ""
	@echo "======================================================================"
	@echo -e "==  EXPLANATION  ==\nSince the Text segment, or the Code segment, contains all the machine-level instructions of a program, it should be located in the executable object file, as part of its static memory layout. These instructions are fetched by the processor and get executed at runtime when the process is running.\n\nAs you see in the preceding shell box, there are various sections containing machine-level instructions: the .text, .init, and .plt sections and some others, which all together allow a program to become loaded and running. All of these sections are part of the same Text segment found in the static memory layout, inside the executable object file.\n\nOur C program, written for example 4.5, had only one function, the main function, but as you see, the final executable object file has a dozen other functions.\n\nThe preceding output, seen as part of Shell Box 4-11, shows that the main function is not the first function to be called in a C program and there are logics before and after main that should be executed. As explained in Chapter 2, Compilation and Linking, in Linux, these functions are usually borrowed from the glibc library, and they are put together by the linker to form the final executable object file."
	@echo "======================================================================"

# ******************************************************************************
# PROBING THE DYNAMIC MEMORY LAYOUT
# ******************************************************************************
60_NOTE_dynamic_or_static:
	@echo "======================================================================"
	@echo -e "==  INFORMATION  ==\nThe dynamic memory layout is actually the runtime memory of a process, and it exists as long as the process is running. When you execute an executable object file, a program called loader takes care of the execution. It spawns a new process and it creates the initial memory layout which is supposed to be dynamic. To form this layout, the segments found in the static layout will be copied from the executable object file. More than that, two new segments will also be added to it. Only then can the process proceed and become running.\n\n In short, we expect to have five segments in the memory layout of a running process. Three of these segments are directly copied from the static layout found in the executable object file. The two newly added segments are called Stack and Heap segments. These segments are dynamic, and they exist only when the process is running. This means that you cannot find any trace of them as part of the executable object file.\n\nFrom time to time, we might refer to these segments as the process's dynamic memory layout, without considering the other three segments copied from the object file, but you should always remember that the dynamic memory of a process consists of all five segments together.\n\n The five segments found in the dynamic memory of a process are referring to parts of the main memory that are already allocated, dedicated, and private to a running process. These segments, excluding the Text segment, which is literally static and constant, are dynamic in a sense that their contents are always changing at runtime. That's due to the fact that these segments are constantly being modified by the algorithm that the process is executing."
	@echo "======================================================================"
	@echo ""

# ******************************************************************************
61_PROCEDURE_stack_memory_mapping: $(word 6,$(BINARIES))
	@echo "======================================================================"
	@echo -e "==  PROCEDURE  ==\nFirst, running the inifinite loop in example4_6 in the background of the shell (with &) gives you all the time to probe the memory structure. Of course, don't forget to kill it when you are done with the inspection\n\nThen open the /proc folder which is not an ordinary filesystem in Unix-like operating system, but rather a hierarchical interface to query about individual process on the system as a whole. Knowing the process id you can explore its interface with:\n\n# ls -l /proc/PID\n\nFor querying the memory mappings of the process, we have to see the contents of the file maps under the PID directory. We use the cat command to dump the contents of the /proc/PID/maps file:\n\n# cat /proc/PID/maps\n\nNow to have explanation about the mapping run command 62 in the Makefile and when the inspection in over kill the process:\n\n#kill -9 PID"
	@echo "======================================================================"
	@echo ""

# ******************************************************************************
62_EXPLANATION_memory_mapping:
	@echo "======================================================================"
	@echo -e "==  EXPLANATION  ==\nAs you see in the cat command output, the result consists of a number of rows. Each row represents a memory mapping that indicates a range of memory addresses (a region) that are allocated and mapped to a specific file or segment in the dynamic memory layout of the process. Each mapping has a number of fields separated by one or more spaces. Next, you can find the descriptions of these fields from left to right:\n\n ● Address range: These are the start and end addresses of the mapped range. You can find a file path in front of them if the region is mapped to a file. This is a smart way to map the same loaded shared object file in various processes. We have talked about this as part of Chapter 3, Object Files.\n\n ● Permissions: This indicates whether the content can be executed (x), read (r), or modified (w). The region can also be shared (s) by the other processes or be private (p) only to the owning process.\n\n ● Offset: If the region is mapped to a file, this is the offset from the beginning of the file. It is usually 0 if the region is not mapped to a file.\n\n ● Device: If the region is mapped to a file, this would be the device number (in the form of m:n), indicating a device that contains the mapped file. For example, this would be the device number of the hard disk that contains a shared object file.\n\n ● The inode: If the region is mapped to a file, that file should reside on a filesystem. Then, this field would be the inode number of the file in that filesystem. An inode is an abstract concept within filesystems such as ext4 which are mostly used in Unix-like operating systems. Each inode can represent both files and directories. Every inode has a number that is used to access its content.\n\n ● Pathname or description: If the region is mapped to a file, this would be the path to that file. Otherwise, it would be left empty, or it would describe the purpose of the region. For example, [stack] indicates that the region is actually the Stack segment."
	@echo "======================================================================"
	@echo ""

# ******************************************************************************
63_NOTE_stack_segment:
	@echo "======================================================================"
	@echo -e "==  EXPLANATION  ==\nThe Stack segment is a key part of a process's dynamic memory, mainly used for local variables and managing function calls. It operates as a Last In, First Out (LIFO) structure, with each function call pushing a new stack frame to store return addresses and local data. Because of its limited size, it's best suited for small, short-lived variables—excessive use, such as from deep recursion, can cause a stack overflow and crash the program.\n\nUnlike static memory, the Stack changes constantly at runtime and is private to each process, making it hard to inspect without tools like \`gdb\`. Its sensitive role means careful management is crucial, as corruption can lead to serious failures. Further inspection and use of debugging tools will be discussed after introducing the Heap segment."
	@echo "======================================================================"
	@echo ""

# ******************************************************************************
7_PROCEDURE_heap_memory_mapping: $(word 7,$(BINARIES))
	@echo "======================================================================"
	@echo -e "==  PROCEDURE  ==\nProceed just like in command 61 of the Makefile. Run in background and dump the /proc/PID/maps with cat. If necessary run command 62 for explanation.\n\nYou will notice in the mapping a new segment called haep and and that its memory range encompasses the memory address print out by the running process.This region has been added because of using the malloc() function. If you calculate the size of the region, it is 0x21000 bytes or 132 KB. This means that to allocate only 1 KB in the code, a region of the size 132 KB has been allocated. This is usually done in order to prevent further memory allocations when using malloc again in the future. That's simply because the memory allocation from the Heap segment is not cheap and it has both memory and time overheads.\n\nThen KILL the process."
	@echo "======================================================================"
	@echo ""

# ******************************************************************************
8_pointers_to_interact_with_the_heap: $(word 8,$(BINARIES))
	cat $(word 8,$(SOURCES))
	@echo "======================================================================"
	./$(word 8,$(BINARIES))
	@echo "======================================================================"
	@echo -e "==  INFORMATION  ==\nNote that the local pointer variables, gptr and ptr, are allocated from the Stack. These pointers need memory to store their values, and this memory comes from the Stack segment. But the address that they are pointing to is inside the Heap segment. This is the theme when working with Heap memories. You have local pointers which are allocated from the Stack segment, but they are actually pointing to a region allocated from the Heap segment. We show more of these in the following chapter.\n\nNote that the ptr pointer inside the fill function is also allocated from the Stack but it is in a different scope, and it is different from the ptr pointer declared in the main function.\n\nWhen it comes to Heap memory, the program, or actually the programmer, is responsible for memory allocation. The program is also responsible for deallocation of the memory when it is not needed. Having a piece of allocated Heap memory that is not reachable is considered a memory leak. By not being reachable, we mean that there is no pointer that can be used to address that region."
	@echo "======================================================================"
	@echo ""

# ******************************************************************************
$(word 1,$(BINARIES)): $(word 1,$(SOURCES))
	$(CC) $(GDBFLAGS) -o $@ $<
$(word 2,$(BINARIES)): $(word 2,$(SOURCES))
	$(CC) $(GDBFLAGS) -o $@ $<
$(word 3,$(BINARIES)): $(word 3,$(SOURCES))
	$(CC) $(GDBFLAGS) -o $@ $<
$(word 4,$(BINARIES)): $(word 4,$(SOURCES))
	$(CC) $(GDBFLAGS) -o $@ $<
$(word 5,$(BINARIES)): $(word 5,$(SOURCES))
	$(CC) $(GDBFLAGS) -o $@ $<
$(word 6,$(BINARIES)): $(word 6,$(SOURCES))
	$(CC) $(GDBFLAGS) -o $@ $<
$(word 7,$(BINARIES)): $(word 7,$(SOURCES))
	$(CC) $(GDBFLAGS) -o $@ $<
$(word 8,$(BINARIES)): $(word 8,$(SOURCES))
	$(CC) $(GDBFLAGS) -o $@ $<

# ******************************************************************************
# Clean target to remove built files
clean:
	@rm -fv *.out
