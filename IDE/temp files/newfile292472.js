

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

// Function to simulate input() in JavaScript
function input(promptText) {
    // Display the prompt and get user input
    return prompt(promptText);
}

function StrLen(s) {
    // Return the length of the given string
    return s.length;
}

function Chr(number) {
    // Return the character corresponding to the Unicode code point, or an empty string if out of range
    return (number >= 0 && number <= 0x10FFFF) ? String.fromCharCode(number) : "";
}

function SubStr(str, startPos, length) {
    // If str is null or undefined, return an empty string
    if (str === null || str === undefined) {
        return "";
    }
    // If length is not provided or is blank, default to "all characters"
    if (length === undefined || length === "") {
        length = str.length - startPos + 1;
    }
    // If startPos is less than 1, adjust it to start from the end of the string
    if (startPos < 1) {
        startPos = str.length + startPos;
    }
    // Extract the substring based on startPos and length
    return str.substr(startPos - 1, length);
}

function Trim(inputString) {
    return inputString ? inputString.trim() : "";
}

function StrReplace(originalString, find, replaceWith) {
    return originalString.split(find).join(replaceWith);
}

function StringTrimLeft(input, numChars) {
    return (numChars <= input.length) ? input.substring(numChars) : input;
}

function StringTrimRight(input, numChars) {
    return (numChars <= input.length) ? input.substring(0, input.length - numChars) : input;
}

function StrLower(string) {
    return string.toLowerCase();
}

function Mod(dividend, divisor) {
    return dividend % divisor;
}

function MsgBox(text, title = " ", value = 0, timeout = null) {
    return new Promise((resolve) => {
        // Define default options for the message box
        let defaultOptions = {
            title: title || " ", // Default title is empty
            text: text || "Press OK to continue.", // Default text if not provided
            showCancelButton: false, // Default is to not show Cancel button
            showDenyButton: false, // Default is to not show Deny button
            confirmButtonText: "OK", // Default text for OK button
            focusConfirm: true, // Default focus on OK button
        };
        let numOriginal = value;
        let num = numOriginal;
        let done1 = 0;
        let done2 = 0;
        let done3 = 0;
        let AIndex = 0;
        for (AIndex = 1; AIndex <= 1; AIndex++) {
            // Handle special case for value adjustments
            if (num >= 262144) {
                num = num - 262144;
                numOriginal = numOriginal - 262144;
            }
            if (num >= 256 && num < 500) {
                num = num - 256;
                done3 = 256;
            }
            if (num >= 512) {
                num = num - 512;
                done3 = 512;
            }
            if (num == 0) {
                done1 = 0;
                break;
            }
            if (num <= 6) {
                done1 = num;
                break;
            }
            if (num >= 64 && num < 64 * 2) {
                done2 = 64;
                if (num == 64) {
                    done1 = 0;
                    break;
                } else {
                    done1 = num - 64;
                    break;
                }
            }
            if (num >= 48 && num < 63) {
                done2 = 48;
                if (num == 48) {
                    done1 = 0;
                    break;
                } else {
                    done1 = num - 48;
                    break;
                }
            }
            if (num >= 32 && num < 47) {
                done2 = 32;
                if (num == 32) {
                    done1 = 0;
                    break;
                } else {
                    done1 = num - 32;
                    break;
                }
            }
            if (num >= 16 && num < 30) {
                done2 = 16;
                if (num == 16) {
                    done1 = 0;
                    break;
                } else {
                    done1 = num - 16;
                    break;
                }
            }
        }
        let doneAdded = done1 + done2 + done3;
        if (doneAdded !== numOriginal) {
            // displayMessage("The calc was wrong!");
        } else {
            // displayMessage("num was: " + numOriginal + "\ndone1: " + done1 + "\ndone2: " + done2 + "\ndone3: " + done3);
        }
        // Parse the value to determine the options for the message box
        if (done1 === 1) defaultOptions.showCancelButton = true;
        if (done1 === 3) {
            defaultOptions.showCancelButton = true;
            defaultOptions.showDenyButton = true;
        }
        if (done1 === 4) {
            defaultOptions.showDenyButton = true;
        }
        if (done1 === 5) {
            defaultOptions.showCancelButton = true;
        }
        if (done2 === 16) defaultOptions.icon = "error";
        if (done2 === 32) defaultOptions.icon = "question";
        if (done2 === 48) defaultOptions.icon = "warning";
        if (done2 === 64) defaultOptions.icon = "info";
        if (done3 === 256) defaultOptions.focusDeny = true;
        if (done3 === 512) defaultOptions.focusCancel = true;
        // Set timeout if provided
        if (timeout) {
            defaultOptions.timer = timeout * 1000; // Convert timeout to milliseconds
        }
        // Display the message box with the constructed options
        Swal.fire(defaultOptions).then((result) => {
            if (result.isConfirmed) {
                resolve("OK");
            } else if (result.isDenied) {
                resolve("No");
            } else {
                resolve("Cancel");
            }
        });
    });
}



