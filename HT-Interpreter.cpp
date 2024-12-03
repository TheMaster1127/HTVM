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

size_t StrLen(const std::string& str) {
    return str.length();
}

double Exp(double value) {
    return std::exp(value);
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

std::string Chr(int number) {
    return (number >= 0 && number <= 0x10FFFF) ? std::string(1, static_cast<char>(number)) : "";
}

int Mod(int dividend, int divisor) {
    return dividend % divisor;
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

int RegExMatch(const std::string& haystack, const std::string& needle) {
    std::regex re(needle);
    std::smatch match;
    if (std::regex_search(haystack, match, re)) {
        return match.position(0) + 1; // 1-based index
    }
    return 0; // No match
}


//Shunting Yard Algorithm
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
int int1 = 0;
int int2 = 0;
int int3 = 0;
int int4 = 0;
int int5 = 0;
int int6 = 0;
int int7 = 0;
float float1 = 0.0;
float float2 = 0.0;
float float3 = 0.0;
float float4 = 0.0;
float float5 = 0.0;
std::vector<std::string> theIdNumOfThe34theVar;
int theIdNumOfThe34 = 0;
std::vector<std::string> swapLast2StrArrayElement(std::vector<std::string> theStrArray) {
    // Check if the array has at least two elements
    if (theStrArray.size() < 2) {
        return theStrArray;
    }
    // Get the indices of the last two elements
    int lastIndex = theStrArray.size() - 1;
    int secondLastIndex = lastIndex - 1;
    // Swap the last two elements
    std::string temp = theStrArray[lastIndex];
    theStrArray[lastIndex] = theStrArray[secondLastIndex];
    theStrArray[secondLastIndex] = temp;
    // Return the modified array
    return theStrArray;
}
std::vector<std::string> popFirstStrArrayElement(std::vector<std::string> theStrArray) {
    std::vector<std::string> out123;
    for (int A_Index1 = 0; A_Index1 < theStrArray.size() + 0; A_Index1++) {
        if (A_Index1 > 0) {
            out123.push_back(theStrArray[A_Index1]);
        }
    }
    return out123;
}
std::string ExpresionEvalNoParentesis(std::string expresion) {
    std::string expresionOut = "";
    std::vector<std::string> holdingStack;
    std::vector<std::string> outputTemp;
    std::vector<std::string> solvingStack;
    std::string input = "0";
    std::string arithmeticOperations = "+-/*";
    int arithmeticOperationStrength = 0;
    std::string tempPopHoldingStack = "";
    int indexOfexpresionLoop = 0;
    int tempHoldingStackNumFIX = 0;
    expresion = StrReplace(expresion, " ", "");
    expresion = StrReplace(expresion, "-", " - ");
    expresion = StrReplace(expresion, "+", " + ");
    expresion = StrReplace(expresion, "*", " * ");
    expresion = StrReplace(expresion, "/", " / ");
    expresion = StrReplace(expresion, "(", " ( ");
    expresion = StrReplace(expresion, ")", " ) ");
    std::string addNegativeNums = "";
    std::vector<std::string> addNegativeNumsFurture;
    expresion = Trim(expresion);
    std::vector<std::string> items2 = LoopParseFunc(expresion, " ");
    for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
        std::string A_LoopField2 = items2[A_Index2 - 0];
        addNegativeNumsFurture.push_back(A_LoopField2);
    }
    int skip = 0;
    addNegativeNumsFurture.push_back("");
    std::vector<std::string> items3 = LoopParseFunc(expresion, " ");
    for (size_t A_Index3 = 0; A_Index3 < items3.size() + 0; A_Index3++) {
        std::string A_LoopField3 = items3[A_Index3 - 0];
        if (A_Index3 == 0 && A_LoopField3 == "-") {
            addNegativeNums += Trim(A_LoopField3) + addNegativeNumsFurture[A_Index3 + 1] + " ";
            skip = 1;
        }
        else if (A_LoopField3 == "-" && (addNegativeNumsFurture[A_Index3 - 1] == "*" || addNegativeNumsFurture[A_Index3 - 1] == "/" || addNegativeNumsFurture[A_Index3 - 1] == "-" || addNegativeNumsFurture[A_Index3 - 1] == "+")) {
            addNegativeNums += Trim(A_LoopField3) + addNegativeNumsFurture[A_Index3 + 1] + " ";
            skip = 1;
        } else {
            if (skip != 1) {
                addNegativeNums += A_LoopField3 + " ";
                skip = 0;
            } else {
                skip = 0;
            }
        }
    }
    expresion = StringTrimRight(addNegativeNums, 1);
    expresion = Trim(expresion);
    //print("DEBUGGGGGGGGGGGG:" . expresion)
    std::vector<std::string> output234543;
    std::vector<std::string> items4 = LoopParseFunc(expresion, " ");
    for (size_t A_Index4 = 0; A_Index4 < items4.size() + 0; A_Index4++) {
        std::string A_LoopField4 = items4[A_Index4 - 0];
        indexOfexpresionLoop = A_Index4 + 1;
        input = A_LoopField4;
        if (InStr(arithmeticOperations, input) == 0) {
            // numbers
            //print(input)
            outputTemp.push_back(input);
        } else {
            // arithmeticOperation
            //print(input)
            if (holdingStack.size() == 0) {
                holdingStack.push_back(input);
            } else {
                if (InStr(arithmeticOperations, input) == InStr(arithmeticOperations, holdingStack[holdingStack.size() - 1])) {
                    outputTemp.push_back(input);
                }
                else if (InStr(arithmeticOperations, holdingStack[holdingStack.size() - 1]) < InStr(arithmeticOperations, input)) {
                    holdingStack.push_back(input);
                } else {
                    // what do we do
                    // add the last
                    for (int A_Index5 = 0; ; A_Index5++) {
                        if (holdingStack.size() > 0 && InStr(arithmeticOperations, holdingStack[holdingStack.size() - 1]) > InStr(arithmeticOperations, input)) {
                            tempHoldingStackNumFIX = holdingStack.size();
                            for (int A_Index6 = 0; A_Index6 < tempHoldingStackNumFIX + 0; A_Index6++) {
                                tempPopHoldingStack = holdingStack[holdingStack.size() - 1];
                                holdingStack.pop_back();
                                outputTemp.push_back(tempPopHoldingStack);
                            }
                        } else {
                            break;
                        }
                    }
                    holdingStack.push_back(input);
                }
                // 2 else and 1 loop end
            }
        }
    }
    if (holdingStack.size() != 0 || STR(holdingStack.size()) != "") {
        for (int A_Index7 = 0; A_Index7 < holdingStack.size() + 0; A_Index7++) {
            if (Trim(holdingStack[holdingStack.size() - 1 - A_Index7]) != "") {
                outputTemp.push_back(holdingStack[holdingStack.size() - 1 - A_Index7]);
            }
        }
    }
    int fixOutputTempRMparanesises = outputTemp.size();
    std::vector<std::string> outputTemp2;
    for (int A_Index8 = 0; A_Index8 < fixOutputTempRMparanesises + 0; A_Index8++) {
        if (Trim(outputTemp[A_Index8]) != "") {
            outputTemp2.push_back(outputTemp[A_Index8]);
        }
    }
    outputTemp = outputTemp2;
    //print(outputTemp)
    for (int A_Index9 = 0; ; A_Index9++) {
        if (outputTemp.size() == 0 || STR(outputTemp.size()) == "") {
            break;
        }
        tempPopHoldingStack = outputTemp[0];
        outputTemp = popFirstStrArrayElement(outputTemp);
        solvingStack.push_back(tempPopHoldingStack);
        if (InStr(arithmeticOperations, solvingStack[solvingStack.size() - 1]) != 0) {
            solvingStack = swapLast2StrArrayElement(solvingStack);
            float1 = FLOAT(solvingStack[solvingStack.size() - 3]);
            str2 = solvingStack[solvingStack.size() - 2];
            float3 = FLOAT(solvingStack[solvingStack.size() - 1]);
            solvingStack.pop_back();
            solvingStack.pop_back();
            solvingStack.pop_back();
            if (str2 == "-") {
                float4 = float1 - float3;
                solvingStack.push_back(STR(float4));
            }
            if (str2 == "+") {
                float4 = float1 + float3;
                solvingStack.push_back(STR(float4));
            }
            if (str2 == "*") {
                float4 = float1 * float3;
                solvingStack.push_back(STR(float4));
            }
            if (str2 == "/") {
                float4 = float1 / float3;
                solvingStack.push_back(STR(float4));
            }
        }
    }
    expresionOut = Trim(solvingStack[solvingStack.size() - 1]);
    if (SubStr(expresionOut, 1, 2) == "- ") {
        expresionOut = StringTrimLeft(expresionOut, 2);
        expresionOut = "-" + expresionOut;
    }
    if (Trim(expresionOut) == "") {
        expresionOut = "null";
    }
    return expresionOut;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string expresionEvalHelp(std::string expression) {
    int startIndex = 0;
    int endIndex = 0;
    std::string innerExpression = "";
    std::string innerResult = "";
    int openCount = 0;
    std::string char123 = "";
    // Remove spaces for consistency
    expression = StrReplace(expression, " ", "");
    // Loop until no more parentheses are left
    while (InStr(expression, "(")) {
        // Find the position of the first '('
        startIndex = InStr(expression, "(");
        // Now, find the matching closing ')'
        openCount = 1;
        endIndex = startIndex + 1;
        // Loop to find the matching closing ')'
        while (openCount > 0 && endIndex <= StrLen(expression)) {
            char123 = SubStr(expression, endIndex, 1);
            if (char123 == "(") {
                openCount++;
            }
            else if (char123 == ")") {
                openCount--;
            }
            endIndex++;
        }
        // Extract the inner expression
        innerExpression = SubStr(expression, startIndex + 1, endIndex - startIndex - 2);
        //print(innerExpression)
        // Evaluate the inner expression (this is where recursion handles nested parentheses)
        innerResult = expresionEvalHelp(innerExpression);
        // Replace the entire parentheses with the result
        expression = SubStr(expression, 1, startIndex - 1) + innerResult + SubStr(expression, endIndex);
    }
    // Now evaluate the expression without parentheses
    return ExpresionEvalNoParentesis(expression);
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string callFunc(std::string funcParams) {
    std::string funcParamsOut = "";
    funcParams = Trim(funcParams);
    funcParams = StringTrimRight(funcParams, 1);
    std::string funcName = "";
    std::vector<std::string> items10 = LoopParseFunc(funcParams, " ");
    for (size_t A_Index10 = 0; A_Index10 < items10.size() + 0; A_Index10++) {
        std::string A_LoopField10 = items10[A_Index10 - 0];
        if (A_Index10 == 0) {
            funcName = Trim(A_LoopField10);
        }
        if (A_Index10 > 1) {
            funcParamsOut += A_LoopField10 + " ";
        }
    }
    //print("debug funcname: " . funcName)
    funcParamsOut = StringTrimRight(funcParamsOut, 1);
    funcParams = Trim(StrReplace(Trim(funcParamsOut), " ", ""));
    funcParamsOut = "";
    if (funcName == "INT") {
        std::vector<std::string> items11 = LoopParseFunc(funcParams, ",");
        for (size_t A_Index11 = 0; A_Index11 < items11.size() + 0; A_Index11++) {
            std::string A_LoopField11 = items11[A_Index11 - 0];
            funcParamsOut += expresionEvalHelp(StringTrimRight(StringTrimLeft(A_LoopField11, 1), 1)) + "+";
        }
    }
    else if (funcName == "STR") {
        std::vector<std::string> items12 = LoopParseFunc(funcParams, ",");
        for (size_t A_Index12 = 0; A_Index12 < items12.size() + 0; A_Index12++) {
            std::string A_LoopField12 = items12[A_Index12 - 0];
            funcParamsOut += expresionEvalHelp(Chr(34) + A_LoopField12 + Chr(34)) + "+";
        }
    }
    else if (funcName == "print") {
        print(expresionEvalHelp(Trim(funcParams)));
        return "null";
    } else {
        std::vector<std::string> items13 = LoopParseFunc(funcParams, ",");
        for (size_t A_Index13 = 0; A_Index13 < items13.size() + 0; A_Index13++) {
            std::string A_LoopField13 = items13[A_Index13 - 0];
            funcParamsOut += expresionEvalHelp(A_LoopField13) + "+";
        }
    }
    funcParamsOut = StringTrimRight(funcParamsOut, 1);
    return expresionEvalHelp(funcParamsOut);
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string expresionEval(std::string expresion) {
    //print("=========================")
    //print(expresion)
    //print("=========================")
    std::string HTpyCodeOUT754754 = "";
    int areWEinSome34sNum = 0;
    std::vector<std::string> items14 = LoopParseFunc(expresion);
    for (size_t A_Index14 = 0; A_Index14 < items14.size() + 0; A_Index14++) {
        std::string A_LoopField14 = items14[A_Index14 - 0];
        theIdNumOfThe34theVar.push_back("");
        theIdNumOfThe34theVar[A_Index14] = Chr(34);
    }
    std::vector<std::string> items15 = LoopParseFunc(expresion);
    for (size_t A_Index15 = 0; A_Index15 < items15.size() + 0; A_Index15++) {
        std::string A_LoopField15 = items15[A_Index15 - 0];
        if (A_LoopField15 == Chr(34)) {
            areWEinSome34sNum++;
        }
        if (areWEinSome34sNum == 1) {
            if (A_LoopField15 != Chr(34)) {
                if (A_LoopField15 == Chr(96)) {
                    theIdNumOfThe34theVar[theIdNumOfThe34] += Chr(92);
                } else {
                    theIdNumOfThe34theVar[theIdNumOfThe34] += A_LoopField15;
                }
            } else {
                theIdNumOfThe34++;
                HTpyCodeOUT754754 += "ihuiuuhuuhtheidFor|||||||||||asas|||||||||||theuhturtyphoutr|||||||||||" + str11 + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
            }
        }
        if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
            if (A_LoopField15 != Chr(34)) {
                HTpyCodeOUT754754 += A_LoopField15;
            }
            areWEinSome34sNum = 0;
        }
    }
    expresion = HTpyCodeOUT754754;
    for (int A_Index16 = 0; A_Index16 < theIdNumOfThe34 + 0; A_Index16++) {
        theIdNumOfThe34theVar[A_Index16 + 1] += Chr(34);
    }
    for (int A_Index17 = 0; A_Index17 < theIdNumOfThe34 + 0; A_Index17++) {
        expresion = StrReplace(expresion, "ihuiuuhuuhtheidFor|||||||||||asas|||||||||||theuhturtyphoutr|||||||||||AA" + STR(A_Index17 + 1) + "AA", theIdNumOfThe34theVar[A_Index17 + 1]);
    }
    expresion = Trim(StrReplace(expresion, " ", ""));
    expresion = Trim(StrReplace(expresion, "(", " ( "));
    expresion = Trim(StrReplace(expresion, ")", " ) "));
    expresion = Trim(StrReplace(expresion, "+", " + "));
    expresion = Trim(StrReplace(expresion, "-", " - "));
    expresion = Trim(StrReplace(expresion, "/", " / "));
    expresion = Trim(StrReplace(expresion, "*", " * "));
    expresion = Trim(StrReplace(expresion, ",", " , "));
    std::vector<std::string> expresionForFuncLookInF;
    std::vector<std::string> items18 = LoopParseFunc(expresion, " ");
    for (size_t A_Index18 = 0; A_Index18 < items18.size() + 0; A_Index18++) {
        std::string A_LoopField18 = items18[A_Index18 - 0];
        expresionForFuncLookInF.push_back(A_LoopField18);
    }
    expresionForFuncLookInF.push_back("");
    int foundFunc = 0;
    int foundFunc2 = 0;
    int didWeSeeAfunc = 0;
    int countParentheses = 0;
    int countParenthesesOnceHelper = 0;
    int funcEndEnd = 0;
    int funcPosIndex1 = 0;
    int funcPosIndex2 = 0;
    std::string expresionReplaceHelper = "";
    std::string expresionReplaceHelper1 = "";
    for (int A_Index19 = 0; A_Index19 < 20 + 0; A_Index19++) {
        foundFunc = 0;
        foundFunc2 = 0;
        didWeSeeAfunc = 0;
        countParentheses = 0;
        countParenthesesOnceHelper = 0;
        funcEndEnd = 0;
        funcPosIndex1 = 0;
        funcPosIndex2 = 0;
        std::vector<std::string> items20 = LoopParseFunc(expresion, " ");
        for (size_t A_Index20 = 0; A_Index20 < items20.size() + 0; A_Index20++) {
            std::string A_LoopField20 = items20[A_Index20 - 0];
            if (foundFunc == 1) {
                if (RegExMatch(A_LoopField20, "^[A-Za-z_][A-Za-z0-9_]*$") && expresionForFuncLookInF[A_Index20 + 1] == "(" && foundFunc == 1) {
                    foundFunc2 = 1;
                    funcPosIndex1 = A_Index20;
                    countParentheses = 0;
                    countParenthesesOnceHelper = 0;
                    //print("debug in: " + A_LoopField20)
                }
                if (A_LoopField20 == "(") {
                    countParentheses++;
                    countParenthesesOnceHelper++;
                }
                if (A_LoopField20 == ")") {
                    countParentheses--;
                }
                if (countParenthesesOnceHelper != 0) {
                    if (countParentheses == 0) {
                        funcEndEnd = 1;
                        funcPosIndex2 = A_Index20;
                        break;
                    }
                }
            }
            // Check if the variable matches the regex pattern
            if (RegExMatch(A_LoopField20, "^[A-Za-z_][A-Za-z0-9_]*$") && expresionForFuncLookInF[A_Index20 + 1] == "(" && foundFunc == 0) {
                foundFunc = 1;
                funcPosIndex1 = A_Index20;
                //print(A_LoopField20)
            }
        }
        if (foundFunc != 1) {
            //print("no more funcs")
            expresion = Trim(expresion);
            expresion = Trim(expresionEvalHelp(expresion));
            // eval
            // eval
            // eval
            // eval
            // eval
            // eval
            break;
        }
        expresionReplaceHelper1 = "";
        expresionReplaceHelper = "";
        std::vector<std::string> items21 = LoopParseFunc(expresion, " ");
        for (size_t A_Index21 = 0; A_Index21 < items21.size() + 0; A_Index21++) {
            std::string A_LoopField21 = items21[A_Index21 - 0];
            if (A_Index21 >= funcPosIndex1 && A_Index21 < funcPosIndex2) {
                expresionReplaceHelper1 += A_LoopField21 + " ";
                //print("found: " . A_LoopField21)
            }
            else if (A_Index21 == funcPosIndex2) {
                expresionReplaceHelper1 += A_LoopField21 + " ";
                //print("found: " . A_LoopField21)
                expresionReplaceHelper += callFunc(Trim(expresionReplaceHelper1)) + " ";
            } else {
                expresionReplaceHelper += A_LoopField21 + " ";
            }
        }
        expresion = Trim(expresionReplaceHelper);
        //print("=========================")
        //print(expresion)
        //print("=========================")
        if (InStr(Trim(expresion), " ")) {
            continue;
        } else {
            break;
        }
    }
    // eval too
    // eval too
    // eval too
    // eval too
    expresion = Trim(expresion);
    // eval too
    expresion = Trim(expresionEvalHelp(expresion));
    return expresion;
}
void interpreter() {
    std::string HTIcode = "";
    std::string params = GetParams();
    if (params == "") {
        print("Usage:\nHT-Interpreter yourFile.hti\nOr use -c to open console mode.");
        return;
    }
    std::string fileName = "";
    fileName = Trim(params);
    print(fileName);
    int consoleMode = 0;
    if (fileName == "-c") {
        consoleMode = 1;
    } else {
        HTIcode = FileRead(Trim(fileName));
        HTIcode = StrReplace(HTIcode, Chr(13), "");
    }
    std::string consoleModeInput = "";
    std::string consoleModeInputHelp = "";
    if (consoleMode == 1) {
        for (int A_Index22 = 0; ; A_Index22++) {
            consoleModeInput = Trim(input(">>> "));
            if (consoleModeInput == "exit()") {
                break;
            } else {
                consoleModeInputHelp = Trim(expresionEval(consoleModeInput));
                if (consoleModeInputHelp != "null") {
                    print(consoleModeInputHelp);
                }
            }
        }
    } else {
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        std::vector<std::string> items23 = LoopParseFunc(HTIcode, "\n", "\r");
        for (size_t A_Index23 = 0; A_Index23 < items23.size() + 0; A_Index23++) {
            std::string A_LoopField23 = items23[A_Index23 - 0];
            if (Trim(A_LoopField23) != "") {
                expresionEval(Trim(A_LoopField23));
            }
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    }
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
int main(int argc, char* argv[]) {
    int test1 = 0;
    if (test1 == 1) {
        print("Shunting Yard Algorithm");
        std::string expresion = "1+2*4-3";
        print(expresionEvalHelp(expresion));
        std::string testExpresions = "3+5|12-4|7*3|18/6|4+92|10-23|15+3-2|87-9|6+8/4|32+5|18-4/2|6/3+8|14-62|5+9/3|75-3|8+43|9/3+42|12+6*2-3|16-4/2+3|1+2*4-3";
        std::string answersOfTheTestExpresions = "8|8|21|3|96|-13|16|78|8|37|16|10|-48|8|72|51|45|21|17|6";
        int testIndexTestExpresions = 0;
        std::string TEMPanswersOfTheTestExpresions = "";
        int DidWePassTheTestExpresions = 1;
        int DidWePassTheTestExpresionsCOUNT = 0;
        int DidWePassTheTestExpresionsCOUNTMAX = 0;
        std::vector<std::string> items24 = LoopParseFunc(testExpresions, "|");
        for (size_t A_Index24 = 0; A_Index24 < items24.size() + 0; A_Index24++) {
            std::string A_LoopField24 = items24[A_Index24 - 0];
            DidWePassTheTestExpresionsCOUNT++;
            DidWePassTheTestExpresionsCOUNTMAX++;
            testIndexTestExpresions = A_Index24;
            std::vector<std::string> items25 = LoopParseFunc(answersOfTheTestExpresions, "|");
            for (size_t A_Index25 = 0; A_Index25 < items25.size() + 0; A_Index25++) {
                std::string A_LoopField25 = items25[A_Index25 - 0];
                if (A_Index25 == testIndexTestExpresions) {
                    TEMPanswersOfTheTestExpresions = A_LoopField25;
                }
            }
            print(STR(A_Index24 + 1) + " ===============================");
            print(A_LoopField24);
            print(expresionEvalHelp(A_LoopField24));
            if (FLOAT(expresionEvalHelp(A_LoopField24)) == FLOAT(TEMPanswersOfTheTestExpresions)) {
                print("true");
            } else {
                print("false");
                DidWePassTheTestExpresionsCOUNT--;
                DidWePassTheTestExpresions = 0;
            }
        }
        print("==================================");
        print("==================================");
        if (DidWePassTheTestExpresions == 0) {
            print("TestExpresions NOT PASSED!!! " + STR(DidWePassTheTestExpresionsCOUNT) + "/" + STR(DidWePassTheTestExpresionsCOUNTMAX));
        } else {
            print("TestExpresions PASSED!!!" + STR(DidWePassTheTestExpresionsCOUNT) + "/" + STR(DidWePassTheTestExpresionsCOUNTMAX));
        }
        print("5+(5+5)*1");
        print(expresionEvalHelp("5+(5+5)*1"));
        print("6+((8/2+6+((8/2)*3+6+((8+6+((8/2+6+((8/2)*3+6+((8/2)*3)))*3)/2)*3)))*3)");
        print(expresionEvalHelp("6+((8/2+6+((8/2)*3+6+((8+6+((8/2+6+((8/2)*3+6+((8/2)*3)))*3)/2)*3)))*3)"));
        print("((3 + 5) * (10 - 4) / 2) + (-7 * (3 + 2)) - (4 / (6 - 2)) * -3");
        print(expresionEvalHelp("((3 + 5) * (10 - 4) / 2) + (-7 * (3 + 2)) - (4 / (6 - 2)) * -3"));
        print("-((1+2)/((6*-7)+(7*-4)/2)-3)");
        print(FLOAT(expresionEvalHelp("-((1+2)/((6*-7)+(7*-4)/2)-3)")));
        print("=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        print("=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        print("=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        print(expresionEval("-5+func1(45+1, 5+5+(58+5/2--2), func2(56, func3(func4(5))))"));
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    // runing the interpreter
    interpreter();
    return 0;
}