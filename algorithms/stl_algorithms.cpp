#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    std::vector<std::string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    
    std::cout << "Original numbers: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    // sort
    std::cout << "\n=== std::sort ===" << std::endl;
    std::vector<int> sorted = numbers;
    std::sort(sorted.begin(), sorted.end());
    std::cout << "Sorted: ";
    for (int n : sorted) std::cout << n << " ";
    std::cout << std::endl;
    
    // reverse
    std::cout << "\n=== std::reverse ===" << std::endl;
    std::reverse(sorted.begin(), sorted.end());
    std::cout << "Reversed: ";
    for (int n : sorted) std::cout << n << " ";
    std::cout << std::endl;
    
    // find
    std::cout << "\n=== std::find ===" << std::endl;
    auto it = std::find(numbers.begin(), numbers.end(), 7);
    if (it != numbers.end()) {
        std::cout << "Found 7 at position " << std::distance(numbers.begin(), it) << std::endl;
    }
    
    // count
    std::cout << "\n=== std::count ===" << std::endl;
    std::vector<int> values = {1, 2, 3, 2, 4, 2, 5};
    int count = std::count(values.begin(), values.end(), 2);
    std::cout << "Count of 2: " << count << std::endl;
    
    // count_if
    std::cout << "\n=== std::count_if ===" << std::endl;
    int evenCount = std::count_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0;
    });
    std::cout << "Count of even numbers: " << evenCount << std::endl;
    
    // transform
    std::cout << "\n=== std::transform ===" << std::endl;
    std::vector<int> squared(numbers.size());
    std::transform(numbers.begin(), numbers.end(), squared.begin(), [](int n) {
        return n * n;
    });
    std::cout << "Squared values: ";
    for (int n : squared) std::cout << n << " ";
    std::cout << std::endl;
    
    // accumulate
    std::cout << "\n=== std::accumulate ===" << std::endl;
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Sum: " << sum << std::endl;
    
    int product = std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<int>());
    std::cout << "Product: " << product << std::endl;
    
    // min_element and max_element
    std::cout << "\n=== std::min_element / std::max_element ===" << std::endl;
    auto minIt = std::min_element(numbers.begin(), numbers.end());
    auto maxIt = std::max_element(numbers.begin(), numbers.end());
    std::cout << "Min: " << *minIt << std::endl;
    std::cout << "Max: " << *maxIt << std::endl;
    
    // for_each
    std::cout << "\n=== std::for_each ===" << std::endl;
    std::cout << "Numbers * 2: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n) {
        std::cout << n * 2 << " ";
    });
    std::cout << std::endl;
    
    // any_of, all_of, none_of
    std::cout << "\n=== std::any_of / std::all_of / std::none_of ===" << std::endl;
    bool hasEven = std::any_of(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0;
    });
    std::cout << "Has even number: " << (hasEven ? "Yes" : "No") << std::endl;
    
    bool allPositive = std::all_of(numbers.begin(), numbers.end(), [](int n) {
        return n > 0;
    });
    std::cout << "All positive: " << (allPositive ? "Yes" : "No") << std::endl;
    
    bool noneNegative = std::none_of(numbers.begin(), numbers.end(), [](int n) {
        return n < 0;
    });
    std::cout << "None negative: " << (noneNegative ? "Yes" : "No") << std::endl;
    
    // copy_if
    std::cout << "\n=== std::copy_if ===" << std::endl;
    std::vector<int> evenNumbers;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(evenNumbers), [](int n) {
        return n % 2 == 0;
    });
    std::cout << "Even numbers: ";
    for (int n : evenNumbers) std::cout << n << " ";
    std::cout << std::endl;
    
    // remove_if
    std::cout << "\n=== std::remove_if ===" << std::endl;
    std::vector<int> filtered = numbers;
    auto removeIt = std::remove_if(filtered.begin(), filtered.end(), [](int n) {
        return n < 5;
    });
    filtered.erase(removeIt, filtered.end());
    std::cout << "Numbers >= 5: ";
    for (int n : filtered) std::cout << n << " ";
    std::cout << std::endl;
    
    // unique
    std::cout << "\n=== std::unique ===" << std::endl;
    std::vector<int> duplicates = {1, 1, 2, 2, 3, 3, 4, 4, 5};
    auto uniqueEnd = std::unique(duplicates.begin(), duplicates.end());
    duplicates.erase(uniqueEnd, duplicates.end());
    std::cout << "Unique elements: ";
    for (int n : duplicates) std::cout << n << " ";
    std::cout << std::endl;
    
    return 0;
}
