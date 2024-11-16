#include <algorithm>
#include <any>
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


int main(int argc, char* argv[]) {
    std::string params = "";
    std::string param1 = "";
    std::string param2 = "";
    params = Trim(GetParams());
    if (Trim(params) == "") {
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
    if (checkIfFuncNameExists == 1) {
        int exitedLoopCheckIfFuncNameExists = 0;
        for (int A_Index3 = 0; A_Index3 < allFuncNames.size() + 0; A_Index3++) {
            if (param2 == Trim(allFuncNames[A_Index3])) {
                exitedLoopCheckIfFuncNameExists = 1;
            }
        }
        if (exitedLoopCheckIfFuncNameExists == 1) {
            print("the func alredy exists!!!");
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
    for (int A_Index6 = 0; A_Index6 < allFuncNames.size() + 0; A_Index6++) {
        print(allFuncNames[A_Index6]);
    }
    return 0;
}