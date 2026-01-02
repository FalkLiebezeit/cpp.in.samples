#include <iostream>
#include <vector>
#include <algorithm>

// Linear Search
int linearSearch(const std::vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// Binary Search (iterative)
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Binary Search (recursive)
int binarySearchRecursive(const std::vector<int>& arr, int target, int left, int right) {
    if (left > right) {
        return -1;
    }
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursive(arr, target, mid + 1, right);
    } else {
        return binarySearchRecursive(arr, target, left, mid - 1);
    }
}

// Jump Search
int jumpSearch(const std::vector<int>& arr, int target) {
    int n = arr.size();
    int step = std::sqrt(n);
    int prev = 0;
    
    while (arr[std::min(step, n) - 1] < target) {
        prev = step;
        step += std::sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }
    
    while (arr[prev] < target) {
        prev++;
        if (prev == std::min(step, n)) {
            return -1;
        }
    }
    
    if (arr[prev] == target) {
        return prev;
    }
    return -1;
}

int main() {
    std::vector<int> unsortedArray = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
    std::vector<int> sortedArray = {11, 12, 22, 25, 34, 45, 50, 64, 88, 90};
    
    int target = 25;
    
    std::cout << "=== Linear Search ===" << std::endl;
    std::cout << "Array: ";
    for (int num : unsortedArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    int result = linearSearch(unsortedArray, target);
    if (result != -1) {
        std::cout << "Found " << target << " at index " << result << std::endl;
    } else {
        std::cout << target << " not found" << std::endl;
    }
    
    std::cout << "\n=== Binary Search (Iterative) ===" << std::endl;
    std::cout << "Sorted Array: ";
    for (int num : sortedArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    result = binarySearch(sortedArray, target);
    if (result != -1) {
        std::cout << "Found " << target << " at index " << result << std::endl;
    } else {
        std::cout << target << " not found" << std::endl;
    }
    
    std::cout << "\n=== Binary Search (Recursive) ===" << std::endl;
    result = binarySearchRecursive(sortedArray, target, 0, sortedArray.size() - 1);
    if (result != -1) {
        std::cout << "Found " << target << " at index " << result << std::endl;
    } else {
        std::cout << target << " not found" << std::endl;
    }
    
    std::cout << "\n=== Jump Search ===" << std::endl;
    result = jumpSearch(sortedArray, target);
    if (result != -1) {
        std::cout << "Found " << target << " at index " << result << std::endl;
    } else {
        std::cout << target << " not found" << std::endl;
    }
    
    std::cout << "\n=== STL Binary Search ===" << std::endl;
    bool found = std::binary_search(sortedArray.begin(), sortedArray.end(), target);
    std::cout << target << (found ? " found" : " not found") << " in array" << std::endl;
    
    // lower_bound and upper_bound
    auto lower = std::lower_bound(sortedArray.begin(), sortedArray.end(), target);
    auto upper = std::upper_bound(sortedArray.begin(), sortedArray.end(), target);
    
    if (lower != sortedArray.end()) {
        std::cout << "lower_bound of " << target << " is at index " 
                  << std::distance(sortedArray.begin(), lower) << std::endl;
    }
    if (upper != sortedArray.end()) {
        std::cout << "upper_bound of " << target << " is at index " 
                  << std::distance(sortedArray.begin(), upper) << std::endl;
    }
    
    return 0;
}
