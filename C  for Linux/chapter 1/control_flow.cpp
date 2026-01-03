#include <iostream>

int main() {
    // If-else statement
    int number = 42;
    
    if (number > 0) {
        std::cout << "Number is positive" << std::endl;
    } else if (number < 0) {
        std::cout << "Number is negative" << std::endl;
    } else {
        std::cout << "Number is zero" << std::endl;
    }
    
    // For loop
    std::cout << "\nFor loop (1 to 5):" << std::endl;
    for (int i = 1; i <= 5; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // While loop
    std::cout << "\nWhile loop countdown:" << std::endl;
    int countdown = 5;
    while (countdown > 0) {
        std::cout << countdown << " ";
        countdown--;
    }
    std::cout << "Liftoff!" << std::endl;
    
    // Switch statement
    char grade = 'B';
    std::cout << "\nGrade evaluation: ";
    switch (grade) {
        case 'A':
            std::cout << "Excellent!" << std::endl;
            break;
        case 'B':
            std::cout << "Good job!" << std::endl;
            break;
        case 'C':
            std::cout << "Fair" << std::endl;
            break;
        default:
            std::cout << "Need improvement" << std::endl;
    }
    
    // Range-based for loop (C++11)
    std::cout << "\nRange-based for loop:" << std::endl;
    int array[] = {10, 20, 30, 40, 50};
    for (int value : array) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
