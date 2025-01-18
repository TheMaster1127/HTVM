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

std::string Trim(const std::string &inputString) {
    if (inputString.empty()) return "";
    size_t start = inputString.find_first_not_of(" \t\n\r\f\v");
    size_t end = inputString.find_last_not_of(" \t\n\r\f\v");
    return (start == std::string::npos) ? "" : inputString.substr(start, end - start + 1);
}

std::string StrSplit(const std::string &inputStr, const std::string &delimiter, int num) {
    size_t start = 0, end = 0, count = 0;
    while ((end = inputStr.find(delimiter, start)) != std::string::npos) {
        if (++count == num) {
            return inputStr.substr(start, end - start);
        }
        start = end + delimiter.length();
    }
    if (count + 1 == num) {
        return inputStr.substr(start);
    }
    return "";
}

std::string Chr(int number) {
    return (number >= 0 && number <= 0x10FFFF) ? std::string(1, static_cast<char>(number)) : "";
}

std::string RegExReplace(const std::string& inputStr, const std::string& regexPattern, const std::string& replacement) {
    std::regex re(regexPattern, std::regex_constants::ECMAScript | std::regex_constants::multiline);
    return std::regex_replace(inputStr, re, replacement);
}


std::string langToConvertTo = "py";
std::string keyWordArrayAppend = ".add";
std::string keyWordArrayPop = ".pop";
std::string keyWordArraySize = ".size";
std::string keyWordArrayInsert = ".inster";
std::string keyWordArrayRemove = ".rm";
std::string keyWordArrayIndexOf = ".indexOf";
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;; end
std::string fixArray1234(std::string line) {
    std::string out = "";
    int started = 0;
    std::vector<std::string> items1 = LoopParseFunc(line);
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        if (started == 1) {
            if (StrLen(line) == A_Index1 + 1) {
                return out;
            }
            out += A_LoopField1;
        }
        if (A_LoopField1 == "(") {
            started = 1;
        }
    }
    return out;
}
std::string fixArray123(std::string line, std::string arrayMethodStr, int mode) {
    // mode 1 = Append
    // mode 2 = Pop
    // mode 3 = Size
    // mode 4 = Insert
    // mode 5 = Remove
    // mode 6 = IndexOf
    // HTVM_Append
    // HTVM_Pop
    // HTVM_Size
    // HTVM_Insert
    // HTVM_Remove
    // HTVM_IndexOf
    if (langToConvertTo != "swift") {
        if (mode == 1) {
            return "HTVM_Append(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 2) {
            return "HTVM_Pop(" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 3) {
            return "HTVM_Size(" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 4) {
            return "HTVM_Insert(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 5) {
            return "HTVM_Remove(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 6) {
            return "HTVM_IndexOf(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
    } else {
        if (mode == 1) {
            return "HTVM_Append(&" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 2) {
            return "HTVM_Pop(&" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 3) {
            return "HTVM_Size(" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 4) {
            return "HTVM_Insert(&" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 5) {
            return "HTVM_Remove(&" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 6) {
            return "HTVM_IndexOf(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
    }
    return line;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string arrayParserTranspiler1(std::string line, std::string arrayMethodStr, int mode) {
    std::string out = "";
    std::string allDelimiters = " ()[],;:'!&|=<>+-*/^%~" + Chr(34) + Chr(9) + Chr(11);
    std::vector<std::string> arrAll;
    std::vector<std::string> items2 = LoopParseFunc(line);
    for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
        std::string A_LoopField2 = items2[A_Index2 - 0];
        arrAll.push_back(A_LoopField2);
    }
    int i1 = 0;
    std::string tempHold = "";
    int holdPos = 0;
    std::vector<int> holdPositions;
    for (int A_Index3 = 0; A_Index3 < arrAll.size() + 0; A_Index3++) {
        tempHold = "";
        if (arrAll.size() - StrLen(arrayMethodStr) + 1 == i1) {
            break;
        }
        for (int A_Index4 = 0; A_Index4 < StrLen(arrayMethodStr) + 0; A_Index4++) {
            tempHold += arrAll[A_Index4 + i1];
        }
        i1++;
        //print(tempHold)
        if (tempHold == arrayMethodStr) {
            holdPos = i1;
            //print(holdPos)
            holdPositions.push_back(holdPos);
        }
    }
    //print("===========================================")
    int holdPositionsTEMP = 0;
    for (int A_Index5 = 0; A_Index5 < holdPositions.size() + 0; A_Index5++) {
        holdPositionsTEMP = holdPositions[A_Index5];
        i1 = arrAll.size();
        tempHold = "";
        for (int A_Index6 = 0; A_Index6 < arrAll.size() + 0; A_Index6++) {
            if (holdPositionsTEMP >= i1 + 1) {
                if (InStr(allDelimiters, arrAll[i1]) == false) {
                    tempHold += arrAll[i1 - 1];
                } else {
                    break;
                }
            }
            i1--;
        }
        //print(await StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", ""))))
        holdPositions[A_Index5] = holdPositions[A_Index5] - StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", "")));
    }
    //;;;;;;;;;;;;;;;;;;
    int foundFirstParenthesis = 0;
    int ParenthesisStackOPEN = 0;
    int ParenthesisStackCLOSE = 0;
    std::vector<int> holdPositionsEnd;
    holdPositionsTEMP = 0;
    for (int A_Index7 = 0; A_Index7 < holdPositions.size() + 0; A_Index7++) {
        holdPositionsTEMP = holdPositions[A_Index7];
        i1 = 0;
        tempHold = "";
        foundFirstParenthesis = 0;
        ParenthesisStackOPEN = 0;
        ParenthesisStackCLOSE = 0;
        for (int A_Index8 = 0; A_Index8 < arrAll.size() + 0; A_Index8++) {
            if (holdPositionsTEMP < i1 + 1) {
                if (arrAll[i1] == "(") {
                    foundFirstParenthesis = 1;
                }
                if (arrAll[i1] == "(" && foundFirstParenthesis == 1) {
                    ParenthesisStackOPEN++;
                }
                if (arrAll[i1] == ")" && foundFirstParenthesis == 1) {
                    ParenthesisStackCLOSE++;
                }
                tempHold += arrAll[i1 - 1];
                if (ParenthesisStackOPEN == ParenthesisStackCLOSE && foundFirstParenthesis == 1) {
                    tempHold += arrAll[i1];
                    holdPositionsEnd.push_back(i1 + 1);
                    break;
                }
            }
            i1++;
        }
        //print(tempHold)
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    int startPosReplace = 0;
    int endPosReplace = 0;
    int beenInside = 0;
    std::string holdDebug = "";
    int holdDebugLen = 0;
    int canOut = 1;
    for (int A_Index9 = 0; A_Index9 < holdPositions.size() + 0; A_Index9++) {
        startPosReplace = holdPositions[holdPositions.size() - A_Index9 - 1];
        endPosReplace = holdPositionsEnd[holdPositions.size() - A_Index9 - 1];
        holdDebug = "";
        beenInside = 0;
        holdDebugLen = 0;
        canOut = 1;
        std::vector<std::string> items10 = LoopParseFunc(line);
        for (size_t A_Index10 = 0; A_Index10 < items10.size() + 0; A_Index10++) {
            std::string A_LoopField10 = items10[A_Index10 - 0];
            if (A_Index10 + 1 >= startPosReplace && A_Index10 + 1 <= endPosReplace) {
                holdDebug += A_LoopField10;
            }
        }
        holdDebugLen = StrLen(holdDebug);
        std::vector<std::string> items11 = LoopParseFunc(line);
        for (size_t A_Index11 = 0; A_Index11 < items11.size() + 0; A_Index11++) {
            std::string A_LoopField11 = items11[A_Index11 - 0];
            if (A_Index11 + 1 >= startPosReplace && A_Index11 + 1 <= endPosReplace) {
                beenInside++;
            }
            if (beenInside == 1) {
                out += fixArray123(holdDebug, arrayMethodStr, mode);
                canOut = 0;
            } else {
                if (canOut == 0) {
                    holdDebugLen--;
                    if (holdDebugLen == 0) {
                        canOut = 1;
                    }
                }
                if (canOut == 1) {
                    out += A_LoopField11;
                }
            }
        }
        //print("|" . holdDebug . "|")
        line = out;
        out = "";
    }
    return line;
}
std::string arrayParserTranspiler(std::string line) {
    // mode 1 = Append
    // mode 2 = Pop
    // mode 3 = Size
    // mode 4 = Insert
    // mode 5 = Remove
    // mode 6 = IndexOf
    line = arrayParserTranspiler1(line, keyWordArrayAppend + "(", 1);
    line = arrayParserTranspiler1(line, keyWordArrayPop + "(", 2);
    line = arrayParserTranspiler1(line, keyWordArraySize + "(", 3);
    line = arrayParserTranspiler1(line, keyWordArrayInsert + "(", 4);
    line = arrayParserTranspiler1(line, keyWordArrayRemove + "(", 5);
    line = arrayParserTranspiler1(line, keyWordArrayIndexOf + "(", 6);
    return line;
}
int main(int argc, char* argv[]) {
    print(arrayParserTranspiler("()()()arr123.size() + arr1234.indexOf(arr12.size() + arrr1234.add(5) + arrr1234.rm(2), arr12.size(), 2)"));
    print(arrayParserTranspiler("arr123.size()"));
    print(arrayParserTranspiler("arr123.size() + arr123.size() + arr123.size() + arr123.size()"));
    print(arrayParserTranspiler("arr1234.size() + arr123.size() + arr12345.size() + arr12.size()"));
    print(arrayParserTranspiler("arr12.size() + arr123.size() + arr1.size() + arr123.size()"));
    print(arrayParserTranspiler("arr12.size() + arr123.size() + arr1.size() + arr12366.size()"));
    return 0;
}
