

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

function StrLen(s) {
    // Return the length of the given string
    return s.length;
}

function Chr(number) {
    // Return the character corresponding to the Unicode code point, or an empty string if out of range
    return (number >= 0 && number <= 0x10FFFF) ? String.fromCharCode(number) : "";
}

function Exp(value) {
    return Math.exp(value);
}

function SubStr(str, startPos, length = -1) {
    let result = "";
    let strLen = str.length;
    // Handle negative starting positions (counting from the end)
    if (startPos < 0) {
        startPos = strLen + startPos;
        if (startPos < 0) startPos = 0;  // Ensure it doesn't go beyond the start of the string
    } else {
        startPos -= 1; // Convert to 0-based index for internal operations
    }
    // Handle length
    if (length < 0) {
        length = strLen - startPos; // Length to the end of the string
    } else if (startPos + length > strLen) {
        length = strLen - startPos; // Adjust length to fit within the string
    }
    // Extract the substring
    result = str.substr(startPos, length);
    return result;
}

function Trim(inputString) {
    return inputString ? inputString.trim() : "";
}

function StringTrimRight(input, numChars) {
    return (numChars <= input.length) ? input.substring(0, input.length - numChars) : input;
}

function Mod(dividend, divisor) {
    return dividend % divisor;
}

// RegExMatch
function RegExMatch(haystack, needle) {
    const regex = new RegExp(needle);
    const match = haystack.match(regex);
    return match ? match.index + 1 : 0; // 1-based index or 0 if no match
}

function HTVM_Size(arr) {
    return arr.length;
}


