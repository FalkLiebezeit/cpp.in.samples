# C++ Samples Collection

A comprehensive collection of C++ sample programs demonstrating various concepts from basics to advanced modern C++ features.

## Project Structure

```
cpp.in.samples/
├── basics/              # Basic C++ concepts
├── stl/                # STL containers examples
├── modern_cpp/         # Modern C++ features (C++11/14/17)
├── algorithms/         # Algorithm implementations
└── CMakeLists.txt     # Build configuration
```

## Categories

### 1. Basics
- **hello_world.cpp** - Classic Hello World program
- **variables_types.cpp** - Variable declarations and data types
- **control_flow.cpp** - If-else, loops, switch statements

### 2. STL (Standard Template Library)
- **vector_example.cpp** - Dynamic arrays with std::vector
- **map_example.cpp** - Key-value pairs with std::map
- **set_example.cpp** - Unique sorted elements with std::set

### 3. Modern C++
- **smart_pointers.cpp** - unique_ptr, shared_ptr, weak_ptr
- **templates.cpp** - Function and class templates
- **lambda_example.cpp** - Lambda expressions and closures
- **move_semantics.cpp** - Move constructors and rvalue references

### 4. Algorithms
- **sorting.cpp** - Bubble, Selection, Insertion, Quick Sort
- **searching.cpp** - Linear, Binary, Jump Search
- **stl_algorithms.cpp** - STL algorithm examples (transform, accumulate, etc.)

## Requirements

- C++ compiler with C++17 support (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.15 or higher

## Building the Project

### Linux/macOS

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build all samples
cmake --build .

# Or build specific sample
cmake --build . --target hello_world
```

### Windows

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build all samples
cmake --build . --config Release

# Or build specific sample
cmake --build . --target hello_world --config Release
```

## Running Examples

After building, executables will be in the `build` directory:

```bash
# From the build directory
./basics/hello_world
./stl/vector_example
./modern_cpp/smart_pointers
./algorithms/sorting
```

On Windows:
```bash
.\basics\Release\hello_world.exe
.\stl\Release\vector_example.exe
```

## Quick Start

To quickly test a single file without CMake:

```bash
# Compile single file
g++ -std=c++17 -Wall basics/hello_world.cpp -o hello_world

# Run
./hello_world
```

## Learning Path

1. Start with **basics/** to understand fundamental C++ syntax
2. Explore **stl/** to learn about standard containers
3. Study **modern_cpp/** for C++11/14/17 features
4. Review **algorithms/** for common algorithmic patterns

## Key Concepts Covered

- ✅ Basic syntax and control structures
- ✅ STL containers (vector, map, set)
- ✅ Smart pointers and memory management
- ✅ Templates and generic programming
- ✅ Lambda expressions
- ✅ Move semantics and rvalue references
- ✅ Sorting and searching algorithms
- ✅ STL algorithms (transform, accumulate, for_each, etc.)

## C++ Standards

All examples are written using C++17 standard. Key modern C++ features used:

- Auto type deduction
- Range-based for loops
- Smart pointers
- Lambda expressions
- Move semantics
- Structured bindings (where applicable)

## Contributing

Feel free to add more examples or improve existing ones. Follow these guidelines:

- Use modern C++ standards (C++17+)
- Include clear comments explaining concepts
- Follow consistent naming conventions
- Add appropriate examples to the correct category

## Resources

- [cppreference.com](https://en.cppreference.com/) - Comprehensive C++ reference
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/) - Best practices
- [Modern C++ Features](https://github.com/AnthonyCalandra/modern-cpp-features) - Feature overview

## License

These samples are provided for educational purposes.
