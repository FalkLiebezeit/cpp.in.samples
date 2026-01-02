#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Create a vector
    std::vector<int> numbers;
    
    // Add elements
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);
    numbers.push_back(50);
    
    std::cout << "Vector elements: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Access elements
    std::cout << "First element: " << numbers.front() << std::endl;
    std::cout << "Last element: " << numbers.back() << std::endl;
    std::cout << "Element at index 2: " << numbers[2] << std::endl;
    
    // Size and capacity
    std::cout << "Size: " << numbers.size() << std::endl;
    std::cout << "Capacity: " << numbers.capacity() << std::endl;
    
    // Insert element at position
    numbers.insert(numbers.begin() + 2, 25);
    std::cout << "\nAfter inserting 25 at index 2: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Remove last element
    numbers.pop_back();
    std::cout << "\nAfter pop_back: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Sort in descending order
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());
    std::cout << "\nSorted (descending): ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Find element
    auto it = std::find(numbers.begin(), numbers.end(), 25);
    if (it != numbers.end()) {
        std::cout << "\nFound 25 at position: " << std::distance(numbers.begin(), it) << std::endl;
    }
    
    return 0;
}
