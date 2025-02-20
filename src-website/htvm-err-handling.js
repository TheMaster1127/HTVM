

function LoopParseFunc(varString, delimiter1="", delimiter2="") {
    let items;
    if (!delimiter1 && !delimiter2) {
        // If no delimiters are provided, return an array of characters
        items = [...varString];
    } else {
        // Construct the regular expression pattern for splitting the string
        let pattern = new RegExp('[' + delimiter1.replace(/[.*+?^${}()|[\]\\]/g, '\\$&') + delimiter2.replace(/[.*+?^${}()|[\]\\]/g, '\\$&') + ']+');
        // Split the string using the constructed pattern
        items = varString.split(pattern);
    }
    return items;
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

// Function to find the position of needle in haystack (string overload)
function InStr(haystack, needle) {
    const pos = haystack.indexOf(needle);
    return (pos !== -1) ? pos + 1 : 0;
}

function Chr(number) {
    // Return the character corresponding to the Unicode code point, or an empty string if out of range
    return (number >= 0 && number <= 0x10FFFF) ? String.fromCharCode(number) : "";
}

function Trim(inputString) {
    return inputString ? inputString.trim() : "";
}

function StringTrimRight(input, numChars) {
    return (numChars <= input.length) ? input.substring(0, input.length - numChars) : input;
}


// htvm-err-handling.htvm
function handleError(htvmInstrText) {
    let fixTrim = "";
    items1 = LoopParseFunc(htvmInstrText, "\n", "\r")
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        fixTrim += Trim(A_LoopField1) + Chr(10);
    }
    htvmInstrText = StringTrimRight(fixTrim, 1);
    items2 = LoopParseFunc(htvmInstrText, "\n", "\r")
    for (let A_Index2 = 0; A_Index2 < items2.length + 0; A_Index2++) {
        const A_LoopField2 = items2[A_Index2 - 0];
        if (InStr(A_LoopField2, Chr(34))) {
            throw new Error("You cant use " + Chr(34) + " in line " + STR(A_Index2 + 1) + "!!!");
        }
        if (InStr(A_LoopField2, Chr(39))) {
            throw new Error("You cant use " + Chr(39) + " in line " + STR(A_Index2 + 1) + "!!!");
        }
        if (InStr(A_LoopField2, Chr(123))) {
            throw new Error("You cant use " + Chr(123) + " in line " + STR(A_Index2 + 1) + "!!!");
        }
        if (InStr(A_LoopField2, Chr(125))) {
            throw new Error("You cant use " + Chr(125) + " in line " + STR(A_Index2 + 1) + "!!!");
        }
    }
    return "noERROR";
}
