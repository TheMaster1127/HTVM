

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

// Function to find the position of needle in haystack (string overload)
function InStr(haystack, needle) {
    const pos = haystack.indexOf(needle);
    return (pos !== -1) ? pos + 1 : 0;
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

function Exp(value) {
    return Math.exp(value);
}

function Log(value) {
    return Math.log10(value);
}

function SubStr(str, startPos, length = -1) {
    // If str is null or undefined, return an empty string
    if (str === null || str === undefined) {
        return "";
    }
    let strLen = str.length;
    
    // Handle negative starting positions (C++ style)
    if (startPos < 1) {
        startPos = strLen + startPos;
        if (startPos < 0) startPos = 0;
    } else {
        startPos -= 1; // Convert to 0-based index (C++ style)
    }

    // Handle length (C++ style)
    if (length < 0) {
        length = strLen - startPos; // Length to end of string
    } else if (startPos + length > strLen) {
        length = strLen - startPos; // Adjust length to fit within the string
    }

    // Extract the substring
    return str.substr(startPos, length);
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

function StrSplit(inputStr, delimiter, num) {
    const parts = inputStr.split(delimiter);
    return (num > 0 && num <= parts.length) ? parts[num - 1] : "";
}

function Mod(dividend, divisor) {
    return dividend % divisor;
}

function Sort(varName, options = "") {
    let delimiter = '\n'; // Default delimiter
    let delimiterIndex = options.indexOf('D');
    if (delimiterIndex !== -1) {
        let delimiterChar = options[delimiterIndex + 1];
        delimiter = delimiterChar === '' ? ',' : delimiterChar;
    }
    let items = varName.split(new RegExp(delimiter === ',' ? ',' : '\\' + delimiter));
    // Remove empty items and trim whitespace
    items = items.filter(item => item.trim() !== '');
    // Apply sorting based on options
    if (options.includes('N')) {
        // Numeric sort
        items.sort((a, b) => parseInt(a, 10) - parseInt(b, 10));
    } else if (options.includes('Random')) {
        // Random sort
        for (let i = items.length - 1; i > 0; i--) {
            const j = Math.floor(Math.random() * (i + 1));
            [items[i], items[j]] = [items[j], items[i]];
        }
    } else {
        // Default alphabetical sort
        items.sort((a, b) => {
            const keyA = options.includes('C') ? a : a.toLowerCase();
            const keyB = options.includes('C') ? b : b.toLowerCase();
            if (keyA < keyB) return -1;
            if (keyA > keyB) return 1;
            return 0;
        });
    }
    // Reverse if 'R' option is present
    if (options.includes('R')) {
        items.reverse();
    }
    // Remove duplicates if 'U' option is present
    if (options.includes('U')) {
        const seen = new Map();
        items = items.filter(item => {
            const key = options.includes('C') ? item : item.toLowerCase();
            if (!seen.has(key)) {
                seen.set(key, item);
                return true;
            }
            return false;
        });
    }
    // Join the sorted items back into a string
    const sortedVar = items.join(delimiter === ',' ? ',' : '\n');
    return sortedVar;
}

      // Function to simulate AutoHotkey's RegExReplace in JavaScript
      function RegExReplace(inputStr, regexPattern, replacement) {
          // Create a regular expression object using the provided pattern
          const regex = new RegExp(regexPattern, 'g'); // 'g' flag for global match
          // Use the replace() method to perform the regex replacement
          const resultStr = inputStr.replace(regex, replacement);
          // Return the modified string
          return resultStr;
      }

// RegExMatch
function RegExMatch(haystack, needle) {
    const regex = new RegExp(needle);
    const match = haystack.match(regex);
    return match ? match.index + 1 : 0; // 1-based index or 0 if no match
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

function countChars(string, theChar) {
    let count = 0;
    for (let char of string) {
        if (char === theChar) {
            count++;
        }
    }
    return count;
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

function HTVM_Append(arr, value) {
    arr.push(value);
}

function HTVM_Pop(arr) {
    arr.pop();
}

function HTVM_Size(arr) {
    return arr.length;
}

function HTVM_Insert(arr, index, value) {
    arr.splice(index, 0, value);
}

function HTVM_Remove(arr, index) {
    if (index >= 0 && index < arr.length) arr.splice(index, 1);
}

function HTVM_IndexOf(arr, value) {
    return arr.indexOf(value);
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
var str15 = "";
var str16 = "";
var str17 = "";
var str18 = "";
var str19 = "";
var str20 = "";
var str21 = "";
var int0 = 0;
var int1 = 0;
var int2 = 0;
var int3 = 0;
var int4 = 0;
var int5 = 0;
var int6 = 0;
var int7 = 0;
let argHTVMinstrMORE = [];
var isNotHTVMfileEXTRA_INT = 0;
var isNotHTVMfile2 = 0;
var isNotHTVMfileEXTRA_LIB_INFO = "";
var isNotHTVMfileEXTRA_FUNCS_INFO = "";
let programmingBlock_InTheTranspiledLang = [];
let programmingBlock_CPP = [];
let programmingBlock_PY = [];
let programmingBlock_JS = [];
let programmingBlock_GO = [];
let programmingBlock_LUA = [];
let programmingBlock_CS = [];
let programmingBlock_JAVA = [];
let programmingBlock_KT = [];
let programmingBlock_RB = [];
let programmingBlock_NIM = [];
let programmingBlock_AHK = [];
let programmingBlock_SWIFT = [];
let programmingBlock_DART = [];
let programmingBlock_TS = [];
let programmingBlock_GROOVY = [];
let programmingBlock_HTVM = [];
let programmingBlock_HTVMsyntax = [];
let fullLangAllOperators = [];
let fullLangAllOperators_HELP = [];
var fixExpertionLineFuncOnly = 0;
var langToConvertTo = "";
var langFileExtension = "";
var commands = "";
var keyWordAlliance = "";
var keyWordCrew = "";
var keyWordMethod = "";
var keyWordDefObj = "";
var keyWordPorp = "";
var keyWordThis = "";
var keyWordInclude = "";
var keyWordCodeInTheTranspiledLangStart = "";
var keyWordCodeInTheTranspiledLangEnd = "";
var keyWordCodeInTheTranspiledLangStartCPP = "";
var keyWordCodeInTheTranspiledLangEndCPP = "";
var keyWordCodeInTheTranspiledLangStartPY = "";
var keyWordCodeInTheTranspiledLangEndPY = "";
var keyWordCodeInTheTranspiledLangStartJS = "";
var keyWordCodeInTheTranspiledLangEndJS = "";
var keyWordCodeInTheTranspiledLangStartGO = "";
var keyWordCodeInTheTranspiledLangEndGO = "";
var keyWordCodeInTheTranspiledLangStartLUA = "";
var keyWordCodeInTheTranspiledLangEndLUA = "";
var keyWordCodeInTheTranspiledLangStartCS = "";
var keyWordCodeInTheTranspiledLangEndCS = "";
var keyWordCodeInTheTranspiledLangStartJAVA = "";
var keyWordCodeInTheTranspiledLangEndJAVA = "";
var keyWordCodeInTheTranspiledLangStartKT = "";
var keyWordCodeInTheTranspiledLangEndKT = "";
var keyWordCodeInTheTranspiledLangStartRB = "";
var keyWordCodeInTheTranspiledLangEndRB = "";
var keyWordCodeInTheTranspiledLangStartNIM = "";
var keyWordCodeInTheTranspiledLangEndNIM = "";
var keyWordCodeInTheTranspiledLangStartAHK = "";
var keyWordCodeInTheTranspiledLangEndAHK = "";
var keyWordCodeInTheTranspiledLangStartSWIFT = "";
var keyWordCodeInTheTranspiledLangEndSWIFT = "";
var keyWordCodeInTheTranspiledLangStartDART = "";
var keyWordCodeInTheTranspiledLangEndDART = "";
var keyWordCodeInTheTranspiledLangStartTS = "";
var keyWordCodeInTheTranspiledLangEndTS = "";
var keyWordCodeInTheTranspiledLangStartGROOVY = "";
var keyWordCodeInTheTranspiledLangEndGROOVY = "";
var keyWordCodeInTheTranspiledLangStartHTVM = "";
var keyWordCodeInTheTranspiledLangEndHTVM = "";
var keyWordCodeInHTVMstart = "";
var keyWordCodeInHTVMend = "";
var keyWordCurlyBraceOpen = "";
var keyWordCurlyBraceClose = "";
var keyWordNull = "";
var keyWordTrue = "";
var keyWordFalse = "";
var keyWordVoid = "";
var keyWordDouble = "";
var keyWordChar = "";
var keyWordUint8 = "";
var keyWordUint16 = "";
var keyWordUint32 = "";
var keyWordUint64 = "";
var keyWordINT = "";
var keyWordSTR = "";
var keyWordBOOL = "";
var keyWordFLOAT = "";
var keyWordINT8 = "";
var keyWordINT16 = "";
var keyWordINT32 = "";
var keyWordINT64 = "";
var keyWordIF = "";
var keyWordElseIf = "";
var keyWordElse = "";
var keyWordWhileLoop = "";
var keyWordLoopInfinite = "";
var keyWordLoop = "";
var keyWordLoopParse = "";
var keyWordContinue = "";
var keyWordBreak = "";
var keyWordFunc = "";
var keyWordAwait = "";
var keyWordAsync = "";
var keyWordThrow = "";
var keyWordErrorMsg = "";
var keyWordTry = "";
var keyWordCatch = "";
var keyWordFinally = "";
var keyWordReturnStatement = "";
var keyWordArrayAppend = "";
var keyWordArrayPop = "";
var keyWordArraySize = "";
var keyWordArrayInsert = "";
var keyWordArrayRemove = "";
var keyWordArrayIndexOf = "";
var keyWordArrayDefinition = "";
var keyWordArrayOfIntegersDefinition = "";
var keyWordArrayOfStringsDefinition = "";
var keyWordArrayOfFloatingPointNumbersDefinition = "";
var keyWordArrayOfBooleansDefinition = "";
var keyWordVar = "";
var keyWordLet = "";
var keyWordConst = "";
var keyWordEnd = "";
var keyWordGlobal = "";
var keyWordComment = "";
var keyWordCommentOpenMultiLine = "";
var keyWordCommentCloseMultiLine = "";
var keyWordEscpaeChar = "";
var keyWordMainLabel = "";
var keyWordConcat = "";
var keyWordAdd = "";
var keyWordSub = "";
var keyWordMul = "";
var keyWordDiv = "";
var keyWordMod = "";
var keyWordExp = "";
var keyWordEqual = "";
var keyWordStrictEqual = "";
var keyWordNotEqual = "";
var keyWordGreater = "";
var keyWordLess = "";
var keyWordGreaterEqual = "";
var keyWordLessEqual = "";
var keyWordAnd = "";
var keyWordOr = "";
var keyWordNot = "";
var keyWordBitAnd = "";
var keyWordBitOr = "";
var keyWordBitXor = "";
var keyWordBitNot = "";
var keyWordShiftLeft = "";
var keyWordShiftRight = "";
var keyWordShiftUnsignedRight = "";
var keyWordAssign = "";
var keyWordAssignAdd = "";
var keyWordAssignConcat = "";
var keyWordAssignSub = "";
var keyWordAssignMul = "";
var keyWordAssignDiv = "";
var keyWordAssignMod = "";
var keyWordAssignShiftLeft = "";
var keyWordAssignShiftRight = "";
var keyWordLogicalAssignShiftRight = "";
var keyWordAssignBitAnd = "";
var keyWordAssignBitOr = "";
var keyWordAssignBitXor = "";
var keyWordTernary1 = "";
var keyWordTernary2 = "";
var keyWordInc = "";
var keyWordDec = "";
var AHKlikeLoopsIndexedAt = "";
var keyWordAIndex = "";
var keyWordALoopField = "";
var useFuncKeyWord = "";
var useCurlyBraces = "";
var useEnd = "";
var useSemicolon = "";
var theSemicolon = "";
var theColon = "";
var useParentheses = "";
var usePrefixTypeForTypeDefinition = "";
var usePostfixTypeForTypeDefinition = "";
var usePythonicColonSyntax = "";
var useCurlyBracesSyntaxForArrayDef = "";
var useInJavaScriptAlwaysUseVar = "";
var useJavaScriptInAfullHTMLfile = "";
var useJavaScriptAmainFuncDef = "";
var useJavaScriptAllFuncsAreAsync = "";
var useJavaScriptAlwaysTripleEqual = "";
var langToConvertTo_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var langFileExtension_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var commands_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAlliance_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCrew_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordMethod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordDefObj_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordPorp_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordThis_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordInclude_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStart_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartCPP_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndCPP_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartPY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndPY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartJS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndJS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartGO_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndGO_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartLUA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndLUA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartCS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndCS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartJAVA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndJAVA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartKT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndKT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartRB_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndRB_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartNIM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndNIM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartAHK_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndAHK_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartSWIFT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndSWIFT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartDART_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndDART_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartTS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndTS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartGROOVY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndGROOVY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangStartHTVM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInTheTranspiledLangEndHTVM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInHTVMstart_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCodeInHTVMend_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCurlyBraceOpen_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCurlyBraceClose_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordNull_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordTrue_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordFalse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordVoid_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordDouble_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordChar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordUint8_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordUint16_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordUint32_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordUint64_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordINT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordSTR_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordBOOL_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordFLOAT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordINT8_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordINT16_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordINT32_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordINT64_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordIF_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordElseIf_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordElse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordWhileLoop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordLoopInfinite_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordLoop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordLoopParse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordContinue_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordBreak_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordFunc_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAwait_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAsync_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordThrow_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordErrorMsg_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordTry_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCatch_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordFinally_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordReturnStatement_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordArrayAppend_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordArrayPop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordArraySize_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordArrayInsert_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordArrayRemove_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordArrayIndexOf_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordArrayDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordArrayOfIntegersDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordArrayOfStringsDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordArrayOfFloatingPointNumbersDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordArrayOfBooleansDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordVar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordLet_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordConst_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordGlobal_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordComment_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCommentOpenMultiLine_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordCommentCloseMultiLine_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordEscpaeChar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordMainLabel_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordConcat_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAdd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordSub_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordMul_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordDiv_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordMod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordExp_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordStrictEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordNotEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordGreater_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordLess_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordGreaterEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordLessEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordNot_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordBitAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordBitOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordBitXor_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordBitNot_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordShiftLeft_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordShiftUnsignedRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAssign_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAssignAdd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAssignConcat_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAssignSub_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAssignMul_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAssignDiv_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAssignMod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAssignShiftLeft_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAssignShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordLogicalAssignShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAssignBitAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAssignBitOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAssignBitXor_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordTernary1_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordTernary2_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordInc_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordDec_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var AHKlikeLoopsIndexedAt_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordAIndex_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordALoopField_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var useCurlyBraces_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var useEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var useSemicolon_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var useParentheses_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var usePrefixTypeForTypeDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var usePostfixTypeForTypeDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var usePythonicColonSyntax_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var useCurlyBracesSyntaxForArrayDef_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var useInJavaScriptAlwaysUseVar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var useJavaScriptInAfullHTMLfile_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var useJavaScriptAmainFuncDef_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var useJavaScriptAllFuncsAreAsync_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var useJavaScriptAlwaysTripleEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordALoopFieldOriginal = "";
var keyWordAIndexOriginal = "";
var out_KeyWordsCommands = "";
var outTrimCode = "";
var htCode = "";
var outVarOperator = "";
var lineDone = 0;
var areWeInAFuncFromInstructions = 0;
var areWeInAFuncFromInstructionsLineNum = 0;
var javaMainFuncSeen = 0;
var csMainFuncSeen = 0;
var howMany_fixAindexInGoUnused = 0;
var luaContinueFix_Num = 0;
var theTryCatchVarForErrors = "jhku-dfsds-ds-d-ffdsf-sdfsfdsedsf";
let allVarsSoWeDontReDecVars = [];
let allVarsSoWeDontReDecVars_FIX_uint8 = [];
let allVarsSoWeDontReDecVars_FIX_uint16 = [];
let allVarsSoWeDontReDecVars_FIX_uint32 = [];
let allVarsSoWeDontReDecVars_FIX_uint64 = [];
let allVarsSoWeDontReDecVars_FIX_int64 = [];
let allVarsSoWeDontReDecVars_FIX_float = [];
var allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function fixCSandJAVAstaticBugForFunc(line) {
    var out = "";
    var haveWeSeenMainFunc = 0;
    items1 = LoopParseFunc(line, "\n", "\r")
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        if (haveWeSeenMainFunc == 0 && InStr(A_LoopField1, "    static ")) {
            out += StrReplace(A_LoopField1, "    static ", "    ") + Chr(10);
        } else {
            out += A_LoopField1 + Chr(10);
        }
        if (InStr(StrLower(A_LoopField1), " main(")) {
            haveWeSeenMainFunc = 1;
        }
    }
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function allVarsSoWeDontReDecVarsFixFunc(line, varName) {
    var out = "";
    if (RegExMatch(line, "^\\d+(\\.\\d+)?$")) {
        for (let A_Index2 = 0; A_Index2 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint8) + 0; A_Index2++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint8[A_Index2]) == Trim(varName)) {
                if (langToConvertTo == "java") {
                    out = "(byte) " + line;
                }
                if (langToConvertTo == "kt") {
                    out = line + "u";
                }
            }
        }
        for (let A_Index3 = 0; A_Index3 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint16) + 0; A_Index3++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint16[A_Index3]) == Trim(varName)) {
                if (langToConvertTo == "java") {
                    out = "(short) " + line;
                }
                if (langToConvertTo == "kt") {
                    out = line + "u";
                }
            }
        }
        for (let A_Index4 = 0; A_Index4 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint32) + 0; A_Index4++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint32[A_Index4]) == Trim(varName)) {
                if (langToConvertTo == "kt") {
                    out = line + "u";
                }
                if (langToConvertTo == "nim") {
                    out = line + "'u32";
                }
            }
        }
        for (let A_Index5 = 0; A_Index5 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint64) + 0; A_Index5++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint64[A_Index5]) == Trim(varName)) {
                if (langToConvertTo == "kt") {
                    out = line + "uL";
                }
                if (langToConvertTo == "cpp") {
                    out = line + "ULL";
                }
                if (langToConvertTo == "java") {
                    out = line + "L";
                }
                if (langToConvertTo == "cs") {
                    out = line + "UL";
                }
                if (langToConvertTo == "nim") {
                    out = line + "'u64";
                }
                if (langToConvertTo == "java") {
                    out = line + "L";
                }
                if (langToConvertTo == "dart") {
                    out = "BigInt.parse(" + Chr(34) + line + Chr(34) + ")";
                }
                if (langToConvertTo == "js" || langToConvertTo == "ts") {
                    out = line + "n";
                }
            }
        }
        for (let A_Index6 = 0; A_Index6 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_int64) + 0; A_Index6++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_int64[A_Index6]) == Trim(varName)) {
                if (langToConvertTo == "kt") {
                    out = line + "L";
                }
                if (langToConvertTo == "cpp") {
                    out = line + "LL";
                }
                if (langToConvertTo == "cs") {
                    out = line + "L";
                }
                if (langToConvertTo == "js" || langToConvertTo == "ts") {
                    out = line + "n";
                }
            }
        }
        for (let A_Index7 = 0; A_Index7 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_float) + 0; A_Index7++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_float[A_Index7]) == Trim(varName)) {
                if (langToConvertTo == "cpp" || langToConvertTo == "cs" || langToConvertTo == "java" || langToConvertTo == "kt") {
                    out = line + "f";
                }
            }
        }
    } else {
        return line;
    }
    if (Trim(out) == "") {
        return line;
    }
    return out;
}
function KeyWordsCommands(theCodeCommands, mode, keyWordsCommands, langToConvertTo) {
    theCodeCommands = StrReplace(theCodeCommands, "%", "");
    if (mode == "check") {
        items8 = LoopParseFunc(keyWordsCommands, "|")
        for (let A_Index8 = 0; A_Index8 < items8.length + 0; A_Index8++) {
            const A_LoopField8 = items8[A_Index8 - 0];
            items9 = LoopParseFunc(A_LoopField8, ",");
            for (let A_Index9 = 0; A_Index9 < items9.length + 0; A_Index9++) {
                const A_LoopField9 = items9[A_Index9 - 0];
                if (A_Index9 == 0) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField9 + ", ")) == StrLower(A_LoopField9 + ", ")) {
                        //MsgBox, true
                        return "true";
                    }
                }
                if (A_Index9 == 0) {
                    if (theCodeCommands == A_LoopField9) {
                        //MsgBox, true
                        return "true";
                    }
                }
            }
        }
        //MsgBox, false
        return "false";
    }
    var AIndex = 0;
    if (mode == "transpile") {
        var keyWordsCommandsNumLine = 1;
        items10 = LoopParseFunc(keyWordsCommands, "|")
        for (let A_Index10 = 0; A_Index10 < items10.length + 0; A_Index10++) {
            const A_LoopField10 = items10[A_Index10 - 0];
            AIndex = A_Index10;
            items11 = LoopParseFunc(A_LoopField10, ",");
            for (let A_Index11 = 0; A_Index11 < items11.length + 0; A_Index11++) {
                const A_LoopField11 = items11[A_Index11 - 0];
                if (A_Index11 == 0) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField11 + ", ")) == StrLower(A_LoopField11 + ", ")) {
                        //MsgBox, true
                        keyWordsCommandsNumLine = AIndex;
                        break;
                    }
                }
                if (A_Index11 == 0) {
                    //MsgBox, %theCodeCommands% = %A_LoopField11%
                    if (theCodeCommands == A_LoopField11) {
                        //MsgBox, true
                        keyWordsCommandsNumLine = AIndex;
                        break;
                    }
                }
            }
        }
        var outConstuctTheOutFromTheCommands = "";
        var outConstuctTheOutFromTheCommandsFucnName = "";
        var outConstuctTheOutFromTheCommandsParams = "";
        var outConstuctTheOutFromTheCommandsOutVar = "";
        var outConstuctTheOutFromTheCommandsInVar = "";
        var theCodeCommandNum = 0;
        var outConstuctTheOutFromTheCommandsLineTranspile = 0;
        var outConstuctTheOutFromTheCommandsLineTranspileText = "";
        var semicolon = "";
        if (langToConvertTo != "py" && langToConvertTo != "nim" && langToConvertTo != "ahk" && langToConvertTo != "go" && langToConvertTo != "lua" && langToConvertTo != "kt" && langToConvertTo != "rb" && langToConvertTo != "swift" && langToConvertTo != "groovy") {
            semicolon = ";";
        }
        let theCodeCommand = [];
        theCodeCommands = Trim(theCodeCommands);
        items12 = LoopParseFunc(theCodeCommands, ",");
        for (let A_Index12 = 0; A_Index12 < items12.length + 0; A_Index12++) {
            const A_LoopField12 = items12[A_Index12 - 0];
            HTVM_Append(theCodeCommand, Trim(A_LoopField12));
            //MsgBox, % A_LoopField12
        }
        items13 = LoopParseFunc(keyWordsCommands, "|")
        for (let A_Index13 = 0; A_Index13 < items13.length + 0; A_Index13++) {
            const A_LoopField13 = items13[A_Index13 - 0];
            if (keyWordsCommandsNumLine == A_Index13) {
                //MsgBox, % A_LoopField13
                items14 = LoopParseFunc(A_LoopField13, ",");
                for (let A_Index14 = 0; A_Index14 < items14.length + 0; A_Index14++) {
                    const A_LoopField14 = items14[A_Index14 - 0];
                    if (A_Index14 == 0) {
                        outConstuctTheOutFromTheCommandsFucnName = A_LoopField14;
                    }
                    else if (A_Index14 == 1) {
                        //MsgBox, % A_LoopField14
                        if (A_LoopField14 == "lineTranspile") {
                            outConstuctTheOutFromTheCommandsLineTranspile = 1;
                        }
                        if (A_LoopField14 == "OUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField14 == "INOUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField14 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField14, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    }
                    else if (A_Index14 == 2) {
                        if (outConstuctTheOutFromTheCommandsLineTranspile == 1) {
                            outConstuctTheOutFromTheCommandsLineTranspileText = A_LoopField14;
                        }
                        if (A_LoopField14 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField14, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    } else {
                        //MsgBox, % theCodeCommand[theCodeCommandNum]
                        if (InStr(A_LoopField14, Chr(39))) {
                            if (Trim(theCodeCommand[theCodeCommandNum]) != "") {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            }
                        } else {
                            if (Trim(theCodeCommand[theCodeCommandNum]) != "") {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    }
                    theCodeCommandNum++;
                }
                break;
            }
        }
        outConstuctTheOutFromTheCommandsParams = StringTrimRight(outConstuctTheOutFromTheCommandsParams, 2);
        if (outConstuctTheOutFromTheCommandsOutVar != "") {
            if (outConstuctTheOutFromTheCommandsParams == "") {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " = " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ")" + semicolon;
            } else {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " = " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ", " + outConstuctTheOutFromTheCommandsParams + ")" + semicolon;
            }
        }
        if (outConstuctTheOutFromTheCommandsOutVar == "") {
            if (outConstuctTheOutFromTheCommandsParams == "") {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ")" + semicolon;
            } else {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ", " + outConstuctTheOutFromTheCommandsParams + ")" + semicolon;
            }
        }
        if (outConstuctTheOutFromTheCommandsLineTranspile == 1) {
            outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsLineTranspileText;
        }
        outConstuctTheOutFromTheCommands = StrReplace(outConstuctTheOutFromTheCommands, "(, ", "( ");
        outConstuctTheOutFromTheCommands = StrReplace(outConstuctTheOutFromTheCommands, "(,", "(");
        return outConstuctTheOutFromTheCommands;
    }
    return "false";
}
function HTVMmatchStrRrplace(line, matchString, replaceString) {
    var lineOut = "";
    if (!InStr(line, matchString)) {
        return line;
    }
    var allDelimiters = " ()[].,;:'!&|=<>+-*/^%~" + Chr(34) + Chr(9) + Chr(11);
    let lineArr = [];
    items15 = LoopParseFunc(line)
    for (let A_Index15 = 0; A_Index15 < items15.length + 0; A_Index15++) {
        const A_LoopField15 = items15[A_Index15 - 0];
        HTVM_Append(lineArr, A_LoopField15);
    }
    var matchStringLEN = StrLen(matchString);
    var replaceStringLEN = StrLen(replaceString);
    let allPosForReplacing = [];
    var sildingLine = "";
    var isStart = 1;
    var i1 = 0;
    var hasFound = 0;
    var hasFound2 = 0;
    var isStartTrue = 0;
    var isEndTrue = 0;
    var char1 = "";
    var char2 = "";
    var char3 = "";
    var char4 = "";
    var isMatch = 0;
    sildingLine = "";
    isStart = 1;
    i1 = 0;
    hasFound = 0;
    hasFound2 = 0;
    isStartTrue = 0;
    isEndTrue = 0;
    for (let A_Index16 = 0; A_Index16 < HTVM_Size(lineArr) + 0; A_Index16++) {
        char1 = "";
        char2 = "";
        char3 = "";
        char4 = "";
        isMatch = 0;
        if (A_Index16 != 0) {
            isStart = 0;
        }
        sildingLine = "";
        for (let A_Index17 = 0; A_Index17 < matchStringLEN + 0; A_Index17++) {
            if (A_Index17 + i1 <= HTVM_Size(lineArr) - 1) {
                sildingLine += lineArr[A_Index17 + i1];
            }
        }
        if (StrLen(sildingLine) < matchStringLEN) {
            break;
        }
        if (sildingLine == matchString) {
            hasFound = 1;
            if (isStart != 1) {
                char1 = lineArr[i1 - 1];
                char2 = lineArr[i1];
            } else {
                isStartTrue = 1;
            }
            if (i1 + matchStringLEN < HTVM_Size(lineArr)) {
                char3 = lineArr[i1 + matchStringLEN - 1];
                char4 = lineArr[i1 + matchStringLEN];
            } else {
                isEndTrue = 1;
            }
            if (InStr(allDelimiters, char1) || InStr(allDelimiters, char2)) {
                isStartTrue = 1;
            }
            if (InStr(allDelimiters, char3) || InStr(allDelimiters, char4)) {
                isEndTrue = 1;
            }
            if (isStartTrue == 1 && isEndTrue == 1) {
                isMatch = 1;
            }
        }
        if (isMatch == 1) {
            if (HTVM_Size(allPosForReplacing) > 0) {
                for (let A_Index18 = 0; A_Index18 < HTVM_Size(allPosForReplacing) + 0; A_Index18++) {
                    if (i1 + 1 != allPosForReplacing[A_Index18]) {
                        HTVM_Append(allPosForReplacing, i1 + 1);
                        break;
                    }
                }
            } else {
                HTVM_Append(allPosForReplacing, i1 + 1);
            }
        }
        i1++;
    }
    var lineTEMP = "";
    lineOut = line;
    if (HTVM_Size(allPosForReplacing) > 0) {
        var l2 = 0;
        var currentPos = 0;
        var onceEnd = 0;
        for (let A_Index19 = 0; A_Index19 < HTVM_Size(allPosForReplacing) + 0; A_Index19++) {
            if (A_Index19 == 0) {
                currentPos = allPosForReplacing[A_Index19];
            } else {
                currentPos = allPosForReplacing[A_Index19] - (matchStringLEN - replaceStringLEN);
            }
            onceEnd = 0;
            items20 = LoopParseFunc(lineOut)
            for (let A_Index20 = 0; A_Index20 < items20.length + 0; A_Index20++) {
                const A_LoopField20 = items20[A_Index20 - 0];
                if (A_Index20 + 2 > currentPos && A_Index20 + 1 < currentPos + matchStringLEN) {
                    onceEnd++;
                    if (onceEnd == 1) {
                        lineTEMP += replaceString;
                    }
                } else {
                    lineTEMP += A_LoopField20;
                }
            }
            lineOut = lineTEMP;
            lineTEMP = "";
            l2++;
        }
    } else {
        return line;
    }
    return lineOut;
}
function SubStrLastChars(text, numOfChars) {
    var LastOut = "";
    var NumOfChars = 0;
    items21 = LoopParseFunc(text)
    for (let A_Index21 = 0; A_Index21 < items21.length + 0; A_Index21++) {
        const A_LoopField21 = items21[A_Index21 - 0];
        NumOfChars++;
    }
    for (let A_Index22 = 0; A_Index22 < numOfChars + 0; A_Index22++) {
        NumOfChars--;
    }
    items23 = LoopParseFunc(text)
    for (let A_Index23 = 0; A_Index23 < items23.length + 0; A_Index23++) {
        const A_LoopField23 = items23[A_Index23 - 0];
        if (A_Index23 >= NumOfChars) {
            LastOut += A_LoopField23;
        }
    }
    return LastOut;
}
function ExtractDigits(inputString) {
    var digits = "";
    items24 = LoopParseFunc(inputString)
    for (let A_Index24 = 0; A_Index24 < items24.length + 0; A_Index24++) {
        const A_LoopField24 = items24[A_Index24 - 0];
        if (RegExMatch(A_LoopField24, "\\d")) {
            digits += A_LoopField24;
        }
    }
    return digits;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Helper function to create spaces
function spaces(n) {
    var s = "";
    if (n != 0) {
        for (let A_Index25 = 0; A_Index25 < n + 0; A_Index25++) {
            s += " ";
        }
    }
    return s;
}
// Define the function to check odd spaces at the beginning
function CheckOddLeadingSpaces(string123) {
    // Initialize a variable to count the spaces
    var spaceCount = 0;
    // Loop through the string one character at a time
    items26 = LoopParseFunc(string123)
    for (let A_Index26 = 0; A_Index26 < items26.length + 0; A_Index26++) {
        const A_LoopField26 = items26[A_Index26 - 0];
        // Check if the current character is a space
        if (A_LoopField26 == Chr(32)) {
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
function LTrim(input) {
    var result = "";
    var foundNonSpace = false;
    items27 = LoopParseFunc(input)
    for (let A_Index27 = 0; A_Index27 < items27.length + 0; A_Index27++) {
        const A_LoopField27 = items27[A_Index27 - 0];
        if (A_LoopField27 != " " || foundNonSpace) {
            result += A_LoopField27;
            foundNonSpace = true;
        }
    }
    return result;
}
function getLastChar(strippedString) {
    var lastChar;
    items28 = LoopParseFunc(strippedString)
    for (let A_Index28 = 0; A_Index28 < items28.length + 0; A_Index28++) {
        const A_LoopField28 = items28[A_Index28 - 0];
        lastChar = A_LoopField28;
    }
    return lastChar;
}
function AddCurlyBraces(pythonCode) {
    pythonCode = StrReplace(pythonCode, Chr(9), "    ");
    var result = "";
    var indentLevel = 0;
    var indent = 0;
    var line = "";
    var stripped = "";
    items29 = LoopParseFunc(pythonCode, "\n", "\r")
    for (let A_Index29 = 0; A_Index29 < items29.length + 0; A_Index29++) {
        const A_LoopField29 = items29[A_Index29 - 0];
        line = A_LoopField29;
        stripped = Trim(line);
        if (stripped == "") {
            result += line + Chr(10);
            continue;
        }
        // Count leading spaces
        indent = StrLen(line) - StrLen(LTrim(line));
        // Close braces for unindents
        for (let A_Index30 = 0; ; A_Index30++) {
            if (indentLevel <= indent) {
                break;
            }
            indentLevel -= 4;
            result += spaces(indentLevel) + "}\n";
        }
        // Add opening brace for new blocks
        if (getLastChar(stripped) == ":" && SubStr(StrLower(Trim(A_LoopField29)), 1, StrLen(StrLower(keyWordComment))) != StrLower(keyWordComment)) {
            result += SubStr(line, 1, -1) + " {\n";
            indentLevel += 4;
        } else {
            result += line + Chr(10);
        }
    }
    // Close any remaining open braces
    for (let A_Index31 = 0; ; A_Index31++) {
        if (indentLevel <= 0) {
            break;
        }
        indentLevel -= 4;
        result += spaces(indentLevel) + "}\n";
    }
    return result;
}
function RepeatSpaces(count) {
    var spaces = "";
    for (let A_Index32 = 0; A_Index32 < count + 0; A_Index32++) {
        spaces += Chr(32);
    }
    return spaces;
}
function indent_nested_curly_braces(input_string, modeCurlyBracesOn) {
    var indent_size = 4;
    var current_indent = 0;
    var result = "";
    var trimmed_line = "";
    var resultOut = "";
    var culyOpenFix = "{";
    var culyCloseFix = "}";
    if (langToConvertTo == langFileExtension_2) {
        culyOpenFix = Trim(keyWordCurlyBraceOpen_2);
        culyCloseFix = Trim(keyWordCurlyBraceClose_2);
    }
    //MsgBox, % input_string
    items33 = LoopParseFunc(input_string, "\n", "\r")
    for (let A_Index33 = 0; A_Index33 < items33.length + 0; A_Index33++) {
        const A_LoopField33 = items33[A_Index33 - 0];
        trimmed_line = Trim(A_LoopField33);
        if (trimmed_line == Chr(123)) {
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + Chr(10);
            current_indent = current_indent + indent_size;
        }
        else if (trimmed_line == Chr(125)) {
            current_indent = current_indent - indent_size;
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + Chr(10);
        } else {
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + Chr(10);
        }
    }
    if (modeCurlyBracesOn == 0) {
        var resultOut = "";
        items34 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index34 = 0; A_Index34 < items34.length + 0; A_Index34++) {
            const A_LoopField34 = items34[A_Index34 - 0];
            if (Trim(A_LoopField34) != "{" && Trim(A_LoopField34) != "}") {
                resultOut += A_LoopField34 + Chr(10);
            }
        }
        result = StringTrimRight(resultOut, 1);
    } else {
        // format curly braces in a K&R style
        let lookIntoFurture = [];
        items35 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index35 = 0; A_Index35 < items35.length + 0; A_Index35++) {
            const A_LoopField35 = items35[A_Index35 - 0];
            HTVM_Append(lookIntoFurture, Trim(A_LoopField35));
        }
        HTVM_Append(lookIntoFurture, " ");
        var resultOut = "";
        var skipNext = 0;
        items36 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index36 = 0; A_Index36 < items36.length + 0; A_Index36++) {
            const A_LoopField36 = items36[A_Index36 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (Trim(lookIntoFurture[A_Index36 + 1]) == "{") {
                resultOut += A_LoopField36 + " " + culyOpenFix + Chr(10);
                skipNext = 2;
            }
            if (skipNext == 0) {
                resultOut += A_LoopField36 + Chr(10);
            }
        }
        result = StringTrimRight(resultOut, 1);
        let lookIntoFurture2 = [];
        items37 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index37 = 0; A_Index37 < items37.length + 0; A_Index37++) {
            const A_LoopField37 = items37[A_Index37 - 0];
            HTVM_Append(lookIntoFurture2, Trim(A_LoopField37));
        }
        HTVM_Append(lookIntoFurture2, " ");
        resultOut = "";
        skipNext = 0;
        var addSpacesAtTheBegginig;
        items38 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index38 = 0; A_Index38 < items38.length + 0; A_Index38++) {
            const A_LoopField38 = items38[A_Index38 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (langToConvertTo != "lua" && langToConvertTo != "rb" && langToConvertTo != langFileExtension_2) {
                if (Trim(A_LoopField38) == "}" && Trim(lookIntoFurture2[A_Index38 + 1]) == "else {") {
                    skipNext = 2;
                    addSpacesAtTheBegginig = "";
                    items39 = LoopParseFunc(A_LoopField38)
                    for (let A_Index39 = 0; A_Index39 < items39.length + 0; A_Index39++) {
                        const A_LoopField39 = items39[A_Index39 - 0];
                        if (A_LoopField39 == " ") {
                            if (A_LoopField39 != " ") {
                                break;
                            }
                            addSpacesAtTheBegginig += StrReplace(A_LoopField39, "}", culyCloseFix);
                        }
                    }
                    resultOut += addSpacesAtTheBegginig + culyCloseFix + " else " + culyOpenFix + Chr(10);
                }
            }
            if (skipNext == 0) {
                resultOut += A_LoopField38 + Chr(10);
            }
        }
        result = StringTrimRight(resultOut, 1);
    }
    resultOut = "";
    var ALoopField;
    items40 = LoopParseFunc(result, "\n", "\r")
    for (let A_Index40 = 0; A_Index40 < items40.length + 0; A_Index40++) {
        const A_LoopField40 = items40[A_Index40 - 0];
        if (CheckOddLeadingSpaces(A_LoopField40) == "1") {
            ALoopField = StringTrimLeft(A_LoopField40, 1);
            resultOut += ALoopField + Chr(10);
        } else {
            resultOut += A_LoopField40 + Chr(10);
        }
    }
    result = StringTrimRight(resultOut, 1);
    var fixResultFIX = "";
    if (langToConvertTo == langFileExtension_2 && modeCurlyBracesOn == 1) {
        items41 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index41 = 0; A_Index41 < items41.length + 0; A_Index41++) {
            const A_LoopField41 = items41[A_Index41 - 0];
            if (Trim(A_LoopField41) == "}") {
                fixResultFIX += StrReplace(A_LoopField41, "}", culyCloseFix) + Chr(10);
            } else {
                fixResultFIX += A_LoopField41 + Chr(10);
            }
        }
        result = StringTrimRight(fixResultFIX, 1);
    }
    // Return the result
    return result;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// path.path.path:propName1[str],propName2[bool],propName3[str array]|path.path.path:propName1[str],propName2[bool],propName3[str array]
var OSPstrArrayStrALLobjInOSP = "";
var HoldOSPdethodNamePath = "";
function findTypeOfOSPprop(fullARRAYstr, FromPath) {
    var outType = "";
    // if the fullARRAYstr is in this format
    // path.path.path:propName1[str],propName2[bool],propName3[str array]|path.path.path:propName1[str],propName2[bool],propName3[str array]
    var outFormat = "";
    var outFormatHELP1 = "";
    var outFormatHELP2 = "";
    items42 = LoopParseFunc(fullARRAYstr, "|")
    for (let A_Index42 = 0; A_Index42 < items42.length + 0; A_Index42++) {
        const A_LoopField42 = items42[A_Index42 - 0];
        if (Trim(A_LoopField42) != "") {
            outFormatHELP1 = StrSplit(A_LoopField42, ":", 1);
            outFormatHELP2 = StrSplit(A_LoopField42, ":", 2);
            items43 = LoopParseFunc(outFormatHELP2, ",");
            for (let A_Index43 = 0; A_Index43 < items43.length + 0; A_Index43++) {
                const A_LoopField43 = items43[A_Index43 - 0];
                outFormat += outFormatHELP1 + "." + A_LoopField43 + "|";
            }
        }
    }
    outFormat = StringTrimRight(outFormat, 1);
    items44 = LoopParseFunc(outFormat, "|")
    for (let A_Index44 = 0; A_Index44 < items44.length + 0; A_Index44++) {
        const A_LoopField44 = items44[A_Index44 - 0];
        if (Trim(A_LoopField44) != "") {
            if (StrSplit(Trim(A_LoopField44), "[", 1) == Trim(FromPath)) {
                outType = StrSplit(Trim(A_LoopField44), "[", 2);
                outType = StringTrimRight(outType, 1);
                break;
            }
        }
    }
    if (outType == "vector<int>") {
        outType = "std::vector<int>&";
    }
    else if (outType == "vector<string>") {
        outType = "std::vector<std::string>&";
    }
    else if (outType == "vector<string>") {
        outType = "std::vector<std::string>&";
    }
    else if (outType == "vector<float>") {
        outType = "std::vector<float>&";
    }
    else if (outType == "vector<bool>") {
        outType = "std::vector<bool>&";
    }
    else if (outType == Trim(keyWordINT)) {
        outType = "int";
    }
    else if (outType == Trim(keyWordSTR)) {
        outType = "std::string";
    }
    else if (outType == Trim(keyWordFLOAT)) {
        outType = "float";
    }
    else if (outType == Trim(keyWordBOOL)) {
        outType = "bool";
    }
    else if (outType == Trim(keyWordINT8)) {
        outType = "int8_t";
    }
    else if (outType == Trim(keyWordINT16)) {
        outType = "int16_t";
    }
    else if (outType == Trim(keyWordINT32)) {
        outType = "int32_t";
    }
    else if (outType == Trim(keyWordINT64)) {
        outType = "int64_t";
    }
    return outType;
}
function REMOVELastSTRfromDOT(THESTR) {
    var THESTRout = "";
    if (Trim(THESTR) == "") {
        return "";
    }
    var count12345 = 0;
    items45 = LoopParseFunc(THESTR, ".")
    for (let A_Index45 = 0; A_Index45 < items45.length + 0; A_Index45++) {
        const A_LoopField45 = items45[A_Index45 - 0];
        count12345++;
    }
    items46 = LoopParseFunc(THESTR, ".")
    for (let A_Index46 = 0; A_Index46 < items46.length + 0; A_Index46++) {
        const A_LoopField46 = items46[A_Index46 - 0];
        if (count12345 == A_Index46) {
            break;
        } else {
            THESTRout += Trim(A_LoopField46) + ".";
        }
    }
    THESTRout = StringTrimRight(THESTRout, 1);
    return THESTRout;
}
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
function replaceTheOSPpathsPY_JS(theSTR123, ALoopFieldIN) {
    if (Trim(theSTR123) == "") {
        return "";
    }
    if (Trim(ALoopFieldIN) == "") {
        return "";
    }
    var type = "";
    var theSTR123out = "";
    var ALoopField = "";
    var ALoopField1 = "";
    var ALoopField11 = "";
    if (InStr(ALoopFieldIN, "[")) {
        // ALoopFieldIN
        // animalsKingdom.animals.Dog.typeOf2[2]
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField11 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(ALoopField1) + "[" + ALoopField11;
        // REMOVELastSTRfromDOT(param1)
        theSTR123 = StrReplace(theSTR123, Trim(ALoopField), "OSPHTVMOSP_" + StrReplace(ALoopField1, ".", "_"));
    } else {
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(StrSplit(Trim(ALoopFieldIN), "]", 1));
        ALoopField1 = "[" + Trim(StrSplit(ALoopField1, "[", 2)) + "]";
        theSTR123 = StrReplace(theSTR123, Trim(ALoopFieldIN), "OSPHTVMOSP_" + StrReplace(ALoopFieldIN, ".", "_"));
    }
    //this__OSP__this
    theSTR123 = RegExReplace(theSTR123, "\\bthis\\b", "this__OSP__this[0]");
    theSTR123 = StrReplace(theSTR123, "OSPHTVMOSP_OSPHTVMOSP_", "OSPHTVMOSP_");
    return theSTR123;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function replaceTheOSPpathsLEFT(theSTR123, ALoopFieldIN) {
    if (Trim(theSTR123) == "") {
        return "";
    }
    if (Trim(ALoopFieldIN) == "") {
        return "";
    }
    var type = "";
    var theSTR123out = "";
    var ALoopField = "";
    var ALoopField1 = "";
    var ALoopField11 = "";
    if (InStr(ALoopFieldIN, "[")) {
        // ALoopFieldIN
        // animalsKingdom.animals.Dog.typeOf2[2]
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField11 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(ALoopField1) + "[" + ALoopField11;
        // REMOVELastSTRfromDOT(param1)
        theSTR123 = StrReplace(theSTR123, Trim(ALoopField), "OSPHTVMOSP_" + StrReplace(ALoopField1, ".", "_"));
    } else {
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(StrSplit(Trim(ALoopFieldIN), "]", 1));
        ALoopField1 = "[" + Trim(StrSplit(ALoopField1, "[", 2)) + "]";
        theSTR123 = StrReplace(theSTR123, Trim(ALoopFieldIN), "OSPHTVMOSP_" + StrReplace(ALoopFieldIN, ".", "_"));
    }
    //this__OSP__this
    theSTR123 = RegExReplace(theSTR123, "\\bthis\\b", "std::any_cast<std::string>((*this__OSP__this)[0])");
    theSTR123 = StrReplace(theSTR123, "OSPHTVMOSP_OSPHTVMOSP_", "OSPHTVMOSP_");
    return theSTR123;
}
function replaceTheOSPpathsRIGHT(theSTR123, ALoopFieldIN) {
    if (Trim(theSTR123) == "") {
        return "";
    }
    if (Trim(ALoopFieldIN) == "") {
        return "";
    }
    var type = "";
    var theSTR123out = "";
    var ALoopField = "";
    var ALoopField1 = "";
    var ALoopField11 = "";
    if (InStr(ALoopFieldIN, "[")) {
        // ALoopFieldIN
        // animalsKingdom.animals.Dog.typeOf2[2]
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField11 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(ALoopField1) + "[" + ALoopField11;
        // REMOVELastSTRfromDOT(param1)
        type = findTypeOfOSPprop(OSPstrArrayStrALLobjInOSP, ALoopField);
        //MsgBox, % type
        theSTR123 = StrReplace(theSTR123, Trim(ALoopField), "std::any_cast<" + type + ">(OSPHTVMOSP_" + StrReplace(ALoopField1, ".", "_") + ")");
    } else {
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(StrSplit(Trim(ALoopFieldIN), "]", 1));
        ALoopField1 = "[" + Trim(StrSplit(ALoopField1, "[", 2)) + "]";
        theSTR123 = StrReplace(theSTR123, Trim(ALoopFieldIN), "OSPHTVMOSP_" + StrReplace(ALoopFieldIN, ".", "_"));
    }
    //this__OSP__this
    theSTR123 = RegExReplace(theSTR123, "\\bthis\\b", "std::any_cast<std::string>((*this__OSP__this)[0])");
    theSTR123 = StrReplace(theSTR123, "OSPHTVMOSP_OSPHTVMOSP_", "OSPHTVMOSP_");
    return theSTR123;
}
function CheckStringPosition(text, target, reference) {
    var posReference = SubStr(text, 1, StrLen(reference));
    var posTarget = SubStr(text, 1, StrLen(target));
    if (posReference != "" && posTarget != "") {
        posTarget = RegExMatch(text, target);
        posReference = RegExMatch(text, reference);
        if (posTarget < posReference) {
            return "left";
        }
        else if (posTarget > posReference) {
            return "not left";
        } else {
            return "uuh";
        }
    } else {
        return "One or both strings not found.";
    }
    return "huh";
}
function getIndexOfTheStrArrayStrOST(ALoopField, theSringOSPlineARRAYstrstrSTR) {
    items47 = LoopParseFunc(theSringOSPlineARRAYstrstrSTR, "|")
    for (let A_Index47 = 0; A_Index47 < items47.length + 0; A_Index47++) {
        const A_LoopField47 = items47[A_Index47 - 0];
        if (Trim(StrSplit(A_LoopField47, ":", 1)) == Trim(ALoopField)) {
            return STR(A_Index47);
        }
    }
    return "0";
}
function parserOSPgloabl(theSringOSPline, str123) {
    var str_1 = "";
    var str_2 = "";
    var str_3 = "";
    var str_4 = "";
    var str_5 = "";
    var str_6 = "";
    var HELPHoldOSPdethodNamePath = "";
    items48 = LoopParseFunc(theSringOSPline, "|")
    for (let A_Index48 = 0; A_Index48 < items48.length + 0; A_Index48++) {
        const A_LoopField48 = items48[A_Index48 - 0];
        str_1 += Trim(StrSplit(A_LoopField48, ":", 1)) + Chr(10);
        str_5 = Trim(StrSplit(A_LoopField48, ":", 1));
        str_6 = Trim(StrSplit(A_LoopField48, ":", 2));
        items49 = LoopParseFunc(str_6, ",");
        for (let A_Index49 = 0; A_Index49 < items49.length + 0; A_Index49++) {
            const A_LoopField49 = items49[A_Index49 - 0];
            str_1 += str_5 + "." + Trim(StrSplit(A_LoopField49, "[", 1)) + "[" + STR(A_Index49) + "]\n";
        }
    }
    str_1 += StrReplace(HELPHoldOSPdethodNamePath, "|", Chr(10));
    var shortestLine = "";
    var currentLine = "";
    var currentLength = 0;
    var minLength = 0;
    var tempStr = "";
    // Sorting by repeatedly finding and appending the shortest line
    for (let A_Index50 = 0; ; A_Index50++) {
        shortestLine = "";
        minLength = 999999;
        items51 = LoopParseFunc(str_1, "\n", "\r")
        for (let A_Index51 = 0; A_Index51 < items51.length + 0; A_Index51++) {
            const A_LoopField51 = items51[A_Index51 - 0];
            currentLine = A_LoopField51;
            currentLength = StrLen(currentLine);
            if (currentLength < minLength) {
                minLength = currentLength;
                shortestLine = currentLine;
            }
        }
        if (shortestLine == "") {
            break;
        }
        str_2 += shortestLine + Chr(10);
        tempStr = "";
        items52 = LoopParseFunc(str_1, "\n", "\r")
        for (let A_Index52 = 0; A_Index52 < items52.length + 0; A_Index52++) {
            const A_LoopField52 = items52[A_Index52 - 0];
            if (A_LoopField52 != shortestLine) {
                tempStr += A_LoopField52 + Chr(10);
            }
        }
        tempStr = StringTrimRight(tempStr, 1);
        str_1 = tempStr;
    }
    // Trim the final trailing newline from str_2
    str_2 = StringTrimRight(str_2, 1);
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    // Initialize an empty result for the reversed lines
    var reversedStr = "";
    // Count the number of lines
    var lineCount = 0;
    var index = 0;
    var lineNum = 0;
    items53 = LoopParseFunc(str_2, "\n", "\r")
    for (let A_Index53 = 0; A_Index53 < items53.length + 0; A_Index53++) {
        const A_LoopField53 = items53[A_Index53 - 0];
        lineCount++;
    }
    // Reverse the order by re-parsing and appending lines in reverse order
    for (let A_Index54 = 0; A_Index54 < lineCount + 0; A_Index54++) {
        index = lineCount - A_Index54 + 1;
        currentLine = "";
        lineNum = 0;
        items55 = LoopParseFunc(str_2, "\n", "\r")
        for (let A_Index55 = 0; A_Index55 < items55.length + 0; A_Index55++) {
            const A_LoopField55 = items55[A_Index55 - 0];
            lineNum++;
            if (lineNum == index) {
                currentLine = A_LoopField55;
                break;
            }
        }
        reversedStr += currentLine + Chr(10);
    }
    // Trim the final trailing newline
    str_2 = StringTrimRight(reversedStr, 1);
    // Display the sorted result
    //MsgBox, % str_2
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //CheckStringPosition(text, target, reference)
    var ALoopField = "";
    var ALoopField1 = "";
    items56 = LoopParseFunc(str_2, "\n", "\r")
    for (let A_Index56 = 0; A_Index56 < items56.length + 0; A_Index56++) {
        const A_LoopField56 = items56[A_Index56 - 0];
        if (SubStr(A_LoopField56, 1, StrLen(keyWordFunc)) != keyWordFunc) {
            if (langToConvertTo == "cpp") {
                if (Trim(A_LoopField56) != "") {
                    if (InStr(str123, " += ")) {
                        str6 = " += ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField56));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField56));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    }
                    else if (InStr(str123, " = ")) {
                        str6 = " = ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField56));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField56));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    }
                    else if (InStr(str123, " -= ")) {
                        str6 = " -= ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField56));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField56));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    }
                    else if (InStr(str123, " *= ")) {
                        str6 = " *= ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField56));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField56));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    }
                    else if (InStr(str123, " /= ")) {
                        str6 = " /= ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField56));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField56));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    } else {
                        str123 = replaceTheOSPpathsRIGHT(str123, A_LoopField56);
                    }
                    //;;;;
                }
            } else {
                if (Trim(A_LoopField56) != "") {
                    str123 = replaceTheOSPpathsPY_JS(str123, A_LoopField56);
                }
            }
        }
    }
    return str123;
}
function isLineAconstruct(line) {
    line = StrLower(Trim(line));
    if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf)) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordElse) || StrLower(Trim(line)) == StrLower(keyWordElse + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordElse))) == keyWordCurlyBraceClose + " " + StrLower(keyWordElse)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordElse) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordElse) + " " + keyWordCurlyBraceOpen) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordLoopInfinite) || StrLower(Trim(line)) == StrLower(keyWordLoopInfinite + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordLoopInfinite))) == keyWordCurlyBraceClose + " " + StrLower(keyWordLoopInfinite)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordLoopInfinite) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordLoopInfinite) + " " + keyWordCurlyBraceOpen) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordTry) || StrLower(Trim(line)) == StrLower(keyWordTry + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordTry))) == keyWordCurlyBraceClose + " " + StrLower(keyWordTry)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordTry) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordTry) + " " + keyWordCurlyBraceOpen) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordCrew))) == StrLower(keyWordCrew)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordDefObj))) == StrLower(keyWordDefObj)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordMethod))) == StrLower(keyWordMethod)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordFinally) || StrLower(Trim(line)) == StrLower(keyWordFinally + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordFinally))) == keyWordCurlyBraceClose + " " + StrLower(keyWordFinally)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordFinally) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordFinally) + " " + keyWordCurlyBraceOpen) {
        return true;
    }
    else if (SubStr(StrLower(Trim(StrLower(line))), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordAsync))) == StrLower(keyWordAsync)) {
        return true;
    }
    return false;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function fixDoubleQuotes(line, isLast) {
    var out = "";
    if (isLast == 0) {
        out = StrReplace(line, Chr(92) + Chr(92) + Chr(34), Chr(92) + Chr(34));
    } else {
        line = StringTrimRight(line, 1);
        out = StrReplace(line, Chr(92) + Chr(92) + Chr(34), Chr(92) + Chr(34)) + Chr(34);
    }
    return out;
}
function fixArray1234(line) {
    var out = "";
    var started = 0;
    items57 = LoopParseFunc(line)
    for (let A_Index57 = 0; A_Index57 < items57.length + 0; A_Index57++) {
        const A_LoopField57 = items57[A_Index57 - 0];
        if (started == 1) {
            if (StrLen(line) == A_Index57 + 1) {
                return out;
            }
            out += A_LoopField57;
        }
        if (A_LoopField57 == "(") {
            started = 1;
        }
    }
    return out;
}
function fixArray123(line, arrayMethodStr, mode) {
    // mode 1 = Append
    // mode 2 = Pop
    // mode 3 = Size
    // mode 4 = Insert
    // mode 5 = Remove
    // mode 6 = IndexOf
    // HTVM_Append
    // HTVM_Pop
    // HTVM_Size
    // HTVM_Insert
    // HTVM_Remove
    // HTVM_IndexOf
    if (langToConvertTo != "swift" && langToConvertTo != "go") {
        if (mode == 1) {
            return "HTVM_Append(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 2) {
            return "HTVM_Pop(" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 3) {
            return "HTVM_Size(" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 4) {
            return "HTVM_Insert(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 5) {
            return "HTVM_Remove(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 6) {
            return "HTVM_IndexOf(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
    } else {
        if (mode == 1) {
            return "HTVM_Append(&" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 2) {
            return "HTVM_Pop(&" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 3) {
            return "HTVM_Size(" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 4) {
            return "HTVM_Insert(&" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 5) {
            return "HTVM_Remove(&" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 6) {
            return "HTVM_IndexOf(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
    }
    return line;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function arrayParserTranspiler1(line, arrayMethodStr, mode) {
    if (InStr(line, arrayMethodStr) == false) {
        return line;
    }
    var out = "";
    var allDelimiters = " ()[],;:'!&|=<>+-*/^%~" + Chr(34) + Chr(9) + Chr(11);
    let arrAll = [];
    items58 = LoopParseFunc(line)
    for (let A_Index58 = 0; A_Index58 < items58.length + 0; A_Index58++) {
        const A_LoopField58 = items58[A_Index58 - 0];
        HTVM_Append(arrAll, A_LoopField58);
    }
    var i1 = 0;
    var tempHold = "";
    var holdPos = 0;
    let holdPositions = [];
    for (let A_Index59 = 0; A_Index59 < HTVM_Size(arrAll) + 0; A_Index59++) {
        tempHold = "";
        if (HTVM_Size(arrAll) - StrLen(arrayMethodStr) + 1 == i1) {
            break;
        }
        for (let A_Index60 = 0; A_Index60 < StrLen(arrayMethodStr) + 0; A_Index60++) {
            tempHold += arrAll[A_Index60 + i1];
        }
        i1++;
        //print(tempHold)
        if (tempHold == arrayMethodStr) {
            holdPos = i1;
            //print(holdPos)
            HTVM_Append(holdPositions, holdPos);
        }
    }
    //print("===========================================")
    var holdPositionsTEMP = 0;
    for (let A_Index61 = 0; A_Index61 < HTVM_Size(holdPositions) + 0; A_Index61++) {
        holdPositionsTEMP = holdPositions[A_Index61];
        i1 = HTVM_Size(arrAll);
        tempHold = "";
        for (let A_Index62 = 0; A_Index62 < HTVM_Size(arrAll) + 0; A_Index62++) {
            if (holdPositionsTEMP >= i1 + 1) {
                if (InStr(allDelimiters, arrAll[i1]) == false) {
                    tempHold += arrAll[i1 - 1];
                } else {
                    break;
                }
            }
            i1--;
        }
        //print(StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", ""))))
        holdPositions[A_Index61] = holdPositions[A_Index61] - StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", "")));
    }
    //;;;;;;;;;;;;;;;;;;
    var foundFirstParenthesis = 0;
    var ParenthesisStackOPEN = 0;
    var ParenthesisStackCLOSE = 0;
    let holdPositionsEnd = [];
    holdPositionsTEMP = 0;
    for (let A_Index63 = 0; A_Index63 < HTVM_Size(holdPositions) + 0; A_Index63++) {
        holdPositionsTEMP = holdPositions[A_Index63];
        i1 = 0;
        tempHold = "";
        foundFirstParenthesis = 0;
        ParenthesisStackOPEN = 0;
        ParenthesisStackCLOSE = 0;
        for (let A_Index64 = 0; A_Index64 < HTVM_Size(arrAll) + 0; A_Index64++) {
            if (holdPositionsTEMP < i1 + 1) {
                if (arrAll[i1] == "(") {
                    foundFirstParenthesis = 1;
                }
                if (arrAll[i1] == "(" && foundFirstParenthesis == 1) {
                    ParenthesisStackOPEN++;
                }
                if (arrAll[i1] == ")" && foundFirstParenthesis == 1) {
                    ParenthesisStackCLOSE++;
                }
                tempHold += arrAll[i1 - 1];
                if (ParenthesisStackOPEN == ParenthesisStackCLOSE && foundFirstParenthesis == 1) {
                    tempHold += arrAll[i1];
                    HTVM_Append(holdPositionsEnd, i1 + 1);
                    break;
                }
            }
            i1++;
        }
        //print(tempHold)
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var startPosReplace = 0;
    var endPosReplace = 0;
    var beenInside = 0;
    var holdDebug = "";
    var holdDebugLen = 0;
    var canOut = 1;
    for (let A_Index65 = 0; A_Index65 < HTVM_Size(holdPositions) + 0; A_Index65++) {
        startPosReplace = holdPositions[HTVM_Size(holdPositions) - A_Index65 - 1];
        endPosReplace = holdPositionsEnd[HTVM_Size(holdPositions) - A_Index65 - 1];
        holdDebug = "";
        beenInside = 0;
        holdDebugLen = 0;
        canOut = 1;
        items66 = LoopParseFunc(line)
        for (let A_Index66 = 0; A_Index66 < items66.length + 0; A_Index66++) {
            const A_LoopField66 = items66[A_Index66 - 0];
            if (A_Index66 + 1 >= startPosReplace && A_Index66 + 1 <= endPosReplace) {
                holdDebug += A_LoopField66;
            }
        }
        holdDebugLen = StrLen(holdDebug);
        items67 = LoopParseFunc(line)
        for (let A_Index67 = 0; A_Index67 < items67.length + 0; A_Index67++) {
            const A_LoopField67 = items67[A_Index67 - 0];
            if (A_Index67 + 1 >= startPosReplace && A_Index67 + 1 <= endPosReplace) {
                beenInside++;
            }
            if (beenInside == 1) {
                out += fixArray123(holdDebug, arrayMethodStr, mode);
                canOut = 0;
            } else {
                if (canOut == 0) {
                    holdDebugLen--;
                    if (holdDebugLen == 0) {
                        canOut = 1;
                    }
                }
                if (canOut == 1) {
                    out += A_LoopField67;
                }
            }
        }
        //print("|" . holdDebug . "|")
        line = out;
        out = "";
    }
    return line;
}
function arrayParserTranspiler(line) {
    // mode 1 = Append
    // mode 2 = Pop
    // mode 3 = Size
    // mode 4 = Insert
    // mode 5 = Remove
    // mode 6 = IndexOf
    if (langToConvertTo == langFileExtension_2) {
        line = HTVMmatchStrRrplace(line, keyWordArrayAppend + "(", keyWordArrayAppend_2 + "(");
        line = HTVMmatchStrRrplace(line, keyWordArrayPop + "(", keyWordArrayPop_2 + "(");
        line = HTVMmatchStrRrplace(line, keyWordArraySize + "(", keyWordArraySize_2 + "(");
        line = HTVMmatchStrRrplace(line, keyWordArrayInsert + "(", keyWordArrayInsert_2 + "(");
        line = HTVMmatchStrRrplace(line, keyWordArrayRemove + "(", keyWordArrayRemove_2 + "(");
        line = HTVMmatchStrRrplace(line, keyWordArrayIndexOf + "(", keyWordArrayIndexOf_2 + "(");
    } else {
        line = arrayParserTranspiler1(line, keyWordArrayAppend + "(", 1);
        line = arrayParserTranspiler1(line, keyWordArrayPop + "(", 2);
        line = arrayParserTranspiler1(line, keyWordArraySize + "(", 3);
        line = arrayParserTranspiler1(line, keyWordArrayInsert + "(", 4);
        line = arrayParserTranspiler1(line, keyWordArrayRemove + "(", 5);
        line = arrayParserTranspiler1(line, keyWordArrayIndexOf + "(", 6);
    }
    return line;
}
function getFuncTypeConvert(type) {
    var theType = "";
    type = Trim(type);
    if (allVarsSoWeDontReDecVars_FIX_TOGGLE == 1) {
        if (type == keyWordUint8) {
            HTVM_Append(allVarsSoWeDontReDecVars_FIX_uint8, str2);
        }
        if (type == keyWordUint16) {
            HTVM_Append(allVarsSoWeDontReDecVars_FIX_uint16, str2);
        }
        if (type == keyWordUint32) {
            HTVM_Append(allVarsSoWeDontReDecVars_FIX_uint32, str2);
        }
        if (type == keyWordUint64) {
            HTVM_Append(allVarsSoWeDontReDecVars_FIX_uint64, str2);
        }
        if (type == keyWordFLOAT) {
            HTVM_Append(allVarsSoWeDontReDecVars_FIX_float, str2);
        }
        if (type == keyWordINT64) {
            HTVM_Append(allVarsSoWeDontReDecVars_FIX_int64, str2);
        }
        if (langToConvertTo == "java") {
            if (type == keyWordINT8) {
                HTVM_Append(allVarsSoWeDontReDecVars_FIX_uint8, str2);
            }
            if (type == keyWordINT16) {
                HTVM_Append(allVarsSoWeDontReDecVars_FIX_uint16, str2);
            }
        }
    }
    if (langToConvertTo == "cpp") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "double";
        }
        if (type == keyWordChar) {
            theType = "char";
        }
        if (type == keyWordUint8) {
            theType = "uint8_t";
        }
        if (type == keyWordUint16) {
            theType = "uint16_t";
        }
        if (type == keyWordUint32) {
            theType = "uint32_t";
        }
        if (type == keyWordUint64) {
            theType = "uint64_t";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "std::string";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "float";
        }
        if (type == keyWordINT8) {
            theType = "int8_t";
        }
        if (type == keyWordINT16) {
            theType = "int16_t";
        }
        if (type == keyWordINT32) {
            theType = "int32_t";
        }
        if (type == keyWordINT64) {
            theType = "int64_t";
        }
        if (type == keyWordArrayDefinition) {
            theType = "std::vector<std::string>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "std::vector<int>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "std::vector<std::string>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "std::vector<float>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "std::vector<bool>";
        }
    }
    if (langToConvertTo == "py") {
        theType = "";
    }
    if (langToConvertTo == "js") {
        theType = "";
    }
    if (langToConvertTo == "go") {
        if (type == keyWordVoid) {
            theType = "";
        }
        if (type == keyWordDouble) {
            theType = "float64";
        }
        if (type == keyWordChar) {
            theType = "byte";
        }
        if (type == keyWordUint8) {
            theType = "uint8";
        }
        if (type == keyWordUint16) {
            theType = "uint16";
        }
        if (type == keyWordUint32) {
            theType = "uint32";
        }
        if (type == keyWordUint64) {
            theType = "uint64";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "string";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "float32";
        }
        if (type == keyWordINT8) {
            theType = "int8";
        }
        if (type == keyWordINT16) {
            theType = "int16";
        }
        if (type == keyWordINT32) {
            theType = "int32";
        }
        if (type == keyWordINT64) {
            theType = "int64";
        }
        if (type == keyWordArrayDefinition) {
            theType = "[]string";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "[]int";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "[]string";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "[]float32";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "[]bool";
        }
    }
    if (langToConvertTo == "lua") {
        theType = "";
    }
    if (langToConvertTo == "cs") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "double";
        }
        if (type == keyWordChar) {
            theType = "char";
        }
        if (type == keyWordUint8) {
            theType = "byte";
        }
        if (type == keyWordUint16) {
            theType = "ushort";
        }
        if (type == keyWordUint32) {
            theType = "uint";
        }
        if (type == keyWordUint64) {
            theType = "ulong";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "string";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "float";
        }
        if (type == keyWordINT8) {
            theType = "sbyte";
        }
        if (type == keyWordINT16) {
            theType = "short";
        }
        if (type == keyWordINT32) {
            theType = "int";
        }
        if (type == keyWordINT64) {
            theType = "long";
        }
        if (type == keyWordArrayDefinition) {
            theType = "List<string>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "List<int>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "List<string>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "List<double>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "List<bool>";
        }
    }
    if (langToConvertTo == "java") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "double";
        }
        if (type == keyWordChar) {
            theType = "char";
        }
        if (type == keyWordUint8) {
            theType = "byte ";
        }
        if (type == keyWordUint16) {
            theType = "short";
        }
        if (type == keyWordUint32) {
            theType = "int";
        }
        if (type == keyWordUint64) {
            theType = "long";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "String";
        }
        if (type == keyWordBOOL) {
            theType = "boolean";
        }
        if (type == keyWordFLOAT) {
            theType = "float";
        }
        if (type == keyWordINT8) {
            theType = "byte";
        }
        if (type == keyWordINT16) {
            theType = "short";
        }
        if (type == keyWordINT32) {
            theType = "int";
        }
        if (type == keyWordINT64) {
            theType = "long";
        }
        if (type == keyWordArrayDefinition) {
            theType = "ArrayList<String>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "ArrayList<Integer>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "ArrayList<String>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "ArrayList<Double>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "ArrayList<Boolean>";
        }
    }
    if (langToConvertTo == "kt") {
        if (type == keyWordVoid) {
            theType = "";
        }
        if (type == keyWordDouble) {
            theType = "Double";
        }
        if (type == keyWordChar) {
            theType = "Char";
        }
        if (type == keyWordUint8) {
            theType = "UByte";
        }
        if (type == keyWordUint16) {
            theType = "UShort";
        }
        if (type == keyWordUint32) {
            theType = "UInt";
        }
        if (type == keyWordUint64) {
            theType = "ULong";
        }
        if (type == keyWordINT) {
            theType = "Int";
        }
        if (type == keyWordSTR) {
            theType = "String";
        }
        if (type == keyWordBOOL) {
            theType = "Boolean";
        }
        if (type == keyWordFLOAT) {
            theType = "Float";
        }
        if (type == keyWordINT8) {
            theType = "Byte";
        }
        if (type == keyWordINT16) {
            theType = "Short";
        }
        if (type == keyWordINT32) {
            theType = "Int";
        }
        if (type == keyWordINT64) {
            theType = "Long";
        }
        if (type == keyWordArrayDefinition) {
            theType = "ArrayList<String>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "ArrayList<Int>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "ArrayList<String>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "ArrayList<Float>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "ArrayList<Boolean>";
        }
    }
    if (langToConvertTo == "rb") {
        theType = "";
    }
    if (langToConvertTo == "nim") {
        if (type == keyWordVoid) {
            theType = "";
        }
        if (type == keyWordDouble) {
            theType = "float";
        }
        if (type == keyWordChar) {
            theType = "char";
        }
        if (type == keyWordUint8) {
            theType = "uint8";
        }
        if (type == keyWordUint16) {
            theType = "uint16";
        }
        if (type == keyWordUint32) {
            theType = "uint32";
        }
        if (type == keyWordUint64) {
            theType = "uint64";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "string";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "float";
        }
        if (type == keyWordINT8) {
            theType = "int8";
        }
        if (type == keyWordINT16) {
            theType = "int16";
        }
        if (type == keyWordINT32) {
            theType = "int32";
        }
        if (type == keyWordINT64) {
            theType = "int64";
        }
        if (type == keyWordArrayDefinition) {
            theType = "seq[string]";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "seq[int]";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "seq[string]";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "seq[float64]";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "seq[bool]";
        }
    }
    if (langToConvertTo == "ahk") {
        theType = "";
    }
    if (langToConvertTo == "swift") {
        if (type == keyWordVoid) {
            theType = "";
        }
        if (type == keyWordDouble) {
            theType = "Double";
        }
        if (type == keyWordChar) {
            theType = "Character";
        }
        if (type == keyWordUint8) {
            theType = "UInt8";
        }
        if (type == keyWordUint16) {
            theType = "UInt16";
        }
        if (type == keyWordUint32) {
            theType = "UInt32";
        }
        if (type == keyWordUint64) {
            theType = "UInt64";
        }
        if (type == keyWordINT) {
            theType = "Int";
        }
        if (type == keyWordSTR) {
            theType = "String";
        }
        if (type == keyWordBOOL) {
            theType = "Bool";
        }
        if (type == keyWordFLOAT) {
            theType = "Float";
        }
        if (type == keyWordINT8) {
            theType = "Int8";
        }
        if (type == keyWordINT16) {
            theType = "Int16";
        }
        if (type == keyWordINT32) {
            theType = "Int32";
        }
        if (type == keyWordINT64) {
            theType = "Int64";
        }
        if (type == keyWordArrayDefinition) {
            theType = "inout [String]";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "inout [Int]";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "inout [String]";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "inout [Float]";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "inout [Bool]";
        }
    }
    if (langToConvertTo == "dart") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "double";
        }
        if (type == keyWordChar) {
            theType = "String";
        }
        if (type == keyWordUint8) {
            theType = "int";
        }
        if (type == keyWordUint16) {
            theType = "int";
        }
        if (type == keyWordUint32) {
            theType = "int";
        }
        if (type == keyWordUint64) {
            theType = "BigInt";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "String";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "double";
        }
        if (type == keyWordINT8) {
            theType = "int";
        }
        if (type == keyWordINT16) {
            theType = "int";
        }
        if (type == keyWordINT32) {
            theType = "int";
        }
        if (type == keyWordINT64) {
            theType = "int";
        }
        if (type == keyWordArrayDefinition) {
            theType = "List<String>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "List<int>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "List<String>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "List<double>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "List<bool>";
        }
    }
    if (langToConvertTo == "ts") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "number";
        }
        if (type == keyWordChar) {
            theType = "string";
        }
        if (type == keyWordUint8) {
            theType = "number";
        }
        if (type == keyWordUint16) {
            theType = "number";
        }
        if (type == keyWordUint32) {
            theType = "number";
        }
        if (type == keyWordUint64) {
            theType = "bigint";
        }
        if (type == keyWordINT) {
            theType = "number";
        }
        if (type == keyWordSTR) {
            theType = "string";
        }
        if (type == keyWordBOOL) {
            theType = "boolean";
        }
        if (type == keyWordFLOAT) {
            theType = "number";
        }
        if (type == keyWordINT8) {
            theType = "number";
        }
        if (type == keyWordINT16) {
            theType = "number";
        }
        if (type == keyWordINT32) {
            theType = "number";
        }
        if (type == keyWordINT64) {
            theType = "bigint";
        }
        if (type == keyWordArrayDefinition) {
            theType = "string[]";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "number[]";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "string[]";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "number[]";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "boolean[]";
        }
    }
    if (langToConvertTo == "groovy") {
        theType = "";
    }
    if (langToConvertTo == langFileExtension_2) {
        // keyWordVoid
        // keyWordDouble
        // keyWordChar
        // keyWordUint8
        // keyWordUint16
        // keyWordUint32
        // keyWordUint64
        // keyWordINT
        // keyWordSTR
        // keyWordBOOL
        // keyWordFLOAT
        // keyWordINT8
        // keyWordINT16
        // keyWordINT32
        // keyWordINT64
        // keyWordArrayDefinition
        // keyWordArrayOfIntegersDefinition
        // keyWordArrayOfStringsDefinition
        // keyWordArrayOfFloatingPointNumbersDefinition
        // keyWordArrayOfBooleansDefinition
        if (type == keyWordVoid) {
            theType = keyWordVoid_2;
        }
        if (type == keyWordDouble) {
            theType = keyWordDouble_2;
        }
        if (type == keyWordChar) {
            theType = keyWordChar_2;
        }
        if (type == keyWordUint8) {
            theType = keyWordUint8_2;
        }
        if (type == keyWordUint16) {
            theType = keyWordUint16_2;
        }
        if (type == keyWordUint32) {
            theType = keyWordUint32_2;
        }
        if (type == keyWordUint64) {
            theType = keyWordUint64_2;
        }
        if (type == keyWordINT) {
            theType = keyWordINT_2;
        }
        if (type == keyWordSTR) {
            theType = keyWordSTR_2;
        }
        if (type == keyWordBOOL) {
            theType = keyWordBOOL_2;
        }
        if (type == keyWordFLOAT) {
            theType = keyWordFLOAT_2;
        }
        if (type == keyWordINT8) {
            theType = keyWordINT8_2;
        }
        if (type == keyWordINT16) {
            theType = keyWordINT16_2;
        }
        if (type == keyWordINT32) {
            theType = keyWordINT32_2;
        }
        if (type == keyWordINT64) {
            theType = keyWordINT64_2;
        }
        if (type == keyWordArrayDefinition) {
            theType = keyWordArrayDefinition_2;
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = keyWordArrayOfIntegersDefinition_2;
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = keyWordArrayOfStringsDefinition_2;
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = keyWordArrayOfFloatingPointNumbersDefinition_2;
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = keyWordArrayOfBooleansDefinition_2;
        }
    }
    return theType;
}
function getTheLastWord(line) {
    if (InStr(Trim(line), " ") == false) {
        return line;
    }
    items68 = LoopParseFunc(line, " ")
    for (let A_Index68 = 0; A_Index68 < items68.length + 0; A_Index68++) {
        const A_LoopField68 = items68[A_Index68 - 0];
        line = A_LoopField68;
    }
    return line;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function fixGoAindexUnseen(codeToFixTheGoUNSEEN) {
    var tempFixBugInfLoop = "";
    var AindexKeyWOrd = keyWordAIndex;
    // Regex to find all A_Index<num> occurrences
    let fixAindexInGoUnused = [];
    var tempFixIDK = "";
    var howMany_fixAindexInGoUnusedNUM = 0;
    var found_fixAindexInGoUnused = 0;
    var foundWHAT_fixAindexInGoUnused = "";
    items69 = LoopParseFunc(codeToFixTheGoUNSEEN, "\n", "\r")
    for (let A_Index69 = 0; A_Index69 < items69.length + 0; A_Index69++) {
        const A_LoopField69 = items69[A_Index69 - 0];
        if (RegExMatch(A_LoopField69, AindexKeyWOrd + "\\d+")) {
            if (SubStr(Trim(A_LoopField69), 1, 4) != "for ") {
                tempFixBugInfLoop = "";
                items70 = LoopParseFunc(A_LoopField69, " ")
                for (let A_Index70 = 0; A_Index70 < items70.length + 0; A_Index70++) {
                    const A_LoopField70 = items70[A_Index70 - 0];
                    if (InStr(A_LoopField70, AindexKeyWOrd)) {
                        tempFixBugInfLoop = ExtractDigits(StrSplit(A_LoopField70, AindexKeyWOrd, 2));
                        break;
                    }
                }
                HTVM_Append(fixAindexInGoUnused, AindexKeyWOrd + tempFixBugInfLoop);
            }
        }
    }
    howMany_fixAindexInGoUnused++;
    howMany_fixAindexInGoUnused++;
    for (let A_Index71 = 0; A_Index71 < howMany_fixAindexInGoUnused + 0; A_Index71++) {
        howMany_fixAindexInGoUnusedNUM = A_Index71;
        found_fixAindexInGoUnused = 0;
        foundWHAT_fixAindexInGoUnused = AindexKeyWOrd + STR(howMany_fixAindexInGoUnusedNUM);
        for (let A_Index72 = 0; A_Index72 < HTVM_Size(fixAindexInGoUnused) + 0; A_Index72++) {
            if (fixAindexInGoUnused[A_Index72] == AindexKeyWOrd + STR(howMany_fixAindexInGoUnusedNUM)) {
                found_fixAindexInGoUnused = 1;
                break;
            }
        }
        if (foundWHAT_fixAindexInGoUnused != "") {
            if (found_fixAindexInGoUnused == 0) {
                tempFixIDK = "";
                items73 = LoopParseFunc(codeToFixTheGoUNSEEN, "\n", "\r")
                for (let A_Index73 = 0; A_Index73 < items73.length + 0; A_Index73++) {
                    const A_LoopField73 = items73[A_Index73 - 0];
                    if (InStr(A_LoopField73, " := range ")) {
                        tempFixIDK += StrReplace(A_LoopField73, foundWHAT_fixAindexInGoUnused, "_") + Chr(10);
                    } else {
                        tempFixIDK += StrReplace(A_LoopField73, foundWHAT_fixAindexInGoUnused, "i") + Chr(10);
                    }
                }
                codeToFixTheGoUNSEEN = StringTrimRight(tempFixIDK, 1);
            }
        }
    }
    return codeToFixTheGoUNSEEN;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function GETfullLangAllOperators() {
    let fullLangAllOperators = [];
    if (langToConvertTo == "cpp") {
        HTVM_Append(fullLangAllOperators, "nullptr");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "py") {
        HTVM_Append(fullLangAllOperators, "None");
        HTVM_Append(fullLangAllOperators, "True");
        HTVM_Append(fullLangAllOperators, "False");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "**");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "is");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "and");
        HTVM_Append(fullLangAllOperators, "or");
        HTVM_Append(fullLangAllOperators, "not");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "js") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "**");
        if (useJavaScriptAlwaysTripleEqual == "on") {
            HTVM_Append(fullLangAllOperators, "===");
        } else {
            HTVM_Append(fullLangAllOperators, "==");
        }
        HTVM_Append(fullLangAllOperators, "===");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, ">>>");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "go") {
        HTVM_Append(fullLangAllOperators, "nil");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR");
    }
    if (langToConvertTo == "lua") {
        HTVM_Append(fullLangAllOperators, "nil");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "..");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "~=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "and");
        HTVM_Append(fullLangAllOperators, "or");
        HTVM_Append(fullLangAllOperators, "not");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "cs") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "java") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, ">>>");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "kt") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "===");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "and");
        HTVM_Append(fullLangAllOperators, "or");
        HTVM_Append(fullLangAllOperators, "xor");
        HTVM_Append(fullLangAllOperators, "inv");
        HTVM_Append(fullLangAllOperators, "shl");
        HTVM_Append(fullLangAllOperators, "shr");
        HTVM_Append(fullLangAllOperators, "ushr");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "rb") {
        HTVM_Append(fullLangAllOperators, "nil");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "**");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "nim") {
        HTVM_Append(fullLangAllOperators, "nil");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "HTVM--Fix-Nim-TheConcat-NOT--Working--AA");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "and");
        HTVM_Append(fullLangAllOperators, "or");
        HTVM_Append(fullLangAllOperators, "not");
        HTVM_Append(fullLangAllOperators, "and");
        HTVM_Append(fullLangAllOperators, "or");
        HTVM_Append(fullLangAllOperators, "xor");
        HTVM_Append(fullLangAllOperators, "not");
        HTVM_Append(fullLangAllOperators, "shl");
        HTVM_Append(fullLangAllOperators, "shr");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "ahk") {
        HTVM_Append(fullLangAllOperators, Chr(34) + "" + Chr(34));
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, ".");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "=");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "swift") {
        HTVM_Append(fullLangAllOperators, "nil");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "===");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "dart") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "===");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, ">>>");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "ts") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "**");
        if (useJavaScriptAlwaysTripleEqual == "on") {
            HTVM_Append(fullLangAllOperators, "===");
        } else {
            HTVM_Append(fullLangAllOperators, "==");
        }
        HTVM_Append(fullLangAllOperators, "===");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, ">>>");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == "groovy") {
        HTVM_Append(fullLangAllOperators, "null");
        HTVM_Append(fullLangAllOperators, "true");
        HTVM_Append(fullLangAllOperators, "false");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "+");
        HTVM_Append(fullLangAllOperators, "-");
        HTVM_Append(fullLangAllOperators, "*");
        HTVM_Append(fullLangAllOperators, "/");
        HTVM_Append(fullLangAllOperators, "%");
        HTVM_Append(fullLangAllOperators, "**");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "==");
        HTVM_Append(fullLangAllOperators, "!=");
        HTVM_Append(fullLangAllOperators, ">");
        HTVM_Append(fullLangAllOperators, "<");
        HTVM_Append(fullLangAllOperators, ">=");
        HTVM_Append(fullLangAllOperators, "<=");
        HTVM_Append(fullLangAllOperators, "&&");
        HTVM_Append(fullLangAllOperators, "||");
        HTVM_Append(fullLangAllOperators, "!");
        HTVM_Append(fullLangAllOperators, "&");
        HTVM_Append(fullLangAllOperators, "|");
        HTVM_Append(fullLangAllOperators, "^");
        HTVM_Append(fullLangAllOperators, "~");
        HTVM_Append(fullLangAllOperators, "<<");
        HTVM_Append(fullLangAllOperators, ">>");
        HTVM_Append(fullLangAllOperators, ">>>");
        HTVM_Append(fullLangAllOperators, "?");
        HTVM_Append(fullLangAllOperators, ":");
    }
    if (langToConvertTo == langFileExtension_2) {
        HTVM_Append(fullLangAllOperators, keyWordNull_2);
        HTVM_Append(fullLangAllOperators, keyWordTrue_2);
        HTVM_Append(fullLangAllOperators, keyWordFalse_2);
        HTVM_Append(fullLangAllOperators, keyWordConcat_2);
        HTVM_Append(fullLangAllOperators, keyWordAdd_2);
        HTVM_Append(fullLangAllOperators, keyWordSub_2);
        HTVM_Append(fullLangAllOperators, keyWordMul_2);
        HTVM_Append(fullLangAllOperators, keyWordDiv_2);
        HTVM_Append(fullLangAllOperators, keyWordMod_2);
        HTVM_Append(fullLangAllOperators, keyWordExp_2);
        HTVM_Append(fullLangAllOperators, keyWordEqual_2);
        HTVM_Append(fullLangAllOperators, keyWordStrictEqual_2);
        HTVM_Append(fullLangAllOperators, keyWordNotEqual_2);
        HTVM_Append(fullLangAllOperators, keyWordGreater_2);
        HTVM_Append(fullLangAllOperators, keyWordLess_2);
        HTVM_Append(fullLangAllOperators, keyWordGreaterEqual_2);
        HTVM_Append(fullLangAllOperators, keyWordLessEqual_2);
        HTVM_Append(fullLangAllOperators, keyWordAnd_2);
        HTVM_Append(fullLangAllOperators, keyWordOr_2);
        HTVM_Append(fullLangAllOperators, keyWordNot_2);
        HTVM_Append(fullLangAllOperators, keyWordBitAnd_2);
        HTVM_Append(fullLangAllOperators, keyWordBitOr_2);
        HTVM_Append(fullLangAllOperators, keyWordBitXor_2);
        HTVM_Append(fullLangAllOperators, keyWordBitNot_2);
        HTVM_Append(fullLangAllOperators, keyWordShiftLeft_2);
        HTVM_Append(fullLangAllOperators, keyWordShiftRight_2);
        HTVM_Append(fullLangAllOperators, keyWordShiftUnsignedRight_2);
        HTVM_Append(fullLangAllOperators, keyWordTernary1_2);
        HTVM_Append(fullLangAllOperators, keyWordTernary2_2);
    }
    return fullLangAllOperators;
}
function GETfullLangAllOperators_HELP() {
    let fullLangAllOperators_HELP = [];
    HTVM_Append(fullLangAllOperators_HELP, keyWordNull);
    HTVM_Append(fullLangAllOperators_HELP, keyWordTrue);
    HTVM_Append(fullLangAllOperators_HELP, keyWordFalse);
    HTVM_Append(fullLangAllOperators_HELP, keyWordConcat);
    HTVM_Append(fullLangAllOperators_HELP, keyWordAdd);
    HTVM_Append(fullLangAllOperators_HELP, keyWordSub);
    HTVM_Append(fullLangAllOperators_HELP, keyWordMul);
    HTVM_Append(fullLangAllOperators_HELP, keyWordDiv);
    HTVM_Append(fullLangAllOperators_HELP, keyWordMod);
    HTVM_Append(fullLangAllOperators_HELP, keyWordExp);
    HTVM_Append(fullLangAllOperators_HELP, keyWordEqual);
    HTVM_Append(fullLangAllOperators_HELP, keyWordStrictEqual);
    HTVM_Append(fullLangAllOperators_HELP, keyWordNotEqual);
    HTVM_Append(fullLangAllOperators_HELP, keyWordGreater);
    HTVM_Append(fullLangAllOperators_HELP, keyWordLess);
    HTVM_Append(fullLangAllOperators_HELP, keyWordGreaterEqual);
    HTVM_Append(fullLangAllOperators_HELP, keyWordLessEqual);
    HTVM_Append(fullLangAllOperators_HELP, keyWordAnd);
    HTVM_Append(fullLangAllOperators_HELP, keyWordOr);
    HTVM_Append(fullLangAllOperators_HELP, keyWordNot);
    HTVM_Append(fullLangAllOperators_HELP, keyWordBitAnd);
    HTVM_Append(fullLangAllOperators_HELP, keyWordBitOr);
    HTVM_Append(fullLangAllOperators_HELP, keyWordBitXor);
    HTVM_Append(fullLangAllOperators_HELP, keyWordBitNot);
    HTVM_Append(fullLangAllOperators_HELP, keyWordShiftLeft);
    HTVM_Append(fullLangAllOperators_HELP, keyWordShiftRight);
    HTVM_Append(fullLangAllOperators_HELP, keyWordShiftUnsignedRight);
    HTVM_Append(fullLangAllOperators_HELP, keyWordTernary1);
    HTVM_Append(fullLangAllOperators_HELP, keyWordTernary2);
    return fullLangAllOperators_HELP;
}
function expressionParserTranspiler(expression) {
    var fixExpertionLineFuncOnlyTEXT_func = "";
    var fixExpertionLineFuncOnlyTEXT_numDelete = 0;
    if (fixExpertionLineFuncOnly == 1) {
        fixExpertionLineFuncOnlyTEXT_func = StrSplit(expression, "(", 1);
        fixExpertionLineFuncOnlyTEXT_numDelete = StrLen(fixExpertionLineFuncOnlyTEXT_func) + 1;
        expression = StringTrimLeft(expression, fixExpertionLineFuncOnlyTEXT_numDelete);
    }
    // extra for array methods
    expression = arrayParserTranspiler(expression);
    if (langToConvertTo == langFileExtension_2) {
        expression = RegExReplace(expression, "\\b" + keyWordAwait + "\\b", keyWordAwait_2);
    }
    if (langToConvertTo == "js" || langToConvertTo == "ts") {
        expression = RegExReplace(expression, "\\b" + keyWordAwait + "\\b", "await ");
    }
    if (langToConvertTo != "js" && langToConvertTo != "ts" && langToConvertTo != langFileExtension_2) {
        expression = RegExReplace(expression, "\\b" + keyWordAwait + "\\b", "");
    }
    for (let A_Index74 = 0; A_Index74 < 29 + 0; A_Index74++) {
        if (InStr(expression, fullLangAllOperators_HELP[A_Index74])) {
            if (A_Index74 == 0 || A_Index74 == 1 || A_Index74 == 2) {
                expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index74] + "\\b", fullLangAllOperators[A_Index74]);
            } else {
                if (A_Index74 == 19) {
                    if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index74] + "\\b", "not");
                    } else {
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index74] + "\\b", "!");
                    }
                    if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
                        expression = RegExReplace(expression, "!([\\w]+)", "not $1");
                    }
                    expression = StrReplace(expression, " not= ", " != ");
                } else {
                    expression = StrReplace(expression, " " + fullLangAllOperators_HELP[A_Index74] + " ", " " + fullLangAllOperators[A_Index74] + " ");
                    if (A_Index74 == 28) {
                        if (langToConvertTo == "py") {
                            // Convert C-like ternary to Python ternary using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "$2 if $1 else $3");
                        }
                        if (langToConvertTo == "nim") {
                            // Convert C-like ternary to Nim ternary using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*)", "if $1: $2 else: $3");
                        }
                        if (langToConvertTo == "lua") {
                            // Convert C-like ternary to Lua ternary-like expression using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "$1 and $2 or $3");
                        }
                        if (langToConvertTo == "kt") {
                            // Convert C-like ternary to Kotlin ternary-like expression using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "if $1 $2 else $3");
                        }
                    }
                }
            }
        }
    }
    if (langToConvertTo == "ahk") {
        if (InStr(expression, keyWordAIndex)) {
            expression = RegExReplace(expression, "\\b" + keyWordAIndex + "\\b", "A_Index");
        }
        if (InStr(expression, keyWordALoopField)) {
            expression = RegExReplace(expression, "\\b" + keyWordALoopField + "\\b", "A_LoopField");
        }
    }
    if (langToConvertTo == "rb") {
        expression = RegExReplace(expression, keyWordAIndexOriginal + "(\\d*)", StrLower(keyWordAIndexOriginal) + "$1");
        expression = RegExReplace(expression, keyWordALoopFieldOriginal + "(\\d*)", StrLower(keyWordALoopFieldOriginal) + "$1");
    }
    if (langToConvertTo == langFileExtension_2) {
        if (InStr(expression, keyWordAIndex)) {
            expression = RegExReplace(expression, "\\b" + keyWordAIndex + "\\b", keyWordAIndex_2);
        }
        if (InStr(expression, keyWordALoopField)) {
            expression = RegExReplace(expression, "\\b" + keyWordALoopField + "\\b", keyWordALoopField_2);
        }
    }
    if (langToConvertTo != langFileExtension_2 && langToConvertTo != "ahk") {
        if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
            expression = StrReplace(expression, ") and (", " and ");
            expression = StrReplace(expression, ") or (", " or ");
        } else {
            expression = StrReplace(expression, ") && (", " && ");
            expression = StrReplace(expression, ") || (", " || ");
        }
    }
    if (langToConvertTo == "cpp") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".what()");
    }
    if (langToConvertTo == "js") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    if (langToConvertTo == "cs") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".Message");
    }
    if (langToConvertTo == "java") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".getMessage()");
    }
    if (langToConvertTo == "kt") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    if (langToConvertTo == "rb") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    if (langToConvertTo == "nim") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".msg");
    }
    if (langToConvertTo == "swift") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".localizedDescription");
    }
    if (langToConvertTo == "ts") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    if (langToConvertTo == "groovy") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    // fix java arrName[A_Index] not existing
    if (langToConvertTo == "java") {
        expression = RegExReplace(expression, "(\\b[A-Za-z_]\\w*)\\s*\\[", "$1.get(");
        expression = StrReplace(expression, "]", ")");
    }
    if (langToConvertTo == "swift") {
        expression = StrReplace(expression, Chr(39), Chr(34));
    }
    if (langToConvertTo == "ahk") {
        expression = StrReplace(expression, Chr(39), Chr(34));
    }
    if (fixExpertionLineFuncOnly == 1) {
        expression = fixExpertionLineFuncOnlyTEXT_func + "(" + expression;
    }
    if (langToConvertTo == "nim") {
        expression = StrReplace(expression, "HTVM--Fix-Nim-TheConcat-NOT--Working--AA", "&");
    }
    return expression;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function compiler(htCode, allInstructionFile, mode, langToConvertToParam = "") {
    var instructions = allInstructionFile;
    items75 = LoopParseFunc(allInstructionFile, "\n", "\r")
    for (let A_Index75 = 0; A_Index75 < items75.length + 0; A_Index75++) {
        const A_LoopField75 = items75[A_Index75 - 0];
        if (A_Index75 == 0) {
            langToConvertTo = Trim(A_LoopField75);
        }
        if (A_Index75 == 1) {
            langFileExtension = Trim(A_LoopField75);
        }
        if (A_Index75 == 2) {
            commands = Trim(A_LoopField75);
        }
        if (A_Index75 == 3) {
            keyWordAlliance = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 4) {
            keyWordCrew = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 5) {
            keyWordMethod = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 6) {
            keyWordDefObj = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 7) {
            keyWordPorp = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 8) {
            keyWordThis = Trim(A_LoopField75);
        }
        if (A_Index75 == 9) {
            keyWordInclude = Trim(A_LoopField75);
        }
        if (A_Index75 == 10) {
            keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField75);
        }
        if (A_Index75 == 11) {
            keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField75);
        }
        if (A_Index75 == 12) {
            keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField75);
        }
        if (A_Index75 == 13) {
            keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField75);
        }
        if (A_Index75 == 14) {
            keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField75);
        }
        if (A_Index75 == 15) {
            keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField75);
        }
        if (A_Index75 == 16) {
            keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField75);
        }
        if (A_Index75 == 17) {
            keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField75);
        }
        if (A_Index75 == 18) {
            keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField75);
        }
        if (A_Index75 == 19) {
            keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField75);
        }
        if (A_Index75 == 20) {
            keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField75);
        }
        if (A_Index75 == 21) {
            keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField75);
        }
        if (A_Index75 == 22) {
            keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField75);
        }
        if (A_Index75 == 23) {
            keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField75);
        }
        if (A_Index75 == 24) {
            keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField75);
        }
        if (A_Index75 == 25) {
            keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField75);
        }
        if (A_Index75 == 26) {
            keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField75);
        }
        if (A_Index75 == 27) {
            keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField75);
        }
        if (A_Index75 == 28) {
            keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField75);
        }
        if (A_Index75 == 29) {
            keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField75);
        }
        if (A_Index75 == 30) {
            keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField75);
        }
        if (A_Index75 == 31) {
            keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField75);
        }
        if (A_Index75 == 32) {
            keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField75);
        }
        if (A_Index75 == 33) {
            keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField75);
        }
        if (A_Index75 == 34) {
            keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField75);
        }
        if (A_Index75 == 35) {
            keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField75);
        }
        if (A_Index75 == 36) {
            keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField75);
        }
        if (A_Index75 == 37) {
            keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField75);
        }
        if (A_Index75 == 38) {
            keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField75);
        }
        if (A_Index75 == 39) {
            keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField75);
        }
        if (A_Index75 == 40) {
            keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField75);
        }
        if (A_Index75 == 41) {
            keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField75);
        }
        if (A_Index75 == 42) {
            keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField75);
        }
        if (A_Index75 == 43) {
            keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField75);
        }
        if (A_Index75 == 44) {
            keyWordCodeInHTVMstart = Trim(A_LoopField75);
        }
        if (A_Index75 == 45) {
            keyWordCodeInHTVMend = Trim(A_LoopField75);
        }
        if (A_Index75 == 46) {
            keyWordCurlyBraceOpen = Trim(A_LoopField75);
        }
        if (A_Index75 == 47) {
            keyWordCurlyBraceClose = Trim(A_LoopField75);
        }
        if (A_Index75 == 48) {
            keyWordNull = Trim(A_LoopField75);
        }
        if (A_Index75 == 49) {
            keyWordTrue = Trim(A_LoopField75);
        }
        if (A_Index75 == 50) {
            keyWordFalse = Trim(A_LoopField75);
        }
        if (A_Index75 == 51) {
            keyWordVoid = Trim(A_LoopField75);
        }
        if (A_Index75 == 52) {
            keyWordDouble = Trim(A_LoopField75);
        }
        if (A_Index75 == 53) {
            keyWordChar = Trim(A_LoopField75);
        }
        if (A_Index75 == 54) {
            keyWordUint8 = Trim(A_LoopField75);
        }
        if (A_Index75 == 55) {
            keyWordUint16 = Trim(A_LoopField75);
        }
        if (A_Index75 == 56) {
            keyWordUint32 = Trim(A_LoopField75);
        }
        if (A_Index75 == 57) {
            keyWordUint64 = Trim(A_LoopField75);
        }
        if (A_Index75 == 58) {
            keyWordINT = Trim(A_LoopField75);
        }
        if (A_Index75 == 59) {
            keyWordSTR = Trim(A_LoopField75);
        }
        if (A_Index75 == 60) {
            keyWordBOOL = Trim(A_LoopField75);
        }
        if (A_Index75 == 61) {
            keyWordFLOAT = Trim(A_LoopField75);
        }
        if (A_Index75 == 62) {
            keyWordINT8 = Trim(A_LoopField75);
        }
        if (A_Index75 == 63) {
            keyWordINT16 = Trim(A_LoopField75);
        }
        if (A_Index75 == 64) {
            keyWordINT32 = Trim(A_LoopField75);
        }
        if (A_Index75 == 65) {
            keyWordINT64 = Trim(A_LoopField75);
        }
        if (A_Index75 == 66) {
            keyWordIF = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 67) {
            keyWordElseIf = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 68) {
            keyWordElse = Trim(A_LoopField75);
        }
        if (A_Index75 == 69) {
            keyWordWhileLoop = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 70) {
            keyWordLoopInfinite = Trim(A_LoopField75);
        }
        if (A_Index75 == 71) {
            keyWordLoop = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 72) {
            keyWordLoopParse = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 73) {
            keyWordContinue = Trim(A_LoopField75);
        }
        if (A_Index75 == 74) {
            keyWordBreak = Trim(A_LoopField75);
        }
        if (A_Index75 == 75) {
            keyWordFunc = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 76) {
            keyWordAwait = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 77) {
            keyWordAsync = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 78) {
            keyWordThrow = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 79) {
            keyWordErrorMsg = Trim(A_LoopField75);
        }
        if (A_Index75 == 80) {
            keyWordTry = Trim(A_LoopField75);
        }
        if (A_Index75 == 81) {
            keyWordCatch = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 82) {
            keyWordFinally = Trim(A_LoopField75);
        }
        if (A_Index75 == 83) {
            keyWordReturnStatement = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 84) {
            keyWordArrayAppend = Trim(A_LoopField75);
        }
        if (A_Index75 == 85) {
            keyWordArrayPop = Trim(A_LoopField75);
        }
        if (A_Index75 == 86) {
            keyWordArraySize = Trim(A_LoopField75);
        }
        if (A_Index75 == 87) {
            keyWordArrayInsert = Trim(A_LoopField75);
        }
        if (A_Index75 == 88) {
            keyWordArrayRemove = Trim(A_LoopField75);
        }
        if (A_Index75 == 89) {
            keyWordArrayIndexOf = Trim(A_LoopField75);
        }
        if (A_Index75 == 90) {
            keyWordArrayDefinition = Trim(A_LoopField75);
        }
        if (A_Index75 == 91) {
            keyWordArrayOfIntegersDefinition = Trim(A_LoopField75);
        }
        if (A_Index75 == 92) {
            keyWordArrayOfStringsDefinition = Trim(A_LoopField75);
        }
        if (A_Index75 == 93) {
            keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField75);
        }
        if (A_Index75 == 94) {
            keyWordArrayOfBooleansDefinition = Trim(A_LoopField75);
        }
        if (A_Index75 == 95) {
            keyWordVar = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 96) {
            keyWordLet = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 97) {
            keyWordConst = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 98) {
            keyWordEnd = Trim(A_LoopField75);
        }
        if (A_Index75 == 99) {
            keyWordGlobal = Trim(A_LoopField75) + " ";
        }
        if (A_Index75 == 100) {
            keyWordComment = Trim(A_LoopField75);
        }
        if (A_Index75 == 101) {
            keyWordCommentOpenMultiLine = Trim(A_LoopField75);
        }
        if (A_Index75 == 102) {
            keyWordCommentCloseMultiLine = Trim(A_LoopField75);
        }
        if (A_Index75 == 103) {
            keyWordEscpaeChar = Trim(A_LoopField75);
        }
        if (A_Index75 == 104) {
            keyWordMainLabel = Trim(A_LoopField75);
        }
        if (A_Index75 == 105) {
            keyWordConcat = Trim(A_LoopField75);
        }
        if (A_Index75 == 106) {
            keyWordAdd = Trim(A_LoopField75);
        }
        if (A_Index75 == 107) {
            keyWordSub = Trim(A_LoopField75);
        }
        if (A_Index75 == 108) {
            keyWordMul = Trim(A_LoopField75);
        }
        if (A_Index75 == 109) {
            keyWordDiv = Trim(A_LoopField75);
        }
        if (A_Index75 == 110) {
            keyWordMod = Trim(A_LoopField75);
        }
        if (A_Index75 == 111) {
            keyWordExp = Trim(A_LoopField75);
        }
        if (A_Index75 == 112) {
            keyWordEqual = Trim(A_LoopField75);
        }
        if (A_Index75 == 113) {
            keyWordStrictEqual = Trim(A_LoopField75);
        }
        if (A_Index75 == 114) {
            keyWordNotEqual = Trim(A_LoopField75);
        }
        if (A_Index75 == 115) {
            keyWordGreater = Trim(A_LoopField75);
        }
        if (A_Index75 == 116) {
            keyWordLess = Trim(A_LoopField75);
        }
        if (A_Index75 == 117) {
            keyWordGreaterEqual = Trim(A_LoopField75);
        }
        if (A_Index75 == 118) {
            keyWordLessEqual = Trim(A_LoopField75);
        }
        if (A_Index75 == 119) {
            keyWordAnd = Trim(A_LoopField75);
        }
        if (A_Index75 == 120) {
            keyWordOr = Trim(A_LoopField75);
        }
        if (A_Index75 == 121) {
            keyWordNot = Trim(A_LoopField75);
        }
        if (A_Index75 == 122) {
            keyWordBitAnd = Trim(A_LoopField75);
        }
        if (A_Index75 == 123) {
            keyWordBitOr = Trim(A_LoopField75);
        }
        if (A_Index75 == 124) {
            keyWordBitXor = Trim(A_LoopField75);
        }
        if (A_Index75 == 125) {
            keyWordBitNot = Trim(A_LoopField75);
        }
        if (A_Index75 == 126) {
            keyWordShiftLeft = Trim(A_LoopField75);
        }
        if (A_Index75 == 127) {
            keyWordShiftRight = Trim(A_LoopField75);
        }
        if (A_Index75 == 128) {
            keyWordShiftUnsignedRight = Trim(A_LoopField75);
        }
        if (A_Index75 == 129) {
            keyWordAssign = Trim(A_LoopField75);
        }
        if (A_Index75 == 130) {
            keyWordAssignAdd = Trim(A_LoopField75);
        }
        if (A_Index75 == 131) {
            keyWordAssignConcat = Trim(A_LoopField75);
        }
        if (A_Index75 == 132) {
            keyWordAssignSub = Trim(A_LoopField75);
        }
        if (A_Index75 == 133) {
            keyWordAssignMul = Trim(A_LoopField75);
        }
        if (A_Index75 == 134) {
            keyWordAssignDiv = Trim(A_LoopField75);
        }
        if (A_Index75 == 135) {
            keyWordAssignMod = Trim(A_LoopField75);
        }
        if (A_Index75 == 136) {
            keyWordAssignShiftLeft = Trim(A_LoopField75);
        }
        if (A_Index75 == 137) {
            keyWordAssignShiftRight = Trim(A_LoopField75);
        }
        if (A_Index75 == 138) {
            keyWordLogicalAssignShiftRight = Trim(A_LoopField75);
        }
        if (A_Index75 == 139) {
            keyWordAssignBitAnd = Trim(A_LoopField75);
        }
        if (A_Index75 == 140) {
            keyWordAssignBitOr = Trim(A_LoopField75);
        }
        if (A_Index75 == 141) {
            keyWordAssignBitXor = Trim(A_LoopField75);
        }
        if (A_Index75 == 142) {
            keyWordTernary1 = Trim(A_LoopField75);
        }
        if (A_Index75 == 143) {
            keyWordTernary2 = Trim(A_LoopField75);
        }
        if (A_Index75 == 144) {
            keyWordInc = Trim(A_LoopField75);
        }
        if (A_Index75 == 145) {
            keyWordDec = Trim(A_LoopField75);
        }
        if (A_Index75 == 146) {
            AHKlikeLoopsIndexedAt = Trim(A_LoopField75);
        }
        if (A_Index75 == 147) {
            keyWordAIndex = Trim(A_LoopField75);
        }
        if (A_Index75 == 148) {
            keyWordALoopField = Trim(A_LoopField75);
        }
        if (A_Index75 == 149) {
            useCurlyBraces = Trim(A_LoopField75);
        }
        if (A_Index75 == 150) {
            useEnd = Trim(A_LoopField75);
        }
        if (A_Index75 == 151) {
            useSemicolon = Trim(A_LoopField75);
        }
        if (A_Index75 == 152) {
            useParentheses = Trim(A_LoopField75);
        }
        if (A_Index75 == 153) {
            usePrefixTypeForTypeDefinition = Trim(A_LoopField75);
        }
        if (A_Index75 == 154) {
            usePostfixTypeForTypeDefinition = Trim(A_LoopField75);
        }
        if (A_Index75 == 155) {
            usePythonicColonSyntax = Trim(A_LoopField75);
        }
        if (A_Index75 == 156) {
            useCurlyBracesSyntaxForArrayDef = Trim(A_LoopField75);
        }
        if (A_Index75 == 157) {
            useInJavaScriptAlwaysUseVar = Trim(A_LoopField75);
        }
        if (A_Index75 == 158) {
            useJavaScriptInAfullHTMLfile = Trim(A_LoopField75);
        }
        if (A_Index75 == 159) {
            useJavaScriptAmainFuncDef = Trim(A_LoopField75);
        }
        if (A_Index75 == 160) {
            useJavaScriptAllFuncsAreAsync = Trim(A_LoopField75);
        }
        if (A_Index75 == 161) {
            useJavaScriptAlwaysTripleEqual = Trim(A_LoopField75);
        }
    }
    if (HTVM_Size(argHTVMinstrMORE) > 0) {
        var allInstructionFile_2 = Trim(FileRead(Trim(argHTVMinstrMORE[0])));
        items76 = LoopParseFunc(allInstructionFile_2, "\n", "\r")
        for (let A_Index76 = 0; A_Index76 < items76.length + 0; A_Index76++) {
            const A_LoopField76 = items76[A_Index76 - 0];
            if (A_Index76 == 0) {
                langToConvertTo_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 1) {
                langFileExtension_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 2) {
                commands_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 3) {
                keyWordAlliance_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 4) {
                keyWordCrew_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 5) {
                keyWordMethod_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 6) {
                keyWordDefObj_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 7) {
                keyWordPorp_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 8) {
                keyWordThis_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 9) {
                keyWordInclude_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 10) {
                keyWordCodeInTheTranspiledLangStart_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 11) {
                keyWordCodeInTheTranspiledLangEnd_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 12) {
                keyWordCodeInTheTranspiledLangStartCPP_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 13) {
                keyWordCodeInTheTranspiledLangEndCPP_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 14) {
                keyWordCodeInTheTranspiledLangStartPY_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 15) {
                keyWordCodeInTheTranspiledLangEndPY_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 16) {
                keyWordCodeInTheTranspiledLangStartJS_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 17) {
                keyWordCodeInTheTranspiledLangEndJS_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 18) {
                keyWordCodeInTheTranspiledLangStartGO_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 19) {
                keyWordCodeInTheTranspiledLangEndGO_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 20) {
                keyWordCodeInTheTranspiledLangStartLUA_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 21) {
                keyWordCodeInTheTranspiledLangEndLUA_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 22) {
                keyWordCodeInTheTranspiledLangStartCS_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 23) {
                keyWordCodeInTheTranspiledLangEndCS_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 24) {
                keyWordCodeInTheTranspiledLangStartJAVA_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 25) {
                keyWordCodeInTheTranspiledLangEndJAVA_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 26) {
                keyWordCodeInTheTranspiledLangStartKT_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 27) {
                keyWordCodeInTheTranspiledLangEndKT_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 28) {
                keyWordCodeInTheTranspiledLangStartRB_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 29) {
                keyWordCodeInTheTranspiledLangEndRB_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 30) {
                keyWordCodeInTheTranspiledLangStartNIM_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 31) {
                keyWordCodeInTheTranspiledLangEndNIM_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 32) {
                keyWordCodeInTheTranspiledLangStartAHK_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 33) {
                keyWordCodeInTheTranspiledLangEndAHK_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 34) {
                keyWordCodeInTheTranspiledLangStartSWIFT_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 35) {
                keyWordCodeInTheTranspiledLangEndSWIFT_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 36) {
                keyWordCodeInTheTranspiledLangStartDART_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 37) {
                keyWordCodeInTheTranspiledLangEndDART_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 38) {
                keyWordCodeInTheTranspiledLangStartTS_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 39) {
                keyWordCodeInTheTranspiledLangEndTS_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 40) {
                keyWordCodeInTheTranspiledLangStartGROOVY_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 41) {
                keyWordCodeInTheTranspiledLangEndGROOVY_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 42) {
                keyWordCodeInTheTranspiledLangStartHTVM_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 43) {
                keyWordCodeInTheTranspiledLangEndHTVM_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 44) {
                keyWordCodeInHTVMstart_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 45) {
                keyWordCodeInHTVMend_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 46) {
                keyWordCurlyBraceOpen_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 47) {
                keyWordCurlyBraceClose_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 48) {
                keyWordNull_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 49) {
                keyWordTrue_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 50) {
                keyWordFalse_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 51) {
                keyWordVoid_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 52) {
                keyWordDouble_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 53) {
                keyWordChar_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 54) {
                keyWordUint8_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 55) {
                keyWordUint16_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 56) {
                keyWordUint32_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 57) {
                keyWordUint64_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 58) {
                keyWordINT_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 59) {
                keyWordSTR_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 60) {
                keyWordBOOL_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 61) {
                keyWordFLOAT_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 62) {
                keyWordINT8_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 63) {
                keyWordINT16_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 64) {
                keyWordINT32_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 65) {
                keyWordINT64_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 66) {
                keyWordIF_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 67) {
                keyWordElseIf_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 68) {
                keyWordElse_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 69) {
                keyWordWhileLoop_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 70) {
                keyWordLoopInfinite_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 71) {
                keyWordLoop_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 72) {
                keyWordLoopParse_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 73) {
                keyWordContinue_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 74) {
                keyWordBreak_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 75) {
                keyWordFunc_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 76) {
                keyWordAwait_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 77) {
                keyWordAsync_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 78) {
                keyWordThrow_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 79) {
                keyWordErrorMsg_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 80) {
                keyWordTry_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 81) {
                keyWordCatch_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 82) {
                keyWordFinally_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 83) {
                keyWordReturnStatement_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 84) {
                keyWordArrayAppend_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 85) {
                keyWordArrayPop_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 86) {
                keyWordArraySize_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 87) {
                keyWordArrayInsert_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 88) {
                keyWordArrayRemove_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 89) {
                keyWordArrayIndexOf_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 90) {
                keyWordArrayDefinition_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 91) {
                keyWordArrayOfIntegersDefinition_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 92) {
                keyWordArrayOfStringsDefinition_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 93) {
                keyWordArrayOfFloatingPointNumbersDefinition_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 94) {
                keyWordArrayOfBooleansDefinition_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 95) {
                keyWordVar_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 96) {
                keyWordLet_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 97) {
                keyWordConst_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 98) {
                keyWordEnd_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 99) {
                keyWordGlobal_2 = Trim(A_LoopField76) + " ";
            }
            if (A_Index76 == 100) {
                keyWordComment_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 101) {
                keyWordCommentOpenMultiLine_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 102) {
                keyWordCommentCloseMultiLine_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 103) {
                keyWordEscpaeChar_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 104) {
                keyWordMainLabel_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 105) {
                keyWordConcat_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 106) {
                keyWordAdd_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 107) {
                keyWordSub_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 108) {
                keyWordMul_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 109) {
                keyWordDiv_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 110) {
                keyWordMod_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 111) {
                keyWordExp_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 112) {
                keyWordEqual_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 113) {
                keyWordStrictEqual_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 114) {
                keyWordNotEqual_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 115) {
                keyWordGreater_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 116) {
                keyWordLess_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 117) {
                keyWordGreaterEqual_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 118) {
                keyWordLessEqual_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 119) {
                keyWordAnd_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 120) {
                keyWordOr_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 121) {
                keyWordNot_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 122) {
                keyWordBitAnd_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 123) {
                keyWordBitOr_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 124) {
                keyWordBitXor_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 125) {
                keyWordBitNot_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 126) {
                keyWordShiftLeft_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 127) {
                keyWordShiftRight_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 128) {
                keyWordShiftUnsignedRight_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 129) {
                keyWordAssign_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 130) {
                keyWordAssignAdd_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 131) {
                keyWordAssignConcat_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 132) {
                keyWordAssignSub_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 133) {
                keyWordAssignMul_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 134) {
                keyWordAssignDiv_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 135) {
                keyWordAssignMod_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 136) {
                keyWordAssignShiftLeft_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 137) {
                keyWordAssignShiftRight_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 138) {
                keyWordLogicalAssignShiftRight_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 139) {
                keyWordAssignBitAnd_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 140) {
                keyWordAssignBitOr_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 141) {
                keyWordAssignBitXor_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 142) {
                keyWordTernary1_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 143) {
                keyWordTernary2_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 144) {
                keyWordInc_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 145) {
                keyWordDec_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 146) {
                AHKlikeLoopsIndexedAt_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 147) {
                keyWordAIndex_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 148) {
                keyWordALoopField_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 149) {
                useCurlyBraces_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 150) {
                useEnd_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 151) {
                useSemicolon_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 152) {
                useParentheses_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 153) {
                usePrefixTypeForTypeDefinition_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 154) {
                usePostfixTypeForTypeDefinition_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 155) {
                usePythonicColonSyntax_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 156) {
                useCurlyBracesSyntaxForArrayDef_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 157) {
                useInJavaScriptAlwaysUseVar_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 158) {
                useJavaScriptInAfullHTMLfile_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 159) {
                useJavaScriptAmainFuncDef_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 160) {
                useJavaScriptAllFuncsAreAsync_2 = Trim(A_LoopField76);
            }
            if (A_Index76 == 161) {
                useJavaScriptAlwaysTripleEqual_2 = Trim(A_LoopField76);
            }
        }
    }
    if (Trim(langToConvertToParam) != "") {
        langToConvertTo = Trim(langToConvertToParam);
    }
    var isFullHTVMCode = 0;
    var isNotHTVMfile = 0;
    if (Trim(mode) == "full") {
        isFullHTVMCode = 1;
    } else {
        isFullHTVMCode = 0;
    }
    if (Trim(mode) == "notHTVM") {
        isNotHTVMfile = 1;
    } else {
        isNotHTVMfile = 0;
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    /*
    if (langToConvertTo == langFileExtension_2) {
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
    if (langToConvertTo == "groovy") {
    }
    */
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var HTVMout = "";
    htCode = Trim(StrReplace(htCode, Chr(13), ""));
    var code = "";
    //print(htCode)
    code = htCode;
    //print(mode)
    //print(langToConvertTo)
    //print("==================================")
    //print("==================================")
    //print("==================================")
    //print("==================================")
    //print("==================================")
    //print(allInstructionFile)
    if (langToConvertTo == "rb") {
        keyWordAIndexOriginal = keyWordAIndex;
        keyWordALoopFieldOriginal = keyWordALoopField;
        keyWordAIndex = StrLower(keyWordAIndex);
        keyWordALoopField = StrLower(keyWordALoopField);
    }
    var haveWeEverUsedAloop = 0;
    var lineDone = 0;
    var var1 = "";
    var nothing = "";
    var AindexcharLength = 1;
    var AindexcharLengthStr = "";
    var theFixTextLoopNL = "";
    var htCodeAcurlyBraceAddSomeVrasFixNL = 0;
    var htCodeLoopfixa = "";
    var htCodeLoopfixa1 = "";
    var str123 = "";
    var out2 = "";
    var myVar = "";
    var lineYGI = "";
    var line = "";
    var line1 = "";
    var line2 = "";
    var line3 = "";
    var itemsOut = "";
    var var1out = "";
    var theFixTextLoopLP = "";
    var htCodeAcurlyBraceAddSomeVrasFixLP = 0;
    var AIndexLoopCurlyFix = 0;
    var sstr123 = "";
    var fixLoopLokingFor = "";
    var fixLoopLokingForfound = 0;
    var out1 = "";
    var wasAtanyIfsElseAddAIndexLoopCurlyFix = 0;
    var inTarget = 0;
    var insideBracket = 0;
    var netsedCurly = 0;
    var eldLoopNestedBADlol = 0;
    var readyToEnd = 0;
    var endBracketDOntPutThere = 0;
    var dontSaveStr = 0;
    var weAreDoneHereCurly = 0;
    var DeleayOneCuzOfLoopParse = 0;
    var fixLoopLokingForNum = 0;
    var insdeAnestedLoopBAD = 0;
    var foundTheTopLoop = 0;
    var out4758686d86d86d86578991a;
    var ALoopField = "";
    var out1z = "";
    var insideBracket1 = 0;
    var netsedCurly1 = 0;
    var readyToEnd1 = 0;
    var strstysrstsytTRIMHELP = "";
    var out4758686d86dgt8r754444444 = "";
    var hold = 0;
    var holdText = "";
    var ignore = 0;
    var htCodeOut1234565432 = "";
    var out = "";
    var s = "";
    var skipLeftCuleyForFuncPLS = 0;
    // keyWordInclude
    // keyWordInclude
    // keyWordInclude
    var allLibCODE = "";
    var allLibCODEfix = "";
    let allLibsWeSee = [];
    let allLibsWeSeeSEE = [];
    var allLibsWeSeeHOLD = "";
    var doseCodeHaveLibs = 0;
    var doseCodeHaveLibs_HAS_SEEN = 0;
    var doseCodeHaveLibs_HAS_SEEN2 = 0;
    if (isNotHTVMfile == 0) {
        if (langToConvertTo != langFileExtension_2) {
            if (InStr(StrLower(code), StrLower(keyWordInclude + " "))) {
                for (let A_Index77 = 0; A_Index77 < 10000 + 0; A_Index77++) {
                    doseCodeHaveLibs = 0;
                    allLibCODE = "";
                    if (A_Index77 == 0) {
                        items78 = LoopParseFunc(code, "\n", "\r")
                        for (let A_Index78 = 0; A_Index78 < items78.length + 0; A_Index78++) {
                            const A_LoopField78 = items78[A_Index78 - 0];
                            if (SubStr(StrLower(Trim(A_LoopField78)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ")) {
                                HTVM_Append(allLibsWeSee, StrReplace(StringTrimLeft(Trim(A_LoopField78), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                HTVM_Append(allLibsWeSeeSEE, StrReplace(StringTrimLeft(Trim(A_LoopField78), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                doseCodeHaveLibs = 1;
                            }
                        }
                    } else {
                        items79 = LoopParseFunc(code, "\n", "\r")
                        for (let A_Index79 = 0; A_Index79 < items79.length + 0; A_Index79++) {
                            const A_LoopField79 = items79[A_Index79 - 0];
                            ALoopField = A_LoopField79;
                            if (SubStr(StrLower(Trim(A_LoopField79)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ")) {
                                doseCodeHaveLibs_HAS_SEEN = 0;
                                for (let A_Index80 = 0; A_Index80 < HTVM_Size(allLibsWeSee) + 0; A_Index80++) {
                                    if (StrReplace(StringTrimLeft(Trim(ALoopField), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), "") == allLibsWeSee[A_Index80]) {
                                        doseCodeHaveLibs_HAS_SEEN = 1;
                                    }
                                }
                                if (doseCodeHaveLibs_HAS_SEEN == 0) {
                                    HTVM_Append(allLibsWeSee, StrReplace(StringTrimLeft(Trim(A_LoopField79), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                    HTVM_Append(allLibsWeSeeSEE, StrReplace(StringTrimLeft(Trim(A_LoopField79), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                    doseCodeHaveLibs = 1;
                                }
                            }
                        }
                    }
                    for (let A_Index81 = 0; A_Index81 < HTVM_Size(allLibsWeSee) + 0; A_Index81++) {
                        allLibsWeSeeHOLD = allLibsWeSee[A_Index81];
                        doseCodeHaveLibs_HAS_SEEN2 = 0;
                        for (let A_Index82 = 0; A_Index82 < HTVM_Size(allLibsWeSeeSEE) - HTVM_Size(allLibsWeSee) + 0; A_Index82++) {
                            if (allLibsWeSeeHOLD == allLibsWeSeeSEE[A_Index82]) {
                                doseCodeHaveLibs_HAS_SEEN2 = 1;
                            }
                        }
                        if (doseCodeHaveLibs_HAS_SEEN2 == 0) {
                            allLibCODE += FileRead(Trim(allLibsWeSee[HTVM_Size(allLibsWeSee) - A_Index81 - 1])) + Chr(10);
                        }
                        HTVM_Pop(allLibsWeSee);
                    }
                    allLibCODEfix = "";
                    items83 = LoopParseFunc(code, "\n", "\r")
                    for (let A_Index83 = 0; A_Index83 < items83.length + 0; A_Index83++) {
                        const A_LoopField83 = items83[A_Index83 - 0];
                        if (SubStr(StrLower(Trim(A_LoopField83)), 1, StrLen(StrLower(keyWordInclude + " "))) != StrLower(keyWordInclude + " ")) {
                            allLibCODEfix += A_LoopField83 + Chr(10);
                        }
                    }
                    code = StringTrimRight(allLibCODEfix, 1);
                    code = allLibCODE + code;
                    if (doseCodeHaveLibs == 0) {
                        break;
                    }
                }
            }
        }
        ALoopField = "";
    }
    // keyWordInclude
    // keyWordInclude
    // keyWordInclude
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    var COUNT_programmingBlock_InTheTranspiledLang = 0;
    var COUNT_programmingBlock_CPP = 0;
    var COUNT_programmingBlock_PY = 0;
    var COUNT_programmingBlock_JS = 0;
    var COUNT_programmingBlock_GO = 0;
    var COUNT_programmingBlock_LUA = 0;
    var COUNT_programmingBlock_CS = 0;
    var COUNT_programmingBlock_JAVA = 0;
    var COUNT_programmingBlock_KT = 0;
    var COUNT_programmingBlock_RB = 0;
    var COUNT_programmingBlock_NIM = 0;
    var COUNT_programmingBlock_AHK = 0;
    var COUNT_programmingBlock_SWIFT = 0;
    var COUNT_programmingBlock_DART = 0;
    var COUNT_programmingBlock_TS = 0;
    var COUNT_programmingBlock_GROOVY = 0;
    var COUNT_programmingBlock_HTVM = 0;
    var COUNT_programmingBlock_HTVMsyntax = 0;
    var programmingBlocksTemp = "";
    var inProgarmmingBlock = 0;
    var holdTempDataProgrammingBlockThenPutInArr = "";
    items84 = LoopParseFunc(code, "\n", "\r")
    for (let A_Index84 = 0; A_Index84 < items84.length + 0; A_Index84++) {
        const A_LoopField84 = items84[A_Index84 - 0];
        if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEnd)) {
            COUNT_programmingBlock_InTheTranspiledLang++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(COUNT_programmingBlock_InTheTranspiledLang) + "AA\n";
            HTVM_Append(programmingBlock_InTheTranspiledLang, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndCPP)) {
            COUNT_programmingBlock_CPP++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(COUNT_programmingBlock_CPP) + "AA\n";
            HTVM_Append(programmingBlock_CPP, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndPY)) {
            COUNT_programmingBlock_PY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_PY-programmingBlock_PY-AA" + STR(COUNT_programmingBlock_PY) + "AA\n";
            HTVM_Append(programmingBlock_PY, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndJS)) {
            COUNT_programmingBlock_JS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JS-programmingBlock_JS-AA" + STR(COUNT_programmingBlock_JS) + "AA\n";
            HTVM_Append(programmingBlock_JS, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndGO)) {
            COUNT_programmingBlock_GO++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GO-programmingBlock_GO-AA" + STR(COUNT_programmingBlock_GO) + "AA\n";
            HTVM_Append(programmingBlock_GO, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndLUA)) {
            COUNT_programmingBlock_LUA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(COUNT_programmingBlock_LUA) + "AA\n";
            HTVM_Append(programmingBlock_LUA, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndCS)) {
            COUNT_programmingBlock_CS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CS-programmingBlock_CS-AA" + STR(COUNT_programmingBlock_CS) + "AA\n";
            HTVM_Append(programmingBlock_CS, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndJAVA)) {
            COUNT_programmingBlock_JAVA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(COUNT_programmingBlock_JAVA) + "AA\n";
            HTVM_Append(programmingBlock_JAVA, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndKT)) {
            COUNT_programmingBlock_KT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_KT-programmingBlock_KT-AA" + STR(COUNT_programmingBlock_KT) + "AA\n";
            HTVM_Append(programmingBlock_KT, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndRB)) {
            COUNT_programmingBlock_RB++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_RB-programmingBlock_RB-AA" + STR(COUNT_programmingBlock_RB) + "AA\n";
            HTVM_Append(programmingBlock_RB, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndNIM)) {
            COUNT_programmingBlock_NIM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(COUNT_programmingBlock_NIM) + "AA\n";
            HTVM_Append(programmingBlock_NIM, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndAHK)) {
            COUNT_programmingBlock_AHK++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(COUNT_programmingBlock_AHK) + "AA\n";
            HTVM_Append(programmingBlock_AHK, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndSWIFT)) {
            COUNT_programmingBlock_SWIFT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(COUNT_programmingBlock_SWIFT) + "AA\n";
            HTVM_Append(programmingBlock_SWIFT, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndDART)) {
            COUNT_programmingBlock_DART++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_DART-programmingBlock_DART-AA" + STR(COUNT_programmingBlock_DART) + "AA\n";
            HTVM_Append(programmingBlock_DART, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndTS)) {
            COUNT_programmingBlock_TS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_TS-programmingBlock_TS-AA" + STR(COUNT_programmingBlock_TS) + "AA\n";
            HTVM_Append(programmingBlock_TS, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndGROOVY)) {
            COUNT_programmingBlock_GROOVY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(COUNT_programmingBlock_GROOVY) + "AA\n";
            HTVM_Append(programmingBlock_GROOVY, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangEndHTVM)) {
            COUNT_programmingBlock_HTVM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(COUNT_programmingBlock_HTVM) + "AA\n";
            HTVM_Append(programmingBlock_HTVM, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInHTVMend)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            COUNT_programmingBlock_HTVMsyntax++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(COUNT_programmingBlock_HTVMsyntax) + "AA\n";
            HTVM_Append(programmingBlock_HTVMsyntax, holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        }
        else if (inProgarmmingBlock == 1) {
            holdTempDataProgrammingBlockThenPutInArr += A_LoopField84 + Chr(10);
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStart)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartCPP)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartPY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartJS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartGO)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartLUA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartCS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartJAVA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartKT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartRB)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartNIM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartAHK)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartSWIFT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartDART)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartTS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartGROOVY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInTheTranspiledLangStartHTVM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField84)) == StrLower(keyWordCodeInHTVMstart)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        } else {
            programmingBlocksTemp += A_LoopField84 + Chr(10);
        }
    }
    code = StringTrimRight(programmingBlocksTemp, 1);
    //programmingBlock_InTheTranspiledLang
    //programmingBlock_CPP
    //programmingBlock_PY
    //programmingBlock_JS
    //programmingBlock_GO
    //programmingBlock_LUA
    //programmingBlock_CS
    //programmingBlock_JAVA
    //programmingBlock_KT
    //programmingBlock_RB
    //programmingBlock_NIM
    //programmingBlock_AHK
    //programmingBlock_SWIFT
    //programmingBlock_DART
    //programmingBlock_TS
    //programmingBlock_GROOVY
    //programmingBlock_HTVM
    //programmingBlock_HTVMsyntax
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    let lookIntoTheNextLineForFuncWhitNoKeyWord = [];
    var didWeUseMainLabel = 0;
    var codeOutFixAndAddMainFunc = "";
    var htCodeOutFixEnd = "";
    var htCodeOutFixINT = 0;
    var htCodeOutFixINT2 = 0;
    var beforeKeywordForRemoveCommentsOnTheEndOfTheLine = "";
    var newStringOutCode = "";
    var posForRemoveCommentsOnTheEndOfTheLine = 0;
    var originalStringForRemoveCommentsOnTheEndOfTheLine = "";
    var OutFixDoubleQuotesInsideDoubleQuotes = "";
    var fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
    var htCodeOUT754754 = "";
    var areWEinSome34sNum = 0;
    var theIdNumOfThe34 = 0;
    let theIdNumOfThe34theVar = [];
    var ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = "";
    let getAllCharForTheFurtureSoIcanAddEscapeChar = [];
    var removeNexFixkeyWordEscpaeChar = 0;
    if (isNotHTVMfile == 0) {
        //print("============programmingBlock_CPP==================")
        //print("============programmingBlock_CPP==================")
        if (HTVM_Size(programmingBlock_CPP) > 0) {
            for (let A_Index85 = 0; A_Index85 < HTVM_Size(programmingBlock_CPP) + 0; A_Index85++) {
                //print(programmingBlock_CPP[A_Index85])
            }
        }
        //print("============programmingBlock_CPP==================")
        //print("============programmingBlock_CPP==================")
        items86 = LoopParseFunc(code)
        for (let A_Index86 = 0; A_Index86 < items86.length + 0; A_Index86++) {
            const A_LoopField86 = items86[A_Index86 - 0];
            HTVM_Append(theIdNumOfThe34theVar, "");
            HTVM_Append(theIdNumOfThe34theVar, "");
        }
        items87 = LoopParseFunc(code)
        for (let A_Index87 = 0; A_Index87 < items87.length + 0; A_Index87++) {
            const A_LoopField87 = items87[A_Index87 - 0];
            theIdNumOfThe34theVar[A_Index87] = theIdNumOfThe34theVar[A_Index87] + Chr(34);
            HTVM_Append(getAllCharForTheFurtureSoIcanAddEscapeChar, A_LoopField87);
        }
        HTVM_Append(getAllCharForTheFurtureSoIcanAddEscapeChar, " ");
        ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuuhuuhtheidFor" + str21 + "--" + str21 + "asds" + str21 + "as--" + str21 + "theuhtuwaesphoutr" + Chr(34);
        items88 = LoopParseFunc(code)
        for (let A_Index88 = 0; A_Index88 < items88.length + 0; A_Index88++) {
            const A_LoopField88 = items88[A_Index88 - 0];
            if (A_LoopField88 == keyWordEscpaeChar && getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index88 + 1] == Chr(34)) {
                fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1;
                OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes;
            } else {
                if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1) {
                    OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField88;
                } else {
                    fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
                }
            }
        }
        code = OutFixDoubleQuotesInsideDoubleQuotes;
        if (keyWordEscpaeChar != Chr(92) && langToConvertTo != langFileExtension_2) {
            code = StrReplace(code, Chr(92), Chr(92) + Chr(92));
        }
        if (keyWordEscpaeChar == Chr(92) && langToConvertTo != langFileExtension_2) {
            items89 = LoopParseFunc(code)
            for (let A_Index89 = 0; A_Index89 < items89.length + 0; A_Index89++) {
                const A_LoopField89 = items89[A_Index89 - 0];
                if (A_LoopField89 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField89 != Chr(34)) {
                        if (A_LoopField89 == keyWordEscpaeChar && langToConvertTo != langFileExtension_2) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField89;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField89 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField89;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        } else {
            items90 = LoopParseFunc(code)
            for (let A_Index90 = 0; A_Index90 < items90.length + 0; A_Index90++) {
                const A_LoopField90 = items90[A_Index90 - 0];
                if (A_LoopField90 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField90 != Chr(34)) {
                        if (A_LoopField90 == keyWordEscpaeChar && keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index90 + 1] && langToConvertTo != langFileExtension_2) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar;
                            removeNexFixkeyWordEscpaeChar = 1;
                        }
                        else if (A_LoopField90 == keyWordEscpaeChar && langToConvertTo != langFileExtension_2) {
                            if (removeNexFixkeyWordEscpaeChar != 1) {
                                theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                            } else {
                                removeNexFixkeyWordEscpaeChar = 0;
                            }
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField90;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField90 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField90;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        }
        code = htCodeOUT754754;
        for (let A_Index91 = 0; A_Index91 < theIdNumOfThe34 + 0; A_Index91++) {
            theIdNumOfThe34theVar[A_Index91] = theIdNumOfThe34theVar[A_Index91] + Chr(34);
        }
        HTVM_Append(theIdNumOfThe34theVar, Chr(34));
        code = StrReplace(code, Chr(13), "");
        newStringOutCode = "";
        items92 = LoopParseFunc(code, "\n", "\r")
        for (let A_Index92 = 0; A_Index92 < items92.length + 0; A_Index92++) {
            const A_LoopField92 = items92[A_Index92 - 0];
            originalStringForRemoveCommentsOnTheEndOfTheLine = A_LoopField92;
            posForRemoveCommentsOnTheEndOfTheLine = InStr(originalStringForRemoveCommentsOnTheEndOfTheLine, " " + keyWordComment);
            if (posForRemoveCommentsOnTheEndOfTheLine > 0 && InStr(originalStringForRemoveCommentsOnTheEndOfTheLine, " " + keyWordComment)) {
                newStringOutCode += SubStr(A_LoopField92, 1, posForRemoveCommentsOnTheEndOfTheLine - 1) + Chr(10);
            } else {
                newStringOutCode += A_LoopField92 + Chr(10);
            }
        }
        code = StringTrimRight(newStringOutCode, 1);
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        if (langToConvertTo == langFileExtension_2) {
            if (useSemicolon_2 == "on") {
                theSemicolon = ";";
            } else {
                theSemicolon = "";
            }
            if (usePythonicColonSyntax_2 == "off") {
                theColon = "";
            } else {
                theColon = ":";
            }
        } else {
            if (langToConvertTo != "py" && langToConvertTo != "nim" && langToConvertTo != "ahk" && langToConvertTo != "go" && langToConvertTo != "lua" && langToConvertTo != "kt" && langToConvertTo != "rb" && langToConvertTo != "swift" && langToConvertTo != "groovy" && useSemicolon == "off") {
                theSemicolon = ";";
            } else {
                theSemicolon = "";
            }
            if (langToConvertTo != "py" && langToConvertTo != "nim" && usePythonicColonSyntax == "off") {
                theColon = "";
            } else {
                theColon = ":";
            }
        }
        if (useCurlyBraces == "on") {
            if (keyWordCurlyBraceOpen != "{") {
                items93 = LoopParseFunc(code, "\n", "\r")
                for (let A_Index93 = 0; A_Index93 < items93.length + 0; A_Index93++) {
                    const A_LoopField93 = items93[A_Index93 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField93)) == true || Trim(A_LoopField93) == keyWordCurlyBraceOpen) {
                        htCodeOutFixINT2 = 1;
                    }
                    htCodeOutFixINT = 0;
                    items94 = LoopParseFunc(A_LoopField93, " ")
                    for (let A_Index94 = 0; A_Index94 < items94.length + 0; A_Index94++) {
                        const A_LoopField94 = items94[A_Index94 - 0];
                        htCodeOutFixINT++;
                    }
                    htCodeOutFixINT--;
                    items95 = LoopParseFunc(A_LoopField93, " ")
                    for (let A_Index95 = 0; A_Index95 < items95.length + 0; A_Index95++) {
                        const A_LoopField95 = items95[A_Index95 - 0];
                        if (htCodeOutFixINT == A_Index95 && htCodeOutFixINT2 == 1) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField95, keyWordCurlyBraceOpen, "{") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField95 + " ";
                        }
                    }
                    htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1);
                    htCodeOutFixEnd += Chr(10);
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            htCodeOutFixEnd = "";
            if (keyWordCurlyBraceClose != "}") {
                items96 = LoopParseFunc(code, "\n", "\r")
                for (let A_Index96 = 0; A_Index96 < items96.length + 0; A_Index96++) {
                    const A_LoopField96 = items96[A_Index96 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField96)) == true || Trim(A_LoopField96) == keyWordCurlyBraceClose) {
                        htCodeOutFixINT2 = 1;
                    }
                    items97 = LoopParseFunc(A_LoopField96, " ")
                    for (let A_Index97 = 0; A_Index97 < items97.length + 0; A_Index97++) {
                        const A_LoopField97 = items97[A_Index97 - 0];
                        if (htCodeOutFixINT2 == 1 || Trim(A_LoopField97) == keyWordCurlyBraceClose) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField97, keyWordCurlyBraceClose, "}") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField97 + " ";
                        }
                    }
                    htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1);
                    htCodeOutFixEnd += Chr(10);
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        htCodeOutFixEnd = "";
        if (useEnd == "on") {
            items98 = LoopParseFunc(code, "\n", "\r")
            for (let A_Index98 = 0; A_Index98 < items98.length + 0; A_Index98++) {
                const A_LoopField98 = items98[A_Index98 - 0];
                if (StrLower(Trim(A_LoopField98)) == StrLower(keyWordEnd)) {
                    htCodeOutFixEnd += "}\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField98)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF) && isLineAconstruct(Trim(A_LoopField98)) == true) {
                    htCodeOutFixEnd += A_LoopField98 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField98)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop) && isLineAconstruct(Trim(A_LoopField98)) == true) {
                    htCodeOutFixEnd += A_LoopField98 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField98)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf) && isLineAconstruct(Trim(A_LoopField98)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField98 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField98)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse) && isLineAconstruct(Trim(A_LoopField98)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField98 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField98)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch) && isLineAconstruct(Trim(A_LoopField98)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField98 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField98)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally) && isLineAconstruct(Trim(A_LoopField98)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField98 + "\n{\n";
                }
                else if (isLineAconstruct(Trim(A_LoopField98)) == true) {
                    htCodeOutFixEnd += A_LoopField98 + "\n{\n";
                } else {
                    htCodeOutFixEnd += A_LoopField98 + Chr(10);
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        if (usePythonicColonSyntax == "off") {
            if (useEnd == "off" && useCurlyBraces == "off") {
                htCodeOutFixEnd = "";
                items99 = LoopParseFunc(code, "\n", "\r")
                for (let A_Index99 = 0; A_Index99 < items99.length + 0; A_Index99++) {
                    const A_LoopField99 = items99[A_Index99 - 0];
                    if (isLineAconstruct(Trim(A_LoopField99)) == true) {
                        htCodeOutFixEnd += A_LoopField99 + ":\n";
                    } else {
                        htCodeOutFixEnd += A_LoopField99 + Chr(10);
                    }
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
        }
        if (useCurlyBraces == "off" && useEnd == "off") {
            code = AddCurlyBraces(code);
        }
        outTrimCode = "";
        items100 = LoopParseFunc(code, "\n", "\r")
        for (let A_Index100 = 0; A_Index100 < items100.length + 0; A_Index100++) {
            const A_LoopField100 = items100[A_Index100 - 0];
            outTrimCode += Trim(A_LoopField100) + Chr(10);
        }
        code = StringTrimRight(outTrimCode, 1);
        // for converting c++ to js and py
        //code := StrReplace(code, "{}", "[]")
        var outCodeFixBraces = "";
        for (let A_Index101 = 0; A_Index101 < 2 + 0; A_Index101++) {
            outCodeFixBraces = "";
            items102 = LoopParseFunc(code, "\n", "\r")
            for (let A_Index102 = 0; A_Index102 < items102.length + 0; A_Index102++) {
                const A_LoopField102 = items102[A_Index102 - 0];
                if (InStr(A_LoopField102, " " + keyWordAssign + " ") || InStr(A_LoopField102, " " + keyWordAssignAdd + " ") || InStr(A_LoopField102, " " + keyWordAssignConcat + " ") || InStr(A_LoopField102, " " + keyWordAssignSub + " ") || InStr(A_LoopField102, " " + keyWordAssignMul + " ") || InStr(A_LoopField102, " " + keyWordAssignDiv + " ") || InStr(A_LoopField102, " " + keyWordAssignMod + " ") || InStr(A_LoopField102, " " + keyWordAssignShiftLeft + " ") || InStr(A_LoopField102, " " + keyWordAssignShiftRight + " ") || InStr(A_LoopField102, " " + keyWordLogicalAssignShiftRight + " ") || InStr(A_LoopField102, " " + keyWordAssignBitAnd + " ") || InStr(A_LoopField102, " " + keyWordAssignBitOr + " ") || InStr(A_LoopField102, " " + keyWordAssignBitXor + " ") && useCurlyBracesSyntaxForArrayDef == "on") {
                    if (SubStr(StrLower(A_LoopField102), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc) || SubStr(StrLower(A_LoopField102), 1, StrLen(StrLower(keyWordAsync) + StrLower(keyWordFunc))) == StrLower(keyWordAsync) + StrLower(keyWordFunc)) {
                        if (InStr(Trim(A_LoopField102), "{") && Trim(A_LoopField102) != "{") {
                            outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField102), "{", "")) + "\n{\n";
                        }
                        else if (InStr(Trim(A_LoopField102), "}") && Trim(A_LoopField102) != "}") {
                            outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField102), "}", "")) + Chr(10);
                        } else {
                            outCodeFixBraces += Trim(A_LoopField102) + Chr(10);
                        }
                    } else {
                        outCodeFixBraces += Trim(A_LoopField102) + Chr(10);
                    }
                } else {
                    if (InStr(Trim(A_LoopField102), "{") && Trim(A_LoopField102) != "{") {
                        outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField102), "{", "")) + "\n{\n";
                    }
                    else if (InStr(Trim(A_LoopField102), "}") && Trim(A_LoopField102) != "}") {
                        outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField102), "}", "")) + Chr(10);
                    } else {
                        outCodeFixBraces += Trim(A_LoopField102) + Chr(10);
                    }
                }
            }
            code = StringTrimRight(outCodeFixBraces, 1);
        }
        htCodeOutFixEnd = "";
        if (usePythonicColonSyntax == "on" || useCurlyBraces == "off" && useEnd == "off") {
            items103 = LoopParseFunc(code, "\n", "\r")
            for (let A_Index103 = 0; A_Index103 < items103.length + 0; A_Index103++) {
                const A_LoopField103 = items103[A_Index103 - 0];
                if (isLineAconstruct(Trim(A_LoopField103)) == true) {
                    htCodeOutFixEnd += StringTrimRight(A_LoopField103, 1) + Chr(10);
                } else {
                    htCodeOutFixEnd += A_LoopField103 + Chr(10);
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        //;; main loop
        //;; main loop
        //;; main loop
        //;; main loop
        fullLangAllOperators = GETfullLangAllOperators();
        fullLangAllOperators_HELP = GETfullLangAllOperators_HELP();
        if (isNotHTVMfile2 == 0) {
            items104 = LoopParseFunc(code, "\n", "\r")
            for (let A_Index104 = 0; A_Index104 < items104.length + 0; A_Index104++) {
                const A_LoopField104 = items104[A_Index104 - 0];
                if (StrLower(A_LoopField104) == StrLower(keyWordMainLabel)) {
                    didWeUseMainLabel = 1;
                    if (langToConvertTo == langFileExtension_2) {
                        codeOutFixAndAddMainFunc += keyWordMainLabel_2 + Chr(10);
                    }
                    if (langToConvertTo == "cpp") {
                        codeOutFixAndAddMainFunc += "int main(int argc, char* argv[])" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
                        codeOutFixAndAddMainFunc += "async function main()" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
                        codeOutFixAndAddMainFunc += "async function main(): Promise<void>" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "go") {
                        codeOutFixAndAddMainFunc += "func main()" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "cs") {
                        codeOutFixAndAddMainFunc += "static void Main(string[] args)" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "java") {
                        codeOutFixAndAddMainFunc += "public static void main(String[] args)" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "kt") {
                        codeOutFixAndAddMainFunc += "fun main(args: Array<String>)" + Chr(10) + "{" + Chr(10);
                    }
                    if (langToConvertTo == "swift") {
                        codeOutFixAndAddMainFunc += "func main()\n{\n";
                    }
                    if (langToConvertTo == "dart") {
                        codeOutFixAndAddMainFunc += "void main(List<String> arguments)" + Chr(10) + "{" + Chr(10);
                    }
                } else {
                    codeOutFixAndAddMainFunc += A_LoopField104 + Chr(10);
                }
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "cpp") {
                codeOutFixAndAddMainFunc = "int main(int argc, char* argv[])" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
                codeOutFixAndAddMainFunc = "async function main()" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
                codeOutFixAndAddMainFunc = "async function main(): Promise<void>" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "go") {
                codeOutFixAndAddMainFunc = "func main()" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "cs") {
                codeOutFixAndAddMainFunc = "static void Main(string[] args)" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "java") {
                codeOutFixAndAddMainFunc = "public static void main(String[] args)" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "kt") {
                codeOutFixAndAddMainFunc = "fun main(args: Array<String>)" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "swift") {
                codeOutFixAndAddMainFunc = "func main()" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "dart") {
                codeOutFixAndAddMainFunc = "void main(List<String> arguments)" + Chr(10) + "{" + Chr(10) + codeOutFixAndAddMainFunc;
            }
            code = StringTrimRight(codeOutFixAndAddMainFunc, 1);
            // main loop
            // main loop
        }
        items105 = LoopParseFunc(code, "\n", "\r")
        for (let A_Index105 = 0; A_Index105 < items105.length + 0; A_Index105++) {
            const A_LoopField105 = items105[A_Index105 - 0];
            HTVM_Append(lookIntoTheNextLineForFuncWhitNoKeyWord, A_LoopField105);
        }
        HTVM_Append(lookIntoTheNextLineForFuncWhitNoKeyWord, " ");
        htCode = "";
        //print("=======UP==========")
        //print(code)
        //print("=======DOWN==========")
        items106 = LoopParseFunc(code, "\n", "\r")
        for (let A_Index106 = 0; A_Index106 < items106.length + 0; A_Index106++) {
            const A_LoopField106 = items106[A_Index106 - 0];
            lineDone = 0;
            if (SubStr(A_LoopField106, 1, StrLen(keyWordComment)) == keyWordComment) {
                str1 = StringTrimLeft(A_LoopField106, StrLen(keyWordComment));
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordComment_2 + str1 + Chr(10);
                }
                if (langToConvertTo == "cpp") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "#" + str1 + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "--" + str1 + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "#" + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "#" + str1 + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += ";" + str1 + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "//" + str1 + Chr(10);
                }
            }
            else if (Trim(A_LoopField106) == keyWordCommentOpenMultiLine) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordCommentOpenMultiLine_2 + Chr(10);
                }
                if (langToConvertTo == "cpp") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += Chr(34) + Chr(34) + Chr(34) + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "--[[" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "=begin" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "#[" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "/*" + Chr(10);
                }
            }
            else if (Trim(A_LoopField106) == keyWordCommentCloseMultiLine) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordCommentCloseMultiLine_2 + Chr(10);
                }
                if (langToConvertTo == "cpp") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += Chr(34) + Chr(34) + Chr(34) + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "]]" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "=end" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "]#" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "*/" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField106)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF)) {
                str1 = Trim(StringTrimLeft(A_LoopField106, StrLen(keyWordIF)));
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"));
                str1 = StringTrimRight(str1, 1);
                str1 = StringTrimLeft(str1, 1);
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + str1 + ":" + Chr(10);
                            } else {
                                htCode += keyWordIF_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":" + Chr(10);
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + "(" + str1 + "):" + Chr(10);
                            } else {
                                htCode += keyWordIF_2 + str1 + ":" + Chr(10);
                            }
                        }
                    } else {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + str1 + Chr(10);
                            } else {
                                htCode += keyWordIF_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + Chr(10);
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + "(" + str1 + ")" + Chr(10);
                            } else {
                                htCode += keyWordIF_2 + str1 + Chr(10);
                            }
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "py") {
                    htCode += "if " + str1 + ":" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "go") {
                    htCode += "if " + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "if " + str1 + " then" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "java") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "kt") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "if " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "if " + str1 + ":" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "if " + str1 + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "if (" + str1 + ")" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField106)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf)) {
                str1 = Trim(StringTrimLeft(A_LoopField106, StrLen(keyWordElseIf)));
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"));
                str1 = StringTrimRight(str1, 1);
                str1 = StringTrimLeft(str1, 1);
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + str1 + ":\n";
                            } else {
                                htCode += keyWordElseIf_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":\n";
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + "(" + str1 + "):\n";
                            } else {
                                htCode += keyWordElseIf_2 + str1 + ":\n";
                            }
                        }
                    } else {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + str1 + Chr(10);
                            } else {
                                htCode += keyWordElseIf_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + Chr(10);
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + "(" + str1 + ")\n";
                            } else {
                                htCode += keyWordElseIf_2 + str1 + Chr(10);
                            }
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "py") {
                    htCode += "elif " + str1 + ":\n";
                }
                if (langToConvertTo == "js") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "go") {
                    htCode += "else if " + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "elseif " + str1 + " then\n";
                }
                if (langToConvertTo == "cs") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "java") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "kt") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "elsif " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "elif " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "else if " + str1 + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + Chr(10);
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "else if (" + str1 + ")" + Chr(10);
                }
            }
            else if (StrLower(Trim(A_LoopField106)) == StrLower(keyWordElse) || StrLower(Trim(A_LoopField106)) == StrLower(keyWordElse + ":")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordElse_2 + ":\n";
                    } else {
                        htCode += keyWordElse_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "else:\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "else:\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "else\n";
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField106)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)) {
                str1 = Trim(StringTrimLeft(A_LoopField106, StrLen(keyWordWhileLoop)));
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"));
                str1 = StringTrimRight(str1, 1);
                str1 = StringTrimLeft(str1, 1);
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordWhileLoop_2 + str1 + ":" + Chr(10);
                            } else {
                                htCode += keyWordWhileLoop_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":" + Chr(10);
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordWhileLoop_2 + "(" + str1 + "):" + Chr(10);
                            } else {
                                htCode += keyWordWhileLoop_2 + str1 + ":" + Chr(10);
                            }
                        }
                    } else {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordWhileLoop_2 + str1 + Chr(10);
                            } else {
                                htCode += keyWordWhileLoop_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + Chr(10);
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordWhileLoop_2 + "(" + str1 + ")" + Chr(10);
                            } else {
                                htCode += keyWordWhileLoop_2 + str1 + Chr(10);
                            }
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "py") {
                    htCode += "while " + str1 + ":" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "go") {
                    htCode += "for " + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "while " + str1 + " do" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "java") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "kt") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "while " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "while " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "while " + str1 + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "while (" + str1 + ")" +  Chr(10);
                }
            }
            else if (StrLower(Trim(A_LoopField106)) == StrLower(keyWordTry) || StrLower(Trim(A_LoopField106)) == StrLower(keyWordTry + ":")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordTry_2 + ":\n";
                    } else {
                        htCode += keyWordTry_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "try:\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "begin\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "try:\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "do\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "try\n";
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField106)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)) {
                str1 = Trim(StrReplace(StrReplace(StringTrimLeft(A_LoopField106, StrLen(keyWordCatch)), "(", ""), ")", ""));
                theTryCatchVarForErrors = str1;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordCatch_2 + "(" + str1 + "):\n";
                    } else {
                        htCode += keyWordCatch_2 + "(" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "catch (const std::exception& " + str1 + ")\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "except Exception as " + str1 + ":\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "catch (" + str1 + ")\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "catch (Exception " + str1 + ")\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "catch (Exception " + str1 + ")n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "catch (" + str1 + ": Exception)\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "rescue => " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "except ValueError as " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "catch " + str1 + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "catch let " + str1 + " as NSError\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "catch (" + str1 + ")\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "catch (" + str1 + ")\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "catch (Exception " + str1 + ")\n";
                }
            }
            else if (StrLower(Trim(A_LoopField106)) == StrLower(keyWordFinally) || StrLower(Trim(A_LoopField106)) == StrLower(keyWordFinally + ":")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordFinally_2 + ":\n";
                    } else {
                        htCode += keyWordFinally_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "if (" + Chr(34) + "finally dosent exist in c++" + Chr(34) + " == " + Chr(34) + "finally dosent exist in c++" + Chr(34) + ")\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "finally:\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "ensure\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "finally:\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "if (" + Chr(34) + "finally dosent exist in swift" + Chr(34) + " == " + Chr(34) + "finally dosent exist in swift" + Chr(34) + ")\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "finally\n";
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField106)), 1, StrLen(StrLower(keyWordThrow))) == StrLower(keyWordThrow)) {
                str1 = Trim(A_LoopField106);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str1 = expressionParserTranspiler(fixArray1234(Trim(StringTrimLeft(str1, StrLen(keyWordThrow)))));
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordThrow_2 + " " + keyWordErrorMsg_2 + "(" + str1 + ");\n";
                    } else {
                        htCode += keyWordThrow_2 + " " + keyWordErrorMsg_2 + "(" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "throw std::runtime_error(" + str1 + ");\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "raise Exception(" + str1 + ")\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "throw new Error(" + str1 + ");\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "throw new Exception(" + str1 + ");\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "throw new Exception(" + str1 + ");\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "throw Exception(" + str1 + ")" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "raise " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "raise newException(ValueError, " + str1 + ")\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "throw " + str1 + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "try ErrorMsg(" + str1 + ")\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "throw Exception(" + str1 + ");n";
                }
                if (langToConvertTo == "ts") {
                    htCode += " throw new Error(" + str1 + ");\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "throw new Exception(" + str1 + ")\n";
                }
            }
            else if (StrLower(A_LoopField106) == StrLower(keyWordBreak) || StrLower(A_LoopField106) == StrLower(keyWordBreak + ";")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordBreak_2 + ";\n";
                    } else {
                        htCode += keyWordBreak_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "break;\n";
                }
            }
            else if (StrLower(A_LoopField106) == StrLower(Trim(keyWordReturnStatement)) || StrLower(A_LoopField106) == StrLower(Trim(keyWordReturnStatement) + ";")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordReturnStatement_2 + ";\n";
                    } else {
                        htCode += keyWordReturnStatement_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "return;\n";
                }
            }
            else if (SubStr(Trim(StrLower(A_LoopField106)), 1, StrLen(StrLower(keyWordReturnStatement))) == StrLower(keyWordReturnStatement)) {
                str1 = Trim(expressionParserTranspiler(Trim(StringTrimLeft(A_LoopField106, StrLen(keyWordReturnStatement)))));
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordReturnStatement_2 + str1 + ";" + Chr(10);
                    } else {
                        htCode += keyWordReturnStatement_2 + str1 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "return " + str1 + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "return " + str1 + ";\n";
                }
            }
            else if (StrLower(A_LoopField106) == StrLower(keyWordContinue) || StrLower(A_LoopField106) == StrLower(keyWordContinue + ";")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordContinue_2 + ";\n";
                    } else {
                        htCode += keyWordContinue_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "goto continue" + STR(luaContinueFix_Num) + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "next\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "continue;\n";
                }
            }
            else if (StrLower(A_LoopField106) == "::" + keyWordContinue) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode += "::" + keyWordContinue_2 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "::continue" + STR(luaContinueFix_Num) + "::" + Chr(10);
                    luaContinueFix_Num++;
                }
            }
            else if (StrLower(A_LoopField106) == StrLower(keyWordLoopInfinite) || StrLower(A_LoopField106) == StrLower(keyWordLoopInfinite + ":")) {
                // infinity loops
                haveWeEverUsedAloop = 1;
                lineDone = 1;
                howMany_fixAindexInGoUnused++;
                if (langToConvertTo == "py") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , value in enumerate(iter(int, 1), start=" + AHKlikeLoopsIndexedAt + "):";
                }
                if (langToConvertTo == "js") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "cpp") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "go") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++";
                }
                if (langToConvertTo == "lua") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in infinite_HTVM_Lua_Loop_HTVM() do";
                }
                if (langToConvertTo == "cs") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in generateSequence(" + AHKlikeLoopsIndexedAt + ") { it + 1 })";
                }
                if (langToConvertTo == "rb") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..Float::INFINITY";
                }
                if (langToConvertTo == "nim") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in countup(" + AHKlikeLoopsIndexedAt + ", high(int)):";
                }
                if (langToConvertTo == "ahk") {
                    var1 = "Loop";
                }
                if (langToConvertTo == "swift") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "...";
                }
                if (langToConvertTo == "dart") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        var1 = keyWordLoopInfinite_2 + ":";
                    } else {
                        var1 = keyWordLoopInfinite_2;
                    }
                }
                nothing = "";
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
                htCodeAcurlyBraceAddSomeVrasFixNL = 1;
                lineDone = 1;
                if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + Chr(10);
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                htCode += htCodeLoopfixa1 + Chr(10) + var1 + Chr(10);
            }
            else if (SubStr(Trim(StrLower(A_LoopField106)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop) && SubStr(Trim(StrLower(A_LoopField106)), 1, StrLen(StrLower(keyWordLoop)) + 2) != StrLower(keyWordLoop) + "% " && SubStr(Trim(StrLower(A_LoopField106)), 1, StrLen(StrLower(keyWordLoopParse))) != StrLower(keyWordLoopParse)) {
                out2 = StringTrimLeft(A_LoopField106, StrLen(keyWordLoop));
                out2 = StrReplace(out2, ":", "");
                //MsgBox % out2
                howMany_fixAindexInGoUnused++;
                //MsgBox, % out2
                out2 = Trim(out2);
                myVar = out2;
                lineYGI = expressionParserTranspiler(myVar);
                line = lineYGI;
                haveWeEverUsedAloop = 1;
                //MsgBox, % line
                if (langToConvertTo == "py") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in range(" + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + "):";
                }
                if (langToConvertTo == "js") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "cpp") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "go") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++";
                }
                if (langToConvertTo == "lua") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + " + 1 " + ", " + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "cs") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " until " + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == "rb") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..." + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "nim") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..<" + line + " + " + AHKlikeLoopsIndexedAt + ":";
                }
                if (langToConvertTo == "ahk") {
                    var1 = "Loop, " + line;
                }
                if (langToConvertTo == "swift") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " ..< " + line + " + " + AHKlikeLoopsIndexedAt;
                }
                if (langToConvertTo == "dart") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..<" + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        var1 = Trim(keyWordLoop_2) + " " + line + ":";
                    } else {
                        var1 = Trim(keyWordLoop_2) + " " + line;
                    }
                }
                nothing = "";
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
                htCodeAcurlyBraceAddSomeVrasFixNL = 1;
                if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + Chr(10);
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                lineDone = 1;
                htCode += htCodeLoopfixa1 + Chr(10) + var1 + Chr(10);
            }
            else if (SubStr(Trim(StrLower(A_LoopField106)), 1, StrLen(StrLower(keyWordLoop)) + 2) == StrLower(keyWordLoop) + "% ") {
                howMany_fixAindexInGoUnused++;
                out2 = StringTrimLeft(A_LoopField106, StrLen(keyWordLoop) + 2);
                out2 = StrReplace(out2, ":", "");
                //MsgBox % out2
                //MsgBox, % out2
                out2 = Trim(out2);
                myVar = out2;
                lineYGI = expressionParserTranspiler(myVar);
                line = lineYGI;
                haveWeEverUsedAloop = 1;
                //MsgBox, % line
                if (langToConvertTo == "py") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in range(" + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + "):";
                }
                if (langToConvertTo == "js") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "cpp") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "go") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++";
                }
                if (langToConvertTo == "lua") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + " + 1 " + ", " + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "cs") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " until " + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == "rb") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..." + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "nim") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..<" + line + " + " + AHKlikeLoopsIndexedAt + ":";
                }
                if (langToConvertTo == "ahk") {
                    var1 = "Loop, % " + line;
                }
                if (langToConvertTo == "swift") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " ..< " + line + " + " + AHKlikeLoopsIndexedAt;
                }
                if (langToConvertTo == "dart") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..<" + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        var1 = Trim(keyWordLoop_2) + " % " + line + ":";
                    } else {
                        var1 = Trim(keyWordLoop_2) + " % " + line;
                    }
                }
                nothing = "";
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
                htCodeAcurlyBraceAddSomeVrasFixNL = 1;
                if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + Chr(10);
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                lineDone = 1;
                htCode += htCodeLoopfixa1 + Chr(10) + var1 + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField106), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
                howMany_fixAindexInGoUnused++;
                var1 = StringTrimLeft(A_LoopField106, StrLen(keyWordLoopParse));
                out2 = StrReplace(out2, ":", "");
                lineDone = 1;
                line1 = Trim(StrSplit(var1, ",", 1));
                line1 = expressionParserTranspiler(line1);
                line2 = "";
                line3 = "";
                itemsOut = "";
                line2 = Trim(StrSplit(var1, ",", 2));
                line3 = Trim(StrSplit(var1, ",", 3));
                if (InStr(var1, keyWordEscpaeChar + ",")) {
                    line2 = Chr(34) + "," + Chr(34);
                    if (langToConvertTo == "py") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "js") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "cpp") {
                        itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "go") {
                        itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ", " + Chr(34) + Chr(34) + ")";
                    }
                    if (langToConvertTo == "lua") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "cs") {
                        itemsOut = "List<string> items" + STR(AindexcharLength) + " = new List<string>(LoopParseFunc(" + line1 + ", " + line2 + "));";
                    }
                    if (langToConvertTo == "java") {
                        itemsOut = "String[] items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + Chr(34) + Chr(34) + ");";
                    }
                    if (langToConvertTo == "kt") {
                        itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "rb") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "nim") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "ahk") {
                        itemsOut = Chr(10);
                    }
                    if (langToConvertTo == "swift") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "dart") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "ts") {
                        itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "groovy") {
                        itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                } else {
                    if (line2 == "" && line3 == "") {
                        // nothing so only each char
                        if (langToConvertTo == "py" || langToConvertTo == "js") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "cpp") {
                            itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
                        }
                        if (langToConvertTo == "go") {
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + Chr(34) + Chr(34) + ", " + Chr(34) + Chr(34) + ")";
                        }
                        if (langToConvertTo == "lua") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "cs") {
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = new List<string>(LoopParseFunc(" + line1 + "));";
                        }
                        if (langToConvertTo == "java") {
                            itemsOut = "String[] items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + Chr(34) + Chr(34) + ", " + Chr(34) + Chr(34) + ");";
                        }
                        if (langToConvertTo == "kt") {
                            itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "nim") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "ahk") {
                            itemsOut = Chr(10);
                        }
                        if (langToConvertTo == "swift") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "dart") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
                        }
                        if (langToConvertTo == "ts") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
                        }
                        if (langToConvertTo == "groovy") {
                            itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                    }
                    if (line2 != "" && line3 == "") {
                        if (InStr(line2, keyWordEscpaeChar)) {
                            line2 = Chr(34) + line2 + Chr(34);
                        }
                        if (langToConvertTo == "py" || langToConvertTo == "js") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "cpp") {
                            itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                        }
                        if (langToConvertTo == "go") {
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ", " + Chr(34) + Chr(34) + ")";
                        }
                        if (langToConvertTo == "lua") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "cs") {
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = new List<string>(LoopParseFunc(" + line1 + ", " + line2 + "));";
                        }
                        if (langToConvertTo == "java") {
                            itemsOut = "String[] items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + Chr(34) + Chr(34) + ");";
                        }
                        if (langToConvertTo == "kt") {
                            itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "nim") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "ahk") {
                            itemsOut = Chr(10);
                        }
                        if (langToConvertTo == "swift") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "dart") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                        }
                        if (langToConvertTo == "ts") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "groovy") {
                            itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                    }
                    if (line2 != "" && line3 != "") {
                        if (InStr(line2, keyWordEscpaeChar)) {
                            line2 = Chr(34) + line2 + Chr(34);
                        }
                        if (InStr(line3, keyWordEscpaeChar)) {
                            line3 = Chr(34) + line3 + Chr(34);
                        }
                        if (langToConvertTo == "py" || langToConvertTo == "js") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "cpp") {
                            itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
                        }
                        if (langToConvertTo == "go") {
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "lua") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "cs") {
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = new List<string>(LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + "));";
                        }
                        if (langToConvertTo == "java") {
                            itemsOut = "String[] items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
                        }
                        if (langToConvertTo == "kt") {
                            itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "nim") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "ahk") {
                            itemsOut = Chr(10);
                        }
                        if (langToConvertTo == "swift") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "dart") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
                        }
                        if (langToConvertTo == "ts") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "groovy") {
                            itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                    }
                    itemsOut = StrReplace(itemsOut, keyWordEscpaeChar, Chr(92));
                }
                if (langToConvertTo == "py") {
                    var1out = itemsOut + Chr(10) + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in enumerate(items" + STR(AindexcharLength) + ", start=" + AHKlikeLoopsIndexedAt + "):";
                }
                if (langToConvertTo == "js") {
                    var1out = itemsOut + Chr(10) + "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "cpp") {
                    var1out = itemsOut + Chr(10) + "for (size_t " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".size() + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "go") {
                    var1out = itemsOut + Chr(10) + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " := range items" + STR(AindexcharLength);
                }
                if (langToConvertTo == "lua") {
                    var1out = itemsOut + Chr(10) + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in ipairs(items" + STR(AindexcharLength) + ") do";
                }
                if (langToConvertTo == "cs") {
                    var1out = itemsOut + Chr(10) + "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".Count + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1out = itemsOut + Chr(10) + "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1out = itemsOut + Chr(10) + "for ((" + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + ") in items" + STR(AindexcharLength) + ".withIndex())";
                }
                if (langToConvertTo == "rb") {
                    var1out = itemsOut + Chr(10) + "for HTVM----HTVM_FOR_hsdufosyigdydtddy_FOR_HTVM_Ruby_HTVM---HTVM-For_Ruby---AA items" + STR(AindexcharLength) + ".each_with_index do |" + keyWordALoopField + "" + STR(AindexcharLength) + " , " + keyWordAIndex + "" + STR(AindexcharLength) + "|";
                }
                if (langToConvertTo == "nim") {
                    var1out = itemsOut + Chr(10) + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + ":";
                }
                if (langToConvertTo == "ahk") {
                    if (Trim(line2) == "" && Trim(line3) == "") {
                        var1out = "Loop, Parse, " + line1;
                    }
                    if (Trim(line2) != "" && Trim(line3) == "") {
                        var1out = "Loop, Parse, " + line1 + ", " + StrReplace(StrReplace(line2, keyWordEscpaeChar, "\\"), Chr(34) + "," + Chr(34), Chr(34) + "\\," + Chr(34));
                    }
                    if (Trim(line2) != "" && Trim(line3) != "") {
                        var1out = "Loop, Parse, " + line1 + ", " + StrReplace(line2, keyWordEscpaeChar, "\\") + ", " + StrReplace(line3, keyWordEscpaeChar, "\\");
                    }
                }
                if (langToConvertTo == "swift") {
                    var1out = itemsOut + Chr(10) + "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + ") in items" + STR(AindexcharLength) + ".enumerated()";
                }
                if (langToConvertTo == "dart") {
                    var1out = itemsOut + Chr(10) + "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1out = itemsOut + Chr(10) + "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1out = itemsOut + Chr(10) + "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..<items" + STR(AindexcharLength) + ".size())";
                }
                nothing = "";
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
                //
                //
                theFixTextLoopLP = "";
                if (langToConvertTo == "cpp") {
                    theFixTextLoopLP = "std::string " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "js") {
                    theFixTextLoopLP = "const " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "go") {
                    theFixTextLoopLP = Chr(10);
                }
                if (langToConvertTo == "lua") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "cs") {
                    theFixTextLoopLP = "string " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "java") {
                    theFixTextLoopLP = "String " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "kt") {
                    theFixTextLoopLP = Chr(10);
                }
                if (langToConvertTo == "rb") {
                    theFixTextLoopLP = Chr(10);
                }
                if (langToConvertTo == "nim") {
                    theFixTextLoopLP = Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    theFixTextLoopLP = Chr(10);
                }
                if (langToConvertTo == "swift") {
                    theFixTextLoopLP = Chr(10);
                }
                if (langToConvertTo == "dart") {
                    theFixTextLoopLP = "var " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "ts") {
                    theFixTextLoopLP = "let " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "groovy") {
                    theFixTextLoopLP = "def " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                htCodeAcurlyBraceAddSomeVrasFixLP = 1;
                haveWeEverUsedAloop = 1;
                if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                    htCodeLoopfixa += "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + Chr(10);
                    htCodeLoopfixa1 = "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += Trim(keyWordLoopParse_2) + " " + StrReplace(var1, keyWordEscpaeChar, keyWordEscpaeChar_2) + ":\n";
                    } else {
                        htCode += Trim(keyWordLoopParse_2) + " " + StrReplace(var1, keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(10);
                    }
                } else {
                    htCode += htCodeLoopfixa1 + Chr(10) + var1out + Chr(10);
                }
            }
            else if (SubStrLastChars(Trim(A_LoopField106), StrLen(keyWordInc)) == keyWordInc || SubStrLastChars(Trim(A_LoopField106), StrLen(keyWordInc + ";")) == keyWordInc + ";" && lineDone == 0) {
                if (useSemicolon == "on") {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField106), StrLen(keyWordInc + ";")));
                } else {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField106), StrLen(keyWordInc)));
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += str1 + keyWordInc_2 + ";" + Chr(10);
                    } else {
                        htCode += str1 + keyWordInc_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += str1 + " += 1" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += str1 + " = " + str1 + " + 1" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += str1 + " += 1" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += str1 + " += 1" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += str1 + "++" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += str1 + " += 1" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += str1 + "++;" + Chr(10);
                }
            }
            else if (SubStrLastChars(Trim(A_LoopField106), StrLen(keyWordDec)) == keyWordDec || SubStrLastChars(Trim(A_LoopField106), StrLen(keyWordDec + ";")) == keyWordDec + ";" && lineDone == 0) {
                if (useSemicolon == "on") {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField106), StrLen(keyWordDec + ";")));
                } else {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField106), StrLen(keyWordDec)));
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += str1 + keyWordDec_2 + ";" + Chr(10);
                    } else {
                        htCode += str1 + keyWordDec_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += str1 + " -= 1" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += str1 + " = " + str1 + " - 1\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += str1 + " -= 1" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += str1 + " -= 1" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += str1 + "--" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += str1 + " -= 1" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += str1 + "--;" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField106)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ") && langToConvertTo == langFileExtension_2) {
                htCode += keyWordInclude_2 + " " + Trim(StringTrimLeft(Trim(A_LoopField106), StrLen(StrLower(keyWordInclude) + " "))) + Chr(10);
            }
            else if (StrLower(A_LoopField106) == StrLower(keyWordGlobal) || StrLower(A_LoopField106) == StrLower(keyWordGlobal + ";")) {
                if (langToConvertTo == "ahk") {
                    htCode += "global\n";
                }
            }
            else if (SubStr(StrLower(A_LoopField106), 1, StrLen(StrLower(keyWordAwait))) == StrLower(keyWordAwait)) {
                str1 = StringTrimLeft(A_LoopField106, StrLen(keyWordAwait));
                //MsgBox, % A_LoopField106
                lineDone = 1;
                fixExpertionLineFuncOnly = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        str2 = expressionParserTranspiler(Trim(str1)) + ";";
                    } else {
                        str2 = expressionParserTranspiler(Trim(str1));
                    }
                } else {
                    if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "groovy") {
                        if (SubStrLastChars(str1, 1) == ";") {
                            str1 = StringTrimRight(str1, 1);
                        }
                    }
                    str2 = expressionParserTranspiler(Trim(str1)) + ";";
                    if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "groovy") {
                        if (SubStrLastChars(str2, 1) == ";") {
                            str2 = StringTrimRight(str2, 1);
                        }
                    }
                }
                fixExpertionLineFuncOnly = 0;
                if (langToConvertTo == "js" || langToConvertTo == "ts" || langToConvertTo == langFileExtension_2) {
                    if (langToConvertTo == langFileExtension_2) {
                        htCode += keyWordAwait_2 + str2 + Chr(10);
                    } else {
                        htCode += "await " + str2 + Chr(10);
                    }
                } else {
                    htCode += str2 + Chr(10);
                }
            }
            else if (SubStr(StrLower(A_LoopField106), 1, StrLen(StrLower(keyWordGlobal))) == StrLower(keyWordGlobal)) {
                str1 = StringTrimLeft(A_LoopField106, StrLen(keyWordGlobal));
                //MsgBox, % A_LoopField106
                str1 = StrReplace(str1, ";", "");
                lineDone = 1;
                if (langToConvertTo == "py" || langToConvertTo == "ahk") {
                    str2 = "global " + str1;
                } else {
                    str2 = "";
                }
                htCode += str2 + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField106), 1, StrLen(keyWordFunc)) == StrLower(keyWordFunc) || SubStr(StrLower(A_LoopField106), 1, StrLen(StrLower(keyWordAsync) + StrLower(keyWordFunc))) == StrLower(keyWordAsync) + StrLower(keyWordFunc) && InStr(StrLower(A_LoopField106), " main(") == false && lineDone == 0) {
                lineDone = 1;
                if (SubStr(StrLower(A_LoopField106), 1, StrLen(StrLower(keyWordAsync) + StrLower(keyWordFunc))) == StrLower(keyWordAsync) + StrLower(keyWordFunc)) {
                    // is async
                    int1 = 1;
                    str1 = Trim(StringTrimLeft(A_LoopField106, StrLen(StrLower(keyWordAsync + keyWordFunc))));
                } else {
                    // is async
                    int1 = 0;
                    str1 = Trim(StringTrimLeft(A_LoopField106, StrLen(StrLower(keyWordFunc))));
                }
                if (usePrefixTypeForTypeDefinition == "on") {
                    str2 = Trim(StrSplit(str1, "(", 1));
                    // func body
                    str1 = Trim(StringTrimLeft(str1, StrLen(str2)));
                    str1 = StringTrimRight(str1, 1);
                    // type of the func
                    str3 = Trim(StringTrimRight(str2, StrLen(StrSplit(str2, " ", countChars(str2, " ") + 1))));
                    // name of func
                    str2 = Trim(StrSplit(str2, " ", countChars(str2, " ") + 1));
                }
                if (usePostfixTypeForTypeDefinition == "on") {
                    // name of func
                    str2 = Trim(StrSplit(str1, "(", 1));
                    // func body
                    str1 = Trim(StringTrimLeft(str1, StrLen(str2)));
                    // type of the func
                    str3 = Trim(StrSplit(str1, ")", countChars(str1, ")") + 1));
                    str3 = StringTrimLeft(str3, 1);
                    str1 = Trim(StringTrimRight(str1, StrLen(str3) + 2));
                }
                str1 = StringTrimLeft(str1, 1);
                str3 = Trim(str3);
                if (Trim(str1) == "") {
                    if (langToConvertTo == langFileExtension_2) {
                        if (int1 == 1) {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                htCode += keyWordAsync_2 + keyWordFunc_2 + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                            } else {
                                htCode += keyWordAsync_2 + keyWordFunc_2 + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                htCode += keyWordFunc_2 + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                            } else {
                                htCode += keyWordFunc_2 + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "py") {
                        htCode += "def " + str2 + "():" + Chr(10);
                    }
                    if (langToConvertTo == "js") {
                        if (int1 == 1) {
                            htCode += "async function " + str2 + "()" + Chr(10);
                        } else {
                            htCode += "function " + str2 + "()" + Chr(10);
                        }
                    }
                    // Go
                    if (langToConvertTo == "go") {
                        if (str3 == keyWordVoid) {
                            htCode += "func " + str2 + "()" + Chr(10);
                        } else {
                            htCode += "func " + str2 + "() " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "lua") {
                        htCode += "function " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "cs") {
                        htCode += "static " + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "java") {
                        htCode += "public static " + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "kt") {
                        if (str3 == keyWordVoid) {
                            htCode += "fun " + str2 + "()" + Chr(10);
                        } else {
                            htCode += "fun " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "rb") {
                        htCode += "def " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == keyWordVoid) {
                            htCode += "proc " + str2 + "() =" + Chr(10);
                        } else {
                            htCode += "proc " + str2 + "(): " + getFuncTypeConvert(str3) + " =" + Chr(10);
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        htCode += str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == keyWordVoid) {
                            htCode += "func " + str2 + "()" + Chr(10);
                        } else {
                            htCode += "func " + str2 + "() -> " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "dart") {
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "ts") {
                        htCode += "function " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                    }
                    if (langToConvertTo == "groovy") {
                        htCode += "def " + str2 + "()" + Chr(10);
                    }
                } else {
                    str5 = "";
                    str6 = "";
                    str7 = "";
                    str8 = "";
                    str9 = "";
                    str10 = "";
                    str11 = "";
                    str12 = "";
                    str13 = "";
                    str14 = "";
                    str15 = "";
                    str16 = "";
                    str17 = "";
                    str18 = "";
                    str19 = "";
                    str20 = "";
                    items107 = LoopParseFunc(str1, ",");
                    for (let A_Index107 = 0; A_Index107 < items107.length + 0; A_Index107++) {
                        const A_LoopField107 = items107[A_Index107 - 0];
                        //print("|" . Trim(A_LoopField107) . "|")
                        if (InStr(Trim(A_LoopField107), " ")) {
                            // there is space aka there is a type
                            if (InStr(A_LoopField107, " " + Trim(keyWordAssign) + " ") == false) {
                                if (usePrefixTypeForTypeDefinition == "on") {
                                    // normal
                                    str6 = Trim(A_LoopField107);
                                    str7 = getTheLastWord(str6);
                                    str8 = getFuncTypeConvert(Trim(StringTrimRight(str6, StrLen(Trim(str7)) + 1)));
                                    // str5 .= str8 . " " . str7 . Chr(10)
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    // save to str5
                                    // str8 = the type
                                    // str7 = variable name
                                    if (langToConvertTo == langFileExtension_2) {
                                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                                            str5 += str8 + " " + str7 + Chr(10);
                                        } else {
                                            str5 += str7 + ": " + str8 + Chr(10);
                                        }
                                    }
                                    if (langToConvertTo == "cpp") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "py") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "js") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "go") {
                                        str5 += str7 + " " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "lua") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "cs") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "java") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "kt") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "rb") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "nim") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "ahk") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "swift") {
                                        str5 += "_ " + str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "dart") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "ts") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "groovy") {
                                        str5 += str7 + Chr(10);
                                    }
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                } else {
                                    // not normal
                                    str6 = Trim(A_LoopField107);
                                    str7 = Trim(StrSplit(str6, ":", 1));
                                    str8 = getFuncTypeConvert(Trim(StrSplit(str6, ":", 2)));
                                    // str5 .= str7 . " :" . str8 . Chr(10)
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    // save to str5
                                    // str8 = the type
                                    // str7 = variable name
                                    if (langToConvertTo == langFileExtension_2) {
                                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                                            str5 += str8 + " " + str7 + Chr(10);
                                        } else {
                                            str5 += str7 + ": " + str8 + Chr(10);
                                        }
                                    }
                                    if (langToConvertTo == "cpp") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "py") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "js") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "go") {
                                        str5 += str7 + " " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "lua") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "cs") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "java") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "kt") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "rb") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "nim") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "ahk") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "swift") {
                                        str5 += "_ " + str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "dart") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "ts") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "groovy") {
                                        str5 += str7 + Chr(10);
                                    }
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                }
                            } else {
                                // optanal param
                                if (InStr(Trim(StrSplit(Trim(A_LoopField107), " " + Trim(keyWordAssign) + " ", 1)), " ")) {
                                    // there is a type
                                    if (usePrefixTypeForTypeDefinition == "on") {
                                        // normal
                                        str6 = Trim(StrSplit(Trim(A_LoopField107), " " + Trim(keyWordAssign) + " ", 1));
                                        str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField107), " " + Trim(keyWordAssign) + " ", 2))));
                                        str7 = getTheLastWord(str6);
                                        str8 = getFuncTypeConvert(Trim(StringTrimRight(str6, StrLen(Trim(str7)) + 1)));
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;; optanal param
                                        // save to str10
                                        // str8 = the type
                                        // str7 = variable name
                                        // str9 = after the keyWordAssign
                                        if (langToConvertTo == langFileExtension_2) {
                                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                                str10 += str8 + " " + str7 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                            } else {
                                                str10 += str7 + ": " + str8 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                            }
                                        }
                                        if (langToConvertTo == "cpp") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "py") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "js") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "go") {
                                            skipLeftCuleyForFuncPLS = 1;
                                            str10 += str7 + " " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "lua") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "cs") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "java") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "kt") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "rb") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "nim") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "ahk") {
                                            str10 += str7 + " := " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "swift") {
                                            str10 += "_ " + str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "dart") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "ts") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "groovy") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        // str10
                                        // skipLeftCuleyForFuncPLS := 1
                                    } else {
                                        // not normal
                                        str6 = Trim(StrSplit(Trim(A_LoopField107), " " + Trim(keyWordAssign) + " ", 1));
                                        str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField107), " " + Trim(keyWordAssign) + " ", 2))));
                                        str7 = Trim(StrSplit(str6, ":", 1));
                                        str8 = getFuncTypeConvert(Trim(StrSplit(str6, ":", 2)));
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;; optanal param
                                        // save to str10
                                        // str8 = the type
                                        // str7 = variable name
                                        // str9 = after the keyWordAssign
                                        if (langToConvertTo == langFileExtension_2) {
                                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                                str10 += str8 + " " + str7 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                            } else {
                                                str10 += str7 + ": " + str8 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                            }
                                        }
                                        if (langToConvertTo == "cpp") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "py") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "js") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "go") {
                                            skipLeftCuleyForFuncPLS = 1;
                                            str10 += str7 + " " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "lua") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "cs") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "java") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "kt") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "rb") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "nim") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "ahk") {
                                            str10 += str7 + " := " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "swift") {
                                            str10 += "_ " + str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "dart") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "ts") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "groovy") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        // str10
                                        // skipLeftCuleyForFuncPLS := 1
                                    }
                                } else {
                                    // there is no type
                                    str8 = Trim(StrSplit(Trim(A_LoopField107), " " + Trim(keyWordAssign) + " ", 1));
                                    str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField107), " " + Trim(keyWordAssign) + " ", 2))));
                                    // str10
                                    // skipLeftCuleyForFuncPLS := 1
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;; optanal param
                                    // save to str10
                                    // str8 = variable name
                                    // str9 = after the keyWordAssign
                                    if (langToConvertTo == langFileExtension_2) {
                                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                                            str10 += str7 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                        } else {
                                            str10 += str7 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                        }
                                    }
                                    if (langToConvertTo == "py") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                    }
                                    if (langToConvertTo == "js") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                    }
                                    if (langToConvertTo == "lua") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                        skipLeftCuleyForFuncPLS = 1;
                                    }
                                    if (langToConvertTo == "rb") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                    }
                                    if (langToConvertTo == "ahk") {
                                        str10 += str7 + " := " + str9 + Chr(10);
                                    }
                                    if (langToConvertTo == "groovy") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                    }
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                }
                            }
                        } else {
                            str5 += Trim(A_LoopField107) + Chr(10);
                        }
                    }
                    //print(str5)
                    //print(str10)
                    if (Trim(str5) != "") {
                        str5 = StringTrimRight(str5, 1);
                    }
                    if (Trim(str10) != "") {
                        str10 = StringTrimRight(str10, 1);
                    }
                    str5 = Trim(str5);
                    str10 = Trim(str10);
                    if (Trim(str5) != "" && Trim(str10) != "") {
                        items108 = LoopParseFunc(str5, "\n", "\r")
                        for (let A_Index108 = 0; A_Index108 < items108.length + 0; A_Index108++) {
                            const A_LoopField108 = items108[A_Index108 - 0];
                            str11 += A_LoopField108 + ", ";
                        }
                        items109 = LoopParseFunc(str10, "\n", "\r")
                        for (let A_Index109 = 0; A_Index109 < items109.length + 0; A_Index109++) {
                            const A_LoopField109 = items109[A_Index109 - 0];
                            str12 += A_LoopField109 + ", ";
                        }
                        str12 = StringTrimRight(str12, 2);
                        if (langToConvertTo == "dart") {
                            str12 = "[" + str12 + "]";
                        }
                        if (langToConvertTo == "lua") {
                            items110 = LoopParseFunc(str12, ",");
                            for (let A_Index110 = 0; A_Index110 < items110.length + 0; A_Index110++) {
                                const A_LoopField110 = items110[A_Index110 - 0];
                                str14 += Trim(StrSplit(Trim(A_LoopField110), " = ", 1)) + ", ";
                            }
                            str14 = StringTrimRight(str14, 2);
                            str13 += "{" + Chr(10);
                            items111 = LoopParseFunc(str12, ",");
                            for (let A_Index111 = 0; A_Index111 < items111.length + 0; A_Index111++) {
                                const A_LoopField111 = items111[A_Index111 - 0];
                                str13 += Trim(StrSplit(Trim(A_LoopField111), " = ", 1)) + " = " + Trim(StrSplit(Trim(A_LoopField111), " = ", 1)) + " or " + Trim(StrSplit(Trim(A_LoopField111), " = ", 2)) + Chr(10);
                            }
                            str12 = str14;
                        }
                        if (langToConvertTo == "go") {
                            str14 = "__HTVM_V2_TO_GO_optionalParams__ ...interface{}";
                            str13 += "{" + Chr(10) + " ";
                            items112 = LoopParseFunc(str12, ",");
                            for (let A_Index112 = 0; A_Index112 < items112.length + 0; A_Index112++) {
                                const A_LoopField112 = items112[A_Index112 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField112), " = ", 1)), " ", 1));
                                str17 = Trim(StrSplit(Trim(A_LoopField112), " = ", 2));
                                str13 += str16 + " := " + str17 + Chr(10);
                            }
                            items113 = LoopParseFunc(str12, ",");
                            for (let A_Index113 = 0; A_Index113 < items113.length + 0; A_Index113++) {
                                const A_LoopField113 = items113[A_Index113 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField113), " = ", 1)), " ", 1));
                                str18 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField113), " = ", 1)), " ", 2));
                                // str16 = var name
                                // str18 = var type
                                str13 += "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " " + STR(A_Index113) + Chr(10) + "{" + Chr(10) + str16 + " = __HTVM_V2_TO_GO_optionalParams__[" + STR(A_Index113) + "].(" + str18 + ")" + Chr(10) + "}" + Chr(10);
                            }
                            str12 = str14;
                        }
                        if (langToConvertTo == "java") {
                            str14 = "Object... __HTVM_V2_TO_JAVA_optionalParams__";
                            str13 += "{" + Chr(10);
                            items114 = LoopParseFunc(str12, ",");
                            for (let A_Index114 = 0; A_Index114 < items114.length + 0; A_Index114++) {
                                const A_LoopField114 = items114[A_Index114 - 0];
                                str13 += Trim(A_LoopField114) + ";" + Chr(10);
                            }
                            items115 = LoopParseFunc(str12, ",");
                            for (let A_Index115 = 0; A_Index115 < items115.length + 0; A_Index115++) {
                                const A_LoopField115 = items115[A_Index115 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField115), " = ", 1)), " ", 2));
                                str17 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField115), " = ", 1)), " ", 1));
                                // str16 = var name
                                // str17 = type name
                                str13 += "if (__HTVM_V2_TO_JAVA_optionalParams__.length " + Chr(62) + " " + STR(A_Index115) + ") " + str16 + " = (" + str17 + ") __HTVM_V2_TO_JAVA_optionalParams__[" + STR(A_Index115) + "];" + Chr(10);
                            }
                            str12 = str14;
                        }
                        str11 += str12;
                    }
                    if (Trim(str5) != "" && Trim(str10) == "") {
                        items116 = LoopParseFunc(str5, "\n", "\r")
                        for (let A_Index116 = 0; A_Index116 < items116.length + 0; A_Index116++) {
                            const A_LoopField116 = items116[A_Index116 - 0];
                            str11 += A_LoopField116 + ", ";
                        }
                        str11 = StringTrimRight(str11, 2);
                    }
                    if (Trim(str5) == "" && Trim(str10) != "") {
                        items117 = LoopParseFunc(str10, "\n", "\r")
                        for (let A_Index117 = 0; A_Index117 < items117.length + 0; A_Index117++) {
                            const A_LoopField117 = items117[A_Index117 - 0];
                            str11 += A_LoopField117 + ", ";
                        }
                        str11 = StringTrimRight(str11, 2);
                        if (langToConvertTo == "dart") {
                            str11 = "[" + str11 + "]";
                        }
                        if (langToConvertTo == "lua") {
                            items118 = LoopParseFunc(str11, ",");
                            for (let A_Index118 = 0; A_Index118 < items118.length + 0; A_Index118++) {
                                const A_LoopField118 = items118[A_Index118 - 0];
                                str14 += Trim(StrSplit(Trim(A_LoopField118), " = ", 1)) + ", ";
                            }
                            str14 = StringTrimRight(str14, 2);
                            str13 += "{" + Chr(10);
                            items119 = LoopParseFunc(str11, ",");
                            for (let A_Index119 = 0; A_Index119 < items119.length + 0; A_Index119++) {
                                const A_LoopField119 = items119[A_Index119 - 0];
                                str13 += Trim(StrSplit(Trim(A_LoopField119), " = ", 1)) + " = " + Trim(StrSplit(Trim(A_LoopField119), " = ", 1)) + " or " + Trim(StrSplit(Trim(A_LoopField119), " = ", 2)) + Chr(10);
                            }
                            str11 = str14;
                        }
                        if (langToConvertTo == "go") {
                            str14 = "__HTVM_V2_TO_GO_optionalParams__ ...interface{}";
                            str13 += "{" + Chr(10) + " ";
                            items120 = LoopParseFunc(str11, ",");
                            for (let A_Index120 = 0; A_Index120 < items120.length + 0; A_Index120++) {
                                const A_LoopField120 = items120[A_Index120 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField120), " = ", 1)), " ", 1));
                                str17 = Trim(StrSplit(Trim(A_LoopField120), " = ", 2));
                                str13 += str16 + " := " + str17 + Chr(10);
                            }
                            items121 = LoopParseFunc(str11, ",");
                            for (let A_Index121 = 0; A_Index121 < items121.length + 0; A_Index121++) {
                                const A_LoopField121 = items121[A_Index121 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField121), " = ", 1)), " ", 1));
                                str18 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField121), " = ", 1)), " ", 2));
                                // str16 = var name
                                // str18 = var type
                                str13 += "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " " + STR(A_Index121) + Chr(10) + "{" + Chr(10) + str16 + " = __HTVM_V2_TO_GO_optionalParams__[" + STR(A_Index121) + "].(" + str18 + ")" + Chr(10) + "}" + Chr(10);
                            }
                            str11 = str14;
                        }
                        if (langToConvertTo == "java") {
                            str14 = "Object... __HTVM_V2_TO_JAVA_optionalParams__";
                            str13 += "{" + Chr(10);
                            items122 = LoopParseFunc(str11, ",");
                            for (let A_Index122 = 0; A_Index122 < items122.length + 0; A_Index122++) {
                                const A_LoopField122 = items122[A_Index122 - 0];
                                str13 += Trim(A_LoopField122) + ";" + Chr(10);
                            }
                            items123 = LoopParseFunc(str11, ",");
                            for (let A_Index123 = 0; A_Index123 < items123.length + 0; A_Index123++) {
                                const A_LoopField123 = items123[A_Index123 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField123), " = ", 1)), " ", 2));
                                str17 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField123), " = ", 1)), " ", 1));
                                // str16 = var name
                                // str17 = type name
                                str13 += "if (__HTVM_V2_TO_JAVA_optionalParams__.length " + Chr(62) + " " + STR(A_Index123) + ") " + str16 + " = (" + str17 + ") __HTVM_V2_TO_JAVA_optionalParams__[" + STR(A_Index123) + "];" + Chr(10);
                            }
                            str11 = str14;
                        }
                    }
                    //print(str11)
                    //;;;;;;; last put all
                    //;;;;;;; last put all
                    //;;;;;;; last put all
                    if (langToConvertTo == langFileExtension_2) {
                        if (int1 == 1) {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                htCode += keyWordAsync_2 + keyWordFunc_2 + getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                            } else {
                                htCode += keyWordAsync_2 + keyWordFunc_2 + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                htCode += keyWordFunc_2 + getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                            } else {
                                htCode += keyWordFunc_2 + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "py") {
                        htCode += "def " + str2 + "(" + str11 + "):" + Chr(10);
                    }
                    if (langToConvertTo == "js") {
                        if (int1 == 1) {
                            htCode += "async function " + str2 + "(" + str11 + ")" + Chr(10);
                        } else {
                            htCode += "function " + str2 + "(" + str11 + ")" + Chr(10);
                        }
                    }
                    // Go
                    if (langToConvertTo == "go") {
                        if (str3 == keyWordVoid) {
                            htCode += "func " + str2 + "(" + str11 + ")" + Chr(10) + str13;
                        } else {
                            htCode += "func " + str2 + "(" + str11 + ") " + getFuncTypeConvert(str3) + Chr(10) + str13;
                        }
                    }
                    if (langToConvertTo == "lua") {
                        htCode += "function " + str2 + "(" + str11 + ")" + Chr(10) + str13;
                    }
                    if (langToConvertTo == "cs") {
                        htCode += "static " + getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "java") {
                        htCode += "public static " + getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10) + str13;
                    }
                    if (langToConvertTo == "kt") {
                        if (str3 == keyWordVoid) {
                            htCode += "fun " + str2 + "(" + str11 + ")" + Chr(10);
                        } else {
                            htCode += "fun " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "rb") {
                        htCode += "def " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == keyWordVoid) {
                            htCode += "proc " + str2 + "(" + str11 + ") =" + Chr(10);
                        } else {
                            htCode += "proc " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + " =" + Chr(10);
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        htCode += str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == keyWordVoid) {
                            htCode += "func " + str2 + "(" + str11 + ")" + Chr(10);
                        } else {
                            htCode += "func " + str2 + "(" + str11 + ") -> " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "dart") {
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "ts") {
                        htCode += "function " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                    }
                    if (langToConvertTo == "groovy") {
                        htCode += "def " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    //;;;;;;; last put all
                    //;;;;;;; last put all
                    //;;;;;;; last put all
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode = StringTrimRight(htCode, 1);
                        htCode += ":" + Chr(10);
                    }
                }
            }
            else if (InStr(StrLower(A_LoopField106), " main(") && lineDone == 0) {
                lineDone = 1;
                javaMainFuncSeen = 1;
                csMainFuncSeen = 1;
                htCode += A_LoopField106 + Chr(10);
            }
            else if (InStr(A_LoopField106, " " + keyWordAssign + " ") || InStr(A_LoopField106, " " + keyWordAssignAdd + " ") || InStr(A_LoopField106, " " + keyWordAssignConcat + " ") || InStr(A_LoopField106, " " + keyWordAssignSub + " ") || InStr(A_LoopField106, " " + keyWordAssignMul + " ") || InStr(A_LoopField106, " " + keyWordAssignDiv + " ") || InStr(A_LoopField106, " " + keyWordAssignMod + " ") || InStr(A_LoopField106, " " + keyWordAssignShiftLeft + " ") || InStr(A_LoopField106, " " + keyWordAssignShiftRight + " ") || InStr(A_LoopField106, " " + keyWordLogicalAssignShiftRight + " ") || InStr(A_LoopField106, " " + keyWordAssignBitAnd + " ") || InStr(A_LoopField106, " " + keyWordAssignBitOr + " ") || InStr(A_LoopField106, " " + keyWordAssignBitXor + " ") && lineDone == 0) {
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                //keyWordAssign
                //keyWordAssignAdd
                //keyWordAssignConcat
                //keyWordAssignSub
                //keyWordAssignMul
                //keyWordAssignDiv
                //keyWordAssignMod
                //keyWordAssignShiftLeft
                //keyWordAssignShiftRight
                //keyWordLogicalAssignShiftRight
                //keyWordAssignBitAnd
                //keyWordAssignBitOr
                //keyWordAssignBitXor
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //allVarsSoWeDontReDecVars
                //allVarsSoWeDontReDecVars_FIX_uint8
                //allVarsSoWeDontReDecVars_FIX_uint16
                //allVarsSoWeDontReDecVars_FIX_uint32
                //allVarsSoWeDontReDecVars_FIX_uint64
                //allVarsSoWeDontReDecVars_FIX_int64
                //allVarsSoWeDontReDecVars_FIX_float
                if (InStr(A_LoopField106, " " + keyWordAssign + " ")) {
                    str1 = StrSplit(A_LoopField106, " " + keyWordAssign + " ", 1);
                    str6 = StrSplit(A_LoopField106, " " + keyWordAssign + " ", 2);
                    str10 = keyWordAssign;
                    str11 = keyWordAssign_2;
                    if (langToConvertTo == "ahk") {
                        str12 = ":=";
                    } else {
                        str12 = "=";
                    }
                }
                else if (InStr(A_LoopField106, " " + keyWordAssignAdd + " ")) {
                    str1 = StrSplit(A_LoopField106, " " + keyWordAssignAdd + " ", 1);
                    str6 = StrSplit(A_LoopField106, " " + keyWordAssignAdd + " ", 2);
                    str10 = keyWordAssignAdd;
                    str11 = keyWordAssignAdd_2;
                    str12 = "+=";
                }
                else if (InStr(A_LoopField106, " " + keyWordAssignConcat + " ")) {
                    str1 = StrSplit(A_LoopField106, " " + keyWordAssignConcat + " ", 1);
                    str6 = StrSplit(A_LoopField106, " " + keyWordAssignConcat + " ", 2);
                    str10 = keyWordAssignConcat;
                    str11 = keyWordAssignConcat_2;
                    if (langToConvertTo == "ahk") {
                        str12 = ".=";
                    } else {
                        str12 = "+=";
                    }
                }
                else if (InStr(A_LoopField106, " " + keyWordAssignSub + " ")) {
                    str1 = StrSplit(A_LoopField106, " " + keyWordAssignSub + " ", 1);
                    str6 = StrSplit(A_LoopField106, " " + keyWordAssignSub + " ", 2);
                    str10 = keyWordAssignSub;
                    str11 = keyWordAssignSub_2;
                    str12 = "-=";
                }
                else if (InStr(A_LoopField106, " " + keyWordAssignMul + " ")) {
                    str1 = StrSplit(A_LoopField106, " " + keyWordAssignMul + " ", 1);
                    str6 = StrSplit(A_LoopField106, " " + keyWordAssignMul + " ", 2);
                    str10 = keyWordAssignMul;
                    str11 = keyWordAssignMul_2;
                    str12 = "*=";
                }
                else if (InStr(A_LoopField106, " " + keyWordAssignDiv + " ")) {
                    str1 = StrSplit(A_LoopField106, " " + keyWordAssignDiv + " ", 1);
                    str6 = StrSplit(A_LoopField106, " " + keyWordAssignDiv + " ", 2);
                    str10 = keyWordAssignDiv;
                    str11 = keyWordAssignDiv_2;
                    str12 = "/=";
                }
                else if (InStr(A_LoopField106, " " + keyWordAssignMod + " ")) {
                    str1 = StrSplit(A_LoopField106, " " + keyWordAssignMod + " ", 1);
                    str6 = StrSplit(A_LoopField106, " " + keyWordAssignMod + " ", 2);
                    str10 = keyWordAssignMod;
                    str11 = keyWordAssignMod_2;
                    str12 = "%=";
                }
                else if (InStr(A_LoopField106, " " + keyWordAssignShiftLeft + " ")) {
                    str1 = StrSplit(A_LoopField106, " " + keyWordAssignShiftLeft + " ", 1);
                    str6 = StrSplit(A_LoopField106, " " + keyWordAssignShiftLeft + " ", 2);
                    str10 = keyWordAssignShiftLeft;
                    str11 = keyWordAssignShiftLeft_2;
                    str12 = "<<=";
                }
                else if (InStr(A_LoopField106, " " + keyWordAssignShiftRight + " ")) {
                    str1 = StrSplit(A_LoopField106, " " + keyWordAssignShiftRight + " ", 1);
                    str6 = StrSplit(A_LoopField106, " " + keyWordAssignShiftRight + " ", 2);
                    str10 = keyWordAssignShiftRight;
                    str11 = keyWordAssignShiftRight_2;
                    str12 = ">>=";
                }
                else if (InStr(A_LoopField106, " " + keyWordLogicalAssignShiftRight + " ")) {
                    str1 = StrSplit(A_LoopField106, " " + keyWordLogicalAssignShiftRight + " ", 1);
                    str6 = StrSplit(A_LoopField106, " " + keyWordLogicalAssignShiftRight + " ", 2);
                    str10 = keyWordLogicalAssignShiftRight;
                    str11 = keyWordLogicalAssignShiftRight_2;
                    str12 = ">>>=";
                }
                else if (InStr(A_LoopField106, " " + keyWordAssignBitAnd + " ")) {
                    str1 = StrSplit(A_LoopField106, " " + keyWordAssignBitAnd + " ", 1);
                    str6 = StrSplit(A_LoopField106, " " + keyWordAssignBitAnd + " ", 2);
                    str10 = keyWordAssignBitAnd;
                    str11 = keyWordAssignBitAnd_2;
                    str12 = "&=";
                }
                else if (InStr(A_LoopField106, " " + keyWordAssignBitOr + " ")) {
                    str1 = StrSplit(A_LoopField106, " " + keyWordAssignBitOr + " ", 1);
                    str6 = StrSplit(A_LoopField106, " " + keyWordAssignBitOr + " ", 2);
                    str10 = keyWordAssignBitOr;
                    str11 = keyWordAssignBitOr_2;
                    str12 = "|=";
                }
                else if (InStr(A_LoopField106, " " + keyWordAssignBitXor + " ")) {
                    str1 = StrSplit(A_LoopField106, " " + keyWordAssignBitXor + " ", 1);
                    str6 = StrSplit(A_LoopField106, " " + keyWordAssignBitXor + " ", 2);
                    str10 = keyWordAssignBitXor;
                    str11 = keyWordAssignBitXor_2;
                    str12 = "^=";
                }
                str6 = Trim(expressionParserTranspiler(Trim(str6)));
                if (SubStrLastChars(str6, 1) == ";") {
                    str6 = StringTrimRight(str6, 1);
                }
                str1 = Trim(str1);
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                ALoopField = str1;
                if (InStr(ALoopField, " ") == false) {
                    lineDone = 1;
                    str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str1);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            str4 = str1 + " " + str11 + " " + str6 + ";";
                        } else {
                            str4 = str1 + " " + str11 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str1 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "js") {
                        str4 = str1 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "go") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "cs") {
                        str4 = str1 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "java") {
                        if (InStr(str1, "[")) {
                            // Convert arr[something] to arr.set(something, value);
                            str1 = RegExReplace(str1, "(\\b[A-Za-z_]\\w*)\\s*\\[(.*?)\\]", "$1.set($2, ");
                            str4 = str1 + str6 + ");";
                        } else {
                            str4 = str1 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "nim") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "swift") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str1 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = str1 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = str1 + " " + str12 + " " + str6;
                    }
                    htCode += str4 + Chr(10);
                }
                else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordConst)) == keyWordConst && lineDone == 0) {
                    lineDone = 1;
                    if (usePostfixTypeForTypeDefinition == "off") {
                        lineDone = 1;
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordConst)));
                        items124 = LoopParseFunc(str1, " ")
                        for (let A_Index124 = 0; A_Index124 < items124.length + 0; A_Index124++) {
                            const A_LoopField124 = items124[A_Index124 - 0];
                            str2 = A_LoopField124;
                        }
                        str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                        str2 = Trim(str2);
                        // str2 = var name
                        // str3 = type
                        HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    } else {
                        lineDone = 1;
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordConst)));
                        str2 = Trim(StrSplit(str1, ":", 1));
                        str3 = Trim(StrSplit(str1, ":", 2));
                        // str2 = var name
                        // str3 = type
                    }
                    if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                        str3 = getFuncTypeConvert(str3);
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                str6 = "{" + str6 + "}";
                            } else {
                                str6 = "[" + str6 + "]";
                            }
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordConst_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = keyWordConst_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordConst_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = keyWordConst_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        }
                        if (langToConvertTo == "js") {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        }
                        if (langToConvertTo == "go") {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "let " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " := [" + str6 + "]";
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = "def " + str2 + " = [" + str6 + "]";
                        }
                    } else {
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        str3 = getFuncTypeConvert(str3);
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordConst_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = keyWordConst_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordConst_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = keyWordConst_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = "const " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "js") {
                            str4 = "const " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "go") {
                            str4 = "const " + str2 + " " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "cs") {
                            str4 = "const " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = "final " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static final " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "val " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "const " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "let " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "dart") {
                            str4 = "const " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "const " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = "final " + str2 + " " + str12 + " " + str6;
                        }
                        //;;;
                    }
                    htCode += str4 + Chr(10);
                }
                else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordVar)) == keyWordVar && lineDone == 0) {
                    lineDone = 1;
                    if (usePostfixTypeForTypeDefinition == "off") {
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordVar)));
                        items125 = LoopParseFunc(str1, " ")
                        for (let A_Index125 = 0; A_Index125 < items125.length + 0; A_Index125++) {
                            const A_LoopField125 = items125[A_Index125 - 0];
                            str2 = A_LoopField125;
                        }
                        str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                        str2 = Trim(str2);
                        // str2 = var name
                        // str3 = type
                        HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    } else {
                        lineDone = 1;
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordVar)));
                        str2 = Trim(StrSplit(str1, ":", 1));
                        str3 = Trim(StrSplit(str1, ":", 2));
                        // str2 = var name
                        // str3 = type
                    }
                    if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                        str3 = getFuncTypeConvert(str3);
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                str6 = "{" + str6 + "}";
                            } else {
                                str6 = "[" + str6 + "]";
                            }
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordVar_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = keyWordVar_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordVar_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = keyWordVar_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        }
                        if (langToConvertTo == "js") {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        }
                        if (langToConvertTo == "go") {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " := [" + str6 + "]";
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = "def " + str2 + " = [" + str6 + "]";
                        }
                    } else {
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        str3 = getFuncTypeConvert(str3);
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordVar_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = keyWordVar_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordVar_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = keyWordVar_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "js") {
                            str4 = "var " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "go") {
                            str4 = "var " + str2 + " " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + "? " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = "def " + str2 + " " + str12 + " " + str6;
                        }
                        //;;;
                    }
                    htCode += str4 + Chr(10);
                }
                else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordLet)) == keyWordLet && lineDone == 0) {
                    lineDone = 1;
                    if (usePostfixTypeForTypeDefinition == "off") {
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordLet)));
                        items126 = LoopParseFunc(str1, " ")
                        for (let A_Index126 = 0; A_Index126 < items126.length + 0; A_Index126++) {
                            const A_LoopField126 = items126[A_Index126 - 0];
                            str2 = A_LoopField126;
                        }
                        str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                        str2 = Trim(str2);
                        // str2 = var name
                        // str3 = type
                        HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    } else {
                        lineDone = 1;
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordLet)));
                        str2 = Trim(StrSplit(str1, ":", 1));
                        str3 = Trim(StrSplit(str1, ":", 2));
                        // str2 = var name
                        // str3 = type
                        HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    }
                    if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                        str3 = getFuncTypeConvert(str3);
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                str6 = "{" + str6 + "}";
                            } else {
                                str6 = "[" + str6 + "]";
                            }
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordLet_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = keyWordLet_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordLet_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = keyWordLet_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        }
                        if (langToConvertTo == "js") {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        }
                        if (langToConvertTo == "go") {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " := [" + str6 + "]";
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = "def " + str2 + " = [" + str6 + "]";
                        }
                    } else {
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        str3 = getFuncTypeConvert(str3);
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordLet_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = keyWordLet_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = keyWordLet_2 + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = keyWordLet_2 + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "js") {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "go") {
                            str4 = "var " + str2 + " " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "lua") {
                            str4 = "local " + str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "let " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = "def " + str2 + " " + str12 + " " + str6;
                        }
                        //;;;
                    }
                    htCode += str4 + Chr(10);
                }
                else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordDouble + " ")) == keyWordDouble + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordChar + " ")) == keyWordChar + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint8 + " ")) == keyWordUint8 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint16 + " ")) == keyWordUint16 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint32 + " ")) == keyWordUint32 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint64 + " ")) == keyWordUint64 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT + " ")) == keyWordINT + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordSTR + " ")) == keyWordSTR + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordBOOL + " ")) == keyWordBOOL + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordFLOAT + " ")) == keyWordFLOAT + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT8 + " ")) == keyWordINT8 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT16 + " ")) == keyWordINT16 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT32 + " ")) == keyWordINT32 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT64 + " ")) == keyWordINT64 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayDefinition + " ")) == keyWordArrayDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfIntegersDefinition + " ")) == keyWordArrayOfIntegersDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfStringsDefinition + " ")) == keyWordArrayOfStringsDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfFloatingPointNumbersDefinition + " ")) == keyWordArrayOfFloatingPointNumbersDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfBooleansDefinition + " ")) == keyWordArrayOfBooleansDefinition + " " && usePrefixTypeForTypeDefinition == "on" && lineDone == 0) {
                    lineDone = 1;
                    items127 = LoopParseFunc(str1, " ")
                    for (let A_Index127 = 0; A_Index127 < items127.length + 0; A_Index127++) {
                        const A_LoopField127 = items127[A_Index127 - 0];
                        str2 = A_LoopField127;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                        str3 = getFuncTypeConvert(str3);
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                str6 = "{" + str6 + "}";
                            } else {
                                str6 = "[" + str6 + "]";
                            }
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        }
                        if (langToConvertTo == "js") {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        }
                        if (langToConvertTo == "go") {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " := [" + str6 + "]";
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = "def " + str2 + " = [" + str6 + "]";
                        }
                    } else {
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        str3 = getFuncTypeConvert(str3);
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "js") {
                            if (useInJavaScriptAlwaysUseVar == "on") {
                                str4 = "var " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            str4 = "var " + str2 + " " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2  + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "ts") {
                            if (useInJavaScriptAlwaysUseVar == "on") {
                                str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = "def " + str2 + " " + str12 + " " + str6;
                        }
                        //;;;
                    }
                    htCode += str4 + Chr(10);
                }
                else if (RegExMatch(Trim(str1), "^[a-zA-Z_][a-zA-Z_0-9]*:\\s?.*$") && usePostfixTypeForTypeDefinition == "on" && lineDone == 0) {
                    lineDone = 1;
                    str2 = Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                        str3 = getFuncTypeConvert(str3);
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                str6 = "{" + str6 + "}";
                            } else {
                                str6 = "[" + str6 + "]";
                            }
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        }
                        if (langToConvertTo == "js") {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        }
                        if (langToConvertTo == "go") {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "val " + str2 + " = arrayListOf(" + str6 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " := [" + str6 + "]";
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "ts") {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = "def " + str2 + " = [" + str6 + "]";
                        }
                    } else {
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        //;;;
                        str3 = getFuncTypeConvert(str3);
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "py") {
                            str4 = str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "js") {
                            if (useInJavaScriptAlwaysUseVar == "on") {
                                str4 = "var " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            str4 = "var " + str2 + " " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "lua") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "kt") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "rb") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "nim") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "ahk") {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "swift") {
                            str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6;
                        }
                        if (langToConvertTo == "dart") {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        if (langToConvertTo == "ts") {
                            if (useInJavaScriptAlwaysUseVar == "on") {
                                str4 = "var " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            str4 = "def " + str2 + " " + str12 + " " + str6 + ";";
                        }
                        //;;;
                    }
                    htCode += str4 + Chr(10);
                }
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; vars
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if (SubStr(Trim(A_LoopField106), 1, StrLen(keyWordVar)) == keyWordVar && lineDone == 0) {
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField106), StrLen(keyWordVar)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    items128 = LoopParseFunc(str1, " ")
                    for (let A_Index128 = 0; A_Index128 < items128.length + 0; A_Index128++) {
                        const A_LoopField128 = items128[A_Index128 - 0];
                        str2 = A_LoopField128;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField106), StrLen(keyWordVar)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    str2 = Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                }
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordVar_2 + " " + str3 + " " + str2 + ";";
                            } else {
                                str4 = keyWordVar_2 + " " + str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordVar_2 + " " + str3 + " " + str2;
                            } else {
                                str4 = keyWordVar_2 + " " + str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str3 + " " + str2 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "let " + str2 + " = [];";
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = {}";
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new " + str3 + "();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new " + str3 + "();";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new ArrayList<>();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new ArrayList<>();";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "val " + str2 + " = " + str3 + "()";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " = @[]";
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := []";
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = []";
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " = [];";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "let " + str2 + ": " + str3 + " = [];";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = "def " + str2 + " = []";
                    }
                } else {
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2;
                            } else {
                                str4 = str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (str3 == "double") {
                            str5 = "0.00";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint16_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint32_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint64_t") {
                            str5 = "0ULL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "std::string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.00f";
                        }
                        if (str3 == "int8_t") {
                            str5 = "0";
                        }
                        if (str3 == "int16_t") {
                            str5 = "0";
                        }
                        if (str3 == "int32_t") {
                            str5 = "0";
                        }
                        if (str3 == "int64_t") {
                            str5 = "0LL";
                        }
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = None";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "var " + str2 + ";";
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " +  str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "cs") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "0";
                        }
                        if (str3 == "ushort") {
                            str5 = "0";
                        }
                        if (str3 == "uint") {
                            str5 = "0";
                        }
                        if (str3 == "ulong") {
                            str5 = "0UL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "sbyte") {
                            str5 = "0";
                        }
                        if (str3 == "short") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "(byte) 0";
                        }
                        if (str3 == "short") {
                            str5 = "(short) 0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "boolean") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0L";
                        }
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + ": " + str3 + "? = null";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == "float") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8") {
                            str5 = "0";
                        }
                        if (str3 == "uint16") {
                            str5 = "0";
                        }
                        if (str3 == "uint32") {
                            str5 = "0";
                        }
                        if (str3 == "uint64") {
                            str5 = "0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := " + Chr(34) + Chr(34);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == "Double") {
                            str5 = "0.00";
                        }
                        if (str3 == "Character") {
                            str5 = Chr(34) + "a" + Chr(34);
                        }
                        if (str3 == "UInt8") {
                            str5 = "0";
                        }
                        if (str3 == "UInt16") {
                            str5 = "0";
                        }
                        if (str3 == "UInt32") {
                            str5 = "0";
                        }
                        if (str3 == "UInt64") {
                            str5 = "0";
                        }
                        if (str3 == "Int") {
                            str5 = "0";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "Bool") {
                            str5 = "false";
                        }
                        if (str3 == "Float") {
                            str5 = "0.00";
                        }
                        if (str3 == "Int8") {
                            str5 = "0";
                        }
                        if (str3 == "Int16") {
                            str5 = "0";
                        }
                        if (str3 == "Int32") {
                            str5 = "0";
                        }
                        if (str3 == "Int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + "? " + str2 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "var " + str2 + ": " + str3 + ";";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = "def " + str2;
                    }
                    //;;;
                }
                htCode += str4 + Chr(10);
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if (SubStr(Trim(A_LoopField106), 1, StrLen(keyWordLet)) == keyWordLet && lineDone == 0) {
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField106), StrLen(keyWordLet)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    items129 = LoopParseFunc(str1, " ")
                    for (let A_Index129 = 0; A_Index129 < items129.length + 0; A_Index129++) {
                        const A_LoopField129 = items129[A_Index129 - 0];
                        str2 = A_LoopField129;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField106), StrLen(keyWordLet)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    str2 = Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                }
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordLet_2 + " " + str3 + " " + str2 + ";";
                            } else {
                                str4 = keyWordLet_2 + " " + str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = keyWordLet_2 + " " + str3 + " " + str2;
                            } else {
                                str4 = keyWordLet_2 + " " + str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str3 + " " + str2 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "let " + str2 + " = [];";
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = {}";
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new " + str3 + "();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new " + str3 + "();";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new ArrayList<>();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new ArrayList<>();";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "val " + str2 + " = " + str3 + "()";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " = @[]";
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := []";
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = []";
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " = [];";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "let " + str2 + ": " + str3 + " = [];";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = "def " + str2 + " = []";
                    }
                } else {
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2;
                            } else {
                                str4 = str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (str3 == "double") {
                            str5 = "0.00";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint16_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint32_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint64_t") {
                            str5 = "0ULL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "std::string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.00f";
                        }
                        if (str3 == "int8_t") {
                            str5 = "0";
                        }
                        if (str3 == "int16_t") {
                            str5 = "0";
                        }
                        if (str3 == "int32_t") {
                            str5 = "0";
                        }
                        if (str3 == "int64_t") {
                            str5 = "0LL";
                        }
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = None";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "let " + str2 + ";";
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = "local " + str2 + " = nil";
                    }
                    if (langToConvertTo == "cs") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "0";
                        }
                        if (str3 == "ushort") {
                            str5 = "0";
                        }
                        if (str3 == "uint") {
                            str5 = "0";
                        }
                        if (str3 == "ulong") {
                            str5 = "0UL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "sbyte") {
                            str5 = "0";
                        }
                        if (str3 == "short") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "(byte) 0";
                        }
                        if (str3 == "short") {
                            str5 = "(short) 0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "boolean") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0L";
                        }
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + ": " + str3 + "? = null";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == "float") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8") {
                            str5 = "0";
                        }
                        if (str3 == "uint16") {
                            str5 = "0";
                        }
                        if (str3 == "uint32") {
                            str5 = "0";
                        }
                        if (str3 == "uint64") {
                            str5 = "0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := " + Chr(34) + Chr(34);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == "Double") {
                            str5 = "0.00";
                        }
                        if (str3 == "Character") {
                            str5 = Chr(34) + "a" + Chr(34);
                        }
                        if (str3 == "UInt8") {
                            str5 = "0";
                        }
                        if (str3 == "UInt16") {
                            str5 = "0";
                        }
                        if (str3 == "UInt32") {
                            str5 = "0";
                        }
                        if (str3 == "UInt64") {
                            str5 = "0";
                        }
                        if (str3 == "Int") {
                            str5 = "0";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "Bool") {
                            str5 = "false";
                        }
                        if (str3 == "Float") {
                            str5 = "0.00";
                        }
                        if (str3 == "Int8") {
                            str5 = "0";
                        }
                        if (str3 == "Int16") {
                            str5 = "0";
                        }
                        if (str3 == "Int32") {
                            str5 = "0";
                        }
                        if (str3 == "Int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + "? " + str2 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "let " + str2 + ": " + str3 + ";";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = "def " + str2;
                    }
                    //;;;
                }
                htCode += str4 + Chr(10);
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if (SubStr(Trim(A_LoopField106), 1, StrLen(keyWordDouble + " ")) == keyWordDouble + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordChar + " ")) == keyWordChar + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordUint8 + " ")) == keyWordUint8 + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordUint16 + " ")) == keyWordUint16 + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordUint32 + " ")) == keyWordUint32 + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordUint64 + " ")) == keyWordUint64 + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordINT + " ")) == keyWordINT + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordSTR + " ")) == keyWordSTR + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordBOOL + " ")) == keyWordBOOL + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordFLOAT + " ")) == keyWordFLOAT + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordINT8 + " ")) == keyWordINT8 + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordINT16 + " ")) == keyWordINT16 + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordINT32 + " ")) == keyWordINT32 + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordINT64 + " ")) == keyWordINT64 + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordArrayDefinition + " ")) == keyWordArrayDefinition + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordArrayOfIntegersDefinition + " ")) == keyWordArrayOfIntegersDefinition + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordArrayOfStringsDefinition + " ")) == keyWordArrayOfStringsDefinition + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordArrayOfFloatingPointNumbersDefinition + " ")) == keyWordArrayOfFloatingPointNumbersDefinition + " " || SubStr(Trim(A_LoopField106), 1, StrLen(keyWordArrayOfBooleansDefinition + " ")) == keyWordArrayOfBooleansDefinition + " " && usePrefixTypeForTypeDefinition == "on" && lineDone == 0) {
                lineDone = 1;
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                str1 = Trim(A_LoopField106);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                items130 = LoopParseFunc(str1, " ")
                for (let A_Index130 = 0; A_Index130 < items130.length + 0; A_Index130++) {
                    const A_LoopField130 = items130[A_Index130 - 0];
                    str2 = A_LoopField130;
                }
                str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                str2 = Trim(str2);
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2;
                            } else {
                                str4 = str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str3 + " " + str2 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "js") {
                        str4 = "let " + str2 + " = [];";
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = {}";
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new " + str3 + "();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new " + str3 + "();";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new ArrayList<>();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new ArrayList<>();";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "val " + str2 + " = " + str3 + "()";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " = @[]";
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := []";
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = []";
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " = [];";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "let " + str2 + ": " + str3 + " = [];";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = "def " + str2 + " = []";
                    }
                } else {
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2;
                            } else {
                                str4 = str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (str3 == "double") {
                            str5 = "0.00";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint16_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint32_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint64_t") {
                            str5 = "0ULL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "std::string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.00f";
                        }
                        if (str3 == "int8_t") {
                            str5 = "0";
                        }
                        if (str3 == "int16_t") {
                            str5 = "0";
                        }
                        if (str3 == "int32_t") {
                            str5 = "0";
                        }
                        if (str3 == "int64_t") {
                            str5 = "0LL";
                        }
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = None";
                    }
                    if (langToConvertTo == "js") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + ";";
                        } else {
                            str4 = "let " + str2 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "cs") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "0";
                        }
                        if (str3 == "ushort") {
                            str5 = "0";
                        }
                        if (str3 == "uint") {
                            str5 = "0";
                        }
                        if (str3 == "ulong") {
                            str5 = "0UL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "sbyte") {
                            str5 = "0";
                        }
                        if (str3 == "short") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "(byte) 0";
                        }
                        if (str3 == "short") {
                            str5 = "(short) 0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "boolean") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0L";
                        }
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + ": " + str3 + "? = null";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == "float") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8") {
                            str5 = "0";
                        }
                        if (str3 == "uint16") {
                            str5 = "0";
                        }
                        if (str3 == "uint32") {
                            str5 = "0";
                        }
                        if (str3 == "uint64") {
                            str5 = "0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := " + Chr(34) + Chr(34);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == "Double") {
                            str5 = "0.00";
                        }
                        if (str3 == "Character") {
                            str5 = Chr(34) + "a" + Chr(34);
                        }
                        if (str3 == "UInt8") {
                            str5 = "0";
                        }
                        if (str3 == "UInt16") {
                            str5 = "0";
                        }
                        if (str3 == "UInt32") {
                            str5 = "0";
                        }
                        if (str3 == "UInt64") {
                            str5 = "0";
                        }
                        if (str3 == "Int") {
                            str5 = "0";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "Bool") {
                            str5 = "false";
                        }
                        if (str3 == "Float") {
                            str5 = "0.00";
                        }
                        if (str3 == "Int8") {
                            str5 = "0";
                        }
                        if (str3 == "Int16") {
                            str5 = "0";
                        }
                        if (str3 == "Int32") {
                            str5 = "0";
                        }
                        if (str3 == "Int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + "? " + str2 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + ": " + str3 + ";";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = "def " + str2;
                    }
                    //;;;
                }
                htCode += str4 + Chr(10);
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if (RegExMatch(Trim(A_LoopField106), "^[a-zA-Z_][a-zA-Z0-9_]*: [^:]*;?$") && usePostfixTypeForTypeDefinition == "on" && lineDone == 0) {
                lineDone = 1;
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                str1 = Trim(A_LoopField106);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str2 = Trim(StrSplit(str1, ":", 1));
                str3 = Trim(StrSplit(str1, ":", 2));
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2;
                            } else {
                                str4 = str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        str4 = str3 + " " + str2 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "js") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + " = [];";
                        } else {
                            str4 = "let " + str2 + " = [];";
                        }
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = {}";
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new " + str3 + "();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new " + str3 + "();";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = new ArrayList<>();";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = new ArrayList<>();";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "val " + str2 + " = " + str3 + "()";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = []";
                    }
                    if (langToConvertTo == "nim") {
                        str4 = "var " + str2 + ": " + str3 + " = @[]";
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := []";
                    }
                    if (langToConvertTo == "swift") {
                        str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = []";
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + " " + str2 + " = [];";
                    }
                    if (langToConvertTo == "ts") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + ": " + str3 + " = [];";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " = [];";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = "def " + str2 + " = []";
                    }
                } else {
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    //;;;
                    str3 = getFuncTypeConvert(str3);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2 + ";";
                            } else {
                                str4 = str2 + ": " + str3 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = str3 + " " + str2;
                            } else {
                                str4 = str2 + ": " + str3;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (str3 == "double") {
                            str5 = "0.00";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint16_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint32_t") {
                            str5 = "0";
                        }
                        if (str3 == "uint64_t") {
                            str5 = "0ULL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "std::string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.00f";
                        }
                        if (str3 == "int8_t") {
                            str5 = "0";
                        }
                        if (str3 == "int16_t") {
                            str5 = "0";
                        }
                        if (str3 == "int32_t") {
                            str5 = "0";
                        }
                        if (str3 == "int64_t") {
                            str5 = "0LL";
                        }
                        str4 = str3 + " " + str2 + " = " + str5 + ";";
                    }
                    if (langToConvertTo == "py") {
                        str4 = str2 + " = None";
                    }
                    if (langToConvertTo == "js") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + ";";
                        } else {
                            str4 = "let " + str2 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        str4 = "var " + str2 + " " + str3;
                    }
                    if (langToConvertTo == "lua") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "cs") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "0";
                        }
                        if (str3 == "ushort") {
                            str5 = "0";
                        }
                        if (str3 == "uint") {
                            str5 = "0";
                        }
                        if (str3 == "ulong") {
                            str5 = "0UL";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "sbyte") {
                            str5 = "0";
                        }
                        if (str3 == "short") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (csMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (str3 == "double") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "byte") {
                            str5 = "(byte) 0";
                        }
                        if (str3 == "short") {
                            str5 = "(short) 0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "long") {
                            str5 = "0L";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "boolean") {
                            str5 = "false";
                        }
                        if (str3 == "float") {
                            str5 = "0.0f";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0L";
                        }
                        if (javaMainFuncSeen == 1) {
                            str4 = str3 + " " + str2 + " = " + str5 + ";";
                        } else {
                            str4 = "static " + str3 + " " + str2 + " = " + str5 + ";";
                        }
                    }
                    if (langToConvertTo == "kt") {
                        str4 = "var " + str2 + ": " + str3 + "? = null";
                    }
                    if (langToConvertTo == "rb") {
                        str4 = str2 + " = nil";
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == "float") {
                            str5 = "0.0";
                        }
                        if (str3 == "char") {
                            str5 = "'a'";
                        }
                        if (str3 == "uint8") {
                            str5 = "0";
                        }
                        if (str3 == "uint16") {
                            str5 = "0";
                        }
                        if (str3 == "uint32") {
                            str5 = "0";
                        }
                        if (str3 == "uint64") {
                            str5 = "0";
                        }
                        if (str3 == "int") {
                            str5 = "0";
                        }
                        if (str3 == "string") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "bool") {
                            str5 = "false";
                        }
                        if (str3 == "int8") {
                            str5 = "0";
                        }
                        if (str3 == "int16") {
                            str5 = "0";
                        }
                        if (str3 == "int32") {
                            str5 = "0";
                        }
                        if (str3 == "int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "ahk") {
                        str4 = str2 + " := " + Chr(34) + Chr(34);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == "Double") {
                            str5 = "0.00";
                        }
                        if (str3 == "Character") {
                            str5 = Chr(34) + "a" + Chr(34);
                        }
                        if (str3 == "UInt8") {
                            str5 = "0";
                        }
                        if (str3 == "UInt16") {
                            str5 = "0";
                        }
                        if (str3 == "UInt32") {
                            str5 = "0";
                        }
                        if (str3 == "UInt64") {
                            str5 = "0";
                        }
                        if (str3 == "Int") {
                            str5 = "0";
                        }
                        if (str3 == "String") {
                            str5 = Chr(34) + Chr(34);
                        }
                        if (str3 == "Bool") {
                            str5 = "false";
                        }
                        if (str3 == "Float") {
                            str5 = "0.00";
                        }
                        if (str3 == "Int8") {
                            str5 = "0";
                        }
                        if (str3 == "Int16") {
                            str5 = "0";
                        }
                        if (str3 == "Int32") {
                            str5 = "0";
                        }
                        if (str3 == "Int64") {
                            str5 = "0";
                        }
                        str4 = "var " + str2 + ": " + str3 + " = " + str5;
                    }
                    if (langToConvertTo == "dart") {
                        str4 = str3 + "? " + str2 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        if (useInJavaScriptAlwaysUseVar == "on") {
                            str4 = "var " + str2 + ": " + str3 + ";";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = "def " + str2;
                    }
                    //;;;
                }
                htCode += str4 + Chr(10);
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if ((SubStr(Trim(A_LoopField106), -2) == ");" || SubStr(Trim(A_LoopField106), -1) == ")") && !(InStr(StrLower(A_LoopField106), " main(")) && lineDone == 0) {
                lineDone = 1;
                str1 = Trim(A_LoopField106);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                fixExpertionLineFuncOnly = 0;
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        str2 = expressionParserTranspiler(Trim(str1)) + ";";
                    } else {
                        str2 = expressionParserTranspiler(Trim(str1));
                    }
                } else {
                    if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "groovy") {
                        str2 = expressionParserTranspiler(Trim(str1));
                    } else {
                        str2 = expressionParserTranspiler(Trim(str1)) + ";";
                    }
                }
                fixExpertionLineFuncOnly = 0;
                htCode += str2 + Chr(10);
            }
            else if (KeyWordsCommands(A_LoopField106, "check", commands, langToConvertTo) == "true" && lineDone == 0) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += A_LoopField106 + Chr(10);
                } else {
                    out_KeyWordsCommands = KeyWordsCommands(A_LoopField106, "transpile", commands, langToConvertTo);
                    htCode += out_KeyWordsCommands + Chr(10);
                }
            } else {
                //print("else else else " . A_LoopField106)
                // this is THE else
                if (lineDone != 1) {
                    if (skipLeftCuleyForFuncPLS != 1) {
                        if (SubStr(Trim(StrLower(A_LoopField106)), 1, 1) == Chr(125)) {
                            htCode += Chr(125) + Chr(10);
                        } else {
                            if (htCodeAcurlyBraceAddSomeVrasFixLP == 1 && SubStr(Trim(StrLower(A_LoopField106)), 1, 1) == Chr(123)) {
                                htCodeAcurlyBraceAddSomeVrasFixLP = 0;
                                htCode += A_LoopField106 + Chr(10) + theFixTextLoopLP + Chr(10);
                            } else {
                                if (htCodeAcurlyBraceAddSomeVrasFixNL == 1 && SubStr(Trim(StrLower(A_LoopField106)), 1, 1) == Chr(123)) {
                                    htCodeAcurlyBraceAddSomeVrasFixNL = 0;
                                    htCode += A_LoopField106 + Chr(10) + theFixTextLoopNL + Chr(10);
                                } else {
                                    htCode += A_LoopField106 + Chr(10);
                                }
                            }
                        }
                    } else {
                        skipLeftCuleyForFuncPLS = 0;
                    }
                }
            }
        }
        htCode = StringTrimRight(htCode, 1);
        //s
        //s
        //s
        if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
            //s
            if (haveWeEverUsedAloop == 1) {
                htCodeLoopfixa = StringTrimRight(htCodeLoopfixa, 1);
                //OutputDebug, |%htCodeLoopfixa%|
                AIndexLoopCurlyFix = 1;
                items131 = LoopParseFunc(htCodeLoopfixa, "\n", "\r")
                for (let A_Index131 = 0; A_Index131 < items131.length + 0; A_Index131++) {
                    const A_LoopField131 = items131[A_Index131 - 0];
                    sstr123 = A_LoopField131;
                    fixLoopLokingFor = A_LoopField131;
                    fixLoopLokingForfound = 1;
                    out1 = StrSplit(sstr123 ,"|" , 1);
                    out2 = StrSplit(sstr123 ,"|" , 3);
                    //OutputDebug, |%out1%|
                    //OutputDebug, |%out2%|
                    wasAtanyIfsElseAddAIndexLoopCurlyFix = 0;
                    if (out1 == "nl") {
                        inTarget = 0;
                        insideBracket = 0;
                        netsedCurly = 0;
                        eldLoopNestedBADlol = 0;
                        readyToEnd = 0;
                        endBracketDOntPutThere = 0;
                        dontSaveStr = 0;
                        weAreDoneHereCurly = 0;
                        DeleayOneCuzOfLoopParse = 0;
                        fixLoopLokingForNum = 0;
                        insdeAnestedLoopBAD = 0;
                        foundTheTopLoop = 0;
                        out4758686d86d86d86578991a = "";
                        items132 = LoopParseFunc(htCode, "\n", "\r")
                        for (let A_Index132 = 0; A_Index132 < items132.length + 0; A_Index132++) {
                            const A_LoopField132 = items132[A_Index132 - 0];
                            //MsgBox, dsfgsdefgesrdg1
                            //MsgBox, |%A_LoopField132%|`n|%fixLoopLokingFor%|
                            if (InStr(A_LoopField132, fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 1
                            }
                            if (SubStr(Trim(A_LoopField132), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField132 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(s);
                                //MsgBox, % out1z
                                //MsgBox, do we came here 2
                                fixLoopLokingForNum = 0;
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField132
                                dontSaveStr = 1;
                                ALoopField = A_LoopField132;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if (inTarget == 1 && InStr(A_LoopField132, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField132, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField132, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField132), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField132, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField132, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField132, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField132, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField132
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField132 + Chr(10);
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField132;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if (inTarget == 1 && InStr(A_LoopField132, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1) {
                                //MsgBox, % A_LoopField132
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField132 + Chr(10);
                            }
                            endBracketDOntPutThere = 0;
                            if (eldLoopNestedBADlol == 1) {
                                insdeAnestedLoopBAD = 0;
                            }
                        }
                        strstysrstsytTRIMHELP = out4758686d86d86d86578991a;
                        strstysrstsytTRIMHELP = StringTrimRight(strstysrstsytTRIMHELP, 1);
                        htCode = strstysrstsytTRIMHELP;
                        //MsgBox, % htCode
                        wasAtanyIfsElseAddAIndexLoopCurlyFix = 1;
                    } else {
                        inTarget = 0;
                        insideBracket = 0;
                        netsedCurly = 0;
                        eldLoopNestedBADlol = 0;
                        readyToEnd = 0;
                        endBracketDOntPutThere = 0;
                        dontSaveStr = 0;
                        weAreDoneHereCurly = 0;
                        DeleayOneCuzOfLoopParse = 0;
                        fixLoopLokingForNum = 0;
                        insdeAnestedLoopBAD = 0;
                        foundTheTopLoop = 0;
                        out4758686d86d86d86578991a = "";
                        items133 = LoopParseFunc(htCode, "\n", "\r")
                        for (let A_Index133 = 0; A_Index133 < items133.length + 0; A_Index133++) {
                            const A_LoopField133 = items133[A_Index133 - 0];
                            if (InStr(A_LoopField133 , fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 3
                            }
                            if (SubStr(Trim(A_LoopField133), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField133 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(StrReplace(s, "|", ""));
                                //MsgBox, % out1z
                                fixLoopLokingForNum = 0;
                                //MsgBox, do we came here 4
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField133
                                dontSaveStr = 1;
                                ALoopField = A_LoopField133;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if (inTarget == 1 && InStr(A_LoopField133, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField133, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField133, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField133), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField133, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField133, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField133, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField133, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField133
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField133 + Chr(10);
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField133;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordALoopField + "\\d*", "" + keyWordALoopField + "" + out1z);
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if ((inTarget == 1 && InStr(A_LoopField133, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1)) {
                                //MsgBox, % A_LoopField133
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField133 + Chr(10);
                            }
                            endBracketDOntPutThere = 0;
                            if (eldLoopNestedBADlol == 1) {
                                insdeAnestedLoopBAD = 0;
                            }
                        }
                        strstysrstsytTRIMHELP = out4758686d86d86d86578991a;
                        strstysrstsytTRIMHELP = StringTrimRight(strstysrstsytTRIMHELP, 1);
                        htCode = strstysrstsytTRIMHELP;
                        //MsgBox, % htCode
                        wasAtanyIfsElseAddAIndexLoopCurlyFix = 1;
                    }
                    if (wasAtanyIfsElseAddAIndexLoopCurlyFix == 1) {
                        AIndexLoopCurlyFix++;
                        wasAtanyIfsElseAddAIndexLoopCurlyFix = 0;
                    }
                }
                out4758686d86dgt8r754444444 = "";
                hold = 0;
                items134 = LoopParseFunc(htCode, "\n", "\r")
                for (let A_Index134 = 0; A_Index134 < items134.length + 0; A_Index134++) {
                    const A_LoopField134 = items134[A_Index134 - 0];
                    ignore = 0;
                    if (SubStr(Trim(A_LoopField134), 1, 4) == "for ") {
                        if (hold == 1 && holdText == A_LoopField134) {
                            ignore = 1;
                        } else {
                            holdText = A_LoopField134;
                            hold = 1;
                        }
                    }
                    if (!ignore) {
                        out4758686d86dgt8r754444444 += A_LoopField134 + Chr(10);
                    }
                }
                out4758686d86dgt8r754444444 = StringTrimRight(out4758686d86dgt8r754444444, 1);
                htCode = out4758686d86dgt8r754444444;
            }
            htCodeOut1234565432 = "";
            items135 = LoopParseFunc(htCode, "\n", "\r")
            for (let A_Index135 = 0; A_Index135 < items135.length + 0; A_Index135++) {
                const A_LoopField135 = items135[A_Index135 - 0];
                out = A_LoopField135;
                if (!InStr(out, "|itsaersdtgtgfergsdgfsegdfsedAA|")) {
                    htCodeOut1234565432 += out + Chr(10);
                }
            }
            htCode = StringTrimRight(htCodeOut1234565432, 1);
            if (langToConvertTo == "rb") {
                htCode = StrReplace(htCode, "for HTVM----HTVM_FOR_hsdufosyigdydtddy_FOR_HTVM_Ruby_HTVM---HTVM-For_Ruby---AA ", "");
            }
        }
        if (langToConvertTo == "go") {
            htCode = fixGoAindexUnseen(htCode);
        }
    } else {
        htCode = code;
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var ADD_ALL_programmingBlock_HTVMsyntax = "";
    if (COUNT_programmingBlock_HTVMsyntax != 0) {
        isNotHTVMfileEXTRA_INT = 1;
        for (let A_Index136 = 0; A_Index136 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index136++) {
            ADD_ALL_programmingBlock_HTVMsyntax += programmingBlock_HTVMsyntax[A_Index136] + Chr(10);
        }
        ADD_ALL_programmingBlock_HTVMsyntax = StringTrimRight(ADD_ALL_programmingBlock_HTVMsyntax, 1);
        ADD_ALL_programmingBlock_HTVMsyntax = compiler(ADD_ALL_programmingBlock_HTVMsyntax, allInstructionFile, "full", langToConvertToParam);
        isNotHTVMfileEXTRA_INT = 0;
        isNotHTVMfile2 = 1;
        for (let A_Index137 = 0; A_Index137 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index137++) {
            htCode = StrReplace(htCode, "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(A_Index137 + 1) + "AA", compiler(programmingBlock_HTVMsyntax[A_Index137], allInstructionFile, "full", langToConvertToParam));
        }
        isNotHTVMfile2 = 0;
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    if (isNotHTVMfile == 1) {
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print(Chr(10) + isNotHTVMfileEXTRA_LIB_INFO + Chr(10));
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print(Chr(10) + isNotHTVMfileEXTRA_FUNCS_INFO + Chr(10));
        print(Chr(10));
        print("\nYou must include all the libs from under the section and MAKE SURE your code doesn't already use them!!!");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("\nYou must copy-paste all the funcs from under the section and MAKE SURE your code doesn't already use them!!!");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed\n");
        print("SCROLL UP!!!!!");
        print("SCROLL UP!!!!!");
        print("SCROLL UP!!!!!");
        print("Note: If you dont see any libs or built-in functions that you need to add, then that means you dont have to!");
        return htCode;
    }
    var fixLuaAndRuby = "";
    if (langToConvertTo == langFileExtension_2) {
        if (useCurlyBraces_2 == "off" && useEnd_2 == "off") {
            htCode = indent_nested_curly_braces(htCode, 0);
        } else {
            htCode = indent_nested_curly_braces(htCode, 1);
        }
        if (useEnd_2 == "on") {
            items138 = LoopParseFunc(htCode, "\n", "\r")
            for (let A_Index138 = 0; A_Index138 < items138.length + 0; A_Index138++) {
                const A_LoopField138 = items138[A_Index138 - 0];
                if (Trim(A_LoopField138) == keyWordCurlyBraceClose_2) {
                    fixLuaAndRuby += StrReplace(A_LoopField138, keyWordCurlyBraceClose_2, Trim(keyWordEnd_2)) + Chr(10);
                }
                else if (SubStrLastChars(A_LoopField138, 2) == " " + keyWordCurlyBraceOpen_2) {
                    fixLuaAndRuby += StringTrimRight(A_LoopField138, 2) + Chr(10);
                } else {
                    fixLuaAndRuby += A_LoopField138 + Chr(10);
                }
            }
            htCode = StringTrimRight(fixLuaAndRuby, 1);
        }
        //;;;;;;;;;;
        //;;;;;;;;;;
    } else {
        //;;;;;;;;;;
        //;;;;;;;;;;
        if (langToConvertTo == "py" || langToConvertTo == "nim") {
            htCode = indent_nested_curly_braces(htCode, 0);
        } else {
            htCode = indent_nested_curly_braces(htCode, 1);
        }
        if (langToConvertTo == "lua" || langToConvertTo == "rb") {
            items139 = LoopParseFunc(htCode, "\n", "\r")
            for (let A_Index139 = 0; A_Index139 < items139.length + 0; A_Index139++) {
                const A_LoopField139 = items139[A_Index139 - 0];
                if (Trim(A_LoopField139) == "}") {
                    fixLuaAndRuby += StrReplace(A_LoopField139, "}", "end") + Chr(10);
                }
                else if (SubStrLastChars(A_LoopField139, 2) == " {") {
                    fixLuaAndRuby += StringTrimRight(A_LoopField139, 2) + Chr(10);
                } else {
                    fixLuaAndRuby += A_LoopField139 + Chr(10);
                }
            }
            htCode = StringTrimRight(fixLuaAndRuby, 1);
        }
    }
    let nextWordEndFix = [];
    var nextWordEndFixOut = "";
    if (langToConvertTo == "lua") {
        items140 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index140 = 0; A_Index140 < items140.length + 0; A_Index140++) {
            const A_LoopField140 = items140[A_Index140 - 0];
            HTVM_Append(nextWordEndFix, A_LoopField140);
        }
        HTVM_Append(nextWordEndFix, " ");
        items141 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index141 = 0; A_Index141 < items141.length + 0; A_Index141++) {
            const A_LoopField141 = items141[A_Index141 - 0];
            if (Trim(A_LoopField141) == "end" && SubStr(Trim(nextWordEndFix[A_Index141 + 1]), 1, StrLen("elseif ")) == "elseif " || Trim(A_LoopField141) == "end" && Trim(nextWordEndFix[A_Index141 + 1]) == "else") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField141 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == "rb") {
        items142 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index142 = 0; A_Index142 < items142.length + 0; A_Index142++) {
            const A_LoopField142 = items142[A_Index142 - 0];
            HTVM_Append(nextWordEndFix, A_LoopField142);
        }
        HTVM_Append(nextWordEndFix, " ");
        items143 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index143 = 0; A_Index143 < items143.length + 0; A_Index143++) {
            const A_LoopField143 = items143[A_Index143 - 0];
            if (Trim(A_LoopField143) == "end" && SubStr(Trim(nextWordEndFix[A_Index143 + 1]), 1, StrLen("elsif ")) == "elsif " || Trim(A_LoopField143) == "end" && Trim(nextWordEndFix[A_Index143 + 1]) == "else") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField143 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    let nextWordEndFixRB = [];
    nextWordEndFixOut = "";
    if (langToConvertTo == "rb") {
        items144 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index144 = 0; A_Index144 < items144.length + 0; A_Index144++) {
            const A_LoopField144 = items144[A_Index144 - 0];
            HTVM_Append(nextWordEndFixRB, A_LoopField144);
        }
        HTVM_Append(nextWordEndFixRB, " ");
        items145 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index145 = 0; A_Index145 < items145.length + 0; A_Index145++) {
            const A_LoopField145 = items145[A_Index145 - 0];
            if (Trim(A_LoopField145) == "end" && SubStr(Trim(nextWordEndFixRB[A_Index145 + 1]), 1, StrLen("rescue ")) == "rescue " || Trim(A_LoopField145) == "end" && Trim(nextWordEndFixRB[A_Index145 + 1]) == "ensure") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField145 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    nextWordEndFixOut = "";
    if (langToConvertTo == "ahk") {
        items146 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index146 = 0; A_Index146 < items146.length + 0; A_Index146++) {
            const A_LoopField146 = items146[A_Index146 - 0];
            if (SubStr(Trim(A_LoopField146), 1, StrLen("Loop, Parse, ")) == "Loop, Parse, ") {
                nextWordEndFixOut += StrReplace(A_LoopField146, "{", Chr(10) + "{" + Chr(10)) + Chr(10);
            } else {
                nextWordEndFixOut += A_LoopField146 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == "go") {
        let fixGoManGoIsSoAnnoyingBroooFurure = [];
        items147 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index147 = 0; A_Index147 < items147.length + 0; A_Index147++) {
            const A_LoopField147 = items147[A_Index147 - 0];
            HTVM_Append(fixGoManGoIsSoAnnoyingBroooFurure, A_LoopField147);
        }
        HTVM_Append(fixGoManGoIsSoAnnoyingBroooFurure, " ");
        var fixGoManGoIsSoAnnoyingBroooSkip = 0;
        var fixGoManGoIsSoAnnoyingBroooCount = 0;
        var fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
        var fixGoManGoIsSoAnnoyingBrooo = "";
        items148 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index148 = 0; A_Index148 < items148.length + 0; A_Index148++) {
            const A_LoopField148 = items148[A_Index148 - 0];
            if (Trim(A_LoopField148) == "}" && SubStr(Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index148 + 1]), 1, StrLen("else if ")) == "else if ") {
                fixGoManGoIsSoAnnoyingBroooSkip = 1;
                fixGoManGoIsSoAnnoyingBroooCount = 0;
                items149 = LoopParseFunc(fixGoManGoIsSoAnnoyingBroooFurure[A_Index148 + 1])
                for (let A_Index149 = 0; A_Index149 < items149.length + 0; A_Index149++) {
                    const A_LoopField149 = items149[A_Index149 - 0];
                    if (A_LoopField149 == " ") {
                        fixGoManGoIsSoAnnoyingBroooCount++;
                    } else {
                        break;
                    }
                }
                fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
                for (let A_Index150 = 0; A_Index150 < fixGoManGoIsSoAnnoyingBroooCount + 0; A_Index150++) {
                    fixGoManGoIsSoAnnoyingBroooCountSpaceses += " ";
                }
                fixGoManGoIsSoAnnoyingBrooo += fixGoManGoIsSoAnnoyingBroooCountSpaceses + "} " + Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index148 + 1]) + Chr(10);
            } else {
                if (fixGoManGoIsSoAnnoyingBroooSkip == 0) {
                    fixGoManGoIsSoAnnoyingBrooo += A_LoopField148 + Chr(10);
                }
                fixGoManGoIsSoAnnoyingBroooSkip = 0;
            }
        }
        htCode = StringTrimRight(fixGoManGoIsSoAnnoyingBrooo, 1);
    }
    if (langToConvertTo == "cs" || langToConvertTo == "java") {
        htCode = fixCSandJAVAstaticBugForFunc(htCode);
    }
    if (COUNT_programmingBlock_InTheTranspiledLang != 0) {
        for (let A_Index151 = 0; A_Index151 < COUNT_programmingBlock_InTheTranspiledLang + 0; A_Index151++) {
            htCode = StrReplace(htCode, "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(A_Index151 + 1) + "AA", programmingBlock_InTheTranspiledLang[A_Index151]);
        }
    }
    if (langToConvertTo == "cpp") {
        if (COUNT_programmingBlock_CPP != 0) {
            for (let A_Index152 = 0; A_Index152 < COUNT_programmingBlock_CPP + 0; A_Index152++) {
                htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index152 + 1) + "AA", programmingBlock_CPP[A_Index152]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CPP != 0) {
            for (let A_Index153 = 0; A_Index153 < COUNT_programmingBlock_CPP + 0; A_Index153++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index153 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCPP + Chr(10) + programmingBlock_CPP[A_Index153] + Chr(10) + keyWordCodeInTheTranspiledLangEndCPP);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index153 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "py") {
        if (COUNT_programmingBlock_PY != 0) {
            for (let A_Index154 = 0; A_Index154 < COUNT_programmingBlock_PY + 0; A_Index154++) {
                htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index154 + 1) + "AA", programmingBlock_PY[A_Index154]);
            }
        }
    } else {
        if (COUNT_programmingBlock_PY != 0) {
            for (let A_Index155 = 0; A_Index155 < COUNT_programmingBlock_PY + 0; A_Index155++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index155 + 1) + "AA", keyWordCodeInTheTranspiledLangStartPY + Chr(10) + programmingBlock_PY[A_Index155] + Chr(10) + keyWordCodeInTheTranspiledLangEndPY);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index155 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "js") {
        if (COUNT_programmingBlock_JS != 0) {
            for (let A_Index156 = 0; A_Index156 < COUNT_programmingBlock_JS + 0; A_Index156++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index156 + 1) + "AA", programmingBlock_JS[A_Index156]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JS != 0) {
            for (let A_Index157 = 0; A_Index157 < COUNT_programmingBlock_JS + 0; A_Index157++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index157 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJS + Chr(10) + programmingBlock_JS[A_Index157] + Chr(10) + keyWordCodeInTheTranspiledLangEndJS);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index157 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "go") {
        if (COUNT_programmingBlock_GO != 0) {
            for (let A_Index158 = 0; A_Index158 < COUNT_programmingBlock_GO + 0; A_Index158++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index158 + 1) + "AA", programmingBlock_GO[A_Index158]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GO != 0) {
            for (let A_Index159 = 0; A_Index159 < COUNT_programmingBlock_GO + 0; A_Index159++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index159 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGO + Chr(10) + programmingBlock_GO[A_Index159] + Chr(10) + keyWordCodeInTheTranspiledLangEndGO);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index159 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "lua") {
        if (COUNT_programmingBlock_LUA != 0) {
            for (let A_Index160 = 0; A_Index160 < COUNT_programmingBlock_LUA + 0; A_Index160++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index160 + 1) + "AA", programmingBlock_LUA[A_Index160]);
            }
        }
    } else {
        if (COUNT_programmingBlock_LUA != 0) {
            for (let A_Index161 = 0; A_Index161 < COUNT_programmingBlock_LUA + 0; A_Index161++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index161 + 1) + "AA", keyWordCodeInTheTranspiledLangStartLUA + Chr(10) + programmingBlock_LUA[A_Index161] + Chr(10) + keyWordCodeInTheTranspiledLangEndLUA);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index161 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "cs") {
        if (COUNT_programmingBlock_CS != 0) {
            for (let A_Index162 = 0; A_Index162 < COUNT_programmingBlock_CS + 0; A_Index162++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index162 + 1) + "AA", programmingBlock_CS[A_Index162]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CS != 0) {
            for (let A_Index163 = 0; A_Index163 < COUNT_programmingBlock_CS + 0; A_Index163++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index163 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCS + Chr(10) + programmingBlock_CS[A_Index163] + Chr(10) + keyWordCodeInTheTranspiledLangEndCS);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index163 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "java") {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (let A_Index164 = 0; A_Index164 < COUNT_programmingBlock_JAVA + 0; A_Index164++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index164 + 1) + "AA", programmingBlock_JAVA[A_Index164]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (let A_Index165 = 0; A_Index165 < COUNT_programmingBlock_JAVA + 0; A_Index165++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index165 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJAVA + Chr(10) + programmingBlock_JAVA[A_Index165] + Chr(10) + keyWordCodeInTheTranspiledLangEndJAVA);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index165 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "kt") {
        if (COUNT_programmingBlock_KT != 0) {
            for (let A_Index166 = 0; A_Index166 < COUNT_programmingBlock_KT + 0; A_Index166++) {
                htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index166 + 1) + "AA", programmingBlock_KT[A_Index166]);
            }
        }
    } else {
        if (COUNT_programmingBlock_KT != 0) {
            for (let A_Index167 = 0; A_Index167 < COUNT_programmingBlock_KT + 0; A_Index167++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index167 + 1) + "AA", keyWordCodeInTheTranspiledLangStartKT + Chr(10) + programmingBlock_KT[A_Index167] + Chr(10) + keyWordCodeInTheTranspiledLangEndKT);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index167 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "rb") {
        if (COUNT_programmingBlock_RB != 0) {
            for (let A_Index168 = 0; A_Index168 < COUNT_programmingBlock_RB + 0; A_Index168++) {
                htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index168 + 1) + "AA", programmingBlock_RB[A_Index168]);
            }
        }
    } else {
        if (COUNT_programmingBlock_RB != 0) {
            for (let A_Index169 = 0; A_Index169 < COUNT_programmingBlock_RB + 0; A_Index169++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index169 + 1) + "AA", keyWordCodeInTheTranspiledLangStartRB + Chr(10) + programmingBlock_RB[A_Index169] + Chr(10) + keyWordCodeInTheTranspiledLangEndRB);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index169 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "nim") {
        if (COUNT_programmingBlock_NIM != 0) {
            for (let A_Index170 = 0; A_Index170 < COUNT_programmingBlock_NIM + 0; A_Index170++) {
                htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index170 + 1) + "AA", programmingBlock_NIM[A_Index170]);
            }
        }
    } else {
        if (COUNT_programmingBlock_NIM != 0) {
            for (let A_Index171 = 0; A_Index171 < COUNT_programmingBlock_NIM + 0; A_Index171++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index171 + 1) + "AA", keyWordCodeInTheTranspiledLangStartNIM + Chr(10) + programmingBlock_NIM[A_Index171] + Chr(10) + keyWordCodeInTheTranspiledLangEndNIM);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index171 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "ahk") {
        if (COUNT_programmingBlock_AHK != 0) {
            for (let A_Index172 = 0; A_Index172 < COUNT_programmingBlock_AHK + 0; A_Index172++) {
                htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index172 + 1) + "AA", programmingBlock_AHK[A_Index172]);
            }
        }
    } else {
        if (COUNT_programmingBlock_AHK != 0) {
            for (let A_Index173 = 0; A_Index173 < COUNT_programmingBlock_AHK + 0; A_Index173++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index173 + 1) + "AA", keyWordCodeInTheTranspiledLangStartAHK + Chr(10) + programmingBlock_AHK[A_Index173] + Chr(10) + keyWordCodeInTheTranspiledLangEndAHK);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index173 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "swift") {
        if (COUNT_programmingBlock_SWIFT != 0) {
            for (let A_Index174 = 0; A_Index174 < COUNT_programmingBlock_SWIFT + 0; A_Index174++) {
                htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index174 + 1) + "AA", programmingBlock_SWIFT[A_Index174]);
            }
        }
    } else {
        if (COUNT_programmingBlock_SWIFT != 0) {
            for (let A_Index175 = 0; A_Index175 < COUNT_programmingBlock_SWIFT + 0; A_Index175++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index175 + 1) + "AA", keyWordCodeInTheTranspiledLangStartSWIFT + Chr(10) + programmingBlock_SWIFT[A_Index175] + Chr(10) + keyWordCodeInTheTranspiledLangEndSWIFT);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index175 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "dart") {
        if (COUNT_programmingBlock_DART != 0) {
            for (let A_Index176 = 0; A_Index176 < COUNT_programmingBlock_DART + 0; A_Index176++) {
                htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index176 + 1) + "AA", programmingBlock_DART[A_Index176]);
            }
        }
    } else {
        if (COUNT_programmingBlock_DART != 0) {
            for (let A_Index177 = 0; A_Index177 < COUNT_programmingBlock_DART + 0; A_Index177++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index177 + 1) + "AA", keyWordCodeInTheTranspiledLangStartDART + Chr(10) + programmingBlock_DART[A_Index177] + Chr(10) + keyWordCodeInTheTranspiledLangEndDART);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index177 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "ts") {
        if (COUNT_programmingBlock_TS != 0) {
            for (let A_Index178 = 0; A_Index178 < COUNT_programmingBlock_TS + 0; A_Index178++) {
                htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index178 + 1) + "AA", programmingBlock_TS[A_Index178]);
            }
        }
    } else {
        if (COUNT_programmingBlock_TS != 0) {
            for (let A_Index179 = 0; A_Index179 < COUNT_programmingBlock_TS + 0; A_Index179++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index179 + 1) + "AA", keyWordCodeInTheTranspiledLangStartTS + Chr(10) + programmingBlock_TS[A_Index179] + Chr(10) + keyWordCodeInTheTranspiledLangEndTS);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index179 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "groovy") {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (let A_Index180 = 0; A_Index180 < COUNT_programmingBlock_GROOVY + 0; A_Index180++) {
                htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index180 + 1) + "AA", programmingBlock_GROOVY[A_Index180]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (let A_Index181 = 0; A_Index181 < COUNT_programmingBlock_GROOVY + 0; A_Index181++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index181 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGROOVY + Chr(10) + programmingBlock_GROOVY[A_Index181] + Chr(10) + keyWordCodeInTheTranspiledLangEndGROOVY);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index181 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    //;;;;;;;;;;
    if (langToConvertTo == langFileExtension_2) {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (let A_Index182 = 0; A_Index182 < COUNT_programmingBlock_HTVM + 0; A_Index182++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index182 + 1) + "AA", programmingBlock_HTVM[A_Index182]);
            }
        }
    } else {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (let A_Index183 = 0; A_Index183 < COUNT_programmingBlock_HTVM + 0; A_Index183++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index183 + 1) + "AA", Chr(10));
            }
        }
    }
    areWeInAFuncFromInstructions = 0;
    areWeInAFuncFromInstructionsLineNum = 0;
    var funcLangHolder = "";
    var funcNameHolder = "";
    var funcLibsHolder = "";
    var funcFuncHolder = "";
    var funcDescriptionHolder = "";
    let allFuncLang = [];
    let allFuncNames = [];
    let allFuncLibs = [];
    let allFuncs = [];
    let allfuncDescription = [];
    var correctLang = 0;
    items184 = LoopParseFunc(instructions, "\n", "\r")
    for (let A_Index184 = 0; A_Index184 < items184.length + 0; A_Index184++) {
        const A_LoopField184 = items184[A_Index184 - 0];
        if (Trim(A_LoopField184) == "funcEND======================funcEND==============") {
            areWeInAFuncFromInstructions = 0;
            areWeInAFuncFromInstructionsLineNum = 0;
            if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                //MsgBox, % funcFuncHolder
                HTVM_Append(allFuncs, funcFuncHolder);
            }
            correctLang = 0;
            funcFuncHolder = "";
        }
        if (areWeInAFuncFromInstructions == 1) {
            if (areWeInAFuncFromInstructionsLineNum == 1) {
                // name of the func
                funcLangHolder = StringTrimLeft(A_LoopField184, 5);
                if (Trim(funcLangHolder) == langToConvertTo) {
                    HTVM_Append(allFuncLang, Trim(funcLangHolder));
                    correctLang = 1;
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 2) {
                // name of the func
                funcNameHolder = StringTrimLeft(A_LoopField184, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    HTVM_Append(allFuncNames, Trim(funcNameHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 3) {
                // all libs
                funcLibsHolder = StringTrimLeft(A_LoopField184, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    HTVM_Append(allFuncLibs, Trim(funcLibsHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 4) {
                // func description
                funcDescriptionHolder = StringTrimLeft(A_LoopField184, 12);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    HTVM_Append(allfuncDescription, Trim(funcDescriptionHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum >= 5) {
                // the full func
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    funcFuncHolder += A_LoopField184 + Chr(10);
                }
            }
            //MsgBox, % A_LoopField184
            areWeInAFuncFromInstructionsLineNum++;
        }
        if (Trim(A_LoopField184) == "func======================func==============") {
            areWeInAFuncFromInstructions = 1;
            areWeInAFuncFromInstructionsLineNum = 1;
            correctLang = 0;
        }
    }
    //~ MsgBox, ===========================================================================
    //~ msgbox, % allFuncNames
    //~ MsgBox, ===========================================================================
    //~ msgbox, % allFuncLibs
    //~ MsgBox, ===========================================================================
    //~ msgbox, % allFuncLang
    //~ MsgBox, ===========================================================================
    //~ msgbox, % allFuncs
    //~ MsgBox, ===========================================================================
    if (isNotHTVMfile2 == 0) {
        if (langToConvertTo == "cpp") {
            htCode = htCode + Chr(10) + "    return 0;" + Chr(10) + "}";
            htCode = StrReplace(htCode, "int main(int argc, char* argv[]);", "int main(int argc, char* argv[])");
        }
        if (langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
            htCode = htCode + "\n}\nmain();";
            htCode = StrReplace(htCode, "async function main();", "async function main()");
            htCode = StrReplace(htCode, "function async function main()", "async function main()");
        }
        if (langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
            htCode = htCode + "\n}\nmain();";
            htCode = StrReplace(htCode, "async function main(): Promise<void>;", "async function main(): Promise<void>");
            htCode = StrReplace(htCode, "function async function main(): Promise<void>", "async function main(): Promise<void>");
        }
        if (langToConvertTo == "go") {
            htCode = htCode + "\n}";
            htCode = StrReplace(htCode, "func main();", "func main()");
        }
        if (langToConvertTo == "cs") {
            htCode = htCode + Chr(10) + "}" + Chr(10) + "}";
            htCode = StrReplace(htCode, "static void Main(string[] args);", "static void Main(string[] args)");
        }
        if (langToConvertTo == "java") {
            htCode = htCode + Chr(10) + "}" + Chr(10) + "}";
            htCode = StrReplace(htCode, "public static void main(String[] args);", "public static void main(String[] args)");
        }
        if (langToConvertTo == "kt") {
            htCode = htCode + "\n}";
            htCode = StrReplace(htCode, "fun main(args: Array<String>);", "fun main(args: Array<String>)");
        }
        if (langToConvertTo == "swift") {
            htCode = htCode + "\n}\nmain()";
            htCode = StrReplace(htCode, "func main();", "func main()");
            htCode = StrReplace(htCode, "func main() ->", "func main()");
        }
        if (langToConvertTo == "dart") {
            htCode = htCode + "\n}";
            htCode = StrReplace(htCode, "void main(List<String> arguments);", "void main(List<String> arguments)");
        }
    }
    var jsHTMLdownCode = "</script>" + Chr(10) + "</body>" + Chr(10) + "</html>";
    var includeLibsInCppIf = 0;
    var allFuncsToPutAtTop = Chr(10);
    var allLibsToPutAtTop = "";
    if (!(HTVM_Size(allFuncNames) <= 0)) {
        for (let A_Index185 = 0; A_Index185 < HTVM_Size(allFuncNames) + 0; A_Index185++) {
            if (InStr(htCode, allFuncNames[A_Index185]) + "(") {
                //MsgBox, % allFuncNames[A_Index185]
                allFuncsToPutAtTop += allFuncs[A_Index185] + Chr(10);
                if (Trim(allFuncLibs[A_Index185]) != "null") {
                    allLibsToPutAtTop += allFuncLibs[A_Index185] + "|";
                }
            }
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTop, 1);
        var allLibsToPutAtTopTEMP;
        items186 = LoopParseFunc(allLibsToPutAtTop, "|")
        for (let A_Index186 = 0; A_Index186 < items186.length + 0; A_Index186++) {
            const A_LoopField186 = items186[A_Index186 - 0];
            allLibsToPutAtTopTEMP += A_LoopField186 + Chr(10);
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTopTEMP, 1);
        includeLibsInCppIf = 1;
        if (langToConvertTo == "cpp") {
            allLibsToPutAtTop = "#include <iostream>\n#include <sstream>\n#include <string>\n#include <cstdint>\n#include <algorithm>\n#include <vector>\n#include <any>\n#include <optional>\n" + allLibsToPutAtTop;
        }
        if (langToConvertTo == "cs") {
            allLibsToPutAtTop = "using System;\nusing System.Collections.Generic;\n" + allLibsToPutAtTop;
        }
        allLibsToPutAtTop = Sort(allLibsToPutAtTop, "U");
        allLibsToPutAtTop = StrReplace(allLibsToPutAtTop, "~~~", Chr(10));
        if (isNotHTVMfileEXTRA_INT == 1) {
            isNotHTVMfileEXTRA_LIB_INFO = allLibsToPutAtTop;
            isNotHTVMfileEXTRA_FUNCS_INFO = allFuncsToPutAtTop;
        }
        if (isNotHTVMfile2 == 0) {
            if (langToConvertTo == "cs" || langToConvertTo == "java") {
                htCode = Chr(10) + allFuncsToPutAtTop + Chr(10) + htCode;
            } else {
                if (langToConvertTo != "js") {
                    htCode = allLibsToPutAtTop + Chr(10) + allFuncsToPutAtTop + Chr(10) + htCode;
                } else {
                    if (useJavaScriptInAfullHTMLfile == "on") {
                        htCode = allLibsToPutAtTop + Chr(10) + allFuncsToPutAtTop + Chr(10) + htCode;
                    } else {
                        htCode = Chr(10) + allFuncsToPutAtTop + Chr(10) + htCode;
                    }
                }
            }
        }
        if (langToConvertTo == "cs") {
            htCode = allLibsToPutAtTop + Chr(10) + "class Program" + Chr(10) + "{" + Chr(10) + htCode;
        }
        if (langToConvertTo == "java") {
            htCode = allLibsToPutAtTop + Chr(10) + "import java.util.ArrayList;" + Chr(10) + "import java.util.List;" + Chr(10) + "import java.util.regex.Pattern;" + Chr(10) + "import java.util.*;" + Chr(10) + "public class Main" + Chr(10) + "{" + Chr(10) + htCode;
        }
        if (langToConvertTo == "go") {
            htCode = "package main" + Chr(10) + "import (" + Chr(10) + htCode;
        }
    }
    for (let A_Index187 = 0; A_Index187 < theIdNumOfThe34 + 0; A_Index187++) {
        if (theIdNumOfThe34 == A_Index187 + 1) {
            if (langToConvertTo == langFileExtension_2) {
                if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index187 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index187 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                } else {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index187 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index187 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                }
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index187 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index187 + 1], keyWordEscpaeChar, "\\") + Chr(34));
            }
        } else {
            if (langToConvertTo == langFileExtension_2) {
                if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index187 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index187 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2));
                } else {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index187 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index187 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2));
                }
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index187 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index187 + 1], keyWordEscpaeChar, "\\"));
            }
        }
    }
    if (langToConvertTo == langFileExtension_2) {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, keyWordEscpaeChar_2 + Chr(34));
    } else {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, Chr(92) + Chr(34));
    }
    htCode = StrReplace(htCode, "std::string(" + Chr(34) + Chr(34) + ";),", "std::string(" + Chr(34) + Chr(34) + "),");
    var jsHTMLupCode = "<!doctype html>" + Chr(10) + "<html lang=" + Chr(34) + "en" + Chr(34) + ">" + Chr(10) + "    <head>\n        <meta charset=" + Chr(34) + "UTF-8" + Chr(34) + " />" + Chr(10) + "        <meta name=" + Chr(34) + "viewport" + Chr(34) + " content=" + Chr(34) + "width=device-width, initial-scale=1.0" + Chr(34) + " />" + Chr(10) + "        <title>HTVM</title>" + Chr(10) + "        <style>" + Chr(10) + "            body {" + Chr(10) + "                background-color: #202020;" + Chr(10) + "                font-family:" + Chr(10) + "                    " + Chr(34) + "Open Sans" + Chr(34) + "," + Chr(10) + "                    -apple-system," + Chr(10) + "                    BlinkMacSystemFont," + Chr(10) + "                    " + Chr(34) + "Segoe UI" + Chr(34) + "," + Chr(10) + "                    Roboto," + Chr(10) + "                    Oxygen-Sans," + Chr(10) + "                    Ubuntu," + Chr(10) + "                    Cantarell," + Chr(10) + "                    " + Chr(34) + "Helvetica Neue" + Chr(34) + "," + Chr(10) + "                    Helvetica," + Chr(10) + "                    Arial," + Chr(10) + "                    sans-serif;" + Chr(10) + "            }" + Chr(10) + "        </style>" + Chr(10) + allLibsToPutAtTop + Chr(10) + "</head>" + Chr(10) + "    <body>\n<script>";
    if (isNotHTVMfile2 == 0) {
        if (useJavaScriptInAfullHTMLfile == "on" && langToConvertTo == "js") {
            htCode = jsHTMLupCode + Chr(10) + htCode + Chr(10) + jsHTMLdownCode;
        }
        if (langToConvertTo == "cpp" && includeLibsInCppIf == 0) {
            htCode = "#include <iostream>" + Chr(10) + "#include <sstream>" + Chr(10) + "#include <any>" + Chr(10) + "#include <string>" + Chr(10) + "#include <cstdint>" + Chr(10) + "#include <algorithm>" + Chr(10) + "#include <vector>" + Chr(10) +  Chr(10) + htCode;
        }
        if (langToConvertTo == "cs") {
            htCode = Chr(10) + htCode;
        }
        if (langToConvertTo == "ahk") {
            htCode = "#EscapeChar \\" + Chr(10) + htCode;
        }
        if (langToConvertTo == "swift") {
            htCode = "import Foundation" + Chr(10) + htCode;
        }
        if (langToConvertTo == langFileExtension_2) {
            if (SubStr(htCode, 1, 1) == Chr(10)) {
                htCode = StringTrimLeft(htCode, 1);
            }
        }
    }
    //print(htCode)
    return htCode;
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
function HTVMv2() {
    var argCODE = "";
    var argCODEfile = "";
    var argHTVMinstr = "";
    var argLangTo = "";
    var OUTCODE = "null";
    var numOfParams = 0;
    HTVM_v2_HTVM();
    if (noParams == true) {
        return;
    }
    items188 = LoopParseFunc(str0)
    for (let A_Index188 = 0; A_Index188 < items188.length + 0; A_Index188++) {
        const A_LoopField188 = items188[A_Index188 - 0];
        str00 = Trim(A_LoopField188);
        str00 = StringTrimRight(str00, 1);
    }
    //print("HTVM v2")
    if (HTVM_getLang_HTVM() == "cpp" || HTVM_getLang_HTVM() == "py") {
        if (HTVM_getLang_HTVM() == "cpp") {
            //print("CPP")
        }
        if (HTVM_getLang_HTVM() == "py") {
            //print("PY")
        }
        items189 = LoopParseFunc(allArgs, "\n", "\r")
        for (let A_Index189 = 0; A_Index189 < items189.length + 0; A_Index189++) {
            const A_LoopField189 = items189[A_Index189 - 0];
            if (A_Index189 == 0) {
                numOfParams++;
                argCODE = FileRead(Trim(A_LoopField189));
                argCODEfile = Trim(A_LoopField189);
            }
            else if (A_Index189 == 1) {
                numOfParams++;
                argHTVMinstr = Trim(A_LoopField189);
            }
            else if (A_Index189 == 2) {
                numOfParams++;
                argLangTo = Trim(A_LoopField189);
            } else {
                numOfParams++;
                HTVM_Append(argHTVMinstrMORE, Trim(A_LoopField189));
            }
        }
        //print("===============123431234===========start=====")
        for (let A_Index190 = 0; A_Index190 < HTVM_Size(argHTVMinstrMORE) + 0; A_Index190++) {
            //print(argHTVMinstrMORE[A_Index190])
        }
        //print("===============123431234==========end======")
        //print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) . langToConvertTo)
        if (SubStrLastChars(argCODEfile, 4) == ".cpp" || SubStrLastChars(argCODEfile, 3) == ".py" || SubStrLastChars(argCODEfile, 3) == ".js" || SubStrLastChars(argCODEfile, 3) == ".go" || SubStrLastChars(argCODEfile, 4) == ".lua" || SubStrLastChars(argCODEfile, 3) == ".cs" || SubStrLastChars(argCODEfile, 5) == ".java" || SubStrLastChars(argCODEfile, 3) == ".kt" || SubStrLastChars(argCODEfile, 3) == ".rb" || SubStrLastChars(argCODEfile, 4) == ".nim" || SubStrLastChars(argCODEfile, 4) == ".ahk" || SubStrLastChars(argCODEfile, 6) == ".swift" || SubStrLastChars(argCODEfile, 5) == ".dart" || SubStrLastChars(argCODEfile, 3) == ".ts" || SubStrLastChars(argCODEfile, 7) == ".groovy" || SubStrLastChars(argCODEfile, StrLen("." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), Chr(10), 2)))) == "." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), Chr(10), 2)) && numOfParams == 2) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (SubStrLastChars(argCODEfile, 4) == ".cpp") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "cpp");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".py") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "py");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".js") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "js");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".go") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "go");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 4) == ".lua") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "lua");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".cs") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "cs");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 5) == ".java") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "java");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".kt") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "kt");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".rb") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "rb");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 4) == ".nim") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "nim");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 4) == ".ahk") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "ahk");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 6) == ".swift") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "swift");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 5) == ".dart") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "dart");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".ts") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "ts");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 7) == ".groovy") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "groovy");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, StrLen("." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), Chr(10), 2)))) == "." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), Chr(10), 2))) {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), Chr(10), 2)));
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            } else {
                //print("INVALID LANG!!!")
                return;
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        } else {
            if (argLangTo != "") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "full", argLangTo);
            } else {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "full");
            }
        }
        print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        if (langToConvertTo == "js" && useJavaScriptInAfullHTMLfile == "on") {
            FileDelete(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + "html");
            FileAppend(OUTCODE, StringTrimRight(argCODEfile, StrLen(langFileExtension)) + "html");
        } else {
            FileDelete(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
            FileAppend(OUTCODE, StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        }
    }
    if (HTVM_getLang_HTVM() == "js") {
        //print("JS")
    }
}
HTVMv2();
