#include <algorithm>
#include <cctype>
#include <chrono>
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
#include <unordered_set>
#include <vector>

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

// Wellcome the new revolution
// keyWordsCommands rules
// OUTVAR = the output variable
// INVAR = the input variable, like the one before the =
// INOUTVAR = both the output variable and the input variable
// lineTranspile = the first keyword will be replaced with the third section
// 'param123... = a parameter with ""
// param123... = a regular parameter, nothing much, just add as many as needed
std::string KeyWordsCommands(std::string theCodeCommands, std::string mode, std::string keyWordsCommands, std::string langToTranspileTo)
{
theCodeCommands = StrReplace ( theCodeCommands , "%" , "" ) ;
if (mode == "check") 
{
std::vector<std::string> items1 = LoopParseFunc(keyWordsCommands, "|");
for (size_t A_Index1 = 1; A_Index1 < items1.size() + 1; A_Index1++)
{
std::string A_LoopField1 = items1[A_Index1 - 1];
std::vector<std::string> items2 = LoopParseFunc(A_LoopField1, ",");
for (size_t A_Index2 = 1; A_Index2 < items2.size() + 1; A_Index2++)
{
std::string A_LoopField2 = items2[A_Index2 - 1];
if (A_Index2 == 1) 
{
if (SubStr (StrLower (theCodeCommands) , 1 , StrLen (A_LoopField2 + ", ")) == StrLower (A_LoopField2 + ", ")) 
{
//MsgBox, true
return "true";
}
}
if (A_Index2 == 1) 
{
if (theCodeCommands == A_LoopField2) 
{
//MsgBox, true
return "true";
}
}
}
}
//MsgBox, false
return "false";
}
int AIndex;
if (mode == "transpile") 
{
int keyWordsCommandsNumLine = 1;
std::vector<std::string> items3 = LoopParseFunc(keyWordsCommands, "|");
for (size_t A_Index3 = 1; A_Index3 < items3.size() + 1; A_Index3++)
{
std::string A_LoopField3 = items3[A_Index3 - 1];
AIndex = A_Index3;
std::vector<std::string> items4 = LoopParseFunc(A_LoopField3, ",");
for (size_t A_Index4 = 1; A_Index4 < items4.size() + 1; A_Index4++)
{
std::string A_LoopField4 = items4[A_Index4 - 1];
if (A_Index4 == 1) 
{
if (SubStr (StrLower (theCodeCommands) , 1 , StrLen (A_LoopField4 + ", ")) == StrLower (A_LoopField4 + ", ")) 
{
//MsgBox, true
keyWordsCommandsNumLine = AIndex;
break;
}
}
if (A_Index4 == 1) 
{
//MsgBox, %theCodeCommands% = %A_LoopField4%
if (theCodeCommands == A_LoopField4) 
{
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
int theCodeCommandNum = 1;
int outConstuctTheOutFromTheCommandsLineTranspile = 0;
std::string outConstuctTheOutFromTheCommandsLineTranspileText = "";
std::string semicolon = "";
if (langToTranspileTo!= "py") 
{
semicolon = ";";
}
OneIndexedArray<std::string> theCodeCommand;
theCodeCommands = Trim ( theCodeCommands ) ;
std::vector<std::string> items5 = LoopParseFunc(theCodeCommands, ",");
for (size_t A_Index5 = 1; A_Index5 < items5.size() + 1; A_Index5++)
{
std::string A_LoopField5 = items5[A_Index5 - 1];
theCodeCommand.add(Trim(A_LoopField5));
//MsgBox, % A_LoopField5
}
std::vector<std::string> items6 = LoopParseFunc(keyWordsCommands, "|");
for (size_t A_Index6 = 1; A_Index6 < items6.size() + 1; A_Index6++)
{
std::string A_LoopField6 = items6[A_Index6 - 1];
if (keyWordsCommandsNumLine == A_Index6) 
{
//MsgBox, % A_LoopField6
std::vector<std::string> items7 = LoopParseFunc(A_LoopField6, ",");
for (size_t A_Index7 = 1; A_Index7 < items7.size() + 1; A_Index7++)
{
std::string A_LoopField7 = items7[A_Index7 - 1];
if (A_Index7 == 1) 
{
outConstuctTheOutFromTheCommandsFucnName = A_LoopField7;
}
else if (A_Index7 == 2) 
{
//MsgBox, % A_LoopField7
if (A_LoopField7 == "lineTranspile") 
{
outConstuctTheOutFromTheCommandsLineTranspile = 1;
}
if (A_LoopField7 == "OUTVAR") 
{
outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
}
else if (A_LoopField7 == "INOUTVAR") 
{
outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
}
else if (A_LoopField7 == "INVAR") 
{
outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
}
else
{
if (InStr (A_LoopField7 , Chr (39))) 
{
outConstuctTheOutFromTheCommandsParams += Chr ( 34 ) + theCodeCommand[theCodeCommandNum] + Chr ( 34 ) + ", ";
}
else
{
outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
}
}
}
else if (A_Index7 == 3) 
{
if (outConstuctTheOutFromTheCommandsLineTranspile == 1) 
{
outConstuctTheOutFromTheCommandsLineTranspileText = A_LoopField7;
}
if (A_LoopField7 == "INVAR") 
{
outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
}
else
{
if (InStr (A_LoopField7 , Chr (39))) 
{
outConstuctTheOutFromTheCommandsParams += Chr ( 34 ) + theCodeCommand[theCodeCommandNum] + Chr ( 34 ) + ", ";
}
else
{
outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
}
}
}
else
{
//MsgBox, % theCodeCommand[theCodeCommandNum]
if (InStr (A_LoopField7 , Chr (39))) 
{
if (Trim (theCodeCommand[theCodeCommandNum])!= "") 
{
outConstuctTheOutFromTheCommandsParams += Chr ( 34 ) + theCodeCommand[theCodeCommandNum] + Chr ( 34 ) + ", ";
}
}
else
{
if (Trim (theCodeCommand[theCodeCommandNum])!= "") 
{
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
if (outConstuctTheOutFromTheCommandsOutVar!= "") 
{
if (outConstuctTheOutFromTheCommandsParams == "") 
{
outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " = " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ")" + semicolon;
}
else
{
outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " = " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ", " + outConstuctTheOutFromTheCommandsParams + ")" + semicolon;
}
}
if (outConstuctTheOutFromTheCommandsOutVar == "") 
{
if (outConstuctTheOutFromTheCommandsParams == "") 
{
outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ")" + semicolon;
}
else
{
outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ", " + outConstuctTheOutFromTheCommandsParams + ")" + semicolon;
}
}
if (outConstuctTheOutFromTheCommandsLineTranspile == 1) 
{
outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsLineTranspileText;
}
outConstuctTheOutFromTheCommands = StrReplace ( outConstuctTheOutFromTheCommands , "(, " , "( " ) ;
outConstuctTheOutFromTheCommands = StrReplace ( outConstuctTheOutFromTheCommands , "(," , "(" ) ;
return outConstuctTheOutFromTheCommands;
}
return "false";
}
std::string ExtractDigits(std::string inputString)
{
std::string digits;
std::vector<std::string> items8 = LoopParseFunc(inputString);
for (size_t A_Index8 = 1; A_Index8 < items8.size() + 1; A_Index8++)
{
std::string A_LoopField8 = items8[A_Index8 - 1];
if (RegExMatch (A_LoopField8 , "\\d")) 
{
digits += A_LoopField8;
}
}
return digits;
}
std::string convertJs_cpp_Normal(std::string theCode)
{
std::string out;
std::string indexName;
std::string indexEqual;
std::string indexMax;
std::vector<std::string> items9 = LoopParseFunc(theCode, " ");
for (size_t A_Index9 = 1; A_Index9 < items9.size() + 1; A_Index9++)
{
std::string A_LoopField9 = items9[A_Index9 - 1];
if (A_Index9 == 3) 
{
indexName = StrReplace ( A_LoopField9 , ";" , "" ) ;
}
if (A_Index9 == 5) 
{
indexEqual = StrReplace ( A_LoopField9 , ";" , "" ) ;
}
if (A_Index9 == 8) 
{
indexMax = StrReplace ( A_LoopField9 , ";" , "" ) ;
}
}
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for (int " + indexName + " = " + indexEqual + "; " + indexName + " < " + indexMax + "; " + indexName + "++)";
return out;
}
std::string convertJs_py_Normal(std::string theCode)
{
std::string out;
std::string indexName;
std::string indexEqual;
std::string indexMax;
std::vector<std::string> items10 = LoopParseFunc(theCode, " ");
for (size_t A_Index10 = 1; A_Index10 < items10.size() + 1; A_Index10++)
{
std::string A_LoopField10 = items10[A_Index10 - 1];
if (A_Index10 == 3) 
{
indexName = StrReplace ( A_LoopField10 , ";" , "" ) ;
}
if (A_Index10 == 5) 
{
indexEqual = StrReplace ( A_LoopField10 , ";" , "" ) ;
}
if (A_Index10 == 8) 
{
indexMax = StrReplace ( A_LoopField10 , ";" , "" ) ;
}
}
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for " + indexName + " in range(" + indexEqual + ", " + indexMax + "):";
return out;
}
std::string convertPy_cpp_Normal(std::string theCode)
{
std::string out;
std::string indexName;
std::string indexEqual;
std::string indexMax;
if (InStr (theCode , ",")) 
{
std::vector<std::string> items11 = LoopParseFunc(theCode, " ");
for (size_t A_Index11 = 1; A_Index11 < items11.size() + 1; A_Index11++)
{
std::string A_LoopField11 = items11[A_Index11 - 1];
if (A_Index11 == 2) 
{
indexName = StrReplace ( A_LoopField11 , ";" , "" ) ;
}
if (A_Index11 == 4) 
{
indexEqual = Trim ( StrReplace ( StrReplace ( StrReplace ( A_LoopField11 , ";" , "" ) , "range(" , "" ) , "," , "" ) ) ;
}
if (A_Index11 == 5) 
{
indexMax = Trim ( StrReplace ( StrReplace ( StrReplace ( A_LoopField11 , ";" , "" ) , ")" , "" ) , "," , "" ) ) ;
}
}
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for (int " + indexName + " = " + indexEqual + "; " + indexName + " < " + indexMax + "; " + indexName + "++)";
return out;
}
else
{
std::vector<std::string> items12 = LoopParseFunc(theCode, " ");
for (size_t A_Index12 = 1; A_Index12 < items12.size() + 1; A_Index12++)
{
std::string A_LoopField12 = items12[A_Index12 - 1];
if (A_Index12 == 2) 
{
indexName = StrReplace ( A_LoopField12 , ";" , "" ) ;
}
if (A_Index12 == 4) 
{
indexEqual = "0";
indexMax = ExtractDigits ( StrReplace ( A_LoopField12 , ";" , "" ) ) ;
}
}
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for (int " + indexName + " = " + indexEqual + "; " + indexName + " < " + indexMax + "; " + indexName + "++)";
return out;
}
}
std::string convertPy_js_Normal(std::string theCode)
{
std::string out;
std::string indexName;
std::string indexEqual;
std::string indexMax;
if (InStr (theCode , ",")) 
{
std::vector<std::string> items13 = LoopParseFunc(theCode, " ");
for (size_t A_Index13 = 1; A_Index13 < items13.size() + 1; A_Index13++)
{
std::string A_LoopField13 = items13[A_Index13 - 1];
if (A_Index13 == 2) 
{
indexName = StrReplace ( A_LoopField13 , ";" , "" ) ;
}
if (A_Index13 == 4) 
{
indexEqual = Trim ( StrReplace ( StrReplace ( StrReplace ( A_LoopField13 , ";" , "" ) , "range(" , "" ) , "," , "" ) ) ;
}
if (A_Index13 == 5) 
{
indexMax = Trim ( StrReplace ( StrReplace ( StrReplace ( A_LoopField13 , ";" , "" ) , ")" , "" ) , "," , "" ) ) ;
}
}
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for (let " + indexName + " = " + indexEqual + "; " + indexName + " < " + indexMax + "; " + indexName + "++)";
return out;
}
else
{
std::vector<std::string> items14 = LoopParseFunc(theCode, " ");
for (size_t A_Index14 = 1; A_Index14 < items14.size() + 1; A_Index14++)
{
std::string A_LoopField14 = items14[A_Index14 - 1];
if (A_Index14 == 2) 
{
indexName = StrReplace ( A_LoopField14 , ";" , "" ) ;
}
if (A_Index14 == 4) 
{
indexEqual = "0";
indexMax = ExtractDigits ( StrReplace ( A_LoopField14 , ";" , "" ) ) ;
}
}
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for (let " + indexName + " = " + indexEqual + "; " + indexName + " < " + indexMax + "; " + indexName + "++)";
return out;
}
}
std::string convertCpp_js_Normal(std::string theCode)
{
std::string out;
std::string indexName;
std::string indexEqual;
std::string indexMax;
std::vector<std::string> items15 = LoopParseFunc(theCode, " ");
for (size_t A_Index15 = 1; A_Index15 < items15.size() + 1; A_Index15++)
{
std::string A_LoopField15 = items15[A_Index15 - 1];
if (A_Index15 == 3) 
{
indexName = StrReplace ( A_LoopField15 , ";" , "" ) ;
}
if (A_Index15 == 5) 
{
indexEqual = StrReplace ( A_LoopField15 , ";" , "" ) ;
}
if (A_Index15 == 8) 
{
indexMax = StrReplace ( A_LoopField15 , ";" , "" ) ;
}
}
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for (let " + indexName + " = " + indexEqual + "; " + indexName + " < " + indexMax + "; " + indexName + "++)";
return out;
}
std::string convertCpp_py_Normal(std::string theCode)
{
std::string out;
std::string indexName;
std::string indexEqual;
std::string indexMax;
std::vector<std::string> items16 = LoopParseFunc(theCode, " ");
for (size_t A_Index16 = 1; A_Index16 < items16.size() + 1; A_Index16++)
{
std::string A_LoopField16 = items16[A_Index16 - 1];
if (A_Index16 == 3) 
{
indexName = StrReplace ( A_LoopField16 , ";" , "" ) ;
}
if (A_Index16 == 5) 
{
indexEqual = StrReplace ( A_LoopField16 , ";" , "" ) ;
}
if (A_Index16 == 8) 
{
indexMax = StrReplace ( A_LoopField16 , ";" , "" ) ;
}
}
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for " + indexName + " in range(" + indexEqual + ", " + indexMax + "):";
return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string keyWordComment;
std::string convertJs_cpp_Array(std::string theCode)
{
std::string out;
std::string indexName;
std::string indexEqual;
std::string indexMax;
std::vector<std::string> items17 = LoopParseFunc(theCode, " ");
for (size_t A_Index17 = 1; A_Index17 < items17.size() + 1; A_Index17++)
{
std::string A_LoopField17 = items17[A_Index17 - 1];
if (A_Index17 == 3) 
{
indexName = StrReplace ( A_LoopField17 , ";" , "" ) ;
}
if (A_Index17 == 5) 
{
indexEqual = StrReplace ( A_LoopField17 , ";" , "" ) ;
}
if (A_Index17 == 8) 
{
indexMax = StrReplace ( A_LoopField17 , ";" , "" ) ;
}
}
indexMax = StrSplit ( indexMax , "." , 1 ) + ".size()";
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for (int " + indexName + " = " + indexEqual + "; " + indexName + " < " + indexMax + "; " + indexName + "++)";
return out;
}
std::string convertJs_py_Array(std::string theCode)
{
std::string out;
std::string indexName;
std::string indexEqual;
std::string indexMax;
std::vector<std::string> items18 = LoopParseFunc(theCode, " ");
for (size_t A_Index18 = 1; A_Index18 < items18.size() + 1; A_Index18++)
{
std::string A_LoopField18 = items18[A_Index18 - 1];
if (A_Index18 == 3) 
{
indexName = StrReplace ( A_LoopField18 , ";" , "" ) ;
}
if (A_Index18 == 5) 
{
indexEqual = StrReplace ( A_LoopField18 , ";" , "" ) ;
}
if (A_Index18 == 8) 
{
indexMax = StrSplit ( StrReplace ( A_LoopField18 , ";" , "" ) , "." , 1 ) ;
}
}
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for " + indexName + " in range(" + indexEqual + ", len(" + indexMax + ")):";
return out;
}
std::string convertPy_cpp_Array(std::string theCode)
{
std::string out;
std::string indexName;
std::string indexEqual;
std::string indexMax;
if (InStr (theCode , ",")) 
{
std::vector<std::string> items19 = LoopParseFunc(theCode, " ");
for (size_t A_Index19 = 1; A_Index19 < items19.size() + 1; A_Index19++)
{
std::string A_LoopField19 = items19[A_Index19 - 1];
if (A_Index19 == 2) 
{
indexName = StrReplace ( A_LoopField19 , ";" , "" ) ;
}
if (A_Index19 == 4) 
{
indexEqual = ExtractDigits ( StrReplace ( A_LoopField19 , ";" , "" ) ) ;
}
if (A_Index19 == 5) 
{
indexMax = StrSplit ( StrSplit ( StrReplace ( A_LoopField19 , ";" , "" ) , "len(" , 2 ) , ")" , 1 ) + ".size()";
}
}
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for (int " + indexName + " = " + indexEqual + "; " + indexName + " < " + indexMax + "; " + indexName + "++)";
return out;
}
else
{
std::vector<std::string> items20 = LoopParseFunc(theCode, " ");
for (size_t A_Index20 = 1; A_Index20 < items20.size() + 1; A_Index20++)
{
std::string A_LoopField20 = items20[A_Index20 - 1];
if (A_Index20 == 2) 
{
indexName = A_LoopField20;
}
if (A_Index20 == 4) 
{
indexEqual = "0";
indexMax = StrSplit ( StrSplit ( StrReplace ( A_LoopField20 , ";" , "" ) , "len(" , 2 ) , ")" , 1 ) + ".size()";
}
}
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for (int " + indexName + " = " + indexEqual + "; " + indexName + " < " + indexMax + "; " + indexName + "++)";
return out;
}
}
std::string convertPy_js_Array(std::string theCode)
{
std::string out;
std::string indexName;
std::string indexEqual;
std::string indexMax;
if (InStr (theCode , ",")) 
{
std::vector<std::string> items21 = LoopParseFunc(theCode, " ");
for (size_t A_Index21 = 1; A_Index21 < items21.size() + 1; A_Index21++)
{
std::string A_LoopField21 = items21[A_Index21 - 1];
if (A_Index21 == 2) 
{
indexName = StrReplace ( A_LoopField21 , ";" , "" ) ;
}
if (A_Index21 == 4) 
{
indexEqual = ExtractDigits ( StrReplace ( A_LoopField21 , ";" , "" ) ) ;
}
if (A_Index21 == 5) 
{
indexMax = StrSplit ( StrSplit ( StrReplace ( A_LoopField21 , ";" , "" ) , "len(" , 2 ) , ")" , 1 ) + ".length";
}
}
out = "for (let " + StrReplace ( indexName , ":" , "" ) + " = " + StrReplace ( indexEqual , ":" , "" ) + "; " + StrReplace ( indexName , ":" , "" ) + " < " + StrReplace ( indexMax , ":" , "" ) + "; " + StrReplace ( indexName , ":" , "" ) + "++)";
return out;
}
else
{
std::vector<std::string> items22 = LoopParseFunc(theCode, " ");
for (size_t A_Index22 = 1; A_Index22 < items22.size() + 1; A_Index22++)
{
std::string A_LoopField22 = items22[A_Index22 - 1];
if (A_Index22 == 2) 
{
indexName = StrReplace ( A_LoopField22 , ";" , "" ) ;
}
if (A_Index22 == 4) 
{
indexEqual = "0";
indexMax = StrSplit ( StrSplit ( StrReplace ( A_LoopField22 , ";" , "" ) , "len(" , 2 ) , ")" , 1 ) + ".length";
}
}
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for (let " + indexName + " = " + indexEqual + "; " + indexName + " < " + indexMax + "; " + indexName + "++)";
return out;
}
}
std::string convertCpp_js_Array(std::string theCode)
{
std::string out;
std::string indexName;
std::string indexEqual;
std::string indexMax;
std::vector<std::string> items23 = LoopParseFunc(theCode, " ");
for (size_t A_Index23 = 1; A_Index23 < items23.size() + 1; A_Index23++)
{
std::string A_LoopField23 = items23[A_Index23 - 1];
if (A_Index23 == 3) 
{
indexName = StrReplace ( A_LoopField23 , ";" , "" ) ;
}
if (A_Index23 == 5) 
{
indexEqual = StrReplace ( A_LoopField23 , ";" , "" ) ;
}
if (A_Index23 == 8) 
{
indexMax = StrReplace ( A_LoopField23 , ";" , "" ) ;
}
}
indexMax = StrSplit ( indexMax , "." , 1 ) + ".length";
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for (let " + indexName + " = " + indexEqual + "; " + indexName + " < " + indexMax + "; " + indexName + "++)";
return out;
}
std::string convertCpp_py_Array(std::string theCode)
{
std::string out;
std::string indexName;
std::string indexEqual;
std::string indexMax;
std::vector<std::string> items24 = LoopParseFunc(theCode, " ");
for (size_t A_Index24 = 1; A_Index24 < items24.size() + 1; A_Index24++)
{
std::string A_LoopField24 = items24[A_Index24 - 1];
if (A_Index24 == 3) 
{
indexName = StrReplace ( A_LoopField24 , ";" , "" ) ;
}
if (A_Index24 == 5) 
{
indexEqual = StrReplace ( A_LoopField24 , ";" , "" ) ;
}
if (A_Index24 == 8) 
{
indexMax = StrSplit ( StrReplace ( A_LoopField24 , ";" , "" ) , "." , 1 ) ;
}
}
indexName = StrReplace ( indexName , ":" , "" ) ;
indexEqual = StrReplace ( indexEqual , ":" , "" ) ;
indexMax = StrReplace ( indexMax , ":" , "" ) ;
out = "for " + indexName + " in range(" + indexEqual + ", len(" + indexMax + ")):";
return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string transpileForLoop(std::string langToConvertTo, std::string langForLoopStyleOfUser, std::string TheCode)
{
std::string out;
bool isNormalLoop;
// Check if source and target languages are the same
if (langForLoopStyleOfUser == langToConvertTo) 
{
//theColon
if (langForLoopStyleOfUser == "py") 
{
if (!(InStr (TheCode , ":"))) 
{
TheCode = TheCode + ":";
return TheCode;
}
}
else
{
if (InStr (TheCode , ":")) 
{
TheCode = StrReplace ( TheCode , ":" , "" ) ;
return TheCode;
}
}
return TheCode;
}
if (Trim (TheCode) == "for (;;)") 
{
if (langToConvertTo!= "py") 
{
return "for (;;)";
}
else
{
return "while Ture:";
}
}
if (langForLoopStyleOfUser == "py") 
{
if (InStr (TheCode , "len(")) 
{
isNormalLoop = false;
}
else
{
isNormalLoop = true;
}
}
else
{
if (InStr (TheCode , ".")) 
{
isNormalLoop = false;
}
else
{
isNormalLoop = true;
}
}
if (isNormalLoop) 
{
if (langForLoopStyleOfUser == "py" && langToConvertTo == "cpp") 
{
out = convertPy_cpp_Normal ( TheCode ) ;
}
if (langForLoopStyleOfUser == "py" && langToConvertTo == "js") 
{
out = convertPy_js_Normal ( TheCode ) ;
}
if (langForLoopStyleOfUser == "js" && langToConvertTo == "cpp") 
{
out = convertJs_cpp_Normal ( TheCode ) ;
}
if (langForLoopStyleOfUser == "js" && langToConvertTo == "py") 
{
out = convertJs_py_Normal ( TheCode ) ;
}
if (langForLoopStyleOfUser == "cpp" && langToConvertTo == "py") 
{
out = convertCpp_py_Normal ( TheCode ) ;
}
if (langForLoopStyleOfUser == "cpp" && langToConvertTo == "js") 
{
out = convertCpp_js_Normal ( TheCode ) ;
}
}
else
{
if (langForLoopStyleOfUser == "py" && langToConvertTo == "cpp") 
{
out = convertPy_cpp_Array ( TheCode ) ;
}
if (langForLoopStyleOfUser == "py" && langToConvertTo == "js") 
{
out = convertPy_js_Array ( TheCode ) ;
}
if (langForLoopStyleOfUser == "js" && langToConvertTo == "cpp") 
{
out = convertJs_cpp_Array ( TheCode ) ;
}
if (langForLoopStyleOfUser == "js" && langToConvertTo == "py") 
{
out = convertJs_py_Array ( TheCode ) ;
}
if (langForLoopStyleOfUser == "cpp" && langToConvertTo == "py") 
{
out = convertCpp_py_Array ( TheCode ) ;
}
if (langForLoopStyleOfUser == "cpp" && langToConvertTo == "js") 
{
out = convertCpp_js_Array ( TheCode ) ;
}
}
return out;
}
// Helper function to create spaces
std::string spaces(int n)
{
std::string s = "";
if (n!= 0) 
{
for (int A_Index25 = 1; A_Index25<= n; ++A_Index25)
{
s += " ";
}
}
return s;
}
// Define the function to check odd spaces at the beginning
std::string CheckOddLeadingSpaces(std::string string123)
{
// Initialize a variable to count the spaces
int spaceCount = 0;
// Loop through the string one character at a time
std::vector<std::string> items26 = LoopParseFunc(string123);
for (size_t A_Index26 = 1; A_Index26 < items26.size() + 1; A_Index26++)
{
std::string A_LoopField26 = items26[A_Index26 - 1];
// Check if the current character is a space
if (A_LoopField26 == Chr (32)) 
{
spaceCount++;
}
else
{
// When we hit a non-space character, break the loop
break;
}
}
// Return true if the number of spaces is odd, false otherwise
std::string sdsfawasd = STR ( Mod ( spaceCount , 2 ) == 1 ) ;
//MsgBox, % sdsfawasd
return sdsfawasd;
}
std::string LTrim(std::string input)
{
std::string result = "";
bool foundNonSpace = false;
std::vector<std::string> items27 = LoopParseFunc(input);
for (size_t A_Index27 = 1; A_Index27 < items27.size() + 1; A_Index27++)
{
std::string A_LoopField27 = items27[A_Index27 - 1];
if (A_LoopField27!= " " || foundNonSpace) 
{
result += A_LoopField27;
foundNonSpace = true;
}
}
return result;
}
std::string getLastChar(std::string strippedString)
{
std::string lastChar;
std::vector<std::string> items28 = LoopParseFunc(strippedString);
for (size_t A_Index28 = 1; A_Index28 < items28.size() + 1; A_Index28++)
{
std::string A_LoopField28 = items28[A_Index28 - 1];
lastChar = A_LoopField28;
}
return lastChar;
}
std::string AddCurlyBraces(std::string pythonCode)
{
pythonCode = StrReplace ( pythonCode , BuildInVars("A_Tab") , "    " ) ;
std::string result = "";
int indentLevel = 0;
int indent;
std::string line;
std::string stripped;
std::vector<std::string> items29 = LoopParseFunc(pythonCode, "\n", "\r");
for (size_t A_Index29 = 1; A_Index29 < items29.size() + 1; A_Index29++)
{
std::string A_LoopField29 = items29[A_Index29 - 1];
line = A_LoopField29;
stripped = Trim ( line ) ;
if (stripped == "") 
{
result += line + "\n";
continue;
}
// Count leading spaces
indent = StrLen ( line ) - StrLen ( LTrim ( line ) ) ;
//MsgBox, % indent
// Close braces for unindents
for (int A_Index30 = 1;; A_Index30++)
{
if (indentLevel <= indent) 
{
break;
}
indentLevel -= 4;
result += spaces ( indentLevel ) + "}\n";
}
// Add opening brace for new blocks
if (getLastChar (stripped) == ":" && SubStr (StrLower (Trim (A_LoopField29)) , 1 , StrLen (StrLower (keyWordComment)))!= StrLower (keyWordComment)) 
{
result += SubStr ( line , 1 , -1 ) + " {\n";
indentLevel += 4;
}
else
{
result += line + "\n";
}
}
// Close any remaining open braces
for (int A_Index31 = 1;; A_Index31++)
{
if (indentLevel <= 0) 
{
break;
}
indentLevel -= 4;
result += spaces ( indentLevel ) + "}\n";
}
return result;
}
std::string RepeatSpaces(int count)
{
std::string spaces = "";
for (int A_Index32 = 1; A_Index32<= count; ++A_Index32)
{
spaces += Chr ( 32 ) ;
}
return spaces;
}
std::string indent_nested_curly_braces(std::string input_string, int modeCurlyBracesOn)
{
int indent_size = 4;
int current_indent = 0;
std::string result;
std::string trimmed_line;
std::string resultOut;
//MsgBox, % input_string
std::vector<std::string> items33 = LoopParseFunc(input_string, "\n", "\r");
for (size_t A_Index33 = 1; A_Index33 < items33.size() + 1; A_Index33++)
{
std::string A_LoopField33 = items33[A_Index33 - 1];
trimmed_line = Trim ( A_LoopField33 ) ;
if (trimmed_line == Chr (123)) 
{
result += Chr ( 32 ) + RepeatSpaces ( current_indent ) + trimmed_line + "\n";
current_indent = current_indent + indent_size;
}
else if (trimmed_line == Chr (125)) 
{
current_indent = current_indent - indent_size;
result += Chr ( 32 ) + RepeatSpaces ( current_indent ) + trimmed_line + "\n";
}
else
{
result += Chr ( 32 ) + RepeatSpaces ( current_indent ) + trimmed_line + "\n";
}
}
if (modeCurlyBracesOn == 0) 
{
std::string resultOut;
std::vector<std::string> items34 = LoopParseFunc(result, "\n", "\r");
for (size_t A_Index34 = 1; A_Index34 < items34.size() + 1; A_Index34++)
{
std::string A_LoopField34 = items34[A_Index34 - 1];
if (Trim (A_LoopField34)!= "{" && Trim (A_LoopField34)!= "}") 
{
resultOut += A_LoopField34 + "\n";
}
}
result = StringTrimRight(resultOut, 1);
}
else
{
// format curly braces in a K&R style
OneIndexedArray<std::string> lookIntoFurture;
std::vector<std::string> items35 = LoopParseFunc(result, "\n", "\r");
for (size_t A_Index35 = 1; A_Index35 < items35.size() + 1; A_Index35++)
{
std::string A_LoopField35 = items35[A_Index35 - 1];
lookIntoFurture.add(Trim(A_LoopField35));
}
lookIntoFurture.add(" ");
std::string resultOut;
int skipNext = 0;
std::vector<std::string> items36 = LoopParseFunc(result, "\n", "\r");
for (size_t A_Index36 = 1; A_Index36 < items36.size() + 1; A_Index36++)
{
std::string A_LoopField36 = items36[A_Index36 - 1];
skipNext--;
if (skipNext <= 0) 
{
skipNext = 0;
}
if (Trim (lookIntoFurture[A_Index36 + 1]) == "{") 
{
resultOut += A_LoopField36 + " {\n";
skipNext = 2;
}
if (skipNext == 0) 
{
resultOut += A_LoopField36 + "\n";
}
}
result = StringTrimRight(resultOut, 1);
OneIndexedArray<std::string> lookIntoFurture2;
std::vector<std::string> items37 = LoopParseFunc(result, "\n", "\r");
for (size_t A_Index37 = 1; A_Index37 < items37.size() + 1; A_Index37++)
{
std::string A_LoopField37 = items37[A_Index37 - 1];
lookIntoFurture2.add(Trim(A_LoopField37));
}
lookIntoFurture2.add(" ");
resultOut = "";
skipNext = 0;
std::string addSpacesAtTheBegginig;
std::vector<std::string> items38 = LoopParseFunc(result, "\n", "\r");
for (size_t A_Index38 = 1; A_Index38 < items38.size() + 1; A_Index38++)
{
std::string A_LoopField38 = items38[A_Index38 - 1];
skipNext--;
if (skipNext <= 0) 
{
skipNext = 0;
}
if (Trim (A_LoopField38) == "}" && Trim (lookIntoFurture2[A_Index38 + 1]) == "else {") 
{
skipNext = 2;
addSpacesAtTheBegginig = "";
std::vector<std::string> items39 = LoopParseFunc(A_LoopField38);
for (size_t A_Index39 = 1; A_Index39 < items39.size() + 1; A_Index39++)
{
std::string A_LoopField39 = items39[A_Index39 - 1];
if (A_LoopField39 == " ") 
{
if (A_LoopField39!= " ") 
{
break;
}
addSpacesAtTheBegginig += A_LoopField39;
}
}
resultOut += addSpacesAtTheBegginig + "} else {\n";
}
if (skipNext == 0) 
{
resultOut += A_LoopField38 + "\n";
}
}
result = StringTrimRight(resultOut, 1);
}
resultOut = "";
std::string ALoopField;
std::vector<std::string> items40 = LoopParseFunc(result, "\n", "\r");
for (size_t A_Index40 = 1; A_Index40 < items40.size() + 1; A_Index40++)
{
std::string A_LoopField40 = items40[A_Index40 - 1];
if (CheckOddLeadingSpaces (A_LoopField40) == "1") 
{
ALoopField = StringTrimLeft(A_LoopField40, 1);
resultOut += ALoopField + "\n";
}
else
{
resultOut += A_LoopField40 + "\n";
}
}
result = StringTrimRight(resultOut, 1);
// Return the result
return result;
}
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
//str keyWordComment defined at line 489
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
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string isItAPlusPlusOrMinusMinus(std::string str111, int mode)
{
// 2 modes
// 0 mode = detect only
// mode 1
// ++
// ++;
// --
// --;
std::string out;
std::string str1;
std::string str2;
std::string str11;
std::string str12;
std::string str13;
int numCountFix;
if (mode == 0) 
{
std::vector<std::string> items41 = LoopParseFunc(str111);
for (size_t A_Index41 = 1; A_Index41 < items41.size() + 1; A_Index41++)
{
std::string A_LoopField41 = items41[A_Index41 - 1];
numCountFix++;
}
std::vector<std::string> items42 = LoopParseFunc(str111);
for (size_t A_Index42 = 1; A_Index42 < items42.size() + 1; A_Index42++)
{
std::string A_LoopField42 = items42[A_Index42 - 1];
if (A_Index42 == numCountFix - 2) 
{
str11 = A_LoopField42;
}
if (A_Index42 == numCountFix - 1) 
{
str12 = A_LoopField42;
}
if (A_Index42 == numCountFix) 
{
str13 = A_LoopField42;
}
}
if (str11 == "+" && str12 == "+" && str13 == ";") 
{
return "detected";
}
if (str11 == "-" && str12 == "-" && str13 == ";") 
{
return "detected";
}
if (str12 == "+" && str13 == "+") 
{
return "detected";
}
if (str12 == "-" && str13 == "-") 
{
return "detected";
}
return "no";
}
if (mode == 1) 
{
std::vector<std::string> items43 = LoopParseFunc(str111);
for (size_t A_Index43 = 1; A_Index43 < items43.size() + 1; A_Index43++)
{
std::string A_LoopField43 = items43[A_Index43 - 1];
numCountFix++;
}
std::vector<std::string> items44 = LoopParseFunc(str111);
for (size_t A_Index44 = 1; A_Index44 < items44.size() + 1; A_Index44++)
{
std::string A_LoopField44 = items44[A_Index44 - 1];
if (A_Index44 == numCountFix - 2) 
{
str11 = A_LoopField44;
}
if (A_Index44 == numCountFix - 1) 
{
str12 = A_LoopField44;
}
if (A_Index44 == numCountFix) 
{
str13 = A_LoopField44;
}
}
if (str11 == "+" && str12 == "+" && str13 == ";") 
{
str111 = StringTrimRight(str111, 3);
if (langToTranspileTo == "py") 
{
str2 = str111 + " = " + Trim ( str111 ) + " + 1";
}
else
{
str2 = str111 + "++;";
}
}
if (str11 == "-" && str12 == "-" && str13 == ";") 
{
str111 = StringTrimRight(str111, 3);
if (langToTranspileTo == "py") 
{
str2 = str111 + " = " + Trim ( str111 ) + " - 1";
}
else
{
str2 = str111 + "--;";
}
}
if (str12 == "+" && str13 == "+") 
{
str111 = StringTrimRight(str111, 2);
if (langToTranspileTo == "py") 
{
str2 = str111 + " = " + Trim ( str111 ) + " + 1";
}
else
{
str2 = str111 + "++;";
}
}
if (str12 == "-" && str13 == "-") 
{
str111 = StringTrimRight(str111, 2);
if (langToTranspileTo == "py") 
{
str2 = str111 + " = " + Trim ( str111 ) + " - 1";
}
else
{
str2 = str111 + "--;";
}
}
out = str2;
return out;
}
return str111;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string fixFuncParamsHandleSpacesHELPER(int theINDEX, std::string str2FIXhelper)
{
if (theINDEX == 1) 
{
str2FIXhelper = RegExReplace ( str2FIXhelper , "\\b" + Trim ( keyWordArrayDefinition ) + "\\b" , "std::vector<std::string>" ) ;
}
if (theINDEX == 2) 
{
str2FIXhelper = RegExReplace ( str2FIXhelper , "\\b" + Trim ( keyWordArrayOfIntegersDefinition ) + "\\b" , "std::vector<int>" ) ;
}
if (theINDEX == 3) 
{
str2FIXhelper = RegExReplace ( str2FIXhelper , "\\b" + Trim ( keyWordArrayOfStringsDefinition ) + "\\b" , "std::vector<std::string>" ) ;
}
if (theINDEX == 4) 
{
str2FIXhelper = RegExReplace ( str2FIXhelper , "\\b" + Trim ( keyWordArrayOfFloatingPointNumbersDefinition ) + "\\b" , "std::vector<float>" ) ;
}
if (theINDEX == 5) 
{
str2FIXhelper = RegExReplace ( str2FIXhelper , "\\b" + Trim ( keyWordArrayOfBooleansDefinition ) + "\\b" , "std::vector<bool>" ) ;
}
if (theINDEX == 6) 
{
str2FIXhelper = RegExReplace ( str2FIXhelper , "\\b" + Trim ( keyWordINT ) + "\\b" , "int" ) ;
}
if (theINDEX == 7) 
{
str2FIXhelper = RegExReplace ( str2FIXhelper , "\\b" + Trim ( keyWordSTR ) + "\\b" , "std::string" ) ;
}
if (theINDEX == 8) 
{
str2FIXhelper = RegExReplace ( str2FIXhelper , "\\b" + Trim ( keyWordBOOL ) + "\\b" , "bool" ) ;
}
if (theINDEX == 9) 
{
str2FIXhelper = RegExReplace ( str2FIXhelper , "\\b" + Trim ( keyWordINT8 ) + "\\b" , "int8_t" ) ;
}
if (theINDEX == 10) 
{
str2FIXhelper = RegExReplace ( str2FIXhelper , "\\b" + Trim ( keyWordINT16 ) + "\\b" , "int8_t" ) ;
}
if (theINDEX == 11) 
{
str2FIXhelper = RegExReplace ( str2FIXhelper , "\\b" + Trim ( keyWordINT32 ) + "\\b" , "int32_t" ) ;
}
if (theINDEX == 12) 
{
str2FIXhelper = RegExReplace ( str2FIXhelper , "\\b" + Trim ( keyWordINT64 ) + "\\b" , "long long" ) ;
}
if (theINDEX == 13) 
{
str2FIXhelper = RegExReplace ( str2FIXhelper , "\\b" + Trim ( keyWordFLOAT ) + "\\b" , "float" ) ;
}
return str2FIXhelper;
}
int getNumOfSpacesHelperFunc(std::string theTEXTtoGetTheSpaceCount)
{
int NUMofSpaces = 0;
std::vector<std::string> items45 = LoopParseFunc(theTEXTtoGetTheSpaceCount);
for (size_t A_Index45 = 1; A_Index45 < items45.size() + 1; A_Index45++)
{
std::string A_LoopField45 = items45[A_Index45 - 1];
if (A_LoopField45 == " ") 
{
NUMofSpaces++;
}
}
return NUMofSpaces;
}
std::string fixFuncParamsHandleSpaces(std::string str2FIX)
{
OneIndexedArray<int> holdDoneIdexes;
holdDoneIdexes.add(0);
holdDoneIdexes.add(0);
holdDoneIdexes.add(0);
holdDoneIdexes.add(0);
holdDoneIdexes.add(0);
holdDoneIdexes.add(0);
holdDoneIdexes.add(0);
holdDoneIdexes.add(0);
holdDoneIdexes.add(0);
holdDoneIdexes.add(0);
holdDoneIdexes.add(0);
holdDoneIdexes.add(0);
holdDoneIdexes.add(0);
OneIndexedArray<std::string> holdAllKeyWords;
holdAllKeyWords.add(keyWordArrayDefinition);
holdAllKeyWords.add(keyWordArrayOfIntegersDefinition);
holdAllKeyWords.add(keyWordArrayOfStringsDefinition);
holdAllKeyWords.add(keyWordArrayOfFloatingPointNumbersDefinition);
holdAllKeyWords.add(keyWordArrayOfBooleansDefinition);
holdAllKeyWords.add(keyWordINT);
holdAllKeyWords.add(keyWordSTR);
holdAllKeyWords.add(keyWordBOOL);
holdAllKeyWords.add(keyWordINT8);
holdAllKeyWords.add(keyWordINT16);
holdAllKeyWords.add(keyWordINT32);
holdAllKeyWords.add(keyWordINT64);
holdAllKeyWords.add(keyWordFLOAT);
int tempSIZEholder;
int indexHolder;
for (int A_Index46 = 1; A_Index46<= INT ( holdAllKeyWords[0] ) ; ++A_Index46)
{
tempSIZEholder = 0;
for (int A_Index47 = 1; A_Index47<= INT ( holdAllKeyWords[0] ) ; ++A_Index47)
{
if (holdDoneIdexes[A_Index47] == 0 && getNumOfSpacesHelperFunc (holdAllKeyWords[A_Index47]) >= tempSIZEholder) 
{
tempSIZEholder = getNumOfSpacesHelperFunc ( holdAllKeyWords[A_Index47] ) ;
indexHolder = A_Index47;
}
}
holdDoneIdexes[indexHolder] = indexHolder;
str2FIX = fixFuncParamsHandleSpacesHELPER ( indexHolder , str2FIX ) ;
}
return str2FIX;
}
// path.path.path:propName1[str],propName2[bool],propName3[str array]|path.path.path:propName1[str],propName2[bool],propName3[str array]
std::string OSPstrArrayStrALLobjInOSP = "";
std::string HoldOSPdethodNamePath = "";
std::string findTypeOfOSPprop(std::string fullARRAYstr, std::string FromPath)
{
std::string outType = "";
// if the fullARRAYstr is in this format
// path.path.path:propName1[str],propName2[bool],propName3[str array]|path.path.path:propName1[str],propName2[bool],propName3[str array]
std::string outFormat = "";
std::string outFormatHELP1 = "";
std::string outFormatHELP2 = "";
std::vector<std::string> items48 = LoopParseFunc(fullARRAYstr, "|");
for (size_t A_Index48 = 1; A_Index48 < items48.size() + 1; A_Index48++)
{
std::string A_LoopField48 = items48[A_Index48 - 1];
if (Trim (A_LoopField48)!= "") 
{
outFormatHELP1 = StrSplit ( A_LoopField48 , ":" , 1 ) ;
outFormatHELP2 = StrSplit ( A_LoopField48 , ":" , 2 ) ;
std::vector<std::string> items49 = LoopParseFunc(outFormatHELP2, ",");
for (size_t A_Index49 = 1; A_Index49 < items49.size() + 1; A_Index49++)
{
std::string A_LoopField49 = items49[A_Index49 - 1];
outFormat += outFormatHELP1 + "." + A_LoopField49 + "|";
}
}
}
outFormat = StringTrimRight(outFormat, 1);
std::vector<std::string> items50 = LoopParseFunc(outFormat, "|");
for (size_t A_Index50 = 1; A_Index50 < items50.size() + 1; A_Index50++)
{
std::string A_LoopField50 = items50[A_Index50 - 1];
if (Trim (A_LoopField50)!= "") 
{
if (StrSplit (Trim (A_LoopField50) , "[" , 1) == Trim (FromPath)) 
{
outType = StrSplit ( Trim ( A_LoopField50 ) , "[" , 2 ) ;
outType = StringTrimRight(outType, 1);
break;
}
}
}
if (outType == "vector<int>") 
{
outType = "std::vector<int>&";
}
else if (outType == "vector<string>") 
{
outType = "std::vector<std::string>&";
}
else if (outType == "vector<string>") 
{
outType = "std::vector<std::string>&";
}
else if (outType == "vector<float>") 
{
outType = "std::vector<float>&";
}
else if (outType == "vector<bool>") 
{
outType = "std::vector<bool>&";
}
else if (outType == Trim (keyWordINT)) 
{
outType = "int";
}
else if (outType == Trim (keyWordSTR)) 
{
outType = "std::string";
}
else if (outType == Trim (keyWordFLOAT)) 
{
outType = "float";
}
else if (outType == Trim (keyWordBOOL)) 
{
outType = "bool";
}
else if (outType == Trim (keyWordINT8)) 
{
outType = "int8_t";
}
else if (outType == Trim (keyWordINT16)) 
{
outType = "int16_t";
}
else if (outType == Trim (keyWordINT32)) 
{
outType = "int32_t";
}
else if (outType == Trim (keyWordINT64)) 
{
outType = "int64_t";
}
return outType;
}
std::string REMOVELastSTRfromDOT(std::string THESTR)
{
std::string THESTRout = "";
if (Trim (THESTR) == "") 
{
return "";
}
int count12345;
std::vector<std::string> items51 = LoopParseFunc(THESTR, ".");
for (size_t A_Index51 = 1; A_Index51 < items51.size() + 1; A_Index51++)
{
std::string A_LoopField51 = items51[A_Index51 - 1];
count12345++;
}
std::vector<std::string> items52 = LoopParseFunc(THESTR, ".");
for (size_t A_Index52 = 1; A_Index52 < items52.size() + 1; A_Index52++)
{
std::string A_LoopField52 = items52[A_Index52 - 1];
if (count12345 == A_Index52) 
{
break;
}
else
{
THESTRout += Trim ( A_LoopField52 ) + ".";
}
}
THESTRout = StringTrimRight(THESTRout, 1);
return THESTRout;
}
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
std::string replaceTheOSPpathsPY_JS(std::string theSTR123, std::string ALoopFieldIN)
{
if (Trim (theSTR123) == "") 
{
return "";
}
if (Trim (ALoopFieldIN) == "") 
{
return "";
}
std::string type = "";
std::string theSTR123out = "";
std::string ALoopField = "";
std::string ALoopField1 = "";
std::string ALoopField11 = "";
if (InStr (ALoopFieldIN , "[")) 
{
// ALoopFieldIN
// animalsKingdom.animals.Dog.typeOf2[2]
ALoopField = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 1 ) ;
ALoopField1 = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 1 ) ;
ALoopField11 = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 2 ) ;
ALoopField1 = REMOVELastSTRfromDOT ( ALoopField1 ) + "[" + ALoopField11;
// REMOVELastSTRfromDOT(param1)
theSTR123 = StrReplace ( theSTR123 , Trim ( ALoopField ) , "OSPHTVMOSP_" + StrReplace ( ALoopField1 , "." , "_" ) ) ;
}
else
{
ALoopField = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 1 ) ;
ALoopField1 = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 2 ) ;
ALoopField1 = REMOVELastSTRfromDOT ( StrSplit ( Trim ( ALoopFieldIN ) , "]" , 1 ) ) ;
ALoopField1 = "[" + Trim ( StrSplit ( ALoopField1 , "[" , 2 ) ) + "]";
theSTR123 = StrReplace ( theSTR123 , Trim ( ALoopFieldIN ) , "OSPHTVMOSP_" + StrReplace ( ALoopFieldIN , "." , "_" ) ) ;
}
//this__OSP__this
theSTR123 = RegExReplace ( theSTR123 , "\\bthis\\b" , "this__OSP__this[0]" ) ;
theSTR123 = StrReplace ( theSTR123 , "OSPHTVMOSP_OSPHTVMOSP_" , "OSPHTVMOSP_" ) ;
return theSTR123;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string replaceTheOSPpathsLEFT(std::string theSTR123, std::string ALoopFieldIN)
{
if (Trim (theSTR123) == "") 
{
return "";
}
if (Trim (ALoopFieldIN) == "") 
{
return "";
}
std::string type = "";
std::string theSTR123out = "";
std::string ALoopField = "";
std::string ALoopField1 = "";
std::string ALoopField11 = "";
if (InStr (ALoopFieldIN , "[")) 
{
// ALoopFieldIN
// animalsKingdom.animals.Dog.typeOf2[2]
ALoopField = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 1 ) ;
ALoopField1 = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 1 ) ;
ALoopField11 = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 2 ) ;
ALoopField1 = REMOVELastSTRfromDOT ( ALoopField1 ) + "[" + ALoopField11;
// REMOVELastSTRfromDOT(param1)
theSTR123 = StrReplace ( theSTR123 , Trim ( ALoopField ) , "OSPHTVMOSP_" + StrReplace ( ALoopField1 , "." , "_" ) ) ;
}
else
{
ALoopField = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 1 ) ;
ALoopField1 = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 2 ) ;
ALoopField1 = REMOVELastSTRfromDOT ( StrSplit ( Trim ( ALoopFieldIN ) , "]" , 1 ) ) ;
ALoopField1 = "[" + Trim ( StrSplit ( ALoopField1 , "[" , 2 ) ) + "]";
theSTR123 = StrReplace ( theSTR123 , Trim ( ALoopFieldIN ) , "OSPHTVMOSP_" + StrReplace ( ALoopFieldIN , "." , "_" ) ) ;
}
//this__OSP__this
theSTR123 = RegExReplace ( theSTR123 , "\\bthis\\b" , "std::any_cast<std::string>((*this__OSP__this)[0])" ) ;
theSTR123 = StrReplace ( theSTR123 , "OSPHTVMOSP_OSPHTVMOSP_" , "OSPHTVMOSP_" ) ;
return theSTR123;
}
std::string replaceTheOSPpathsRIGHT(std::string theSTR123, std::string ALoopFieldIN)
{
if (Trim (theSTR123) == "") 
{
return "";
}
if (Trim (ALoopFieldIN) == "") 
{
return "";
}
std::string type = "";
std::string theSTR123out = "";
std::string ALoopField = "";
std::string ALoopField1 = "";
std::string ALoopField11 = "";
if (InStr (ALoopFieldIN , "[")) 
{
// ALoopFieldIN
// animalsKingdom.animals.Dog.typeOf2[2]
ALoopField = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 1 ) ;
ALoopField1 = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 1 ) ;
ALoopField11 = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 2 ) ;
ALoopField1 = REMOVELastSTRfromDOT ( ALoopField1 ) + "[" + ALoopField11;
// REMOVELastSTRfromDOT(param1)
type = findTypeOfOSPprop ( OSPstrArrayStrALLobjInOSP , ALoopField ) ;
//MsgBox, % type
theSTR123 = StrReplace ( theSTR123 , Trim ( ALoopField ) , "std::any_cast<" + type + ">(OSPHTVMOSP_" + StrReplace ( ALoopField1 , "." , "_" ) + ")" ) ;
}
else
{
ALoopField = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 1 ) ;
ALoopField1 = StrSplit ( Trim ( ALoopFieldIN ) , "[" , 2 ) ;
ALoopField1 = REMOVELastSTRfromDOT ( StrSplit ( Trim ( ALoopFieldIN ) , "]" , 1 ) ) ;
ALoopField1 = "[" + Trim ( StrSplit ( ALoopField1 , "[" , 2 ) ) + "]";
theSTR123 = StrReplace ( theSTR123 , Trim ( ALoopFieldIN ) , "OSPHTVMOSP_" + StrReplace ( ALoopFieldIN , "." , "_" ) ) ;
}
//this__OSP__this
theSTR123 = RegExReplace ( theSTR123 , "\\bthis\\b" , "std::any_cast<std::string>((*this__OSP__this)[0])" ) ;
theSTR123 = StrReplace ( theSTR123 , "OSPHTVMOSP_OSPHTVMOSP_" , "OSPHTVMOSP_" ) ;
return theSTR123;
}
std::string CheckStringPosition(std::string text, std::string target, std::string reference)
{
std::string posReference = SubStr ( text , 1 , StrLen ( reference ) ) ;
std::string posTarget = SubStr ( text , 1 , StrLen ( target ) ) ;
// Check if both strings are found (not using InStr)
if (posReference!= "" && posTarget!= "") 
{
// Manually find the positions of the target and reference
posTarget = RegExMatch ( text , target ) ;
posReference = RegExMatch ( text , reference ) ;
// Compare positions of target and reference
if (posTarget < posReference) 
{
return "left";
}
else if (posTarget > posReference) 
{
return "not left";
}
else
{
return "uuh";
}
}
else
{
return "One or both strings not found.";
}
return "huh";
}
std::string getIndexOfTheStrArrayStrOST(std::string ALoopField, std::string theSringOSPlineARRAYstrstrSTR)
{
std::vector<std::string> items53 = LoopParseFunc(theSringOSPlineARRAYstrstrSTR, "|");
for (size_t A_Index53 = 1; A_Index53 < items53.size() + 1; A_Index53++)
{
std::string A_LoopField53 = items53[A_Index53 - 1];
if (Trim (StrSplit (A_LoopField53 , ":" , 1)) == Trim (ALoopField)) 
{
return STR ( A_Index53 ) ;
}
}
return "0";
}
std::string parserOSPgloabl(std::string theSringOSPline, std::string str123)
{
std::string str_1 = "";
std::string str_2 = "";
std::string str_3 = "";
std::string str_4 = "";
std::string str_5 = "";
std::string str_6 = "";
std::string HELPHoldOSPdethodNamePath = "";
HELPHoldOSPdethodNamePath = StringTrimRight(HoldOSPdethodNamePath, 1);
std::vector<std::string> items54 = LoopParseFunc(theSringOSPline, "|");
for (size_t A_Index54 = 1; A_Index54 < items54.size() + 1; A_Index54++)
{
std::string A_LoopField54 = items54[A_Index54 - 1];
str_1 += Trim ( StrSplit ( A_LoopField54 , ":" , 1 ) ) + "\n";
str_5 = Trim ( StrSplit ( A_LoopField54 , ":" , 1 ) ) ;
str_6 = Trim ( StrSplit ( A_LoopField54 , ":" , 2 ) ) ;
std::vector<std::string> items55 = LoopParseFunc(str_6, ",");
for (size_t A_Index55 = 1; A_Index55 < items55.size() + 1; A_Index55++)
{
std::string A_LoopField55 = items55[A_Index55 - 1];
str_1 += str_5 + "." + Trim ( StrSplit ( A_LoopField55 , "[" , 1 ) ) + "[" + STR ( A_Index55 ) + "]\n";
}
}
str_1 += StrReplace ( HELPHoldOSPdethodNamePath , "|" , "\n" ) ;
std::string shortestLine;
std::string currentLine;
int currentLength;
int minLength;
std::string tempStr;
// Sorting by repeatedly finding and appending the shortest line
for (int A_Index56 = 1;; A_Index56++)
{
// Initialize variables to track the shortest line in this pass
shortestLine = "";
minLength = 999999;
// Find the shortest line in str_1
std::vector<std::string> items57 = LoopParseFunc(str_1, "\n", "\r");
for (size_t A_Index57 = 1; A_Index57 < items57.size() + 1; A_Index57++)
{
std::string A_LoopField57 = items57[A_Index57 - 1];
currentLine = A_LoopField57;
currentLength = StrLen ( currentLine ) ;
if (currentLength < minLength) 
{
minLength = currentLength;
shortestLine = currentLine;
}
}
// If no shortest line is found, break (str_1 is empty)
if (shortestLine == "") 
{
break;
}
// Add the shortest line to the sorted result
str_2 += shortestLine + "\n";
// Rebuild str_1 without the shortest line
tempStr = "";
std::vector<std::string> items58 = LoopParseFunc(str_1, "\n", "\r");
for (size_t A_Index58 = 1; A_Index58 < items58.size() + 1; A_Index58++)
{
std::string A_LoopField58 = items58[A_Index58 - 1];
if (A_LoopField58!= shortestLine) 
{
tempStr += A_LoopField58 + "\n";
}
}
tempStr = StringTrimRight(tempStr, 1);
str_1 = tempStr;
}
// Trim the final trailing newline from str_2
str_2 = StringTrimRight(str_2, 1);
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Initialize an empty result for the reversed lines
std::string reversedStr = "";
// Count the number of lines
int lineCount = 0;
int index;
int lineNum;
std::vector<std::string> items59 = LoopParseFunc(str_2, "\n", "\r");
for (size_t A_Index59 = 1; A_Index59 < items59.size() + 1; A_Index59++)
{
std::string A_LoopField59 = items59[A_Index59 - 1];
lineCount++;
}
// Reverse the order by re-parsing and appending lines in reverse order
for (int A_Index60 = 1; A_Index60<= lineCount; ++A_Index60)
{
// Inner loop to find the (lineCount - A_Index60 + 1)-th line
index = lineCount - A_Index60 + 1;
currentLine = "";
lineNum = 0;
std::vector<std::string> items61 = LoopParseFunc(str_2, "\n", "\r");
for (size_t A_Index61 = 1; A_Index61 < items61.size() + 1; A_Index61++)
{
std::string A_LoopField61 = items61[A_Index61 - 1];
lineNum++;
if (lineNum == index) 
{
currentLine = A_LoopField61;
break;
}
}
// Append the line in reverse order
reversedStr += currentLine + "\n";
}
// Trim the final trailing newline
str_2 = StringTrimRight(reversedStr, 1);
// Display the sorted result
//MsgBox, % str_2
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//CheckStringPosition(text, target, reference)
std::string ALoopField = "";
std::string ALoopField1 = "";
std::vector<std::string> items62 = LoopParseFunc(str_2, "\n", "\r");
for (size_t A_Index62 = 1; A_Index62 < items62.size() + 1; A_Index62++)
{
std::string A_LoopField62 = items62[A_Index62 - 1];
if (langToTranspileTo == "cpp") 
{
if (Trim (A_LoopField62)!= "") 
{
if (InStr (str123 , " += ")) 
{
str6 = " += ";
str1 = "";
str2 = "";
str3 = "";
str4 = "";
str5 = "";
str1 = Trim ( StrSplit ( str123 , str6 , 1 ) ) ;
str2 = Trim ( StrSplit ( str123 , str6 , 2 ) ) ;
str3 = Trim ( replaceTheOSPpathsLEFT ( str1 , A_LoopField62 ) ) ;
str4 = Trim ( replaceTheOSPpathsRIGHT ( str2 , A_LoopField62 ) ) ;
str5 = str3 + str6 + str4;
str123 = Trim ( str5 ) ;
}
else if (InStr (str123 , " = ")) 
{
str6 = " = ";
str1 = "";
str2 = "";
str3 = "";
str4 = "";
str5 = "";
str1 = Trim ( StrSplit ( str123 , str6 , 1 ) ) ;
str2 = Trim ( StrSplit ( str123 , str6 , 2 ) ) ;
str3 = Trim ( replaceTheOSPpathsLEFT ( str1 , A_LoopField62 ) ) ;
str4 = Trim ( replaceTheOSPpathsRIGHT ( str2 , A_LoopField62 ) ) ;
str5 = str3 + str6 + str4;
str123 = Trim ( str5 ) ;
}
else if (InStr (str123 , " -= ")) 
{
str6 = " -= ";
str1 = "";
str2 = "";
str3 = "";
str4 = "";
str5 = "";
str1 = Trim ( StrSplit ( str123 , str6 , 1 ) ) ;
str2 = Trim ( StrSplit ( str123 , str6 , 2 ) ) ;
str3 = Trim ( replaceTheOSPpathsLEFT ( str1 , A_LoopField62 ) ) ;
str4 = Trim ( replaceTheOSPpathsRIGHT ( str2 , A_LoopField62 ) ) ;
str5 = str3 + str6 + str4;
str123 = Trim ( str5 ) ;
}
else if (InStr (str123 , " *= ")) 
{
str6 = " *= ";
str1 = "";
str2 = "";
str3 = "";
str4 = "";
str5 = "";
str1 = Trim ( StrSplit ( str123 , str6 , 1 ) ) ;
str2 = Trim ( StrSplit ( str123 , str6 , 2 ) ) ;
str3 = Trim ( replaceTheOSPpathsLEFT ( str1 , A_LoopField62 ) ) ;
str4 = Trim ( replaceTheOSPpathsRIGHT ( str2 , A_LoopField62 ) ) ;
str5 = str3 + str6 + str4;
str123 = Trim ( str5 ) ;
}
else if (InStr (str123 , " /= ")) 
{
str6 = " /= ";
str1 = "";
str2 = "";
str3 = "";
str4 = "";
str5 = "";
str1 = Trim ( StrSplit ( str123 , str6 , 1 ) ) ;
str2 = Trim ( StrSplit ( str123 , str6 , 2 ) ) ;
str3 = Trim ( replaceTheOSPpathsLEFT ( str1 , A_LoopField62 ) ) ;
str4 = Trim ( replaceTheOSPpathsRIGHT ( str2 , A_LoopField62 ) ) ;
str5 = str3 + str6 + str4;
str123 = Trim ( str5 ) ;
}
else
{
str123 = replaceTheOSPpathsRIGHT ( str123 , A_LoopField62 ) ;
}
//;;;;
}
}
else
{
if (Trim (A_LoopField62)!= "") 
{
str123 = replaceTheOSPpathsPY_JS ( str123 , A_LoopField62 ) ;
}
}
}
return str123;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string expressionParserTranspiler(std::string expression)
{
if (forLoopLang == "cpp") 
{
expression = RegExReplace ( expression , "\\b" + Trim ( keyWordINT ) + "\\b" , "int" ) ;
}
expression = StrReplace ( expression , " " + keyWordAdditionOperator + " " , " + " ) ;
expression = StrReplace ( expression , " " + keyWordConcatenationOperator + " " , " + " ) ;
expression = StrReplace ( expression , " " + keyWordEqualOperator + " " , " == " ) ;
if (langToTranspileTo == "py") 
{
expression = RegExReplace ( expression , "!([\\w]+)" , "not $1" ) ;
}
if (langToTranspileTo == "py") 
{
expression = RegExReplace ( expression , "\\b" + keyWordNotOperator + "\\b" , "not" ) ;
}
else
{
expression = RegExReplace ( expression , "\\b" + keyWordNotOperator + "\\b" , "!" ) ;
}
expression = StrReplace ( expression , " " + keyWordGreaterThanOperator + " " , " > " ) ;
expression = StrReplace ( expression , " " + keyWordLessThanOperator + " " , " < " ) ;
expression = StrReplace ( expression , " " + keyWordGreaterThanOrEqualToOperator + " " , " >= " ) ;
expression = StrReplace ( expression , " " + keyWordLessThanOrEqualToOperator + " " , " <= " ) ;
if (langToTranspileTo == "py") 
{
expression = StrReplace ( expression , " " + keyWordOrOperator + " " , " or " ) ;
}
else
{
expression = StrReplace ( expression , " " + keyWordOrOperator + " " , " || " ) ;
}
if (langToTranspileTo == "py") 
{
expression = StrReplace ( expression , " " + keyWordAndOperator + " " , " and " ) ;
}
else
{
expression = StrReplace ( expression , " " + keyWordAndOperator + " " , " && " ) ;
}
expression = StrReplace ( expression , " " + keyWordNotEqualToOperator + " " , " != " ) ;
expression = StrReplace ( expression , " not= " , " != " ) ;
if (langToTranspileTo == "py") 
{
// Python-specific replacements
expression = RegExReplace ( expression , "\\b" + keyWordTrue + "\\b" , "True" ) ;
expression = RegExReplace ( expression , "\\b" + keyWordFalse + "\\b" , "False" ) ;
expression = RegExReplace ( expression , "\\bnull\\b" , "None" ) ;
expression = StrReplace ( expression , "{}" , "[]" ) ;
expression = RegExReplace ( expression , "\\b" + keyWordErrorMsg + "\\b" , "Exception" ) ;
expression = StrReplace ( expression , keyWordArrayAppend , ".append" ) ;
expression = StrReplace ( expression , keyWordArrayPop , ".pop" ) ;
expression = RegExReplace ( expression , "(\\w+)\\" + keyWordArrayInsert + "\\(([^,]+), ([^)]+)\\)" , "$1.insert($2, $3)" ) ;
expression = RegExReplace ( expression , "(\\w+)\\" + keyWordArrayRemove + "\\(([^)]+)\\)" , "$1.remove($2)" ) ;
expression = RegExReplace ( expression , "(\\w+)\\" + keyWordArrayIndexOf + "\\(([^)]+)\\)" , "$1.index($2) if $2 in $1 else -1" ) ;
expression = StrReplace ( expression , ") and (" , " and " ) ;
expression = StrReplace ( expression , ") or (" , " or " ) ;
if (InStr (expression , keyWordArraySize)) 
{
std::string pattern1 = "(\\w{1,1})\\" + keyWordArraySize;
std::string pattern2 = "(\\w+)\\" + keyWordArraySize;
int result2 = RegExMatch ( expression , pattern1 ) ;
int result1 = RegExMatch ( expression , pattern2 ) ;
std::string concatResults;
std::vector<std::string> items63 = LoopParseFunc(expression);
for (size_t A_Index63 = 1; A_Index63 < items63.size() + 1; A_Index63++)
{
std::string A_LoopField63 = items63[A_Index63 - 1];
if (A_Index63 >= result1 && A_Index63 <= result2) 
{
concatResults += A_LoopField63;
}
}
expression = StrReplace ( expression , concatResults + "." , "." ) ;
expression = StrReplace ( expression , keyWordArraySize , "len(" + concatResults + ")" ) ;
expression = StrReplace ( expression , ")()" , ")" ) ;
}
}
else if (langToTranspileTo == "js") 
{
// JavaScript-specific replacements
expression = RegExReplace ( expression , "\\b" + keyWordTrue + "\\b" , "true" ) ;
expression = RegExReplace ( expression , "\\b" + keyWordFalse + "\\b" , "false" ) ;
expression = RegExReplace ( expression , "\\bNone\\b" , "null" ) ;
expression = StrReplace ( expression , "{}" , "[]" ) ;
expression = RegExReplace ( expression , "\\b" + keyWordErrorMsg + "\\b" , "new Error" ) ;
expression = StrReplace ( expression , keyWordArrayAppend , ".push" ) ;
expression = StrReplace ( expression , keyWordArrayPop , ".pop" ) ;
expression = StrReplace ( expression , keyWordArraySize , ".length" ) ;
expression = RegExReplace ( expression , "(\\w+)\\" + keyWordArrayInsert + "\\(([^,]+), ([^)]+)\\)" , "$1.splice($2, 0, $3)" ) ;
expression = RegExReplace ( expression , "(\\w+)\\" + keyWordArrayRemove + "\\(([^)]+)\\)" , "$1.splice($1.indexOf($2), 1)" ) ;
expression = RegExReplace ( expression , "(\\w+)\\" + keyWordArrayIndexOf + "\\(([^)]+)\\)" , "$1.includes($2) ? $1.indexOf($2) : -1" ) ;
expression = StrReplace ( expression , ") && (" , " && " ) ;
expression = StrReplace ( expression , ") || (" , " || " ) ;
}
else if (langToTranspileTo == "cpp") 
{
// C++-specific replacements
expression = RegExReplace ( expression , "\\b" + theCppVarForErrors + "\\b" , theCppVarForErrors + ".what()" ) ;
expression = RegExReplace ( expression , "\\b" + keyWordTrue + "\\b" , "true" ) ;
expression = RegExReplace ( expression , "\\b" + keyWordFalse + "\\b" , "false" ) ;
expression = RegExReplace ( expression , "\\bnull\\b" , Chr ( 34 ) + Chr ( 34 ) ) ;
expression = RegExReplace ( expression , "\\bNone\\b" , Chr ( 34 ) + Chr ( 34 ) ) ;
expression = StrReplace ( expression , "[]" , "{}" ) ;
expression = RegExReplace ( expression , "\\b" + keyWordErrorMsg + "\\b" , "std::runtime_error" ) ;
expression = StrReplace ( expression , keyWordArrayAppend , ".push_back" ) ;
expression = StrReplace ( expression , keyWordArrayPop , ".pop_back" ) ;
expression = StrReplace ( expression , keyWordArraySize , ".size" ) ;
expression = RegExReplace ( expression , "(\\w+)\\" + keyWordArrayInsert + "\\(([^,]+), ([^)]+)\\)" , "$1.insert($1.begin() + $2, $3)" ) ;
expression = RegExReplace ( expression , "(\\w+)\\" + keyWordArrayRemove + "\\(([^)]+)\\)" , "$1.erase(std::remove($1.begin(), $1.end(), $2), $1.end())" ) ;
expression = RegExReplace ( expression , "(\\w+)\\" + keyWordArrayIndexOf + "\\(([^)]+)\\)" , "std::find($1.begin(), $1.end(), $2) != $1.end() ? std::find($1.begin(), $1.end(), $2) - $1.begin() : -1" ) ;
expression = StrReplace ( expression , ") && (" , " && " ) ;
expression = StrReplace ( expression , ") || (" , " || " ) ;
}
expression = StrReplace ( expression , ".length()" , ".length" ) ;
expression = StrReplace ( expression , + " " + Trim ( keyWordVariablesAssignmentOperator ) + " " , " = " ) ;
return expression;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void compiler()
{
std::string params = GetParams ( ) ;
if (params == "") 
{
print(str10 + "Usage: HTVM <yourCodeFileName.yourExtension> <HT-instructions.txt> [optional LangToTranspileTo]\n\nOptions:\n  <yourCodeFileName.yourExtension>  The source code file to transpile.\n  <HT-instructions.txt>              The instructions file for transpilation.\n  [LangToTranspileTo]                Optional: Specify the target language (cpp, py, js).\n\nExample:\n  HTVM main.ht HT-instructions.txt cpp\n");
ExitApp();
}
int linesFixBugBUGbugBUG = 0;
std::vector<std::string> items64 = LoopParseFunc(params, "\n", "\r");
for (size_t A_Index64 = 1; A_Index64 < items64.size() + 1; A_Index64++)
{
std::string A_LoopField64 = items64[A_Index64 - 1];
linesFixBugBUGbugBUG++;
}
if (linesFixBugBUGbugBUG < 2) 
{
print(std::string("You need at leats 2 params"));
print(str10 + "Usage: HTVM <yourCodeFileName.yourExtension> <HT-instructions.txt> [optional LangToTranspileTo]\n\nOptions:\n  <yourCodeFileName.yourExtension>  The source code file to transpile.\n  <HT-instructions.txt>              The instructions file for transpilation.\n  [LangToTranspileTo]                Optional: Specify the target language (cpp, py, js).\n\nExample:\n  HTVM main.ht HT-instructions.txt cpp\n");
ExitApp();
}
int optionalLangToTranspileTo = 0;
std::vector<std::string> items65 = LoopParseFunc(params, "\n", "\r");
for (size_t A_Index65 = 1; A_Index65 < items65.size() + 1; A_Index65++)
{
std::string A_LoopField65 = items65[A_Index65 - 1];
if (A_Index65 == 1) 
{
print(A_LoopField65);
filePathOfCode = Trim ( A_LoopField65 ) ;
//MsgBox, % filePathOfCode
//code := FileRead(filePathOfCode)
code = FileRead(filePathOfCode);
//MsgBox, % code
}
if (A_Index65 == 2) 
{
print(A_LoopField65);
instructions = FileRead(A_LoopField65);
}
if (A_Index65 == 3) 
{
optionalLangToTranspileTo = 1;
langToTranspileTo = Trim ( A_LoopField65 ) ;
}
}
//MsgBox, % code
std::vector<std::string> items66 = LoopParseFunc(instructions, "\n", "\r");
for (size_t A_Index66 = 1; A_Index66 < items66.size() + 1; A_Index66++)
{
std::string A_LoopField66 = items66[A_Index66 - 1];
if (A_Index66 == 1) 
{
if (optionalLangToTranspileTo == 0) 
{
langToTranspileTo = Trim ( A_LoopField66 ) ;
}
}
if (A_Index66 == 2) 
{
fileExtention = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 3) 
{
keyWordsCommands = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 4) 
{
keyWordINT = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 5) 
{
keyWordSTR = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 6) 
{
keyWordBOOL = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 7) 
{
keyWordFLOAT = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 8) 
{
keyWordINT8 = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 9) 
{
keyWordINT16 = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 10) 
{
keyWordINT32 = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 11) 
{
keyWordINT64 = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 12) 
{
keyWordIF = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 13) 
{
keyWordElseIf = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 14) 
{
keyWordElse = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 15) 
{
keyWordWhileLoop = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 16) 
{
keyWordForLoop = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 17) 
{
keyWordLoopInfinite = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 18) 
{
keyWordLoop = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 19) 
{
keyWordLoopParse = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 20) 
{
keyWordContinue = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 21) 
{
keyWordBreak = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 22) 
{
keyWordFunc = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 23) 
{
keyWordAwait = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 24) 
{
keyWordVariablesAssignmentOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 25) 
{
keyWordConcatenationAssignmentOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 26) 
{
keyWordAdditionAssignmentOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 27) 
{
keyWordSubtractionAssignmentOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 28) 
{
keyWordMultiplicationAssignmentOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 29) 
{
keyWordDivisionAssignmentOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 30) 
{
keyWordAdditionOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 31) 
{
keyWordConcatenationOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 32) 
{
keyWordEqualOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 33) 
{
keyWordNotOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 34) 
{
keyWordGreaterThanOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 35) 
{
keyWordLessThanOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 36) 
{
keyWordGreaterThanOrEqualToOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 37) 
{
keyWordLessThanOrEqualToOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 38) 
{
keyWordOrOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 39) 
{
keyWordAndOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 40) 
{
keyWordNotEqualToOperator = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 41) 
{
keyWordTrue = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 42) 
{
keyWordFalse = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 43) 
{
keyWordSwitch = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 44) 
{
keyWordSwitchCase = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 45) 
{
keyWordSwitchDefault = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 46) 
{
keyWordThrow = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 47) 
{
keyWordErrorMsg = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 48) 
{
keyWordTry = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 49) 
{
keyWordCatch = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 50) 
{
keyWordFinally = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 51) 
{
keyWordArrayAppend = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 52) 
{
keyWordArrayPop = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 53) 
{
keyWordArraySize = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 54) 
{
keyWordArrayInsert = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 55) 
{
keyWordArrayRemove = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 56) 
{
keyWordArrayIndexOf = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 57) 
{
keyWordArrayDefinition = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 58) 
{
keyWordArrayOfIntegersDefinition = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 59) 
{
keyWordArrayOfStringsDefinition = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 60) 
{
keyWordArrayOfFloatingPointNumbersDefinition = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 61) 
{
keyWordArrayOfBooleansDefinition = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 62) 
{
keyWordJavaScriptVar = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 63) 
{
keyWordJavaScriptLet = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 64) 
{
keyWordJavaScriptConst = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 65) 
{
keyWordReturnStatement = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 66) 
{
keyWordEnd = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 67) 
{
keyWordGlobal = Trim ( A_LoopField66 ) + " ";
}
if (A_Index66 == 68) 
{
keyWordComment = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 69) 
{
keyWordCommentOpenMultiLine = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 70) 
{
keyWordCommentCloseMultiLine = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 71) 
{
keyWordEscpaeChar = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 72) 
{
AHKlikeLoopsIndexedAt = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 73) 
{
keyWordAIndex = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 74) 
{
keyWordALoopField = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 75) 
{
keyWordMainLabel = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 76) 
{
useFuncKeyWord = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 77) 
{
useCurlyBraces = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 78) 
{
useEnd = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 79) 
{
useSemicolon = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 80) 
{
useParentheses = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 81) 
{
usePythonicColonSyntax = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 82) 
{
forLoopLang = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 83) 
{
useInJavaScriptAlwaysUseVar = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 84) 
{
useJavaScriptInAfullHTMLfile = Trim ( A_LoopField66 ) ;
}
if (A_Index66 == 85) 
{
useJavaScriptAmainFuncDef = Trim ( A_LoopField66 ) ;
}
}
std::string htCodeOUT754754 = "";
int areWEinSome34sNum = 0;
int theIdNumOfThe34 = 0;
OneIndexedArray<std::string> theIdNumOfThe34theVar;
OneIndexedArray<std::string> getAllCharForTheFurtureSoIcanAddEscapeChar;
int removeNexFixkeyWordEscpaeChar = 0;
std::vector<std::string> items67 = LoopParseFunc(code);
for (size_t A_Index67 = 1; A_Index67 < items67.size() + 1; A_Index67++)
{
std::string A_LoopField67 = items67[A_Index67 - 1];
theIdNumOfThe34theVar[A_Index67] = theIdNumOfThe34theVar[A_Index67] + Chr ( 34 ) ;
getAllCharForTheFurtureSoIcanAddEscapeChar.add(A_LoopField67);
}
getAllCharForTheFurtureSoIcanAddEscapeChar.add(" ");
std::string ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr ( 34 ) + "ihuiuusgfgesrheidFor-asas-theuhtuwaesphoutr" + Chr ( 34 ) ;
std::string OutFixDoubleQuotesInsideDoubleQuotes;
int fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
std::vector<std::string> items68 = LoopParseFunc(code);
for (size_t A_Index68 = 1; A_Index68 < items68.size() + 1; A_Index68++)
{
std::string A_LoopField68 = items68[A_Index68 - 1];
if (A_LoopField68 == keyWordEscpaeChar && getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index68 + 1] == Chr (34)) 
{
fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1;
OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes;
}
else
{
if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok!= 1) 
{
OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField68;
}
else
{
fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
}
}
}
code = StringTrimRight(OutFixDoubleQuotesInsideDoubleQuotes, 1);
if (keyWordEscpaeChar!= Chr (92)) 
{
code = StrReplace ( code , Chr ( 92 ) , Chr ( 92 ) + Chr ( 92 ) ) ;
}
if (keyWordEscpaeChar == Chr (92)) 
{
std::vector<std::string> items69 = LoopParseFunc(code);
for (size_t A_Index69 = 1; A_Index69 < items69.size() + 1; A_Index69++)
{
std::string A_LoopField69 = items69[A_Index69 - 1];
if (A_LoopField69 == Chr (34)) 
{
areWEinSome34sNum++;
}
if (areWEinSome34sNum == 1) 
{
if (A_LoopField69!= Chr (34)) 
{
if (A_LoopField69 == keyWordEscpaeChar) 
{
theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr ( 92 ) ;
}
else
{
theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField69;
}
}
else
{
theIdNumOfThe34++;
htCodeOUT754754 += "ihuiuuhuuhtheidFor-asas-theuhturtyphoutr-" + Chr ( 65 ) + Chr ( 65 ) + STR ( theIdNumOfThe34 ) + Chr ( 65 ) + Chr ( 65 ) ;
}
}
if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) 
{
if (A_LoopField69!= Chr (34)) 
{
htCodeOUT754754 += A_LoopField69;
}
areWEinSome34sNum = 0;
}
}
}
else
{
std::vector<std::string> items70 = LoopParseFunc(code);
for (size_t A_Index70 = 1; A_Index70 < items70.size() + 1; A_Index70++)
{
std::string A_LoopField70 = items70[A_Index70 - 1];
if (A_LoopField70 == Chr (34)) 
{
areWEinSome34sNum++;
}
if (areWEinSome34sNum == 1) 
{
if (A_LoopField70!= Chr (34)) 
{
//MsgBox, % A_LoopField70 . " = " . keyWordEscpaeChar . ") && (" . keyWordEscpaeChar . " = " . getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index70 + 1] . ")"
if (A_LoopField70 == keyWordEscpaeChar && keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index70 + 1]) 
{
theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar;
removeNexFixkeyWordEscpaeChar = 1;
}
else if (A_LoopField70 == keyWordEscpaeChar) 
{
if (removeNexFixkeyWordEscpaeChar!= 1) 
{
theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr ( 92 ) ;
}
else
{
removeNexFixkeyWordEscpaeChar = 0;
}
}
else
{
theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField70;
}
}
else
{
theIdNumOfThe34++;
htCodeOUT754754 += "ihuiuuhuuhtheidFor-asas-theuhturtyphoutr-" + Chr ( 65 ) + Chr ( 65 ) + STR ( theIdNumOfThe34 ) + Chr ( 65 ) + Chr ( 65 ) ;
}
}
if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) 
{
if (A_LoopField70!= Chr (34)) 
{
htCodeOUT754754 += A_LoopField70;
}
areWEinSome34sNum = 0;
}
}
}
code = htCodeOUT754754;
for (int A_Index71 = 1; A_Index71<= theIdNumOfThe34; ++A_Index71)
{
theIdNumOfThe34theVar[A_Index71] = theIdNumOfThe34theVar[A_Index71] + Chr ( 34 ) ;
}
code = StrReplace ( code , Chr ( 13 ) , "" ) ;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
if (langToTranspileTo!= "py" && useSemicolon == "off") 
{
theSemicolon = ";";
}
else
{
theSemicolon = "";
}
if (langToTranspileTo!= "py" && usePythonicColonSyntax == "off") 
{
theColon = "";
}
else
{
theColon = ":";
}
std::string beforeKeywordForRemoveCommentsOnTheEndOfTheLine;
std::string newStringOutCode;
int posForRemoveCommentsOnTheEndOfTheLine;
std::string originalStringForRemoveCommentsOnTheEndOfTheLine;
std::vector<std::string> items72 = LoopParseFunc(code, "\n", "\r");
for (size_t A_Index72 = 1; A_Index72 < items72.size() + 1; A_Index72++)
{
std::string A_LoopField72 = items72[A_Index72 - 1];
// Define the original string
originalStringForRemoveCommentsOnTheEndOfTheLine = A_LoopField72;
// Find the position of the keyword in the original string
posForRemoveCommentsOnTheEndOfTheLine = InStr ( originalStringForRemoveCommentsOnTheEndOfTheLine , " " + keyWordComment ) ;
if (!(SubStr (Trim (A_LoopField72) , 1 , StrLen (keyWordComment)) == keyWordComment)) 
{
if (posForRemoveCommentsOnTheEndOfTheLine > 0) 
{
// Extract the part of the string before the keyword
if (!(SubStr (StrLower (A_LoopField72) , 1 , StrLen (StrLower (keyWordForLoop))) == StrLower (keyWordForLoop))) 
{
beforeKeywordForRemoveCommentsOnTheEndOfTheLine = SubStr ( originalStringForRemoveCommentsOnTheEndOfTheLine , 1 , posForRemoveCommentsOnTheEndOfTheLine - 1 ) ;
}
else
{
beforeKeywordForRemoveCommentsOnTheEndOfTheLine = A_LoopField72;
}
// Construct the new string with everything before the keyword
newStringOutCode += beforeKeywordForRemoveCommentsOnTheEndOfTheLine + "\n";
}
else
{
newStringOutCode += A_LoopField72 + "\n";
}
}
else
{
newStringOutCode += A_LoopField72 + "\n";
}
}
code = StringTrimRight(newStringOutCode, 1);
//MsgBox, % code
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string htCodeOutFixEnd;
if (useEnd == "on") 
{
std::vector<std::string> items73 = LoopParseFunc(code, "\n", "\r");
for (size_t A_Index73 = 1; A_Index73 < items73.size() + 1; A_Index73++)
{
std::string A_LoopField73 = items73[A_Index73 - 1];
if (StrLower (Trim (A_LoopField73)) == StrLower (keyWordEnd)) 
{
htCodeOutFixEnd += str10 + "}" + "\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordIF))) == StrLower (keyWordIF)) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordElseIf))) == StrLower (keyWordElseIf)) 
{
htCodeOutFixEnd += "\n}\n" + A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordElse))) == StrLower (keyWordElse)) 
{
htCodeOutFixEnd += "\n}\n" + A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordWhileLoop))) == StrLower (keyWordWhileLoop)) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordForLoop))) == StrLower (keyWordForLoop)) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordLoopInfinite))) == StrLower (keyWordLoopInfinite)) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordLoop))) == StrLower (keyWordLoop)) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordLoopParse))) == StrLower (keyWordLoopParse)) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordSwitch))) == StrLower (keyWordSwitch)) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordSwitchCase))) == StrLower (keyWordSwitchCase)) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordSwitchDefault))) == StrLower (keyWordSwitchDefault)) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordTry))) == StrLower (keyWordTry)) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower ("alliance"))) == StrLower ("alliance")) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower ("crew"))) == StrLower ("crew")) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower ("def obj"))) == StrLower ("def obj")) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower ("method"))) == StrLower ("method")) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordCatch))) == StrLower (keyWordCatch)) 
{
htCodeOutFixEnd += "\n}\n" + A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordFinally))) == StrLower (keyWordFinally)) 
{
htCodeOutFixEnd += "\n}\n" + A_LoopField73 + "\n{\n";
}
else if (SubStr (StrLower (Trim (A_LoopField73)) , 1 , StrLen (StrLower (keyWordFunc))) == StrLower (keyWordFunc)) 
{
htCodeOutFixEnd += A_LoopField73 + "\n{\n";
}
else
{
htCodeOutFixEnd += A_LoopField73 + "\n";
}
}
code = StringTrimRight(htCodeOutFixEnd, 1);
}
if (useEnd == "off" && useCurlyBraces == "off") 
{
htCodeOutFixEnd = "";
std::vector<std::string> items74 = LoopParseFunc(code, "\n", "\r");
for (size_t A_Index74 = 1; A_Index74 < items74.size() + 1; A_Index74++)
{
std::string A_LoopField74 = items74[A_Index74 - 1];
if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordIF))) == StrLower (keyWordIF)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordElseIf))) == StrLower (keyWordElseIf)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordElse))) == StrLower (keyWordElse)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordWhileLoop))) == StrLower (keyWordWhileLoop)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordForLoop))) == StrLower (keyWordForLoop)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordLoopInfinite))) == StrLower (keyWordLoopInfinite)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordLoop))) == StrLower (keyWordLoop)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordLoopParse))) == StrLower (keyWordLoopParse)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordSwitch))) == StrLower (keyWordSwitch)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordSwitchCase))) == StrLower (keyWordSwitchCase)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordSwitchDefault))) == StrLower (keyWordSwitchDefault)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordTry))) == StrLower (keyWordTry)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower ("alliance"))) == StrLower ("alliance")) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower ("crew"))) == StrLower ("crew")) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower ("def obj"))) == StrLower ("def obj")) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower ("method"))) == StrLower ("method")) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordCatch))) == StrLower (keyWordCatch)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordFinally))) == StrLower (keyWordFinally)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else if (SubStr (StrLower (Trim (A_LoopField74)) , 1 , StrLen (StrLower (keyWordFunc))) == StrLower (keyWordFunc)) 
{
htCodeOutFixEnd += A_LoopField74 + ":\n";
}
else
{
htCodeOutFixEnd += A_LoopField74 + "\n";
}
}
code = StringTrimRight(htCodeOutFixEnd, 1);
}
if (useCurlyBraces == "off" && useEnd == "off") 
{
code = AddCurlyBraces ( code ) ;
}
std::vector<std::string> items75 = LoopParseFunc(code, "\n", "\r");
for (size_t A_Index75 = 1; A_Index75 < items75.size() + 1; A_Index75++)
{
std::string A_LoopField75 = items75[A_Index75 - 1];
outTrimCode += Trim ( A_LoopField75 ) + "\n";
}
code = StringTrimRight(outTrimCode, 1);
// for converting c++ to js and py
code = StrReplace ( code , "{}" , "[]" ) ;
std::string outCodeFixBraces;
for (int A_Index76 = 1; A_Index76<= 2; ++A_Index76)
{
outCodeFixBraces = "";
std::vector<std::string> items77 = LoopParseFunc(code, "\n", "\r");
for (size_t A_Index77 = 1; A_Index77 < items77.size() + 1; A_Index77++)
{
std::string A_LoopField77 = items77[A_Index77 - 1];
if (InStr (Trim (A_LoopField77) , "{") && Trim (A_LoopField77)!= "{") 
{
outCodeFixBraces += Trim ( StrReplace ( Trim ( A_LoopField77 ) , "{" , "" ) ) + "\n{\n";
}
else if (InStr (Trim (A_LoopField77) , "}") && Trim (A_LoopField77)!= "}") 
{
outCodeFixBraces += "}\n" + Trim ( StrReplace ( Trim ( A_LoopField77 ) , "}" , "" ) ) + "\n";
}
else
{
outCodeFixBraces += Trim ( A_LoopField77 ) + "\n";
}
}
code = StringTrimRight(outCodeFixBraces, 1);
}
//MsgBox, % code
// main loop
// main loop
// main loop
// main loop
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
std::string out4758686d86d86d86578991a;
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
// main loop
// main loop
// main loop
// main loop
// main loop
int didWeUseMainLabel = 0;
std::string codeOutFixAndAddMainFunc;
std::vector<std::string> items78 = LoopParseFunc(code, "\n", "\r");
for (size_t A_Index78 = 1; A_Index78 < items78.size() + 1; A_Index78++)
{
std::string A_LoopField78 = items78[A_Index78 - 1];
if (StrLower (A_LoopField78) == StrLower (keyWordMainLabel)) 
{
didWeUseMainLabel = 1;
if (langToTranspileTo == "cpp") 
{
codeOutFixAndAddMainFunc += "int main(int argc, char* argv[])\n{\n";
}
if (langToTranspileTo == "js" && useJavaScriptAmainFuncDef == "on") 
{
codeOutFixAndAddMainFunc += "async function main()\n{\n";
}
}
else
{
codeOutFixAndAddMainFunc += A_LoopField78 + "\n";
}
}
if (didWeUseMainLabel!= 1 && langToTranspileTo == "cpp") 
{
codeOutFixAndAddMainFunc = "int main(int argc, char* argv[])\n{\n" + codeOutFixAndAddMainFunc;
}
if (didWeUseMainLabel!= 1 && langToTranspileTo == "js" && useJavaScriptAmainFuncDef == "on") 
{
codeOutFixAndAddMainFunc = "async function main()\n{\n" + codeOutFixAndAddMainFunc;
}
code = StringTrimRight(codeOutFixAndAddMainFunc, 1);
// main loop
// main loop
OneIndexedArray<std::string> lookIntoTheNextLineForFuncWhitNoKeyWord;
std::vector<std::string> items79 = LoopParseFunc(code, "\n", "\r");
for (size_t A_Index79 = 1; A_Index79 < items79.size() + 1; A_Index79++)
{
std::string A_LoopField79 = items79[A_Index79 - 1];
lookIntoTheNextLineForFuncWhitNoKeyWord.add(A_LoopField79);
}
lookIntoTheNextLineForFuncWhitNoKeyWord.add(" ");
// main loop
// main loop
// main loop
std::vector<std::string> items80 = LoopParseFunc(code, "\n", "\r");
for (size_t A_Index80 = 1; A_Index80 < items80.size() + 1; A_Index80++)
{
std::string A_LoopField80 = items80[A_Index80 - 1];
lineDone = 0;
if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower ("prop "))) == StrLower ("prop ")) 
{
if (InStr (A_LoopField80 , " " + Trim (keyWordConcatenationAssignmentOperator) + " ")) 
{
htCode += expressionParserTranspiler ( StrReplace ( A_LoopField80 , " " + Trim ( keyWordConcatenationAssignmentOperator ) + " " , " += " ) ) + "\n";
}
else if (InStr (A_LoopField80 , " " + Trim (keyWordVariablesAssignmentOperator) + " ")) 
{
htCode += expressionParserTranspiler ( StrReplace ( A_LoopField80 , " " + Trim ( keyWordVariablesAssignmentOperator ) + " " , " = " ) ) + "\n";
}
else if (InStr (A_LoopField80 , " " + Trim (keyWordAdditionAssignmentOperator) + " ")) 
{
htCode += expressionParserTranspiler ( StrReplace ( A_LoopField80 , " " + Trim ( keyWordAdditionAssignmentOperator ) + " " , " += " ) ) + "\n";
}
else if (InStr (A_LoopField80 , " " + Trim (keyWordSubtractionAssignmentOperator) + " ")) 
{
htCode += expressionParserTranspiler ( StrReplace ( A_LoopField80 , " " + Trim ( keyWordSubtractionAssignmentOperator ) + " " , " -= " ) ) + "\n";
}
else if (InStr (A_LoopField80 , " " + Trim (keyWordMultiplicationAssignmentOperator) + " ")) 
{
htCode += expressionParserTranspiler ( StrReplace ( A_LoopField80 , " " + Trim ( keyWordMultiplicationAssignmentOperator ) + " " , " *= " ) ) + "\n";
}
else if (InStr (A_LoopField80 , " " + Trim (keyWordDivisionAssignmentOperator) + " ")) 
{
htCode += expressionParserTranspiler ( StrReplace ( A_LoopField80 , " " + Trim ( keyWordDivisionAssignmentOperator ) + " " , " /= " ) ) + "\n";
}
else
{
htCode += expressionParserTranspiler ( A_LoopField80 ) + "\n";
}
lineDone = 1;
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordINT))) == StrLower (keyWordINT)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordINT ) ) ;
if (langToTranspileTo == "cpp") 
{
str5 = "int ";
}
else if (langToTranspileTo == "js") 
{
str5 = "var ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = None";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordSTR))) == StrLower (keyWordSTR)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordSTR ) ) ;
if (langToTranspileTo == "cpp") 
{
str5 = "std::string ";
}
else if (langToTranspileTo == "js") 
{
str5 = "var ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = None";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordBOOL))) == StrLower (keyWordBOOL)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordBOOL ) ) ;
if (langToTranspileTo == "cpp") 
{
str5 = "bool ";
}
else if (langToTranspileTo == "js") 
{
str5 = "var ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = None";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordFLOAT))) == StrLower (keyWordFLOAT)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordFLOAT ) ) ;
if (langToTranspileTo == "cpp") 
{
str5 = "float ";
}
else if (langToTranspileTo == "js") 
{
str5 = "var ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = None";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordINT8))) == StrLower (keyWordINT8)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordINT8 ) ) ;
if (langToTranspileTo == "cpp") 
{
str5 = "int8_t ";
}
else if (langToTranspileTo == "js") 
{
str5 = "var ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = None";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordINT16))) == StrLower (keyWordINT16)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordINT16 ) ) ;
if (langToTranspileTo == "cpp") 
{
str5 = "int16_t ";
}
else if (langToTranspileTo == "js") 
{
str5 = "var ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = None";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordINT32))) == StrLower (keyWordINT32)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordINT32 ) ) ;
if (langToTranspileTo == "cpp") 
{
str5 = "int32_t ";
}
else if (langToTranspileTo == "js") 
{
str5 = "var ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = None";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordINT64))) == StrLower (keyWordINT64)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordINT64 ) ) ;
if (langToTranspileTo == "cpp") 
{
str5 = "long long ";
}
else if (langToTranspileTo == "js") 
{
str5 = "var ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = None";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordIF))) == StrLower (keyWordIF)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordIF ) ) ;
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
//useParentheses
if (useParentheses == "off") 
{
str8 = "";
str9 = expressionParserTranspiler ( str1 ) ;
std::vector<std::string> items81 = LoopParseFunc(str9, " ");
for (size_t A_Index81 = 1; A_Index81 < items81.size() + 1; A_Index81++)
{
std::string A_LoopField81 = items81[A_Index81 - 1];
str8 = STR ( A_Index81 ) ;
}
if (INT (str8) <= 4) 
{
str2 = "if " + expressionParserTranspiler ( str1 ) + theColon;
}
else
{
str2 = "if " + str10 + "(" + StrReplace ( expressionParserTranspiler ( str1 ) , ":" , "" ) + ")" + theColon;
}
}
else
{
str2 = "if " + expressionParserTranspiler ( str1 ) + theColon;
}
str2 = StrReplace ( str2 , ";" , "" ) ;
str2 = StrReplace ( str2 , "::" , ":" ) ;
}
else
{
str1 = StrReplace ( str1 , ":" , "" ) ;
if (useParentheses == "off") 
{
str2 = "if " + str10 + "(" + expressionParserTranspiler ( str1 ) + ")";
}
else
{
str2 = "if " + expressionParserTranspiler ( str1 ) ;
}
str2 = StrReplace ( str2 , ";;" , ";" ) ;
}
str2 = StrReplace ( str2 , "::" , ":" ) ;
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordElseIf))) == StrLower (keyWordElseIf)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordElseIf ) ) ;
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
//useParentheses
if (useParentheses == "off") 
{
str8 = "";
str9 = expressionParserTranspiler ( str1 ) ;
std::vector<std::string> items82 = LoopParseFunc(str9, " ");
for (size_t A_Index82 = 1; A_Index82 < items82.size() + 1; A_Index82++)
{
std::string A_LoopField82 = items82[A_Index82 - 1];
str8 = STR ( A_Index82 ) ;
}
if (INT (str8) <= 4) 
{
str2 = "elif " + expressionParserTranspiler ( str1 ) + theColon;
}
else
{
str2 = "elif " + str10 + "(" + StrReplace ( expressionParserTranspiler ( str1 ) , ":" , "" ) + ")" + theColon;
}
}
else
{
str2 = "elif " + expressionParserTranspiler ( str1 ) + theColon;
}
str2 = StrReplace ( str2 , ";" , "" ) ;
str2 = StrReplace ( str2 , "::" , ":" ) ;
}
else
{
str1 = StrReplace ( str1 , ":" , "" ) ;
if (useParentheses == "off") 
{
str2 = "else if " + str10 + "(" + expressionParserTranspiler ( str1 ) + ")";
}
else
{
str2 = "else if " + expressionParserTranspiler ( str1 ) ;
}
str2 = StrReplace ( str2 , ";;" , ";" ) ;
}
str2 = StrReplace ( str2 , "::" , ":" ) ;
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordElse))) == StrLower (keyWordElse)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordElse ) ) ;
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str2 = "else:";
}
else
{
str2 = "else";
}
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordWhileLoop))) == StrLower (keyWordWhileLoop)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordWhileLoop ) ) ;
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
//useParentheses
if (useParentheses == "off") 
{
str8 = "";
str9 = expressionParserTranspiler ( str1 ) ;
std::vector<std::string> items83 = LoopParseFunc(str9, " ");
for (size_t A_Index83 = 1; A_Index83 < items83.size() + 1; A_Index83++)
{
std::string A_LoopField83 = items83[A_Index83 - 1];
str8 = STR ( A_Index83 ) ;
}
if (INT (str8) <= 4) 
{
str2 = "while " + expressionParserTranspiler ( str1 ) + theColon;
}
else
{
str2 = "while " + str10 + "(" + StrReplace ( expressionParserTranspiler ( str1 ) , ":" , "" ) + ")" + theColon;
}
}
else
{
str2 = "while " + expressionParserTranspiler ( str1 ) + theColon;
}
str2 = StrReplace ( str2 , ";" , "" ) ;
str2 = StrReplace ( str2 , "::" , ":" ) ;
}
else
{
str1 = StrReplace ( str1 , ":" , "" ) ;
if (useParentheses == "off") 
{
str2 = "while " + str10 + "(" + expressionParserTranspiler ( str1 ) + ")";
}
else
{
str2 = "while " + expressionParserTranspiler ( str1 ) ;
}
str2 = StrReplace ( str2 , ";;" , ";" ) ;
}
str2 = StrReplace ( str2 , "::" , ":" ) ;
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordForLoop))) == StrLower (keyWordForLoop)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordForLoop ) ) ;
//MsgBox, % A_LoopField80
if (useParentheses == "on") 
{
str2 = transpileForLoop ( langToTranspileTo , forLoopLang , "for " + expressionParserTranspiler ( str1 ) ) ;
}
else
{
if (langToTranspileTo == "py") 
{
str2 = transpileForLoop ( langToTranspileTo , forLoopLang , "for " + expressionParserTranspiler ( str1 ) ) ;
}
if (langToTranspileTo == "js") 
{
str2 = transpileForLoop ( langToTranspileTo , forLoopLang , "for (" + expressionParserTranspiler ( str1 ) + ")" ) ;
}
if (langToTranspileTo == "cpp") 
{
str2 = transpileForLoop ( langToTranspileTo , forLoopLang , "for (" + expressionParserTranspiler ( str1 ) + ")" ) ;
}
}
lineDone = 1;
str2 = StrReplace ( str2 , "::" , ":" ) ;
str2 = StrReplace ( str2 , ";;" , ";" ) ;
htCode += str2 + "\n";
}
else if (StrLower (A_LoopField80) == StrLower (keyWordLoopInfinite) || StrLower (A_LoopField80) == StrLower (keyWordLoopInfinite + ":")) 
{
// infinity loops
haveWeEverUsedAloop = 1;
lineDone = 1;
if (langToTranspileTo == "py") 
{
var1 = "for " + keyWordAIndex + "" + STR ( AindexcharLength ) + " , value in enumerate(iter(int, 1), start=" + AHKlikeLoopsIndexedAt + "):";
}
if (langToTranspileTo == "js") 
{
var1 = "for (let " + keyWordAIndex + "" + STR ( AindexcharLength ) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR ( AindexcharLength ) + "++)";
}
if (langToTranspileTo == "cpp") 
{
var1 = "for (int " + keyWordAIndex + "" + STR ( AindexcharLength ) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR ( AindexcharLength ) + "++)";
}
nothing = "";
AindexcharLengthStr = nothing + STR ( AindexcharLength ) + nothing;
htCodeAcurlyBraceAddSomeVrasFixNL = 1;
lineDone = 1;
htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR ( AindexcharLength ) + "\n";
htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR ( AindexcharLength ) ;
AindexcharLength++;
htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
}
else if (SubStr (Trim (StrLower (A_LoopField80)) , 1 , StrLen (StrLower (keyWordLoop))) == StrLower (keyWordLoop) && SubStr (Trim (StrLower (A_LoopField80)) , 1 , StrLen (StrLower (keyWordLoop)) + 2)!= StrLower (keyWordLoop) + "% " && SubStr (Trim (StrLower (A_LoopField80)) , 1 , StrLen (StrLower (keyWordLoopParse)))!= StrLower (keyWordLoopParse)) 
{
out2 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordLoop ) ) ;
out2 = StrReplace ( out2 , ":" , "" ) ;
//MsgBox % out2
//MsgBox, % out2
out2 = Trim ( out2 ) ;
myVar = out2;
lineYGI = expressionParserTranspiler ( myVar ) ;
line = lineYGI;
haveWeEverUsedAloop = 1;
//MsgBox, % line
if (langToTranspileTo == "py") 
{
var1 = "for " + keyWordAIndex + "" + STR ( AindexcharLength ) + " in range(" + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + "):";
}
if (langToTranspileTo == "js") 
{
var1 = "for (let " + keyWordAIndex + "" + STR ( AindexcharLength ) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR ( AindexcharLength ) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR ( AindexcharLength ) + "++)";
}
if (langToTranspileTo == "cpp") 
{
var1 = "for (int " + keyWordAIndex + "" + STR ( AindexcharLength ) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR ( AindexcharLength ) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR ( AindexcharLength ) + "++)";
}
nothing = "";
AindexcharLengthStr = nothing + STR ( AindexcharLength ) + nothing;
htCodeAcurlyBraceAddSomeVrasFixNL = 1;
htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR ( AindexcharLength ) + "\n";
htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR ( AindexcharLength ) ;
AindexcharLength++;
lineDone = 1;
htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
}
else if (SubStr (Trim (StrLower (A_LoopField80)) , 1 , StrLen (StrLower (keyWordLoop)) + 2) == StrLower (keyWordLoop) + "% ") 
{
out2 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordLoop ) + 2 ) ;
out2 = StrReplace ( out2 , ":" , "" ) ;
//MsgBox % out2
//MsgBox, % out2
out2 = Trim ( out2 ) ;
myVar = out2;
lineYGI = expressionParserTranspiler ( myVar ) ;
line = lineYGI;
haveWeEverUsedAloop = 1;
//MsgBox, % line
if (langToTranspileTo == "py") 
{
var1 = "for " + keyWordAIndex + "" + STR ( AindexcharLength ) + " in range(" + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + "):";
}
if (langToTranspileTo == "js") 
{
var1 = "for (let " + keyWordAIndex + "" + STR ( AindexcharLength ) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR ( AindexcharLength ) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR ( AindexcharLength ) + "++)";
}
if (langToTranspileTo == "cpp") 
{
var1 = "for (int " + keyWordAIndex + "" + STR ( AindexcharLength ) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR ( AindexcharLength ) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR ( AindexcharLength ) + "++)";
}
nothing = "";
AindexcharLengthStr = nothing + STR ( AindexcharLength ) + nothing;
htCodeAcurlyBraceAddSomeVrasFixNL = 1;
htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR ( AindexcharLength ) + "\n";
htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR ( AindexcharLength ) ;
AindexcharLength++;
lineDone = 1;
htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordLoopParse))) == StrLower (keyWordLoopParse)) 
{
var1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordLoopParse ) ) ;
out2 = StrReplace ( out2 , ":" , "" ) ;
lineDone = 1;
line1 = Trim ( StrSplit ( var1 , "," , 1 ) ) ;
line1 = expressionParserTranspiler ( line1 ) ;
line2 = "";
line3 = "";
itemsOut = "";
line2 = Trim ( StrSplit ( var1 , "," , 2 ) ) ;
line3 = Trim ( StrSplit ( var1 , "," , 3 ) ) ;
if (InStr (var1 , keyWordEscpaeChar + ",")) 
{
line2 = Chr ( 34 ) + "," + Chr ( 34 ) ;
if (langToTranspileTo == "py" || langToTranspileTo == "js") 
{
itemsOut = "items" + STR ( AindexcharLength ) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
}
else
{
itemsOut = "std::vector<std::string> items" + STR ( AindexcharLength ) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
}
}
else
{
if (line2 == "" && line3 == "") 
{
// nothing so only each char
if (langToTranspileTo == "py" || langToTranspileTo == "js") 
{
itemsOut = "items" + STR ( AindexcharLength ) + " = LoopParseFunc(" + line1 + ")";
}
else
{
itemsOut = "std::vector<std::string> items" + STR ( AindexcharLength ) + " = LoopParseFunc(" + line1 + ");";
}
}
if (line2!= "" && line3 == "") 
{
if (InStr (line2 , keyWordEscpaeChar)) 
{
line2 = Chr ( 34 ) + line2 + Chr ( 34 ) ;
}
if (langToTranspileTo == "py" || langToTranspileTo == "js") 
{
itemsOut = "items" + STR ( AindexcharLength ) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
}
else
{
itemsOut = "std::vector<std::string> items" + STR ( AindexcharLength ) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
}
}
if (line2!= "" && line3!= "") 
{
if (InStr (line2 , keyWordEscpaeChar)) 
{
line2 = Chr ( 34 ) + line2 + Chr ( 34 ) ;
}
if (InStr (line3 , keyWordEscpaeChar)) 
{
line3 = Chr ( 34 ) + line3 + Chr ( 34 ) ;
}
if (langToTranspileTo == "py" || langToTranspileTo == "js") 
{
itemsOut = "items" + STR ( AindexcharLength ) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
}
else
{
itemsOut = "std::vector<std::string> items" + STR ( AindexcharLength ) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
}
}
itemsOut = StrReplace ( itemsOut , keyWordEscpaeChar , Chr ( 92 ) ) ;
}
if (langToTranspileTo == "py") 
{
var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR ( AindexcharLength ) + " , " + keyWordALoopField + "" + STR ( AindexcharLength ) + " in enumerate(items" + STR ( AindexcharLength ) + ", start=" + AHKlikeLoopsIndexedAt + "):";
}
if (langToTranspileTo == "js") 
{
var1out = itemsOut + "\n" + "for (let " + keyWordAIndex + "" + STR ( AindexcharLength ) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR ( AindexcharLength ) + " < items" + STR ( AindexcharLength ) + ".length + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR ( AindexcharLength ) + "++)";
}
if (langToTranspileTo == "cpp") 
{
var1out = itemsOut + "\n" + "for (size_t " + keyWordAIndex + "" + STR ( AindexcharLength ) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR ( AindexcharLength ) + " < items" + STR ( AindexcharLength ) + ".size() + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR ( AindexcharLength ) + "++)";
}
nothing = "";
AindexcharLengthStr = nothing + STR ( AindexcharLength ) + nothing;
//
//
theFixTextLoopLP = "";
if (langToTranspileTo == "cpp") 
{
theFixTextLoopLP = "std::string " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
}
if (langToTranspileTo == "js") 
{
theFixTextLoopLP = "const " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
}
htCodeAcurlyBraceAddSomeVrasFixLP = 1;
haveWeEverUsedAloop = 1;
htCodeLoopfixa += "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR ( AindexcharLength ) + "\n";
htCodeLoopfixa1 = "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR ( AindexcharLength ) ;
AindexcharLength++;
htCode += htCodeLoopfixa1 + "\n" + var1out + "\n";
}
else if (StrLower (A_LoopField80) == StrLower (keyWordContinue) || StrLower (A_LoopField80) == StrLower (keyWordContinue + ";")) 
{
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str2 = "continue";
}
else
{
str2 = "continue;";
}
htCode += str2 + "\n";
}
else if (StrLower (A_LoopField80) == StrLower (keyWordBreak) || StrLower (A_LoopField80) == StrLower (keyWordBreak + ";")) 
{
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str2 = "break";
}
else
{
str2 = "break;";
}
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordFunc))) == StrLower (keyWordFunc) && useFuncKeyWord == "on") 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordFunc ) ) ;
//MsgBox, % A_LoopField80
str2 = str1;
str2 = StrReplace ( str2 , ":" , "" ) ;
str2 = StrReplace ( str2 , Trim ( keyWordVariablesAssignmentOperator ) , "=" ) ;
if (langToTranspileTo == "cpp") 
{
str2 = RegExReplace ( str2 , "\\b" + keyWordTrue + "\\b" , "true" ) ;
str2 = RegExReplace ( str2 , "\\b" + keyWordFalse + "\\b" , "false" ) ;
str2 = fixFuncParamsHandleSpaces ( str2 ) ;
}
else
{
str2 = RegExReplace ( str2 , "\\bvoid\\b" , "" ) ;
if (langToTranspileTo!= "py") 
{
str2 = RegExReplace ( str2 , "\\b" + keyWordTrue + "\\b" , "true" ) ;
str2 = RegExReplace ( str2 , "\\b" + keyWordFalse + "\\b" , "false" ) ;
}
else
{
str2 = RegExReplace ( str2 , "\\b" + keyWordTrue + "\\b" , "True" ) ;
str2 = RegExReplace ( str2 , "\\b" + keyWordFalse + "\\b" , "False" ) ;
}
str2 = RegExReplace ( str2 , "\\b" + Trim ( keyWordArrayDefinition ) + "\\b" , "" ) ;
str2 = RegExReplace ( str2 , "\\b" + Trim ( keyWordArrayOfIntegersDefinition ) + "\\b" , "" ) ;
str2 = RegExReplace ( str2 , "\\b" + Trim ( keyWordArrayOfStringsDefinition ) + "\\b" , "" ) ;
str2 = RegExReplace ( str2 , "\\b" + Trim ( keyWordArrayOfFloatingPointNumbersDefinition ) + "\\b" , "" ) ;
str2 = RegExReplace ( str2 , "\\b" + Trim ( keyWordArrayOfBooleansDefinition ) + "\\b" , "" ) ;
str2 = RegExReplace ( str2 , "\\b" + Trim ( keyWordINT ) + "\\b" , "" ) ;
str2 = RegExReplace ( str2 , "\\b" + Trim ( keyWordSTR ) + "\\b" , "" ) ;
str2 = RegExReplace ( str2 , "\\b" + Trim ( keyWordBOOL ) + "\\b" , "" ) ;
str2 = RegExReplace ( str2 , "\\b" + Trim ( keyWordINT8 ) + "\\b" , "" ) ;
str2 = RegExReplace ( str2 , "\\b" + Trim ( keyWordINT16 ) + "\\b" , "" ) ;
str2 = RegExReplace ( str2 , "\\b" + Trim ( keyWordINT32 ) + "\\b" , "" ) ;
str2 = RegExReplace ( str2 , "\\b" + Trim ( keyWordINT64 ) + "\\b" , "" ) ;
str2 = RegExReplace ( str2 , "\\b" + Trim ( keyWordFLOAT ) + "\\b" , "" ) ;
}
str2 = StrReplace ( str2 , "):" , ")" ) ;
str2 = StrReplace ( str2 , ") :" , ")" ) ;
if (langToTranspileTo == "py") 
{
str3 = "def " + str2 + ":";
}
if (langToTranspileTo == "js") 
{
str3 = "async function " + str2;
}
if (langToTranspileTo == "cpp") 
{
str3 = str2;
}
str3 = StrReplace ( str3 , "  " , " " ) ;
str3 = StrReplace ( str3 , "( " , "(" ) ;
lineDone = 1;
htCode += str3 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordAwait))) == StrLower (keyWordAwait)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordAwait ) ) ;
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str2 = expressionParserTranspiler ( str1 ) + theSemicolon;
str2 = StrReplace ( str2 , ";" , "" ) ;
}
else if (langToTranspileTo == "js") 
{
str2 = "await " + expressionParserTranspiler ( str1 ) + theSemicolon;
str2 = StrReplace ( str2 , ";;" , ";" ) ;
}
else
{
str2 = expressionParserTranspiler ( str1 ) + theSemicolon;
str2 = StrReplace ( str2 , ";;" , ";" ) ;
}
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordSwitch))) == StrLower (keyWordSwitch)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordSwitch ) ) ;
//MsgBox, % A_LoopField80
lineDone = 1;
str1 = StrReplace ( str1 , ":" , "" ) ;
if (langToTranspileTo == "py") 
{
str2 = "match " + expressionParserTranspiler ( str1 ) + theColon;
str2 = StrReplace ( str2 , ";" , "" ) ;
str2 = StrReplace ( str2 , "::" , ":" ) ;
str2 = StrReplace ( str2 , "(" , "" ) ;
str2 = StrReplace ( str2 , ")" , "" ) ;
}
else
{
str1 = StrReplace ( str1 , ":" , "" ) ;
str2 = "switch " + expressionParserTranspiler ( str1 ) ;
str2 = StrReplace ( str2 , ";;" , ";" ) ;
}
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordSwitchCase))) == StrLower (keyWordSwitchCase)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordSwitchCase ) ) ;
//MsgBox, % A_LoopField80
str1 = StrReplace ( str1 , ":" , "" ) ;
str2 = "case " + expressionParserTranspiler ( str1 ) + ":";
lineDone = 1;
htCode += str2 + "\n";
}
else if (StrLower (A_LoopField80) == StrLower (keyWordSwitchDefault) || StrLower (A_LoopField80) == StrLower (keyWordSwitchDefault + ":")) 
{
//MsgBox, % A_LoopField80
if (langToTranspileTo == "py") 
{
str2 = "case _:";
}
else
{
str2 = "default:";
}
lineDone = 1;
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordThrow))) == StrLower (keyWordThrow)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordThrow ) ) ;
//MsgBox, % A_LoopField80
//#include <stdexcept>
lineDone = 1;
if (langToTranspileTo == "py") 
{
str2 = "raise " + expressionParserTranspiler ( str1 ) + theSemicolon;
str2 = StrReplace ( str2 , ";" , "" ) ;
}
else
{
str2 = "throw " + expressionParserTranspiler ( str1 ) + theSemicolon;
str2 = StrReplace ( str2 , ";;" , ";" ) ;
}
htCode += str2 + "\n";
}
else if (StrLower (A_LoopField80) == StrLower (keyWordTry) || StrLower (A_LoopField80) == StrLower (keyWordTry + ":")) 
{
//MsgBox, % A_LoopField80
if (langToTranspileTo == "py") 
{
str2 = "try:";
}
else
{
str2 = "try";
}
lineDone = 1;
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordCatch))) == StrLower (keyWordCatch)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordCatch ) ) ;
//MsgBox, % A_LoopField80
lineDone = 1;
str1 = StrReplace ( str1 , ":" , "" ) ;
if (langToTranspileTo == "cpp") 
{
str2 = "catch " + str10 + "(const std::exception& " + Trim ( StrReplace ( StrReplace ( StrReplace ( str1 , ":" , "" ) , ")" , "" ) , "(" , "" ) ) + ")";
theCppVarForErrors = Trim ( StrReplace ( StrReplace ( StrReplace ( str1 , ":" , "" ) , ")" , "" ) , "(" , "" ) ) ;
}
if (langToTranspileTo == "js") 
{
str2 = "catch " + str10 + "(" + Trim ( StrReplace ( StrReplace ( StrReplace ( str1 , ":" , "" ) , ")" , "" ) , "(" , "" ) ) + ")";
}
if (langToTranspileTo == "py") 
{
str2 = "except " + str10 + "Exception as " + Trim ( StrReplace ( StrReplace ( StrReplace ( str1 , ":" , "" ) , ")" , "" ) , "(" , "" ) ) + ":";
}
htCode += str2 + "\n";
}
else if (StrLower (A_LoopField80) == StrLower (keyWordFinally) || StrLower (A_LoopField80) == StrLower (keyWordFinally + ":")) 
{
//MsgBox, % A_LoopField80
if (langToTranspileTo == "py") 
{
str2 = "finally:";
}
if (langToTranspileTo == "js") 
{
str2 = "finally";
}
if (langToTranspileTo == "cpp") 
{
str2 = "if (" + Chr ( 34 ) + "finally dosent exist in c++" + Chr ( 34 ) + " == " + Chr ( 34 ) + "finally dosent exist in c++" + Chr ( 34 ) + ")";
}
lineDone = 1;
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordArrayOfIntegersDefinition))) == StrLower (keyWordArrayOfIntegersDefinition)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordArrayOfIntegersDefinition ) ) ;
if (langToTranspileTo == "cpp") 
{
str5 = "std::vector<int> ";
}
else if (langToTranspileTo == "js") 
{
str5 = "let ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = []";
}
else if (langToTranspileTo == "js") 
{
str4 = str5 + StrReplace ( str1 , ";" , "" ) + " = [];";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordArrayOfStringsDefinition))) == StrLower (keyWordArrayOfStringsDefinition)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordArrayOfStringsDefinition ) ) ;
if (langToTranspileTo == "cpp") 
{
str5 = "std::vector<std::string> ";
}
else if (langToTranspileTo == "js") 
{
str5 = "let ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = []";
}
else if (langToTranspileTo == "js") 
{
str4 = str5 + StrReplace ( str1 , ";" , "" ) + " = [];";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordArrayOfFloatingPointNumbersDefinition))) == StrLower (keyWordArrayOfFloatingPointNumbersDefinition)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordArrayOfFloatingPointNumbersDefinition ) ) ;
if (langToTranspileTo == "cpp") 
{
str5 = "std::vector<float> ";
}
else if (langToTranspileTo == "js") 
{
str5 = "let ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = []";
}
else if (langToTranspileTo == "js") 
{
str4 = str5 + StrReplace ( str1 , ";" , "" ) + " = [];";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordArrayOfBooleansDefinition))) == StrLower (keyWordArrayOfBooleansDefinition)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordArrayOfBooleansDefinition ) ) ;
if (langToTranspileTo == "cpp") 
{
str5 = "std::vector<bool> ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = []";
}
else if (langToTranspileTo == "js") 
{
str4 = str5 + StrReplace ( str1 , ";" , "" ) + " = [];";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordArrayDefinition))) == StrLower (keyWordArrayDefinition) && lineDone == 0) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordArrayDefinition ) ) ;
if (langToTranspileTo == "cpp") 
{
str5 = "std::vector<std::string> ";
}
else if (langToTranspileTo == "js") 
{
str5 = "let ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = []";
}
else if (langToTranspileTo == "js") 
{
str4 = str5 + StrReplace ( str1 , ";" , "" ) + " = [];";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordJavaScriptVar))) == StrLower (keyWordJavaScriptVar)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordJavaScriptVar ) ) ;
if (langToTranspileTo == "js") 
{
str5 = "var ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = None";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordJavaScriptLet))) == StrLower (keyWordJavaScriptLet)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordJavaScriptLet ) ) ;
if (langToTranspileTo == "js") 
{
str5 = "let ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = None";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordJavaScriptConst))) == StrLower (keyWordJavaScriptConst)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordJavaScriptConst ) ) ;
if (langToTranspileTo == "js") 
{
str5 = "const ";
}
else
{
str5 = "";
}
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = None";
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if (isItAPlusPlusOrMinusMinus (Trim (A_LoopField80) , 0)!= "no" && (InStr (A_LoopField80 , "++") || InStr (A_LoopField80 , "--"))) 
{
str1 = isItAPlusPlusOrMinusMinus ( Trim ( A_LoopField80 ) , 1 ) ;
lineDone = 1;
htCode += str1 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordReturnStatement))) == StrLower (keyWordReturnStatement)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordReturnStatement ) ) ;
//MsgBox, % A_LoopField80
lineDone = 1;
str2 = "return " + expressionParserTranspiler ( str1 ) + theSemicolon;
if (langToTranspileTo == "py") 
{
str2 = StrReplace ( str2 , ";" , "" ) ;
}
else
{
str2 = StrReplace ( str2 , ";;" , ";" ) ;
}
htCode += str2 + "\n";
}
else if (StrLower (Trim (A_LoopField80)) == StrLower (Trim (keyWordReturnStatement))) 
{
//MsgBox, % A_LoopField80
lineDone = 1;
str2 = "return;";
if (langToTranspileTo == "py") 
{
str2 = StrReplace ( str2 , ";" , "" ) ;
}
else
{
str2 = StrReplace ( str2 , ";;" , ";" ) ;
}
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordGlobal))) == StrLower (keyWordGlobal)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordGlobal ) ) ;
//MsgBox, % A_LoopField80
str1 = StrReplace ( str1 , ";" , "" ) ;
lineDone = 1;
if (langToTranspileTo == "py") 
{
str2 = "global " + str1;
}
else
{
str2 = "";
}
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordComment))) == StrLower (keyWordComment)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordComment ) ) ;
//MsgBox, % A_LoopField80
if (langToTranspileTo == "py") 
{
str2 = "#" + str1;
}
if (langToTranspileTo == "js") 
{
str2 = "//" + str1;
}
if (langToTranspileTo == "cpp") 
{
str2 = "//" + str1;
}
lineDone = 1;
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordCommentOpenMultiLine))) == StrLower (keyWordCommentOpenMultiLine)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordCommentOpenMultiLine ) ) ;
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
htCode += Chr ( 34 ) + Chr ( 34 ) + Chr ( 34 ) + "\n";
}
else
{
htCode += Chr ( 47 ) + Chr ( 42 ) + "\n";
}
}
else if (SubStr (StrLower (A_LoopField80) , 1 , StrLen (StrLower (keyWordCommentCloseMultiLine))) == StrLower (keyWordCommentCloseMultiLine)) 
{
str1 = StringTrimLeft ( A_LoopField80 , StrLen ( keyWordCommentCloseMultiLine ) ) ;
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
htCode += Chr ( 34 ) + Chr ( 34 ) + Chr ( 34 ) + "\n";
}
else
{
htCode += Chr ( 42 ) + Chr ( 47 ) + "\n";
}
}
else if (KeyWordsCommands (A_LoopField80 , "check" , keyWordsCommands , langToTranspileTo) == "true" && lineDone == 0) 
{
out_KeyWordsCommands = KeyWordsCommands ( A_LoopField80 , "transpile" , keyWordsCommands , langToTranspileTo ) ;
//MsgBox, % out_KeyWordsCommands
lineDone = 1;
htCode += out_KeyWordsCommands + "\n";
}
else if (InStr (A_LoopField80 , keyWordArrayAppend) || InStr (A_LoopField80 , keyWordArrayPop) || InStr (A_LoopField80 , keyWordArraySize) || InStr (A_LoopField80 , keyWordArrayInsert) || InStr (A_LoopField80 , keyWordArrayRemove) || InStr (A_LoopField80 , keyWordArrayIndexOf) && lineDone == 0) 
{
//MsgBox, % A_LoopField80
lineDone = 1;
str2 = expressionParserTranspiler ( A_LoopField80 ) + theSemicolon;
if (langToTranspileTo == "py") 
{
str2 = StrReplace ( str2 , ";" , "" ) ;
}
else
{
str2 = StrReplace ( str2 , ";;" , ";" ) ;
}
htCode += str2 + "\n";
}
else if (InStr (A_LoopField80 , keyWordVariablesAssignmentOperator) || InStr (A_LoopField80 , keyWordConcatenationAssignmentOperator) || InStr (A_LoopField80 , keyWordAdditionAssignmentOperator) || InStr (A_LoopField80 , keyWordSubtractionAssignmentOperator) || InStr (A_LoopField80 , keyWordMultiplicationAssignmentOperator) || InStr (A_LoopField80 , keyWordDivisionAssignmentOperator) && lineDone == 0) 
{
str1 = A_LoopField80;
str5 = "";
if (InStr (str1 , keyWordVariablesAssignmentOperator)) 
{
outVarOperator = "=";
str2 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordVariablesAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
if (langToTranspileTo == "js" && useInJavaScriptAlwaysUseVar == "on") 
{
//theJSvarDeclaredVarsBugFix
if (InStr (theJSvarDeclaredVarsBugFix , "|" + Trim (StrReplace (str2 , ";" , "")) + "|")) 
{
str5 = "";
}
else
{
str5 = "var ";
}
}
else
{
str5 = "";
}
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordConcatenationAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordConcatenationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
if (langToTranspileTo == "js" && useInJavaScriptAlwaysUseVar == "on") 
{
//theJSvarDeclaredVarsBugFix
if (InStr (theJSvarDeclaredVarsBugFix , "|" + Trim (StrReplace (str2 , ";" , "")) + "|")) 
{
str5 = "";
}
else
{
str5 = "var ";
}
}
else
{
str5 = "";
}
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordAdditionAssignmentOperator)) 
{
outVarOperator = "+=";
str2 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordAdditionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
if (langToTranspileTo == "js" && useInJavaScriptAlwaysUseVar == "on") 
{
//theJSvarDeclaredVarsBugFix
if (InStr (theJSvarDeclaredVarsBugFix , "|" + Trim (StrReplace (str2 , ";" , "")) + "|")) 
{
str5 = "";
}
else
{
str5 = "var ";
}
}
else
{
str5 = "";
}
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordSubtractionAssignmentOperator)) 
{
outVarOperator = "-=";
str2 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordSubtractionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
if (langToTranspileTo == "js" && useInJavaScriptAlwaysUseVar == "on") 
{
//theJSvarDeclaredVarsBugFix
if (InStr (theJSvarDeclaredVarsBugFix , "|" + Trim (StrReplace (str2 , ";" , "")) + "|")) 
{
str5 = "";
}
else
{
str5 = "var ";
}
}
else
{
str5 = "";
}
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordMultiplicationAssignmentOperator)) 
{
outVarOperator = "*=";
str2 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordMultiplicationAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
if (langToTranspileTo == "js" && useInJavaScriptAlwaysUseVar == "on") 
{
//theJSvarDeclaredVarsBugFix
if (InStr (theJSvarDeclaredVarsBugFix , "|" + Trim (StrReplace (str2 , ";" , "")) + "|")) 
{
str5 = "";
}
else
{
str5 = "var ";
}
}
else
{
str5 = "";
}
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else if (InStr (str1 , keyWordDivisionAssignmentOperator)) 
{
outVarOperator = "/=";
str2 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 1 ) ) ;
str3 = Trim ( StrSplit ( str1 , keyWordDivisionAssignmentOperator , 2 ) ) ;
str3 = expressionParserTranspiler ( str3 ) ;
if (langToTranspileTo == "js" && useInJavaScriptAlwaysUseVar == "on") 
{
//theJSvarDeclaredVarsBugFix
if (InStr (theJSvarDeclaredVarsBugFix , "|" + Trim (StrReplace (str2 , ";" , "")) + "|")) 
{
str5 = "";
}
else
{
str5 = "var ";
}
}
else
{
str5 = "";
}
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str2 , ";" , "" ) ) + "|";
str4 = str5 + str2 + " " + outVarOperator + " " + str3 + theSemicolon;
}
else
{
if (langToTranspileTo == "py") 
{
str4 = Trim ( str5 ) + Trim ( str1 ) + " = None";
}
else if (langToTranspileTo == "js") 
{
if (langToTranspileTo == "js" && useInJavaScriptAlwaysUseVar == "on") 
{
//theJSvarDeclaredVarsBugFix
if (InStr (theJSvarDeclaredVarsBugFix , "|" + Trim (StrReplace (str1 , ";" , "")) + "|")) 
{
str5 = "";
}
else
{
str5 = "var ";
}
}
else
{
str5 = "";
}
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
else
{
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField80
lineDone = 1;
if (langToTranspileTo == "py") 
{
str4 = StrReplace ( str4 , ";" , "" ) ;
}
else
{
str4 = StrReplace ( str4 , ";;" , ";" ) ;
}
htCode += str4 + "\n";
}
else if ((SubStr (Trim (A_LoopField80) , -2) == ");" || SubStr (Trim (A_LoopField80) , -1) == ")") &&!(InStr (A_LoopField80 , "int main(int argc, char* argv[])")) &&!(InStr (A_LoopField80 , "async function main()")) && lineDone == 0) 
{
lineDone = 1;
str1 = A_LoopField80;
if (langToTranspileTo == "py") 
{
str1 = StrReplace ( str1 , ";" , "" ) ;
}
if (Trim (lookIntoTheNextLineForFuncWhitNoKeyWord[A_Index80 + 1]) == "{" && useFuncKeyWord == "off") 
{
str2 = str1;
str2 = StrReplace ( str2 , Trim ( keyWordVariablesAssignmentOperator ) , "=" ) ;
str2 = StrReplace ( str2 , "):" , ")" ) ;
str2 = StrReplace ( str2 , ") :" , ")" ) ;
if (langToTranspileTo == "py") 
{
str3 = "def " + str2 + ":";
}
if (langToTranspileTo == "js") 
{
str3 = "async function " + str2;
}
if (langToTranspileTo == "cpp") 
{
str3 = str1;
}
htCode += str3 + "\n";
}
else
{
str2 = expressionParserTranspiler ( Trim ( str1 ) ) + ";";
if (langToTranspileTo == "py") 
{
str2 = StrReplace ( str2 , ";" , "" ) ;
}
else
{
str2 = StrReplace ( str2 , ";;" , ";" ) ;
}
htCode += str2 + "\n";
}
}
else
{
//MsgBox, % "else else else " . A_LoopField80
// this is THE else
if (lineDone!= 1) 
{
if (skipLeftCuleyForFuncPLS!= 1) 
{
if (SubStr (Trim (StrLower (A_LoopField80)) , 1 , 1) == Chr (125)) 
{
htCode += Chr ( 125 ) + "\n";
}
else
{
if (htCodeAcurlyBraceAddSomeVrasFixLP == 1 && SubStr (Trim (StrLower (A_LoopField80)) , 1 , 1) == Chr (123)) 
{
htCodeAcurlyBraceAddSomeVrasFixLP = 0;
htCode += A_LoopField80 + "\n" + theFixTextLoopLP + "\n";
}
else
{
if (htCodeAcurlyBraceAddSomeVrasFixNL == 1 && SubStr (Trim (StrLower (A_LoopField80)) , 1 , 1) == Chr (123)) 
{
htCodeAcurlyBraceAddSomeVrasFixNL = 0;
htCode += A_LoopField80 + "\n" + theFixTextLoopNL + "\n";
}
else
{
htCode += A_LoopField80 + "\n";
}
}
}
}
else
{
skipLeftCuleyForFuncPLS = 0;
}
}
}
}
htCode = StringTrimRight(htCode, 1);
int indentTrackCurlyBraceOpenClose = 0;
int canEndIndentTrackCurlyBraceOpenClose = 0;
int indentTrackCurlyBraceOpenCloseSTARTEDAT = 0;
int indentTrackCurlyBraceOpenCloseENDNEXTonce = 0;
int indentTrackCurlyBraceOpenCloseENDNEXT = 0;
int INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDE = 0;
int INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE = 0;
int INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_itsOVERover = 0;
int startInStartEdCurlyBraceStartONce = 0;
std::string OSPpasringHoldNameFirstPart = "";
std::string addOSPtoHTVM = "";
int foundAllianceCrewOrOtehrs = 0;
foundAllianceCrewOrOtehrs = 0;
std::vector<std::string> items84 = LoopParseFunc(htCode, "\n", "\r");
for (size_t A_Index84 = 1; A_Index84 < items84.size() + 1; A_Index84++)
{
std::string A_LoopField84 = items84[A_Index84 - 1];
if (SubStr (StrLower (Trim (A_LoopField84)) , 1 , 9) == "alliance ") 
{
foundAllianceCrewOrOtehrs = 1;
OSPpasringHoldNameFirstPart = StringTrimLeft(A_LoopField84, 9);
OSPpasringHoldNameFirstPart = Trim ( OSPpasringHoldNameFirstPart ) ;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_itsOVERover = 0;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDE = 1;
indentTrackCurlyBraceOpenCloseSTARTEDAT = A_Index84;
indentTrackCurlyBraceOpenClose = 0;
canEndIndentTrackCurlyBraceOpenClose = 0;
indentTrackCurlyBraceOpenCloseENDNEXT = 0;
indentTrackCurlyBraceOpenCloseENDNEXTonce = 0;
startInStartEdCurlyBraceStartONce = 0;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE = 0;
}
else if (Trim (A_LoopField84) == "{") 
{
if (foundAllianceCrewOrOtehrs == 1) 
{
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE = 0;
startInStartEdCurlyBraceStartONce++;
indentTrackCurlyBraceOpenCloseENDNEXTonce = 0;
if (startInStartEdCurlyBraceStartONce == 1) 
{
addOSPtoHTVM += "alliance|start|" + OSPpasringHoldNameFirstPart + "\n";
}
else
{
addOSPtoHTVM += A_LoopField84 + "\n";
}
canEndIndentTrackCurlyBraceOpenClose = 1;
indentTrackCurlyBraceOpenClose--;
}
else
{
addOSPtoHTVM += A_LoopField84 + "\n";
}
}
else if (Trim (A_LoopField84) == "}") 
{
if (foundAllianceCrewOrOtehrs == 1) 
{
canEndIndentTrackCurlyBraceOpenClose = 1;
indentTrackCurlyBraceOpenClose++;
if (indentTrackCurlyBraceOpenClose == 0) 
{
indentTrackCurlyBraceOpenCloseENDNEXT = 1;
indentTrackCurlyBraceOpenCloseENDNEXTonce++;
if (indentTrackCurlyBraceOpenCloseENDNEXTonce == 1 && INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_itsOVERover == 0) 
{
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_itsOVERover++;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE++;
addOSPtoHTVM += "alliance|end|" + OSPpasringHoldNameFirstPart + "\n";
//MsgBox, % "foundCLose } at line " . STR(A_Index84) . " and started at " . STR(indentTrackCurlyBraceOpenCloseSTARTEDAT)
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDE = 0;
}
}
if (INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE == 0) 
{
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE = 0;
addOSPtoHTVM += A_LoopField84 + "\n";
}
}
else
{
addOSPtoHTVM += A_LoopField84 + "\n";
}
}
else
{
addOSPtoHTVM += A_LoopField84 + "\n";
}
}
htCode = StringTrimRight(addOSPtoHTVM, 1);
foundAllianceCrewOrOtehrs = 0;
addOSPtoHTVM = "";
std::vector<std::string> items85 = LoopParseFunc(htCode, "\n", "\r");
for (size_t A_Index85 = 1; A_Index85 < items85.size() + 1; A_Index85++)
{
std::string A_LoopField85 = items85[A_Index85 - 1];
if (SubStr (StrLower (Trim (A_LoopField85)) , 1 , 5) == "crew ") 
{
foundAllianceCrewOrOtehrs = 1;
OSPpasringHoldNameFirstPart = StringTrimLeft(A_LoopField85, 5);
OSPpasringHoldNameFirstPart = Trim ( OSPpasringHoldNameFirstPart ) ;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_itsOVERover = 0;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDE = 1;
indentTrackCurlyBraceOpenCloseSTARTEDAT = A_Index85;
indentTrackCurlyBraceOpenClose = 0;
canEndIndentTrackCurlyBraceOpenClose = 0;
indentTrackCurlyBraceOpenCloseENDNEXT = 0;
indentTrackCurlyBraceOpenCloseENDNEXTonce = 0;
startInStartEdCurlyBraceStartONce = 0;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE = 0;
}
else if (Trim (A_LoopField85) == "{") 
{
if (foundAllianceCrewOrOtehrs == 1) 
{
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE = 0;
startInStartEdCurlyBraceStartONce++;
indentTrackCurlyBraceOpenCloseENDNEXTonce = 0;
if (startInStartEdCurlyBraceStartONce == 1) 
{
addOSPtoHTVM += "crew|start|" + OSPpasringHoldNameFirstPart + "\n";
}
else
{
addOSPtoHTVM += A_LoopField85 + "\n";
}
canEndIndentTrackCurlyBraceOpenClose = 1;
indentTrackCurlyBraceOpenClose--;
}
else
{
addOSPtoHTVM += A_LoopField85 + "\n";
}
}
else if (Trim (A_LoopField85) == "}") 
{
if (foundAllianceCrewOrOtehrs == 1) 
{
canEndIndentTrackCurlyBraceOpenClose = 1;
indentTrackCurlyBraceOpenClose++;
if (indentTrackCurlyBraceOpenClose == 0) 
{
indentTrackCurlyBraceOpenCloseENDNEXT = 1;
indentTrackCurlyBraceOpenCloseENDNEXTonce++;
if (indentTrackCurlyBraceOpenCloseENDNEXTonce == 1 && INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_itsOVERover == 0) 
{
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_itsOVERover++;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE++;
addOSPtoHTVM += "crew|end|" + OSPpasringHoldNameFirstPart + "\n";
//MsgBox, % "foundCLose } at line " . STR(A_Index85) . " and started at " . STR(indentTrackCurlyBraceOpenCloseSTARTEDAT)
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDE = 0;
}
}
if (INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE == 0) 
{
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE = 0;
addOSPtoHTVM += A_LoopField85 + "\n";
}
}
else
{
addOSPtoHTVM += A_LoopField85 + "\n";
}
}
else
{
addOSPtoHTVM += A_LoopField85 + "\n";
}
}
htCode = StringTrimRight(addOSPtoHTVM, 1);
addOSPtoHTVM = "";
foundAllianceCrewOrOtehrs = 0;
std::vector<std::string> items86 = LoopParseFunc(htCode, "\n", "\r");
for (size_t A_Index86 = 1; A_Index86 < items86.size() + 1; A_Index86++)
{
std::string A_LoopField86 = items86[A_Index86 - 1];
if (SubStr (StrLower (Trim (A_LoopField86)) , 1 , 8) == "def obj ") 
{
foundAllianceCrewOrOtehrs = 1;
OSPpasringHoldNameFirstPart = StringTrimLeft(A_LoopField86, 8);
OSPpasringHoldNameFirstPart = Trim ( OSPpasringHoldNameFirstPart ) ;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_itsOVERover = 0;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDE = 1;
indentTrackCurlyBraceOpenCloseSTARTEDAT = A_Index86;
indentTrackCurlyBraceOpenClose = 0;
canEndIndentTrackCurlyBraceOpenClose = 0;
indentTrackCurlyBraceOpenCloseENDNEXT = 0;
indentTrackCurlyBraceOpenCloseENDNEXTonce = 0;
startInStartEdCurlyBraceStartONce = 0;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE = 0;
}
else if (Trim (A_LoopField86) == "{") 
{
if (foundAllianceCrewOrOtehrs == 1) 
{
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE = 0;
startInStartEdCurlyBraceStartONce++;
indentTrackCurlyBraceOpenCloseENDNEXTonce = 0;
if (startInStartEdCurlyBraceStartONce == 1) 
{
addOSPtoHTVM += "def obj|start|" + OSPpasringHoldNameFirstPart + "\n";
}
else
{
addOSPtoHTVM += A_LoopField86 + "\n";
}
canEndIndentTrackCurlyBraceOpenClose = 1;
indentTrackCurlyBraceOpenClose--;
}
else
{
addOSPtoHTVM += A_LoopField86 + "\n";
}
}
else if (Trim (A_LoopField86) == "}") 
{
if (foundAllianceCrewOrOtehrs == 1) 
{
canEndIndentTrackCurlyBraceOpenClose = 1;
indentTrackCurlyBraceOpenClose++;
if (indentTrackCurlyBraceOpenClose == 0) 
{
indentTrackCurlyBraceOpenCloseENDNEXT = 1;
indentTrackCurlyBraceOpenCloseENDNEXTonce++;
if (indentTrackCurlyBraceOpenCloseENDNEXTonce == 1 && INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_itsOVERover == 0) 
{
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_itsOVERover++;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE++;
addOSPtoHTVM += "def obj|end|" + OSPpasringHoldNameFirstPart + "\n";
//MsgBox, % "foundCLose } at line " . STR(A_Index86) . " and started at " . STR(indentTrackCurlyBraceOpenCloseSTARTEDAT)
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDE = 0;
}
}
if (INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE == 0) 
{
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE = 0;
addOSPtoHTVM += A_LoopField86 + "\n";
}
}
else
{
addOSPtoHTVM += A_LoopField86 + "\n";
}
}
else
{
addOSPtoHTVM += A_LoopField86 + "\n";
}
}
htCode = StringTrimRight(addOSPtoHTVM, 1);
addOSPtoHTVM = "";
foundAllianceCrewOrOtehrs = 0;
std::vector<std::string> items87 = LoopParseFunc(htCode, "\n", "\r");
for (size_t A_Index87 = 1; A_Index87 < items87.size() + 1; A_Index87++)
{
std::string A_LoopField87 = items87[A_Index87 - 1];
if (SubStr (StrLower (Trim (A_LoopField87)) , 1 , 7) == "method ") 
{
foundAllianceCrewOrOtehrs = 1;
OSPpasringHoldNameFirstPart = StringTrimLeft(A_LoopField87, 7);
OSPpasringHoldNameFirstPart = Trim ( OSPpasringHoldNameFirstPart ) ;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_itsOVERover = 0;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDE = 1;
indentTrackCurlyBraceOpenCloseSTARTEDAT = A_Index87;
indentTrackCurlyBraceOpenClose = 0;
canEndIndentTrackCurlyBraceOpenClose = 0;
indentTrackCurlyBraceOpenCloseENDNEXT = 0;
indentTrackCurlyBraceOpenCloseENDNEXTonce = 0;
startInStartEdCurlyBraceStartONce = 0;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE = 0;
}
else if (Trim (A_LoopField87) == "{") 
{
if (foundAllianceCrewOrOtehrs == 1) 
{
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE = 0;
startInStartEdCurlyBraceStartONce++;
indentTrackCurlyBraceOpenCloseENDNEXTonce = 0;
if (startInStartEdCurlyBraceStartONce == 1) 
{
addOSPtoHTVM += "method|start|" + OSPpasringHoldNameFirstPart + "\n";
}
else
{
addOSPtoHTVM += A_LoopField87 + "\n";
}
canEndIndentTrackCurlyBraceOpenClose = 1;
indentTrackCurlyBraceOpenClose--;
}
else
{
addOSPtoHTVM += A_LoopField87 + "\n";
}
}
else if (Trim (A_LoopField87) == "}") 
{
if (foundAllianceCrewOrOtehrs == 1) 
{
canEndIndentTrackCurlyBraceOpenClose = 1;
indentTrackCurlyBraceOpenClose++;
if (indentTrackCurlyBraceOpenClose == 0) 
{
indentTrackCurlyBraceOpenCloseENDNEXT = 1;
indentTrackCurlyBraceOpenCloseENDNEXTonce++;
if (indentTrackCurlyBraceOpenCloseENDNEXTonce == 1 && INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_itsOVERover == 0) 
{
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_itsOVERover++;
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE++;
addOSPtoHTVM += "method|end|" + OSPpasringHoldNameFirstPart + "\n";
//MsgBox, % "foundCLose } at line " . STR(A_Index87) . " and started at " . STR(indentTrackCurlyBraceOpenCloseSTARTEDAT)
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDE = 0;
}
}
if (INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE == 0) 
{
INSIDEindentTrackCurlyBraceOpenCloseENDNEXT_INSIDEdoneDONE = 0;
addOSPtoHTVM += A_LoopField87 + "\n";
}
}
else
{
addOSPtoHTVM += A_LoopField87 + "\n";
}
}
else
{
addOSPtoHTVM += A_LoopField87 + "\n";
}
}
htCode = StringTrimRight(addOSPtoHTVM, 1);
//MsgBox, ========================== phase1 =============================
//MsgBox, ========================== phase1 =============================
//MsgBox, ========================== phase1 =============================
//MsgBox, ========================== phase1 =============================
//MsgBox, % htCode
//MsgBox, ========================== phase1 =============================
//MsgBox, ========================== phase1 =============================
//MsgBox, ========================== phase1 =============================
//MsgBox, ========================== phase1 =============================
OneIndexedArray<std::string> statckOSPgetData;
OneIndexedArray<std::string> OSPconnectionArrayHOLD;
std::string OSPconnectionStrHOLD;
std::string OSPholdPROPstrForArray = "";
// important string
// exmaple how it will look like
int areWeInDefObj = 0;
addOSPtoHTVM = "";
std::vector<std::string> items88 = LoopParseFunc(htCode, "\n", "\r");
for (size_t A_Index88 = 1; A_Index88 < items88.size() + 1; A_Index88++)
{
std::string A_LoopField88 = items88[A_Index88 - 1];
if (InStr (A_LoopField88 , "alliance|start|")) 
{
statckOSPgetData.add(Trim(StrSplit(A_LoopField88, "|", 3)));
}
else if (InStr (A_LoopField88 , "crew|start|")) 
{
statckOSPgetData.add(Trim(StrSplit(A_LoopField88, "|", 3)));
}
else if (InStr (A_LoopField88 , "def obj|start|")) 
{
OSPholdPROPstrForArray = "";
areWeInDefObj = 1;
statckOSPgetData.add(Trim(StrSplit(A_LoopField88, "|", 3)));
}
else if (SubStr (Trim (StrLower (A_LoopField88)) , 1 , 5) == "prop ") 
{
OSPholdPROPstrForArray += A_LoopField88 + "|";
}
else if (InStr (A_LoopField88 , "method|start|")) 
{
if (InStr (Trim (A_LoopField88) , " ")) 
{
statckOSPgetData.add(Trim(StrSplit(Trim(StrSplit(Trim(StrSplit(A_LoopField88, "|", 3)), "(", 1)), " ", 2)));
}
else
{
statckOSPgetData.add(Trim(StrSplit(Trim(StrSplit(A_LoopField88, "|", 3)), "(", 1)));
}
OSPconnectionStrHOLD = "";
for (int A_Index89 = 1; A_Index89<= INT ( statckOSPgetData[0] ) ; ++A_Index89)
{
//MsgBox, % "aswadsfadsfasdfasd::::::::::::::" . statckOSPgetData[A_Index89]
OSPconnectionStrHOLD += statckOSPgetData[A_Index89] + "_";
str5 = statckOSPgetData[A_Index89];
}
OSPconnectionStrHOLD = StringTrimRight(OSPconnectionStrHOLD, 1);
//MsgBox, % OSPconnectionStrHOLD
HoldOSPdethodNamePath += StrReplace ( OSPconnectionStrHOLD , "_" , "." ) + "|";
str1 = Trim ( StrSplit ( Trim ( StrSplit ( A_LoopField88 , "|" , 3 ) ) , " " , 1 ) ) ;
str2 = OSPconnectionStrHOLD;
if (str1 == Trim (keyWordINT)) 
{
str4 = "int";
}
else if (str1 == Trim (keyWordSTR)) 
{
str4 = "std::string";
}
else if (str1 == Trim (keyWordFLOAT)) 
{
str4 = "float";
}
else if (str1 == Trim (keyWordBOOL)) 
{
str4 = "bool";
}
else if (str1 == Trim (keyWordINT8)) 
{
str4 = "int8_t";
}
else if (str1 == Trim (keyWordINT16)) 
{
str4 = "int16_t";
}
else if (str1 == Trim (keyWordINT32)) 
{
str4 = "int32_t";
}
else if (str1 == Trim (keyWordINT64)) 
{
str4 = "int64_t";
}
else
{
str4 = "void";
}
if (langToTranspileTo == "cpp") 
{
addOSPtoHTVM += str4 + " OSPHTVMOSP_" + str2 + "(std::optional<std::vector<std::any>> this__OSP__this = std::nullopt)\n{\n";
}
if (langToTranspileTo == "js") 
{
addOSPtoHTVM += "async function OSPHTVMOSP_" + str2 + "(this__OSP__this = null)\n{\n";
}
if (langToTranspileTo == "py") 
{
addOSPtoHTVM += "def OSPHTVMOSP_" + str2 + "(this__OSP__this = None):\n{\n";
}
}
else if (InStr (A_LoopField88 , "alliance|end|")) 
{
OSPconnectionStrHOLD = "";
for (int A_Index90 = 1; A_Index90<= INT ( statckOSPgetData[0] ) ; ++A_Index90)
{
OSPconnectionStrHOLD += statckOSPgetData[A_Index90] + ".";
}
OSPconnectionStrHOLD = StringTrimRight(OSPconnectionStrHOLD, 1);
OSPconnectionArrayHOLD.add(OSPconnectionStrHOLD);
statckOSPgetData.pop_back ( ) ;
}
else if (InStr (A_LoopField88 , "crew|end|")) 
{
OSPconnectionStrHOLD = "";
for (int A_Index91 = 1; A_Index91<= INT ( statckOSPgetData[0] ) ; ++A_Index91)
{
OSPconnectionStrHOLD += statckOSPgetData[A_Index91] + ".";
}
OSPconnectionStrHOLD = StringTrimRight(OSPconnectionStrHOLD, 1);
OSPconnectionArrayHOLD.add(OSPconnectionStrHOLD);
statckOSPgetData.pop_back ( ) ;
}
else if (InStr (A_LoopField88 , "def obj|end|")) 
{
OSPholdPROPstrForArray = StringTrimRight(OSPholdPROPstrForArray, 1);
if (Trim (OSPholdPROPstrForArray)!= "") 
{
str1 = "";
str2 = "";
str3 = "";
str4 = "";
str5 = "";
str6 = "";
str7 = "";
str8 = "";
str9 = "";
str10 = "";
str1 = "";
areWeInDefObj = 0;
OSPconnectionStrHOLD = "";
for (int A_Index92 = 1; A_Index92<= INT ( statckOSPgetData[0] ) ; ++A_Index92)
{
OSPconnectionStrHOLD += statckOSPgetData[A_Index92] + ".";
}
OSPconnectionStrHOLD = StringTrimRight(OSPconnectionStrHOLD, 1);
OSPconnectionArrayHOLD.add(OSPconnectionStrHOLD);
statckOSPgetData.pop_back ( ) ;
OSPstrArrayStrALLobjInOSP += OSPconnectionStrHOLD + ":";
if (langToTranspileTo == "cpp") 
{
str2 = "std::vector<std::any> OSPHTVMOSP_" + StrReplace ( OSPconnectionStrHOLD , "." , "_" ) + " = {\nstd::string(" + Chr ( 34 ) + OSPconnectionStrHOLD + Chr ( 34 ) + "),\n";
}
if (langToTranspileTo == "py") 
{
str2 = "OSPHTVMOSP_" + StrReplace ( OSPconnectionStrHOLD , "." , "_" ) + " = [\n" + Chr ( 34 ) + OSPconnectionStrHOLD + Chr ( 34 ) + ",\n";
}
if (langToTranspileTo == "js") 
{
str2 = "let OSPHTVMOSP_" + StrReplace ( OSPconnectionStrHOLD , "." , "_" ) + " = [\n" + Chr ( 34 ) + OSPconnectionStrHOLD + Chr ( 34 ) + ",\n";
}
std::vector<std::string> items93 = LoopParseFunc(OSPholdPROPstrForArray, "|");
for (size_t A_Index93 = 1; A_Index93 < items93.size() + 1; A_Index93++)
{
std::string A_LoopField93 = items93[A_Index93 - 1];
str1 = A_LoopField93;
if (Trim (A_LoopField93)!= "") 
{
// prop str typeOf := ""
// path.path.path:propName1[str],propName2[bool],propName3[str array]|path.path.path:propName1[str],propName2[bool],propName3[str array]
//;;;;;;;
str1 = StrReplace ( str1 , Trim ( keyWordArrayOfIntegersDefinition ) + " " , "vector<int> " ) ;
str1 = StrReplace ( str1 , Trim ( keyWordArrayOfStringsDefinition ) + " " , "vector<string> " ) ;
str1 = StrReplace ( str1 , Trim ( keyWordArrayOfFloatingPointNumbersDefinition ) + " " , "vector<float> " ) ;
str1 = StrReplace ( str1 , Trim ( keyWordArrayOfBooleansDefinition ) + " " , "vector<bool> " ) ;
str1 = StrReplace ( str1 , Trim ( keyWordArrayDefinition ) + " " , "vector<string> " ) ;
str1 = StrReplace ( str1 , ";" , "" ) ;
OSPstrArrayStrALLobjInOSP += Trim ( StrSplit ( str1 , " " , 3 ) ) + "[" + Trim ( StrSplit ( str1 , " " , 2 ) ) + "],";
if (InStr (Trim (StrSplit (str1 , " " , 5)) , "ihuiuuhuuhtheidFor-asas-theuhturtyphoutr-") || InStr (Trim (StrSplit (str1 , " " , 5)) , Chr (34))) 
{
if (langToTranspileTo == "cpp") 
{
str4 += "std::string(" + Trim ( StrSplit ( str1 , " " , 5 ) ) + "),\n";
}
else
{
str4 += Trim ( StrSplit ( str1 , " " , 5 ) ) + ",\n";
}
}
else
{
if (langToTranspileTo == "cpp") 
{
str4 += Trim ( StrSplit ( str1 , " " , 5 ) ) + ",\n";
}
else
{
str4 += Trim ( StrSplit ( str1 , " " , 5 ) ) + ",\n";
}
}
//;;;;;;;
}
}
OSPstrArrayStrALLobjInOSP = StringTrimRight(OSPstrArrayStrALLobjInOSP, 1);
OSPstrArrayStrALLobjInOSP += "|";
if (langToTranspileTo == "cpp") 
{
addOSPtoHTVM += str2 + str4 + "};\n";
}
else
{
addOSPtoHTVM += str2 + str4 + "]\n";
}
}
}
else if (InStr (A_LoopField88 , "method|end|")) 
{
addOSPtoHTVM += "}\n";
OSPconnectionStrHOLD = "";
for (int A_Index94 = 1; A_Index94<= INT ( statckOSPgetData[0] ) ; ++A_Index94)
{
OSPconnectionStrHOLD += statckOSPgetData[A_Index94] + ".";
}
OSPconnectionStrHOLD = StringTrimRight(OSPconnectionStrHOLD, 1);
OSPconnectionArrayHOLD.add(OSPconnectionStrHOLD);
statckOSPgetData.pop_back ( ) ;
}
else
{
addOSPtoHTVM += parserOSPgloabl ( OSPstrArrayStrALLobjInOSP , A_LoopField88 ) + "\n";
}
}
htCode = StringTrimRight(addOSPtoHTVM, 1);
OSPstrArrayStrALLobjInOSP = StringTrimRight(OSPstrArrayStrALLobjInOSP, 1);
// alliance|start|animalsKingdom
// crew|start|animals
// def obj|start|Dog
//MsgBox, ========================== phase2 =============================
//MsgBox, ========================== phase2 =============================
//MsgBox, % OSPstrArrayStrALLobjInOSP
//MsgBox, ========================== phase2 =============================
//MsgBox, ========================== phase2 =============================
//MsgBox, % htCode
//MsgBox, ========================== phase2 =============================
//MsgBox, ========================== phase2 =============================
//MsgBox, ========================== phase2 =============================
//MsgBox, ========================== phase2 =============================
// last OSP fix
std::string fixJSthatVARkeyword = "";
std::string fixJSthatVARkeywordOUT = "";
if (langToTranspileTo == "js") 
{
std::vector<std::string> items95 = LoopParseFunc(htCode, "\n", "\r");
for (size_t A_Index95 = 1; A_Index95 < items95.size() + 1; A_Index95++)
{
std::string A_LoopField95 = items95[A_Index95 - 1];
if (SubStr (Trim (A_LoopField95) , 1 , StrLen ("var ")) == "var ") 
{
if (InStr (A_LoopField95 , "= ")) 
{
if (InStr (StrSplit (A_LoopField95 , "= " , 1) , "[") || InStr (StrSplit (A_LoopField95 , "= " , 1) , ".")) 
{
fixJSthatVARkeywordOUT += StringTrimLeft ( A_LoopField95 , 4 ) + "\n";
}
else
{
fixJSthatVARkeywordOUT += A_LoopField95 + "\n";
}
}
else
{
fixJSthatVARkeywordOUT += A_LoopField95 + "\n";
}
}
else
{
fixJSthatVARkeywordOUT += A_LoopField95 + "\n";
}
}
htCode = StringTrimRight(fixJSthatVARkeywordOUT, 1);
}
//s
if (haveWeEverUsedAloop == 1) 
{
htCodeLoopfixa = StringTrimRight(htCodeLoopfixa, 1);
//OutputDebug, |%htCodeLoopfixa%|
AIndexLoopCurlyFix = 1;
std::vector<std::string> items96 = LoopParseFunc(htCodeLoopfixa, "\n", "\r");
for (size_t A_Index96 = 1; A_Index96 < items96.size() + 1; A_Index96++)
{
std::string A_LoopField96 = items96[A_Index96 - 1];
sstr123 = A_LoopField96;
fixLoopLokingFor = A_LoopField96;
fixLoopLokingForfound = 1;
out1 = StrSplit ( sstr123 , "|" , 1 ) ;
out2 = StrSplit ( sstr123 , "|" , 3 ) ;
//OutputDebug, |%out1%|
//OutputDebug, |%out2%|
wasAtanyIfsElseAddAIndexLoopCurlyFix = 0;
if (out1 == "nl") 
{
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
std::vector<std::string> items97 = LoopParseFunc(htCode, "\n", "\r");
for (size_t A_Index97 = 1; A_Index97 < items97.size() + 1; A_Index97++)
{
std::string A_LoopField97 = items97[A_Index97 - 1];
//MsgBox, dsfgsdefgesrdg1
//MsgBox, |%A_LoopField97%|`n|%fixLoopLokingFor%|
if (InStr (A_LoopField97 , fixLoopLokingFor) && insdeAnestedLoopBAD!= 1) 
{
fixLoopLokingForNum = 1;
//MsgBox, do we came here 1
}
if (SubStr (Trim (A_LoopField97) , 1 , 4) == "for " && weAreDoneHereCurly!= 1 && insdeAnestedLoopBAD!= 1 && fixLoopLokingForNum == 1) 
{
s = StrSplit ( A_LoopField97 , "" + keyWordAIndex + "" , 2 ) ;
out1z = s;
s = StrSplit ( out1z , " " , 1 ) ;
out1z = Trim ( s ) ;
//MsgBox, % out1z
//MsgBox, do we came here 2
fixLoopLokingForNum = 0;
foundTheTopLoop++;
inTarget = 1;
//MsgBox, % A_LoopField97
dontSaveStr = 1;
ALoopField = A_LoopField97;
DeleayOneCuzOfLoopParse = 1;
out4758686d86d86d86578991a += ALoopField + "\n";
}
if (inTarget == 1 && InStr (A_LoopField97 , Chr (123)) && insdeAnestedLoopBAD!= 1) 
{
insideBracket = 1;
}
if (insideBracket == 1 && InStr (A_LoopField97 , Chr (123)) && insdeAnestedLoopBAD!= 1) 
{
netsedCurly++;
}
if (insideBracket == 1 && InStr (A_LoopField97 , Chr (125)) && insdeAnestedLoopBAD!= 1) 
{
netsedCurly--;
readyToEnd = 1;
}
if (SubStr (Trim (A_LoopField97) , 1 , 4) == "for " && insdeAnestedLoopBAD!= 1 && foundTheTopLoop >= 2) 
{
insdeAnestedLoopBAD = 1;
insideBracket1 = 0;
netsedCurly1 = 0;
}
if (inTarget == 1) 
{
foundTheTopLoop++;
}
if (insdeAnestedLoopBAD == 1) 
{
if (InStr (A_LoopField97 , Chr (123))) 
{
insideBracket1 = 1;
}
if (insideBracket1 == 1 && InStr (A_LoopField97 , Chr (123))) 
{
netsedCurly1++;
}
if (insideBracket1 == 1 && InStr (A_LoopField97 , Chr (125))) 
{
netsedCurly1--;
readyToEnd1 = 1;
}
if (InStr (A_LoopField97 , Chr (125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) 
{
//MsgBox, % A_LoopField97
eldLoopNestedBADlol = 1;
}
out4758686d86d86d86578991a += A_LoopField97 + "\n";
}
if (inTarget == 1 && dontSaveStr!= 1 && fixLoopLokingForNum!= 1 && insdeAnestedLoopBAD!= 1) 
{
ALoopField = A_LoopField97;
// Replace "A_Index" with or without a following digit with "A_Index" + out1z
ALoopField = RegExReplace ( ALoopField , "" + keyWordAIndex + "\\d*" , "" + keyWordAIndex + "" + out1z ) ;
out4758686d86d86d86578991a += ALoopField + "\n";
}
if (inTarget == 1 && InStr (A_LoopField97 , Chr (125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr!= 1 && insdeAnestedLoopBAD!= 1) 
{
//MsgBox, % A_LoopField97
weAreDoneHereCurly = 1;
inTarget = 0;
endBracketDOntPutThere = 1;
}
dontSaveStr = 0;
if (inTarget!= 1 && endBracketDOntPutThere!= 1 && insdeAnestedLoopBAD!= 1) 
{
out4758686d86d86d86578991a += A_LoopField97 + "\n";
}
endBracketDOntPutThere = 0;
if (eldLoopNestedBADlol == 1) 
{
insdeAnestedLoopBAD = 0;
}
}
strstysrstsytTRIMHELP = out4758686d86d86d86578991a;
strstysrstsytTRIMHELP = StringTrimRight(strstysrstsytTRIMHELP, 1);
htCode = strstysrstsytTRIMHELP;
//MsgBox, % htCode
wasAtanyIfsElseAddAIndexLoopCurlyFix = 1;
}
else
{
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
std::vector<std::string> items98 = LoopParseFunc(htCode, "\n", "\r");
for (size_t A_Index98 = 1; A_Index98 < items98.size() + 1; A_Index98++)
{
std::string A_LoopField98 = items98[A_Index98 - 1];
if (InStr (A_LoopField98 , fixLoopLokingFor) && insdeAnestedLoopBAD!= 1) 
{
fixLoopLokingForNum = 1;
//MsgBox, do we came here 3
}
if (SubStr (Trim (A_LoopField98) , 1 , 4) == "for " && weAreDoneHereCurly!= 1 && insdeAnestedLoopBAD!= 1 && fixLoopLokingForNum == 1) 
{
s = StrSplit ( A_LoopField98 , "" + keyWordAIndex + "" , 2 ) ;
out1z = s;
s = StrSplit ( out1z , " " , 1 ) ;
out1z = Trim ( s ) ;
//MsgBox, % out1z
fixLoopLokingForNum = 0;
//MsgBox, do we came here 4
foundTheTopLoop++;
inTarget = 1;
//MsgBox, % A_LoopField98
dontSaveStr = 1;
ALoopField = A_LoopField98;
DeleayOneCuzOfLoopParse = 1;
out4758686d86d86d86578991a += ALoopField + "\n";
}
if (inTarget == 1 && InStr (A_LoopField98 , Chr (123)) && insdeAnestedLoopBAD!= 1) 
{
insideBracket = 1;
}
if (insideBracket == 1 && InStr (A_LoopField98 , Chr (123)) && insdeAnestedLoopBAD!= 1) 
{
netsedCurly++;
}
if (insideBracket == 1 && InStr (A_LoopField98 , Chr (125)) && insdeAnestedLoopBAD!= 1) 
{
netsedCurly--;
readyToEnd = 1;
}
if (SubStr (Trim (A_LoopField98) , 1 , 4) == "for " && insdeAnestedLoopBAD!= 1 && foundTheTopLoop >= 2) 
{
insdeAnestedLoopBAD = 1;
insideBracket1 = 0;
netsedCurly1 = 0;
}
if (inTarget == 1) 
{
foundTheTopLoop++;
}
if (insdeAnestedLoopBAD == 1) 
{
if (InStr (A_LoopField98 , Chr (123))) 
{
insideBracket1 = 1;
}
if (insideBracket1 == 1 && InStr (A_LoopField98 , Chr (123))) 
{
netsedCurly1++;
}
if (insideBracket1 == 1 && InStr (A_LoopField98 , Chr (125))) 
{
netsedCurly1--;
readyToEnd1 = 1;
}
if (InStr (A_LoopField98 , Chr (125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) 
{
//MsgBox, % A_LoopField98
eldLoopNestedBADlol = 1;
}
out4758686d86d86d86578991a += A_LoopField98 + "\n";
}
if (inTarget == 1 && dontSaveStr!= 1 && fixLoopLokingForNum!= 1 && insdeAnestedLoopBAD!= 1) 
{
ALoopField = A_LoopField98;
// Replace "A_Index" with or without a following digit with "A_Index" + out1z
ALoopField = RegExReplace ( ALoopField , "" + keyWordAIndex + "\\d*" , "" + keyWordAIndex + "" + out1z ) ;
// Replace "A_Index" with or without a following digit with "A_Index" + out1z
ALoopField = RegExReplace ( ALoopField , "" + keyWordALoopField + "\\d*" , "" + keyWordALoopField + "" + out1z ) ;
out4758686d86d86d86578991a += ALoopField + "\n";
}
if ((inTarget == 1 && InStr (A_LoopField98 , Chr (125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr!= 1 && insdeAnestedLoopBAD!= 1)) 
{
//MsgBox, % A_LoopField98
weAreDoneHereCurly = 1;
inTarget = 0;
endBracketDOntPutThere = 1;
}
dontSaveStr = 0;
if (inTarget!= 1 && endBracketDOntPutThere!= 1 && insdeAnestedLoopBAD!= 1) 
{
out4758686d86d86d86578991a += A_LoopField98 + "\n";
}
endBracketDOntPutThere = 0;
if (eldLoopNestedBADlol == 1) 
{
insdeAnestedLoopBAD = 0;
}
}
strstysrstsytTRIMHELP = out4758686d86d86d86578991a;
strstysrstsytTRIMHELP = StringTrimRight(strstysrstsytTRIMHELP, 1);
htCode = strstysrstsytTRIMHELP;
//MsgBox, % htCode
wasAtanyIfsElseAddAIndexLoopCurlyFix = 1;
}
if (wasAtanyIfsElseAddAIndexLoopCurlyFix == 1) 
{
AIndexLoopCurlyFix++;
wasAtanyIfsElseAddAIndexLoopCurlyFix = 0;
}
}
out4758686d86dgt8r754444444 = "";
hold = 0;
std::vector<std::string> items99 = LoopParseFunc(htCode, "\n", "\r");
for (size_t A_Index99 = 1; A_Index99 < items99.size() + 1; A_Index99++)
{
std::string A_LoopField99 = items99[A_Index99 - 1];
ignore = 0;
if (SubStr (Trim (A_LoopField99) , 1 , 4) == "for ") 
{
if (hold == 1 && holdText == A_LoopField99) 
{
ignore = 1;
}
else
{
holdText = A_LoopField99;
hold = 1;
}
}
if (!(ignore)) 
{
out4758686d86dgt8r754444444 += A_LoopField99 + "\n";
}
}
out4758686d86dgt8r754444444 = StringTrimRight(out4758686d86dgt8r754444444, 1);
htCode = out4758686d86dgt8r754444444;
}
htCodeOut1234565432 = "";
std::vector<std::string> items100 = LoopParseFunc(htCode, "\n", "\r");
for (size_t A_Index100 = 1; A_Index100 < items100.size() + 1; A_Index100++)
{
std::string A_LoopField100 = items100[A_Index100 - 1];
out = A_LoopField100;
if (!(InStr (out , "|itsaersdtgtgfergsdgfsegdfsedAA|"))) 
{
htCodeOut1234565432 += out + "\n";
}
}
htCode = StringTrimRight(htCodeOut1234565432, 1);
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
std::vector<std::string> items101 = LoopParseFunc(instructions, "\n", "\r");
for (size_t A_Index101 = 1; A_Index101 < items101.size() + 1; A_Index101++)
{
std::string A_LoopField101 = items101[A_Index101 - 1];
if (Trim (A_LoopField101) == "funcEND======================funcEND==============") 
{
areWeInAFuncFromInstructions = 0;
areWeInAFuncFromInstructionsLineNum = 0;
if (correctLang == 1 && InStr (htCode , Trim (funcNameHolder))) 
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
funcLangHolder = StringTrimLeft(A_LoopField101, 5);
if (Trim (funcLangHolder) == langToTranspileTo) 
{
allFuncLang.add(Trim(funcLangHolder));
correctLang = 1;
}
}
if (areWeInAFuncFromInstructionsLineNum == 2) 
{
// name of the func
funcNameHolder = StringTrimLeft(A_LoopField101, 5);
if (correctLang == 1 && InStr (htCode , Trim (funcNameHolder))) 
{
allFuncNames.add(Trim(funcNameHolder));
}
}
if (areWeInAFuncFromInstructionsLineNum == 3) 
{
// all libs
funcLibsHolder = StringTrimLeft(A_LoopField101, 5);
if (correctLang == 1 && InStr (htCode , Trim (funcNameHolder))) 
{
allFuncLibs.add(Trim(funcLibsHolder));
}
}
if (areWeInAFuncFromInstructionsLineNum == 4) 
{
// func description
funcDescriptionHolder = StringTrimLeft(A_LoopField101, 12);
if (correctLang == 1 && InStr (htCode , Trim (funcNameHolder))) 
{
allfuncDescription.add(Trim(funcDescriptionHolder));
}
}
if (areWeInAFuncFromInstructionsLineNum >= 5) 
{
// the full func
if (correctLang == 1 && InStr (htCode , Trim (funcNameHolder))) 
{
funcFuncHolder += A_LoopField101 + "\n";
}
}
//MsgBox, % A_LoopField101
areWeInAFuncFromInstructionsLineNum++;
}
if (Trim (A_LoopField101) == "func======================func==============") 
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
if (langToTranspileTo == "py") 
{
htCode = indent_nested_curly_braces ( htCode , 0 ) ;
}
else
{
htCode = indent_nested_curly_braces ( htCode , 1 ) ;
}
if (langToTranspileTo == "cpp") 
{
htCode = htCode + "\n    return 0;\n}";
htCode = StrReplace ( htCode , "int main(int argc, char* argv[]);" , "int main(int argc, char* argv[])" ) ;
}
if (langToTranspileTo == "js" && useJavaScriptAmainFuncDef == "on") 
{
htCode = htCode + "\n}\nmain();";
htCode = StrReplace ( htCode , "async function main();" , "async function main()" ) ;
htCode = StrReplace ( htCode , "function async function main()" , "async function main()" ) ;
}
std::string jsHTMLdownCode = "</script>\n</body>\n</html>";
int includeLibsInCppIf;
std::string allFuncsToPutAtTop = "\n";
std::string allLibsToPutAtTop;
print(std::string("Transpiling..."));
if (!(INT (allFuncNames[0]) <= 0)) 
{
for (int A_Index102 = 1; A_Index102<= INT ( allFuncNames[0] ) ; ++A_Index102)
{
if (InStr (htCode , allFuncNames[A_Index102]) + "(") 
{
//MsgBox, % allFuncNames[A_Index102]
allFuncsToPutAtTop += allFuncs[A_Index102] + "\n";
if (Trim (allFuncLibs[A_Index102])!= "null") 
{
allLibsToPutAtTop += allFuncLibs[A_Index102] + "|";
}
}
}
allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTop, 1);
std::string allLibsToPutAtTopTEMP;
std::vector<std::string> items103 = LoopParseFunc(allLibsToPutAtTop, "|");
for (size_t A_Index103 = 1; A_Index103 < items103.size() + 1; A_Index103++)
{
std::string A_LoopField103 = items103[A_Index103 - 1];
allLibsToPutAtTopTEMP += A_LoopField103 + "\n";
}
allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTopTEMP, 1);
includeLibsInCppIf = 1;
if (langToTranspileTo == "cpp") 
{
allLibsToPutAtTop = "#include <iostream>\n#include <sstream>\n#include <string>\n#include <cstdint>\n#include <algorithm>\n#include <vector>\n#include <any>\n#include <optional>\n" + allLibsToPutAtTop;
}
allLibsToPutAtTop = SortLikeAHK(allLibsToPutAtTop, "U");
allLibsToPutAtTop = StrReplace ( allLibsToPutAtTop , "~" , "\n" ) ;
if (langToTranspileTo!= "js") 
{
htCode = allLibsToPutAtTop + "\n" + allFuncsToPutAtTop + "\n" + htCode;
}
else
{
htCode = "\n" + allFuncsToPutAtTop + "\n" + htCode;
}
}
print(std::string("Transpiling..."));
for (int A_Index104 = 1; A_Index104<= theIdNumOfThe34; ++A_Index104)
{
htCode = StrReplace ( htCode , "ihuiuuhuuhtheidFor-asas-theuhturtyphoutr-" + Chr ( 65 ) + Chr ( 65 ) + STR ( A_Index104 ) + Chr ( 65 ) + Chr ( 65 ) , theIdNumOfThe34theVar[A_Index104] ) ;
}
htCode = StrReplace ( htCode , ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes , Chr ( 92 ) + Chr ( 34 ) ) ;
htCode = StrReplace ( htCode , "std::string(" + Chr ( 34 ) + Chr ( 34 ) + ";)," , "std::string(" + Chr ( 34 ) + Chr ( 34 ) + ")," ) ;
std::string jsHTMLupCode = "<!doctype html>\n<html lang=" + Chr ( 34 ) + "en" + Chr ( 34 ) + ">\n    <head>\n        <meta charset=" + Chr ( 34 ) + "UTF-8" + Chr ( 34 ) + " />\n        <meta name=" + Chr ( 34 ) + "viewport" + Chr ( 34 ) + " content=" + Chr ( 34 ) + "width=device-width, initial-scale=1.0" + Chr ( 34 ) + " />\n        <title>HTVM</title>\n        <style>\n            body {\n                background-color: #202020;\n                font-family:\n                    " + Chr ( 34 ) + "Open Sans" + Chr ( 34 ) + ",\n                    -apple-system,\n                    BlinkMacSystemFont,\n                    " + Chr ( 34 ) + "Segoe UI" + Chr ( 34 ) + ",\n                    Roboto,\n                    Oxygen-Sans,\n                    Ubuntu,\n                    Cantarell,\n                    " + Chr ( 34 ) + "Helvetica Neue" + Chr ( 34 ) + ",\n                    Helvetica,\n                    Arial,\n                    sans-serif;\n            }\n        </style>\n" + allLibsToPutAtTop + "\n</head>\n    <body>\n<script>";
if (useJavaScriptInAfullHTMLfile == "on" && langToTranspileTo == "js") 
{
htCode = jsHTMLupCode + "\n" + htCode + "\n" + jsHTMLdownCode;
}
if (langToTranspileTo == "cpp" && includeLibsInCppIf == 0) 
{
htCode = "#include <iostream>\n#include <sstream>\n#include <any>\n#include <string>\n#include <cstdint>\n#include <algorithm>\n#include <vector>\n\n" + htCode;
}
print(htCode);
std::vector<std::string> items105 = LoopParseFunc(fileExtention);
for (size_t A_Index105 = 1; A_Index105 < items105.size() + 1; A_Index105++)
{
std::string A_LoopField105 = items105[A_Index105 - 1];
filePathOfCode = StringTrimRight(filePathOfCode, 1);
}
if (useJavaScriptInAfullHTMLfile == "on" && langToTranspileTo == "js") 
{
filePathOfCode = filePathOfCode + "html";
}
else
{
filePathOfCode = filePathOfCode + langToTranspileTo;
}
FileDelete(filePathOfCode);
FileAppend(htCode, filePathOfCode);
}
int main(int argc, char* argv[])
{
compiler ( ) ;

return 0;
}
