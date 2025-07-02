

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
var keyWordProc = "";
var keyWordStruct = "";
var keyWordProp = "";
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
var keyWordProc_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordStruct_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
var keyWordProp_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
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
var availableFuncsInHTVMInHTVM = "";
var saveAllArrayVarNamesSoWeCanDoAfix = "|";
var initializeBackendAndGUIInteractionWithLabelSubroutineLikeButConvertsToFunction_WAS_IN_PYTHON = 0;
let weAreInMLSarr = [];
let ospDic = [];
let ospDic1 = [];
let ospDic2 = [];
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function SubStrLastChars(text, numOfChars) {
    var LastOut = "";
    var NumOfChars = 0;
    let items1 = LoopParseFunc(text);
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        NumOfChars++;
    }
    for (let A_Index2 = 0; A_Index2 < numOfChars + 0; A_Index2++) {
        NumOfChars--;
    }
    let items3 = LoopParseFunc(text);
    for (let A_Index3 = 0; A_Index3 < items3.length + 0; A_Index3++) {
        const A_LoopField3 = items3[A_Index3 - 0];
        if (A_Index3 >= NumOfChars) {
            LastOut += A_LoopField3;
        }
    }
    return LastOut;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function fixCSandJAVAstaticBugForFunc(line) {
    var out = "";
    var haveWeSeenMainFunc = 0;
    let items4 = LoopParseFunc(line, "\n", "\r");
    for (let A_Index4 = 0; A_Index4 < items4.length + 0; A_Index4++) {
        const A_LoopField4 = items4[A_Index4 - 0];
        if (haveWeSeenMainFunc == 0 && InStr(A_LoopField4, "    static ")) {
            out += StrReplace(A_LoopField4, "    static ", "    ") + Chr(10);
        } else {
            out += A_LoopField4 + Chr(10);
        }
        if (InStr(StrLower(A_LoopField4), " main(")) {
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
        for (let A_Index5 = 0; A_Index5 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint8) + 0; A_Index5++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint8[A_Index5]) == Trim(varName)) {
                if (langToConvertTo == "java") {
                    out = "(byte) " + line;
                }
                if (langToConvertTo == "kt") {
                    out = line + "u";
                }
            }
        }
        for (let A_Index6 = 0; A_Index6 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint16) + 0; A_Index6++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint16[A_Index6]) == Trim(varName)) {
                if (langToConvertTo == "java") {
                    out = "(short) " + line;
                }
                if (langToConvertTo == "kt") {
                    out = line + "u";
                }
            }
        }
        for (let A_Index7 = 0; A_Index7 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint32) + 0; A_Index7++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint32[A_Index7]) == Trim(varName)) {
                if (langToConvertTo == "kt") {
                    out = line + "u";
                }
                if (langToConvertTo == "nim") {
                    out = line + "'u32";
                }
            }
        }
        for (let A_Index8 = 0; A_Index8 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_uint64) + 0; A_Index8++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_uint64[A_Index8]) == Trim(varName)) {
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
        for (let A_Index9 = 0; A_Index9 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_int64) + 0; A_Index9++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_int64[A_Index9]) == Trim(varName)) {
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
        for (let A_Index10 = 0; A_Index10 < HTVM_Size(allVarsSoWeDontReDecVars_FIX_float) + 0; A_Index10++) {
            if (Trim(allVarsSoWeDontReDecVars_FIX_float[A_Index10]) == Trim(varName)) {
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
    theCodeCommands = Trim(theCodeCommands);
    theCodeCommands = StrReplace(theCodeCommands, "%", "");
    theCodeCommands = StrReplace(theCodeCommands, "| ", "|");
    theCodeCommands = StrReplace(theCodeCommands, ", ", ",");
    if (SubStrLastChars(theCodeCommands, 1) == "|") {
        theCodeCommands = StringTrimRight(theCodeCommands, 1);
    }
    if (mode == "check") {
        let items11 = LoopParseFunc(keyWordsCommands, "|");
        for (let A_Index11 = 0; A_Index11 < items11.length + 0; A_Index11++) {
            const A_LoopField11 = items11[A_Index11 - 0];
            let items12 = LoopParseFunc(A_LoopField11, ",");
            for (let A_Index12 = 0; A_Index12 < items12.length + 0; A_Index12++) {
                const A_LoopField12 = items12[A_Index12 - 0];
                if (A_Index12 == 0) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField12 + ",")) == StrLower(A_LoopField12 + ",")) {
                        //MsgBox, true
                        return "true";
                    }
                }
                if (A_Index12 == 0) {
                    if (theCodeCommands == A_LoopField12) {
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
        let items13 = LoopParseFunc(keyWordsCommands, "|");
        for (let A_Index13 = 0; A_Index13 < items13.length + 0; A_Index13++) {
            const A_LoopField13 = items13[A_Index13 - 0];
            AIndex = A_Index13;
            let items14 = LoopParseFunc(A_LoopField13, ",");
            for (let A_Index14 = 0; A_Index14 < items14.length + 0; A_Index14++) {
                const A_LoopField14 = items14[A_Index14 - 0];
                if (A_Index14 == 0) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField14 + ",")) == StrLower(A_LoopField14 + ",")) {
                        //MsgBox, true
                        keyWordsCommandsNumLine = AIndex;
                        break;
                    }
                }
                if (A_Index14 == 0) {
                    //MsgBox, %theCodeCommands% = %A_LoopField%
                    if (theCodeCommands == A_LoopField14) {
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
        var assignmentOperatorKeyWord = "=";
        if (langToConvertTo == langFileExtension_2) {
            assignmentOperatorKeyWord = keyWordAssign_2;
        }
        else if (langToConvertTo == "ahk") {
            assignmentOperatorKeyWord = ":=";
        } else {
            assignmentOperatorKeyWord = "=";
        }
        let theCodeCommand = [];
        theCodeCommands = Trim(theCodeCommands);
        let items15 = LoopParseFunc(theCodeCommands, ",");
        for (let A_Index15 = 0; A_Index15 < items15.length + 0; A_Index15++) {
            const A_LoopField15 = items15[A_Index15 - 0];
            HTVM_Append(theCodeCommand, Trim(A_LoopField15));
            //MsgBox, % A_LoopField
        }
        let items16 = LoopParseFunc(keyWordsCommands, "|");
        for (let A_Index16 = 0; A_Index16 < items16.length + 0; A_Index16++) {
            const A_LoopField16 = items16[A_Index16 - 0];
            if (keyWordsCommandsNumLine == A_Index16) {
                //MsgBox, % A_LoopField
                let items17 = LoopParseFunc(A_LoopField16, ",");
                for (let A_Index17 = 0; A_Index17 < items17.length + 0; A_Index17++) {
                    const A_LoopField17 = items17[A_Index17 - 0];
                    if (A_Index17 == 0) {
                        outConstuctTheOutFromTheCommandsFucnName = A_LoopField17;
                    }
                    else if (A_Index17 == 1) {
                        //MsgBox, % A_LoopField
                        if (A_LoopField17 == "lineTranspile") {
                            outConstuctTheOutFromTheCommandsLineTranspile = 1;
                        }
                        if (A_LoopField17 == "OUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField17 == "INOUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField17 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField17, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    }
                    else if (A_Index17 == 2) {
                        if (outConstuctTheOutFromTheCommandsLineTranspile == 1) {
                            outConstuctTheOutFromTheCommandsLineTranspileText = A_LoopField17;
                        }
                        if (A_LoopField17 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField17, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    } else {
                        //MsgBox, % theCodeCommand[theCodeCommandNum]
                        if (InStr(A_LoopField17, Chr(39))) {
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
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " " + assignmentOperatorKeyWord + " " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ")" + semicolon;
            } else {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " " + assignmentOperatorKeyWord + " " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ", " + outConstuctTheOutFromTheCommandsParams + ")" + semicolon;
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
            outConstuctTheOutFromTheCommands = StrReplace(outConstuctTheOutFromTheCommandsLineTranspileText, "~~~", Chr(10));
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
    let items18 = LoopParseFunc(line);
    for (let A_Index18 = 0; A_Index18 < items18.length + 0; A_Index18++) {
        const A_LoopField18 = items18[A_Index18 - 0];
        HTVM_Append(lineArr, A_LoopField18);
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
    // char1 is for text outside the start
    var char1 = "";
    // char2 is for text inside the start
    var char2 = "";
    // char3 is for text inside the end
    var char3 = "";
    // char4 is for text outside the end
    var char4 = "";
    var isMatch = 0;
    sildingLine = "";
    isStart = 1;
    i1 = 0;
    hasFound = 0;
    hasFound2 = 0;
    isStartTrue = 0;
    isEndTrue = 0;
    for (let A_Index19 = 0; A_Index19 < HTVM_Size(lineArr) + 0; A_Index19++) {
        char1 = "";
        char2 = "";
        char3 = "";
        char4 = "";
        isMatch = 0;
        if (A_Index19 != 0) {
            isStart = 0;
        }
        sildingLine = "";
        for (let A_Index20 = 0; A_Index20 < matchStringLEN + 0; A_Index20++) {
            if (A_Index20 + i1 <= HTVM_Size(lineArr) - 1) {
                sildingLine += lineArr[A_Index20 + i1];
            }
        }
        if (StrLen(sildingLine) < matchStringLEN) {
            break;
        }
        //print("!!!!111111111!!!!!!: " . sildingLine)
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;==================
        if (sildingLine == matchString) {
            hasFound = 1;
            if (isStart != 1) {
                //print("!!!!2222222222!!!!!!: " . lineArr[i1 - 1])
                char1 = lineArr[i1 - 1];
                //print("!!!!2222222222.555555555!!!!!!: " . lineArr[i1])
                char2 = lineArr[i1];
            } else {
                isStartTrue = 1;
            }
            if (i1 + matchStringLEN < HTVM_Size(lineArr)) {
                //print("!!!!3333333333.5555555555!!!!!!: " . lineArr[i1 + matchStringLEN - 1])
                char3 = lineArr[i1 + matchStringLEN - 1];
                //print("!!!!3333333333!!!!!!: " . lineArr[i1 + matchStringLEN])
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
        //;;;;;;;;;;;;;;;;;;;===============
        if (isMatch == 1) {
            if (HTVM_Size(allPosForReplacing) > 0) {
                for (let A_Index21 = 0; A_Index21 < HTVM_Size(allPosForReplacing) + 0; A_Index21++) {
                    if (i1 + 1 != allPosForReplacing[A_Index21]) {
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
    //print(allPosForReplacing)
    if (HTVM_Size(allPosForReplacing) > 0) {
        // matchStringLEN
        // replaceStringLEN
        var l2 = 0;
        var currentPos = 0;
        var onceEnd = 0;
        for (let A_Index22 = 0; A_Index22 < HTVM_Size(allPosForReplacing) + 0; A_Index22++) {
            if (A_Index22 == 0) {
                currentPos = allPosForReplacing[A_Index22];
            } else {
                currentPos = allPosForReplacing[A_Index22] - (matchStringLEN - replaceStringLEN);
            }
            onceEnd = 0;
            let items23 = LoopParseFunc(lineOut);
            for (let A_Index23 = 0; A_Index23 < items23.length + 0; A_Index23++) {
                const A_LoopField23 = items23[A_Index23 - 0];
                if (A_Index23 + 2 > currentPos && A_Index23 + 1 < currentPos + matchStringLEN) {
                    onceEnd++;
                    //print("DDDDDDDDDDD" . STR(A_Index))
                    if (onceEnd == 1) {
                        lineTEMP += replaceString;
                    }
                } else {
                    lineTEMP += A_LoopField23;
                }
            }
            lineOut = lineTEMP;
            lineTEMP = "";
            //print(lineTEMP)
            l2++;
        }
    } else {
        return line;
    }
    return lineOut;
}
function ExtractDigits(inputString) {
    var digits = "";
    let items24 = LoopParseFunc(inputString);
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
    let items26 = LoopParseFunc(string123);
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
    let items27 = LoopParseFunc(input);
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
    let items28 = LoopParseFunc(strippedString);
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
    let items29 = LoopParseFunc(pythonCode, "\n", "\r");
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
    let items33 = LoopParseFunc(input_string, "\n", "\r");
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
        let items34 = LoopParseFunc(result, "\n", "\r");
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
        let items35 = LoopParseFunc(result, "\n", "\r");
        for (let A_Index35 = 0; A_Index35 < items35.length + 0; A_Index35++) {
            const A_LoopField35 = items35[A_Index35 - 0];
            HTVM_Append(lookIntoFurture, Trim(A_LoopField35));
        }
        HTVM_Append(lookIntoFurture, " ");
        var resultOut = "";
        var skipNext = 0;
        let items36 = LoopParseFunc(result, "\n", "\r");
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
        let items37 = LoopParseFunc(result, "\n", "\r");
        for (let A_Index37 = 0; A_Index37 < items37.length + 0; A_Index37++) {
            const A_LoopField37 = items37[A_Index37 - 0];
            HTVM_Append(lookIntoFurture2, Trim(A_LoopField37));
        }
        HTVM_Append(lookIntoFurture2, " ");
        resultOut = "";
        skipNext = 0;
        var addSpacesAtTheBegginig;
        let items38 = LoopParseFunc(result, "\n", "\r");
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
                    let items39 = LoopParseFunc(A_LoopField38);
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
    let items40 = LoopParseFunc(result, "\n", "\r");
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
        let items41 = LoopParseFunc(result, "\n", "\r");
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
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
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
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordElse) + " " + StrLower(keyWordCurlyBraceOpen))) == StrLower(keyWordElse) + " " + StrLower(keyWordCurlyBraceOpen)) {
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
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordLoopInfinite) + " " + StrLower(keyWordCurlyBraceOpen))) == StrLower(keyWordLoopInfinite) + " " + StrLower(keyWordCurlyBraceOpen)) {
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
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordTry) + " " + StrLower(keyWordCurlyBraceOpen))) == StrLower(keyWordTry) + " " + StrLower(keyWordCurlyBraceOpen)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordCrew))) == StrLower(keyWordCrew)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordStruct))) == StrLower(keyWordStruct)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordProc))) == StrLower(keyWordProc)) {
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
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordFinally) + " " + StrLower(keyWordCurlyBraceOpen))) == StrLower(keyWordFinally) + " " + StrLower(keyWordCurlyBraceOpen)) {
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
function fixArray1234(line) {
    var out = "";
    var started = 0;
    let items42 = LoopParseFunc(line);
    for (let A_Index42 = 0; A_Index42 < items42.length + 0; A_Index42++) {
        const A_LoopField42 = items42[A_Index42 - 0];
        if (started == 1) {
            if (StrLen(line) == A_Index42 + 1) {
                return out;
            }
            out += A_LoopField42;
        }
        if (A_LoopField42 == "(") {
            started = 1;
        }
    }
    return out;
}
function fixArray123(line, arrayProcStr, mode) {
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
function arrayParserTranspiler1(line, arrayProcStr, mode) {
    if (InStr(line, arrayProcStr) == false) {
        return line;
    }
    var out = "";
    var allDelimiters = " ()[],;:'!&|=<>+-*/^%~" + Chr(34) + Chr(9) + Chr(11);
    let arrAll = [];
    let items43 = LoopParseFunc(line);
    for (let A_Index43 = 0; A_Index43 < items43.length + 0; A_Index43++) {
        const A_LoopField43 = items43[A_Index43 - 0];
        HTVM_Append(arrAll, A_LoopField43);
    }
    var i1 = 0;
    var tempHold = "";
    var holdPos = 0;
    let holdPositions = [];
    for (let A_Index44 = 0; A_Index44 < HTVM_Size(arrAll) + 0; A_Index44++) {
        tempHold = "";
        if (HTVM_Size(arrAll) - StrLen(arrayProcStr) + 1 == i1) {
            break;
        }
        for (let A_Index45 = 0; A_Index45 < StrLen(arrayProcStr) + 0; A_Index45++) {
            tempHold += arrAll[A_Index45 + i1];
        }
        i1++;
        //print(tempHold)
        if (tempHold == arrayProcStr) {
            holdPos = i1;
            //print(holdPos)
            HTVM_Append(holdPositions, holdPos);
        }
    }
    //print("===========================================")
    var holdPositionsTEMP = 0;
    for (let A_Index46 = 0; A_Index46 < HTVM_Size(holdPositions) + 0; A_Index46++) {
        holdPositionsTEMP = holdPositions[A_Index46];
        i1 = HTVM_Size(arrAll);
        tempHold = "";
        for (let A_Index47 = 0; A_Index47 < HTVM_Size(arrAll) + 0; A_Index47++) {
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
        holdPositions[A_Index46] = holdPositions[A_Index46] - StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", "")));
    }
    //;;;;;;;;;;;;;;;;;;
    var foundFirstParenthesis = 0;
    var ParenthesisStackOPEN = 0;
    var ParenthesisStackCLOSE = 0;
    let holdPositionsEnd = [];
    holdPositionsTEMP = 0;
    for (let A_Index48 = 0; A_Index48 < HTVM_Size(holdPositions) + 0; A_Index48++) {
        holdPositionsTEMP = holdPositions[A_Index48];
        i1 = 0;
        tempHold = "";
        foundFirstParenthesis = 0;
        ParenthesisStackOPEN = 0;
        ParenthesisStackCLOSE = 0;
        for (let A_Index49 = 0; A_Index49 < HTVM_Size(arrAll) + 0; A_Index49++) {
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
    for (let A_Index50 = 0; A_Index50 < HTVM_Size(holdPositions) + 0; A_Index50++) {
        startPosReplace = holdPositions[HTVM_Size(holdPositions) - A_Index50 - 1];
        endPosReplace = holdPositionsEnd[HTVM_Size(holdPositions) - A_Index50 - 1];
        holdDebug = "";
        beenInside = 0;
        holdDebugLen = 0;
        canOut = 1;
        let items51 = LoopParseFunc(line);
        for (let A_Index51 = 0; A_Index51 < items51.length + 0; A_Index51++) {
            const A_LoopField51 = items51[A_Index51 - 0];
            if (A_Index51 + 1 >= startPosReplace && A_Index51 + 1 <= endPosReplace) {
                holdDebug += A_LoopField51;
            }
        }
        holdDebugLen = StrLen(holdDebug);
        let items52 = LoopParseFunc(line);
        for (let A_Index52 = 0; A_Index52 < items52.length + 0; A_Index52++) {
            const A_LoopField52 = items52[A_Index52 - 0];
            if (A_Index52 + 1 >= startPosReplace && A_Index52 + 1 <= endPosReplace) {
                beenInside++;
            }
            if (beenInside == 1) {
                out += fixArray123(holdDebug, arrayProcStr, mode);
                canOut = 0;
            } else {
                if (canOut == 0) {
                    holdDebugLen--;
                    if (holdDebugLen == 0) {
                        canOut = 1;
                    }
                }
                if (canOut == 1) {
                    out += A_LoopField52;
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
            theType = "float64";
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
            theType = "[]float64";
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
    let items53 = LoopParseFunc(line, " ");
    for (let A_Index53 = 0; A_Index53 < items53.length + 0; A_Index53++) {
        const A_LoopField53 = items53[A_Index53 - 0];
        line = A_LoopField53;
    }
    return line;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function OSPhelp(line, keyWorddddddddddddd) {
    let lookAhead = [];
    let items54 = LoopParseFunc(line, "\n", "\r");
    for (let A_Index54 = 0; A_Index54 < items54.length + 0; A_Index54++) {
        const A_LoopField54 = items54[A_Index54 - 0];
        HTVM_Append(lookAhead, A_LoopField54);
    }
    HTVM_Append(lookAhead, " ");
    let items55 = LoopParseFunc(line, "\n", "\r");
    for (let A_Index55 = 0; A_Index55 < items55.length + 0; A_Index55++) {
        const A_LoopField55 = items55[A_Index55 - 0];
        if (SubStr(Trim(StrLower(A_LoopField55)), 1, StrLen(keyWorddddddddddddd)) == StrLower(keyWorddddddddddddd) && lookAhead[A_Index55 + 1] == "{") {
            return true;
        }
        if (SubStr(Trim(StrLower(A_LoopField55)), 1, StrLen(keyWorddddddddddddd)) == StrLower(keyWorddddddddddddd) && lookAhead[A_Index55 + 1] == "{") {
            return true;
        }
        if (SubStr(Trim(StrLower(A_LoopField55)), 1, StrLen(StrLower(keyWorddddddddddddd))) == StrLower(keyWorddddddddddddd) && lookAhead[A_Index55 + 1] == "{") {
            return true;
        }
    }
    return false;
}
function OSP(line) {
    var lineOriginal = line;
    var outOSP = "";
    let lookAhead = [];
    let items56 = LoopParseFunc(line, "\n", "\r");
    for (let A_Index56 = 0; A_Index56 < items56.length + 0; A_Index56++) {
        const A_LoopField56 = items56[A_Index56 - 0];
        HTVM_Append(lookAhead, A_LoopField56);
    }
    HTVM_Append(lookAhead, " ");
    let stack = [];
    var inConstructOSP = 0;
    var countParentheses = 0;
    var countParenthesesStart = 0;
    var countParenthesesOfSet = 0;
    var stackRN = "";
    var alredy = 0;
    outOSP = "";
    if (OSPhelp(line, keyWordAlliance)) {
        let items57 = LoopParseFunc(line, "\n", "\r");
        for (let A_Index57 = 0; A_Index57 < items57.length + 0; A_Index57++) {
            const A_LoopField57 = items57[A_Index57 - 0];
            if (SubStr(Trim(StrLower(A_LoopField57)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance) && lookAhead[A_Index57 + 1] == "{") {
                //print(A_LoopField)
                stackRN = A_LoopField57;
                countParentheses = 0;
                countParenthesesStart = 0;
            }
            if (A_LoopField57 == "{") {
                countParentheses++;
                countParenthesesStart = 1;
            }
            if (A_LoopField57 == "}") {
                countParentheses--;
            }
            if (countParenthesesStart == 1 && countParentheses == 0) {
                // escaped
                countParentheses = 0;
                countParenthesesStart = 0;
                alredy = 1;
                outOSP += A_LoopField57 + "_HTVM-OSP-HTVM-OSP-REMOVE-OSP-HTVMv2--OSP" + Chr(10);
                countParentheses = 1;
            }
            if (alredy == 0) {
                outOSP += A_LoopField57 + "\n";
            }
            alredy = 0;
        }
        outOSP = StringTrimRight(outOSP, 1);
        line = outOSP;
    }
    inConstructOSP = 0;
    countParentheses = 0;
    countParenthesesStart = 0;
    countParenthesesOfSet = 0;
    stackRN = "";
    alredy = 0;
    outOSP = "";
    if (OSPhelp(line, keyWordCrew)) {
        let items58 = LoopParseFunc(line, "\n", "\r");
        for (let A_Index58 = 0; A_Index58 < items58.length + 0; A_Index58++) {
            const A_LoopField58 = items58[A_Index58 - 0];
            if (SubStr(Trim(StrLower(A_LoopField58)), 1, StrLen(keyWordCrew)) == StrLower(keyWordCrew) && lookAhead[A_Index58 + 1] == "{") {
                //print(A_LoopField)
                stackRN = A_LoopField58;
                countParentheses = 0;
                countParenthesesStart = 0;
            }
            if (A_LoopField58 == "{") {
                countParentheses++;
                countParenthesesStart = 1;
            }
            if (A_LoopField58 == "}") {
                countParentheses--;
            }
            if (countParenthesesStart == 1 && countParentheses == 0) {
                // escaped
                countParentheses = 0;
                countParenthesesStart = 0;
                alredy = 1;
                outOSP += A_LoopField58 + "_HTVM-OSP-HTVM-OSP-REMOVE-OSP-HTVMv2--OSP" + Chr(10);
                countParentheses = 1;
            }
            if (alredy == 0) {
                outOSP += A_LoopField58 + "\n";
            }
            alredy = 0;
        }
        outOSP = StringTrimRight(outOSP, 1);
        line = outOSP;
    }
    inConstructOSP = 0;
    countParentheses = 0;
    countParenthesesStart = 0;
    countParenthesesOfSet = 0;
    stackRN = "";
    alredy = 0;
    outOSP = "";
    if (OSPhelp(line, keyWordStruct)) {
        let items59 = LoopParseFunc(line, "\n", "\r");
        for (let A_Index59 = 0; A_Index59 < items59.length + 0; A_Index59++) {
            const A_LoopField59 = items59[A_Index59 - 0];
            if (SubStr(Trim(StrLower(A_LoopField59)), 1, StrLen(keyWordStruct)) == StrLower(keyWordStruct) && lookAhead[A_Index59 + 1] == "{") {
                //print(A_LoopField)
                stackRN = A_LoopField59;
                countParentheses = 0;
                countParenthesesStart = 0;
            }
            if (A_LoopField59 == "{") {
                countParentheses++;
                countParenthesesStart = 1;
            }
            if (A_LoopField59 == "}") {
                countParentheses--;
            }
            if (countParenthesesStart == 1 && countParentheses == 0) {
                // escaped
                countParentheses = 0;
                countParenthesesStart = 0;
                alredy = 1;
                outOSP += A_LoopField59 + "_HTVM-OSP-HTVM-OSP-REMOVE-OSP-HTVMv2--OSP" + Chr(10);
                countParentheses = 1;
            }
            if (alredy == 0) {
                outOSP += A_LoopField59 + "\n";
            }
            alredy = 0;
        }
        line = outOSP;
    }
    inConstructOSP = 0;
    countParentheses = 0;
    countParenthesesStart = 0;
    countParenthesesOfSet = 0;
    stackRN = "";
    alredy = 0;
    var inOBJ = 0;
    var tempStackText = "";
    outOSP = "";
    let items60 = LoopParseFunc(line, "\n", "\r");
    for (let A_Index60 = 0; A_Index60 < items60.length + 0; A_Index60++) {
        const A_LoopField60 = items60[A_Index60 - 0];
        if (SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordStruct)) == StrLower(keyWordStruct) && lookAhead[A_Index60 + 1] == "{") {
            str1 = Trim(StringTrimLeft(A_LoopField60, StrLen(SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordStruct)))));
            HTVM_Append(ospDic, str1);
            alredy = 2;
            inOBJ = 1;
            tempStackText = "";
            for (let A_Index61 = 0; A_Index61 < HTVM_Size(ospDic) + 0; A_Index61++) {
                tempStackText += ospDic[A_Index61] + ".";
            }
            tempStackText = StringTrimRight(tempStackText, 1);
            outOSP += "[][][][][] " + StrReplace(tempStackText, ".", "_") + " [][][][][]" + Chr(10);
        }
        if (SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordProp)) == StrLower(keyWordProp)) {
            tempStackText = "";
            for (let A_Index62 = 0; A_Index62 < HTVM_Size(ospDic) + 0; A_Index62++) {
                tempStackText += ospDic[A_Index62] + ".";
            }
            tempStackText = StringTrimRight(tempStackText, 1);
            outOSP += A_LoopField60 + "-----------------------HTVM-OSP-HTVM-OBJ--------------" + tempStackText + Chr(10);
        }
        if (SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordProc)) == StrLower(keyWordProc) && lookAhead[A_Index60 + 1] == "{") {
            tempStackText = "";
            for (let A_Index63 = 0; A_Index63 < HTVM_Size(ospDic) + 0; A_Index63++) {
                tempStackText += ospDic[A_Index63] + ".";
            }
            tempStackText = StringTrimRight(tempStackText, 1);
            alredy = 1;
            outOSP += A_LoopField60 + "-----------------------HTVM-OSP-HTVM-OBJ-------------- " + "OSPHTVMOSP_" + StrReplace(tempStackText, ".", "_") + Chr(10);
        }
        if (SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordCrew)) == StrLower(keyWordCrew) && lookAhead[A_Index60 + 1] == "{") {
            str1 = Trim(StringTrimLeft(A_LoopField60, StrLen(SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordCrew)))));
            //print("DEBUG11111111111111111111: " + str1)
            HTVM_Append(ospDic, str1);
            //print(A_LoopField)
            alredy = 2;
        }
        if (SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordAlliance)) == StrLower(keyWordAlliance) && lookAhead[A_Index60 + 1] == "{") {
            str1 = Trim(StringTrimLeft(A_LoopField60, StrLen(SubStr(Trim(StrLower(A_LoopField60)), 1, StrLen(keyWordAlliance)))));
            HTVM_Append(ospDic, str1);
            //print(A_LoopField)
            alredy = 2;
        }
        if (A_LoopField60 == "}_HTVM-OSP-HTVM-OSP-REMOVE-OSP-HTVMv2--OSP") {
            if (inOBJ == 1) {
                // extra code
                tempStackText = "";
                for (let A_Index64 = 0; A_Index64 < HTVM_Size(ospDic) + 0; A_Index64++) {
                    tempStackText += ospDic[A_Index64] + ".";
                }
                tempStackText = StringTrimRight(tempStackText, 1);
                outOSP += "[end][end][end][end][end] " + StrReplace(tempStackText, ".", "_") + " [end][end][end][end][end]" + Chr(10);
                inOBJ = 0;
            }
            alredy = 1;
            HTVM_Pop(ospDic);
        }
        if (alredy <= 0) {
            outOSP += A_LoopField60 + "\n";
        }
        alredy--;
    }
    outOSP = StringTrimRight(outOSP, 1);
    if (Trim(outOSP) == "") {
        return lineOriginal;
    }
    return outOSP;
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
    let items65 = LoopParseFunc(codeToFixTheGoUNSEEN, "\n", "\r");
    for (let A_Index65 = 0; A_Index65 < items65.length + 0; A_Index65++) {
        const A_LoopField65 = items65[A_Index65 - 0];
        if (RegExMatch(A_LoopField65, AindexKeyWOrd + "\\d+")) {
            if (SubStr(Trim(A_LoopField65), 1, 4) != "for ") {
                tempFixBugInfLoop = "";
                let items66 = LoopParseFunc(A_LoopField65, " ");
                for (let A_Index66 = 0; A_Index66 < items66.length + 0; A_Index66++) {
                    const A_LoopField66 = items66[A_Index66 - 0];
                    if (InStr(A_LoopField66, AindexKeyWOrd)) {
                        tempFixBugInfLoop = ExtractDigits(StrSplit(A_LoopField66, AindexKeyWOrd, 2));
                        break;
                    }
                }
                HTVM_Append(fixAindexInGoUnused, AindexKeyWOrd + tempFixBugInfLoop);
            }
        }
    }
    howMany_fixAindexInGoUnused++;
    howMany_fixAindexInGoUnused++;
    for (let A_Index67 = 0; A_Index67 < howMany_fixAindexInGoUnused + 0; A_Index67++) {
        howMany_fixAindexInGoUnusedNUM = A_Index67;
        found_fixAindexInGoUnused = 0;
        foundWHAT_fixAindexInGoUnused = AindexKeyWOrd + STR(howMany_fixAindexInGoUnusedNUM);
        for (let A_Index68 = 0; A_Index68 < HTVM_Size(fixAindexInGoUnused) + 0; A_Index68++) {
            if (fixAindexInGoUnused[A_Index68] == AindexKeyWOrd + STR(howMany_fixAindexInGoUnusedNUM)) {
                found_fixAindexInGoUnused = 1;
                break;
            }
        }
        if (foundWHAT_fixAindexInGoUnused != "") {
            if (found_fixAindexInGoUnused == 0) {
                tempFixIDK = "";
                let items69 = LoopParseFunc(codeToFixTheGoUNSEEN, "\n", "\r");
                for (let A_Index69 = 0; A_Index69 < items69.length + 0; A_Index69++) {
                    const A_LoopField69 = items69[A_Index69 - 0];
                    if (InStr(A_LoopField69, " := range ")) {
                        tempFixIDK += StrReplace(A_LoopField69, foundWHAT_fixAindexInGoUnused, "_") + Chr(10);
                    } else {
                        tempFixIDK += StrReplace(A_LoopField69, foundWHAT_fixAindexInGoUnused, "i") + Chr(10);
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
        HTVM_Append(fullLangAllOperators, "mod");
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
function ospHELP2(line) {
    var outHelp = "";
    var outHelpInt = 0;
    var outHelpInt2 = 1;
    let items70 = LoopParseFunc(line);
    for (let A_Index70 = 0; A_Index70 < items70.length + 0; A_Index70++) {
        const A_LoopField70 = items70[A_Index70 - 0];
        if (A_LoopField70 == ".") {
            outHelpInt2++;
        }
    }
    outHelpInt = StrLen(StrSplit(line, ".", outHelpInt2));
    outHelpInt++;
    outHelp = StringTrimRight(line, outHelpInt);
    return outHelp;
}
function extraFlexableFuncCallsHelp(line) {
    let allFuncsDot = [];
    var temp = "";
    let items71 = LoopParseFunc(line, ".");
    for (let A_Index71 = 0; A_Index71 < items71.length + 0; A_Index71++) {
        const A_LoopField71 = items71[A_Index71 - 0];
        if (A_Index71 == 0) {
            // the value name/other
            temp = A_LoopField71;
        } else {
            HTVM_Append(allFuncsDot, StrSplit(A_LoopField71, "(", 1) + "|" + StringTrimRight(StrSplit(A_LoopField71, "(", 2), 1));
        }
    }
    var out = "";
    var endParentesesToPut = 0;
    for (let A_Index72 = 0; A_Index72 < HTVM_Size(allFuncsDot) + 0; A_Index72++) {
        if (HTVM_Size(allFuncsDot) == A_Index72 + 1) {
            if (Trim(StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index72 - 1], "|", 2)) == "") {
                out += StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index72 - 1], "|", 1) + "(" + temp;
            } else {
                out += StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index72 - 1], "|", 1) + "(" + temp + ", " + Trim(StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index72 - 1], "|", 2));
            }
            for (let A_Index73 = 0; A_Index73 < endParentesesToPut + 1 + 0; A_Index73++) {
                out += ")";
            }
        } else {
            endParentesesToPut++;
            if (Trim(StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index72 - 1], "|", 2)) == "") {
                out += StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index72 - 1], "|", 1) + "(";
            } else {
                out += StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index72 - 1], "|", 1) + "(" + Trim(StrSplit(allFuncsDot[HTVM_Size(allFuncsDot) - A_Index72 - 1], "|", 2)) + ", ";
            }
        }
    }
    //print("=================================")
    return out;
}
function splitFunctionCalls(line) {
    var doWeAddParentisiesLater = 0;
    line = Trim(line);
    for (let A_Index74 = 0; ; A_Index74++) {
        if (SubStr(line, 1, 1) == "(") {
            line = StringTrimRight(line, 1);
            line = StringTrimLeft(line, 1);
            doWeAddParentisiesLater++;
        } else {
            break;
        }
    }
    var doseBracketsExist = 0;
    let saveDoseBracketsExist = [];
    var saveDoseBracketsExistTEMP = "";
    var inBarkets = 0;
    var inBarketsNum = 0;
    var lineOut = "";
    if (InStr(line, "[")) {
        doseBracketsExist = 1;
        let items75 = LoopParseFunc(line);
        for (let A_Index75 = 0; A_Index75 < items75.length + 0; A_Index75++) {
            const A_LoopField75 = items75[A_Index75 - 0];
            if (A_LoopField75 == "[") {
                inBarkets = 1;
                saveDoseBracketsExistTEMP += A_LoopField75;
            }
            if (A_LoopField75 == "]") {
                inBarkets = 0;
                saveDoseBracketsExistTEMP += A_LoopField75;
                HTVM_Append(saveDoseBracketsExist, saveDoseBracketsExistTEMP);
                saveDoseBracketsExistTEMP = "";
                lineOut += "brackests--rpelacse-brackets--HTVM-new-BUG--AA" + STR(inBarketsNum) + "AA";
                inBarketsNum++;
            }
            if (inBarkets == 1 && A_LoopField75 != "[" && A_LoopField75 != "]") {
                saveDoseBracketsExistTEMP += A_LoopField75;
            } else {
                lineOut += A_LoopField75;
            }
        }
        line = lineOut;
    }
    var doseFuncAtTheBegggging = 0;
    var doWeAddParentisiesLater2 = 0;
    var numRemoveFunc = 0;
    let FuncAtTheBegggging = [];
    var FuncAtTheBeggggingTEMP = "";
    if (RegExMatch(line, "^[a-zA-Z_][a-zA-Z0-9_]*\\(")) {
        doseFuncAtTheBegggging = 1;
        for (let A_Index76 = 0; ; A_Index76++) {
            if (RegExMatch(line, "^[a-zA-Z_][a-zA-Z0-9_]*\\(")) {
                FuncAtTheBeggggingTEMP = "";
                let items77 = LoopParseFunc(line);
                for (let A_Index77 = 0; A_Index77 < items77.length + 0; A_Index77++) {
                    const A_LoopField77 = items77[A_Index77 - 0];
                    if (A_LoopField77 == "(") {
                        numRemoveFunc++;
                        FuncAtTheBeggggingTEMP += A_LoopField77;
                        HTVM_Append(FuncAtTheBegggging, FuncAtTheBeggggingTEMP);
                        FuncAtTheBeggggingTEMP = "";
                        break;
                    }
                    FuncAtTheBeggggingTEMP += A_LoopField77;
                    numRemoveFunc++;
                }
                line = StringTrimLeft(line, numRemoveFunc);
                numRemoveFunc = 0;
                line = StringTrimRight(line, 1);
                doWeAddParentisiesLater2++;
            } else {
                break;
            }
        }
    }
    let funcCalls = [];
    var temp = "";
    var parenthesesDepth = 0;
    var seenDot = 0;
    let items78 = LoopParseFunc(line);
    for (let A_Index78 = 0; A_Index78 < items78.length + 0; A_Index78++) {
        const A_LoopField78 = items78[A_Index78 - 0];
        if (A_LoopField78 == ".") {
            seenDot = 1;
        }
        // Handle spaces
        if (A_LoopField78 == " ") {
            if (parenthesesDepth == 0) {
                if (temp != "") {
                    HTVM_Append(funcCalls, temp);
                    temp = "";
                }
            } else {
                temp += A_LoopField78;
            }
        }
        else if (A_LoopField78 == "(" && seenDot == 1) {
            parenthesesDepth++;
            temp += A_LoopField78;
        }
        else if (A_LoopField78 == ")" && seenDot == 1) {
            parenthesesDepth--;
            temp += A_LoopField78;
        } else {
            temp += A_LoopField78;
        }
    }
    if (temp != "") {
        HTVM_Append(funcCalls, temp);
    }
    var arrToStrSTR = "";
    for (let A_Index79 = 0; A_Index79 < HTVM_Size(funcCalls) + 0; A_Index79++) {
        if (RegExMatch(funcCalls[A_Index79], "\\.[a-zA-Z_][a-zA-Z0-9_]*")) {
            //print(funcCalls[A_Index])
            arrToStrSTR += extraFlexableFuncCallsHelp(funcCalls[A_Index79]) + " ";
        } else {
            arrToStrSTR += funcCalls[A_Index79] + " ";
        }
    }
    arrToStrSTR = StringTrimRight(arrToStrSTR, 1);
    if (doWeAddParentisiesLater != 0) {
        for (let A_Index80 = 0; A_Index80 < doWeAddParentisiesLater + 0; A_Index80++) {
            arrToStrSTR = "(" + arrToStrSTR + ")";
        }
    }
    if (doseBracketsExist == 1) {
        for (let A_Index81 = 0; A_Index81 < HTVM_Size(saveDoseBracketsExist) + 0; A_Index81++) {
            arrToStrSTR = StrReplace(arrToStrSTR, "brackests--rpelacse-brackets--HTVM-new-BUG--AA" + STR(A_Index81) + "AA", StringTrimLeft(StringTrimRight(saveDoseBracketsExist[A_Index81], 1), 1));
        }
    }
    if (doseFuncAtTheBegggging == 1) {
        for (let A_Index82 = 0; A_Index82 < HTVM_Size(FuncAtTheBegggging) + 0; A_Index82++) {
            arrToStrSTR = FuncAtTheBegggging[A_Index82] + arrToStrSTR;
        }
        for (let A_Index83 = 0; A_Index83 < doWeAddParentisiesLater2 + 0; A_Index83++) {
            arrToStrSTR = arrToStrSTR + ")";
        }
    }
    return arrToStrSTR;
}
function extraFlexableFuncCalls(line, availableFuncsInHTVMInHTVM) {
    availableFuncsInHTVMInHTVM = StringTrimRight(availableFuncsInHTVMInHTVM, 1);
    var out = line;
    let funcCalls = [];
    var temp = "";
    var parenthesesDepth = 0;
    var seenDot = 0;
    let items84 = LoopParseFunc(line);
    for (let A_Index84 = 0; A_Index84 < items84.length + 0; A_Index84++) {
        const A_LoopField84 = items84[A_Index84 - 0];
        if (A_LoopField84 == "(") {
            seenDot = 1;
        }
        // Handle spaces
        if (A_LoopField84 == " ") {
            if (parenthesesDepth == 0) {
                if (temp != "") {
                    HTVM_Append(funcCalls, temp);
                    temp = "";
                }
            } else {
                temp += A_LoopField84;
            }
        }
        else if (A_LoopField84 == "(" && seenDot == 1) {
            parenthesesDepth++;
            temp += A_LoopField84;
        }
        else if (A_LoopField84 == ")" && seenDot == 1) {
            parenthesesDepth--;
            temp += A_LoopField84;
        } else {
            temp += A_LoopField84;
        }
    }
    if (temp != "") {
        HTVM_Append(funcCalls, temp);
    }
    var isFuncExist = 0;
    out = "";
    var i = 0;
    for (let A_Index85 = 0; A_Index85 < HTVM_Size(funcCalls) + 0; A_Index85++) {
        i = A_Index85;
        isFuncExist = 0;
        let items86 = LoopParseFunc(availableFuncsInHTVMInHTVM, "\n", "\r");
        for (let A_Index86 = 0; A_Index86 < items86.length + 0; A_Index86++) {
            const A_LoopField86 = items86[A_Index86 - 0];
            if (RegExMatch(funcCalls[i], "\\b" + A_LoopField86 + "\\b")) {
                isFuncExist = 1;
            }
        }
        if (isFuncExist == 1) {
            out += splitFunctionCalls(funcCalls[A_Index85]) + " ";
        } else {
            out += funcCalls[A_Index85] + " ";
        }
    }
    out = StringTrimRight(out, 1);
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e ; e
function expressionParserTranspiler(expression) {
    var fixExpertionLineFuncOnlyTEXT_func = "";
    var fixExpertionLineFuncOnlyTEXT_numDelete = 0;
    if (fixExpertionLineFuncOnly == 1) {
        fixExpertionLineFuncOnlyTEXT_func = StrSplit(expression, "(", 1);
        fixExpertionLineFuncOnlyTEXT_numDelete = StrLen(fixExpertionLineFuncOnlyTEXT_func) + 1;
        expression = StringTrimLeft(expression, fixExpertionLineFuncOnlyTEXT_numDelete);
    }
    //go works but kinda need to use:
    //print(osp_osp_this_keyword_htvm_osp_this_htvm_keyword)
    // osp
    if (langToConvertTo != langFileExtension_2) {
        for (let A_Index87 = 0; A_Index87 < HTVM_Size(ospDic1) + 0; A_Index87++) {
            str00 = ospDic1[A_Index87];
            expression = StrReplace(expression, StrReplace(str00, "_", ".") + ".", str00 + "_");
        }
        for (let A_Index88 = 0; A_Index88 < HTVM_Size(ospDic2) + 0; A_Index88++) {
            str00 = ospDic2[A_Index88];
            expression = RegExReplace(expression, "\\b" + str00 + "\\b", "OSPHTVMOSP_" + StrReplace(str00, ".", "_"));
        }
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
    for (let A_Index89 = 0; A_Index89 < 29 + 0; A_Index89++) {
        if (InStr(expression, fullLangAllOperators_HELP[A_Index89])) {
            if (A_Index89 == 0 || A_Index89 == 1 || A_Index89 == 2) {
                expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index89] + "\\b", fullLangAllOperators[A_Index89]);
            } else {
                if (A_Index89 == 19) {
                    if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index89] + "\\b", "not");
                    } else {
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index89] + "\\b", "!");
                    }
                    if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
                        expression = RegExReplace(expression, "!([\\w]+)", "not $1");
                    }
                    expression = StrReplace(expression, " not= ", " != ");
                } else {
                    expression = StrReplace(expression, " " + fullLangAllOperators_HELP[A_Index89] + " ", " " + fullLangAllOperators[A_Index89] + " ");
                    if (A_Index89 == 28) {
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
    if (langToConvertTo == langFileExtension_2) {
        expression = RegExReplace(expression, "\\b" + keyWordThis + "\\b", keyWordThis_2);
    } else {
        expression = RegExReplace(expression, "\\b" + keyWordThis + "\\b", "osp_osp_this_keyword_htvm_osp_this_htvm_keyword");
    }
    if (RegExMatch(expression, "\\.[a-zA-Z_][a-zA-Z0-9_]*") && langToConvertTo != langFileExtension_2) {
        expression = extraFlexableFuncCalls(expression, availableFuncsInHTVMInHTVM);
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
function FixRubyGlobalVars(line) {
    let htCodeFixRubyGlobalVars = [];
    let items90 = LoopParseFunc(line, "\n", "\r");
    for (let A_Index90 = 0; A_Index90 < items90.length + 0; A_Index90++) {
        const A_LoopField90 = items90[A_Index90 - 0];
        if (RegExMatch(A_LoopField90, "^[a-zA-Z_][a-zA-Z0-9_]* = .*")) {
            HTVM_Append(htCodeFixRubyGlobalVars, Trim(StrSplit(A_LoopField90, " = ", 1)));
        }
    }
    for (let A_Index91 = 0; A_Index91 < HTVM_Size(htCodeFixRubyGlobalVars) + 0; A_Index91++) {
        line = RegExReplace(line, "\\b" + htCodeFixRubyGlobalVars[A_Index91] + "\\b", "$" + htCodeFixRubyGlobalVars[A_Index91]);
    }
    return line;
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
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function propHELP(line, lineOspHelpLine) {
    if (lineOspHelpLine == "no-no") {
        lineOspHelpLine = "";
    }
    var htCodeOUTOUT = "";
    var ALoopField = "";
    let items92 = LoopParseFunc(line, "\n", "\r");
    for (let A_Index92 = 0; A_Index92 < items92.length + 0; A_Index92++) {
        const A_LoopField92 = items92[A_Index92 - 0];
        if (InStr(A_LoopField92, " " + keyWordAssign + " ") || InStr(A_LoopField92, " " + keyWordAssignAdd + " ") || InStr(A_LoopField92, " " + keyWordAssignConcat + " ") || InStr(A_LoopField92, " " + keyWordAssignSub + " ") || InStr(A_LoopField92, " " + keyWordAssignMul + " ") || InStr(A_LoopField92, " " + keyWordAssignDiv + " ") || InStr(A_LoopField92, " " + keyWordAssignMod + " ") || InStr(A_LoopField92, " " + keyWordAssignShiftLeft + " ") || InStr(A_LoopField92, " " + keyWordAssignShiftRight + " ") || InStr(A_LoopField92, " " + keyWordLogicalAssignShiftRight + " ") || InStr(A_LoopField92, " " + keyWordAssignBitAnd + " ") || InStr(A_LoopField92, " " + keyWordAssignBitOr + " ") || InStr(A_LoopField92, " " + keyWordAssignBitXor + " ") && lineDone == 0) {
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
            if (InStr(A_LoopField92, " " + keyWordAssign + " ")) {
                str1 = StrSplit(A_LoopField92, " " + keyWordAssign + " ", 1);
                str6 = StrSplit(A_LoopField92, " " + keyWordAssign + " ", 2);
                str10 = keyWordAssign;
                str11 = keyWordAssign_2;
                if (langToConvertTo == "ahk") {
                    str12 = ":=";
                } else {
                    str12 = "=";
                }
            }
            else if (InStr(A_LoopField92, " " + keyWordAssignAdd + " ")) {
                str1 = StrSplit(A_LoopField92, " " + keyWordAssignAdd + " ", 1);
                str6 = StrSplit(A_LoopField92, " " + keyWordAssignAdd + " ", 2);
                str10 = keyWordAssignAdd;
                str11 = keyWordAssignAdd_2;
                str12 = "+=";
            }
            else if (InStr(A_LoopField92, " " + keyWordAssignConcat + " ")) {
                str1 = StrSplit(A_LoopField92, " " + keyWordAssignConcat + " ", 1);
                str6 = StrSplit(A_LoopField92, " " + keyWordAssignConcat + " ", 2);
                str10 = keyWordAssignConcat;
                str11 = keyWordAssignConcat_2;
                if (langToConvertTo == "ahk") {
                    str12 = ".=";
                } else {
                    str12 = "+=";
                }
            }
            else if (InStr(A_LoopField92, " " + keyWordAssignSub + " ")) {
                str1 = StrSplit(A_LoopField92, " " + keyWordAssignSub + " ", 1);
                str6 = StrSplit(A_LoopField92, " " + keyWordAssignSub + " ", 2);
                str10 = keyWordAssignSub;
                str11 = keyWordAssignSub_2;
                str12 = "-=";
            }
            else if (InStr(A_LoopField92, " " + keyWordAssignMul + " ")) {
                str1 = StrSplit(A_LoopField92, " " + keyWordAssignMul + " ", 1);
                str6 = StrSplit(A_LoopField92, " " + keyWordAssignMul + " ", 2);
                str10 = keyWordAssignMul;
                str11 = keyWordAssignMul_2;
                str12 = "*=";
            }
            else if (InStr(A_LoopField92, " " + keyWordAssignDiv + " ")) {
                str1 = StrSplit(A_LoopField92, " " + keyWordAssignDiv + " ", 1);
                str6 = StrSplit(A_LoopField92, " " + keyWordAssignDiv + " ", 2);
                str10 = keyWordAssignDiv;
                str11 = keyWordAssignDiv_2;
                str12 = "/=";
            }
            else if (InStr(A_LoopField92, " " + keyWordAssignMod + " ")) {
                str1 = StrSplit(A_LoopField92, " " + keyWordAssignMod + " ", 1);
                str6 = StrSplit(A_LoopField92, " " + keyWordAssignMod + " ", 2);
                str10 = keyWordAssignMod;
                str11 = keyWordAssignMod_2;
                str12 = "%=";
            }
            else if (InStr(A_LoopField92, " " + keyWordAssignShiftLeft + " ")) {
                str1 = StrSplit(A_LoopField92, " " + keyWordAssignShiftLeft + " ", 1);
                str6 = StrSplit(A_LoopField92, " " + keyWordAssignShiftLeft + " ", 2);
                str10 = keyWordAssignShiftLeft;
                str11 = keyWordAssignShiftLeft_2;
                str12 = "<<=";
            }
            else if (InStr(A_LoopField92, " " + keyWordAssignShiftRight + " ")) {
                str1 = StrSplit(A_LoopField92, " " + keyWordAssignShiftRight + " ", 1);
                str6 = StrSplit(A_LoopField92, " " + keyWordAssignShiftRight + " ", 2);
                str10 = keyWordAssignShiftRight;
                str11 = keyWordAssignShiftRight_2;
                str12 = ">>=";
            }
            else if (InStr(A_LoopField92, " " + keyWordLogicalAssignShiftRight + " ")) {
                str1 = StrSplit(A_LoopField92, " " + keyWordLogicalAssignShiftRight + " ", 1);
                str6 = StrSplit(A_LoopField92, " " + keyWordLogicalAssignShiftRight + " ", 2);
                str10 = keyWordLogicalAssignShiftRight;
                str11 = keyWordLogicalAssignShiftRight_2;
                str12 = ">>>=";
            }
            else if (InStr(A_LoopField92, " " + keyWordAssignBitAnd + " ")) {
                str1 = StrSplit(A_LoopField92, " " + keyWordAssignBitAnd + " ", 1);
                str6 = StrSplit(A_LoopField92, " " + keyWordAssignBitAnd + " ", 2);
                str10 = keyWordAssignBitAnd;
                str11 = keyWordAssignBitAnd_2;
                str12 = "&=";
            }
            else if (InStr(A_LoopField92, " " + keyWordAssignBitOr + " ")) {
                str1 = StrSplit(A_LoopField92, " " + keyWordAssignBitOr + " ", 1);
                str6 = StrSplit(A_LoopField92, " " + keyWordAssignBitOr + " ", 2);
                str10 = keyWordAssignBitOr;
                str11 = keyWordAssignBitOr_2;
                str12 = "|=";
            }
            else if (InStr(A_LoopField92, " " + keyWordAssignBitXor + " ")) {
                str1 = StrSplit(A_LoopField92, " " + keyWordAssignBitXor + " ", 1);
                str6 = StrSplit(A_LoopField92, " " + keyWordAssignBitXor + " ", 2);
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
            if (InStr(ALoopField, " ") == false || SubStrLastChars(ALoopField, 1) == "]") {
                lineDone = 1;
                str1 = lineOspHelpLine + Trim(str1);
                str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str1);
                if (InStr(saveAllArrayVarNamesSoWeCanDoAfix, "|" + Trim(str1) + "|")) {
                    str6 = Trim(str6);
                    str6 = StringTrimRight(str6, 1);
                    str6 = StringTrimLeft(str6, 1);
                    if (langToConvertTo == "cpp") {
                        str6 = "{" + str6 + "}";
                    }
                    if (langToConvertTo == "py") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "js") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "go") {
                        str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                    }
                    if (langToConvertTo == "lua") {
                        str6 = "{" + str6 + "}";
                    }
                    if (langToConvertTo == "cs") {
                        str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                    }
                    if (langToConvertTo == "java") {
                        str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                    }
                    if (langToConvertTo == "kt") {
                        str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                    }
                    if (langToConvertTo == "rb") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "nim") {
                        str6 = "@[" + str6 + "]";
                    }
                    if (langToConvertTo == "ahk") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "swift") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "dart") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "ts") {
                        str6 = "[" + str6 + "]";
                    }
                    if (langToConvertTo == "groovy") {
                        str6 = "[" + str6 + "]";
                    }
                }
                if (Trim(str6) == "[]" || Trim(str6) == "{}") {
                    if (useCurlyBracesSyntaxForArrayDef_2 == "on" && langToConvertTo == langFileExtension_2) {
                        str6 = "{}";
                    } else {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "cpp") {
                        str6 = "{}";
                    }
                    if (langToConvertTo == "py") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "js") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "go") {
                        str6 = Trim(str1) + "[:0]";
                    }
                    if (langToConvertTo == "lua") {
                        str6 = "{}";
                    }
                    if (langToConvertTo == "cs") {
                        str6 = "ResetList(" + Trim(str1) + ")";
                    }
                    if (langToConvertTo == "java") {
                        str6 = "new ArrayList<>()";
                    }
                    if (langToConvertTo == "kt") {
                        str6 = "ArrayList()";
                    }
                    if (langToConvertTo == "rb") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "nim") {
                        str6 = "@[]";
                    }
                    if (langToConvertTo == "ahk") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "swift") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "dart") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "ts") {
                        str6 = "[]";
                    }
                    if (langToConvertTo == "groovy") {
                        str6 = "[]";
                    }
                }
                //;;;;;;;;;;;;;;;;;
                //;;;;;;;;;;;;;;;;;
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
                    if (Trim(str6) == "[]" || Trim(str6) == "{}") {
                        str4 = str1 + " " + str12 + " " + str6 + ";";
                    } else {
                        if (InStr(str1, "[")) {
                            // Convert arr[something] to arr.set(something, value);
                            str1 = RegExReplace(str1, "(\\b[A-Za-z_]\\w*)\\s*\\[(.*?)\\]", "$1.set($2, ");
                            str4 = str1 + str6 + ");";
                        } else {
                            str4 = str1 + " " + str12 + " " + str6 + ";";
                        }
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
                htCodeOUTOUT += str4 + Chr(10);
            }
            else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordConst)) == keyWordConst && lineDone == 0) {
                lineDone = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordConst)));
                    let items93 = LoopParseFunc(str1, " ");
                    for (let A_Index93 = 0; A_Index93 < items93.length + 0; A_Index93++) {
                        const A_LoopField93 = items93[A_Index93 - 0];
                        str2 = A_LoopField93;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = lineOspHelpLine + Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordConst)));
                    str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                }
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    int5 = 0;
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            if (int5 != 0) {
                                str6 = "{" + str6 + "}";
                            }
                        } else {
                            if (int5 != 0) {
                                str6 = "[" + str6 + "]";
                            }
                        }
                        if (useSemicolon_2 == "on") {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        } else {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "py") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6 + "";
                        }
                    }
                    if (langToConvertTo == "js") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        if (int5 != 0) {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        } else {
                            str4 = str2 + " := " + str3 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "lua") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "kt") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                        } else {
                            str4 = "var " + str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "rb") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "nim") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + str3 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        if (int5 != 0) {
                            str4 = str2 + " := [" + str6 + "]";
                        } else {
                            str4 = str2 + " := " + str6;
                        }
                    }
                    if (langToConvertTo == "swift") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "dart") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        } else {
                            str4 = str3 + " " + str2 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "ts") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
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
                                str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                            } else {
                                str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                            } else {
                                str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
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
                        str4 = "final " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "ts") {
                        str4 = "const " + str2 + ": " + str3 + " " + str12 + " " + str6 + ";";
                    }
                    if (langToConvertTo == "groovy") {
                        str4 = "final " + str2 + " " + str12 + " " + str6;
                    }
                    //;;;
                }
                htCodeOUTOUT += str4 + Chr(10);
            }
            else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordVar)) == keyWordVar && lineDone == 0) {
                lineDone = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordVar)));
                    let items94 = LoopParseFunc(str1, " ");
                    for (let A_Index94 = 0; A_Index94 < items94.length + 0; A_Index94++) {
                        const A_LoopField94 = items94[A_Index94 - 0];
                        str2 = A_LoopField94;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = lineOspHelpLine + Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordVar)));
                    str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                }
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    int5 = 0;
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            if (int5 != 0) {
                                str6 = "{" + str6 + "}";
                            }
                        } else {
                            if (int5 != 0) {
                                str6 = "[" + str6 + "]";
                            }
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
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        } else {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "py") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6 + "";
                        }
                    }
                    if (langToConvertTo == "js") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        if (int5 != 0) {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        } else {
                            str4 = str2 + " := " + str3 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "lua") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "kt") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                        } else {
                            str4 = "var " + str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "rb") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "nim") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + str3 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        if (int5 != 0) {
                            str4 = str2 + " := [" + str6 + "]";
                        } else {
                            str4 = str2 + " := " + str6;
                        }
                    }
                    if (langToConvertTo == "swift") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "dart") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        } else {
                            str4 = str3 + " " + str2 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "ts") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
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
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    //;;;
                }
                htCodeOUTOUT += str4 + Chr(10);
            }
            else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordLet)) == keyWordLet && lineDone == 0) {
                lineDone = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordLet)));
                    let items95 = LoopParseFunc(str1, " ");
                    for (let A_Index95 = 0; A_Index95 < items95.length + 0; A_Index95++) {
                        const A_LoopField95 = items95[A_Index95 - 0];
                        str2 = A_LoopField95;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = lineOspHelpLine + Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordLet)));
                    str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                }
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    int5 = 0;
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            if (int5 != 0) {
                                str6 = "{" + str6 + "}";
                            }
                        } else {
                            if (int5 != 0) {
                                str6 = "[" + str6 + "]";
                            }
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
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        } else {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "py") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6 + "";
                        }
                    }
                    if (langToConvertTo == "js") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        if (int5 != 0) {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        } else {
                            str4 = str2 + " := " + str3 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "lua") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "kt") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                        } else {
                            str4 = "var " + str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "rb") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "nim") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + str3 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        if (int5 != 0) {
                            str4 = str2 + " := [" + str6 + "]";
                        } else {
                            str4 = str2 + " := " + str6;
                        }
                    }
                    if (langToConvertTo == "swift") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "dart") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        } else {
                            str4 = str3 + " " + str2 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "ts") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
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
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    //;;;
                }
                htCodeOUTOUT += str4 + Chr(10);
            }
            else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordDouble + " ")) == keyWordDouble + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordChar + " ")) == keyWordChar + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint8 + " ")) == keyWordUint8 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint16 + " ")) == keyWordUint16 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint32 + " ")) == keyWordUint32 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint64 + " ")) == keyWordUint64 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT + " ")) == keyWordINT + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordSTR + " ")) == keyWordSTR + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordBOOL + " ")) == keyWordBOOL + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordFLOAT + " ")) == keyWordFLOAT + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT8 + " ")) == keyWordINT8 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT16 + " ")) == keyWordINT16 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT32 + " ")) == keyWordINT32 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT64 + " ")) == keyWordINT64 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayDefinition + " ")) == keyWordArrayDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfIntegersDefinition + " ")) == keyWordArrayOfIntegersDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfStringsDefinition + " ")) == keyWordArrayOfStringsDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfFloatingPointNumbersDefinition + " ")) == keyWordArrayOfFloatingPointNumbersDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfBooleansDefinition + " ")) == keyWordArrayOfBooleansDefinition + " " && usePrefixTypeForTypeDefinition == "on" && lineDone == 0) {
                lineDone = 1;
                let items96 = LoopParseFunc(str1, " ");
                for (let A_Index96 = 0; A_Index96 < items96.length + 0; A_Index96++) {
                    const A_LoopField96 = items96[A_Index96 - 0];
                    str2 = A_LoopField96;
                }
                str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                str2 = lineOspHelpLine + Trim(str2);
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    int5 = 0;
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            if (int5 != 0) {
                                str6 = "{" + str6 + "}";
                            }
                        } else {
                            if (int5 != 0) {
                                str6 = "[" + str6 + "]";
                            }
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
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        } else {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "py") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6 + "";
                        }
                    }
                    if (langToConvertTo == "js") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        if (int5 != 0) {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        } else {
                            str4 = str2 + " := " + str3 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "lua") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "kt") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                        } else {
                            str4 = "var " + str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "rb") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "nim") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + str3 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        if (int5 != 0) {
                            str4 = str2 + " := [" + str6 + "]";
                        } else {
                            str4 = str2 + " := " + str6;
                        }
                    }
                    if (langToConvertTo == "swift") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "dart") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        } else {
                            str4 = str3 + " " + str2 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "ts") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
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
                        str4 = str2 + " " + str12 + " " + str6;
                    }
                    //;;;
                }
                htCodeOUTOUT += str4 + Chr(10);
            }
            else if (RegExMatch(Trim(str1), "^[a-zA-Z_][a-zA-Z_0-9]*:\\s?.*$") && usePostfixTypeForTypeDefinition == "on" && lineDone == 0) {
                lineDone = 1;
                str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
                str3 = Trim(StrSplit(str1, ":", 2));
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                    str3 = getFuncTypeConvert(str3);
                    int5 = 0;
                    if (useCurlyBracesSyntaxForArrayDef == "on") {
                        if (SubStr(str6, 1, 1) == "{") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    } else {
                        if (SubStr(str6, 1, 1) == "[") {
                            int5 = 1;
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                        }
                    }
                    if (langToConvertTo == langFileExtension_2) {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                            if (int5 != 0) {
                                str6 = "{" + str6 + "}";
                            }
                        } else {
                            if (int5 != 0) {
                                str6 = "[" + str6 + "]";
                            }
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
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                        } else {
                            str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "py") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " [" + str6 + "]";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6 + "";
                        }
                    }
                    if (langToConvertTo == "js") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "go") {
                        if (int5 != 0) {
                            str4 = str2 + " := " + str3 + "{" + str6 + "}";
                        } else {
                            str4 = str2 + " := " + str3 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "lua") {
                        if (int5 != 0) {
                            str4 = str2 + " " + str12 + " {" + str6 + "}";
                        } else {
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                    }
                    if (langToConvertTo == "cs") {
                        if (csMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                            } else {
                                str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "java") {
                        if (javaMainFuncSeen == 1) {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        } else {
                            if (int5 != 0) {
                                str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                            } else {
                                str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                    }
                    if (langToConvertTo == "kt") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                        } else {
                            str4 = "var " + str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "rb") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "nim") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + str3 + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        if (int5 != 0) {
                            str4 = str2 + " := [" + str6 + "]";
                        } else {
                            str4 = str2 + " := " + str6;
                        }
                    }
                    if (langToConvertTo == "swift") {
                        if (int5 != 0) {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                        } else {
                            str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                        }
                    }
                    if (langToConvertTo == "dart") {
                        if (int5 != 0) {
                            str4 = str3 + " " + str2 + " = [" + str6 + "];";
                        } else {
                            str4 = str3 + " " + str2 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "ts") {
                        if (int5 != 0) {
                            str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                        } else {
                            str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        if (int5 != 0) {
                            str4 = str2 + " = [" + str6 + "]";
                        } else {
                            str4 = str2 + " = " + str6;
                        }
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
                        str4 = str2 + " " + str12 + " " + str6 + ";";
                    }
                    //;;;
                }
                htCodeOUTOUT += str4 + Chr(10);
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
        else if (SubStr(Trim(A_LoopField92), 1, StrLen(keyWordVar)) == keyWordVar && lineDone == 0) {
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
            if (usePostfixTypeForTypeDefinition == "off") {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(Trim(A_LoopField92), StrLen(keyWordVar)));
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                let items97 = LoopParseFunc(str1, " ");
                for (let A_Index97 = 0; A_Index97 < items97.length + 0; A_Index97++) {
                    const A_LoopField97 = items97[A_Index97 - 0];
                    str2 = A_LoopField97;
                }
                str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                str2 = lineOspHelpLine + Trim(str2);
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
            } else {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(Trim(A_LoopField92), StrLen(keyWordVar)));
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
                str3 = Trim(StrSplit(str1, ":", 2));
                // str2 = var name
                // str3 = type
            }
            if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
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
                    str4 = "var " + str2 + " = " + str3 + "()";
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
                    str4 = str2 + " = []";
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
                    str4 = str2 + " = null";
                }
                //;;;
            }
            htCodeOUTOUT += str4 + Chr(10);
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
        }
        else if (SubStr(Trim(A_LoopField92), 1, StrLen(keyWordLet)) == keyWordLet && lineDone == 0) {
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
            if (usePostfixTypeForTypeDefinition == "off") {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(Trim(A_LoopField92), StrLen(keyWordLet)));
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                let items98 = LoopParseFunc(str1, " ");
                for (let A_Index98 = 0; A_Index98 < items98.length + 0; A_Index98++) {
                    const A_LoopField98 = items98[A_Index98 - 0];
                    str2 = A_LoopField98;
                }
                str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                str2 = lineOspHelpLine + Trim(str2);
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
            } else {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(Trim(A_LoopField92), StrLen(keyWordLet)));
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
                str3 = Trim(StrSplit(str1, ":", 2));
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
            }
            if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
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
                    str4 = "var " + str2 + " = " + str3 + "()";
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
                    str4 = str2 + " = []";
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
                    str4 = str2 + " = null";
                }
                //;;;
            }
            htCodeOUTOUT += str4 + Chr(10);
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
        }
        else if (SubStr(Trim(A_LoopField92), 1, StrLen(keyWordDouble + " ")) == keyWordDouble + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordChar + " ")) == keyWordChar + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordUint8 + " ")) == keyWordUint8 + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordUint16 + " ")) == keyWordUint16 + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordUint32 + " ")) == keyWordUint32 + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordUint64 + " ")) == keyWordUint64 + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordINT + " ")) == keyWordINT + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordSTR + " ")) == keyWordSTR + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordBOOL + " ")) == keyWordBOOL + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordFLOAT + " ")) == keyWordFLOAT + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordINT8 + " ")) == keyWordINT8 + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordINT16 + " ")) == keyWordINT16 + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordINT32 + " ")) == keyWordINT32 + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordINT64 + " ")) == keyWordINT64 + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordArrayDefinition + " ")) == keyWordArrayDefinition + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordArrayOfIntegersDefinition + " ")) == keyWordArrayOfIntegersDefinition + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordArrayOfStringsDefinition + " ")) == keyWordArrayOfStringsDefinition + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordArrayOfFloatingPointNumbersDefinition + " ")) == keyWordArrayOfFloatingPointNumbersDefinition + " " || SubStr(Trim(A_LoopField92), 1, StrLen(keyWordArrayOfBooleansDefinition + " ")) == keyWordArrayOfBooleansDefinition + " " && usePrefixTypeForTypeDefinition == "on" && lineDone == 0) {
            lineDone = 1;
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
            str1 = Trim(A_LoopField92);
            if (SubStrLastChars(str1, 1) == ";") {
                str1 = StringTrimRight(str1, 1);
            }
            let items99 = LoopParseFunc(str1, " ");
            for (let A_Index99 = 0; A_Index99 < items99.length + 0; A_Index99++) {
                const A_LoopField99 = items99[A_Index99 - 0];
                str2 = A_LoopField99;
            }
            str3 = Trim(StringTrimRight(str1, StrLen(str2)));
            str2 = lineOspHelpLine + Trim(str2);
            // str2 = var name
            // str3 = type
            HTVM_Append(allVarsSoWeDontReDecVars, str2);
            if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
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
                    str4 = "var " + str2 + " = " + str3 + "()";
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
                    str4 = str2 + " = []";
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
                    str4 = str2 + " = null";
                }
                //;;;
            }
            htCodeOUTOUT += str4 + Chr(10);
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
        }
        else if (RegExMatch(Trim(A_LoopField92), "^[a-zA-Z_][a-zA-Z0-9_]*: [^:]*;?$") && usePostfixTypeForTypeDefinition == "on" && lineDone == 0) {
            lineDone = 1;
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
            str1 = Trim(A_LoopField92);
            if (SubStrLastChars(str1, 1) == ";") {
                str1 = StringTrimRight(str1, 1);
            }
            str2 = lineOspHelpLine + Trim(StrSplit(str1, ":", 1));
            str3 = Trim(StrSplit(str1, ":", 2));
            // str2 = var name
            // str3 = type
            HTVM_Append(allVarsSoWeDontReDecVars, str2);
            if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
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
                    str4 = "var " + str2 + " = " + str3 + "()";
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
                    str4 = str2 + " = []";
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
                    str4 = str2 + " = null";
                }
                //;;;
            }
            htCodeOUTOUT += str4 + Chr(10);
            allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
        } else {
            htCodeOUTOUT += A_LoopField92 + Chr(10);
        }
    }
    htCodeOUTOUT = StringTrimRight(htCodeOUTOUT, 1);
    return htCodeOUTOUT;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// the GUI funcs
