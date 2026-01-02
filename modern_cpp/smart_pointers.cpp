#include <iostream>
#include <memory>
#include <string>

// Sample class
class Person {
public:
    Person(const std::string& name, int age) : name_(name), age_(age) {
        std::cout << "Person created: " << name_ << std::endl;
    }
    
    ~Person() {
        std::cout << "Person destroyed: " << name_ << std::endl;
    }
    
    void introduce() const {
        std::cout << "Hi, I'm " << name_ << ", " << age_ << " years old" << std::endl;
    }
    
private:
    std::string name_;
    int age_;
};

// Example function demonstrating unique_ptr transfer
std::unique_ptr<Person> createPerson(const std::string& name, int age) {
    return std::make_unique<Person>(name, age);
}

int main() {
    std::cout << "=== unique_ptr Example ===" << std::endl;
    {
        // Create unique_ptr
        std::unique_ptr<Person> person1 = std::make_unique<Person>("Alice", 25);
        person1->introduce();
        
        // Transfer ownership (move)
        std::unique_ptr<Person> person2 = std::move(person1);
        // person1 is now nullptr
        if (!person1) {
            std::cout << "person1 is now null" << std::endl;
        }
        person2->introduce();
        
        // Create using factory function
        auto person3 = createPerson("Charlie", 35);
        person3->introduce();
        
    }  // unique_ptr automatically deletes objects here
    
    std::cout << "\n=== shared_ptr Example ===" << std::endl;
    {
        std::shared_ptr<Person> shared1 = std::make_shared<Person>("Bob", 30);
        std::cout << "Reference count: " << shared1.use_count() << std::endl;
        
        {
            // Create another shared_ptr pointing to same object
            std::shared_ptr<Person> shared2 = shared1;
            std::cout << "Reference count after sharing: " << shared1.use_count() << std::endl;
            shared2->introduce();
            
        }  // shared2 goes out of scope
        
        std::cout << "Reference count after shared2 destroyed: " << shared1.use_count() << std::endl;
        
    }  // Object deleted when last shared_ptr is destroyed
    
    std::cout << "\n=== weak_ptr Example ===" << std::endl;
    {
        std::shared_ptr<Person> shared = std::make_shared<Person>("Diana", 28);
        std::weak_ptr<Person> weak = shared;  // Doesn't increase reference count
        
        std::cout << "Shared ref count: " << shared.use_count() << std::endl;
        std::cout << "Weak expired: " << (weak.expired() ? "Yes" : "No") << std::endl;
        
        // Use weak_ptr by converting to shared_ptr
        if (auto temp = weak.lock()) {
            temp->introduce();
        }
        
        shared.reset();  // Delete the Person object
        std::cout << "After reset, weak expired: " << (weak.expired() ? "Yes" : "No") << std::endl;
    }
    
    std::cout << "\n=== Program End ===" << std::endl;
    return 0;
}
