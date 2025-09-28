

function print(value) {
    console.log(value)
}

// Convert value to string
function STR(value) {
    if (value === null || value === undefined) {
        return ""; // Return a string for null or undefined
    } else if (typeof value === 'number') {
        return value.toString();
    } else if (typeof value === 'boolean') {
        return value ? "1" : "0";
    } else if (typeof value === 'string') {
        return value; // Return the string as is
    } else {
        // Handle any unexpected types gracefully
        return String(value); // Convert any other type to a string
    }
}

// Function to simulate input() in JavaScript
function input(promptText) {
    // Display the prompt and get user input
    return prompt(promptText);
}

function Chr(number) {
    // Return the character corresponding to the Unicode code point, or an empty string if out of range
    return (number >= 0 && number <= 0x10FFFF) ? String.fromCharCode(number) : "";
}


async function main() {
    var var1 = 5;
    var var2 = 6;
    var shakdaz = "swdesfdg";
    var var3 = 7;
    print("Hello world");
    input("(PRESS ENTER TO CONTINUE) - Breakpoint: 1" + Chr(10) + "============================================" + Chr(10) + "var1: " + STR(var1) + Chr(10) + "var2: " + STR(var2) + Chr(10) + "shakdaz: " + STR(shakdaz) + Chr(10) + "var3: " + STR(var3));

}
main();