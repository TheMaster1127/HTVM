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

// Function to find the position of needle in haystack (std::string overload)
int InStr(const std::string& haystack, const std::string& needle) {
    size_t pos = haystack.find(needle);
    return (pos != std::string::npos) ? static_cast<int>(pos) + 1 : 0;
}

size_t StrLen(const std::string& str) {
    return str.length();
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


std::string HTVMmatchStrRrplace(std::string line, std::string matchString, std::string replaceString) {
    std::string lineOut = "";
    if (!InStr(line, matchString)) {
        return line;
    }
    std::string allDelimiters = " ()[].,;:'!&|=<>+-*/^%~" + Chr(34);
    std::vector<std::string> lineArr;
    std::vector<std::string> items1 = LoopParseFunc(line);
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        lineArr.push_back(A_LoopField1);
    }
    int matchStringLEN = StrLen(matchString);
    int replaceStringLEN = StrLen(replaceString);
    std::vector<int> allPosForReplacing;
    std::string sildingLine = "";
    int isStart = 1;
    int i1 = 0;
    int hasFound = 0;
    int hasFound2 = 0;
    int isStartTrue = 0;
    int isEndTrue = 0;
    // char1 is for text outside the start
    std::string char1 = "";
    // char2 is for text inside the start
    std::string char2 = "";
    // char3 is for text inside the end
    std::string char3 = "";
    // char4 is for text outside the end
    std::string char4 = "";
    int isMatch = 0;
    sildingLine = "";
    isStart = 1;
    i1 = 0;
    hasFound = 0;
    hasFound2 = 0;
    isStartTrue = 0;
    isEndTrue = 0;
    for (int A_Index2 = 0; A_Index2 < lineArr.size() + 0; A_Index2++) {
        char1 = "";
        char2 = "";
        char3 = "";
        char4 = "";
        isMatch = 0;
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
        //print("!!!!111111111!!!!!!: " . sildingLine)
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;==================
        if (sildingLine == matchString) {
            hasFound = 1;
            if (isStart != 1) {
                //print("!!!!2222222222!!!!!!: " . lineArr[i1 - 1])
                char1 = lineArr[i1 - 1];
                //print("!!!!2222222222.555555555!!!!!!: " . lineArr[i1])
                char2 = lineArr[i1];
            } else {
                isStartTrue = 1;
            }
            if (i1 + matchStringLEN < lineArr.size()) {
                //print("!!!!3333333333.5555555555!!!!!!: " . lineArr[i1 + matchStringLEN - 1])
                char3 = lineArr[i1 + matchStringLEN - 1];
                //print("!!!!3333333333!!!!!!: " . lineArr[i1 + matchStringLEN])
                char4 = lineArr[i1 + matchStringLEN];
            } else {
                isEndTrue = 1;
            }
            if (InStr(allDelimiters, char1) || InStr(allDelimiters, char2)) {
                isStartTrue = 1;
            }
            if (InStr(allDelimiters, char3) || InStr(allDelimiters, char4)) {
                isEndTrue = 1;
            }
            if (isStartTrue == 1 && isEndTrue == 1) {
                isMatch = 1;
            }
        }
        //;;;;;;;;;;;;;;;;;;;===============
        if (isMatch == 1) {
            if (allPosForReplacing.size() > 0) {
                for (int A_Index4 = 0; A_Index4 < allPosForReplacing.size() + 0; A_Index4++) {
                    if (i1 + 1 != allPosForReplacing[A_Index4]) {
                        allPosForReplacing.push_back(i1 + 1);
                        break;
                    }
                }
            } else {
                allPosForReplacing.push_back(i1 + 1);
            }
        }
        i1++;
    }
    std::string lineTEMP = "";
    lineOut = line;
    //print(allPosForReplacing)
    if (allPosForReplacing.size() > 0) {
        // matchStringLEN
        // replaceStringLEN
        int l2 = 0;
        int currentPos = 0;
        int onceEnd = 0;
        for (int A_Index5 = 0; A_Index5 < allPosForReplacing.size() + 0; A_Index5++) {
            if (A_Index5 == 0) {
                currentPos = allPosForReplacing[A_Index5];
            } else {
                currentPos = allPosForReplacing[A_Index5] - (matchStringLEN - replaceStringLEN);
            }
            onceEnd = 0;
            std::vector<std::string> items6 = LoopParseFunc(lineOut);
            for (size_t A_Index6 = 0; A_Index6 < items6.size() + 0; A_Index6++) {
                std::string A_LoopField6 = items6[A_Index6 - 0];
                if (A_Index6 + 2 > currentPos && A_Index6 + 1 < currentPos + matchStringLEN) {
                    onceEnd++;
                    //print("DDDDDDDDDDD" . STR(A_Index6))
                    if (onceEnd == 1) {
                        lineTEMP += replaceString;
                    }
                } else {
                    lineTEMP += A_LoopField6;
                }
            }
            lineOut = lineTEMP;
            lineTEMP = "";
            //print(lineTEMP)
            l2++;
        }
    } else {
        return line;
    }
    return lineOut;
}
int main(int argc, char* argv[]) {
    std::string varQYTYWAEUSR = "";
    print(HTVMmatchStrRrplace("hi man", "hi", "hello"));
    print(HTVMmatchStrRrplace("hi man", "man", "woman"));
    print(HTVMmatchStrRrplace("func1(man.hello()) func1(man.hello())", ".hello", ".mello"));
    print(HTVMmatchStrRrplace("func1(var1 plus plus var2 plus plus var34)", "plus plus", "+"));
    print(HTVMmatchStrRrplace("var1.add() + var12.add()", ".add()", ".push()"));
    print(HTVMmatchStrRrplace("var1.add() + var12.add()", ".add()", ".pu()"));
    for (int A_Index7 = 0; A_Index7 < 10000 + 0; A_Index7++) {
        varQYTYWAEUSR += HTVMmatchStrRrplace("hi man", "hi", "hello") + "\n";
        varQYTYWAEUSR += HTVMmatchStrRrplace("hi man", "man", "woman") + "\n";
        varQYTYWAEUSR += HTVMmatchStrRrplace("func1(man.hello()) func1(man.hello())", ".hello", ".mello") + "\n";
        varQYTYWAEUSR += HTVMmatchStrRrplace("func1(var1 plus plus var2 plus plus var34)", "plus plus", "+") + "\n";
        varQYTYWAEUSR += HTVMmatchStrRrplace("var1.add() + var12.add()", ".add()", ".push()") + "\n";
        varQYTYWAEUSR += HTVMmatchStrRrplace("var1.add() + var12.add()", ".add()", ".pu()") + "\n";
    }
    varQYTYWAEUSR = StringTrimRight(varQYTYWAEUSR, 1);
    return 0;
}
