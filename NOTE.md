# Extreme C

## Memory alignment

To perform all its computation which are super fast the CPU needs to optimize its memory access which is slow in comparison. Memory access is made by bit chunks called **word**. Their size is architecture-dependent and for most 64-bit machines is 32 bits or 4 bytes.

When a **User-Defined-DataTypes** (UDTs) or `struct` has a field starting after the preceding field but not at the beginning of a **`word`** and spanning through the beginning of the next memory word, the field is **unaligned**. To optimize memory access the compiler will use a technique called **padding** to pad the preceding field enough for the unaligned field to start at the beginning of a **`word`**.

UDTs can be made **packed** i.e. unpadded by declaring them with:

```c
struct __attribute__((__packed__)) sample {
    // ...
};
```
>**CAUTION**: **Packed struct** may lead to binary incompatibilities and performance degradation.

## Compiling pipeline

### The build pipeline

---

<table border="3">
    <thead>
        <tr>
            <th>Stage</th>
            <th>Sub-Stage</th>
            <th>Tool/Utility</th>
            <th>Input</th>
            <th>Output</th>
            <th>Output Extension</th>
            <th>Command Example</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <th rowspan="2" colspan="2">Preprocessing</th>
            <td colspan="6">Converts source code into a translation unit by expanding macros and all preprocessing directives like <code>#include</code>.</td>
        </tr>
        <tr>
            <td><code>cpp</code>, <code>gcc</code>, <code>clang</code></td>
            <td>Source code (<code>.c</code>, <code>.cpp</code>)</td>
            <td>Preprocessed source code</td>
            <td><code>.i</code>, <code>.ii</code></td>
            <td><code>gcc -E file.c -o file.i</code></td>
        </tr>
        <tr>
            <th rowspan="8">Compilation</th>
            <th rowspan="2">Translation Unit (concept)</th>
            <td colspan="6">A <b>translation unit</b> consists of a single source file and all included headers after preprocessing.</td>
        </tr>
        <tr>
            <td>Preprocessed source code (<code>.i</code>)</td>
            <td>Source file for a single compilation unit</td>
            <td><code>.i</code></td>
            <td>(Generated implicitly during preprocessing)</td>
        </tr>
        <tr>
            <th rowspan="2">Compilation Frontend</th>
            <td colspan="6">Parses the code into an AST, performs semantic checks, and generates an Intermediate Representation (IR).</td>
        </tr>
        <tr>
            <td>Integrated in gcc/clang</td>
            <td>Preprocessed code (<code>.i</code>, <code>.ii</code>)</td>
            <td>Intermediate Representation (IR) or AST</td>
            <td>None</td>
            <td>(Internal step, no separate tool)</td>
        </tr>
        <tr>
            <th rowspan="2">AST Generation (concept)</th>
            <td colspan="6">Conherts source code into an AST, representing the syntax and structure of the program.</td>
        </tr>
        <tr>
            <td><code>clang</code></td>
            <td>Preprocessed source code (<code>.i</code>)</td>
            <td>Abstract Syntax Tree (AST)</td>
            <td>None</td>
            <td><code>clang -Xclang -ast-dump -fsyntax-only file.c</code></td>
        </tr>
        <tr>
            <th rowspan="2">Compilation Backend</th>
            <td colspan="6">Converts preprocessed code (or IR/AST) to architecture-specific assembly code.</td>
        </tr>
        <tr>
            <td><code>gcc</code>, <code>clang</code></td>
            <td>AST or IR</td>
            <td>Assembly code</td>
            <td><code>.s</code></td>
            <td><code>gcc -S file.c -o file.s</code></td>
        </tr>
        <tr>
            <th rowspan="5">Assembly</th>
            <th rowspan="3">Assembly Generation</th>
            <td colspan="6">Includes relocation information and converts assembly to machine code in a file called <b>relocatable or intermediate object files</b> (example format: ELF).</td>
        </tr>
        <tr>
            <td rowspan="2"><code>as</code>, <code>nasm</code></td>
            <td rowspan="2">Assembly code (<code>.s</code>)</td>
            <td rowspan="2">Relocatable object file</td>
            <td rowspan="2"><code>.o</code></td>
            <td><code>as file.s -o file.o</code></td>
        </tr>
        <tr>
            <td><code>nasm -f elf64 file.s -o file.o</code></td>
        </tr>
        <tr>
            <th rowspan="2">Integrated Assembly</th>
            <td colspan="6">Integrated assembler step in the gcc pipeline.</td>
        </tr>
        <tr>
            <td><code>gcc</code>/<code>clang</code></td>
            <td>Assembly code (<code>.s</code>)</td>
            <td>Relocatable object file</td>
            <td><code>.o</code></td>
            <td><code>gcc -c file.s -o file.o</code></td>
        </tr>
        <tr>
            <th rowspan="4">Linking</th>
            <th rowspan="2">Linking</th>
            <td colspan="6">Combines relocatable object files (and optional static libraries) and resolves symbols to produce the final executable.</td>
        </tr>
        <tr>
            <td><code>ld</code></td>
            <td>Object files (<code>.o</code>) and libraries (<code>.a</code>, <code>.so</code>)</td>
            <td>Executable binary</td>
            <td><code>.out</code> or <code>.exe</code></td>
            <td><code>ld file1.o file2.o -o program</code></td>
        </tr>
        <tr>
            <th rowspan="2">Simplified Linking</th>
            <td colspan="6">Simplified invocation of ld with extra handling for libraries.</td>
        </tr>
        <tr>
            <td><code>gcc</code>/<code>clang</code></td>
            <td>Object files and libraries</td>
            <td>Executable binary</td>
            <td><code>.out</code> or <code>.exe</code></td>
            <td><code>gcc file.o -o program</code></td>
        </tr>
    </tbody>
