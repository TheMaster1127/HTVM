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


// This is a preview of your language and how it will look.
// Here's how types will appear if you only define them:
int varName1;
std::string varName2;
bool varName3;
float varName4;
int8_t varName5;
int16_t varName6;
int32_t varName7;
long long varName8;
// Alternatively, you can define them like this:
int varName9 = 34;
// Here is how to define a function with static types if you convert to C++.
// However, it will still work even if you are not converting to C++; types will be stripped away.
void funcName1(int paramVar1, std::string paramVar2 = "", bool paramVar3 = false, float paramVar4 = 1.5) {
    // This is how the global keyword works if we convert to Python.
    // But even if we don't, it will just be removed, so you can add it if you want to convert to Python as well.
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
int main(int argc, char* argv[]) {
    funcName1(varName9);
    // this is how a while loop works in your lang
    bool var1 = false;
    while (var1 == false) {
        print("we are inside the while loop");
        var1 = true;
    }
    print("we are outside the while loop");
    // this is how to use a for loop
    int indexMax = 5;
    // this is how to use a for loop normal
    for (int indexName = 0; indexName < indexMax; indexName++) {
        print("iteration: " + STR(indexName));
    }
    // this is how to use a for loop whit arrays
    std::vector<std::string> array;
    array.push_back("hello");
    array.push_back("how");
    array.push_back("are");
    array.push_back("you");
    array.push_back("doing");
    for (int indexName = 0; indexName < array.size(); indexName++) {
        print("iteration: " + STR(indexName));
        print("Item: " + array[indexName]);
    }
    print("this is how the escape char looks like \nthis is a new line");
    /*
    this is a comment block
    this is a comment block
    */
    // this is how to use an AutoHotKey like Loop
    for (int A_Index1 = 0; A_Index1 < 10 + 0; A_Index1++) {
        if (A_Index1 % 2 == 0) {
            continue;
        }
        print(A_Index1);
    }
    // this is how to use an AutoHotKey like infinite Loop
    for (int A_Index2 = 0; ; A_Index2++) {
        if (A_Index2 == 5) {
            break;
        } else {
            print(A_Index2);
        }
    }
    // this is how to use an AutoHotKey like Loop, parse
    std::string someText = "hello how are you doing\ntoday we are good.";
    std::vector<std::string> items3 = LoopParseFunc(someText, " ", "\n");
    for (size_t A_Index3 = 0; A_Index3 < items3.size() + 0; A_Index3++) {
        std::string A_LoopField3 = items3[A_Index3 - 0];
        print(A_LoopField3);
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