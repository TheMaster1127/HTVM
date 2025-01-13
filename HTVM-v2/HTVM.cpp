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
        print("Usage: HTVM <yourCodeFileName.yourExtension> <HTVM-instructions.txt> [optional LangToTranspileTo]\n\nOptions:\n  <yourCodeFileName.yourExtension>  The source code file to transpile.\n  <HTVM-instructions.txt>              The instructions file for transpilation.\n  [LangToTranspileTo]                Optional: Specify the target language (cpp, py, js, go, lua, cs, java, kt, rb, nim, ahk, swift, dart, ts, scala, groovy, htvm or <yourExtension>).\n\nExample:\n  HTVM main.htvm HTVM-instructions.txt cpp\n");
        return;
    }
    std::vector<std::string> items1 = LoopParseFunc(params, "\n", "\r");
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        allArgs += Trim(A_LoopField1) + "\n";
    }
    allArgs = StringTrimRight(allArgs, 1);
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
int int0 = 0;
int int1 = 0;
int int2 = 0;
int int3 = 0;
int int4 = 0;
int int5 = 0;
int int6 = 0;
int int7 = 0;
std::vector<std::string> argHTVMinstrMORE;
std::string extraCodeReturned = "";
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
std::vector<std::string> programmingBlock_SCALA;
std::vector<std::string> programmingBlock_GROOVY;
std::vector<std::string> programmingBlock_HTVM;
std::vector<std::string> programmingBlock_HTVMsyntax;
std::string langToConvertTo = "";
std::string langFileExtension = "";
std::string commands = "";
std::string keyWordAlliance = "";
std::string keyWordCrew = "";
std::string keyWordMethod = "";
std::string keyWordDefObj = "";
std::string keyWordPorp = "";
std::string keyWordThis = "";
std::string keyWordInclude = "";
std::string keyWordIncludeInTheTranspiledLang = "";
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
std::string keyWordCodeInTheTranspiledLangStartSCALA = "";
std::string keyWordCodeInTheTranspiledLangEndSCALA = "";
std::string keyWordCodeInTheTranspiledLangStartGROOVY = "";
std::string keyWordCodeInTheTranspiledLangEndGROOVY = "";
std::string keyWordCodeInTheTranspiledLangStartHTVM = "";
std::string keyWordCodeInTheTranspiledLangEndHTVM = "";
std::string keyWordCodeInHTVMstart = "";
std::string keyWordCodeInHTVMend = "";
std::string keyWordCodeInOtherHTVMsyntaxStart = "";
std::string keyWordCodeInOtherHTVMsyntaxEnd = "";
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
std::string keyWordSwitch = "";
std::string keyWordSwitchCase = "";
std::string keyWordSwitchDefault = "";
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
std::string keyWordPorp_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordThis_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordInclude_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordIncludeInTheTranspiledLang_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
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
std::string keyWordCodeInTheTranspiledLangStartSCALA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndSCALA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartGROOVY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndGROOVY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartHTVM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndHTVM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInHTVMstart_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInHTVMend_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInOtherHTVMsyntaxStart_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInOtherHTVMsyntaxEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
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
std::string keyWordSwitch_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordSwitchCase_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordSwitchDefault_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
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
std::string out_KeyWordsCommands = "";
std::string outTrimCode = "";
std::string htCode = "";
std::string outVarOperator = "";
int lineDone = 0;
int areWeInAFuncFromInstructions = 0;
int areWeInAFuncFromInstructionsLineNum = 0;
std::string theCppVarForErrors = "jhku-dfsds-ds-d-ffdsf-sdfsfdsedsf";
std::string theJSvarDeclaredVarsBugFix = "|";
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string KeyWordsCommands(std::string theCodeCommands, std::string mode, std::string keyWordsCommands, std::string langToConvertTo) {
    theCodeCommands = StrReplace(theCodeCommands, "%", "");
    if (mode == "check") {
        std::vector<std::string> items1 = LoopParseFunc(keyWordsCommands, "|");
        for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
            std::string A_LoopField1 = items1[A_Index1 - 0];
            std::vector<std::string> items2 = LoopParseFunc(A_LoopField1, ",");
            for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
                std::string A_LoopField2 = items2[A_Index2 - 0];
                if (A_Index2 == 1) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField2 + ", ")) == StrLower(A_LoopField2 + ", ")) {
                        //MsgBox, true
                        return "true";
                    }
                }
                if (A_Index2 == 1) {
                    if (theCodeCommands == A_LoopField2) {
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
        std::vector<std::string> items3 = LoopParseFunc(keyWordsCommands, "|");
        for (size_t A_Index3 = 0; A_Index3 < items3.size() + 0; A_Index3++) {
            std::string A_LoopField3 = items3[A_Index3 - 0];
            AIndex = A_Index3;
            std::vector<std::string> items4 = LoopParseFunc(A_LoopField3, ",");
            for (size_t A_Index4 = 0; A_Index4 < items4.size() + 0; A_Index4++) {
                std::string A_LoopField4 = items4[A_Index4 - 0];
                if (A_Index4 == 1) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField4 + ", ")) == StrLower(A_LoopField4 + ", ")) {
                        //MsgBox, true
                        keyWordsCommandsNumLine = AIndex;
                        break;
                    }
                }
                if (A_Index4 == 1) {
                    //MsgBox, %theCodeCommands% = %A_LoopField4%
                    if (theCodeCommands == A_LoopField4) {
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
        if (langToConvertTo != "py") {
            semicolon = ";";
        }
        std::vector<std::string> theCodeCommand;
        theCodeCommands = Trim(theCodeCommands);
        std::vector<std::string> items5 = LoopParseFunc(theCodeCommands, ",");
        for (size_t A_Index5 = 0; A_Index5 < items5.size() + 0; A_Index5++) {
            std::string A_LoopField5 = items5[A_Index5 - 0];
            theCodeCommand.push_back(Trim(A_LoopField5));
            //MsgBox, % A_LoopField5
        }
        std::vector<std::string> items6 = LoopParseFunc(keyWordsCommands, "|");
        for (size_t A_Index6 = 0; A_Index6 < items6.size() + 0; A_Index6++) {
            std::string A_LoopField6 = items6[A_Index6 - 0];
            if (keyWordsCommandsNumLine == A_Index6) {
                //MsgBox, % A_LoopField6
                std::vector<std::string> items7 = LoopParseFunc(A_LoopField6, ",");
                for (size_t A_Index7 = 0; A_Index7 < items7.size() + 0; A_Index7++) {
                    std::string A_LoopField7 = items7[A_Index7 - 0];
                    if (A_Index7 == 1) {
                        outConstuctTheOutFromTheCommandsFucnName = A_LoopField7;
                    }
                    else if (A_Index7 == 2) {
                        //MsgBox, % A_LoopField7
                        if (A_LoopField7 == "lineTranspile") {
                            outConstuctTheOutFromTheCommandsLineTranspile = 1;
                        }
                        if (A_LoopField7 == "OUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField7 == "INOUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField7 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField7, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    }
                    else if (A_Index7 == 3) {
                        if (outConstuctTheOutFromTheCommandsLineTranspile == 1) {
                            outConstuctTheOutFromTheCommandsLineTranspileText = A_LoopField7;
                        }
                        if (A_LoopField7 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField7, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    } else {
                        //MsgBox, % theCodeCommand[theCodeCommandNum]
                        if (InStr(A_LoopField7, Chr(39))) {
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
    std::vector<std::string> items8 = LoopParseFunc(line);
    for (size_t A_Index8 = 0; A_Index8 < items8.size() + 0; A_Index8++) {
        std::string A_LoopField8 = items8[A_Index8 - 0];
        lineArr.push_back(A_LoopField8);
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
    for (int A_Index9 = 0; A_Index9 < lineArr.size() + 0; A_Index9++) {
        char1 = "";
        char2 = "";
        char3 = "";
        char4 = "";
        isMatch = 0;
        if (A_Index9 != 0) {
            isStart = 0;
        }
        sildingLine = "";
        for (int A_Index10 = 0; A_Index10 < matchStringLEN + 0; A_Index10++) {
            if (A_Index10 + i1 <= lineArr.size() - 1) {
                sildingLine += lineArr[A_Index10 + i1];
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
            if (i1 + matchStringLEN < lineArr.size()) {
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
            if (allPosForReplacing.size() > 0) {
                for (int A_Index11 = 0; A_Index11 < allPosForReplacing.size() + 0; A_Index11++) {
                    if (i1 + 1 != allPosForReplacing[A_Index11]) {
                        allPosForReplacing.push_back(i1 + 1);
                        break;
                    }
                }
            } else {
                allPosForReplacing.push_back(i1 + 1);
            }
        }
        i1++;
    }
    std::string lineTEMP = "";
    lineOut = line;
    //print(allPosForReplacing)
    if (allPosForReplacing.size() > 0) {
        // matchStringLEN
        // replaceStringLEN
        int l2 = 0;
        int currentPos = 0;
        int onceEnd = 0;
        for (int A_Index12 = 0; A_Index12 < allPosForReplacing.size() + 0; A_Index12++) {
            if (A_Index12 == 0) {
                currentPos = allPosForReplacing[A_Index12];
            } else {
                currentPos = allPosForReplacing[A_Index12] - (matchStringLEN - replaceStringLEN);
            }
            onceEnd = 0;
            std::vector<std::string> items13 = LoopParseFunc(lineOut);
            for (size_t A_Index13 = 0; A_Index13 < items13.size() + 0; A_Index13++) {
                std::string A_LoopField13 = items13[A_Index13 - 0];
                if (A_Index13 + 2 > currentPos && A_Index13 + 1 < currentPos + matchStringLEN) {
                    onceEnd++;
                    //print("DDDDDDDDDDD" . STR(A_Index13))
                    if (onceEnd == 1) {
                        lineTEMP += replaceString;
                    }
                } else {
                    lineTEMP += A_LoopField13;
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
std::string SubStrLastChars(std::string text, int numOfChars) {
    std::string LastOut = "";
    int NumOfChars = 0;
    std::vector<std::string> items14 = LoopParseFunc(text);
    for (size_t A_Index14 = 0; A_Index14 < items14.size() + 0; A_Index14++) {
        std::string A_LoopField14 = items14[A_Index14 - 0];
        NumOfChars++;
    }
    for (int A_Index15 = 0; A_Index15 < numOfChars + 0; A_Index15++) {
        NumOfChars--;
    }
    std::vector<std::string> items16 = LoopParseFunc(text);
    for (size_t A_Index16 = 0; A_Index16 < items16.size() + 0; A_Index16++) {
        std::string A_LoopField16 = items16[A_Index16 - 0];
        if (A_Index16 >= NumOfChars) {
            LastOut += A_LoopField16;
        }
    }
    return LastOut;
}
std::string ExtractDigits(std::string inputString) {
    std::string digits = "";
    std::vector<std::string> items17 = LoopParseFunc(inputString);
    for (size_t A_Index17 = 0; A_Index17 < items17.size() + 0; A_Index17++) {
        std::string A_LoopField17 = items17[A_Index17 - 0];
        if (RegExMatch(A_LoopField17, "\\d")) {
            digits += A_LoopField17;
        }
    }
    return digits;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Helper function to create spaces
std::string spaces(int n) {
    std::string s = "";
    if (n != 0) {
        for (int A_Index18 = 0; A_Index18 < n + 0; A_Index18++) {
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
    std::vector<std::string> items19 = LoopParseFunc(string123);
    for (size_t A_Index19 = 0; A_Index19 < items19.size() + 0; A_Index19++) {
        std::string A_LoopField19 = items19[A_Index19 - 0];
        // Check if the current character is a space
        if (A_LoopField19 == Chr(32)) {
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
    std::vector<std::string> items20 = LoopParseFunc(input);
    for (size_t A_Index20 = 0; A_Index20 < items20.size() + 0; A_Index20++) {
        std::string A_LoopField20 = items20[A_Index20 - 0];
        if (A_LoopField20 != " " || foundNonSpace) {
            result += A_LoopField20;
            foundNonSpace = true;
        }
    }
    return result;
}
std::string getLastChar(std::string strippedString) {
    std::string lastChar;
    std::vector<std::string> items21 = LoopParseFunc(strippedString);
    for (size_t A_Index21 = 0; A_Index21 < items21.size() + 0; A_Index21++) {
        std::string A_LoopField21 = items21[A_Index21 - 0];
        lastChar = A_LoopField21;
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
    std::vector<std::string> items22 = LoopParseFunc(pythonCode, "\n", "\r");
    for (size_t A_Index22 = 0; A_Index22 < items22.size() + 0; A_Index22++) {
        std::string A_LoopField22 = items22[A_Index22 - 0];
        line = A_LoopField22;
        stripped = Trim(line);
        if (stripped == "") {
            result += line + "\n";
            continue;
        }
        // Count leading spaces
        indent = StrLen(line) - StrLen(LTrim(line));
        // Close braces for unindents
        for (int A_Index23 = 0; ; A_Index23++) {
            if (indentLevel <= indent) {
                break;
            }
            indentLevel -= 4;
            result += spaces(indentLevel) + "}\n";
        }
        // Add opening brace for new blocks
        if (getLastChar(stripped) == ":" && SubStr(StrLower(Trim(A_LoopField22)), 1, StrLen(StrLower(keyWordComment))) != StrLower(keyWordComment)) {
            result += SubStr(line, 1, -1) + " {\n";
            indentLevel += 4;
        } else {
            result += line + "\n";
        }
    }
    // Close any remaining open braces
    for (int A_Index24 = 0; ; A_Index24++) {
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
    for (int A_Index25 = 0; A_Index25 < count + 0; A_Index25++) {
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
    std::vector<std::string> items26 = LoopParseFunc(input_string, "\n", "\r");
    for (size_t A_Index26 = 0; A_Index26 < items26.size() + 0; A_Index26++) {
        std::string A_LoopField26 = items26[A_Index26 - 0];
        trimmed_line = Trim(A_LoopField26);
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
        std::string resultOut = "";
        std::vector<std::string> items27 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index27 = 0; A_Index27 < items27.size() + 0; A_Index27++) {
            std::string A_LoopField27 = items27[A_Index27 - 0];
            if (Trim(A_LoopField27) != "{" && Trim(A_LoopField27) != "}") {
                resultOut += A_LoopField27 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
    } else {
        // format curly braces in a K&R style
        std::vector<std::string> lookIntoFurture;
        std::vector<std::string> items28 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index28 = 0; A_Index28 < items28.size() + 0; A_Index28++) {
            std::string A_LoopField28 = items28[A_Index28 - 0];
            lookIntoFurture.push_back(Trim(A_LoopField28));
        }
        lookIntoFurture.push_back(" ");
        std::string resultOut = "";
        int skipNext = 0;
        std::vector<std::string> items29 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index29 = 0; A_Index29 < items29.size() + 0; A_Index29++) {
            std::string A_LoopField29 = items29[A_Index29 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (Trim(lookIntoFurture[A_Index29 + 1]) == "{") {
                resultOut += A_LoopField29 + " " + culyOpenFix + "\n";
                skipNext = 2;
            }
            if (skipNext == 0) {
                resultOut += A_LoopField29 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
        std::vector<std::string> lookIntoFurture2;
        std::vector<std::string> items30 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index30 = 0; A_Index30 < items30.size() + 0; A_Index30++) {
            std::string A_LoopField30 = items30[A_Index30 - 0];
            lookIntoFurture2.push_back(Trim(A_LoopField30));
        }
        lookIntoFurture2.push_back(" ");
        resultOut = "";
        skipNext = 0;
        std::string addSpacesAtTheBegginig;
        std::vector<std::string> items31 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index31 = 0; A_Index31 < items31.size() + 0; A_Index31++) {
            std::string A_LoopField31 = items31[A_Index31 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (langToConvertTo != "lua" && langToConvertTo != "rb" && langToConvertTo != langFileExtension_2) {
                if (Trim(A_LoopField31) == "}" && Trim(lookIntoFurture2[A_Index31 + 1]) == "else {") {
                    skipNext = 2;
                    addSpacesAtTheBegginig = "";
                    std::vector<std::string> items32 = LoopParseFunc(A_LoopField31);
                    for (size_t A_Index32 = 0; A_Index32 < items32.size() + 0; A_Index32++) {
                        std::string A_LoopField32 = items32[A_Index32 - 0];
                        if (A_LoopField32 == " ") {
                            if (A_LoopField32 != " ") {
                                break;
                            }
                            addSpacesAtTheBegginig += StrReplace(A_LoopField32, "}", culyCloseFix);
                        }
                    }
                    resultOut += addSpacesAtTheBegginig + culyCloseFix + " else " + culyOpenFix + "\n";
                }
            }
            if (skipNext == 0) {
                resultOut += A_LoopField31 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
    }
    resultOut = "";
    std::string ALoopField;
    std::vector<std::string> items33 = LoopParseFunc(result, "\n", "\r");
    for (size_t A_Index33 = 0; A_Index33 < items33.size() + 0; A_Index33++) {
        std::string A_LoopField33 = items33[A_Index33 - 0];
        if (CheckOddLeadingSpaces(A_LoopField33) == "1") {
            ALoopField = StringTrimLeft(A_LoopField33, 1);
            resultOut += ALoopField + "\n";
        } else {
            resultOut += A_LoopField33 + "\n";
        }
    }
    result = StringTrimRight(resultOut, 1);
    std::string fixResultFIX = "";
    if (langToConvertTo == langFileExtension_2 && modeCurlyBracesOn == 1) {
        std::vector<std::string> items34 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index34 = 0; A_Index34 < items34.size() + 0; A_Index34++) {
            std::string A_LoopField34 = items34[A_Index34 - 0];
            if (Trim(A_LoopField34) == "}") {
                fixResultFIX += StrReplace(A_LoopField34, "}", culyCloseFix) + "\n";
            } else {
                fixResultFIX += A_LoopField34 + "\n";
            }
        }
        result = StringTrimRight(fixResultFIX, 1);
    }
    // Return the result
    return result;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// path.path.path:propName1[str],propName2[bool],propName3[str array]|path.path.path:propName1[str],propName2[bool],propName3[str array]
std::string OSPstrArrayStrALLobjInOSP = "";
std::string HoldOSPdethodNamePath = "";
std::string findTypeOfOSPprop(std::string fullARRAYstr, std::string FromPath) {
    std::string outType = "";
    // if the fullARRAYstr is in this format
    // path.path.path:propName1[str],propName2[bool],propName3[str array]|path.path.path:propName1[str],propName2[bool],propName3[str array]
    std::string outFormat = "";
    std::string outFormatHELP1 = "";
    std::string outFormatHELP2 = "";
    std::vector<std::string> items35 = LoopParseFunc(fullARRAYstr, "|");
    for (size_t A_Index35 = 0; A_Index35 < items35.size() + 0; A_Index35++) {
        std::string A_LoopField35 = items35[A_Index35 - 0];
        if (Trim(A_LoopField35) != "") {
            outFormatHELP1 = StrSplit(A_LoopField35, ":", 1);
            outFormatHELP2 = StrSplit(A_LoopField35, ":", 2);
            std::vector<std::string> items36 = LoopParseFunc(outFormatHELP2, ",");
            for (size_t A_Index36 = 0; A_Index36 < items36.size() + 0; A_Index36++) {
                std::string A_LoopField36 = items36[A_Index36 - 0];
                outFormat += outFormatHELP1 + "." + A_LoopField36 + "|";
            }
        }
    }
    outFormat = StringTrimRight(outFormat, 1);
    std::vector<std::string> items37 = LoopParseFunc(outFormat, "|");
    for (size_t A_Index37 = 0; A_Index37 < items37.size() + 0; A_Index37++) {
        std::string A_LoopField37 = items37[A_Index37 - 0];
        if (Trim(A_LoopField37) != "") {
            if (StrSplit(Trim(A_LoopField37), "[", 1) == Trim(FromPath)) {
                outType = StrSplit(Trim(A_LoopField37), "[", 2);
                outType = StringTrimRight(outType, 1);
                break;
            }
        }
    }
    if (outType == "vector<int>") {
        outType = "std::vector<int>&";
    }
    else if (outType == "vector<string>") {
        outType = "std::vector<std::string>&";
    }
    else if (outType == "vector<string>") {
        outType = "std::vector<std::string>&";
    }
    else if (outType == "vector<float>") {
        outType = "std::vector<float>&";
    }
    else if (outType == "vector<bool>") {
        outType = "std::vector<bool>&";
    }
    else if (outType == Trim(keyWordINT)) {
        outType = "int";
    }
    else if (outType == Trim(keyWordSTR)) {
        outType = "std::string";
    }
    else if (outType == Trim(keyWordFLOAT)) {
        outType = "float";
    }
    else if (outType == Trim(keyWordBOOL)) {
        outType = "bool";
    }
    else if (outType == Trim(keyWordINT8)) {
        outType = "int8_t";
    }
    else if (outType == Trim(keyWordINT16)) {
        outType = "int16_t";
    }
    else if (outType == Trim(keyWordINT32)) {
        outType = "int32_t";
    }
    else if (outType == Trim(keyWordINT64)) {
        outType = "int64_t";
    }
    return outType;
}
std::string REMOVELastSTRfromDOT(std::string THESTR) {
    std::string THESTRout = "";
    if (Trim(THESTR) == "") {
        return "";
    }
    int count12345 = 0;
    std::vector<std::string> items38 = LoopParseFunc(THESTR, ".");
    for (size_t A_Index38 = 0; A_Index38 < items38.size() + 0; A_Index38++) {
        std::string A_LoopField38 = items38[A_Index38 - 0];
        count12345++;
    }
    std::vector<std::string> items39 = LoopParseFunc(THESTR, ".");
    for (size_t A_Index39 = 0; A_Index39 < items39.size() + 0; A_Index39++) {
        std::string A_LoopField39 = items39[A_Index39 - 0];
        if (count12345 == A_Index39) {
            break;
        } else {
            THESTRout += Trim(A_LoopField39) + ".";
        }
    }
    THESTRout = StringTrimRight(THESTRout, 1);
    return THESTRout;
}
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
std::string replaceTheOSPpathsPY_JS(std::string theSTR123, std::string ALoopFieldIN) {
    if (Trim(theSTR123) == "") {
        return "";
    }
    if (Trim(ALoopFieldIN) == "") {
        return "";
    }
    std::string type = "";
    std::string theSTR123out = "";
    std::string ALoopField = "";
    std::string ALoopField1 = "";
    std::string ALoopField11 = "";
    if (InStr(ALoopFieldIN, "[")) {
        // ALoopFieldIN
        // animalsKingdom.animals.Dog.typeOf2[2]
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField11 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(ALoopField1) + "[" + ALoopField11;
        // REMOVELastSTRfromDOT(param1)
        theSTR123 = StrReplace(theSTR123, Trim(ALoopField), "OSPHTVMOSP_" + StrReplace(ALoopField1, ".", "_"));
    } else {
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(StrSplit(Trim(ALoopFieldIN), "]", 1));
        ALoopField1 = "[" + Trim(StrSplit(ALoopField1, "[", 2)) + "]";
        theSTR123 = StrReplace(theSTR123, Trim(ALoopFieldIN), "OSPHTVMOSP_" + StrReplace(ALoopFieldIN, ".", "_"));
    }
    //this__OSP__this
    theSTR123 = RegExReplace(theSTR123, "\\bthis\\b", "this__OSP__this[0]");
    theSTR123 = StrReplace(theSTR123, "OSPHTVMOSP_OSPHTVMOSP_", "OSPHTVMOSP_");
    return theSTR123;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string replaceTheOSPpathsLEFT(std::string theSTR123, std::string ALoopFieldIN) {
    if (Trim(theSTR123) == "") {
        return "";
    }
    if (Trim(ALoopFieldIN) == "") {
        return "";
    }
    std::string type = "";
    std::string theSTR123out = "";
    std::string ALoopField = "";
    std::string ALoopField1 = "";
    std::string ALoopField11 = "";
    if (InStr(ALoopFieldIN, "[")) {
        // ALoopFieldIN
        // animalsKingdom.animals.Dog.typeOf2[2]
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField11 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(ALoopField1) + "[" + ALoopField11;
        // REMOVELastSTRfromDOT(param1)
        theSTR123 = StrReplace(theSTR123, Trim(ALoopField), "OSPHTVMOSP_" + StrReplace(ALoopField1, ".", "_"));
    } else {
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(StrSplit(Trim(ALoopFieldIN), "]", 1));
        ALoopField1 = "[" + Trim(StrSplit(ALoopField1, "[", 2)) + "]";
        theSTR123 = StrReplace(theSTR123, Trim(ALoopFieldIN), "OSPHTVMOSP_" + StrReplace(ALoopFieldIN, ".", "_"));
    }
    //this__OSP__this
    theSTR123 = RegExReplace(theSTR123, "\\bthis\\b", "std::any_cast<std::string>((*this__OSP__this)[0])");
    theSTR123 = StrReplace(theSTR123, "OSPHTVMOSP_OSPHTVMOSP_", "OSPHTVMOSP_");
    return theSTR123;
}
std::string replaceTheOSPpathsRIGHT(std::string theSTR123, std::string ALoopFieldIN) {
    if (Trim(theSTR123) == "") {
        return "";
    }
    if (Trim(ALoopFieldIN) == "") {
        return "";
    }
    std::string type = "";
    std::string theSTR123out = "";
    std::string ALoopField = "";
    std::string ALoopField1 = "";
    std::string ALoopField11 = "";
    if (InStr(ALoopFieldIN, "[")) {
        // ALoopFieldIN
        // animalsKingdom.animals.Dog.typeOf2[2]
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField11 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(ALoopField1) + "[" + ALoopField11;
        // REMOVELastSTRfromDOT(param1)
        type = findTypeOfOSPprop(OSPstrArrayStrALLobjInOSP, ALoopField);
        //MsgBox, % type
        theSTR123 = StrReplace(theSTR123, Trim(ALoopField), "std::any_cast<" + type + ">(OSPHTVMOSP_" + StrReplace(ALoopField1, ".", "_") + ")");
    } else {
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(StrSplit(Trim(ALoopFieldIN), "]", 1));
        ALoopField1 = "[" + Trim(StrSplit(ALoopField1, "[", 2)) + "]";
        theSTR123 = StrReplace(theSTR123, Trim(ALoopFieldIN), "OSPHTVMOSP_" + StrReplace(ALoopFieldIN, ".", "_"));
    }
    //this__OSP__this
    theSTR123 = RegExReplace(theSTR123, "\\bthis\\b", "std::any_cast<std::string>((*this__OSP__this)[0])");
    theSTR123 = StrReplace(theSTR123, "OSPHTVMOSP_OSPHTVMOSP_", "OSPHTVMOSP_");
    return theSTR123;
}
std::string CheckStringPosition(std::string text, std::string target, std::string reference) {
    std::string posReference = SubStr(text, 1, StrLen(reference));
    std::string posTarget = SubStr(text, 1, StrLen(target));
    // Check if both strings are found (not using InStr)
    if (posReference != "" && posTarget != "") {
        // Manually find the positions of the target and reference
        posTarget = RegExMatch(text, target);
        posReference = RegExMatch(text, reference);
        // Compare positions of target and reference
        if (posTarget < posReference) {
            return "left";
        }
        else if (posTarget > posReference) {
            return "not left";
        } else {
            return "uuh";
        }
    } else {
        return "One or both strings not found.";
    }
    return "huh";
}
std::string getIndexOfTheStrArrayStrOST(std::string ALoopField, std::string theSringOSPlineARRAYstrstrSTR) {
    std::vector<std::string> items40 = LoopParseFunc(theSringOSPlineARRAYstrstrSTR, "|");
    for (size_t A_Index40 = 0; A_Index40 < items40.size() + 0; A_Index40++) {
        std::string A_LoopField40 = items40[A_Index40 - 0];
        if (Trim(StrSplit(A_LoopField40, ":", 1)) == Trim(ALoopField)) {
            return STR(A_Index40);
        }
    }
    return "0";
}
std::string parserOSPgloabl(std::string theSringOSPline, std::string str123) {
    std::string str_1 = "";
    std::string str_2 = "";
    std::string str_3 = "";
    std::string str_4 = "";
    std::string str_5 = "";
    std::string str_6 = "";
    std::string HELPHoldOSPdethodNamePath = "";
    HELPHoldOSPdethodNamePath = StringTrimRight(HoldOSPdethodNamePath, 1);
    std::vector<std::string> items41 = LoopParseFunc(theSringOSPline, "|");
    for (size_t A_Index41 = 0; A_Index41 < items41.size() + 0; A_Index41++) {
        std::string A_LoopField41 = items41[A_Index41 - 0];
        str_1 += Trim(StrSplit(A_LoopField41, ":", 1)) + "\n";
        str_5 = Trim(StrSplit(A_LoopField41, ":", 1));
        str_6 = Trim(StrSplit(A_LoopField41, ":", 2));
        std::vector<std::string> items42 = LoopParseFunc(str_6, ",");
        for (size_t A_Index42 = 0; A_Index42 < items42.size() + 0; A_Index42++) {
            std::string A_LoopField42 = items42[A_Index42 - 0];
            str_1 += str_5 + "." + Trim(StrSplit(A_LoopField42, "[", 1)) + "[" + STR(A_Index42) + "]\n";
        }
    }
    str_1 += StrReplace(HELPHoldOSPdethodNamePath, "|", "\n");
    std::string shortestLine = "";
    std::string currentLine = "";
    int currentLength = 0;
    int minLength = 0;
    std::string tempStr = "";
    // Sorting by repeatedly finding and appending the shortest line
    for (int A_Index43 = 0; ; A_Index43++) {
        // Initialize variables to track the shortest line in this pass
        shortestLine = "";
        minLength = 999999;
        // Find the shortest line in str_1
        std::vector<std::string> items44 = LoopParseFunc(str_1, "\n", "\r");
        for (size_t A_Index44 = 0; A_Index44 < items44.size() + 0; A_Index44++) {
            std::string A_LoopField44 = items44[A_Index44 - 0];
            currentLine = A_LoopField44;
            currentLength = StrLen(currentLine);
            if (currentLength < minLength) {
                minLength = currentLength;
                shortestLine = currentLine;
            }
        }
        // If no shortest line is found, break (str_1 is empty)
        if (shortestLine == "") {
            break;
        }
        // Add the shortest line to the sorted result
        str_2 += shortestLine + "\n";
        // Rebuild str_1 without the shortest line
        tempStr = "";
        std::vector<std::string> items45 = LoopParseFunc(str_1, "\n", "\r");
        for (size_t A_Index45 = 0; A_Index45 < items45.size() + 0; A_Index45++) {
            std::string A_LoopField45 = items45[A_Index45 - 0];
            if (A_LoopField45 != shortestLine) {
                tempStr += A_LoopField45 + "\n";
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
    int index = 0;
    int lineNum = 0;
    std::vector<std::string> items46 = LoopParseFunc(str_2, "\n", "\r");
    for (size_t A_Index46 = 0; A_Index46 < items46.size() + 0; A_Index46++) {
        std::string A_LoopField46 = items46[A_Index46 - 0];
        lineCount++;
    }
    // Reverse the order by re-parsing and appending lines in reverse order
    for (int A_Index47 = 0; A_Index47 < lineCount + 0; A_Index47++) {
        // Inner loop to find the (lineCount - A_Index47 + 1)-th line
        index = lineCount - A_Index47 + 1;
        currentLine = "";
        lineNum = 0;
        std::vector<std::string> items48 = LoopParseFunc(str_2, "\n", "\r");
        for (size_t A_Index48 = 0; A_Index48 < items48.size() + 0; A_Index48++) {
            std::string A_LoopField48 = items48[A_Index48 - 0];
            lineNum++;
            if (lineNum == index) {
                currentLine = A_LoopField48;
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
    std::vector<std::string> items49 = LoopParseFunc(str_2, "\n", "\r");
    for (size_t A_Index49 = 0; A_Index49 < items49.size() + 0; A_Index49++) {
        std::string A_LoopField49 = items49[A_Index49 - 0];
        if (SubStr(A_LoopField49, 1, StrLen(keyWordFunc)) != keyWordFunc) {
            if (langToConvertTo == "cpp") {
                if (Trim(A_LoopField49) != "") {
                    if (InStr(str123, " += ")) {
                        str6 = " += ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    }
                    else if (InStr(str123, " = ")) {
                        str6 = " = ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    }
                    else if (InStr(str123, " -= ")) {
                        str6 = " -= ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    }
                    else if (InStr(str123, " *= ")) {
                        str6 = " *= ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    }
                    else if (InStr(str123, " /= ")) {
                        str6 = " /= ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    } else {
                        str123 = replaceTheOSPpathsRIGHT(str123, A_LoopField49);
                    }
                    //;;;;
                }
            } else {
                if (Trim(A_LoopField49) != "") {
                    str123 = replaceTheOSPpathsPY_JS(str123, A_LoopField49);
                }
            }
        }
    }
    return str123;
}
bool isLineAconstruct(std::string line) {
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
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordElse) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordElse) + " " + keyWordCurlyBraceOpen) {
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
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordLoopInfinite) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordLoopInfinite) + " " + keyWordCurlyBraceOpen) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordSwitch))) == StrLower(keyWordSwitch)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordSwitchCase))) == StrLower(keyWordSwitchCase)) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordSwitchDefault) || StrLower(Trim(line)) == StrLower(keyWordSwitchDefault + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordSwitchDefault))) == keyWordCurlyBraceClose + " " + StrLower(keyWordSwitchDefault)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordSwitchDefault) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordSwitchDefault) + " " + keyWordCurlyBraceOpen) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordTry) || StrLower(Trim(line)) == StrLower(keyWordTry + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordTry))) == keyWordCurlyBraceClose + " " + StrLower(keyWordTry)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordTry) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordTry) + " " + keyWordCurlyBraceOpen) {
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
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordFinally) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordFinally) + " " + keyWordCurlyBraceOpen) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc)) {
        return true;
    }
    return false;
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
std::string expressionParserTranspiler(std::string expression) {
    if (langToConvertTo == "htvm") {
        expression = expression;
    }
    if (langToConvertTo == "cpp") {
        expression = expression;
    }
    if (langToConvertTo == "py") {
        expression = expression;
    }
    if (langToConvertTo == "js") {
        expression = expression;
    }
    if (langToConvertTo == "go") {
        expression = expression;
    }
    if (langToConvertTo == "lua") {
        expression = expression;
    }
    if (langToConvertTo == "cs") {
        expression = expression;
    }
    if (langToConvertTo == "java") {
        expression = expression;
    }
    if (langToConvertTo == "kt") {
        expression = expression;
    }
    if (langToConvertTo == "rb") {
        expression = expression;
    }
    if (langToConvertTo == "nim") {
        expression = expression;
    }
    if (langToConvertTo == "ahk") {
        expression = expression;
    }
    if (langToConvertTo == "swift") {
        expression = expression;
    }
    if (langToConvertTo == "dart") {
        expression = expression;
    }
    if (langToConvertTo == "ts") {
        expression = expression;
    }
    if (langToConvertTo == "scala") {
        expression = expression;
    }
    if (langToConvertTo == "groovy") {
        expression = expression;
    }
    if (langToConvertTo == langFileExtension_2) {
        expression = expression;
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
std::string compiler(std::string htCode, std::string allInstructionFile, std::string mode, std::string langToConvertToParam = "") {
    extraCodeReturned = "";
    std::string instructions = allInstructionFile;
    std::vector<std::string> items50 = LoopParseFunc(allInstructionFile, "\n", "\r");
    for (size_t A_Index50 = 0; A_Index50 < items50.size() + 0; A_Index50++) {
        std::string A_LoopField50 = items50[A_Index50 - 0];
        if (A_Index50 == 0) {
            langToConvertTo = Trim(A_LoopField50);
        }
        if (A_Index50 == 1) {
            langFileExtension = Trim(A_LoopField50);
        }
        if (A_Index50 == 2) {
            commands = Trim(A_LoopField50);
        }
        if (A_Index50 == 3) {
            keyWordAlliance = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 4) {
            keyWordCrew = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 5) {
            keyWordMethod = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 6) {
            keyWordDefObj = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 7) {
            keyWordPorp = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 8) {
            keyWordThis = Trim(A_LoopField50);
        }
        if (A_Index50 == 9) {
            keyWordInclude = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 10) {
            keyWordIncludeInTheTranspiledLang = Trim(A_LoopField50);
        }
        if (A_Index50 == 11) {
            keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField50);
        }
        if (A_Index50 == 12) {
            keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField50);
        }
        if (A_Index50 == 13) {
            keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField50);
        }
        if (A_Index50 == 14) {
            keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField50);
        }
        if (A_Index50 == 15) {
            keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField50);
        }
        if (A_Index50 == 16) {
            keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField50);
        }
        if (A_Index50 == 17) {
            keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField50);
        }
        if (A_Index50 == 18) {
            keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField50);
        }
        if (A_Index50 == 19) {
            keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField50);
        }
        if (A_Index50 == 20) {
            keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField50);
        }
        if (A_Index50 == 21) {
            keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField50);
        }
        if (A_Index50 == 22) {
            keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField50);
        }
        if (A_Index50 == 23) {
            keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField50);
        }
        if (A_Index50 == 24) {
            keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField50);
        }
        if (A_Index50 == 25) {
            keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField50);
        }
        if (A_Index50 == 26) {
            keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField50);
        }
        if (A_Index50 == 27) {
            keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField50);
        }
        if (A_Index50 == 28) {
            keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField50);
        }
        if (A_Index50 == 29) {
            keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField50);
        }
        if (A_Index50 == 30) {
            keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField50);
        }
        if (A_Index50 == 31) {
            keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField50);
        }
        if (A_Index50 == 32) {
            keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField50);
        }
        if (A_Index50 == 33) {
            keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField50);
        }
        if (A_Index50 == 34) {
            keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField50);
        }
        if (A_Index50 == 35) {
            keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField50);
        }
        if (A_Index50 == 36) {
            keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField50);
        }
        if (A_Index50 == 37) {
            keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField50);
        }
        if (A_Index50 == 38) {
            keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField50);
        }
        if (A_Index50 == 39) {
            keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField50);
        }
        if (A_Index50 == 40) {
            keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField50);
        }
        if (A_Index50 == 41) {
            keyWordCodeInTheTranspiledLangStartSCALA = Trim(A_LoopField50);
        }
        if (A_Index50 == 42) {
            keyWordCodeInTheTranspiledLangEndSCALA = Trim(A_LoopField50);
        }
        if (A_Index50 == 43) {
            keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField50);
        }
        if (A_Index50 == 44) {
            keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField50);
        }
        if (A_Index50 == 45) {
            keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField50);
        }
        if (A_Index50 == 46) {
            keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField50);
        }
        if (A_Index50 == 47) {
            keyWordCodeInHTVMstart = Trim(A_LoopField50);
        }
        if (A_Index50 == 48) {
            keyWordCodeInHTVMend = Trim(A_LoopField50);
        }
        if (A_Index50 == 49) {
            keyWordCodeInOtherHTVMsyntaxStart = Trim(A_LoopField50);
        }
        if (A_Index50 == 50) {
            keyWordCodeInOtherHTVMsyntaxEnd = Trim(A_LoopField50);
        }
        if (A_Index50 == 51) {
            keyWordCurlyBraceOpen = Trim(A_LoopField50);
        }
        if (A_Index50 == 52) {
            keyWordCurlyBraceClose = Trim(A_LoopField50);
        }
        if (A_Index50 == 53) {
            keyWordNull = Trim(A_LoopField50);
        }
        if (A_Index50 == 54) {
            keyWordTrue = Trim(A_LoopField50);
        }
        if (A_Index50 == 55) {
            keyWordFalse = Trim(A_LoopField50);
        }
        if (A_Index50 == 56) {
            keyWordVoid = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 57) {
            keyWordDouble = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 58) {
            keyWordChar = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 59) {
            keyWordUint8 = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 60) {
            keyWordUint16 = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 61) {
            keyWordUint32 = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 62) {
            keyWordUint64 = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 63) {
            keyWordINT = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 64) {
            keyWordSTR = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 65) {
            keyWordBOOL = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 66) {
            keyWordFLOAT = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 67) {
            keyWordINT8 = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 68) {
            keyWordINT16 = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 69) {
            keyWordINT32 = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 70) {
            keyWordINT64 = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 71) {
            keyWordIF = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 72) {
            keyWordElseIf = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 73) {
            keyWordElse = Trim(A_LoopField50);
        }
        if (A_Index50 == 74) {
            keyWordSwitch = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 75) {
            keyWordSwitchCase = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 76) {
            keyWordSwitchDefault = Trim(A_LoopField50);
        }
        if (A_Index50 == 77) {
            keyWordWhileLoop = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 78) {
            keyWordLoopInfinite = Trim(A_LoopField50);
        }
        if (A_Index50 == 79) {
            keyWordLoop = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 80) {
            keyWordLoopParse = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 81) {
            keyWordContinue = Trim(A_LoopField50);
        }
        if (A_Index50 == 82) {
            keyWordBreak = Trim(A_LoopField50);
        }
        if (A_Index50 == 83) {
            keyWordFunc = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 84) {
            keyWordAwait = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 85) {
            keyWordAsync = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 86) {
            keyWordThrow = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 87) {
            keyWordErrorMsg = Trim(A_LoopField50);
        }
        if (A_Index50 == 88) {
            keyWordTry = Trim(A_LoopField50);
        }
        if (A_Index50 == 89) {
            keyWordCatch = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 90) {
            keyWordFinally = Trim(A_LoopField50);
        }
        if (A_Index50 == 91) {
            keyWordReturnStatement = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 92) {
            keyWordArrayAppend = Trim(A_LoopField50);
        }
        if (A_Index50 == 93) {
            keyWordArrayPop = Trim(A_LoopField50);
        }
        if (A_Index50 == 94) {
            keyWordArraySize = Trim(A_LoopField50);
        }
        if (A_Index50 == 95) {
            keyWordArrayInsert = Trim(A_LoopField50);
        }
        if (A_Index50 == 96) {
            keyWordArrayRemove = Trim(A_LoopField50);
        }
        if (A_Index50 == 97) {
            keyWordArrayIndexOf = Trim(A_LoopField50);
        }
        if (A_Index50 == 98) {
            keyWordArrayDefinition = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 99) {
            keyWordArrayOfIntegersDefinition = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 100) {
            keyWordArrayOfStringsDefinition = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 101) {
            keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 102) {
            keyWordArrayOfBooleansDefinition = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 103) {
            keyWordVar = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 104) {
            keyWordLet = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 105) {
            keyWordConst = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 106) {
            keyWordEnd = Trim(A_LoopField50);
        }
        if (A_Index50 == 107) {
            keyWordGlobal = Trim(A_LoopField50) + " ";
        }
        if (A_Index50 == 108) {
            keyWordComment = Trim(A_LoopField50);
        }
        if (A_Index50 == 109) {
            keyWordCommentOpenMultiLine = Trim(A_LoopField50);
        }
        if (A_Index50 == 110) {
            keyWordCommentCloseMultiLine = Trim(A_LoopField50);
        }
        if (A_Index50 == 111) {
            keyWordEscpaeChar = Trim(A_LoopField50);
        }
        if (A_Index50 == 112) {
            keyWordMainLabel = Trim(A_LoopField50);
        }
        if (A_Index50 == 113) {
            keyWordConcat = Trim(A_LoopField50);
        }
        if (A_Index50 == 114) {
            keyWordAdd = Trim(A_LoopField50);
        }
        if (A_Index50 == 115) {
            keyWordSub = Trim(A_LoopField50);
        }
        if (A_Index50 == 116) {
            keyWordMul = Trim(A_LoopField50);
        }
        if (A_Index50 == 117) {
            keyWordDiv = Trim(A_LoopField50);
        }
        if (A_Index50 == 118) {
            keyWordMod = Trim(A_LoopField50);
        }
        if (A_Index50 == 119) {
            keyWordExp = Trim(A_LoopField50);
        }
        if (A_Index50 == 120) {
            keyWordEqual = Trim(A_LoopField50);
        }
        if (A_Index50 == 121) {
            keyWordStrictEqual = Trim(A_LoopField50);
        }
        if (A_Index50 == 122) {
            keyWordNotEqual = Trim(A_LoopField50);
        }
        if (A_Index50 == 123) {
            keyWordGreater = Trim(A_LoopField50);
        }
        if (A_Index50 == 124) {
            keyWordLess = Trim(A_LoopField50);
        }
        if (A_Index50 == 125) {
            keyWordGreaterEqual = Trim(A_LoopField50);
        }
        if (A_Index50 == 126) {
            keyWordLessEqual = Trim(A_LoopField50);
        }
        if (A_Index50 == 127) {
            keyWordAnd = Trim(A_LoopField50);
        }
        if (A_Index50 == 128) {
            keyWordOr = Trim(A_LoopField50);
        }
        if (A_Index50 == 129) {
            keyWordNot = Trim(A_LoopField50);
        }
        if (A_Index50 == 130) {
            keyWordBitAnd = Trim(A_LoopField50);
        }
        if (A_Index50 == 131) {
            keyWordBitOr = Trim(A_LoopField50);
        }
        if (A_Index50 == 132) {
            keyWordBitXor = Trim(A_LoopField50);
        }
        if (A_Index50 == 133) {
            keyWordBitNot = Trim(A_LoopField50);
        }
        if (A_Index50 == 134) {
            keyWordShiftLeft = Trim(A_LoopField50);
        }
        if (A_Index50 == 135) {
            keyWordShiftRight = Trim(A_LoopField50);
        }
        if (A_Index50 == 136) {
            keyWordShiftUnsignedRight = Trim(A_LoopField50);
        }
        if (A_Index50 == 137) {
            keyWordAssign = Trim(A_LoopField50);
        }
        if (A_Index50 == 138) {
            keyWordAssignAdd = Trim(A_LoopField50);
        }
        if (A_Index50 == 139) {
            keyWordAssignConcat = Trim(A_LoopField50);
        }
        if (A_Index50 == 140) {
            keyWordAssignSub = Trim(A_LoopField50);
        }
        if (A_Index50 == 141) {
            keyWordAssignMul = Trim(A_LoopField50);
        }
        if (A_Index50 == 142) {
            keyWordAssignDiv = Trim(A_LoopField50);
        }
        if (A_Index50 == 143) {
            keyWordAssignMod = Trim(A_LoopField50);
        }
        if (A_Index50 == 144) {
            keyWordAssignShiftLeft = Trim(A_LoopField50);
        }
        if (A_Index50 == 145) {
            keyWordAssignShiftRight = Trim(A_LoopField50);
        }
        if (A_Index50 == 146) {
            keyWordLogicalAssignShiftRight = Trim(A_LoopField50);
        }
        if (A_Index50 == 147) {
            keyWordAssignBitAnd = Trim(A_LoopField50);
        }
        if (A_Index50 == 148) {
            keyWordAssignBitOr = Trim(A_LoopField50);
        }
        if (A_Index50 == 149) {
            keyWordAssignBitXor = Trim(A_LoopField50);
        }
        if (A_Index50 == 150) {
            keyWordTernary1 = Trim(A_LoopField50);
        }
        if (A_Index50 == 151) {
            keyWordTernary2 = Trim(A_LoopField50);
        }
        if (A_Index50 == 152) {
            keyWordInc = Trim(A_LoopField50);
        }
        if (A_Index50 == 153) {
            keyWordDec = Trim(A_LoopField50);
        }
        if (A_Index50 == 154) {
            AHKlikeLoopsIndexedAt = Trim(A_LoopField50);
        }
        if (A_Index50 == 155) {
            keyWordAIndex = Trim(A_LoopField50);
        }
        if (A_Index50 == 156) {
            keyWordALoopField = Trim(A_LoopField50);
        }
        if (A_Index50 == 157) {
            useCurlyBraces = Trim(A_LoopField50);
        }
        if (A_Index50 == 158) {
            useEnd = Trim(A_LoopField50);
        }
        if (A_Index50 == 159) {
            useSemicolon = Trim(A_LoopField50);
        }
        if (A_Index50 == 160) {
            useParentheses = Trim(A_LoopField50);
        }
        if (A_Index50 == 161) {
            usePrefixTypeForTypeDefinition = Trim(A_LoopField50);
        }
        if (A_Index50 == 162) {
            usePostfixTypeForTypeDefinition = Trim(A_LoopField50);
        }
        if (A_Index50 == 163) {
            usePythonicColonSyntax = Trim(A_LoopField50);
        }
        if (A_Index50 == 164) {
            useCurlyBracesSyntaxForArrayDef = Trim(A_LoopField50);
        }
        if (A_Index50 == 165) {
            useInJavaScriptAlwaysUseVar = Trim(A_LoopField50);
        }
        if (A_Index50 == 166) {
            useJavaScriptInAfullHTMLfile = Trim(A_LoopField50);
        }
        if (A_Index50 == 167) {
            useJavaScriptAmainFuncDef = Trim(A_LoopField50);
        }
        if (A_Index50 == 168) {
            useJavaScriptAllFuncsAreAsync = Trim(A_LoopField50);
        }
        if (A_Index50 == 169) {
            useJavaScriptAlwaysTripleEqual = Trim(A_LoopField50);
        }
    }
    if (argHTVMinstrMORE.size() > 0) {
        std::string allInstructionFile_2 = Trim(FileRead(Trim(argHTVMinstrMORE[0])));
        std::vector<std::string> items51 = LoopParseFunc(allInstructionFile_2, "\n", "\r");
        for (size_t A_Index51 = 0; A_Index51 < items51.size() + 0; A_Index51++) {
            std::string A_LoopField51 = items51[A_Index51 - 0];
            if (A_Index51 == 0) {
                langToConvertTo_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 1) {
                langFileExtension_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 2) {
                commands_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 3) {
                keyWordAlliance_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 4) {
                keyWordCrew_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 5) {
                keyWordMethod_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 6) {
                keyWordDefObj_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 7) {
                keyWordPorp_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 8) {
                keyWordThis_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 9) {
                keyWordInclude_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 10) {
                keyWordIncludeInTheTranspiledLang_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 11) {
                keyWordCodeInTheTranspiledLangStart_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 12) {
                keyWordCodeInTheTranspiledLangEnd_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 13) {
                keyWordCodeInTheTranspiledLangStartCPP_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 14) {
                keyWordCodeInTheTranspiledLangEndCPP_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 15) {
                keyWordCodeInTheTranspiledLangStartPY_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 16) {
                keyWordCodeInTheTranspiledLangEndPY_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 17) {
                keyWordCodeInTheTranspiledLangStartJS_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 18) {
                keyWordCodeInTheTranspiledLangEndJS_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 19) {
                keyWordCodeInTheTranspiledLangStartGO_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 20) {
                keyWordCodeInTheTranspiledLangEndGO_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 21) {
                keyWordCodeInTheTranspiledLangStartLUA_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 22) {
                keyWordCodeInTheTranspiledLangEndLUA_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 23) {
                keyWordCodeInTheTranspiledLangStartCS_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 24) {
                keyWordCodeInTheTranspiledLangEndCS_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 25) {
                keyWordCodeInTheTranspiledLangStartJAVA_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 26) {
                keyWordCodeInTheTranspiledLangEndJAVA_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 27) {
                keyWordCodeInTheTranspiledLangStartKT_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 28) {
                keyWordCodeInTheTranspiledLangEndKT_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 29) {
                keyWordCodeInTheTranspiledLangStartRB_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 30) {
                keyWordCodeInTheTranspiledLangEndRB_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 31) {
                keyWordCodeInTheTranspiledLangStartNIM_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 32) {
                keyWordCodeInTheTranspiledLangEndNIM_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 33) {
                keyWordCodeInTheTranspiledLangStartAHK_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 34) {
                keyWordCodeInTheTranspiledLangEndAHK_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 35) {
                keyWordCodeInTheTranspiledLangStartSWIFT_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 36) {
                keyWordCodeInTheTranspiledLangEndSWIFT_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 37) {
                keyWordCodeInTheTranspiledLangStartDART_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 38) {
                keyWordCodeInTheTranspiledLangEndDART_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 39) {
                keyWordCodeInTheTranspiledLangStartTS_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 40) {
                keyWordCodeInTheTranspiledLangEndTS_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 41) {
                keyWordCodeInTheTranspiledLangStartSCALA_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 42) {
                keyWordCodeInTheTranspiledLangEndSCALA_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 43) {
                keyWordCodeInTheTranspiledLangStartGROOVY_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 44) {
                keyWordCodeInTheTranspiledLangEndGROOVY_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 45) {
                keyWordCodeInTheTranspiledLangStartHTVM_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 46) {
                keyWordCodeInTheTranspiledLangEndHTVM_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 47) {
                keyWordCodeInHTVMstart_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 48) {
                keyWordCodeInHTVMend_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 49) {
                keyWordCodeInOtherHTVMsyntaxStart_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 50) {
                keyWordCodeInOtherHTVMsyntaxEnd_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 51) {
                keyWordCurlyBraceOpen_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 52) {
                keyWordCurlyBraceClose_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 53) {
                keyWordNull_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 54) {
                keyWordTrue_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 55) {
                keyWordFalse_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 56) {
                keyWordVoid_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 57) {
                keyWordDouble_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 58) {
                keyWordChar_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 59) {
                keyWordUint8_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 60) {
                keyWordUint16_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 61) {
                keyWordUint32_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 62) {
                keyWordUint64_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 63) {
                keyWordINT_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 64) {
                keyWordSTR_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 65) {
                keyWordBOOL_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 66) {
                keyWordFLOAT_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 67) {
                keyWordINT8_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 68) {
                keyWordINT16_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 69) {
                keyWordINT32_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 70) {
                keyWordINT64_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 71) {
                keyWordIF_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 72) {
                keyWordElseIf_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 73) {
                keyWordElse_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 74) {
                keyWordSwitch_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 75) {
                keyWordSwitchCase_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 76) {
                keyWordSwitchDefault_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 77) {
                keyWordWhileLoop_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 78) {
                keyWordLoopInfinite_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 79) {
                keyWordLoop_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 80) {
                keyWordLoopParse_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 81) {
                keyWordContinue_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 82) {
                keyWordBreak_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 83) {
                keyWordFunc_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 84) {
                keyWordAwait_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 85) {
                keyWordAsync_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 86) {
                keyWordThrow_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 87) {
                keyWordErrorMsg_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 88) {
                keyWordTry_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 89) {
                keyWordCatch_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 90) {
                keyWordFinally_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 91) {
                keyWordReturnStatement_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 92) {
                keyWordArrayAppend_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 93) {
                keyWordArrayPop_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 94) {
                keyWordArraySize_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 95) {
                keyWordArrayInsert_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 96) {
                keyWordArrayRemove_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 97) {
                keyWordArrayIndexOf_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 98) {
                keyWordArrayDefinition_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 99) {
                keyWordArrayOfIntegersDefinition_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 100) {
                keyWordArrayOfStringsDefinition_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 101) {
                keyWordArrayOfFloatingPointNumbersDefinition_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 102) {
                keyWordArrayOfBooleansDefinition_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 103) {
                keyWordVar_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 104) {
                keyWordLet_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 105) {
                keyWordConst_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 106) {
                keyWordEnd_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 107) {
                keyWordGlobal_2 = Trim(A_LoopField51) + " ";
            }
            if (A_Index51 == 108) {
                keyWordComment_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 109) {
                keyWordCommentOpenMultiLine_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 110) {
                keyWordCommentCloseMultiLine_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 111) {
                keyWordEscpaeChar_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 112) {
                keyWordMainLabel_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 113) {
                keyWordConcat_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 114) {
                keyWordAdd_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 115) {
                keyWordSub_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 116) {
                keyWordMul_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 117) {
                keyWordDiv_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 118) {
                keyWordMod_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 119) {
                keyWordExp_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 120) {
                keyWordEqual_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 121) {
                keyWordStrictEqual_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 122) {
                keyWordNotEqual_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 123) {
                keyWordGreater_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 124) {
                keyWordLess_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 125) {
                keyWordGreaterEqual_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 126) {
                keyWordLessEqual_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 127) {
                keyWordAnd_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 128) {
                keyWordOr_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 129) {
                keyWordNot_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 130) {
                keyWordBitAnd_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 131) {
                keyWordBitOr_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 132) {
                keyWordBitXor_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 133) {
                keyWordBitNot_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 134) {
                keyWordShiftLeft_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 135) {
                keyWordShiftRight_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 136) {
                keyWordShiftUnsignedRight_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 137) {
                keyWordAssign_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 138) {
                keyWordAssignAdd_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 139) {
                keyWordAssignConcat_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 140) {
                keyWordAssignSub_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 141) {
                keyWordAssignMul_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 142) {
                keyWordAssignDiv_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 143) {
                keyWordAssignMod_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 144) {
                keyWordAssignShiftLeft_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 145) {
                keyWordAssignShiftRight_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 146) {
                keyWordLogicalAssignShiftRight_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 147) {
                keyWordAssignBitAnd_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 148) {
                keyWordAssignBitOr_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 149) {
                keyWordAssignBitXor_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 150) {
                keyWordTernary1_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 151) {
                keyWordTernary2_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 152) {
                keyWordInc_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 153) {
                keyWordDec_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 154) {
                AHKlikeLoopsIndexedAt_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 155) {
                keyWordAIndex_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 156) {
                keyWordALoopField_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 157) {
                useCurlyBraces_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 158) {
                useEnd_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 159) {
                useSemicolon_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 160) {
                useParentheses_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 161) {
                usePrefixTypeForTypeDefinition_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 162) {
                usePostfixTypeForTypeDefinition_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 163) {
                usePythonicColonSyntax_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 164) {
                useCurlyBracesSyntaxForArrayDef_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 165) {
                useInJavaScriptAlwaysUseVar_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 166) {
                useJavaScriptInAfullHTMLfile_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 167) {
                useJavaScriptAmainFuncDef_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 168) {
                useJavaScriptAllFuncsAreAsync_2 = Trim(A_LoopField51);
            }
            if (A_Index51 == 169) {
                useJavaScriptAlwaysTripleEqual_2 = Trim(A_LoopField51);
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
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    /*
    if (langToConvertTo == "htvm") {
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
    if (langToConvertTo == "scala") {
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
    print(htCode);
    code = htCode;
    print(mode);
    print(langToConvertTo);
    print("==================================");
    print("==================================");
    print("==================================");
    print("==================================");
    print("==================================");
    //print(allInstructionFile)
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
    int COUNT_programmingBlock_SCALA = 0;
    int COUNT_programmingBlock_GROOVY = 0;
    int COUNT_programmingBlock_HTVM = 0;
    int COUNT_programmingBlock_HTVMsyntax = 0;
    std::string programmingBlocksTemp = "";
    int inProgarmmingBlock = 0;
    std::string holdTempDataProgrammingBlockThenPutInArr = "";
    std::vector<std::string> items52 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index52 = 0; A_Index52 < items52.size() + 0; A_Index52++) {
        std::string A_LoopField52 = items52[A_Index52 - 0];
        if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEnd)) {
            COUNT_programmingBlock_InTheTranspiledLang++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(COUNT_programmingBlock_InTheTranspiledLang) + "AA\n";
            programmingBlock_InTheTranspiledLang.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndCPP)) {
            COUNT_programmingBlock_CPP++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(COUNT_programmingBlock_CPP) + "AA\n";
            programmingBlock_CPP.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndPY)) {
            COUNT_programmingBlock_PY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_PY-programmingBlock_PY-AA" + STR(COUNT_programmingBlock_PY) + "AA\n";
            programmingBlock_PY.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndJS)) {
            COUNT_programmingBlock_JS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JS-programmingBlock_JS-AA" + STR(COUNT_programmingBlock_JS) + "AA\n";
            programmingBlock_JS.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndGO)) {
            COUNT_programmingBlock_GO++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GO-programmingBlock_GO-AA" + STR(COUNT_programmingBlock_GO) + "AA\n";
            programmingBlock_GO.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndLUA)) {
            COUNT_programmingBlock_LUA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(COUNT_programmingBlock_LUA) + "AA\n";
            programmingBlock_LUA.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndCS)) {
            COUNT_programmingBlock_CS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CS-programmingBlock_CS-AA" + STR(COUNT_programmingBlock_CS) + "AA\n";
            programmingBlock_CS.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndJAVA)) {
            COUNT_programmingBlock_JAVA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(COUNT_programmingBlock_JAVA) + "AA\n";
            programmingBlock_JAVA.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndKT)) {
            COUNT_programmingBlock_KT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_KT-programmingBlock_KT-AA" + STR(COUNT_programmingBlock_KT) + "AA\n";
            programmingBlock_KT.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndRB)) {
            COUNT_programmingBlock_RB++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_RB-programmingBlock_RB-AA" + STR(COUNT_programmingBlock_RB) + "AA\n";
            programmingBlock_RB.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndNIM)) {
            COUNT_programmingBlock_NIM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(COUNT_programmingBlock_NIM) + "AA\n";
            programmingBlock_NIM.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndAHK)) {
            COUNT_programmingBlock_AHK++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(COUNT_programmingBlock_AHK) + "AA\n";
            programmingBlock_AHK.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndSWIFT)) {
            COUNT_programmingBlock_SWIFT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(COUNT_programmingBlock_SWIFT) + "AA\n";
            programmingBlock_SWIFT.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndDART)) {
            COUNT_programmingBlock_DART++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_DART-programmingBlock_DART-AA" + STR(COUNT_programmingBlock_DART) + "AA\n";
            programmingBlock_DART.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndTS)) {
            COUNT_programmingBlock_TS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_TS-programmingBlock_TS-AA" + STR(COUNT_programmingBlock_TS) + "AA\n";
            programmingBlock_TS.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndSCALA)) {
            COUNT_programmingBlock_SCALA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_SCALA-programmingBlock_SCALA-AA" + STR(COUNT_programmingBlock_SCALA) + "AA\n";
            programmingBlock_SCALA.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndGROOVY)) {
            COUNT_programmingBlock_GROOVY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(COUNT_programmingBlock_GROOVY) + "AA\n";
            programmingBlock_GROOVY.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangEndHTVM)) {
            COUNT_programmingBlock_HTVM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(COUNT_programmingBlock_HTVM) + "AA\n";
            programmingBlock_HTVM.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInOtherHTVMsyntaxEnd)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            COUNT_programmingBlock_HTVMsyntax++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(COUNT_programmingBlock_HTVMsyntax) + "AA\n";
            programmingBlock_HTVMsyntax.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        }
        else if (inProgarmmingBlock == 1) {
            holdTempDataProgrammingBlockThenPutInArr += A_LoopField52 + "\n";
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStart)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartCPP)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartPY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartJS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartGO)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartLUA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartCS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartJAVA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartKT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartRB)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartNIM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartAHK)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartSWIFT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartDART)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartTS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartSCALA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartGROOVY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInTheTranspiledLangStartHTVM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField52)) == StrLower(keyWordCodeInOtherHTVMsyntaxStart)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        } else {
            programmingBlocksTemp += A_LoopField52 + "\n";
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
    //programmingBlock_SCALA
    //programmingBlock_GROOVY
    //programmingBlock_HTVM
    //programmingBlock_HTVMsyntax
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    print("============programmingBlock_CPP==================");
    print("============programmingBlock_CPP==================");
    if (programmingBlock_CPP.size() > 0) {
        for (int A_Index53 = 0; A_Index53 < programmingBlock_CPP.size() + 0; A_Index53++) {
            print(programmingBlock_CPP[A_Index53]);
        }
    }
    print("============programmingBlock_CPP==================");
    print("============programmingBlock_CPP==================");
    std::string htCodeOUT754754 = "";
    int areWEinSome34sNum = 0;
    int theIdNumOfThe34 = 0;
    std::vector<std::string> theIdNumOfThe34theVar;
    std::string ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = "";
    std::vector<std::string> getAllCharForTheFurtureSoIcanAddEscapeChar;
    int removeNexFixkeyWordEscpaeChar = 0;
    std::vector<std::string> items54 = LoopParseFunc(code);
    for (size_t A_Index54 = 0; A_Index54 < items54.size() + 0; A_Index54++) {
        std::string A_LoopField54 = items54[A_Index54 - 0];
        theIdNumOfThe34theVar.push_back("");
        theIdNumOfThe34theVar.push_back("");
    }
    std::vector<std::string> items55 = LoopParseFunc(code);
    for (size_t A_Index55 = 0; A_Index55 < items55.size() + 0; A_Index55++) {
        std::string A_LoopField55 = items55[A_Index55 - 0];
        theIdNumOfThe34theVar[A_Index55] = theIdNumOfThe34theVar[A_Index55] + Chr(34);
        getAllCharForTheFurtureSoIcanAddEscapeChar.push_back(A_LoopField55);
    }
    getAllCharForTheFurtureSoIcanAddEscapeChar.push_back(" ");
    ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuusgfgesrheidFor-aasdsas-theuhtuwaesphoutr" + Chr(34);
    std::string OutFixDoubleQuotesInsideDoubleQuotes = "";
    int fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
    std::vector<std::string> items56 = LoopParseFunc(code);
    for (size_t A_Index56 = 0; A_Index56 < items56.size() + 0; A_Index56++) {
        std::string A_LoopField56 = items56[A_Index56 - 0];
        if (A_LoopField56 == keyWordEscpaeChar && getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index56 + 1] == Chr(34)) {
            fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1;
            OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes;
        } else {
            if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1) {
                OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField56;
            } else {
                fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
            }
        }
    }
    code = OutFixDoubleQuotesInsideDoubleQuotes;
    if (keyWordEscpaeChar != Chr(92)) {
        code = StrReplace(code, Chr(92), Chr(92) + Chr(92));
    }
    if (keyWordEscpaeChar == Chr(92)) {
        std::vector<std::string> items57 = LoopParseFunc(code);
        for (size_t A_Index57 = 0; A_Index57 < items57.size() + 0; A_Index57++) {
            std::string A_LoopField57 = items57[A_Index57 - 0];
            if (A_LoopField57 == Chr(34)) {
                areWEinSome34sNum++;
            }
            if (areWEinSome34sNum == 1) {
                if (A_LoopField57 != Chr(34)) {
                    if (A_LoopField57 == keyWordEscpaeChar) {
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                    } else {
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField57;
                    }
                } else {
                    theIdNumOfThe34++;
                    htCodeOUT754754 += "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                }
            }
            if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                if (A_LoopField57 != Chr(34)) {
                    htCodeOUT754754 += A_LoopField57;
                }
                areWEinSome34sNum = 0;
            }
        }
    } else {
        std::vector<std::string> items58 = LoopParseFunc(code);
        for (size_t A_Index58 = 0; A_Index58 < items58.size() + 0; A_Index58++) {
            std::string A_LoopField58 = items58[A_Index58 - 0];
            if (A_LoopField58 == Chr(34)) {
                areWEinSome34sNum++;
            }
            if (areWEinSome34sNum == 1) {
                if (A_LoopField58 != Chr(34)) {
                    if (A_LoopField58 == keyWordEscpaeChar && keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index58 + 1]) {
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar;
                        removeNexFixkeyWordEscpaeChar = 1;
                    }
                    else if (A_LoopField58 == keyWordEscpaeChar) {
                        if (removeNexFixkeyWordEscpaeChar != 1) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                        } else {
                            removeNexFixkeyWordEscpaeChar = 0;
                        }
                    } else {
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField58;
                    }
                } else {
                    theIdNumOfThe34++;
                    htCodeOUT754754 += "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                }
            }
            if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                if (A_LoopField58 != Chr(34)) {
                    htCodeOUT754754 += A_LoopField58;
                }
                areWEinSome34sNum = 0;
            }
        }
    }
    code = htCodeOUT754754;
    for (int A_Index59 = 0; A_Index59 < theIdNumOfThe34 + 0; A_Index59++) {
        theIdNumOfThe34theVar[A_Index59] = theIdNumOfThe34theVar[A_Index59] + Chr(34);
    }
    theIdNumOfThe34theVar.push_back(Chr(34));
    code = StrReplace(code, Chr(13), "");
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
        if (langToConvertTo != "py" && langToConvertTo != "nim" && langToConvertTo != "lua" && langToConvertTo != "rb" && langToConvertTo != "go" && langToConvertTo != "swift" && useSemicolon == "off") {
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
    std::string beforeKeywordForRemoveCommentsOnTheEndOfTheLine = "";
    std::string newStringOutCode = "";
    int posForRemoveCommentsOnTheEndOfTheLine = 0;
    std::string originalStringForRemoveCommentsOnTheEndOfTheLine = "";
    std::vector<std::string> items60 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index60 = 0; A_Index60 < items60.size() + 0; A_Index60++) {
        std::string A_LoopField60 = items60[A_Index60 - 0];
        // Define the original string
        originalStringForRemoveCommentsOnTheEndOfTheLine = A_LoopField60;
        // Find the position of the keyword in the original string
        posForRemoveCommentsOnTheEndOfTheLine = InStr(originalStringForRemoveCommentsOnTheEndOfTheLine, " " + keyWordComment);
        if (SubStr(Trim(A_LoopField60), 1, StrLen(keyWordComment)) != keyWordComment) {
            if (posForRemoveCommentsOnTheEndOfTheLine > 0) {
                beforeKeywordForRemoveCommentsOnTheEndOfTheLine = A_LoopField60;
                // Construct the new string with everything before the keyword
                newStringOutCode += beforeKeywordForRemoveCommentsOnTheEndOfTheLine + "\n";
            } else {
                newStringOutCode += A_LoopField60 + "\n";
            }
        } else {
            newStringOutCode += A_LoopField60 + "\n";
        }
    }
    code = StringTrimRight(newStringOutCode, 1);
    //MsgBox, % code
    std::string htCodeOutFixEnd = "";
    int htCodeOutFixINT = 0;
    int htCodeOutFixINT2 = 0;
    if (useCurlyBraces == "on") {
        if (keyWordCurlyBraceOpen != "{") {
            std::vector<std::string> items61 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index61 = 0; A_Index61 < items61.size() + 0; A_Index61++) {
                std::string A_LoopField61 = items61[A_Index61 - 0];
                htCodeOutFixINT2 = 0;
                if (isLineAconstruct(Trim(A_LoopField61)) == true || Trim(A_LoopField61) == keyWordCurlyBraceOpen) {
                    htCodeOutFixINT2 = 1;
                }
                htCodeOutFixINT = 0;
                std::vector<std::string> items62 = LoopParseFunc(A_LoopField61, " ");
                for (size_t A_Index62 = 0; A_Index62 < items62.size() + 0; A_Index62++) {
                    std::string A_LoopField62 = items62[A_Index62 - 0];
                    htCodeOutFixINT++;
                }
                htCodeOutFixINT--;
                std::vector<std::string> items63 = LoopParseFunc(A_LoopField61, " ");
                for (size_t A_Index63 = 0; A_Index63 < items63.size() + 0; A_Index63++) {
                    std::string A_LoopField63 = items63[A_Index63 - 0];
                    if (htCodeOutFixINT == A_Index63 && htCodeOutFixINT2 == 1) {
                        htCodeOutFixINT2 = 0;
                        htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField63, keyWordCurlyBraceOpen, "{") + " ";
                    } else {
                        htCodeOutFixEnd += A_LoopField63 + " ";
                    }
                }
                htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1);
                htCodeOutFixEnd += "\n";
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        htCodeOutFixEnd = "";
        if (keyWordCurlyBraceClose != "}") {
            std::vector<std::string> items64 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index64 = 0; A_Index64 < items64.size() + 0; A_Index64++) {
                std::string A_LoopField64 = items64[A_Index64 - 0];
                htCodeOutFixINT2 = 0;
                if (isLineAconstruct(Trim(A_LoopField64)) == true || Trim(A_LoopField64) == keyWordCurlyBraceClose) {
                    htCodeOutFixINT2 = 1;
                }
                std::vector<std::string> items65 = LoopParseFunc(A_LoopField64, " ");
                for (size_t A_Index65 = 0; A_Index65 < items65.size() + 0; A_Index65++) {
                    std::string A_LoopField65 = items65[A_Index65 - 0];
                    if (htCodeOutFixINT2 == 1 || Trim(A_LoopField65) == keyWordCurlyBraceClose) {
                        htCodeOutFixINT2 = 0;
                        htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField65, keyWordCurlyBraceClose, "}") + " ";
                    } else {
                        htCodeOutFixEnd += A_LoopField65 + " ";
                    }
                }
                htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1);
                htCodeOutFixEnd += "\n";
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
        std::vector<std::string> items66 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index66 = 0; A_Index66 < items66.size() + 0; A_Index66++) {
            std::string A_LoopField66 = items66[A_Index66 - 0];
            if (StrLower(Trim(A_LoopField66)) == StrLower(keyWordEnd)) {
                htCodeOutFixEnd += "}\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField66)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF) && isLineAconstruct(Trim(A_LoopField66)) == true) {
                htCodeOutFixEnd += A_LoopField66 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField66)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf) && isLineAconstruct(Trim(A_LoopField66)) == true) {
                htCodeOutFixEnd += "\n}\n" + A_LoopField66 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField66)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse) && isLineAconstruct(Trim(A_LoopField66)) == true) {
                htCodeOutFixEnd += "\n}\n" + A_LoopField66 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField66)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch) && isLineAconstruct(Trim(A_LoopField66)) == true) {
                htCodeOutFixEnd += "\n}\n" + A_LoopField66 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField66)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally) && isLineAconstruct(Trim(A_LoopField66)) == true) {
                htCodeOutFixEnd += "\n}\n" + A_LoopField66 + "\n{\n";
            }
            else if (isLineAconstruct(Trim(A_LoopField66)) == true) {
                htCodeOutFixEnd += A_LoopField66 + "\n{\n";
            } else {
                htCodeOutFixEnd += A_LoopField66 + "\n";
            }
        }
        code = StringTrimRight(htCodeOutFixEnd, 1);
    }
    if (usePythonicColonSyntax == "off") {
        if (useEnd == "off" && useCurlyBraces == "off") {
            htCodeOutFixEnd = "";
            std::vector<std::string> items67 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index67 = 0; A_Index67 < items67.size() + 0; A_Index67++) {
                std::string A_LoopField67 = items67[A_Index67 - 0];
                if (isLineAconstruct(Trim(A_LoopField67)) == true) {
                    htCodeOutFixEnd += A_LoopField67 + ":\n";
                } else {
                    htCodeOutFixEnd += A_LoopField67 + "\n";
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
    }
    if (useCurlyBraces == "off" && useEnd == "off") {
        code = AddCurlyBraces(code);
    }
    outTrimCode = "";
    std::vector<std::string> items68 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index68 = 0; A_Index68 < items68.size() + 0; A_Index68++) {
        std::string A_LoopField68 = items68[A_Index68 - 0];
        outTrimCode += Trim(A_LoopField68) + "\n";
    }
    code = StringTrimRight(outTrimCode, 1);
    // for converting c++ to js and py
    //code := StrReplace(code, "{}", "[]")
    std::string outCodeFixBraces = "";
    for (int A_Index69 = 0; A_Index69 < 2 + 0; A_Index69++) {
        outCodeFixBraces = "";
        std::vector<std::string> items70 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index70 = 0; A_Index70 < items70.size() + 0; A_Index70++) {
            std::string A_LoopField70 = items70[A_Index70 - 0];
            if (InStr(Trim(A_LoopField70), "{") && Trim(A_LoopField70) != "{") {
                outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField70), "{", "")) + "\n{\n";
            }
            else if (InStr(Trim(A_LoopField70), "}") && Trim(A_LoopField70) != "}") {
                outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField70), "}", "")) + "\n";
            } else {
                outCodeFixBraces += Trim(A_LoopField70) + "\n";
            }
        }
        code = StringTrimRight(outCodeFixBraces, 1);
    }
    htCodeOutFixEnd = "";
    if (usePythonicColonSyntax == "on") {
        std::vector<std::string> items71 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index71 = 0; A_Index71 < items71.size() + 0; A_Index71++) {
            std::string A_LoopField71 = items71[A_Index71 - 0];
            if (isLineAconstruct(Trim(A_LoopField71)) == true) {
                htCodeOutFixEnd += StringTrimRight(A_LoopField71, 1) + "\n";
            } else {
                htCodeOutFixEnd += A_LoopField71 + "\n";
            }
        }
        code = StringTrimRight(htCodeOutFixEnd, 1);
    }
    //;; main loop ;;;
    //;; main loop ;;;
    //;; main loop ;;;
    //;; main loop ;;;
    int didWeUseMainLabel = 0;
    std::string codeOutFixAndAddMainFunc = "";
    std::vector<std::string> items72 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index72 = 0; A_Index72 < items72.size() + 0; A_Index72++) {
        std::string A_LoopField72 = items72[A_Index72 - 0];
        if (StrLower(A_LoopField72) == StrLower(keyWordMainLabel)) {
            didWeUseMainLabel = 1;
            if (langToConvertTo == "cpp") {
                codeOutFixAndAddMainFunc += "int main(int argc, char* argv[])\n{\n";
            }
            if (langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
                codeOutFixAndAddMainFunc += "async function main()\n{\n";
            }
            if (langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
                codeOutFixAndAddMainFunc += "async function main(): Promise<void>\n{\n";
            }
            if (langToConvertTo == "go") {
                codeOutFixAndAddMainFunc += "func main()\n{\n";
            }
            if (langToConvertTo == "cs") {
                codeOutFixAndAddMainFunc += "static void Main(string[] args)\n{\n";
            }
            if (langToConvertTo == "java") {
                codeOutFixAndAddMainFunc += "public static void main(String[] args)\n{\n";
            }
            if (langToConvertTo == "kt") {
                codeOutFixAndAddMainFunc += "fun main(args: Array<String>)\n{\n";
            }
            if (langToConvertTo == "swift") {
                codeOutFixAndAddMainFunc += "func main()\n{\n";
            }
            if (langToConvertTo == "dart") {
                codeOutFixAndAddMainFunc += "void main(List<String> arguments)\n{\n";
            }
            if (langToConvertTo == "scala") {
                codeOutFixAndAddMainFunc += "ndef main(args: Array[String]): Unit = \n{\n";
            }
        } else {
            codeOutFixAndAddMainFunc += A_LoopField72 + "\n";
        }
    }
    if (didWeUseMainLabel != 1 && langToConvertTo == "cpp") {
        codeOutFixAndAddMainFunc = "int main(int argc, char* argv[])\n{\n" + codeOutFixAndAddMainFunc;
    }
    if (didWeUseMainLabel != 1 && langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
        codeOutFixAndAddMainFunc = "async function main()\n{\n" + codeOutFixAndAddMainFunc;
    }
    if (didWeUseMainLabel != 1 && langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
        codeOutFixAndAddMainFunc = "async function main(): Promise<void>\n{\n" + codeOutFixAndAddMainFunc;
    }
    if (didWeUseMainLabel != 1 && langToConvertTo == "go") {
        codeOutFixAndAddMainFunc = "func main()\n{\n" + codeOutFixAndAddMainFunc;
    }
    if (didWeUseMainLabel != 1 && langToConvertTo == "cs") {
        codeOutFixAndAddMainFunc = "static void Main(string[] args)\n{\n" + codeOutFixAndAddMainFunc;
    }
    if (didWeUseMainLabel != 1 && langToConvertTo == "java") {
        codeOutFixAndAddMainFunc = "public static void main(String[] args)\n{\n" + codeOutFixAndAddMainFunc;
    }
    if (didWeUseMainLabel != 1 && langToConvertTo == "kt") {
        codeOutFixAndAddMainFunc = "fun main(args: Array<String>)\n{\n" + codeOutFixAndAddMainFunc;
    }
    if (didWeUseMainLabel != 1 && langToConvertTo == "swift") {
        codeOutFixAndAddMainFunc = "func main()\n{\n" + codeOutFixAndAddMainFunc;
    }
    if (didWeUseMainLabel != 1 && langToConvertTo == "dart") {
        codeOutFixAndAddMainFunc = "void main(List<String> arguments)\n{\n" + codeOutFixAndAddMainFunc;
    }
    if (didWeUseMainLabel != 1 && langToConvertTo == "scala") {
        codeOutFixAndAddMainFunc = "def main(args: Array[String]): Unit = \n{\n" + codeOutFixAndAddMainFunc;
    }
    code = StringTrimRight(codeOutFixAndAddMainFunc, 1);
    // main loop
    // main loop
    std::vector<std::string> lookIntoTheNextLineForFuncWhitNoKeyWord;
    std::vector<std::string> items73 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index73 = 0; A_Index73 < items73.size() + 0; A_Index73++) {
        std::string A_LoopField73 = items73[A_Index73 - 0];
        lookIntoTheNextLineForFuncWhitNoKeyWord.push_back(A_LoopField73);
    }
    lookIntoTheNextLineForFuncWhitNoKeyWord.push_back(" ");
    htCode = "";
    print("=======UP==========");
    print(code);
    print("=======DOWN==========");
    std::vector<std::string> items74 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index74 = 0; A_Index74 < items74.size() + 0; A_Index74++) {
        std::string A_LoopField74 = items74[A_Index74 - 0];
        lineDone = 0;
        if (StrLower(A_LoopField74) == StrLower(keyWordLoopInfinite) || StrLower(A_LoopField74) == StrLower(keyWordLoopInfinite + ":")) {
            // infinity loops
            haveWeEverUsedAloop = 1;
            lineDone = 1;
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
                var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++";
            }
            if (langToConvertTo == "lua") {
                var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + ", someLimit do";
            }
            if (langToConvertTo == "cs") {
                var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
            }
            if (langToConvertTo == "java") {
                var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
            }
            if (langToConvertTo == "kt") {
                var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit)";
            }
            if (langToConvertTo == "rb") {
                var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit do";
            }
            if (langToConvertTo == "nim") {
                var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit:";
            }
            if (langToConvertTo == "ahk") {
                var1 = "Loop";
            }
            if (langToConvertTo == "swift") {
                var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " ..< someLimit";
            }
            if (langToConvertTo == "dart") {
                var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
            }
            if (langToConvertTo == "ts") {
                var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
            }
            if (langToConvertTo == "scala") {
                var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " <- " + AHKlikeLoopsIndexedAt + " to someLimit)";
            }
            if (langToConvertTo == "groovy") {
                var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit)";
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
                htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
            }
            AindexcharLength++;
            htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
        }
        else if (SubStr(Trim(StrLower(A_LoopField74)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop) && SubStr(Trim(StrLower(A_LoopField74)), 1, StrLen(StrLower(keyWordLoop)) + 2) != StrLower(keyWordLoop) + "% " && SubStr(Trim(StrLower(A_LoopField74)), 1, StrLen(StrLower(keyWordLoopParse))) != StrLower(keyWordLoopParse)) {
            out2 = StringTrimLeft(A_LoopField74, StrLen(keyWordLoop));
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
                var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + " do";
            }
            if (langToConvertTo == "cs") {
                var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
            }
            if (langToConvertTo == "java") {
                var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
            }
            if (langToConvertTo == "kt") {
                var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")";
            }
            if (langToConvertTo == "rb") {
                var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + " do";
            }
            if (langToConvertTo == "nim") {
                var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ":";
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
            if (langToConvertTo == "scala") {
                var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " <- " + AHKlikeLoopsIndexedAt + " to " + line + " + " + AHKlikeLoopsIndexedAt + ")";
            }
            if (langToConvertTo == "groovy") {
                var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")";
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
                htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
            }
            AindexcharLength++;
            lineDone = 1;
            htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
        }
        else if (SubStr(Trim(StrLower(A_LoopField74)), 1, StrLen(StrLower(keyWordLoop)) + 2) == StrLower(keyWordLoop) + "% ") {
            out2 = StringTrimLeft(A_LoopField74, StrLen(keyWordLoop) + 2);
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
                var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + " do";
            }
            if (langToConvertTo == "cs") {
                var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
            }
            if (langToConvertTo == "java") {
                var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
            }
            if (langToConvertTo == "kt") {
                var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")";
            }
            if (langToConvertTo == "rb") {
                var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + " do";
            }
            if (langToConvertTo == "nim") {
                var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ":";
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
            if (langToConvertTo == "scala") {
                var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " <- " + AHKlikeLoopsIndexedAt + " to " + line + " + " + AHKlikeLoopsIndexedAt + ")";
            }
            if (langToConvertTo == "groovy") {
                var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")";
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
                htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
            }
            AindexcharLength++;
            lineDone = 1;
            htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
        }
        else if (SubStr(StrLower(A_LoopField74), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
            var1 = StringTrimLeft(A_LoopField74, StrLen(keyWordLoopParse));
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
                    itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ")";
                }
                if (langToConvertTo == "lua") {
                    itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                }
                if (langToConvertTo == "cs") {
                    itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                }
                if (langToConvertTo == "java") {
                    itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
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
                    itemsOut = "\n";
                }
                if (langToConvertTo == "swift") {
                    itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                }
                if (langToConvertTo == "dart") {
                    itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                }
                if (langToConvertTo == "ts") {
                    itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                }
                if (langToConvertTo == "scala") {
                    itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
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
                        itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ")";
                    }
                    if (langToConvertTo == "lua") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                    }
                    if (langToConvertTo == "cs") {
                        itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
                    }
                    if (langToConvertTo == "java") {
                        itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
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
                        itemsOut = "\n";
                    }
                    if (langToConvertTo == "swift") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                    }
                    if (langToConvertTo == "dart") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                    }
                    if (langToConvertTo == "ts") {
                        itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                    }
                    if (langToConvertTo == "scala") {
                        itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
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
                        itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "lua") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "cs") {
                        itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "java") {
                        itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
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
                        itemsOut = "\n";
                    }
                    if (langToConvertTo == "swift") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "dart") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "ts") {
                        itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "scala") {
                        itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
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
                        itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
                    }
                    if (langToConvertTo == "java") {
                        itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
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
                        itemsOut = "\n";
                    }
                    if (langToConvertTo == "swift") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                    }
                    if (langToConvertTo == "dart") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                    }
                    if (langToConvertTo == "ts") {
                        itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                    }
                    if (langToConvertTo == "scala") {
                        itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                    }
                    if (langToConvertTo == "groovy") {
                        itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                    }
                }
                itemsOut = StrReplace(itemsOut, keyWordEscpaeChar, Chr(92));
            }
            if (langToConvertTo == "py") {
                var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in enumerate(items" + STR(AindexcharLength) + ", start=" + AHKlikeLoopsIndexedAt + "):";
            }
            if (langToConvertTo == "js") {
                var1out = itemsOut + "\n" + "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
            }
            if (langToConvertTo == "cpp") {
                var1out = itemsOut + "\n" + "for (size_t " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".size() + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
            }
            if (langToConvertTo == "go") {
                var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " := range(items" + STR(AindexcharLength) + ")";
            }
            if (langToConvertTo == "lua") {
                var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in ipairs(items" + STR(AindexcharLength) + ") do";
            }
            if (langToConvertTo == "cs") {
                var1out = itemsOut + "\n" + "foreach (var " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + ")";
            }
            if (langToConvertTo == "java") {
                var1out = itemsOut + "\n" + "for (" + keyWordALoopField + "" + STR(AindexcharLength) + " : items" + STR(AindexcharLength) + ")";
            }
            if (langToConvertTo == "kt") {
                var1out = itemsOut + "\n" + "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + ".withIndex())";
            }
            if (langToConvertTo == "rb") {
                var1out = itemsOut + "\n" + "items" + STR(AindexcharLength) + ".each_with_index do |" + keyWordALoopField + "" + STR(AindexcharLength) + " , " + keyWordAIndex + "" + STR(AindexcharLength) + "|";
            }
            if (langToConvertTo == "nim") {
                var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + " | " + keyWordAIndex + "" + STR(AindexcharLength) + " += 1:";
            }
            if (langToConvertTo == "ahk") {
                var1out = "Loop, Parse, " + line1 + " " + line2 + " " + line3;
            }
            if (langToConvertTo == "swift") {
                var1out = itemsOut + "\n" + "for (index, " + keyWordALoopField + "" + STR(AindexcharLength) + ") in items" + STR(AindexcharLength) + ".enumerated()";
            }
            if (langToConvertTo == "dart") {
                var1out = itemsOut + "\n" + "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = 0; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
            }
            if (langToConvertTo == "ts") {
                var1out = itemsOut + "\n" + "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = 0; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
            }
            if (langToConvertTo == "scala") {
                var1out = itemsOut + "\n" + "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " <- items" + STR(AindexcharLength) + ".indices)";
            }
            if (langToConvertTo == "groovy") {
                var1out = itemsOut + "\n" + "items" + STR(AindexcharLength) + ".eachWithIndex { " + keyWordALoopField + "" + STR(AindexcharLength) + " , " + keyWordAIndex + "" + STR(AindexcharLength) + " ->";
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
                theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " := items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
            }
            if (langToConvertTo == "lua") {
                theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
            }
            if (langToConvertTo == "cs") {
                theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
            }
            if (langToConvertTo == "java") {
                theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
            }
            if (langToConvertTo == "kt") {
                theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
            }
            if (langToConvertTo == "rb") {
                theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
            }
            if (langToConvertTo == "nim") {
                theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
            }
            if (langToConvertTo == "ahk") {
                theFixTextLoopLP = "\n";
            }
            if (langToConvertTo == "swift") {
                theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
            }
            if (langToConvertTo == "dart") {
                theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
            }
            if (langToConvertTo == "ts") {
                theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
            }
            if (langToConvertTo == "scala") {
                theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
            }
            if (langToConvertTo == "groovy") {
                theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
            }
            htCodeAcurlyBraceAddSomeVrasFixLP = 1;
            haveWeEverUsedAloop = 1;
            if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                htCodeLoopfixa += "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                htCodeLoopfixa1 = "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
            }
            AindexcharLength++;
            if (langToConvertTo == langFileExtension_2) {
                if (usePythonicColonSyntax_2 == "on") {
                    htCode += Trim(keyWordLoopParse_2) + " " + var1 + ":\n";
                } else {
                    htCode += Trim(keyWordLoopParse_2) + " " + var1 + "\n";
                }
            } else {
                htCode += htCodeLoopfixa1 + "\n" + var1out + "\n";
            }
        }
        else if ((SubStr(Trim(A_LoopField74), -2) == ");" || SubStr(Trim(A_LoopField74), -1) == ")") && !(InStr(A_LoopField74, "int main(int argc, char* argv[])")) && !(InStr(A_LoopField74, "async function main()")) && lineDone == 0) {
            lineDone = 1;
            str1 = Trim(A_LoopField74);
            if (langToConvertTo == langFileExtension_2) {
                if (useSemicolon_2 == "on") {
                    str2 = expressionParserTranspiler(Trim(str1)) + ";";
                } else {
                    str2 = expressionParserTranspiler(Trim(str1));
                }
            } else {
                if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "scala" || langToConvertTo == "groovy") {
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                }
                str2 = expressionParserTranspiler(Trim(str1)) + ";";
                if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "scala" || langToConvertTo == "groovy") {
                    if (SubStrLastChars(str2, 1) == ";") {
                        str2 = StringTrimRight(str2, 1);
                    }
                }
            }
            htCode += str2 + "\n";
        } else {
            //print("else else else " . A_LoopField74)
            // this is THE else
            if (lineDone != 1) {
                if (skipLeftCuleyForFuncPLS != 1) {
                    if (SubStr(Trim(StrLower(A_LoopField74)), 1, 1) == Chr(125)) {
                        htCode += Chr(125) + "\n";
                    } else {
                        if (htCodeAcurlyBraceAddSomeVrasFixLP == 1 && SubStr(Trim(StrLower(A_LoopField74)), 1, 1) == Chr(123)) {
                            htCodeAcurlyBraceAddSomeVrasFixLP = 0;
                            htCode += A_LoopField74 + "\n" + theFixTextLoopLP + "\n";
                        } else {
                            if (htCodeAcurlyBraceAddSomeVrasFixNL == 1 && SubStr(Trim(StrLower(A_LoopField74)), 1, 1) == Chr(123)) {
                                htCodeAcurlyBraceAddSomeVrasFixNL = 0;
                                htCode += A_LoopField74 + "\n" + theFixTextLoopNL + "\n";
                            } else {
                                htCode += A_LoopField74 + "\n";
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
            std::vector<std::string> items75 = LoopParseFunc(htCodeLoopfixa, "\n", "\r");
            for (size_t A_Index75 = 0; A_Index75 < items75.size() + 0; A_Index75++) {
                std::string A_LoopField75 = items75[A_Index75 - 0];
                sstr123 = A_LoopField75;
                fixLoopLokingFor = A_LoopField75;
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
                    std::vector<std::string> items76 = LoopParseFunc(htCode, "\n", "\r");
                    for (size_t A_Index76 = 0; A_Index76 < items76.size() + 0; A_Index76++) {
                        std::string A_LoopField76 = items76[A_Index76 - 0];
                        //MsgBox, dsfgsdefgesrdg1
                        //MsgBox, |%A_LoopField76%|`n|%fixLoopLokingFor%|
                        if (InStr(A_LoopField76, fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                            fixLoopLokingForNum = 1;
                            //MsgBox, do we came here 1
                        }
                        if (SubStr(Trim(A_LoopField76), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                            s = StrSplit(A_LoopField76 ,"" + keyWordAIndex + "", 2);
                            out1z = s;
                            s = StrSplit(out1z, " ", 1);
                            out1z = Trim(s);
                            //MsgBox, % out1z
                            //MsgBox, do we came here 2
                            fixLoopLokingForNum = 0;
                            foundTheTopLoop++;
                            inTarget = 1;
                            //MsgBox, % A_LoopField76
                            dontSaveStr = 1;
                            ALoopField = A_LoopField76;
                            DeleayOneCuzOfLoopParse = 1;
                            out4758686d86d86d86578991a += ALoopField + "\n";
                        }
                        if (inTarget == 1 && InStr(A_LoopField76, Chr(123)) && insdeAnestedLoopBAD != 1) {
                            insideBracket = 1;
                        }
                        if (insideBracket == 1 && InStr(A_LoopField76, Chr(123)) && insdeAnestedLoopBAD != 1) {
                            netsedCurly++;
                        }
                        if (insideBracket == 1 && InStr(A_LoopField76, Chr(125)) && insdeAnestedLoopBAD != 1) {
                            netsedCurly--;
                            readyToEnd = 1;
                        }
                        if (SubStr(Trim(A_LoopField76), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                            insdeAnestedLoopBAD = 1;
                            insideBracket1 = 0;
                            netsedCurly1 = 0;
                        }
                        if (inTarget == 1) {
                            foundTheTopLoop++;
                        }
                        if (insdeAnestedLoopBAD == 1) {
                            if (InStr(A_LoopField76, Chr(123))) {
                                insideBracket1 = 1;
                            }
                            if (insideBracket1 == 1 && InStr(A_LoopField76, Chr(123))) {
                                netsedCurly1++;
                            }
                            if (insideBracket1 == 1 && InStr(A_LoopField76, Chr(125))) {
                                netsedCurly1--;
                                readyToEnd1 = 1;
                            }
                            if (InStr(A_LoopField76, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                //MsgBox, % A_LoopField76
                                eldLoopNestedBADlol = 1;
                            }
                            out4758686d86d86d86578991a += A_LoopField76 + "\n";
                        }
                        if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                            ALoopField = A_LoopField76;
                            // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                            ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                            out4758686d86d86d86578991a += ALoopField + "\n";
                        }
                        if (inTarget == 1 && InStr(A_LoopField76, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1) {
                            //MsgBox, % A_LoopField76
                            weAreDoneHereCurly = 1;
                            inTarget = 0;
                            endBracketDOntPutThere = 1;
                        }
                        dontSaveStr = 0;
                        if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                            out4758686d86d86d86578991a += A_LoopField76 + "\n";
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
                    std::vector<std::string> items77 = LoopParseFunc(htCode, "\n", "\r");
                    for (size_t A_Index77 = 0; A_Index77 < items77.size() + 0; A_Index77++) {
                        std::string A_LoopField77 = items77[A_Index77 - 0];
                        if (InStr(A_LoopField77 , fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                            fixLoopLokingForNum = 1;
                            //MsgBox, do we came here 3
                        }
                        if (SubStr(Trim(A_LoopField77), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                            s = StrSplit(A_LoopField77 ,"" + keyWordAIndex + "", 2);
                            out1z = s;
                            s = StrSplit(out1z, " ", 1);
                            out1z = Trim(s);
                            //MsgBox, % out1z
                            fixLoopLokingForNum = 0;
                            //MsgBox, do we came here 4
                            foundTheTopLoop++;
                            inTarget = 1;
                            //MsgBox, % A_LoopField77
                            dontSaveStr = 1;
                            ALoopField = A_LoopField77;
                            DeleayOneCuzOfLoopParse = 1;
                            out4758686d86d86d86578991a += ALoopField + "\n";
                        }
                        if (inTarget == 1 && InStr(A_LoopField77, Chr(123)) && insdeAnestedLoopBAD != 1) {
                            insideBracket = 1;
                        }
                        if (insideBracket == 1 && InStr(A_LoopField77, Chr(123)) && insdeAnestedLoopBAD != 1) {
                            netsedCurly++;
                        }
                        if (insideBracket == 1 && InStr(A_LoopField77, Chr(125)) && insdeAnestedLoopBAD != 1) {
                            netsedCurly--;
                            readyToEnd = 1;
                        }
                        if (SubStr(Trim(A_LoopField77), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                            insdeAnestedLoopBAD = 1;
                            insideBracket1 = 0;
                            netsedCurly1 = 0;
                        }
                        if (inTarget == 1) {
                            foundTheTopLoop++;
                        }
                        if (insdeAnestedLoopBAD == 1) {
                            if (InStr(A_LoopField77, Chr(123))) {
                                insideBracket1 = 1;
                            }
                            if (insideBracket1 == 1 && InStr(A_LoopField77, Chr(123))) {
                                netsedCurly1++;
                            }
                            if (insideBracket1 == 1 && InStr(A_LoopField77, Chr(125))) {
                                netsedCurly1--;
                                readyToEnd1 = 1;
                            }
                            if (InStr(A_LoopField77, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                //MsgBox, % A_LoopField77
                                eldLoopNestedBADlol = 1;
                            }
                            out4758686d86d86d86578991a += A_LoopField77 + "\n";
                        }
                        if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                            ALoopField = A_LoopField77;
                            // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                            ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                            // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                            ALoopField = RegExReplace(ALoopField, "" + keyWordALoopField + "\\d*", "" + keyWordALoopField + "" + out1z);
                            out4758686d86d86d86578991a += ALoopField + "\n";
                        }
                        if ((inTarget == 1 && InStr(A_LoopField77, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1)) {
                            //MsgBox, % A_LoopField77
                            weAreDoneHereCurly = 1;
                            inTarget = 0;
                            endBracketDOntPutThere = 1;
                        }
                        dontSaveStr = 0;
                        if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                            out4758686d86d86d86578991a += A_LoopField77 + "\n";
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
            std::vector<std::string> items78 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index78 = 0; A_Index78 < items78.size() + 0; A_Index78++) {
                std::string A_LoopField78 = items78[A_Index78 - 0];
                ignore = 0;
                if (SubStr(Trim(A_LoopField78), 1, 4) == "for ") {
                    if (hold == 1 && holdText == A_LoopField78) {
                        ignore = 1;
                    } else {
                        holdText = A_LoopField78;
                        hold = 1;
                    }
                }
                if (!ignore) {
                    out4758686d86dgt8r754444444 += A_LoopField78 + "\n";
                }
            }
            out4758686d86dgt8r754444444 = StringTrimRight(out4758686d86dgt8r754444444, 1);
            htCode = out4758686d86dgt8r754444444;
        }
        htCodeOut1234565432 = "";
        std::vector<std::string> items79 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index79 = 0; A_Index79 < items79.size() + 0; A_Index79++) {
            std::string A_LoopField79 = items79[A_Index79 - 0];
            out = A_LoopField79;
            if (!InStr(out, "|itsaersdtgtgfergsdgfsegdfsedAA|")) {
                htCodeOut1234565432 += out + "\n";
            }
        }
        htCode = StringTrimRight(htCodeOut1234565432, 1);
    }
    if (COUNT_programmingBlock_InTheTranspiledLang != 0) {
        for (int A_Index80 = 0; A_Index80 < COUNT_programmingBlock_InTheTranspiledLang + 0; A_Index80++) {
            htCode = StrReplace(htCode, "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(A_Index80 + 1) + "AA", programmingBlock_InTheTranspiledLang[A_Index80]);
        }
    }
    if (langToConvertTo == "cpp") {
        if (COUNT_programmingBlock_CPP != 0) {
            for (int A_Index81 = 0; A_Index81 < COUNT_programmingBlock_CPP + 0; A_Index81++) {
                htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index81 + 1) + "AA", programmingBlock_CPP[A_Index81]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CPP != 0) {
            for (int A_Index82 = 0; A_Index82 < COUNT_programmingBlock_CPP + 0; A_Index82++) {
                htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index82 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "py") {
        if (COUNT_programmingBlock_PY != 0) {
            for (int A_Index83 = 0; A_Index83 < COUNT_programmingBlock_PY + 0; A_Index83++) {
                htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index83 + 1) + "AA", programmingBlock_PY[A_Index83]);
            }
        }
    } else {
        if (COUNT_programmingBlock_PY != 0) {
            for (int A_Index84 = 0; A_Index84 < COUNT_programmingBlock_PY + 0; A_Index84++) {
                htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index84 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "js") {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index85 = 0; A_Index85 < COUNT_programmingBlock_JS + 0; A_Index85++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index85 + 1) + "AA", programmingBlock_JS[A_Index85]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index86 = 0; A_Index86 < COUNT_programmingBlock_JS + 0; A_Index86++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index86 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "go") {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index87 = 0; A_Index87 < COUNT_programmingBlock_GO + 0; A_Index87++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index87 + 1) + "AA", programmingBlock_GO[A_Index87]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index88 = 0; A_Index88 < COUNT_programmingBlock_GO + 0; A_Index88++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index88 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "lua") {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index89 = 0; A_Index89 < COUNT_programmingBlock_LUA + 0; A_Index89++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index89 + 1) + "AA", programmingBlock_LUA[A_Index89]);
            }
        }
    } else {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index90 = 0; A_Index90 < COUNT_programmingBlock_LUA + 0; A_Index90++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index90 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "cs") {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index91 = 0; A_Index91 < COUNT_programmingBlock_CS + 0; A_Index91++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index91 + 1) + "AA", programmingBlock_CS[A_Index91]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index92 = 0; A_Index92 < COUNT_programmingBlock_CS + 0; A_Index92++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index92 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "java") {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index93 = 0; A_Index93 < COUNT_programmingBlock_JAVA + 0; A_Index93++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index93 + 1) + "AA", programmingBlock_JAVA[A_Index93]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index94 = 0; A_Index94 < COUNT_programmingBlock_JAVA + 0; A_Index94++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index94 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "js") {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index95 = 0; A_Index95 < COUNT_programmingBlock_JS + 0; A_Index95++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index95 + 1) + "AA", programmingBlock_JS[A_Index95]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index96 = 0; A_Index96 < COUNT_programmingBlock_JS + 0; A_Index96++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index96 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "go") {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index97 = 0; A_Index97 < COUNT_programmingBlock_GO + 0; A_Index97++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index97 + 1) + "AA", programmingBlock_GO[A_Index97]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index98 = 0; A_Index98 < COUNT_programmingBlock_GO + 0; A_Index98++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index98 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "lua") {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index99 = 0; A_Index99 < COUNT_programmingBlock_LUA + 0; A_Index99++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index99 + 1) + "AA", programmingBlock_LUA[A_Index99]);
            }
        }
    } else {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index100 = 0; A_Index100 < COUNT_programmingBlock_LUA + 0; A_Index100++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index100 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "cs") {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index101 = 0; A_Index101 < COUNT_programmingBlock_CS + 0; A_Index101++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index101 + 1) + "AA", programmingBlock_CS[A_Index101]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index102 = 0; A_Index102 < COUNT_programmingBlock_CS + 0; A_Index102++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index102 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "java") {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index103 = 0; A_Index103 < COUNT_programmingBlock_JAVA + 0; A_Index103++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index103 + 1) + "AA", programmingBlock_JAVA[A_Index103]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index104 = 0; A_Index104 < COUNT_programmingBlock_JAVA + 0; A_Index104++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index104 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "ts") {
        if (COUNT_programmingBlock_TS != 0) {
            for (int A_Index105 = 0; A_Index105 < COUNT_programmingBlock_TS + 0; A_Index105++) {
                htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index105 + 1) + "AA", programmingBlock_TS[A_Index105]);
            }
        }
    } else {
        if (COUNT_programmingBlock_TS != 0) {
            for (int A_Index106 = 0; A_Index106 < COUNT_programmingBlock_TS + 0; A_Index106++) {
                htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index106 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "scala") {
        if (COUNT_programmingBlock_SCALA != 0) {
            for (int A_Index107 = 0; A_Index107 < COUNT_programmingBlock_SCALA + 0; A_Index107++) {
                htCode = StrReplace(htCode, "programmingBlock_SCALA-programmingBlock_SCALA-AA" + STR(A_Index107 + 1) + "AA", programmingBlock_SCALA[A_Index107]);
            }
        }
    } else {
        if (COUNT_programmingBlock_SCALA != 0) {
            for (int A_Index108 = 0; A_Index108 < COUNT_programmingBlock_SCALA + 0; A_Index108++) {
                htCode = StrReplace(htCode, "programmingBlock_SCALA-programmingBlock_SCALA-AA" + STR(A_Index108 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "groovy") {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (int A_Index109 = 0; A_Index109 < COUNT_programmingBlock_GROOVY + 0; A_Index109++) {
                htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index109 + 1) + "AA", programmingBlock_GROOVY[A_Index109]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (int A_Index110 = 0; A_Index110 < COUNT_programmingBlock_GROOVY + 0; A_Index110++) {
                htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index110 + 1) + "AA", "\n");
            }
        }
    }
    //;;;;;;;;;;
    if (langToConvertTo == langFileExtension_2) {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (int A_Index111 = 0; A_Index111 < COUNT_programmingBlock_HTVM + 0; A_Index111++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index111 + 1) + "AA", programmingBlock_HTVM[A_Index111]);
            }
        }
    } else {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (int A_Index112 = 0; A_Index112 < COUNT_programmingBlock_HTVM + 0; A_Index112++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index112 + 1) + "AA", "\n");
            }
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    if (COUNT_programmingBlock_HTVMsyntax != 0) {
        for (int A_Index113 = 0; A_Index113 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index113++) {
            htCode = StrReplace(htCode, "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(A_Index113 + 1) + "AA", programmingBlock_HTVMsyntax[A_Index113]);
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    std::string fixLuaAndRuby = "";
    if (langToConvertTo == langFileExtension_2) {
        if (useCurlyBraces_2 == "off" && useEnd_2 == "off") {
            htCode = indent_nested_curly_braces(htCode, 0);
        } else {
            htCode = indent_nested_curly_braces(htCode, 1);
        }
        if (useEnd_2 == "on") {
            std::vector<std::string> items114 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index114 = 0; A_Index114 < items114.size() + 0; A_Index114++) {
                std::string A_LoopField114 = items114[A_Index114 - 0];
                if (Trim(A_LoopField114) == keyWordCurlyBraceClose_2) {
                    fixLuaAndRuby += StrReplace(A_LoopField114, keyWordCurlyBraceClose_2, Trim(keyWordEnd_2)) + "\n";
                }
                else if (SubStrLastChars(A_LoopField114, 2) == " " + keyWordCurlyBraceOpen_2) {
                    fixLuaAndRuby += StringTrimRight(A_LoopField114, 2) + "\n";
                } else {
                    fixLuaAndRuby += A_LoopField114 + "\n";
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
        if (langToConvertTo == "lua" || langToConvertTo == "rb") {
            std::vector<std::string> items115 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index115 = 0; A_Index115 < items115.size() + 0; A_Index115++) {
                std::string A_LoopField115 = items115[A_Index115 - 0];
                if (Trim(A_LoopField115) == "}") {
                    fixLuaAndRuby += StrReplace(A_LoopField115, "}", "end") + "\n";
                }
                else if (SubStrLastChars(A_LoopField115, 2) == " {") {
                    fixLuaAndRuby += StringTrimRight(A_LoopField115, 2) + "\n";
                } else {
                    fixLuaAndRuby += A_LoopField115 + "\n";
                }
            }
            htCode = StringTrimRight(fixLuaAndRuby, 1);
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
    std::vector<std::string> items116 = LoopParseFunc(instructions, "\n", "\r");
    for (size_t A_Index116 = 0; A_Index116 < items116.size() + 0; A_Index116++) {
        std::string A_LoopField116 = items116[A_Index116 - 0];
        if (Trim(A_LoopField116) == "funcEND======================funcEND==============") {
            areWeInAFuncFromInstructions = 0;
            areWeInAFuncFromInstructionsLineNum = 0;
            if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                //MsgBox, % funcFuncHolder
                allFuncs.push_back(funcFuncHolder);
            }
            correctLang = 0;
            funcFuncHolder = "";
        }
        if (areWeInAFuncFromInstructions == 1) {
            if (areWeInAFuncFromInstructionsLineNum == 1) {
                // name of the func
                funcLangHolder = StringTrimLeft(A_LoopField116, 5);
                if (Trim(funcLangHolder) == langToConvertTo) {
                    allFuncLang.push_back(Trim(funcLangHolder));
                    correctLang = 1;
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 2) {
                // name of the func
                funcNameHolder = StringTrimLeft(A_LoopField116, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allFuncNames.push_back(Trim(funcNameHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 3) {
                // all libs
                funcLibsHolder = StringTrimLeft(A_LoopField116, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allFuncLibs.push_back(Trim(funcLibsHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 4) {
                // func description
                funcDescriptionHolder = StringTrimLeft(A_LoopField116, 12);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allfuncDescription.push_back(Trim(funcDescriptionHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum >= 5) {
                // the full func
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    funcFuncHolder += A_LoopField116 + "\n";
                }
            }
            //MsgBox, % A_LoopField116
            areWeInAFuncFromInstructionsLineNum++;
        }
        if (Trim(A_LoopField116) == "func======================func==============") {
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
    if (langToConvertTo == "cpp") {
        htCode = htCode + "\n    return 0;\n}";
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
        htCode = htCode + "\n    }\n}";
        htCode = StrReplace(htCode, "static void Main(string[] args);", "static void Main(string[] args)");
    }
    if (langToConvertTo == "java") {
        htCode = htCode + "\n    }\n}";
        htCode = StrReplace(htCode, "public static void main(String[] args);", "public static void main(String[] args)");
    }
    if (langToConvertTo == "kt") {
        htCode = htCode + "\n}";
        htCode = StrReplace(htCode, "fun main(args: Array<String>);", "fun main(args: Array<String>)");
    }
    if (langToConvertTo == "swift") {
        htCode = htCode + "\n}\nmain()";
        htCode = StrReplace(htCode, "func main();", "func main()");
    }
    if (langToConvertTo == "dart") {
        htCode = htCode + "\n}";
        htCode = StrReplace(htCode, "void main(List<String> arguments);", "void main(List<String> arguments)");
    }
    if (langToConvertTo == "scala") {
        htCode = htCode + "\n    }\n}";
    }
    std::string jsHTMLdownCode = "</script>\n</body>\n</html>";
    int includeLibsInCppIf = 0;
    std::string allFuncsToPutAtTop = "\n";
    std::string allLibsToPutAtTop;
    if (!(allFuncNames.size() <= 0)) {
        for (int A_Index117 = 0; A_Index117 < allFuncNames.size() + 0; A_Index117++) {
            if (InStr(htCode, allFuncNames[A_Index117]) + "(") {
                //MsgBox, % allFuncNames[A_Index117]
                allFuncsToPutAtTop += allFuncs[A_Index117] + "\n";
                if (Trim(allFuncLibs[A_Index117]) != "null") {
                    allLibsToPutAtTop += allFuncLibs[A_Index117] + "|";
                }
            }
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTop, 1);
        std::string allLibsToPutAtTopTEMP;
        std::vector<std::string> items118 = LoopParseFunc(allLibsToPutAtTop, "|");
        for (size_t A_Index118 = 0; A_Index118 < items118.size() + 0; A_Index118++) {
            std::string A_LoopField118 = items118[A_Index118 - 0];
            allLibsToPutAtTopTEMP += A_LoopField118 + "\n";
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTopTEMP, 1);
        includeLibsInCppIf = 1;
        if (langToConvertTo == "cpp") {
            allLibsToPutAtTop = "#include <iostream>\n#include <sstream>\n#include <string>\n#include <cstdint>\n#include <algorithm>\n#include <vector>\n#include <any>\n#include <optional>\n" + allLibsToPutAtTop;
        }
        if (langToConvertTo == "cs") {
            allLibsToPutAtTop = "using System;\n" + allLibsToPutAtTop;
        }
        allLibsToPutAtTop = Sort(allLibsToPutAtTop, "U");
        allLibsToPutAtTop = StrReplace(allLibsToPutAtTop, "~~~", "\n");
        if (langToConvertTo == "cs" || langToConvertTo == "java" || langToConvertTo == "scala") {
            htCode = "\n" + allFuncsToPutAtTop + "\n" + htCode;
        } else {
            if (langToConvertTo != "js") {
                htCode = allLibsToPutAtTop + "\n" + allFuncsToPutAtTop + "\n" + htCode;
            } else {
                if (useJavaScriptInAfullHTMLfile != "on") {
                    htCode = allLibsToPutAtTop + "\n" + allFuncsToPutAtTop + "\n" + htCode;
                } else {
                    htCode = "\n" + allFuncsToPutAtTop + "\n" + htCode;
                }
            }
        }
    }
    if (langToConvertTo == "cs") {
        htCode = allLibsToPutAtTop + "\nclass Program\n{\n" + htCode;
    }
    if (langToConvertTo == "java") {
        htCode = allLibsToPutAtTop + "\npublic class Main\n{\n" + htCode;
    }
    if (langToConvertTo == "scala") {
        htCode = allLibsToPutAtTop + "\nobject MainApp\n{\n" + htCode;
    }
    if (langToConvertTo == "go") {
        htCode = "package main\nimport (\n" + htCode;
    }
    for (int A_Index119 = 0; A_Index119 < theIdNumOfThe34 + 0; A_Index119++) {
        if (theIdNumOfThe34 == A_Index119 + 1) {
            if (langToConvertTo == langFileExtension_2) {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(A_Index119 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index119 + 1], "\\", keyWordEscpaeChar_2) + Chr(34));
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(A_Index119 + 1) + Chr(65) + Chr(65), theIdNumOfThe34theVar[A_Index119 + 1] + Chr(34));
            }
        } else {
            if (langToConvertTo == langFileExtension_2) {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(A_Index119 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index119 + 1], "\\", keyWordEscpaeChar_2));
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(A_Index119 + 1) + Chr(65) + Chr(65), theIdNumOfThe34theVar[A_Index119 + 1]);
            }
        }
    }
    if (langToConvertTo == langFileExtension_2) {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, keyWordEscpaeChar_2 + Chr(34));
    } else {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, Chr(92) + Chr(34));
    }
    htCode = StrReplace(htCode, "std::string(" + Chr(34) + Chr(34) + ";),", "std::string(" + Chr(34) + Chr(34) + "),");
    std::string jsHTMLupCode = "<!doctype html>\n<html lang=" + Chr(34) + "en" + Chr(34) + ">\n    <head>\n        <meta charset=" + Chr(34) + "UTF-8" + Chr(34) + " />\n        <meta name=" + Chr(34) + "viewport" + Chr(34) + " content=" + Chr(34) + "width=device-width, initial-scale=1.0" + Chr(34) + " />\n        <title>HTVM</title>\n        <style>\n            body {\n                background-color: #202020;\n                font-family:\n                    " + Chr(34) + "Open Sans" + Chr(34) + ",\n                    -apple-system,\n                    BlinkMacSystemFont,\n                    " + Chr(34) + "Segoe UI" + Chr(34) + ",\n                    Roboto,\n                    Oxygen-Sans,\n                    Ubuntu,\n                    Cantarell,\n                    " + Chr(34) + "Helvetica Neue" + Chr(34) + ",\n                    Helvetica,\n                    Arial,\n                    sans-serif;\n            }\n        </style>\n" + allLibsToPutAtTop + "\n</head>\n    <body>\n<script>";
    if (useJavaScriptInAfullHTMLfile == "on" && langToConvertTo == "js") {
        htCode = jsHTMLupCode + "\n" + htCode + "\n" + jsHTMLdownCode;
    }
    if (langToConvertTo == "cpp" && includeLibsInCppIf == 0) {
        htCode = "#include <iostream>\n#include <sstream>\n#include <any>\n#include <string>\n#include <cstdint>\n#include <algorithm>\n#include <vector>\n\n" + htCode;
    }
    if (langToConvertTo == "cs") {
        htCode = "\n" + htCode;
    }
    if (langToConvertTo == "ahk") {
        htCode = "#EscapeChar \\\n" + htCode;
    }
    if (langToConvertTo == langFileExtension_2) {
        htCode = StringTrimLeft(htCode, 1);
    }
    print(htCode);
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
    std::vector<std::string> items120 = LoopParseFunc(str0);
    for (size_t A_Index120 = 0; A_Index120 < items120.size() + 0; A_Index120++) {
        std::string A_LoopField120 = items120[A_Index120 - 0];
        str00 = Trim(A_LoopField120);
        str00 = StringTrimRight(str00, 1);
    }
    print("HTVM v2");
    if (HTVM_getLang_HTVM() == "cpp" || HTVM_getLang_HTVM() == "py") {
        if (HTVM_getLang_HTVM() == "cpp") {
            print("CPP");
        }
        if (HTVM_getLang_HTVM() == "py") {
            print("PY");
        }
        std::vector<std::string> items121 = LoopParseFunc(allArgs, "\n", "\r");
        for (size_t A_Index121 = 0; A_Index121 < items121.size() + 0; A_Index121++) {
            std::string A_LoopField121 = items121[A_Index121 - 0];
            if (A_Index121 == 0) {
                numOfParams++;
                argCODE = FileRead(Trim(A_LoopField121));
                argCODEfile = Trim(A_LoopField121);
            }
            else if (A_Index121 == 1) {
                numOfParams++;
                argHTVMinstr = Trim(A_LoopField121);
            }
            else if (A_Index121 == 2) {
                numOfParams++;
                argLangTo = Trim(A_LoopField121);
            } else {
                numOfParams++;
                argHTVMinstrMORE.push_back(Trim(A_LoopField121));
            }
        }
        print("===============123431234===========start=====");
        for (int A_Index122 = 0; A_Index122 < argHTVMinstrMORE.size() + 0; A_Index122++) {
            print(argHTVMinstrMORE[A_Index122]);
        }
        print("===============123431234==========end======");
        print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        if (SubStrLastChars(argCODEfile, 4) == ".cpp" || SubStrLastChars(argCODEfile, 3) == ".py" || SubStrLastChars(argCODEfile, 3) == ".js" || SubStrLastChars(argCODEfile, 3) == ".go" || SubStrLastChars(argCODEfile, 4) == ".lua" || SubStrLastChars(argCODEfile, 3) == ".cs" || SubStrLastChars(argCODEfile, 5) == ".java" || SubStrLastChars(argCODEfile, 3) == ".kt" || SubStrLastChars(argCODEfile, 3) == ".rb" || SubStrLastChars(argCODEfile, 4) == ".nim" || SubStrLastChars(argCODEfile, 4) == ".ahk" || SubStrLastChars(argCODEfile, 6) == ".swift" || SubStrLastChars(argCODEfile, 5) == ".dart" || SubStrLastChars(argCODEfile, 3) == ".ts" || SubStrLastChars(argCODEfile, 6) == ".scala" || SubStrLastChars(argCODEfile, 7) == ".groovy" || SubStrLastChars(argCODEfile, StrLen("." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)))) == "." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)) && numOfParams == 2) {
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
            else if (SubStrLastChars(argCODEfile, 6) == ".scala") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "scala");
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
            else if (SubStrLastChars(argCODEfile, StrLen("." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)))) == "." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2))) {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)));
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            } else {
                print("INVALID LANG!!!");
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
        print("JS");
    }
}
int main(int argc, char* argv[]) {
    HTVMv2();
    return 0;
}