</table>

---

### Incpecting the Intermediate object files

How to inspect `.o` **relocatable object files** (**ELF** format on linux) or `.out` **executable object files**.

---

<table border="3">
    <thead>
        <tr>
            <th>Methods</th>
            <th>Tool/Utility</th>
            <th>Display</th>
            <th>Command Example</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <th rowspan="2">Symbol Inspection</th>
            <td colspan="6">Displays symbol table, including defined and undefined symbols, their addresses, and types.</td>
        </tr>
        <tr>
            <td><code>nm</code></td>
            <td>List of symbols</td>
            <td><code>nm file.o</code></td>
        </tr>
        <tr>
            <th rowspan="4">ELF File Analysis</th>
            <td colspan="6">Inspects ELF files for headers, section details, symbol tables, and relocation entries.</td>
        </tr>
        <tr>
            <td rowspan="3"><code>readelf</code></td>
            <td rowspan="3">ELF header and sections info</td>
            <td><code>readelf -s file.o</code></td>
        </tr>
        <tr>
            <td><code>readelf -hSl file.o</code></td>
        </tr>
        <tr>
            <td><code>readelf -a file.o</code></td>
        </tr>
        <tr>
            <th rowspan="2">Disassembly</th>
            <td colspan="6">Disassembles binaries, inspects sections, and shows relocation and debugging info.</td>
        </tr>
        <tr>
            <td><code>objdump</code></td>
            <td>Assembly code, relocation entries</td>
            <td><code>objdump -d file.o</code></td>
        </tr>
    </tbody>
</table>

---

## Compilation artifacts

Here’s a comprehensive summary of the possible **artifacts** generated during a build process: **binaries**, **static libraries**, and **dynamic libraries**.

### **Key Differences**

| **Aspect**             | **Binaries**                 | **Static Libraries**          | **Dynamic Libraries**        |
|-------------------------|------------------------------|--------------------------------|-------------------------------|
| **Linking Time**        | Full linking happens upfront.| At compile/link time.         | At runtime (or dynamically). |
| **Dependency**          | No external dependency.      | No runtime dependency.         | Requires the library at runtime. |
| **Size**                | Typically larger.            | N/A (linked into binary).      | Smaller binaries.            |
| **Update Impact**       | Recompile required to update.| Recompile all dependent files.| Updating the library affects all linked programs. |
| **Memory Usage**        | N/A (fully self-contained).  | N/A (bundled in binary).       | Shared across processes.     |

