#include <algorithm>
#include <any>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <optional>
#include <random>
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

// Function to find the position of needle in haystack (std::string overload)
int InStr(const std::string& haystack, const std::string& needle) {
    size_t pos = haystack.find(needle);
    return (pos != std::string::npos) ? static_cast<int>(pos) + 1 : 0;
}

int Random(int min, int max) {
    // Create a random device to seed the generator
    std::random_device rd;
    
    // Create a generator seeded with the random device
    std::mt19937 gen(rd());
    
    // Define a distribution within the specified range
    std::uniform_int_distribution<> dis(min, max);
    
    // Generate and return a random number within the specified range
    return dis(gen);
}

std::string Trim(const std::string &inputString) {
    if (inputString.empty()) return "";
    size_t start = inputString.find_first_not_of(" \t\n\r\f\v");
    size_t end = inputString.find_last_not_of(" \t\n\r\f\v");
    return (start == std::string::npos) ? "" : inputString.substr(start, end - start + 1);
}

std::string StrReplace(const std::string &originalString, const std::string &find, const std::string &replaceWith) {
    std::string result = originalString;
    size_t pos = 0;
    while ((pos = result.find(find, pos)) != std::string::npos) {
        result.replace(pos, find.length(), replaceWith);
        pos += replaceWith.length();
    }
    return result;
}

int RegExMatch(const std::string& haystack, const std::string& needle) {
    std::regex re(needle);
    std::smatch match;
    if (std::regex_search(haystack, match, re)) {
        return match.position(0) + 1; // 1-based index
    }
    return 0; // No match
}



std::string callFunc(std::string funcParams) {
    // just test
    return STR(Random(12345, 1234567));
}
std::string parseFunc(std::string expresion) {
    print("=========================");
    print(expresion);
    print("=========================");
    expresion = Trim(StrReplace(expresion, " ", ""));
    expresion = Trim(StrReplace(expresion, "(", " ( "));
    expresion = Trim(StrReplace(expresion, ")", " ) "));
    expresion = Trim(StrReplace(expresion, "+", " + "));
    expresion = Trim(StrReplace(expresion, "-", " - "));
    expresion = Trim(StrReplace(expresion, "/", " / "));
    expresion = Trim(StrReplace(expresion, "*", " * "));
    expresion = Trim(StrReplace(expresion, ",", " , "));
    std::vector<std::string> expresionForFuncLookInF;
    std::vector<std::string> items1 = LoopParseFunc(expresion, " ");
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        expresionForFuncLookInF.push_back(A_LoopField1);
    }
    expresionForFuncLookInF.push_back("");
    int foundFunc = 0;
    int foundFunc2 = 0;
    int didWeSeeAfunc = 0;
    int countParentheses = 0;
    int countParenthesesOnceHelper = 0;
    int funcEndEnd = 0;
    int funcPosIndex1 = 0;
    int funcPosIndex2 = 0;
    std::string expresionReplaceHelper = "";
    std::string expresionReplaceHelper1 = "";
    for (int A_Index2 = 0; A_Index2 < 20 + 0; A_Index2++) {
        foundFunc = 0;
        foundFunc2 = 0;
        didWeSeeAfunc = 0;
        countParentheses = 0;
        countParenthesesOnceHelper = 0;
        funcEndEnd = 0;
        funcPosIndex1 = 0;
        funcPosIndex2 = 0;
        std::vector<std::string> items3 = LoopParseFunc(expresion, " ");
        for (size_t A_Index3 = 0; A_Index3 < items3.size() + 0; A_Index3++) {
            std::string A_LoopField3 = items3[A_Index3 - 0];
            if (foundFunc == 1) {
                if (RegExMatch(A_LoopField3, "^[A-Za-z_][A-Za-z0-9_]*$") && expresionForFuncLookInF[A_Index3 + 1] == "(" && foundFunc == 1) {
                    foundFunc2 = 1;
                    funcPosIndex1 = A_Index3;
                    countParentheses = 0;
                    countParenthesesOnceHelper = 0;
                    print("debug in: " + A_LoopField3);
                }
                if (A_LoopField3 == "(") {
                    countParentheses++;
                    countParenthesesOnceHelper++;
                }
                if (A_LoopField3 == ")") {
                    countParentheses--;
                }
                if (countParenthesesOnceHelper != 0) {
                    if (countParentheses == 0) {
                        funcEndEnd = 1;
                        funcPosIndex2 = A_Index3;
                        break;
                    }
                }
            }
            // Check if the variable matches the regex pattern
            if (RegExMatch(A_LoopField3, "^[A-Za-z_][A-Za-z0-9_]*$") && expresionForFuncLookInF[A_Index3 + 1] == "(" && foundFunc == 0) {
                foundFunc = 1;
                funcPosIndex1 = A_Index3;
                //print(A_LoopField3)
            }
        }
        if (foundFunc != 1) {
            print("no more funcs");
            expresion = Trim(expresion);
            // eval
            // eval
            // eval
            // eval
            // eval
            // eval
            break;
        }
        expresionReplaceHelper1 = "";
        expresionReplaceHelper = "";
        std::vector<std::string> items4 = LoopParseFunc(expresion, " ");
        for (size_t A_Index4 = 0; A_Index4 < items4.size() + 0; A_Index4++) {
            std::string A_LoopField4 = items4[A_Index4 - 0];
            if (A_Index4 >= funcPosIndex1 && A_Index4 < funcPosIndex2) {
                expresionReplaceHelper1 += A_LoopField4 + " ";
                print("found: " + A_LoopField4);
            }
            else if (A_Index4 == funcPosIndex2) {
                expresionReplaceHelper1 += A_LoopField4 + " ";
                print("found: " + A_LoopField4);
                expresionReplaceHelper += callFunc(Trim(expresionReplaceHelper1)) + " ";
            } else {
                expresionReplaceHelper += A_LoopField4 + " ";
            }
        }
        expresion = Trim(expresionReplaceHelper);
        print("=========================");
        print(expresion);
        print("=========================");
        if (InStr(Trim(expresion), " ")) {
            continue;
        } else {
            break;
        }
    }
    // eval too
    // eval too
    // eval too
    // eval too
    expresion = Trim(expresion);
    // eval too
    return expresion;
}
int main(int argc, char* argv[]) {
    print(parseFunc("-5+func1(bar1, 5+5+(58+5/2--2), func2(VAR1234R, func3(func4(5))))"));
    return 0;
}