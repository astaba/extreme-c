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

