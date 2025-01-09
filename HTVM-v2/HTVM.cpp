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
std::vector<std::string> argHTVMinstrMOVE;
std::string extraCodeReturned = "";
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
std::string keyWordAllianceEndExtraInfo = "";
std::string keyWordCrewEndExtraInfo = "";
std::string keyWordMethodEndExtraInfo = "";
std::string keyWordDefObjEndExtraInfo = "";
std::string keyWordIFEndExtraInfo = "";
std::string keyWordElseIfEndExtraInfo = "";
std::string keyWordElseEndExtraInfo = "";
std::string keyWordSwitchEndExtraInfo = "";
std::string keyWordSwitchCaseEndExtraInfo = "";
std::string keyWordSwitchDefaultEndExtraInfo = "";
std::string keyWordWhileLoopEndExtraInfo = "";
std::string keyWordForLoopEndExtraInfo = "";
std::string keyWordLoopInfiniteEndExtraInfo = "";
std::string keyWordLoopEndExtraInfo = "";
std::string keyWordLoopParseEndExtraInfo = "";
std::string keyWordFuncEndExtraInfo = "";
std::string keyWordTryEndExtraInfo = "";
std::string keyWordCatchEndExtraInfo = "";
std::string keyWordFinallyEndExtraInfo = "";
std::string useFuncKeyWord = "";
std::string useCurlyBraces = "";
std::string useEnd = "";
std::string useEndExtraInfo = "";
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
                resultOut += A_LoopField29 + " {\n";
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
            if (langToConvertTo != "lua" && langToConvertTo != "rb") {
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
                            addSpacesAtTheBegginig += A_LoopField32;
                        }
                    }
                    resultOut += addSpacesAtTheBegginig + "} else {\n";
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
    std::vector<std::string> items34 = LoopParseFunc(fullARRAYstr, "|");
    for (size_t A_Index34 = 0; A_Index34 < items34.size() + 0; A_Index34++) {
        std::string A_LoopField34 = items34[A_Index34 - 0];
        if (Trim(A_LoopField34) != "") {
            outFormatHELP1 = StrSplit(A_LoopField34, ":", 1);
            outFormatHELP2 = StrSplit(A_LoopField34, ":", 2);
            std::vector<std::string> items35 = LoopParseFunc(outFormatHELP2, ",");
            for (size_t A_Index35 = 0; A_Index35 < items35.size() + 0; A_Index35++) {
                std::string A_LoopField35 = items35[A_Index35 - 0];
                outFormat += outFormatHELP1 + "." + A_LoopField35 + "|";
            }
        }
    }
    outFormat = StringTrimRight(outFormat, 1);
    std::vector<std::string> items36 = LoopParseFunc(outFormat, "|");
    for (size_t A_Index36 = 0; A_Index36 < items36.size() + 0; A_Index36++) {
        std::string A_LoopField36 = items36[A_Index36 - 0];
        if (Trim(A_LoopField36) != "") {
            if (StrSplit(Trim(A_LoopField36), "[", 1) == Trim(FromPath)) {
                outType = StrSplit(Trim(A_LoopField36), "[", 2);
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
    std::vector<std::string> items37 = LoopParseFunc(THESTR, ".");
    for (size_t A_Index37 = 0; A_Index37 < items37.size() + 0; A_Index37++) {
        std::string A_LoopField37 = items37[A_Index37 - 0];
        count12345++;
    }
    std::vector<std::string> items38 = LoopParseFunc(THESTR, ".");
    for (size_t A_Index38 = 0; A_Index38 < items38.size() + 0; A_Index38++) {
        std::string A_LoopField38 = items38[A_Index38 - 0];
        if (count12345 == A_Index38) {
            break;
        } else {
            THESTRout += Trim(A_LoopField38) + ".";
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
    std::vector<std::string> items39 = LoopParseFunc(theSringOSPlineARRAYstrstrSTR, "|");
    for (size_t A_Index39 = 0; A_Index39 < items39.size() + 0; A_Index39++) {
        std::string A_LoopField39 = items39[A_Index39 - 0];
        if (Trim(StrSplit(A_LoopField39, ":", 1)) == Trim(ALoopField)) {
            return STR(A_Index39);
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
    std::vector<std::string> items40 = LoopParseFunc(theSringOSPline, "|");
    for (size_t A_Index40 = 0; A_Index40 < items40.size() + 0; A_Index40++) {
        std::string A_LoopField40 = items40[A_Index40 - 0];
        str_1 += Trim(StrSplit(A_LoopField40, ":", 1)) + "\n";
        str_5 = Trim(StrSplit(A_LoopField40, ":", 1));
        str_6 = Trim(StrSplit(A_LoopField40, ":", 2));
        std::vector<std::string> items41 = LoopParseFunc(str_6, ",");
        for (size_t A_Index41 = 0; A_Index41 < items41.size() + 0; A_Index41++) {
            std::string A_LoopField41 = items41[A_Index41 - 0];
            str_1 += str_5 + "." + Trim(StrSplit(A_LoopField41, "[", 1)) + "[" + STR(A_Index41) + "]\n";
        }
    }
    str_1 += StrReplace(HELPHoldOSPdethodNamePath, "|", "\n");
    std::string shortestLine = "";
    std::string currentLine = "";
    int currentLength = 0;
    int minLength = 0;
    std::string tempStr = "";
    // Sorting by repeatedly finding and appending the shortest line
    for (int A_Index42 = 0; ; A_Index42++) {
        // Initialize variables to track the shortest line in this pass
        shortestLine = "";
        minLength = 999999;
        // Find the shortest line in str_1
        std::vector<std::string> items43 = LoopParseFunc(str_1, "\n", "\r");
        for (size_t A_Index43 = 0; A_Index43 < items43.size() + 0; A_Index43++) {
            std::string A_LoopField43 = items43[A_Index43 - 0];
            currentLine = A_LoopField43;
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
        std::vector<std::string> items44 = LoopParseFunc(str_1, "\n", "\r");
        for (size_t A_Index44 = 0; A_Index44 < items44.size() + 0; A_Index44++) {
            std::string A_LoopField44 = items44[A_Index44 - 0];
            if (A_LoopField44 != shortestLine) {
                tempStr += A_LoopField44 + "\n";
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
    std::vector<std::string> items45 = LoopParseFunc(str_2, "\n", "\r");
    for (size_t A_Index45 = 0; A_Index45 < items45.size() + 0; A_Index45++) {
        std::string A_LoopField45 = items45[A_Index45 - 0];
        lineCount++;
    }
    // Reverse the order by re-parsing and appending lines in reverse order
    for (int A_Index46 = 0; A_Index46 < lineCount + 0; A_Index46++) {
        // Inner loop to find the (lineCount - A_Index46 + 1)-th line
        index = lineCount - A_Index46 + 1;
        currentLine = "";
        lineNum = 0;
        std::vector<std::string> items47 = LoopParseFunc(str_2, "\n", "\r");
        for (size_t A_Index47 = 0; A_Index47 < items47.size() + 0; A_Index47++) {
            std::string A_LoopField47 = items47[A_Index47 - 0];
            lineNum++;
            if (lineNum == index) {
                currentLine = A_LoopField47;
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
    std::vector<std::string> items48 = LoopParseFunc(str_2, "\n", "\r");
    for (size_t A_Index48 = 0; A_Index48 < items48.size() + 0; A_Index48++) {
        std::string A_LoopField48 = items48[A_Index48 - 0];
        if (SubStr(A_LoopField48, 1, StrLen(keyWordFunc)) != keyWordFunc) {
            if (langToConvertTo == "cpp") {
                if (Trim(A_LoopField48) != "") {
                    if (InStr(str123, " += ")) {
                        str6 = " += ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48));
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48));
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48));
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48));
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    } else {
                        str123 = replaceTheOSPpathsRIGHT(str123, A_LoopField48);
                    }
                    //;;;;
                }
            } else {
                if (Trim(A_LoopField48) != "") {
                    str123 = replaceTheOSPpathsPY_JS(str123, A_LoopField48);
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
    std::vector<std::string> items49 = LoopParseFunc(allInstructionFile, "\n", "\r");
    for (size_t A_Index49 = 0; A_Index49 < items49.size() + 0; A_Index49++) {
        std::string A_LoopField49 = items49[A_Index49 - 0];
        if (A_Index49 == 0) {
            langToConvertTo = Trim(A_LoopField49);
        }
        if (A_Index49 == 1) {
            langFileExtension = Trim(A_LoopField49);
        }
        if (A_Index49 == 2) {
            commands = Trim(A_LoopField49);
        }
        if (A_Index49 == 3) {
            keyWordAlliance = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 4) {
            keyWordCrew = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 5) {
            keyWordMethod = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 6) {
            keyWordDefObj = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 7) {
            keyWordPorp = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 8) {
            keyWordThis = Trim(A_LoopField49);
        }
        if (A_Index49 == 9) {
            keyWordInclude = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 10) {
            keyWordIncludeInTheTranspiledLang = Trim(A_LoopField49);
        }
        if (A_Index49 == 11) {
            keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField49);
        }
        if (A_Index49 == 12) {
            keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField49);
        }
        if (A_Index49 == 13) {
            keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField49);
        }
        if (A_Index49 == 14) {
            keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField49);
        }
        if (A_Index49 == 15) {
            keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField49);
        }
        if (A_Index49 == 16) {
            keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField49);
        }
        if (A_Index49 == 17) {
            keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField49);
        }
        if (A_Index49 == 18) {
            keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField49);
        }
        if (A_Index49 == 19) {
            keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField49);
        }
        if (A_Index49 == 20) {
            keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField49);
        }
        if (A_Index49 == 21) {
            keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField49);
        }
        if (A_Index49 == 22) {
            keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField49);
        }
        if (A_Index49 == 23) {
            keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField49);
        }
        if (A_Index49 == 24) {
            keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField49);
        }
        if (A_Index49 == 25) {
            keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField49);
        }
        if (A_Index49 == 26) {
            keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField49);
        }
        if (A_Index49 == 27) {
            keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField49);
        }
        if (A_Index49 == 28) {
            keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField49);
        }
        if (A_Index49 == 29) {
            keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField49);
        }
        if (A_Index49 == 30) {
            keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField49);
        }
        if (A_Index49 == 31) {
            keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField49);
        }
        if (A_Index49 == 32) {
            keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField49);
        }
        if (A_Index49 == 33) {
            keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField49);
        }
        if (A_Index49 == 34) {
            keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField49);
        }
        if (A_Index49 == 35) {
            keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField49);
        }
        if (A_Index49 == 36) {
            keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField49);
        }
        if (A_Index49 == 37) {
            keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField49);
        }
        if (A_Index49 == 38) {
            keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField49);
        }
        if (A_Index49 == 39) {
            keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField49);
        }
        if (A_Index49 == 40) {
            keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField49);
        }
        if (A_Index49 == 41) {
            keyWordCodeInTheTranspiledLangStartSCALA = Trim(A_LoopField49);
        }
        if (A_Index49 == 42) {
            keyWordCodeInTheTranspiledLangEndSCALA = Trim(A_LoopField49);
        }
        if (A_Index49 == 43) {
            keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField49);
        }
        if (A_Index49 == 44) {
            keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField49);
        }
        if (A_Index49 == 45) {
            keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField49);
        }
        if (A_Index49 == 46) {
            keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField49);
        }
        if (A_Index49 == 47) {
            keyWordCodeInHTVMstart = Trim(A_LoopField49);
        }
        if (A_Index49 == 48) {
            keyWordCodeInHTVMend = Trim(A_LoopField49);
        }
        if (A_Index49 == 49) {
            keyWordCodeInOtherHTVMsyntaxStart = Trim(A_LoopField49);
        }
        if (A_Index49 == 50) {
            keyWordCodeInOtherHTVMsyntaxStart = Trim(A_LoopField49);
        }
        if (A_Index49 == 51) {
            keyWordCurlyBraceOpen = Trim(A_LoopField49);
        }
        if (A_Index49 == 52) {
            keyWordCurlyBraceClose = Trim(A_LoopField49);
        }
        if (A_Index49 == 53) {
            keyWordNull = Trim(A_LoopField49);
        }
        if (A_Index49 == 54) {
            keyWordTrue = Trim(A_LoopField49);
        }
        if (A_Index49 == 55) {
            keyWordFalse = Trim(A_LoopField49);
        }
        if (A_Index49 == 56) {
            keyWordVoid = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 57) {
            keyWordDouble = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 58) {
            keyWordChar = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 59) {
            keyWordUint8 = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 60) {
            keyWordUint16 = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 61) {
            keyWordUint32 = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 62) {
            keyWordUint64 = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 63) {
            keyWordINT = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 64) {
            keyWordSTR = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 65) {
            keyWordBOOL = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 66) {
            keyWordFLOAT = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 67) {
            keyWordINT8 = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 68) {
            keyWordINT16 = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 69) {
            keyWordINT32 = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 70) {
            keyWordINT64 = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 71) {
            keyWordIF = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 72) {
            keyWordElseIf = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 73) {
            keyWordElse = Trim(A_LoopField49);
        }
        if (A_Index49 == 74) {
            keyWordSwitch = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 75) {
            keyWordSwitchCase = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 76) {
            keyWordSwitchDefault = Trim(A_LoopField49);
        }
        if (A_Index49 == 77) {
            keyWordWhileLoop = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 78) {
            keyWordLoopInfinite = Trim(A_LoopField49);
        }
        if (A_Index49 == 79) {
            keyWordLoop = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 80) {
            keyWordLoopParse = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 81) {
            keyWordContinue = Trim(A_LoopField49);
        }
        if (A_Index49 == 82) {
            keyWordBreak = Trim(A_LoopField49);
        }
        if (A_Index49 == 83) {
            keyWordFunc = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 84) {
            keyWordAwait = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 85) {
            keyWordAsync = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 86) {
            keyWordThrow = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 87) {
            keyWordErrorMsg = Trim(A_LoopField49);
        }
        if (A_Index49 == 88) {
            keyWordTry = Trim(A_LoopField49);
        }
        if (A_Index49 == 89) {
            keyWordCatch = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 90) {
            keyWordFinally = Trim(A_LoopField49);
        }
        if (A_Index49 == 91) {
            keyWordReturnStatement = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 92) {
            keyWordArrayAppend = Trim(A_LoopField49);
        }
        if (A_Index49 == 93) {
            keyWordArrayPop = Trim(A_LoopField49);
        }
        if (A_Index49 == 94) {
            keyWordArraySize = Trim(A_LoopField49);
        }
        if (A_Index49 == 95) {
            keyWordArrayInsert = Trim(A_LoopField49);
        }
        if (A_Index49 == 96) {
            keyWordArrayRemove = Trim(A_LoopField49);
        }
        if (A_Index49 == 97) {
            keyWordArrayIndexOf = Trim(A_LoopField49);
        }
        if (A_Index49 == 98) {
            keyWordArrayDefinition = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 99) {
            keyWordArrayOfIntegersDefinition = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 100) {
            keyWordArrayOfStringsDefinition = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 101) {
            keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 102) {
            keyWordArrayOfBooleansDefinition = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 103) {
            keyWordVar = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 104) {
            keyWordLet = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 105) {
            keyWordConst = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 106) {
            keyWordEnd = Trim(A_LoopField49);
        }
        if (A_Index49 == 107) {
            keyWordGlobal = Trim(A_LoopField49) + " ";
        }
        if (A_Index49 == 108) {
            keyWordComment = Trim(A_LoopField49);
        }
        if (A_Index49 == 109) {
            keyWordCommentOpenMultiLine = Trim(A_LoopField49);
        }
        if (A_Index49 == 110) {
            keyWordCommentCloseMultiLine = Trim(A_LoopField49);
        }
        if (A_Index49 == 111) {
            keyWordEscpaeChar = Trim(A_LoopField49);
        }
        if (A_Index49 == 112) {
            keyWordMainLabel = Trim(A_LoopField49);
        }
        if (A_Index49 == 113) {
            keyWordConcat = Trim(A_LoopField49);
        }
        if (A_Index49 == 114) {
            keyWordAdd = Trim(A_LoopField49);
        }
        if (A_Index49 == 115) {
            keyWordSub = Trim(A_LoopField49);
        }
        if (A_Index49 == 116) {
            keyWordMul = Trim(A_LoopField49);
        }
        if (A_Index49 == 117) {
            keyWordDiv = Trim(A_LoopField49);
        }
        if (A_Index49 == 118) {
            keyWordMod = Trim(A_LoopField49);
        }
        if (A_Index49 == 119) {
            keyWordExp = Trim(A_LoopField49);
        }
        if (A_Index49 == 120) {
            keyWordEqual = Trim(A_LoopField49);
        }
        if (A_Index49 == 121) {
            keyWordStrictEqual = Trim(A_LoopField49);
        }
        if (A_Index49 == 122) {
            keyWordNotEqual = Trim(A_LoopField49);
        }
        if (A_Index49 == 123) {
            keyWordGreater = Trim(A_LoopField49);
        }
        if (A_Index49 == 124) {
            keyWordLess = Trim(A_LoopField49);
        }
        if (A_Index49 == 125) {
            keyWordGreaterEqual = Trim(A_LoopField49);
        }
        if (A_Index49 == 126) {
            keyWordLessEqual = Trim(A_LoopField49);
        }
        if (A_Index49 == 127) {
            keyWordAnd = Trim(A_LoopField49);
        }
        if (A_Index49 == 128) {
            keyWordOr = Trim(A_LoopField49);
        }
        if (A_Index49 == 129) {
            keyWordNot = Trim(A_LoopField49);
        }
        if (A_Index49 == 130) {
            keyWordBitAnd = Trim(A_LoopField49);
        }
        if (A_Index49 == 131) {
            keyWordBitOr = Trim(A_LoopField49);
        }
        if (A_Index49 == 132) {
            keyWordBitXor = Trim(A_LoopField49);
        }
        if (A_Index49 == 133) {
            keyWordBitNot = Trim(A_LoopField49);
        }
        if (A_Index49 == 134) {
            keyWordShiftLeft = Trim(A_LoopField49);
        }
        if (A_Index49 == 135) {
            keyWordShiftRight = Trim(A_LoopField49);
        }
        if (A_Index49 == 136) {
            keyWordShiftUnsignedRight = Trim(A_LoopField49);
        }
        if (A_Index49 == 137) {
            keyWordAssign = Trim(A_LoopField49);
        }
        if (A_Index49 == 138) {
            keyWordAssignAdd = Trim(A_LoopField49);
        }
        if (A_Index49 == 139) {
            keyWordAssignConcat = Trim(A_LoopField49);
        }
        if (A_Index49 == 140) {
            keyWordAssignSub = Trim(A_LoopField49);
        }
        if (A_Index49 == 141) {
            keyWordAssignMul = Trim(A_LoopField49);
        }
        if (A_Index49 == 142) {
            keyWordAssignDiv = Trim(A_LoopField49);
        }
        if (A_Index49 == 143) {
            keyWordAssignMod = Trim(A_LoopField49);
        }
        if (A_Index49 == 144) {
            keyWordAssignShiftLeft = Trim(A_LoopField49);
        }
        if (A_Index49 == 145) {
            keyWordAssignShiftRight = Trim(A_LoopField49);
        }
        if (A_Index49 == 146) {
            keyWordLogicalAssignShiftRight = Trim(A_LoopField49);
        }
        if (A_Index49 == 147) {
            keyWordAssignBitAnd = Trim(A_LoopField49);
        }
        if (A_Index49 == 148) {
            keyWordAssignBitOr = Trim(A_LoopField49);
        }
        if (A_Index49 == 149) {
            keyWordAssignBitXor = Trim(A_LoopField49);
        }
        if (A_Index49 == 150) {
            keyWordTernary1 = Trim(A_LoopField49);
        }
        if (A_Index49 == 151) {
            keyWordTernary2 = Trim(A_LoopField49);
        }
        if (A_Index49 == 152) {
            keyWordInc = Trim(A_LoopField49);
        }
        if (A_Index49 == 153) {
            keyWordDec = Trim(A_LoopField49);
        }
        if (A_Index49 == 154) {
            AHKlikeLoopsIndexedAt = Trim(A_LoopField49);
        }
        if (A_Index49 == 155) {
            keyWordAIndex = Trim(A_LoopField49);
        }
        if (A_Index49 == 156) {
            keyWordALoopField = Trim(A_LoopField49);
        }
        if (A_Index49 == 157) {
            keyWordAllianceEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 158) {
            keyWordCrewEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 159) {
            keyWordMethodEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 160) {
            keyWordDefObjEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 161) {
            keyWordIFEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 162) {
            keyWordElseIfEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 163) {
            keyWordElseEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 164) {
            keyWordSwitchEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 165) {
            keyWordSwitchCaseEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 166) {
            keyWordSwitchDefaultEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 167) {
            keyWordWhileLoopEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 168) {
            keyWordForLoopEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 169) {
            keyWordLoopInfiniteEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 170) {
            keyWordLoopEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 171) {
            keyWordLoopParseEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 172) {
            keyWordFuncEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 173) {
            keyWordTryEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 174) {
            keyWordCatchEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 175) {
            keyWordFinallyEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 176) {
            useCurlyBraces = Trim(A_LoopField49);
        }
        if (A_Index49 == 177) {
            useEnd = Trim(A_LoopField49);
        }
        if (A_Index49 == 178) {
            useEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 179) {
            useSemicolon = Trim(A_LoopField49);
        }
        if (A_Index49 == 180) {
            useParentheses = Trim(A_LoopField49);
        }
        if (A_Index49 == 181) {
            usePrefixTypeForTypeDefinition = Trim(A_LoopField49);
        }
        if (A_Index49 == 182) {
            usePostfixTypeForTypeDefinition = Trim(A_LoopField49);
        }
        if (A_Index49 == 183) {
            usePythonicColonSyntax = Trim(A_LoopField49);
        }
        if (A_Index49 == 184) {
            useCurlyBracesSyntaxForArrayDef = Trim(A_LoopField49);
        }
        if (A_Index49 == 185) {
            useInJavaScriptAlwaysUseVar = Trim(A_LoopField49);
        }
        if (A_Index49 == 186) {
            useJavaScriptInAfullHTMLfile = Trim(A_LoopField49);
        }
        if (A_Index49 == 187) {
            useJavaScriptAmainFuncDef = Trim(A_LoopField49);
        }
        if (A_Index49 == 188) {
            useJavaScriptAllFuncsAreAsync = Trim(A_LoopField49);
        }
        if (A_Index49 == 189) {
            useJavaScriptAlwaysTripleEqual = Trim(A_LoopField49);
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
    std::string htCodeOUT754754 = "";
    int areWEinSome34sNum = 0;
    int theIdNumOfThe34 = 0;
    std::vector<std::string> theIdNumOfThe34theVar;
    std::string ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = "";
    std::vector<std::string> getAllCharForTheFurtureSoIcanAddEscapeChar;
    int removeNexFixkeyWordEscpaeChar = 0;
    std::vector<std::string> items50 = LoopParseFunc(code);
    for (size_t A_Index50 = 0; A_Index50 < items50.size() + 0; A_Index50++) {
        std::string A_LoopField50 = items50[A_Index50 - 0];
        theIdNumOfThe34theVar.push_back("");
        theIdNumOfThe34theVar.push_back("");
    }
    std::vector<std::string> items51 = LoopParseFunc(code);
    for (size_t A_Index51 = 0; A_Index51 < items51.size() + 0; A_Index51++) {
        std::string A_LoopField51 = items51[A_Index51 - 0];
        theIdNumOfThe34theVar[A_Index51] = theIdNumOfThe34theVar[A_Index51] + Chr(34);
        getAllCharForTheFurtureSoIcanAddEscapeChar.push_back(A_LoopField51);
    }
    getAllCharForTheFurtureSoIcanAddEscapeChar.push_back(" ");
    ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuusgfgesrheidFor-aasdsas-theuhtuwaesphoutr" + Chr(34);
    std::string OutFixDoubleQuotesInsideDoubleQuotes = "";
    int fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
    std::vector<std::string> items52 = LoopParseFunc(code);
    for (size_t A_Index52 = 0; A_Index52 < items52.size() + 0; A_Index52++) {
        std::string A_LoopField52 = items52[A_Index52 - 0];
        if (A_LoopField52 == keyWordEscpaeChar && getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index52 + 1] == Chr(34)) {
            fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1;
            OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes;
        } else {
            if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1) {
                OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField52;
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
        std::vector<std::string> items53 = LoopParseFunc(code);
        for (size_t A_Index53 = 0; A_Index53 < items53.size() + 0; A_Index53++) {
            std::string A_LoopField53 = items53[A_Index53 - 0];
            if (A_LoopField53 == Chr(34)) {
                areWEinSome34sNum++;
            }
            if (areWEinSome34sNum == 1) {
                if (A_LoopField53 != Chr(34)) {
                    if (A_LoopField53 == keyWordEscpaeChar) {
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                    } else {
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField53;
                    }
                } else {
                    theIdNumOfThe34++;
                    htCodeOUT754754 += "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                }
            }
            if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                if (A_LoopField53 != Chr(34)) {
                    htCodeOUT754754 += A_LoopField53;
                }
                areWEinSome34sNum = 0;
            }
        }
    } else {
        std::vector<std::string> items54 = LoopParseFunc(code);
        for (size_t A_Index54 = 0; A_Index54 < items54.size() + 0; A_Index54++) {
            std::string A_LoopField54 = items54[A_Index54 - 0];
            if (A_LoopField54 == Chr(34)) {
                areWEinSome34sNum++;
            }
            if (areWEinSome34sNum == 1) {
                if (A_LoopField54 != Chr(34)) {
                    if (A_LoopField54 == keyWordEscpaeChar && keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index54 + 1]) {
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar;
                        removeNexFixkeyWordEscpaeChar = 1;
                    }
                    else if (A_LoopField54 == keyWordEscpaeChar) {
                        if (removeNexFixkeyWordEscpaeChar != 1) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                        } else {
                            removeNexFixkeyWordEscpaeChar = 0;
                        }
                    } else {
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField54;
                    }
                } else {
                    theIdNumOfThe34++;
                    htCodeOUT754754 += "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                }
            }
            if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                if (A_LoopField54 != Chr(34)) {
                    htCodeOUT754754 += A_LoopField54;
                }
                areWEinSome34sNum = 0;
            }
        }
    }
    code = htCodeOUT754754;
    for (int A_Index55 = 0; A_Index55 < theIdNumOfThe34 + 0; A_Index55++) {
        theIdNumOfThe34theVar[A_Index55] = theIdNumOfThe34theVar[A_Index55] + Chr(34);
    }
    theIdNumOfThe34theVar.push_back(Chr(34));
    code = StrReplace(code, Chr(13), "");
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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
    std::string beforeKeywordForRemoveCommentsOnTheEndOfTheLine = "";
    std::string newStringOutCode = "";
    int posForRemoveCommentsOnTheEndOfTheLine = 0;
    std::string originalStringForRemoveCommentsOnTheEndOfTheLine = "";
    std::vector<std::string> items56 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index56 = 0; A_Index56 < items56.size() + 0; A_Index56++) {
        std::string A_LoopField56 = items56[A_Index56 - 0];
        // Define the original string
        originalStringForRemoveCommentsOnTheEndOfTheLine = A_LoopField56;
        // Find the position of the keyword in the original string
        posForRemoveCommentsOnTheEndOfTheLine = InStr(originalStringForRemoveCommentsOnTheEndOfTheLine, " " + keyWordComment);
        if (SubStr(Trim(A_LoopField56), 1, StrLen(keyWordComment)) != keyWordComment) {
            if (posForRemoveCommentsOnTheEndOfTheLine > 0) {
                beforeKeywordForRemoveCommentsOnTheEndOfTheLine = A_LoopField56;
                // Construct the new string with everything before the keyword
                newStringOutCode += beforeKeywordForRemoveCommentsOnTheEndOfTheLine + "\n";
            } else {
                newStringOutCode += A_LoopField56 + "\n";
            }
        } else {
            newStringOutCode += A_LoopField56 + "\n";
        }
    }
    code = StringTrimRight(newStringOutCode, 1);
    //MsgBox, % code
    std::string htCodeOutFixEnd = "";
    int htCodeOutFixINT = 0;
    int htCodeOutFixINT2 = 0;
    if (useCurlyBraces == "on") {
        if (keyWordCurlyBraceOpen != "{") {
            std::vector<std::string> items57 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index57 = 0; A_Index57 < items57.size() + 0; A_Index57++) {
                std::string A_LoopField57 = items57[A_Index57 - 0];
                htCodeOutFixINT2 = 0;
                if (isLineAconstruct(Trim(A_LoopField57)) == true || Trim(A_LoopField57) == keyWordCurlyBraceOpen) {
                    htCodeOutFixINT2 = 1;
                }
                htCodeOutFixINT = 0;
                std::vector<std::string> items58 = LoopParseFunc(A_LoopField57, " ");
                for (size_t A_Index58 = 0; A_Index58 < items58.size() + 0; A_Index58++) {
                    std::string A_LoopField58 = items58[A_Index58 - 0];
                    htCodeOutFixINT++;
                }
                htCodeOutFixINT--;
                std::vector<std::string> items59 = LoopParseFunc(A_LoopField57, " ");
                for (size_t A_Index59 = 0; A_Index59 < items59.size() + 0; A_Index59++) {
                    std::string A_LoopField59 = items59[A_Index59 - 0];
                    if (htCodeOutFixINT == A_Index59 && htCodeOutFixINT2 == 1) {
                        htCodeOutFixINT2 = 0;
                        htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField59, keyWordCurlyBraceOpen, "{") + " ";
                    } else {
                        htCodeOutFixEnd += A_LoopField59 + " ";
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
            std::vector<std::string> items60 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index60 = 0; A_Index60 < items60.size() + 0; A_Index60++) {
                std::string A_LoopField60 = items60[A_Index60 - 0];
                htCodeOutFixINT2 = 0;
                if (isLineAconstruct(Trim(A_LoopField60)) == true || Trim(A_LoopField60) == keyWordCurlyBraceClose) {
                    htCodeOutFixINT2 = 1;
                }
                std::vector<std::string> items61 = LoopParseFunc(A_LoopField60, " ");
                for (size_t A_Index61 = 0; A_Index61 < items61.size() + 0; A_Index61++) {
                    std::string A_LoopField61 = items61[A_Index61 - 0];
                    if (htCodeOutFixINT2 == 1 || Trim(A_LoopField61) == keyWordCurlyBraceClose) {
                        htCodeOutFixINT2 = 0;
                        htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField61, keyWordCurlyBraceClose, "}") + " ";
                    } else {
                        htCodeOutFixEnd += A_LoopField61 + " ";
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
    if (useEnd == "on" || useEndExtraInfo == "on") {
        std::vector<std::string> items62 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index62 = 0; A_Index62 < items62.size() + 0; A_Index62++) {
            std::string A_LoopField62 = items62[A_Index62 - 0];
            if (StrLower(Trim(A_LoopField62)) == StrLower(keyWordEnd) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordAllianceEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordCrewEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordMethodEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordDefObjEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordIFEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordElseIfEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordElseEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordSwitchEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordSwitchCaseEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordSwitchDefaultEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordWhileLoopEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordForLoopEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordLoopInfiniteEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordLoopEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordLoopParseEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordFuncEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordTryEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordCatchEndExtraInfo) || StrLower(Trim(A_LoopField62)) == StrLower(keyWordFinallyEndExtraInfo)) {
                htCodeOutFixEnd += "}\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField62)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF) && isLineAconstruct(Trim(A_LoopField62)) == true) {
                htCodeOutFixEnd += A_LoopField62 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField62)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf) && isLineAconstruct(Trim(A_LoopField62)) == true) {
                htCodeOutFixEnd += "\n}\n" + A_LoopField62 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField62)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse) && isLineAconstruct(Trim(A_LoopField62)) == true) {
                htCodeOutFixEnd += "\n}\n" + A_LoopField62 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField62)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch) && isLineAconstruct(Trim(A_LoopField62)) == true) {
                htCodeOutFixEnd += "\n}\n" + A_LoopField62 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField62)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally) && isLineAconstruct(Trim(A_LoopField62)) == true) {
                htCodeOutFixEnd += "\n}\n" + A_LoopField62 + "\n{\n";
            }
            else if (isLineAconstruct(Trim(A_LoopField62)) == true) {
                htCodeOutFixEnd += A_LoopField62 + "\n{\n";
            } else {
                htCodeOutFixEnd += A_LoopField62 + "\n";
            }
        }
        code = StringTrimRight(htCodeOutFixEnd, 1);
    }
    if (usePythonicColonSyntax == "off") {
        if (useEnd == "off" && useEndExtraInfo == "off" && useCurlyBraces == "off") {
            htCodeOutFixEnd = "";
            std::vector<std::string> items63 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index63 = 0; A_Index63 < items63.size() + 0; A_Index63++) {
                std::string A_LoopField63 = items63[A_Index63 - 0];
                if (isLineAconstruct(Trim(A_LoopField63)) == true) {
                    htCodeOutFixEnd += A_LoopField63 + ":\n";
                } else {
                    htCodeOutFixEnd += A_LoopField63 + "\n";
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
    }
    if (useCurlyBraces == "off" && useEnd == "off" && useEndExtraInfo == "off") {
        code = AddCurlyBraces(code);
    }
    outTrimCode = "";
    std::vector<std::string> items64 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index64 = 0; A_Index64 < items64.size() + 0; A_Index64++) {
        std::string A_LoopField64 = items64[A_Index64 - 0];
        outTrimCode += Trim(A_LoopField64) + "\n";
    }
    code = StringTrimRight(outTrimCode, 1);
    // for converting c++ to js and py
    //code := StrReplace(code, "{}", "[]")
    std::string outCodeFixBraces = "";
    for (int A_Index65 = 0; A_Index65 < 2 + 0; A_Index65++) {
        outCodeFixBraces = "";
        std::vector<std::string> items66 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index66 = 0; A_Index66 < items66.size() + 0; A_Index66++) {
            std::string A_LoopField66 = items66[A_Index66 - 0];
            if (InStr(Trim(A_LoopField66), "{") && Trim(A_LoopField66) != "{") {
                outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField66), "{", "")) + "\n{\n";
            }
            else if (InStr(Trim(A_LoopField66), "}") && Trim(A_LoopField66) != "}") {
                outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField66), "}", "")) + "\n";
            } else {
                outCodeFixBraces += Trim(A_LoopField66) + "\n";
            }
        }
        code = StringTrimRight(outCodeFixBraces, 1);
    }
    htCodeOutFixEnd = "";
    if (usePythonicColonSyntax == "on") {
        std::vector<std::string> items67 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index67 = 0; A_Index67 < items67.size() + 0; A_Index67++) {
            std::string A_LoopField67 = items67[A_Index67 - 0];
            if (isLineAconstruct(Trim(A_LoopField67)) == true) {
                htCodeOutFixEnd += StringTrimRight(A_LoopField67, 1) + "\n";
            } else {
                htCodeOutFixEnd += A_LoopField67 + "\n";
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
    std::vector<std::string> items68 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index68 = 0; A_Index68 < items68.size() + 0; A_Index68++) {
        std::string A_LoopField68 = items68[A_Index68 - 0];
        if (StrLower(A_LoopField68) == StrLower(keyWordMainLabel)) {
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
            codeOutFixAndAddMainFunc += A_LoopField68 + "\n";
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
    std::vector<std::string> items69 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index69 = 0; A_Index69 < items69.size() + 0; A_Index69++) {
        std::string A_LoopField69 = items69[A_Index69 - 0];
        lookIntoTheNextLineForFuncWhitNoKeyWord.push_back(A_LoopField69);
    }
    lookIntoTheNextLineForFuncWhitNoKeyWord.push_back(" ");
    htCode = "";
    print("=======UP==========");
    print(code);
    print("=======DOWN==========");
    std::vector<std::string> items70 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index70 = 0; A_Index70 < items70.size() + 0; A_Index70++) {
        std::string A_LoopField70 = items70[A_Index70 - 0];
        lineDone = 0;
        if (A_LoopField70 == "qWERDEW3ERE QOWES FSjw sfdfouwae pawi") {
            htCode += "ASFSEDF\n";
        }
        else if (StrLower(A_LoopField70) == StrLower(keyWordLoopInfinite) || StrLower(A_LoopField70) == StrLower(keyWordLoopInfinite + ":")) {
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
            nothing = "";
            AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
            htCodeAcurlyBraceAddSomeVrasFixNL = 1;
            lineDone = 1;
            if (langToConvertTo != "ahk") {
                htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
            }
            AindexcharLength++;
            htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
        }
        else if (SubStr(Trim(StrLower(A_LoopField70)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop) && SubStr(Trim(StrLower(A_LoopField70)), 1, StrLen(StrLower(keyWordLoop)) + 2) != StrLower(keyWordLoop) + "% " && SubStr(Trim(StrLower(A_LoopField70)), 1, StrLen(StrLower(keyWordLoopParse))) != StrLower(keyWordLoopParse)) {
            out2 = StringTrimLeft(A_LoopField70, StrLen(keyWordLoop));
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
            nothing = "";
            AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
            htCodeAcurlyBraceAddSomeVrasFixNL = 1;
            if (langToConvertTo != "ahk") {
                htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
            }
            AindexcharLength++;
            lineDone = 1;
            htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
        }
        else if (SubStr(Trim(StrLower(A_LoopField70)), 1, StrLen(StrLower(keyWordLoop)) + 2) == StrLower(keyWordLoop) + "% ") {
            out2 = StringTrimLeft(A_LoopField70, StrLen(keyWordLoop) + 2);
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
            nothing = "";
            AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
            htCodeAcurlyBraceAddSomeVrasFixNL = 1;
            if (langToConvertTo != "ahk") {
                htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
            }
            AindexcharLength++;
            lineDone = 1;
            htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
        }
        else if (SubStr(StrLower(A_LoopField70), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
            var1 = StringTrimLeft(A_LoopField70, StrLen(keyWordLoopParse));
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
            if (langToConvertTo != "ahk") {
                htCodeLoopfixa += "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                htCodeLoopfixa1 = "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
            }
            AindexcharLength++;
            htCode += htCodeLoopfixa1 + "\n" + var1out + "\n";
        }
        else if ((SubStr(Trim(A_LoopField70), -2) == ");" || SubStr(Trim(A_LoopField70), -1) == ")") && !(InStr(A_LoopField70, "int main(int argc, char* argv[])")) && !(InStr(A_LoopField70, "async function main()")) && lineDone == 0) {
            lineDone = 1;
            str1 = A_LoopField70;
            if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "scala" || langToConvertTo == "groovy") {
                str1 = StrReplace(str1, ";", "");
            }
            str2 = expressionParserTranspiler(Trim(str1)) + ";";
            if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "scala" || langToConvertTo == "groovy") {
                str2 = StrReplace(str2, ";", "");
            } else {
                str2 = StrReplace(str2, ";;", ";");
            }
            htCode += str2 + "\n";
        } else {
            //print("else else else " . A_LoopField70)
            // this is THE else
            if (lineDone != 1) {
                if (skipLeftCuleyForFuncPLS != 1) {
                    if (SubStr(Trim(StrLower(A_LoopField70)), 1, 1) == Chr(125)) {
                        htCode += Chr(125) + "\n";
                    } else {
                        if (htCodeAcurlyBraceAddSomeVrasFixLP == 1 && SubStr(Trim(StrLower(A_LoopField70)), 1, 1) == Chr(123)) {
                            htCodeAcurlyBraceAddSomeVrasFixLP = 0;
                            htCode += A_LoopField70 + "\n" + theFixTextLoopLP + "\n";
                        } else {
                            if (htCodeAcurlyBraceAddSomeVrasFixNL == 1 && SubStr(Trim(StrLower(A_LoopField70)), 1, 1) == Chr(123)) {
                                htCodeAcurlyBraceAddSomeVrasFixNL = 0;
                                htCode += A_LoopField70 + "\n" + theFixTextLoopNL + "\n";
                            } else {
                                htCode += A_LoopField70 + "\n";
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
    if (langToConvertTo != "ahk") {
        //s
        if (haveWeEverUsedAloop == 1) {
            htCodeLoopfixa = StringTrimRight(htCodeLoopfixa, 1);
            //OutputDebug, |%htCodeLoopfixa%|
            AIndexLoopCurlyFix = 1;
            std::vector<std::string> items71 = LoopParseFunc(htCodeLoopfixa, "\n", "\r");
            for (size_t A_Index71 = 0; A_Index71 < items71.size() + 0; A_Index71++) {
                std::string A_LoopField71 = items71[A_Index71 - 0];
                sstr123 = A_LoopField71;
                fixLoopLokingFor = A_LoopField71;
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
                    std::vector<std::string> items72 = LoopParseFunc(htCode, "\n", "\r");
                    for (size_t A_Index72 = 0; A_Index72 < items72.size() + 0; A_Index72++) {
                        std::string A_LoopField72 = items72[A_Index72 - 0];
                        //MsgBox, dsfgsdefgesrdg1
                        //MsgBox, |%A_LoopField72%|`n|%fixLoopLokingFor%|
                        if (InStr(A_LoopField72, fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                            fixLoopLokingForNum = 1;
                            //MsgBox, do we came here 1
                        }
                        if (SubStr(Trim(A_LoopField72), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                            s = StrSplit(A_LoopField72 ,"" + keyWordAIndex + "", 2);
                            out1z = s;
                            s = StrSplit(out1z, " ", 1);
                            out1z = Trim(s);
                            //MsgBox, % out1z
                            //MsgBox, do we came here 2
                            fixLoopLokingForNum = 0;
                            foundTheTopLoop++;
                            inTarget = 1;
                            //MsgBox, % A_LoopField72
                            dontSaveStr = 1;
                            ALoopField = A_LoopField72;
                            DeleayOneCuzOfLoopParse = 1;
                            out4758686d86d86d86578991a += ALoopField + "\n";
                        }
                        if (inTarget == 1 && InStr(A_LoopField72, Chr(123)) && insdeAnestedLoopBAD != 1) {
                            insideBracket = 1;
                        }
                        if (insideBracket == 1 && InStr(A_LoopField72, Chr(123)) && insdeAnestedLoopBAD != 1) {
                            netsedCurly++;
                        }
                        if (insideBracket == 1 && InStr(A_LoopField72, Chr(125)) && insdeAnestedLoopBAD != 1) {
                            netsedCurly--;
                            readyToEnd = 1;
                        }
                        if (SubStr(Trim(A_LoopField72), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                            insdeAnestedLoopBAD = 1;
                            insideBracket1 = 0;
                            netsedCurly1 = 0;
                        }
                        if (inTarget == 1) {
                            foundTheTopLoop++;
                        }
                        if (insdeAnestedLoopBAD == 1) {
                            if (InStr(A_LoopField72, Chr(123))) {
                                insideBracket1 = 1;
                            }
                            if (insideBracket1 == 1 && InStr(A_LoopField72, Chr(123))) {
                                netsedCurly1++;
                            }
                            if (insideBracket1 == 1 && InStr(A_LoopField72, Chr(125))) {
                                netsedCurly1--;
                                readyToEnd1 = 1;
                            }
                            if (InStr(A_LoopField72, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                //MsgBox, % A_LoopField72
                                eldLoopNestedBADlol = 1;
                            }
                            out4758686d86d86d86578991a += A_LoopField72 + "\n";
                        }
                        if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                            ALoopField = A_LoopField72;
                            // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                            ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                            out4758686d86d86d86578991a += ALoopField + "\n";
                        }
                        if (inTarget == 1 && InStr(A_LoopField72, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1) {
                            //MsgBox, % A_LoopField72
                            weAreDoneHereCurly = 1;
                            inTarget = 0;
                            endBracketDOntPutThere = 1;
                        }
                        dontSaveStr = 0;
                        if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                            out4758686d86d86d86578991a += A_LoopField72 + "\n";
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
                    std::vector<std::string> items73 = LoopParseFunc(htCode, "\n", "\r");
                    for (size_t A_Index73 = 0; A_Index73 < items73.size() + 0; A_Index73++) {
                        std::string A_LoopField73 = items73[A_Index73 - 0];
                        if (InStr(A_LoopField73 , fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                            fixLoopLokingForNum = 1;
                            //MsgBox, do we came here 3
                        }
                        if (SubStr(Trim(A_LoopField73), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                            s = StrSplit(A_LoopField73 ,"" + keyWordAIndex + "", 2);
                            out1z = s;
                            s = StrSplit(out1z, " ", 1);
                            out1z = Trim(s);
                            //MsgBox, % out1z
                            fixLoopLokingForNum = 0;
                            //MsgBox, do we came here 4
                            foundTheTopLoop++;
                            inTarget = 1;
                            //MsgBox, % A_LoopField73
                            dontSaveStr = 1;
                            ALoopField = A_LoopField73;
                            DeleayOneCuzOfLoopParse = 1;
                            out4758686d86d86d86578991a += ALoopField + "\n";
                        }
                        if (inTarget == 1 && InStr(A_LoopField73, Chr(123)) && insdeAnestedLoopBAD != 1) {
                            insideBracket = 1;
                        }
                        if (insideBracket == 1 && InStr(A_LoopField73, Chr(123)) && insdeAnestedLoopBAD != 1) {
                            netsedCurly++;
                        }
                        if (insideBracket == 1 && InStr(A_LoopField73, Chr(125)) && insdeAnestedLoopBAD != 1) {
                            netsedCurly--;
                            readyToEnd = 1;
                        }
                        if (SubStr(Trim(A_LoopField73), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                            insdeAnestedLoopBAD = 1;
                            insideBracket1 = 0;
                            netsedCurly1 = 0;
                        }
                        if (inTarget == 1) {
                            foundTheTopLoop++;
                        }
                        if (insdeAnestedLoopBAD == 1) {
                            if (InStr(A_LoopField73, Chr(123))) {
                                insideBracket1 = 1;
                            }
                            if (insideBracket1 == 1 && InStr(A_LoopField73, Chr(123))) {
                                netsedCurly1++;
                            }
                            if (insideBracket1 == 1 && InStr(A_LoopField73, Chr(125))) {
                                netsedCurly1--;
                                readyToEnd1 = 1;
                            }
                            if (InStr(A_LoopField73, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                //MsgBox, % A_LoopField73
                                eldLoopNestedBADlol = 1;
                            }
                            out4758686d86d86d86578991a += A_LoopField73 + "\n";
                        }
                        if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                            ALoopField = A_LoopField73;
                            // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                            ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                            // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                            ALoopField = RegExReplace(ALoopField, "" + keyWordALoopField + "\\d*", "" + keyWordALoopField + "" + out1z);
                            out4758686d86d86d86578991a += ALoopField + "\n";
                        }
                        if ((inTarget == 1 && InStr(A_LoopField73, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1)) {
                            //MsgBox, % A_LoopField73
                            weAreDoneHereCurly = 1;
                            inTarget = 0;
                            endBracketDOntPutThere = 1;
                        }
                        dontSaveStr = 0;
                        if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                            out4758686d86d86d86578991a += A_LoopField73 + "\n";
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
            std::vector<std::string> items74 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index74 = 0; A_Index74 < items74.size() + 0; A_Index74++) {
                std::string A_LoopField74 = items74[A_Index74 - 0];
                ignore = 0;
                if (SubStr(Trim(A_LoopField74), 1, 4) == "for ") {
                    if (hold == 1 && holdText == A_LoopField74) {
                        ignore = 1;
                    } else {
                        holdText = A_LoopField74;
                        hold = 1;
                    }
                }
                if (!ignore) {
                    out4758686d86dgt8r754444444 += A_LoopField74 + "\n";
                }
            }
            out4758686d86dgt8r754444444 = StringTrimRight(out4758686d86dgt8r754444444, 1);
            htCode = out4758686d86dgt8r754444444;
        }
        htCodeOut1234565432 = "";
        std::vector<std::string> items75 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index75 = 0; A_Index75 < items75.size() + 0; A_Index75++) {
            std::string A_LoopField75 = items75[A_Index75 - 0];
            out = A_LoopField75;
            if (!InStr(out, "|itsaersdtgtgfergsdgfsegdfsedAA|")) {
                htCodeOut1234565432 += out + "\n";
            }
        }
        htCode = StringTrimRight(htCodeOut1234565432, 1);
    }
    if (langToConvertTo == "py" || langToConvertTo == "nim") {
        htCode = indent_nested_curly_braces(htCode, 0);
    } else {
        htCode = indent_nested_curly_braces(htCode, 1);
    }
    std::string fixLuaAndRuby = "";
    if (langToConvertTo == "lua" || langToConvertTo == "rb") {
        std::vector<std::string> items76 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index76 = 0; A_Index76 < items76.size() + 0; A_Index76++) {
            std::string A_LoopField76 = items76[A_Index76 - 0];
            if (Trim(A_LoopField76) == "}") {
                fixLuaAndRuby += StrReplace(A_LoopField76, "}", "end") + "\n";
            }
            else if (SubStrLastChars(A_LoopField76, 2) == " {") {
                fixLuaAndRuby += StringTrimRight(A_LoopField76, 2) + "\n";
            } else {
                fixLuaAndRuby += A_LoopField76 + "\n";
            }
        }
        htCode = StringTrimRight(fixLuaAndRuby, 1);
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
    std::vector<std::string> items77 = LoopParseFunc(instructions, "\n", "\r");
    for (size_t A_Index77 = 0; A_Index77 < items77.size() + 0; A_Index77++) {
        std::string A_LoopField77 = items77[A_Index77 - 0];
        if (Trim(A_LoopField77) == "funcEND======================funcEND==============") {
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
                funcLangHolder = StringTrimLeft(A_LoopField77, 5);
                if (Trim(funcLangHolder) == langToConvertTo) {
                    allFuncLang.push_back(Trim(funcLangHolder));
                    correctLang = 1;
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 2) {
                // name of the func
                funcNameHolder = StringTrimLeft(A_LoopField77, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allFuncNames.push_back(Trim(funcNameHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 3) {
                // all libs
                funcLibsHolder = StringTrimLeft(A_LoopField77, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allFuncLibs.push_back(Trim(funcLibsHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 4) {
                // func description
                funcDescriptionHolder = StringTrimLeft(A_LoopField77, 12);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allfuncDescription.push_back(Trim(funcDescriptionHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum >= 5) {
                // the full func
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    funcFuncHolder += A_LoopField77 + "\n";
                }
            }
            //MsgBox, % A_LoopField77
            areWeInAFuncFromInstructionsLineNum++;
        }
        if (Trim(A_LoopField77) == "func======================func==============") {
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
        for (int A_Index78 = 0; A_Index78 < allFuncNames.size() + 0; A_Index78++) {
            if (InStr(htCode, allFuncNames[A_Index78]) + "(") {
                //MsgBox, % allFuncNames[A_Index78]
                allFuncsToPutAtTop += allFuncs[A_Index78] + "\n";
                if (Trim(allFuncLibs[A_Index78]) != "null") {
                    allLibsToPutAtTop += allFuncLibs[A_Index78] + "|";
                }
            }
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTop, 1);
        std::string allLibsToPutAtTopTEMP;
        std::vector<std::string> items79 = LoopParseFunc(allLibsToPutAtTop, "|");
        for (size_t A_Index79 = 0; A_Index79 < items79.size() + 0; A_Index79++) {
            std::string A_LoopField79 = items79[A_Index79 - 0];
            allLibsToPutAtTopTEMP += A_LoopField79 + "\n";
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
    for (int A_Index80 = 0; A_Index80 < theIdNumOfThe34 + 0; A_Index80++) {
        if (theIdNumOfThe34 == A_Index80 + 1) {
            htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(A_Index80 + 1) + Chr(65) + Chr(65), theIdNumOfThe34theVar[A_Index80 + 1] + Chr(34));
        } else {
            htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(A_Index80 + 1) + Chr(65) + Chr(65), theIdNumOfThe34theVar[A_Index80 + 1]);
        }
    }
    htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, Chr(92) + Chr(34));
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
    HTVM_v2_HTVM();
    if (noParams == true) {
        return;
    }
    std::vector<std::string> items81 = LoopParseFunc(str0);
    for (size_t A_Index81 = 0; A_Index81 < items81.size() + 0; A_Index81++) {
        std::string A_LoopField81 = items81[A_Index81 - 0];
        str00 = Trim(A_LoopField81);
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
        std::vector<std::string> items82 = LoopParseFunc(allArgs, "\n", "\r");
        for (size_t A_Index82 = 0; A_Index82 < items82.size() + 0; A_Index82++) {
            std::string A_LoopField82 = items82[A_Index82 - 0];
            if (A_Index82 == 0) {
                argCODE = FileRead(Trim(A_LoopField82));
                argCODEfile = Trim(A_LoopField82);
            }
            else if (A_Index82 == 1) {
                argHTVMinstr = Trim(A_LoopField82);
            }
            else if (A_Index82 == 2) {
                argLangTo = Trim(A_LoopField82);
            } else {
                argHTVMinstrMOVE.push_back(Trim(A_LoopField82));
            }
        }
        print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        if (SubStrLastChars(argCODEfile, 4) == ".cpp" || SubStrLastChars(argCODEfile, 3) == ".py" || SubStrLastChars(argCODEfile, 3) == ".js" || SubStrLastChars(argCODEfile, 3) == ".go" || SubStrLastChars(argCODEfile, 4) == ".lua" || SubStrLastChars(argCODEfile, 3) == ".cs" || SubStrLastChars(argCODEfile, 5) == ".java" || SubStrLastChars(argCODEfile, 3) == ".kt" || SubStrLastChars(argCODEfile, 3) == ".rb" || SubStrLastChars(argCODEfile, 4) == ".nim" || SubStrLastChars(argCODEfile, 4) == ".ahk" || SubStrLastChars(argCODEfile, 6) == ".swift" || SubStrLastChars(argCODEfile, 5) == ".dart" || SubStrLastChars(argCODEfile, 3) == ".ts" || SubStrLastChars(argCODEfile, 6) == ".scala" || SubStrLastChars(argCODEfile, 7) == ".groovy") {
            if (argLangTo != "") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", argLangTo);
            } else {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM");
            }
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