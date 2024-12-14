#include <algorithm>
#include <any>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
#include <thread>
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

// Function to sleep for a specified number of milliseconds
void Sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// Function to get input from the user, similar to Python's input() function
std::string input(const std::string& prompt) {
    std::string userInput;
    std::cout << prompt; // Display the prompt to the user
    std::getline(std::cin, userInput); // Get the entire line of input
    return userInput;
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


std::string detectWin(std::string board) {
    std::vector<int> arrPosPlayer1;
    std::vector<int> arrPosPlayer2;
    std::string temp1 = "player";
    std::vector<std::string> items1 = LoopParseFunc(board, "|");
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        if (Trim(A_LoopField1) == "x") {
            arrPosPlayer1.push_back(1);
        } else {
            arrPosPlayer1.push_back(0);
        }
    }
    std::vector<std::string> items2 = LoopParseFunc(board, "|");
    for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
        std::string A_LoopField2 = items2[A_Index2 - 0];
        if (Trim(A_LoopField2) == "o") {
            arrPosPlayer2.push_back(1);
        } else {
            arrPosPlayer2.push_back(0);
        }
    }
    for (int A_Index3 = 0; A_Index3 < 3 + 0; A_Index3++) {
        if (arrPosPlayer1[0 + (A_Index3 * 3)] == 1 && arrPosPlayer1[1 + (A_Index3 * 3)] == 1 && arrPosPlayer1[2 + (A_Index3 * 3)] == 1) {
            return temp1 + " 1 won!!!";
        }
    }
    for (int A_Index4 = 0; A_Index4 < 3 + 0; A_Index4++) {
        if (arrPosPlayer1[A_Index4] == 1 && arrPosPlayer1[A_Index4 + 3] == 1 && arrPosPlayer1[A_Index4 + 6] == 1) {
            return temp1 + " 1 won!!!";
        }
    }
    if (arrPosPlayer1[0] == 1 && arrPosPlayer1[4] == 1 && arrPosPlayer1[8] == 1) {
        return temp1 + " 1 won!!!";
    }
    if (arrPosPlayer1[2] == 1 && arrPosPlayer1[4] == 1 && arrPosPlayer1[6] == 1) {
        return temp1 + " 1 won!!!";
    }
    for (int A_Index5 = 0; A_Index5 < 3 + 0; A_Index5++) {
        if (arrPosPlayer2[0 + (A_Index5 * 3)] == 1 && arrPosPlayer2[1 + (A_Index5 * 3)] == 1 && arrPosPlayer2[2 + (A_Index5 * 3)] == 1) {
            return temp1 + " 2 won!!!";
        }
    }
    for (int A_Index6 = 0; A_Index6 < 3 + 0; A_Index6++) {
        if (arrPosPlayer2[A_Index6] == 1 && arrPosPlayer2[A_Index6 + 3] == 1 && arrPosPlayer2[A_Index6 + 6] == 1) {
            return temp1 + " 2 won!!!";
        }
    }
    if (arrPosPlayer2[0] == 1 && arrPosPlayer2[4] == 1 && arrPosPlayer2[8] == 1) {
        return temp1 + " 2 won!!!";
    }
    if (arrPosPlayer2[2] == 1 && arrPosPlayer2[4] == 1 && arrPosPlayer2[6] == 1) {
        return temp1 + " 2 won!!!";
    }
    return temp1 + "null";
}
int main(int argc, char* argv[]) {
    std::string tabel = "0|0|0|0|0|0|0|0|0";
    std::string tabelTemp = "";
    int turn = 0;
    int pos = 0;
    std::string tempHoldToPrint = "";
    int tempHoldToPrintINT = 0;
    int error = 0;
    int index = 0;
    for (int A_Index7 = 0; A_Index7 < 1000 + 0; A_Index7++) {
        index++;
        if (Mod(index, 2)) {
            for (int A_Index8 = 0; ; A_Index8++) {
                pos = INT(Trim(input("PLAYER 2 make a move from pos 1 to 9: ")));
                Sleep(10);
                if (pos <= 0 || pos >= 10) {
                    print("error cant play this move!!!");
                } else {
                    break;
                }
            }
            tabelTemp = "";
            std::vector<std::string> items9 = LoopParseFunc(tabel, "|");
            for (size_t A_Index9 = 0; A_Index9 < items9.size() + 0; A_Index9++) {
                std::string A_LoopField9 = items9[A_Index9 - 0];
                if (A_Index9 + 1 == pos) {
                    if (Trim(A_LoopField9) == "x" || Trim(A_LoopField9) == "o") {
                        error = 1;
                        index--;
                        print("error cant play this move!!!");
                        break;
                    }
                    tabelTemp += "o|";
                } else {
                    tabelTemp += A_LoopField9 + "|";
                }
            }
            if (error == 0) {
                error = 0;
                tabel = StringTrimRight(tabelTemp, 1);
            } else {
                error = 0;
                continue;
            }
        } else {
            for (int A_Index10 = 0; ; A_Index10++) {
                pos = INT(Trim(input("PLAYER 1 make a move from pos 1 to 9: ")));
                Sleep(10);
                if (pos <= 0 || pos >= 10) {
                    print("error cant play this move!!!");
                } else {
                    break;
                }
            }
            tabelTemp = "";
            std::vector<std::string> items11 = LoopParseFunc(tabel, "|");
            for (size_t A_Index11 = 0; A_Index11 < items11.size() + 0; A_Index11++) {
                std::string A_LoopField11 = items11[A_Index11 - 0];
                if (A_Index11 + 1 == pos) {
                    if (Trim(A_LoopField11) == "x" || Trim(A_LoopField11) == "o") {
                        error = 1;
                        index--;
                        print("error cant play this move!!!");
                        break;
                    }
                    tabelTemp += "x|";
                } else {
                    tabelTemp += A_LoopField11 + "|";
                }
            }
            if (error == 0) {
                error = 0;
                tabel = StringTrimRight(tabelTemp, 1);
            } else {
                error = 0;
                continue;
            }
        }
        tempHoldToPrint = "";
        tempHoldToPrintINT = 0;
        std::vector<std::string> items12 = LoopParseFunc(tabel, "|");
        for (size_t A_Index12 = 0; A_Index12 < items12.size() + 0; A_Index12++) {
            std::string A_LoopField12 = items12[A_Index12 - 0];
            tempHoldToPrintINT++;
            tempHoldToPrint += A_LoopField12 + "|";
            if (tempHoldToPrintINT == 3) {
                tempHoldToPrintINT = 0;
                tempHoldToPrint += "\n";
            }
        }
        tempHoldToPrint = StringTrimRight(tempHoldToPrint, 1);
        print(tempHoldToPrint);
        Sleep(10);
        if (detectWin(tempHoldToPrint) == "player 1 won!!!") {
            print("player 1 won!!!");
            break;
        }
        if (detectWin(tempHoldToPrint) == "player 2 won!!!") {
            print("player 2 won!!!");
            break;
        }
    }
    print("GAME OVER!!!");
    return 0;
}
