#if __has_include("srell.hpp")
    #include "srell.hpp"
    #define USE_POWERFUL_REGEX 1
    #pragma message("SUCCESS: Compiling with powerful SRELL regex engine. Lookbehinds will work.")
#else
    #include <regex>
    #define USE_POWERFUL_REGEX 0
    #pragma message("WARNING: srell.hpp not found. Falling back to limited std::regex. Lookbehinds will NOT work.")
#endif

#include <algorithm>
#include <any>
#include <cstdint>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

// Print function for const char*
void print(const char* value) {
    std::cout << std::string(value) << std::endl;
}
// Handle signed 8-bit integers
void print(int8_t value) {
    std::cout << static_cast<int>(value) << std::endl;
}
// Handle unsigned 8-bit integers
void print(uint8_t value) {
    std::cout << static_cast<unsigned int>(value) << std::endl;
}
// Generic print function fallback
template <typename T>
void print(const T& value) {
    std::cout << value << std::endl;
}


int main(int argc, char* argv[]) {
    int A_SUCCESS = 0;
    int A_SUCCESS_WEIGHTED = 0;
    int A_TOTAL_WEIGHT = 4;
    bool A_SUCCESS_ALL = false;
    bool hasMagicKey = true;
    int level = 20;
    int mana = 100;
    bool isCursed = false;
    // ------------------
    A_SUCCESS = 0;
    A_SUCCESS_WEIGHTED = 0;
    A_TOTAL_WEIGHT = 4;
    A_SUCCESS_ALL = false;
    if (hasMagicKey) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 1;
    }
    if (level > 15) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 1;
    }
    if (mana > 50) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 1;
    }
    if (!isCursed) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 1;
    }
    if (A_SUCCESS_WEIGHTED == A_TOTAL_WEIGHT) {
        A_SUCCESS_ALL = true;
    }
    // ------------------
    if (A_SUCCESS_ALL) {
        print("The ancient barrier dissolves...");
    }
    

    return 0;
}