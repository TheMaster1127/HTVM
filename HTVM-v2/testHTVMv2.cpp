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

// Overload for std::vector<std::string>
void HTVM_Append(std::vector<std::string>& arr, const std::string& value) {
    arr.push_back(value);
}
// Overload for const char* (so you can pass string literals)
void HTVM_Append(std::vector<std::string>& arr, const char* value) {
    arr.push_back(std::string(value));
}
// General template for other vector types
template <typename T>
void HTVM_Append(std::vector<T>& arr, const T& value) {
    arr.push_back(value);
}

template <typename T>
size_t HTVM_Size(const std::vector<T>& arr) {
    return arr.size();
}


std::string func1(std::string var1) {
    return var1 + var1;
}
void func2(std::string var1) {
    print(var1 + var1);
}
void func3(std::string var1, std::string var2 = "hello") {
    print(var1 + " " + var2);
}
int main(int argc, char* argv[]) {
    print(func1("hi1"));
    func2("hi2");
    func3("hi3");
    func3("hi3", "hello3");
    int var1 = 0;
    std::vector<bool> myArr0;
    HTVM_Append(myArr0, true);
    HTVM_Append(myArr0, false);
    HTVM_Append(myArr0, true);
    std::vector<int> myArr = {5, 6, 7};
    for (int A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        var1 = 6;
        HTVM_Append(myArr, A_Index1);
    }
    for (int A_Index2 = 0; A_Index2 < HTVM_Size(myArr) + 0; A_Index2++) {
        print(myArr[A_Index2]);
    }
    for (int A_Index3 = 0; A_Index3 < HTVM_Size(myArr0) + 0; A_Index3++) {
        print(myArr0[A_Index3]);
    }
    if (var1 == 6) {
        print(var1);
    }
    else if (var1 == 7) {
        print(var1);
    }
    std::string var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn";
    std::vector<std::string> items4 = LoopParseFunc(var123, "\n", "\r");
    for (size_t A_Index4 = 0; A_Index4 < items4.size() + 0; A_Index4++) {
        std::string A_LoopField4 = items4[A_Index4 - 0];
        if (A_Index4 == 0) {
            print(A_Index4);
        }
        print(A_LoopField4);
    }
    print("==================");
    std::string var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg";
    std::vector<std::string> items5 = LoopParseFunc(var1234, ",");
    for (size_t A_Index5 = 0; A_Index5 < items5.size() + 0; A_Index5++) {
        std::string A_LoopField5 = items5[A_Index5 - 0];
        if (A_Index5 == 0) {
            print(A_Index5);
        }
        print(A_LoopField5);
    }
    print("==================");
    std::string var12345 = "hello";
    std::vector<std::string> items6 = LoopParseFunc(var12345);
    for (size_t A_Index6 = 0; A_Index6 < items6.size() + 0; A_Index6++) {
        std::string A_LoopField6 = items6[A_Index6 - 0];
        print(A_LoopField6);
    }
    return 0;
}