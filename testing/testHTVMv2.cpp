#include <algorithm>
#include <any>
#include <cstdint>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

// Print function for const char* specifically
void print(const char* value) {
    std::cout << std::string(value) << std::endl;  // Convert const char* to std::string
}
// Print function that converts all types to string if needed
template <typename T>
void print(const T& value) {
    std::cout << value << std::endl;
}

template<typename T>
std::string fstr(const T& val) {
    std::ostringstream oss;
    oss << val;
    return oss.str();
}


int main(int argc, char* argv[]) {
    // === Regular F-String Example ===
    int calculation = 10 + 5;
    std::string message = "The result is: " + fstr(calculation) + ". Double is: " + fstr(calculation * 2) + "";
    print("Regular F-String:");
    print(message);
    print("=========================");
    // === Multiline String (Raw) Example ===
    std::string ascii_cat = " /\\_/\\\n( o.o )\n > ^ <";
    print("Multiline String (Raw):");
    print(ascii_cat);
    print("=========================");
    // === Multiline F-String Example ===
    std::string userName = "Alice";
    int items = 3;
    float price = 19.99f;
    std::string order_summary = "Order Summary for: " + fstr(userName) + "\n\nItems purchased: " + fstr(items) + "\nTotal cost: $" + fstr(items * price) + "\n\nThank you for your order!\nNewlines and indentation are preserved.";
    print("Multiline F-String:");
    print(order_summary);
    print("=========================");
    return 0;
}