// Helper function to create spaces
async function spaces(n) {
    var s = "";
    if (n != 0) {
        for (let A_Index1 = 0; A_Index1 < n + 0; A_Index1++) {
            s += " ";
        }
    }
    return s;
}
// Define the function to check odd spaces at the beginning
async function CheckOddLeadingSpaces(string123) {
    // Initialize a variable to count the spaces
    var spaceCount = 0;
    // Loop through the string one character at a time
    items2 = LoopParseFunc(string123)
    for (let A_Index2 = 0; A_Index2 < items2.length + 0; A_Index2++) {
        const A_LoopField2 = items2[A_Index2 - 0];
        // Check if the current character is a space
        if (A_LoopField2 == Chr(32)) {
            spaceCount++;
        } else {
            // When we hit a non-space character, break the loop
            break;
        }
    }
    // Return true if the number of spaces is odd, false otherwise
    var sdsfawasd = STR(Mod(spaceCount, 2) == 1);
    //MsgBox, % sdsfawasd
    return sdsfawasd;
}
async function LTrim(input) {
    var result = "";
    var foundNonSpace = false;
    items3 = LoopParseFunc(input)
    for (let A_Index3 = 0; A_Index3 < items3.length + 0; A_Index3++) {
        const A_LoopField3 = items3[A_Index3 - 0];
        if (A_LoopField3 != " " || foundNonSpace) {
            result += A_LoopField3;
            foundNonSpace = true;
        }
    }
    return result;
}
async function getLastChar(strippedString) {
    var lastChar;
    items4 = LoopParseFunc(strippedString)
    for (let A_Index4 = 0; A_Index4 < items4.length + 0; A_Index4++) {
        const A_LoopField4 = items4[A_Index4 - 0];
        lastChar = A_LoopField4;
    }
    return lastChar;
}
async function AddCurlyBraces(pythonCode) {
    var pythonCode = StrReplace(pythonCode, A_Tab, "    ");
    var result = "";
    var indentLevel = 0;
    var indent;
    var line;
    var stripped;
    items5 = LoopParseFunc(pythonCode, "\n", "\r")
    for (let A_Index5 = 0; A_Index5 < items5.length + 0; A_Index5++) {
        const A_LoopField5 = items5[A_Index5 - 0];
        line = A_LoopField5;
        stripped = Trim(line);
        if (stripped == "") {
            result += line + "\n";
            continue;
        }
        // Count leading spaces
        indent = StrLen(line) - StrLen(LTrim(line));
        //MsgBox, % indent
        // Close braces for unindents
        for (let A_Index6 = 0; ; A_Index6++) {
            if (indentLevel <= indent) {
                break;
            }
            indentLevel -= 4;
            result += spaces(indentLevel) + "}\n";
        }
        // Add opening brace for new blocks
        if (getLastChar(stripped) == ":" && SubStr(StrLower(Trim(A_LoopField5)), 1, StrLen(StrLower(keyWordComment))) != StrLower(keyWordComment)) {
            result += SubStr(line, 1, -1) + " {\n";
            indentLevel += 4;
        } else {
            result += line + "\n";
        }
    }
    // Close any remaining open braces
    for (let A_Index7 = 0; ; A_Index7++) {
        if (indentLevel <= 0) {
            break;
        }
        indentLevel -= 4;
        result += spaces(indentLevel) + "}\n";
    }
    return result;
}
async function RepeatSpaces(count) {
    var spaces = "";
    for (let A_Index8 = 0; A_Index8 < count + 0; A_Index8++) {
        spaces += Chr(32);
    }
    return spaces;
}
async function indent_nested_curly_braces(input_string, modeCurlyBracesOn) {
    var indent_size = 4;
    var current_indent = 0;
    var result;
    var trimmed_line;
    var resultOut;
    //MsgBox, % input_string
    items9 = LoopParseFunc(input_string, "\n", "\r")
    for (let A_Index9 = 0; A_Index9 < items9.length + 0; A_Index9++) {
        const A_LoopField9 = items9[A_Index9 - 0];
        trimmed_line = Trim(A_LoopField9);
        if (trimmed_line == Chr(123)) {
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n";
            current_indent = current_indent + indent_size;
        }
        else if (trimmed_line == Chr(125)) {
            current_indent = current_indent - indent_size;
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n";
        } else {
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n";
        }
    }
    if (modeCurlyBracesOn == 0) {
        var resultOut;
        items10 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index10 = 0; A_Index10 < items10.length + 0; A_Index10++) {
            const A_LoopField10 = items10[A_Index10 - 0];
            if (Trim(A_LoopField10) != "{" && Trim(A_LoopField10) != "}") {
                resultOut += A_LoopField10 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
    } else {
        // format curly braces in a K&R style
        let lookIntoFurture = [];
        items11 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index11 = 0; A_Index11 < items11.length + 0; A_Index11++) {
            const A_LoopField11 = items11[A_Index11 - 0];
            let lookIntoFurture += Trim(A_LoopField11);
        }
        let lookIntoFurture += " ";
        var resultOut;
        var skipNext = 0;
        items12 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index12 = 0; A_Index12 < items12.length + 0; A_Index12++) {
            const A_LoopField12 = items12[A_Index12 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (Trim(lookIntoFurture[A_Index12 + 1]) == "{") {
                resultOut += A_LoopField12 + " {\n";
                skipNext = 2;
            }
            if (skipNext == 0) {
                resultOut += A_LoopField12 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
        let lookIntoFurture2 = [];
        items13 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index13 = 0; A_Index13 < items13.length + 0; A_Index13++) {
            const A_LoopField13 = items13[A_Index13 - 0];
            let lookIntoFurture2 += Trim(A_LoopField13);
        }
        let lookIntoFurture2 += " ";
        resultOut = "";
        skipNext = 0;
        var addSpacesAtTheBegginig;
        items14 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index14 = 0; A_Index14 < items14.length + 0; A_Index14++) {
            const A_LoopField14 = items14[A_Index14 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (Trim(A_LoopField14) == "}" && Trim(lookIntoFurture2[A_Index14 + 1]) == "else {") {
                skipNext = 2;
                addSpacesAtTheBegginig = "";
                items15 = LoopParseFunc(A_LoopField14)
                for (let A_Index15 = 0; A_Index15 < items15.length + 0; A_Index15++) {
                    const A_LoopField15 = items15[A_Index15 - 0];
                    if (A_LoopField15 == " ") {
                        if (A_LoopField15 != " ") {
                            break;
                        }
                        addSpacesAtTheBegginig += A_LoopField15;
                    }
                }
                resultOut += addSpacesAtTheBegginig + "} else {\n";
            }
            if (skipNext == 0) {
                resultOut += A_LoopField14 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
    }
    resultOut = "";
    var ALoopField;
    items16 = LoopParseFunc(result, "\n", "\r")
    for (let A_Index16 = 0; A_Index16 < items16.length + 0; A_Index16++) {
        const A_LoopField16 = items16[A_Index16 - 0];
        if (CheckOddLeadingSpaces(A_LoopField16) == "1") {
            ALoopField = StringTrimLeft(A_LoopField16, 1);
            resultOut += ALoopField + "\n";
        } else {
            resultOut += A_LoopField16 + "\n";
        }
    }
    result = StringTrimRight(resultOut, 1);
    // Return the result
    return result;
}
async function main() {
}
main();