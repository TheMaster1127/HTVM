#include <algorithm>
#include <any>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <regex>
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

std::string HTVM_getLang_HTVM() {
    return "cpp";
}


std::string instructionFileData = "";
std::string DOCS_params = "";
std::string DOCS_param1 = "";
std::string DOCS_param2 = "";
int checkIfFuncNameExists = 0;
std::string OUTdocs_HTML = "";
std::string OUTdocs_MD = "";
std::string genDocs(std::string mode) {
    std::string outDocs = "";
    if (Trim(instructionFileData) == "") {
        throw std::runtime_error("instructionFileData is empty");
        return "error: instructionFileData is empty!!!";
    }
    std::vector<std::string> items1 = LoopParseFunc(instructionFileData, "\n", "\r");
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        outDocs = "test out in " + mode;
    }
    outDocs = "still in development!!! test out in " + mode;
    return outDocs;
}
int main(int argc, char* argv[]) {
    if (HTVM_getLang_HTVM() != "js") {
        DOCS_params = Trim(GetParams());
        if (Trim(StrSplit(DOCS_params, "\n", 1)) == "") {
            print("Usage: <instruction_file> [function_name]" + Chr(10) + Chr(10) + "- <instruction_file>: Required. Generates DOCUMENTATION.md and DOCUMENTATION.html." + Chr(10) + "- [function_name]: Optional. If provided, checks whether the function exists and it does not output any files.");
            print("no params Exiting...");
            ExitApp();
        }
        std::vector<std::string> items2 = LoopParseFunc(DOCS_params, "\n", "\r");
        for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
            std::string A_LoopField2 = items2[A_Index2 - 0];
            if (A_Index2 == 0) {
                print(A_LoopField2);
                DOCS_param1 = Trim(A_LoopField2);
            }
            if (A_Index2 == 1) {
                print(A_LoopField2);
                DOCS_param2 = Trim(A_LoopField2);
            }
        }
        if (!FileExist(DOCS_param1)) {
            print("the file doesn't exist!!!");
            ExitApp();
        }
        if (Trim(DOCS_param2) != "") {
            checkIfFuncNameExists = 1;
        }
        if (checkIfFuncNameExists == 1) {
            print("[function_name] still in development!!!");
            print("Exiting...");
            ExitApp();
        } else {
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
    }
    // else add the full user instruction file in instructionFileData variable
    // MAKE SURE to put the instruction file in instructionFileData variable!!!
    // run genDocs("html") and the output will be text that needs to be saved in DOCUMENTATION.html
    // run genDocs("md") and the output will be text that needs to be saved in DOCUMENTATION.md
    return 0;
}