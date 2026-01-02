#include <iostream>
#include <vector>
#include <string>

// Function template
template<typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

// Class template
template<typename T>
class Stack {
private:
    std::vector<T> elements;
    
public:
    void push(const T& element) {
        elements.push_back(element);
    }
    
    void pop() {
        if (!elements.empty()) {
            elements.pop_back();
        }
    }
    
    T top() const {
        if (!elements.empty()) {
            return elements.back();
        }
        throw std::runtime_error("Stack is empty");
    }
    
    bool empty() const {
        return elements.empty();
    }
    
    size_t size() const {
        return elements.size();
    }
};

// Template specialization
template<>
class Stack<bool> {
private:
    std::vector<bool> elements;
    
public:
    void push(bool element) {
        elements.push_back(element);
        std::cout << "Specialized bool stack: pushed " << (element ? "true" : "false") << std::endl;
    }
    
    void pop() {
        if (!elements.empty()) {
            elements.pop_back();
        }
    }
    
    bool top() const {
        if (!elements.empty()) {
            return elements.back();
        }
        throw std::runtime_error("Stack is empty");
    }
    
    bool empty() const {
        return elements.empty();
    }
    
    size_t size() const {
        return elements.size();
    }
};

// Variadic template (C++11)
template<typename T>
T sum(T value) {
    return value;
}

template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...);
}

int main() {
    std::cout << "=== Function Templates ===" << std::endl;
    std::cout << "Max of 10 and 20: " << getMax(10, 20) << std::endl;
    std::cout << "Max of 3.14 and 2.71: " << getMax(3.14, 2.71) << std::endl;
    std::cout << "Max of 'a' and 'z': " << getMax('a', 'z') << std::endl;
    
    std::cout << "\n=== Class Templates ===" << std::endl;
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    
    std::cout << "Int stack top: " << intStack.top() << std::endl;
    std::cout << "Int stack size: " << intStack.size() << std::endl;
    
    Stack<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    
    std::cout << "String stack top: " << stringStack.top() << std::endl;
    
    std::cout << "\n=== Template Specialization ===" << std::endl;
    Stack<bool> boolStack;
    boolStack.push(true);
    boolStack.push(false);
    
    std::cout << "\n=== Variadic Templates ===" << std::endl;
    std::cout << "Sum of 1, 2, 3, 4, 5: " << sum(1, 2, 3, 4, 5) << std::endl;
    std::cout << "Sum of 1.5, 2.5, 3.5: " << sum(1.5, 2.5, 3.5) << std::endl;
    
    return 0;
}
