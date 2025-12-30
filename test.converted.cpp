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
std::string STR(const std::string& value) {
    return value;
}

// Function to get input from the user, similar to Python's input() function
std::string input(const std::string& prompt) {
    std::string userInput;
    std::cout << prompt; // Display the prompt to the user
    std::getline(std::cin, userInput); // Get the entire line of input
    return userInput;
}

std::string Chr(int number) {
    return (number >= 0 && number <= 0x10FFFF) ? std::string(1, static_cast<char>(number)) : "";
}


int gloabal_var1 = 777777;
int gloabal_var2 = 7777778;
std::string test1(std::string var1) {
    int var_test1 = 7854;
    // breakpoint was here
    input("(PRESS ENTER TO CONTINUE) - Breakpoint: 1" + Chr(10) + "============================================" + Chr(10) + "gloabal_var1: " + STR(gloabal_var1) + Chr(10) + "gloabal_var2: " + STR(gloabal_var2) + Chr(10) + "var1: " + STR(var1) + Chr(10) + "var_test1: " + STR(var_test1));
    return var1;
}
std::string test2(std::string var1) {
    int var_test2 = 6556;
    var_test2 = 6556;
    // breakpoint was here
    input("(PRESS ENTER TO CONTINUE) - Breakpoint: 2" + Chr(10) + "============================================" + Chr(10) + "gloabal_var1: " + STR(gloabal_var1) + Chr(10) + "gloabal_var2: " + STR(gloabal_var2) + Chr(10) + "var1: " + STR(var1) + Chr(10) + "var_test2: " + STR(var_test2));
    return var1;
}
int main(int argc, char* argv[]) {
    test1("wased");
    test2("wasedderfg");
    int var1 = 0;
    // breakpoint was here
    input("(PRESS ENTER TO CONTINUE) - Breakpoint: 3" + Chr(10) + "============================================" + Chr(10) + "gloabal_var1: " + STR(gloabal_var1) + Chr(10) + "gloabal_var2: " + STR(gloabal_var2) + Chr(10) + "var1: " + STR(var1));
    for (int A_Index1 = 0; A_Index1 < 5; A_Index1++) {
        var1++;
        print(var1);
    }
    

    return 0;
}