---

### **Practical Use Cases**
1. **Binaries**:
   - Final executable product for direct use.
   - Self-contained for distribution (especially with static linking).

2. **Static Libraries**:
   - Libraries intended for fixed inclusion at compile time.
   - Used when distribution of a single, self-contained binary is required.

3. **Dynamic Libraries**:
   - Ideal for reusable components across multiple programs.
   - Common in modern systems for performance and modularity.

---

## Relocatable Object Files

Ref.: Chapter 03_1

```bash
gcc -c ExtremeC_examples_chapter3_1_funcs.c -o funcs.o
gcc -c ExtremeC_examples_chapter3_1.c -o main.o
```

### **What Are Relocatable Object Files?**
Relocatable object files are intermediate binary files produced by compiling individual source files with the `-c` option in `gcc`. They contain:
1. **Code**: Machine-level instructions for functions in the source file.
2. **Data**: Initial values for global variables.
3. **Symbol Table**: Lists symbols defined in the file and references to external symbols needed for linking.
4. **Relocation Entries**: Metadata for adjusting addresses during the linking phase.

The instructions and symbols within relocatable object files are not assigned their final memory addresses yet, making them **relocatable**.

---

### **Key Observations from ELF File Analysis**

Ref:  **[See `Makefile`](./ch03-object-files/executable/Makefile)**.

```bash
readelf -lSh funcs.o
readelf -lSh main.o

readelf -s funcs.o
readelf -s main.o
```

1. **`ELF Header`:**
   - The file type is `REL (Relocatable file)` and is designed to be linked with other relocatable files to form an executable or shared library.
   - There are no program headers, indicating this file is not executable or directly loadable into memory.

2. **`Section Headers`:**
   - `.text`: Contains the machine-level instructions for the functions defined in the file.
   - `.data` and `.bss`: Represent initialized and uninitialized global variables, respectively.
   - `.rela.text` and `.rela.eh_frame`: Contain relocation information to adjust addresses during linking.

3. **`Symbol Table` (`.symtab`):**
   - **Local Symbols**: Symbols private to the file (e.g., sections or source file metadata).
   - **Global Symbols**: Symbols accessible from other files during linking (e.g., `max`, `max_3` in `funcs.o`, and `main`, `a`, `b` in `main.o`).
   - Undefined symbols (`UND`): Refer to symbols not defined in the current file but required for linking (e.g., `max` and `max_3` in `main.o`).

4. **Relocation and Addressing:**
   - Symbols like `main`, `a`, and `b` have placeholder addresses (`0x0` or offsets in sections) in `main.o`, indicating they will be assigned final addresses during the linking stage.

---

### **Conclusion**
- **Relocatable Object Files**: `funcs.o` and `main.o` are relocatable files generated by compiling individual source files. They are not executable until the linker resolves their symbols and performs relocation.
- **Purpose**: The linker processes these files, resolves undefined symbols, combines sections (e.g., `.text`, `.data`), and assigns final addresses to create a fully linked executable or library.
- **Relocation**: The placeholder addresses and relocation entries in the ELF files confirm their nature as intermediate, relocatable binaries

## Executable Object Files

### **1. Binaries (Executable Object Files)**

| **Feature**              | **Description**                                                                 |
|---------------------------|---------------------------------------------------------------------------------|
| **Definition**            | An **executable binary** is a file containing machine code that can be directly run by the operating system. |
| **Produced By**           | **Linking** stage of the build process, combining multiple object files and resolving symbols. |
| **File Extensions**       | `.out` (Linux default), `.exe` (Windows).                                      |
| **Characteristics**       | - Fully self-contained; includes all necessary code and data to execute.       |
|                           | - Contains headers (e.g., ELF, PE) to inform the OS how to load and run it.    |
| **Advantages**            | - Easy to distribute and execute without dependencies.                        |
|                           | - No runtime linking or external requirements.                                |
| **Disadvantages**         | - Larger file size if static linking is used.                                 |
| **Creation Command**      | `gcc file.o -o executable_name`                                                |
| **Key Tools**             | `nm`, `readelf`, `objdump` (for analysis).                                    |