// the GUI funcs
// the GUI funcs
// the GUI funcs
// the GUI funcs
// the GUI funcs
// the GUI funcs
function guiParserStep4(option) {
    // convert and handle the options to js
    var out = "";
    // ============================================================
    // ALIAS DEFINITIONS FOR GUI OPTIONS
    // ============================================================
    // elementType, id, parentId, x, y, width, height, zIndex, value, placeholder, callback, backgroundColor, color, rounding, border, rawCss, size, isEnabled, isVisible, isDeleting
    // These arrays hold the valid aliases for each GUI property.
    // They are used to map user input (e.g., "w", "width", "widh")
    // to the canonical property name used in the generated JS (e.g., "width").
    //
    // - `aliases_single_PROPERTY`: Contains single-letter aliases (used like `w100`).
    // - `aliases_colon_PROPERTY`: Contains aliases used with a colon (e.g., `width:100`).
    // Note: All checks should be case-insensitive.
    // --- id Aliases ---
    let aliases_single_id = ["i", "v"];
    let aliases_colon_id = ["i", "v", "id", "elementId", "eid", "elId"];
    var canonical_id = "id";
    // --- parentId Aliases ---
    let aliases_single_parentId = ["p"];
    let aliases_colon_parentId = ["p", "parentId", "pid", "parId", "divId", "guiId"];
    var canonical_parentId = "parentId";
    // --- x Aliases ---
    let aliases_single_x = ["x"];
    let aliases_colon_x = ["x", "xPos", "xCoord", "xCrd"];
    var canonical_x = "x";
    // --- y Aliases ---
    let aliases_single_y = ["y"];
    let aliases_colon_y = ["y", "yPos", "yCoord", "yCrd"];
    var canonical_y = "y";
    // --- width Aliases ---
    let aliases_single_width = ["w"];
    let aliases_colon_width = ["w", "width", "wight", "widh", "widht", "widhth", "wdtih", "widhh", "widhts"];
    var canonical_width = "width";
    // --- height Aliases ---
    let aliases_single_height = ["h"];
    let aliases_colon_height = ["h", "height", "hight", "heigth", "heigtht", "hieght", "hegt", "heihgt"];
    var canonical_height = "height";
    // --- zIndex Aliases ---
    let aliases_single_zIndex = ["z"];
    let aliases_colon_zIndex = ["z", "zIndex", "z-Index", "zi"];
    var canonical_zIndex = "zIndex";
    // --- value Aliases ---
    let aliases_single_value = ["d"];
    let aliases_colon_value = ["d", "val", "value", "displayValue", "dv"];
    var canonical_value = "value";
    // --- placeholder Aliases ---
    let aliases_single_placeholder = ["q"];
    let aliases_colon_placeholder = ["q", "placeHolder", "plc", "plch", "ph", "grayText", "editForeGround", "editPlaceHolder", "editGrayInfo", "editPlaceHolderGrayInfoText"];
    var canonical_placeholder = "placeholder";
    // --- callback Aliases ---
    let aliases_single_callback = ["g", "f"];
    let aliases_colon_callback = ["g", "f", "callback", "call", "func", "fn", "function", "point", "back", "bakc"];
    var canonical_callback = "callback";
    // --- backgroundColor Aliases ---
    let aliases_single_backgroundColor = ["o"];
    let aliases_colon_backgroundColor = ["o", "bg", "bc", "bgc", "backgroundColor", "bgColor"];
    var canonical_backgroundColor = "backgroundColor";
    // --- color Aliases ---
    let aliases_single_color = ["c"];
    let aliases_colon_color = ["c", "color", "colour", "clr"];
    var canonical_color = "color";
    // --- rounding Aliases ---
    let aliases_single_rounding = ["r"];
    let aliases_colon_rounding = ["r", "rounding", "round", "rounded", "rnd"];
    var canonical_rounding = "rounding";
    // --- border Aliases ---
    let aliases_single_border = ["b"];
    let aliases_colon_border = ["b", "border", "boder", "outline", "brd"];
    var canonical_border = "border";
    // --- rawCss Aliases ---
    let aliases_single_rawCss = ["l"];
    let aliases_colon_rawCss = ["l", "rawCss", "luxury", "rawSsc", "rawScc", "css", "scc", "style", "stlye", "styel", "sytle", "sytel", "stylye", "stiyl", "stiyel", "luxary", "luxuary", "luxery", "luxurey"];
    var canonical_rawCss = "rawCss";
    // --- size Aliases ---
    let aliases_single_size = ["s"];
    let aliases_colon_size = ["s", "size", "sz", "szie", "bigness"];
    var canonical_size = "size";
    // --- isEnabled Aliases ---
    let aliases_single_isEnabled = ["a"];
    let aliases_colon_isEnabled = ["a", "isEnabled", "isE", "isEnb"];
    var canonical_isEnabled = "isEnabled";
    // --- isVisible Aliases ---
    let aliases_single_isVisible = ["u"];
    let aliases_colon_isVisible = ["u", "isVisible", "isV", "isVsb"];
    var canonical_isVisible = "isVisible";
    // --- isDeleting Aliases ---
    let aliases_single_isDeleting = ["n"];
    let aliases_colon_isDeleting = ["n", "isDeleting", "isD", "isDlt", "del", "delete", "remove", "rmv", "rm"];
    var canonical_isDeleting = "isDeleting";
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    // aliases_single_id               ; aliases_colon_id               ; canonical_id
    // aliases_single_parentId         ; aliases_colon_parentId         ; canonical_parentId
    // aliases_single_x                ; aliases_colon_x                ; canonical_x
    // aliases_single_y                ; aliases_colon_y                ; canonical_y
    // aliases_single_width            ; aliases_colon_width            ; canonical_width
    // aliases_single_height           ; aliases_colon_height           ; canonical_height
    // aliases_single_zIndex           ; aliases_colon_zIndex           ; canonical_zIndex
    // aliases_single_value            ; aliases_colon_value            ; canonical_value
    // aliases_single_placeholder      ; aliases_colon_placeholder      ; canonical_placeholder
    // aliases_single_callback         ; aliases_colon_callback         ; canonical_callback
    // aliases_single_backgroundColor  ; aliases_colon_backgroundColor  ; canonical_backgroundColor
    // aliases_single_color            ; aliases_colon_color            ; canonical_color
    // aliases_single_rounding         ; aliases_colon_rounding         ; canonical_rounding
    // aliases_single_border           ; aliases_colon_border           ; canonical_border
    // aliases_single_rawCss           ; aliases_colon_rawCss           ; canonical_rawCss
    // aliases_single_size             ; aliases_colon_size             ; canonical_size
    // aliases_single_isEnabled        ; aliases_colon_isEnabled        ; canonical_isEnabled
    // aliases_single_isVisible        ; aliases_colon_isVisible        ; canonical_isVisible
    // aliases_single_isDeleting       ; aliases_colon_isDeleting       ; canonical_isDeleting
    // option
    var option0 = "";
    var option1 = "";
    if (InStr(option, ":")) {
        option0 = Trim(StrSplit(option, ":", 1));
        option1 = Trim(StrSplit(option, ":", 2));
        //print("=-=-=-=-=-=-=-=-=-=-::::::::::::::::::=-=-=-=-=-=-=-=-=-=-=-=-=")
        //print(option)
        //print(option0)
        //print(option1)
        //print("=-=-=-=-=-=-=-=-=-=-::::::::::::::::::=-=-=-=-=-=-=-=-=-=-=-=-=")
        for (let A_Index100 = 0; A_Index100 < HTVM_Size(aliases_colon_id) + 0; A_Index100++) {
            if (StrLower(option0) == StrLower(aliases_colon_id[A_Index100])) {
                option0 = canonical_id;
                break;
            }
        }
        for (let A_Index101 = 0; A_Index101 < HTVM_Size(aliases_colon_parentId) + 0; A_Index101++) {
            if (StrLower(option0) == StrLower(aliases_colon_parentId[A_Index101])) {
                option0 = canonical_parentId;
                break;
            }
        }
        for (let A_Index102 = 0; A_Index102 < HTVM_Size(aliases_colon_x) + 0; A_Index102++) {
            if (StrLower(option0) == StrLower(aliases_colon_x[A_Index102])) {
                option0 = canonical_x;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (let A_Index103 = 0; A_Index103 < HTVM_Size(aliases_colon_y) + 0; A_Index103++) {
            if (StrLower(option0) == StrLower(aliases_colon_y[A_Index103])) {
                option0 = canonical_y;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (let A_Index104 = 0; A_Index104 < HTVM_Size(aliases_colon_width) + 0; A_Index104++) {
            if (StrLower(option0) == StrLower(aliases_colon_width[A_Index104])) {
                option0 = canonical_width;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (let A_Index105 = 0; A_Index105 < HTVM_Size(aliases_colon_height) + 0; A_Index105++) {
            if (StrLower(option0) == StrLower(aliases_colon_height[A_Index105])) {
                option0 = canonical_height;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (let A_Index106 = 0; A_Index106 < HTVM_Size(aliases_colon_zIndex) + 0; A_Index106++) {
            if (StrLower(option0) == StrLower(aliases_colon_zIndex[A_Index106])) {
                option0 = canonical_zIndex;
                break;
            }
        }
        for (let A_Index107 = 0; A_Index107 < HTVM_Size(aliases_colon_value) + 0; A_Index107++) {
            if (StrLower(option0) == StrLower(aliases_colon_value[A_Index107])) {
                option0 = canonical_value;
                break;
            }
        }
        for (let A_Index108 = 0; A_Index108 < HTVM_Size(aliases_colon_placeholder) + 0; A_Index108++) {
            if (StrLower(option0) == StrLower(aliases_colon_placeholder[A_Index108])) {
                option0 = canonical_placeholder;
                break;
            }
        }
        for (let A_Index109 = 0; A_Index109 < HTVM_Size(aliases_colon_callback) + 0; A_Index109++) {
            if (StrLower(option0) == StrLower(aliases_colon_callback[A_Index109])) {
                option0 = canonical_callback;
                break;
            }
        }
        for (let A_Index110 = 0; A_Index110 < HTVM_Size(aliases_colon_backgroundColor) + 0; A_Index110++) {
            if (StrLower(option0) == StrLower(aliases_colon_backgroundColor[A_Index110])) {
                option0 = canonical_backgroundColor;
                if (RegExMatch(option1, "^(([0-9a-fA-F]{2}){3}|([0-9a-fA-F]){3})$")) {
                    option1 = Chr(34) + "#" + option1 + Chr(34);
                } else {
                    if (InStr(option1, "#")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    }
                }
                // else it's just a var name, just make sure your var name is not a valid 3- or 6-length hex — yeah, kinda weird
                break;
            }
        }
        for (let A_Index111 = 0; A_Index111 < HTVM_Size(aliases_colon_color) + 0; A_Index111++) {
            if (StrLower(option0) == StrLower(aliases_colon_color[A_Index111])) {
                option0 = canonical_color;
                if (RegExMatch(option1, "^(([0-9a-fA-F]{2}){3}|([0-9a-fA-F]){3})$")) {
                    option1 = Chr(34) + "#" + option1 + Chr(34);
                } else {
                    if (InStr(option1, "#")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    }
                }
                // else it's just a var name, just make sure your var name is not a valid 3- or 6-length hex — yeah, kinda weird
                break;
            }
        }
        for (let A_Index112 = 0; A_Index112 < HTVM_Size(aliases_colon_rounding) + 0; A_Index112++) {
            if (StrLower(option0) == StrLower(aliases_colon_rounding[A_Index112])) {
                option0 = canonical_rounding;
                break;
            }
        }
        for (let A_Index113 = 0; A_Index113 < HTVM_Size(aliases_colon_border) + 0; A_Index113++) {
            if (StrLower(option0) == StrLower(aliases_colon_border[A_Index113])) {
                option0 = canonical_border;
                break;
            }
        }
        for (let A_Index114 = 0; A_Index114 < HTVM_Size(aliases_colon_rawCss) + 0; A_Index114++) {
            if (StrLower(option0) == StrLower(aliases_colon_rawCss[A_Index114])) {
                option0 = canonical_rawCss;
                break;
            }
        }
        for (let A_Index115 = 0; A_Index115 < HTVM_Size(aliases_colon_size) + 0; A_Index115++) {
            if (StrLower(option0) == StrLower(aliases_colon_size[A_Index115])) {
                option0 = canonical_size;
                break;
            }
        }
        for (let A_Index116 = 0; A_Index116 < HTVM_Size(aliases_colon_isEnabled) + 0; A_Index116++) {
            if (StrLower(option0) == StrLower(aliases_colon_isEnabled[A_Index116])) {
                option0 = canonical_isEnabled;
                break;
            }
        }
        for (let A_Index117 = 0; A_Index117 < HTVM_Size(aliases_colon_isVisible) + 0; A_Index117++) {
            if (StrLower(option0) == StrLower(aliases_colon_isVisible[A_Index117])) {
                option0 = canonical_isVisible;
                break;
            }
        }
        for (let A_Index118 = 0; A_Index118 < HTVM_Size(aliases_colon_isDeleting) + 0; A_Index118++) {
            if (StrLower(option0) == StrLower(aliases_colon_isDeleting[A_Index118])) {
                option0 = canonical_isDeleting;
                break;
            }
        }
        out = option0 + ":" + Trim(expressionParserTranspiler(Trim(option1)));
        //print("DEBUG out with (:) is: " . out)
    } else {
        option0 = SubStr(option, 1, 1);
        option1 = StringTrimLeft(option, 1);
        //print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=")
        //print(option)
        //print(option0)
        //print(option1)
        //print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=")
        for (let A_Index119 = 0; A_Index119 < HTVM_Size(aliases_single_id) + 0; A_Index119++) {
            if (StrLower(option0) == StrLower(aliases_single_id[A_Index119])) {
                option0 = canonical_id;
                break;
            }
        }
        for (let A_Index120 = 0; A_Index120 < HTVM_Size(aliases_single_parentId) + 0; A_Index120++) {
            if (StrLower(option0) == StrLower(aliases_single_parentId[A_Index120])) {
                option0 = canonical_parentId;
                break;
            }
        }
        for (let A_Index121 = 0; A_Index121 < HTVM_Size(aliases_single_x) + 0; A_Index121++) {
            if (StrLower(option0) == StrLower(aliases_single_x[A_Index121])) {
                option0 = canonical_x;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (let A_Index122 = 0; A_Index122 < HTVM_Size(aliases_single_y) + 0; A_Index122++) {
            if (StrLower(option0) == StrLower(aliases_single_y[A_Index122])) {
                option0 = canonical_y;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (let A_Index123 = 0; A_Index123 < HTVM_Size(aliases_single_width) + 0; A_Index123++) {
            if (StrLower(option0) == StrLower(aliases_single_width[A_Index123])) {
                option0 = canonical_width;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (let A_Index124 = 0; A_Index124 < HTVM_Size(aliases_single_height) + 0; A_Index124++) {
            if (StrLower(option0) == StrLower(aliases_single_height[A_Index124])) {
                option0 = canonical_height;
                if (RegExMatch(option1, "^-?\\d+(\\.\\d+)?(px|%)?$")) {
                    if (InStr(option1, "%") || InStr(option1, "px")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    } else {
                        option1 = Chr(34) + option1 + "px" + Chr(34);
                    }
                }
                break;
            }
        }
        for (let A_Index125 = 0; A_Index125 < HTVM_Size(aliases_single_zIndex) + 0; A_Index125++) {
            if (StrLower(option0) == StrLower(aliases_single_zIndex[A_Index125])) {
                option0 = canonical_zIndex;
                break;
            }
        }
        for (let A_Index126 = 0; A_Index126 < HTVM_Size(aliases_single_value) + 0; A_Index126++) {
            if (StrLower(option0) == StrLower(aliases_single_value[A_Index126])) {
                option0 = canonical_value;
                break;
            }
        }
        for (let A_Index127 = 0; A_Index127 < HTVM_Size(aliases_single_placeholder) + 0; A_Index127++) {
            if (StrLower(option0) == StrLower(aliases_single_placeholder[A_Index127])) {
                option0 = canonical_placeholder;
                break;
            }
        }
        for (let A_Index128 = 0; A_Index128 < HTVM_Size(aliases_single_callback) + 0; A_Index128++) {
            if (StrLower(option0) == StrLower(aliases_single_callback[A_Index128])) {
                option0 = canonical_callback;
                break;
            }
        }
        for (let A_Index129 = 0; A_Index129 < HTVM_Size(aliases_single_backgroundColor) + 0; A_Index129++) {
            if (StrLower(option0) == StrLower(aliases_single_backgroundColor[A_Index129])) {
                option0 = canonical_backgroundColor;
                if (RegExMatch(option1, "^(([0-9a-fA-F]{2}){3}|([0-9a-fA-F]){3})$")) {
                    option1 = Chr(34) + "#" + option1 + Chr(34);
                } else {
                    if (InStr(option1, "#")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    }
                }
                // else it's just a var name, just make sure your var name is not a valid 3- or 6-length hex — yeah, kinda weird
                break;
            }
        }
        for (let A_Index130 = 0; A_Index130 < HTVM_Size(aliases_single_color) + 0; A_Index130++) {
            if (StrLower(option0) == StrLower(aliases_single_color[A_Index130])) {
                option0 = canonical_color;
                if (RegExMatch(option1, "^(([0-9a-fA-F]{2}){3}|([0-9a-fA-F]){3})$")) {
                    option1 = Chr(34) + "#" + option1 + Chr(34);
                } else {
                    if (InStr(option1, "#")) {
                        option1 = Chr(34) + option1 + Chr(34);
                    }
                }
                // else it's just a var name, just make sure your var name is not a valid 3- or 6-length hex — yeah, kinda weird
                break;
            }
        }
        for (let A_Index131 = 0; A_Index131 < HTVM_Size(aliases_single_rounding) + 0; A_Index131++) {
            if (StrLower(option0) == StrLower(aliases_single_rounding[A_Index131])) {
                option0 = canonical_rounding;
                break;
            }
        }
        for (let A_Index132 = 0; A_Index132 < HTVM_Size(aliases_single_border) + 0; A_Index132++) {
            if (StrLower(option0) == StrLower(aliases_single_border[A_Index132])) {
                option0 = canonical_border;
                break;
            }
        }
        for (let A_Index133 = 0; A_Index133 < HTVM_Size(aliases_single_rawCss) + 0; A_Index133++) {
            if (StrLower(option0) == StrLower(aliases_single_rawCss[A_Index133])) {
                option0 = canonical_rawCss;
                break;
            }
        }
        for (let A_Index134 = 0; A_Index134 < HTVM_Size(aliases_single_size) + 0; A_Index134++) {
            if (StrLower(option0) == StrLower(aliases_single_size[A_Index134])) {
                option0 = canonical_size;
                break;
            }
        }
        for (let A_Index135 = 0; A_Index135 < HTVM_Size(aliases_single_isEnabled) + 0; A_Index135++) {
            if (StrLower(option0) == StrLower(aliases_single_isEnabled[A_Index135])) {
                option0 = canonical_isEnabled;
                break;
            }
        }
        for (let A_Index136 = 0; A_Index136 < HTVM_Size(aliases_single_isVisible) + 0; A_Index136++) {
            if (StrLower(option0) == StrLower(aliases_single_isVisible[A_Index136])) {
                option0 = canonical_isVisible;
                break;
            }
        }
        for (let A_Index137 = 0; A_Index137 < HTVM_Size(aliases_single_isDeleting) + 0; A_Index137++) {
            if (StrLower(option0) == StrLower(aliases_single_isDeleting[A_Index137])) {
                option0 = canonical_isDeleting;
                break;
            }
        }
        out = option0 + ":" + Trim(expressionParserTranspiler(Trim(option1)));
        //print("DEBUG out no (:) is: " . out)
    }
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function guiParserStep3(guiCode) {
    // convert the parsed code to func calls
    var out = "";
    var temp0 = "";
    var temp1 = "";
    var temp2 = "";
    var temp3 = "";
    var temp4 = "";
    var temp5 = "";
    var temp6 = "";
    var temp7 = "";
    var temp8 = "";
    var temp9 = "";
    var temp10 = "";
    var temp11 = "";
    var temp12 = "";
    var temp13 = "";
    var temp14 = "";
    var temp15 = "";
    var temp16 = "";
    var temp17 = "";
    var temp18 = "";
    var temp19 = "";
    var temp20 = "";
    var temp21 = "";
    var temp22 = "";
    var temp23 = "";
    var temp24 = "";
    var temp25 = "";
    var temp26 = "";
    var temp27 = "";
    var temp28 = "";
    var temp29 = "";
    var temp30 = "";
    var temp31 = "";
    var temp32 = "";
    var found_id = 0;
    var found_parentId = 0;
    var found_x = 0;
    var found_y = 0;
    var found_width = 0;
    var found_height = 0;
    var found_zIndex = 0;
    var found_value = 0;
    var found_placeholder = 0;
    var found_callback = 0;
    var found_backgroundColor = 0;
    var found_color = 0;
    var found_rounding = 0;
    var found_border = 0;
    var found_rawCss = 0;
    var found_size = 0;
    var found_isEnabled = 0;
    var found_isVisible = 0;
    var found_isDeleting = 0;
    var openCurlyTEXT = "wklajebawszopsne--tshecurlyybarxccsesgFORguiTHTVM0987HTVM---HTVMAAAadhksudahsdGUI_-_HTVM_OPEN-HTVM--GUI";
    var closeCurlyTEXT = "wklajebawszopsne--tshecurlyybarxccsesgFORguiTHTVM0987HTVM---HTVMAAAadhksudahsdGUI_-_HTVM_CLOSE-HTVM--GUI";
    var buttons = -1;
    var texts = -1;
    var edits = -1;
    var pictures = -1;
    var toggles = -1;
    var rectangles = -1;
    var circles = -1;
    var videos = -1;
    var dropdowns = -1;
    var iframes = -1;
    var isElement = 0;
    var whatElement = "";
    var lowerField = "";
    let items138 = LoopParseFunc(guiCode, "\n", "\r");
    for (let A_Index138 = 0; A_Index138 < items138.length + 0; A_Index138++) {
        const A_LoopField138 = items138[A_Index138 - 0];
        temp1 = "";
        temp2 = "";
        temp3 = "";
        temp4 = "";
        temp5 = "";
        temp6 = "";
        temp7 = "";
        temp8 = "";
        temp9 = "";
        temp10 = "";
        temp11 = "";
        temp12 = "";
        temp13 = "";
        temp14 = "";
        temp15 = "";
        temp16 = "";
        temp17 = "";
        temp18 = "";
        temp19 = "";
        temp20 = "";
        temp21 = "";
        temp22 = "";
        temp23 = "";
        temp24 = "";
        temp25 = "";
        temp26 = "";
        temp27 = "";
        temp28 = "";
        temp29 = "";
        temp30 = "";
        temp31 = "";
        temp32 = "";
        temp0 = "";
        if (SubStr(Trim(StrLower(A_LoopField138)), 1, 4) == "gui " || RegExMatch(StrLower(Trim(A_LoopField138)), "^gui[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            isElement = 0;
            whatElement = "";
            let items139 = LoopParseFunc(A_LoopField138, " ");
            for (let A_Index139 = 0; A_Index139 < items139.length + 0; A_Index139++) {
                const A_LoopField139 = items139[A_Index139 - 0];
                if (A_Index139 != 0) {
                    //;;;;;; 0start
                    //;;;;;; 0start (Inside the Loop, Parse, A_LoopField, " " in guiParserStep3)
                    // --- Check for Element Type Aliases ---
                    // Direct name, single-letter prefix 'e', or colon aliases
                    lowerField = StrLower(Trim(A_LoopField139));
                    if (lowerField == "button" || lowerField == "ebutton" || lowerField == "elementType:button" || lowerField == "element:button" || lowerField == "elmnt:button" || lowerField == "elmenet:button" || lowerField == "elment:button" || lowerField == "elemnt:button") {
                        buttons++;
                        isElement = 1;
                        whatElement = "button";
                    }
                    else if (lowerField == "text" || lowerField == "etext" || lowerField == "elementType:text" || lowerField == "element:text" || lowerField == "elmnt:text" || lowerField == "elmenet:text" || lowerField == "elment:text") {
                        texts++;
                        isElement = 1;
                        whatElement = "text";
                    }
                    else if (lowerField == "edit" || lowerField == "eedit" || lowerField == "elementType:edit" || lowerField == "element:edit" || lowerField == "elmnt:edit" || lowerField == "elmenet:edit" || lowerField == "elment:edit") {
                        edits++;
                        isElement = 1;
                        whatElement = "edit";
                    }
                    else if (lowerField == "picture" || lowerField == "epicture" || lowerField == "elementType:picture" || lowerField == "element:picture" || lowerField == "elmnt:picture" || lowerField == "elmenet:picture" || lowerField == "elment:picture") {
                        pictures++;
                        isElement = 1;
                        whatElement = "picture";
                    }
                    else if (lowerField == "toggle" || lowerField == "etoggle" || lowerField == "elementType:toggle" || lowerField == "element:toggle" || lowerField == "elmnt:toggle" || lowerField == "elmenet:toggle" || lowerField == "elment:toggle") {
                        toggles++;
                        isElement = 1;
                        whatElement = "toggle";
                    }
                    else if (lowerField == "rectangle" || lowerField == "erectangle" || lowerField == "elementType:rectangle" || lowerField == "element:rectangle" || lowerField == "elmnt:rectangle" || lowerField == "elmenet:rectangle" || lowerField == "elment:rectangle") {
                        rectangles++;
                        isElement = 1;
                        whatElement = "rectangle";
                    }
                    else if (lowerField == "circle" || lowerField == "ecircle" || lowerField == "elementType:circle" || lowerField == "element:circle" || lowerField == "elmnt:circle" || lowerField == "elmenet:circle" || lowerField == "elment:circle") {
                        circles++;
                        isElement = 1;
                        whatElement = "circle";
                    }
                    else if (lowerField == "video" || lowerField == "evideo" || lowerField == "elementType:video" || lowerField == "element:video" || lowerField == "elmnt:video" || lowerField == "elmenet:video" || lowerField == "elment:video") {
                        videos++;
                        isElement = 1;
                        whatElement = "video";
                    }
                    else if (lowerField == "dropdown" || lowerField == "edropdown" || lowerField == "elementType:dropdown" || lowerField == "element:dropdown" || lowerField == "elmnt:dropdown" || lowerField == "elmenet:dropdown" || lowerField == "elment:dropdown") {
                        dropdowns++;
                        isElement = 1;
                        whatElement = "dropdown";
                    }
                    else if (lowerField == "iframe" || lowerField == "eiframe" || lowerField == "elementType:iframe" || lowerField == "element:iframe" || lowerField == "elmnt:iframe" || lowerField == "elmenet:iframe" || lowerField == "elment:iframe") {
                        iframes++;
                        isElement = 1;
                        whatElement = "iframe";
                    } else {
                        temp1 += guiParserStep4(Trim(A_LoopField139)) + ", ";
                    }
                    //;;;;;; 0end
                    //;;;;; 1start
                    //;;;;; 1end
                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                }
            }
            //;;;;;;;;;;;;;;;;;;;;; -111
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            // step 5
            // step 5
            // step 5
            // step 5 add callback if not defined and more...
            found_id = 0;
            found_parentId = 0;
            found_x = 0;
            found_y = 0;
            found_width = 0;
            found_height = 0;
            found_zIndex = 0;
            found_value = 0;
            found_placeholder = 0;
            found_callback = 0;
            found_backgroundColor = 0;
            found_color = 0;
            found_rounding = 0;
            found_border = 0;
            found_rawCss = 0;
            found_size = 0;
            found_isEnabled = 0;
            found_isVisible = 0;
            found_isDeleting = 0;
            let items140 = LoopParseFunc(temp1, ",");
            for (let A_Index140 = 0; A_Index140 < items140.length + 0; A_Index140++) {
                const A_LoopField140 = items140[A_Index140 - 0];
                temp2 = Trim(A_LoopField140);
                if (StrSplit(temp2, ":", 1) == "id") {
                    found_id = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "parentId") {
                    found_parentId = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "x") {
                    found_x = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "y") {
                    found_y = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "width") {
                    found_width = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "height") {
                    found_height = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "zIndex") {
                    found_zIndex = 1;
                }
                else if (StrSplit(temp2, ":", 1) == "callback") {
                    found_callback = 1;
                }
            }
            //print("found_id:              " . STR(found_id))
            //print("found_parentId:        " . STR(found_parentId))
            //print("found_x:               " . STR(found_x))
            //print("found_y:               " . STR(found_y))
            //print("found_width:           " . STR(found_width))
            //print("found_height:          " . STR(found_height))
            //print("found_zIndex:          " . STR(found_zIndex))
            //print("found_value:           " . STR(found_value))
            //print("found_placeholder:     " . STR(found_placeholder))
            //print("found_callback:        " . STR(found_callback))
            //print("found_backgroundColor: " . STR(found_backgroundColor))
            //print("found_color:           " . STR(found_color))
            //print("found_rounding:        " . STR(found_rounding))
            //print("found_border:          " . STR(found_border))
            //print("found_rawCss:          " . STR(found_rawCss))
            //print("found_size:            " . STR(found_size))
            //print("found_isEnabled:       " . STR(found_isEnabled))
            //print("found_isVisible:       " . STR(found_isVisible))
            //print("found_isDeleting:      " . STR(found_isDeleting))
            if (isElement == 1 && found_callback == 0) {
                if (whatElement == "button") {
                    temp1 += "callback:" + Chr(34) + "Button" + STR(buttons) + Chr(34) + ", ";
                }
                else if (whatElement == "text") {
                    temp1 += "callback:" + Chr(34) + "Text" + STR(texts) + Chr(34) + ", ";
                }
                else if (whatElement == "edit") {
                    temp1 += "callback:" + Chr(34) + "Edit" + STR(edits) + Chr(34) + ", ";
                }
                else if (whatElement == "picture") {
                    temp1 += "callback:" + Chr(34) + "Picture" + STR(pictures) + Chr(34) + ", ";
                }
                else if (whatElement == "toggle") {
                    temp1 += "callback:" + Chr(34) + "Toggle" + STR(toggles) + Chr(34) + ", ";
                }
                else if (whatElement == "rectangle") {
                    temp1 += "callback:" + Chr(34) + "Rectangle" + STR(rectangles) + Chr(34) + ", ";
                }
                else if (whatElement == "circle") {
                    temp1 += "callback:" + Chr(34) + "Circle" + STR(circles) + Chr(34) + ", ";
                }
                else if (whatElement == "video") {
                    temp1 += "callback:" + Chr(34) + "Video" + STR(videos) + Chr(34) + ", ";
                }
                else if (whatElement == "dropdown") {
                    temp1 += "callback:" + Chr(34) + "Dropdown" + STR(dropdowns) + Chr(34) + ", ";
                }
                else if (whatElement == "iframe") {
                    temp1 += "callback:" + Chr(34) + "Iframe" + STR(iframes) + Chr(34) + ", ";
                }
            }
            if (found_parentId == 0 && isElement == 1) {
                temp1 += "parentId:" + Chr(34) + "div0" + Chr(34) + ", ";
            }
            // step 5
            // step 5
            // step 5
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (isElement == 1) {
                temp0 += "guiAddElement(" + openCurlyTEXT + " elementType: '" + whatElement + "', " + temp1;
                temp0 = StringTrimRight(temp0, 2);
                temp0 += " " + closeCurlyTEXT + ");";
            } else {
                temp0 += "guiAdd(" + openCurlyTEXT + " " + StrReplace(temp1, "parentId:", "id:");
                temp0 = StringTrimRight(temp0, 2);
                temp0 += " " + closeCurlyTEXT + ");";
            }
            //;;;;;;;;;;;;;;;;;;;;; -111
            out += temp0 + Chr(10);
        }
        else if (SubStr(Trim(StrLower(A_LoopField138)), 1, 11) == "guicontrol " || RegExMatch(StrLower(Trim(A_LoopField138)), "^guicontrol[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            isElement = 0;
            whatElement = "";
            let items141 = LoopParseFunc(A_LoopField138, " ");
            for (let A_Index141 = 0; A_Index141 < items141.length + 0; A_Index141++) {
                const A_LoopField141 = items141[A_Index141 - 0];
                if (A_Index141 != 0) {
                    //;;;;;; 0start
                    //;;;;;; 0start (Inside the Loop, Parse, A_LoopField, " " in guiParserStep3)
                    // --- Check for Element Type Aliases ---
                    // Direct name, single-letter prefix 'e', or colon aliases - all on one line per type
                    lowerField = StrLower(Trim(A_LoopField141));
                    if (lowerField == "button" || lowerField == "ebutton" || lowerField == "elementType:button" || lowerField == "element:button" || lowerField == "elmnt:button" || lowerField == "elmenet:button" || lowerField == "elment:button" || lowerField == "elemnt:button") {
                        buttons++;
                        isElement = 1;
                        whatElement = "button";
                    }
                    else if (lowerField == "text" || lowerField == "etext" || lowerField == "elementType:text" || lowerField == "element:text" || lowerField == "elmnt:text" || lowerField == "elmenet:text" || lowerField == "elment:text") {
                        texts++;
                        isElement = 1;
                        whatElement = "text";
                    }
                    else if (lowerField == "edit" || lowerField == "eedit" || lowerField == "elementType:edit" || lowerField == "element:edit" || lowerField == "elmnt:edit" || lowerField == "elmenet:edit" || lowerField == "elment:edit") {
                        edits++;
                        isElement = 1;
                        whatElement = "edit";
                    }
                    else if (lowerField == "picture" || lowerField == "epicture" || lowerField == "elementType:picture" || lowerField == "element:picture" || lowerField == "elmnt:picture" || lowerField == "elmenet:picture" || lowerField == "elment:picture") {
                        pictures++;
                        isElement = 1;
                        whatElement = "picture";
                    }
                    else if (lowerField == "toggle" || lowerField == "etoggle" || lowerField == "elementType:toggle" || lowerField == "element:toggle" || lowerField == "elmnt:toggle" || lowerField == "elmenet:toggle" || lowerField == "elment:toggle") {
                        toggles++;
                        isElement = 1;
                        whatElement = "toggle";
                    }
                    else if (lowerField == "rectangle" || lowerField == "erectangle" || lowerField == "elementType:rectangle" || lowerField == "element:rectangle" || lowerField == "elmnt:rectangle" || lowerField == "elmenet:rectangle" || lowerField == "elment:rectangle") {
                        rectangles++;
                        isElement = 1;
                        whatElement = "rectangle";
                    }
                    else if (lowerField == "circle" || lowerField == "ecircle" || lowerField == "elementType:circle" || lowerField == "element:circle" || lowerField == "elmnt:circle" || lowerField == "elmenet:circle" || lowerField == "elment:circle") {
                        circles++;
                        isElement = 1;
                        whatElement = "circle";
                    }
                    else if (lowerField == "video" || lowerField == "evideo" || lowerField == "elementType:video" || lowerField == "element:video" || lowerField == "elmnt:video" || lowerField == "elmenet:video" || lowerField == "elment:video") {
                        videos++;
                        isElement = 1;
                        whatElement = "video";
                    }
                    else if (lowerField == "dropdown" || lowerField == "edropdown" || lowerField == "elementType:dropdown" || lowerField == "element:dropdown" || lowerField == "elmnt:dropdown" || lowerField == "elmenet:dropdown" || lowerField == "elment:dropdown") {
                        dropdowns++;
                        isElement = 1;
                        whatElement = "dropdown";
                    }
                    else if (lowerField == "iframe" || lowerField == "eiframe" || lowerField == "elementType:iframe" || lowerField == "element:iframe" || lowerField == "elmnt:iframe" || lowerField == "elmenet:iframe" || lowerField == "elment:iframe") {
                        iframes++;
                        isElement = 1;
                        whatElement = "iframe";
                    } else {
                        temp1 += guiParserStep4(Trim(A_LoopField141)) + ", ";
                    }
                    //;;;;;; 0end
                    //;;;;; 1start
                    //;;;;; 1end
                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                }
            }
            //;;;;;;;;;;;;;;;;;;;;; -111
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            // step 5
            // step 5
            // step 5
            // step 5 add callback if not defined and more...
            found_id = 0;
            found_parentId = 0;
            found_x = 0;
            found_y = 0;
            found_width = 0;
            found_height = 0;
            found_zIndex = 0;
            found_value = 0;
            found_placeholder = 0;
            found_callback = 0;
            found_backgroundColor = 0;
            found_color = 0;
            found_rounding = 0;
            found_border = 0;
            found_rawCss = 0;
            found_size = 0;
            found_isEnabled = 0;
            found_isVisible = 0;
            found_isDeleting = 0;
            let items142 = LoopParseFunc(temp1, ",");
            for (let A_Index142 = 0; A_Index142 < items142.length + 0; A_Index142++) {
                const A_LoopField142 = items142[A_Index142 - 0];
                temp2 = Trim(A_LoopField142);
                if (StrSplit(temp2, ":", 1) == "parentId") {
                    found_parentId = 1;
                }
            }
            // print("found_parentId: " . STR(found_parentId))
            if (found_parentId == 0) {
                temp1 += "parentId:" + Chr(34) + "div0" + Chr(34) + ", ";
            }
            // step 5
            // step 5
            // step 5
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (isElement == 1) {
                temp0 += "guiControl(" + openCurlyTEXT + " elementType: '" + whatElement + "', " + temp1;
                temp0 = StringTrimRight(temp0, 2);
                temp0 += " " + closeCurlyTEXT + ");";
            } else {
                temp0 += "guiControl(" + openCurlyTEXT + " " + temp1;
                temp0 = StringTrimRight(temp0, 2);
                temp0 += " " + closeCurlyTEXT + ");";
            }
            //;;;;;;;;;;;;;;;;;;;;; -111
            out += temp0 + Chr(10);
        } else {
            out += A_LoopField138 + Chr(10);
        }
    }
    out = StringTrimRight(out, 1);
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function guiParserStep2(guiCode) {
    // remove spacses, commas and format the colon (:) and remove "add"
    var out = "";
    var temp = "";
    let items143 = LoopParseFunc(guiCode, "\n", "\r");
    for (let A_Index143 = 0; A_Index143 < items143.length + 0; A_Index143++) {
        const A_LoopField143 = items143[A_Index143 - 0];
        if (SubStr(Trim(StrLower(A_LoopField143)), 1, 11) == "guicontrol " || SubStr(Trim(StrLower(A_LoopField143)), 1, 11) == "guicontrol," || RegExMatch(StrLower(Trim(A_LoopField143)), "^guicontrol[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            temp = StrReplace(A_LoopField143, ",", " ");
            while (InStr(temp, "  ")) {
                temp = StrReplace(temp, "  ", " ");
            }
            while (InStr(temp, ": ")) {
                temp = StrReplace(temp, ": ", ":");
            }
            while (InStr(temp, " :")) {
                temp = StrReplace(temp, " :", ":");
            }
            out += Trim(temp) + Chr(10);
        }
        else if (SubStr(Trim(StrLower(A_LoopField143)), 1, 4) == "gui " || SubStr(Trim(StrLower(A_LoopField143)), 1, 4) == "gui," || RegExMatch(StrLower(Trim(A_LoopField143)), "^gui[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            temp = StrReplace(A_LoopField143, ",", " ");
            temp = RegExReplace(temp, "\\badd\\b(?!\\()", " ");
            while (InStr(temp, "  ")) {
                temp = StrReplace(temp, "  ", " ");
            }
            while (InStr(temp, ": ")) {
                temp = StrReplace(temp, ": ", ":");
            }
            while (InStr(temp, " :")) {
                temp = StrReplace(temp, " :", ":");
            }
            out += Trim(temp) + Chr(10);
        } else {
            out += A_LoopField143 + Chr(10);
        }
    }
    out = StringTrimRight(out, 1);
    return guiParserStep3(out);
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function guiParser0(guiCode) {
    var out = "";
    var begin = 0;
    let lookAhead = [];
    let items144 = LoopParseFunc(guiCode, "\n", "\r");
    for (let A_Index144 = 0; A_Index144 < items144.length + 0; A_Index144++) {
        const A_LoopField144 = items144[A_Index144 - 0];
        HTVM_Append(lookAhead, Trim(A_LoopField144));
    }
    HTVM_Append(lookAhead, " ");
    let items145 = LoopParseFunc(guiCode, "\n", "\r");
    for (let A_Index145 = 0; A_Index145 < items145.length + 0; A_Index145++) {
        const A_LoopField145 = items145[A_Index145 - 0];
        if (Trim(StrLower(A_LoopField145)) == "guicontrol" || SubStr(Trim(StrLower(A_LoopField145)), 1, 11) == "guicontrol " || SubStr(Trim(StrLower(A_LoopField145)), 1, 11) == "guicontrol," || SubStr(Trim(StrLower(A_LoopField145)), 1, 11) == "guicontrol{" || SubStr(Trim(StrLower(A_LoopField145)), 1, 12) == "guicontrol {" || SubStr(Trim(StrLower(A_LoopField145)), 1, 13) == "guicontrol  {" || SubStr(Trim(StrLower(A_LoopField145)), 1, 11) == "guicontrol[" || SubStr(Trim(StrLower(A_LoopField145)), 1, 12) == "guicontrol [" || SubStr(Trim(StrLower(A_LoopField145)), 1, 13) == "guicontrol  [" || SubStr(Trim(StrLower(A_LoopField145)), 1, 11) == "guicontrol(" || SubStr(Trim(StrLower(A_LoopField145)), 1, 12) == "guicontrol (" || SubStr(Trim(StrLower(A_LoopField145)), 1, 13) == "guicontrol  (" || RegExMatch(StrLower(Trim(A_LoopField145)), "^guicontrol[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            begin = 0;
            if (Trim(StrLower(lookAhead[A_Index145 + 1])) == "{" || Trim(StrLower(lookAhead[A_Index145 + 1])) == "[" || Trim(StrLower(lookAhead[A_Index145 + 1])) == "(") {
                begin = 1;
            }
            if (RegExMatch(StrLower(Trim(A_LoopField145)), "^guicontrol[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)") && SubStrLastChars(Trim(A_LoopField145), 1) == "{" || SubStrLastChars(Trim(A_LoopField145), 1) == "[" || SubStrLastChars(Trim(A_LoopField145), 1) == "(") {
                begin = 1;
                out += StringTrimRight(Trim(A_LoopField145), 1);
            }
            else if (SubStr(Trim(StrLower(A_LoopField145)), 1, 11) == "guicontrol{") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField145), 11);
            }
            else if (SubStr(Trim(StrLower(A_LoopField145)), 1, 11) == "guicontrol[") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField145), 11);
            }
            else if (SubStr(Trim(StrLower(A_LoopField145)), 1, 11) == "guicontrol(") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField145), 11);
            }
            else if (SubStr(Trim(StrLower(A_LoopField145)), 1, 12) == "guicontrol {") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField145), 12);
            }
            else if (SubStr(Trim(StrLower(A_LoopField145)), 1, 12) == "guicontrol [") {
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField145), 12);
            }
            else if (SubStr(Trim(StrLower(A_LoopField145)), 1, 12) == "guicontrol (") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField145), 12);
            }
            else if (SubStr(Trim(StrLower(A_LoopField145)), 1, 13) == "guicontrol  {") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField145), 13);
            }
            else if (SubStr(Trim(StrLower(A_LoopField145)), 1, 13) == "guicontrol  [") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField145), 13);
            }
            else if (SubStr(Trim(StrLower(A_LoopField145)), 1, 13) == "guicontrol  (") {
                begin = 1;
                out += "guicontrol " + StringTrimLeft(Trim(A_LoopField145), 13);
            } else {
                if (begin == 1) {
                    out += Trim(A_LoopField145) + " ";
                } else {
                    out += Trim(A_LoopField145) + Chr(10);
                }
            }
        }
        else if (begin == 1) {
            if (Trim(StrLower(A_LoopField145)) == "{" || Trim(StrLower(A_LoopField145)) == "[" || Trim(StrLower(A_LoopField145)) == "(") {
                begin = 1;
            }
            else if (Trim(StrLower(A_LoopField145)) == "}" || Trim(StrLower(A_LoopField145)) == "]" || Trim(StrLower(A_LoopField145)) == ")") {
                begin = 0;
                out += Chr(10);
            } else {
                if (SubStr(Trim(A_LoopField145), 1, StrLen(keyWordComment)) != keyWordComment) {
                    out += A_LoopField145 + " ";
                }
            }
        } else {
            out += A_LoopField145 + Chr(10);
        }
        //print("DEBIG123: " . A_LoopField . "|" . STR(begin))
    }
    out = StringTrimRight(out, 1);
    return guiParserStep2(out);
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function guiParser(guiCode) {
    var doWeExitGUIfuncCuzNoGuiFound = 1;
    var doWeExitGUIfuncCuzNoGuiFoundINcommentBlock = 0;
    let items146 = LoopParseFunc(guiCode, "\n", "\r");
    for (let A_Index146 = 0; A_Index146 < items146.length + 0; A_Index146++) {
        const A_LoopField146 = items146[A_Index146 - 0];
        if (Trim(A_LoopField146) == Trim(keyWordCommentOpenMultiLine)) {
            doWeExitGUIfuncCuzNoGuiFoundINcommentBlock = 1;
        }
        if (Trim(A_LoopField146) == Trim(keyWordCommentCloseMultiLine)) {
            doWeExitGUIfuncCuzNoGuiFoundINcommentBlock = 0;
        }
        if (Trim(StrLower(A_LoopField146)) == "gui" || SubStr(Trim(StrLower(A_LoopField146)), 1, 4) == "gui " || SubStr(Trim(StrLower(A_LoopField146)), 1, 4) == "gui," || SubStr(Trim(StrLower(A_LoopField146)), 1, 4) == "gui{" || SubStr(Trim(StrLower(A_LoopField146)), 1, 5) == "gui {" || SubStr(Trim(StrLower(A_LoopField146)), 1, 6) == "gui  {" || SubStr(Trim(StrLower(A_LoopField146)), 1, 4) == "gui[" || SubStr(Trim(StrLower(A_LoopField146)), 1, 5) == "gui [" || SubStr(Trim(StrLower(A_LoopField146)), 1, 6) == "gui  [" || SubStr(Trim(StrLower(A_LoopField146)), 1, 4) == "gui(" || SubStr(Trim(StrLower(A_LoopField146)), 1, 5) == "gui (" || SubStr(Trim(StrLower(A_LoopField146)), 1, 6) == "gui  (" || RegExMatch(StrLower(Trim(A_LoopField146)), "^gui[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            if (doWeExitGUIfuncCuzNoGuiFoundINcommentBlock == 0) {
                doWeExitGUIfuncCuzNoGuiFound = 0;
            }
        }
    }
    if (doWeExitGUIfuncCuzNoGuiFound == 1) {
        return guiCode;
    }
    var out = "";
    var whenGuiBegin = 0;
    var whenGuiBeginTHEONE = 0;
    var begin = 0;
    let lookAhead = [];
    let items147 = LoopParseFunc(guiCode, "\n", "\r");
    for (let A_Index147 = 0; A_Index147 < items147.length + 0; A_Index147++) {
        const A_LoopField147 = items147[A_Index147 - 0];
        HTVM_Append(lookAhead, Trim(A_LoopField147));
    }
    HTVM_Append(lookAhead, " ");
    let items148 = LoopParseFunc(guiCode, "\n", "\r");
    for (let A_Index148 = 0; A_Index148 < items148.length + 0; A_Index148++) {
        const A_LoopField148 = items148[A_Index148 - 0];
        if (Trim(StrLower(lookAhead[A_Index148 + 1])) != "{" && Trim(StrLower(lookAhead[A_Index148 + 1])) != "[" && Trim(StrLower(lookAhead[A_Index148 + 1])) != "(" && Trim(StrLower(A_LoopField148)) == "gui") {
            begin = 0;
            //print("DUBUG HKDOUVISYobusdsfvbaedsf")
            whenGuiBegin++;
            if (whenGuiBegin == 1) {
                whenGuiBeginTHEONE = 1;
                out = "HTVM--__gui_init-null,nulllllllllllllldasdfxuoifsedfuiJHTVM---HTVMguiNO-jsadsfpisszdjfpisasJz-HTVM-GUI" + Chr(10) + out;
            }
        }
        else if (Trim(StrLower(A_LoopField148)) == "gui" || SubStr(Trim(StrLower(A_LoopField148)), 1, 4) == "gui " || SubStr(Trim(StrLower(A_LoopField148)), 1, 4) == "gui," || SubStr(Trim(StrLower(A_LoopField148)), 1, 4) == "gui{" || SubStr(Trim(StrLower(A_LoopField148)), 1, 5) == "gui {" || SubStr(Trim(StrLower(A_LoopField148)), 1, 6) == "gui  {" || SubStr(Trim(StrLower(A_LoopField148)), 1, 4) == "gui[" || SubStr(Trim(StrLower(A_LoopField148)), 1, 5) == "gui [" || SubStr(Trim(StrLower(A_LoopField148)), 1, 6) == "gui  [" || SubStr(Trim(StrLower(A_LoopField148)), 1, 4) == "gui(" || SubStr(Trim(StrLower(A_LoopField148)), 1, 5) == "gui (" || SubStr(Trim(StrLower(A_LoopField148)), 1, 6) == "gui  (" || RegExMatch(StrLower(Trim(A_LoopField148)), "^gui[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)")) {
            begin = 0;
            whenGuiBegin++;
            if (whenGuiBegin == 1) {
                out = "HTVM--__gui_init-null,nulllllllllllllldasdfxuoifsedfuiJHTVM---HTVMguiNO-jsadsfpisszdjfpisasJz-HTVM-GUI" + Chr(10) + out;
            }
            if (Trim(StrLower(lookAhead[A_Index148 + 1])) == "{" || Trim(StrLower(lookAhead[A_Index148 + 1])) == "[" || Trim(StrLower(lookAhead[A_Index148 + 1])) == "(") {
                begin = 1;
            }
            if (RegExMatch(StrLower(Trim(A_LoopField148)), "^gui[-_][A-Za-z0-9_]+(?:[-_][A-Za-z0-9_]+)*(?=[, ]|$)") && SubStrLastChars(Trim(A_LoopField148), 1) == "{" || SubStrLastChars(Trim(A_LoopField148), 1) == "[" || SubStrLastChars(Trim(A_LoopField148), 1) == "(") {
                begin = 1;
                out += StringTrimRight(Trim(A_LoopField148), 1);
            }
            else if (SubStr(Trim(StrLower(A_LoopField148)), 1, 4) == "gui{") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField148), 4);
            }
            else if (SubStr(Trim(StrLower(A_LoopField148)), 1, 4) == "gui[") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField148), 4);
            }
            else if (SubStr(Trim(StrLower(A_LoopField148)), 1, 4) == "gui(") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField148), 4);
            }
            else if (SubStr(Trim(StrLower(A_LoopField148)), 1, 5) == "gui {") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField148), 5);
            }
            else if (SubStr(Trim(StrLower(A_LoopField148)), 1, 5) == "gui [") {
                out += "gui " + StringTrimLeft(Trim(A_LoopField148), 5);
            }
            else if (SubStr(Trim(StrLower(A_LoopField148)), 1, 5) == "gui (") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField148), 5);
            }
            else if (SubStr(Trim(StrLower(A_LoopField148)), 1, 6) == "gui  {") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField148), 6);
            }
            else if (SubStr(Trim(StrLower(A_LoopField148)), 1, 6) == "gui  [") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField148), 6);
            }
            else if (SubStr(Trim(StrLower(A_LoopField148)), 1, 6) == "gui  (") {
                begin = 1;
                out += "gui " + StringTrimLeft(Trim(A_LoopField148), 6);
            } else {
                if (begin == 1) {
                    out += Trim(A_LoopField148) + " ";
                } else {
                    out += Trim(A_LoopField148) + Chr(10);
                }
            }
        }
        else if (begin == 1) {
            if (Trim(StrLower(A_LoopField148)) == "{" || Trim(StrLower(A_LoopField148)) == "[" || Trim(StrLower(A_LoopField148)) == "(") {
                begin = 1;
            }
            else if (Trim(StrLower(A_LoopField148)) == "}" || Trim(StrLower(A_LoopField148)) == "]" || Trim(StrLower(A_LoopField148)) == ")") {
                begin = 0;
                out += Chr(10);
            } else {
                if (SubStr(Trim(A_LoopField148), 1, StrLen(keyWordComment)) != keyWordComment) {
                    out += A_LoopField148 + " ";
                }
            }
        } else {
            out += A_LoopField148 + Chr(10);
        }
        //print("DEBIG123: " . A_LoopField . "|" . STR(begin))
    }
    var openCurlyTEXT = "wklajebawszopsne--tshecurlyybarxccsesgFORguiTHTVM0987HTVM---HTVMAAAadhksudahsdGUI_-_HTVM_OPEN-HTVM--GUI";
    var closeCurlyTEXT = "wklajebawszopsne--tshecurlyybarxccsesgFORguiTHTVM0987HTVM---HTVMAAAadhksudahsdGUI_-_HTVM_CLOSE-HTVM--GUI";
    if (whenGuiBeginTHEONE == 1 && whenGuiBegin == 1) {
        out = StrReplace(out, "HTVM--__gui_init-null,nulllllllllllllldasdfxuoifsedfuiJHTVM---HTVMguiNO-jsadsfpisszdjfpisasJz-HTVM-GUI", "guiInit(" + Chr(34) + "#202020" + Chr(34) + ", " + Chr(34) + "This is a GUI" + Chr(34) + ");");
    } else {
        out = StrReplace(out, "HTVM--__gui_init-null,nulllllllllllllldasdfxuoifsedfuiJHTVM---HTVMguiNO-jsadsfpisszdjfpisasJz-HTVM-GUI", "guiInit(" + Chr(34) + "#202020" + Chr(34) + ", " + Chr(34) + Chr(34) + ");" + Chr(10) + " guiAdd(" + openCurlyTEXT + " x:" + Chr(34) + "0px" + Chr(34) + ", y:" + Chr(34) + "0px" + Chr(34) + ", width:" + Chr(34) + "100%" + Chr(34) + ", height:" + Chr(34) + "100%" + Chr(34) + ", id:" + Chr(34) + "div0" + Chr(34) + ", backgroundColor:" + Chr(34) + "#202020" + Chr(34) + ", rounding:0" + " " + closeCurlyTEXT + ");" + Chr(10));
    }
    out = StringTrimRight(out, 1);
    if (InStr(StrLower(out), "guicontrol")) {
        return guiParser0(out);
    } else {
        return guiParserStep2(out);
    }
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function initializeBackendAndGUIInteractionWithLabelSubroutineLikeButConvertsToFunction(codeToConvert) {
    var out = "";
    var temp = "";
    var temp1 = "";
    var temp2 = "";
    var firstTimePythonIn = 0;
    var wasHereNeedFixEndpointCall = 0;
    let items149 = LoopParseFunc(codeToConvert, "\n", "\r");
    for (let A_Index149 = 0; A_Index149 < items149.length + 0; A_Index149++) {
        const A_LoopField149 = items149[A_Index149 - 0];
        if (RegExMatch(Trim(A_LoopField149), "^[a-zA-Z_][a-zA-Z0-9_]*:$") && isLineAconstruct(Trim(A_LoopField149)) == false) {
            //print("DEBUG: " . A_LoopField)
            temp = StringTrimRight(Trim(A_LoopField149), 1);
            if (langToConvertTo == "js") {
                out += Trim(keyWordAsync) + " " + Trim(keyWordFunc) + " " + Trim(temp) + "(A_Id, A_Event, A_Value )" + Chr(10) + "{" + Chr(10);
            }
            else if (langToConvertTo == "py") {
                initializeBackendAndGUIInteractionWithLabelSubroutineLikeButConvertsToFunction_WAS_IN_PYTHON = 1;
                firstTimePythonIn++;
                if (firstTimePythonIn == 1) {
                    out += Trim(keyWordComment) + " added the HTVM_custom_port()" + Chr(10) + Trim(keyWordComment) + " added the HTVM_register()" + Chr(10) + Trim(keyWordComment) + " added the HTVM_init()" + Chr(10) + Trim(keyWordFunc) + " " + Trim(temp) + "(A_Input=" + Chr(34) + "" + Chr(34) + " )" + Chr(10) + "{" + Chr(10);
                } else {
                    out += Trim(keyWordFunc) + " " + Trim(temp) + "(A_Input=" + Chr(34) + "" + Chr(34) + " )" + Chr(10) + "{" + Chr(10);
                }
            } else {
                out += "!!!NOT POISBLE ONLY POSIBLE IN JS AND PY!!!" + Chr(10);
            }
            // endpoint, enpointName, enpointFunc, [reqType]
            // fileinit, index.html or someJsFile.js or someHtmlFile.html it can be both .html and .js file
            // port, 8000
        }
        else if (SubStr(Trim(StrLower(A_LoopField149)), 1, 9) == "endpoint,") {
            // HTVM_register("endpointName", "endpointName", method="POST")
            temp1 = "";
            let items150 = LoopParseFunc(Trim(A_LoopField149), ",");
            for (let A_Index150 = 0; A_Index150 < items150.length + 0; A_Index150++) {
                const A_LoopField150 = items150[A_Index150 - 0];
                temp = Trim(A_LoopField150);
                if (A_Index150 != 0) {
                    if (A_Index150 == 1) {
                        if (InStr(temp, Chr(34))) {
                            temp1 += temp + ", ";
                            temp2 = temp;
                        } else {
                            temp1 += Chr(34) + temp + Chr(34) + ", ";
                            temp2 = Chr(34) + temp + Chr(34);
                        }
                    }
                    else if (A_Index150 == 2) {
                        wasHereNeedFixEndpointCall = 1;
                        if (InStr(temp, Chr(34))) {
                            temp1 += temp + ", ";
                        } else {
                            temp1 += Chr(34) + temp + Chr(34) + ", ";
                        }
                    }
                    else if (A_Index150 == 3) {
                        if (InStr(temp, Chr(34))) {
                            temp1 += temp + ", ";
                        } else {
                            temp1 += Chr(34) + temp + Chr(34) + ", ";
                        }
                    } else {
                        if (InStr(temp, Chr(34))) {
                            temp1 += temp + ", ";
                        } else {
                            temp1 += Chr(34) + temp + Chr(34) + ", ";
                        }
                    }
                }
            }
            if (wasHereNeedFixEndpointCall == 0) {
                temp1 += temp2;
            } else {
                temp1 = StringTrimRight(temp1, 2);
            }
            out += "HTVM_register(" + temp1 + ")" + Chr(10);
        }
        else if (SubStr(Trim(StrLower(A_LoopField149)), 1, 9) == "fileinit,") {
            // HTVM_init("fileName")
            temp1 = "";
            let items151 = LoopParseFunc(Trim(A_LoopField149), ",");
            for (let A_Index151 = 0; A_Index151 < items151.length + 0; A_Index151++) {
                const A_LoopField151 = items151[A_Index151 - 0];
                temp = Trim(A_LoopField151);
                if (A_Index151 != 0) {
                    if (A_Index151 == 1) {
                        if (InStr(temp, Chr(34))) {
                            temp1 += temp;
                        } else {
                            temp1 += Chr(34) + temp + Chr(34);
                        }
                    }
                }
            }
            out += "HTVM_init(" + temp1 + ")" + Chr(10);
        }
        else if (SubStr(Trim(StrLower(A_LoopField149)), 1, 5) == "port,") {
            // HTVM_custom_port("fileName")
            temp1 = "";
            let items152 = LoopParseFunc(Trim(A_LoopField149), ",");
            for (let A_Index152 = 0; A_Index152 < items152.length + 0; A_Index152++) {
                const A_LoopField152 = items152[A_Index152 - 0];
                temp = Trim(A_LoopField152);
                if (A_Index152 != 0) {
                    if (A_Index152 == 1) {
                        temp1 += temp;
                    }
                }
            }
            temp1 = Trim(StrReplace(temp1, Chr(34), ""));
            out += "HTVM_custom_port(" + temp1 + ")" + Chr(10);
        }
        else if (Trim(StrLower(A_LoopField149)) == "subout") {
            out += "}" + Chr(10);
        } else {
            out += A_LoopField149 + Chr(10);
        }
    }
    out = StringTrimRight(out, 1);
    return out;
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
function fString(line) {
    if (langToConvertTo != langFileExtension_2) {
        line = StrReplace(line, "{", Chr(34) + " + fstr(");
        line = StrReplace(line, "}", ") + " + Chr(34));
    }
    return line;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// --------------------------------------------------
// TrimR Function Definition
// Removes trailing whitespace (space, tab, newline, carriage return)
// from the right side of a string.
// Parameters:
//   inputString (str): The string to trim.
// Returns:
//   str: The string with trailing whitespace removed.
// --------------------------------------------------
function TrimR(inputString) {
    var len = StrLen(inputString);
    var lastNonWhitespaceIndex = 0;
    // Handle empty string immediately
    if (len == 0) {
        return "";
    }
    var charr = "";
    // Loop backwards from the last character (index len) down to the first (index 1)
    var i = len;
    while (i >= 1) {
        // Get the character at the current index (using 1-based SubStr)
        charr = SubStr(inputString, i, 1);
        // Check if the character is NOT whitespace
        if (charr != " " && charr != Chr(9) && charr != Chr(13) && charr != Chr(10)) {
            // This is the last non-whitespace character found
            lastNonWhitespaceIndex = i;
            break;
        }
        // Decrement index to check the previous character
        i = i - 1;
    }
    // If no non-whitespace character was found (string was all whitespace)
    if (lastNonWhitespaceIndex == 0) {
        return "";
    }
    // Extract the substring from the beginning (index 1) up to the
    // last non-whitespace character found (index lastNonWhitespaceIndex)
    return SubStr(inputString, 1, lastNonWhitespaceIndex);
}
function handleMultiLineStrings(code) {
    var didWeFindOrWeOut = 0;
    let items153 = LoopParseFunc(code, "\n", "\r");
    for (let A_Index153 = 0; A_Index153 < items153.length + 0; A_Index153++) {
        const A_LoopField153 = items153[A_Index153 - 0];
        if (SubStrLastChars(Trim(A_LoopField153), 4) == " mls" || SubStrLastChars(Trim(A_LoopField153), 5) == " fmls") {
            didWeFindOrWeOut = 1;
        }
    }
    if (didWeFindOrWeOut == 0) {
        return code;
    }
    var out = "";
    code = StrReplace(code, Chr(10) , Chr(10) + "HTVM-newLineAHw4y9w730q8237w4e8srhgesw0s8rgw04e5g08sgr0e8srdgt--YOU-BETERNOTUSETHISAH--aesdfssz" + Chr(10));
    let lookAhead = [];
    let items154 = LoopParseFunc(code, "\n", "\r");
    for (let A_Index154 = 0; A_Index154 < items154.length + 0; A_Index154++) {
        const A_LoopField154 = items154[A_Index154 - 0];
        HTVM_Append(lookAhead, Trim(A_LoopField154));
    }
    HTVM_Append(lookAhead, Trim(" "));
    var weAreIn = 0;
    var weAreInOnce = 0;
    var weAreInNum = 0;
    var weAreInMLSarrTemp = "";
    let items155 = LoopParseFunc(code, "\n", "\r");
    for (let A_Index155 = 0; A_Index155 < items155.length + 0; A_Index155++) {
        const A_LoopField155 = items155[A_Index155 - 0];
        if (langToConvertTo == langFileExtension_2) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (weAreIn == 1 && Trim(A_LoopField155) == "mle") {
                HTVM_Append(weAreInMLSarr, StringTrimRight(StringTrimLeft(StrReplace(weAreInMLSarrTemp, "HTVM-newLineAHw4y9w730q8237w4e8srhgesw0s8rgw04e5g08sgr0e8srdgt--YOU-BETERNOTUSETHISAH--aesdfssz", Chr(10)), 1), 1));
                weAreInMLSarrTemp = "";
                weAreInOnce = 0;
                weAreIn = 0;
            }
            if (weAreIn == 1) {
                weAreInOnce++;
                if (weAreInOnce == 1) {
                    out += "aejsoydoxubviycbdgsut7eoy-ihsxbvhowadesdio6376e7wuwyuau--szd--AA" + STR(weAreInNum) + "AA" + Chr(10);
                    weAreInNum++;
                }
                weAreInMLSarrTemp += A_LoopField155;
            }
            if (SubStrLastChars(Trim(A_LoopField155), 4) == " mls" || SubStrLastChars(Trim(A_LoopField155), 5) == " fmls") {
                weAreIn = 1;
                out += A_LoopField155 + Chr(10);
            }
            if (weAreIn == 0) {
                out += A_LoopField155 + Chr(10);
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        } else {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (weAreIn == 1 && Trim(A_LoopField155) == "mle") {
                out = StringTrimRight(out, 2);
                out += Chr(34) + Chr(10);
                weAreIn = 0;
            }
            if (weAreIn == 1 && Trim(A_LoopField155) == "HTVM-newLineAHw4y9w730q8237w4e8srhgesw0s8rgw04e5g08sgr0e8srdgt--YOU-BETERNOTUSETHISAH--aesdfssz") {
                if (lookAhead[A_Index155 + 1] == "HTVM-newLineAHw4y9w730q8237w4e8srhgesw0s8rgw04e5g08sgr0e8srdgt--YOU-BETERNOTUSETHISAH--aesdfssz") {
                    out += keyWordEscpaeChar + "n";
                }
            }
            if (weAreIn == 1 && Trim(A_LoopField155) != "HTVM-newLineAHw4y9w730q8237w4e8srhgesw0s8rgw04e5g08sgr0e8srdgt--YOU-BETERNOTUSETHISAH--aesdfssz") {
                out += A_LoopField155 + keyWordEscpaeChar + "n";
            }
            if (SubStrLastChars(Trim(A_LoopField155), 4) == " mls" || SubStrLastChars(Trim(A_LoopField155), 5) == " fmls") {
                weAreIn = 1;
                if (SubStrLastChars(Trim(A_LoopField155), 5) == " fmls") {
                    out += TrimR(StringTrimRight(TrimR(A_LoopField155), 3)) + Chr(34);
                } else {
                    out += TrimR(StringTrimRight(TrimR(A_LoopField155), 3)) + " " + Chr(34);
                }
            }
            if (weAreIn == 0) {
                if (Trim(A_LoopField155) != "mle") {
                    out += A_LoopField155 + Chr(10);
                }
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        }
    }
    out = StrReplace(out, "HTVM-newLineAHw4y9w730q8237w4e8srhgesw0s8rgw04e5g08sgr0e8srdgt--YOU-BETERNOTUSETHISAH--aesdfssz", Chr(10) + Chr(10));
    out = StringTrimRight(out, 1);
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function slidingWinFixCommentsRmFUNC(line) {
    let slidingWinFixCommentsRmFFFF = [];
    let items156 = LoopParseFunc(line);
    for (let A_Index156 = 0; A_Index156 < items156.length + 0; A_Index156++) {
        const A_LoopField156 = items156[A_Index156 - 0];
        HTVM_Append(slidingWinFixCommentsRmFFFF, A_LoopField156);
    }
    for (let A_Index157 = 0; A_Index157 < StrLen(keyWordComment + keyWordComment) + 2 + 0; A_Index157++) {
        HTVM_Append(slidingWinFixCommentsRmFFFF, " ");
    }
    return slidingWinFixCommentsRmFFFF;
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
function fixIfElseIfMultiLineStatementHELP(aloopfield) {
    var out = "";
    var count = 0;
    let items158 = LoopParseFunc(aloopfield);
    for (let A_Index158 = 0; A_Index158 < items158.length + 0; A_Index158++) {
        const A_LoopField158 = items158[A_Index158 - 0];
        if (A_LoopField158 == "(") {
            count++;
        }
        if (A_LoopField158 == ")") {
            count--;
        }
    }
    if (count == 0) {
        return "w";
    } else {
        return "";
    }
    return out;
}
function fixIfElseIfMultiLineStatement(someHTVMcode) {
    var doWeExitInsta = 1;
    let items159 = LoopParseFunc(someHTVMcode, "\n", "\r");
    for (let A_Index159 = 0; A_Index159 < items159.length + 0; A_Index159++) {
        const A_LoopField159 = items159[A_Index159 - 0];
        if (SubStr(StrLower(Trim(A_LoopField159)), 1, StrLen(keyWordIF)) == keyWordIF) {
            doWeExitInsta = 0;
        }
        else if (SubStr(StrLower(Trim(A_LoopField159)), 1, StrLen(keyWordWhileLoop)) == keyWordWhileLoop) {
            doWeExitInsta = 0;
        }
        else if (SubStr(StrLower(Trim(A_LoopField159)), 1, StrLen(keyWordElseIf)) == keyWordElseIf) {
            doWeExitInsta = 0;
        }
    }
    if (doWeExitInsta == 1) {
        return someHTVMcode;
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var out = "";
    var out2 = "";
    // this will make sure we exit once we dont have if else if while
    var doWeJustExit = 0;
    // this will make sure we exit once we dont fix the if else if while
    var doWeExit = false;
    var doWeExitHELP = 0;
    out = someHTVMcode;
    // 10000 just in case the loop somehow becomes infinite
    for (let A_Index160 = 0; A_Index160 < 10000 + 0; A_Index160++) {
        out2 = out;
        out = "";
        doWeExit = false;
        let items161 = LoopParseFunc(out2, "\n", "\r");
        for (let A_Index161 = 0; A_Index161 < items161.length + 0; A_Index161++) {
            const A_LoopField161 = items161[A_Index161 - 0];
            if (SubStr(StrLower(Trim(A_LoopField161)), 1, StrLen(keyWordIF)) == keyWordIF) {
                doWeJustExit = 1;
                if (fixIfElseIfMultiLineStatementHELP(A_LoopField161) == "") {
                    out += Trim(A_LoopField161) + " ";
                    doWeExit = false;
                    doWeExitHELP--;
                } else {
                    doWeExit = true;
                    out += Trim(A_LoopField161) + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField161)), 1, StrLen(keyWordWhileLoop)) == keyWordWhileLoop) {
                doWeJustExit = 1;
                if (fixIfElseIfMultiLineStatementHELP(A_LoopField161) == "") {
                    out += Trim(A_LoopField161) + " ";
                    doWeExit = false;
                    doWeExitHELP--;
                } else {
                    doWeExit = true;
                    out += Trim(A_LoopField161) + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField161)), 1, StrLen(keyWordElseIf)) == keyWordElseIf) {
                doWeJustExit = 1;
                if (fixIfElseIfMultiLineStatementHELP(A_LoopField161) == "") {
                    out += Trim(A_LoopField161) + " ";
                    doWeExit = false;
                    doWeExitHELP--;
                } else {
                    doWeExit = true;
                    out += Trim(A_LoopField161) + Chr(10);
                }
            } else {
                out += Trim(A_LoopField161) + Chr(10);
            }
        }
        out = StringTrimRight(out, 1);
        //print(A_Index)
        if (doWeJustExit == 0) {
            break;
        }
        if (doWeExit == true) {
            doWeExitHELP++;
            if (doWeExitHELP > 2) {
                break;
            }
        }
    }
    return out;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function doseHaveInclude(TheCodeThatMightHaveInclude) {
    let items162 = LoopParseFunc(TheCodeThatMightHaveInclude, "\n", "\r");
    for (let A_Index162 = 0; A_Index162 < items162.length + 0; A_Index162++) {
        const A_LoopField162 = items162[A_Index162 - 0];
        if (SubStr(StrLower(Trim(A_LoopField162)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ")) {
            return true;
        }
    }
    return false;
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
function compiler(htCode, allInstructionFile, mode, langToConvertToParam = "") {
    var instructions = allInstructionFile;
    let items163 = LoopParseFunc(allInstructionFile, "\n", "\r");
    for (let A_Index163 = 0; A_Index163 < items163.length + 0; A_Index163++) {
        const A_LoopField163 = items163[A_Index163 - 0];
        if (A_Index163 == 0) {
            langToConvertTo = Trim(A_LoopField163);
        }
        if (A_Index163 == 1) {
            langFileExtension = Trim(A_LoopField163);
        }
        if (A_Index163 == 2) {
            commands = Trim(A_LoopField163);
        }
        if (A_Index163 == 3) {
            keyWordAlliance = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 4) {
            keyWordCrew = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 5) {
            keyWordProc = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 6) {
            keyWordStruct = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 7) {
            keyWordProp = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 8) {
            keyWordThis = Trim(A_LoopField163);
        }
        if (A_Index163 == 9) {
            keyWordInclude = Trim(A_LoopField163);
        }
        if (A_Index163 == 10) {
            keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField163);
        }
        if (A_Index163 == 11) {
            keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField163);
        }
        if (A_Index163 == 12) {
            keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField163);
        }
        if (A_Index163 == 13) {
            keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField163);
        }
        if (A_Index163 == 14) {
            keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField163);
        }
        if (A_Index163 == 15) {
            keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField163);
        }
        if (A_Index163 == 16) {
            keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField163);
        }
        if (A_Index163 == 17) {
            keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField163);
        }
        if (A_Index163 == 18) {
            keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField163);
        }
        if (A_Index163 == 19) {
            keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField163);
        }
        if (A_Index163 == 20) {
            keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField163);
        }
        if (A_Index163 == 21) {
            keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField163);
        }
        if (A_Index163 == 22) {
            keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField163);
        }
        if (A_Index163 == 23) {
            keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField163);
        }
        if (A_Index163 == 24) {
            keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField163);
        }
        if (A_Index163 == 25) {
            keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField163);
        }
        if (A_Index163 == 26) {
            keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField163);
        }
        if (A_Index163 == 27) {
            keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField163);
        }
        if (A_Index163 == 28) {
            keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField163);
        }
        if (A_Index163 == 29) {
            keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField163);
        }
        if (A_Index163 == 30) {
            keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField163);
        }
        if (A_Index163 == 31) {
            keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField163);
        }
        if (A_Index163 == 32) {
            keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField163);
        }
        if (A_Index163 == 33) {
            keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField163);
        }
        if (A_Index163 == 34) {
            keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField163);
        }
        if (A_Index163 == 35) {
            keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField163);
        }
        if (A_Index163 == 36) {
            keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField163);
        }
        if (A_Index163 == 37) {
            keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField163);
        }
        if (A_Index163 == 38) {
            keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField163);
        }
        if (A_Index163 == 39) {
            keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField163);
        }
        if (A_Index163 == 40) {
            keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField163);
        }
        if (A_Index163 == 41) {
            keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField163);
        }
        if (A_Index163 == 42) {
            keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField163);
        }
        if (A_Index163 == 43) {
            keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField163);
        }
        if (A_Index163 == 44) {
            keyWordCodeInHTVMstart = Trim(A_LoopField163);
        }
        if (A_Index163 == 45) {
            keyWordCodeInHTVMend = Trim(A_LoopField163);
        }
        if (A_Index163 == 46) {
            keyWordCurlyBraceOpen = Trim(A_LoopField163);
        }
        if (A_Index163 == 47) {
            keyWordCurlyBraceClose = Trim(A_LoopField163);
        }
        if (A_Index163 == 48) {
            keyWordNull = Trim(A_LoopField163);
        }
        if (A_Index163 == 49) {
            keyWordTrue = Trim(A_LoopField163);
        }
        if (A_Index163 == 50) {
            keyWordFalse = Trim(A_LoopField163);
        }
        if (A_Index163 == 51) {
            keyWordVoid = Trim(A_LoopField163);
        }
        if (A_Index163 == 52) {
            keyWordDouble = Trim(A_LoopField163);
        }
        if (A_Index163 == 53) {
            keyWordChar = Trim(A_LoopField163);
        }
        if (A_Index163 == 54) {
            keyWordUint8 = Trim(A_LoopField163);
        }
        if (A_Index163 == 55) {
            keyWordUint16 = Trim(A_LoopField163);
        }
        if (A_Index163 == 56) {
            keyWordUint32 = Trim(A_LoopField163);
        }
        if (A_Index163 == 57) {
            keyWordUint64 = Trim(A_LoopField163);
        }
        if (A_Index163 == 58) {
            keyWordINT = Trim(A_LoopField163);
        }
        if (A_Index163 == 59) {
            keyWordSTR = Trim(A_LoopField163);
        }
        if (A_Index163 == 60) {
            keyWordBOOL = Trim(A_LoopField163);
        }
        if (A_Index163 == 61) {
            keyWordFLOAT = Trim(A_LoopField163);
        }
        if (A_Index163 == 62) {
            keyWordINT8 = Trim(A_LoopField163);
        }
        if (A_Index163 == 63) {
            keyWordINT16 = Trim(A_LoopField163);
        }
        if (A_Index163 == 64) {
            keyWordINT32 = Trim(A_LoopField163);
        }
        if (A_Index163 == 65) {
            keyWordINT64 = Trim(A_LoopField163);
        }
        if (A_Index163 == 66) {
            keyWordIF = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 67) {
            keyWordElseIf = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 68) {
            keyWordElse = Trim(A_LoopField163);
        }
        if (A_Index163 == 69) {
            keyWordWhileLoop = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 70) {
            keyWordLoopInfinite = Trim(A_LoopField163);
        }
        if (A_Index163 == 71) {
            keyWordLoop = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 72) {
            keyWordLoopParse = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 73) {
            keyWordContinue = Trim(A_LoopField163);
        }
        if (A_Index163 == 74) {
            keyWordBreak = Trim(A_LoopField163);
        }
        if (A_Index163 == 75) {
            keyWordFunc = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 76) {
            keyWordAwait = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 77) {
            keyWordAsync = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 78) {
            keyWordThrow = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 79) {
            keyWordErrorMsg = Trim(A_LoopField163);
        }
        if (A_Index163 == 80) {
            keyWordTry = Trim(A_LoopField163);
        }
        if (A_Index163 == 81) {
            keyWordCatch = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 82) {
            keyWordFinally = Trim(A_LoopField163);
        }
        if (A_Index163 == 83) {
            keyWordReturnStatement = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 84) {
            keyWordArrayAppend = Trim(A_LoopField163);
        }
        if (A_Index163 == 85) {
            keyWordArrayPop = Trim(A_LoopField163);
        }
        if (A_Index163 == 86) {
            keyWordArraySize = Trim(A_LoopField163);
        }
        if (A_Index163 == 87) {
            keyWordArrayInsert = Trim(A_LoopField163);
        }
        if (A_Index163 == 88) {
            keyWordArrayRemove = Trim(A_LoopField163);
        }
        if (A_Index163 == 89) {
            keyWordArrayIndexOf = Trim(A_LoopField163);
        }
        if (A_Index163 == 90) {
            keyWordArrayDefinition = Trim(A_LoopField163);
        }
        if (A_Index163 == 91) {
            keyWordArrayOfIntegersDefinition = Trim(A_LoopField163);
        }
        if (A_Index163 == 92) {
            keyWordArrayOfStringsDefinition = Trim(A_LoopField163);
        }
        if (A_Index163 == 93) {
            keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField163);
        }
        if (A_Index163 == 94) {
            keyWordArrayOfBooleansDefinition = Trim(A_LoopField163);
        }
        if (A_Index163 == 95) {
            keyWordVar = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 96) {
            keyWordLet = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 97) {
            keyWordConst = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 98) {
            keyWordEnd = Trim(A_LoopField163);
        }
        if (A_Index163 == 99) {
            keyWordGlobal = Trim(A_LoopField163) + " ";
        }
        if (A_Index163 == 100) {
            keyWordComment = Trim(A_LoopField163);
        }
        if (A_Index163 == 101) {
            keyWordCommentOpenMultiLine = Trim(A_LoopField163);
        }
        if (A_Index163 == 102) {
            keyWordCommentCloseMultiLine = Trim(A_LoopField163);
        }
        if (A_Index163 == 103) {
            keyWordEscpaeChar = Trim(A_LoopField163);
        }
        if (A_Index163 == 104) {
            keyWordMainLabel = Trim(A_LoopField163);
        }
        if (A_Index163 == 105) {
            keyWordConcat = Trim(A_LoopField163);
        }
        if (A_Index163 == 106) {
            keyWordAdd = Trim(A_LoopField163);
        }
        if (A_Index163 == 107) {
            keyWordSub = Trim(A_LoopField163);
        }
        if (A_Index163 == 108) {
            keyWordMul = Trim(A_LoopField163);
        }
        if (A_Index163 == 109) {
            keyWordDiv = Trim(A_LoopField163);
        }
        if (A_Index163 == 110) {
            keyWordMod = Trim(A_LoopField163);
        }
        if (A_Index163 == 111) {
            keyWordExp = Trim(A_LoopField163);
        }
        if (A_Index163 == 112) {
            keyWordEqual = Trim(A_LoopField163);
        }
        if (A_Index163 == 113) {
            keyWordStrictEqual = Trim(A_LoopField163);
        }
        if (A_Index163 == 114) {
            keyWordNotEqual = Trim(A_LoopField163);
        }
        if (A_Index163 == 115) {
            keyWordGreater = Trim(A_LoopField163);
        }
        if (A_Index163 == 116) {
            keyWordLess = Trim(A_LoopField163);
        }
        if (A_Index163 == 117) {
            keyWordGreaterEqual = Trim(A_LoopField163);
        }
        if (A_Index163 == 118) {
            keyWordLessEqual = Trim(A_LoopField163);
        }
        if (A_Index163 == 119) {
            keyWordAnd = Trim(A_LoopField163);
        }
        if (A_Index163 == 120) {
            keyWordOr = Trim(A_LoopField163);
        }
        if (A_Index163 == 121) {
            keyWordNot = Trim(A_LoopField163);
        }
        if (A_Index163 == 122) {
            keyWordBitAnd = Trim(A_LoopField163);
        }
        if (A_Index163 == 123) {
            keyWordBitOr = Trim(A_LoopField163);
        }
        if (A_Index163 == 124) {
            keyWordBitXor = Trim(A_LoopField163);
        }
        if (A_Index163 == 125) {
            keyWordBitNot = Trim(A_LoopField163);
        }
        if (A_Index163 == 126) {
            keyWordShiftLeft = Trim(A_LoopField163);
        }
        if (A_Index163 == 127) {
            keyWordShiftRight = Trim(A_LoopField163);
        }
        if (A_Index163 == 128) {
            keyWordShiftUnsignedRight = Trim(A_LoopField163);
        }
        if (A_Index163 == 129) {
            keyWordAssign = Trim(A_LoopField163);
        }
        if (A_Index163 == 130) {
            keyWordAssignAdd = Trim(A_LoopField163);
        }
        if (A_Index163 == 131) {
            keyWordAssignConcat = Trim(A_LoopField163);
        }
        if (A_Index163 == 132) {
            keyWordAssignSub = Trim(A_LoopField163);
        }
        if (A_Index163 == 133) {
            keyWordAssignMul = Trim(A_LoopField163);
        }
        if (A_Index163 == 134) {
            keyWordAssignDiv = Trim(A_LoopField163);
        }
        if (A_Index163 == 135) {
            keyWordAssignMod = Trim(A_LoopField163);
        }
        if (A_Index163 == 136) {
            keyWordAssignShiftLeft = Trim(A_LoopField163);
        }
        if (A_Index163 == 137) {
            keyWordAssignShiftRight = Trim(A_LoopField163);
        }
        if (A_Index163 == 138) {
            keyWordLogicalAssignShiftRight = Trim(A_LoopField163);
        }
        if (A_Index163 == 139) {
            keyWordAssignBitAnd = Trim(A_LoopField163);
        }
        if (A_Index163 == 140) {
            keyWordAssignBitOr = Trim(A_LoopField163);
        }
        if (A_Index163 == 141) {
            keyWordAssignBitXor = Trim(A_LoopField163);
        }
        if (A_Index163 == 142) {
            keyWordTernary1 = Trim(A_LoopField163);
        }
        if (A_Index163 == 143) {
            keyWordTernary2 = Trim(A_LoopField163);
        }
        if (A_Index163 == 144) {
            keyWordInc = Trim(A_LoopField163);
        }
        if (A_Index163 == 145) {
            keyWordDec = Trim(A_LoopField163);
        }
        if (A_Index163 == 146) {
            AHKlikeLoopsIndexedAt = Trim(A_LoopField163);
        }
        if (A_Index163 == 147) {
            keyWordAIndex = Trim(A_LoopField163);
        }
        if (A_Index163 == 148) {
            keyWordALoopField = Trim(A_LoopField163);
        }
        if (A_Index163 == 149) {
            useCurlyBraces = Trim(A_LoopField163);
        }
        if (A_Index163 == 150) {
            useEnd = Trim(A_LoopField163);
        }
        if (A_Index163 == 151) {
            useSemicolon = Trim(A_LoopField163);
        }
        if (A_Index163 == 152) {
            useParentheses = Trim(A_LoopField163);
        }
        if (A_Index163 == 153) {
            usePrefixTypeForTypeDefinition = Trim(A_LoopField163);
        }
        if (A_Index163 == 154) {
            usePostfixTypeForTypeDefinition = Trim(A_LoopField163);
        }
        if (A_Index163 == 155) {
            usePythonicColonSyntax = Trim(A_LoopField163);
        }
        if (A_Index163 == 156) {
            useCurlyBracesSyntaxForArrayDef = Trim(A_LoopField163);
        }
        if (A_Index163 == 157) {
            useInJavaScriptAlwaysUseVar = Trim(A_LoopField163);
        }
        if (A_Index163 == 158) {
            useJavaScriptInAfullHTMLfile = Trim(A_LoopField163);
        }
        if (A_Index163 == 159) {
            useJavaScriptAmainFuncDef = Trim(A_LoopField163);
        }
        if (A_Index163 == 160) {
            useJavaScriptAllFuncsAreAsync = Trim(A_LoopField163);
        }
        if (A_Index163 == 161) {
            useJavaScriptAlwaysTripleEqual = Trim(A_LoopField163);
        }
    }
    if (HTVM_Size(argHTVMinstrMORE) > 0) {
        var allInstructionFile_2 = "";
        if (HTVM_getLang_HTVM() == "js") {
            allInstructionFile_2 = Trim(argHTVMinstrMORE[0]);
        } else {
            allInstructionFile_2 = Trim(FileRead(Trim(argHTVMinstrMORE[0])));
        }
        let items164 = LoopParseFunc(allInstructionFile_2, "\n", "\r");
        for (let A_Index164 = 0; A_Index164 < items164.length + 0; A_Index164++) {
            const A_LoopField164 = items164[A_Index164 - 0];
            if (A_Index164 == 0) {
                langToConvertTo_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 1) {
                langFileExtension_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 2) {
                commands_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 3) {
                keyWordAlliance_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 4) {
                keyWordCrew_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 5) {
                keyWordProc_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 6) {
                keyWordStruct_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 7) {
                keyWordProp_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 8) {
                keyWordThis_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 9) {
                keyWordInclude_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 10) {
                keyWordCodeInTheTranspiledLangStart_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 11) {
                keyWordCodeInTheTranspiledLangEnd_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 12) {
                keyWordCodeInTheTranspiledLangStartCPP_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 13) {
                keyWordCodeInTheTranspiledLangEndCPP_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 14) {
                keyWordCodeInTheTranspiledLangStartPY_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 15) {
                keyWordCodeInTheTranspiledLangEndPY_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 16) {
                keyWordCodeInTheTranspiledLangStartJS_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 17) {
                keyWordCodeInTheTranspiledLangEndJS_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 18) {
                keyWordCodeInTheTranspiledLangStartGO_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 19) {
                keyWordCodeInTheTranspiledLangEndGO_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 20) {
                keyWordCodeInTheTranspiledLangStartLUA_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 21) {
                keyWordCodeInTheTranspiledLangEndLUA_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 22) {
                keyWordCodeInTheTranspiledLangStartCS_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 23) {
                keyWordCodeInTheTranspiledLangEndCS_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 24) {
                keyWordCodeInTheTranspiledLangStartJAVA_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 25) {
                keyWordCodeInTheTranspiledLangEndJAVA_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 26) {
                keyWordCodeInTheTranspiledLangStartKT_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 27) {
                keyWordCodeInTheTranspiledLangEndKT_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 28) {
                keyWordCodeInTheTranspiledLangStartRB_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 29) {
                keyWordCodeInTheTranspiledLangEndRB_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 30) {
                keyWordCodeInTheTranspiledLangStartNIM_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 31) {
                keyWordCodeInTheTranspiledLangEndNIM_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 32) {
                keyWordCodeInTheTranspiledLangStartAHK_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 33) {
                keyWordCodeInTheTranspiledLangEndAHK_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 34) {
                keyWordCodeInTheTranspiledLangStartSWIFT_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 35) {
                keyWordCodeInTheTranspiledLangEndSWIFT_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 36) {
                keyWordCodeInTheTranspiledLangStartDART_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 37) {
                keyWordCodeInTheTranspiledLangEndDART_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 38) {
                keyWordCodeInTheTranspiledLangStartTS_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 39) {
                keyWordCodeInTheTranspiledLangEndTS_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 40) {
                keyWordCodeInTheTranspiledLangStartGROOVY_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 41) {
                keyWordCodeInTheTranspiledLangEndGROOVY_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 42) {
                keyWordCodeInTheTranspiledLangStartHTVM_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 43) {
                keyWordCodeInTheTranspiledLangEndHTVM_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 44) {
                keyWordCodeInHTVMstart_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 45) {
                keyWordCodeInHTVMend_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 46) {
                keyWordCurlyBraceOpen_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 47) {
                keyWordCurlyBraceClose_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 48) {
                keyWordNull_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 49) {
                keyWordTrue_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 50) {
                keyWordFalse_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 51) {
                keyWordVoid_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 52) {
                keyWordDouble_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 53) {
                keyWordChar_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 54) {
                keyWordUint8_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 55) {
                keyWordUint16_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 56) {
                keyWordUint32_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 57) {
                keyWordUint64_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 58) {
                keyWordINT_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 59) {
                keyWordSTR_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 60) {
                keyWordBOOL_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 61) {
                keyWordFLOAT_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 62) {
                keyWordINT8_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 63) {
                keyWordINT16_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 64) {
                keyWordINT32_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 65) {
                keyWordINT64_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 66) {
                keyWordIF_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 67) {
                keyWordElseIf_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 68) {
                keyWordElse_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 69) {
                keyWordWhileLoop_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 70) {
                keyWordLoopInfinite_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 71) {
                keyWordLoop_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 72) {
                keyWordLoopParse_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 73) {
                keyWordContinue_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 74) {
                keyWordBreak_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 75) {
                keyWordFunc_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 76) {
                keyWordAwait_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 77) {
                keyWordAsync_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 78) {
                keyWordThrow_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 79) {
                keyWordErrorMsg_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 80) {
                keyWordTry_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 81) {
                keyWordCatch_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 82) {
                keyWordFinally_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 83) {
                keyWordReturnStatement_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 84) {
                keyWordArrayAppend_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 85) {
                keyWordArrayPop_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 86) {
                keyWordArraySize_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 87) {
                keyWordArrayInsert_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 88) {
                keyWordArrayRemove_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 89) {
                keyWordArrayIndexOf_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 90) {
                keyWordArrayDefinition_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 91) {
                keyWordArrayOfIntegersDefinition_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 92) {
                keyWordArrayOfStringsDefinition_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 93) {
                keyWordArrayOfFloatingPointNumbersDefinition_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 94) {
                keyWordArrayOfBooleansDefinition_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 95) {
                keyWordVar_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 96) {
                keyWordLet_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 97) {
                keyWordConst_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 98) {
                keyWordEnd_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 99) {
                keyWordGlobal_2 = Trim(A_LoopField164) + " ";
            }
            if (A_Index164 == 100) {
                keyWordComment_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 101) {
                keyWordCommentOpenMultiLine_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 102) {
                keyWordCommentCloseMultiLine_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 103) {
                keyWordEscpaeChar_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 104) {
                keyWordMainLabel_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 105) {
                keyWordConcat_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 106) {
                keyWordAdd_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 107) {
                keyWordSub_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 108) {
                keyWordMul_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 109) {
                keyWordDiv_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 110) {
                keyWordMod_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 111) {
                keyWordExp_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 112) {
                keyWordEqual_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 113) {
                keyWordStrictEqual_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 114) {
                keyWordNotEqual_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 115) {
                keyWordGreater_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 116) {
                keyWordLess_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 117) {
                keyWordGreaterEqual_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 118) {
                keyWordLessEqual_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 119) {
                keyWordAnd_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 120) {
                keyWordOr_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 121) {
                keyWordNot_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 122) {
                keyWordBitAnd_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 123) {
                keyWordBitOr_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 124) {
                keyWordBitXor_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 125) {
                keyWordBitNot_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 126) {
                keyWordShiftLeft_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 127) {
                keyWordShiftRight_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 128) {
                keyWordShiftUnsignedRight_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 129) {
                keyWordAssign_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 130) {
                keyWordAssignAdd_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 131) {
                keyWordAssignConcat_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 132) {
                keyWordAssignSub_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 133) {
                keyWordAssignMul_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 134) {
                keyWordAssignDiv_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 135) {
                keyWordAssignMod_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 136) {
                keyWordAssignShiftLeft_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 137) {
                keyWordAssignShiftRight_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 138) {
                keyWordLogicalAssignShiftRight_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 139) {
                keyWordAssignBitAnd_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 140) {
                keyWordAssignBitOr_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 141) {
                keyWordAssignBitXor_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 142) {
                keyWordTernary1_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 143) {
                keyWordTernary2_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 144) {
                keyWordInc_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 145) {
                keyWordDec_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 146) {
                AHKlikeLoopsIndexedAt_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 147) {
                keyWordAIndex_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 148) {
                keyWordALoopField_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 149) {
                useCurlyBraces_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 150) {
                useEnd_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 151) {
                useSemicolon_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 152) {
                useParentheses_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 153) {
                usePrefixTypeForTypeDefinition_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 154) {
                usePostfixTypeForTypeDefinition_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 155) {
                usePythonicColonSyntax_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 156) {
                useCurlyBracesSyntaxForArrayDef_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 157) {
                useInJavaScriptAlwaysUseVar_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 158) {
                useJavaScriptInAfullHTMLfile_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 159) {
                useJavaScriptAmainFuncDef_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 160) {
                useJavaScriptAllFuncsAreAsync_2 = Trim(A_LoopField164);
            }
            if (A_Index164 == 161) {
                useJavaScriptAlwaysTripleEqual_2 = Trim(A_LoopField164);
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
    if (useEnd == "on") {
        keyWordCurlyBraceOpen = "{";
        keyWordCurlyBraceClose = "}";
    }
    if (useEnd_2 == "on") {
        keyWordCurlyBraceOpen_2 = "{";
        keyWordCurlyBraceClose_2 = "}";
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
    availableFuncsInHTVMInHTVM = "";
    let items165 = LoopParseFunc(allInstructionFile, "\n", "\r");
    for (let A_Index165 = 0; A_Index165 < items165.length + 0; A_Index165++) {
        const A_LoopField165 = items165[A_Index165 - 0];
        if (RegExMatch(Trim(A_LoopField165), "^name: [A-Za-z0-9_]+")) {
            availableFuncsInHTVMInHTVM += Trim(StrSplit(Trim(A_LoopField165), "name: ", 2)) + Chr(10);
        }
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
    var strOspHold = "";
    if (isNotHTVMfile == 0) {
        code = handleMultiLineStrings(code);
    }
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
    let items166 = LoopParseFunc(code, "\n", "\r");
    for (let A_Index166 = 0; A_Index166 < items166.length + 0; A_Index166++) {
        const A_LoopField166 = items166[A_Index166 - 0];
        if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEnd)) {
            COUNT_programmingBlock_InTheTranspiledLang++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(COUNT_programmingBlock_InTheTranspiledLang) + "AA\n";
            HTVM_Append(programmingBlock_InTheTranspiledLang, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndCPP)) {
            COUNT_programmingBlock_CPP++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(COUNT_programmingBlock_CPP) + "AA\n";
            HTVM_Append(programmingBlock_CPP, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndPY)) {
            COUNT_programmingBlock_PY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_PY-programmingBlock_PY-AA" + STR(COUNT_programmingBlock_PY) + "AA\n";
            HTVM_Append(programmingBlock_PY, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndJS)) {
            COUNT_programmingBlock_JS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JS-programmingBlock_JS-AA" + STR(COUNT_programmingBlock_JS) + "AA\n";
            HTVM_Append(programmingBlock_JS, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndGO)) {
            COUNT_programmingBlock_GO++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GO-programmingBlock_GO-AA" + STR(COUNT_programmingBlock_GO) + "AA\n";
            HTVM_Append(programmingBlock_GO, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndLUA)) {
            COUNT_programmingBlock_LUA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(COUNT_programmingBlock_LUA) + "AA\n";
            HTVM_Append(programmingBlock_LUA, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndCS)) {
            COUNT_programmingBlock_CS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CS-programmingBlock_CS-AA" + STR(COUNT_programmingBlock_CS) + "AA\n";
            HTVM_Append(programmingBlock_CS, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndJAVA)) {
            COUNT_programmingBlock_JAVA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(COUNT_programmingBlock_JAVA) + "AA\n";
            HTVM_Append(programmingBlock_JAVA, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndKT)) {
            COUNT_programmingBlock_KT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_KT-programmingBlock_KT-AA" + STR(COUNT_programmingBlock_KT) + "AA\n";
            HTVM_Append(programmingBlock_KT, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndRB)) {
            COUNT_programmingBlock_RB++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_RB-programmingBlock_RB-AA" + STR(COUNT_programmingBlock_RB) + "AA\n";
            HTVM_Append(programmingBlock_RB, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndNIM)) {
            COUNT_programmingBlock_NIM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(COUNT_programmingBlock_NIM) + "AA\n";
            HTVM_Append(programmingBlock_NIM, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndAHK)) {
            COUNT_programmingBlock_AHK++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(COUNT_programmingBlock_AHK) + "AA\n";
            HTVM_Append(programmingBlock_AHK, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndSWIFT)) {
            COUNT_programmingBlock_SWIFT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(COUNT_programmingBlock_SWIFT) + "AA\n";
            HTVM_Append(programmingBlock_SWIFT, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndDART)) {
            COUNT_programmingBlock_DART++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_DART-programmingBlock_DART-AA" + STR(COUNT_programmingBlock_DART) + "AA\n";
            HTVM_Append(programmingBlock_DART, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndTS)) {
            COUNT_programmingBlock_TS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_TS-programmingBlock_TS-AA" + STR(COUNT_programmingBlock_TS) + "AA\n";
            HTVM_Append(programmingBlock_TS, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndGROOVY)) {
            COUNT_programmingBlock_GROOVY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(COUNT_programmingBlock_GROOVY) + "AA\n";
            HTVM_Append(programmingBlock_GROOVY, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangEndHTVM)) {
            COUNT_programmingBlock_HTVM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(COUNT_programmingBlock_HTVM) + "AA\n";
            HTVM_Append(programmingBlock_HTVM, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInHTVMend)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            COUNT_programmingBlock_HTVMsyntax++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(COUNT_programmingBlock_HTVMsyntax) + "AA\n";
            HTVM_Append(programmingBlock_HTVMsyntax, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        }
        else if (inProgarmmingBlock == 1) {
            holdTempDataProgrammingBlockThenPutInArr += A_LoopField166 + Chr(10);
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStart)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartCPP)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartPY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartJS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartGO)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartLUA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartCS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartJAVA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartKT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartRB)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartNIM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartAHK)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartSWIFT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartDART)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartTS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartGROOVY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInTheTranspiledLangStartHTVM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField166)) == StrLower(keyWordCodeInHTVMstart)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        } else {
            programmingBlocksTemp += A_LoopField166 + Chr(10);
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
    // keyWordInclude
    // keyWordInclude
    // keyWordInclude
    // --- HTVM Include Directive Processor ---
    //
    // This script processes 'include' directives by replacing them with the content of the specified files.
    // It handles nested includes and prevents the same file from being included multiple times.
    // All variables are declared at the top for scope safety and clarity.
    // The main logic is wrapped in an IF block to avoid running unnecessarily.
    // =========================================================================================
    // --- Variable Declarations ---
    // All variables used in this script are declared upfront.
    let includedFilePaths = [];
    var includesWereFoundInPass = false;
    var reconstructedCode = "";
    var currentLine = "";
    var filePathToInclude = "";
    var isAlreadyIncluded = false;
    var fileContent = "";
    if (isNotHTVMfile == 0) {
        if (langToConvertTo != langFileExtension_2) {
            // --- Main Processing Logic ---
            // Optimization: Only run the complex processing logic IF the 'include' keyword exists in the code.
            // This avoids a 'return' and simply skips the block if it's not needed.
            if (doseHaveInclude(code)) {
                // Loop up to 10 times to resolve nested includes. Each pass processes one level of includes.
                for (let A_Index167 = 0; A_Index167 < 10 + 0; A_Index167++) {
                    // Reset the flag and the temporary code string for this pass.
                    includesWereFoundInPass = false;
                    reconstructedCode = "";
                    // Iterate through each line of the current code.
                    let items168 = LoopParseFunc(code, "\n", "\r");
                    for (let A_Index168 = 0; A_Index168 < items168.length + 0; A_Index168++) {
                        const A_LoopField168 = items168[A_Index168 - 0];
                        currentLine = A_LoopField168;
                        // Check if the current line is an 'include' directive.
                        if (SubStr(StrLower(Trim(currentLine)), 1, StrLen(keyWordInclude + " ")) == StrLower(keyWordInclude + " ")) {
                            includesWereFoundInPass = true;
                            filePathToInclude = StrReplace(StringTrimLeft(Trim(currentLine), StrLen(keyWordInclude + " ")), Chr(34), "");
                            // Reset flag for the inner loop.
                            isAlreadyIncluded = false;
                            // NOTE: Both this loop's A_Index and the array access are 0-based, which is correct.
                            for (let A_Index169 = 0; A_Index169 < HTVM_Size(includedFilePaths) + 0; A_Index169++) {
                                if (filePathToInclude == includedFilePaths[A_Index169]) {
                                    isAlreadyIncluded = true;
                                    break;
                                }
                            }
                            if (isAlreadyIncluded == false) {
                                fileContent = FileRead(filePathToInclude);
                                // The 'include' line is replaced by the file's content in the reconstructed code.
                                reconstructedCode = reconstructedCode + fileContent + Chr(10);
                                HTVM_Append(includedFilePaths, filePathToInclude);
                            }
                        } else {
                            // If it's not an include directive, just copy the line as is.
                            reconstructedCode = reconstructedCode + currentLine + Chr(10);
                        }
                    }
                    // --- Cleanup and Preparation for Next Pass ---
                    // Replace the old code with the newly reconstructed code. This "clears up" the processed includes.
                    code = reconstructedCode;
                    // If no includes were found in this entire pass, all directives are resolved. Exit the loop.
                    if (includesWereFoundInPass == false) {
                        break;
                    }
                }
            }
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        programmingBlocksTemp = "";
        inProgarmmingBlock = 0;
        holdTempDataProgrammingBlockThenPutInArr = "";
        let items170 = LoopParseFunc(code, "\n", "\r");
        for (let A_Index170 = 0; A_Index170 < items170.length + 0; A_Index170++) {
            const A_LoopField170 = items170[A_Index170 - 0];
            if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEnd)) {
                COUNT_programmingBlock_InTheTranspiledLang++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(COUNT_programmingBlock_InTheTranspiledLang) + "AA\n";
                HTVM_Append(programmingBlock_InTheTranspiledLang, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndCPP)) {
                COUNT_programmingBlock_CPP++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(COUNT_programmingBlock_CPP) + "AA\n";
                HTVM_Append(programmingBlock_CPP, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndPY)) {
                COUNT_programmingBlock_PY++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_PY-programmingBlock_PY-AA" + STR(COUNT_programmingBlock_PY) + "AA\n";
                HTVM_Append(programmingBlock_PY, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndJS)) {
                COUNT_programmingBlock_JS++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_JS-programmingBlock_JS-AA" + STR(COUNT_programmingBlock_JS) + "AA\n";
                HTVM_Append(programmingBlock_JS, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndGO)) {
                COUNT_programmingBlock_GO++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_GO-programmingBlock_GO-AA" + STR(COUNT_programmingBlock_GO) + "AA\n";
                HTVM_Append(programmingBlock_GO, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndLUA)) {
                COUNT_programmingBlock_LUA++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(COUNT_programmingBlock_LUA) + "AA\n";
                HTVM_Append(programmingBlock_LUA, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndCS)) {
                COUNT_programmingBlock_CS++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_CS-programmingBlock_CS-AA" + STR(COUNT_programmingBlock_CS) + "AA\n";
                HTVM_Append(programmingBlock_CS, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndJAVA)) {
                COUNT_programmingBlock_JAVA++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(COUNT_programmingBlock_JAVA) + "AA\n";
                HTVM_Append(programmingBlock_JAVA, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndKT)) {
                COUNT_programmingBlock_KT++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_KT-programmingBlock_KT-AA" + STR(COUNT_programmingBlock_KT) + "AA\n";
                HTVM_Append(programmingBlock_KT, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndRB)) {
                COUNT_programmingBlock_RB++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_RB-programmingBlock_RB-AA" + STR(COUNT_programmingBlock_RB) + "AA\n";
                HTVM_Append(programmingBlock_RB, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndNIM)) {
                COUNT_programmingBlock_NIM++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(COUNT_programmingBlock_NIM) + "AA\n";
                HTVM_Append(programmingBlock_NIM, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndAHK)) {
                COUNT_programmingBlock_AHK++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(COUNT_programmingBlock_AHK) + "AA\n";
                HTVM_Append(programmingBlock_AHK, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndSWIFT)) {
                COUNT_programmingBlock_SWIFT++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(COUNT_programmingBlock_SWIFT) + "AA\n";
                HTVM_Append(programmingBlock_SWIFT, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndDART)) {
                COUNT_programmingBlock_DART++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_DART-programmingBlock_DART-AA" + STR(COUNT_programmingBlock_DART) + "AA\n";
                HTVM_Append(programmingBlock_DART, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndTS)) {
                COUNT_programmingBlock_TS++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_TS-programmingBlock_TS-AA" + STR(COUNT_programmingBlock_TS) + "AA\n";
                HTVM_Append(programmingBlock_TS, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndGROOVY)) {
                COUNT_programmingBlock_GROOVY++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(COUNT_programmingBlock_GROOVY) + "AA\n";
                HTVM_Append(programmingBlock_GROOVY, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangEndHTVM)) {
                COUNT_programmingBlock_HTVM++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(COUNT_programmingBlock_HTVM) + "AA\n";
                HTVM_Append(programmingBlock_HTVM, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInHTVMend)) {
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                COUNT_programmingBlock_HTVMsyntax++;
                holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
                programmingBlocksTemp += "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(COUNT_programmingBlock_HTVMsyntax) + "AA\n";
                HTVM_Append(programmingBlock_HTVMsyntax, Chr(10) + holdTempDataProgrammingBlockThenPutInArr);
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 0;
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            }
            else if (inProgarmmingBlock == 1) {
                holdTempDataProgrammingBlockThenPutInArr += A_LoopField170 + Chr(10);
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStart)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartCPP)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartPY)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartJS)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartGO)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartLUA)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartCS)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartJAVA)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartKT)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartRB)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartNIM)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartAHK)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartSWIFT)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartDART)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartTS)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartGROOVY)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInTheTranspiledLangStartHTVM)) {
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
            }
            else if (Trim(StrLower(A_LoopField170)) == StrLower(keyWordCodeInHTVMstart)) {
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                holdTempDataProgrammingBlockThenPutInArr = "";
                inProgarmmingBlock = 1;
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            } else {
                programmingBlocksTemp += A_LoopField170 + Chr(10);
            }
        }
        code = StringTrimRight(programmingBlocksTemp, 1);
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ----------------
    }
    // keyWordInclude
    // keyWordInclude
    // keyWordInclude
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
    let slidingWinFixCommentsRm = [];
    var slidingWinFixCommentsRmHold = "";
    var slidingWinFixCommentsRmI = 0;
    var fixSomeOSPbigHTVMtoHTVM = "";
    let theIdNumOfThe34theVar = [];
    var ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = "";
    let getAllCharForTheFurtureSoIcanAddEscapeChar = [];
    var removeNexFixkeyWordEscpaeChar = 0;
    var fixSomeCurlyBraceForExratFlexability = "";
    var fixSomeCurlyBraceForExratFlexabilityTriHELP = "";
    var semiColonForOneLinerOut = "";
    var addNoCurlyFixWhenNextLineAfterConstructOut = "";
    let addNoCurlyFixWhenNextLineAfterConstructLookAhead = [];
    //;;;;;;;;;;;;;;;;;;;
    let commentsBugFix = [];
    var commentsBugFixHold = "";
    var commentsBugFixHold1 = "";
    var commentsBugFixHold2 = "";
    var commentsBugFixHelpInt = 0;
    var commentsBugFixOut = "";
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    if (isNotHTVMfile == 0) {
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        let items171 = LoopParseFunc(code, "\n", "\r");
        for (let A_Index171 = 0; A_Index171 < items171.length + 0; A_Index171++) {
            const A_LoopField171 = items171[A_Index171 - 0];
            if (SubStr(Trim(A_LoopField171), 1, StrLen(keyWordComment)) == keyWordComment) {
                commentsBugFixHold = StringTrimLeft(Trim(A_LoopField171), StrLen(keyWordComment));
                let items172 = LoopParseFunc(A_LoopField171);
                for (let A_Index172 = 0; A_Index172 < items172.length + 0; A_Index172++) {
                    const A_LoopField172 = items172[A_Index172 - 0];
                    if (InStr(A_LoopField172, " ") || InStr(A_LoopField172, Chr(9))) {
                        commentsBugFixHold1 = A_LoopField172;
                    } else {
                        break;
                    }
                }
                HTVM_Append(commentsBugFix, commentsBugFixHold);
                commentsBugFixHold2 = "HTVM--cnavisdofbuvsesdivdidufg79wregwewaeosd8ges7dfdftuawdiHTVMv2yerheyziberlasduci6syiq--AA" + STR(commentsBugFixHelpInt) + "AA";
                commentsBugFixHelpInt++;
                commentsBugFixOut += commentsBugFixHold1 + keyWordComment + commentsBugFixHold2 + Chr(10);
            } else {
                commentsBugFixOut += A_LoopField171 + Chr(10);
            }
        }
        code = StringTrimRight(commentsBugFixOut, 1);
        //print("============programmingBlock_CPP==================")
        //print("============programmingBlock_CPP==================")
        //print("============programmingBlock_CPP==================")
        //print("============programmingBlock_CPP==================")
        let items173 = LoopParseFunc(code);
        for (let A_Index173 = 0; A_Index173 < items173.length + 0; A_Index173++) {
            const A_LoopField173 = items173[A_Index173 - 0];
            HTVM_Append(theIdNumOfThe34theVar, "");
            HTVM_Append(theIdNumOfThe34theVar, "");
        }
        let items174 = LoopParseFunc(code);
        for (let A_Index174 = 0; A_Index174 < items174.length + 0; A_Index174++) {
            const A_LoopField174 = items174[A_Index174 - 0];
            theIdNumOfThe34theVar[A_Index174] = theIdNumOfThe34theVar[A_Index174] + Chr(34);
            HTVM_Append(getAllCharForTheFurtureSoIcanAddEscapeChar, A_LoopField174);
        }
        HTVM_Append(getAllCharForTheFurtureSoIcanAddEscapeChar, " ");
        ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuuhuuhtheidFor" + str21 + "--" + str21 + "asds" + str21 + "as--" + str21 + "theuhtuwaesphoutr" + Chr(34);
        let items175 = LoopParseFunc(code);
        for (let A_Index175 = 0; A_Index175 < items175.length + 0; A_Index175++) {
            const A_LoopField175 = items175[A_Index175 - 0];
            if (A_LoopField175 == keyWordEscpaeChar && getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index175 + 1] == Chr(34)) {
                fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1;
                OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes;
            } else {
                if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1) {
                    OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField175;
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
            let items176 = LoopParseFunc(code);
            for (let A_Index176 = 0; A_Index176 < items176.length + 0; A_Index176++) {
                const A_LoopField176 = items176[A_Index176 - 0];
                if (A_LoopField176 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField176 != Chr(34)) {
                        if (A_LoopField176 == keyWordEscpaeChar && langToConvertTo != langFileExtension_2) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField176;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField176 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField176;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        } else {
            let items177 = LoopParseFunc(code);
            for (let A_Index177 = 0; A_Index177 < items177.length + 0; A_Index177++) {
                const A_LoopField177 = items177[A_Index177 - 0];
                if (A_LoopField177 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField177 != Chr(34)) {
                        if (A_LoopField177 == keyWordEscpaeChar && keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index177 + 1] && langToConvertTo != langFileExtension_2) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar;
                            removeNexFixkeyWordEscpaeChar = 1;
                        }
                        else if (A_LoopField177 == keyWordEscpaeChar && langToConvertTo != langFileExtension_2) {
                            if (removeNexFixkeyWordEscpaeChar != 1) {
                                theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                            } else {
                                removeNexFixkeyWordEscpaeChar = 0;
                            }
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField177;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField177 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField177;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        }
        code = htCodeOUT754754;
        for (let A_Index178 = 0; A_Index178 < theIdNumOfThe34 + 0; A_Index178++) {
            theIdNumOfThe34theVar[A_Index178] = theIdNumOfThe34theVar[A_Index178] + Chr(34);
        }
        HTVM_Append(theIdNumOfThe34theVar, Chr(34));
        code = StrReplace(code, Chr(13), "");
        slidingWinFixCommentsRmI = 0;
        newStringOutCode = "";
        let items179 = LoopParseFunc(code, "\n", "\r");
        for (let A_Index179 = 0; A_Index179 < items179.length + 0; A_Index179++) {
            const A_LoopField179 = items179[A_Index179 - 0];
            if (InStr(A_LoopField179, " " + keyWordComment) != false && SubStr(Trim(A_LoopField179), 1, StrLen(keyWordComment)) != keyWordComment) {
                posForRemoveCommentsOnTheEndOfTheLine = 0;
                slidingWinFixCommentsRmI = 0;
                slidingWinFixCommentsRm = slidingWinFixCommentsRmFUNC(A_LoopField179);
                for (let A_Index180 = 0; A_Index180 < HTVM_Size(slidingWinFixCommentsRm) + 0; A_Index180++) {
                    slidingWinFixCommentsRmI = A_Index180;
                    slidingWinFixCommentsRmHold = "";
                    for (let A_Index181 = 0; A_Index181 < StrLen(" " + keyWordComment) + 0; A_Index181++) {
                        slidingWinFixCommentsRmHold += slidingWinFixCommentsRm[slidingWinFixCommentsRmI + A_Index181];
                    }
                    if (Trim(slidingWinFixCommentsRmHold) == keyWordComment) {
                        posForRemoveCommentsOnTheEndOfTheLine = A_Index180;
                        break;
                    }
                }
                if (posForRemoveCommentsOnTheEndOfTheLine > 0) {
                    // Keep only the part before the comment
                    newStringOutCode += SubStr(A_LoopField179, 1, posForRemoveCommentsOnTheEndOfTheLine) + Chr(10);
                } else {
                    // Keep the whole line as it is
                    newStringOutCode += A_LoopField179 + Chr(10);
                }
            } else {
                newStringOutCode += A_LoopField179 + Chr(10);
            }
        }
        // Trim the last character (line break) from the final string
        code = StringTrimRight(newStringOutCode, 1);
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        if (langToConvertTo != langFileExtension_2) {
            semiColonForOneLinerOut = "";
            let items182 = LoopParseFunc(code, "\n", "\r");
            for (let A_Index182 = 0; A_Index182 < items182.length + 0; A_Index182++) {
                const A_LoopField182 = items182[A_Index182 - 0];
                if (SubStr(Trim(A_LoopField182), 1, 1) != ";") {
                    semiColonForOneLinerOut += StrReplace(A_LoopField182, ";", Chr(10)) + Chr(10);
                } else {
                    semiColonForOneLinerOut += A_LoopField182 + Chr(10);
                }
            }
            code = StringTrimRight(semiColonForOneLinerOut, 1);
        }
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
            fixSomeCurlyBraceForExratFlexability = "";
            str1 = "";
            let items183 = LoopParseFunc(code, "\n", "\r");
            for (let A_Index183 = 0; A_Index183 < items183.length + 0; A_Index183++) {
                const A_LoopField183 = items183[A_Index183 - 0];
                str1 = "";
                if (InStr(A_LoopField183, keyWordCurlyBraceOpen) || InStr(A_LoopField183, keyWordCurlyBraceClose)) {
                    if (SubStr(Trim(A_LoopField183), 1, StrLen(Trim(keyWordComment))) == Trim(keyWordComment) && isLineAconstruct(Trim(A_LoopField183)) == false) {
                        fixSomeCurlyBraceForExratFlexability += A_LoopField183 + Chr(10);
                    } else {
                        if (InStr(A_LoopField183, Trim(keyWordArrayDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField183, Trim(keyWordArrayOfIntegersDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField183, Trim(keyWordArrayOfStringsDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField183, Trim(keyWordArrayOfFloatingPointNumbersDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField183, Trim(keyWordArrayOfBooleansDefinition) + " " + keyWordAssign + " ") && useCurlyBracesSyntaxForArrayDef == "on") {
                            fixSomeCurlyBraceForExratFlexability += A_LoopField183 + Chr(10);
                        } else {
                            str1 = StrReplace(A_LoopField183, keyWordCurlyBraceOpen, "{");
                            str1 = StrReplace(str1, keyWordCurlyBraceClose, "}");
                            str1 = StrReplace(str1, "{", Chr(10) + "{" + Chr(10));
                            str1 = StrReplace(str1, "}", Chr(10) + "}" + Chr(10));
                            fixSomeCurlyBraceForExratFlexability += str1 + Chr(10);
                        }
                    }
                } else {
                    fixSomeCurlyBraceForExratFlexability += A_LoopField183 + Chr(10);
                }
            }
            code = StringTrimRight(fixSomeCurlyBraceForExratFlexability, 1);
            fixSomeCurlyBraceForExratFlexabilityTriHELP = "";
            let items184 = LoopParseFunc(code, "\n", "\r");
            for (let A_Index184 = 0; A_Index184 < items184.length + 0; A_Index184++) {
                const A_LoopField184 = items184[A_Index184 - 0];
                fixSomeCurlyBraceForExratFlexabilityTriHELP += Trim(A_LoopField184) + Chr(10);
            }
            code = StringTrimRight(fixSomeCurlyBraceForExratFlexabilityTriHELP, 1);
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (langToConvertTo != langFileExtension_2) {
                // GUI
                // GUI
                // GUI
                if (langToConvertTo == "js" && InStr(Trim(StrLower(code)), "gui")) {
                    code = guiParser(code);
                }
                // GUI
                // GUI
                // GUI
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            // name: subroutine/func for GUI and backend
            if (langToConvertTo != langFileExtension_2) {
                if (langToConvertTo == "js" || langToConvertTo == "py") {
                    code = initializeBackendAndGUIInteractionWithLabelSubroutineLikeButConvertsToFunction(code);
                }
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (keyWordCurlyBraceOpen != "{") {
                let items185 = LoopParseFunc(code, "\n", "\r");
                for (let A_Index185 = 0; A_Index185 < items185.length + 0; A_Index185++) {
                    const A_LoopField185 = items185[A_Index185 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField185)) == true || Trim(A_LoopField185) == keyWordCurlyBraceOpen) {
                        htCodeOutFixINT2 = 1;
                    }
                    htCodeOutFixINT = 0;
                    let items186 = LoopParseFunc(A_LoopField185, " ");
                    for (let A_Index186 = 0; A_Index186 < items186.length + 0; A_Index186++) {
                        const A_LoopField186 = items186[A_Index186 - 0];
                        htCodeOutFixINT++;
                    }
                    htCodeOutFixINT--;
                    let items187 = LoopParseFunc(A_LoopField185, " ");
                    for (let A_Index187 = 0; A_Index187 < items187.length + 0; A_Index187++) {
                        const A_LoopField187 = items187[A_Index187 - 0];
                        if (htCodeOutFixINT == A_Index187 && htCodeOutFixINT2 == 1) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField187, keyWordCurlyBraceOpen, "{") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField187 + " ";
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
                let items188 = LoopParseFunc(code, "\n", "\r");
                for (let A_Index188 = 0; A_Index188 < items188.length + 0; A_Index188++) {
                    const A_LoopField188 = items188[A_Index188 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField188)) == true || Trim(A_LoopField188) == keyWordCurlyBraceClose) {
                        htCodeOutFixINT2 = 1;
                    }
                    let items189 = LoopParseFunc(A_LoopField188, " ");
                    for (let A_Index189 = 0; A_Index189 < items189.length + 0; A_Index189++) {
                        const A_LoopField189 = items189[A_Index189 - 0];
                        if (htCodeOutFixINT2 == 1 || Trim(A_LoopField189) == keyWordCurlyBraceClose) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField189, keyWordCurlyBraceClose, "}") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField189 + " ";
                        }
                    }
                    htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1);
                    htCodeOutFixEnd += Chr(10);
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        if (useCurlyBraces == "on") {
            code = fixIfElseIfMultiLineStatement(code);
            int5 = 0;
            let items190 = LoopParseFunc(code, "\n", "\r");
            for (let A_Index190 = 0; A_Index190 < items190.length + 0; A_Index190++) {
                const A_LoopField190 = items190[A_Index190 - 0];
                HTVM_Append(addNoCurlyFixWhenNextLineAfterConstructLookAhead, Trim(A_LoopField190));
            }
            HTVM_Append(addNoCurlyFixWhenNextLineAfterConstructLookAhead, " ");
            //;;;
            addNoCurlyFixWhenNextLineAfterConstructOut = "";
            let items191 = LoopParseFunc(code, "\n", "\r");
            for (let A_Index191 = 0; A_Index191 < items191.length + 0; A_Index191++) {
                const A_LoopField191 = items191[A_Index191 - 0];
                if (isLineAconstruct(Trim(A_LoopField191)) && addNoCurlyFixWhenNextLineAfterConstructLookAhead[A_Index191 + 1] != "{") {
                    int5 = 1;
                    addNoCurlyFixWhenNextLineAfterConstructOut += A_LoopField191 + Chr(10) + "{" + Chr(10);
                } else {
                    if (int5 == 1) {
                        int5 = 0;
                        addNoCurlyFixWhenNextLineAfterConstructOut += A_LoopField191 + Chr(10) + "}" + Chr(10);
                    } else {
                        addNoCurlyFixWhenNextLineAfterConstructOut += A_LoopField191 + Chr(10);
                    }
                }
            }
            code = StringTrimRight(addNoCurlyFixWhenNextLineAfterConstructOut, 1);
            int5 = 0;
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        htCodeOutFixEnd = "";
        if (useEnd == "on") {
            let items192 = LoopParseFunc(code, "\n", "\r");
            for (let A_Index192 = 0; A_Index192 < items192.length + 0; A_Index192++) {
                const A_LoopField192 = items192[A_Index192 - 0];
                if (StrLower(Trim(A_LoopField192)) == StrLower(keyWordEnd)) {
                    htCodeOutFixEnd += "}\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField192)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF) && isLineAconstruct(Trim(A_LoopField192)) == true) {
                    htCodeOutFixEnd += A_LoopField192 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField192)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop) && isLineAconstruct(Trim(A_LoopField192)) == true) {
                    htCodeOutFixEnd += A_LoopField192 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField192)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf) && isLineAconstruct(Trim(A_LoopField192)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField192 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField192)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse) && isLineAconstruct(Trim(A_LoopField192)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField192 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField192)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch) && isLineAconstruct(Trim(A_LoopField192)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField192 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField192)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally) && isLineAconstruct(Trim(A_LoopField192)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField192 + "\n{\n";
                }
                else if (isLineAconstruct(Trim(A_LoopField192)) == true) {
                    htCodeOutFixEnd += A_LoopField192 + "\n{\n";
                } else {
                    htCodeOutFixEnd += A_LoopField192 + Chr(10);
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        if (usePythonicColonSyntax == "off") {
            if (useEnd == "off" && useCurlyBraces == "off") {
                htCodeOutFixEnd = "";
                let items193 = LoopParseFunc(code, "\n", "\r");
                for (let A_Index193 = 0; A_Index193 < items193.length + 0; A_Index193++) {
                    const A_LoopField193 = items193[A_Index193 - 0];
                    if (isLineAconstruct(Trim(A_LoopField193)) == true) {
                        htCodeOutFixEnd += A_LoopField193 + ":\n";
                    } else {
                        htCodeOutFixEnd += A_LoopField193 + Chr(10);
                    }
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
        }
        if (useCurlyBraces == "off" && useEnd == "off") {
            code = AddCurlyBraces(code);
        }
        outTrimCode = "";
        let items194 = LoopParseFunc(code, "\n", "\r");
        for (let A_Index194 = 0; A_Index194 < items194.length + 0; A_Index194++) {
            const A_LoopField194 = items194[A_Index194 - 0];
            outTrimCode += Trim(A_LoopField194) + Chr(10);
        }
        code = StringTrimRight(outTrimCode, 1);
        // for converting c++ to js and py
        //code := StrReplace(code, "{}", "[]")
        var outCodeFixBraces = "";
        for (let A_Index195 = 0; A_Index195 < 2 + 0; A_Index195++) {
            outCodeFixBraces = "";
            let items196 = LoopParseFunc(code, "\n", "\r");
            for (let A_Index196 = 0; A_Index196 < items196.length + 0; A_Index196++) {
                const A_LoopField196 = items196[A_Index196 - 0];
                if (InStr(A_LoopField196, Trim(keyWordArrayDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField196, Trim(keyWordArrayOfIntegersDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField196, Trim(keyWordArrayOfStringsDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField196, Trim(keyWordArrayOfFloatingPointNumbersDefinition) + " " + keyWordAssign + " ") || InStr(A_LoopField196, Trim(keyWordArrayOfBooleansDefinition) + " " + keyWordAssign + " ") && useCurlyBracesSyntaxForArrayDef == "on") {
                    if (SubStr(StrLower(A_LoopField196), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc) || SubStr(StrLower(A_LoopField196), 1, StrLen(StrLower(keyWordAsync) + StrLower(keyWordFunc))) == StrLower(keyWordAsync) + StrLower(keyWordFunc)) {
                        if (InStr(Trim(A_LoopField196), "{") && Trim(A_LoopField196) != "{" && SubStr(Trim(A_LoopField196), 1, StrLen(Trim(keyWordComment))) != Trim(keyWordComment)) {
                            outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField196), "{", "")) + "\n{\n";
                        }
                        else if (InStr(Trim(A_LoopField196), "}") && Trim(A_LoopField196) != "}" && SubStr(Trim(A_LoopField196), 1, StrLen(Trim(keyWordComment))) != Trim(keyWordComment)) {
                            outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField196), "}", "")) + Chr(10);
                        } else {
                            outCodeFixBraces += Trim(A_LoopField196) + Chr(10);
                        }
                    } else {
                        outCodeFixBraces += Trim(A_LoopField196) + Chr(10);
                    }
                } else {
                    if (InStr(Trim(A_LoopField196), "{") && Trim(A_LoopField196) != "{" && SubStr(Trim(A_LoopField196), 1, StrLen(Trim(keyWordComment))) != Trim(keyWordComment)) {
                        outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField196), "{", "")) + "\n{\n";
                    }
                    else if (InStr(Trim(A_LoopField196), "}") && Trim(A_LoopField196) != "}" && SubStr(Trim(A_LoopField196), 1, StrLen(Trim(keyWordComment))) != Trim(keyWordComment)) {
                        outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField196), "}", "")) + Chr(10);
                    } else {
                        outCodeFixBraces += Trim(A_LoopField196) + Chr(10);
                    }
                }
            }
            code = StringTrimRight(outCodeFixBraces, 1);
        }
        htCodeOutFixEnd = "";
        if (usePythonicColonSyntax == "on" || useCurlyBraces == "off" && useEnd == "off") {
            let items197 = LoopParseFunc(code, "\n", "\r");
            for (let A_Index197 = 0; A_Index197 < items197.length + 0; A_Index197++) {
                const A_LoopField197 = items197[A_Index197 - 0];
                if (isLineAconstruct(Trim(A_LoopField197)) == true) {
                    htCodeOutFixEnd += StringTrimRight(A_LoopField197, 1) + Chr(10);
                } else {
                    htCodeOutFixEnd += A_LoopField197 + Chr(10);
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        //;; main loop ;;;
        //;; main loop ;;;
        //;; main loop ;;;
        //;; main loop ;;;
        fullLangAllOperators = GETfullLangAllOperators();
        fullLangAllOperators_HELP = GETfullLangAllOperators_HELP();
        if (isNotHTVMfile2 == 0) {
            let items198 = LoopParseFunc(code, "\n", "\r");
            for (let A_Index198 = 0; A_Index198 < items198.length + 0; A_Index198++) {
                const A_LoopField198 = items198[A_Index198 - 0];
                if (StrLower(Trim(A_LoopField198)) == StrLower(keyWordMainLabel)) {
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
                    codeOutFixAndAddMainFunc += A_LoopField198 + Chr(10);
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
        if (useCurlyBraces == "off") {
            code = fixIfElseIfMultiLineStatement(code);
        }
        let items199 = LoopParseFunc(code, "\n", "\r");
        for (let A_Index199 = 0; A_Index199 < items199.length + 0; A_Index199++) {
            const A_LoopField199 = items199[A_Index199 - 0];
            HTVM_Append(lookIntoTheNextLineForFuncWhitNoKeyWord, A_LoopField199);
        }
        HTVM_Append(lookIntoTheNextLineForFuncWhitNoKeyWord, " ");
        if (langToConvertTo != langFileExtension_2) {
            code = OSP(code);
            code = StrReplace(code, "}_HTVM-OSP-HTVM-OSP-REMOVE-OSP-HTVMv2--OSP", "}");
            code = StrReplace(code, "{_HTVM-OSP-HTVM-OSP-REMOVE-OSP-HTVMv2--OSP", "{");
        }
        htCode = "";
        //print("=======UP==========")
        //print(code)
        //print("=======DOWN==========")
        let items200 = LoopParseFunc(code, "\n", "\r");
        for (let A_Index200 = 0; A_Index200 < items200.length + 0; A_Index200++) {
            const A_LoopField200 = items200[A_Index200 - 0];
            lineDone = 0;
            if (SubStr(A_LoopField200, 1, StrLen(keyWordComment)) == keyWordComment) {
                lineDone = 1;
                str1 = StringTrimLeft(A_LoopField200, StrLen(keyWordComment));
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
            else if (InStr(A_LoopField200, "guiInit(") || InStr(A_LoopField200, "guiAdd(") || InStr(A_LoopField200, "guiAddElement(") || InStr(A_LoopField200, "guiControl(") || InStr(A_LoopField200, "HTVM_init(") || InStr(A_LoopField200, "HTVM_register(") || InStr(A_LoopField200, "HTVM_custom_port(") && lineDone == 0) {
                lineDone = 1;
                if (InStr(A_LoopField200, "HTVM_init(")) {
                    htCode += Trim(A_LoopField200) + Chr(10);
                } else {
                    htCode += Trim(expressionParserTranspiler(Trim(A_LoopField200))) + Chr(10);
                }
            }
            else if (Trim(A_LoopField200) == keyWordCommentOpenMultiLine) {
                lineDone = 1;
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
            else if (Trim(A_LoopField200) == keyWordCommentCloseMultiLine) {
                lineDone = 1;
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
            else if (InStr(A_LoopField200, "[][][][][] ")) {
                lineDone = 1;
                str1 = StrSplit(A_LoopField200, " ", 2);
                HTVM_Append(ospDic1, str1);
                strOspHold = StrReplace(str1, "_", ".");
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordStruct_2 + StrReplace(str1, "_", ".") + Chr(10) + "{" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField200)), 1, StrLen(StrLower(keyWordStruct))) == StrLower(keyWordStruct)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField200, StrLen(keyWordStruct)));
                if (langToConvertTo == langFileExtension_2) {
                    htCode += Trim(keyWordStruct_2) + " " + str0 + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField200)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField200, StrLen(keyWordAlliance)));
                if (langToConvertTo == langFileExtension_2) {
                    htCode += Trim(keyWordAlliance_2) + " " + str0 + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField200)), 1, StrLen(StrLower(keyWordCrew))) == StrLower(keyWordCrew)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField200, StrLen(keyWordCrew)));
                if (langToConvertTo == langFileExtension_2) {
                    htCode += Trim(keyWordCrew_2) + " " + str0 + Chr(10);
                }
            }
            else if (InStr(A_LoopField200, "[end][end][end][end][end] ")) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += "}" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField200)), 1, StrLen(StrLower(keyWordProp))) == StrLower(keyWordProp)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField200, StrLen(keyWordProp)));
                str1 = Trim(StrSplit(str0, "-----------------------HTVM-OSP-HTVM-OBJ--------------", 1));
                str20 = Trim(StrSplit(str0, "-----------------------HTVM-OSP-HTVM-OBJ--------------", 2));
                if (str20 == "" && langToConvertTo != langFileExtension_2) {
                    continue;
                }
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordProp_2 + propHELP(str1, "no-no") + Chr(10);
                } else {
                    htCode += propHELP(str1, StrReplace(str20, ".", "_") + "_") + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField200)), 1, StrLen(StrLower(keyWordProc))) == StrLower(keyWordProc)) {
                lineDone = 1;
                str0 = Trim(StringTrimLeft(A_LoopField200, StrLen(keyWordProc)));
                str1 = Trim(StrSplit(str0, "-----------------------HTVM-OSP-HTVM-OBJ--------------", 1));
                str20 = Trim(StrSplit(str0, "-----------------------HTVM-OSP-HTVM-OBJ--------------", 2));
                str16 = Trim(StrSplit(str1, "(", 1));
                str18 = Trim(StrSplit(str1, ")", 2));
                int1 = 0;
                str17 = "";
                let items201 = LoopParseFunc(str16, " ");
                for (let A_Index201 = 0; A_Index201 < items201.length + 0; A_Index201++) {
                    const A_LoopField201 = items201[A_Index201 - 0];
                    str17 = Trim(A_LoopField201);
                }
                // last word aka the proc name
                //str17
                str15 = StrReplace(str20 + "_" + str17, "_", ".");
                HTVM_Append(ospDic2, StringTrimLeft(str15, 11));
                str15 = StrReplace(str15, ".", "_");
                str1 = StrReplace(str1, "(" + keyWordThis + ")", "()");
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
                if (langToConvertTo == langFileExtension_2) {
                    if (int1 == 1) {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            htCode += keyWordAsync_2 + keyWordProc_2 + getFuncTypeConvert(str3) + " " + str2 + "(" + keyWordThis_2 + ")" + Chr(10);
                        } else {
                            htCode += keyWordAsync_2 + keyWordProc_2 + str2 + "(" + keyWordThis_2 + "): " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    } else {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            htCode += keyWordProc_2 + getFuncTypeConvert(str3) + " " + str2 + "(" + keyWordThis_2 + ")" + Chr(10);
                        } else {
                            htCode += keyWordProc_2 + str2 + "(" + keyWordThis_2 + "): " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                }
                availableFuncsInHTVMInHTVM += str15 + Chr(10);
                if (langToConvertTo == "cpp") {
                    htCode += getFuncTypeConvert(str3) + " " + str15 + "(std::string osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "def " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + "):" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    if (int1 == 1) {
                        htCode += "async function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                    } else {
                        if (useJavaScriptAllFuncsAreAsync == "on") {
                            htCode += "async function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                        } else {
                            htCode += "function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                        }
                    }
                }
                // Go
                if (langToConvertTo == "go") {
                    skipLeftCuleyForFuncPLS = 1;
                    if (str3 == keyWordVoid) {
                        htCode += "func " + str15 + "(__HTVM_V2_TO_GO_optionalParams__ ...interface{})" + Chr(10) + "{" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword := " + Chr(34) + Chr(34) + Chr(10) + "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " 0 " + Chr(10) + "{" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword = __HTVM_V2_TO_GO_optionalParams__[0].(string)" + Chr(10) + "}" + Chr(10) + "_ = osp_osp_this_keyword_htvm_osp_this_htvm_keyword" + Chr(10);
                    } else {
                        htCode += "func " + str15 + "(__HTVM_V2_TO_GO_optionalParams__ ...interface{}) " + getFuncTypeConvert(str3) + Chr(10) + "{" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword := " + Chr(34) + Chr(34) + Chr(10) + "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " 0 {" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword = __HTVM_V2_TO_GO_optionalParams__[0].(string)" + Chr(10) + "}" + Chr(10) + "_ = osp_osp_this_keyword_htvm_osp_this_htvm_keyword" + Chr(10);
                    }
                }
                if (langToConvertTo == "lua") {
                    skipLeftCuleyForFuncPLS = 1;
                    htCode += "function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword) " + Chr(10) + "{" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword = osp_osp_this_keyword_htvm_osp_this_htvm_keyword or " + Chr(34) + Chr(34) + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "static " + getFuncTypeConvert(str3) + " " + str15 + "(string osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    skipLeftCuleyForFuncPLS = 1;
                    htCode += "public static " + getFuncTypeConvert(str3) + " " + str15 + "(Object... __HTVM_V2_TO_JAVA_optionalParams__)" + Chr(10) + "{" + Chr(10) + "String osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + "" + Chr(34) + ";  // Initialize the variable" + Chr(10) + "if (__HTVM_V2_TO_JAVA_optionalParams__.length " + Chr(62) + " 0 && __HTVM_V2_TO_JAVA_optionalParams__[0] instanceof String)" + Chr(10) + "{" + Chr(10) + "osp_osp_this_keyword_htvm_osp_this_htvm_keyword = (String) __HTVM_V2_TO_JAVA_optionalParams__[0];" + Chr(10) + "}" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    if (str3 == keyWordVoid) {
                        htCode += "fun " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword: String = " + Chr(34) + Chr(34) + ")" + Chr(10);
                    } else {
                        htCode += "fun " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword: String = " + Chr(34) + Chr(34) + "): " + getFuncTypeConvert(str3) + Chr(10);
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "def " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    if (str3 == keyWordVoid) {
                        htCode += "proc " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword: string = " + Chr(34) + Chr(34) + ") =" + Chr(10);
                    } else {
                        htCode += "proc " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword: string = " + Chr(34) + Chr(34) + "): " + getFuncTypeConvert(str3) + " =" + Chr(10);
                    }
                }
                if (langToConvertTo == "ahk") {
                    htCode += str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword := " + Chr(34) + Chr(34) + ")" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    if (str3 == keyWordVoid) {
                        htCode += "func " + str15 + "(_ osp_osp_this_keyword_htvm_osp_this_htvm_keyword: String = " + Chr(34) + Chr(34) + ")" + Chr(10);
                    } else {
                        htCode += "func " + str15 + "(_ osp_osp_this_keyword_htvm_osp_this_htvm_keyword: String = " + Chr(34) + Chr(34) + ") -> " + getFuncTypeConvert(str3) + Chr(10);
                    }
                }
                if (langToConvertTo == "dart") {
                    htCode += getFuncTypeConvert(str3) + " " + str15 + "([String osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + "])" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    if (useJavaScriptAllFuncsAreAsync == "off") {
                        htCode += "function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword: string = " + Chr(34) + Chr(34) + "): " + getFuncTypeConvert(str3) + Chr(10);
                    } else {
                        htCode += "async function " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword: string = " + Chr(34) + Chr(34) + "): " + getFuncTypeConvert(str3) + Chr(10);
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "def " + str15 + "(osp_osp_this_keyword_htvm_osp_this_htvm_keyword = " + Chr(34) + Chr(34) + ")" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField200)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF) && SubStr(StrLower(Trim(A_LoopField200)), 1, StrLen(StrLower(keyWordElseIf))) != StrLower(keyWordElseIf)) {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(A_LoopField200, StrLen(keyWordIF)));
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
            else if (SubStr(StrLower(Trim(A_LoopField200)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf) && SubStr(StrLower(Trim(A_LoopField200)), 1, StrLen(StrLower(keyWordIF))) != StrLower(keyWordIF)) {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(A_LoopField200, StrLen(keyWordElseIf)));
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
            else if (StrLower(Trim(A_LoopField200)) == StrLower(keyWordElse) || StrLower(Trim(A_LoopField200)) == StrLower(keyWordElse + ":")) {
                lineDone = 1;
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
            else if (SubStr(StrLower(Trim(A_LoopField200)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)) {
                lineDone = 1;
                str1 = Trim(StringTrimLeft(A_LoopField200, StrLen(keyWordWhileLoop)));
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
            else if (StrLower(Trim(A_LoopField200)) == StrLower(keyWordTry) || StrLower(Trim(A_LoopField200)) == StrLower(keyWordTry + ":")) {
                lineDone = 1;
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
            else if (SubStr(StrLower(Trim(A_LoopField200)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)) {
                lineDone = 1;
                str1 = Trim(StrReplace(StrReplace(StringTrimLeft(A_LoopField200, StrLen(keyWordCatch)), "(", ""), ")", ""));
                theTryCatchVarForErrors = str1;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        if (useParentheses_2 == "on") {
                            htCode += keyWordCatch_2 + "(" + str1 + "):" + Chr(10);
                        } else {
                            htCode += keyWordCatch_2 + str1 + ":" + Chr(10);
                        }
                    } else {
                        if (useParentheses_2 == "off") {
                            htCode += keyWordCatch_2 + str1 + Chr(10);
                        } else {
                            htCode += keyWordCatch_2 + "(" + str1 + ")" + Chr(10);
                        }
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
                    htCode += "catch (Exception " + str1 + ")\n";
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
            else if (StrLower(Trim(A_LoopField200)) == StrLower(keyWordFinally) || StrLower(Trim(A_LoopField200)) == StrLower(keyWordFinally + ":")) {
                lineDone = 1;
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
            else if (SubStr(StrLower(Trim(A_LoopField200)), 1, StrLen(StrLower(keyWordThrow))) == StrLower(keyWordThrow)) {
                lineDone = 1;
                str1 = Trim(A_LoopField200);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str1 = expressionParserTranspiler(fixArray1234(Trim(StringTrimLeft(str1, StrLen(keyWordThrow)))));
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordThrow_2 + keyWordErrorMsg_2 + "(" + str1 + ");\n";
                    } else {
                        htCode += keyWordThrow_2 + keyWordErrorMsg_2 + "(" + str1 + ")\n";
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
                    htCode += "throw Exception(" + str1 + ");\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += " throw new Error(" + str1 + ");\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "throw new Exception(" + str1 + ")\n";
                }
            }
            else if (StrLower(A_LoopField200) == StrLower(keyWordBreak) || StrLower(A_LoopField200) == StrLower(keyWordBreak + ";")) {
                lineDone = 1;
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
            else if (StrLower(A_LoopField200) == StrLower(Trim(keyWordReturnStatement)) || StrLower(A_LoopField200) == StrLower(Trim(keyWordReturnStatement) + ";")) {
                lineDone = 1;
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
                    htCode += "return\n";
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
            else if (SubStr(Trim(StrLower(A_LoopField200)), 1, StrLen(StrLower(keyWordReturnStatement))) == StrLower(keyWordReturnStatement)) {
                lineDone = 1;
                str1 = Trim(expressionParserTranspiler(Trim(StringTrimLeft(A_LoopField200, StrLen(keyWordReturnStatement)))));
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
            else if (StrLower(A_LoopField200) == StrLower(keyWordContinue) || StrLower(A_LoopField200) == StrLower(keyWordContinue + ";")) {
                lineDone = 1;
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
            else if (StrLower(A_LoopField200) == "::" + keyWordContinue || StrLower(A_LoopField200) == "::" + keyWordContinue + ";") {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += "::" + keyWordContinue_2 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "::continue" + STR(luaContinueFix_Num) + "::" + Chr(10);
                    luaContinueFix_Num++;
                }
            }
            else if (StrLower(A_LoopField200) == StrLower(keyWordLoopInfinite) || StrLower(A_LoopField200) == StrLower(keyWordLoopInfinite + ":")) {
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
            else if (SubStr(Trim(StrLower(A_LoopField200)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop) && SubStr(Trim(StrLower(A_LoopField200)), 1, StrLen(StrLower(keyWordLoop)) + 2) != StrLower(keyWordLoop) + "% " && SubStr(Trim(StrLower(A_LoopField200)), 1, StrLen(StrLower(keyWordLoopParse))) != StrLower(keyWordLoopParse)) {
                out2 = StringTrimLeft(A_LoopField200, StrLen(keyWordLoop));
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
            else if (SubStr(Trim(StrLower(A_LoopField200)), 1, StrLen(StrLower(keyWordLoop)) + 2) == StrLower(keyWordLoop) + "% ") {
                howMany_fixAindexInGoUnused++;
                out2 = StringTrimLeft(A_LoopField200, StrLen(keyWordLoop) + 2);
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
            else if (SubStr(StrLower(A_LoopField200), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
                howMany_fixAindexInGoUnused++;
                var1 = StringTrimLeft(A_LoopField200, StrLen(keyWordLoopParse));
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
                        itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
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
                        itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "groovy") {
                        itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                } else {
                    if (line2 == "" && line3 == "") {
                        // nothing so only each char
                        if (langToConvertTo == "py") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "js") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
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
                        if (langToConvertTo == "js") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                        }
                        if (langToConvertTo == "py") {
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
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
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
                        if (langToConvertTo == "js") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
                        }
                        if (langToConvertTo == "py") {
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
            else if (SubStrLastChars(Trim(A_LoopField200), StrLen(keyWordInc)) == keyWordInc || SubStrLastChars(Trim(A_LoopField200), StrLen(keyWordInc + ";")) == keyWordInc + ";" && lineDone == 0) {
                if (useSemicolon == "on" || SubStrLastChars(Trim(A_LoopField200), 1) == ";") {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField200), StrLen(keyWordInc + ";")));
                } else {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField200), StrLen(keyWordInc)));
                }
                str1 = Trim(expressionParserTranspiler(str1));
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
            else if (SubStrLastChars(Trim(A_LoopField200), StrLen(keyWordDec)) == keyWordDec || SubStrLastChars(Trim(A_LoopField200), StrLen(keyWordDec + ";")) == keyWordDec + ";" && lineDone == 0) {
                if (useSemicolon == "on" || SubStrLastChars(Trim(A_LoopField200), 1) == ";") {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField200), StrLen(keyWordDec + ";")));
                } else {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField200), StrLen(keyWordDec)));
                }
                str1 = Trim(expressionParserTranspiler(str1));
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
            else if (SubStr(StrLower(Trim(A_LoopField200)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ") && langToConvertTo == langFileExtension_2) {
                htCode += keyWordInclude_2 + " " + Trim(StringTrimLeft(Trim(A_LoopField200), StrLen(StrLower(keyWordInclude) + " "))) + Chr(10);
            }
            else if (StrLower(A_LoopField200) == StrLower(keyWordGlobal) || StrLower(A_LoopField200) == StrLower(keyWordGlobal + ";")) {
                if (langToConvertTo == "ahk") {
                    htCode += "global\n";
                }
            }
            else if (SubStr(StrLower(A_LoopField200), 1, StrLen(StrLower(keyWordAwait))) == StrLower(keyWordAwait)) {
                str1 = StringTrimLeft(A_LoopField200, StrLen(keyWordAwait));
                //MsgBox, % A_LoopField
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
            else if (SubStr(StrLower(A_LoopField200), 1, StrLen(StrLower(keyWordGlobal))) == StrLower(keyWordGlobal)) {
                str1 = StringTrimLeft(A_LoopField200, StrLen(keyWordGlobal));
                //MsgBox, % A_LoopField
                str1 = StrReplace(str1, ";", "");
                lineDone = 1;
                if (langToConvertTo == "py" || langToConvertTo == "ahk" || langToConvertTo == langFileExtension_2) {
                    if (langToConvertTo == langFileExtension_2) {
                        str2 = Trim(keyWordGlobal_2) + " " + str1;
                    } else {
                        str2 = "global " + StrReplace(str1, ".", "_");
                    }
                } else {
                    str2 = "";
                }
                htCode += str2 + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField200), 1, StrLen(keyWordFunc)) == StrLower(keyWordFunc) || SubStr(StrLower(A_LoopField200), 1, StrLen(StrLower(keyWordAsync) + StrLower(keyWordFunc))) == StrLower(keyWordAsync) + StrLower(keyWordFunc) && InStr(StrLower(A_LoopField200), " main(") == false && lineDone == 0) {
                lineDone = 1;
                if (SubStr(StrLower(A_LoopField200), 1, StrLen(StrLower(keyWordAsync) + StrLower(keyWordFunc))) == StrLower(keyWordAsync) + StrLower(keyWordFunc)) {
                    // is async
                    int1 = 1;
                    str1 = Trim(StringTrimLeft(A_LoopField200, StrLen(StrLower(keyWordAsync + keyWordFunc))));
                } else {
                    // is async
                    int1 = 0;
                    str1 = Trim(StringTrimLeft(A_LoopField200, StrLen(StrLower(keyWordFunc))));
                }
                if (langToConvertTo != langFileExtension_2 && langToConvertTo != "cpp" && langToConvertTo != "go" && langToConvertTo != "cs" && langToConvertTo != "java" && langToConvertTo != "kt" && langToConvertTo != "nim" && langToConvertTo != "swift" && langToConvertTo != "dart" && langToConvertTo != "ts") {
                    if (str1 != "") {
                        str4 = "";
                        let items202 = LoopParseFunc(str1, ",");
                        for (let A_Index202 = 0; A_Index202 < items202.length + 0; A_Index202++) {
                            const A_LoopField202 = items202[A_Index202 - 0];
                            if (InStr(A_LoopField202, " := ")) {
                                if (InStr(Trim(StrSplit(A_LoopField202, " := ", 1)), " ") != true) {
                                    str4 += "optanal-HTVM-opt-parmsNOtWorking-theirewIs-a-bug-Iusfbudfbuoeshfuisbav=-fwaegs-awedsf-dd-sfgc " + A_LoopField202 + ", ";
                                } else {
                                    str4 += A_LoopField202 + ", ";
                                }
                            }
                            else if (InStr(A_LoopField202, " = ")) {
                                if (InStr(Trim(StrSplit(A_LoopField202, " = ", 1)), " ") != true) {
                                    str4 += "optanal-HTVM-opt-parmsNOtWorking-theirewIs-a-bug-Iusfbudfbuoeshfuisbav=-fwaegs-awedsf-dd-sfgc " + A_LoopField202 + ", ";
                                } else {
                                    str4 += A_LoopField202 + ", ";
                                }
                            }
                            else if (InStr(A_LoopField202, " " + Trim(keyWordAssign) + " ")) {
                                if (InStr(Trim(StrSplit(A_LoopField202, " " + Trim(keyWordAssign) + " ", 1)), " ") != true) {
                                    str4 += "optanal-HTVM-opt-parmsNOtWorking-theirewIs-a-bug-Iusfbudfbuoeshfuisbav=-fwaegs-awedsf-dd-sfgc " + A_LoopField202 + ", ";
                                } else {
                                    str4 += A_LoopField202 + ", ";
                                }
                            } else {
                                str4 += A_LoopField202 + ", ";
                            }
                        }
                        str1 = StringTrimRight(str4, 2);
                        str1 = StrReplace(str1, "  ", " ");
                    }
                }
                str4 = "";
                str1 = Trim(str1);
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
                    availableFuncsInHTVMInHTVM += str2 + Chr(10);
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
                            if (useJavaScriptAllFuncsAreAsync == "on") {
                                htCode += "async function " + str2 + "()" + Chr(10);
                            } else {
                                htCode += "function " + str2 + "()" + Chr(10);
                            }
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
                        if (int1 == 1) {
                            htCode += "async function " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                        } else {
                            if (useJavaScriptAllFuncsAreAsync == "on") {
                                htCode += "async function " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                            } else {
                                htCode += "function " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        }
                    }
                    if (langToConvertTo == "groovy") {
                        htCode += "def " + str2 + "()" + Chr(10);
                    }
                } else {
                    str4 = "";
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
                    let items203 = LoopParseFunc(str1, ",");
                    for (let A_Index203 = 0; A_Index203 < items203.length + 0; A_Index203++) {
                        const A_LoopField203 = items203[A_Index203 - 0];
                        //print("|" . Trim(A_LoopField) . "|")
                        if (InStr(Trim(A_LoopField203), " ")) {
                            // there is space aka there is a type
                            if (InStr(A_LoopField203, " " + Trim(keyWordAssign) + " ") == false) {
                                if (usePrefixTypeForTypeDefinition == "on") {
                                    // normal
                                    str6 = Trim(A_LoopField203);
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
                                    str6 = Trim(A_LoopField203);
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
                                if (InStr(Trim(StrSplit(Trim(A_LoopField203), " " + Trim(keyWordAssign) + " ", 1)), " ")) {
                                    // there is a type
                                    if (usePrefixTypeForTypeDefinition == "on") {
                                        // normal
                                        str6 = Trim(StrSplit(Trim(A_LoopField203), " " + Trim(keyWordAssign) + " ", 1));
                                        str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField203), " " + Trim(keyWordAssign) + " ", 2))));
                                        str7 = getTheLastWord(str6);
                                        str8 = getFuncTypeConvert(Trim(StringTrimRight(str6, StrLen(Trim(str7)) + 1)));
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;; optanal param ;;;;;;;;;;;;;;;;;
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
                                            if (RegExMatch(str9, "^\\d+(\\.\\d+)?$")) {
                                                str10 += str8 + " " + str7 + " = " + str9 + "f" + Chr(10);
                                            } else {
                                                str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                            }
                                        }
                                        if (langToConvertTo == "java") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "kt") {
                                            if (RegExMatch(str9, "^\\d+(\\.\\d+)?$")) {
                                                str10 += str7 + ": " + str8 + " = " + str9 + "f" + Chr(10);
                                            } else {
                                                str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                            }
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
                                        str6 = Trim(StrSplit(Trim(A_LoopField203), " " + Trim(keyWordAssign) + " ", 1));
                                        str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField203), " " + Trim(keyWordAssign) + " ", 2))));
                                        str7 = Trim(StrSplit(str6, ":", 1));
                                        str8 = getFuncTypeConvert(Trim(StrSplit(str6, ":", 2)));
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;; optanal param ;;;;;;;;;;;;;;;;;
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
                                            if (RegExMatch(str9, "^\\d+(\\.\\d+)?$")) {
                                                str10 += str8 + " " + str7 + " = " + str9 + "f" + Chr(10);
                                            } else {
                                                str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                            }
                                        }
                                        if (langToConvertTo == "java") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "kt") {
                                            if (RegExMatch(str9, "^\\d+(\\.\\d+)?$")) {
                                                str10 += str7 + ": " + str8 + " = " + str9 + "f" + Chr(10);
                                            } else {
                                                str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                            }
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
                                    str8 = Trim(StrSplit(Trim(A_LoopField203), " " + Trim(keyWordAssign) + " ", 1));
                                    str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField203), " " + Trim(keyWordAssign) + " ", 2))));
                                    // str10
                                    // skipLeftCuleyForFuncPLS := 1
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;; optanal param ;;;;;;;;;;;;;;;;;
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
                            str5 += Trim(A_LoopField203) + Chr(10);
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
                        let items204 = LoopParseFunc(str5, "\n", "\r");
                        for (let A_Index204 = 0; A_Index204 < items204.length + 0; A_Index204++) {
                            const A_LoopField204 = items204[A_Index204 - 0];
                            str11 += A_LoopField204 + ", ";
                        }
                        let items205 = LoopParseFunc(str10, "\n", "\r");
                        for (let A_Index205 = 0; A_Index205 < items205.length + 0; A_Index205++) {
                            const A_LoopField205 = items205[A_Index205 - 0];
                            str12 += A_LoopField205 + ", ";
                        }
                        str12 = StringTrimRight(str12, 2);
                        if (langToConvertTo == "dart") {
                            str12 = "[" + str12 + "]";
                        }
                        if (langToConvertTo == "lua") {
                            let items206 = LoopParseFunc(str12, ",");
                            for (let A_Index206 = 0; A_Index206 < items206.length + 0; A_Index206++) {
                                const A_LoopField206 = items206[A_Index206 - 0];
                                str14 += Trim(StrSplit(Trim(A_LoopField206), " = ", 1)) + ", ";
                            }
                            str14 = StringTrimRight(str14, 2);
                            str13 += "{" + Chr(10);
                            let items207 = LoopParseFunc(str12, ",");
                            for (let A_Index207 = 0; A_Index207 < items207.length + 0; A_Index207++) {
                                const A_LoopField207 = items207[A_Index207 - 0];
                                str13 += Trim(StrSplit(Trim(A_LoopField207), " = ", 1)) + " = " + Trim(StrSplit(Trim(A_LoopField207), " = ", 1)) + " or " + Trim(StrSplit(Trim(A_LoopField207), " = ", 2)) + Chr(10);
                            }
                            str12 = str14;
                        }
                        if (langToConvertTo == "go") {
                            str14 = "__HTVM_V2_TO_GO_optionalParams__ ...interface{}";
                            str13 += "{" + Chr(10) + " ";
                            let items208 = LoopParseFunc(str12, ",");
                            for (let A_Index208 = 0; A_Index208 < items208.length + 0; A_Index208++) {
                                const A_LoopField208 = items208[A_Index208 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField208), " = ", 1)), " ", 1));
                                str17 = Trim(StrSplit(Trim(A_LoopField208), " = ", 2));
                                str13 += str16 + " := " + str17 + Chr(10);
                            }
                            let items209 = LoopParseFunc(str12, ",");
                            for (let A_Index209 = 0; A_Index209 < items209.length + 0; A_Index209++) {
                                const A_LoopField209 = items209[A_Index209 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField209), " = ", 1)), " ", 1));
                                str18 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField209), " = ", 1)), " ", 2));
                                // str16 = var name
                                // str18 = var type
                                str13 += "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " " + STR(A_Index209) + Chr(10) + "{" + Chr(10) + str16 + " = __HTVM_V2_TO_GO_optionalParams__[" + STR(A_Index209) + "].(" + str18 + ")" + Chr(10) + "}" + Chr(10);
                            }
                            str12 = str14;
                        }
                        if (langToConvertTo == "java") {
                            str14 = "Object... __HTVM_V2_TO_JAVA_optionalParams__";
                            str13 += "{" + Chr(10);
                            let items210 = LoopParseFunc(str12, ",");
                            for (let A_Index210 = 0; A_Index210 < items210.length + 0; A_Index210++) {
                                const A_LoopField210 = items210[A_Index210 - 0];
                                str19 = Trim(A_LoopField210);
                                str20 = "";
                                let items211 = LoopParseFunc(str19, " ");
                                for (let A_Index211 = 0; A_Index211 < items211.length + 0; A_Index211++) {
                                    const A_LoopField211 = items211[A_Index211 - 0];
                                    if (A_Index211 == 3) {
                                        if (RegExMatch(A_LoopField211, "^\\d+(\\.\\d+)?$")) {
                                            str20 += A_LoopField211 + "f ";
                                        } else {
                                            str20 += A_LoopField211 + " ";
                                        }
                                    } else {
                                        str20 += A_LoopField211 + " ";
                                    }
                                }
                                str20 = StringTrimRight(str20, 1);
                                str13 += Trim(str20) + ";" + Chr(10);
                            }
                            let items212 = LoopParseFunc(str12, ",");
                            for (let A_Index212 = 0; A_Index212 < items212.length + 0; A_Index212++) {
                                const A_LoopField212 = items212[A_Index212 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField212), " = ", 1)), " ", 2));
                                str17 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField212), " = ", 1)), " ", 1));
                                // str16 = var name
                                // str17 = type name
                                str13 += "if (__HTVM_V2_TO_JAVA_optionalParams__.length " + Chr(62) + " " + STR(A_Index212) + ") " + str16 + " = (" + str17 + ") __HTVM_V2_TO_JAVA_optionalParams__[" + STR(A_Index212) + "];" + Chr(10);
                            }
                            str12 = str14;
                        }
                        str11 += str12;
                    }
                    if (Trim(str5) != "" && Trim(str10) == "") {
                        let items213 = LoopParseFunc(str5, "\n", "\r");
                        for (let A_Index213 = 0; A_Index213 < items213.length + 0; A_Index213++) {
                            const A_LoopField213 = items213[A_Index213 - 0];
                            str11 += A_LoopField213 + ", ";
                        }
                        str11 = StringTrimRight(str11, 2);
                    }
                    if (Trim(str5) == "" && Trim(str10) != "") {
                        let items214 = LoopParseFunc(str10, "\n", "\r");
                        for (let A_Index214 = 0; A_Index214 < items214.length + 0; A_Index214++) {
                            const A_LoopField214 = items214[A_Index214 - 0];
                            str11 += A_LoopField214 + ", ";
                        }
                        str11 = StringTrimRight(str11, 2);
                        if (langToConvertTo == "dart") {
                            str11 = "[" + str11 + "]";
                        }
                        if (langToConvertTo == "lua") {
                            let items215 = LoopParseFunc(str11, ",");
                            for (let A_Index215 = 0; A_Index215 < items215.length + 0; A_Index215++) {
                                const A_LoopField215 = items215[A_Index215 - 0];
                                str14 += Trim(StrSplit(Trim(A_LoopField215), " = ", 1)) + ", ";
                            }
                            str14 = StringTrimRight(str14, 2);
                            str13 += "{" + Chr(10);
                            let items216 = LoopParseFunc(str11, ",");
                            for (let A_Index216 = 0; A_Index216 < items216.length + 0; A_Index216++) {
                                const A_LoopField216 = items216[A_Index216 - 0];
                                str13 += Trim(StrSplit(Trim(A_LoopField216), " = ", 1)) + " = " + Trim(StrSplit(Trim(A_LoopField216), " = ", 1)) + " or " + Trim(StrSplit(Trim(A_LoopField216), " = ", 2)) + Chr(10);
                            }
                            str11 = str14;
                        }
                        if (langToConvertTo == "go") {
                            str14 = "__HTVM_V2_TO_GO_optionalParams__ ...interface{}";
                            str13 += "{" + Chr(10) + " ";
                            let items217 = LoopParseFunc(str11, ",");
                            for (let A_Index217 = 0; A_Index217 < items217.length + 0; A_Index217++) {
                                const A_LoopField217 = items217[A_Index217 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField217), " = ", 1)), " ", 1));
                                str17 = Trim(StrSplit(Trim(A_LoopField217), " = ", 2));
                                str13 += str16 + " := " + str17 + Chr(10);
                            }
                            let items218 = LoopParseFunc(str11, ",");
                            for (let A_Index218 = 0; A_Index218 < items218.length + 0; A_Index218++) {
                                const A_LoopField218 = items218[A_Index218 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField218), " = ", 1)), " ", 1));
                                str18 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField218), " = ", 1)), " ", 2));
                                // str16 = var name
                                // str18 = var type
                                str13 += "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " " + STR(A_Index218) + Chr(10) + "{" + Chr(10) + str16 + " = __HTVM_V2_TO_GO_optionalParams__[" + STR(A_Index218) + "].(" + str18 + ")" + Chr(10) + "}" + Chr(10);
                            }
                            str11 = str14;
                        }
                        if (langToConvertTo == "java") {
                            str14 = "Object... __HTVM_V2_TO_JAVA_optionalParams__";
                            str13 += "{" + Chr(10);
                            let items219 = LoopParseFunc(str11, ",");
                            for (let A_Index219 = 0; A_Index219 < items219.length + 0; A_Index219++) {
                                const A_LoopField219 = items219[A_Index219 - 0];
                                str19 = Trim(A_LoopField219);
                                str20 = "";
                                let items220 = LoopParseFunc(str19, " ");
                                for (let A_Index220 = 0; A_Index220 < items220.length + 0; A_Index220++) {
                                    const A_LoopField220 = items220[A_Index220 - 0];
                                    if (A_Index220 == 3) {
                                        if (RegExMatch(A_LoopField220, "^\\d+(\\.\\d+)?$")) {
                                            str20 += A_LoopField220 + "f ";
                                        } else {
                                            str20 += A_LoopField220 + " ";
                                        }
                                    } else {
                                        str20 += A_LoopField220 + " ";
                                    }
                                }
                                str20 = StringTrimRight(str20, 1);
                                str13 += Trim(str20) + ";" + Chr(10);
                            }
                            let items221 = LoopParseFunc(str11, ",");
                            for (let A_Index221 = 0; A_Index221 < items221.length + 0; A_Index221++) {
                                const A_LoopField221 = items221[A_Index221 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField221), " = ", 1)), " ", 2));
                                str17 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField221), " = ", 1)), " ", 1));
                                // str16 = var name
                                // str17 = type name
                                str13 += "if (__HTVM_V2_TO_JAVA_optionalParams__.length " + Chr(62) + " " + STR(A_Index221) + ") " + str16 + " = (" + str17 + ") __HTVM_V2_TO_JAVA_optionalParams__[" + STR(A_Index221) + "];" + Chr(10);
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
                    availableFuncsInHTVMInHTVM += str2 + Chr(10);
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
                            if (useJavaScriptAllFuncsAreAsync == "on") {
                                htCode += "async function " + str2 + "(" + str11 + ")" + Chr(10);
                            } else {
                                htCode += "function " + str2 + "(" + str11 + ")" + Chr(10);
                            }
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
                        if (int1 == 1) {
                            htCode += "async function " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                        } else {
                            if (useJavaScriptAllFuncsAreAsync == "on") {
                                htCode += "async function " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                            } else {
                                htCode += "function " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        }
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
            else if (InStr(StrLower(A_LoopField200), " main(") && lineDone == 0) {
                lineDone = 1;
                javaMainFuncSeen = 1;
                csMainFuncSeen = 1;
                htCode += A_LoopField200 + Chr(10);
            }
            else if (InStr(A_LoopField200, " " + keyWordAssign + " ") || InStr(A_LoopField200, " " + keyWordAssignAdd + " ") || InStr(A_LoopField200, " " + keyWordAssignConcat + " ") || InStr(A_LoopField200, " " + keyWordAssignSub + " ") || InStr(A_LoopField200, " " + keyWordAssignMul + " ") || InStr(A_LoopField200, " " + keyWordAssignDiv + " ") || InStr(A_LoopField200, " " + keyWordAssignMod + " ") || InStr(A_LoopField200, " " + keyWordAssignShiftLeft + " ") || InStr(A_LoopField200, " " + keyWordAssignShiftRight + " ") || InStr(A_LoopField200, " " + keyWordLogicalAssignShiftRight + " ") || InStr(A_LoopField200, " " + keyWordAssignBitAnd + " ") || InStr(A_LoopField200, " " + keyWordAssignBitOr + " ") || InStr(A_LoopField200, " " + keyWordAssignBitXor + " ") && lineDone == 0) {
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
                if (InStr(A_LoopField200, " " + keyWordAssign + " ")) {
                    str1 = StrSplit(A_LoopField200, " " + keyWordAssign + " ", 1);
                    str6 = StrSplit(A_LoopField200, " " + keyWordAssign + " ", 2);
                    str10 = keyWordAssign;
                    str11 = keyWordAssign_2;
                    if (langToConvertTo == "ahk") {
                        str12 = ":=";
                    } else {
                        str12 = "=";
                    }
                }
                else if (InStr(A_LoopField200, " " + keyWordAssignAdd + " ")) {
                    str1 = StrSplit(A_LoopField200, " " + keyWordAssignAdd + " ", 1);
                    str6 = StrSplit(A_LoopField200, " " + keyWordAssignAdd + " ", 2);
                    str10 = keyWordAssignAdd;
                    str11 = keyWordAssignAdd_2;
                    str12 = "+=";
                }
                else if (InStr(A_LoopField200, " " + keyWordAssignConcat + " ")) {
                    str1 = StrSplit(A_LoopField200, " " + keyWordAssignConcat + " ", 1);
                    str6 = StrSplit(A_LoopField200, " " + keyWordAssignConcat + " ", 2);
                    str10 = keyWordAssignConcat;
                    str11 = keyWordAssignConcat_2;
                    if (langToConvertTo == "ahk") {
                        str12 = ".=";
                    } else {
                        str12 = "+=";
                    }
                }
                else if (InStr(A_LoopField200, " " + keyWordAssignSub + " ")) {
                    str1 = StrSplit(A_LoopField200, " " + keyWordAssignSub + " ", 1);
                    str6 = StrSplit(A_LoopField200, " " + keyWordAssignSub + " ", 2);
                    str10 = keyWordAssignSub;
                    str11 = keyWordAssignSub_2;
                    str12 = "-=";
                }
                else if (InStr(A_LoopField200, " " + keyWordAssignMul + " ")) {
                    str1 = StrSplit(A_LoopField200, " " + keyWordAssignMul + " ", 1);
                    str6 = StrSplit(A_LoopField200, " " + keyWordAssignMul + " ", 2);
                    str10 = keyWordAssignMul;
                    str11 = keyWordAssignMul_2;
                    str12 = "*=";
                }
                else if (InStr(A_LoopField200, " " + keyWordAssignDiv + " ")) {
                    str1 = StrSplit(A_LoopField200, " " + keyWordAssignDiv + " ", 1);
                    str6 = StrSplit(A_LoopField200, " " + keyWordAssignDiv + " ", 2);
                    str10 = keyWordAssignDiv;
                    str11 = keyWordAssignDiv_2;
                    str12 = "/=";
                }
                else if (InStr(A_LoopField200, " " + keyWordAssignMod + " ")) {
                    str1 = StrSplit(A_LoopField200, " " + keyWordAssignMod + " ", 1);
                    str6 = StrSplit(A_LoopField200, " " + keyWordAssignMod + " ", 2);
                    str10 = keyWordAssignMod;
                    str11 = keyWordAssignMod_2;
                    str12 = "%=";
                }
                else if (InStr(A_LoopField200, " " + keyWordAssignShiftLeft + " ")) {
                    str1 = StrSplit(A_LoopField200, " " + keyWordAssignShiftLeft + " ", 1);
                    str6 = StrSplit(A_LoopField200, " " + keyWordAssignShiftLeft + " ", 2);
                    str10 = keyWordAssignShiftLeft;
                    str11 = keyWordAssignShiftLeft_2;
                    str12 = "<<=";
                }
                else if (InStr(A_LoopField200, " " + keyWordAssignShiftRight + " ")) {
                    str1 = StrSplit(A_LoopField200, " " + keyWordAssignShiftRight + " ", 1);
                    str6 = StrSplit(A_LoopField200, " " + keyWordAssignShiftRight + " ", 2);
                    str10 = keyWordAssignShiftRight;
                    str11 = keyWordAssignShiftRight_2;
                    str12 = ">>=";
                }
                else if (InStr(A_LoopField200, " " + keyWordLogicalAssignShiftRight + " ")) {
                    str1 = StrSplit(A_LoopField200, " " + keyWordLogicalAssignShiftRight + " ", 1);
                    str6 = StrSplit(A_LoopField200, " " + keyWordLogicalAssignShiftRight + " ", 2);
                    str10 = keyWordLogicalAssignShiftRight;
                    str11 = keyWordLogicalAssignShiftRight_2;
                    str12 = ">>>=";
                }
                else if (InStr(A_LoopField200, " " + keyWordAssignBitAnd + " ")) {
                    str1 = StrSplit(A_LoopField200, " " + keyWordAssignBitAnd + " ", 1);
                    str6 = StrSplit(A_LoopField200, " " + keyWordAssignBitAnd + " ", 2);
                    str10 = keyWordAssignBitAnd;
                    str11 = keyWordAssignBitAnd_2;
                    str12 = "&=";
                }
                else if (InStr(A_LoopField200, " " + keyWordAssignBitOr + " ")) {
                    str1 = StrSplit(A_LoopField200, " " + keyWordAssignBitOr + " ", 1);
                    str6 = StrSplit(A_LoopField200, " " + keyWordAssignBitOr + " ", 2);
                    str10 = keyWordAssignBitOr;
                    str11 = keyWordAssignBitOr_2;
                    str12 = "|=";
                }
                else if (InStr(A_LoopField200, " " + keyWordAssignBitXor + " ")) {
                    str1 = StrSplit(A_LoopField200, " " + keyWordAssignBitXor + " ", 1);
                    str6 = StrSplit(A_LoopField200, " " + keyWordAssignBitXor + " ", 2);
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
                if (InStr(ALoopField, " ") == false || SubStrLastChars(ALoopField, 1) == "]") {
                    lineDone = 1;
                    if (langToConvertTo != langFileExtension_2) {
                        str1 = StrReplace(Trim(str1), ".", "_");
                    }
                    str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str1);
                    if (InStr(saveAllArrayVarNamesSoWeCanDoAfix, "|" + Trim(str1) + "|")) {
                        str6 = Trim(str6);
                        if (SubStr(str6, 1, 1) == "[" || SubStr(str6, 1, 1) == "{") {
                            str6 = StringTrimRight(str6, 1);
                            str6 = StringTrimLeft(str6, 1);
                            if (langToConvertTo == "cpp") {
                                str6 = "{" + str6 + "}";
                            }
                            if (langToConvertTo == "py") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "js") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "go") {
                                str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                            }
                            if (langToConvertTo == "lua") {
                                str6 = "{" + str6 + "}";
                            }
                            if (langToConvertTo == "cs") {
                                str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                            }
                            if (langToConvertTo == "java") {
                                str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                            }
                            if (langToConvertTo == "kt") {
                                str6 = "THIS IS NOT POSSIBLE MAYBE TRY TO RESET THE ARRAY AND THEN PUSH INTO IT[" + str6 + "]";
                            }
                            if (langToConvertTo == "rb") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "nim") {
                                str6 = "@[" + str6 + "]";
                            }
                            if (langToConvertTo == "ahk") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "swift") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "dart") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "ts") {
                                str6 = "[" + str6 + "]";
                            }
                            if (langToConvertTo == "groovy") {
                                str6 = "[" + str6 + "]";
                            }
                        }
                    }
                    if (Trim(str6) == "[]" || Trim(str6) == "{}") {
                        if (useCurlyBracesSyntaxForArrayDef_2 == "on" && langToConvertTo == langFileExtension_2) {
                            str6 = "{}";
                        } else {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "cpp") {
                            str6 = "{}";
                        }
                        if (langToConvertTo == "py") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "js") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "go") {
                            str6 = Trim(str1) + "[:0]";
                        }
                        if (langToConvertTo == "lua") {
                            str6 = "{}";
                        }
                        if (langToConvertTo == "cs") {
                            str6 = "ResetList(" + Trim(str1) + ")";
                        }
                        if (langToConvertTo == "java") {
                            str6 = "new ArrayList<>()";
                        }
                        if (langToConvertTo == "kt") {
                            str6 = "ArrayList()";
                        }
                        if (langToConvertTo == "rb") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "nim") {
                            str6 = "@[]";
                        }
                        if (langToConvertTo == "ahk") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "swift") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "dart") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "ts") {
                            str6 = "[]";
                        }
                        if (langToConvertTo == "groovy") {
                            str6 = "[]";
                        }
                    }
                    //;;;;;;;;;;;;;;;;;
                    //;;;;;;;;;;;;;;;;;
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
                        if (Trim(str6) == "[]" || Trim(str6) == "{}") {
                            str4 = str1 + " " + str12 + " " + str6 + ";";
                        } else {
                            if (InStr(str1, "[")) {
                                // Convert arr[something] to arr.set(something, value);
                                str1 = RegExReplace(str1, "(\\b[A-Za-z_]\\w*)\\s*\\[(.*?)\\]", "$1.set($2, ");
                                str4 = str1 + str6 + ");";
                            } else {
                                str4 = str1 + " " + str12 + " " + str6 + ";";
                            }
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
                        let items222 = LoopParseFunc(str1, " ");
                        for (let A_Index222 = 0; A_Index222 < items222.length + 0; A_Index222++) {
                            const A_LoopField222 = items222[A_Index222 - 0];
                            str2 = A_LoopField222;
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
                        saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                        str3 = getFuncTypeConvert(str3);
                        int5 = 0;
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                if (int5 != 0) {
                                    str6 = "{" + str6 + "}";
                                }
                            } else {
                                if (int5 != 0) {
                                    str6 = "[" + str6 + "]";
                                }
                            }
                            if (useSemicolon_2 == "on") {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
                                }
                            }
                        }
                        if (langToConvertTo == "cpp") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "py") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " [" + str6 + "]";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6 + "";
                            }
                        }
                        if (langToConvertTo == "js") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            if (int5 != 0) {
                                str4 = str2 + " := " + str3 + "{" + str6 + "}";
                            } else {
                                str4 = str2 + " := " + str3 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "lua") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " {" + str6 + "}";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = str3 + " " + str2 + " = " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "kt") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                            } else {
                                str4 = "var " + str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "rb") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "nim") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + str3 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "ahk") {
                            if (int5 != 0) {
                                str4 = str2 + " := [" + str6 + "]";
                            } else {
                                str4 = str2 + " := " + str6;
                            }
                        }
                        if (langToConvertTo == "swift") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "dart") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = [" + str6 + "];";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "ts") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
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
                                    str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6 + ";";
                                } else {
                                    str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6 + ";";
                                }
                            } else {
                                if (usePrefixTypeForTypeDefinition_2 == "on") {
                                    str4 = Trim(keyWordConst_2) + " " + str3 + " " + str2 + " " + str11 + " " + str6;
                                } else {
                                    str4 = Trim(keyWordConst_2) + " " + str2 + ": " + str3 + " " + str11 + " " + str6;
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
                            str4 = "final " + str3 + " " + str2 + " " + str12 + " " + str6 + ";";
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
                        let items223 = LoopParseFunc(str1, " ");
                        for (let A_Index223 = 0; A_Index223 < items223.length + 0; A_Index223++) {
                            const A_LoopField223 = items223[A_Index223 - 0];
                            str2 = A_LoopField223;
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
                        saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                        str3 = getFuncTypeConvert(str3);
                        int5 = 0;
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                if (int5 != 0) {
                                    str6 = "{" + str6 + "}";
                                }
                            } else {
                                if (int5 != 0) {
                                    str6 = "[" + str6 + "]";
                                }
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
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "py") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " [" + str6 + "]";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6 + "";
                            }
                        }
                        if (langToConvertTo == "js") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            if (int5 != 0) {
                                str4 = str2 + " := " + str3 + "{" + str6 + "}";
                            } else {
                                str4 = str2 + " := " + str3 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "lua") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " {" + str6 + "}";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = str3 + " " + str2 + " = " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "kt") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                            } else {
                                str4 = "var " + str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "rb") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "nim") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + str3 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "ahk") {
                            if (int5 != 0) {
                                str4 = str2 + " := [" + str6 + "]";
                            } else {
                                str4 = str2 + " := " + str6;
                            }
                        }
                        if (langToConvertTo == "swift") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "dart") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = [" + str6 + "];";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "ts") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
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
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        //;;;
                    }
                    htCode += str4 + Chr(10);
                }
                else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordLet)) == keyWordLet && lineDone == 0) {
                    lineDone = 1;
                    if (usePostfixTypeForTypeDefinition == "off") {
                        str1 = Trim(StringTrimLeft(Trim(str1), StrLen(keyWordLet)));
                        let items224 = LoopParseFunc(str1, " ");
                        for (let A_Index224 = 0; A_Index224 < items224.length + 0; A_Index224++) {
                            const A_LoopField224 = items224[A_Index224 - 0];
                            str2 = A_LoopField224;
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
                        saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                        str3 = getFuncTypeConvert(str3);
                        int5 = 0;
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        str6 = allVarsSoWeDontReDecVarsFixFunc(str6, str2);
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                if (int5 != 0) {
                                    str6 = "{" + str6 + "}";
                                }
                            } else {
                                if (int5 != 0) {
                                    str6 = "[" + str6 + "]";
                                }
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
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "py") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " [" + str6 + "]";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6 + "";
                            }
                        }
                        if (langToConvertTo == "js") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            if (int5 != 0) {
                                str4 = str2 + " := " + str3 + "{" + str6 + "}";
                            } else {
                                str4 = str2 + " := " + str3 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "lua") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " {" + str6 + "}";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = str3 + " " + str2 + " = " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "kt") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                            } else {
                                str4 = "var " + str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "rb") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "nim") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + str3 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "ahk") {
                            if (int5 != 0) {
                                str4 = str2 + " := [" + str6 + "]";
                            } else {
                                str4 = str2 + " := " + str6;
                            }
                        }
                        if (langToConvertTo == "swift") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "dart") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = [" + str6 + "];";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "ts") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
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
                            str4 = str2 + " " + str12 + " " + str6;
                        }
                        //;;;
                    }
                    htCode += str4 + Chr(10);
                }
                else if (SubStr(Trim(ALoopField), 1, StrLen(keyWordDouble + " ")) == keyWordDouble + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordChar + " ")) == keyWordChar + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint8 + " ")) == keyWordUint8 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint16 + " ")) == keyWordUint16 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint32 + " ")) == keyWordUint32 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordUint64 + " ")) == keyWordUint64 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT + " ")) == keyWordINT + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordSTR + " ")) == keyWordSTR + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordBOOL + " ")) == keyWordBOOL + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordFLOAT + " ")) == keyWordFLOAT + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT8 + " ")) == keyWordINT8 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT16 + " ")) == keyWordINT16 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT32 + " ")) == keyWordINT32 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordINT64 + " ")) == keyWordINT64 + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayDefinition + " ")) == keyWordArrayDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfIntegersDefinition + " ")) == keyWordArrayOfIntegersDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfStringsDefinition + " ")) == keyWordArrayOfStringsDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfFloatingPointNumbersDefinition + " ")) == keyWordArrayOfFloatingPointNumbersDefinition + " " || SubStr(Trim(ALoopField), 1, StrLen(keyWordArrayOfBooleansDefinition + " ")) == keyWordArrayOfBooleansDefinition + " " && usePrefixTypeForTypeDefinition == "on" && lineDone == 0) {
                    lineDone = 1;
                    let items225 = LoopParseFunc(str1, " ");
                    for (let A_Index225 = 0; A_Index225 < items225.length + 0; A_Index225++) {
                        const A_LoopField225 = items225[A_Index225 - 0];
                        str2 = A_LoopField225;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                    if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                        saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                        str3 = getFuncTypeConvert(str3);
                        int5 = 0;
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                if (int5 != 0) {
                                    str6 = "{" + str6 + "}";
                                }
                            } else {
                                if (int5 != 0) {
                                    str6 = "[" + str6 + "]";
                                }
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
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "py") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " [" + str6 + "]";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6 + "";
                            }
                        }
                        if (langToConvertTo == "js") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            if (int5 != 0) {
                                str4 = str2 + " := " + str3 + "{" + str6 + "}";
                            } else {
                                str4 = str2 + " := " + str3 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "lua") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " {" + str6 + "}";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = str3 + " " + str2 + " = " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "kt") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                            } else {
                                str4 = "var " + str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "rb") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "nim") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + str3 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "ahk") {
                            if (int5 != 0) {
                                str4 = str2 + " := [" + str6 + "]";
                            } else {
                                str4 = str2 + " := " + str6;
                            }
                        }
                        if (langToConvertTo == "swift") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "dart") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = [" + str6 + "];";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "ts") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
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
                            str4 = str2 + " " + str12 + " " + str6;
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
                        saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
                        str3 = getFuncTypeConvert(str3);
                        int5 = 0;
                        if (useCurlyBracesSyntaxForArrayDef == "on") {
                            if (SubStr(str6, 1, 1) == "{") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        } else {
                            if (SubStr(str6, 1, 1) == "[") {
                                int5 = 1;
                                str6 = StringTrimRight(str6, 1);
                                str6 = StringTrimLeft(str6, 1);
                            }
                        }
                        if (langToConvertTo == langFileExtension_2) {
                            if (useCurlyBracesSyntaxForArrayDef_2 == "on") {
                                if (int5 != 0) {
                                    str6 = "{" + str6 + "}";
                                }
                            } else {
                                if (int5 != 0) {
                                    str6 = "[" + str6 + "]";
                                }
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
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " " + str12 + " {" + str6 + "};";
                            } else {
                                str4 = str3 + " " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "py") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " [" + str6 + "]";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6 + "";
                            }
                        }
                        if (langToConvertTo == "js") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + " " + str12 + " [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + " " + str12 + " " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "go") {
                            if (int5 != 0) {
                                str4 = str2 + " := " + str3 + "{" + str6 + "}";
                            } else {
                                str4 = str2 + " := " + str3 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "lua") {
                            if (int5 != 0) {
                                str4 = str2 + " " + str12 + " {" + str6 + "}";
                            } else {
                                str4 = str2 + " " + str12 + " " + str6;
                            }
                        }
                        if (langToConvertTo == "cs") {
                            if (csMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " {" + str6 + "};";
                                } else {
                                    str4 = "static " +  str3 + " " + str2 + " = new " + str3 + " " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "java") {
                            if (javaMainFuncSeen == 1) {
                                if (int5 != 0) {
                                    str4 = str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = str3 + " " + str2 + " = " + str6 + ";";
                                }
                            } else {
                                if (int5 != 0) {
                                    str4 = "static " + str3 + " " + str2 + " = new ArrayList<>(List.of(" + str6 + "));";
                                } else {
                                    str4 = "static " + str3 + " " + str2 + " = " + str6 + ";";
                                }
                            }
                        }
                        if (langToConvertTo == "kt") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + " = arrayListOf(" + str6 + ")";
                            } else {
                                str4 = "var " + str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "rb") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "nim") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + str3 + " = @[" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + str3 + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "ahk") {
                            if (int5 != 0) {
                                str4 = str2 + " := [" + str6 + "]";
                            } else {
                                str4 = str2 + " := " + str6;
                            }
                        }
                        if (langToConvertTo == "swift") {
                            if (int5 != 0) {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = [" + str6 + "]";
                            } else {
                                str4 = "var " + str2 + ": " + Trim(StrSplit(str3, " ", 2)) + " = " + str6;
                            }
                        }
                        if (langToConvertTo == "dart") {
                            if (int5 != 0) {
                                str4 = str3 + " " + str2 + " = [" + str6 + "];";
                            } else {
                                str4 = str3 + " " + str2 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "ts") {
                            if (int5 != 0) {
                                str4 = "let " + str2 + ": " + str3 + " = [" + str6 + "];";
                            } else {
                                str4 = "let " + str2 + ": " + str3 + " = " + str6 + ";";
                            }
                        }
                        if (langToConvertTo == "groovy") {
                            if (int5 != 0) {
                                str4 = str2 + " = [" + str6 + "]";
                            } else {
                                str4 = str2 + " = " + str6;
                            }
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
                            str4 = str2 + " " + str12 + " " + str6 + ";";
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
            else if (SubStr(Trim(A_LoopField200), 1, StrLen(keyWordVar)) == keyWordVar && lineDone == 0) {
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField200), StrLen(keyWordVar)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    let items226 = LoopParseFunc(str1, " ");
                    for (let A_Index226 = 0; A_Index226 < items226.length + 0; A_Index226++) {
                        const A_LoopField226 = items226[A_Index226 - 0];
                        str2 = A_LoopField226;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField200), StrLen(keyWordVar)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    str2 = Trim(StrSplit(str1, ":", 1));
                    str3 = Trim(StrSplit(str1, ":", 2));
                    // str2 = var name
                    // str3 = type
                }
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
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
                        str4 = "var " + str2 + " = " + str3 + "()";
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
                        str4 = str2 + " = []";
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
                        str4 = str2 + " = null";
                    }
                    //;;;
                }
                htCode += str4 + Chr(10);
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if (SubStr(Trim(A_LoopField200), 1, StrLen(keyWordLet)) == keyWordLet && lineDone == 0) {
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                if (usePostfixTypeForTypeDefinition == "off") {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField200), StrLen(keyWordLet)));
                    if (SubStrLastChars(str1, 1) == ";") {
                        str1 = StringTrimRight(str1, 1);
                    }
                    let items227 = LoopParseFunc(str1, " ");
                    for (let A_Index227 = 0; A_Index227 < items227.length + 0; A_Index227++) {
                        const A_LoopField227 = items227[A_Index227 - 0];
                        str2 = A_LoopField227;
                    }
                    str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                    str2 = Trim(str2);
                    // str2 = var name
                    // str3 = type
                    HTVM_Append(allVarsSoWeDontReDecVars, str2);
                } else {
                    lineDone = 1;
                    str1 = Trim(StringTrimLeft(Trim(A_LoopField200), StrLen(keyWordLet)));
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
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
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
                        str4 = "var " + str2 + " = " + str3 + "()";
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
                        str4 = str2 + " = []";
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
                        str4 = str2 + " = null";
                    }
                    //;;;
                }
                htCode += str4 + Chr(10);
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if (SubStr(Trim(A_LoopField200), 1, StrLen(keyWordDouble + " ")) == keyWordDouble + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordChar + " ")) == keyWordChar + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordUint8 + " ")) == keyWordUint8 + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordUint16 + " ")) == keyWordUint16 + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordUint32 + " ")) == keyWordUint32 + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordUint64 + " ")) == keyWordUint64 + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordINT + " ")) == keyWordINT + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordSTR + " ")) == keyWordSTR + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordBOOL + " ")) == keyWordBOOL + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordFLOAT + " ")) == keyWordFLOAT + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordINT8 + " ")) == keyWordINT8 + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordINT16 + " ")) == keyWordINT16 + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordINT32 + " ")) == keyWordINT32 + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordINT64 + " ")) == keyWordINT64 + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordArrayDefinition + " ")) == keyWordArrayDefinition + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordArrayOfIntegersDefinition + " ")) == keyWordArrayOfIntegersDefinition + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordArrayOfStringsDefinition + " ")) == keyWordArrayOfStringsDefinition + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordArrayOfFloatingPointNumbersDefinition + " ")) == keyWordArrayOfFloatingPointNumbersDefinition + " " || SubStr(Trim(A_LoopField200), 1, StrLen(keyWordArrayOfBooleansDefinition + " ")) == keyWordArrayOfBooleansDefinition + " " && usePrefixTypeForTypeDefinition == "on" && lineDone == 0) {
                lineDone = 1;
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                str1 = Trim(A_LoopField200);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                let items228 = LoopParseFunc(str1, " ");
                for (let A_Index228 = 0; A_Index228 < items228.length + 0; A_Index228++) {
                    const A_LoopField228 = items228[A_Index228 - 0];
                    str2 = A_LoopField228;
                }
                str3 = Trim(StringTrimRight(str1, StrLen(str2)));
                str2 = Trim(str2);
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
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
                        str4 = "var " + str2 + " = " + str3 + "()";
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
                        str4 = str2 + " = []";
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
                        str4 = str2 + " = null";
                    }
                    //;;;
                }
                htCode += str4 + Chr(10);
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if (RegExMatch(Trim(A_LoopField200), "^[a-zA-Z_][a-zA-Z0-9_]*: [^:]*;?$") && usePostfixTypeForTypeDefinition == "on" && lineDone == 0) {
                lineDone = 1;
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 1;
                str1 = Trim(A_LoopField200);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str2 = Trim(StrSplit(str1, ":", 1));
                str3 = Trim(StrSplit(str1, ":", 2));
                // str2 = var name
                // str3 = type
                HTVM_Append(allVarsSoWeDontReDecVars, str2);
                if (str3 == keyWordArrayDefinition || str3 == keyWordArrayOfIntegersDefinition || str3 == keyWordArrayOfStringsDefinition || str3 == keyWordArrayOfFloatingPointNumbersDefinition || str3 == keyWordArrayOfBooleansDefinition) {
                    saveAllArrayVarNamesSoWeCanDoAfix += "|" + Trim(str2) + "|";
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
                        str4 = "var " + str2 + " = " + str3 + "()";
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
                        str4 = str2 + " = []";
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
                        str4 = str2 + " = null";
                    }
                    //;;;
                }
                htCode += str4 + Chr(10);
                allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
            }
            else if (RegExMatch(Trim(A_LoopField200), "^[a-zA-Z0-9_\\.]+\\(") && !(InStr(StrLower(A_LoopField200), " main(")) && lineDone == 0) {
                lineDone = 1;
                str1 = Trim(A_LoopField200);
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
            else if (RegExMatch(A_LoopField200, "\\.[a-zA-Z_][a-zA-Z0-9_]*") && lineDone == 0) {
                lineDone = 1;
                str1 = Trim(A_LoopField200);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                if (langToConvertTo != langFileExtension_2) {
                    if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "groovy") {
                        htCode += expressionParserTranspiler(extraFlexableFuncCalls(str1, availableFuncsInHTVMInHTVM)) + Chr(10);
                    } else {
                        htCode += expressionParserTranspiler(extraFlexableFuncCalls(str1, availableFuncsInHTVMInHTVM)) + ";" + Chr(10);
                    }
                } else {
                    if (useSemicolon_2 == "on") {
                        htCode += str1 + "; " + Chr(10);
                    } else {
                        htCode += str1 + Chr(10);
                    }
                }
            }
            else if (KeyWordsCommands(A_LoopField200, "check", commands, langToConvertTo) == "true" && lineDone == 0) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += A_LoopField200 + Chr(10);
                } else {
                    out_KeyWordsCommands = KeyWordsCommands(A_LoopField200, "transpile", commands, langToConvertTo);
                    htCode += out_KeyWordsCommands + Chr(10);
                }
            } else {
                //print("else else else " . A_LoopField)
                // this is THE else
                //;;;;;;;;;;;;;;;;;;
                if (lineDone != 1) {
                    if (skipLeftCuleyForFuncPLS != 1) {
                        if (SubStr(Trim(StrLower(A_LoopField200)), 1, 1) == Chr(125)) {
                            htCode += Chr(125) + Chr(10);
                        } else {
                            if (htCodeAcurlyBraceAddSomeVrasFixLP == 1 && SubStr(Trim(StrLower(A_LoopField200)), 1, 1) == Chr(123)) {
                                htCodeAcurlyBraceAddSomeVrasFixLP = 0;
                                htCode += A_LoopField200 + Chr(10) + theFixTextLoopLP + Chr(10);
                            } else {
                                if (htCodeAcurlyBraceAddSomeVrasFixNL == 1 && SubStr(Trim(StrLower(A_LoopField200)), 1, 1) == Chr(123)) {
                                    htCodeAcurlyBraceAddSomeVrasFixNL = 0;
                                    htCode += A_LoopField200 + Chr(10) + theFixTextLoopNL + Chr(10);
                                } else {
                                    htCode += A_LoopField200 + Chr(10);
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
                let items229 = LoopParseFunc(htCodeLoopfixa, "\n", "\r");
                for (let A_Index229 = 0; A_Index229 < items229.length + 0; A_Index229++) {
                    const A_LoopField229 = items229[A_Index229 - 0];
                    sstr123 = A_LoopField229;
                    fixLoopLokingFor = A_LoopField229;
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
                        let items230 = LoopParseFunc(htCode, "\n", "\r");
                        for (let A_Index230 = 0; A_Index230 < items230.length + 0; A_Index230++) {
                            const A_LoopField230 = items230[A_Index230 - 0];
                            //MsgBox, dsfgsdefgesrdg1
                            //MsgBox, |%A_LoopField%|`n|%fixLoopLokingFor%|
                            if (InStr(A_LoopField230, fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 1
                            }
                            if (SubStr(Trim(A_LoopField230), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField230 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(s);
                                //MsgBox, % out1z
                                //MsgBox, do we came here 2
                                fixLoopLokingForNum = 0;
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField
                                dontSaveStr = 1;
                                ALoopField = A_LoopField230;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if (inTarget == 1 && InStr(A_LoopField230, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField230, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField230, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField230), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField230, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField230, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField230, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField230, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField230 + Chr(10);
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField230;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "\\b" + keyWordAIndex + "\\d*\\b", "" + keyWordAIndex + "" + out1z);
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if (inTarget == 1 && InStr(A_LoopField230, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1) {
                                //MsgBox, % A_LoopField
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField230 + Chr(10);
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
                        let items231 = LoopParseFunc(htCode, "\n", "\r");
                        for (let A_Index231 = 0; A_Index231 < items231.length + 0; A_Index231++) {
                            const A_LoopField231 = items231[A_Index231 - 0];
                            if (InStr(A_LoopField231 , fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 3
                            }
                            if (SubStr(Trim(A_LoopField231), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField231 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(StrReplace(s, "|", ""));
                                //MsgBox, % out1z
                                fixLoopLokingForNum = 0;
                                //MsgBox, do we came here 4
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField
                                dontSaveStr = 1;
                                ALoopField = A_LoopField231;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if (inTarget == 1 && InStr(A_LoopField231, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField231, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField231, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField231), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField231, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField231, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField231, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField231, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField231 + Chr(10);
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField231;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "\\b" + keyWordAIndex + "\\d*\\b", "" + keyWordAIndex + "" + out1z);
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "\\b" + keyWordALoopField + "\\d*\\b", "" + keyWordALoopField + "" + out1z);
                                out4758686d86d86d86578991a += ALoopField + Chr(10);
                            }
                            if ((inTarget == 1 && InStr(A_LoopField231, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1)) {
                                //MsgBox, % A_LoopField
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField231 + Chr(10);
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
                let items232 = LoopParseFunc(htCode, "\n", "\r");
                for (let A_Index232 = 0; A_Index232 < items232.length + 0; A_Index232++) {
                    const A_LoopField232 = items232[A_Index232 - 0];
                    ignore = 0;
                    if (SubStr(Trim(A_LoopField232), 1, 4) == "for ") {
                        if (hold == 1 && holdText == A_LoopField232) {
                            ignore = 1;
                        } else {
                            holdText = A_LoopField232;
                            hold = 1;
                        }
                    }
                    if (!ignore) {
                        out4758686d86dgt8r754444444 += A_LoopField232 + Chr(10);
                    }
                }
                out4758686d86dgt8r754444444 = StringTrimRight(out4758686d86dgt8r754444444, 1);
                htCode = out4758686d86dgt8r754444444;
            }
            htCodeOut1234565432 = "";
            let items233 = LoopParseFunc(htCode, "\n", "\r");
            for (let A_Index233 = 0; A_Index233 < items233.length + 0; A_Index233++) {
                const A_LoopField233 = items233[A_Index233 - 0];
                out = A_LoopField233;
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
        for (let A_Index234 = 0; A_Index234 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index234++) {
            ADD_ALL_programmingBlock_HTVMsyntax += programmingBlock_HTVMsyntax[A_Index234] + Chr(10);
        }
        ADD_ALL_programmingBlock_HTVMsyntax = StringTrimRight(ADD_ALL_programmingBlock_HTVMsyntax, 1);
        ADD_ALL_programmingBlock_HTVMsyntax = compiler(ADD_ALL_programmingBlock_HTVMsyntax, allInstructionFile, "full", langToConvertToParam);
        isNotHTVMfileEXTRA_INT = 0;
        isNotHTVMfile2 = 1;
        for (let A_Index235 = 0; A_Index235 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index235++) {
            htCode = StrReplace(htCode, "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(A_Index235 + 1) + "AA", compiler(programmingBlock_HTVMsyntax[A_Index235], allInstructionFile, "full", langToConvertToParam));
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
    var fixLuaAndRubyHELP = "";
    if (langToConvertTo == langFileExtension_2) {
        if (useCurlyBraces_2 == "off" && useEnd_2 == "off") {
            htCode = indent_nested_curly_braces(htCode, 0);
        } else {
            htCode = indent_nested_curly_braces(htCode, 1);
        }
        if (useEnd_2 == "on") {
            let items236 = LoopParseFunc(htCode, "\n", "\r");
            for (let A_Index236 = 0; A_Index236 < items236.length + 0; A_Index236++) {
                const A_LoopField236 = items236[A_Index236 - 0];
                if (Trim(A_LoopField236) == keyWordCurlyBraceClose_2) {
                    fixLuaAndRuby += StrReplace(A_LoopField236, keyWordCurlyBraceClose_2, Trim(keyWordEnd_2)) + Chr(10);
                }
                else if (SubStrLastChars(A_LoopField236, 2) == " " + keyWordCurlyBraceOpen_2) {
                    fixLuaAndRuby += StringTrimRight(A_LoopField236, 2) + Chr(10);
                } else {
                    fixLuaAndRuby += A_LoopField236 + Chr(10);
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
        if (langToConvertTo == "lua" || langToConvertTo == "rb" || langToConvertTo == langFileExtension_2) {
            if (langToConvertTo == langFileExtension_2 && useEnd_2 == "on") {
                fixLuaAndRubyHELP = Trim(keyWordEnd_2);
                let items237 = LoopParseFunc(htCode, "\n", "\r");
                for (let A_Index237 = 0; A_Index237 < items237.length + 0; A_Index237++) {
                    const A_LoopField237 = items237[A_Index237 - 0];
                    if (Trim(A_LoopField237) == "}") {
                        fixLuaAndRuby += StrReplace(A_LoopField237, "}", fixLuaAndRubyHELP) + Chr(10);
                    }
                    else if (SubStrLastChars(A_LoopField237, 2) == " {") {
                        fixLuaAndRuby += StringTrimRight(A_LoopField237, 2) + Chr(10);
                    } else {
                        fixLuaAndRuby += A_LoopField237 + Chr(10);
                    }
                }
                htCode = StringTrimRight(fixLuaAndRuby, 1);
            } else {
                fixLuaAndRubyHELP = "end";
                let items238 = LoopParseFunc(htCode, "\n", "\r");
                for (let A_Index238 = 0; A_Index238 < items238.length + 0; A_Index238++) {
                    const A_LoopField238 = items238[A_Index238 - 0];
                    if (Trim(A_LoopField238) == "}") {
                        fixLuaAndRuby += StrReplace(A_LoopField238, "}", fixLuaAndRubyHELP) + Chr(10);
                    }
                    else if (SubStrLastChars(A_LoopField238, 2) == " {") {
                        fixLuaAndRuby += StringTrimRight(A_LoopField238, 2) + Chr(10);
                    } else {
                        fixLuaAndRuby += A_LoopField238 + Chr(10);
                    }
                }
                htCode = StringTrimRight(fixLuaAndRuby, 1);
            }
        }
    }
    let nextWordEndFix = [];
    var nextWordEndFixOut = "";
    if (langToConvertTo == langFileExtension_2 && useEnd_2 == "on") {
        let items239 = LoopParseFunc(htCode, "\n", "\r");
        for (let A_Index239 = 0; A_Index239 < items239.length + 0; A_Index239++) {
            const A_LoopField239 = items239[A_Index239 - 0];
            HTVM_Append(nextWordEndFix, A_LoopField239);
        }
        HTVM_Append(nextWordEndFix, " ");
        let items240 = LoopParseFunc(htCode, "\n", "\r");
        for (let A_Index240 = 0; A_Index240 < items240.length + 0; A_Index240++) {
            const A_LoopField240 = items240[A_Index240 - 0];
            if (Trim(A_LoopField240) == Trim(keyWordEnd_2) && SubStr(Trim(nextWordEndFix[A_Index240 + 1]), 1, StrLen(Trim(keyWordElseIf_2) + " ")) == Trim(keyWordElseIf_2) + " " || Trim(A_LoopField240) == Trim(keyWordEnd_2) && (Trim(nextWordEndFix[A_Index240 + 1]) == Trim(keyWordElse_2) || Trim(nextWordEndFix[A_Index240 + 1]) == Trim(keyWordElse_2 + ":"))) {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField240 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == "lua") {
        let items241 = LoopParseFunc(htCode, "\n", "\r");
        for (let A_Index241 = 0; A_Index241 < items241.length + 0; A_Index241++) {
            const A_LoopField241 = items241[A_Index241 - 0];
            HTVM_Append(nextWordEndFix, A_LoopField241);
        }
        HTVM_Append(nextWordEndFix, " ");
        let items242 = LoopParseFunc(htCode, "\n", "\r");
        for (let A_Index242 = 0; A_Index242 < items242.length + 0; A_Index242++) {
            const A_LoopField242 = items242[A_Index242 - 0];
            if (Trim(A_LoopField242) == "end" && SubStr(Trim(nextWordEndFix[A_Index242 + 1]), 1, StrLen("elseif ")) == "elseif " || Trim(A_LoopField242) == "end" && Trim(nextWordEndFix[A_Index242 + 1]) == "else") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField242 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == "rb") {
        let items243 = LoopParseFunc(htCode, "\n", "\r");
        for (let A_Index243 = 0; A_Index243 < items243.length + 0; A_Index243++) {
            const A_LoopField243 = items243[A_Index243 - 0];
            HTVM_Append(nextWordEndFix, A_LoopField243);
        }
        HTVM_Append(nextWordEndFix, " ");
        let items244 = LoopParseFunc(htCode, "\n", "\r");
        for (let A_Index244 = 0; A_Index244 < items244.length + 0; A_Index244++) {
            const A_LoopField244 = items244[A_Index244 - 0];
            if (Trim(A_LoopField244) == "end" && SubStr(Trim(nextWordEndFix[A_Index244 + 1]), 1, StrLen("elsif ")) == "elsif " || Trim(A_LoopField244) == "end" && Trim(nextWordEndFix[A_Index244 + 1]) == "else") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField244 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    let nextWordEndFixRB = [];
    nextWordEndFixOut = "";
    if (langToConvertTo == "rb") {
        let items245 = LoopParseFunc(htCode, "\n", "\r");
        for (let A_Index245 = 0; A_Index245 < items245.length + 0; A_Index245++) {
            const A_LoopField245 = items245[A_Index245 - 0];
            HTVM_Append(nextWordEndFixRB, A_LoopField245);
        }
        HTVM_Append(nextWordEndFixRB, " ");
        let items246 = LoopParseFunc(htCode, "\n", "\r");
        for (let A_Index246 = 0; A_Index246 < items246.length + 0; A_Index246++) {
            const A_LoopField246 = items246[A_Index246 - 0];
            if (Trim(A_LoopField246) == "end" && SubStr(Trim(nextWordEndFixRB[A_Index246 + 1]), 1, StrLen("rescue ")) == "rescue " || Trim(A_LoopField246) == "end" && Trim(nextWordEndFixRB[A_Index246 + 1]) == "ensure") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField246 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == langFileExtension_2 && useEnd_2 == "on") {
        let items247 = LoopParseFunc(htCode, "\n", "\r");
        for (let A_Index247 = 0; A_Index247 < items247.length + 0; A_Index247++) {
            const A_LoopField247 = items247[A_Index247 - 0];
            HTVM_Append(nextWordEndFixRB, A_LoopField247);
        }
        HTVM_Append(nextWordEndFixRB, " ");
        let items248 = LoopParseFunc(htCode, "\n", "\r");
        for (let A_Index248 = 0; A_Index248 < items248.length + 0; A_Index248++) {
            const A_LoopField248 = items248[A_Index248 - 0];
            if (Trim(A_LoopField248) == Trim(keyWordEnd_2) && SubStr(Trim(nextWordEndFixRB[A_Index248 + 1]), 1, StrLen(Trim(keyWordCatch_2) + " ")) == Trim(keyWordCatch_2) + " " || Trim(A_LoopField248) == Trim(keyWordEnd_2) && Trim(nextWordEndFixRB[A_Index248 + 1]) == Trim(keyWordFinally_2) || Trim(nextWordEndFixRB[A_Index248 + 1]) == Trim(keyWordFinally_2 + ":")) {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField248 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    nextWordEndFixOut = "";
    if (langToConvertTo == "ahk") {
        let items249 = LoopParseFunc(htCode, "\n", "\r");
        for (let A_Index249 = 0; A_Index249 < items249.length + 0; A_Index249++) {
            const A_LoopField249 = items249[A_Index249 - 0];
            if (SubStr(Trim(A_LoopField249), 1, StrLen("Loop, Parse, ")) == "Loop, Parse, ") {
                nextWordEndFixOut += StrReplace(A_LoopField249, "{", Chr(10) + "{" + Chr(10)) + Chr(10);
            } else {
                nextWordEndFixOut += A_LoopField249 + Chr(10);
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == "go") {
        let fixGoManGoIsSoAnnoyingBroooFurure = [];
        let items250 = LoopParseFunc(htCode, "\n", "\r");
        for (let A_Index250 = 0; A_Index250 < items250.length + 0; A_Index250++) {
            const A_LoopField250 = items250[A_Index250 - 0];
            HTVM_Append(fixGoManGoIsSoAnnoyingBroooFurure, A_LoopField250);
        }
        HTVM_Append(fixGoManGoIsSoAnnoyingBroooFurure, " ");
        var fixGoManGoIsSoAnnoyingBroooSkip = 0;
        var fixGoManGoIsSoAnnoyingBroooCount = 0;
        var fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
        var fixGoManGoIsSoAnnoyingBrooo = "";
        let items251 = LoopParseFunc(htCode, "\n", "\r");
        for (let A_Index251 = 0; A_Index251 < items251.length + 0; A_Index251++) {
            const A_LoopField251 = items251[A_Index251 - 0];
            if (Trim(A_LoopField251) == "}" && SubStr(Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index251 + 1]), 1, StrLen("else if ")) == "else if ") {
                fixGoManGoIsSoAnnoyingBroooSkip = 1;
                fixGoManGoIsSoAnnoyingBroooCount = 0;
                let items252 = LoopParseFunc(fixGoManGoIsSoAnnoyingBroooFurure[A_Index251 + 1]);
                for (let A_Index252 = 0; A_Index252 < items252.length + 0; A_Index252++) {
                    const A_LoopField252 = items252[A_Index252 - 0];
                    if (A_LoopField252 == " ") {
                        fixGoManGoIsSoAnnoyingBroooCount++;
                    } else {
                        break;
                    }
                }
                fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
                for (let A_Index253 = 0; A_Index253 < fixGoManGoIsSoAnnoyingBroooCount + 0; A_Index253++) {
                    fixGoManGoIsSoAnnoyingBroooCountSpaceses += " ";
                }
                fixGoManGoIsSoAnnoyingBrooo += fixGoManGoIsSoAnnoyingBroooCountSpaceses + "} " + Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index251 + 1]) + Chr(10);
            } else {
                if (fixGoManGoIsSoAnnoyingBroooSkip == 0) {
                    fixGoManGoIsSoAnnoyingBrooo += A_LoopField251 + Chr(10);
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
        for (let A_Index254 = 0; A_Index254 < COUNT_programmingBlock_InTheTranspiledLang + 0; A_Index254++) {
            htCode = StrReplace(htCode, "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(A_Index254 + 1) + "AA", programmingBlock_InTheTranspiledLang[A_Index254]);
        }
    }
    if (langToConvertTo == "cpp") {
        if (COUNT_programmingBlock_CPP != 0) {
            for (let A_Index255 = 0; A_Index255 < COUNT_programmingBlock_CPP + 0; A_Index255++) {
                htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index255 + 1) + "AA", programmingBlock_CPP[A_Index255]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CPP != 0) {
            for (let A_Index256 = 0; A_Index256 < COUNT_programmingBlock_CPP + 0; A_Index256++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index256 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCPP_2 + Chr(10) + programmingBlock_CPP[A_Index256] + Chr(10) + keyWordCodeInTheTranspiledLangEndCPP_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index256 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "py") {
        if (COUNT_programmingBlock_PY != 0) {
            for (let A_Index257 = 0; A_Index257 < COUNT_programmingBlock_PY + 0; A_Index257++) {
                htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index257 + 1) + "AA", programmingBlock_PY[A_Index257]);
            }
        }
    } else {
        if (COUNT_programmingBlock_PY != 0) {
            for (let A_Index258 = 0; A_Index258 < COUNT_programmingBlock_PY + 0; A_Index258++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index258 + 1) + "AA", keyWordCodeInTheTranspiledLangStartPY_2 + Chr(10) + programmingBlock_PY[A_Index258] + Chr(10) + keyWordCodeInTheTranspiledLangEndPY_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index258 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "js") {
        if (COUNT_programmingBlock_JS != 0) {
            for (let A_Index259 = 0; A_Index259 < COUNT_programmingBlock_JS + 0; A_Index259++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index259 + 1) + "AA", programmingBlock_JS[A_Index259]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JS != 0) {
            for (let A_Index260 = 0; A_Index260 < COUNT_programmingBlock_JS + 0; A_Index260++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index260 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJS_2 + Chr(10) + programmingBlock_JS[A_Index260] + Chr(10) + keyWordCodeInTheTranspiledLangEndJS_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index260 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "go") {
        if (COUNT_programmingBlock_GO != 0) {
            for (let A_Index261 = 0; A_Index261 < COUNT_programmingBlock_GO + 0; A_Index261++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index261 + 1) + "AA", programmingBlock_GO[A_Index261]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GO != 0) {
            for (let A_Index262 = 0; A_Index262 < COUNT_programmingBlock_GO + 0; A_Index262++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index262 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGO_2 + Chr(10) + programmingBlock_GO[A_Index262] + Chr(10) + keyWordCodeInTheTranspiledLangEndGO_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index262 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "lua") {
        if (COUNT_programmingBlock_LUA != 0) {
            for (let A_Index263 = 0; A_Index263 < COUNT_programmingBlock_LUA + 0; A_Index263++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index263 + 1) + "AA", programmingBlock_LUA[A_Index263]);
            }
        }
    } else {
        if (COUNT_programmingBlock_LUA != 0) {
            for (let A_Index264 = 0; A_Index264 < COUNT_programmingBlock_LUA + 0; A_Index264++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index264 + 1) + "AA", keyWordCodeInTheTranspiledLangStartLUA_2 + Chr(10) + programmingBlock_LUA[A_Index264] + Chr(10) + keyWordCodeInTheTranspiledLangEndLUA_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index264 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "cs") {
        if (COUNT_programmingBlock_CS != 0) {
            for (let A_Index265 = 0; A_Index265 < COUNT_programmingBlock_CS + 0; A_Index265++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index265 + 1) + "AA", programmingBlock_CS[A_Index265]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CS != 0) {
            for (let A_Index266 = 0; A_Index266 < COUNT_programmingBlock_CS + 0; A_Index266++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index266 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCS_2 + Chr(10) + programmingBlock_CS[A_Index266] + Chr(10) + keyWordCodeInTheTranspiledLangEndCS_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index266 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "java") {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (let A_Index267 = 0; A_Index267 < COUNT_programmingBlock_JAVA + 0; A_Index267++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index267 + 1) + "AA", programmingBlock_JAVA[A_Index267]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (let A_Index268 = 0; A_Index268 < COUNT_programmingBlock_JAVA + 0; A_Index268++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index268 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJAVA_2 + Chr(10) + programmingBlock_JAVA[A_Index268] + Chr(10) + keyWordCodeInTheTranspiledLangEndJAVA_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index268 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "kt") {
        if (COUNT_programmingBlock_KT != 0) {
            for (let A_Index269 = 0; A_Index269 < COUNT_programmingBlock_KT + 0; A_Index269++) {
                htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index269 + 1) + "AA", programmingBlock_KT[A_Index269]);
            }
        }
    } else {
        if (COUNT_programmingBlock_KT != 0) {
            for (let A_Index270 = 0; A_Index270 < COUNT_programmingBlock_KT + 0; A_Index270++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index270 + 1) + "AA", keyWordCodeInTheTranspiledLangStartKT_2 + Chr(10) + programmingBlock_KT[A_Index270] + Chr(10) + keyWordCodeInTheTranspiledLangEndKT_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index270 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "rb") {
        if (COUNT_programmingBlock_RB != 0) {
            for (let A_Index271 = 0; A_Index271 < COUNT_programmingBlock_RB + 0; A_Index271++) {
                htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index271 + 1) + "AA", programmingBlock_RB[A_Index271]);
            }
        }
    } else {
        if (COUNT_programmingBlock_RB != 0) {
            for (let A_Index272 = 0; A_Index272 < COUNT_programmingBlock_RB + 0; A_Index272++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index272 + 1) + "AA", keyWordCodeInTheTranspiledLangStartRB_2 + Chr(10) + programmingBlock_RB[A_Index272] + Chr(10) + keyWordCodeInTheTranspiledLangEndRB_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index272 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "nim") {
        if (COUNT_programmingBlock_NIM != 0) {
            for (let A_Index273 = 0; A_Index273 < COUNT_programmingBlock_NIM + 0; A_Index273++) {
                htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index273 + 1) + "AA", programmingBlock_NIM[A_Index273]);
            }
        }
    } else {
        if (COUNT_programmingBlock_NIM != 0) {
            for (let A_Index274 = 0; A_Index274 < COUNT_programmingBlock_NIM + 0; A_Index274++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index274 + 1) + "AA", keyWordCodeInTheTranspiledLangStartNIM_2 + Chr(10) + programmingBlock_NIM[A_Index274] + Chr(10) + keyWordCodeInTheTranspiledLangEndNIM_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index274 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "ahk") {
        if (COUNT_programmingBlock_AHK != 0) {
            for (let A_Index275 = 0; A_Index275 < COUNT_programmingBlock_AHK + 0; A_Index275++) {
                htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index275 + 1) + "AA", programmingBlock_AHK[A_Index275]);
            }
        }
    } else {
        if (COUNT_programmingBlock_AHK != 0) {
            for (let A_Index276 = 0; A_Index276 < COUNT_programmingBlock_AHK + 0; A_Index276++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index276 + 1) + "AA", keyWordCodeInTheTranspiledLangStartAHK_2 + Chr(10) + programmingBlock_AHK[A_Index276] + Chr(10) + keyWordCodeInTheTranspiledLangEndAHK_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index276 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "swift") {
        if (COUNT_programmingBlock_SWIFT != 0) {
            for (let A_Index277 = 0; A_Index277 < COUNT_programmingBlock_SWIFT + 0; A_Index277++) {
                htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index277 + 1) + "AA", programmingBlock_SWIFT[A_Index277]);
            }
        }
    } else {
        if (COUNT_programmingBlock_SWIFT != 0) {
            for (let A_Index278 = 0; A_Index278 < COUNT_programmingBlock_SWIFT + 0; A_Index278++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index278 + 1) + "AA", keyWordCodeInTheTranspiledLangStartSWIFT_2 + Chr(10) + programmingBlock_SWIFT[A_Index278] + Chr(10) + keyWordCodeInTheTranspiledLangEndSWIFT_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index278 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "dart") {
        if (COUNT_programmingBlock_DART != 0) {
            for (let A_Index279 = 0; A_Index279 < COUNT_programmingBlock_DART + 0; A_Index279++) {
                htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index279 + 1) + "AA", programmingBlock_DART[A_Index279]);
            }
        }
    } else {
        if (COUNT_programmingBlock_DART != 0) {
            for (let A_Index280 = 0; A_Index280 < COUNT_programmingBlock_DART + 0; A_Index280++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index280 + 1) + "AA", keyWordCodeInTheTranspiledLangStartDART_2 + Chr(10) + programmingBlock_DART[A_Index280] + Chr(10) + keyWordCodeInTheTranspiledLangEndDART_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index280 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "ts") {
        if (COUNT_programmingBlock_TS != 0) {
            for (let A_Index281 = 0; A_Index281 < COUNT_programmingBlock_TS + 0; A_Index281++) {
                htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index281 + 1) + "AA", programmingBlock_TS[A_Index281]);
            }
        }
    } else {
        if (COUNT_programmingBlock_TS != 0) {
            for (let A_Index282 = 0; A_Index282 < COUNT_programmingBlock_TS + 0; A_Index282++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index282 + 1) + "AA", keyWordCodeInTheTranspiledLangStartTS_2 + Chr(10) + programmingBlock_TS[A_Index282] + Chr(10) + keyWordCodeInTheTranspiledLangEndTS_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index282 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    if (langToConvertTo == "groovy") {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (let A_Index283 = 0; A_Index283 < COUNT_programmingBlock_GROOVY + 0; A_Index283++) {
                htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index283 + 1) + "AA", programmingBlock_GROOVY[A_Index283]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (let A_Index284 = 0; A_Index284 < COUNT_programmingBlock_GROOVY + 0; A_Index284++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index284 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGROOVY_2 + Chr(10) + programmingBlock_GROOVY[A_Index284] + Chr(10) + keyWordCodeInTheTranspiledLangEndGROOVY_2);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index284 + 1) + "AA", Chr(10));
                }
            }
        }
    }
    //;;;;;;;;;;
    if (langToConvertTo == langFileExtension_2) {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (let A_Index285 = 0; A_Index285 < COUNT_programmingBlock_HTVM + 0; A_Index285++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index285 + 1) + "AA", programmingBlock_HTVM[A_Index285]);
            }
        }
    } else {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (let A_Index286 = 0; A_Index286 < COUNT_programmingBlock_HTVM + 0; A_Index286++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index286 + 1) + "AA", Chr(10));
            }
        }
    }
    if (langToConvertTo != langFileExtension_2) {
        htCode = StrReplace(htCode, "wklajebawszopsne--tshecurlyybarxccsesgFORguiTHTVM0987HTVM---HTVMAAAadhksudahsdGUI_-_HTVM_OPEN-HTVM--GUI", "{");
        htCode = StrReplace(htCode, "wklajebawszopsne--tshecurlyybarxccsesgFORguiTHTVM0987HTVM---HTVMAAAadhksudahsdGUI_-_HTVM_CLOSE-HTVM--GUI", "}");
        for (let A_Index287 = 0; A_Index287 < theIdNumOfThe34 + 0; A_Index287++) {
            if (theIdNumOfThe34 == A_Index287 + 1) {
                if (langToConvertTo == langFileExtension_2) {
                    if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                        htCode = StrReplace(htCode, "fihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index287 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(fString(theIdNumOfThe34theVar[A_Index287 + 1]), "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                    } else {
                        htCode = StrReplace(htCode, "fihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index287 + 1) + Chr(65) + Chr(65), StrReplace(fString(theIdNumOfThe34theVar[A_Index287 + 1]), keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                    }
                } else {
                    htCode = StrReplace(htCode, "fihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index287 + 1) + Chr(65) + Chr(65), StrReplace(fString(theIdNumOfThe34theVar[A_Index287 + 1]), keyWordEscpaeChar, "\\") + Chr(34));
                }
            } else {
                if (langToConvertTo == langFileExtension_2) {
                    if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                        htCode = StrReplace(htCode, "fihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index287 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(fString(theIdNumOfThe34theVar[A_Index287 + 1]), "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2));
                    } else {
                        htCode = StrReplace(htCode, "fihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index287 + 1) + Chr(65) + Chr(65), StrReplace(fString(theIdNumOfThe34theVar[A_Index287 + 1]), keyWordEscpaeChar, keyWordEscpaeChar_2));
                    }
                } else {
                    htCode = StrReplace(htCode, "fihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index287 + 1) + Chr(65) + Chr(65), StrReplace(fString(theIdNumOfThe34theVar[A_Index287 + 1]), keyWordEscpaeChar, "\\"));
                }
            }
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    for (let A_Index288 = 0; A_Index288 < HTVM_Size(commentsBugFix) + 0; A_Index288++) {
        htCode = StrReplace(htCode, "HTVM--cnavisdofbuvsesdivdidufg79wregwewaeosd8ges7dfdftuawdiHTVMv2yerheyziberlasduci6syiq--AA" + STR(A_Index288) + "AA", commentsBugFix[A_Index288]);
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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
    let items289 = LoopParseFunc(instructions, "\n", "\r");
    for (let A_Index289 = 0; A_Index289 < items289.length + 0; A_Index289++) {
        const A_LoopField289 = items289[A_Index289 - 0];
        if (Trim(A_LoopField289) == "funcEND======================funcEND==============") {
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
                funcLangHolder = StringTrimLeft(A_LoopField289, 5);
                if (Trim(funcLangHolder) == langToConvertTo) {
                    HTVM_Append(allFuncLang, Trim(funcLangHolder));
                    correctLang = 1;
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 2) {
                // name of the func
                funcNameHolder = StringTrimLeft(A_LoopField289, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    HTVM_Append(allFuncNames, Trim(funcNameHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 3) {
                // all libs
                funcLibsHolder = StringTrimLeft(A_LoopField289, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    HTVM_Append(allFuncLibs, Trim(funcLibsHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 4) {
                // func description
                funcDescriptionHolder = StringTrimLeft(A_LoopField289, 12);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    HTVM_Append(allfuncDescription, Trim(funcDescriptionHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum >= 5) {
                // the full func
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    funcFuncHolder += A_LoopField289 + Chr(10);
                }
            }
            //MsgBox, % A_LoopField
            areWeInAFuncFromInstructionsLineNum++;
        }
        if (Trim(A_LoopField289) == "func======================func==============") {
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
        for (let A_Index290 = 0; A_Index290 < HTVM_Size(allFuncNames) + 0; A_Index290++) {
            if (InStr(htCode, allFuncNames[A_Index290]) + "(") {
                //MsgBox, % allFuncNames[A_Index]
                allFuncsToPutAtTop += allFuncs[A_Index290] + Chr(10);
                if (Trim(allFuncLibs[A_Index290]) != "null") {
                    allLibsToPutAtTop += allFuncLibs[A_Index290] + "|";
                }
            }
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTop, 1);
        var allLibsToPutAtTopTEMP = "";
        let items291 = LoopParseFunc(allLibsToPutAtTop, "|");
        for (let A_Index291 = 0; A_Index291 < items291.length + 0; A_Index291++) {
            const A_LoopField291 = items291[A_Index291 - 0];
            allLibsToPutAtTopTEMP += A_LoopField291 + Chr(10);
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTopTEMP, 1);
        includeLibsInCppIf = 1;
        if (langToConvertTo == "cpp") {
            allLibsToPutAtTop = "#include <iostream>" + Chr(10) + "#include <sstream>" + Chr(10) + "#include <string>" + Chr(10) + "#include <cstdint>" + Chr(10) + "#include <algorithm>" + Chr(10) + "#include <vector>" + Chr(10) + "#include <any>" + Chr(10) + "#include <optional>" + Chr(10) + allLibsToPutAtTop;
        }
        if (langToConvertTo == "cs") {
            allLibsToPutAtTop = "using System;" + Chr(10) + "using System.Collections.Generic;" + Chr(10) + allLibsToPutAtTop;
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
                        htCode = Chr(10) + allFuncsToPutAtTop + Chr(10) + htCode;
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
    if (langToConvertTo != langFileExtension_2) {
        for (let A_Index292 = 0; A_Index292 < HTVM_Size(ospDic1) + 0; A_Index292++) {
            str00 = ospDic1[A_Index292];
            if (langToConvertTo == "rb") {
                if (SubStr(Trim(htCode), 1, 1) != "$") {
                    htCode = StrReplace(htCode, StrReplace(str00, "_", "_") + "_", "$" + str00 + "_");
                }
            }
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    HTVM_Append(ospDic, "end");
    var size_ospDic = HTVM_Size(ospDic);
    if (size_ospDic != 0) {
        for (let A_Index293 = 0; A_Index293 < size_ospDic + 0; A_Index293++) {
            HTVM_Pop(ospDic);
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    HTVM_Append(ospDic1, "end");
    var size_ospDic1 = HTVM_Size(ospDic1);
    if (size_ospDic1 != 0) {
        for (let A_Index294 = 0; A_Index294 < size_ospDic1 + 0; A_Index294++) {
            HTVM_Pop(ospDic1);
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    HTVM_Append(ospDic2, "end");
    var size_ospDic2 = HTVM_Size(ospDic2);
    if (size_ospDic2 != 0) {
        for (let A_Index295 = 0; A_Index295 < size_ospDic2 + 0; A_Index295++) {
            HTVM_Pop(ospDic2);
        }
    }
    availableFuncsInHTVMInHTVM = "";
    saveAllArrayVarNamesSoWeCanDoAfix = "";
    if (langToConvertTo == "rb") {
        htCode = FixRubyGlobalVars(htCode);
    }
    htCode = StrReplace(htCode, "optanal-HTVM-opt-parmsNOtWorking-theirewIs-a-bug-Iusfbudfbuoeshfuisbav=-fwaegs-awedsf-dd-sfgc ", "");
    if (langToConvertTo == "rb") {
        htCode = StrReplace(htCode, "$$", "$");
        htCode = StrReplace(htCode, "$$", "$");
        htCode = StrReplace(htCode, "$$", "$");
    }
    if (langToConvertTo == "java") {
        htCode = StrReplace(htCode, "= [);", "= new ArrayList<>();");
    }
    for (let A_Index296 = 0; A_Index296 < theIdNumOfThe34 + 0; A_Index296++) {
        if (theIdNumOfThe34 == A_Index296 + 1) {
            if (langToConvertTo == langFileExtension_2) {
                if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index296 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index296 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                } else {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index296 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index296 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                }
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index296 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index296 + 1], keyWordEscpaeChar, "\\") + Chr(34));
            }
        } else {
            if (langToConvertTo == langFileExtension_2) {
                if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index296 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index296 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2));
                } else {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index296 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index296 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2));
                }
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asds" + str21 + "as--" + str21 + "theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index296 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index296 + 1], keyWordEscpaeChar, "\\"));
            }
        }
    }
    if (langToConvertTo == langFileExtension_2) {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, keyWordEscpaeChar_2 + Chr(34));
    } else {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, Chr(92) + Chr(34));
    }
    htCode = StrReplace(htCode, "std::string(" + Chr(34) + Chr(34) + ";),", "std::string(" + Chr(34) + Chr(34) + "),");
    var jsHTMLupCode = "<!doctype html>" + Chr(10) + "<html lang=" + Chr(34) + "en" + Chr(34) + ">" + Chr(10) + "    <head>\n        <meta charset=" + Chr(34) + "UTF-8" + Chr(34) + " />" + Chr(10) + "        <meta name=" + Chr(34) + "viewport" + Chr(34) + " content=" + Chr(34) + "width=device-width, initial-scale=1.0" + Chr(34) + " />" + Chr(10) + "        <title>HTVM</title>" + Chr(10) + "        <style>" + Chr(10) + "            body {" + Chr(10) + "                background-color: #202020;" + Chr(10) + "                font-family:" + Chr(10) + "                    " + Chr(34) + "Open Sans" + Chr(34) + "," + Chr(10) + "                    -apple-system," + Chr(10) + "                    BlinkMacSystemFont," + Chr(10) + "                    " + Chr(34) + "Segoe UI" + Chr(34) + "," + Chr(10) + "                    Roboto," + Chr(10) + "                    Oxygen-Sans," + Chr(10) + "                    Ubuntu," + Chr(10) + "                    Cantarell," + Chr(10) + "                    " + Chr(34) + "Helvetica Neue" + Chr(34) + "," + Chr(10) + "                    Helvetica," + Chr(10) + "                    Arial," + Chr(10) + "                    sans-serif;" + Chr(10) + "            }" + Chr(10) + "        </style>" + Chr(10) + allLibsToPutAtTop + Chr(10) + "</head>" + Chr(10) + "    <body>" + Chr(10) + "<script>";
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
            for (let A_Index297 = 0; A_Index297 < HTVM_Size(weAreInMLSarr) + 0; A_Index297++) {
                htCode = StrReplace(htCode, "aejsoydoxubviycbdgsut7eoy-ihsxbvhowadesdio6376e7wuwyuau--szd--AA" + STR(A_Index297) + "AA", weAreInMLSarr[A_Index297]);
            }
            if (SubStr(htCode, 1, 1) == Chr(10)) {
                htCode = StringTrimLeft(htCode, 1);
            }
        }
    }
    HTVM_Append(weAreInMLSarr, "end");
    var size_weAreInMLSarr = HTVM_Size(weAreInMLSarr);
    if (size_weAreInMLSarr != 0) {
        for (let A_Index298 = 0; A_Index298 < size_weAreInMLSarr + 0; A_Index298++) {
            HTVM_Pop(weAreInMLSarr);
        }
    }
    if (initializeBackendAndGUIInteractionWithLabelSubroutineLikeButConvertsToFunction_WAS_IN_PYTHON == 1) {
        htCode = htCode + Chr(10) + Chr(10) + "if __name__ == " + Chr(34) + "__main__" + Chr(34) + ":" + Chr(10) + "    # --- Cleaned up startup messages ---" + Chr(10) + "    # print(f" + Chr(34) + "--- Flask Routes ---" + Chr(34) + ") # REMOVED" + Chr(10) + "    # print(app.url_map) # REMOVED" + Chr(10) + "    # print(f" + Chr(34) + "--------------------" + Chr(34) + ") # REMOVED" + Chr(10) + "    # print(f" + Chr(34) + "Starting server on http://0.0.0.0:{HTVM_server_port_HTVM}" + Chr(34) + ") # REMOVED" + Chr(10) + "    " + Chr(10) + "    # KEEP This specific message:" + Chr(10) + "    print(f" + Chr(34) + "Root '/' will attempt to serve './{HTVM_DEFAULT_FILE_HTVM}' as configured." + Chr(34) + ")" + Chr(10) + "    " + Chr(10) + "    # print(" + Chr(34) + "Endpoints /hello and /goodbye (POST) expect PLAIN TEXT input and return PLAIN TEXT." + Chr(34) + ") # REMOVED" + Chr(10) + "" + Chr(10) + "    # Standard app run" + Chr(10) + "    app.run(host=" + Chr(34) + "0.0.0.0" + Chr(34) + ", port=HTVM_server_port_HTVM, debug=True)";
    }
    initializeBackendAndGUIInteractionWithLabelSubroutineLikeButConvertsToFunction_WAS_IN_PYTHON = 0;
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
    let items299 = LoopParseFunc(str0);
    for (let A_Index299 = 0; A_Index299 < items299.length + 0; A_Index299++) {
        const A_LoopField299 = items299[A_Index299 - 0];
        str00 = Trim(A_LoopField299);
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
        let items300 = LoopParseFunc(allArgs, "\n", "\r");
        for (let A_Index300 = 0; A_Index300 < items300.length + 0; A_Index300++) {
            const A_LoopField300 = items300[A_Index300 - 0];
            if (A_Index300 == 0) {
                numOfParams++;
                argCODE = FileRead(Trim(A_LoopField300));
                argCODEfile = Trim(A_LoopField300);
            }
            else if (A_Index300 == 1) {
                numOfParams++;
                argHTVMinstr = Trim(A_LoopField300);
            }
            else if (A_Index300 == 2) {
                numOfParams++;
                argLangTo = Trim(A_LoopField300);
            } else {
                numOfParams++;
                HTVM_Append(argHTVMinstrMORE, Trim(A_LoopField300));
            }
        }
        //print("===============123431234===========start=====")
        for (let A_Index301 = 0; A_Index301 < HTVM_Size(argHTVMinstrMORE) + 0; A_Index301++) {
            //print(argHTVMinstrMORE[A_Index])
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