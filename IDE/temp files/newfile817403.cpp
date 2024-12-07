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

// Convert various types to std::string
std::string STR(int value) {
    return std::to_string(value);
}
// Convert various types to std::string
std::string STR(long long value) {
    return std::to_string(value);
}
std::string STR(float value) {
    return std::to_string(value);
}
std::string STR(double value) {
    return std::to_string(value);
}
std::string STR(size_t value) {
    return std::to_string(value);
}
std::string STR(bool value) {
    return value ? "1" : "0";
}
std::string STR(const char* value) {
    return std::string(value);
}


std::vector<std::string> copyTemp1;
std::vector<std::string> copyTemp2;
std::vector<std::any> OSPHTVMOSP_someObj = {
std::string("someObj"),
copyTemp1,
};
std::vector<std::any> OSPHTVMOSP_someObj2 = {
std::string("someObj2"),
copyTemp2,
};
std::vector<std::any> OSPHTVMOSP_main1_main2_main3_main4_main1_main = {
std::string("main1.main2.main3.main4.main1.main"),
std::string("hello BOWAH"),
};
int main(int argc, char* argv[]) {
    for (int A_Index1 = 0; A_Index1 < 7 + 0; A_Index1++) {
        std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_someObj[1]).push_back("hello" + STR(A_Index1));
        std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_someObj2[1]).push_back("hello" + STR(A_Index1));
    }
    print(std::any_cast<std::string>(OSPHTVMOSP_main1_main2_main3_main4_main1_main[1]));
    print(std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_someObj[1])[5]);
    print(std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_someObj2[1])[5]);
    return 0;
}