---

### Content

Ref:  **[See `Makefile`](./ch03-object-files/executable/Makefile)**.

```bash
gcc -c main.o funcs.o -o ex3_1.out

readelf -lSh ex3_1.out
```

Let’s break down **rows 01 to 06** in the *"Section to Segment mapping:"* of the last command output.

---

#### **Row 01: INTERP Segment**

- **Segment Type**: This maps to the `.interp` section, which contains the **interpreter path** (e.g., `/lib64/ld-linux-x86-64.so.2`).  
- **Purpose**:  
  - The loader program (dynamic linker) reads this segment to determine which program should load and execute the binary.
  - This segment is required for position-independent executables (PIE) and dynamically linked executables.
- **File Properties**:  
  - It has a **R (read)** flag since it is read-only.  
  - It is **not executable or writable**.

---

#### **Row 02: LOAD Segment for Metadata and Relocations**

- **Sections Included**:  
  `.interp`, `.note.gnu.property`, `.note.gnu.build-id`, `.note.ABI-tag`, `.gnu.hash`, `.dynsym`, `.dynstr`, `.gnu.version`, `.gnu.version_r`, `.rela.dyn`
- **Purpose**:  
  - This segment includes metadata used by the dynamic linker to resolve symbols and manage dynamic linking.  
  - Examples:
    - `.gnu.hash`, `.dynsym`, `.dynstr`: Symbol tables and string tables for dynamic linking.
    - `.rela.dyn`: Relocation information to patch addresses during dynamic linking.
    - `.note.*`: Various notes, such as build ID or ABI compatibility information.
- **File Properties**:  
  - **R (read)** flag since it contains data required for linking and relocation.  
  - **Not executable**, as it doesn't contain any code.

---

#### **Row 03: LOAD Segment for Executable Code**

- **Sections Included**:  
  `.init`, `.plt`, `.plt.got`, `.text`, `.fini`
- **Purpose**:  
  - This segment contains **executable code** and stubs required for function calls.
  - Examples:
    - `.text`: Contains the main program's compiled machine code.
    - `.plt`, `.plt.got`: Used for dynamic function calls through the Procedure Linkage Table (PLT).
    - `.init`/`.fini`: Contain initialization and cleanup routines.
- **File Properties**:  
  - **R (read)** and **E (execute)** flags since it contains executable machine instructions.  
  - **Not writable** to prevent code modification during execution.

---

#### **Row 04: LOAD Segment for Read-Only Data**

- **Sections Included**:  
  `.rodata`, `.eh_frame_hdr`, `.eh_frame`
- **Purpose**:  
  - This segment contains **read-only data** used by the program.
  - Examples:
    - `.rodata`: Read-only constants such as string literals.
    - `.eh_frame` and `.eh_frame_hdr`: Exception handling and stack unwinding metadata for C++ and other languages.
- **File Properties**:  
  - **R (read)** flag since it only contains data.  
  - **Not executable or writable**.

---

#### **Row 05: LOAD Segment for Writable Data and BSS**

- **Sections Included**:  
  `.init_array`, `.fini_array`, `.dynamic`, `.got`, `.data`, `.bss`
- **Purpose**:  
  - This segment contains writable and runtime-initialized data.
  - Examples:
    - `.data`: Global and static variables initialized in the program.
    - `.bss`: Uninitialized global and static variables, which are zeroed at runtime.
    - `.got`: Global Offset Table, used for position-independent addressing.
    - `.init_array` and `.fini_array`: Pointers to functions that run during initialization and cleanup phases.
- **File Properties**:  
  - **R (read)** and **W (write)** flags since the program writes to this data at runtime.  
  - **Not executable**.

---

#### **Row 06: DYNAMIC Segment**

- **Sections Included**:  
  `.dynamic`
- **Purpose**:  
  - This segment contains dynamic linking information used by the dynamic loader.
  - The `.dynamic` section provides tables and pointers that guide the loader in resolving symbols and managing shared libraries.
  - Example contents:  
    - Paths to needed shared libraries.
    - Addresses of PLT and GOT.
    - Relocation information.
