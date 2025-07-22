#if __has_include("srell.hpp")
    #include "srell.hpp"
    #define USE_POWERFUL_REGEX 1
    #pragma message("SUCCESS: Compiling with powerful SRELL regex engine. Lookbehinds will work.")
#else
    #include <regex>
    #define USE_POWERFUL_REGEX 0
    #pragma message("WARNING: srell.hpp not found. Falling back to limited std::regex. Lookbehinds will NOT work.")
#endif

#include <algorithm>
#include <any>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_set>
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

// Print function for const char*
void print(const char* value) {
    std::cout << std::string(value) << std::endl;
}
// Handle signed 8-bit integers
void print(int8_t value) {
    std::cout << static_cast<int>(value) << std::endl;
}
// Handle unsigned 8-bit integers
void print(uint8_t value) {
    std::cout << static_cast<unsigned int>(value) << std::endl;
}
// Generic print function fallback
template <typename T>
void print(const T& value) {
    std::cout << value << std::endl;
}

// Convert std::string to int
int INT(const std::string& str) {
    std::istringstream iss(str);
    int value;
    iss >> value;
    return value;
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
std::string STR(const std::string& value) {
    return value;
}

// Convert std::string to float
float FLOAT(const std::string& str) {
    std::istringstream iss(str);
    float value;
    iss >> value;
    return value;
}

// Function to find the position of needle in haystack (std::string overload)
int InStr(const std::string& haystack, const std::string& needle) {
    size_t pos = haystack.find(needle);
    return (pos != std::string::npos) ? static_cast<int>(pos) + 1 : 0;
}

// Function to get input from the user, similar to Python's input() function
std::string input(const std::string& prompt) {
    std::string userInput;
    std::cout << prompt; // Display the prompt to the user
    std::getline(std::cin, userInput); // Get the entire line of input
    return userInput;
}

std::string FileRead(const std::string& path) {
    std::ifstream file;
    std::filesystem::path full_path;
    // Check if the file path is an absolute path
    if (std::filesystem::path(path).is_absolute()) {
        full_path = path;
    } else {
        // If it's not a full path, prepend the current working directory
        full_path = std::filesystem::current_path() / path;
    }
    // Open the file
    file.open(full_path);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open the file.");
    }
    // Read the file content into a string
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + '\n';
    }
    file.close();
    return content;
}

bool FileAppend(const std::string& content, const std::string& path) {
    std::ofstream file;
    // Open the file in append mode
    file.open(path, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file for appending." << std::endl;
        return false;
    }
    // Append the content to the file
    file << content;
    // Close the file
    file.close();
    return true;
}

bool FileDelete(const std::string& path) {
    std::filesystem::path file_path(path);
    // Check if the file exists
    if (!std::filesystem::exists(file_path)) {
        return false;
    }
    // Attempt to remove the file
    if (!std::filesystem::remove(file_path)) {
        return false;
    }
    return true;
}

size_t StrLen(const std::string& str) {
    return str.length();
}

// For float input
float Exp(float value) {
    return expf(value);
}
// For double input
double Exp(double value) {
    return std::exp(value);
}
// For long double input
long double Exp(long double value) {
    return expl(value);
}
// For int input, convert to double
double Exp(int value) {
    return std::exp(static_cast<double>(value));
}

// For float input
float Log(float value) {
    return log10f(value);
}
// For double input
double Log(double value) {
    return std::log10(value);
}
// For long double input
long double Log(long double value) {
    return log10l(value);
}
// For int input, convert to double
double Log(int value) {
    return std::log10(static_cast<double>(value));
}

std::string SubStr(const std::string& str, int startPos, int length = -1) {
    std::string result;
    size_t strLen = str.size();
    // Handle negative starting positions (counting from the end)
    if (startPos < 0) {
        startPos = strLen + startPos;
        if (startPos < 0) startPos = 0;  // Ensure it doesn't go beyond the start of the string
    }
    else {
        startPos -= 1; // Convert to 0-based index for internal operations
    }
    // Handle length
    if (length < 0) {
        length = strLen - startPos; // Length to the end of the string
    } else if (startPos + length > static_cast<int>(strLen)) {
        length = strLen - startPos; // Adjust length to fit within the string
    }
    // Extract the substring
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

int Mod(int dividend, int divisor) {
    return dividend % divisor;
}

// Helper function to trim whitespace from both ends of a string
std::string trim(const std::string& str) {
    const std::string whitespace = " \t\n\r\f\v";
    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}
// Helper function to convert string to lowercase
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}
// Function to sort case-insensitively but ensure lowercase items come last
bool customSortCompare(const std::string& a, const std::string& b) {
    std::string lowerA = toLower(a);
    std::string lowerB = toLower(b);
    if (lowerA == lowerB) {
        // If case-insensitive equivalent, ensure lowercase items come last
        if (std::islower(a[0]) && std::isupper(b[0])) {
            return false; // a should come after b
        } else if (std::isupper(a[0]) && std::islower(b[0])) {
            return true; // a should come before b
        }
        return a < b; // Otherwise, sort lexicographically
    }
    return lowerA < lowerB;
}
// Function to remove exact duplicates (case-sensitive)
std::vector<std::string> removeExactDuplicates(const std::vector<std::string>& items) {
    std::unordered_set<std::string> seen;
    std::vector<std::string> uniqueItems;
    for (const auto& item : items) {
        if (seen.find(item) == seen.end()) {
            seen.insert(item);
            uniqueItems.push_back(item);
        }
    }
    return uniqueItems;
}
// Main sorting function
std::string Sort(const std::string& input, const std::string& options) {
    std::string delimiter = "\n";
    bool caseInsensitive = options.find('C') != std::string::npos;
    bool unique = options.find('U') != std::string::npos;
    bool reverse = options.find('R') != std::string::npos;
    bool random = options.find("Random") != std::string::npos;
    bool numeric = options.find('N') != std::string::npos;
    // Custom delimiter
    if (options.find('D') != std::string::npos) {
        size_t delimiterPos = options.find('D') + 1;
        if (delimiterPos < options.size()) {
            delimiter = options.substr(delimiterPos, 1);
        }
    }
    // Split input by delimiter
    std::vector<std::string> items;
    std::stringstream ss(input);
    std::string item;
    while (std::getline(ss, item, delimiter[0])) {
        item = trim(item);  // Trim whitespace from each item
        if (!item.empty()) {
            items.push_back(item);
        }
    }
    // Sort items
    if (numeric) {
        std::sort(items.begin(), items.end(), [](const std::string& a, const std::string& b) {
            return std::stoi(a) < std::stoi(b);
        });
    } else {
        std::sort(items.begin(), items.end(), customSortCompare);
    }
    // Remove exact duplicates if needed
    if (unique) {
        items = removeExactDuplicates(items);
    }
    // Apply reverse order if needed
    if (reverse) {
        std::reverse(items.begin(), items.end());
    }
    // Separate uppercase and lowercase items
    std::vector<std::string> uppercaseItems;
    std::vector<std::string> lowercaseItems;
    for (const auto& item : items) {
        if (std::isupper(item[0])) {
            uppercaseItems.push_back(item);
        } else {
            lowercaseItems.push_back(item);
        }
    }
    // Combine sorted uppercase items with sorted lowercase items
    std::string result;
    for (const auto& item : uppercaseItems) {
        result += item;
        result += delimiter;
    }
    for (const auto& item : lowercaseItems) {
        result += item;
        if (&item != &lowercaseItems.back()) {
            result += delimiter;
        }
    }
    // Remove trailing delimiter if necessary
    if (!result.empty() && result.back() == delimiter[0]) {
        result.pop_back();
    }
    return result;
}

std::string RegExReplace(std::string_view inputStr, std::string_view regexPattern, std::string_view replacement) {
#if USE_POWERFUL_REGEX
    // --- SRELL PATH ---
    try {
        const srell::regex re = srell::regex(regexPattern.data(), regexPattern.size());
        return srell::regex_replace(std::string(inputStr), re, std::string(replacement));
    } catch (const srell::regex_error& e) {
        // ERROR IS CAUGHT, BUT WE DO NOTHING. NO MORE MESSAGE.
        return std::string(inputStr); // Return original string on failure
    }
#else
    // --- FALLBACK PATH ---
    try {
        const std::regex re{std::string(regexPattern)};
        return std::regex_replace(std::string(inputStr), re, std::string(replacement));
    } catch (const std::regex_error& e) {
        // ERROR IS CAUGHT, BUT WE DO NOTHING. NO MORE MESSAGE.
        return std::string(inputStr); // Return original string on failure
    }
#endif
}

int RegExMatch(std::string_view haystack, std::string_view needle) {
#if USE_POWERFUL_REGEX
    // --- SRELL PATH ---
    try {
        const srell::regex re = srell::regex(needle.data(), needle.size());
        srell::cmatch match;
        if (srell::regex_search(haystack.data(), haystack.data() + haystack.size(), match, re)) {
            return match.position(0) + 1;
        }
    } catch (const srell::regex_error& e) {
        // ERROR IS CAUGHT, BUT WE DO NOTHING. NO MORE MESSAGE.
    }
#else
    // --- FALLBACK PATH ---
    try {
        const std::regex re{std::string(needle)};
        std::match_results<std::string_view::const_iterator> match;
        if (std::regex_search(haystack.begin(), haystack.end(), match, re)) {
            return match.position(0) + 1;
        }
    } catch (const std::regex_error& e) {
        // ERROR IS CAUGHT, BUT WE DO NOTHING. NO MORE MESSAGE.
    }
#endif
    return 0; // Return 0 on failure
}

// Overload for counting a single character
int countChars(const std::string& str, char theChar) {
    int count = 0;
    for (char c : str) {
        if (c == theChar) {
            count++;
        }
    }
    return count;
}
// Overload for counting a substring
int countChars(const std::string& str, const std::string& substring) {
    if (substring.empty()) return 0; // Avoid infinite loop
    int count = 0;
    size_t pos = 0;
    // Find occurrences of the substring
    while ((pos = str.find(substring, pos)) != std::string::npos) {
        count++;
        pos += substring.length(); // Move past the found substring
    }
    return count;
}

std::string HTVM_getLang_HTVM() {
    return "cpp";
}

bool noParams = false;
std::string allArgs = "";
// in allArgs will look like:
// full/path/code/
// HTVM-Instruction.txt file
// lang to convert to
// HTVM-Instruction.txt file MORE
// HTVM-Instruction.txt file MORE
// HTVM-Instruction.txt file MORE and more
#ifdef _WIN32
    #define ARGC __argc
    #define ARGV __argv
#else
    extern char **environ;
    int ARGC;
    char** ARGV;
    __attribute__((constructor)) void init_args(int argc, char* argv[], char* envp[]) {
        ARGC = argc;
        ARGV = argv;
    }
#endif
std::string GetParams() {
    std::vector<std::string> params;
    for (int i = 1; i < ARGC; ++i) {
        std::string arg = ARGV[i];
        if (std::filesystem::exists(arg)) {
            arg = std::filesystem::absolute(arg).string();
        }
        params.push_back(arg);
    }
    std::string result;
    for (const auto& param : params) {
        result += param + "\n";
    }
    return result;
}
void HTVM_v2_HTVM() {
    std::string params = Trim(GetParams());
    if (params == "") {
	noParams = true;
        print("Usage: HTVM <yourCodeFileName.yourExtension> <HTVM-instructions.txt> [optional LangToTranspileTo]\n\nOptions:\n  <yourCodeFileName.yourExtension>  The source code file to transpile.\n  <HTVM-instructions.txt>              The instructions file for transpilation.\n  [LangToTranspileTo]                Optional: Specify the target language (cpp, py, js, go, lua, cs, java, kt, rb, nim, ahk, swift, dart, ts, groovy, htvm or <yourExtension>).\n\nExample:\n  HTVM main.htvm HTVM-instructions.txt cpp\n");
        return;
    }
    std::vector<std::string> items1 = LoopParseFunc(params, "\n", "\r");
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        allArgs += Trim(A_LoopField1) + "\n";
    }
    allArgs = StringTrimRight(allArgs, 1);
}

void HTVM_Append(std::vector<std::string>& arr, const std::string& value) {
    arr.push_back(value);
}
void HTVM_Append(std::vector<std::string>& arr, const char* value) {
    arr.push_back(std::string(value));
}
void HTVM_Append(std::vector<int>& arr, int value) {
    arr.push_back(value);
}
void HTVM_Append(std::vector<float>& arr, float value) {
    arr.push_back(value);
}
void HTVM_Append(std::vector<bool>& arr, bool value) {
    arr.push_back(value);
}

void HTVM_Pop(std::vector<std::string>& arr) {
    if (!arr.empty()) arr.pop_back();
}
void HTVM_Pop(std::vector<int>& arr) {
    if (!arr.empty()) arr.pop_back();
}
void HTVM_Pop(std::vector<float>& arr) {
    if (!arr.empty()) arr.pop_back();
}
void HTVM_Pop(std::vector<bool>& arr) {
    if (!arr.empty()) arr.pop_back();
}

size_t HTVM_Size(const std::vector<std::string>& arr) {
    return arr.size();
}
size_t HTVM_Size(const std::vector<int>& arr) {
    return arr.size();
}
size_t HTVM_Size(const std::vector<float>& arr) {
    return arr.size();
}
size_t HTVM_Size(const std::vector<bool>& arr) {
    return arr.size();
}


// HTVM: The Adaptive, Multi-Language, Customizable Syntax and Code Generation Engine
// Copyright (C) 2025 TheMaster1127
// ------------------------------------------------------------------------
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// ------------------------------------------------------------------------
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// ------------------------------------------------------------------------
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
// ------------------------------------------------------------------------
std::string str0 = "nothing";
std::string str00 = "nothing";
std::string str1 = "";
std::string str2 = "";
std::string str3 = "";
std::string str4 = "";
std::string str5 = "";
std::string str6 = "";
std::string str7 = "";
std::string str8 = "";
std::string str9 = "";
std::string str10 = "";
std::string str11 = "";
std::string str12 = "";
std::string str13 = "";
std::string str14 = "";
std::string str15 = "";
std::string str16 = "";
std::string str17 = "";
std::string str18 = "";
std::string str19 = "";
std::string str20 = "";
std::string str21 = "";
std::string str22 = "";
std::string str23 = "";
int int0 = 0;
int int1 = 0;
int int2 = 0;
int int3 = 0;
int int4 = 0;
int int5 = 0;
int int6 = 0;
int int7 = 0;
std::vector<std::string> argHTVMinstrMORE;
int isNotHTVMfileEXTRA_INT = 0;
int isNotHTVMfile2 = 0;
std::string isNotHTVMfileEXTRA_LIB_INFO = "";
std::string isNotHTVMfileEXTRA_FUNCS_INFO = "";
std::vector<std::string> programmingBlock_InTheTranspiledLang;
std::vector<std::string> programmingBlock_CPP;
std::vector<std::string> programmingBlock_PY;
std::vector<std::string> programmingBlock_JS;
std::vector<std::string> programmingBlock_GO;
std::vector<std::string> programmingBlock_LUA;
std::vector<std::string> programmingBlock_CS;
std::vector<std::string> programmingBlock_JAVA;
std::vector<std::string> programmingBlock_KT;
std::vector<std::string> programmingBlock_RB;
std::vector<std::string> programmingBlock_NIM;
std::vector<std::string> programmingBlock_AHK;
std::vector<std::string> programmingBlock_SWIFT;
std::vector<std::string> programmingBlock_DART;
std::vector<std::string> programmingBlock_TS;
std::vector<std::string> programmingBlock_GROOVY;
std::vector<std::string> programmingBlock_HTVM;
std::vector<std::string> programmingBlock_HTVMsyntax;
std::vector<std::string> fullLangAllOperators;
std::vector<std::string> fullLangAllOperators_HELP;
int fixExpertionLineFuncOnly = 0;
std::string langToConvertTo = "";
std::string langFileExtension = "";
std::string commands = "";
std::string keyWordAlliance = "";
std::string keyWordCrew = "";
std::string keyWordProc = "";
std::string keyWordStruct = "";
std::string keyWordProp = "";
std::string keyWordThis = "";
std::string keyWordInclude = "";
std::string keyWordCodeInTheTranspiledLangStart = "";
std::string keyWordCodeInTheTranspiledLangEnd = "";
std::string keyWordCodeInTheTranspiledLangStartCPP = "";
std::string keyWordCodeInTheTranspiledLangEndCPP = "";
std::string keyWordCodeInTheTranspiledLangStartPY = "";
std::string keyWordCodeInTheTranspiledLangEndPY = "";
std::string keyWordCodeInTheTranspiledLangStartJS = "";
std::string keyWordCodeInTheTranspiledLangEndJS = "";
std::string keyWordCodeInTheTranspiledLangStartGO = "";
std::string keyWordCodeInTheTranspiledLangEndGO = "";
std::string keyWordCodeInTheTranspiledLangStartLUA = "";
std::string keyWordCodeInTheTranspiledLangEndLUA = "";
std::string keyWordCodeInTheTranspiledLangStartCS = "";
std::string keyWordCodeInTheTranspiledLangEndCS = "";
std::string keyWordCodeInTheTranspiledLangStartJAVA = "";
std::string keyWordCodeInTheTranspiledLangEndJAVA = "";
std::string keyWordCodeInTheTranspiledLangStartKT = "";
std::string keyWordCodeInTheTranspiledLangEndKT = "";
std::string keyWordCodeInTheTranspiledLangStartRB = "";
std::string keyWordCodeInTheTranspiledLangEndRB = "";
std::string keyWordCodeInTheTranspiledLangStartNIM = "";
std::string keyWordCodeInTheTranspiledLangEndNIM = "";
std::string keyWordCodeInTheTranspiledLangStartAHK = "";
std::string keyWordCodeInTheTranspiledLangEndAHK = "";
std::string keyWordCodeInTheTranspiledLangStartSWIFT = "";
std::string keyWordCodeInTheTranspiledLangEndSWIFT = "";
std::string keyWordCodeInTheTranspiledLangStartDART = "";
std::string keyWordCodeInTheTranspiledLangEndDART = "";
std::string keyWordCodeInTheTranspiledLangStartTS = "";
std::string keyWordCodeInTheTranspiledLangEndTS = "";
std::string keyWordCodeInTheTranspiledLangStartGROOVY = "";
std::string keyWordCodeInTheTranspiledLangEndGROOVY = "";
std::string keyWordCodeInTheTranspiledLangStartHTVM = "";
std::string keyWordCodeInTheTranspiledLangEndHTVM = "";
std::string keyWordCodeInHTVMstart = "";
std::string keyWordCodeInHTVMend = "";
std::string keyWordCurlyBraceOpen = "";
std::string keyWordCurlyBraceClose = "";
std::string keyWordNull = "";
std::string keyWordTrue = "";
std::string keyWordFalse = "";
std::string keyWordVoid = "";
std::string keyWordDouble = "";
std::string keyWordChar = "";
std::string keyWordUint8 = "";
std::string keyWordUint16 = "";
std::string keyWordUint32 = "";
std::string keyWordUint64 = "";
std::string keyWordINT = "";
std::string keyWordSTR = "";
std::string keyWordBOOL = "";
std::string keyWordFLOAT = "";
std::string keyWordINT8 = "";
std::string keyWordINT16 = "";
std::string keyWordINT32 = "";
std::string keyWordINT64 = "";
std::string keyWordIF = "";
std::string keyWordElseIf = "";
std::string keyWordElse = "";
std::string keyWordWhileLoop = "";
std::string keyWordLoopInfinite = "";
std::string keyWordLoop = "";
std::string keyWordLoopParse = "";
std::string keyWordContinue = "";
std::string keyWordBreak = "";
std::string keyWordFunc = "";
std::string keyWordAwait = "";
std::string keyWordAsync = "";
std::string keyWordThrow = "";
std::string keyWordErrorMsg = "";
std::string keyWordTry = "";
std::string keyWordCatch = "";
std::string keyWordFinally = "";
std::string keyWordReturnStatement = "";
std::string keyWordArrayAppend = "";
std::string keyWordArrayPop = "";
std::string keyWordArraySize = "";
std::string keyWordArrayInsert = "";
std::string keyWordArrayRemove = "";
std::string keyWordArrayIndexOf = "";
std::string keyWordArrayDefinition = "";
std::string keyWordArrayOfIntegersDefinition = "";
std::string keyWordArrayOfStringsDefinition = "";
std::string keyWordArrayOfFloatingPointNumbersDefinition = "";
std::string keyWordArrayOfBooleansDefinition = "";
std::string keyWordVar = "";
std::string keyWordLet = "";
std::string keyWordConst = "";
std::string keyWordEnd = "";
std::string keyWordGlobal = "";
std::string keyWordComment = "";
std::string keyWordCommentOpenMultiLine = "";
std::string keyWordCommentCloseMultiLine = "";
std::string keyWordEscpaeChar = "";
std::string keyWordMainLabel = "";
std::string keyWordConcat = "";
std::string keyWordAdd = "";
std::string keyWordSub = "";
std::string keyWordMul = "";
std::string keyWordDiv = "";
std::string keyWordMod = "";
std::string keyWordExp = "";
std::string keyWordEqual = "";
std::string keyWordStrictEqual = "";
std::string keyWordNotEqual = "";
std::string keyWordGreater = "";
std::string keyWordLess = "";
std::string keyWordGreaterEqual = "";
std::string keyWordLessEqual = "";
std::string keyWordAnd = "";
std::string keyWordOr = "";
std::string keyWordNot = "";
std::string keyWordBitAnd = "";
std::string keyWordBitOr = "";
std::string keyWordBitXor = "";
std::string keyWordBitNot = "";
std::string keyWordShiftLeft = "";
std::string keyWordShiftRight = "";
std::string keyWordShiftUnsignedRight = "";
std::string keyWordAssign = "";
std::string keyWordAssignAdd = "";
std::string keyWordAssignConcat = "";
std::string keyWordAssignSub = "";
std::string keyWordAssignMul = "";
std::string keyWordAssignDiv = "";
std::string keyWordAssignMod = "";
std::string keyWordAssignShiftLeft = "";
std::string keyWordAssignShiftRight = "";
std::string keyWordLogicalAssignShiftRight = "";
std::string keyWordAssignBitAnd = "";
std::string keyWordAssignBitOr = "";
std::string keyWordAssignBitXor = "";
std::string keyWordTernary1 = "";
std::string keyWordTernary2 = "";
std::string keyWordInc = "";
std::string keyWordDec = "";
std::string AHKlikeLoopsIndexedAt = "";
std::string keyWordAIndex = "";
std::string keyWordALoopField = "";
std::string useFuncKeyWord = "";
std::string useCurlyBraces = "";
std::string useEnd = "";
std::string useSemicolon = "";
std::string theSemicolon = "";
std::string theColon = "";
std::string useParentheses = "";
std::string usePrefixTypeForTypeDefinition = "";
std::string usePostfixTypeForTypeDefinition = "";
std::string usePythonicColonSyntax = "";
std::string useCurlyBracesSyntaxForArrayDef = "";
std::string useInJavaScriptAlwaysUseVar = "";
std::string useJavaScriptInAfullHTMLfile = "";
std::string useJavaScriptAmainFuncDef = "";
std::string useJavaScriptAllFuncsAreAsync = "";
std::string useJavaScriptAlwaysTripleEqual = "";
std::string langToConvertTo_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string langFileExtension_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string commands_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAlliance_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCrew_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordProc_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordStruct_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordProp_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordThis_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordInclude_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStart_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartCPP_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndCPP_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartPY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndPY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartJS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndJS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartGO_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndGO_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartLUA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndLUA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartCS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndCS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartJAVA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndJAVA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartKT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndKT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartRB_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndRB_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartNIM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndNIM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartAHK_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndAHK_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartSWIFT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndSWIFT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartDART_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndDART_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartTS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndTS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartGROOVY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndGROOVY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartHTVM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndHTVM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInHTVMstart_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInHTVMend_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCurlyBraceOpen_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCurlyBraceClose_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordNull_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordTrue_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordFalse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordVoid_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordDouble_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordChar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordUint8_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordUint16_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordUint32_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordUint64_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordINT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordSTR_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordBOOL_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordFLOAT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordINT8_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordINT16_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordINT32_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordINT64_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordIF_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordElseIf_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordElse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordWhileLoop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLoopInfinite_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLoop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLoopParse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordContinue_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordBreak_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordFunc_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAwait_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAsync_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordThrow_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordErrorMsg_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordTry_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCatch_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordFinally_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordReturnStatement_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayAppend_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayPop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArraySize_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayInsert_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayRemove_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayIndexOf_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayOfIntegersDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayOfStringsDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayOfFloatingPointNumbersDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayOfBooleansDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordVar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLet_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordConst_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordGlobal_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordComment_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCommentOpenMultiLine_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCommentCloseMultiLine_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordEscpaeChar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordMainLabel_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordConcat_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAdd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordSub_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordMul_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordDiv_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordMod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordExp_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordStrictEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordNotEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordGreater_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLess_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordGreaterEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLessEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordNot_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordBitAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordBitOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordBitXor_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordBitNot_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordShiftLeft_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordShiftUnsignedRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssign_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignAdd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignConcat_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignSub_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignMul_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignDiv_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignMod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignShiftLeft_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLogicalAssignShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignBitAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignBitOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignBitXor_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordTernary1_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordTernary2_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordInc_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordDec_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string AHKlikeLoopsIndexedAt_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAIndex_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordALoopField_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useCurlyBraces_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useSemicolon_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useParentheses_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string usePrefixTypeForTypeDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string usePostfixTypeForTypeDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string usePythonicColonSyntax_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useCurlyBracesSyntaxForArrayDef_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useInJavaScriptAlwaysUseVar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useJavaScriptInAfullHTMLfile_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useJavaScriptAmainFuncDef_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useJavaScriptAllFuncsAreAsync_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useJavaScriptAlwaysTripleEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordALoopFieldOriginal = "";
std::string keyWordAIndexOriginal = "";
std::string out_KeyWordsCommands = "";
std::string outTrimCode = "";
std::string htCode = "";
std::string outVarOperator = "";
int lineDone = 0;
int areWeInAFuncFromInstructions = 0;
int areWeInAFuncFromInstructionsLineNum = 0;
int javaMainFuncSeen = 0;
int csMainFuncSeen = 0;
int howMany_fixAindexInGoUnused = 0;
int luaContinueFix_Num = 0;
std::string theTryCatchVarForErrors = "jhku-dfsds-ds-d-ffdsf-sdfsfdsedsf";
std::vector<std::string> allVarsSoWeDontReDecVars;
std::vector<std::string> allVarsSoWeDontReDecVars_FIX_uint8;
std::vector<std::string> allVarsSoWeDontReDecVars_FIX_uint16;
std::vector<std::string> allVarsSoWeDontReDecVars_FIX_uint32;
std::vector<std::string> allVarsSoWeDontReDecVars_FIX_uint64;
std::vector<std::string> allVarsSoWeDontReDecVars_FIX_int64;
std::vector<std::string> allVarsSoWeDontReDecVars_FIX_float;
int allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
std::string availableFuncsInHTVMInHTVM = "";
std::string saveAllArrayVarNamesSoWeCanDoAfix = "|";
int initializeBackendAndGUIInteractionWithLabelSubroutineLikeButConvertsToFunction_WAS_IN_PYTHON = 0;
std::vector<std::string> weAreInMLSarr;
std::vector<std::string> ospDic;
std::vector<std::string> ospDic1;
std::vector<std::string> ospDic2;
std::vector<std::string> htCodeFixRubyGlobalVars_EXPOSED;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string SubStrLastChars(std::string text, int numOfChars) {
    std::string LastOut = "";
    int NumOfChars = 0;
    std::vector<std::string> items1 = LoopParseFunc(text);
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        NumOfChars++;
    }
    for (int A_Index2 = 0; A_Index2 < numOfChars + 0; A_Index2++) {
        NumOfChars--;
    }
    std::vector<std::string> items3 = LoopParseFunc(text);
    for (size_t A_Index3 = 0; A_Index3 < items3.size() + 0; A_Index3++) {
        std::string A_LoopField3 = items3[A_Index3 - 0];
        if (A_Index3 >= NumOfChars) {
            LastOut += A_LoopField3;
        }
    }
    return LastOut;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string fixCSandJAVAstaticBugForFunc(std::string line) {
    std::string out = "";
    int haveWeSeenMainFunc = 0;
    std::vector<std::string> items4 = LoopParseFunc(line, "\n", "\r");
    for (size_t A_Index4 = 0; A_Index4 < items4.size() + 0; A_Index4++) {
        std::string A_LoopField4 = items4[A_Index4 - 0];
        if (haveWeSeenMainFunc == 0 && InStr(A_LoopField4, "    static ")) {
            out += StrReplace(A_LoopField4, "    static ", "    ") + Chr(10);
        } else {
            out += A_LoopField4 + Chr(10);
        }
        if (InStr(StrLower(A_LoopField4), " main(")) {
            haveWeSeenMainFunc = 1;
        }
    }
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string allVarsSoWeDontReDecVarsFixFunc(std::string line, std::string varName) {
    std::string out = "";
    if (RegExMatch(line, "^-?\\d+(\\.\\d+)?$")) {
        for (int A_Index5 = 0; A_Index5 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint8) + 0; A_Index5++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint8[A_Index5]) == Trim(varName)) {
                if (langToConvertTo == "java") {
                    out = "(byte) " + line;
                }
                if (langToConvertTo == "kt") {
                    out = line + "u";
                }
            }
        }
        for (int A_Index6 = 0; A_Index6 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint16) + 0; A_Index6++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint16[A_Index6]) == Trim(varName)) {
                if (langToConvertTo == "java") {
                    out = "(short) " + line;
                }
                if (langToConvertTo == "kt") {
                    out = line + "u";
                }
            }
        }
        for (int A_Index7 = 0; A_Index7 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint32) + 0; A_Index7++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint32[A_Index7]) == Trim(varName)) {
                if (langToConvertTo == "kt") {
                    out = line + "u";
                }
                if (langToConvertTo == "nim") {
                    out = line + "'u32";
                }
            }
        }
        for (int A_Index8 = 0; A_Index8 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint64) + 0; A_Index8++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint64[A_Index8]) == Trim(varName)) {
                if (langToConvertTo == "kt") {
                    out = line + "uL";
                }
                if (langToConvertTo == "cpp") {
                    out = line + "ULL";
                }
                if (langToConvertTo == "java") {
                    out = line + "L";
                }
                if (langToConvertTo == "cs") {
                    out = line + "UL";
                }
                if (langToConvertTo == "nim") {
                    out = line + "'u64";
                }
                if (langToConvertTo == "java") {
                    out = line + "L";
                }
                if (langToConvertTo == "dart") {
                    out = "BigInt.parse(" + Chr(34) + line + Chr(34) + ")";
                }
                if (langToConvertTo == "js" || langToConvertTo == "ts") {
                    out = line + "n";
                }
            }
        }
        for (int A_Index9 = 0; A_Index9 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_int64) + 0; A_Index9++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_int64[A_Index9]) == Trim(varName)) {
                if (langToConvertTo == "kt") {
                    out = line + "L";
                }
                if (langToConvertTo == "cpp") {
                    out = line + "LL";
                }
                if (langToConvertTo == "cs") {
                    out = line + "L";
                }
                if (langToConvertTo == "js" || langToConvertTo == "ts") {
                    out = line + "n";
                }
            }
        }
        for (int A_Index10 = 0; A_Index10 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_float) + 0; A_Index10++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_float[A_Index10]) == Trim(varName)) {
                if (langToConvertTo == "cpp" || langToConvertTo == "cs" || langToConvertTo == "java" || langToConvertTo == "kt") {
                    out = line + "f";
                }
            }
        }
    } else {
        return line;
    }
    if (Trim(out) == "") {
        return line;
    }
    return out;
}
std::string KeyWordsCommands(std::string theCodeCommands, std::string mode, std::string keyWordsCommands, std::string langToConvertTo) {
    theCodeCommands = Trim(theCodeCommands);
    theCodeCommands = StrReplace(theCodeCommands, "%", "");
    theCodeCommands = StrReplace(theCodeCommands, "| ", "|");
    theCodeCommands = StrReplace(theCodeCommands, ", ", ",");
    if (SubStrLastChars(theCodeCommands, 1) == "|") {
        theCodeCommands = StringTrimRight(theCodeCommands, 1);
    }
    if (mode == "check") {
        std::vector<std::string> items11 = LoopParseFunc(keyWordsCommands, "|");
        for (size_t A_Index11 = 0; A_Index11 < items11.size() + 0; A_Index11++) {
            std::string A_LoopField11 = items11[A_Index11 - 0];
            std::vector<std::string> items12 = LoopParseFunc(A_LoopField11, ",");
            for (size_t A_Index12 = 0; A_Index12 < items12.size() + 0; A_Index12++) {
                std::string A_LoopField12 = items12[A_Index12 - 0];
                if (A_Index12 == 0) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField12 + ",")) == StrLower(A_LoopField12 + ",")) {
                        //MsgBox, true
                        return "true";
                    }
                }
                if (A_Index12 == 0) {
                    if (theCodeCommands == A_LoopField12) {
                        //MsgBox, true
                        return "true";
                    }
                }
            }
        }
        //MsgBox, false
        return "false";
    }
    int AIndex = 0;
    if (mode == "transpile") {
        int keyWordsCommandsNumLine = 1;
        std::vector<std::string> items13 = LoopParseFunc(keyWordsCommands, "|");
        for (size_t A_Index13 = 0; A_Index13 < items13.size() + 0; A_Index13++) {
            std::string A_LoopField13 = items13[A_Index13 - 0];
            AIndex = A_Index13;
            std::vector<std::string> items14 = LoopParseFunc(A_LoopField13, ",");
            for (size_t A_Index14 = 0; A_Index14 < items14.size() + 0; A_Index14++) {
                std::string A_LoopField14 = items14[A_Index14 - 0];
                if (A_Index14 == 0) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField14 + ",")) == StrLower(A_LoopField14 + ",")) {
                        //MsgBox, true
                        keyWordsCommandsNumLine = AIndex;
                        break;
                    }
                }
                if (A_Index14 == 0) {
                    //MsgBox, %theCodeCommands% = %A_LoopField%
                    if (theCodeCommands == A_LoopField14) {
                        //MsgBox, true
                        keyWordsCommandsNumLine = AIndex;
                        break;
                    }
                }
            }
        }
        std::string outConstuctTheOutFromTheCommands = "";
        std::string outConstuctTheOutFromTheCommandsFucnName = "";
        std::string outConstuctTheOutFromTheCommandsParams = "";
        std::string outConstuctTheOutFromTheCommandsOutVar = "";
        std::string outConstuctTheOutFromTheCommandsInVar = "";
        int theCodeCommandNum = 0;
        int outConstuctTheOutFromTheCommandsLineTranspile = 0;
        std::string outConstuctTheOutFromTheCommandsLineTranspileText = "";
        std::string semicolon = "";
        if (langToConvertTo != "py" && langToConvertTo != "nim" && langToConvertTo != "ahk" && langToConvertTo != "go" && langToConvertTo != "lua" && langToConvertTo != "kt" && langToConvertTo != "rb" && langToConvertTo != "swift" && langToConvertTo != "groovy") {
            semicolon = ";";
        }
        std::string assignmentOperatorKeyWord = "=";
        if (langToConvertTo == langFileExtension_2) {
            assignmentOperatorKeyWord = keyWordAssign_2;
        }
        else if (langToConvertTo == "ahk") {
            assignmentOperatorKeyWord = ":=";
        } else {
            assignmentOperatorKeyWord = "=";
        }
        std::vector<std::string> theCodeCommand;
        theCodeCommands = Trim(theCodeCommands);
        std::vector<std::string> items15 = LoopParseFunc(theCodeCommands, ",");
        for (size_t A_Index15 = 0; A_Index15 < items15.size() + 0; A_Index15++) {
            std::string A_LoopField15 = items15[A_Index15 - 0];
            HTVM_Append(theCodeCommand, Trim(A_LoopField15));
            //MsgBox, % A_LoopField
        }
        std::vector<std::string> items16 = LoopParseFunc(keyWordsCommands, "|");
        for (size_t A_Index16 = 0; A_Index16 < items16.size() + 0; A_Index16++) {
            std::string A_LoopField16 = items16[A_Index16 - 0];
            if (keyWordsCommandsNumLine == A_Index16) {
                //MsgBox, % A_LoopField
                std::vector<std::string> items17 = LoopParseFunc(A_LoopField16, ",");
                for (size_t A_Index17 = 0; A_Index17 < items17.size() + 0; A_Index17++) {
                    std::string A_LoopField17 = items17[A_Index17 - 0];
                    if (A_Index17 == 0) {
                        outConstuctTheOutFromTheCommandsFucnName = A_LoopField17;
                    }
                    else if (A_Index17 == 1) {
                        //MsgBox, % A_LoopField
                        if (A_LoopField17 == "lineTranspile") {
                            outConstuctTheOutFromTheCommandsLineTranspile = 1;
                        }
                        if (A_LoopField17 == "OUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField17 == "INOUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField17 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField17, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    }
                    else if (A_Index17 == 2) {
                        if (outConstuctTheOutFromTheCommandsLineTranspile == 1) {
                            outConstuctTheOutFromTheCommandsLineTranspileText = A_LoopField17;
                        }
                        if (A_LoopField17 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField17, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    } else {
                        //MsgBox, % theCodeCommand[theCodeCommandNum]
                        if (InStr(A_LoopField17, Chr(39))) {
                            if (Trim(theCodeCommand[theCodeCommandNum]) != "") {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            }
                        } else {
                            if (Trim(theCodeCommand[theCodeCommandNum]) != "") {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    }
                    theCodeCommandNum++;
                }
                break;
            }
        }
        outConstuctTheOutFromTheCommandsParams = StringTrimRight(outConstuctTheOutFromTheCommandsParams, 2);
        if (outConstuctTheOutFromTheCommandsOutVar != "") {
            if (outConstuctTheOutFromTheCommandsParams == "") {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " " + assignmentOperatorKeyWord + " " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ")" + semicolon;
            } else {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " " + assignmentOperatorKeyWord + " " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ", " + outConstuctTheOutFromTheCommandsParams + ")" + semicolon;
            }
        }
        if (outConstuctTheOutFromTheCommandsOutVar == "") {
            if (outConstuctTheOutFromTheCommandsParams == "") {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ")" + semicolon;
            } else {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ", " + outConstuctTheOutFromTheCommandsParams + ")" + semicolon;
            }
        }
        if (outConstuctTheOutFromTheCommandsLineTranspile == 1) {
            outConstuctTheOutFromTheCommands = StrReplace(outConstuctTheOutFromTheCommandsLineTranspileText, "~~~", Chr(10));
        }
        outConstuctTheOutFromTheCommands = StrReplace(outConstuctTheOutFromTheCommands, "(, ", "( ");
        outConstuctTheOutFromTheCommands = StrReplace(outConstuctTheOutFromTheCommands, "(,", "(");
        return outConstuctTheOutFromTheCommands;
    }
    return "false";
}
std::string HTVMmatchStrRrplace(std::string line, std::string matchString, std::string replaceString) {
    std::string lineOut = "";
    if (!InStr(line, matchString)) {
        return line;
    }
    std::string allDelimiters = " ()[].,;:'!&|=<>+-*/^%~" + Chr(34) + Chr(9) + Chr(11);
    std::vector<std::string> lineArr;
    std::vector<std::string> items18 = LoopParseFunc(line);
    for (size_t A_Index18 = 0; A_Index18 < items18.size() + 0; A_Index18++) {
        std::string A_LoopField18 = items18[A_Index18 - 0];
        HTVM_Append(lineArr, A_LoopField18);
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
    for (int A_Index19 = 0; A_Index19 < HTVM_Size(lineArr) + 0; A_Index19++) {
        char1 = "";
        char2 = "";
        char3 = "";
        char4 = "";
        isMatch = 0;
        if (A_Index19 != 0) {
            isStart = 0;
        }
        sildingLine = "";
        for (int A_Index20 = 0; A_Index20 < matchStringLEN + 0; A_Index20++) {
            if (A_Index20 + i1 <= HTVM_Size(lineArr) - 1) {
                sildingLine += lineArr[A_Index20 + i1];
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
            if (i1 + matchStringLEN < HTVM_Size(lineArr)) {
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
            if (HTVM_Size(allPosForReplacing) > 0) {
                for (int A_Index21 = 0; A_Index21 < HTVM_Size(allPosForReplacing) + 0; A_Index21++) {
                    if (i1 + 1 != allPosForReplacing[A_Index21]) {
                        HTVM_Append(allPosForReplacing, i1 + 1);
                        break;
                    }
                }
            } else {
                HTVM_Append(allPosForReplacing, i1 + 1);
            }
        }
        i1++;
    }
    std::string lineTEMP = "";
    lineOut = line;
    //print(allPosForReplacing)
    if (HTVM_Size(allPosForReplacing) > 0) {
        // matchStringLEN
        // replaceStringLEN
        int l2 = 0;
        int currentPos = 0;
        int onceEnd = 0;
        for (int A_Index22 = 0; A_Index22 < HTVM_Size(allPosForReplacing) + 0; A_Index22++) {
            if (A_Index22 == 0) {
                currentPos = allPosForReplacing[A_Index22];
            } else {
                currentPos = allPosForReplacing[A_Index22] - (matchStringLEN - replaceStringLEN);
            }
            onceEnd = 0;
            std::vector<std::string> items23 = LoopParseFunc(lineOut);
            for (size_t A_Index23 = 0; A_Index23 < items23.size() + 0; A_Index23++) {
                std::string A_LoopField23 = items23[A_Index23 - 0];
                if (A_Index23 + 2 > currentPos && A_Index23 + 1 < currentPos + matchStringLEN) {
                    onceEnd++;
                    //print("DDDDDDDDDDD" . STR(A_Index))
                    if (onceEnd == 1) {
                        lineTEMP += replaceString;
                    }
                } else {
                    lineTEMP += A_LoopField23;
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
std::string ExtractDigits(std::string inputString) {
    std::string digits = "";
    std::vector<std::string> items24 = LoopParseFunc(inputString);
    for (size_t A_Index24 = 0; A_Index24 < items24.size() + 0; A_Index24++) {
        std::string A_LoopField24 = items24[A_Index24 - 0];
        if (RegExMatch(A_LoopField24, "\\d")) {
            digits += A_LoopField24;
        }
    }
    return digits;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Helper function to create spaces
std::string spaces(int n) {
    std::string s = "";
    if (n != 0) {
        for (int A_Index25 = 0; A_Index25 < n + 0; A_Index25++) {
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
    std::vector<std::string> items26 = LoopParseFunc(string123);
    for (size_t A_Index26 = 0; A_Index26 < items26.size() + 0; A_Index26++) {
        std::string A_LoopField26 = items26[A_Index26 - 0];
        // Check if the current character is a space
        if (A_LoopField26 == Chr(32)) {
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
    std::vector<std::string> items27 = LoopParseFunc(input);
    for (size_t A_Index27 = 0; A_Index27 < items27.size() + 0; A_Index27++) {
        std::string A_LoopField27 = items27[A_Index27 - 0];
        if (A_LoopField27 != " " || foundNonSpace) {
            result += A_LoopField27;
            foundNonSpace = true;
        }
    }
    return result;
}
std::string getLastChar(std::string strippedString) {
    std::string lastChar = "";
    std::vector<std::string> items28 = LoopParseFunc(strippedString);
    for (size_t A_Index28 = 0; A_Index28 < items28.size() + 0; A_Index28++) {
        std::string A_LoopField28 = items28[A_Index28 - 0];
        lastChar = A_LoopField28;
    }
    return lastChar;
}
std::string AddCurlyBraces(std::string pythonCode) {
    pythonCode = StrReplace(pythonCode, Chr(9), "    ");
    std::string result = "";
    int indentLevel = 0;
    int indent = 0;
    std::string line = "";
    std::string stripped = "";
    std::vector<std::string> items29 = LoopParseFunc(pythonCode, "\n", "\r");
    for (size_t A_Index29 = 0; A_Index29 < items29.size() + 0; A_Index29++) {
        std::string A_LoopField29 = items29[A_Index29 - 0];
        line = A_LoopField29;
        stripped = Trim(line);
        if (stripped == "") {
            result += line + Chr(10);
            continue;
        }
        // Count leading spaces
        indent = StrLen(line) - StrLen(LTrim(line));
        // Close braces for unindents
        for (int A_Index30 = 0; ; A_Index30++) {
            if (indentLevel <= indent) {
                break;
            }
            indentLevel -= 4;
            result += spaces(indentLevel) + "}" + Chr(10);
        }
        // Add opening brace for new blocks
        if (getLastChar(stripped) == ":" && SubStr(StrLower(Trim(A_LoopField29)), 1, StrLen(StrLower(keyWordComment))) != StrLower(keyWordComment)) {
            result += SubStr(line, 1, -1) + " {" + Chr(10);
            indentLevel += 4;
        } else {
            result += line + Chr(10);
        }
    }
    // Close any remaining open braces
    for (int A_Index31 = 0; ; A_Index31++) {
        if (indentLevel <= 0) {
            break;
        }
        indentLevel -= 4;
        result += spaces(indentLevel) + "}" + Chr(10);
    }
    return result;
}
std::string RepeatSpaces(int count) {
    std::string spaces = "";
    for (int A_Index32 = 0; A_Index32 < count + 0; A_Index32++) {
        spaces += Chr(32);
    }
    return spaces;
}
std::string indent_nested_curly_braces(std::string input_string, int modeCurlyBracesOn) {
    int indent_size = 4;
    int current_indent = 0;
    std::string result = "";
    std::string trimmed_line = "";
    std::string resultOut = "";
    std::string culyOpenFix = "{";
    std::string culyCloseFix = "}";
    if (langToConvertTo == langFileExtension_2) {
        culyOpenFix = Trim(keyWordCurlyBraceOpen_2);
        culyCloseFix = Trim(keyWordCurlyBraceClose_2);
    }
    //MsgBox, % input_string
    std::vector<std::string> items33 = LoopParseFunc(input_string, "\n", "\r");
    for (size_t A_Index33 = 0; A_Index33 < items33.size() + 0; A_Index33++) {
        std::string A_LoopField33 = items33[A_Index33 - 0];
        trimmed_line = Trim(A_LoopField33);
        if (trimmed_line == Chr(123)) {
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + Chr(10);
            current_indent = current_indent + indent_size;
        }
        else if (trimmed_line == Chr(125)) {
            current_indent = current_indent - indent_size;
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + Chr(10);
        } else {
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + Chr(10);
        }
    }
    if (modeCurlyBracesOn == 0) {
        std::string resultOut = "";
        std::vector<std::string> items34 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index34 = 0; A_Index34 < items34.size() + 0; A_Index34++) {
            std::string A_LoopField34 = items34[A_Index34 - 0];
            if (Trim(A_LoopField34) != "{" && Trim(A_LoopField34) != "}") {
                resultOut += A_LoopField34 + Chr(10);
            }
        }
        result = StringTrimRight(resultOut, 1);
    } else {
        // format curly braces in a K&R style
        std::vector<std::string> lookIntoFurture;
        std::vector<std::string> items35 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index35 = 0; A_Index35 < items35.size() + 0; A_Index35++) {
            std::string A_LoopField35 = items35[A_Index35 - 0];
            HTVM_Append(lookIntoFurture, Trim(A_LoopField35));
        }
        HTVM_Append(lookIntoFurture, " ");
        std::string resultOut = "";
        int skipNext = 0;
        std::vector<std::string> items36 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index36 = 0; A_Index36 < items36.size() + 0; A_Index36++) {
            std::string A_LoopField36 = items36[A_Index36 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (Trim(lookIntoFurture[A_Index36 + 1]) == "{") {
                resultOut += A_LoopField36 + " " + culyOpenFix + Chr(10);
                skipNext = 2;
            }
            if (skipNext == 0) {
                resultOut += A_LoopField36 + Chr(10);
            }
        }
        result = StringTrimRight(resultOut, 1);
        std::vector<std::string> lookIntoFurture2;
        std::vector<std::string> items37 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index37 = 0; A_Index37 < items37.size() + 0; A_Index37++) {
            std::string A_LoopField37 = items37[A_Index37 - 0];
            HTVM_Append(lookIntoFurture2, Trim(A_LoopField37));
        }
        HTVM_Append(lookIntoFurture2, " ");
        resultOut = "";
        skipNext = 0;
        std::string addSpacesAtTheBegginig = "";
        std::vector<std::string> items38 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index38 = 0; A_Index38 < items38.size() + 0; A_Index38++) {
            std::string A_LoopField38 = items38[A_Index38 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (langToConvertTo != "lua" && langToConvertTo != "rb" && langToConvertTo != langFileExtension_2) {
                if (Trim(A_LoopField38) == "}" && Trim(lookIntoFurture2[A_Index38 + 1]) == "else {") {
                    skipNext = 2;
                    addSpacesAtTheBegginig = "";
                    std::vector<std::string> items39 = LoopParseFunc(A_LoopField38);
                    for (size_t A_Index39 = 0; A_Index39 < items39.size() + 0; A_Index39++) {
                        std::string A_LoopField39 = items39[A_Index39 - 0];
                        if (A_LoopField39 == " ") {
                            if (A_LoopField39 != " ") {
                                break;
                            }
                            addSpacesAtTheBegginig += StrReplace(A_LoopField39, "}", culyCloseFix);
                        }
                    }
                    resultOut += addSpacesAtTheBegginig + culyCloseFix + " else " + culyOpenFix + Chr(10);
                }
            }
            if (skipNext == 0) {
                resultOut += A_LoopField38 + Chr(10);
            }
        }
        result = StringTrimRight(resultOut, 1);
    }
    resultOut = "";
    std::string ALoopField = "";
    std::vector<std::string> items40 = LoopParseFunc(result, "\n", "\r");
    for (size_t A_Index40 = 0; A_Index40 < items40.size() + 0; A_Index40++) {
        std::string A_LoopField40 = items40[A_Index40 - 0];
        if (CheckOddLeadingSpaces(A_LoopField40) == "1") {
            ALoopField = StringTrimLeft(A_LoopField40, 1);
            resultOut += ALoopField + Chr(10);
        } else {
            resultOut += A_LoopField40 + Chr(10);
        }
    }
    result = StringTrimRight(resultOut, 1);
    std::string fixResultFIX = "";
    if (langToConvertTo == langFileExtension_2 && modeCurlyBracesOn == 1) {
        std::vector<std::string> items41 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index41 = 0; A_Index41 < items41.size() + 0; A_Index41++) {
            std::string A_LoopField41 = items41[A_Index41 - 0];
            if (Trim(A_LoopField41) == "}") {
                fixResultFIX += StrReplace(A_LoopField41, "}", culyCloseFix) + Chr(10);
            } else {
                fixResultFIX += A_LoopField41 + Chr(10);
            }
        }
        result = StringTrimRight(fixResultFIX, 1);
    }
    // Return the result
    return result;
}
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
bool isLineAconstruct(std::string line) {
    line = StrLower(Trim(line));
    if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf)) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordElse) || StrLower(Trim(line)) == StrLower(keyWordElse + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordElse))) == keyWordCurlyBraceClose + " " + StrLower(keyWordElse)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordElse) + " " + StrLower(keyWordCurlyBraceOpen))) == StrLower(keyWordElse) + " " + StrLower(keyWordCurlyBraceOpen)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordLoopInfinite) || StrLower(Trim(line)) == StrLower(keyWordLoopInfinite + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordLoopInfinite))) == keyWordCurlyBraceClose + " " + StrLower(keyWordLoopInfinite)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordLoopInfinite) + " " + StrLower(keyWordCurlyBraceOpen))) == StrLower(keyWordLoopInfinite) + " " + StrLower(keyWordCurlyBraceOpen)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordTry) || StrLower(Trim(line)) == StrLower(keyWordTry + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordTry))) == keyWordCurlyBraceClose + " " + StrLower(keyWordTry)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordTry) + " " + StrLower(keyWordCurlyBraceOpen))) == StrLower(keyWordTry) + " " + StrLower(keyWordCurlyBraceOpen)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordCrew))) == StrLower(keyWordCrew)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordStruct))) == StrLower(keyWordStruct)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordProc))) == StrLower(keyWordProc)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordFinally) || StrLower(Trim(line)) == StrLower(keyWordFinally + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordFinally))) == keyWordCurlyBraceClose + " " + StrLower(keyWordFinally)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordFinally) + " " + StrLower(keyWordCurlyBraceOpen))) == StrLower(keyWordFinally) + " " + StrLower(keyWordCurlyBraceOpen)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(StrLower(line))), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordAsync))) == StrLower(keyWordAsync)) {
        return true;
    }
    return false;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string fixArray1234(std::string line) {
    std::string out = "";
    int started = 0;
    std::vector<std::string> items42 = LoopParseFunc(line);
    for (size_t A_Index42 = 0; A_Index42 < items42.size() + 0; A_Index42++) {
        std::string A_LoopField42 = items42[A_Index42 - 0];
        if (started == 1) {
            if (StrLen(line) == A_Index42 + 1) {
                return out;
            }
            out += A_LoopField42;
        }
        if (A_LoopField42 == "(") {
            started = 1;
        }
    }
    return out;
}
std::string fixArray123(std::string line, std::string arrayProcStr, int mode) {
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
    if (langToConvertTo != "swift" && langToConvertTo != "go") {
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
std::string arrayParserTranspiler1(std::string line, std::string arrayProcStr, int mode) {
    if (InStr(line, arrayProcStr) == false) {
        return line;
    }
    std::string out = "";
    std::string allDelimiters = " ()[],;:'!&|=<>+-*/^%~" + Chr(34) + Chr(9) + Chr(11);
    std::vector<std::string> arrAll;
    std::vector<std::string> items43 = LoopParseFunc(line);
    for (size_t A_Index43 = 0; A_Index43 < items43.size() + 0; A_Index43++) {
        std::string A_LoopField43 = items43[A_Index43 - 0];
        HTVM_Append(arrAll, A_LoopField43);
    }
    int i1 = 0;
    std::string tempHold = "";
    int holdPos = 0;
    std::vector<int> holdPositions;
    for (int A_Index44 = 0; A_Index44 < HTVM_Size(arrAll) + 0; A_Index44++) {
        tempHold = "";
        if (HTVM_Size(arrAll) - StrLen(arrayProcStr) + 1 == i1) {
            break;
        }
        for (int A_Index45 = 0; A_Index45 < StrLen(arrayProcStr) + 0; A_Index45++) {
            tempHold += arrAll[A_Index45 + i1];
        }
        i1++;
        //print(tempHold)
        if (tempHold == arrayProcStr) {
            holdPos = i1;
            //print(holdPos)
            HTVM_Append(holdPositions, holdPos);
        }
    }
    //print("===========================================")
    int holdPositionsTEMP = 0;
    for (int A_Index46 = 0; A_Index46 < HTVM_Size(holdPositions) + 0; A_Index46++) {
        holdPositionsTEMP = holdPositions[A_Index46];
        i1 = HTVM_Size(arrAll);
        tempHold = "";
        for (int A_Index47 = 0; A_Index47 < HTVM_Size(arrAll) + 0; A_Index47++) {
            if (holdPositionsTEMP >= i1 + 1) {
                if (InStr(allDelimiters, arrAll[i1]) == false) {
                    tempHold += arrAll[i1 - 1];
                } else {
                    break;
                }
            }
            i1--;
        }
        //print(StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", ""))))
        holdPositions[A_Index46] = holdPositions[A_Index46] - StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", "")));
    }
    //;;;;;;;;;;;;;;;;;;
    int foundFirstParenthesis = 0;
    int ParenthesisStackOPEN = 0;
    int ParenthesisStackCLOSE = 0;
    std::vector<int> holdPositionsEnd;
    holdPositionsTEMP = 0;
    for (int A_Index48 = 0; A_Index48 < HTVM_Size(holdPositions) + 0; A_Index48++) {
        holdPositionsTEMP = holdPositions[A_Index48];
        i1 = 0;
        tempHold = "";
        foundFirstParenthesis = 0;
        ParenthesisStackOPEN = 0;
        ParenthesisStackCLOSE = 0;
        for (int A_Index49 = 0; A_Index49 < HTVM_Size(arrAll) + 0; A_Index49++) {
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
                    HTVM_Append(holdPositionsEnd, i1 + 1);
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
    for (int A_Index50 = 0; A_Index50 < HTVM_Size(holdPositions) + 0; A_Index50++) {
        startPosReplace = holdPositions[HTVM_Size(holdPositions) - A_Index50 - 1];
        endPosReplace = holdPositionsEnd[HTVM_Size(holdPositions) - A_Index50 - 1];
        holdDebug = "";
        beenInside = 0;
        holdDebugLen = 0;
        canOut = 1;
        std::vector<std::string> items51 = LoopParseFunc(line);
        for (size_t A_Index51 = 0; A_Index51 < items51.size() + 0; A_Index51++) {
            std::string A_LoopField51 = items51[A_Index51 - 0];
            if (A_Index51 + 1 >= startPosReplace && A_Index51 + 1 <= endPosReplace) {
                holdDebug += A_LoopField51;
            }
        }
        holdDebugLen = StrLen(holdDebug);
        std::vector<std::string> items52 = LoopParseFunc(line);
        for (size_t A_Index52 = 0; A_Index52 < items52.size() + 0; A_Index52++) {
            std::string A_LoopField52 = items52[A_Index52 - 0];
            if (A_Index52 + 1 >= startPosReplace && A_Index52 + 1 <= endPosReplace) {
                beenInside++;
            }
            if (beenInside == 1) {
                out += fixArray123(holdDebug, arrayProcStr, mode);
                canOut = 0;
            } else {
                if (canOut == 0) {
                    holdDebugLen--;
                    if (holdDebugLen == 0) {
                        canOut = 1;
                    }
                }
                if (canOut == 1) {
                    out += A_LoopField52;
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
    if (langToConvertTo == langFileExtension_2) {
        line = HTVMmatchStrRrplace(line, keyWordArrayAppend + "(", keyWordArrayAppend_2 + "(");
        line = HTVMmatchStrRrplace(line, keyWordArrayPop + "(", keyWordArrayPop_2 + "(");
        line = HTVMmatchStrRrplace(line, keyWordArraySize + "(", keyWordArraySize_2 + "(");
        line = HTVMmatchStrRrplace(line, keyWordArrayInsert + "(", keyWordArrayInsert_2 + "(");
        line = HTVMmatchStrRrplace(line, keyWordArrayRemove + "(", keyWordArrayRemove_2 + "(");
        line = HTVMmatchStrRrplace(line, keyWordArrayIndexOf + "(", keyWordArrayIndexOf_2 + "(");
    } else {
        line = arrayParserTranspiler1(line, keyWordArrayAppend + "(", 1);
        line = arrayParserTranspiler1(line, keyWordArrayPop + "(", 2);
        line = arrayParserTranspiler1(line, keyWordArraySize + "(", 3);
        line = arrayParserTranspiler1(line, keyWordArrayInsert + "(", 4);
        line = arrayParserTranspiler1(line, keyWordArrayRemove + "(", 5);
        line = arrayParserTranspiler1(line, keyWordArrayIndexOf + "(", 6);
    }
    return line;
}
std::string getFuncTypeConvert(std::string type) {
    std::string theType = "";
    type = Trim(type);
    if (allVarsSoWeDontReDecVars_FIX_TOGGLE == 1) {
        if (type == keyWordUint8) {
            HTVM_Append(allVarsSoWeDontReDecVars_FIX_uint8, str2);
        }
        if (type == keyWordUint16) {
            HTVM_Append(allVarsSoWeDontReDecVars_FIX_uint16, str2);
        }
        if (type == keyWordUint32) {
            HTVM_Append(allVarsSoWeDontReDecVars_FIX_uint32, str2);
        }
        if (type == keyWordUint64) {
            HTVM_Append(allVarsSoWeDontReDecVars_FIX_uint64, str2);
        }
        if (type == keyWordFLOAT) {
            HTVM_Append(allVarsSoWeDontReDecVars_FIX_float, str2);
        }
        if (type == keyWordINT64) {
            HTVM_Append(allVarsSoWeDontReDecVars_FIX_int64, str2);
        }
        if (langToConvertTo == "java") {
            if (type == keyWordINT8) {
                HTVM_Append(allVarsSoWeDontReDecVars_FIX_uint8, str2);
            }
            if (type == keyWordINT16) {
                HTVM_Append(allVarsSoWeDontReDecVars_FIX_uint16, str2);
            }
        }
    }
    if (langToConvertTo == "cpp") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "double";
        }
        if (type == keyWordChar) {
            theType = "char";
        }
        if (type == keyWordUint8) {
            theType = "uint8_t";
        }
        if (type == keyWordUint16) {
            theType = "uint16_t";
        }
        if (type == keyWordUint32) {
            theType = "uint32_t";
        }
        if (type == keyWordUint64) {
            theType = "uint64_t";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "std::string";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "float";
        }
        if (type == keyWordINT8) {
            theType = "int8_t";
        }
        if (type == keyWordINT16) {
            theType = "int16_t";
        }
        if (type == keyWordINT32) {
            theType = "int32_t";
        }
        if (type == keyWordINT64) {
            theType = "int64_t";
        }
        if (type == keyWordArrayDefinition) {
            theType = "std::vector<std::string>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "std::vector<int>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "std::vector<std::string>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "std::vector<float>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "std::vector<bool>";
        }
    }
    if (langToConvertTo == "py") {
        theType = "";
    }
    if (langToConvertTo == "js") {
        theType = "";
    }
    if (langToConvertTo == "go") {
        if (type == keyWordVoid) {
            theType = "";
        }
        if (type == keyWordDouble) {
            theType = "float64";
        }
        if (type == keyWordChar) {
            theType = "byte";
        }
        if (type == keyWordUint8) {
            theType = "uint8";
        }
        if (type == keyWordUint16) {
            theType = "uint16";
        }
        if (type == keyWordUint32) {
            theType = "uint32";
        }
        if (type == keyWordUint64) {
            theType = "uint64";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "string";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "float64";
        }
        if (type == keyWordINT8) {
            theType = "int8";
        }
        if (type == keyWordINT16) {
            theType = "int16";
        }
        if (type == keyWordINT32) {
            theType = "int32";
        }
        if (type == keyWordINT64) {
            theType = "int64";
        }
        if (type == keyWordArrayDefinition) {
            theType = "[]string";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "[]int";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "[]string";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "[]float64";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "[]bool";
        }
    }
    if (langToConvertTo == "lua") {
        theType = "";
    }
    if (langToConvertTo == "cs") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "double";
        }
        if (type == keyWordChar) {
            theType = "char";
        }
        if (type == keyWordUint8) {
            theType = "byte";
        }
        if (type == keyWordUint16) {
            theType = "ushort";
        }
        if (type == keyWordUint32) {
            theType = "uint";
        }
        if (type == keyWordUint64) {
            theType = "ulong";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "string";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "float";
        }
        if (type == keyWordINT8) {
            theType = "sbyte";
        }
        if (type == keyWordINT16) {
            theType = "short";
        }
        if (type == keyWordINT32) {
            theType = "int";
        }
        if (type == keyWordINT64) {
            theType = "long";
        }
        if (type == keyWordArrayDefinition) {
            theType = "List<string>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "List<int>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "List<string>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "List<double>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "List<bool>";
        }
    }
    if (langToConvertTo == "java") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "double";
        }
        if (type == keyWordChar) {
            theType = "char";
        }
        if (type == keyWordUint8) {
            theType = "byte ";
        }
        if (type == keyWordUint16) {
            theType = "short";
        }
        if (type == keyWordUint32) {
            theType = "int";
        }
        if (type == keyWordUint64) {
            theType = "long";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "String";
        }
        if (type == keyWordBOOL) {
            theType = "boolean";
        }
        if (type == keyWordFLOAT) {
            theType = "float";
        }
        if (type == keyWordINT8) {
            theType = "byte";
        }
        if (type == keyWordINT16) {
            theType = "short";
        }
        if (type == keyWordINT32) {
            theType = "int";
        }
        if (type == keyWordINT64) {
            theType = "long";
        }
        if (type == keyWordArrayDefinition) {
            theType = "ArrayList<String>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "ArrayList<Integer>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "ArrayList<String>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "ArrayList<Double>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "ArrayList<Boolean>";
        }
    }
    if (langToConvertTo == "kt") {
        if (type == keyWordVoid) {
            theType = "";
        }
        if (type == keyWordDouble) {
            theType = "Double";
        }
        if (type == keyWordChar) {
            theType = "Char";
        }
        if (type == keyWordUint8) {
            theType = "UByte";
        }
        if (type == keyWordUint16) {
            theType = "UShort";
        }
        if (type == keyWordUint32) {
            theType = "UInt";
        }
        if (type == keyWordUint64) {
            theType = "ULong";
        }
        if (type == keyWordINT) {
            theType = "Int";
        }
        if (type == keyWordSTR) {
            theType = "String";
        }
        if (type == keyWordBOOL) {
            theType = "Boolean";
        }
        if (type == keyWordFLOAT) {
            theType = "Float";
        }
        if (type == keyWordINT8) {
            theType = "Byte";
        }
        if (type == keyWordINT16) {
            theType = "Short";
        }
        if (type == keyWordINT32) {
            theType = "Int";
        }
        if (type == keyWordINT64) {
            theType = "Long";
        }
        if (type == keyWordArrayDefinition) {
            theType = "ArrayList<String>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "ArrayList<Int>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "ArrayList<String>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "ArrayList<Float>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "ArrayList<Boolean>";
        }
    }
    if (langToConvertTo == "rb") {
        theType = "";
    }
    if (langToConvertTo == "nim") {
        if (type == keyWordVoid) {
            theType = "";
        }
        if (type == keyWordDouble) {
            theType = "float";
        }
        if (type == keyWordChar) {
            theType = "char";
        }
        if (type == keyWordUint8) {
            theType = "uint8";
        }
        if (type == keyWordUint16) {
            theType = "uint16";
        }
        if (type == keyWordUint32) {
            theType = "uint32";
        }
        if (type == keyWordUint64) {
            theType = "uint64";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "string";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "float";
        }
        if (type == keyWordINT8) {
            theType = "int8";
        }
        if (type == keyWordINT16) {
            theType = "int16";
        }
        if (type == keyWordINT32) {
            theType = "int32";
        }
        if (type == keyWordINT64) {
            theType = "int64";
        }
        if (type == keyWordArrayDefinition) {
            theType = "seq[string]";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "seq[int]";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "seq[string]";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "seq[float64]";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "seq[bool]";
        }
    }
    if (langToConvertTo == "ahk") {
        theType = "";
    }
    if (langToConvertTo == "swift") {
        if (type == keyWordVoid) {
            theType = "";
        }
        if (type == keyWordDouble) {
            theType = "Double";
        }
        if (type == keyWordChar) {
            theType = "Character";
        }
        if (type == keyWordUint8) {
            theType = "UInt8";
        }
        if (type == keyWordUint16) {
            theType = "UInt16";
        }
        if (type == keyWordUint32) {
            theType = "UInt32";
        }
        if (type == keyWordUint64) {
            theType = "UInt64";
        }
        if (type == keyWordINT) {
            theType = "Int";
        }
        if (type == keyWordSTR) {
            theType = "String";
        }
        if (type == keyWordBOOL) {
            theType = "Bool";
        }
        if (type == keyWordFLOAT) {
            theType = "Float";
        }
        if (type == keyWordINT8) {
            theType = "Int8";
        }
        if (type == keyWordINT16) {
            theType = "Int16";
        }
        if (type == keyWordINT32) {
            theType = "Int32";
        }
        if (type == keyWordINT64) {
            theType = "Int64";
        }
        if (type == keyWordArrayDefinition) {
            theType = "inout [String]";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "inout [Int]";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "inout [String]";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "inout [Float]";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "inout [Bool]";
        }
    }
    if (langToConvertTo == "dart") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "double";
        }
        if (type == keyWordChar) {
            theType = "String";
        }
        if (type == keyWordUint8) {
            theType = "int";
        }
        if (type == keyWordUint16) {
            theType = "int";
        }
        if (type == keyWordUint32) {
            theType = "int";
        }
        if (type == keyWordUint64) {
            theType = "BigInt";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "String";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "double";
        }
        if (type == keyWordINT8) {
            theType = "int";
        }
        if (type == keyWordINT16) {
            theType = "int";
        }
        if (type == keyWordINT32) {
            theType = "int";
        }
        if (type == keyWordINT64) {
            theType = "int";
        }
        if (type == keyWordArrayDefinition) {
            theType = "List<String>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "List<int>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "List<String>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "List<double>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "List<bool>";
        }
    }
    if (langToConvertTo == "ts") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "number";
        }
        if (type == keyWordChar) {
            theType = "string";
        }
        if (type == keyWordUint8) {
            theType = "number";
        }
        if (type == keyWordUint16) {
            theType = "number";
        }
        if (type == keyWordUint32) {
            theType = "number";
        }
        if (type == keyWordUint64) {
            theType = "bigint";
        }
        if (type == keyWordINT) {
            theType = "number";
        }
        if (type == keyWordSTR) {
            theType = "string";
        }
        if (type == keyWordBOOL) {
            theType = "boolean";
        }
        if (type == keyWordFLOAT) {
            theType = "number";
        }
        if (type == keyWordINT8) {
            theType = "number";
        }
        if (type == keyWordINT16) {
            theType = "number";
        }
        if (type == keyWordINT32) {
            theType = "number";
        }
        if (type == keyWordINT64) {
            theType = "bigint";
        }
        if (type == keyWordArrayDefinition) {
            theType = "string[]";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "number[]";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "string[]";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "number[]";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "boolean[]";
        }
    }
    if (langToConvertTo == "groovy") {
        theType = "";
    }
    if (langToConvertTo == langFileExtension_2) {
        // keyWordVoid
        // keyWordDouble
        // keyWordChar
        // keyWordUint8
        // keyWordUint16
        // keyWordUint32
        // keyWordUint64
        // keyWordINT
        // keyWordSTR
        // keyWordBOOL
        // keyWordFLOAT
        // keyWordINT8
        // keyWordINT16
        // keyWordINT32
        // keyWordINT64
        // keyWordArrayDefinition
        // keyWordArrayOfIntegersDefinition
        // keyWordArrayOfStringsDefinition
        // keyWordArrayOfFloatingPointNumbersDefinition
        // keyWordArrayOfBooleansDefinition
        if (type == keyWordVoid) {
            theType = keyWordVoid_2;
        }
        if (type == keyWordDouble) {
            theType = keyWordDouble_2;
        }
        if (type == keyWordChar) {
            theType = keyWordChar_2;
        }
        if (type == keyWordUint8) {
            theType = keyWordUint8_2;
        }
        if (type == keyWordUint16) {
            theType = keyWordUint16_2;
        }
        if (type == keyWordUint32) {
            theType = keyWordUint32_2;
        }
        if (type == keyWordUint64) {
            theType = keyWordUint64_2;
        }
        if (type == keyWordINT) {
            theType = keyWordINT_2;
        }
        if (type == keyWordSTR) {
            theType = keyWordSTR_2;
        }
        if (type == keyWordBOOL) {
            theType = keyWordBOOL_2;
        }
        if (type == keyWordFLOAT) {
            theType = keyWordFLOAT_2;
        }
        if (type == keyWordINT8) {
            theType = keyWordINT8_2;
        }
        if (type == keyWordINT16) {
            theType = keyWordINT16_2;
        }
        if (type == keyWordINT32) {
            theType = keyWordINT32_2;
        }
        if (type == keyWordINT64) {
            theType = keyWordINT64_2;
        }
        if (type == keyWordArrayDefinition) {
            theType = keyWordArrayDefinition_2;
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = keyWordArrayOfIntegersDefinition_2;
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = keyWordArrayOfStringsDefinition_2;
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = keyWordArrayOfFloatingPointNumbersDefinition_2;
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = keyWordArrayOfBooleansDefinition_2;
        }
    }
    return theType;
}
std::string getTheLastWord(std::string line) {
    if (InStr(Trim(line), " ") == false) {
        return line;
    }
    std::vector<std::string> items53 = LoopParseFunc(line, " ");
    for (size_t A_Index53 = 0; A_Index53 < items53.size() + 0; A_Index53++) {
        std::string A_LoopField53 = items53[A_Index53 - 0];
        line = A_LoopField53;
    }
    return line;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
bool OSPhelp(std::string line, std::string keyWorddddddddddddd) {
    std::vector<std::string> lookAhead;
    std::vector<std::string> items54 = LoopParseFunc(line, "\n", "\r");
    for (size_t A_Index54 = 0; A_Index54 < items54.size() + 0; A_Index54++) {
        std::string A_LoopField54 = items54[A_Index54 - 0];
        HTVM_Append(lookAhead, A_LoopField54);
    }
    HTVM_Append(lookAhead, " ");
    std::vector<std::string> items55 = LoopParseFunc(line, "\n", "\r");
    for (size_t A_Index55 = 0; A_Index55 < items55.size() + 0; A_Index55++) {
        std::string A_LoopField55 = items55[A_Index55 - 0];
        if (SubStr(Trim(StrLower(A_LoopField55)), 1, StrLen(keyWorddddddddddddd)) == StrLower(keyWorddddddddddddd) && lookAhead[A_Index55 + 1] == "{") {
            return true;
        }
        if (SubStr(Trim(StrLower(A_LoopField55)), 1, StrLen(keyWorddddddddddddd)) == StrLower(keyWorddddddddddddd) && lookAhead[A_Index55 + 1] == "{") {
            return true;
        }
        if (SubStr(Trim(StrLower(A_LoopField55)), 1, StrLen(StrLower(keyWorddddddddddddd))) == StrLower(keyWorddddddddddddd) && lookAhead[A_Index55 + 1] == "{") {
            return true;
        }
    }
    return false;
}
std::string OSP(std::string line) {
    std::string lineOriginal = line;
    std::string outOSP = "";
    std::vector<std::string> lookAhead;
    std::vector<std::string> items56 = LoopParseFunc(line, "\n", "\r");
    for (size_t A_Index56 = 0; A_Index56 < items56.size() + 0; A_Index56++) {
        std::string A_LoopField56 = items56[A_Index56 - 0];
        HTVM_Append(lookAhead, A_LoopField56);
    }
    HTVM_Append(lookAhead, " ");
    std::vector<std::string> stack;
    int inConstructOSP = 0;
    int countParentheses = 0;
    int countParenthesesStart = 0;
    int countParenthesesOfSet = 0;
    std::string stackRN = "";
    int alredy = 0;
    outOSP = "";
    if (OSPhelp(line, keyWordAlliance)) {
        std::vector<std::string> items57 = LoopParseFunc(line, "\n", "\r");
        for (size_t A_Index57 = 0; A_Index57 < items57.size() + 0; A_Index57++) {
            std::string A_LoopField57 = items57[A_Index57 - 0];
            if (SubStr(Trim(StrLower(A_LoopField57)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance) && lookAhead[A_Index57 + 1] == "{") {
                //print(A_LoopField)
                stackRN = A_LoopField57;
                countParentheses = 0;
                countParenthesesStart = 0;
            }
            if (A_LoopField57 == "{") {
                countParentheses++;
                countParenthesesStart = 1;
            }
            if (A_LoopField57 == "}") {
                countParentheses--;
            }
            if (countParenthesesStart == 1 && countParentheses == 0) {
                // escaped
                countParentheses = 0;
                countParenthesesStart = 0;
                alredy = 1;
                outOSP += A_LoopField57 + "_HTVM-OSP-HTVM-OSP-REMOVE-OSP-HTVMv2--OSP" + Chr(10);
                countParentheses = 1;
            }
            if (alredy == 0) {
                outOSP += A_LoopField57 + "" + Chr(10);
            }
            alredy = 0;
        }
        outOSP = StringTrimRight(outOSP, 1);
        line = outOSP;
    }
    inConstructOSP = 0;
    countParentheses = 0;
    countParenthesesStart = 0;
    countParenthesesOfSet = 0;
    stackRN = "";
    alredy = 0;
    outOSP = "";
    if (OSPhelp(line, keyWordCrew)) {
        std::vector<std::string> items58 = LoopParseFunc(line, "\n", "\r");
        for (size_t A_Index58 = 0; A_Index58 < items58.size() + 0; A_Index58++) {
            std::string A_LoopField58 = items58[A_Index58 - 0];
            if (SubStr(Trim(StrLower(A_LoopField58)), 1, StrLen(keyWordCrew)) == StrLower(keyWordCrew) && lookAhead[A_Index58 + 1] == "{") {
                //print(A_LoopField)
                stackRN = A_LoopField58;
                countParentheses = 0;
                countParenthesesStart = 0;
            }
            if (A_LoopField58 == "{") {
                countParentheses++;
                countParenthesesStart = 1;
            }
            if (A_LoopField58 == "}") {
                countParentheses--;
            }
            if (countParenthesesStart == 1 && countParentheses == 0) {
                // escaped
                countParentheses = 0;
                countParenthesesStart = 0;
                alredy = 1;
                outOSP += A_LoopField58 + "_HTVM-OSP-HTVM-OSP-REMOVE-OSP-HTVMv2--OSP" + Chr(10);
                countParentheses = 1;
            }
            if (alredy == 0) {
                outOSP += A_LoopField58 + "" + Chr(10);
            }
            alredy = 0;
        }
        outOSP = StringTrimRight(outOSP, 1);
        line = outOSP;
    }
    inConstructOSP = 0;
    countParentheses = 0;
    countParenthesesStart = 0;
    countParenthesesOfSet = 0;
    stackRN = "";
    alredy = 0;
    outOSP = "";
    if (OSPhelp(line, keyWordStruct)) {
        std::vector<std::string> items59 = LoopParseFunc(line, "\n", "\r");
        for (size_t A_Index59 = 0; A_Index59 < items59.size() + 0; A_Index59++) {
            std::string A_LoopField59 = items59[A_Index59 - 0];
            if (SubStr(Trim(StrLower(A_LoopField59)), 1, StrLen(keyWordStruct)) == StrLower(keyWordStruct) && lookAhead[A_Index59 + 1] == "{") {
                //print(A_LoopField)
                stackRN = A_LoopField59;
                countParentheses = 0;
                countParenthesesStart = 0;
            }
            if (A_LoopField59 == "{") {
                countParentheses++;
                countParenthesesStart = 1;
            }
            if (A_LoopField59 == "}") {
                countParentheses--;
            }
            if (countParenthesesStart == 1 && countParentheses == 0) {
                // escaped
                countParentheses = 0;
                countParenthesesStart = 0;
                alredy = 1;
                outOSP += A_LoopField59 + "_HTVM-OSP-HTVM-OSP-REMOVE-OSP-HTVMv2--OSP" + Chr(10);
                countParentheses = 1;
            }
            if (alredy == 0) {
                outOSP += A_LoopField59 + "" + Chr(10);
            }
            alredy = 0;
        }
        line = outOSP;
    }
    inConstructOSP = 0;
    countParentheses = 0;
    countParenthesesStart = 0;
    countParenthesesOfSet = 0;
    stackRN = "";
    alredy = 0;
    int inOBJ = 0;
    std::string tempStackText = "";
    outOSP = "";
    std::vector<std::string> items60 = LoopParseFunc(line, "\n", "\r");
    for (size_t A_Index60 = 0; A_Index60 < items60.size() + 0; A_Index60++) {
        std::string A_LoopField60 = items60[A_Index60 - 0];
        if (SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordStruct)) == StrLower(keyWordStruct) && lookAhead[A_Index60 + 1] == "{") {
            str1 = Trim(StringTrimLeft(A_LoopField60, StrLen(SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordStruct)))));
            HTVM_Append(ospDic, str1);
            alredy = 2;
            inOBJ = 1;
            tempStackText = "";
            for (int A_Index61 = 0; A_Index61 < HTVM_Size(ospDic) + 0; A_Index61++) {
                tempStackText += ospDic[A_Index61] + ".";
            }
            tempStackText = StringTrimRight(tempStackText, 1);
            outOSP += "[][][][][] " + StrReplace(tempStackText, ".", "_") + " [][][][][]" + Chr(10);
        }
        if (SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordProp)) == StrLower(keyWordProp)) {
            tempStackText = "";
            for (int A_Index62 = 0; A_Index62 < HTVM_Size(ospDic) + 0; A_Index62++) {
                tempStackText += ospDic[A_Index62] + ".";
            }
            tempStackText = StringTrimRight(tempStackText, 1);
            outOSP += A_LoopField60 + "-----------------------HTVM-OSP-HTVM-OBJ--------------" + tempStackText + Chr(10);
        }
        if (SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordProc)) == StrLower(keyWordProc) && lookAhead[A_Index60 + 1] == "{") {
            tempStackText = "";
            for (int A_Index63 = 0; A_Index63 < HTVM_Size(ospDic) + 0; A_Index63++) {
                tempStackText += ospDic[A_Index63] + ".";
            }
            tempStackText = StringTrimRight(tempStackText, 1);
            alredy = 1;
            outOSP += A_LoopField60 + "-----------------------HTVM-OSP-HTVM-OBJ-------------- " + "OSPHTVMOSP_" + StrReplace(tempStackText, ".", "_") + Chr(10);
        }
        if (SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordCrew)) == StrLower(keyWordCrew) && lookAhead[A_Index60 + 1] == "{") {
            str1 = Trim(StringTrimLeft(A_LoopField60, StrLen(SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordCrew)))));
            //print("DEBUG11111111111111111111: " + str1)
            HTVM_Append(ospDic, str1);
            //print(A_LoopField)
            alredy = 2;
        }
        if (SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordAlliance)) == StrLower(keyWordAlliance) && lookAhead[A_Index60 + 1] == "{") {
            str1 = Trim(StringTrimLeft(A_LoopField60, StrLen(SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordAlliance)))));
            HTVM_Append(ospDic, str1);
            //print(A_LoopField)
            alredy = 2;
        }
        if (A_LoopField60 == "}_HTVM-OSP-HTVM-OSP-REMOVE-OSP-HTVMv2--OSP") {
            if (inOBJ == 1) {
                // extra code
                tempStackText = "";
                for (int A_Index64 = 0; A_Index64 < HTVM_Size(ospDic) + 0; A_Index64++) {
                    tempStackText += ospDic[A_Index64] + ".";
                }
                tempStackText = StringTrimRight(tempStackText, 1);
                outOSP += "[end][end][end][end][end] " + StrReplace(tempStackText, ".", "_") + " [end][end][end][end][end]" + Chr(10);
                inOBJ = 0;
            }
            alredy = 1;
            HTVM_Pop(ospDic);
        }
        if (alredy <= 0) {
            outOSP += A_LoopField60 + "" + Chr(10);
        }
        alredy--;
    }
    outOSP = StringTrimRight(outOSP, 1);
    if (Trim(outOSP) == "") {
        return lineOriginal;
    }
    return outOSP;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string fixGoAindexUnseen(std::string codeToFixTheGoUNSEEN) {
    std::string tempFixBugInfLoop = "";
    std::string AindexKeyWOrd = keyWordAIndex;
    // Regex to find all A_Index<num> occurrences
    std::vector<std::string> fixAindexInGoUnused;
    std::string tempFixIDK = "";
    int howMany_fixAindexInGoUnusedNUM = 0;
    int found_fixAindexInGoUnused = 0;
    std::string foundWHAT_fixAindexInGoUnused = "";
    std::vector<std::string> items65 = LoopParseFunc(codeToFixTheGoUNSEEN, "\n", "\r");
    for (size_t A_Index65 = 0; A_Index65 < items65.size() + 0; A_Index65++) {
        std::string A_LoopField65 = items65[A_Index65 - 0];
        if (RegExMatch(A_LoopField65, AindexKeyWOrd + "\\d+")) {
            if (SubStr(Trim(A_LoopField65), 1, 4) != "for ") {
                tempFixBugInfLoop = "";
                std::vector<std::string> items66 = LoopParseFunc(A_LoopField65, " ");
                for (size_t A_Index66 = 0; A_Index66 < items66.size() + 0; A_Index66++) {
                    std::string A_LoopField66 = items66[A_Index66 - 0];
                    if (InStr(A_LoopField66, AindexKeyWOrd)) {
                        tempFixBugInfLoop = ExtractDigits(StrSplit(A_LoopField66, AindexKeyWOrd, 2));
                        break;
                    }
                }
                HTVM_Append(fixAindexInGoUnused, AindexKeyWOrd + tempFixBugInfLoop);
            }
        }
    }
    howMany_fixAindexInGoUnused++;
    howMany_fixAindexInGoUnused++;
    for (int A_Index67 = 0; A_Index67 < howMany_fixAindexInGoUnused + 0; A_Index67++) {
        howMany_fixAindexInGoUnusedNUM = A_Index67;
        found_fixAindexInGoUnused = 0;
        foundWHAT_fixAindexInGoUnused = AindexKeyWOrd + STR(howMany_fixAindexInGoUnusedNUM);
        for (int A_Index68 = 0; A_Index68 < HTVM_Size(fixAindexInGoUnused) + 0; A_Index68++) {
            if (fixAindexInGoUnused[A_Index68] == AindexKeyWOrd + STR(howMany_fixAindexInGoUnusedNUM)) {
                found_fixAindexInGoUnused = 1;
                break;
            }
        }
        if (foundWHAT_fixAindexInGoUnused != "") {
            if (found_fixAindexInGoUnused == 0) {
                tempFixIDK = "";
                std::vector<std::string> items69 = LoopParseFunc(codeToFixTheGoUNSEEN, "\n", "\r");
                for (size_t A_Index69 = 0; A_Index69 < items69.size() + 0; A_Index69++) {
                    std::string A_LoopField69 = items69[A_Index69 - 0];
                    if (InStr(A_LoopField69, " := range ")) {
                        tempFixIDK += StrReplace(A_LoopField69, foundWHAT_fixAindexInGoUnused, "_") + Chr(10);
                    } else {
                        tempFixIDK += StrReplace(A_LoopField69, foundWHAT_fixAindexInGoUnused, "i") + Chr(10);
                    }
                }
                codeToFixTheGoUNSEEN = StringTrimRight(tempFixIDK, 1);
            }
        }
    }
    return codeToFixTheGoUNSEEN;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::vector<std::string> GETfullLangAllOperators() {
    std::vector<std::string> fullLangAllOperators;
    if (langToConvertTo == "cpp") {
        HTVM_Append(fullLangAllOperators, "nullptr");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "py") {
        HTVM_Append(fullLangAllOperators, "None");
        HTVM_Append(fullLangAllOperators, "True");
        HTVM_Append(fullLangAllOperators, "False");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "**");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "is");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "and");
        HTVM_Append(fullLangAllOperators, "or");
        HTVM_Append(fullLangAllOperators, "not");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "js") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "**");
        if (useJavaScriptAlwaysTripleEqual == "on") {
            HTVM_Append(fullLangAllOperators, "===");
        } else {
            HTVM_Append(fullLangAllOperators, "==");
        }
        HTVM_Append(fullLangAllOperators, "===");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, ">>>");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "go") {
        HTVM_Append(fullLangAllOperators, "nil");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR");
    }
    if (langToConvertTo == "lua") {
        HTVM_Append(fullLangAllOperators, "nil");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "..");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "~=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "and");
        HTVM_Append(fullLangAllOperators, "or");
        HTVM_Append(fullLangAllOperators, "not");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "cs") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "java") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, ">>>");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "kt") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "===");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "and");
        HTVM_Append(fullLangAllOperators, "or");
        HTVM_Append(fullLangAllOperators, "xor");
        HTVM_Append(fullLangAllOperators, "inv");
        HTVM_Append(fullLangAllOperators, "shl");
        HTVM_Append(fullLangAllOperators, "shr");
        HTVM_Append(fullLangAllOperators, "ushr");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "rb") {
        HTVM_Append(fullLangAllOperators, "nil");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "**");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "nim") {
        HTVM_Append(fullLangAllOperators, "nil");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "HTVM--Fix-Nim-TheConcat-NOT--Working--AA");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "mod");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "and");
        HTVM_Append(fullLangAllOperators, "or");
        HTVM_Append(fullLangAllOperators, "not");
        HTVM_Append(fullLangAllOperators, "and");
        HTVM_Append(fullLangAllOperators, "or");
        HTVM_Append(fullLangAllOperators, "xor");
        HTVM_Append(fullLangAllOperators, "not");
        HTVM_Append(fullLangAllOperators, "shl");
        HTVM_Append(fullLangAllOperators, "shr");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "ahk") {
        HTVM_Append(fullLangAllOperators, Chr(34) + "" + Chr(34));
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, ".");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "=");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "swift") {
        HTVM_Append(fullLangAllOperators, "nil");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "===");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "dart") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "===");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, ">>>");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "ts") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "**");
        if (useJavaScriptAlwaysTripleEqual == "on") {
            HTVM_Append(fullLangAllOperators, "===");
        } else {
            HTVM_Append(fullLangAllOperators, "==");
        }
        HTVM_Append(fullLangAllOperators, "===");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, ">>>");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "groovy") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "**");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, ">>>");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == langFileExtension_2) {
        HTVM_Append(fullLangAllOperators, keyWordNull_2);
        HTVM_Append(fullLangAllOperators, keyWordTrue_2);
        HTVM_Append(fullLangAllOperators, keyWordFalse_2);
        HTVM_Append(fullLangAllOperators, keyWordConcat_2);
        HTVM_Append(fullLangAllOperators, keyWordAdd_2);
        HTVM_Append(fullLangAllOperators, keyWordSub_2);
        HTVM_Append(fullLangAllOperators, keyWordMul_2);
        HTVM_Append(fullLangAllOperators, keyWordDiv_2);
        HTVM_Append(fullLangAllOperators, keyWordMod_2);
        HTVM_Append(fullLangAllOperators, keyWordExp_2);
        HTVM_Append(fullLangAllOperators, keyWordEqual_2);
        HTVM_Append(fullLangAllOperators, keyWordStrictEqual_2);
        HTVM_Append(fullLangAllOperators, keyWordNotEqual_2);
        HTVM_Append(fullLangAllOperators, keyWordGreater_2);
        HTVM_Append(fullLangAllOperators, keyWordLess_2);
        HTVM_Append(fullLangAllOperators, keyWordGreaterEqual_2);
        HTVM_Append(fullLangAllOperators, keyWordLessEqual_2);
        HTVM_Append(fullLangAllOperators, keyWordAnd_2);
        HTVM_Append(fullLangAllOperators, keyWordOr_2);
        HTVM_Append(fullLangAllOperators, keyWordNot_2);
        HTVM_Append(fullLangAllOperators, keyWordBitAnd_2);
        HTVM_Append(fullLangAllOperators, keyWordBitOr_2);
        HTVM_Append(fullLangAllOperators, keyWordBitXor_2);
        HTVM_Append(fullLangAllOperators, keyWordBitNot_2);
        HTVM_Append(fullLangAllOperators, keyWordShiftLeft_2);
        HTVM_Append(fullLangAllOperators, keyWordShiftRight_2);
        HTVM_Append(fullLangAllOperators, keyWordShiftUnsignedRight_2);
        HTVM_Append(fullLangAllOperators, keyWordTernary1_2);
        HTVM_Append(fullLangAllOperators, keyWordTernary2_2);
    }
    return fullLangAllOperators;
}
std::vector<std::string> GETfullLangAllOperators_HELP() {
    std::vector<std::string> fullLangAllOperators_HELP;
    HTVM_Append(fullLangAllOperators_HELP, keyWordNull);
    HTVM_Append(fullLangAllOperators_HELP, keyWordTrue);
    HTVM_Append(fullLangAllOperators_HELP, keyWordFalse);
    HTVM_Append(fullLangAllOperators_HELP, keyWordConcat);
    HTVM_Append(fullLangAllOperators_HELP, keyWordAdd);
    HTVM_Append(fullLangAllOperators_HELP, keyWordSub);
    HTVM_Append(fullLangAllOperators_HELP, keyWordMul);
    HTVM_Append(fullLangAllOperators_HELP, keyWordDiv);
    HTVM_Append(fullLangAllOperators_HELP, keyWordMod);
    HTVM_Append(fullLangAllOperators_HELP, keyWordExp);
    HTVM_Append(fullLangAllOperators_HELP, keyWordEqual);
    HTVM_Append(fullLangAllOperators_HELP, keyWordStrictEqual);
    HTVM_Append(fullLangAllOperators_HELP, keyWordNotEqual);
    HTVM_Append(fullLangAllOperators_HELP, keyWordGreater);
    HTVM_Append(fullLangAllOperators_HELP, keyWordLess);
    HTVM_Append(fullLangAllOperators_HELP, keyWordGreaterEqual);
    HTVM_Append(fullLangAllOperators_HELP, keyWordLessEqual);
    HTVM_Append(fullLangAllOperators_HELP, keyWordAnd);
    HTVM_Append(fullLangAllOperators_HELP, keyWordOr);
    HTVM_Append(fullLangAllOperators_HELP, keyWordNot);
    HTVM_Append(fullLangAllOperators_HELP, keyWordBitAnd);
    HTVM_Append(fullLangAllOperators_HELP, keyWordBitOr);
    HTVM_Append(fullLangAllOperators_HELP, keyWordBitXor);
    HTVM_Append(fullLangAllOperators_HELP, keyWordBitNot);
    HTVM_Append(fullLangAllOperators_HELP, keyWordShiftLeft);
    HTVM_Append(fullLangAllOperators_HELP, keyWordShiftRight);
    HTVM_Append(fullLangAllOperators_HELP, keyWordShiftUnsignedRight);
    HTVM_Append(fullLangAllOperators_HELP, keyWordTernary1);
    HTVM_Append(fullLangAllOperators_HELP, keyWordTernary2);
    return fullLangAllOperators_HELP;
}
std::string extraFlexableFuncCallsHelp(std::string line) {
    std::vector<std::string> allFuncsDot;
    std::string temp = "";
    std::vector<std::string> items70 = LoopParseFunc(line, ".");
    for (size_t A_Index70 = 0; A_Index70 < items70.size() + 0; A_Index70++) {
        std::string A_LoopField70 = items70[A_Index70 - 0];
        if (A_Index70 == 0) {
            // the value name/other
            temp = A_LoopField70;
        } else {
            HTVM_Append(allFuncsDot, StrSplit(A_LoopField70, "(", 1) + "|" + StringTrimRight(StrSplit(A_LoopField70, "(", 2), 1));
        }
    }
    std::string out = "";
    int endParentesesToPut = 0;
    for (int A_Index71 = 0; A_Index71 < HTVM_Size(allFuncsDot) + 0; A_Index71++) {
        if (HTVM_Size(allFuncsDot) == A_Index71 + 1) {
            if (Trim(StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index71 - 1], "|", 2)) == "") {
                out += StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index71 - 1], "|", 1) + "(" + temp;
            } else {
                out += StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index71 - 1], "|", 1) + "(" + temp + ", " + Trim(StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index71 - 1], "|", 2));
            }
            for (int A_Index72 = 0; A_Index72 < endParentesesToPut + 1 + 0; A_Index72++) {
                out += ")";
            }
        } else {
            endParentesesToPut++;
            if (Trim(StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index71 - 1], "|", 2)) == "") {
                out += StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index71 - 1], "|", 1) + "(";
            } else {
                out += StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index71 - 1], "|", 1) + "(" + Trim(StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index71 - 1], "|", 2)) + ", ";
            }
        }
    }
    //print("=================================")
    return out;
}
std::string splitFunctionCalls(std::string line) {
    int doWeAddParentisiesLater = 0;
    line = Trim(line);
    for (int A_Index73 = 0; ; A_Index73++) {
        if (SubStr(line, 1, 1) == "(") {
            line = StringTrimRight(line, 1);
            line = StringTrimLeft(line, 1);
            doWeAddParentisiesLater++;
        } else {
            break;
        }
    }
    int doseBracketsExist = 0;
    std::vector<std::string> saveDoseBracketsExist;
    std::string saveDoseBracketsExistTEMP = "";
    int inBarkets = 0;
    int inBarketsNum = 0;
    std::string lineOut = "";
    if (InStr(line, "[")) {
        doseBracketsExist = 1;
        std::vector<std::string> items74 = LoopParseFunc(line);
        for (size_t A_Index74 = 0; A_Index74 < items74.size() + 0; A_Index74++) {
            std::string A_LoopField74 = items74[A_Index74 - 0];
            if (A_LoopField74 == "[") {
                inBarkets = 1;
                saveDoseBracketsExistTEMP += A_LoopField74;
            }
            if (A_LoopField74 == "]") {
                inBarkets = 0;
                saveDoseBracketsExistTEMP += A_LoopField74;
                HTVM_Append(saveDoseBracketsExist, saveDoseBracketsExistTEMP);
                saveDoseBracketsExistTEMP = "";
                lineOut += "brackests--rpelacse-brackets--HTVM-new-BUG--AA" + STR(inBarketsNum) + "AA";
                inBarketsNum++;
            }
            if (inBarkets == 1 && A_LoopField74 != "[" && A_LoopField74 != "]") {
                saveDoseBracketsExistTEMP += A_LoopField74;
            } else {
                lineOut += A_LoopField74;
            }
        }
        line = lineOut;
    }
    int doseFuncAtTheBegggging = 0;
    int doWeAddParentisiesLater2 = 0;
    int numRemoveFunc = 0;
    std::vector<std::string> FuncAtTheBegggging;
    std::string FuncAtTheBeggggingTEMP = "";
    if (RegExMatch(line, "^[a-zA-Z_][a-zA-Z0-9_]*\\(")) {
        doseFuncAtTheBegggging = 1;
        for (int A_Index75 = 0; ; A_Index75++) {
            if (RegExMatch(line, "^[a-zA-Z_][a-zA-Z0-9_]*\\(")) {
                FuncAtTheBeggggingTEMP = "";
                std::vector<std::string> items76 = LoopParseFunc(line);
                for (size_t A_Index76 = 0; A_Index76 < items76.size() + 0; A_Index76++) {
                    std::string A_LoopField76 = items76[A_Index76 - 0];
                    if (A_LoopField76 == "(") {
                        numRemoveFunc++;
                        FuncAtTheBeggggingTEMP += A_LoopField76;
                        HTVM_Append(FuncAtTheBegggging, FuncAtTheBeggggingTEMP);
                        FuncAtTheBeggggingTEMP = "";
                        break;
                    }
                    FuncAtTheBeggggingTEMP += A_LoopField76;
                    numRemoveFunc++;
                }
                line = StringTrimLeft(line, numRemoveFunc);
                numRemoveFunc = 0;
                line = StringTrimRight(line, 1);
                doWeAddParentisiesLater2++;
            } else {
                break;
            }
        }
    }
    std::vector<std::string> funcCalls;
    std::string temp = "";
    int parenthesesDepth = 0;
    int seenDot = 0;
    std::vector<std::string> items77 = LoopParseFunc(line);
    for (size_t A_Index77 = 0; A_Index77 < items77.size() + 0; A_Index77++) {
        std::string A_LoopField77 = items77[A_Index77 - 0];
        if (A_LoopField77 == ".") {
            seenDot = 1;
        }
        // Handle spaces
        if (A_LoopField77 == " ") {
            if (parenthesesDepth == 0) {
                if (temp != "") {
                    HTVM_Append(funcCalls, temp);
                    temp = "";
                }
            } else {
                temp += A_LoopField77;
            }
        }
        else if (A_LoopField77 == "(" && seenDot == 1) {
            parenthesesDepth++;
            temp += A_LoopField77;
        }
        else if (A_LoopField77 == ")" && seenDot == 1) {
            parenthesesDepth--;
            temp += A_LoopField77;
        } else {
            temp += A_LoopField77;
        }
    }
    if (temp != "") {
        HTVM_Append(funcCalls, temp);
    }
    std::string arrToStrSTR = "";
    for (int A_Index78 = 0; A_Index78 < HTVM_Size(funcCalls) + 0; A_Index78++) {
        if (RegExMatch(funcCalls[A_Index78], "\\.[a-zA-Z_][a-zA-Z0-9_]*")) {
            //print(funcCalls[A_Index])
            arrToStrSTR += extraFlexableFuncCallsHelp(funcCalls[A_Index78]) + " ";
        } else {
            arrToStrSTR += funcCalls[A_Index78] + " ";
        }
    }
    arrToStrSTR = StringTrimRight(arrToStrSTR, 1);
    if (doWeAddParentisiesLater != 0) {
        for (int A_Index79 = 0; A_Index79 < doWeAddParentisiesLater + 0; A_Index79++) {
            arrToStrSTR = "(" + arrToStrSTR + ")";
        }
    }
    if (doseBracketsExist == 1) {
        for (int A_Index80 = 0; A_Index80 < HTVM_Size(saveDoseBracketsExist) + 0; A_Index80++) {
            arrToStrSTR = StrReplace(arrToStrSTR, "brackests--rpelacse-brackets--HTVM-new-BUG--AA" + STR(A_Index80) + "AA", StringTrimLeft(StringTrimRight(saveDoseBracketsExist[A_Index80], 1), 1));
        }
    }
    if (doseFuncAtTheBegggging == 1) {
        for (int A_Index81 = 0; A_Index81 < HTVM_Size(FuncAtTheBegggging) + 0; A_Index81++) {
            arrToStrSTR = FuncAtTheBegggging[A_Index81] + arrToStrSTR;
        }
        for (int A_Index82 = 0; A_Index82 < doWeAddParentisiesLater2 + 0; A_Index82++) {
            arrToStrSTR = arrToStrSTR + ")";
        }
    }
    return arrToStrSTR;
}
std::string extraFlexableFuncCalls(std::string line, std::string availableFuncsInHTVMInHTVM) {
    availableFuncsInHTVMInHTVM = StringTrimRight(availableFuncsInHTVMInHTVM, 1);
    std::string out = line;
    std::vector<std::string> funcCalls;
    std::string temp = "";
    int parenthesesDepth = 0;
    int seenDot = 0;
    std::vector<std::string> items83 = LoopParseFunc(line);
    for (size_t A_Index83 = 0; A_Index83 < items83.size() + 0; A_Index83++) {
        std::string A_LoopField83 = items83[A_Index83 - 0];
        if (A_LoopField83 == "(") {
            seenDot = 1;
        }
        // Handle spaces
        if (A_LoopField83 == " ") {
            if (parenthesesDepth == 0) {
                if (temp != "") {
                    HTVM_Append(funcCalls, temp);
                    temp = "";
                }
            } else {
                temp += A_LoopField83;
            }
        }
        else if (A_LoopField83 == "(" && seenDot == 1) {
            parenthesesDepth++;
            temp += A_LoopField83;
        }
        else if (A_LoopField83 == ")" && seenDot == 1) {
            parenthesesDepth--;
            temp += A_LoopField83;
        } else {
            temp += A_LoopField83;
        }
    }
    if (temp != "") {
        HTVM_Append(funcCalls, temp);
    }
    int isFuncExist = 0;
    out = "";
    int i = 0;
    for (int A_Index84 = 0; A_Index84 < HTVM_Size(funcCalls) + 0; A_Index84++) {
        i = A_Index84;
        isFuncExist = 0;
        std::vector<std::string> items85 = LoopParseFunc(availableFuncsInHTVMInHTVM, "\n", "\r");
        for (size_t A_Index85 = 0; A_Index85 < items85.size() + 0; A_Index85++) {
            std::string A_LoopField85 = items85[A_Index85 - 0];
            if (RegExMatch(funcCalls[i], "\\b" + A_LoopField85 + "\\b")) {
                isFuncExist = 1;
            }
        }
        if (isFuncExist == 1) {
            out += splitFunctionCalls(funcCalls[A_Index84]) + " ";
        } else {
            out += funcCalls[A_Index84] + " ";
        }
    }
    out = StringTrimRight(out, 1);
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e
std::string expressionParserTranspiler(std::string expression) {
    std::string fixExpertionLineFuncOnlyTEXT_func = "";
    int fixExpertionLineFuncOnlyTEXT_numDelete = 0;
    if (fixExpertionLineFuncOnly == 1) {
        fixExpertionLineFuncOnlyTEXT_func = StrSplit(expression, "(", 1);
        fixExpertionLineFuncOnlyTEXT_numDelete = StrLen(fixExpertionLineFuncOnlyTEXT_func) + 1;
        expression = StringTrimLeft(expression, fixExpertionLineFuncOnlyTEXT_numDelete);
    }
    //go works but kinda need to use:
    //print(osp_osp_this_keyword_htvm_osp_this_htvm_keyword)
    // osp
    if (langToConvertTo != langFileExtension_2) {
        for (int A_Index86 = 0; A_Index86 < HTVM_Size(ospDic1) + 0; A_Index86++) {
            str00 = ospDic1[A_Index86];
            expression = StrReplace(expression, StrReplace(str00, "_", ".") + ".", str00 + "_");
        }
        for (int A_Index87 = 0; A_Index87 < HTVM_Size(ospDic2) + 0; A_Index87++) {
            str00 = ospDic2[A_Index87];
            expression = RegExReplace(expression, "\\b" + str00 + "\\b", "OSPHTVMOSP_" + StrReplace(str00, ".", "_"));
        }
    }
    // extra for array methods
    expression = arrayParserTranspiler(expression);
    if (langToConvertTo == langFileExtension_2) {
        expression = RegExReplace(expression, "\\b" + keyWordAwait + "\\b", keyWordAwait_2);
    }
    if (langToConvertTo == "js" || langToConvertTo == "ts") {
        expression = RegExReplace(expression, "\\b" + keyWordAwait + "\\b", "await ");
    }
    if (langToConvertTo != "js" && langToConvertTo != "ts" && langToConvertTo != langFileExtension_2) {
        expression = RegExReplace(expression, "\\b" + keyWordAwait + "\\b", "");
    }
    for (int A_Index88 = 0; A_Index88 < 29 + 0; A_Index88++) {
        if (InStr(expression, fullLangAllOperators_HELP[A_Index88])) {
            if (A_Index88 == 0 || A_Index88 == 1 || A_Index88 == 2) {
                expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index88] + "\\b", fullLangAllOperators[A_Index88]);
            } else {
                if (A_Index88 == 19) {
                    if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index88] + "\\b", "not");
                    } else {
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index88] + "\\b", "!");
                    }
                    if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
                        expression = RegExReplace(expression, "!([\\w]+)", "not $1");
                    }
                    expression = StrReplace(expression, " not= ", " != ");
                } else {
                    expression = StrReplace(expression, " " + fullLangAllOperators_HELP[A_Index88] + " ", " " + fullLangAllOperators[A_Index88] + " ");
                    if (A_Index88 == 28) {
                        if (langToConvertTo == "py") {
                            // Convert C-like ternary to Python ternary using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "$2 if $1 else $3");
                        }
                        if (langToConvertTo == "nim") {
                            // Convert C-like ternary to Nim ternary using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*)", "if $1: $2 else: $3");
                        }
                        if (langToConvertTo == "lua") {
                            // Convert C-like ternary to Lua ternary-like expression using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "$1 and $2 or $3");
                        }
                        if (langToConvertTo == "kt") {
                            // Convert C-like ternary to Kotlin ternary-like expression using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "if $1 $2 else $3");
                        }
                    }
                }
            }
        }
    }
    if (langToConvertTo == "ahk") {
        if (InStr(expression, keyWordAIndex)) {
            expression = RegExReplace(expression, "\\b" + keyWordAIndex + "\\b", "A_Index");
        }
        if (InStr(expression, keyWordALoopField)) {
            expression = RegExReplace(expression, "\\b" + keyWordALoopField + "\\b", "A_LoopField");
        }
    }
    if (langToConvertTo == "rb") {
        expression = RegExReplace(expression, keyWordAIndexOriginal + "(\\d*)", StrLower(keyWordAIndexOriginal) + "$1");
        expression = RegExReplace(expression, keyWordALoopFieldOriginal + "(\\d*)", StrLower(keyWordALoopFieldOriginal) + "$1");
    }
    if (langToConvertTo == langFileExtension_2) {
        if (InStr(expression, keyWordAIndex)) {
            expression = RegExReplace(expression, "\\b" + keyWordAIndex + "\\b", keyWordAIndex_2);
        }
        if (InStr(expression, keyWordALoopField)) {
            expression = RegExReplace(expression, "\\b" + keyWordALoopField + "\\b", keyWordALoopField_2);
        }
    }
    if (langToConvertTo != langFileExtension_2 && langToConvertTo != "ahk") {
        if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
            expression = StrReplace(expression, ") and (", " and ");
            expression = StrReplace(expression, ") or (", " or ");
        } else {
            expression = StrReplace(expression, ") && (", " && ");
            expression = StrReplace(expression, ") || (", " || ");
        }
    }
    if (langToConvertTo == langFileExtension_2) {
        expression = RegExReplace(expression, "\\b" + keyWordThis + "\\b", keyWordThis_2);
    } else {
        expression = RegExReplace(expression, "\\b" + keyWordThis + "\\b", "osp_osp_this_keyword_htvm_osp_this_htvm_keyword");
    }
    if (RegExMatch(expression, "\\.[a-zA-Z_][a-zA-Z0-9_]*") && langToConvertTo != langFileExtension_2) {
        expression = extraFlexableFuncCalls(expression, availableFuncsInHTVMInHTVM);
    }
    if (langToConvertTo == "cpp") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".what()");
    }
    if (langToConvertTo == "js") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    if (langToConvertTo == "cs") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".Message");
    }
    if (langToConvertTo == "java") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".getMessage()");
    }
    if (langToConvertTo == "kt") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    if (langToConvertTo == "rb") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    if (langToConvertTo == "nim") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".msg");
    }
    if (langToConvertTo == "swift") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".localizedDescription");
    }
    if (langToConvertTo == "ts") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    if (langToConvertTo == "groovy") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    // fix java arrName[A_Index] not existing
    if (langToConvertTo == "java") {
        expression = RegExReplace(expression, "(\\b[A-Za-z_]\\w*)\\s*\\[", "$1.get(");
        expression = StrReplace(expression, "]", ")");
    }
    if (langToConvertTo == "swift") {
        expression = StrReplace(expression, Chr(39), Chr(34));
    }
    if (langToConvertTo == "ahk") {
        expression = StrReplace(expression, Chr(39), Chr(34));
    }
    if (fixExpertionLineFuncOnly == 1) {
        expression = fixExpertionLineFuncOnlyTEXT_func + "(" + expression;
    }
    if (langToConvertTo == "nim") {
        expression = StrReplace(expression, "HTVM--Fix-Nim-TheConcat-NOT--Working--AA", "&");
    }
    return expression;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string FixRubyGlobalVars(std::string line) {
    std::vector<std::string> htCodeFixRubyGlobalVars;
    std::vector<std::string> items89 = LoopParseFunc(line, "\n", "\r");
    for (size_t A_Index89 = 0; A_Index89 < items89.size() + 0; A_Index89++) {
        std::string A_LoopField89 = items89[A_Index89 - 0];
        if (RegExMatch(A_LoopField89, "^[a-zA-Z_][a-zA-Z0-9_]* = .*")) {
            HTVM_Append(htCodeFixRubyGlobalVars, Trim(StrSplit(A_LoopField89, " = ", 1)));
            HTVM_Append(htCodeFixRubyGlobalVars_EXPOSED, Trim(StrSplit(A_LoopField89, " = ", 1)));
        }
    }
    for (int A_Index90 = 0; A_Index90 < HTVM_Size(htCodeFixRubyGlobalVars) + 0; A_Index90++) {
        line = RegExReplace(line, "\\b" + htCodeFixRubyGlobalVars[A_Index90] + "\\b", "$" + htCodeFixRubyGlobalVars[A_Index90]);
    }
    return line;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string propHELP(std::string line, std::string lineOspHelpLine) {
    if (lineOspHelpLine == "no-no") {
        lineOspHelpLine = "";
    }
    std::string htCodeOUTOUT = "";
    std::string ALoopField = "";
    std::vector<std::string> items91 = LoopParseFunc(line, "\n", "\r");
    for (size_t A_Index91 = 0; A_Index91 < items91.size() + 0; A_Index91++) {
        std::string A_LoopField91 = items91[A_Index91 - 0];
        if (InStr(A_LoopField91, " " + keyWordAssign + " ") || InStr(A_LoopField91, " " + keyWordAssignAdd + " ") || InStr(A_LoopField91, " " + keyWordAssignConcat + " ") || InStr(A_LoopField91, " " + keyWordAssignSub + " ") || InStr(A_LoopField91, " " + keyWordAssignMul + " ") || InStr(A_LoopField91, " " + keyWordAssignDiv + " ") || InStr(A_LoopField91, " " + keyWordAssignMod + " ") || InStr(A_LoopField91, " " + keyWordAssignShiftLeft + " ") || InStr(A_LoopField91, " " + keyWordAssignShiftRight + " ") || InStr(A_LoopField91, " " + keyWordLogicalAssignShiftRight + " ") || InStr(A_LoopField91, " " + keyWordAssignBitAnd + " ") || InStr(A_LoopField91, " " + keyWordAssignBitOr + " ") || InStr(A_LoopField91, " " + keyWordAssignBitXor + " ") && lineDone == 0) {
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
            //keyWordAssign
            //keyWordAssignAdd
            //keyWordAssignConcat
            //keyWordAssignSub
            //keyWordAssignMul
            //keyWordAssignDiv
            //keyWordAssignMod
            //keyWordAssignShiftLeft
            //keyWordAssignShiftRight
            //keyWordLogicalAssignShiftRight
            //keyWordAssignBitAnd
            //keyWordAssignBitOr
            //keyWordAssignBitXor
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //allVarsSoWeDontReDecVars
            //allVarsSoWeDontReDecVars_FIX_uint8
            //allVarsSoWeDontReDecVars_FIX_uint16
            //allVarsSoWeDontReDecVars_FIX_uint32
            //allVarsSoWeDontReDecVars_FIX_uint64
            //allVarsSoWeDontReDecVars_FIX_int64
            //allVarsSoWeDontReDecVars_FIX_float
            if (InStr(A_LoopField91, " " + keyWordAssign + " ")) {
                str1 = StrSplit(A_LoopField91, " " + keyWordAssign + " ", 1);
                str6 = StrSplit(A_LoopField91, " " + keyWordAssign + " ", 2);
                str10 = keyWordAssign;
                str11 = keyWordAssign_2;
                if (langToConvertTo == "ahk") {
                    str12 = ":=";
                } else {
                    str12 = "=";
                }
            }
            else if (InStr(A_LoopField91, " " + keyWordAssignAdd + " ")) {
                str1 = StrSplit(A_LoopField91, " " + keyWordAssignAdd + " ", 1);
                str6 = StrSplit(A_LoopField91, " " + keyWordAssignAdd + " ", 2);
                str10 = keyWordAssignAdd;
                str11 = keyWordAssignAdd_2;
                str12 = "+=";
            }
            else if (InStr(A_LoopField91, " " + keyWordAssignConcat + " ")) {
                str1 = StrSplit(A_LoopField91, " " + keyWordAssignConcat + " ", 1);
                str6 = StrSplit(A_LoopField91, " " + keyWordAssignConcat + " ", 2);
                str10 = keyWordAssignConcat;
                str11 = keyWordAssignConcat_2;
                if (langToConvertTo == "ahk") {
                    str12 = ".=";
                } else {
                    str12 = "+=";
                }
            }
            else if (InStr(A_LoopField91, " " + keyWordAssignSub + " ")) {
                str1 = StrSplit(A_LoopField91, " " + keyWordAssignSub + " ", 1);
                str6 = StrSplit(A_LoopField91, " " + keyWordAssignSub + " ", 2);
                str10 = keyWordAssignSub;
                str11 = keyWordAssignSub_2;
                str12 = "-=";
            }
            else if (InStr(A_LoopField91, " " + keyWordAssignMul + " ")) {
                str1 = StrSplit(A_LoopField91, " " + keyWordAssignMul + " ", 1);
                str6 = StrSplit(A_LoopField91, " " + keyWordAssignMul + " ", 2);
                str10 = keyWordAssignMul;
                str11 = keyWordAssignMul_2;
                str12 = "*=";
            }
            else if (InStr(A_LoopField91, " " + keyWordAssignDiv + " ")) {
                str1 = StrSplit(A_LoopField91, " " + keyWordAssignDiv + " ", 1);
                str6 = StrSplit(A_LoopField91, " " + keyWordAssignDiv + " ", 2);
                str10 = keyWordAssignDiv;
                str11 = keyWordAssignDiv_2;
                str12 = "/=";
            }
            else if (InStr(A_LoopField91, " " + keyWordAssignMod + " ")) {
                str1 = StrSplit(A_LoopField91, " " + keyWordAssignMod + " ", 1);
                str6 = StrSplit(A_LoopField91, " " + keyWordAssignMod + " ", 2);
                str10 = keyWordAssignMod;
                str11 = keyWordAssignMod_2;
                str12 = "%=";
            }
            else if (InStr(A_LoopField91, " " + keyWordAssignShiftLeft + " ")) {
                str1 = StrSplit(A_LoopField91, " " + keyWordAssignShiftLeft + " ", 1);
                str6 = StrSplit(A_LoopField91, " " + keyWordAssignShiftLeft + " ", 2);
                str10 = keyWordAssignShiftLeft;
                str11 = keyWordAssignShiftLeft_2;
                str12 = "<<=";
            }
            else if (InStr(A_LoopField91, " " + keyWordAssignShiftRight + " ")) {
                str1 = StrSplit(A_LoopField91, " " + keyWordAssignShiftRight + " ", 1);
                str6 = StrSplit(A_LoopField91, " " + keyWordAssignShiftRight + " ", 2);
                str10 = keyWordAssignShiftRight;
                str11 = keyWordAssignShiftRight_2;
                str12 = ">>=";
            }
            else if (InStr(A_LoopField91, " " + keyWordLogicalAssignShiftRight + " ")) {
                str1 = StrSplit(A_LoopField91, " " + keyWordLogicalAssignShiftRight + " ", 1);
                str6 = StrSplit(A_LoopField91, " " + keyWordLogicalAssignShiftRight + " ", 2);
                str10 = keyWordLogicalAssignShiftRight;
                str11 = keyWordLogicalAssignShiftRight_2;
                str12 = ">>>=";
            }
            else if (InStr(A_LoopField91, " " + keyWordAssignBitAnd + " ")) {
                str1 = StrSplit(A_LoopField91, " " + keyWordAssignBitAnd + " ", 1);
                str6 = StrSplit(A_LoopField91, " " + keyWordAssignBitAnd + " ", 2);
                str10 = keyWordAssignBitAnd;
                str11 = keyWordAssignBitAnd_2;
                str12 = "&=";
            }
            else if (InStr(A_LoopField91, " " + keyWordAssignBitOr + " ")) {
                str1 = StrSplit(A_LoopField91, " " + keyWordAssignBitOr + " ", 1);
                str6 = StrSplit(A_LoopField91, " " + keyWordAssignBitOr + " ", 2);
                str10 = keyWordAssignBitOr;
                str11 = keyWordAssignBitOr_2;
                str12 = "|=";
            }
            else if (InStr(A_LoopField91, " " + keyWordAssignBitXor + " ")) {
                str1 = StrSplit(A_LoopField91, " " + keyWordAssignBitXor + " ", 1);
                str6 = StrSplit(A_LoopField91, " " + keyWordAssignBitXor + " ", 2);
                str10 = keyWordAssignBitXor;
                str11 = keyWordAssignBitXor_2;
                str12 = "^=";
            }
            str6 = Trim(expressionParserTranspiler(Trim(str6)));
            if (SubStrLastChars(str6, 1) == ";") {
                str6 = StringTrimRight(str6, 1);
            }
            str1 = Trim(str1);
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            ALoopField = str1;
            if (InStr(ALoopField, " ") == false || SubStrLastChars(ALoopField, 1) == "]") {
                lineDone = 1;
                str1 = lineOspHelpLine + Trim(str1);
                str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str1);
                if (InStr(saveAllArrayVarNamesSoWeCanDoAfix, "|" + Trim(str1) + "|")) {
                    str6 = Trim(str6);
                    str6 = StringTrimRight(str6, 1);
                    str6 = StringTrimLeft(str6, 1);
                    if (langToConvertTo == "cpp") {
                        str6 = "{" + str6 + "}";
                    }
                    if (langToConvertTo == "py") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "js") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "go") {
                        str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                    }
                    if (langToConvertTo == "lua") {
                        str6 = "{" + str6 + "}";
                    }
                    if (langToConvertTo == "cs") {
                        str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                    }
                    if (langToConvertTo == "java") {
                        str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                    }
                    if (langToConvertTo == "kt") {
                        str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                    }
                    if (langToConvertTo == "rb") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "nim") {
                        str6 = "@[" + str6 + "]";
                    }
                    if (langToConvertTo == "ahk") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "swift") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "dart") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "ts") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "groovy") {
                        str6 = "[" + str6 + "]";
                    }
                }
                if (Trim(str6) == "[]" || Trim(str6) == "{}") {
                    if (useCurlyBracesSyntaxForArrayDef_2 == "on" && langToConvertTo == langFileExtension_2) {
                        str6 = "{}";
                    } else {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "cpp") {
                        str6 = "{}";
                    }
                    if (langToConvertTo == "py") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "js") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "go") {
                        str6 = Trim(str1) + "[:0]";
                    }
                    if (langToConvertTo == "lua") {
                        str6 = "{}";
                    }
                    if (langToConvertTo == "cs") {
                        str6 = "ResetList(" + Trim(str1) + ")";
                    }
                    if (langToConvertTo == "java") {
                        str6 = "new ArrayList<>()";
                    }
                    if (langToConvertTo == "kt") {
                        str6 = "ArrayList()";
                    }
                    if (langToConvertTo == "rb") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "nim") {
                        str6 = "@[]";
                    }
                    if (langToConvertTo == "ahk") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "swift") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "dart") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "ts") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "groovy") {
                        str6 = "[]";
                    }
                }
                //;;;;;;;;;;;;;;;;;
                //;;;;;;;;;;;;;;;;;
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        str4 = str1 + " " + str11 + " " + str6 + ";";
                    } else {
                        str4 = str1 + " " + str11 + " " + str6;
                    }
                }
                if (langToConvertTo == "cpp") {
                    str4 = str1 + " " + str12 + " " + str6 + ";";
                }
                if (langToConvertTo == "py") {
                    str4 = str1 + " " + str12 + " " + str6;
                }
                if (langToConvertTo == "js") {
                    str4 = str1 + " " + str12 + " " + str6 + ";";
                }
                if (langToConvertTo == "go") {
                    str4 = str1 + " " + str12 + " " + str6;
                }
                if (langToConvertTo == "lua") {
                    str4 = str1 + " " + str12 + " " + str6;
                }
                if (langToConvertTo == "cs") {
                    str4 = str1 + " " + str12 + " " + str6 + ";";
                }
                if (langToConvertTo == "java") {
                    if (Trim(str6) == "[]" || Trim(str6) == "{}") {
                        str4 = str1 + " " + str12 + " " + str6 + ";";
                    } else {
                        if (InStr(str1, "[")) {
                            // Convert arr[something] to arr.set(something, value);
                            str1 = RegExReplace(str1, "(\\b[A-Za-z_]\\w*)\\s*\\[(.*?)\\]", "$1.set($2, ");
                            str4 = str1 + str6 + ");";
                        } else {
                            str4 = str1 + " " + str12 + " " + str6 + ";";
                        }
                    }
                }
                if (langToConvertTo == "kt") {
                    str4 = str1 + " " + str12 + " " + str6;
                }
                if (langToConvertTo == "rb") {
                    str4 = str1 + " " + str12 + " " + str6;
                }
                if (langToConvertTo == "nim") {
                    str4 = str1 + " " + str12 + " " + str6;
                }
                if (langToConvertTo == "ahk") {
                    str4 = str1 + " " + str12 + " " + str6;
                }
                if (langToConvertTo == "swift") {
                    str4 = str1 + " " + str12 + " " + str6;
                }
                if (langToConvertTo == "dart") {
                    str4 = str1 + " " + str12 + " " + str6 + ";";
                }
                if (langToConvertTo == "ts") {
                    str4 = str1 + " " + str12 + " " + str6 + ";";
                }
                if (langToConvertTo == "groovy") {
                    str4 = str1 + " " + str12 + " " + str6;
                }
                htCodeOUTOUT += str4 + Chr(10);
            }
            else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordConst)) == keyWordConst && lineDone == 0) {
                lineDone = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordConst)));
                    std::vector<std::string> items92 = LoopParseFunc(str1, " ");
                    for (size_t A_Index92 = 0; A_Index92 < items92.size() + 0; A_Index92++) {
                        std::string A_LoopField92 = items92[A_Index92 - 0];
                        str2 = A_LoopField92;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = lineOspHelpLine + Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordConst)));
                    str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                }
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    int5 = 0;
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            if (int5 != 0) {
                                str6 = "{" + str6 + "}";
                            }
                        } else {
                            if (int5 != 0) {
                                str6 = "[" + str6 + "]";
                            }
                        }
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        } else {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "py") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6 + "";
                        }
                    }
                    if (langToConvertTo == "js") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        if (int5 != 0) {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        } else {
                            str4 = str2 + " := " + str3 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "lua") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "kt") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                        } else {
                            str4 = "var " + str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "rb") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "nim") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + str3 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        if (int5 != 0) {
                            str4 = str2 + " := [" + str6 + "]";
                        } else {
                            str4 = str2 + " := " + str6;
                        }
                    }
                    if (langToConvertTo == "swift") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "dart") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        } else {
                            str4 = str3 + " " + str2 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "ts") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                } else {
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    str3 = getFuncTypeConvert(str3);
                    str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = "const " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "js") {
                        str4 = "const " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "go") {
                        str4 = "const " + str2 + " " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "cs") {
                        str4 = "const " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = "final " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        } else {
                            str4 = "static final " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "val " + str2 + ": " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "const " + str2 + ": " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "let " + str2 + ": " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = "final " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "const " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = "final " + str2 + " " + str12 + " " + str6;
                    }
                    //;;;
                }
                htCodeOUTOUT += str4 + Chr(10);
            }
            else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordVar)) == keyWordVar && lineDone == 0) {
                lineDone = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordVar)));
                    std::vector<std::string> items93 = LoopParseFunc(str1, " ");
                    for (size_t A_Index93 = 0; A_Index93 < items93.size() + 0; A_Index93++) {
                        std::string A_LoopField93 = items93[A_Index93 - 0];
                        str2 = A_LoopField93;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = lineOspHelpLine + Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordVar)));
                    str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                }
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    int5 = 0;
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            if (int5 != 0) {
                                str6 = "{" + str6 + "}";
                            }
                        } else {
                            if (int5 != 0) {
                                str6 = "[" + str6 + "]";
                            }
                        }
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordVar_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = keyWordVar_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordVar_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = keyWordVar_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        } else {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "py") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6 + "";
                        }
                    }
                    if (langToConvertTo == "js") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        if (int5 != 0) {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        } else {
                            str4 = str2 + " := " + str3 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "lua") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "kt") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                        } else {
                            str4 = "var " + str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "rb") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "nim") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + str3 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        if (int5 != 0) {
                            str4 = str2 + " := [" + str6 + "]";
                        } else {
                            str4 = str2 + " := " + str6;
                        }
                    }
                    if (langToConvertTo == "swift") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "dart") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        } else {
                            str4 = str3 + " " + str2 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "ts") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                } else {
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    str3 = getFuncTypeConvert(str3);
                    str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordVar_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = keyWordVar_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordVar_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = keyWordVar_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "js") {
                        str4 = "var " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + "? " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    //;;;
                }
                htCodeOUTOUT += str4 + Chr(10);
            }
            else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordLet)) == keyWordLet && lineDone == 0) {
                lineDone = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordLet)));
                    std::vector<std::string> items94 = LoopParseFunc(str1, " ");
                    for (size_t A_Index94 = 0; A_Index94 < items94.size() + 0; A_Index94++) {
                        std::string A_LoopField94 = items94[A_Index94 - 0];
                        str2 = A_LoopField94;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = lineOspHelpLine + Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordLet)));
                    str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                }
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    int5 = 0;
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            if (int5 != 0) {
                                str6 = "{" + str6 + "}";
                            }
                        } else {
                            if (int5 != 0) {
                                str6 = "[" + str6 + "]";
                            }
                        }
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordLet_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = keyWordLet_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordLet_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = keyWordLet_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        } else {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "py") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6 + "";
                        }
                    }
                    if (langToConvertTo == "js") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        if (int5 != 0) {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        } else {
                            str4 = str2 + " := " + str3 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "lua") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "kt") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                        } else {
                            str4 = "var " + str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "rb") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "nim") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + str3 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        if (int5 != 0) {
                            str4 = str2 + " := [" + str6 + "]";
                        } else {
                            str4 = str2 + " := " + str6;
                        }
                    }
                    if (langToConvertTo == "swift") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "dart") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        } else {
                            str4 = str3 + " " + str2 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "ts") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                } else {
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    str3 = getFuncTypeConvert(str3);
                    str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordLet_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = keyWordLet_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordLet_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = keyWordLet_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "js") {
                        str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = "local " + str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "let " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    //;;;
                }
                htCodeOUTOUT += str4 + Chr(10);
            }
            else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordDouble + " ")) == keyWordDouble + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordChar + " ")) == keyWordChar + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint8 + " ")) == keyWordUint8 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint16 + " ")) == keyWordUint16 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint32 + " ")) == keyWordUint32 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint64 + " ")) == keyWordUint64 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT + " ")) == keyWordINT + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordSTR + " ")) == keyWordSTR + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordBOOL + " ")) == keyWordBOOL + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordFLOAT + " ")) == keyWordFLOAT + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT8 + " ")) == keyWordINT8 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT16 + " ")) == keyWordINT16 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT32 + " ")) == keyWordINT32 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT64 + " ")) == keyWordINT64 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayDefinition + " ")) == keyWordArrayDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfIntegersDefinition + " ")) == keyWordArrayOfIntegersDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfStringsDefinition + " ")) == keyWordArrayOfStringsDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfFloatingPointNumbersDefinition + " ")) == keyWordArrayOfFloatingPointNumbersDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfBooleansDefinition + " ")) == keyWordArrayOfBooleansDefinition + " " && usePrefixTypeForTypeDefinition == "on" && lineDone == 0) {
                lineDone = 1;
                std::vector<std::string> items95 = LoopParseFunc(str1, " ");
                for (size_t A_Index95 = 0; A_Index95 < items95.size() + 0; A_Index95++) {
                    std::string A_LoopField95 = items95[A_Index95 - 0];
                    str2 = A_LoopField95;
                }
                str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                str2 = lineOspHelpLine + Trim(str2);
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    int5 = 0;
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            if (int5 != 0) {
                                str6 = "{" + str6 + "}";
                            }
                        } else {
                            if (int5 != 0) {
                                str6 = "[" + str6 + "]";
                            }
                        }
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = str2 + ": " + str3 + " " + str11 + " " + str6;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        } else {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "py") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6 + "";
                        }
                    }
                    if (langToConvertTo == "js") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        if (int5 != 0) {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        } else {
                            str4 = str2 + " := " + str3 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "lua") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "kt") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                        } else {
                            str4 = "var " + str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "rb") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "nim") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + str3 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        if (int5 != 0) {
                            str4 = str2 + " := [" + str6 + "]";
                        } else {
                            str4 = str2 + " := " + str6;
                        }
                    }
                    if (langToConvertTo == "swift") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "dart") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        } else {
                            str4 = str3 + " " + str2 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "ts") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                } else {
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    str3 = getFuncTypeConvert(str3);
                    str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = str2 + ": " + str3 + " " + str11 + " " + str6;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "js") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + " " + str12 + " " + str6 + ";";
                        } else {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2  + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    //;;;
                }
                htCodeOUTOUT += str4 + Chr(10);
            }
            else if (RegExMatch(Trim(str1), "^[a-zA-Z_][a-zA-Z_0-9]*:\\s?.*$") && usePostfixTypeForTypeDefinition == "on" && lineDone == 0) {
                lineDone = 1;
                str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
                str3 = Trim(StrSplit(str1, ":", 2));
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    int5 = 0;
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            if (int5 != 0) {
                                str6 = "{" + str6 + "}";
                            }
                        } else {
                            if (int5 != 0) {
                                str6 = "[" + str6 + "]";
                            }
                        }
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = str2 + ": " + str3 + " " + str11 + " " + str6;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        } else {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "py") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6 + "";
                        }
                    }
                    if (langToConvertTo == "js") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        if (int5 != 0) {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        } else {
                            str4 = str2 + " := " + str3 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "lua") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "kt") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                        } else {
                            str4 = "var " + str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "rb") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "nim") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + str3 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        if (int5 != 0) {
                            str4 = str2 + " := [" + str6 + "]";
                        } else {
                            str4 = str2 + " := " + str6;
                        }
                    }
                    if (langToConvertTo == "swift") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "dart") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        } else {
                            str4 = str3 + " " + str2 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "ts") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                } else {
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    str3 = getFuncTypeConvert(str3);
                    str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = str2 + ": " + str3 + " " + str11 + " " + str6;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "js") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + " " + str12 + " " + str6 + ";";
                        } else {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " " + str12 + " " + str6 + ";";
                    }
                    //;;;
                }
                htCodeOUTOUT += str4 + Chr(10);
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
        }
        else if (SubStr(Trim(A_LoopField91), 1, StrLen(keyWordVar)) == keyWordVar && lineDone == 0) {
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
            if (usePostfixTypeForTypeDefinition == "off") {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(Trim(A_LoopField91), StrLen(keyWordVar)));
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                std::vector<std::string> items96 = LoopParseFunc(str1, " ");
                for (size_t A_Index96 = 0; A_Index96 < items96.size() + 0; A_Index96++) {
                    std::string A_LoopField96 = items96[A_Index96 - 0];
                    str2 = A_LoopField96;
                }
                str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                str2 = lineOspHelpLine + Trim(str2);
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
            } else {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(Trim(A_LoopField91), StrLen(keyWordVar)));
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
                str3 = Trim(StrSplit(str1, ":", 2));
                // str2 = var name
                // str3 = type
            }
            if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                str3 = getFuncTypeConvert(str3);
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = keyWordVar_2 + " " + str3 + " " + str2 + ";";
                        } else {
                            str4 = keyWordVar_2 + " " + str2 + ": " + str3 + ";";
                        }
                    } else {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = keyWordVar_2 + " " + str3 + " " + str2;
                        } else {
                            str4 = keyWordVar_2 + " " + str2 + ": " + str3;
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    str4 = str3 + " " + str2 + ";";
                }
                if (langToConvertTo == "py") {
                    str4 = str2 + " = []";
                }
                if (langToConvertTo == "js") {
                    str4 = "let " + str2 + " = [];";
                }
                if (langToConvertTo == "go") {
                    str4 = "var " + str2 + " " + str3;
                }
                if (langToConvertTo == "lua") {
                    str4 = str2 + " = {}";
                }
                if (langToConvertTo == "cs") {
                    if (csMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = new " + str3 + "();";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = new " + str3 + "();";
                    }
                }
                if (langToConvertTo == "java") {
                    if (javaMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = new ArrayList<>();";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = new ArrayList<>();";
                    }
                }
                if (langToConvertTo == "kt") {
                    str4 = "var " + str2 + " = " + str3 + "()";
                }
                if (langToConvertTo == "rb") {
                    str4 = str2 + " = []";
                }
                if (langToConvertTo == "nim") {
                    str4 = "var " + str2 + ": " + str3 + " = @[]";
                }
                if (langToConvertTo == "ahk") {
                    str4 = str2 + " := []";
                }
                if (langToConvertTo == "swift") {
                    str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = []";
                }
                if (langToConvertTo == "dart") {
                    str4 = str3 + " " + str2 + " = [];";
                }
                if (langToConvertTo == "ts") {
                    str4 = "let " + str2 + ": " + str3 + " = [];";
                }
                if (langToConvertTo == "groovy") {
                    str4 = str2 + " = []";
                }
            } else {
                //;;;
                //;;;
                //;;;
                //;;;
                //;;;
                str3 = getFuncTypeConvert(str3);
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2 + ";";
                        } else {
                            str4 = str2 + ": " + str3 + ";";
                        }
                    } else {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2;
                        } else {
                            str4 = str2 + ": " + str3;
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (str3 == "double") {
                        str5 = "0.00";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "uint8_t") {
                        str5 = "0";
                    }
                    if (str3 == "uint16_t") {
                        str5 = "0";
                    }
                    if (str3 == "uint32_t") {
                        str5 = "0";
                    }
                    if (str3 == "uint64_t") {
                        str5 = "0ULL";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "std::string") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "bool") {
                        str5 = "false";
                    }
                    if (str3 == "float") {
                        str5 = "0.00f";
                    }
                    if (str3 == "int8_t") {
                        str5 = "0";
                    }
                    if (str3 == "int16_t") {
                        str5 = "0";
                    }
                    if (str3 == "int32_t") {
                        str5 = "0";
                    }
                    if (str3 == "int64_t") {
                        str5 = "0LL";
                    }
                    str4 = str3 + " " + str2 + " = " + str5 + ";";
                }
                if (langToConvertTo == "py") {
                    str4 = str2 + " = None";
                }
                if (langToConvertTo == "js") {
                    str4 = "var " + str2 + ";";
                }
                if (langToConvertTo == "go") {
                    str4 = "var " + str2 + " " +  str3;
                }
                if (langToConvertTo == "lua") {
                    str4 = str2 + " = nil";
                }
                if (langToConvertTo == "cs") {
                    if (str3 == "double") {
                        str5 = "0.0";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "byte") {
                        str5 = "0";
                    }
                    if (str3 == "ushort") {
                        str5 = "0";
                    }
                    if (str3 == "uint") {
                        str5 = "0";
                    }
                    if (str3 == "ulong") {
                        str5 = "0UL";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "string") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "bool") {
                        str5 = "false";
                    }
                    if (str3 == "float") {
                        str5 = "0.0f";
                    }
                    if (str3 == "sbyte") {
                        str5 = "0";
                    }
                    if (str3 == "short") {
                        str5 = "0";
                    }
                    if (str3 == "long") {
                        str5 = "0L";
                    }
                    if (csMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                    }
                }
                if (langToConvertTo == "java") {
                    if (str3 == "double") {
                        str5 = "0.0";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "byte") {
                        str5 = "(byte) 0";
                    }
                    if (str3 == "short") {
                        str5 = "(short) 0";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "long") {
                        str5 = "0L";
                    }
                    if (str3 == "String") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "boolean") {
                        str5 = "false";
                    }
                    if (str3 == "float") {
                        str5 = "0.0f";
                    }
                    if (str3 == "int8") {
                        str5 = "0";
                    }
                    if (str3 == "int16") {
                        str5 = "0";
                    }
                    if (str3 == "int32") {
                        str5 = "0";
                    }
                    if (str3 == "int64") {
                        str5 = "0L";
                    }
                    if (javaMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                    }
                }
                if (langToConvertTo == "kt") {
                    str4 = "var " + str2 + ": " + str3 + "? = null";
                }
                if (langToConvertTo == "rb") {
                    str4 = str2 + " = nil";
                }
                if (langToConvertTo == "nim") {
                    if (str3 == "float") {
                        str5 = "0.0";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "uint8") {
                        str5 = "0";
                    }
                    if (str3 == "uint16") {
                        str5 = "0";
                    }
                    if (str3 == "uint32") {
                        str5 = "0";
                    }
                    if (str3 == "uint64") {
                        str5 = "0";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "string") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "bool") {
                        str5 = "false";
                    }
                    if (str3 == "int8") {
                        str5 = "0";
                    }
                    if (str3 == "int16") {
                        str5 = "0";
                    }
                    if (str3 == "int32") {
                        str5 = "0";
                    }
                    if (str3 == "int64") {
                        str5 = "0";
                    }
                    str4 = "var " + str2 + ": " + str3 + " = " + str5;
                }
                if (langToConvertTo == "ahk") {
                    str4 = str2 + " := " + Chr(34) + Chr(34);
                }
                if (langToConvertTo == "swift") {
                    if (str3 == "Double") {
                        str5 = "0.00";
                    }
                    if (str3 == "Character") {
                        str5 = Chr(34) + "a" + Chr(34);
                    }
                    if (str3 == "UInt8") {
                        str5 = "0";
                    }
                    if (str3 == "UInt16") {
                        str5 = "0";
                    }
                    if (str3 == "UInt32") {
                        str5 = "0";
                    }
                    if (str3 == "UInt64") {
                        str5 = "0";
                    }
                    if (str3 == "Int") {
                        str5 = "0";
                    }
                    if (str3 == "String") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "Bool") {
                        str5 = "false";
                    }
                    if (str3 == "Float") {
                        str5 = "0.00";
                    }
                    if (str3 == "Int8") {
                        str5 = "0";
                    }
                    if (str3 == "Int16") {
                        str5 = "0";
                    }
                    if (str3 == "Int32") {
                        str5 = "0";
                    }
                    if (str3 == "Int64") {
                        str5 = "0";
                    }
                    str4 = "var " + str2 + ": " + str3 + " = " + str5;
                }
                if (langToConvertTo == "dart") {
                    str4 = str3 + "? " + str2 + ";";
                }
                if (langToConvertTo == "ts") {
                    str4 = "var " + str2 + ": " + str3 + ";";
                }
                if (langToConvertTo == "groovy") {
                    str4 = str2 + " = null";
                }
                //;;;
            }
            htCodeOUTOUT += str4 + Chr(10);
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
        }
        else if (SubStr(Trim(A_LoopField91), 1, StrLen(keyWordLet)) == keyWordLet && lineDone == 0) {
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
            if (usePostfixTypeForTypeDefinition == "off") {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(Trim(A_LoopField91), StrLen(keyWordLet)));
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                std::vector<std::string> items97 = LoopParseFunc(str1, " ");
                for (size_t A_Index97 = 0; A_Index97 < items97.size() + 0; A_Index97++) {
                    std::string A_LoopField97 = items97[A_Index97 - 0];
                    str2 = A_LoopField97;
                }
                str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                str2 = lineOspHelpLine + Trim(str2);
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
            } else {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(Trim(A_LoopField91), StrLen(keyWordLet)));
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
                str3 = Trim(StrSplit(str1, ":", 2));
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
            }
            if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                str3 = getFuncTypeConvert(str3);
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = keyWordLet_2 + " " + str3 + " " + str2 + ";";
                        } else {
                            str4 = keyWordLet_2 + " " + str2 + ": " + str3 + ";";
                        }
                    } else {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = keyWordLet_2 + " " + str3 + " " + str2;
                        } else {
                            str4 = keyWordLet_2 + " " + str2 + ": " + str3;
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    str4 = str3 + " " + str2 + ";";
                }
                if (langToConvertTo == "py") {
                    str4 = str2 + " = []";
                }
                if (langToConvertTo == "js") {
                    str4 = "let " + str2 + " = [];";
                }
                if (langToConvertTo == "go") {
                    str4 = "var " + str2 + " " + str3;
                }
                if (langToConvertTo == "lua") {
                    str4 = str2 + " = {}";
                }
                if (langToConvertTo == "cs") {
                    if (csMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = new " + str3 + "();";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = new " + str3 + "();";
                    }
                }
                if (langToConvertTo == "java") {
                    if (javaMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = new ArrayList<>();";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = new ArrayList<>();";
                    }
                }
                if (langToConvertTo == "kt") {
                    str4 = "var " + str2 + " = " + str3 + "()";
                }
                if (langToConvertTo == "rb") {
                    str4 = str2 + " = []";
                }
                if (langToConvertTo == "nim") {
                    str4 = "var " + str2 + ": " + str3 + " = @[]";
                }
                if (langToConvertTo == "ahk") {
                    str4 = str2 + " := []";
                }
                if (langToConvertTo == "swift") {
                    str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = []";
                }
                if (langToConvertTo == "dart") {
                    str4 = str3 + " " + str2 + " = [];";
                }
                if (langToConvertTo == "ts") {
                    str4 = "let " + str2 + ": " + str3 + " = [];";
                }
                if (langToConvertTo == "groovy") {
                    str4 = str2 + " = []";
                }
            } else {
                //;;;
                //;;;
                //;;;
                //;;;
                //;;;
                str3 = getFuncTypeConvert(str3);
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2 + ";";
                        } else {
                            str4 = str2 + ": " + str3 + ";";
                        }
                    } else {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2;
                        } else {
                            str4 = str2 + ": " + str3;
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (str3 == "double") {
                        str5 = "0.00";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "uint8_t") {
                        str5 = "0";
                    }
                    if (str3 == "uint16_t") {
                        str5 = "0";
                    }
                    if (str3 == "uint32_t") {
                        str5 = "0";
                    }
                    if (str3 == "uint64_t") {
                        str5 = "0ULL";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "std::string") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "bool") {
                        str5 = "false";
                    }
                    if (str3 == "float") {
                        str5 = "0.00f";
                    }
                    if (str3 == "int8_t") {
                        str5 = "0";
                    }
                    if (str3 == "int16_t") {
                        str5 = "0";
                    }
                    if (str3 == "int32_t") {
                        str5 = "0";
                    }
                    if (str3 == "int64_t") {
                        str5 = "0LL";
                    }
                    str4 = str3 + " " + str2 + " = " + str5 + ";";
                }
                if (langToConvertTo == "py") {
                    str4 = str2 + " = None";
                }
                if (langToConvertTo == "js") {
                    str4 = "let " + str2 + ";";
                }
                if (langToConvertTo == "go") {
                    str4 = "var " + str2 + " " + str3;
                }
                if (langToConvertTo == "lua") {
                    str4 = "local " + str2 + " = nil";
                }
                if (langToConvertTo == "cs") {
                    if (str3 == "double") {
                        str5 = "0.0";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "byte") {
                        str5 = "0";
                    }
                    if (str3 == "ushort") {
                        str5 = "0";
                    }
                    if (str3 == "uint") {
                        str5 = "0";
                    }
                    if (str3 == "ulong") {
                        str5 = "0UL";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "string") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "bool") {
                        str5 = "false";
                    }
                    if (str3 == "float") {
                        str5 = "0.0f";
                    }
                    if (str3 == "sbyte") {
                        str5 = "0";
                    }
                    if (str3 == "short") {
                        str5 = "0";
                    }
                    if (str3 == "long") {
                        str5 = "0L";
                    }
                    if (csMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                    }
                }
                if (langToConvertTo == "java") {
                    if (str3 == "double") {
                        str5 = "0.0";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "byte") {
                        str5 = "(byte) 0";
                    }
                    if (str3 == "short") {
                        str5 = "(short) 0";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "long") {
                        str5 = "0L";
                    }
                    if (str3 == "String") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "boolean") {
                        str5 = "false";
                    }
                    if (str3 == "float") {
                        str5 = "0.0f";
                    }
                    if (str3 == "int8") {
                        str5 = "0";
                    }
                    if (str3 == "int16") {
                        str5 = "0";
                    }
                    if (str3 == "int32") {
                        str5 = "0";
                    }
                    if (str3 == "int64") {
                        str5 = "0L";
                    }
                    if (javaMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                    }
                }
                if (langToConvertTo == "kt") {
                    str4 = "var " + str2 + ": " + str3 + "? = null";
                }
                if (langToConvertTo == "rb") {
                    str4 = str2 + " = nil";
                }
                if (langToConvertTo == "nim") {
                    if (str3 == "float") {
                        str5 = "0.0";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "uint8") {
                        str5 = "0";
                    }
                    if (str3 == "uint16") {
                        str5 = "0";
                    }
                    if (str3 == "uint32") {
                        str5 = "0";
                    }
                    if (str3 == "uint64") {
                        str5 = "0";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "string") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "bool") {
                        str5 = "false";
                    }
                    if (str3 == "int8") {
                        str5 = "0";
                    }
                    if (str3 == "int16") {
                        str5 = "0";
                    }
                    if (str3 == "int32") {
                        str5 = "0";
                    }
                    if (str3 == "int64") {
                        str5 = "0";
                    }
                    str4 = "var " + str2 + ": " + str3 + " = " + str5;
                }
                if (langToConvertTo == "ahk") {
                    str4 = str2 + " := " + Chr(34) + Chr(34);
                }
                if (langToConvertTo == "swift") {
                    if (str3 == "Double") {
                        str5 = "0.00";
                    }
                    if (str3 == "Character") {
                        str5 = Chr(34) + "a" + Chr(34);
                    }
                    if (str3 == "UInt8") {
                        str5 = "0";
                    }
                    if (str3 == "UInt16") {
                        str5 = "0";
                    }
                    if (str3 == "UInt32") {
                        str5 = "0";
                    }
                    if (str3 == "UInt64") {
                        str5 = "0";
                    }
                    if (str3 == "Int") {
                        str5 = "0";
                    }
                    if (str3 == "String") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "Bool") {
                        str5 = "false";
                    }
                    if (str3 == "Float") {
                        str5 = "0.00";
                    }
                    if (str3 == "Int8") {
                        str5 = "0";
                    }
                    if (str3 == "Int16") {
                        str5 = "0";
                    }
                    if (str3 == "Int32") {
                        str5 = "0";
                    }
                    if (str3 == "Int64") {
                        str5 = "0";
                    }
                    str4 = "var " + str2 + ": " + str3 + " = " + str5;
                }
                if (langToConvertTo == "dart") {
                    str4 = str3 + "? " + str2 + ";";
                }
                if (langToConvertTo == "ts") {
                    str4 = "let " + str2 + ": " + str3 + ";";
                }
                if (langToConvertTo == "groovy") {
                    str4 = str2 + " = null";
                }
                //;;;
            }
            htCodeOUTOUT += str4 + Chr(10);
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
        }
        else if (SubStr(Trim(A_LoopField91), 1, StrLen(keyWordDouble + " ")) == keyWordDouble + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordChar + " ")) == keyWordChar + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordUint8 + " ")) == keyWordUint8 + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordUint16 + " ")) == keyWordUint16 + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordUint32 + " ")) == keyWordUint32 + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordUint64 + " ")) == keyWordUint64 + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordINT + " ")) == keyWordINT + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordSTR + " ")) == keyWordSTR + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordBOOL + " ")) == keyWordBOOL + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordFLOAT + " ")) == keyWordFLOAT + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordINT8 + " ")) == keyWordINT8 + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordINT16 + " ")) == keyWordINT16 + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordINT32 + " ")) == keyWordINT32 + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordINT64 + " ")) == keyWordINT64 + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordArrayDefinition + " ")) == keyWordArrayDefinition + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordArrayOfIntegersDefinition + " ")) == keyWordArrayOfIntegersDefinition + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordArrayOfStringsDefinition + " ")) == keyWordArrayOfStringsDefinition + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordArrayOfFloatingPointNumbersDefinition + " ")) == keyWordArrayOfFloatingPointNumbersDefinition + " " || SubStr(Trim(A_LoopField91), 1, StrLen(keyWordArrayOfBooleansDefinition + " ")) == keyWordArrayOfBooleansDefinition + " " && usePrefixTypeForTypeDefinition == "on" && lineDone == 0) {
            lineDone = 1;
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
            str1 = Trim(A_LoopField91);
            if (SubStrLastChars(str1, 1) == ";") {
                str1 = StringTrimRight(str1, 1);
            }
            std::vector<std::string> items98 = LoopParseFunc(str1, " ");
            for (size_t A_Index98 = 0; A_Index98 < items98.size() + 0; A_Index98++) {
                std::string A_LoopField98 = items98[A_Index98 - 0];
                str2 = A_LoopField98;
            }
            str3 = Trim(StringTrimRight(str1, StrLen(str2)));
            str2 = lineOspHelpLine + Trim(str2);
            // str2 = var name
            // str3 = type
            HTVM_Append(allVarsSoWeDontReDecVars, str2);
            if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                str3 = getFuncTypeConvert(str3);
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2 + ";";
                        } else {
                            str4 = str2 + ": " + str3 + ";";
                        }
                    } else {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2;
                        } else {
                            str4 = str2 + ": " + str3;
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    str4 = str3 + " " + str2 + ";";
                }
                if (langToConvertTo == "py") {
                    str4 = str2 + " = []";
                }
                if (langToConvertTo == "js") {
                    str4 = "let " + str2 + " = [];";
                }
                if (langToConvertTo == "go") {
                    str4 = "var " + str2 + " " + str3;
                }
                if (langToConvertTo == "lua") {
                    str4 = str2 + " = {}";
                }
                if (langToConvertTo == "cs") {
                    if (csMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = new " + str3 + "();";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = new " + str3 + "();";
                    }
                }
                if (langToConvertTo == "java") {
                    if (javaMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = new ArrayList<>();";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = new ArrayList<>();";
                    }
                }
                if (langToConvertTo == "kt") {
                    str4 = "var " + str2 + " = " + str3 + "()";
                }
                if (langToConvertTo == "rb") {
                    str4 = str2 + " = []";
                }
                if (langToConvertTo == "nim") {
                    str4 = "var " + str2 + ": " + str3 + " = @[]";
                }
                if (langToConvertTo == "ahk") {
                    str4 = str2 + " := []";
                }
                if (langToConvertTo == "swift") {
                    str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = []";
                }
                if (langToConvertTo == "dart") {
                    str4 = str3 + " " + str2 + " = [];";
                }
                if (langToConvertTo == "ts") {
                    str4 = "let " + str2 + ": " + str3 + " = [];";
                }
                if (langToConvertTo == "groovy") {
                    str4 = str2 + " = []";
                }
            } else {
                //;;;
                //;;;
                //;;;
                //;;;
                //;;;
                str3 = getFuncTypeConvert(str3);
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2 + ";";
                        } else {
                            str4 = str2 + ": " + str3 + ";";
                        }
                    } else {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2;
                        } else {
                            str4 = str2 + ": " + str3;
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (str3 == "double") {
                        str5 = "0.00";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "uint8_t") {
                        str5 = "0";
                    }
                    if (str3 == "uint16_t") {
                        str5 = "0";
                    }
                    if (str3 == "uint32_t") {
                        str5 = "0";
                    }
                    if (str3 == "uint64_t") {
                        str5 = "0ULL";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "std::string") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "bool") {
                        str5 = "false";
                    }
                    if (str3 == "float") {
                        str5 = "0.00f";
                    }
                    if (str3 == "int8_t") {
                        str5 = "0";
                    }
                    if (str3 == "int16_t") {
                        str5 = "0";
                    }
                    if (str3 == "int32_t") {
                        str5 = "0";
                    }
                    if (str3 == "int64_t") {
                        str5 = "0LL";
                    }
                    str4 = str3 + " " + str2 + " = " + str5 + ";";
                }
                if (langToConvertTo == "py") {
                    str4 = str2 + " = None";
                }
                if (langToConvertTo == "js") {
                    if (useInJavaScriptAlwaysUseVar == "on") {
                        str4 = "var " + str2 + ";";
                    } else {
                        str4 = "let " + str2 + ";";
                    }
                }
                if (langToConvertTo == "go") {
                    str4 = "var " + str2 + " " + str3;
                }
                if (langToConvertTo == "lua") {
                    str4 = str2 + " = nil";
                }
                if (langToConvertTo == "cs") {
                    if (str3 == "double") {
                        str5 = "0.0";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "byte") {
                        str5 = "0";
                    }
                    if (str3 == "ushort") {
                        str5 = "0";
                    }
                    if (str3 == "uint") {
                        str5 = "0";
                    }
                    if (str3 == "ulong") {
                        str5 = "0UL";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "string") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "bool") {
                        str5 = "false";
                    }
                    if (str3 == "float") {
                        str5 = "0.0f";
                    }
                    if (str3 == "sbyte") {
                        str5 = "0";
                    }
                    if (str3 == "short") {
                        str5 = "0";
                    }
                    if (str3 == "long") {
                        str5 = "0L";
                    }
                    if (csMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                    }
                }
                if (langToConvertTo == "java") {
                    if (str3 == "double") {
                        str5 = "0.0";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "byte") {
                        str5 = "(byte) 0";
                    }
                    if (str3 == "short") {
                        str5 = "(short) 0";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "long") {
                        str5 = "0L";
                    }
                    if (str3 == "String") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "boolean") {
                        str5 = "false";
                    }
                    if (str3 == "float") {
                        str5 = "0.0f";
                    }
                    if (str3 == "int8") {
                        str5 = "0";
                    }
                    if (str3 == "int16") {
                        str5 = "0";
                    }
                    if (str3 == "int32") {
                        str5 = "0";
                    }
                    if (str3 == "int64") {
                        str5 = "0L";
                    }
                    if (javaMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                    }
                }
                if (langToConvertTo == "kt") {
                    str4 = "var " + str2 + ": " + str3 + "? = null";
                }
                if (langToConvertTo == "rb") {
                    str4 = str2 + " = nil";
                }
                if (langToConvertTo == "nim") {
                    if (str3 == "float") {
                        str5 = "0.0";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "uint8") {
                        str5 = "0";
                    }
                    if (str3 == "uint16") {
                        str5 = "0";
                    }
                    if (str3 == "uint32") {
                        str5 = "0";
                    }
                    if (str3 == "uint64") {
                        str5 = "0";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "string") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "bool") {
                        str5 = "false";
                    }
                    if (str3 == "int8") {
                        str5 = "0";
                    }
                    if (str3 == "int16") {
                        str5 = "0";
                    }
                    if (str3 == "int32") {
                        str5 = "0";
                    }
                    if (str3 == "int64") {
                        str5 = "0";
                    }
                    str4 = "var " + str2 + ": " + str3 + " = " + str5;
                }
                if (langToConvertTo == "ahk") {
                    str4 = str2 + " := " + Chr(34) + Chr(34);
                }
                if (langToConvertTo == "swift") {
                    if (str3 == "Double") {
                        str5 = "0.00";
                    }
                    if (str3 == "Character") {
                        str5 = Chr(34) + "a" + Chr(34);
                    }
                    if (str3 == "UInt8") {
                        str5 = "0";
                    }
                    if (str3 == "UInt16") {
                        str5 = "0";
                    }
                    if (str3 == "UInt32") {
                        str5 = "0";
                    }
                    if (str3 == "UInt64") {
                        str5 = "0";
                    }
                    if (str3 == "Int") {
                        str5 = "0";
                    }
                    if (str3 == "String") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "Bool") {
                        str5 = "false";
                    }
                    if (str3 == "Float") {
                        str5 = "0.00";
                    }
                    if (str3 == "Int8") {
                        str5 = "0";
                    }
                    if (str3 == "Int16") {
                        str5 = "0";
                    }
                    if (str3 == "Int32") {
                        str5 = "0";
                    }
                    if (str3 == "Int64") {
                        str5 = "0";
                    }
                    str4 = "var " + str2 + ": " + str3 + " = " + str5;
                }
                if (langToConvertTo == "dart") {
                    str4 = str3 + "? " + str2 + ";";
                }
                if (langToConvertTo == "ts") {
                    if (useInJavaScriptAlwaysUseVar == "on") {
                        str4 = "var " + str2 + ": " + str3 + ";";
                    } else {
                        str4 = "let " + str2 + ": " + str3 + ";";
                    }
                }
                if (langToConvertTo == "groovy") {
                    str4 = str2 + " = null";
                }
                //;;;
            }
            htCodeOUTOUT += str4 + Chr(10);
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
        }
        else if (RegExMatch(Trim(A_LoopField91), "^[a-zA-Z_][a-zA-Z0-9_]*: [^:]*;?$") && usePostfixTypeForTypeDefinition == "on" && lineDone == 0) {
            lineDone = 1;
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
            str1 = Trim(A_LoopField91);
            if (SubStrLastChars(str1, 1) == ";") {
                str1 = StringTrimRight(str1, 1);
            }
            str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
            str3 = Trim(StrSplit(str1, ":", 2));
            // str2 = var name
            // str3 = type
            HTVM_Append(allVarsSoWeDontReDecVars, str2);
            if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                str3 = getFuncTypeConvert(str3);
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2 + ";";
                        } else {
                            str4 = str2 + ": " + str3 + ";";
                        }
                    } else {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2;
                        } else {
                            str4 = str2 + ": " + str3;
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    str4 = str3 + " " + str2 + ";";
                }
                if (langToConvertTo == "py") {
                    str4 = str2 + " = []";
                }
                if (langToConvertTo == "js") {
                    if (useInJavaScriptAlwaysUseVar == "on") {
                        str4 = "var " + str2 + " = [];";
                    } else {
                        str4 = "let " + str2 + " = [];";
                    }
                }
                if (langToConvertTo == "go") {
                    str4 = "var " + str2 + " " + str3;
                }
                if (langToConvertTo == "lua") {
                    str4 = str2 + " = {}";
                }
                if (langToConvertTo == "cs") {
                    if (csMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = new " + str3 + "();";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = new " + str3 + "();";
                    }
                }
                if (langToConvertTo == "java") {
                    if (javaMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = new ArrayList<>();";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = new ArrayList<>();";
                    }
                }
                if (langToConvertTo == "kt") {
                    str4 = "var " + str2 + " = " + str3 + "()";
                }
                if (langToConvertTo == "rb") {
                    str4 = str2 + " = []";
                }
                if (langToConvertTo == "nim") {
                    str4 = "var " + str2 + ": " + str3 + " = @[]";
                }
                if (langToConvertTo == "ahk") {
                    str4 = str2 + " := []";
                }
                if (langToConvertTo == "swift") {
                    str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = []";
                }
                if (langToConvertTo == "dart") {
                    str4 = str3 + " " + str2 + " = [];";
                }
                if (langToConvertTo == "ts") {
                    if (useInJavaScriptAlwaysUseVar == "on") {
                        str4 = "var " + str2 + ": " + str3 + " = [];";
                    } else {
                        str4 = "let " + str2 + ": " + str3 + " = [];";
                    }
                }
                if (langToConvertTo == "groovy") {
                    str4 = str2 + " = []";
                }
            } else {
                //;;;
                //;;;
                //;;;
                //;;;
                //;;;
                str3 = getFuncTypeConvert(str3);
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2 + ";";
                        } else {
                            str4 = str2 + ": " + str3 + ";";
                        }
                    } else {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2;
                        } else {
                            str4 = str2 + ": " + str3;
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (str3 == "double") {
                        str5 = "0.00";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "uint8_t") {
                        str5 = "0";
                    }
                    if (str3 == "uint16_t") {
                        str5 = "0";
                    }
                    if (str3 == "uint32_t") {
                        str5 = "0";
                    }
                    if (str3 == "uint64_t") {
                        str5 = "0ULL";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "std::string") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "bool") {
                        str5 = "false";
                    }
                    if (str3 == "float") {
                        str5 = "0.00f";
                    }
                    if (str3 == "int8_t") {
                        str5 = "0";
                    }
                    if (str3 == "int16_t") {
                        str5 = "0";
                    }
                    if (str3 == "int32_t") {
                        str5 = "0";
                    }
                    if (str3 == "int64_t") {
                        str5 = "0LL";
                    }
                    str4 = str3 + " " + str2 + " = " + str5 + ";";
                }
                if (langToConvertTo == "py") {
                    str4 = str2 + " = None";
                }
                if (langToConvertTo == "js") {
                    if (useInJavaScriptAlwaysUseVar == "on") {
                        str4 = "var " + str2 + ";";
                    } else {
                        str4 = "let " + str2 + ";";
                    }
                }
                if (langToConvertTo == "go") {
                    str4 = "var " + str2 + " " + str3;
                }
                if (langToConvertTo == "lua") {
                    str4 = str2 + " = nil";
                }
                if (langToConvertTo == "cs") {
                    if (str3 == "double") {
                        str5 = "0.0";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "byte") {
                        str5 = "0";
                    }
                    if (str3 == "ushort") {
                        str5 = "0";
                    }
                    if (str3 == "uint") {
                        str5 = "0";
                    }
                    if (str3 == "ulong") {
                        str5 = "0UL";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "string") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "bool") {
                        str5 = "false";
                    }
                    if (str3 == "float") {
                        str5 = "0.0f";
                    }
                    if (str3 == "sbyte") {
                        str5 = "0";
                    }
                    if (str3 == "short") {
                        str5 = "0";
                    }
                    if (str3 == "long") {
                        str5 = "0L";
                    }
                    if (csMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                    }
                }
                if (langToConvertTo == "java") {
                    if (str3 == "double") {
                        str5 = "0.0";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "byte") {
                        str5 = "(byte) 0";
                    }
                    if (str3 == "short") {
                        str5 = "(short) 0";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "long") {
                        str5 = "0L";
                    }
                    if (str3 == "String") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "boolean") {
                        str5 = "false";
                    }
                    if (str3 == "float") {
                        str5 = "0.0f";
                    }
                    if (str3 == "int8") {
                        str5 = "0";
                    }
                    if (str3 == "int16") {
                        str5 = "0";
                    }
                    if (str3 == "int32") {
                        str5 = "0";
                    }
                    if (str3 == "int64") {
                        str5 = "0L";
                    }
                    if (javaMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    } else {
                        str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                    }
                }
                if (langToConvertTo == "kt") {
                    str4 = "var " + str2 + ": " + str3 + "? = null";
                }
                if (langToConvertTo == "rb") {
                    str4 = str2 + " = nil";
                }
                if (langToConvertTo == "nim") {
                    if (str3 == "float") {
                        str5 = "0.0";
                    }
                    if (str3 == "char") {
                        str5 = "'a'";
                    }
                    if (str3 == "uint8") {
                        str5 = "0";
                    }
                    if (str3 == "uint16") {
                        str5 = "0";
                    }
                    if (str3 == "uint32") {
                        str5 = "0";
                    }
                    if (str3 == "uint64") {
                        str5 = "0";
                    }
                    if (str3 == "int") {
                        str5 = "0";
                    }
                    if (str3 == "string") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "bool") {
                        str5 = "false";
                    }
                    if (str3 == "int8") {
                        str5 = "0";
                    }
                    if (str3 == "int16") {
                        str5 = "0";
                    }
                    if (str3 == "int32") {
                        str5 = "0";
                    }
                    if (str3 == "int64") {
                        str5 = "0";
                    }
                    str4 = "var " + str2 + ": " + str3 + " = " + str5;
                }
                if (langToConvertTo == "ahk") {
                    str4 = str2 + " := " + Chr(34) + Chr(34);
                }
                if (langToConvertTo == "swift") {
                    if (str3 == "Double") {
                        str5 = "0.00";
                    }
                    if (str3 == "Character") {
                        str5 = Chr(34) + "a" + Chr(34);
                    }
                    if (str3 == "UInt8") {
                        str5 = "0";
                    }
                    if (str3 == "UInt16") {
                        str5 = "0";
                    }
                    if (str3 == "UInt32") {
                        str5 = "0";
                    }
                    if (str3 == "UInt64") {
                        str5 = "0";
                    }
                    if (str3 == "Int") {
                        str5 = "0";
                    }
                    if (str3 == "String") {
                        str5 = Chr(34) + Chr(34);
                    }
                    if (str3 == "Bool") {
                        str5 = "false";
                    }
                    if (str3 == "Float") {
                        str5 = "0.00";
                    }
                    if (str3 == "Int8") {
                        str5 = "0";
                    }
                    if (str3 == "Int16") {
                        str5 = "0";
                    }
                    if (str3 == "Int32") {
                        str5 = "0";
                    }
                    if (str3 == "Int64") {
                        str5 = "0";
                    }
                    str4 = "var " + str2 + ": " + str3 + " = " + str5;
                }
                if (langToConvertTo == "dart") {
                    str4 = str3 + "? " + str2 + ";";
                }
                if (langToConvertTo == "ts") {
                    if (useInJavaScriptAlwaysUseVar == "on") {
                        str4 = "var " + str2 + ": " + str3 + ";";
                    } else {
                        str4 = "let " + str2 + ": " + str3 + ";";
                    }
                }
                if (langToConvertTo == "groovy") {
                    str4 = str2 + " = null";
                }
                //;;;
            }
            htCodeOUTOUT += str4 + Chr(10);
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
        } else {
            htCodeOUTOUT += A_LoopField91 + Chr(10);
        }
    }
    htCodeOUTOUT = StringTrimRight(htCodeOUTOUT, 1);
    return htCodeOUTOUT;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// the GUI funcs
// the GUI funcs
// the GUI funcs
// the GUI funcs
// the GUI funcs
// the GUI funcs
// the GUI funcs
std::string guiParserStep4(std::string option) {
    // convert and handle the options to js
    std::string out = "";
    // ============================================================
    // ALIAS DEFINITIONS FOR GUI OPTIONS
    // ============================================================
    // elementType, id, parentId, x, y, width, height, zIndex, value, placeholder, callback, backgroundColor, color, rounding, border, rawCss, size, isEnabled, isVisible, isDeleting
    // These arrays hold the valid aliases for each GUI property.
    // They are used to map user input (e.g., "w", "width", "widh")
    // to the canonical property name used in the generated JS (e.g., "width").
    //
    // - `aliases_single_PROPERTY`: Contains single-letter aliases (used like `w100`).
    // - `aliases_colon_PROPERTY`: Contains aliases used with a colon (e.g., `width:100`).
    // Note: All checks should be case-insensitive.
    // --- id Aliases ---
    std::vector<std::string> aliases_single_id = {"i", "v"};
    std::vector<std::string> aliases_colon_id = {"i", "v", "id", "elementId", "eid", "elId"};
    std::string canonical_id = "id";
    // --- parentId Aliases ---
    std::vector<std::string> aliases_single_parentId = {"p"};
    std::vector<std::string> aliases_colon_parentId = {"p", "parentId", "pid", "parId", "divId", "guiId"};
    std::string canonical_parentId = "parentId";
    // --- x Aliases ---
    std::vector<std::string> aliases_single_x = {"x"};
    std::vector<std::string> aliases_colon_x = {"x", "xPos", "xCoord", "xCrd"};
    std::string canonical_x = "x";
    // --- y Aliases ---
    std::vector<std::string> aliases_single_y = {"y"};
    std::vector<std::string> aliases_colon_y = {"y", "yPos", "yCoord", "yCrd"};
    std::string canonical_y = "y";
    // --- width Aliases ---
    std::vector<std::string> aliases_single_width = {"w"};
    std::vector<std::string> aliases_colon_width = {"w", "width", "wight", "widh", "widht", "widhth", "wdtih", "widhh", "widhts"};
    std::string canonical_width = "width";
    // --- height Aliases ---
    std::vector<std::string> aliases_single_height = {"h"};
    std::vector<std::string> aliases_colon_height = {"h", "height", "hight", "heigth", "heigtht", "hieght", "hegt", "heihgt"};
    std::string canonical_height = "height";
    // --- zIndex Aliases ---
    std::vector<std::string> aliases_single_zIndex = {"z"};
    std::vector<std::string> aliases_colon_zIndex = {"z", "zIndex", "z-Index", "zi"};
    std::string canonical_zIndex = "zIndex";
    // --- value Aliases ---
    std::vector<std::string> aliases_single_value = {"d"};
    std::vector<std::string> aliases_colon_value = {"d", "val", "value", "displayValue", "dv"};
    std::string canonical_value = "value";
    // --- placeholder Aliases ---
    std::vector<std::string> aliases_single_placeholder = {"q"};
    std::vector<std::string> aliases_colon_placeholder = {"q", "placeHolder", "plc", "plch", "ph", "grayText", "editForeGround", "editPlaceHolder", "editGrayInfo", "editPlaceHolderGrayInfoText"};
    std::string canonical_placeholder = "placeholder";
    // --- callback Aliases ---
    std::vector<std::string> aliases_single_callback = {"g", "f"};
    std::vector<std::string> aliases_colon_callback = {"g", "f", "callback", "call", "func", "fn", "function", "point", "back", "bakc"};
    std::string canonical_callback = "callback";
    // --- backgroundColor Aliases ---
    std::vector<std::string> aliases_single_backgroundColor = {"o"};
    std::vector<std::string> aliases_colon_backgroundColor = {"o", "bg", "bc", "bgc", "backgroundColor", "bgColor"};
    std::string canonical_backgroundColor = "backgroundColor";
    // --- color Aliases ---
    std::vector<std::string> aliases_single_color = {"c"};
    std::vector<std::string> aliases_colon_color = {"c", "color", "colour", "clr"};
    std::string canonical_color = "color";
    // --- rounding Aliases ---
    std::vector<std::string> aliases_single_rounding = {"r"};
    std::vector<std::string> aliases_colon_rounding = {"r", "rounding", "round", "rounded", "rnd"};
    std::string canonical_rounding = "rounding";
    // --- border Aliases ---
    std::vector<std::string> aliases_single_border = {"b"};
    std::vector<std::string> aliases_colon_border = {"b", "border", "boder", "outline", "brd"};
    std::string canonical_border = "border";
    // --- rawCss Aliases ---
    std::vector<std::string> aliases_single_rawCss = {"l"};
    std::vector<std::string> aliases_colon_rawCss = {"l", "rawCss", "luxury", "rawSsc", "rawScc", "css", "scc", "style", "stlye", "styel", "sytle", "sytel", "stylye", "stiyl", "stiyel", "luxary", "luxuary", "luxery", "luxurey"};
    std::string canonical_rawCss = "rawCss";
    // --- size Aliases ---
    std::vector<std::string> aliases_single_size = {"s"};
    std::vector<std::string> aliases_colon_size = {"s", "size", "sz", "szie", "bigness"};
    std::string canonical_size = "size";
    // --- isEnabled Aliases ---
    std::vector<std::string> aliases_single_isEnabled = {"a"};
    std::vector<std::string> aliases_colon_isEnabled = {"a", "isEnabled", "isE", "isEnb"};
    std::string canonical_isEnabled = "isEnabled";
    // --- isVisible Aliases ---
    std::vector<std::string> aliases_single_isVisible = {"u"};
    std::vector<std::string> aliases_colon_isVisible = {"u", "isVisible", "isV", "isVsb"};
    std::string canonical_isVisible = "isVisible";
    // --- isDeleting Aliases ---
    std::vector<std::string> aliases_single_isDeleting = {"n"};
    std::vector<std::string> aliases_colon_isDeleting = {"n", "isDeleting", "isD", "isDlt", "del", "delete", "remove", "rmv", "rm"};
    std::string canonical_isDeleting = "isDeleting";
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    // aliases_single_id               ; aliases_colon_id               ; canonical_id
    // aliases_single_parentId         ; aliases_colon_parentId         ; canonical_parentId
    // aliases_single_x                ; aliases_colon_x                ; canonical_x
    // aliases_single_y                ; aliases_colon_y                ; canonical_y
    // aliases_single_width            ; aliases_colon_width            ; canonical_width
    // aliases_single_height           ; aliases_colon_height           ; canonical_height
    // aliases_single_zIndex           ; aliases_colon_zIndex           ; canonical_zIndex
    // aliases_single_value            ; aliases_colon_value            ; canonical_value
    // aliases_single_placeholder      ; aliases_colon_placeholder      ; canonical_placeholder
    // aliases_single_callback         ; aliases_colon_callback         ; canonical_callback
    // aliases_single_backgroundColor  ; aliases_colon_backgroundColor  ; canonical_backgroundColor
    // aliases_single_color            ; aliases_colon_color            ; canonical_color
    // aliases_single_rounding         ; aliases_colon_rounding         ; canonical_rounding
    // aliases_single_border           ; aliases_colon_border           ; canonical_border
    // aliases_single_rawCss           ; aliases_colon_rawCss           ; canonical_rawCss
    // aliases_single_size             ; aliases_colon_size             ; canonical_size
    // aliases_single_isEnabled        ; aliases_colon_isEnabled        ; canonical_isEnabled
    // aliases_single_isVisible        ; aliases_colon_isVisible        ; canonical_isVisible
    // aliases_single_isDeleting       ; aliases_colon_isDeleting       ; canonical_isDeleting
    // option
    std::string option0 = "";
    std::string option1 = "";
    if (InStr(option, ":")) {
        option0 = Trim(StrSplit(option, ":", 1));
        option1 = Trim(StrSplit(option, ":", 2));
        //print("=-=-=-=-=-=-=-=-=-=-::::::::::::::::::=-=-=-=-=-=-=-=-=-=-=-=-=")
        //print(option)
        //print(option0)
        //print(option1)
        //print("=-=-=-=-=-=-=-=-=-=-::::::::::::::::::=-=-=-=-=-=-=-=-=-=-=-=-=")
        for (int A_Index99 = 0; A_Index99 < HTVM_Size(aliases_colon_id) + 0; A_Index99++) {
            if (StrLower(option0) == StrLower(aliases_colon_id[A_Index99])) {
                option0 = canonical_id;
                break;
            }
        }
        for (int A_Index100 = 0; A_Index100 < HTVM_Size(aliases_colon_parentId) + 0; A_Index100++) {
            if (StrLower(option0) == StrLower(aliases_colon_parentId[A_Index100])) {
                option0 = canonical_parentId;
                break;
            }
        }
        for (int A_Index101 = 0; A_Index101 < HTVM_Size(aliases_colon_x) + 0; A_Index101++) {
            if (StrLower(option0) == StrLower(aliases_colon_x[A_Index101])) {
                option0 = canonical_x;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (int A_Index102 = 0; A_Index102 < HTVM_Size(aliases_colon_y) + 0; A_Index102++) {
            if (StrLower(option0) == StrLower(aliases_colon_y[A_Index102])) {
                option0 = canonical_y;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (int A_Index103 = 0; A_Index103 < HTVM_Size(aliases_colon_width) + 0; A_Index103++) {
            if (StrLower(option0) == StrLower(aliases_colon_width[A_Index103])) {
                option0 = canonical_width;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (int A_Index104 = 0; A_Index104 < HTVM_Size(aliases_colon_height) + 0; A_Index104++) {
            if (StrLower(option0) == StrLower(aliases_colon_height[A_Index104])) {
                option0 = canonical_height;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (int A_Index105 = 0; A_Index105 < HTVM_Size(aliases_colon_zIndex) + 0; A_Index105++) {
            if (StrLower(option0) == StrLower(aliases_colon_zIndex[A_Index105])) {
                option0 = canonical_zIndex;
                break;
            }
        }
        for (int A_Index106 = 0; A_Index106 < HTVM_Size(aliases_colon_value) + 0; A_Index106++) {
            if (StrLower(option0) == StrLower(aliases_colon_value[A_Index106])) {
                option0 = canonical_value;
                break;
            }
        }
        for (int A_Index107 = 0; A_Index107 < HTVM_Size(aliases_colon_placeholder) + 0; A_Index107++) {
            if (StrLower(option0) == StrLower(aliases_colon_placeholder[A_Index107])) {
                option0 = canonical_placeholder;
                break;
            }
        }
        for (int A_Index108 = 0; A_Index108 < HTVM_Size(aliases_colon_callback) + 0; A_Index108++) {
            if (StrLower(option0) == StrLower(aliases_colon_callback[A_Index108])) {
                option0 = canonical_callback;
                break;
            }
        }
        for (int A_Index109 = 0; A_Index109 < HTVM_Size(aliases_colon_backgroundColor) + 0; A_Index109++) {
            if (StrLower(option0) == StrLower(aliases_colon_backgroundColor[A_Index109])) {
                option0 = canonical_backgroundColor;
                if (RegExMatch(option1, "^(([0-9a-fA-F]{2}){3}|([0-9a-fA-F]){3})$")) {
                    option1 = Chr(34) + "#" + option1 + Chr(34);
                } else {
                    if (InStr(option1, "#")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    }
                }
                // else it's just a var name, just make sure your var name is not a valid 3- or 6-length hex — yeah, kinda weird
                break;
            }
        }
        for (int A_Index110 = 0; A_Index110 < HTVM_Size(aliases_colon_color) + 0; A_Index110++) {
            if (StrLower(option0) == StrLower(aliases_colon_color[A_Index110])) {
                option0 = canonical_color;
                if (RegExMatch(option1, "^(([0-9a-fA-F]{2}){3}|([0-9a-fA-F]){3})$")) {
                    option1 = Chr(34) + "#" + option1 + Chr(34);
                } else {
                    if (InStr(option1, "#")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    }
                }
                // else it's just a var name, just make sure your var name is not a valid 3- or 6-length hex — yeah, kinda weird
                break;
            }
        }
        for (int A_Index111 = 0; A_Index111 < HTVM_Size(aliases_colon_rounding) + 0; A_Index111++) {
            if (StrLower(option0) == StrLower(aliases_colon_rounding[A_Index111])) {
                option0 = canonical_rounding;
                break;
            }
        }
        for (int A_Index112 = 0; A_Index112 < HTVM_Size(aliases_colon_border) + 0; A_Index112++) {
            if (StrLower(option0) == StrLower(aliases_colon_border[A_Index112])) {
                option0 = canonical_border;
                break;
            }
        }
        for (int A_Index113 = 0; A_Index113 < HTVM_Size(aliases_colon_rawCss) + 0; A_Index113++) {
            if (StrLower(option0) == StrLower(aliases_colon_rawCss[A_Index113])) {
                option0 = canonical_rawCss;
                break;
            }
        }
        for (int A_Index114 = 0; A_Index114 < HTVM_Size(aliases_colon_size) + 0; A_Index114++) {
            if (StrLower(option0) == StrLower(aliases_colon_size[A_Index114])) {
                option0 = canonical_size;
                break;
            }
        }
        for (int A_Index115 = 0; A_Index115 < HTVM_Size(aliases_colon_isEnabled) + 0; A_Index115++) {
            if (StrLower(option0) == StrLower(aliases_colon_isEnabled[A_Index115])) {
                option0 = canonical_isEnabled;
                break;
            }
        }
        for (int A_Index116 = 0; A_Index116 < HTVM_Size(aliases_colon_isVisible) + 0; A_Index116++) {
            if (StrLower(option0) == StrLower(aliases_colon_isVisible[A_Index116])) {
                option0 = canonical_isVisible;
                break;
            }
        }
        for (int A_Index117 = 0; A_Index117 < HTVM_Size(aliases_colon_isDeleting) + 0; A_Index117++) {
            if (StrLower(option0) == StrLower(aliases_colon_isDeleting[A_Index117])) {
                option0 = canonical_isDeleting;
                break;
            }
        }
        out = option0 + ":" + Trim(expressionParserTranspiler(Trim(option1)));
        //print("DEBUG out with (:) is: " . out)
    } else {
        option0 = SubStr(option, 1, 1);
        option1 = StringTrimLeft(option, 1);
        //print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=")
        //print(option)
        //print(option0)
        //print(option1)
        //print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=")
        for (int A_Index118 = 0; A_Index118 < HTVM_Size(aliases_single_id) + 0; A_Index118++) {
            if (StrLower(option0) == StrLower(aliases_single_id[A_Index118])) {
                option0 = canonical_id;
                break;
            }
        }
        for (int A_Index119 = 0; A_Index119 < HTVM_Size(aliases_single_parentId) + 0; A_Index119++) {
            if (StrLower(option0) == StrLower(aliases_single_parentId[A_Index119])) {
                option0 = canonical_parentId;
                break;
            }
        }
        for (int A_Index120 = 0; A_Index120 < HTVM_Size(aliases_single_x) + 0; A_Index120++) {
            if (StrLower(option0) == StrLower(aliases_single_x[A_Index120])) {
                option0 = canonical_x;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (int A_Index121 = 0; A_Index121 < HTVM_Size(aliases_single_y) + 0; A_Index121++) {
            if (StrLower(option0) == StrLower(aliases_single_y[A_Index121])) {
                option0 = canonical_y;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (int A_Index122 = 0; A_Index122 < HTVM_Size(aliases_single_width) + 0; A_Index122++) {
            if (StrLower(option0) == StrLower(aliases_single_width[A_Index122])) {
                option0 = canonical_width;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (int A_Index123 = 0; A_Index123 < HTVM_Size(aliases_single_height) + 0; A_Index123++) {
            if (StrLower(option0) == StrLower(aliases_single_height[A_Index123])) {
                option0 = canonical_height;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (int A_Index124 = 0; A_Index124 < HTVM_Size(aliases_single_zIndex) + 0; A_Index124++) {
            if (StrLower(option0) == StrLower(aliases_single_zIndex[A_Index124])) {
                option0 = canonical_zIndex;
                break;
            }
        }
        for (int A_Index125 = 0; A_Index125 < HTVM_Size(aliases_single_value) + 0; A_Index125++) {
            if (StrLower(option0) == StrLower(aliases_single_value[A_Index125])) {
                option0 = canonical_value;
                break;
            }
        }
        for (int A_Index126 = 0; A_Index126 < HTVM_Size(aliases_single_placeholder) + 0; A_Index126++) {
            if (StrLower(option0) == StrLower(aliases_single_placeholder[A_Index126])) {
                option0 = canonical_placeholder;
                break;
            }
        }
        for (int A_Index127 = 0; A_Index127 < HTVM_Size(aliases_single_callback) + 0; A_Index127++) {
            if (StrLower(option0) == StrLower(aliases_single_callback[A_Index127])) {
                option0 = canonical_callback;
                break;
            }
        }
        for (int A_Index128 = 0; A_Index128 < HTVM_Size(aliases_single_backgroundColor) + 0; A_Index128++) {
            if (StrLower(option0) == StrLower(aliases_single_backgroundColor[A_Index128])) {
                option0 = canonical_backgroundColor;
                if (RegExMatch(option1, "^(([0-9a-fA-F]{2}){3}|([0-9a-fA-F]){3})$")) {
                    option1 = Chr(34) + "#" + option1 + Chr(34);
                } else {
                    if (InStr(option1, "#")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    }
                }
                // else it's just a var name, just make sure your var name is not a valid 3- or 6-length hex — yeah, kinda weird
                break;
            }
        }
        for (int A_Index129 = 0; A_Index129 < HTVM_Size(aliases_single_color) + 0; A_Index129++) {
            if (StrLower(option0) == StrLower(aliases_single_color[A_Index129])) {
                option0 = canonical_color;
                if (RegExMatch(option1, "^(([0-9a-fA-F]{2}){3}|([0-9a-fA-F]){3})$")) {
                    option1 = Chr(34) + "#" + option1 + Chr(34);
                } else {
                    if (InStr(option1, "#")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    }
                }
                // else it's just a var name, just make sure your var name is not a valid 3- or 6-length hex — yeah, kinda weird
                break;
            }
        }
        for (int A_Index130 = 0; A_Index130 < HTVM_Size(aliases_single_rounding) + 0; A_Index130++) {
            if (StrLower(option0) == StrLower(aliases_single_rounding[A_Index130])) {
                option0 = canonical_rounding;
                break;
            }
        }
        for (int A_Index131 = 0; A_Index131 < HTVM_Size(aliases_single_border) + 0; A_Index131++) {
            if (StrLower(option0) == StrLower(aliases_single_border[A_Index131])) {
                option0 = canonical_border;
                break;
            }
        }
        for (int A_Index132 = 0; A_Index132 < HTVM_Size(aliases_single_rawCss) + 0; A_Index132++) {
            if (StrLower(option0) == StrLower(aliases_single_rawCss[A_Index132])) {
                option0 = canonical_rawCss;
                break;
            }
        }
        for (int A_Index133 = 0; A_Index133 < HTVM_Size(aliases_single_size) + 0; A_Index133++) {
            if (StrLower(option0) == StrLower(aliases_single_size[A_Index133])) {
                option0 = canonical_size;
                break;
            }
        }
        for (int A_Index134 = 0; A_Index134 < HTVM_Size(aliases_single_isEnabled) + 0; A_Index134++) {
            if (StrLower(option0) == StrLower(aliases_single_isEnabled[A_Index134])) {
                option0 = canonical_isEnabled;
                break;
            }
        }
        for (int A_Index135 = 0; A_Index135 < HTVM_Size(aliases_single_isVisible) + 0; A_Index135++) {
            if (StrLower(option0) == StrLower(aliases_single_isVisible[A_Index135])) {
                option0 = canonical_isVisible;
                break;
            }
        }
        for (int A_Index136 = 0; A_Index136 < HTVM_Size(aliases_single_isDeleting) + 0; A_Index136++) {
            if (StrLower(option0) == StrLower(aliases_single_isDeleting[A_Index136])) {
                option0 = canonical_isDeleting;
                break;
            }
        }
        out = option0 + ":" + Trim(expressionParserTranspiler(Trim(option1)));
        //print("DEBUG out no (:) is: " . out)
    }
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string guiParserStep3(std::string guiCode) {
    // convert the parsed code to func calls
    std::string out = "";
    std::string temp0 = "";
    std::string temp1 = "";
    std::string temp2 = "";
    std::string temp3 = "";
    std::string temp4 = "";
    std::string temp5 = "";
    std::string temp6 = "";
    std::string temp7 = "";
    std::string temp8 = "";
    std::string temp9 = "";
    std::string temp10 = "";
    std::string temp11 = "";
    std::string temp12 = "";
    std::string temp13 = "";
    std::string temp14 = "";
    std::string temp15 = "";
    std::string temp16 = "";
    std::string temp17 = "";
    std::string temp18 = "";
    std::string temp19 = "";
    std::string temp20 = "";
    std::string temp21 = "";
    std::string temp22 = "";
    std::string temp23 = "";
    std::string temp24 = "";
    std::string temp25 = "";
    std::string temp26 = "";
    std::string temp27 = "";
    std::string temp28 = "";
    std::string temp29 = "";
    std::string temp30 = "";
    std::string temp31 = "";
    std::string temp32 = "";
    int found_id = 0;
    int found_parentId = 0;
    int found_x = 0;
    int found_y = 0;
    int found_width = 0;
    int found_height = 0;
    int found_zIndex = 0;
    int found_value = 0;
    int found_placeholder = 0;
    int found_callback = 0;
    int found_backgroundColor = 0;
    int found_color = 0;
    int found_rounding = 0;
    int found_border = 0;
    int found_rawCss = 0;
    int found_size = 0;
    int found_isEnabled = 0;
    int found_isVisible = 0;
    int found_isDeleting = 0;
    std::string openCurlyTEXT = "wklajebawszopsne--tshecurlyybarxccsesgFORguiTHTVM0987HTVM---HTVMAAAadhksudahsdGUI_-_HTVM_OPEN-HTVM--GUI";
    std::string closeCurlyTEXT = "wklajebawszopsne--tshecurlyybarxccsesgFORguiTHTVM0987HTVM---HTVMAAAadhksudahsdGUI_-_HTVM_CLOSE-HTVM--GUI";
    int buttons = -1;
    int texts = -1;
    int edits = -1;
    int pictures = -1;
    int toggles = -1;
    int rectangles = -1;
    int circles = -1;
    int videos = -1;
    int dropdowns = -1;
    int iframes = -1;
    int isElement = 0;
    std::string whatElement = "";
    std::string lowerField = "";
    std::vector<std::string> items137 = LoopParseFunc(guiCode, "\n", "\r");
    for (size_t A_Index137 = 0; A_Index137 < items137.size() + 0; A_Index137++) {
        std::string A_LoopField137 = items137[A_Index137 - 0];
        temp1 = "";
        temp2 = "";
        temp3 = "";
        temp4 = "";
        temp5 = "";
        temp6 = "";
        temp7 = "";
        temp8 = "";
        temp9 = "";
        temp10 = "";
        temp11 = "";
        temp12 = "";
        temp13 = "";
        temp14 = "";
        temp15 = "";
        temp16 = "";
        temp17 = "";
        temp18 = "";
        temp19 = "";
        temp20 = "";
        temp21 = "";
        temp22 = "";
        temp23 = "";
        temp24 = "";
        temp25 = "";
        temp26 = "";
        temp27 = "";
        temp28 = "";
        temp29 = "";
        temp30 = "";
        temp31 = "";
        temp32 = "";
        temp0 = "";
        if (SubStr(Trim(StrLower(A_LoopField137)), 1, 4) == "gui " || RegExMatch(StrLower(Trim(A_LoopField137)), "^gui[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            isElement = 0;
            whatElement = "";
            std::vector<std::string> items138 = LoopParseFunc(A_LoopField137, " ");
            for (size_t A_Index138 = 0; A_Index138 < items138.size() + 0; A_Index138++) {
                std::string A_LoopField138 = items138[A_Index138 - 0];
                if (A_Index138 != 0) {
                    //;;;;;; 0start
                    //;;;;;; 0start (Inside the Loop, Parse, A_LoopField, " " in guiParserStep3)
                    // --- Check for Element Type Aliases ---
                    // Direct name, single-letter prefix 'e', or colon aliases
                    lowerField = StrLower(Trim(A_LoopField138));
                    if (lowerField == "button" || lowerField == "ebutton" || lowerField == "elementType:button" || lowerField == "element:button" || lowerField == "elmnt:button" || lowerField == "elmenet:button" || lowerField == "elment:button" || lowerField == "elemnt:button") {
                        buttons++;
                        isElement = 1;
                        whatElement = "button";
                    }
                    else if (lowerField == "text" || lowerField == "etext" || lowerField == "elementType:text" || lowerField == "element:text" || lowerField == "elmnt:text" || lowerField == "elmenet:text" || lowerField == "elment:text") {
                        texts++;
                        isElement = 1;
                        whatElement = "text";
                    }
                    else if (lowerField == "edit" || lowerField == "eedit" || lowerField == "elementType:edit" || lowerField == "element:edit" || lowerField == "elmnt:edit" || lowerField == "elmenet:edit" || lowerField == "elment:edit") {
                        edits++;
                        isElement = 1;
                        whatElement = "edit";
                    }
                    else if (lowerField == "picture" || lowerField == "epicture" || lowerField == "elementType:picture" || lowerField == "element:picture" || lowerField == "elmnt:picture" || lowerField == "elmenet:picture" || lowerField == "elment:picture") {
                        pictures++;
                        isElement = 1;
                        whatElement = "picture";
                    }
                    else if (lowerField == "toggle" || lowerField == "etoggle" || lowerField == "elementType:toggle" || lowerField == "element:toggle" || lowerField == "elmnt:toggle" || lowerField == "elmenet:toggle" || lowerField == "elment:toggle") {
                        toggles++;
                        isElement = 1;
                        whatElement = "toggle";
                    }
                    else if (lowerField == "rectangle" || lowerField == "erectangle" || lowerField == "elementType:rectangle" || lowerField == "element:rectangle" || lowerField == "elmnt:rectangle" || lowerField == "elmenet:rectangle" || lowerField == "elment:rectangle") {
                        rectangles++;
                        isElement = 1;
                        whatElement = "rectangle";
                    }
                    else if (lowerField == "circle" || lowerField == "ecircle" || lowerField == "elementType:circle" || lowerField == "element:circle" || lowerField == "elmnt:circle" || lowerField == "elmenet:circle" || lowerField == "elment:circle") {
                        circles++;
                        isElement = 1;
                        whatElement = "circle";
                    }
                    else if (lowerField == "video" || lowerField == "evideo" || lowerField == "elementType:video" || lowerField == "element:video" || lowerField == "elmnt:video" || lowerField == "elmenet:video" || lowerField == "elment:video") {
                        videos++;
                        isElement = 1;
                        whatElement = "video";
                    }
                    else if (lowerField == "dropdown" || lowerField == "edropdown" || lowerField == "elementType:dropdown" || lowerField == "element:dropdown" || lowerField == "elmnt:dropdown" || lowerField == "elmenet:dropdown" || lowerField == "elment:dropdown") {
                        dropdowns++;
                        isElement = 1;
                        whatElement = "dropdown";
                    }
                    else if (lowerField == "iframe" || lowerField == "eiframe" || lowerField == "elementType:iframe" || lowerField == "element:iframe" || lowerField == "elmnt:iframe" || lowerField == "elmenet:iframe" || lowerField == "elment:iframe") {
                        iframes++;
                        isElement = 1;
                        whatElement = "iframe";
                    } else {
                        temp1 += guiParserStep4(Trim(A_LoopField138)) + ", ";
                    }
                    //;;;;;; 0end
                    //;;;;; 1start
                    //;;;;; 1end
                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                }
            }
            //;;;;;;;;;;;;;;;;;;;;; -111
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            // step 5
            // step 5
            // step 5
            // step 5 add callback if not defined and more...
            found_id = 0;
            found_parentId = 0;
            found_x = 0;
            found_y = 0;
            found_width = 0;
            found_height = 0;
            found_zIndex = 0;
            found_value = 0;
            found_placeholder = 0;
            found_callback = 0;
            found_backgroundColor = 0;
            found_color = 0;
            found_rounding = 0;
            found_border = 0;
            found_rawCss = 0;
            found_size = 0;
            found_isEnabled = 0;
            found_isVisible = 0;
            found_isDeleting = 0;
            std::vector<std::string> items139 = LoopParseFunc(temp1, ",");
            for (size_t A_Index139 = 0; A_Index139 < items139.size() + 0; A_Index139++) {
                std::string A_LoopField139 = items139[A_Index139 - 0];
                temp2 = Trim(A_LoopField139);
                if (StrSplit(temp2, ":", 1) == "id") {
                    found_id = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "parentId") {
                    found_parentId = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "x") {
                    found_x = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "y") {
                    found_y = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "width") {
                    found_width = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "height") {
                    found_height = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "zIndex") {
                    found_zIndex = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "callback") {
                    found_callback = 1;
                }
            }
            //print("found_id:              " . STR(found_id))
            //print("found_parentId:        " . STR(found_parentId))
            //print("found_x:               " . STR(found_x))
            //print("found_y:               " . STR(found_y))
            //print("found_width:           " . STR(found_width))
            //print("found_height:          " . STR(found_height))
            //print("found_zIndex:          " . STR(found_zIndex))
            //print("found_value:           " . STR(found_value))
            //print("found_placeholder:     " . STR(found_placeholder))
            //print("found_callback:        " . STR(found_callback))
            //print("found_backgroundColor: " . STR(found_backgroundColor))
            //print("found_color:           " . STR(found_color))
            //print("found_rounding:        " . STR(found_rounding))
            //print("found_border:          " . STR(found_border))
            //print("found_rawCss:          " . STR(found_rawCss))
            //print("found_size:            " . STR(found_size))
            //print("found_isEnabled:       " . STR(found_isEnabled))
            //print("found_isVisible:       " . STR(found_isVisible))
            //print("found_isDeleting:      " . STR(found_isDeleting))
            if (isElement == 1 && found_callback == 0) {
                if (whatElement == "button") {
                    temp1 += "callback:" + Chr(34) + "Button" + STR(buttons) + Chr(34) + ", ";
                }
                else if (whatElement == "text") {
                    temp1 += "callback:" + Chr(34) + "Text" + STR(texts) + Chr(34) + ", ";
                }
                else if (whatElement == "edit") {
                    temp1 += "callback:" + Chr(34) + "Edit" + STR(edits) + Chr(34) + ", ";
                }
                else if (whatElement == "picture") {
                    temp1 += "callback:" + Chr(34) + "Picture" + STR(pictures) + Chr(34) + ", ";
                }
                else if (whatElement == "toggle") {
                    temp1 += "callback:" + Chr(34) + "Toggle" + STR(toggles) + Chr(34) + ", ";
                }
                else if (whatElement == "rectangle") {
                    temp1 += "callback:" + Chr(34) + "Rectangle" + STR(rectangles) + Chr(34) + ", ";
                }
                else if (whatElement == "circle") {
                    temp1 += "callback:" + Chr(34) + "Circle" + STR(circles) + Chr(34) + ", ";
                }
                else if (whatElement == "video") {
                    temp1 += "callback:" + Chr(34) + "Video" + STR(videos) + Chr(34) + ", ";
                }
                else if (whatElement == "dropdown") {
                    temp1 += "callback:" + Chr(34) + "Dropdown" + STR(dropdowns) + Chr(34) + ", ";
                }
                else if (whatElement == "iframe") {
                    temp1 += "callback:" + Chr(34) + "Iframe" + STR(iframes) + Chr(34) + ", ";
                }
            }
            if (found_parentId == 0 && isElement == 1) {
                temp1 += "parentId:" + Chr(34) + "div0" + Chr(34) + ", ";
            }
            // step 5
            // step 5
            // step 5
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (isElement == 1) {
                temp0 += "guiAddElement(" + openCurlyTEXT + " elementType: '" + whatElement + "', " + temp1;
                temp0 = StringTrimRight(temp0, 2);
                temp0 += " " + closeCurlyTEXT + ");";
            } else {
                temp0 += "guiAdd(" + openCurlyTEXT + " " + StrReplace(temp1, "parentId:", "id:");
                temp0 = StringTrimRight(temp0, 2);
                temp0 += " " + closeCurlyTEXT + ");";
            }
            //;;;;;;;;;;;;;;;;;;;;; -111
            out += temp0 + Chr(10);
        }
        else if (SubStr(Trim(StrLower(A_LoopField137)), 1, 11) == "guicontrol " || RegExMatch(StrLower(Trim(A_LoopField137)), "^guicontrol[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            isElement = 0;
            whatElement = "";
            std::vector<std::string> items140 = LoopParseFunc(A_LoopField137, " ");
            for (size_t A_Index140 = 0; A_Index140 < items140.size() + 0; A_Index140++) {
                std::string A_LoopField140 = items140[A_Index140 - 0];
                if (A_Index140 != 0) {
                    //;;;;;; 0start
                    //;;;;;; 0start (Inside the Loop, Parse, A_LoopField, " " in guiParserStep3)
                    // --- Check for Element Type Aliases ---
                    // Direct name, single-letter prefix 'e', or colon aliases - all on one line per type
                    lowerField = StrLower(Trim(A_LoopField140));
                    if (lowerField == "button" || lowerField == "ebutton" || lowerField == "elementType:button" || lowerField == "element:button" || lowerField == "elmnt:button" || lowerField == "elmenet:button" || lowerField == "elment:button" || lowerField == "elemnt:button") {
                        buttons++;
                        isElement = 1;
                        whatElement = "button";
                    }
                    else if (lowerField == "text" || lowerField == "etext" || lowerField == "elementType:text" || lowerField == "element:text" || lowerField == "elmnt:text" || lowerField == "elmenet:text" || lowerField == "elment:text") {
                        texts++;
                        isElement = 1;
                        whatElement = "text";
                    }
                    else if (lowerField == "edit" || lowerField == "eedit" || lowerField == "elementType:edit" || lowerField == "element:edit" || lowerField == "elmnt:edit" || lowerField == "elmenet:edit" || lowerField == "elment:edit") {
                        edits++;
                        isElement = 1;
                        whatElement = "edit";
                    }
                    else if (lowerField == "picture" || lowerField == "epicture" || lowerField == "elementType:picture" || lowerField == "element:picture" || lowerField == "elmnt:picture" || lowerField == "elmenet:picture" || lowerField == "elment:picture") {
                        pictures++;
                        isElement = 1;
                        whatElement = "picture";
                    }
                    else if (lowerField == "toggle" || lowerField == "etoggle" || lowerField == "elementType:toggle" || lowerField == "element:toggle" || lowerField == "elmnt:toggle" || lowerField == "elmenet:toggle" || lowerField == "elment:toggle") {
                        toggles++;
                        isElement = 1;
                        whatElement = "toggle";
                    }
                    else if (lowerField == "rectangle" || lowerField == "erectangle" || lowerField == "elementType:rectangle" || lowerField == "element:rectangle" || lowerField == "elmnt:rectangle" || lowerField == "elmenet:rectangle" || lowerField == "elment:rectangle") {
                        rectangles++;
                        isElement = 1;
                        whatElement = "rectangle";
                    }
                    else if (lowerField == "circle" || lowerField == "ecircle" || lowerField == "elementType:circle" || lowerField == "element:circle" || lowerField == "elmnt:circle" || lowerField == "elmenet:circle" || lowerField == "elment:circle") {
                        circles++;
                        isElement = 1;
                        whatElement = "circle";
                    }
                    else if (lowerField == "video" || lowerField == "evideo" || lowerField == "elementType:video" || lowerField == "element:video" || lowerField == "elmnt:video" || lowerField == "elmenet:video" || lowerField == "elment:video") {
                        videos++;
                        isElement = 1;
                        whatElement = "video";
                    }
                    else if (lowerField == "dropdown" || lowerField == "edropdown" || lowerField == "elementType:dropdown" || lowerField == "element:dropdown" || lowerField == "elmnt:dropdown" || lowerField == "elmenet:dropdown" || lowerField == "elment:dropdown") {
                        dropdowns++;
                        isElement = 1;
                        whatElement = "dropdown";
                    }
                    else if (lowerField == "iframe" || lowerField == "eiframe" || lowerField == "elementType:iframe" || lowerField == "element:iframe" || lowerField == "elmnt:iframe" || lowerField == "elmenet:iframe" || lowerField == "elment:iframe") {
                        iframes++;
                        isElement = 1;
                        whatElement = "iframe";
                    } else {
                        temp1 += guiParserStep4(Trim(A_LoopField140)) + ", ";
                    }
                    //;;;;;; 0end
                    //;;;;; 1start
                    //;;;;; 1end
                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                }
            }
            //;;;;;;;;;;;;;;;;;;;;; -111
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            // step 5
            // step 5
            // step 5
            // step 5 add callback if not defined and more...
            found_id = 0;
            found_parentId = 0;
            found_x = 0;
            found_y = 0;
            found_width = 0;
            found_height = 0;
            found_zIndex = 0;
            found_value = 0;
            found_placeholder = 0;
            found_callback = 0;
            found_backgroundColor = 0;
            found_color = 0;
            found_rounding = 0;
            found_border = 0;
            found_rawCss = 0;
            found_size = 0;
            found_isEnabled = 0;
            found_isVisible = 0;
            found_isDeleting = 0;
            std::vector<std::string> items141 = LoopParseFunc(temp1, ",");
            for (size_t A_Index141 = 0; A_Index141 < items141.size() + 0; A_Index141++) {
                std::string A_LoopField141 = items141[A_Index141 - 0];
                temp2 = Trim(A_LoopField141);
                if (StrSplit(temp2, ":", 1) == "parentId") {
                    found_parentId = 1;
                }
            }
            // print("found_parentId: " . STR(found_parentId))
            if (found_parentId == 0) {
                temp1 += "parentId:" + Chr(34) + "div0" + Chr(34) + ", ";
            }
            // step 5
            // step 5
            // step 5
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (isElement == 1) {
                temp0 += "guiControl(" + openCurlyTEXT + " elementType: '" + whatElement + "', " + temp1;
                temp0 = StringTrimRight(temp0, 2);
                temp0 += " " + closeCurlyTEXT + ");";
            } else {
                temp0 += "guiControl(" + openCurlyTEXT + " " + temp1;
                temp0 = StringTrimRight(temp0, 2);
                temp0 += " " + closeCurlyTEXT + ");";
            }
            //;;;;;;;;;;;;;;;;;;;;; -111
            out += temp0 + Chr(10);
        } else {
            out += A_LoopField137 + Chr(10);
        }
    }
    out = StringTrimRight(out, 1);
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string guiParserStep2(std::string guiCode) {
    // remove spacses, commas and format the colon (:) and remove "add"
    std::string out = "";
    std::string temp = "";
    std::vector<std::string> items142 = LoopParseFunc(guiCode, "\n", "\r");
    for (size_t A_Index142 = 0; A_Index142 < items142.size() + 0; A_Index142++) {
        std::string A_LoopField142 = items142[A_Index142 - 0];
        if (SubStr(Trim(StrLower(A_LoopField142)), 1, 11) == "guicontrol " || SubStr(Trim(StrLower(A_LoopField142)), 1, 11) == "guicontrol," || RegExMatch(StrLower(Trim(A_LoopField142)), "^guicontrol[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            temp = StrReplace(A_LoopField142, ",", " ");
            while (InStr(temp, "  ")) {
                temp = StrReplace(temp, "  ", " ");
            }
            while (InStr(temp, ": ")) {
                temp = StrReplace(temp, ": ", ":");
            }
            while (InStr(temp, " :")) {
                temp = StrReplace(temp, " :", ":");
            }
            out += Trim(temp) + Chr(10);
        }
        else if (SubStr(Trim(StrLower(A_LoopField142)), 1, 4) == "gui " || SubStr(Trim(StrLower(A_LoopField142)), 1, 4) == "gui," || RegExMatch(StrLower(Trim(A_LoopField142)), "^gui[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            temp = StrReplace(A_LoopField142, ",", " ");
            temp = RegExReplace(temp, "\\badd\\b(?!\\()", " ");
            while (InStr(temp, "  ")) {
                temp = StrReplace(temp, "  ", " ");
            }
            while (InStr(temp, ": ")) {
                temp = StrReplace(temp, ": ", ":");
            }
            while (InStr(temp, " :")) {
                temp = StrReplace(temp, " :", ":");
            }
            out += Trim(temp) + Chr(10);
        } else {
            out += A_LoopField142 + Chr(10);
        }
    }
    out = StringTrimRight(out, 1);
    return guiParserStep3(out);
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string guiParser0(std::string guiCode) {
    std::string out = "";
    int begin = 0;
    std::vector<std::string> lookAhead;
    std::vector<std::string> items143 = LoopParseFunc(guiCode, "\n", "\r");
    for (size_t A_Index143 = 0; A_Index143 < items143.size() + 0; A_Index143++) {
        std::string A_LoopField143 = items143[A_Index143 - 0];
        HTVM_Append(lookAhead, Trim(A_LoopField143));
    }
    HTVM_Append(lookAhead, " ");
    std::vector<std::string> items144 = LoopParseFunc(guiCode, "\n", "\r");
    for (size_t A_Index144 = 0; A_Index144 < items144.size() + 0; A_Index144++) {
        std::string A_LoopField144 = items144[A_Index144 - 0];
        if (Trim(StrLower(A_LoopField144)) == "guicontrol" || SubStr(Trim(StrLower(A_LoopField144)), 1, 11) == "guicontrol " || SubStr(Trim(StrLower(A_LoopField144)), 1, 11) == "guicontrol," || SubStr(Trim(StrLower(A_LoopField144)), 1, 11) == "guicontrol{" || SubStr(Trim(StrLower(A_LoopField144)), 1, 12) == "guicontrol {" || SubStr(Trim(StrLower(A_LoopField144)), 1, 13) == "guicontrol  {" || SubStr(Trim(StrLower(A_LoopField144)), 1, 11) == "guicontrol[" || SubStr(Trim(StrLower(A_LoopField144)), 1, 12) == "guicontrol [" || SubStr(Trim(StrLower(A_LoopField144)), 1, 13) == "guicontrol  [" || SubStr(Trim(StrLower(A_LoopField144)), 1, 11) == "guicontrol(" || SubStr(Trim(StrLower(A_LoopField144)), 1, 12) == "guicontrol (" || SubStr(Trim(StrLower(A_LoopField144)), 1, 13) == "guicontrol  (" || RegExMatch(StrLower(Trim(A_LoopField144)), "^guicontrol[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            begin = 0;
            if (Trim(StrLower(lookAhead[A_Index144 + 1])) == "{" || Trim(StrLower(lookAhead[A_Index144 + 1])) == "[" || Trim(StrLower(lookAhead[A_Index144 + 1])) == "(") {
                begin = 1;
            }
            if (RegExMatch(StrLower(Trim(A_LoopField144)), "^guicontrol[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)") && SubStrLastChars(Trim(A_LoopField144), 1) == "{" || SubStrLastChars(Trim(A_LoopField144), 1) == "[" || SubStrLastChars(Trim(A_LoopField144), 1) == "(") {
                begin = 1;
                out += StringTrimRight(Trim(A_LoopField144), 1);
            }
            else if (SubStr(Trim(StrLower(A_LoopField144)), 1, 11) == "guicontrol{") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField144), 11);
            }
            else if (SubStr(Trim(StrLower(A_LoopField144)), 1, 11) == "guicontrol[") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField144), 11);
            }
            else if (SubStr(Trim(StrLower(A_LoopField144)), 1, 11) == "guicontrol(") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField144), 11);
            }
            else if (SubStr(Trim(StrLower(A_LoopField144)), 1, 12) == "guicontrol {") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField144), 12);
            }
            else if (SubStr(Trim(StrLower(A_LoopField144)), 1, 12) == "guicontrol [") {
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField144), 12);
            }
            else if (SubStr(Trim(StrLower(A_LoopField144)), 1, 12) == "guicontrol (") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField144), 12);
            }
            else if (SubStr(Trim(StrLower(A_LoopField144)), 1, 13) == "guicontrol  {") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField144), 13);
            }
            else if (SubStr(Trim(StrLower(A_LoopField144)), 1, 13) == "guicontrol  [") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField144), 13);
            }
            else if (SubStr(Trim(StrLower(A_LoopField144)), 1, 13) == "guicontrol  (") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField144), 13);
            } else {
                if (begin == 1) {
                    out += Trim(A_LoopField144) + " ";
                } else {
                    out += Trim(A_LoopField144) + Chr(10);
                }
            }
        }
        else if (begin == 1) {
            if (Trim(StrLower(A_LoopField144)) == "{" || Trim(StrLower(A_LoopField144)) == "[" || Trim(StrLower(A_LoopField144)) == "(") {
                begin = 1;
            }
            else if (Trim(StrLower(A_LoopField144)) == "}" || Trim(StrLower(A_LoopField144)) == "]" || Trim(StrLower(A_LoopField144)) == ")") {
                begin = 0;
                out += Chr(10);
            } else {
                if (SubStr(Trim(A_LoopField144), 1, StrLen(keyWordComment)) != keyWordComment) {
                    out += A_LoopField144 + " ";
                }
            }
        } else {
            out += A_LoopField144 + Chr(10);
        }
        //print("DEBIG123: " . A_LoopField . "|" . STR(begin))
    }
    out = StringTrimRight(out, 1);
    return guiParserStep2(out);
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string guiParser(std::string guiCode) {
    int doWeExitGUIfuncCuzNoGuiFound = 1;
    int doWeExitGUIfuncCuzNoGuiFoundINcommentBlock = 0;
    std::vector<std::string> items145 = LoopParseFunc(guiCode, "\n", "\r");
    for (size_t A_Index145 = 0; A_Index145 < items145.size() + 0; A_Index145++) {
        std::string A_LoopField145 = items145[A_Index145 - 0];
        if (Trim(A_LoopField145) == Trim(keyWordCommentOpenMultiLine)) {
            doWeExitGUIfuncCuzNoGuiFoundINcommentBlock = 1;
        }
        if (Trim(A_LoopField145) == Trim(keyWordCommentCloseMultiLine)) {
            doWeExitGUIfuncCuzNoGuiFoundINcommentBlock = 0;
        }
        if (Trim(StrLower(A_LoopField145)) == "gui" || SubStr(Trim(StrLower(A_LoopField145)), 1, 4) == "gui " || SubStr(Trim(StrLower(A_LoopField145)), 1, 4) == "gui," || SubStr(Trim(StrLower(A_LoopField145)), 1, 4) == "gui{" || SubStr(Trim(StrLower(A_LoopField145)), 1, 5) == "gui {" || SubStr(Trim(StrLower(A_LoopField145)), 1, 6) == "gui  {" || SubStr(Trim(StrLower(A_LoopField145)), 1, 4) == "gui[" || SubStr(Trim(StrLower(A_LoopField145)), 1, 5) == "gui [" || SubStr(Trim(StrLower(A_LoopField145)), 1, 6) == "gui  [" || SubStr(Trim(StrLower(A_LoopField145)), 1, 4) == "gui(" || SubStr(Trim(StrLower(A_LoopField145)), 1, 5) == "gui (" || SubStr(Trim(StrLower(A_LoopField145)), 1, 6) == "gui  (" || RegExMatch(StrLower(Trim(A_LoopField145)), "^gui[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            if (doWeExitGUIfuncCuzNoGuiFoundINcommentBlock == 0) {
                doWeExitGUIfuncCuzNoGuiFound = 0;
            }
        }
    }
    if (doWeExitGUIfuncCuzNoGuiFound == 1) {
        return guiCode;
    }
    std::string out = "";
    int whenGuiBegin = 0;
    int whenGuiBeginTHEONE = 0;
    int begin = 0;
    std::vector<std::string> lookAhead;
    std::vector<std::string> items146 = LoopParseFunc(guiCode, "\n", "\r");
    for (size_t A_Index146 = 0; A_Index146 < items146.size() + 0; A_Index146++) {
        std::string A_LoopField146 = items146[A_Index146 - 0];
        HTVM_Append(lookAhead, Trim(A_LoopField146));
    }
    HTVM_Append(lookAhead, " ");
    std::vector<std::string> items147 = LoopParseFunc(guiCode, "\n", "\r");
    for (size_t A_Index147 = 0; A_Index147 < items147.size() + 0; A_Index147++) {
        std::string A_LoopField147 = items147[A_Index147 - 0];
        if (Trim(StrLower(lookAhead[A_Index147 + 1])) != "{" && Trim(StrLower(lookAhead[A_Index147 + 1])) != "[" && Trim(StrLower(lookAhead[A_Index147 + 1])) != "(" && Trim(StrLower(A_LoopField147)) == "gui") {
            begin = 0;
            //print("DUBUG HKDOUVISYobusdsfvbaedsf")
            whenGuiBegin++;
            if (whenGuiBegin == 1) {
                whenGuiBeginTHEONE = 1;
                out = "HTVM--__gui_init-null,nulllllllllllllldasdfxuoifsedfuiJHTVM---HTVMguiNO-jsadsfpisszdjfpisasJz-HTVM-GUI" + Chr(10) + out;
            }
        }
        else if (Trim(StrLower(A_LoopField147)) == "gui" || SubStr(Trim(StrLower(A_LoopField147)), 1, 4) == "gui " || SubStr(Trim(StrLower(A_LoopField147)), 1, 4) == "gui," || SubStr(Trim(StrLower(A_LoopField147)), 1, 4) == "gui{" || SubStr(Trim(StrLower(A_LoopField147)), 1, 5) == "gui {" || SubStr(Trim(StrLower(A_LoopField147)), 1, 6) == "gui  {" || SubStr(Trim(StrLower(A_LoopField147)), 1, 4) == "gui[" || SubStr(Trim(StrLower(A_LoopField147)), 1, 5) == "gui [" || SubStr(Trim(StrLower(A_LoopField147)), 1, 6) == "gui  [" || SubStr(Trim(StrLower(A_LoopField147)), 1, 4) == "gui(" || SubStr(Trim(StrLower(A_LoopField147)), 1, 5) == "gui (" || SubStr(Trim(StrLower(A_LoopField147)), 1, 6) == "gui  (" || RegExMatch(StrLower(Trim(A_LoopField147)), "^gui[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            begin = 0;
            whenGuiBegin++;
            if (whenGuiBegin == 1) {
                out = "HTVM--__gui_init-null,nulllllllllllllldasdfxuoifsedfuiJHTVM---HTVMguiNO-jsadsfpisszdjfpisasJz-HTVM-GUI" + Chr(10) + out;
            }
            if (Trim(StrLower(lookAhead[A_Index147 + 1])) == "{" || Trim(StrLower(lookAhead[A_Index147 + 1])) == "[" || Trim(StrLower(lookAhead[A_Index147 + 1])) == "(") {
                begin = 1;
            }
            if (RegExMatch(StrLower(Trim(A_LoopField147)), "^gui[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)") && SubStrLastChars(Trim(A_LoopField147), 1) == "{" || SubStrLastChars(Trim(A_LoopField147), 1) == "[" || SubStrLastChars(Trim(A_LoopField147), 1) == "(") {
                begin = 1;
                out += StringTrimRight(Trim(A_LoopField147), 1);
            }
            else if (SubStr(Trim(StrLower(A_LoopField147)), 1, 4) == "gui{") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField147), 4);
            }
            else if (SubStr(Trim(StrLower(A_LoopField147)), 1, 4) == "gui[") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField147), 4);
            }
            else if (SubStr(Trim(StrLower(A_LoopField147)), 1, 4) == "gui(") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField147), 4);
            }
            else if (SubStr(Trim(StrLower(A_LoopField147)), 1, 5) == "gui {") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField147), 5);
            }
            else if (SubStr(Trim(StrLower(A_LoopField147)), 1, 5) == "gui [") {
                out += "gui " + StringTrimLeft(Trim(A_LoopField147), 5);
            }
            else if (SubStr(Trim(StrLower(A_LoopField147)), 1, 5) == "gui (") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField147), 5);
            }
            else if (SubStr(Trim(StrLower(A_LoopField147)), 1, 6) == "gui  {") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField147), 6);
            }
            else if (SubStr(Trim(StrLower(A_LoopField147)), 1, 6) == "gui  [") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField147), 6);
            }
            else if (SubStr(Trim(StrLower(A_LoopField147)), 1, 6) == "gui  (") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField147), 6);
            } else {
                if (begin == 1) {
                    out += Trim(A_LoopField147) + " ";
                } else {
                    out += Trim(A_LoopField147) + Chr(10);
                }
            }
        }
        else if (begin == 1) {
            if (Trim(StrLower(A_LoopField147)) == "{" || Trim(StrLower(A_LoopField147)) == "[" || Trim(StrLower(A_LoopField147)) == "(") {
                begin = 1;
            }
            else if (Trim(StrLower(A_LoopField147)) == "}" || Trim(StrLower(A_LoopField147)) == "]" || Trim(StrLower(A_LoopField147)) == ")") {
                begin = 0;
                out += Chr(10);
            } else {
                if (SubStr(Trim(A_LoopField147), 1, StrLen(keyWordComment)) != keyWordComment) {
                    out += A_LoopField147 + " ";
                }
            }
        } else {
            out += A_LoopField147 + Chr(10);
        }
        //print("DEBIG123: " . A_LoopField . "|" . STR(begin))
    }
    std::string openCurlyTEXT = "wklajebawszopsne--tshecurlyybarxccsesgFORguiTHTVM0987HTVM---HTVMAAAadhksudahsdGUI_-_HTVM_OPEN-HTVM--GUI";
    std::string closeCurlyTEXT = "wklajebawszopsne--tshecurlyybarxccsesgFORguiTHTVM0987HTVM---HTVMAAAadhksudahsdGUI_-_HTVM_CLOSE-HTVM--GUI";
    if (whenGuiBeginTHEONE == 1 && whenGuiBegin == 1) {
        out = StrReplace(out, "HTVM--__gui_init-null,nulllllllllllllldasdfxuoifsedfuiJHTVM---HTVMguiNO-jsadsfpisszdjfpisasJz-HTVM-GUI", "guiInit(" + Chr(34) + "#202020" + Chr(34) + ", " + Chr(34) + "This is a GUI" + Chr(34) + ");");
    } else {
        out = StrReplace(out, "HTVM--__gui_init-null,nulllllllllllllldasdfxuoifsedfuiJHTVM---HTVMguiNO-jsadsfpisszdjfpisasJz-HTVM-GUI", "guiInit(" + Chr(34) + "#202020" + Chr(34) + ", " + Chr(34) + Chr(34) + ");" + Chr(10) + " guiAdd(" + openCurlyTEXT + " x:" + Chr(34) + "0px" + Chr(34) + ", y:" + Chr(34) + "0px" + Chr(34) + ", width:" + Chr(34) + "100%" + Chr(34) + ", height:" + Chr(34) + "100%" + Chr(34) + ", id:" + Chr(34) + "div0" + Chr(34) + ", backgroundColor:" + Chr(34) + "#202020" + Chr(34) + ", rounding:0" + " " + closeCurlyTEXT + ");" + Chr(10));
    }
    out = StringTrimRight(out, 1);
    if (InStr(StrLower(out), "guicontrol")) {
        return guiParser0(out);
    } else {
        return guiParserStep2(out);
    }
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string initializeBackendAndGUIInteractionWithLabelSubroutineLikeButConvertsToFunction(std::string codeToConvert) {
    std::string out = "";
    std::string temp = "";
    std::string temp1 = "";
    std::string temp2 = "";
    int firstTimePythonIn = 0;
    int wasHereNeedFixEndpointCall = 0;
    std::vector<std::string> items148 = LoopParseFunc(codeToConvert, "\n", "\r");
    for (size_t A_Index148 = 0; A_Index148 < items148.size() + 0; A_Index148++) {
        std::string A_LoopField148 = items148[A_Index148 - 0];
        if (RegExMatch(Trim(A_LoopField148), "^[a-zA-Z_][a-zA-Z0-9_]*:$") && isLineAconstruct(Trim(A_LoopField148)) == false) {
            //print("DEBUG: " . A_LoopField)
            temp = StringTrimRight(Trim(A_LoopField148), 1);
            if (langToConvertTo == "js") {
                out += Trim(keyWordAsync) + " " + Trim(keyWordFunc) + " " + Trim(temp) + "(A_Id, A_Event, A_Value )" + Chr(10) + "{" + Chr(10);
            }
            else if (langToConvertTo == "py") {
                initializeBackendAndGUIInteractionWithLabelSubroutineLikeButConvertsToFunction_WAS_IN_PYTHON = 1;
                firstTimePythonIn++;
                if (firstTimePythonIn == 1) {
                    out += Trim(keyWordComment) + " added the HTVM_custom_port()" + Chr(10) + Trim(keyWordComment) + " added the HTVM_register()" + Chr(10) + Trim(keyWordComment) + " added the HTVM_init()" + Chr(10) + Trim(keyWordFunc) + " " + Trim(temp) + "(A_Input=" + Chr(34) + "" + Chr(34) + " )" + Chr(10) + "{" + Chr(10);
                } else {
                    out += Trim(keyWordFunc) + " " + Trim(temp) + "(A_Input=" + Chr(34) + "" + Chr(34) + " )" + Chr(10) + "{" + Chr(10);
                }
            } else {
                out += "!!!NOT POISBLE ONLY POSIBLE IN JS AND PY!!!" + Chr(10);
            }
            // endpoint, enpointName, enpointFunc, [reqType]
            // fileinit, index.html or someJsFile.js or someHtmlFile.html it can be both .html and .js file
            // port, 8000
        }
        else if (SubStr(Trim(StrLower(A_LoopField148)), 1, 9) == "endpoint,") {
            // HTVM_register("endpointName", "endpointName", method="POST")
            temp1 = "";
            std::vector<std::string> items149 = LoopParseFunc(Trim(A_LoopField148), ",");
            for (size_t A_Index149 = 0; A_Index149 < items149.size() + 0; A_Index149++) {
                std::string A_LoopField149 = items149[A_Index149 - 0];
                temp = Trim(A_LoopField149);
                if (A_Index149 != 0) {
                    if (A_Index149 == 1) {
                        if (InStr(temp, Chr(34))) {
                            temp1 += temp + ", ";
                            temp2 = temp;
                        } else {
                            temp1 += Chr(34) + temp + Chr(34) + ", ";
                            temp2 = Chr(34) + temp + Chr(34);
                        }
                    }
                    else if (A_Index149 == 2) {
                        wasHereNeedFixEndpointCall = 1;
                        if (InStr(temp, Chr(34))) {
                            temp1 += temp + ", ";
                        } else {
                            temp1 += Chr(34) + temp + Chr(34) + ", ";
                        }
                    }
                    else if (A_Index149 == 3) {
                        if (InStr(temp, Chr(34))) {
                            temp1 += temp + ", ";
                        } else {
                            temp1 += Chr(34) + temp + Chr(34) + ", ";
                        }
                    } else {
                        if (InStr(temp, Chr(34))) {
                            temp1 += temp + ", ";
                        } else {
                            temp1 += Chr(34) + temp + Chr(34) + ", ";
                        }
                    }
                }
            }
            if (wasHereNeedFixEndpointCall == 0) {
                temp1 += temp2;
            } else {
                temp1 = StringTrimRight(temp1, 2);
            }
            out += "HTVM_register(" + temp1 + ")" + Chr(10);
        }
        else if (SubStr(Trim(StrLower(A_LoopField148)), 1, 9) == "fileinit,") {
            // HTVM_init("fileName")
            temp1 = "";
            std::vector<std::string> items150 = LoopParseFunc(Trim(A_LoopField148), ",");
            for (size_t A_Index150 = 0; A_Index150 < items150.size() + 0; A_Index150++) {
                std::string A_LoopField150 = items150[A_Index150 - 0];
                temp = Trim(A_LoopField150);
                if (A_Index150 != 0) {
                    if (A_Index150 == 1) {
                        if (InStr(temp, Chr(34))) {
                            temp1 += temp;
                        } else {
                            temp1 += Chr(34) + temp + Chr(34);
                        }
                    }
                }
            }
            out += "HTVM_init(" + temp1 + ")" + Chr(10);
        }
        else if (SubStr(Trim(StrLower(A_LoopField148)), 1, 5) == "port,") {
            // HTVM_custom_port("fileName")
            temp1 = "";
            std::vector<std::string> items151 = LoopParseFunc(Trim(A_LoopField148), ",");
            for (size_t A_Index151 = 0; A_Index151 < items151.size() + 0; A_Index151++) {
                std::string A_LoopField151 = items151[A_Index151 - 0];
                temp = Trim(A_LoopField151);
                if (A_Index151 != 0) {
                    if (A_Index151 == 1) {
                        temp1 += temp;
                    }
                }
            }
            temp1 = Trim(StrReplace(temp1, Chr(34), ""));
            out += "HTVM_custom_port(" + temp1 + ")" + Chr(10);
        }
        else if (Trim(StrLower(A_LoopField148)) == "subout") {
            out += "}" + Chr(10);
        } else {
            out += A_LoopField148 + Chr(10);
        }
    }
    out = StringTrimRight(out, 1);
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// --------------------------------------------------
// TrimR Function Definition
// Removes trailing whitespace (space, tab, newline, carriage return)
// from the right side of a string.
// Parameters:
//   inputString (str): The string to trim.
// Returns:
//   str: The string with trailing whitespace removed.
// --------------------------------------------------
std::string TrimR(std::string inputString) {
    int len = StrLen(inputString);
    int lastNonWhitespaceIndex = 0;
    // Handle empty string immediately
    if (len == 0) {
        return "";
    }
    std::string charr = "";
    // Loop backwards from the last character (index len) down to the first (index 1)
    int i = len;
    while (i >= 1) {
        // Get the character at the current index (using 1-based SubStr)
        charr = SubStr(inputString, i, 1);
        // Check if the character is NOT whitespace
        if (charr != " " && charr != Chr(9) && charr != Chr(13) && charr != Chr(10)) {
            // This is the last non-whitespace character found
            lastNonWhitespaceIndex = i;
            break;
        }
        // Decrement index to check the previous character
        i = i - 1;
    }
    // If no non-whitespace character was found (string was all whitespace)
    if (lastNonWhitespaceIndex == 0) {
        return "";
    }
    // Extract the substring from the beginning (index 1) up to the
    // last non-whitespace character found (index lastNonWhitespaceIndex)
    return SubStr(inputString, 1, lastNonWhitespaceIndex);
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
bool fixHTVMToHTVMMissingAfterAssignmentOperatorHELP(std::string line) {
    std::string last = "";
    line = Trim(line);
    std::vector<std::string> items152 = LoopParseFunc(line, " ");
    for (size_t A_Index152 = 0; A_Index152 < items152.size() + 0; A_Index152++) {
        std::string A_LoopField152 = items152[A_Index152 - 0];
        last = Trim(A_LoopField152);
    }
    if (last == keyWordAssign_2 || last == keyWordAssignAdd_2 || last == keyWordAssignConcat_2 || last == keyWordAssignSub_2 || last == keyWordAssignMul_2 || last == keyWordAssignDiv_2 || last == keyWordAssignMod_2 || last == keyWordAssignShiftLeft_2 || last == keyWordAssignShiftRight_2 || last == keyWordLogicalAssignShiftRight_2 || last == keyWordAssignBitAnd_2 || last == keyWordAssignBitOr_2 || last == keyWordAssignBitXor_2) {
        return true;
    }
    return false;
}
std::string fixHTVMToHTVMMissingAfterAssignmentOperator(std::string line) {
    std::string out = "";
    std::vector<std::string> items153 = LoopParseFunc(line, "\n", "\r");
    for (size_t A_Index153 = 0; A_Index153 < items153.size() + 0; A_Index153++) {
        std::string A_LoopField153 = items153[A_Index153 - 0];
        if (fixHTVMToHTVMMissingAfterAssignmentOperatorHELP(A_LoopField153)) {
            if (useCurlyBracesSyntaxForArrayDef_2 == "off") {
                out += TrimR(A_LoopField153) + " []" + Chr(10);
            } else {
                out += TrimR(A_LoopField153) + " {}" + Chr(10);
            }
        } else {
            out += A_LoopField153 + Chr(10);
        }
    }
    out = StringTrimRight(out, 1);
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string fixLastParentesis(std::string lines) {
    int open = 0;
    int close = 0;
    std::string out = "";
    std::vector<std::string> items154 = LoopParseFunc(lines, "\n", "\r");
    for (size_t A_Index154 = 0; A_Index154 < items154.size() + 0; A_Index154++) {
        std::string A_LoopField154 = items154[A_Index154 - 0];
        open = 0;
        close = 0;
        std::vector<std::string> items155 = LoopParseFunc(A_LoopField154);
        for (size_t A_Index155 = 0; A_Index155 < items155.size() + 0; A_Index155++) {
            std::string A_LoopField155 = items155[A_Index155 - 0];
            if (A_LoopField155 == "(") {
                open++;
            }
            if (A_LoopField155 == ")") {
                close++;
            }
        }
        if (open != close) {
            if (InStr(A_LoopField154, " {")) {
                out += StrReplace(A_LoopField154, " {", ") {") + Chr(10);
            } else {
                out += A_LoopField154 + ")" + Chr(10);
            }
        } else {
            out += A_LoopField154 + Chr(10);
        }
    }
    out = StringTrimRight(out, 1);
    return out;
}
std::string fixJAVAcmpANDandORtheFixForTheFix(std::string javaCodeUgh) {
    std::string out = "";
    std::vector<std::string> items156 = LoopParseFunc(javaCodeUgh, "\n", "\r");
    for (size_t A_Index156 = 0; A_Index156 < items156.size() + 0; A_Index156++) {
        std::string A_LoopField156 = items156[A_Index156 - 0];
        if (SubStr(Trim(A_LoopField156), 1, 3) == "if " && InStr(A_LoopField156, "__HTVM_V2_TO_JAVA_optionalParams__") == false) {
            if (InStr(A_LoopField156, " && ") || InStr(A_LoopField156, " || ")) {
                out += StrReplace(StrReplace(A_LoopField156, " || ", ") || ("), " && ", ") && (") + Chr(10);
            } else {
                out += A_LoopField156 + Chr(10);
            }
        } else {
            out += A_LoopField156 + Chr(10);
        }
    }
    out = StringTrimRight(out, 1);
    out = fixLastParentesis(out);
    std::string out1 = "";
    std::vector<std::string> items157 = LoopParseFunc(out, "\n", "\r");
    for (size_t A_Index157 = 0; A_Index157 < items157.size() + 0; A_Index157++) {
        std::string A_LoopField157 = items157[A_Index157 - 0];
        if (SubStr(Trim(A_LoopField157), 1, 3) == "if " && InStr(A_LoopField157, "__HTVM_V2_TO_JAVA_optionalParams__") == false) {
            out1 += RegExReplace(A_LoopField157, "\\bif\\b", "if (") + Chr(10);
        } else {
            out1 += A_LoopField157 + Chr(10);
        }
    }
    out1 = StringTrimRight(out1, 1);
    out1 = fixLastParentesis(out1);
    return out1;
}
std::string FIXregexEspaceThem(std::string line) {
    line = StrReplace(line, "\\", "\\\\");
    line = StrReplace(line, ".", "\\.");
    line = StrReplace(line, "*", "\\*");
    line = StrReplace(line, "+", "\\+");
    line = StrReplace(line, "?", "\\?");
    line = StrReplace(line, "^", "\\^");
    line = StrReplace(line, "$", "\\$");
    line = StrReplace(line, "{", "\\{");
    line = StrReplace(line, "}", "\\}");
    line = StrReplace(line, "(", "\\(");
    line = StrReplace(line, ")", "\\)");
    line = StrReplace(line, "|", "\\|");
    line = StrReplace(line, "[", "\\[");
    line = StrReplace(line, "]", "\\]");
    line = StrReplace(line, "-", "\\-");
    return line;
}
std::string fixJAVAstrCmp_FjavaUGH(std::string javaCode) {
    std::vector<std::string> allJavaStringsIG;
    int next = 0;
    std::vector<std::string> items158 = LoopParseFunc(javaCode, " ");
    for (size_t A_Index158 = 0; A_Index158 < items158.size() + 0; A_Index158++) {
        std::string A_LoopField158 = items158[A_Index158 - 0];
        if (InStr(A_LoopField158, "ihuiuuhuuhtheidFor--asds")) {
            HTVM_Append(allJavaStringsIG, Trim(FIXregexEspaceThem(A_LoopField158)));
        }
        if (next == 1) {
            if (RegExMatch(Trim(A_LoopField158), "^[A-Za-z_][A-Za-z0-9_]*$")) {
                HTVM_Append(allJavaStringsIG, Trim(FIXregexEspaceThem(A_LoopField158)));
            }
            next = 0;
        }
        if (A_LoopField158 == "String") {
            next = 1;
        }
    }
    std::string pattern1 = "";
    std::string pattern2 = "";
    std::string pattern3 = "";
    std::string pattern4 = "";
    std::string replace1 = "";
    std::string replace2 = "";
    std::string replace3 = "";
    std::string replace4 = "";
    std::string varName = "";
    for (int A_Index159 = 0; A_Index159 < HTVM_Size(allJavaStringsIG) + 0; A_Index159++) {
        varName = allJavaStringsIG[A_Index159];
        pattern3 = "\\b" + varName + "\\s*!=\\s*([\\w\\.\\(\\)\\[\\],]+)";
        replace3 = "!(" + varName + ".equals($1))";
        javaCode = RegExReplace(javaCode, pattern3, replace3);
        pattern4 = "\\b([\\w\\.\\(\\)\\[\\],]+)\\s*!=\\s*" + varName;
        replace4 = "!(" + varName + ".equals($1))";
        pattern1 = "\\b" + varName + "\\s*==\\s*([\\w\\.\\(\\)\\[\\],]+)";
        replace1 = varName + ".equals($1)";
        javaCode = RegExReplace(javaCode, pattern1, replace1);
        pattern2 = "\\b([\\w\\.\\(\\)\\[\\],]+)\\s*==\\s*" + varName;
        replace2 = varName + ".equals($1)";
        javaCode = RegExReplace(javaCode, pattern2, replace2);
        javaCode = RegExReplace(javaCode, pattern4, replace4);
    }
    javaCode = StrReplace(javaCode, "huiuuhuuhtheidFor\\-\\-asdsas\\-\\-theuhturtyphoutr\\-\\-AA", "huiuuhuuhtheidFor--asdsas--theuhturtyphoutr--AA");
    javaCode = StrReplace(javaCode, "AA\\).equals(", "AA.equals(");
    javaCode = StrReplace(javaCode, ".equals(ihuiuuhuuhtheidFor)--asdsas--theuhturtyphoutr--AA", ".equals(ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--AA");
    javaCode = StrReplace(javaCode, ".equals(ihuiuuhuuhtheidFor))--asdsas--theuhturtyphoutr--AA", ".equals(ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--AA");
    if (InStr(javaCode, " && ") || InStr(javaCode, " || ")) {
        javaCode = fixJAVAcmpANDandORtheFixForTheFix(javaCode);
    }
    javaCode = fixLastParentesis(javaCode);
    javaCode = fixLastParentesis(javaCode);
    javaCode = fixLastParentesis(javaCode);
    return javaCode;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string FixDoubleInThe4langs(std::string line) {
    std::string FixDoubleInThe4langsOUT = "";
    std::vector<std::string> items160 = LoopParseFunc(line, "\n", "\r");
    for (size_t A_Index160 = 0; A_Index160 < items160.size() + 0; A_Index160++) {
        std::string A_LoopField160 = items160[A_Index160 - 0];
        if (RegExMatch(A_LoopField160, "\\bdouble\\b") || RegExMatch(A_LoopField160, "\\bDouble\\b")) {
            FixDoubleInThe4langsOUT += RegExReplace(A_LoopField160, "(?<![A-Za-z0-9_])(-?\\d+\\.\\d+)f(?![A-Za-z0-9_])", "$1") + Chr(10);
        } else {
            FixDoubleInThe4langsOUT += A_LoopField160 + Chr(10);
        }
    }
    FixDoubleInThe4langsOUT = StringTrimRight(FixDoubleInThe4langsOUT, 1);
    return FixDoubleInThe4langsOUT;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string fStringHELP(std::string line) {
    line = RegExReplace(line, "\\b" + keyWordAIndex + "\\d*\\b", "" + keyWordAIndex + "" + str2);
    line = RegExReplace(line, "\\b" + keyWordALoopField + "\\d*\\b", "" + keyWordALoopField + "" + str2);
    return line;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string fString(std::string line) {
    std::string outHelp = "";
    std::string out = "";
    int areWeIn = 0;
    std::string concatStringInOtherLangs = "+";
    if (langToConvertTo != langFileExtension_2) {
        if (langToConvertTo == "lua") {
            concatStringInOtherLangs = "..";
        }
        else if (langToConvertTo == "ahk") {
            concatStringInOtherLangs = ".";
        }
        else if (langToConvertTo == "nim") {
            concatStringInOtherLangs = "&";
        }
        std::vector<std::string> items161 = LoopParseFunc(line);
        for (size_t A_Index161 = 0; A_Index161 < items161.size() + 0; A_Index161++) {
            std::string A_LoopField161 = items161[A_Index161 - 0];
            if (areWeIn == 1 && A_LoopField161 != "{" && A_LoopField161 != "}") {
                outHelp += A_LoopField161;
            } else {
                if (A_LoopField161 == "{") {
                    out += Chr(34) + " " + concatStringInOtherLangs + " fstr(";
                }
                else if (A_LoopField161 == "}" && areWeIn != 0) {
                    out += expressionParserTranspiler(fStringHELP(outHelp)) + ") " + concatStringInOtherLangs + " " + Chr(34);
                    outHelp = "";
                } else {
                    out += A_LoopField161;
                }
            }
            if (A_LoopField161 == "{") {
                areWeIn = 1;
            }
            if (A_LoopField161 == "}") {
                areWeIn = 0;
            }
        }
    } else {
        std::vector<std::string> items162 = LoopParseFunc(line);
        for (size_t A_Index162 = 0; A_Index162 < items162.size() + 0; A_Index162++) {
            std::string A_LoopField162 = items162[A_Index162 - 0];
            if (areWeIn == 1 && A_LoopField162 != "{" && A_LoopField162 != "}") {
                outHelp += A_LoopField162;
            } else {
                if (A_LoopField162 == "{") {
                    out += "{";
                }
                else if (A_LoopField162 == "}" && areWeIn != 0) {
                    out += expressionParserTranspiler(outHelp) + "}";
                    outHelp = "";
                } else {
                    out += A_LoopField162;
                }
            }
            if (A_LoopField162 == "{") {
                areWeIn = 1;
            }
            if (A_LoopField162 == "}") {
                areWeIn = 0;
            }
        }
    }
    if (langToConvertTo == "rb") {
        for (int A_Index163 = 0; A_Index163 < HTVM_Size(htCodeFixRubyGlobalVars_EXPOSED) + 0; A_Index163++) {
            out = RegExReplace(out, "\\b" + htCodeFixRubyGlobalVars_EXPOSED[A_Index163] + "\\b", "$" + htCodeFixRubyGlobalVars_EXPOSED[A_Index163]);
        }
    }
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string handleMultiLineStrings(std::string code) {
    int didWeFindOrWeOut = 0;
    std::vector<std::string> items164 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index164 = 0; A_Index164 < items164.size() + 0; A_Index164++) {
        std::string A_LoopField164 = items164[A_Index164 - 0];
        if (SubStrLastChars(Trim(A_LoopField164), 4) == " mls" || SubStrLastChars(Trim(A_LoopField164), 5) == " fmls") {
            didWeFindOrWeOut = 1;
        }
    }
    if (didWeFindOrWeOut == 0) {
        return code;
    }
    std::string out = "";
    code = StrReplace(code, Chr(10) , Chr(10) + "HTVM-newLineAHw4y9w730q8237w4e8srhgesw0s8rgw04e5g08sgr0e8srdgt--YOU-BETERNOTUSETHISAH--aesdfssz" + Chr(10));
    std::vector<std::string> lookAhead;
    std::vector<std::string> items165 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index165 = 0; A_Index165 < items165.size() + 0; A_Index165++) {
        std::string A_LoopField165 = items165[A_Index165 - 0];
        HTVM_Append(lookAhead, Trim(A_LoopField165));
    }
    HTVM_Append(lookAhead, Trim(" "));
    int weAreIn = 0;
    int weAreInOnce = 0;
    int weAreInNum = 0;
    std::string weAreInMLSarrTemp = "";
    std::vector<std::string> items166 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index166 = 0; A_Index166 < items166.size() + 0; A_Index166++) {
        std::string A_LoopField166 = items166[A_Index166 - 0];
        if (langToConvertTo == langFileExtension_2) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (weAreIn == 1 && Trim(A_LoopField166) == "mle") {
                HTVM_Append(weAreInMLSarr, StringTrimRight(StringTrimLeft(StrReplace(weAreInMLSarrTemp, "HTVM-newLineAHw4y9w730q8237w4e8srhgesw0s8rgw04e5g08sgr0e8srdgt--YOU-BETERNOTUSETHISAH--aesdfssz", Chr(10)), 1), 1));
                weAreInMLSarrTemp = "";
                weAreInOnce = 0;
                weAreIn = 0;
            }
            if (weAreIn == 1) {
                weAreInOnce++;
                if (weAreInOnce == 1) {
                    out += "aejsoydoxubviycbdgsut7eoy-ihsxbvhowadesdio6376e7wuwyuau--szd--AA" + STR(weAreInNum) + "AA" + Chr(10);
                    weAreInNum++;
                }
                weAreInMLSarrTemp += A_LoopField166;
            }
            if (SubStrLastChars(Trim(A_LoopField166), 4) == " mls" || SubStrLastChars(Trim(A_LoopField166), 5) == " fmls") {
                weAreIn = 1;
                out += A_LoopField166 + Chr(10);
            }
            if (weAreIn == 0) {
                out += A_LoopField166 + Chr(10);
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        } else {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (weAreIn == 1 && Trim(A_LoopField166) == "mle") {
                out = StringTrimRight(out, 2);
                out += Chr(34) + Chr(10);
                weAreIn = 0;
            }
            if (weAreIn == 1 && Trim(A_LoopField166) == "HTVM-newLineAHw4y9w730q8237w4e8srhgesw0s8rgw04e5g08sgr0e8srdgt--YOU-BETERNOTUSETHISAH--aesdfssz") {
                if (lookAhead[A_Index166 + 1] == "HTVM-newLineAHw4y9w730q8237w4e8srhgesw0s8rgw04e5g08sgr0e8srdgt--YOU-BETERNOTUSETHISAH--aesdfssz") {
                    out += keyWordEscpaeChar + "n";
                }
            }
            if (weAreIn == 1 && Trim(A_LoopField166) != "HTVM-newLineAHw4y9w730q8237w4e8srhgesw0s8rgw04e5g08sgr0e8srdgt--YOU-BETERNOTUSETHISAH--aesdfssz") {
                out += A_LoopField166 + keyWordEscpaeChar + "n";
            }
            if (SubStrLastChars(Trim(A_LoopField166), 4) == " mls" || SubStrLastChars(Trim(A_LoopField166), 5) == " fmls") {
                weAreIn = 1;
                if (SubStrLastChars(Trim(A_LoopField166), 5) == " fmls") {
                    out += TrimR(StringTrimRight(TrimR(A_LoopField166), 3)) + Chr(34);
                } else {
                    out += TrimR(StringTrimRight(TrimR(A_LoopField166), 3)) + " " + Chr(34);
                }
            }
            if (weAreIn == 0) {
                if (Trim(A_LoopField166) != "mle") {
                    out += A_LoopField166 + Chr(10);
                }
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        }
    }
    out = StrReplace(out, "HTVM-newLineAHw4y9w730q8237w4e8srhgesw0s8rgw04e5g08sgr0e8srdgt--YOU-BETERNOTUSETHISAH--aesdfssz", Chr(10) + Chr(10));
    out = StringTrimRight(out, 1);
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::vector<std::string> slidingWinFixCommentsRmFUNC(std::string line) {
    std::vector<std::string> slidingWinFixCommentsRmFFFF;
    std::vector<std::string> items167 = LoopParseFunc(line);
    for (size_t A_Index167 = 0; A_Index167 < items167.size() + 0; A_Index167++) {
        std::string A_LoopField167 = items167[A_Index167 - 0];
        HTVM_Append(slidingWinFixCommentsRmFFFF, A_LoopField167);
    }
    for (int A_Index168 = 0; A_Index168 < StrLen(keyWordComment + keyWordComment) + 2 + 0; A_Index168++) {
        HTVM_Append(slidingWinFixCommentsRmFFFF, " ");
    }
    return slidingWinFixCommentsRmFFFF;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string when_patternMatchingHELP1(std::string line) {
    std::string pading = "";
    std::vector<std::string> items169 = LoopParseFunc(line);
    for (size_t A_Index169 = 0; A_Index169 < items169.size() + 0; A_Index169++) {
        std::string A_LoopField169 = items169[A_Index169 - 0];
        if (A_LoopField169 != " ") {
            break;
        } else {
            pading += " ";
        }
    }
    return pading;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string when_patternMatching_HELP_HTVMtoHTVM(std::string theCode) {
    std::string out = "";
    int inWhen = 0;
    std::string temp = "";
    std::vector<std::string> items170 = LoopParseFunc(theCode, "\n", "\r");
    for (size_t A_Index170 = 0; A_Index170 < items170.size() + 0; A_Index170++) {
        std::string A_LoopField170 = items170[A_Index170 - 0];
        if (Trim(A_LoopField170) == "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2") {
            inWhen = 0;
        }
        if (inWhen > 0 && SubStr(Trim(A_LoopField170), 1, 5) != "when " && SubStr(Trim(A_LoopField170), 1, 5) != "wehn " && Trim(A_LoopField170) != "when" && Trim(A_LoopField170) != "wehn") {
            if (Trim(A_LoopField170) == Trim(keyWordElse)) {
                out += StrReplace(A_LoopField170, Trim(keyWordElse), "HTVM-------else---HTVM--parartenet--manstccing--hdksfbsdWYOUWHOUDNEVERBEABALETOTYPEYHIS--FFfix") + Chr(10);
            } else {
                out += A_LoopField170 + Chr(10);
            }
        } else {
            out += A_LoopField170 + Chr(10);
        }
        if (SubStr(Trim(A_LoopField170), 1, 5) == "when " || SubStr(Trim(A_LoopField170), 1, 5) == "wehn " || Trim(A_LoopField170) == "when" || Trim(A_LoopField170) == "wehn") {
            inWhen++;
        }
        if (Trim(A_LoopField170) == "subout" && inWhen != 0) {
            inWhen--;
        }
    }
    out = StringTrimRight(out, 1);
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string when_patternMatching(std::string theCode) {
    std::string out = "";
    int inWhen = 0;
    int isWhenWhitVal = 0;
    int firstUseIF = 0;
    int firstUseIF_HELP = 0;
    std::string preFixIfORelseIf = "";
    std::string whenStackSTR = "";
    std::vector<std::string> whenStack;
    std::string temp = "";
    std::string temp1 = "";
    std::string temp2 = "";
    std::string temp3 = "";
    std::string temp4 = "";
    std::string temp5 = "";
    std::string temp6 = "";
    std::string temp7 = "";
    std::string temp8 = "";
    std::string temp9 = "";
    std::string pading = "";
    std::vector<std::string> items171 = LoopParseFunc(theCode, "\n", "\r");
    for (size_t A_Index171 = 0; A_Index171 < items171.size() + 0; A_Index171++) {
        std::string A_LoopField171 = items171[A_Index171 - 0];
        if (inWhen > 0 && SubStr(Trim(A_LoopField171), 1, 5) != "when " && SubStr(Trim(A_LoopField171), 1, 5) != "wehn " && Trim(A_LoopField171) != "when" && Trim(A_LoopField171) != "wehn") {
            if (InStr(A_LoopField171, "->")) {
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                temp = A_LoopField171;
                pading = when_patternMatchingHELP1(temp);
                temp = Trim(temp);
                whenStackSTR = whenStack[HTVM_Size(whenStack) - 1];
                if (whenStackSTR == "-=-NON-=-") {
                    isWhenWhitVal = 0;
                } else {
                    isWhenWhitVal = 1;
                }
                if (firstUseIF == 1) {
                    firstUseIF = 0;
                    firstUseIF_HELP = 1;
                    preFixIfORelseIf = Trim(keyWordIF);
                } else {
                    firstUseIF_HELP = 0;
                    preFixIfORelseIf = Trim(keyWordElseIf);
                }
                // keyWordIF
                // keyWordElseIf
                // keyWordElse
                // keyWordEqual — =
                // keyWordGreaterEqual — >=
                // keyWordLessEqual — <=
                // keyWordAnd — and
                // keyWordOr — or
                if (RegExMatch(temp, "\\b" + Trim(keyWordElse) + "\\b")) {
                    temp = RegExReplace(temp, "\\b" + Trim(keyWordElse) + "\\b", "} " + Trim(keyWordElse) + " {" + Chr(10));
                }
                else if (InStr(temp, " ->")) {
                    //;;;;;;;;;;;;
                    if (RegExMatch(Trim(StrSplit(temp, "->", 1)), "(?<!\\s)\\.\\.(?!\\s)") && InStr(Trim(StrSplit(temp, "->", 1)), " in ")) {
                        //print("DUBUGG1: " . A_LoopField)
                        temp1 = Trim(StrSplit(temp, "->", 1));
                        temp2 = Trim(StrSplit(temp, "->", 2));
                        // isWhenWhitVal
                        // preFixIfORelseIf
                        // whenStackSTR
                        whenStackSTR = Trim(StrSplit(temp1, " in ", 1));
                        temp1 = Trim(StrSplit(temp1, " in ", 2));
                        temp3 = Trim(StrSplit(temp1, "..", 1));
                        temp4 = Trim(StrSplit(temp1, "..", 2));
                        temp5 = whenStackSTR + " " + Trim(keyWordGreaterEqual) + " " + temp3 + " " + Trim(keyWordAnd) + " " + whenStackSTR + " " + Trim(keyWordLessEqual) + " " + temp4;
                        if (isWhenWhitVal == 0) {
                            temp1 = Trim(preFixIfORelseIf) + " (" + temp5 + ")";
                        } else {
                            temp1 = Trim(preFixIfORelseIf) + " (" + temp5 + ")";
                        }
                        temp = temp1 + " -> " + temp2;
                        temp = Trim(temp);
                    }
                    else if (RegExMatch(Trim(StrSplit(temp, "->", 1)), "(?<!\\s)\\.\\.(?!\\s)")) {
                        //print("DUBUGG2: " . A_LoopField)
                        temp1 = Trim(StrSplit(temp, "->", 1));
                        temp2 = Trim(StrSplit(temp, "->", 2));
                        // isWhenWhitVal
                        // preFixIfORelseIf
                        // whenStackSTR
                        temp3 = Trim(StrSplit(temp1, "..", 1));
                        temp4 = Trim(StrSplit(temp1, "..", 2));
                        temp5 = whenStackSTR + " " + Trim(keyWordGreaterEqual) + " " + temp3 + " " + Trim(keyWordAnd) + " " + whenStackSTR + " " + Trim(keyWordLessEqual) + " " + temp4;
                        if (isWhenWhitVal == 0) {
                            temp1 = Trim(preFixIfORelseIf) + " (ERROR YOU CANT DO .. IF NO when whit a val THEN YOU NEED TO use varName in num..num!!!)";
                        } else {
                            temp1 = Trim(preFixIfORelseIf) + " (" + temp5 + ")";
                        }
                        temp = temp1 + " -> " + temp2;
                        temp = Trim(temp);
                    }
                    else if (InStr(Trim(StrSplit(temp, "->", 1)), ",") && InStr(Trim(StrSplit(temp, "->", 1)), "(") == false && InStr(Trim(StrSplit(temp, "->", 1)), " in ")) {
                        //print("DUBUGG3: " . A_LoopField)
                        temp1 = Trim(StrSplit(temp, "->", 1));
                        temp2 = Trim(StrSplit(temp, "->", 2));
                        // isWhenWhitVal
                        // preFixIfORelseIf
                        // whenStackSTR
                        whenStackSTR = Trim(StrSplit(temp1, " in ", 1));
                        temp1 = Trim(StrSplit(temp1, " in ", 2));
                        // keyWordEqual
                        // keyWordOr
                        temp3 = "";
                        std::vector<std::string> items172 = LoopParseFunc(temp1, ",");
                        for (size_t A_Index172 = 0; A_Index172 < items172.size() + 0; A_Index172++) {
                            std::string A_LoopField172 = items172[A_Index172 - 0];
                            temp3 += whenStackSTR + " " + Trim(keyWordEqual) + " " + Trim(A_LoopField172) + " " + Trim(keyWordOr) + " ";
                        }
                        temp3 = Trim(temp3);
                        temp3 = Trim(StringTrimRight(temp3, StrLen(Trim(keyWordOr))));
                        if (isWhenWhitVal == 0) {
                            temp1 = Trim(preFixIfORelseIf) + " (" + temp3 + ")";
                        } else {
                            temp1 = Trim(preFixIfORelseIf) + " (" + temp3 + ")";
                        }
                        temp = temp1 + " -> " + temp2;
                        temp = Trim(temp);
                    }
                    else if (InStr(Trim(StrSplit(temp, "->", 1)), ",") && InStr(Trim(StrSplit(temp, "->", 1)), "(") == false) {
                        //print("DUBUGG4: " . A_LoopField)
                        temp1 = Trim(StrSplit(temp, "->", 1));
                        temp2 = Trim(StrSplit(temp, "->", 2));
                        // isWhenWhitVal
                        // preFixIfORelseIf
                        // whenStackSTR
                        // keyWordEqual
                        // keyWordOr
                        temp3 = "";
                        std::vector<std::string> items173 = LoopParseFunc(temp1, ",");
                        for (size_t A_Index173 = 0; A_Index173 < items173.size() + 0; A_Index173++) {
                            std::string A_LoopField173 = items173[A_Index173 - 0];
                            temp3 += whenStackSTR + " " + Trim(keyWordEqual) + " " + Trim(A_LoopField173) + " " + Trim(keyWordOr) + " ";
                        }
                        temp3 = Trim(temp3);
                        temp3 = Trim(StringTrimRight(temp3, StrLen(Trim(keyWordOr))));
                        if (isWhenWhitVal == 0) {
                            temp1 = Trim(preFixIfORelseIf) + " (ERROR YOU CANT DO THAT IF NO when whit a val THEN YOU NEED TO use varName in string, string, string, ... !!!)";
                        } else {
                            temp1 = Trim(preFixIfORelseIf) + " (" + temp3 + ")";
                        }
                        temp = temp1 + " -> " + temp2;
                        temp = Trim(temp);
                    } else {
                        //print("DUBUGG5: " . A_LoopField)
                        temp1 = Trim(StrSplit(temp, "->", 1));
                        temp2 = Trim(StrSplit(temp, "->", 2));
                        // isWhenWhitVal
                        // preFixIfORelseIf
                        // whenStackSTR
                        if (isWhenWhitVal == 0) {
                            temp1 = Trim(preFixIfORelseIf) + " (" + temp1 + ")";
                        } else {
                            temp1 = Trim(preFixIfORelseIf) + " (" + whenStackSTR + " " + Trim(keyWordEqual) + " " + temp1 + ")";
                        }
                        temp = temp1 + " -> " + temp2;
                        temp = Trim(temp);
                    }
                    //;;;;;;;;;;;;
                }
                if (firstUseIF_HELP == 0) {
                    if (Trim(temp) != "subout") {
                        if (InStr(temp, "->")) {
                            out += pading + "}" + Chr(10) + StrReplace(temp, "->", Chr(10) + "{" + Chr(10)) + Chr(10);
                        } else {
                            out += A_LoopField171 + Chr(10);
                        }
                    } else {
                        out += A_LoopField171 + Chr(10);
                    }
                } else {
                    if (InStr(temp, "->")) {
                        out += pading + StrReplace(temp, "->", Chr(10) + "{" + Chr(10)) + Chr(10);
                    } else {
                        out += A_LoopField171 + Chr(10);
                    }
                }
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            } else {
                if (RegExMatch(A_LoopField171, "\\b" + Trim(keyWordElse) + "\\b")) {
                    out += RegExReplace(A_LoopField171, "\\b" + Trim(keyWordElse) + "\\b", "} " + Trim(keyWordElse) + " {" + Chr(10)) + Chr(10);
                } else {
                    out += A_LoopField171 + Chr(10);
                }
            }
        } else {
            if (SubStr(Trim(A_LoopField171), 1, 5) != "when " && SubStr(Trim(A_LoopField171), 1, 5) != "wehn " && Trim(A_LoopField171) != "when" && Trim(A_LoopField171) != "wehn") {
                out += A_LoopField171 + Chr(10);
            }
        }
        if (SubStr(Trim(A_LoopField171), 1, 5) == "when " || SubStr(Trim(A_LoopField171), 1, 5) == "wehn " || Trim(A_LoopField171) == "when" || Trim(A_LoopField171) == "wehn") {
            if (SubStr(Trim(A_LoopField171), 1, 5) == "when " || SubStr(Trim(A_LoopField171), 1, 5) == "wehn ") {
                temp = Trim(A_LoopField171);
                temp = StringTrimLeft(temp, 5);
                temp = Trim(temp);
                HTVM_Append(whenStack, temp);
            } else {
                HTVM_Append(whenStack, "-=-NON-=-");
            }
            firstUseIF = 1;
            inWhen++;
        }
        if (Trim(A_LoopField171) == "subout" && inWhen != 0) {
            inWhen--;
            HTVM_Pop(whenStack);
        }
    }
    out = StringTrimRight(out, 1);
    theCode = out;
    out = "";
    std::vector<std::string> items174 = LoopParseFunc(theCode, "\n", "\r");
    for (size_t A_Index174 = 0; A_Index174 < items174.size() + 0; A_Index174++) {
        std::string A_LoopField174 = items174[A_Index174 - 0];
        if (Trim(A_LoopField174) == "subout") {
            out += "}" + Chr(10);
        } else {
            out += A_LoopField174 + Chr(10);
        }
    }
    out = StringTrimRight(out, 1);
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string formatHTVMtoHTVMsubout_HELP(std::string theCode, int padding) {
    std::string out = "";
    for (int A_Index175 = 0; A_Index175 < padding * 4 + 0; A_Index175++) {
        out += " ";
    }
    return out + theCode;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string formatHTVMtoHTVMsubout(std::string theCode) {
    std::string out = "";
    int inside = 0;
    std::vector<std::string> items176 = LoopParseFunc(theCode, "\n", "\r");
    for (size_t A_Index176 = 0; A_Index176 < items176.size() + 0; A_Index176++) {
        std::string A_LoopField176 = items176[A_Index176 - 0];
        if (Trim(A_LoopField176) == "subout") {
            inside--;
        }
        if (inside > 0) {
            out += formatHTVMtoHTVMsubout_HELP(A_LoopField176, inside) + Chr(10);
        } else {
            out += A_LoopField176 + Chr(10);
        }
        if (RegExMatch(A_LoopField176, "\\bwhen\\b") || RegExMatch(A_LoopField176, "\\bwehn\\b") || RegExMatch(Trim(A_LoopField176), "^\\s*[a-zA-Z_][a-zA-Z0-9_]*:\\s*$")) {
            inside++;
        }
    }
    out = StringTrimRight(out, 1);
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string fixIfElseIfMultiLineStatementHELP(std::string aloopfield) {
    std::string out = "";
    int count = 0;
    std::vector<std::string> items177 = LoopParseFunc(aloopfield);
    for (size_t A_Index177 = 0; A_Index177 < items177.size() + 0; A_Index177++) {
        std::string A_LoopField177 = items177[A_Index177 - 0];
        if (A_LoopField177 == "(") {
            count++;
        }
        if (A_LoopField177 == ")") {
            count--;
        }
    }
    if (count == 0) {
        return "w";
    } else {
        return "";
    }
    return out;
}
std::string fixIfElseIfMultiLineStatement(std::string someHTVMcode) {
    int doWeExitInsta = 1;
    std::vector<std::string> items178 = LoopParseFunc(someHTVMcode, "\n", "\r");
    for (size_t A_Index178 = 0; A_Index178 < items178.size() + 0; A_Index178++) {
        std::string A_LoopField178 = items178[A_Index178 - 0];
        if (SubStr(StrLower(Trim(A_LoopField178)), 1, StrLen(keyWordIF)) == keyWordIF) {
            doWeExitInsta = 0;
        }
        else if (SubStr(StrLower(Trim(A_LoopField178)), 1, StrLen(keyWordWhileLoop)) == keyWordWhileLoop) {
            doWeExitInsta = 0;
        }
        else if (SubStr(StrLower(Trim(A_LoopField178)), 1, StrLen(keyWordElseIf)) == keyWordElseIf) {
            doWeExitInsta = 0;
        }
    }
    if (doWeExitInsta == 1) {
        return someHTVMcode;
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    std::string out = "";
    std::string out2 = "";
    // this will make sure we exit once we dont have if else if while
    int doWeJustExit = 0;
    // this will make sure we exit once we dont fix the if else if while
    bool doWeExit = false;
    int doWeExitHELP = 0;
    out = someHTVMcode;
    // 10000 just in case the loop somehow becomes infinite
    for (int A_Index179 = 0; A_Index179 < 10000 + 0; A_Index179++) {
        out2 = out;
        out = "";
        doWeExit = false;
        std::vector<std::string> items180 = LoopParseFunc(out2, "\n", "\r");
        for (size_t A_Index180 = 0; A_Index180 < items180.size() + 0; A_Index180++) {
            std::string A_LoopField180 = items180[A_Index180 - 0];
            if (SubStr(StrLower(Trim(A_LoopField180)), 1, StrLen(keyWordIF)) == keyWordIF) {
                doWeJustExit = 1;
                if (fixIfElseIfMultiLineStatementHELP(A_LoopField180) == "") {
                    out += Trim(A_LoopField180) + " ";
                    doWeExit = false;
                    doWeExitHELP--;
                } else {
                    doWeExit = true;
                    out += Trim(A_LoopField180) + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField180)), 1, StrLen(keyWordWhileLoop)) == keyWordWhileLoop) {
                doWeJustExit = 1;
                if (fixIfElseIfMultiLineStatementHELP(A_LoopField180) == "") {
                    out += Trim(A_LoopField180) + " ";
                    doWeExit = false;
                    doWeExitHELP--;
                } else {
                    doWeExit = true;
                    out += Trim(A_LoopField180) + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField180)), 1, StrLen(keyWordElseIf)) == keyWordElseIf) {
                doWeJustExit = 1;
                if (fixIfElseIfMultiLineStatementHELP(A_LoopField180) == "") {
                    out += Trim(A_LoopField180) + " ";
                    doWeExit = false;
                    doWeExitHELP--;
                } else {
                    doWeExit = true;
                    out += Trim(A_LoopField180) + Chr(10);
                }
            } else {
                out += Trim(A_LoopField180) + Chr(10);
            }
        }
        out = StringTrimRight(out, 1);
        //print(A_Index)
        if (doWeJustExit == 0) {
            break;
        }
        if (doWeExit == true) {
            doWeExitHELP++;
            if (doWeExitHELP > 2) {
                break;
            }
        }
    }
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
bool doseHaveInclude(std::string TheCodeThatMightHaveInclude) {
    std::vector<std::string> items181 = LoopParseFunc(TheCodeThatMightHaveInclude, "\n", "\r");
    for (size_t A_Index181 = 0; A_Index181 < items181.size() + 0; A_Index181++) {
        std::string A_LoopField181 = items181[A_Index181 - 0];
        if (SubStr(StrLower(Trim(A_LoopField181)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ")) {
            return true;
        }
    }
    return false;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string compiler(std::string htCode, std::string allInstructionFile, std::string mode, std::string langToConvertToParam = "") {
    std::string instructions = allInstructionFile;
    std::vector<std::string> items182 = LoopParseFunc(allInstructionFile, "\n", "\r");
    for (size_t A_Index182 = 0; A_Index182 < items182.size() + 0; A_Index182++) {
        std::string A_LoopField182 = items182[A_Index182 - 0];
        if (A_Index182 == 0) {
            langToConvertTo = Trim(A_LoopField182);
        }
        if (A_Index182 == 1) {
            langFileExtension = Trim(A_LoopField182);
        }
        if (A_Index182 == 2) {
            commands = Trim(A_LoopField182);
        }
        if (A_Index182 == 3) {
            keyWordAlliance = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 4) {
            keyWordCrew = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 5) {
            keyWordProc = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 6) {
            keyWordStruct = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 7) {
            keyWordProp = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 8) {
            keyWordThis = Trim(A_LoopField182);
        }
        if (A_Index182 == 9) {
            keyWordInclude = Trim(A_LoopField182);
        }
        if (A_Index182 == 10) {
            keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField182);
        }
        if (A_Index182 == 11) {
            keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField182);
        }
        if (A_Index182 == 12) {
            keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField182);
        }
        if (A_Index182 == 13) {
            keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField182);
        }
        if (A_Index182 == 14) {
            keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField182);
        }
        if (A_Index182 == 15) {
            keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField182);
        }
        if (A_Index182 == 16) {
            keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField182);
        }
        if (A_Index182 == 17) {
            keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField182);
        }
        if (A_Index182 == 18) {
            keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField182);
        }
        if (A_Index182 == 19) {
            keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField182);
        }
        if (A_Index182 == 20) {
            keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField182);
        }
        if (A_Index182 == 21) {
            keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField182);
        }
        if (A_Index182 == 22) {
            keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField182);
        }
        if (A_Index182 == 23) {
            keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField182);
        }
        if (A_Index182 == 24) {
            keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField182);
        }
        if (A_Index182 == 25) {
            keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField182);
        }
        if (A_Index182 == 26) {
            keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField182);
        }
        if (A_Index182 == 27) {
            keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField182);
        }
        if (A_Index182 == 28) {
            keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField182);
        }
        if (A_Index182 == 29) {
            keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField182);
        }
        if (A_Index182 == 30) {
            keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField182);
        }
        if (A_Index182 == 31) {
            keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField182);
        }
        if (A_Index182 == 32) {
            keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField182);
        }
        if (A_Index182 == 33) {
            keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField182);
        }
        if (A_Index182 == 34) {
            keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField182);
        }
        if (A_Index182 == 35) {
            keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField182);
        }
        if (A_Index182 == 36) {
            keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField182);
        }
        if (A_Index182 == 37) {
            keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField182);
        }
        if (A_Index182 == 38) {
            keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField182);
        }
        if (A_Index182 == 39) {
            keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField182);
        }
        if (A_Index182 == 40) {
            keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField182);
        }
        if (A_Index182 == 41) {
            keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField182);
        }
        if (A_Index182 == 42) {
            keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField182);
        }
        if (A_Index182 == 43) {
            keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField182);
        }
        if (A_Index182 == 44) {
            keyWordCodeInHTVMstart = Trim(A_LoopField182);
        }
        if (A_Index182 == 45) {
            keyWordCodeInHTVMend = Trim(A_LoopField182);
        }
        if (A_Index182 == 46) {
            keyWordCurlyBraceOpen = Trim(A_LoopField182);
        }
        if (A_Index182 == 47) {
            keyWordCurlyBraceClose = Trim(A_LoopField182);
        }
        if (A_Index182 == 48) {
            keyWordNull = Trim(A_LoopField182);
        }
        if (A_Index182 == 49) {
            keyWordTrue = Trim(A_LoopField182);
        }
        if (A_Index182 == 50) {
            keyWordFalse = Trim(A_LoopField182);
        }
        if (A_Index182 == 51) {
            keyWordVoid = Trim(A_LoopField182);
        }
        if (A_Index182 == 52) {
            keyWordDouble = Trim(A_LoopField182);
        }
        if (A_Index182 == 53) {
            keyWordChar = Trim(A_LoopField182);
        }
        if (A_Index182 == 54) {
            keyWordUint8 = Trim(A_LoopField182);
        }
        if (A_Index182 == 55) {
            keyWordUint16 = Trim(A_LoopField182);
        }
        if (A_Index182 == 56) {
            keyWordUint32 = Trim(A_LoopField182);
        }
        if (A_Index182 == 57) {
            keyWordUint64 = Trim(A_LoopField182);
        }
        if (A_Index182 == 58) {
            keyWordINT = Trim(A_LoopField182);
        }
        if (A_Index182 == 59) {
            keyWordSTR = Trim(A_LoopField182);
        }
        if (A_Index182 == 60) {
            keyWordBOOL = Trim(A_LoopField182);
        }
        if (A_Index182 == 61) {
            keyWordFLOAT = Trim(A_LoopField182);
        }
        if (A_Index182 == 62) {
            keyWordINT8 = Trim(A_LoopField182);
        }
        if (A_Index182 == 63) {
            keyWordINT16 = Trim(A_LoopField182);
        }
        if (A_Index182 == 64) {
            keyWordINT32 = Trim(A_LoopField182);
        }
        if (A_Index182 == 65) {
            keyWordINT64 = Trim(A_LoopField182);
        }
        if (A_Index182 == 66) {
            keyWordIF = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 67) {
            keyWordElseIf = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 68) {
            keyWordElse = Trim(A_LoopField182);
        }
        if (A_Index182 == 69) {
            keyWordWhileLoop = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 70) {
            keyWordLoopInfinite = Trim(A_LoopField182);
        }
        if (A_Index182 == 71) {
            keyWordLoop = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 72) {
            keyWordLoopParse = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 73) {
            keyWordContinue = Trim(A_LoopField182);
        }
        if (A_Index182 == 74) {
            keyWordBreak = Trim(A_LoopField182);
        }
        if (A_Index182 == 75) {
            keyWordFunc = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 76) {
            keyWordAwait = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 77) {
            keyWordAsync = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 78) {
            keyWordThrow = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 79) {
            keyWordErrorMsg = Trim(A_LoopField182);
        }
        if (A_Index182 == 80) {
            keyWordTry = Trim(A_LoopField182);
        }
        if (A_Index182 == 81) {
            keyWordCatch = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 82) {
            keyWordFinally = Trim(A_LoopField182);
        }
        if (A_Index182 == 83) {
            keyWordReturnStatement = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 84) {
            keyWordArrayAppend = Trim(A_LoopField182);
        }
        if (A_Index182 == 85) {
            keyWordArrayPop = Trim(A_LoopField182);
        }
        if (A_Index182 == 86) {
            keyWordArraySize = Trim(A_LoopField182);
        }
        if (A_Index182 == 87) {
            keyWordArrayInsert = Trim(A_LoopField182);
        }
        if (A_Index182 == 88) {
            keyWordArrayRemove = Trim(A_LoopField182);
        }
        if (A_Index182 == 89) {
            keyWordArrayIndexOf = Trim(A_LoopField182);
        }
        if (A_Index182 == 90) {
            keyWordArrayDefinition = Trim(A_LoopField182);
        }
        if (A_Index182 == 91) {
            keyWordArrayOfIntegersDefinition = Trim(A_LoopField182);
        }
        if (A_Index182 == 92) {
            keyWordArrayOfStringsDefinition = Trim(A_LoopField182);
        }
        if (A_Index182 == 93) {
            keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField182);
        }
        if (A_Index182 == 94) {
            keyWordArrayOfBooleansDefinition = Trim(A_LoopField182);
        }
        if (A_Index182 == 95) {
            keyWordVar = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 96) {
            keyWordLet = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 97) {
            keyWordConst = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 98) {
            keyWordEnd = Trim(A_LoopField182);
        }
        if (A_Index182 == 99) {
            keyWordGlobal = Trim(A_LoopField182) + " ";
        }
        if (A_Index182 == 100) {
            keyWordComment = Trim(A_LoopField182);
        }
        if (A_Index182 == 101) {
            keyWordCommentOpenMultiLine = Trim(A_LoopField182);
        }
        if (A_Index182 == 102) {
            keyWordCommentCloseMultiLine = Trim(A_LoopField182);
        }
        if (A_Index182 == 103) {
            keyWordEscpaeChar = Trim(A_LoopField182);
        }
        if (A_Index182 == 104) {
            keyWordMainLabel = Trim(A_LoopField182);
        }
        if (A_Index182 == 105) {
            keyWordConcat = Trim(A_LoopField182);
        }
        if (A_Index182 == 106) {
            keyWordAdd = Trim(A_LoopField182);
        }
        if (A_Index182 == 107) {
            keyWordSub = Trim(A_LoopField182);
        }
        if (A_Index182 == 108) {
            keyWordMul = Trim(A_LoopField182);
        }
        if (A_Index182 == 109) {
            keyWordDiv = Trim(A_LoopField182);
        }
        if (A_Index182 == 110) {
            keyWordMod = Trim(A_LoopField182);
        }
        if (A_Index182 == 111) {
            keyWordExp = Trim(A_LoopField182);
        }
        if (A_Index182 == 112) {
            keyWordEqual = Trim(A_LoopField182);
        }
        if (A_Index182 == 113) {
            keyWordStrictEqual = Trim(A_LoopField182);
        }
        if (A_Index182 == 114) {
            keyWordNotEqual = Trim(A_LoopField182);
        }
        if (A_Index182 == 115) {
            keyWordGreater = Trim(A_LoopField182);
        }
        if (A_Index182 == 116) {
            keyWordLess = Trim(A_LoopField182);
        }
        if (A_Index182 == 117) {
            keyWordGreaterEqual = Trim(A_LoopField182);
        }
        if (A_Index182 == 118) {
            keyWordLessEqual = Trim(A_LoopField182);
        }
        if (A_Index182 == 119) {
            keyWordAnd = Trim(A_LoopField182);
        }
        if (A_Index182 == 120) {
            keyWordOr = Trim(A_LoopField182);
        }
        if (A_Index182 == 121) {
            keyWordNot = Trim(A_LoopField182);
        }
        if (A_Index182 == 122) {
            keyWordBitAnd = Trim(A_LoopField182);
        }
        if (A_Index182 == 123) {
            keyWordBitOr = Trim(A_LoopField182);
        }
        if (A_Index182 == 124) {
            keyWordBitXor = Trim(A_LoopField182);
        }
        if (A_Index182 == 125) {
            keyWordBitNot = Trim(A_LoopField182);
        }
        if (A_Index182 == 126) {
            keyWordShiftLeft = Trim(A_LoopField182);
        }
        if (A_Index182 == 127) {
            keyWordShiftRight = Trim(A_LoopField182);
        }
        if (A_Index182 == 128) {
            keyWordShiftUnsignedRight = Trim(A_LoopField182);
        }
        if (A_Index182 == 129) {
            keyWordAssign = Trim(A_LoopField182);
        }
        if (A_Index182 == 130) {
            keyWordAssignAdd = Trim(A_LoopField182);
        }
        if (A_Index182 == 131) {
            keyWordAssignConcat = Trim(A_LoopField182);
        }
        if (A_Index182 == 132) {
            keyWordAssignSub = Trim(A_LoopField182);
        }
        if (A_Index182 == 133) {
            keyWordAssignMul = Trim(A_LoopField182);
        }
        if (A_Index182 == 134) {
            keyWordAssignDiv = Trim(A_LoopField182);
        }
        if (A_Index182 == 135) {
            keyWordAssignMod = Trim(A_LoopField182);
        }
        if (A_Index182 == 136) {
            keyWordAssignShiftLeft = Trim(A_LoopField182);
        }
        if (A_Index182 == 137) {
            keyWordAssignShiftRight = Trim(A_LoopField182);
        }
        if (A_Index182 == 138) {
            keyWordLogicalAssignShiftRight = Trim(A_LoopField182);
        }
        if (A_Index182 == 139) {
            keyWordAssignBitAnd = Trim(A_LoopField182);
        }
        if (A_Index182 == 140) {
            keyWordAssignBitOr = Trim(A_LoopField182);
        }
        if (A_Index182 == 141) {
            keyWordAssignBitXor = Trim(A_LoopField182);
        }
        if (A_Index182 == 142) {
            keyWordTernary1 = Trim(A_LoopField182);
        }
        if (A_Index182 == 143) {
            keyWordTernary2 = Trim(A_LoopField182);
        }
        if (A_Index182 == 144) {
            keyWordInc = Trim(A_LoopField182);
        }
        if (A_Index182 == 145) {
            keyWordDec = Trim(A_LoopField182);
        }
        if (A_Index182 == 146) {
            AHKlikeLoopsIndexedAt = Trim(A_LoopField182);
        }
        if (A_Index182 == 147) {
            keyWordAIndex = Trim(A_LoopField182);
        }
        if (A_Index182 == 148) {
            keyWordALoopField = Trim(A_LoopField182);
        }
        if (A_Index182 == 149) {
            useCurlyBraces = Trim(A_LoopField182);
        }
        if (A_Index182 == 150) {
            useEnd = Trim(A_LoopField182);
        }
        if (A_Index182 == 151) {
            useSemicolon = Trim(A_LoopField182);
        }
        if (A_Index182 == 152) {
            useParentheses = Trim(A_LoopField182);
        }
        if (A_Index182 == 153) {
            usePrefixTypeForTypeDefinition = Trim(A_LoopField182);
        }
        if (A_Index182 == 154) {
            usePostfixTypeForTypeDefinition = Trim(A_LoopField182);
        }
        if (A_Index182 == 155) {
            usePythonicColonSyntax = Trim(A_LoopField182);
        }
        if (A_Index182 == 156) {
            useCurlyBracesSyntaxForArrayDef = Trim(A_LoopField182);
        }
        if (A_Index182 == 157) {
            useInJavaScriptAlwaysUseVar = Trim(A_LoopField182);
        }
        if (A_Index182 == 158) {
            useJavaScriptInAfullHTMLfile = Trim(A_LoopField182);
        }
        if (A_Index182 == 159) {
            useJavaScriptAmainFuncDef = Trim(A_LoopField182);
        }
        if (A_Index182 == 160) {
            useJavaScriptAllFuncsAreAsync = Trim(A_LoopField182);
        }
        if (A_Index182 == 161) {
            useJavaScriptAlwaysTripleEqual = Trim(A_LoopField182);
        }
    }
    if (HTVM_Size(argHTVMinstrMORE) > 0) {
        std::string allInstructionFile_2 = "";
        if (HTVM_getLang_HTVM() == "js") {
            allInstructionFile_2 = Trim(argHTVMinstrMORE[0]);
        } else {
            allInstructionFile_2 = Trim(FileRead(Trim(argHTVMinstrMORE[0])));
        }
        std::vector<std::string> items183 = LoopParseFunc(allInstructionFile_2, "\n", "\r");
        for (size_t A_Index183 = 0; A_Index183 < items183.size() + 0; A_Index183++) {
            std::string A_LoopField183 = items183[A_Index183 - 0];
            if (A_Index183 == 0) {
                langToConvertTo_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 1) {
                langFileExtension_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 2) {
                commands_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 3) {
                keyWordAlliance_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 4) {
                keyWordCrew_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 5) {
                keyWordProc_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 6) {
                keyWordStruct_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 7) {
                keyWordProp_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 8) {
                keyWordThis_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 9) {
                keyWordInclude_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 10) {
                keyWordCodeInTheTranspiledLangStart_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 11) {
                keyWordCodeInTheTranspiledLangEnd_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 12) {
                keyWordCodeInTheTranspiledLangStartCPP_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 13) {
                keyWordCodeInTheTranspiledLangEndCPP_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 14) {
                keyWordCodeInTheTranspiledLangStartPY_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 15) {
                keyWordCodeInTheTranspiledLangEndPY_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 16) {
                keyWordCodeInTheTranspiledLangStartJS_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 17) {
                keyWordCodeInTheTranspiledLangEndJS_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 18) {
                keyWordCodeInTheTranspiledLangStartGO_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 19) {
                keyWordCodeInTheTranspiledLangEndGO_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 20) {
                keyWordCodeInTheTranspiledLangStartLUA_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 21) {
                keyWordCodeInTheTranspiledLangEndLUA_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 22) {
                keyWordCodeInTheTranspiledLangStartCS_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 23) {
                keyWordCodeInTheTranspiledLangEndCS_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 24) {
                keyWordCodeInTheTranspiledLangStartJAVA_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 25) {
                keyWordCodeInTheTranspiledLangEndJAVA_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 26) {
                keyWordCodeInTheTranspiledLangStartKT_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 27) {
                keyWordCodeInTheTranspiledLangEndKT_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 28) {
                keyWordCodeInTheTranspiledLangStartRB_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 29) {
                keyWordCodeInTheTranspiledLangEndRB_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 30) {
                keyWordCodeInTheTranspiledLangStartNIM_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 31) {
                keyWordCodeInTheTranspiledLangEndNIM_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 32) {
                keyWordCodeInTheTranspiledLangStartAHK_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 33) {
                keyWordCodeInTheTranspiledLangEndAHK_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 34) {
                keyWordCodeInTheTranspiledLangStartSWIFT_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 35) {
                keyWordCodeInTheTranspiledLangEndSWIFT_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 36) {
                keyWordCodeInTheTranspiledLangStartDART_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 37) {
                keyWordCodeInTheTranspiledLangEndDART_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 38) {
                keyWordCodeInTheTranspiledLangStartTS_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 39) {
                keyWordCodeInTheTranspiledLangEndTS_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 40) {
                keyWordCodeInTheTranspiledLangStartGROOVY_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 41) {
                keyWordCodeInTheTranspiledLangEndGROOVY_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 42) {
                keyWordCodeInTheTranspiledLangStartHTVM_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 43) {
                keyWordCodeInTheTranspiledLangEndHTVM_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 44) {
                keyWordCodeInHTVMstart_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 45) {
                keyWordCodeInHTVMend_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 46) {
                keyWordCurlyBraceOpen_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 47) {
                keyWordCurlyBraceClose_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 48) {
                keyWordNull_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 49) {
                keyWordTrue_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 50) {
                keyWordFalse_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 51) {
                keyWordVoid_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 52) {
                keyWordDouble_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 53) {
                keyWordChar_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 54) {
                keyWordUint8_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 55) {
                keyWordUint16_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 56) {
                keyWordUint32_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 57) {
                keyWordUint64_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 58) {
                keyWordINT_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 59) {
                keyWordSTR_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 60) {
                keyWordBOOL_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 61) {
                keyWordFLOAT_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 62) {
                keyWordINT8_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 63) {
                keyWordINT16_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 64) {
                keyWordINT32_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 65) {
                keyWordINT64_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 66) {
                keyWordIF_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 67) {
                keyWordElseIf_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 68) {
                keyWordElse_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 69) {
                keyWordWhileLoop_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 70) {
                keyWordLoopInfinite_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 71) {
                keyWordLoop_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 72) {
                keyWordLoopParse_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 73) {
                keyWordContinue_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 74) {
                keyWordBreak_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 75) {
                keyWordFunc_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 76) {
                keyWordAwait_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 77) {
                keyWordAsync_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 78) {
                keyWordThrow_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 79) {
                keyWordErrorMsg_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 80) {
                keyWordTry_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 81) {
                keyWordCatch_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 82) {
                keyWordFinally_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 83) {
                keyWordReturnStatement_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 84) {
                keyWordArrayAppend_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 85) {
                keyWordArrayPop_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 86) {
                keyWordArraySize_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 87) {
                keyWordArrayInsert_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 88) {
                keyWordArrayRemove_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 89) {
                keyWordArrayIndexOf_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 90) {
                keyWordArrayDefinition_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 91) {
                keyWordArrayOfIntegersDefinition_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 92) {
                keyWordArrayOfStringsDefinition_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 93) {
                keyWordArrayOfFloatingPointNumbersDefinition_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 94) {
                keyWordArrayOfBooleansDefinition_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 95) {
                keyWordVar_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 96) {
                keyWordLet_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 97) {
                keyWordConst_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 98) {
                keyWordEnd_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 99) {
                keyWordGlobal_2 = Trim(A_LoopField183) + " ";
            }
            if (A_Index183 == 100) {
                keyWordComment_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 101) {
                keyWordCommentOpenMultiLine_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 102) {
                keyWordCommentCloseMultiLine_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 103) {
                keyWordEscpaeChar_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 104) {
                keyWordMainLabel_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 105) {
                keyWordConcat_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 106) {
                keyWordAdd_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 107) {
                keyWordSub_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 108) {
                keyWordMul_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 109) {
                keyWordDiv_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 110) {
                keyWordMod_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 111) {
                keyWordExp_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 112) {
                keyWordEqual_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 113) {
                keyWordStrictEqual_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 114) {
                keyWordNotEqual_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 115) {
                keyWordGreater_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 116) {
                keyWordLess_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 117) {
                keyWordGreaterEqual_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 118) {
                keyWordLessEqual_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 119) {
                keyWordAnd_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 120) {
                keyWordOr_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 121) {
                keyWordNot_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 122) {
                keyWordBitAnd_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 123) {
                keyWordBitOr_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 124) {
                keyWordBitXor_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 125) {
                keyWordBitNot_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 126) {
                keyWordShiftLeft_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 127) {
                keyWordShiftRight_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 128) {
                keyWordShiftUnsignedRight_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 129) {
                keyWordAssign_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 130) {
                keyWordAssignAdd_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 131) {
                keyWordAssignConcat_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 132) {
                keyWordAssignSub_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 133) {
                keyWordAssignMul_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 134) {
                keyWordAssignDiv_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 135) {
                keyWordAssignMod_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 136) {
                keyWordAssignShiftLeft_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 137) {
                keyWordAssignShiftRight_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 138) {
                keyWordLogicalAssignShiftRight_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 139) {
                keyWordAssignBitAnd_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 140) {
                keyWordAssignBitOr_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 141) {
                keyWordAssignBitXor_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 142) {
                keyWordTernary1_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 143) {
                keyWordTernary2_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 144) {
                keyWordInc_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 145) {
                keyWordDec_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 146) {
                AHKlikeLoopsIndexedAt_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 147) {
                keyWordAIndex_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 148) {
                keyWordALoopField_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 149) {
                useCurlyBraces_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 150) {
                useEnd_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 151) {
                useSemicolon_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 152) {
                useParentheses_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 153) {
                usePrefixTypeForTypeDefinition_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 154) {
                usePostfixTypeForTypeDefinition_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 155) {
                usePythonicColonSyntax_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 156) {
                useCurlyBracesSyntaxForArrayDef_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 157) {
                useInJavaScriptAlwaysUseVar_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 158) {
                useJavaScriptInAfullHTMLfile_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 159) {
                useJavaScriptAmainFuncDef_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 160) {
                useJavaScriptAllFuncsAreAsync_2 = Trim(A_LoopField183);
            }
            if (A_Index183 == 161) {
                useJavaScriptAlwaysTripleEqual_2 = Trim(A_LoopField183);
            }
        }
    }
    if (Trim(langToConvertToParam) != "") {
        langToConvertTo = Trim(langToConvertToParam);
    }
    int isFullHTVMCode = 0;
    int isNotHTVMfile = 0;
    if (Trim(mode) == "full") {
        isFullHTVMCode = 1;
    } else {
        isFullHTVMCode = 0;
    }
    if (Trim(mode) == "notHTVM") {
        isNotHTVMfile = 1;
    } else {
        isNotHTVMfile = 0;
    }
    if (useEnd == "on") {
        keyWordCurlyBraceOpen = "{";
        keyWordCurlyBraceClose = "}";
    }
    if (useEnd_2 == "on") {
        keyWordCurlyBraceOpen_2 = "{";
        keyWordCurlyBraceClose_2 = "}";
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    /*
    if (langToConvertTo == langFileExtension_2) {
    }
    if (langToConvertTo == "cpp") {
    }
    if (langToConvertTo == "py") {
    }
    if (langToConvertTo == "js") {
    }
    if (langToConvertTo == "go") {
    }
    if (langToConvertTo == "lua") {
    }
    if (langToConvertTo == "cs") {
    }
    if (langToConvertTo == "java") {
    }
    if (langToConvertTo == "kt") {
    }
    if (langToConvertTo == "rb") {
    }
    if (langToConvertTo == "nim") {
    }
    if (langToConvertTo == "ahk") {
    }
    if (langToConvertTo == "swift") {
    }
    if (langToConvertTo == "dart") {
    }
    if (langToConvertTo == "ts") {
    }
    if (langToConvertTo == "groovy") {
    }
    */
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    std::string HTVMout = "";
    htCode = Trim(StrReplace(htCode, Chr(13), ""));
    std::string code = "";
    //print(htCode)
    code = htCode;
    //print(mode)
    //print(langToConvertTo)
    //print("==================================")
    //print("==================================")
    //print("==================================")
    //print("==================================")
    //print("==================================")
    //print(allInstructionFile)
    if (langToConvertTo == "rb") {
        keyWordAIndexOriginal = keyWordAIndex;
        keyWordALoopFieldOriginal = keyWordALoopField;
        keyWordAIndex = StrLower(keyWordAIndex);
        keyWordALoopField = StrLower(keyWordALoopField);
    }
    availableFuncsInHTVMInHTVM = "";
    std::vector<std::string> items184 = LoopParseFunc(allInstructionFile, "\n", "\r");
    for (size_t A_Index184 = 0; A_Index184 < items184.size() + 0; A_Index184++) {
        std::string A_LoopField184 = items184[A_Index184 - 0];
        if (RegExMatch(Trim(A_LoopField184), "^name: [A-Za-z0-9_]+")) {
            availableFuncsInHTVMInHTVM += Trim(StrSplit(Trim(A_LoopField184), "name: ", 2)) + Chr(10);
        }
    }
    int haveWeEverUsedAloop = 0;
    int lineDone = 0;
    std::string var1 = "";
    std::string nothing = "";
    int AindexcharLength = 1;
    std::string AindexcharLengthStr = "";
    std::string theFixTextLoopNL = "";
    int htCodeAcurlyBraceAddSomeVrasFixNL = 0;
    std::string htCodeLoopfixa = "";
    std::string htCodeLoopfixa1 = "";
    std::string str123 = "";
    std::string out2 = "";
    std::string myVar = "";
    std::string lineYGI = "";
    std::string line = "";
    std::string line1 = "";
    std::string line2 = "";
    std::string line3 = "";
    std::string itemsOut = "";
    std::string var1out = "";
    std::string theFixTextLoopLP = "";
    int htCodeAcurlyBraceAddSomeVrasFixLP = 0;
    int AIndexLoopCurlyFix = 0;
    std::string sstr123 = "";
    std::string fixLoopLokingFor = "";
    int fixLoopLokingForfound = 0;
    std::string out1 = "";
    int wasAtanyIfsElseAddAIndexLoopCurlyFix = 0;
    int inTarget = 0;
    int insideBracket = 0;
    int netsedCurly = 0;
    int eldLoopNestedBADlol = 0;
    int readyToEnd = 0;
    int endBracketDOntPutThere = 0;
    int dontSaveStr = 0;
    int weAreDoneHereCurly = 0;
    int DeleayOneCuzOfLoopParse = 0;
    int fixLoopLokingForNum = 0;
    int insdeAnestedLoopBAD = 0;
    int foundTheTopLoop = 0;
    std::string out4758686d86d86d86578991a = "";
    std::string ALoopField = "";
    std::string out1z = "";
    int insideBracket1 = 0;
    int netsedCurly1 = 0;
    int readyToEnd1 = 0;
    std::string strstysrstsytTRIMHELP = "";
    std::string out4758686d86dgt8r754444444 = "";
    int hold = 0;
    std::string holdText = "";
    int ignore = 0;
    std::string htCodeOut1234565432 = "";
    std::string out = "";
    std::string s = "";
    int skipLeftCuleyForFuncPLS = 0;
    std::string strOspHold = "";
    if (isNotHTVMfile == 0) {
        code = handleMultiLineStrings(code);
    }
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    int COUNT_programmingBlock_InTheTranspiledLang = 0;
    int COUNT_programmingBlock_CPP = 0;
    int COUNT_programmingBlock_PY = 0;
    int COUNT_programmingBlock_JS = 0;
    int COUNT_programmingBlock_GO = 0;
    int COUNT_programmingBlock_LUA = 0;
    int COUNT_programmingBlock_CS = 0;
    int COUNT_programmingBlock_JAVA = 0;
    int COUNT_programmingBlock_KT = 0;
    int COUNT_programmingBlock_RB = 0;
    int COUNT_programmingBlock_NIM = 0;
    int COUNT_programmingBlock_AHK = 0;
    int COUNT_programmingBlock_SWIFT = 0;
    int COUNT_programmingBlock_DART = 0;
    int COUNT_programmingBlock_TS = 0;
    int COUNT_programmingBlock_GROOVY = 0;
    int COUNT_programmingBlock_HTVM = 0;
    int COUNT_programmingBlock_HTVMsyntax = 0;
    std::string programmingBlocksTemp = "";
    int inProgarmmingBlock = 0;
    std::string holdTempDataProgrammingBlockThenPutInArr = "";
    std::vector<std::string> items185 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index185 = 0; A_Index185 < items185.size() + 0; A_Index185++) {
        std::string A_LoopField185 = items185[A_Index185 - 0];
        if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEnd)) {
            COUNT_programmingBlock_InTheTranspiledLang++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(COUNT_programmingBlock_InTheTranspiledLang) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_InTheTranspiledLang, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndCPP)) {
            COUNT_programmingBlock_CPP++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(COUNT_programmingBlock_CPP) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_CPP, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndPY)) {
            COUNT_programmingBlock_PY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_PY-programmingBlock_PY-AA" + STR(COUNT_programmingBlock_PY) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_PY, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndJS)) {
            COUNT_programmingBlock_JS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JS-programmingBlock_JS-AA" + STR(COUNT_programmingBlock_JS) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_JS, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndGO)) {
            COUNT_programmingBlock_GO++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GO-programmingBlock_GO-AA" + STR(COUNT_programmingBlock_GO) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_GO, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndLUA)) {
            COUNT_programmingBlock_LUA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(COUNT_programmingBlock_LUA) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_LUA, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndCS)) {
            COUNT_programmingBlock_CS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CS-programmingBlock_CS-AA" + STR(COUNT_programmingBlock_CS) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_CS, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndJAVA)) {
            COUNT_programmingBlock_JAVA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(COUNT_programmingBlock_JAVA) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_JAVA, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndKT)) {
            COUNT_programmingBlock_KT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_KT-programmingBlock_KT-AA" + STR(COUNT_programmingBlock_KT) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_KT, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndRB)) {
            COUNT_programmingBlock_RB++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_RB-programmingBlock_RB-AA" + STR(COUNT_programmingBlock_RB) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_RB, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndNIM)) {
            COUNT_programmingBlock_NIM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(COUNT_programmingBlock_NIM) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_NIM, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndAHK)) {
            COUNT_programmingBlock_AHK++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(COUNT_programmingBlock_AHK) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_AHK, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndSWIFT)) {
            COUNT_programmingBlock_SWIFT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(COUNT_programmingBlock_SWIFT) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_SWIFT, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndDART)) {
            COUNT_programmingBlock_DART++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_DART-programmingBlock_DART-AA" + STR(COUNT_programmingBlock_DART) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_DART, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndTS)) {
            COUNT_programmingBlock_TS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_TS-programmingBlock_TS-AA" + STR(COUNT_programmingBlock_TS) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_TS, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndGROOVY)) {
            COUNT_programmingBlock_GROOVY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(COUNT_programmingBlock_GROOVY) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_GROOVY, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangEndHTVM)) {
            COUNT_programmingBlock_HTVM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(COUNT_programmingBlock_HTVM) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_HTVM, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInHTVMend)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            COUNT_programmingBlock_HTVMsyntax++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(COUNT_programmingBlock_HTVMsyntax) + "AA" + Chr(10);
            HTVM_Append(programmingBlock_HTVMsyntax, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        }
        else if (inProgarmmingBlock == 1) {
            holdTempDataProgrammingBlockThenPutInArr += A_LoopField185 + Chr(10);
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStart)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartCPP)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartPY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartJS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartGO)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartLUA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartCS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartJAVA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartKT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartRB)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartNIM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartAHK)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartSWIFT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartDART)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartTS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartGROOVY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInTheTranspiledLangStartHTVM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField185)) == StrLower(keyWordCodeInHTVMstart)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        } else {
            programmingBlocksTemp += A_LoopField185 + Chr(10);
        }
    }
    code = StringTrimRight(programmingBlocksTemp, 1);
    //programmingBlock_InTheTranspiledLang
    //programmingBlock_CPP
    //programmingBlock_PY
    //programmingBlock_JS
    //programmingBlock_GO
    //programmingBlock_LUA
    //programmingBlock_CS
    //programmingBlock_JAVA
    //programmingBlock_KT
    //programmingBlock_RB
    //programmingBlock_NIM
    //programmingBlock_AHK
    //programmingBlock_SWIFT
    //programmingBlock_DART
    //programmingBlock_TS
    //programmingBlock_GROOVY
    //programmingBlock_HTVM
    //programmingBlock_HTVMsyntax
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // keyWordInclude
    // keyWordInclude
    // keyWordInclude
    // --- HTVM Include Directive Processor ---
    //
    // This script processes 'include' directives by replacing them with the content of the specified files.
    // It handles nested includes and prevents the same file from being included multiple times.
    // All variables are declared at the top for scope safety and clarity.
    // The main logic is wrapped in an IF block to avoid running unnecessarily.
    // =========================================================================================
    // Welcome!
    // --- Variable Declarations ---
    // All variables used in this script are declared upfront.
    std::vector<std::string> includedFilePaths;
    bool includesWereFoundInPass = false;
    std::string reconstructedCode = "";
    std::string currentLine = "";
    std::string filePathToInclude = "";
    bool isAlreadyIncluded = false;
    std::string fileContent = "";
    if (isNotHTVMfile == 0) {
        if (langToConvertTo != langFileExtension_2) {
            // --- Main Processing Logic ---
            // Optimization: Only run the complex processing logic IF the 'include' keyword exists in the code.
            // This avoids a 'return' and simply skips the block if it's not needed.
            if (doseHaveInclude(code)) {
                // Loop up to 10000 times to resolve nested includes. Each pass processes one level of includes.
                for (int A_Index186 = 0; A_Index186 < 10000 + 0; A_Index186++) {
                    // Reset the flag and the temporary code string for this pass.
                    includesWereFoundInPass = false;
                    reconstructedCode = "";
                    // Iterate through each line of the current code.
                    std::vector<std::string> items187 = LoopParseFunc(code, "\n", "\r");
                    for (size_t A_Index187 = 0; A_Index187 < items187.size() + 0; A_Index187++) {
                        std::string A_LoopField187 = items187[A_Index187 - 0];
                        currentLine = A_LoopField187;
                        // Check if the current line is an 'include' directive.
                        if (SubStr(StrLower(Trim(currentLine)), 1, StrLen(keyWordInclude + " ")) == StrLower(keyWordInclude + " ")) {
                            includesWereFoundInPass = true;
                            filePathToInclude = StrReplace(StringTrimLeft(Trim(currentLine), StrLen(keyWordInclude + " ")), Chr(34), "");
                            // Reset flag for the inner loop.
                            isAlreadyIncluded = false;
                            // NOTE: Both this loop's A_Index and the array access are 0-based, which is correct.
                            for (int A_Index188 = 0; A_Index188 < HTVM_Size(includedFilePaths) + 0; A_Index188++) {
                                if (filePathToInclude == includedFilePaths[A_Index188]) {
                                    isAlreadyIncluded = true;
                                    break;
                                }
                            }
                            if (isAlreadyIncluded == false) {
                                fileContent = Trim(FileRead(filePathToInclude));
                                // The 'include' line is replaced by the file's content in the reconstructed code.
                                reconstructedCode = reconstructedCode + Chr(10) + keyWordComment + " start of " + filePathToInclude + Chr(10) + fileContent + Chr(10) + keyWordComment + " end of " + filePathToInclude + Chr(10) + Chr(10);
                                HTVM_Append(includedFilePaths, filePathToInclude);
                            }
                        } else {
                            // If it's not an include directive, just copy the line as is.
                            reconstructedCode = reconstructedCode + currentLine + Chr(10);
                        }
                    }
                    // --- Cleanup and Preparation for Next Pass ---
                    // Replace the old code with the newly reconstructed code. This "clears up" the processed includes.
                    code = reconstructedCode;
                    // If no includes were found in this entire pass, all directives are resolved. Exit the loop.
                    if (includesWereFoundInPass == false) {
                        break;
                    }
                }
            }
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        programmingBlocksTemp = "";
        inProgarmmingBlock = 0;
        holdTempDataProgrammingBlockThenPutInArr = "";
        std::vector<std::string> items189 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index189 = 0; A_Index189 < items189.size() + 0; A_Index189++) {
            std::string A_LoopField189 = items189[A_Index189 - 0];
            if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEnd)) {
                COUNT_programmingBlock_InTheTranspiledLang++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(COUNT_programmingBlock_InTheTranspiledLang) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_InTheTranspiledLang, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndCPP)) {
                COUNT_programmingBlock_CPP++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(COUNT_programmingBlock_CPP) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_CPP, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndPY)) {
                COUNT_programmingBlock_PY++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_PY-programmingBlock_PY-AA" + STR(COUNT_programmingBlock_PY) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_PY, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndJS)) {
                COUNT_programmingBlock_JS++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_JS-programmingBlock_JS-AA" + STR(COUNT_programmingBlock_JS) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_JS, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndGO)) {
                COUNT_programmingBlock_GO++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_GO-programmingBlock_GO-AA" + STR(COUNT_programmingBlock_GO) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_GO, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndLUA)) {
                COUNT_programmingBlock_LUA++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(COUNT_programmingBlock_LUA) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_LUA, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndCS)) {
                COUNT_programmingBlock_CS++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_CS-programmingBlock_CS-AA" + STR(COUNT_programmingBlock_CS) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_CS, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndJAVA)) {
                COUNT_programmingBlock_JAVA++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(COUNT_programmingBlock_JAVA) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_JAVA, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndKT)) {
                COUNT_programmingBlock_KT++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_KT-programmingBlock_KT-AA" + STR(COUNT_programmingBlock_KT) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_KT, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndRB)) {
                COUNT_programmingBlock_RB++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_RB-programmingBlock_RB-AA" + STR(COUNT_programmingBlock_RB) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_RB, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndNIM)) {
                COUNT_programmingBlock_NIM++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(COUNT_programmingBlock_NIM) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_NIM, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndAHK)) {
                COUNT_programmingBlock_AHK++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(COUNT_programmingBlock_AHK) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_AHK, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndSWIFT)) {
                COUNT_programmingBlock_SWIFT++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(COUNT_programmingBlock_SWIFT) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_SWIFT, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndDART)) {
                COUNT_programmingBlock_DART++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_DART-programmingBlock_DART-AA" + STR(COUNT_programmingBlock_DART) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_DART, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndTS)) {
                COUNT_programmingBlock_TS++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_TS-programmingBlock_TS-AA" + STR(COUNT_programmingBlock_TS) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_TS, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndGROOVY)) {
                COUNT_programmingBlock_GROOVY++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(COUNT_programmingBlock_GROOVY) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_GROOVY, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangEndHTVM)) {
                COUNT_programmingBlock_HTVM++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(COUNT_programmingBlock_HTVM) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_HTVM, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInHTVMend)) {
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                COUNT_programmingBlock_HTVMsyntax++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(COUNT_programmingBlock_HTVMsyntax) + "AA" + Chr(10);
                HTVM_Append(programmingBlock_HTVMsyntax, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            }
            else if (inProgarmmingBlock == 1) {
                holdTempDataProgrammingBlockThenPutInArr += A_LoopField189 + Chr(10);
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStart)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartCPP)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartPY)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartJS)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartGO)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartLUA)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartCS)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartJAVA)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartKT)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartRB)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartNIM)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartAHK)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartSWIFT)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartDART)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartTS)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartGROOVY)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInTheTranspiledLangStartHTVM)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField189)) == StrLower(keyWordCodeInHTVMstart)) {
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            } else {
                programmingBlocksTemp += A_LoopField189 + Chr(10);
            }
        }
        code = StringTrimRight(programmingBlocksTemp, 1);
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
    }
    // keyWordInclude
    // keyWordInclude
    // keyWordInclude
    std::vector<std::string> lookIntoTheNextLineForFuncWhitNoKeyWord;
    int didWeUseMainLabel = 0;
    std::string codeOutFixAndAddMainFunc = "";
    std::string htCodeOutFixEnd = "";
    int htCodeOutFixINT = 0;
    int htCodeOutFixINT2 = 0;
    std::string beforeKeywordForRemoveCommentsOnTheEndOfTheLine = "";
    std::string newStringOutCode = "";
    int posForRemoveCommentsOnTheEndOfTheLine = 0;
    std::string originalStringForRemoveCommentsOnTheEndOfTheLine = "";
    std::string OutFixDoubleQuotesInsideDoubleQuotes = "";
    int fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
    std::string htCodeOUT754754 = "";
    int areWEinSome34sNum = 0;
    int theIdNumOfThe34 = 0;
    std::vector<std::string> slidingWinFixCommentsRm;
    std::string slidingWinFixCommentsRmHold = "";
    int slidingWinFixCommentsRmI = 0;
    std::string fixSomeOSPbigHTVMtoHTVM = "";
    std::vector<std::string> theIdNumOfThe34theVar;
    std::vector<std::string> theIdNumOfThe34theVarFIX;
    std::string ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = "";
    std::vector<std::string> getAllCharForTheFurtureSoIcanAddEscapeChar;
    int removeNexFixkeyWordEscpaeChar = 0;
    std::string fixSomeCurlyBraceForExratFlexability = "";
    std::string fixSomeCurlyBraceForExratFlexabilityTriHELP = "";
    std::string semiColonForOneLinerOut = "";
    std::string addNoCurlyFixWhenNextLineAfterConstructOut = "";
    std::vector<std::string> addNoCurlyFixWhenNextLineAfterConstructLookAhead;
    //;;;;;;;;;;;;;;;;;;;
    std::vector<std::string> commentsBugFix;
    std::string commentsBugFixHold = "";
    std::string commentsBugFixHold1 = "";
    std::string commentsBugFixHold2 = "";
    int commentsBugFixHelpInt = 0;
    std::string commentsBugFixOut = "";
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    if (isNotHTVMfile == 0) {
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        std::vector<std::string> items190 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index190 = 0; A_Index190 < items190.size() + 0; A_Index190++) {
            std::string A_LoopField190 = items190[A_Index190 - 0];
            if (SubStr(Trim(A_LoopField190), 1, StrLen(keyWordComment)) == keyWordComment) {
                commentsBugFixHold = StringTrimLeft(Trim(A_LoopField190), StrLen(keyWordComment));
                std::vector<std::string> items191 = LoopParseFunc(A_LoopField190);
                for (size_t A_Index191 = 0; A_Index191 < items191.size() + 0; A_Index191++) {
                    std::string A_LoopField191 = items191[A_Index191 - 0];
                    if (InStr(A_LoopField191, " ") || InStr(A_LoopField191, Chr(9))) {
                        commentsBugFixHold1 = A_LoopField191;
                    } else {
                        break;
                    }
                }
                HTVM_Append(commentsBugFix, commentsBugFixHold);
                commentsBugFixHold2 = "HTVM--cnavisdofbuvsesdivdidufg79wregwewaeosd8ges7dfdftuawdiHTVMv2yerheyziberlasduci6syiq--AA" + STR(commentsBugFixHelpInt) + "AA";
                commentsBugFixHelpInt++;
                commentsBugFixOut += commentsBugFixHold1 + keyWordComment + commentsBugFixHold2 + Chr(10);
            } else {
                commentsBugFixOut += A_LoopField190 + Chr(10);
            }
        }
        code = StringTrimRight(commentsBugFixOut, 1);
        //print("============programmingBlock_CPP==================")
        //print("============programmingBlock_CPP==================")
        //print("============programmingBlock_CPP==================")
        //print("============programmingBlock_CPP==================")
        std::vector<std::string> items192 = LoopParseFunc(code);
        for (size_t A_Index192 = 0; A_Index192 < items192.size() + 0; A_Index192++) {
            std::string A_LoopField192 = items192[A_Index192 - 0];
            HTVM_Append(theIdNumOfThe34theVar, "");
            HTVM_Append(theIdNumOfThe34theVar, "");
        }
        std::vector<std::string> items193 = LoopParseFunc(code);
        for (size_t A_Index193 = 0; A_Index193 < items193.size() + 0; A_Index193++) {
            std::string A_LoopField193 = items193[A_Index193 - 0];
            theIdNumOfThe34theVar[A_Index193] = theIdNumOfThe34theVar[A_Index193] + Chr(34);
            HTVM_Append(getAllCharForTheFurtureSoIcanAddEscapeChar, A_LoopField193);
        }
        HTVM_Append(getAllCharForTheFurtureSoIcanAddEscapeChar, " ");
        ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuuhuuhtheidFor" + str21 + "--" + str21 + "asds" + str21 + "as--" + str21 + "theuhtuwaesphoutr" + Chr(34);
        std::vector<std::string> items194 = LoopParseFunc(code);
        for (size_t A_Index194 = 0; A_Index194 < items194.size() + 0; A_Index194++) {
            std::string A_LoopField194 = items194[A_Index194 - 0];
            if (A_LoopField194 == keyWordEscpaeChar && getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index194 + 1] == Chr(34)) {
                fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1;
                OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes;
            } else {
                if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1) {
                    OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField194;
                } else {
                    fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
                }
            }
        }
        code = OutFixDoubleQuotesInsideDoubleQuotes;
        if (keyWordEscpaeChar != Chr(92) && langToConvertTo != langFileExtension_2) {
            code = StrReplace(code, Chr(92), Chr(92) + Chr(92));
        }
        if (keyWordEscpaeChar == Chr(92) && langToConvertTo != langFileExtension_2) {
            std::vector<std::string> items195 = LoopParseFunc(code);
            for (size_t A_Index195 = 0; A_Index195 < items195.size() + 0; A_Index195++) {
                std::string A_LoopField195 = items195[A_Index195 - 0];
                if (A_LoopField195 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField195 != Chr(34)) {
                        if (A_LoopField195 == keyWordEscpaeChar && langToConvertTo != langFileExtension_2) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField195;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField195 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField195;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        } else {
            std::vector<std::string> items196 = LoopParseFunc(code);
            for (size_t A_Index196 = 0; A_Index196 < items196.size() + 0; A_Index196++) {
                std::string A_LoopField196 = items196[A_Index196 - 0];
                if (A_LoopField196 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField196 != Chr(34)) {
                        if (A_LoopField196 == keyWordEscpaeChar && keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index196 + 1] && langToConvertTo != langFileExtension_2) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar;
                            removeNexFixkeyWordEscpaeChar = 1;
                        }
                        else if (A_LoopField196 == keyWordEscpaeChar && langToConvertTo != langFileExtension_2) {
                            if (removeNexFixkeyWordEscpaeChar != 1) {
                                theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                            } else {
                                removeNexFixkeyWordEscpaeChar = 0;
                            }
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField196;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField196 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField196;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        }
        code = htCodeOUT754754;
        for (int A_Index197 = 0; A_Index197 < theIdNumOfThe34 + 0; A_Index197++) {
            theIdNumOfThe34theVar[A_Index197] = theIdNumOfThe34theVar[A_Index197] + Chr(34);
        }
        HTVM_Append(theIdNumOfThe34theVar, Chr(34));
        if (langToConvertTo == "dart" || langToConvertTo == "groovy") {
            for (int A_Index198 = 0; A_Index198 < HTVM_Size(theIdNumOfThe34theVar) + 0; A_Index198++) {
                theIdNumOfThe34theVar[A_Index198] = StrReplace(theIdNumOfThe34theVar[A_Index198], "$", Chr(92) + "$");
            }
        }
        code = StrReplace(code, Chr(13), "");
        slidingWinFixCommentsRmI = 0;
        newStringOutCode = "";
        std::vector<std::string> items199 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index199 = 0; A_Index199 < items199.size() + 0; A_Index199++) {
            std::string A_LoopField199 = items199[A_Index199 - 0];
            if (InStr(A_LoopField199, " " + keyWordComment) != false && SubStr(Trim(A_LoopField199), 1, StrLen(keyWordComment)) != keyWordComment) {
                posForRemoveCommentsOnTheEndOfTheLine = 0;
                slidingWinFixCommentsRmI = 0;
                slidingWinFixCommentsRm = slidingWinFixCommentsRmFUNC(A_LoopField199);
                for (int A_Index200 = 0; A_Index200 < HTVM_Size(slidingWinFixCommentsRm) + 0; A_Index200++) {
                    slidingWinFixCommentsRmI = A_Index200;
                    slidingWinFixCommentsRmHold = "";
                    for (int A_Index201 = 0; A_Index201 < StrLen(" " + keyWordComment) + 0; A_Index201++) {
                        slidingWinFixCommentsRmHold += slidingWinFixCommentsRm[slidingWinFixCommentsRmI + A_Index201];
                    }
                    if (Trim(slidingWinFixCommentsRmHold) == keyWordComment) {
                        posForRemoveCommentsOnTheEndOfTheLine = A_Index200;
                        break;
                    }
                }
                if (posForRemoveCommentsOnTheEndOfTheLine > 0) {
                    // Keep only the part before the comment
                    newStringOutCode += SubStr(A_LoopField199, 1, posForRemoveCommentsOnTheEndOfTheLine) + Chr(10);
                } else {
                    // Keep the whole line as it is
                    newStringOutCode += A_LoopField199 + Chr(10);
                }
            } else {
                newStringOutCode += A_LoopField199 + Chr(10);
            }
        }
        // Trim the last character (line break) from the final string
        code = StringTrimRight(newStringOutCode, 1);
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        if (langToConvertTo != langFileExtension_2) {
            semiColonForOneLinerOut = "";
            std::vector<std::string> items202 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index202 = 0; A_Index202 < items202.size() + 0; A_Index202++) {
                std::string A_LoopField202 = items202[A_Index202 - 0];
                if (SubStr(Trim(A_LoopField202), 1, 1) != ";") {
                    semiColonForOneLinerOut += StrReplace(A_LoopField202, ";", Chr(10)) + Chr(10);
                } else {
                    semiColonForOneLinerOut += A_LoopField202 + Chr(10);
                }
            }
            code = StringTrimRight(semiColonForOneLinerOut, 1);
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        if (langToConvertTo == langFileExtension_2) {
            if (useSemicolon_2 == "on") {
                theSemicolon = ";";
            } else {
                theSemicolon = "";
            }
            if (usePythonicColonSyntax_2 == "off") {
                theColon = "";
            } else {
                theColon = ":";
            }
        } else {
            if (langToConvertTo != "py" && langToConvertTo != "nim" && langToConvertTo != "ahk" && langToConvertTo != "go" && langToConvertTo != "lua" && langToConvertTo != "kt" && langToConvertTo != "rb" && langToConvertTo != "swift" && langToConvertTo != "groovy" && useSemicolon == "off") {
                theSemicolon = ";";
            } else {
                theSemicolon = "";
            }
            if (langToConvertTo != "py" && langToConvertTo != "nim" && usePythonicColonSyntax == "off") {
                theColon = "";
            } else {
                theColon = ":";
            }
        }
        if (langToConvertTo != langFileExtension_2) {
            // when
            // when
            // when
            if (RegExMatch(code, "\\bwhen\\b") || RegExMatch(code, "\\bwehn\\b")) {
                code = when_patternMatching(code);
            }
            // when
            // when
            // when
        } else {
            // when
            // when
            // when
            if (RegExMatch(code, "\\bwhen\\b") || RegExMatch(code, "\\bwehn\\b")) {
                code = when_patternMatching_HELP_HTVMtoHTVM(code);
            }
            // when
            // when
            // when
        }
        if (useCurlyBraces == "on") {
            fixSomeCurlyBraceForExratFlexability = "";
            str1 = "";
            std::vector<std::string> items203 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index203 = 0; A_Index203 < items203.size() + 0; A_Index203++) {
                std::string A_LoopField203 = items203[A_Index203 - 0];
                str1 = "";
                if (InStr(A_LoopField203, keyWordCurlyBraceOpen) || InStr(A_LoopField203, keyWordCurlyBraceClose)) {
                    if (SubStr(Trim(A_LoopField203), 1, StrLen(Trim(keyWordComment))) == Trim(keyWordComment) && isLineAconstruct(Trim(A_LoopField203)) == false) {
                        fixSomeCurlyBraceForExratFlexability += A_LoopField203 + Chr(10);
                    } else {
                        if (InStr(A_LoopField203, Trim(keyWordArrayDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField203, Trim(keyWordArrayOfIntegersDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField203, Trim(keyWordArrayOfStringsDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField203, Trim(keyWordArrayOfFloatingPointNumbersDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField203, Trim(keyWordArrayOfBooleansDefinition) + " " + keyWordAssign + " ") && useCurlyBracesSyntaxForArrayDef == "on") {
                            fixSomeCurlyBraceForExratFlexability += A_LoopField203 + Chr(10);
                        } else {
                            str1 = StrReplace(A_LoopField203, keyWordCurlyBraceOpen, "{");
                            str1 = StrReplace(str1, keyWordCurlyBraceClose, "}");
                            str1 = StrReplace(str1, "{", Chr(10) + "{" + Chr(10));
                            str1 = StrReplace(str1, "}", Chr(10) + "}" + Chr(10));
                            fixSomeCurlyBraceForExratFlexability += str1 + Chr(10);
                        }
                    }
                } else {
                    fixSomeCurlyBraceForExratFlexability += A_LoopField203 + Chr(10);
                }
            }
            code = StringTrimRight(fixSomeCurlyBraceForExratFlexability, 1);
            fixSomeCurlyBraceForExratFlexabilityTriHELP = "";
            std::vector<std::string> items204 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index204 = 0; A_Index204 < items204.size() + 0; A_Index204++) {
                std::string A_LoopField204 = items204[A_Index204 - 0];
                fixSomeCurlyBraceForExratFlexabilityTriHELP += Trim(A_LoopField204) + Chr(10);
            }
            code = StringTrimRight(fixSomeCurlyBraceForExratFlexabilityTriHELP, 1);
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            // name: subroutine/func for GUI and backend
            if (langToConvertTo != langFileExtension_2) {
                if (langToConvertTo == "js" || langToConvertTo == "py") {
                    code = initializeBackendAndGUIInteractionWithLabelSubroutineLikeButConvertsToFunction(code);
                }
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (keyWordCurlyBraceOpen != "{") {
                std::vector<std::string> items205 = LoopParseFunc(code, "\n", "\r");
                for (size_t A_Index205 = 0; A_Index205 < items205.size() + 0; A_Index205++) {
                    std::string A_LoopField205 = items205[A_Index205 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField205)) == true || Trim(A_LoopField205) == keyWordCurlyBraceOpen) {
                        htCodeOutFixINT2 = 1;
                    }
                    htCodeOutFixINT = 0;
                    std::vector<std::string> items206 = LoopParseFunc(A_LoopField205, " ");
                    for (size_t A_Index206 = 0; A_Index206 < items206.size() + 0; A_Index206++) {
                        std::string A_LoopField206 = items206[A_Index206 - 0];
                        htCodeOutFixINT++;
                    }
                    htCodeOutFixINT--;
                    std::vector<std::string> items207 = LoopParseFunc(A_LoopField205, " ");
                    for (size_t A_Index207 = 0; A_Index207 < items207.size() + 0; A_Index207++) {
                        std::string A_LoopField207 = items207[A_Index207 - 0];
                        if (htCodeOutFixINT == A_Index207 && htCodeOutFixINT2 == 1) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField207, keyWordCurlyBraceOpen, "{") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField207 + " ";
                        }
                    }
                    htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1);
                    htCodeOutFixEnd += Chr(10);
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            htCodeOutFixEnd = "";
            if (keyWordCurlyBraceClose != "}") {
                std::vector<std::string> items208 = LoopParseFunc(code, "\n", "\r");
                for (size_t A_Index208 = 0; A_Index208 < items208.size() + 0; A_Index208++) {
                    std::string A_LoopField208 = items208[A_Index208 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField208)) == true || Trim(A_LoopField208) == keyWordCurlyBraceClose) {
                        htCodeOutFixINT2 = 1;
                    }
                    std::vector<std::string> items209 = LoopParseFunc(A_LoopField208, " ");
                    for (size_t A_Index209 = 0; A_Index209 < items209.size() + 0; A_Index209++) {
                        std::string A_LoopField209 = items209[A_Index209 - 0];
                        if (htCodeOutFixINT2 == 1 || Trim(A_LoopField209) == keyWordCurlyBraceClose) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField209, keyWordCurlyBraceClose, "}") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField209 + " ";
                        }
                    }
                    htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1);
                    htCodeOutFixEnd += Chr(10);
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
        }
        if (langToConvertTo != langFileExtension_2) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            // GUI
            // GUI
            // GUI
            if (langToConvertTo == "js" && InStr(Trim(StrLower(code)), "gui")) {
                code = guiParser(code);
            }
            // GUI
            // GUI
            // GUI
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        if (useCurlyBraces == "on") {
            code = fixIfElseIfMultiLineStatement(code);
            int5 = 0;
            std::vector<std::string> items210 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index210 = 0; A_Index210 < items210.size() + 0; A_Index210++) {
                std::string A_LoopField210 = items210[A_Index210 - 0];
                HTVM_Append(addNoCurlyFixWhenNextLineAfterConstructLookAhead, Trim(A_LoopField210));
            }
            HTVM_Append(addNoCurlyFixWhenNextLineAfterConstructLookAhead, " ");
            //;;;
            addNoCurlyFixWhenNextLineAfterConstructOut = "";
            std::vector<std::string> items211 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index211 = 0; A_Index211 < items211.size() + 0; A_Index211++) {
                std::string A_LoopField211 = items211[A_Index211 - 0];
                if (isLineAconstruct(Trim(A_LoopField211)) && addNoCurlyFixWhenNextLineAfterConstructLookAhead[A_Index211 + 1] != "{") {
                    int5 = 1;
                    addNoCurlyFixWhenNextLineAfterConstructOut += A_LoopField211 + Chr(10) + "{" + Chr(10);
                } else {
                    if (int5 == 1) {
                        int5 = 0;
                        addNoCurlyFixWhenNextLineAfterConstructOut += A_LoopField211 + Chr(10) + "}" + Chr(10);
                    } else {
                        addNoCurlyFixWhenNextLineAfterConstructOut += A_LoopField211 + Chr(10);
                    }
                }
            }
            code = StringTrimRight(addNoCurlyFixWhenNextLineAfterConstructOut, 1);
            int5 = 0;
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        htCodeOutFixEnd = "";
        if (useEnd == "on") {
            std::vector<std::string> items212 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index212 = 0; A_Index212 < items212.size() + 0; A_Index212++) {
                std::string A_LoopField212 = items212[A_Index212 - 0];
                if (StrLower(Trim(A_LoopField212)) == StrLower(keyWordEnd)) {
                    htCodeOutFixEnd += "}" + Chr(10);
                }
                else if (SubStr(StrLower(Trim(A_LoopField212)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF) && isLineAconstruct(Trim(A_LoopField212)) == true) {
                    htCodeOutFixEnd += A_LoopField212 + Chr(10) + "{" + Chr(10);
                }
                else if (SubStr(StrLower(Trim(A_LoopField212)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop) && isLineAconstruct(Trim(A_LoopField212)) == true) {
                    htCodeOutFixEnd += A_LoopField212 + Chr(10) + "{" + Chr(10);
                }
                else if (SubStr(StrLower(Trim(A_LoopField212)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf) && isLineAconstruct(Trim(A_LoopField212)) == true) {
                    htCodeOutFixEnd += Chr(10) + "}" + Chr(10) + A_LoopField212 + Chr(10) + "{" + Chr(10);
                }
                else if (SubStr(StrLower(Trim(A_LoopField212)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse) && isLineAconstruct(Trim(A_LoopField212)) == true) {
                    htCodeOutFixEnd += Chr(10) + "}" + Chr(10) + A_LoopField212 + Chr(10) + "{" + Chr(10);
                }
                else if (SubStr(StrLower(Trim(A_LoopField212)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch) && isLineAconstruct(Trim(A_LoopField212)) == true) {
                    htCodeOutFixEnd += Chr(10) + "}" + Chr(10) + A_LoopField212 + Chr(10) + "{" + Chr(10);
                }
                else if (SubStr(StrLower(Trim(A_LoopField212)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally) && isLineAconstruct(Trim(A_LoopField212)) == true) {
                    htCodeOutFixEnd += Chr(10) + "}" + Chr(10) + A_LoopField212 + Chr(10) + "{" + Chr(10);
                }
                else if (isLineAconstruct(Trim(A_LoopField212)) == true) {
                    htCodeOutFixEnd += A_LoopField212 + Chr(10) + "{" + Chr(10);
                } else {
                    htCodeOutFixEnd += A_LoopField212 + Chr(10);
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        if (usePythonicColonSyntax == "off") {
            if (useEnd == "off" && useCurlyBraces == "off") {
                htCodeOutFixEnd = "";
                std::vector<std::string> items213 = LoopParseFunc(code, "\n", "\r");
                for (size_t A_Index213 = 0; A_Index213 < items213.size() + 0; A_Index213++) {
                    std::string A_LoopField213 = items213[A_Index213 - 0];
                    if (isLineAconstruct(Trim(A_LoopField213)) == true) {
                        htCodeOutFixEnd += A_LoopField213 + ":" + Chr(10);
                    } else {
                        htCodeOutFixEnd += A_LoopField213 + Chr(10);
                    }
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
        }
        if (useCurlyBraces == "off" && useEnd == "off") {
            code = AddCurlyBraces(code);
        }
        outTrimCode = "";
        std::vector<std::string> items214 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index214 = 0; A_Index214 < items214.size() + 0; A_Index214++) {
            std::string A_LoopField214 = items214[A_Index214 - 0];
            outTrimCode += Trim(A_LoopField214) + Chr(10);
        }
        code = StringTrimRight(outTrimCode, 1);
        // for converting c++ to js and py
        //code := StrReplace(code, "{}", "[]")
        std::string outCodeFixBraces = "";
        for (int A_Index215 = 0; A_Index215 < 2 + 0; A_Index215++) {
            outCodeFixBraces = "";
            std::vector<std::string> items216 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index216 = 0; A_Index216 < items216.size() + 0; A_Index216++) {
                std::string A_LoopField216 = items216[A_Index216 - 0];
                if (InStr(A_LoopField216, Trim(keyWordArrayDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField216, Trim(keyWordArrayOfIntegersDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField216, Trim(keyWordArrayOfStringsDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField216, Trim(keyWordArrayOfFloatingPointNumbersDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField216, Trim(keyWordArrayOfBooleansDefinition) + " " + keyWordAssign + " ") && useCurlyBracesSyntaxForArrayDef == "on") {
                    if (SubStr(StrLower(A_LoopField216), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc) || SubStr(StrLower(A_LoopField216), 1, StrLen(StrLower(keyWordAsync) + StrLower(keyWordFunc))) == StrLower(keyWordAsync) + StrLower(keyWordFunc)) {
                        if (InStr(Trim(A_LoopField216), "{") && Trim(A_LoopField216) != "{" && SubStr(Trim(A_LoopField216), 1, StrLen(Trim(keyWordComment))) != Trim(keyWordComment)) {
                            outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField216), "{", "")) + Chr(10) + "{" + Chr(10);
                        }
                        else if (InStr(Trim(A_LoopField216), "}") && Trim(A_LoopField216) != "}" && SubStr(Trim(A_LoopField216), 1, StrLen(Trim(keyWordComment))) != Trim(keyWordComment)) {
                            outCodeFixBraces += "}" + Chr(10) + Trim(StrReplace(Trim(A_LoopField216), "}", "")) + Chr(10);
                        } else {
                            outCodeFixBraces += Trim(A_LoopField216) + Chr(10);
                        }
                    } else {
                        outCodeFixBraces += Trim(A_LoopField216) + Chr(10);
                    }
                } else {
                    if (InStr(Trim(A_LoopField216), "{") && Trim(A_LoopField216) != "{" && SubStr(Trim(A_LoopField216), 1, StrLen(Trim(keyWordComment))) != Trim(keyWordComment)) {
                        outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField216), "{", "")) + Chr(10) + "{" + Chr(10);
                    }
                    else if (InStr(Trim(A_LoopField216), "}") && Trim(A_LoopField216) != "}" && SubStr(Trim(A_LoopField216), 1, StrLen(Trim(keyWordComment))) != Trim(keyWordComment)) {
                        outCodeFixBraces += "}" + Chr(10) + Trim(StrReplace(Trim(A_LoopField216), "}", "")) + Chr(10);
                    } else {
                        outCodeFixBraces += Trim(A_LoopField216) + Chr(10);
                    }
                }
            }
            code = StringTrimRight(outCodeFixBraces, 1);
        }
        htCodeOutFixEnd = "";
        if (usePythonicColonSyntax == "on" || useCurlyBraces == "off" && useEnd == "off") {
            std::vector<std::string> items217 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index217 = 0; A_Index217 < items217.size() + 0; A_Index217++) {
                std::string A_LoopField217 = items217[A_Index217 - 0];
                if (isLineAconstruct(Trim(A_LoopField217)) == true) {
                    htCodeOutFixEnd += StringTrimRight(A_LoopField217, 1) + Chr(10);
                } else {
                    htCodeOutFixEnd += A_LoopField217 + Chr(10);
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        //;; main loop ;;;
        //;; main loop ;;;
        //;; main loop ;;;
        //;; main loop ;;;
        fullLangAllOperators = GETfullLangAllOperators();
        fullLangAllOperators_HELP = GETfullLangAllOperators_HELP();
        if (isNotHTVMfile2 == 0) {
            std::vector<std::string> items218 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index218 = 0; A_Index218 < items218.size() + 0; A_Index218++) {
                std::string A_LoopField218 = items218[A_Index218 - 0];
                if (StrLower(Trim(A_LoopField218)) == StrLower(keyWordMainLabel)) {
                    didWeUseMainLabel = 1;
                    if (langToConvertTo == langFileExtension_2) {
                        codeOutFixAndAddMainFunc += keyWordMainLabel_2 + Chr(10);
                    }
                    if (langToConvertTo == "cpp") {
                        codeOutFixAndAddMainFunc += "int main(int argc, char* argv[])" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
                        codeOutFixAndAddMainFunc += "async function main()" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
                        codeOutFixAndAddMainFunc += "async function main(): Promise<void>" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "go") {
                        codeOutFixAndAddMainFunc += "func main()" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "cs") {
                        codeOutFixAndAddMainFunc += "static void Main(string[] args)" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "java") {
                        codeOutFixAndAddMainFunc += "public static void main(String[] args)" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "kt") {
                        codeOutFixAndAddMainFunc += "fun main(args: Array<String>)" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "swift") {
                        codeOutFixAndAddMainFunc += "func main()" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "dart") {
                        codeOutFixAndAddMainFunc += "void main(List<String> arguments)" + Chr(10) + "{" + Chr(10);
                    }
                } else {
                    codeOutFixAndAddMainFunc += A_LoopField218 + Chr(10);
                }
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "cpp") {
                codeOutFixAndAddMainFunc = "int main(int argc, char* argv[])" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
                codeOutFixAndAddMainFunc = "async function main()" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
                codeOutFixAndAddMainFunc = "async function main(): Promise<void>" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "go") {
                codeOutFixAndAddMainFunc = "func main()" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "cs") {
                codeOutFixAndAddMainFunc = "static void Main(string[] args)" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "java") {
                codeOutFixAndAddMainFunc = "public static void main(String[] args)" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "kt") {
                codeOutFixAndAddMainFunc = "fun main(args: Array<String>)" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "swift") {
                codeOutFixAndAddMainFunc = "func main()" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "dart") {
                codeOutFixAndAddMainFunc = "void main(List<String> arguments)" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            code = StringTrimRight(codeOutFixAndAddMainFunc, 1);
            // main loop
            // main loop
        }
        if (useCurlyBraces == "off") {
            code = fixIfElseIfMultiLineStatement(code);
        }
        std::vector<std::string> items219 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index219 = 0; A_Index219 < items219.size() + 0; A_Index219++) {
            std::string A_LoopField219 = items219[A_Index219 - 0];
            HTVM_Append(lookIntoTheNextLineForFuncWhitNoKeyWord, A_LoopField219);
        }
        HTVM_Append(lookIntoTheNextLineForFuncWhitNoKeyWord, " ");
        if (langToConvertTo != langFileExtension_2) {
            code = OSP(code);
            code = StrReplace(code, "}_HTVM-OSP-HTVM-OSP-REMOVE-OSP-HTVMv2--OSP", "}");
            code = StrReplace(code, "{_HTVM-OSP-HTVM-OSP-REMOVE-OSP-HTVMv2--OSP", "{");
        }
        htCode = "";
        //print("=======UP==========")
        //print(code)
        //print("=======DOWN==========")
        std::vector<std::string> items220 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index220 = 0; A_Index220 < items220.size() + 0; A_Index220++) {
            std::string A_LoopField220 = items220[A_Index220 - 0];
            lineDone = 0;
            if (SubStr(A_LoopField220, 1, StrLen(keyWordComment)) == keyWordComment) {
                lineDone = 1;
                str1 = StringTrimLeft(A_LoopField220, StrLen(keyWordComment));
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordComment_2 + str1 + Chr(10);
                }
                if (langToConvertTo == "cpp") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "#" + str1 + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "--" + str1 + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "#" + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "#" + str1 + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += ";" + str1 + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "//" + str1 + Chr(10);
                }
            }
            else if (InStr(A_LoopField220, "guiInit(") || InStr(A_LoopField220, "guiAdd(") || InStr(A_LoopField220, "guiAddElement(") || InStr(A_LoopField220, "guiControl(") || InStr(A_LoopField220, "HTVM_init(") || InStr(A_LoopField220, "HTVM_register(") || InStr(A_LoopField220, "HTVM_custom_port(") && lineDone == 0) {
                lineDone = 1;
                if (InStr(A_LoopField220, "HTVM_init(")) {
                    htCode += Trim(A_LoopField220) + Chr(10);
                } else {
                    htCode += Trim(expressionParserTranspiler(Trim(A_LoopField220))) + Chr(10);
                }
            }
            else if (Trim(A_LoopField220) == keyWordCommentOpenMultiLine) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordCommentOpenMultiLine_2 + Chr(10);
                }
                if (langToConvertTo == "cpp") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += Chr(34) + Chr(34) + Chr(34) + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "--[[" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "=begin" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "#[" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "/*" + Chr(10);
                }
            }
            else if (Trim(A_LoopField220) == keyWordCommentCloseMultiLine) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordCommentCloseMultiLine_2 + Chr(10);
                }
                if (langToConvertTo == "cpp") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += Chr(34) + Chr(34) + Chr(34) + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "]]" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "=end" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "]#" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "*/" + Chr(10);
                }
            }
            else if (InStr(A_LoopField220, "[][][][][] ")) {
                lineDone = 1;
                str1 = StrSplit(A_LoopField220, " ", 2);
                HTVM_Append(ospDic1, str1);
                strOspHold = StrReplace(str1, "_", ".");
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordStruct_2 + StrReplace(str1, "_", ".") + Chr(10) + "{" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField220)), 1, StrLen(StrLower(keyWordStruct))) == StrLower(keyWordStruct)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField220, StrLen(keyWordStruct)));
                if (langToConvertTo == langFileExtension_2) {
                    htCode += Trim(keyWordStruct_2) + " " + str0 + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField220)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField220, StrLen(keyWordAlliance)));
                if (langToConvertTo == langFileExtension_2) {
                    htCode += Trim(keyWordAlliance_2) + " " + str0 + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField220)), 1, StrLen(StrLower(keyWordCrew))) == StrLower(keyWordCrew)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField220, StrLen(keyWordCrew)));
                if (langToConvertTo == langFileExtension_2) {
                    htCode += Trim(keyWordCrew_2) + " " + str0 + Chr(10);
                }
            }
            else if (InStr(A_LoopField220, "[end][end][end][end][end] ")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += "}" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField220)), 1, StrLen(StrLower(keyWordProp))) == StrLower(keyWordProp)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField220, StrLen(keyWordProp)));
                str1 = Trim(StrSplit(str0, "-----------------------HTVM-OSP-HTVM-OBJ--------------", 1));
                str20 = Trim(StrSplit(str0, "-----------------------HTVM-OSP-HTVM-OBJ--------------", 2));
                if (str20 == "" && langToConvertTo != langFileExtension_2) {
                    continue;
                }
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordProp_2 + propHELP(str1, "no-no") + Chr(10);
                } else {
                    htCode += propHELP(str1, StrReplace(str20, ".", "_") + "_") + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField220)), 1, StrLen(StrLower(keyWordProc))) == StrLower(keyWordProc)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField220, StrLen(keyWordProc)));
                str1 = Trim(StrSplit(str0, "-----------------------HTVM-OSP-HTVM-OBJ--------------", 1));
                str20 = Trim(StrSplit(str0, "-----------------------HTVM-OSP-HTVM-OBJ--------------", 2));
                str16 = Trim(StrSplit(str1, "(", 1));
                str18 = Trim(StrSplit(str1, ")", 2));
                int1 = 0;
                str17 = "";
                std::vector<std::string> items221 = LoopParseFunc(str16, " ");
                for (size_t A_Index221 = 0; A_Index221 < items221.size() + 0; A_Index221++) {
                    std::string A_LoopField221 = items221[A_Index221 - 0];
                    str17 = Trim(A_LoopField221);
                }
                // last word aka the proc name
                //str17
                str15 = StrReplace(str20 + "_" + str17, "_", ".");
                HTVM_Append(ospDic2, StringTrimLeft(str15, 11));
                str15 = StrReplace(str15, ".", "_");
                str1 = StrReplace(str1, "(" + keyWordThis + ")", "()");
                if (usePrefixTypeForTypeDefinition == "on") {
                    str2 = Trim(StrSplit(str1, "(", 1));
                    // func body
                    str1 = Trim(StringTrimLeft(str1, StrLen(str2)));
                    str1 = StringTrimRight(str1, 1);
                    // type of the func
                    str3 = Trim(StringTrimRight(str2, StrLen(StrSplit(str2, " ", countChars(str2, " ") + 1))));
                    // name of func
                    str2 = Trim(StrSplit(str2, " ", countChars(str2, " ") + 1));
                }
                if (usePostfixTypeForTypeDefinition == "on") {
                    // name of func
                    str2 = Trim(StrSplit(str1, "(", 1));
                    // func body
                    str1 = Trim(StringTrimLeft(str1, StrLen(str2)));
                    // type of the func
                    str3 = Trim(StrSplit(str1, ")", countChars(str1, ")") + 1));
                    str3 = StringTrimLeft(str3, 1);
                    str1 = Trim(StringTrimRight(str1, StrLen(str3) + 2));
                }
                str1 = StringTrimLeft(str1, 1);
                str3 = Trim(str3);
                if (langToConvertTo == langFileExtension_2) {
                    if (int1 == 1) {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            htCode += keyWordAsync_2 + keyWordProc_2 + getFuncTypeConvert(str3) + " " + str2 + "(" + keyWordThis_2 + ")" + Chr(10);
                        } else {
                            htCode += keyWordAsync_2 + keyWordProc_2 + str2 + "(" + keyWordThis_2 + "): " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    } else {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            htCode += keyWordProc_2 + getFuncTypeConvert(str3) + " " + str2 + "(" + keyWordThis_2 + ")" + Chr(10);
                        } else {
                            htCode += keyWordProc_2 + str2 + "(" + keyWordThis_2 + "): " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                }
                availableFuncsInHTVMInHTVM += str15 + Chr(10);
                if (langToConvertTo == "cpp") {
                    htCode += getFuncTypeConvert(str3) + " " + str15 + "(std::string osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "def " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + "):" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    if (int1 == 1) {
                        htCode += "async function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                    } else {
                        if (useJavaScriptAllFuncsAreAsync == "on") {
                            htCode += "async function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                        } else {
                            htCode += "function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                        }
                    }
                }
                // Go
                if (langToConvertTo == "go") {
                    skipLeftCuleyForFuncPLS = 1;
                    if (str3 == keyWordVoid) {
                        htCode += "func " + str15 + "(__HTVM_V2_TO_GO_optionalParams__ ...interface{})" + Chr(10) + "{" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword := " + Chr(34) + Chr(34) + Chr(10) + "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " 0 " + Chr(10) + "{" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword = __HTVM_V2_TO_GO_optionalParams__[0].(string)" + Chr(10) + "}" + Chr(10) + "_ = osp_osp_this_keyword_htvm_osp_this_htvm_keyword" + Chr(10);
                    } else {
                        htCode += "func " + str15 + "(__HTVM_V2_TO_GO_optionalParams__ ...interface{}) " + getFuncTypeConvert(str3) + Chr(10) + "{" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword := " + Chr(34) + Chr(34) + Chr(10) + "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " 0 {" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword = __HTVM_V2_TO_GO_optionalParams__[0].(string)" + Chr(10) + "}" + Chr(10) + "_ = osp_osp_this_keyword_htvm_osp_this_htvm_keyword" + Chr(10);
                    }
                }
                if (langToConvertTo == "lua") {
                    skipLeftCuleyForFuncPLS = 1;
                    htCode += "function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword) " + Chr(10) + "{" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword = osp_osp_this_keyword_htvm_osp_this_htvm_keyword or " + Chr(34) + Chr(34) + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "static " + getFuncTypeConvert(str3) + " " + str15 + "(string osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    skipLeftCuleyForFuncPLS = 1;
                    htCode += "public static " + getFuncTypeConvert(str3) + " " + str15 + "(Object... __HTVM_V2_TO_JAVA_optionalParams__)" + Chr(10) + "{" + Chr(10) + "String osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + "" + Chr(34) + ";  // Initialize the variable" + Chr(10) + "if (__HTVM_V2_TO_JAVA_optionalParams__.length " + Chr(62) + " 0 && __HTVM_V2_TO_JAVA_optionalParams__[0] instanceof String)" + Chr(10) + "{" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword = (String) __HTVM_V2_TO_JAVA_optionalParams__[0];" + Chr(10) + "}" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    if (str3 == keyWordVoid) {
                        htCode += "fun " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword: String = " + Chr(34) + Chr(34) + ")" + Chr(10);
                    } else {
                        htCode += "fun " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword: String = " + Chr(34) + Chr(34) + "): " + getFuncTypeConvert(str3) + Chr(10);
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "def " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    if (str3 == keyWordVoid) {
                        htCode += "proc " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword: string = " + Chr(34) + Chr(34) + ") =" + Chr(10);
                    } else {
                        htCode += "proc " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword: string = " + Chr(34) + Chr(34) + "): " + getFuncTypeConvert(str3) + " =" + Chr(10);
                    }
                }
                if (langToConvertTo == "ahk") {
                    htCode += str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword := " + Chr(34) + Chr(34) + ")" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    if (str3 == keyWordVoid) {
                        htCode += "func " + str15 + "(_ osp_osp_this_keyword_htvm_osp_this_htvm_keyword: String = " + Chr(34) + Chr(34) + ")" + Chr(10);
                    } else {
                        htCode += "func " + str15 + "(_ osp_osp_this_keyword_htvm_osp_this_htvm_keyword: String = " + Chr(34) + Chr(34) + ") -> " + getFuncTypeConvert(str3) + Chr(10);
                    }
                }
                if (langToConvertTo == "dart") {
                    htCode += getFuncTypeConvert(str3) + " " + str15 + "([String osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + "])" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    if (useJavaScriptAllFuncsAreAsync == "off") {
                        htCode += "function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword: string = " + Chr(34) + Chr(34) + "): " + getFuncTypeConvert(str3) + Chr(10);
                    } else {
                        htCode += "async function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword: string = " + Chr(34) + Chr(34) + "): " + getFuncTypeConvert(str3) + Chr(10);
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "def " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField220)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF) && SubStr(StrLower(Trim(A_LoopField220)), 1, StrLen(StrLower(keyWordElseIf))) != StrLower(keyWordElseIf)) {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(A_LoopField220, StrLen(keyWordIF)));
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"));
                str1 = StringTrimRight(str1, 1);
                str1 = StringTrimLeft(str1, 1);
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + str1 + ":" + Chr(10);
                            } else {
                                htCode += keyWordIF_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":" + Chr(10);
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + "(" + str1 + "):" + Chr(10);
                            } else {
                                htCode += keyWordIF_2 + str1 + ":" + Chr(10);
                            }
                        }
                    } else {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + str1 + Chr(10);
                            } else {
                                htCode += keyWordIF_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + Chr(10);
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + "(" + str1 + ")" + Chr(10);
                            } else {
                                htCode += keyWordIF_2 + str1 + Chr(10);
                            }
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "py") {
                    htCode += "if " + str1 + ":" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "go") {
                    htCode += "if " + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "if " + str1 + " then" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "java") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "kt") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "if " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "if " + str1 + ":" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "if " + str1 + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "if (" + str1 + ")" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField220)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf) && SubStr(StrLower(Trim(A_LoopField220)), 1, StrLen(StrLower(keyWordIF))) != StrLower(keyWordIF)) {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(A_LoopField220, StrLen(keyWordElseIf)));
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"));
                str1 = StringTrimRight(str1, 1);
                str1 = StringTrimLeft(str1, 1);
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + str1 + ":" + Chr(10);
                            } else {
                                htCode += keyWordElseIf_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":" + Chr(10);
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + "(" + str1 + "):" + Chr(10);
                            } else {
                                htCode += keyWordElseIf_2 + str1 + ":" + Chr(10);
                            }
                        }
                    } else {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + str1 + Chr(10);
                            } else {
                                htCode += keyWordElseIf_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + Chr(10);
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + "(" + str1 + ")" + Chr(10);
                            } else {
                                htCode += keyWordElseIf_2 + str1 + Chr(10);
                            }
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "py") {
                    htCode += "elif " + str1 + ":" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "go") {
                    htCode += "else if " + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "elseif " + str1 + " then" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "java") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "kt") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "elsif " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "elif " + str1 + ":" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "else if " + str1 + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "else if (" + str1 + ")" + Chr(10);
                }
            }
            else if (StrLower(Trim(A_LoopField220)) == StrLower(keyWordElse) || StrLower(Trim(A_LoopField220)) == StrLower(keyWordElse + ":")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordElse_2 + ":" + Chr(10);
                    } else {
                        htCode += keyWordElse_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "else" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "else:" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "else" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "else" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "else" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "else" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "else" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "else" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "else" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "else:" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "else" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "else" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "else" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "else" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "else" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField220)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)) {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(A_LoopField220, StrLen(keyWordWhileLoop)));
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"));
                str1 = StringTrimRight(str1, 1);
                str1 = StringTrimLeft(str1, 1);
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordWhileLoop_2 + str1 + ":" + Chr(10);
                            } else {
                                htCode += keyWordWhileLoop_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":" + Chr(10);
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordWhileLoop_2 + "(" + str1 + "):" + Chr(10);
                            } else {
                                htCode += keyWordWhileLoop_2 + str1 + ":" + Chr(10);
                            }
                        }
                    } else {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordWhileLoop_2 + str1 + Chr(10);
                            } else {
                                htCode += keyWordWhileLoop_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + Chr(10);
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordWhileLoop_2 + "(" + str1 + ")" + Chr(10);
                            } else {
                                htCode += keyWordWhileLoop_2 + str1 + Chr(10);
                            }
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "py") {
                    htCode += "while " + str1 + ":" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "go") {
                    htCode += "for " + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "while " + str1 + " do" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "java") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "kt") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "while " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "while " + str1 + ":" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "while " + str1 + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "while (" + str1 + ")" +  Chr(10);
                }
            }
            else if (StrLower(Trim(A_LoopField220)) == StrLower(keyWordTry) || StrLower(Trim(A_LoopField220)) == StrLower(keyWordTry + ":")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordTry_2 + ":" + Chr(10);
                    } else {
                        htCode += keyWordTry_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "try" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "try:" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "try" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "try" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "try" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "try" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "begin" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "try:" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "try" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "do" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "try" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "try" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "try" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField220)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)) {
                lineDone = 1;
                str1 = Trim(StrReplace(StrReplace(StringTrimLeft(A_LoopField220, StrLen(keyWordCatch)), "(", ""), ")", ""));
                theTryCatchVarForErrors = str1;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        if (useParentheses_2 == "on") {
                            htCode += keyWordCatch_2 + "(" + str1 + "):" + Chr(10);
                        } else {
                            htCode += keyWordCatch_2 + str1 + ":" + Chr(10);
                        }
                    } else {
                        if (useParentheses_2 == "off") {
                            htCode += keyWordCatch_2 + str1 + Chr(10);
                        } else {
                            htCode += keyWordCatch_2 + "(" + str1 + ")" + Chr(10);
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "catch (const std::exception& " + str1 + ")" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "except Exception as " + str1 + ":" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "catch (" + str1 + ")" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "catch (Exception " + str1 + ")" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "catch (Exception " + str1 + ")" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "catch (" + str1 + ": Exception)" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "rescue => " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "except ValueError as " + str1 + ":" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "catch " + str1 + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "catch let " + str1 + " as NSError" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "catch (" + str1 + ")" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "catch (" + str1 + ")" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "catch (Exception " + str1 + ")" + Chr(10);
                }
            }
            else if (StrLower(Trim(A_LoopField220)) == StrLower(keyWordFinally) || StrLower(Trim(A_LoopField220)) == StrLower(keyWordFinally + ":")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordFinally_2 + ":" + Chr(10);
                    } else {
                        htCode += keyWordFinally_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "if (" + Chr(34) + "finally dosent exist in c++" + Chr(34) + " == " + Chr(34) + "finally dosent exist in c++" + Chr(34) + ")" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "finally:" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "finally" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "finally" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "finally" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "finally" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "ensure" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "finally:" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "finally" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "if (" + Chr(34) + "finally dosent exist in swift" + Chr(34) + " == " + Chr(34) + "finally dosent exist in swift" + Chr(34) + ")" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "finally" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "finally" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "finally" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField220)), 1, StrLen(StrLower(keyWordThrow))) == StrLower(keyWordThrow)) {
                lineDone = 1;
                str1 = Trim(A_LoopField220);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str1 = expressionParserTranspiler(fixArray1234(Trim(StringTrimLeft(str1, StrLen(keyWordThrow)))));
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordThrow_2 + keyWordErrorMsg_2 + "(" + str1 + ");" + Chr(10);
                    } else {
                        htCode += keyWordThrow_2 + keyWordErrorMsg_2 + "(" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "throw std::runtime_error(" + str1 + ");" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "raise Exception(" + str1 + ")" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "throw new Error(" + str1 + ");" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "throw new Exception(" + str1 + ");" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "throw new Exception(" + str1 + ");" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "throw Exception(" + str1 + ")" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "raise " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "raise newException(ValueError, " + str1 + ")" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "throw " + str1 + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "try ErrorMsg(" + str1 + ")" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "throw Exception(" + str1 + ");" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += " throw new Error(" + str1 + ");" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "throw new Exception(" + str1 + ")" + Chr(10);
                }
            }
            else if (StrLower(A_LoopField220) == StrLower(keyWordBreak) || StrLower(A_LoopField220) == StrLower(keyWordBreak + ";")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordBreak_2 + ";" + Chr(10);
                    } else {
                        htCode += keyWordBreak_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "break;" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "break" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "break;" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "break" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "break" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "break;" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "break;" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "break" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "break" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "break" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "break" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "break" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "break;" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "break;" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "break;" + Chr(10);
                }
            }
            else if (StrLower(A_LoopField220) == StrLower(Trim(keyWordReturnStatement)) || StrLower(A_LoopField220) == StrLower(Trim(keyWordReturnStatement) + ";")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordReturnStatement_2 + ";" + Chr(10);
                    } else {
                        htCode += keyWordReturnStatement_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "return;" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "return" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "return;" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "return" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "return" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "return;" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "return;" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "return" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "return" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "return" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "return" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "return" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "return;" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "return;" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "return;" + Chr(10);
                }
            }
            else if (SubStr(Trim(StrLower(A_LoopField220)), 1, StrLen(StrLower(keyWordReturnStatement))) == StrLower(keyWordReturnStatement)) {
                lineDone = 1;
                str1 = Trim(expressionParserTranspiler(Trim(StringTrimLeft(A_LoopField220, StrLen(keyWordReturnStatement)))));
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordReturnStatement_2 + str1 + ";" + Chr(10);
                    } else {
                        htCode += keyWordReturnStatement_2 + str1 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "return " + str1 + ";" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "return " + str1 + ";" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "return " + str1 + ";" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "return " + str1 + ";" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "return " + str1 + ";" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "return " + str1 + ";" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "return " + str1 + ";" + Chr(10);
                }
            }
            else if (StrLower(A_LoopField220) == StrLower(keyWordContinue) || StrLower(A_LoopField220) == StrLower(keyWordContinue + ";")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordContinue_2 + ";" + Chr(10);
                    } else {
                        htCode += keyWordContinue_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "continue;" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "continue" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "continue;" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "continue" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "goto continue" + STR(luaContinueFix_Num) + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "continue;" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "continue;" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "continue" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "next" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "continue" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "continue" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "continue" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "continue;" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "continue;" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "continue;" + Chr(10);
                }
            }
            else if (StrLower(A_LoopField220) == "::" + keyWordContinue || StrLower(A_LoopField220) == "::" + keyWordContinue + ";") {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += "::" + keyWordContinue_2 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "::continue" + STR(luaContinueFix_Num) + "::" + Chr(10);
                    luaContinueFix_Num++;
                }
            }
            else if (StrLower(A_LoopField220) == StrLower(keyWordLoopInfinite) || StrLower(A_LoopField220) == StrLower(keyWordLoopInfinite + ":")) {
                // infinity loops
                haveWeEverUsedAloop = 1;
                lineDone = 1;
                howMany_fixAindexInGoUnused++;
                if (langToConvertTo == "py") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , value in enumerate(iter(int, 1), start=" + AHKlikeLoopsIndexedAt + "):";
                }
                if (langToConvertTo == "js") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "cpp") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "go") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++";
                }
                if (langToConvertTo == "lua") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in infinite_HTVM_Lua_Loop_HTVM() do";
                }
                if (langToConvertTo == "cs") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in generateSequence(" + AHKlikeLoopsIndexedAt + ") { it + 1 })";
                }
                if (langToConvertTo == "rb") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..Float::INFINITY";
                }
                if (langToConvertTo == "nim") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in countup(" + AHKlikeLoopsIndexedAt + ", high(int)):";
                }
                if (langToConvertTo == "ahk") {
                    var1 = "Loop";
                }
                if (langToConvertTo == "swift") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "...";
                }
                if (langToConvertTo == "dart") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        var1 = keyWordLoopInfinite_2 + ":";
                    } else {
                        var1 = keyWordLoopInfinite_2;
                    }
                }
                nothing = "";
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
                htCodeAcurlyBraceAddSomeVrasFixNL = 1;
                lineDone = 1;
                if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + Chr(10);
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                htCode += htCodeLoopfixa1 + Chr(10) + var1 + Chr(10);
            }
            else if (SubStr(Trim(StrLower(A_LoopField220)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop) && SubStr(Trim(StrLower(A_LoopField220)), 1, StrLen(StrLower(keyWordLoop)) + 2) != StrLower(keyWordLoop) + "% " && SubStr(Trim(StrLower(A_LoopField220)), 1, StrLen(StrLower(keyWordLoopParse))) != StrLower(keyWordLoopParse)) {
                out2 = StringTrimLeft(A_LoopField220, StrLen(keyWordLoop));
                out2 = StrReplace(out2, ":", "");
                //MsgBox % out2
                howMany_fixAindexInGoUnused++;
                //MsgBox, % out2
                out2 = Trim(out2);
                myVar = out2;
                lineYGI = expressionParserTranspiler(myVar);
                line = lineYGI;
                haveWeEverUsedAloop = 1;
                //MsgBox, % line
                if (langToConvertTo == "py") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in range(" + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + "):";
                }
                if (langToConvertTo == "js") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "cpp") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "go") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++";
                }
                if (langToConvertTo == "lua") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + " + 1 " + ", " + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "cs") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " until " + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == "rb") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..." + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "nim") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..<" + line + " + " + AHKlikeLoopsIndexedAt + ":";
                }
                if (langToConvertTo == "ahk") {
                    var1 = "Loop, " + line;
                }
                if (langToConvertTo == "swift") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " ..< " + line + " + " + AHKlikeLoopsIndexedAt;
                }
                if (langToConvertTo == "dart") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..<" + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        var1 = Trim(keyWordLoop_2) + " " + line + ":";
                    } else {
                        var1 = Trim(keyWordLoop_2) + " " + line;
                    }
                }
                nothing = "";
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
                htCodeAcurlyBraceAddSomeVrasFixNL = 1;
                if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + Chr(10);
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                lineDone = 1;
                htCode += htCodeLoopfixa1 + Chr(10) + var1 + Chr(10);
            }
            else if (SubStr(Trim(StrLower(A_LoopField220)), 1, StrLen(StrLower(keyWordLoop)) + 2) == StrLower(keyWordLoop) + "% ") {
                howMany_fixAindexInGoUnused++;
                out2 = StringTrimLeft(A_LoopField220, StrLen(keyWordLoop) + 2);
                out2 = StrReplace(out2, ":", "");
                //MsgBox % out2
                //MsgBox, % out2
                out2 = Trim(out2);
                myVar = out2;
                lineYGI = expressionParserTranspiler(myVar);
                line = lineYGI;
                haveWeEverUsedAloop = 1;
                //MsgBox, % line
                if (langToConvertTo == "py") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in range(" + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + "):";
                }
                if (langToConvertTo == "js") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "cpp") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "go") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++";
                }
                if (langToConvertTo == "lua") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + " + 1 " + ", " + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "cs") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " until " + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == "rb") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..." + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "nim") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..<" + line + " + " + AHKlikeLoopsIndexedAt + ":";
                }
                if (langToConvertTo == "ahk") {
                    var1 = "Loop, % " + line;
                }
                if (langToConvertTo == "swift") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " ..< " + line + " + " + AHKlikeLoopsIndexedAt;
                }
                if (langToConvertTo == "dart") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..<" + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        var1 = Trim(keyWordLoop_2) + " % " + line + ":";
                    } else {
                        var1 = Trim(keyWordLoop_2) + " % " + line;
                    }
                }
                nothing = "";
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
                htCodeAcurlyBraceAddSomeVrasFixNL = 1;
                if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + Chr(10);
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                lineDone = 1;
                htCode += htCodeLoopfixa1 + Chr(10) + var1 + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField220), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
                howMany_fixAindexInGoUnused++;
                var1 = StringTrimLeft(A_LoopField220, StrLen(keyWordLoopParse));
                out2 = StrReplace(out2, ":", "");
                lineDone = 1;
                line1 = Trim(StrSplit(var1, ",", 1));
                line1 = expressionParserTranspiler(line1);
                line2 = "";
                line3 = "";
                itemsOut = "";
                line2 = Trim(StrSplit(var1, ",", 2));
                line3 = Trim(StrSplit(var1, ",", 3));
                if (InStr(var1, keyWordEscpaeChar + ",")) {
                    line2 = Chr(34) + "," + Chr(34);
                    if (langToConvertTo == "py") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "js") {
                        itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "cpp") {
                        itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "go") {
                        itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ", " + Chr(34) + Chr(34) + ")";
                    }
                    if (langToConvertTo == "lua") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "cs") {
                        itemsOut = "List<string> items" + STR(AindexcharLength) + " = new List<string>(LoopParseFunc(" + line1 + ", " + line2 + "));";
                    }
                    if (langToConvertTo == "java") {
                        itemsOut = "String[] items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + Chr(34) + Chr(34) + ");";
                    }
                    if (langToConvertTo == "kt") {
                        itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "rb") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "nim") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "ahk") {
                        itemsOut = Chr(10);
                    }
                    if (langToConvertTo == "swift") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "dart") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "ts") {
                        itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "groovy") {
                        itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                } else {
                    if (line2 == "" && line3 == "") {
                        // nothing so only each char
                        if (langToConvertTo == "py") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "js") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
                        }
                        if (langToConvertTo == "cpp") {
                            itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
                        }
                        if (langToConvertTo == "go") {
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + Chr(34) + Chr(34) + ", " + Chr(34) + Chr(34) + ")";
                        }
                        if (langToConvertTo == "lua") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "cs") {
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = new List<string>(LoopParseFunc(" + line1 + "));";
                        }
                        if (langToConvertTo == "java") {
                            itemsOut = "String[] items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + Chr(34) + Chr(34) + ", " + Chr(34) + Chr(34) + ");";
                        }
                        if (langToConvertTo == "kt") {
                            itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "nim") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "ahk") {
                            itemsOut = Chr(10);
                        }
                        if (langToConvertTo == "swift") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "dart") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
                        }
                        if (langToConvertTo == "ts") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
                        }
                        if (langToConvertTo == "groovy") {
                            itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                    }
                    if (line2 != "" && line3 == "") {
                        if (InStr(line2, keyWordEscpaeChar)) {
                            line2 = Chr(34) + line2 + Chr(34);
                        }
                        if (langToConvertTo == "js") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                        }
                        if (langToConvertTo == "py") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "cpp") {
                            itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                        }
                        if (langToConvertTo == "go") {
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ", " + Chr(34) + Chr(34) + ")";
                        }
                        if (langToConvertTo == "lua") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "cs") {
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = new List<string>(LoopParseFunc(" + line1 + ", " + line2 + "));";
                        }
                        if (langToConvertTo == "java") {
                            itemsOut = "String[] items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + Chr(34) + Chr(34) + ");";
                        }
                        if (langToConvertTo == "kt") {
                            itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "nim") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "ahk") {
                            itemsOut = Chr(10);
                        }
                        if (langToConvertTo == "swift") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "dart") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                        }
                        if (langToConvertTo == "ts") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                        }
                        if (langToConvertTo == "groovy") {
                            itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                    }
                    if (line2 != "" && line3 != "") {
                        if (InStr(line2, keyWordEscpaeChar)) {
                            line2 = Chr(34) + line2 + Chr(34);
                        }
                        if (InStr(line3, keyWordEscpaeChar)) {
                            line3 = Chr(34) + line3 + Chr(34);
                        }
                        if (langToConvertTo == "js") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
                        }
                        if (langToConvertTo == "py") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "cpp") {
                            itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
                        }
                        if (langToConvertTo == "go") {
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "lua") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "cs") {
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = new List<string>(LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + "));";
                        }
                        if (langToConvertTo == "java") {
                            itemsOut = "String[] items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
                        }
                        if (langToConvertTo == "kt") {
                            itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "nim") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "ahk") {
                            itemsOut = Chr(10);
                        }
                        if (langToConvertTo == "swift") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "dart") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
                        }
                        if (langToConvertTo == "ts") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "groovy") {
                            itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                    }
                    itemsOut = StrReplace(itemsOut, keyWordEscpaeChar, Chr(92));
                }
                if (langToConvertTo == "py") {
                    var1out = itemsOut + Chr(10) + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in enumerate(items" + STR(AindexcharLength) + ", start=" + AHKlikeLoopsIndexedAt + "):";
                }
                if (langToConvertTo == "js") {
                    var1out = itemsOut + Chr(10) + "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "cpp") {
                    var1out = itemsOut + Chr(10) + "for (size_t " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".size() + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "go") {
                    var1out = itemsOut + Chr(10) + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " := range items" + STR(AindexcharLength);
                }
                if (langToConvertTo == "lua") {
                    var1out = itemsOut + Chr(10) + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in ipairs(items" + STR(AindexcharLength) + ") do";
                }
                if (langToConvertTo == "cs") {
                    var1out = itemsOut + Chr(10) + "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".Count + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1out = itemsOut + Chr(10) + "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1out = itemsOut + Chr(10) + "for ((" + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + ") in items" + STR(AindexcharLength) + ".withIndex())";
                }
                if (langToConvertTo == "rb") {
                    var1out = itemsOut + Chr(10) + "for HTVM----HTVM_FOR_hsdufosyigdydtddy_FOR_HTVM_Ruby_HTVM---HTVM-For_Ruby---AA items" + STR(AindexcharLength) + ".each_with_index do |" + keyWordALoopField + "" + STR(AindexcharLength) + " , " + keyWordAIndex + "" + STR(AindexcharLength) + "|";
                }
                if (langToConvertTo == "nim") {
                    var1out = itemsOut + Chr(10) + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + ":";
                }
                if (langToConvertTo == "ahk") {
                    if (Trim(line2) == "" && Trim(line3) == "") {
                        var1out = "Loop, Parse, " + line1;
                    }
                    if (Trim(line2) != "" && Trim(line3) == "") {
                        var1out = "Loop, Parse, " + line1 + ", " + StrReplace(StrReplace(line2, keyWordEscpaeChar, "\\"), Chr(34) + "," + Chr(34), Chr(34) + "\\," + Chr(34));
                    }
                    if (Trim(line2) != "" && Trim(line3) != "") {
                        var1out = "Loop, Parse, " + line1 + ", " + StrReplace(line2, keyWordEscpaeChar, "\\") + ", " + StrReplace(line3, keyWordEscpaeChar, "\\");
                    }
                }
                if (langToConvertTo == "swift") {
                    var1out = itemsOut + Chr(10) + "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + ") in items" + STR(AindexcharLength) + ".enumerated()";
                }
                if (langToConvertTo == "dart") {
                    var1out = itemsOut + Chr(10) + "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1out = itemsOut + Chr(10) + "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1out = itemsOut + Chr(10) + "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..<items" + STR(AindexcharLength) + ".size())";
                }
                nothing = "";
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
                //
                //
                theFixTextLoopLP = "";
                if (langToConvertTo == "cpp") {
                    theFixTextLoopLP = "std::string " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "js") {
                    theFixTextLoopLP = "const " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "go") {
                    theFixTextLoopLP = Chr(10);
                }
                if (langToConvertTo == "lua") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "cs") {
                    theFixTextLoopLP = "string " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "java") {
                    theFixTextLoopLP = "String " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "kt") {
                    theFixTextLoopLP = Chr(10);
                }
                if (langToConvertTo == "rb") {
                    theFixTextLoopLP = Chr(10);
                }
                if (langToConvertTo == "nim") {
                    theFixTextLoopLP = Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    theFixTextLoopLP = Chr(10);
                }
                if (langToConvertTo == "swift") {
                    theFixTextLoopLP = Chr(10);
                }
                if (langToConvertTo == "dart") {
                    theFixTextLoopLP = "var " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "ts") {
                    theFixTextLoopLP = "let " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "groovy") {
                    theFixTextLoopLP = "def " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                htCodeAcurlyBraceAddSomeVrasFixLP = 1;
                haveWeEverUsedAloop = 1;
                if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                    htCodeLoopfixa += "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + Chr(10);
                    htCodeLoopfixa1 = "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += Trim(keyWordLoopParse_2) + " " + StrReplace(var1, keyWordEscpaeChar, keyWordEscpaeChar_2) + ":" + Chr(10);
                    } else {
                        htCode += Trim(keyWordLoopParse_2) + " " + StrReplace(var1, keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(10);
                    }
                } else {
                    htCode += htCodeLoopfixa1 + Chr(10) + var1out + Chr(10);
                }
            }
            else if (SubStrLastChars(Trim(A_LoopField220), StrLen(keyWordInc)) == keyWordInc || SubStrLastChars(Trim(A_LoopField220), StrLen(keyWordInc + ";")) == keyWordInc + ";" && lineDone == 0) {
                if (useSemicolon == "on" || SubStrLastChars(Trim(A_LoopField220), 1) == ";") {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField220), StrLen(keyWordInc + ";")));
                } else {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField220), StrLen(keyWordInc)));
                }
                str1 = Trim(expressionParserTranspiler(str1));
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += str1 + keyWordInc_2 + ";" + Chr(10);
                    } else {
                        htCode += str1 + keyWordInc_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += str1 + " += 1" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += str1 + " = " + str1 + " + 1" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += str1 + " += 1" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += str1 + " += 1" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += str1 + "++" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += str1 + " += 1" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += str1 + "++;" + Chr(10);
                }
            }
            else if (SubStrLastChars(Trim(A_LoopField220), StrLen(keyWordDec)) == keyWordDec || SubStrLastChars(Trim(A_LoopField220), StrLen(keyWordDec + ";")) == keyWordDec + ";" && lineDone == 0) {
                if (useSemicolon == "on" || SubStrLastChars(Trim(A_LoopField220), 1) == ";") {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField220), StrLen(keyWordDec + ";")));
                } else {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField220), StrLen(keyWordDec)));
                }
                str1 = Trim(expressionParserTranspiler(str1));
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += str1 + keyWordDec_2 + ";" + Chr(10);
                    } else {
                        htCode += str1 + keyWordDec_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += str1 + " -= 1" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += str1 + " = " + str1 + " - 1" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += str1 + " -= 1" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += str1 + " -= 1" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += str1 + "--" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += str1 + " -= 1" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += str1 + "--;" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField220)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ") && langToConvertTo == langFileExtension_2) {
                htCode += keyWordInclude_2 + " " + Trim(StringTrimLeft(Trim(A_LoopField220), StrLen(StrLower(keyWordInclude) + " "))) + Chr(10);
            }
            else if (StrLower(A_LoopField220) == StrLower(keyWordGlobal) || StrLower(A_LoopField220) == StrLower(keyWordGlobal + ";")) {
                if (langToConvertTo == "ahk") {
                    htCode += "global" + Chr(10);
                }
            }
            else if (SubStr(StrLower(A_LoopField220), 1, StrLen(StrLower(keyWordAwait))) == StrLower(keyWordAwait)) {
                str1 = StringTrimLeft(A_LoopField220, StrLen(keyWordAwait));
                //MsgBox, % A_LoopField
                lineDone = 1;
                fixExpertionLineFuncOnly = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        str2 = expressionParserTranspiler(Trim(str1)) + ";";
                    } else {
                        str2 = expressionParserTranspiler(Trim(str1));
                    }
                } else {
                    if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "groovy") {
                        if (SubStrLastChars(str1, 1) == ";") {
                            str1 = StringTrimRight(str1, 1);
                        }
                    }
                    str2 = expressionParserTranspiler(Trim(str1)) + ";";
                    if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "groovy") {
                        if (SubStrLastChars(str2, 1) == ";") {
                            str2 = StringTrimRight(str2, 1);
                        }
                    }
                }
                fixExpertionLineFuncOnly = 0;
                if (langToConvertTo == "js" || langToConvertTo == "ts" || langToConvertTo == langFileExtension_2) {
                    if (langToConvertTo == langFileExtension_2) {
                        htCode += keyWordAwait_2 + str2 + Chr(10);
                    } else {
                        htCode += "await " + str2 + Chr(10);
                    }
                } else {
                    htCode += str2 + Chr(10);
                }
            }
            else if (SubStr(StrLower(A_LoopField220), 1, StrLen(StrLower(keyWordGlobal))) == StrLower(keyWordGlobal)) {
                str1 = StringTrimLeft(A_LoopField220, StrLen(keyWordGlobal));
                //MsgBox, % A_LoopField
                str1 = StrReplace(str1, ";", "");
                lineDone = 1;
                if (langToConvertTo == "py" || langToConvertTo == "ahk" || langToConvertTo == langFileExtension_2) {
                    if (langToConvertTo == langFileExtension_2) {
                        str2 = Trim(keyWordGlobal_2) + " " + str1;
                    } else {
                        str2 = "global " + StrReplace(str1, ".", "_");
                    }
                } else {
                    str2 = "";
                }
                htCode += str2 + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField220), 1, StrLen(keyWordFunc)) == StrLower(keyWordFunc) || SubStr(StrLower(A_LoopField220), 1, StrLen(StrLower(keyWordAsync) + StrLower(keyWordFunc))) == StrLower(keyWordAsync) + StrLower(keyWordFunc) && InStr(StrLower(A_LoopField220), " main(") == false && lineDone == 0) {
                lineDone = 1;
                if (SubStr(StrLower(A_LoopField220), 1, StrLen(StrLower(keyWordAsync) + StrLower(keyWordFunc))) == StrLower(keyWordAsync) + StrLower(keyWordFunc)) {
                    // is async
                    int1 = 1;
                    str1 = Trim(StringTrimLeft(A_LoopField220, StrLen(StrLower(keyWordAsync + keyWordFunc))));
                } else {
                    // is async
                    int1 = 0;
                    str1 = Trim(StringTrimLeft(A_LoopField220, StrLen(StrLower(keyWordFunc))));
                }
                if (langToConvertTo != langFileExtension_2 && langToConvertTo != "cpp" && langToConvertTo != "go" && langToConvertTo != "cs" && langToConvertTo != "java" && langToConvertTo != "kt" && langToConvertTo != "nim" && langToConvertTo != "swift" && langToConvertTo != "dart" && langToConvertTo != "ts") {
                    if (str1 != "") {
                        str4 = "";
                        std::vector<std::string> items222 = LoopParseFunc(str1, ",");
                        for (size_t A_Index222 = 0; A_Index222 < items222.size() + 0; A_Index222++) {
                            std::string A_LoopField222 = items222[A_Index222 - 0];
                            if (InStr(A_LoopField222, " := ")) {
                                if (InStr(Trim(StrSplit(A_LoopField222, " := ", 1)), " ") != true) {
                                    str4 += "optanal-HTVM-opt-parmsNOtWorking-theirewIs-a-bug-Iusfbudfbuoeshfuisbav=-fwaegs-awedsf-dd-sfgc " + A_LoopField222 + ", ";
                                } else {
                                    str4 += A_LoopField222 + ", ";
                                }
                            }
                            else if (InStr(A_LoopField222, " = ")) {
                                if (InStr(Trim(StrSplit(A_LoopField222, " = ", 1)), " ") != true) {
                                    str4 += "optanal-HTVM-opt-parmsNOtWorking-theirewIs-a-bug-Iusfbudfbuoeshfuisbav=-fwaegs-awedsf-dd-sfgc " + A_LoopField222 + ", ";
                                } else {
                                    str4 += A_LoopField222 + ", ";
                                }
                            }
                            else if (InStr(A_LoopField222, " " + Trim(keyWordAssign) + " ")) {
                                if (InStr(Trim(StrSplit(A_LoopField222, " " + Trim(keyWordAssign) + " ", 1)), " ") != true) {
                                    str4 += "optanal-HTVM-opt-parmsNOtWorking-theirewIs-a-bug-Iusfbudfbuoeshfuisbav=-fwaegs-awedsf-dd-sfgc " + A_LoopField222 + ", ";
                                } else {
                                    str4 += A_LoopField222 + ", ";
                                }
                            } else {
                                str4 += A_LoopField222 + ", ";
                            }
                        }
                        str1 = StringTrimRight(str4, 2);
                        str1 = StrReplace(str1, "  ", " ");
                    }
                }
                str4 = "";
                str1 = Trim(str1);
                if (usePrefixTypeForTypeDefinition == "on") {
                    str2 = Trim(StrSplit(str1, "(", 1));
                    // func body
                    str1 = Trim(StringTrimLeft(str1, StrLen(str2)));
                    str1 = StringTrimRight(str1, 1);
                    // type of the func
                    str3 = Trim(StringTrimRight(str2, StrLen(StrSplit(str2, " ", countChars(str2, " ") + 1))));
                    // name of func
                    str2 = Trim(StrSplit(str2, " ", countChars(str2, " ") + 1));
                }
                if (usePostfixTypeForTypeDefinition == "on") {
                    // name of func
                    str2 = Trim(StrSplit(str1, "(", 1));
                    // func body
                    str1 = Trim(StringTrimLeft(str1, StrLen(str2)));
                    // type of the func
                    str3 = Trim(StrSplit(str1, ")", countChars(str1, ")") + 1));
                    str3 = StringTrimLeft(str3, 1);
                    str1 = Trim(StringTrimRight(str1, StrLen(str3) + 2));
                }
                str1 = StringTrimLeft(str1, 1);
                str3 = Trim(str3);
                if (Trim(str1) == "") {
                    if (langToConvertTo == langFileExtension_2) {
                        if (int1 == 1) {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                htCode += keyWordAsync_2 + keyWordFunc_2 + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                            } else {
                                htCode += keyWordAsync_2 + keyWordFunc_2 + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                htCode += keyWordFunc_2 + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                            } else {
                                htCode += keyWordFunc_2 + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        }
                    }
                    availableFuncsInHTVMInHTVM += str2 + Chr(10);
                    if (langToConvertTo == "cpp") {
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "py") {
                        htCode += "def " + str2 + "():" + Chr(10);
                    }
                    if (langToConvertTo == "js") {
                        if (int1 == 1) {
                            htCode += "async function " + str2 + "()" + Chr(10);
                        } else {
                            if (useJavaScriptAllFuncsAreAsync == "on") {
                                htCode += "async function " + str2 + "()" + Chr(10);
                            } else {
                                htCode += "function " + str2 + "()" + Chr(10);
                            }
                        }
                    }
                    // Go
                    if (langToConvertTo == "go") {
                        if (str3 == keyWordVoid) {
                            htCode += "func " + str2 + "()" + Chr(10);
                        } else {
                            htCode += "func " + str2 + "() " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "lua") {
                        htCode += "function " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "cs") {
                        htCode += "static " + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "java") {
                        htCode += "public static " + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "kt") {
                        if (str3 == keyWordVoid) {
                            htCode += "fun " + str2 + "()" + Chr(10);
                        } else {
                            htCode += "fun " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "rb") {
                        htCode += "def " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == keyWordVoid) {
                            htCode += "proc " + str2 + "() =" + Chr(10);
                        } else {
                            htCode += "proc " + str2 + "(): " + getFuncTypeConvert(str3) + " =" + Chr(10);
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        htCode += str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == keyWordVoid) {
                            htCode += "func " + str2 + "()" + Chr(10);
                        } else {
                            htCode += "func " + str2 + "() -> " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "dart") {
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "ts") {
                        if (int1 == 1) {
                            htCode += "async function " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                        } else {
                            if (useJavaScriptAllFuncsAreAsync == "on") {
                                htCode += "async function " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                            } else {
                                htCode += "function " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        htCode += "def " + str2 + "()" + Chr(10);
                    }
                } else {
                    str4 = "";
                    str5 = "";
                    str6 = "";
                    str7 = "";
                    str8 = "";
                    str9 = "";
                    str10 = "";
                    str11 = "";
                    str12 = "";
                    str13 = "";
                    str14 = "";
                    str15 = "";
                    str16 = "";
                    str17 = "";
                    str18 = "";
                    str19 = "";
                    str20 = "";
                    std::vector<std::string> items223 = LoopParseFunc(str1, ",");
                    for (size_t A_Index223 = 0; A_Index223 < items223.size() + 0; A_Index223++) {
                        std::string A_LoopField223 = items223[A_Index223 - 0];
                        //print("|" . Trim(A_LoopField) . "|")
                        if (InStr(Trim(A_LoopField223), " ")) {
                            // there is space aka there is a type
                            if (InStr(A_LoopField223, " " + Trim(keyWordAssign) + " ") == false) {
                                if (usePrefixTypeForTypeDefinition == "on") {
                                    // normal
                                    str6 = Trim(A_LoopField223);
                                    str7 = getTheLastWord(str6);
                                    str8 = getFuncTypeConvert(Trim(StringTrimRight(str6, StrLen(Trim(str7)) + 1)));
                                    // str5 .= str8 . " " . str7 . Chr(10)
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    // save to str5
                                    // str8 = the type
                                    // str7 = variable name
                                    if (langToConvertTo == langFileExtension_2) {
                                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                                            str5 += str8 + " " + str7 + Chr(10);
                                        } else {
                                            str5 += str7 + ": " + str8 + Chr(10);
                                        }
                                    }
                                    if (langToConvertTo == "cpp") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "py") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "js") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "go") {
                                        str5 += str7 + " " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "lua") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "cs") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "java") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "kt") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "rb") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "nim") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "ahk") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "swift") {
                                        str5 += "_ " + str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "dart") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "ts") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "groovy") {
                                        str5 += str7 + Chr(10);
                                    }
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                } else {
                                    // not normal
                                    str6 = Trim(A_LoopField223);
                                    str7 = Trim(StrSplit(str6, ":", 1));
                                    str8 = getFuncTypeConvert(Trim(StrSplit(str6, ":", 2)));
                                    // str5 .= str7 . " :" . str8 . Chr(10)
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    // save to str5
                                    // str8 = the type
                                    // str7 = variable name
                                    if (langToConvertTo == langFileExtension_2) {
                                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                                            str5 += str8 + " " + str7 + Chr(10);
                                        } else {
                                            str5 += str7 + ": " + str8 + Chr(10);
                                        }
                                    }
                                    if (langToConvertTo == "cpp") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "py") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "js") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "go") {
                                        str5 += str7 + " " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "lua") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "cs") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "java") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "kt") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "rb") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "nim") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "ahk") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "swift") {
                                        str5 += "_ " + str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "dart") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "ts") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "groovy") {
                                        str5 += str7 + Chr(10);
                                    }
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                }
                            } else {
                                // optanal param
                                if (InStr(Trim(StrSplit(Trim(A_LoopField223), " " + Trim(keyWordAssign) + " ", 1)), " ")) {
                                    // there is a type
                                    if (usePrefixTypeForTypeDefinition == "on") {
                                        // normal
                                        str6 = Trim(StrSplit(Trim(A_LoopField223), " " + Trim(keyWordAssign) + " ", 1));
                                        str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField223), " " + Trim(keyWordAssign) + " ", 2))));
                                        str7 = getTheLastWord(str6);
                                        str8 = getFuncTypeConvert(Trim(StringTrimRight(str6, StrLen(Trim(str7)) + 1)));
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;; optanal param ;;;;;;;;;;;;;;;;;
                                        // save to str10
                                        // str8 = the type
                                        // str7 = variable name
                                        // str9 = after the keyWordAssign
                                        if (langToConvertTo == langFileExtension_2) {
                                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                                str10 += str8 + " " + str7 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                            } else {
                                                str10 += str7 + ": " + str8 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                            }
                                        }
                                        if (langToConvertTo == "cpp") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "py") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "js") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "go") {
                                            skipLeftCuleyForFuncPLS = 1;
                                            str10 += str7 + " " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "lua") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "cs") {
                                            if (RegExMatch(str9, "^-?\\d+(\\.\\d+)?$")) {
                                                str10 += str8 + " " + str7 + " = " + str9 + "f" + Chr(10);
                                            } else {
                                                str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                            }
                                        }
                                        if (langToConvertTo == "java") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "kt") {
                                            if (RegExMatch(str9, "^-?\\d+(\\.\\d+)?$")) {
                                                str10 += str7 + ": " + str8 + " = " + str9 + "f" + Chr(10);
                                            } else {
                                                str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                            }
                                        }
                                        if (langToConvertTo == "rb") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "nim") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "ahk") {
                                            str10 += str7 + " := " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "swift") {
                                            str10 += "_ " + str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "dart") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "ts") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "groovy") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        // str10
                                        // skipLeftCuleyForFuncPLS := 1
                                    } else {
                                        // not normal
                                        str6 = Trim(StrSplit(Trim(A_LoopField223), " " + Trim(keyWordAssign) + " ", 1));
                                        str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField223), " " + Trim(keyWordAssign) + " ", 2))));
                                        str7 = Trim(StrSplit(str6, ":", 1));
                                        str8 = getFuncTypeConvert(Trim(StrSplit(str6, ":", 2)));
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;; optanal param ;;;;;;;;;;;;;;;;;
                                        // save to str10
                                        // str8 = the type
                                        // str7 = variable name
                                        // str9 = after the keyWordAssign
                                        if (langToConvertTo == langFileExtension_2) {
                                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                                str10 += str8 + " " + str7 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                            } else {
                                                str10 += str7 + ": " + str8 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                            }
                                        }
                                        if (langToConvertTo == "cpp") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "py") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "js") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "go") {
                                            skipLeftCuleyForFuncPLS = 1;
                                            str10 += str7 + " " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "lua") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "cs") {
                                            if (RegExMatch(str9, "^-?\\d+(\\.\\d+)?$")) {
                                                str10 += str8 + " " + str7 + " = " + str9 + "f" + Chr(10);
                                            } else {
                                                str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                            }
                                        }
                                        if (langToConvertTo == "java") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "kt") {
                                            if (RegExMatch(str9, "^-?\\d+(\\.\\d+)?$")) {
                                                str10 += str7 + ": " + str8 + " = " + str9 + "f" + Chr(10);
                                            } else {
                                                str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                            }
                                        }
                                        if (langToConvertTo == "rb") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "nim") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "ahk") {
                                            str10 += str7 + " := " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "swift") {
                                            str10 += "_ " + str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "dart") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "ts") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "groovy") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        // str10
                                        // skipLeftCuleyForFuncPLS := 1
                                    }
                                } else {
                                    // there is no type
                                    str8 = Trim(StrSplit(Trim(A_LoopField223), " " + Trim(keyWordAssign) + " ", 1));
                                    str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField223), " " + Trim(keyWordAssign) + " ", 2))));
                                    // str10
                                    // skipLeftCuleyForFuncPLS := 1
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;; optanal param ;;;;;;;;;;;;;;;;;
                                    // save to str10
                                    // str8 = variable name
                                    // str9 = after the keyWordAssign
                                    if (langToConvertTo == langFileExtension_2) {
                                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                                            str10 += str7 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                        } else {
                                            str10 += str7 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                        }
                                    }
                                    if (langToConvertTo == "py") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                    }
                                    if (langToConvertTo == "js") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                    }
                                    if (langToConvertTo == "lua") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                        skipLeftCuleyForFuncPLS = 1;
                                    }
                                    if (langToConvertTo == "rb") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                    }
                                    if (langToConvertTo == "ahk") {
                                        str10 += str7 + " := " + str9 + Chr(10);
                                    }
                                    if (langToConvertTo == "groovy") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                    }
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                }
                            }
                        } else {
                            str5 += Trim(A_LoopField223) + Chr(10);
                        }
                    }
                    //print(str5)
                    //print(str10)
                    if (Trim(str5) != "") {
                        str5 = StringTrimRight(str5, 1);
                    }
                    if (Trim(str10) != "") {
                        str10 = StringTrimRight(str10, 1);
                    }
                    str5 = Trim(str5);
                    str10 = Trim(str10);
                    if (Trim(str5) != "" && Trim(str10) != "") {
                        std::vector<std::string> items224 = LoopParseFunc(str5, "\n", "\r");
                        for (size_t A_Index224 = 0; A_Index224 < items224.size() + 0; A_Index224++) {
                            std::string A_LoopField224 = items224[A_Index224 - 0];
                            str11 += A_LoopField224 + ", ";
                        }
                        std::vector<std::string> items225 = LoopParseFunc(str10, "\n", "\r");
                        for (size_t A_Index225 = 0; A_Index225 < items225.size() + 0; A_Index225++) {
                            std::string A_LoopField225 = items225[A_Index225 - 0];
                            str12 += A_LoopField225 + ", ";
                        }
                        str12 = StringTrimRight(str12, 2);
                        if (langToConvertTo == "dart") {
                            str12 = "[" + str12 + "]";
                        }
                        if (langToConvertTo == "lua") {
                            std::vector<std::string> items226 = LoopParseFunc(str12, ",");
                            for (size_t A_Index226 = 0; A_Index226 < items226.size() + 0; A_Index226++) {
                                std::string A_LoopField226 = items226[A_Index226 - 0];
                                str14 += Trim(StrSplit(Trim(A_LoopField226), " = ", 1)) + ", ";
                            }
                            str14 = StringTrimRight(str14, 2);
                            str13 += "{" + Chr(10);
                            std::vector<std::string> items227 = LoopParseFunc(str12, ",");
                            for (size_t A_Index227 = 0; A_Index227 < items227.size() + 0; A_Index227++) {
                                std::string A_LoopField227 = items227[A_Index227 - 0];
                                str13 += Trim(StrSplit(Trim(A_LoopField227), " = ", 1)) + " = " + Trim(StrSplit(Trim(A_LoopField227), " = ", 1)) + " or " + Trim(StrSplit(Trim(A_LoopField227), " = ", 2)) + Chr(10);
                            }
                            str12 = str14;
                        }
                        if (langToConvertTo == "go") {
                            str14 = "__HTVM_V2_TO_GO_optionalParams__ ...interface{}";
                            str13 += "{" + Chr(10) + " ";
                            std::vector<std::string> items228 = LoopParseFunc(str12, ",");
                            for (size_t A_Index228 = 0; A_Index228 < items228.size() + 0; A_Index228++) {
                                std::string A_LoopField228 = items228[A_Index228 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField228), " = ", 1)), " ", 1));
                                str17 = Trim(StrSplit(Trim(A_LoopField228), " = ", 2));
                                str13 += str16 + " := " + str17 + Chr(10);
                            }
                            std::vector<std::string> items229 = LoopParseFunc(str12, ",");
                            for (size_t A_Index229 = 0; A_Index229 < items229.size() + 0; A_Index229++) {
                                std::string A_LoopField229 = items229[A_Index229 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField229), " = ", 1)), " ", 1));
                                str18 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField229), " = ", 1)), " ", 2));
                                // str16 = var name
                                // str18 = var type
                                str13 += "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " " + STR(A_Index229) + Chr(10) + "{" + Chr(10) + str16 + " = __HTVM_V2_TO_GO_optionalParams__[" + STR(A_Index229) + "].(" + str18 + ")" + Chr(10) + "}" + Chr(10);
                            }
                            str12 = str14;
                        }
                        if (langToConvertTo == "java") {
                            str14 = "Object... __HTVM_V2_TO_JAVA_optionalParams__";
                            str13 += "{" + Chr(10);
                            std::vector<std::string> items230 = LoopParseFunc(str12, ",");
                            for (size_t A_Index230 = 0; A_Index230 < items230.size() + 0; A_Index230++) {
                                std::string A_LoopField230 = items230[A_Index230 - 0];
                                str19 = Trim(A_LoopField230);
                                str20 = "";
                                std::vector<std::string> items231 = LoopParseFunc(str19, " ");
                                for (size_t A_Index231 = 0; A_Index231 < items231.size() + 0; A_Index231++) {
                                    std::string A_LoopField231 = items231[A_Index231 - 0];
                                    if (A_Index231 == 3) {
                                        if (RegExMatch(A_LoopField231, "^-?\\d+(\\.\\d+)?$")) {
                                            str20 += A_LoopField231 + "f ";
                                        } else {
                                            str20 += A_LoopField231 + " ";
                                        }
                                    } else {
                                        str20 += A_LoopField231 + " ";
                                    }
                                }
                                str20 = StringTrimRight(str20, 1);
                                str13 += Trim(str20) + ";" + Chr(10);
                            }
                            std::vector<std::string> items232 = LoopParseFunc(str12, ",");
                            for (size_t A_Index232 = 0; A_Index232 < items232.size() + 0; A_Index232++) {
                                std::string A_LoopField232 = items232[A_Index232 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField232), " = ", 1)), " ", 2));
                                str17 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField232), " = ", 1)), " ", 1));
                                // str16 = var name
                                // str17 = type name
                                str13 += "if (__HTVM_V2_TO_JAVA_optionalParams__.length " + Chr(62) + " " + STR(A_Index232) + ") " + str16 + " = (" + str17 + ") __HTVM_V2_TO_JAVA_optionalParams__[" + STR(A_Index232) + "];" + Chr(10);
                            }
                            str12 = str14;
                        }
                        str11 += str12;
                    }
                    if (Trim(str5) != "" && Trim(str10) == "") {
                        std::vector<std::string> items233 = LoopParseFunc(str5, "\n", "\r");
                        for (size_t A_Index233 = 0; A_Index233 < items233.size() + 0; A_Index233++) {
                            std::string A_LoopField233 = items233[A_Index233 - 0];
                            str11 += A_LoopField233 + ", ";
                        }
                        str11 = StringTrimRight(str11, 2);
                    }
                    if (Trim(str5) == "" && Trim(str10) != "") {
                        std::vector<std::string> items234 = LoopParseFunc(str10, "\n", "\r");
                        for (size_t A_Index234 = 0; A_Index234 < items234.size() + 0; A_Index234++) {
                            std::string A_LoopField234 = items234[A_Index234 - 0];
                            str11 += A_LoopField234 + ", ";
                        }
                        str11 = StringTrimRight(str11, 2);
                        if (langToConvertTo == "dart") {
                            str11 = "[" + str11 + "]";
                        }
                        if (langToConvertTo == "lua") {
                            std::vector<std::string> items235 = LoopParseFunc(str11, ",");
                            for (size_t A_Index235 = 0; A_Index235 < items235.size() + 0; A_Index235++) {
                                std::string A_LoopField235 = items235[A_Index235 - 0];
                                str14 += Trim(StrSplit(Trim(A_LoopField235), " = ", 1)) + ", ";
                            }
                            str14 = StringTrimRight(str14, 2);
                            str13 += "{" + Chr(10);
                            std::vector<std::string> items236 = LoopParseFunc(str11, ",");
                            for (size_t A_Index236 = 0; A_Index236 < items236.size() + 0; A_Index236++) {
                                std::string A_LoopField236 = items236[A_Index236 - 0];
                                str13 += Trim(StrSplit(Trim(A_LoopField236), " = ", 1)) + " = " + Trim(StrSplit(Trim(A_LoopField236), " = ", 1)) + " or " + Trim(StrSplit(Trim(A_LoopField236), " = ", 2)) + Chr(10);
                            }
                            str11 = str14;
                        }
                        if (langToConvertTo == "go") {
                            str14 = "__HTVM_V2_TO_GO_optionalParams__ ...interface{}";
                            str13 += "{" + Chr(10) + " ";
                            std::vector<std::string> items237 = LoopParseFunc(str11, ",");
                            for (size_t A_Index237 = 0; A_Index237 < items237.size() + 0; A_Index237++) {
                                std::string A_LoopField237 = items237[A_Index237 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField237), " = ", 1)), " ", 1));
                                str17 = Trim(StrSplit(Trim(A_LoopField237), " = ", 2));
                                str13 += str16 + " := " + str17 + Chr(10);
                            }
                            std::vector<std::string> items238 = LoopParseFunc(str11, ",");
                            for (size_t A_Index238 = 0; A_Index238 < items238.size() + 0; A_Index238++) {
                                std::string A_LoopField238 = items238[A_Index238 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField238), " = ", 1)), " ", 1));
                                str18 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField238), " = ", 1)), " ", 2));
                                // str16 = var name
                                // str18 = var type
                                str13 += "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " " + STR(A_Index238) + Chr(10) + "{" + Chr(10) + str16 + " = __HTVM_V2_TO_GO_optionalParams__[" + STR(A_Index238) + "].(" + str18 + ")" + Chr(10) + "}" + Chr(10);
                            }
                            str11 = str14;
                        }
                        if (langToConvertTo == "java") {
                            str14 = "Object... __HTVM_V2_TO_JAVA_optionalParams__";
                            str13 += "{" + Chr(10);
                            std::vector<std::string> items239 = LoopParseFunc(str11, ",");
                            for (size_t A_Index239 = 0; A_Index239 < items239.size() + 0; A_Index239++) {
                                std::string A_LoopField239 = items239[A_Index239 - 0];
                                str19 = Trim(A_LoopField239);
                                str20 = "";
                                std::vector<std::string> items240 = LoopParseFunc(str19, " ");
                                for (size_t A_Index240 = 0; A_Index240 < items240.size() + 0; A_Index240++) {
                                    std::string A_LoopField240 = items240[A_Index240 - 0];
                                    if (A_Index240 == 3) {
                                        if (RegExMatch(A_LoopField240, "^-?\\d+(\\.\\d+)?$")) {
                                            str20 += A_LoopField240 + "f ";
                                        } else {
                                            str20 += A_LoopField240 + " ";
                                        }
                                    } else {
                                        str20 += A_LoopField240 + " ";
                                    }
                                }
                                str20 = StringTrimRight(str20, 1);
                                str13 += Trim(str20) + ";" + Chr(10);
                            }
                            std::vector<std::string> items241 = LoopParseFunc(str11, ",");
                            for (size_t A_Index241 = 0; A_Index241 < items241.size() + 0; A_Index241++) {
                                std::string A_LoopField241 = items241[A_Index241 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField241), " = ", 1)), " ", 2));
                                str17 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField241), " = ", 1)), " ", 1));
                                // str16 = var name
                                // str17 = type name
                                str13 += "if (__HTVM_V2_TO_JAVA_optionalParams__.length " + Chr(62) + " " + STR(A_Index241) + ") " + str16 + " = (" + str17 + ") __HTVM_V2_TO_JAVA_optionalParams__[" + STR(A_Index241) + "];" + Chr(10);
                            }
                            str11 = str14;
                        }
                    }
                    //print(str11)
                    //;;;;;;; last put all
                    //;;;;;;; last put all
                    //;;;;;;; last put all
                    if (langToConvertTo == langFileExtension_2) {
                        if (int1 == 1) {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                htCode += keyWordAsync_2 + keyWordFunc_2 + getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                            } else {
                                htCode += keyWordAsync_2 + keyWordFunc_2 + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                htCode += keyWordFunc_2 + getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                            } else {
                                htCode += keyWordFunc_2 + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        }
                    }
                    availableFuncsInHTVMInHTVM += str2 + Chr(10);
                    if (langToConvertTo == "cpp") {
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "py") {
                        htCode += "def " + str2 + "(" + str11 + "):" + Chr(10);
                    }
                    if (langToConvertTo == "js") {
                        if (int1 == 1) {
                            htCode += "async function " + str2 + "(" + str11 + ")" + Chr(10);
                        } else {
                            if (useJavaScriptAllFuncsAreAsync == "on") {
                                htCode += "async function " + str2 + "(" + str11 + ")" + Chr(10);
                            } else {
                                htCode += "function " + str2 + "(" + str11 + ")" + Chr(10);
                            }
                        }
                    }
                    // Go
                    if (langToConvertTo == "go") {
                        if (str3 == keyWordVoid) {
                            htCode += "func " + str2 + "(" + str11 + ")" + Chr(10) + str13;
                        } else {
                            htCode += "func " + str2 + "(" + str11 + ") " + getFuncTypeConvert(str3) + Chr(10) + str13;
                        }
                    }
                    if (langToConvertTo == "lua") {
                        htCode += "function " + str2 + "(" + str11 + ")" + Chr(10) + str13;
                    }
                    if (langToConvertTo == "cs") {
                        htCode += "static " + getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "java") {
                        htCode += "public static " + getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10) + str13;
                    }
                    if (langToConvertTo == "kt") {
                        if (str3 == keyWordVoid) {
                            htCode += "fun " + str2 + "(" + str11 + ")" + Chr(10);
                        } else {
                            htCode += "fun " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "rb") {
                        htCode += "def " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == keyWordVoid) {
                            htCode += "proc " + str2 + "(" + str11 + ") =" + Chr(10);
                        } else {
                            htCode += "proc " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + " =" + Chr(10);
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        htCode += str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == keyWordVoid) {
                            htCode += "func " + str2 + "(" + str11 + ")" + Chr(10);
                        } else {
                            htCode += "func " + str2 + "(" + str11 + ") -> " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "dart") {
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "ts") {
                        if (int1 == 1) {
                            htCode += "async function " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                        } else {
                            if (useJavaScriptAllFuncsAreAsync == "on") {
                                htCode += "async function " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                            } else {
                                htCode += "function " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        htCode += "def " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    //;;;;;;; last put all
                    //;;;;;;; last put all
                    //;;;;;;; last put all
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode = StringTrimRight(htCode, 1);
                        htCode += ":" + Chr(10);
                    }
                }
            }
            else if (InStr(StrLower(A_LoopField220), " main(") && lineDone == 0) {
                lineDone = 1;
                javaMainFuncSeen = 1;
                csMainFuncSeen = 1;
                htCode += A_LoopField220 + Chr(10);
            }
            else if (InStr(A_LoopField220, " " + keyWordAssign + " ") || InStr(A_LoopField220, " " + keyWordAssignAdd + " ") || InStr(A_LoopField220, " " + keyWordAssignConcat + " ") || InStr(A_LoopField220, " " + keyWordAssignSub + " ") || InStr(A_LoopField220, " " + keyWordAssignMul + " ") || InStr(A_LoopField220, " " + keyWordAssignDiv + " ") || InStr(A_LoopField220, " " + keyWordAssignMod + " ") || InStr(A_LoopField220, " " + keyWordAssignShiftLeft + " ") || InStr(A_LoopField220, " " + keyWordAssignShiftRight + " ") || InStr(A_LoopField220, " " + keyWordLogicalAssignShiftRight + " ") || InStr(A_LoopField220, " " + keyWordAssignBitAnd + " ") || InStr(A_LoopField220, " " + keyWordAssignBitOr + " ") || InStr(A_LoopField220, " " + keyWordAssignBitXor + " ") && lineDone == 0) {
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                //keyWordAssign
                //keyWordAssignAdd
                //keyWordAssignConcat
                //keyWordAssignSub
                //keyWordAssignMul
                //keyWordAssignDiv
                //keyWordAssignMod
                //keyWordAssignShiftLeft
                //keyWordAssignShiftRight
                //keyWordLogicalAssignShiftRight
                //keyWordAssignBitAnd
                //keyWordAssignBitOr
                //keyWordAssignBitXor
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //allVarsSoWeDontReDecVars
                //allVarsSoWeDontReDecVars_FIX_uint8
                //allVarsSoWeDontReDecVars_FIX_uint16
                //allVarsSoWeDontReDecVars_FIX_uint32
                //allVarsSoWeDontReDecVars_FIX_uint64
                //allVarsSoWeDontReDecVars_FIX_int64
                //allVarsSoWeDontReDecVars_FIX_float
                if (InStr(A_LoopField220, " " + keyWordAssign + " ")) {
                    str1 = StrSplit(A_LoopField220, " " + keyWordAssign + " ", 1);
                    str6 = StrSplit(A_LoopField220, " " + keyWordAssign + " ", 2);
                    str10 = keyWordAssign;
                    str11 = keyWordAssign_2;
                    if (langToConvertTo == "ahk") {
                        str12 = ":=";
                    } else {
                        str12 = "=";
                    }
                }
                else if (InStr(A_LoopField220, " " + keyWordAssignAdd + " ")) {
                    str1 = StrSplit(A_LoopField220, " " + keyWordAssignAdd + " ", 1);
                    str6 = StrSplit(A_LoopField220, " " + keyWordAssignAdd + " ", 2);
                    str10 = keyWordAssignAdd;
                    str11 = keyWordAssignAdd_2;
                    str12 = "+=";
                }
                else if (InStr(A_LoopField220, " " + keyWordAssignConcat + " ")) {
                    str1 = StrSplit(A_LoopField220, " " + keyWordAssignConcat + " ", 1);
                    str6 = StrSplit(A_LoopField220, " " + keyWordAssignConcat + " ", 2);
                    str10 = keyWordAssignConcat;
                    str11 = keyWordAssignConcat_2;
                    if (langToConvertTo == "ahk") {
                        str12 = ".=";
                    } else {
                        str12 = "+=";
                    }
                }
                else if (InStr(A_LoopField220, " " + keyWordAssignSub + " ")) {
                    str1 = StrSplit(A_LoopField220, " " + keyWordAssignSub + " ", 1);
                    str6 = StrSplit(A_LoopField220, " " + keyWordAssignSub + " ", 2);
                    str10 = keyWordAssignSub;
                    str11 = keyWordAssignSub_2;
                    str12 = "-=";
                }
                else if (InStr(A_LoopField220, " " + keyWordAssignMul + " ")) {
                    str1 = StrSplit(A_LoopField220, " " + keyWordAssignMul + " ", 1);
                    str6 = StrSplit(A_LoopField220, " " + keyWordAssignMul + " ", 2);
                    str10 = keyWordAssignMul;
                    str11 = keyWordAssignMul_2;
                    str12 = "*=";
                }
                else if (InStr(A_LoopField220, " " + keyWordAssignDiv + " ")) {
                    str1 = StrSplit(A_LoopField220, " " + keyWordAssignDiv + " ", 1);
                    str6 = StrSplit(A_LoopField220, " " + keyWordAssignDiv + " ", 2);
                    str10 = keyWordAssignDiv;
                    str11 = keyWordAssignDiv_2;
                    str12 = "/=";
                }
                else if (InStr(A_LoopField220, " " + keyWordAssignMod + " ")) {
                    str1 = StrSplit(A_LoopField220, " " + keyWordAssignMod + " ", 1);
                    str6 = StrSplit(A_LoopField220, " " + keyWordAssignMod + " ", 2);
                    str10 = keyWordAssignMod;
                    str11 = keyWordAssignMod_2;
                    str12 = "%=";
                }
                else if (InStr(A_LoopField220, " " + keyWordAssignShiftLeft + " ")) {
                    str1 = StrSplit(A_LoopField220, " " + keyWordAssignShiftLeft + " ", 1);
                    str6 = StrSplit(A_LoopField220, " " + keyWordAssignShiftLeft + " ", 2);
                    str10 = keyWordAssignShiftLeft;
                    str11 = keyWordAssignShiftLeft_2;
                    str12 = "<<=";
                }
                else if (InStr(A_LoopField220, " " + keyWordAssignShiftRight + " ")) {
                    str1 = StrSplit(A_LoopField220, " " + keyWordAssignShiftRight + " ", 1);
                    str6 = StrSplit(A_LoopField220, " " + keyWordAssignShiftRight + " ", 2);
                    str10 = keyWordAssignShiftRight;
                    str11 = keyWordAssignShiftRight_2;
                    str12 = ">>=";
                }
                else if (InStr(A_LoopField220, " " + keyWordLogicalAssignShiftRight + " ")) {
                    str1 = StrSplit(A_LoopField220, " " + keyWordLogicalAssignShiftRight + " ", 1);
                    str6 = StrSplit(A_LoopField220, " " + keyWordLogicalAssignShiftRight + " ", 2);
                    str10 = keyWordLogicalAssignShiftRight;
                    str11 = keyWordLogicalAssignShiftRight_2;
                    str12 = ">>>=";
                }
                else if (InStr(A_LoopField220, " " + keyWordAssignBitAnd + " ")) {
                    str1 = StrSplit(A_LoopField220, " " + keyWordAssignBitAnd + " ", 1);
                    str6 = StrSplit(A_LoopField220, " " + keyWordAssignBitAnd + " ", 2);
                    str10 = keyWordAssignBitAnd;
                    str11 = keyWordAssignBitAnd_2;
                    str12 = "&=";
                }
                else if (InStr(A_LoopField220, " " + keyWordAssignBitOr + " ")) {
                    str1 = StrSplit(A_LoopField220, " " + keyWordAssignBitOr + " ", 1);
                    str6 = StrSplit(A_LoopField220, " " + keyWordAssignBitOr + " ", 2);
                    str10 = keyWordAssignBitOr;
                    str11 = keyWordAssignBitOr_2;
                    str12 = "|=";
                }
                else if (InStr(A_LoopField220, " " + keyWordAssignBitXor + " ")) {
                    str1 = StrSplit(A_LoopField220, " " + keyWordAssignBitXor + " ", 1);
                    str6 = StrSplit(A_LoopField220, " " + keyWordAssignBitXor + " ", 2);
                    str10 = keyWordAssignBitXor;
                    str11 = keyWordAssignBitXor_2;
                    str12 = "^=";
                }
                str6 = Trim(expressionParserTranspiler(Trim(str6)));
                if (SubStrLastChars(str6, 1) == ";") {
                    str6 = StringTrimRight(str6, 1);
                }
                str1 = Trim(str1);
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                ALoopField = str1;
                if (InStr(ALoopField, " ") == false || SubStrLastChars(ALoopField, 1) == "]") {
                    lineDone = 1;
                    if (langToConvertTo != langFileExtension_2) {
                        str1 = StrReplace(Trim(str1), ".", "_");
                    }
                    str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str1);
                    if (InStr(saveAllArrayVarNamesSoWeCanDoAfix, "|" + Trim(str1) + "|")) {
                        str6 = Trim(str6);
                        if (SubStr(str6, 1, 1) == "[" || SubStr(str6, 1, 1) == "{") {
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                            if (langToConvertTo == "cpp") {
                                str6 = "{" + str6 + "}";
                            }
                            if (langToConvertTo == "py") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "js") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "go") {
                                str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                            }
                            if (langToConvertTo == "lua") {
                                str6 = "{" + str6 + "}";
                            }
                            if (langToConvertTo == "cs") {
                                str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                            }
                            if (langToConvertTo == "java") {
                                str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                            }
                            if (langToConvertTo == "kt") {
                                str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                            }
                            if (langToConvertTo == "rb") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "nim") {
                                str6 = "@[" + str6 + "]";
                            }
                            if (langToConvertTo == "ahk") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "swift") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "dart") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "ts") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "groovy") {
                                str6 = "[" + str6 + "]";
                            }
                        }
                    }
                    if (Trim(str6) == "[]" || Trim(str6) == "{}") {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on" && langToConvertTo == langFileExtension_2) {
                            str6 = "{}";
                        } else {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "cpp") {
                            str6 = "{}";
                        }
                        if (langToConvertTo == "py") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "js") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "go") {
                            str6 = Trim(str1) + "[:0]";
                        }
                        if (langToConvertTo == "lua") {
                            str6 = "{}";
                        }
                        if (langToConvertTo == "cs") {
                            str6 = "ResetList(" + Trim(str1) + ")";
                        }
                        if (langToConvertTo == "java") {
                            str6 = "new ArrayList<>()";
                        }
                        if (langToConvertTo == "kt") {
                            str6 = "ArrayList()";
                        }
                        if (langToConvertTo == "rb") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "nim") {
                            str6 = "@[]";
                        }
                        if (langToConvertTo == "ahk") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "swift") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "dart") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "ts") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "groovy") {
                            str6 = "[]";
                        }
                    }
                    //;;;;;;;;;;;;;;;;;
                    //;;;;;;;;;;;;;;;;;
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            str4 = str1 + " " + str11 + " " + str6 + ";";
                        } else {
                            str4 = str1 + " " + str11 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str1 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "js") {
                        str4 = str1 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "go") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "cs") {
                        str4 = str1 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "java") {
                        if (Trim(str6) == "[]" || Trim(str6) == "{}") {
                            str4 = str1 + " " + str12 + " " + str6 + ";";
                        } else {
                            if (InStr(str1, "[")) {
                                // Convert arr[something] to arr.set(something, value);
                                str1 = RegExReplace(str1, "(\\b[A-Za-z_]\\w*)\\s*\\[(.*?)\\]", "$1.set($2, ");
                                str4 = str1 + str6 + ");";
                            } else {
                                str4 = str1 + " " + str12 + " " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "nim") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "swift") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str1 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = str1 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    htCode += str4 + Chr(10);
                }
                else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordConst)) == keyWordConst && lineDone == 0) {
                    lineDone = 1;
                    if (usePostfixTypeForTypeDefinition == "off") {
                        lineDone = 1;
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordConst)));
                        std::vector<std::string> items242 = LoopParseFunc(str1, " ");
                        for (size_t A_Index242 = 0; A_Index242 < items242.size() + 0; A_Index242++) {
                            std::string A_LoopField242 = items242[A_Index242 - 0];
                            str2 = A_LoopField242;
                        }
                        str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                        str2 = Trim(str2);
                        // str2 = var name
                        // str3 = type
                        HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    } else {
                        lineDone = 1;
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordConst)));
                        str2 = Trim(StrSplit(str1, ":", 1));
                        str3 = Trim(StrSplit(str1, ":", 2));
                        // str2 = var name
                        // str3 = type
                    }
                    if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                        saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                        str3 = getFuncTypeConvert(str3);
                        int5 = 0;
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                if (int5 != 0) {
                                    str6 = "{" + str6 + "}";
                                }
                            } else {
                                if (int5 != 0) {
                                    str6 = "[" + str6 + "]";
                                }
                            }
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "py") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " [" + str6 + "]";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6 + "";
                            }
                        }
                        if (langToConvertTo == "js") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            if (int5 != 0) {
                                str4 = str2 + " := " + str3 + "{" + str6 + "}";
                            } else {
                                str4 = str2 + " := " + str3 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "lua") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " {" + str6 + "}";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = str3 + " " + str2 + " = " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "kt") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                            } else {
                                str4 = "var " + str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "rb") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "nim") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + str3 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "ahk") {
                            if (int5 != 0) {
                                str4 = str2 + " := [" + str6 + "]";
                            } else {
                                str4 = str2 + " := " + str6;
                            }
                        }
                        if (langToConvertTo == "swift") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "dart") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = [" + str6 + "];";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "ts") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                    } else {
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        str3 = getFuncTypeConvert(str3);
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = "const " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "js") {
                            str4 = "const " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "go") {
                            str4 = "const " + str2 + " " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "cs") {
                            str4 = "const " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = "final " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static final " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "val " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "const " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "let " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "dart") {
                            str4 = "final " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "const " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = "final " + str2 + " " + str12 + " " + str6;
                        }
                        //;;;
                    }
                    htCode += str4 + Chr(10);
                }
                else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordVar)) == keyWordVar && lineDone == 0) {
                    lineDone = 1;
                    if (usePostfixTypeForTypeDefinition == "off") {
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordVar)));
                        std::vector<std::string> items243 = LoopParseFunc(str1, " ");
                        for (size_t A_Index243 = 0; A_Index243 < items243.size() + 0; A_Index243++) {
                            std::string A_LoopField243 = items243[A_Index243 - 0];
                            str2 = A_LoopField243;
                        }
                        str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                        str2 = Trim(str2);
                        // str2 = var name
                        // str3 = type
                        HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    } else {
                        lineDone = 1;
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordVar)));
                        str2 = Trim(StrSplit(str1, ":", 1));
                        str3 = Trim(StrSplit(str1, ":", 2));
                        // str2 = var name
                        // str3 = type
                    }
                    if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                        saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                        str3 = getFuncTypeConvert(str3);
                        int5 = 0;
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                if (int5 != 0) {
                                    str6 = "{" + str6 + "}";
                                }
                            } else {
                                if (int5 != 0) {
                                    str6 = "[" + str6 + "]";
                                }
                            }
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordVar_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = keyWordVar_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordVar_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = keyWordVar_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "py") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " [" + str6 + "]";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6 + "";
                            }
                        }
                        if (langToConvertTo == "js") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            if (int5 != 0) {
                                str4 = str2 + " := " + str3 + "{" + str6 + "}";
                            } else {
                                str4 = str2 + " := " + str3 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "lua") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " {" + str6 + "}";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = str3 + " " + str2 + " = " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "kt") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                            } else {
                                str4 = "var " + str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "rb") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "nim") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + str3 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "ahk") {
                            if (int5 != 0) {
                                str4 = str2 + " := [" + str6 + "]";
                            } else {
                                str4 = str2 + " := " + str6;
                            }
                        }
                        if (langToConvertTo == "swift") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "dart") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = [" + str6 + "];";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "ts") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                    } else {
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        str3 = getFuncTypeConvert(str3);
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordVar_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = keyWordVar_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordVar_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = keyWordVar_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "js") {
                            str4 = "var " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "go") {
                            str4 = "var " + str2 + " " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                            // g p l | g p l | g p l | g p l |
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + "? " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        //;;;
                    }
                    htCode += str4 + Chr(10);
                }
                else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordLet)) == keyWordLet && lineDone == 0) {
                    lineDone = 1;
                    if (usePostfixTypeForTypeDefinition == "off") {
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordLet)));
                        std::vector<std::string> items244 = LoopParseFunc(str1, " ");
                        for (size_t A_Index244 = 0; A_Index244 < items244.size() + 0; A_Index244++) {
                            std::string A_LoopField244 = items244[A_Index244 - 0];
                            str2 = A_LoopField244;
                        }
                        str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                        str2 = Trim(str2);
                        // str2 = var name
                        // str3 = type
                        HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    } else {
                        lineDone = 1;
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordLet)));
                        str2 = Trim(StrSplit(str1, ":", 1));
                        str3 = Trim(StrSplit(str1, ":", 2));
                        // str2 = var name
                        // str3 = type
                        HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    }
                    if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                        saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                        str3 = getFuncTypeConvert(str3);
                        int5 = 0;
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                if (int5 != 0) {
                                    str6 = "{" + str6 + "}";
                                }
                            } else {
                                if (int5 != 0) {
                                    str6 = "[" + str6 + "]";
                                }
                            }
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordLet_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = keyWordLet_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordLet_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = keyWordLet_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "py") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " [" + str6 + "]";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6 + "";
                            }
                        }
                        if (langToConvertTo == "js") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            if (int5 != 0) {
                                str4 = str2 + " := " + str3 + "{" + str6 + "}";
                            } else {
                                str4 = str2 + " := " + str3 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "lua") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " {" + str6 + "}";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = str3 + " " + str2 + " = " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "kt") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                            } else {
                                str4 = "var " + str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "rb") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "nim") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + str3 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "ahk") {
                            if (int5 != 0) {
                                str4 = str2 + " := [" + str6 + "]";
                            } else {
                                str4 = str2 + " := " + str6;
                            }
                        }
                        if (langToConvertTo == "swift") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "dart") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = [" + str6 + "];";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "ts") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                    } else {
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        str3 = getFuncTypeConvert(str3);
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordLet_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = keyWordLet_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordLet_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = keyWordLet_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "js") {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "go") {
                            str4 = "var " + str2 + " " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "lua") {
                            str4 = "local " + str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "let " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        //;;;
                    }
                    htCode += str4 + Chr(10);
                }
                else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordDouble + " ")) == keyWordDouble + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordChar + " ")) == keyWordChar + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint8 + " ")) == keyWordUint8 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint16 + " ")) == keyWordUint16 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint32 + " ")) == keyWordUint32 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint64 + " ")) == keyWordUint64 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT + " ")) == keyWordINT + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordSTR + " ")) == keyWordSTR + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordBOOL + " ")) == keyWordBOOL + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordFLOAT + " ")) == keyWordFLOAT + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT8 + " ")) == keyWordINT8 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT16 + " ")) == keyWordINT16 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT32 + " ")) == keyWordINT32 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT64 + " ")) == keyWordINT64 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayDefinition + " ")) == keyWordArrayDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfIntegersDefinition + " ")) == keyWordArrayOfIntegersDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfStringsDefinition + " ")) == keyWordArrayOfStringsDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfFloatingPointNumbersDefinition + " ")) == keyWordArrayOfFloatingPointNumbersDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfBooleansDefinition + " ")) == keyWordArrayOfBooleansDefinition + " " && usePrefixTypeForTypeDefinition == "on" && lineDone == 0) {
                    lineDone = 1;
                    std::vector<std::string> items245 = LoopParseFunc(str1, " ");
                    for (size_t A_Index245 = 0; A_Index245 < items245.size() + 0; A_Index245++) {
                        std::string A_LoopField245 = items245[A_Index245 - 0];
                        str2 = A_LoopField245;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                        saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                        str3 = getFuncTypeConvert(str3);
                        int5 = 0;
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                if (int5 != 0) {
                                    str6 = "{" + str6 + "}";
                                }
                            } else {
                                if (int5 != 0) {
                                    str6 = "[" + str6 + "]";
                                }
                            }
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "py") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " [" + str6 + "]";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6 + "";
                            }
                        }
                        if (langToConvertTo == "js") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            if (int5 != 0) {
                                str4 = str2 + " := " + str3 + "{" + str6 + "}";
                            } else {
                                str4 = str2 + " := " + str3 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "lua") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " {" + str6 + "}";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = str3 + " " + str2 + " = " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "kt") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                            } else {
                                str4 = "var " + str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "rb") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "nim") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + str3 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "ahk") {
                            if (int5 != 0) {
                                str4 = str2 + " := [" + str6 + "]";
                            } else {
                                str4 = str2 + " := " + str6;
                            }
                        }
                        if (langToConvertTo == "swift") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "dart") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = [" + str6 + "];";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "ts") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                    } else {
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        str3 = getFuncTypeConvert(str3);
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "js") {
                            if (useInJavaScriptAlwaysUseVar == "on") {
                                str4 = "var " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            str4 = "var " + str2 + " " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2  + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "ts") {
                            if (useInJavaScriptAlwaysUseVar == "on") {
                                str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        //;;;
                    }
                    htCode += str4 + Chr(10);
                }
                else if (RegExMatch(Trim(str1), "^[a-zA-Z_][a-zA-Z_0-9]*:\\s?.*$") && usePostfixTypeForTypeDefinition == "on" && lineDone == 0) {
                    lineDone = 1;
                    str2 = Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                        saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                        str3 = getFuncTypeConvert(str3);
                        int5 = 0;
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                if (int5 != 0) {
                                    str6 = "{" + str6 + "}";
                                }
                            } else {
                                if (int5 != 0) {
                                    str6 = "[" + str6 + "]";
                                }
                            }
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "py") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " [" + str6 + "]";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6 + "";
                            }
                        }
                        if (langToConvertTo == "js") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            if (int5 != 0) {
                                str4 = str2 + " := " + str3 + "{" + str6 + "}";
                            } else {
                                str4 = str2 + " := " + str3 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "lua") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " {" + str6 + "}";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = str3 + " " + str2 + " = " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "kt") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                            } else {
                                str4 = "var " + str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "rb") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "nim") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + str3 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "ahk") {
                            if (int5 != 0) {
                                str4 = str2 + " := [" + str6 + "]";
                            } else {
                                str4 = str2 + " := " + str6;
                            }
                        }
                        if (langToConvertTo == "swift") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "dart") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = [" + str6 + "];";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "ts") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                    } else {
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        str3 = getFuncTypeConvert(str3);
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "js") {
                            if (useInJavaScriptAlwaysUseVar == "on") {
                                str4 = "var " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            str4 = "var " + str2 + " " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "ts") {
                            if (useInJavaScriptAlwaysUseVar == "on") {
                                str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = str2 + " " + str12 + " " + str6 + ";";
                        }
                        //;;;
                    }
                    htCode += str4 + Chr(10);
                }
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if (SubStr(Trim(A_LoopField220), 1, StrLen(keyWordVar)) == keyWordVar && lineDone == 0) {
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField220), StrLen(keyWordVar)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    std::vector<std::string> items246 = LoopParseFunc(str1, " ");
                    for (size_t A_Index246 = 0; A_Index246 < items246.size() + 0; A_Index246++) {
                        std::string A_LoopField246 = items246[A_Index246 - 0];
                        str2 = A_LoopField246;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField220), StrLen(keyWordVar)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    str2 = Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                }
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordVar_2 + " " + str3 + " " + str2 + ";";
                            } else {
                                str4 = keyWordVar_2 + " " + str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordVar_2 + " " + str3 + " " + str2;
                            } else {
                                str4 = keyWordVar_2 + " " + str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str3 + " " + str2 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "let " + str2 + " = [];";
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = {}";
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new " + str3 + "();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new " + str3 + "();";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new ArrayList<>();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new ArrayList<>();";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + " = " + str3 + "()";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " = @[]";
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := []";
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = []";
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " = [];";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "let " + str2 + ": " + str3 + " = [];";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " = []";
                    }
                } else {
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2;
                            } else {
                                str4 = str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (str3 == "double") {
                            str5 = "0.00";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint16_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint32_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint64_t") {
                            str5 = "0ULL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "std::string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.00f";
                        }
                        if (str3 == "int8_t") {
                            str5 = "0";
                        }
                        if (str3 == "int16_t") {
                            str5 = "0";
                        }
                        if (str3 == "int32_t") {
                            str5 = "0";
                        }
                        if (str3 == "int64_t") {
                            str5 = "0LL";
                        }
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = None";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "var " + str2 + ";";
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " +  str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "cs") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "0";
                        }
                        if (str3 == "ushort") {
                            str5 = "0";
                        }
                        if (str3 == "uint") {
                            str5 = "0";
                        }
                        if (str3 == "ulong") {
                            str5 = "0UL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "sbyte") {
                            str5 = "0";
                        }
                        if (str3 == "short") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "(byte) 0";
                        }
                        if (str3 == "short") {
                            str5 = "(short) 0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "boolean") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0L";
                        }
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + ": " + str3 + "? = null";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == "float") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8") {
                            str5 = "0";
                        }
                        if (str3 == "uint16") {
                            str5 = "0";
                        }
                        if (str3 == "uint32") {
                            str5 = "0";
                        }
                        if (str3 == "uint64") {
                            str5 = "0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := " + Chr(34) + Chr(34);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == "Double") {
                            str5 = "0.00";
                        }
                        if (str3 == "Character") {
                            str5 = Chr(34) + "a" + Chr(34);
                        }
                        if (str3 == "UInt8") {
                            str5 = "0";
                        }
                        if (str3 == "UInt16") {
                            str5 = "0";
                        }
                        if (str3 == "UInt32") {
                            str5 = "0";
                        }
                        if (str3 == "UInt64") {
                            str5 = "0";
                        }
                        if (str3 == "Int") {
                            str5 = "0";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "Bool") {
                            str5 = "false";
                        }
                        if (str3 == "Float") {
                            str5 = "0.00";
                        }
                        if (str3 == "Int8") {
                            str5 = "0";
                        }
                        if (str3 == "Int16") {
                            str5 = "0";
                        }
                        if (str3 == "Int32") {
                            str5 = "0";
                        }
                        if (str3 == "Int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + "? " + str2 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "var " + str2 + ": " + str3 + ";";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " = null";
                    }
                    //;;;
                }
                htCode += str4 + Chr(10);
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if (SubStr(Trim(A_LoopField220), 1, StrLen(keyWordLet)) == keyWordLet && lineDone == 0) {
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField220), StrLen(keyWordLet)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    std::vector<std::string> items247 = LoopParseFunc(str1, " ");
                    for (size_t A_Index247 = 0; A_Index247 < items247.size() + 0; A_Index247++) {
                        std::string A_LoopField247 = items247[A_Index247 - 0];
                        str2 = A_LoopField247;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField220), StrLen(keyWordLet)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    str2 = Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                }
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordLet_2 + " " + str3 + " " + str2 + ";";
                            } else {
                                str4 = keyWordLet_2 + " " + str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordLet_2 + " " + str3 + " " + str2;
                            } else {
                                str4 = keyWordLet_2 + " " + str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str3 + " " + str2 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "let " + str2 + " = [];";
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = {}";
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new " + str3 + "();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new " + str3 + "();";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new ArrayList<>();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new ArrayList<>();";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + " = " + str3 + "()";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " = @[]";
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := []";
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = []";
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " = [];";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "let " + str2 + ": " + str3 + " = [];";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " = []";
                    }
                } else {
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2;
                            } else {
                                str4 = str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (str3 == "double") {
                            str5 = "0.00";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint16_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint32_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint64_t") {
                            str5 = "0ULL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "std::string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.00f";
                        }
                        if (str3 == "int8_t") {
                            str5 = "0";
                        }
                        if (str3 == "int16_t") {
                            str5 = "0";
                        }
                        if (str3 == "int32_t") {
                            str5 = "0";
                        }
                        if (str3 == "int64_t") {
                            str5 = "0LL";
                        }
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = None";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "let " + str2 + ";";
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = "local " + str2 + " = nil";
                    }
                    if (langToConvertTo == "cs") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "0";
                        }
                        if (str3 == "ushort") {
                            str5 = "0";
                        }
                        if (str3 == "uint") {
                            str5 = "0";
                        }
                        if (str3 == "ulong") {
                            str5 = "0UL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "sbyte") {
                            str5 = "0";
                        }
                        if (str3 == "short") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "(byte) 0";
                        }
                        if (str3 == "short") {
                            str5 = "(short) 0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "boolean") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0L";
                        }
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + ": " + str3 + "? = null";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == "float") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8") {
                            str5 = "0";
                        }
                        if (str3 == "uint16") {
                            str5 = "0";
                        }
                        if (str3 == "uint32") {
                            str5 = "0";
                        }
                        if (str3 == "uint64") {
                            str5 = "0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := " + Chr(34) + Chr(34);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == "Double") {
                            str5 = "0.00";
                        }
                        if (str3 == "Character") {
                            str5 = Chr(34) + "a" + Chr(34);
                        }
                        if (str3 == "UInt8") {
                            str5 = "0";
                        }
                        if (str3 == "UInt16") {
                            str5 = "0";
                        }
                        if (str3 == "UInt32") {
                            str5 = "0";
                        }
                        if (str3 == "UInt64") {
                            str5 = "0";
                        }
                        if (str3 == "Int") {
                            str5 = "0";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "Bool") {
                            str5 = "false";
                        }
                        if (str3 == "Float") {
                            str5 = "0.00";
                        }
                        if (str3 == "Int8") {
                            str5 = "0";
                        }
                        if (str3 == "Int16") {
                            str5 = "0";
                        }
                        if (str3 == "Int32") {
                            str5 = "0";
                        }
                        if (str3 == "Int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + "? " + str2 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "let " + str2 + ": " + str3 + ";";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " = null";
                    }
                    //;;;
                }
                htCode += str4 + Chr(10);
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if (SubStr(Trim(A_LoopField220), 1, StrLen(keyWordDouble + " ")) == keyWordDouble + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordChar + " ")) == keyWordChar + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordUint8 + " ")) == keyWordUint8 + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordUint16 + " ")) == keyWordUint16 + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordUint32 + " ")) == keyWordUint32 + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordUint64 + " ")) == keyWordUint64 + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordINT + " ")) == keyWordINT + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordSTR + " ")) == keyWordSTR + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordBOOL + " ")) == keyWordBOOL + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordFLOAT + " ")) == keyWordFLOAT + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordINT8 + " ")) == keyWordINT8 + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordINT16 + " ")) == keyWordINT16 + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordINT32 + " ")) == keyWordINT32 + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordINT64 + " ")) == keyWordINT64 + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordArrayDefinition + " ")) == keyWordArrayDefinition + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordArrayOfIntegersDefinition + " ")) == keyWordArrayOfIntegersDefinition + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordArrayOfStringsDefinition + " ")) == keyWordArrayOfStringsDefinition + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordArrayOfFloatingPointNumbersDefinition + " ")) == keyWordArrayOfFloatingPointNumbersDefinition + " " || SubStr(Trim(A_LoopField220), 1, StrLen(keyWordArrayOfBooleansDefinition + " ")) == keyWordArrayOfBooleansDefinition + " " && usePrefixTypeForTypeDefinition == "on" && lineDone == 0) {
                lineDone = 1;
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                str1 = Trim(A_LoopField220);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                std::vector<std::string> items248 = LoopParseFunc(str1, " ");
                for (size_t A_Index248 = 0; A_Index248 < items248.size() + 0; A_Index248++) {
                    std::string A_LoopField248 = items248[A_Index248 - 0];
                    str2 = A_LoopField248;
                }
                str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                str2 = Trim(str2);
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2;
                            } else {
                                str4 = str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str3 + " " + str2 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "let " + str2 + " = [];";
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = {}";
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new " + str3 + "();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new " + str3 + "();";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new ArrayList<>();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new ArrayList<>();";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + " = " + str3 + "()";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " = @[]";
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := []";
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = []";
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " = [];";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "let " + str2 + ": " + str3 + " = [];";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " = []";
                    }
                } else {
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2;
                            } else {
                                str4 = str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (str3 == "double") {
                            str5 = "0.00";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint16_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint32_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint64_t") {
                            str5 = "0ULL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "std::string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.00f";
                        }
                        if (str3 == "int8_t") {
                            str5 = "0";
                        }
                        if (str3 == "int16_t") {
                            str5 = "0";
                        }
                        if (str3 == "int32_t") {
                            str5 = "0";
                        }
                        if (str3 == "int64_t") {
                            str5 = "0LL";
                        }
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = None";
                    }
                    if (langToConvertTo == "js") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + ";";
                        } else {
                            str4 = "let " + str2 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "cs") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "0";
                        }
                        if (str3 == "ushort") {
                            str5 = "0";
                        }
                        if (str3 == "uint") {
                            str5 = "0";
                        }
                        if (str3 == "ulong") {
                            str5 = "0UL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "sbyte") {
                            str5 = "0";
                        }
                        if (str3 == "short") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "(byte) 0";
                        }
                        if (str3 == "short") {
                            str5 = "(short) 0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "boolean") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0L";
                        }
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + ": " + str3 + "? = null";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == "float") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8") {
                            str5 = "0";
                        }
                        if (str3 == "uint16") {
                            str5 = "0";
                        }
                        if (str3 == "uint32") {
                            str5 = "0";
                        }
                        if (str3 == "uint64") {
                            str5 = "0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := " + Chr(34) + Chr(34);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == "Double") {
                            str5 = "0.00";
                        }
                        if (str3 == "Character") {
                            str5 = Chr(34) + "a" + Chr(34);
                        }
                        if (str3 == "UInt8") {
                            str5 = "0";
                        }
                        if (str3 == "UInt16") {
                            str5 = "0";
                        }
                        if (str3 == "UInt32") {
                            str5 = "0";
                        }
                        if (str3 == "UInt64") {
                            str5 = "0";
                        }
                        if (str3 == "Int") {
                            str5 = "0";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "Bool") {
                            str5 = "false";
                        }
                        if (str3 == "Float") {
                            str5 = "0.00";
                        }
                        if (str3 == "Int8") {
                            str5 = "0";
                        }
                        if (str3 == "Int16") {
                            str5 = "0";
                        }
                        if (str3 == "Int32") {
                            str5 = "0";
                        }
                        if (str3 == "Int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + "? " + str2 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + ": " + str3 + ";";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " = null";
                    }
                    //;;;
                }
                htCode += str4 + Chr(10);
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if (RegExMatch(Trim(A_LoopField220), "^[a-zA-Z_][a-zA-Z0-9_]*: [^:]*;?$") && usePostfixTypeForTypeDefinition == "on" && lineDone == 0) {
                lineDone = 1;
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                str1 = Trim(A_LoopField220);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str2 = Trim(StrSplit(str1, ":", 1));
                str3 = Trim(StrSplit(str1, ":", 2));
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2;
                            } else {
                                str4 = str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str3 + " " + str2 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "js") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + " = [];";
                        } else {
                            str4 = "let " + str2 + " = [];";
                        }
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = {}";
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new " + str3 + "();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new " + str3 + "();";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new ArrayList<>();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new ArrayList<>();";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + " = " + str3 + "()";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " = @[]";
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := []";
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = []";
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " = [];";
                    }
                    if (langToConvertTo == "ts") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + ": " + str3 + " = [];";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " = [];";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " = []";
                    }
                } else {
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2;
                            } else {
                                str4 = str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (str3 == "double") {
                            str5 = "0.00";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint16_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint32_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint64_t") {
                            str5 = "0ULL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "std::string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.00f";
                        }
                        if (str3 == "int8_t") {
                            str5 = "0";
                        }
                        if (str3 == "int16_t") {
                            str5 = "0";
                        }
                        if (str3 == "int32_t") {
                            str5 = "0";
                        }
                        if (str3 == "int64_t") {
                            str5 = "0LL";
                        }
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = None";
                    }
                    if (langToConvertTo == "js") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + ";";
                        } else {
                            str4 = "let " + str2 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "cs") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "0";
                        }
                        if (str3 == "ushort") {
                            str5 = "0";
                        }
                        if (str3 == "uint") {
                            str5 = "0";
                        }
                        if (str3 == "ulong") {
                            str5 = "0UL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "sbyte") {
                            str5 = "0";
                        }
                        if (str3 == "short") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "(byte) 0";
                        }
                        if (str3 == "short") {
                            str5 = "(short) 0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "boolean") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0L";
                        }
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + ": " + str3 + "? = null";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == "float") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8") {
                            str5 = "0";
                        }
                        if (str3 == "uint16") {
                            str5 = "0";
                        }
                        if (str3 == "uint32") {
                            str5 = "0";
                        }
                        if (str3 == "uint64") {
                            str5 = "0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := " + Chr(34) + Chr(34);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == "Double") {
                            str5 = "0.00";
                        }
                        if (str3 == "Character") {
                            str5 = Chr(34) + "a" + Chr(34);
                        }
                        if (str3 == "UInt8") {
                            str5 = "0";
                        }
                        if (str3 == "UInt16") {
                            str5 = "0";
                        }
                        if (str3 == "UInt32") {
                            str5 = "0";
                        }
                        if (str3 == "UInt64") {
                            str5 = "0";
                        }
                        if (str3 == "Int") {
                            str5 = "0";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "Bool") {
                            str5 = "false";
                        }
                        if (str3 == "Float") {
                            str5 = "0.00";
                        }
                        if (str3 == "Int8") {
                            str5 = "0";
                        }
                        if (str3 == "Int16") {
                            str5 = "0";
                        }
                        if (str3 == "Int32") {
                            str5 = "0";
                        }
                        if (str3 == "Int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + "? " + str2 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + ": " + str3 + ";";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " = null";
                    }
                    //;;;
                }
                htCode += str4 + Chr(10);
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if (RegExMatch(Trim(A_LoopField220), "^[a-zA-Z0-9_\\.]+\\(") && !(InStr(StrLower(A_LoopField220), " main(")) && lineDone == 0) {
                lineDone = 1;
                str1 = Trim(A_LoopField220);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                fixExpertionLineFuncOnly = 0;
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        str2 = expressionParserTranspiler(Trim(str1)) + ";";
                    } else {
                        str2 = expressionParserTranspiler(Trim(str1));
                    }
                } else {
                    if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "groovy") {
                        str2 = expressionParserTranspiler(Trim(str1));
                    } else {
                        str2 = expressionParserTranspiler(Trim(str1)) + ";";
                    }
                }
                fixExpertionLineFuncOnly = 0;
                htCode += str2 + Chr(10);
            }
            else if (RegExMatch(A_LoopField220, "\\.[a-zA-Z_][a-zA-Z0-9_]*") && lineDone == 0) {
                lineDone = 1;
                str1 = Trim(A_LoopField220);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                if (langToConvertTo != langFileExtension_2) {
                    if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "groovy") {
                        htCode += expressionParserTranspiler(extraFlexableFuncCalls(str1, availableFuncsInHTVMInHTVM)) + Chr(10);
                    } else {
                        htCode += expressionParserTranspiler(extraFlexableFuncCalls(str1, availableFuncsInHTVMInHTVM)) + ";" + Chr(10);
                    }
                } else {
                    if (useSemicolon_2 == "on") {
                        htCode += str1 + "; " + Chr(10);
                    } else {
                        htCode += str1 + Chr(10);
                    }
                }
            }
            else if (KeyWordsCommands(A_LoopField220, "check", commands, langToConvertTo) == "true" && lineDone == 0) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += A_LoopField220 + Chr(10);
                } else {
                    out_KeyWordsCommands = KeyWordsCommands(A_LoopField220, "transpile", commands, langToConvertTo);
                    htCode += out_KeyWordsCommands + Chr(10);
                }
            } else {
                //print("else else else " . A_LoopField)
                // this is THE else
                //;;;;;;;;;;;;;;;;;;
                if (lineDone != 1) {
                    if (skipLeftCuleyForFuncPLS != 1) {
                        if (SubStr(Trim(StrLower(A_LoopField220)), 1, 1) == Chr(125)) {
                            htCode += Chr(125) + Chr(10);
                        } else {
                            if (htCodeAcurlyBraceAddSomeVrasFixLP == 1 && SubStr(Trim(StrLower(A_LoopField220)), 1, 1) == Chr(123)) {
                                htCodeAcurlyBraceAddSomeVrasFixLP = 0;
                                htCode += A_LoopField220 + Chr(10) + theFixTextLoopLP + Chr(10);
                            } else {
                                if (htCodeAcurlyBraceAddSomeVrasFixNL == 1 && SubStr(Trim(StrLower(A_LoopField220)), 1, 1) == Chr(123)) {
                                    htCodeAcurlyBraceAddSomeVrasFixNL = 0;
                                    htCode += A_LoopField220 + Chr(10) + theFixTextLoopNL + Chr(10);
                                } else {
                                    htCode += A_LoopField220 + Chr(10);
                                }
                            }
                        }
                    } else {
                        skipLeftCuleyForFuncPLS = 0;
                    }
                }
            }
        }
        htCode = StringTrimRight(htCode, 1);
        //s
        //s
        //s
        if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
            //s
            if (haveWeEverUsedAloop == 1) {
                htCodeLoopfixa = StringTrimRight(htCodeLoopfixa, 1);
                //OutputDebug, |%htCodeLoopfixa%|
                AIndexLoopCurlyFix = 1;
                std::vector<std::string> items249 = LoopParseFunc(htCodeLoopfixa, "\n", "\r");
                for (size_t A_Index249 = 0; A_Index249 < items249.size() + 0; A_Index249++) {
                    std::string A_LoopField249 = items249[A_Index249 - 0];
                    sstr123 = A_LoopField249;
                    fixLoopLokingFor = A_LoopField249;
                    fixLoopLokingForfound = 1;
                    out1 = StrSplit(sstr123 ,"|" , 1);
                    out2 = StrSplit(sstr123 ,"|" , 3);
                    //OutputDebug, |%out1%|
                    //OutputDebug, |%out2%|
                    wasAtanyIfsElseAddAIndexLoopCurlyFix = 0;
                    if (out1 == "nl") {
                        inTarget = 0;
                        insideBracket = 0;
                        netsedCurly = 0;
                        eldLoopNestedBADlol = 0;
                        readyToEnd = 0;
                        endBracketDOntPutThere = 0;
                        dontSaveStr = 0;
                        weAreDoneHereCurly = 0;
                        DeleayOneCuzOfLoopParse = 0;
                        fixLoopLokingForNum = 0;
                        insdeAnestedLoopBAD = 0;
                        foundTheTopLoop = 0;
                        out4758686d86d86d86578991a = "";
                        std::vector<std::string> items250 = LoopParseFunc(htCode, "\n", "\r");
                        for (size_t A_Index250 = 0; A_Index250 < items250.size() + 0; A_Index250++) {
                            std::string A_LoopField250 = items250[A_Index250 - 0];
                            if (InStr(A_LoopField250, fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 1
                            }
                            if (SubStr(Trim(A_LoopField250), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField250 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(s);
                                //MsgBox, % out1z
                                //MsgBox, do we came here 2
                                fixLoopLokingForNum = 0;
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField
                                dontSaveStr = 1;
                                ALoopField = A_LoopField250;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if (inTarget == 1 && InStr(A_LoopField250, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField250, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField250, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField250), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField250, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField250, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField250, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField250, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField250 + Chr(10);
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField250;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "\\b" + keyWordAIndex + "\\d*\\b", "" + keyWordAIndex + "" + out1z);
                                ALoopField = StrReplace(ALoopField, "fihuiuuhuuhtheidFor--asds", "HTVM" + str22 + "-A-A-A-A-A-A-A-A-A--A-A-A-A1" + out1z + "HTVM" + "-A-A-A-A-A-A-A-A-A--A-A-A-A2fihuiuuhuuhtheidFor--asds");
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if (inTarget == 1 && InStr(A_LoopField250, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1) {
                                //MsgBox, % A_LoopField
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField250 + Chr(10);
                            }
                            endBracketDOntPutThere = 0;
                            if (eldLoopNestedBADlol == 1) {
                                insdeAnestedLoopBAD = 0;
                            }
                        }
                        strstysrstsytTRIMHELP = out4758686d86d86d86578991a;
                        strstysrstsytTRIMHELP = StringTrimRight(strstysrstsytTRIMHELP, 1);
                        htCode = strstysrstsytTRIMHELP;
                        //MsgBox, % htCode
                        wasAtanyIfsElseAddAIndexLoopCurlyFix = 1;
                    } else {
                        inTarget = 0;
                        insideBracket = 0;
                        netsedCurly = 0;
                        eldLoopNestedBADlol = 0;
                        readyToEnd = 0;
                        endBracketDOntPutThere = 0;
                        dontSaveStr = 0;
                        weAreDoneHereCurly = 0;
                        DeleayOneCuzOfLoopParse = 0;
                        fixLoopLokingForNum = 0;
                        insdeAnestedLoopBAD = 0;
                        foundTheTopLoop = 0;
                        out4758686d86d86d86578991a = "";
                        std::vector<std::string> items251 = LoopParseFunc(htCode, "\n", "\r");
                        for (size_t A_Index251 = 0; A_Index251 < items251.size() + 0; A_Index251++) {
                            std::string A_LoopField251 = items251[A_Index251 - 0];
                            if (InStr(A_LoopField251 , fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 3
                            }
                            if (SubStr(Trim(A_LoopField251), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField251 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(StrReplace(s, "|", ""));
                                //MsgBox, % out1z
                                fixLoopLokingForNum = 0;
                                //MsgBox, do we came here 4
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField
                                dontSaveStr = 1;
                                ALoopField = A_LoopField251;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if (inTarget == 1 && InStr(A_LoopField251, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField251, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField251, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField251), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField251, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField251, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField251, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField251, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField251 + Chr(10);
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField251;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "\\b" + keyWordAIndex + "\\d*\\b", "" + keyWordAIndex + "" + out1z);
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "\\b" + keyWordALoopField + "\\d*\\b", "" + keyWordALoopField + "" + out1z);
                                ALoopField = StrReplace(ALoopField, "fihuiuuhuuhtheidFor--asds", "HTVM" + str22 + "-A-A-A-A-A-A-A-A-A--A-A-A-A1" + out1z + "HTVM" + "-A-A-A-A-A-A-A-A-A--A-A-A-A2fihuiuuhuuhtheidFor--asds");
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if ((inTarget == 1 && InStr(A_LoopField251, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1)) {
                                //MsgBox, % A_LoopField
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField251 + Chr(10);
                            }
                            endBracketDOntPutThere = 0;
                            if (eldLoopNestedBADlol == 1) {
                                insdeAnestedLoopBAD = 0;
                            }
                        }
                        strstysrstsytTRIMHELP = out4758686d86d86d86578991a;
                        strstysrstsytTRIMHELP = StringTrimRight(strstysrstsytTRIMHELP, 1);
                        htCode = strstysrstsytTRIMHELP;
                        //MsgBox, % htCode
                        wasAtanyIfsElseAddAIndexLoopCurlyFix = 1;
                    }
                    if (wasAtanyIfsElseAddAIndexLoopCurlyFix == 1) {
                        AIndexLoopCurlyFix++;
                        wasAtanyIfsElseAddAIndexLoopCurlyFix = 0;
                    }
                }
                out4758686d86dgt8r754444444 = "";
                hold = 0;
                std::vector<std::string> items252 = LoopParseFunc(htCode, "\n", "\r");
                for (size_t A_Index252 = 0; A_Index252 < items252.size() + 0; A_Index252++) {
                    std::string A_LoopField252 = items252[A_Index252 - 0];
                    ignore = 0;
                    if (SubStr(Trim(A_LoopField252), 1, 4) == "for ") {
                        if (hold == 1 && holdText == A_LoopField252) {
                            ignore = 1;
                        } else {
                            holdText = A_LoopField252;
                            hold = 1;
                        }
                    }
                    if (!ignore) {
                        out4758686d86dgt8r754444444 += A_LoopField252 + Chr(10);
                    }
                }
                out4758686d86dgt8r754444444 = StringTrimRight(out4758686d86dgt8r754444444, 1);
                htCode = out4758686d86dgt8r754444444;
            }
            htCodeOut1234565432 = "";
            std::vector<std::string> items253 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index253 = 0; A_Index253 < items253.size() + 0; A_Index253++) {
                std::string A_LoopField253 = items253[A_Index253 - 0];
                out = A_LoopField253;
                if (!InStr(out, "|itsaersdtgtgfergsdgfsegdfsedAA|")) {
                    htCodeOut1234565432 += out + Chr(10);
                }
            }
            htCode = StringTrimRight(htCodeOut1234565432, 1);
            if (langToConvertTo == "rb") {
                htCode = StrReplace(htCode, "for HTVM----HTVM_FOR_hsdufosyigdydtddy_FOR_HTVM_Ruby_HTVM---HTVM-For_Ruby---AA ", "");
            }
        }
        if (langToConvertTo == "go") {
            htCode = fixGoAindexUnseen(htCode);
        }
    } else {
        htCode = code;
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    std::string ADD_ALL_programmingBlock_HTVMsyntax = "";
    if (COUNT_programmingBlock_HTVMsyntax != 0) {
        isNotHTVMfileEXTRA_INT = 1;
        for (int A_Index254 = 0; A_Index254 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index254++) {
            ADD_ALL_programmingBlock_HTVMsyntax += programmingBlock_HTVMsyntax[A_Index254] + Chr(10);
        }
        ADD_ALL_programmingBlock_HTVMsyntax = StringTrimRight(ADD_ALL_programmingBlock_HTVMsyntax, 1);
        ADD_ALL_programmingBlock_HTVMsyntax = compiler(ADD_ALL_programmingBlock_HTVMsyntax, allInstructionFile, "full", langToConvertToParam);
        isNotHTVMfileEXTRA_INT = 0;
        isNotHTVMfile2 = 1;
        for (int A_Index255 = 0; A_Index255 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index255++) {
            htCode = StrReplace(htCode, "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(A_Index255 + 1) + "AA", compiler(programmingBlock_HTVMsyntax[A_Index255], allInstructionFile, "full", langToConvertToParam));
        }
        isNotHTVMfile2 = 0;
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    if (isNotHTVMfile == 1) {
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print(Chr(10) + isNotHTVMfileEXTRA_LIB_INFO + Chr(10));
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print(Chr(10) + isNotHTVMfileEXTRA_FUNCS_INFO + Chr(10));
        print(Chr(10));
        print(Chr(10));
        print("You must include all the libs from under the section and MAKE SURE your code doesn't already use them!!!");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print(Chr(10));
        print("You must copy-paste all the funcs from under the section and MAKE SURE your code doesn't already use them!!!");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("SCROLL UP!!!!!");
        print("SCROLL UP!!!!!");
        print("SCROLL UP!!!!!");
        print("Note: If you dont see any libs or built-in functions that you need to add, then that means you dont have to!");
        return htCode;
    }
    std::string fixLuaAndRuby = "";
    std::string fixLuaAndRubyHELP = "";
    if (langToConvertTo == langFileExtension_2) {
        if (useCurlyBraces_2 == "off" && useEnd_2 == "off") {
            htCode = indent_nested_curly_braces(htCode, 0);
        } else {
            htCode = indent_nested_curly_braces(htCode, 1);
        }
        if (useEnd_2 == "on") {
            std::vector<std::string> items256 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index256 = 0; A_Index256 < items256.size() + 0; A_Index256++) {
                std::string A_LoopField256 = items256[A_Index256 - 0];
                if (Trim(A_LoopField256) == keyWordCurlyBraceClose_2) {
                    fixLuaAndRuby += StrReplace(A_LoopField256, keyWordCurlyBraceClose_2, Trim(keyWordEnd_2)) + Chr(10);
                }
                else if (SubStrLastChars(A_LoopField256, 2) == " " + keyWordCurlyBraceOpen_2) {
                    fixLuaAndRuby += StringTrimRight(A_LoopField256, 2) + Chr(10);
                } else {
                    fixLuaAndRuby += A_LoopField256 + Chr(10);
                }
            }
            htCode = StringTrimRight(fixLuaAndRuby, 1);
        }
        //;;;;;;;;;;
        //;;;;;;;;;;
    } else {
        //;;;;;;;;;;
        //;;;;;;;;;;
        if (langToConvertTo == "py" || langToConvertTo == "nim") {
            htCode = indent_nested_curly_braces(htCode, 0);
        } else {
            htCode = indent_nested_curly_braces(htCode, 1);
        }
        if (langToConvertTo == "lua" || langToConvertTo == "rb" || langToConvertTo == langFileExtension_2) {
            if (langToConvertTo == langFileExtension_2 && useEnd_2 == "on") {
                fixLuaAndRubyHELP = Trim(keyWordEnd_2);
                std::vector<std::string> items257 = LoopParseFunc(htCode, "\n", "\r");
                for (size_t A_Index257 = 0; A_Index257 < items257.size() + 0; A_Index257++) {
                    std::string A_LoopField257 = items257[A_Index257 - 0];
                    if (Trim(A_LoopField257) == "}") {
                        fixLuaAndRuby += StrReplace(A_LoopField257, "}", fixLuaAndRubyHELP) + Chr(10);
                    }
                    else if (SubStrLastChars(A_LoopField257, 2) == " {") {
                        fixLuaAndRuby += StringTrimRight(A_LoopField257, 2) + Chr(10);
                    } else {
                        fixLuaAndRuby += A_LoopField257 + Chr(10);
                    }
                }
                htCode = StringTrimRight(fixLuaAndRuby, 1);
            } else {
                fixLuaAndRubyHELP = "end";
                std::vector<std::string> items258 = LoopParseFunc(htCode, "\n", "\r");
                for (size_t A_Index258 = 0; A_Index258 < items258.size() + 0; A_Index258++) {
                    std::string A_LoopField258 = items258[A_Index258 - 0];
                    if (Trim(A_LoopField258) == "}") {
                        fixLuaAndRuby += StrReplace(A_LoopField258, "}", fixLuaAndRubyHELP) + Chr(10);
                    }
                    else if (SubStrLastChars(A_LoopField258, 2) == " {") {
                        fixLuaAndRuby += StringTrimRight(A_LoopField258, 2) + Chr(10);
                    } else {
                        fixLuaAndRuby += A_LoopField258 + Chr(10);
                    }
                }
                htCode = StringTrimRight(fixLuaAndRuby, 1);
            }
        }
    }
    std::vector<std::string> nextWordEndFix;
    std::string nextWordEndFixOut = "";
    if (langToConvertTo == langFileExtension_2 && useEnd_2 == "on") {
        std::vector<std::string> items259 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index259 = 0; A_Index259 < items259.size() + 0; A_Index259++) {
            std::string A_LoopField259 = items259[A_Index259 - 0];
            HTVM_Append(nextWordEndFix, A_LoopField259);
        }
        HTVM_Append(nextWordEndFix, " ");
        std::vector<std::string> items260 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index260 = 0; A_Index260 < items260.size() + 0; A_Index260++) {
            std::string A_LoopField260 = items260[A_Index260 - 0];
            if (Trim(A_LoopField260) == Trim(keyWordEnd_2) && SubStr(Trim(nextWordEndFix[A_Index260 + 1]), 1, StrLen(Trim(keyWordElseIf_2) + " ")) == Trim(keyWordElseIf_2) + " " || Trim(A_LoopField260) == Trim(keyWordEnd_2) && (Trim(nextWordEndFix[A_Index260 + 1]) == Trim(keyWordElse_2) || Trim(nextWordEndFix[A_Index260 + 1]) == Trim(keyWordElse_2 + ":"))) {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField260 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == "lua") {
        std::vector<std::string> items261 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index261 = 0; A_Index261 < items261.size() + 0; A_Index261++) {
            std::string A_LoopField261 = items261[A_Index261 - 0];
            HTVM_Append(nextWordEndFix, A_LoopField261);
        }
        HTVM_Append(nextWordEndFix, " ");
        std::vector<std::string> items262 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index262 = 0; A_Index262 < items262.size() + 0; A_Index262++) {
            std::string A_LoopField262 = items262[A_Index262 - 0];
            if (Trim(A_LoopField262) == "end" && SubStr(Trim(nextWordEndFix[A_Index262 + 1]), 1, StrLen("elseif ")) == "elseif " || Trim(A_LoopField262) == "end" && Trim(nextWordEndFix[A_Index262 + 1]) == "else") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField262 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == "rb") {
        std::vector<std::string> items263 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index263 = 0; A_Index263 < items263.size() + 0; A_Index263++) {
            std::string A_LoopField263 = items263[A_Index263 - 0];
            HTVM_Append(nextWordEndFix, A_LoopField263);
        }
        HTVM_Append(nextWordEndFix, " ");
        std::vector<std::string> items264 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index264 = 0; A_Index264 < items264.size() + 0; A_Index264++) {
            std::string A_LoopField264 = items264[A_Index264 - 0];
            if (Trim(A_LoopField264) == "end" && SubStr(Trim(nextWordEndFix[A_Index264 + 1]), 1, StrLen("elsif ")) == "elsif " || Trim(A_LoopField264) == "end" && Trim(nextWordEndFix[A_Index264 + 1]) == "else") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField264 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    std::vector<std::string> nextWordEndFixRB;
    nextWordEndFixOut = "";
    if (langToConvertTo == "rb") {
        std::vector<std::string> items265 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index265 = 0; A_Index265 < items265.size() + 0; A_Index265++) {
            std::string A_LoopField265 = items265[A_Index265 - 0];
            HTVM_Append(nextWordEndFixRB, A_LoopField265);
        }
        HTVM_Append(nextWordEndFixRB, " ");
        std::vector<std::string> items266 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index266 = 0; A_Index266 < items266.size() + 0; A_Index266++) {
            std::string A_LoopField266 = items266[A_Index266 - 0];
            if (Trim(A_LoopField266) == "end" && SubStr(Trim(nextWordEndFixRB[A_Index266 + 1]), 1, StrLen("rescue ")) == "rescue " || Trim(A_LoopField266) == "end" && Trim(nextWordEndFixRB[A_Index266 + 1]) == "ensure") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField266 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == langFileExtension_2 && useEnd_2 == "on") {
        std::vector<std::string> items267 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index267 = 0; A_Index267 < items267.size() + 0; A_Index267++) {
            std::string A_LoopField267 = items267[A_Index267 - 0];
            HTVM_Append(nextWordEndFixRB, A_LoopField267);
        }
        HTVM_Append(nextWordEndFixRB, " ");
        std::vector<std::string> items268 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index268 = 0; A_Index268 < items268.size() + 0; A_Index268++) {
            std::string A_LoopField268 = items268[A_Index268 - 0];
            if (Trim(A_LoopField268) == Trim(keyWordEnd_2) && SubStr(Trim(nextWordEndFixRB[A_Index268 + 1]), 1, StrLen(Trim(keyWordCatch_2) + " ")) == Trim(keyWordCatch_2) + " " || Trim(A_LoopField268) == Trim(keyWordEnd_2) && Trim(nextWordEndFixRB[A_Index268 + 1]) == Trim(keyWordFinally_2) || Trim(nextWordEndFixRB[A_Index268 + 1]) == Trim(keyWordFinally_2 + ":")) {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField268 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    nextWordEndFixOut = "";
    if (langToConvertTo == "ahk") {
        std::vector<std::string> items269 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index269 = 0; A_Index269 < items269.size() + 0; A_Index269++) {
            std::string A_LoopField269 = items269[A_Index269 - 0];
            if (SubStr(Trim(A_LoopField269), 1, StrLen("Loop, Parse, ")) == "Loop, Parse, ") {
                nextWordEndFixOut += StrReplace(A_LoopField269, "{", Chr(10) + "{" + Chr(10)) + Chr(10);
            } else {
                nextWordEndFixOut += A_LoopField269 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == "go") {
        std::vector<std::string> fixGoManGoIsSoAnnoyingBroooFurure;
        std::vector<std::string> items270 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index270 = 0; A_Index270 < items270.size() + 0; A_Index270++) {
            std::string A_LoopField270 = items270[A_Index270 - 0];
            HTVM_Append(fixGoManGoIsSoAnnoyingBroooFurure, A_LoopField270);
        }
        HTVM_Append(fixGoManGoIsSoAnnoyingBroooFurure, " ");
        int fixGoManGoIsSoAnnoyingBroooSkip = 0;
        int fixGoManGoIsSoAnnoyingBroooCount = 0;
        std::string fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
        std::string fixGoManGoIsSoAnnoyingBrooo = "";
        std::vector<std::string> items271 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index271 = 0; A_Index271 < items271.size() + 0; A_Index271++) {
            std::string A_LoopField271 = items271[A_Index271 - 0];
            if (Trim(A_LoopField271) == "}" && SubStr(Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index271 + 1]), 1, StrLen("else if ")) == "else if ") {
                fixGoManGoIsSoAnnoyingBroooSkip = 1;
                fixGoManGoIsSoAnnoyingBroooCount = 0;
                std::vector<std::string> items272 = LoopParseFunc(fixGoManGoIsSoAnnoyingBroooFurure[A_Index271 + 1]);
                for (size_t A_Index272 = 0; A_Index272 < items272.size() + 0; A_Index272++) {
                    std::string A_LoopField272 = items272[A_Index272 - 0];
                    if (A_LoopField272 == " ") {
                        fixGoManGoIsSoAnnoyingBroooCount++;
                    } else {
                        break;
                    }
                }
                fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
                for (int A_Index273 = 0; A_Index273 < fixGoManGoIsSoAnnoyingBroooCount + 0; A_Index273++) {
                    fixGoManGoIsSoAnnoyingBroooCountSpaceses += " ";
                }
                fixGoManGoIsSoAnnoyingBrooo += fixGoManGoIsSoAnnoyingBroooCountSpaceses + "} " + Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index271 + 1]) + Chr(10);
            } else {
                if (fixGoManGoIsSoAnnoyingBroooSkip == 0) {
                    fixGoManGoIsSoAnnoyingBrooo += A_LoopField271 + Chr(10);
                }
                fixGoManGoIsSoAnnoyingBroooSkip = 0;
            }
        }
        htCode = StringTrimRight(fixGoManGoIsSoAnnoyingBrooo, 1);
    }
    if (langToConvertTo == "cs" || langToConvertTo == "java") {
        htCode = fixCSandJAVAstaticBugForFunc(htCode);
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;; fix here
    //;;;;;;;;;;;;;;;;;;;;;;;;; fix here
    //;;;;;;;;;;;;;;;;;;;;;;;;; fix here
    if (langToConvertTo == "rb") {
        htCode = FixRubyGlobalVars(htCode);
    }
    htCode = StrReplace(htCode, "optanal-HTVM-opt-parmsNOtWorking-theirewIs-a-bug-Iusfbudfbuoeshfuisbav=-fwaegs-awedsf-dd-sfgc ", "");
    if (langToConvertTo == "rb") {
        htCode = StrReplace(htCode, "$$", "$");
        htCode = StrReplace(htCode, "$$", "$");
        htCode = StrReplace(htCode, "$$", "$");
    }
    if (langToConvertTo == "java") {
        htCode = StrReplace(htCode, "= [);", "= new ArrayList<>();");
        htCode = fixJAVAstrCmp_FjavaUGH(htCode);
    }
    if (langToConvertTo == "cpp" || langToConvertTo == "cs" || langToConvertTo == "java" || langToConvertTo == "kt") {
        htCode = RegExReplace(htCode, "(?<![A-Za-z0-9_])(-?\\d+\\.\\d+)(?![A-Za-z0-9_]|f)", "$1f");
        htCode = FixDoubleInThe4langs(htCode);
    }
    if (langToConvertTo == langFileExtension_2) {
        htCode = fixHTVMToHTVMMissingAfterAssignmentOperator(htCode);
        htCode = formatHTVMtoHTVMsubout(htCode);
        htCode = StrReplace(htCode, "HTVM-------else---HTVM--parartenet--manstccing--hdksfbsdWYOUWHOUDNEVERBEABALETOTYPEYHIS--FFfix", Trim(keyWordElse_2));
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;; fix here
    //;;;;;;;;;;;;;;;;;;;;;;;;; fix here
    //;;;;;;;;;;;;;;;;;;;;;;;;; fix here
    if (COUNT_programmingBlock_InTheTranspiledLang != 0) {
        for (int A_Index274 = 0; A_Index274 < COUNT_programmingBlock_InTheTranspiledLang + 0; A_Index274++) {
            htCode = StrReplace(htCode, "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(A_Index274 + 1) + "AA", programmingBlock_InTheTranspiledLang[A_Index274]);
        }
    }
    if (langToConvertTo == "cpp") {
        if (COUNT_programmingBlock_CPP != 0) {
            for (int A_Index275 = 0; A_Index275 < COUNT_programmingBlock_CPP + 0; A_Index275++) {
                htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index275 + 1) + "AA", programmingBlock_CPP[A_Index275]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CPP != 0) {
            for (int A_Index276 = 0; A_Index276 < COUNT_programmingBlock_CPP + 0; A_Index276++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index276 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCPP_2 + Chr(10) + programmingBlock_CPP[A_Index276] + Chr(10) + keyWordCodeInTheTranspiledLangEndCPP_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index276 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "py") {
        if (COUNT_programmingBlock_PY != 0) {
            for (int A_Index277 = 0; A_Index277 < COUNT_programmingBlock_PY + 0; A_Index277++) {
                htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index277 + 1) + "AA", programmingBlock_PY[A_Index277]);
            }
        }
    } else {
        if (COUNT_programmingBlock_PY != 0) {
            for (int A_Index278 = 0; A_Index278 < COUNT_programmingBlock_PY + 0; A_Index278++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index278 + 1) + "AA", keyWordCodeInTheTranspiledLangStartPY_2 + Chr(10) + programmingBlock_PY[A_Index278] + Chr(10) + keyWordCodeInTheTranspiledLangEndPY_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index278 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "js") {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index279 = 0; A_Index279 < COUNT_programmingBlock_JS + 0; A_Index279++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index279 + 1) + "AA", programmingBlock_JS[A_Index279]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index280 = 0; A_Index280 < COUNT_programmingBlock_JS + 0; A_Index280++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index280 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJS_2 + Chr(10) + programmingBlock_JS[A_Index280] + Chr(10) + keyWordCodeInTheTranspiledLangEndJS_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index280 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "go") {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index281 = 0; A_Index281 < COUNT_programmingBlock_GO + 0; A_Index281++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index281 + 1) + "AA", programmingBlock_GO[A_Index281]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index282 = 0; A_Index282 < COUNT_programmingBlock_GO + 0; A_Index282++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index282 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGO_2 + Chr(10) + programmingBlock_GO[A_Index282] + Chr(10) + keyWordCodeInTheTranspiledLangEndGO_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index282 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "lua") {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index283 = 0; A_Index283 < COUNT_programmingBlock_LUA + 0; A_Index283++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index283 + 1) + "AA", programmingBlock_LUA[A_Index283]);
            }
        }
    } else {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index284 = 0; A_Index284 < COUNT_programmingBlock_LUA + 0; A_Index284++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index284 + 1) + "AA", keyWordCodeInTheTranspiledLangStartLUA_2 + Chr(10) + programmingBlock_LUA[A_Index284] + Chr(10) + keyWordCodeInTheTranspiledLangEndLUA_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index284 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "cs") {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index285 = 0; A_Index285 < COUNT_programmingBlock_CS + 0; A_Index285++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index285 + 1) + "AA", programmingBlock_CS[A_Index285]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index286 = 0; A_Index286 < COUNT_programmingBlock_CS + 0; A_Index286++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index286 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCS_2 + Chr(10) + programmingBlock_CS[A_Index286] + Chr(10) + keyWordCodeInTheTranspiledLangEndCS_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index286 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "java") {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index287 = 0; A_Index287 < COUNT_programmingBlock_JAVA + 0; A_Index287++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index287 + 1) + "AA", programmingBlock_JAVA[A_Index287]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index288 = 0; A_Index288 < COUNT_programmingBlock_JAVA + 0; A_Index288++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index288 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJAVA_2 + Chr(10) + programmingBlock_JAVA[A_Index288] + Chr(10) + keyWordCodeInTheTranspiledLangEndJAVA_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index288 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "kt") {
        if (COUNT_programmingBlock_KT != 0) {
            for (int A_Index289 = 0; A_Index289 < COUNT_programmingBlock_KT + 0; A_Index289++) {
                htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index289 + 1) + "AA", programmingBlock_KT[A_Index289]);
            }
        }
    } else {
        if (COUNT_programmingBlock_KT != 0) {
            for (int A_Index290 = 0; A_Index290 < COUNT_programmingBlock_KT + 0; A_Index290++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index290 + 1) + "AA", keyWordCodeInTheTranspiledLangStartKT_2 + Chr(10) + programmingBlock_KT[A_Index290] + Chr(10) + keyWordCodeInTheTranspiledLangEndKT_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index290 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "rb") {
        if (COUNT_programmingBlock_RB != 0) {
            for (int A_Index291 = 0; A_Index291 < COUNT_programmingBlock_RB + 0; A_Index291++) {
                htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index291 + 1) + "AA", programmingBlock_RB[A_Index291]);
            }
        }
    } else {
        if (COUNT_programmingBlock_RB != 0) {
            for (int A_Index292 = 0; A_Index292 < COUNT_programmingBlock_RB + 0; A_Index292++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index292 + 1) + "AA", keyWordCodeInTheTranspiledLangStartRB_2 + Chr(10) + programmingBlock_RB[A_Index292] + Chr(10) + keyWordCodeInTheTranspiledLangEndRB_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index292 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "nim") {
        if (COUNT_programmingBlock_NIM != 0) {
            for (int A_Index293 = 0; A_Index293 < COUNT_programmingBlock_NIM + 0; A_Index293++) {
                htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index293 + 1) + "AA", programmingBlock_NIM[A_Index293]);
            }
        }
    } else {
        if (COUNT_programmingBlock_NIM != 0) {
            for (int A_Index294 = 0; A_Index294 < COUNT_programmingBlock_NIM + 0; A_Index294++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index294 + 1) + "AA", keyWordCodeInTheTranspiledLangStartNIM_2 + Chr(10) + programmingBlock_NIM[A_Index294] + Chr(10) + keyWordCodeInTheTranspiledLangEndNIM_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index294 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "ahk") {
        if (COUNT_programmingBlock_AHK != 0) {
            for (int A_Index295 = 0; A_Index295 < COUNT_programmingBlock_AHK + 0; A_Index295++) {
                htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index295 + 1) + "AA", programmingBlock_AHK[A_Index295]);
            }
        }
    } else {
        if (COUNT_programmingBlock_AHK != 0) {
            for (int A_Index296 = 0; A_Index296 < COUNT_programmingBlock_AHK + 0; A_Index296++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index296 + 1) + "AA", keyWordCodeInTheTranspiledLangStartAHK_2 + Chr(10) + programmingBlock_AHK[A_Index296] + Chr(10) + keyWordCodeInTheTranspiledLangEndAHK_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index296 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "swift") {
        if (COUNT_programmingBlock_SWIFT != 0) {
            for (int A_Index297 = 0; A_Index297 < COUNT_programmingBlock_SWIFT + 0; A_Index297++) {
                htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index297 + 1) + "AA", programmingBlock_SWIFT[A_Index297]);
            }
        }
    } else {
        if (COUNT_programmingBlock_SWIFT != 0) {
            for (int A_Index298 = 0; A_Index298 < COUNT_programmingBlock_SWIFT + 0; A_Index298++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index298 + 1) + "AA", keyWordCodeInTheTranspiledLangStartSWIFT_2 + Chr(10) + programmingBlock_SWIFT[A_Index298] + Chr(10) + keyWordCodeInTheTranspiledLangEndSWIFT_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index298 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "dart") {
        if (COUNT_programmingBlock_DART != 0) {
            for (int A_Index299 = 0; A_Index299 < COUNT_programmingBlock_DART + 0; A_Index299++) {
                htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index299 + 1) + "AA", programmingBlock_DART[A_Index299]);
            }
        }
    } else {
        if (COUNT_programmingBlock_DART != 0) {
            for (int A_Index300 = 0; A_Index300 < COUNT_programmingBlock_DART + 0; A_Index300++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index300 + 1) + "AA", keyWordCodeInTheTranspiledLangStartDART_2 + Chr(10) + programmingBlock_DART[A_Index300] + Chr(10) + keyWordCodeInTheTranspiledLangEndDART_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index300 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "ts") {
        if (COUNT_programmingBlock_TS != 0) {
            for (int A_Index301 = 0; A_Index301 < COUNT_programmingBlock_TS + 0; A_Index301++) {
                htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index301 + 1) + "AA", programmingBlock_TS[A_Index301]);
            }
        }
    } else {
        if (COUNT_programmingBlock_TS != 0) {
            for (int A_Index302 = 0; A_Index302 < COUNT_programmingBlock_TS + 0; A_Index302++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index302 + 1) + "AA", keyWordCodeInTheTranspiledLangStartTS_2 + Chr(10) + programmingBlock_TS[A_Index302] + Chr(10) + keyWordCodeInTheTranspiledLangEndTS_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index302 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "groovy") {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (int A_Index303 = 0; A_Index303 < COUNT_programmingBlock_GROOVY + 0; A_Index303++) {
                htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index303 + 1) + "AA", programmingBlock_GROOVY[A_Index303]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (int A_Index304 = 0; A_Index304 < COUNT_programmingBlock_GROOVY + 0; A_Index304++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index304 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGROOVY_2 + Chr(10) + programmingBlock_GROOVY[A_Index304] + Chr(10) + keyWordCodeInTheTranspiledLangEndGROOVY_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index304 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    //;;;;;;;;;;
    if (langToConvertTo == langFileExtension_2) {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (int A_Index305 = 0; A_Index305 < COUNT_programmingBlock_HTVM + 0; A_Index305++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index305 + 1) + "AA", programmingBlock_HTVM[A_Index305]);
            }
        }
    } else {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (int A_Index306 = 0; A_Index306 < COUNT_programmingBlock_HTVM + 0; A_Index306++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index306 + 1) + "AA", Chr(10));
            }
        }
    }
    if (langToConvertTo != langFileExtension_2) {
        htCode = StrReplace(htCode, "wklajebawszopsne--tshecurlyybarxccsesgFORguiTHTVM0987HTVM---HTVMAAAadhksudahsdGUI_-_HTVM_OPEN-HTVM--GUI", "{");
        htCode = StrReplace(htCode, "wklajebawszopsne--tshecurlyybarxccsesgFORguiTHTVM0987HTVM---HTVMAAAadhksudahsdGUI_-_HTVM_CLOSE-HTVM--GUI", "}");
        ALoopField = "";
        str23 = "";
        std::vector<std::string> items307 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index307 = 0; A_Index307 < items307.size() + 0; A_Index307++) {
            std::string A_LoopField307 = items307[A_Index307 - 0];
            ALoopField = A_LoopField307;
            if (InStr(A_LoopField307, "fihuiuuhuuhtheidFor--asds")) {
                str2 = Trim(StrSplit(ALoopField, "HTVM" + str22 + "-A-A-A-A-A-A-A-A-A--A-A-A-A1", 2));
                str2 = Trim(StrSplit(Trim(str2), "HTVM" + str22 + "-A-A-A-A-A-A-A-A-A--A-A-A-A2", 1));
                for (int A_Index308 = 0; A_Index308 < theIdNumOfThe34 + 0; A_Index308++) {
                    if (theIdNumOfThe34 == A_Index308 + 1) {
                        if (langToConvertTo == langFileExtension_2) {
                            if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                                ALoopField = StrReplace(ALoopField, "fihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index308 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(fString(theIdNumOfThe34theVar[A_Index308 + 1]), "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                            } else {
                                ALoopField = StrReplace(ALoopField, "fihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index308 + 1) + Chr(65) + Chr(65), StrReplace(fString(theIdNumOfThe34theVar[A_Index308 + 1]), keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                            }
                        } else {
                            ALoopField = StrReplace(ALoopField, "fihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index308 + 1) + Chr(65) + Chr(65), StrReplace(fString(theIdNumOfThe34theVar[A_Index308 + 1]), keyWordEscpaeChar, "\\") + Chr(34));
                        }
                    } else {
                        if (langToConvertTo == langFileExtension_2) {
                            if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                                ALoopField = StrReplace(ALoopField, "fihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index308 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(fString(theIdNumOfThe34theVar[A_Index308 + 1]), "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2));
                            } else {
                                ALoopField = StrReplace(ALoopField, "fihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index308 + 1) + Chr(65) + Chr(65), StrReplace(fString(theIdNumOfThe34theVar[A_Index308 + 1]), keyWordEscpaeChar, keyWordEscpaeChar_2));
                            }
                        } else {
                            ALoopField = StrReplace(ALoopField, "fihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index308 + 1) + Chr(65) + Chr(65), StrReplace(fString(theIdNumOfThe34theVar[A_Index308 + 1]), keyWordEscpaeChar, "\\"));
                        }
                    }
                }
            }
            str23 += ALoopField + Chr(10);
        }
        htCode = StringTrimRight(str23, 1);
        str23 = "";
        htCode = RegExReplace(htCode, "HTVM" + str22 + "-A-A-A-A-A-A-A-A-A--A-A-A-A1.*?HTVM" + str22 + "-A-A-A-A-A-A-A-A-A--A-A-A-A2", "");
        //;;;
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    areWeInAFuncFromInstructions = 0;
    areWeInAFuncFromInstructionsLineNum = 0;
    std::string funcLangHolder = "";
    std::string funcNameHolder = "";
    std::string funcLibsHolder = "";
    std::string funcFuncHolder = "";
    std::string funcDescriptionHolder = "";
    std::vector<std::string> allFuncLang;
    std::vector<std::string> allFuncNames;
    std::vector<std::string> allFuncLibs;
    std::vector<std::string> allFuncs;
    std::vector<std::string> allfuncDescription;
    int correctLang = 0;
    std::vector<std::string> items309 = LoopParseFunc(instructions, "\n", "\r");
    for (size_t A_Index309 = 0; A_Index309 < items309.size() + 0; A_Index309++) {
        std::string A_LoopField309 = items309[A_Index309 - 0];
        if (Trim(A_LoopField309) == "funcEND======================funcEND==============") {
            areWeInAFuncFromInstructions = 0;
            areWeInAFuncFromInstructionsLineNum = 0;
            if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                //MsgBox, % funcFuncHolder
                HTVM_Append(allFuncs, funcFuncHolder);
            }
            correctLang = 0;
            funcFuncHolder = "";
        }
        if (areWeInAFuncFromInstructions == 1) {
            if (areWeInAFuncFromInstructionsLineNum == 1) {
                // name of the func
                funcLangHolder = StringTrimLeft(A_LoopField309, 5);
                if (Trim(funcLangHolder) == langToConvertTo) {
                    HTVM_Append(allFuncLang, Trim(funcLangHolder));
                    correctLang = 1;
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 2) {
                // name of the func
                funcNameHolder = StringTrimLeft(A_LoopField309, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    HTVM_Append(allFuncNames, Trim(funcNameHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 3) {
                // all libs
                funcLibsHolder = StringTrimLeft(A_LoopField309, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    HTVM_Append(allFuncLibs, Trim(funcLibsHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 4) {
                // func description
                funcDescriptionHolder = StringTrimLeft(A_LoopField309, 12);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    HTVM_Append(allfuncDescription, Trim(funcDescriptionHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum >= 5) {
                // the full func
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    funcFuncHolder += A_LoopField309 + Chr(10);
                }
            }
            //MsgBox, % A_LoopField
            areWeInAFuncFromInstructionsLineNum++;
        }
        if (Trim(A_LoopField309) == "func======================func==============") {
            areWeInAFuncFromInstructions = 1;
            areWeInAFuncFromInstructionsLineNum = 1;
            correctLang = 0;
        }
    }
    //~ MsgBox, ===========================================================================
    //~ msgbox, % allFuncNames
    //~ MsgBox, ===========================================================================
    //~ msgbox, % allFuncLibs
    //~ MsgBox, ===========================================================================
    //~ msgbox, % allFuncLang
    //~ MsgBox, ===========================================================================
    //~ msgbox, % allFuncs
    //~ MsgBox, ===========================================================================
    if (isNotHTVMfile2 == 0) {
        if (langToConvertTo == "ahk") {
            htCode = RegExReplace(htCode, "\\bStrSplit\\b", "AHK_StrSplit_AHK");
            htCode = RegExReplace(htCode, "\\bSleep\\b", "AHK_Sleep_AHK");
        }
        if (langToConvertTo == "cpp") {
            htCode = htCode + Chr(10) + "    return 0;" + Chr(10) + "}";
            htCode = StrReplace(htCode, "int main(int argc, char* argv[]);", "int main(int argc, char* argv[])");
        }
        if (langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
            htCode = htCode + Chr(10) + "}" + Chr(10) + "main();";
            htCode = StrReplace(htCode, "async function main();", "async function main()");
            htCode = StrReplace(htCode, "function async function main()", "async function main()");
        }
        if (langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
            htCode = htCode + Chr(10) + "}" + Chr(10) + "main();";
            htCode = StrReplace(htCode, "async function main(): Promise<void>;", "async function main(): Promise<void>");
            htCode = StrReplace(htCode, "function async function main(): Promise<void>", "async function main(): Promise<void>");
        }
        if (langToConvertTo == "go") {
            htCode = htCode + Chr(10) + "}";
            htCode = StrReplace(htCode, "func main();", "func main()");
        }
        if (langToConvertTo == "cs") {
            htCode = htCode + Chr(10) + "}" + Chr(10) + "}";
            htCode = StrReplace(htCode, "static void Main(string[] args);", "static void Main(string[] args)");
        }
        if (langToConvertTo == "java") {
            htCode = htCode + Chr(10) + "}" + Chr(10) + "}";
            htCode = StrReplace(htCode, "public static void main(String[] args);", "public static void main(String[] args)");
        }
        if (langToConvertTo == "kt") {
            htCode = htCode + Chr(10) + "}";
            htCode = StrReplace(htCode, "fun main(args: Array<String>);", "fun main(args: Array<String>)");
        }
        if (langToConvertTo == "swift") {
            htCode = htCode + Chr(10) + "}" + Chr(10) + "main()";
            htCode = StrReplace(htCode, "func main();", "func main()");
            htCode = StrReplace(htCode, "func main() ->", "func main()");
        }
        if (langToConvertTo == "dart") {
            htCode = htCode + Chr(10) + "}";
            htCode = StrReplace(htCode, "void main(List<String> arguments);", "void main(List<String> arguments)");
        }
        for (int A_Index310 = 0; A_Index310 < HTVM_Size(commentsBugFix) + 0; A_Index310++) {
            htCode = StrReplace(htCode, "HTVM--cnavisdofbuvsesdivdidufg79wregwewaeosd8ges7dfdftuawdiHTVMv2yerheyziberlasduci6syiq--AA" + STR(A_Index310) + "AA", commentsBugFix[A_Index310]);
        }
    }
    std::string jsHTMLdownCode = "</script>" + Chr(10) + "</body>" + Chr(10) + "</html>";
    int includeLibsInCppIf = 0;
    std::string allFuncsToPutAtTop = Chr(10);
    std::string allLibsToPutAtTop = "";
    if (!(HTVM_Size(allFuncNames) <= 0)) {
        for (int A_Index311 = 0; A_Index311 < HTVM_Size(allFuncNames) + 0; A_Index311++) {
            if (InStr(htCode, allFuncNames[A_Index311]) + "(") {
                //MsgBox, % allFuncNames[A_Index]
                allFuncsToPutAtTop += allFuncs[A_Index311] + Chr(10);
                if (Trim(allFuncLibs[A_Index311]) != "null") {
                    allLibsToPutAtTop += allFuncLibs[A_Index311] + "|";
                }
            }
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTop, 1);
        std::string allLibsToPutAtTopTEMP = "";
        std::vector<std::string> items312 = LoopParseFunc(allLibsToPutAtTop, "|");
        for (size_t A_Index312 = 0; A_Index312 < items312.size() + 0; A_Index312++) {
            std::string A_LoopField312 = items312[A_Index312 - 0];
            allLibsToPutAtTopTEMP += A_LoopField312 + Chr(10);
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTopTEMP, 1);
        includeLibsInCppIf = 1;
        if (langToConvertTo == "cpp") {
            allLibsToPutAtTop = "#include <iostream>" + Chr(10) + "#include <sstream>" + Chr(10) + "#include <string>" + Chr(10) + "#include <cstdint>" + Chr(10) + "#include <algorithm>" + Chr(10) + "#include <vector>" + Chr(10) + "#include <any>" + Chr(10) + "#include <optional>" + Chr(10) + allLibsToPutAtTop;
        }
        if (langToConvertTo == "cs") {
            allLibsToPutAtTop = "using System;" + Chr(10) + "using System.Collections.Generic;" + Chr(10) + allLibsToPutAtTop;
        }
        allLibsToPutAtTop = Sort(allLibsToPutAtTop, "U");
        allLibsToPutAtTop = StrReplace(allLibsToPutAtTop, "~~~", Chr(10));
        // cpp is a failed language
        if (langToConvertTo == "cpp") {
            allLibsToPutAtTop = "#if __has_include(" + Chr(34) + "srell.hpp" + Chr(34) + ")" + Chr(10) + "    #include " + Chr(34) + "srell.hpp" + Chr(34) + "" + Chr(10) + "    #define USE_POWERFUL_REGEX 1" + Chr(10) + "    #pragma message(" + Chr(34) + "SUCCESS: Compiling with powerful SRELL regex engine. Lookbehinds will work." + Chr(34) + ")" + Chr(10) + "#else" + Chr(10) + "    #include " + Chr(60) + "regex" + Chr(62) + "" + Chr(10) + "    #define USE_POWERFUL_REGEX 0" + Chr(10) + "    #pragma message(" + Chr(34) + "WARNING: srell.hpp not found. Falling back to limited std::regex. Lookbehinds will NOT work." + Chr(34) + ")" + Chr(10) + "#endif" + Chr(10) + "" + Chr(10) + allLibsToPutAtTop;
        }
        if (isNotHTVMfileEXTRA_INT == 1) {
            isNotHTVMfileEXTRA_LIB_INFO = allLibsToPutAtTop;
            isNotHTVMfileEXTRA_FUNCS_INFO = allFuncsToPutAtTop;
        }
        if (isNotHTVMfile2 == 0) {
            if (langToConvertTo == "cs" || langToConvertTo == "java") {
                htCode = Chr(10) + allFuncsToPutAtTop + Chr(10) + htCode;
            } else {
                if (langToConvertTo != "js") {
                    htCode = allLibsToPutAtTop + Chr(10) + allFuncsToPutAtTop + Chr(10) + htCode;
                } else {
                    if (useJavaScriptInAfullHTMLfile == "on") {
                        htCode = Chr(10) + allFuncsToPutAtTop + Chr(10) + htCode;
                    } else {
                        htCode = Chr(10) + allFuncsToPutAtTop + Chr(10) + htCode;
                    }
                }
            }
        }
        if (langToConvertTo == "cs") {
            htCode = allLibsToPutAtTop + Chr(10) + "class Program" + Chr(10) + "{" + Chr(10) + htCode;
        }
        if (langToConvertTo == "java") {
            htCode = allLibsToPutAtTop + Chr(10) + "import java.util.ArrayList;" + Chr(10) + "import java.util.List;" + Chr(10) + "import java.util.regex.Pattern;" + Chr(10) + "import java.util.*;" + Chr(10) + "public class Main" + Chr(10) + "{" + Chr(10) + htCode;
        }
        if (langToConvertTo == "go") {
            htCode = "package main" + Chr(10) + "import (" + Chr(10) + htCode;
        }
    }
    if (langToConvertTo != langFileExtension_2) {
        for (int A_Index313 = 0; A_Index313 < HTVM_Size(ospDic1) + 0; A_Index313++) {
            str00 = ospDic1[A_Index313];
            if (langToConvertTo == "rb") {
                if (SubStr(Trim(htCode), 1, 1) != "$") {
                    htCode = StrReplace(htCode, StrReplace(str00, "_", "_") + "_", "$" + str00 + "_");
                }
            }
        }
    }
    if (langToConvertTo == "rb") {
        htCode = StrReplace(htCode, "$$", "$");
        htCode = StrReplace(htCode, "$$", "$");
        htCode = StrReplace(htCode, "$$", "$");
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    HTVM_Append(ospDic, "end");
    int size_ospDic = HTVM_Size(ospDic);
    if (size_ospDic != 0) {
        for (int A_Index314 = 0; A_Index314 < size_ospDic + 0; A_Index314++) {
            HTVM_Pop(ospDic);
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    HTVM_Append(ospDic1, "end");
    int size_ospDic1 = HTVM_Size(ospDic1);
    if (size_ospDic1 != 0) {
        for (int A_Index315 = 0; A_Index315 < size_ospDic1 + 0; A_Index315++) {
            HTVM_Pop(ospDic1);
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    HTVM_Append(ospDic2, "end");
    int size_ospDic2 = HTVM_Size(ospDic2);
    if (size_ospDic2 != 0) {
        for (int A_Index316 = 0; A_Index316 < size_ospDic2 + 0; A_Index316++) {
            HTVM_Pop(ospDic2);
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    HTVM_Append(htCodeFixRubyGlobalVars_EXPOSED, "end");
    int size_htCodeFixRubyGlobalVars_EXPOSED = HTVM_Size(htCodeFixRubyGlobalVars_EXPOSED);
    if (size_htCodeFixRubyGlobalVars_EXPOSED != 0) {
        for (int A_Index317 = 0; A_Index317 < size_htCodeFixRubyGlobalVars_EXPOSED + 0; A_Index317++) {
            HTVM_Pop(htCodeFixRubyGlobalVars_EXPOSED);
        }
    }
    //;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;
    availableFuncsInHTVMInHTVM = "";
    saveAllArrayVarNamesSoWeCanDoAfix = "";
    for (int A_Index318 = 0; A_Index318 < theIdNumOfThe34 + 0; A_Index318++) {
        if (theIdNumOfThe34 == A_Index318 + 1) {
            if (langToConvertTo == langFileExtension_2) {
                if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index318 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index318 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                } else {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index318 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index318 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                }
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index318 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index318 + 1], keyWordEscpaeChar, "\\") + Chr(34));
            }
        } else {
            if (langToConvertTo == langFileExtension_2) {
                if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index318 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index318 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2));
                } else {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index318 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index318 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2));
                }
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index318 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index318 + 1], keyWordEscpaeChar, "\\"));
            }
        }
    }
    if (langToConvertTo == langFileExtension_2) {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, keyWordEscpaeChar_2 + Chr(34));
    } else {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, Chr(92) + Chr(34));
    }
    htCode = StrReplace(htCode, "std::string(" + Chr(34) + Chr(34) + ";),", "std::string(" + Chr(34) + Chr(34) + "),");
    std::string jsHTMLupCode = "<!doctype html>" + Chr(10) + "<html lang=" + Chr(34) + "en" + Chr(34) + ">" + Chr(10) + "    <head>" + Chr(10) + "        <meta charset=" + Chr(34) + "UTF-8" + Chr(34) + " />" + Chr(10) + "        <meta name=" + Chr(34) + "viewport" + Chr(34) + " content=" + Chr(34) + "width=device-width, initial-scale=1.0" + Chr(34) + " />" + Chr(10) + "        <title>HTVM</title>" + Chr(10) + "        <style>" + Chr(10) + "            body {" + Chr(10) + "                background-color: #202020;" + Chr(10) + "                font-family:" + Chr(10) + "                    " + Chr(34) + "Open Sans" + Chr(34) + "," + Chr(10) + "                    -apple-system," + Chr(10) + "                    BlinkMacSystemFont," + Chr(10) + "                    " + Chr(34) + "Segoe UI" + Chr(34) + "," + Chr(10) + "                    Roboto," + Chr(10) + "                    Oxygen-Sans," + Chr(10) + "                    Ubuntu," + Chr(10) + "                    Cantarell," + Chr(10) + "                    " + Chr(34) + "Helvetica Neue" + Chr(34) + "," + Chr(10) + "                    Helvetica," + Chr(10) + "                    Arial," + Chr(10) + "                    sans-serif;" + Chr(10) + "            }" + Chr(10) + "        </style>" + Chr(10) + allLibsToPutAtTop + Chr(10) + "</head>" + Chr(10) + "    <body>" + Chr(10) + "<script>";
    if (isNotHTVMfile2 == 0) {
        if (useJavaScriptInAfullHTMLfile == "on" && langToConvertTo == "js") {
            htCode = jsHTMLupCode + Chr(10) + htCode + Chr(10) + jsHTMLdownCode;
        }
        if (langToConvertTo == "cpp" && includeLibsInCppIf == 0) {
            htCode = "#include <iostream>" + Chr(10) + "#include <sstream>" + Chr(10) + "#include <any>" + Chr(10) + "#include <string>" + Chr(10) + "#include <cstdint>" + Chr(10) + "#include <algorithm>" + Chr(10) + "#include <vector>" + Chr(10) +  Chr(10) + htCode;
        }
        if (langToConvertTo == "cs") {
            htCode = Chr(10) + htCode;
        }
        if (langToConvertTo == "ahk") {
            htCode = "#EscapeChar \\" + Chr(10) + htCode;
        }
        if (langToConvertTo == "swift") {
            htCode = "import Foundation" + Chr(10) + htCode;
        }
        if (langToConvertTo == "dart" || langToConvertTo == "groovy") {
            htCode = StrReplace(htCode, Chr(92) + Chr(92) + Chr(92) + "$", Chr(92) + "$");
        }
        if (langToConvertTo == langFileExtension_2) {
            for (int A_Index319 = 0; A_Index319 < HTVM_Size(weAreInMLSarr) + 0; A_Index319++) {
                htCode = StrReplace(htCode, "aejsoydoxubviycbdgsut7eoy-ihsxbvhowadesdio6376e7wuwyuau--szd--AA" + STR(A_Index319) + "AA", weAreInMLSarr[A_Index319]);
            }
            if (SubStr(htCode, 1, 1) == Chr(10)) {
                htCode = StringTrimLeft(htCode, 1);
            }
        }
    }
    HTVM_Append(weAreInMLSarr, "end");
    int size_weAreInMLSarr = HTVM_Size(weAreInMLSarr);
    if (size_weAreInMLSarr != 0) {
        for (int A_Index320 = 0; A_Index320 < size_weAreInMLSarr + 0; A_Index320++) {
            HTVM_Pop(weAreInMLSarr);
        }
    }
    if (initializeBackendAndGUIInteractionWithLabelSubroutineLikeButConvertsToFunction_WAS_IN_PYTHON == 1) {
        htCode = htCode + Chr(10) + Chr(10) + "if __name__ == " + Chr(34) + "__main__" + Chr(34) + ":" + Chr(10) + "    # --- Cleaned up startup messages ---" + Chr(10) + "    # print(f" + Chr(34) + "--- Flask Routes ---" + Chr(34) + ") # REMOVED" + Chr(10) + "    # print(app.url_map) # REMOVED" + Chr(10) + "    # print(f" + Chr(34) + "--------------------" + Chr(34) + ") # REMOVED" + Chr(10) + "    # print(f" + Chr(34) + "Starting server on http://0.0.0.0:{HTVM_server_port_HTVM}" + Chr(34) + ") # REMOVED" + Chr(10) + "    " + Chr(10) + "    # KEEP This specific message:" + Chr(10) + "    print(f" + Chr(34) + "Root '/' will attempt to serve './{HTVM_DEFAULT_FILE_HTVM}' as configured." + Chr(34) + ")" + Chr(10) + "    " + Chr(10) + "    # print(" + Chr(34) + "Endpoints /hello and /goodbye (POST) expect PLAIN TEXT input and return PLAIN TEXT." + Chr(34) + ") # REMOVED" + Chr(10) + "" + Chr(10) + "    # Standard app run" + Chr(10) + "    app.run(host=" + Chr(34) + "0.0.0.0" + Chr(34) + ", port=HTVM_server_port_HTVM, debug=True)";
    }
    initializeBackendAndGUIInteractionWithLabelSubroutineLikeButConvertsToFunction_WAS_IN_PYTHON = 0;
    //print(htCode)
    return htCode;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void HTVMv2() {
    std::string argCODE = "";
    std::string argCODEfile = "";
    std::string argHTVMinstr = "";
    std::string argLangTo = "";
    std::string OUTCODE = "null";
    int numOfParams = 0;
    HTVM_v2_HTVM();
    if (noParams == true) {
        return;
    }
    std::vector<std::string> items321 = LoopParseFunc(str0);
    for (size_t A_Index321 = 0; A_Index321 < items321.size() + 0; A_Index321++) {
        std::string A_LoopField321 = items321[A_Index321 - 0];
        str00 = Trim(A_LoopField321);
        str00 = StringTrimRight(str00, 1);
    }
    //print("HTVM v2")
    if (HTVM_getLang_HTVM() == "cpp" || HTVM_getLang_HTVM() == "py") {
        if (HTVM_getLang_HTVM() == "cpp") {
            //print("CPP")
        }
        if (HTVM_getLang_HTVM() == "py") {
            //print("PY")
        }
        std::vector<std::string> items322 = LoopParseFunc(allArgs, "\n", "\r");
        for (size_t A_Index322 = 0; A_Index322 < items322.size() + 0; A_Index322++) {
            std::string A_LoopField322 = items322[A_Index322 - 0];
            if (A_Index322 == 0) {
                numOfParams++;
                argCODE = FileRead(Trim(A_LoopField322));
                argCODEfile = Trim(A_LoopField322);
            }
            else if (A_Index322 == 1) {
                numOfParams++;
                argHTVMinstr = Trim(A_LoopField322);
            }
            else if (A_Index322 == 2) {
                numOfParams++;
                argLangTo = Trim(A_LoopField322);
            } else {
                numOfParams++;
                HTVM_Append(argHTVMinstrMORE, Trim(A_LoopField322));
            }
        }
        //print("===============123431234===========start=====")
        for (int A_Index323 = 0; A_Index323 < HTVM_Size(argHTVMinstrMORE) + 0; A_Index323++) {
            //print(argHTVMinstrMORE[A_Index])
        }
        //print("===============123431234==========end======")
        //print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) . langToConvertTo)
        if (SubStrLastChars(argCODEfile, 4) == ".cpp" || SubStrLastChars(argCODEfile, 3) == ".py" || SubStrLastChars(argCODEfile, 3) == ".js" || SubStrLastChars(argCODEfile, 3) == ".go" || SubStrLastChars(argCODEfile, 4) == ".lua" || SubStrLastChars(argCODEfile, 3) == ".cs" || SubStrLastChars(argCODEfile, 5) == ".java" || SubStrLastChars(argCODEfile, 3) == ".kt" || SubStrLastChars(argCODEfile, 3) == ".rb" || SubStrLastChars(argCODEfile, 4) == ".nim" || SubStrLastChars(argCODEfile, 4) == ".ahk" || SubStrLastChars(argCODEfile, 6) == ".swift" || SubStrLastChars(argCODEfile, 5) == ".dart" || SubStrLastChars(argCODEfile, 3) == ".ts" || SubStrLastChars(argCODEfile, 7) == ".groovy" || SubStrLastChars(argCODEfile, StrLen("." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), Chr(10), 2)))) == "." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), Chr(10), 2)) && numOfParams == 2) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (SubStrLastChars(argCODEfile, 4) == ".cpp") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "cpp");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".py") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "py");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".js") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "js");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".go") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "go");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 4) == ".lua") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "lua");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".cs") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "cs");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 5) == ".java") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "java");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".kt") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "kt");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".rb") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "rb");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 4) == ".nim") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "nim");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 4) == ".ahk") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "ahk");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 6) == ".swift") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "swift");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 5) == ".dart") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "dart");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".ts") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "ts");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 7) == ".groovy") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "groovy");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, StrLen("." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), Chr(10), 2)))) == "." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), Chr(10), 2))) {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), Chr(10), 2)));
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            } else {
                //print("INVALID LANG!!!")
                return;
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        } else {
            if (argLangTo != "") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "full", argLangTo);
            } else {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "full");
            }
        }
        print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        if (langToConvertTo == "js" && useJavaScriptInAfullHTMLfile == "on") {
            FileDelete(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + "html");
            FileAppend(OUTCODE, StringTrimRight(argCODEfile, StrLen(langFileExtension)) + "html");
        } else {
            FileDelete(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
            FileAppend(OUTCODE, StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        }
    }
    if (HTVM_getLang_HTVM() == "js") {
        //print("JS")
    }
}
int main(int argc, char* argv[]) {
    HTVMv2();

    return 0;
}