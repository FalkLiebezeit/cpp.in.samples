#include <iostream>
#include <vector>
#include <string>
#include <utility>

// Class demonstrating move semantics
class Buffer {
private:
    int* data;
    size_t size;
    
public:
    // Constructor
    Buffer(size_t size) : data(new int[size]), size(size) {
        std::cout << "Constructor: Allocated buffer of size " << size << std::endl;
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i);
        }
    }
    
    // Destructor
    ~Buffer() {
        if (data) {
            std::cout << "Destructor: Deallocated buffer" << std::endl;
            delete[] data;
        }
    }
    
    // Copy constructor (expensive)
    Buffer(const Buffer& other) : data(new int[other.size]), size(other.size) {
        std::cout << "Copy Constructor: Deep copy of buffer" << std::endl;
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    
    // Copy assignment
    Buffer& operator=(const Buffer& other) {
        std::cout << "Copy Assignment" << std::endl;
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // Move constructor (efficient)
    Buffer(Buffer&& other) noexcept : data(other.data), size(other.size) {
        std::cout << "Move Constructor: Moved buffer ownership" << std::endl;
        other.data = nullptr;
        other.size = 0;
    }
    
    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        std::cout << "Move Assignment" << std::endl;
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    void print() const {
        if (data) {
            std::cout << "Buffer contents: ";
            for (size_t i = 0; i < size; ++i) {
                std::cout << data[i] << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "Buffer is empty" << std::endl;
        }
    }
};

// Factory function returning by value (move semantics)
Buffer createBuffer(size_t size) {
    return Buffer(size);
}

int main() {
    std::cout << "=== Creating Buffer ===" << std::endl;
    Buffer buf1(5);
    buf1.print();
    
    std::cout << "\n=== Copy Constructor ===" << std::endl;
    Buffer buf2 = buf1;  // Copy
    buf2.print();
    
    std::cout << "\n=== Move Constructor ===" << std::endl;
    Buffer buf3 = std::move(buf1);  // Move
    std::cout << "After move, buf1: ";
    buf1.print();
    std::cout << "buf3: ";
    buf3.print();
    
    std::cout << "\n=== Factory Function (RVO/NRVO) ===" << std::endl;
    Buffer buf4 = createBuffer(3);
    buf4.print();
    
    std::cout << "\n=== Move Assignment ===" << std::endl;
    Buffer buf5(2);
    buf5 = std::move(buf3);
    buf5.print();
    
    std::cout << "\n=== std::move with Vector ===" << std::endl;
    std::vector<std::string> vec1 = {"Hello", "World", "C++"};
    std::cout << "vec1 size: " << vec1.size() << std::endl;
    
    std::vector<std::string> vec2 = std::move(vec1);  // Move
    std::cout << "After move:" << std::endl;
    std::cout << "vec1 size: " << vec1.size() << std::endl;
    std::cout << "vec2 size: " << vec2.size() << std::endl;
    
    std::cout << "\n=== Program End ===" << std::endl;
    return 0;
}
