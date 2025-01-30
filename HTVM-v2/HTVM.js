

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
var out_KeyWordsCommands = "";
var outTrimCode = "";
var htCode = "";
var outVarOperator = "";
var lineDone = 0;
var areWeInAFuncFromInstructions = 0;
var areWeInAFuncFromInstructionsLineNum = 0;
var theTryCatchVarForErrors = "jhku-dfsds-ds-d-ffdsf-sdfsfdsedsf";
var theJSvarDeclaredVarsBugFix = "|";
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
async function KeyWordsCommands(theCodeCommands, mode, keyWordsCommands, langToConvertTo) {
    var theCodeCommands = StrReplace(theCodeCommands, "%", "");
    if (mode == "check") {
        items1 = LoopParseFunc(keyWordsCommands, "|")
        for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
            const A_LoopField1 = items1[A_Index1 - 0];
            items2 = LoopParseFunc(A_LoopField1, ",")
            for (let A_Index2 = 0; A_Index2 < items2.length + 0; A_Index2++) {
                const A_LoopField2 = items2[A_Index2 - 0];
                if (A_Index2 == 0) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField2 + ", ")) == StrLower(A_LoopField2 + ", ")) {
                        //MsgBox, true
                        return "true";
                    }
                }
                if (A_Index2 == 0) {
                    if (theCodeCommands == A_LoopField2) {
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
        items3 = LoopParseFunc(keyWordsCommands, "|")
        for (let A_Index3 = 0; A_Index3 < items3.length + 0; A_Index3++) {
            const A_LoopField3 = items3[A_Index3 - 0];
            AIndex = A_Index3;
            items4 = LoopParseFunc(A_LoopField3, ",")
            for (let A_Index4 = 0; A_Index4 < items4.length + 0; A_Index4++) {
                const A_LoopField4 = items4[A_Index4 - 0];
                if (A_Index4 == 0) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField4 + ", ")) == StrLower(A_LoopField4 + ", ")) {
                        //MsgBox, true
                        keyWordsCommandsNumLine = AIndex;
                        break;
                    }
                }
                if (A_Index4 == 0) {
                    //MsgBox, %theCodeCommands% = %A_LoopField4%
                    if (theCodeCommands == A_LoopField4) {
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
        items5 = LoopParseFunc(theCodeCommands, ",")
        for (let A_Index5 = 0; A_Index5 < items5.length + 0; A_Index5++) {
            const A_LoopField5 = items5[A_Index5 - 0];
            theCodeCommand.push(Trim(A_LoopField5));
            //MsgBox, % A_LoopField5
        }
        items6 = LoopParseFunc(keyWordsCommands, "|")
        for (let A_Index6 = 0; A_Index6 < items6.length + 0; A_Index6++) {
            const A_LoopField6 = items6[A_Index6 - 0];
            if (keyWordsCommandsNumLine == A_Index6) {
                //MsgBox, % A_LoopField6
                items7 = LoopParseFunc(A_LoopField6, ",")
                for (let A_Index7 = 0; A_Index7 < items7.length + 0; A_Index7++) {
                    const A_LoopField7 = items7[A_Index7 - 0];
                    if (A_Index7 == 0) {
                        outConstuctTheOutFromTheCommandsFucnName = A_LoopField7;
                    }
                    else if (A_Index7 == 1) {
                        //MsgBox, % A_LoopField7
                        if (A_LoopField7 == "lineTranspile") {
                            outConstuctTheOutFromTheCommandsLineTranspile = 1;
                        }
                        if (A_LoopField7 == "OUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField7 == "INOUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField7 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField7, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    }
                    else if (A_Index7 == 2) {
                        if (outConstuctTheOutFromTheCommandsLineTranspile == 1) {
                            outConstuctTheOutFromTheCommandsLineTranspileText = A_LoopField7;
                        }
                        if (A_LoopField7 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField7, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    } else {
                        //MsgBox, % theCodeCommand[theCodeCommandNum]
                        if (InStr(A_LoopField7, Chr(39))) {
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
async function HTVMmatchStrRrplace(line, matchString, replaceString) {
    var lineOut = "";
    if (!InStr(line, matchString)) {
        return line;
    }
    var allDelimiters = " ()[].,;:'!&|=<>+-*/^%~" + Chr(34) + Chr(9) + Chr(11);
    let lineArr = [];
    items8 = LoopParseFunc(line)
    for (let A_Index8 = 0; A_Index8 < items8.length + 0; A_Index8++) {
        const A_LoopField8 = items8[A_Index8 - 0];
        lineArr.push(A_LoopField8);
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
    for (let A_Index9 = 0; A_Index9 < lineArr.length + 0; A_Index9++) {
        char1 = "";
        char2 = "";
        char3 = "";
        char4 = "";
        isMatch = 0;
        if (A_Index9 != 0) {
            isStart = 0;
        }
        sildingLine = "";
        for (let A_Index10 = 0; A_Index10 < matchStringLEN + 0; A_Index10++) {
            if (A_Index10 + i1 <= lineArr.length - 1) {
                sildingLine += lineArr[A_Index10 + i1];
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
            if (i1 + matchStringLEN < lineArr.length) {
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
            if (allPosForReplacing.length > 0) {
                for (let A_Index11 = 0; A_Index11 < allPosForReplacing.length + 0; A_Index11++) {
                    if (i1 + 1 != allPosForReplacing[A_Index11]) {
                        allPosForReplacing.push(i1 + 1);
                        break;
                    }
                }
            } else {
                allPosForReplacing.push(i1 + 1);
            }
        }
        i1++;
    }
    var lineTEMP = "";
    lineOut = line;
    //print(allPosForReplacing)
    if (allPosForReplacing.length > 0) {
        // matchStringLEN
        // replaceStringLEN
        var l2 = 0;
        var currentPos = 0;
        var onceEnd = 0;
        for (let A_Index12 = 0; A_Index12 < allPosForReplacing.length + 0; A_Index12++) {
            if (A_Index12 == 0) {
                currentPos = allPosForReplacing[A_Index12];
            } else {
                currentPos = allPosForReplacing[A_Index12] - (matchStringLEN - replaceStringLEN);
            }
            onceEnd = 0;
            items13 = LoopParseFunc(lineOut)
            for (let A_Index13 = 0; A_Index13 < items13.length + 0; A_Index13++) {
                const A_LoopField13 = items13[A_Index13 - 0];
                if (A_Index13 + 2 > currentPos && A_Index13 + 1 < currentPos + matchStringLEN) {
                    onceEnd++;
                    //print("DDDDDDDDDDD" . STR(A_Index13))
                    if (onceEnd == 1) {
                        lineTEMP += replaceString;
                    }
                } else {
                    lineTEMP += A_LoopField13;
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
async function SubStrLastChars(text, numOfChars) {
    var LastOut = "";
    var NumOfChars = 0;
    items14 = LoopParseFunc(text)
    for (let A_Index14 = 0; A_Index14 < items14.length + 0; A_Index14++) {
        const A_LoopField14 = items14[A_Index14 - 0];
        NumOfChars++;
    }
    for (let A_Index15 = 0; A_Index15 < numOfChars + 0; A_Index15++) {
        NumOfChars--;
    }
    items16 = LoopParseFunc(text)
    for (let A_Index16 = 0; A_Index16 < items16.length + 0; A_Index16++) {
        const A_LoopField16 = items16[A_Index16 - 0];
        if (A_Index16 >= NumOfChars) {
            LastOut += A_LoopField16;
        }
    }
    return LastOut;
}
async function ExtractDigits(inputString) {
    var digits = "";
    items17 = LoopParseFunc(inputString)
    for (let A_Index17 = 0; A_Index17 < items17.length + 0; A_Index17++) {
        const A_LoopField17 = items17[A_Index17 - 0];
        if (RegExMatch(A_LoopField17, "\\d")) {
            digits += A_LoopField17;
        }
    }
    return digits;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Helper function to create spaces
async function spaces(n) {
    var s = "";
    if (n != 0) {
        for (let A_Index18 = 0; A_Index18 < n + 0; A_Index18++) {
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
    items19 = LoopParseFunc(string123)
    for (let A_Index19 = 0; A_Index19 < items19.length + 0; A_Index19++) {
        const A_LoopField19 = items19[A_Index19 - 0];
        // Check if the current character is a space
        if (A_LoopField19 == Chr(32)) {
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
    items20 = LoopParseFunc(input)
    for (let A_Index20 = 0; A_Index20 < items20.length + 0; A_Index20++) {
        const A_LoopField20 = items20[A_Index20 - 0];
        if (A_LoopField20 != " " || foundNonSpace) {
            result += A_LoopField20;
            foundNonSpace = true;
        }
    }
    return result;
}
async function getLastChar(strippedString) {
    var lastChar;
    items21 = LoopParseFunc(strippedString)
    for (let A_Index21 = 0; A_Index21 < items21.length + 0; A_Index21++) {
        const A_LoopField21 = items21[A_Index21 - 0];
        lastChar = A_LoopField21;
    }
    return lastChar;
}
async function AddCurlyBraces(pythonCode) {
    var pythonCode = StrReplace(pythonCode, Chr(9), "    ");
    var result = "";
    var indentLevel = 0;
    var indent = 0;
    var line = "";
    var stripped = "";
    items22 = LoopParseFunc(pythonCode, "\n", "\r")
    for (let A_Index22 = 0; A_Index22 < items22.length + 0; A_Index22++) {
        const A_LoopField22 = items22[A_Index22 - 0];
        line = A_LoopField22;
        stripped = Trim(line);
        if (stripped == "") {
            result += line + "\n";
            continue;
        }
        // Count leading spaces
        indent = StrLen(line) - StrLen(LTrim(line));
        // Close braces for unindents
        for (let A_Index23 = 0; ; A_Index23++) {
            if (indentLevel <= indent) {
                break;
            }
            indentLevel -= 4;
            result += spaces(indentLevel) + "}\n";
        }
        // Add opening brace for new blocks
        if (getLastChar(stripped) == ":" && SubStr(StrLower(Trim(A_LoopField22)), 1, StrLen(StrLower(keyWordComment))) != StrLower(keyWordComment)) {
            result += SubStr(line, 1, -1) + " {\n";
            indentLevel += 4;
        } else {
            result += line + "\n";
        }
    }
    // Close any remaining open braces
    for (let A_Index24 = 0; ; A_Index24++) {
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
    for (let A_Index25 = 0; A_Index25 < count + 0; A_Index25++) {
        spaces += Chr(32);
    }
    return spaces;
}
async function indent_nested_curly_braces(input_string, modeCurlyBracesOn) {
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
    items26 = LoopParseFunc(input_string, "\n", "\r")
    for (let A_Index26 = 0; A_Index26 < items26.length + 0; A_Index26++) {
        const A_LoopField26 = items26[A_Index26 - 0];
        trimmed_line = Trim(A_LoopField26);
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
        var resultOut = "";
        items27 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index27 = 0; A_Index27 < items27.length + 0; A_Index27++) {
            const A_LoopField27 = items27[A_Index27 - 0];
            if (Trim(A_LoopField27) != "{" && Trim(A_LoopField27) != "}") {
                resultOut += A_LoopField27 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
    } else {
        // format curly braces in a K&R style
        let lookIntoFurture = [];
        items28 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index28 = 0; A_Index28 < items28.length + 0; A_Index28++) {
            const A_LoopField28 = items28[A_Index28 - 0];
            lookIntoFurture.push(Trim(A_LoopField28));
        }
        lookIntoFurture.push(" ");
        var resultOut = "";
        var skipNext = 0;
        items29 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index29 = 0; A_Index29 < items29.length + 0; A_Index29++) {
            const A_LoopField29 = items29[A_Index29 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (Trim(lookIntoFurture[A_Index29 + 1]) == "{") {
                resultOut += A_LoopField29 + " " + culyOpenFix + "\n";
                skipNext = 2;
            }
            if (skipNext == 0) {
                resultOut += A_LoopField29 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
        let lookIntoFurture2 = [];
        items30 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index30 = 0; A_Index30 < items30.length + 0; A_Index30++) {
            const A_LoopField30 = items30[A_Index30 - 0];
            lookIntoFurture2.push(Trim(A_LoopField30));
        }
        lookIntoFurture2.push(" ");
        resultOut = "";
        skipNext = 0;
        var addSpacesAtTheBegginig;
        items31 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index31 = 0; A_Index31 < items31.length + 0; A_Index31++) {
            const A_LoopField31 = items31[A_Index31 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (langToConvertTo != "lua" && langToConvertTo != "rb" && langToConvertTo != langFileExtension_2) {
                if (Trim(A_LoopField31) == "}" && Trim(lookIntoFurture2[A_Index31 + 1]) == "else {") {
                    skipNext = 2;
                    addSpacesAtTheBegginig = "";
                    items32 = LoopParseFunc(A_LoopField31)
                    for (let A_Index32 = 0; A_Index32 < items32.length + 0; A_Index32++) {
                        const A_LoopField32 = items32[A_Index32 - 0];
                        if (A_LoopField32 == " ") {
                            if (A_LoopField32 != " ") {
                                break;
                            }
                            addSpacesAtTheBegginig += StrReplace(A_LoopField32, "}", culyCloseFix);
                        }
                    }
                    resultOut += addSpacesAtTheBegginig + culyCloseFix + " else " + culyOpenFix + "\n";
                }
            }
            if (skipNext == 0) {
                resultOut += A_LoopField31 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
    }
    resultOut = "";
    var ALoopField;
    items33 = LoopParseFunc(result, "\n", "\r")
    for (let A_Index33 = 0; A_Index33 < items33.length + 0; A_Index33++) {
        const A_LoopField33 = items33[A_Index33 - 0];
        if (CheckOddLeadingSpaces(A_LoopField33) == "1") {
            ALoopField = StringTrimLeft(A_LoopField33, 1);
            resultOut += ALoopField + "\n";
        } else {
            resultOut += A_LoopField33 + "\n";
        }
    }
    result = StringTrimRight(resultOut, 1);
    var fixResultFIX = "";
    if (langToConvertTo == langFileExtension_2 && modeCurlyBracesOn == 1) {
        items34 = LoopParseFunc(result, "\n", "\r")
        for (let A_Index34 = 0; A_Index34 < items34.length + 0; A_Index34++) {
            const A_LoopField34 = items34[A_Index34 - 0];
            if (Trim(A_LoopField34) == "}") {
                fixResultFIX += StrReplace(A_LoopField34, "}", culyCloseFix) + "\n";
            } else {
                fixResultFIX += A_LoopField34 + "\n";
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
async function findTypeOfOSPprop(fullARRAYstr, FromPath) {
    var outType = "";
    // if the fullARRAYstr is in this format
    // path.path.path:propName1[str],propName2[bool],propName3[str array]|path.path.path:propName1[str],propName2[bool],propName3[str array]
    var outFormat = "";
    var outFormatHELP1 = "";
    var outFormatHELP2 = "";
    items35 = LoopParseFunc(fullARRAYstr, "|")
    for (let A_Index35 = 0; A_Index35 < items35.length + 0; A_Index35++) {
        const A_LoopField35 = items35[A_Index35 - 0];
        if (Trim(A_LoopField35) != "") {
            outFormatHELP1 = StrSplit(A_LoopField35, ":", 1);
            outFormatHELP2 = StrSplit(A_LoopField35, ":", 2);
            items36 = LoopParseFunc(outFormatHELP2, ",")
            for (let A_Index36 = 0; A_Index36 < items36.length + 0; A_Index36++) {
                const A_LoopField36 = items36[A_Index36 - 0];
                outFormat += outFormatHELP1 + "." + A_LoopField36 + "|";
            }
        }
    }
    outFormat = StringTrimRight(outFormat, 1);
    items37 = LoopParseFunc(outFormat, "|")
    for (let A_Index37 = 0; A_Index37 < items37.length + 0; A_Index37++) {
        const A_LoopField37 = items37[A_Index37 - 0];
        if (Trim(A_LoopField37) != "") {
            if (StrSplit(Trim(A_LoopField37), "[", 1) == Trim(FromPath)) {
                outType = StrSplit(Trim(A_LoopField37), "[", 2);
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
async function REMOVELastSTRfromDOT(THESTR) {
    var THESTRout = "";
    if (Trim(THESTR) == "") {
        return "";
    }
    var count12345 = 0;
    items38 = LoopParseFunc(THESTR, ".")
    for (let A_Index38 = 0; A_Index38 < items38.length + 0; A_Index38++) {
        const A_LoopField38 = items38[A_Index38 - 0];
        count12345++;
    }
    items39 = LoopParseFunc(THESTR, ".")
    for (let A_Index39 = 0; A_Index39 < items39.length + 0; A_Index39++) {
        const A_LoopField39 = items39[A_Index39 - 0];
        if (count12345 == A_Index39) {
            break;
        } else {
            THESTRout += Trim(A_LoopField39) + ".";
        }
    }
    THESTRout = StringTrimRight(THESTRout, 1);
    return THESTRout;
}
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
async function replaceTheOSPpathsPY_JS(theSTR123, ALoopFieldIN) {
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
        var theSTR123 = StrReplace(theSTR123, Trim(ALoopField), "OSPHTVMOSP_" + StrReplace(ALoopField1, ".", "_"));
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
async function replaceTheOSPpathsLEFT(theSTR123, ALoopFieldIN) {
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
async function replaceTheOSPpathsRIGHT(theSTR123, ALoopFieldIN) {
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
async function CheckStringPosition(text, target, reference) {
    var posReference = SubStr(text, 1, StrLen(reference));
    var posTarget = SubStr(text, 1, StrLen(target));
    // Check if both strings are found (not using InStr)
    if (posReference != "" && posTarget != "") {
        // Manually find the positions of the target and reference
        posTarget = RegExMatch(text, target);
        posReference = RegExMatch(text, reference);
        // Compare positions of target and reference
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
async function getIndexOfTheStrArrayStrOST(ALoopField, theSringOSPlineARRAYstrstrSTR) {
    items40 = LoopParseFunc(theSringOSPlineARRAYstrstrSTR, "|")
    for (let A_Index40 = 0; A_Index40 < items40.length + 0; A_Index40++) {
        const A_LoopField40 = items40[A_Index40 - 0];
        if (Trim(StrSplit(A_LoopField40, ":", 1)) == Trim(ALoopField)) {
            return STR(A_Index40);
        }
    }
    return "0";
}
async function parserOSPgloabl(theSringOSPline, str123) {
    var str_1 = "";
    var str_2 = "";
    var str_3 = "";
    var str_4 = "";
    var str_5 = "";
    var str_6 = "";
    var HELPHoldOSPdethodNamePath = "";
    items41 = LoopParseFunc(theSringOSPline, "|")
    for (let A_Index41 = 0; A_Index41 < items41.length + 0; A_Index41++) {
        const A_LoopField41 = items41[A_Index41 - 0];
        str_1 += Trim(StrSplit(A_LoopField41, ":", 1)) + "\n";
        str_5 = Trim(StrSplit(A_LoopField41, ":", 1));
        str_6 = Trim(StrSplit(A_LoopField41, ":", 2));
        items42 = LoopParseFunc(str_6, ",")
        for (let A_Index42 = 0; A_Index42 < items42.length + 0; A_Index42++) {
            const A_LoopField42 = items42[A_Index42 - 0];
            str_1 += str_5 + "." + Trim(StrSplit(A_LoopField42, "[", 1)) + "[" + STR(A_Index42) + "]\n";
        }
    }
    str_1 += StrReplace(HELPHoldOSPdethodNamePath, "|", "\n");
    var shortestLine = "";
    var currentLine = "";
    var currentLength = 0;
    var minLength = 0;
    var tempStr = "";
    // Sorting by repeatedly finding and appending the shortest line
    for (let A_Index43 = 0; ; A_Index43++) {
        // Initialize variables to track the shortest line in this pass
        shortestLine = "";
        minLength = 999999;
        // Find the shortest line in str_1
        items44 = LoopParseFunc(str_1, "\n", "\r")
        for (let A_Index44 = 0; A_Index44 < items44.length + 0; A_Index44++) {
            const A_LoopField44 = items44[A_Index44 - 0];
            currentLine = A_LoopField44;
            currentLength = StrLen(currentLine);
            if (currentLength < minLength) {
                minLength = currentLength;
                shortestLine = currentLine;
            }
        }
        // If no shortest line is found, break (str_1 is empty)
        if (shortestLine == "") {
            break;
        }
        // Add the shortest line to the sorted result
        str_2 += shortestLine + "\n";
        // Rebuild str_1 without the shortest line
        tempStr = "";
        items45 = LoopParseFunc(str_1, "\n", "\r")
        for (let A_Index45 = 0; A_Index45 < items45.length + 0; A_Index45++) {
            const A_LoopField45 = items45[A_Index45 - 0];
            if (A_LoopField45 != shortestLine) {
                tempStr += A_LoopField45 + "\n";
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
    items46 = LoopParseFunc(str_2, "\n", "\r")
    for (let A_Index46 = 0; A_Index46 < items46.length + 0; A_Index46++) {
        const A_LoopField46 = items46[A_Index46 - 0];
        lineCount++;
    }
    // Reverse the order by re-parsing and appending lines in reverse order
    for (let A_Index47 = 0; A_Index47 < lineCount + 0; A_Index47++) {
        // Inner loop to find the (lineCount - A_Index47 + 1)-th line
        index = lineCount - A_Index47 + 1;
        currentLine = "";
        lineNum = 0;
        items48 = LoopParseFunc(str_2, "\n", "\r")
        for (let A_Index48 = 0; A_Index48 < items48.length + 0; A_Index48++) {
            const A_LoopField48 = items48[A_Index48 - 0];
            lineNum++;
            if (lineNum == index) {
                currentLine = A_LoopField48;
                break;
            }
        }
        // Append the line in reverse order
        reversedStr += currentLine + "\n";
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
    items49 = LoopParseFunc(str_2, "\n", "\r")
    for (let A_Index49 = 0; A_Index49 < items49.length + 0; A_Index49++) {
        const A_LoopField49 = items49[A_Index49 - 0];
        if (SubStr(A_LoopField49, 1, StrLen(keyWordFunc)) != keyWordFunc) {
            if (langToConvertTo == "cpp") {
                if (Trim(A_LoopField49) != "") {
                    if (InStr(str123, " += ")) {
                        str6 = " += ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
                        str5 = str3 + str6 + str4;
                        var str123 = Trim(str5);
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    } else {
                        str123 = replaceTheOSPpathsRIGHT(str123, A_LoopField49);
                    }
                    //;;;;
                }
            } else {
                if (Trim(A_LoopField49) != "") {
                    str123 = replaceTheOSPpathsPY_JS(str123, A_LoopField49);
                }
            }
        }
    }
    return str123;
}
async function isLineAconstruct(line) {
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
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc)) {
        return true;
    }
    return false;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
async function fixDoubleQuotes(line, isLast) {
    var out = "";
    if (isLast == 0) {
        out = StrReplace(line, Chr(92) + Chr(92) + Chr(34), Chr(92) + Chr(34));
    } else {
        line = StringTrimRight(line, 1);
        out = StrReplace(line, Chr(92) + Chr(92) + Chr(34), Chr(92) + Chr(34)) + Chr(34);
    }
    return out;
}
async function fixArray1234(line) {
    var out = "";
    var started = 0;
    items50 = LoopParseFunc(line)
    for (let A_Index50 = 0; A_Index50 < items50.length + 0; A_Index50++) {
        const A_LoopField50 = items50[A_Index50 - 0];
        if (started == 1) {
            if (StrLen(line) == A_Index50 + 1) {
                return out;
            }
            out += A_LoopField50;
        }
        if (A_LoopField50 == "(") {
            started = 1;
        }
    }
    return out;
}
async function fixArray123(line, arrayMethodStr, mode) {
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
    if (langToConvertTo != "swift") {
        if (mode == 1) {
            return "HTVM_Append(" + StrSplit(line, ".", 1) + ", " + await fixArray1234(line) + ")";
        }
        if (mode == 2) {
            return "HTVM_Pop(" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 3) {
            return "HTVM_Size(" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 4) {
            return "HTVM_Insert(" + StrSplit(line, ".", 1) + ", " + await fixArray1234(line) + ")";
        }
        if (mode == 5) {
            return "HTVM_Remove(" + StrSplit(line, ".", 1) + ", " + await fixArray1234(line) + ")";
        }
        if (mode == 6) {
            return "HTVM_IndexOf(" + StrSplit(line, ".", 1) + ", " + await fixArray1234(line) + ")";
        }
    } else {
        if (mode == 1) {
            return "HTVM_Append(&" + StrSplit(line, ".", 1) + ", " + await fixArray1234(line) + ")";
        }
        if (mode == 2) {
            return "HTVM_Pop(&" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 3) {
            return "HTVM_Size(" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 4) {
            return "HTVM_Insert(&" + StrSplit(line, ".", 1) + ", " + await fixArray1234(line) + ")";
        }
        if (mode == 5) {
            return "HTVM_Remove(&" + StrSplit(line, ".", 1) + ", " + await fixArray1234(line) + ")";
        }
        if (mode == 6) {
            return "HTVM_IndexOf(" + StrSplit(line, ".", 1) + ", " + await fixArray1234(line) + ")";
        }
    }
    return line;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
async function arrayParserTranspiler1(line, arrayMethodStr, mode) {
    if (InStr(line, arrayMethodStr) == false) {
        return line;
    }
    var out = "";
    var allDelimiters = " ()[],;:'!&|=<>+-*/^%~" + Chr(34) + Chr(9) + Chr(11);
    let arrAll = [];
    items51 = LoopParseFunc(line)
    for (let A_Index51 = 0; A_Index51 < items51.length + 0; A_Index51++) {
        const A_LoopField51 = items51[A_Index51 - 0];
        arrAll.push(A_LoopField51);
    }
    var i1 = 0;
    var tempHold = "";
    var holdPos = 0;
    let holdPositions = [];
    for (let A_Index52 = 0; A_Index52 < arrAll.length + 0; A_Index52++) {
        tempHold = "";
        if (arrAll.length - StrLen(arrayMethodStr) + 1 == i1) {
            break;
        }
        for (let A_Index53 = 0; A_Index53 < StrLen(arrayMethodStr) + 0; A_Index53++) {
            tempHold += arrAll[A_Index53 + i1];
        }
        i1++;
        //print(tempHold)
        if (tempHold == arrayMethodStr) {
            holdPos = i1;
            //print(holdPos)
            holdPositions.push(holdPos);
        }
    }
    //print("===========================================")
    var holdPositionsTEMP = 0;
    for (let A_Index54 = 0; A_Index54 < holdPositions.length + 0; A_Index54++) {
        holdPositionsTEMP = holdPositions[A_Index54];
        i1 = arrAll.length;
        tempHold = "";
        for (let A_Index55 = 0; A_Index55 < arrAll.length + 0; A_Index55++) {
            if (holdPositionsTEMP >= i1 + 1) {
                if (InStr(allDelimiters, arrAll[i1]) == false) {
                    tempHold += arrAll[i1 - 1];
                } else {
                    break;
                }
            }
            i1--;
        }
        //print(await StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", ""))))
        holdPositions[A_Index54] = holdPositions[A_Index54] - StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", "")));
    }
    //;;;;;;;;;;;;;;;;;;
    var foundFirstParenthesis = 0;
    var ParenthesisStackOPEN = 0;
    var ParenthesisStackCLOSE = 0;
    let holdPositionsEnd = [];
    holdPositionsTEMP = 0;
    for (let A_Index56 = 0; A_Index56 < holdPositions.length + 0; A_Index56++) {
        holdPositionsTEMP = holdPositions[A_Index56];
        i1 = 0;
        tempHold = "";
        foundFirstParenthesis = 0;
        ParenthesisStackOPEN = 0;
        ParenthesisStackCLOSE = 0;
        for (let A_Index57 = 0; A_Index57 < arrAll.length + 0; A_Index57++) {
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
                    holdPositionsEnd.push(i1 + 1);
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
    for (let A_Index58 = 0; A_Index58 < holdPositions.length + 0; A_Index58++) {
        startPosReplace = holdPositions[holdPositions.length - A_Index58 - 1];
        endPosReplace = holdPositionsEnd[holdPositions.length - A_Index58 - 1];
        holdDebug = "";
        beenInside = 0;
        holdDebugLen = 0;
        canOut = 1;
        items59 = LoopParseFunc(line)
        for (let A_Index59 = 0; A_Index59 < items59.length + 0; A_Index59++) {
            const A_LoopField59 = items59[A_Index59 - 0];
            if (A_Index59 + 1 >= startPosReplace && A_Index59 + 1 <= endPosReplace) {
                holdDebug += A_LoopField59;
            }
        }
        holdDebugLen = StrLen(holdDebug);
        items60 = LoopParseFunc(line)
        for (let A_Index60 = 0; A_Index60 < items60.length + 0; A_Index60++) {
            const A_LoopField60 = items60[A_Index60 - 0];
            if (A_Index60 + 1 >= startPosReplace && A_Index60 + 1 <= endPosReplace) {
                beenInside++;
            }
            if (beenInside == 1) {
                out += await fixArray123(holdDebug, arrayMethodStr, mode);
                canOut = 0;
            } else {
                if (canOut == 0) {
                    holdDebugLen--;
                    if (holdDebugLen == 0) {
                        canOut = 1;
                    }
                }
                if (canOut == 1) {
                    out += A_LoopField60;
                }
            }
        }
        //print("|" . holdDebug . "|")
        line = out;
        out = "";
    }
    return line;
}
async function arrayParserTranspiler(line) {
    // mode 1 = Append
    // mode 2 = Pop
    // mode 3 = Size
    // mode 4 = Insert
    // mode 5 = Remove
    // mode 6 = IndexOf
    if (langToConvertTo == langFileExtension_2) {
        line = await HTVMmatchStrRrplace(line, "." + keyWordArrayAppend + "(", "." + keyWordArrayAppend_2 + "(");
        line = await HTVMmatchStrRrplace(line, "." + keyWordArrayPop + "(", "." + keyWordArrayPop_2 + "(");
        line = await HTVMmatchStrRrplace(line, "." + keyWordArraySize + "(", "." + keyWordArraySize_2 + "(");
        line = await HTVMmatchStrRrplace(line, "." + keyWordArrayInsert + "(", "." + keyWordArrayInsert_2 + "(");
        line = await HTVMmatchStrRrplace(line, "." + keyWordArrayRemove + "(", "." + keyWordArrayRemove_2 + "(");
        line = await HTVMmatchStrRrplace(line, "." + keyWordArrayIndexOf + "(", "." + keyWordArrayIndexOf_2 + "(");
    } else {
        line = await arrayParserTranspiler1(line, keyWordArrayAppend + "(", 1);
        line = await arrayParserTranspiler1(line, keyWordArrayPop + "(", 2);
        line = await arrayParserTranspiler1(line, keyWordArraySize + "(", 3);
        line = await arrayParserTranspiler1(line, keyWordArrayInsert + "(", 4);
        line = await arrayParserTranspiler1(line, keyWordArrayRemove + "(", 5);
        line = await arrayParserTranspiler1(line, keyWordArrayIndexOf + "(", 6);
    }
    return line;
}
async function getFuncTypeConvert(type) {
    var theType = "";
    type = Trim(type);
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
            theType = "std::vector<void>";
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
            theType = "List<float>";
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
            theType = "ArrayList<Float>";
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
            theType = "Array<String>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "Array<Int>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "Array<String>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "Array<Float>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "Array<Boolean>";
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
            theType = "[String]";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "[Int]";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "[String]";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "[Float]";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "[Bool]";
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
            theType = "int";
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
async function getTheLastWord(line) {
    if (InStr(Trim(line), " ") == false) {
        return line;
    }
    var outNum = 0;
    items61 = LoopParseFunc(line, " ")
    for (let A_Index61 = 0; A_Index61 < items61.length + 0; A_Index61++) {
        const A_LoopField61 = items61[A_Index61 - 0];
        outNum++;
    }
    items62 = LoopParseFunc(line, " ")
    for (let A_Index62 = 0; A_Index62 < items62.length + 0; A_Index62++) {
        const A_LoopField62 = items62[A_Index62 - 0];
        if (outNum == A_Index62 + 1) {
            return A_LoopField62;
        }
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
async function  GETfullLangAllOperators() {
    let fullLangAllOperators = [];
    if (langToConvertTo == "cpp") {
        fullLangAllOperators.push("nullptr");
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("&&");
        fullLangAllOperators.push("||");
        fullLangAllOperators.push("!");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("|");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("~");
        fullLangAllOperators.push("<<");
        fullLangAllOperators.push(">>");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == "py") {
        fullLangAllOperators.push("None");
        fullLangAllOperators.push("True");
        fullLangAllOperators.push("False");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("**");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("is");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("and");
        fullLangAllOperators.push("or");
        fullLangAllOperators.push("not");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("|");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("~");
        fullLangAllOperators.push("<<");
        fullLangAllOperators.push(">>");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == "js") {
        fullLangAllOperators.push("null");
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("**");
        if (useJavaScriptAlwaysTripleEqual == "on") {
            fullLangAllOperators.push("===");
        } else {
            fullLangAllOperators.push("==");
        }
        fullLangAllOperators.push("===");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("&&");
        fullLangAllOperators.push("||");
        fullLangAllOperators.push("!");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("|");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("~");
        fullLangAllOperators.push("<<");
        fullLangAllOperators.push(">>");
        fullLangAllOperators.push(">>>");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == "go") {
        fullLangAllOperators.push("nil");
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("&&");
        fullLangAllOperators.push("||");
        fullLangAllOperators.push("!");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("|");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("<<");
        fullLangAllOperators.push(">>");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR");
    }
    if (langToConvertTo == "lua") {
        fullLangAllOperators.push("nil");
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push("..");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("~=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("and");
        fullLangAllOperators.push("or");
        fullLangAllOperators.push("not");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("|");
        fullLangAllOperators.push("~");
        fullLangAllOperators.push("~");
        fullLangAllOperators.push("<<");
        fullLangAllOperators.push(">>");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == "cs") {
        fullLangAllOperators.push("null");
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("&&");
        fullLangAllOperators.push("||");
        fullLangAllOperators.push("!");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("|");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("~");
        fullLangAllOperators.push("<<");
        fullLangAllOperators.push(">>");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == "java") {
        fullLangAllOperators.push("null");
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("&&");
        fullLangAllOperators.push("||");
        fullLangAllOperators.push("!");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("|");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("~");
        fullLangAllOperators.push("<<");
        fullLangAllOperators.push(">>");
        fullLangAllOperators.push(">>>");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == "kt") {
        fullLangAllOperators.push("null");
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("===");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("&&");
        fullLangAllOperators.push("||");
        fullLangAllOperators.push("!");
        fullLangAllOperators.push("and");
        fullLangAllOperators.push("or");
        fullLangAllOperators.push("xor");
        fullLangAllOperators.push("inv");
        fullLangAllOperators.push("shl");
        fullLangAllOperators.push("shr");
        fullLangAllOperators.push("ushr");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == "rb") {
        fullLangAllOperators.push("nil");
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("**");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("&&");
        fullLangAllOperators.push("||");
        fullLangAllOperators.push("!");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("|");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("~");
        fullLangAllOperators.push("<<");
        fullLangAllOperators.push(">>");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == "nim") {
        fullLangAllOperators.push("nil");
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("and");
        fullLangAllOperators.push("or");
        fullLangAllOperators.push("not");
        fullLangAllOperators.push("and");
        fullLangAllOperators.push("or");
        fullLangAllOperators.push("xor");
        fullLangAllOperators.push("not");
        fullLangAllOperators.push("shl");
        fullLangAllOperators.push("shr");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == "ahk") {
        fullLangAllOperators.push(Chr(34) + "" + Chr(34));
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push(".");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("=");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("&&");
        fullLangAllOperators.push("||");
        fullLangAllOperators.push("!");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("|");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("~");
        fullLangAllOperators.push("<<");
        fullLangAllOperators.push(">>");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == "swift") {
        fullLangAllOperators.push("nil");
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("===");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("&&");
        fullLangAllOperators.push("||");
        fullLangAllOperators.push("!");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("|");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("~");
        fullLangAllOperators.push("<<");
        fullLangAllOperators.push(">>");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == "dart") {
        fullLangAllOperators.push("null");
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("===");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("&&");
        fullLangAllOperators.push("||");
        fullLangAllOperators.push("!");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("|");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("~");
        fullLangAllOperators.push("<<");
        fullLangAllOperators.push(">>");
        fullLangAllOperators.push(">>>");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == "ts") {
        fullLangAllOperators.push("null");
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("**");
        if (useJavaScriptAlwaysTripleEqual == "on") {
            fullLangAllOperators.push("===");
        } else {
            fullLangAllOperators.push("==");
        }
        fullLangAllOperators.push("===");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("&&");
        fullLangAllOperators.push("||");
        fullLangAllOperators.push("!");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("|");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("~");
        fullLangAllOperators.push("<<");
        fullLangAllOperators.push(">>");
        fullLangAllOperators.push(">>>");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == "groovy") {
        fullLangAllOperators.push("null");
        fullLangAllOperators.push("true");
        fullLangAllOperators.push("false");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("+");
        fullLangAllOperators.push("-");
        fullLangAllOperators.push("*");
        fullLangAllOperators.push("/");
        fullLangAllOperators.push("%");
        fullLangAllOperators.push("**");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("==");
        fullLangAllOperators.push("!=");
        fullLangAllOperators.push(">");
        fullLangAllOperators.push("<");
        fullLangAllOperators.push(">=");
        fullLangAllOperators.push("<=");
        fullLangAllOperators.push("&&");
        fullLangAllOperators.push("||");
        fullLangAllOperators.push("!");
        fullLangAllOperators.push("&");
        fullLangAllOperators.push("|");
        fullLangAllOperators.push("^");
        fullLangAllOperators.push("~");
        fullLangAllOperators.push("<<");
        fullLangAllOperators.push(">>");
        fullLangAllOperators.push(">>>");
        fullLangAllOperators.push("?");
        fullLangAllOperators.push(":");
    }
    if (langToConvertTo == langFileExtension_2) {
        fullLangAllOperators.push(keyWordNull_2);
        fullLangAllOperators.push(keyWordTrue_2);
        fullLangAllOperators.push(keyWordFalse_2);
        fullLangAllOperators.push(keyWordConcat_2);
        fullLangAllOperators.push(keyWordAdd_2);
        fullLangAllOperators.push(keyWordSub_2);
        fullLangAllOperators.push(keyWordMul_2);
        fullLangAllOperators.push(keyWordDiv_2);
        fullLangAllOperators.push(keyWordMod_2);
        fullLangAllOperators.push(keyWordExp_2);
        fullLangAllOperators.push(keyWordEqual_2);
        fullLangAllOperators.push(keyWordStrictEqual_2);
        fullLangAllOperators.push(keyWordNotEqual_2);
        fullLangAllOperators.push(keyWordGreater_2);
        fullLangAllOperators.push(keyWordLess_2);
        fullLangAllOperators.push(keyWordGreaterEqual_2);
        fullLangAllOperators.push(keyWordLessEqual_2);
        fullLangAllOperators.push(keyWordAnd_2);
        fullLangAllOperators.push(keyWordOr_2);
        fullLangAllOperators.push(keyWordNot_2);
        fullLangAllOperators.push(keyWordBitAnd_2);
        fullLangAllOperators.push(keyWordBitOr_2);
        fullLangAllOperators.push(keyWordBitXor_2);
        fullLangAllOperators.push(keyWordBitNot_2);
        fullLangAllOperators.push(keyWordShiftLeft_2);
        fullLangAllOperators.push(keyWordShiftRight_2);
        fullLangAllOperators.push(keyWordShiftUnsignedRight_2);
        fullLangAllOperators.push(keyWordTernary1_2);
        fullLangAllOperators.push(keyWordTernary2_2);
    }
    return fullLangAllOperators;
}
async function  GETfullLangAllOperators_HELP() {
    let fullLangAllOperators_HELP = [];
    fullLangAllOperators_HELP.push(keyWordNull);
    fullLangAllOperators_HELP.push(keyWordTrue);
    fullLangAllOperators_HELP.push(keyWordFalse);
    fullLangAllOperators_HELP.push(keyWordConcat);
    fullLangAllOperators_HELP.push(keyWordAdd);
    fullLangAllOperators_HELP.push(keyWordSub);
    fullLangAllOperators_HELP.push(keyWordMul);
    fullLangAllOperators_HELP.push(keyWordDiv);
    fullLangAllOperators_HELP.push(keyWordMod);
    fullLangAllOperators_HELP.push(keyWordExp);
    fullLangAllOperators_HELP.push(keyWordEqual);
    fullLangAllOperators_HELP.push(keyWordStrictEqual);
    fullLangAllOperators_HELP.push(keyWordNotEqual);
    fullLangAllOperators_HELP.push(keyWordGreater);
    fullLangAllOperators_HELP.push(keyWordLess);
    fullLangAllOperators_HELP.push(keyWordGreaterEqual);
    fullLangAllOperators_HELP.push(keyWordLessEqual);
    fullLangAllOperators_HELP.push(keyWordAnd);
    fullLangAllOperators_HELP.push(keyWordOr);
    fullLangAllOperators_HELP.push(keyWordNot);
    fullLangAllOperators_HELP.push(keyWordBitAnd);
    fullLangAllOperators_HELP.push(keyWordBitOr);
    fullLangAllOperators_HELP.push(keyWordBitXor);
    fullLangAllOperators_HELP.push(keyWordBitNot);
    fullLangAllOperators_HELP.push(keyWordShiftLeft);
    fullLangAllOperators_HELP.push(keyWordShiftRight);
    fullLangAllOperators_HELP.push(keyWordShiftUnsignedRight);
    fullLangAllOperators_HELP.push(keyWordTernary1);
    fullLangAllOperators_HELP.push(keyWordTernary2);
    return fullLangAllOperators_HELP;
}
async function expressionParserTranspiler(expression) {
    var fixExpertionLineFuncOnlyTEXT_func = "";
    var fixExpertionLineFuncOnlyTEXT_numDelete = 0;
    if (fixExpertionLineFuncOnly == 1) {
        fixExpertionLineFuncOnlyTEXT_func = StrSplit(expression, "(", 1);
        fixExpertionLineFuncOnlyTEXT_numDelete = StrLen(fixExpertionLineFuncOnlyTEXT_func) + 1;
        var expression = StringTrimLeft(expression, fixExpertionLineFuncOnlyTEXT_numDelete);
    }
    if (langToConvertTo != "js" && langToConvertTo != "ts" && langToConvertTo != langFileExtension_2) {
        expression = RegExReplace(expression, "\\b" + keyWordAwait + "\\b", "");
    }
    for (let A_Index63 = 0; A_Index63 < 29 + 0; A_Index63++) {
        if (InStr(expression, fullLangAllOperators_HELP[A_Index63])) {
            if (A_Index63 == 0 || A_Index63 == 1 || A_Index63 == 2) {
                expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index63] + "\\b", fullLangAllOperators[A_Index63]);
            } else {
                if (A_Index63 == 19) {
                    if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index63] + "\\b", "not");
                    } else {
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index63] + "\\b", "!");
                    }
                    if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
                        expression = RegExReplace(expression, "!([\\w]+)", "not $1");
                    }
                    expression = StrReplace(expression, " not= ", " != ");
                } else {
                    expression = StrReplace(expression, " " + fullLangAllOperators_HELP[A_Index63] + " ", " " + fullLangAllOperators[A_Index63] + " ");
                    if (A_Index63 == 28) {
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
    // extra for array methods
    expression = await arrayParserTranspiler(expression);
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
    if (fixExpertionLineFuncOnly == 1) {
        expression = fixExpertionLineFuncOnlyTEXT_func + "(" + expression;
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
async function compiler(htCode, allInstructionFile, mode, langToConvertToParam = "") {
    var instructions = allInstructionFile;
    items64 = LoopParseFunc(allInstructionFile, "\n", "\r")
    for (let A_Index64 = 0; A_Index64 < items64.length + 0; A_Index64++) {
        const A_LoopField64 = items64[A_Index64 - 0];
        if (A_Index64 == 0) {
            langToConvertTo = Trim(A_LoopField64);
        }
        if (A_Index64 == 1) {
            langFileExtension = Trim(A_LoopField64);
        }
        if (A_Index64 == 2) {
            commands = Trim(A_LoopField64);
        }
        if (A_Index64 == 3) {
            keyWordAlliance = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 4) {
            keyWordCrew = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 5) {
            keyWordMethod = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 6) {
            keyWordDefObj = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 7) {
            keyWordPorp = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 8) {
            keyWordThis = Trim(A_LoopField64);
        }
        if (A_Index64 == 9) {
            keyWordInclude = Trim(A_LoopField64);
        }
        if (A_Index64 == 10) {
            keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField64);
        }
        if (A_Index64 == 11) {
            keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField64);
        }
        if (A_Index64 == 12) {
            keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField64);
        }
        if (A_Index64 == 13) {
            keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField64);
        }
        if (A_Index64 == 14) {
            keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField64);
        }
        if (A_Index64 == 15) {
            keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField64);
        }
        if (A_Index64 == 16) {
            keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField64);
        }
        if (A_Index64 == 17) {
            keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField64);
        }
        if (A_Index64 == 18) {
            keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField64);
        }
        if (A_Index64 == 19) {
            keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField64);
        }
        if (A_Index64 == 20) {
            keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField64);
        }
        if (A_Index64 == 21) {
            keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField64);
        }
        if (A_Index64 == 22) {
            keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField64);
        }
        if (A_Index64 == 23) {
            keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField64);
        }
        if (A_Index64 == 24) {
            keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField64);
        }
        if (A_Index64 == 25) {
            keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField64);
        }
        if (A_Index64 == 26) {
            keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField64);
        }
        if (A_Index64 == 27) {
            keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField64);
        }
        if (A_Index64 == 28) {
            keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField64);
        }
        if (A_Index64 == 29) {
            keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField64);
        }
        if (A_Index64 == 30) {
            keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField64);
        }
        if (A_Index64 == 31) {
            keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField64);
        }
        if (A_Index64 == 32) {
            keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField64);
        }
        if (A_Index64 == 33) {
            keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField64);
        }
        if (A_Index64 == 34) {
            keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField64);
        }
        if (A_Index64 == 35) {
            keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField64);
        }
        if (A_Index64 == 36) {
            keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField64);
        }
        if (A_Index64 == 37) {
            keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField64);
        }
        if (A_Index64 == 38) {
            keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField64);
        }
        if (A_Index64 == 39) {
            keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField64);
        }
        if (A_Index64 == 40) {
            keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField64);
        }
        if (A_Index64 == 41) {
            keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField64);
        }
        if (A_Index64 == 42) {
            keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField64);
        }
        if (A_Index64 == 43) {
            keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField64);
        }
        if (A_Index64 == 44) {
            keyWordCodeInHTVMstart = Trim(A_LoopField64);
        }
        if (A_Index64 == 45) {
            keyWordCodeInHTVMend = Trim(A_LoopField64);
        }
        if (A_Index64 == 46) {
            keyWordCurlyBraceOpen = Trim(A_LoopField64);
        }
        if (A_Index64 == 47) {
            keyWordCurlyBraceClose = Trim(A_LoopField64);
        }
        if (A_Index64 == 48) {
            keyWordNull = Trim(A_LoopField64);
        }
        if (A_Index64 == 49) {
            keyWordTrue = Trim(A_LoopField64);
        }
        if (A_Index64 == 50) {
            keyWordFalse = Trim(A_LoopField64);
        }
        if (A_Index64 == 51) {
            keyWordVoid = Trim(A_LoopField64);
        }
        if (A_Index64 == 52) {
            keyWordDouble = Trim(A_LoopField64);
        }
        if (A_Index64 == 53) {
            keyWordChar = Trim(A_LoopField64);
        }
        if (A_Index64 == 54) {
            keyWordUint8 = Trim(A_LoopField64);
        }
        if (A_Index64 == 55) {
            keyWordUint16 = Trim(A_LoopField64);
        }
        if (A_Index64 == 56) {
            keyWordUint32 = Trim(A_LoopField64);
        }
        if (A_Index64 == 57) {
            keyWordUint64 = Trim(A_LoopField64);
        }
        if (A_Index64 == 58) {
            keyWordINT = Trim(A_LoopField64);
        }
        if (A_Index64 == 59) {
            keyWordSTR = Trim(A_LoopField64);
        }
        if (A_Index64 == 60) {
            keyWordBOOL = Trim(A_LoopField64);
        }
        if (A_Index64 == 61) {
            keyWordFLOAT = Trim(A_LoopField64);
        }
        if (A_Index64 == 62) {
            keyWordINT8 = Trim(A_LoopField64);
        }
        if (A_Index64 == 63) {
            keyWordINT16 = Trim(A_LoopField64);
        }
        if (A_Index64 == 64) {
            keyWordINT32 = Trim(A_LoopField64);
        }
        if (A_Index64 == 65) {
            keyWordINT64 = Trim(A_LoopField64);
        }
        if (A_Index64 == 66) {
            keyWordIF = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 67) {
            keyWordElseIf = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 68) {
            keyWordElse = Trim(A_LoopField64);
        }
        if (A_Index64 == 69) {
            keyWordWhileLoop = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 70) {
            keyWordLoopInfinite = Trim(A_LoopField64);
        }
        if (A_Index64 == 71) {
            keyWordLoop = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 72) {
            keyWordLoopParse = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 73) {
            keyWordContinue = Trim(A_LoopField64);
        }
        if (A_Index64 == 74) {
            keyWordBreak = Trim(A_LoopField64);
        }
        if (A_Index64 == 75) {
            keyWordFunc = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 76) {
            keyWordAwait = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 77) {
            keyWordAsync = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 78) {
            keyWordThrow = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 79) {
            keyWordErrorMsg = Trim(A_LoopField64);
        }
        if (A_Index64 == 80) {
            keyWordTry = Trim(A_LoopField64);
        }
        if (A_Index64 == 81) {
            keyWordCatch = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 82) {
            keyWordFinally = Trim(A_LoopField64);
        }
        if (A_Index64 == 83) {
            keyWordReturnStatement = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 84) {
            keyWordArrayAppend = Trim(A_LoopField64);
        }
        if (A_Index64 == 85) {
            keyWordArrayPop = Trim(A_LoopField64);
        }
        if (A_Index64 == 86) {
            keyWordArraySize = Trim(A_LoopField64);
        }
        if (A_Index64 == 87) {
            keyWordArrayInsert = Trim(A_LoopField64);
        }
        if (A_Index64 == 88) {
            keyWordArrayRemove = Trim(A_LoopField64);
        }
        if (A_Index64 == 89) {
            keyWordArrayIndexOf = Trim(A_LoopField64);
        }
        if (A_Index64 == 90) {
            keyWordArrayDefinition = Trim(A_LoopField64);
        }
        if (A_Index64 == 91) {
            keyWordArrayOfIntegersDefinition = Trim(A_LoopField64);
        }
        if (A_Index64 == 92) {
            keyWordArrayOfStringsDefinition = Trim(A_LoopField64);
        }
        if (A_Index64 == 93) {
            keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField64);
        }
        if (A_Index64 == 94) {
            keyWordArrayOfBooleansDefinition = Trim(A_LoopField64);
        }
        if (A_Index64 == 95) {
            keyWordVar = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 96) {
            keyWordLet = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 97) {
            keyWordConst = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 98) {
            keyWordEnd = Trim(A_LoopField64);
        }
        if (A_Index64 == 99) {
            keyWordGlobal = Trim(A_LoopField64) + " ";
        }
        if (A_Index64 == 100) {
            keyWordComment = Trim(A_LoopField64);
        }
        if (A_Index64 == 101) {
            keyWordCommentOpenMultiLine = Trim(A_LoopField64);
        }
        if (A_Index64 == 102) {
            keyWordCommentCloseMultiLine = Trim(A_LoopField64);
        }
        if (A_Index64 == 103) {
            keyWordEscpaeChar = Trim(A_LoopField64);
        }
        if (A_Index64 == 104) {
            keyWordMainLabel = Trim(A_LoopField64);
        }
        if (A_Index64 == 105) {
            keyWordConcat = Trim(A_LoopField64);
        }
        if (A_Index64 == 106) {
            keyWordAdd = Trim(A_LoopField64);
        }
        if (A_Index64 == 107) {
            keyWordSub = Trim(A_LoopField64);
        }
        if (A_Index64 == 108) {
            keyWordMul = Trim(A_LoopField64);
        }
        if (A_Index64 == 109) {
            keyWordDiv = Trim(A_LoopField64);
        }
        if (A_Index64 == 110) {
            keyWordMod = Trim(A_LoopField64);
        }
        if (A_Index64 == 111) {
            keyWordExp = Trim(A_LoopField64);
        }
        if (A_Index64 == 112) {
            keyWordEqual = Trim(A_LoopField64);
        }
        if (A_Index64 == 113) {
            keyWordStrictEqual = Trim(A_LoopField64);
        }
        if (A_Index64 == 114) {
            keyWordNotEqual = Trim(A_LoopField64);
        }
        if (A_Index64 == 115) {
            keyWordGreater = Trim(A_LoopField64);
        }
        if (A_Index64 == 116) {
            keyWordLess = Trim(A_LoopField64);
        }
        if (A_Index64 == 117) {
            keyWordGreaterEqual = Trim(A_LoopField64);
        }
        if (A_Index64 == 118) {
            keyWordLessEqual = Trim(A_LoopField64);
        }
        if (A_Index64 == 119) {
            keyWordAnd = Trim(A_LoopField64);
        }
        if (A_Index64 == 120) {
            keyWordOr = Trim(A_LoopField64);
        }
        if (A_Index64 == 121) {
            keyWordNot = Trim(A_LoopField64);
        }
        if (A_Index64 == 122) {
            keyWordBitAnd = Trim(A_LoopField64);
        }
        if (A_Index64 == 123) {
            keyWordBitOr = Trim(A_LoopField64);
        }
        if (A_Index64 == 124) {
            keyWordBitXor = Trim(A_LoopField64);
        }
        if (A_Index64 == 125) {
            keyWordBitNot = Trim(A_LoopField64);
        }
        if (A_Index64 == 126) {
            keyWordShiftLeft = Trim(A_LoopField64);
        }
        if (A_Index64 == 127) {
            keyWordShiftRight = Trim(A_LoopField64);
        }
        if (A_Index64 == 128) {
            keyWordShiftUnsignedRight = Trim(A_LoopField64);
        }
        if (A_Index64 == 129) {
            keyWordAssign = Trim(A_LoopField64);
        }
        if (A_Index64 == 130) {
            keyWordAssignAdd = Trim(A_LoopField64);
        }
        if (A_Index64 == 131) {
            keyWordAssignConcat = Trim(A_LoopField64);
        }
        if (A_Index64 == 132) {
            keyWordAssignSub = Trim(A_LoopField64);
        }
        if (A_Index64 == 133) {
            keyWordAssignMul = Trim(A_LoopField64);
        }
        if (A_Index64 == 134) {
            keyWordAssignDiv = Trim(A_LoopField64);
        }
        if (A_Index64 == 135) {
            keyWordAssignMod = Trim(A_LoopField64);
        }
        if (A_Index64 == 136) {
            keyWordAssignShiftLeft = Trim(A_LoopField64);
        }
        if (A_Index64 == 137) {
            keyWordAssignShiftRight = Trim(A_LoopField64);
        }
        if (A_Index64 == 138) {
            keyWordLogicalAssignShiftRight = Trim(A_LoopField64);
        }
        if (A_Index64 == 139) {
            keyWordAssignBitAnd = Trim(A_LoopField64);
        }
        if (A_Index64 == 140) {
            keyWordAssignBitOr = Trim(A_LoopField64);
        }
        if (A_Index64 == 141) {
            keyWordAssignBitXor = Trim(A_LoopField64);
        }
        if (A_Index64 == 142) {
            keyWordTernary1 = Trim(A_LoopField64);
        }
        if (A_Index64 == 143) {
            keyWordTernary2 = Trim(A_LoopField64);
        }
        if (A_Index64 == 144) {
            keyWordInc = Trim(A_LoopField64);
        }
        if (A_Index64 == 145) {
            keyWordDec = Trim(A_LoopField64);
        }
        if (A_Index64 == 146) {
            AHKlikeLoopsIndexedAt = Trim(A_LoopField64);
        }
        if (A_Index64 == 147) {
            keyWordAIndex = Trim(A_LoopField64);
        }
        if (A_Index64 == 148) {
            keyWordALoopField = Trim(A_LoopField64);
        }
        if (A_Index64 == 149) {
            useCurlyBraces = Trim(A_LoopField64);
        }
        if (A_Index64 == 150) {
            useEnd = Trim(A_LoopField64);
        }
        if (A_Index64 == 151) {
            useSemicolon = Trim(A_LoopField64);
        }
        if (A_Index64 == 152) {
            useParentheses = Trim(A_LoopField64);
        }
        if (A_Index64 == 153) {
            usePrefixTypeForTypeDefinition = Trim(A_LoopField64);
        }
        if (A_Index64 == 154) {
            usePostfixTypeForTypeDefinition = Trim(A_LoopField64);
        }
        if (A_Index64 == 155) {
            usePythonicColonSyntax = Trim(A_LoopField64);
        }
        if (A_Index64 == 156) {
            useCurlyBracesSyntaxForArrayDef = Trim(A_LoopField64);
        }
        if (A_Index64 == 157) {
            useInJavaScriptAlwaysUseVar = Trim(A_LoopField64);
        }
        if (A_Index64 == 158) {
            useJavaScriptInAfullHTMLfile = Trim(A_LoopField64);
        }
        if (A_Index64 == 159) {
            useJavaScriptAmainFuncDef = Trim(A_LoopField64);
        }
        if (A_Index64 == 160) {
            useJavaScriptAllFuncsAreAsync = Trim(A_LoopField64);
        }
        if (A_Index64 == 161) {
            useJavaScriptAlwaysTripleEqual = Trim(A_LoopField64);
        }
    }
    if (argHTVMinstrMORE.length > 0) {
        var allInstructionFile_2 = Trim(FileRead(Trim(argHTVMinstrMORE[0])));
        items65 = LoopParseFunc(allInstructionFile_2, "\n", "\r")
        for (let A_Index65 = 0; A_Index65 < items65.length + 0; A_Index65++) {
            const A_LoopField65 = items65[A_Index65 - 0];
            if (A_Index65 == 0) {
                langToConvertTo_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 1) {
                langFileExtension_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 2) {
                commands_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 3) {
                keyWordAlliance_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 4) {
                keyWordCrew_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 5) {
                keyWordMethod_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 6) {
                keyWordDefObj_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 7) {
                keyWordPorp_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 8) {
                keyWordThis_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 9) {
                keyWordInclude_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 10) {
                keyWordCodeInTheTranspiledLangStart_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 11) {
                keyWordCodeInTheTranspiledLangEnd_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 12) {
                keyWordCodeInTheTranspiledLangStartCPP_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 13) {
                keyWordCodeInTheTranspiledLangEndCPP_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 14) {
                keyWordCodeInTheTranspiledLangStartPY_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 15) {
                keyWordCodeInTheTranspiledLangEndPY_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 16) {
                keyWordCodeInTheTranspiledLangStartJS_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 17) {
                keyWordCodeInTheTranspiledLangEndJS_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 18) {
                keyWordCodeInTheTranspiledLangStartGO_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 19) {
                keyWordCodeInTheTranspiledLangEndGO_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 20) {
                keyWordCodeInTheTranspiledLangStartLUA_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 21) {
                keyWordCodeInTheTranspiledLangEndLUA_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 22) {
                keyWordCodeInTheTranspiledLangStartCS_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 23) {
                keyWordCodeInTheTranspiledLangEndCS_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 24) {
                keyWordCodeInTheTranspiledLangStartJAVA_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 25) {
                keyWordCodeInTheTranspiledLangEndJAVA_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 26) {
                keyWordCodeInTheTranspiledLangStartKT_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 27) {
                keyWordCodeInTheTranspiledLangEndKT_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 28) {
                keyWordCodeInTheTranspiledLangStartRB_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 29) {
                keyWordCodeInTheTranspiledLangEndRB_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 30) {
                keyWordCodeInTheTranspiledLangStartNIM_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 31) {
                keyWordCodeInTheTranspiledLangEndNIM_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 32) {
                keyWordCodeInTheTranspiledLangStartAHK_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 33) {
                keyWordCodeInTheTranspiledLangEndAHK_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 34) {
                keyWordCodeInTheTranspiledLangStartSWIFT_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 35) {
                keyWordCodeInTheTranspiledLangEndSWIFT_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 36) {
                keyWordCodeInTheTranspiledLangStartDART_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 37) {
                keyWordCodeInTheTranspiledLangEndDART_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 38) {
                keyWordCodeInTheTranspiledLangStartTS_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 39) {
                keyWordCodeInTheTranspiledLangEndTS_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 40) {
                keyWordCodeInTheTranspiledLangStartGROOVY_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 41) {
                keyWordCodeInTheTranspiledLangEndGROOVY_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 42) {
                keyWordCodeInTheTranspiledLangStartHTVM_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 43) {
                keyWordCodeInTheTranspiledLangEndHTVM_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 44) {
                keyWordCodeInHTVMstart_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 45) {
                keyWordCodeInHTVMend_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 46) {
                keyWordCurlyBraceOpen_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 47) {
                keyWordCurlyBraceClose_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 48) {
                keyWordNull_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 49) {
                keyWordTrue_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 50) {
                keyWordFalse_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 51) {
                keyWordVoid_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 52) {
                keyWordDouble_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 53) {
                keyWordChar_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 54) {
                keyWordUint8_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 55) {
                keyWordUint16_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 56) {
                keyWordUint32_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 57) {
                keyWordUint64_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 58) {
                keyWordINT_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 59) {
                keyWordSTR_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 60) {
                keyWordBOOL_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 61) {
                keyWordFLOAT_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 62) {
                keyWordINT8_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 63) {
                keyWordINT16_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 64) {
                keyWordINT32_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 65) {
                keyWordINT64_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 66) {
                keyWordIF_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 67) {
                keyWordElseIf_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 68) {
                keyWordElse_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 69) {
                keyWordWhileLoop_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 70) {
                keyWordLoopInfinite_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 71) {
                keyWordLoop_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 72) {
                keyWordLoopParse_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 73) {
                keyWordContinue_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 74) {
                keyWordBreak_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 75) {
                keyWordFunc_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 76) {
                keyWordAwait_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 77) {
                keyWordAsync_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 78) {
                keyWordThrow_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 79) {
                keyWordErrorMsg_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 80) {
                keyWordTry_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 81) {
                keyWordCatch_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 82) {
                keyWordFinally_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 83) {
                keyWordReturnStatement_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 84) {
                keyWordArrayAppend_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 85) {
                keyWordArrayPop_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 86) {
                keyWordArraySize_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 87) {
                keyWordArrayInsert_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 88) {
                keyWordArrayRemove_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 89) {
                keyWordArrayIndexOf_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 90) {
                keyWordArrayDefinition_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 91) {
                keyWordArrayOfIntegersDefinition_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 92) {
                keyWordArrayOfStringsDefinition_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 93) {
                keyWordArrayOfFloatingPointNumbersDefinition_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 94) {
                keyWordArrayOfBooleansDefinition_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 95) {
                keyWordVar_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 96) {
                keyWordLet_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 97) {
                keyWordConst_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 98) {
                keyWordEnd_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 99) {
                keyWordGlobal_2 = Trim(A_LoopField65) + " ";
            }
            if (A_Index65 == 100) {
                keyWordComment_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 101) {
                keyWordCommentOpenMultiLine_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 102) {
                keyWordCommentCloseMultiLine_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 103) {
                keyWordEscpaeChar_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 104) {
                keyWordMainLabel_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 105) {
                keyWordConcat_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 106) {
                keyWordAdd_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 107) {
                keyWordSub_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 108) {
                keyWordMul_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 109) {
                keyWordDiv_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 110) {
                keyWordMod_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 111) {
                keyWordExp_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 112) {
                keyWordEqual_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 113) {
                keyWordStrictEqual_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 114) {
                keyWordNotEqual_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 115) {
                keyWordGreater_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 116) {
                keyWordLess_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 117) {
                keyWordGreaterEqual_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 118) {
                keyWordLessEqual_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 119) {
                keyWordAnd_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 120) {
                keyWordOr_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 121) {
                keyWordNot_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 122) {
                keyWordBitAnd_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 123) {
                keyWordBitOr_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 124) {
                keyWordBitXor_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 125) {
                keyWordBitNot_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 126) {
                keyWordShiftLeft_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 127) {
                keyWordShiftRight_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 128) {
                keyWordShiftUnsignedRight_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 129) {
                keyWordAssign_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 130) {
                keyWordAssignAdd_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 131) {
                keyWordAssignConcat_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 132) {
                keyWordAssignSub_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 133) {
                keyWordAssignMul_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 134) {
                keyWordAssignDiv_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 135) {
                keyWordAssignMod_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 136) {
                keyWordAssignShiftLeft_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 137) {
                keyWordAssignShiftRight_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 138) {
                keyWordLogicalAssignShiftRight_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 139) {
                keyWordAssignBitAnd_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 140) {
                keyWordAssignBitOr_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 141) {
                keyWordAssignBitXor_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 142) {
                keyWordTernary1_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 143) {
                keyWordTernary2_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 144) {
                keyWordInc_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 145) {
                keyWordDec_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 146) {
                AHKlikeLoopsIndexedAt_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 147) {
                keyWordAIndex_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 148) {
                keyWordALoopField_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 149) {
                useCurlyBraces_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 150) {
                useEnd_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 151) {
                useSemicolon_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 152) {
                useParentheses_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 153) {
                usePrefixTypeForTypeDefinition_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 154) {
                usePostfixTypeForTypeDefinition_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 155) {
                usePythonicColonSyntax_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 156) {
                useCurlyBracesSyntaxForArrayDef_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 157) {
                useInJavaScriptAlwaysUseVar_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 158) {
                useJavaScriptInAfullHTMLfile_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 159) {
                useJavaScriptAmainFuncDef_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 160) {
                useJavaScriptAllFuncsAreAsync_2 = Trim(A_LoopField65);
            }
            if (A_Index65 == 161) {
                useJavaScriptAlwaysTripleEqual_2 = Trim(A_LoopField65);
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
    print(htCode);
    code = htCode;
    print(mode);
    print(langToConvertTo);
    print("==================================");
    print("==================================");
    print("==================================");
    print("==================================");
    print("==================================");
    //print(allInstructionFile)
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
            if (InStr(code, StrLower(keyWordInclude + " "))) {
                for (let A_Index66 = 0; A_Index66 < 10000 + 0; A_Index66++) {
                    doseCodeHaveLibs = 0;
                    allLibCODE = "";
                    if (A_Index66 == 0) {
                        items67 = LoopParseFunc(code, "\n", "\r")
                        for (let A_Index67 = 0; A_Index67 < items67.length + 0; A_Index67++) {
                            const A_LoopField67 = items67[A_Index67 - 0];
                            if (SubStr(StrLower(Trim(A_LoopField67)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ")) {
                                allLibsWeSee.push(StrReplace(StringTrimLeft(Trim(A_LoopField67), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                allLibsWeSeeSEE.push(StrReplace(StringTrimLeft(Trim(A_LoopField67), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                doseCodeHaveLibs = 1;
                            }
                        }
                    } else {
                        items68 = LoopParseFunc(code, "\n", "\r")
                        for (let A_Index68 = 0; A_Index68 < items68.length + 0; A_Index68++) {
                            const A_LoopField68 = items68[A_Index68 - 0];
                            ALoopField = A_LoopField68;
                            if (SubStr(StrLower(Trim(A_LoopField68)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ")) {
                                doseCodeHaveLibs_HAS_SEEN = 0;
                                for (let A_Index69 = 0; A_Index69 < allLibsWeSee.length + 0; A_Index69++) {
                                    if (StrReplace(StringTrimLeft(Trim(ALoopField), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), "") == allLibsWeSee[A_Index69]) {
                                        doseCodeHaveLibs_HAS_SEEN = 1;
                                    }
                                }
                                if (doseCodeHaveLibs_HAS_SEEN == 0) {
                                    allLibsWeSee.push(StrReplace(StringTrimLeft(Trim(A_LoopField68), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                    allLibsWeSeeSEE.push(StrReplace(StringTrimLeft(Trim(A_LoopField68), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                    doseCodeHaveLibs = 1;
                                }
                            }
                        }
                    }
                    for (let A_Index70 = 0; A_Index70 < allLibsWeSee.length + 0; A_Index70++) {
                        allLibsWeSeeHOLD = allLibsWeSee[A_Index70];
                        doseCodeHaveLibs_HAS_SEEN2 = 0;
                        for (let A_Index71 = 0; A_Index71 < allLibsWeSeeSEE.length - allLibsWeSee.length + 0; A_Index71++) {
                            if (allLibsWeSeeHOLD == allLibsWeSeeSEE[A_Index71]) {
                                doseCodeHaveLibs_HAS_SEEN2 = 1;
                            }
                        }
                        if (doseCodeHaveLibs_HAS_SEEN2 == 0) {
                            allLibCODE += FileRead(Trim(allLibsWeSee[allLibsWeSee.length - A_Index70 - 1])) + "\n";
                        }
                        allLibsWeSee.pop();
                    }
                    allLibCODEfix = "";
                    items72 = LoopParseFunc(code, "\n", "\r")
                    for (let A_Index72 = 0; A_Index72 < items72.length + 0; A_Index72++) {
                        const A_LoopField72 = items72[A_Index72 - 0];
                        if (SubStr(StrLower(Trim(A_LoopField72)), 1, StrLen(StrLower(keyWordInclude + " "))) != StrLower(keyWordInclude + " ")) {
                            allLibCODEfix += A_LoopField72 + "\n";
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
    items73 = LoopParseFunc(code, "\n", "\r")
    for (let A_Index73 = 0; A_Index73 < items73.length + 0; A_Index73++) {
        const A_LoopField73 = items73[A_Index73 - 0];
        if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEnd)) {
            COUNT_programmingBlock_InTheTranspiledLang++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(COUNT_programmingBlock_InTheTranspiledLang) + "AA\n";
            programmingBlock_InTheTranspiledLang.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndCPP)) {
            COUNT_programmingBlock_CPP++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(COUNT_programmingBlock_CPP) + "AA\n";
            programmingBlock_CPP.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndPY)) {
            COUNT_programmingBlock_PY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_PY-programmingBlock_PY-AA" + STR(COUNT_programmingBlock_PY) + "AA\n";
            programmingBlock_PY.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndJS)) {
            COUNT_programmingBlock_JS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JS-programmingBlock_JS-AA" + STR(COUNT_programmingBlock_JS) + "AA\n";
            programmingBlock_JS.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndGO)) {
            COUNT_programmingBlock_GO++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GO-programmingBlock_GO-AA" + STR(COUNT_programmingBlock_GO) + "AA\n";
            programmingBlock_GO.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndLUA)) {
            COUNT_programmingBlock_LUA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(COUNT_programmingBlock_LUA) + "AA\n";
            programmingBlock_LUA.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndCS)) {
            COUNT_programmingBlock_CS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CS-programmingBlock_CS-AA" + STR(COUNT_programmingBlock_CS) + "AA\n";
            programmingBlock_CS.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndJAVA)) {
            COUNT_programmingBlock_JAVA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(COUNT_programmingBlock_JAVA) + "AA\n";
            programmingBlock_JAVA.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndKT)) {
            COUNT_programmingBlock_KT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_KT-programmingBlock_KT-AA" + STR(COUNT_programmingBlock_KT) + "AA\n";
            programmingBlock_KT.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndRB)) {
            COUNT_programmingBlock_RB++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_RB-programmingBlock_RB-AA" + STR(COUNT_programmingBlock_RB) + "AA\n";
            programmingBlock_RB.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndNIM)) {
            COUNT_programmingBlock_NIM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(COUNT_programmingBlock_NIM) + "AA\n";
            programmingBlock_NIM.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndAHK)) {
            COUNT_programmingBlock_AHK++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(COUNT_programmingBlock_AHK) + "AA\n";
            programmingBlock_AHK.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndSWIFT)) {
            COUNT_programmingBlock_SWIFT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(COUNT_programmingBlock_SWIFT) + "AA\n";
            programmingBlock_SWIFT.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndDART)) {
            COUNT_programmingBlock_DART++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_DART-programmingBlock_DART-AA" + STR(COUNT_programmingBlock_DART) + "AA\n";
            programmingBlock_DART.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndTS)) {
            COUNT_programmingBlock_TS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_TS-programmingBlock_TS-AA" + STR(COUNT_programmingBlock_TS) + "AA\n";
            programmingBlock_TS.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndGROOVY)) {
            COUNT_programmingBlock_GROOVY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(COUNT_programmingBlock_GROOVY) + "AA\n";
            programmingBlock_GROOVY.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndHTVM)) {
            COUNT_programmingBlock_HTVM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(COUNT_programmingBlock_HTVM) + "AA\n";
            programmingBlock_HTVM.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInHTVMend)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            COUNT_programmingBlock_HTVMsyntax++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(COUNT_programmingBlock_HTVMsyntax) + "AA\n";
            programmingBlock_HTVMsyntax.push(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        }
        else if (inProgarmmingBlock == 1) {
            holdTempDataProgrammingBlockThenPutInArr += A_LoopField73 + "\n";
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStart)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartCPP)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartPY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartJS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartGO)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartLUA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartCS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartJAVA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartKT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartRB)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartNIM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartAHK)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartSWIFT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartDART)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartTS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartGROOVY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartHTVM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInHTVMstart)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        } else {
            programmingBlocksTemp += A_LoopField73 + "\n";
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
        print("============programmingBlock_CPP==================");
        print("============programmingBlock_CPP==================");
        if (programmingBlock_CPP.length > 0) {
            for (let A_Index74 = 0; A_Index74 < programmingBlock_CPP.length + 0; A_Index74++) {
                print(programmingBlock_CPP[A_Index74]);
            }
        }
        print("============programmingBlock_CPP==================");
        print("============programmingBlock_CPP==================");
        items75 = LoopParseFunc(code)
        for (let A_Index75 = 0; A_Index75 < items75.length + 0; A_Index75++) {
            const A_LoopField75 = items75[A_Index75 - 0];
            theIdNumOfThe34theVar.push("");
            theIdNumOfThe34theVar.push("");
        }
        items76 = LoopParseFunc(code)
        for (let A_Index76 = 0; A_Index76 < items76.length + 0; A_Index76++) {
            const A_LoopField76 = items76[A_Index76 - 0];
            theIdNumOfThe34theVar[A_Index76] = theIdNumOfThe34theVar[A_Index76] + Chr(34);
            getAllCharForTheFurtureSoIcanAddEscapeChar.push(A_LoopField76);
        }
        getAllCharForTheFurtureSoIcanAddEscapeChar.push(" ");
        ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuusgfgesrheidFor--asdsas--theuhtuwaesphoutr" + Chr(34);
        items77 = LoopParseFunc(code)
        for (let A_Index77 = 0; A_Index77 < items77.length + 0; A_Index77++) {
            const A_LoopField77 = items77[A_Index77 - 0];
            if (A_LoopField77 == keyWordEscpaeChar && getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index77 + 1] == Chr(34)) {
                fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1;
                OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes;
            } else {
                if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1) {
                    OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField77;
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
            items78 = LoopParseFunc(code)
            for (let A_Index78 = 0; A_Index78 < items78.length + 0; A_Index78++) {
                const A_LoopField78 = items78[A_Index78 - 0];
                if (A_LoopField78 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField78 != Chr(34)) {
                        if (A_LoopField78 == keyWordEscpaeChar && langToConvertTo != langFileExtension_2) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField78;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField78 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField78;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        } else {
            items79 = LoopParseFunc(code)
            for (let A_Index79 = 0; A_Index79 < items79.length + 0; A_Index79++) {
                const A_LoopField79 = items79[A_Index79 - 0];
                if (A_LoopField79 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField79 != Chr(34)) {
                        if (A_LoopField79 == keyWordEscpaeChar && keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index79 + 1] && langToConvertTo != langFileExtension_2) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar;
                            removeNexFixkeyWordEscpaeChar = 1;
                        }
                        else if (A_LoopField79 == keyWordEscpaeChar && langToConvertTo != langFileExtension_2) {
                            if (removeNexFixkeyWordEscpaeChar != 1) {
                                theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                            } else {
                                removeNexFixkeyWordEscpaeChar = 0;
                            }
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField79;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField79 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField79;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        }
        code = htCodeOUT754754;
        for (let A_Index80 = 0; A_Index80 < theIdNumOfThe34 + 0; A_Index80++) {
            theIdNumOfThe34theVar[A_Index80] = theIdNumOfThe34theVar[A_Index80] + Chr(34);
        }
        theIdNumOfThe34theVar.push(Chr(34));
        code = StrReplace(code, Chr(13), "");
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
        items81 = LoopParseFunc(code, "\n", "\r")
        for (let A_Index81 = 0; A_Index81 < items81.length + 0; A_Index81++) {
            const A_LoopField81 = items81[A_Index81 - 0];
            // Define the original string
            originalStringForRemoveCommentsOnTheEndOfTheLine = A_LoopField81;
            // Find the position of the keyword in the original string
            posForRemoveCommentsOnTheEndOfTheLine = InStr(originalStringForRemoveCommentsOnTheEndOfTheLine, " " + keyWordComment);
            if (SubStr(Trim(A_LoopField81), 1, StrLen(keyWordComment)) != keyWordComment) {
                if (posForRemoveCommentsOnTheEndOfTheLine > 0) {
                    beforeKeywordForRemoveCommentsOnTheEndOfTheLine = A_LoopField81;
                    // Construct the new string with everything before the keyword
                    newStringOutCode += beforeKeywordForRemoveCommentsOnTheEndOfTheLine + "\n";
                } else {
                    newStringOutCode += A_LoopField81 + "\n";
                }
            } else {
                newStringOutCode += A_LoopField81 + "\n";
            }
        }
        code = StringTrimRight(newStringOutCode, 1);
        //MsgBox, % code
        if (useCurlyBraces == "on") {
            if (keyWordCurlyBraceOpen != "{") {
                items82 = LoopParseFunc(code, "\n", "\r")
                for (let A_Index82 = 0; A_Index82 < items82.length + 0; A_Index82++) {
                    const A_LoopField82 = items82[A_Index82 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField82)) == true || Trim(A_LoopField82) == keyWordCurlyBraceOpen) {
                        htCodeOutFixINT2 = 1;
                    }
                    htCodeOutFixINT = 0;
                    items83 = LoopParseFunc(A_LoopField82, " ")
                    for (let A_Index83 = 0; A_Index83 < items83.length + 0; A_Index83++) {
                        const A_LoopField83 = items83[A_Index83 - 0];
                        htCodeOutFixINT++;
                    }
                    htCodeOutFixINT--;
                    items84 = LoopParseFunc(A_LoopField82, " ")
                    for (let A_Index84 = 0; A_Index84 < items84.length + 0; A_Index84++) {
                        const A_LoopField84 = items84[A_Index84 - 0];
                        if (htCodeOutFixINT == A_Index84 && htCodeOutFixINT2 == 1) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField84, keyWordCurlyBraceOpen, "{") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField84 + " ";
                        }
                    }
                    htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1);
                    htCodeOutFixEnd += "\n";
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            htCodeOutFixEnd = "";
            if (keyWordCurlyBraceClose != "}") {
                items85 = LoopParseFunc(code, "\n", "\r")
                for (let A_Index85 = 0; A_Index85 < items85.length + 0; A_Index85++) {
                    const A_LoopField85 = items85[A_Index85 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField85)) == true || Trim(A_LoopField85) == keyWordCurlyBraceClose) {
                        htCodeOutFixINT2 = 1;
                    }
                    items86 = LoopParseFunc(A_LoopField85, " ")
                    for (let A_Index86 = 0; A_Index86 < items86.length + 0; A_Index86++) {
                        const A_LoopField86 = items86[A_Index86 - 0];
                        if (htCodeOutFixINT2 == 1 || Trim(A_LoopField86) == keyWordCurlyBraceClose) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField86, keyWordCurlyBraceClose, "}") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField86 + " ";
                        }
                    }
                    htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1);
                    htCodeOutFixEnd += "\n";
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
            items87 = LoopParseFunc(code, "\n", "\r")
            for (let A_Index87 = 0; A_Index87 < items87.length + 0; A_Index87++) {
                const A_LoopField87 = items87[A_Index87 - 0];
                if (StrLower(Trim(A_LoopField87)) == StrLower(keyWordEnd)) {
                    htCodeOutFixEnd += "}\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField87)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF) && isLineAconstruct(Trim(A_LoopField87)) == true) {
                    htCodeOutFixEnd += A_LoopField87 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField87)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop) && isLineAconstruct(Trim(A_LoopField87)) == true) {
                    htCodeOutFixEnd += A_LoopField87 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField87)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf) && isLineAconstruct(Trim(A_LoopField87)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField87 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField87)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse) && isLineAconstruct(Trim(A_LoopField87)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField87 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField87)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch) && isLineAconstruct(Trim(A_LoopField87)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField87 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField87)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally) && isLineAconstruct(Trim(A_LoopField87)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField87 + "\n{\n";
                }
                else if (isLineAconstruct(Trim(A_LoopField87)) == true) {
                    htCodeOutFixEnd += A_LoopField87 + "\n{\n";
                } else {
                    htCodeOutFixEnd += A_LoopField87 + "\n";
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        if (usePythonicColonSyntax == "off") {
            if (useEnd == "off" && useCurlyBraces == "off") {
                htCodeOutFixEnd = "";
                items88 = LoopParseFunc(code, "\n", "\r")
                for (let A_Index88 = 0; A_Index88 < items88.length + 0; A_Index88++) {
                    const A_LoopField88 = items88[A_Index88 - 0];
                    if (isLineAconstruct(Trim(A_LoopField88)) == true) {
                        htCodeOutFixEnd += A_LoopField88 + ":\n";
                    } else {
                        htCodeOutFixEnd += A_LoopField88 + "\n";
                    }
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
        }
        if (useCurlyBraces == "off" && useEnd == "off") {
            code = AddCurlyBraces(code);
        }
        outTrimCode = "";
        items89 = LoopParseFunc(code, "\n", "\r")
        for (let A_Index89 = 0; A_Index89 < items89.length + 0; A_Index89++) {
            const A_LoopField89 = items89[A_Index89 - 0];
            outTrimCode += Trim(A_LoopField89) + "\n";
        }
        code = StringTrimRight(outTrimCode, 1);
        // for converting c++ to js and py
        //code := StrReplace(code, "{}", "[]")
        var outCodeFixBraces = "";
        for (let A_Index90 = 0; A_Index90 < 2 + 0; A_Index90++) {
            outCodeFixBraces = "";
            items91 = LoopParseFunc(code, "\n", "\r")
            for (let A_Index91 = 0; A_Index91 < items91.length + 0; A_Index91++) {
                const A_LoopField91 = items91[A_Index91 - 0];
                if (InStr(Trim(A_LoopField91), "{") && Trim(A_LoopField91) != "{") {
                    outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField91), "{", "")) + "\n{\n";
                }
                else if (InStr(Trim(A_LoopField91), "}") && Trim(A_LoopField91) != "}") {
                    outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField91), "}", "")) + "\n";
                } else {
                    outCodeFixBraces += Trim(A_LoopField91) + "\n";
                }
            }
            code = StringTrimRight(outCodeFixBraces, 1);
        }
        htCodeOutFixEnd = "";
        if (usePythonicColonSyntax == "on") {
            items92 = LoopParseFunc(code, "\n", "\r")
            for (let A_Index92 = 0; A_Index92 < items92.length + 0; A_Index92++) {
                const A_LoopField92 = items92[A_Index92 - 0];
                if (isLineAconstruct(Trim(A_LoopField92)) == true) {
                    htCodeOutFixEnd += StringTrimRight(A_LoopField92, 1) + "\n";
                } else {
                    htCodeOutFixEnd += A_LoopField92 + "\n";
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        //;; main loop ;;;
        //;; main loop ;;;
        //;; main loop ;;;
        //;; main loop ;;;
        fullLangAllOperators = await GETfullLangAllOperators();
        fullLangAllOperators_HELP = await GETfullLangAllOperators_HELP();
        if (isNotHTVMfile2 == 0) {
            items93 = LoopParseFunc(code, "\n", "\r")
            for (let A_Index93 = 0; A_Index93 < items93.length + 0; A_Index93++) {
                const A_LoopField93 = items93[A_Index93 - 0];
                if (StrLower(A_LoopField93) == StrLower(keyWordMainLabel)) {
                    didWeUseMainLabel = 1;
                    if (langToConvertTo == langFileExtension_2) {
                        codeOutFixAndAddMainFunc += keyWordMainLabel_2 + Chr(10);
                    }
                    if (langToConvertTo == "cpp") {
                        codeOutFixAndAddMainFunc += "int main(int argc, char* argv[])\n{\n";
                    }
                    if (langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
                        codeOutFixAndAddMainFunc += "async function main()\n{\n";
                    }
                    if (langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
                        codeOutFixAndAddMainFunc += "async function main(): Promise<void>\n{\n";
                    }
                    if (langToConvertTo == "go") {
                        codeOutFixAndAddMainFunc += "func main()\n{\n";
                    }
                    if (langToConvertTo == "cs") {
                        codeOutFixAndAddMainFunc += "static void Main(string[] args)\n{\n";
                    }
                    if (langToConvertTo == "java") {
                        codeOutFixAndAddMainFunc += "public static void main(String[] args)\n{\n";
                    }
                    if (langToConvertTo == "kt") {
                        codeOutFixAndAddMainFunc += "fun main(args: Array<String>)\n{\n";
                    }
                    if (langToConvertTo == "swift") {
                        codeOutFixAndAddMainFunc += "func main()\n{\n";
                    }
                    if (langToConvertTo == "dart") {
                        codeOutFixAndAddMainFunc += "void main(List<String> arguments)\n{\n";
                    }
                } else {
                    codeOutFixAndAddMainFunc += A_LoopField93 + "\n";
                }
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "cpp") {
                codeOutFixAndAddMainFunc = "int main(int argc, char* argv[])\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
                codeOutFixAndAddMainFunc = "async function main()\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
                codeOutFixAndAddMainFunc = "async function main(): Promise<void>\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "go") {
                codeOutFixAndAddMainFunc = "func main()\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "cs") {
                codeOutFixAndAddMainFunc = "static void Main(string[] args)\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "java") {
                codeOutFixAndAddMainFunc = "public static void main(String[] args)\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "kt") {
                codeOutFixAndAddMainFunc = "fun main(args: Array<String>)\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "swift") {
                codeOutFixAndAddMainFunc = "func main()\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "dart") {
                codeOutFixAndAddMainFunc = "void main(List<String> arguments)\n{\n" + codeOutFixAndAddMainFunc;
            }
            code = StringTrimRight(codeOutFixAndAddMainFunc, 1);
            // main loop
            // main loop
        }
        items94 = LoopParseFunc(code, "\n", "\r")
        for (let A_Index94 = 0; A_Index94 < items94.length + 0; A_Index94++) {
            const A_LoopField94 = items94[A_Index94 - 0];
            lookIntoTheNextLineForFuncWhitNoKeyWord.push(A_LoopField94);
        }
        lookIntoTheNextLineForFuncWhitNoKeyWord.push(" ");
        htCode = "";
        print("=======UP==========");
        print(code);
        print("=======DOWN==========");
        items95 = LoopParseFunc(code, "\n", "\r")
        for (let A_Index95 = 0; A_Index95 < items95.length + 0; A_Index95++) {
            const A_LoopField95 = items95[A_Index95 - 0];
            lineDone = 0;
            if (SubStr(A_LoopField95, 1, StrLen(keyWordComment)) == keyWordComment) {
                str1 = StringTrimLeft(A_LoopField95, StrLen(keyWordComment));
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
            else if (Trim(A_LoopField95) == keyWordCommentOpenMultiLine) {
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
            else if (Trim(A_LoopField95) == keyWordCommentCloseMultiLine) {
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
            else if (SubStr(StrLower(Trim(A_LoopField95)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF)) {
                str1 = Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordIF)));
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"));
                str1 = StringTrimRight(str1, 1);
                str1 = StringTrimLeft(str1, 1);
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + str1 + ":\n";
                            } else {
                                htCode += keyWordIF_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":\n";
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + "(" + str1 + "):\n";
                            } else {
                                htCode += keyWordIF_2 + str1 + ":\n";
                            }
                        }
                    } else {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + str1 + "\n";
                            } else {
                                htCode += keyWordIF_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + "\n";
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + "(" + str1 + ")\n";
                            } else {
                                htCode += keyWordIF_2 + str1 + "\n";
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
                    htCode += "if " + str1 + "\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "if " + str1 + " then\n";
                }
                if (langToConvertTo == "cs") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + "\n";
                    } else {
                        htCode += "if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "java") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + "\n";
                    } else {
                        htCode += "if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "kt") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + "\n";
                    } else {
                        htCode += "if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "if " + str1 + "\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "if " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + "\n";
                    } else {
                        htCode += "if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "if " + str1 + "\n";
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + "\n";
                    } else {
                        htCode += "if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + "\n";
                    } else {
                        htCode += "if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "if " + str1 + "\n";
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField95)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf)) {
                str1 = Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordElseIf)));
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
                                htCode += keyWordElseIf_2 + str1 + "\n";
                            } else {
                                htCode += keyWordElseIf_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + "\n";
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + "(" + str1 + ")\n";
                            } else {
                                htCode += keyWordElseIf_2 + str1 + "\n";
                            }
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "py") {
                    htCode += "elif " + str1 + ":\n";
                }
                if (langToConvertTo == "js") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "go") {
                    htCode += "else if " + str1 + "\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "elseif " + str1 + " then\n";
                }
                if (langToConvertTo == "cs") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "java") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "kt") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "elsif " + str1 + "\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "elif " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "else if " + str1 + "\n";
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "else if " + str1 + "\n";
                }
            }
            else if (StrLower(Trim(A_LoopField95)) == StrLower(keyWordElse) || StrLower(Trim(A_LoopField95)) == StrLower(keyWordElse + ":")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordElse_2 + ":\n";
                    } else {
                        htCode += keyWordElse_2 + "\n";
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
            else if (SubStr(StrLower(Trim(A_LoopField95)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)) {
                str1 = Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordWhileLoop)));
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
                        htCode += "while " + str1 + "\n";
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "while " + str1 + "\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "while " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + "\n";
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "while " + str1 + "\n";
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + "\n";
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + "\n";
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "while " + str1 + "\n";
                }
            }
            else if (StrLower(Trim(A_LoopField95)) == StrLower(keyWordTry) || StrLower(Trim(A_LoopField95)) == StrLower(keyWordTry + ":")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordTry_2 + ":\n";
                    } else {
                        htCode += keyWordTry_2 + "\n";
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
            else if (SubStr(StrLower(Trim(A_LoopField95)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)) {
                str1 = Trim(StrReplace(StrReplace(StringTrimLeft(A_LoopField95, StrLen(keyWordCatch)), "(", ""), ")", ""));
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
                    htCode += "catch (Exception " + str1 + ")\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "catch (" + str1 + ": Exception)\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "rescue => " + str1 + "\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "except ValueError as " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "catch " + str1 + "\n";
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
            else if (StrLower(Trim(A_LoopField95)) == StrLower(keyWordFinally) || StrLower(Trim(A_LoopField95)) == StrLower(keyWordFinally + ":")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordFinally_2 + ":\n";
                    } else {
                        htCode += keyWordFinally_2 + "\n";
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
            else if (SubStr(StrLower(Trim(A_LoopField95)), 1, StrLen(StrLower(keyWordThrow))) == StrLower(keyWordThrow)) {
                str1 = expressionParserTranspiler(fixArray1234(Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordThrow)))));
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordThrow_2 + " " + keyWordErrorMsg + "(" + str1 + ");\n";
                    } else {
                        htCode += keyWordThrow_2 + " " + keyWordErrorMsg + "(" + str1 + ")\n";
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
                    htCode += "throw " + str1 + "\n";
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
            else if (StrLower(A_LoopField95) == StrLower(keyWordBreak) || StrLower(A_LoopField95) == StrLower(keyWordBreak + ";")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordBreak_2 + ";\n";
                    } else {
                        htCode += keyWordBreak_2 + "\n";
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
                    htCode += "break;\n";
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
            else if (StrLower(A_LoopField95) == StrLower(Trim(keyWordReturnStatement)) || StrLower(A_LoopField95) == StrLower(Trim(keyWordReturnStatement) + ";")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordReturnStatement_2 + ";\n";
                    } else {
                        htCode += keyWordReturnStatement_2 + "\n";
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
                    htCode += "return;\n";
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
            else if (SubStr(Trim(StrLower(A_LoopField95)), 1, StrLen(StrLower(keyWordReturnStatement))) == StrLower(keyWordReturnStatement)) {
                str1 = Trim(expressionParserTranspiler(Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordReturnStatement)))));
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordReturnStatement_2 + str1 + ";\n";
                    } else {
                        htCode += keyWordReturnStatement_2 + str1 + "\n";
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "return " + str1 + ";\n";
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
            else if (StrLower(A_LoopField95) == StrLower(keyWordContinue) || StrLower(A_LoopField95) == StrLower(keyWordContinue + ";")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordContinue_2 + ";\n";
                    } else {
                        htCode += keyWordContinue_2 + "\n";
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
                    htCode += "goto continue\n";
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
                    htCode += "continue;\n";
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
            else if (StrLower(A_LoopField95) == "::" + keyWordContinue + "::") {
                if (langToConvertTo == langFileExtension_2) {
                    htCode += "::" + keyWordContinue_2 + "::\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "::continue::\n";
                }
            }
            else if (StrLower(A_LoopField95) == StrLower(keyWordLoopInfinite) || StrLower(A_LoopField95) == StrLower(keyWordLoopInfinite + ":")) {
                // infinity loops
                haveWeEverUsedAloop = 1;
                lineDone = 1;
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
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++";
                }
                if (langToConvertTo == "lua") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + ", someLimit do";
                }
                if (langToConvertTo == "cs") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit)";
                }
                if (langToConvertTo == "rb") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit do";
                }
                if (langToConvertTo == "nim") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit:";
                }
                if (langToConvertTo == "ahk") {
                    var1 = "Loop";
                }
                if (langToConvertTo == "swift") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " ..< someLimit";
                }
                if (langToConvertTo == "dart") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit)";
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
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
            }
            else if (SubStr(Trim(StrLower(A_LoopField95)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop) && SubStr(Trim(StrLower(A_LoopField95)), 1, StrLen(StrLower(keyWordLoop)) + 2) != StrLower(keyWordLoop) + "% " && SubStr(Trim(StrLower(A_LoopField95)), 1, StrLen(StrLower(keyWordLoopParse))) != StrLower(keyWordLoopParse)) {
                out2 = StringTrimLeft(A_LoopField95, StrLen(keyWordLoop));
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
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "cs") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == "rb") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "nim") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ":";
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
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")";
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
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                lineDone = 1;
                htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
            }
            else if (SubStr(Trim(StrLower(A_LoopField95)), 1, StrLen(StrLower(keyWordLoop)) + 2) == StrLower(keyWordLoop) + "% ") {
                out2 = StringTrimLeft(A_LoopField95, StrLen(keyWordLoop) + 2);
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
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "cs") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == "rb") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "nim") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ":";
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
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")";
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
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                lineDone = 1;
                htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
            }
            else if (SubStr(StrLower(A_LoopField95), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
                var1 = StringTrimLeft(A_LoopField95, StrLen(keyWordLoopParse));
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
                        itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "lua") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "cs") {
                        itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "java") {
                        itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
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
                        itemsOut = "\n";
                    }
                    if (langToConvertTo == "swift") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "dart") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
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
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "lua") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "cs") {
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
                        }
                        if (langToConvertTo == "java") {
                            itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
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
                            itemsOut = "\n";
                        }
                        if (langToConvertTo == "swift") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "dart") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "ts") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
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
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "lua") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "cs") {
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                        }
                        if (langToConvertTo == "java") {
                            itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
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
                            itemsOut = "\n";
                        }
                        if (langToConvertTo == "swift") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "dart") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
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
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
                        }
                        if (langToConvertTo == "java") {
                            itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
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
                            itemsOut = "\n";
                        }
                        if (langToConvertTo == "swift") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "dart") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
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
                    var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in enumerate(items" + STR(AindexcharLength) + ", start=" + AHKlikeLoopsIndexedAt + "):";
                }
                if (langToConvertTo == "js") {
                    var1out = itemsOut + "\n" + "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "cpp") {
                    var1out = itemsOut + "\n" + "for (size_t " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".size() + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "go") {
                    var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " := range(items" + STR(AindexcharLength) + ")";
                }
                if (langToConvertTo == "lua") {
                    var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in ipairs(items" + STR(AindexcharLength) + ") do";
                }
                if (langToConvertTo == "cs") {
                    var1out = itemsOut + "\n" + "foreach (var " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + ")";
                }
                if (langToConvertTo == "java") {
                    var1out = itemsOut + "\n" + "for (" + keyWordALoopField + "" + STR(AindexcharLength) + " : items" + STR(AindexcharLength) + ")";
                }
                if (langToConvertTo == "kt") {
                    var1out = itemsOut + "\n" + "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + ".withIndex())";
                }
                if (langToConvertTo == "rb") {
                    var1out = itemsOut + "\n" + "items" + STR(AindexcharLength) + ".each_with_index do |" + keyWordALoopField + "" + STR(AindexcharLength) + " , " + keyWordAIndex + "" + STR(AindexcharLength) + "|";
                }
                if (langToConvertTo == "nim") {
                    var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + " | " + keyWordAIndex + "" + STR(AindexcharLength) + " += 1:";
                }
                if (langToConvertTo == "ahk") {
                    var1out = "Loop, Parse, " + line1 + " " + line2 + " " + line3;
                }
                if (langToConvertTo == "swift") {
                    var1out = itemsOut + "\n" + "for (index, " + keyWordALoopField + "" + STR(AindexcharLength) + ") in items" + STR(AindexcharLength) + ".enumerated()";
                }
                if (langToConvertTo == "dart") {
                    var1out = itemsOut + "\n" + "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = 0; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1out = itemsOut + "\n" + "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = 0; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1out = itemsOut + "\n" + "items" + STR(AindexcharLength) + ".eachWithIndex { " + keyWordALoopField + "" + STR(AindexcharLength) + " , " + keyWordAIndex + "" + STR(AindexcharLength) + " ->";
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
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " := items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "lua") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "cs") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "java") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "kt") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "rb") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "nim") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "ahk") {
                    theFixTextLoopLP = "\n";
                }
                if (langToConvertTo == "swift") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "dart") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "ts") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "groovy") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                htCodeAcurlyBraceAddSomeVrasFixLP = 1;
                haveWeEverUsedAloop = 1;
                if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                    htCodeLoopfixa += "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                    htCodeLoopfixa1 = "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += Trim(keyWordLoopParse_2) + " " + var1 + ":\n";
                    } else {
                        htCode += Trim(keyWordLoopParse_2) + " " + var1 + Chr(10);
                    }
                } else {
                    htCode += htCodeLoopfixa1 + Chr(10) + var1out + Chr(10);
                }
            }
            else if (SubStrLastChars(Trim(A_LoopField95), StrLen(keyWordInc)) == keyWordInc || SubStrLastChars(Trim(A_LoopField95), StrLen(keyWordInc + ";")) == keyWordInc + ";" && lineDone == 0) {
                if (useSemicolon == "on") {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField95), StrLen(keyWordInc + ";")));
                } else {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField95), StrLen(keyWordInc)));
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
                    htCode += str1 + "++;" + Chr(10);
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
            else if (SubStrLastChars(Trim(A_LoopField95), StrLen(keyWordDec)) == keyWordDec || SubStrLastChars(Trim(A_LoopField95), StrLen(keyWordDec + ";")) == keyWordDec + ";" && lineDone == 0) {
                if (useSemicolon == "on") {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField95), StrLen(keyWordDec + ";")));
                } else {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField95), StrLen(keyWordDec)));
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
                    htCode += str1 + "--;" + Chr(10);
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
            else if (SubStr(StrLower(Trim(A_LoopField95)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ") && langToConvertTo == langFileExtension_2) {
                htCode += keyWordInclude_2 + " " + Trim(StringTrimLeft(Trim(A_LoopField95), StrLen(StrLower(keyWordInclude) + " "))) + "\n";
            }
            else if (StrLower(A_LoopField95) == StrLower(keyWordGlobal) || StrLower(A_LoopField95) == StrLower(keyWordGlobal + ";")) {
                if (langToConvertTo == "ahk") {
                    htCode += "global\n";
                }
            }
            else if (SubStr(StrLower(A_LoopField95), 1, StrLen(StrLower(keyWordAwait))) == StrLower(keyWordAwait)) {
                str1 = StringTrimLeft(A_LoopField95, StrLen(keyWordAwait));
                //MsgBox, % A_LoopField95
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
                    htCode += "await " + str2 + "\n";
                } else {
                    htCode += str2 + "\n";
                }
            }
            else if (SubStr(StrLower(A_LoopField95), 1, StrLen(StrLower(keyWordGlobal))) == StrLower(keyWordGlobal)) {
                str1 = StringTrimLeft(A_LoopField95, StrLen(keyWordGlobal));
                //MsgBox, % A_LoopField95
                str1 = StrReplace(str1, ";", "");
                lineDone = 1;
                if (langToConvertTo == "py" || langToConvertTo == "ahk") {
                    str2 = "global " + str1;
                } else {
                    str2 = "";
                }
                htCode += str2 + "\n";
            }
            else if (A_LoopField95 == "sdghbuheaq8ehgfuowhPSAVBYOFXDSAWHPDIVHXDBOAUHIPXVBOAUHFXDPVOYaushdpzuoyvsdhpxuoazdsfpc") {
                lineDone = 1;
                htCode += A_LoopField95 + Chr(10);
            }
            else if (A_LoopField95 == "sdghbuheaq8ehgfuowhPSAVBYOFXDSAWHPDIVHXDBOAUHIPXVBOAUHFXDPVOYaushdpzuoyvsdhpxuoazdsfpc") {
                lineDone = 1;
                htCode += A_LoopField95 + Chr(10);
            }
            else if (A_LoopField95 == "sdghbuheaq8ehgfuowhPSAVBYOFXDSAWHPDIVHXDBOAUHIPXVBOAUHFXDPVOYaushdpzuoyvsdhpxuoazdsfpc") {
                lineDone = 1;
                htCode += A_LoopField95 + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField95), 1, StrLen(keyWordFunc)) == keyWordFunc || SubStr(StrLower(A_LoopField95), 1, StrLen(keyWordAsync + keyWordFunc)) == keyWordAsync + keyWordFunc && lineDone == 0) {
                lineDone = 1;
                if (SubStr(StrLower(A_LoopField95), 1, StrLen(keyWordAsync + keyWordFunc)) == keyWordAsync + keyWordFunc) {
                    // is async
                    int1 = 1;
                    str1 = Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordAsync + keyWordFunc)));
                } else {
                    // is async
                    int1 = 0;
                    str1 = Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordFunc)));
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
                                htCode += keyWordAsync + keyWordFunc + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                            } else {
                                htCode += keyWordAsync + keyWordFunc + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                htCode += keyWordFunc + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                            } else {
                                htCode += keyWordFunc + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
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
                    str1 = "";
                    str2 = "";
                    str3 = "";
                    str4 = "";
                    str5 = "";
                    str6 = "";
                    str7 = "";
                    str8 = "";
                    str9 = "";
                    str10 = "";
                    items96 = LoopParseFunc(str1, ",")
                    for (let A_Index96 = 0; A_Index96 < items96.length + 0; A_Index96++) {
                        const A_LoopField96 = items96[A_Index96 - 0];
                        print("|" + Trim(A_LoopField96) + "|");
                        if (InStr(Trim(A_LoopField96), " ")) {
                            // there is space aka there is a type
                            if (InStr(A_LoopField96, " " + Trim(keyWordAssign) + " ") == false) {
                                str6 = Trim(A_LoopField96);
                                str7 = getTheLastWord(str6);
                                str8 = getFuncTypeConvert(Trim(StringTrimRight(str6, StrLen(Trim(str7)) + 1)));
                                // str5 .= str8 . " " . str7 . Chr(10)
                            } else {
                                // optanal param
                                if (InStr(Trim(StrSplit(Trim(A_LoopField96), " " + Trim(keyWordAssign) + " ", 1)), " ")) {
                                    // there is a type
                                    str6 = Trim(StrSplit(Trim(A_LoopField96), " " + Trim(keyWordAssign) + " ", 1));
                                    str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField96), " " + Trim(keyWordAssign) + " ", 2))));
                                    str7 = getTheLastWord(str6);
                                    str8 = getFuncTypeConvert(Trim(StringTrimRight(str6, StrLen(Trim(str7)) + 1)));
                                    // str10
                                    // skipLeftCuleyForFuncPLS := 1
                                } else {
                                    // there is no type
                                    str8 = Trim(StrSplit(Trim(A_LoopField96), " " + Trim(keyWordAssign) + " ", 1));
                                    str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField96), " " + Trim(keyWordAssign) + " ", 2))));
                                    str7 = str8;
                                    // str10
                                }
                            }
                        } else {
                            str5 += Trim(A_LoopField96) + Chr(10);
                        }
                    }
                    str5 = StringTrimRight(str5, 1);
                }
            }
            else if ((SubStr(Trim(A_LoopField95), -2) == ");" || SubStr(Trim(A_LoopField95), -1) == ")") && !(InStr(A_LoopField95, "int main(int argc, char* argv[])")) && !(InStr(A_LoopField95, "async function main()")) && lineDone == 0) {
                lineDone = 1;
                str1 = Trim(A_LoopField95);
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
                htCode += str2 + "\n";
            }
            else if (KeyWordsCommands(A_LoopField95, "check", commands, langToConvertTo) == "true" && lineDone == 0) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += A_LoopField95 + "\n";
                } else {
                    out_KeyWordsCommands = KeyWordsCommands(A_LoopField95, "transpile", commands, langToConvertTo);
                    htCode += out_KeyWordsCommands + "\n";
                }
            } else {
                //print("else else else " . A_LoopField95)
                // this is THE else
                if (lineDone != 1) {
                    if (skipLeftCuleyForFuncPLS != 1) {
                        if (SubStr(Trim(StrLower(A_LoopField95)), 1, 1) == Chr(125)) {
                            htCode += Chr(125) + "\n";
                        } else {
                            if (htCodeAcurlyBraceAddSomeVrasFixLP == 1 && SubStr(Trim(StrLower(A_LoopField95)), 1, 1) == Chr(123)) {
                                htCodeAcurlyBraceAddSomeVrasFixLP = 0;
                                htCode += A_LoopField95 + "\n" + theFixTextLoopLP + "\n";
                            } else {
                                if (htCodeAcurlyBraceAddSomeVrasFixNL == 1 && SubStr(Trim(StrLower(A_LoopField95)), 1, 1) == Chr(123)) {
                                    htCodeAcurlyBraceAddSomeVrasFixNL = 0;
                                    htCode += A_LoopField95 + "\n" + theFixTextLoopNL + "\n";
                                } else {
                                    htCode += A_LoopField95 + "\n";
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
                items97 = LoopParseFunc(htCodeLoopfixa, "\n", "\r")
                for (let A_Index97 = 0; A_Index97 < items97.length + 0; A_Index97++) {
                    const A_LoopField97 = items97[A_Index97 - 0];
                    sstr123 = A_LoopField97;
                    fixLoopLokingFor = A_LoopField97;
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
                        items98 = LoopParseFunc(htCode, "\n", "\r")
                        for (let A_Index98 = 0; A_Index98 < items98.length + 0; A_Index98++) {
                            const A_LoopField98 = items98[A_Index98 - 0];
                            //MsgBox, dsfgsdefgesrdg1
                            //MsgBox, |%A_LoopField98%|`n|%fixLoopLokingFor%|
                            if (InStr(A_LoopField98, fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 1
                            }
                            if (SubStr(Trim(A_LoopField98), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField98 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(s);
                                //MsgBox, % out1z
                                //MsgBox, do we came here 2
                                fixLoopLokingForNum = 0;
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField98
                                dontSaveStr = 1;
                                ALoopField = A_LoopField98;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + "\n";
                            }
                            if (inTarget == 1 && InStr(A_LoopField98, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField98, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField98, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField98), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField98, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField98, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField98, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField98, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField98
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField98 + "\n";
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField98;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                                out4758686d86d86d86578991a += ALoopField + "\n";
                            }
                            if (inTarget == 1 && InStr(A_LoopField98, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1) {
                                //MsgBox, % A_LoopField98
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField98 + "\n";
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
                        items99 = LoopParseFunc(htCode, "\n", "\r")
                        for (let A_Index99 = 0; A_Index99 < items99.length + 0; A_Index99++) {
                            const A_LoopField99 = items99[A_Index99 - 0];
                            if (InStr(A_LoopField99 , fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 3
                            }
                            if (SubStr(Trim(A_LoopField99), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField99 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(s);
                                //MsgBox, % out1z
                                fixLoopLokingForNum = 0;
                                //MsgBox, do we came here 4
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField99
                                dontSaveStr = 1;
                                ALoopField = A_LoopField99;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + "\n";
                            }
                            if (inTarget == 1 && InStr(A_LoopField99, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField99, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField99, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField99), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField99, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField99, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField99, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField99, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField99
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField99 + "\n";
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField99;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordALoopField + "\\d*", "" + keyWordALoopField + "" + out1z);
                                out4758686d86d86d86578991a += ALoopField + "\n";
                            }
                            if ((inTarget == 1 && InStr(A_LoopField99, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1)) {
                                //MsgBox, % A_LoopField99
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField99 + "\n";
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
                items100 = LoopParseFunc(htCode, "\n", "\r")
                for (let A_Index100 = 0; A_Index100 < items100.length + 0; A_Index100++) {
                    const A_LoopField100 = items100[A_Index100 - 0];
                    ignore = 0;
                    if (SubStr(Trim(A_LoopField100), 1, 4) == "for ") {
                        if (hold == 1 && holdText == A_LoopField100) {
                            ignore = 1;
                        } else {
                            holdText = A_LoopField100;
                            hold = 1;
                        }
                    }
                    if (!ignore) {
                        out4758686d86dgt8r754444444 += A_LoopField100 + "\n";
                    }
                }
                out4758686d86dgt8r754444444 = StringTrimRight(out4758686d86dgt8r754444444, 1);
                htCode = out4758686d86dgt8r754444444;
            }
            htCodeOut1234565432 = "";
            items101 = LoopParseFunc(htCode, "\n", "\r")
            for (let A_Index101 = 0; A_Index101 < items101.length + 0; A_Index101++) {
                const A_LoopField101 = items101[A_Index101 - 0];
                out = A_LoopField101;
                if (!InStr(out, "|itsaersdtgtgfergsdgfsegdfsedAA|")) {
                    htCodeOut1234565432 += out + "\n";
                }
            }
            htCode = StringTrimRight(htCodeOut1234565432, 1);
        }
    } else {
        htCode = code;
    }
    if (COUNT_programmingBlock_InTheTranspiledLang != 0) {
        for (let A_Index102 = 0; A_Index102 < COUNT_programmingBlock_InTheTranspiledLang + 0; A_Index102++) {
            htCode = StrReplace(htCode, "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(A_Index102 + 1) + "AA", programmingBlock_InTheTranspiledLang[A_Index102]);
        }
    }
    if (langToConvertTo == "cpp") {
        if (COUNT_programmingBlock_CPP != 0) {
            for (let A_Index103 = 0; A_Index103 < COUNT_programmingBlock_CPP + 0; A_Index103++) {
                htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index103 + 1) + "AA", programmingBlock_CPP[A_Index103]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CPP != 0) {
            for (let A_Index104 = 0; A_Index104 < COUNT_programmingBlock_CPP + 0; A_Index104++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index104 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCPP + "\n" + programmingBlock_CPP[A_Index104] + "\n" + keyWordCodeInTheTranspiledLangEndCPP);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index104 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "py") {
        if (COUNT_programmingBlock_PY != 0) {
            for (let A_Index105 = 0; A_Index105 < COUNT_programmingBlock_PY + 0; A_Index105++) {
                htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index105 + 1) + "AA", programmingBlock_PY[A_Index105]);
            }
        }
    } else {
        if (COUNT_programmingBlock_PY != 0) {
            for (let A_Index106 = 0; A_Index106 < COUNT_programmingBlock_PY + 0; A_Index106++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index106 + 1) + "AA", keyWordCodeInTheTranspiledLangStartPY + "\n" + programmingBlock_PY[A_Index106] + "\n" + keyWordCodeInTheTranspiledLangEndPY);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index106 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "js") {
        if (COUNT_programmingBlock_JS != 0) {
            for (let A_Index107 = 0; A_Index107 < COUNT_programmingBlock_JS + 0; A_Index107++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index107 + 1) + "AA", programmingBlock_JS[A_Index107]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JS != 0) {
            for (let A_Index108 = 0; A_Index108 < COUNT_programmingBlock_JS + 0; A_Index108++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index108 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJS + "\n" + programmingBlock_JS[A_Index108] + "\n" + keyWordCodeInTheTranspiledLangEndJS);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index108 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "go") {
        if (COUNT_programmingBlock_GO != 0) {
            for (let A_Index109 = 0; A_Index109 < COUNT_programmingBlock_GO + 0; A_Index109++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index109 + 1) + "AA", programmingBlock_GO[A_Index109]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GO != 0) {
            for (let A_Index110 = 0; A_Index110 < COUNT_programmingBlock_GO + 0; A_Index110++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index110 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGO + "\n" + programmingBlock_GO[A_Index110] + "\n" + keyWordCodeInTheTranspiledLangEndGO);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index110 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "lua") {
        if (COUNT_programmingBlock_LUA != 0) {
            for (let A_Index111 = 0; A_Index111 < COUNT_programmingBlock_LUA + 0; A_Index111++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index111 + 1) + "AA", programmingBlock_LUA[A_Index111]);
            }
        }
    } else {
        if (COUNT_programmingBlock_LUA != 0) {
            for (let A_Index112 = 0; A_Index112 < COUNT_programmingBlock_LUA + 0; A_Index112++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index112 + 1) + "AA", keyWordCodeInTheTranspiledLangStartLUA + "\n" + programmingBlock_LUA[A_Index112] + "\n" + keyWordCodeInTheTranspiledLangEndLUA);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index112 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "cs") {
        if (COUNT_programmingBlock_CS != 0) {
            for (let A_Index113 = 0; A_Index113 < COUNT_programmingBlock_CS + 0; A_Index113++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index113 + 1) + "AA", programmingBlock_CS[A_Index113]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CS != 0) {
            for (let A_Index114 = 0; A_Index114 < COUNT_programmingBlock_CS + 0; A_Index114++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index114 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCS + "\n" + programmingBlock_CS[A_Index114] + "\n" + keyWordCodeInTheTranspiledLangEndCS);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index114 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "java") {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (let A_Index115 = 0; A_Index115 < COUNT_programmingBlock_JAVA + 0; A_Index115++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index115 + 1) + "AA", programmingBlock_JAVA[A_Index115]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (let A_Index116 = 0; A_Index116 < COUNT_programmingBlock_JAVA + 0; A_Index116++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index116 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJAVA + "\n" + programmingBlock_JAVA[A_Index116] + "\n" + keyWordCodeInTheTranspiledLangEndJAVA);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index116 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "kt") {
        if (COUNT_programmingBlock_KT != 0) {
            for (let A_Index117 = 0; A_Index117 < COUNT_programmingBlock_KT + 0; A_Index117++) {
                htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index117 + 1) + "AA", programmingBlock_KT[A_Index117]);
            }
        }
    } else {
        if (COUNT_programmingBlock_KT != 0) {
            for (let A_Index118 = 0; A_Index118 < COUNT_programmingBlock_KT + 0; A_Index118++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index118 + 1) + "AA", keyWordCodeInTheTranspiledLangStartKT + "\n" + programmingBlock_KT[A_Index118] + "\n" + keyWordCodeInTheTranspiledLangEndKT);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index118 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "rb") {
        if (COUNT_programmingBlock_RB != 0) {
            for (let A_Index119 = 0; A_Index119 < COUNT_programmingBlock_RB + 0; A_Index119++) {
                htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index119 + 1) + "AA", programmingBlock_RB[A_Index119]);
            }
        }
    } else {
        if (COUNT_programmingBlock_RB != 0) {
            for (let A_Index120 = 0; A_Index120 < COUNT_programmingBlock_RB + 0; A_Index120++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index120 + 1) + "AA", keyWordCodeInTheTranspiledLangStartRB + "\n" + programmingBlock_RB[A_Index120] + "\n" + keyWordCodeInTheTranspiledLangEndRB);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index120 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "nim") {
        if (COUNT_programmingBlock_NIM != 0) {
            for (let A_Index121 = 0; A_Index121 < COUNT_programmingBlock_NIM + 0; A_Index121++) {
                htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index121 + 1) + "AA", programmingBlock_NIM[A_Index121]);
            }
        }
    } else {
        if (COUNT_programmingBlock_NIM != 0) {
            for (let A_Index122 = 0; A_Index122 < COUNT_programmingBlock_NIM + 0; A_Index122++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index122 + 1) + "AA", keyWordCodeInTheTranspiledLangStartNIM + "\n" + programmingBlock_NIM[A_Index122] + "\n" + keyWordCodeInTheTranspiledLangEndNIM);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index122 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "ahk") {
        if (COUNT_programmingBlock_AHK != 0) {
            for (let A_Index123 = 0; A_Index123 < COUNT_programmingBlock_AHK + 0; A_Index123++) {
                htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index123 + 1) + "AA", programmingBlock_AHK[A_Index123]);
            }
        }
    } else {
        if (COUNT_programmingBlock_AHK != 0) {
            for (let A_Index124 = 0; A_Index124 < COUNT_programmingBlock_AHK + 0; A_Index124++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index124 + 1) + "AA", keyWordCodeInTheTranspiledLangStartAHK + "\n" + programmingBlock_AHK[A_Index124] + "\n" + keyWordCodeInTheTranspiledLangEndAHK);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index124 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "swift") {
        if (COUNT_programmingBlock_SWIFT != 0) {
            for (let A_Index125 = 0; A_Index125 < COUNT_programmingBlock_SWIFT + 0; A_Index125++) {
                htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index125 + 1) + "AA", programmingBlock_SWIFT[A_Index125]);
            }
        }
    } else {
        if (COUNT_programmingBlock_SWIFT != 0) {
            for (let A_Index126 = 0; A_Index126 < COUNT_programmingBlock_SWIFT + 0; A_Index126++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index126 + 1) + "AA", keyWordCodeInTheTranspiledLangStartSWIFT + "\n" + programmingBlock_SWIFT[A_Index126] + "\n" + keyWordCodeInTheTranspiledLangEndSWIFT);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index126 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "dart") {
        if (COUNT_programmingBlock_DART != 0) {
            for (let A_Index127 = 0; A_Index127 < COUNT_programmingBlock_DART + 0; A_Index127++) {
                htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index127 + 1) + "AA", programmingBlock_DART[A_Index127]);
            }
        }
    } else {
        if (COUNT_programmingBlock_DART != 0) {
            for (let A_Index128 = 0; A_Index128 < COUNT_programmingBlock_DART + 0; A_Index128++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index128 + 1) + "AA", keyWordCodeInTheTranspiledLangStartDART + "\n" + programmingBlock_DART[A_Index128] + "\n" + keyWordCodeInTheTranspiledLangEndDART);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index128 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "ts") {
        if (COUNT_programmingBlock_TS != 0) {
            for (let A_Index129 = 0; A_Index129 < COUNT_programmingBlock_TS + 0; A_Index129++) {
                htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index129 + 1) + "AA", programmingBlock_TS[A_Index129]);
            }
        }
    } else {
        if (COUNT_programmingBlock_TS != 0) {
            for (let A_Index130 = 0; A_Index130 < COUNT_programmingBlock_TS + 0; A_Index130++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index130 + 1) + "AA", keyWordCodeInTheTranspiledLangStartTS + "\n" + programmingBlock_TS[A_Index130] + "\n" + keyWordCodeInTheTranspiledLangEndTS);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index130 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "groovy") {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (let A_Index131 = 0; A_Index131 < COUNT_programmingBlock_GROOVY + 0; A_Index131++) {
                htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index131 + 1) + "AA", programmingBlock_GROOVY[A_Index131]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (let A_Index132 = 0; A_Index132 < COUNT_programmingBlock_GROOVY + 0; A_Index132++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index132 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGROOVY + "\n" + programmingBlock_GROOVY[A_Index132] + "\n" + keyWordCodeInTheTranspiledLangEndGROOVY);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index132 + 1) + "AA", "\n");
                }
            }
        }
    }
    //;;;;;;;;;;
    if (langToConvertTo == langFileExtension_2) {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (let A_Index133 = 0; A_Index133 < COUNT_programmingBlock_HTVM + 0; A_Index133++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index133 + 1) + "AA", programmingBlock_HTVM[A_Index133]);
            }
        }
    } else {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (let A_Index134 = 0; A_Index134 < COUNT_programmingBlock_HTVM + 0; A_Index134++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index134 + 1) + "AA", "\n");
            }
        }
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var ADD_ALL_programmingBlock_HTVMsyntax = "";
    if (COUNT_programmingBlock_HTVMsyntax != 0) {
        isNotHTVMfileEXTRA_INT = 1;
        for (let A_Index135 = 0; A_Index135 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index135++) {
            ADD_ALL_programmingBlock_HTVMsyntax += programmingBlock_HTVMsyntax[A_Index135] + "\n";
        }
        ADD_ALL_programmingBlock_HTVMsyntax = StringTrimRight(ADD_ALL_programmingBlock_HTVMsyntax, 1);
        ADD_ALL_programmingBlock_HTVMsyntax = compiler(ADD_ALL_programmingBlock_HTVMsyntax, allInstructionFile, "full", langToConvertToParam);
        isNotHTVMfileEXTRA_INT = 0;
        isNotHTVMfile2 = 1;
        for (let A_Index136 = 0; A_Index136 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index136++) {
            htCode = StrReplace(htCode, "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(A_Index136 + 1) + "AA", compiler(programmingBlock_HTVMsyntax[A_Index136], allInstructionFile, "full", langToConvertToParam));
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
        print("\n" + isNotHTVMfileEXTRA_LIB_INFO + "\n");
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
        print("\n" + isNotHTVMfileEXTRA_FUNCS_INFO + "\n");
        print("\n");
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
            items137 = LoopParseFunc(htCode, "\n", "\r")
            for (let A_Index137 = 0; A_Index137 < items137.length + 0; A_Index137++) {
                const A_LoopField137 = items137[A_Index137 - 0];
                if (Trim(A_LoopField137) == keyWordCurlyBraceClose_2) {
                    fixLuaAndRuby += StrReplace(A_LoopField137, keyWordCurlyBraceClose_2, Trim(keyWordEnd_2)) + "\n";
                }
                else if (SubStrLastChars(A_LoopField137, 2) == " " + keyWordCurlyBraceOpen_2) {
                    fixLuaAndRuby += StringTrimRight(A_LoopField137, 2) + "\n";
                } else {
                    fixLuaAndRuby += A_LoopField137 + "\n";
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
            items138 = LoopParseFunc(htCode, "\n", "\r")
            for (let A_Index138 = 0; A_Index138 < items138.length + 0; A_Index138++) {
                const A_LoopField138 = items138[A_Index138 - 0];
                if (Trim(A_LoopField138) == "}") {
                    fixLuaAndRuby += StrReplace(A_LoopField138, "}", "end") + "\n";
                }
                else if (SubStrLastChars(A_LoopField138, 2) == " {") {
                    fixLuaAndRuby += StringTrimRight(A_LoopField138, 2) + "\n";
                } else {
                    fixLuaAndRuby += A_LoopField138 + "\n";
                }
            }
            htCode = StringTrimRight(fixLuaAndRuby, 1);
        }
    }
    let nextWordEndFix = [];
    var nextWordEndFixOut = "";
    if (langToConvertTo == "lua" || langToConvertTo == "rb") {
        items139 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index139 = 0; A_Index139 < items139.length + 0; A_Index139++) {
            const A_LoopField139 = items139[A_Index139 - 0];
            nextWordEndFix.push(A_LoopField139);
        }
        nextWordEndFix.push(" ");
        items140 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index140 = 0; A_Index140 < items140.length + 0; A_Index140++) {
            const A_LoopField140 = items140[A_Index140 - 0];
            if (Trim(A_LoopField140) == "end" && SubStr(Trim(nextWordEndFix[A_Index140 + 1]), 1, StrLen("elseif ")) == "elseif " || Trim(A_LoopField140) == "end" && Trim(nextWordEndFix[A_Index140 + 1]) == "else") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField140 + "\n";
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    let nextWordEndFixRB = [];
    nextWordEndFixOut = "";
    if (langToConvertTo == "rb") {
        items141 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index141 = 0; A_Index141 < items141.length + 0; A_Index141++) {
            const A_LoopField141 = items141[A_Index141 - 0];
            nextWordEndFixRB.push(A_LoopField141);
        }
        nextWordEndFixRB.push(" ");
        items142 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index142 = 0; A_Index142 < items142.length + 0; A_Index142++) {
            const A_LoopField142 = items142[A_Index142 - 0];
            if (Trim(A_LoopField142) == "end" && SubStr(Trim(nextWordEndFixRB[A_Index142 + 1]), 1, StrLen("rescue ")) == "rescue " || Trim(A_LoopField142) == "end" && Trim(nextWordEndFixRB[A_Index142 + 1]) == "ensure") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField142 + "\n";
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == "go") {
        let fixGoManGoIsSoAnnoyingBroooFurure = [];
        items143 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index143 = 0; A_Index143 < items143.length + 0; A_Index143++) {
            const A_LoopField143 = items143[A_Index143 - 0];
            fixGoManGoIsSoAnnoyingBroooFurure.push(A_LoopField143);
        }
        fixGoManGoIsSoAnnoyingBroooFurure.push(" ");
        var fixGoManGoIsSoAnnoyingBroooSkip = 0;
        var fixGoManGoIsSoAnnoyingBroooCount = 0;
        var fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
        var fixGoManGoIsSoAnnoyingBrooo = "";
        items144 = LoopParseFunc(htCode, "\n", "\r")
        for (let A_Index144 = 0; A_Index144 < items144.length + 0; A_Index144++) {
            const A_LoopField144 = items144[A_Index144 - 0];
            if (Trim(A_LoopField144) == "}" && SubStr(Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index144 + 1]), 1, StrLen("else if ")) == "else if ") {
                fixGoManGoIsSoAnnoyingBroooSkip = 1;
                fixGoManGoIsSoAnnoyingBroooCount = 0;
                items145 = LoopParseFunc(fixGoManGoIsSoAnnoyingBroooFurure[A_Index144 + 1])
                for (let A_Index145 = 0; A_Index145 < items145.length + 0; A_Index145++) {
                    const A_LoopField145 = items145[A_Index145 - 0];
                    if (A_LoopField145 == " ") {
                        fixGoManGoIsSoAnnoyingBroooCount++;
                    } else {
                        break;
                    }
                }
                fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
                for (let A_Index146 = 0; A_Index146 < fixGoManGoIsSoAnnoyingBroooCount + 0; A_Index146++) {
                    fixGoManGoIsSoAnnoyingBroooCountSpaceses += " ";
                }
                fixGoManGoIsSoAnnoyingBrooo += fixGoManGoIsSoAnnoyingBroooCountSpaceses + "} " + Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index144 + 1]) + "\n";
            } else {
                if (fixGoManGoIsSoAnnoyingBroooSkip == 0) {
                    fixGoManGoIsSoAnnoyingBrooo += A_LoopField144 + "\n";
                }
                fixGoManGoIsSoAnnoyingBroooSkip = 0;
            }
        }
        htCode = StringTrimRight(fixGoManGoIsSoAnnoyingBrooo, 1);
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
    items147 = LoopParseFunc(instructions, "\n", "\r")
    for (let A_Index147 = 0; A_Index147 < items147.length + 0; A_Index147++) {
        const A_LoopField147 = items147[A_Index147 - 0];
        if (Trim(A_LoopField147) == "funcEND======================funcEND==============") {
            areWeInAFuncFromInstructions = 0;
            areWeInAFuncFromInstructionsLineNum = 0;
            if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                //MsgBox, % funcFuncHolder
                allFuncs.push(funcFuncHolder);
            }
            correctLang = 0;
            funcFuncHolder = "";
        }
        if (areWeInAFuncFromInstructions == 1) {
            if (areWeInAFuncFromInstructionsLineNum == 1) {
                // name of the func
                funcLangHolder = StringTrimLeft(A_LoopField147, 5);
                if (Trim(funcLangHolder) == langToConvertTo) {
                    allFuncLang.push(Trim(funcLangHolder));
                    correctLang = 1;
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 2) {
                // name of the func
                funcNameHolder = StringTrimLeft(A_LoopField147, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allFuncNames.push(Trim(funcNameHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 3) {
                // all libs
                funcLibsHolder = StringTrimLeft(A_LoopField147, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allFuncLibs.push(Trim(funcLibsHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 4) {
                // func description
                funcDescriptionHolder = StringTrimLeft(A_LoopField147, 12);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allfuncDescription.push(Trim(funcDescriptionHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum >= 5) {
                // the full func
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    funcFuncHolder += A_LoopField147 + "\n";
                }
            }
            //MsgBox, % A_LoopField147
            areWeInAFuncFromInstructionsLineNum++;
        }
        if (Trim(A_LoopField147) == "func======================func==============") {
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
            htCode = htCode + "\n    return 0;\n}";
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
            htCode = htCode + "\n    }\n}";
            htCode = StrReplace(htCode, "static void Main(string[] args);", "static void Main(string[] args)");
        }
        if (langToConvertTo == "java") {
            htCode = htCode + "\n    }\n}";
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
    var jsHTMLdownCode = "</script>\n</body>\n</html>";
    var includeLibsInCppIf = 0;
    var allFuncsToPutAtTop = Chr(10);
    var allLibsToPutAtTop = "";
    if (!(allFuncNames.length <= 0)) {
        for (let A_Index148 = 0; A_Index148 < allFuncNames.length + 0; A_Index148++) {
            if (InStr(htCode, allFuncNames[A_Index148]) + "(") {
                //MsgBox, % allFuncNames[A_Index148]
                allFuncsToPutAtTop += allFuncs[A_Index148] + "\n";
                if (Trim(allFuncLibs[A_Index148]) != "null") {
                    allLibsToPutAtTop += allFuncLibs[A_Index148] + "|";
                }
            }
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTop, 1);
        var allLibsToPutAtTopTEMP;
        items149 = LoopParseFunc(allLibsToPutAtTop, "|")
        for (let A_Index149 = 0; A_Index149 < items149.length + 0; A_Index149++) {
            const A_LoopField149 = items149[A_Index149 - 0];
            allLibsToPutAtTopTEMP += A_LoopField149 + "\n";
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTopTEMP, 1);
        includeLibsInCppIf = 1;
        if (langToConvertTo == "cpp") {
            allLibsToPutAtTop = "#include <iostream>\n#include <sstream>\n#include <string>\n#include <cstdint>\n#include <algorithm>\n#include <vector>\n#include <any>\n#include <optional>\n" + allLibsToPutAtTop;
        }
        if (langToConvertTo == "cs") {
            allLibsToPutAtTop = "using System;\n" + allLibsToPutAtTop;
        }
        allLibsToPutAtTop = Sort(allLibsToPutAtTop, "U");
        allLibsToPutAtTop = StrReplace(allLibsToPutAtTop, "~~~", "\n");
        if (isNotHTVMfileEXTRA_INT == 1) {
            isNotHTVMfileEXTRA_LIB_INFO = allLibsToPutAtTop;
            isNotHTVMfileEXTRA_FUNCS_INFO = allFuncsToPutAtTop;
        }
        if (isNotHTVMfile2 == 0) {
            if (langToConvertTo == "cs" || langToConvertTo == "java") {
                htCode = "\n" + allFuncsToPutAtTop + "\n" + htCode;
            } else {
                if (langToConvertTo != "js") {
                    htCode = allLibsToPutAtTop + "\n" + allFuncsToPutAtTop + "\n" + htCode;
                } else {
                    if (useJavaScriptInAfullHTMLfile != "on") {
                        htCode = allLibsToPutAtTop + "\n" + allFuncsToPutAtTop + "\n" + htCode;
                    } else {
                        htCode = "\n" + allFuncsToPutAtTop + "\n" + htCode;
                    }
                }
            }
        }
        if (langToConvertTo == "cs") {
            htCode = allLibsToPutAtTop + "\nclass Program\n{\n" + htCode;
        }
        if (langToConvertTo == "java") {
            htCode = allLibsToPutAtTop + "\npublic class Main\n{\n" + htCode;
        }
        if (langToConvertTo == "go") {
            htCode = "package main\nimport (\n" + htCode;
        }
    }
    for (let A_Index150 = 0; A_Index150 < theIdNumOfThe34 + 0; A_Index150++) {
        if (theIdNumOfThe34 == A_Index150 + 1) {
            if (langToConvertTo == langFileExtension_2) {
                if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index150 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index150 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                } else {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index150 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index150 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                }
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index150 + 1) + Chr(65) + Chr(65), theIdNumOfThe34theVar[A_Index150 + 1] + Chr(34));
            }
        } else {
            if (langToConvertTo == langFileExtension_2) {
                if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index150 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index150 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2));
                } else {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index150 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index150 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2));
                }
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index150 + 1) + Chr(65) + Chr(65), theIdNumOfThe34theVar[A_Index150 + 1]);
            }
        }
    }
    if (langToConvertTo == langFileExtension_2) {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, keyWordEscpaeChar_2 + Chr(34));
    } else {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, Chr(92) + Chr(34));
    }
    htCode = StrReplace(htCode, "std::string(" + Chr(34) + Chr(34) + ";),", "std::string(" + Chr(34) + Chr(34) + "),");
    var jsHTMLupCode = "<!doctype html>\n<html lang=" + Chr(34) + "en" + Chr(34) + ">\n    <head>\n        <meta charset=" + Chr(34) + "UTF-8" + Chr(34) + " />\n        <meta name=" + Chr(34) + "viewport" + Chr(34) + " content=" + Chr(34) + "width=device-width, initial-scale=1.0" + Chr(34) + " />\n        <title>HTVM</title>\n        <style>\n            body {\n                background-color: #202020;\n                font-family:\n                    " + Chr(34) + "Open Sans" + Chr(34) + ",\n                    -apple-system,\n                    BlinkMacSystemFont,\n                    " + Chr(34) + "Segoe UI" + Chr(34) + ",\n                    Roboto,\n                    Oxygen-Sans,\n                    Ubuntu,\n                    Cantarell,\n                    " + Chr(34) + "Helvetica Neue" + Chr(34) + ",\n                    Helvetica,\n                    Arial,\n                    sans-serif;\n            }\n        </style>\n" + allLibsToPutAtTop + "\n</head>\n    <body>\n<script>";
    if (isNotHTVMfile2 == 0) {
        if (useJavaScriptInAfullHTMLfile == "on" && langToConvertTo == "js") {
            htCode = jsHTMLupCode + "\n" + htCode + "\n" + jsHTMLdownCode;
        }
        if (langToConvertTo == "cpp" && includeLibsInCppIf == 0) {
            htCode = "#include <iostream>\n#include <sstream>\n#include <any>\n#include <string>\n#include <cstdint>\n#include <algorithm>\n#include <vector>\n\n" + htCode;
        }
        if (langToConvertTo == "cs") {
            htCode = "\n" + htCode;
        }
        if (langToConvertTo == "ahk") {
            htCode = "#EscapeChar \\\n" + htCode;
        }
        if (langToConvertTo == "swift") {
            htCode = "import Foundation\n" + htCode;
        }
        if (langToConvertTo == langFileExtension_2) {
            if (SubStr(htCode, 1, 1) == "\n") {
                htCode = StringTrimLeft(htCode, 1);
            }
        }
    }
    print(htCode);
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
async function HTVMv2() {
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
    items151 = LoopParseFunc(str0)
    for (let A_Index151 = 0; A_Index151 < items151.length + 0; A_Index151++) {
        const A_LoopField151 = items151[A_Index151 - 0];
        str00 = Trim(A_LoopField151);
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
        items152 = LoopParseFunc(allArgs, "\n", "\r")
        for (let A_Index152 = 0; A_Index152 < items152.length + 0; A_Index152++) {
            const A_LoopField152 = items152[A_Index152 - 0];
            if (A_Index152 == 0) {
                numOfParams++;
                argCODE = FileRead(Trim(A_LoopField152));
                argCODEfile = Trim(A_LoopField152);
            }
            else if (A_Index152 == 1) {
                numOfParams++;
                argHTVMinstr = Trim(A_LoopField152);
            }
            else if (A_Index152 == 2) {
                numOfParams++;
                argLangTo = Trim(A_LoopField152);
            } else {
                numOfParams++;
                argHTVMinstrMORE.push(Trim(A_LoopField152));
            }
        }
        print("===============123431234===========start=====");
        for (let A_Index153 = 0; A_Index153 < argHTVMinstrMORE.length + 0; A_Index153++) {
            print(argHTVMinstrMORE[A_Index153]);
        }
        print("===============123431234==========end======");
        print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        if (SubStrLastChars(argCODEfile, 4) == ".cpp" || SubStrLastChars(argCODEfile, 3) == ".py" || SubStrLastChars(argCODEfile, 3) == ".js" || SubStrLastChars(argCODEfile, 3) == ".go" || SubStrLastChars(argCODEfile, 4) == ".lua" || SubStrLastChars(argCODEfile, 3) == ".cs" || SubStrLastChars(argCODEfile, 5) == ".java" || SubStrLastChars(argCODEfile, 3) == ".kt" || SubStrLastChars(argCODEfile, 3) == ".rb" || SubStrLastChars(argCODEfile, 4) == ".nim" || SubStrLastChars(argCODEfile, 4) == ".ahk" || SubStrLastChars(argCODEfile, 6) == ".swift" || SubStrLastChars(argCODEfile, 5) == ".dart" || SubStrLastChars(argCODEfile, 3) == ".ts" || SubStrLastChars(argCODEfile, 7) == ".groovy" || SubStrLastChars(argCODEfile, StrLen("." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)))) == "." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)) && numOfParams == 2) {
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
            else if (SubStrLastChars(argCODEfile, StrLen("." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)))) == "." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2))) {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)));
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            } else {
                print("INVALID LANG!!!");
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
        print("JS");
    }
}
async function main() {
    HTVMv2();
}
main();
