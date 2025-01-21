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

size_t StrLen(const std::string& str) {
    return str.length();
}

std::string SubStr(const std::string& str, int startPos, int length = -1) {
    std::string result;
    size_t strLen = str.size();
    // Handle negative starting positions
    if (startPos < 0) {
        startPos += strLen;
        if (startPos < 0) startPos = 0;
    } else {
        if (startPos > static_cast<int>(strLen)) return ""; // Starting position beyond string length
        startPos -= 1; // Convert to 0-based index
    }
    // Handle length
    if (length < 0) {
        length = strLen - startPos; // Length to end of string
    } else if (startPos + length > static_cast<int>(strLen)) {
        length = strLen - startPos; // Adjust length to fit within the string
    }
    // Extract substring
    result = str.substr(startPos, length);
    return result;
}

std::string Trim(const std::string &inputString) {
    if (inputString.empty()) return "";
    size_t start = inputString.find_first_not_of(" \t\n\r\f\v");
    size_t end = inputString.find_last_not_of(" \t\n\r\f\v");
    return (start == std::string::npos) ? "" : inputString.substr(start, end - start + 1);
}

std::string StringTrimRight(const std::string &input, int numChars) {
    return (numChars <= input.length()) ? input.substr(0, input.length() - numChars) : input;
}

std::string Chr(int number) {
    return (number >= 0 && number <= 0x10FFFF) ? std::string(1, static_cast<char>(number)) : "";
}


int main(int argc, char* argv[]) {
    std::string htCode = "-- Function definition with a while loop and if-elseif-else inside it\nfunction myFunction()\n    local x = 1\n    while x " + Chr(60) + "= 3 do\n        -- if-elseif-else inside the while loop\n        if x == 1 then\n            print(" + Chr(34) + "x is 1" + Chr(34) + ")\n        end\n        elseif x == 2 then\n            print(" + Chr(34) + "x is 2" + Chr(34) + ")\n        end\n        else\n            print(" + Chr(34) + "x is 3" + Chr(34) + ")\n        end\n        x = x + 1\n    end\nend\n\n-- Call the function\nmyFunction()";
    std::vector<std::string> nextWordEndFix;
    std::vector<std::string> items1 = LoopParseFunc(htCode, "\n", "\r");
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        nextWordEndFix.push_back(A_LoopField1);
    }
    nextWordEndFix.push_back(" ");
    std::string nextWordEndFixOut = "";
    std::vector<std::string> items2 = LoopParseFunc(htCode, "\n", "\r");
    for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
        std::string A_LoopField2 = items2[A_Index2 - 0];
        if (Trim(A_LoopField2) == "end" && SubStr(Trim(nextWordEndFix[A_Index2 + 1]), 1, StrLen("elseif ")) == "elseif " || Trim(A_LoopField2) == "end" && Trim(nextWordEndFix[A_Index2 + 1]) == "else") {
            nextWordEndFixOut += "";
        } else {
            nextWordEndFixOut += A_LoopField2 + "\n";
        }
    }
    htCode = StringTrimRight(nextWordEndFixOut, 1);
    print(htCode);
    return 0;
}
