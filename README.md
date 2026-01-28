# DynamicArray

A high-performance, generic **Dynamic Array** implementation in C++. This library offers automatic resizing, custom iterator support, robust binary serialization, and an advanced **Introsort** algorithm.

## 📖 Overview

**DynamicArray** is a C++ template library designed to mimic `std::vector` while adding built-in persistence and optimized sorting. [cite_start]It uses `std::unique_ptr` for safe memory management [cite: 68] [cite_start]and implements the "Rule of Five" to handle deep copying and move semantics correctly [cite: 78-88].

### Key Features
* **Generic & Type-Safe**: Works with primitives (`int`, `float`) and custom objects.
* **Advanced Sorting**: Implements **Introsort** (Introspective Sort), a hybrid algorithm that switches between Quicksort, Heapsort, and Insertion Sort for optimal performance.
* **Persistence**: Built-in `Save()` and `Load()` methods for binary serialization.
* **STL Compatibility**: Custom iterators allow usage with standard algorithms like `std::for_each` or range-based for loops.
* **Exception Safety**: Bounds checking prevents invalid memory access.

## 📂 Project Structure

```text
DynamicArray/
├── inc/
│   ├── Array.h         # Main class definition
│   ├── Serializer.h    # Binary serialization logic
│   ├── Sorting.h       # Introsort algorithm definitions
│   └── Exceptions.h    # Custom exception classes
├── src/
│   ├── Array.tpp       # Template implementation for Array
│   └── Sorting.tpp     # Template implementation for Sorting
├── main.cpp            # Usage demonstration
└── tests.cpp           # Unit tests (Catch2)
