

// 1. Function to reverse a string
function reverseString(str) {
    return str.split('').reverse().join('');
}

// 2. Function to calculate the factorial of a number
function factorial(n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// 3. Function to check if a number is prime
function isPrime(num) {
    if (num <= 1) return false;
    for (let i = 2; i <= Math.sqrt(num); i++) {
        if (num % i === 0) return false;
    }
    return true;
}


// Using the reverseString function
let reversed = reverseString("Hello World");
console.log("Reversed string:", reversed);
// Using the factorial function
let fact = factorial(5);
console.log("Factorial of 5:", fact);
// Using the isPrime function
let primeCheck = isPrime(7);
console.log("Is 7 prime?", primeCheck);
primeCheck == isPrime(10);
console.log("Is 10 prime?", primeCheck);