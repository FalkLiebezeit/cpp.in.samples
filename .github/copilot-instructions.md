# C++ Samples Workspace

This workspace contains C++ sample programs demonstrating various concepts from basics to modern C++17 features.

## Project Structure

The workspace is organized into categories:
- **basics/** - Fundamental C++ concepts (hello world, variables, control flow)
- **stl/** - Standard Template Library examples (vector, map, set)
- **modern_cpp/** - Modern C++ features (smart pointers, templates, lambdas, move semantics)
- **algorithms/** - Algorithm implementations (sorting, searching, STL algorithms)

## Project Guidelines

- Use modern C++ standards (C++17 or later)
- Follow clear naming conventions
- Include comments for educational purposes
- Build system uses CMake (or compile directly with g++)

## Build Instructions

### Using CMake (if installed)
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Using g++ directly
```bash
g++ -std=c++17 -Wall <source_file>.cpp -o <output_name>
```

## Copilot Instructions

When working with this workspace:
- Maintain C++17 standard compliance
- Add clear educational comments to code
- Follow existing file organization patterns
- Test code before committing
