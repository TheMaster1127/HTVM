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
    if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    } else {
        print(5+5);
    }
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    try {
        throw std::runtime_error("this is an ERROR HTVM v2");
    }
    catch (const std::exception& ee) {
        print(ee.what());
    }
    if ("finally dosent exist in c++" == "finally dosent exist in c++") {
        print("finally finally finally finally");
    }
    return 0;
}
