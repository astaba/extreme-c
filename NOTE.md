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

### **3. Dynamic Libraries (Shared Object Files)**

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
| **Creation Command**      | `gcc -shared -fPIC -o libname.so file1.o file2.o`                               |
| **Usage in Compilation**  | `gcc main.c -L. -lname -o program` (use `-L` for library path).                |
|                           | Run with `LD_LIBRARY_PATH` if the shared library isn't in the default path.    |
| **Key Tools**             | `ldd` (list shared dependencies), `nm`, `readelf`.                             |

---

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
