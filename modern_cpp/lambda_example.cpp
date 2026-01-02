#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::cout << "=== Basic Lambda ===" << std::endl;
    // Simple lambda to print each element
    std::cout << "Numbers: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n) {
        std::cout << n << " ";
    });
    std::cout << std::endl;
    
    std::cout << "\n=== Lambda with Capture ===" << std::endl;
    int threshold = 5;
    
    // Count numbers greater than threshold
    int count = std::count_if(numbers.begin(), numbers.end(), [threshold](int n) {
        return n > threshold;
    });
    std::cout << "Count of numbers > " << threshold << ": " << count << std::endl;
    
    std::cout << "\n=== Lambda with Mutable Capture ===" << std::endl;
    int sum = 0;
    std::for_each(numbers.begin(), numbers.end(), [&sum](int n) {
        sum += n;
    });
    std::cout << "Sum of all numbers: " << sum << std::endl;
    
    std::cout << "\n=== Lambda with Return Type ===" << std::endl;
    auto multiply = [](int a, int b) -> int {
        return a * b;
    };
    std::cout << "5 * 7 = " << multiply(5, 7) << std::endl;
    
    std::cout << "\n=== Lambda for Sorting ===" << std::endl;
    std::vector<int> sortedNumbers = numbers;
    
    // Sort in descending order
    std::sort(sortedNumbers.begin(), sortedNumbers.end(), [](int a, int b) {
        return a > b;
    });
    
    std::cout << "Sorted (descending): ";
    for (int n : sortedNumbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\n=== Lambda as Function Object ===" << std::endl;
    auto isEven = [](int n) { return n % 2 == 0; };
    
    std::cout << "Even numbers: ";
    for (int n : numbers) {
        if (isEven(n)) {
            std::cout << n << " ";
        }
    }
    std::cout << std::endl;
    
    std::cout << "\n=== Generic Lambda (C++14) ===" << std::endl;
    auto printer = [](const auto& value) {
        std::cout << value << std::endl;
    };
    
    printer(42);
    printer(3.14);
    printer("Hello, Lambda!");
    
    std::cout << "\n=== Lambda with std::function ===" << std::endl;
    std::function<int(int, int)> operation;
    
    operation = [](int a, int b) { return a + b; };
    std::cout << "10 + 5 = " << operation(10, 5) << std::endl;
    
    operation = [](int a, int b) { return a * b; };
    std::cout << "10 * 5 = " << operation(10, 5) << std::endl;
    
    return 0;
}
