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
    std::cout << value << std::endl;
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

std::string StringTrimRight(const std::string &input, int numChars) {
    return (numChars <= input.length()) ? input.substr(0, input.length() - numChars) : input;
}

std::string Chr(int number) {
    return (number >= 0 && number <= 0x10FFFF) ? std::string(1, static_cast<char>(number)) : "";
}


int main(int argc, char* argv[]) {
    

    std::string getAllKeyWords() {
        getAllKeyWordsIn();
        getFunctionNames();
        std::string allKeyWordsIn_OUT = "";
        std::string allKeyWordsIn_OUT_TEMP = "";
        std::vector<std::string> items1 = LoopParseFunc(allKeyWordsIn, "\n", "\r");
        for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
            std::string A_LoopField1 = items1[A_Index1 - 0];
            if (A_Index1 != 0 && A_Index1 != 1) {
                allKeyWordsIn_OUT += A_LoopField1 + "\n";
            }
        }
        allKeyWordsIn_OUT = StringTrimRight(allKeyWordsIn_OUT, 1);
        allKeyWordsOut = allKeyWordsIn_OUT;
    }
    

    allFunctionNamesString2 = Trim(StrReplace(allFunctionNamesString, Chr(10), "|"));
    //print("=============================")
    //print(allFunctionNamesString2)
    //print("=============================")
    

    std::string builtInCommands_temp = "";
    std::string htvmKeywords_temp = "";
    std::string staticTypes_temp = "";
    std::string builtInVars_temp = "";
    std::string operators_temp = "";
    std::string arrayMethods_temp = "";
    std::string programmingBlocksAndImport_temp = "";
    std::string htvm_trueFalseGlobalNull_temp = "";
    std::string htvm_comment_temp = "";
    std::string htvm_commentOpen1_temp = "";
    std::string htvm_commentClose2_temp = "";
    std::vector<std::string> items2 = LoopParseFunc(allKeyWordsOut3, "\n", "\r");
    for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
        std::string A_LoopField2 = items2[A_Index2 - 0];
        if (Trim(A_LoopField2) != "") {
            if (A_Index2 == 0) {
                std::vector<std::string> items3 = LoopParseFunc(A_LoopField2, "|");
                for (size_t A_Index3 = 0; A_Index3 < items3.size() + 0; A_Index3++) {
                    std::string A_LoopField3 = items3[A_Index3 - 0];
                    std::vector<std::string> items4 = LoopParseFunc(A_LoopField3, ",");
                    for (size_t A_Index4 = 0; A_Index4 < items4.size() + 0; A_Index4++) {
                        std::string A_LoopField4 = items4[A_Index4 - 0];
                        builtInCommands_temp += Trim(A_LoopField4) + "|";
                    }
                }
            }
            if (A_Index2 == 1 || A_Index2 == 2 || A_Index2 == 3 || A_Index2 == 4 || A_Index2 == 5 || A_Index2 == 64 || A_Index2 == 65 || A_Index2 == 66 || A_Index2 == 67 || A_Index2 == 68 || A_Index2 == 69 || A_Index2 == 70 || A_Index2 == 71 || A_Index2 == 72 || A_Index2 == 73 || A_Index2 == 74 || A_Index2 == 75 || A_Index2 == 76 || A_Index2 == 78 || A_Index2 == 79 || A_Index2 == 80 || A_Index2 == 81 || A_Index2 == 93 || A_Index2 == 94 || A_Index2 == 95 || A_Index2 == 96) {
                htvmKeywords_temp += A_LoopField2 + "|";
            }
            if (A_Index2 == 77) {
                allFunctionNamesString3 += "|" + Trim(A_LoopField2);
            }
            if (A_Index2 >= 49 && A_Index2 <= 63) {
                staticTypes_temp += A_LoopField2 + "|";
            }
            if (A_Index2 >= 88 && A_Index2 <= 92) {
                staticTypes_temp += A_LoopField2 + "|";
            }
            if (A_Index2 == 145 || A_Index2 == 146 || A_Index2 == 6) {
                builtInVars_temp += A_LoopField2 + "|";
            }
            if (A_Index2 >= 103 && A_Index2 <= 126) {
                operators_temp += A_LoopField2 + "|";
            }
            if (A_Index2 >= 140 && A_Index2 <= 141) {
                operators_temp += A_LoopField2 + "|";
            }
            if (A_Index2 >= 82 && A_Index2 <= 87) {
                arrayMethods_temp += Trim(StrReplace(A_LoopField2, ".", "")) + "|";
            }
            if (A_Index2 >= 7 && A_Index2 <= 43) {
                programmingBlocksAndImport_temp += A_LoopField2 + "|";
            }
            if (A_Index2 == 98) {
                htvm_comment_temp = Trim(A_LoopField2);
            }
            if (A_Index2 == 99) {
                htvm_commentOpen1_temp = Trim(A_LoopField2);
            }
            if (A_Index2 == 100) {
                htvm_commentClose2_temp = Trim(A_LoopField2);
            }
            if (A_Index2 == 46 || A_Index2 == 47 || A_Index2 == 48 || A_Index2 == 97) {
                htvm_trueFalseGlobalNull_temp += A_LoopField2 + "|";
            }
        }
    }
    builtInCommands_temp = StringTrimRight(builtInCommands_temp, 1);
    htvmKeywords_temp = StringTrimRight(htvmKeywords_temp, 1);
    staticTypes_temp = StringTrimRight(staticTypes_temp, 1);
    builtInVars_temp = StringTrimRight(builtInVars_temp, 1);
    operators_temp = StringTrimRight(operators_temp, 1);
    arrayMethods_temp = StringTrimRight(arrayMethods_temp, 1);
    programmingBlocksAndImport_temp = StringTrimRight(programmingBlocksAndImport_temp, 1);
    htvm_trueFalseGlobalNull_temp = StringTrimRight(htvm_trueFalseGlobalNull_temp, 1);
    

    return 0;
}