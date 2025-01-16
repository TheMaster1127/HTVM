#include <algorithm>
#include <any>
#include <cstdint>
#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

// Print function for const char* specifically
void print(const char* value) {
    std::cout << std::string(value) << std::endl;  // Convert const char* to std::string
}
// Print function that converts all types to string if needed
template <typename T>
void print(const T& value) {
    if constexpr (std::is_same_v<T, std::string>) {
        std::cout << value << std::endl;
    } else if constexpr (std::is_same_v<T, char>) {
        std::cout << value << std::endl;
    } else if constexpr (std::is_same_v<T, int>) {
        std::cout << std::to_string(value) << std::endl;
    } else if constexpr (std::is_same_v<T, float>) {
        std::cout << std::to_string(value) << std::endl;
    } else if constexpr (std::is_same_v<T, double>) {
        std::cout << std::to_string(value) << std::endl;
    } else if constexpr (std::is_same_v<T, size_t>) {
        std::cout << std::to_string(value) << std::endl;
    } else if constexpr (std::is_same_v<T, bool>) {
        std::cout << (value ? "1" : "0") << std::endl;
    } else {
        std::cout << "Unsupported type" << std::endl;
    }
}

// Function to sort and remove duplicates
std::vector<std::string> sortArr(const std::vector<std::string>& input) {
    std::set<std::string> uniqueSorted(input.begin(), input.end());
    return std::vector<std::string>(uniqueSorted.begin(), uniqueSorted.end());
}

// Function to sort an array of strings by length in descending order
void sortArrByLenOnly(std::vector<std::string>& array) {
    std::sort(array.begin(), array.end(), [](const std::string& a, const std::string& b) {
        return a.length() > b.length();
    });
}


int main(int argc, char* argv[]) {
    std::vector<std::string> test;
    test.push_back("hello");
    test.push_back("+");
    test.push_back("+");
    test.push_back(".");
    test.push_back("!=");
    test.push_back("!");
    sortArrByLenOnly(test);
    for (int A_Index1 = 0; A_Index1 < test.size() + 0; A_Index1++) {
        print(test[A_Index1]);
    }
    return 0;
}
