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

// Print function for const char* specifically
void print(const char* value) {
    std::cout << std::string(value) << std::endl;  // Convert const char* to std::string
}
// Print function that converts all types to string if needed
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

double Exp(double value) {
    return std::exp(value);
}

double Log(double value) {
    return std::log10(value);
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

std::string RegExReplace(const std::string& inputStr, const std::string& regexPattern, const std::string& replacement) {
    std::regex re(regexPattern, std::regex_constants::ECMAScript | std::regex_constants::multiline);
    return std::regex_replace(inputStr, re, replacement);
}

int RegExMatch(const std::string& haystack, const std::string& needle) {
    std::regex re(needle);
    std::smatch match;
    if (std::regex_search(haystack, match, re)) {
        return match.position(0) + 1; // 1-based index
    }
    return 0; // No match
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

void HTVM_Insert(std::vector<std::string>& arr, size_t index, const std::string& value) {
    if (index <= arr.size()) arr.insert(arr.begin() + index, value);
}
void HTVM_Insert(std::vector<std::string>& arr, size_t index, const char* value) {
    if (index <= arr.size()) arr.insert(arr.begin() + index, std::string(value));
}
void HTVM_Insert(std::vector<int>& arr, size_t index, int value) {
    if (index <= arr.size()) arr.insert(arr.begin() + index, value);
}
void HTVM_Insert(std::vector<float>& arr, size_t index, float value) {
    if (index <= arr.size()) arr.insert(arr.begin() + index, value);
}
void HTVM_Insert(std::vector<bool>& arr, size_t index, bool value) {
    if (index <= arr.size()) arr.insert(arr.begin() + index, value);
}

// Remove by index for std::vector<std::string>
void HTVM_Remove(std::vector<std::string>& arr, size_t index) {
    if (index < arr.size()) {
        arr.erase(arr.begin() + index);
    }
}
// Remove by index for std::vector<int>
void HTVM_Remove(std::vector<int>& arr, size_t index) {
    if (index < arr.size()) {
        arr.erase(arr.begin() + index);
    }
}
// Remove by index for std::vector<float>
void HTVM_Remove(std::vector<float>& arr, size_t index) {
    if (index < arr.size()) {
        arr.erase(arr.begin() + index);
    }
}
// Remove by index for std::vector<bool>
void HTVM_Remove(std::vector<bool>& arr, size_t index) {
    if (index < arr.size()) {
        arr.erase(arr.begin() + index);
    }
}

// IndexOf for std::vector<std::string>
int HTVM_IndexOf(const std::vector<std::string>& arr, const std::string& value) {
    auto it = std::find(arr.begin(), arr.end(), value);
    return (it != arr.end()) ? static_cast<int>(std::distance(arr.begin(), it)) : -1;
}
// Overload for string literals
int HTVM_IndexOf(const std::vector<std::string>& arr, const char* value) {
    return HTVM_IndexOf(arr, std::string(value));
}
// IndexOf for std::vector<int>
int HTVM_IndexOf(const std::vector<int>& arr, int value) {
    auto it = std::find(arr.begin(), arr.end(), value);
    return (it != arr.end()) ? static_cast<int>(std::distance(arr.begin(), it)) : -1;
}
// IndexOf for std::vector<float>
int HTVM_IndexOf(const std::vector<float>& arr, float value) {
    auto it = std::find(arr.begin(), arr.end(), value);
    return (it != arr.end()) ? static_cast<int>(std::distance(arr.begin(), it)) : -1;
}
// IndexOf for std::vector<bool>
int HTVM_IndexOf(const std::vector<bool>& arr, bool value) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == value) {
            return static_cast<int>(i);
        }
    }
    return -1;
}


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
std::string keyWordMethod = "";
std::string keyWordDefObj = "";
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
std::string keyWordMethod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordDefObj_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
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
std::vector<std::string> ospDic;
std::vector<std::string> ospDic1;
std::vector<std::string> ospDic2;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string fixCSandJAVAstaticBugForFunc(std::string line) {
    std::string out = "";
    int haveWeSeenMainFunc = 0;
    std::vector<std::string> items1 = LoopParseFunc(line, "\n", "\r");
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        if (haveWeSeenMainFunc == 0 && InStr(A_LoopField1, "    static ")) {
            out += StrReplace(A_LoopField1, "    static ", "    ") + Chr(10);
        } else {
            out += A_LoopField1 + Chr(10);
        }
        if (InStr(StrLower(A_LoopField1), " main(")) {
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
    if (RegExMatch(line, "^\\d+(\\.\\d+)?$")) {
        for (int A_Index2 = 0; A_Index2 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint8) + 0; A_Index2++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint8[A_Index2]) == Trim(varName)) {
                if (langToConvertTo == "java") {
                    out = "(byte) " + line;
                }
                if (langToConvertTo == "kt") {
                    out = line + "u";
                }
            }
        }
        for (int A_Index3 = 0; A_Index3 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint16) + 0; A_Index3++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint16[A_Index3]) == Trim(varName)) {
                if (langToConvertTo == "java") {
                    out = "(short) " + line;
                }
                if (langToConvertTo == "kt") {
                    out = line + "u";
                }
            }
        }
        for (int A_Index4 = 0; A_Index4 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint32) + 0; A_Index4++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint32[A_Index4]) == Trim(varName)) {
                if (langToConvertTo == "kt") {
                    out = line + "u";
                }
                if (langToConvertTo == "nim") {
                    out = line + "'u32";
                }
            }
        }
        for (int A_Index5 = 0; A_Index5 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint64) + 0; A_Index5++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint64[A_Index5]) == Trim(varName)) {
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
        for (int A_Index6 = 0; A_Index6 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_int64) + 0; A_Index6++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_int64[A_Index6]) == Trim(varName)) {
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
        for (int A_Index7 = 0; A_Index7 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_float) + 0; A_Index7++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_float[A_Index7]) == Trim(varName)) {
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
    theCodeCommands = StrReplace(theCodeCommands, "%", "");
    if (mode == "check") {
        std::vector<std::string> items8 = LoopParseFunc(keyWordsCommands, "|");
        for (size_t A_Index8 = 0; A_Index8 < items8.size() + 0; A_Index8++) {
            std::string A_LoopField8 = items8[A_Index8 - 0];
            std::vector<std::string> items9 = LoopParseFunc(A_LoopField8, ",");
            for (size_t A_Index9 = 0; A_Index9 < items9.size() + 0; A_Index9++) {
                std::string A_LoopField9 = items9[A_Index9 - 0];
                if (A_Index9 == 0) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField9 + ", ")) == StrLower(A_LoopField9 + ", ")) {
                        //MsgBox, true
                        return "true";
                    }
                }
                if (A_Index9 == 0) {
                    if (theCodeCommands == A_LoopField9) {
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
        std::vector<std::string> items10 = LoopParseFunc(keyWordsCommands, "|");
        for (size_t A_Index10 = 0; A_Index10 < items10.size() + 0; A_Index10++) {
            std::string A_LoopField10 = items10[A_Index10 - 0];
            AIndex = A_Index10;
            std::vector<std::string> items11 = LoopParseFunc(A_LoopField10, ",");
            for (size_t A_Index11 = 0; A_Index11 < items11.size() + 0; A_Index11++) {
                std::string A_LoopField11 = items11[A_Index11 - 0];
                if (A_Index11 == 0) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField11 + ", ")) == StrLower(A_LoopField11 + ", ")) {
                        //MsgBox, true
                        keyWordsCommandsNumLine = AIndex;
                        break;
                    }
                }
                if (A_Index11 == 0) {
                    //MsgBox, %theCodeCommands% = %A_LoopField11%
                    if (theCodeCommands == A_LoopField11) {
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
        std::vector<std::string> theCodeCommand;
        theCodeCommands = Trim(theCodeCommands);
        std::vector<std::string> items12 = LoopParseFunc(theCodeCommands, ",");
        for (size_t A_Index12 = 0; A_Index12 < items12.size() + 0; A_Index12++) {
            std::string A_LoopField12 = items12[A_Index12 - 0];
            HTVM_Append(theCodeCommand, Trim(A_LoopField12));
            //MsgBox, % A_LoopField12
        }
        std::vector<std::string> items13 = LoopParseFunc(keyWordsCommands, "|");
        for (size_t A_Index13 = 0; A_Index13 < items13.size() + 0; A_Index13++) {
            std::string A_LoopField13 = items13[A_Index13 - 0];
            if (keyWordsCommandsNumLine == A_Index13) {
                //MsgBox, % A_LoopField13
                std::vector<std::string> items14 = LoopParseFunc(A_LoopField13, ",");
                for (size_t A_Index14 = 0; A_Index14 < items14.size() + 0; A_Index14++) {
                    std::string A_LoopField14 = items14[A_Index14 - 0];
                    if (A_Index14 == 0) {
                        outConstuctTheOutFromTheCommandsFucnName = A_LoopField14;
                    }
                    else if (A_Index14 == 1) {
                        //MsgBox, % A_LoopField14
                        if (A_LoopField14 == "lineTranspile") {
                            outConstuctTheOutFromTheCommandsLineTranspile = 1;
                        }
                        if (A_LoopField14 == "OUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField14 == "INOUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField14 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField14, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    }
                    else if (A_Index14 == 2) {
                        if (outConstuctTheOutFromTheCommandsLineTranspile == 1) {
                            outConstuctTheOutFromTheCommandsLineTranspileText = A_LoopField14;
                        }
                        if (A_LoopField14 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField14, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    } else {
                        //MsgBox, % theCodeCommand[theCodeCommandNum]
                        if (InStr(A_LoopField14, Chr(39))) {
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
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " = " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ")" + semicolon;
            } else {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " = " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ", " + outConstuctTheOutFromTheCommandsParams + ")" + semicolon;
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
            outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsLineTranspileText;
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
    std::vector<std::string> items15 = LoopParseFunc(line);
    for (size_t A_Index15 = 0; A_Index15 < items15.size() + 0; A_Index15++) {
        std::string A_LoopField15 = items15[A_Index15 - 0];
        HTVM_Append(lineArr, A_LoopField15);
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
    std::string char1 = "";
    std::string char2 = "";
    std::string char3 = "";
    std::string char4 = "";
    int isMatch = 0;
    sildingLine = "";
    isStart = 1;
    i1 = 0;
    hasFound = 0;
    hasFound2 = 0;
    isStartTrue = 0;
    isEndTrue = 0;
    for (int A_Index16 = 0; A_Index16 < HTVM_Size(lineArr) + 0; A_Index16++) {
        char1 = "";
        char2 = "";
        char3 = "";
        char4 = "";
        isMatch = 0;
        if (A_Index16 != 0) {
            isStart = 0;
        }
        sildingLine = "";
        for (int A_Index17 = 0; A_Index17 < matchStringLEN + 0; A_Index17++) {
            if (A_Index17 + i1 <= HTVM_Size(lineArr) - 1) {
                sildingLine += lineArr[A_Index17 + i1];
            }
        }
        if (StrLen(sildingLine) < matchStringLEN) {
            break;
        }
        if (sildingLine == matchString) {
            hasFound = 1;
            if (isStart != 1) {
                char1 = lineArr[i1 - 1];
                char2 = lineArr[i1];
            } else {
                isStartTrue = 1;
            }
            if (i1 + matchStringLEN < HTVM_Size(lineArr)) {
                char3 = lineArr[i1 + matchStringLEN - 1];
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
        if (isMatch == 1) {
            if (HTVM_Size(allPosForReplacing) > 0) {
                for (int A_Index18 = 0; A_Index18 < HTVM_Size(allPosForReplacing) + 0; A_Index18++) {
                    if (i1 + 1 != allPosForReplacing[A_Index18]) {
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
    if (HTVM_Size(allPosForReplacing) > 0) {
        int l2 = 0;
        int currentPos = 0;
        int onceEnd = 0;
        for (int A_Index19 = 0; A_Index19 < HTVM_Size(allPosForReplacing) + 0; A_Index19++) {
            if (A_Index19 == 0) {
                currentPos = allPosForReplacing[A_Index19];
            } else {
                currentPos = allPosForReplacing[A_Index19] - (matchStringLEN - replaceStringLEN);
            }
            onceEnd = 0;
            std::vector<std::string> items20 = LoopParseFunc(lineOut);
            for (size_t A_Index20 = 0; A_Index20 < items20.size() + 0; A_Index20++) {
                std::string A_LoopField20 = items20[A_Index20 - 0];
                if (A_Index20 + 2 > currentPos && A_Index20 + 1 < currentPos + matchStringLEN) {
                    onceEnd++;
                    if (onceEnd == 1) {
                        lineTEMP += replaceString;
                    }
                } else {
                    lineTEMP += A_LoopField20;
                }
            }
            lineOut = lineTEMP;
            lineTEMP = "";
            l2++;
        }
    } else {
        return line;
    }
    return lineOut;
}
std::string SubStrLastChars(std::string text, int numOfChars) {
    std::string LastOut = "";
    int NumOfChars = 0;
    std::vector<std::string> items21 = LoopParseFunc(text);
    for (size_t A_Index21 = 0; A_Index21 < items21.size() + 0; A_Index21++) {
        std::string A_LoopField21 = items21[A_Index21 - 0];
        NumOfChars++;
    }
    for (int A_Index22 = 0; A_Index22 < numOfChars + 0; A_Index22++) {
        NumOfChars--;
    }
    std::vector<std::string> items23 = LoopParseFunc(text);
    for (size_t A_Index23 = 0; A_Index23 < items23.size() + 0; A_Index23++) {
        std::string A_LoopField23 = items23[A_Index23 - 0];
        if (A_Index23 >= NumOfChars) {
            LastOut += A_LoopField23;
        }
    }
    return LastOut;
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
            result += spaces(indentLevel) + "}\n";
        }
        // Add opening brace for new blocks
        if (getLastChar(stripped) == ":" && SubStr(StrLower(Trim(A_LoopField29)), 1, StrLen(StrLower(keyWordComment))) != StrLower(keyWordComment)) {
            result += SubStr(line, 1, -1) + " {\n";
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
        result += spaces(indentLevel) + "}\n";
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
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordDefObj))) == StrLower(keyWordDefObj)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordMethod))) == StrLower(keyWordMethod)) {
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
std::string fixDoubleQuotes(std::string line, int isLast) {
    std::string out = "";
    if (isLast == 0) {
        out = StrReplace(line, Chr(92) + Chr(92) + Chr(34), Chr(92) + Chr(34));
    } else {
        line = StringTrimRight(line, 1);
        out = StrReplace(line, Chr(92) + Chr(92) + Chr(34), Chr(92) + Chr(34)) + Chr(34);
    }
    return out;
}
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
std::string arrayParserTranspiler1(std::string line, std::string arrayMethodStr, int mode) {
    if (InStr(line, arrayMethodStr) == false) {
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
        if (HTVM_Size(arrAll) - StrLen(arrayMethodStr) + 1 == i1) {
            break;
        }
        for (int A_Index45 = 0; A_Index45 < StrLen(arrayMethodStr) + 0; A_Index45++) {
            tempHold += arrAll[A_Index45 + i1];
        }
        i1++;
        //print(tempHold)
        if (tempHold == arrayMethodStr) {
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
                //print(A_LoopField57)
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
                outOSP += A_LoopField57 + "\n";
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
                //print(A_LoopField58)
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
                outOSP += A_LoopField58 + "\n";
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
    if (OSPhelp(line, keyWordDefObj)) {
        std::vector<std::string> items59 = LoopParseFunc(line, "\n", "\r");
        for (size_t A_Index59 = 0; A_Index59 < items59.size() + 0; A_Index59++) {
            std::string A_LoopField59 = items59[A_Index59 - 0];
            if (SubStr(Trim(StrLower(A_LoopField59)), 1, StrLen(keyWordDefObj)) == StrLower(keyWordDefObj) && lookAhead[A_Index59 + 1] == "{") {
                //print(A_LoopField59)
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
                outOSP += A_LoopField59 + "\n";
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
        if (SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordDefObj)) == StrLower(keyWordDefObj) && lookAhead[A_Index60 + 1] == "{") {
            str1 = Trim(StringTrimLeft(A_LoopField60, StrLen(SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordDefObj)))));
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
        if (SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordMethod)) == StrLower(keyWordMethod) && lookAhead[A_Index60 + 1] == "{") {
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
            //print(A_LoopField60)
            alredy = 2;
        }
        if (SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordAlliance)) == StrLower(keyWordAlliance) && lookAhead[A_Index60 + 1] == "{") {
            str1 = Trim(StringTrimLeft(A_LoopField60, StrLen(SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordAlliance)))));
            HTVM_Append(ospDic, str1);
            //print(A_LoopField60)
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
            outOSP += A_LoopField60 + "\n";
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
std::string ospHELP2(std::string line) {
    std::string outHelp = "";
    int outHelpInt = 0;
    int outHelpInt2 = 1;
    std::vector<std::string> items70 = LoopParseFunc(line);
    for (size_t A_Index70 = 0; A_Index70 < items70.size() + 0; A_Index70++) {
        std::string A_LoopField70 = items70[A_Index70 - 0];
        if (A_LoopField70 == ".") {
            outHelpInt2++;
        }
    }
    outHelpInt = StrLen(StrSplit(line, ".", outHelpInt2));
    outHelpInt++;
    outHelp = StringTrimRight(line, outHelpInt);
    return outHelp;
}
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
        for (int A_Index71 = 0; A_Index71 < HTVM_Size(ospDic1) + 0; A_Index71++) {
            str00 = ospDic1[A_Index71];
            if (langToConvertTo == "rb") {
                expression = StrReplace(expression, StrReplace(str00, "_", ".") + ".", "$" + str00 + "_");
            } else {
                expression = StrReplace(expression, StrReplace(str00, "_", ".") + ".", str00 + "_");
            }
        }
        for (int A_Index72 = 0; A_Index72 < HTVM_Size(ospDic2) + 0; A_Index72++) {
            str00 = ospDic2[A_Index72];
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
    for (int A_Index73 = 0; A_Index73 < 29 + 0; A_Index73++) {
        if (InStr(expression, fullLangAllOperators_HELP[A_Index73])) {
            if (A_Index73 == 0 || A_Index73 == 1 || A_Index73 == 2) {
                expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index73] + "\\b", fullLangAllOperators[A_Index73]);
            } else {
                if (A_Index73 == 19) {
                    if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index73] + "\\b", "not");
                    } else {
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index73] + "\\b", "!");
                    }
                    if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
                        expression = RegExReplace(expression, "!([\\w]+)", "not $1");
                    }
                    expression = StrReplace(expression, " not= ", " != ");
                } else {
                    expression = StrReplace(expression, " " + fullLangAllOperators_HELP[A_Index73] + " ", " " + fullLangAllOperators[A_Index73] + " ");
                    if (A_Index73 == 28) {
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
    std::vector<std::string> items74 = LoopParseFunc(line, "\n", "\r");
    for (size_t A_Index74 = 0; A_Index74 < items74.size() + 0; A_Index74++) {
        std::string A_LoopField74 = items74[A_Index74 - 0];
        if (InStr(A_LoopField74, " " + keyWordAssign + " ") || InStr(A_LoopField74, " " + keyWordAssignAdd + " ") || InStr(A_LoopField74, " " + keyWordAssignConcat + " ") || InStr(A_LoopField74, " " + keyWordAssignSub + " ") || InStr(A_LoopField74, " " + keyWordAssignMul + " ") || InStr(A_LoopField74, " " + keyWordAssignDiv + " ") || InStr(A_LoopField74, " " + keyWordAssignMod + " ") || InStr(A_LoopField74, " " + keyWordAssignShiftLeft + " ") || InStr(A_LoopField74, " " + keyWordAssignShiftRight + " ") || InStr(A_LoopField74, " " + keyWordLogicalAssignShiftRight + " ") || InStr(A_LoopField74, " " + keyWordAssignBitAnd + " ") || InStr(A_LoopField74, " " + keyWordAssignBitOr + " ") || InStr(A_LoopField74, " " + keyWordAssignBitXor + " ") && lineDone == 0) {
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
            if (InStr(A_LoopField74, " " + keyWordAssign + " ")) {
                str1 = StrSplit(A_LoopField74, " " + keyWordAssign + " ", 1);
                str6 = StrSplit(A_LoopField74, " " + keyWordAssign + " ", 2);
                str10 = keyWordAssign;
                str11 = keyWordAssign_2;
                if (langToConvertTo == "ahk") {
                    str12 = ":=";
                } else {
                    str12 = "=";
                }
            }
            else if (InStr(A_LoopField74, " " + keyWordAssignAdd + " ")) {
                str1 = StrSplit(A_LoopField74, " " + keyWordAssignAdd + " ", 1);
                str6 = StrSplit(A_LoopField74, " " + keyWordAssignAdd + " ", 2);
                str10 = keyWordAssignAdd;
                str11 = keyWordAssignAdd_2;
                str12 = "+=";
            }
            else if (InStr(A_LoopField74, " " + keyWordAssignConcat + " ")) {
                str1 = StrSplit(A_LoopField74, " " + keyWordAssignConcat + " ", 1);
                str6 = StrSplit(A_LoopField74, " " + keyWordAssignConcat + " ", 2);
                str10 = keyWordAssignConcat;
                str11 = keyWordAssignConcat_2;
                if (langToConvertTo == "ahk") {
                    str12 = ".=";
                } else {
                    str12 = "+=";
                }
            }
            else if (InStr(A_LoopField74, " " + keyWordAssignSub + " ")) {
                str1 = StrSplit(A_LoopField74, " " + keyWordAssignSub + " ", 1);
                str6 = StrSplit(A_LoopField74, " " + keyWordAssignSub + " ", 2);
                str10 = keyWordAssignSub;
                str11 = keyWordAssignSub_2;
                str12 = "-=";
            }
            else if (InStr(A_LoopField74, " " + keyWordAssignMul + " ")) {
                str1 = StrSplit(A_LoopField74, " " + keyWordAssignMul + " ", 1);
                str6 = StrSplit(A_LoopField74, " " + keyWordAssignMul + " ", 2);
                str10 = keyWordAssignMul;
                str11 = keyWordAssignMul_2;
                str12 = "*=";
            }
            else if (InStr(A_LoopField74, " " + keyWordAssignDiv + " ")) {
                str1 = StrSplit(A_LoopField74, " " + keyWordAssignDiv + " ", 1);
                str6 = StrSplit(A_LoopField74, " " + keyWordAssignDiv + " ", 2);
                str10 = keyWordAssignDiv;
                str11 = keyWordAssignDiv_2;
                str12 = "/=";
            }
            else if (InStr(A_LoopField74, " " + keyWordAssignMod + " ")) {
                str1 = StrSplit(A_LoopField74, " " + keyWordAssignMod + " ", 1);
                str6 = StrSplit(A_LoopField74, " " + keyWordAssignMod + " ", 2);
                str10 = keyWordAssignMod;
                str11 = keyWordAssignMod_2;
                str12 = "%=";
            }
            else if (InStr(A_LoopField74, " " + keyWordAssignShiftLeft + " ")) {
                str1 = StrSplit(A_LoopField74, " " + keyWordAssignShiftLeft + " ", 1);
                str6 = StrSplit(A_LoopField74, " " + keyWordAssignShiftLeft + " ", 2);
                str10 = keyWordAssignShiftLeft;
                str11 = keyWordAssignShiftLeft_2;
                str12 = "<<=";
            }
            else if (InStr(A_LoopField74, " " + keyWordAssignShiftRight + " ")) {
                str1 = StrSplit(A_LoopField74, " " + keyWordAssignShiftRight + " ", 1);
                str6 = StrSplit(A_LoopField74, " " + keyWordAssignShiftRight + " ", 2);
                str10 = keyWordAssignShiftRight;
                str11 = keyWordAssignShiftRight_2;
                str12 = ">>=";
            }
            else if (InStr(A_LoopField74, " " + keyWordLogicalAssignShiftRight + " ")) {
                str1 = StrSplit(A_LoopField74, " " + keyWordLogicalAssignShiftRight + " ", 1);
                str6 = StrSplit(A_LoopField74, " " + keyWordLogicalAssignShiftRight + " ", 2);
                str10 = keyWordLogicalAssignShiftRight;
                str11 = keyWordLogicalAssignShiftRight_2;
                str12 = ">>>=";
            }
            else if (InStr(A_LoopField74, " " + keyWordAssignBitAnd + " ")) {
                str1 = StrSplit(A_LoopField74, " " + keyWordAssignBitAnd + " ", 1);
                str6 = StrSplit(A_LoopField74, " " + keyWordAssignBitAnd + " ", 2);
                str10 = keyWordAssignBitAnd;
                str11 = keyWordAssignBitAnd_2;
                str12 = "&=";
            }
            else if (InStr(A_LoopField74, " " + keyWordAssignBitOr + " ")) {
                str1 = StrSplit(A_LoopField74, " " + keyWordAssignBitOr + " ", 1);
                str6 = StrSplit(A_LoopField74, " " + keyWordAssignBitOr + " ", 2);
                str10 = keyWordAssignBitOr;
                str11 = keyWordAssignBitOr_2;
                str12 = "|=";
            }
            else if (InStr(A_LoopField74, " " + keyWordAssignBitXor + " ")) {
                str1 = StrSplit(A_LoopField74, " " + keyWordAssignBitXor + " ", 1);
                str6 = StrSplit(A_LoopField74, " " + keyWordAssignBitXor + " ", 2);
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
            if (InStr(ALoopField, " ") == false) {
                lineDone = 1;
                str1 = lineOspHelpLine + Trim(str1);
                str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str1);
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
                    if (InStr(str1, "[")) {
                        // Convert arr[something] to arr.set(something, value);
                        str1 = RegExReplace(str1, "(\\b[A-Za-z_]\\w*)\\s*\\[(.*?)\\]", "$1.set($2, ");
                        str4 = str1 + str6 + ");";
                    } else {
                        str4 = str1 + " " + str12 + " " + str6 + ";";
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
                    std::vector<std::string> items75 = LoopParseFunc(str1, " ");
                    for (size_t A_Index75 = 0; A_Index75 < items75.size() + 0; A_Index75++) {
                        std::string A_LoopField75 = items75[A_Index75 - 0];
                        str2 = A_LoopField75;
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
                                str4 = keyWordConst_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = keyWordConst_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordConst_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = keyWordConst_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
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
                            str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                        } else {
                            str4 = "val " + str2 + " = " + str6;
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
                            str4 = "let " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " = " + str6;
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
                                str4 = keyWordConst_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = keyWordConst_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordConst_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = keyWordConst_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
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
                    std::vector<std::string> items76 = LoopParseFunc(str1, " ");
                    for (size_t A_Index76 = 0; A_Index76 < items76.size() + 0; A_Index76++) {
                        std::string A_LoopField76 = items76[A_Index76 - 0];
                        str2 = A_LoopField76;
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
                    str3 = getFuncTypeConvert(str3);
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            str6 = "{" + str6 + "}";
                        } else {
                            str6 = "[" + str6 + "]";
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
                        str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " " + str12 + " [" + str6 + "]";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                    }
                    if (langToConvertTo == "go") {
                        str4 = str2 + " := " + str3 + "{" + str6 + "}";
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " " + str12 + " {" + str6 + "}";
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = [" + str6 + "]";
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := [" + str6 + "]";
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " = [" + str6 + "];";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " = [" + str6 + "]";
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
                    std::vector<std::string> items77 = LoopParseFunc(str1, " ");
                    for (size_t A_Index77 = 0; A_Index77 < items77.size() + 0; A_Index77++) {
                        std::string A_LoopField77 = items77[A_Index77 - 0];
                        str2 = A_LoopField77;
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
                    str3 = getFuncTypeConvert(str3);
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            str6 = "{" + str6 + "}";
                        } else {
                            str6 = "[" + str6 + "]";
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
                        str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " " + str12 + " [" + str6 + "]";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                    }
                    if (langToConvertTo == "go") {
                        str4 = str2 + " := " + str3 + "{" + str6 + "}";
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " " + str12 + " {" + str6 + "}";
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = [" + str6 + "]";
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := [" + str6 + "]";
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " = [" + str6 + "];";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " = [" + str6 + "]";
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
                std::vector<std::string> items78 = LoopParseFunc(str1, " ");
                for (size_t A_Index78 = 0; A_Index78 < items78.size() + 0; A_Index78++) {
                    std::string A_LoopField78 = items78[A_Index78 - 0];
                    str2 = A_LoopField78;
                }
                str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                str2 = lineOspHelpLine + Trim(str2);
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    str3 = getFuncTypeConvert(str3);
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            str6 = "{" + str6 + "}";
                        } else {
                            str6 = "[" + str6 + "]";
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
                        str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " " + str12 + " [" + str6 + "]";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                    }
                    if (langToConvertTo == "go") {
                        str4 = str2 + " := " + str3 + "{" + str6 + "}";
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " " + str12 + " {" + str6 + "}";
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = [" + str6 + "]";
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := [" + str6 + "]";
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " = [" + str6 + "];";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " = [" + str6 + "]";
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
                    str3 = getFuncTypeConvert(str3);
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            str6 = "{" + str6 + "}";
                        } else {
                            str6 = "[" + str6 + "]";
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
                        str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " " + str12 + " [" + str6 + "]";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                    }
                    if (langToConvertTo == "go") {
                        str4 = str2 + " := " + str3 + "{" + str6 + "}";
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " " + str12 + " {" + str6 + "}";
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = [" + str6 + "]";
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := [" + str6 + "]";
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " = [" + str6 + "];";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str2 + " = [" + str6 + "]";
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
        else if (SubStr(Trim(A_LoopField74), 1, StrLen(keyWordVar)) == keyWordVar && lineDone == 0) {
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
            if (usePostfixTypeForTypeDefinition == "off") {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(Trim(A_LoopField74), StrLen(keyWordVar)));
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                std::vector<std::string> items79 = LoopParseFunc(str1, " ");
                for (size_t A_Index79 = 0; A_Index79 < items79.size() + 0; A_Index79++) {
                    std::string A_LoopField79 = items79[A_Index79 - 0];
                    str2 = A_LoopField79;
                }
                str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                str2 = lineOspHelpLine + Trim(str2);
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
            } else {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(Trim(A_LoopField74), StrLen(keyWordVar)));
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
                str3 = Trim(StrSplit(str1, ":", 2));
                // str2 = var name
                // str3 = type
            }
            if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
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
                    str4 = "val " + str2 + " = " + str3 + "()";
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
        else if (SubStr(Trim(A_LoopField74), 1, StrLen(keyWordLet)) == keyWordLet && lineDone == 0) {
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
            if (usePostfixTypeForTypeDefinition == "off") {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(Trim(A_LoopField74), StrLen(keyWordLet)));
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                std::vector<std::string> items80 = LoopParseFunc(str1, " ");
                for (size_t A_Index80 = 0; A_Index80 < items80.size() + 0; A_Index80++) {
                    std::string A_LoopField80 = items80[A_Index80 - 0];
                    str2 = A_LoopField80;
                }
                str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                str2 = lineOspHelpLine + Trim(str2);
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
            } else {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(Trim(A_LoopField74), StrLen(keyWordLet)));
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
                    str4 = "val " + str2 + " = " + str3 + "()";
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
        else if (SubStr(Trim(A_LoopField74), 1, StrLen(keyWordDouble + " ")) == keyWordDouble + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordChar + " ")) == keyWordChar + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordUint8 + " ")) == keyWordUint8 + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordUint16 + " ")) == keyWordUint16 + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordUint32 + " ")) == keyWordUint32 + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordUint64 + " ")) == keyWordUint64 + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordINT + " ")) == keyWordINT + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordSTR + " ")) == keyWordSTR + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordBOOL + " ")) == keyWordBOOL + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordFLOAT + " ")) == keyWordFLOAT + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordINT8 + " ")) == keyWordINT8 + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordINT16 + " ")) == keyWordINT16 + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordINT32 + " ")) == keyWordINT32 + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordINT64 + " ")) == keyWordINT64 + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordArrayDefinition + " ")) == keyWordArrayDefinition + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordArrayOfIntegersDefinition + " ")) == keyWordArrayOfIntegersDefinition + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordArrayOfStringsDefinition + " ")) == keyWordArrayOfStringsDefinition + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordArrayOfFloatingPointNumbersDefinition + " ")) == keyWordArrayOfFloatingPointNumbersDefinition + " " || SubStr(Trim(A_LoopField74), 1, StrLen(keyWordArrayOfBooleansDefinition + " ")) == keyWordArrayOfBooleansDefinition + " " && usePrefixTypeForTypeDefinition == "on" && lineDone == 0) {
            lineDone = 1;
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
            str1 = Trim(A_LoopField74);
            if (SubStrLastChars(str1, 1) == ";") {
                str1 = StringTrimRight(str1, 1);
            }
            std::vector<std::string> items81 = LoopParseFunc(str1, " ");
            for (size_t A_Index81 = 0; A_Index81 < items81.size() + 0; A_Index81++) {
                std::string A_LoopField81 = items81[A_Index81 - 0];
                str2 = A_LoopField81;
            }
            str3 = Trim(StringTrimRight(str1, StrLen(str2)));
            str2 = lineOspHelpLine + Trim(str2);
            // str2 = var name
            // str3 = type
            HTVM_Append(allVarsSoWeDontReDecVars, str2);
            if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
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
                    str4 = "val " + str2 + " = " + str3 + "()";
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
        else if (RegExMatch(Trim(A_LoopField74), "^[a-zA-Z_][a-zA-Z0-9_]*: [^:]*;?$") && usePostfixTypeForTypeDefinition == "on" && lineDone == 0) {
            lineDone = 1;
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
            str1 = Trim(A_LoopField74);
            if (SubStrLastChars(str1, 1) == ";") {
                str1 = StringTrimRight(str1, 1);
            }
            str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
            str3 = Trim(StrSplit(str1, ":", 2));
            // str2 = var name
            // str3 = type
            HTVM_Append(allVarsSoWeDontReDecVars, str2);
            if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
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
                    str4 = "val " + str2 + " = " + str3 + "()";
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
            htCodeOUTOUT += A_LoopField74 + Chr(10);
        }
    }
    htCodeOUTOUT = StringTrimRight(htCodeOUTOUT, 1);
    return htCodeOUTOUT;
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
std::vector<std::string> slidingWinFixCommentsRmFUNC(std::string line) {
    std::vector<std::string> slidingWinFixCommentsRmFFFF;
    std::vector<std::string> items82 = LoopParseFunc(line);
    for (size_t A_Index82 = 0; A_Index82 < items82.size() + 0; A_Index82++) {
        std::string A_LoopField82 = items82[A_Index82 - 0];
        HTVM_Append(slidingWinFixCommentsRmFFFF, A_LoopField82);
    }
    for (int A_Index83 = 0; A_Index83 < StrLen(keyWordComment + keyWordComment) + 2 + 0; A_Index83++) {
        HTVM_Append(slidingWinFixCommentsRmFFFF, " ");
    }
    return slidingWinFixCommentsRmFFFF;
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
std::string compiler(std::string htCode, std::string allInstructionFile, std::string mode, std::string langToConvertToParam = "") {
    std::string instructions = allInstructionFile;
    std::vector<std::string> items84 = LoopParseFunc(allInstructionFile, "\n", "\r");
    for (size_t A_Index84 = 0; A_Index84 < items84.size() + 0; A_Index84++) {
        std::string A_LoopField84 = items84[A_Index84 - 0];
        if (A_Index84 == 0) {
            langToConvertTo = Trim(A_LoopField84);
        }
        if (A_Index84 == 1) {
            langFileExtension = Trim(A_LoopField84);
        }
        if (A_Index84 == 2) {
            commands = Trim(A_LoopField84);
        }
        if (A_Index84 == 3) {
            keyWordAlliance = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 4) {
            keyWordCrew = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 5) {
            keyWordMethod = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 6) {
            keyWordDefObj = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 7) {
            keyWordProp = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 8) {
            keyWordThis = Trim(A_LoopField84);
        }
        if (A_Index84 == 9) {
            keyWordInclude = Trim(A_LoopField84);
        }
        if (A_Index84 == 10) {
            keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField84);
        }
        if (A_Index84 == 11) {
            keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField84);
        }
        if (A_Index84 == 12) {
            keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField84);
        }
        if (A_Index84 == 13) {
            keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField84);
        }
        if (A_Index84 == 14) {
            keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField84);
        }
        if (A_Index84 == 15) {
            keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField84);
        }
        if (A_Index84 == 16) {
            keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField84);
        }
        if (A_Index84 == 17) {
            keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField84);
        }
        if (A_Index84 == 18) {
            keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField84);
        }
        if (A_Index84 == 19) {
            keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField84);
        }
        if (A_Index84 == 20) {
            keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField84);
        }
        if (A_Index84 == 21) {
            keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField84);
        }
        if (A_Index84 == 22) {
            keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField84);
        }
        if (A_Index84 == 23) {
            keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField84);
        }
        if (A_Index84 == 24) {
            keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField84);
        }
        if (A_Index84 == 25) {
            keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField84);
        }
        if (A_Index84 == 26) {
            keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField84);
        }
        if (A_Index84 == 27) {
            keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField84);
        }
        if (A_Index84 == 28) {
            keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField84);
        }
        if (A_Index84 == 29) {
            keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField84);
        }
        if (A_Index84 == 30) {
            keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField84);
        }
        if (A_Index84 == 31) {
            keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField84);
        }
        if (A_Index84 == 32) {
            keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField84);
        }
        if (A_Index84 == 33) {
            keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField84);
        }
        if (A_Index84 == 34) {
            keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField84);
        }
        if (A_Index84 == 35) {
            keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField84);
        }
        if (A_Index84 == 36) {
            keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField84);
        }
        if (A_Index84 == 37) {
            keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField84);
        }
        if (A_Index84 == 38) {
            keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField84);
        }
        if (A_Index84 == 39) {
            keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField84);
        }
        if (A_Index84 == 40) {
            keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField84);
        }
        if (A_Index84 == 41) {
            keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField84);
        }
        if (A_Index84 == 42) {
            keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField84);
        }
        if (A_Index84 == 43) {
            keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField84);
        }
        if (A_Index84 == 44) {
            keyWordCodeInHTVMstart = Trim(A_LoopField84);
        }
        if (A_Index84 == 45) {
            keyWordCodeInHTVMend = Trim(A_LoopField84);
        }
        if (A_Index84 == 46) {
            keyWordCurlyBraceOpen = Trim(A_LoopField84);
        }
        if (A_Index84 == 47) {
            keyWordCurlyBraceClose = Trim(A_LoopField84);
        }
        if (A_Index84 == 48) {
            keyWordNull = Trim(A_LoopField84);
        }
        if (A_Index84 == 49) {
            keyWordTrue = Trim(A_LoopField84);
        }
        if (A_Index84 == 50) {
            keyWordFalse = Trim(A_LoopField84);
        }
        if (A_Index84 == 51) {
            keyWordVoid = Trim(A_LoopField84);
        }
        if (A_Index84 == 52) {
            keyWordDouble = Trim(A_LoopField84);
        }
        if (A_Index84 == 53) {
            keyWordChar = Trim(A_LoopField84);
        }
        if (A_Index84 == 54) {
            keyWordUint8 = Trim(A_LoopField84);
        }
        if (A_Index84 == 55) {
            keyWordUint16 = Trim(A_LoopField84);
        }
        if (A_Index84 == 56) {
            keyWordUint32 = Trim(A_LoopField84);
        }
        if (A_Index84 == 57) {
            keyWordUint64 = Trim(A_LoopField84);
        }
        if (A_Index84 == 58) {
            keyWordINT = Trim(A_LoopField84);
        }
        if (A_Index84 == 59) {
            keyWordSTR = Trim(A_LoopField84);
        }
        if (A_Index84 == 60) {
            keyWordBOOL = Trim(A_LoopField84);
        }
        if (A_Index84 == 61) {
            keyWordFLOAT = Trim(A_LoopField84);
        }
        if (A_Index84 == 62) {
            keyWordINT8 = Trim(A_LoopField84);
        }
        if (A_Index84 == 63) {
            keyWordINT16 = Trim(A_LoopField84);
        }
        if (A_Index84 == 64) {
            keyWordINT32 = Trim(A_LoopField84);
        }
        if (A_Index84 == 65) {
            keyWordINT64 = Trim(A_LoopField84);
        }
        if (A_Index84 == 66) {
            keyWordIF = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 67) {
            keyWordElseIf = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 68) {
            keyWordElse = Trim(A_LoopField84);
        }
        if (A_Index84 == 69) {
            keyWordWhileLoop = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 70) {
            keyWordLoopInfinite = Trim(A_LoopField84);
        }
        if (A_Index84 == 71) {
            keyWordLoop = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 72) {
            keyWordLoopParse = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 73) {
            keyWordContinue = Trim(A_LoopField84);
        }
        if (A_Index84 == 74) {
            keyWordBreak = Trim(A_LoopField84);
        }
        if (A_Index84 == 75) {
            keyWordFunc = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 76) {
            keyWordAwait = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 77) {
            keyWordAsync = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 78) {
            keyWordThrow = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 79) {
            keyWordErrorMsg = Trim(A_LoopField84);
        }
        if (A_Index84 == 80) {
            keyWordTry = Trim(A_LoopField84);
        }
        if (A_Index84 == 81) {
            keyWordCatch = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 82) {
            keyWordFinally = Trim(A_LoopField84);
        }
        if (A_Index84 == 83) {
            keyWordReturnStatement = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 84) {
            keyWordArrayAppend = Trim(A_LoopField84);
        }
        if (A_Index84 == 85) {
            keyWordArrayPop = Trim(A_LoopField84);
        }
        if (A_Index84 == 86) {
            keyWordArraySize = Trim(A_LoopField84);
        }
        if (A_Index84 == 87) {
            keyWordArrayInsert = Trim(A_LoopField84);
        }
        if (A_Index84 == 88) {
            keyWordArrayRemove = Trim(A_LoopField84);
        }
        if (A_Index84 == 89) {
            keyWordArrayIndexOf = Trim(A_LoopField84);
        }
        if (A_Index84 == 90) {
            keyWordArrayDefinition = Trim(A_LoopField84);
        }
        if (A_Index84 == 91) {
            keyWordArrayOfIntegersDefinition = Trim(A_LoopField84);
        }
        if (A_Index84 == 92) {
            keyWordArrayOfStringsDefinition = Trim(A_LoopField84);
        }
        if (A_Index84 == 93) {
            keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField84);
        }
        if (A_Index84 == 94) {
            keyWordArrayOfBooleansDefinition = Trim(A_LoopField84);
        }
        if (A_Index84 == 95) {
            keyWordVar = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 96) {
            keyWordLet = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 97) {
            keyWordConst = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 98) {
            keyWordEnd = Trim(A_LoopField84);
        }
        if (A_Index84 == 99) {
            keyWordGlobal = Trim(A_LoopField84) + " ";
        }
        if (A_Index84 == 100) {
            keyWordComment = Trim(A_LoopField84);
        }
        if (A_Index84 == 101) {
            keyWordCommentOpenMultiLine = Trim(A_LoopField84);
        }
        if (A_Index84 == 102) {
            keyWordCommentCloseMultiLine = Trim(A_LoopField84);
        }
        if (A_Index84 == 103) {
            keyWordEscpaeChar = Trim(A_LoopField84);
        }
        if (A_Index84 == 104) {
            keyWordMainLabel = Trim(A_LoopField84);
        }
        if (A_Index84 == 105) {
            keyWordConcat = Trim(A_LoopField84);
        }
        if (A_Index84 == 106) {
            keyWordAdd = Trim(A_LoopField84);
        }
        if (A_Index84 == 107) {
            keyWordSub = Trim(A_LoopField84);
        }
        if (A_Index84 == 108) {
            keyWordMul = Trim(A_LoopField84);
        }
        if (A_Index84 == 109) {
            keyWordDiv = Trim(A_LoopField84);
        }
        if (A_Index84 == 110) {
            keyWordMod = Trim(A_LoopField84);
        }
        if (A_Index84 == 111) {
            keyWordExp = Trim(A_LoopField84);
        }
        if (A_Index84 == 112) {
            keyWordEqual = Trim(A_LoopField84);
        }
        if (A_Index84 == 113) {
            keyWordStrictEqual = Trim(A_LoopField84);
        }
        if (A_Index84 == 114) {
            keyWordNotEqual = Trim(A_LoopField84);
        }
        if (A_Index84 == 115) {
            keyWordGreater = Trim(A_LoopField84);
        }
        if (A_Index84 == 116) {
            keyWordLess = Trim(A_LoopField84);
        }
        if (A_Index84 == 117) {
            keyWordGreaterEqual = Trim(A_LoopField84);
        }
        if (A_Index84 == 118) {
            keyWordLessEqual = Trim(A_LoopField84);
        }
        if (A_Index84 == 119) {
            keyWordAnd = Trim(A_LoopField84);
        }
        if (A_Index84 == 120) {
            keyWordOr = Trim(A_LoopField84);
        }
        if (A_Index84 == 121) {
            keyWordNot = Trim(A_LoopField84);
        }
        if (A_Index84 == 122) {
            keyWordBitAnd = Trim(A_LoopField84);
        }
        if (A_Index84 == 123) {
            keyWordBitOr = Trim(A_LoopField84);
        }
        if (A_Index84 == 124) {
            keyWordBitXor = Trim(A_LoopField84);
        }
        if (A_Index84 == 125) {
            keyWordBitNot = Trim(A_LoopField84);
        }
        if (A_Index84 == 126) {
            keyWordShiftLeft = Trim(A_LoopField84);
        }
        if (A_Index84 == 127) {
            keyWordShiftRight = Trim(A_LoopField84);
        }
        if (A_Index84 == 128) {
            keyWordShiftUnsignedRight = Trim(A_LoopField84);
        }
        if (A_Index84 == 129) {
            keyWordAssign = Trim(A_LoopField84);
        }
        if (A_Index84 == 130) {
            keyWordAssignAdd = Trim(A_LoopField84);
        }
        if (A_Index84 == 131) {
            keyWordAssignConcat = Trim(A_LoopField84);
        }
        if (A_Index84 == 132) {
            keyWordAssignSub = Trim(A_LoopField84);
        }
        if (A_Index84 == 133) {
            keyWordAssignMul = Trim(A_LoopField84);
        }
        if (A_Index84 == 134) {
            keyWordAssignDiv = Trim(A_LoopField84);
        }
        if (A_Index84 == 135) {
            keyWordAssignMod = Trim(A_LoopField84);
        }
        if (A_Index84 == 136) {
            keyWordAssignShiftLeft = Trim(A_LoopField84);
        }
        if (A_Index84 == 137) {
            keyWordAssignShiftRight = Trim(A_LoopField84);
        }
        if (A_Index84 == 138) {
            keyWordLogicalAssignShiftRight = Trim(A_LoopField84);
        }
        if (A_Index84 == 139) {
            keyWordAssignBitAnd = Trim(A_LoopField84);
        }
        if (A_Index84 == 140) {
            keyWordAssignBitOr = Trim(A_LoopField84);
        }
        if (A_Index84 == 141) {
            keyWordAssignBitXor = Trim(A_LoopField84);
        }
        if (A_Index84 == 142) {
            keyWordTernary1 = Trim(A_LoopField84);
        }
        if (A_Index84 == 143) {
            keyWordTernary2 = Trim(A_LoopField84);
        }
        if (A_Index84 == 144) {
            keyWordInc = Trim(A_LoopField84);
        }
        if (A_Index84 == 145) {
            keyWordDec = Trim(A_LoopField84);
        }
        if (A_Index84 == 146) {
            AHKlikeLoopsIndexedAt = Trim(A_LoopField84);
        }
        if (A_Index84 == 147) {
            keyWordAIndex = Trim(A_LoopField84);
        }
        if (A_Index84 == 148) {
            keyWordALoopField = Trim(A_LoopField84);
        }
        if (A_Index84 == 149) {
            useCurlyBraces = Trim(A_LoopField84);
        }
        if (A_Index84 == 150) {
            useEnd = Trim(A_LoopField84);
        }
        if (A_Index84 == 151) {
            useSemicolon = Trim(A_LoopField84);
        }
        if (A_Index84 == 152) {
            useParentheses = Trim(A_LoopField84);
        }
        if (A_Index84 == 153) {
            usePrefixTypeForTypeDefinition = Trim(A_LoopField84);
        }
        if (A_Index84 == 154) {
            usePostfixTypeForTypeDefinition = Trim(A_LoopField84);
        }
        if (A_Index84 == 155) {
            usePythonicColonSyntax = Trim(A_LoopField84);
        }
        if (A_Index84 == 156) {
            useCurlyBracesSyntaxForArrayDef = Trim(A_LoopField84);
        }
        if (A_Index84 == 157) {
            useInJavaScriptAlwaysUseVar = Trim(A_LoopField84);
        }
        if (A_Index84 == 158) {
            useJavaScriptInAfullHTMLfile = Trim(A_LoopField84);
        }
        if (A_Index84 == 159) {
            useJavaScriptAmainFuncDef = Trim(A_LoopField84);
        }
        if (A_Index84 == 160) {
            useJavaScriptAllFuncsAreAsync = Trim(A_LoopField84);
        }
        if (A_Index84 == 161) {
            useJavaScriptAlwaysTripleEqual = Trim(A_LoopField84);
        }
    }
    if (HTVM_Size(argHTVMinstrMORE) > 0) {
        std::string allInstructionFile_2 = "";
        if (HTVM_getLang_HTVM() == "js") {
            allInstructionFile_2 = Trim(argHTVMinstrMORE[0]);
        } else {
            allInstructionFile_2 = Trim(FileRead(Trim(argHTVMinstrMORE[0])));
        }
        std::vector<std::string> items85 = LoopParseFunc(allInstructionFile_2, "\n", "\r");
        for (size_t A_Index85 = 0; A_Index85 < items85.size() + 0; A_Index85++) {
            std::string A_LoopField85 = items85[A_Index85 - 0];
            if (A_Index85 == 0) {
                langToConvertTo_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 1) {
                langFileExtension_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 2) {
                commands_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 3) {
                keyWordAlliance_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 4) {
                keyWordCrew_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 5) {
                keyWordMethod_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 6) {
                keyWordDefObj_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 7) {
                keyWordProp_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 8) {
                keyWordThis_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 9) {
                keyWordInclude_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 10) {
                keyWordCodeInTheTranspiledLangStart_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 11) {
                keyWordCodeInTheTranspiledLangEnd_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 12) {
                keyWordCodeInTheTranspiledLangStartCPP_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 13) {
                keyWordCodeInTheTranspiledLangEndCPP_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 14) {
                keyWordCodeInTheTranspiledLangStartPY_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 15) {
                keyWordCodeInTheTranspiledLangEndPY_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 16) {
                keyWordCodeInTheTranspiledLangStartJS_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 17) {
                keyWordCodeInTheTranspiledLangEndJS_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 18) {
                keyWordCodeInTheTranspiledLangStartGO_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 19) {
                keyWordCodeInTheTranspiledLangEndGO_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 20) {
                keyWordCodeInTheTranspiledLangStartLUA_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 21) {
                keyWordCodeInTheTranspiledLangEndLUA_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 22) {
                keyWordCodeInTheTranspiledLangStartCS_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 23) {
                keyWordCodeInTheTranspiledLangEndCS_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 24) {
                keyWordCodeInTheTranspiledLangStartJAVA_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 25) {
                keyWordCodeInTheTranspiledLangEndJAVA_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 26) {
                keyWordCodeInTheTranspiledLangStartKT_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 27) {
                keyWordCodeInTheTranspiledLangEndKT_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 28) {
                keyWordCodeInTheTranspiledLangStartRB_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 29) {
                keyWordCodeInTheTranspiledLangEndRB_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 30) {
                keyWordCodeInTheTranspiledLangStartNIM_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 31) {
                keyWordCodeInTheTranspiledLangEndNIM_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 32) {
                keyWordCodeInTheTranspiledLangStartAHK_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 33) {
                keyWordCodeInTheTranspiledLangEndAHK_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 34) {
                keyWordCodeInTheTranspiledLangStartSWIFT_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 35) {
                keyWordCodeInTheTranspiledLangEndSWIFT_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 36) {
                keyWordCodeInTheTranspiledLangStartDART_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 37) {
                keyWordCodeInTheTranspiledLangEndDART_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 38) {
                keyWordCodeInTheTranspiledLangStartTS_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 39) {
                keyWordCodeInTheTranspiledLangEndTS_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 40) {
                keyWordCodeInTheTranspiledLangStartGROOVY_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 41) {
                keyWordCodeInTheTranspiledLangEndGROOVY_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 42) {
                keyWordCodeInTheTranspiledLangStartHTVM_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 43) {
                keyWordCodeInTheTranspiledLangEndHTVM_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 44) {
                keyWordCodeInHTVMstart_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 45) {
                keyWordCodeInHTVMend_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 46) {
                keyWordCurlyBraceOpen_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 47) {
                keyWordCurlyBraceClose_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 48) {
                keyWordNull_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 49) {
                keyWordTrue_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 50) {
                keyWordFalse_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 51) {
                keyWordVoid_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 52) {
                keyWordDouble_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 53) {
                keyWordChar_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 54) {
                keyWordUint8_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 55) {
                keyWordUint16_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 56) {
                keyWordUint32_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 57) {
                keyWordUint64_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 58) {
                keyWordINT_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 59) {
                keyWordSTR_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 60) {
                keyWordBOOL_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 61) {
                keyWordFLOAT_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 62) {
                keyWordINT8_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 63) {
                keyWordINT16_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 64) {
                keyWordINT32_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 65) {
                keyWordINT64_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 66) {
                keyWordIF_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 67) {
                keyWordElseIf_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 68) {
                keyWordElse_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 69) {
                keyWordWhileLoop_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 70) {
                keyWordLoopInfinite_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 71) {
                keyWordLoop_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 72) {
                keyWordLoopParse_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 73) {
                keyWordContinue_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 74) {
                keyWordBreak_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 75) {
                keyWordFunc_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 76) {
                keyWordAwait_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 77) {
                keyWordAsync_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 78) {
                keyWordThrow_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 79) {
                keyWordErrorMsg_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 80) {
                keyWordTry_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 81) {
                keyWordCatch_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 82) {
                keyWordFinally_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 83) {
                keyWordReturnStatement_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 84) {
                keyWordArrayAppend_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 85) {
                keyWordArrayPop_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 86) {
                keyWordArraySize_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 87) {
                keyWordArrayInsert_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 88) {
                keyWordArrayRemove_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 89) {
                keyWordArrayIndexOf_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 90) {
                keyWordArrayDefinition_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 91) {
                keyWordArrayOfIntegersDefinition_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 92) {
                keyWordArrayOfStringsDefinition_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 93) {
                keyWordArrayOfFloatingPointNumbersDefinition_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 94) {
                keyWordArrayOfBooleansDefinition_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 95) {
                keyWordVar_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 96) {
                keyWordLet_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 97) {
                keyWordConst_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 98) {
                keyWordEnd_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 99) {
                keyWordGlobal_2 = Trim(A_LoopField85) + " ";
            }
            if (A_Index85 == 100) {
                keyWordComment_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 101) {
                keyWordCommentOpenMultiLine_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 102) {
                keyWordCommentCloseMultiLine_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 103) {
                keyWordEscpaeChar_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 104) {
                keyWordMainLabel_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 105) {
                keyWordConcat_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 106) {
                keyWordAdd_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 107) {
                keyWordSub_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 108) {
                keyWordMul_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 109) {
                keyWordDiv_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 110) {
                keyWordMod_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 111) {
                keyWordExp_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 112) {
                keyWordEqual_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 113) {
                keyWordStrictEqual_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 114) {
                keyWordNotEqual_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 115) {
                keyWordGreater_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 116) {
                keyWordLess_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 117) {
                keyWordGreaterEqual_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 118) {
                keyWordLessEqual_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 119) {
                keyWordAnd_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 120) {
                keyWordOr_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 121) {
                keyWordNot_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 122) {
                keyWordBitAnd_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 123) {
                keyWordBitOr_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 124) {
                keyWordBitXor_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 125) {
                keyWordBitNot_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 126) {
                keyWordShiftLeft_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 127) {
                keyWordShiftRight_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 128) {
                keyWordShiftUnsignedRight_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 129) {
                keyWordAssign_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 130) {
                keyWordAssignAdd_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 131) {
                keyWordAssignConcat_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 132) {
                keyWordAssignSub_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 133) {
                keyWordAssignMul_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 134) {
                keyWordAssignDiv_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 135) {
                keyWordAssignMod_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 136) {
                keyWordAssignShiftLeft_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 137) {
                keyWordAssignShiftRight_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 138) {
                keyWordLogicalAssignShiftRight_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 139) {
                keyWordAssignBitAnd_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 140) {
                keyWordAssignBitOr_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 141) {
                keyWordAssignBitXor_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 142) {
                keyWordTernary1_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 143) {
                keyWordTernary2_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 144) {
                keyWordInc_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 145) {
                keyWordDec_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 146) {
                AHKlikeLoopsIndexedAt_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 147) {
                keyWordAIndex_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 148) {
                keyWordALoopField_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 149) {
                useCurlyBraces_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 150) {
                useEnd_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 151) {
                useSemicolon_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 152) {
                useParentheses_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 153) {
                usePrefixTypeForTypeDefinition_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 154) {
                usePostfixTypeForTypeDefinition_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 155) {
                usePythonicColonSyntax_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 156) {
                useCurlyBracesSyntaxForArrayDef_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 157) {
                useInJavaScriptAlwaysUseVar_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 158) {
                useJavaScriptInAfullHTMLfile_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 159) {
                useJavaScriptAmainFuncDef_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 160) {
                useJavaScriptAllFuncsAreAsync_2 = Trim(A_LoopField85);
            }
            if (A_Index85 == 161) {
                useJavaScriptAlwaysTripleEqual_2 = Trim(A_LoopField85);
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
    std::vector<std::string> items86 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index86 = 0; A_Index86 < items86.size() + 0; A_Index86++) {
        std::string A_LoopField86 = items86[A_Index86 - 0];
        if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEnd)) {
            COUNT_programmingBlock_InTheTranspiledLang++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(COUNT_programmingBlock_InTheTranspiledLang) + "AA\n";
            HTVM_Append(programmingBlock_InTheTranspiledLang, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndCPP)) {
            COUNT_programmingBlock_CPP++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(COUNT_programmingBlock_CPP) + "AA\n";
            HTVM_Append(programmingBlock_CPP, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndPY)) {
            COUNT_programmingBlock_PY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_PY-programmingBlock_PY-AA" + STR(COUNT_programmingBlock_PY) + "AA\n";
            HTVM_Append(programmingBlock_PY, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndJS)) {
            COUNT_programmingBlock_JS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JS-programmingBlock_JS-AA" + STR(COUNT_programmingBlock_JS) + "AA\n";
            HTVM_Append(programmingBlock_JS, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndGO)) {
            COUNT_programmingBlock_GO++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GO-programmingBlock_GO-AA" + STR(COUNT_programmingBlock_GO) + "AA\n";
            HTVM_Append(programmingBlock_GO, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndLUA)) {
            COUNT_programmingBlock_LUA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(COUNT_programmingBlock_LUA) + "AA\n";
            HTVM_Append(programmingBlock_LUA, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndCS)) {
            COUNT_programmingBlock_CS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CS-programmingBlock_CS-AA" + STR(COUNT_programmingBlock_CS) + "AA\n";
            HTVM_Append(programmingBlock_CS, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndJAVA)) {
            COUNT_programmingBlock_JAVA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(COUNT_programmingBlock_JAVA) + "AA\n";
            HTVM_Append(programmingBlock_JAVA, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndKT)) {
            COUNT_programmingBlock_KT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_KT-programmingBlock_KT-AA" + STR(COUNT_programmingBlock_KT) + "AA\n";
            HTVM_Append(programmingBlock_KT, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndRB)) {
            COUNT_programmingBlock_RB++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_RB-programmingBlock_RB-AA" + STR(COUNT_programmingBlock_RB) + "AA\n";
            HTVM_Append(programmingBlock_RB, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndNIM)) {
            COUNT_programmingBlock_NIM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(COUNT_programmingBlock_NIM) + "AA\n";
            HTVM_Append(programmingBlock_NIM, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndAHK)) {
            COUNT_programmingBlock_AHK++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(COUNT_programmingBlock_AHK) + "AA\n";
            HTVM_Append(programmingBlock_AHK, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndSWIFT)) {
            COUNT_programmingBlock_SWIFT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(COUNT_programmingBlock_SWIFT) + "AA\n";
            HTVM_Append(programmingBlock_SWIFT, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndDART)) {
            COUNT_programmingBlock_DART++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_DART-programmingBlock_DART-AA" + STR(COUNT_programmingBlock_DART) + "AA\n";
            HTVM_Append(programmingBlock_DART, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndTS)) {
            COUNT_programmingBlock_TS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_TS-programmingBlock_TS-AA" + STR(COUNT_programmingBlock_TS) + "AA\n";
            HTVM_Append(programmingBlock_TS, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndGROOVY)) {
            COUNT_programmingBlock_GROOVY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(COUNT_programmingBlock_GROOVY) + "AA\n";
            HTVM_Append(programmingBlock_GROOVY, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangEndHTVM)) {
            COUNT_programmingBlock_HTVM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(COUNT_programmingBlock_HTVM) + "AA\n";
            HTVM_Append(programmingBlock_HTVM, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInHTVMend)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            COUNT_programmingBlock_HTVMsyntax++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(COUNT_programmingBlock_HTVMsyntax) + "AA\n";
            HTVM_Append(programmingBlock_HTVMsyntax, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        }
        else if (inProgarmmingBlock == 1) {
            holdTempDataProgrammingBlockThenPutInArr += A_LoopField86 + Chr(10);
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStart)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartCPP)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartPY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartJS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartGO)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartLUA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartCS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartJAVA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartKT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartRB)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartNIM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartAHK)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartSWIFT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartDART)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartTS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartGROOVY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInTheTranspiledLangStartHTVM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField86)) == StrLower(keyWordCodeInHTVMstart)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        } else {
            programmingBlocksTemp += A_LoopField86 + Chr(10);
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
    std::string allLibCODE = "";
    std::string allLibCODEfix = "";
    std::vector<std::string> allLibsWeSee;
    std::vector<std::string> allLibsWeSeeSEE;
    std::string allLibsWeSeeHOLD = "";
    int doseCodeHaveLibs = 0;
    int doseCodeHaveLibs_HAS_SEEN = 0;
    int doseCodeHaveLibs_HAS_SEEN2 = 0;
    if (isNotHTVMfile == 0) {
        if (langToConvertTo != langFileExtension_2) {
            if (InStr(StrLower(code), StrLower(keyWordInclude + " "))) {
                for (int A_Index87 = 0; A_Index87 < 10000 + 0; A_Index87++) {
                    doseCodeHaveLibs = 0;
                    allLibCODE = "";
                    if (A_Index87 == 0) {
                        std::vector<std::string> items88 = LoopParseFunc(code, "\n", "\r");
                        for (size_t A_Index88 = 0; A_Index88 < items88.size() + 0; A_Index88++) {
                            std::string A_LoopField88 = items88[A_Index88 - 0];
                            if (SubStr(StrLower(Trim(A_LoopField88)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ")) {
                                HTVM_Append(allLibsWeSee, StrReplace(StringTrimLeft(Trim(A_LoopField88), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                HTVM_Append(allLibsWeSeeSEE, StrReplace(StringTrimLeft(Trim(A_LoopField88), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                doseCodeHaveLibs = 1;
                            }
                        }
                    } else {
                        std::vector<std::string> items89 = LoopParseFunc(code, "\n", "\r");
                        for (size_t A_Index89 = 0; A_Index89 < items89.size() + 0; A_Index89++) {
                            std::string A_LoopField89 = items89[A_Index89 - 0];
                            ALoopField = A_LoopField89;
                            if (SubStr(StrLower(Trim(A_LoopField89)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ")) {
                                doseCodeHaveLibs_HAS_SEEN = 0;
                                for (int A_Index90 = 0; A_Index90 < HTVM_Size(allLibsWeSee) + 0; A_Index90++) {
                                    if (StrReplace(StringTrimLeft(Trim(ALoopField), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), "") == allLibsWeSee[A_Index90]) {
                                        doseCodeHaveLibs_HAS_SEEN = 1;
                                    }
                                }
                                if (doseCodeHaveLibs_HAS_SEEN == 0) {
                                    HTVM_Append(allLibsWeSee, StrReplace(StringTrimLeft(Trim(A_LoopField89), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                    HTVM_Append(allLibsWeSeeSEE, StrReplace(StringTrimLeft(Trim(A_LoopField89), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                    doseCodeHaveLibs = 1;
                                }
                            }
                        }
                    }
                    for (int A_Index91 = 0; A_Index91 < HTVM_Size(allLibsWeSee) + 0; A_Index91++) {
                        allLibsWeSeeHOLD = allLibsWeSee[A_Index91];
                        doseCodeHaveLibs_HAS_SEEN2 = 0;
                        for (int A_Index92 = 0; A_Index92 < HTVM_Size(allLibsWeSeeSEE) - HTVM_Size(allLibsWeSee) + 0; A_Index92++) {
                            if (allLibsWeSeeHOLD == allLibsWeSeeSEE[A_Index92]) {
                                doseCodeHaveLibs_HAS_SEEN2 = 1;
                            }
                        }
                        if (doseCodeHaveLibs_HAS_SEEN2 == 0) {
                            allLibCODE += FileRead(Trim(allLibsWeSee[HTVM_Size(allLibsWeSee) - A_Index91 - 1])) + Chr(10);
                        }
                        HTVM_Pop(allLibsWeSee);
                    }
                    allLibCODEfix = "";
                    std::vector<std::string> items93 = LoopParseFunc(code, "\n", "\r");
                    for (size_t A_Index93 = 0; A_Index93 < items93.size() + 0; A_Index93++) {
                        std::string A_LoopField93 = items93[A_Index93 - 0];
                        if (SubStr(StrLower(Trim(A_LoopField93)), 1, StrLen(StrLower(keyWordInclude + " "))) != StrLower(keyWordInclude + " ")) {
                            allLibCODEfix += A_LoopField93 + Chr(10);
                        }
                    }
                    code = StringTrimRight(allLibCODEfix, 1);
                    code = allLibCODE + code;
                    if (doseCodeHaveLibs == 0) {
                        break;
                    }
                }
            }
        }
        ALoopField = "";
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
    std::string ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = "";
    std::vector<std::string> getAllCharForTheFurtureSoIcanAddEscapeChar;
    int removeNexFixkeyWordEscpaeChar = 0;
    if (isNotHTVMfile == 0) {
        //print("============programmingBlock_CPP==================")
        //print("============programmingBlock_CPP==================")
        //print("============programmingBlock_CPP==================")
        //print("============programmingBlock_CPP==================")
        std::vector<std::string> items94 = LoopParseFunc(code);
        for (size_t A_Index94 = 0; A_Index94 < items94.size() + 0; A_Index94++) {
            std::string A_LoopField94 = items94[A_Index94 - 0];
            HTVM_Append(theIdNumOfThe34theVar, "");
            HTVM_Append(theIdNumOfThe34theVar, "");
        }
        std::vector<std::string> items95 = LoopParseFunc(code);
        for (size_t A_Index95 = 0; A_Index95 < items95.size() + 0; A_Index95++) {
            std::string A_LoopField95 = items95[A_Index95 - 0];
            theIdNumOfThe34theVar[A_Index95] = theIdNumOfThe34theVar[A_Index95] + Chr(34);
            HTVM_Append(getAllCharForTheFurtureSoIcanAddEscapeChar, A_LoopField95);
        }
        HTVM_Append(getAllCharForTheFurtureSoIcanAddEscapeChar, " ");
        ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuuhuuhtheidFor" + str21 + "--" + str21 + "asds" + str21 + "as--" + str21 + "theuhtuwaesphoutr" + Chr(34);
        std::vector<std::string> items96 = LoopParseFunc(code);
        for (size_t A_Index96 = 0; A_Index96 < items96.size() + 0; A_Index96++) {
            std::string A_LoopField96 = items96[A_Index96 - 0];
            if (A_LoopField96 == keyWordEscpaeChar && getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index96 + 1] == Chr(34)) {
                fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1;
                OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes;
            } else {
                if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1) {
                    OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField96;
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
            std::vector<std::string> items97 = LoopParseFunc(code);
            for (size_t A_Index97 = 0; A_Index97 < items97.size() + 0; A_Index97++) {
                std::string A_LoopField97 = items97[A_Index97 - 0];
                if (A_LoopField97 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField97 != Chr(34)) {
                        if (A_LoopField97 == keyWordEscpaeChar && langToConvertTo != langFileExtension_2) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField97;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField97 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField97;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        } else {
            std::vector<std::string> items98 = LoopParseFunc(code);
            for (size_t A_Index98 = 0; A_Index98 < items98.size() + 0; A_Index98++) {
                std::string A_LoopField98 = items98[A_Index98 - 0];
                if (A_LoopField98 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField98 != Chr(34)) {
                        if (A_LoopField98 == keyWordEscpaeChar && keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index98 + 1] && langToConvertTo != langFileExtension_2) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar;
                            removeNexFixkeyWordEscpaeChar = 1;
                        }
                        else if (A_LoopField98 == keyWordEscpaeChar && langToConvertTo != langFileExtension_2) {
                            if (removeNexFixkeyWordEscpaeChar != 1) {
                                theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                            } else {
                                removeNexFixkeyWordEscpaeChar = 0;
                            }
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField98;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField98 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField98;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        }
        code = htCodeOUT754754;
        for (int A_Index99 = 0; A_Index99 < theIdNumOfThe34 + 0; A_Index99++) {
            theIdNumOfThe34theVar[A_Index99] = theIdNumOfThe34theVar[A_Index99] + Chr(34);
        }
        HTVM_Append(theIdNumOfThe34theVar, Chr(34));
        code = StrReplace(code, Chr(13), "");
        slidingWinFixCommentsRmI = 0;
        newStringOutCode = "";
        std::vector<std::string> items100 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index100 = 0; A_Index100 < items100.size() + 0; A_Index100++) {
            std::string A_LoopField100 = items100[A_Index100 - 0];
            if (InStr(A_LoopField100, " " + keyWordComment) != false && SubStr(Trim(A_LoopField100), 1, StrLen(keyWordComment)) != keyWordComment) {
                posForRemoveCommentsOnTheEndOfTheLine = 0;
                slidingWinFixCommentsRmI = 0;
                slidingWinFixCommentsRm = slidingWinFixCommentsRmFUNC(A_LoopField100);
                for (int A_Index101 = 0; A_Index101 < HTVM_Size(slidingWinFixCommentsRm) + 0; A_Index101++) {
                    slidingWinFixCommentsRmI = A_Index101;
                    slidingWinFixCommentsRmHold = "";
                    for (int A_Index102 = 0; A_Index102 < StrLen(" " + keyWordComment) + 0; A_Index102++) {
                        slidingWinFixCommentsRmHold += slidingWinFixCommentsRm[slidingWinFixCommentsRmI + A_Index102];
                    }
                    if (Trim(slidingWinFixCommentsRmHold) == keyWordComment) {
                        posForRemoveCommentsOnTheEndOfTheLine = A_Index101;
                        break;
                    }
                }
                if (posForRemoveCommentsOnTheEndOfTheLine > 0) {
                    newStringOutCode += SubStr(A_LoopField100, 1, posForRemoveCommentsOnTheEndOfTheLine) + Chr(10);
                } else {
                    newStringOutCode += A_LoopField100 + Chr(10);
                }
            } else {
                newStringOutCode += A_LoopField100 + Chr(10);
            }
        }
        // Trim the last character (line break) from the final string
        code = StringTrimRight(newStringOutCode, 1);
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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
        if (useCurlyBraces == "on") {
            if (keyWordCurlyBraceOpen != "{") {
                std::vector<std::string> items103 = LoopParseFunc(code, "\n", "\r");
                for (size_t A_Index103 = 0; A_Index103 < items103.size() + 0; A_Index103++) {
                    std::string A_LoopField103 = items103[A_Index103 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField103)) == true || Trim(A_LoopField103) == keyWordCurlyBraceOpen) {
                        htCodeOutFixINT2 = 1;
                    }
                    htCodeOutFixINT = 0;
                    std::vector<std::string> items104 = LoopParseFunc(A_LoopField103, " ");
                    for (size_t A_Index104 = 0; A_Index104 < items104.size() + 0; A_Index104++) {
                        std::string A_LoopField104 = items104[A_Index104 - 0];
                        htCodeOutFixINT++;
                    }
                    htCodeOutFixINT--;
                    std::vector<std::string> items105 = LoopParseFunc(A_LoopField103, " ");
                    for (size_t A_Index105 = 0; A_Index105 < items105.size() + 0; A_Index105++) {
                        std::string A_LoopField105 = items105[A_Index105 - 0];
                        if (htCodeOutFixINT == A_Index105 && htCodeOutFixINT2 == 1) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField105, keyWordCurlyBraceOpen, "{") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField105 + " ";
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
                std::vector<std::string> items106 = LoopParseFunc(code, "\n", "\r");
                for (size_t A_Index106 = 0; A_Index106 < items106.size() + 0; A_Index106++) {
                    std::string A_LoopField106 = items106[A_Index106 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField106)) == true || Trim(A_LoopField106) == keyWordCurlyBraceClose) {
                        htCodeOutFixINT2 = 1;
                    }
                    std::vector<std::string> items107 = LoopParseFunc(A_LoopField106, " ");
                    for (size_t A_Index107 = 0; A_Index107 < items107.size() + 0; A_Index107++) {
                        std::string A_LoopField107 = items107[A_Index107 - 0];
                        if (htCodeOutFixINT2 == 1 || Trim(A_LoopField107) == keyWordCurlyBraceClose) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField107, keyWordCurlyBraceClose, "}") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField107 + " ";
                        }
                    }
                    htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1);
                    htCodeOutFixEnd += Chr(10);
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        htCodeOutFixEnd = "";
        if (useEnd == "on") {
            std::vector<std::string> items108 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index108 = 0; A_Index108 < items108.size() + 0; A_Index108++) {
                std::string A_LoopField108 = items108[A_Index108 - 0];
                if (StrLower(Trim(A_LoopField108)) == StrLower(keyWordEnd)) {
                    htCodeOutFixEnd += "}\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField108)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF) && isLineAconstruct(Trim(A_LoopField108)) == true) {
                    htCodeOutFixEnd += A_LoopField108 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField108)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop) && isLineAconstruct(Trim(A_LoopField108)) == true) {
                    htCodeOutFixEnd += A_LoopField108 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField108)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf) && isLineAconstruct(Trim(A_LoopField108)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField108 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField108)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse) && isLineAconstruct(Trim(A_LoopField108)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField108 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField108)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch) && isLineAconstruct(Trim(A_LoopField108)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField108 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField108)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally) && isLineAconstruct(Trim(A_LoopField108)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField108 + "\n{\n";
                }
                else if (isLineAconstruct(Trim(A_LoopField108)) == true) {
                    htCodeOutFixEnd += A_LoopField108 + "\n{\n";
                } else {
                    htCodeOutFixEnd += A_LoopField108 + Chr(10);
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        if (usePythonicColonSyntax == "off") {
            if (useEnd == "off" && useCurlyBraces == "off") {
                htCodeOutFixEnd = "";
                std::vector<std::string> items109 = LoopParseFunc(code, "\n", "\r");
                for (size_t A_Index109 = 0; A_Index109 < items109.size() + 0; A_Index109++) {
                    std::string A_LoopField109 = items109[A_Index109 - 0];
                    if (isLineAconstruct(Trim(A_LoopField109)) == true) {
                        htCodeOutFixEnd += A_LoopField109 + ":\n";
                    } else {
                        htCodeOutFixEnd += A_LoopField109 + Chr(10);
                    }
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
        }
        if (useCurlyBraces == "off" && useEnd == "off") {
            code = AddCurlyBraces(code);
        }
        outTrimCode = "";
        std::vector<std::string> items110 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index110 = 0; A_Index110 < items110.size() + 0; A_Index110++) {
            std::string A_LoopField110 = items110[A_Index110 - 0];
            outTrimCode += Trim(A_LoopField110) + Chr(10);
        }
        code = StringTrimRight(outTrimCode, 1);
        // for converting c++ to js and py
        //code := StrReplace(code, "{}", "[]")
        std::string outCodeFixBraces = "";
        for (int A_Index111 = 0; A_Index111 < 2 + 0; A_Index111++) {
            outCodeFixBraces = "";
            std::vector<std::string> items112 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index112 = 0; A_Index112 < items112.size() + 0; A_Index112++) {
                std::string A_LoopField112 = items112[A_Index112 - 0];
                if (InStr(A_LoopField112, " " + keyWordAssign + " ") || InStr(A_LoopField112, " " + keyWordAssignAdd + " ") || InStr(A_LoopField112, " " + keyWordAssignConcat + " ") || InStr(A_LoopField112, " " + keyWordAssignSub + " ") || InStr(A_LoopField112, " " + keyWordAssignMul + " ") || InStr(A_LoopField112, " " + keyWordAssignDiv + " ") || InStr(A_LoopField112, " " + keyWordAssignMod + " ") || InStr(A_LoopField112, " " + keyWordAssignShiftLeft + " ") || InStr(A_LoopField112, " " + keyWordAssignShiftRight + " ") || InStr(A_LoopField112, " " + keyWordLogicalAssignShiftRight + " ") || InStr(A_LoopField112, " " + keyWordAssignBitAnd + " ") || InStr(A_LoopField112, " " + keyWordAssignBitOr + " ") || InStr(A_LoopField112, " " + keyWordAssignBitXor + " ") && useCurlyBracesSyntaxForArrayDef == "on") {
                    if (SubStr(StrLower(A_LoopField112), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc) || SubStr(StrLower(A_LoopField112), 1, StrLen(StrLower(keyWordAsync) + StrLower(keyWordFunc))) == StrLower(keyWordAsync) + StrLower(keyWordFunc)) {
                        if (InStr(Trim(A_LoopField112), "{") && Trim(A_LoopField112) != "{") {
                            outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField112), "{", "")) + "\n{\n";
                        }
                        else if (InStr(Trim(A_LoopField112), "}") && Trim(A_LoopField112) != "}") {
                            outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField112), "}", "")) + Chr(10);
                        } else {
                            outCodeFixBraces += Trim(A_LoopField112) + Chr(10);
                        }
                    } else {
                        outCodeFixBraces += Trim(A_LoopField112) + Chr(10);
                    }
                } else {
                    if (InStr(Trim(A_LoopField112), "{") && Trim(A_LoopField112) != "{") {
                        outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField112), "{", "")) + "\n{\n";
                    }
                    else if (InStr(Trim(A_LoopField112), "}") && Trim(A_LoopField112) != "}") {
                        outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField112), "}", "")) + Chr(10);
                    } else {
                        outCodeFixBraces += Trim(A_LoopField112) + Chr(10);
                    }
                }
            }
            code = StringTrimRight(outCodeFixBraces, 1);
        }
        htCodeOutFixEnd = "";
        if (usePythonicColonSyntax == "on" || useCurlyBraces == "off" && useEnd == "off") {
            std::vector<std::string> items113 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index113 = 0; A_Index113 < items113.size() + 0; A_Index113++) {
                std::string A_LoopField113 = items113[A_Index113 - 0];
                if (isLineAconstruct(Trim(A_LoopField113)) == true) {
                    htCodeOutFixEnd += StringTrimRight(A_LoopField113, 1) + Chr(10);
                } else {
                    htCodeOutFixEnd += A_LoopField113 + Chr(10);
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        //;
        //;
        //;
        //;
        fullLangAllOperators = GETfullLangAllOperators();
        fullLangAllOperators_HELP = GETfullLangAllOperators_HELP();
        if (isNotHTVMfile2 == 0) {
            std::vector<std::string> items114 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index114 = 0; A_Index114 < items114.size() + 0; A_Index114++) {
                std::string A_LoopField114 = items114[A_Index114 - 0];
                if (StrLower(Trim(A_LoopField114)) == StrLower(keyWordMainLabel)) {
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
                        codeOutFixAndAddMainFunc += "func main()\n{\n";
                    }
                    if (langToConvertTo == "dart") {
                        codeOutFixAndAddMainFunc += "void main(List<String> arguments)" + Chr(10) + "{" + Chr(10);
                    }
                } else {
                    codeOutFixAndAddMainFunc += A_LoopField114 + Chr(10);
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
        std::vector<std::string> items115 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index115 = 0; A_Index115 < items115.size() + 0; A_Index115++) {
            std::string A_LoopField115 = items115[A_Index115 - 0];
            HTVM_Append(lookIntoTheNextLineForFuncWhitNoKeyWord, A_LoopField115);
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
        std::vector<std::string> items116 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index116 = 0; A_Index116 < items116.size() + 0; A_Index116++) {
            std::string A_LoopField116 = items116[A_Index116 - 0];
            lineDone = 0;
            if (SubStr(A_LoopField116, 1, StrLen(keyWordComment)) == keyWordComment) {
                lineDone = 1;
                str1 = StringTrimLeft(A_LoopField116, StrLen(keyWordComment));
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
            else if (Trim(A_LoopField116) == keyWordCommentOpenMultiLine) {
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
            else if (Trim(A_LoopField116) == keyWordCommentCloseMultiLine) {
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
            else if (InStr(A_LoopField116, "[][][][][] ")) {
                lineDone = 1;
                str1 = StrSplit(A_LoopField116, " ", 2);
                HTVM_Append(ospDic1, str1);
                strOspHold = StrReplace(str1, "_", ".");
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordDefObj_2 + StrReplace(str1, "_", ".") + Chr(10) + "{" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField116)), 1, StrLen(StrLower(keyWordDefObj))) == StrLower(keyWordDefObj)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField116, StrLen(keyWordDefObj)));
                if (langToConvertTo == langFileExtension_2) {
                    htCode += Trim(keyWordDefObj_2) + " " + str0 + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField116)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField116, StrLen(keyWordAlliance)));
                if (langToConvertTo == langFileExtension_2) {
                    htCode += Trim(keyWordAlliance_2) + " " + str0 + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField116)), 1, StrLen(StrLower(keyWordCrew))) == StrLower(keyWordCrew)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField116, StrLen(keyWordCrew)));
                if (langToConvertTo == langFileExtension_2) {
                    htCode += Trim(keyWordCrew_2) + " " + str0 + Chr(10);
                }
            }
            else if (InStr(A_LoopField116, "[end][end][end][end][end] ")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += "}" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField116)), 1, StrLen(StrLower(keyWordProp))) == StrLower(keyWordProp)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField116, StrLen(keyWordProp)));
                str1 = Trim(StrSplit(str0, "-----------------------HTVM-OSP-HTVM-OBJ--------------", 1));
                str20 = Trim(StrSplit(str0, "-----------------------HTVM-OSP-HTVM-OBJ--------------", 2));
                if (str20 == "" && langToConvertTo != langFileExtension_2) {
                    continue;
                }
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordProp_2 + propHELP(str1, "no-no") + Chr(10);
                } else {
                    if (langToConvertTo == "rb") {
                        htCode += propHELP(str1, "$" + Trim(StrReplace(str20, ".", "_") + "_")) + Chr(10);
                    } else {
                        htCode += propHELP(str1, StrReplace(str20, ".", "_") + "_") + Chr(10);
                    }
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField116)), 1, StrLen(StrLower(keyWordMethod))) == StrLower(keyWordMethod)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField116, StrLen(keyWordMethod)));
                str1 = Trim(StrSplit(str0, "-----------------------HTVM-OSP-HTVM-OBJ--------------", 1));
                str20 = Trim(StrSplit(str0, "-----------------------HTVM-OSP-HTVM-OBJ--------------", 2));
                str16 = Trim(StrSplit(str1, "(", 1));
                str18 = Trim(StrSplit(str1, ")", 2));
                int1 = 0;
                str17 = "";
                std::vector<std::string> items117 = LoopParseFunc(str16, " ");
                for (size_t A_Index117 = 0; A_Index117 < items117.size() + 0; A_Index117++) {
                    std::string A_LoopField117 = items117[A_Index117 - 0];
                    str17 = Trim(A_LoopField117);
                }
                // last word aka the method name
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
                            htCode += keyWordAsync_2 + keyWordMethod_2 + getFuncTypeConvert(str3) + " " + str2 + "(" + keyWordThis_2 + ")" + Chr(10);
                        } else {
                            htCode += keyWordAsync_2 + keyWordMethod_2 + str2 + "(" + keyWordThis_2 + "): " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    } else {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            htCode += keyWordMethod_2 + getFuncTypeConvert(str3) + " " + str2 + "(" + keyWordThis_2 + ")" + Chr(10);
                        } else {
                            htCode += keyWordMethod_2 + str2 + "(" + keyWordThis_2 + "): " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                }
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
                        htCode += "function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                    }
                }
                // Go
                if (langToConvertTo == "go") {
                    skipLeftCuleyForFuncPLS = 1;
                    if (str3 == keyWordVoid) {
                        htCode += "func " + str15 + "(__HTVM_V2_TO_GO_optionalParams__ ...interface{})" + Chr(10) + "{" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword := " + Chr(34) + Chr(34) + Chr(10) + "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " 0 " + Chr(10) + "{" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword = __HTVM_V2_TO_GO_optionalParams__[0].(string)" + Chr(10) + "}" + Chr(10);
                    } else {
                        htCode += "func " + str15 + "(__HTVM_V2_TO_GO_optionalParams__ ...interface{}) " + getFuncTypeConvert(str3) + Chr(10) + "{" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword := " + Chr(34) + Chr(34) + Chr(10) + "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " 0 {" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword = __HTVM_V2_TO_GO_optionalParams__[0].(string)" + Chr(10) + "}" + Chr(10);
                    }
                }
                if (langToConvertTo == "lua") {
                    skipLeftCuleyForFuncPLS = 1;
                    htCode += "function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword) {" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword = osp_osp_this_keyword_htvm_osp_this_htvm_keyword or " + Chr(34) + Chr(34) + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "static " + getFuncTypeConvert(str3) + " " + str15 + "(string osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    skipLeftCuleyForFuncPLS = 1;
                    htCode += "public static " + getFuncTypeConvert(str3) + " " + str15 + "(Object... __HTVM_V2_TO_JAVA_optionalParams__)" + Chr(10) + "{" + Chr(10) + "String osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ";" + Chr(10);
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
                    htCode += "function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword: string = " + Chr(34) + Chr(34) + "): " + getFuncTypeConvert(str3) + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "def " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField116)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF) && SubStr(StrLower(Trim(A_LoopField116)), 1, StrLen(StrLower(keyWordElseIf))) != StrLower(keyWordElseIf)) {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(A_LoopField116, StrLen(keyWordIF)));
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
            else if (SubStr(StrLower(Trim(A_LoopField116)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf) && SubStr(StrLower(Trim(A_LoopField116)), 1, StrLen(StrLower(keyWordIF))) != StrLower(keyWordIF)) {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(A_LoopField116, StrLen(keyWordElseIf)));
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"));
                str1 = StringTrimRight(str1, 1);
                str1 = StringTrimLeft(str1, 1);
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + str1 + ":\n";
                            } else {
                                htCode += keyWordElseIf_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":\n";
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + "(" + str1 + "):\n";
                            } else {
                                htCode += keyWordElseIf_2 + str1 + ":\n";
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
                                htCode += keyWordElseIf_2 + "(" + str1 + ")\n";
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
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "py") {
                    htCode += "elif " + str1 + ":\n";
                }
                if (langToConvertTo == "js") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "go") {
                    htCode += "else if " + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "elseif " + str1 + " then\n";
                }
                if (langToConvertTo == "cs") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "java") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "kt") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "elsif " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "elif " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "else if " + str1 + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "else if (" + str1 + ")" + Chr(10);
                }
            }
            else if (StrLower(Trim(A_LoopField116)) == StrLower(keyWordElse) || StrLower(Trim(A_LoopField116)) == StrLower(keyWordElse + ":")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordElse_2 + ":\n";
                    } else {
                        htCode += keyWordElse_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "else:\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "else:\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "else\n";
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField116)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)) {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(A_LoopField116, StrLen(keyWordWhileLoop)));
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
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "while " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "while " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "while " + str1 + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "while (" + str1 + ")" +  Chr(10);
                }
            }
            else if (StrLower(Trim(A_LoopField116)) == StrLower(keyWordTry) || StrLower(Trim(A_LoopField116)) == StrLower(keyWordTry + ":")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordTry_2 + ":\n";
                    } else {
                        htCode += keyWordTry_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "try:\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "begin\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "try:\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "do\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "try\n";
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField116)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)) {
                lineDone = 1;
                str1 = Trim(StrReplace(StrReplace(StringTrimLeft(A_LoopField116, StrLen(keyWordCatch)), "(", ""), ")", ""));
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
                    htCode += "catch (const std::exception& " + str1 + ")\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "except Exception as " + str1 + ":\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "catch (" + str1 + ")\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "catch (Exception " + str1 + ")\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "catch (Exception " + str1 + ")\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "catch (" + str1 + ": Exception)\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "rescue => " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "except ValueError as " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "catch " + str1 + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "catch let " + str1 + " as NSError\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "catch (" + str1 + ")\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "catch (" + str1 + ")\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "catch (Exception " + str1 + ")\n";
                }
            }
            else if (StrLower(Trim(A_LoopField116)) == StrLower(keyWordFinally) || StrLower(Trim(A_LoopField116)) == StrLower(keyWordFinally + ":")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordFinally_2 + ":\n";
                    } else {
                        htCode += keyWordFinally_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "if (" + Chr(34) + "finally dosent exist in c++" + Chr(34) + " == " + Chr(34) + "finally dosent exist in c++" + Chr(34) + ")\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "finally:\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "ensure\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "finally:\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "if (" + Chr(34) + "finally dosent exist in swift" + Chr(34) + " == " + Chr(34) + "finally dosent exist in swift" + Chr(34) + ")\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "finally\n";
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField116)), 1, StrLen(StrLower(keyWordThrow))) == StrLower(keyWordThrow)) {
                lineDone = 1;
                str1 = Trim(A_LoopField116);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str1 = expressionParserTranspiler(fixArray1234(Trim(StringTrimLeft(str1, StrLen(keyWordThrow)))));
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordThrow_2 + keyWordErrorMsg_2 + "(" + str1 + ");\n";
                    } else {
                        htCode += keyWordThrow_2 + keyWordErrorMsg_2 + "(" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "throw std::runtime_error(" + str1 + ");\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "raise Exception(" + str1 + ")\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "throw new Error(" + str1 + ");\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "throw new Exception(" + str1 + ");\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "throw new Exception(" + str1 + ");\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "throw Exception(" + str1 + ")" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "raise " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "raise newException(ValueError, " + str1 + ")\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "throw " + str1 + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "try ErrorMsg(" + str1 + ")\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "throw Exception(" + str1 + ");\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += " throw new Error(" + str1 + ");\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "throw new Exception(" + str1 + ")\n";
                }
            }
            else if (StrLower(A_LoopField116) == StrLower(keyWordBreak) || StrLower(A_LoopField116) == StrLower(keyWordBreak + ";")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordBreak_2 + ";\n";
                    } else {
                        htCode += keyWordBreak_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "break;\n";
                }
            }
            else if (StrLower(A_LoopField116) == StrLower(Trim(keyWordReturnStatement)) || StrLower(A_LoopField116) == StrLower(Trim(keyWordReturnStatement) + ";")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordReturnStatement_2 + ";\n";
                    } else {
                        htCode += keyWordReturnStatement_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "return;\n";
                }
            }
            else if (SubStr(Trim(StrLower(A_LoopField116)), 1, StrLen(StrLower(keyWordReturnStatement))) == StrLower(keyWordReturnStatement)) {
                lineDone = 1;
                str1 = Trim(expressionParserTranspiler(Trim(StringTrimLeft(A_LoopField116, StrLen(keyWordReturnStatement)))));
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
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "return " + str1 + ";\n";
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
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "return " + str1 + ";\n";
                }
            }
            else if (StrLower(A_LoopField116) == StrLower(keyWordContinue) || StrLower(A_LoopField116) == StrLower(keyWordContinue + ";")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordContinue_2 + ";\n";
                    } else {
                        htCode += keyWordContinue_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "goto continue" + STR(luaContinueFix_Num) + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "next\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "continue;\n";
                }
            }
            else if (StrLower(A_LoopField116) == "::" + keyWordContinue) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += "::" + keyWordContinue_2 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "::continue" + STR(luaContinueFix_Num) + "::" + Chr(10);
                    luaContinueFix_Num++;
                }
            }
            else if (StrLower(A_LoopField116) == StrLower(keyWordLoopInfinite) || StrLower(A_LoopField116) == StrLower(keyWordLoopInfinite + ":")) {
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
            else if (SubStr(Trim(StrLower(A_LoopField116)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop) && SubStr(Trim(StrLower(A_LoopField116)), 1, StrLen(StrLower(keyWordLoop)) + 2) != StrLower(keyWordLoop) + "% " && SubStr(Trim(StrLower(A_LoopField116)), 1, StrLen(StrLower(keyWordLoopParse))) != StrLower(keyWordLoopParse)) {
                out2 = StringTrimLeft(A_LoopField116, StrLen(keyWordLoop));
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
            else if (SubStr(Trim(StrLower(A_LoopField116)), 1, StrLen(StrLower(keyWordLoop)) + 2) == StrLower(keyWordLoop) + "% ") {
                howMany_fixAindexInGoUnused++;
                out2 = StringTrimLeft(A_LoopField116, StrLen(keyWordLoop) + 2);
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
            else if (SubStr(StrLower(A_LoopField116), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
                howMany_fixAindexInGoUnused++;
                var1 = StringTrimLeft(A_LoopField116, StrLen(keyWordLoopParse));
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
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
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
                        itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "groovy") {
                        itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                } else {
                    if (line2 == "" && line3 == "") {
                        // nothing so only each char
                        if (langToConvertTo == "py" || langToConvertTo == "js") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
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
                        if (langToConvertTo == "py" || langToConvertTo == "js") {
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
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
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
                        if (langToConvertTo == "py" || langToConvertTo == "js") {
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
                        htCode += Trim(keyWordLoopParse_2) + " " + StrReplace(var1, keyWordEscpaeChar, keyWordEscpaeChar_2) + ":\n";
                    } else {
                        htCode += Trim(keyWordLoopParse_2) + " " + StrReplace(var1, keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(10);
                    }
                } else {
                    htCode += htCodeLoopfixa1 + Chr(10) + var1out + Chr(10);
                }
            }
            else if (SubStrLastChars(Trim(A_LoopField116), StrLen(keyWordInc)) == keyWordInc || SubStrLastChars(Trim(A_LoopField116), StrLen(keyWordInc + ";")) == keyWordInc + ";" && lineDone == 0) {
                if (useSemicolon == "on") {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField116), StrLen(keyWordInc + ";")));
                } else {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField116), StrLen(keyWordInc)));
                }
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
            else if (SubStrLastChars(Trim(A_LoopField116), StrLen(keyWordDec)) == keyWordDec || SubStrLastChars(Trim(A_LoopField116), StrLen(keyWordDec + ";")) == keyWordDec + ";" && lineDone == 0) {
                if (useSemicolon == "on") {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField116), StrLen(keyWordDec + ";")));
                } else {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField116), StrLen(keyWordDec)));
                }
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
                    htCode += str1 + " = " + str1 + " - 1\n";
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
            else if (SubStr(StrLower(Trim(A_LoopField116)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ") && langToConvertTo == langFileExtension_2) {
                htCode += keyWordInclude_2 + " " + Trim(StringTrimLeft(Trim(A_LoopField116), StrLen(StrLower(keyWordInclude) + " "))) + Chr(10);
            }
            else if (StrLower(A_LoopField116) == StrLower(keyWordGlobal) || StrLower(A_LoopField116) == StrLower(keyWordGlobal + ";")) {
                if (langToConvertTo == "ahk") {
                    htCode += "global\n";
                }
            }
            else if (SubStr(StrLower(A_LoopField116), 1, StrLen(StrLower(keyWordAwait))) == StrLower(keyWordAwait)) {
                str1 = StringTrimLeft(A_LoopField116, StrLen(keyWordAwait));
                //MsgBox, % A_LoopField116
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
            else if (SubStr(StrLower(A_LoopField116), 1, StrLen(StrLower(keyWordGlobal))) == StrLower(keyWordGlobal)) {
                str1 = StringTrimLeft(A_LoopField116, StrLen(keyWordGlobal));
                //MsgBox, % A_LoopField116
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
            else if (SubStr(StrLower(A_LoopField116), 1, StrLen(keyWordFunc)) == StrLower(keyWordFunc) || SubStr(StrLower(A_LoopField116), 1, StrLen(StrLower(keyWordAsync) + StrLower(keyWordFunc))) == StrLower(keyWordAsync) + StrLower(keyWordFunc) && InStr(StrLower(A_LoopField116), " main(") == false && lineDone == 0) {
                lineDone = 1;
                if (SubStr(StrLower(A_LoopField116), 1, StrLen(StrLower(keyWordAsync) + StrLower(keyWordFunc))) == StrLower(keyWordAsync) + StrLower(keyWordFunc)) {
                    // is async
                    int1 = 1;
                    str1 = Trim(StringTrimLeft(A_LoopField116, StrLen(StrLower(keyWordAsync + keyWordFunc))));
                } else {
                    // is async
                    int1 = 0;
                    str1 = Trim(StringTrimLeft(A_LoopField116, StrLen(StrLower(keyWordFunc))));
                }
                if (langToConvertTo != "cpp" && langToConvertTo != "go" && langToConvertTo != "cs" && langToConvertTo != "java" && langToConvertTo != "kt" && langToConvertTo != "nim" && langToConvertTo != "swift" && langToConvertTo != "dart" && langToConvertTo != "ts") {
                    if (str1 != "") {
                        str4 = "";
                        std::vector<std::string> items118 = LoopParseFunc(str1, ",");
                        for (size_t A_Index118 = 0; A_Index118 < items118.size() + 0; A_Index118++) {
                            std::string A_LoopField118 = items118[A_Index118 - 0];
                            if (InStr(A_LoopField118, " := ")) {
                                if (InStr(Trim(StrSplit(A_LoopField118, " := ", 1)), " ") != true) {
                                    str4 += "optanal-HTVM-opt-parmsNOtWorking-theirewIs-a-bug-Iusfbudfbuoeshfuisbav=-fwaegs-awedsf-dd-sfgc " + A_LoopField118 + ", ";
                                } else {
                                    str4 += A_LoopField118 + ", ";
                                }
                            }
                            else if (InStr(A_LoopField118, " = ")) {
                                if (InStr(Trim(StrSplit(A_LoopField118, " = ", 1)), " ") != true) {
                                    str4 += "optanal-HTVM-opt-parmsNOtWorking-theirewIs-a-bug-Iusfbudfbuoeshfuisbav=-fwaegs-awedsf-dd-sfgc " + A_LoopField118 + ", ";
                                } else {
                                    str4 += A_LoopField118 + ", ";
                                }
                            } else {
                                str4 += A_LoopField118 + ", ";
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
                            htCode += "function " + str2 + "()" + Chr(10);
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
                            htCode += "function " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
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
                    std::vector<std::string> items119 = LoopParseFunc(str1, ",");
                    for (size_t A_Index119 = 0; A_Index119 < items119.size() + 0; A_Index119++) {
                        std::string A_LoopField119 = items119[A_Index119 - 0];
                        //print("|" . Trim(A_LoopField119) . "|")
                        if (InStr(Trim(A_LoopField119), " ")) {
                            // there is space aka there is a type
                            if (InStr(A_LoopField119, " " + Trim(keyWordAssign) + " ") == false) {
                                if (usePrefixTypeForTypeDefinition == "on") {
                                    // normal
                                    str6 = Trim(A_LoopField119);
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
                                    str6 = Trim(A_LoopField119);
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
                                if (InStr(Trim(StrSplit(Trim(A_LoopField119), " " + Trim(keyWordAssign) + " ", 1)), " ")) {
                                    // there is a type
                                    if (usePrefixTypeForTypeDefinition == "on") {
                                        // normal
                                        str6 = Trim(StrSplit(Trim(A_LoopField119), " " + Trim(keyWordAssign) + " ", 1));
                                        str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField119), " " + Trim(keyWordAssign) + " ", 2))));
                                        str7 = getTheLastWord(str6);
                                        str8 = getFuncTypeConvert(Trim(StringTrimRight(str6, StrLen(Trim(str7)) + 1)));
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;
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
                                            if (RegExMatch(str9, "^\\d+(\\.\\d+)?$")) {
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
                                            if (RegExMatch(str9, "^\\d+(\\.\\d+)?$")) {
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
                                        str6 = Trim(StrSplit(Trim(A_LoopField119), " " + Trim(keyWordAssign) + " ", 1));
                                        str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField119), " " + Trim(keyWordAssign) + " ", 2))));
                                        str7 = Trim(StrSplit(str6, ":", 1));
                                        str8 = getFuncTypeConvert(Trim(StrSplit(str6, ":", 2)));
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;
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
                                            if (RegExMatch(str9, "^\\d+(\\.\\d+)?$")) {
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
                                            if (RegExMatch(str9, "^\\d+(\\.\\d+)?$")) {
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
                                    str8 = Trim(StrSplit(Trim(A_LoopField119), " " + Trim(keyWordAssign) + " ", 1));
                                    str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField119), " " + Trim(keyWordAssign) + " ", 2))));
                                    // str10
                                    // skipLeftCuleyForFuncPLS := 1
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;
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
                            str5 += Trim(A_LoopField119) + Chr(10);
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
                        std::vector<std::string> items120 = LoopParseFunc(str5, "\n", "\r");
                        for (size_t A_Index120 = 0; A_Index120 < items120.size() + 0; A_Index120++) {
                            std::string A_LoopField120 = items120[A_Index120 - 0];
                            str11 += A_LoopField120 + ", ";
                        }
                        std::vector<std::string> items121 = LoopParseFunc(str10, "\n", "\r");
                        for (size_t A_Index121 = 0; A_Index121 < items121.size() + 0; A_Index121++) {
                            std::string A_LoopField121 = items121[A_Index121 - 0];
                            str12 += A_LoopField121 + ", ";
                        }
                        str12 = StringTrimRight(str12, 2);
                        if (langToConvertTo == "dart") {
                            str12 = "[" + str12 + "]";
                        }
                        if (langToConvertTo == "lua") {
                            std::vector<std::string> items122 = LoopParseFunc(str12, ",");
                            for (size_t A_Index122 = 0; A_Index122 < items122.size() + 0; A_Index122++) {
                                std::string A_LoopField122 = items122[A_Index122 - 0];
                                str14 += Trim(StrSplit(Trim(A_LoopField122), " = ", 1)) + ", ";
                            }
                            str14 = StringTrimRight(str14, 2);
                            str13 += "{" + Chr(10);
                            std::vector<std::string> items123 = LoopParseFunc(str12, ",");
                            for (size_t A_Index123 = 0; A_Index123 < items123.size() + 0; A_Index123++) {
                                std::string A_LoopField123 = items123[A_Index123 - 0];
                                str13 += Trim(StrSplit(Trim(A_LoopField123), " = ", 1)) + " = " + Trim(StrSplit(Trim(A_LoopField123), " = ", 1)) + " or " + Trim(StrSplit(Trim(A_LoopField123), " = ", 2)) + Chr(10);
                            }
                            str12 = str14;
                        }
                        if (langToConvertTo == "go") {
                            str14 = "__HTVM_V2_TO_GO_optionalParams__ ...interface{}";
                            str13 += "{" + Chr(10) + " ";
                            std::vector<std::string> items124 = LoopParseFunc(str12, ",");
                            for (size_t A_Index124 = 0; A_Index124 < items124.size() + 0; A_Index124++) {
                                std::string A_LoopField124 = items124[A_Index124 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField124), " = ", 1)), " ", 1));
                                str17 = Trim(StrSplit(Trim(A_LoopField124), " = ", 2));
                                str13 += str16 + " := " + str17 + Chr(10);
                            }
                            std::vector<std::string> items125 = LoopParseFunc(str12, ",");
                            for (size_t A_Index125 = 0; A_Index125 < items125.size() + 0; A_Index125++) {
                                std::string A_LoopField125 = items125[A_Index125 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField125), " = ", 1)), " ", 1));
                                str18 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField125), " = ", 1)), " ", 2));
                                // str16 = var name
                                // str18 = var type
                                str13 += "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " " + STR(A_Index125) + Chr(10) + "{" + Chr(10) + str16 + " = __HTVM_V2_TO_GO_optionalParams__[" + STR(A_Index125) + "].(" + str18 + ")" + Chr(10) + "}" + Chr(10);
                            }
                            str12 = str14;
                        }
                        if (langToConvertTo == "java") {
                            str14 = "Object... __HTVM_V2_TO_JAVA_optionalParams__";
                            str13 += "{" + Chr(10);
                            std::vector<std::string> items126 = LoopParseFunc(str12, ",");
                            for (size_t A_Index126 = 0; A_Index126 < items126.size() + 0; A_Index126++) {
                                std::string A_LoopField126 = items126[A_Index126 - 0];
                                str19 = Trim(A_LoopField126);
                                str20 = "";
                                std::vector<std::string> items127 = LoopParseFunc(str19, " ");
                                for (size_t A_Index127 = 0; A_Index127 < items127.size() + 0; A_Index127++) {
                                    std::string A_LoopField127 = items127[A_Index127 - 0];
                                    if (A_Index127 == 3) {
                                        if (RegExMatch(A_LoopField127, "^\\d+(\\.\\d+)?$")) {
                                            str20 += A_LoopField127 + "f ";
                                        } else {
                                            str20 += A_LoopField127 + " ";
                                        }
                                    } else {
                                        str20 += A_LoopField127 + " ";
                                    }
                                }
                                str20 = StringTrimRight(str20, 1);
                                str13 += Trim(str20) + ";" + Chr(10);
                            }
                            std::vector<std::string> items128 = LoopParseFunc(str12, ",");
                            for (size_t A_Index128 = 0; A_Index128 < items128.size() + 0; A_Index128++) {
                                std::string A_LoopField128 = items128[A_Index128 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField128), " = ", 1)), " ", 2));
                                str17 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField128), " = ", 1)), " ", 1));
                                // str16 = var name
                                // str17 = type name
                                str13 += "if (__HTVM_V2_TO_JAVA_optionalParams__.length " + Chr(62) + " " + STR(A_Index128) + ") " + str16 + " = (" + str17 + ") __HTVM_V2_TO_JAVA_optionalParams__[" + STR(A_Index128) + "];" + Chr(10);
                            }
                            str12 = str14;
                        }
                        str11 += str12;
                    }
                    if (Trim(str5) != "" && Trim(str10) == "") {
                        std::vector<std::string> items129 = LoopParseFunc(str5, "\n", "\r");
                        for (size_t A_Index129 = 0; A_Index129 < items129.size() + 0; A_Index129++) {
                            std::string A_LoopField129 = items129[A_Index129 - 0];
                            str11 += A_LoopField129 + ", ";
                        }
                        str11 = StringTrimRight(str11, 2);
                    }
                    if (Trim(str5) == "" && Trim(str10) != "") {
                        std::vector<std::string> items130 = LoopParseFunc(str10, "\n", "\r");
                        for (size_t A_Index130 = 0; A_Index130 < items130.size() + 0; A_Index130++) {
                            std::string A_LoopField130 = items130[A_Index130 - 0];
                            str11 += A_LoopField130 + ", ";
                        }
                        str11 = StringTrimRight(str11, 2);
                        if (langToConvertTo == "dart") {
                            str11 = "[" + str11 + "]";
                        }
                        if (langToConvertTo == "lua") {
                            std::vector<std::string> items131 = LoopParseFunc(str11, ",");
                            for (size_t A_Index131 = 0; A_Index131 < items131.size() + 0; A_Index131++) {
                                std::string A_LoopField131 = items131[A_Index131 - 0];
                                str14 += Trim(StrSplit(Trim(A_LoopField131), " = ", 1)) + ", ";
                            }
                            str14 = StringTrimRight(str14, 2);
                            str13 += "{" + Chr(10);
                            std::vector<std::string> items132 = LoopParseFunc(str11, ",");
                            for (size_t A_Index132 = 0; A_Index132 < items132.size() + 0; A_Index132++) {
                                std::string A_LoopField132 = items132[A_Index132 - 0];
                                str13 += Trim(StrSplit(Trim(A_LoopField132), " = ", 1)) + " = " + Trim(StrSplit(Trim(A_LoopField132), " = ", 1)) + " or " + Trim(StrSplit(Trim(A_LoopField132), " = ", 2)) + Chr(10);
                            }
                            str11 = str14;
                        }
                        if (langToConvertTo == "go") {
                            str14 = "__HTVM_V2_TO_GO_optionalParams__ ...interface{}";
                            str13 += "{" + Chr(10) + " ";
                            std::vector<std::string> items133 = LoopParseFunc(str11, ",");
                            for (size_t A_Index133 = 0; A_Index133 < items133.size() + 0; A_Index133++) {
                                std::string A_LoopField133 = items133[A_Index133 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField133), " = ", 1)), " ", 1));
                                str17 = Trim(StrSplit(Trim(A_LoopField133), " = ", 2));
                                str13 += str16 + " := " + str17 + Chr(10);
                            }
                            std::vector<std::string> items134 = LoopParseFunc(str11, ",");
                            for (size_t A_Index134 = 0; A_Index134 < items134.size() + 0; A_Index134++) {
                                std::string A_LoopField134 = items134[A_Index134 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField134), " = ", 1)), " ", 1));
                                str18 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField134), " = ", 1)), " ", 2));
                                // str16 = var name
                                // str18 = var type
                                str13 += "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " " + STR(A_Index134) + Chr(10) + "{" + Chr(10) + str16 + " = __HTVM_V2_TO_GO_optionalParams__[" + STR(A_Index134) + "].(" + str18 + ")" + Chr(10) + "}" + Chr(10);
                            }
                            str11 = str14;
                        }
                        if (langToConvertTo == "java") {
                            str14 = "Object... __HTVM_V2_TO_JAVA_optionalParams__";
                            str13 += "{" + Chr(10);
                            std::vector<std::string> items135 = LoopParseFunc(str11, ",");
                            for (size_t A_Index135 = 0; A_Index135 < items135.size() + 0; A_Index135++) {
                                std::string A_LoopField135 = items135[A_Index135 - 0];
                                str19 = Trim(A_LoopField135);
                                str20 = "";
                                std::vector<std::string> items136 = LoopParseFunc(str19, " ");
                                for (size_t A_Index136 = 0; A_Index136 < items136.size() + 0; A_Index136++) {
                                    std::string A_LoopField136 = items136[A_Index136 - 0];
                                    if (A_Index136 == 3) {
                                        if (RegExMatch(A_LoopField136, "^\\d+(\\.\\d+)?$")) {
                                            str20 += A_LoopField136 + "f ";
                                        } else {
                                            str20 += A_LoopField136 + " ";
                                        }
                                    } else {
                                        str20 += A_LoopField136 + " ";
                                    }
                                }
                                str20 = StringTrimRight(str20, 1);
                                str13 += Trim(str20) + ";" + Chr(10);
                            }
                            std::vector<std::string> items137 = LoopParseFunc(str11, ",");
                            for (size_t A_Index137 = 0; A_Index137 < items137.size() + 0; A_Index137++) {
                                std::string A_LoopField137 = items137[A_Index137 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField137), " = ", 1)), " ", 2));
                                str17 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField137), " = ", 1)), " ", 1));
                                // str16 = var name
                                // str17 = type name
                                str13 += "if (__HTVM_V2_TO_JAVA_optionalParams__.length " + Chr(62) + " " + STR(A_Index137) + ") " + str16 + " = (" + str17 + ") __HTVM_V2_TO_JAVA_optionalParams__[" + STR(A_Index137) + "];" + Chr(10);
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
                            htCode += "function " + str2 + "(" + str11 + ")" + Chr(10);
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
                        htCode += "function " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
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
            else if (InStr(StrLower(A_LoopField116), " main(") && lineDone == 0) {
                lineDone = 1;
                javaMainFuncSeen = 1;
                csMainFuncSeen = 1;
                htCode += A_LoopField116 + Chr(10);
            }
            else if (InStr(A_LoopField116, " " + keyWordAssign + " ") || InStr(A_LoopField116, " " + keyWordAssignAdd + " ") || InStr(A_LoopField116, " " + keyWordAssignConcat + " ") || InStr(A_LoopField116, " " + keyWordAssignSub + " ") || InStr(A_LoopField116, " " + keyWordAssignMul + " ") || InStr(A_LoopField116, " " + keyWordAssignDiv + " ") || InStr(A_LoopField116, " " + keyWordAssignMod + " ") || InStr(A_LoopField116, " " + keyWordAssignShiftLeft + " ") || InStr(A_LoopField116, " " + keyWordAssignShiftRight + " ") || InStr(A_LoopField116, " " + keyWordLogicalAssignShiftRight + " ") || InStr(A_LoopField116, " " + keyWordAssignBitAnd + " ") || InStr(A_LoopField116, " " + keyWordAssignBitOr + " ") || InStr(A_LoopField116, " " + keyWordAssignBitXor + " ") && lineDone == 0) {
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
                if (InStr(A_LoopField116, " " + keyWordAssign + " ")) {
                    str1 = StrSplit(A_LoopField116, " " + keyWordAssign + " ", 1);
                    str6 = StrSplit(A_LoopField116, " " + keyWordAssign + " ", 2);
                    str10 = keyWordAssign;
                    str11 = keyWordAssign_2;
                    if (langToConvertTo == "ahk") {
                        str12 = ":=";
                    } else {
                        str12 = "=";
                    }
                }
                else if (InStr(A_LoopField116, " " + keyWordAssignAdd + " ")) {
                    str1 = StrSplit(A_LoopField116, " " + keyWordAssignAdd + " ", 1);
                    str6 = StrSplit(A_LoopField116, " " + keyWordAssignAdd + " ", 2);
                    str10 = keyWordAssignAdd;
                    str11 = keyWordAssignAdd_2;
                    str12 = "+=";
                }
                else if (InStr(A_LoopField116, " " + keyWordAssignConcat + " ")) {
                    str1 = StrSplit(A_LoopField116, " " + keyWordAssignConcat + " ", 1);
                    str6 = StrSplit(A_LoopField116, " " + keyWordAssignConcat + " ", 2);
                    str10 = keyWordAssignConcat;
                    str11 = keyWordAssignConcat_2;
                    if (langToConvertTo == "ahk") {
                        str12 = ".=";
                    } else {
                        str12 = "+=";
                    }
                }
                else if (InStr(A_LoopField116, " " + keyWordAssignSub + " ")) {
                    str1 = StrSplit(A_LoopField116, " " + keyWordAssignSub + " ", 1);
                    str6 = StrSplit(A_LoopField116, " " + keyWordAssignSub + " ", 2);
                    str10 = keyWordAssignSub;
                    str11 = keyWordAssignSub_2;
                    str12 = "-=";
                }
                else if (InStr(A_LoopField116, " " + keyWordAssignMul + " ")) {
                    str1 = StrSplit(A_LoopField116, " " + keyWordAssignMul + " ", 1);
                    str6 = StrSplit(A_LoopField116, " " + keyWordAssignMul + " ", 2);
                    str10 = keyWordAssignMul;
                    str11 = keyWordAssignMul_2;
                    str12 = "*=";
                }
                else if (InStr(A_LoopField116, " " + keyWordAssignDiv + " ")) {
                    str1 = StrSplit(A_LoopField116, " " + keyWordAssignDiv + " ", 1);
                    str6 = StrSplit(A_LoopField116, " " + keyWordAssignDiv + " ", 2);
                    str10 = keyWordAssignDiv;
                    str11 = keyWordAssignDiv_2;
                    str12 = "/=";
                }
                else if (InStr(A_LoopField116, " " + keyWordAssignMod + " ")) {
                    str1 = StrSplit(A_LoopField116, " " + keyWordAssignMod + " ", 1);
                    str6 = StrSplit(A_LoopField116, " " + keyWordAssignMod + " ", 2);
                    str10 = keyWordAssignMod;
                    str11 = keyWordAssignMod_2;
                    str12 = "%=";
                }
                else if (InStr(A_LoopField116, " " + keyWordAssignShiftLeft + " ")) {
                    str1 = StrSplit(A_LoopField116, " " + keyWordAssignShiftLeft + " ", 1);
                    str6 = StrSplit(A_LoopField116, " " + keyWordAssignShiftLeft + " ", 2);
                    str10 = keyWordAssignShiftLeft;
                    str11 = keyWordAssignShiftLeft_2;
                    str12 = "<<=";
                }
                else if (InStr(A_LoopField116, " " + keyWordAssignShiftRight + " ")) {
                    str1 = StrSplit(A_LoopField116, " " + keyWordAssignShiftRight + " ", 1);
                    str6 = StrSplit(A_LoopField116, " " + keyWordAssignShiftRight + " ", 2);
                    str10 = keyWordAssignShiftRight;
                    str11 = keyWordAssignShiftRight_2;
                    str12 = ">>=";
                }
                else if (InStr(A_LoopField116, " " + keyWordLogicalAssignShiftRight + " ")) {
                    str1 = StrSplit(A_LoopField116, " " + keyWordLogicalAssignShiftRight + " ", 1);
                    str6 = StrSplit(A_LoopField116, " " + keyWordLogicalAssignShiftRight + " ", 2);
                    str10 = keyWordLogicalAssignShiftRight;
                    str11 = keyWordLogicalAssignShiftRight_2;
                    str12 = ">>>=";
                }
                else if (InStr(A_LoopField116, " " + keyWordAssignBitAnd + " ")) {
                    str1 = StrSplit(A_LoopField116, " " + keyWordAssignBitAnd + " ", 1);
                    str6 = StrSplit(A_LoopField116, " " + keyWordAssignBitAnd + " ", 2);
                    str10 = keyWordAssignBitAnd;
                    str11 = keyWordAssignBitAnd_2;
                    str12 = "&=";
                }
                else if (InStr(A_LoopField116, " " + keyWordAssignBitOr + " ")) {
                    str1 = StrSplit(A_LoopField116, " " + keyWordAssignBitOr + " ", 1);
                    str6 = StrSplit(A_LoopField116, " " + keyWordAssignBitOr + " ", 2);
                    str10 = keyWordAssignBitOr;
                    str11 = keyWordAssignBitOr_2;
                    str12 = "|=";
                }
                else if (InStr(A_LoopField116, " " + keyWordAssignBitXor + " ")) {
                    str1 = StrSplit(A_LoopField116, " " + keyWordAssignBitXor + " ", 1);
                    str6 = StrSplit(A_LoopField116, " " + keyWordAssignBitXor + " ", 2);
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
                if (InStr(ALoopField, " ") == false) {
                    lineDone = 1;
                    str1 = StrReplace(Trim(str1), ".", "_");
                    str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str1);
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
                        if (InStr(str1, "[")) {
                            // Convert arr[something] to arr.set(something, value);
                            str1 = RegExReplace(str1, "(\\b[A-Za-z_]\\w*)\\s*\\[(.*?)\\]", "$1.set($2, ");
                            str4 = str1 + str6 + ");";
                        } else {
                            str4 = str1 + " " + str12 + " " + str6 + ";";
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
                        std::vector<std::string> items138 = LoopParseFunc(str1, " ");
                        for (size_t A_Index138 = 0; A_Index138 < items138.size() + 0; A_Index138++) {
                            std::string A_LoopField138 = items138[A_Index138 - 0];
                            str2 = A_LoopField138;
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
                        str3 = getFuncTypeConvert(str3);
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                str6 = "{" + str6 + "}";
                            } else {
                                str6 = "[" + str6 + "]";
                            }
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordConst_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = keyWordConst_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordConst_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = keyWordConst_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        }
                        if (langToConvertTo == "js") {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        }
                        if (langToConvertTo == "go") {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "let " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " := [" + str6 + "]";
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = str2 + " = [" + str6 + "]";
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
                                    str4 = keyWordConst_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = keyWordConst_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordConst_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = keyWordConst_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
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
                        std::vector<std::string> items139 = LoopParseFunc(str1, " ");
                        for (size_t A_Index139 = 0; A_Index139 < items139.size() + 0; A_Index139++) {
                            std::string A_LoopField139 = items139[A_Index139 - 0];
                            str2 = A_LoopField139;
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
                        str3 = getFuncTypeConvert(str3);
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                str6 = "{" + str6 + "}";
                            } else {
                                str6 = "[" + str6 + "]";
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
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        }
                        if (langToConvertTo == "js") {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        }
                        if (langToConvertTo == "go") {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " := [" + str6 + "]";
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = str2 + " = [" + str6 + "]";
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
                    htCode += str4 + Chr(10);
                }
                else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordLet)) == keyWordLet && lineDone == 0) {
                    lineDone = 1;
                    if (usePostfixTypeForTypeDefinition == "off") {
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordLet)));
                        std::vector<std::string> items140 = LoopParseFunc(str1, " ");
                        for (size_t A_Index140 = 0; A_Index140 < items140.size() + 0; A_Index140++) {
                            std::string A_LoopField140 = items140[A_Index140 - 0];
                            str2 = A_LoopField140;
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
                        str3 = getFuncTypeConvert(str3);
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                str6 = "{" + str6 + "}";
                            } else {
                                str6 = "[" + str6 + "]";
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
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        }
                        if (langToConvertTo == "js") {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        }
                        if (langToConvertTo == "go") {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " := [" + str6 + "]";
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = str2 + " = [" + str6 + "]";
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
                    std::vector<std::string> items141 = LoopParseFunc(str1, " ");
                    for (size_t A_Index141 = 0; A_Index141 < items141.size() + 0; A_Index141++) {
                        std::string A_LoopField141 = items141[A_Index141 - 0];
                        str2 = A_LoopField141;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                        str3 = getFuncTypeConvert(str3);
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                str6 = "{" + str6 + "}";
                            } else {
                                str6 = "[" + str6 + "]";
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
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        }
                        if (langToConvertTo == "js") {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        }
                        if (langToConvertTo == "go") {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " := [" + str6 + "]";
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = str2 + " = [" + str6 + "]";
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
                        str3 = getFuncTypeConvert(str3);
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                str6 = "{" + str6 + "}";
                            } else {
                                str6 = "[" + str6 + "]";
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
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        }
                        if (langToConvertTo == "js") {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        }
                        if (langToConvertTo == "go") {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " := [" + str6 + "]";
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = str2 + " = [" + str6 + "]";
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
            else if (SubStr(Trim(A_LoopField116), 1, StrLen(keyWordVar)) == keyWordVar && lineDone == 0) {
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField116), StrLen(keyWordVar)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    std::vector<std::string> items142 = LoopParseFunc(str1, " ");
                    for (size_t A_Index142 = 0; A_Index142 < items142.size() + 0; A_Index142++) {
                        std::string A_LoopField142 = items142[A_Index142 - 0];
                        str2 = A_LoopField142;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField116), StrLen(keyWordVar)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    str2 = Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                }
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
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
                        str4 = "val " + str2 + " = " + str3 + "()";
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
            else if (SubStr(Trim(A_LoopField116), 1, StrLen(keyWordLet)) == keyWordLet && lineDone == 0) {
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField116), StrLen(keyWordLet)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    std::vector<std::string> items143 = LoopParseFunc(str1, " ");
                    for (size_t A_Index143 = 0; A_Index143 < items143.size() + 0; A_Index143++) {
                        std::string A_LoopField143 = items143[A_Index143 - 0];
                        str2 = A_LoopField143;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField116), StrLen(keyWordLet)));
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
                        str4 = "val " + str2 + " = " + str3 + "()";
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
            else if (SubStr(Trim(A_LoopField116), 1, StrLen(keyWordDouble + " ")) == keyWordDouble + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordChar + " ")) == keyWordChar + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordUint8 + " ")) == keyWordUint8 + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordUint16 + " ")) == keyWordUint16 + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordUint32 + " ")) == keyWordUint32 + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordUint64 + " ")) == keyWordUint64 + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordINT + " ")) == keyWordINT + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordSTR + " ")) == keyWordSTR + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordBOOL + " ")) == keyWordBOOL + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordFLOAT + " ")) == keyWordFLOAT + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordINT8 + " ")) == keyWordINT8 + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordINT16 + " ")) == keyWordINT16 + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordINT32 + " ")) == keyWordINT32 + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordINT64 + " ")) == keyWordINT64 + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordArrayDefinition + " ")) == keyWordArrayDefinition + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordArrayOfIntegersDefinition + " ")) == keyWordArrayOfIntegersDefinition + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordArrayOfStringsDefinition + " ")) == keyWordArrayOfStringsDefinition + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordArrayOfFloatingPointNumbersDefinition + " ")) == keyWordArrayOfFloatingPointNumbersDefinition + " " || SubStr(Trim(A_LoopField116), 1, StrLen(keyWordArrayOfBooleansDefinition + " ")) == keyWordArrayOfBooleansDefinition + " " && usePrefixTypeForTypeDefinition == "on" && lineDone == 0) {
                lineDone = 1;
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                str1 = Trim(A_LoopField116);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                std::vector<std::string> items144 = LoopParseFunc(str1, " ");
                for (size_t A_Index144 = 0; A_Index144 < items144.size() + 0; A_Index144++) {
                    std::string A_LoopField144 = items144[A_Index144 - 0];
                    str2 = A_LoopField144;
                }
                str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                str2 = Trim(str2);
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
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
                        str4 = "val " + str2 + " = " + str3 + "()";
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
            else if (RegExMatch(Trim(A_LoopField116), "^[a-zA-Z_][a-zA-Z0-9_]*: [^:]*;?$") && usePostfixTypeForTypeDefinition == "on" && lineDone == 0) {
                lineDone = 1;
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                str1 = Trim(A_LoopField116);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str2 = Trim(StrSplit(str1, ":", 1));
                str3 = Trim(StrSplit(str1, ":", 2));
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
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
                        str4 = "val " + str2 + " = " + str3 + "()";
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
            else if (RegExMatch(Trim(A_LoopField116), "^[a-zA-Z0-9_\\.]+\\(") && !(InStr(StrLower(A_LoopField116), " main(")) && lineDone == 0) {
                lineDone = 1;
                str1 = Trim(A_LoopField116);
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
            else if (KeyWordsCommands(A_LoopField116, "check", commands, langToConvertTo) == "true" && lineDone == 0) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += A_LoopField116 + Chr(10);
                } else {
                    out_KeyWordsCommands = KeyWordsCommands(A_LoopField116, "transpile", commands, langToConvertTo);
                    htCode += out_KeyWordsCommands + Chr(10);
                }
            } else {
                //print("else else else " . A_LoopField116)
                // this is THE else
                //;;;;;;;;;;;;;;;;;;
                if (lineDone != 1) {
                    if (skipLeftCuleyForFuncPLS != 1) {
                        if (SubStr(Trim(StrLower(A_LoopField116)), 1, 1) == Chr(125)) {
                            htCode += Chr(125) + Chr(10);
                        } else {
                            if (htCodeAcurlyBraceAddSomeVrasFixLP == 1 && SubStr(Trim(StrLower(A_LoopField116)), 1, 1) == Chr(123)) {
                                htCodeAcurlyBraceAddSomeVrasFixLP = 0;
                                htCode += A_LoopField116 + Chr(10) + theFixTextLoopLP + Chr(10);
                            } else {
                                if (htCodeAcurlyBraceAddSomeVrasFixNL == 1 && SubStr(Trim(StrLower(A_LoopField116)), 1, 1) == Chr(123)) {
                                    htCodeAcurlyBraceAddSomeVrasFixNL = 0;
                                    htCode += A_LoopField116 + Chr(10) + theFixTextLoopNL + Chr(10);
                                } else {
                                    htCode += A_LoopField116 + Chr(10);
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
                std::vector<std::string> items145 = LoopParseFunc(htCodeLoopfixa, "\n", "\r");
                for (size_t A_Index145 = 0; A_Index145 < items145.size() + 0; A_Index145++) {
                    std::string A_LoopField145 = items145[A_Index145 - 0];
                    sstr123 = A_LoopField145;
                    fixLoopLokingFor = A_LoopField145;
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
                        std::vector<std::string> items146 = LoopParseFunc(htCode, "\n", "\r");
                        for (size_t A_Index146 = 0; A_Index146 < items146.size() + 0; A_Index146++) {
                            std::string A_LoopField146 = items146[A_Index146 - 0];
                            //MsgBox, dsfgsdefgesrdg1
                            //MsgBox, |%A_LoopField146%|`n|%fixLoopLokingFor%|
                            if (InStr(A_LoopField146, fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 1
                            }
                            if (SubStr(Trim(A_LoopField146), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField146 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(s);
                                //MsgBox, % out1z
                                //MsgBox, do we came here 2
                                fixLoopLokingForNum = 0;
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField146
                                dontSaveStr = 1;
                                ALoopField = A_LoopField146;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if (inTarget == 1 && InStr(A_LoopField146, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField146, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField146, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField146), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField146, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField146, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField146, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField146, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField146
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField146 + Chr(10);
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField146;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if (inTarget == 1 && InStr(A_LoopField146, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1) {
                                //MsgBox, % A_LoopField146
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField146 + Chr(10);
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
                        std::vector<std::string> items147 = LoopParseFunc(htCode, "\n", "\r");
                        for (size_t A_Index147 = 0; A_Index147 < items147.size() + 0; A_Index147++) {
                            std::string A_LoopField147 = items147[A_Index147 - 0];
                            if (InStr(A_LoopField147 , fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 3
                            }
                            if (SubStr(Trim(A_LoopField147), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField147 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(StrReplace(s, "|", ""));
                                //MsgBox, % out1z
                                fixLoopLokingForNum = 0;
                                //MsgBox, do we came here 4
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField147
                                dontSaveStr = 1;
                                ALoopField = A_LoopField147;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if (inTarget == 1 && InStr(A_LoopField147, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField147, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField147, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField147), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField147, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField147, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField147, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField147, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField147
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField147 + Chr(10);
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField147;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordALoopField + "\\d*", "" + keyWordALoopField + "" + out1z);
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if ((inTarget == 1 && InStr(A_LoopField147, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1)) {
                                //MsgBox, % A_LoopField147
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField147 + Chr(10);
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
                std::vector<std::string> items148 = LoopParseFunc(htCode, "\n", "\r");
                for (size_t A_Index148 = 0; A_Index148 < items148.size() + 0; A_Index148++) {
                    std::string A_LoopField148 = items148[A_Index148 - 0];
                    ignore = 0;
                    if (SubStr(Trim(A_LoopField148), 1, 4) == "for ") {
                        if (hold == 1 && holdText == A_LoopField148) {
                            ignore = 1;
                        } else {
                            holdText = A_LoopField148;
                            hold = 1;
                        }
                    }
                    if (!ignore) {
                        out4758686d86dgt8r754444444 += A_LoopField148 + Chr(10);
                    }
                }
                out4758686d86dgt8r754444444 = StringTrimRight(out4758686d86dgt8r754444444, 1);
                htCode = out4758686d86dgt8r754444444;
            }
            htCodeOut1234565432 = "";
            std::vector<std::string> items149 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index149 = 0; A_Index149 < items149.size() + 0; A_Index149++) {
                std::string A_LoopField149 = items149[A_Index149 - 0];
                out = A_LoopField149;
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
        for (int A_Index150 = 0; A_Index150 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index150++) {
            ADD_ALL_programmingBlock_HTVMsyntax += programmingBlock_HTVMsyntax[A_Index150] + Chr(10);
        }
        ADD_ALL_programmingBlock_HTVMsyntax = StringTrimRight(ADD_ALL_programmingBlock_HTVMsyntax, 1);
        ADD_ALL_programmingBlock_HTVMsyntax = compiler(ADD_ALL_programmingBlock_HTVMsyntax, allInstructionFile, "full", langToConvertToParam);
        isNotHTVMfileEXTRA_INT = 0;
        isNotHTVMfile2 = 1;
        for (int A_Index151 = 0; A_Index151 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index151++) {
            htCode = StrReplace(htCode, "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(A_Index151 + 1) + "AA", compiler(programmingBlock_HTVMsyntax[A_Index151], allInstructionFile, "full", langToConvertToParam));
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
        print("\nYou must include all the libs from under the section and MAKE SURE your code doesn't already use them!!!");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("\nYou must copy-paste all the funcs from under the section and MAKE SURE your code doesn't already use them!!!");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed\n");
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
            std::vector<std::string> items152 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index152 = 0; A_Index152 < items152.size() + 0; A_Index152++) {
                std::string A_LoopField152 = items152[A_Index152 - 0];
                if (Trim(A_LoopField152) == keyWordCurlyBraceClose_2) {
                    fixLuaAndRuby += StrReplace(A_LoopField152, keyWordCurlyBraceClose_2, Trim(keyWordEnd_2)) + Chr(10);
                }
                else if (SubStrLastChars(A_LoopField152, 2) == " " + keyWordCurlyBraceOpen_2) {
                    fixLuaAndRuby += StringTrimRight(A_LoopField152, 2) + Chr(10);
                } else {
                    fixLuaAndRuby += A_LoopField152 + Chr(10);
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
                std::vector<std::string> items153 = LoopParseFunc(htCode, "\n", "\r");
                for (size_t A_Index153 = 0; A_Index153 < items153.size() + 0; A_Index153++) {
                    std::string A_LoopField153 = items153[A_Index153 - 0];
                    if (Trim(A_LoopField153) == "}") {
                        fixLuaAndRuby += StrReplace(A_LoopField153, "}", fixLuaAndRubyHELP) + Chr(10);
                    }
                    else if (SubStrLastChars(A_LoopField153, 2) == " {") {
                        fixLuaAndRuby += StringTrimRight(A_LoopField153, 2) + Chr(10);
                    } else {
                        fixLuaAndRuby += A_LoopField153 + Chr(10);
                    }
                }
                htCode = StringTrimRight(fixLuaAndRuby, 1);
            } else {
                fixLuaAndRubyHELP = "end";
                std::vector<std::string> items154 = LoopParseFunc(htCode, "\n", "\r");
                for (size_t A_Index154 = 0; A_Index154 < items154.size() + 0; A_Index154++) {
                    std::string A_LoopField154 = items154[A_Index154 - 0];
                    if (Trim(A_LoopField154) == "}") {
                        fixLuaAndRuby += StrReplace(A_LoopField154, "}", fixLuaAndRubyHELP) + Chr(10);
                    }
                    else if (SubStrLastChars(A_LoopField154, 2) == " {") {
                        fixLuaAndRuby += StringTrimRight(A_LoopField154, 2) + Chr(10);
                    } else {
                        fixLuaAndRuby += A_LoopField154 + Chr(10);
                    }
                }
                htCode = StringTrimRight(fixLuaAndRuby, 1);
            }
        }
    }
    std::vector<std::string> nextWordEndFix;
    std::string nextWordEndFixOut = "";
    if (langToConvertTo == langFileExtension_2 && useEnd_2 == "on") {
        std::vector<std::string> items155 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index155 = 0; A_Index155 < items155.size() + 0; A_Index155++) {
            std::string A_LoopField155 = items155[A_Index155 - 0];
            HTVM_Append(nextWordEndFix, A_LoopField155);
        }
        HTVM_Append(nextWordEndFix, " ");
        std::vector<std::string> items156 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index156 = 0; A_Index156 < items156.size() + 0; A_Index156++) {
            std::string A_LoopField156 = items156[A_Index156 - 0];
            if (Trim(A_LoopField156) == Trim(keyWordEnd_2) && SubStr(Trim(nextWordEndFix[A_Index156 + 1]), 1, StrLen(Trim(keyWordElseIf_2) + " ")) == Trim(keyWordElseIf_2) + " " || Trim(A_LoopField156) == Trim(keyWordEnd_2) && (Trim(nextWordEndFix[A_Index156 + 1]) == Trim(keyWordElse_2) || Trim(nextWordEndFix[A_Index156 + 1]) == Trim(keyWordElse_2 + ":"))) {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField156 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == "lua") {
        std::vector<std::string> items157 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index157 = 0; A_Index157 < items157.size() + 0; A_Index157++) {
            std::string A_LoopField157 = items157[A_Index157 - 0];
            HTVM_Append(nextWordEndFix, A_LoopField157);
        }
        HTVM_Append(nextWordEndFix, " ");
        std::vector<std::string> items158 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index158 = 0; A_Index158 < items158.size() + 0; A_Index158++) {
            std::string A_LoopField158 = items158[A_Index158 - 0];
            if (Trim(A_LoopField158) == "end" && SubStr(Trim(nextWordEndFix[A_Index158 + 1]), 1, StrLen("elseif ")) == "elseif " || Trim(A_LoopField158) == "end" && Trim(nextWordEndFix[A_Index158 + 1]) == "else") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField158 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == "rb") {
        std::vector<std::string> items159 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index159 = 0; A_Index159 < items159.size() + 0; A_Index159++) {
            std::string A_LoopField159 = items159[A_Index159 - 0];
            HTVM_Append(nextWordEndFix, A_LoopField159);
        }
        HTVM_Append(nextWordEndFix, " ");
        std::vector<std::string> items160 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index160 = 0; A_Index160 < items160.size() + 0; A_Index160++) {
            std::string A_LoopField160 = items160[A_Index160 - 0];
            if (Trim(A_LoopField160) == "end" && SubStr(Trim(nextWordEndFix[A_Index160 + 1]), 1, StrLen("elsif ")) == "elsif " || Trim(A_LoopField160) == "end" && Trim(nextWordEndFix[A_Index160 + 1]) == "else") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField160 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    std::vector<std::string> nextWordEndFixRB;
    nextWordEndFixOut = "";
    if (langToConvertTo == "rb") {
        std::vector<std::string> items161 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index161 = 0; A_Index161 < items161.size() + 0; A_Index161++) {
            std::string A_LoopField161 = items161[A_Index161 - 0];
            HTVM_Append(nextWordEndFixRB, A_LoopField161);
        }
        HTVM_Append(nextWordEndFixRB, " ");
        std::vector<std::string> items162 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index162 = 0; A_Index162 < items162.size() + 0; A_Index162++) {
            std::string A_LoopField162 = items162[A_Index162 - 0];
            if (Trim(A_LoopField162) == "end" && SubStr(Trim(nextWordEndFixRB[A_Index162 + 1]), 1, StrLen("rescue ")) == "rescue " || Trim(A_LoopField162) == "end" && Trim(nextWordEndFixRB[A_Index162 + 1]) == "ensure") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField162 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == langFileExtension_2 && useEnd_2 == "on") {
        std::vector<std::string> items163 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index163 = 0; A_Index163 < items163.size() + 0; A_Index163++) {
            std::string A_LoopField163 = items163[A_Index163 - 0];
            HTVM_Append(nextWordEndFixRB, A_LoopField163);
        }
        HTVM_Append(nextWordEndFixRB, " ");
        std::vector<std::string> items164 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index164 = 0; A_Index164 < items164.size() + 0; A_Index164++) {
            std::string A_LoopField164 = items164[A_Index164 - 0];
            if (Trim(A_LoopField164) == Trim(keyWordEnd_2) && SubStr(Trim(nextWordEndFixRB[A_Index164 + 1]), 1, StrLen(Trim(keyWordCatch_2) + " ")) == Trim(keyWordCatch_2) + " " || Trim(A_LoopField164) == Trim(keyWordEnd_2) && Trim(nextWordEndFixRB[A_Index164 + 1]) == Trim(keyWordFinally_2) || Trim(nextWordEndFixRB[A_Index164 + 1]) == Trim(keyWordFinally_2 + ":")) {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField164 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    nextWordEndFixOut = "";
    if (langToConvertTo == "ahk") {
        std::vector<std::string> items165 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index165 = 0; A_Index165 < items165.size() + 0; A_Index165++) {
            std::string A_LoopField165 = items165[A_Index165 - 0];
            if (SubStr(Trim(A_LoopField165), 1, StrLen("Loop, Parse, ")) == "Loop, Parse, ") {
                nextWordEndFixOut += StrReplace(A_LoopField165, "{", Chr(10) + "{" + Chr(10)) + Chr(10);
            } else {
                nextWordEndFixOut += A_LoopField165 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == "go") {
        std::vector<std::string> fixGoManGoIsSoAnnoyingBroooFurure;
        std::vector<std::string> items166 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index166 = 0; A_Index166 < items166.size() + 0; A_Index166++) {
            std::string A_LoopField166 = items166[A_Index166 - 0];
            HTVM_Append(fixGoManGoIsSoAnnoyingBroooFurure, A_LoopField166);
        }
        HTVM_Append(fixGoManGoIsSoAnnoyingBroooFurure, " ");
        int fixGoManGoIsSoAnnoyingBroooSkip = 0;
        int fixGoManGoIsSoAnnoyingBroooCount = 0;
        std::string fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
        std::string fixGoManGoIsSoAnnoyingBrooo = "";
        std::vector<std::string> items167 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index167 = 0; A_Index167 < items167.size() + 0; A_Index167++) {
            std::string A_LoopField167 = items167[A_Index167 - 0];
            if (Trim(A_LoopField167) == "}" && SubStr(Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index167 + 1]), 1, StrLen("else if ")) == "else if ") {
                fixGoManGoIsSoAnnoyingBroooSkip = 1;
                fixGoManGoIsSoAnnoyingBroooCount = 0;
                std::vector<std::string> items168 = LoopParseFunc(fixGoManGoIsSoAnnoyingBroooFurure[A_Index167 + 1]);
                for (size_t A_Index168 = 0; A_Index168 < items168.size() + 0; A_Index168++) {
                    std::string A_LoopField168 = items168[A_Index168 - 0];
                    if (A_LoopField168 == " ") {
                        fixGoManGoIsSoAnnoyingBroooCount++;
                    } else {
                        break;
                    }
                }
                fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
                for (int A_Index169 = 0; A_Index169 < fixGoManGoIsSoAnnoyingBroooCount + 0; A_Index169++) {
                    fixGoManGoIsSoAnnoyingBroooCountSpaceses += " ";
                }
                fixGoManGoIsSoAnnoyingBrooo += fixGoManGoIsSoAnnoyingBroooCountSpaceses + "} " + Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index167 + 1]) + Chr(10);
            } else {
                if (fixGoManGoIsSoAnnoyingBroooSkip == 0) {
                    fixGoManGoIsSoAnnoyingBrooo += A_LoopField167 + Chr(10);
                }
                fixGoManGoIsSoAnnoyingBroooSkip = 0;
            }
        }
        htCode = StringTrimRight(fixGoManGoIsSoAnnoyingBrooo, 1);
    }
    if (langToConvertTo == "cs" || langToConvertTo == "java") {
        htCode = fixCSandJAVAstaticBugForFunc(htCode);
    }
    if (COUNT_programmingBlock_InTheTranspiledLang != 0) {
        for (int A_Index170 = 0; A_Index170 < COUNT_programmingBlock_InTheTranspiledLang + 0; A_Index170++) {
            htCode = StrReplace(htCode, "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(A_Index170 + 1) + "AA", programmingBlock_InTheTranspiledLang[A_Index170]);
        }
    }
    if (langToConvertTo == "cpp") {
        if (COUNT_programmingBlock_CPP != 0) {
            for (int A_Index171 = 0; A_Index171 < COUNT_programmingBlock_CPP + 0; A_Index171++) {
                htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index171 + 1) + "AA", programmingBlock_CPP[A_Index171]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CPP != 0) {
            for (int A_Index172 = 0; A_Index172 < COUNT_programmingBlock_CPP + 0; A_Index172++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index172 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCPP_2 + Chr(10) + programmingBlock_CPP[A_Index172] + Chr(10) + keyWordCodeInTheTranspiledLangEndCPP_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index172 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "py") {
        if (COUNT_programmingBlock_PY != 0) {
            for (int A_Index173 = 0; A_Index173 < COUNT_programmingBlock_PY + 0; A_Index173++) {
                htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index173 + 1) + "AA", programmingBlock_PY[A_Index173]);
            }
        }
    } else {
        if (COUNT_programmingBlock_PY != 0) {
            for (int A_Index174 = 0; A_Index174 < COUNT_programmingBlock_PY + 0; A_Index174++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index174 + 1) + "AA", keyWordCodeInTheTranspiledLangStartPY_2 + Chr(10) + programmingBlock_PY[A_Index174] + Chr(10) + keyWordCodeInTheTranspiledLangEndPY_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index174 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "js") {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index175 = 0; A_Index175 < COUNT_programmingBlock_JS + 0; A_Index175++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index175 + 1) + "AA", programmingBlock_JS[A_Index175]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index176 = 0; A_Index176 < COUNT_programmingBlock_JS + 0; A_Index176++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index176 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJS_2 + Chr(10) + programmingBlock_JS[A_Index176] + Chr(10) + keyWordCodeInTheTranspiledLangEndJS_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index176 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "go") {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index177 = 0; A_Index177 < COUNT_programmingBlock_GO + 0; A_Index177++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index177 + 1) + "AA", programmingBlock_GO[A_Index177]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index178 = 0; A_Index178 < COUNT_programmingBlock_GO + 0; A_Index178++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index178 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGO_2 + Chr(10) + programmingBlock_GO[A_Index178] + Chr(10) + keyWordCodeInTheTranspiledLangEndGO_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index178 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "lua") {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index179 = 0; A_Index179 < COUNT_programmingBlock_LUA + 0; A_Index179++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index179 + 1) + "AA", programmingBlock_LUA[A_Index179]);
            }
        }
    } else {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index180 = 0; A_Index180 < COUNT_programmingBlock_LUA + 0; A_Index180++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index180 + 1) + "AA", keyWordCodeInTheTranspiledLangStartLUA_2 + Chr(10) + programmingBlock_LUA[A_Index180] + Chr(10) + keyWordCodeInTheTranspiledLangEndLUA_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index180 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "cs") {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index181 = 0; A_Index181 < COUNT_programmingBlock_CS + 0; A_Index181++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index181 + 1) + "AA", programmingBlock_CS[A_Index181]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index182 = 0; A_Index182 < COUNT_programmingBlock_CS + 0; A_Index182++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index182 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCS_2 + Chr(10) + programmingBlock_CS[A_Index182] + Chr(10) + keyWordCodeInTheTranspiledLangEndCS_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index182 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "java") {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index183 = 0; A_Index183 < COUNT_programmingBlock_JAVA + 0; A_Index183++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index183 + 1) + "AA", programmingBlock_JAVA[A_Index183]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index184 = 0; A_Index184 < COUNT_programmingBlock_JAVA + 0; A_Index184++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index184 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJAVA_2 + Chr(10) + programmingBlock_JAVA[A_Index184] + Chr(10) + keyWordCodeInTheTranspiledLangEndJAVA_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index184 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "kt") {
        if (COUNT_programmingBlock_KT != 0) {
            for (int A_Index185 = 0; A_Index185 < COUNT_programmingBlock_KT + 0; A_Index185++) {
                htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index185 + 1) + "AA", programmingBlock_KT[A_Index185]);
            }
        }
    } else {
        if (COUNT_programmingBlock_KT != 0) {
            for (int A_Index186 = 0; A_Index186 < COUNT_programmingBlock_KT + 0; A_Index186++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index186 + 1) + "AA", keyWordCodeInTheTranspiledLangStartKT_2 + Chr(10) + programmingBlock_KT[A_Index186] + Chr(10) + keyWordCodeInTheTranspiledLangEndKT_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index186 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "rb") {
        if (COUNT_programmingBlock_RB != 0) {
            for (int A_Index187 = 0; A_Index187 < COUNT_programmingBlock_RB + 0; A_Index187++) {
                htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index187 + 1) + "AA", programmingBlock_RB[A_Index187]);
            }
        }
    } else {
        if (COUNT_programmingBlock_RB != 0) {
            for (int A_Index188 = 0; A_Index188 < COUNT_programmingBlock_RB + 0; A_Index188++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index188 + 1) + "AA", keyWordCodeInTheTranspiledLangStartRB_2 + Chr(10) + programmingBlock_RB[A_Index188] + Chr(10) + keyWordCodeInTheTranspiledLangEndRB_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index188 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "nim") {
        if (COUNT_programmingBlock_NIM != 0) {
            for (int A_Index189 = 0; A_Index189 < COUNT_programmingBlock_NIM + 0; A_Index189++) {
                htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index189 + 1) + "AA", programmingBlock_NIM[A_Index189]);
            }
        }
    } else {
        if (COUNT_programmingBlock_NIM != 0) {
            for (int A_Index190 = 0; A_Index190 < COUNT_programmingBlock_NIM + 0; A_Index190++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index190 + 1) + "AA", keyWordCodeInTheTranspiledLangStartNIM_2 + Chr(10) + programmingBlock_NIM[A_Index190] + Chr(10) + keyWordCodeInTheTranspiledLangEndNIM_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index190 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "ahk") {
        if (COUNT_programmingBlock_AHK != 0) {
            for (int A_Index191 = 0; A_Index191 < COUNT_programmingBlock_AHK + 0; A_Index191++) {
                htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index191 + 1) + "AA", programmingBlock_AHK[A_Index191]);
            }
        }
    } else {
        if (COUNT_programmingBlock_AHK != 0) {
            for (int A_Index192 = 0; A_Index192 < COUNT_programmingBlock_AHK + 0; A_Index192++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index192 + 1) + "AA", keyWordCodeInTheTranspiledLangStartAHK_2 + Chr(10) + programmingBlock_AHK[A_Index192] + Chr(10) + keyWordCodeInTheTranspiledLangEndAHK_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index192 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "swift") {
        if (COUNT_programmingBlock_SWIFT != 0) {
            for (int A_Index193 = 0; A_Index193 < COUNT_programmingBlock_SWIFT + 0; A_Index193++) {
                htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index193 + 1) + "AA", programmingBlock_SWIFT[A_Index193]);
            }
        }
    } else {
        if (COUNT_programmingBlock_SWIFT != 0) {
            for (int A_Index194 = 0; A_Index194 < COUNT_programmingBlock_SWIFT + 0; A_Index194++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index194 + 1) + "AA", keyWordCodeInTheTranspiledLangStartSWIFT_2 + Chr(10) + programmingBlock_SWIFT[A_Index194] + Chr(10) + keyWordCodeInTheTranspiledLangEndSWIFT_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index194 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "dart") {
        if (COUNT_programmingBlock_DART != 0) {
            for (int A_Index195 = 0; A_Index195 < COUNT_programmingBlock_DART + 0; A_Index195++) {
                htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index195 + 1) + "AA", programmingBlock_DART[A_Index195]);
            }
        }
    } else {
        if (COUNT_programmingBlock_DART != 0) {
            for (int A_Index196 = 0; A_Index196 < COUNT_programmingBlock_DART + 0; A_Index196++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index196 + 1) + "AA", keyWordCodeInTheTranspiledLangStartDART_2 + Chr(10) + programmingBlock_DART[A_Index196] + Chr(10) + keyWordCodeInTheTranspiledLangEndDART_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index196 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "ts") {
        if (COUNT_programmingBlock_TS != 0) {
            for (int A_Index197 = 0; A_Index197 < COUNT_programmingBlock_TS + 0; A_Index197++) {
                htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index197 + 1) + "AA", programmingBlock_TS[A_Index197]);
            }
        }
    } else {
        if (COUNT_programmingBlock_TS != 0) {
            for (int A_Index198 = 0; A_Index198 < COUNT_programmingBlock_TS + 0; A_Index198++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index198 + 1) + "AA", keyWordCodeInTheTranspiledLangStartTS_2 + Chr(10) + programmingBlock_TS[A_Index198] + Chr(10) + keyWordCodeInTheTranspiledLangEndTS_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index198 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "groovy") {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (int A_Index199 = 0; A_Index199 < COUNT_programmingBlock_GROOVY + 0; A_Index199++) {
                htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index199 + 1) + "AA", programmingBlock_GROOVY[A_Index199]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (int A_Index200 = 0; A_Index200 < COUNT_programmingBlock_GROOVY + 0; A_Index200++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index200 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGROOVY_2 + Chr(10) + programmingBlock_GROOVY[A_Index200] + Chr(10) + keyWordCodeInTheTranspiledLangEndGROOVY_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index200 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    //;;;;;;;;;;
    if (langToConvertTo == langFileExtension_2) {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (int A_Index201 = 0; A_Index201 < COUNT_programmingBlock_HTVM + 0; A_Index201++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index201 + 1) + "AA", programmingBlock_HTVM[A_Index201]);
            }
        }
    } else {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (int A_Index202 = 0; A_Index202 < COUNT_programmingBlock_HTVM + 0; A_Index202++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index202 + 1) + "AA", Chr(10));
            }
        }
    }
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
    std::vector<std::string> items203 = LoopParseFunc(instructions, "\n", "\r");
    for (size_t A_Index203 = 0; A_Index203 < items203.size() + 0; A_Index203++) {
        std::string A_LoopField203 = items203[A_Index203 - 0];
        if (Trim(A_LoopField203) == "funcEND======================funcEND==============") {
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
                funcLangHolder = StringTrimLeft(A_LoopField203, 5);
                if (Trim(funcLangHolder) == langToConvertTo) {
                    HTVM_Append(allFuncLang, Trim(funcLangHolder));
                    correctLang = 1;
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 2) {
                // name of the func
                funcNameHolder = StringTrimLeft(A_LoopField203, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    HTVM_Append(allFuncNames, Trim(funcNameHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 3) {
                // all libs
                funcLibsHolder = StringTrimLeft(A_LoopField203, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    HTVM_Append(allFuncLibs, Trim(funcLibsHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 4) {
                // func description
                funcDescriptionHolder = StringTrimLeft(A_LoopField203, 12);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    HTVM_Append(allfuncDescription, Trim(funcDescriptionHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum >= 5) {
                // the full func
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    funcFuncHolder += A_LoopField203 + Chr(10);
                }
            }
            //MsgBox, % A_LoopField203
            areWeInAFuncFromInstructionsLineNum++;
        }
        if (Trim(A_LoopField203) == "func======================func==============") {
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
        if (langToConvertTo == "cpp") {
            htCode = htCode + Chr(10) + "    return 0;" + Chr(10) + "}";
            htCode = StrReplace(htCode, "int main(int argc, char* argv[]);", "int main(int argc, char* argv[])");
        }
        if (langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
            htCode = htCode + "\n}\nmain();";
            htCode = StrReplace(htCode, "async function main();", "async function main()");
            htCode = StrReplace(htCode, "function async function main()", "async function main()");
        }
        if (langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
            htCode = htCode + "\n}\nmain();";
            htCode = StrReplace(htCode, "async function main(): Promise<void>;", "async function main(): Promise<void>");
            htCode = StrReplace(htCode, "function async function main(): Promise<void>", "async function main(): Promise<void>");
        }
        if (langToConvertTo == "go") {
            htCode = htCode + "\n}";
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
            htCode = htCode + "\n}";
            htCode = StrReplace(htCode, "fun main(args: Array<String>);", "fun main(args: Array<String>)");
        }
        if (langToConvertTo == "swift") {
            htCode = htCode + "\n}\nmain()";
            htCode = StrReplace(htCode, "func main();", "func main()");
            htCode = StrReplace(htCode, "func main() ->", "func main()");
        }
        if (langToConvertTo == "dart") {
            htCode = htCode + "\n}";
            htCode = StrReplace(htCode, "void main(List<String> arguments);", "void main(List<String> arguments)");
        }
    }
    std::string jsHTMLdownCode = "</script>" + Chr(10) + "</body>" + Chr(10) + "</html>";
    int includeLibsInCppIf = 0;
    std::string allFuncsToPutAtTop = Chr(10);
    std::string allLibsToPutAtTop = "";
    if (!(HTVM_Size(allFuncNames) <= 0)) {
        for (int A_Index204 = 0; A_Index204 < HTVM_Size(allFuncNames) + 0; A_Index204++) {
            if (InStr(htCode, allFuncNames[A_Index204]) + "(") {
                //MsgBox, % allFuncNames[A_Index204]
                allFuncsToPutAtTop += allFuncs[A_Index204] + Chr(10);
                if (Trim(allFuncLibs[A_Index204]) != "null") {
                    allLibsToPutAtTop += allFuncLibs[A_Index204] + "|";
                }
            }
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTop, 1);
        std::string allLibsToPutAtTopTEMP = "";
        std::vector<std::string> items205 = LoopParseFunc(allLibsToPutAtTop, "|");
        for (size_t A_Index205 = 0; A_Index205 < items205.size() + 0; A_Index205++) {
            std::string A_LoopField205 = items205[A_Index205 - 0];
            allLibsToPutAtTopTEMP += A_LoopField205 + Chr(10);
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
                        htCode = allLibsToPutAtTop + Chr(10) + allFuncsToPutAtTop + Chr(10) + htCode;
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
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    HTVM_Append(ospDic, "end");
    int size_ospDic = HTVM_Size(ospDic);
    if (size_ospDic != 0) {
        for (int A_Index206 = 0; A_Index206 < size_ospDic + 0; A_Index206++) {
            HTVM_Pop(ospDic);
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    HTVM_Append(ospDic1, "end");
    int size_ospDic1 = HTVM_Size(ospDic1);
    if (size_ospDic1 != 0) {
        for (int A_Index207 = 0; A_Index207 < size_ospDic1 + 0; A_Index207++) {
            HTVM_Pop(ospDic1);
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    HTVM_Append(ospDic2, "end");
    int size_ospDic2 = HTVM_Size(ospDic2);
    if (size_ospDic2 != 0) {
        for (int A_Index208 = 0; A_Index208 < size_ospDic2 + 0; A_Index208++) {
            HTVM_Pop(ospDic2);
        }
    }
    htCode = StrReplace(htCode, "optanal-HTVM-opt-parmsNOtWorking-theirewIs-a-bug-Iusfbudfbuoeshfuisbav=-fwaegs-awedsf-dd-sfgc ", "");
    for (int A_Index209 = 0; A_Index209 < theIdNumOfThe34 + 0; A_Index209++) {
        if (theIdNumOfThe34 == A_Index209 + 1) {
            if (langToConvertTo == langFileExtension_2) {
                if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index209 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index209 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                } else {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index209 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index209 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                }
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index209 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index209 + 1], keyWordEscpaeChar, "\\") + Chr(34));
            }
        } else {
            if (langToConvertTo == langFileExtension_2) {
                if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index209 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index209 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2));
                } else {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index209 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index209 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2));
                }
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index209 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index209 + 1], keyWordEscpaeChar, "\\"));
            }
        }
    }
    if (langToConvertTo == langFileExtension_2) {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, keyWordEscpaeChar_2 + Chr(34));
    } else {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, Chr(92) + Chr(34));
    }
    htCode = StrReplace(htCode, "std::string(" + Chr(34) + Chr(34) + ";),", "std::string(" + Chr(34) + Chr(34) + "),");
    std::string jsHTMLupCode = "<!doctype html>" + Chr(10) + "<html lang=" + Chr(34) + "en" + Chr(34) + ">" + Chr(10) + "    <head>\n        <meta charset=" + Chr(34) + "UTF-8" + Chr(34) + " />" + Chr(10) + "        <meta name=" + Chr(34) + "viewport" + Chr(34) + " content=" + Chr(34) + "width=device-width, initial-scale=1.0" + Chr(34) + " />" + Chr(10) + "        <title>HTVM</title>" + Chr(10) + "        <style>" + Chr(10) + "            body {" + Chr(10) + "                background-color: #202020;" + Chr(10) + "                font-family:" + Chr(10) + "                    " + Chr(34) + "Open Sans" + Chr(34) + "," + Chr(10) + "                    -apple-system," + Chr(10) + "                    BlinkMacSystemFont," + Chr(10) + "                    " + Chr(34) + "Segoe UI" + Chr(34) + "," + Chr(10) + "                    Roboto," + Chr(10) + "                    Oxygen-Sans," + Chr(10) + "                    Ubuntu," + Chr(10) + "                    Cantarell," + Chr(10) + "                    " + Chr(34) + "Helvetica Neue" + Chr(34) + "," + Chr(10) + "                    Helvetica," + Chr(10) + "                    Arial," + Chr(10) + "                    sans-serif;" + Chr(10) + "            }" + Chr(10) + "        </style>" + Chr(10) + allLibsToPutAtTop + Chr(10) + "</head>" + Chr(10) + "    <body>" + Chr(10) + "<script>";
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
        if (langToConvertTo == langFileExtension_2) {
            if (SubStr(htCode, 1, 1) == Chr(10)) {
                htCode = StringTrimLeft(htCode, 1);
            }
        }
    }
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
    std::vector<std::string> items210 = LoopParseFunc(str0);
    for (size_t A_Index210 = 0; A_Index210 < items210.size() + 0; A_Index210++) {
        std::string A_LoopField210 = items210[A_Index210 - 0];
        str00 = Trim(A_LoopField210);
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
        std::vector<std::string> items211 = LoopParseFunc(allArgs, "\n", "\r");
        for (size_t A_Index211 = 0; A_Index211 < items211.size() + 0; A_Index211++) {
            std::string A_LoopField211 = items211[A_Index211 - 0];
            if (A_Index211 == 0) {
                numOfParams++;
                argCODE = FileRead(Trim(A_LoopField211));
                argCODEfile = Trim(A_LoopField211);
            }
            else if (A_Index211 == 1) {
                numOfParams++;
                argHTVMinstr = Trim(A_LoopField211);
            }
            else if (A_Index211 == 2) {
                numOfParams++;
                argLangTo = Trim(A_LoopField211);
            } else {
                numOfParams++;
                HTVM_Append(argHTVMinstrMORE, Trim(A_LoopField211));
            }
        }
        //print("===============123431234===========start=====")
        for (int A_Index212 = 0; A_Index212 < HTVM_Size(argHTVMinstrMORE) + 0; A_Index212++) {
            //print(argHTVMinstrMORE[A_Index212])
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