// htvm-err-handling.htvm
// Helper function to check for disallowed characters based on mode.
// Mode 0: Check if any disallowed char exists anywhere in the line.
// Mode 1: Check if any disallowed char exists ONLY at the beginning of the line.
// Mode 2: Check if any disallowed char exists ONLY at the end of the line.
// Returns true if a disallowed character is found according to the mode, false otherwise.
function handleErrorHelper(theArray, line, mode = 0) {
    if (mode == 0) {
        var found = false;
        for (let A_Index1 = 0; A_Index1 < HTVM_Size(theArray) + 0; A_Index1++) {
            if (InStr(line, theArray[A_Index1])) {
                found = true;
                break;
            }
        }
        return found;
    }
    else if (mode == 1) {
        if (StrLen(line) == 0) {
            return false;
        }
        var firstChar = SubStr(line, 1, 1);
        var foundAtStart = false;
        for (let A_Index2 = 0; A_Index2 < HTVM_Size(theArray) + 0; A_Index2++) {
            if (firstChar == theArray[A_Index2]) {
                foundAtStart = true;
                break;
            }
        }
        return foundAtStart;
    }
    else if (mode == 2) {
        var len = StrLen(line);
        if (len == 0) {
            return false;
        }
        var lastChar = SubStr(line, len, 1);
        var foundAtEnd = false;
        for (let A_Index3 = 0; A_Index3 < HTVM_Size(theArray) + 0; A_Index3++) {
            if (lastChar == theArray[A_Index3]) {
                foundAtEnd = true;
                break;
            }
        }
        return foundAtEnd;
    }
    return false;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function handleError(htvmInstrText) {
    var fixTrim = "";
    items4 = LoopParseFunc(htvmInstrText, "\n", "\r")
    for (let A_Index4 = 0; A_Index4 < items4.length + 0; A_Index4++) {
        const A_LoopField4 = items4[A_Index4 - 0];
        fixTrim += Trim(A_LoopField4) + Chr(10);
    }
    htvmInstrText = StringTrimRight(fixTrim, 1);
    // double quote newline carriage return
    let disallowedChars_Globaly = [Chr(34), Chr(10), Chr(13)];
    var disallowedChars_Globaly_EXPLAIN = "double quote, newline, carriage return";
    // "double quote newline carriage return ( ) [ ] { }"
    let disallowedChars_InExprTranspiler = [Chr(34), Chr(10), Chr(13), Chr(40), Chr(41), Chr(91), Chr(93), Chr(123), Chr(125)];
    var disallowedChars_InExprTranspiler_EXPLAIN = "double quote, newline, carriage return, (, ), [, ], {, }";
    // "double quote newline carriage return ( ) [ ] { }"
    let disallowedChars_BeginEndLine = [Chr(34), Chr(10), Chr(13), Chr(40), Chr(41), Chr(91), Chr(93), Chr(123), Chr(125)];
    var disallowedChars_BeginEndLine_EXPLAIN = "double quote, newline, carriage return, (, ), [, ], {, }";
    // "double quote newline carriage return ( ) [ ] { } :"
    let disallowedChars_AT_THE_END = [Chr(34), Chr(10), Chr(13), Chr(40), Chr(41), Chr(91), Chr(93), Chr(123), Chr(125), Chr(58)];
    var disallowedChars_AT_THE_END_EXPLAIN = "double quote, newline, carriage return, (, ), [, ], {, }, :";
    // "double quote newline carriage return ( ) { }"
    let disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD = [Chr(34), Chr(10), Chr(13), Chr(40), Chr(41), Chr(123), Chr(125)];
    var disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD_EXPLAIN = "double quote, newline, carriage return, (, ), {, }";
    // "double quote newline carriage return ( ) { } :"
    let disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD = [Chr(34), Chr(10), Chr(13), Chr(40), Chr(41), Chr(123), Chr(125), Chr(58)];
    var disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD_EXPLAIN = "double quote, newline, carriage return, (, ), {, }, :";
    // special/isolated
    // newline carriage return
    let disallowedChars_For_2 = [Chr(10), Chr(13)];
    var disallowedChars_For_2_EXPLAIN = "newline, carriage return";
    // double quote newline carriage return :
    let disallowedChars_For_46_47 = [Chr(34), Chr(10), Chr(13), Chr(58)];
    var disallowedChars_For_46_47_EXPLAIN = "double quote, newline, carriage return, :";
    // double quote newline carriage return
    let disallowedChars_For_103 = [Chr(34), Chr(10), Chr(13)];
    var disallowedChars_For_103_EXPLAIN = "double quote, newline, carriage return";
    // lines that cant have spacses
    let lineThatCANNOThaveSpacses = [0, 1, 46, 47, 84, 85, 86, 87, 88, 89, 103, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161];
    // special stuff
    // 0. we can only have those
    let onlyAllowed_0 = ["cpp", "py", "js", "go", "lua", "cs", "java", "kt", "rb", "nim", "ahk", "swift", "dart", "ts", "groovy"];
    // 1. for matching custom file extensions in HTVM we only allow them to start with a lowercase letter, followed by lowercase letters or numbers, and be at least 2 characters long.
    // This is the regex: "^[a-z][a-z0-9]{1,}$"
    // 2. this is complex so um i will just leave it and just use disallowedChars_For_2 array to check if any of those chars exists.
    // 3 - 9 - for OSP and include - so just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine, disallowedChars_AT_THE_END
    // 10 - 45 - programming blocks - so just use the following arrays disallowedChars_Globaly
    // 46 and 47 - this are keyWordCurlyBraceOpen and keyWordCurlyBraceClose so no spacses and use the arrays disallowedChars_For_46_47, disallowedChars_Globaly
    // 48 - 83 - types and constructs - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine, disallowedChars_AT_THE_END
    // 84 - 89 - array methods - for the array methods, they must have NO SPACE and must start with a dot (.) followed by at least one character from [A-Za-z0-9_]. Use the regex "^\\.[A-Za-z0-9_]+$"
    // 90 - 102 - ArrayDefinition and some more - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD
    // 103 is the keyWordEscpaeChar so it must be any char BUT MUST BE 1 single char NOT MORE THEN 1 CHAR and use the array disallowedChars_Globaly, disallowedChars_For_103
    // 104 - 128 - some operators - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine, disallowedChars_AT_THE_END
    // 129 - 141 - for Assignment operators - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD AND NO SPACSES
    // 142 and 143 - the ternary operators - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD
    // 144 and 145 - (++ and --) - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine, disallowedChars_AT_THE_END
    // 146 - Use the regex "^-?\\d+$" ONLY and disallowedChars_Globaly ig
    // 147 and 148 - A_Index and A_LoopField ARE CUSTOMIZABLE so NO SPACE and use the arrays disallowedChars_Globaly and Use the regex "^[a-zA-Z_][a-zA-Z0-9_]*$"
    // 149 - 161 - settings ONLY allow "on" and "off" THATS IT but the website will automatically handle it since it's a toggle switch and will put "on" or "off"
    //;;;;;;;;;;;;;;;;;;;;;;; thats all HTVM options 162 of them
    var for0 = 0;
    var AIndex = 0;
    var ALoopField = "";
    items5 = LoopParseFunc(htvmInstrText, "\n", "\r")
    for (let A_Index5 = 0; A_Index5 < items5.length + 0; A_Index5++) {
        const A_LoopField5 = items5[A_Index5 - 0];
        AIndex = A_Index5;
        ALoopField = A_LoopField5;
        for (let A_Index6 = 0; A_Index6 < HTVM_Size(lineThatCANNOThaveSpacses) + 0; A_Index6++) {
            if (AIndex == lineThatCANNOThaveSpacses[A_Index6] && InStr(ALoopField, " ")) {
                return STR(AIndex) + "|You can't use a space here!!!.";
            }
        }
        // retun format is
        // index|error msg
        if (A_Index5 == 0) {
            // Code for condition 0
            for (let A_Index7 = 0; A_Index7 < HTVM_Size(onlyAllowed_0) + 0; A_Index7++) {
                if (A_LoopField5 == onlyAllowed_0[A_Index7]) {
                    for0 = 1;
                }
            }
            if (for0 == 0) {
                return STR(A_Index5) + "|You can only use: " + "" + Chr(34) + "cpp" + Chr(34) + ", " + Chr(34) + "py" + Chr(34) + ", " + Chr(34) + "js" + Chr(34) + ", " + Chr(34) + "go" + Chr(34) + ", " + Chr(34) + "lua" + Chr(34) + ", " + Chr(34) + "cs" + Chr(34) + ", " + Chr(34) + "java" + Chr(34) + ", " + Chr(34) + "kt" + Chr(34) + ", " + Chr(34) + "rb" + Chr(34) + ", " + Chr(34) + "nim" + Chr(34) + ", " + Chr(34) + "ahk" + Chr(34) + ", " + Chr(34) + "swift" + Chr(34) + ", " + Chr(34) + "dart" + Chr(34) + ", " + Chr(34) + "ts" + Chr(34) + ", " + Chr(34) + "groovy" + Chr(34);
            }
        }
        else if (A_Index5 == 1) {
            // Code for condition 1
            if (RegExMatch(A_LoopField5, "^[a-z][a-z0-9]{1,}$") == false) {
                return STR(A_Index5) + "|The file name must start with a lowercase letter and can only contain lowercase letters or numbers afterward.";
            }
        }
        else if (A_Index5 == 2) {
            // Code for condition 2
            if (InStr(A_LoopField5, Chr(13)) || InStr(A_LoopField5, Chr(10))) {
                return STR(A_Index5) + "|Dont use a newline or a carriage retrun";
            }
        }
        else if (A_Index5 >= 3 && A_Index5 <= 9) {
            // Code for conditions 3 - 9 (OSP and include)
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField5) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField5, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField5, 2)) {
                return STR(A_Index5) + "|You can't use the folowing characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
            }
        }
        else if (A_Index5 >= 10 && A_Index5 <= 45) {
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField5) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField5, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField5, 2)) {
                return STR(A_Index5) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
            }
        }
        else if (A_Index5 >= 46 && A_Index5 <= 47) {
            if (handleErrorHelper(disallowedChars_For_46_47, A_LoopField5) || handleErrorHelper(disallowedChars_Globaly, A_LoopField5)) {
                return STR(A_Index5) + "|You can't use the following characters: " + disallowedChars_For_46_47_EXPLAIN + ", " + disallowedChars_Globaly_EXPLAIN;
            }
        }
        else if (A_Index5 >= 48 && A_Index5 <= 83) {
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField5) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField5, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField5, 2)) {
                return STR(A_Index5) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
            }
        }
        else if (A_Index5 >= 84 && A_Index5 <= 89) {
            if (RegExMatch(A_LoopField5, "^\\.[A-Za-z0-9_]+$") == false) {
                return STR(A_Index5) + "|Array methods must start with a dot and contain only alphanumeric characters or underscores.";
            }
        }
        else if (A_Index5 >= 90 && A_Index5 <= 102) {
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField5) || handleErrorHelper(disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, A_LoopField5, 1) || handleErrorHelper(disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD, A_LoopField5, 2)) {
                return STR(A_Index5) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD_EXPLAIN + ", " + disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD_EXPLAIN;
            }
        }
        else if (A_Index5 == 103) {
            if (StrLen(A_LoopField5) != 1 || handleErrorHelper(disallowedChars_Globaly, A_LoopField5) || handleErrorHelper(disallowedChars_For_103, A_LoopField5)) {
                return STR(A_Index5) + "|Escape character must be a single valid character.";
            }
        }
        else if (A_Index5 >= 104 && A_Index5 <= 128) {
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField5) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField5, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField5, 2)) {
                return STR(A_Index5) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
            }
        }
        else if (A_Index5 >= 129 && A_Index5 <= 141) {
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField5) || handleErrorHelper(disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, A_LoopField5, 1) || handleErrorHelper(disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD, A_LoopField5, 2) || InStr(A_LoopField5, " ")) {
                return STR(A_Index5) + "|Assignment operators can't contain spaces and can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD_EXPLAIN + ", " + disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD_EXPLAIN;
            }
        }
        else if (A_Index5 >= 142 && A_Index5 <= 143) {
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField5) || handleErrorHelper(disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, A_LoopField5, 1)) {
                return STR(A_Index5) + "|Ternary operators can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD_EXPLAIN;
            }
        }
        else if (A_Index5 >= 144 && A_Index5 <= 145) {
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField5) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField5, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField5, 2)) {
                return STR(A_Index5) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
            }
        }
        else if (A_Index5 == 146) {
            if (RegExMatch(A_LoopField5, "^-?\\d+$") == false) {
                return STR(A_Index5) + "|Value must be a valid integer (optionally negative).";
            }
        }
        else if (A_Index5 >= 147 && A_Index5 <= 148) {
            if (RegExMatch(A_LoopField5, "^[a-zA-Z_][a-zA-Z0-9_]*$") == false) {
                return STR(A_Index5) + "|Variable names must start with a letter or underscore, and contain only alphanumeric characters and underscores.";
            }
        }
        else if (A_Index5 >= 149 && A_Index5 <= 161) {
            if (A_LoopField5 != "on" && A_LoopField5 != "off") {
                return STR(A_Index5) + "|Settings can only be 'on' or 'off'.";
            }
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;
        if (A_Index5 == 161) {
            break;
        }
    }
    return "noERROR";
}
