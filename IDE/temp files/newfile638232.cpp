#include <algorithm>
#include <any>
#include <cstdint>
#include <iostream>
#include <optional>
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


int main(int argc, char* argv[]) {
    std::vector<int> theArr;
    theArr.push_back(1);
    theArr.push_back(2);
    theArr.push_back(2);
    theArr.push_back(3);
    theArr.push_back(3);
    theArr.push_back(3);
    std::vector<int> tempArr;
    std::vector<int> outArr;
    int currnet = 0;
    int found = 0;
    for (int A_Index1 = 0; A_Index1 < theArr.size() + 0; A_Index1++) {
        if (A_Index1 != 0) {
            currnet = A_Index1;
            for (int A_Index2 = 0; A_Index2 < tempArr.size() + 0; A_Index2++) {
                if (tempArr[A_Index2] == theArr[currnet]) {
                    found = 1;
                    break;
                }
            }
            if (found != 1) {
                outArr.push_back(theArr[A_Index1]);
            }
            tempArr.push_back(theArr[A_Index1]);
            found = 0;
        } else {
            tempArr.push_back(theArr[A_Index1]);
            outArr.push_back(theArr[A_Index1]);
        }
    }
    print(outArr);
    return 0;
}
