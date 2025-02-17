#include <algorithm>
#include <any>
#include <cstdint>
#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
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

// Function to get input from the user, similar to Python's input() function
std::string input(const std::string& prompt) {
    std::string userInput;
    std::cout << prompt; // Display the prompt to the user
    std::getline(std::cin, userInput); // Get the entire line of input
    return userInput;
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

int RegExMatch(const std::string& haystack, const std::string& needle) {
    std::regex re(needle);
    std::smatch match;
    if (std::regex_search(haystack, match, re)) {
        return match.position(0) + 1; // 1-based index
    }
    return 0; // No match
}

// Overload for std::vector<std::string>
void HTVM_Append(std::vector<std::string>& arr, const std::string& value) {
    arr.push_back(value);
}
// Overload for const char* (so you can pass string literals)
void HTVM_Append(std::vector<std::string>& arr, const char* value) {
    arr.push_back(std::string(value));
}
// General template for other vector types
template <typename T>
void HTVM_Append(std::vector<T>& arr, const T& value) {
    arr.push_back(value);
}

template <typename T>
size_t HTVM_Size(const std::vector<T>& arr) {
    return arr.size();
}


std::string ExtractDigits(std::string inputString) {
    std::string digits = "";
    std::vector<std::string> items1 = LoopParseFunc(inputString);
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        if (RegExMatch(A_LoopField1, "\\d")) {
            digits += A_LoopField1;
        }
    }
    return digits;
}
std::string fixGoAindexUnseen(std::string codeToFixTheGoUNSEEN) {
    std::string AindexKeyWOrd = "A_Index";
    // Regex to find all A_Index<num> occurrences
    std::vector<std::string> fixAindexInGoUnused;
    int howMany_fixAindexInGoUnused = 10;
    int howMany_fixAindexInGoUnusedNUM = 0;
    int found_fixAindexInGoUnused = 0;
    std::string foundWHAT_fixAindexInGoUnused = "";
    std::vector<std::string> items2 = LoopParseFunc(codeToFixTheGoUNSEEN, "\n", "\r");
    for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
        std::string A_LoopField2 = items2[A_Index2 - 0];
        if (RegExMatch(A_LoopField2, AindexKeyWOrd + "\\d+")) {
            if (SubStr(Trim(A_LoopField2), 1, 4) != "for ") {
                HTVM_Append(fixAindexInGoUnused, AindexKeyWOrd + ExtractDigits(StrSplit(A_LoopField2, AindexKeyWOrd, 2)));
            }
        }
    }
    for (int A_Index3 = 0; A_Index3 < howMany_fixAindexInGoUnused + 0; A_Index3++) {
        howMany_fixAindexInGoUnusedNUM = A_Index3;
        found_fixAindexInGoUnused = 0;
        foundWHAT_fixAindexInGoUnused = AindexKeyWOrd + STR(howMany_fixAindexInGoUnusedNUM);
        for (int A_Index4 = 0; A_Index4 < HTVM_Size(fixAindexInGoUnused) + 0; A_Index4++) {
            if (fixAindexInGoUnused[A_Index4] == AindexKeyWOrd + STR(howMany_fixAindexInGoUnusedNUM)) {
                found_fixAindexInGoUnused = 1;
                break;
            }
        }
        if (foundWHAT_fixAindexInGoUnused != "") {
            if (found_fixAindexInGoUnused == 0) {
                codeToFixTheGoUNSEEN = StrReplace(codeToFixTheGoUNSEEN, foundWHAT_fixAindexInGoUnused, "_");
            }
        }
    }
    return codeToFixTheGoUNSEEN;
}
int main(int argc, char* argv[]) {
    std::string code = "package main" + Chr(10) + "import (" + Chr(10) + "" + Chr(34) + "fmt" + Chr(34) + "" + Chr(10) + "" + Chr(34) + "regexp" + Chr(34) + "" + Chr(10) + ")" + Chr(10) + "" + Chr(10) + "func LoopParseFunc(varString string, delimiter1 string, delimiter2 string) []string {" + Chr(10) + "    var items []string" + Chr(10) + "    if delimiter1 == " + Chr(34) + "" + Chr(34) + " && delimiter2 == " + Chr(34) + "" + Chr(34) + " {" + Chr(10) + "        // If no delimiters are provided, convert string to slice of strings" + Chr(10) + "        items = make([]string, len(varString))" + Chr(10) + "        for i, c := range varString {" + Chr(10) + "            items[i] = string(c)" + Chr(10) + "        }" + Chr(10) + "    } else {" + Chr(10) + "        // Construct the regular expression pattern for splitting the string" + Chr(10) + "        pattern := fmt.Sprintf(" + Chr(34) + "[%s%s]+" + Chr(34) + ", delimiter1, delimiter2)" + Chr(10) + "        // Split the string using the constructed pattern" + Chr(10) + "        items = regexp.MustCompile(pattern).Split(varString, -1)" + Chr(10) + "    }" + Chr(10) + "    return items" + Chr(10) + "}" + Chr(10) + "" + Chr(10) + "func print(value interface{}) {" + Chr(10) + "	switch v := value.(type) {" + Chr(10) + "	case string:" + Chr(10) + "		fmt.Println(v)" + Chr(10) + "	case int, int32, int64:" + Chr(10) + "		fmt.Println(fmt.Sprintf(" + Chr(34) + "%d" + Chr(34) + ", v))" + Chr(10) + "	case float32, float64:" + Chr(10) + "		fmt.Println(fmt.Sprintf(" + Chr(34) + "%f" + Chr(34) + ", v))" + Chr(10) + "	case bool:" + Chr(10) + "		fmt.Println(fmt.Sprintf(" + Chr(34) + "%v" + Chr(34) + ", v))" + Chr(10) + "	default:" + Chr(10) + "		fmt.Println(" + Chr(34) + "Unsupported type" + Chr(34) + ")" + Chr(10) + "	}" + Chr(10) + "}" + Chr(10) + "" + Chr(10) + "func HTVM_Append[T any](arr *[]T, value T) {" + Chr(10) + "    *arr = append(*arr, value)" + Chr(10) + "}" + Chr(10) + "" + Chr(10) + "func HTVM_Size[T any](arr []T) int {" + Chr(10) + "    return len(arr)" + Chr(10) + "}" + Chr(10) + "" + Chr(10) + "" + Chr(10) + "func func1(var1 string) string {" + Chr(10) + "    return var1 + var1" + Chr(10) + "}" + Chr(10) + "func func2(var1 string) {" + Chr(10) + "    print(var1 + var1)" + Chr(10) + "}" + Chr(10) + "func func3(var1 string, __HTVM_V2_TO_GO_optionalParams__ ...interface{}) {" + Chr(10) + "    var2 := " + Chr(34) + "hello" + Chr(34) + "" + Chr(10) + "    if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " 0 {" + Chr(10) + "        var2 = __HTVM_V2_TO_GO_optionalParams__[0].(string)" + Chr(10) + "    }" + Chr(10) + "    print(var1 + " + Chr(34) + " " + Chr(34) + " + var2)" + Chr(10) + "}" + Chr(10) + "func main() {" + Chr(10) + "    print(func1(" + Chr(34) + "hi1" + Chr(34) + "))" + Chr(10) + "    func2(" + Chr(34) + "hi2" + Chr(34) + ")" + Chr(10) + "    func3(" + Chr(34) + "hi3" + Chr(34) + ")" + Chr(10) + "    func3(" + Chr(34) + "hi3" + Chr(34) + ", " + Chr(34) + "hello3" + Chr(34) + ")" + Chr(10) + "    var var1 int" + Chr(10) + "    var myArr0 []bool" + Chr(10) + "    HTVM_Append(&myArr0, true)" + Chr(10) + "    HTVM_Append(&myArr0, false)" + Chr(10) + "    HTVM_Append(&myArr0, true)" + Chr(10) + "    myArr := []int{5, 6, 7}" + Chr(10) + "    for A_Index1 := 0; A_Index1 " + Chr(60) + " 5 + 0; A_Index1++ {" + Chr(10) + "        var1 = 6" + Chr(10) + "        HTVM_Append(&myArr, A_Index1)" + Chr(10) + "    }" + Chr(10) + "    for A_Index2 := 0; A_Index2 " + Chr(60) + " HTVM_Size(myArr) + 0; A_Index2++ {" + Chr(10) + "        print(myArr[A_Index2])" + Chr(10) + "    }" + Chr(10) + "    for A_Index3 := 0; A_Index3 " + Chr(60) + " HTVM_Size(myArr0) + 0; A_Index3++ {" + Chr(10) + "        print(myArr0[A_Index3])" + Chr(10) + "    }" + Chr(10) + "    if (var1 == 6) {" + Chr(10) + "        print(var1)" + Chr(10) + "    } else if (var1 == 7) {" + Chr(10) + "        print(var1)" + Chr(10) + "    }" + Chr(10) + "    var var123 string = " + Chr(34) + "sdf" + Chr(92) + "naszdxgvh" + Chr(92) + "newsrdt" + Chr(92) + "nsdr" + Chr(92) + "rdfgcvbnb" + Chr(92) + "n" + Chr(92) + "rsdxfgcvn" + Chr(34) + "" + Chr(10) + "    items4 := LoopParseFunc(var123, " + Chr(34) + "" + Chr(92) + "n" + Chr(34) + ", " + Chr(34) + "" + Chr(92) + "r" + Chr(34) + ")" + Chr(10) + "    for A_Index4 , A_LoopField4 := range items4 {" + Chr(10) + "        if (A_Index4 == 0) {" + Chr(10) + "            print(A_Index4)" + Chr(10) + "        }" + Chr(10) + "        print(A_LoopField4)" + Chr(10) + "    }" + Chr(10) + "    print(" + Chr(34) + "==================" + Chr(34) + ")" + Chr(10) + "    var var1234 string = " + Chr(34) + "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg" + Chr(34) + "" + Chr(10) + "    items5 := LoopParseFunc(var1234, " + Chr(34) + "," + Chr(34) + ", " + Chr(34) + "" + Chr(34) + ")" + Chr(10) + "    for A_Index5 , A_LoopField5 := range items5 {" + Chr(10) + "        if (A_Index5 == 0) {" + Chr(10) + "            print(A_Index5)" + Chr(10) + "        }" + Chr(10) + "        print(A_LoopField5)" + Chr(10) + "    }" + Chr(10) + "    print(" + Chr(34) + "==================" + Chr(34) + ")" + Chr(10) + "    var var12345 string = " + Chr(34) + "hello" + Chr(34) + "" + Chr(10) + "    items6 := LoopParseFunc(var12345, " + Chr(34) + "" + Chr(34) + ", " + Chr(34) + "" + Chr(34) + ")" + Chr(10) + "    for A_Index6 , A_LoopField6 := range items6 {" + Chr(10) + "        print(A_LoopField6)" + Chr(10) + "    }" + Chr(10) + "}";
    print(fixGoAindexUnseen(code));
    return 0;
}
