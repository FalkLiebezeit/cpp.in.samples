#include <iostream>
#include <vector>
#include <algorithm>

// Bubble Sort
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Selection Sort
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            std::swap(arr[i], arr[minIdx]);
        }
    }
}

// Insertion Sort
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort helper
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Print vector
void printVector(const std::vector<int>& arr, const std::string& label) {
    std::cout << label << ": ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> original = {64, 34, 25, 12, 22, 11, 90};
    
    std::cout << "=== Original Array ===" << std::endl;
    printVector(original, "Original");
    
    // Bubble Sort
    std::cout << "\n=== Bubble Sort ===" << std::endl;
    std::vector<int> arr1 = original;
    bubbleSort(arr1);
    printVector(arr1, "Sorted");
    
    // Selection Sort
    std::cout << "\n=== Selection Sort ===" << std::endl;
    std::vector<int> arr2 = original;
    selectionSort(arr2);
    printVector(arr2, "Sorted");
    
    // Insertion Sort
    std::cout << "\n=== Insertion Sort ===" << std::endl;
    std::vector<int> arr3 = original;
    insertionSort(arr3);
    printVector(arr3, "Sorted");
    
    // Quick Sort
    std::cout << "\n=== Quick Sort ===" << std::endl;
    std::vector<int> arr4 = original;
    quickSort(arr4, 0, arr4.size() - 1);
    printVector(arr4, "Sorted");
    
    // STL Sort
    std::cout << "\n=== STL Sort ===" << std::endl;
    std::vector<int> arr5 = original;
    std::sort(arr5.begin(), arr5.end());
    printVector(arr5, "Sorted");
    
    // STL Sort (descending)
    std::cout << "\n=== STL Sort (Descending) ===" << std::endl;
    std::vector<int> arr6 = original;
    std::sort(arr6.begin(), arr6.end(), std::greater<int>());
    printVector(arr6, "Sorted");
    
    return 0;
}
