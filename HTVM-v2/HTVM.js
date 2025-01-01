

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

// Convert value to float
function FLOAT(value) {
    const floatValue = parseFloat(value);
    if (isNaN(floatValue)) {
        throw new TypeError("Cannot convert to float");
    }
    return floatValue;
}

function StrLen(s) {
    // Return the length of the given string
    return s.length;
}

function Exp(value) {
    return Math.exp(value);
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

function HTVM_getLang_HTVM() {
    return "js";
}

// HTVM_v2_HTVM()
let allArgs = "";
let noParams = false;
function HTVM_v2_HTVM() {
return
}



var str0 = "nothing";
var str00 = "nothing";
var str1 = "";
var str2 = "";
var str3 = "";
var str4 = "";
var str5 = "";
var str6 = "";
var str7 = "";
var str8 = "";
var str9 = "";
var str10 = "";
var str11 = "";
var str12 = "";
var str13 = "";
var str14 = "";
let argHTVMinstrMOVE = [];
var extraCodeReturned = "";
var langToConvertTo = "";
var langFileExtension = "";
async function compiler(code, instructionFile, mode, langToConvertToParam = "") {
    extraCodeReturned = "";
    var allInstructionFile = Trim(FileRead(instructionFile));
    items1 = LoopParseFunc(allInstructionFile, "\n", "\r")
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        if (A_Index1 == 0) {
            langToConvertTo = Trim(A_LoopField1);
        }
        if (A_Index1 == 1) {
            langFileExtension = Trim(A_LoopField1);
        }
        if (A_Index1 == 2) {
            var commands = Trim(A_LoopField1);
        }
        if (A_Index1 == 3) {
            var keyWordAlliance = Trim(A_LoopField1);
        }
        if (A_Index1 == 4) {
            var keyWordCrew = Trim(A_LoopField1);
        }
        if (A_Index1 == 5) {
            var keyWordMethod = Trim(A_LoopField1);
        }
        if (A_Index1 == 6) {
            var keyWordDefObj = Trim(A_LoopField1);
        }
        if (A_Index1 == 7) {
            var keyWordPorp = Trim(A_LoopField1);
        }
        if (A_Index1 == 8) {
            var keyWordThis = Trim(A_LoopField1);
        }
        if (A_Index1 == 9) {
            var keyWordInclude = Trim(A_LoopField1);
        }
        if (A_Index1 == 10) {
            var keyWordIncludeInTheTranspiledLang = Trim(A_LoopField1);
        }
        if (A_Index1 == 11) {
            var keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField1);
        }
        if (A_Index1 == 12) {
            var keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField1);
        }
        if (A_Index1 == 13) {
            var keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField1);
        }
        if (A_Index1 == 14) {
            var keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField1);
        }
        if (A_Index1 == 15) {
            var keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField1);
        }
        if (A_Index1 == 16) {
            var keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField1);
        }
        if (A_Index1 == 17) {
            var keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField1);
        }
        if (A_Index1 == 18) {
            var keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField1);
        }
        if (A_Index1 == 19) {
            var keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField1);
        }
        if (A_Index1 == 20) {
            var keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField1);
        }
        if (A_Index1 == 21) {
            var keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField1);
        }
        if (A_Index1 == 22) {
            var keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField1);
        }
        if (A_Index1 == 23) {
            var keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField1);
        }
        if (A_Index1 == 24) {
            var keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField1);
        }
        if (A_Index1 == 25) {
            var keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField1);
        }
        if (A_Index1 == 26) {
            var keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField1);
        }
        if (A_Index1 == 27) {
            var keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField1);
        }
        if (A_Index1 == 28) {
            var keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField1);
        }
        if (A_Index1 == 29) {
            var keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField1);
        }
        if (A_Index1 == 30) {
            var keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField1);
        }
        if (A_Index1 == 31) {
            var keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField1);
        }
        if (A_Index1 == 32) {
            var keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField1);
        }
        if (A_Index1 == 33) {
            var keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField1);
        }
        if (A_Index1 == 34) {
            var keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField1);
        }
        if (A_Index1 == 35) {
            var keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField1);
        }
        if (A_Index1 == 36) {
            var keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField1);
        }
        if (A_Index1 == 37) {
            var keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField1);
        }
        if (A_Index1 == 38) {
            var keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField1);
        }
        if (A_Index1 == 39) {
            var keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField1);
        }
        if (A_Index1 == 40) {
            var keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField1);
        }
        if (A_Index1 == 41) {
            var keyWordCodeInTheTranspiledLangStartSCALA = Trim(A_LoopField1);
        }
        if (A_Index1 == 42) {
            var keyWordCodeInTheTranspiledLangEndSCALA = Trim(A_LoopField1);
        }
        if (A_Index1 == 43) {
            var keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField1);
        }
        if (A_Index1 == 44) {
            var keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField1);
        }
        if (A_Index1 == 45) {
            var keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField1);
        }
        if (A_Index1 == 46) {
            var keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField1);
        }
        if (A_Index1 == 47) {
            var keyWordCodeInHTVMstart = Trim(A_LoopField1);
        }
        if (A_Index1 == 48) {
            var keyWordCodeInHTVMend = Trim(A_LoopField1);
        }
        if (A_Index1 == 49) {
            var keyWordCodeInOtherHTVMsyntaxStart = Trim(A_LoopField1);
        }
        if (A_Index1 == 50) {
            var keyWordCodeInOtherHTVMsyntaxStart = Trim(A_LoopField1);
        }
        if (A_Index1 == 51) {
            var keyWordCurlyBraceOpen = Trim(A_LoopField1);
        }
        if (A_Index1 == 52) {
            var keyWordCurlyBraceClose = Trim(A_LoopField1);
        }
        if (A_Index1 == 53) {
            var keyWordNull = Trim(A_LoopField1);
        }
        if (A_Index1 == 54) {
            var keyWordTrue = Trim(A_LoopField1);
        }
        if (A_Index1 == 55) {
            var keyWordFalse = Trim(A_LoopField1);
        }
        if (A_Index1 == 56) {
            var keyWordVoid = Trim(A_LoopField1);
        }
        if (A_Index1 == 57) {
            var keyWordDouble = Trim(A_LoopField1);
        }
        if (A_Index1 == 58) {
            var keyWordChar = Trim(A_LoopField1);
        }
        if (A_Index1 == 59) {
            var keyWordUint8 = Trim(A_LoopField1);
        }
        if (A_Index1 == 60) {
            var keyWordUint16 = Trim(A_LoopField1);
        }
        if (A_Index1 == 61) {
            var keyWordUint32 = Trim(A_LoopField1);
        }
        if (A_Index1 == 62) {
            var keyWordUint64 = Trim(A_LoopField1);
        }
        if (A_Index1 == 63) {
            var keyWordINT = Trim(A_LoopField1);
        }
        if (A_Index1 == 64) {
            var keyWordSTR = Trim(A_LoopField1);
        }
        if (A_Index1 == 65) {
            var keyWordBOOL = Trim(A_LoopField1);
        }
        if (A_Index1 == 66) {
            var keyWordFLOAT = Trim(A_LoopField1);
        }
        if (A_Index1 == 67) {
            var keyWordINT8 = Trim(A_LoopField1);
        }
        if (A_Index1 == 68) {
            var keyWordINT16 = Trim(A_LoopField1);
        }
        if (A_Index1 == 69) {
            var keyWordINT32 = Trim(A_LoopField1);
        }
        if (A_Index1 == 70) {
            var keyWordINT64 = Trim(A_LoopField1);
        }
        if (A_Index1 == 71) {
            var keyWordIF = Trim(A_LoopField1);
        }
        if (A_Index1 == 72) {
            var keyWordElseIf = Trim(A_LoopField1);
        }
        if (A_Index1 == 73) {
            var keyWordElse = Trim(A_LoopField1);
        }
        if (A_Index1 == 74) {
            var keyWordSwitch = Trim(A_LoopField1);
        }
        if (A_Index1 == 75) {
            var keyWordSwitchCase = Trim(A_LoopField1);
        }
        if (A_Index1 == 76) {
            var keyWordSwitchDefault = Trim(A_LoopField1);
        }
        if (A_Index1 == 77) {
            var keyWordWhileLoop = Trim(A_LoopField1);
        }
        if (A_Index1 == 78) {
            var keyWordForLoop = Trim(A_LoopField1);
        }
        if (A_Index1 == 79) {
            var keyWordLoopInfinite = Trim(A_LoopField1);
        }
        if (A_Index1 == 80) {
            var keyWordLoop = Trim(A_LoopField1);
        }
        if (A_Index1 == 81) {
            var keyWordLoopParse = Trim(A_LoopField1);
        }
        if (A_Index1 == 82) {
            var keyWordContinue = Trim(A_LoopField1);
        }
        if (A_Index1 == 83) {
            var keyWordBreak = Trim(A_LoopField1);
        }
        if (A_Index1 == 84) {
            var keyWordFunc = Trim(A_LoopField1);
        }
        if (A_Index1 == 85) {
            var keyWordAwait = Trim(A_LoopField1);
        }
        if (A_Index1 == 86) {
            var keyWordAsync = Trim(A_LoopField1);
        }
        if (A_Index1 == 87) {
            var keyWordThrow = Trim(A_LoopField1);
        }
        if (A_Index1 == 88) {
            var keyWordErrorMsg = Trim(A_LoopField1);
        }
        if (A_Index1 == 89) {
            var keyWordTry = Trim(A_LoopField1);
        }
        if (A_Index1 == 90) {
            var keyWordCatch = Trim(A_LoopField1);
        }
        if (A_Index1 == 91) {
            var keyWordFinally = Trim(A_LoopField1);
        }
        if (A_Index1 == 92) {
            var keyWordReturnStatement = Trim(A_LoopField1);
        }
        if (A_Index1 == 93) {
            var keyWordArrayAppend = Trim(A_LoopField1);
        }
        if (A_Index1 == 94) {
            var keyWordArrayPop = Trim(A_LoopField1);
        }
        if (A_Index1 == 95) {
            var keyWordArraySize = Trim(A_LoopField1);
        }
        if (A_Index1 == 96) {
            var keyWordArrayInsert = Trim(A_LoopField1);
        }
        if (A_Index1 == 97) {
            var keyWordArrayRemove = Trim(A_LoopField1);
        }
        if (A_Index1 == 98) {
            var keyWordArrayIndexOf = Trim(A_LoopField1);
        }
        if (A_Index1 == 99) {
            var keyWordArrayDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 100) {
            var keyWordArrayOfIntegersDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 101) {
            var keyWordArrayOfStringsDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 102) {
            var keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 103) {
            var keyWordArrayOfBooleansDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 104) {
            var keyWordJavaScriptVar = Trim(A_LoopField1);
        }
        if (A_Index1 == 105) {
            var keyWordJavaScriptLet = Trim(A_LoopField1);
        }
        if (A_Index1 == 106) {
            var keyWordJavaScriptConst = Trim(A_LoopField1);
        }
        if (A_Index1 == 107) {
            var keyWordEnd = Trim(A_LoopField1);
        }
        if (A_Index1 == 108) {
            var keyWordGlobal = Trim(A_LoopField1);
        }
        if (A_Index1 == 109) {
            var keyWordComment = Trim(A_LoopField1);
        }
        if (A_Index1 == 110) {
            var keyWordCommentOpenMultiLine = Trim(A_LoopField1);
        }
        if (A_Index1 == 111) {
            var keyWordCommentCloseMultiLine = Trim(A_LoopField1);
        }
        if (A_Index1 == 112) {
            var keyWordEscpaeChar = Trim(A_LoopField1);
        }
        if (A_Index1 == 113) {
            var keyWordMainLabel = Trim(A_LoopField1);
        }
        if (A_Index1 == 114) {
            var keyWordConcat = Trim(A_LoopField1);
        }
        if (A_Index1 == 115) {
            var keyWordAdd = Trim(A_LoopField1);
        }
        if (A_Index1 == 116) {
            var keyWordSub = Trim(A_LoopField1);
        }
        if (A_Index1 == 117) {
            var keyWordMul = Trim(A_LoopField1);
        }
        if (A_Index1 == 118) {
            var keyWordDiv = Trim(A_LoopField1);
        }
        if (A_Index1 == 119) {
            var keyWordMod = Trim(A_LoopField1);
        }
        if (A_Index1 == 120) {
            var keyWordExp = Trim(A_LoopField1);
        }
        if (A_Index1 == 121) {
            var keyWordEqual = Trim(A_LoopField1);
        }
        if (A_Index1 == 122) {
            var keyWordStrictEqual = Trim(A_LoopField1);
        }
        if (A_Index1 == 123) {
            var keyWordNotEqual = Trim(A_LoopField1);
        }
        if (A_Index1 == 124) {
            var keyWordGreater = Trim(A_LoopField1);
        }
        if (A_Index1 == 125) {
            var keyWordLess = Trim(A_LoopField1);
        }
        if (A_Index1 == 126) {
            var keyWordGreaterEqual = Trim(A_LoopField1);
        }
        if (A_Index1 == 127) {
            var keyWordLessEqual = Trim(A_LoopField1);
        }
        if (A_Index1 == 128) {
            var keyWordAnd = Trim(A_LoopField1);
        }
        if (A_Index1 == 129) {
            var keyWordOr = Trim(A_LoopField1);
        }
        if (A_Index1 == 130) {
            var keyWordNot = Trim(A_LoopField1);
        }
        if (A_Index1 == 131) {
            var keyWordBitAnd = Trim(A_LoopField1);
        }
        if (A_Index1 == 132) {
            var keyWordBitOr = Trim(A_LoopField1);
        }
        if (A_Index1 == 133) {
            var keyWordBitXor = Trim(A_LoopField1);
        }
        if (A_Index1 == 134) {
            var keyWordBitNot = Trim(A_LoopField1);
        }
        if (A_Index1 == 135) {
            var keyWordShiftLeft = Trim(A_LoopField1);
        }
        if (A_Index1 == 136) {
            var keyWordShiftRight = Trim(A_LoopField1);
        }
        if (A_Index1 == 137) {
            var keyWordShiftUnsignedRight = Trim(A_LoopField1);
        }
        if (A_Index1 == 138) {
            var keyWordAssign = Trim(A_LoopField1);
        }
        if (A_Index1 == 139) {
            var keyWordAssignAdd = Trim(A_LoopField1);
        }
        if (A_Index1 == 140) {
            var keyWordAssignConcat = Trim(A_LoopField1);
        }
        if (A_Index1 == 141) {
            var keyWordAssignSub = Trim(A_LoopField1);
        }
        if (A_Index1 == 142) {
            var keyWordAssignMul = Trim(A_LoopField1);
        }
        if (A_Index1 == 143) {
            var keyWordAssignDiv = Trim(A_LoopField1);
        }
        if (A_Index1 == 144) {
            var keyWordAssignMod = Trim(A_LoopField1);
        }
        if (A_Index1 == 145) {
            var keyWordAssignShiftLeft = Trim(A_LoopField1);
        }
        if (A_Index1 == 146) {
            var keyWordAssignShiftRight = Trim(A_LoopField1);
        }
        if (A_Index1 == 147) {
            var keyWordAssignBitAnd = Trim(A_LoopField1);
        }
        if (A_Index1 == 148) {
            var keyWordAssignBitOr = Trim(A_LoopField1);
        }
        if (A_Index1 == 149) {
            var keyWordAssignBitXor = Trim(A_LoopField1);
        }
        if (A_Index1 == 150) {
            var keyWordTernary1 = Trim(A_LoopField1);
        }
        if (A_Index1 == 151) {
            var keyWordTernary2 = Trim(A_LoopField1);
        }
        if (A_Index1 == 152) {
            var keyWordInc = Trim(A_LoopField1);
        }
        if (A_Index1 == 153) {
            var keyWordDec = Trim(A_LoopField1);
        }
        if (A_Index1 == 154) {
            var AHKlikeLoopsIndexedAt = Trim(A_LoopField1);
        }
        if (A_Index1 == 155) {
            var keyWordAIndex = Trim(A_LoopField1);
        }
        if (A_Index1 == 156) {
            var keyWordALoopField = Trim(A_LoopField1);
        }
        if (A_Index1 == 157) {
            var keyWordAllianceEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 158) {
            var keyWordCrewEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 159) {
            var keyWordMethodEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 160) {
            var keyWordDefObjEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 161) {
            var keyWordIFEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 162) {
            var keyWordElseIfEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 163) {
            var keyWordElseEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 164) {
            var keyWordSwitchEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 165) {
            var keyWordSwitchCaseEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 166) {
            var keyWordWhileLoopEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 167) {
            var keyWordForLoopEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 168) {
            var keyWordLoopInfiniteEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 169) {
            var keyWordLoopEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 170) {
            var keyWordLoopParseEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 171) {
            var keyWordFuncEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 172) {
            var keyWordTryEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 173) {
            var keyWordCatchEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 174) {
            var keyWordFinallyEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 175) {
            var useFuncKeyWord = Trim(A_LoopField1);
        }
        if (A_Index1 == 176) {
            var useCurlyBraces = Trim(A_LoopField1);
        }
        if (A_Index1 == 177) {
            var useEnd = Trim(A_LoopField1);
        }
        if (A_Index1 == 178) {
            var useEndExtraInfo = Trim(A_LoopField1);
        }
        if (A_Index1 == 179) {
            var useSemicolon = Trim(A_LoopField1);
        }
        if (A_Index1 == 180) {
            var useParentheses = Trim(A_LoopField1);
        }
        if (A_Index1 == 181) {
            var usePrefixTypeForTypeDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 182) {
            var usePostfixTypeForTypeDefinition = Trim(A_LoopField1);
        }
        if (A_Index1 == 183) {
            var usePythonicColonSyntax = Trim(A_LoopField1);
        }
        if (A_Index1 == 184) {
            var useInJavaScriptAlwaysUseVar = Trim(A_LoopField1);
        }
        if (A_Index1 == 185) {
            var useJavaScriptInAfullHTMLfile = Trim(A_LoopField1);
        }
        if (A_Index1 == 186) {
            var useJavaScriptAmainFuncDef = Trim(A_LoopField1);
        }
        if (A_Index1 == 187) {
            var useJavaScriptAllFuncsAreAsync = Trim(A_LoopField1);
        }
        if (A_Index1 == 188) {
            var useJavaScriptAlwaysTripleEqual = Trim(A_LoopField1);
        }
    }
    if (Trim(langToConvertToParam) != "") {
        langToConvertTo = Trim(langToConvertToParam);
    }
    var isFullHTVMCode = 0;
    if (Trim(mode) == "full") {
        isFullHTVMCode = 1;
    } else {
        isFullHTVMCode = 0;
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    /*
    if (langToConvertTo == "htvm") {
    }
    if (langToConvertTo == "cpp") {
    }
    if (langToConvertTo == "py") {
    }
    if (langToConvertTo == "js") {
    }
    if (langToConvertTo == "go") {
    }
    if (langToConvertTo == "lua") {
    }
    if (langToConvertTo == "cs") {
    }
    if (langToConvertTo == "java") {
    }
    if (langToConvertTo == "kt") {
    }
    if (langToConvertTo == "rb") {
    }
    if (langToConvertTo == "nim") {
    }
    if (langToConvertTo == "ahk") {
    }
    if (langToConvertTo == "swift") {
    }
    if (langToConvertTo == "dart") {
    }
    if (langToConvertTo == "ts") {
    }
    if (langToConvertTo == "scala") {
    }
    if (langToConvertTo == "groovy") {
    }
    */
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var HTVMout = "";
    var code = Trim(code);
    if (langToConvertTo == "htvm") {
        HTVMout = "0";
    }
    if (langToConvertTo == "cpp") {
        HTVMout = "0";
    }
    if (langToConvertTo == "py") {
        HTVMout = "0";
    }
    if (langToConvertTo == "js") {
        HTVMout = "0";
    }
    if (langToConvertTo == "go") {
        HTVMout = "0";
    }
    if (langToConvertTo == "lua") {
        HTVMout = "0";
    }
    if (langToConvertTo == "cs") {
        HTVMout = "0";
    }
    if (langToConvertTo == "java") {
        HTVMout = "0";
    }
    if (langToConvertTo == "kt") {
        HTVMout = "0";
    }
    if (langToConvertTo == "rb") {
        HTVMout = "0";
    }
    if (langToConvertTo == "nim") {
        HTVMout = "0";
    }
    if (langToConvertTo == "ahk") {
        HTVMout = "0";
    }
    if (langToConvertTo == "swift") {
        HTVMout = "0";
    }
    if (langToConvertTo == "dart") {
        HTVMout = "0";
    }
    if (langToConvertTo == "ts") {
        HTVMout = "0";
    }
    if (langToConvertTo == "scala") {
        HTVMout = "0";
    }
    if (langToConvertTo == "groovy") {
        HTVMout = "0";
    }
    print(code);
    print(instructionFile);
    print(mode);
    print(langToConvertTo);
    print("==================================");
    print("==================================");
    print("==================================");
    print("==================================");
    print("==================================");
    print(allInstructionFile);
    var codeOutFix1 = "";
    items2 = LoopParseFunc(code, "\n", "\r")
    for (let A_Index2 = 0; A_Index2 < items2.length + 0; A_Index2++) {
        const A_LoopField2 = items2[A_Index2 - 0];
        codeOutFix1 += Trim(A_LoopField2) + "\n";
    }
    codeOutFix1 = StringTrimRight(codeOutFix1, 1);
    return HTVMout;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
async function HTVMv2() {
    var argCODE = "";
    var argCODEfile = "";
    var argHTVMinstr = "";
    var argLangTo = "";
    var OUTCODE = "null";
    HTVM_v2_HTVM();
    if (noParams == true) {
        return;
    }
    items3 = LoopParseFunc(str0)
    for (let A_Index3 = 0; A_Index3 < items3.length + 0; A_Index3++) {
        const A_LoopField3 = items3[A_Index3 - 0];
        str00 = Trim(A_LoopField3);
        str00 = StringTrimRight(str00, 1);
    }
    print("HTVM v2");
    if (HTVM_getLang_HTVM() == "cpp" || HTVM_getLang_HTVM() == "py") {
        if (HTVM_getLang_HTVM() == "cpp") {
            print("CPP");
        }
        if (HTVM_getLang_HTVM() == "py") {
            print("PY");
        }
        items4 = LoopParseFunc(allArgs, "\n", "\r")
        for (let A_Index4 = 0; A_Index4 < items4.length + 0; A_Index4++) {
            const A_LoopField4 = items4[A_Index4 - 0];
            if (A_Index4 == 0) {
                argCODE = FileRead(Trim(A_LoopField4));
                argCODEfile = Trim(A_LoopField4);
            }
            else if (A_Index4 == 1) {
                argHTVMinstr = Trim(A_LoopField4);
            }
            else if (A_Index4 == 2) {
                argLangTo = Trim(A_LoopField4);
            } else {
                argHTVMinstrMOVE.push(Trim(A_LoopField4));
            }
        }
        if (argLangTo != "") {
            OUTCODE = compiler(argCODE, argHTVMinstr, "full", argLangTo);
        } else {
            OUTCODE = compiler(argCODE, argHTVMinstr, "full");
        }
        FileDelete(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        FileAppend(OUTCODE, StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
    }
    if (HTVM_getLang_HTVM() == "js") {
        print("JS");
    }
}
HTVMv2();
