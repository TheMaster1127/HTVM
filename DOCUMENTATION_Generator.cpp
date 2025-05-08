#include <algorithm>
#include <any>
#include <array>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <regex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <system_error>
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
    std::cout << value << std::endl;
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

// Checks if a file or directory exists
bool FileExist(const std::string& path) {
    try {
        return std::filesystem::exists(path);
    } catch (const std::filesystem::filesystem_error&) {
        // Handle errors silently; return false if an error occurs
        return false;
    }
}

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

std::string RunCMD(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;
#if defined(_WIN32)
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
#else
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
#endif
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void ExitApp() {
    std::exit(0);
}

// Function to sort and remove duplicates
std::vector<std::string> sortArr(const std::vector<std::string>& input) {
    std::set<std::string> uniqueSorted(input.begin(), input.end());
    return std::vector<std::string>(uniqueSorted.begin(), uniqueSorted.end());
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

std::string StrTitleCase(const std::string& input) {
    std::string result;
    bool newWord = true;
    for (char ch : input) {
        if (std::isspace(ch)) {
            newWord = true; // next character starts a new word
            result += ch;
        } else if (newWord) {
            result += std::toupper(ch); // capitalize the first letter of the word
            newWord = false;
        } else {
            result += std::tolower(ch); // make other letters lowercase
        }
    }
    return result;
}

std::string HTVM_getLang_HTVM() {
    return "cpp";
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


std::string instructionFileData = "";
std::string DOCS_params = "";
std::string DOCS_param1 = "";
std::string DOCS_param2 = "";
int DOCS_checkIfFuncNameExists = 0;
std::string OUTdocs_HTML = "";
std::string OUTdocs_MD = "";
int htvmSnippetAlredy = 0;
std::string htvmSnippet000 = "";
std::string htvmSnippet00 = "";
std::string htvmSnippet0 = "";
std::string htvmSnippet1 = "";
std::string htvmSnippet2 = "";
std::string htvmSnippet3 = "";
std::string htvmSnippet4 = "";
std::string htvmSnippet5 = "";
std::string htvmSnippet6 = "";
std::string htvmSnippet7 = "";
std::string htvmSnippet8 = "";
std::string htvmSnippet9 = "";
std::string htvmSnippet10 = "";
std::string htvmSnippet11 = "";
std::string htvmSnippet12 = "";
std::string htvmSnippet13 = "";
std::string htvmSnippet14 = "";
std::string htvmSnippet15 = "";
std::string htvmSnippet16 = "";
std::string htvmSnippet17 = "";
std::string htvmSnippet18 = "";
std::string htvmSnippet19 = "";
std::string htvmSnippet20 = "";
std::string htvmSnippet21 = "";
std::string htvmSnippet22 = "";
std::string htvmSnippet23 = "";
std::string htvmSnippet24 = "";
std::string htvmSnippet25 = "";
std::string htvmSnippet26 = "";
std::string htvmSnippet27 = "";
std::string htvmSnippet28 = "";
std::string htvmSnippet29 = "";
std::string htvmSnippet30 = "";
std::string htvmSnippet31 = "";
std::string htvmSnippet32 = "";
std::string htvmSnippet33 = "";
std::string htvmSnippet34 = "";
std::string htvmSnippet35 = "";
std::string htvmSnippet36 = "";
std::string htvmSnippet37 = "";
std::string htvmSnippet38 = "";
std::string htvmSnippet39 = "";
std::string htvmSnippet40 = "";
std::string htvmSnippet41 = "";
std::string htvmSnippet42 = "";
std::string htvmSnippet43 = "";
std::string htvmSnippet44 = "";
std::string htvmSnippet45 = "";
std::string htvmSnippet46 = "";
std::string htvmSnippet47 = "";
std::string htvmSnippet48 = "";
std::string htvmSnippet49 = "";
std::string htvmSnippet50 = "";
std::string htvmSnippet51 = "";
std::string htvmSnippet52 = "";
std::string htvmSnippet53 = "";
std::string htvmSnippet54 = "";
std::string htvmSnippet55 = "";
std::string htvmSnippet56 = "";
std::string htvmSnippet57 = "";
std::string htvmSnippet58 = "";
std::string htvmSnippet59 = "";
std::string htvmSnippet60 = "";
std::string htvmSnippet61 = "";
std::string htvmSnippet62 = "";
std::string htvmSnippet63 = "";
std::string htvmSnippet64 = "";
std::string htvmSnippet65 = "";
std::string htvmSnippet66 = "";
std::string htvmSnippet67 = "";
std::string htvmSnippet68 = "";
std::string htvmSnippet69 = "";
std::string htvmSnippet70 = "";
std::string htvmSnippet71 = "";
std::string htvmSnippet72 = "";
std::string htvmSnippet73 = "";
std::string htvmSnippet74 = "";
std::string htvmSnippet75 = "";
std::string htvmSnippet76 = "";
std::string htvmSnippet77 = "";
std::string htvmSnippet78 = "";
std::string htvmSnippet79 = "";
std::string htvmSnippet80 = "";
std::string htvmSnippet81 = "";
std::string htvmSnippet82 = "";
std::string htvmSnippet83 = "";
std::string htvmSnippet84 = "";
std::string htvmSnippet85 = "";
std::string htvmSnippet86 = "";
std::string htvmSnippet87 = "";
std::string htvmSnippet88 = "";
std::string htvmSnippet89 = "";
std::string htvmSnippet90 = "";
std::string htvmSnippet91 = "";
std::string escapeStr(const std::string& str) {
    std::string encoded;
    for (char c : str) {
        switch (c) {
            case '\\': encoded += "\\\\"; break;
            case '`':  encoded += "\\`"; break;
            case '$':  encoded += "\\$"; break; // Only if preventing `${` interpolation
            case '\n': encoded += "\\n"; break;
            case '\t': encoded += "\\t"; break;
            case '\r': encoded += "\\r"; break;
            default:   encoded += c;
        }
    }
    return encoded;
}


// RunCMD(
#include <iostream>
#include <cstdio>
#include <string>
#include <array>
#include <memory>
#include <stdexcept>
#include <filesystem>
// Function to extract directory path from a full file path
std::string GetDirectoryPath(const std::string& fullPath) {
    std::filesystem::path path(fullPath);
    return path.parent_path().string();  // Returns directory path
}
#include <memory>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <cstdio>
    #include <array>
#endif
std::string convertSnipetToAnotherSyntax(std::string instrFile, std::string codeSnippet) {
    std::string out = "";
    std::string str0 = "";
    std::string instr0 = "";
    std::string instr1 = "";
    std::string instr2 = "";
    std::string instr3 = "";
    std::string instr4 = "";
    std::string directoryPath = "";
    if (HTVM_getLang_HTVM() == "cpp") {
        str0 = "";
        str0 = FileRead(Trim(instrFile));
        std::vector<std::string> items1 = LoopParseFunc(str0, "\n", "\r");
        for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
            std::string A_LoopField1 = items1[A_Index1 - 0];
            if (A_Index1 == 1) {
                instr3 = Trim(A_LoopField1);
                break;
            }
        }
        instr0 = "cpp" + Chr(10) + instr3 + Chr(10) + "StringTrimLeft,OUTVAR,INVAR,param1|StringTrimRight,OUTVAR,INVAR,param1|Random,OUTVAR,param1,param2|Sleep,INVAR|FileRead,OUTVAR,'param1|FileAppend,INVAR,'param1|FileDelete,'INVAR|Sort,INOUTVAR,'param1|MsgBox,'param1" + Chr(10) + "alliance" + Chr(10) + "crew" + Chr(10) + "proc" + Chr(10) + "struct" + Chr(10) + "prop" + Chr(10) + "this" + Chr(10) + "import" + Chr(10) + "___start" + Chr(10) + "___end" + Chr(10) + "___cpp start" + Chr(10) + "___cpp end" + Chr(10) + "___py start" + Chr(10) + "___py end" + Chr(10) + "___js start" + Chr(10) + "___js end" + Chr(10) + "___go start" + Chr(10) + "___go end" + Chr(10) + "___lua start" + Chr(10) + "___lua end" + Chr(10) + "___cs start" + Chr(10) + "___cs end" + Chr(10) + "___java start" + Chr(10) + "___java end" + Chr(10) + "___kt start" + Chr(10) + "___kt end" + Chr(10) + "___rb start" + Chr(10) + "___rb end" + Chr(10) + "___nim start" + Chr(10) + "___nim end" + Chr(10) + "___ahk start" + Chr(10) + "___ahk end" + Chr(10) + "___swift start" + Chr(10) + "___swift end" + Chr(10) + "___dart start" + Chr(10) + "___dart end" + Chr(10) + "___ts start" + Chr(10) + "___ts end" + Chr(10) + "___groovy start" + Chr(10) + "___groovy end" + Chr(10) + "___htvm start" + Chr(10) + "___htvm end" + Chr(10) + "___inhtvm start" + Chr(10) + "___inhtvm end" + Chr(10) + "{" + Chr(10) + "}" + Chr(10) + "null" + Chr(10) + "true" + Chr(10) + "false" + Chr(10) + "void" + Chr(10) + "double" + Chr(10) + "char" + Chr(10) + "uint8" + Chr(10) + "uint16" + Chr(10) + "uint32" + Chr(10) + "uint64" + Chr(10) + "int" + Chr(10) + "str" + Chr(10) + "bool" + Chr(10) + "float" + Chr(10) + "int8" + Chr(10) + "int16" + Chr(10) + "int32" + Chr(10) + "int64" + Chr(10) + "if" + Chr(10) + "else if" + Chr(10) + "else" + Chr(10) + "while" + Chr(10) + "Loop" + Chr(10) + "Loop," + Chr(10) + "Loop, Parse," + Chr(10) + "continue" + Chr(10) + "break" + Chr(10) + "func" + Chr(10) + "await" + Chr(10) + "async" + Chr(10) + "throw" + Chr(10) + "ErrorMsg" + Chr(10) + "try" + Chr(10) + "catch" + Chr(10) + "finally" + Chr(10) + "return" + Chr(10) + ".add" + Chr(10) + ".pop" + Chr(10) + ".size" + Chr(10) + ".insert" + Chr(10) + ".rm" + Chr(10) + ".indexOf" + Chr(10) + "arr" + Chr(10) + "arr int" + Chr(10) + "arr str" + Chr(10) + "arr float" + Chr(10) + "arr bool" + Chr(10) + "var" + Chr(10) + "let" + Chr(10) + "const" + Chr(10) + "end" + Chr(10) + "global" + Chr(10) + ";" + Chr(10) + "'''1" + Chr(10) + "'''2" + Chr(10) + Chr(96) + Chr(10) + "main" + Chr(10) + "." + Chr(10) + "+" + Chr(10) + "-" + Chr(10) + "*" + Chr(10) + "/" + Chr(10) + "%" + Chr(10) + "**" + Chr(10) + "=" + Chr(10) + "===" + Chr(10) + "!=" + Chr(10) + Chr(62) + Chr(10) + Chr(60) + Chr(10) + Chr(62) + "=" + Chr(10) + Chr(60) + "=" + Chr(10) + "and" + Chr(10) + "or" + Chr(10) + "!" + Chr(10) + "&" + Chr(10) + "|" + Chr(10) + "^" + Chr(10) + "~" + Chr(10) + Chr(60) + Chr(60) + Chr(10) + Chr(62) + Chr(62) + Chr(10) + Chr(62) + Chr(62) + Chr(62) + Chr(10) + ":=" + Chr(10) + "+=" + Chr(10) + ".=" + Chr(10) + "-=" + Chr(10) + "*=" + Chr(10) + "/=" + Chr(10) + "%=" + Chr(10) + Chr(60) + Chr(60) + "=" + Chr(10) + Chr(62) + Chr(62) + "=" + Chr(10) + Chr(62) + Chr(62) + Chr(62) + "=" + Chr(10) + "&=" + Chr(10) + "|=" + Chr(10) + "^=" + Chr(10) + "?" + Chr(10) + ":" + Chr(10) + "++" + Chr(10) + "--" + Chr(10) + "0" + Chr(10) + "A_Index" + Chr(10) + "A_LoopField" + Chr(10) + "on" + Chr(10) + "off" + Chr(10) + "off" + Chr(10) + "on" + Chr(10) + "on" + Chr(10) + "off" + Chr(10) + "off" + Chr(10) + "off" + Chr(10) + "on" + Chr(10) + "off" + Chr(10) + "off" + Chr(10) + "on" + Chr(10) + "off" + Chr(10) + Chr(10);
        FileDelete("HTVM-Instr-temp.txt");
        FileDelete("HTVM-code-temp." + instr3);
        FileAppend(Trim(instr0), "HTVM-Instr-temp.txt");
        FileAppend(Trim(codeSnippet), "HTVM-code-temp." + instr3);
        // Extract directory path from instrFile
        directoryPath = GetDirectoryPath(instrFile);
        instr1 = directoryPath + "/" + "HTVM-code-temp." + instr3;
        instr2 = instrFile;
        // instr3
        instr4 = directoryPath + "/" + "HTVM-Instr-temp.txt";
        print("Waiting for all code snippets to convert using the HTVM binary, so this might take a while...");
            // Construct the command to run HTVM.exe or ./HTVM depending on the platform
    std::string command;
#if defined(_WIN32)
    command = "HTVM.exe \"" + instr1 + "\" \"" + instr4 + "\" \"" + instr3 + "\" \"" + instr2 + "\"";
#else
    command = "./HTVM \"" + instr1 + "\" \"" + instr4+ "\" \"" + instr3 + "\" \"" + instr2 + "\"";
#endif
    //std::cout << "Running command: " << command << std::endl;  // Output the command for debugging
    try {
        // Run the command and capture the output
        std::string output = RunCMD(command);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
        out = FileRead("HTVM-code-temp." + instr3);
        FileDelete("HTVM-Instr-temp.txt");
        FileDelete("HTVM-code-temp." + instr3);
    }
    std::string fixInstrFile = "";
    if (HTVM_getLang_HTVM() == "js") {
        str0 = "";
        

        fixInstrFile = "";
        std::vector<std::string> items2 = LoopParseFunc(instrFile, "\n", "\r");
        for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
            std::string A_LoopField2 = items2[A_Index2 - 0];
            if (A_Index2 == 1) {
                fixInstrFile += "htvm" + Chr(10);
            } else {
                fixInstrFile += Trim(A_LoopField2) + Chr(10);
            }
        }
        instrFile = StringTrimRight(fixInstrFile, 1);
        instr1 = Trim(codeSnippet);
        instr4 = Trim(instrFile);
        instr3 = "htvm";
        instr2 = Trim(instr0);
        

    }
    return out;
}
void htvmSnippetLoad() {
    int numTemp = 0;
    if (htvmSnippetAlredy != 1) {
        htvmSnippetAlredy = 1;
        if (HTVM_getLang_HTVM() == "cpp") {
            htvmSnippet000 = "";
            htvmSnippet00 = "";
            htvmSnippet0 = "";
            htvmSnippet1 = "";
            htvmSnippet2 = "";
            htvmSnippet3 = "";
            htvmSnippet4 = "";
            htvmSnippet5 = "";
            htvmSnippet6 = "";
            htvmSnippet7 = "";
            htvmSnippet8 = "";
            htvmSnippet9 = "";
            htvmSnippet10 = "";
            htvmSnippet11 = "";
            htvmSnippet12 = "";
            htvmSnippet13 = "";
            htvmSnippet14 = "";
            htvmSnippet15 = "";
            htvmSnippet16 = "";
            htvmSnippet17 = "";
            htvmSnippet18 = "";
            htvmSnippet19 = "";
            htvmSnippet20 = "";
            htvmSnippet21 = "";
            htvmSnippet22 = "";
            htvmSnippet23 = "";
            htvmSnippet24 = "";
            htvmSnippet25 = "";
            htvmSnippet26 = "";
            htvmSnippet27 = "";
            htvmSnippet28 = "";
            htvmSnippet29 = "";
            htvmSnippet30 = "";
            htvmSnippet31 = "";
            htvmSnippet32 = "";
            htvmSnippet33 = "";
            htvmSnippet34 = "";
            htvmSnippet35 = "";
            htvmSnippet36 = "";
            htvmSnippet37 = "";
            htvmSnippet38 = "";
            htvmSnippet39 = "";
            htvmSnippet40 = "";
            htvmSnippet41 = "";
            htvmSnippet42 = "";
            htvmSnippet43 = "";
            htvmSnippet44 = "";
            htvmSnippet45 = "";
            htvmSnippet46 = "";
            htvmSnippet47 = "";
            htvmSnippet48 = "";
            htvmSnippet49 = "";
            htvmSnippet50 = "";
            htvmSnippet51 = "";
            htvmSnippet52 = "";
            htvmSnippet53 = "";
            htvmSnippet54 = "";
            htvmSnippet55 = "";
            htvmSnippet56 = "";
            htvmSnippet57 = "";
            htvmSnippet58 = "";
            htvmSnippet59 = "";
            htvmSnippet60 = "";
            htvmSnippet61 = "";
            htvmSnippet62 = "";
            htvmSnippet63 = "";
            htvmSnippet64 = "";
            htvmSnippet65 = "";
            htvmSnippet66 = "";
            htvmSnippet67 = "";
            htvmSnippet68 = "";
            htvmSnippet69 = "";
            htvmSnippet70 = "";
            htvmSnippet71 = "";
            htvmSnippet72 = "";
            htvmSnippet73 = "";
            htvmSnippet74 = "";
            htvmSnippet75 = "";
            htvmSnippet76 = "";
            htvmSnippet77 = "";
            htvmSnippet78 = "";
            htvmSnippet79 = "";
            htvmSnippet80 = "";
            htvmSnippet81 = "";
            htvmSnippet82 = "";
            htvmSnippet83 = "";
            htvmSnippet84 = "";
            htvmSnippet85 = "";
            htvmSnippet86 = "";
            htvmSnippet87 = "";
            htvmSnippet88 = "";
            htvmSnippet89 = "";
            htvmSnippet90 = "";
            htvmSnippet91 = "";
            htvmSnippet00 = FileRead("DOCUMENTATION Examples\\htvmSnippet0.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet1.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet2.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet3.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet4.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet5.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet6.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet7.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet8.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet9.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet10.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet11.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet12.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet13.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet14.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet15.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet16.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet17.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet18.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet19.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet20.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet21.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet22.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet23.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet24.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet25.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet26.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet27.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet28.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet29.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet30.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet31.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet32.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet33.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet34.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet35.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet36.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet37.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet38.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet39.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet40.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet41.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet42.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet43.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet44.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet45.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet46.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet47.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet48.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet49.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet50.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet51.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet52.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet53.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet54.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet55.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet56.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet57.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet58.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet59.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet60.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet61.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet62.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet63.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet64.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet65.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet66.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet67.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet68.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet69.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet70.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet71.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet72.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet73.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet74.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet75.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet76.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet77.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet78.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet79.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet80.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet81.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet82.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet83.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet84.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet85.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 += FileRead("DOCUMENTATION Examples\\htvmSnippet86.htvm") + Chr(10) + "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2" + Chr(10);
            htvmSnippet00 = convertSnipetToAnotherSyntax(DOCS_param1, htvmSnippet00);
            numTemp = 0;
            htvmSnippet000 = "";
            std::vector<std::string> items3 = LoopParseFunc(htvmSnippet00, "\n", "\r");
            for (size_t A_Index3 = 0; A_Index3 < items3.size() + 0; A_Index3++) {
                std::string A_LoopField3 = items3[A_Index3 - 0];
                if (numTemp == 1 && Trim(htvmSnippet0) == "") {
                    htvmSnippet0 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet0 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 2 && Trim(htvmSnippet1) == "") {
                    htvmSnippet1 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet1 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 3 && Trim(htvmSnippet2) == "") {
                    htvmSnippet2 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet2 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 4 && Trim(htvmSnippet3) == "") {
                    htvmSnippet3 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet3 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 5 && Trim(htvmSnippet4) == "") {
                    htvmSnippet4 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet4 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 6 && Trim(htvmSnippet5) == "") {
                    htvmSnippet5 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet5 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 7 && Trim(htvmSnippet6) == "") {
                    htvmSnippet6 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet6 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 8 && Trim(htvmSnippet7) == "") {
                    htvmSnippet7 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet7 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 9 && Trim(htvmSnippet8) == "") {
                    htvmSnippet8 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet8 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 10 && Trim(htvmSnippet9) == "") {
                    htvmSnippet9 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet9 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 11 && Trim(htvmSnippet10) == "") {
                    htvmSnippet10 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet10 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 12 && Trim(htvmSnippet11) == "") {
                    htvmSnippet11 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet11 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 13 && Trim(htvmSnippet12) == "") {
                    htvmSnippet12 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet12 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 14 && Trim(htvmSnippet13) == "") {
                    htvmSnippet13 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet13 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 15 && Trim(htvmSnippet14) == "") {
                    htvmSnippet14 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet14 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 16 && Trim(htvmSnippet15) == "") {
                    htvmSnippet15 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet15 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 17 && Trim(htvmSnippet16) == "") {
                    htvmSnippet16 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet16 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 18 && Trim(htvmSnippet17) == "") {
                    htvmSnippet17 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet17 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 19 && Trim(htvmSnippet18) == "") {
                    htvmSnippet18 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet18 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 20 && Trim(htvmSnippet19) == "") {
                    htvmSnippet19 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet19 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 21 && Trim(htvmSnippet20) == "") {
                    htvmSnippet20 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet20 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 22 && Trim(htvmSnippet21) == "") {
                    htvmSnippet21 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet21 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 23 && Trim(htvmSnippet22) == "") {
                    htvmSnippet22 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet22 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 24 && Trim(htvmSnippet23) == "") {
                    htvmSnippet23 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet23 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 25 && Trim(htvmSnippet24) == "") {
                    htvmSnippet24 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet24 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 26 && Trim(htvmSnippet25) == "") {
                    htvmSnippet25 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet25 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 27 && Trim(htvmSnippet26) == "") {
                    htvmSnippet26 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet26 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 28 && Trim(htvmSnippet27) == "") {
                    htvmSnippet27 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet27 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 29 && Trim(htvmSnippet28) == "") {
                    htvmSnippet28 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet28 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 30 && Trim(htvmSnippet29) == "") {
                    htvmSnippet29 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet29 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 31 && Trim(htvmSnippet30) == "") {
                    htvmSnippet30 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet30 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 32 && Trim(htvmSnippet31) == "") {
                    htvmSnippet31 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet31 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 33 && Trim(htvmSnippet32) == "") {
                    htvmSnippet32 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet32 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 34 && Trim(htvmSnippet33) == "") {
                    htvmSnippet33 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet33 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 35 && Trim(htvmSnippet34) == "") {
                    htvmSnippet34 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet34 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 36 && Trim(htvmSnippet35) == "") {
                    htvmSnippet35 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet35 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 37 && Trim(htvmSnippet36) == "") {
                    htvmSnippet36 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet36 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 38 && Trim(htvmSnippet37) == "") {
                    htvmSnippet37 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet37 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 39 && Trim(htvmSnippet38) == "") {
                    htvmSnippet38 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet38 += Chr(10);
                    htvmSnippet000 = "";
                }
                //;;;;;;;;;;;;
                else if (numTemp == 40 && Trim(htvmSnippet39) == "") {
                    htvmSnippet39 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet39 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 41 && Trim(htvmSnippet40) == "") {
                    htvmSnippet40 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet40 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 42 && Trim(htvmSnippet41) == "") {
                    htvmSnippet41 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet41 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 43 && Trim(htvmSnippet42) == "") {
                    htvmSnippet42 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet42 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 44 && Trim(htvmSnippet43) == "") {
                    htvmSnippet43 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet43 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 45 && Trim(htvmSnippet44) == "") {
                    htvmSnippet44 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet44 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 46 && Trim(htvmSnippet45) == "") {
                    htvmSnippet45 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet45 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 47 && Trim(htvmSnippet46) == "") {
                    htvmSnippet46 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet46 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 48 && Trim(htvmSnippet47) == "") {
                    htvmSnippet47 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet47 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 49 && Trim(htvmSnippet48) == "") {
                    htvmSnippet48 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet48 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 50 && Trim(htvmSnippet49) == "") {
                    htvmSnippet49 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet49 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 51 && Trim(htvmSnippet50) == "") {
                    htvmSnippet50 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet50 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 52 && Trim(htvmSnippet51) == "") {
                    htvmSnippet51 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet51 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 53 && Trim(htvmSnippet52) == "") {
                    htvmSnippet52 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet52 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 54 && Trim(htvmSnippet53) == "") {
                    htvmSnippet53 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet53 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 55 && Trim(htvmSnippet54) == "") {
                    htvmSnippet54 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet54 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 56 && Trim(htvmSnippet55) == "") {
                    htvmSnippet55 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet55 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 57 && Trim(htvmSnippet56) == "") {
                    htvmSnippet56 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet56 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 58 && Trim(htvmSnippet57) == "") {
                    htvmSnippet57 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet57 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 59 && Trim(htvmSnippet58) == "") {
                    htvmSnippet58 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet58 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 60 && Trim(htvmSnippet59) == "") {
                    htvmSnippet59 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet59 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 61 && Trim(htvmSnippet60) == "") {
                    htvmSnippet60 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet60 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 62 && Trim(htvmSnippet61) == "") {
                    htvmSnippet61 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet61 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 63 && Trim(htvmSnippet62) == "") {
                    htvmSnippet62 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet62 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 64 && Trim(htvmSnippet63) == "") {
                    htvmSnippet63 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet63 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 65 && Trim(htvmSnippet64) == "") {
                    htvmSnippet64 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet64 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 66 && Trim(htvmSnippet65) == "") {
                    htvmSnippet65 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet65 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 67 && Trim(htvmSnippet66) == "") {
                    htvmSnippet66 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet66 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 68 && Trim(htvmSnippet67) == "") {
                    htvmSnippet67 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet67 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 69 && Trim(htvmSnippet68) == "") {
                    htvmSnippet68 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet68 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 70 && Trim(htvmSnippet69) == "") {
                    htvmSnippet69 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet69 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 71 && Trim(htvmSnippet70) == "") {
                    htvmSnippet70 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet70 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 72 && Trim(htvmSnippet71) == "") {
                    htvmSnippet71 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet71 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 73 && Trim(htvmSnippet72) == "") {
                    htvmSnippet72 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet72 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 74 && Trim(htvmSnippet73) == "") {
                    htvmSnippet73 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet73 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 75 && Trim(htvmSnippet74) == "") {
                    htvmSnippet74 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet74 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 76 && Trim(htvmSnippet75) == "") {
                    htvmSnippet75 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet75 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 77 && Trim(htvmSnippet76) == "") {
                    htvmSnippet76 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet76 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 78 && Trim(htvmSnippet77) == "") {
                    htvmSnippet77 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet77 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 79 && Trim(htvmSnippet78) == "") {
                    htvmSnippet78 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet78 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 80 && Trim(htvmSnippet79) == "") {
                    htvmSnippet79 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet79 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 81 && Trim(htvmSnippet80) == "") {
                    htvmSnippet80 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet80 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 82 && Trim(htvmSnippet81) == "") {
                    htvmSnippet81 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet81 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 83 && Trim(htvmSnippet82) == "") {
                    htvmSnippet82 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet82 += Chr(10);
                    htvmSnippet000 = "";
                }
                else if (numTemp == 84 && Trim(htvmSnippet83) == "") {
                    htvmSnippet83 = StringTrimRight(htvmSnippet000, 1);
                    htvmSnippet83 += Chr(10);
                    htvmSnippet000 = "";
                }
                if (Trim(A_LoopField3) != "HTVMv2-help-DOC-get-ThisOnly-For-DOC-GEN-HTVMv2") {
                    htvmSnippet000 += A_LoopField3 + Chr(10);
                } else {
                    numTemp++;
                }
            }
        } else {
            htvmSnippet000 = "";
            htvmSnippet00 = "";
            htvmSnippet0 = "";
            htvmSnippet1 = "";
            htvmSnippet2 = "";
            htvmSnippet3 = "";
            htvmSnippet4 = "";
            htvmSnippet5 = "";
            htvmSnippet6 = "";
            htvmSnippet7 = "";
            htvmSnippet8 = "";
            htvmSnippet9 = "";
            htvmSnippet10 = "";
            htvmSnippet11 = "";
            htvmSnippet12 = "";
            htvmSnippet13 = "";
            htvmSnippet14 = "";
            htvmSnippet15 = "";
            htvmSnippet16 = "";
            htvmSnippet17 = "";
            htvmSnippet18 = "";
            htvmSnippet19 = "";
            htvmSnippet20 = "";
            htvmSnippet21 = "";
            htvmSnippet22 = "";
            htvmSnippet23 = "";
            htvmSnippet24 = "";
            htvmSnippet25 = "";
            htvmSnippet26 = "";
            htvmSnippet27 = "";
            htvmSnippet28 = "";
            htvmSnippet29 = "";
            htvmSnippet30 = "";
            htvmSnippet31 = "";
            htvmSnippet32 = "";
            htvmSnippet33 = "";
            htvmSnippet34 = "";
            htvmSnippet35 = "";
            htvmSnippet36 = "";
            htvmSnippet37 = "";
            htvmSnippet38 = "";
            htvmSnippet39 = "";
            htvmSnippet40 = "";
            htvmSnippet41 = "";
            htvmSnippet42 = "";
            htvmSnippet43 = "";
            htvmSnippet44 = "";
            htvmSnippet45 = "";
            htvmSnippet46 = "";
            htvmSnippet47 = "";
            htvmSnippet48 = "";
            htvmSnippet49 = "";
            htvmSnippet50 = "";
            htvmSnippet51 = "";
            htvmSnippet52 = "";
            htvmSnippet53 = "";
            htvmSnippet54 = "";
            htvmSnippet55 = "";
            htvmSnippet56 = "";
            htvmSnippet57 = "";
            htvmSnippet58 = "";
            htvmSnippet59 = "";
            htvmSnippet60 = "";
            htvmSnippet61 = "";
            htvmSnippet62 = "";
            htvmSnippet63 = "";
            htvmSnippet64 = "";
            htvmSnippet65 = "";
            htvmSnippet66 = "";
            htvmSnippet67 = "";
            htvmSnippet68 = "";
            htvmSnippet69 = "";
            htvmSnippet70 = "";
            htvmSnippet71 = "";
            htvmSnippet72 = "";
            htvmSnippet73 = "";
            htvmSnippet74 = "";
            htvmSnippet75 = "";
            htvmSnippet76 = "";
            htvmSnippet77 = "";
            htvmSnippet78 = "";
            htvmSnippet79 = "";
            htvmSnippet80 = "";
            htvmSnippet81 = "";
            htvmSnippet82 = "";
            htvmSnippet83 = "";
            htvmSnippet84 = "";
            htvmSnippet85 = "";
            htvmSnippet86 = "";
            htvmSnippet87 = "";
            htvmSnippet88 = "";
            htvmSnippet89 = "";
            htvmSnippet90 = "";
            htvmSnippet91 = "";
            

        }
    }
}


std::string escapeForMarkdownTable(const std::string& input) {
    std::ostringstream escaped;
    for (char c : input) {
        switch (c) {
            case '&': escaped << "&amp;"; break;
            case '|': escaped << "&#124;"; break;
            case '<': escaped << "&lt;"; break;
            case '>': escaped << "&gt;"; break;
            case '\'': escaped << "&#39;"; break;
            case '\\': escaped << "\\\\"; break;
            case '\n': escaped << "<br>"; break;
            default: escaped << c;
        }
    }
    return escaped.str();
}
std::string escapeForMarkdownTable2(std::string line) {
    std::string lineOut = "";
    if (InStr(line, Chr(39))) {
        std::vector<std::string> items4 = LoopParseFunc(line);
        for (size_t A_Index4 = 0; A_Index4 < items4.size() + 0; A_Index4++) {
            std::string A_LoopField4 = items4[A_Index4 - 0];
            lineOut += Chr(96) + A_LoopField4;
        }
        return lineOut;
    }
    line = StrReplace(line, "&", "&amp;");
    line = StrReplace(line, "<", "&lt;");
    line = StrReplace(line, ">", "&gt;");
    line = StrReplace(line, "\\", "\\\\");
    line = StrReplace(line, "|", "\\|");
    return line;
}
std::string makeCommandsTextHELP(std::string line) {
    std::string out = "";
    line = Trim(line);
    std::vector<std::string> items5 = LoopParseFunc(line, ",");
    for (size_t A_Index5 = 0; A_Index5 < items5.size() + 0; A_Index5++) {
        std::string A_LoopField5 = items5[A_Index5 - 0];
        out += A_LoopField5 + ", ";
    }
    out = StringTrimRight(out, 2);
    return out;
}
std::string makeCommandsText(std::string commands) {
    std::string out = "";
    // posible params and stuff
    //;;;;;;;;;;;;;;;;;;;;;;;;;
    // OUTVAR
    // INVAR
    // INOUTVAR
    // '
    // just param
    // and lineTranspile
    commands = Trim(StrReplace(commands, ", ", ","));
    int num = 0;
    std::vector<std::string> items6 = LoopParseFunc(commands, "|");
    for (size_t A_Index6 = 0; A_Index6 < items6.size() + 0; A_Index6++) {
        std::string A_LoopField6 = items6[A_Index6 - 0];
        if (Trim(A_LoopField6) != "") {
            out += Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + makeCommandsTextHELP(A_LoopField6) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10);
        }
    }
    return out;
}
std::string genDocs(std::string mode) {
    std::string outDocs = "";
    if (Trim(instructionFileData) == "") {
        throw std::runtime_error("instructionFileData is empty");
        return "error: instructionFileData is empty!!!";
    }
    std::string allInstrDocName = "langToConvertTo" + Chr(10) + "langFileExtension" + Chr(10) + "commands" + Chr(10) + "keyWordAlliance" + Chr(10) + "keyWordCrew" + Chr(10) + "keyWordProc" + Chr(10) + "keyWordStruct" + Chr(10) + "keyWordProp" + Chr(10) + "keyWordThis" + Chr(10) + "keyWordInclude" + Chr(10) + "keyWordCodeInTheTranspiledLangStart" + Chr(10) + "keyWordCodeInTheTranspiledLangEnd" + Chr(10) + "keyWordCodeInTheTranspiledLangStartCPP" + Chr(10) + "keyWordCodeInTheTranspiledLangEndCPP" + Chr(10) + "keyWordCodeInTheTranspiledLangStartPY" + Chr(10) + "keyWordCodeInTheTranspiledLangEndPY" + Chr(10) + "keyWordCodeInTheTranspiledLangStartJS" + Chr(10) + "keyWordCodeInTheTranspiledLangEndJS" + Chr(10) + "keyWordCodeInTheTranspiledLangStartGO" + Chr(10) + "keyWordCodeInTheTranspiledLangEndGO" + Chr(10) + "keyWordCodeInTheTranspiledLangStartLUA" + Chr(10) + "keyWordCodeInTheTranspiledLangEndLUA" + Chr(10) + "keyWordCodeInTheTranspiledLangStartCS" + Chr(10) + "keyWordCodeInTheTranspiledLangEndCS" + Chr(10) + "keyWordCodeInTheTranspiledLangStartJAVA" + Chr(10) + "keyWordCodeInTheTranspiledLangEndJAVA" + Chr(10) + "keyWordCodeInTheTranspiledLangStartKT" + Chr(10) + "keyWordCodeInTheTranspiledLangEndKT" + Chr(10) + "keyWordCodeInTheTranspiledLangStartRB" + Chr(10) + "keyWordCodeInTheTranspiledLangEndRB" + Chr(10) + "keyWordCodeInTheTranspiledLangStartNIM" + Chr(10) + "keyWordCodeInTheTranspiledLangEndNIM" + Chr(10) + "keyWordCodeInTheTranspiledLangStartAHK" + Chr(10) + "keyWordCodeInTheTranspiledLangEndAHK" + Chr(10) + "keyWordCodeInTheTranspiledLangStartSWIFT" + Chr(10) + "keyWordCodeInTheTranspiledLangEndSWIFT" + Chr(10) + "keyWordCodeInTheTranspiledLangStartDART" + Chr(10) + "keyWordCodeInTheTranspiledLangEndDART" + Chr(10) + "keyWordCodeInTheTranspiledLangStartTS" + Chr(10) + "keyWordCodeInTheTranspiledLangEndTS" + Chr(10) + "keyWordCodeInTheTranspiledLangStartGROOVY" + Chr(10) + "keyWordCodeInTheTranspiledLangEndGROOVY" + Chr(10) + "keyWordCodeInTheTranspiledLangStartHTVM" + Chr(10) + "keyWordCodeInTheTranspiledLangEndHTVM" + Chr(10) + "keyWordCodeInHTVMstart" + Chr(10) + "keyWordCodeInHTVMend" + Chr(10) + "keyWordCurlyBraceOpen" + Chr(10) + "keyWordCurlyBraceClose" + Chr(10) + "keyWordNull" + Chr(10) + "keyWordTrue" + Chr(10) + "keyWordFalse" + Chr(10) + "keyWordVoid" + Chr(10) + "keyWordDouble" + Chr(10) + "keyWordChar" + Chr(10) + "keyWordUint8" + Chr(10) + "keyWordUint16" + Chr(10) + "keyWordUint32" + Chr(10) + "keyWordUint64" + Chr(10) + "keyWordINT" + Chr(10) + "keyWordSTR" + Chr(10) + "keyWordBOOL" + Chr(10) + "keyWordFLOAT" + Chr(10) + "keyWordINT8" + Chr(10) + "keyWordINT16" + Chr(10) + "keyWordINT32" + Chr(10) + "keyWordINT64" + Chr(10) + "keyWordIF" + Chr(10) + "keyWordElseIf" + Chr(10) + "keyWordElse" + Chr(10) + "keyWordWhileLoop" + Chr(10) + "keyWordLoopInfinite" + Chr(10) + "keyWordLoop" + Chr(10) + "keyWordLoopParse" + Chr(10) + "keyWordContinue" + Chr(10) + "keyWordBreak" + Chr(10) + "keyWordFunc" + Chr(10) + "keyWordAwait" + Chr(10) + "keyWordAsync" + Chr(10) + "keyWordThrow" + Chr(10) + "keyWordErrorMsg" + Chr(10) + "keyWordTry" + Chr(10) + "keyWordCatch" + Chr(10) + "keyWordFinally" + Chr(10) + "keyWordReturnStatement" + Chr(10) + "keyWordArrayAppend" + Chr(10) + "keyWordArrayPop" + Chr(10) + "keyWordArraySize" + Chr(10) + "keyWordArrayInsert" + Chr(10) + "keyWordArrayRemove" + Chr(10) + "keyWordArrayIndexOf" + Chr(10) + "keyWordArrayDefinition" + Chr(10) + "keyWordArrayOfIntegersDefinition" + Chr(10) + "keyWordArrayOfStringsDefinition" + Chr(10) + "keyWordArrayOfFloatingPointNumbersDefinition" + Chr(10) + "keyWordArrayOfBooleansDefinition" + Chr(10) + "keyWordVar" + Chr(10) + "keyWordLet" + Chr(10) + "keyWordConst" + Chr(10) + "keyWordEnd" + Chr(10) + "keyWordGlobal" + Chr(10) + "keyWordComment" + Chr(10) + "keyWordCommentOpenMultiLine" + Chr(10) + "keyWordCommentCloseMultiLine" + Chr(10) + "keyWordEscpaeChar" + Chr(10) + "keyWordMainLabel" + Chr(10) + "keyWordConcat" + Chr(10) + "keyWordAdd" + Chr(10) + "keyWordSub" + Chr(10) + "keyWordMul" + Chr(10) + "keyWordDiv" + Chr(10) + "keyWordMod" + Chr(10) + "keyWordExp" + Chr(10) + "keyWordEqual" + Chr(10) + "keyWordStrictEqual" + Chr(10) + "keyWordNotEqual" + Chr(10) + "keyWordGreater" + Chr(10) + "keyWordLess" + Chr(10) + "keyWordGreaterEqual" + Chr(10) + "keyWordLessEqual" + Chr(10) + "keyWordAnd" + Chr(10) + "keyWordOr" + Chr(10) + "keyWordNot" + Chr(10) + "keyWordBitAnd" + Chr(10) + "keyWordBitOr" + Chr(10) + "keyWordBitXor" + Chr(10) + "keyWordBitNot" + Chr(10) + "keyWordShiftLeft" + Chr(10) + "keyWordShiftRight" + Chr(10) + "keyWordShiftUnsignedRight" + Chr(10) + "keyWordAssign" + Chr(10) + "keyWordAssignAdd" + Chr(10) + "keyWordAssignConcat" + Chr(10) + "keyWordAssignSub" + Chr(10) + "keyWordAssignMul" + Chr(10) + "keyWordAssignDiv" + Chr(10) + "keyWordAssignMod" + Chr(10) + "keyWordAssignShiftLeft" + Chr(10) + "keyWordAssignShiftRight" + Chr(10) + "keyWordLogicalAssignShiftRight" + Chr(10) + "keyWordAssignBitAnd" + Chr(10) + "keyWordAssignBitOr" + Chr(10) + "keyWordAssignBitXor" + Chr(10) + "keyWordTernary1" + Chr(10) + "keyWordTernary2" + Chr(10) + "keyWordInc" + Chr(10) + "keyWordDec" + Chr(10) + "AHKlikeLoopsIndexedAt" + Chr(10) + "keyWordAIndex" + Chr(10) + "keyWordALoopField" + Chr(10) + "useCurlyBraces" + Chr(10) + "useEnd" + Chr(10) + "useSemicolon" + Chr(10) + "useParentheses" + Chr(10) + "usePrefixTypeForTypeDefinition" + Chr(10) + "usePostfixTypeForTypeDefinition" + Chr(10) + "usePythonicColonSyntax" + Chr(10) + "useCurlyBracesSyntaxForArrayDef" + Chr(10) + "useInJavaScriptAlwaysUseVar" + Chr(10) + "useJavaScriptInAfullHTMLfile" + Chr(10) + "useJavaScriptAmainFuncDef" + Chr(10) + "useJavaScriptAllFuncsAreAsync" + Chr(10) + "useJavaScriptAlwaysTripleEqual";
    std::vector<std::string> allInstrDocNameArray;
    std::vector<std::string> items7 = LoopParseFunc(allInstrDocName, "\n", "\r");
    for (size_t A_Index7 = 0; A_Index7 < items7.size() + 0; A_Index7++) {
        std::string A_LoopField7 = items7[A_Index7 - 0];
        HTVM_Append(allInstrDocNameArray, A_LoopField7);
    }
    std::string allSyntax = "";
    if (mode == "html") {
        //;;;;;;;;;;;;;;;;;;;;;;;;; html
        //;;;;;;;;;;;;;;;;;;;;;;;;; html
        //;;;;;;;;;;;;;;;;;;;;;;;;; html
        //;;;;;;;;;;;;;;;;;;;;;;;;; html
        //;;;;;;;;;;;;;;;;;;;;;;;;; html
        //;;;;;;;;;;;;;;;;;;;;;;;;; html
        allSyntax = "<pre>" + Chr(10) + "| kewWordName                                   | Syntax                               |" + Chr(10) + "|-----------------------------------------------|-----------------------------------|" + Chr(10) + "| ";
        std::vector<std::string> items8 = LoopParseFunc(instructionFileData, "\n", "\r");
        for (size_t A_Index8 = 0; A_Index8 < items8.size() + 0; A_Index8++) {
            std::string A_LoopField8 = items8[A_Index8 - 0];
            if (A_Index8 == 162) {
                break;
            }
            if (A_Index8 == 2) {
                allSyntax += " " + allInstrDocNameArray[A_Index8] + "  | " + StrReplace(Trim(A_LoopField8), "|", " \\| ") + "        |" + Chr(10) + "| ";
            } else {
                allSyntax += " " + allInstrDocNameArray[A_Index8] + "  | " + escapeForMarkdownTable2(Trim(A_LoopField8)) + "        |" + Chr(10) + "| ";
            }
            //escapeForMarkdownTable
        }
        allSyntax = StringTrimRight(allSyntax, 2);
        allSyntax += "<pre>" + Chr(10);
    } else {
        //;;;;;;;;;;;;;;;;;;;;;;;;; md
        //;;;;;;;;;;;;;;;;;;;;;;;;; md
        //;;;;;;;;;;;;;;;;;;;;;;;;; md
        //;;;;;;;;;;;;;;;;;;;;;;;;; md
        //;;;;;;;;;;;;;;;;;;;;;;;;; md
        //;;;;;;;;;;;;;;;;;;;;;;;;; md
        allSyntax = "| kewWordName                                   | Syntax                               |" + Chr(10) + "|-----------------------------------------------|-----------------------------------|" + Chr(10) + "| ";
        std::vector<std::string> items9 = LoopParseFunc(instructionFileData, "\n", "\r");
        for (size_t A_Index9 = 0; A_Index9 < items9.size() + 0; A_Index9++) {
            std::string A_LoopField9 = items9[A_Index9 - 0];
            if (A_Index9 == 162) {
                break;
            }
            if (A_Index9 == 2) {
                allSyntax += " " + allInstrDocNameArray[A_Index9] + "  | " + StrReplace(Trim(A_LoopField9), "|", " &#124; ") + "        |" + Chr(10) + "| ";
            } else {
                allSyntax += " " + allInstrDocNameArray[A_Index9] + "  | " + escapeForMarkdownTable(Trim(A_LoopField9)) + "        |" + Chr(10) + "| ";
            }
            //escapeForMarkdownTable
        }
        allSyntax = StringTrimRight(allSyntax, 2);
    }
    int inFunc = 0;
    std::vector<std::string> funcData_lang;
    std::vector<std::string> funcData_name;
    std::vector<std::string> funcData_desc;
    std::string on_useCurlyBraces = "";
    std::string on_useEnd = "";
    std::string on_useSemicolon = "";
    std::string on_useParentheses = "";
    std::string on_usePrefixTypeForTypeDefinition = "";
    std::string on_usePostfixTypeForTypeDefinition = "";
    std::string on_usePythonicColonSyntax = "";
    std::string on_useCurlyBracesSyntaxForArrayDef = "";
    std::string on_useInJavaScriptAlwaysUseVar = "";
    std::string on_useJavaScriptInAfullHTMLfile = "";
    std::string on_useJavaScriptAmainFuncDef = "";
    std::string on_useJavaScriptAllFuncsAreAsync = "";
    std::string on_useJavaScriptAlwaysTripleEqual = "";
    std::string doc_keyWordArrayAppend = "";
    std::string doc_keyWordArrayPop = "";
    std::string doc_keyWordArraySize = "";
    std::string doc_keyWordArrayInsert = "";
    std::string doc_keyWordArrayRemove = "";
    std::string doc_keyWordArrayIndexOf = "";
    std::string doc_keyWordArrayDefinition = "";
    std::string doc_keyWordArrayOfIntegersDefinition = "";
    std::string doc_keyWordArrayOfStringsDefinition = "";
    std::string doc_keyWordArrayOfFloatingPointNumbersDefinition = "";
    std::string doc_keyWordArrayOfBooleansDefinition = "";
    std::string htvmOpenPrgBlock = "";
    std::string htvmClosePrgBlock = "";
    std::string doc_keyWordWhileLoop = "";
    std::string doc_keyWordLoopInfinite = "";
    std::string doc_keyWordLoop = "";
    std::string doc_keyWordLoopParse = "";
    std::string doc_keyWordContinue = "";
    std::string doc_keyWordBreak = "";
    std::string doc_keyWordAIndex = "";
    std::string doc_keyWordALoopField = "";
    std::string doc_keyWordComment = "";
    std::string doc_keyWordCommentOpenMultiLine = "";
    std::string doc_keyWordCommentCloseMultiLine = "";
    std::string doc_funcKeyWord = "";
    std::string doc_keyWordErrorMsg = "";
    std::string doc_keyWordTry = "";
    std::string doc_keyWordCatch = "";
    std::string doc_keyWordFinally = "";
    std::string doc_keyWordInclude = "";
    std::string allCommandsDoc = "";
    std::vector<std::string> items10 = LoopParseFunc(instructionFileData, "\n", "\r");
    for (size_t A_Index10 = 0; A_Index10 < items10.size() + 0; A_Index10++) {
        std::string A_LoopField10 = items10[A_Index10 - 0];
        if (A_Index10 == 2) {
            allCommandsDoc = makeCommandsText(Trim(A_LoopField10));
        }
        if (A_Index10 == 9) {
            doc_keyWordInclude = Trim(A_LoopField10);
        }
        if (A_Index10 == 44) {
            htvmOpenPrgBlock = Trim(A_LoopField10);
        }
        if (A_Index10 == 45) {
            htvmClosePrgBlock = Trim(A_LoopField10);
        }
        if (A_Index10 == 79) {
            doc_keyWordErrorMsg = Trim(A_LoopField10);
        }
        if (A_Index10 == 80) {
            doc_keyWordTry = Trim(A_LoopField10);
        }
        if (A_Index10 == 81) {
            doc_keyWordCatch = Trim(A_LoopField10);
        }
        if (A_Index10 == 82) {
            doc_keyWordFinally = Trim(A_LoopField10);
        }
        if (A_Index10 == 75) {
            doc_funcKeyWord = Trim(A_LoopField10);
        }
        if (A_Index10 == 100) {
            doc_keyWordComment = Trim(A_LoopField10);
        }
        if (A_Index10 == 101) {
            doc_keyWordCommentOpenMultiLine = Trim(A_LoopField10);
        }
        if (A_Index10 == 102) {
            doc_keyWordCommentCloseMultiLine = Trim(A_LoopField10);
        }
        if (A_Index10 == 69) {
            doc_keyWordWhileLoop = Trim(A_LoopField10);
        }
        if (A_Index10 == 70) {
            doc_keyWordLoopInfinite = Trim(A_LoopField10);
        }
        if (A_Index10 == 71) {
            doc_keyWordLoop = Trim(A_LoopField10);
        }
        if (A_Index10 == 72) {
            doc_keyWordLoopParse = Trim(A_LoopField10);
        }
        if (A_Index10 == 73) {
            doc_keyWordContinue = Trim(A_LoopField10);
        }
        if (A_Index10 == 74) {
            doc_keyWordBreak = Trim(A_LoopField10);
        }
        if (A_Index10 == 147) {
            doc_keyWordAIndex = Trim(A_LoopField10);
        }
        if (A_Index10 == 148) {
            doc_keyWordALoopField = Trim(A_LoopField10);
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;
        if (A_Index10 == 84) {
            doc_keyWordArrayAppend = Trim(A_LoopField10);
        }
        if (A_Index10 == 85) {
            doc_keyWordArrayPop = Trim(A_LoopField10);
        }
        if (A_Index10 == 86) {
            doc_keyWordArraySize = Trim(A_LoopField10);
        }
        if (A_Index10 == 87) {
            doc_keyWordArrayInsert = Trim(A_LoopField10);
        }
        if (A_Index10 == 88) {
            doc_keyWordArrayRemove = Trim(A_LoopField10);
        }
        if (A_Index10 == 89) {
            doc_keyWordArrayIndexOf = Trim(A_LoopField10);
        }
        if (A_Index10 == 90) {
            doc_keyWordArrayDefinition = Trim(A_LoopField10);
        }
        if (A_Index10 == 91) {
            doc_keyWordArrayOfIntegersDefinition = Trim(A_LoopField10);
        }
        if (A_Index10 == 92) {
            doc_keyWordArrayOfStringsDefinition = Trim(A_LoopField10);
        }
        if (A_Index10 == 93) {
            doc_keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField10);
        }
        if (A_Index10 == 94) {
            doc_keyWordArrayOfBooleansDefinition = Trim(A_LoopField10);
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;
        if (A_Index10 == 149) {
            on_useCurlyBraces = Trim(A_LoopField10);
        }
        if (A_Index10 == 150) {
            on_useEnd = Trim(A_LoopField10);
        }
        if (A_Index10 == 151) {
            on_useSemicolon = Trim(A_LoopField10);
        }
        if (A_Index10 == 152) {
            on_useParentheses = Trim(A_LoopField10);
        }
        if (A_Index10 == 153) {
            on_usePrefixTypeForTypeDefinition = Trim(A_LoopField10);
        }
        if (A_Index10 == 154) {
            on_usePostfixTypeForTypeDefinition = Trim(A_LoopField10);
        }
        if (A_Index10 == 155) {
            on_usePythonicColonSyntax = Trim(A_LoopField10);
        }
        if (A_Index10 == 156) {
            on_useCurlyBracesSyntaxForArrayDef = Trim(A_LoopField10);
        }
        if (A_Index10 == 157) {
            on_useInJavaScriptAlwaysUseVar = Trim(A_LoopField10);
        }
        if (A_Index10 == 158) {
            on_useJavaScriptInAfullHTMLfile = Trim(A_LoopField10);
        }
        if (A_Index10 == 159) {
            on_useJavaScriptAmainFuncDef = Trim(A_LoopField10);
        }
        if (A_Index10 == 160) {
            on_useJavaScriptAllFuncsAreAsync = Trim(A_LoopField10);
        }
        if (A_Index10 == 161) {
            on_useJavaScriptAlwaysTripleEqual = Trim(A_LoopField10);
        }
        if (Trim(A_LoopField10) == "funcEND======================funcEND==============") {
            inFunc = 0;
        }
        if (inFunc == 1) {
            if (SubStr(Trim(A_LoopField10), 1, 6) == "lang: ") {
                HTVM_Append(funcData_lang, Trim(A_LoopField10));
            }
            else if (SubStr(Trim(A_LoopField10), 1, 6) == "name: ") {
                HTVM_Append(funcData_name, Trim(A_LoopField10));
            }
            else if (SubStr(Trim(A_LoopField10), 1, 13) == "description: ") {
                HTVM_Append(funcData_desc, Trim(A_LoopField10));
            }
        }
        if (Trim(A_LoopField10) == "func======================func==============") {
            inFunc = 1;
        }
    }
    std::vector<std::string> allFuncNames;
    allFuncNames = sortArr(funcData_name);
    std::string theFuncThatExistsIsCalled = "";
    if (DOCS_checkIfFuncNameExists == 1) {
        int exitedLoopCheckIfFuncNameExists = 0;
        for (int A_Index11 = 0; A_Index11 < HTVM_Size(allFuncNames) + 0; A_Index11++) {
            print(allFuncNames[A_Index11]);
            if (StrLower(DOCS_param2) == StrLower(Trim(StrSplit(allFuncNames[A_Index11], ":", 2)))) {
                theFuncThatExistsIsCalled = Trim(StrSplit(allFuncNames[A_Index11], ":", 2));
                exitedLoopCheckIfFuncNameExists = 1;
                break;
            }
        }
        if (exitedLoopCheckIfFuncNameExists == 1) {
            print("the func alredy exists!!! called: " + theFuncThatExistsIsCalled);
            ExitApp();
        } else {
            print("the func dosent exists!!! YOU CAN USE IT");
            ExitApp();
        }
    }
    // allFuncNames
    std::string allFuncNamesTemp = "";
    std::string tempDesc = "";
    std::string tempLang = "";
    for (int A_Index12 = 0; A_Index12 < HTVM_Size(funcData_name) + 0; A_Index12++) {
        //print(funcData_name[A_Index12])
        allFuncNamesTemp = funcData_name[A_Index12];
        tempLang = funcData_lang[A_Index12];
        tempDesc = funcData_desc[A_Index12];
        for (int A_Index13 = 0; A_Index13 < HTVM_Size(allFuncNames) + 0; A_Index13++) {
            if (Trim(allFuncNamesTemp) == Trim(StrSplit(allFuncNames[A_Index13], "|", 1))) {
                if (countChars(allFuncNames[A_Index13], "|") == 0) {
                    allFuncNames[A_Index13] = allFuncNames[A_Index13] + "|" + Trim(tempDesc) + "|" + Trim(tempLang);
                } else {
                    allFuncNames[A_Index13] = allFuncNames[A_Index13] + "|" + Trim(tempLang);
                }
            }
        }
    }
    std::vector<std::string> allFuncs;
    std::string tempstr = "";
    std::string isLangCpp = "";
    std::string isLangPy = "";
    std::string isLangJs = "";
    std::string isLangGo = "";
    std::string isLangLua = "";
    std::string isLangCs = "";
    std::string isLangJava = "";
    std::string isLangKotlin = "";
    std::string isLangRuby = "";
    std::string isLangNim = "";
    std::string isLangAhk = "";
    std::string isLangSwift = "";
    std::string isLangDart = "";
    std::string isLangTs = "";
    std::string isLangGroovy = "";
    std::string allFuncsTempAdd = "";
    int isDescNull = 0;
    for (int A_Index14 = 0; A_Index14 < HTVM_Size(allFuncNames) + 0; A_Index14++) {
        //print(allFuncNames[A_Index14])
        tempstr = Trim(allFuncNames[A_Index14]);
        isDescNull = 0;
        allFuncsTempAdd = "";
        isLangCpp = "No";
        isLangPy = "No";
        isLangJs = "No";
        isLangGo = "No";
        isLangLua = "No";
        isLangCs = "No";
        isLangJava = "No";
        isLangKotlin = "No";
        isLangRuby = "No";
        isLangNim = "No";
        isLangAhk = "No";
        isLangSwift = "No";
        isLangDart = "No";
        isLangTs = "No";
        isLangGroovy = "No";
        std::vector<std::string> items15 = LoopParseFunc(tempstr, "|");
        for (size_t A_Index15 = 0; A_Index15 < items15.size() + 0; A_Index15++) {
            std::string A_LoopField15 = items15[A_Index15 - 0];
            if (SubStr(Trim(A_LoopField15), 1, 8) == "lang: js") {
                isLangJs = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 8) == "lang: py") {
                isLangPy = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 9) == "lang: cpp") {
                isLangCpp = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 8) == "lang: go") {
                isLangGo = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 9) == "lang: lua") {
                isLangLua = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 8) == "lang: cs") {
                isLangCs = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 10) == "lang: java") {
                isLangJava = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 12) == "lang: kt") {
                isLangKotlin = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 10) == "lang: rb") {
                isLangRuby = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 9) == "lang: nim") {
                isLangNim = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 9) == "lang: ahk") {
                isLangAhk = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 11) == "lang: swift") {
                isLangSwift = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 10) == "lang: dart") {
                isLangDart = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 8) == "lang: ts") {
                isLangTs = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 12) == "lang: groovy") {
                isLangGroovy = "Yes";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 6) == "name: ") {
                allFuncsTempAdd += Trim(A_LoopField15) + "|";
            }
            else if (SubStr(Trim(A_LoopField15), 1, 13) == "description: ") {
                allFuncsTempAdd += Trim(A_LoopField15) + "|";
            }
            if (Trim(StrLower(A_LoopField15)) == "description: null") {
                isDescNull = 1;
            }
        }
        if (isDescNull != 1) {
            allFuncsTempAdd += isLangCpp + "|" + isLangPy + "|" + isLangJs + "|" + isLangGo + "|" + isLangLua + "|" + isLangCs + "|" + isLangJava + "|" + isLangKotlin + "|" + isLangRuby + "|" + isLangNim + "|" + isLangAhk + "|" + isLangSwift + "|" + isLangDart + "|" + isLangTs + "|" + isLangGroovy;
            HTVM_Append(allFuncs, allFuncsTempAdd);
        }
    }
    for (int A_Index16 = 0; A_Index16 < 20 + 0; A_Index16++) {
        //print("===========================================")
    }
    std::vector<std::string> categories;
    std::string theCurrentLine = "";
    std::string theCurrentDescCategory = "";
    int once = 0;
    int didWeFindSameCategory = 0;
    for (int A_Index17 = 0; A_Index17 < HTVM_Size(allFuncs) + 0; A_Index17++) {
        //print(allFuncs[A_Index17])
        once++;
        theCurrentLine = Trim(allFuncs[A_Index17]);
        theCurrentDescCategory = Trim(StrSplit(theCurrentLine, "|", 2));
        theCurrentDescCategory = Trim(StrSplit(theCurrentDescCategory, ":", 2));
        theCurrentDescCategory = Trim(StrLower(Trim(StrSplit(theCurrentDescCategory, "~~~", 1))));
        didWeFindSameCategory = 0;
        if (once == 1) {
            HTVM_Append(categories, theCurrentDescCategory + Chr(10) + theCurrentLine);
        } else {
            for (int A_Index18 = 0; A_Index18 < HTVM_Size(categories) + 0; A_Index18++) {
                if (Trim(StrLower(StrSplit(categories[A_Index18], Chr(10), 1))) == Trim(theCurrentDescCategory)) {
                    didWeFindSameCategory = 1;
                    categories[A_Index18] = categories[A_Index18] + Chr(10) + theCurrentLine;
                    break;
                }
            }
            if (didWeFindSameCategory == 0) {
                HTVM_Append(categories, theCurrentDescCategory + Chr(10) + theCurrentLine);
            }
        }
    }
    htvmSnippetLoad();
    

    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    std::vector<std::string> features;
// Indentation styles
if (on_useCurlyBraces == "on" && on_useEnd == "off") {
    features.push_back("curly braces for indentation");
} else if (on_useCurlyBraces == "off" && on_useEnd == "on") {
    features.push_back("Lua-style indentation (using `end` keywords)");
} else if (on_useCurlyBraces == "off" && on_useEnd == "off") {
    features.push_back("Pythonic indentation style (using spaces for indentation)");
}
// Array syntax
if (on_useCurlyBracesSyntaxForArrayDef == "off") {
    features.push_back("square brackets for array definitions");
} else {
    features.push_back("curly braces for array definitions");
}
// Semicolons
if (on_useSemicolon == "on") {
    features.push_back("semicolon to terminate statements (marks the end of a statement in your language)");
}
// Parentheses for control flow statements
if (on_useParentheses == "on") {
    features.push_back("parentheses around conditions in control flow statements (e.g., if, else if, while loops, like `if (condition)` or `while (condition)`)");
} else {
    features.push_back("no parentheses around conditions in control flow statements (e.g., if condition or while condition, like `if condition` or `while condition`)");
}
// Type definitions
if (on_usePrefixTypeForTypeDefinition == "on") {
    std::string prefixExample = (on_useSemicolon == "on") ? "int var1 = 5;" : "int var1 = 5";
    features.push_back("prefix type for variable definitions (similar to C-style type declaration, e.g., `" + prefixExample + "`)");
}
if (on_usePostfixTypeForTypeDefinition == "on") {
    std::string postfixExample = (on_useSemicolon == "on") ? "var1: int = 5;" : "var1: int = 5";
    features.push_back("postfix type for variable definitions (similar to TypeScript-style declaration, e.g., `" + postfixExample + "`)");
}
// Pythonic colon syntax
if (on_usePythonicColonSyntax == "on") {
    features.push_back("Pythonic colon syntax (colon used at the beginning of constructs like conditionals, loops, and function definitions, marking the start of a code block, similar to Python)");
}
// Constructing the sentence
std::string sentence = "Your language uses ";
for (size_t i = 0; i < features.size(); ++i) {
    sentence += features[i];
    if (i < features.size() - 1) {  
        sentence += ", ";
    }
}
sentence += ".";
    std::string funcSentence = "";
    if (on_usePrefixTypeForTypeDefinition == "on") {
        funcSentence = "in HTVM allow you to create reusable pieces of code. A function is defined using the " + Chr(96) + doc_funcKeyWord + Chr(96) + " keyword, followed by the return type, the function name, and its parameters";
    } else {
        funcSentence = "in HTVM are simple to use. They follow a structure where the " + Chr(96) + doc_funcKeyWord + Chr(96) + " keyword is used first, followed by the function name, its parameters, and the return type";
    }
    std::string hlepComments1 = "";
    std::string hlepComments2 = "";
    std::string hlepComments3 = "";
    hlepComments1 = doc_keyWordComment + " ✅ This comment will convert to any HTVM language or target language conversion.";
    hlepComments2 = doc_keyWordCommentOpenMultiLine + Chr(10) + "This is a multi-line comment." + Chr(10) + "It will be preserved in all conversions." + Chr(10) + doc_keyWordCommentCloseMultiLine;
    if (on_useSemicolon == "on") {
        hlepComments3 = "print(" + Chr(34) + "some text" + Chr(34) + "); " + doc_keyWordComment + " ❌ is comment will disappear when converting to another HTVM language or any target language.";
    } else {
        hlepComments3 = "print(" + Chr(34) + "some text" + Chr(34) + ") " + doc_keyWordComment + " ❌ is comment will disappear when converting to another HTVM language or any target language.";
    }
    std::string outMDsec0 = Chr(10) + "1. [Introduction](#introduction-to-htvm)  " + Chr(10) + "Understand why HTVM is the future of programming." + Chr(10) + Chr(10) + "2. [OSP (Ordinal Struct Programming)](#osp-ordinal-struct-programming)  " + Chr(10) + "Learn about OSP (Ordinal Struct Programming) a new way to use Structs." + Chr(10) + Chr(10) + "3. [How Your Language Looks Like](#how-your-language-looks-like)  " + Chr(10) + "Get to know how HTVM code is structured and its syntax style." + Chr(10) + Chr(10) + "4. [Programming Blocks](#programming-blocks)  " + Chr(10) + "HTVM introduces **programming blocks** that allow you to code in the target language seamlessly in your code. This feature is designed to handle cases where HTVM itself can't achieve something directly or when you'd prefer to rely on another language for specific tasks." + Chr(10) + Chr(10) + "5. [Variables](#variables)  " + Chr(10) + "Learn how to declare and use variables in HTVM for storing and manipulating data." + Chr(10) + Chr(10) + "6. [Functions](#functions)  " + Chr(10) + "Explore how to define and use functions for modular and reusable code." + Chr(10) + Chr(10) + "7. [Arrays](#arrays)  " + Chr(10) + "Dive into working with arrays, one of the most essential data structures in HTVM." + Chr(10) + Chr(10) + "8. [Loops](#loops)  " + Chr(10) + "Master the looping structures available in HTVM, such as the standard loop and infinite loops." + Chr(10) + Chr(10) + "9. [Comments](#comments)  " + Chr(10) + "Add clarity to your code by using comments to document and explain your code." + Chr(10) + Chr(10) + "10. [GUI (Graphical User Interface with HTVM)](#gui-graphical-user-interface-with-htvm)  " + Chr(10) + "Learn how to the GUI feature in HTVM that allows for the creation of graphical user interfaces specifically for **web browsers (JavaScript)**." + Chr(10) + Chr(10) + "11. [Backend in HTVM](#backend-in-htvm)  " + Chr(10) + "Learn how to use HTVM's Backend functionality that generates **Python** code using **Flask**." + Chr(10) + Chr(10) + "12. [Error Handling](#error-handling)  " + Chr(10) + "Understand how to manage errors and handle exceptions in HTVM to make your programs more robust." + Chr(10) + Chr(10) + "13. [Include](#include)  " + Chr(10) + "Discover how to include external files and resources in your HTVM project for enhanced functionality." + Chr(10) + Chr(10) + "14. [Commands](#commands)  " + Chr(10) + "Commands in HTVM are a simplified way to perform actions, similar to functions, but with a more compact, direct, and concise syntax for better efficiency." + Chr(10) + Chr(10) + "15. [All Syntax](#all-syntax)  " + Chr(10) + "This is all of your syntax." + Chr(10) + Chr(10) + "16. [Built-in Functions](#built-in-functions)  " + Chr(10) + "Explore the wide range of built-in functions categorized for ease of use." + Chr(10);
    std::string outMDsec1 = "### How Your Language Looks Like" + Chr(10) + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + Chr(10) + "Get to know how HTVM code is structured and its syntax style. HTVM uses a clean, human-readable syntax that focuses on simplicity and ease of use. You can define your own syntax, making HTVM incredibly flexible and tailored to your needs." + Chr(10) + Chr(10) + sentence + Chr(10) + Chr(10) + "Here is how it looks like:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet12 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "### Advanced String Features" + Chr(10) + Chr(10) + "HTVM supports powerful string definition methods, including formatted strings (f-strings) and multiline strings for easier text handling." + Chr(10) + Chr(10) + "*   **F-Strings (" + Chr(96) + "f" + Chr(34) + "..." + Chr(34) + Chr(96) + ")**: Allow embedding variables and expressions directly within strings." + Chr(10) + "*   **Multiline Strings (" + Chr(96) + "mls" + Chr(96) + "..." + Chr(96) + "mle" + Chr(96) + ")**: Define strings that span multiple lines, preserving formatting (like newlines and indentation) exactly as written. Ideal for raw text, templates, or ASCII art." + Chr(10) + "*   **Multiline F-Strings (" + Chr(96) + "fmls" + Chr(96) + "..." + Chr(96) + "mle" + Chr(96) + ")**: Combine the benefits of multiline strings and f-strings, allowing embedded variables and expressions within a multiline block." + Chr(10) + Chr(10) + "Here's how you can use them:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet49 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "#### Summary: The Power of Advanced Strings" + Chr(10) + Chr(10) + "These advanced string features (" + Chr(96) + "f" + Chr(96) + ", " + Chr(96) + "mls" + Chr(96) + ", " + Chr(96) + "fmls" + Chr(96) + ") significantly enhance HTVM's usability and power. They eliminate the need for cumbersome string concatenation and complex formatting logic." + Chr(10) + Chr(10) + "*   **Readability**: Code becomes much cleaner and easier to read, especially when dealing with templates, long text blocks, or dynamic content generation." + Chr(10) + "*   **Simplicity**: Constructing complex strings with embedded variables or preserving exact formatting is now straightforward and intuitive." + Chr(10) + "*   **Expressiveness**: HTVM becomes even more expressive, allowing you to focus on the logic rather than wrestling with string manipulation quirks." + Chr(10) + Chr(10) + "This level of string handling flexibility is a testament to HTVM's design philosophy: providing powerful, convenient tools that adapt to the programmer's needs, ultimately making development faster and more enjoyable. It's another step towards making HTVM the future of simplified, yet powerful, programming." + Chr(10) + Chr(10) + "---" + Chr(10) + "";
    std::string outMDsec2 = "### Programming Blocks" + Chr(10) + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + Chr(10) + "Programming blocks in HTVM allow you to write code directly in the target language when HTVM itself cannot handle certain tasks. These blocks give you the flexibility to insert language-specific code into your HTVM project without disrupting the overall flow. There are two main use cases for programming blocks: single-language programming blocks and multi-language programming blocks." + Chr(10) + Chr(10) + "#### **Single-Language Programming Block**" + Chr(10) + Chr(10) + "A single-language programming block allows you to write code directly in the target language. If you're converting HTVM code to, say, C++, you can open a programming block and write C++ code inside. This block will only be valid in the context of converting to C++ and will disappear when converting to another language." + Chr(10) + Chr(10) + "**Example:**" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet13 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "#### **Multiple-Language Programming Block**" + Chr(10) + Chr(10) + "HTVM also supports multiple-language programming blocks, where you can write code in different languages for the same functionality. For instance, if you're converting to both C++ and JavaScript, you can write separate blocks for each language but ensure the code behaves similarly in both." + Chr(10) + Chr(10) + "**Example:**" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet14 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "When using multi-language blocks, the syntax and implementation might differ, but the core functionality should remain the same. This is a great way to ensure consistency across multiple target languages." + Chr(10) + Chr(10) + "#### **Warning About AI-Generated Code**" + Chr(10) + Chr(10) + "**WARNING:** Be cautious when using AI-generated code. While AI can help speed up development, relying too heavily on it can be dangerous. You must understand the code you're incorporating into your project. **MAKE SURE YOU KNOW WHAT YOU'RE DOING BEFORE USING AI**. " + Chr(10) + Chr(10) + "If you don't have a solid understanding of the concepts you're asking the AI to handle, it can harm your learning process. **It could also negatively affect your development as a programmer.** Are you truly understanding the code you’re working with, or just relying on AI to do the heavy lifting for you?" + Chr(10) + Chr(10) + "Use AI to *assist*, not replace your learning process. **Be careful and make sure you understand every line of code** before integrating it into your project. This is essential for becoming a proficient programmer." + Chr(10) + Chr(10) + "#### **Reverse Programming Blocks**" + Chr(10) + Chr(10) + "Reverse programming blocks in HTVM allow you to write HTVM code in another file, which the HTVM compiler can recognize. These reverse blocks are helpful when you need to convert code written in HTVM into a target language while automatically including the necessary libraries and built-in functions." + Chr(10) + Chr(10) + "The syntax for reverse programming blocks is the same as for regular programming blocks, but you'll write HTVM code inside files of supported languages (e.g., " + Chr(96) + ".cpp" + Chr(96) + ", " + Chr(96) + ".js" + Chr(96) + ", etc.). Once you pass both the source file (e.g., " + Chr(96) + "main.cpp" + Chr(96) + ") and the HTVM instruction file to HTVM, the compiler will automatically replace the HTVM code with the appropriate target language code." + Chr(10) + Chr(10) + "HTVM will also ensure that all necessary libraries and built-in functions are included. It will automatically show you which libraries need to be included at the top of the file and which built-in functions you must import if they're not already part of the language's standard library." + Chr(10) + Chr(10) + "**Example of reverse programming block:**" + Chr(10) + Chr(10) + "1. Create a " + Chr(96) + ".cpp" + Chr(96) + " file (or any supported language file)." + Chr(10) + "2. Open the HTVM programming block using the syntax below:" + Chr(10) + "- To open - " + Chr(96) + htvmOpenPrgBlock + Chr(96) + Chr(10) + "- To close - " + Chr(96) + htvmClosePrgBlock + Chr(96) + Chr(10) + Chr(10) + "3. Pass both the " + Chr(96) + ".cpp" + Chr(96) + " file and the HTVM instruction file to HTVM." + Chr(10) + Chr(10) + "HTVM will:" + Chr(10) + Chr(10) + "- Replace the HTVM code with C++ (or the corresponding language)." + Chr(10) + "- Display the libraries and built-in functions that need to be included." + Chr(10) + Chr(10) + "---" + Chr(10) + "";
    std::string outMDsec3 = "### Variables" + Chr(10) + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + Chr(10) + "Learn how to declare and use variables in HTVM for storing and manipulating data. HTVM makes working with variables straightforward by providing flexible types and easy handling of data." + Chr(10) + Chr(10) + Chr(10) + "### **Variables in HTVM**  " + Chr(10) + Chr(10) + "A variable is a way to store and reference data in your code. In HTVM, you can use different variable types depending on your needs. Here are all the variable types supported by HTVM:  " + Chr(10) + Chr(10) + "| Type         | Description |" + Chr(10) + "|-------------|------------|" + Chr(10) + "| " + Chr(96) + "int" + Chr(96) + "       | Regular integer (size depends on the target language) |" + Chr(10) + "| " + Chr(96) + "int8" + Chr(96) + "      | 8-bit signed integer |" + Chr(10) + "| " + Chr(96) + "int16" + Chr(96) + "     | 16-bit signed integer |" + Chr(10) + "| " + Chr(96) + "int32" + Chr(96) + "     | 32-bit signed integer |" + Chr(10) + "| " + Chr(96) + "int64" + Chr(96) + "     | 64-bit signed integer |" + Chr(10) + "| " + Chr(96) + "uint8" + Chr(96) + "     | 8-bit unsigned integer |" + Chr(10) + "| " + Chr(96) + "uint16" + Chr(96) + "    | 16-bit unsigned integer |" + Chr(10) + "| " + Chr(96) + "uint32" + Chr(96) + "    | 32-bit unsigned integer |" + Chr(10) + "| " + Chr(96) + "uint64" + Chr(96) + "    | 64-bit unsigned integer |" + Chr(10) + "| " + Chr(96) + "float" + Chr(96) + "     | Floating-point number (usually 32-bit) |" + Chr(10) + "| " + Chr(96) + "double" + Chr(96) + "    | Double-precision floating-point number |" + Chr(10) + "| " + Chr(96) + "char" + Chr(96) + "      | Single character |" + Chr(10) + "| " + Chr(96) + "string" + Chr(96) + "    | Text string |" + Chr(10) + "| " + Chr(96) + "bool" + Chr(96) + "      | Boolean (" + Chr(96) + "true" + Chr(96) + " or " + Chr(96) + "false" + Chr(96) + ") |" + Chr(10) + Chr(10) + Chr(62) + " **Note:** We won't mention arrays here because they have a separate section under." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **HTVM Variable Example**  " + Chr(10) + Chr(10) + "Here’s a simple example of declaring and printing variables in HTVM:  " + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet15 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "This will correctly convert to the target language with the appropriate syntax." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Static vs. Dynamic Typing in HTVM**  " + Chr(10) + Chr(10) + "HTVM itself is **neither statically typed nor dynamically typed**. It simply converts code to the target language, which may be either.  " + Chr(10) + Chr(10) + "| **Language**  | **Typing** |" + Chr(10) + "|--------------|------------|" + Chr(10) + "| JavaScript   | Dynamic    |" + Chr(10) + "| Python       | Dynamic    |" + Chr(10) + "| Lua          | Dynamic    |" + Chr(10) + "| Ruby         | Dynamic    |" + Chr(10) + "| Groovy       | Dynamic    |" + Chr(10) + "| TypeScript   | Static     |" + Chr(10) + "| C++          | Static     |" + Chr(10) + "| Go (Golang)  | Static     |" + Chr(10) + "| C#           | Static     |" + Chr(10) + "| Java         | Static     |" + Chr(10) + "| Kotlin       | Static     |" + Chr(10) + "| Nim          | Static     |" + Chr(10) + "| Swift        | Static     |" + Chr(10) + "| Dart         | Static     |" + Chr(10) + "| AutoHotKey   | Dynamic    |" + Chr(10) + Chr(10) + "- **For static languages**, you **must** use types; otherwise, the conversion will result in invalid code." + Chr(10) + "- **For dynamic languages**, you **can** use types, but HTVM will **strip them away** automatically." + Chr(10) + "- **HTVM does not provide type safety** – it will not warn you about type mismatches. You'll find out only when running the target language." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "#### **" + Chr(96) + "let" + Chr(96) + " and " + Chr(96) + "var" + Chr(96) + " Keywords**" + Chr(10) + Chr(10) + "The " + Chr(96) + "let" + Chr(96) + " and " + Chr(96) + "var" + Chr(96) + " keywords in HTVM are mainly useful when converting to languages that support these keywords, like **JavaScript** and **TypeScript**. These keywords are used to define mutable variables, but outside of those specific languages, you can ignore them, as HTVM will convert them appropriately based on the target language." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **The " + Chr(96) + "const" + Chr(96) + " Keyword**  " + Chr(10) + Chr(10) + "HTVM supports the " + Chr(96) + "const" + Chr(96) + " keyword, but it **does not enforce it** in any way. It simply converts it to the target language if the language supports " + Chr(96) + "const" + Chr(96) + ".  " + Chr(10) + Chr(10) + "| **Language**  | **Supports " + Chr(96) + "const" + Chr(96) + "?** |" + Chr(10) + "|--------------|--------------------|" + Chr(10) + "| JavaScript   | ✅ Yes |" + Chr(10) + "| TypeScript   | ✅ Yes |" + Chr(10) + "| C++          | ✅ Yes |" + Chr(10) + "| Go (Golang)  | ✅ Yes |" + Chr(10) + "| C#           | ✅ Yes |" + Chr(10) + "| Java         | ✅ Yes |" + Chr(10) + "| Kotlin       | ✅ Yes |" + Chr(10) + "| Swift        | ✅ Yes |" + Chr(10) + "| Dart         | ✅ Yes |" + Chr(10) + "| Python       | ❌ No (ignored) |" + Chr(10) + "| Lua          | ❌ No (ignored) |" + Chr(10) + "| Ruby         | ❌ No (ignored) |" + Chr(10) + "| Groovy       | ❌ No (ignored) |" + Chr(10) + "| Nim          | ✅ Yes |" + Chr(10) + "| AutoHotKey   | ❌ No (ignored) |" + Chr(10) + Chr(10) + "HTVM **does not check** whether you're violating " + Chr(96) + "const" + Chr(96) + ". If a language doesn’t support " + Chr(96) + "const" + Chr(96) + ", HTVM **removes it** without warning." + Chr(10) + Chr(10) + "Example:  " + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet16 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "- If converting to **C++**, this becomes " + Chr(96) + "const int x = 10;" + Chr(96) + Chr(10) + "- If converting to **Python**, this becomes " + Chr(96) + "x = 10" + Chr(96) + " (no " + Chr(96) + "const" + Chr(96) + ")." + Chr(10) + "- If converting to **Java**, this becomes " + Chr(96) + "final int x = 10;" + Chr(96) + Chr(10) + "- ... etc." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Programming Blocks & Variable Scope**  " + Chr(10) + Chr(10) + "HTVM allows **programming blocks**, where you write code directly in a target language. These blocks **do not convert** – they remain as-is." + Chr(10) + Chr(10) + "#### **Variable Accessibility in Programming Blocks**" + Chr(10) + "- **HTVM variables can be accessed inside programming blocks.**" + Chr(10) + "- **Modifications inside a block persist after the block.**" + Chr(10) + "- **Programming blocks are not scoped – they are part of the converted language.**" + Chr(10) + "- **However, different programming languages do not share scope.**  " + Chr(10) + Chr(10) + "Example (Converting to Python):  " + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet17 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "This converts to:  " + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "python" + Chr(10) + "myNumber = 5" + Chr(10) + "myNumber += 10  # Python block stays intact" + Chr(10) + "print(myNumber)  # 15" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Multiple Programming Blocks & Limitations**  " + Chr(10) + Chr(10) + "#### **Single Language Conversion**" + Chr(10) + "If you are converting to just **one language**, everything works as expected. Variables declared in HTVM can be used inside the programming block and modified." + Chr(10) + Chr(10) + "#### **Multiple Language Conversion**" + Chr(10) + "If you are converting to **multiple languages**, each programming block is isolated per language.  " + Chr(10) + "- **You cannot access variables across different language blocks.**  " + Chr(10) + "- You must **manually maintain the same logic** in each block.  " + Chr(10) + Chr(10) + "Example (Invalid cross-language access):  " + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet18 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "To fix this, you need to **manually synchronize values** in each programming block." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Unsigned Integers & Java**  " + Chr(10) + Chr(10) + "- **Java does not support unsigned integers** (" + Chr(96) + "uint8" + Chr(96) + ", " + Chr(96) + "uint16" + Chr(96) + ", etc.)." + Chr(10) + "- If you try to use them, **HTVM will not warn you**, but Java might throw errors." + Chr(10) + "- **Avoid using unsigned integers when converting to Java.**  " + Chr(10) + Chr(10) + "Example of bad practice:  " + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet19 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "- **Works in C++** (" + Chr(96) + "uint32_t myUnsigned = 500;" + Chr(96) + ")" + Chr(10) + "- **Might fail in Java since unsigned ints are converted to signed ones**" + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Summary**" + Chr(10) + Chr(10) + "- HTVM has multiple **variable types**, including integers, floats, chars, strings, and booleans." + Chr(10) + "- HTVM **converts to both static and dynamic languages** but does not enforce type safety." + Chr(10) + "- The " + Chr(96) + "const" + Chr(96) + " keyword is supported but **ignored** in languages that don’t use it." + Chr(10) + "- **Programming blocks do not convert** – they stay in the target language." + Chr(10) + "- **Variables persist inside programming blocks** but do not transfer between different language blocks." + Chr(10) + "- **Java does not support unsigned integers**, so try to avoid them when converting to Java." + Chr(10) + Chr(10) + "---" + Chr(10) + "";
    std::string outMDsec4 = "### Functions" + Chr(10) + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + Chr(10) + "Explore how to define and use functions for modular and reusable code. Functions in HTVM can be written easily, and the language supports efficient handling of function calls, parameters, and returns." + Chr(10) + Chr(10) + "### **HTVM Functions**  " + Chr(10) + Chr(10) + "Functions " + funcSentence + "." + Chr(10) + Chr(10) + "#### **Defining a Function**" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet32 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet33 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet34 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + " " + Chr(10) + Chr(10) + "Optional parameters example:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet35 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "If you are converting to a dynamically typed language, the types will be stripped away automatically. However, for statically typed languages, you must include them.  " + Chr(10) + Chr(10) + "#### The " + Chr(96) + "main" + Chr(96) + " Function" + Chr(10) + Chr(10) + "In HTVM, the " + Chr(96) + "main" + Chr(96) + " function is required if you are using functions. It is defined as a simple label at the beginning of the program. If you do not include the " + Chr(96) + "main" + Chr(96) + " function, HTVM will insert it automatically at the top of the code. However, if you define any functions and do not include the " + Chr(96) + "main" + Chr(96) + " label, the program will not work as expected." + Chr(10) + Chr(10) + "The " + Chr(96) + "main" + Chr(96) + " label is where the execution starts in languages that use a main function (like C++). In languages that do not require a " + Chr(96) + "main" + Chr(96) + " function (like Python), HTVM handles it automatically." + Chr(10) + Chr(10) + "Here’s how it looks:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet36 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "- The " + Chr(96) + "greet" + Chr(96) + " function is defined before " + Chr(96) + "main" + Chr(96) + "." + Chr(10) + "- The " + Chr(96) + "main" + Chr(96) + " function calls " + Chr(96) + "greet()" + Chr(96) + " to execute the code." + Chr(10) + Chr(10) + "If you do not define the " + Chr(96) + "main" + Chr(96) + " label, HTVM will automatically add it at the top of the code, but **you must include it if you are using functions** to ensure everything works correctly." + Chr(10) + Chr(10) + "### **HTVM: Flexible Function Call Syntax**" + Chr(10) + Chr(10) + "#### **Overview**  " + Chr(10) + "HTVM introduces a unique and flexible function call syntax that allows developers to call functions in multiple ways while maintaining simplicity and readability. This enhancement does not change the fundamental nature of functions in HTVM—they remain regular functions rather than methods. However, HTVM allows them to be called using dot notation for convenience. No programming language supports this level of freedom—this is a new invention: a flexible and freeing way to call HTVM functions." + Chr(10) + Chr(10) + "#### **Features**" + Chr(10) + Chr(10) + "- **Traditional Function Calls**  " + Chr(10) + "  Functions can be called using the standard syntax:  " + Chr(10) + "  " + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "  StrLower(var1)" + Chr(10) + "  Trim(var1)" + Chr(10) + "  " + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "- **Dot Notation for Function Calls**  " + Chr(10) + "  HTVM allows functions to be called using dot notation for enhanced readability and convenience:  " + Chr(10) + "  " + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "  var1.StrLower()" + Chr(10) + "  var1.Trim()" + Chr(10) + "  " + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "- **Optional Parentheses**  " + Chr(10) + "  When a function does not require additional parameters, parentheses can be omitted:  " + Chr(10) + "  " + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "  var1.StrLower" + Chr(10) + "  var1.Trim" + Chr(10) + "  " + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "- **Chained Function Calls**  " + Chr(10) + "  Functions can be chained together using dot notation:  " + Chr(10) + "  " + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "  var1.StrLower().Trim()" + Chr(10) + "  " + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "  Since parentheses are optional, the same operation can be written as:  " + Chr(10) + "  " + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "  var1.StrLower.Trim" + Chr(10) + "  " + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "  It is also possible to mix both styles:  " + Chr(10) + "  " + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "  var1.StrLower().Trim" + Chr(10) + "  " + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "- **Seamless Transpilation**  " + Chr(10) + "  HTVM automatically converts these function calls into standard function calls during conversion. This ensures that the underlying implementation remains consistent while providing developers with flexibility in how they write their code." + Chr(10) + Chr(10) + "#### **Examples**" + Chr(10) + Chr(10) + "### **Standard Function Calls**  " + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "StrLower(var1)" + Chr(10) + "Trim(var1)" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "### **Dot Notation Function Calls**  " + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "var1.StrLower()" + Chr(10) + "var1.Trim()" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "### **Dot Notation Without Parentheses**  " + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "var1.StrLower" + Chr(10) + "var1.Trim" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "### **Chained Function Calls**  " + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "var1.StrLower().Trim()" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "### **Mixed Parentheses Usage**  " + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "var1.StrLower().Trim" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "### **Full Example with OSP**" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet37 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "#### This only works with HTVM built-in functions and user-defined functions.  " + Chr(10) + "When using the " + Chr(96) + "varName.funcName" + Chr(96) + " format, HTVM will only convert it to a regular function call (" + Chr(96) + "funcName(varName)" + Chr(96) + ") **if** the function is either a built-in function in HTVM or explicitly defined by the user." + Chr(10) + Chr(10) + "HTVM **does not care** whether the function is built-in in the target language (e.g. Python). If the function is not recognized by HTVM, it will not be converted — even if it's valid in the output language." + Chr(10) + Chr(10) + "For example:" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "py" + Chr(10) + "strVar.upper()" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + "- If " + Chr(96) + "upper" + Chr(96) + " is not a built-in HTVM function or user-defined in your code, HTVM will **not** convert this into " + Chr(96) + "upper(strVar)" + Chr(96) + " for Python.  " + Chr(10) + "- It will stay as " + Chr(96) + "strVar.upper()" + Chr(96) + " or may cause unexpected output depending on the target." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "#### **Conclusion**  " + Chr(10) + "This feature enhances HTVM's usability by providing developers with multiple ways to call functions. While function calls remain standard behind the scenes, the optional dot notation and support for omitting parentheses make the syntax more intuitive, readable, and faster to write — especially in casual or repetitive scenarios." + Chr(10) + Chr(10) + "---" + Chr(10) + "";
    std::string outMDsec5 = "### Arrays" + Chr(10) + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + Chr(10) + "Dive into working with arrays, one of the most essential data structures in HTVM. Arrays are simple to declare and manipulate, enabling you to store and process collections of data easily." + Chr(10) + Chr(10) + "### **Arrays in HTVM**" + Chr(10) + Chr(10) + "Arrays in HTVM are collections of values stored in a single variable. Arrays can hold multiple values of the same type. HTVM supports a variety of array types and offers flexibility, especially in dynamic languages. Here's an overview of how arrays work in HTVM:" + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Supported Array Types**  " + Chr(10) + Chr(10) + "HTVM supports the following array types:" + Chr(10) + Chr(10) + "| Type        | Description |" + Chr(10) + "|-------------|------------|" + Chr(10) + "| " + Chr(96) + doc_keyWordArrayOfIntegersDefinition + Chr(96) + "     | Array of integers (regular size depends on the target language) |" + Chr(10) + "| " + Chr(96) + doc_keyWordArrayOfFloatingPointNumbersDefinition + Chr(96) + "   | Array of floating-point numbers |" + Chr(10) + "| " + Chr(96) + doc_keyWordArrayOfBooleansDefinition + Chr(96) + "    | Array of booleans (true or false) |" + Chr(10) + "| " + Chr(96) + doc_keyWordArrayOfStringsDefinition + Chr(96) + "  | Array of strings (text) |" + Chr(10) + Chr(10) + Chr(62) + " **Note:** In dynamic languages like JavaScript and Python, you can use arrays without explicitly defining the type. The type will be inferred or stripped out, depending on the language." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **The Generic Array Type**  " + Chr(10) + Chr(10) + "In addition to the specific array types above, HTVM provides a more flexible **generic array** keyword which is " + Chr(96) + doc_keyWordArrayDefinition + Chr(96) + ". This allows you to create arrays without specifying a type. When you use this keyword:" + Chr(10) + Chr(10) + "- In **dynamically typed languages** (e.g., JavaScript, Python), HTVM will infer the type based on the values you assign." + Chr(10) + "- In **statically typed languages** (e.g., C++, Java), HTVM will convert it into a " + Chr(96) + "std::vector&lt;std::string" + Chr(62) + Chr(96) + " / " + Chr(96) + "string[]" + Chr(96) + "." + Chr(10) + Chr(10) + "This provides flexibility, but also means you lose type checking, and you’ll need to ensure the elements in the array match the expected type." + Chr(10) + Chr(10) + "Example (Dynamic Language):" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet20 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Array Methods in HTVM**" + Chr(10) + Chr(10) + "| **Method**                          | **Description**                                                                                |" + Chr(10) + "|-------------------------------------|------------------------------------------------------------------------------------------------|" + Chr(10) + "| " + Chr(96) + doc_keyWordArrayAppend + "()" + Chr(96) + "    | Adds an element to the end of the array.                                                       |" + Chr(10) + "| " + Chr(96) + doc_keyWordArrayPop + "()" + Chr(96) + "       | Removes and returns the last element of the array.                                             |" + Chr(10) + "| " + Chr(96) + doc_keyWordArraySize + "()" + Chr(96) + "      | Returns the number of elements in the array.                                                   |" + Chr(10) + "| " + Chr(96) + doc_keyWordArrayInsert + "()" + Chr(96) + "    | Inserts an element at a specific index.                                                        |" + Chr(10) + "| " + Chr(96) + doc_keyWordArrayRemove + "()" + Chr(96) + "    | Removes the element at the specified index.                                                    |" + Chr(10) + "| " + Chr(96) + doc_keyWordArrayIndexOf + "()" + Chr(96) + "   | Returns the index of the first occurrence of the specified element. Returns " + Chr(96) + "-1" + Chr(96) + " if not found. |" + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Array Methods in Detail**" + Chr(10) + Chr(10) + "HTVM provides a set of useful methods to manipulate arrays in your programs. These methods follow a consistent " + Chr(96) + ".method()" + Chr(96) + " syntax, making it easy to interact with arrays. Below are the array methods supported in HTVM:" + Chr(10) + Chr(10) + "1. **" + Chr(96) + doc_keyWordArrayAppend + "()" + Chr(96) + "**  " + Chr(10) + Chr(10) + "Adds an element to the end of the array.  " + Chr(10) + "Example:" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet21 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "2. **" + Chr(96) + doc_keyWordArrayPop + "()" + Chr(96) + "**  " + Chr(10) + Chr(10) + "Removes and returns the last element of the array.  " + Chr(10) + "Example:" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet22 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "3. **" + Chr(96) + doc_keyWordArraySize + "()" + Chr(96) + "**  " + Chr(10) + Chr(10) + "Returns the number of elements in the array.  " + Chr(10) + "Example:" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet23 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "4. **" + Chr(96) + doc_keyWordArrayInsert + "()" + Chr(96) + "** " + Chr(10) + " " + Chr(10) + "Inserts an element at a specific index. The index is the first argument, and the element to insert is the second argument.  " + Chr(10) + "Example:" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet24 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "5. **" + Chr(96) + doc_keyWordArrayRemove + "()" + Chr(96) + "**  " + Chr(10) + Chr(10) + "Removes the element at the specified index.  " + Chr(10) + "Example:" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet25 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "6. **" + Chr(96) + doc_keyWordArrayIndexOf + "()" + Chr(96) + "**  " + Chr(10) + Chr(10) + "Returns the index of the first occurrence of the specified element. If the element is not found, it returns " + Chr(96) + "-1" + Chr(96) + ".  " + Chr(10) + "Example:" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet26 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Example of Using Array Methods in HTVM**" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet27 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "In the example above, you can see how various methods like " + Chr(96) + doc_keyWordArrayAppend + "()" + Chr(96) + ", " + Chr(96) + doc_keyWordArrayRemove + "()" + Chr(96) + ", and " + Chr(96) + doc_keyWordArrayInsert + "()" + Chr(96) + " are used in sequence to manipulate the array." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Summary of Array Methods**" + Chr(10) + Chr(10) + "- **" + Chr(96) + doc_keyWordArrayAppend + "()" + Chr(96) + "**: Adds an element to the end of the array." + Chr(10) + "- **" + Chr(96) + doc_keyWordArrayPop + "()" + Chr(96) + "**: Removes and returns the last element of the array." + Chr(10) + "- **" + Chr(96) + doc_keyWordArraySize + "()" + Chr(96) + "**: Returns the size of the array." + Chr(10) + "- **" + Chr(96) + doc_keyWordArrayInsert + "(index, element)" + Chr(96) + "**: Inserts an element at the specified index." + Chr(10) + "- **" + Chr(96) + doc_keyWordArrayRemove + "(index)" + Chr(96) + "**: Removes the element at the specified index." + Chr(10) + "- **" + Chr(96) + doc_keyWordArrayIndexOf + "(element)" + Chr(96) + "**: Finds the index of the first occurrence of the specified element." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Arrays in Programming Blocks**  " + Chr(10) + Chr(10) + "Just like variables, arrays can be accessed and modified inside **programming blocks**. Programming blocks in HTVM are directly written in the target language and do not undergo conversion. The following behaviors apply to arrays inside programming blocks:" + Chr(10) + Chr(10) + "- **Arrays persist across blocks**, meaning changes made to an array within a block are retained when the block ends." + Chr(10) + "- **Arrays are not scoped**—they are part of the target language’s code." + Chr(10) + "- **Different programming languages do not share arrays across blocks**, just like variables." + Chr(10) + Chr(10) + "Example (Converting to Python):" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet28 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "This will convert to:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "python" + Chr(10) + "myArray = [1, 2, 3]" + Chr(10) + "myArray.append(4)  # Python block stays intact" + Chr(10) + "print(myArray)  # Output: [1, 2, 3, 4]" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **No Type Checking for Arrays**  " + Chr(10) + Chr(10) + "HTVM **does not perform type checking** for arrays. It will **not warn you** if you accidentally try to mix types within an array or if you make other mistakes related to array types. You will only notice errors during runtime in the target language." + Chr(10) + Chr(10) + "Example:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet29 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "In **JavaScript**, this would become:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "javascript" + Chr(10) + "let myArray = [1, " + Chr(34) + "two" + Chr(34) + ", 3];  // Valid in JavaScript, but mixed types" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "However, you might get unexpected results in a **statically typed language**, like **C++**." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **No " + Chr(96) + "const" + Chr(96) + " Arrays**  " + Chr(10) + Chr(10) + "HTVM does not support **constant arrays** or array immutability like some languages might (e.g., " + Chr(96) + "const" + Chr(96) + " arrays in JavaScript). If you want to have immutable arrays, you will need to **use programming blocks** and ensure the logic prevents modification." + Chr(10) + Chr(10) + "Example:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet30 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "If you want immutability or similar behavior, you must handle it manually within programming blocks or by controlling logic in your code." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Arrays in Multiple Language Conversions**  " + Chr(10) + Chr(10) + "When converting to **multiple languages**, arrays function similarly to variables in programming blocks. However, you cannot directly **share arrays between different language blocks**. Each block is isolated in its respective language, so any array manipulations within one block will not affect another block." + Chr(10) + Chr(10) + "Example (Invalid cross-language access):" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet31 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "You’ll need to manually synchronize arrays between programming blocks if needed." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Summary**  " + Chr(10) + Chr(10) + "- HTVM supports **integer arrays**, **floating-point arrays**, **boolean arrays**, and **string arrays**." + Chr(10) + "- **Array Methods in HTVM**" + Chr(10) + "- HTVM offers a **generic array type**, which is flexible but removes type checking in dynamic languages." + Chr(10) + "- **Arrays in programming blocks persist**, but they are not scoped across blocks." + Chr(10) + "- **No type checking** is performed on arrays, so errors related to mismatched types will not be caught until runtime." + Chr(10) + "- **No support for constant arrays**—you need to manage immutability yourself using programming blocks." + Chr(10) + "- **Arrays cannot be shared across different language blocks** in multiple language conversions." + Chr(10) + Chr(10) + "#### ⚠️ WARNING: We can't use nested arrays or multiline arrays (like arrays inside arrays or 2D/3D arrays). To achieve that, use a programming block." + Chr(10) + Chr(10) + "---" + Chr(10) + "";
    std::string outMDsec6 = Chr(10) + Chr(10);
    std::string outMDsec7 = "" + Chr(10) + "### Loops" + Chr(10) + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + Chr(10) + "### **Understanding Loops in HTVM**" + Chr(10) + Chr(10) + "HTVM supports multiple types of loops, inspired by AutoHotKey (AHK) syntax. These loops are designed to be simple and efficient, offering flexibility for various tasks. Let’s explore the **Regular Loop**, **Loop Parse**, **Infinite Loop**, and the **while loop**." + Chr(10) + Chr(10) + "**Regular Loop** = " + Chr(96) + doc_keyWordLoop + Chr(96) + Chr(10) + Chr(10) + "**Loop Parse** = " + Chr(96) + doc_keyWordLoopParse + Chr(96) + Chr(10) + Chr(10) + "**Infinite Loop** = " + Chr(96) + doc_keyWordLoopInfinite + Chr(96) + Chr(10) + Chr(10) + "**While loop** = " + Chr(96) + doc_keyWordWhileLoop + Chr(96) + Chr(10) + Chr(10) + "**continue** = " + Chr(96) + doc_keyWordContinue + Chr(96) + Chr(10) + Chr(10) + "**break** = " + Chr(96) + doc_keyWordBreak + Chr(96) + Chr(10) + Chr(10) + "**A_Index** = " + Chr(96) + doc_keyWordAIndex + Chr(96) + Chr(10) + Chr(10) + "**A_LoopField** = " + Chr(96) + doc_keyWordALoopField + Chr(96) + Chr(10) + Chr(10) + Chr(10) + "### **1. Regular Loop**" + Chr(10) + Chr(10) + "The " + Chr(96) + doc_keyWordLoop + Chr(96) + " keyword in HTVM is the simplest and most common type of loop. It runs a specified number of iterations, and you can use the " + Chr(96) + doc_keyWordAIndex + Chr(96) + " keyword to track the current iteration number." + Chr(10) + Chr(10) + "#### Example:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet38 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "In this loop, " + Chr(96) + doc_keyWordAIndex + Chr(96) + " is used to track the current iteration number. The " + Chr(96) + doc_keyWordContinue + Chr(96) + " keyword is used to skip even numbers, so only odd numbers will be printed." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **2. Loop Parse**" + Chr(10) + Chr(10) + "The " + Chr(96) + doc_keyWordLoopParse + Chr(96) + " is similar to AutoHotKey’s loop parsing method, where you can iterate over a string or text with different delimiters. In HTVM, " + Chr(96) + doc_keyWordALoopField + Chr(96) + " is used to access the current field (or token) in the string being parsed." + Chr(10) + Chr(10) + "#### **Example 1: Delimited by Space (" + Chr(34) + " " + Chr(34) + ")**" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet39 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "In this example, the loop iterates over each word in the string " + Chr(96) + "someText" + Chr(96) + ", which is delimited by spaces. The " + Chr(96) + doc_keyWordALoopField + Chr(96) + " holds the current word from the string." + Chr(10) + Chr(10) + "#### **Example 2: Delimited by New Line**" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet40 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "Here, the loop splits the text by new lines, and " + Chr(96) + doc_keyWordALoopField + Chr(96) + " holds each line individually." + Chr(10) + Chr(10) + "#### **Example 3: Delimited by Carriage Return**" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet41 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "In this case, the text is delimited by carriage returns, and each line is printed separately." + Chr(10) + Chr(10) + "#### **Example 4: Delimited by Both Space and New Line**" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet42 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "This example uses both a space and a new line as delimiters to split the string into tokens." + Chr(10) + Chr(10) + "#### **Example 5: No delimited**" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet43 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "This example uses no delimiters to parse each character." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **3. Infinite Loop**" + Chr(10) + Chr(10) + "HTVM also supports infinite loops using the " + Chr(96) + doc_keyWordLoopInfinite + Chr(96) + " keyword without a defined number of iterations. The loop will continue running until a " + Chr(96) + doc_keyWordBreak + Chr(96) + " condition or manual termination occurs. The " + Chr(96) + doc_keyWordContinue + Chr(96) + " keyword can be used inside the infinite loop to skip the current iteration and continue with the next one." + Chr(10) + Chr(10) + "#### Example (Infinite Loop):" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet44 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "Here, the loop runs indefinitely, printing the current value of " + Chr(96) + doc_keyWordAIndex + Chr(96) + ". When " + Chr(96) + doc_keyWordAIndex + Chr(96) + " reaches 5, the loop breaks. You can also use " + Chr(96) + doc_keyWordContinue + Chr(96) + " to skip iterations as needed." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **4. While Loop**" + Chr(10) + Chr(10) + "The " + Chr(96) + doc_keyWordWhileLoop + Chr(96) + " loop in HTVM works like a typical while loop in other languages. It continues to execute the loop body as long as the specified condition evaluates to true." + Chr(10) + Chr(10) + "#### Example (While Loop):" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet45 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "In this example, the " + Chr(96) + doc_keyWordWhileLoop + Chr(96) + " loop runs once because the condition is initially true, then changes " + Chr(96) + "var1" + Chr(96) + " to true, causing the loop to terminate." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Array Example in Loop**" + Chr(10) + Chr(10) + "HTVM also allows arrays, which can be used in loops for more complex tasks. Here’s an example that iterates over an array:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet46 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "In this case, the loop iterates through each element of the array " + Chr(96) + "arr123" + Chr(96) + " using " + Chr(96) + doc_keyWordAIndex + Chr(96) + " to reference the array's index." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Variable Example in Loop**" + Chr(10) + Chr(10) + "With HTVM, you can also use variables to control loops. Here's an example:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet47 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "This example shows how HTVM allows you to use variables like " + Chr(96) + "var1" + Chr(96) + " to control the number of iterations in the loop, with " + Chr(96) + doc_keyWordAIndex + Chr(96) + " printing the current iteration number." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Key Notes:**" + Chr(10) + "- **" + Chr(96) + doc_keyWordAIndex + Chr(96) + "**: Used in all loops except for " + Chr(96) + doc_keyWordWhileLoop + Chr(96) + " loops." + Chr(10) + "- **" + Chr(96) + doc_keyWordALoopField + Chr(96) + "**: Used only in " + Chr(96) + doc_keyWordLoopParse + Chr(96) + " to reference the current field." + Chr(10) + "- **" + Chr(96) + doc_keyWordContinue + Chr(96) + "**: Can be used in any loop to skip the current iteration and continue with the next one. When converting to Lua, place the " + Chr(96) + "::" + doc_keyWordContinue + Chr(96) + " at the end of the loop, just before it ends." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Lua Conversion**" + Chr(10) + Chr(10) + "For the **" + doc_keyWordLoop + "**, **" + doc_keyWordLoopParse + "**, and **" + doc_keyWordLoopInfinite + "** types, the Lua conversion looks like this:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet48 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "In Lua, the conversion for these loops would use the " + Chr(96) + "goto" + Chr(96) + " statement to achieve the continue behavior. Here's how it would look in Lua:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "lua" + Chr(10) + "function infinite_HTVM_Lua_Loop_HTVM()" + Chr(10) + "    local i = 0" + Chr(10) + "    return function()" + Chr(10) + "        i = i + 1" + Chr(10) + "        return i" + Chr(10) + "    end" + Chr(10) + "end" + Chr(10) + Chr(10) + "function LoopParseFunc(varString, delimiter1, delimiter2)" + Chr(10) + "    local items = {}" + Chr(10) + "    delimiter1 = delimiter1 or " + Chr(34) + Chr(34) + Chr(10) + "    delimiter2 = delimiter2 or " + Chr(34) + Chr(34) + Chr(10) + "    -- Changed: Don't escape the delimiters since we want them literal" + Chr(10) + "    -- Just use them directly in the pattern" + Chr(10) + "    if delimiter1 == " + Chr(34) + Chr(34) + " and delimiter2 == " + Chr(34) + Chr(34) + " then" + Chr(10) + "        for i = 1, #varString do" + Chr(10) + "            table.insert(items, varString:sub(i, i))" + Chr(10) + "        end" + Chr(10) + "    else" + Chr(10) + "        -- Changed: Simplified pattern to directly match " + Chr(92) + "n and " + Chr(92) + "r" + Chr(10) + "        local pattern = delimiter1 .. delimiter2" + Chr(10) + "        for item in varString:gmatch(" + Chr(34) + "([^" + Chr(34) + " .. pattern .. " + Chr(34) + "]+)" + Chr(34) + ") do" + Chr(10) + "            table.insert(items, item)" + Chr(10) + "        end" + Chr(10) + "    end" + Chr(10) + "    return items" + Chr(10) + "end" + Chr(10) + Chr(10) + "-- Regular loop example" + Chr(10) + "for A_Index1 = 0 + 1 , 10 + 0 do" + Chr(10) + "    if (A_Index1 % 2 == 0) then" + Chr(10) + "        goto continue0" + Chr(10) + "    end" + Chr(10) + "    -- Output only odd numbers from 1 to 9" + Chr(10) + "    print(A_Index1)" + Chr(10) + "    ::continue0::" + Chr(10) + "end" + Chr(10) + Chr(10) + "print(" + Chr(34) + "=====================" + Chr(34) + ")" + Chr(10) + Chr(10) + "-- Infinite loop example" + Chr(10) + "for A_Index2 in infinite_HTVM_Lua_Loop_HTVM() do" + Chr(10) + "    if (A_Index2 % 2 == 0) then" + Chr(10) + "        goto continue1" + Chr(10) + "    end" + Chr(10) + "    -- Output only odd numbers from 1 to 9" + Chr(10) + "    print(A_Index2)" + Chr(10) + "    if (A_Index2 == 9) then" + Chr(10) + "        break" + Chr(10) + "    end" + Chr(10) + "    ::continue1::" + Chr(10) + "end" + Chr(10) + Chr(10) + "print(" + Chr(34) + "=====================" + Chr(34) + ")" + Chr(10) + Chr(10) + "-- Loop, Parse loop example" + Chr(10) + "var1 = " + Chr(34) + "hello whats up bro how are you doing" + Chr(34) + Chr(10) + "items3 = LoopParseFunc(var1, " + Chr(34) + " " + Chr(34) + ")" + Chr(10) + "for A_Index3 , A_LoopField3 in ipairs(items3) do" + Chr(10) + "    A_LoopField3 = items3[A_Index3 - 0]" + Chr(10) + "    if (A_LoopField3 == " + Chr(34) + "bro" + Chr(34) + ") then" + Chr(10) + "        goto continue2" + Chr(10) + "    end" + Chr(10) + "    -- 3 will never print" + Chr(10) + "    print(A_Index3)" + Chr(10) + "    ::continue2::" + Chr(10) + "end" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "This approach with " + Chr(96) + "::" + doc_keyWordContinue + Chr(96) + " is used only for the 3 types of loops but NOT the " + Chr(96) + doc_keyWordWhileLoop + Chr(96) + " loop." + Chr(10) + Chr(10) + Chr(62) + " **Note:** Lua does not support a native " + Chr(96) + "continue" + Chr(96) + " statement. To mimic this behavior, we use a labeled " + Chr(96) + "goto" + Chr(96) + "—specifically " + Chr(96) + "goto continue" + Chr(96) + "—followed by a " + Chr(96) + "::continue::" + Chr(96) + " label at the end of the loop.  " + Chr(10) + Chr(62) + " This approach is **only required when converting to Lua**. If you're using HTVM with JavaScript, Python etc... as the target language, there's **no need to write or worry about " + Chr(96) + "::" + doc_keyWordContinue + Chr(96) + "**—it's automatically ignored or excluded in those environments." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Conclusion**" + Chr(10) + Chr(10) + "In HTVM, we have three main types of loops:" + Chr(10) + Chr(10) + "1. **Regular Loop** - " + Chr(96) + doc_keyWordLoop + Chr(96) + " - Simple iteration over a specified number of times." + Chr(10) + "2. **Loop Parse** - " + Chr(96) + doc_keyWordLoopParse + Chr(96) + " - Iterates over fields in a string or text, with customizable delimiters." + Chr(10) + "3. **Infinite Loop** - " + Chr(96) + doc_keyWordLoopInfinite + Chr(96) + " - A loop that runs indefinitely until broken manually or a condition is met." + Chr(10) + "4. **While Loop** - " + Chr(96) + doc_keyWordWhileLoop + Chr(96) + " - A standard loop that runs while a condition is true." + Chr(10) + Chr(10) + "Each of these loops is intuitive and makes it easy to handle a variety of looping needs. Make sure to use " + Chr(96) + doc_keyWordAIndex + Chr(96) + " and " + Chr(96) + doc_keyWordALoopField + Chr(96) + " where appropriate, and use the " + Chr(96) + doc_keyWordContinue + Chr(96) + " keyword to control loop flow. When converting to Lua, remember to add " + Chr(96) + "::" + doc_keyWordContinue + Chr(96) + " just before the loop ends." + Chr(10) + Chr(10) + "---" + Chr(10) + "";
    std::string outMDsec8 = "" + Chr(10) + "### Comments" + Chr(10) + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + Chr(10) + "## **Comments in HTVM**" + Chr(10) + Chr(10) + "Comments are essential for writing clear and maintainable code. They allow you to document your code without affecting how it runs. In HTVM, there are different types of comments: **Standalone Comments**, **Multi-line Comments**, **Inline Comments**, and **Comments in Programming Blocks**. Here's how each of them works:" + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Standalone Comments:**" + Chr(10) + Chr(10) + "**Standalone comments** are written on their own line and **will convert** properly when transforming to **other HTVM languages** or any target programming languages. These comments are perfect for leaving explanations or notes that need to be preserved across conversions." + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + hlepComments1 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "**💡 Tip:** Standalone comments are **ideal** when you need your notes to **convert** correctly across different languages and maintain clarity for others who may work with your code." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Multi-line Comments:**" + Chr(10) + Chr(10) + "**Multi-line comments** are used for writing longer explanations or comments that span multiple lines. They must **always start and end on their own lines**—you cannot place extra text before or after the opening and closing markers. Inside multi-line comments, you can write as much text as you want." + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + hlepComments2 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "#### **⚠️ Important Rules:**" + Chr(10) + "- The opening of a multi-line comment **must always be on its own line**. " + Chr(10) + "- The closing of a multi-line comment **must always be on its own line**." + Chr(10) + "- **🚨 WARNING**: If you write **code** inside multi-line comments, that code **MAY get converted** during language conversion! ❗️" + Chr(10) + "  - The code **won’t run**, but **it could still appear in the final code**! " + Chr(10) + "  - This means that if you have code inside multi-line comments, **be extra cautious**. If you don’t want the code to be accidentally included or converted, consider using **regular standalone comments** instead." + Chr(10) + Chr(10) + "**💡 Tip:** If you want the code inside multi-line comments to be **preserved** and not accidentally converted during the conversion process, **use regular standalone comments** instead of multi-line comments for code explanation. **Regular standalone comments** are safer for maintaining the integrity of your code." + Chr(10) + Chr(10) + "**⚠️ You can't use multiline comments inside a " + Chr(96) + "Gui" + Chr(96) + " code block.**" + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Inline Comments:**" + Chr(10) + Chr(10) + "**Inline comments** are written on the same line as your code. They’re useful for short explanations but **will disappear** when converting to **another HTVM language** or to other programming languages (e.g., **Python**, **JavaScript**, **C++**, **etc.**). This makes them **not recommended**, especially if you're working with code that will be converted, as they might carry important context that others won’t be able to see." + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + hlepComments3 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "**⚠️ Important:** **Avoid** using inline comments whenever possible. Inline comments **will disappear** even when converting to another HTVM language. This is because they won’t be included in the converted code. If you rely on these comments for important context, it’s better to avoid using them. **Not recommended**, unless you know exactly what you’re doing, as it can lead to the loss of important information when others view or convert your code." + Chr(10) + Chr(10) + Chr(62) + " *Note:* When converting code that includes Multiline Comments with commented-out code, the code will be converted into the target language as well. This ensures that even commented-out code is reflected in the converted language, making it easier for others to understand or reuse. This can be especially useful when converting to another HTVM language. For example, if someone is reading your code and has converted it to their own HTVM language, any commented-out code will be converted into their language, allowing them to read and understand what you intended to comment out. But only inside multiline comments will the code be converted into the target language." + Chr(10) + Chr(62) + Chr(10) + Chr(62) + " Regular Standalone Comments will also be converted, but only the comment keyword will be converted—nothing inside them will be converted. Only code inside Multiline Comments will be converted into the target language." + Chr(10) + Chr(62) + Chr(10) + Chr(62) + " But don’t worry, that code will not run because it’s just text, though it will be converted. This means you can use Multiline Comments to explain something without needing to include any code. Just plain text will work as well." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Comments in Programming Blocks:**" + Chr(10) + Chr(10) + "**Comments in programming blocks** must use the correct syntax for the target language. This is a **must**, not a best practice. You have to use the correct comment syntax based on the target language (e.g., **Python**, **JavaScript**, **C++**, **etc.**) inside their respective programming blocks." + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "py" + Chr(10) + "# This is a Python comment inside a Python programming block." + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "**⚠️ Important:** When working with **programming blocks**, make sure that you use the correct comment **syntax for that programming block language**. Otherwise, you may encounter issues in the code. Make sure you know which **characters** or **keywords** are used for comments in that language (for example, **#** for Python or **//** for JavaScript) to avoid mistakes." + Chr(10) + Chr(10) + "---" + Chr(10) + "";
    std::string outMDsec9 = Chr(10) + "### GUI (Graphical User Interface with HTVM)" + Chr(10) + "" + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + "" + Chr(10) + "**⚠️ Language Limitation: JavaScript Only**" + Chr(10) + "" + Chr(10) + "The GUI feature in HTVM allows for the creation of graphical user interfaces specifically for **web browsers (JavaScript)**. It generates the necessary HTML and JavaScript code. It **does not** support creating native GUIs for Python, C++, or other desktop environments. Using these commands when targeting non-JS languages will not work." + Chr(10) + "" + Chr(10) + "HTVM's GUI system lets you build interfaces with elements like buttons, text, edit fields, pictures, and more, using a simplified, flexible syntax designed for efficiency and fewer keystrokes. HTVM handles the basic HTML page setup implicitly when GUI commands are present." + Chr(10) + "" + Chr(10) + Chr(10) + "" + Chr(10) + "### GUI Commands" + Chr(10) + "" + Chr(10) + "HTVM uses two primary commands for building GUIs: " + Chr(96) + "gui" + Chr(96) + " for creating elements and containers, and " + Chr(96) + "guicontrol" + Chr(96) + " for modifying existing elements." + Chr(10) + "" + Chr(10) + "#### " + Chr(96) + "gui" + Chr(96) + " Command" + Chr(10) + "" + Chr(10) + "This command is used to **add new elements** (like buttons, text) or **create container " + Chr(96) + "div" + Chr(96) + "s** to organize your layout." + Chr(10) + "" + Chr(10) + "**Syntax:**" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + doc_keyWordComment + " Create a container (div) - Options separated by spaces OR commas" + Chr(10) + "gui [Option1:Value1] [Option2:Value2] ..." + Chr(10) + "gui [Option1:Value1],[Option2:Value2],..." + Chr(10) + "" + Chr(10) + "" + doc_keyWordComment + " Add a specific control element - ElementType followed by space/comma separated options" + Chr(10) + "gui " + "&lt;" + "ElementType" + "&gt;" + " [Option1:Value1] [Option2:Value2] ..." + Chr(10) + "gui " + "&lt;" + "ElementType" + "&gt;" + ",[Option1:Value1],[Option2:Value2],..." + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "*   **" + Chr(96) + "" + "&lt;" + "ElementType" + "&gt;" + "" + Chr(96) + "**: Specifies the type of control to add (e.g., " + Chr(96) + "button" + Chr(96) + ", " + Chr(96) + "text" + Chr(96) + ", " + Chr(96) + "edit" + Chr(96) + "). If omitted, a container (" + Chr(96) + "div" + Chr(96) + ") is created." + Chr(10) + "*   **" + Chr(96) + "[Options...]" + Chr(96) + "**: A series of options defining the element's properties. **Options can be separated by SPACES or COMMAS.**" + Chr(10) + "" + Chr(10) + "**Option Flexibility:**" + Chr(10) + "" + Chr(10) + "1.  **Separators**: Options can be separated by **SPACES** or **COMMAS**. You can mix them." + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + doc_keyWordComment + " Space separated is often cleaner also different style of defining values" + Chr(10) + "gui button x:50 y100 w" + Chr(34) + "200px" + Chr(34) + " h:" + Chr(34) + "30px" + Chr(34) + "" + Chr(10) + "" + doc_keyWordComment + " Comma separated also works" + Chr(10) + "gui button,x:" + Chr(34) + "50px" + Chr(34) + ",y:" + Chr(34) + "100px" + Chr(34) + ",w:" + Chr(34) + "200px" + Chr(34) + ",h:" + Chr(34) + "30px" + Chr(34) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "2.  **Key-Value Format**: Use " + Chr(96) + "key:value" + Chr(96) + " or single-letter prefixes " + Chr(96) + "kvalue" + Chr(96) + ". Many aliases exist (see [Options & Aliases](#options--aliases))." + Chr(10) + "3.  **Case Insensitivity**: Option *keys* and element types are case-insensitive. Option *values* (like IDs, text content, callback names) are case-sensitive." + Chr(10) + "4.  **" + Chr(96) + "add" + Chr(96) + " Keyword**: Optional and ignored (" + Chr(96) + "gui add button" + Chr(96) + " is the same as " + Chr(96) + "gui button" + Chr(96) + ")." + Chr(10) + "5.  **Grouping**: Options can span multiple lines using " + Chr(96) + "{...}" + Chr(96) + ", " + Chr(96) + "[...]" + Chr(96) + ", or " + Chr(96) + "(...)" + Chr(96) + " for readability. Separator rules (spaces or commas) still apply inside the group." + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + doc_keyWordComment + " Single line with spaces" + Chr(10) + "gui button x:" + Chr(34) + "10px" + Chr(34) + " y:" + Chr(34) + "10px" + Chr(34) + " w:" + Chr(34) + "100px" + Chr(34) + " h:" + Chr(34) + "30px" + Chr(34) + " id:" + Chr(34) + "myBtn" + Chr(34) + " callback:MyAction value:" + Chr(34) + "Click" + Chr(34) + "" + Chr(10) + "" + Chr(10) + "" + doc_keyWordComment + " Multi-line grouping (using spaces within the lines)" + Chr(10) + "gui button {" + Chr(10) + "    x:" + Chr(34) + "10px" + Chr(34) + " y:" + Chr(34) + "10px" + Chr(34) + "" + Chr(10) + "    width:" + Chr(34) + "100px" + Chr(34) + " height:" + Chr(34) + "30px" + Chr(34) + "" + Chr(10) + "    id:" + Chr(34) + "myBtn" + Chr(34) + "" + Chr(10) + "    callback:MyAction" + Chr(10) + "    value:" + Chr(34) + "Click" + Chr(34) + "" + Chr(10) + "}" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**Parenting & Default Container:**" + Chr(10) + "" + Chr(10) + "*   Every element belongs inside a container." + Chr(10) + "*   If no " + Chr(96) + "parentId" + Chr(96) + " is specified when using the " + Chr(96) + "gui" + Chr(96) + " command to create an element, it is placed in the default background container (internally referred to as " + Chr(96) + "div0" + Chr(96) + ")." + Chr(10) + "*   To place an element inside *your* custom container (e.g., one created with " + Chr(96) + "gui id:" + Chr(34) + "myPanel" + Chr(34) + " ..." + Chr(96) + "), you **must** use the " + Chr(96) + "parentId:" + Chr(34) + "myPanel" + Chr(34) + "" + Chr(96) + " option on the element being created." + Chr(10) + "" + Chr(10) + "#### " + Chr(96) + "guicontrol" + Chr(96) + " Command" + Chr(10) + "" + Chr(10) + "Modifies properties of an **existing** GUI element." + Chr(10) + "" + Chr(10) + "**Syntax:**" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + doc_keyWordComment + " Single line modification" + Chr(10) + "guicontrol [Option1:Value1] [Option2:Value2] ..." + Chr(10) + "guicontrol [Option1:Value1],[Option2:Value2],..." + Chr(10) + "" + Chr(10) + "" + doc_keyWordComment + " Multi-line modification using flexible grouping (), [], or {}" + Chr(10) + "guicontrol (" + Chr(10) + "    Option1:Value1" + Chr(10) + "    Option2:Value2" + Chr(10) + "    ..." + Chr(10) + ")" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "*   **" + Chr(96) + "[Options...]" + Chr(96) + "**: **SPACE or COMMA-SEPARATED** options." + Chr(10) + "    *   **MUST** include " + Chr(96) + "id:" + "&lt;" + "element_id" + "&gt;" + "" + Chr(96) + " (e.g., " + Chr(96) + "id:" + Chr(34) + "myButton" + Chr(34) + "" + Chr(96) + ") to target the element." + Chr(10) + "    *   **" + Chr(96) + "parentId" + Chr(96) + " Requirement (CRITICAL CLARIFICATION):**" + Chr(10) + "        *   **Case 1: No Custom Containers Created:** If your entire script **only** adds elements directly to the background (never using " + Chr(96) + "gui { id:" + Chr(34) + "..." + Chr(34) + " ... }" + Chr(96) + " to create a custom container), then " + Chr(96) + "parentId" + Chr(96) + " is **optional** for " + Chr(96) + "guicontrol" + Chr(96) + ". HTVM will assume the target element is on the default background (" + Chr(96) + "div0" + Chr(96) + ")." + Chr(10) + "        *   **Case 2: Custom Containers Exist:** As soon as you create **even one** custom container using " + Chr(96) + "gui { id:" + Chr(34) + "..." + Chr(34) + " ... }" + Chr(96) + ", the " + Chr(96) + "parentId" + Chr(96) + " option becomes **mandatory** for **all** " + Chr(96) + "guicontrol" + Chr(96) + " commands to avoid ambiguity." + Chr(10) + "            *   To target an element **inside** a custom container: Use " + Chr(96) + "parentId:" + Chr(34) + "containerId" + Chr(34) + "" + Chr(96) + "." + Chr(10) + "            *   To target an element that is still on the **default background** (or a top-level container itself): Don't use " + Chr(96) + "parentId:" + Chr(34) + "..." + Chr(34) + "" + Chr(96) + "." + Chr(10) + "    *   Other options specify the changes (e.g., " + Chr(96) + "value:" + Chr(34) + "NewText" + Chr(34) + "" + Chr(96) + ", " + Chr(96) + "isVisible:false" + Chr(96) + ")." + Chr(10) + "" + Chr(10) + "**Mapping HTH Actions to HTVM Options (using " + Chr(96) + "guicontrol" + Chr(96) + "):**" + Chr(10) + "" + Chr(10) + "*   **Move/Resize**: Use " + Chr(96) + "x:" + Chr(96) + ", " + Chr(96) + "y:" + Chr(96) + ", " + Chr(96) + "width:" + Chr(96) + ", " + Chr(96) + "height:" + Chr(96) + " options with pre-formatted string values (e.g., " + Chr(96) + "x:varX_px" + Chr(96) + ")." + Chr(10) + "*   **Text**: Use " + Chr(96) + "value:" + Chr(96) + " (e.g., " + Chr(96) + "guicontrol id:" + Chr(34) + "myLabel" + Chr(34) + ",value:" + Chr(34) + "New Text" + Chr(34) + "" + Chr(96) + ")." + Chr(10) + "*   **Picture**: Use " + Chr(96) + "value:" + Chr(96) + " with a new URL (e.g., " + Chr(96) + "guicontrol id:" + Chr(34) + "myImage" + Chr(34) + ",value:" + Chr(34) + "http://new.url/img.png" + Chr(34) + "" + Chr(96) + ")." + Chr(10) + "*   **Hide/Show**: Use " + Chr(96) + "isVisible:false" + Chr(96) + " or " + Chr(96) + "isVisible:true" + Chr(96) + "." + Chr(10) + "*   **Enable/Disable**: Use " + Chr(96) + "isEnabled:false" + Chr(96) + " or " + Chr(96) + "isEnabled:true" + Chr(96) + "." + Chr(10) + "*   **Destroy**: Use " + Chr(96) + "isDeleting:true" + Chr(96) + "." + Chr(10) + "*   **Font**: Use " + Chr(96) + "size:" + Chr(96) + " for font size (e.g., " + Chr(96) + "size:16" + Chr(96) + ") and " + Chr(96) + "color:" + Chr(96) + " for text color (e.g., " + Chr(96) + "color:" + Chr(34) + "#FF0000" + Chr(34) + "" + Chr(96) + "). Use " + Chr(96) + "rawCss:" + Chr(96) + " for font family (e.g., " + Chr(96) + "rawCss:" + Chr(34) + "font-family:Courier;" + Chr(34) + "" + Chr(96) + ")." + Chr(10) + "" + Chr(10) + "#### Multiple GUI Windows (" + Chr(96) + "num:" + Chr(96) + " prefix - *NOT SUPPORTED*)" + Chr(10) + "" + Chr(10) + "HTVM **does not** use HTH's " + Chr(96) + "Gui 2:" + Chr(96) + ", " + Chr(96) + "Gui 3:" + Chr(96) + " syntax. Simulate multiple areas by:" + Chr(10) + "1.  Creating container " + Chr(96) + "div" + Chr(96) + "s: " + Chr(96) + "gui id:" + Chr(34) + "window1" + Chr(34) + ",..." + Chr(96) + ", " + Chr(96) + "gui id:" + Chr(34) + "window2" + Chr(34) + ",..." + Chr(96) + "" + Chr(10) + "2.  Placing elements inside using " + Chr(96) + "parentId:" + Chr(34) + "window1" + Chr(34) + "" + Chr(96) + " or " + Chr(96) + "parentId:" + Chr(34) + "window2" + Chr(34) + "" + Chr(96) + "." + Chr(10) + "3.  Toggling visibility using " + Chr(96) + "guicontrol id:" + Chr(34) + "window1" + Chr(34) + ",isVisible:false" + Chr(96) + " etc." + Chr(10) + "" + Chr(10) + "### GUI Elements (Controls)" + Chr(10) + "" + Chr(10) + "Add elements using " + Chr(96) + "gui " + "&lt;" + "ElementType" + "&gt;" + " [Options...]" + Chr(96) + ":" + Chr(10) + "" + Chr(10) + "| Element Type | Description                                     | Default ID Format | Default Callback Format | Notes                                                                           |" + Chr(10) + "| :----------- | :---------------------------------------------- | :---------------- | :---------------------- | :------------------------------------------------------------------------------ |" + Chr(10) + "| " + Chr(96) + "button" + Chr(96) + "     | Clickable button                                | " + Chr(96) + "button" + Chr(96) + " + Counter  | " + Chr(96) + "Button" + Chr(96) + " + Counter      |                                                                                 |" + Chr(10) + "| " + Chr(96) + "text" + Chr(96) + "       | Static text label                               | " + Chr(96) + "text" + Chr(96) + " + Counter    | " + Chr(96) + "Text" + Chr(96) + " + Counter        |                                                                                 |" + Chr(10) + "| " + Chr(96) + "edit" + Chr(96) + "       | Text input field                                | " + Chr(96) + "edit" + Chr(96) + " + Counter    | " + Chr(96) + "Edit" + Chr(96) + " + Counter        | Use callback + global var/OSP struct to get value.                              |" + Chr(10) + "| " + Chr(96) + "picture" + Chr(96) + "    | Image display (" + Chr(96) + "" + "&lt;" + "img" + "&gt;" + "" + Chr(96) + ")                         | " + Chr(96) + "picture" + Chr(96) + " + Counter | " + Chr(96) + "Picture" + Chr(96) + " + Counter     | " + Chr(96) + "value" + Chr(96) + " is URL. Local paths *not* auto-encoded.                               |" + Chr(10) + "| " + Chr(96) + "toggle" + Chr(96) + "     | Checkbox / Switch                               | " + Chr(96) + "toggle" + Chr(96) + " + Counter  | " + Chr(96) + "Toggle" + Chr(96) + " + Counter      | " + Chr(96) + "value" + Chr(96) + " is " + Chr(96) + "true" + Chr(96) + "/" + Chr(96) + "false" + Chr(96) + ". " + Chr(96) + "A_Value" + Chr(96) + " in callback is boolean.                    |" + Chr(10) + "| " + Chr(96) + "rectangle" + Chr(96) + "  | Colored rectangle (" + Chr(96) + "" + "&lt;" + "div" + "&gt;" + "" + Chr(96) + ")                     | " + Chr(96) + "rectangle" + Chr(96) + " + Counter | " + Chr(96) + "Rectangle" + Chr(96) + " + Counter | Use " + Chr(96) + "backgroundColor" + Chr(96) + ".                                                        |" + Chr(10) + "| " + Chr(96) + "circle" + Chr(96) + "     | Colored circle (" + Chr(96) + "" + "&lt;" + "div" + "&gt;" + "" + Chr(96) + " + round border)         | " + Chr(96) + "circle" + Chr(96) + " + Counter  | " + Chr(96) + "Circle" + Chr(96) + " + Counter      | Use " + Chr(96) + "backgroundColor" + Chr(96) + ".                                                        |" + Chr(10) + "| " + Chr(96) + "video" + Chr(96) + "      | Video player (" + Chr(96) + "" + "&lt;" + "video" + "&gt;" + "" + Chr(96) + ")                        | " + Chr(96) + "video" + Chr(96) + " + Counter   | " + Chr(96) + "Video" + Chr(96) + " + Counter       | " + Chr(96) + "value" + Chr(96) + " is URL (video file or YouTube embed).                                 |" + Chr(10) + "| " + Chr(96) + "dropdown" + Chr(96) + "   | Select dropdown (" + Chr(96) + "" + "&lt;" + "select" + "&gt;" + "" + Chr(96) + ")                    | " + Chr(96) + "dropdown" + Chr(96) + " + Counter| " + Chr(96) + "Dropdown" + Chr(96) + " + Counter    | " + Chr(96) + "value" + Chr(96) + " is pipe separated options. **element1&#124;element2&#124;element3** |" + Chr(10) + "| " + Chr(96) + "iframe" + Chr(96) + "     | Embed external content (" + Chr(96) + "" + "&lt;" + "iframe" + "&gt;" + "" + Chr(96) + ")             | " + Chr(96) + "iframe" + Chr(96) + " + Counter  | " + Chr(96) + "Iframe" + Chr(96) + " + Counter      | " + Chr(96) + "value" + Chr(96) + " is URL.                                                               |" + Chr(10) + "" + Chr(10) + "(Counters start at 0 for each type, e.g., " + Chr(96) + "button0" + Chr(96) + ", " + Chr(96) + "Button0" + Chr(96) + ", " + Chr(96) + "edit0" + Chr(96) + ", " + Chr(96) + "Edit0" + Chr(96) + "...)" + Chr(10) + "" + Chr(10) + "#### Exmaple:" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet50 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "### Options & Aliases " + "" + Chr(10) + "" + Chr(10) + "" + Chr(10) + "Configure elements using **SPACE or COMMA-SEPARATED** options." + Chr(10) + "" + Chr(10) + "**Key Rules:**" + Chr(10) + "" + Chr(10) + "1.  **Separators**: Use Spaces or Commas between options (" + Chr(96) + "x:" + Chr(34) + "10px" + Chr(34) + " y:" + Chr(34) + "10px" + Chr(34) + "" + Chr(96) + " or " + Chr(96) + "x:" + Chr(34) + "10px" + Chr(34) + ",y:" + Chr(34) + "10px" + Chr(34) + "" + Chr(96) + ")." + Chr(10) + "2.  **No Spaces in Direct Values**: Store values like " + Chr(96) + "var1 + var2" + Chr(96) + " in a variable (" + Chr(96) + "str hw := var1 + var2" + Chr(96) + ") and use " + Chr(96) + "value:hw" + Chr(96) + "." + Chr(10) + "3.  **Quote Literal IDs/ParentIDs**: Use quotes for string literals (" + Chr(96) + "id:" + Chr(34) + "myId" + Chr(34) + "" + Chr(96) + "). Do not quote variables (" + Chr(96) + "id:myIdVar" + Chr(96) + ")." + Chr(10) + "4.  **Pre-concatenate Units**: For " + Chr(96) + "x" + Chr(96) + ", " + Chr(96) + "y" + Chr(96) + ", " + Chr(96) + "width" + Chr(96) + ", " + Chr(96) + "height" + Chr(96) + ", prepare string variables including " + Chr(96) + "px" + Chr(96) + " or " + Chr(96) + "%" + Chr(96) + " **before** using them in the command (e.g., " + Chr(96) + "str width_px := myWidth . " + Chr(34) + "px" + Chr(34) + "" + Chr(96) + ", then use " + Chr(96) + "width:width_px" + Chr(96) + ")." + Chr(10) + "5.  **Case Sensitivity**: Keys/aliases/types are case-insensitive; values are case-sensitive." + Chr(10) + "" + Chr(10) + "**Common Options Table:**" + Chr(10) + "" + Chr(10) + "| Canonical JS      | Purpose                     | Single-Letter Prefix | Colon Aliases (Examples)                    | Notes                                                                 |" + Chr(10) + "| :---------------- | :-------------------------- | :------------------- | :------------------------------------------ | :-------------------------------------------------------------------- |" + Chr(10) + "| " + Chr(96) + "id" + Chr(96) + "              | Unique Element Identifier   | " + Chr(96) + "i" + Chr(96) + ", " + Chr(96) + "v" + Chr(96) + "             | " + Chr(96) + "id" + Chr(96) + ", " + Chr(96) + "elementId" + Chr(96) + ", " + Chr(96) + "eid" + Chr(96) + "                    | String. **Quote if literal.** Defaults if omitted.                    |" + Chr(10) + "| " + Chr(96) + "parentId" + Chr(96) + "        | ID of Container Element     | " + Chr(96) + "p" + Chr(96) + "                  | " + Chr(96) + "parentId" + Chr(96) + ", " + Chr(96) + "pid" + Chr(96) + ", " + Chr(96) + "divId" + Chr(96) + "                  | String. Defaults to " + Chr(96) + "" + Chr(34) + "div0" + Chr(34) + "" + Chr(96) + ". **Quote if literal.**                   |" + Chr(10) + "| " + Chr(96) + "x" + Chr(96) + "               | Horizontal Position         | " + Chr(96) + "x" + Chr(96) + "                  | " + Chr(96) + "x" + Chr(96) + ", " + Chr(96) + "xPos" + Chr(96) + ", " + Chr(96) + "xCoord" + Chr(96) + "                       | **String var required (e.g., " + Chr(96) + "myVarX_px" + Chr(96) + ").** Supports " + Chr(96) + "px" + Chr(96) + " or " + Chr(96) + "%" + Chr(96) + ".    |" + Chr(10) + "| " + Chr(96) + "y" + Chr(96) + "               | Vertical Position           | " + Chr(96) + "y" + Chr(96) + "                  | " + Chr(96) + "y" + Chr(96) + ", " + Chr(96) + "yPos" + Chr(96) + ", " + Chr(96) + "yCoord" + Chr(96) + "                       | **String var required (e.g., " + Chr(96) + "myVarY_px" + Chr(96) + ").** Supports " + Chr(96) + "px" + Chr(96) + " or " + Chr(96) + "%" + Chr(96) + ".    |" + Chr(10) + "| " + Chr(96) + "width" + Chr(96) + "           | Element Width               | " + Chr(96) + "w" + Chr(96) + "                  | " + Chr(96) + "width" + Chr(96) + ", " + Chr(96) + "wight" + Chr(96) + ", " + Chr(96) + "widh" + Chr(96) + "                    | **String var required (e.g., " + Chr(96) + "myVarW_px" + Chr(96) + ").** Supports " + Chr(96) + "px" + Chr(96) + " or " + Chr(96) + "%" + Chr(96) + ".    |" + Chr(10) + "| " + Chr(96) + "height" + Chr(96) + "          | Element Height              | " + Chr(96) + "h" + Chr(96) + "                  | " + Chr(96) + "height" + Chr(96) + ", " + Chr(96) + "hight" + Chr(96) + ", " + Chr(96) + "heigth" + Chr(96) + "                 | **String var required (e.g., " + Chr(96) + "myVarH_px" + Chr(96) + ").** Supports " + Chr(96) + "px" + Chr(96) + " or " + Chr(96) + "%" + Chr(96) + ".    |" + Chr(10) + "| " + Chr(96) + "zIndex" + Chr(96) + "          | Stacking Order              | " + Chr(96) + "z" + Chr(96) + "                  | " + Chr(96) + "zIndex" + Chr(96) + ", " + Chr(96) + "z-index" + Chr(96) + "                         | Integer.                                                              |" + Chr(10) + "| " + Chr(96) + "value" + Chr(96) + "           | Content/State             | " + Chr(96) + "d" + Chr(96) + "                  | " + Chr(96) + "value" + Chr(96) + ", " + Chr(96) + "val" + Chr(96) + ", " + Chr(96) + "displayValue" + Chr(96) + "              | Text/URL/Bool/Options. **Use variable for spaces/commas.**          |" + Chr(10) + "| " + Chr(96) + "placeholder" + Chr(96) + "     | Placeholder text for Edit | " + Chr(96) + "q" + Chr(96) + "                  | " + Chr(96) + "placeholder" + Chr(96) + ", " + Chr(96) + "plc" + Chr(96) + ", " + Chr(96) + "ph" + Chr(96) + ", " + Chr(96) + "grayText" + Chr(96) + "      | String. **Use variable for spaces.**                                  |" + Chr(10) + "| " + Chr(96) + "callback" + Chr(96) + "        | Function on Interaction     | " + Chr(96) + "g" + Chr(96) + ", " + Chr(96) + "f" + Chr(96) + "             | " + Chr(96) + "callback" + Chr(96) + ", " + Chr(96) + "func" + Chr(96) + ", " + Chr(96) + "fn" + Chr(96) + ", " + Chr(96) + "call" + Chr(96) + "            | String (HTVM Label Name). Defaults if omitted.                        |" + Chr(10) + "| " + Chr(96) + "backgroundColor" + Chr(96) + " | Background Color            | " + Chr(96) + "o" + Chr(96) + "                  | " + Chr(96) + "backgroundColor" + Chr(96) + ", " + Chr(96) + "bgColor" + Chr(96) + ", " + Chr(96) + "bg" + Chr(96) + ", " + Chr(96) + "bgc" + Chr(96) + " | String (" + Chr(96) + "" + Chr(34) + "red" + Chr(34) + "" + Chr(96) + ", " + Chr(96) + "" + Chr(34) + "#FF0000" + Chr(34) + "" + Chr(96) + "). Auto-adds " + Chr(96) + "#" + Chr(96) + " for hex.                 |" + Chr(10) + "| " + Chr(96) + "color" + Chr(96) + "           | Text/Foreground Color       | " + Chr(96) + "c" + Chr(96) + "                  | " + Chr(96) + "color" + Chr(96) + ", " + Chr(96) + "clr" + Chr(96) + "                              | String (" + Chr(96) + "" + Chr(34) + "blue" + Chr(34) + "" + Chr(96) + ", " + Chr(96) + "" + Chr(34) + "#00F" + Chr(34) + "" + Chr(96) + "). Auto-adds " + Chr(96) + "#" + Chr(96) + " for hex.                 |" + Chr(10) + "| " + Chr(96) + "rounding" + Chr(96) + "        | Corner Rounding (px)        | " + Chr(96) + "r" + Chr(96) + "                  | " + Chr(96) + "rounding" + Chr(96) + ", " + Chr(96) + "round" + Chr(96) + ", " + Chr(96) + "rnd" + Chr(96) + "                  | Integer (pixels).                                                     |" + Chr(10) + "| " + Chr(96) + "border" + Chr(96) + "          | Element Border              | " + Chr(96) + "b" + Chr(96) + "                  | " + Chr(96) + "border" + Chr(96) + ", " + Chr(96) + "boder" + Chr(96) + ", " + Chr(96) + "outline" + Chr(96) + "                | String (CSS syntax). **Use var for spaces.**                          |" + Chr(10) + "| " + Chr(96) + "rawCss" + Chr(96) + "          | Additional CSS Styles       | " + Chr(96) + "l" + Chr(96) + "                  | " + Chr(96) + "rawCss" + Chr(96) + ", " + Chr(96) + "css" + Chr(96) + ", " + Chr(96) + "style" + Chr(96) + ", " + Chr(96) + "luxury" + Chr(96) + "          | String (CSS rules). **Use var for multiple.**                         |" + Chr(10) + "| " + Chr(96) + "size" + Chr(96) + "            | Font Size (px)              | " + Chr(96) + "s" + Chr(96) + "                  | " + Chr(96) + "size" + Chr(96) + ", " + Chr(96) + "sz" + Chr(96) + "                                | Integer (pixels).                                                     |" + Chr(10) + "| " + Chr(96) + "isEnabled" + Chr(96) + "       | Enable/Disable Interaction  | " + Chr(96) + "a" + Chr(96) + "                  | " + Chr(96) + "isEnabled" + Chr(96) + ", " + Chr(96) + "isEnb" + Chr(96) + "                        | Boolean (" + Chr(96) + "true" + Chr(96) + "/" + Chr(96) + "false" + Chr(96) + ").                                             |" + Chr(10) + "| " + Chr(96) + "isVisible" + Chr(96) + "       | Show/Hide Element           | " + Chr(96) + "u" + Chr(96) + "                  | " + Chr(96) + "isVisible" + Chr(96) + ", " + Chr(96) + "isVsb" + Chr(96) + "                        | Boolean (" + Chr(96) + "true" + Chr(96) + "/" + Chr(96) + "false" + Chr(96) + ").                                             |" + Chr(10) + "| " + Chr(96) + "isDeleting" + Chr(96) + "      | Remove Element from GUI   | " + Chr(96) + "n" + Chr(96) + "                  | " + Chr(96) + "isDeleting" + Chr(96) + ", " + Chr(96) + "del" + Chr(96) + ", " + Chr(96) + "remove" + Chr(96) + ", " + Chr(96) + "rm" + Chr(96) + "         | Boolean (" + Chr(96) + "true" + Chr(96) + "). Use with " + Chr(96) + "guicontrol" + Chr(96) + ".                              |" + Chr(10) + "" + Chr(10) + "*(See HTVM source (" + Chr(96) + "guiParserStep4" + Chr(96) + ") for a full alias list.)*" + Chr(10) + "" + Chr(10) + "#### Exmaple:" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet51 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "### Callbacks and State Management" + Chr(10) + "" + Chr(10) + "Callbacks connect GUI events to HTVM logic (labels ending in " + Chr(96) + "subout" + Chr(96) + "). Logic **must start on the line AFTER the label**, not on the same line. Use " + Chr(96) + "await" + Chr(96) + " before functions like " + Chr(96) + "MsgBox" + Chr(96) + " that return Promises in JavaScript." + Chr(10) + "" + Chr(10) + "**Managing State (Input Example):**" + Chr(10) + "" + Chr(10) + "To retrieve data entered by the user (e.g., in an " + Chr(96) + "edit" + Chr(96) + " field), store the data from the input's callback (" + Chr(96) + "A_Value" + Chr(96) + ") into a shared state, typically using global variables or an OSP struct. Using an OSP " + Chr(96) + "struct" + Chr(96) + " is often better for organization, but global variables work too." + Chr(10) + "" + Chr(10) + "**Getting Input Example (using OSP Struct - Recommended):**" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet52 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**Callback Parameters:** " + Chr(96) + "A_Id" + Chr(96) + ", " + Chr(96) + "A_Value" + Chr(96) + ", " + Chr(96) + "A_Event" + Chr(96) + " provide context within the callback label." + Chr(10) + "" + Chr(10) + "### Examples" + Chr(10) + "" + Chr(10) + "*(Using space separation, pre-concatenated units, OSP struct for state where beneficial, correct callback formatting, and await for MsgBox)*" + Chr(10) + "" + Chr(10) + "**Example 1: Simple Input and Button (using OSP Struct)**" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet53 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**Example 2: Sized Container (Hardcoded)**" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet54 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**Example 3: Button Grid using Loops (Using A_Id)**" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet55 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**Example 4: Toggle, Dropdown, Picture Update (using OSP Struct)**" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet56 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**Example 5: Using " + Chr(96) + "rawCss" + Chr(96) + " for Styling**" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet57 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**Example 6: HTVM Simulated Numeric Adjuster Using Buttons and Input Field (0–100 Range)**" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet58 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**Example 7: " + Chr(96) + "Tic-tac-toe" + Chr(96) + "**" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet59 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "### Summary" + Chr(10) + "" + Chr(10) + "HTVM's GUI system offers a simplified yet powerful way to build graphical user interfaces directly within your HTVM code, targeting **JavaScript web environments**. By using the intuitive " + Chr(96) + "gui" + Chr(96) + " command to define elements and containers, and " + Chr(96) + "guicontrol" + Chr(96) + " to modify them dynamically, you can build interactive web applications. The system leverages flexible option syntax (spaces, commas, shorthand, multi-line grouping) and automatically handles underlying HTML/CSS/JS generation, adhering to HTVM's philosophy of **reducing keystrokes and complexity**. Understanding the conditional requirement for " + Chr(96) + "parentId" + Chr(96) + " in " + Chr(96) + "guicontrol" + Chr(96) + " (it's only optional if no custom containers are defined) is key to correctly manipulating elements." + Chr(10) + "" + Chr(10) + "The " + Chr(96) + "gui" + Chr(96) + " and " + Chr(96) + "guicontrol" + Chr(96) + " features allows developers to focus on interface logic and layout using their custom HTVM syntax, bridging the gap between high-level design and functional web UIs." + Chr(10) + Chr(10) + "---" + Chr(10);
    std::string outMDsec10 = Chr(10) + Chr(10) + "### Backend in HTVM" + Chr(10) + "" + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + "" + Chr(10) + "**⚠️ Language Limitation: Python Only (Flask)**" + Chr(10) + "" + Chr(10) + "HTVM's Backend functionality generates **Python** code using **Flask**. It does **not** support other languages like JavaScript (Node.js) for backend generation. Use these commands only when targeting Python (" + Chr(96) + "py" + Chr(96) + ")." + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "" + Chr(10) + "### Introduction" + Chr(10) + "" + Chr(10) + "HTVM provides simple commands to create basic web backends in Python. This enables communication between your HTVM frontend (JavaScript GUI) and a server for tasks needing server-side logic or access. Communication is primarily plain text over HTTP (defaulting to POST)." + Chr(10) + "" + Chr(10) + "### Backend Commands" + Chr(10) + "" + Chr(10) + "Use these commands in your backend HTVM file (" + Chr(96) + ".htvm" + Chr(96) + " targeted for Python). They **must** use comma separators." + Chr(10) + "" + Chr(10) + "#### " + Chr(96) + "fileinit, filename" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**Essential.** Initializes Flask and sets the root route (" + Chr(96) + "/" + Chr(96) + ") to serve your main frontend file." + Chr(10) + "" + Chr(10) + "*   **" + Chr(96) + "filename" + Chr(96) + "**: Name of your frontend file (e.g., " + Chr(96) + "main.js" + Chr(96) + ", " + Chr(96) + "index.html" + Chr(96) + "). Must be in the same directory as the generated Python script." + Chr(10) + "*   If " + Chr(96) + ".js" + Chr(96) + ", HTVM wraps it in basic HTML (with " + Chr(96) + "sweetalert2" + Chr(96) + "). If " + Chr(96) + ".html" + Chr(96) + ", served directly." + Chr(10) + "*   **Must be used before " + Chr(96) + "endpoint," + Chr(96) + " or " + Chr(96) + "port," + Chr(96) + ".**" + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "" + Chr(10) + "#### " + Chr(96) + "endpoint, route_or_label_name, [label_name_if_different], [method]" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "Registers an HTVM label (backend logic block) as an HTTP endpoint." + Chr(10) + "" + Chr(10) + "*   **" + Chr(96) + "route_or_label_name" + Chr(96) + " (Mandatory):**" + Chr(10) + "    *   If **only this parameter** is provided (besides the optional method), it serves as **both** the URL path (e.g., " + Chr(96) + "/hello" + Chr(96) + ") and the HTVM label name (e.g., " + Chr(96) + "hello:" + Chr(96) + ")." + Chr(10) + "    *   If " + Chr(96) + "label_name_if_different" + Chr(96) + " is also provided, this parameter is treated solely as the URL path (e.g., " + Chr(96) + "processData" + Chr(96) + " becomes route " + Chr(96) + "/processData" + Chr(96) + "). No leading/trailing slashes needed here." + Chr(10) + "*   **" + Chr(96) + "[label_name_if_different]" + Chr(96) + " (Optional):** The exact HTVM label name (case-sensitive) if it's different from the URL route name. If omitted, the value from " + Chr(96) + "route_or_label_name" + Chr(96) + " is used." + Chr(10) + "*   **" + Chr(96) + "[method]" + Chr(96) + " (Optional):** HTTP method (" + Chr(96) + "POST" + Chr(96) + ", " + Chr(96) + "GET" + Chr(96) + ", etc.). Defaults to " + Chr(96) + "POST" + Chr(96) + "." + Chr(10) + "" + Chr(10) + "**Examples:**" + Chr(10) + "" + Chr(10) + "Registers route " + Chr(34) + "/myapi" + Chr(34) + " linked to label " + Chr(34) + "myapi:" + Chr(34) + " (POST default)" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "endpoint, myapi" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "Registers route " + Chr(34) + "/user/data" + Chr(34) + " linked to label " + Chr(34) + "GetUserData:" + Chr(34) + " (GET method)" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "endpoint, user/data, GetUserData, GET" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "" + Chr(10) + "#### " + Chr(96) + "port, port_number" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "Specifies the network port the Flask server will listen on." + Chr(10) + "" + Chr(10) + "*   **" + Chr(96) + "port_number" + Chr(96) + "**: e.g., " + Chr(96) + "5000" + Chr(96) + ", " + Chr(96) + "8080" + Chr(96) + " etc." + Chr(10) + "*   Defaults to " + Chr(96) + "8000" + Chr(96) + " if omitted." + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "" + Chr(10) + "### Defining Backend Logic (Labels & " + Chr(96) + "subout" + Chr(96) + ")" + Chr(10) + "" + Chr(10) + "Write endpoint logic within labeled blocks ending with " + Chr(96) + "subout" + Chr(96) + ". Logic **must start on the line after** the label." + Chr(10) + "" + Chr(10) + "*   **Labels**: Define the start (e.g., " + Chr(96) + "myEndpoint:" + Chr(96) + "). Matched with " + Chr(96) + "route_or_label_name" + Chr(96) + " in " + Chr(96) + "endpoint," + Chr(96) + "." + Chr(10) + "*   **" + Chr(96) + "A_Input" + Chr(96) + "**: Variable holding plain text data from the frontend request body." + Chr(10) + "*   **Return Value**: **Must** " + Chr(96) + "return" + Chr(96) + " a **string** (the plain text response)." + Chr(10) + "*   **" + Chr(96) + "subout" + Chr(96) + "**: Marks the end of the block." + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet60 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "### Frontend-Backend Interaction (" + Chr(96) + "callBackend" + Chr(96) + ")" + Chr(10) + "" + Chr(10) + "In your **frontend** HTVM code (JavaScript GUI), use the " + Chr(96) + "callBackend" + Chr(96) + " function." + Chr(10) + "" + Chr(10) + "*   **" + Chr(96) + "async callBackend(endpointPath, textData, [method='POST'])" + Chr(96) + "**:" + Chr(10) + "    *   Sends plain text " + Chr(96) + "textData" + Chr(96) + " to " + Chr(96) + "endpointPath" + Chr(96) + " using " + Chr(96) + "method" + Chr(96) + "." + Chr(10) + "    *   **" + Chr(96) + "endpointPath" + Chr(96) + "**: Backend URL path. **Must start with a slash** (e.g., " + Chr(96) + "" + Chr(34) + "/hello" + Chr(34) + "" + Chr(96) + ")." + Chr(10) + "    *   **" + Chr(96) + "textData" + Chr(96) + "**: String data to send." + Chr(10) + "    *   **" + Chr(96) + "[method='POST']" + Chr(96) + "** (Optional): HTTP method. Match backend definition. Defaults to " + Chr(96) + "'POST'" + Chr(96) + "." + Chr(10) + "    *   **Returns**: Promise resolving to the plain text response string. Use " + Chr(96) + "await" + Chr(96) + "." + Chr(10) + "    *   **Throws**: Error on network/server failure." + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet61 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "### Example: Simple Backend & Frontend" + Chr(10) + "" + Chr(10) + "**1. Backend Code (" + Chr(96) + "backend.htvm" + Chr(96) + ")**" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet62 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**2. Frontend Code (" + Chr(96) + "frontend.htvm" + Chr(96) + " -" + Chr(62) + " generates " + Chr(96) + "frontend.js" + Chr(96) + ")**" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet63 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**To Run:**" + Chr(10) + "" + Chr(10) + "1.  **Transpile Backend:** " + Chr(96) + "HTVM backend.htvm HTVM-instructions.txt py" + Chr(96) + "" + Chr(10) + "2.  **Transpile Frontend:** " + Chr(96) + "HTVM frontend.htvm HTVM-instructions.txt js" + Chr(96) + "" + Chr(10) + "3.  **Place Files:** Ensure " + Chr(96) + "frontend.js" + Chr(96) + " is in the same directory as " + Chr(96) + "backend.py" + Chr(96) + "." + Chr(10) + "4.  **Run Backend:** " + Chr(96) + "python backend.py" + Chr(96) + "" + Chr(10) + "5.  **Access Frontend:** Open browser to " + Chr(96) + "http://localhost:5678" + Chr(96) + ". Interact with the GUI." + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "" + Chr(10) + "### Summary" + Chr(10) + "" + Chr(10) + "HTVM's backend feature simplifies the creation of basic web servers using **Python and Flask**. By leveraging straightforward commands like " + Chr(96) + "fileinit," + Chr(96) + ", " + Chr(96) + "endpoint," + Chr(96) + ", and " + Chr(96) + "port," + Chr(96) + ", developers can quickly set up routes that map to specific HTVM logic blocks defined by labels. This system facilitates communication between an HTVM JavaScript frontend (using the " + Chr(96) + "callBackend" + Chr(96) + " function) and the Python server, primarily through plain text requests and responses. This functionality provides a streamlined way to add server-side processing capabilities to HTVM projects without requiring extensive backend framework knowledge, aligning with HTVM's philosophy of simplifying development workflows." + Chr(10) + "" + Chr(10) + "---" + Chr(10) + Chr(10);
    std::string outMDsec11 = "" + Chr(10) + "### Error Handling" + Chr(10) + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + Chr(10) + "Understand how to manage errors and handle exceptions in HTVM to make your programs more robust. HTVM provides simple ways to catch and handle errors, helping you write more stable and reliable code." + Chr(10) + Chr(10) + "### Error Handling in HTVM" + Chr(10) + "" + Chr(10) + "Error handling is an essential part of writing robust programs. In HTVM, you can handle errors using the " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + " keywords, similar to other modern programming languages. This allows you to handle exceptions effectively, ensuring that your program can gracefully recover or manage unexpected situations." + Chr(10) + "" + Chr(10) + "HTVM supports error handling, and even if certain target languages don't fully support " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ", HTVM ensures that the structure remains intact during conversion. For unsupported features, HTVM provides an easy workaround by using **programming blocks**." + Chr(10) + "" + Chr(10) + "### HTVM Error Handling Syntax" + Chr(10) + "" + Chr(10) + "| **HTVM Keyword**         | **Description**                                                                   | **Target Language Syntax**     |" + Chr(10) + "|--------------------------|-----------------------------------------------------------------------------------|--------------------------------|" + Chr(10) + "| " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + "                    | Used to define the block of code where errors may occur.                          | " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + "                          |" + Chr(10) + "| Error message function   | Used to throw an error message.                                                   | " + Chr(96) + "" + doc_keyWordErrorMsg + "(" + Chr(34) + "message" + Chr(34) + ")" + Chr(96) + "          |" + Chr(10) + "| " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + "                  | Used to catch and handle the error.                                               | " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + "                        |" + Chr(10) + "| " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + "                | Used to define code that runs after " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", regardless of whether an error occurs. | " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + "                      |" + Chr(10) + "" + Chr(10) + "HTVM's error handling syntax is simple and intuitive. You can use " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + " and " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + " to handle errors, and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + " to ensure that some code is always executed at the end of the try block. Here's a quick overview:" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet64 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "or" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet65 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "In the above example, the error message is customizable and should be a string. This allows you to define your own error messages in a way that fits your needs." + Chr(10) + "" + Chr(10) + "### Programming Blocks for Unsupported Features" + Chr(10) + "" + Chr(10) + "For languages that do not support traditional error handling structures (such as " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + "), HTVM provides **programming blocks**. These allow you to write directly in the target language’s syntax, enabling you to implement your own error handling solutions or other programming structures. For example, if you're converting your HTVM code to Golang or Lua (which do not support " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", or " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + "), you can use programming blocks to write your custom error handling code in the respective language." + Chr(10) + "" + Chr(10) + "A programming block is a way to insert code directly in the target language, bypassing HTVM's standard syntax when necessary. This gives you full control over how your program handles exceptions and other language-specific behaviors." + Chr(10) + "" + Chr(10) + "### Error Handling Support in Target Languages" + Chr(10) + "" + Chr(10) + "| Language     | " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + " | " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + " | " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + "    | Notes                                                                                            |" + Chr(10) + "|--------------|-------|---------|--------------|--------------------------------------------------------------------------------------------------|" + Chr(10) + "| C++          | ✅     | ✅       | ❌         | No support for " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ".                                                                        |" + Chr(10) + "| Python       | ✅     | ✅       | ✅         | Full support for " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ".                                                  |" + Chr(10) + "| JavaScript   | ✅     | ✅       | ✅         | Full support for " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ".                                                  |" + Chr(10) + "| Go           | ❌     | ❌       | ❌         | No " + Chr(96) + "try-catch-finally" + Chr(96) + " support. Use programming blocks to implement custom error handling.       |" + Chr(10) + "| Lua          | ❌     | ❌       | ❌         | No " + Chr(96) + "try-catch-finally" + Chr(96) + " support. Use programming blocks to implement custom error handling.       |" + Chr(10) + "| C#           | ✅     | ✅       | ✅         | Full support for " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ".                                                  |" + Chr(10) + "| Java         | ✅     | ✅       | ✅         | Full support for " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ".                                                  |" + Chr(10) + "| Kotlin       | ✅     | ✅       | ✅         | Full support for " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ".                                                  |" + Chr(10) + "| Ruby         | ✅     | ✅       | ✅         | Full support for " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ".                                                  |" + Chr(10) + "| Nim          | ✅     | ✅       | ✅         | Full support for " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ".                                                  |" + Chr(10) + "| AutoHotKey   | ✅     | ✅       | ✅         | Full support for " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ".                                                  |" + Chr(10) + "| Swift        | ✅     | ✅       | ❌         | No support for " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ".                                                                        |" + Chr(10) + "| Dart         | ✅     | ✅       | ✅         | Full support for " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ".                                                  |" + Chr(10) + "| TypeScript   | ✅     | ✅       | ✅         | Full support for " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ".                                                  |" + Chr(10) + "| Groovy       | ✅     | ✅       | ✅         | Full support for " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + ".                                                  |" + Chr(10) + "" + Chr(10) + "### Notes:" + Chr(10) + "" + Chr(10) + "- **Golang and Lua**: These languages don't support traditional " + Chr(96) + "try-catch-finally" + Chr(96) + " blocks. If you try to use HTVM’s error handling in these languages, you will see placeholder strings inserted, which will result in errors. You can instead write custom error handling inside programming blocks in their respective languages." + Chr(10) + "  " + Chr(10) + "- **C++ and Swift**: The " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + " block is not natively supported, but you can include it in your HTVM code, and HTVM will convert it to an if statement. You can still structure your code in a way that mimics " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + " behavior by ensuring that certain code kinda runs." + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp" + Chr(10) + "try {" + Chr(10) + "    // Your code that might throw an error" + Chr(10) + "    throw std::runtime_error(" + Chr(34) + "Something went wrong!" + Chr(34) + ");" + Chr(10) + "}" + Chr(10) + "catch (const std::exception& e) {" + Chr(10) + "    // Handle the error, e contains the error message" + Chr(10) + "    print(" + Chr(34) + "Caught error: " + Chr(34) + " + STR(e.what()));" + Chr(10) + "}" + Chr(10) + "if (" + Chr(34) + "finally dosent exist in c++" + Chr(34) + " == " + Chr(34) + "finally dosent exist in c++" + Chr(34) + ") {" + Chr(10) + "    // This simulates a finally block, but it's not guaranteed to behave like one in all cases" + Chr(10) + "    // HTVM may treat this like a finally block, but behavior can vary across targets" + Chr(10) + "    // Intended to run after try/catch, but not a true finally block" + Chr(10) + "    print(" + Chr(34) + "Finally block executed" + Chr(34) + ");" + Chr(10) + "}" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "swift" + Chr(10) + "do {" + Chr(10) + "    // Your code that might throw an error" + Chr(10) + "    try ErrorMsg(" + Chr(34) + "Something went wrong!" + Chr(34) + ")" + Chr(10) + "}" + Chr(10) + "catch let e as NSError {" + Chr(10) + "    // Handle the error, e contains the error message" + Chr(10) + "    print(" + Chr(34) + "Caught error: " + Chr(34) + " + e.localizedDescription)" + Chr(10) + "}" + Chr(10) + "if (" + Chr(34) + "finally dosent exist in swift" + Chr(34) + " == " + Chr(34) + "finally dosent exist in swift" + Chr(34) + ") {" + Chr(10) + "    // This simulates a finally block, but it's not guaranteed to behave like one in all cases" + Chr(10) + "    // HTVM may treat this like a finally block, but behavior can vary across targets" + Chr(10) + "    // Intended to run after try/catch, but not a true finally block" + Chr(10) + "    print(" + Chr(34) + "Finally block executed" + Chr(34) + ")" + Chr(10) + "}" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "#### Since " + Chr(96) + "Go" + Chr(96) + " and " + Chr(96) + "Lua" + Chr(96) + " don't support " + Chr(96) + "try-catch-finally" + Chr(96) + ", it will look like this:" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "go" + Chr(10) + "GO DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK {" + Chr(10) + "    // Your code that might throw an error" + Chr(10) + "    GO DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK" + Chr(10) + "}" + Chr(10) + "GO DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK {" + Chr(10) + "    // Handle the error, e contains the error message" + Chr(10) + "    print(" + Chr(34) + "Caught error: " + Chr(34) + " + STR(e))" + Chr(10) + "}" + Chr(10) + "GO DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK {" + Chr(10) + "    // Code that will always execute, regardless of an error" + Chr(10) + "    print(" + Chr(34) + "Finally block executed" + Chr(34) + ")" + Chr(10) + "}" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "lua" + Chr(10) + "LUA DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK" + Chr(10) + "    -- Your code that might throw an error" + Chr(10) + "    LUA DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK" + Chr(10) + "end" + Chr(10) + "LUA DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK" + Chr(10) + "    -- Handle the error, e contains the error message" + Chr(10) + "    print(" + Chr(34) + "Caught error: " + Chr(34) + " .. STR(e))" + Chr(10) + "end" + Chr(10) + "LUA DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK" + Chr(10) + "    -- Code that will always execute, regardless of an error" + Chr(10) + "    print(" + Chr(34) + "Finally block executed" + Chr(34) + ")" + Chr(10) + "end" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "That means you can't use them when converting to " + Chr(96) + "Go" + Chr(96) + " and " + Chr(96) + "Lua" + Chr(96) + ". " + Chr(10) + "" + Chr(10) + "### Catch Block Syntax" + Chr(10) + "" + Chr(10) + "The " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + " block syntax in HTVM is simple and flexible. You can write:" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet66 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "- **e**: This is the error variable, which stores the error message. You can use any variable name here, but " + Chr(96) + "e" + Chr(96) + " is the most common and convenient choice." + Chr(10) + "- You don't need parentheses around " + Chr(96) + "e" + Chr(96) + " or other variable names, though you can use them if you prefer." + Chr(10) + "" + Chr(10) + "### Important Notes:" + Chr(10) + "" + Chr(10) + "- **Error handling behavior across languages**: The behavior of " + Chr(96) + "" + doc_keyWordTry + "" + Chr(96) + ", " + Chr(96) + "" + doc_keyWordCatch + "" + Chr(96) + ", and " + Chr(96) + "" + doc_keyWordFinally + "" + Chr(96) + " blocks may not be exactly the same across all languages. Make sure to thoroughly test your code when converting between different target languages. While HTVM provides support for error handling in many languages, differences in implementation and behavior can arise." + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "";
    std::string outMDsec12 = "" + Chr(10) + "### Include" + Chr(10) + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + Chr(10) + "Discover how to include external files and resources in your HTVM project for enhanced functionality. The **include** feature in HTVM allows you to integrate additional code or libraries into your project seamlessly." + Chr(10) + Chr(10) + "### Including Files in HTVM" + Chr(10) + "" + Chr(10) + "In HTVM, the " + Chr(96) + "" + doc_keyWordInclude + "" + Chr(96) + " keyword allows you to include another HTVM file within your code. This works in a very simple way: just use the " + Chr(96) + "" + doc_keyWordInclude + "" + Chr(96) + " keyword followed by a string containing the file path. It's important to remember that this string must be static; you cannot use any operators or dynamic strings." + Chr(10) + "" + Chr(10) + "**Syntax**:" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet67 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "The included file will be appended to the top of your code. If there are other includes within the included file, those will be included as well, creating a chain of inclusions. Be careful of nesting too many includes, as it may lead to unexpected behavior." + Chr(10) + "" + Chr(10) + "In most cases, it's a good idea to specify the full file path if possible, though relative paths may work depending on where your files are located." + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "" + Chr(10) + "### The Main Label" + Chr(10) + "" + Chr(10) + "The " + Chr(96) + "main" + Chr(96) + " keyword in HTVM is a special label used to define the starting point of your program. It is not required to be inside a programming block and can be used freely to mark the beginning of the main code execution." + Chr(10) + "" + Chr(10) + "The " + Chr(96) + "main" + Chr(96) + " keyword serves as a label and does not require any special syntax. You simply place your main code inside the block after the " + Chr(96) + "main" + Chr(96) + " label. When including code from another file, however, make sure that the " + Chr(96) + "main" + Chr(96) + " label appears immediately after any inclusion from other languages." + Chr(10) + "" + Chr(10) + "**Rules**:" + Chr(10) + "" + Chr(10) + "- **Before " + Chr(96) + "main" + Chr(96) + "**: You can define functions and include code." + Chr(10) + "- **After " + Chr(96) + "main" + Chr(96) + "**: You **cannot** define functions—only the main body of your program should follow. While some target languages (like JavaScript) might technically allow nested functions or definitions after the main execution point begins, this is strongly discouraged and disallowed by HTVM's structure to maintain clarity and predictable behavior across conversions." + Chr(10) + "" + Chr(10) + "If you're including code from another language, make sure to remove any pre-existing " + Chr(96) + "main" + Chr(96) + " function from that file before including it. This ensures that the " + Chr(96) + "main" + Chr(96) + " label in HTVM is properly used to start your program's execution." + Chr(10) + "" + Chr(10) + "**Using HTVM without Function Definitions**: If you're using HTVM normally, without defining functions or including code from other languages or files, the " + Chr(96) + "main" + Chr(96) + " label becomes optional as the code execution implicitly starts from the top. But when including functions, HTVM files, or programming blocks with definitions, make sure to follow the structure outlined above (definitions before " + Chr(96) + "main" + Chr(96) + ", main execution logic after " + Chr(96) + "main" + Chr(96) + ") for proper execution." + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "" + Chr(10) + "### Using Programming Blocks" + Chr(10) + "" + Chr(10) + "HTVM supports including code from other programming languages through programming blocks. To include code from another language, open a programming block and write the import or include statement in the respective syntax for the target language. Then close the block to finish." + Chr(10) + "" + Chr(10) + "**Example (Python)**" + Chr(10) + "" + Chr(10) + "If you need to import a library in Python, you can write it like this inside a programming block:" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet68 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "In this case, " + Chr(96) + "math" + Chr(96) + " is a Python library that you can use within your HTVM code. If you want to use a function from the library, you would call it as " + Chr(96) + "math.function_name()" + Chr(96) + "." + Chr(10) + "" + Chr(10) + "**Example (JavaScript)**" + Chr(10) + "" + Chr(10) + "For JavaScript, it might look like this:" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet69 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**Example (C++)**" + Chr(10) + "" + Chr(10) + "For C++, the inclusion might look like this:" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet70 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "Each programming language has its own syntax for imports or includes, so be sure to use the correct syntax for the target language." + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "" + Chr(10) + "### Caching Functions" + Chr(10) + "" + Chr(10) + "HTVM allows you to cache functions and reuse them across different projects. This process involves writing your functions in HTVM, converting them to the target language, and then including them in your HTVM code using programming blocks." + Chr(10) + "" + Chr(10) + "#### **Directly Caching Functions Using File Conversion**" + Chr(10) + "" + Chr(10) + "One way to cache functions is by directly writing and saving them as separate files. When you convert these files, you can reuse them across your projects without manually importing specific libraries or using function names with prefixes." + Chr(10) + "" + Chr(10) + "Here’s how you can achieve this with Python:" + Chr(10) + "" + Chr(10) + "1.  **Write your functions in HTVM**." + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet71 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "2.  **Convert the functions to Python** and remove the " + Chr(96) + "main" + Chr(96) + " function (if applicable) from the converted Python file." + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "python" + Chr(10) + "def add(a, b):" + Chr(10) + "    return a + b" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "3.  **Save the Python code as a separate file** (e.g., " + Chr(96) + "functions.py" + Chr(96) + "). This file should not include any " + Chr(96) + "main" + Chr(96) + " function." + Chr(10) + "" + Chr(10) + "4.  **Directly import and use the functions without needing to prefix them with a library name** by following Python's normal import syntax. This means that once the " + Chr(96) + "functions.py" + Chr(96) + " file is in the same directory as your HTVM project, you can import the function directly." + Chr(10) + "" + Chr(10) + "**Example (No library prefix)**:" + Chr(10) + "" + Chr(10) + "5.  **If " + Chr(96) + "functions.py" + Chr(96) + " is in the same directory**" + Chr(10) + "" + Chr(10) + "This import allows you to directly use " + Chr(96) + "add" + Chr(96) + " in your HTVM code without having to prefix it with the filename or a library name (i.e., no need for " + Chr(96) + "functions.add()" + Chr(96) + ")." + Chr(10) + "" + Chr(10) + "Use the function as normal in your HTVM code using the following import:" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet72 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "By following this method, you can write functions in HTVM, convert them to Python (or any other language), and reuse them across different projects while keeping the syntax clean and free of unnecessary library names." + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "" + Chr(10) + "#### **Alternative: Inline Caching**" + Chr(10) + "" + Chr(10) + "Instead of saving the converted Python (or other language) code to a separate file and importing it, you can directly paste the raw function definitions from the converted output into a programming block within your main HTVM file." + Chr(10) + "" + Chr(10) + "**Example (Python)**:" + Chr(10) + "" + Chr(10) + "1.  Convert your HTVM functions (like " + Chr(96) + "add" + Chr(96) + ") to Python." + Chr(10) + "2.  Copy the resulting Python function definition(s)." + Chr(10) + "3.  Paste them directly into a Python programming block in your main HTVM file:" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + htvmSnippet73 + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**Trade-offs**:" + Chr(10) + "*   **Pro**: Keeps all code within a single HTVM file, potentially simplifying distribution or editing if you prefer not to manage separate files. No need to re-transpile the function source HTVM if you only modify the main HTVM file." + Chr(10) + "*   **Con**: Can make the main HTVM file very large and harder to navigate if you have many or complex functions. You lose the modularity of separate files." + Chr(10) + "" + Chr(10) + "Functions defined this way are directly available in the subsequent HTVM code (within the same target language context) without needing any " + Chr(96) + "import" + Chr(96) + " statements or library prefixes." + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "" + Chr(10) + "Or just add it as a built-in function if you use it often." + Chr(10) + "### Adding Built-In Functions" + Chr(10) + "" + Chr(10) + "**Description**: Add custom built-in functions to your language by following simple syntax rules." + Chr(10) + "" + Chr(10) + "1.  Open " + Chr(96) + "HTVM-instructions.txt" + Chr(96) + "." + Chr(10) + "2.  Copy the last function block and paste it at the bottom." + Chr(10) + "3.  Follow these rules:" + Chr(10) + "    *   **Language Specification**: Use " + Chr(96) + "lang: cpp" + Chr(96) + ", " + Chr(96) + "lang: py" + Chr(96) + ", " + Chr(96) + "lang: js" + Chr(96) + ", " + Chr(96) + "lang: go" + Chr(96) + ", " + Chr(96) + "lang: lua" + Chr(96) + ", " + Chr(96) + "lang: cs" + Chr(96) + ", " + Chr(96) + "lang: java" + Chr(96) + ", " + Chr(96) + "lang: kt" + Chr(96) + ", " + Chr(96) + "lang: rb" + Chr(96) + ", " + Chr(96) + "lang: nim" + Chr(96) + ", " + Chr(96) + "lang: ahk" + Chr(96) + ", " + Chr(96) + "lang: swift" + Chr(96) + ", " + Chr(96) + "lang: dart" + Chr(96) + ", " + Chr(96) + "lang: ts" + Chr(96) + ", or " + Chr(96) + "lang: groovy" + Chr(96) + " to define the language-specific implementation." + Chr(10) + "    *   **Function Name**: Use " + Chr(96) + "name: functionName" + Chr(96) + "." + Chr(10) + "    *   **Libraries**: List required libraries with a " + Chr(96) + "|" + Chr(96) + " delimiter. For example:" + Chr(10) + "        *   **C++**: " + Chr(96) + "libs: #include " + Chr(60) + "iostream" + Chr(62) + "|#include " + Chr(60) + "cstdlib" + Chr(62) + "" + Chr(96) + "" + Chr(10) + "        *   **JavaScript (not in a full .html file)**: " + Chr(96) + "libs: import { readFileSync } from 'fs';|import { EventEmitter } from 'events';" + Chr(96) + "" + Chr(10) + "        *   **JavaScript (in a full .html file)**: " + Chr(96) + "libs: " + Chr(60) + "script src=" + Chr(34) + "https://cdn.jsdelivr.net/npm/sweetalert2@11" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "" + Chr(96) + "" + Chr(10) + "        *   **JavaScript (in a full .html file for more than one)**: " + Chr(96) + "libs: " + Chr(60) + "script src=" + Chr(34) + "https://cdn.jsdelivr.net/npm/sweetalert2@11" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "|" + Chr(60) + "script src=" + Chr(34) + "myModule.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "" + Chr(96) + "" + Chr(10) + "        *   For other languages, just use the same format. For " + Chr(96) + "Go" + Chr(96) + ", use " + Chr(96) + "libs: )|" + Chr(34) + "theLibName" + Chr(34) + "" + Chr(96) + ". The reason for using " + Chr(96) + ")" + Chr(96) + " is that in HTVM, it doesn't know when the import " + Chr(96) + "()" + Chr(96) + " ends, so we add the " + Chr(96) + ")" + Chr(96) + " as a placeholder. It ensures that the import is correctly handled and will be sorted out at the end. Also, don't worry about including the same lib multiple times, since HTVM will remove duplicates." + Chr(10) + "    *   **Description**:" + Chr(10) + "        *   Format:" + Chr(10) + "            " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "            description: string~~~[One-line description of the function]~~~Here is how the function looks:~~~" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "~~~[Function signature]~~~" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "            " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "        *   Example:" + Chr(10) + "            " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "            description: string~~~Sort is a function to sort elements based on various criteria like numeric, random, alphabetical order, etc.~~~Here is how the function looks:~~~" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "~~~Sort(string input, [string options = " + Chr(34) + "" + Chr(34) + "])~~~" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "            " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "        Note: The ~~~ delimiters in the description section are placeholders that will be replaced with new lines in the final documentation." + Chr(10) + "" + Chr(10) + "**Here is how a built-in function in HTVM-instructions.txt looks like:**" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "func======================func==============" + Chr(10) + "lang: cpp" + Chr(10) + "name: Sleep" + Chr(10) + "libs: #include " + Chr(60) + "thread" + Chr(62) + "|#include " + Chr(60) + "chrono" + Chr(62) + "" + Chr(10) + "description: system~~~Sleep is a function that pauses execution for a specified number of milliseconds.~~~here is how the func looks like:~~~" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "~~~Sleep(int milliseconds)~~~" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "~~~" + Chr(10) + "// Function to sleep for a specified number of milliseconds" + Chr(10) + "void Sleep(int milliseconds) {" + Chr(10) + "    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));" + Chr(10) + "}" + Chr(10) + "funcEND======================funcEND==============" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "4.  **ChatGPT Prompt for Function Descriptions:**" + Chr(10) + "    To generate descriptions for functions, use the following ChatGPT prompt to ensure the response follows a specific format:" + Chr(10) + "" + Chr(10) + "    **ChatGPT Prompt:**" + Chr(10) + "    " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "    here is what you will do structly so i wil give you a func like something like this it can be in c++ py or js dosnet matter from what it is it what you must do is give me output in this format:" + Chr(10) + "" + Chr(10) + "    MAKRE SURE IT SATRST WHIT description: and all in one code block" + Chr(10) + "" + Chr(10) + "    description: string~~~StrTitleCase is a func balalbla bla bal~~~here is how the func looks like:~~~" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm~~~StrTitleCase(string, [optanalName], string, [optanal], string, [optanal], [optanal])~~~" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "~~~" + Chr(10) + "" + Chr(10) + "    it must be " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm not " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp or others IT MUST BE " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm" + Chr(10) + "" + Chr(10) + "    all of the ~~~ and all the same format DONT change it only chamge words" + Chr(10) + "" + Chr(10) + "    allways start like this description: category_name~~~" + Chr(10) + "" + Chr(10) + "    the param dosnet have to be the same name juts a simlpe name no _ pls" + Chr(10) + "" + Chr(10) + "    Use square brackets: When you mention the function or describe the parameters, put optional parameters in square brackets [ ]. This is the most common notation for optional parameters. For example:" + Chr(10) + "" + Chr(10) + "    functionName(param1, [param2], [param3])" + Chr(10) + "    This means that param2 and param3 are optional." + Chr(10) + "    Provide a description or note: You can also mention which parameters are optional in a description or a comment, such as:" + Chr(10) + "" + Chr(10) + "    " + Chr(34) + "The param2 and param3 parameters are optional." + Chr(34) + "" + Chr(10) + "    " + Chr(34) + "The optional parameters are param2 and param3." + Chr(34) + "" + Chr(10) + "    Default values in code: If the function includes default values for parameters, you can also point this out. For example:" + Chr(10) + "" + Chr(10) + "    functionName(param1, param2 = " + Chr(34) + "default" + Chr(34) + ", param3 = 10)" + Chr(10) + "    This means that param2 and param3 have default values and are optional." + Chr(10) + "" + Chr(10) + "    YOU MUST SPECIFY THE TYPE AS WELL like this" + Chr(10) + "" + Chr(10) + "    funcName(int asd, str, waeds, bool, waedsf, arr str, waesdf, bool [awsesrs = false], bool [awsesrs = true])" + Chr(10) + "" + Chr(10) + "    YOU MUST SPECIFY THE TYPE EVEN IF YOU DONT KNOW TRY TO GUESS HERE IS THE TYPE SYNTAX" + Chr(10) + "    str" + Chr(10) + "    int" + Chr(10) + "    bool" + Chr(10) + "    arr str" + Chr(10) + "    func" + Chr(10) + "    ... otherwize made them up" + Chr(10) + "" + Chr(10) + "    respond in a " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "txt all in one line" + Chr(10) + "" + Chr(10) + "    so the ~~~ = to a new line ok ~~~ is a new line and the first one where we typed string is the category and it must alwas be one word the bets word for thet category like string math gui io files bla..." + Chr(10) + "    THE description BUST BE ONLY IN ONE LINE" + Chr(10) + "    here is func and replay in one line:" + Chr(10) + "    ================================================" + Chr(10) + "" + Chr(10) + "    // Function to sleep for a specified number of milliseconds" + Chr(10) + "    void Sleep(int milliseconds) {" + Chr(10) + "        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));" + Chr(10) + "    }" + Chr(10) + "" + Chr(10) + "    " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "Open it in a text editor and make sure the response is in 1 line. Otherwise, if ChatGPT replies in more than one line, tell it:" + Chr(10) + "" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "txt" + Chr(10) + "I SAID REPLY IN ONE LINE" + Chr(10) + "" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "" + Chr(10) + "" + Chr(10) + "**Important**: Do not modify the first 162 lines of " + Chr(96) + "HTVM-instructions.txt" + Chr(96) + "." + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "" + Chr(10) + "### Important Notes on Library Usage and Conversions" + Chr(10) + "" + Chr(10) + "HTVM is flexible, but there are some important things to keep in mind when working with external libraries or converting code between languages." + Chr(10) + "" + Chr(10) + "#### **Converting Libraries Between Languages**:" + Chr(10) + "" + Chr(10) + "- You cannot use a Python library and convert it to JavaScript or any other languages. When including libraries, ensure that they are compatible with the target language. For example, if you want to use the " + Chr(96) + "NumPy" + Chr(96) + " library in Python, you cannot convert your code to JavaScript or C++ because the " + Chr(96) + "NumPy" + Chr(96) + " library won't work in those languages." + Chr(10) + "" + Chr(10) + "#### **Library-Specific Syntax**:" + Chr(10) + "" + Chr(10) + "- When including libraries in HTVM, you’ll need to follow the target language's syntax. For example, if you're using Python libraries, you'll have to call them in Python syntax, such as " + Chr(96) + "library_name.function_name()" + Chr(96) + ". This can be cumbersome but is necessary for cross-language compatibility." + Chr(10) + "" + Chr(10) + "#### **Using HTVM Syntax with Other Languages**:" + Chr(10) + "" + Chr(10) + "- You can use HTVM to emulate the syntax of another language, such as Lua, while still utilizing Python libraries like Pygame. However, this comes with some limitations—HTVM will allow you to write in a Lua-like style, but the built-in functions will remain HTVM functions, and not all features of the target language will be available." + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "" + Chr(10) + "### Final Considerations" + Chr(10) + "" + Chr(10) + "- After using the " + Chr(96) + "" + doc_keyWordInclude + "" + Chr(96) + " keyword, always ensure that the " + Chr(96) + "main" + Chr(96) + " label is placed underneath any includes or programming blocks containing definitions. **Do not** define functions after the " + Chr(96) + "main" + Chr(96) + " label in your HTVM code. While some target languages (like JavaScript) might technically allow nested functions after the main execution point, this is strongly discouraged and disallowed by HTVM's structure for clarity and predictable behavior." + Chr(10) + "" + Chr(10) + "- When including code from other languages that HTVM has converted, remove their " + Chr(96) + "main" + Chr(96) + " function to avoid conflicts. This is crucial for the proper execution of the HTVM program." + Chr(10) + "" + Chr(10) + "- If you frequently reuse the same set of functions across many projects (especially functions converted from HTVM or native language code), consider adding them as custom built-in functions by editing " + Chr(96) + "HTVM-instructions.txt" + Chr(96) + " (as described in the " + Chr(34) + "Adding Built-In Functions" + Chr(34) + " section) instead of repeatedly using " + Chr(96) + "" + doc_keyWordInclude + "" + Chr(96) + " or inline caching via programming blocks. This can centralize your common utilities." + Chr(10) + "" + Chr(10) + "---" + Chr(10) + "";
    std::string outMDsec13 = "" + Chr(10) + "### Commands" + Chr(10) + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + Chr(10) + "Commands in HTVM are a simplified way to perform actions, similar to functions, but with a more compact, direct, and concise syntax for better efficiency. Commands help streamline your code and reduce unnecessary complexity." + Chr(10) + Chr(10) + "### Commands in HTVM" + Chr(10) + Chr(10) + "**What is a Command?**  " + Chr(10) + "In HTVM, commands are simple, intuitive building blocks that you use to perform actions in your code. They are inspired by AutoHotKey commands, but in HTVM, they automatically convert into function calls, making the process seamless. These commands are designed to be straightforward and concise, so you don’t need to worry about the underlying complexity of function definitions. When you write a command, HTVM handles converting it into an appropriate function call behind the scenes, allowing you to focus on logic rather than syntax." + Chr(10) + Chr(10) + "Each command can accept one or more parameters, depending on its functionality, and follows a consistent format for easy readability and use." + Chr(10) + Chr(10) + "### Structure of a Command  " + Chr(10) + "A basic command looks like this:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "command, parameter1, parameter2, ..." + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "Commands support multiple parameters and follow a simple, comma-separated format. Behind the scenes, these commands are transformed into corresponding function calls, which execute the desired actions with minimal keystrokes." + Chr(10) + Chr(10) + "**⚠️ Disclaimer:**  " + Chr(10) + "This command syntax is structured and follows a defined format: a command name followed by a comma, then a space, then the next value, and so on — like " + Chr(96) + "text, text, text" + Chr(96) + ". It is different from how GUI definitions work in HTVM. GUI syntax is far more flexible and allows you to do insane stuff, while commands follow this more controlled, predictable pattern." + Chr(10) + Chr(10) + "#### Rules" + Chr(10) + Chr(10) + "We can have " + Chr(96) + "OUTVAR" + Chr(96) + " which means it will be " + Chr(96) + "OUTVAR = funcName(...)" + Chr(96) + Chr(10) + "So if we have " + Chr(96) + "commandName, OUTVAR, someParam" + Chr(96) + " that will equal " + Chr(96) + "OUTVAR = commandName(someParam)" + Chr(96) + " " + Chr(10) + Chr(10) + "If we have " + Chr(96) + "INVAR" + Chr(96) + " which means it will be " + Chr(96) + "funcName(INVAR ...)" + Chr(96) + Chr(10) + "So if we have " + Chr(96) + "commandName, INVAR, someParam" + Chr(96) + " that will equal " + Chr(96) + "commandName(INVAR, someParam)" + Chr(96) + " " + Chr(10) + Chr(10) + "If we have " + Chr(96) + "INOUTVAR" + Chr(96) + " which means it will be " + Chr(96) + "INOUTVAR = funcName(INOUTVAR ...)" + Chr(96) + Chr(10) + "So if we have " + Chr(96) + "commandName, INOUTVAR, someParam" + Chr(96) + " that will equal " + Chr(96) + "INOUTVAR = commandName(INOUTVAR, someParam)" + Chr(96) + " " + Chr(10) + Chr(10) + "If we have " + Chr(96) + "'" + Chr(96) + " which means it will be " + Chr(96) + "funcName(someParam ...)" + Chr(96) + Chr(10) + "So if we have " + Chr(96) + "commandName, someParam" + Chr(96) + " that will equal " + Chr(96) + "commandName(" + Chr(34) + "someParam" + Chr(34) + ")" + Chr(96) + " " + Chr(10) + "Basically, it means it will wrap it in double quotes (" + Chr(34) + Chr(34) + ")." + Chr(10) + Chr(10) + "If we have " + Chr(96) + "lineTranspile" + Chr(96) + " it means it will do a replace.  " + Chr(10) + "So if we have " + Chr(96) + "someText, lineTranspile, replacementText" + Chr(96) + ",  " + Chr(10) + "that means if you put on a single line alone: " + Chr(96) + "someText" + Chr(96) + ",  " + Chr(10) + "that will simply be replaced with " + Chr(96) + "replacementText" + Chr(96) + ".  " + Chr(10) + "And if we have ~~~ in the replacement, it will be replaced with actual new lines." + Chr(10) + Chr(10) + "Example:" + Chr(10) + "If we define " + Chr(96) + "greetUser, lineTranspile, print(" + Chr(34) + "Hello!" + Chr(34) + ")~~~print(" + Chr(34) + "Welcome to HTVM." + Chr(34) + ")" + Chr(96) + "  " + Chr(10) + "Then this:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "greetUser" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "Will become:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "print(" + Chr(34) + "Hello!" + Chr(34) + ")" + Chr(10) + "print(" + Chr(34) + "Welcome to HTVM." + Chr(34) + ")" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + Chr(62) + " ⚠️ **Important**: You **cannot** use the following characters inside commands: " + Chr(96) + "," + Chr(96) + " " + Chr(96) + "|" + Chr(96) + " " + Chr(96) + "%" + Chr(96) + " — these are reserved and will break the parsing." + Chr(10) + Chr(10) + Chr(62) + " If we have " + Chr(96) + "'" + Chr(96) + ", it means the param will be wrapped in double quotes. You **don’t actually type " + Chr(96) + "'" + Chr(96) + " in your code** — it’s just used here in the command definition to mark that param." + Chr(10) + Chr(10) + "### Available Commands  " + Chr(10) + "Here are all the available commands in this HTVM language:" + Chr(10) + Chr(10) + allCommandsDoc + Chr(10) + Chr(10) + "This was all of them." + Chr(10) + Chr(10) + "### Customizing Commands in HTVM  " + Chr(10) + "You can configure and customize the syntax of commands—along with the rest of your HTVM language—on the [HTVM Syntax Configurator website](#https://themaster1127.github.io/HTVM/web-ui/). That’s where you define how your custom HTVM language behaves, including how commands are recognized and structured." + Chr(10) + Chr(10) + "### Summary  " + Chr(10) + "This is a comprehensive guide to the commands in HTVM. With the goal of reducing keystrokes and inspired by AutoHotKey, HTVM provides an intuitive way to program with less effort.  " + Chr(10) + "To configure and customize your HTVM language, visit the [HTVM Syntax Configurator website](#https://themaster1127.github.io/HTVM/web-ui/). There you can adjust the commands, see how to define them, and other elements to create your own language and fit your coding needs." + Chr(10) + Chr(10) + "### HTVM Philosophy  " + Chr(10) + "HTVM is built on the idea of simplifying the coding experience through **minimal keystrokes**. It’s not about being lazy—it’s about being efficient. Traditional programming languages often burden the developer with excessive syntax, repetitive structures, and unnecessary complexity." + Chr(10) + Chr(10) + "HTVM flips that by giving you clean, readable code that does more with less. While some may argue that AI can write code for you, HTVM emphasizes control and creativity—two things that get lost when you offload everything to an AI. Besides, coding is fun. You should be able to enjoy it without the clutter.  " + Chr(10) + Chr(10) + "HTVM is trying to make you code with **fewer keystrokes**. Commands are a direct reflection of this philosophy—they let you express complex logic in just a few words, automatically converting into efficient function calls with minimal effort." + Chr(10) + Chr(10) + "---" + Chr(10) + "";
    std::string outMDsec14 = "";
    std::string outMDsec15 = "" + Chr(10) + "### All Syntax" + Chr(10) + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + Chr(10) + "#### Here is all of the syntax in this language:" + Chr(10) + Chr(10) + allSyntax + Chr(10) + Chr(10) + "---" + Chr(10) + "";
    std::string outMDup = "# HTVM Documentation" + Chr(10) + Chr(10) + outMDsec0 + Chr(10) + "---" + Chr(10) + Chr(10) + "## Introduction to HTVM" + Chr(10) + Chr(10) + "[Go back](#htvm-documentation) " + Chr(10) + Chr(10) + "HTVM is a revolutionary tool designed to replace traditional programming. With HTVM, you can create your own programming language directly [here](https://themaster1127.github.io/HTVM/)." + Chr(10) + Chr(10) + Chr(10) + "HTVM offers **extensive syntax customization**, giving you the freedom to tailor the language structure to your own preferences. Almost all of these customizations can be converted into 15 languages, providing flexibility while keeping things simple." + Chr(10) + Chr(10) + "## Customization Features" + Chr(10) + Chr(10) + "### Code Block Delimiters" + Chr(10) + Chr(10) + "You can **customize the block delimiters**, which define the start and end of code blocks. You can use:" + Chr(10) + Chr(10) + "- Curly braces " + Chr(96) + "{}" + Chr(96) + " (default)." + Chr(10) + "- **Other characters**, words, or even single letters, as long as the opening and closing delimiters are different from each other." + Chr(10) + Chr(10) + "### Indentation Styles" + Chr(10) + Chr(10) + "You have the ability to choose between multiple **indentation styles**:" + Chr(10) + Chr(10) + "- **Pythonic indentation style**: This removes the need for block delimiters like curly braces, relying on indentation to define code blocks." + Chr(10) + "- **Lua indentation style**: Uses the customizable " + Chr(96) + "end" + Chr(96) + " keyword to close code blocks." + Chr(10) + Chr(10) + "Both styles are fully customizable, and you can define your own keyword for closing blocks (such as " + Chr(96) + "end" + Chr(96) + ", or any other word)." + Chr(10) + Chr(10) + "### Toggleable Semicolons" + Chr(10) + Chr(10) + "Semicolons are **toggleable** in HTVM. By default, semicolons are not required to terminate statements, but you can enable the use of semicolons if you prefer them in your syntax. It's completely up to you whether or not to use them in your code." + Chr(10) + Chr(10) + "### Parentheses Customization" + Chr(10) + Chr(10) + "For **conditional statements** like " + Chr(96) + "if" + Chr(96) + ", " + Chr(96) + "else if" + Chr(96) + ", and " + Chr(96) + "while" + Chr(96) + " loops, you can choose to **use or omit parentheses** around conditions. This customization allows you to streamline your code and make it more intuitive according to your preferences." + Chr(10) + Chr(10) + "### Customizable Operators" + Chr(10) + Chr(10) + "HTVM allows you to **customize operators** to make your code more readable or suit your style. For example, instead of using " + Chr(96) + "==" + Chr(96) + " for equality, you can change it to a keyword like " + Chr(96) + "is" + Chr(96) + ". This means you can write more natural, human-readable code, such as:" + Chr(10) + Chr(10) + "- " + Chr(96) + "if var1 is 5" + Chr(96) + " (instead of " + Chr(96) + "if var1 == 5" + Chr(96) + ")." + Chr(10) + Chr(10) + "This flexibility extends across various operators, giving you full control over how your conditions and operations are structured." + Chr(10) + Chr(10) + Chr(10) + "## More Customization Options in HTVM" + Chr(10) + Chr(10) + "HTVM offers even **more customization** for your syntax and style. Here's a breakdown of additional features:" + Chr(10) + Chr(10) + "### Type Definition Styles" + Chr(10) + Chr(10) + "You can choose between **PostFix** or **Prefix** style for type definitions, similar to TypeScript:" + Chr(10) + Chr(10) + "- **PostFix**: Define the variable first, then the type after the colon (" + Chr(96) + "var1: int" + Chr(96) + ")." + Chr(10) + "- **Prefix**: Define the type first, then the variable (" + Chr(96) + "int var1" + Chr(96) + ")." + Chr(10) + Chr(10) + "You can toggle between these styles depending on which one fits your preferred syntax better." + Chr(10) + Chr(10) + "### Array Syntax Customization" + Chr(10) + Chr(10) + "HTVM lets you customize the array syntax by choosing between two options:" + Chr(10) + Chr(10) + "- **Regular braces** (" + Chr(96) + "[]" + Chr(96) + "): The default style for arrays." + Chr(10) + "- **Curly braces** (" + Chr(96) + "{}" + Chr(96) + "): If you prefer this style, you can toggle it on." + Chr(10) + Chr(10) + "It's fully flexible, so you can use whichever syntax feels right for your code." + Chr(10) + Chr(10) + "### Customizable Operators" + Chr(10) + Chr(10) + "HTVM extends **operator customizability** even further, allowing you to adjust a wide range of operators:" + Chr(10) + Chr(10) + "- **All operators**: You can customize **all operators**, including logical, comparison, and even **bitwise operators**." + Chr(10) + "- **Assignment operators**: You can customize assignment operators, such as " + Chr(96) + "=" + Chr(96) + ", to whatever you prefer (e.g., " + Chr(96) + "is" + Chr(96) + ", " + Chr(96) + "set" + Chr(96) + ", or any other single word)." + Chr(10) + Chr(10) + "However, remember that you are only allowed to use **one word** for customization—no spaces in operator names." + Chr(10) + Chr(10) + "### Customizable Comments" + Chr(10) + Chr(10) + "Comments are also fully customizable:" + Chr(10) + Chr(10) + "- **Single-line comments**: Change the single-line comment syntax to whatever you like (e.g., " + Chr(96) + "//" + Chr(96) + ", " + Chr(96) + "#" + Chr(96) + ", or any word)." + Chr(10) + "- **Multi-line comments**: Customize the syntax for multi-line comments, allowing for multiple words or characters if necessary." + Chr(10) + Chr(10) + "### Custom Escape Characters" + Chr(10) + Chr(10) + "Escape characters can now be **customized**:" + Chr(10) + Chr(10) + "- **Escape character**: You are no longer limited to using just the backslash (" + Chr(96) + Chr(92) + Chr(96) + "). You can choose any single character you want as your escape character—such as the backtick (" + Chr(96) + Chr(96) + " " + Chr(96) + " " + Chr(96) + Chr(96) + ") or something entirely different." + Chr(10) + Chr(10) + "### Loop Index Customization" + Chr(10) + Chr(10) + "You can **change the index for regular loops**. By default, HTVM uses **zero-based indexing** for loops. However, you can change this for certain languages:" + Chr(10) + Chr(10) + "- **AutoHotKey and Lua**: By default, both of these languages use **one-based indexing** for arrays and loops." + Chr(10) + "- **Other languages**: It's important to note that **changing loop indices may cause issues** with some languages, as not all languages support customizable loop indexes. **Use caution** when making changes to this setting, especially when working with languages like Python, JavaScript, or C++." + Chr(10) + Chr(10) + "HTVM allows for this change, but it’s recommended to keep the default zero-based indexing unless you’re specifically creating **meme languages** where the index may be something unconventional (like " + Chr(96) + "-69" + Chr(96) + " or " + Chr(96) + "420" + Chr(96) + ")." + Chr(10) + Chr(10) + "### Key Considerations for Indexing" + Chr(10) + Chr(10) + "- For **AutoHotKey** and **Lua**, the index starts at **one** by default." + Chr(10) + "- For **other languages**, **zero-based indexing** is the norm, so be mindful of this when converting to other languages." + Chr(10) + "  " + Chr(10) + "If you are creating custom languages or experimenting with unconventional indexing, keep these limitations in mind to avoid potential issues when converting to other languages." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + Chr(10) + "## Further Customization in HTVM" + Chr(10) + Chr(10) + "HTVM offers **even more customization options**, allowing you to tailor the language to your preferences, especially when it comes to types and arrays." + Chr(10) + Chr(10) + "### Custom Type Names" + Chr(10) + Chr(10) + "HTVM allows you to **customize type names** to anything you like. For example:" + Chr(10) + Chr(10) + "- **Basic Types**: Instead of using the traditional " + Chr(96) + "int" + Chr(96) + ", you can use " + Chr(96) + "number" + Chr(96) + ", " + Chr(96) + "i" + Chr(96) + ", or any other word you prefer. The same goes for types like " + Chr(96) + "double" + Chr(96) + ", " + Chr(96) + "char" + Chr(96) + ", " + Chr(96) + "boolean" + Chr(96) + ", " + Chr(96) + "float" + Chr(96) + ", and more." + Chr(10) + "- **Integer Sizes**: You can change types like " + Chr(96) + "int16" + Chr(96) + " to " + Chr(96) + "i16" + Chr(96) + " or any naming convention you prefer." + Chr(10) + "  " + Chr(10) + "**Important:** While you can use **multiple words** for type names, be cautious about potential conflicts in the parser. For instance, using common words that might be parsed as something else could lead to issues. Always ensure that the type names are unique and won't interfere with other syntax elements." + Chr(10) + Chr(10) + "The available types you can customize include:" + Chr(10) + Chr(10) + "- **Void**: You can rename " + Chr(96) + "void" + Chr(96) + " to whatever you want." + Chr(10) + "- **Integers**: " + Chr(96) + "int" + Chr(96) + ", " + Chr(96) + "int8" + Chr(96) + ", " + Chr(96) + "int16" + Chr(96) + ", " + Chr(96) + "int32" + Chr(96) + ", " + Chr(96) + "int64" + Chr(96) + ", etc." + Chr(10) + "- **Unsigned Integers**: " + Chr(96) + "uint8" + Chr(96) + ", " + Chr(96) + "uint16" + Chr(96) + ", " + Chr(96) + "uint32" + Chr(96) + ", " + Chr(96) + "uint64" + Chr(96) + " (Note: be cautious when converting unsigned integers to Java, as Java doesn’t support them)." + Chr(10) + "- **Floating Point**: " + Chr(96) + "double" + Chr(96) + ", " + Chr(96) + "float" + Chr(96) + "." + Chr(10) + "- **Character**: " + Chr(96) + "char" + Chr(96) + "." + Chr(10) + "- **String**: " + Chr(96) + "string" + Chr(96) + "." + Chr(10) + "- **Boolean**: " + Chr(96) + "boolean" + Chr(96) + "." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### Array Types Customization" + Chr(10) + Chr(10) + "In HTVM, you can customize the **array types** as well:" + Chr(10) + Chr(10) + "- **Four main array types**:" + Chr(10) + "  - " + Chr(96) + "arr str" + Chr(96) + ": For arrays of strings." + Chr(10) + "  - " + Chr(96) + "arr int" + Chr(96) + ": For arrays of integers." + Chr(10) + "  - " + Chr(96) + "arr float" + Chr(96) + ": For arrays of floating-point numbers." + Chr(10) + "  - " + Chr(96) + "arr bool" + Chr(96) + ": For arrays of booleans." + Chr(10) + "  " + Chr(10) + "- **Dynamic Arrays**: For dynamic-type languages, you can use the generic " + Chr(96) + "array" + Chr(96) + " keyword, but it defaults to a string array when converted to static type languages. This provides a flexible way to define arrays in your code." + Chr(10) + "  " + Chr(10) + "**Note on Static vs. Dynamic Types**: In **static-type languages**, arrays are strictly defined, so if you use the " + Chr(96) + "array" + Chr(96) + " keyword, it will default to a **string array**. For **dynamic languages**, the array type is more flexible." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### Array Methods Customization" + Chr(10) + Chr(10) + "HTVM allows you to customize array methods with ease. These methods work by appending a dot (" + Chr(96) + "." + Chr(96) + ") after the array, followed by the method name:" + Chr(10) + Chr(10) + "- **append**: Adds an element to the end of the array." + Chr(10) + "- **pop**: Removes the last element from the array." + Chr(10) + "- **size**: Retrieves the size (length) of the array." + Chr(10) + "- **insert**: Inserts an element at a specific index (not by value)." + Chr(10) + "- **remove**: Removes an element at a specific index (not by value)." + Chr(10) + "- **indexOf**: Finds the index of a value in the array." + Chr(10) + Chr(10) + "These methods can be customized with different names or functionality if needed, making it easier to manipulate arrays according to your needs." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### Important Considerations" + Chr(10) + Chr(10) + "- **Java and Unsigned Integers**: Be careful when converting unsigned integers (" + Chr(96) + "uint8" + Chr(96) + ", " + Chr(96) + "uint16" + Chr(96) + ", etc.) to **Java**, as Java does not support unsigned integers. HTVM will **NOT** warn you when attempting this conversion." + Chr(10) + "- **Array Methods**: Ensure that you define methods like " + Chr(96) + "insert" + Chr(96) + " and " + Chr(96) + "remove" + Chr(96) + " clearly to avoid confusion with other types of array manipulations. Using the dot (" + Chr(96) + "." + Chr(96) + ") ensures consistency and clarity in how methods are applied to arrays." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "## Extensive Customization in HTVM" + Chr(10) + Chr(10) + "HTVM offers **wide-ranging customization options** to ensure the language suits your preferences, especially when it comes to keywords and functionality. You can customize several aspects of the language, ranging from basic variable declarations to control structures and even language-specific keywords." + Chr(10) + Chr(10) + "### Customizing Keywords" + Chr(10) + Chr(10) + "HTVM allows you to customize many fundamental keywords that are used across different programming languages:" + Chr(10) + Chr(10) + "- **Variable Declarations**: Customize " + Chr(96) + "var" + Chr(96) + ", " + Chr(96) + "let" + Chr(96) + ", and " + Chr(96) + "const" + Chr(96) + " keywords. These are primarily used in **JavaScript** and **TypeScript**. " + Chr(10) + "  - The " + Chr(96) + "const" + Chr(96) + " keyword is supported in most languages, but in languages that don't have constants (e.g., **Python**, **AutoHotKey**, **Lua** and some more), it will be ignored, and the variable will be created as usual." + Chr(10) + "  " + Chr(10) + "- **Boolean Keywords**: Change the " + Chr(96) + "true" + Chr(96) + " and " + Chr(96) + "false" + Chr(96) + " keywords to something else like " + Chr(96) + "yeah" + Chr(96) + " and " + Chr(96) + "nah" + Chr(96) + ". This customization provides flexibility in how logical values are represented." + Chr(10) + "  " + Chr(10) + "- **Null Keyword**: You can also customize the " + Chr(96) + "null" + Chr(96) + " keyword, though be cautious—some languages do not support " + Chr(96) + "null" + Chr(96) + " in the same way (e.g., **Python**, **C++**, **AutoHotKey** and some more). For languages that don't support " + Chr(96) + "null" + Chr(96) + ", the value will simply be ignored or treated as an empty value." + Chr(10) + "  " + Chr(10) + "- **End Keyword**: You can change the " + Chr(96) + "end" + Chr(96) + " keyword to something else. This is typically used for denoting the end of code blocks in various languages and is customizable in HTVM." + Chr(10) + Chr(10) + "- **Global Keyword**: " + Chr(10) + "  - The " + Chr(96) + "global" + Chr(96) + " keyword works only in **Python** and **AutoHotKey**. It allows passing a global variable into a function and modifying it. In other languages, the " + Chr(96) + "global" + Chr(96) + " keyword will be ignored, but the variable will still be created." + Chr(10) + "  - You can also customize the " + Chr(96) + "global" + Chr(96) + " keyword to something else, keeping the functionality intact within supported languages." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### Main Label and Main Function Customization" + Chr(10) + Chr(10) + "HTVM allows you to **customize the main function label**. The main label refers to the starting point of your program, especially for languages like **C++** and many more but in **JavaScript** and **TypeScript** it's a bit different:" + Chr(10) + Chr(10) + "- **Main Label**: " + Chr(10) + "  - This is a customizable label where your main function is typically located. You can define a single word or even multiple words as the main label. The parser will ensure that the code below the label is treated as the main function's content. " + Chr(10) + "  - The main label is optional, and it’s simply a label—there’s no need to wrap the code in a block unless the language requires it (e.g., **Python** doesn’t need a " + Chr(96) + "main" + Chr(96) + " function, so the code will be placed directly beneath it)." + Chr(10) + "  " + Chr(10) + "- **Main Function**:" + Chr(10) + "  - In **JavaScript** and **TypeScript**, you can toggle between an **async main function** and a regular one." + Chr(10) + "  - The language will default to creating asynchronous functions for all function definitions, but you can customize this behavior with the **async** keyword (which is also customizable to other terms if you prefer). Also, if you don’t use the main label keyword, the HTVM parser will assume that you haven't created any functions, and all the code will be placed in the main function if the target language has a main function." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### Function Customization" + Chr(10) + Chr(10) + "HTVM allows you to **customize various function-related keywords** to suit your needs:" + Chr(10) + Chr(10) + "- **Async Functions**: " + Chr(10) + "  - By default, all functions in HTVM are asynchronous. You can toggle this behavior or use the **asynchronous** keyword, which is customizable." + Chr(10) + "  - The **await** keyword can also be modified to something else (e.g., " + Chr(96) + "wait" + Chr(96) + ") to fit your naming preferences." + Chr(10) + "  " + Chr(10) + "- **Loop Customization**: " + Chr(10) + "  - The loop syntax can be customized with terms like " + Chr(96) + "A_Index" + Chr(96) + " and " + Chr(96) + "A_LoopField" + Chr(96) + " to resemble **AutoHotKey**-style loops. These keywords provide a cleaner, more intuitive loop structure for those familiar with AutoHotKey." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### Important Considerations" + Chr(10) + Chr(10) + "- **Customizing Keywords**: When you customize keywords (e.g., " + Chr(96) + "const" + Chr(96) + ", " + Chr(96) + "true" + Chr(96) + ", " + Chr(96) + "false" + Chr(96) + ", " + Chr(96) + "null" + Chr(96) + "), ensure that they don’t conflict with existing language constructs. The parser will handle many of these customizations, but be aware of limitations in certain languages." + Chr(10) + "  " + Chr(10) + "- **Global Variables**: The " + Chr(96) + "global" + Chr(96) + " keyword is supported in **Python** and **AutoHotKey**, but it will be ignored in other languages like **JavaScript** or **C++**. Ensure you understand how this will behave across different languages." + Chr(10) + Chr(10) + "- **Async Functions in JavaScript/TypeScript**: This is especially useful for **JavaScript** and **TypeScript** but can be customized to suit your project’s needs." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "HTVM provides a **high level of flexibility** for customizing how the language operates, allowing you to adapt it to the specific needs of your project. Whether you're working with variable declarations, loop structures, or customizing language-specific keywords, HTVM makes it easier to code in a way that feels natural to you." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "## Advanced Customizations in HTVM" + Chr(10) + Chr(10) + "HTVM offers **advanced customizations** that allow you to control everything from ternary operators to error handling and even modularity with " + Chr(96) + "include" + Chr(96) + ". This flexibility makes it possible to tailor the language to your coding style and needs." + Chr(10) + Chr(10) + "### Ternary Operator Customization" + Chr(10) + Chr(10) + "HTVM lets you customize the **ternary operator**:" + Chr(10) + Chr(10) + "- By default, HTVM uses the regular **C-style ternary operator** (" + Chr(96) + "condition ? true : false" + Chr(96) + "). This works in most languages, but certain languages (like **Go**) do not support this syntax." + Chr(10) + "- For languages that use a different syntax for ternary operators, HTVM will handle the conversion automatically, converting it to the appropriate format." + Chr(10) + "  - For example, **Python** uses the " + Chr(96) + "condition if true else false" + Chr(96) + " syntax." + Chr(10) + "  - HTVM will ensure that the ternary operator is properly converted, but if the target language does not support ternary operators, HTVM will generate a message and prevent execution in languages like **Go** where it won’t run. This ensures that you avoid runtime errors from unsupported syntax." + Chr(10) + Chr(10) + "### Error Handling Customization" + Chr(10) + Chr(10) + "HTVM allows you to **customize error handling** as well:" + Chr(10) + Chr(10) + "- The " + Chr(96) + "try" + Chr(96) + ", " + Chr(96) + "catch" + Chr(96) + ", " + Chr(96) + "finally" + Chr(96) + ", and " + Chr(96) + "throw" + Chr(96) + " keywords are customizable, enabling you to tailor them to your preference." + Chr(10) + "- When using **throw**, you can customize the function name for the error message. This is how it works:" + Chr(10) + "  - Type " + Chr(96) + "throw" + Chr(96) + ", followed by the function name (which is customizable), open parentheses, and inside the parentheses, you can pass a string that represents the error message." + Chr(10) + "  - Example:" + Chr(10) + "    " + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "    " + htvmSnippet11 + Chr(10) + "    " + Chr(96) + Chr(96) + Chr(96) + Chr(10) + "- **Conversion to Other Languages**:" + Chr(10) + "  - HTVM converts error handling to most languages, but **Lua** and **Go** are exceptions. In those languages, the error handling structure is not supported, and HTVM will generate a string that alerts you about the lack of support." + Chr(10) + "  - HTVM does not provide error handling within itself. Instead, it relies on the target language to handle errors since HTVM assumes your code is flawless, and any issues should be identified by the language you're transpiling to." + Chr(10) + Chr(10) + "### Include Keyword Customization" + Chr(10) + Chr(10) + "HTVM also supports **modularity** through the " + Chr(96) + "include" + Chr(96) + " keyword:" + Chr(10) + Chr(10) + "- The " + Chr(96) + "include" + Chr(96) + " keyword allows you to include other HTVM files at the top of your code." + Chr(10) + "- This is useful for organizing your code across multiple files or for reusing common functionality across different projects." + Chr(10) + "  - Example:" + Chr(10) + "    " + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + "    " + htvmSnippet10 + Chr(10) + "    " + Chr(96) + Chr(96) + Chr(96) + Chr(10) + "- The " + Chr(96) + "include" + Chr(96) + " keyword is fully customizable, so you can change it to something else if preferred." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### Key Takeaways:" + Chr(10) + Chr(10) + "- **Ternary Operator**: Customizable to fit different syntaxes across languages, with automatic conversion. However, unsupported in **Go** and it will hardcode a message instead of running." + Chr(10) + "  " + Chr(10) + "- **Error Handling**: Customizable for the " + Chr(96) + "try" + Chr(96) + ", " + Chr(96) + "catch" + Chr(96) + ", " + Chr(96) + "finally" + Chr(96) + ", and " + Chr(96) + "throw" + Chr(96) + " keywords, and the function name for error messages can also be customized. HTVM does not handle errors itself but relies on the target language’s error handling. However, unsupported languages like **Go** and **Lua** will hardcode a message instead of running." + Chr(10) + Chr(10) + "- **Include**: Supports modularity by including external HTVM files, and the keyword itself is customizable." + Chr(10) + Chr(10) + "These advanced customizations further enhance HTVM's flexibility, allowing you to adjust error handling, ternary operators, and file management to fit your needs. With these tools, HTVM can be tailored to suit your specific coding style and make your development process more efficient." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "## Programming Blocks in HTVM" + Chr(10) + Chr(10) + "HTVM introduces **programming blocks** that allow you to **mix languages** seamlessly in your code. This feature is designed to handle cases where HTVM itself can't achieve something directly or when you'd prefer to rely on another language for specific tasks." + Chr(10) + Chr(10) + "### How Programming Blocks Work" + Chr(10) + Chr(10) + "1. **Opening a Programming Block**: You can open a programming block for a specific target language with the following syntax:" + Chr(10) + "    - One line to open the programming block." + Chr(10) + "    - Inside the block, you can write in the target language." + Chr(10) + "    - You close the block on a new line after your code." + Chr(10) + Chr(10) + "Example:" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet9 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "2. **Incorporating Blocks into HTVM Code**:" + Chr(10) + "    - When you write in HTVM, you can seamlessly insert target-language code using programming blocks." + Chr(10) + "    - For example, if you're converting to **JavaScript**, you can open a **JavaScript programming block**, and the code inside will be converted directly to JavaScript and placed in the converted code without alteration." + Chr(10) + "    - If the HTVM code contains loops or other structures, the programming block code stays intact in the appropriate place during conversion." + Chr(10) + Chr(10) + "3. **Multiple Programming Blocks**: You can use **multiple programming blocks** for different target languages, but they will be context-sensitive:" + Chr(10) + "    - **For JavaScript**: The **Python programming block** will be ignored during conversion." + Chr(10) + "    - **For Python**: The **JavaScript programming block** will be ignored." + Chr(10) + "    - In other words, only the relevant programming block for the target language will be included in the final code." + Chr(10) + Chr(10) + "Example:" + Chr(10) + "- **JavaScript block** in HTVM:" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet8 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + "- **Python block** in HTVM:" + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet7 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + "When converting to **JavaScript**, the Python block will disappear, and only the JavaScript block will be included." + Chr(10) + Chr(10) + "4. **Reverse Programming Blocks**:" + Chr(10) + "    - You can also open an **HTVM programming block** within other target language code (e.g., C++). The block will then be converted into HTVM-compatible code." + Chr(10) + "    - For example, if you're writing in C++ and need to use HTVM-specific functionality, you can insert an HTVM block, and it will be transpiled into C++ when you convert the code." + Chr(10) + "    - The process works by specifying the **target file** (e.g., " + Chr(96) + "main.cpp" + Chr(96) + "), and the HTVM block inside it will be converted based on the file's extension." + Chr(10) + Chr(10) + "5. **Universal Programming Block**:" + Chr(10) + "    - If two languages share the same syntax for a particular construct, HTVM allows you to use a **universal programming block**. This block can handle situations where HTVM cannot achieve the desired behavior but the syntax matches in multiple languages." + Chr(10) + "    - This is useful when the target languages have compatible syntax for specific code constructs but HTVM doesn't support them directly." + Chr(10) + Chr(10) + "6. **Conversion and Functionality**:" + Chr(10) + "    - During conversion, HTVM ensures that only the relevant programming block is preserved based on the target language. Unused blocks are omitted." + Chr(10) + "    - When converting code, HTVM will automatically include any necessary built-in functions or libraries for the target language, displaying them in the console." + Chr(10) + Chr(10) + Chr(10) + "### Key Advantages of Programming Blocks:" + Chr(10) + Chr(10) + "- **Flexibility**: Allows mixing HTVM with other languages for complex or specialized tasks." + Chr(10) + "- **Modularity**: Enables using language-specific libraries or features when HTVM cannot do the job." + Chr(10) + "- **Customizability**: Supports a wide range of languages, with options to adjust and adapt as needed." + Chr(10) + "- **Seamless Conversion**: Code stays in place, and HTVM ensures proper language-specific syntax is followed." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### Key Takeaways:" + Chr(10) + "- **Programming blocks** allow writing code in another language directly within HTVM, which will be preserved during conversion to that language." + Chr(10) + "- Multiple programming blocks can be used, but only the relevant block will be included based on the target language." + Chr(10) + "- **Reverse programming blocks** allow you to insert HTVM code into other target language code." + Chr(10) + "- The **universal programming block** enables handling languages with similar syntax for specific constructs." + Chr(10) + Chr(10) + Chr(10) + "#### **And More...**  " + Chr(10) + "- Go to [HTVM's website](https://themaster1127.github.io/HTVM) to explore all the syntax customizability and create your own language." + Chr(10) + Chr(10) + "### **The Power of HTVM – Beyond Anything Else**  " + Chr(10) + "This isn’t just some hobby project. **HTVM Version 2 took many months just for the parser.** And that was with prior experience from HTVM Version 1 and all the work put into previous languages like HT++, HTH, and HTpy. Every single language had to be carefully mapped out—loops, if-statements, try/catch blocks, functions, variables, types—**every detail had to be considered, tested, and tweaked.**  " + Chr(10) + Chr(10) + "And here’s the thing: **HTVM doesn’t just output to one language at a time—it can compile to multiple languages simultaneously.** That means you can write a single HTVM file and have it generate both JavaScript and Python code at the same time. That alone is something **almost no other tool in the world can do.**  " + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **Programming Blocks – Total Control Over Your Code**  " + Chr(10) + "And then we have **Programming Blocks.** These allow you to **write native code for the target language directly inside HTVM files**. So if you’re converting to JavaScript and need something that HTVM doesn’t handle natively, you can just open a **JavaScript Programming Block**, write JavaScript inside it, and it will only be included when compiling to JavaScript.  " + Chr(10) + Chr(10) + "But it gets even crazier—**you can have multiple programming blocks for different languages in the same file.** That means you can mix HTVM, JavaScript, Python, and C++ **all in one place** and still have everything work correctly.  " + Chr(10) + Chr(10) + "And if that wasn’t enough, there are **Reverse Programming Blocks**—which allow for even more insane levels of customization. Even if nobody uses them, **HTVM is so complete that the feature is still there.**  " + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "### **The Future of Programming**  " + Chr(10) + "HTVM **isn’t just a transpiler—it’s the future of programming.**  " + Chr(10) + Chr(10) + "This is a system that allows **anyone** to create their own syntax, define how they want their language to behave, and then generate fully functional code in fifteen different programming languages. No more being stuck with a single syntax or workflow—**HTVM lets you build programming your way.**  " + Chr(10) + Chr(10) + "Think about it. If you had to manually convert HTVM to fifteen different languages, it would take months just for a single feature. But **HTVM automates that entire process**—**once your syntax is defined, your language works across all targets instantly.**  " + Chr(10) + Chr(10) + "### **HTVM – The Future of Programming**  " + Chr(10) + "This level of customization **doesn’t exist anywhere else.** No other system gives you this much control over how your language looks and feels. You’re not just writing code—you’re **designing your own programming experience.**  " + Chr(10) + Chr(10) + "HTVM isn’t just powerful—it’s **insane.** This is how programming should be." + Chr(10) + Chr(10) + "**HTVM doesn’t force you into a fixed way of coding—it lets you create your own language and then outputs it into real programming languages.**  " + Chr(10) + Chr(10) + "HTVM **isn’t just another programming tool. It’s a revolution.**" + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "## OSP (Ordinal Struct Programming)" + Chr(10) + Chr(10) + "[Go back](#htvm-documentation)" + Chr(10) + Chr(10) + "OSP (Ordinal Struct Programming) is HTVM's built-in approach for organizing data and related procedures using hierarchical namespaces and explicit path-based access. It focuses on **ordinal** positioning – meaning the unique location of structures within the defined hierarchy (" + Chr(96) + "alliance" + Chr(96) + ", " + Chr(96) + "crew" + Chr(96) + "). This feature offers an alternative for structuring code, particularly for those who prefer direct data manipulation and clear, absolute referencing over features like inheritance or encapsulation found in traditional OOP." + Chr(10) + Chr(10) + "### What is a " + Chr(96) + "struct" + Chr(96) + " in HTVM OSP?" + Chr(10) + Chr(10) + "At its core, a " + Chr(96) + "struct" + Chr(96) + " in HTVM OSP is similar to structs in languages like C: it's a way to **group related data fields together under a single name**." + Chr(10) + Chr(10) + "-   **Definition:** You define a struct using the " + Chr(96) + "struct" + Chr(96) + " keyword." + Chr(10) + "-   **Properties:** Inside a struct, you define its data fields using the " + Chr(96) + "prop" + Chr(96) + " keyword. Each " + Chr(96) + "prop" + Chr(96) + " holds a piece of data (like an integer, string, boolean, or even an array)." + Chr(10) + "-   **Access:** Crucially, you *always* access struct properties using their **full, absolute path** starting from the top level (or the struct name if defined standalone). For example: " + Chr(96) + "MyAlliance.MyCrew.MyStruct.myProp" + Chr(96) + "." + Chr(10) + "-   **Global Nature:** Structs defined in OSP are globally accessible from any point in the code below their definition, using their full path." + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet4 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "### Optional Hierarchy: " + Chr(96) + "alliance" + Chr(96) + " and " + Chr(96) + "crew" + Chr(96) + Chr(10) + Chr(10) + "While you can define simple " + Chr(96) + "struct" + Chr(96) + "s directly, OSP provides optional hierarchical keywords (" + Chr(96) + "alliance" + Chr(96) + " and " + Chr(96) + "crew" + Chr(96) + ") for better organization, especially in larger projects:" + Chr(10) + Chr(10) + "-   **" + Chr(96) + "alliance" + Chr(96) + "**: The top-level organizational container." + Chr(10) + "-   **" + Chr(96) + "crew" + Chr(96) + "**: A sub-level container within an " + Chr(96) + "alliance" + Chr(96) + " (or potentially nested within other crews, though nesting isn't shown in examples)." + Chr(10) + Chr(10) + "**Why use hierarchy?**" + Chr(10) + Chr(10) + "-   **Organization:** Group related structs and procedures together logically (e.g., all UI elements in a " + Chr(96) + "GUI" + Chr(96) + " crew, all vehicle data in a " + Chr(96) + "Vehicles" + Chr(96) + " crew)." + Chr(10) + "-   **Avoiding Name Collisions:** If you had two different concepts both needing a " + Chr(96) + "struct" + Chr(96) + " named " + Chr(96) + "Settings" + Chr(96) + ", you could place them in different crews (e.g., " + Chr(96) + "Audio.Settings" + Chr(96) + " and " + Chr(96) + "Video.Settings" + Chr(96) + ") allowing them to coexist without conflict. Using " + Chr(96) + "alliance" + Chr(96) + " and " + Chr(96) + "crew" + Chr(96) + " acts like creating namespaces." + Chr(10) + Chr(10) + "Most of the time, for simpler data organization, you might just need standalone " + Chr(96) + "struct" + Chr(96) + "s. Use " + Chr(96) + "alliance" + Chr(96) + " and " + Chr(96) + "crew" + Chr(96) + " when you need the extra structure to avoid naming hurdles and keep related components neatly grouped." + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet5 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "### Procedures (" + Chr(96) + "proc" + Chr(96) + ")" + Chr(10) + Chr(10) + "Procedures are functions defined within the OSP hierarchy (" + Chr(96) + "alliance" + Chr(96) + " or " + Chr(96) + "crew" + Chr(96) + ") using the " + Chr(96) + "proc" + Chr(96) + " keyword. They are intended to perform actions related to the structs within their hierarchy." + Chr(10) + Chr(10) + "-   **Association:** Defining a " + Chr(96) + "proc" + Chr(96) + " inside an " + Chr(96) + "alliance" + Chr(96) + " or " + Chr(96) + "crew" + Chr(96) + " links it semantically to that part of the hierarchy." + Chr(10) + "-   **Global Access:** Like structs, " + Chr(96) + "proc" + Chr(96) + "s are globally accessible via their full path (e.g., " + Chr(96) + "MyAlliance.MyCrew.myProc" + Chr(96) + ")." + Chr(10) + "-   **Context (" + Chr(96) + "this" + Chr(96) + " Keyword):** Procedures can optionally accept a special parameter named " + Chr(96) + "this" + Chr(96) + " to understand *which* struct (identified by its path string) initiated the call." + Chr(10) + Chr(10) + "### The " + Chr(96) + "this" + Chr(96) + " Keyword (Procedure Context)" + Chr(10) + Chr(10) + "The " + Chr(96) + "this" + Chr(96) + " keyword in OSP (Ordinal) is **different** from " + Chr(96) + "this" + Chr(96) + " in traditional OOP." + Chr(10) + Chr(10) + "-   **Purpose:** It serves as an **optional input parameter for " + Chr(96) + "proc" + Chr(96) + "s**. When a " + Chr(96) + "proc" + Chr(96) + " is called with a struct's path string, " + Chr(96) + "this" + Chr(96) + " holds that **literal string value** inside the " + Chr(96) + "proc" + Chr(96) + "." + Chr(10) + "-   **Usage:** It allows a " + Chr(96) + "proc" + Chr(96) + " to perform different actions based on *which* struct path was passed to it. This is typically checked using simple string comparison (" + Chr(96) + "if (this == " + Chr(34) + "MyAlliance.MyCrew.MyStruct" + Chr(34) + ")" + Chr(96) + ")." + Chr(10) + "-   **Mechanism:** You must explicitly pass the **full path of the struct as a string** when calling the " + Chr(96) + "proc" + Chr(96) + " if you intend for that " + Chr(96) + "proc" + Chr(96) + " to use the " + Chr(96) + "this" + Chr(96) + " context." + Chr(10) + "-   **Limitation:** This string-based approach is explicit but requires careful maintenance. If you rename a " + Chr(96) + "struct" + Chr(96) + " or change the hierarchy, you **must** update all the corresponding string literals used in " + Chr(96) + "proc" + Chr(96) + " calls and within the " + Chr(96) + "proc" + Chr(96) + "'s " + Chr(96) + "if/else if" + Chr(96) + " checks. It doesn't automatically track the struct itself." + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet6 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "### Key Rules Recap" + Chr(10) + Chr(10) + "1.  **Full Path Access:** Always use the full, absolute path to access " + Chr(96) + "struct" + Chr(96) + " properties (e.g., " + Chr(96) + "Alliance.Crew.Struct.prop" + Chr(96) + ")." + Chr(10) + "2.  **" + Chr(96) + "this" + Chr(96) + " is Context String:** The " + Chr(96) + "this" + Chr(96) + " keyword, when used in a " + Chr(96) + "proc" + Chr(96) + ", holds the *path string* passed during the call. It's only valid inside " + Chr(96) + "proc" + Chr(96) + "s and requires explicit string comparison for conditional logic." + Chr(10) + Chr(10) + "### Arrays in Structs" + Chr(10) + Chr(10) + "Arrays can be defined as properties within structs just like any other data type:" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet1 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "### Summary of OSP (Ordinal Struct Programming)" + Chr(10) + Chr(10) + "-   **Organizes** code using optional " + Chr(96) + "alliance" + Chr(96) + "/" + Chr(96) + "crew" + Chr(96) + " hierarchies and " + Chr(96) + "struct" + Chr(96) + " data containers." + Chr(10) + "-   **Emphasizes** explicit, **ordinal** (position-based) access via mandatory **full paths**." + Chr(10) + "-   Uses " + Chr(96) + "struct" + Chr(96) + " for data aggregation and " + Chr(96) + "proc" + Chr(96) + " for associated procedures within the hierarchy." + Chr(10) + "-   Offers an optional " + Chr(96) + "this" + Chr(96) + " keyword for " + Chr(96) + "proc" + Chr(96) + "s to receive the **calling struct's path as a string**, enabling context-specific actions via string comparison." + Chr(10) + "-   Provides **global accessibility** for all defined structs and procs via their full paths." + Chr(10) + "-   Serves as an **alternative structure** within HTVM, focusing on explicitness and hierarchy, potentially avoiding certain OOP complexities but introducing verbosity and reliance on string paths for context." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "## Note:" + Chr(10) + Chr(10) + "### Never use underscores when naming things in OSP. Otherwise, you can use them, but be cautious because underscores can be unstable." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + "#### Example of OSP (Ordinal Struct Programming)" + Chr(10) + Chr(10) + Chr(96) + Chr(96) + Chr(96) + "htvm" + Chr(10) + htvmSnippet0 + Chr(10) + Chr(96) + Chr(96) + Chr(96) + Chr(10) + Chr(10) + "OSP (Ordinal Struct Programming) provides a structured, path-based approach to organizing data and procedures within HTVM, emphasizing explicit referencing." + Chr(10) + Chr(10) + "---" + Chr(10) + Chr(10) + outMDsec1 + Chr(10) + Chr(10) + outMDsec2 + Chr(10) + Chr(10) + outMDsec3 + Chr(10) + Chr(10) + outMDsec4 + Chr(10) + Chr(10) + outMDsec5 + Chr(10) + Chr(10) + outMDsec6 + Chr(10) + Chr(10) + outMDsec7 + Chr(10) + Chr(10) + outMDsec8 + Chr(10) + Chr(10) + outMDsec9 + Chr(10) + Chr(10) + outMDsec10 + Chr(10) + Chr(10) + outMDsec11 + Chr(10) + Chr(10) + outMDsec12 + Chr(10) + Chr(10) + outMDsec13 + Chr(10) + Chr(10) + outMDsec14 + Chr(10) + Chr(10) + outMDsec15 + Chr(10) + Chr(10) + "## Built-in Functions  " + Chr(10) + Chr(10) + "[Go back](#htvm-documentation) " + Chr(10) + Chr(10) + "HTVM includes a variety of built-in functions organized into categories for convenience." + Chr(10) + Chr(10);
    std::string outMD = "";
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
    std::string str24 = "";
    std::string str25 = "";
    std::string str26 = "";
    std::string str27 = "";
    for (int A_Index19 = 0; A_Index19 < HTVM_Size(categories) + 0; A_Index19++) {
        //print(categories[A_Index19])
        str1 = Trim(StrTitleCase(Trim(StrSplit(categories[A_Index19], Chr(10), 1)))) + " Functions";
        // 1. [String Functions](#string-functions)
        str2 = STR(A_Index19 + 1) + ". [" + str1 + "](#" + Trim(StrReplace(StrLower(str1), " ", "-")) + ")";
        outMD += str2 + Chr(10);
        // [Go back](#built-in-functions)
    }
    outMD += Chr(10) + "---" + Chr(10) + Chr(10);
    std::string categoriesElement = "";
    for (int A_Index20 = 0; A_Index20 < HTVM_Size(categories) + 0; A_Index20++) {
        //print(categories[A_Index20])
        str1 = Trim(StrTitleCase(Trim(StrSplit(categories[A_Index20], Chr(10), 1)))) + " Functions";
        // ## String Functions
        str2 = "## " + Trim(str1) + Chr(10) + Chr(10) + "[Go back](#built-in-functions)" + Chr(10) + Chr(10);
        str10 = "[Go back](#" + Trim(StrReplace(StrLower(str1), " ", "-")) + ")";
        outMD += str2;
        // 1. [str1](#str1)
        // 2. [str2](#str2)
        // 3. [str3](#str3)
        categoriesElement = categories[A_Index20];
        std::vector<std::string> items21 = LoopParseFunc(categoriesElement, "\n", "\r");
        for (size_t A_Index21 = 0; A_Index21 < items21.size() + 0; A_Index21++) {
            std::string A_LoopField21 = items21[A_Index21 - 0];
            if (A_Index21 != 0) {
                if (Trim(A_LoopField21) != "") {
                    str1 = Trim(StrSplit(StrSplit(A_LoopField21, "|", 1), ":", 2));
                    str3 = STR(A_Index21) + ". [" + str1 + "](#" + Trim(StrReplace(StrLower(str1), " ", "-")) + ")";
                    outMD += str3 + Chr(10);
                }
            }
        }
        outMD += Chr(10) + "---" + Chr(10) + Chr(10) + "**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**" + Chr(10) + Chr(10) + "**HTVM build-in functions availability.**" + Chr(10) + Chr(10) + "| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |" + Chr(10) + "|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|" + Chr(10);
        std::vector<std::string> items22 = LoopParseFunc(categoriesElement, "\n", "\r");
        for (size_t A_Index22 = 0; A_Index22 < items22.size() + 0; A_Index22++) {
            std::string A_LoopField22 = items22[A_Index22 - 0];
            if (A_Index22 != 0) {
                if (Trim(A_LoopField22) != "") {
                    str1 = Trim(StrSplit(StrSplit(A_LoopField22, "|", 1), ":", 2));
                    // cpp py js and more
                    str4 = Trim(StrSplit(A_LoopField22, "|", 3));
                    str5 = Trim(StrSplit(A_LoopField22, "|", 4));
                    str6 = Trim(StrSplit(A_LoopField22, "|", 5));
                    str7 = Trim(StrSplit(A_LoopField22, "|", 6));
                    //
                    str11 = Trim(StrSplit(A_LoopField22, "|", 7));
                    str12 = Trim(StrSplit(A_LoopField22, "|", 8));
                    str13 = Trim(StrSplit(A_LoopField22, "|", 9));
                    str14 = Trim(StrSplit(A_LoopField22, "|", 10));
                    str15 = Trim(StrSplit(A_LoopField22, "|", 11));
                    str16 = Trim(StrSplit(A_LoopField22, "|", 12));
                    str17 = Trim(StrSplit(A_LoopField22, "|", 13));
                    str18 = Trim(StrSplit(A_LoopField22, "|", 14));
                    str19 = Trim(StrSplit(A_LoopField22, "|", 15));
                    str20 = Trim(StrSplit(A_LoopField22, "|", 16));
                    str21 = Trim(StrSplit(A_LoopField22, "|", 17));
                    // | str1 | Yes | No | Yes | and more
                    str3 = "| " + str1 + " | " + str4 + " | " + str5 + " | " + str6 + " | " + str7 + " |" + str11 + " |" + str12 + " |" + str13 + " |" + str14 + " |" + str15 + " |" + str16 + " |" + str17 + " |" + str18 + " |" + str19 + " |" + str20 + " |" + str21 + " |";
                    outMD += str3 + Chr(10);
                }
            }
        }
        outMD += Chr(10) + "---" + Chr(10) + Chr(10);
        std::vector<std::string> items23 = LoopParseFunc(categoriesElement, "\n", "\r");
        for (size_t A_Index23 = 0; A_Index23 < items23.size() + 0; A_Index23++) {
            std::string A_LoopField23 = items23[A_Index23 - 0];
            if (A_Index23 != 0) {
                if (Trim(A_LoopField23) != "") {
                    str1 = Trim(StrSplit(StrSplit(A_LoopField23, "|", 1), ":", 2));
                    str2 = "### " + str1 + Chr(10) + Chr(10) + Trim(str10) + Chr(10) + Chr(10) + "**HTVM build-in functions availability.**" + Chr(10) + Chr(10) + "| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |" + Chr(10) + "|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|" + Chr(10);
                    // cpp py js
                    str4 = Trim(StrSplit(A_LoopField23, "|", 3));
                    str5 = Trim(StrSplit(A_LoopField23, "|", 4));
                    str6 = Trim(StrSplit(A_LoopField23, "|", 5));
                    str7 = Trim(StrSplit(A_LoopField23, "|", 6));
                    //
                    str11 = Trim(StrSplit(A_LoopField23, "|", 7));
                    str12 = Trim(StrSplit(A_LoopField23, "|", 8));
                    str13 = Trim(StrSplit(A_LoopField23, "|", 9));
                    str14 = Trim(StrSplit(A_LoopField23, "|", 10));
                    str15 = Trim(StrSplit(A_LoopField23, "|", 11));
                    str16 = Trim(StrSplit(A_LoopField23, "|", 12));
                    str17 = Trim(StrSplit(A_LoopField23, "|", 13));
                    str18 = Trim(StrSplit(A_LoopField23, "|", 14));
                    str19 = Trim(StrSplit(A_LoopField23, "|", 15));
                    str20 = Trim(StrSplit(A_LoopField23, "|", 16));
                    str21 = Trim(StrSplit(A_LoopField23, "|", 17));
                    // | str1 | Yes | No | Yes | and more
                    str3 = "| " + str1 + " | " + str4 + " | " + str5 + " | " + str6 + " | " + str7 + " |" + str11 + " |" + str12 + " |" + str13 + " |" + str14 + " |" + str15 + " |" + str16 + " |" + str17 + " |" + str18 + " |" + str19 + " |" + str20 + " |" + str21 + " |";
                    str8 = "";
                    str9 = Trim(StrSplit(StrSplit(A_LoopField23, "|", 2), "description:", 2));
                    std::vector<std::string> items24 = LoopParseFunc(str9, "~~~");
                    for (size_t A_Index24 = 0; A_Index24 < items24.size() + 0; A_Index24++) {
                        std::string A_LoopField24 = items24[A_Index24 - 0];
                        if (A_Index24 != 0) {
                            if (A_LoopField24 != "") {
                                str8 += A_LoopField24 + Chr(10);
                            }
                        }
                    }
                    outMD += str2 + str3 + Chr(10) + Chr(10) + str8 + Chr(10) + "---" + Chr(10);
                }
            }
        }
    }
    std::string THEINSTESCEPAED = "";
    std::vector<std::string> items25 = LoopParseFunc(instructionFileData, "\n", "\r");
    for (size_t A_Index25 = 0; A_Index25 < items25.size() + 0; A_Index25++) {
        std::string A_LoopField25 = items25[A_Index25 - 0];
        if (A_Index25 <= 161) {
            THEINSTESCEPAED += escapeStr(Trim(A_LoopField25)) + Chr(10);
        }
    }
    THEINSTESCEPAED = StringTrimRight(THEINSTESCEPAED, 1);
    std::string htmlUP = "" + Chr(60) + "!DOCTYPE html" + Chr(62) + Chr(10) + Chr(60) + "html lang=" + Chr(34) + "en" + Chr(34) + Chr(62) + Chr(10) + Chr(60) + "head" + Chr(62) + Chr(10) + "    " + Chr(60) + "meta charset=" + Chr(34) + "UTF-8" + Chr(34) + Chr(62) + Chr(10) + "    " + Chr(60) + "meta name=" + Chr(34) + "viewport" + Chr(34) + " content=" + Chr(34) + "width=device-width, initial-scale=1.0" + Chr(34) + Chr(62) + Chr(10) + "    " + Chr(60) + "title" + Chr(62) + "GitHub-Style Markdown with Ace Editor" + Chr(60) + "/title" + Chr(62) + Chr(10) + Chr(10) + "    " + Chr(60) + "!-- Link to markdown-it library --" + Chr(62) + Chr(10) + "    " + Chr(60) + "script src=" + Chr(34) + "https://cdn.jsdelivr.net/npm/markdown-it@12.0.4/dist/markdown-it.min.js" + Chr(34) + Chr(62) + Chr(60) + "/script" + Chr(62) + Chr(10) + "    " + Chr(10) + "    " + Chr(60) + "!-- Ace Editor --" + Chr(62) + Chr(10) + "    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/ace.js" + Chr(34) + Chr(62) + Chr(60) + "/script" + Chr(62) + Chr(10) + "    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/theme-monokai.min.js" + Chr(34) + Chr(62) + Chr(60) + "/script" + Chr(62) + Chr(10) + "    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-javascript.min.js" + Chr(34) + Chr(62) + Chr(60) + "/script" + Chr(62) + Chr(10) + "    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-python.min.js" + Chr(34) + Chr(62) + Chr(60) + "/script" + Chr(62) + Chr(10) + "    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-html.min.js" + Chr(34) + Chr(62) + Chr(60) + "/script" + Chr(62) + Chr(10) + "    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-css.min.js" + Chr(34) + Chr(62) + Chr(60) + "/script" + Chr(62) + Chr(10) + "    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-json.min.js" + Chr(34) + Chr(62) + Chr(60) + "/script" + Chr(62) + Chr(10) + Chr(10) + "    " + Chr(60) + "!-- Font Awesome for icons --" + Chr(62) + Chr(10) + "    " + Chr(60) + "link rel=" + Chr(34) + "stylesheet" + Chr(34) + " href=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css" + Chr(34) + Chr(62) + Chr(10) + Chr(10) + "    " + Chr(60) + "style" + Chr(62) + Chr(10) + "        /* Dark Mode Styles */" + Chr(10) + "        body {" + Chr(10) + "            background-color: #121212;" + Chr(10) + "            color: #e0e0e0;" + Chr(10) + "            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;" + Chr(10) + "            line-height: 1.6;" + Chr(10) + "            padding-left: 30px;" + Chr(10) + "            padding-right: 30px;" + Chr(10) + "            margin: 0;" + Chr(10) + "            word-wrap: break-word;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        h1, h2, h3, h4, h5, h6 {" + Chr(10) + "            color: #ffffff;" + Chr(10) + "            position: relative;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        /* Container for the markdown content */" + Chr(10) + "        #markdown-output {" + Chr(10) + "            background-color: #1e1e1e;" + Chr(10) + "            border-radius: 8px;" + Chr(10) + "            padding: 30px;" + Chr(10) + "            margin-top: 20px;" + Chr(10) + "            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        /* Header Styling */" + Chr(10) + "        h1 {" + Chr(10) + "            font-size: 2.5em;" + Chr(10) + "            border-bottom: 2px solid #444;" + Chr(10) + "            padding-bottom: 10px;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        h2 {" + Chr(10) + "            color: #ffffff;" + Chr(10) + "            border-bottom: 1px solid #444;" + Chr(10) + "            padding-bottom: 5px;" + Chr(10) + "            margin-top: 30px;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        h3 {" + Chr(10) + "            color: #81a1c1;" + Chr(10) + "            margin-top: 20px;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        /* Links */" + Chr(10) + "        a {" + Chr(10) + "            color: #1e90ff;" + Chr(10) + "            text-decoration: none;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        a:hover {" + Chr(10) + "            text-decoration: underline;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        /* External link icon */" + Chr(10) + "        a.external-link:after {" + Chr(10) + "            content: " + Chr(34) + " " + Chr(92) + "2197" + Chr(34) + ";" + Chr(10) + "            display: inline-block;" + Chr(10) + "            margin-left: 4px;" + Chr(10) + "            font-size: 0.8em;" + Chr(10) + "        }" + Chr(10) + "        " + Chr(10) + "        /* Header anchor links that show on hover */" + Chr(10) + "        .header-anchor {" + Chr(10) + "            opacity: 0;" + Chr(10) + "            font-size: 0.8em;" + Chr(10) + "            margin-left: 8px;" + Chr(10) + "            color: #666;" + Chr(10) + "            transition: opacity 0.2s ease-in-out;" + Chr(10) + "        }" + Chr(10) + "        " + Chr(10) + "        h1:hover .header-anchor," + Chr(10) + "        h2:hover .header-anchor," + Chr(10) + "        h3:hover .header-anchor," + Chr(10) + "        h4:hover .header-anchor," + Chr(10) + "        h5:hover .header-anchor," + Chr(10) + "        h6:hover .header-anchor {" + Chr(10) + "            opacity: 1;" + Chr(10) + "            color: #1e90ff;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        /* Ace Editor Styling */" + Chr(10) + "        .ace-editor-container {" + Chr(10) + "            margin: 20px 0;" + Chr(10) + "            border-radius: 8px;" + Chr(10) + "            overflow: hidden;" + Chr(10) + "        }" + Chr(10) + "        " + Chr(10) + "        .ace-editor {" + Chr(10) + "            width: 100%;" + Chr(10) + "            border-radius: 8px;" + Chr(10) + "            /* Height will be set dynamically based on content */" + Chr(10) + "        }" + Chr(10) + "        " + Chr(10) + "        .ace-editor-header {" + Chr(10) + "            background-color: #333;" + Chr(10) + "            color: #fff;" + Chr(10) + "            padding: 8px 15px;" + Chr(10) + "            font-family: monospace;" + Chr(10) + "            font-size: 0.9em;" + Chr(10) + "            display: flex;" + Chr(10) + "            justify-content: space-between;" + Chr(10) + "            align-items: center;" + Chr(10) + "            border-top-left-radius: 8px;" + Chr(10) + "            border-top-right-radius: 8px;" + Chr(10) + "        }" + Chr(10) + "        " + Chr(10) + "        .ace-editor-language {" + Chr(10) + "            font-weight: bold;" + Chr(10) + "            color: #82aaff;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        /* Copy Button Styling */" + Chr(10) + "        .copy-button {" + Chr(10) + "            background-color: #2a2a2a;" + Chr(10) + "            border: none;" + Chr(10) + "            color: #ccc;" + Chr(10) + "            border-radius: 4px;" + Chr(10) + "            padding: 3px 8px;" + Chr(10) + "            font-size: 12px;" + Chr(10) + "            cursor: pointer;" + Chr(10) + "            margin-right: 10px;" + Chr(10) + "            transition: all 0.2s ease;" + Chr(10) + "            display: flex;" + Chr(10) + "            align-items: center;" + Chr(10) + "        }" + Chr(10) + "        " + Chr(10) + "        .copy-button:hover {" + Chr(10) + "            background-color: #3a3a3a;" + Chr(10) + "            color: #fff;" + Chr(10) + "        }" + Chr(10) + "        " + Chr(10) + "        .copy-button i {" + Chr(10) + "            margin-right: 4px;" + Chr(10) + "        }" + Chr(10) + "        " + Chr(10) + "        .copy-success {" + Chr(10) + "            background-color: #28a745 !important;" + Chr(10) + "            color: white !important;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        /* Inline code */" + Chr(10) + "        p code, li code {" + Chr(10) + "            background-color: #2b2b2b;" + Chr(10) + "            padding: 2px 5px;" + Chr(10) + "            border-radius: 3px;" + Chr(10) + "            font-family: Consolas, 'Courier New', monospace;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        /* Table Styling */" + Chr(10) + "        table {" + Chr(10) + "            width: 100%;" + Chr(10) + "            margin: 20px 0;" + Chr(10) + "            border-collapse: collapse;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        th, td {" + Chr(10) + "            padding: 10px;" + Chr(10) + "            text-align: left;" + Chr(10) + "            border: 1px solid #444;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        th {" + Chr(10) + "            background-color: #333;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        tr:nth-child(even) {" + Chr(10) + "            background-color: #2a2a2a;" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        tr:hover {" + Chr(10) + "            background-color: #444;" + Chr(10) + "        }" + Chr(10) + "        " + Chr(10) + "        /* Fix for internal links */" + Chr(10) + "        :target {" + Chr(10) + "            scroll-margin-top: 20px;" + Chr(10) + "            animation: highlight 2s ease;" + Chr(10) + "        }" + Chr(10) + "        " + Chr(10) + "        @keyframes highlight {" + Chr(10) + "            from { background-color: #333333; }" + Chr(10) + "            to { background-color: transparent; }" + Chr(10) + "        }" + Chr(10) + "    " + Chr(60) + "/style" + Chr(62) + Chr(10) + Chr(60) + "/head" + Chr(62) + Chr(10) + Chr(60) + "body" + Chr(62) + Chr(10) + Chr(10) + "    " + Chr(60) + "!-- Markdown content written in normal syntax --" + Chr(62) + Chr(10) + Chr(60) + "div id=" + Chr(34) + "markdown-content" + Chr(34) + " style=" + Chr(34) + "display:none;" + Chr(34) + Chr(62) + Chr(10) + Chr(10);
    std::string htmlDOWN = "" + Chr(10) + Chr(60) + "/div" + Chr(62) + Chr(10) + Chr(10) + "    " + Chr(60) + "br" + Chr(62) + Chr(60) + "br" + Chr(62) + Chr(10) + Chr(10) + "    " + Chr(60) + "!-- A div to display the rendered HTML --" + Chr(62) + Chr(10) + "    " + Chr(60) + "div id=" + Chr(34) + "markdown-output" + Chr(34) + Chr(62) + Chr(60) + "/div" + Chr(62) + Chr(10) + Chr(10) + "    " + Chr(60) + "script" + Chr(62) + Chr(10) + "        // Initialize Markdown-it with HTML enabled and proper heading IDs" + Chr(10) + "        var md = window.markdownit({" + Chr(10) + "            html: true," + Chr(10) + "            linkify: true," + Chr(10) + "            typographer: true" + Chr(10) + "        });" + Chr(10) + "        " + Chr(10) + "        function changeFaviconAtTheBeginning(faviconUrl) {" + Chr(10) + "        // Create a new favicon link element" + Chr(10) + "        const newFavicon = document.createElement(" + Chr(34) + "link" + Chr(34) + ");" + Chr(10) + "        newFavicon.rel = " + Chr(34) + "icon" + Chr(34) + ";" + Chr(10) + "        newFavicon.href = faviconUrl;" + Chr(10) + Chr(10) + "        // Get the current favicon element (if exists)" + Chr(10) + "        const existingFavicon = document.querySelector('link[rel=" + Chr(34) + "icon" + Chr(34) + "]');" + Chr(10) + Chr(10) + "        // Replace the current favicon with the new one" + Chr(10) + "        if (existingFavicon) {" + Chr(10) + "          // If a favicon exists, replace it" + Chr(10) + "          document.head.removeChild(existingFavicon); // Remove the existing favicon" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        // Append the new favicon to the head" + Chr(10) + "        document.head.appendChild(newFavicon);" + Chr(10) + "      }" + Chr(10) + Chr(10) + "      // Call the function with the desired favicon URL" + Chr(10) + "      changeFaviconAtTheBeginning(" + Chr(34) + "https://i.ibb.co/Jpty1B8/305182938-1a0efe63-726e-49ca-a13c-d0ed627f2ea7.png" + Chr(34) + ");" + Chr(10) + Chr(10) + "      function showCustomMessageBox(options, title, text, value, timeout) {" + Chr(10) + "        return new Promise((resolve) =" + Chr(62) + " {" + Chr(10) + "          // Define default options for the message box" + Chr(10) + "          let defaultOptions = {" + Chr(10) + "            title: title || " + Chr(34) + Chr(34) + ", // Default title is empty" + Chr(10) + "            text: text || " + Chr(34) + "Press OK to continue." + Chr(34) + ", // Default text if not provided" + Chr(10) + "            showCancelButton: false, // Default is to not show Cancel button" + Chr(10) + "            showDenyButton: false, // Default is to not show Deny button" + Chr(10) + "            confirmButtonText: " + Chr(34) + "OK" + Chr(34) + ", // Default text for OK button" + Chr(10) + "            focusConfirm: true, // Default focus on OK button" + Chr(10) + "          };" + Chr(10) + Chr(10) + "          let numOriginal = value;" + Chr(10) + Chr(10) + "          let num = numOriginal;" + Chr(10) + Chr(10) + "          let done1 = 0;" + Chr(10) + Chr(10) + "          let done2 = 0;" + Chr(10) + Chr(10) + "          let done3 = 0;" + Chr(10) + Chr(10) + "          let AIndex = 0;" + Chr(10) + Chr(10) + "          for (AIndex = 1; AIndex " + Chr(60) + "= 1; AIndex++) {" + Chr(10) + "            // this is about if you add always on top in a msgbox it will be removed in js cuz its kinda useless..." + Chr(10) + "            // becouse if you like adding always on top in ahk in js we dont realy do it so yeah" + Chr(10) + "            if (num " + Chr(62) + "= 262144) {" + Chr(10) + "              num = num - 262144;" + Chr(10) + "              numOriginal = numOriginal - 262144;" + Chr(10) + "            }" + Chr(10) + Chr(10) + "            if (num " + Chr(62) + "= 256 && num " + Chr(60) + " 500) {" + Chr(10) + "              num = num - 256;" + Chr(10) + Chr(10) + "              done3 = 256;" + Chr(10) + "            }" + Chr(10) + Chr(10) + "            if (num " + Chr(62) + "= 512) {" + Chr(10) + "              num = num - 512;" + Chr(10) + Chr(10) + "              done3 = 512;" + Chr(10) + "            }" + Chr(10) + Chr(10) + "            if (num == 0) {" + Chr(10) + "              done1 = 0;" + Chr(10) + Chr(10) + "              break;" + Chr(10) + "            }" + Chr(10) + Chr(10) + "            if (num " + Chr(60) + "= 6) {" + Chr(10) + "              done1 = num;" + Chr(10) + Chr(10) + "              break;" + Chr(10) + "            }" + Chr(10) + Chr(10) + "            if (num " + Chr(62) + "= 64 && num " + Chr(60) + " 64 * 2) {" + Chr(10) + "              done2 = 64;" + Chr(10) + Chr(10) + "              if (num == 64) {" + Chr(10) + "                done1 = 0;" + Chr(10) + Chr(10) + "                break;" + Chr(10) + "              } else {" + Chr(10) + "                done1 = num - 64;" + Chr(10) + Chr(10) + "                break;" + Chr(10) + "              }" + Chr(10) + "            }" + Chr(10) + Chr(10) + "            if (num " + Chr(62) + "= 48 && num " + Chr(60) + " 63) {" + Chr(10) + "              done2 = 48;" + Chr(10) + Chr(10) + "              if (num == 48) {" + Chr(10) + "                done1 = 0;" + Chr(10) + Chr(10) + "                break;" + Chr(10) + "              } else {" + Chr(10) + "                done1 = num - 48;" + Chr(10) + Chr(10) + "                break;" + Chr(10) + "              }" + Chr(10) + "            }" + Chr(10) + Chr(10) + "            if (num " + Chr(62) + "= 32 && num " + Chr(60) + " 47) {" + Chr(10) + "              done2 = 32;" + Chr(10) + Chr(10) + "              if (num == 32) {" + Chr(10) + "                done1 = 0;" + Chr(10) + Chr(10) + "                break;" + Chr(10) + "              } else {" + Chr(10) + "                done1 = num - 32;" + Chr(10) + Chr(10) + "                break;" + Chr(10) + "              }" + Chr(10) + "            }" + Chr(10) + Chr(10) + "            if (num " + Chr(62) + "= 16 && num " + Chr(60) + " 30) {" + Chr(10) + "              done2 = 16;" + Chr(10) + Chr(10) + "              if (num == 16) {" + Chr(10) + "                done1 = 0;" + Chr(10) + Chr(10) + "                break;" + Chr(10) + "              } else {" + Chr(10) + "                done1 = num - 16;" + Chr(10) + Chr(10) + "                break;" + Chr(10) + "              }" + Chr(10) + "            }" + Chr(10) + "          }" + Chr(10) + Chr(10) + "          let doneAdded = done1 + done2 + done3;" + Chr(10) + Chr(10) + "          if (doneAdded !== numOriginal) {" + Chr(10) + "            // displayMessage(" + Chr(34) + "The calc was wrong!" + Chr(34) + ");" + Chr(10) + "          } else {" + Chr(10) + "            // displayMessage(" + Chr(34) + "num was: " + Chr(34) + " + numOriginal + " + Chr(34) + Chr(92) + "ndone1: " + Chr(34) + " + done1 + " + Chr(34) + Chr(92) + "ndone2: " + Chr(34) + " + done2 + " + Chr(34) + Chr(92) + "ndone3: " + Chr(34) + " + done3);" + Chr(10) + "          }" + Chr(10) + Chr(10) + "          // Parse the value to determine the options for the message box" + Chr(10) + "          if (done1 === 1) defaultOptions.showCancelButton = true; // OK/Cancel in ahk but here it will show Ok/Cancel wiat its same haha" + Chr(10) + Chr(10) + "          // not gonna work if you can make it work i will appreciate" + Chr(10) + "          //   if (done1 === 2) {" + Chr(10) + "          //     defaultOptions.showCancelButton = true; // Abort/Retry/Ignore" + Chr(10) + "          //     defaultOptions.showDenyButton = true;" + Chr(10) + "          //   }" + Chr(10) + "          if (done1 === 3) {" + Chr(10) + "            defaultOptions.showCancelButton = true; // Yes/No/Cancel in ahk but here it will show Ok/No/Cancel" + Chr(10) + "            defaultOptions.showDenyButton = true;" + Chr(10) + "          }" + Chr(10) + "          if (done1 === 4) {" + Chr(10) + "            // defaultOptions.showCancelButton = true;" + Chr(10) + "            defaultOptions.showDenyButton = true; // Yes/No in ahk but here it will show Ok/No" + Chr(10) + "          }" + Chr(10) + "          if (done1 === 5) {" + Chr(10) + "            defaultOptions.showCancelButton = true; // Retry/Cancel in ahk but here it will show Ok/Cancel tip you can write in the Msgbox press ok to retry" + Chr(10) + "          }" + Chr(10) + "          // not gonna work if you can make it work i will appreciate" + Chr(10) + "          //   if (done1 === 6) {" + Chr(10) + "          //     defaultOptions.showCancelButton = true; // Cancel/Try Again/Continue" + Chr(10) + "          //     defaultOptions.showDenyButton = true;" + Chr(10) + "          //   }" + Chr(10) + Chr(10) + "          if (done2 === 16) defaultOptions.icon = " + Chr(34) + "error" + Chr(34) + "; // Icon Hand (stop/error)" + Chr(10) + "          if (done2 === 32) defaultOptions.icon = " + Chr(34) + "question" + Chr(34) + "; // Icon Question" + Chr(10) + "          if (done2 === 48) defaultOptions.icon = " + Chr(34) + "warning" + Chr(34) + "; // Icon Exclamation" + Chr(10) + "          if (done2 === 64) defaultOptions.icon = " + Chr(34) + "info" + Chr(34) + "; // Icon Asterisk (info)" + Chr(10) + Chr(10) + "          if (done3 === 256) defaultOptions.focusDeny = true; // Makes the 3rd button the default" + Chr(10) + "          if (done3 === 512) defaultOptions.focusCancel = true; // Makes the 2nd button the default" + Chr(10) + Chr(10) + "          // Set timeout if provided" + Chr(10) + "          if (timeout) {" + Chr(10) + "            defaultOptions.timer = timeout * 1000; // Convert timeout to milliseconds" + Chr(10) + "          }" + Chr(10) + Chr(10) + "          // Merge default options with provided options" + Chr(10) + "          Object.assign(defaultOptions, options);" + Chr(10) + Chr(10) + "          // Display the message box with the constructed options" + Chr(10) + "          Swal.fire(defaultOptions).then((result) =" + Chr(62) + " {" + Chr(10) + "            if (result.isConfirmed) {" + Chr(10) + "              resolve(" + Chr(34) + "OK" + Chr(34) + ");" + Chr(10) + "            } else if (result.isDenied) {" + Chr(10) + "              resolve(" + Chr(34) + "No" + Chr(34) + ");" + Chr(10) + "            } else {" + Chr(10) + "              resolve(" + Chr(34) + "Cancel" + Chr(34) + ");" + Chr(10) + "            }" + Chr(10) + "          });" + Chr(10) + "        });" + Chr(10) + "      }" + Chr(10) + Chr(10) + "      var lastKeyPressed = " + Chr(34) + Chr(34) + ";" + Chr(10) + Chr(10) + "      function trackLastKeyPressed() {" + Chr(10) + "        document.addEventListener(" + Chr(34) + "keydown" + Chr(34) + ", function (event) {" + Chr(10) + "          lastKeyPressed = event.key;" + Chr(10) + "          // console.log(lastKeyPressed);" + Chr(10) + "        });" + Chr(10) + "      }" + Chr(10) + Chr(10) + "      function getLastKeyPressed() {" + Chr(10) + "        return lastKeyPressed;" + Chr(10) + "      }" + Chr(10) + Chr(10) + "      // Call the trackLastKeyPressed function to start tracking key presses" + Chr(10) + "      trackLastKeyPressed();" + Chr(10) + Chr(10) + "      let lastInputTime = Date.now(); // Initialize with current timestamp" + Chr(10) + "      let startTimestamp = Date.now(); // Initialize with current timestamp" + Chr(10) + Chr(10) + "      // Event listener to track user activity" + Chr(10) + "      function resetIdleTimer() {" + Chr(10) + "        lastInputTime = Date.now(); // Update last input time" + Chr(10) + "      }" + Chr(10) + Chr(10) + "      document.addEventListener(" + Chr(34) + "mousemove" + Chr(34) + ", resetIdleTimer);" + Chr(10) + "      document.addEventListener(" + Chr(34) + "keypress" + Chr(34) + ", resetIdleTimer);" + Chr(10) + Chr(10) + "      // Function to calculate time since last input event" + Chr(10) + "      function A_TimeIdle() {" + Chr(10) + "        return Date.now() - lastInputTime; // Calculate time difference" + Chr(10) + "      }" + Chr(10) + Chr(10) + "      function LoopParseFunc(varString, delimiter1=" + Chr(34) + Chr(34) + ", delimiter2=" + Chr(34) + Chr(34) + ") {" + Chr(10) + "    let items;" + Chr(10) + "    if (!delimiter1 && !delimiter2) {" + Chr(10) + "        // If no delimiters are provided, return an array of characters" + Chr(10) + "        items = [...varString];" + Chr(10) + "    } else {" + Chr(10) + "        // Construct the regular expression pattern for splitting the string" + Chr(10) + "        let pattern = new RegExp('[' + delimiter1.replace(/[.*+?^${}()|[" + Chr(92) + "]" + Chr(92) + Chr(92) + "]/g, '" + Chr(92) + Chr(92) + "$&') + delimiter2.replace(/[.*+?^${}()|[" + Chr(92) + "]" + Chr(92) + Chr(92) + "]/g, '" + Chr(92) + Chr(92) + "$&') + ']+');" + Chr(10) + "        // Split the string using the constructed pattern" + Chr(10) + "        items = varString.split(pattern);" + Chr(10) + "    }" + Chr(10) + "    return items;" + Chr(10) + "}" + Chr(10) + Chr(10) + "function print(value) {" + Chr(10) + "    console.log(value)" + Chr(10) + "}" + Chr(10) + Chr(10) + "// Convert value to string" + Chr(10) + "function STR(value) {" + Chr(10) + "    if (value === null || value === undefined) {" + Chr(10) + "        return " + Chr(34) + Chr(34) + "; // Return a string for null or undefined" + Chr(10) + "    } else if (typeof value === 'number') {" + Chr(10) + "        return value.toString();" + Chr(10) + "    } else if (typeof value === 'boolean') {" + Chr(10) + "        return value ? " + Chr(34) + "1" + Chr(34) + " : " + Chr(34) + "0" + Chr(34) + ";" + Chr(10) + "    } else if (typeof value === 'string') {" + Chr(10) + "        return value; // Return the string as is" + Chr(10) + "    } else {" + Chr(10) + "        // Handle any unexpected types gracefully" + Chr(10) + "        return String(value); // Convert any other type to a string" + Chr(10) + "    }" + Chr(10) + "}" + Chr(10) + Chr(10) + "function Chr(number) {" + Chr(10) + "    // Return the character corresponding to the Unicode code point, or an empty string if out of range" + Chr(10) + "    return (number " + Chr(62) + "= 0 && number " + Chr(60) + "= 0x10FFFF) ? String.fromCharCode(number) : " + Chr(34) + Chr(34) + ";" + Chr(10) + "}" + Chr(10) + Chr(10) + "function SubStr(str, startPos, length = -1) {" + Chr(10) + "    // If str is null or undefined, return an empty string" + Chr(10) + "    if (str === null || str === undefined) {" + Chr(10) + "        return " + Chr(34) + Chr(34) + ";" + Chr(10) + "    }" + Chr(10) + "    let strLen = str.length;" + Chr(10) + "    " + Chr(10) + "    // Handle negative starting positions (C++ style)" + Chr(10) + "    if (startPos " + Chr(60) + " 1) {" + Chr(10) + "        startPos = strLen + startPos;" + Chr(10) + "        if (startPos " + Chr(60) + " 0) startPos = 0;" + Chr(10) + "    } else {" + Chr(10) + "        startPos -= 1; // Convert to 0-based index (C++ style)" + Chr(10) + "    }" + Chr(10) + "    // Handle length (C++ style)" + Chr(10) + "    if (length " + Chr(60) + " 0) {" + Chr(10) + "        length = strLen - startPos; // Length to end of string" + Chr(10) + "    } else if (startPos + length " + Chr(62) + " strLen) {" + Chr(10) + "        length = strLen - startPos; // Adjust length to fit within the string" + Chr(10) + "    }" + Chr(10) + "    // Extract the substring" + Chr(10) + "    return str.substr(startPos, length);" + Chr(10) + "}" + Chr(10) + Chr(10) + "function Trim(inputString) {" + Chr(10) + "    return inputString ? inputString.trim() : " + Chr(34) + Chr(34) + ";" + Chr(10) + "}" + Chr(10) + Chr(10) + "function StrReplace(originalString, find, replaceWith) {" + Chr(10) + "    return originalString.split(find).join(replaceWith);" + Chr(10) + "}" + Chr(10) + Chr(10) + "function StrLower(string) {" + Chr(10) + "    return string.toLowerCase();" + Chr(10) + "}" + Chr(10) + Chr(10) + "function StrSplit(inputStr, delimiter, num) {" + Chr(10) + "    const parts = inputStr.split(delimiter);" + Chr(10) + "    return (num " + Chr(62) + " 0 && num " + Chr(60) + "= parts.length) ? parts[num - 1] : " + Chr(34) + Chr(34) + ";" + Chr(10) + "}" + Chr(10) + Chr(10) + "// Function to sort and remove duplicates" + Chr(10) + "function sortArr(inputArray) {" + Chr(10) + "    // Remove duplicates using Set and sort the array" + Chr(10) + "    return [...new Set(inputArray)].sort();" + Chr(10) + "}" + Chr(10) + Chr(10) + "function countChars(string, theChar) {" + Chr(10) + "    let count = 0;" + Chr(10) + "    for (let char of string) {" + Chr(10) + "        if (char === theChar) {" + Chr(10) + "            count++;" + Chr(10) + "        }" + Chr(10) + "    }" + Chr(10) + "    return count;" + Chr(10) + "}" + Chr(10) + Chr(10) + Chr(10) + "//" + Chr(10) + Chr(10) + "function StrTitleCase(inputString) {" + Chr(10) + "    return inputString.split(' ')  // Split the string into words" + Chr(10) + "        .map(word =" + Chr(62) + " {" + Chr(10) + "            if (word) {  // Avoid empty words (multiple spaces)" + Chr(10) + "                return word.charAt(0).toUpperCase() + word.slice(1).toLowerCase();  // Capitalize first letter" + Chr(10) + "            }" + Chr(10) + "            return word;  // If it's an empty string (spaces), keep it as is" + Chr(10) + "        })" + Chr(10) + "        .join(' ');  // Join the words back together with spaces" + Chr(10) + "}" + Chr(10) + Chr(10) + "function HTVM_getLang_HTVM() {" + Chr(10) + "    return " + Chr(34) + "js" + Chr(34) + ";" + Chr(10) + "}" + Chr(10) + Chr(10) + "function HTVM_Append(arr, value) {" + Chr(10) + "    arr.push(value);" + Chr(10) + "}" + Chr(10) + Chr(10) + "function HTVM_Size(arr) {" + Chr(10) + "    return arr.length;" + Chr(10) + "}" + Chr(10) + Chr(10) + "      // Function to calculate tick count in milliseconds" + Chr(10) + "      function A_TickCount() {" + Chr(10) + "        return Date.now() - startTimestamp;" + Chr(10) + "      }" + Chr(10) + Chr(10) + "      function GuiControl(action, id, param1, param2, param3, param4) {" + Chr(10) + "        const element = document.getElementById(id);" + Chr(10) + "        if (element) {" + Chr(10) + "          // Handle DOM elements" + Chr(10) + "          if (action === " + Chr(34) + "move" + Chr(34) + ") {" + Chr(10) + "            // Set position and size" + Chr(10) + "            element.style.left = param1 + " + Chr(34) + "px" + Chr(34) + ";" + Chr(10) + "            element.style.top = param2 + " + Chr(34) + "px" + Chr(34) + ";" + Chr(10) + "            element.style.width = param3 + " + Chr(34) + "px" + Chr(34) + ";" + Chr(10) + "            element.style.height = param4 + " + Chr(34) + "px" + Chr(34) + ";" + Chr(10) + "          } else if (action === " + Chr(34) + "focus" + Chr(34) + " && (element instanceof HTMLInputElement || element instanceof HTMLElement)) {" + Chr(10) + "            // Focus on the element" + Chr(10) + "            element.focus();" + Chr(10) + "          } else if (action === " + Chr(34) + "text" + Chr(34) + ") {" + Chr(10) + "            // Set new text content" + Chr(10) + "            element.textContent = param1;" + Chr(10) + "          } else if (action === " + Chr(34) + "hide" + Chr(34) + ") {" + Chr(10) + "            // Hide the element" + Chr(10) + "            element.style.display = " + Chr(34) + "none" + Chr(34) + ";" + Chr(10) + "          } else if (action === " + Chr(34) + "show" + Chr(34) + ") {" + Chr(10) + "            // Show the element" + Chr(10) + "            element.style.display = " + Chr(34) + Chr(34) + ";" + Chr(10) + "          } else if (action === " + Chr(34) + "enable" + Chr(34) + ") {" + Chr(10) + "            // Enable the element" + Chr(10) + "            element.disabled = false;" + Chr(10) + "          } else if (action === " + Chr(34) + "disable" + Chr(34) + ") {" + Chr(10) + "            // Disable the element" + Chr(10) + "            element.disabled = true;" + Chr(10) + "          } else if (action === " + Chr(34) + "font" + Chr(34) + ") {" + Chr(10) + "            // Set font size" + Chr(10) + "            element.style.fontSize = param1 + " + Chr(34) + "px" + Chr(34) + ";" + Chr(10) + "          } else if (action === " + Chr(34) + "destroy" + Chr(34) + ") {" + Chr(10) + "            // Remove the element from the DOM" + Chr(10) + "            element.parentNode.removeChild(element);" + Chr(10) + "          } else if (action === " + Chr(34) + "color" + Chr(34) + ") {" + Chr(10) + "            // Set color" + Chr(10) + "            element.style.color = param1;" + Chr(10) + "          } else if (action === " + Chr(34) + "picture" + Chr(34) + ") {" + Chr(10) + "            // Change the image source" + Chr(10) + "            if (element instanceof HTMLImageElement) {" + Chr(10) + "              element.src = param1;" + Chr(10) + "            } else {" + Chr(10) + "              console.error(" + Chr(34) + "Element is not an " + Chr(60) + "img" + Chr(62) + " tag, cannot change picture." + Chr(34) + ");" + Chr(10) + "            }" + Chr(10) + "          } else if (action === " + Chr(34) + "textide" + Chr(34) + ") {" + Chr(10) + "            // Set value for Ace editor" + Chr(10) + "            var editor = ace.edit(id); // Access the Ace editor instance using its ID" + Chr(10) + "            if (editor && param1) {" + Chr(10) + "              editor.session.setValue(param1);" + Chr(10) + "            } else {" + Chr(10) + "              console.error(" + Chr(34) + "Element is not an Ace editor or parameter is missing." + Chr(34) + ");" + Chr(10) + "            }" + Chr(10) + "          }" + Chr(10) + "        } else {" + Chr(10) + "          // Handle canvas or non-existing element" + Chr(10) + "          if (action === " + Chr(34) + "move" + Chr(34) + ") {" + Chr(10) + "            // Update position and size of the rectangle" + Chr(10) + "            updateRectangle(id, param1, param2, param3, param4);" + Chr(10) + "            redrawCanvas(); // Redraw the canvas with updated rectangles" + Chr(10) + "          } else if (action === " + Chr(34) + "color" + Chr(34) + ") {" + Chr(10) + "            // Update color of the rectangle" + Chr(10) + "            updateRectangleColor(id, param1);" + Chr(10) + "            redrawCanvas(); // Redraw the canvas with updated rectangles" + Chr(10) + "          }" + Chr(10) + "        }" + Chr(10) + "      }" + Chr(10) + Chr(10) + "      function BuildInVars(varName) {" + Chr(10) + "        switch (varName) {" + Chr(10) + "          case " + Chr(34) + "A_ScreenWidth" + Chr(34) + ":" + Chr(10) + "            // Return screen width" + Chr(10) + "            return window.innerWidth;" + Chr(10) + "          case " + Chr(34) + "A_LastKey" + Chr(34) + ":" + Chr(10) + "            // Return screen width" + Chr(10) + "            return getLastKeyPressed();" + Chr(10) + "          case " + Chr(34) + "A_ScreenHeight" + Chr(34) + ":" + Chr(10) + "            // Return screen height" + Chr(10) + "            return window.innerHeight;" + Chr(10) + "          case " + Chr(34) + "A_TimeIdle" + Chr(34) + ":" + Chr(10) + "            // Return time idle" + Chr(10) + "            return A_TimeIdle();" + Chr(10) + "          case " + Chr(34) + "A_TickCount" + Chr(34) + ":" + Chr(10) + "            // Return tick count in milliseconds" + Chr(10) + "            return A_TickCount();" + Chr(10) + "          case " + Chr(34) + "A_Now" + Chr(34) + ":" + Chr(10) + "            // Return current local timestamp" + Chr(10) + "            return new Date().toLocaleString();" + Chr(10) + "          case " + Chr(34) + "A_YYYY" + Chr(34) + ":" + Chr(10) + "            // Return current year" + Chr(10) + "            return new Date().getFullYear();" + Chr(10) + "          case " + Chr(34) + "A_MM" + Chr(34) + ":" + Chr(10) + "            // Return current month" + Chr(10) + "            return (new Date().getMonth() + 1).toString().padStart(2, " + Chr(34) + "0" + Chr(34) + ");" + Chr(10) + "          case " + Chr(34) + "A_DD" + Chr(34) + ":" + Chr(10) + "            // Return current day" + Chr(10) + "            return new Date().getDate().toString().padStart(2, " + Chr(34) + "0" + Chr(34) + ");" + Chr(10) + "          case " + Chr(34) + "A_MMMM" + Chr(34) + ":" + Chr(10) + "            // Return full month name" + Chr(10) + "            return new Date().toLocaleDateString(undefined, { month: " + Chr(34) + "long" + Chr(34) + " });" + Chr(10) + "          case " + Chr(34) + "A_MMM" + Chr(34) + ":" + Chr(10) + "            // Return short month name" + Chr(10) + "            return new Date().toLocaleDateString(undefined, { month: " + Chr(34) + "short" + Chr(34) + " });" + Chr(10) + "          case " + Chr(34) + "A_DDDD" + Chr(34) + ":" + Chr(10) + "            // Return full day name" + Chr(10) + "            return new Date().toLocaleDateString(undefined, { weekday: " + Chr(34) + "long" + Chr(34) + " });" + Chr(10) + "          case " + Chr(34) + "A_DDD" + Chr(34) + ":" + Chr(10) + "            // Return short day name" + Chr(10) + "            return new Date().toLocaleDateString(undefined, { weekday: " + Chr(34) + "short" + Chr(34) + " });" + Chr(10) + "          case " + Chr(34) + "A_Hour" + Chr(34) + ":" + Chr(10) + "            // Return current hour" + Chr(10) + "            return new Date().getHours().toString().padStart(2, " + Chr(34) + "0" + Chr(34) + ");" + Chr(10) + "          case " + Chr(34) + "A_Min" + Chr(34) + ":" + Chr(10) + "            // Return current minute" + Chr(10) + "            return new Date().getMinutes().toString().padStart(2, " + Chr(34) + "0" + Chr(34) + ");" + Chr(10) + "          case " + Chr(34) + "A_Sec" + Chr(34) + ":" + Chr(10) + "            // Return current second" + Chr(10) + "            return new Date().getSeconds().toString().padStart(2, " + Chr(34) + "0" + Chr(34) + ");" + Chr(10) + "          case " + Chr(34) + "A_Space" + Chr(34) + ":" + Chr(10) + "            // Return space character" + Chr(10) + "            return " + Chr(34) + " " + Chr(34) + ";" + Chr(10) + "          case " + Chr(34) + "A_Tab" + Chr(34) + ":" + Chr(10) + "            // Return tab character" + Chr(10) + "            return " + Chr(34) + Chr(92) + "t" + Chr(34) + ";" + Chr(10) + Chr(10) + "          default:" + Chr(10) + "            // Handle unknown variable names" + Chr(10) + "            return null;" + Chr(10) + "        }" + Chr(10) + "      }" + Chr(10) + "      function StrReplace(originalString, find, replaceWith) {" + Chr(10) + "    return originalString.split(find).join(replaceWith);" + Chr(10) + "}" + Chr(10) + Chr(10) + "function StringTrimRight(input, numChars) {" + Chr(10) + "    return (numChars " + Chr(60) + "= input.length) ? input.substring(0, input.length - numChars) : input;" + Chr(10) + "}" + Chr(10) + Chr(10) + "//" + Chr(10) + Chr(10) + "      function Chr(number) {" + Chr(10) + "        // Check if the number is null" + Chr(10) + "        if (number === null) {" + Chr(10) + "          // Return an empty string" + Chr(10) + "          return " + Chr(34) + Chr(34) + ";" + Chr(10) + "        }" + Chr(10) + Chr(10) + "        // Check if the number is within the valid range" + Chr(10) + "        if (number " + Chr(62) + "= 0 && number " + Chr(60) + "= 0x10ffff) {" + Chr(10) + "          // Convert the number to a character using String.fromCharCode" + Chr(10) + "          return String.fromCharCode(number);" + Chr(10) + "        } else {" + Chr(10) + "          // Return an empty string for invalid numbers" + Chr(10) + "          return " + Chr(34) + Chr(34) + ";" + Chr(10) + "        }" + Chr(10) + "      }" + Chr(10) + Chr(10) + "let allHTVMinst = " + Chr(96) + THEINSTESCEPAED + Chr(96) + ";" + Chr(10) + Chr(10) + Chr(10) + "let allKeyWordsIn = " + Chr(34) + Chr(34) + "; // Global variable to store the result" + Chr(10) + "let allKeyWordsOut = " + Chr(34) + Chr(34) + ";" + Chr(10) + "let allFunctionNamesString = " + Chr(34) + Chr(34) + "; // Global string to store function names" + Chr(10) + "async function getFunctionNames() {" + Chr(10) + "    const url = 'https://raw.githubusercontent.com/TheMaster1127/HTVM/refs/heads/main/HTVM-instructions.txt';" + Chr(10) + "    " + Chr(10) + "    try {" + Chr(10) + "        const response = await fetch(url);" + Chr(10) + "        if (!response.ok) {" + Chr(10) + "            throw new Error(" + Chr(96) + "Network response was not ok: ${response.statusText}" + Chr(96) + ");" + Chr(10) + "        }" + Chr(10) + "        const text = await response.text();" + Chr(10) + "        " + Chr(10) + "        // Split text by line and get lines starting from line 162" + Chr(10) + "        const lines = text.split('" + Chr(92) + "n').slice(162); // Line 162 starts at index 161" + Chr(10) + "        " + Chr(10) + "        // Extract function names that start with " + Chr(34) + "name: " + Chr(34) + Chr(10) + "        const functionNames = lines" + Chr(10) + "            .map(line =" + Chr(62) + " line.trim()) // Trim each line" + Chr(10) + "            .filter(line =" + Chr(62) + " line.startsWith(" + Chr(34) + "name: " + Chr(34) + ")) // Only lines that start with " + Chr(34) + "name: " + Chr(34) + Chr(10) + "            .map(line =" + Chr(62) + " line.replace(" + Chr(34) + "name: " + Chr(34) + ", " + Chr(34) + Chr(34) + ").trim()) // Get function name (remove " + Chr(34) + "name: " + Chr(34) + " part)" + Chr(10) + "            .filter((value, index, self) =" + Chr(62) + " self.indexOf(value) === index); // Remove duplicates" + Chr(10) + "        " + Chr(10) + "        // Save the function names in the global variable" + Chr(10) + "        allFunctionNamesString = functionNames.join('" + Chr(92) + "n');" + Chr(10) + "        " + Chr(10) + "    } catch (error) {" + Chr(10) + "        console.error('Error fetching the text file:', error);" + Chr(10) + "    }" + Chr(10) + "}" + Chr(10) + "// Function to fetch the first 161 lines from a remote text file" + Chr(10) + "async function fetchFirst161Lines(url) {" + Chr(10) + "    try {" + Chr(10) + "        const response = await fetch(url);" + Chr(10) + "        if (!response.ok) {" + Chr(10) + "            throw new Error(" + Chr(96) + "Network response was not ok: ${response.statusText}" + Chr(96) + ");" + Chr(10) + "        }" + Chr(10) + "        const text = await response.text();" + Chr(10) + "        return text.split('" + Chr(92) + "n').slice(0, 162).join('" + Chr(92) + "n');" + Chr(10) + "    } catch (error) {" + Chr(10) + "        console.error('Error fetching the text file:', error);" + Chr(10) + "        return null;" + Chr(10) + "    }" + Chr(10) + "}" + Chr(10) + "// Main function to handle localStorage and data retrieval" + Chr(10) + "async function getAllKeyWordsIn() {" + Chr(10) + "allKeyWordsIn = allHTVMinst;" + Chr(10) + "}" + Chr(10) + "function fixSomeBugUGH() {" + Chr(10) + "    var var123Out = " + Chr(34) + Chr(34) + ";" + Chr(10) + Chr(10) + "let storedData = allHTVMinst;" + Chr(10) + "allKeyWordsIn = allHTVMinst;" + Chr(10) + Chr(10) + "    var allKeyWordsIn_OUT = " + Chr(34) + Chr(34) + ";" + Chr(10) + "    var allKeyWordsIn_OUT_TEMP = " + Chr(34) + Chr(34) + ";" + Chr(10) + "    items1 = LoopParseFunc(allKeyWordsIn, " + Chr(34) + Chr(92) + "n" + Chr(34) + ", " + Chr(34) + Chr(92) + "r" + Chr(34) + ")" + Chr(10) + "    for (let A_Index1 = 0; A_Index1 " + Chr(60) + " items1.length + 0; A_Index1++) {" + Chr(10) + "        const A_LoopField1 = items1[A_Index1 - 0];" + Chr(10) + "        if (A_Index1 != 0 && A_Index1 != 1) {" + Chr(10) + "            allKeyWordsIn_OUT += A_LoopField1 + " + Chr(34) + Chr(92) + "n" + Chr(34) + ";" + Chr(10) + "        }" + Chr(10) + "    }" + Chr(10) + "    allKeyWordsIn_OUT = StringTrimRight(allKeyWordsIn_OUT, 1);" + Chr(10) + "    var123Out = allKeyWordsIn_OUT;" + Chr(10) + "    return var123Out;" + Chr(10) + "}" + Chr(10) + "async function getAllKeyWords() {" + Chr(10) + "    await getAllKeyWordsIn();" + Chr(10) + "    await getFunctionNames();" + Chr(10) + "allKeyWordsIn = allHTVMinst;" + Chr(10) + "    var allKeyWordsIn_OUT = " + Chr(34) + Chr(34) + ";" + Chr(10) + "    var allKeyWordsIn_OUT_TEMP = " + Chr(34) + Chr(34) + ";" + Chr(10) + "    items2 = LoopParseFunc(allKeyWordsIn, " + Chr(34) + Chr(92) + "n" + Chr(34) + ", " + Chr(34) + Chr(92) + "r" + Chr(34) + ")" + Chr(10) + "    for (let A_Index2 = 0; A_Index2 " + Chr(60) + " items2.length + 0; A_Index2++) {" + Chr(10) + "        const A_LoopField2 = items2[A_Index2 - 0];" + Chr(10) + "        if (A_Index2 != 0 && A_Index2 != 1) {" + Chr(10) + "            allKeyWordsIn_OUT += A_LoopField2 + " + Chr(34) + Chr(92) + "n" + Chr(34) + ";" + Chr(10) + "        }" + Chr(10) + "    }" + Chr(10) + "    allKeyWordsIn_OUT = StringTrimRight(allKeyWordsIn_OUT, 1);" + Chr(10) + "    allKeyWordsOut = allKeyWordsIn_OUT;" + Chr(10) + "}" + Chr(10) + "let allFunctionNamesString2 = " + Chr(34) + Chr(34) + ";" + Chr(10) + "(async function () {" + Chr(10) + "    await getAllKeyWords();" + Chr(10) + "    //console.log(allKeyWordsOut);" + Chr(10) + "allFunctionNamesString2 = Trim(StrReplace(allFunctionNamesString, Chr(10), " + Chr(34) + "|" + Chr(34) + "));" + Chr(10) + "//print(" + Chr(34) + "=============================" + Chr(34) + ")" + Chr(10) + "//print(allFunctionNamesString2)" + Chr(10) + "//print(" + Chr(34) + "=============================" + Chr(34) + ")" + Chr(10) + "// Get the URL parameter 'id'" + Chr(10) + Chr(10) + "const id = 1" + Chr(10) + "// Check if 'id' is present in the URL" + Chr(10) + Chr(10) + "    // Create the key for localStorage" + Chr(10) + "    const storageKey = " + Chr(96) + "htvm_lang_${id}_allFunctionNamesString" + Chr(96) + ";" + Chr(10) + "    const storageKey2 = " + Chr(96) + "htvm_lang_${id}_allKeyWordsOut" + Chr(96) + ";" + Chr(10) + "    // Save 'allFunctionNamesString2' to localStorage" + Chr(10) + "    localStorage.setItem(storageKey, allFunctionNamesString2);" + Chr(10) + "    localStorage.setItem(storageKey2, allKeyWordsOut);" + Chr(10) + Chr(10) + "})();" + Chr(10) + Chr(10) + "      // Define the custom " + Chr(34) + "ht" + Chr(34) + " language for Ace Editor with AHK rules" + Chr(10) + "      ace.define(" + Chr(34) + "ace/mode/htvm" + Chr(34) + ", [" + Chr(34) + "require" + Chr(34) + ", " + Chr(34) + "exports" + Chr(34) + ", " + Chr(34) + "module" + Chr(34) + ", " + Chr(34) + "ace/lib/oop" + Chr(34) + ", " + Chr(34) + "ace/mode/text" + Chr(34) + ", " + Chr(34) + "ace/mode/text_highlight_rules" + Chr(34) + "], function (require, exports, module) {" + Chr(10) + "    var oop = require(" + Chr(34) + "ace/lib/oop" + Chr(34) + ");" + Chr(10) + "    var TextMode = require(" + Chr(34) + "ace/mode/text" + Chr(34) + ").Mode;" + Chr(10) + "    var TextHighlightRules = require(" + Chr(34) + "ace/mode/text_highlight_rules" + Chr(34) + ").TextHighlightRules;" + Chr(10) + "    var HTVMHighlightRules = function() {" + Chr(10) + "        " + Chr(10) + "        //console.log(new URLSearchParams(window.location.search).get('id'));" + Chr(10) + "let allFunctionNamesString3 = " + Chr(34) + Chr(34) + ";" + Chr(10) + "let allKeyWordsOut3 = " + Chr(34) + Chr(34) + ";" + Chr(10) + Chr(10) + "const id = 1" + Chr(10) + "// Check if 'id' is present in the URL" + Chr(10) + Chr(10) + "    // Create the key for localStorage" + Chr(10) + "    const storageKey = " + Chr(96) + "htvm_lang_${id}_allFunctionNamesString" + Chr(96) + ";" + Chr(10) + "    const storageKey2 = " + Chr(96) + "htvm_lang_${id}_allKeyWordsOut" + Chr(96) + ";" + Chr(10) + "    // Retrieve 'allFunctionNamesString' from localStorage" + Chr(10) + "    allFunctionNamesString3 = localStorage.getItem(storageKey);" + Chr(10) + "    if (localStorage.getItem(" + Chr(34) + "htvm_lang_" + Chr(34) + " + id))" + Chr(10) + "    {" + Chr(10) + "        allKeyWordsOut3 = fixSomeBugUGH();" + Chr(10) + "    }" + Chr(10) + "    else" + Chr(10) + "    {" + Chr(10) + "        allKeyWordsOut3 = localStorage.getItem(storageKey2);    " + Chr(10) + "    }" + Chr(10) + Chr(10) + "var builtInCommands_temp = " + Chr(34) + Chr(34) + ";" + Chr(10) + "var htvmKeywords_temp = " + Chr(34) + Chr(34) + ";" + Chr(10) + "var staticTypes_temp = " + Chr(34) + Chr(34) + ";" + Chr(10) + "var builtInVars_temp = " + Chr(34) + Chr(34) + ";" + Chr(10) + "var operators_temp = " + Chr(34) + Chr(34) + ";" + Chr(10) + "var arrayMethods_temp = " + Chr(34) + Chr(34) + ";" + Chr(10) + "var programmingBlocksAndImport_temp = " + Chr(34) + Chr(34) + ";" + Chr(10) + "var htvm_trueFalseGlobalNull_temp = " + Chr(34) + Chr(34) + ";" + Chr(10) + "var htvm_comment_temp = " + Chr(34) + Chr(34) + ";" + Chr(10) + "var htvm_commentOpen1_temp = " + Chr(34) + Chr(34) + ";" + Chr(10) + "var htvm_commentClose2_temp = " + Chr(34) + Chr(34) + ";" + Chr(10) + "items3 = LoopParseFunc(allKeyWordsOut3, " + Chr(34) + Chr(92) + "n" + Chr(34) + ", " + Chr(34) + Chr(92) + "r" + Chr(34) + ")" + Chr(10) + "for (let A_Index3 = 0; A_Index3 " + Chr(60) + " items3.length + 0; A_Index3++) {" + Chr(10) + "    const A_LoopField3 = items3[A_Index3 - 0];" + Chr(10) + "    if (Trim(A_LoopField3) != " + Chr(34) + Chr(34) + ") {" + Chr(10) + "        if (A_Index3 == 0) {" + Chr(10) + "            items4 = LoopParseFunc(A_LoopField3, " + Chr(34) + "|" + Chr(34) + ")" + Chr(10) + "            for (let A_Index4 = 0; A_Index4 " + Chr(60) + " items4.length + 0; A_Index4++) {" + Chr(10) + "                const A_LoopField4 = items4[A_Index4 - 0];" + Chr(10) + "                items5 = LoopParseFunc(A_LoopField4, " + Chr(34) + "," + Chr(34) + ");" + Chr(10) + "                for (let A_Index5 = 0; A_Index5 " + Chr(60) + " items5.length + 0; A_Index5++) {" + Chr(10) + "                    const A_LoopField5 = items5[A_Index5 - 0];" + Chr(10) + "                    builtInCommands_temp += Trim(A_LoopField5) + " + Chr(34) + "|" + Chr(34) + ";" + Chr(10) + "                }" + Chr(10) + "            }" + Chr(10) + "        }" + Chr(10) + "        if (A_Index3 == 1 || A_Index3 == 2 || A_Index3 == 3 || A_Index3 == 4 || A_Index3 == 5 || A_Index3 == 64 || A_Index3 == 65 || A_Index3 == 66 || A_Index3 == 67 || A_Index3 == 68 || A_Index3 == 69 || A_Index3 == 70 || A_Index3 == 71 || A_Index3 == 72 || A_Index3 == 73 || A_Index3 == 74 || A_Index3 == 75 || A_Index3 == 76 || A_Index3 == 78 || A_Index3 == 79 || A_Index3 == 80 || A_Index3 == 81 || A_Index3 == 93 || A_Index3 == 94 || A_Index3 == 95 || A_Index3 == 96) {" + Chr(10) + "            htvmKeywords_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";" + Chr(10) + "        }" + Chr(10) + "        if (A_Index3 == 77) {" + Chr(10) + "            allFunctionNamesString3 += " + Chr(34) + "|" + Chr(34) + " + Trim(A_LoopField3);" + Chr(10) + "        }" + Chr(10) + "        if (A_Index3 " + Chr(62) + "= 49 && A_Index3 " + Chr(60) + "= 63) {" + Chr(10) + "            staticTypes_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";" + Chr(10) + "        }" + Chr(10) + "        if (A_Index3 " + Chr(62) + "= 88 && A_Index3 " + Chr(60) + "= 92) {" + Chr(10) + "            staticTypes_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";" + Chr(10) + "        }" + Chr(10) + "        if (A_Index3 == 145 || A_Index3 == 146 || A_Index3 == 6) {" + Chr(10) + "            builtInVars_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";" + Chr(10) + "        }" + Chr(10) + "        if (A_Index3 " + Chr(62) + "= 103 && A_Index3 " + Chr(60) + "= 126) {" + Chr(10) + "            operators_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";" + Chr(10) + "        }" + Chr(10) + "        if (A_Index3 " + Chr(62) + "= 140 && A_Index3 " + Chr(60) + "= 141) {" + Chr(10) + "            operators_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";" + Chr(10) + "        }" + Chr(10) + "        if (A_Index3 " + Chr(62) + "= 82 && A_Index3 " + Chr(60) + "= 87) {" + Chr(10) + "            arrayMethods_temp += Trim(StrReplace(A_LoopField3, " + Chr(34) + "." + Chr(34) + ", " + Chr(34) + Chr(34) + ")) + " + Chr(34) + "|" + Chr(34) + ";" + Chr(10) + "        }" + Chr(10) + "        if (A_Index3 " + Chr(62) + "= 7 && A_Index3 " + Chr(60) + "= 43) {" + Chr(10) + "            programmingBlocksAndImport_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";" + Chr(10) + "        }" + Chr(10) + "        if (A_Index3 == 98) {" + Chr(10) + "            htvm_comment_temp = Trim(A_LoopField3);" + Chr(10) + "        }" + Chr(10) + "        if (A_Index3 == 99) {" + Chr(10) + "            htvm_commentOpen1_temp = Trim(A_LoopField3);" + Chr(10) + "        }" + Chr(10) + "        if (A_Index3 == 100) {" + Chr(10) + "            htvm_commentClose2_temp = Trim(A_LoopField3);" + Chr(10) + "        }" + Chr(10) + "        if (A_Index3 == 46 || A_Index3 == 47 || A_Index3 == 48 || A_Index3 == 97) {" + Chr(10) + "            htvm_trueFalseGlobalNull_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";" + Chr(10) + "        }" + Chr(10) + "    }" + Chr(10) + "}" + Chr(10) + "builtInCommands_temp = StringTrimRight(builtInCommands_temp, 1);" + Chr(10) + "htvmKeywords_temp = StringTrimRight(htvmKeywords_temp, 1);" + Chr(10) + "staticTypes_temp = StringTrimRight(staticTypes_temp, 1);" + Chr(10) + "builtInVars_temp = StringTrimRight(builtInVars_temp, 1);" + Chr(10) + "operators_temp = StringTrimRight(operators_temp, 1);" + Chr(10) + "arrayMethods_temp = StringTrimRight(arrayMethods_temp, 1);" + Chr(10) + "programmingBlocksAndImport_temp = StringTrimRight(programmingBlocksAndImport_temp, 1);" + Chr(10) + "htvm_trueFalseGlobalNull_temp = StringTrimRight(htvm_trueFalseGlobalNull_temp, 1);" + Chr(10) + "var htvmKeywords = htvmKeywords_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');" + Chr(10) + "var builtInCommands = builtInCommands_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');" + Chr(10) + "var builtInFunctions = allFunctionNamesString3.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');" + Chr(10) + "var staticTypes = staticTypes_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');" + Chr(10) + "var builtInVars = builtInVars_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');" + Chr(10) + "var arrayMethods = arrayMethods_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');" + Chr(10) + "var programmingBlocksAndImport = programmingBlocksAndImport_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');" + Chr(10) + "var htvm_trueFalseGlobalNull = htvm_trueFalseGlobalNull_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');" + Chr(10) + "var htvm_operators = operators_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');" + Chr(10) + "        " + Chr(10) + "        " + Chr(10) + "        var htvm_comment = htvm_comment_temp;" + Chr(10) + "        // Escape special characters in the comment symbol (just in case)" + Chr(10) + "        var escapedComment = htvm_comment.replace(/[.*+?^${}()|[" + Chr(92) + "]" + Chr(92) + Chr(92) + "]/g, '" + Chr(92) + Chr(92) + "$&');" + Chr(10) + "        var htvm_commentOpen1 = htvm_commentOpen1_temp.replace(/[.*+?^${}()|[" + Chr(92) + "]" + Chr(92) + Chr(92) + "]/g, '" + Chr(92) + Chr(92) + "$&');" + Chr(10) + "        var htvm_commentClose2 = htvm_commentClose2_temp.replace(/[.*+?^${}()|[" + Chr(92) + "]" + Chr(92) + Chr(92) + "]/g, '" + Chr(92) + Chr(92) + "$&');" + Chr(10) + "        this.$rules = {" + Chr(10) + "            start: [" + Chr(10) + "                { token: " + Chr(34) + "comment" + Chr(34) + ", regex: escapedComment + " + Chr(34) + ".*$" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "comment.block" + Chr(34) + ", regex: new RegExp(htvm_commentOpen1), next: " + Chr(34) + "comment_block" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "keyword" + Chr(34) + ", regex: " + Chr(34) + Chr(92) + Chr(92) + "b(?:" + Chr(34) + " + htvmKeywords + " + Chr(34) + ")" + Chr(92) + Chr(92) + "b" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "command" + Chr(34) + ", regex: " + Chr(34) + Chr(92) + Chr(92) + "b(?:" + Chr(34) + " + builtInCommands + " + Chr(34) + ")(?=" + Chr(92) + Chr(92) + ",)" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "functions" + Chr(34) + ", regex: " + Chr(34) + Chr(92) + Chr(92) + "b(?:" + Chr(34) + " + builtInFunctions + " + Chr(34) + ")(?=" + Chr(92) + Chr(92) + "()" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "BuildInFunc" + Chr(34) + ", regex: " + Chr(34) + Chr(92) + Chr(92) + "b(?:" + Chr(34) + " + builtInVars + " + Chr(34) + ")" + Chr(92) + Chr(92) + "b" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "arrayMethods" + Chr(34) + ", regex: " + Chr(34) + Chr(92) + Chr(92) + ".(?:" + Chr(34) + " + arrayMethods + " + Chr(34) + ")" + Chr(92) + Chr(92) + "b" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "static_types" + Chr(34) + ", regex: " + Chr(34) + Chr(92) + Chr(92) + "b(?:" + Chr(34) + " + staticTypes + " + Chr(34) + ")" + Chr(92) + Chr(92) + "b" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "programmingBlocksAndImport" + Chr(34) + ", regex: " + Chr(34) + Chr(92) + Chr(92) + "b(?:" + Chr(34) + " + programmingBlocksAndImport + " + Chr(34) + ")" + Chr(92) + Chr(92) + "b" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "operators" + Chr(34) + ", regex: " + Chr(34) + Chr(92) + Chr(92) + "b(?:" + Chr(34) + " + htvm_operators + " + Chr(34) + ")" + Chr(92) + Chr(92) + "b" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "trueANDfalse" + Chr(34) + ", regex: " + Chr(34) + Chr(92) + Chr(92) + "b(?:" + Chr(34) + " + htvm_trueFalseGlobalNull + " + Chr(34) + ")" + Chr(92) + Chr(92) + "b" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "variables" + Chr(34) + ", regex: " + Chr(34) + Chr(92) + Chr(92) + "b[a-zA-Z_][a-zA-Z0-9_]*" + Chr(92) + Chr(92) + "b" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "constant.numeric" + Chr(34) + ", regex: " + Chr(34) + Chr(92) + Chr(92) + "b[0-9]+" + Chr(92) + Chr(92) + "b" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "braces_Open" + Chr(34) + ", regex: " + Chr(34) + Chr(92) + Chr(92) + "{" + Chr(34) + " }," + Chr(10) + "                { token: " + Chr(34) + "braces_Close" + Chr(34) + ", regex: " + Chr(34) + Chr(92) + Chr(92) + "}" + Chr(34) + " }," + Chr(10) + "              { token: " + Chr(34) + "string" + Chr(34) + ", regex: '" + Chr(34) + ".*?" + Chr(34) + "' }," + Chr(10) + "              // Multi-line comments" + Chr(10) + "              {" + Chr(10) + "                token: " + Chr(34) + "comment.block" + Chr(34) + ", // Token for multi-line comments" + Chr(10) + "               regex: new RegExp(htvm_commentOpen1)," + Chr(10) + "                next: " + Chr(34) + "comment_block" + Chr(34) + "," + Chr(10) + "              }," + Chr(10) + "            ]," + Chr(10) + "            comment_block: [" + Chr(10) + "              {" + Chr(10) + "                token: " + Chr(34) + "comment.block" + Chr(34) + "," + Chr(10) + "                regex: new RegExp(htvm_commentClose2)," + Chr(10) + "                next: " + Chr(34) + "start" + Chr(34) + ", // Go back to the start state" + Chr(10) + "              }," + Chr(10) + "              {" + Chr(10) + "                token: " + Chr(34) + "comment.block" + Chr(34) + "," + Chr(10) + "                regex: /.*/, // Any other content within the comment" + Chr(10) + "              }," + Chr(10) + "            ]," + Chr(10) + "          };" + Chr(10) + "        };" + Chr(10) + " oop.inherits(HTVMHighlightRules, TextHighlightRules);" + Chr(10) + Chr(10) + "        var HTMode = function () {" + Chr(10) + "          this.HighlightRules = HTVMHighlightRules;" + Chr(10) + "        };" + Chr(10) + "        oop.inherits(HTMode, TextMode);" + Chr(10) + Chr(10) + "        exports.Mode = HTMode;" + Chr(10) + "      });" + Chr(10) + Chr(10) + "// Custom renderer for code blocks to use Ace Editor" + Chr(10) + Chr(10) + "// Custom renderer for code blocks to use Ace Editor" + Chr(10) + Chr(10) + "var defaultCodeRenderer = md.renderer.rules.fence;" + Chr(10) + "md.renderer.rules.fence = function(tokens, idx, options, env, self) {" + Chr(10) + "    var token = tokens[idx];" + Chr(10) + "    var language = token.info.trim() || 'text';" + Chr(10) + "    var code = token.content;" + Chr(10) + "    " + Chr(10) + "    // Generate a unique ID for the editor" + Chr(10) + "    var editorId = 'ace-editor-' + idx;" + Chr(10) + "    var codeId = 'code-content-' + idx;" + Chr(10) + "    var buttonId = 'copy-button-' + idx;" + Chr(10) + "    " + Chr(10) + "    // Create container for the ace editor" + Chr(10) + "    var html = '" + Chr(60) + "div class=" + Chr(34) + "ace-editor-container" + Chr(34) + Chr(62) + Chr(92) + "n';" + Chr(10) + "    html += '" + Chr(60) + "div class=" + Chr(34) + "ace-editor-header" + Chr(34) + Chr(62) + "';" + Chr(10) + "    " + Chr(10) + "    // Add copy button before language" + Chr(10) + "    html += '" + Chr(60) + "div style=" + Chr(34) + "display: flex; align-items: center;" + Chr(34) + Chr(62) + "';" + Chr(10) + "    html += '" + Chr(60) + "button id=" + Chr(34) + "' + buttonId + '" + Chr(34) + " class=" + Chr(34) + "copy-button" + Chr(34) + " data-code-id=" + Chr(34) + "' + codeId + '" + Chr(34) + Chr(62) + "';" + Chr(10) + "    html += '" + Chr(60) + "i class=" + Chr(34) + "fas fa-copy" + Chr(34) + Chr(62) + Chr(60) + "/i" + Chr(62) + " Copy" + Chr(60) + "/button" + Chr(62) + "';" + Chr(10) + "    html += '" + Chr(60) + "span class=" + Chr(34) + "ace-editor-language" + Chr(34) + Chr(62) + "' + language + '" + Chr(60) + "/span" + Chr(62) + "';" + Chr(10) + "    html += '" + Chr(60) + "/div" + Chr(62) + "';" + Chr(10) + "    " + Chr(10) + "    html += '" + Chr(60) + "span" + Chr(62) + Chr(60) + "i class=" + Chr(34) + "fas fa-code" + Chr(34) + Chr(62) + Chr(60) + "/i" + Chr(62) + Chr(60) + "/span" + Chr(62) + Chr(60) + "/div" + Chr(62) + Chr(92) + "n';" + Chr(10) + "    " + Chr(10) + "    // Create a pre element to hold the code initially" + Chr(10) + "    html += '" + Chr(60) + "pre id=" + Chr(34) + "' + editorId + '" + Chr(34) + " class=" + Chr(34) + "ace-editor" + Chr(34) + Chr(62) + "' + escapeHtml(code) + '" + Chr(60) + "/pre" + Chr(62) + Chr(92) + "n';" + Chr(10) + "    html += '" + Chr(60) + "div id=" + Chr(34) + "' + codeId + '" + Chr(34) + " style=" + Chr(34) + "display: none;" + Chr(34) + Chr(62) + "' + escapeHtml(code) + '" + Chr(60) + "/div" + Chr(62) + Chr(92) + "n';" + Chr(10) + "    html += '" + Chr(60) + "/div" + Chr(62) + Chr(92) + "n';" + Chr(10) + "    " + Chr(10) + "    // Store the code and language for later use with Ace" + Chr(10) + "    setTimeout(function() {" + Chr(10) + "        initAceEditor(editorId, code, language);" + Chr(10) + "    }, 100);" + Chr(10) + "    " + Chr(10) + "    return html;" + Chr(10) + "};" + Chr(10) + "        " + Chr(10) + "// Function to initialize the Ace editor" + Chr(10) + "function initAceEditor(editorId, code, language) {" + Chr(10) + "    var editor = ace.edit(editorId);" + Chr(10) + "    editor.setTheme(" + Chr(34) + "ace/theme/monokai" + Chr(34) + ");" + Chr(10) + "    " + Chr(10) + "    // Map markdown language names to Ace mode names" + Chr(10) + "    var modeMap = {" + Chr(10) + "        'javascript': 'javascript'," + Chr(10) + "        'js': 'javascript'," + Chr(10) + "        'html': 'html'," + Chr(10) + "        'css': 'css'," + Chr(10) + "        'python': 'python'," + Chr(10) + "        'py': 'python'," + Chr(10) + "        'json': 'json'," + Chr(10) + "        'htvm': 'htvm'" + Chr(10) + "        // Add more mappings as needed" + Chr(10) + "    };" + Chr(10) + "    " + Chr(10) + "    // Set the correct mode based on language" + Chr(10) + "    var mode = modeMap[language.toLowerCase()] || 'text';" + Chr(10) + "    editor.session.setMode(" + Chr(34) + "ace/mode/" + Chr(34) + " + mode);" + Chr(10) + "    " + Chr(10) + "    // Set full code content directly to maintain formatting" + Chr(10) + "    editor.setValue(code);" + Chr(10) + "    editor.clearSelection();" + Chr(10) + "    " + Chr(10) + "    // Make editor read-only" + Chr(10) + "    editor.setReadOnly(true);" + Chr(10) + "    " + Chr(10) + "    // Disable wrap mode to preserve formatting" + Chr(10) + "    editor.getSession().setUseWrapMode(false);" + Chr(10) + "    " + Chr(10) + "    // Additional editor settings" + Chr(10) + "    editor.setShowPrintMargin(false);" + Chr(10) + "    editor.setHighlightActiveLine(true);" + Chr(10) + "    editor.setOptions({" + Chr(10) + "        fontSize: " + Chr(34) + "14px" + Chr(34) + "," + Chr(10) + "    });" + Chr(10) + "    " + Chr(10) + "    // Calculate the exact number of lines" + Chr(10) + "    var lineCount = editor.session.getLength();" + Chr(10) + "    " + Chr(10) + "    // Get the actual line height from the renderer" + Chr(10) + "    var lineHeight = editor.renderer.lineHeight;" + Chr(10) + "    " + Chr(10) + "    // Calculate exact height with a tiny buffer" + Chr(10) + "    var exactHeight = (lineCount * lineHeight);" + Chr(10) + "    " + Chr(10) + "    // Set the editor height to exactly fit the content" + Chr(10) + "    document.getElementById(editorId).style.height = exactHeight + " + Chr(34) + "px" + Chr(34) + ";" + Chr(10) + "    " + Chr(10) + "    // Final resize to update the editor view" + Chr(10) + "    editor.resize();" + Chr(10) + "}" + Chr(10) + Chr(10) + "// Helper function to escape HTML" + Chr(10) + "function escapeHtml(unsafe) {" + Chr(10) + "    return unsafe" + Chr(10) + "        .replace(/&/g, " + Chr(34) + "&amp;" + Chr(34) + ")" + Chr(10) + "        .replace(/" + Chr(60) + "/g, " + Chr(34) + "&lt;" + Chr(34) + ")" + Chr(10) + "        .replace(/" + Chr(62) + "/g, " + Chr(34) + "&gt;" + Chr(34) + ")" + Chr(10) + "        .replace(/" + Chr(34) + "/g, " + Chr(34) + "&quot;" + Chr(34) + ")" + Chr(10) + "        .replace(/'/g, " + Chr(34) + "&#039;" + Chr(34) + ");" + Chr(10) + "}" + Chr(10) + Chr(10) + "        " + Chr(10) + "        // Get the markdown content (from the hidden div)" + Chr(10) + "        var markdownText = document.getElementById(" + Chr(34) + "markdown-content" + Chr(34) + ").innerText;" + Chr(10) + Chr(10) + "        // Convert markdown to HTML" + Chr(10) + "        var htmlContent = md.render(markdownText);" + Chr(10) + Chr(10) + "        // Output the rendered HTML to the markdown-output div" + Chr(10) + "        document.getElementById(" + Chr(34) + "markdown-output" + Chr(34) + ").innerHTML = htmlContent;" + Chr(10) + "        " + Chr(10) + "        // Process all headings to add anchor links" + Chr(10) + "        document.querySelectorAll('#markdown-output h1, #markdown-output h2, #markdown-output h3, #markdown-output h4, #markdown-output h5, #markdown-output h6').forEach(function(heading) {" + Chr(10) + "            // Generate ID if none exists" + Chr(10) + "            if (!heading.id) {" + Chr(10) + "                heading.id = heading.textContent.toLowerCase().replace(/" + Chr(92) + "s+/g, '-').replace(/[^" + Chr(92) + "w-]/g, '');" + Chr(10) + "            }" + Chr(10) + "            " + Chr(10) + "            // Create an anchor element" + Chr(10) + "            var anchor = document.createElement('a');" + Chr(10) + "            anchor.className = 'header-anchor';" + Chr(10) + "            anchor.href = '#' + heading.id;" + Chr(10) + "            anchor.innerHTML = '" + Chr(60) + "i class=" + Chr(34) + "fas fa-link" + Chr(34) + Chr(62) + Chr(60) + "/i" + Chr(62) + "';" + Chr(10) + "            " + Chr(10) + "            // Add click event to update URL without refreshing page" + Chr(10) + "            anchor.addEventListener('click', function(e) {" + Chr(10) + "                e.preventDefault();" + Chr(10) + "                history.pushState(null, null, this.getAttribute('href'));" + Chr(10) + "                // Scroll to the element" + Chr(10) + "                document.getElementById(heading.id).scrollIntoView({" + Chr(10) + "                    behavior: 'smooth'" + Chr(10) + "                });" + Chr(10) + "            });" + Chr(10) + "            " + Chr(10) + "            // Add the anchor to the heading" + Chr(10) + "            heading.appendChild(anchor);" + Chr(10) + "        });" + Chr(10) + "        " + Chr(10) + "        // Process all links in the rendered markdown" + Chr(10) + "        document.querySelectorAll('#markdown-output a:not(.header-anchor)').forEach(function(link) {" + Chr(10) + "            // Check if it's an internal anchor link" + Chr(10) + "            if (link.getAttribute('href').startsWith('#')) {" + Chr(10) + "                // Add click event to update URL without refreshing page" + Chr(10) + "                link.addEventListener('click', function(e) {" + Chr(10) + "                    e.preventDefault();" + Chr(10) + "                    var targetId = this.getAttribute('href').substring(1);" + Chr(10) + "                    history.pushState(null, null, this.getAttribute('href'));" + Chr(10) + "                    // Scroll to the element" + Chr(10) + "                    document.getElementById(targetId).scrollIntoView({" + Chr(10) + "                        behavior: 'smooth'" + Chr(10) + "                    });" + Chr(10) + "                });" + Chr(10) + "            } else {" + Chr(10) + "                // It's an external link" + Chr(10) + "                link.setAttribute('target', '_blank');" + Chr(10) + "                link.setAttribute('rel', 'noopener noreferrer');" + Chr(10) + "                link.classList.add('external-link');" + Chr(10) + "            }" + Chr(10) + "        });" + Chr(10) + "        " + Chr(10) + "        // Set up clipboard functionality for copy buttons after DOM is fully loaded" + Chr(10) + "        document.addEventListener('DOMContentLoaded', function() {" + Chr(10) + "            setupCopyButtons();" + Chr(10) + "        });" + Chr(10) + "        " + Chr(10) + "        // Also set up copy buttons after the markdown is rendered" + Chr(10) + "        setTimeout(function() {" + Chr(10) + "            setupCopyButtons();" + Chr(10) + "        }, 200);" + Chr(10) + "        " + Chr(10) + "        // Function to set up copy buttons" + Chr(10) + "        function setupCopyButtons() {" + Chr(10) + "            document.querySelectorAll('.copy-button').forEach(function(button) {" + Chr(10) + "                button.addEventListener('click', function() {" + Chr(10) + "                    // Store the current button ID" + Chr(10) + "                    var buttonId = this.id;" + Chr(10) + "                    var codeId = this.getAttribute('data-code-id');" + Chr(10) + "                    var codeElement = document.getElementById(codeId);" + Chr(10) + "                    var codeText = codeElement.textContent;" + Chr(10) + "                    " + Chr(10) + "                    // Create a temporary textarea element to copy from" + Chr(10) + "                    var textarea = document.createElement('textarea');" + Chr(10) + "                    textarea.value = codeText;" + Chr(10) + "                    textarea.setAttribute('readonly', '');" + Chr(10) + "                    textarea.style.position = 'absolute';" + Chr(10) + "                    textarea.style.left = '-9999px';" + Chr(10) + "                    document.body.appendChild(textarea);" + Chr(10) + "                    " + Chr(10) + "                    // Select and copy the text" + Chr(10) + "                    textarea.select();" + Chr(10) + "                    document.execCommand('copy');" + Chr(10) + "                    " + Chr(10) + "                    // Remove the temporary element" + Chr(10) + "                    document.body.removeChild(textarea);" + Chr(10) + "                    " + Chr(10) + "                    // Visual feedback - only for this specific button" + Chr(10) + "                    var originalText = this.innerHTML;" + Chr(10) + "                    this.innerHTML = '" + Chr(60) + "i class=" + Chr(34) + "fas fa-check" + Chr(34) + Chr(62) + Chr(60) + "/i" + Chr(62) + " Copied!';" + Chr(10) + "                    this.classList.add('copy-success');" + Chr(10) + "                    " + Chr(10) + "                    // Reset button after 5 seconds" + Chr(10) + "                    var buttonElement = this;" + Chr(10) + "                    setTimeout(function() {" + Chr(10) + "                        // Only reset if it hasn't been changed again" + Chr(10) + "                        if (buttonElement.classList.contains('copy-success')) {" + Chr(10) + "                            buttonElement.innerHTML = originalText;" + Chr(10) + "                            buttonElement.classList.remove('copy-success');" + Chr(10) + "                        }" + Chr(10) + "                    }, 5000);" + Chr(10) + "                });" + Chr(10) + "            });" + Chr(10) + "        }" + Chr(10) + "        " + Chr(10) + "        // Handle initial hash in URL if any" + Chr(10) + "        if (window.location.hash) {" + Chr(10) + "            var targetId = window.location.hash.substring(1);" + Chr(10) + "            var targetElement = document.getElementById(targetId);" + Chr(10) + "            if (targetElement) {" + Chr(10) + "                setTimeout(function() {" + Chr(10) + "                    targetElement.scrollIntoView({" + Chr(10) + "                        behavior: 'smooth'" + Chr(10) + "                    });" + Chr(10) + "                }, 100);" + Chr(10) + "            }" + Chr(10) + "        }" + Chr(10) + Chr(10) + Chr(10) + "        // Apply CSS styles for the editor" + Chr(10) + Chr(10) + "        var css = " + Chr(96) + Chr(10) + "    .ace-monokai .ace_marker-layer .ace_active-line {" + Chr(10) + "      background-color: #103010 !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai {" + Chr(10) + "      background-color: #050505 !important;" + Chr(10) + "      color: #f8f8f2;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_gutter {" + Chr(10) + "      background: #204020 !important;" + Chr(10) + "      color: #cbcdc3 !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_gutter-active-line {" + Chr(10) + "      background-color: transparent !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_entity.ace_name.ace_tag," + Chr(10) + "    .ace-monokai .ace_keyword," + Chr(10) + "    .ace-monokai .ace_meta.ace_tag," + Chr(10) + "    .ace-monokai .ace_storage {" + Chr(10) + "      color: #40a0e0 !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_entity.ace_name.ace_function," + Chr(10) + "    .ace-monokai .ace_entity.ace_other," + Chr(10) + "    .ace-monokai .ace_entity.ace_other.ace_attribute-name," + Chr(10) + "    .ace-monokai .ace_variable {" + Chr(10) + "      color: #ff80df !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_comment {" + Chr(10) + "      color: #40d080 !important;" + Chr(10) + "      font-weight: line-through !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_commentOpen_Close {" + Chr(10) + "      color: #40d080 !important;" + Chr(10) + "      font-weight: line-through !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_variables {" + Chr(10) + "      color: #ffffff !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_functions {" + Chr(10) + "      color: #80dfff !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_keyword {" + Chr(10) + "    color: #8080e0 !important; /* Customize color as needed */" + Chr(10) + "    font-weight: bold !important;" + Chr(10) + "    }" + Chr(10) + "    .ace-monokai .ace_braces_Open {" + Chr(10) + "      color: #FFFFff !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_braces_Close {" + Chr(10) + "      color: #FFFFff !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_arrayMethods {" + Chr(10) + "      color: #FAB820 !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_BuildInFunc {" + Chr(10) + "      color: #ff80df !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_command {" + Chr(10) + "      color: #40a0e0 !important;" + Chr(10) + "      font-weight: bold !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_static_types {" + Chr(10) + "      color: #569cd6 !important;" + Chr(10) + "      font-weight: bold !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_string {" + Chr(10) + "      color: #ffa0a0 !important;" + Chr(10) + "      font-weight: lighter !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_operators {" + Chr(10) + "      color: #00ffff !important;" + Chr(10) + "      font-weight: lighter !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_trueANDfalse {" + Chr(10) + "      color: #00ffff !important;" + Chr(10) + "      font-weight: lighter !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_escape-char {" + Chr(10) + "      color: #ff8000 !important;" + Chr(10) + "      font-weight: bold !important;" + Chr(10) + "    }" + Chr(10) + Chr(10) + "    .ace-monokai .ace_programmingBlocksAndImport {" + Chr(10) + "      color: #F0401C !important;" + Chr(10) + "      font-weight: bold !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    .ace-monokai .ace_punctuation," + Chr(10) + "    .ace-monokai .ace_punctuation.ace _tag {" + Chr(10) + "      color: #ffa0a0 !important;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    *::-webkit-scrollbar {" + Chr(10) + "      width: 1em;" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    *::-webkit-scrollbar-track {" + Chr(10) + "      box-shadow: inset 0 0 6px rgba(0, 0, 0, 0.3);" + Chr(10) + "    }" + Chr(10) + "    " + Chr(10) + "    *::-webkit-scrollbar-thumb {" + Chr(10) + "      background-color: darkgrey;" + Chr(10) + "      outline: 1px solid slategrey;" + Chr(10) + "    }" + Chr(10) + Chr(96) + ";" + Chr(10) + Chr(10) + "        var style = document.createElement(" + Chr(34) + "style" + Chr(34) + ");" + Chr(10) + "        style.type = " + Chr(34) + "text/css" + Chr(34) + ";" + Chr(10) + "        if (style.styleSheet) {" + Chr(10) + "          style.styleSheet.cssText = css;" + Chr(10) + "        } else {" + Chr(10) + "          style.appendChild(document.createTextNode(css));" + Chr(10) + "        }" + Chr(10) + "        document.head.appendChild(style);" + Chr(10) + Chr(10) + "// allHTVMinst" + Chr(10) + Chr(10) + "let allHTVMinstOLD = " + Chr(34) + Chr(34) + Chr(10) + Chr(10) + "function sleep(ms) {" + Chr(10) + "    return new Promise(resolve =" + Chr(62) + " setTimeout(resolve, ms));" + Chr(10) + "}" + Chr(10) + Chr(10) + "async function reloadPage() {" + Chr(10) + "    // Check if key exists in localStorage" + Chr(10) + "    if (localStorage.getItem(" + Chr(34) + "allHTVMinst_FIX_FIX_FIX_FIX_FIX_FIX_FIX_FIX" + Chr(34) + ") !== null) {" + Chr(10) + "        // console.log(" + Chr(34) + "allHTVMinst_FIX_FIX_FIX_FIX_FIX_FIX_FIX_FIX exists in localStorage!" + Chr(34) + ");" + Chr(10) + "        // Retrieve data from localStorage" + Chr(10) + "        allHTVMinstOLD = localStorage.getItem(" + Chr(34) + "allHTVMinst_FIX_FIX_FIX_FIX_FIX_FIX_FIX_FIX" + Chr(34) + ");" + Chr(10) + "        " + Chr(10) + "        if (allHTVMinst != allHTVMinstOLD) {" + Chr(10) + "            localStorage.setItem(" + Chr(34) + "allHTVMinst_FIX_FIX_FIX_FIX_FIX_FIX_FIX_FIX" + Chr(34) + ", allHTVMinst); " + Chr(10) + "            await sleep(900); // Add a 1 second delay before the first reload" + Chr(10) + "            window.location.reload();" + Chr(10) + "        }    " + Chr(10) + "    } else {" + Chr(10) + "        // console.log(" + Chr(34) + "allHTVMinst_FIX_FIX_FIX_FIX_FIX_FIX_FIX_FIX does not exist." + Chr(34) + ");" + Chr(10) + "        // Set data in localStorage" + Chr(10) + "        localStorage.setItem(" + Chr(34) + "allHTVMinst_FIX_FIX_FIX_FIX_FIX_FIX_FIX_FIX" + Chr(34) + ", allHTVMinst); " + Chr(10) + "        await sleep(900); // Add a 1 second delay before the first reload" + Chr(10) + "        window.location.reload();" + Chr(10) + "    }" + Chr(10) + "}" + Chr(10) + "// Call the reloadPage function" + Chr(10) + "reloadPage();" + Chr(10) + Chr(10) + "    " + Chr(60) + "/script" + Chr(62) + Chr(10) + Chr(60) + "/body" + Chr(62) + Chr(10) + Chr(60) + "/html" + Chr(62);
    if (mode == "md") {
        outDocs = outMDup + outMD;
    } else {
        outDocs = htmlUP + Chr(10) + outMDup + outMD + Chr(10) + htmlDOWN;
    }
    return outDocs;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
int main(int argc, char* argv[]) {
    if (HTVM_getLang_HTVM() != "js") {
        DOCS_params = Trim(GetParams());
        if (Trim(StrSplit(DOCS_params, Chr(10), 1)) == "") {
            print("Usage: <instruction_file> [function_name]" + Chr(10) + Chr(10) + "- <instruction_file>: Required. Generates DOCUMENTATION.md and DOCUMENTATION.html." + Chr(10) + "- [function_name]: Optional. If provided, checks whether the function exists and it does not output any files.");
            print("no params Exiting...");
            ExitApp();
        }
        std::vector<std::string> items26 = LoopParseFunc(DOCS_params, "\n", "\r");
        for (size_t A_Index26 = 0; A_Index26 < items26.size() + 0; A_Index26++) {
            std::string A_LoopField26 = items26[A_Index26 - 0];
            if (A_Index26 == 0) {
                print(A_LoopField26);
                DOCS_param1 = Trim(A_LoopField26);
            }
            if (A_Index26 == 1) {
                print(A_LoopField26);
                DOCS_param2 = Trim(A_LoopField26);
            }
        }
        if (!FileExist(DOCS_param1)) {
            print("the file doesn't exist!!!");
            ExitApp();
        }
        if (Trim(DOCS_param2) != "") {
            DOCS_checkIfFuncNameExists = 1;
        }
        instructionFileData = FileRead(Trim(DOCS_param1));
        OUTdocs_HTML = genDocs("html");
        OUTdocs_MD = genDocs("md");
        FileDelete("DOCUMENTATION.md");
        FileAppend(OUTdocs_MD, "DOCUMENTATION.md");
        print("Everything is saved in DOCUMENTATION.md");
        print("========================================");
        FileDelete("DOCUMENTATION.html");
        FileAppend(OUTdocs_HTML, "DOCUMENTATION.html");
        print("Everything is saved in DOCUMENTATION.html");
        print("========================================");
        print("Done!");
    }
    // else add the full user instruction file in instructionFileData variable
    // make sure to reset all vars
    /*
    "" = std::string mode;
    "" = std::string mode;
    "" = std::string mode;
    "" = std::string mode;
    0 = std::string mode;
    "" = std::string mode;
    "" = std::string mode;
    */
    // MAKE SURE to put the instruction file in instructionFileData variable!!!
    // run genDocs("html") and the output will be text that needs to be saved in DOCUMENTATION.html
    // run genDocs("md") and the output will be text that needs to be saved in DOCUMENTATION.md
    return 0;
}