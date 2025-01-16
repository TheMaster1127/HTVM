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
#include <set>
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

// Function to sort and remove duplicates
std::vector<std::string> sortArr(const std::vector<std::string>& input) {
    std::set<std::string> uniqueSorted(input.begin(), input.end());
    return std::vector<std::string>(uniqueSorted.begin(), uniqueSorted.end());
}

// Function to sort an array of strings by length in descending order
void sortArrByLenOnly(std::vector<std::string>& array) {
    std::sort(array.begin(), array.end(), [](const std::string& a, const std::string& b) {
        return a.length() > b.length();
    });
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
std::vector<std::string> programmingBlock_SCALA;
std::vector<std::string> programmingBlock_GROOVY;
std::vector<std::string> programmingBlock_HTVM;
std::vector<std::string> programmingBlock_HTVMsyntax;
std::vector<std::string> fullLangAllOperators;
std::vector<std::string> fullLangAllOperators_HELP;
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
std::string fixArray1234(std::string line) {
    std::string out = "";
    int started = 0;
    std::vector<std::string> items50 = LoopParseFunc(line);
    for (size_t A_Index50 = 0; A_Index50 < items50.size() + 0; A_Index50++) {
        std::string A_LoopField50 = items50[A_Index50 - 0];
        if (started == 1) {
            if (StrLen(line) == A_Index50 + 1) {
                return out;
            }
            out += A_LoopField50;
        }
        if (A_LoopField50 == "(") {
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
    if (langToConvertTo != "swift") {
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
    std::vector<std::string> items51 = LoopParseFunc(line);
    for (size_t A_Index51 = 0; A_Index51 < items51.size() + 0; A_Index51++) {
        std::string A_LoopField51 = items51[A_Index51 - 0];
        arrAll.push_back(A_LoopField51);
    }
    int i1 = 0;
    std::string tempHold = "";
    int holdPos = 0;
    std::vector<int> holdPositions;
    for (int A_Index52 = 0; A_Index52 < arrAll.size() + 0; A_Index52++) {
        tempHold = "";
        if (arrAll.size() - StrLen(arrayMethodStr) + 1 == i1) {
            break;
        }
        for (int A_Index53 = 0; A_Index53 < StrLen(arrayMethodStr) + 0; A_Index53++) {
            tempHold += arrAll[A_Index53 + i1];
        }
        i1++;
        //print(tempHold)
        if (tempHold == arrayMethodStr) {
            holdPos = i1;
            //print(holdPos)
            holdPositions.push_back(holdPos);
        }
    }
    //print("===========================================")
    int holdPositionsTEMP = 0;
    for (int A_Index54 = 0; A_Index54 < holdPositions.size() + 0; A_Index54++) {
        holdPositionsTEMP = holdPositions[A_Index54];
        i1 = arrAll.size();
        tempHold = "";
        for (int A_Index55 = 0; A_Index55 < arrAll.size() + 0; A_Index55++) {
            if (holdPositionsTEMP >= i1 + 1) {
                if (InStr(allDelimiters, arrAll[i1]) == false) {
                    tempHold += arrAll[i1 - 1];
                } else {
                    break;
                }
            }
            i1--;
        }
        //print(await StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", ""))))
        holdPositions[A_Index54] = holdPositions[A_Index54] - StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", "")));
    }
    //;;;;;;;;;;;;;;;;;;
    int foundFirstParenthesis = 0;
    int ParenthesisStackOPEN = 0;
    int ParenthesisStackCLOSE = 0;
    std::vector<int> holdPositionsEnd;
    holdPositionsTEMP = 0;
    for (int A_Index56 = 0; A_Index56 < holdPositions.size() + 0; A_Index56++) {
        holdPositionsTEMP = holdPositions[A_Index56];
        i1 = 0;
        tempHold = "";
        foundFirstParenthesis = 0;
        ParenthesisStackOPEN = 0;
        ParenthesisStackCLOSE = 0;
        for (int A_Index57 = 0; A_Index57 < arrAll.size() + 0; A_Index57++) {
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
                    holdPositionsEnd.push_back(i1 + 1);
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
    for (int A_Index58 = 0; A_Index58 < holdPositions.size() + 0; A_Index58++) {
        startPosReplace = holdPositions[holdPositions.size() - A_Index58 - 1];
        endPosReplace = holdPositionsEnd[holdPositions.size() - A_Index58 - 1];
        holdDebug = "";
        beenInside = 0;
        holdDebugLen = 0;
        canOut = 1;
        std::vector<std::string> items59 = LoopParseFunc(line);
        for (size_t A_Index59 = 0; A_Index59 < items59.size() + 0; A_Index59++) {
            std::string A_LoopField59 = items59[A_Index59 - 0];
            if (A_Index59 + 1 >= startPosReplace && A_Index59 + 1 <= endPosReplace) {
                holdDebug += A_LoopField59;
            }
        }
        holdDebugLen = StrLen(holdDebug);
        std::vector<std::string> items60 = LoopParseFunc(line);
        for (size_t A_Index60 = 0; A_Index60 < items60.size() + 0; A_Index60++) {
            std::string A_LoopField60 = items60[A_Index60 - 0];
            if (A_Index60 + 1 >= startPosReplace && A_Index60 + 1 <= endPosReplace) {
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
                    out += A_LoopField60;
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
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayAppend + "(", "." + keyWordArrayAppend_2 + "(");
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayPop + "(", "." + keyWordArrayPop_2 + "(");
        line = HTVMmatchStrRrplace(line, "." + keyWordArraySize + "(", "." + keyWordArraySize_2 + "(");
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayInsert + "(", "." + keyWordArrayInsert_2 + "(");
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayRemove + "(", "." + keyWordArrayRemove_2 + "(");
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayIndexOf + "(", "." + keyWordArrayIndexOf_2 + "(");
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
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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
        fullLangAllOperators.push_back("nullptr");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "py") {
        fullLangAllOperators.push_back("None");
        fullLangAllOperators.push_back("True");
        fullLangAllOperators.push_back("False");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("**");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("is");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("and");
        fullLangAllOperators.push_back("or");
        fullLangAllOperators.push_back("not");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
    }
    if (langToConvertTo == "js") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("**");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("===");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back(">>>");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "go") {
        fullLangAllOperators.push_back("nil");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
    }
    if (langToConvertTo == "lua") {
        fullLangAllOperators.push_back("nil");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("..");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("~=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("and");
        fullLangAllOperators.push_back("or");
        fullLangAllOperators.push_back("not");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
    }
    if (langToConvertTo == "cs") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "java") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back(">>>");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "kt") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("===");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("and");
        fullLangAllOperators.push_back("or");
        fullLangAllOperators.push_back("xor");
        fullLangAllOperators.push_back("inv");
        fullLangAllOperators.push_back("shl");
        fullLangAllOperators.push_back("shr");
        fullLangAllOperators.push_back("ushr");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "rb") {
        fullLangAllOperators.push_back("nil");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("**");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "nim") {
        fullLangAllOperators.push_back("nil");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("and");
        fullLangAllOperators.push_back("or");
        fullLangAllOperators.push_back("not");
        fullLangAllOperators.push_back("and");
        fullLangAllOperators.push_back("or");
        fullLangAllOperators.push_back("xor");
        fullLangAllOperators.push_back("not");
        fullLangAllOperators.push_back("shl");
        fullLangAllOperators.push_back("shr");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
    }
    if (langToConvertTo == "ahk") {
        fullLangAllOperators.push_back(Chr(34) + "" + Chr(34));
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back(".");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("=");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "swift") {
        fullLangAllOperators.push_back("nil");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("===");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "dart") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("===");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back(">>>");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "ts") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("**");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("===");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back(">>>");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "scala") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("eq");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back(">>>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
    }
    if (langToConvertTo == "groovy") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("**");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back(">>>");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == langFileExtension_2) {
        fullLangAllOperators.push_back(keyWordNull_2);
        fullLangAllOperators.push_back(keyWordTrue_2);
        fullLangAllOperators.push_back(keyWordFalse_2);
        fullLangAllOperators.push_back(keyWordConcat_2);
        fullLangAllOperators.push_back(keyWordAdd_2);
        fullLangAllOperators.push_back(keyWordSub_2);
        fullLangAllOperators.push_back(keyWordMul_2);
        fullLangAllOperators.push_back(keyWordDiv_2);
        fullLangAllOperators.push_back(keyWordMod_2);
        fullLangAllOperators.push_back(keyWordExp_2);
        fullLangAllOperators.push_back(keyWordEqual_2);
        fullLangAllOperators.push_back(keyWordStrictEqual_2);
        fullLangAllOperators.push_back(keyWordNotEqual_2);
        fullLangAllOperators.push_back(keyWordGreater_2);
        fullLangAllOperators.push_back(keyWordLess_2);
        fullLangAllOperators.push_back(keyWordGreaterEqual_2);
        fullLangAllOperators.push_back(keyWordLessEqual_2);
        fullLangAllOperators.push_back(keyWordAnd_2);
        fullLangAllOperators.push_back(keyWordOr_2);
        fullLangAllOperators.push_back(keyWordNot_2);
        fullLangAllOperators.push_back(keyWordBitAnd_2);
        fullLangAllOperators.push_back(keyWordBitOr_2);
        fullLangAllOperators.push_back(keyWordBitXor_2);
        fullLangAllOperators.push_back(keyWordBitNot_2);
        fullLangAllOperators.push_back(keyWordShiftLeft_2);
        fullLangAllOperators.push_back(keyWordShiftRight_2);
        fullLangAllOperators.push_back(keyWordShiftUnsignedRight_2);
        fullLangAllOperators.push_back(keyWordTernary1_2);
        fullLangAllOperators.push_back(keyWordTernary2_2);
    }
    return fullLangAllOperators;
}
std::vector<std::string> GETfullLangAllOperators_HELP() {
    std::vector<std::string> fullLangAllOperators_HELP;
    fullLangAllOperators_HELP.push_back("01|" + keyWordNull);
    fullLangAllOperators_HELP.push_back("02|" + keyWordTrue);
    fullLangAllOperators_HELP.push_back("03|" + keyWordFalse);
    fullLangAllOperators_HELP.push_back("04|" + keyWordConcat);
    fullLangAllOperators_HELP.push_back("05|" + keyWordAdd);
    fullLangAllOperators_HELP.push_back("06|" + keyWordSub);
    fullLangAllOperators_HELP.push_back("07|" + keyWordMul);
    fullLangAllOperators_HELP.push_back("08|" + keyWordDiv);
    fullLangAllOperators_HELP.push_back("09|" + keyWordMod);
    fullLangAllOperators_HELP.push_back("10|" + keyWordExp);
    fullLangAllOperators_HELP.push_back("11|" + keyWordEqual);
    fullLangAllOperators_HELP.push_back("12|" + keyWordStrictEqual);
    fullLangAllOperators_HELP.push_back("13|" + keyWordNotEqual);
    fullLangAllOperators_HELP.push_back("14|" + keyWordGreater);
    fullLangAllOperators_HELP.push_back("15|" + keyWordLess);
    fullLangAllOperators_HELP.push_back("16|" + keyWordGreaterEqual);
    fullLangAllOperators_HELP.push_back("17|" + keyWordLessEqual);
    fullLangAllOperators_HELP.push_back("18|" + keyWordAnd);
    fullLangAllOperators_HELP.push_back("19|" + keyWordOr);
    fullLangAllOperators_HELP.push_back("20|" + keyWordNot);
    fullLangAllOperators_HELP.push_back("21|" + keyWordBitAnd);
    fullLangAllOperators_HELP.push_back("22|" + keyWordBitOr);
    fullLangAllOperators_HELP.push_back("23|" + keyWordBitXor);
    fullLangAllOperators_HELP.push_back("24|" + keyWordBitNot);
    fullLangAllOperators_HELP.push_back("25|" + keyWordShiftLeft);
    fullLangAllOperators_HELP.push_back("26|" + keyWordShiftRight);
    fullLangAllOperators_HELP.push_back("27|" + keyWordShiftUnsignedRight);
    fullLangAllOperators_HELP.push_back("28|" + keyWordTernary1);
    fullLangAllOperators_HELP.push_back("29|" + keyWordTernary2);
    sortArrByLenOnly(fullLangAllOperators_HELP);
    return fullLangAllOperators_HELP;
}
std::string expressionParserTranspiler(std::string expression) {
    for (int A_Index61 = 0; A_Index61 < 29 + 0; A_Index61++) {
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "01") {
            expression = StrReplace(expression, keyWordNull, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA1AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "02") {
            expression = StrReplace(expression, keyWordTrue, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA2AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "03") {
            expression = StrReplace(expression, keyWordFalse, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA3AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "04") {
            expression = StrReplace(expression, keyWordConcat, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA4AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "05") {
            expression = StrReplace(expression, keyWordAdd, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA5AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "06") {
            expression = StrReplace(expression, keyWordSub, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA6AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "07") {
            expression = StrReplace(expression, keyWordMul, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA7AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "08") {
            expression = StrReplace(expression, keyWordDiv, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA8AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "09") {
            expression = StrReplace(expression, keyWordMod, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA9AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "10") {
            expression = StrReplace(expression, keyWordExp, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA10AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "11") {
            expression = StrReplace(expression, keyWordEqual, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA11AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "12") {
            expression = StrReplace(expression, keyWordStrictEqual, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA12AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "13") {
            expression = StrReplace(expression, keyWordNotEqual, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA13AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "14") {
            expression = StrReplace(expression, keyWordGreater, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA14AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "15") {
            expression = StrReplace(expression, keyWordLess, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA15AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "16") {
            expression = StrReplace(expression, keyWordGreaterEqual, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA16AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "17") {
            expression = StrReplace(expression, keyWordLessEqual, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA17AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "18") {
            expression = StrReplace(expression, keyWordAnd, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA18AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "19") {
            expression = StrReplace(expression, keyWordOr, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA19AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "20") {
            expression = StrReplace(expression, keyWordNot, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA20AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "21") {
            expression = StrReplace(expression, keyWordBitAnd, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA21AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "22") {
            expression = StrReplace(expression, keyWordBitOr, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA22AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "23") {
            expression = StrReplace(expression, keyWordBitXor, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA23AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "24") {
            expression = StrReplace(expression, keyWordBitNot, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA24AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "25") {
            expression = StrReplace(expression, keyWordShiftLeft, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA25AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "26") {
            expression = StrReplace(expression, keyWordShiftRight, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA26AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "27") {
            expression = StrReplace(expression, keyWordShiftUnsignedRight, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA27AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "28") {
            expression = StrReplace(expression, keyWordTernary1, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA28AA");
        }
        if (StrSplit(fullLangAllOperators_HELP[A_Index61], "|", 1) == "29") {
            expression = StrReplace(expression, keyWordTernary2, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA29AA");
        }
    }
    for (int A_Index62 = 0; A_Index62 < 29 + 0; A_Index62++) {
        expression = StrReplace(expression, "asihgapvaQQQsQQQvbaQQQfvsbaQQQABSQQQWERSQQQFZDQQQSDXVQQQQQQAsdfdgdQQQasxAA" + STR(A_Index62 + 1) + "AA", fullLangAllOperators[A_Index62]);
    }
    // extra for array methods
    expression = arrayParserTranspiler(expression);
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
    std::string instructions = allInstructionFile;
    std::vector<std::string> items63 = LoopParseFunc(allInstructionFile, "\n", "\r");
    for (size_t A_Index63 = 0; A_Index63 < items63.size() + 0; A_Index63++) {
        std::string A_LoopField63 = items63[A_Index63 - 0];
        if (A_Index63 == 0) {
            langToConvertTo = Trim(A_LoopField63);
        }
        if (A_Index63 == 1) {
            langFileExtension = Trim(A_LoopField63);
        }
        if (A_Index63 == 2) {
            commands = Trim(A_LoopField63);
        }
        if (A_Index63 == 3) {
            keyWordAlliance = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 4) {
            keyWordCrew = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 5) {
            keyWordMethod = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 6) {
            keyWordDefObj = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 7) {
            keyWordPorp = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 8) {
            keyWordThis = Trim(A_LoopField63);
        }
        if (A_Index63 == 9) {
            keyWordInclude = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 10) {
            keyWordIncludeInTheTranspiledLang = Trim(A_LoopField63);
        }
        if (A_Index63 == 11) {
            keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField63);
        }
        if (A_Index63 == 12) {
            keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField63);
        }
        if (A_Index63 == 13) {
            keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField63);
        }
        if (A_Index63 == 14) {
            keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField63);
        }
        if (A_Index63 == 15) {
            keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField63);
        }
        if (A_Index63 == 16) {
            keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField63);
        }
        if (A_Index63 == 17) {
            keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField63);
        }
        if (A_Index63 == 18) {
            keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField63);
        }
        if (A_Index63 == 19) {
            keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField63);
        }
        if (A_Index63 == 20) {
            keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField63);
        }
        if (A_Index63 == 21) {
            keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField63);
        }
        if (A_Index63 == 22) {
            keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField63);
        }
        if (A_Index63 == 23) {
            keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField63);
        }
        if (A_Index63 == 24) {
            keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField63);
        }
        if (A_Index63 == 25) {
            keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField63);
        }
        if (A_Index63 == 26) {
            keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField63);
        }
        if (A_Index63 == 27) {
            keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField63);
        }
        if (A_Index63 == 28) {
            keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField63);
        }
        if (A_Index63 == 29) {
            keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField63);
        }
        if (A_Index63 == 30) {
            keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField63);
        }
        if (A_Index63 == 31) {
            keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField63);
        }
        if (A_Index63 == 32) {
            keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField63);
        }
        if (A_Index63 == 33) {
            keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField63);
        }
        if (A_Index63 == 34) {
            keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField63);
        }
        if (A_Index63 == 35) {
            keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField63);
        }
        if (A_Index63 == 36) {
            keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField63);
        }
        if (A_Index63 == 37) {
            keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField63);
        }
        if (A_Index63 == 38) {
            keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField63);
        }
        if (A_Index63 == 39) {
            keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField63);
        }
        if (A_Index63 == 40) {
            keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField63);
        }
        if (A_Index63 == 41) {
            keyWordCodeInTheTranspiledLangStartSCALA = Trim(A_LoopField63);
        }
        if (A_Index63 == 42) {
            keyWordCodeInTheTranspiledLangEndSCALA = Trim(A_LoopField63);
        }
        if (A_Index63 == 43) {
            keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField63);
        }
        if (A_Index63 == 44) {
            keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField63);
        }
        if (A_Index63 == 45) {
            keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField63);
        }
        if (A_Index63 == 46) {
            keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField63);
        }
        if (A_Index63 == 47) {
            keyWordCodeInHTVMstart = Trim(A_LoopField63);
        }
        if (A_Index63 == 48) {
            keyWordCodeInHTVMend = Trim(A_LoopField63);
        }
        if (A_Index63 == 49) {
            keyWordCurlyBraceOpen = Trim(A_LoopField63);
        }
        if (A_Index63 == 50) {
            keyWordCurlyBraceClose = Trim(A_LoopField63);
        }
        if (A_Index63 == 51) {
            keyWordNull = Trim(A_LoopField63);
        }
        if (A_Index63 == 52) {
            keyWordTrue = Trim(A_LoopField63);
        }
        if (A_Index63 == 53) {
            keyWordFalse = Trim(A_LoopField63);
        }
        if (A_Index63 == 54) {
            keyWordVoid = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 55) {
            keyWordDouble = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 56) {
            keyWordChar = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 57) {
            keyWordUint8 = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 58) {
            keyWordUint16 = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 59) {
            keyWordUint32 = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 60) {
            keyWordUint64 = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 61) {
            keyWordINT = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 62) {
            keyWordSTR = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 63) {
            keyWordBOOL = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 64) {
            keyWordFLOAT = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 65) {
            keyWordINT8 = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 66) {
            keyWordINT16 = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 67) {
            keyWordINT32 = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 68) {
            keyWordINT64 = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 69) {
            keyWordIF = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 70) {
            keyWordElseIf = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 71) {
            keyWordElse = Trim(A_LoopField63);
        }
        if (A_Index63 == 72) {
            keyWordSwitch = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 73) {
            keyWordSwitchCase = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 74) {
            keyWordSwitchDefault = Trim(A_LoopField63);
        }
        if (A_Index63 == 75) {
            keyWordWhileLoop = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 76) {
            keyWordLoopInfinite = Trim(A_LoopField63);
        }
        if (A_Index63 == 77) {
            keyWordLoop = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 78) {
            keyWordLoopParse = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 79) {
            keyWordContinue = Trim(A_LoopField63);
        }
        if (A_Index63 == 80) {
            keyWordBreak = Trim(A_LoopField63);
        }
        if (A_Index63 == 81) {
            keyWordFunc = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 82) {
            keyWordAwait = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 83) {
            keyWordAsync = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 84) {
            keyWordThrow = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 85) {
            keyWordErrorMsg = Trim(A_LoopField63);
        }
        if (A_Index63 == 86) {
            keyWordTry = Trim(A_LoopField63);
        }
        if (A_Index63 == 87) {
            keyWordCatch = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 88) {
            keyWordFinally = Trim(A_LoopField63);
        }
        if (A_Index63 == 89) {
            keyWordReturnStatement = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 90) {
            keyWordArrayAppend = Trim(A_LoopField63);
        }
        if (A_Index63 == 91) {
            keyWordArrayPop = Trim(A_LoopField63);
        }
        if (A_Index63 == 92) {
            keyWordArraySize = Trim(A_LoopField63);
        }
        if (A_Index63 == 93) {
            keyWordArrayInsert = Trim(A_LoopField63);
        }
        if (A_Index63 == 94) {
            keyWordArrayRemove = Trim(A_LoopField63);
        }
        if (A_Index63 == 95) {
            keyWordArrayIndexOf = Trim(A_LoopField63);
        }
        if (A_Index63 == 96) {
            keyWordArrayDefinition = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 97) {
            keyWordArrayOfIntegersDefinition = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 98) {
            keyWordArrayOfStringsDefinition = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 99) {
            keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 100) {
            keyWordArrayOfBooleansDefinition = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 101) {
            keyWordVar = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 102) {
            keyWordLet = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 103) {
            keyWordConst = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 104) {
            keyWordEnd = Trim(A_LoopField63);
        }
        if (A_Index63 == 105) {
            keyWordGlobal = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 106) {
            keyWordComment = Trim(A_LoopField63);
        }
        if (A_Index63 == 107) {
            keyWordCommentOpenMultiLine = Trim(A_LoopField63);
        }
        if (A_Index63 == 108) {
            keyWordCommentCloseMultiLine = Trim(A_LoopField63);
        }
        if (A_Index63 == 109) {
            keyWordEscpaeChar = Trim(A_LoopField63);
        }
        if (A_Index63 == 110) {
            keyWordMainLabel = Trim(A_LoopField63);
        }
        if (A_Index63 == 111) {
            keyWordConcat = Trim(A_LoopField63);
        }
        if (A_Index63 == 112) {
            keyWordAdd = Trim(A_LoopField63);
        }
        if (A_Index63 == 113) {
            keyWordSub = Trim(A_LoopField63);
        }
        if (A_Index63 == 114) {
            keyWordMul = Trim(A_LoopField63);
        }
        if (A_Index63 == 115) {
            keyWordDiv = Trim(A_LoopField63);
        }
        if (A_Index63 == 116) {
            keyWordMod = Trim(A_LoopField63);
        }
        if (A_Index63 == 117) {
            keyWordExp = Trim(A_LoopField63);
        }
        if (A_Index63 == 118) {
            keyWordEqual = Trim(A_LoopField63);
        }
        if (A_Index63 == 119) {
            keyWordStrictEqual = Trim(A_LoopField63);
        }
        if (A_Index63 == 120) {
            keyWordNotEqual = Trim(A_LoopField63);
        }
        if (A_Index63 == 121) {
            keyWordGreater = Trim(A_LoopField63);
        }
        if (A_Index63 == 122) {
            keyWordLess = Trim(A_LoopField63);
        }
        if (A_Index63 == 123) {
            keyWordGreaterEqual = Trim(A_LoopField63);
        }
        if (A_Index63 == 124) {
            keyWordLessEqual = Trim(A_LoopField63);
        }
        if (A_Index63 == 125) {
            keyWordAnd = Trim(A_LoopField63);
        }
        if (A_Index63 == 126) {
            keyWordOr = Trim(A_LoopField63);
        }
        if (A_Index63 == 127) {
            keyWordNot = Trim(A_LoopField63);
        }
        if (A_Index63 == 128) {
            keyWordBitAnd = Trim(A_LoopField63);
        }
        if (A_Index63 == 129) {
            keyWordBitOr = Trim(A_LoopField63);
        }
        if (A_Index63 == 130) {
            keyWordBitXor = Trim(A_LoopField63);
        }
        if (A_Index63 == 131) {
            keyWordBitNot = Trim(A_LoopField63);
        }
        if (A_Index63 == 132) {
            keyWordShiftLeft = Trim(A_LoopField63);
        }
        if (A_Index63 == 133) {
            keyWordShiftRight = Trim(A_LoopField63);
        }
        if (A_Index63 == 134) {
            keyWordShiftUnsignedRight = Trim(A_LoopField63);
        }
        if (A_Index63 == 135) {
            keyWordAssign = Trim(A_LoopField63);
        }
        if (A_Index63 == 136) {
            keyWordAssignAdd = Trim(A_LoopField63);
        }
        if (A_Index63 == 137) {
            keyWordAssignConcat = Trim(A_LoopField63);
        }
        if (A_Index63 == 138) {
            keyWordAssignSub = Trim(A_LoopField63);
        }
        if (A_Index63 == 139) {
            keyWordAssignMul = Trim(A_LoopField63);
        }
        if (A_Index63 == 140) {
            keyWordAssignDiv = Trim(A_LoopField63);
        }
        if (A_Index63 == 141) {
            keyWordAssignMod = Trim(A_LoopField63);
        }
        if (A_Index63 == 142) {
            keyWordAssignShiftLeft = Trim(A_LoopField63);
        }
        if (A_Index63 == 143) {
            keyWordAssignShiftRight = Trim(A_LoopField63);
        }
        if (A_Index63 == 144) {
            keyWordLogicalAssignShiftRight = Trim(A_LoopField63);
        }
        if (A_Index63 == 145) {
            keyWordAssignBitAnd = Trim(A_LoopField63);
        }
        if (A_Index63 == 146) {
            keyWordAssignBitOr = Trim(A_LoopField63);
        }
        if (A_Index63 == 147) {
            keyWordAssignBitXor = Trim(A_LoopField63);
        }
        if (A_Index63 == 148) {
            keyWordTernary1 = Trim(A_LoopField63);
        }
        if (A_Index63 == 149) {
            keyWordTernary2 = Trim(A_LoopField63);
        }
        if (A_Index63 == 150) {
            keyWordInc = Trim(A_LoopField63);
        }
        if (A_Index63 == 151) {
            keyWordDec = Trim(A_LoopField63);
        }
        if (A_Index63 == 152) {
            AHKlikeLoopsIndexedAt = Trim(A_LoopField63);
        }
        if (A_Index63 == 153) {
            keyWordAIndex = Trim(A_LoopField63);
        }
        if (A_Index63 == 154) {
            keyWordALoopField = Trim(A_LoopField63);
        }
        if (A_Index63 == 155) {
            useCurlyBraces = Trim(A_LoopField63);
        }
        if (A_Index63 == 156) {
            useEnd = Trim(A_LoopField63);
        }
        if (A_Index63 == 157) {
            useSemicolon = Trim(A_LoopField63);
        }
        if (A_Index63 == 158) {
            useParentheses = Trim(A_LoopField63);
        }
        if (A_Index63 == 159) {
            usePrefixTypeForTypeDefinition = Trim(A_LoopField63);
        }
        if (A_Index63 == 160) {
            usePostfixTypeForTypeDefinition = Trim(A_LoopField63);
        }
        if (A_Index63 == 161) {
            usePythonicColonSyntax = Trim(A_LoopField63);
        }
        if (A_Index63 == 162) {
            useCurlyBracesSyntaxForArrayDef = Trim(A_LoopField63);
        }
        if (A_Index63 == 163) {
            useInJavaScriptAlwaysUseVar = Trim(A_LoopField63);
        }
        if (A_Index63 == 164) {
            useJavaScriptInAfullHTMLfile = Trim(A_LoopField63);
        }
        if (A_Index63 == 165) {
            useJavaScriptAmainFuncDef = Trim(A_LoopField63);
        }
        if (A_Index63 == 166) {
            useJavaScriptAllFuncsAreAsync = Trim(A_LoopField63);
        }
        if (A_Index63 == 167) {
            useJavaScriptAlwaysTripleEqual = Trim(A_LoopField63);
        }
    }
    if (argHTVMinstrMORE.size() > 0) {
        std::string allInstructionFile_2 = Trim(FileRead(Trim(argHTVMinstrMORE[0])));
        std::vector<std::string> items64 = LoopParseFunc(allInstructionFile_2, "\n", "\r");
        for (size_t A_Index64 = 0; A_Index64 < items64.size() + 0; A_Index64++) {
            std::string A_LoopField64 = items64[A_Index64 - 0];
            if (A_Index64 == 0) {
                langToConvertTo_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 1) {
                langFileExtension_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 2) {
                commands_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 3) {
                keyWordAlliance_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 4) {
                keyWordCrew_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 5) {
                keyWordMethod_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 6) {
                keyWordDefObj_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 7) {
                keyWordPorp_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 8) {
                keyWordThis_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 9) {
                keyWordInclude_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 10) {
                keyWordIncludeInTheTranspiledLang_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 11) {
                keyWordCodeInTheTranspiledLangStart_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 12) {
                keyWordCodeInTheTranspiledLangEnd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 13) {
                keyWordCodeInTheTranspiledLangStartCPP_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 14) {
                keyWordCodeInTheTranspiledLangEndCPP_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 15) {
                keyWordCodeInTheTranspiledLangStartPY_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 16) {
                keyWordCodeInTheTranspiledLangEndPY_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 17) {
                keyWordCodeInTheTranspiledLangStartJS_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 18) {
                keyWordCodeInTheTranspiledLangEndJS_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 19) {
                keyWordCodeInTheTranspiledLangStartGO_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 20) {
                keyWordCodeInTheTranspiledLangEndGO_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 21) {
                keyWordCodeInTheTranspiledLangStartLUA_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 22) {
                keyWordCodeInTheTranspiledLangEndLUA_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 23) {
                keyWordCodeInTheTranspiledLangStartCS_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 24) {
                keyWordCodeInTheTranspiledLangEndCS_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 25) {
                keyWordCodeInTheTranspiledLangStartJAVA_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 26) {
                keyWordCodeInTheTranspiledLangEndJAVA_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 27) {
                keyWordCodeInTheTranspiledLangStartKT_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 28) {
                keyWordCodeInTheTranspiledLangEndKT_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 29) {
                keyWordCodeInTheTranspiledLangStartRB_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 30) {
                keyWordCodeInTheTranspiledLangEndRB_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 31) {
                keyWordCodeInTheTranspiledLangStartNIM_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 32) {
                keyWordCodeInTheTranspiledLangEndNIM_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 33) {
                keyWordCodeInTheTranspiledLangStartAHK_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 34) {
                keyWordCodeInTheTranspiledLangEndAHK_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 35) {
                keyWordCodeInTheTranspiledLangStartSWIFT_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 36) {
                keyWordCodeInTheTranspiledLangEndSWIFT_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 37) {
                keyWordCodeInTheTranspiledLangStartDART_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 38) {
                keyWordCodeInTheTranspiledLangEndDART_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 39) {
                keyWordCodeInTheTranspiledLangStartTS_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 40) {
                keyWordCodeInTheTranspiledLangEndTS_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 41) {
                keyWordCodeInTheTranspiledLangStartSCALA_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 42) {
                keyWordCodeInTheTranspiledLangEndSCALA_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 43) {
                keyWordCodeInTheTranspiledLangStartGROOVY_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 44) {
                keyWordCodeInTheTranspiledLangEndGROOVY_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 45) {
                keyWordCodeInTheTranspiledLangStartHTVM_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 46) {
                keyWordCodeInTheTranspiledLangEndHTVM_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 47) {
                keyWordCodeInHTVMstart_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 48) {
                keyWordCodeInHTVMend_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 49) {
                keyWordCurlyBraceOpen_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 50) {
                keyWordCurlyBraceClose_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 51) {
                keyWordNull_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 52) {
                keyWordTrue_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 53) {
                keyWordFalse_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 54) {
                keyWordVoid_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 55) {
                keyWordDouble_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 56) {
                keyWordChar_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 57) {
                keyWordUint8_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 58) {
                keyWordUint16_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 59) {
                keyWordUint32_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 60) {
                keyWordUint64_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 61) {
                keyWordINT_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 62) {
                keyWordSTR_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 63) {
                keyWordBOOL_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 64) {
                keyWordFLOAT_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 65) {
                keyWordINT8_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 66) {
                keyWordINT16_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 67) {
                keyWordINT32_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 68) {
                keyWordINT64_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 69) {
                keyWordIF_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 70) {
                keyWordElseIf_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 71) {
                keyWordElse_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 72) {
                keyWordSwitch_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 73) {
                keyWordSwitchCase_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 74) {
                keyWordSwitchDefault_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 75) {
                keyWordWhileLoop_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 76) {
                keyWordLoopInfinite_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 77) {
                keyWordLoop_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 78) {
                keyWordLoopParse_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 79) {
                keyWordContinue_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 80) {
                keyWordBreak_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 81) {
                keyWordFunc_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 82) {
                keyWordAwait_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 83) {
                keyWordAsync_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 84) {
                keyWordThrow_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 85) {
                keyWordErrorMsg_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 86) {
                keyWordTry_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 87) {
                keyWordCatch_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 88) {
                keyWordFinally_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 89) {
                keyWordReturnStatement_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 90) {
                keyWordArrayAppend_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 91) {
                keyWordArrayPop_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 92) {
                keyWordArraySize_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 93) {
                keyWordArrayInsert_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 94) {
                keyWordArrayRemove_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 95) {
                keyWordArrayIndexOf_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 96) {
                keyWordArrayDefinition_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 97) {
                keyWordArrayOfIntegersDefinition_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 98) {
                keyWordArrayOfStringsDefinition_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 99) {
                keyWordArrayOfFloatingPointNumbersDefinition_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 100) {
                keyWordArrayOfBooleansDefinition_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 101) {
                keyWordVar_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 102) {
                keyWordLet_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 103) {
                keyWordConst_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 104) {
                keyWordEnd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 105) {
                keyWordGlobal_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 106) {
                keyWordComment_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 107) {
                keyWordCommentOpenMultiLine_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 108) {
                keyWordCommentCloseMultiLine_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 109) {
                keyWordEscpaeChar_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 110) {
                keyWordMainLabel_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 111) {
                keyWordConcat_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 112) {
                keyWordAdd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 113) {
                keyWordSub_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 114) {
                keyWordMul_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 115) {
                keyWordDiv_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 116) {
                keyWordMod_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 117) {
                keyWordExp_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 118) {
                keyWordEqual_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 119) {
                keyWordStrictEqual_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 120) {
                keyWordNotEqual_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 121) {
                keyWordGreater_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 122) {
                keyWordLess_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 123) {
                keyWordGreaterEqual_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 124) {
                keyWordLessEqual_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 125) {
                keyWordAnd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 126) {
                keyWordOr_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 127) {
                keyWordNot_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 128) {
                keyWordBitAnd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 129) {
                keyWordBitOr_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 130) {
                keyWordBitXor_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 131) {
                keyWordBitNot_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 132) {
                keyWordShiftLeft_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 133) {
                keyWordShiftRight_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 134) {
                keyWordShiftUnsignedRight_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 135) {
                keyWordAssign_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 136) {
                keyWordAssignAdd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 137) {
                keyWordAssignConcat_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 138) {
                keyWordAssignSub_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 139) {
                keyWordAssignMul_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 140) {
                keyWordAssignDiv_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 141) {
                keyWordAssignMod_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 142) {
                keyWordAssignShiftLeft_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 143) {
                keyWordAssignShiftRight_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 144) {
                keyWordLogicalAssignShiftRight_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 145) {
                keyWordAssignBitAnd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 146) {
                keyWordAssignBitOr_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 147) {
                keyWordAssignBitXor_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 148) {
                keyWordTernary1_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 149) {
                keyWordTernary2_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 150) {
                keyWordInc_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 151) {
                keyWordDec_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 152) {
                AHKlikeLoopsIndexedAt_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 153) {
                keyWordAIndex_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 154) {
                keyWordALoopField_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 155) {
                useCurlyBraces_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 156) {
                useEnd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 157) {
                useSemicolon_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 158) {
                useParentheses_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 159) {
                usePrefixTypeForTypeDefinition_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 160) {
                usePostfixTypeForTypeDefinition_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 161) {
                usePythonicColonSyntax_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 162) {
                useCurlyBracesSyntaxForArrayDef_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 163) {
                useInJavaScriptAlwaysUseVar_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 164) {
                useJavaScriptInAfullHTMLfile_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 165) {
                useJavaScriptAmainFuncDef_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 166) {
                useJavaScriptAllFuncsAreAsync_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 167) {
                useJavaScriptAlwaysTripleEqual_2 = Trim(A_LoopField64);
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
    std::vector<std::string> items65 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index65 = 0; A_Index65 < items65.size() + 0; A_Index65++) {
        std::string A_LoopField65 = items65[A_Index65 - 0];
        if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEnd)) {
            COUNT_programmingBlock_InTheTranspiledLang++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(COUNT_programmingBlock_InTheTranspiledLang) + "AA\n";
            programmingBlock_InTheTranspiledLang.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndCPP)) {
            COUNT_programmingBlock_CPP++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(COUNT_programmingBlock_CPP) + "AA\n";
            programmingBlock_CPP.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndPY)) {
            COUNT_programmingBlock_PY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_PY-programmingBlock_PY-AA" + STR(COUNT_programmingBlock_PY) + "AA\n";
            programmingBlock_PY.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndJS)) {
            COUNT_programmingBlock_JS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JS-programmingBlock_JS-AA" + STR(COUNT_programmingBlock_JS) + "AA\n";
            programmingBlock_JS.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndGO)) {
            COUNT_programmingBlock_GO++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GO-programmingBlock_GO-AA" + STR(COUNT_programmingBlock_GO) + "AA\n";
            programmingBlock_GO.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndLUA)) {
            COUNT_programmingBlock_LUA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(COUNT_programmingBlock_LUA) + "AA\n";
            programmingBlock_LUA.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndCS)) {
            COUNT_programmingBlock_CS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CS-programmingBlock_CS-AA" + STR(COUNT_programmingBlock_CS) + "AA\n";
            programmingBlock_CS.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndJAVA)) {
            COUNT_programmingBlock_JAVA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(COUNT_programmingBlock_JAVA) + "AA\n";
            programmingBlock_JAVA.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndKT)) {
            COUNT_programmingBlock_KT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_KT-programmingBlock_KT-AA" + STR(COUNT_programmingBlock_KT) + "AA\n";
            programmingBlock_KT.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndRB)) {
            COUNT_programmingBlock_RB++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_RB-programmingBlock_RB-AA" + STR(COUNT_programmingBlock_RB) + "AA\n";
            programmingBlock_RB.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndNIM)) {
            COUNT_programmingBlock_NIM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(COUNT_programmingBlock_NIM) + "AA\n";
            programmingBlock_NIM.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndAHK)) {
            COUNT_programmingBlock_AHK++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(COUNT_programmingBlock_AHK) + "AA\n";
            programmingBlock_AHK.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndSWIFT)) {
            COUNT_programmingBlock_SWIFT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(COUNT_programmingBlock_SWIFT) + "AA\n";
            programmingBlock_SWIFT.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndDART)) {
            COUNT_programmingBlock_DART++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_DART-programmingBlock_DART-AA" + STR(COUNT_programmingBlock_DART) + "AA\n";
            programmingBlock_DART.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndTS)) {
            COUNT_programmingBlock_TS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_TS-programmingBlock_TS-AA" + STR(COUNT_programmingBlock_TS) + "AA\n";
            programmingBlock_TS.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndSCALA)) {
            COUNT_programmingBlock_SCALA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_SCALA-programmingBlock_SCALA-AA" + STR(COUNT_programmingBlock_SCALA) + "AA\n";
            programmingBlock_SCALA.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndGROOVY)) {
            COUNT_programmingBlock_GROOVY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(COUNT_programmingBlock_GROOVY) + "AA\n";
            programmingBlock_GROOVY.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangEndHTVM)) {
            COUNT_programmingBlock_HTVM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(COUNT_programmingBlock_HTVM) + "AA\n";
            programmingBlock_HTVM.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInHTVMend)) {
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
            holdTempDataProgrammingBlockThenPutInArr += A_LoopField65 + "\n";
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStart)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartCPP)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartPY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartJS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartGO)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartLUA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartCS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartJAVA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartKT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartRB)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartNIM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartAHK)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartSWIFT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartDART)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartTS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartSCALA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartGROOVY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInTheTranspiledLangStartHTVM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField65)) == StrLower(keyWordCodeInHTVMstart)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        } else {
            programmingBlocksTemp += A_LoopField65 + "\n";
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
    std::vector<std::string> theIdNumOfThe34theVar;
    std::string ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = "";
    std::vector<std::string> getAllCharForTheFurtureSoIcanAddEscapeChar;
    int removeNexFixkeyWordEscpaeChar = 0;
    if (isNotHTVMfile == 0) {
        print("============programmingBlock_CPP==================");
        print("============programmingBlock_CPP==================");
        if (programmingBlock_CPP.size() > 0) {
            for (int A_Index66 = 0; A_Index66 < programmingBlock_CPP.size() + 0; A_Index66++) {
                print(programmingBlock_CPP[A_Index66]);
            }
        }
        print("============programmingBlock_CPP==================");
        print("============programmingBlock_CPP==================");
        std::vector<std::string> items67 = LoopParseFunc(code);
        for (size_t A_Index67 = 0; A_Index67 < items67.size() + 0; A_Index67++) {
            std::string A_LoopField67 = items67[A_Index67 - 0];
            theIdNumOfThe34theVar.push_back("");
            theIdNumOfThe34theVar.push_back("");
        }
        std::vector<std::string> items68 = LoopParseFunc(code);
        for (size_t A_Index68 = 0; A_Index68 < items68.size() + 0; A_Index68++) {
            std::string A_LoopField68 = items68[A_Index68 - 0];
            theIdNumOfThe34theVar[A_Index68] = theIdNumOfThe34theVar[A_Index68] + Chr(34);
            getAllCharForTheFurtureSoIcanAddEscapeChar.push_back(A_LoopField68);
        }
        getAllCharForTheFurtureSoIcanAddEscapeChar.push_back(" ");
        ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuusgfgesrheidForQQQasdsasQQQtheuhtuwaesphoutr" + Chr(34);
        std::vector<std::string> items69 = LoopParseFunc(code);
        for (size_t A_Index69 = 0; A_Index69 < items69.size() + 0; A_Index69++) {
            std::string A_LoopField69 = items69[A_Index69 - 0];
            if (A_LoopField69 == keyWordEscpaeChar && getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index69 + 1] == Chr(34)) {
                fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1;
                OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes;
            } else {
                if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1) {
                    OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField69;
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
            std::vector<std::string> items70 = LoopParseFunc(code);
            for (size_t A_Index70 = 0; A_Index70 < items70.size() + 0; A_Index70++) {
                std::string A_LoopField70 = items70[A_Index70 - 0];
                if (A_LoopField70 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField70 != Chr(34)) {
                        if (A_LoopField70 == keyWordEscpaeChar) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField70;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidForQQQasdsasQQQtheuhturtyphoutrQQQ" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField70 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField70;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        } else {
            std::vector<std::string> items71 = LoopParseFunc(code);
            for (size_t A_Index71 = 0; A_Index71 < items71.size() + 0; A_Index71++) {
                std::string A_LoopField71 = items71[A_Index71 - 0];
                if (A_LoopField71 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField71 != Chr(34)) {
                        if (A_LoopField71 == keyWordEscpaeChar && keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index71 + 1]) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar;
                            removeNexFixkeyWordEscpaeChar = 1;
                        }
                        else if (A_LoopField71 == keyWordEscpaeChar) {
                            if (removeNexFixkeyWordEscpaeChar != 1) {
                                theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                            } else {
                                removeNexFixkeyWordEscpaeChar = 0;
                            }
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField71;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidForQQQasdsasQQQtheuhturtyphoutrQQQ" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField71 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField71;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        }
        code = htCodeOUT754754;
        for (int A_Index72 = 0; A_Index72 < theIdNumOfThe34 + 0; A_Index72++) {
            theIdNumOfThe34theVar[A_Index72] = theIdNumOfThe34theVar[A_Index72] + Chr(34);
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
        std::vector<std::string> items73 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index73 = 0; A_Index73 < items73.size() + 0; A_Index73++) {
            std::string A_LoopField73 = items73[A_Index73 - 0];
            // Define the original string
            originalStringForRemoveCommentsOnTheEndOfTheLine = A_LoopField73;
            // Find the position of the keyword in the original string
            posForRemoveCommentsOnTheEndOfTheLine = InStr(originalStringForRemoveCommentsOnTheEndOfTheLine, " " + keyWordComment);
            if (SubStr(Trim(A_LoopField73), 1, StrLen(keyWordComment)) != keyWordComment) {
                if (posForRemoveCommentsOnTheEndOfTheLine > 0) {
                    beforeKeywordForRemoveCommentsOnTheEndOfTheLine = A_LoopField73;
                    // Construct the new string with everything before the keyword
                    newStringOutCode += beforeKeywordForRemoveCommentsOnTheEndOfTheLine + "\n";
                } else {
                    newStringOutCode += A_LoopField73 + "\n";
                }
            } else {
                newStringOutCode += A_LoopField73 + "\n";
            }
        }
        code = StringTrimRight(newStringOutCode, 1);
        //MsgBox, % code
        if (useCurlyBraces == "on") {
            if (keyWordCurlyBraceOpen != "{") {
                std::vector<std::string> items74 = LoopParseFunc(code, "\n", "\r");
                for (size_t A_Index74 = 0; A_Index74 < items74.size() + 0; A_Index74++) {
                    std::string A_LoopField74 = items74[A_Index74 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField74)) == true || Trim(A_LoopField74) == keyWordCurlyBraceOpen) {
                        htCodeOutFixINT2 = 1;
                    }
                    htCodeOutFixINT = 0;
                    std::vector<std::string> items75 = LoopParseFunc(A_LoopField74, " ");
                    for (size_t A_Index75 = 0; A_Index75 < items75.size() + 0; A_Index75++) {
                        std::string A_LoopField75 = items75[A_Index75 - 0];
                        htCodeOutFixINT++;
                    }
                    htCodeOutFixINT--;
                    std::vector<std::string> items76 = LoopParseFunc(A_LoopField74, " ");
                    for (size_t A_Index76 = 0; A_Index76 < items76.size() + 0; A_Index76++) {
                        std::string A_LoopField76 = items76[A_Index76 - 0];
                        if (htCodeOutFixINT == A_Index76 && htCodeOutFixINT2 == 1) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField76, keyWordCurlyBraceOpen, "{") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField76 + " ";
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
                std::vector<std::string> items77 = LoopParseFunc(code, "\n", "\r");
                for (size_t A_Index77 = 0; A_Index77 < items77.size() + 0; A_Index77++) {
                    std::string A_LoopField77 = items77[A_Index77 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField77)) == true || Trim(A_LoopField77) == keyWordCurlyBraceClose) {
                        htCodeOutFixINT2 = 1;
                    }
                    std::vector<std::string> items78 = LoopParseFunc(A_LoopField77, " ");
                    for (size_t A_Index78 = 0; A_Index78 < items78.size() + 0; A_Index78++) {
                        std::string A_LoopField78 = items78[A_Index78 - 0];
                        if (htCodeOutFixINT2 == 1 || Trim(A_LoopField78) == keyWordCurlyBraceClose) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField78, keyWordCurlyBraceClose, "}") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField78 + " ";
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
            std::vector<std::string> items79 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index79 = 0; A_Index79 < items79.size() + 0; A_Index79++) {
                std::string A_LoopField79 = items79[A_Index79 - 0];
                if (StrLower(Trim(A_LoopField79)) == StrLower(keyWordEnd)) {
                    htCodeOutFixEnd += "}\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField79)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF) && isLineAconstruct(Trim(A_LoopField79)) == true) {
                    htCodeOutFixEnd += A_LoopField79 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField79)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf) && isLineAconstruct(Trim(A_LoopField79)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField79 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField79)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse) && isLineAconstruct(Trim(A_LoopField79)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField79 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField79)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch) && isLineAconstruct(Trim(A_LoopField79)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField79 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField79)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally) && isLineAconstruct(Trim(A_LoopField79)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField79 + "\n{\n";
                }
                else if (isLineAconstruct(Trim(A_LoopField79)) == true) {
                    htCodeOutFixEnd += A_LoopField79 + "\n{\n";
                } else {
                    htCodeOutFixEnd += A_LoopField79 + "\n";
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        if (usePythonicColonSyntax == "off") {
            if (useEnd == "off" && useCurlyBraces == "off") {
                htCodeOutFixEnd = "";
                std::vector<std::string> items80 = LoopParseFunc(code, "\n", "\r");
                for (size_t A_Index80 = 0; A_Index80 < items80.size() + 0; A_Index80++) {
                    std::string A_LoopField80 = items80[A_Index80 - 0];
                    if (isLineAconstruct(Trim(A_LoopField80)) == true) {
                        htCodeOutFixEnd += A_LoopField80 + ":\n";
                    } else {
                        htCodeOutFixEnd += A_LoopField80 + "\n";
                    }
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
        }
        if (useCurlyBraces == "off" && useEnd == "off") {
            code = AddCurlyBraces(code);
        }
        outTrimCode = "";
        std::vector<std::string> items81 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index81 = 0; A_Index81 < items81.size() + 0; A_Index81++) {
            std::string A_LoopField81 = items81[A_Index81 - 0];
            outTrimCode += Trim(A_LoopField81) + "\n";
        }
        code = StringTrimRight(outTrimCode, 1);
        // for converting c++ to js and py
        //code := StrReplace(code, "{}", "[]")
        std::string outCodeFixBraces = "";
        for (int A_Index82 = 0; A_Index82 < 2 + 0; A_Index82++) {
            outCodeFixBraces = "";
            std::vector<std::string> items83 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index83 = 0; A_Index83 < items83.size() + 0; A_Index83++) {
                std::string A_LoopField83 = items83[A_Index83 - 0];
                if (InStr(Trim(A_LoopField83), "{") && Trim(A_LoopField83) != "{") {
                    outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField83), "{", "")) + "\n{\n";
                }
                else if (InStr(Trim(A_LoopField83), "}") && Trim(A_LoopField83) != "}") {
                    outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField83), "}", "")) + "\n";
                } else {
                    outCodeFixBraces += Trim(A_LoopField83) + "\n";
                }
            }
            code = StringTrimRight(outCodeFixBraces, 1);
        }
        htCodeOutFixEnd = "";
        if (usePythonicColonSyntax == "on") {
            std::vector<std::string> items84 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index84 = 0; A_Index84 < items84.size() + 0; A_Index84++) {
                std::string A_LoopField84 = items84[A_Index84 - 0];
                if (isLineAconstruct(Trim(A_LoopField84)) == true) {
                    htCodeOutFixEnd += StringTrimRight(A_LoopField84, 1) + "\n";
                } else {
                    htCodeOutFixEnd += A_LoopField84 + "\n";
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
            std::vector<std::string> items85 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index85 = 0; A_Index85 < items85.size() + 0; A_Index85++) {
                std::string A_LoopField85 = items85[A_Index85 - 0];
                if (StrLower(A_LoopField85) == StrLower(keyWordMainLabel)) {
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
                    codeOutFixAndAddMainFunc += A_LoopField85 + "\n";
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
        }
        std::vector<std::string> items86 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index86 = 0; A_Index86 < items86.size() + 0; A_Index86++) {
            std::string A_LoopField86 = items86[A_Index86 - 0];
            lookIntoTheNextLineForFuncWhitNoKeyWord.push_back(A_LoopField86);
        }
        lookIntoTheNextLineForFuncWhitNoKeyWord.push_back(" ");
        htCode = "";
        print("=======UP==========");
        print(code);
        print("=======DOWN==========");
        std::vector<std::string> items87 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index87 = 0; A_Index87 < items87.size() + 0; A_Index87++) {
            std::string A_LoopField87 = items87[A_Index87 - 0];
            lineDone = 0;
            if (StrLower(A_LoopField87) == StrLower(keyWordLoopInfinite) || StrLower(A_LoopField87) == StrLower(keyWordLoopInfinite + ":")) {
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
            else if (SubStr(Trim(StrLower(A_LoopField87)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop) && SubStr(Trim(StrLower(A_LoopField87)), 1, StrLen(StrLower(keyWordLoop)) + 2) != StrLower(keyWordLoop) + "% " && SubStr(Trim(StrLower(A_LoopField87)), 1, StrLen(StrLower(keyWordLoopParse))) != StrLower(keyWordLoopParse)) {
                out2 = StringTrimLeft(A_LoopField87, StrLen(keyWordLoop));
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
            else if (SubStr(Trim(StrLower(A_LoopField87)), 1, StrLen(StrLower(keyWordLoop)) + 2) == StrLower(keyWordLoop) + "% ") {
                out2 = StringTrimLeft(A_LoopField87, StrLen(keyWordLoop) + 2);
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
            else if (SubStr(StrLower(A_LoopField87), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
                var1 = StringTrimLeft(A_LoopField87, StrLen(keyWordLoopParse));
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
            else if ((SubStr(Trim(A_LoopField87), -2) == ");" || SubStr(Trim(A_LoopField87), -1) == ")") && !(InStr(A_LoopField87, "int main(int argc, char* argv[])")) && !(InStr(A_LoopField87, "async function main()")) && lineDone == 0) {
                lineDone = 1;
                str1 = Trim(A_LoopField87);
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
                //print("else else else " . A_LoopField87)
                // this is THE else
                if (lineDone != 1) {
                    if (skipLeftCuleyForFuncPLS != 1) {
                        if (SubStr(Trim(StrLower(A_LoopField87)), 1, 1) == Chr(125)) {
                            htCode += Chr(125) + "\n";
                        } else {
                            if (htCodeAcurlyBraceAddSomeVrasFixLP == 1 && SubStr(Trim(StrLower(A_LoopField87)), 1, 1) == Chr(123)) {
                                htCodeAcurlyBraceAddSomeVrasFixLP = 0;
                                htCode += A_LoopField87 + "\n" + theFixTextLoopLP + "\n";
                            } else {
                                if (htCodeAcurlyBraceAddSomeVrasFixNL == 1 && SubStr(Trim(StrLower(A_LoopField87)), 1, 1) == Chr(123)) {
                                    htCodeAcurlyBraceAddSomeVrasFixNL = 0;
                                    htCode += A_LoopField87 + "\n" + theFixTextLoopNL + "\n";
                                } else {
                                    htCode += A_LoopField87 + "\n";
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
                std::vector<std::string> items88 = LoopParseFunc(htCodeLoopfixa, "\n", "\r");
                for (size_t A_Index88 = 0; A_Index88 < items88.size() + 0; A_Index88++) {
                    std::string A_LoopField88 = items88[A_Index88 - 0];
                    sstr123 = A_LoopField88;
                    fixLoopLokingFor = A_LoopField88;
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
                        std::vector<std::string> items89 = LoopParseFunc(htCode, "\n", "\r");
                        for (size_t A_Index89 = 0; A_Index89 < items89.size() + 0; A_Index89++) {
                            std::string A_LoopField89 = items89[A_Index89 - 0];
                            //MsgBox, dsfgsdefgesrdg1
                            //MsgBox, |%A_LoopField89%|`n|%fixLoopLokingFor%|
                            if (InStr(A_LoopField89, fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 1
                            }
                            if (SubStr(Trim(A_LoopField89), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField89 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(s);
                                //MsgBox, % out1z
                                //MsgBox, do we came here 2
                                fixLoopLokingForNum = 0;
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField89
                                dontSaveStr = 1;
                                ALoopField = A_LoopField89;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + "\n";
                            }
                            if (inTarget == 1 && InStr(A_LoopField89, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField89, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField89, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField89), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField89, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField89, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField89, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField89, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField89
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField89 + "\n";
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField89;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                                out4758686d86d86d86578991a += ALoopField + "\n";
                            }
                            if (inTarget == 1 && InStr(A_LoopField89, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1) {
                                //MsgBox, % A_LoopField89
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField89 + "\n";
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
                        std::vector<std::string> items90 = LoopParseFunc(htCode, "\n", "\r");
                        for (size_t A_Index90 = 0; A_Index90 < items90.size() + 0; A_Index90++) {
                            std::string A_LoopField90 = items90[A_Index90 - 0];
                            if (InStr(A_LoopField90 , fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 3
                            }
                            if (SubStr(Trim(A_LoopField90), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField90 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(s);
                                //MsgBox, % out1z
                                fixLoopLokingForNum = 0;
                                //MsgBox, do we came here 4
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField90
                                dontSaveStr = 1;
                                ALoopField = A_LoopField90;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + "\n";
                            }
                            if (inTarget == 1 && InStr(A_LoopField90, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField90, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField90, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField90), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField90, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField90, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField90, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField90, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField90
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField90 + "\n";
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField90;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordALoopField + "\\d*", "" + keyWordALoopField + "" + out1z);
                                out4758686d86d86d86578991a += ALoopField + "\n";
                            }
                            if ((inTarget == 1 && InStr(A_LoopField90, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1)) {
                                //MsgBox, % A_LoopField90
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField90 + "\n";
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
                std::vector<std::string> items91 = LoopParseFunc(htCode, "\n", "\r");
                for (size_t A_Index91 = 0; A_Index91 < items91.size() + 0; A_Index91++) {
                    std::string A_LoopField91 = items91[A_Index91 - 0];
                    ignore = 0;
                    if (SubStr(Trim(A_LoopField91), 1, 4) == "for ") {
                        if (hold == 1 && holdText == A_LoopField91) {
                            ignore = 1;
                        } else {
                            holdText = A_LoopField91;
                            hold = 1;
                        }
                    }
                    if (!ignore) {
                        out4758686d86dgt8r754444444 += A_LoopField91 + "\n";
                    }
                }
                out4758686d86dgt8r754444444 = StringTrimRight(out4758686d86dgt8r754444444, 1);
                htCode = out4758686d86dgt8r754444444;
            }
            htCodeOut1234565432 = "";
            std::vector<std::string> items92 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index92 = 0; A_Index92 < items92.size() + 0; A_Index92++) {
                std::string A_LoopField92 = items92[A_Index92 - 0];
                out = A_LoopField92;
                if (!InStr(out, "|itsaersdtgtgfergsdgfsegdfsedAA|")) {
                    htCodeOut1234565432 += out + "\n";
                }
            }
            htCode = StringTrimRight(htCodeOut1234565432, 1);
        }
    } else {
        htCode = code;
    }
    if (COUNT_programmingBlock_InTheTranspiledLang != 0) {
        for (int A_Index93 = 0; A_Index93 < COUNT_programmingBlock_InTheTranspiledLang + 0; A_Index93++) {
            htCode = StrReplace(htCode, "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(A_Index93 + 1) + "AA", programmingBlock_InTheTranspiledLang[A_Index93]);
        }
    }
    if (langToConvertTo == "cpp") {
        if (COUNT_programmingBlock_CPP != 0) {
            for (int A_Index94 = 0; A_Index94 < COUNT_programmingBlock_CPP + 0; A_Index94++) {
                htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index94 + 1) + "AA", programmingBlock_CPP[A_Index94]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CPP != 0) {
            for (int A_Index95 = 0; A_Index95 < COUNT_programmingBlock_CPP + 0; A_Index95++) {
                htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index95 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "py") {
        if (COUNT_programmingBlock_PY != 0) {
            for (int A_Index96 = 0; A_Index96 < COUNT_programmingBlock_PY + 0; A_Index96++) {
                htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index96 + 1) + "AA", programmingBlock_PY[A_Index96]);
            }
        }
    } else {
        if (COUNT_programmingBlock_PY != 0) {
            for (int A_Index97 = 0; A_Index97 < COUNT_programmingBlock_PY + 0; A_Index97++) {
                htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index97 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "js") {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index98 = 0; A_Index98 < COUNT_programmingBlock_JS + 0; A_Index98++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index98 + 1) + "AA", programmingBlock_JS[A_Index98]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index99 = 0; A_Index99 < COUNT_programmingBlock_JS + 0; A_Index99++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index99 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "go") {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index100 = 0; A_Index100 < COUNT_programmingBlock_GO + 0; A_Index100++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index100 + 1) + "AA", programmingBlock_GO[A_Index100]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index101 = 0; A_Index101 < COUNT_programmingBlock_GO + 0; A_Index101++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index101 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "lua") {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index102 = 0; A_Index102 < COUNT_programmingBlock_LUA + 0; A_Index102++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index102 + 1) + "AA", programmingBlock_LUA[A_Index102]);
            }
        }
    } else {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index103 = 0; A_Index103 < COUNT_programmingBlock_LUA + 0; A_Index103++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index103 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "cs") {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index104 = 0; A_Index104 < COUNT_programmingBlock_CS + 0; A_Index104++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index104 + 1) + "AA", programmingBlock_CS[A_Index104]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index105 = 0; A_Index105 < COUNT_programmingBlock_CS + 0; A_Index105++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index105 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "java") {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index106 = 0; A_Index106 < COUNT_programmingBlock_JAVA + 0; A_Index106++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index106 + 1) + "AA", programmingBlock_JAVA[A_Index106]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index107 = 0; A_Index107 < COUNT_programmingBlock_JAVA + 0; A_Index107++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index107 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "js") {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index108 = 0; A_Index108 < COUNT_programmingBlock_JS + 0; A_Index108++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index108 + 1) + "AA", programmingBlock_JS[A_Index108]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index109 = 0; A_Index109 < COUNT_programmingBlock_JS + 0; A_Index109++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index109 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "go") {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index110 = 0; A_Index110 < COUNT_programmingBlock_GO + 0; A_Index110++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index110 + 1) + "AA", programmingBlock_GO[A_Index110]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index111 = 0; A_Index111 < COUNT_programmingBlock_GO + 0; A_Index111++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index111 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "lua") {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index112 = 0; A_Index112 < COUNT_programmingBlock_LUA + 0; A_Index112++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index112 + 1) + "AA", programmingBlock_LUA[A_Index112]);
            }
        }
    } else {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index113 = 0; A_Index113 < COUNT_programmingBlock_LUA + 0; A_Index113++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index113 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "cs") {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index114 = 0; A_Index114 < COUNT_programmingBlock_CS + 0; A_Index114++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index114 + 1) + "AA", programmingBlock_CS[A_Index114]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index115 = 0; A_Index115 < COUNT_programmingBlock_CS + 0; A_Index115++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index115 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "java") {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index116 = 0; A_Index116 < COUNT_programmingBlock_JAVA + 0; A_Index116++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index116 + 1) + "AA", programmingBlock_JAVA[A_Index116]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index117 = 0; A_Index117 < COUNT_programmingBlock_JAVA + 0; A_Index117++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index117 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "ts") {
        if (COUNT_programmingBlock_TS != 0) {
            for (int A_Index118 = 0; A_Index118 < COUNT_programmingBlock_TS + 0; A_Index118++) {
                htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index118 + 1) + "AA", programmingBlock_TS[A_Index118]);
            }
        }
    } else {
        if (COUNT_programmingBlock_TS != 0) {
            for (int A_Index119 = 0; A_Index119 < COUNT_programmingBlock_TS + 0; A_Index119++) {
                htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index119 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "scala") {
        if (COUNT_programmingBlock_SCALA != 0) {
            for (int A_Index120 = 0; A_Index120 < COUNT_programmingBlock_SCALA + 0; A_Index120++) {
                htCode = StrReplace(htCode, "programmingBlock_SCALA-programmingBlock_SCALA-AA" + STR(A_Index120 + 1) + "AA", programmingBlock_SCALA[A_Index120]);
            }
        }
    } else {
        if (COUNT_programmingBlock_SCALA != 0) {
            for (int A_Index121 = 0; A_Index121 < COUNT_programmingBlock_SCALA + 0; A_Index121++) {
                htCode = StrReplace(htCode, "programmingBlock_SCALA-programmingBlock_SCALA-AA" + STR(A_Index121 + 1) + "AA", "\n");
            }
        }
    }
    if (langToConvertTo == "groovy") {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (int A_Index122 = 0; A_Index122 < COUNT_programmingBlock_GROOVY + 0; A_Index122++) {
                htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index122 + 1) + "AA", programmingBlock_GROOVY[A_Index122]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (int A_Index123 = 0; A_Index123 < COUNT_programmingBlock_GROOVY + 0; A_Index123++) {
                htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index123 + 1) + "AA", "\n");
            }
        }
    }
    //;;;;;;;;;;
    if (langToConvertTo == langFileExtension_2) {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (int A_Index124 = 0; A_Index124 < COUNT_programmingBlock_HTVM + 0; A_Index124++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index124 + 1) + "AA", programmingBlock_HTVM[A_Index124]);
            }
        }
    } else {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (int A_Index125 = 0; A_Index125 < COUNT_programmingBlock_HTVM + 0; A_Index125++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index125 + 1) + "AA", "\n");
            }
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    std::string ADD_ALL_programmingBlock_HTVMsyntax = "";
    if (COUNT_programmingBlock_HTVMsyntax != 0) {
        isNotHTVMfileEXTRA_INT = 1;
        for (int A_Index126 = 0; A_Index126 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index126++) {
            ADD_ALL_programmingBlock_HTVMsyntax += programmingBlock_HTVMsyntax[A_Index126] + "\n";
        }
        ADD_ALL_programmingBlock_HTVMsyntax = StringTrimRight(ADD_ALL_programmingBlock_HTVMsyntax, 1);
        ADD_ALL_programmingBlock_HTVMsyntax = compiler(ADD_ALL_programmingBlock_HTVMsyntax, allInstructionFile, "full", langToConvertToParam);
        isNotHTVMfileEXTRA_INT = 0;
        isNotHTVMfile2 = 1;
        for (int A_Index127 = 0; A_Index127 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index127++) {
            htCode = StrReplace(htCode, "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(A_Index127 + 1) + "AA", compiler(programmingBlock_HTVMsyntax[A_Index127], allInstructionFile, "full", langToConvertToParam));
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
        print("\n" + isNotHTVMfileEXTRA_LIB_INFO + "\n");
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
        print("\n" + isNotHTVMfileEXTRA_FUNCS_INFO + "\n");
        print("\n");
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
    if (langToConvertTo == langFileExtension_2) {
        if (useCurlyBraces_2 == "off" && useEnd_2 == "off") {
            htCode = indent_nested_curly_braces(htCode, 0);
        } else {
            htCode = indent_nested_curly_braces(htCode, 1);
        }
        if (useEnd_2 == "on") {
            std::vector<std::string> items128 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index128 = 0; A_Index128 < items128.size() + 0; A_Index128++) {
                std::string A_LoopField128 = items128[A_Index128 - 0];
                if (Trim(A_LoopField128) == keyWordCurlyBraceClose_2) {
                    fixLuaAndRuby += StrReplace(A_LoopField128, keyWordCurlyBraceClose_2, Trim(keyWordEnd_2)) + "\n";
                }
                else if (SubStrLastChars(A_LoopField128, 2) == " " + keyWordCurlyBraceOpen_2) {
                    fixLuaAndRuby += StringTrimRight(A_LoopField128, 2) + "\n";
                } else {
                    fixLuaAndRuby += A_LoopField128 + "\n";
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
            std::vector<std::string> items129 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index129 = 0; A_Index129 < items129.size() + 0; A_Index129++) {
                std::string A_LoopField129 = items129[A_Index129 - 0];
                if (Trim(A_LoopField129) == "}") {
                    fixLuaAndRuby += StrReplace(A_LoopField129, "}", "end") + "\n";
                }
                else if (SubStrLastChars(A_LoopField129, 2) == " {") {
                    fixLuaAndRuby += StringTrimRight(A_LoopField129, 2) + "\n";
                } else {
                    fixLuaAndRuby += A_LoopField129 + "\n";
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
    std::vector<std::string> items130 = LoopParseFunc(instructions, "\n", "\r");
    for (size_t A_Index130 = 0; A_Index130 < items130.size() + 0; A_Index130++) {
        std::string A_LoopField130 = items130[A_Index130 - 0];
        if (Trim(A_LoopField130) == "funcEND======================funcEND==============") {
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
                funcLangHolder = StringTrimLeft(A_LoopField130, 5);
                if (Trim(funcLangHolder) == langToConvertTo) {
                    allFuncLang.push_back(Trim(funcLangHolder));
                    correctLang = 1;
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 2) {
                // name of the func
                funcNameHolder = StringTrimLeft(A_LoopField130, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allFuncNames.push_back(Trim(funcNameHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 3) {
                // all libs
                funcLibsHolder = StringTrimLeft(A_LoopField130, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allFuncLibs.push_back(Trim(funcLibsHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 4) {
                // func description
                funcDescriptionHolder = StringTrimLeft(A_LoopField130, 12);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allfuncDescription.push_back(Trim(funcDescriptionHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum >= 5) {
                // the full func
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    funcFuncHolder += A_LoopField130 + "\n";
                }
            }
            //MsgBox, % A_LoopField130
            areWeInAFuncFromInstructionsLineNum++;
        }
        if (Trim(A_LoopField130) == "func======================func==============") {
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
    }
    std::string jsHTMLdownCode = "</script>\n</body>\n</html>";
    int includeLibsInCppIf = 0;
    std::string allFuncsToPutAtTop = "\n";
    std::string allLibsToPutAtTop;
    if (!(allFuncNames.size() <= 0)) {
        for (int A_Index131 = 0; A_Index131 < allFuncNames.size() + 0; A_Index131++) {
            if (InStr(htCode, allFuncNames[A_Index131]) + "(") {
                //MsgBox, % allFuncNames[A_Index131]
                allFuncsToPutAtTop += allFuncs[A_Index131] + "\n";
                if (Trim(allFuncLibs[A_Index131]) != "null") {
                    allLibsToPutAtTop += allFuncLibs[A_Index131] + "|";
                }
            }
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTop, 1);
        std::string allLibsToPutAtTopTEMP;
        std::vector<std::string> items132 = LoopParseFunc(allLibsToPutAtTop, "|");
        for (size_t A_Index132 = 0; A_Index132 < items132.size() + 0; A_Index132++) {
            std::string A_LoopField132 = items132[A_Index132 - 0];
            allLibsToPutAtTopTEMP += A_LoopField132 + "\n";
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
        if (isNotHTVMfileEXTRA_INT == 1) {
            isNotHTVMfileEXTRA_LIB_INFO = allLibsToPutAtTop;
            isNotHTVMfileEXTRA_FUNCS_INFO = allFuncsToPutAtTop;
        }
        if (isNotHTVMfile2 == 0) {
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
    }
    for (int A_Index133 = 0; A_Index133 < theIdNumOfThe34 + 0; A_Index133++) {
        if (theIdNumOfThe34 == A_Index133 + 1) {
            if (langToConvertTo == langFileExtension_2) {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidForQQQasdsasQQQtheuhturtyphoutrQQQ" + Chr(65) + Chr(65) + STR(A_Index133 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index133 + 1], "\\", keyWordEscpaeChar_2) + Chr(34));
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidForQQQasdsasQQQtheuhturtyphoutrQQQ" + Chr(65) + Chr(65) + STR(A_Index133 + 1) + Chr(65) + Chr(65), theIdNumOfThe34theVar[A_Index133 + 1] + Chr(34));
            }
        } else {
            if (langToConvertTo == langFileExtension_2) {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidForQQQasdsasQQQtheuhturtyphoutrQQQ" + Chr(65) + Chr(65) + STR(A_Index133 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index133 + 1], "\\", keyWordEscpaeChar_2));
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidForQQQasdsasQQQtheuhturtyphoutrQQQ" + Chr(65) + Chr(65) + STR(A_Index133 + 1) + Chr(65) + Chr(65), theIdNumOfThe34theVar[A_Index133 + 1]);
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
    if (isNotHTVMfile2 == 0) {
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
    std::vector<std::string> items134 = LoopParseFunc(str0);
    for (size_t A_Index134 = 0; A_Index134 < items134.size() + 0; A_Index134++) {
        std::string A_LoopField134 = items134[A_Index134 - 0];
        str00 = Trim(A_LoopField134);
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
        std::vector<std::string> items135 = LoopParseFunc(allArgs, "\n", "\r");
        for (size_t A_Index135 = 0; A_Index135 < items135.size() + 0; A_Index135++) {
            std::string A_LoopField135 = items135[A_Index135 - 0];
            if (A_Index135 == 0) {
                numOfParams++;
                argCODE = FileRead(Trim(A_LoopField135));
                argCODEfile = Trim(A_LoopField135);
            }
            else if (A_Index135 == 1) {
                numOfParams++;
                argHTVMinstr = Trim(A_LoopField135);
            }
            else if (A_Index135 == 2) {
                numOfParams++;
                argLangTo = Trim(A_LoopField135);
            } else {
                numOfParams++;
                argHTVMinstrMORE.push_back(Trim(A_LoopField135));
            }
        }
        print("===============123431234===========start=====");
        for (int A_Index136 = 0; A_Index136 < argHTVMinstrMORE.size() + 0; A_Index136++) {
            print(argHTVMinstrMORE[A_Index136]);
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