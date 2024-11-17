#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Define a map to store dynamic variables
    std::unordered_map<std::string, std::string> variables;

// Forward declare OneIndexedArray template
template <typename T>
class OneIndexedArray;

#define OneIndexedArray_DEFINED

// Helper function to set the internal array's size as a string
template <typename T>
void setInternalArraySize(T& element, size_t size) {
    element = static_cast<T>(size);
}

// Specialization for std::string
template <>
void setInternalArraySize<std::string>(std::string& element, size_t size) {
    element = std::to_string(size);
}

// One-indexed dynamic array class
template <typename T>
class OneIndexedArray {
private:
    std::vector<T> internalArray;

public:
    OneIndexedArray() {
        internalArray.push_back(T{}); // Placeholder for element count
    }

    void add(const T& newElement) {
        internalArray.push_back(newElement);
        setInternalArraySize(internalArray[0], internalArray.size() - 1);
    }

    void setArray(const std::vector<T>& newArray) {
        internalArray.resize(newArray.size() + 1);
        std::copy(newArray.begin(), newArray.end(), internalArray.begin() + 1);
        setInternalArraySize(internalArray[0], newArray.size());
    }

    T& operator[](size_t index) {
        if (index >= internalArray.size()) {
            internalArray.resize(index + 1);
            setInternalArraySize(internalArray[0], internalArray.size() - 1);
        }
        return internalArray[index];
    }

    const T& operator[](size_t index) const {
        if (index >= internalArray.size()) {
            throw std::out_of_range("Index out of range");
        }
        return internalArray[index];
    }

    size_t size() const {
        return static_cast<size_t>(internalArray.size() - 1);
    }
    void pop_back() {
        if (size() > 0) {
            internalArray.pop_back(); // Remove last element
            setInternalArraySize(internalArray[0], internalArray.size() - 1); // Update size
        }
    }
};

// Function to split text into words based on a delimiter
std::vector<std::string> split(const std::string& text, const std::string& delimiter) {
    std::vector<std::string> words;
    std::istringstream stream(text);
    std::string word;
    while (std::getline(stream, word, delimiter[0])) { // assuming single character delimiter
        words.push_back(word);
    }
    return words;
}

