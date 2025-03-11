#include <algorithm>
#include <any>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
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


std::string genDocs(std::string mode) {
    std::string outDocs = "";
    if (Trim(instructionFileData) == "") {
        throw std::runtime_error("instructionFileData is empty");
        return "error: instructionFileData is empty!!!";
    }
    int inFunc = 0;
    std::vector<std::string> funcData_lang;
    std::vector<std::string> funcData_name;
    std::vector<std::string> funcData_desc;
    std::vector<std::string> items1 = LoopParseFunc(instructionFileData, "\n", "\r");
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        if (Trim(A_LoopField1) == "funcEND======================funcEND==============") {
            inFunc = 0;
        }
        if (inFunc == 1) {
            if (SubStr(Trim(A_LoopField1), 1, 6) == "lang: ") {
                HTVM_Append(funcData_lang, Trim(A_LoopField1));
            }
            else if (SubStr(Trim(A_LoopField1), 1, 6) == "name: ") {
                HTVM_Append(funcData_name, Trim(A_LoopField1));
            }
            else if (SubStr(Trim(A_LoopField1), 1, 13) == "description: ") {
                HTVM_Append(funcData_desc, Trim(A_LoopField1));
            }
        }
        if (Trim(A_LoopField1) == "func======================func==============") {
            inFunc = 1;
        }
    }
    std::vector<std::string> allFuncNames = {sortArr(funcData_name)};
    std::string theFuncThatExistsIsCalled = "";
    if (DOCS_checkIfFuncNameExists == 1) {
        int exitedLoopCheckIfFuncNameExists = 0;
        for (int A_Index2 = 0; A_Index2 < HTVM_Size(allFuncNames) + 0; A_Index2++) {
            print(allFuncNames[A_Index2]);
            if (StrLower(DOCS_param2) == StrLower(Trim(StrSplit(allFuncNames[A_Index2], ":", 2)))) {
                theFuncThatExistsIsCalled = Trim(StrSplit(allFuncNames[A_Index2], ":", 2));
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
    for (int A_Index3 = 0; A_Index3 < HTVM_Size(funcData_name) + 0; A_Index3++) {
        //print(funcData_name[A_Index3])
        allFuncNamesTemp = funcData_name[A_Index3];
        tempLang = funcData_lang[A_Index3];
        tempDesc = funcData_desc[A_Index3];
        for (int A_Index4 = 0; A_Index4 < HTVM_Size(allFuncNames) + 0; A_Index4++) {
            if (Trim(allFuncNamesTemp) == Trim(StrSplit(allFuncNames[A_Index4], "|", 1))) {
                if (countChars(allFuncNames[A_Index4], "|") == 0) {
                    allFuncNames[A_Index4] = allFuncNames[A_Index4] + "|" + Trim(tempDesc) + "|" + Trim(tempLang);
                } else {
                    allFuncNames[A_Index4] = allFuncNames[A_Index4] + "|" + Trim(tempLang);
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
    for (int A_Index5 = 0; A_Index5 < HTVM_Size(allFuncNames) + 0; A_Index5++) {
        //print(allFuncNames[A_Index5])
        tempstr = Trim(allFuncNames[A_Index5]);
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
        std::vector<std::string> items6 = LoopParseFunc(tempstr, "|");
        for (size_t A_Index6 = 0; A_Index6 < items6.size() + 0; A_Index6++) {
            std::string A_LoopField6 = items6[A_Index6 - 0];
            if (SubStr(Trim(A_LoopField6), 1, 8) == "lang: js") {
                isLangJs = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 8) == "lang: py") {
                isLangPy = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 9) == "lang: cpp") {
                isLangCpp = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 8) == "lang: go") {
                isLangGo = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 9) == "lang: lua") {
                isLangLua = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 8) == "lang: cs") {
                isLangCs = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 10) == "lang: java") {
                isLangJava = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 12) == "lang: kotlin") {
                isLangKotlin = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 10) == "lang: ruby") {
                isLangRuby = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 9) == "lang: nim") {
                isLangNim = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 9) == "lang: ahk") {
                isLangAhk = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 11) == "lang: swift") {
                isLangSwift = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 10) == "lang: dart") {
                isLangDart = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 8) == "lang: ts") {
                isLangTs = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 12) == "lang: groovy") {
                isLangGroovy = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 6) == "name: ") {
                allFuncsTempAdd += Trim(A_LoopField6) + "|";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 13) == "description: ") {
                allFuncsTempAdd += Trim(A_LoopField6) + "|";
            }
            if (Trim(StrLower(A_LoopField6)) == "description: null") {
                isDescNull = 1;
            }
        }
        if (isDescNull != 1) {
            allFuncsTempAdd += isLangCpp + "|" + isLangPy + "|" + isLangJs + "|" + isLangGo + "|" + isLangLua + "|" + isLangCs + "|" + isLangJava + "|" + isLangKotlin + "|" + isLangRuby + "|" + isLangNim + "|" + isLangAhk + "|" + isLangSwift + "|" + isLangDart + "|" + isLangTs + "|" + isLangGroovy;
            HTVM_Append(allFuncs, allFuncsTempAdd);
        }
    }
    for (int A_Index7 = 0; A_Index7 < 20 + 0; A_Index7++) {
        //print("===========================================")
    }
    std::vector<std::string> categories;
    std::string theCurrentLine = "";
    std::string theCurrentDescCategory = "";
    int once = 0;
    int didWeFindSameCategory = 0;
    for (int A_Index8 = 0; A_Index8 < HTVM_Size(allFuncs) + 0; A_Index8++) {
        //print(allFuncs[A_Index8])
        once++;
        theCurrentLine = Trim(allFuncs[A_Index8]);
        theCurrentDescCategory = Trim(StrSplit(theCurrentLine, "|", 2));
        theCurrentDescCategory = Trim(StrSplit(theCurrentDescCategory, ":", 2));
        theCurrentDescCategory = Trim(StrLower(Trim(StrSplit(theCurrentDescCategory, "~~~", 1))));
        didWeFindSameCategory = 0;
        if (once == 1) {
            HTVM_Append(categories, theCurrentDescCategory + "\n" + theCurrentLine);
        } else {
            for (int A_Index9 = 0; A_Index9 < HTVM_Size(categories) + 0; A_Index9++) {
                if (Trim(StrLower(StrSplit(categories[A_Index9], "\n", 1))) == Trim(theCurrentDescCategory)) {
                    didWeFindSameCategory = 1;
                    categories[A_Index9] = categories[A_Index9] + "\n" + theCurrentLine;
                    break;
                }
            }
            if (didWeFindSameCategory == 0) {
                HTVM_Append(categories, theCurrentDescCategory + "\n" + theCurrentLine);
            }
        }
    }
    for (int A_Index10 = 0; A_Index10 < 20 + 0; A_Index10++) {
        //print("==========================")
    }
    std::string outMDup = "# HTVM Documentation\n\n1. [Introduction](#introduction-to-htvm) \nUnderstand why HTVM is the future of programming.  \n\n2. [OSP (Objectively Simplified Programming) Paradigm](#osp-objectively-simplified-programming-paradigm)  \nLearn about the new paradigm that replaces traditional object-oriented programming.  \n\n3. [Built-in Functions](#built-in-functions)  \nExplore the wide range of built-in functions categorized for ease of use.  \n\n---\n\n## Introduction to HTVM\n\n[Go back](#htvm-documentation) \n\nHTVM is a revolutionary tool designed to replace traditional programming. With HTVM, you can create your own programming language directly [here](https://themaster1127.github.io/HTVM/).\n\nWhat makes HTVM powerful:  \n- **Syntax Customization**:  \n  Here’s what you can change:  \n  - **Keywords**: Modify the keywords used for " + Chr(96) + "if" + Chr(96) + " statements, " + Chr(96) + "while" + Chr(96) + " loops, " + Chr(96) + "for" + Chr(96) + " loops, and more.  \n  - **Operators**: Change the operators like " + Chr(96) + "==" + Chr(96) + ", " + Chr(96) + "!=" + Chr(96) + ", and others to suit your needs.  \n\n- **Inspiration from AutoHotKey**:  \n  Features like " + Chr(96) + "Loop" + Chr(96) + " and " + Chr(96) + "Loop, Parse" + Chr(96) + " (just like in AutoHotKey) are supported and customizable.  \n\n- **Cross-Language Compatibility**:  \n  Languages created with HTVM can be transpiled into **C++**, **Python**, and **JavaScript**.  \n\n- **Static Typing**:  \n  Types are required when converting to C++, but are optional for Python and JavaScript.  \n\n- **Built-in Functions**:  \n  Instead of libraries, HTVM offers built-in functions organized into categories. Scroll to the [Built-in Functions](#built-in-functions) section for more details.  \n\n## Core Features\n\n### Language Configuration\n- **Target Language Selection**\n  - Choose between **C++**, **Python** and **JavaScript** \n  - Specify file extensions for output files\n  - Configure HTML wrapping for JavaScript output\n\n### Syntax Customization\n- **Code Block Style**\n  - Toggle between curly braces " + Chr(96) + "{}" + Chr(96) + " or " + Chr(96) + "end" + Chr(96) + " keywords\n  - Enable/disable Python-style colon syntax\n  - Customize parentheses usage\n  - Control semicolon placement\n\n- **Function Definitions**\n  - Toggle function keywords\n  - Customize async main function for JavaScript\n  - Configure global variable handling\n\n### Type System\n- **Basic Types**\n  - Integer (INT)\n  - String (STR)\n  - Boolean (BOOL)\n  - Float (FLOAT)\n\n- **Extended Integer Types**\n  - INT8\n  - INT16\n  - INT32\n  - INT64\n\n### Control Structures\n- **Conditional Statements**\n  - If/Else/ElseIf\n  - Switch/Case/Default\n  - Custom keywords for all conditional operators\n\n- **Loops**\n  - While loops\n  - For loops with customizable syntax\n  - Infinite loops\n  - Parse loops (AutoHotkey-style)\n  - Custom indexing (0-based or 1-based)\n  - Loop control (break, continue)\n\n### Arrays and Collections\n- **Array Types**\n  - Integer arrays\n  - String arrays\n  - Float arrays\n  - Boolean arrays\n\n- **Array Operations**\n  - Append\n  - Pop\n  - Insert\n  - Remove\n  - Size\n  - IndexOf\n\n### Error Handling\n- **Exception Management**\n  - Try blocks\n  - Catch blocks\n  - Finally blocks\n  - Custom error messages\n  - Throw statements\n\n### JavaScript-Specific Features\n- **Variable Declaration**\n  - var, let, const keywords\n  - Automatic var declaration option\n  - await keyword support\n\n### Operators\n- **Assignment Operators**\n  - Basic assignment\n  - Addition assignment\n  - Subtraction assignment\n  - Multiplication assignment\n  - Division assignment\n  - Concatenation assignment\n\n- **Comparison Operators**\n  - Equal to\n  - Not equal to\n  - Greater than\n  - Less than\n  - Greater than or equal to\n  - Less than or equal to\n\n- **Logical Operators**\n  - AND\n  - OR\n  - NOT\n\n### Comments\n- Single-line comments\n- Multi-line comments\n- Custom comment symbols\n\n### AutoHotkey-Inspired Features\n- **Loop Variables**\n  - A_Index (customizable)\n  - A_LoopField (customizable)\n- **Loop Types**\n  - Parse loops\n  - Count loops\n  - Infinite loops\n\n## Configuration Options\n\n### Syntax Style\n- " + Chr(96) + "useFuncKeyWord" + Chr(96) + ": Toggle function definition keywords\n- " + Chr(96) + "useCurlyBraces" + Chr(96) + ": Toggle curly brace block definitions\n- " + Chr(96) + "useEnd" + Chr(96) + ": Toggle 'end' keyword for block closure\n- " + Chr(96) + "useSemicolon" + Chr(96) + ": Toggle statement-ending semicolons\n- " + Chr(96) + "useParentheses" + Chr(96) + ": Configure parentheses requirements\n- " + Chr(96) + "usePythonicColonSyntax" + Chr(96) + ": Enable Python-style block definitions\n\n### JavaScript Configuration\n- " + Chr(96) + "useInJavaScriptAlwaysUseVar" + Chr(96) + ": Force 'var' declarations\n- " + Chr(96) + "useJavaScriptInAfullHTMLfile" + Chr(96) + ": Enable HTML wrapping\n- " + Chr(96) + "useJavaScriptAmainFuncDef" + Chr(96) + ": Configure async main function\n\n### Loop Configuration\n- " + Chr(96) + "AHKlikeLoopsIndexedAt" + Chr(96) + ": Set loop index starting value\n- " + Chr(96) + "forLoopLang" + Chr(96) + ": Select loop syntax style\n- " + Chr(96) + "keyWordAIndex" + Chr(96) + ": Customize loop index variable name\n- " + Chr(96) + "keyWordALoopField" + Chr(96) + ": Customize loop field variable name\n\n\nHTVM empowers developers to create programming languages tailored to their needs while maintaining compatibility with modern technologies.  \n\n---\n\n## OSP (Objectively Simplified Programming) Paradigm  \n\n[Go back](#htvm-documentation) \n\nOSP (Objectively Simplified Programming) is a paradigm designed to replace OOP since OOP was a mistake. To learn OSP you need to first forget everything about OOP. Forget about concepts like inheritance, polymorphism, encapsulation, private/public keywords and instances.\n\nOSP eliminates the complexities of object-oriented programming.  \n\nHere’s how OSP works:  \n- **Hierarchies**:  \n  - **Alliance**: The top-level structure, defined using the " + Chr(96) + "alliance" + Chr(96) + " keyword. \n  - **Crew**: Sub-levels within an alliance, defined using the " + Chr(96) + "crew" + Chr(96) + " keyword.  \n  - **Method**: Functions defined within alliances or crews using the " + Chr(96) + "method" + Chr(96) + " keyword.  \n  - **Object**: Objects are defined using the " + Chr(96) + "def obj" + Chr(96) + " keyword.  \n\n- **Properties**:  \n  - Defined within objects using the " + Chr(96) + "porp" + Chr(96) + " keyword. You must specify the type, even when converting to Python or JavaScript, for readability.  \n\n\n### **The " + Chr(96) + "this" + Chr(96) + " Keyword**:\n\n- **Definition**:  \n  The " + Chr(96) + "this" + Chr(96) + " keyword is a reference to the current object that invoked a method. In OSP, " + Chr(96) + "this" + Chr(96) + " is **explicitly required to refer to objects**, and **you must always specify the full path** of objects and their properties when using it. Additionally, " + Chr(96) + "this" + Chr(96) + " is **only valid within methods**, as it represents the object calling that specific method.\n\n---\n\n### **Key Rules**:\n1. **Full Path Requirement**:  \n   - In OSP, **you must always specify the full path** of objects and properties when using " + Chr(96) + "this" + Chr(96) + ".  \n   - For example:  \n     - **Correct**: " + Chr(96) + "Movable.Vehicles.Car.fuel" + Chr(96) + "  \n     - **Incorrect**: " + Chr(96) + "fuel" + Chr(96) + "\n\n2. **Only Inside Methods**:  \n   - The " + Chr(96) + "this" + Chr(96) + " keyword can **only** be used inside a method. It refers to the object that invoked the method and provides context for operations on that object.  \n   - Using " + Chr(96) + "this" + Chr(96) + " outside of a method will result in an error, as there is no calling object to reference.\n\n---\n\n### **Explanation Using the Example**:\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm\nmethod void move(this) {\n    if (this == " + Chr(34) + "Movable.Vehicles.Car" + Chr(34) + ") {\n        if (Movable.Vehicles.Car.fuel " + Chr(62) + " 0) {\n            print(" + Chr(34) + "The car is driving." + Chr(34) + ")\n            Movable.Vehicles.Car.fuel = Movable.Vehicles.Car.fuel - 10\n        } else {\n            print(" + Chr(34) + "The car is out of fuel." + Chr(34) + ")\n            Movable.Vehicles.Car.hasFUEL = false\n        }\n    }\n    else if (this == " + Chr(34) + "Movable.Vehicles.Bike" + Chr(34) + ") {\n        if (Movable.Vehicles.Bike.energy " + Chr(62) + " 0) {\n            print(" + Chr(34) + "The bike is pedaling." + Chr(34) + ")\n            Movable.Vehicles.Bike.energy = Movable.Vehicles.Bike.energy - 5\n        } else {\n            print(" + Chr(34) + "The bike is out of energy." + Chr(34) + ")\n            Movable.Vehicles.Bike.hasENERGY = false\n        }\n    }\n}\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n- The " + Chr(96) + "this" + Chr(96) + " keyword in this method represents the specific object calling " + Chr(96) + "move()" + Chr(96) + ".  \n  For instance:\n  - If " + Chr(96) + "this == " + Chr(34) + "Movable.Vehicles.Car" + Chr(34) + "" + Chr(96) + ", the method knows the caller is the **Car object**, and it manipulates " + Chr(96) + "Movable.Vehicles.Car" + Chr(96) + " properties.\n  - Similarly, if " + Chr(96) + "this == " + Chr(34) + "Movable.Vehicles.Bike" + Chr(34) + "" + Chr(96) + ", the method operates on the **Bike object**.\n\n- If you try to use " + Chr(96) + "this" + Chr(96) + " **outside of any method**, it won’t work because " + Chr(96) + "this" + Chr(96) + " has no object context to refer to.  \n  For example:\n  " + Chr(96) + "" + Chr(96) + "" + Chr(96) + " htvm\n  def obj Car {\n      prop int fuel = 100\n      print(this)  // This will cause an error!\n  }\n  " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\n---\n\n### **Why This Restriction Exists**:\n1. **Object Context**:  \n   - The " + Chr(96) + "this" + Chr(96) + " keyword needs a calling object to provide context. Without a method invocation, there’s no object to reference.\n\n2. **Scope Control**:  \n   - Limiting " + Chr(96) + "this" + Chr(96) + " to methods ensures clear and explicit usage, making code easier to understand and debug.\n\n3. **Example: Calling a Method with an Object**:  \n   - To use the " + Chr(96) + "this" + Chr(96) + " keyword, you must **pass an object** when invoking the method:  \n   " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm\n   allianceName.crewName.move(allianceName.crewName.objName)\n   " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n   - Here:\n     - " + Chr(96) + "allianceName" + Chr(96) + " is the main alliance.\n     - " + Chr(96) + "crewName" + Chr(96) + " is the crew containing the method " + Chr(96) + "move" + Chr(96) + ".\n     - " + Chr(96) + "objName" + Chr(96) + " is the specific object being passed to the method. This allows " + Chr(96) + "this" + Chr(96) + " to refer to " + Chr(96) + "objName" + Chr(96) + " inside the method.\n\n---\n\n## **You Don’t Need an Alliance or Crew to Define Objects**\n- In OSP, you can define objects (" + Chr(96) + "def obj" + Chr(96) + ") directly without placing them inside an **alliance** or a **crew**.  \n- This makes it flexible to create standalone objects when you don’t need a larger structure.  \n\n### **Example: Standalone Object Definition**\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm\ndef obj Standalone {\n    prop int value = 10\n    prop str name = " + Chr(34) + "Independent" + Chr(34) + "\n}\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\nto access later just use:\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm\nStandalone.value\nStandalone.name\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\n---\n\n### **Methods in Alliances**\n- Methods can also be defined directly in an **alliance**, without being part of a **crew** and the opposite is well.\n\n### **Example: Method in an Alliance**\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm\nalliance ExampleAlliance {\n    method void greet() {\n        print(" + Chr(34) + "Hello from ExampleAlliance!" + Chr(34) + ")\n    }\n}\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\nto call greet just do:\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm\nExampleAlliance.greet()\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\n## Global Accessibility:  \n  - There are no scopes in OSP. As long as a variable or structure is defined above, it is accessible below. Everything is global, and the full path must always be used.  \n\n## Arrays:  \n  - When using arrays you need to create a temporary array and then copy it to another like this:\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm\ndef obj name {\n    arr str temp\n    prop arr str prop1 = temp\n    prop arr str prop2 = temp\n    prop arr str prop3 = temp\n    prop arr str prop4 = temp\n}\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\n### **Summary**:\n- **Full Paths Always**: Explicit references, such as " + Chr(96) + "Movable.Vehicles.Car.fuel" + Chr(96) + ", are mandatory in OSP. Always use the full path to reference objects. This avoids ambiguity and ensures that each object is uniquely identified within the code.\n- **Only Inside Methods**: The " + Chr(96) + "this" + Chr(96) + " keyword can only be used inside a method to refer to the calling object. It is not valid outside of a method because it requires the context of the method invocation to work correctly.\n- **Promotes Clarity**: These rules ensure consistency, clarity, and unambiguous functionality in OSP. By restricting the use of " + Chr(96) + "this" + Chr(96) + " to methods and requiring full paths, the code remains explicit and easier to follow.\n- **Helps with Debugging**: Since " + Chr(96) + "this" + Chr(96) + " is only valid inside methods, errors related to improper use are easier to detect. Using full paths also helps pinpoint issues more precisely by avoiding confusion with similarly named objects.\n- **Encourages Best Practices**: These guidelines encourage a more structured and organized approach to coding in OSP, fostering a clearer and more maintainable codebase in larger projects.\n\n---\n\n## Note:\n\n### Never use underscores when naming things in OSP. Otherwise, you can use them, but be cautious because underscores can be unstable.\n\n\n#### Example of OSP\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "htvm\nalliance Movable {\n    crew Vehicles {\n        def obj Car {\n            prop int door = 4\n            prop int fuel = 100\n            prop bool hasFUEL = true\n        }\n        def obj Bike {\n            prop bool hasGears = true\n            prop int energy = 100\n            prop bool hasENERGY = true\n        }\n\n        method void move(this) {\n            if (this == " + Chr(34) + "Movable.Vehicles.Car" + Chr(34) + ") {\n                if (Movable.Vehicles.Car.fuel " + Chr(62) + " 0) {\n                    print(" + Chr(34) + "The car is driving." + Chr(34) + ")\n                    Movable.Vehicles.Car.fuel = Movable.Vehicles.Car.fuel - 10\n                } else {\n                    print(" + Chr(34) + "The car is out of fuel." + Chr(34) + ")\n                    Movable.Vehicles.Car.hasFUEL = false\n                }\n            }\n            else if (this == " + Chr(34) + "Movable.Vehicles.Bike" + Chr(34) + ") {\n                if (Movable.Vehicles.Bike.energy " + Chr(62) + " 0) {\n                    print(" + Chr(34) + "The bike is pedaling." + Chr(34) + ")\n                    Movable.Vehicles.Bike.energy = Movable.Vehicles.Bike.energy - 5\n                } else {\n                    print(" + Chr(34) + "The bike is out of energy." + Chr(34) + ")\n                    Movable.Vehicles.Bike.hasENERGY = false\n                }\n            }\n        }\n    }\n    \n    crew settings {\n        def obj GeneralSettings {\n            prop str difficulty = " + Chr(34) + "normal" + Chr(34) + "\n            prop int volume = 50\n            prop str resolution = " + Chr(34) + "1920x1080" + Chr(34) + "\n        }\n        def obj AudioSettings {\n            prop int masterVolume = 70\n            prop int musicVolume = 50\n            prop int sfxVolume = 40\n        }\n        def obj DisplaySettings {\n            prop bool fullscreen = true\n            prop str aspectRatio = " + Chr(34) + "16:9" + Chr(34) + "\n        }\n    }\n    \n    crew actions {\n        // General Settings Methods\n        method void resetGeneralSettings() {\n            Movable.settings.GeneralSettings.difficulty = STR(" + Chr(34) + "normal" + Chr(34) + ")\n            Movable.settings.GeneralSettings.volume = 50\n            Movable.settings.GeneralSettings.resolution = STR(" + Chr(34) + "1920x1080" + Chr(34) + ")\n            print(" + Chr(34) + "General settings reset to default." + Chr(34) + ")\n        }\n        method void printGeneralSettings() {\n            print(" + Chr(34) + "General Settings:" + Chr(34) + ")\n            print(" + Chr(34) + "Difficulty: " + Chr(34) + " + Movable.settings.GeneralSettings.difficulty)\n            print(" + Chr(34) + "Volume: " + Chr(34) + " + STR(Movable.settings.GeneralSettings.volume))\n            print(" + Chr(34) + "Resolution: " + Chr(34) + " + Movable.settings.GeneralSettings.resolution)\n        }\n\n        // Audio Settings Methods\n        method void resetAudioSettings() {\n            Movable.settings.AudioSettings.masterVolume = 70\n            Movable.settings.AudioSettings.musicVolume = 50\n            Movable.settings.AudioSettings.sfxVolume = 40\n            print(" + Chr(34) + "Audio settings reset to default." + Chr(34) + ")\n        }\n        method void printAudioSettings() {\n            print(" + Chr(34) + "Audio Settings:" + Chr(34) + ")\n            print(" + Chr(34) + "Master Volume: " + Chr(34) + " + STR(Movable.settings.AudioSettings.masterVolume))\n            print(" + Chr(34) + "Music Volume: " + Chr(34) + " + STR(Movable.settings.AudioSettings.musicVolume))\n            print(" + Chr(34) + "SFX Volume: " + Chr(34) + " + STR(Movable.settings.AudioSettings.sfxVolume))\n        }\n\n        // Display Settings Methods\n        method void resetDisplaySettings() {\n            Movable.settings.DisplaySettings.fullscreen = true\n            Movable.settings.DisplaySettings.aspectRatio = STR(" + Chr(34) + "16:9" + Chr(34) + ")\n            print(" + Chr(34) + "Display settings reset to default." + Chr(34) + ")\n        }\n        method void printDisplaySettings() {\n            print(" + Chr(34) + "Display Settings:" + Chr(34) + ")\n            print(" + Chr(34) + "Fullscreen: " + Chr(34) + " + STR(Movable.settings.DisplaySettings.fullscreen))\n            print(" + Chr(34) + "Aspect Ratio: " + Chr(34) + " + Movable.settings.DisplaySettings.aspectRatio)\n        }\n    }\n\n    crew array {\n        def obj name {\n            arr str temp\n            prop arr str prop1 = temp\n            prop arr str prop2 = temp\n            prop arr str prop3 = temp\n            prop arr str prop4 = temp\n        }\n    }\n    \n}\n\nmain\n// Test vehicle movement\nwhile (Movable.Vehicles.Car.hasFUEL == true) && (Movable.Vehicles.Bike.hasENERGY = true) {\n    Movable.Vehicles.move(Movable.Vehicles.Car)\n    Movable.Vehicles.move(Movable.Vehicles.Bike)\n    print(" + Chr(34) + "=====================================" + Chr(34) + ")\n}\n\n// Test settings manipulation\nMovable.settings.GeneralSettings.difficulty = STR(" + Chr(34) + "hard" + Chr(34) + ")\nMovable.settings.GeneralSettings.volume = 80\nMovable.settings.GeneralSettings.resolution = STR(" + Chr(34) + "2560x1440" + Chr(34) + ")\nMovable.settings.AudioSettings.masterVolume = 90\nMovable.settings.AudioSettings.musicVolume = 60\nMovable.settings.AudioSettings.sfxVolume = 50\nMovable.settings.DisplaySettings.fullscreen = false\nMovable.settings.DisplaySettings.aspectRatio = STR(" + Chr(34) + "21:9" + Chr(34) + ")\n\nMovable.actions.printGeneralSettings()\nMovable.actions.printAudioSettings()\nMovable.actions.printDisplaySettings()\n\nMovable.actions.resetGeneralSettings()\nMovable.actions.resetAudioSettings()\nMovable.actions.resetDisplaySettings()\n\nMovable.actions.printGeneralSettings()\nMovable.actions.printAudioSettings()\nMovable.actions.printDisplaySettings()\n\n// Test array manipulation\nMovable.array.name.prop1.push(" + Chr(34) + "1text1" + Chr(34) + ")\nMovable.array.name.prop1.push(" + Chr(34) + "1text2" + Chr(34) + ")\nMovable.array.name.prop1.push(" + Chr(34) + "1text3" + Chr(34) + ")\nMovable.array.name.prop2.push(" + Chr(34) + "2text1" + Chr(34) + ")\nMovable.array.name.prop2.push(" + Chr(34) + "2text2" + Chr(34) + ")\nMovable.array.name.prop2.push(" + Chr(34) + "2text3" + Chr(34) + ")\nMovable.array.name.prop3.push(" + Chr(34) + "3text1" + Chr(34) + ")\nMovable.array.name.prop3.push(" + Chr(34) + "3text2" + Chr(34) + ")\nMovable.array.name.prop3.push(" + Chr(34) + "3text3" + Chr(34) + ")\nMovable.array.name.prop4.push(" + Chr(34) + "4text1" + Chr(34) + ")\nMovable.array.name.prop4.push(" + Chr(34) + "4text2" + Chr(34) + ")\nMovable.array.name.prop4.push(" + Chr(34) + "4text3" + Chr(34) + ")\n\n// why this\n// cuz python used len(param) insed of param.len() so it meses up evrything\n// if using OSP objects that have a dot (.) it doset work in python to get the lenght\n// but for a name whit no dots it works\n\narr str arrayTempOnlyGetSize1 = Movable.array.name.prop1\narr str arrayTempOnlyGetSize2 = Movable.array.name.prop2\narr str arrayTempOnlyGetSize3 = Movable.array.name.prop3\narr str arrayTempOnlyGetSize4 = Movable.array.name.prop4\n\n\n\n\nLoop, % arrayTempOnlyGetSize1.size() \n{\nprint(Movable.array.name.prop1[A_Index])\n}\nLoop, % arrayTempOnlyGetSize2.size() {\n    print(Movable.array.name.prop2[A_Index])\n}\nLoop, % arrayTempOnlyGetSize3.size() {\n    print(Movable.array.name.prop3[A_Index])\n}\nLoop, % arrayTempOnlyGetSize4.size() {\n    print(Movable.array.name.prop4[A_Index])\n}\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\nOSP simplifies programming while ensuring compatibility with **C++**, **Python**, and **JavaScript**.  \n\n---\n\n## Built-in Functions  \n\n[Go back](#htvm-documentation) \n\nHTVM includes a variety of built-in functions organized into categories for convenience.\n\n";
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
    for (int A_Index11 = 0; A_Index11 < HTVM_Size(categories) + 0; A_Index11++) {
        //print(categories[A_Index11])
        str1 = Trim(StrTitleCase(Trim(StrSplit(categories[A_Index11], "\n", 1)))) + " Functions";
        // 1. [String Functions](#string-functions)
        str2 = STR(A_Index11 + 1) + ". [" + str1 + "](#" + Trim(StrReplace(StrLower(str1), " ", "-")) + ")";
        outMD += str2 + "\n";
        // [Go back](#built-in-functions)
    }
    outMD += "\n---\n\n";
    std::string categoriesElement = "";
    for (int A_Index12 = 0; A_Index12 < HTVM_Size(categories) + 0; A_Index12++) {
        //print(categories[A_Index12])
        str1 = Trim(StrTitleCase(Trim(StrSplit(categories[A_Index12], "\n", 1)))) + " Functions";
        // ## String Functions
        str2 = "## " + Trim(str1) + "\n\n[Go back](#built-in-functions)\n\n";
        str10 = "[Go back](#" + Trim(StrReplace(StrLower(str1), " ", "-")) + ")";
        outMD += str2;
        // 1. [str1](#str1)
        // 2. [str2](#str2)
        // 3. [str3](#str3)
        categoriesElement = categories[A_Index12];
        std::vector<std::string> items13 = LoopParseFunc(categoriesElement, "\n", "\r");
        for (size_t A_Index13 = 0; A_Index13 < items13.size() + 0; A_Index13++) {
            std::string A_LoopField13 = items13[A_Index13 - 0];
            if (A_Index13 != 0) {
                if (Trim(A_LoopField13) != "") {
                    str1 = Trim(StrSplit(StrSplit(A_LoopField13, "|", 1), ":", 2));
                    str3 = STR(A_Index13) + ". [" + str1 + "](#" + Trim(StrReplace(StrLower(str1), " ", "-")) + ")";
                    outMD += str3 + "\n";
                }
            }
        }
        outMD += "\n---\n\n**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**\n\n**HTVM build-in functions availability.**\n\n| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |\n|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|\n";
        std::vector<std::string> items14 = LoopParseFunc(categoriesElement, "\n", "\r");
        for (size_t A_Index14 = 0; A_Index14 < items14.size() + 0; A_Index14++) {
            std::string A_LoopField14 = items14[A_Index14 - 0];
            if (A_Index14 != 0) {
                if (Trim(A_LoopField14) != "") {
                    str1 = Trim(StrSplit(StrSplit(A_LoopField14, "|", 1), ":", 2));
                    // cpp py js and more
                    str4 = Trim(StrSplit(A_LoopField14, "|", 3));
                    str5 = Trim(StrSplit(A_LoopField14, "|", 4));
                    str6 = Trim(StrSplit(A_LoopField14, "|", 5));
                    str7 = Trim(StrSplit(A_LoopField14, "|", 6));
                    //
                    str11 = Trim(StrSplit(A_LoopField14, "|", 7));
                    str12 = Trim(StrSplit(A_LoopField14, "|", 8));
                    str13 = Trim(StrSplit(A_LoopField14, "|", 9));
                    str14 = Trim(StrSplit(A_LoopField14, "|", 10));
                    str15 = Trim(StrSplit(A_LoopField14, "|", 11));
                    str16 = Trim(StrSplit(A_LoopField14, "|", 12));
                    str17 = Trim(StrSplit(A_LoopField14, "|", 13));
                    str18 = Trim(StrSplit(A_LoopField14, "|", 14));
                    str19 = Trim(StrSplit(A_LoopField14, "|", 15));
                    str20 = Trim(StrSplit(A_LoopField14, "|", 16));
                    str21 = Trim(StrSplit(A_LoopField14, "|", 17));
                    // | str1 | Yes | No | Yes | and more
                    str3 = "| " + str1 + " | " + str4 + " | " + str5 + " | " + str6 + " | " + str7 + " |" + str11 + " |" + str12 + " |" + str13 + " |" + str14 + " |" + str15 + " |" + str16 + " |" + str17 + " |" + str18 + " |" + str19 + " |" + str20 + " |" + str21 + " |";
                    outMD += str3 + "\n";
                }
            }
        }
        outMD += "\n---\n\n";
        std::vector<std::string> items15 = LoopParseFunc(categoriesElement, "\n", "\r");
        for (size_t A_Index15 = 0; A_Index15 < items15.size() + 0; A_Index15++) {
            std::string A_LoopField15 = items15[A_Index15 - 0];
            if (A_Index15 != 0) {
                if (Trim(A_LoopField15) != "") {
                    str1 = Trim(StrSplit(StrSplit(A_LoopField15, "|", 1), ":", 2));
                    str2 = "### " + str1 + "\n\n" + Trim(str10) + "\n\n**HTVM build-in functions availability.**\n\n| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |\n|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|\n";
                    // cpp py js
                    str4 = Trim(StrSplit(A_LoopField15, "|", 3));
                    str5 = Trim(StrSplit(A_LoopField15, "|", 4));
                    str6 = Trim(StrSplit(A_LoopField15, "|", 5));
                    str7 = Trim(StrSplit(A_LoopField15, "|", 6));
                    //
                    str11 = Trim(StrSplit(A_LoopField15, "|", 7));
                    str12 = Trim(StrSplit(A_LoopField15, "|", 8));
                    str13 = Trim(StrSplit(A_LoopField15, "|", 9));
                    str14 = Trim(StrSplit(A_LoopField15, "|", 10));
                    str15 = Trim(StrSplit(A_LoopField15, "|", 11));
                    str16 = Trim(StrSplit(A_LoopField15, "|", 12));
                    str17 = Trim(StrSplit(A_LoopField15, "|", 13));
                    str18 = Trim(StrSplit(A_LoopField15, "|", 14));
                    str19 = Trim(StrSplit(A_LoopField15, "|", 15));
                    str20 = Trim(StrSplit(A_LoopField15, "|", 16));
                    str21 = Trim(StrSplit(A_LoopField15, "|", 17));
                    // | str1 | Yes | No | Yes | and more
                    str3 = "| " + str1 + " | " + str4 + " | " + str5 + " | " + str6 + " | " + str7 + " |" + str11 + " |" + str12 + " |" + str13 + " |" + str14 + " |" + str15 + " |" + str16 + " |" + str17 + " |" + str18 + " |" + str19 + " |" + str20 + " |" + str21 + " |";
                    str8 = "";
                    str9 = Trim(StrSplit(StrSplit(A_LoopField15, "|", 2), "description:", 2));
                    std::vector<std::string> items16 = LoopParseFunc(str9, "~~~");
                    for (size_t A_Index16 = 0; A_Index16 < items16.size() + 0; A_Index16++) {
                        std::string A_LoopField16 = items16[A_Index16 - 0];
                        if (A_Index16 != 0) {
                            if (A_LoopField16 != "") {
                                str7 += A_LoopField16 + "\n";
                            }
                        }
                    }
                    outMD += str2 + str3 + "\n\n" + str8 + "\n---\n\n";
                }
            }
        }
    }
    std::string THEINSTESCEPAED = "";
    std::vector<std::string> items17 = LoopParseFunc(instructionFileData, "\n", "\r");
    for (size_t A_Index17 = 0; A_Index17 < items17.size() + 0; A_Index17++) {
        std::string A_LoopField17 = items17[A_Index17 - 0];
        if (A_Index17 <= 161) {
            THEINSTESCEPAED += escapeStr(Trim(A_LoopField17)) + "\n";
        }
    }
    THEINSTESCEPAED = StringTrimRight(THEINSTESCEPAED, 1);
    std::string htmlUP = "" + Chr(60) + "!DOCTYPE html" + Chr(62) + "\n" + Chr(60) + "html lang=" + Chr(34) + "en" + Chr(34) + "" + Chr(62) + "\n" + Chr(60) + "head" + Chr(62) + "\n    " + Chr(60) + "meta charset=" + Chr(34) + "UTF-8" + Chr(34) + "" + Chr(62) + "\n    " + Chr(60) + "meta name=" + Chr(34) + "viewport" + Chr(34) + " content=" + Chr(34) + "width=device-width, initial-scale=1.0" + Chr(34) + "" + Chr(62) + "\n    " + Chr(60) + "title" + Chr(62) + "GitHub-Style Markdown with Ace Editor" + Chr(60) + "/title" + Chr(62) + "\n\n    " + Chr(60) + "!-- Link to markdown-it library --" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdn.jsdelivr.net/npm/markdown-it@12.0.4/dist/markdown-it.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    \n    " + Chr(60) + "!-- Ace Editor --" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/ace.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/theme-monokai.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-javascript.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-python.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-html.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-css.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-json.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n\n    " + Chr(60) + "!-- Font Awesome for icons --" + Chr(62) + "\n    " + Chr(60) + "link rel=" + Chr(34) + "stylesheet" + Chr(34) + " href=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css" + Chr(34) + "" + Chr(62) + "\n\n    " + Chr(60) + "style" + Chr(62) + "\n        /* Dark Mode Styles */\n        body {\n            background-color: #121212;\n            color: #e0e0e0;\n            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;\n            line-height: 1.6;\n            padding-left: 30px;\n            padding-right: 30px;\n            margin: 0;\n            word-wrap: break-word;\n        }\n\n        h1, h2, h3, h4, h5, h6 {\n            color: #ffffff;\n            position: relative;\n        }\n\n        /* Container for the markdown content */\n        #markdown-output {\n            background-color: #1e1e1e;\n            border-radius: 8px;\n            padding: 30px;\n            margin-top: 20px;\n            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);\n        }\n\n        /* Header Styling */\n        h1 {\n            font-size: 2.5em;\n            border-bottom: 2px solid #444;\n            padding-bottom: 10px;\n        }\n\n        h2 {\n            color: #ffffff;\n            border-bottom: 1px solid #444;\n            padding-bottom: 5px;\n            margin-top: 30px;\n        }\n\n        h3 {\n            color: #81a1c1;\n            margin-top: 20px;\n        }\n\n        /* Links */\n        a {\n            color: #1e90ff;\n            text-decoration: none;\n        }\n\n        a:hover {\n            text-decoration: underline;\n        }\n\n        /* External link icon */\n        a.external-link:after {\n            content: " + Chr(34) + " " + Chr(92) + "2197" + Chr(34) + ";\n            display: inline-block;\n            margin-left: 4px;\n            font-size: 0.8em;\n        }\n        \n        /* Header anchor links that show on hover */\n        .header-anchor {\n            opacity: 0;\n            font-size: 0.8em;\n            margin-left: 8px;\n            color: #666;\n            transition: opacity 0.2s ease-in-out;\n        }\n        \n        h1:hover .header-anchor,\n        h2:hover .header-anchor,\n        h3:hover .header-anchor,\n        h4:hover .header-anchor,\n        h5:hover .header-anchor,\n        h6:hover .header-anchor {\n            opacity: 1;\n            color: #1e90ff;\n        }\n\n        /* Ace Editor Styling */\n        .ace-editor-container {\n            margin: 20px 0;\n            border-radius: 8px;\n            overflow: hidden;\n        }\n        \n        .ace-editor {\n            width: 100%;\n            border-radius: 8px;\n            /* Height will be set dynamically based on content */\n        }\n        \n        .ace-editor-header {\n            background-color: #333;\n            color: #fff;\n            padding: 8px 15px;\n            font-family: monospace;\n            font-size: 0.9em;\n            display: flex;\n            justify-content: space-between;\n            align-items: center;\n            border-top-left-radius: 8px;\n            border-top-right-radius: 8px;\n        }\n        \n        .ace-editor-language {\n            font-weight: bold;\n            color: #82aaff;\n        }\n\n        /* Copy Button Styling */\n        .copy-button {\n            background-color: #2a2a2a;\n            border: none;\n            color: #ccc;\n            border-radius: 4px;\n            padding: 3px 8px;\n            font-size: 12px;\n            cursor: pointer;\n            margin-right: 10px;\n            transition: all 0.2s ease;\n            display: flex;\n            align-items: center;\n        }\n        \n        .copy-button:hover {\n            background-color: #3a3a3a;\n            color: #fff;\n        }\n        \n        .copy-button i {\n            margin-right: 4px;\n        }\n        \n        .copy-success {\n            background-color: #28a745 !important;\n            color: white !important;\n        }\n\n        /* Inline code */\n        p code, li code {\n            background-color: #2b2b2b;\n            padding: 2px 5px;\n            border-radius: 3px;\n            font-family: Consolas, 'Courier New', monospace;\n        }\n\n        /* Table Styling */\n        table {\n            width: 100%;\n            margin: 20px 0;\n            border-collapse: collapse;\n        }\n\n        th, td {\n            padding: 10px;\n            text-align: left;\n            border: 1px solid #444;\n        }\n\n        th {\n            background-color: #333;\n        }\n\n        tr:nth-child(even) {\n            background-color: #2a2a2a;\n        }\n\n        tr:hover {\n            background-color: #444;\n        }\n        \n        /* Fix for internal links */\n        :target {\n            scroll-margin-top: 20px;\n            animation: highlight 2s ease;\n        }\n        \n        @keyframes highlight {\n            from { background-color: #333333; }\n            to { background-color: transparent; }\n        }\n    " + Chr(60) + "/style" + Chr(62) + "\n" + Chr(60) + "/head" + Chr(62) + "\n" + Chr(60) + "body" + Chr(62) + "\n\n    " + Chr(60) + "!-- Markdown content written in normal syntax --" + Chr(62) + "\n" + Chr(60) + "div id=" + Chr(34) + "markdown-content" + Chr(34) + " style=" + Chr(34) + "display:none;" + Chr(34) + "" + Chr(62) + "\n\n";
    std::string htmlDOWN = "\n" + Chr(60) + "/div" + Chr(62) + "\n\n    " + Chr(60) + "br" + Chr(62) + "" + Chr(60) + "br" + Chr(62) + "\n\n    " + Chr(60) + "!-- A div to display the rendered HTML --" + Chr(62) + "\n    " + Chr(60) + "div id=" + Chr(34) + "markdown-output" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/div" + Chr(62) + "\n\n    " + Chr(60) + "script" + Chr(62) + "\n        // Initialize Markdown-it with HTML enabled and proper heading IDs\n        var md = window.markdownit({\n            html: true,\n            linkify: true,\n            typographer: true\n        });\n        \n        function changeFaviconAtTheBeginning(faviconUrl) {\n        // Create a new favicon link element\n        const newFavicon = document.createElement(" + Chr(34) + "link" + Chr(34) + ");\n        newFavicon.rel = " + Chr(34) + "icon" + Chr(34) + ";\n        newFavicon.href = faviconUrl;\n\n        // Get the current favicon element (if exists)\n        const existingFavicon = document.querySelector('link[rel=" + Chr(34) + "icon" + Chr(34) + "]');\n\n        // Replace the current favicon with the new one\n        if (existingFavicon) {\n          // If a favicon exists, replace it\n          document.head.removeChild(existingFavicon); // Remove the existing favicon\n        }\n\n        // Append the new favicon to the head\n        document.head.appendChild(newFavicon);\n      }\n\n      // Call the function with the desired favicon URL\n      changeFaviconAtTheBeginning(" + Chr(34) + "https://i.ibb.co/Jpty1B8/305182938-1a0efe63-726e-49ca-a13c-d0ed627f2ea7.png" + Chr(34) + ");\n\n      function showCustomMessageBox(options, title, text, value, timeout) {\n        return new Promise((resolve) =" + Chr(62) + " {\n          // Define default options for the message box\n          let defaultOptions = {\n            title: title || " + Chr(34) + "" + Chr(34) + ", // Default title is empty\n            text: text || " + Chr(34) + "Press OK to continue." + Chr(34) + ", // Default text if not provided\n            showCancelButton: false, // Default is to not show Cancel button\n            showDenyButton: false, // Default is to not show Deny button\n            confirmButtonText: " + Chr(34) + "OK" + Chr(34) + ", // Default text for OK button\n            focusConfirm: true, // Default focus on OK button\n          };\n\n          let numOriginal = value;\n\n          let num = numOriginal;\n\n          let done1 = 0;\n\n          let done2 = 0;\n\n          let done3 = 0;\n\n          let AIndex = 0;\n\n          for (AIndex = 1; AIndex " + Chr(60) + "= 1; AIndex++) {\n            // this is about if you add always on top in a msgbox it will be removed in js cuz its kinda useless...\n            // becouse if you like adding always on top in ahk in js we dont realy do it so yeah\n            if (num " + Chr(62) + "= 262144) {\n              num = num - 262144;\n              numOriginal = numOriginal - 262144;\n            }\n\n            if (num " + Chr(62) + "= 256 && num " + Chr(60) + " 500) {\n              num = num - 256;\n\n              done3 = 256;\n            }\n\n            if (num " + Chr(62) + "= 512) {\n              num = num - 512;\n\n              done3 = 512;\n            }\n\n            if (num == 0) {\n              done1 = 0;\n\n              break;\n            }\n\n            if (num " + Chr(60) + "= 6) {\n              done1 = num;\n\n              break;\n            }\n\n            if (num " + Chr(62) + "= 64 && num " + Chr(60) + " 64 * 2) {\n              done2 = 64;\n\n              if (num == 64) {\n                done1 = 0;\n\n                break;\n              } else {\n                done1 = num - 64;\n\n                break;\n              }\n            }\n\n            if (num " + Chr(62) + "= 48 && num " + Chr(60) + " 63) {\n              done2 = 48;\n\n              if (num == 48) {\n                done1 = 0;\n\n                break;\n              } else {\n                done1 = num - 48;\n\n                break;\n              }\n            }\n\n            if (num " + Chr(62) + "= 32 && num " + Chr(60) + " 47) {\n              done2 = 32;\n\n              if (num == 32) {\n                done1 = 0;\n\n                break;\n              } else {\n                done1 = num - 32;\n\n                break;\n              }\n            }\n\n            if (num " + Chr(62) + "= 16 && num " + Chr(60) + " 30) {\n              done2 = 16;\n\n              if (num == 16) {\n                done1 = 0;\n\n                break;\n              } else {\n                done1 = num - 16;\n\n                break;\n              }\n            }\n          }\n\n          let doneAdded = done1 + done2 + done3;\n\n          if (doneAdded !== numOriginal) {\n            // displayMessage(" + Chr(34) + "The calc was wrong!" + Chr(34) + ");\n          } else {\n            // displayMessage(" + Chr(34) + "num was: " + Chr(34) + " + numOriginal + " + Chr(34) + "" + Chr(92) + "ndone1: " + Chr(34) + " + done1 + " + Chr(34) + "" + Chr(92) + "ndone2: " + Chr(34) + " + done2 + " + Chr(34) + "" + Chr(92) + "ndone3: " + Chr(34) + " + done3);\n          }\n\n          // Parse the value to determine the options for the message box\n          if (done1 === 1) defaultOptions.showCancelButton = true; // OK/Cancel in ahk but here it will show Ok/Cancel wiat its same haha\n\n          // not gonna work if you can make it work i will appreciate\n          //   if (done1 === 2) {\n          //     defaultOptions.showCancelButton = true; // Abort/Retry/Ignore\n          //     defaultOptions.showDenyButton = true;\n          //   }\n          if (done1 === 3) {\n            defaultOptions.showCancelButton = true; // Yes/No/Cancel in ahk but here it will show Ok/No/Cancel\n            defaultOptions.showDenyButton = true;\n          }\n          if (done1 === 4) {\n            // defaultOptions.showCancelButton = true;\n            defaultOptions.showDenyButton = true; // Yes/No in ahk but here it will show Ok/No\n          }\n          if (done1 === 5) {\n            defaultOptions.showCancelButton = true; // Retry/Cancel in ahk but here it will show Ok/Cancel tip you can write in the Msgbox press ok to retry\n          }\n          // not gonna work if you can make it work i will appreciate\n          //   if (done1 === 6) {\n          //     defaultOptions.showCancelButton = true; // Cancel/Try Again/Continue\n          //     defaultOptions.showDenyButton = true;\n          //   }\n\n          if (done2 === 16) defaultOptions.icon = " + Chr(34) + "error" + Chr(34) + "; // Icon Hand (stop/error)\n          if (done2 === 32) defaultOptions.icon = " + Chr(34) + "question" + Chr(34) + "; // Icon Question\n          if (done2 === 48) defaultOptions.icon = " + Chr(34) + "warning" + Chr(34) + "; // Icon Exclamation\n          if (done2 === 64) defaultOptions.icon = " + Chr(34) + "info" + Chr(34) + "; // Icon Asterisk (info)\n\n          if (done3 === 256) defaultOptions.focusDeny = true; // Makes the 3rd button the default\n          if (done3 === 512) defaultOptions.focusCancel = true; // Makes the 2nd button the default\n\n          // Set timeout if provided\n          if (timeout) {\n            defaultOptions.timer = timeout * 1000; // Convert timeout to milliseconds\n          }\n\n          // Merge default options with provided options\n          Object.assign(defaultOptions, options);\n\n          // Display the message box with the constructed options\n          Swal.fire(defaultOptions).then((result) =" + Chr(62) + " {\n            if (result.isConfirmed) {\n              resolve(" + Chr(34) + "OK" + Chr(34) + ");\n            } else if (result.isDenied) {\n              resolve(" + Chr(34) + "No" + Chr(34) + ");\n            } else {\n              resolve(" + Chr(34) + "Cancel" + Chr(34) + ");\n            }\n          });\n        });\n      }\n\n      var lastKeyPressed = " + Chr(34) + "" + Chr(34) + ";\n\n      function trackLastKeyPressed() {\n        document.addEventListener(" + Chr(34) + "keydown" + Chr(34) + ", function (event) {\n          lastKeyPressed = event.key;\n          // console.log(lastKeyPressed);\n        });\n      }\n\n      function getLastKeyPressed() {\n        return lastKeyPressed;\n      }\n\n      // Call the trackLastKeyPressed function to start tracking key presses\n      trackLastKeyPressed();\n\n      let lastInputTime = Date.now(); // Initialize with current timestamp\n      let startTimestamp = Date.now(); // Initialize with current timestamp\n\n      // Event listener to track user activity\n      function resetIdleTimer() {\n        lastInputTime = Date.now(); // Update last input time\n      }\n\n      document.addEventListener(" + Chr(34) + "mousemove" + Chr(34) + ", resetIdleTimer);\n      document.addEventListener(" + Chr(34) + "keypress" + Chr(34) + ", resetIdleTimer);\n\n      // Function to calculate time since last input event\n      function A_TimeIdle() {\n        return Date.now() - lastInputTime; // Calculate time difference\n      }\n\n      function LoopParseFunc(varString, delimiter1=" + Chr(34) + "" + Chr(34) + ", delimiter2=" + Chr(34) + "" + Chr(34) + ") {\n    let items;\n    if (!delimiter1 && !delimiter2) {\n        // If no delimiters are provided, return an array of characters\n        items = [...varString];\n    } else {\n        // Construct the regular expression pattern for splitting the string\n        let pattern = new RegExp('[' + delimiter1.replace(/[.*+?^${}()|[" + Chr(92) + "]" + Chr(92) + "" + Chr(92) + "]/g, '" + Chr(92) + "" + Chr(92) + "$&') + delimiter2.replace(/[.*+?^${}()|[" + Chr(92) + "]" + Chr(92) + "" + Chr(92) + "]/g, '" + Chr(92) + "" + Chr(92) + "$&') + ']+');\n        // Split the string using the constructed pattern\n        items = varString.split(pattern);\n    }\n    return items;\n}\n\nfunction print(value) {\n    console.log(value)\n}\n\n// Convert value to string\nfunction STR(value) {\n    if (value === null || value === undefined) {\n        return " + Chr(34) + "" + Chr(34) + "; // Return a string for null or undefined\n    } else if (typeof value === 'number') {\n        return value.toString();\n    } else if (typeof value === 'boolean') {\n        return value ? " + Chr(34) + "1" + Chr(34) + " : " + Chr(34) + "0" + Chr(34) + ";\n    } else if (typeof value === 'string') {\n        return value; // Return the string as is\n    } else {\n        // Handle any unexpected types gracefully\n        return String(value); // Convert any other type to a string\n    }\n}\n\nfunction Chr(number) {\n    // Return the character corresponding to the Unicode code point, or an empty string if out of range\n    return (number " + Chr(62) + "= 0 && number " + Chr(60) + "= 0x10FFFF) ? String.fromCharCode(number) : " + Chr(34) + "" + Chr(34) + ";\n}\n\nfunction SubStr(str, startPos, length = -1) {\n    // If str is null or undefined, return an empty string\n    if (str === null || str === undefined) {\n        return " + Chr(34) + "" + Chr(34) + ";\n    }\n    let strLen = str.length;\n    \n    // Handle negative starting positions (C++ style)\n    if (startPos " + Chr(60) + " 1) {\n        startPos = strLen + startPos;\n        if (startPos " + Chr(60) + " 0) startPos = 0;\n    } else {\n        startPos -= 1; // Convert to 0-based index (C++ style)\n    }\n    // Handle length (C++ style)\n    if (length " + Chr(60) + " 0) {\n        length = strLen - startPos; // Length to end of string\n    } else if (startPos + length " + Chr(62) + " strLen) {\n        length = strLen - startPos; // Adjust length to fit within the string\n    }\n    // Extract the substring\n    return str.substr(startPos, length);\n}\n\nfunction Trim(inputString) {\n    return inputString ? inputString.trim() : " + Chr(34) + "" + Chr(34) + ";\n}\n\nfunction StrReplace(originalString, find, replaceWith) {\n    return originalString.split(find).join(replaceWith);\n}\n\nfunction StrLower(string) {\n    return string.toLowerCase();\n}\n\nfunction StrSplit(inputStr, delimiter, num) {\n    const parts = inputStr.split(delimiter);\n    return (num " + Chr(62) + " 0 && num " + Chr(60) + "= parts.length) ? parts[num - 1] : " + Chr(34) + "" + Chr(34) + ";\n}\n\n// Function to sort and remove duplicates\nfunction sortArr(inputArray) {\n    // Remove duplicates using Set and sort the array\n    return [...new Set(inputArray)].sort();\n}\n\nfunction countChars(string, theChar) {\n    let count = 0;\n    for (let char of string) {\n        if (char === theChar) {\n            count++;\n        }\n    }\n    return count;\n}\n\n\n//\n\nfunction StrTitleCase(inputString) {\n    return inputString.split(' ')  // Split the string into words\n        .map(word =" + Chr(62) + " {\n            if (word) {  // Avoid empty words (multiple spaces)\n                return word.charAt(0).toUpperCase() + word.slice(1).toLowerCase();  // Capitalize first letter\n            }\n            return word;  // If it's an empty string (spaces), keep it as is\n        })\n        .join(' ');  // Join the words back together with spaces\n}\n\nfunction HTVM_getLang_HTVM() {\n    return " + Chr(34) + "js" + Chr(34) + ";\n}\n\nfunction HTVM_Append(arr, value) {\n    arr.push(value);\n}\n\nfunction HTVM_Size(arr) {\n    return arr.length;\n}\n\n      // Function to calculate tick count in milliseconds\n      function A_TickCount() {\n        return Date.now() - startTimestamp;\n      }\n\n      function GuiControl(action, id, param1, param2, param3, param4) {\n        const element = document.getElementById(id);\n        if (element) {\n          // Handle DOM elements\n          if (action === " + Chr(34) + "move" + Chr(34) + ") {\n            // Set position and size\n            element.style.left = param1 + " + Chr(34) + "px" + Chr(34) + ";\n            element.style.top = param2 + " + Chr(34) + "px" + Chr(34) + ";\n            element.style.width = param3 + " + Chr(34) + "px" + Chr(34) + ";\n            element.style.height = param4 + " + Chr(34) + "px" + Chr(34) + ";\n          } else if (action === " + Chr(34) + "focus" + Chr(34) + " && (element instanceof HTMLInputElement || element instanceof HTMLElement)) {\n            // Focus on the element\n            element.focus();\n          } else if (action === " + Chr(34) + "text" + Chr(34) + ") {\n            // Set new text content\n            element.textContent = param1;\n          } else if (action === " + Chr(34) + "hide" + Chr(34) + ") {\n            // Hide the element\n            element.style.display = " + Chr(34) + "none" + Chr(34) + ";\n          } else if (action === " + Chr(34) + "show" + Chr(34) + ") {\n            // Show the element\n            element.style.display = " + Chr(34) + "" + Chr(34) + ";\n          } else if (action === " + Chr(34) + "enable" + Chr(34) + ") {\n            // Enable the element\n            element.disabled = false;\n          } else if (action === " + Chr(34) + "disable" + Chr(34) + ") {\n            // Disable the element\n            element.disabled = true;\n          } else if (action === " + Chr(34) + "font" + Chr(34) + ") {\n            // Set font size\n            element.style.fontSize = param1 + " + Chr(34) + "px" + Chr(34) + ";\n          } else if (action === " + Chr(34) + "destroy" + Chr(34) + ") {\n            // Remove the element from the DOM\n            element.parentNode.removeChild(element);\n          } else if (action === " + Chr(34) + "color" + Chr(34) + ") {\n            // Set color\n            element.style.color = param1;\n          } else if (action === " + Chr(34) + "picture" + Chr(34) + ") {\n            // Change the image source\n            if (element instanceof HTMLImageElement) {\n              element.src = param1;\n            } else {\n              console.error(" + Chr(34) + "Element is not an " + Chr(60) + "img" + Chr(62) + " tag, cannot change picture." + Chr(34) + ");\n            }\n          } else if (action === " + Chr(34) + "textide" + Chr(34) + ") {\n            // Set value for Ace editor\n            var editor = ace.edit(id); // Access the Ace editor instance using its ID\n            if (editor && param1) {\n              editor.session.setValue(param1);\n            } else {\n              console.error(" + Chr(34) + "Element is not an Ace editor or parameter is missing." + Chr(34) + ");\n            }\n          }\n        } else {\n          // Handle canvas or non-existing element\n          if (action === " + Chr(34) + "move" + Chr(34) + ") {\n            // Update position and size of the rectangle\n            updateRectangle(id, param1, param2, param3, param4);\n            redrawCanvas(); // Redraw the canvas with updated rectangles\n          } else if (action === " + Chr(34) + "color" + Chr(34) + ") {\n            // Update color of the rectangle\n            updateRectangleColor(id, param1);\n            redrawCanvas(); // Redraw the canvas with updated rectangles\n          }\n        }\n      }\n\n      function BuildInVars(varName) {\n        switch (varName) {\n          case " + Chr(34) + "A_ScreenWidth" + Chr(34) + ":\n            // Return screen width\n            return window.innerWidth;\n          case " + Chr(34) + "A_LastKey" + Chr(34) + ":\n            // Return screen width\n            return getLastKeyPressed();\n          case " + Chr(34) + "A_ScreenHeight" + Chr(34) + ":\n            // Return screen height\n            return window.innerHeight;\n          case " + Chr(34) + "A_TimeIdle" + Chr(34) + ":\n            // Return time idle\n            return A_TimeIdle();\n          case " + Chr(34) + "A_TickCount" + Chr(34) + ":\n            // Return tick count in milliseconds\n            return A_TickCount();\n          case " + Chr(34) + "A_Now" + Chr(34) + ":\n            // Return current local timestamp\n            return new Date().toLocaleString();\n          case " + Chr(34) + "A_YYYY" + Chr(34) + ":\n            // Return current year\n            return new Date().getFullYear();\n          case " + Chr(34) + "A_MM" + Chr(34) + ":\n            // Return current month\n            return (new Date().getMonth() + 1).toString().padStart(2, " + Chr(34) + "0" + Chr(34) + ");\n          case " + Chr(34) + "A_DD" + Chr(34) + ":\n            // Return current day\n            return new Date().getDate().toString().padStart(2, " + Chr(34) + "0" + Chr(34) + ");\n          case " + Chr(34) + "A_MMMM" + Chr(34) + ":\n            // Return full month name\n            return new Date().toLocaleDateString(undefined, { month: " + Chr(34) + "long" + Chr(34) + " });\n          case " + Chr(34) + "A_MMM" + Chr(34) + ":\n            // Return short month name\n            return new Date().toLocaleDateString(undefined, { month: " + Chr(34) + "short" + Chr(34) + " });\n          case " + Chr(34) + "A_DDDD" + Chr(34) + ":\n            // Return full day name\n            return new Date().toLocaleDateString(undefined, { weekday: " + Chr(34) + "long" + Chr(34) + " });\n          case " + Chr(34) + "A_DDD" + Chr(34) + ":\n            // Return short day name\n            return new Date().toLocaleDateString(undefined, { weekday: " + Chr(34) + "short" + Chr(34) + " });\n          case " + Chr(34) + "A_Hour" + Chr(34) + ":\n            // Return current hour\n            return new Date().getHours().toString().padStart(2, " + Chr(34) + "0" + Chr(34) + ");\n          case " + Chr(34) + "A_Min" + Chr(34) + ":\n            // Return current minute\n            return new Date().getMinutes().toString().padStart(2, " + Chr(34) + "0" + Chr(34) + ");\n          case " + Chr(34) + "A_Sec" + Chr(34) + ":\n            // Return current second\n            return new Date().getSeconds().toString().padStart(2, " + Chr(34) + "0" + Chr(34) + ");\n          case " + Chr(34) + "A_Space" + Chr(34) + ":\n            // Return space character\n            return " + Chr(34) + " " + Chr(34) + ";\n          case " + Chr(34) + "A_Tab" + Chr(34) + ":\n            // Return tab character\n            return " + Chr(34) + "" + Chr(92) + "t" + Chr(34) + ";\n\n          default:\n            // Handle unknown variable names\n            return null;\n        }\n      }\n      function StrReplace(originalString, find, replaceWith) {\n    return originalString.split(find).join(replaceWith);\n}\n\nfunction StringTrimRight(input, numChars) {\n    return (numChars " + Chr(60) + "= input.length) ? input.substring(0, input.length - numChars) : input;\n}\n\n//\n\n      function Chr(number) {\n        // Check if the number is null\n        if (number === null) {\n          // Return an empty string\n          return " + Chr(34) + "" + Chr(34) + ";\n        }\n\n        // Check if the number is within the valid range\n        if (number " + Chr(62) + "= 0 && number " + Chr(60) + "= 0x10ffff) {\n          // Convert the number to a character using String.fromCharCode\n          return String.fromCharCode(number);\n        } else {\n          // Return an empty string for invalid numbers\n          return " + Chr(34) + "" + Chr(34) + ";\n        }\n      }\n\nlet allHTVMinst = " + Chr(96) + THEINSTESCEPAED + Chr(96) + ";\n\n\nlet allKeyWordsIn = " + Chr(34) + "" + Chr(34) + "; // Global variable to store the result\nlet allKeyWordsOut = " + Chr(34) + "" + Chr(34) + ";\nlet allFunctionNamesString = " + Chr(34) + "" + Chr(34) + "; // Global string to store function names\nasync function getFunctionNames() {\n    const url = 'https://raw.githubusercontent.com/TheMaster1127/HTVM/refs/heads/main/HTVM-instructions.txt';\n    \n    try {\n        const response = await fetch(url);\n        if (!response.ok) {\n            throw new Error(" + Chr(96) + "Network response was not ok: ${response.statusText}" + Chr(96) + ");\n        }\n        const text = await response.text();\n        \n        // Split text by line and get lines starting from line 162\n        const lines = text.split('" + Chr(92) + "n').slice(162); // Line 162 starts at index 161\n        \n        // Extract function names that start with " + Chr(34) + "name: " + Chr(34) + "\n        const functionNames = lines\n            .map(line =" + Chr(62) + " line.trim()) // Trim each line\n            .filter(line =" + Chr(62) + " line.startsWith(" + Chr(34) + "name: " + Chr(34) + ")) // Only lines that start with " + Chr(34) + "name: " + Chr(34) + "\n            .map(line =" + Chr(62) + " line.replace(" + Chr(34) + "name: " + Chr(34) + ", " + Chr(34) + "" + Chr(34) + ").trim()) // Get function name (remove " + Chr(34) + "name: " + Chr(34) + " part)\n            .filter((value, index, self) =" + Chr(62) + " self.indexOf(value) === index); // Remove duplicates\n        \n        // Save the function names in the global variable\n        allFunctionNamesString = functionNames.join('" + Chr(92) + "n');\n        \n    } catch (error) {\n        console.error('Error fetching the text file:', error);\n    }\n}\n// Function to fetch the first 161 lines from a remote text file\nasync function fetchFirst161Lines(url) {\n    try {\n        const response = await fetch(url);\n        if (!response.ok) {\n            throw new Error(" + Chr(96) + "Network response was not ok: ${response.statusText}" + Chr(96) + ");\n        }\n        const text = await response.text();\n        return text.split('" + Chr(92) + "n').slice(0, 162).join('" + Chr(92) + "n');\n    } catch (error) {\n        console.error('Error fetching the text file:', error);\n        return null;\n    }\n}\n// Main function to handle localStorage and data retrieval\nasync function getAllKeyWordsIn() {\nallKeyWordsIn = allHTVMinst;\n}\nfunction fixSomeBugUGH() {\n    var var123Out = " + Chr(34) + "" + Chr(34) + ";\n\nlet storedData = allHTVMinst;\nallKeyWordsIn = allHTVMinst;\n\n    var allKeyWordsIn_OUT = " + Chr(34) + "" + Chr(34) + ";\n    var allKeyWordsIn_OUT_TEMP = " + Chr(34) + "" + Chr(34) + ";\n    items1 = LoopParseFunc(allKeyWordsIn, " + Chr(34) + "" + Chr(92) + "n" + Chr(34) + ", " + Chr(34) + "" + Chr(92) + "r" + Chr(34) + ")\n    for (let A_Index1 = 0; A_Index1 " + Chr(60) + " items1.length + 0; A_Index1++) {\n        const A_LoopField1 = items1[A_Index1 - 0];\n        if (A_Index1 != 0 && A_Index1 != 1) {\n            allKeyWordsIn_OUT += A_LoopField1 + " + Chr(34) + "" + Chr(92) + "n" + Chr(34) + ";\n        }\n    }\n    allKeyWordsIn_OUT = StringTrimRight(allKeyWordsIn_OUT, 1);\n    var123Out = allKeyWordsIn_OUT;\n    return var123Out;\n}\nasync function getAllKeyWords() {\n    await getAllKeyWordsIn();\n    await getFunctionNames();\nallKeyWordsIn = allHTVMinst;\n    var allKeyWordsIn_OUT = " + Chr(34) + "" + Chr(34) + ";\n    var allKeyWordsIn_OUT_TEMP = " + Chr(34) + "" + Chr(34) + ";\n    items2 = LoopParseFunc(allKeyWordsIn, " + Chr(34) + "" + Chr(92) + "n" + Chr(34) + ", " + Chr(34) + "" + Chr(92) + "r" + Chr(34) + ")\n    for (let A_Index2 = 0; A_Index2 " + Chr(60) + " items2.length + 0; A_Index2++) {\n        const A_LoopField2 = items2[A_Index2 - 0];\n        if (A_Index2 != 0 && A_Index2 != 1) {\n            allKeyWordsIn_OUT += A_LoopField2 + " + Chr(34) + "" + Chr(92) + "n" + Chr(34) + ";\n        }\n    }\n    allKeyWordsIn_OUT = StringTrimRight(allKeyWordsIn_OUT, 1);\n    allKeyWordsOut = allKeyWordsIn_OUT;\n}\nlet allFunctionNamesString2 = " + Chr(34) + "" + Chr(34) + ";\n(async function () {\n    await getAllKeyWords();\n    //console.log(allKeyWordsOut);\nallFunctionNamesString2 = Trim(StrReplace(allFunctionNamesString, Chr(10), " + Chr(34) + "|" + Chr(34) + "));\n//print(" + Chr(34) + "=============================" + Chr(34) + ")\n//print(allFunctionNamesString2)\n//print(" + Chr(34) + "=============================" + Chr(34) + ")\n// Get the URL parameter 'id'\n\nconst id = 1\n// Check if 'id' is present in the URL\n\n    // Create the key for localStorage\n    const storageKey = " + Chr(96) + "htvm_lang_${id}_allFunctionNamesString" + Chr(96) + ";\n    const storageKey2 = " + Chr(96) + "htvm_lang_${id}_allKeyWordsOut" + Chr(96) + ";\n    // Save 'allFunctionNamesString2' to localStorage\n    localStorage.setItem(storageKey, allFunctionNamesString2);\n    localStorage.setItem(storageKey2, allKeyWordsOut);\n\n})();\n\n      // Define the custom " + Chr(34) + "ht" + Chr(34) + " language for Ace Editor with AHK rules\n      ace.define(" + Chr(34) + "ace/mode/htvm" + Chr(34) + ", [" + Chr(34) + "require" + Chr(34) + ", " + Chr(34) + "exports" + Chr(34) + ", " + Chr(34) + "module" + Chr(34) + ", " + Chr(34) + "ace/lib/oop" + Chr(34) + ", " + Chr(34) + "ace/mode/text" + Chr(34) + ", " + Chr(34) + "ace/mode/text_highlight_rules" + Chr(34) + "], function (require, exports, module) {\n    var oop = require(" + Chr(34) + "ace/lib/oop" + Chr(34) + ");\n    var TextMode = require(" + Chr(34) + "ace/mode/text" + Chr(34) + ").Mode;\n    var TextHighlightRules = require(" + Chr(34) + "ace/mode/text_highlight_rules" + Chr(34) + ").TextHighlightRules;\n    var HTVMHighlightRules = function() {\n        \n        //console.log(new URLSearchParams(window.location.search).get('id'));\nlet allFunctionNamesString3 = " + Chr(34) + "" + Chr(34) + ";\nlet allKeyWordsOut3 = " + Chr(34) + "" + Chr(34) + ";\n\nconst id = 1\n// Check if 'id' is present in the URL\n\n    // Create the key for localStorage\n    const storageKey = " + Chr(96) + "htvm_lang_${id}_allFunctionNamesString" + Chr(96) + ";\n    const storageKey2 = " + Chr(96) + "htvm_lang_${id}_allKeyWordsOut" + Chr(96) + ";\n    // Retrieve 'allFunctionNamesString' from localStorage\n    allFunctionNamesString3 = localStorage.getItem(storageKey);\n    if (localStorage.getItem(" + Chr(34) + "htvm_lang_" + Chr(34) + " + id))\n    {\n        allKeyWordsOut3 = fixSomeBugUGH();\n    }\n    else\n    {\n        allKeyWordsOut3 = localStorage.getItem(storageKey2);    \n    }\n\nvar builtInCommands_temp = " + Chr(34) + "" + Chr(34) + ";\nvar htvmKeywords_temp = " + Chr(34) + "" + Chr(34) + ";\nvar staticTypes_temp = " + Chr(34) + "" + Chr(34) + ";\nvar builtInVars_temp = " + Chr(34) + "" + Chr(34) + ";\nvar operators_temp = " + Chr(34) + "" + Chr(34) + ";\nvar arrayMethods_temp = " + Chr(34) + "" + Chr(34) + ";\nvar programmingBlocksAndImport_temp = " + Chr(34) + "" + Chr(34) + ";\nvar htvm_trueFalseGlobalNull_temp = " + Chr(34) + "" + Chr(34) + ";\nvar htvm_comment_temp = " + Chr(34) + "" + Chr(34) + ";\nvar htvm_commentOpen1_temp = " + Chr(34) + "" + Chr(34) + ";\nvar htvm_commentClose2_temp = " + Chr(34) + "" + Chr(34) + ";\nitems3 = LoopParseFunc(allKeyWordsOut3, " + Chr(34) + "" + Chr(92) + "n" + Chr(34) + ", " + Chr(34) + "" + Chr(92) + "r" + Chr(34) + ")\nfor (let A_Index3 = 0; A_Index3 " + Chr(60) + " items3.length + 0; A_Index3++) {\n    const A_LoopField3 = items3[A_Index3 - 0];\n    if (Trim(A_LoopField3) != " + Chr(34) + "" + Chr(34) + ") {\n        if (A_Index3 == 0) {\n            items4 = LoopParseFunc(A_LoopField3, " + Chr(34) + "|" + Chr(34) + ")\n            for (let A_Index4 = 0; A_Index4 " + Chr(60) + " items4.length + 0; A_Index4++) {\n                const A_LoopField4 = items4[A_Index4 - 0];\n                items5 = LoopParseFunc(A_LoopField4, " + Chr(34) + "," + Chr(34) + ");\n                for (let A_Index5 = 0; A_Index5 " + Chr(60) + " items5.length + 0; A_Index5++) {\n                    const A_LoopField5 = items5[A_Index5 - 0];\n                    builtInCommands_temp += Trim(A_LoopField5) + " + Chr(34) + "|" + Chr(34) + ";\n                }\n            }\n        }\n        if (A_Index3 == 1 || A_Index3 == 2 || A_Index3 == 3 || A_Index3 == 4 || A_Index3 == 5 || A_Index3 == 64 || A_Index3 == 65 || A_Index3 == 66 || A_Index3 == 67 || A_Index3 == 68 || A_Index3 == 69 || A_Index3 == 70 || A_Index3 == 71 || A_Index3 == 72 || A_Index3 == 73 || A_Index3 == 74 || A_Index3 == 75 || A_Index3 == 76 || A_Index3 == 78 || A_Index3 == 79 || A_Index3 == 80 || A_Index3 == 81 || A_Index3 == 93 || A_Index3 == 94 || A_Index3 == 95 || A_Index3 == 96) {\n            htvmKeywords_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";\n        }\n        if (A_Index3 == 77) {\n            allFunctionNamesString3 += " + Chr(34) + "|" + Chr(34) + " + Trim(A_LoopField3);\n        }\n        if (A_Index3 " + Chr(62) + "= 49 && A_Index3 " + Chr(60) + "= 63) {\n            staticTypes_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";\n        }\n        if (A_Index3 " + Chr(62) + "= 88 && A_Index3 " + Chr(60) + "= 92) {\n            staticTypes_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";\n        }\n        if (A_Index3 == 145 || A_Index3 == 146 || A_Index3 == 6) {\n            builtInVars_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";\n        }\n        if (A_Index3 " + Chr(62) + "= 103 && A_Index3 " + Chr(60) + "= 126) {\n            operators_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";\n        }\n        if (A_Index3 " + Chr(62) + "= 140 && A_Index3 " + Chr(60) + "= 141) {\n            operators_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";\n        }\n        if (A_Index3 " + Chr(62) + "= 82 && A_Index3 " + Chr(60) + "= 87) {\n            arrayMethods_temp += Trim(StrReplace(A_LoopField3, " + Chr(34) + "." + Chr(34) + ", " + Chr(34) + "" + Chr(34) + ")) + " + Chr(34) + "|" + Chr(34) + ";\n        }\n        if (A_Index3 " + Chr(62) + "= 7 && A_Index3 " + Chr(60) + "= 43) {\n            programmingBlocksAndImport_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";\n        }\n        if (A_Index3 == 98) {\n            htvm_comment_temp = Trim(A_LoopField3);\n        }\n        if (A_Index3 == 99) {\n            htvm_commentOpen1_temp = Trim(A_LoopField3);\n        }\n        if (A_Index3 == 100) {\n            htvm_commentClose2_temp = Trim(A_LoopField3);\n        }\n        if (A_Index3 == 46 || A_Index3 == 47 || A_Index3 == 48 || A_Index3 == 97) {\n            htvm_trueFalseGlobalNull_temp += A_LoopField3 + " + Chr(34) + "|" + Chr(34) + ";\n        }\n    }\n}\nbuiltInCommands_temp = StringTrimRight(builtInCommands_temp, 1);\nhtvmKeywords_temp = StringTrimRight(htvmKeywords_temp, 1);\nstaticTypes_temp = StringTrimRight(staticTypes_temp, 1);\nbuiltInVars_temp = StringTrimRight(builtInVars_temp, 1);\noperators_temp = StringTrimRight(operators_temp, 1);\narrayMethods_temp = StringTrimRight(arrayMethods_temp, 1);\nprogrammingBlocksAndImport_temp = StringTrimRight(programmingBlocksAndImport_temp, 1);\nhtvm_trueFalseGlobalNull_temp = StringTrimRight(htvm_trueFalseGlobalNull_temp, 1);\nvar htvmKeywords = htvmKeywords_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');\nvar builtInCommands = builtInCommands_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');\nvar builtInFunctions = allFunctionNamesString3.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');\nvar staticTypes = staticTypes_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');\nvar builtInVars = builtInVars_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');\nvar arrayMethods = arrayMethods_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');\nvar programmingBlocksAndImport = programmingBlocksAndImport_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');\nvar htvm_trueFalseGlobalNull = htvm_trueFalseGlobalNull_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');\nvar htvm_operators = operators_temp.replace(/[^A-Za-z0-9_|" + Chr(92) + "s]/g, '').replace(/^" + Chr(92) + "d+/g, '').replace(/" + Chr(92) + "|+/g, '|').replace(/^(" + Chr(92) + "|)+|(" + Chr(92) + "|)+$/g, '');\n        \n        \n        var htvm_comment = htvm_comment_temp;\n        // Escape special characters in the comment symbol (just in case)\n        var escapedComment = htvm_comment.replace(/[.*+?^${}()|[" + Chr(92) + "]" + Chr(92) + "" + Chr(92) + "]/g, '" + Chr(92) + "" + Chr(92) + "$&');\n        var htvm_commentOpen1 = htvm_commentOpen1_temp.replace(/[.*+?^${}()|[" + Chr(92) + "]" + Chr(92) + "" + Chr(92) + "]/g, '" + Chr(92) + "" + Chr(92) + "$&');\n        var htvm_commentClose2 = htvm_commentClose2_temp.replace(/[.*+?^${}()|[" + Chr(92) + "]" + Chr(92) + "" + Chr(92) + "]/g, '" + Chr(92) + "" + Chr(92) + "$&');\n        this.$rules = {\n            start: [\n                { token: " + Chr(34) + "comment" + Chr(34) + ", regex: escapedComment + " + Chr(34) + ".*$" + Chr(34) + " },\n                { token: " + Chr(34) + "comment.block" + Chr(34) + ", regex: new RegExp(htvm_commentOpen1), next: " + Chr(34) + "comment_block" + Chr(34) + " },\n                { token: " + Chr(34) + "keyword" + Chr(34) + ", regex: " + Chr(34) + "" + Chr(92) + "" + Chr(92) + "b(?:" + Chr(34) + " + htvmKeywords + " + Chr(34) + ")" + Chr(92) + "" + Chr(92) + "b" + Chr(34) + " },\n                { token: " + Chr(34) + "command" + Chr(34) + ", regex: " + Chr(34) + "" + Chr(92) + "" + Chr(92) + "b(?:" + Chr(34) + " + builtInCommands + " + Chr(34) + ")(?=" + Chr(92) + "" + Chr(92) + ",)" + Chr(34) + " },\n                { token: " + Chr(34) + "functions" + Chr(34) + ", regex: " + Chr(34) + "" + Chr(92) + "" + Chr(92) + "b(?:" + Chr(34) + " + builtInFunctions + " + Chr(34) + ")(?=" + Chr(92) + "" + Chr(92) + "()" + Chr(34) + " },\n                { token: " + Chr(34) + "BuildInFunc" + Chr(34) + ", regex: " + Chr(34) + "" + Chr(92) + "" + Chr(92) + "b(?:" + Chr(34) + " + builtInVars + " + Chr(34) + ")" + Chr(92) + "" + Chr(92) + "b" + Chr(34) + " },\n                { token: " + Chr(34) + "arrayMethods" + Chr(34) + ", regex: " + Chr(34) + "" + Chr(92) + "" + Chr(92) + ".(?:" + Chr(34) + " + arrayMethods + " + Chr(34) + ")" + Chr(92) + "" + Chr(92) + "b" + Chr(34) + " },\n                { token: " + Chr(34) + "static_types" + Chr(34) + ", regex: " + Chr(34) + "" + Chr(92) + "" + Chr(92) + "b(?:" + Chr(34) + " + staticTypes + " + Chr(34) + ")" + Chr(92) + "" + Chr(92) + "b" + Chr(34) + " },\n                { token: " + Chr(34) + "programmingBlocksAndImport" + Chr(34) + ", regex: " + Chr(34) + "" + Chr(92) + "" + Chr(92) + "b(?:" + Chr(34) + " + programmingBlocksAndImport + " + Chr(34) + ")" + Chr(92) + "" + Chr(92) + "b" + Chr(34) + " },\n                { token: " + Chr(34) + "operators" + Chr(34) + ", regex: " + Chr(34) + "" + Chr(92) + "" + Chr(92) + "b(?:" + Chr(34) + " + htvm_operators + " + Chr(34) + ")" + Chr(92) + "" + Chr(92) + "b" + Chr(34) + " },\n                { token: " + Chr(34) + "trueANDfalse" + Chr(34) + ", regex: " + Chr(34) + "" + Chr(92) + "" + Chr(92) + "b(?:" + Chr(34) + " + htvm_trueFalseGlobalNull + " + Chr(34) + ")" + Chr(92) + "" + Chr(92) + "b" + Chr(34) + " },\n                { token: " + Chr(34) + "variables" + Chr(34) + ", regex: " + Chr(34) + "" + Chr(92) + "" + Chr(92) + "b[a-zA-Z_][a-zA-Z0-9_]*" + Chr(92) + "" + Chr(92) + "b" + Chr(34) + " },\n                { token: " + Chr(34) + "constant.numeric" + Chr(34) + ", regex: " + Chr(34) + "" + Chr(92) + "" + Chr(92) + "b[0-9]+" + Chr(92) + "" + Chr(92) + "b" + Chr(34) + " },\n                { token: " + Chr(34) + "braces_Open" + Chr(34) + ", regex: " + Chr(34) + "" + Chr(92) + "" + Chr(92) + "{" + Chr(34) + " },\n                { token: " + Chr(34) + "braces_Close" + Chr(34) + ", regex: " + Chr(34) + "" + Chr(92) + "" + Chr(92) + "}" + Chr(34) + " },\n              { token: " + Chr(34) + "string" + Chr(34) + ", regex: '" + Chr(34) + ".*?" + Chr(34) + "' },\n              // Multi-line comments\n              {\n                token: " + Chr(34) + "comment.block" + Chr(34) + ", // Token for multi-line comments\n               regex: new RegExp(htvm_commentOpen1),\n                next: " + Chr(34) + "comment_block" + Chr(34) + ",\n              },\n            ],\n            comment_block: [\n              {\n                token: " + Chr(34) + "comment.block" + Chr(34) + ",\n                regex: new RegExp(htvm_commentClose2),\n                next: " + Chr(34) + "start" + Chr(34) + ", // Go back to the start state\n              },\n              {\n                token: " + Chr(34) + "comment.block" + Chr(34) + ",\n                regex: /.*/, // Any other content within the comment\n              },\n            ],\n          };\n        };\n oop.inherits(HTVMHighlightRules, TextHighlightRules);\n\n        var HTMode = function () {\n          this.HighlightRules = HTVMHighlightRules;\n        };\n        oop.inherits(HTMode, TextMode);\n\n        exports.Mode = HTMode;\n      });\n\n// Custom renderer for code blocks to use Ace Editor\n\n// Custom renderer for code blocks to use Ace Editor\n\nvar defaultCodeRenderer = md.renderer.rules.fence;\nmd.renderer.rules.fence = function(tokens, idx, options, env, self) {\n    var token = tokens[idx];\n    var language = token.info.trim() || 'text';\n    var code = token.content;\n    \n    // Generate a unique ID for the editor\n    var editorId = 'ace-editor-' + idx;\n    var codeId = 'code-content-' + idx;\n    var buttonId = 'copy-button-' + idx;\n    \n    // Create container for the ace editor\n    var html = '" + Chr(60) + "div class=" + Chr(34) + "ace-editor-container" + Chr(34) + "" + Chr(62) + "" + Chr(92) + "n';\n    html += '" + Chr(60) + "div class=" + Chr(34) + "ace-editor-header" + Chr(34) + "" + Chr(62) + "';\n    \n    // Add copy button before language\n    html += '" + Chr(60) + "div style=" + Chr(34) + "display: flex; align-items: center;" + Chr(34) + "" + Chr(62) + "';\n    html += '" + Chr(60) + "button id=" + Chr(34) + "' + buttonId + '" + Chr(34) + " class=" + Chr(34) + "copy-button" + Chr(34) + " data-code-id=" + Chr(34) + "' + codeId + '" + Chr(34) + "" + Chr(62) + "';\n    html += '" + Chr(60) + "i class=" + Chr(34) + "fas fa-copy" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/i" + Chr(62) + " Copy" + Chr(60) + "/button" + Chr(62) + "';\n    html += '" + Chr(60) + "span class=" + Chr(34) + "ace-editor-language" + Chr(34) + "" + Chr(62) + "' + language + '" + Chr(60) + "/span" + Chr(62) + "';\n    html += '" + Chr(60) + "/div" + Chr(62) + "';\n    \n    html += '" + Chr(60) + "span" + Chr(62) + "" + Chr(60) + "i class=" + Chr(34) + "fas fa-code" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/i" + Chr(62) + "" + Chr(60) + "/span" + Chr(62) + "" + Chr(60) + "/div" + Chr(62) + "" + Chr(92) + "n';\n    \n    // Create a pre element to hold the code initially\n    html += '" + Chr(60) + "pre id=" + Chr(34) + "' + editorId + '" + Chr(34) + " class=" + Chr(34) + "ace-editor" + Chr(34) + "" + Chr(62) + "' + escapeHtml(code) + '" + Chr(60) + "/pre" + Chr(62) + "" + Chr(92) + "n';\n    html += '" + Chr(60) + "div id=" + Chr(34) + "' + codeId + '" + Chr(34) + " style=" + Chr(34) + "display: none;" + Chr(34) + "" + Chr(62) + "' + escapeHtml(code) + '" + Chr(60) + "/div" + Chr(62) + "" + Chr(92) + "n';\n    html += '" + Chr(60) + "/div" + Chr(62) + "" + Chr(92) + "n';\n    \n    // Store the code and language for later use with Ace\n    setTimeout(function() {\n        initAceEditor(editorId, code, language);\n    }, 100);\n    \n    return html;\n};\n        \n// Function to initialize the Ace editor\nfunction initAceEditor(editorId, code, language) {\n    var editor = ace.edit(editorId);\n    editor.setTheme(" + Chr(34) + "ace/theme/monokai" + Chr(34) + ");\n    \n    // Map markdown language names to Ace mode names\n    var modeMap = {\n        'javascript': 'javascript',\n        'js': 'javascript',\n        'html': 'html',\n        'css': 'css',\n        'python': 'python',\n        'py': 'python',\n        'json': 'json',\n        'htvm': 'htvm'\n        // Add more mappings as needed\n    };\n    \n    // Set the correct mode based on language\n    var mode = modeMap[language.toLowerCase()] || 'text';\n    editor.session.setMode(" + Chr(34) + "ace/mode/" + Chr(34) + " + mode);\n    \n    // Set full code content directly to maintain formatting\n    editor.setValue(code);\n    editor.clearSelection();\n    \n    // Make editor read-only\n    editor.setReadOnly(true);\n    \n    // Disable wrap mode to preserve formatting\n    editor.getSession().setUseWrapMode(false);\n    \n    // Additional editor settings\n    editor.setShowPrintMargin(false);\n    editor.setHighlightActiveLine(true);\n    editor.setOptions({\n        fontSize: " + Chr(34) + "14px" + Chr(34) + ",\n    });\n    \n    // Calculate the exact number of lines\n    var lineCount = editor.session.getLength();\n    \n    // Get the actual line height from the renderer\n    var lineHeight = editor.renderer.lineHeight;\n    \n    // Calculate exact height with a tiny buffer\n    var exactHeight = (lineCount * lineHeight);\n    \n    // Set the editor height to exactly fit the content\n    document.getElementById(editorId).style.height = exactHeight + " + Chr(34) + "px" + Chr(34) + ";\n    \n    // Final resize to update the editor view\n    editor.resize();\n}\n\n// Helper function to escape HTML\nfunction escapeHtml(unsafe) {\n    return unsafe\n        .replace(/&/g, " + Chr(34) + "&amp;" + Chr(34) + ")\n        .replace(/" + Chr(60) + "/g, " + Chr(34) + "&lt;" + Chr(34) + ")\n        .replace(/" + Chr(62) + "/g, " + Chr(34) + "&gt;" + Chr(34) + ")\n        .replace(/" + Chr(34) + "/g, " + Chr(34) + "&quot;" + Chr(34) + ")\n        .replace(/'/g, " + Chr(34) + "&#039;" + Chr(34) + ");\n}\n\n        \n        // Get the markdown content (from the hidden div)\n        var markdownText = document.getElementById(" + Chr(34) + "markdown-content" + Chr(34) + ").innerText;\n\n        // Convert markdown to HTML\n        var htmlContent = md.render(markdownText);\n\n        // Output the rendered HTML to the markdown-output div\n        document.getElementById(" + Chr(34) + "markdown-output" + Chr(34) + ").innerHTML = htmlContent;\n        \n        // Process all headings to add anchor links\n        document.querySelectorAll('#markdown-output h1, #markdown-output h2, #markdown-output h3, #markdown-output h4, #markdown-output h5, #markdown-output h6').forEach(function(heading) {\n            // Generate ID if none exists\n            if (!heading.id) {\n                heading.id = heading.textContent.toLowerCase().replace(/" + Chr(92) + "s+/g, '-').replace(/[^" + Chr(92) + "w-]/g, '');\n            }\n            \n            // Create an anchor element\n            var anchor = document.createElement('a');\n            anchor.className = 'header-anchor';\n            anchor.href = '#' + heading.id;\n            anchor.innerHTML = '" + Chr(60) + "i class=" + Chr(34) + "fas fa-link" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/i" + Chr(62) + "';\n            \n            // Add click event to update URL without refreshing page\n            anchor.addEventListener('click', function(e) {\n                e.preventDefault();\n                history.pushState(null, null, this.getAttribute('href'));\n                // Scroll to the element\n                document.getElementById(heading.id).scrollIntoView({\n                    behavior: 'smooth'\n                });\n            });\n            \n            // Add the anchor to the heading\n            heading.appendChild(anchor);\n        });\n        \n        // Process all links in the rendered markdown\n        document.querySelectorAll('#markdown-output a:not(.header-anchor)').forEach(function(link) {\n            // Check if it's an internal anchor link\n            if (link.getAttribute('href').startsWith('#')) {\n                // Add click event to update URL without refreshing page\n                link.addEventListener('click', function(e) {\n                    e.preventDefault();\n                    var targetId = this.getAttribute('href').substring(1);\n                    history.pushState(null, null, this.getAttribute('href'));\n                    // Scroll to the element\n                    document.getElementById(targetId).scrollIntoView({\n                        behavior: 'smooth'\n                    });\n                });\n            } else {\n                // It's an external link\n                link.setAttribute('target', '_blank');\n                link.setAttribute('rel', 'noopener noreferrer');\n                link.classList.add('external-link');\n            }\n        });\n        \n        // Set up clipboard functionality for copy buttons after DOM is fully loaded\n        document.addEventListener('DOMContentLoaded', function() {\n            setupCopyButtons();\n        });\n        \n        // Also set up copy buttons after the markdown is rendered\n        setTimeout(function() {\n            setupCopyButtons();\n        }, 200);\n        \n        // Function to set up copy buttons\n        function setupCopyButtons() {\n            document.querySelectorAll('.copy-button').forEach(function(button) {\n                button.addEventListener('click', function() {\n                    // Store the current button ID\n                    var buttonId = this.id;\n                    var codeId = this.getAttribute('data-code-id');\n                    var codeElement = document.getElementById(codeId);\n                    var codeText = codeElement.textContent;\n                    \n                    // Create a temporary textarea element to copy from\n                    var textarea = document.createElement('textarea');\n                    textarea.value = codeText;\n                    textarea.setAttribute('readonly', '');\n                    textarea.style.position = 'absolute';\n                    textarea.style.left = '-9999px';\n                    document.body.appendChild(textarea);\n                    \n                    // Select and copy the text\n                    textarea.select();\n                    document.execCommand('copy');\n                    \n                    // Remove the temporary element\n                    document.body.removeChild(textarea);\n                    \n                    // Visual feedback - only for this specific button\n                    var originalText = this.innerHTML;\n                    this.innerHTML = '" + Chr(60) + "i class=" + Chr(34) + "fas fa-check" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/i" + Chr(62) + " Copied!';\n                    this.classList.add('copy-success');\n                    \n                    // Reset button after 5 seconds\n                    var buttonElement = this;\n                    setTimeout(function() {\n                        // Only reset if it hasn't been changed again\n                        if (buttonElement.classList.contains('copy-success')) {\n                            buttonElement.innerHTML = originalText;\n                            buttonElement.classList.remove('copy-success');\n                        }\n                    }, 5000);\n                });\n            });\n        }\n        \n        // Handle initial hash in URL if any\n        if (window.location.hash) {\n            var targetId = window.location.hash.substring(1);\n            var targetElement = document.getElementById(targetId);\n            if (targetElement) {\n                setTimeout(function() {\n                    targetElement.scrollIntoView({\n                        behavior: 'smooth'\n                    });\n                }, 100);\n            }\n        }\n\n\n        // Apply CSS styles for the editor\n\n        var css = " + Chr(96) + "\n    .ace-monokai .ace_marker-layer .ace_active-line {\n      background-color: #103010 !important;\n    }\n    \n    .ace-monokai {\n      background-color: #050505 !important;\n      color: #f8f8f2;\n    }\n    \n    .ace-monokai .ace_gutter {\n      background: #204020 !important;\n      color: #cbcdc3 !important;\n    }\n    \n    .ace-monokai .ace_gutter-active-line {\n      background-color: transparent !important;\n    }\n    \n    .ace-monokai .ace_entity.ace_name.ace_tag,\n    .ace-monokai .ace_keyword,\n    .ace-monokai .ace_meta.ace_tag,\n    .ace-monokai .ace_storage {\n      color: #40a0e0 !important;\n    }\n    \n    .ace-monokai .ace_entity.ace_name.ace_function,\n    .ace-monokai .ace_entity.ace_other,\n    .ace-monokai .ace_entity.ace_other.ace_attribute-name,\n    .ace-monokai .ace_variable {\n      color: #ff80df !important;\n    }\n    \n    .ace-monokai .ace_comment {\n      color: #40d080 !important;\n      font-weight: line-through !important;\n    }\n    \n    .ace-monokai .ace_commentOpen_Close {\n      color: #40d080 !important;\n      font-weight: line-through !important;\n    }\n    \n    .ace-monokai .ace_variables {\n      color: #ffffff !important;\n    }\n    \n    .ace-monokai .ace_functions {\n      color: #80dfff !important;\n    }\n    \n    .ace-monokai .ace_keyword {\n    color: #8080e0 !important; /* Customize color as needed */\n    font-weight: bold !important;\n    }\n    .ace-monokai .ace_braces_Open {\n      color: #FFFFff !important;\n    }\n    \n    .ace-monokai .ace_braces_Close {\n      color: #FFFFff !important;\n    }\n    \n    .ace-monokai .ace_arrayMethods {\n      color: #FAB820 !important;\n    }\n    \n    .ace-monokai .ace_BuildInFunc {\n      color: #ff80df !important;\n    }\n    \n    .ace-monokai .ace_command {\n      color: #40a0e0 !important;\n      font-weight: bold !important;\n    }\n    \n    .ace-monokai .ace_static_types {\n      color: #569cd6 !important;\n      font-weight: bold !important;\n    }\n    \n    .ace-monokai .ace_string {\n      color: #ffa0a0 !important;\n      font-weight: lighter !important;\n    }\n    \n    .ace-monokai .ace_operators {\n      color: #00ffff !important;\n      font-weight: lighter !important;\n    }\n    \n    \n    .ace-monokai .ace_trueANDfalse {\n      color: #00ffff !important;\n      font-weight: lighter !important;\n    }\n    \n    .ace-monokai .ace_escape-char {\n      color: #ff8000 !important;\n      font-weight: bold !important;\n    }\n\n    .ace-monokai .ace_programmingBlocksAndImport {\n      color: #F0401C !important;\n      font-weight: bold !important;\n    }\n    \n    .ace-monokai .ace_punctuation,\n    .ace-monokai .ace_punctuation.ace _tag {\n      color: #ffa0a0 !important;\n    }\n    \n    *::-webkit-scrollbar {\n      width: 1em;\n    }\n    \n    *::-webkit-scrollbar-track {\n      box-shadow: inset 0 0 6px rgba(0, 0, 0, 0.3);\n    }\n    \n    *::-webkit-scrollbar-thumb {\n      background-color: darkgrey;\n      outline: 1px solid slategrey;\n    }\n" + Chr(96) + ";\n\n        var style = document.createElement(" + Chr(34) + "style" + Chr(34) + ");\n        style.type = " + Chr(34) + "text/css" + Chr(34) + ";\n        if (style.styleSheet) {\n          style.styleSheet.cssText = css;\n        } else {\n          style.appendChild(document.createTextNode(css));\n        }\n        document.head.appendChild(style);\n" + "\n// allHTVMinst\n\nlet allHTVMinstOLD = " + Chr(34) + "" + Chr(34) + "\n\nfunction sleep(ms) {\n    return new Promise(resolve =" + Chr(62) + " setTimeout(resolve, ms));\n}\n\nasync function reloadPage() {\n    // Check if key exists in localStorage\n    if (localStorage.getItem(" + Chr(34) + "allHTVMinst_FIX_FIX_FIX_FIX_FIX_FIX_FIX_FIX" + Chr(34) + ") !== null) {\n        // console.log(" + Chr(34) + "allHTVMinst_FIX_FIX_FIX_FIX_FIX_FIX_FIX_FIX exists in localStorage!" + Chr(34) + ");\n        // Retrieve data from localStorage\n        allHTVMinstOLD = localStorage.getItem(" + Chr(34) + "allHTVMinst_FIX_FIX_FIX_FIX_FIX_FIX_FIX_FIX" + Chr(34) + ");\n        \n        if (allHTVMinst != allHTVMinstOLD) {\n            localStorage.setItem(" + Chr(34) + "allHTVMinst_FIX_FIX_FIX_FIX_FIX_FIX_FIX_FIX" + Chr(34) + ", allHTVMinst); \n            await sleep(900); // Add a 1 second delay before the first reload\n            window.location.reload();\n        }    \n    } else {\n        // console.log(" + Chr(34) + "allHTVMinst_FIX_FIX_FIX_FIX_FIX_FIX_FIX_FIX does not exist." + Chr(34) + ");\n        // Set data in localStorage\n        localStorage.setItem(" + Chr(34) + "allHTVMinst_FIX_FIX_FIX_FIX_FIX_FIX_FIX_FIX" + Chr(34) + ", allHTVMinst); \n        await sleep(900); // Add a 1 second delay before the first reload\n        window.location.reload();\n    }\n}\n// Call the reloadPage function\nreloadPage();\n" + "\n    " + Chr(60) + "/script" + Chr(62) + "\n" + Chr(60) + "/body" + Chr(62) + "\n" + Chr(60) + "/html" + Chr(62) + "";
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
        if (Trim(StrSplit(DOCS_params, "\n", 1)) == "") {
            print("Usage: <instruction_file> [function_name]" + Chr(10) + Chr(10) + "- <instruction_file>: Required. Generates DOCUMENTATION.md and DOCUMENTATION.html." + Chr(10) + "- [function_name]: Optional. If provided, checks whether the function exists and it does not output any files.");
            print("no params Exiting...");
            ExitApp();
        }
        std::vector<std::string> items18 = LoopParseFunc(DOCS_params, "\n", "\r");
        for (size_t A_Index18 = 0; A_Index18 < items18.size() + 0; A_Index18++) {
            std::string A_LoopField18 = items18[A_Index18 - 0];
            if (A_Index18 == 0) {
                print(A_LoopField18);
                DOCS_param1 = Trim(A_LoopField18);
            }
            if (A_Index18 == 1) {
                print(A_LoopField18);
                DOCS_param2 = Trim(A_LoopField18);
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
