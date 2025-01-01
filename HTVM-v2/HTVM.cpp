#include <algorithm>
#include <any>
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

std::string Trim(const std::string &inputString) {
    if (inputString.empty()) return "";
    size_t start = inputString.find_first_not_of(" \t\n\r\f\v");
    size_t end = inputString.find_last_not_of(" \t\n\r\f\v");
    return (start == std::string::npos) ? "" : inputString.substr(start, end - start + 1);
}

std::string StringTrimRight(const std::string &input, int numChars) {
    return (numChars <= input.length()) ? input.substr(0, input.length() - numChars) : input;
}

int Mod(int dividend, int divisor) {
    return dividend % divisor;
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
std::vector<std::string> argHTVMinstrMOVE;
std::string extraCodeReturned = "";
std::string langToConvertTo = "";
std::string langFileExtension = "";
std::string compiler(std::string code, std::string instructionFile, std::string mode, std::string langToConvertToParam = "") {
    extraCodeReturned = "";
    std::string allInstructionFile = Trim(FileRead(instructionFile));
    std::vector<std::string> items1 = LoopParseFunc(allInstructionFile, "\n", "\r");
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        if (A_Index1 == 0) {
            langToConvertTo = Trim(A_LoopField1);
        }
        if (A_Index1 == 1) {
            langFileExtension = Trim(A_LoopField1);
        }
        if (A_Index1 == 2) {
            std::string commands = Trim(A_LoopField1);
        }
        if (A_Index1 == 3) {
            std::string keyWordAlliance = Trim(A_LoopField1);
        }
        if (A_Index1 == 4) {
            std::string keyWordCrew = Trim(A_LoopField1);
        }
        if (A_Index1 == 5) {
            std::string keyWordMethod = Trim(A_LoopField1);
        }
        if (A_Index1 == 6) {
            std::string keyWordDefObj = Trim(A_LoopField1);
        }
        if (A_Index1 == 7) {
            std::string keyWordPorp = Trim(A_LoopField1);
        }
        if (A_Index1 == 8) {
            std::string keyWordThis = Trim(A_LoopField1);
        }
        if (A_Index1 == 9) {
            std::string keyWordInclude = Trim(A_LoopField1);
        }
        if (A_Index1 == 10) {
            std::string keyWordIncludeInTheTranspiledLang = Trim(A_LoopField1);
        }
        if (A_Index1 == 11) {
            std::string keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField1);
        }
        if (A_Index1 == 12) {
            std::string keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField1);
        }
        if (A_Index1 == 13) {
            std::string keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField1);
        }
        if (A_Index1 == 14) {
            std::string keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField1);
        }
        if (A_Index1 == 15) {
            std::string keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField1);
        }
        if (A_Index1 == 16) {
            std::string keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField1);
        }
        if (A_Index1 == 17) {
            std::string keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField1);
        }
        if (A_Index1 == 18) {
            std::string keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField1);
        }
        if (A_Index1 == 19) {
            std::string keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField1);
        }
        if (A_Index1 == 20) {
            std::string keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField1);
        }
        if (A_Index1 == 21) {
            std::string keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField1);
        }
        if (A_Index1 == 22) {
            std::string keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField1);
        }
        if (A_Index1 == 23) {
            std::string keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField1);
        }
        if (A_Index1 == 24) {
            std::string keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField1);
        }
        if (A_Index1 == 25) {
            std::string keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField1);
        }
        if (A_Index1 == 26) {
            std::string keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField1);
        }
        if (A_Index1 == 27) {
            std::string keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField1);
        }
        if (A_Index1 == 28) {
            std::string keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField1);
        }
        if (A_Index1 == 29) {
            std::string keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField1);
        }
        if (A_Index1 == 30) {
            std::string keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField1);
        }
        if (A_Index1 == 31) {
            std::string keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField1);
        }
        if (A_Index1 == 32) {
            std::string keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField1);
        }
        if (A_Index1 == 33) {
            std::string keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField1);
        }
        if (A_Index1 == 34) {
            std::string keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField1);
        }
        if (A_Index1 == 35) {
            std::string keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField1);
        }
        if (A_Index1 == 36) {
            std::string keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField1);
        }
        if (A_Index1 == 37) {
            std::string keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField1);
        }
        if (A_Index1 == 38) {
            std::string keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField1);
        }
        if (A_Index1 == 39) {
            std::string keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField1);
        }
        if (A_Index1 == 40) {
            std::string keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField1);
        }
        if (A_Index1 == 41) {
            std::string keyWordCodeInTheTranspiledLangStartSCALA = Trim(A_LoopField1);
        }
        if (A_Index1 == 42) {
            std::string keyWordCodeInTheTranspiledLangEndSCALA = Trim(A_LoopField1);
        }
        if (A_Index1 == 43) {
            std::string keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField1);
        }
        if (A_Index1 == 44) {
            std::string keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField1);
        }
        if (A_Index1 == 45) {
            std::string keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField1);
        }
        if (A_Index1 == 46) {
            std::string keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField1);
        }
        if (A_Index1 == 47) {
            std::string keyWordCodeInHTVMstart = Trim(A_LoopField1);
        }
        if (A_Index1 == 48) {
            std::string keyWordCodeInHTVMend = Trim(A_LoopField1);
        }
        if (A_Index1 == 49) {
            std::string keyWordCodeInOtherHTVMsyntaxStart = Trim(A_LoopField1);
        }
        if (A_Index1 == 50) {
            std::string keyWordCodeInOtherHTVMsyntaxStart = Trim(A_LoopField1);
        }
        if (A_Index1 == 51) {
            std::string keyWordCurlyBraceOpen = Trim(A_LoopField1);
        }
        if (A_Index1 == 52) {
            std::string keyWordCurlyBraceClose = Trim(A_LoopField1);
        }
        if (A_Index1 == 53) {
            std::string keyWordNull = Trim(A_LoopField1);
        }
        if (A_Index1 == 54) {
            std::string keyWordTrue = Trim(A_LoopField1);
        }
        if (A_Index1 == 55) {
            std::string keyWordFalse = Trim(A_LoopField1);
        }
        if (A_Index1 == 56) {
            std::string keyWordVoid = Trim(A_LoopField1);
        }
        if (A_Index1 == 57) {
            std::string keyWordDouble = Trim(A_LoopField1);
        }
        if (A_Index1 == 58) {
            std::string keyWordChar = Trim(A_LoopField1);
        }
        if (A_Index1 == 59) {
            std::string keyWordUint8 = Trim(A_LoopField1);
        }
        if (A_Index1 == 60) {
            std::string keyWordUint16 = Trim(A_LoopField1);
        }
        if (A_Index1 == 61) {
            std::string keyWordUint32 = Trim(A_LoopField1);
        }
        if (A_Index1 == 62) {
            std::string keyWordUint64 = Trim(A_LoopField1);
        }
        if (A_Index1 == 63) {
            std::string keyWordINT = Trim(A_LoopField1);
        }
        if (A_Index1 == 64) {
            std::string keyWordSTR = Trim(A_LoopField1);
        }
        if (A_Index1 == 65) {
            std::string keyWordBOOL = Trim(A_LoopField1);
        }
        if (A_Index1 == 66) {
            std::string keyWordFLOAT = Trim(A_LoopField1);
        }
        if (A_Index1 == 67) {
            std::string keyWordINT8 = Trim(A_LoopField1);
        }
        if (A_Index1 == 68) {
            std::string keyWordINT16 = Trim(A_LoopField1);
        }
        if (A_Index1 == 69) {
            std::string keyWordINT32 = Trim(A_LoopField1);
        }
        if (A_Index1 == 70) {
            std::string keyWordINT64 = Trim(A_LoopField1);
        }
        if (A_Index1 == 71) {
            std::string keyWordIF = Trim(A_LoopField1);
        }
        if (A_Index1 == 72) {
            std::string keyWordElseIf = Trim(A_LoopField1);
        }
        if (A_Index1 == 73) {
            std::string keyWordElse = Trim(A_LoopField1);
        }
        if (A_Index1 == 74) {
            std::string keyWordSwitch = Trim(A_LoopField1);
        }
        if (A_Index1 == 75) {
            std::string keyWordSwitchCase = Trim(A_LoopField1);
        }
        if (A_Index1 == 76) {
            std::string keyWordSwitchDefault = Trim(A_LoopField1);
        }
        if (A_Index1 == 77) {
            std::string keyWordWhileLoop = Trim(A_LoopField1);
        }
        if (A_Index1 == 78) {
            std::string keyWordForLoop = Trim(A_LoopField1);
        }
        if (A_Index1 == 79) {
            std::string keyWordLoopInfinite = Trim(A_LoopField1);
        }
        if (A_Index1 == 80) {
            std::string keyWordLoop = Trim(A_LoopField1);
        }
        if (A_Index1 == 81) {
            std::string keyWordLoopParse = Trim(A_LoopField1);
        }
        if (A_Index1 == 82) {
            std::string keyWordContinue = Trim(A_LoopField1);
        }
        if (A_Index1 == 83) {
            std::string keyWordBreak = Trim(A_LoopField1);
        }
        if (A_Index1 == 84) {
            std::string keyWordFunc = Trim(A_LoopField1);
        }
        if (A_Index1 == 85) {
            std::string keyWordAwait = Trim(A_LoopField1);
        }
        if (A_Index1 == 86) {
            std::string keyWordAsync = Trim(A_LoopField1);
        }
        if (A_Index1 == 87) {
            std::string keyWordThrow = Trim(A_LoopField1);
        }
        if (A_Index1 == 88) {
            std::string keyWordErrorMsg = Trim(A_LoopField1);
        }
        if (A_Index1 == 89) {
            std::string keyWordTry = Trim(A_LoopField1);
        }
        if (A_Index1 == 90) {
            std::string keyWordCatch = Trim(A_LoopField1);
        }
        if (A_Index1 == 91) {
            std::string keyWordFinally = Trim(A_LoopField1);
        }
        if (A_Index1 == 92) {
            std::string keyWordReturnStatement = Trim(A_LoopField1);
        }
        if (A_Index1 == 93) {
            std::string keyWordArrayAppend = Trim(A_LoopField1);
        }
        if (A_Index1 == 94) {
            std::string keyWordArrayPop = Trim(A_LoopField1);
        }
        if (A_Index1 == 95) {
            std::string keyWordArraySize = Trim(A_LoopField1);
        }
        if (A_Index1 == 96) {
            std::string keyWordArrayInsert = Trim(A_LoopField1);
        }
        if (A_Index1 == 97) {
            std::string keyWordArrayRemove = Trim(A_LoopField1);
        }
        if (A_Index1 == 98) {
            std::string keyWordArrayIndexOf = Trim(A_LoopField1);
        }
        if (A_Index1 == 99) {
            std::string keyWordArrayDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 100) {
            std::string keyWordArrayOfIntegersDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 101) {
            std::string keyWordArrayOfStringsDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 102) {
            std::string keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 103) {
            std::string keyWordArrayOfBooleansDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 104) {
            std::string keyWordJavaScriptVar = Trim(A_LoopField1);
        }
        if (A_Index1 == 105) {
            std::string keyWordJavaScriptLet = Trim(A_LoopField1);
        }
        if (A_Index1 == 106) {
            std::string keyWordJavaScriptConst = Trim(A_LoopField1);
        }
        if (A_Index1 == 107) {
            std::string keyWordEnd = Trim(A_LoopField1);
        }
        if (A_Index1 == 108) {
            std::string keyWordGlobal = Trim(A_LoopField1);
        }
        if (A_Index1 == 109) {
            std::string keyWordComment = Trim(A_LoopField1);
        }
        if (A_Index1 == 110) {
            std::string keyWordCommentOpenMultiLine = Trim(A_LoopField1);
        }
        if (A_Index1 == 111) {
            std::string keyWordCommentCloseMultiLine = Trim(A_LoopField1);
        }
        if (A_Index1 == 112) {
            std::string keyWordEscpaeChar = Trim(A_LoopField1);
        }
        if (A_Index1 == 113) {
            std::string keyWordMainLabel = Trim(A_LoopField1);
        }
        if (A_Index1 == 114) {
            std::string keyWordConcat = Trim(A_LoopField1);
        }
        if (A_Index1 == 115) {
            std::string keyWordAdd = Trim(A_LoopField1);
        }
        if (A_Index1 == 116) {
            std::string keyWordSub = Trim(A_LoopField1);
        }
        if (A_Index1 == 117) {
            std::string keyWordMul = Trim(A_LoopField1);
        }
        if (A_Index1 == 118) {
            std::string keyWordDiv = Trim(A_LoopField1);
        }
        if (A_Index1 == 119) {
            std::string keyWordMod = Trim(A_LoopField1);
        }
        if (A_Index1 == 120) {
            std::string keyWordExp = Trim(A_LoopField1);
        }
        if (A_Index1 == 121) {
            std::string keyWordEqual = Trim(A_LoopField1);
        }
        if (A_Index1 == 122) {
            std::string keyWordStrictEqual = Trim(A_LoopField1);
        }
        if (A_Index1 == 123) {
            std::string keyWordNotEqual = Trim(A_LoopField1);
        }
        if (A_Index1 == 124) {
            std::string keyWordGreater = Trim(A_LoopField1);
        }
        if (A_Index1 == 125) {
            std::string keyWordLess = Trim(A_LoopField1);
        }
        if (A_Index1 == 126) {
            std::string keyWordGreaterEqual = Trim(A_LoopField1);
        }
        if (A_Index1 == 127) {
            std::string keyWordLessEqual = Trim(A_LoopField1);
        }
        if (A_Index1 == 128) {
            std::string keyWordAnd = Trim(A_LoopField1);
        }
        if (A_Index1 == 129) {
            std::string keyWordOr = Trim(A_LoopField1);
        }
        if (A_Index1 == 130) {
            std::string keyWordNot = Trim(A_LoopField1);
        }
        if (A_Index1 == 131) {
            std::string keyWordBitAnd = Trim(A_LoopField1);
        }
        if (A_Index1 == 132) {
            std::string keyWordBitOr = Trim(A_LoopField1);
        }
        if (A_Index1 == 133) {
            std::string keyWordBitXor = Trim(A_LoopField1);
        }
        if (A_Index1 == 134) {
            std::string keyWordBitNot = Trim(A_LoopField1);
        }
        if (A_Index1 == 135) {
            std::string keyWordShiftLeft = Trim(A_LoopField1);
        }
        if (A_Index1 == 136) {
            std::string keyWordShiftRight = Trim(A_LoopField1);
        }
        if (A_Index1 == 137) {
            std::string keyWordShiftUnsignedRight = Trim(A_LoopField1);
        }
        if (A_Index1 == 138) {
            std::string keyWordAssign = Trim(A_LoopField1);
        }
        if (A_Index1 == 139) {
            std::string keyWordAssignAdd = Trim(A_LoopField1);
        }
        if (A_Index1 == 140) {
            std::string keyWordAssignConcat = Trim(A_LoopField1);
        }
        if (A_Index1 == 141) {
            std::string keyWordAssignSub = Trim(A_LoopField1);
        }
        if (A_Index1 == 142) {
            std::string keyWordAssignMul = Trim(A_LoopField1);
        }
        if (A_Index1 == 143) {
            std::string keyWordAssignDiv = Trim(A_LoopField1);
        }
        if (A_Index1 == 144) {
            std::string keyWordAssignMod = Trim(A_LoopField1);
        }
        if (A_Index1 == 145) {
            std::string keyWordAssignShiftLeft = Trim(A_LoopField1);
        }
        if (A_Index1 == 146) {
            std::string keyWordAssignShiftRight = Trim(A_LoopField1);
        }
        if (A_Index1 == 147) {
            std::string keyWordAssignBitAnd = Trim(A_LoopField1);
        }
        if (A_Index1 == 148) {
            std::string keyWordAssignBitOr = Trim(A_LoopField1);
        }
        if (A_Index1 == 149) {
            std::string keyWordAssignBitXor = Trim(A_LoopField1);
        }
        if (A_Index1 == 150) {
            std::string keyWordTernary1 = Trim(A_LoopField1);
        }
        if (A_Index1 == 151) {
            std::string keyWordTernary2 = Trim(A_LoopField1);
        }
        if (A_Index1 == 152) {
            std::string keyWordInc = Trim(A_LoopField1);
        }
        if (A_Index1 == 153) {
            std::string keyWordDec = Trim(A_LoopField1);
        }
        if (A_Index1 == 154) {
            std::string AHKlikeLoopsIndexedAt = Trim(A_LoopField1);
        }
        if (A_Index1 == 155) {
            std::string keyWordAIndex = Trim(A_LoopField1);
        }
        if (A_Index1 == 156) {
            std::string keyWordALoopField = Trim(A_LoopField1);
        }
        if (A_Index1 == 157) {
            std::string keyWordAllianceEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 158) {
            std::string keyWordCrewEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 159) {
            std::string keyWordMethodEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 160) {
            std::string keyWordDefObjEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 161) {
            std::string keyWordIFEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 162) {
            std::string keyWordElseIfEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 163) {
            std::string keyWordElseEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 164) {
            std::string keyWordSwitchEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 165) {
            std::string keyWordSwitchCaseEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 166) {
            std::string keyWordWhileLoopEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 167) {
            std::string keyWordForLoopEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 168) {
            std::string keyWordLoopInfiniteEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 169) {
            std::string keyWordLoopEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 170) {
            std::string keyWordLoopParseEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 171) {
            std::string keyWordFuncEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 172) {
            std::string keyWordTryEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 173) {
            std::string keyWordCatchEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 174) {
            std::string keyWordFinallyEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 175) {
            std::string useFuncKeyWord = Trim(A_LoopField1);
        }
        if (A_Index1 == 176) {
            std::string useCurlyBraces = Trim(A_LoopField1);
        }
        if (A_Index1 == 177) {
            std::string useEnd = Trim(A_LoopField1);
        }
        if (A_Index1 == 178) {
            std::string useEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 179) {
            std::string useSemicolon = Trim(A_LoopField1);
        }
        if (A_Index1 == 180) {
            std::string useParentheses = Trim(A_LoopField1);
        }
        if (A_Index1 == 181) {
            std::string usePrefixTypeForTypeDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 182) {
            std::string usePostfixTypeForTypeDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 183) {
            std::string usePythonicColonSyntax = Trim(A_LoopField1);
        }
        if (A_Index1 == 184) {
            std::string useInJavaScriptAlwaysUseVar = Trim(A_LoopField1);
        }
        if (A_Index1 == 185) {
            std::string useJavaScriptInAfullHTMLfile = Trim(A_LoopField1);
        }
        if (A_Index1 == 186) {
            std::string useJavaScriptAmainFuncDef = Trim(A_LoopField1);
        }
        if (A_Index1 == 187) {
            std::string useJavaScriptAllFuncsAreAsync = Trim(A_LoopField1);
        }
        if (A_Index1 == 188) {
            std::string useJavaScriptAlwaysTripleEqual = Trim(A_LoopField1);
        }
    }
    if (Trim(langToConvertToParam) != "") {
        langToConvertTo = Trim(langToConvertToParam);
    }
    int isFullHTVMCode = 0;
    if (Trim(mode) == "full") {
        isFullHTVMCode = 1;
    } else {
        isFullHTVMCode = 0;
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
    code = Trim(code);
    if (langToConvertTo == "htvm") {
        HTVMout = "0";
    }
    if (langToConvertTo == "cpp") {
        HTVMout = "0";
    }
    if (langToConvertTo == "py") {
        HTVMout = "0";
    }
    if (langToConvertTo == "js") {
        HTVMout = "0";
    }
    if (langToConvertTo == "go") {
        HTVMout = "0";
    }
    if (langToConvertTo == "lua") {
        HTVMout = "0";
    }
    if (langToConvertTo == "cs") {
        HTVMout = "0";
    }
    if (langToConvertTo == "java") {
        HTVMout = "0";
    }
    if (langToConvertTo == "kt") {
        HTVMout = "0";
    }
    if (langToConvertTo == "rb") {
        HTVMout = "0";
    }
    if (langToConvertTo == "nim") {
        HTVMout = "0";
    }
    if (langToConvertTo == "ahk") {
        HTVMout = "0";
    }
    if (langToConvertTo == "swift") {
        HTVMout = "0";
    }
    if (langToConvertTo == "dart") {
        HTVMout = "0";
    }
    if (langToConvertTo == "ts") {
        HTVMout = "0";
    }
    if (langToConvertTo == "scala") {
        HTVMout = "0";
    }
    if (langToConvertTo == "groovy") {
        HTVMout = "0";
    }
    print(code);
    print(instructionFile);
    print(mode);
    print(langToConvertTo);
    print("==================================");
    print("==================================");
    print("==================================");
    print("==================================");
    print("==================================");
    print(allInstructionFile);
    std::string codeOutFix1 = "";
    std::vector<std::string> items2 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
        std::string A_LoopField2 = items2[A_Index2 - 0];
        codeOutFix1 += Trim(A_LoopField2) + "\n";
    }
    codeOutFix1 = StringTrimRight(codeOutFix1, 1);
    return HTVMout;
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
    std::vector<std::string> items3 = LoopParseFunc(str0);
    for (size_t A_Index3 = 0; A_Index3 < items3.size() + 0; A_Index3++) {
        std::string A_LoopField3 = items3[A_Index3 - 0];
        str00 = Trim(A_LoopField3);
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
        std::vector<std::string> items4 = LoopParseFunc(allArgs, "\n", "\r");
        for (size_t A_Index4 = 0; A_Index4 < items4.size() + 0; A_Index4++) {
            std::string A_LoopField4 = items4[A_Index4 - 0];
            if (A_Index4 == 0) {
                argCODE = FileRead(Trim(A_LoopField4));
                argCODEfile = Trim(A_LoopField4);
            }
            else if (A_Index4 == 1) {
                argHTVMinstr = Trim(A_LoopField4);
            }
            else if (A_Index4 == 2) {
                argLangTo = Trim(A_LoopField4);
            } else {
                argHTVMinstrMOVE.push_back(Trim(A_LoopField4));
            }
        }
        if (argLangTo != "") {
            OUTCODE = compiler(argCODE, argHTVMinstr, "full", argLangTo);
        } else {
            OUTCODE = compiler(argCODE, argHTVMinstr, "full");
        }
        FileDelete(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        FileAppend(OUTCODE, StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
    }
    if (HTVM_getLang_HTVM() == "js") {
        print("JS");
    }
}
int main(int argc, char* argv[]) {
    HTVMv2();
    return 0;
}