- **File Properties**:  
  - **R (read)** and **W (write)** flags since dynamic linking may modify some entries during execution (e.g., runtime symbol resolution).  
  - **Not executable**.

---

#### **Summary**

These rows describe how the ELF executable's **sections** map into **segments** for the loader to process during execution. Each segment has a distinct purpose: some contain executable code, others contain metadata, and some contain runtime-writable data. The properties of these segments (e.g., `R`, `W`, `X`) are critical for ensuring correct program execution and maintaining security (e.g., by preventing code from being writable).

### Symbols

Ref:  **[ex3_1.out content](./ch03-object-files/executable/read_s_exe.txt)**. 

As you see in the preceding shell box, we have two different symbol tables in an executable object file. The first one, `.dynsym`, contains the symbols that should be resolved when loading the executable, but the second symbol table, `.symtab`, contains all the resolved symbols together with unresolved symbols brought from the dynamic symbol table. In other words, the symbol table contains the unresolved symbols from the dynamic table as well.

As you see, the resolved symbols in the symbol table have absolute corresponding addresses that they have obtained after the linking step. The addresses for `max` and `max_3` symbols are shown in bold font.

## Static Libraries

Ref:  **[See `Makefile`](./ch03-object-files/static/Makefile)**.

### Building and usage

```bash
# Compiling source files to relocatable object files
gcc -c ExtremeC_examples_chapter3_2_trigon.c -o trigon.o
gcc -c ExtremeC_examples_chapter3_2_2d.c -o 2d.o
gcc -c ExtremeC_examples_chapter3_2_3d.c -o 3d.o
```
Reading the manual for `ar` helps but I will explain it in more detail. `ar -rcs` is the most likely command you would use when using a `Makefile` to compile a library. `r` means that if the library already exists, replace the old files within the library with your new files. `c` means create the library if it did not exist. `s` can be seen to mean 'sort' (create a sorted index of) the library, so that it will be indexed and faster to access the functions in the library. Therefore, `rcs` can be seen to mean `replace, create, sort`

```bash
# Creating the static library file
ar crs libgeometry.a trigon.o 2d.o 3d.o
# optionally
mkdir -p /opt/ geometry
mv libgeometry.a /opt/ geometry

# Listing the content of the static library file
ar t /opt/ geometry/ libgeometry.a
```
```bash
gcc -c ExtremeC_examples_chapter3_3. c -o main.o

gcc main.o -L./opt/geometry -lgeometry -lm -o ex3_3.out
```

### **2. Static Libraries (Archived Relocatable Object Files)**

| **Feature**              | **Description**                                                                 |
|---------------------------|---------------------------------------------------------------------------------|
| **Definition**            | A **static library** is a collection of object files bundled into a single archive file, used at compile/link time. |
| **Produced By**           | Using the `ar` utility to combine object files.                                |
| **File Extensions**       | `.a` (Linux), `.lib` (Windows).                                                |
| **Characteristics**       | - Bundled object files; functions are copied into the executable during linking. |
|                           | - No dependencies on the library at runtime.                                  |
| **Advantages**            | - Faster execution as all code is linked into the executable.                 |
|                           | - No runtime library dependencies.                                            |
| **Disadvantages**         | - Larger executables because code is duplicated in each linked binary.        |
|                           | - Updating the library requires recompiling all linked binaries.              |
| **Creation Command**      | `ar rcs libname.a file1.o file2.o`                                             |
| **Usage in Compilation**  | `gcc main.c -L. -lname -o program` (use `-L` to specify the library path).     |
| **Key Tools**             | `ar`, `nm`, `ranlib`.                                                         |

---

## Dynamic Libraries

### **Dynamic Libraries (Shared Object Files)**

Ref:  **[See `Makefile`](./ch03-object-files/dynamic/Makefile)**.

