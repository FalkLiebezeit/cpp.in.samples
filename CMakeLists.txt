cmake_minimum_required(VERSION 3.15)
project(CPPSamples VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Add subdirectories for different sample categories
add_subdirectory(basics)
add_subdirectory(stl)
add_subdirectory(modern_cpp)
add_subdirectory(algorithms)
