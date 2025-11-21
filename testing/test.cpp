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


int A_SUCCESS = 0;
int A_SUCCESS_WEIGHTED = 0;
int A_TOTAL_WEIGHT = 0;
bool A_SUCCESS_ALL = false;
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
    // ===================================
    // HTVM: LINER Demo – Game Fight Eligibility
    // ===================================
    // --- Variables ---
    bool hasStrongWeapon = true;
    bool hasShield = false;
    int health = 75;
    int gold = 120;
    bool isBuffed = true;
    bool enemyNearby = true;
    // --- LINER Block for Fight Eligibility ---
    A_SUCCESS = 0;
    A_SUCCESS_WEIGHTED = 0;
    A_TOTAL_WEIGHT = 16;
    A_SUCCESS_ALL = false;
    if (hasStrongWeapon) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 5;
    }
    if (hasShield) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 2;
    }
    if (health > 50) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 3;
    }
    if (gold >= 100) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 1;
    }
    if (isBuffed) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 2;
    }
    if (enemyNearby) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 3;
    }
    if (A_SUCCESS_WEIGHTED == A_TOTAL_WEIGHT) {
        A_SUCCESS_ALL = true;
    }
    // --- Output Results ---
    print("=== Fight Eligibility Evaluation ===");
    print("Raw success count: " + STR(A_SUCCESS));
    print("Weighted success: " + STR(A_SUCCESS_WEIGHTED));
    print("Total possible weight: " + STR(A_TOTAL_WEIGHT));
    print("All passed? " + STR(A_SUCCESS_ALL));
    // --- Single-condition LINER example ---
    A_SUCCESS = 0;
    A_SUCCESS_WEIGHTED = 0;
    A_TOTAL_WEIGHT = 1;
    A_SUCCESS_ALL = false;
    if (hasShield) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 1;
    }
    if (A_SUCCESS_WEIGHTED == A_TOTAL_WEIGHT) {
        A_SUCCESS_ALL = true;
    }
    print("=== Single-condition Check ===");
    print("Raw success count: " + STR(A_SUCCESS));
    print("Weighted success: " + STR(A_SUCCESS_WEIGHTED));
    print("Total possible weight: " + STR(A_TOTAL_WEIGHT));
    print("All passed? " + STR(A_SUCCESS_ALL));
    print(myOwn_var2);
    

    return 0;
}