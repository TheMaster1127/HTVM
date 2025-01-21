

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

function print(value) {
    console.log(value)
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

function StringTrimRight(input, numChars) {
    return (numChars <= input.length) ? input.substring(0, input.length - numChars) : input;
}


async function main() {
    var htCode = "-- Function definition with a while loop and if-elseif-else inside it\nfunction myFunction()\n    local x = 1\n    while x " + Chr(60) + "= 3 do\n        -- if-elseif-else inside the while loop\n        if x == 1 then\n            print(" + Chr(34) + "x is 1" + Chr(34) + ")\n        end\n        elseif x == 2 then\n            print(" + Chr(34) + "x is 2" + Chr(34) + ")\n        end\n        else\n            print(" + Chr(34) + "x is 3" + Chr(34) + ")\n        end\n        x = x + 1\n    end\nend\n\n-- Call the function\nmyFunction()";
    let nextWordEndFix = [];
    items1 = LoopParseFunc(htCode, "\n", "\r")
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        nextWordEndFix.push(A_LoopField1);
    }
    nextWordEndFix.push(" ");
    var nextWordEndFixOut = "";
    items2 = LoopParseFunc(htCode, "\n", "\r")
    for (let A_Index2 = 0; A_Index2 < items2.length + 0; A_Index2++) {
        const A_LoopField2 = items2[A_Index2 - 0];
        if (Trim(A_LoopField2) == "end" && SubStr(Trim(nextWordEndFix[A_Index2 + 1]), 1, StrLen("elseif ")) == "elseif " || Trim(A_LoopField2) == "end" && Trim(nextWordEndFix[A_Index2 + 1]) == "else") {
            nextWordEndFixOut += "";
        } else {
            nextWordEndFixOut += A_LoopField2 + "\n";
        }
    }
    htCode = StringTrimRight(nextWordEndFixOut, 1);
    print(htCode);
}
main();