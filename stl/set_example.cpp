#include <iostream>
#include <set>
#include <string>

int main() {
    // Create a set (stores unique elements in sorted order)
    std::set<int> numbers;
    
    // Insert elements
    numbers.insert(50);
    numbers.insert(20);
    numbers.insert(40);
    numbers.insert(10);
    numbers.insert(30);
    numbers.insert(20);  // Duplicate - will not be inserted
    
    std::cout << "Set contents (automatically sorted):" << std::endl;
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Size
    std::cout << "\nSet size: " << numbers.size() << std::endl;
    
    // Find element
    int searchValue = 30;
    if (numbers.find(searchValue) != numbers.end()) {
        std::cout << searchValue << " found in set" << std::endl;
    } else {
        std::cout << searchValue << " not found in set" << std::endl;
    }
    
    // Check if element exists
    std::cout << "Does 60 exist? " << (numbers.count(60) ? "Yes" : "No") << std::endl;
    
    // Remove element
    numbers.erase(40);
    std::cout << "\nAfter erasing 40: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // String set example
    std::set<std::string> fruits;
    fruits.insert("Apple");
    fruits.insert("Banana");
    fruits.insert("Cherry");
    fruits.insert("Apple");  // Duplicate
    
    std::cout << "\nFruit set (alphabetically sorted):" << std::endl;
    for (const auto& fruit : fruits) {
        std::cout << fruit << std::endl;
    }
    
    return 0;
}
