#include <algorithm>
#include <any>
#include <cstdint>
#include <iostream>
#include <optional>
#include <regex>
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

std::string RegExReplace(const std::string& inputStr, const std::string& regexPattern, const std::string& replacement) {
    std::regex re(regexPattern, std::regex_constants::ECMAScript | std::regex_constants::multiline);
    return std::regex_replace(inputStr, re, replacement);
}


int main(int argc, char* argv[]) {
    std::string outCode = "var1 := ";
    // Example C++ ternary expressions
    std::string cpp_code = "day == SUNDAY ? 12 : 9";
    // Convert C++ ternary to Python ternary using RegExReplace
    std::string python_code = RegExReplace(cpp_code, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "$2 if $1 else $3");
    std::string nim_code = RegExReplace(cpp_code, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*)", "if $1: $2 else: $3");
    // Convert C++ ternary to Lua ternary-like expression using RegExReplace
    std::string lua_code = RegExReplace(cpp_code, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "($1) and $2 or $3");
    // Convert C++ ternary to Kotlin/Scala ternary-like expression using RegExReplace
    std::string kotlin_code = RegExReplace(cpp_code, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "if $1 $2 else $3");
    // Output the converted code for Python, Nim, Lua, and Kotlin/Scala
    print(outCode + python_code);
    print(outCode + nim_code);
    print(outCode + lua_code);
    print(outCode + kotlin_code);
    return 0;
}
