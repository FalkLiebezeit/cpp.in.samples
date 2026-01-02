#include <iostream>
#include <map>
#include <string>

int main() {
    // Create a map (key-value pairs)
    std::map<std::string, int> ages;
    
    // Insert elements
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 35;
    ages.insert({"Diana", 28});
    
    std::cout << "Map contents:" << std::endl;
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << " years old" << std::endl;
    }
    
    // Access elements
    std::cout << "\nAlice's age: " << ages["Alice"] << std::endl;
    
    // Check if key exists
    std::string searchName = "Eve";
    if (ages.find(searchName) != ages.end()) {
        std::cout << searchName << " found in map" << std::endl;
    } else {
        std::cout << searchName << " not found in map" << std::endl;
    }
    
    // Update value
    ages["Bob"] = 31;
    std::cout << "\nBob's updated age: " << ages["Bob"] << std::endl;
    
    // Remove element
    ages.erase("Charlie");
    std::cout << "\nAfter removing Charlie:" << std::endl;
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    // Size
    std::cout << "\nMap size: " << ages.size() << std::endl;
    
    // Using count() to check existence
    std::cout << "Does 'Alice' exist? " << (ages.count("Alice") ? "Yes" : "No") << std::endl;
    
    return 0;
}
