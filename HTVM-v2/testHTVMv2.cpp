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
    std::cout << value << std::endl;
}

// Function to get input from the user, similar to Python's input() function
std::string input(const std::string& prompt) {
    std::string userInput;
    std::cout << prompt; // Display the prompt to the user
    std::getline(std::cin, userInput); // Get the entire line of input
    return userInput;
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
void HTVM_Pop(std::vector<T>& arr) {
    if (!arr.empty()) arr.pop_back();
}

template <typename T>
size_t HTVM_Size(const std::vector<T>& arr) {
    return arr.size();
}

template <typename T>
void HTVM_Insert(std::vector<T>& arr, size_t index, const T& value) {
    if (index <= arr.size()) arr.insert(arr.begin() + index, value);
}

template <typename T>
void HTVM_Remove(std::vector<T>& arr, const T& value) {
    arr.erase(std::remove(arr.begin(), arr.end(), value), arr.end());
}

template <typename T>
int HTVM_IndexOf(const std::vector<T>& arr, const T& value) {
    auto it = std::find(arr.begin(), arr.end(), value);
    return (it != arr.end()) ? std::distance(arr.begin(), it) : -1;
}


// start
void func0(const std::string& input) {
    std::cout << input << std::endl;
}




























void func1(double var1, char var2, uint8_t var3, uint16_t var4, uint32_t var5, uint64_t var6, int var7, std::string var8, bool var9, float var10, int8_t var11, int16_t var12, int32_t var13, int64_t var14) {
    print(var1);
    print(var2);
    print(var3);
    print(var4);
    print(var5);
    print(var6);
    print(var7);
    print(var8);
    print(var9);
    print(var10);
    print(var11);
    print(var12);
    print(var13);
    print(var14);
}
double func2(double var1) {
    return var1;
}
char func3(char var1) {
    return var1;
}
uint8_t func4(uint8_t var1) {
    return var1;
}
uint16_t func5(uint16_t var1) {
    return var1;
}
uint32_t func6(uint32_t var1) {
    return var1;
}
uint64_t func7(uint64_t var1) {
    return var1;
}
int func8(int var1) {
    return var1;
}
std::string func9(std::string var1) {
    return var1;
}
bool func10(bool var1) {
    return var1;
}
float func11(float var1) {
    return var1;
}
int8_t func12(int8_t var1) {
    return var1;
}
int16_t func13(int16_t var1) {
    return var1;
}
int32_t func14(int32_t var1) {
    return var1;
}
int64_t func15(int64_t var1) {
    return var1;
}
/*
this
is
a
multy
line
comment
*/
// outside vars
double var01 = 3.1234567891011;
char var02 = 'a';
uint8_t var03 = 25;
uint16_t var04 = 30;
uint32_t var05 = 35;
uint64_t var06 = 40ULL;
int var07 = 100;
std::string var08 = "hello var ouside";
bool var09 = false;
float var010 = 3.14f;
int8_t var011 = 100;
int16_t var012 = 200;
int32_t var013 = 230;
int64_t var014 = 80009LL;
int main(int argc, char* argv[]) {
    double var_1 = 0.00;
    char var_2 = 'a';
    uint8_t var_3 = 0;
    uint16_t var_4 = 0;
    uint32_t var_5 = 0;
    uint64_t var_6 = 0ULL;
    int var_7 = 0;
    std::string var_8 = "";
    bool var_9 = false;
    float var_10 = 0.00f;
    int8_t var_11 = 0;
    int16_t var_12 = 0;
    int32_t var_13 = 0;
    int64_t var_14 = 0LL;
    func1(var01, var02, var03, var04, var05, var06, var07, var08, var09, var010, var011, var012, var013, var014);
    var_1 = func2(var01);
    var_2 = func3(var02);
    var_3 = func4(var03);
    var_4 = func5(var04);
    var_5 = func6(var05);
    var_6 = func7(var06);
    var_7 = func8(var07);
    var_8 = func9(var08);
    var_9 = func10(var09);
    var_10 = func11(var010);
    var_11 = func12(var011);
    var_12 = func13(var012);
    var_13 = func14(var013);
    var_14 = func15(var014);
    print(var_1);
    print(var_2);
    print(var_3);
    print(var_4);
    print(var_5);
    print(var_6);
    print(var_7);
    print(var_8);
    print(var_9);
    print(var_10);
    print(var_11);
    print(var_12);
    print(var_13);
    print(var_14);
    // start
    func0("Hello World");
    

    

    

    

    

    

    

    

    

    

    

    

    

    

    print("==================================");
    for (int A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        if (A_Index1 == 0) {
            print(A_Index1);
        }
        else if (A_Index1 == 1) {
            print(A_Index1);
        }
        else if (A_Index1 == 2) {
            print(A_Index1);
        }
        else if (A_Index1 == 3) {
            print(A_Index1);
        }
        else if (A_Index1 == 4) {
            print(A_Index1);
        }
        else if (A_Index1 == 5) {
            print(A_Index1);
        } else {
            print("HOW????");
            print(A_Index1);
        }
    }
    bool vars1 = false;
    int vars2 = 0;
    while (vars1 == false) {
        vars2++;
        print(vars2);
        if (vars2 == 6) {
            vars1 = true;
        }
    }
    for (int A_Index2 = 0; ; A_Index2++) {
        if (A_Index2 == 6) {
            break;
        } else {
            continue;
        }
        // this is only for lua
        ::continue::
    }
    std::string str1 = "hello 123 hello2";
    std::vector<std::string> items3 = LoopParseFunc(str1, " ");
    for (size_t A_Index3 = 0; A_Index3 < items3.size() + 0; A_Index3++) {
        std::string A_LoopField3 = items3[A_Index3 - 0];
        print(A_LoopField3);
    }
    print("==================");
    std::vector<std::string> items4 = LoopParseFunc(str1);
    for (size_t A_Index4 = 0; A_Index4 < items4.size() + 0; A_Index4++) {
        std::string A_LoopField4 = items4[A_Index4 - 0];
        print(A_LoopField4);
        if (A_LoopField4 == "2") {
            break;
        } else {
            continue;
        }
        ::continue::
    }
    /*
    keyWordArrayAppend
    keyWordArrayPop
    keyWordArraySize
    keyWordArrayInsert
    keyWordArrayRemove
    keyWordArrayIndexOf
    keyWordArrayDefinition
    keyWordArrayOfIntegersDefinition
    keyWordArrayOfStringsDefinition
    keyWordArrayOfFloatingPointNumbersDefinition
    keyWordArrayOfBooleansDefinition
    */
    std::vector<std::string> arr1 = {"hello1", "hello2"};
    std::vector<bool> arr2 = {true, false};
    std::vector<float> arr3 = {3.13, 3.14};
    std::vector<int> arr4 = {1, 6, 2};
    std::vector<std::string> arr5 = {"real STR"};
    // Array operations
    HTVM_Append(arr1, "hello3");
    int sizeArr1 = HTVM_Size(arr1);
    print("the size of arr1 is:");
    print(sizeArr1);
    HTVM_Insert(arr1, 1, "hello?????");
    HTVM_Remove(arr1, 0);
    int idx1 = HTVM_IndexOf(arr1, "hello2");
    print("the index of arr1 for hello2 is:");
    print(idx1);
    HTVM_Pop(arr1);
    for (int A_Index5 = 0; A_Index5 < HTVM_Size(arr1) + 0; A_Index5++) {
        print(arr1[A_Index5]);
    }
    HTVM_Append(arr2, true);
    int sizeArr2 = HTVM_Size(arr2);
    print("the size of arr2 is:");
    print(sizeArr2);
    HTVM_Insert(arr2, 1, false);
    HTVM_Remove(arr2, 0);
    int idx2 = HTVM_IndexOf(arr2, true);
    print("the index of arr2 for true is:");
    print(idx2);
    HTVM_Pop(arr2);
    for (int A_Index6 = 0; A_Index6 < HTVM_Size(arr2) + 0; A_Index6++) {
        print(arr2[A_Index6]);
    }
    HTVM_Append(arr3, 6.489);
    int sizeArr3 = HTVM_Size(arr3);
    print("the size of arr3 is:");
    print(sizeArr3);
    HTVM_Insert(arr3, 1, 1.556);
    HTVM_Remove(arr3, 0);
    int idx3 = HTVM_IndexOf(arr3, 3.14);
    print("the index of arr3 for 3.14 is:");
    print(idx3);
    HTVM_Pop(arr3);
    for (int A_Index7 = 0; A_Index7 < HTVM_Size(arr3) + 0; A_Index7++) {
        print(arr3[A_Index7]);
    }
    HTVM_Append(arr4, 69);
    int sizeArr4 = HTVM_Size(arr4);
    print("the size of arr4 is:");
    print(sizeArr4);
    HTVM_Insert(arr4, 1, 420);
    HTVM_Remove(arr4, 0);
    int idx4 = HTVM_IndexOf(arr4, 69);
    print("the index of arr4 for 69 is:");
    print(idx4);
    HTVM_Pop(arr4);
    for (int A_Index8 = 0; A_Index8 < HTVM_Size(arr4) + 0; A_Index8++) {
        print(arr4[A_Index8]);
    }
    HTVM_Append(arr5, "hello3real");
    int sizeArr5 = HTVM_Size(arr5);
    print("the size of arr5 is:");
    print(sizeArr5);
    HTVM_Insert(arr5, 1, "hello?real????");
    HTVM_Remove(arr5, 0);
    int idx5 = HTVM_IndexOf(arr5, "hello3real");
    print("the index of arr5 for hello3real is:");
    print(idx5);
    HTVM_Pop(arr5);
    for (int A_Index9 = 0; A_Index9 < HTVM_Size(arr5) + 0; A_Index9++) {
        print(arr5[A_Index9]);
    }
    /*
    keyWordThrow
    keyWordErrorMsg
    keyWordTry
    keyWordCatch
    keyWordFinally
    */
    try {
        print("Trying...");
        throw std::runtime_error("Something went wrong!");
    }
    catch (const std::exception& e) {
        print("Caught an error:");
        print(e.what());
    }
    if ("finally dosent exist in c++" == "finally dosent exist in c++") {
        print("This always runs, success or error.");
    }
    print("==============================================");
    return 0;
}