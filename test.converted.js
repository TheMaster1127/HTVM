

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
    var var1 = 0;
    for (let A_Index1 = 0; A_Index1 < 5; A_Index1++) {
        var1++;
        input("(PRESS ENTER TO CONTINUE) - Breakpoint: 1" + Chr(10) + "============================================" + Chr(10) + "var1: " + STR(var1));
        print(var1);
        input("(PRESS ENTER TO CONTINUE) - Breakpoint: 2" + Chr(10) + "============================================" + Chr(10) + "var1: " + STR(var1));
    }
    

}
main();