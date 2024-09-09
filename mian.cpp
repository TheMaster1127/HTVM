#include <cmath>
#include <iostream>

// 1. Function to reverse a string
std::string reverseString(const std::string& str) {
    return std::string(str.rbegin(), str.rend());
}

// 2. Function to calculate the factorial of a number
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// 3. Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i <= std::sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}


int main(int argc, char* argv[]) {
    std::string reversed = reverseString("Hello World");
    std::cout << "Reversed string: " << reversed << std::endl
    // Using the factorial function
    int fact = factorial(5);
    std::cout << "Factorial of 5: " << fact << std::endl
    // Using the isPrime function
    bool primeCheck = isPrime(7);
    std::cout << "Is 7 prime? " << (primeCheck ? "True" : "False") << std::endl
    primeCheck = isPrime(10);
    std::cout << "Is 10 prime? " << (primeCheck ? "True" : "False") << std::endl
    return 0;
}