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

// Function to find the position of needle in haystack (std::string overload)
int InStr(const std::string& haystack, const std::string& needle) {
    size_t pos = haystack.find(needle);
    return (pos != std::string::npos) ? static_cast<int>(pos) + 1 : 0;
}

size_t StrLen(const std::string& str) {
    return str.length();
}


std::string HTVMmatchStrRrplace(std::string line, std::string matchString, std::string replaceString) {
    if (!InStr(line, matchString)) {
        print("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
        return line;
    }
    std::string allDelimiters = " ()[].";
    std::vector<std::string> lineArr;
    std::vector<std::string> items1 = LoopParseFunc(line);
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        lineArr.push_back(A_LoopField1);
    }
    int matchStringLEN = StrLen(matchString);
    std::string sildingLine = "";
    int isStart = 1;
    int isEnd = 0;
    int i1 = 0;
    for (int A_Index2 = 0; A_Index2 < lineArr.size() + 0; A_Index2++) {
        if (A_Index2 == lineArr.size() - 1) {
            isEnd = 1;
        }
        if (A_Index2 != 0) {
            isStart = 0;
        }
        sildingLine = "";
        for (int A_Index3 = 0; A_Index3 < matchStringLEN + 0; A_Index3++) {
            if (A_Index3 + i1 <= lineArr.size() - 1) {
                sildingLine += lineArr[A_Index3 + i1];
            }
        }
        if (StrLen(sildingLine) < matchStringLEN) {
            break;
        }
        print(sildingLine);
        i1++;
    }
    return "0";
}
int main(int argc, char* argv[]) {
    print(HTVMmatchStrRrplace("hi man", "hi", "hello"));
    print(HTVMmatchStrRrplace("hi man", "man", "woman"));
    print(HTVMmatchStrRrplace("func1(man.hello())", ".hello", ".mello"));
    print(HTVMmatchStrRrplace("func1(var1 plus plus var2)", "plus plus", "+"));
    return 0;
}