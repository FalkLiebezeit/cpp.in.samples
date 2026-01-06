#include <iostream>
#include <string>
#include <iomanip>  // For output formatting

using namespace std::string_literals;  // Enable "s" suffix for string literals

/**
 * Demonstrates fundamental C++ data types and type deduction
 * Shows: primitive types, strings, auto keyword, and formatted output
 */
int main() {
    // === Integral Types ===
    // int: Standard integer type, typically 32-bit (-2^31 to 2^31-1)
    int age = 25;
    
    // long: Larger integer type, at least 32-bit, often 64-bit
    // Suffix 'L' explicitly marks it as a long literal
    long population = 7'800'000'000L;  // C++14 digit separator for readability
    
    // short: Smaller integer type, typically 16-bit
    short year = 2026;
    
    // unsigned: Non-negative values only, doubles positive range
    unsigned int studentCount = 150;
    
    // === Floating-Point Types ===
    // double: Double-precision floating point (64-bit), default for decimals
    constexpr double pi = 3.14159265359;  // constexpr: compile-time constant
    
    // float: Single-precision (32-bit), use 'f' suffix
    float temperature = 22.5f;
    
    // === Character and Boolean ===
    // char: Single character, 8-bit ASCII value
    char grade = 'A';
    
    // bool: Boolean type, stores true (1) or false (0)
    bool isStudent = true;
    
    // === String Type ===
    // std::string: Dynamic string class from STL (not a primitive type)
    const std::string name = "John Doe";  // const: value won't change
    
    // === Type Deduction (C++11) ===
    // auto: Compiler deduces type from initializer
    auto count = 42;              // Deduced as int
    auto average = 85.5;          // Deduced as double
    auto letter = 'B';            // Deduced as char
    auto message = "Hello"s;      // Using string literal suffix (C++14) for std::string
    
    // === Formatted Output ===
    std::cout << std::fixed << std::setprecision(2);  // Set 2 decimal places
    
    std::cout << "=== C++ Data Types Demo ===\n\n";
    
    // Display integral types
    std::cout << "Integral Types:\n";
    std::cout << "  Age (int):           " << age << " years\n";
    std::cout << "  Population (long):   " << population << " people\n";
    std::cout << "  Year (short):        " << year << "\n";
    std::cout << "  Students (unsigned): " << studentCount << "\n\n";
    
    // Display floating-point types
    std::cout << "Floating-Point Types:\n";
    std::cout << "  Pi (double):         " << pi << "\n";
    std::cout << "  Temperature (float): " << temperature << "°C\n\n";
    
    // Display character and boolean
    std::cout << "Other Types:\n";
    std::cout << "  Grade (char):        " << grade << "\n";
    std::cout << "  Is Student (bool):   " << std::boolalpha << isStudent << "\n";
    std::cout << "  Name (string):       " << name << "\n\n";
    
    // Display auto-deduced types
    std::cout << "Auto Type Deduction:\n";
    std::cout << "  Count:               " << count << "\n";
    std::cout << "  Average:             " << average << "\n";
    std::cout << "  Letter:              " << letter << "\n";
    std::cout << "  Message:             " << message << "\n";
    
    return 0;
}
