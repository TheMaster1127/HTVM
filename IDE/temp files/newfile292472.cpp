#include <algorithm>
#include <any>
#include <cctype>
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

// Function to get input from the user, similar to Python's input() function
std::string input(const std::string& prompt) {
    std::string userInput;
    std::cout << prompt; // Display the prompt to the user
    std::getline(std::cin, userInput); // Get the entire line of input
    return userInput;
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

std::string StrReplace(const std::string &originalString, const std::string &find, const std::string &replaceWith) {
    std::string result = originalString;
    size_t pos = 0;
    while ((pos = result.find(find, pos)) != std::string::npos) {
        result.replace(pos, find.length(), replaceWith);
        pos += replaceWith.length();
    }
    return result;
}

std::string StringTrimLeft(const std::string &input, int numChars) {
    return (numChars <= input.length()) ? input.substr(numChars) : input;
}

std::string StringTrimRight(const std::string &input, int numChars) {
    return (numChars <= input.length()) ? input.substr(0, input.length() - numChars) : input;
}

std::string StrLower(const std::string &string) {
    std::string result = string;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string Chr(int number) {
    return (number >= 0 && number <= 0x10FFFF) ? std::string(1, static_cast<char>(number)) : "";
}

int Mod(int dividend, int divisor) {
    return dividend % divisor;
}



// Helper function to create spaces
std::string spaces(int n) {
    std::string s = "";
    if (n != 0) {
        for (int A_Index1 = 0; A_Index1 < n + 0; A_Index1++) {
            s += " ";
        }
    }
    return s;
}
// Define the function to check odd spaces at the beginning
std::string CheckOddLeadingSpaces(std::string string123) {
    // Initialize a variable to count the spaces
    int spaceCount = 0;
    // Loop through the string one character at a time
    std::vector<std::string> items2 = LoopParseFunc(string123);
    for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
        std::string A_LoopField2 = items2[A_Index2 - 0];
        // Check if the current character is a space
        if (A_LoopField2 == Chr(32)) {
            spaceCount++;
        } else {
            // When we hit a non-space character, break the loop
            break;
        }
    }
    // Return true if the number of spaces is odd, false otherwise
    std::string sdsfawasd = STR(Mod(spaceCount, 2) == 1);
    //MsgBox, % sdsfawasd
    return sdsfawasd;
}
std::string LTrim(std::string input) {
    std::string result = "";
    bool foundNonSpace = false;
    std::vector<std::string> items3 = LoopParseFunc(input);
    for (size_t A_Index3 = 0; A_Index3 < items3.size() + 0; A_Index3++) {
        std::string A_LoopField3 = items3[A_Index3 - 0];
        if (A_LoopField3 != " " || foundNonSpace) {
            result += A_LoopField3;
            foundNonSpace = true;
        }
    }
    return result;
}
std::string getLastChar(std::string strippedString) {
    std::string lastChar;
    std::vector<std::string> items4 = LoopParseFunc(strippedString);
    for (size_t A_Index4 = 0; A_Index4 < items4.size() + 0; A_Index4++) {
        std::string A_LoopField4 = items4[A_Index4 - 0];
        lastChar = A_LoopField4;
    }
    return lastChar;
}
std::string AddCurlyBraces(std::string pythonCode) {
    pythonCode = StrReplace(pythonCode, A_Tab, "    ");
    std::string result = "";
    int indentLevel = 0;
    int indent;
    std::string line;
    std::string stripped;
    std::vector<std::string> items5 = LoopParseFunc(pythonCode, "\n", "\r");
    for (size_t A_Index5 = 0; A_Index5 < items5.size() + 0; A_Index5++) {
        std::string A_LoopField5 = items5[A_Index5 - 0];
        line = A_LoopField5;
        stripped = Trim(line);
        if (stripped == "") {
            result += line + "\n";
            continue;
        }
        // Count leading spaces
        indent = StrLen(line) - StrLen(LTrim(line));
        //MsgBox, % indent
        // Close braces for unindents
        for (int A_Index6 = 0; ; A_Index6++) {
            if (indentLevel <= indent) {
                break;
            }
            indentLevel -= 4;
            result += spaces(indentLevel) + "}\n";
        }
        // Add opening brace for new blocks
        if (getLastChar(stripped) == ":" && SubStr(StrLower(Trim(A_LoopField5)), 1, StrLen(StrLower(keyWordComment))) != StrLower(keyWordComment)) {
            result += SubStr(line, 1, -1) + " {\n";
            indentLevel += 4;
        } else {
            result += line + "\n";
        }
    }
    // Close any remaining open braces
    for (int A_Index7 = 0; ; A_Index7++) {
        if (indentLevel <= 0) {
            break;
        }
        indentLevel -= 4;
        result += spaces(indentLevel) + "}\n";
    }
    return result;
}
std::string RepeatSpaces(int count) {
    std::string spaces = "";
    for (int A_Index8 = 0; A_Index8 < count + 0; A_Index8++) {
        spaces += Chr(32);
    }
    return spaces;
}
std::string indent_nested_curly_braces(std::string input_string, int modeCurlyBracesOn) {
    int indent_size = 4;
    int current_indent = 0;
    std::string result;
    std::string trimmed_line;
    std::string resultOut;
    //MsgBox, % input_string
    std::vector<std::string> items9 = LoopParseFunc(input_string, "\n", "\r");
    for (size_t A_Index9 = 0; A_Index9 < items9.size() + 0; A_Index9++) {
        std::string A_LoopField9 = items9[A_Index9 - 0];
        trimmed_line = Trim(A_LoopField9);
        if (trimmed_line == Chr(123)) {
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n";
            current_indent = current_indent + indent_size;
        }
        else if (trimmed_line == Chr(125)) {
            current_indent = current_indent - indent_size;
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n";
        } else {
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n";
        }
    }
    if (modeCurlyBracesOn == 0) {
        std::string resultOut;
        std::vector<std::string> items10 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index10 = 0; A_Index10 < items10.size() + 0; A_Index10++) {
            std::string A_LoopField10 = items10[A_Index10 - 0];
            if (Trim(A_LoopField10) != "{" && Trim(A_LoopField10) != "}") {
                resultOut += A_LoopField10 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
    } else {
        // format curly braces in a K&R style
        std::vector<std::string> lookIntoFurture;
        std::vector<std::string> items11 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index11 = 0; A_Index11 < items11.size() + 0; A_Index11++) {
            std::string A_LoopField11 = items11[A_Index11 - 0];
            std::vector<std::string> lookIntoFurture += Trim(A_LoopField11);
        }
        std::vector<std::string> lookIntoFurture += " ";
        std::string resultOut;
        int skipNext = 0;
        std::vector<std::string> items12 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index12 = 0; A_Index12 < items12.size() + 0; A_Index12++) {
            std::string A_LoopField12 = items12[A_Index12 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (Trim(lookIntoFurture[A_Index12 + 1]) == "{") {
                resultOut += A_LoopField12 + " {\n";
                skipNext = 2;
            }
            if (skipNext == 0) {
                resultOut += A_LoopField12 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
        std::vector<std::string> lookIntoFurture2;
        std::vector<std::string> items13 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index13 = 0; A_Index13 < items13.size() + 0; A_Index13++) {
            std::string A_LoopField13 = items13[A_Index13 - 0];
            std::vector<std::string> lookIntoFurture2 += Trim(A_LoopField13);
        }
        std::vector<std::string> lookIntoFurture2 += " ";
        resultOut = "";
        skipNext = 0;
        std::string addSpacesAtTheBegginig;
        std::vector<std::string> items14 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index14 = 0; A_Index14 < items14.size() + 0; A_Index14++) {
            std::string A_LoopField14 = items14[A_Index14 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (Trim(A_LoopField14) == "}" && Trim(lookIntoFurture2[A_Index14 + 1]) == "else {") {
                skipNext = 2;
                addSpacesAtTheBegginig = "";
                std::vector<std::string> items15 = LoopParseFunc(A_LoopField14);
                for (size_t A_Index15 = 0; A_Index15 < items15.size() + 0; A_Index15++) {
                    std::string A_LoopField15 = items15[A_Index15 - 0];
                    if (A_LoopField15 == " ") {
                        if (A_LoopField15 != " ") {
                            break;
                        }
                        addSpacesAtTheBegginig += A_LoopField15;
                    }
                }
                resultOut += addSpacesAtTheBegginig + "} else {\n";
            }
            if (skipNext == 0) {
                resultOut += A_LoopField14 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
    }
    resultOut = "";
    std::string ALoopField;
    std::vector<std::string> items16 = LoopParseFunc(result, "\n", "\r");
    for (size_t A_Index16 = 0; A_Index16 < items16.size() + 0; A_Index16++) {
        std::string A_LoopField16 = items16[A_Index16 - 0];
        if (CheckOddLeadingSpaces(A_LoopField16) == "1") {
            ALoopField = StringTrimLeft(A_LoopField16, 1);
            resultOut += ALoopField + "\n";
        } else {
            resultOut += A_LoopField16 + "\n";
        }
    }
    result = StringTrimRight(resultOut, 1);
    // Return the result
    return result;
}
int main(int argc, char* argv[]) {
    return 0;
}