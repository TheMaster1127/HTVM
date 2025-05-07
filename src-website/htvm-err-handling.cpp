#include <algorithm>
#include <any>
#include <cmath>
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
    std::cout << value << std::endl;
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

// Function to find the position of needle in haystack (std::string overload)
int InStr(const std::string& haystack, const std::string& needle) {
    size_t pos = haystack.find(needle);
    return (pos != std::string::npos) ? static_cast<int>(pos) + 1 : 0;
}

size_t StrLen(const std::string& str) {
    return str.length();
}

double Exp(double value) {
    return std::exp(value);
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

std::string StringTrimLeft(const std::string &input, int numChars) {
    return (numChars <= input.length()) ? input.substr(numChars) : input;
}

std::string StringTrimRight(const std::string &input, int numChars) {
    return (numChars <= input.length()) ? input.substr(0, input.length() - numChars) : input;
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

int RegExMatch(const std::string& haystack, const std::string& needle) {
    std::regex re(needle);
    std::smatch match;
    if (std::regex_search(haystack, match, re)) {
        return match.position(0) + 1; // 1-based index
    }
    return 0; // No match
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

// IndexOf for std::vector<std::string>
int HTVM_IndexOf(const std::vector<std::string>& arr, const std::string& value) {
    auto it = std::find(arr.begin(), arr.end(), value);
    return (it != arr.end()) ? static_cast<int>(std::distance(arr.begin(), it)) : -1;
}
// Overload for string literals
int HTVM_IndexOf(const std::vector<std::string>& arr, const char* value) {
    return HTVM_IndexOf(arr, std::string(value));
}
// IndexOf for std::vector<int>
int HTVM_IndexOf(const std::vector<int>& arr, int value) {
    auto it = std::find(arr.begin(), arr.end(), value);
    return (it != arr.end()) ? static_cast<int>(std::distance(arr.begin(), it)) : -1;
}
// IndexOf for std::vector<float>
int HTVM_IndexOf(const std::vector<float>& arr, float value) {
    auto it = std::find(arr.begin(), arr.end(), value);
    return (it != arr.end()) ? static_cast<int>(std::distance(arr.begin(), it)) : -1;
}
// IndexOf for std::vector<bool>
int HTVM_IndexOf(const std::vector<bool>& arr, bool value) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == value) {
            return static_cast<int>(i);
        }
    }
    return -1;
}


