

# 1. Function to reverse a string
def reverse_string(s):
    return s[::-1]

# 2. Function to calculate the factorial of a number
def factorial(n):
    if n <= 1:
        return 1
    return n * factorial(n - 1)

# 3. Function to check if a number is prime
def is_prime(num):
    if num <= 1:
        return False
    for i in range(2, int(num ** 0.5) + 1):
        if num % i == 0:
            return False
    return True


# Using the reverse_string function
reversed_str = reverse_string("Hello World")
print("Reversed string:", reversed_str)  # Output: "dlroW olleH"
# Using the factorial function
fact = factorial(5)
print("Factorial of 5:", fact)  # Output: 120
# Using the is_prime function
prime_check = is_prime(7)
print("Is 7 prime?", prime_check)  # Output: True
prime_check = is_prime(10)
print("Is 10 prime?", prime_check)  # Output: False