

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

// Convert value to integer
function INT(value) {
    const intValue = parseInt(value, 10);
    if (Number.isNaN(intValue)) {
        console.warn(`Invalid input: ${value} cannot be converted to an integer.`);
        return 0;  // Or any other default value
    }
    return intValue;
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

function StringTrimLeft(input, numChars) {
    return (numChars <= input.length) ? input.substring(numChars) : input;
}

function StringTrimRight(input, numChars) {
    return (numChars <= input.length) ? input.substring(0, input.length - numChars) : input;
}

function StrLower(string) {
    return string.toLowerCase();
}

function StrSplit(inputStr, delimiter, num) {
    const parts = inputStr.split(delimiter);
    return (num > 0 && num <= parts.length) ? parts[num - 1] : "";
}

// RegExMatch
function RegExMatch(haystack, needle) {
    const regex = new RegExp(needle);
    const match = haystack.match(regex);
    return match ? match.index + 1 : 0; // 1-based index or 0 if no match
}

function HTVM_Append(arr, value) {
    arr.push(value);
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
        // Mode 0: Check anywhere in the line
        var found = false;
        for (let A_Index1 = 0; A_Index1 < HTVM_Size(theArray) + 0; A_Index1++) {
            // If a disallowed character is found IN the line
            if (InStr(line, theArray[A_Index1])) {
                found = true;
                break;
            }
        }
        // Return true if a disallowed character WAS found anywhere
        return found;
    }
    else if (mode == 1) {
        // Mode 1: Check ONLY the beginning of the line (first character)
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
        // Return true if a disallowed character WAS found at the start
        return foundAtStart;
    }
    else if (mode == 2) {
        // Mode 2: Check ONLY the end of the line (last character)
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
        // Return true if a disallowed character WAS found at the end
        return foundAtEnd;
    }
    // Default case if mode is invalid (shouldn't happen with current structure)
    return false;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Function to check for duplicate first words in a multi-line string
// Returns true if a duplicate first word is found, false otherwise.
function handleErrorHelper2(multiLineText) {
    var currentLine0BasedIndex = 0;
    var originalIndex = 0;
    var trimmedCurrentLine = "";
    var originalLine = "";
    var found = 0;
    var hold = "";
    let items4 = LoopParseFunc(multiLineText, "\n", "\r");
    for (let A_Index4 = 0; A_Index4 < items4.length + 0; A_Index4++) {
        const A_LoopField4 = items4[A_Index4 - 0];
        originalIndex = A_Index4;
        originalLine = A_LoopField4;
        if (A_Index4 <= 142) {
            let items5 = LoopParseFunc(multiLineText, "\n", "\r");
            for (let A_Index5 = 0; A_Index5 < items5.length + 0; A_Index5++) {
                const A_LoopField5 = items5[A_Index5 - 0];
                if (A_Index5 <= 142) {
                    trimmedCurrentLine = A_LoopField5;
                    currentLine0BasedIndex = A_Index5;
                    if (InStr(Trim(originalLine), " ")) {
                        hold = Trim(StrSplit(Trim(originalLine), " ", 1));
                        if (hold == Trim(trimmedCurrentLine)) {
                            found = 1;
                            break;
                        }
                    }
                }
            }
            if (found == 1) {
                break;
            }
        }
    }
    var result = "";
    if (found == 1) {
        result = STR(originalIndex) + ":" + originalLine + "-HTVM-SPLIT-HTVM~~|kngeuew8r7dygtosuwesdtesedfxo|~~HTVM-SPLIT-HTVM-" + STR(currentLine0BasedIndex) + ":" + trimmedCurrentLine;
        return result;
    }
    return "NONE";
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function handleError(htvmInstrText) {
    var fixTrim = "";
    let items6 = LoopParseFunc(htvmInstrText, "\n", "\r");
    for (let A_Index6 = 0; A_Index6 < items6.length + 0; A_Index6++) {
        const A_LoopField6 = items6[A_Index6 - 0];
        fixTrim += Trim(A_LoopField6) + Chr(10);
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
    let disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD = [Chr(34), Chr(10), Chr(13), Chr(40), Chr(41), Chr(123), Chr(125), Chr(91), Chr(93)];
    var disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD_EXPLAIN = "double quote, newline, carriage return, (, ), {, }, [, ]";
    // "double quote newline carriage return ( ) { } :"
    let disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD = [Chr(34), Chr(10), Chr(13), Chr(40), Chr(41), Chr(123), Chr(125), Chr(58), Chr(91), Chr(93];
    var disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD_EXPLAIN = "double quote, newline, carriage return, (, ), {, }, [, ], :";
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
    // 84 - 89 - array methods - for the array methods, they must have NO SPACE and must start with a dot (.) followed by at least one character from [A-Za-z0-9_]. Use the regex "^\.[A-Za-z0-9_]+$"
    // 90 - 102 - ArrayDefinition and some more - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD
    // 103 is the keyWordEscpaeChar so it must be any char BUT MUST BE 1 single char NOT MORE THEN 1 CHAR and use the array disallowedChars_Globaly, disallowedChars_For_103
    // 104 - 128 - some operators - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine, disallowedChars_AT_THE_END
    // 129 - 141 - for Assignment operators - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD AND NO SPACSES
    // 142 and 143 - the ternary operators - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD
    // 144 and 145 - (++ and --) - for those just use the following arrays disallowedChars_Globaly, disallowedChars_BeginEndLine, disallowedChars_AT_THE_END
    // 146 - Use the regex "^-?\d+$" ONLY and disallowedChars_Globaly ig
    // 147 and 148 - A_Index and A_LoopField ARE CUSTOMIZABLE so NO SPACE and use the arrays disallowedChars_Globaly and Use the regex "^[a-zA-Z_][a-zA-Z0-9_]*$"
    // 149 - 161 - settings ONLY allow "on" and "off" THATS IT but the website will automatically handle it since it's a toggle switch and will put "on" or "off"
    //;;;;;;;;;;;;;;;;;;;;;;; thats all HTVM options 162 of them
    var allName = "langToConvertTo" + Chr(10) + "langFileExtension" + Chr(10) + "commands" + Chr(10) + "keyWordAlliance" + Chr(10) + "keyWordCrew" + Chr(10) + "keyWordProc" + Chr(10) + "keyWordStruct" + Chr(10) + "keyWordProp" + Chr(10) + "keyWordThis" + Chr(10) + "keyWordInclude" + Chr(10) + "keyWordCodeInTheTranspiledLangStart" + Chr(10) + "keyWordCodeInTheTranspiledLangEnd" + Chr(10) + "keyWordCodeInTheTranspiledLangStartCPP" + Chr(10) + "keyWordCodeInTheTranspiledLangEndCPP" + Chr(10) + "keyWordCodeInTheTranspiledLangStartPY" + Chr(10) + "keyWordCodeInTheTranspiledLangEndPY" + Chr(10) + "keyWordCodeInTheTranspiledLangStartJS" + Chr(10) + "keyWordCodeInTheTranspiledLangEndJS" + Chr(10) + "keyWordCodeInTheTranspiledLangStartGO" + Chr(10) + "keyWordCodeInTheTranspiledLangEndGO" + Chr(10) + "keyWordCodeInTheTranspiledLangStartLUA" + Chr(10) + "keyWordCodeInTheTranspiledLangEndLUA" + Chr(10) + "keyWordCodeInTheTranspiledLangStartCS" + Chr(10) + "keyWordCodeInTheTranspiledLangEndCS" + Chr(10) + "keyWordCodeInTheTranspiledLangStartJAVA" + Chr(10) + "keyWordCodeInTheTranspiledLangEndJAVA" + Chr(10) + "keyWordCodeInTheTranspiledLangStartKT" + Chr(10) + "keyWordCodeInTheTranspiledLangEndKT" + Chr(10) + "keyWordCodeInTheTranspiledLangStartRB" + Chr(10) + "keyWordCodeInTheTranspiledLangEndRB" + Chr(10) + "keyWordCodeInTheTranspiledLangStartNIM" + Chr(10) + "keyWordCodeInTheTranspiledLangEndNIM" + Chr(10) + "keyWordCodeInTheTranspiledLangStartAHK" + Chr(10) + "keyWordCodeInTheTranspiledLangEndAHK" + Chr(10) + "keyWordCodeInTheTranspiledLangStartSWIFT" + Chr(10) + "keyWordCodeInTheTranspiledLangEndSWIFT" + Chr(10) + "keyWordCodeInTheTranspiledLangStartDART" + Chr(10) + "keyWordCodeInTheTranspiledLangEndDART" + Chr(10) + "keyWordCodeInTheTranspiledLangStartTS" + Chr(10) + "keyWordCodeInTheTranspiledLangEndTS" + Chr(10) + "keyWordCodeInTheTranspiledLangStartGROOVY" + Chr(10) + "keyWordCodeInTheTranspiledLangEndGROOVY" + Chr(10) + "keyWordCodeInTheTranspiledLangStartHTVM" + Chr(10) + "keyWordCodeInTheTranspiledLangEndHTVM" + Chr(10) + "keyWordCodeInHTVMstart" + Chr(10) + "keyWordCodeInHTVMend" + Chr(10) + "keyWordCurlyBraceOpen" + Chr(10) + "keyWordCurlyBraceClose" + Chr(10) + "keyWordNull" + Chr(10) + "keyWordTrue" + Chr(10) + "keyWordFalse" + Chr(10) + "keyWordVoid" + Chr(10) + "keyWordDouble" + Chr(10) + "keyWordChar" + Chr(10) + "keyWordUint8" + Chr(10) + "keyWordUint16" + Chr(10) + "keyWordUint32" + Chr(10) + "keyWordUint64" + Chr(10) + "keyWordINT" + Chr(10) + "keyWordSTR" + Chr(10) + "keyWordBOOL" + Chr(10) + "keyWordFLOAT" + Chr(10) + "keyWordINT8" + Chr(10) + "keyWordINT16" + Chr(10) + "keyWordINT32" + Chr(10) + "keyWordINT64" + Chr(10) + "keyWordIF" + Chr(10) + "keyWordElseIf" + Chr(10) + "keyWordElse" + Chr(10) + "keyWordWhileLoop" + Chr(10) + "keyWordLoopInfinite" + Chr(10) + "keyWordLoop" + Chr(10) + "keyWordLoopParse" + Chr(10) + "keyWordContinue" + Chr(10) + "keyWordBreak" + Chr(10) + "keyWordFunc" + Chr(10) + "keyWordAwait" + Chr(10) + "keyWordAsync" + Chr(10) + "keyWordThrow" + Chr(10) + "keyWordErrorMsg" + Chr(10) + "keyWordTry" + Chr(10) + "keyWordCatch" + Chr(10) + "keyWordFinally" + Chr(10) + "keyWordReturnStatement" + Chr(10) + "keyWordArrayAppend" + Chr(10) + "keyWordArrayPop" + Chr(10) + "keyWordArraySize" + Chr(10) + "keyWordArrayInsert" + Chr(10) + "keyWordArrayRemove" + Chr(10) + "keyWordArrayIndexOf" + Chr(10) + "keyWordArrayDefinition" + Chr(10) + "keyWordArrayOfIntegersDefinition" + Chr(10) + "keyWordArrayOfStringsDefinition" + Chr(10) + "keyWordArrayOfFloatingPointNumbersDefinition" + Chr(10) + "keyWordArrayOfBooleansDefinition" + Chr(10) + "keyWordVar" + Chr(10) + "keyWordLet" + Chr(10) + "keyWordConst" + Chr(10) + "keyWordEnd" + Chr(10) + "keyWordGlobal" + Chr(10) + "keyWordComment" + Chr(10) + "keyWordCommentOpenMultiLine" + Chr(10) + "keyWordCommentCloseMultiLine" + Chr(10) + "keyWordEscpaeChar" + Chr(10) + "keyWordMainLabel" + Chr(10) + "keyWordConcat" + Chr(10) + "keyWordAdd" + Chr(10) + "keyWordSub" + Chr(10) + "keyWordMul" + Chr(10) + "keyWordDiv" + Chr(10) + "keyWordMod" + Chr(10) + "keyWordExp" + Chr(10) + "keyWordEqual" + Chr(10) + "keyWordStrictEqual" + Chr(10) + "keyWordNotEqual" + Chr(10) + "keyWordGreater" + Chr(10) + "keyWordLess" + Chr(10) + "keyWordGreaterEqual" + Chr(10) + "keyWordLessEqual" + Chr(10) + "keyWordAnd" + Chr(10) + "keyWordOr" + Chr(10) + "keyWordNot" + Chr(10) + "keyWordBitAnd" + Chr(10) + "keyWordBitOr" + Chr(10) + "keyWordBitXor" + Chr(10) + "keyWordBitNot" + Chr(10) + "keyWordShiftLeft" + Chr(10) + "keyWordShiftRight" + Chr(10) + "keyWordShiftUnsignedRight" + Chr(10) + "keyWordAssign" + Chr(10) + "keyWordAssignAdd" + Chr(10) + "keyWordAssignConcat" + Chr(10) + "keyWordAssignSub" + Chr(10) + "keyWordAssignMul" + Chr(10) + "keyWordAssignDiv" + Chr(10) + "keyWordAssignMod" + Chr(10) + "keyWordAssignShiftLeft" + Chr(10) + "keyWordAssignShiftRight" + Chr(10) + "keyWordLogicalAssignShiftRight" + Chr(10) + "keyWordAssignBitAnd" + Chr(10) + "keyWordAssignBitOr" + Chr(10) + "keyWordAssignBitXor" + Chr(10) + "keyWordTernary1" + Chr(10) + "keyWordTernary2" + Chr(10) + "keyWordInc" + Chr(10) + "keyWordDec" + Chr(10) + "AHKlikeLoopsIndexedAt" + Chr(10) + "keyWordAIndex" + Chr(10) + "keyWordALoopField" + Chr(10) + "useCurlyBraces" + Chr(10) + "useEnd" + Chr(10) + "useSemicolon" + Chr(10) + "useParentheses" + Chr(10) + "usePrefixTypeForTypeDefinition" + Chr(10) + "usePostfixTypeForTypeDefinition" + Chr(10) + "usePythonicColonSyntax" + Chr(10) + "useCurlyBracesSyntaxForArrayDef" + Chr(10) + "useInJavaScriptAlwaysUseVar" + Chr(10) + "useJavaScriptInAfullHTMLfile" + Chr(10) + "useJavaScriptAmainFuncDef" + Chr(10) + "useJavaScriptAllFuncsAreAsync" + Chr(10) + "useJavaScriptAlwaysTripleEqual";
    let allNameARR = [];
    let items7 = LoopParseFunc(allName, "\n", "\r");
    for (let A_Index7 = 0; A_Index7 < items7.length + 0; A_Index7++) {
        const A_LoopField7 = items7[A_Index7 - 0];
        HTVM_Append(allNameARR, A_LoopField7);
    }
    var str1 = "";
    var str2 = "";
    var str3 = "";
    var str4 = "";
    var str5 = "";
    var str6 = "";
    var for0 = 0;
    var AIndex = 0;
    var ALoopField = "";
    var handleErrorHelper2OUT = "";
    let keywordIndices = [6,3,4,7,5,66,67,69,81,78,83,70,71,72,9,99,76,75,97,95,96,52,53,54,55,56,57,58,59,60,61,62,63,64,65,90,91,92,93,94];
    var foundKeywordIndices = 0;
    let items8 = LoopParseFunc(htvmInstrText, "\n", "\r");
    for (let A_Index8 = 0; A_Index8 < items8.length + 0; A_Index8++) {
        const A_LoopField8 = items8[A_Index8 - 0];
        AIndex = A_Index8;
        ALoopField = A_LoopField8;
        if (A_Index8 <= 148) {
            let items9 = LoopParseFunc(htvmInstrText, "\n", "\r");
            for (let A_Index9 = 0; A_Index9 < items9.length + 0; A_Index9++) {
                const A_LoopField9 = items9[A_Index9 - 0];
                if (A_Index9 <= 148) {
                    if (StrLower(ALoopField) == StrLower(A_LoopField9) && A_Index9 != AIndex) {
                        if (AIndex <= 148) {
                            return STR(AIndex) + "|You can't use the same keyword more than once. The problem is whit " + allNameARR[AIndex] + " and " + allNameARR[A_Index9] + "!!!";
                        }
                    }
                }
            }
        }
    }
    handleErrorHelper2OUT = handleErrorHelper2(htvmInstrText);
    if (handleErrorHelper2OUT != "NONE") {
        str1 = StrSplit(handleErrorHelper2OUT, "-HTVM-SPLIT-HTVM~~|kngeuew8r7dygtosuwesdtesedfxo|~~HTVM-SPLIT-HTVM-", 1);
        str2 = StrSplit(handleErrorHelper2OUT, "-HTVM-SPLIT-HTVM~~|kngeuew8r7dygtosuwesdtesedfxo|~~HTVM-SPLIT-HTVM-", 2);
        str3 = "";
        str4 = "";
        let items10 = LoopParseFunc(str1);
        for (let A_Index10 = 0; A_Index10 < items10.length + 0; A_Index10++) {
            const A_LoopField10 = items10[A_Index10 - 0];
            if (A_LoopField10 == ":") {
                break;
            } else {
                str3 += A_LoopField10;
            }
        }
        let items11 = LoopParseFunc(str2);
        for (let A_Index11 = 0; A_Index11 < items11.length + 0; A_Index11++) {
            const A_LoopField11 = items11[A_Index11 - 0];
            if (A_LoopField11 == ":") {
                break;
            } else {
                str4 += A_LoopField11;
            }
        }
        str5 = StringTrimLeft(str1, (StrLen(str3) + 1));
        str6 = StringTrimLeft(str2, (StrLen(str4) + 1));
        // 51 66
        // 90 94
        if ((INT(str3) >= 51 && INT(str3) <= 66) || (INT(str3) >= 90 && INT(str3) <= 94) || (INT(str3) >= 10 && INT(str3) <= 45)) {
            str1 = "";
            str2 = "";
            str3 = "";
            str4 = "";
            str5 = "";
            str6 = "";
        } else {
            str1 = allNameARR[INT(str3)];
            str2 = allNameARR[INT(str4)];
            foundKeywordIndices = 0;
            for (let A_Index12 = 0; A_Index12 < HTVM_Size(keywordIndices) + 0; A_Index12++) {
                if (keywordIndices[A_Index12] == INT(str3)) {
                    foundKeywordIndices++;
                }
                if (keywordIndices[A_Index12] == INT(str4)) {
                    foundKeywordIndices++;
                }
            }
            if (INT(str3) <= 142 && INT(str4) <= 142) {
                if (foundKeywordIndices == 2) {
                    if (str3 == 72 && str2 == "keyWordLoop" && str1 == "keyWordLoopParse") {
                        // 72|keyWordLoop and keyWordLoopParse have the same word at the beginning and we can't have the same first word for different keywords!!!
                    } else {
                        return str3 + "|" + str2 + " and " + str1 + " have the same word at the beginning and we can't have the same first word for different keywords!!!";
                    }
                }
            }
        }
    }
    let items13 = LoopParseFunc(htvmInstrText, "\n", "\r");
    for (let A_Index13 = 0; A_Index13 < items13.length + 0; A_Index13++) {
        const A_LoopField13 = items13[A_Index13 - 0];
        AIndex = A_Index13;
        ALoopField = A_LoopField13;
        for (let A_Index14 = 0; A_Index14 < HTVM_Size(lineThatCANNOThaveSpacses) + 0; A_Index14++) {
            if (AIndex == lineThatCANNOThaveSpacses[A_Index14] && InStr(ALoopField, " ")) {
                return STR(AIndex) + "|You can't use a space here!!!.";
            }
        }
        // retun format is
        // index|error msg
        if (A_Index13 == 0 || A_Index13 == 1) {
            // Code for condition 0 and 1
            if (RegExMatch(A_LoopField13, "^[a-z][a-z0-9]{1,}$") == false) {
                return STR(A_Index13) + "|The file name must start with a lowercase letter and can only contain lowercase letters or numbers afterward.";
            }
        }
        else if (A_Index13 == 2) {
            // Code for condition 2
            if (InStr(A_LoopField13, Chr(13)) || InStr(A_LoopField13, Chr(10))) {
                return STR(A_Index13) + "|Dont use a newline or a carriage return";
            }
        }
        else if (A_Index13 >= 3 && A_Index13 <= 9) {
            // Code for conditions 3 - 9 (OSP and include)
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField13) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField13, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField13, 2)) {
                return STR(A_Index13) + "|You can't use the folowing characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
            }
        }
        else if (A_Index13 >= 10 && A_Index13 <= 45) {
            // Code for programming blocks
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField13) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField13, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField13, 2)) {
                return STR(A_Index13) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
            }
        }
        else if (A_Index13 >= 46 && A_Index13 <= 47) {
            // Code for keyWordCurlyBraceOpen and keyWordCurlyBraceClose
            if (handleErrorHelper(disallowedChars_For_46_47, A_LoopField13) || handleErrorHelper(disallowedChars_Globaly, A_LoopField13)) {
                return STR(A_Index13) + "|You can't use the following characters: " + disallowedChars_For_46_47_EXPLAIN + ", " + disallowedChars_Globaly_EXPLAIN;
            }
        }
        else if (A_Index13 >= 48 && A_Index13 <= 83) {
            // Code for types and constructs
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField13) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField13, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField13, 2)) {
                return STR(A_Index13) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
            }
        }
        else if (A_Index13 >= 84 && A_Index13 <= 89) {
            // Code for array methods
            // No spaces allowed, must start with a dot (.) followed by at least one character from [A-Za-z0-9_]
            if (RegExMatch(A_LoopField13, "^\\.[A-Za-z0-9_]+$") == false) {
                return STR(A_Index13) + "|Array methods must start with a dot and contain only alphanumeric characters or underscores.";
            }
        }
        else if (A_Index13 >= 90 && A_Index13 <= 102) {
            // Code for ArrayDefinition and some more
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField13) || handleErrorHelper(disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, A_LoopField13, 1) || handleErrorHelper(disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD, A_LoopField13, 2)) {
                return STR(A_Index13) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD_EXPLAIN + ", " + disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD_EXPLAIN;
            }
        }
        else if (A_Index13 == 103) {
            // Code for keyWordEscapeChar
            // Must be a single character, and no disallowed characters
            if (StrLen(A_LoopField13) != 1 || handleErrorHelper(disallowedChars_Globaly, A_LoopField13) || handleErrorHelper(disallowedChars_For_103, A_LoopField13)) {
                return STR(A_Index13) + "|Escape character must be a single valid character.";
            }
        }
        else if (A_Index13 >= 104 && A_Index13 <= 128) {
            // Code for some operators
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField13) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField13, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField13, 2)) {
                return STR(A_Index13) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
            }
        }
        else if (A_Index13 >= 129 && A_Index13 <= 141) {
            // Code for Assignment operators
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField13) || handleErrorHelper(disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, A_LoopField13, 1) || handleErrorHelper(disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD, A_LoopField13, 2) || InStr(A_LoopField13, " ")) {
                return STR(A_Index13) + "|Assignment operators can't contain spaces and can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD_EXPLAIN + ", " + disallowedChars_AT_THE_END_FOR_ARRAY_KEYWORD_EXPLAIN;
            }
        }
        else if (A_Index13 >= 142 && A_Index13 <= 143) {
            // Code for ternary operators
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField13) || handleErrorHelper(disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD, A_LoopField13, 1)) {
                return STR(A_Index13) + "|Ternary operators can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_FOR_ARRAY_KEYWORD_EXPLAIN;
            }
        }
        else if (A_Index13 >= 144 && A_Index13 <= 145) {
            // Code for (++ and --)
            if (handleErrorHelper(disallowedChars_Globaly, A_LoopField13) || handleErrorHelper(disallowedChars_BeginEndLine, A_LoopField13, 1) || handleErrorHelper(disallowedChars_AT_THE_END, A_LoopField13, 2)) {
                return STR(A_Index13) + "|You can't use the following characters: " + disallowedChars_Globaly_EXPLAIN + ", " + disallowedChars_BeginEndLine_EXPLAIN + ", " + disallowedChars_AT_THE_END_EXPLAIN;
            }
        }
        else if (A_Index13 == 146) {
            // Code for regex "^-?\d+$"
            if (RegExMatch(A_LoopField13, "^-?\\d+$") == false) {
                return STR(A_Index13) + "|Value must be a valid integer (optionally negative).";
            }
        }
        else if (A_Index13 >= 147 && A_Index13 <= 148) {
            // Code for A_Index and A_LoopField (customizable variables)
            if (RegExMatch(A_LoopField13, "^[a-zA-Z_][a-zA-Z0-9_]*$") == false) {
                return STR(A_Index13) + "|Variable names must start with a letter or underscore, and contain only alphanumeric characters and underscores.";
            }
        }
        else if (A_Index13 >= 149 && A_Index13 <= 161) {
            // Code for settings (only "on" and "off")
            if (A_LoopField13 != "on" && A_LoopField13 != "off") {
                return STR(A_Index13) + "|Settings can only be 'on' or 'off'.";
            }
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;
        if (A_Index13 == 161) {
            break;
        }
    }
    return "noERROR";
}
// testing
//main
// testing
//print(handleError("cpp" . Chr(10) . "htvm" . Chr(10) . "StringTrimLeft,OUTVAR,INVAR,param1|StringTrimRight,OUTVAR,INVAR,param1|Random,OUTVAR,param1,param2|Sleep,INVAR|FileRead,OUTVAR,'param1|FileAppend,INVAR,'param1|FileDelete,'INVAR|Sort,INOUTVAR,'param1|MsgBox,'param1" . Chr(10) . "alliance" . Chr(10) . "crew" . Chr(10) . "proc" . Chr(10) . "struct" . Chr(10) . "prop" . Chr(10) . "this" . Chr(10) . "import" . Chr(10) . "___start" . Chr(10) . "___end" . Chr(10) . "___cpp start" . Chr(10) . "___cpp end" . Chr(10) . "___py start" . Chr(10) . "___py end" . Chr(10) . "___js start" . Chr(10) . "___js end" . Chr(10) . "___go start" . Chr(10) . "___go end" . Chr(10) . "___lua start" . Chr(10) . "___lua end" . Chr(10) . "___cs start" . Chr(10) . "___cs end" . Chr(10) . "___java start" . Chr(10) . "___java end" . Chr(10) . "___kt start" . Chr(10) . "___kt end" . Chr(10) . "___rb start" . Chr(10) . "___rb end" . Chr(10) . "___nim start" . Chr(10) . "___nim end" . Chr(10) . "___ahk start" . Chr(10) . "___ahk end" . Chr(10) . "___swift start" . Chr(10) . "___swift end" . Chr(10) . "___dart start" . Chr(10) . "___dart end" . Chr(10) . "___ts start" . Chr(10) . "___ts end" . Chr(10) . "___groovy start" . Chr(10) . "___groovy end" . Chr(10) . "___htvm start" . Chr(10) . "___htvm end" . Chr(10) . "___inhtvm start" . Chr(10) . "___inhtvm end" . Chr(10) . "{" . Chr(10) . "}" . Chr(10) . "null" . Chr(10) . "true" . Chr(10) . "false" . Chr(10) . "void" . Chr(10) . "double" . Chr(10) . "char" . Chr(10) . "uint8" . Chr(10) . "uint16" . Chr(10) . "uint32" . Chr(10) . "uint64" . Chr(10) . "int" . Chr(10) . "str" . Chr(10) . "bool" . Chr(10) . "float" . Chr(10) . "int8" . Chr(10) . "int16" . Chr(10) . "int32" . Chr(10) . "int64" . Chr(10) . "if" . Chr(10) . "else if" . Chr(10) . "else" . Chr(10) . "while" . Chr(10) . "Loop" . Chr(10) . "Loop," . Chr(10) . "Loop, Parse," . Chr(10) . "continue" . Chr(10) . "break" . Chr(10) . "func" . Chr(10) . "await" . Chr(10) . "async" . Chr(10) . "throw" . Chr(10) . "ErrorMsg" . Chr(10) . "try" . Chr(10) . "catch" . Chr(10) . "finally" . Chr(10) . "return" . Chr(10) . ".add" . Chr(10) . ".pop" . Chr(10) . ".size" . Chr(10) . ".insert" . Chr(10) . ".rm" . Chr(10) . ".indexOf" . Chr(10) . "arr" . Chr(10) . "arr int" . Chr(10) . "arr str" . Chr(10) . "arr float" . Chr(10) . "arr bool" . Chr(10) . "var" . Chr(10) . "let" . Chr(10) . "const" . Chr(10) . "end" . Chr(10) . "global" . Chr(10) . ";" . Chr(10) . "'''1" . Chr(10) . "'''2" . Chr(10) . "" . Chr(96) . "" . Chr(10) . "main" . Chr(10) . "." . Chr(10) . "+" . Chr(10) . "-" . Chr(10) . "*" . Chr(10) . "/" . Chr(10) . "%" . Chr(10) . "**" . Chr(10) . "=" . Chr(10) . "===" . Chr(10) . "!=" . Chr(10) . "" . Chr(62) . "" . Chr(10) . "" . Chr(60) . "" . Chr(10) . "" . Chr(62) . "=" . Chr(10) . "" . Chr(60) . "=" . Chr(10) . "and" . Chr(10) . "or" . Chr(10) . "!" . Chr(10) . "&" . Chr(10) . "|" . Chr(10) . "^" . Chr(10) . "~" . Chr(10) . "" . Chr(60) . "" . Chr(60) . "" . Chr(10) . "" . Chr(62) . "" . Chr(62) . "" . Chr(10) . "" . Chr(62) . "" . Chr(62) . "" . Chr(62) . "" . Chr(10) . ":=" . Chr(10) . "+=" . Chr(10) . ".=" . Chr(10) . "-=" . Chr(10) . "*=" . Chr(10) . "/=" . Chr(10) . "%=" . Chr(10) . "" . Chr(60) . "" . Chr(60) . "=" . Chr(10) . "" . Chr(62) . "" . Chr(62) . "=" . Chr(10) . "" . Chr(62) . "" . Chr(62) . "" . Chr(62) . "=" . Chr(10) . "&=" . Chr(10) . "|=" . Chr(10) . "^=" . Chr(10) . "?" . Chr(10) . ":" . Chr(10) . "++" . Chr(10) . "--" . Chr(10) . "0" . Chr(10) . "A_Index" . Chr(10) . "A_LoopField" . Chr(10) . "on" . Chr(10) . "off" . Chr(10) . "off" . Chr(10) . "on" . Chr(10) . "on" . Chr(10) . "off" . Chr(10) . "off" . Chr(10) . "off" . Chr(10) . "on" . Chr(10) . "off" . Chr(10) . "off" . Chr(10) . "on" . Chr(10) . "off" . Chr(10) . "" . Chr(10) . ""))


