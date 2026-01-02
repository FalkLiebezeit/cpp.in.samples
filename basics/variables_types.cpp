#include <iostream>
#include <string>

int main() {
    // Integer types
    int age = 25;
    long population = 7800000000L;
    
    // Floating point types
    double pi = 3.14159;
    float temperature = 22.5f;
    
    // Character and boolean
    char grade = 'A';
    bool isStudent = true;
    
    // String
    std::string name = "John Doe";
    
    // Auto type deduction (C++11)
    auto count = 42;  // deduced as int
    auto message = "Hello";  // deduced as const char*
    
    // Display values
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Grade: " << grade << std::endl;
    std::cout << "Pi: " << pi << std::endl;
    std::cout << "Is Student: " << (isStudent ? "Yes" : "No") << std::endl;
    std::cout << "Auto count: " << count << std::endl;
    
    return 0;
}
