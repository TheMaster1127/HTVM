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


int myOwn_var1 = 5;
float myOwn_var2 = 6.54f;
int myOwn2_var1 = 5;
float myOwn2_var2 = 6.54f;
int myOwn3_var1 = 5;
float myOwn3_var2 = 6.54f;
int myOwn4_var1 = 5;
float myOwn4_var2 = 6.54f;
int myOwn5_var1 = 5;
std::string myOwn5_var2 = "hello";
int main(int argc, char* argv[]) {
    print(myOwn_var1);
    print(myOwn_var2);
    

    return 0;
}