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


int main(int argc, char* argv[]) {
    std::string htCode = "htCode";
    std::vector<std::string> fixGoManGoIsSoAnnoyingBroooFurure;
    std::vector<std::string> items1 = LoopParseFunc(htCode, "\n", "\r");
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        fixGoManGoIsSoAnnoyingBroooFurure.push_back(A_LoopField1);
    }
    fixGoManGoIsSoAnnoyingBroooFurure.push_back(" ");
    int fixGoManGoIsSoAnnoyingBroooSkip = 0;
    int fixGoManGoIsSoAnnoyingBroooCount = 0;
    std::string fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
    std::string fixGoManGoIsSoAnnoyingBrooo = "";
    std::vector<std::string> items2 = LoopParseFunc(htCode, "\n", "\r");
    for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
        std::string A_LoopField2 = items2[A_Index2 - 0];
        if (Trim(A_LoopField2) == "}" && SubStr(Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index2 + 1]), 1, StrLen("else if ")) == "else if ") {
            fixGoManGoIsSoAnnoyingBroooSkip = 1;
            std::vector<std::string> items3 = LoopParseFunc(fixGoManGoIsSoAnnoyingBroooFurure[A_Index2 + 1]);
            for (size_t A_Index3 = 0; A_Index3 < items3.size() + 0; A_Index3++) {
                std::string A_LoopField3 = items3[A_Index3 - 0];
                if (A_LoopField3 == " ") {
                    fixGoManGoIsSoAnnoyingBroooCount++;
                } else {
                    break;
                }
            }
            for (int A_Index4 = 0; A_Index4 < fixGoManGoIsSoAnnoyingBroooCount + 0; A_Index4++) {
                fixGoManGoIsSoAnnoyingBroooCountSpaceses += " ";
            }
            fixGoManGoIsSoAnnoyingBrooo += fixGoManGoIsSoAnnoyingBroooCountSpaceses + "} " + Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index2 + 1]) + "\n";
        } else {
            if (fixGoManGoIsSoAnnoyingBroooSkip == 1) {
                fixGoManGoIsSoAnnoyingBroooSkip = 0;
                fixGoManGoIsSoAnnoyingBrooo += A_LoopField2 + "\n";
            }
        }
    }
    htCode = StringTrimRight(fixGoManGoIsSoAnnoyingBrooo, 1);
    return 0;
}