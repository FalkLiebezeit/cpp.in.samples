/**
 * control_flow.cpp - Comprehensive demonstration of C++ control flow structures
 * 
 * This program demonstrates:
 * - Conditional statements (if-else)
 * - Loops (for, while, range-based for)
 * - Switch statements
 * 
 * Compiled with: g++ -std=c++17 -Wall control_flow.cpp -o control_flow
 */

#include <iostream>
#include <array>

int main() {
    // === CONDITIONAL STATEMENTS ===
    // If-else: tests conditions and executes code based on boolean evaluation
    int number = 42;
    
    std::cout << "=== Conditional Statement (if-else) ===" << std::endl;
    if (number > 0) {
        std::cout << "Number " << number << " is positive" << std::endl;
    } else if (number < 0) {
        std::cout << "Number " << number << " is negative" << std::endl;
    } else {
        std::cout << "Number is zero" << std::endl;
    }
    
    // === FOR LOOP ===
    // Classic for loop: initialization, condition, increment
    std::cout << "\n=== For Loop (1 to 5) ===" << std::endl;
    for (int i = 1; i <= 5; ++i) {  // Prefix increment is slightly more efficient
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // === WHILE LOOP ===
    // While loop: executes as long as condition is true
    std::cout << "\n=== While Loop (Countdown) ===" << std::endl;
    int countdown = 5;
    while (countdown > 0) {
        std::cout << countdown << " ";
        --countdown;
    }
    std::cout << "Liftoff!" << std::endl;
    
    // === SWITCH STATEMENT ===
    // Switch: efficient multi-way branch based on integer/char values
    char grade = 'B';
    std::cout << "\n=== Switch Statement (Grade: " << grade << ") ===" << std::endl;
    switch (grade) {
        case 'A':
            std::cout << "Excellent! Outstanding performance." << std::endl;
            break;
        case 'B':
            std::cout << "Good job! Above average work." << std::endl;
            break;
        case 'C':
            std::cout << "Fair performance." << std::endl;
            break;
        case 'D':
            std::cout << "Below average, needs improvement." << std::endl;
            break;
        case 'F':
            std::cout << "Failing grade." << std::endl;
            break;
        default:
            std::cout << "Invalid grade entered." << std::endl;
    }
    
    // === RANGE-BASED FOR LOOP (C++11) ===
    // Modern C++ loop: iterates over containers without index management
    std::cout << "\n=== Range-based For Loop (C++11) ===" << std::endl;
    constexpr int array[] = {10, 20, 30, 40, 50};  // constexpr for compile-time constant
    for (const int value : array) {  // const for read-only access
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    // === DO-WHILE LOOP (Bonus) ===
    // Do-while: executes at least once, then checks condition
    std::cout << "\n=== Do-While Loop (Execute at least once) ===" << std::endl;
    int counter = 1;
    do {
        std::cout << "Iteration " << counter << std::endl;
        ++counter;
    } while (counter <= 3);
    
    return 0;
}

