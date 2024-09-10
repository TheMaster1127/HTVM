#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

// Print function for const char* specifically
void MsgBox(const char* value) {
    std::cout << std::string(value) << std::endl;  // Convert const char* to std::string
}
// Print function that converts all types to string if needed
template <typename T>
void MsgBox(const T& value) {
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


int main(int argc, char* argv[]) {
    std::vector<int> arr123;
    arr123.push_back(6);
    arr123.push_back(5);
    arr123.push_back(58);
    // You can use indentations if you want to. It's all optional.
    for (int A_Index1 = 1; A_Index1 <= arr123.size() + 1 - 1; A_Index1++) {
        MsgBox(arr123[A_Index1 - 1]);
    }
    // You can use indentations if you want to. It's all optional.
    for (int A_Index2 = 1; A_Index2 <= 3 + 1 - 1; A_Index2++) {
        MsgBox(A_Index2);
    }
    // You can use indentations if you want to. It's all optional.
    if (arr123[1] == 5) {
        MsgBox("yes");
    }
    return 0;
}