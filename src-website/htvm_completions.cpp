#include <algorithm>
#include <any>
#include <cstdint>
#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
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
                if (A_Index1 == 149) {
                    break;
                }
                if (A_Index1 == 2) {
                    std::vector<std::string> items2 = LoopParseFunc(A_LoopField1, "|");
                    for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
                        std::string A_LoopField2 = items2[A_Index2 - 0];
                        std::vector<std::string> items3 = LoopParseFunc(A_LoopField2, ",");
                        for (size_t A_Index3 = 0; A_Index3 < items3.size() + 0; A_Index3++) {
                            std::string A_LoopField3 = items3[A_Index3 - 0];
                            if (A_Index3 == 0) {
                                allKeyWordsIn_OUT += A_LoopField3 + "\n";
                                break;
                            }
                        }
                    }
                } else {
                    allKeyWordsIn_OUT_TEMP = A_LoopField1;
                    

                    if (isValidStart) {
                        allKeyWordsIn_OUT += A_LoopField1 + "\n";
                    }
                }
            }
        }
        allKeyWordsOut = allKeyWordsIn_OUT + allFunctionNamesString;
    }
    

    return 0;
}