// Function to split text into a OneIndexedArray
OneIndexedArray<std::string> arrSplit(const std::string& text, const std::string& delimiter) {
    OneIndexedArray<std::string> array;
    std::vector<std::string> words = split(text, delimiter);
    array.setArray(words);
    return array;
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

// Function to find the position of needle in haystack (std::string overload)
int InStr(const std::string& haystack, const std::string& needle) {
    size_t pos = haystack.find(needle);
    return (pos != std::string::npos) ? static_cast<int>(pos) + 1 : 0;
}

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

// Print function that converts all types to string if needed
template <typename T>
void print(const T& value) {
    if constexpr (std::is_same_v<T, std::string>) {
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
    } 
    #ifdef OneIndexedArray_DEFINED
    else if constexpr (std::is_base_of_v<OneIndexedArray<std::string>, T>) {
        for (size_t i = 1; i <= value.size(); ++i) {
            std::cout << value[i] << std::endl;
        }
    } else if constexpr (std::is_base_of_v<OneIndexedArray<int>, T>) {
        for (size_t i = 1; i <= value.size(); ++i) {
            std::cout << std::to_string(value[i]) << std::endl;
        }
    } else if constexpr (std::is_base_of_v<OneIndexedArray<float>, T>) {
        for (size_t i = 1; i <= value.size(); ++i) {
            std::cout << std::to_string(value[i]) << std::endl;
        }
    } else if constexpr (std::is_base_of_v<OneIndexedArray<double>, T>) {
        for (size_t i = 1; i <= value.size(); ++i) {
            std::cout << std::to_string(value[i]) << std::endl;
        }
    }
    #endif
    else {
        std::cout << "Unsupported type" << std::endl;
    }
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

// Function that computes the logarithm with base 10
double Log(double value) {
    return std::log10(value);
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

// Platform-specific handling for command-line arguments
#ifdef _WIN32
    #define ARGC __argc
    #define ARGV __argv
#else
    // On Linux/macOS, we need to declare these as extern variables.
    extern char **environ; // Ensure the declaration of `environ`
    int ARGC;
    char** ARGV;

    __attribute__((constructor)) void init_args(int argc, char* argv[], char* envp[]) {
        ARGC = argc;
        ARGV = argv;
    }
#endif

// Function to get command-line parameters
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

// Store the start time as a global variable
std::chrono::time_point<std::chrono::steady_clock> programStartTime = std::chrono::steady_clock::now();

// Function to get built-in variables
std::string BuildInVars(const std::string& varName) {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&currentTime);

    std::ostringstream oss;

    if (varName == "A_TickCount") {
        // Calculate milliseconds since program start
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - programStartTime).count();
        if (duration > std::numeric_limits<int>::max()) {
            // Handle overflow case
            return "Value too large";
        } else {
            return std::to_string(static_cast<int>(duration));
        }
    } else if (varName == "A_Now") {
        oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    } else if (varName == "A_YYYY") {
        oss << std::put_time(localTime, "%Y");
    } else if (varName == "A_MM") {
        oss << std::put_time(localTime, "%m");
    } else if (varName == "A_DD") {
        oss << std::put_time(localTime, "%d");
    } else if (varName == "A_MMMM") {
        oss << std::put_time(localTime, "%B");
    } else if (varName == "A_MMM") {
        oss << std::put_time(localTime, "%b");
    } else if (varName == "A_DDDD") {
        oss << std::put_time(localTime, "%A");
    } else if (varName == "A_DDD") {
        oss << std::put_time(localTime, "%a");
    } else if (varName == "A_Hour") {
        oss << std::put_time(localTime, "%H");
    } else if (varName == "A_Min") {
        oss << std::put_time(localTime, "%M");
    } else if (varName == "A_Sec") {
        oss << std::put_time(localTime, "%S");
    } else if (varName == "A_Space") {
        return " ";
    } else if (varName == "A_Tab") {
        return "\t";
    } else {
        return "";
    }
    return oss.str();
}

// Function to perform regex replacement
std::string RegExReplace(const std::string& inputStr, const std::string& regexPattern, const std::string& replacement) {
    std::regex re(regexPattern, std::regex_constants::ECMAScript | std::regex_constants::multiline);
    return std::regex_replace(inputStr, re, replacement);
}

// Function to perform regex matching and return the match position
int RegExMatch(const std::string& haystack, const std::string& needleRegEx, std::string* outputVar = nullptr, int startingPos = 0) {
    if (haystack.empty() || needleRegEx.empty()) {
        return 0;
    }

    std::regex re(needleRegEx);
    std::smatch match;

    if (std::regex_search(haystack.begin() + startingPos, haystack.end(), match, re)) {
        if (outputVar != nullptr) {
            *outputVar = match.str(0);
        }
        return match.position(0) + 1; // To make it 1-based index
    }

    return 0;
}

void ExitApp() {
    std::exit(0);
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
std::string SortLikeAHK(const std::string& input, const std::string& options) {
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

std::string addBackShlashes(std::string str123)
{
str123 = StrReplace ( str123 , Chr ( 46 ) , Chr ( 92 ) + Chr ( 46 ) ) ;
str123 = StrReplace ( str123 , Chr ( 42 ) , Chr ( 92 ) + Chr ( 42 ) ) ;
str123 = StrReplace ( str123 , Chr ( 43 ) , Chr ( 92 ) + Chr ( 43 ) ) ;
str123 = StrReplace ( str123 , Chr ( 63 ) , Chr ( 92 ) + Chr ( 63 ) ) ;
str123 = StrReplace ( str123 , Chr ( 94 ) , Chr ( 92 ) + Chr ( 94 ) ) ;
str123 = StrReplace ( str123 , Chr ( 36 ) , Chr ( 92 ) + Chr ( 36 ) ) ;
str123 = StrReplace ( str123 , Chr ( 91 ) , Chr ( 92 ) + Chr ( 91 ) ) ;
str123 = StrReplace ( str123 , Chr ( 93 ) , Chr ( 92 ) + Chr ( 93 ) ) ;
str123 = StrReplace ( str123 , Chr ( 40 ) , Chr ( 92 ) + Chr ( 40 ) ) ;
str123 = StrReplace ( str123 , Chr ( 41 ) , Chr ( 92 ) + Chr ( 41 ) ) ;
str123 = StrReplace ( str123 , Chr ( 123 ) , Chr ( 92 ) + Chr ( 123 ) ) ;
str123 = StrReplace ( str123 , Chr ( 125 ) , Chr ( 92 ) + Chr ( 125 ) ) ;
str123 = StrReplace ( str123 , Chr ( 124 ) , Chr ( 92 ) + Chr ( 124 ) ) ;
str123 = StrReplace ( str123 , Chr ( 92 ) , Chr ( 92 ) + Chr ( 92 ) ) ;
str123 = StrReplace ( str123 , Chr ( 45 ) , Chr ( 92 ) + Chr ( 45 ) ) ;
str123 = StrReplace ( str123 , Chr ( 47 ) , Chr ( 92 ) + Chr ( 47 ) ) ;
return str123;
}
int main(int argc, char* argv[])
{
print(std::string("Syntax Highlighting and Code Completion Regeneration"));
std::string keyWordsCommands;
std::string fileExtention;
std::string code;
std::string keyWordINT;
std::string keyWordSTR;
std::string keyWordFLOAT;
std::string instructions;
std::string filePathOfCode;
std::string langToTranspileTo;
std::string out_KeyWordsCommands;
std::string outTrimCode;
std::string htCode;
std::string str1;
std::string str2;
std::string str3;
std::string str4;
std::string str5;
std::string str6;
std::string str7;
std::string str8;
std::string str9;
std::string str10;
std::string outVarOperator;
int lineDone;
int areWeInAFuncFromInstructions;
int areWeInAFuncFromInstructionsLineNum;
std::string keyWordIF;
std::string keyWordElseIf;
std::string keyWordWhileLoop;
std::string keyWordForLoop;
std::string keyWordElse;
std::string keyWordBOOL;
std::string keyWordINT8;
std::string keyWordINT16;
std::string keyWordINT32;
std::string keyWordINT64;
std::string keyWordLoop;
std::string keyWordLoopInfinite;
std::string keyWordLoopParse;
std::string keyWordBreak;
std::string keyWordContinue;
std::string keyWordFunc;
std::string keyWordAwait;
std::string keyWordConcatenationAssignmentOperator;
std::string keyWordVariablesAssignmentOperator;
std::string keyWordAdditionAssignmentOperator;
std::string keyWordSubtractionAssignmentOperator;
std::string keyWordMultiplicationAssignmentOperator;
std::string keyWordDivisionAssignmentOperator;
std::string keyWordAdditionOperator;
std::string keyWordConcatenationOperator;
std::string keyWordEqualOperator;
std::string keyWordNotOperator;
std::string keyWordGreaterThanOperator;
std::string keyWordLessThanOperator;
std::string keyWordGreaterThanOrEqualToOperator;
std::string keyWordLessThanOrEqualToOperator;
std::string keyWordOrOperator;
std::string keyWordAndOperator;
std::string keyWordNotEqualToOperator;
std::string keyWordTrue;
std::string keyWordFalse;
std::string keyWordSwitch;
std::string keyWordSwitchCase;
std::string keyWordSwitchDefault;
std::string keyWordThrow;
std::string keyWordErrorMsg;
std::string keyWordTry;
std::string keyWordCatch;
std::string keyWordFinally;
std::string keyWordArrayAppend;
std::string keyWordArrayPop;
std::string keyWordArraySize;
std::string keyWordArrayInsert;
std::string keyWordArrayRemove;
std::string keyWordArrayIndexOf;
std::string keyWordArrayDefinition;
std::string keyWordArrayOfIntegersDefinition;
std::string keyWordArrayOfStringsDefinition;
std::string keyWordArrayOfFloatingPointNumbersDefinition;
std::string keyWordArrayOfBooleansDefinition;
std::string keyWordJavaScriptVar;
std::string keyWordJavaScriptLet;
std::string keyWordJavaScriptConst;
std::string keyWordReturnStatement;
std::string keyWordEnd;
std::string keyWordGlobal;
std::string keyWordComment;
std::string keyWordCommentOpenMultiLine;
std::string keyWordCommentCloseMultiLine;
std::string keyWordEscpaeChar;
std::string AHKlikeLoopsIndexedAt;
std::string keyWordAIndex;
std::string keyWordALoopField;
std::string keyWordMainLabel;
std::string useFuncKeyWord;
std::string useCurlyBraces;
std::string useEnd;
std::string useSemicolon;
std::string useParentheses;
std::string usePythonicColonSyntax;
std::string useTypes;
std::string forLoopLang;
std::string useJavaScriptInAfullHTMLfile;
std::string useInJavaScriptAlwaysUseVar;
std::string useJavaScriptAmainFuncDef;
std::string theSemicolon;
std::string theColon;
std::string theCppVarForErrors = "jhku-dfsds-ds-d-ffdsf-sdfsfdsedsf";
std::string theJSvarDeclaredVarsBugFix = "|";
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; code starts here realy ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; code starts here realy ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; code starts here realy ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; code starts here realy ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; code starts here realy ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; code starts here realy ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; code starts here realy ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; code starts here realy ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string filePathOfinstructions;
std::string params = GetParams ( ) ;
if (params == "") 
{
print(std::string("No params!!!!"));
ExitApp();
}
std::vector<std::string> items1 = LoopParseFunc(params, "\n", "\r");
for (size_t A_Index1 = 1; A_Index1 < items1.size() + 1; A_Index1++)
{
std::string A_LoopField1 = items1[A_Index1 - 1];
if (A_Index1 == 1) 
{
print(A_LoopField1);
filePathOfinstructions = A_LoopField1;
instructions = FileRead(filePathOfinstructions);
code = FileRead(filePathOfinstructions);
}
}
std::string ALoopField;
std::vector<std::string> items2 = LoopParseFunc(instructions, "\n", "\r");
for (size_t A_Index2 = 1; A_Index2 < items2.size() + 1; A_Index2++)
{
std::string A_LoopField2 = items2[A_Index2 - 1];
ALoopField = addBackShlashes ( A_LoopField2 ) ;
if (A_Index2 == 1) 
{
langToTranspileTo = Trim ( ALoopField ) ;
}
if (A_Index2 == 2) 
{
fileExtention = Trim ( ALoopField ) ;
}
if (A_Index2 == 3) 
{
keyWordsCommands = Trim ( ALoopField ) ;
}
if (A_Index2 == 4) 
{
keyWordINT = Trim ( ALoopField ) ;
}
if (A_Index2 == 5) 
{
keyWordSTR = Trim ( ALoopField ) ;
}
if (A_Index2 == 6) 
{
keyWordBOOL = Trim ( ALoopField ) ;
}
if (A_Index2 == 7) 
{
keyWordFLOAT = Trim ( ALoopField ) ;
}
if (A_Index2 == 8) 
{
keyWordINT8 = Trim ( ALoopField ) ;
}
if (A_Index2 == 9) 
{
keyWordINT16 = Trim ( ALoopField ) ;
}
if (A_Index2 == 10) 
{
keyWordINT32 = Trim ( ALoopField ) ;
}
if (A_Index2 == 11) 
{
keyWordINT64 = Trim ( ALoopField ) ;
}
if (A_Index2 == 12) 
{
keyWordIF = Trim ( ALoopField ) ;
}
if (A_Index2 == 13) 
{
keyWordElseIf = Trim ( ALoopField ) ;
}
if (A_Index2 == 14) 
{
keyWordElse = Trim ( ALoopField ) ;
}
if (A_Index2 == 15) 
{
keyWordWhileLoop = Trim ( ALoopField ) ;
}
if (A_Index2 == 16) 
{
keyWordForLoop = Trim ( ALoopField ) ;
}
if (A_Index2 == 17) 
{
keyWordLoopInfinite = Trim ( ALoopField ) ;
}
if (A_Index2 == 18) 
{
keyWordLoop = Trim ( ALoopField ) ;
}
if (A_Index2 == 19) 
{
keyWordLoopParse = Trim ( ALoopField ) ;
}
if (A_Index2 == 20) 
{
keyWordContinue = Trim ( ALoopField ) ;
}
if (A_Index2 == 21) 
{
keyWordBreak = Trim ( ALoopField ) ;
}
if (A_Index2 == 22) 
{
keyWordFunc = Trim ( ALoopField ) ;
}
if (A_Index2 == 23) 
{
keyWordAwait = Trim ( ALoopField ) ;
}
if (A_Index2 == 24) 
{
keyWordVariablesAssignmentOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 25) 
{
keyWordConcatenationAssignmentOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 26) 
{
keyWordAdditionAssignmentOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 27) 
{
keyWordSubtractionAssignmentOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 28) 
{
keyWordMultiplicationAssignmentOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 29) 
{
keyWordDivisionAssignmentOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 30) 
{
keyWordAdditionOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 31) 
{
keyWordConcatenationOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 32) 
{
keyWordEqualOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 33) 
{
keyWordNotOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 34) 
{
keyWordGreaterThanOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 35) 
{
keyWordLessThanOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 36) 
{
keyWordGreaterThanOrEqualToOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 37) 
{
keyWordLessThanOrEqualToOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 38) 
{
keyWordOrOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 39) 
{
keyWordAndOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 40) 
{
keyWordNotEqualToOperator = Trim ( ALoopField ) ;
}
if (A_Index2 == 41) 
{
keyWordTrue = Trim ( ALoopField ) ;
}
if (A_Index2 == 42) 
{
keyWordFalse = Trim ( ALoopField ) ;
}
if (A_Index2 == 43) 
{
keyWordSwitch = Trim ( ALoopField ) ;
}
if (A_Index2 == 44) 
{
keyWordSwitchCase = Trim ( ALoopField ) ;
}
if (A_Index2 == 45) 
{
keyWordSwitchDefault = Trim ( ALoopField ) ;
}
if (A_Index2 == 46) 
{
keyWordThrow = Trim ( ALoopField ) ;
}
if (A_Index2 == 47) 
{
keyWordErrorMsg = Trim ( ALoopField ) ;
}
if (A_Index2 == 48) 
{
keyWordTry = Trim ( ALoopField ) ;
}
if (A_Index2 == 49) 
{
keyWordCatch = Trim ( ALoopField ) ;
}
if (A_Index2 == 50) 
{
keyWordFinally = Trim ( ALoopField ) ;
}
if (A_Index2 == 51) 
{
keyWordArrayAppend = Trim ( ALoopField ) ;
}
if (A_Index2 == 52) 
{
keyWordArrayPop = Trim ( ALoopField ) ;
}
if (A_Index2 == 53) 
{
keyWordArraySize = Trim ( ALoopField ) ;
}
if (A_Index2 == 54) 
{
keyWordArrayInsert = Trim ( ALoopField ) ;
}
if (A_Index2 == 55) 
{
keyWordArrayRemove = Trim ( ALoopField ) ;
}
if (A_Index2 == 56) 
{
keyWordArrayIndexOf = Trim ( ALoopField ) ;
}
if (A_Index2 == 57) 
{
keyWordArrayDefinition = Trim ( ALoopField ) ;
}
if (A_Index2 == 58) 
{
keyWordArrayOfIntegersDefinition = Trim ( ALoopField ) ;
}
if (A_Index2 == 59) 
{
keyWordArrayOfStringsDefinition = Trim ( ALoopField ) ;
}
if (A_Index2 == 60) 
{
keyWordArrayOfFloatingPointNumbersDefinition = Trim ( ALoopField ) ;
}
if (A_Index2 == 61) 
{
keyWordArrayOfBooleansDefinition = Trim ( ALoopField ) ;
}
if (A_Index2 == 62) 
{
keyWordJavaScriptVar = Trim ( ALoopField ) ;
}
if (A_Index2 == 63) 
{
keyWordJavaScriptLet = Trim ( ALoopField ) ;
}
if (A_Index2 == 64) 
{
keyWordJavaScriptConst = Trim ( ALoopField ) ;
}
if (A_Index2 == 65) 
{
keyWordReturnStatement = Trim ( ALoopField ) ;
}
if (A_Index2 == 66) 
{
keyWordEnd = Trim ( ALoopField ) ;
}
if (A_Index2 == 67) 
{
keyWordGlobal = Trim ( ALoopField ) ;
}
if (A_Index2 == 68) 
{
keyWordComment = Trim ( ALoopField ) ;
}
if (A_Index2 == 69) 
{
keyWordCommentOpenMultiLine = Trim ( ALoopField ) ;
}
if (A_Index2 == 70) 
{
keyWordCommentCloseMultiLine = Trim ( ALoopField ) ;
}
if (A_Index2 == 71) 
{
keyWordEscpaeChar = Trim ( ALoopField ) ;
}
if (A_Index2 == 72) 
{
AHKlikeLoopsIndexedAt = Trim ( ALoopField ) ;
}
if (A_Index2 == 73) 
{
keyWordAIndex = Trim ( ALoopField ) ;
}
if (A_Index2 == 74) 
{
keyWordALoopField = Trim ( ALoopField ) ;
}
if (A_Index2 == 75) 
{
keyWordMainLabel = Trim ( ALoopField ) ;
}
if (A_Index2 == 76) 
{
useFuncKeyWord = Trim ( ALoopField ) ;
}
if (A_Index2 == 77) 
{
useCurlyBraces = Trim ( ALoopField ) ;
}
if (A_Index2 == 78) 
{
useEnd = Trim ( ALoopField ) ;
}
if (A_Index2 == 79) 
{
useSemicolon = Trim ( ALoopField ) ;
}
if (A_Index2 == 80) 
{
useParentheses = Trim ( ALoopField ) ;
}
if (A_Index2 == 81) 
{
usePythonicColonSyntax = Trim ( ALoopField ) ;
}
if (A_Index2 == 82) 
{
forLoopLang = Trim ( ALoopField ) ;
}
if (A_Index2 == 83) 
{
useInJavaScriptAlwaysUseVar = Trim ( ALoopField ) ;
}
if (A_Index2 == 84) 
{
useJavaScriptInAfullHTMLfile = Trim ( ALoopField ) ;
}
if (A_Index2 == 85) 
{
useJavaScriptAmainFuncDef = Trim ( ALoopField ) ;
}
}
areWeInAFuncFromInstructions = 0;
areWeInAFuncFromInstructionsLineNum = 0;
std::string funcLangHolder;
std::string funcNameHolder;
std::string funcLibsHolder;
std::string funcFuncHolder;
std::string funcDescriptionHolder;
OneIndexedArray<std::string> allFuncLang;
OneIndexedArray<std::string> allFuncNames;
OneIndexedArray<std::string> allFuncLibs;
OneIndexedArray<std::string> allFuncs;
OneIndexedArray<std::string> allfuncDescription;
int correctLang = 0;
std::vector<std::string> items3 = LoopParseFunc(instructions, "\n", "\r");
for (size_t A_Index3 = 1; A_Index3 < items3.size() + 1; A_Index3++)
{
std::string A_LoopField3 = items3[A_Index3 - 1];
if (Trim (A_LoopField3) == "funcEND======================funcEND==============") 
{
areWeInAFuncFromInstructions = 0;
areWeInAFuncFromInstructionsLineNum = 0;
if (correctLang == 1 && InStr (code , Trim (funcNameHolder))) 
{
//MsgBox, % funcFuncHolder
allFuncs.add(funcFuncHolder);
}
correctLang = 0;
funcFuncHolder = "";
}
if (areWeInAFuncFromInstructions == 1) 
{
if (areWeInAFuncFromInstructionsLineNum == 1) 
{
// name of the func
funcLangHolder = StringTrimLeft(A_LoopField3, 5);
if (Trim (funcLangHolder) == "cpp" || Trim (funcLangHolder) == "py" || Trim (funcLangHolder) == "js") 
{
allFuncLang.add(Trim(funcLangHolder));
correctLang = 1;
}
}
if (areWeInAFuncFromInstructionsLineNum == 2) 
{
// name of the func
funcNameHolder = StringTrimLeft(A_LoopField3, 5);
if (correctLang == 1 && InStr (code , Trim (funcNameHolder))) 
{
allFuncNames.add(Trim(funcNameHolder));
}
}
if (areWeInAFuncFromInstructionsLineNum == 3) 
{
// all libs
funcLibsHolder = StringTrimLeft(A_LoopField3, 5);
if (correctLang == 1 && InStr (code , Trim (funcNameHolder))) 
{
allFuncLibs.add(Trim(funcLibsHolder));
}
}
if (areWeInAFuncFromInstructionsLineNum == 4) 
{
// func description
funcDescriptionHolder = StringTrimLeft(A_LoopField3, 12);
if (correctLang == 1 && InStr (code , Trim (funcNameHolder))) 
{
allfuncDescription.add(Trim(funcDescriptionHolder));
}
}
if (areWeInAFuncFromInstructionsLineNum >= 5) 
{
// the full func
if (correctLang == 1 && InStr (code , Trim (funcNameHolder))) 
{
funcFuncHolder += A_LoopField3 + "\n";
}
}
//MsgBox, % A_LoopField3
areWeInAFuncFromInstructionsLineNum++;
}
if (Trim (A_LoopField3) == "func======================func==============") 
{
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
std::string upCode = "<!doctype html>\n<html lang=" + Chr ( 34 ) + "en" + Chr ( 34 ) + ">\n  <head>\n    <meta charset=" + Chr ( 34 ) + "UTF-8" + Chr ( 34 ) + " />\n    <meta name=" + Chr ( 34 ) + "viewport" + Chr ( 34 ) + " content=" + Chr ( 34 ) + "width=device-width, initial-scale=1.0" + Chr ( 34 ) + " />\n    <title>HTVM IDE</title>\n    <style>\n      body {\n        background-color: #202020;\n        font-family:\n          " + Chr ( 34 ) + "Open Sans" + Chr ( 34 ) + ",\n          -apple-system,\n          BlinkMacSystemFont,\n          " + Chr ( 34 ) + "Segoe UI" + Chr ( 34 ) + ",\n          Roboto,\n          Oxygen-Sans,\n          Ubuntu,\n          Cantarell,\n          " + Chr ( 34 ) + "Helvetica Neue" + Chr ( 34 ) + ",\n          Helvetica,\n          Arial,\n          sans-serif;\n      }\n    </style>\n    <script src=" + Chr ( 34 ) + "https://cdn.jsdelivr.net/npm/sweetalert2@11" + Chr ( 34 ) + "></script>\n\n    <!-- Include Ace Editor CDN -->\n    <script src=" + Chr ( 34 ) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.32.2/ace.js" + Chr ( 34 ) + " integrity=" + Chr ( 34 ) + "sha512-JLIRlxWh96sND3uUgI2RVHZJpgkWHg3+xoUY8XkgTPKpqRaqdk7zD/ck/XHXFSMW84o6GrP67dlqN3b98NB/yA==" + Chr ( 34 ) + " crossorigin=" + Chr ( 34 ) + "anonymous" + Chr ( 34 ) + " referrerpolicy=" + Chr ( 34 ) + "no-referrer" + Chr ( 34 ) + "></script>\n    <script src=" + Chr ( 34 ) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.4.12/ext-language_tools.js" + Chr ( 34 ) + " crossorigin=" + Chr ( 34 ) + "anonymous" + Chr ( 34 ) + " referrerpolicy=" + Chr ( 34 ) + "no-referrer" + Chr ( 34 ) + "></script>\n  </head>\n  <body>\n    <script>\n      // JavaScript equivalent code with variables\n\n      function changeFaviconAtTheBeginning(faviconUrl) {\n        // Create a new favicon link element\n        const newFavicon = document.createElement(" + Chr ( 34 ) + "link" + Chr ( 34 ) + ");\n        newFavicon.rel = " + Chr ( 34 ) + "icon" + Chr ( 34 ) + ";\n        newFavicon.href = faviconUrl;\n\n        // Get the current favicon element (if exists)\n        const existingFavicon = document.querySelector('link[rel=" + Chr ( 34 ) + "icon" + Chr ( 34 ) + "]');\n\n        // Replace the current favicon with the new one\n        if (existingFavicon) {\n          // If a favicon exists, replace it\n          document.head.removeChild(existingFavicon); // Remove the existing favicon\n        }\n\n        // Append the new favicon to the head\n        document.head.appendChild(newFavicon);\n      }\n\n      // Call the function with the desired favicon URL\n      changeFaviconAtTheBeginning(" + Chr ( 34 ) + "https://i.ibb.co/Jpty1B8/305182938-1a0efe63-726e-49ca-a13c-d0ed627f2ea7.png" + Chr ( 34 ) + ");\n\n      function showCustomMessageBox(options, title, text, value, timeout) {\n        return new Promise((resolve) => {\n          // Define default options for the message box\n          let defaultOptions = {\n            title: title || " + Chr ( 34 ) + "" + Chr ( 34 ) + ", // Default title is empty\n            text: text || " + Chr ( 34 ) + "Press OK to continue." + Chr ( 34 ) + ", // Default text if not provided\n            showCancelButton: false, // Default is to not show Cancel button\n            showDenyButton: false, // Default is to not show Deny button\n            confirmButtonText: " + Chr ( 34 ) + "OK" + Chr ( 34 ) + ", // Default text for OK button\n            focusConfirm: true, // Default focus on OK button\n          };\n\n          let numOriginal = value;\n\n          let num = numOriginal;\n\n          let done1 = 0;\n\n          let done2 = 0;\n\n          let done3 = 0;\n\n          let AIndex = 0;\n\n          for (AIndex = 1; AIndex <= 1; AIndex++) {\n            // this is about if you add always on top in a msgbox it will be removed in js cuz its kinda useless...\n            // becouse if you like adding always on top in ahk in js we dont realy do it so yeah\n            if (num >= 262144) {\n              num = num - 262144;\n              numOriginal = numOriginal - 262144;\n            }\n\n            if (num >= 256 && num < 500) {\n              num = num - 256;\n\n              done3 = 256;\n            }\n\n            if (num >= 512) {\n              num = num - 512;\n\n              done3 = 512;\n            }\n\n            if (num == 0) {\n              done1 = 0;\n\n              break;\n            }\n\n            if (num <= 6) {\n              done1 = num;\n\n              break;\n            }\n\n            if (num >= 64 && num < 64 * 2) {\n              done2 = 64;\n\n              if (num == 64) {\n                done1 = 0;\n\n                break;\n              } else {\n                done1 = num - 64;\n\n                break;\n              }\n            }\n\n            if (num >= 48 && num < 63) {\n              done2 = 48;\n\n              if (num == 48) {\n                done1 = 0;\n\n                break;\n              } else {\n                done1 = num - 48;\n\n                break;\n              }\n            }\n\n            if (num >= 32 && num < 47) {\n              done2 = 32;\n\n              if (num == 32) {\n                done1 = 0;\n\n                break;\n              } else {\n                done1 = num - 32;\n\n                break;\n              }\n            }\n\n            if (num >= 16 && num < 30) {\n              done2 = 16;\n\n              if (num == 16) {\n                done1 = 0;\n\n                break;\n              } else {\n                done1 = num - 16;\n\n                break;\n              }\n            }\n          }\n\n          let doneAdded = done1 + done2 + done3;\n\n          if (doneAdded !== numOriginal) {\n            // displayMessage(" + Chr ( 34 ) + "The calc was wrong!" + Chr ( 34 ) + ");\n          } else {\n            // displayMessage(" + Chr ( 34 ) + "num was: " + Chr ( 34 ) + " + numOriginal + " + Chr ( 34 ) + "" + Chr ( 92 ) + "ndone1: " + Chr ( 34 ) + " + done1 + " + Chr ( 34 ) + "" + Chr ( 92 ) + "ndone2: " + Chr ( 34 ) + " + done2 + " + Chr ( 34 ) + "" + Chr ( 92 ) + "ndone3: " + Chr ( 34 ) + " + done3);\n          }\n\n          // Parse the value to determine the options for the message box\n          if (done1 === 1) defaultOptions.showCancelButton = true; // OK/Cancel in ahk but here it will show Ok/Cancel wiat its same haha\n\n          // not gonna work if you can make it work i will appreciate\n          //   if (done1 === 2) {\n          //     defaultOptions.showCancelButton = true; // Abort/Retry/Ignore\n          //     defaultOptions.showDenyButton = true;\n          //   }\n          if (done1 === 3) {\n            defaultOptions.showCancelButton = true; // Yes/No/Cancel in ahk but here it will show Ok/No/Cancel\n            defaultOptions.showDenyButton = true;\n          }\n          if (done1 === 4) {\n            // defaultOptions.showCancelButton = true;\n            defaultOptions.showDenyButton = true; // Yes/No in ahk but here it will show Ok/No\n          }\n          if (done1 === 5) {\n            defaultOptions.showCancelButton = true; // Retry/Cancel in ahk but here it will show Ok/Cancel tip you can write in the Msgbox press ok to retry\n          }\n          // not gonna work if you can make it work i will appreciate\n          //   if (done1 === 6) {\n          //     defaultOptions.showCancelButton = true; // Cancel/Try Again/Continue\n          //     defaultOptions.showDenyButton = true;\n          //   }\n\n          if (done2 === 16) defaultOptions.icon = " + Chr ( 34 ) + "error" + Chr ( 34 ) + "; // Icon Hand (stop/error)\n          if (done2 === 32) defaultOptions.icon = " + Chr ( 34 ) + "question" + Chr ( 34 ) + "; // Icon Question\n          if (done2 === 48) defaultOptions.icon = " + Chr ( 34 ) + "warning" + Chr ( 34 ) + "; // Icon Exclamation\n          if (done2 === 64) defaultOptions.icon = " + Chr ( 34 ) + "info" + Chr ( 34 ) + "; // Icon Asterisk (info)\n\n          if (done3 === 256) defaultOptions.focusDeny = true; // Makes the 3rd button the default\n          if (done3 === 512) defaultOptions.focusCancel = true; // Makes the 2nd button the default\n\n          // Set timeout if provided\n          if (timeout) {\n            defaultOptions.timer = timeout * 1000; // Convert timeout to milliseconds\n          }\n\n          // Merge default options with provided options\n          Object.assign(defaultOptions, options);\n\n          // Display the message box with the constructed options\n          Swal.fire(defaultOptions).then((result) => {\n            if (result.isConfirmed) {\n              resolve(" + Chr ( 34 ) + "OK" + Chr ( 34 ) + ");\n            } else if (result.isDenied) {\n              resolve(" + Chr ( 34 ) + "No" + Chr ( 34 ) + ");\n            } else {\n              resolve(" + Chr ( 34 ) + "Cancel" + Chr ( 34 ) + ");\n            }\n          });\n        });\n      }\n\n      var lastKeyPressed = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n\n      function trackLastKeyPressed() {\n        document.addEventListener(" + Chr ( 34 ) + "keydown" + Chr ( 34 ) + ", function (event) {\n          lastKeyPressed = event.key;\n          // console.log(lastKeyPressed);\n        });\n      }\n\n      function getLastKeyPressed() {\n        return lastKeyPressed;\n      }\n\n      // Call the trackLastKeyPressed function to start tracking key presses\n      trackLastKeyPressed();\n\n      let lastInputTime = Date.now(); // Initialize with current timestamp\n      let startTimestamp = Date.now(); // Initialize with current timestamp\n\n      // Event listener to track user activity\n      function resetIdleTimer() {\n        lastInputTime = Date.now(); // Update last input time\n      }\n\n      document.addEventListener(" + Chr ( 34 ) + "mousemove" + Chr ( 34 ) + ", resetIdleTimer);\n      document.addEventListener(" + Chr ( 34 ) + "keypress" + Chr ( 34 ) + ", resetIdleTimer);\n\n      // Function to calculate time since last input event\n      function A_TimeIdle() {\n        return Date.now() - lastInputTime; // Calculate time difference\n      }\n\n      // Function to calculate tick count in milliseconds\n      function A_TickCount() {\n        return Date.now() - startTimestamp;\n      }\n\n      function GuiControl(action, id, param1, param2, param3, param4) {\n        const element = document.getElementById(id);\n        if (element) {\n          // Handle DOM elements\n          if (action === " + Chr ( 34 ) + "move" + Chr ( 34 ) + ") {\n            // Set position and size\n            element.style.left = param1 + " + Chr ( 34 ) + "px" + Chr ( 34 ) + ";\n            element.style.top = param2 + " + Chr ( 34 ) + "px" + Chr ( 34 ) + ";\n            element.style.width = param3 + " + Chr ( 34 ) + "px" + Chr ( 34 ) + ";\n            element.style.height = param4 + " + Chr ( 34 ) + "px" + Chr ( 34 ) + ";\n          } else if (action === " + Chr ( 34 ) + "focus" + Chr ( 34 ) + " && (element instanceof HTMLInputElement || element instanceof HTMLElement)) {\n            // Focus on the element\n            element.focus();\n          } else if (action === " + Chr ( 34 ) + "text" + Chr ( 34 ) + ") {\n            // Set new text content\n            element.textContent = param1;\n          } else if (action === " + Chr ( 34 ) + "hide" + Chr ( 34 ) + ") {\n            // Hide the element\n            element.style.display = " + Chr ( 34 ) + "none" + Chr ( 34 ) + ";\n          } else if (action === " + Chr ( 34 ) + "show" + Chr ( 34 ) + ") {\n            // Show the element\n            element.style.display = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          } else if (action === " + Chr ( 34 ) + "enable" + Chr ( 34 ) + ") {\n            // Enable the element\n            element.disabled = false;\n          } else if (action === " + Chr ( 34 ) + "disable" + Chr ( 34 ) + ") {\n            // Disable the element\n            element.disabled = true;\n          } else if (action === " + Chr ( 34 ) + "font" + Chr ( 34 ) + ") {\n            // Set font size\n            element.style.fontSize = param1 + " + Chr ( 34 ) + "px" + Chr ( 34 ) + ";\n          } else if (action === " + Chr ( 34 ) + "destroy" + Chr ( 34 ) + ") {\n            // Remove the element from the DOM\n            element.parentNode.removeChild(element);\n          } else if (action === " + Chr ( 34 ) + "color" + Chr ( 34 ) + ") {\n            // Set color\n            element.style.color = param1;\n          } else if (action === " + Chr ( 34 ) + "picture" + Chr ( 34 ) + ") {\n            // Change the image source\n            if (element instanceof HTMLImageElement) {\n              element.src = param1;\n            } else {\n              console.error(" + Chr ( 34 ) + "Element is not an <img> tag, cannot change picture." + Chr ( 34 ) + ");\n            }\n          } else if (action === " + Chr ( 34 ) + "textide" + Chr ( 34 ) + ") {\n            // Set value for Ace editor\n            var editor = ace.edit(id); // Access the Ace editor instance using its ID\n            if (editor && param1) {\n              editor.session.setValue(param1);\n            } else {\n              console.error(" + Chr ( 34 ) + "Element is not an Ace editor or parameter is missing." + Chr ( 34 ) + ");\n            }\n          }\n        } else {\n          // Handle canvas or non-existing element\n          if (action === " + Chr ( 34 ) + "move" + Chr ( 34 ) + ") {\n            // Update position and size of the rectangle\n            updateRectangle(id, param1, param2, param3, param4);\n            redrawCanvas(); // Redraw the canvas with updated rectangles\n          } else if (action === " + Chr ( 34 ) + "color" + Chr ( 34 ) + ") {\n            // Update color of the rectangle\n            updateRectangleColor(id, param1);\n            redrawCanvas(); // Redraw the canvas with updated rectangles\n          }\n        }\n      }\n\n      function BuildInVars(varName) {\n        switch (varName) {\n          case " + Chr ( 34 ) + "A_ScreenWidth" + Chr ( 34 ) + ":\n            // Return screen width\n            return window.innerWidth;\n          case " + Chr ( 34 ) + "A_LastKey" + Chr ( 34 ) + ":\n            // Return screen width\n            return getLastKeyPressed();\n          case " + Chr ( 34 ) + "A_ScreenHeight" + Chr ( 34 ) + ":\n            // Return screen height\n            return window.innerHeight;\n          case " + Chr ( 34 ) + "A_TimeIdle" + Chr ( 34 ) + ":\n            // Return time idle\n            return A_TimeIdle();\n          case " + Chr ( 34 ) + "A_TickCount" + Chr ( 34 ) + ":\n            // Return tick count in milliseconds\n            return A_TickCount();\n          case " + Chr ( 34 ) + "A_Now" + Chr ( 34 ) + ":\n            // Return current local timestamp\n            return new Date().toLocaleString();\n          case " + Chr ( 34 ) + "A_YYYY" + Chr ( 34 ) + ":\n            // Return current year\n            return new Date().getFullYear();\n          case " + Chr ( 34 ) + "A_MM" + Chr ( 34 ) + ":\n            // Return current month\n            return (new Date().getMonth() + 1).toString().padStart(2, " + Chr ( 34 ) + "0" + Chr ( 34 ) + ");\n          case " + Chr ( 34 ) + "A_DD" + Chr ( 34 ) + ":\n            // Return current day\n            return new Date().getDate().toString().padStart(2, " + Chr ( 34 ) + "0" + Chr ( 34 ) + ");\n          case " + Chr ( 34 ) + "A_MMMM" + Chr ( 34 ) + ":\n            // Return full month name\n            return new Date().toLocaleDateString(undefined, { month: " + Chr ( 34 ) + "long" + Chr ( 34 ) + " });\n          case " + Chr ( 34 ) + "A_MMM" + Chr ( 34 ) + ":\n            // Return short month name\n            return new Date().toLocaleDateString(undefined, { month: " + Chr ( 34 ) + "short" + Chr ( 34 ) + " });\n          case " + Chr ( 34 ) + "A_DDDD" + Chr ( 34 ) + ":\n            // Return full day name\n            return new Date().toLocaleDateString(undefined, { weekday: " + Chr ( 34 ) + "long" + Chr ( 34 ) + " });\n          case " + Chr ( 34 ) + "A_DDD" + Chr ( 34 ) + ":\n            // Return short day name\n            return new Date().toLocaleDateString(undefined, { weekday: " + Chr ( 34 ) + "short" + Chr ( 34 ) + " });\n          case " + Chr ( 34 ) + "A_Hour" + Chr ( 34 ) + ":\n            // Return current hour\n            return new Date().getHours().toString().padStart(2, " + Chr ( 34 ) + "0" + Chr ( 34 ) + ");\n          case " + Chr ( 34 ) + "A_Min" + Chr ( 34 ) + ":\n            // Return current minute\n            return new Date().getMinutes().toString().padStart(2, " + Chr ( 34 ) + "0" + Chr ( 34 ) + ");\n          case " + Chr ( 34 ) + "A_Sec" + Chr ( 34 ) + ":\n            // Return current second\n            return new Date().getSeconds().toString().padStart(2, " + Chr ( 34 ) + "0" + Chr ( 34 ) + ");\n          case " + Chr ( 34 ) + "A_Space" + Chr ( 34 ) + ":\n            // Return space character\n            return " + Chr ( 34 ) + " " + Chr ( 34 ) + ";\n          case " + Chr ( 34 ) + "A_Tab" + Chr ( 34 ) + ":\n            // Return tab character\n            return " + Chr ( 34 ) + "" + Chr ( 92 ) + "t" + Chr ( 34 ) + ";\n\n          default:\n            // Handle unknown variable names\n            return null;\n        }\n      }\n\n      function Chr(number) {\n        // Check if the number is null\n        if (number === null) {\n          // Return an empty string\n          return " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n        }\n\n        // Check if the number is within the valid range\n        if (number >= 0 && number <= 0x10ffff) {\n          // Convert the number to a character using String.fromCharCode\n          return String.fromCharCode(number);\n        } else {\n          // Return an empty string for invalid numbers\n          return " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n        }\n      }\n\n      // Define the custom " + Chr ( 34 ) + "ht" + Chr ( 34 ) + " language for Ace Editor with AHK rules\n      ace.define(" + Chr ( 34 ) + "ace/mode/ht" + Chr ( 34 ) + ", [" + Chr ( 34 ) + "require" + Chr ( 34 ) + ", " + Chr ( 34 ) + "exports" + Chr ( 34 ) + ", " + Chr ( 34 ) + "module" + Chr ( 34 ) + ", " + Chr ( 34 ) + "ace/lib/oop" + Chr ( 34 ) + ", " + Chr ( 34 ) + "ace/mode/text" + Chr ( 34 ) + ", " + Chr ( 34 ) + "ace/mode/text_highlight_rules" + Chr ( 34 ) + "], function (require, exports, module) {\n        var oop = require(" + Chr ( 34 ) + "ace/lib/oop" + Chr ( 34 ) + ");\n        var TextMode = require(" + Chr ( 34 ) + "ace/mode/text" + Chr ( 34 ) + ").Mode;\n        var TextHighlightRules = require(" + Chr ( 34 ) + "ace/mode/text_highlight_rules" + Chr ( 34 ) + ").TextHighlightRules;\n\n        var HTHighlightRules = function () {\n          this.$rules = {\n            start: [";
std::string keyWordsCommandsFolrmated;
std::vector<std::string> items4 = LoopParseFunc(keyWordsCommands, "|");
for (size_t A_Index4 = 1; A_Index4 < items4.size() + 1; A_Index4++)
{
std::string A_LoopField4 = items4[A_Index4 - 1];
std::vector<std::string> items5 = LoopParseFunc(A_LoopField4, ",");
for (size_t A_Index5 = 1; A_Index5 < items5.size() + 1; A_Index5++)
{
std::string A_LoopField5 = items5[A_Index5 - 1];
if (A_Index5 == 1) 
{
keyWordsCommandsFolrmated += A_LoopField5 + "|";
}
}
}
keyWordsCommandsFolrmated = StringTrimRight(keyWordsCommandsFolrmated, 1);
std::string keywords = keyWordIF + "|" + keyWordElseIf + "|" + keyWordElse + "|def obj|prop|crew|alliance|method|" + keyWordWhileLoop + "|" + keyWordForLoop + "|" + keyWordLoopInfinite + "|" + keyWordLoop + "|" + keyWordLoopParse + "|" + keyWordContinue + "|" + keyWordBreak + "|" + keyWordFunc + "|" + keyWordAwait + "|" + keyWordSwitch + "|" + keyWordSwitchCase + "|" + keyWordThrow + "|" + keyWordTry + "|" + keyWordCatch + "|" + keyWordFinally + "|" + keyWordJavaScriptVar + "|" + keyWordJavaScriptLet + "|" + keyWordJavaScriptConst + "|" + keyWordReturnStatement + "|" + keyWordEnd;
std::string functionsForHighlighting;
for (int A_Index6 = 1; A_Index6<= INT ( allFuncNames[0] ) ; ++A_Index6)
{
functionsForHighlighting += allFuncNames[A_Index6] + "|";
}
functionsForHighlighting += keyWordErrorMsg;
std::string keyWordArrayMethods = keyWordArrayAppend + "|" + keyWordArrayPop + "|" + keyWordArraySize + "|" + keyWordArrayInsert + "|" + keyWordArrayRemove + "|" + keyWordArrayIndexOf;
keyWordArrayMethods = StrReplace ( keyWordArrayMethods , "." , "" ) ;
std::string keyWordTypes;
keyWordTypes = keyWordINT + "|" + keyWordSTR + "|void|" + keyWordBOOL + "|" + keyWordFLOAT + "|" + keyWordINT8 + "|" + keyWordINT16 + "|" + keyWordINT32 + "|" + keyWordINT64 + "|" + keyWordArrayDefinition + "|" + keyWordArrayOfIntegersDefinition + "|" + keyWordArrayOfStringsDefinition + "|" + keyWordArrayOfFloatingPointNumbersDefinition + "|" + keyWordArrayOfBooleansDefinition;
std::string autoCompleteUp = "[";
std::string autoCompleteALLTemp = keywords + "|" + keyWordsCommandsFolrmated + "|" + functionsForHighlighting + "|" + keyWordALoopField + "|" + keyWordAIndex + "|" + keyWordArrayMethods + "|" + keyWordTypes + "|" + keyWordGlobal + "|this";
std::string autoCompleteALL;
std::vector<std::string> items7 = LoopParseFunc(autoCompleteALLTemp, "|");
for (size_t A_Index7 = 1; A_Index7 < items7.size() + 1; A_Index7++)
{
std::string A_LoopField7 = items7[A_Index7 - 1];
autoCompleteALL += "{ name: " + Chr ( 34 ) + Trim ( A_LoopField7 ) + Chr ( 34 ) + " }, ";
}
autoCompleteALL = StringTrimRight(autoCompleteALL, 2);
std::string autoCompleteDown = "]";
std::string autoComplete;
autoComplete = autoCompleteUp + autoCompleteALL + autoCompleteDown;
autoComplete = StrReplace ( autoComplete , Chr ( 92 ) , "" ) ;
std::string downCode = " oop.inherits(HTHighlightRules, TextHighlightRules);\n\n        var HTMode = function () {\n          this.HighlightRules = HTHighlightRules;\n        };\n        oop.inherits(HTMode, TextMode);\n\n        exports.Mode = HTMode;\n      });\n\n      function AddIDE(parent, xPos, yPos, w, h, id, font = 18, langName = " + Chr ( 34 ) + "autohotkey" + Chr ( 34 ) + ", onChangeFunc, initialText = " + Chr ( 34 ) + "" + Chr ( 34 ) + ") {\n        var langTools = ace.require(" + Chr ( 34 ) + "ace/ext/language_tools" + Chr ( 34 ) + ");\n\n        let Completer = {\n          getCompletions: function (editor, session, pos, prefix, callback) {\n            if (prefix.startsWith(" + Chr ( 34 ) + "p" + Chr ( 34 ) + ")) {\n              // Continue executing if the prefix starts with " + Chr ( 34 ) + "p" + Chr ( 34 ) + "\n            } else {\n              // Return early if the prefix does not start with " + Chr ( 34 ) + "p" + Chr ( 34 ) + " and its length is not greater than 1\n              if (prefix.length <= 1) {\n                callback(null, []); // Return an empty array of completions\n                return;\n              }\n            }\n\n            let prefixLower = prefix.toLowerCase();\n            let filteredTables = hth.filter(function (table) {\n              return table.name.toLowerCase().startsWith(prefixLower);\n            });\n            // filteredTables.sort(function(a, b) {\n            //     return a.name.length - b.name.length;\n            // });\n            let limitedTables = filteredTables; //.slice(-10);\n\n            callback(\n              null,\n              limitedTables.map(function (table) {\n                return {\n                  caption: table.name,\n                  value: table.name,\n                };\n              }),\n            );\n          },\n        };\n        // Combined keywords for " + Chr ( 34 ) + "ht" + Chr ( 34 ) + " and AHK\n        let hth = " + autoComplete + ";\n\n        // Create a new div element for the editor\n        var editorDiv = document.createElement(" + Chr ( 34 ) + "div" + Chr ( 34 ) + ");\n        editorDiv.id = id;\n        editorDiv.style.position = " + Chr ( 34 ) + "absolute" + Chr ( 34 ) + ";\n        editorDiv.style.left = xPos + " + Chr ( 34 ) + "px" + Chr ( 34 ) + ";\n        editorDiv.style.top = yPos + " + Chr ( 34 ) + "px" + Chr ( 34 ) + ";\n        editorDiv.style.width = w + " + Chr ( 34 ) + "px" + Chr ( 34 ) + ";\n        editorDiv.style.height = h + " + Chr ( 34 ) + "px" + Chr ( 34 ) + ";\n        editorDiv.style.fontSize = font + " + Chr ( 34 ) + "px" + Chr ( 34 ) + ";\n\n        // Append the editor div to the parent\n        parent.appendChild(editorDiv);\n\n        // Create a new editor instance inside the div\n        var editor = ace.edit(id);\n        editor.setTheme(" + Chr ( 34 ) + "ace/theme/monokai" + Chr ( 34 ) + ");\n        editor.session.setMode(" + Chr ( 34 ) + "ace/mode/" + Chr ( 34 ) + " + " + Chr ( 34 ) + "ht" + Chr ( 34 ) + ");\n        // editor.setOptions({\n        //   enableBasicAutocompletion: true,\n        //   enableLiveAutocompletion: true,\n        //   behavioursEnabled: false, // Disable auto-pairing of characters\n        // });\n\n        editor.setOptions({\n          enableBasicAutocompletion: false,\n          enableSnippets: false,\n          enableLiveAutocompletion: true,\n          behavioursEnabled: false,\n          showPrintMargin: false,\n        });\n\n        langTools.setCompleters([]);\n        langTools.addCompleter(Completer);\n\n        // Set initial text if provided\n        if (initialText) {\n          editor.setValue(initialText, -1); // -1 to move cursor to the beginning\n        }\n\n        // Track Vim mode status\n        var isVimMode = false;\n\n        // Hotkey to toggle Vim mode on/off (Ctrl + Alt + Shift + V)\n        editor.commands.addCommand({\n          name: " + Chr ( 34 ) + "toggleVimMode" + Chr ( 34 ) + ",\n          bindKey: { win: " + Chr ( 34 ) + "Ctrl-Alt-Shift-V" + Chr ( 34 ) + ", mac: " + Chr ( 34 ) + "Command-Alt-Shift-V" + Chr ( 34 ) + " },\n          exec: function () {\n            if (isVimMode) {\n              editor.setKeyboardHandler(null); // Disable Vim (back to default)\n              isVimMode = false;\n              console.log(" + Chr ( 34 ) + "Vim mode disabled" + Chr ( 34 ) + ");\n            } else {\n              editor.setKeyboardHandler(" + Chr ( 34 ) + "ace/keyboard/vim" + Chr ( 34 ) + "); // Enable Vim\n              isVimMode = true;\n              console.log(" + Chr ( 34 ) + "Vim mode enabled" + Chr ( 34 ) + ");\n            }\n          },\n        });\n\n        // Apply CSS styles for the editor\n\n        var css = " + Chr ( 96 ) + "\n                      body {\n                        font-family: " + Chr ( 34 ) + "Segoe UI" + Chr ( 34 ) + ", Tahoma, Geneva, Verdana, sans-serif;\n                        background-color: #1a1818;\n                        color: #ffffff;\n                        display: flex;\n                        flex-direction: column;\n                        align-items: center;\n                        height: 100vh;\n                        margin: 0;\n                      }\n\n                      .controls {\n                        display: flex;\n                        justify-content: center;\n                        gap: 1rem;\n                        margin: 1rem;\n                        padding: 1rem;\n                      }\n\n                      button {\n                        padding: 0.7rem;\n                        font-size: 1.2em;\n                        cursor: pointer;\n                        background-color: #bababa;\n                        color: #000000;\n                        border: none;\n                        border-radius: 0.2rem;\n                        transition: background-color 0.3s;\n                      }\n\n                      button:hover {\n                        background-color: #27ae60;\n                      }\n\n                      #${id} {\n                        width: ${w}px;\n                        height: ${h}px;\n                        font-size: 1em;\n                        border-radius: 0.3rem;\n                      }\n\n                      #result {\n                        margin-top: 1rem;\n                        font-size: 1.2em;\n                        color: #999c9a;\n                        font-weight: bold;\n                        text-align: center;\n                      }\n\n                      .ace-monokai .ace_marker-layer .ace_active-line {\n                        background-color: #103010 !important;\n                      }\n\n                      .ace-monokai {\n                        background-color: #121212 !important;\n                        color: #f8f8f2;\n                      }\n\n                      .ace-monokai .ace_gutter {\n                        background: #204020 !important;\n                        color: #cbcdc3 !important;\n                      }\n\n                      .ace-monokai .ace_gutter-active-line {\n                        background-color: transparent !important;\n                      }\n\n                      .ace-monokai .ace_entity.ace_name.ace_tag,\n                      .ace-monokai .ace_keyword,\n                      .ace-monokai .ace_meta.ace_tag,\n                      .ace-monokai .ace_storage {\n                        color: #40a0e0 !important;\n                      }\n\n                      .ace-monokai .ace_entity.ace_name.ace_function,\n                      .ace-monokai .ace_entity.ace_other,\n                      .ace-monokai .ace_entity.ace_other.ace_attribute-name,\n                      .ace-monokai .ace_variable {\n                        color: #ff80df !important;\n                      }\n\n                      .ace-monokai .ace_comment {\n                        color: #40d080 !important;\n                        font-weight: line-through !important;\n                      }\n\n                      .ace-monokai .ace_commentOpen_Close {\n                        color: #40d080 !important;\n                        font-weight: line-through !important;\n                      }\n\n                      .ace-monokai .ace_variables {\n                        color: #ffffff !important;\n                      }\n\n                      .ace-monokai .ace_functions {\n                        color: #80dfff !important;\n                      }\n\n                    .ace-monokai .ace_keywords {\n                color: #8080e0 !important; /* Customize color as needed */\n                font-weight: bold !important;\n            }\n                      .ace-monokai .ace_braces_Open {\n                        color: #FFFFff !important;\n                      }\n\n                      .ace-monokai .ace_braces_Close {\n                        color: #FFFFff !important;\n                      }\n\n                      .ace-monokai .ace_arrayMethods {\n                        color: #FAB820 !important;\n                      }\n\n                      .ace-monokai .ace_BuildInFunc {\n                        color: #ff80df !important;\n                      }\n\n                      .ace-monokai .ace_command {\n                        color: #40a0e0 !important;\n                        font-weight: bold !important;\n                      }\n\n                      .ace-monokai .ace_static_types {\n                        color: #569cd6 !important;\n                        font-weight: bold !important;\n                      }\n\n                      .ace-monokai .ace_string {\n                        color: #ffa0a0 !important;\n                        font-weight: lighter !important;\n                      }\n\n                      .ace-monokai .ace_operators {\n                        color: #00ffff !important;\n                        font-weight: lighter !important;\n                      }\n\n\n                      .ace-monokai .ace_trueANDfalse {\n                        color: #00ffff !important;\n                        font-weight: lighter !important;\n                      }\n\n                      .ace-monokai .ace_escape-char {\n                        color: #ff8000 !important;\n                        font-weight: bold !important;\n                      }\n\n                      .ace-monokai .ace_punctuation,\n                      .ace-monokai .ace_punctuation.ace _tag {\n                        color: #ffa0a0 !important;\n                      }\n\n                      *::-webkit-scrollbar {\n                        width: 1em;\n                      }\n\n                      *::-webkit-scrollbar-track {\n                        box-shadow: inset 0 0 6px rgba(0, 0, 0, 0.3);\n                      }\n\n                      *::-webkit-scrollbar-thumb {\n                        background-color: darkgrey;\n                        outline: 1px solid slategrey;\n                      }\n                    " + Chr ( 96 ) + ";\n\n        var style = document.createElement(" + Chr ( 34 ) + "style" + Chr ( 34 ) + ");\n        style.type = " + Chr ( 34 ) + "text/css" + Chr ( 34 ) + ";\n        if (style.styleSheet) {\n          style.styleSheet.cssText = css;\n        } else {\n          style.appendChild(document.createTextNode(css));\n        }\n        document.head.appendChild(style);\n\n        // Bind change event listener to the editor\n        editor.getSession().on(" + Chr ( 34 ) + "change" + Chr ( 34 ) + ", function () {\n          var code = editor.getValue();\n          if (typeof onChangeFunc === " + Chr ( 34 ) + "function" + Chr ( 34 ) + ") {\n            onChangeFunc(code);\n          }\n        });\n      }\n\n      // Helper function to set the internal array's size as a string\n      function setInternalArraySize(element, size) {\n        if (typeof element === " + Chr ( 34 ) + "string" + Chr ( 34 ) + ") {\n          return size.toString();\n        }\n        return size;\n      }\n\n      // Convert string to int\n      function INT(str) {\n        return str;\n      }\n\n      // Convert various types to string\n      function STR(value) {\n        return value;\n      }\n\n      // Exponential\n      function Exp(num) {\n        if (num === null || isNaN(num)) return null;\n        return Math.exp(num);\n      }\n\n      // Base-10 logarithm\n      function Log(num) {\n        if (num === null || isNaN(num)) return null;\n        return Math.log10(num);\n      }\n\n      function Chr(number) {\n        // Check if the number is null\n        if (number === null) {\n          // Return an empty string\n          return " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n        }\n\n        // Check if the number is within the valid range\n        if (number >= 0 && number <= 0x10ffff) {\n          // Convert the number to a character using String.fromCharCode\n          return String.fromCharCode(number);\n        } else {\n          // Return an empty string for invalid numbers\n          return " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n        }\n      }\n\n      // InStr\n      function InStr(Haystack, Needle, CaseSensitive = true, StartingPos = 1, Occurrence = 1) {\n        if (Haystack === null || Needle === null) return false;\n\n        // Adjust starting position if less than 1\n        StartingPos = Math.max(StartingPos, 1);\n\n        // Case-sensitive search by default\n        if (!CaseSensitive) {\n          Haystack = Haystack.toLowerCase();\n          Needle = Needle.toLowerCase();\n        }\n\n        let pos = -1;\n        let count = 0;\n        for (let i = StartingPos - 1; i < Haystack.length; i++) {\n          if (Haystack.substring(i, i + Needle.length) === Needle) {\n            count++;\n            if (count === Occurrence) {\n              pos = i + 1;\n              break;\n            }\n          }\n        }\n\n        return pos > 0; // Return true if the substring is found, false otherwise\n      }\n\n      // RegExMatch\n      function RegExMatch(Haystack, NeedleRegEx, OutputVar, StartingPos) {\n        if (Haystack === null || NeedleRegEx === null) return null;\n\n        const regex = new RegExp(NeedleRegEx);\n        let match;\n\n        if (typeof Haystack === " + Chr ( 34 ) + "string" + Chr ( 34 ) + ") {\n          match = Haystack.match(regex);\n        }\n\n        if (match) {\n          if (OutputVar) {\n            OutputVar.push(match[0]);\n          }\n          return match.index + 1;\n        } else {\n          return 0;\n        }\n      }\n\n      // StrLen\n      function StrLen(str) {\n        if (typeof str !== " + Chr ( 34 ) + "string" + Chr ( 34 ) + ") {\n          console.error(" + Chr ( 34 ) + "Invalid input: expected a string but received:" + Chr ( 34 ) + ", str);\n          return 0; // Return 0 or handle as needed\n        }\n        return str.length;\n      }\n\n      function SubStr(str, startPos, length) {\n        // If str is null or undefined, return an empty string\n        if (str === null || str === undefined) {\n          return " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n        }\n\n        // If length is not provided or is blank, default to " + Chr ( 34 ) + "all characters" + Chr ( 34 ) + "\n        if (length === undefined || length === " + Chr ( 34 ) + "" + Chr ( 34 ) + ") {\n          length = str.length - startPos + 1;\n        }\n\n        // If startPos is less than 1, adjust it to start from the end of the string\n        if (startPos < 1) {\n          startPos = str.length + startPos;\n        }\n\n        // Extract the substring based on startPos and length\n        return str.substr(startPos - 1, length);\n      }\n\n      function Trim(inputString) {\n        // Check if inputString is null or undefined\n        if (inputString == null) {\n          return " + Chr ( 34 ) + "" + Chr ( 34 ) + "; // Return an empty string if inputString is null or undefined\n        }\n        return inputString.replace(/^" + Chr ( 92 ) + "s+|" + Chr ( 92 ) + "s+$/g, " + Chr ( 34 ) + "" + Chr ( 34 ) + "); // Removes leading and trailing whitespace\n      }\n\n      async function ParseInt(num) {\n        if (num === null) {\n          return null;\n        }\n\n        num = num.trim();\n        num++;\n        num--;\n\n        return num;\n      }\n\n      function StrReplace(originalString, find, replaceWith) {\n        // Check if originalString is a string\n        if (typeof originalString !== " + Chr ( 34 ) + "string" + Chr ( 34 ) + ") {\n          return originalString; // Return originalString as is\n        }\n\n        // Escape special characters in the 'find' string to be used literally\n        const escapedFind = find.replace(/[.*+?^${}()|[" + Chr ( 92 ) + "]" + Chr ( 92 ) + "" + Chr ( 92 ) + "]/g, " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "$&" + Chr ( 34 ) + ");\n\n        // Use replace method to replace all occurrences of 'find' with 'replaceWith'\n        return originalString.replace(new RegExp(escapedFind, " + Chr ( 34 ) + "g" + Chr ( 34 ) + "), replaceWith);\n      }\n\n      // Custom Mod function\n      function Mod(dividend, divisor) {\n        return dividend % divisor;\n      }\n\n      // Function to trim specified number of characters from the left side of a string\n      function StringTrimLeft(input, numChars) {\n        if (typeof input === " + Chr ( 34 ) + "string" + Chr ( 34 ) + " && typeof numChars === " + Chr ( 34 ) + "number" + Chr ( 34 ) + " && numChars >= 0) {\n          return input.length > numChars ? input.substring(numChars) : " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n        } else {\n          console.error(" + Chr ( 34 ) + "Invalid input provided." + Chr ( 34 ) + ");\n          return input; // Return original input if trimming is not possible\n        }\n      }\n\n      // Function to trim specified number of characters from the right side of a string\n      function StringTrimRight(input, numChars) {\n        if (typeof input === " + Chr ( 34 ) + "string" + Chr ( 34 ) + " && typeof numChars === " + Chr ( 34 ) + "number" + Chr ( 34 ) + " && numChars >= 0) {\n          return input.length > numChars ? input.substring(0, input.length - numChars) : " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n        } else {\n          console.error(" + Chr ( 34 ) + "Invalid input provided." + Chr ( 34 ) + ");\n          return input; // Return original input if trimming is not possible\n        }\n      }\n\n      function StrLower(string) {\n        if (typeof string !== " + Chr ( 34 ) + "string" + Chr ( 34 ) + ") {\n          console.error(" + Chr ( 34 ) + "Invalid input: expected a string but received:" + Chr ( 34 ) + ", string);\n          return " + Chr ( 34 ) + "" + Chr ( 34 ) + "; // Return an empty string or handle as needed\n        }\n        return string.toLowerCase();\n      }\n\n      function StrSplit(inputStr, delimiter, num) {\n        // Check if inputStr is a valid string\n        if (typeof inputStr !== " + Chr ( 34 ) + "string" + Chr ( 34 ) + ") {\n          return " + Chr ( 34 ) + "" + Chr ( 34 ) + "; // Return empty string for invalid input\n        }\n\n        // Split the input string based on the delimiter\n        const parts = inputStr.split(delimiter);\n\n        // Return the part specified by the num parameter (1-based index)\n        if (num > 0 && num <= parts.length) {\n          return parts[num - 1]; // Return the specified part (0-based index)\n        } else {\n          return " + Chr ( 34 ) + "" + Chr ( 34 ) + "; // Return an empty string if num is out of range\n        }\n      }\n\n      // Function to simulate AutoHotkey's RegExReplace in JavaScript\n      function RegExReplace(inputStr, regexPattern, replacement) {\n        // Create a regular expression object using the provided pattern\n        const regex = new RegExp(regexPattern, " + Chr ( 34 ) + "g" + Chr ( 34 ) + "); // 'g' flag for global match\n\n        // Use the replace() method to perform the regex replacement\n        const resultStr = inputStr.replace(regex, replacement);\n\n        // Return the modified string\n        return resultStr;\n      }\n\n      // Function to escape special characters for regex\n      function escapeRegex(str) {\n        if (typeof str !== " + Chr ( 34 ) + "string" + Chr ( 34 ) + ") {\n          console.error(" + Chr ( 34 ) + "Invalid input for escapeRegex: expected a string but received:" + Chr ( 34 ) + ", str);\n          return " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n        }\n        return str.replace(/[-[" + Chr ( 92 ) + "]{}()*+?.," + Chr ( 92 ) + "" + Chr ( 92 ) + "^$|#" + Chr ( 92 ) + "s]/g, " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "$&" + Chr ( 34 ) + ");\n      }\n\n      // Function to split a string based on delimiters\n      function LoopParseFunc(var_, delimiter1 = " + Chr ( 34 ) + "" + Chr ( 34 ) + ", delimiter2 = " + Chr ( 34 ) + "" + Chr ( 34 ) + ") {\n        if (typeof var_ !== " + Chr ( 34 ) + "string" + Chr ( 34 ) + ") {\n          console.error(" + Chr ( 34 ) + "Invalid input: expected a string but received:" + Chr ( 34 ) + ", var_);\n          return []; // Return an empty array or handle as needed\n        }\n\n        if (!delimiter1 && !delimiter2) {\n          return var_.split(" + Chr ( 34 ) + "" + Chr ( 34 ) + ");\n        } else {\n          const escapedDelimiters = escapeRegex(delimiter1 + delimiter2);\n          const pattern = new RegExp(" + Chr ( 96 ) + "[${escapedDelimiters}]+" + Chr ( 96 ) + ");\n          return var_.split(pattern).filter(Boolean);\n        }\n      }\n\n      // MsgBox function\n      function MsgBox(value) {\n        console.log(value.toString());\n      }\n\n      // Sorting function\n\n      function SortLikeAHK(varName, options = " + Chr ( 34 ) + "" + Chr ( 34 ) + ") {\n        let delimiter = " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + "; // Default delimiter\n        let delimiterIndex = options.indexOf(" + Chr ( 34 ) + "D" + Chr ( 34 ) + ");\n\n        if (delimiterIndex !== -1) {\n          let delimiterChar = options[delimiterIndex + 1];\n          delimiter = delimiterChar === " + Chr ( 34 ) + "" + Chr ( 34 ) + " ? " + Chr ( 34 ) + "," + Chr ( 34 ) + " : delimiterChar;\n        }\n\n        let items = varName.split(new RegExp(delimiter === " + Chr ( 34 ) + "," + Chr ( 34 ) + " ? " + Chr ( 34 ) + "," + Chr ( 34 ) + " : " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "" + Chr ( 34 ) + " + delimiter));\n\n        // Remove empty items and trim whitespace\n        items = items.filter((item) => item.trim() !== " + Chr ( 34 ) + "" + Chr ( 34 ) + ");\n\n        // Apply sorting based on options\n        if (options.includes(" + Chr ( 34 ) + "N" + Chr ( 34 ) + ")) {\n          // Numeric sort\n          items.sort((a, b) => parseInt(a, 10) - parseInt(b, 10));\n        } else if (options.includes(" + Chr ( 34 ) + "Random" + Chr ( 34 ) + ")) {\n          // Random sort\n          for (let i = items.length - 1; i > 0; i--) {\n            const j = Math.floor(Math.random() * (i + 1));\n            [items[i], items[j]] = [items[j], items[i]];\n          }\n        } else {\n          // Default alphabetical sort\n          items.sort((a, b) => {\n            const keyA = options.includes(" + Chr ( 34 ) + "C" + Chr ( 34 ) + ") ? a : a.toLowerCase();\n            const keyB = options.includes(" + Chr ( 34 ) + "C" + Chr ( 34 ) + ") ? b : b.toLowerCase();\n            if (keyA < keyB) return -1;\n            if (keyA > keyB) return 1;\n            return 0;\n          });\n        }\n\n        // Reverse if 'R' option is present\n        if (options.includes(" + Chr ( 34 ) + "R" + Chr ( 34 ) + ")) {\n          items.reverse();\n        }\n\n        // Remove duplicates if 'U' option is present\n        if (options.includes(" + Chr ( 34 ) + "U" + Chr ( 34 ) + ")) {\n          const seen = new Map();\n          items = items.filter((item) => {\n            const key = options.includes(" + Chr ( 34 ) + "C" + Chr ( 34 ) + ") ? item : item.toLowerCase();\n            if (!seen.has(key)) {\n              seen.set(key, item);\n              return true;\n            }\n            return false;\n          });\n        }\n\n        // Join the sorted items back into a string\n        const sortedVar = items.join(delimiter === " + Chr ( 34 ) + "," + Chr ( 34 ) + " ? " + Chr ( 34 ) + "," + Chr ( 34 ) + " : " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ");\n\n        return sortedVar;\n      }\n\n      function MakeHotKey(hotkey, callback) {\n        document.addEventListener(" + Chr ( 34 ) + "keydown" + Chr ( 34 ) + ", function (event) {\n          const keys = hotkey.split(" + Chr ( 34 ) + "+" + Chr ( 34 ) + ").map((key) => key.trim().toLowerCase());\n          const modifiers = {\n            ctrl: event.ctrlKey,\n            shift: event.shiftKey,\n            alt: event.altKey,\n          };\n\n          let hotkeyPressed = true;\n          keys.forEach((key) => {\n            if (key === " + Chr ( 34 ) + "ctrl" + Chr ( 34 ) + " || key === " + Chr ( 34 ) + "shift" + Chr ( 34 ) + " || key === " + Chr ( 34 ) + "alt" + Chr ( 34 ) + ") {\n              if (!modifiers[key]) {\n                hotkeyPressed = false;\n              }\n            } else if (key === " + Chr ( 34 ) + "backspace" + Chr ( 34 ) + ") {\n              if (event.key !== " + Chr ( 34 ) + "Backspace" + Chr ( 34 ) + ") {\n                hotkeyPressed = false;\n              }\n            } else if (key.startsWith(" + Chr ( 34 ) + "arrow" + Chr ( 34 ) + ")) {\n              const arrowDirection = key.replace(" + Chr ( 34 ) + "arrow" + Chr ( 34 ) + ", " + Chr ( 34 ) + "" + Chr ( 34 ) + ");\n              if (arrowDirection === " + Chr ( 34 ) + "up" + Chr ( 34 ) + " && event.key !== " + Chr ( 34 ) + "ArrowUp" + Chr ( 34 ) + ") {\n                hotkeyPressed = false;\n              } else if (arrowDirection === " + Chr ( 34 ) + "down" + Chr ( 34 ) + " && event.key !== " + Chr ( 34 ) + "ArrowDown" + Chr ( 34 ) + ") {\n                hotkeyPressed = false;\n              } else if (arrowDirection === " + Chr ( 34 ) + "left" + Chr ( 34 ) + " && event.key !== " + Chr ( 34 ) + "ArrowLeft" + Chr ( 34 ) + ") {\n                hotkeyPressed = false;\n              } else if (arrowDirection === " + Chr ( 34 ) + "right" + Chr ( 34 ) + " && event.key !== " + Chr ( 34 ) + "ArrowRight" + Chr ( 34 ) + ") {\n                hotkeyPressed = false;\n              }\n            } else if (key === " + Chr ( 34 ) + "enter" + Chr ( 34 ) + ") {\n              if (event.key !== " + Chr ( 34 ) + "Enter" + Chr ( 34 ) + ") {\n                hotkeyPressed = false;\n              }\n            } else if (!event.key.match(/^[0-9a-zA-Z]$/) && event.key !== key) {\n              hotkeyPressed = false;\n            } else if (event.key.toLowerCase() !== key && event.key.match(/^[a-zA-Z]$/)) {\n              hotkeyPressed = false;\n            }\n          });\n\n          if (hotkeyPressed) {\n            if (modifiers[" + Chr ( 34 ) + "shift" + Chr ( 34 ) + "]) {\n              callback(hotkey.toUpperCase());\n            } else {\n              callback(hotkey.toLowerCase());\n            }\n          }\n        });\n      }\n\n      // InStr\n      function InStr(Haystack, Needle, CaseSensitive = true, StartingPos = 1, Occurrence = 1) {\n        if (Haystack === null || Needle === null) return false;\n\n        // Adjust starting position if less than 1\n        StartingPos = Math.max(StartingPos, 1);\n\n        // Case-sensitive search by default\n        if (!CaseSensitive) {\n          Haystack = Haystack.toLowerCase();\n          Needle = Needle.toLowerCase();\n        }\n\n        let pos = -1;\n        let count = 0;\n        for (let i = StartingPos - 1; i < Haystack.length; i++) {\n          if (Haystack.substring(i, i + Needle.length) === Needle) {\n            count++;\n            if (count === Occurrence) {\n              pos = i + 1;\n              break;\n            }\n          }\n        }\n\n        return pos > 0; // Return true if the substring is found, false otherwise\n      }\n\n      function Trim(inputString) {\n        // Check if inputString is null or undefined\n        if (inputString == null) {\n          return " + Chr ( 34 ) + "" + Chr ( 34 ) + "; // Return an empty string if inputString is null or undefined\n        }\n        return inputString.replace(/^" + Chr ( 92 ) + "s+|" + Chr ( 92 ) + "s+$/g, " + Chr ( 34 ) + "" + Chr ( 34 ) + "); // Removes leading and trailing whitespace\n      }\n\n      function StrReplace(originalString, find, replaceWith) {\n        // Check if originalString is a string\n        if (typeof originalString !== " + Chr ( 34 ) + "string" + Chr ( 34 ) + ") {\n          return originalString; // Return originalString as is\n        }\n\n        // Escape special characters in the 'find' string to be used literally\n        const escapedFind = find.replace(/[.*+?^${}()|[" + Chr ( 92 ) + "]" + Chr ( 92 ) + "" + Chr ( 92 ) + "]/g, " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "$&" + Chr ( 34 ) + ");\n\n        // Use replace method to replace all occurrences of 'find' with 'replaceWith'\n        return originalString.replace(new RegExp(escapedFind, " + Chr ( 34 ) + "g" + Chr ( 34 ) + "), replaceWith);\n      }\n\n      // Function to trim specified number of characters from the right side of a string\n      function StringTrimRight(input, numChars) {\n        if (typeof input === " + Chr ( 34 ) + "string" + Chr ( 34 ) + " && typeof numChars === " + Chr ( 34 ) + "number" + Chr ( 34 ) + " && numChars >= 0) {\n          return input.length > numChars ? input.substring(0, input.length - numChars) : " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n        } else {\n          console.error(" + Chr ( 34 ) + "Invalid input provided." + Chr ( 34 ) + ");\n          return input; // Return original input if trimming is not possible\n        }\n      }\n\n      // Define the str function\n      function str(value) {\n        return String(value);\n      }\n\n      // Single async function to structure the entire script\n      async function runScript() {\n        // Declare and assign a variable\n\n        MakeHotKey(" + Chr ( 34 ) + "Alt+Shift+Ctrl+F" + Chr ( 34 ) + ", function (hotkey) {\n          HotKeyCalledAltShiftCtrlF();\n        });\n\n        MakeHotKey(" + Chr ( 34 ) + "Alt+Shift+Ctrl+G" + Chr ( 34 ) + ", function (hotkey) {\n          HotKeyCalledAltShiftCtrlG();\n        });\n\n        var Gui1 = {};\n        Gui1 = document.createElement(" + Chr ( 34 ) + "div" + Chr ( 34 ) + ");\n        Gui1.id = " + Chr ( 34 ) + "Gui1" + Chr ( 34 ) + ";\n\n        // Declare and assign a variable\n        let variables = {\n          null: null,\n        };\n\n        Gui1.style.position = " + Chr ( 34 ) + "absolute" + Chr ( 34 ) + ";\n        Gui1.style.width = window.innerWidth + " + Chr ( 34 ) + "px" + Chr ( 34 ) + "; // Set the width\n        Gui1.style.height = " + Chr ( 34 ) + "" + Chr ( 34 ) + " + BuildInVars(" + Chr ( 34 ) + "A_ScreenHeight" + Chr ( 34 ) + ") + " + Chr ( 34 ) + "px" + Chr ( 34 ) + "; // Set the height\n        Gui1.style.background = " + Chr ( 34 ) + "linear-gradient(90deg, " + Chr ( 34 ) + " + " + Chr ( 34 ) + "#121212" + Chr ( 34 ) + " + " + Chr ( 34 ) + " 0%, " + Chr ( 34 ) + " + " + Chr ( 34 ) + "#121212" + Chr ( 34 ) + " + " + Chr ( 34 ) + " 100%)" + Chr ( 34 ) + ";\n        Gui1.style.backgroundColor = " + Chr ( 34 ) + "linear-gradient(90deg, " + Chr ( 34 ) + " + " + Chr ( 34 ) + "#121212" + Chr ( 34 ) + " + " + Chr ( 34 ) + " 0%, " + Chr ( 34 ) + " + " + Chr ( 34 ) + "#121212" + Chr ( 34 ) + " + " + Chr ( 34 ) + " 100%)" + Chr ( 34 ) + ";\n        Gui1.style.color = " + Chr ( 34 ) + "white" + Chr ( 34 ) + ";\n        Gui1.style.fontSize = " + Chr ( 34 ) + "15px" + Chr ( 34 ) + ";\n        Gui1.style.padding = " + Chr ( 34 ) + "0px" + Chr ( 34 ) + ";\n        Gui1.style.borderRadius = " + Chr ( 34 ) + "0px" + Chr ( 34 ) + ";\n        Gui1.style.fontFamily = " + Chr ( 34 ) + ", sans-serif" + Chr ( 34 ) + "; // Specify your desired font here\n        Gui1.style.zIndex = " + Chr ( 34 ) + "10" + Chr ( 34 ) + ";\n        document.body.appendChild(Gui1); // Append the GUI window to the body\n        Gui1.style.display = " + Chr ( 34 ) + "block" + Chr ( 34 ) + ";\n        let textOldSave;\n        document.documentElement.setAttribute(" + Chr ( 34 ) + "style" + Chr ( 34 ) + ", " + Chr ( 34 ) + "padding: 0; margin: 0;" + Chr ( 34 ) + ");\n        document.head.setAttribute(" + Chr ( 34 ) + "style" + Chr ( 34 ) + ", " + Chr ( 34 ) + "padding: 0; margin: 0;" + Chr ( 34 ) + ");\n        document.body.setAttribute(" + Chr ( 34 ) + "style" + Chr ( 34 ) + ", " + Chr ( 34 ) + "overflow-x: hidden;padding: 0; margin: 0;" + Chr ( 34 ) + ");\n\n        variables.idetext = variables.ideTEXT;\n        variables.AScreenHeight = BuildInVars(" + Chr ( 34 ) + "A_ScreenHeight" + Chr ( 34 ) + ") - 20;\n        variables.AScreenWidth = BuildInVars(" + Chr ( 34 ) + "A_ScreenWidth" + Chr ( 34 ) + ") - 20;\n        var saveBackCodeBugFix = variables.ideTEXT;\n        AddIDE(Gui1, 10, 10, variables.AScreenWidth, variables.AScreenHeight, " + Chr ( 34 ) + "Gui1IDE1" + Chr ( 34 ) + ", 18, " + Chr ( 34 ) + "autohotkey" + Chr ( 34 ) + ", IDE1, variables.ideTEXT);\n\n        async function IDE1(A_GuiControl) {\n          variables.idetext = A_GuiControl;\n        }\n\n        async function HotKeyCalledAltShiftCtrlG() {\n          GuiControl(" + Chr ( 34 ) + "textide" + Chr ( 34 ) + ", " + Chr ( 34 ) + "Gui1IDE1" + Chr ( 34 ) + ", textOldSave);\n        }\n        async function HotKeyCalledAltShiftCtrlF() {\n          // console.log(" + Chr ( 34 ) + "HotKeyCalled AltShiftCtrlF" + Chr ( 34 ) + ")\n          textOldSave = variables.idetext;\n          variables.TextData = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.out = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.base64ImageData = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.base64soundList = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.base64iconList = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.base64VideoData = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.jsCode01CanvasW = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.jsCode01CanvasH = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.skipLeftCuleyForFuncPLS = 0;\n          variables.eavbnsalvbaslv = 0;\n          variables.ifWeUseCanvas = 0;\n          variables.weUseCnanvasAtALL = 0;\n          variables.numOfTextData = 0;\n          variables.funcs = " + Chr ( 34 ) + "let funcs = {" + Chr ( 92 ) + "n" + Chr ( 34 ) + ";\n          variables.doWeEvenDecAnyFuncHUH = 0;\n          variables.onKeyPress = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.jsCodeGui = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.isFullScrenOnce = 0;\n          variables.HotKeyCalledHotKyes = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.jsCode = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.outAHKCodeTrimed = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.idetext = await StrReplace(variables.idetext, await Chr(13), " + Chr ( 34 ) + "" + Chr ( 34 ) + ");\n          var items1 = LoopParseFunc(variables.idetext, " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ", " + Chr ( 34 ) + "" + Chr ( 92 ) + "r" + Chr ( 34 ) + ");\n          for (/* Loop Parse */ let A_Index1 = 1; A_Index1 <= items1.length; A_Index1++) {\n            variables.A_Index1 = A_Index1;\n            variables.A_LoopField1 = items1[A_Index1 - 1];\n            variables.outAHKCodeTrimed += (await Trim(variables.A_LoopField1)) + " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ";\n          }\n          variables.idetext = StringTrimRight(variables.outAHKCodeTrimed, 1);\n          variables.AHKcodeOUT754754 = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          variables.areWEinSome34sNum = 0;\n          variables.theIdNumOfThe34 = 0;\n          var items2 = LoopParseFunc(variables.idetext);\n          for (/* Loop Parse */ let A_Index2 = 1; A_Index2 <= items2.length; A_Index2++) {\n            variables.A_Index2 = A_Index2;\n            variables.A_LoopField2 = items2[A_Index2 - 1];\n            variables[" + Chr ( 34 ) + "theIdNumOfThe34theVar" + Chr ( 34 ) + " + variables.A_Index2] = await Chr(34);\n          }\n          var items3 = LoopParseFunc(variables.idetext);\n          for (/* Loop Parse */ let A_Index3 = 1; A_Index3 <= items3.length; A_Index3++) {\n            variables.A_Index3 = A_Index3;\n            variables.A_LoopField3 = items3[A_Index3 - 1];\n            if (variables.A_LoopField3 == (await Chr(34))) {\n              variables.areWEinSome34sNum += 1;\n            }\n            if (variables.areWEinSome34sNum == 1) {\n              if (variables.A_LoopField3 != (await Chr(34))) {\n                variables[" + Chr ( 34 ) + "theIdNumOfThe34theVar" + Chr ( 34 ) + " + variables.theIdNumOfThe34] += variables.A_LoopField3;\n              } else {\n                variables.theIdNumOfThe34 += 1;\n                variables.AHKcodeOUT754754 += " + Chr ( 34 ) + "ihuiuuhuuhtheidFor--asas-theuhturtyphoutr-" + Chr ( 34 ) + " + (await Chr(65)) + (await Chr(65)) + (await str(variables.theIdNumOfThe34)) + (await Chr(65)) + (await Chr(65));\n              }\n            }\n            if (variables.areWEinSome34sNum == 2 || variables.areWEinSome34sNum == 0) {\n              if (variables.A_LoopField3 != (await Chr(34))) {\n                variables.AHKcodeOUT754754 += variables.A_LoopField3;\n              }\n              variables.areWEinSome34sNum = 0;\n            }\n          }\n          variables.idetext = variables.AHKcodeOUT754754;\n          for (/* Normal Loop */ variables.A_Index4 = 1; variables.A_Index4 <= variables.theIdNumOfThe34; variables.A_Index4++) {\n            variables[" + Chr ( 34 ) + "theIdNumOfThe34theVar" + Chr ( 34 ) + " + variables.A_Index4] += await Chr(34);\n          }\n          variables.sstr23IfFuncInNAMEnum = 0;\n          variables.outCodeFixBraces = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          for (/* Normal Loop */ variables.A_Index5 = 1; variables.A_Index5 <= 2; variables.A_Index5++) {\n            variables.outCodeFixBraces = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n            var items6 = LoopParseFunc(variables.idetext, " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ", " + Chr ( 34 ) + "" + Chr ( 92 ) + "r" + Chr ( 34 ) + ");\n            for (/* Loop Parse */ let A_Index6 = 1; A_Index6 <= items6.length; A_Index6++) {\n              variables.A_Index6 = A_Index6;\n              variables.A_LoopField6 = items6[A_Index6 - 1];\n              if ((await InStr(await Trim(variables.A_LoopField6), " + Chr ( 34 ) + "{" + Chr ( 34 ) + ")) && (await Trim(variables.A_LoopField6)) != " + Chr ( 34 ) + "{" + Chr ( 34 ) + ") {\n                variables.outCodeFixBraces += (await Trim(await StrReplace(await Trim(variables.A_LoopField6), " + Chr ( 34 ) + "{" + Chr ( 34 ) + ", " + Chr ( 34 ) + "" + Chr ( 34 ) + "))) + " + Chr ( 34 ) + "" + Chr ( 92 ) + "n{" + Chr ( 92 ) + "n" + Chr ( 34 ) + ";\n              } else if ((await InStr(await Trim(variables.A_LoopField6), " + Chr ( 34 ) + "}" + Chr ( 34 ) + ")) && (await Trim(variables.A_LoopField6)) != " + Chr ( 34 ) + "}" + Chr ( 34 ) + ") {\n                variables.outCodeFixBraces += " + Chr ( 34 ) + "}" + Chr ( 92 ) + "n" + Chr ( 34 ) + " + (await Trim(await StrReplace(await Trim(variables.A_LoopField6), " + Chr ( 34 ) + "}" + Chr ( 34 ) + ", " + Chr ( 34 ) + "" + Chr ( 34 ) + "))) + " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ";\n              } else {\n                variables.outCodeFixBraces += (await Trim(variables.A_LoopField6)) + " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ";\n              }\n            }\n            variables.idetext = StringTrimRight(variables.outCodeFixBraces, 1);\n          }\n          variables.idetext = await KandRstyleFormat(await indent_nested_curly_braces(variables.idetext));\n          for (/* Normal Loop */ variables.A_Index7 = 1; variables.A_Index7 <= variables.theIdNumOfThe34; variables.A_Index7++) {\n            variables.idetext = await StrReplace(variables.idetext, " + Chr ( 34 ) + "ihuiuuhuuhtheidFor--asas-theuhturtyphoutr-" + Chr ( 34 ) + " + (await Chr(65)) + (await Chr(65)) + (await str(variables.A_Index7)) + (await Chr(65)) + (await Chr(65)), variables[" + Chr ( 34 ) + "theIdNumOfThe34theVar" + Chr ( 34 ) + " + variables.A_Index7]);\n          }\n          GuiControl(" + Chr ( 34 ) + "textide" + Chr ( 34 ) + ", " + Chr ( 34 ) + "Gui1IDE1" + Chr ( 34 ) + ", variables.idetext);\n        }\n        async function KandRstyleFormat(code) {\n          variables.code = code;\n          variables.codeOut = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          var items8 = LoopParseFunc(variables.code, " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ", " + Chr ( 34 ) + "" + Chr ( 92 ) + "r" + Chr ( 34 ) + ");\n          for (/* Loop Parse */ let A_Index8 = 1; A_Index8 <= items8.length; A_Index8++) {\n            variables.A_Index8 = A_Index8;\n            variables.A_LoopField8 = items8[A_Index8 - 1];\n            variables[" + Chr ( 34 ) + "lookInTheFurtre" + Chr ( 34 ) + " + variables.A_Index8] = await Trim(variables.A_LoopField8);\n          }\n          variables[" + Chr ( 34 ) + "lookInTheFurtre" + Chr ( 34 ) + " + variables.A_Index] = " + Chr ( 34 ) + " " + Chr ( 34 ) + ";\n          variables.skipLine = 0;\n          var items9 = LoopParseFunc(variables.code, " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ", " + Chr ( 34 ) + "" + Chr ( 92 ) + "r" + Chr ( 34 ) + ");\n          for (/* Loop Parse */ let A_Index9 = 1; A_Index9 <= items9.length; A_Index9++) {\n            variables.A_Index9 = A_Index9;\n            variables.A_LoopField9 = items9[A_Index9 - 1];\n            variables.AIndex = variables.A_Index9 + 1;\n            if (variables.skipLine == 1) {\n              variables.skipLine = 0;\n            } else {\n              if (variables[" + Chr ( 34 ) + "lookInTheFurtre" + Chr ( 34 ) + " + variables.AIndex] != " + Chr ( 34 ) + "{" + Chr ( 34 ) + ") {\n                variables.codeOut += variables.A_LoopField9 + " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ";\n              }\n            }\n            if (variables[" + Chr ( 34 ) + "lookInTheFurtre" + Chr ( 34 ) + " + variables.AIndex] == " + Chr ( 34 ) + "{" + Chr ( 34 ) + ") {\n              variables.skipLine = 1;\n              variables.codeOut += variables.A_LoopField9 + " + Chr ( 34 ) + " {" + Chr ( 92 ) + "n" + Chr ( 34 ) + ";\n            }\n          }\n          variables.codeOut = StringTrimRight(variables.codeOut, 1);\n          variables.codeOut2 = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          var items10 = LoopParseFunc(variables.codeOut, " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ", " + Chr ( 34 ) + "" + Chr ( 92 ) + "r" + Chr ( 34 ) + ");\n          for (/* Loop Parse */ let A_Index10 = 1; A_Index10 <= items10.length; A_Index10++) {\n            variables.A_Index10 = A_Index10;\n            variables.A_LoopField10 = items10[A_Index10 - 1];\n            variables[" + Chr ( 34 ) + "lookInTheFurtre" + Chr ( 34 ) + " + variables.A_Index10] = await Trim(variables.A_LoopField10);\n          }\n          variables[" + Chr ( 34 ) + "lookInTheFurtre" + Chr ( 34 ) + " + variables.A_Index] = " + Chr ( 34 ) + " " + Chr ( 34 ) + ";\n          variables.skipLine = 0;\n          var items11 = LoopParseFunc(variables.codeOut, " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ", " + Chr ( 34 ) + "" + Chr ( 92 ) + "r" + Chr ( 34 ) + ");\n          for (/* Loop Parse */ let A_Index11 = 1; A_Index11 <= items11.length; A_Index11++) {\n            variables.A_Index11 = A_Index11;\n            variables.A_LoopField11 = items11[A_Index11 - 1];\n            variables.AIndex = variables.A_Index11 + 1;\n            if (variables.skipLine == 1) {\n              variables.skipLine = 0;\n            } else {\n              if (variables[" + Chr ( 34 ) + "lookInTheFurtre" + Chr ( 34 ) + " + variables.AIndex] != " + Chr ( 34 ) + keyWordElse + " {" + Chr ( 34 ) + ") {\n                variables.codeOut2 += variables.A_LoopField11 + " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ";\n              }\n            }\n            if (variables[" + Chr ( 34 ) + "lookInTheFurtre" + Chr ( 34 ) + " + variables.AIndex] == " + Chr ( 34 ) + keyWordElse + " {" + Chr ( 34 ) + ") {\n              variables.skipLine = 1;\n              variables.scoaceses = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n              var items12 = LoopParseFunc(variables.A_LoopField11);\n              for (/* Loop Parse */ let A_Index12 = 1; A_Index12 <= items12.length; A_Index12++) {\n                variables.A_Index12 = A_Index12;\n                variables.A_LoopField12 = items12[A_Index12 - 1];\n                if (variables.A_LoopField12 != " + Chr ( 34 ) + " " + Chr ( 34 ) + ") {\n                  break;\n                } else {\n                  variables.scoaceses += " + Chr ( 34 ) + " " + Chr ( 34 ) + ";\n                }\n              }\n              variables.codeOut2 += variables.scoaceses + " + Chr ( 34 ) + "} " + keyWordElse + Chr ( 34 ) + " + " + Chr ( 34 ) + " {" + Chr ( 92 ) + "n" + Chr ( 34 ) + ";\n            }\n          }\n          variables.codeOut = StringTrimRight(variables.codeOut2, 1);\n          return variables.codeOut;\n        }\n        async function RepeatSpaces(count) {\n          variables.count = count;\n          variables.spaces = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          for (/* Normal Loop */ variables.A_Index10 = 1; variables.A_Index10 <= variables.count; variables.A_Index10++) {\n            variables.spaces += " + Chr ( 34 ) + " " + Chr ( 34 ) + ";\n          }\n          return variables.spaces;\n        }\n        async function indent_nested_curly_braces(input_string) {\n          variables.input_string = input_string;\n          variables.indent_size = 4;\n          variables.current_indent = 0;\n          variables.result = " + Chr ( 34 ) + "" + Chr ( 34 ) + ";\n          var items11 = variables.input_string.split(/" + Chr ( 92 ) + "r?" + Chr ( 92 ) + "n|" + Chr ( 92 ) + "r/);\n          for (/* Loop Parse */ let A_Index11 = 1; A_Index11 <= items11.length; A_Index11++) {\n            variables.A_Index11 = A_Index11;\n            variables.A_LoopField11 = items11[A_Index11 - 1];\n            variables.trimmed_line = await Trim(variables.A_LoopField11);\n            if (variables.trimmed_line == (await Chr(123))) {\n              variables.result += (await RepeatSpaces(variables.current_indent)) + (variables.trimmed_line + " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ");\n              variables.current_indent = variables.current_indent + variables.indent_size;\n            } else if (variables.trimmed_line == (await Chr(125))) {\n              variables.current_indent = variables.current_indent - variables.indent_size;\n              variables.result += (await RepeatSpaces(variables.current_indent)) + (variables.trimmed_line + " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ");\n            } else {\n              variables.result += (await RepeatSpaces(variables.current_indent)) + (variables.trimmed_line + " + Chr ( 34 ) + "" + Chr ( 92 ) + "n" + Chr ( 34 ) + ");\n            }\n          }\n          variables.result = StringTrimRight(variables.result, 1);\n          // Return the result\n          return variables.result;\n        }\n      }\n\n      // Call the async function to start the script\n      runScript();\n    </script>\n  </body>\n</html>\n";
std::string regexCode = "{ token: " + Chr ( 34 ) + "comment" + Chr ( 34 ) + ", regex: " + Chr ( 34 ) + keyWordComment + ".*$" + Chr ( 34 ) + " },\n              { token: " + Chr ( 34 ) + "keywords" + Chr ( 34 ) + ", regex: " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "b(" + keywords + ")" + Chr ( 92 ) + "" + Chr ( 92 ) + "b" + Chr ( 34 ) + " },\n              { token: " + Chr ( 34 ) + "command" + Chr ( 34 ) + ", regex: " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "b(" + keyWordsCommandsFolrmated + ")(?=" + Chr ( 92 ) + "" + Chr ( 92 ) + ",)" + Chr ( 34 ) + " },\n              { token: " + Chr ( 34 ) + "functions" + Chr ( 34 ) + ", regex: " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "b(" + functionsForHighlighting + ")(?=" + Chr ( 92 ) + "" + Chr ( 92 ) + "()" + Chr ( 34 ) + " },\n              { token: " + Chr ( 34 ) + "BuildInFunc" + Chr ( 34 ) + ", regex: " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "b(" + keyWordAIndex + "|" + keyWordALoopField + "|this)" + Chr ( 92 ) + "" + Chr ( 92 ) + "b" + Chr ( 34 ) + " },\n              { token: " + Chr ( 34 ) + "arrayMethods" + Chr ( 34 ) + ", regex: " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + ".(" + keyWordArrayMethods + ")" + Chr ( 92 ) + "" + Chr ( 92 ) + "b" + Chr ( 34 ) + " },\n              { token: " + Chr ( 34 ) + "static_types" + Chr ( 34 ) + ", regex: " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "b(" + keyWordTypes + ")" + Chr ( 92 ) + "" + Chr ( 92 ) + "b" + Chr ( 34 ) + " },\n              { token: " + Chr ( 34 ) + "operators" + Chr ( 34 ) + ", regex: " + Chr ( 34 ) + " && | " + keyWordOrOperator + " | " + keyWordAndOperator + " | && " + Chr ( 34 ) + " },\n              { token: " + Chr ( 34 ) + "trueANDfalse" + Chr ( 34 ) + ", regex: " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "b(" + keyWordTrue + "|" + keyWordFalse + "|" + keyWordGlobal + ")" + Chr ( 92 ) + "" + Chr ( 92 ) + "b" + Chr ( 34 ) + " },\n              { token: " + Chr ( 34 ) + "variables" + Chr ( 34 ) + ", regex: " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "b[a-zA-Z_][a-zA-Z0-9_]*" + Chr ( 92 ) + "" + Chr ( 92 ) + "b" + Chr ( 34 ) + " },\n              { token: " + Chr ( 34 ) + "constant.numeric" + Chr ( 34 ) + ", regex: " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "b[0-9]+" + Chr ( 92 ) + "" + Chr ( 92 ) + "b" + Chr ( 34 ) + " },\n              { token: " + Chr ( 34 ) + "braces_Open" + Chr ( 34 ) + ", regex: " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "{" + Chr ( 34 ) + " },\n              { token: " + Chr ( 34 ) + "braces_Close" + Chr ( 34 ) + ", regex: " + Chr ( 34 ) + "" + Chr ( 92 ) + "" + Chr ( 92 ) + "}" + Chr ( 34 ) + " },\n              { token: " + Chr ( 34 ) + "string" + Chr ( 34 ) + ", regex: '" + Chr ( 34 ) + ".*?" + Chr ( 34 ) + "' },\n              // Multi-line comments\n              {\n                token: " + Chr ( 34 ) + "comment.block" + Chr ( 34 ) + ", // Token for multi-line comments\n                regex: /" + keyWordCommentOpenMultiLine + "/, // Start of multi-line comment\n                next: " + Chr ( 34 ) + "comment_block" + Chr ( 34 ) + ",\n              },\n            ],\n            comment_block: [\n              {\n                token: " + Chr ( 34 ) + "comment.block" + Chr ( 34 ) + ",\n                regex: /.*?" + keyWordCommentCloseMultiLine + "/, // End of multi-line comment\n                next: " + Chr ( 34 ) + "start" + Chr ( 34 ) + ", // Go back to the start state\n              },\n              {\n                token: " + Chr ( 34 ) + "comment.block" + Chr ( 34 ) + ",\n                regex: /.*/, // Any other content within the comment\n              },\n            ],\n          };\n        };\n";
std::string endCodeOutput = "// Define the custom " + Chr ( 34 ) + "ht" + Chr ( 34 ) + " language for Ace Editor with AHK rules\nace.define(" + Chr ( 34 ) + "ace/mode/ht" + Chr ( 34 ) + ", [" + Chr ( 34 ) + "require" + Chr ( 34 ) + ", " + Chr ( 34 ) + "exports" + Chr ( 34 ) + ", " + Chr ( 34 ) + "module" + Chr ( 34 ) + ", " + Chr ( 34 ) + "ace/lib/oop" + Chr ( 34 ) + ", " + Chr ( 34 ) + "ace/mode/text" + Chr ( 34 ) + ", " + Chr ( 34 ) + "ace/mode/text_highlight_rules" + Chr ( 34 ) + "], function (require, exports, module) {\n  var oop = require(" + Chr ( 34 ) + "ace/lib/oop" + Chr ( 34 ) + ");\n  var TextMode = require(" + Chr ( 34 ) + "ace/mode/text" + Chr ( 34 ) + ").Mode;\n  var TextHighlightRules = require(" + Chr ( 34 ) + "ace/mode/text_highlight_rules" + Chr ( 34 ) + ").TextHighlightRules;\n\n  var HTHighlightRules = function () {\n    this.$rules = {\n      start: [\n" + regexCode + "\n  oop.inherits(HTHighlightRules, TextHighlightRules);\n\n  var HTMode = function () {\n    this.HighlightRules = HTHighlightRules;\n  };\n  oop.inherits(HTMode, TextMode);\n\n  exports.Mode = HTMode;\n});\n\nlet HTVM_Syntax_AutoComplete = " + autoComplete + "\n";
std::string all = endCodeOutput;
FileDelete("IDE/htvm_syntax_highlighting_and_autocomplete.js");
FileAppend(all, "IDE/htvm_syntax_highlighting_and_autocomplete.js");
print(std::string("Done."));

return 0;
}