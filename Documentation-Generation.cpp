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


int main(int argc, char* argv[]) {
    std::string params = "";
    std::string param1 = "";
    std::string param2 = "";
    params = Trim(GetParams());
    if (Trim(StrSplit(params, "\n", 1)) == "") {
        print("no params Exiting...");
        ExitApp();
    }
    std::vector<std::string> items1 = LoopParseFunc(params, "\n", "\r");
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        if (A_Index1 == 0) {
            print(A_LoopField1);
            param1 = Trim(A_LoopField1);
        }
        if (A_Index1 == 1) {
            print(A_LoopField1);
            param2 = Trim(A_LoopField1);
        }
    }
    if (!FileExist(param1)) {
        print("the file doesn't exist!!!");
        ExitApp();
    }
    int checkIfFuncNameExists = 0;
    if (Trim(param2) != "") {
        checkIfFuncNameExists = 1;
    }
    std::string instructionFileData = "";
    instructionFileData = FileRead(Trim(param1));
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    int inFunc = 0;
    std::vector<std::string> tempArrayInitOSP;
    std::vector<std::any> OSPHTVMOSP_funcData = {
    std::string("funcData"),
    tempArrayInitOSP,
    tempArrayInitOSP,
    tempArrayInitOSP,
    };
    std::vector<std::string> items2 = LoopParseFunc(instructionFileData, "\n", "\r");
    for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
        std::string A_LoopField2 = items2[A_Index2 - 0];
        if (Trim(A_LoopField2) == "funcEND======================funcEND==============") {
            inFunc = 0;
        }
        if (inFunc == 1) {
            if (SubStr(Trim(A_LoopField2), 1, 6) == "lang: ") {
                std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_funcData[1]).push_back(Trim(A_LoopField2));
            }
            else if (SubStr(Trim(A_LoopField2), 1, 6) == "name: ") {
                std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_funcData[2]).push_back(Trim(A_LoopField2));
            }
            else if (SubStr(Trim(A_LoopField2), 1, 13) == "description: ") {
                std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_funcData[3]).push_back(Trim(A_LoopField2));
            }
        }
        if (Trim(A_LoopField2) == "func======================func==============") {
            inFunc = 1;
        }
    }
    std::vector<std::string> allFuncNames = sortArr(std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_funcData[2]));
    std::string theFuncThatExistsIsCalled = "";
    if (checkIfFuncNameExists == 1) {
        int exitedLoopCheckIfFuncNameExists = 0;
        for (int A_Index3 = 0; A_Index3 < allFuncNames.size() + 0; A_Index3++) {
            print(allFuncNames[A_Index3]);
            if (StrLower(param2) == StrLower(Trim(StrSplit(allFuncNames[A_Index3], ":", 2)))) {
                theFuncThatExistsIsCalled = Trim(StrSplit(allFuncNames[A_Index3], ":", 2));
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
    for (int A_Index4 = 0; A_Index4 < std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_funcData[2]).size() + 0; A_Index4++) {
        //print(std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_funcData[2])[A_Index4])
        allFuncNamesTemp = std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_funcData[2])[A_Index4];
        tempLang = std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_funcData[1])[A_Index4];
        tempDesc = std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_funcData[3])[A_Index4];
        for (int A_Index5 = 0; A_Index5 < allFuncNames.size() + 0; A_Index5++) {
            if (Trim(allFuncNamesTemp) == Trim(StrSplit(allFuncNames[A_Index5], "|", 1))) {
                if (countChars(allFuncNames[A_Index5], "|") == 0) {
                    allFuncNames[A_Index5] = allFuncNames[A_Index5] + "|" + Trim(tempDesc) + "|" + Trim(tempLang);
                } else {
                    allFuncNames[A_Index5] = allFuncNames[A_Index5] + "|" + Trim(tempLang);
                }
            }
        }
    }
    std::vector<std::string> allFuncs;
    std::string tempstr = "";
    std::string isLangCpp = "";
    std::string isLangPy = "";
    std::string isLangJs = "";
    std::string allFuncsTempAdd = "";
    int isDescNull = 0;
    for (int A_Index6 = 0; A_Index6 < allFuncNames.size() + 0; A_Index6++) {
        //print(allFuncNames[A_Index6])
        tempstr = Trim(allFuncNames[A_Index6]);
        isDescNull = 0;
        allFuncsTempAdd = "";
        isLangCpp = "No";
        isLangPy = "No";
        isLangJs = "No";
        std::vector<std::string> items7 = LoopParseFunc(tempstr, "|");
        for (size_t A_Index7 = 0; A_Index7 < items7.size() + 0; A_Index7++) {
            std::string A_LoopField7 = items7[A_Index7 - 0];
            if (SubStr(Trim(A_LoopField7), 1, 8) == "lang: js") {
                isLangJs = "Yes";
            }
            else if (SubStr(Trim(A_LoopField7), 1, 8) == "lang: py") {
                isLangPy = "Yes";
            }
            else if (SubStr(Trim(A_LoopField7), 1, 9) == "lang: cpp") {
                isLangCpp = "Yes";
            }
            else if (SubStr(Trim(A_LoopField7), 1, 6) == "name: ") {
                allFuncsTempAdd += Trim(A_LoopField7) + "|";
            }
            else if (SubStr(Trim(A_LoopField7), 1, 13) == "description: ") {
                allFuncsTempAdd += Trim(A_LoopField7) + "|";
            }
            if (Trim(StrLower(A_LoopField7)) == "description: null") {
                isDescNull = 1;
            }
        }
        if (isDescNull != 1) {
            allFuncsTempAdd += isLangCpp + "|" + isLangPy + "|" + isLangJs;
            allFuncs.push_back(allFuncsTempAdd);
        }
    }
    for (int A_Index8 = 0; A_Index8 < 20 + 0; A_Index8++) {
        //print("===========================================")
    }
    std::vector<std::string> categories;
    std::string theCurrentLine = "";
    std::string theCurrentDescCategory = "";
    int once = 0;
    int didWeFindSameCategory = 0;
    for (int A_Index9 = 0; A_Index9 < allFuncs.size() + 0; A_Index9++) {
        //print(allFuncs[A_Index9])
        once++;
        theCurrentLine = Trim(allFuncs[A_Index9]);
        theCurrentDescCategory = Trim(StrSplit(theCurrentLine, "|", 2));
        theCurrentDescCategory = Trim(StrSplit(theCurrentDescCategory, ":", 2));
        theCurrentDescCategory = Trim(StrLower(Trim(StrSplit(theCurrentDescCategory, "~~~", 1))));
        didWeFindSameCategory = 0;
        if (once == 1) {
            categories.push_back(theCurrentDescCategory + "\n" + theCurrentLine);
        } else {
            for (int A_Index10 = 0; A_Index10 < categories.size() + 0; A_Index10++) {
                if (Trim(StrLower(StrSplit(categories[A_Index10], "\n", 1))) == Trim(theCurrentDescCategory)) {
                    didWeFindSameCategory = 1;
                    categories[A_Index10] = categories[A_Index10] + "\n" + theCurrentLine;
                    break;
                }
            }
            if (didWeFindSameCategory == 0) {
                categories.push_back(theCurrentDescCategory + "\n" + theCurrentLine);
            }
        }
    }
    for (int A_Index11 = 0; A_Index11 < 20 + 0; A_Index11++) {
        //print("==========================")
    }
    std::string outMDup = "# HTVM Documentation\n\n1. [Introduction](#introduction-to-htvm)  \nUnderstand why HTVM is the future of programming.  \n\n2. [OSP (Objectively Simplified Programming) Paradigm](#osp-objectively-simplified-programming-paradigm)  \nLearn about the new paradigm that replaces traditional object-oriented programming.  \n\n3. [Built-in Functions](#built-in-functions)  \nExplore the wide range of built-in functions categorized for ease of use.  \n\n---\n\n## Introduction to HTVM\n\n[Go back](#htvm-documentation) \n\nHTVM is a revolutionary tool designed to replace traditional programming. With HTVM, you can create your own programming language directly [here](https://themaster1127.github.io/HTVM/).\n\nWhat makes HTVM powerful:  \n- **Syntax Customization**:  \n  Here’s what you can change:  \n  - **Keywords**: Modify the keywords used for " + Chr(96) + "if" + Chr(96) + " statements, " + Chr(96) + "while" + Chr(96) + " loops, " + Chr(96) + "for" + Chr(96) + " loops, and more.  \n  - **Operators**: Change the operators like " + Chr(96) + "==" + Chr(96) + ", " + Chr(96) + "!=" + Chr(96) + ", and others to suit your needs.  \n\n- **Inspiration from AutoHotKey**:  \n  Features like " + Chr(96) + "Loop" + Chr(96) + " and " + Chr(96) + "Loop, Parse" + Chr(96) + " (just like in AutoHotKey) are supported and customizable.  \n\n- **Cross-Language Compatibility**:  \n  Languages created with HTVM can be transpiled into **C++**, **Python**, and **JavaScript**.  \n\n- **Static Typing**:  \n  Types are required when converting to C++, but are optional for Python and JavaScript.  \n\n- **Built-in Functions**:  \n  Instead of libraries, HTVM offers built-in functions organized into categories. Scroll to the [Built-in Functions](#built-in-functions) section for more details.  \n\n## Core Features\n\n### Language Configuration\n- **Target Language Selection**\n  - Choose between **C++**, **Python** and **JavaScript** \n  - Specify file extensions for output files\n  - Configure HTML wrapping for JavaScript output\n\n### Syntax Customization\n- **Code Block Style**\n  - Toggle between curly braces " + Chr(96) + "{}" + Chr(96) + " or " + Chr(96) + "end" + Chr(96) + " keywords\n  - Enable/disable Python-style colon syntax\n  - Customize parentheses usage\n  - Control semicolon placement\n\n- **Function Definitions**\n  - Toggle function keywords\n  - Customize async main function for JavaScript\n  - Configure global variable handling\n\n### Type System\n- **Basic Types**\n  - Integer (INT)\n  - String (STR)\n  - Boolean (BOOL)\n  - Float (FLOAT)\n\n- **Extended Integer Types**\n  - INT8\n  - INT16\n  - INT32\n  - INT64\n\n### Control Structures\n- **Conditional Statements**\n  - If/Else/ElseIf\n  - Switch/Case/Default\n  - Custom keywords for all conditional operators\n\n- **Loops**\n  - While loops\n  - For loops with customizable syntax\n  - Infinite loops\n  - Parse loops (AutoHotkey-style)\n  - Custom indexing (0-based or 1-based)\n  - Loop control (break, continue)\n\n### Arrays and Collections\n- **Array Types**\n  - Integer arrays\n  - String arrays\n  - Float arrays\n  - Boolean arrays\n\n- **Array Operations**\n  - Append\n  - Pop\n  - Insert\n  - Remove\n  - Size\n  - IndexOf\n\n### Error Handling\n- **Exception Management**\n  - Try blocks\n  - Catch blocks\n  - Finally blocks (except in C++)\n  - Custom error messages\n  - Throw statements\n\n### JavaScript-Specific Features\n- **Variable Declaration**\n  - var, let, const keywords\n  - Automatic var declaration option\n  - await keyword support\n\n### Operators\n- **Assignment Operators**\n  - Basic assignment\n  - Addition assignment\n  - Subtraction assignment\n  - Multiplication assignment\n  - Division assignment\n  - Concatenation assignment\n\n- **Comparison Operators**\n  - Equal to\n  - Not equal to\n  - Greater than\n  - Less than\n  - Greater than or equal to\n  - Less than or equal to\n\n- **Logical Operators**\n  - AND\n  - OR\n  - NOT\n\n### Comments\n- Single-line comments\n- Multi-line comments\n- Custom comment symbols\n\n### AutoHotkey-Inspired Features\n- **Loop Variables**\n  - A_Index (customizable)\n  - A_LoopField (customizable)\n- **Loop Types**\n  - Parse loops\n  - Count loops\n  - Infinite loops\n\n## Configuration Options\n\n### Syntax Style\n- " + Chr(96) + "useFuncKeyWord" + Chr(96) + ": Toggle function definition keywords\n- " + Chr(96) + "useCurlyBraces" + Chr(96) + ": Toggle curly brace block definitions\n- " + Chr(96) + "useEnd" + Chr(96) + ": Toggle 'end' keyword for block closure\n- " + Chr(96) + "useSemicolon" + Chr(96) + ": Toggle statement-ending semicolons\n- " + Chr(96) + "useParentheses" + Chr(96) + ": Configure parentheses requirements\n- " + Chr(96) + "usePythonicColonSyntax" + Chr(96) + ": Enable Python-style block definitions\n\n### JavaScript Configuration\n- " + Chr(96) + "useInJavaScriptAlwaysUseVar" + Chr(96) + ": Force 'var' declarations\n- " + Chr(96) + "useJavaScriptInAfullHTMLfile" + Chr(96) + ": Enable HTML wrapping\n- " + Chr(96) + "useJavaScriptAmainFuncDef" + Chr(96) + ": Configure async main function\n\n### Loop Configuration\n- " + Chr(96) + "AHKlikeLoopsIndexedAt" + Chr(96) + ": Set loop index starting value\n- " + Chr(96) + "forLoopLang" + Chr(96) + ": Select loop syntax style\n- " + Chr(96) + "keyWordAIndex" + Chr(96) + ": Customize loop index variable name\n- " + Chr(96) + "keyWordALoopField" + Chr(96) + ": Customize loop field variable name\n\n\nHTVM empowers developers to create programming languages tailored to their needs while maintaining compatibility with modern technologies.  \n\n---\n\n## OSP (Objectively Simplified Programming) Paradigm  \n\n[Go back](#htvm-documentation) \n\nOSP (Objectively Simplified Programming) is a paradigm designed to replace OOP since OOP was a mistake. To learn OSP you need to first forget everything about OOP. Forget about concepts like inheritance, polymorphism, encapsulation, private/public keywords and instances.\n\nOSP eliminates the complexities of object-oriented programming.  \n\nHere’s how OSP works:  \n- **Hierarchies**:  \n  - **Alliance**: The top-level structure, defined using the " + Chr(96) + "alliance" + Chr(96) + " keyword. \n  - **Crew**: Sub-levels within an alliance, defined using the " + Chr(96) + "crew" + Chr(96) + " keyword.  \n  - **Method**: Functions defined within alliances or crews using the " + Chr(96) + "method" + Chr(96) + " keyword.  \n  - **Object**: Objects are defined using the " + Chr(96) + "def obj" + Chr(96) + " keyword.  \n\n- **Properties**:  \n  - Defined within objects using the " + Chr(96) + "porp" + Chr(96) + " keyword. You must specify the type, even when converting to Python or JavaScript, for readability.  \n\n\n### **The " + Chr(96) + "this" + Chr(96) + " Keyword**:\n\n- **Definition**:  \n  The " + Chr(96) + "this" + Chr(96) + " keyword is a reference to the current object that invoked a method. In OSP, " + Chr(96) + "this" + Chr(96) + " is **explicitly required to refer to objects**, and **you must always specify the full path** of objects and their properties when using it. Additionally, " + Chr(96) + "this" + Chr(96) + " is **only valid within methods**, as it represents the object calling that specific method.\n\n---\n\n### **Key Rules**:\n1. **Full Path Requirement**:  \n   - In OSP, **you must always specify the full path** of objects and properties when using " + Chr(96) + "this" + Chr(96) + ".  \n   - For example:  \n     - **Correct**: " + Chr(96) + "Movable.Vehicles.Car.fuel" + Chr(96) + "  \n     - **Incorrect**: " + Chr(96) + "fuel" + Chr(96) + "\n\n2. **Only Inside Methods**:  \n   - The " + Chr(96) + "this" + Chr(96) + " keyword can **only** be used inside a method. It refers to the object that invoked the method and provides context for operations on that object.  \n   - Using " + Chr(96) + "this" + Chr(96) + " outside of a method will result in an error, as there is no calling object to reference.\n\n---\n\n### **Explanation Using the Example**:\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\nmethod void move(this) {\n    if (this == " + Chr(34) + "Movable.Vehicles.Car" + Chr(34) + ") {\n        if (Movable.Vehicles.Car.fuel " + Chr(62) + " 0) {\n            print(" + Chr(34) + "The car is driving." + Chr(34) + ")\n            Movable.Vehicles.Car.fuel = Movable.Vehicles.Car.fuel - 10\n        } else {\n            print(" + Chr(34) + "The car is out of fuel." + Chr(34) + ")\n            Movable.Vehicles.Car.hasFUEL = false\n        }\n    }\n    else if (this == " + Chr(34) + "Movable.Vehicles.Bike" + Chr(34) + ") {\n        if (Movable.Vehicles.Bike.energy " + Chr(62) + " 0) {\n            print(" + Chr(34) + "The bike is pedaling." + Chr(34) + ")\n            Movable.Vehicles.Bike.energy = Movable.Vehicles.Bike.energy - 5\n        } else {\n            print(" + Chr(34) + "The bike is out of energy." + Chr(34) + ")\n            Movable.Vehicles.Bike.hasENERGY = false\n        }\n    }\n}\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n- The " + Chr(96) + "this" + Chr(96) + " keyword in this method represents the specific object calling " + Chr(96) + "move()" + Chr(96) + ".  \n  For instance:\n  - If " + Chr(96) + "this == " + Chr(34) + "Movable.Vehicles.Car" + Chr(34) + "" + Chr(96) + ", the method knows the caller is the **Car object**, and it manipulates " + Chr(96) + "Movable.Vehicles.Car" + Chr(96) + " properties.\n  - Similarly, if " + Chr(96) + "this == " + Chr(34) + "Movable.Vehicles.Bike" + Chr(34) + "" + Chr(96) + ", the method operates on the **Bike object**.\n\n- If you try to use " + Chr(96) + "this" + Chr(96) + " **outside of any method**, it won’t work because " + Chr(96) + "this" + Chr(96) + " has no object context to refer to.  \n  For example:\n  " + Chr(96) + "" + Chr(96) + "" + Chr(96) + " cpp\n  def obj Car {\n      prop int fuel = 100\n      print(this)  // This will cause an error!\n  }\n  " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\n---\n\n### **Why This Restriction Exists**:\n1. **Object Context**:  \n   - The " + Chr(96) + "this" + Chr(96) + " keyword needs a calling object to provide context. Without a method invocation, there’s no object to reference.\n\n2. **Scope Control**:  \n   - Limiting " + Chr(96) + "this" + Chr(96) + " to methods ensures clear and explicit usage, making code easier to understand and debug.\n\n3. **Example: Calling a Method with an Object**:  \n   - To use the " + Chr(96) + "this" + Chr(96) + " keyword, you must **pass an object** when invoking the method:  \n   " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\n   allianceName.crewName.move(allianceName.crewName.objName)\n   " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n   - Here:\n     - " + Chr(96) + "allianceName" + Chr(96) + " is the main alliance.\n     - " + Chr(96) + "crewName" + Chr(96) + " is the crew containing the method " + Chr(96) + "move" + Chr(96) + ".\n     - " + Chr(96) + "objName" + Chr(96) + " is the specific object being passed to the method. This allows " + Chr(96) + "this" + Chr(96) + " to refer to " + Chr(96) + "objName" + Chr(96) + " inside the method.\n\n---\n\n## **You Don’t Need an Alliance or Crew to Define Objects**\n- In OSP, you can define objects (" + Chr(96) + "def obj" + Chr(96) + ") directly without placing them inside an **alliance** or a **crew**.  \n- This makes it flexible to create standalone objects when you don’t need a larger structure.  \n\n### **Example: Standalone Object Definition**\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\ndef obj Standalone {\n    prop int value = 10\n    prop str name = " + Chr(34) + "Independent" + Chr(34) + "\n}\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\nto access later just use:\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\nStandalone.value\nStandalone.name\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\n---\n\n### **Methods in Alliances**\n- Methods can also be defined directly in an **alliance**, without being part of a **crew** and the opposite is well.\n\n### **Example: Method in an Alliance**\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\nalliance ExampleAlliance {\n    method void greet() {\n        print(" + Chr(34) + "Hello from ExampleAlliance!" + Chr(34) + ")\n    }\n}\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\nto call greet just do:\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\nExampleAlliance.greet()\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\n## Global Accessibility:  \n  - There are no scopes in OSP. As long as a variable or structure is defined above, it is accessible below. Everything is global, and the full path must always be used.  \n\n## Arrays:  \n  - When using arrays you need to create a temporary array and then copy it to another like this:\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "py\ndef obj name {\n    arr str temp\n    prop arr str prop1 = temp\n    prop arr str prop2 = temp\n    prop arr str prop3 = temp\n    prop arr str prop4 = temp\n}\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\n### **Summary**:\n- **Full Paths Always**: Explicit references, such as " + Chr(96) + "Movable.Vehicles.Car.fuel" + Chr(96) + ", are mandatory in OSP. Always use the full path to reference objects. This avoids ambiguity and ensures that each object is uniquely identified within the code.\n- **Only Inside Methods**: The " + Chr(96) + "this" + Chr(96) + " keyword can only be used inside a method to refer to the calling object. It is not valid outside of a method because it requires the context of the method invocation to work correctly.\n- **Promotes Clarity**: These rules ensure consistency, clarity, and unambiguous functionality in OSP. By restricting the use of " + Chr(96) + "this" + Chr(96) + " to methods and requiring full paths, the code remains explicit and easier to follow.\n- **Helps with Debugging**: Since " + Chr(96) + "this" + Chr(96) + " is only valid inside methods, errors related to improper use are easier to detect. Using full paths also helps pinpoint issues more precisely by avoiding confusion with similarly named objects.\n- **Encourages Best Practices**: These guidelines encourage a more structured and organized approach to coding in OSP, fostering a clearer and more maintainable codebase in larger projects.\n\n---\n\n## Note:\n\n### Never use underscores when naming things in OSP. Otherwise, you can use them, but be cautious because underscores can be unstable.\n\n\n#### Example of OSP\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\nalliance Movable {\n    crew Vehicles {\n        def obj Car {\n            prop int door = 4\n            prop int fuel = 100\n            prop bool hasFUEL = true\n        }\n        def obj Bike {\n            prop bool hasGears = true\n            prop int energy = 100\n            prop bool hasENERGY = true\n        }\n\n        method void move(this) {\n            if (this == " + Chr(34) + "Movable.Vehicles.Car" + Chr(34) + ") {\n                if (Movable.Vehicles.Car.fuel " + Chr(62) + " 0) {\n                    print(" + Chr(34) + "The car is driving." + Chr(34) + ")\n                    Movable.Vehicles.Car.fuel = Movable.Vehicles.Car.fuel - 10\n                } else {\n                    print(" + Chr(34) + "The car is out of fuel." + Chr(34) + ")\n                    Movable.Vehicles.Car.hasFUEL = false\n                }\n            }\n            else if (this == " + Chr(34) + "Movable.Vehicles.Bike" + Chr(34) + ") {\n                if (Movable.Vehicles.Bike.energy " + Chr(62) + " 0) {\n                    print(" + Chr(34) + "The bike is pedaling." + Chr(34) + ")\n                    Movable.Vehicles.Bike.energy = Movable.Vehicles.Bike.energy - 5\n                } else {\n                    print(" + Chr(34) + "The bike is out of energy." + Chr(34) + ")\n                    Movable.Vehicles.Bike.hasENERGY = false\n                }\n            }\n        }\n    }\n    \n    crew settings {\n        def obj GeneralSettings {\n            prop str difficulty = " + Chr(34) + "normal" + Chr(34) + "\n            prop int volume = 50\n            prop str resolution = " + Chr(34) + "1920x1080" + Chr(34) + "\n        }\n        def obj AudioSettings {\n            prop int masterVolume = 70\n            prop int musicVolume = 50\n            prop int sfxVolume = 40\n        }\n        def obj DisplaySettings {\n            prop bool fullscreen = true\n            prop str aspectRatio = " + Chr(34) + "16:9" + Chr(34) + "\n        }\n    }\n    \n    crew actions {\n        // General Settings Methods\n        method void resetGeneralSettings() {\n            Movable.settings.GeneralSettings.difficulty = STR(" + Chr(34) + "normal" + Chr(34) + ")\n            Movable.settings.GeneralSettings.volume = 50\n            Movable.settings.GeneralSettings.resolution = STR(" + Chr(34) + "1920x1080" + Chr(34) + ")\n            print(" + Chr(34) + "General settings reset to default." + Chr(34) + ")\n        }\n        method void printGeneralSettings() {\n            print(" + Chr(34) + "General Settings:" + Chr(34) + ")\n            print(" + Chr(34) + "Difficulty: " + Chr(34) + " + Movable.settings.GeneralSettings.difficulty)\n            print(" + Chr(34) + "Volume: " + Chr(34) + " + STR(Movable.settings.GeneralSettings.volume))\n            print(" + Chr(34) + "Resolution: " + Chr(34) + " + Movable.settings.GeneralSettings.resolution)\n        }\n\n        // Audio Settings Methods\n        method void resetAudioSettings() {\n            Movable.settings.AudioSettings.masterVolume = 70\n            Movable.settings.AudioSettings.musicVolume = 50\n            Movable.settings.AudioSettings.sfxVolume = 40\n            print(" + Chr(34) + "Audio settings reset to default." + Chr(34) + ")\n        }\n        method void printAudioSettings() {\n            print(" + Chr(34) + "Audio Settings:" + Chr(34) + ")\n            print(" + Chr(34) + "Master Volume: " + Chr(34) + " + STR(Movable.settings.AudioSettings.masterVolume))\n            print(" + Chr(34) + "Music Volume: " + Chr(34) + " + STR(Movable.settings.AudioSettings.musicVolume))\n            print(" + Chr(34) + "SFX Volume: " + Chr(34) + " + STR(Movable.settings.AudioSettings.sfxVolume))\n        }\n\n        // Display Settings Methods\n        method void resetDisplaySettings() {\n            Movable.settings.DisplaySettings.fullscreen = true\n            Movable.settings.DisplaySettings.aspectRatio = STR(" + Chr(34) + "16:9" + Chr(34) + ")\n            print(" + Chr(34) + "Display settings reset to default." + Chr(34) + ")\n        }\n        method void printDisplaySettings() {\n            print(" + Chr(34) + "Display Settings:" + Chr(34) + ")\n            print(" + Chr(34) + "Fullscreen: " + Chr(34) + " + STR(Movable.settings.DisplaySettings.fullscreen))\n            print(" + Chr(34) + "Aspect Ratio: " + Chr(34) + " + Movable.settings.DisplaySettings.aspectRatio)\n        }\n    }\n\n    crew array {\n        def obj name {\n            arr str temp\n            prop arr str prop1 = temp\n            prop arr str prop2 = temp\n            prop arr str prop3 = temp\n            prop arr str prop4 = temp\n        }\n    }\n    \n}\n\nmain\n// Test vehicle movement\nwhile (Movable.Vehicles.Car.hasFUEL == true) && (Movable.Vehicles.Bike.hasENERGY = true) {\n    Movable.Vehicles.move(Movable.Vehicles.Car)\n    Movable.Vehicles.move(Movable.Vehicles.Bike)\n    print(" + Chr(34) + "=====================================" + Chr(34) + ")\n}\n\n// Test settings manipulation\nMovable.settings.GeneralSettings.difficulty = STR(" + Chr(34) + "hard" + Chr(34) + ")\nMovable.settings.GeneralSettings.volume = 80\nMovable.settings.GeneralSettings.resolution = STR(" + Chr(34) + "2560x1440" + Chr(34) + ")\nMovable.settings.AudioSettings.masterVolume = 90\nMovable.settings.AudioSettings.musicVolume = 60\nMovable.settings.AudioSettings.sfxVolume = 50\nMovable.settings.DisplaySettings.fullscreen = false\nMovable.settings.DisplaySettings.aspectRatio = STR(" + Chr(34) + "21:9" + Chr(34) + ")\n\nMovable.actions.printGeneralSettings()\nMovable.actions.printAudioSettings()\nMovable.actions.printDisplaySettings()\n\nMovable.actions.resetGeneralSettings()\nMovable.actions.resetAudioSettings()\nMovable.actions.resetDisplaySettings()\n\nMovable.actions.printGeneralSettings()\nMovable.actions.printAudioSettings()\nMovable.actions.printDisplaySettings()\n\n// Test array manipulation\nMovable.array.name.prop1.push(" + Chr(34) + "1text1" + Chr(34) + ")\nMovable.array.name.prop1.push(" + Chr(34) + "1text2" + Chr(34) + ")\nMovable.array.name.prop1.push(" + Chr(34) + "1text3" + Chr(34) + ")\nMovable.array.name.prop2.push(" + Chr(34) + "2text1" + Chr(34) + ")\nMovable.array.name.prop2.push(" + Chr(34) + "2text2" + Chr(34) + ")\nMovable.array.name.prop2.push(" + Chr(34) + "2text3" + Chr(34) + ")\nMovable.array.name.prop3.push(" + Chr(34) + "3text1" + Chr(34) + ")\nMovable.array.name.prop3.push(" + Chr(34) + "3text2" + Chr(34) + ")\nMovable.array.name.prop3.push(" + Chr(34) + "3text3" + Chr(34) + ")\nMovable.array.name.prop4.push(" + Chr(34) + "4text1" + Chr(34) + ")\nMovable.array.name.prop4.push(" + Chr(34) + "4text2" + Chr(34) + ")\nMovable.array.name.prop4.push(" + Chr(34) + "4text3" + Chr(34) + ")\n\n// why this\n// cuz python used len(param) insed of param.len() so it meses up evrything\n// if using OSP objects that have a dot (.) it doset work in python to get the lenght\n// but for a name whit no dots it works\n\narr str arrayTempOnlyGetSize1 = Movable.array.name.prop1\narr str arrayTempOnlyGetSize2 = Movable.array.name.prop2\narr str arrayTempOnlyGetSize3 = Movable.array.name.prop3\narr str arrayTempOnlyGetSize4 = Movable.array.name.prop4\n\n\n\n\nLoop, % arrayTempOnlyGetSize1.size() \n{\nprint(Movable.array.name.prop1[A_Index])\n}\nLoop, % arrayTempOnlyGetSize2.size() {\n    print(Movable.array.name.prop2[A_Index])\n}\nLoop, % arrayTempOnlyGetSize3.size() {\n    print(Movable.array.name.prop3[A_Index])\n}\nLoop, % arrayTempOnlyGetSize4.size() {\n    print(Movable.array.name.prop4[A_Index])\n}\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\nOSP simplifies programming while ensuring compatibility with **C++**, **Python**, and **JavaScript**.  \n\n---\n\n## Built-in Functions  \n\n[Go back](#htvm-documentation) \n\nHTVM includes a variety of built-in functions organized into categories for convenience.\n\n";
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
    for (int A_Index12 = 0; A_Index12 < categories.size() + 0; A_Index12++) {
        //print(categories[A_Index12])
        str1 = Trim(StrTitleCase(Trim(StrSplit(categories[A_Index12], "\n", 1)))) + " Functions";
        // 1. [String Functions](#string-functions)
        str2 = STR(A_Index12 + 1) + ". [" + str1 + "](#" + Trim(StrReplace(StrLower(str1), " ", "-")) + ")";
        outMD += str2 + "\n";
        // [Go back](#built-in-functions)
    }
    outMD += "\n---\n\n";
    std::string categoriesElement = "";
    for (int A_Index13 = 0; A_Index13 < categories.size() + 0; A_Index13++) {
        //print(categories[A_Index13])
        str1 = Trim(StrTitleCase(Trim(StrSplit(categories[A_Index13], "\n", 1)))) + " Functions";
        // ## String Functions
        str2 = "## " + Trim(str1) + "\n\n[Go back](#built-in-functions)\n\n";
        str10 = "[Go back](#" + Trim(StrReplace(StrLower(str1), " ", "-")) + ")";
        outMD += str2;
        // 1. [str1](#str1)
        // 2. [str2](#str2)
        // 3. [str3](#str3)
        categoriesElement = categories[A_Index13];
        std::vector<std::string> items14 = LoopParseFunc(categoriesElement, "\n", "\r");
        for (size_t A_Index14 = 0; A_Index14 < items14.size() + 0; A_Index14++) {
            std::string A_LoopField14 = items14[A_Index14 - 0];
            if (A_Index14 != 0) {
                if (Trim(A_LoopField14) != "") {
                    str1 = Trim(StrSplit(StrSplit(A_LoopField14, "|", 1), ":", 2));
                    str3 = STR(A_Index14) + ". [" + str1 + "](#" + Trim(StrReplace(StrLower(str1), " ", "-")) + ")";
                    outMD += str3 + "\n";
                }
            }
        }
        outMD += "\n---\n\n**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**\n\n**HTVM build-in functions availability.**\n\n| Functions | C++ | Python | JavaScript |\n|----------|----------|----------|----------|\n";
        std::vector<std::string> items15 = LoopParseFunc(categoriesElement, "\n", "\r");
        for (size_t A_Index15 = 0; A_Index15 < items15.size() + 0; A_Index15++) {
            std::string A_LoopField15 = items15[A_Index15 - 0];
            if (A_Index15 != 0) {
                if (Trim(A_LoopField15) != "") {
                    str1 = Trim(StrSplit(StrSplit(A_LoopField15, "|", 1), ":", 2));
                    // cpp py js
                    str4 = Trim(StrSplit(A_LoopField15, "|", 3));
                    str5 = Trim(StrSplit(A_LoopField15, "|", 4));
                    str6 = Trim(StrSplit(A_LoopField15, "|", 5));
                    // | str1 | Yes | No | Yes |
                    str3 = "| " + str1 + " | " + str4 + " | " + str5 + " | " + str6 + " |";
                    outMD += str3 + "\n";
                }
            }
        }
        outMD += "\n---\n\n";
        std::vector<std::string> items16 = LoopParseFunc(categoriesElement, "\n", "\r");
        for (size_t A_Index16 = 0; A_Index16 < items16.size() + 0; A_Index16++) {
            std::string A_LoopField16 = items16[A_Index16 - 0];
            if (A_Index16 != 0) {
                if (Trim(A_LoopField16) != "") {
                    str1 = Trim(StrSplit(StrSplit(A_LoopField16, "|", 1), ":", 2));
                    str2 = "### " + str1 + "\n\n" + Trim(str10) + "\n\n**HTVM build-in functions availability.**\n\n| Function | C++ | Python | JavaScript |\n|----------|----------|----------|----------|\n";
                    // cpp py js
                    str4 = Trim(StrSplit(A_LoopField16, "|", 3));
                    str5 = Trim(StrSplit(A_LoopField16, "|", 4));
                    str6 = Trim(StrSplit(A_LoopField16, "|", 5));
                    // | str1 | Yes | No | Yes |
                    str3 = "| " + str1 + " | " + str4 + " | " + str5 + " | " + str6 + " |";
                    str7 = "";
                    str8 = Trim(StrSplit(StrSplit(A_LoopField16, "|", 2), "description:", 2));
                    std::vector<std::string> items17 = LoopParseFunc(str8, "~~~");
                    for (size_t A_Index17 = 0; A_Index17 < items17.size() + 0; A_Index17++) {
                        std::string A_LoopField17 = items17[A_Index17 - 0];
                        if (A_Index17 != 0) {
                            if (A_LoopField17 != "") {
                                str7 += A_LoopField17 + "\n";
                            }
                        }
                    }
                    outMD += str2 + str3 + "\n\n" + str7 + "\n---\n\n";
                }
            }
        }
    }
    //print("=========================")
    //print("=========================")
    //print(outMDup . outMD)
    FileDelete("DOCUMENTATION.md");
    FileAppend(outMDup + outMD, "DOCUMENTATION.md");
    print("Everything is saved in DOCUMENTATION.md");
    print("Done!");
    return 0;
}
