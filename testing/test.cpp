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
#include <regex>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

// Function to escape special characters for regex
std::string escapeRegex(const std::string& str) {
    static const std::regex specialChars{R"([-[\]{}()*+?.,\^$|#\s])"};
    return std::regex_replace(str, specialChars, R"(\$&)");
}
// Function to split a string based on delimiters
std::vector<std::string> LoopParseFunc(const std::string& var, const std::string& delimiter1 = "", const std::string& delimiter2 = "") {
    std::vector<std::string> items;
    if (delimiter1.empty() && delimiter2.empty()) {
        // If no delimiters are provided, return a list of characters
        for (char c : var) {
            items.push_back(std::string(1, c));
        }
    } else {
        // Escape delimiters for regex
        std::string escapedDelimiters = escapeRegex(delimiter1 + delimiter2);
        // Construct the regular expression pattern for splitting the string
        std::string pattern = "[" + escapedDelimiters + "]+";
        std::regex regexPattern(pattern);
        std::sregex_token_iterator iter(var.begin(), var.end(), regexPattern, -1);
        std::sregex_token_iterator end;
        while (iter != end) {
            items.push_back(*iter++);
        }
    }
    return items;
}

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

void HTVM_Append(std::vector<std::string>& arr, const std::string& value) {
    arr.push_back(value);
}
void HTVM_Append(std::vector<std::string>& arr, const char* value) {
    arr.push_back(std::string(value));
}
void HTVM_Append(std::vector<int>& arr, int value) {
    arr.push_back(value);
}
void HTVM_Append(std::vector<float>& arr, float value) {
    arr.push_back(value);
}
void HTVM_Append(std::vector<bool>& arr, bool value) {
    arr.push_back(value);
}

size_t HTVM_Size(const std::vector<std::string>& arr) {
    return arr.size();
}
size_t HTVM_Size(const std::vector<int>& arr) {
    return arr.size();
}
size_t HTVM_Size(const std::vector<float>& arr) {
    return arr.size();
}
size_t HTVM_Size(const std::vector<bool>& arr) {
    return arr.size();
}


// This is a preview of your language and how it will look.
// Here's how types will appear if you only define them:
int varName1 = 0;
std::string varName2 = "";
bool varName3 = false;
float varName4 = 0.00f;
int8_t varName5 = 0;
int16_t varName6 = 0;
int32_t varName7 = 0;
int64_t varName8 = 0LL;
// Alternatively, you can define them like this:
int varName9 = 34;
// Here's how to define a function with static types when converting to statically typed languages like:
// TypeScript, C++, Go, C#, Java, Kotlin, Nim, Swift, and Dart.
// However, even if you're not targeting a statically typed language (e.g. JavaScript or Python),
// the types will be stripped away automatically and the function will still work as expected.
void funcName1(int paramVar1, std::string paramVar2 = "", bool paramVar3 = false, float paramVar4 = 1.5f) {
    // This is how the global keyword works if we convert to Python and AutoHotKey.
    // But even if we don't, it will just be removed, so you can add it if you want to convert to Python and AutoHotKey as well.
    // Here's how if, else if, and else statements will look:
    if (varName1 == paramVar1) {
        print("varName1 is equal to paramVar1");
    }
    else if (varName1 != paramVar1 || varName1 <= paramVar1) {
        print("varName1 is less than or equal to paramVar1");
    } else {
        print("varName1 is NOT less than or equal to paramVar1 or something else");
    }
    // this is how the return keyword will look like in your lang
    return;
}
// This is where the main function will start. It's just a label, so don't worry.
int main(int argc, char* argv[]) {
    funcName1(varName9);
    // this is how a while loop works in your lang
    bool var1 = false;
    while (var1 == false) {
        print("we are inside the while loop");
        var1 = true;
    }
    print("we are outside the while loop");
    // this is how to use a loop whit arrays
    std::vector<std::string> array123 = {"hey"};
    HTVM_Append(array123, "hello");
    HTVM_Append(array123, "how");
    HTVM_Append(array123, "are");
    HTVM_Append(array123, "you");
    HTVM_Append(array123, "doing");
    for (int A_Index1 = 0; A_Index1 < HTVM_Size(array123); A_Index1++) {
        print("iteration: " + STR(A_Index1));
        print("Item: " + array123[A_Index1]);
    }
    print("this is how the escape char looks like \nthis is a new line");
    /*
    this is a comment block
    this is a comment block
    */
    // this is how to use an AutoHotKey like Loop
    for (int A_Index2 = 0; A_Index2 < 10; A_Index2++) {
        if (A_Index2 % 2 == 0) {
            continue;
        }
        print(A_Index2);
    }
    // this is how to use an AutoHotKey like infinite Loop
    for (int A_Index3 = 0; ; A_Index3++) {
        if (A_Index3 == 5) {
            break;
        } else {
            print(A_Index3);
        }
    }
    // this is how to use an AutoHotKey like Loop, parse
    std::string someText = "hello how are you doing\ntoday we are good.";
    std::vector<std::string> items4 = LoopParseFunc(someText, " ", "\n");
    for (size_t A_Index4 = 0; A_Index4 < items4.size(); A_Index4++) {
        std::string A_LoopField4 = items4[A_Index4 - 0];
        print(A_LoopField4);
    }
    // Error Handling
    try {
        throw std::runtime_error("Something went wrong!");
    }
    catch (const std::exception& e) {
        print(e.what());
    }
    if ("finally dosent exist in c++" == "finally dosent exist in c++") {
        print("Finally block executed");
    }
    

    return 0;
}