int main(int argc, char* argv[]) {
    // htvm-err-handling.htvm
    // Helper function to check for disallowed characters based on mode.
    // Mode 0: Check if any disallowed char exists anywhere in the line.
    // Mode 1: Check if any disallowed char exists ONLY at the beginning of the line.
    // Mode 2: Check if any disallowed char exists ONLY at the end of the line.
    // Returns true if a disallowed character is found according to the mode, false otherwise.
    bool handleErrorHelper(std::vector<std::string> theArray, std::string line, int mode = 0) {
        if (mode == 0) {
            bool found = false;
            for (int A_Index1 = 0; A_Index1 < HTVM_Size(theArray) + 0; A_Index1++) {
                if (InStr(line, theArray[A_Index1])) {
                    found = true;
                    break;
                }
            }
            return found;
        }
        else if (mode == 1) {
            if (StrLen(line) == 0) {
                return false;
            }
            std::string firstChar = SubStr(line, 1, 1);
            bool foundAtStart = false;
            for (int A_Index2 = 0; A_Index2 < HTVM_Size(theArray) + 0; A_Index2++) {
                if (firstChar == theArray[A_Index2]) {
                    foundAtStart = true;
                    break;
                }
            }
            return foundAtStart;
        }
        else if (mode == 2) {
            int len = StrLen(line);
            if (len == 0) {
                return false;
            }
            std::string lastChar = SubStr(line, len, 1);
            bool foundAtEnd = false;
            for (int A_Index3 = 0; A_Index3 < HTVM_Size(theArray) + 0; A_Index3++) {
                if (lastChar == theArray[A_Index3]) {
                    foundAtEnd = true;
                    break;
                }
            }
            return foundAtEnd;
        }
        return false;
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    // Function to check for duplicate first words in a multi-line string
    // Returns true if a duplicate first word is found, false otherwise.
    std::string handleErrorHelper2(std::string multiLineText) {
        std::vector<std::string> uniqueFirstWordsEncountered = {};
        std::vector<int> firstOccurrenceIndices = {};
        std::vector<std::string> firstOccurrenceLines = {};
        int currentLine0BasedIndex = 0;
        std::vector<std::string> items4 = LoopParseFunc(multiLineText, "\n");
        for (size_t A_Index4 = 0; A_Index4 < items4.size() + 0; A_Index4++) {
            std::string A_LoopField4 = items4[A_Index4 - 0];
            std::string trimmedCurrentLine = Trim(A_LoopField4);
            if (trimmedCurrentLine != "") {
                std::string firstWord = StrSplit(trimmedCurrentLine, " ", 1);
                if (firstWord != "") {
                    int indexOfExisting = HTVM_IndexOf(uniqueFirstWordsEncountered, firstWord);
                    if (indexOfExisting != -1) {
                        int originalIndex = firstOccurrenceIndices[indexOfExisting];
                        std::string originalLine = firstOccurrenceLines[indexOfExisting];
                        std::string result = STR(originalIndex) + ":" + originalLine + "-HTVM-SPLIT-HTVM~~|kngeuew8r7dygtosuwesdtesedfxo|~~HTVM-SPLIT-HTVM-" + STR(currentLine0BasedIndex) + ":" + trimmedCurrentLine;
                        return result;
                    } else {
                        HTVM_Append(uniqueFirstWordsEncountered, firstWord);
                        HTVM_Append(firstOccurrenceIndices, currentLine0BasedIndex);
                        HTVM_Append(firstOccurrenceLines, trimmedCurrentLine);
                    }
                }
            }
            currentLine0BasedIndex = currentLine0BasedIndex + 1;
        }
        return "NONE";
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    std::string handleError(std::string htvmInstrText) {
        std::string fixTrim = "";
        std::vector<std::string> items5 = LoopParseFunc(htvmInstrText, "\n", "\r");
        for (size_t A_Index5 = 0; A_Index5 < items5.size() + 0; A_Index5++) {
            std::string A_LoopField5 = items5[A_Index5 - 0];
            fixTrim += Trim(A_LoopField5) + Chr(10);
        }
        htvmInstrText = StringTrimRight(fixTrim, 1);
        // double quote newline carriage return
        std::vector<std::string> disallowedChars_Globaly = {Chr(34), Chr(10), Chr(13)};
        std::string disallowedChars_Globaly_EXPLAIN = "double quote, newline, carriage return";
        // "double quote newline carriage return ( ) [ ] { }"
        std::vector<std::string> disallowedChars_InExprTranspiler = {Chr(34), Chr(10), Chr(13), Chr(40), Chr(41), Chr(91), Chr(93), Chr(123), Chr(125)};
        std::string disallowedChars_InExprTranspiler_EXPLAIN = "double quote, newline, carriage return, (, ), [, ], {, }";
        // "double quote newline carriage return ( ) [ ] { }"
        std::vector<std::string> disallowedChars_BeginEndLine = {Chr(34), Chr(10), Chr(13), Chr(40), Chr(41), Chr(91), Chr(93), Chr(123), Chr(125)};
        std::string disallowedChars_BeginEndLine_EXPLAIN = "double quote, newline, carriage return, (, ), [, ], {, }";
        // "double quote newline carriage return ( ) [ ] { } :"
        std::vector<std::string> disallowedChars_AT_THE_END = {Chr(34), Chr(10), Chr(13), Chr(40), Chr(41), Chr(91), Chr(93), Chr(123), Chr(125), Chr(58)};
        std::string disallowedChars_AT_THE_END_EXPLAIN = "double quote, newline, carriage return, (, ), [, ], {, }, :";
        // "double quote newline carriage return ( ) { }"
        std::vector<std::string> disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD = {Chr(34), Chr(10), Chr(13), Chr(40), Chr(41), Chr(123), Chr(125)};
        std::string disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD_EXPLAIN = "double quote, newline, carriage return, (, ), {, }";
        // "double quote newline carriage return ( ) { } :"
        std::vector<std::string> disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD = {Chr(34), Chr(10), Chr(13), Chr(40), Chr(41), Chr(123), Chr(125), Chr(58)};
        std::string disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD_EXPLAIN = "double quote, newline, carriage return, (, ), {, }, :";
        // special/isolated
        // newline carriage return
        std::vector<std::string> disallowedChars_For_2 = {Chr(10), Chr(13)};
        std::string disallowedChars_For_2_EXPLAIN = "newline, carriage return";
        // double quote newline carriage return :
        std::vector<std::string> disallowedChars_For_46_47 = {Chr(34), Chr(10), Chr(13), Chr(58)};
        std::string disallowedChars_For_46_47_EXPLAIN = "double quote, newline, carriage return, :";
        // double quote newline carriage return
        std::vector<std::string> disallowedChars_For_103 = {Chr(34), Chr(10), Chr(13)};
        std::string disallowedChars_For_103_EXPLAIN = "double quote, newline, carriage return";
        // lines that cant have spacses
        std::vector<int> lineThatCANNOThaveSpacses = {0, 1, 46, 47, 84, 85, 86, 87, 88, 89, 103, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161};
        // special stuff
        // 0. we can only have those
        std::vector<std::string> onlyAllowed_0 = {"cpp", "py", "js", "go", "lua", "cs", "java", "kt", "rb", "nim", "ahk", "swift", "dart", "ts", "groovy"};
        // 1. for matching custom file extensions in HTVM we only allow them to start with a lowercase letter, followed by lowercase letters or numbers, and be at least 2 characters long.
        // This is the regex: "^[a-z][a-z0-9]{1,}$"
        // 2. this is complex so um i will just leave it and just use disallowedChars_For_2 array to check if any of those chars exists.
        // 3 - 9 - for OSP and include - so just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine, disallowedChars_AT_THE_END
        // 10 - 45 - programming blocks - so just use the following arrays disallowedChars_Globaly
        // 46 and 47 - this are keyWordCurlyBraceOpen and keyWordCurlyBraceClose so no spacses and use the arrays disallowedChars_For_46_47, disallowedChars_Globaly
        // 48 - 83 - types and constructs - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine, disallowedChars_AT_THE_END
        // 84 - 89 - array methods - for the array methods, they must have NO SPACE and must start with a dot (.) followed by at least one character from [A-Za-z0-9_]. Use the regex "^\\.[A-Za-z0-9_]+$"
        // 90 - 102 - ArrayDefinition and some more - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD
        // 103 is the keyWordEscpaeChar so it must be any char BUT MUST BE 1 single char NOT MORE THEN 1 CHAR and use the array disallowedChars_Globaly, disallowedChars_For_103
        // 104 - 128 - some operators - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine, disallowedChars_AT_THE_END
        // 129 - 141 - for Assignment operators - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD AND NO SPACSES
        // 142 and 143 - the ternary operators - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD
        // 144 and 145 - (++ and --) - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine, disallowedChars_AT_THE_END
        // 146 - Use the regex "^-?\\d+$" ONLY and disallowedChars_Globaly ig
        // 147 and 148 - A_Index and A_LoopField ARE CUSTOMIZABLE so NO SPACE and use the arrays disallowedChars_Globaly and Use the regex "^[a-zA-Z_][a-zA-Z0-9_]*$"
        // 149 - 161 - settings ONLY allow "on" and "off" THATS IT but the website will automatically handle it since it's a toggle switch and will put "on" or "off"
        //;;;;;;;;;;;;;;;;;;;;;;; thats all HTVM options 162 of them
        std::string allName = "langToConvertTo" + Chr(10) + "langFileExtension" + Chr(10) + "commands" + Chr(10) + "keyWordAlliance" + Chr(10) + "keyWordCrew" + Chr(10) + "keyWordProc" + Chr(10) + "keyWordStruct" + Chr(10) + "keyWordProp" + Chr(10) + "keyWordThis" + Chr(10) + "keyWordInclude" + Chr(10) + "keyWordCodeInTheTranspiledLangStart" + Chr(10) + "keyWordCodeInTheTranspiledLangEnd" + Chr(10) + "keyWordCodeInTheTranspiledLangStartCPP" + Chr(10) + "keyWordCodeInTheTranspiledLangEndCPP" + Chr(10) + "keyWordCodeInTheTranspiledLangStartPY" + Chr(10) + "keyWordCodeInTheTranspiledLangEndPY" + Chr(10) + "keyWordCodeInTheTranspiledLangStartJS" + Chr(10) + "keyWordCodeInTheTranspiledLangEndJS" + Chr(10) + "keyWordCodeInTheTranspiledLangStartGO" + Chr(10) + "keyWordCodeInTheTranspiledLangEndGO" + Chr(10) + "keyWordCodeInTheTranspiledLangStartLUA" + Chr(10) + "keyWordCodeInTheTranspiledLangEndLUA" + Chr(10) + "keyWordCodeInTheTranspiledLangStartCS" + Chr(10) + "keyWordCodeInTheTranspiledLangEndCS" + Chr(10) + "keyWordCodeInTheTranspiledLangStartJAVA" + Chr(10) + "keyWordCodeInTheTranspiledLangEndJAVA" + Chr(10) + "keyWordCodeInTheTranspiledLangStartKT" + Chr(10) + "keyWordCodeInTheTranspiledLangEndKT" + Chr(10) + "keyWordCodeInTheTranspiledLangStartRB" + Chr(10) + "keyWordCodeInTheTranspiledLangEndRB" + Chr(10) + "keyWordCodeInTheTranspiledLangStartNIM" + Chr(10) + "keyWordCodeInTheTranspiledLangEndNIM" + Chr(10) + "keyWordCodeInTheTranspiledLangStartAHK" + Chr(10) + "keyWordCodeInTheTranspiledLangEndAHK" + Chr(10) + "keyWordCodeInTheTranspiledLangStartSWIFT" + Chr(10) + "keyWordCodeInTheTranspiledLangEndSWIFT" + Chr(10) + "keyWordCodeInTheTranspiledLangStartDART" + Chr(10) + "keyWordCodeInTheTranspiledLangEndDART" + Chr(10) + "keyWordCodeInTheTranspiledLangStartTS" + Chr(10) + "keyWordCodeInTheTranspiledLangEndTS" + Chr(10) + "keyWordCodeInTheTranspiledLangStartGROOVY" + Chr(10) + "keyWordCodeInTheTranspiledLangEndGROOVY" + Chr(10) + "keyWordCodeInTheTranspiledLangStartHTVM" + Chr(10) + "keyWordCodeInTheTranspiledLangEndHTVM" + Chr(10) + "keyWordCodeInHTVMstart" + Chr(10) + "keyWordCodeInHTVMend" + Chr(10) + "keyWordCurlyBraceOpen" + Chr(10) + "keyWordCurlyBraceClose" + Chr(10) + "keyWordNull" + Chr(10) + "keyWordTrue" + Chr(10) + "keyWordFalse" + Chr(10) + "keyWordVoid" + Chr(10) + "keyWordDouble" + Chr(10) + "keyWordChar" + Chr(10) + "keyWordUint8" + Chr(10) + "keyWordUint16" + Chr(10) + "keyWordUint32" + Chr(10) + "keyWordUint64" + Chr(10) + "keyWordINT" + Chr(10) + "keyWordSTR" + Chr(10) + "keyWordBOOL" + Chr(10) + "keyWordFLOAT" + Chr(10) + "keyWordINT8" + Chr(10) + "keyWordINT16" + Chr(10) + "keyWordINT32" + Chr(10) + "keyWordINT64" + Chr(10) + "keyWordIF" + Chr(10) + "keyWordElseIf" + Chr(10) + "keyWordElse" + Chr(10) + "keyWordWhileLoop" + Chr(10) + "keyWordLoopInfinite" + Chr(10) + "keyWordLoop" + Chr(10) + "keyWordLoopParse" + Chr(10) + "keyWordContinue" + Chr(10) + "keyWordBreak" + Chr(10) + "keyWordFunc" + Chr(10) + "keyWordAwait" + Chr(10) + "keyWordAsync" + Chr(10) + "keyWordThrow" + Chr(10) + "keyWordErrorMsg" + Chr(10) + "keyWordTry" + Chr(10) + "keyWordCatch" + Chr(10) + "keyWordFinally" + Chr(10) + "keyWordReturnStatement" + Chr(10) + "keyWordArrayAppend" + Chr(10) + "keyWordArrayPop" + Chr(10) + "keyWordArraySize" + Chr(10) + "keyWordArrayInsert" + Chr(10) + "keyWordArrayRemove" + Chr(10) + "keyWordArrayIndexOf" + Chr(10) + "keyWordArrayDefinition" + Chr(10) + "keyWordArrayOfIntegersDefinition" + Chr(10) + "keyWordArrayOfStringsDefinition" + Chr(10) + "keyWordArrayOfFloatingPointNumbersDefinition" + Chr(10) + "keyWordArrayOfBooleansDefinition" + Chr(10) + "keyWordVar" + Chr(10) + "keyWordLet" + Chr(10) + "keyWordConst" + Chr(10) + "keyWordEnd" + Chr(10) + "keyWordGlobal" + Chr(10) + "keyWordComment" + Chr(10) + "keyWordCommentOpenMultiLine" + Chr(10) + "keyWordCommentCloseMultiLine" + Chr(10) + "keyWordEscpaeChar" + Chr(10) + "keyWordMainLabel" + Chr(10) + "keyWordConcat" + Chr(10) + "keyWordAdd" + Chr(10) + "keyWordSub" + Chr(10) + "keyWordMul" + Chr(10) + "keyWordDiv" + Chr(10) + "keyWordMod" + Chr(10) + "keyWordExp" + Chr(10) + "keyWordEqual" + Chr(10) + "keyWordStrictEqual" + Chr(10) + "keyWordNotEqual" + Chr(10) + "keyWordGreater" + Chr(10) + "keyWordLess" + Chr(10) + "keyWordGreaterEqual" + Chr(10) + "keyWordLessEqual" + Chr(10) + "keyWordAnd" + Chr(10) + "keyWordOr" + Chr(10) + "keyWordNot" + Chr(10) + "keyWordBitAnd" + Chr(10) + "keyWordBitOr" + Chr(10) + "keyWordBitXor" + Chr(10) + "keyWordBitNot" + Chr(10) + "keyWordShiftLeft" + Chr(10) + "keyWordShiftRight" + Chr(10) + "keyWordShiftUnsignedRight" + Chr(10) + "keyWordAssign" + Chr(10) + "keyWordAssignAdd" + Chr(10) + "keyWordAssignConcat" + Chr(10) + "keyWordAssignSub" + Chr(10) + "keyWordAssignMul" + Chr(10) + "keyWordAssignDiv" + Chr(10) + "keyWordAssignMod" + Chr(10) + "keyWordAssignShiftLeft" + Chr(10) + "keyWordAssignShiftRight" + Chr(10) + "keyWordLogicalAssignShiftRight" + Chr(10) + "keyWordAssignBitAnd" + Chr(10) + "keyWordAssignBitOr" + Chr(10) + "keyWordAssignBitXor" + Chr(10) + "keyWordTernary1" + Chr(10) + "keyWordTernary2" + Chr(10) + "keyWordInc" + Chr(10) + "keyWordDec" + Chr(10) + "AHKlikeLoopsIndexedAt" + Chr(10) + "keyWordAIndex" + Chr(10) + "keyWordALoopField" + Chr(10) + "useCurlyBraces" + Chr(10) + "useEnd" + Chr(10) + "useSemicolon" + Chr(10) + "useParentheses" + Chr(10) + "usePrefixTypeForTypeDefinition" + Chr(10) + "usePostfixTypeForTypeDefinition" + Chr(10) + "usePythonicColonSyntax" + Chr(10) + "useCurlyBracesSyntaxForArrayDef" + Chr(10) + "useInJavaScriptAlwaysUseVar" + Chr(10) + "useJavaScriptInAfullHTMLfile" + Chr(10) + "useJavaScriptAmainFuncDef" + Chr(10) + "useJavaScriptAllFuncsAreAsync" + Chr(10) + "useJavaScriptAlwaysTripleEqual";
        std::vector<std::string> allNameARR;
        std::vector<std::string> items6 = LoopParseFunc(allName, "\n", "\r");
        for (size_t A_Index6 = 0; A_Index6 < items6.size() + 0; A_Index6++) {
            std::string A_LoopField6 = items6[A_Index6 - 0];
            HTVM_Append(allNameARR, A_LoopField6);
        }
        std::string str1 = "";
        std::string str2 = "";
        std::string str3 = "";
        std::string str4 = "";
        std::string str5 = "";
        std::string str6 = "";
        int for0 = 0;
        int AIndex = 0;
        std::string ALoopField = "";
        std::string handleErrorHelper2OUT = "";
        handleErrorHelper2OUT = handleErrorHelper2(htvmInstrText);
        if (handleErrorHelper2OUT != "NONE") {
            str1 = StrSplit(handleErrorHelper2OUT, "-HTVM-SPLIT-HTVM~~|kngeuew8r7dygtosuwesdtesedfxo|~~HTVM-SPLIT-HTVM-", 1);
            str2 = StrSplit(handleErrorHelper2OUT, "-HTVM-SPLIT-HTVM~~|kngeuew8r7dygtosuwesdtesedfxo|~~HTVM-SPLIT-HTVM-", 2);
            str3 = "";
            str4 = "";
            std::vector<std::string> items7 = LoopParseFunc(str1);
            for (size_t A_Index7 = 0; A_Index7 < items7.size() + 0; A_Index7++) {
                std::string A_LoopField7 = items7[A_Index7 - 0];
                if (A_LoopField7 == ":") {
                    break;
                } else {
                    str3 += A_LoopField7;
                }
            }
            std::vector<std::string> items8 = LoopParseFunc(str2);
            for (size_t A_Index8 = 0; A_Index8 < items8.size() + 0; A_Index8++) {
                std::string A_LoopField8 = items8[A_Index8 - 0];
                if (A_LoopField8 == ":") {
                    break;
                } else {
                    str4 += A_LoopField8;
                }
            }
            str5 = StringTrimLeft(str1, (StrLen(str3) + 1));
            str6 = StringTrimLeft(str2, (StrLen(str4) + 1));
            // 51 66
            // 90 94
            if ((INT(str3) >= 51 && INT(str3) <= 66) || (INT(str3) >= 90 && INT(str3) <= 94) || (INT(str3) >= 10 && INT(str3) <= 45)) {
                str1 = "";
                str2 = "";
                str3 = "";
                str4 = "";
                str5 = "";
                str6 = "";
            } else {
                str1 = allNameARR[INT(str3)];
                str2 = allNameARR[INT(str4)];
                return str3 + "|" + str1 + " and " + str2 + " have the same word at the beginning and we can't have the same first word for different keywords!!!";
            }
        }
        std::vector<std::string> items9 = LoopParseFunc(htvmInstrText, "\n", "\r");
        for (size_t A_Index9 = 0; A_Index9 < items9.size() + 0; A_Index9++) {
            std::string A_LoopField9 = items9[A_Index9 - 0];
            AIndex = A_Index9;
            ALoopField = A_LoopField9;
            for (int A_Index10 = 0; A_Index10 < HTVM_Size(lineThatCANNOThaveSpacses) + 0; A_Index10++) {
                if (AIndex == lineThatCANNOThaveSpacses[A_Index10] && InStr(ALoopField, " ")) {
                    return STR(AIndex) + "|You can't use a space here!!!.";
                }
            }
            // retun format is
            // index|error msg
            std::vector<std::string> items11 = LoopParseFunc(htvmInstrText, "\n", "\r");
            for (size_t A_Index11 = 0; A_Index11 < items11.size() + 0; A_Index11++) {
                std::string A_LoopField11 = items11[A_Index11 - 0];
                if (ALoopField == A_LoopField11 && A_Index11 != AIndex) {
                    if (AIndex <= 148) {
                        return STR(AIndex) + "|You can't use the same keyword more than once. The problem is whit " + allNameARR[AIndex] + " and " + allNameARR[A_Index11] + "!!!";
                    }
                }
            }
            if (A_Index9 == 0) {
                // Code for condition 0
                for (int A_Index12 = 0; A_Index12 < HTVM_Size(onlyAllowed_0) + 0; A_Index12++) {
                    if (A_LoopField9 == onlyAllowed_0[A_Index12]) {
                        for0 = 1;
                    }
                }
                if (for0 == 0) {
                    return STR(A_Index9) + "|You can only use: " + "" + Chr(34) + "cpp" + Chr(34) + ", " + Chr(34) + "py" + Chr(34) + ", " + Chr(34) + "js" + Chr(34) + ", " + Chr(34) + "go" + Chr(34) + ", " + Chr(34) + "lua" + Chr(34) + ", " + Chr(34) + "cs" + Chr(34) + ", " + Chr(34) + "java" + Chr(34) + ", " + Chr(34) + "kt" + Chr(34) + ", " + Chr(34) + "rb" + Chr(34) + ", " + Chr(34) + "nim" + Chr(34) + ", " + Chr(34) + "ahk" + Chr(34) + ", " + Chr(34) + "swift" + Chr(34) + ", " + Chr(34) + "dart" + Chr(34) + ", " + Chr(34) + "ts" + Chr(34) + ", " + Chr(34) + "groovy" + Chr(34);
                }
            }
            else if (A_Index9 == 1) {
                // Code for condition 1
                if (RegExMatch(A_LoopField9, "^[a-z][a-z0-9]{1,}$") == false) {
                    return STR(A_Index9) + "|The file name must start with a lowercase letter and can only contain lowercase letters or numbers afterward.";
                }
            }
            else if (A_Index9 == 2) {
                // Code for condition 2
                if (InStr(A_LoopField9, Chr(13)) || InStr(A_LoopField9, Chr(10))) {
                    return STR(A_Index9) + "|Dont use a newline or a carriage retrun";
                }
            }
            else if (A_Index9 >= 3 && A_Index9 <= 9) {
                // Code for conditions 3 - 9 (OSP and include)
                if (handleErrorHelper(disallowedChars_Globaly, A_LoopField9) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField9, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField9, 2)) {
                    return STR(A_Index9) + "|You can't use the folowing characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
                }
            }
            else if (A_Index9 >= 10 && A_Index9 <= 45) {
                if (handleErrorHelper(disallowedChars_Globaly, A_LoopField9) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField9, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField9, 2)) {
                    return STR(A_Index9) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
                }
            }
            else if (A_Index9 >= 46 && A_Index9 <= 47) {
                if (handleErrorHelper(disallowedChars_For_46_47, A_LoopField9) || handleErrorHelper(disallowedChars_Globaly, A_LoopField9)) {
                    return STR(A_Index9) + "|You can't use the following characters: " + disallowedChars_For_46_47_EXPLAIN + ", " + disallowedChars_Globaly_EXPLAIN;
                }
            }
            else if (A_Index9 >= 48 && A_Index9 <= 83) {
                if (handleErrorHelper(disallowedChars_Globaly, A_LoopField9) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField9, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField9, 2)) {
                    return STR(A_Index9) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
                }
            }
            else if (A_Index9 >= 84 && A_Index9 <= 89) {
                if (RegExMatch(A_LoopField9, "^\\.[A-Za-z0-9_]+$") == false) {
                    return STR(A_Index9) + "|Array methods must start with a dot and contain only alphanumeric characters or underscores.";
                }
            }
            else if (A_Index9 >= 90 && A_Index9 <= 102) {
                if (handleErrorHelper(disallowedChars_Globaly, A_LoopField9) || handleErrorHelper(disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, A_LoopField9, 1) || handleErrorHelper(disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD, A_LoopField9, 2)) {
                    return STR(A_Index9) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD_EXPLAIN + ", " + disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD_EXPLAIN;
                }
            }
            else if (A_Index9 == 103) {
                if (StrLen(A_LoopField9) != 1 || handleErrorHelper(disallowedChars_Globaly, A_LoopField9) || handleErrorHelper(disallowedChars_For_103, A_LoopField9)) {
                    return STR(A_Index9) + "|Escape character must be a single valid character.";
                }
            }
            else if (A_Index9 >= 104 && A_Index9 <= 128) {
                if (handleErrorHelper(disallowedChars_Globaly, A_LoopField9) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField9, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField9, 2)) {
                    return STR(A_Index9) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
                }
            }
            else if (A_Index9 >= 129 && A_Index9 <= 141) {
                if (handleErrorHelper(disallowedChars_Globaly, A_LoopField9) || handleErrorHelper(disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, A_LoopField9, 1) || handleErrorHelper(disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD, A_LoopField9, 2) || InStr(A_LoopField9, " ")) {
                    return STR(A_Index9) + "|Assignment operators can't contain spaces and can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD_EXPLAIN + ", " + disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD_EXPLAIN;
                }
            }
            else if (A_Index9 >= 142 && A_Index9 <= 143) {
                if (handleErrorHelper(disallowedChars_Globaly, A_LoopField9) || handleErrorHelper(disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, A_LoopField9, 1)) {
                    return STR(A_Index9) + "|Ternary operators can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD_EXPLAIN;
                }
            }
            else if (A_Index9 >= 144 && A_Index9 <= 145) {
                if (handleErrorHelper(disallowedChars_Globaly, A_LoopField9) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField9, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField9, 2)) {
                    return STR(A_Index9) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
                }
            }
            else if (A_Index9 == 146) {
                if (RegExMatch(A_LoopField9, "^-?\\d+$") == false) {
                    return STR(A_Index9) + "|Value must be a valid integer (optionally negative).";
                }
            }
            else if (A_Index9 >= 147 && A_Index9 <= 148) {
                if (RegExMatch(A_LoopField9, "^[a-zA-Z_][a-zA-Z0-9_]*$") == false) {
                    return STR(A_Index9) + "|Variable names must start with a letter or underscore, and contain only alphanumeric characters and underscores.";
                }
            }
            else if (A_Index9 >= 149 && A_Index9 <= 161) {
                if (A_LoopField9 != "on" && A_LoopField9 != "off") {
                    return STR(A_Index9) + "|Settings can only be 'on' or 'off'.";
                }
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;
            if (A_Index9 == 161) {
                break;
            }
        }
        return "noERROR";
    }
    //main
    //print(handleError("cpp" . Chr(10) . "htvm" . Chr(10) . "StringTrimLeft,OUTVAR,INVAR,param1|StringTrimRight,OUTVAR,INVAR,param1|Random,OUTVAR,param1,param2|Sleep,INVAR|FileRead,OUTVAR,'param1|FileAppend,INVAR,'param1|FileDelete,'INVAR|Sort,INOUTVAR,'param1|MsgBox,'param1" . Chr(10) . "alliance" . Chr(10) . "crew" . Chr(10) . "proc" . Chr(10) . "struct" . Chr(10) . "prop" . Chr(10) . "this" . Chr(10) . "import" . Chr(10) . "___start" . Chr(10) . "___end" . Chr(10) . "___cpp start" . Chr(10) . "___cpp end" . Chr(10) . "___py start" . Chr(10) . "___py end" . Chr(10) . "___js start" . Chr(10) . "___js end" . Chr(10) . "___go start" . Chr(10) . "___go end" . Chr(10) . "___lua start" . Chr(10) . "___lua end" . Chr(10) . "___cs start" . Chr(10) . "___cs end" . Chr(10) . "___java start" . Chr(10) . "___java end" . Chr(10) . "___kt start" . Chr(10) . "___kt end" . Chr(10) . "___rb start" . Chr(10) . "___rb end" . Chr(10) . "___nim start" . Chr(10) . "___nim end" . Chr(10) . "___ahk start" . Chr(10) . "___ahk end" . Chr(10) . "___swift start" . Chr(10) . "___swift end" . Chr(10) . "___dart start" . Chr(10) . "___dart end" . Chr(10) . "___ts start" . Chr(10) . "___ts end" . Chr(10) . "___groovy start" . Chr(10) . "___groovy end" . Chr(10) . "___htvm start" . Chr(10) . "___htvm end" . Chr(10) . "___inhtvm start" . Chr(10) . "___inhtvm end" . Chr(10) . "{" . Chr(10) . "}" . Chr(10) . "null" . Chr(10) . "true" . Chr(10) . "false" . Chr(10) . "void" . Chr(10) . "double" . Chr(10) . "char" . Chr(10) . "uint8" . Chr(10) . "uint16" . Chr(10) . "uint32" . Chr(10) . "uint64" . Chr(10) . "int" . Chr(10) . "str" . Chr(10) . "bool" . Chr(10) . "float" . Chr(10) . "int8" . Chr(10) . "int16" . Chr(10) . "int32" . Chr(10) . "int64" . Chr(10) . "if" . Chr(10) . "else if" . Chr(10) . "else" . Chr(10) . "while" . Chr(10) . "Loop" . Chr(10) . "Loop," . Chr(10) . "Loop, Parse," . Chr(10) . "continue" . Chr(10) . "break" . Chr(10) . "func" . Chr(10) . "await" . Chr(10) . "async" . Chr(10) . "throw" . Chr(10) . "ErrorMsg" . Chr(10) . "try" . Chr(10) . "catch" . Chr(10) . "finally" . Chr(10) . "return" . Chr(10) . ".add" . Chr(10) . ".pop" . Chr(10) . ".size" . Chr(10) . ".insert" . Chr(10) . ".rm" . Chr(10) . ".indexOf" . Chr(10) . "arr" . Chr(10) . "arr int" . Chr(10) . "arr str" . Chr(10) . "arr float" . Chr(10) . "arr bool" . Chr(10) . "var" . Chr(10) . "let" . Chr(10) . "const" . Chr(10) . "end" . Chr(10) . "global" . Chr(10) . ";" . Chr(10) . "'''1" . Chr(10) . "'''2" . Chr(10) . "" . Chr(96) . "" . Chr(10) . "main" . Chr(10) . "." . Chr(10) . "+" . Chr(10) . "-" . Chr(10) . "*" . Chr(10) . "/" . Chr(10) . "%" . Chr(10) . "**" . Chr(10) . "=" . Chr(10) . "===" . Chr(10) . "!=" . Chr(10) . "" . Chr(62) . "" . Chr(10) . "" . Chr(60) . "" . Chr(10) . "" . Chr(62) . "=" . Chr(10) . "" . Chr(60) . "=" . Chr(10) . "and" . Chr(10) . "or" . Chr(10) . "!" . Chr(10) . "&" . Chr(10) . "|" . Chr(10) . "^" . Chr(10) . "~" . Chr(10) . "" . Chr(60) . "" . Chr(60) . "" . Chr(10) . "" . Chr(62) . "" . Chr(62) . "" . Chr(10) . "" . Chr(62) . "" . Chr(62) . "" . Chr(62) . "" . Chr(10) . ":=" . Chr(10) . "+=" . Chr(10) . ".=" . Chr(10) . "-=" . Chr(10) . "*=" . Chr(10) . "/=" . Chr(10) . "%=" . Chr(10) . "" . Chr(60) . "" . Chr(60) . "=" . Chr(10) . "" . Chr(62) . "" . Chr(62) . "=" . Chr(10) . "" . Chr(62) . "" . Chr(62) . "" . Chr(62) . "=" . Chr(10) . "&=" . Chr(10) . "|=" . Chr(10) . "^=" . Chr(10) . "?" . Chr(10) . ":" . Chr(10) . "++" . Chr(10) . "--" . Chr(10) . "0" . Chr(10) . "A_Index" . Chr(10) . "A_LoopField" . Chr(10) . "on" . Chr(10) . "off" . Chr(10) . "off" . Chr(10) . "on" . Chr(10) . "on" . Chr(10) . "off" . Chr(10) . "off" . Chr(10) . "off" . Chr(10) . "on" . Chr(10) . "off" . Chr(10) . "off" . Chr(10) . "on" . Chr(10) . "off" . Chr(10) . "" . Chr(10) . ""))
    return 0;
}