| **Feature**              | **Description**                                                                 |
|---------------------------|---------------------------------------------------------------------------------|
| **Definition**            | A **dynamic library** (shared object) is a file containing reusable machine code that is loaded at runtime by the dynamic linker. |
| **Produced By**           | Compiling with the `-fPIC` and `-shared` options for position-independent code. |
| **File Extensions**       | `.so` (Linux), `.dll` (Windows), `.dylib` (macOS).                              |
| **Characteristics**       | - Functions are loaded into memory and linked when the program starts or on-demand. |
|                           | - Multiple programs can share the same library in memory.                      |
| **Advantages**            | - Smaller executables as the code resides in a separate library file.          |
|                           | - Easy to update: replacing the library automatically updates all binaries using it. |
| **Disadvantages**         | - Runtime dependency: the executable won't work without the shared library.    |
|                           | - Slightly slower startup time due to dynamic linking overhead.                |
| **Creation Command**      | - Source files must be assembled as **Position Independent Code**               |
|                           | `gcc -c <each_source_file>.c -fPIC -o <relocatable_file>.o`                         |
|                           | `gcc -shared <all_relocatable_files>.o -o libname.so`                              |
| **Usage in Compilation**  | - **Make `-L<path_to_dylib>` does not contain other dynamic or static library** |
|                           | `gcc main.c -L. -lname -o program` (use `-L` for library path).                |
|                           | Run with `LD_LIBRARY_PATH` if the shared library isn't in the default path.    |
| **Key Tools**             | `ldd` (list shared dependencies), `nm`, `readelf`.                             |

---

### **Dynamic Libraries with Lazy Loading (`dlopen` API)**

Ref:  **[See `Makefile`](./ch03-object-files/lazy_loading/Makefile)**.

| **Feature**              | **Description**                                                                                  |
|---------------------------|--------------------------------------------------------------------------------------------------|
| **Definition**            | Dynamic libraries loaded at runtime **on-demand** using the `dlfcn.h` API (`dlopen`, `dlsym`, etc.). |
| **Produced By**           | Compiling source files into position-independent code with `-fPIC` and linking with `-shared`.   |
| **File Extensions**       | `.so` (Linux), `.dll` (Windows), `.dylib` (macOS).                                              |
| **Characteristics**       | - Functions and symbols are resolved only when explicitly requested by the program.             |
|                           | - Allows greater runtime flexibility compared to standard dynamic linking.                      |
| **Advantages**            | - **Selective Loading**: Only necessary symbols are loaded, saving memory and improving performance. |
|                           | - **Error Handling**: The program can gracefully handle missing or failing libraries.           |
|                           | - **Versioning**: Allows runtime decisions about which version of the library to load.          |
| **Disadvantages**         | - Adds programming complexity due to manual handling of library loading and symbol resolution.  |
|                           | - Slight runtime performance hit for symbol resolution via `dlsym`.                             |
| **Creation Command**      | - Compile each source file as **Position Independent Code**                                      |
|                           |   `gcc -c <source_file>.c -fPIC -o <object_file>.o`                                             |
| **KEY DIFFERENCE**        | - **Shared library for lazy loading must be linked with any library eventually required by the .so at run time**|
|                           |   `gcc -shared <all_object_files>.o [-llibraries] -o libname.so`                                          |
| **Program Usage**         | - Compile the executable with the `-ldl` flag (linker option for dynamic linking).            |
|                           |   `gcc main.c -ldl -o program`                                                                  |
| **Key Functions (API)**   | - `dlopen`: Opens the dynamic library.                                                          |
|                           | - `dlsym`: Resolves and retrieves a symbol (e.g., a function or variable).                      |
|                           | - `dlerror`: Retrieves error messages related to `dlopen` and `dlsym`.                          |
|                           | - `dlclose`: Unloads the library from memory.                                                   |
| **Key Tools**             | - `ldd` (list shared dependencies), `nm`, `readelf`.                                           |

---

### **Command to Compile and Run**
```bash
# Compile the shared library
gcc -c 2d.c 3d.c trigon.c -fPIC -o libgeometry.so
gcc -shared 2d.o 3d.o trigon.o -lm -o libgeometry.so

# Compile the main program with dlopen API
gcc main.c -ldl -o ex3_4.out
```

This table and example illustrate the usage and benefits of lazy loading dynamic libraries in a Linux environment
