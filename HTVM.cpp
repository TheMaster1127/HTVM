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
        std::cerr << "Error: File does not exist." << std::endl;
        return false;
    }

    // Attempt to remove the file
    if (!std::filesystem::remove(file_path)) {
        std::cerr << "Error: Failed to delete the file." << std::endl;
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


// Function to get command-line parameters
std::string GetParams() {
    std::vector<std::string> params;
    for (int i = 1; i < __argc; ++i) {
        std::string arg = __argv[i];
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
    std::cout << "Exiting application..." << std::endl;
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

// HT++
// revolution.htpp
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
outConstuctTheOutFromTheCommandsParams += Chr ( 34 ) + theCodeCommand[theCodeCommandNum] + Chr ( 34 ) + ", ";
}
else
{
outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
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
indexEqual = ExtractDigits ( StrReplace ( A_LoopField11 , ";" , "" ) ) ;
}
if (A_Index11 == 5) 
{
indexMax = ExtractDigits ( StrReplace ( A_LoopField11 , ";" , "" ) ) ;
}
}
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
indexEqual = ExtractDigits ( StrReplace ( A_LoopField13 , ";" , "" ) ) ;
}
if (A_Index13 == 5) 
{
indexMax = ExtractDigits ( StrReplace ( A_LoopField13 , ";" , "" ) ) ;
}
}
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
out = "for " + indexName + " in range(" + indexEqual + ", " + indexMax + "):";
return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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
out = "for (let " + indexName + " = " + indexEqual + "; " + indexName + " < " + indexMax + "; " + indexName + "++)";
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
std::string LTrim(std::string input)
{
std::string result = "";
bool foundNonSpace = false;
std::vector<std::string> items26 = LoopParseFunc(input);
for (size_t A_Index26 = 1; A_Index26 < items26.size() + 1; A_Index26++)
{
std::string A_LoopField26 = items26[A_Index26 - 1];
if (A_LoopField26!= " " || foundNonSpace) 
{
result += A_LoopField26;
foundNonSpace = true;
}
}
return result;
}
std::string getLastChar(std::string strippedString)
{
std::string lastChar;
std::vector<std::string> items27 = LoopParseFunc(strippedString);
for (size_t A_Index27 = 1; A_Index27 < items27.size() + 1; A_Index27++)
{
std::string A_LoopField27 = items27[A_Index27 - 1];
lastChar = A_LoopField27;
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
std::vector<std::string> items28 = LoopParseFunc(pythonCode, "\n", "\r");
for (size_t A_Index28 = 1; A_Index28 < items28.size() + 1; A_Index28++)
{
std::string A_LoopField28 = items28[A_Index28 - 1];
line = A_LoopField28;
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
for (int A_Index29 = 1;; A_Index29++)
{
if (indentLevel <= indent) 
{
break;
}
indentLevel -= 4;
result += spaces ( indentLevel ) + "}\n";
}
// Add opening brace for new blocks
if (getLastChar (stripped) == ":") 
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
for (int A_Index30 = 1;; A_Index30++)
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
for (int A_Index31 = 1; A_Index31<= count; ++A_Index31)
{
spaces += Chr ( 32 ) ;
}
return spaces;
}
std::string indent_nested_curly_braces(std::string input_string)
{
int indent_size = 4;
int current_indent = 0;
std::string result;
std::string trimmed_line;
//MsgBox, % input_string
std::vector<std::string> items32 = LoopParseFunc(input_string, "\n", "\r");
for (size_t A_Index32 = 1; A_Index32 < items32.size() + 1; A_Index32++)
{
std::string A_LoopField32 = items32[A_Index32 - 1];
trimmed_line = Trim ( A_LoopField32 ) ;
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
std::string resultOut;
std::vector<std::string> items33 = LoopParseFunc(result, "\n", "\r");
for (size_t A_Index33 = 1; A_Index33 < items33.size() + 1; A_Index33++)
{
std::string A_LoopField33 = items33[A_Index33 - 1];
if (Trim (A_LoopField33)!= "{" && Trim (A_LoopField33)!= "}") 
{
resultOut += A_LoopField33 + "\n";
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
std::string funcNameHolder;
std::string funcLibsHolder;
std::string funcParamsHolder;
std::string funcFuncHolder;
std::string funcDescriptionHolder;
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
std::string keyWordArrayDefinition;
std::string keyWordArrayOfIntegersDefinition;
std::string keyWordArrayOfStringsDefinition;
std::string keyWordArrayOfFloatingPointNumbersDefinition;
std::string keyWordArrayOfBooleansDefinition;
std::string keyWordJavaScriptVar;
std::string keyWordJavaScriptLet;
std::string keyWordJavaScriptConst;
std::string keyWordReturnStatement;
std::string keyWordReturnEndOFaSubroutineFunction;
std::string keyWordEnd;
std::string keyWordGlobal;
std::string keyWordComment;
std::string keyWordCommentOpenMultiLine;
std::string keyWordCommentCloseMultiLine;
std::string keyWordEscpaeChar;
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
std::string expressionParserTranspiler(std::string expression)
{
expression = StrReplace ( expression , " " + keyWordAdditionOperator + " " , " + " ) ;
expression = StrReplace ( expression , " " + keyWordConcatenationOperator + " " , " + " ) ;
expression = StrReplace ( expression , " " + keyWordEqualOperator + " " , " == " ) ;
if (langToTranspileTo == "py") 
{
expression = RegExReplace ( expression , "!([\\w]+)" , "not $1" ) ;
}
if (langToTranspileTo == "py") 
{
expression = StrReplace ( expression , keyWordNotOperator , "not" ) ;
}
else
{
expression = StrReplace ( expression , keyWordNotOperator , "!" ) ;
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
expression = StrReplace ( expression , keyWordErrorMsg , "Exception" ) ;
expression = StrReplace ( expression , keyWordArrayAppend , ".append" ) ;
expression = StrReplace ( expression , keyWordArrayPop , ".pop" ) ;
expression = StrReplace ( expression , ") and (" , " and " ) ;
expression = StrReplace ( expression , ") or (" , " or " ) ;
if (InStr (expression , keyWordArraySize)) 
{
std::string pattern1 = "(\\w{1,1})\\" + keyWordArraySize;
std::string pattern2 = "(\\w+)\\" + keyWordArraySize;
int result2 = RegExMatch ( expression , pattern1 ) ;
int result1 = RegExMatch ( expression , pattern2 ) ;
std::string concatResults;
std::vector<std::string> items34 = LoopParseFunc(expression);
for (size_t A_Index34 = 1; A_Index34 < items34.size() + 1; A_Index34++)
{
std::string A_LoopField34 = items34[A_Index34 - 1];
if (A_Index34 >= result1 && A_Index34 <= result2) 
{
concatResults += A_LoopField34;
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
expression = RegExReplace ( expression , "\\bTrue\\b" , "true" ) ;
expression = RegExReplace ( expression , "\\bFalse\\b" , "false" ) ;
expression = RegExReplace ( expression , "\\bNone\\b" , "null" ) ;
expression = StrReplace ( expression , "{}" , "[]" ) ;
expression = StrReplace ( expression , keyWordErrorMsg , "new Error" ) ;
expression = StrReplace ( expression , keyWordArrayAppend , ".push" ) ;
expression = StrReplace ( expression , keyWordArrayPop , ".pop" ) ;
expression = StrReplace ( expression , keyWordArraySize , ".length" ) ;
expression = StrReplace ( expression , ") && (" , " && " ) ;
expression = StrReplace ( expression , ") || (" , " || " ) ;
}
else if (langToTranspileTo == "cpp") 
{
// C++-specific replacements
expression = RegExReplace ( expression , "\\b" + theCppVarForErrors + "\\b" , theCppVarForErrors + ".what()" ) ;
expression = RegExReplace ( expression , "\\bTrue\\b" , "true" ) ;
expression = RegExReplace ( expression , "\\bFalse\\b" , "false" ) ;
expression = RegExReplace ( expression , "\\bnull\\b" , Chr ( 34 ) + Chr ( 34 ) ) ;
expression = RegExReplace ( expression , "\\bNone\\b" , Chr ( 34 ) + Chr ( 34 ) ) ;
expression = StrReplace ( expression , "[]" , "{}" ) ;
expression = StrReplace ( expression , keyWordErrorMsg , "std::runtime_error" ) ;
expression = StrReplace ( expression , keyWordArrayAppend , ".push_back" ) ;
expression = StrReplace ( expression , keyWordArrayPop , ".pop_back" ) ;
expression = StrReplace ( expression , keyWordArraySize , ".size" ) ;
expression = StrReplace ( expression , ") && (" , " && " ) ;
expression = StrReplace ( expression , ") || (" , " || " ) ;
}
expression = StrReplace ( expression , ".length()" , ".length" ) ;
std::string expressionOut;
std::vector<std::string> items35 = LoopParseFunc(expression, " ");
for (size_t A_Index35 = 1; A_Index35 < items35.size() + 1; A_Index35++)
{
std::string A_LoopField35 = items35[A_Index35 - 1];
expressionOut += A_LoopField35 + " ";
}
expressionOut = StringTrimRight(expressionOut, 1);
return expressionOut;
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
print(std::string("No params!!!!"));
ExitApp();
}
std::vector<std::string> items36 = LoopParseFunc(params, "\n", "\r");
for (size_t A_Index36 = 1; A_Index36 < items36.size() + 1; A_Index36++)
{
std::string A_LoopField36 = items36[A_Index36 - 1];
if (A_Index36 == 1) 
{
print(A_LoopField36);
filePathOfCode = A_LoopField36;
//MsgBox, % filePathOfCode
//code := FileRead(filePathOfCode)
code = FileRead(filePathOfCode);
//MsgBox, % code
}
if (A_Index36 == 2) 
{
print(A_LoopField36);
instructions = FileRead(A_LoopField36);
}
}
//MsgBox, % code
std::vector<std::string> items37 = LoopParseFunc(instructions, "\n", "\r");
for (size_t A_Index37 = 1; A_Index37 < items37.size() + 1; A_Index37++)
{
std::string A_LoopField37 = items37[A_Index37 - 1];
if (A_Index37 == 1) 
{
langToTranspileTo = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 2) 
{
fileExtention = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 3) 
{
keyWordsCommands = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 4) 
{
keyWordINT = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 5) 
{
keyWordSTR = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 6) 
{
keyWordBOOL = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 7) 
{
keyWordINT8 = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 8) 
{
keyWordINT16 = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 9) 
{
keyWordINT32 = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 10) 
{
keyWordINT64 = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 11) 
{
keyWordIF = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 12) 
{
keyWordElseIf = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 13) 
{
keyWordElse = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 14) 
{
keyWordWhileLoop = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 15) 
{
keyWordForLoop = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 16) 
{
keyWordLoopInfinite = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 17) 
{
keyWordLoop = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 18) 
{
keyWordLoopParse = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 19) 
{
keyWordContinue = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 20) 
{
keyWordBreak = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 21) 
{
keyWordFunc = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 22) 
{
keyWordAwait = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 23) 
{
keyWordVariablesAssignmentOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 24) 
{
keyWordConcatenationAssignmentOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 25) 
{
keyWordAdditionAssignmentOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 26) 
{
keyWordSubtractionAssignmentOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 27) 
{
keyWordMultiplicationAssignmentOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 28) 
{
keyWordDivisionAssignmentOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 29) 
{
keyWordAdditionOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 30) 
{
keyWordConcatenationOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 31) 
{
keyWordEqualOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 32) 
{
keyWordNotOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 33) 
{
keyWordGreaterThanOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 34) 
{
keyWordLessThanOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 35) 
{
keyWordGreaterThanOrEqualToOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 36) 
{
keyWordLessThanOrEqualToOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 37) 
{
keyWordOrOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 38) 
{
keyWordAndOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 39) 
{
keyWordNotEqualToOperator = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 40) 
{
keyWordTrue = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 41) 
{
keyWordFalse = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 42) 
{
keyWordSwitch = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 43) 
{
keyWordSwitchCase = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 44) 
{
keyWordSwitchDefault = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 45) 
{
keyWordThrow = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 46) 
{
keyWordErrorMsg = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 47) 
{
keyWordTry = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 48) 
{
keyWordCatch = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 49) 
{
keyWordFinally = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 50) 
{
keyWordArrayAppend = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 51) 
{
keyWordArrayPop = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 52) 
{
keyWordArraySize = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 53) 
{
keyWordArrayDefinition = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 54) 
{
keyWordArrayOfIntegersDefinition = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 55) 
{
keyWordArrayOfStringsDefinition = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 56) 
{
keyWordArrayOfFloatingPointNumbersDefinition = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 57) 
{
keyWordArrayOfBooleansDefinition = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 58) 
{
keyWordJavaScriptVar = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 59) 
{
keyWordJavaScriptLet = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 60) 
{
keyWordJavaScriptConst = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 61) 
{
keyWordReturnStatement = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 62) 
{
keyWordReturnEndOFaSubroutineFunction = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 63) 
{
keyWordEnd = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 64) 
{
keyWordGlobal = Trim ( A_LoopField37 ) + " ";
}
if (A_Index37 == 65) 
{
keyWordComment = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 66) 
{
keyWordCommentOpenMultiLine = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 67) 
{
keyWordCommentCloseMultiLine = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 68) 
{
keyWordEscpaeChar = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 69) 
{
useCurlyBraces = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 70) 
{
useEnd = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 71) 
{
useSemicolon = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 72) 
{
useParentheses = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 73) 
{
usePythonicColonSyntax = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 74) 
{
useTypes = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 75) 
{
forLoopLang = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 76) 
{
useInJavaScriptAlwaysUseVar = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 77) 
{
useJavaScriptInAfullHTMLfile = Trim ( A_LoopField37 ) ;
}
if (A_Index37 == 78) 
{
useJavaScriptAmainFuncDef = Trim ( A_LoopField37 ) ;
}
}
areWeInAFuncFromInstructions = 0;
areWeInAFuncFromInstructionsLineNum = 0;
OneIndexedArray<std::string> allFuncNames;
OneIndexedArray<std::string> allFuncLibs;
OneIndexedArray<std::string> allFuncParams;
OneIndexedArray<std::string> allFuncs;
OneIndexedArray<std::string> allfuncDescription;
std::vector<std::string> items38 = LoopParseFunc(instructions, "\n", "\r");
for (size_t A_Index38 = 1; A_Index38 < items38.size() + 1; A_Index38++)
{
std::string A_LoopField38 = items38[A_Index38 - 1];
if (Trim (A_LoopField38) == "funcEND======================funcEND==============") 
{
areWeInAFuncFromInstructions = 0;
areWeInAFuncFromInstructionsLineNum = 0;
allFuncs.add(funcFuncHolder);
}
if (areWeInAFuncFromInstructions == 1) 
{
if (areWeInAFuncFromInstructionsLineNum == 1) 
{
// name of the func
funcNameHolder = StringTrimLeft(A_LoopField38, 5);
allFuncNames.add(Trim(funcNameHolder));
}
if (areWeInAFuncFromInstructionsLineNum == 2) 
{
// all libs
funcLibsHolder = StringTrimLeft(A_LoopField38, 5);
allFuncLibs.add(Trim(funcLibsHolder));
}
if (areWeInAFuncFromInstructionsLineNum == 3) 
{
// func params
funcParamsHolder = StringTrimLeft(A_LoopField38, 7);
allFuncParams.add(Trim(funcParamsHolder));
}
if (areWeInAFuncFromInstructionsLineNum == 4) 
{
// func description
funcDescriptionHolder = StringTrimLeft(A_LoopField38, 12);
allfuncDescription.add(Trim(funcDescriptionHolder));
}
if (areWeInAFuncFromInstructionsLineNum >= 5) 
{
// the full func
funcFuncHolder += A_LoopField38 + "\n";
}
//MsgBox, % A_LoopField38
areWeInAFuncFromInstructionsLineNum++;
}
if (Trim (A_LoopField38) == "func======================func==============") 
{
areWeInAFuncFromInstructions = 1;
areWeInAFuncFromInstructionsLineNum = 1;
}
}
//~ MsgBox, % "==========================================================================="
//~ msgbox, % allFuncNames
//~ MsgBox, % "==========================================================================="
//~ msgbox, % allFuncLibs
//~ MsgBox, % "==========================================================================="
//~ msgbox, % allFuncParams
//~ MsgBox, % "==========================================================================="
//~ msgbox, % allFuncs
//~ MsgBox, % "==========================================================================="
std::string htCodeOUT754754 = "";
int areWEinSome34sNum = 0;
int theIdNumOfThe34 = 0;
OneIndexedArray<std::string> theIdNumOfThe34theVar;
OneIndexedArray<std::string> getAllCharForTheFurtureSoIcanAddEscapeChar;
int removeNexFixkeyWordEscpaeChar = 0;
std::vector<std::string> items39 = LoopParseFunc(code);
for (size_t A_Index39 = 1; A_Index39 < items39.size() + 1; A_Index39++)
{
std::string A_LoopField39 = items39[A_Index39 - 1];
theIdNumOfThe34theVar[A_Index39] = theIdNumOfThe34theVar[A_Index39] + Chr ( 34 ) ;
getAllCharForTheFurtureSoIcanAddEscapeChar.add(A_LoopField39);
}
getAllCharForTheFurtureSoIcanAddEscapeChar.add(" ");
std::string ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr ( 34 ) + "ihuiuusgfgesrheidFor-asas-theuhtuwaesphoutr" + Chr ( 34 ) ;
std::string OutFixDoubleQuotesInsideDoubleQuotes;
int fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
std::vector<std::string> items40 = LoopParseFunc(code);
for (size_t A_Index40 = 1; A_Index40 < items40.size() + 1; A_Index40++)
{
std::string A_LoopField40 = items40[A_Index40 - 1];
if (A_LoopField40 == keyWordEscpaeChar && getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index40 + 1] == Chr (34)) 
{
fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1;
OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes;
}
else
{
if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok!= 1) 
{
OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField40;
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
std::vector<std::string> items41 = LoopParseFunc(code);
for (size_t A_Index41 = 1; A_Index41 < items41.size() + 1; A_Index41++)
{
std::string A_LoopField41 = items41[A_Index41 - 1];
if (A_LoopField41 == Chr (34)) 
{
areWEinSome34sNum++;
}
if (areWEinSome34sNum == 1) 
{
if (A_LoopField41!= Chr (34)) 
{
if (A_LoopField41 == keyWordEscpaeChar) 
{
theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr ( 92 ) ;
}
else
{
theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField41;
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
if (A_LoopField41!= Chr (34)) 
{
htCodeOUT754754 += A_LoopField41;
}
areWEinSome34sNum = 0;
}
}
}
else
{
std::vector<std::string> items42 = LoopParseFunc(code);
for (size_t A_Index42 = 1; A_Index42 < items42.size() + 1; A_Index42++)
{
std::string A_LoopField42 = items42[A_Index42 - 1];
if (A_LoopField42 == Chr (34)) 
{
areWEinSome34sNum++;
}
if (areWEinSome34sNum == 1) 
{
if (A_LoopField42!= Chr (34)) 
{
//MsgBox, % A_LoopField42 . " = " . keyWordEscpaeChar . ") && (" . keyWordEscpaeChar . " = " . getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index42 + 1] . ")"
if (A_LoopField42 == keyWordEscpaeChar && keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index42 + 1]) 
{
theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar;
removeNexFixkeyWordEscpaeChar = 1;
}
else if (A_LoopField42 == keyWordEscpaeChar) 
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
theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField42;
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
if (A_LoopField42!= Chr (34)) 
{
htCodeOUT754754 += A_LoopField42;
}
areWEinSome34sNum = 0;
}
}
}
code = htCodeOUT754754;
for (int A_Index43 = 1; A_Index43<= theIdNumOfThe34; ++A_Index43)
{
theIdNumOfThe34theVar[A_Index43] = theIdNumOfThe34theVar[A_Index43] + Chr ( 34 ) ;
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
std::vector<std::string> items44 = LoopParseFunc(code, "\n", "\r");
for (size_t A_Index44 = 1; A_Index44 < items44.size() + 1; A_Index44++)
{
std::string A_LoopField44 = items44[A_Index44 - 1];
// Define the original string
originalStringForRemoveCommentsOnTheEndOfTheLine = A_LoopField44;
// Find the position of the keyword in the original string
posForRemoveCommentsOnTheEndOfTheLine = InStr ( originalStringForRemoveCommentsOnTheEndOfTheLine , keyWordComment ) ;
if (!(SubStr (Trim (A_LoopField44) , 1 , StrLen (keyWordComment)) == keyWordComment)) 
{
if (posForRemoveCommentsOnTheEndOfTheLine > 0) 
{
// Extract the part of the string before the keyword
if (!(SubStr (StrLower (A_LoopField44) , 1 , StrLen (StrLower (keyWordForLoop))) == StrLower (keyWordForLoop))) 
{
beforeKeywordForRemoveCommentsOnTheEndOfTheLine = SubStr ( originalStringForRemoveCommentsOnTheEndOfTheLine , 1 , posForRemoveCommentsOnTheEndOfTheLine - 1 ) ;
}
else
{
beforeKeywordForRemoveCommentsOnTheEndOfTheLine = A_LoopField44;
}
// Construct the new string with everything before the keyword
newStringOutCode += beforeKeywordForRemoveCommentsOnTheEndOfTheLine + "\n";
}
else
{
newStringOutCode += A_LoopField44 + "\n";
}
}
else
{
newStringOutCode += A_LoopField44 + "\n";
}
}
code = StringTrimRight(newStringOutCode, 1);
//MsgBox, % code
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
if (useEnd == "on") 
{
std::string htCodeOutFixEnd;
std::vector<std::string> items45 = LoopParseFunc(code, "\n", "\r");
for (size_t A_Index45 = 1; A_Index45 < items45.size() + 1; A_Index45++)
{
std::string A_LoopField45 = items45[A_Index45 - 1];
if (StrLower (A_LoopField45) == StrLower (keyWordEnd)) 
{
htCodeOutFixEnd += str10 + "}" + "\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordIF))) == StrLower (keyWordIF)) 
{
htCodeOutFixEnd += A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordElseIf))) == StrLower (keyWordElseIf)) 
{
htCodeOutFixEnd += "\n}\n" + A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordElse))) == StrLower (keyWordElse)) 
{
htCodeOutFixEnd += "\n}\n" + A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordWhileLoop))) == StrLower (keyWordWhileLoop)) 
{
htCodeOutFixEnd += A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordForLoop))) == StrLower (keyWordForLoop)) 
{
htCodeOutFixEnd += A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordLoopInfinite))) == StrLower (keyWordLoopInfinite)) 
{
htCodeOutFixEnd += A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordLoop))) == StrLower (keyWordLoop)) 
{
htCodeOutFixEnd += A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordLoopParse))) == StrLower (keyWordLoopParse)) 
{
htCodeOutFixEnd += A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordSwitch))) == StrLower (keyWordSwitch)) 
{
htCodeOutFixEnd += A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordSwitchCase))) == StrLower (keyWordSwitchCase)) 
{
htCodeOutFixEnd += A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordSwitchDefault))) == StrLower (keyWordSwitchDefault)) 
{
htCodeOutFixEnd += A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordTry))) == StrLower (keyWordTry)) 
{
htCodeOutFixEnd += A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordCatch))) == StrLower (keyWordCatch)) 
{
htCodeOutFixEnd += A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordFinally))) == StrLower (keyWordFinally)) 
{
htCodeOutFixEnd += A_LoopField45 + "\n{\n";
}
else if (SubStr (StrLower (A_LoopField45) , 1 , StrLen (StrLower (keyWordFunc))) == StrLower (keyWordFunc)) 
{
htCodeOutFixEnd += A_LoopField45 + "\n{\n";
}
else
{
htCodeOutFixEnd += A_LoopField45 + "\n";
}
}
code = StringTrimRight(htCodeOutFixEnd, 1);
}
if (useCurlyBraces == "off") 
{
code = AddCurlyBraces ( code ) ;
}
std::vector<std::string> items46 = LoopParseFunc(code, "\n", "\r");
for (size_t A_Index46 = 1; A_Index46 < items46.size() + 1; A_Index46++)
{
std::string A_LoopField46 = items46[A_Index46 - 1];
outTrimCode += Trim ( A_LoopField46 ) + "\n";
}
code = StringTrimRight(outTrimCode, 1);
// for converting c++ to js and py
code = StrReplace ( code , "{}" , "[]" ) ;
std::string outCodeFixBraces;
for (int A_Index47 = 1; A_Index47<= 2; ++A_Index47)
{
outCodeFixBraces = "";
std::vector<std::string> items48 = LoopParseFunc(code, "\n", "\r");
for (size_t A_Index48 = 1; A_Index48 < items48.size() + 1; A_Index48++)
{
std::string A_LoopField48 = items48[A_Index48 - 1];
if (InStr (Trim (A_LoopField48) , "{") && Trim (A_LoopField48)!= "{") 
{
outCodeFixBraces += Trim ( StrReplace ( Trim ( A_LoopField48 ) , "{" , "" ) ) + "\n{\n";
}
else if (InStr (Trim (A_LoopField48) , "}") && Trim (A_LoopField48)!= "}") 
{
outCodeFixBraces += "}\n" + Trim ( StrReplace ( Trim ( A_LoopField48 ) , "}" , "" ) ) + "\n";
}
else
{
outCodeFixBraces += Trim ( A_LoopField48 ) + "\n";
}
}
code = StringTrimRight(outCodeFixBraces, 1);
}
//MsgBox, % code
// main loop
// main loop
// main loop
// main loop
// main loop
// main loop
// main loop
// main loop
// main loop
// main loop
// main loop
// main loop
// main loop
// main loop
std::vector<std::string> items49 = LoopParseFunc(code, "\n", "\r");
for (size_t A_Index49 = 1; A_Index49 < items49.size() + 1; A_Index49++)
{
std::string A_LoopField49 = items49[A_Index49 - 1];
lineDone = 0;
if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordINT))) == StrLower (keyWordINT)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordINT ) ) ;
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
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordSTR))) == StrLower (keyWordSTR)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordSTR ) ) ;
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
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordBOOL))) == StrLower (keyWordBOOL)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordBOOL ) ) ;
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
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordINT8))) == StrLower (keyWordINT8)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordINT8 ) ) ;
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
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordINT16))) == StrLower (keyWordINT16)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordINT16 ) ) ;
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
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordINT32))) == StrLower (keyWordINT32)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordINT32 ) ) ;
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
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordINT64))) == StrLower (keyWordINT64)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordINT64 ) ) ;
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
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordIF))) == StrLower (keyWordIF)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordIF ) ) ;
//MsgBox, % A_LoopField49
lineDone = 1;
if (langToTranspileTo == "py") 
{
//useParentheses
if (useParentheses == "off") 
{
str8 = "";
str9 = expressionParserTranspiler ( str1 ) ;
std::vector<std::string> items50 = LoopParseFunc(str9, " ");
for (size_t A_Index50 = 1; A_Index50 < items50.size() + 1; A_Index50++)
{
std::string A_LoopField50 = items50[A_Index50 - 1];
str8 = STR ( A_Index50 ) ;
}
if (INT (str8) <= 4) 
{
str2 = "if " + expressionParserTranspiler ( str1 ) + theColon;
str2 = StrReplace ( str2 , "(" , "" ) ;
str2 = StrReplace ( str2 , ")" , "" ) ;
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
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordElseIf))) == StrLower (keyWordElseIf)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordElseIf ) ) ;
//MsgBox, % A_LoopField49
lineDone = 1;
if (langToTranspileTo == "py") 
{
//useParentheses
if (useParentheses == "off") 
{
str8 = "";
str9 = expressionParserTranspiler ( str1 ) ;
std::vector<std::string> items51 = LoopParseFunc(str9, " ");
for (size_t A_Index51 = 1; A_Index51 < items51.size() + 1; A_Index51++)
{
std::string A_LoopField51 = items51[A_Index51 - 1];
str8 = STR ( A_Index51 ) ;
}
if (INT (str8) <= 4) 
{
str2 = "elif " + expressionParserTranspiler ( str1 ) + theColon;
str2 = StrReplace ( str2 , "(" , "" ) ;
str2 = StrReplace ( str2 , ")" , "" ) ;
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
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordElse))) == StrLower (keyWordElse)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordElse ) ) ;
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordWhileLoop))) == StrLower (keyWordWhileLoop)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordWhileLoop ) ) ;
//MsgBox, % A_LoopField49
lineDone = 1;
if (langToTranspileTo == "py") 
{
//useParentheses
if (useParentheses == "off") 
{
str8 = "";
str9 = expressionParserTranspiler ( str1 ) ;
std::vector<std::string> items52 = LoopParseFunc(str9, " ");
for (size_t A_Index52 = 1; A_Index52 < items52.size() + 1; A_Index52++)
{
std::string A_LoopField52 = items52[A_Index52 - 1];
str8 = STR ( A_Index52 ) ;
}
if (INT (str8) <= 4) 
{
str2 = "while " + expressionParserTranspiler ( str1 ) + theColon;
str2 = StrReplace ( str2 , "(" , "" ) ;
str2 = StrReplace ( str2 , ")" , "" ) ;
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
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordForLoop))) == StrLower (keyWordForLoop)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordForLoop ) ) ;
//MsgBox, % A_LoopField49
str2 = transpileForLoop ( langToTranspileTo , forLoopLang , "for " + str1 ) ;
lineDone = 1;
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordLoopInfinite))) == StrLower (keyWordLoopInfinite)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordLoopInfinite ) ) ;
//MsgBox, % A_LoopField49
lineDone = 1;
htCode += A_LoopField49 + "\n";
}
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordLoop))) == StrLower (keyWordLoop)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordLoop ) ) ;
//MsgBox, % A_LoopField49
lineDone = 1;
htCode += A_LoopField49 + "\n";
}
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordLoopParse))) == StrLower (keyWordLoopParse)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordLoopParse ) ) ;
//MsgBox, % A_LoopField49
lineDone = 1;
htCode += A_LoopField49 + "\n";
}
else if (StrLower (A_LoopField49) == StrLower (keyWordContinue)) 
{
//MsgBox, % A_LoopField49
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
else if (StrLower (A_LoopField49) == StrLower (keyWordBreak)) 
{
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordFunc))) == StrLower (keyWordFunc)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordFunc ) ) ;
//MsgBox, % A_LoopField49
lineDone = 1;
htCode += A_LoopField49 + "\n";
}
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordAwait))) == StrLower (keyWordAwait)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordAwait ) ) ;
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordSwitch))) == StrLower (keyWordSwitch)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordSwitch ) ) ;
//MsgBox, % A_LoopField49
lineDone = 1;
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordSwitchCase))) == StrLower (keyWordSwitchCase)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordSwitchCase ) ) ;
//MsgBox, % A_LoopField49
str1 = StrReplace ( str1 , ":" , "" ) ;
str2 = "case " + expressionParserTranspiler ( str1 ) + ":";
lineDone = 1;
htCode += str2 + "\n";
}
else if (StrLower (A_LoopField49) == StrLower (keyWordSwitchDefault)) 
{
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordThrow))) == StrLower (keyWordThrow)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordThrow ) ) ;
//MsgBox, % A_LoopField49
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
else if (StrLower (A_LoopField49) == StrLower (keyWordTry)) 
{
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordCatch))) == StrLower (keyWordCatch)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordCatch ) ) ;
//MsgBox, % A_LoopField49
lineDone = 1;
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
else if (StrLower (A_LoopField49) == StrLower (keyWordFinally)) 
{
//MsgBox, % A_LoopField49
if (langToTranspileTo == "py") 
{
str2 = "finally:";
}
else
{
str2 = "finally";
}
lineDone = 1;
htCode += str2 + "\n";
}
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordArrayDefinition))) == StrLower (keyWordArrayDefinition)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordArrayDefinition ) ) ;
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
str4 = str5 + str1 + " = []" + theSemicolon;
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordArrayOfIntegersDefinition))) == StrLower (keyWordArrayOfIntegersDefinition)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordArrayOfIntegersDefinition ) ) ;
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
str4 = str5 + str1 + " = []" + theSemicolon;
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordArrayOfStringsDefinition))) == StrLower (keyWordArrayOfStringsDefinition)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordArrayOfStringsDefinition ) ) ;
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
str4 = str5 + str1 + " = []" + theSemicolon;
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordArrayOfFloatingPointNumbersDefinition))) == StrLower (keyWordArrayOfFloatingPointNumbersDefinition)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordArrayOfFloatingPointNumbersDefinition ) ) ;
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
str4 = str5 + str1 + " = []" + theSemicolon;
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordArrayOfBooleansDefinition))) == StrLower (keyWordArrayOfBooleansDefinition)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordArrayOfBooleansDefinition ) ) ;
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
str4 = str5 + str1 + " = []" + theSemicolon;
}
else
{
theJSvarDeclaredVarsBugFix += "|" + Trim ( StrReplace ( str1 , ";" , "" ) ) + "|";
str4 = str5 + str1 + theSemicolon;
}
}
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordJavaScriptVar))) == StrLower (keyWordJavaScriptVar)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordJavaScriptVar ) ) ;
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
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordJavaScriptLet))) == StrLower (keyWordJavaScriptLet)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordJavaScriptLet ) ) ;
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
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordJavaScriptConst))) == StrLower (keyWordJavaScriptConst)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordJavaScriptConst ) ) ;
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
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordReturnStatement))) == StrLower (keyWordReturnStatement)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordReturnStatement ) ) ;
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordReturnEndOFaSubroutineFunction))) == StrLower (keyWordReturnEndOFaSubroutineFunction)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordReturnEndOFaSubroutineFunction ) ) ;
//MsgBox, % A_LoopField49
lineDone = 1;
htCode += str10 + "}" + "\n";
}
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordGlobal))) == StrLower (keyWordGlobal)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordGlobal ) ) ;
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordComment))) == StrLower (keyWordComment)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordComment ) ) ;
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordCommentOpenMultiLine))) == StrLower (keyWordCommentOpenMultiLine)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordCommentOpenMultiLine ) ) ;
//MsgBox, % A_LoopField49
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
else if (SubStr (StrLower (A_LoopField49) , 1 , StrLen (StrLower (keyWordCommentCloseMultiLine))) == StrLower (keyWordCommentCloseMultiLine)) 
{
str1 = StringTrimLeft ( A_LoopField49 , StrLen ( keyWordCommentCloseMultiLine ) ) ;
//MsgBox, % A_LoopField49
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
else if (KeyWordsCommands (A_LoopField49 , "check" , keyWordsCommands , langToTranspileTo) == "true" && lineDone == 0) 
{
out_KeyWordsCommands = KeyWordsCommands ( A_LoopField49 , "transpile" , keyWordsCommands , langToTranspileTo ) ;
//MsgBox, % out_KeyWordsCommands
lineDone = 1;
htCode += out_KeyWordsCommands + "\n";
}
else if (InStr (A_LoopField49 , keyWordArrayAppend) || InStr (A_LoopField49 , keyWordArrayPop) || InStr (A_LoopField49 , keyWordArraySize) && lineDone == 0) 
{
//MsgBox, % A_LoopField49
lineDone = 1;
str2 = expressionParserTranspiler ( A_LoopField49 ) + theSemicolon;
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
else if (InStr (A_LoopField49 , keyWordVariablesAssignmentOperator) || InStr (A_LoopField49 , keyWordConcatenationAssignmentOperator) || InStr (A_LoopField49 , keyWordAdditionAssignmentOperator) || InStr (A_LoopField49 , keyWordSubtractionAssignmentOperator) || InStr (A_LoopField49 , keyWordMultiplicationAssignmentOperator) || InStr (A_LoopField49 , keyWordDivisionAssignmentOperator) && lineDone == 0) 
{
str1 = A_LoopField49;
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
//MsgBox, % A_LoopField49
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
else
{
//MsgBox, % "else else else " . A_LoopField49
lineDone = 1;
htCode += A_LoopField49 + "\n";
}
}
htCode = StringTrimRight(htCode, 1);
if (langToTranspileTo == "py") 
{
htCode = indent_nested_curly_braces ( htCode ) ;
}
for (int A_Index53 = 1; A_Index53<= theIdNumOfThe34; ++A_Index53)
{
htCode = StrReplace ( htCode , "ihuiuuhuuhtheidFor-asas-theuhturtyphoutr-" + Chr ( 65 ) + Chr ( 65 ) + STR ( A_Index53 ) + Chr ( 65 ) + Chr ( 65 ) , theIdNumOfThe34theVar[A_Index53] ) ;
}
htCode = StrReplace ( htCode , ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes , Chr ( 92 ) + Chr ( 34 ) ) ;
//arr str allFuncNames
//arr str allFuncLibs
//arr str allFuncs
std::string allFuncsToPutAtTop = "\n";
std::string allLibsToPutAtTop;
for (int A_Index54 = 1; A_Index54<= INT ( allFuncNames[0] ) ; ++A_Index54)
{
if (InStr (htCode , allFuncNames[A_Index54])) 
{
//MsgBox, % allFuncNames[A_Index54]
allFuncsToPutAtTop += allFuncs[A_Index54] + "\n";
allLibsToPutAtTop += allFuncLibs[A_Index54] + "|";
}
}
allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTop, 1);
std::string allLibsToPutAtTopTEMP;
std::vector<std::string> items55 = LoopParseFunc(allLibsToPutAtTop, "|");
for (size_t A_Index55 = 1; A_Index55 < items55.size() + 1; A_Index55++)
{
std::string A_LoopField55 = items55[A_Index55 - 1];
allLibsToPutAtTopTEMP += A_LoopField55 + "\n";
}
allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTopTEMP, 1);
allLibsToPutAtTop = SortLikeAHK(allLibsToPutAtTop, "U");
htCode = allLibsToPutAtTop + "\n" + allFuncsToPutAtTop + "\n" + htCode;
print(htCode);
std::vector<std::string> items56 = LoopParseFunc(fileExtention);
for (size_t A_Index56 = 1; A_Index56 < items56.size() + 1; A_Index56++)
{
std::string A_LoopField56 = items56[A_Index56 - 1];
filePathOfCode = StringTrimRight(filePathOfCode, 1);
}
filePathOfCode = filePathOfCode + langToTranspileTo;
FileDelete(filePathOfCode);
FileAppend(htCode, filePathOfCode);
}
int main(int argc, char* argv[])
{
compiler ( ) ;
return 0;
}