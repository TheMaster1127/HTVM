

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
let argHTVMinstrMOVE = [];
var extraCodeReturned = "";
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
var keyWordIncludeInTheTranspiledLang = "";
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
var keyWordCodeInTheTranspiledLangStartSCALA = "";
var keyWordCodeInTheTranspiledLangEndSCALA = "";
var keyWordCodeInTheTranspiledLangStartGROOVY = "";
var keyWordCodeInTheTranspiledLangEndGROOVY = "";
var keyWordCodeInTheTranspiledLangStartHTVM = "";
var keyWordCodeInTheTranspiledLangEndHTVM = "";
var keyWordCodeInHTVMstart = "";
var keyWordCodeInHTVMend = "";
var keyWordCodeInOtherHTVMsyntaxStart = "";
var keyWordCodeInOtherHTVMsyntaxEnd = "";
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
var keyWordSwitch = "";
var keyWordSwitchCase = "";
var keyWordSwitchDefault = "";
var keyWordWhileLoop = "";
var keyWordForLoop = "";
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
var keyWordJavaScriptVar = "";
var keyWordJavaScriptLet = "";
var keyWordJavaScriptConst = "";
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
var keyWordAllianceEndExtraInfo = "";
var keyWordCrewEndExtraInfo = "";
var keyWordMethodEndExtraInfo = "";
var keyWordDefObjEndExtraInfo = "";
var keyWordIFEndExtraInfo = "";
var keyWordElseIfEndExtraInfo = "";
var keyWordElseEndExtraInfo = "";
var keyWordSwitchEndExtraInfo = "";
var keyWordSwitchCaseEndExtraInfo = "";
var keyWordWhileLoopEndExtraInfo = "";
var keyWordForLoopEndExtraInfo = "";
var keyWordLoopInfiniteEndExtraInfo = "";
var keyWordLoopEndExtraInfo = "";
var keyWordLoopParseEndExtraInfo = "";
var keyWordFuncEndExtraInfo = "";
var keyWordTryEndExtraInfo = "";
var keyWordCatchEndExtraInfo = "";
var keyWordFinallyEndExtraInfo = "";
var useFuncKeyWord = "";
var useCurlyBraces = "";
var useEnd = "";
var useEndExtraInfo = "";
var useSemicolon = "";
var theSemicolon = "";
var theColon = "";
var useParentheses = "";
var usePrefixTypeForTypeDefinition = "";
var usePostfixTypeForTypeDefinition = "";
var usePythonicColonSyntax = "";
var useInJavaScriptAlwaysUseVar = "";
var useJavaScriptInAfullHTMLfile = "";
var useJavaScriptAmainFuncDef = "";
var useJavaScriptAllFuncsAreAsync = "";
var useJavaScriptAlwaysTripleEqual = "";
var out_KeyWordsCommands;
var outTrimCode;
var htCode;
var outVarOperator = "";
var lineDone = 0;
var areWeInAFuncFromInstructions = 0;
var areWeInAFuncFromInstructionsLineNum = 0;
var theCppVarForErrors = "jhku-dfsds-ds-d-ffdsf-sdfsfdsedsf";
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
                if (A_Index2 == 1) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField2 + ", ")) == StrLower(A_LoopField2 + ", ")) {
                        //MsgBox, true
                        return "true";
                    }
                }
                if (A_Index2 == 1) {
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
                if (A_Index4 == 1) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField4 + ", ")) == StrLower(A_LoopField4 + ", ")) {
                        //MsgBox, true
                        keyWordsCommandsNumLine = AIndex;
                        break;
                    }
                }
                if (A_Index4 == 1) {
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
        var theCodeCommandNum = 1;
        var outConstuctTheOutFromTheCommandsLineTranspile = 0;
        var outConstuctTheOutFromTheCommandsLineTranspileText = "";
        var semicolon = "";
        if (langToConvertTo != "py") {
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
                    if (A_Index7 == 1) {
                        outConstuctTheOutFromTheCommandsFucnName = A_LoopField7;
                    }
                    else if (A_Index7 == 2) {
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
                    else if (A_Index7 == 3) {
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
    var allDelimiters = " ()[].,;:'!&|=<>+-*/^%~" + Chr(34);
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
    var line = 0;
    var stripped = 0;
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
        //MsgBox, % indent
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
                resultOut += A_LoopField29 + " {\n";
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
                        addSpacesAtTheBegginig += A_LoopField32;
                    }
                }
                resultOut += addSpacesAtTheBegginig + "} else {\n";
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
    items34 = LoopParseFunc(fullARRAYstr, "|")
    for (let A_Index34 = 0; A_Index34 < items34.length + 0; A_Index34++) {
        const A_LoopField34 = items34[A_Index34 - 0];
        if (Trim(A_LoopField34) != "") {
            outFormatHELP1 = StrSplit(A_LoopField34, ":", 1);
            outFormatHELP2 = StrSplit(A_LoopField34, ":", 2);
            items35 = LoopParseFunc(outFormatHELP2, ",")
            for (let A_Index35 = 0; A_Index35 < items35.length + 0; A_Index35++) {
                const A_LoopField35 = items35[A_Index35 - 0];
                outFormat += outFormatHELP1 + "." + A_LoopField35 + "|";
            }
        }
    }
    outFormat = StringTrimRight(outFormat, 1);
    items36 = LoopParseFunc(outFormat, "|")
    for (let A_Index36 = 0; A_Index36 < items36.length + 0; A_Index36++) {
        const A_LoopField36 = items36[A_Index36 - 0];
        if (Trim(A_LoopField36) != "") {
            if (StrSplit(Trim(A_LoopField36), "[", 1) == Trim(FromPath)) {
                outType = StrSplit(Trim(A_LoopField36), "[", 2);
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
    items37 = LoopParseFunc(THESTR, ".")
    for (let A_Index37 = 0; A_Index37 < items37.length + 0; A_Index37++) {
        const A_LoopField37 = items37[A_Index37 - 0];
        count12345++;
    }
    items38 = LoopParseFunc(THESTR, ".")
    for (let A_Index38 = 0; A_Index38 < items38.length + 0; A_Index38++) {
        const A_LoopField38 = items38[A_Index38 - 0];
        if (count12345 == A_Index38) {
            break;
        } else {
            THESTRout += Trim(A_LoopField38) + ".";
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
    items39 = LoopParseFunc(theSringOSPlineARRAYstrstrSTR, "|")
    for (let A_Index39 = 0; A_Index39 < items39.length + 0; A_Index39++) {
        const A_LoopField39 = items39[A_Index39 - 0];
        if (Trim(StrSplit(A_LoopField39, ":", 1)) == Trim(ALoopField)) {
            return STR(A_Index39);
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
    HELPHoldOSPdethodNamePath = StringTrimRight(HoldOSPdethodNamePath, 1);
    items40 = LoopParseFunc(theSringOSPline, "|")
    for (let A_Index40 = 0; A_Index40 < items40.length + 0; A_Index40++) {
        const A_LoopField40 = items40[A_Index40 - 0];
        str_1 += Trim(StrSplit(A_LoopField40, ":", 1)) + "\n";
        str_5 = Trim(StrSplit(A_LoopField40, ":", 1));
        str_6 = Trim(StrSplit(A_LoopField40, ":", 2));
        items41 = LoopParseFunc(str_6, ",")
        for (let A_Index41 = 0; A_Index41 < items41.length + 0; A_Index41++) {
            const A_LoopField41 = items41[A_Index41 - 0];
            str_1 += str_5 + "." + Trim(StrSplit(A_LoopField41, "[", 1)) + "[" + STR(A_Index41) + "]\n";
        }
    }
    str_1 += StrReplace(HELPHoldOSPdethodNamePath, "|", "\n");
    var shortestLine = "";
    var currentLine = "";
    var currentLength = 0;
    var minLength = 0;
    var tempStr = "";
    // Sorting by repeatedly finding and appending the shortest line
    for (let A_Index42 = 0; ; A_Index42++) {
        // Initialize variables to track the shortest line in this pass
        shortestLine = "";
        minLength = 999999;
        // Find the shortest line in str_1
        items43 = LoopParseFunc(str_1, "\n", "\r")
        for (let A_Index43 = 0; A_Index43 < items43.length + 0; A_Index43++) {
            const A_LoopField43 = items43[A_Index43 - 0];
            currentLine = A_LoopField43;
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
        items44 = LoopParseFunc(str_1, "\n", "\r")
        for (let A_Index44 = 0; A_Index44 < items44.length + 0; A_Index44++) {
            const A_LoopField44 = items44[A_Index44 - 0];
            if (A_LoopField44 != shortestLine) {
                tempStr += A_LoopField44 + "\n";
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
    items45 = LoopParseFunc(str_2, "\n", "\r")
    for (let A_Index45 = 0; A_Index45 < items45.length + 0; A_Index45++) {
        const A_LoopField45 = items45[A_Index45 - 0];
        lineCount++;
    }
    // Reverse the order by re-parsing and appending lines in reverse order
    for (let A_Index46 = 0; A_Index46 < lineCount + 0; A_Index46++) {
        // Inner loop to find the (lineCount - A_Index46 + 1)-th line
        index = lineCount - A_Index46 + 1;
        currentLine = "";
        lineNum = 0;
        items47 = LoopParseFunc(str_2, "\n", "\r")
        for (let A_Index47 = 0; A_Index47 < items47.length + 0; A_Index47++) {
            const A_LoopField47 = items47[A_Index47 - 0];
            lineNum++;
            if (lineNum == index) {
                currentLine = A_LoopField47;
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
    items48 = LoopParseFunc(str_2, "\n", "\r")
    for (let A_Index48 = 0; A_Index48 < items48.length + 0; A_Index48++) {
        const A_LoopField48 = items48[A_Index48 - 0];
        if (SubStr(A_LoopField48, 1, StrLen(keyWordFunc)) != keyWordFunc) {
            if (langToConvertTo == "cpp") {
                if (Trim(A_LoopField48) != "") {
                    if (InStr(str123, " += ")) {
                        str6 = " += ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48));
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48));
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48));
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48));
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    } else {
                        str123 = replaceTheOSPpathsRIGHT(str123, A_LoopField48);
                    }
                    //;;;;
                }
            } else {
                if (Trim(A_LoopField48) != "") {
                    str123 = replaceTheOSPpathsPY_JS(str123, A_LoopField48);
                }
            }
        }
    }
    return str123;
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
async function compiler(htCode, instructionFile, mode, langToConvertToParam = "") {
    extraCodeReturned = "";
    var allInstructionFile = Trim(FileRead(instructionFile));
    items49 = LoopParseFunc(allInstructionFile, "\n", "\r")
    for (let A_Index49 = 0; A_Index49 < items49.length + 0; A_Index49++) {
        const A_LoopField49 = items49[A_Index49 - 0];
        if (A_Index49 == 0) {
            langToConvertTo = Trim(A_LoopField49);
        }
        if (A_Index49 == 1) {
            langFileExtension = Trim(A_LoopField49);
        }
        if (A_Index49 == 2) {
            commands = Trim(A_LoopField49);
        }
        if (A_Index49 == 3) {
            keyWordAlliance = Trim(A_LoopField49);
        }
        if (A_Index49 == 4) {
            keyWordCrew = Trim(A_LoopField49);
        }
        if (A_Index49 == 5) {
            keyWordMethod = Trim(A_LoopField49);
        }
        if (A_Index49 == 6) {
            keyWordDefObj = Trim(A_LoopField49);
        }
        if (A_Index49 == 7) {
            keyWordPorp = Trim(A_LoopField49);
        }
        if (A_Index49 == 8) {
            keyWordThis = Trim(A_LoopField49);
        }
        if (A_Index49 == 9) {
            keyWordInclude = Trim(A_LoopField49);
        }
        if (A_Index49 == 10) {
            keyWordIncludeInTheTranspiledLang = Trim(A_LoopField49);
        }
        if (A_Index49 == 11) {
            keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField49);
        }
        if (A_Index49 == 12) {
            keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField49);
        }
        if (A_Index49 == 13) {
            keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField49);
        }
        if (A_Index49 == 14) {
            keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField49);
        }
        if (A_Index49 == 15) {
            keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField49);
        }
        if (A_Index49 == 16) {
            keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField49);
        }
        if (A_Index49 == 17) {
            keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField49);
        }
        if (A_Index49 == 18) {
            keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField49);
        }
        if (A_Index49 == 19) {
            keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField49);
        }
        if (A_Index49 == 20) {
            keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField49);
        }
        if (A_Index49 == 21) {
            keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField49);
        }
        if (A_Index49 == 22) {
            keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField49);
        }
        if (A_Index49 == 23) {
            keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField49);
        }
        if (A_Index49 == 24) {
            keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField49);
        }
        if (A_Index49 == 25) {
            keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField49);
        }
        if (A_Index49 == 26) {
            keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField49);
        }
        if (A_Index49 == 27) {
            keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField49);
        }
        if (A_Index49 == 28) {
            keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField49);
        }
        if (A_Index49 == 29) {
            keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField49);
        }
        if (A_Index49 == 30) {
            keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField49);
        }
        if (A_Index49 == 31) {
            keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField49);
        }
        if (A_Index49 == 32) {
            keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField49);
        }
        if (A_Index49 == 33) {
            keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField49);
        }
        if (A_Index49 == 34) {
            keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField49);
        }
        if (A_Index49 == 35) {
            keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField49);
        }
        if (A_Index49 == 36) {
            keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField49);
        }
        if (A_Index49 == 37) {
            keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField49);
        }
        if (A_Index49 == 38) {
            keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField49);
        }
        if (A_Index49 == 39) {
            keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField49);
        }
        if (A_Index49 == 40) {
            keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField49);
        }
        if (A_Index49 == 41) {
            keyWordCodeInTheTranspiledLangStartSCALA = Trim(A_LoopField49);
        }
        if (A_Index49 == 42) {
            keyWordCodeInTheTranspiledLangEndSCALA = Trim(A_LoopField49);
        }
        if (A_Index49 == 43) {
            keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField49);
        }
        if (A_Index49 == 44) {
            keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField49);
        }
        if (A_Index49 == 45) {
            keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField49);
        }
        if (A_Index49 == 46) {
            keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField49);
        }
        if (A_Index49 == 47) {
            keyWordCodeInHTVMstart = Trim(A_LoopField49);
        }
        if (A_Index49 == 48) {
            keyWordCodeInHTVMend = Trim(A_LoopField49);
        }
        if (A_Index49 == 49) {
            keyWordCodeInOtherHTVMsyntaxStart = Trim(A_LoopField49);
        }
        if (A_Index49 == 50) {
            keyWordCodeInOtherHTVMsyntaxEnd = Trim(A_LoopField49);
        }
        if (A_Index49 == 51) {
            keyWordCurlyBraceOpen = Trim(A_LoopField49);
        }
        if (A_Index49 == 52) {
            keyWordCurlyBraceClose = Trim(A_LoopField49);
        }
        if (A_Index49 == 53) {
            keyWordNull = Trim(A_LoopField49);
        }
        if (A_Index49 == 54) {
            keyWordTrue = Trim(A_LoopField49);
        }
        if (A_Index49 == 55) {
            keyWordFalse = Trim(A_LoopField49);
        }
        if (A_Index49 == 56) {
            keyWordVoid = Trim(A_LoopField49);
        }
        if (A_Index49 == 57) {
            keyWordDouble = Trim(A_LoopField49);
        }
        if (A_Index49 == 58) {
            keyWordChar = Trim(A_LoopField49);
        }
        if (A_Index49 == 59) {
            keyWordUint8 = Trim(A_LoopField49);
        }
        if (A_Index49 == 60) {
            keyWordUint16 = Trim(A_LoopField49);
        }
        if (A_Index49 == 61) {
            keyWordUint32 = Trim(A_LoopField49);
        }
        if (A_Index49 == 62) {
            keyWordUint64 = Trim(A_LoopField49);
        }
        if (A_Index49 == 63) {
            keyWordINT = Trim(A_LoopField49);
        }
        if (A_Index49 == 64) {
            keyWordSTR = Trim(A_LoopField49);
        }
        if (A_Index49 == 65) {
            keyWordBOOL = Trim(A_LoopField49);
        }
        if (A_Index49 == 66) {
            keyWordFLOAT = Trim(A_LoopField49);
        }
        if (A_Index49 == 67) {
            keyWordINT8 = Trim(A_LoopField49);
        }
        if (A_Index49 == 68) {
            keyWordINT16 = Trim(A_LoopField49);
        }
        if (A_Index49 == 69) {
            keyWordINT32 = Trim(A_LoopField49);
        }
        if (A_Index49 == 70) {
            keyWordINT64 = Trim(A_LoopField49);
        }
        if (A_Index49 == 71) {
            keyWordIF = Trim(A_LoopField49);
        }
        if (A_Index49 == 72) {
            keyWordElseIf = Trim(A_LoopField49);
        }
        if (A_Index49 == 73) {
            keyWordElse = Trim(A_LoopField49);
        }
        if (A_Index49 == 74) {
            keyWordSwitch = Trim(A_LoopField49);
        }
        if (A_Index49 == 75) {
            keyWordSwitchCase = Trim(A_LoopField49);
        }
        if (A_Index49 == 76) {
            keyWordSwitchDefault = Trim(A_LoopField49);
        }
        if (A_Index49 == 77) {
            keyWordWhileLoop = Trim(A_LoopField49);
        }
        if (A_Index49 == 78) {
            keyWordForLoop = Trim(A_LoopField49);
        }
        if (A_Index49 == 79) {
            keyWordLoopInfinite = Trim(A_LoopField49);
        }
        if (A_Index49 == 80) {
            keyWordLoop = Trim(A_LoopField49);
        }
        if (A_Index49 == 81) {
            keyWordLoopParse = Trim(A_LoopField49);
        }
        if (A_Index49 == 82) {
            keyWordContinue = Trim(A_LoopField49);
        }
        if (A_Index49 == 83) {
            keyWordBreak = Trim(A_LoopField49);
        }
        if (A_Index49 == 84) {
            keyWordFunc = Trim(A_LoopField49);
        }
        if (A_Index49 == 85) {
            keyWordAwait = Trim(A_LoopField49);
        }
        if (A_Index49 == 86) {
            keyWordAsync = Trim(A_LoopField49);
        }
        if (A_Index49 == 87) {
            keyWordThrow = Trim(A_LoopField49);
        }
        if (A_Index49 == 88) {
            keyWordErrorMsg = Trim(A_LoopField49);
        }
        if (A_Index49 == 89) {
            keyWordTry = Trim(A_LoopField49);
        }
        if (A_Index49 == 90) {
            keyWordCatch = Trim(A_LoopField49);
        }
        if (A_Index49 == 91) {
            keyWordFinally = Trim(A_LoopField49);
        }
        if (A_Index49 == 92) {
            keyWordReturnStatement = Trim(A_LoopField49);
        }
        if (A_Index49 == 93) {
            keyWordArrayAppend = Trim(A_LoopField49);
        }
        if (A_Index49 == 94) {
            keyWordArrayPop = Trim(A_LoopField49);
        }
        if (A_Index49 == 95) {
            keyWordArraySize = Trim(A_LoopField49);
        }
        if (A_Index49 == 96) {
            keyWordArrayInsert = Trim(A_LoopField49);
        }
        if (A_Index49 == 97) {
            keyWordArrayRemove = Trim(A_LoopField49);
        }
        if (A_Index49 == 98) {
            keyWordArrayIndexOf = Trim(A_LoopField49);
        }
        if (A_Index49 == 99) {
            keyWordArrayDefinition = Trim(A_LoopField49);
        }
        if (A_Index49 == 100) {
            keyWordArrayOfIntegersDefinition = Trim(A_LoopField49);
        }
        if (A_Index49 == 101) {
            keyWordArrayOfStringsDefinition = Trim(A_LoopField49);
        }
        if (A_Index49 == 102) {
            keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField49);
        }
        if (A_Index49 == 103) {
            keyWordArrayOfBooleansDefinition = Trim(A_LoopField49);
        }
        if (A_Index49 == 104) {
            keyWordJavaScriptVar = Trim(A_LoopField49);
        }
        if (A_Index49 == 105) {
            keyWordJavaScriptLet = Trim(A_LoopField49);
        }
        if (A_Index49 == 106) {
            keyWordJavaScriptConst = Trim(A_LoopField49);
        }
        if (A_Index49 == 107) {
            keyWordEnd = Trim(A_LoopField49);
        }
        if (A_Index49 == 108) {
            keyWordGlobal = Trim(A_LoopField49);
        }
        if (A_Index49 == 109) {
            keyWordComment = Trim(A_LoopField49);
        }
        if (A_Index49 == 110) {
            keyWordCommentOpenMultiLine = Trim(A_LoopField49);
        }
        if (A_Index49 == 111) {
            keyWordCommentCloseMultiLine = Trim(A_LoopField49);
        }
        if (A_Index49 == 112) {
            keyWordEscpaeChar = Trim(A_LoopField49);
        }
        if (A_Index49 == 113) {
            keyWordMainLabel = Trim(A_LoopField49);
        }
        if (A_Index49 == 114) {
            keyWordConcat = Trim(A_LoopField49);
        }
        if (A_Index49 == 115) {
            keyWordAdd = Trim(A_LoopField49);
        }
        if (A_Index49 == 116) {
            keyWordSub = Trim(A_LoopField49);
        }
        if (A_Index49 == 117) {
            keyWordMul = Trim(A_LoopField49);
        }
        if (A_Index49 == 118) {
            keyWordDiv = Trim(A_LoopField49);
        }
        if (A_Index49 == 119) {
            keyWordMod = Trim(A_LoopField49);
        }
        if (A_Index49 == 120) {
            keyWordExp = Trim(A_LoopField49);
        }
        if (A_Index49 == 121) {
            keyWordEqual = Trim(A_LoopField49);
        }
        if (A_Index49 == 122) {
            keyWordStrictEqual = Trim(A_LoopField49);
        }
        if (A_Index49 == 123) {
            keyWordNotEqual = Trim(A_LoopField49);
        }
        if (A_Index49 == 124) {
            keyWordGreater = Trim(A_LoopField49);
        }
        if (A_Index49 == 125) {
            keyWordLess = Trim(A_LoopField49);
        }
        if (A_Index49 == 126) {
            keyWordGreaterEqual = Trim(A_LoopField49);
        }
        if (A_Index49 == 127) {
            keyWordLessEqual = Trim(A_LoopField49);
        }
        if (A_Index49 == 128) {
            keyWordAnd = Trim(A_LoopField49);
        }
        if (A_Index49 == 129) {
            keyWordOr = Trim(A_LoopField49);
        }
        if (A_Index49 == 130) {
            keyWordNot = Trim(A_LoopField49);
        }
        if (A_Index49 == 131) {
            keyWordBitAnd = Trim(A_LoopField49);
        }
        if (A_Index49 == 132) {
            keyWordBitOr = Trim(A_LoopField49);
        }
        if (A_Index49 == 133) {
            keyWordBitXor = Trim(A_LoopField49);
        }
        if (A_Index49 == 134) {
            keyWordBitNot = Trim(A_LoopField49);
        }
        if (A_Index49 == 135) {
            keyWordShiftLeft = Trim(A_LoopField49);
        }
        if (A_Index49 == 136) {
            keyWordShiftRight = Trim(A_LoopField49);
        }
        if (A_Index49 == 137) {
            keyWordShiftUnsignedRight = Trim(A_LoopField49);
        }
        if (A_Index49 == 138) {
            keyWordAssign = Trim(A_LoopField49);
        }
        if (A_Index49 == 139) {
            keyWordAssignAdd = Trim(A_LoopField49);
        }
        if (A_Index49 == 140) {
            keyWordAssignConcat = Trim(A_LoopField49);
        }
        if (A_Index49 == 141) {
            keyWordAssignSub = Trim(A_LoopField49);
        }
        if (A_Index49 == 142) {
            keyWordAssignMul = Trim(A_LoopField49);
        }
        if (A_Index49 == 143) {
            keyWordAssignDiv = Trim(A_LoopField49);
        }
        if (A_Index49 == 144) {
            keyWordAssignMod = Trim(A_LoopField49);
        }
        if (A_Index49 == 145) {
            keyWordAssignShiftLeft = Trim(A_LoopField49);
        }
        if (A_Index49 == 146) {
            keyWordAssignShiftRight = Trim(A_LoopField49);
        }
        if (A_Index49 == 147) {
            keyWordAssignBitAnd = Trim(A_LoopField49);
        }
        if (A_Index49 == 148) {
            keyWordAssignBitOr = Trim(A_LoopField49);
        }
        if (A_Index49 == 149) {
            keyWordAssignBitXor = Trim(A_LoopField49);
        }
        if (A_Index49 == 150) {
            keyWordTernary1 = Trim(A_LoopField49);
        }
        if (A_Index49 == 151) {
            keyWordTernary2 = Trim(A_LoopField49);
        }
        if (A_Index49 == 152) {
            keyWordInc = Trim(A_LoopField49);
        }
        if (A_Index49 == 153) {
            keyWordDec = Trim(A_LoopField49);
        }
        if (A_Index49 == 154) {
            AHKlikeLoopsIndexedAt = Trim(A_LoopField49);
        }
        if (A_Index49 == 155) {
            keyWordAIndex = Trim(A_LoopField49);
        }
        if (A_Index49 == 156) {
            keyWordALoopField = Trim(A_LoopField49);
        }
        if (A_Index49 == 157) {
            keyWordAllianceEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 158) {
            keyWordCrewEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 159) {
            keyWordMethodEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 160) {
            keyWordDefObjEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 161) {
            keyWordIFEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 162) {
            keyWordElseIfEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 163) {
            keyWordElseEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 164) {
            keyWordSwitchEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 165) {
            keyWordSwitchCaseEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 166) {
            keyWordWhileLoopEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 167) {
            keyWordForLoopEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 168) {
            keyWordLoopInfiniteEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 169) {
            keyWordLoopEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 170) {
            keyWordLoopParseEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 171) {
            keyWordFuncEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 172) {
            keyWordTryEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 173) {
            keyWordCatchEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 174) {
            keyWordFinallyEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 175) {
            useFuncKeyWord = Trim(A_LoopField49);
        }
        if (A_Index49 == 176) {
            useCurlyBraces = Trim(A_LoopField49);
        }
        if (A_Index49 == 177) {
            useEnd = Trim(A_LoopField49);
        }
        if (A_Index49 == 178) {
            useEndExtraInfo = Trim(A_LoopField49);
        }
        if (A_Index49 == 179) {
            useSemicolon = Trim(A_LoopField49);
        }
        if (A_Index49 == 180) {
            useParentheses = Trim(A_LoopField49);
        }
        if (A_Index49 == 181) {
            usePrefixTypeForTypeDefinition = Trim(A_LoopField49);
        }
        if (A_Index49 == 182) {
            usePostfixTypeForTypeDefinition = Trim(A_LoopField49);
        }
        if (A_Index49 == 183) {
            usePythonicColonSyntax = Trim(A_LoopField49);
        }
        if (A_Index49 == 184) {
            useInJavaScriptAlwaysUseVar = Trim(A_LoopField49);
        }
        if (A_Index49 == 185) {
            useJavaScriptInAfullHTMLfile = Trim(A_LoopField49);
        }
        if (A_Index49 == 186) {
            useJavaScriptAmainFuncDef = Trim(A_LoopField49);
        }
        if (A_Index49 == 187) {
            useJavaScriptAllFuncsAreAsync = Trim(A_LoopField49);
        }
        if (A_Index49 == 188) {
            useJavaScriptAlwaysTripleEqual = Trim(A_LoopField49);
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
    htCode = Trim(StrReplace(htCode, Chr(13), ""));
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
    var code = "";
    print(htCode);
    code = htCode;
    print(instructionFile);
    print(mode);
    print(langToConvertTo);
    print("==================================");
    print("==================================");
    print("==================================");
    print("==================================");
    print("==================================");
    //print(allInstructionFile)
    var codeOutFix1 = "";
    items50 = LoopParseFunc(code, "\n", "\r")
    for (let A_Index50 = 0; A_Index50 < items50.length + 0; A_Index50++) {
        const A_LoopField50 = items50[A_Index50 - 0];
        codeOutFix1 += Trim(A_LoopField50) + "\n";
    }
    code = StringTrimRight(codeOutFix1, 1);
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
    var htCodeOUT754754 = "";
    var areWEinSome34sNum = 0;
    var theIdNumOfThe34 = 0;
    let theIdNumOfThe34theVar = [];
    var ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = "";
    let getAllCharForTheFurtureSoIcanAddEscapeChar = [];
    var removeNexFixkeyWordEscpaeChar = 0;
    items51 = LoopParseFunc(code)
    for (let A_Index51 = 0; A_Index51 < items51.length + 0; A_Index51++) {
        const A_LoopField51 = items51[A_Index51 - 0];
        theIdNumOfThe34theVar.push("");
        theIdNumOfThe34theVar.push("");
    }
    items52 = LoopParseFunc(code)
    for (let A_Index52 = 0; A_Index52 < items52.length + 0; A_Index52++) {
        const A_LoopField52 = items52[A_Index52 - 0];
        theIdNumOfThe34theVar[A_Index52] = theIdNumOfThe34theVar[A_Index52] + Chr(34);
        getAllCharForTheFurtureSoIcanAddEscapeChar.push(A_LoopField52);
    }
    getAllCharForTheFurtureSoIcanAddEscapeChar.push(" ");
    ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuusgfgesrheidFor-aasdsas-theuhtuwaesphoutr" + Chr(34);
    var OutFixDoubleQuotesInsideDoubleQuotes = "";
    var fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
    items53 = LoopParseFunc(code)
    for (let A_Index53 = 0; A_Index53 < items53.length + 0; A_Index53++) {
        const A_LoopField53 = items53[A_Index53 - 0];
        if (A_LoopField53 == keyWordEscpaeChar && getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index53] == Chr(34)) {
            fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1;
            OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes;
        } else {
            if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1) {
                OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField53;
            } else {
                fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
            }
        }
    }
    code = StringTrimRight(OutFixDoubleQuotesInsideDoubleQuotes, 1);
    if (keyWordEscpaeChar != Chr(92)) {
        code = StrReplace(code, Chr(92), Chr(92) + Chr(92));
    }
    if (keyWordEscpaeChar == Chr(92)) {
        items54 = LoopParseFunc(code)
        for (let A_Index54 = 0; A_Index54 < items54.length + 0; A_Index54++) {
            const A_LoopField54 = items54[A_Index54 - 0];
            if (A_LoopField54 == Chr(34)) {
                areWEinSome34sNum++;
            }
            if (areWEinSome34sNum == 1) {
                if (A_LoopField54 != Chr(34)) {
                    if (A_LoopField54 == keyWordEscpaeChar) {
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                    } else {
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField54;
                    }
                } else {
                    theIdNumOfThe34++;
                    htCodeOUT754754 += "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                }
            }
            if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                if (A_LoopField54 != Chr(34)) {
                    htCodeOUT754754 += A_LoopField54;
                }
                areWEinSome34sNum = 0;
            }
        }
    } else {
        items55 = LoopParseFunc(code)
        for (let A_Index55 = 0; A_Index55 < items55.length + 0; A_Index55++) {
            const A_LoopField55 = items55[A_Index55 - 0];
            if (A_LoopField55 == Chr(34)) {
                areWEinSome34sNum++;
            }
            if (areWEinSome34sNum == 1) {
                if (A_LoopField55 != Chr(34)) {
                    if (A_LoopField55 == keyWordEscpaeChar && keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index55]) {
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar;
                        removeNexFixkeyWordEscpaeChar = 1;
                    }
                    else if (A_LoopField55 == keyWordEscpaeChar) {
                        if (removeNexFixkeyWordEscpaeChar != 1) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                        } else {
                            removeNexFixkeyWordEscpaeChar = 0;
                        }
                    } else {
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField55;
                    }
                } else {
                    theIdNumOfThe34++;
                    htCodeOUT754754 += "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                }
            }
            if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                if (A_LoopField55 != Chr(34)) {
                    htCodeOUT754754 += A_LoopField55;
                }
                areWEinSome34sNum = 0;
            }
        }
    }
    code = htCodeOUT754754;
    for (let A_Index56 = 0; A_Index56 < theIdNumOfThe34 + 0; A_Index56++) {
        theIdNumOfThe34theVar[A_Index56] = theIdNumOfThe34theVar[A_Index56] + Chr(34);
    }
    code = StrReplace(code, Chr(13), "");
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    if (langToConvertTo != "py" && useSemicolon == "off") {
        theSemicolon = ";";
    } else {
        theSemicolon = "";
    }
    if (langToConvertTo != "py" && usePythonicColonSyntax == "off") {
        theColon = "";
    } else {
        theColon = ":";
    }
    var beforeKeywordForRemoveCommentsOnTheEndOfTheLine = "";
    var newStringOutCode = "";
    var posForRemoveCommentsOnTheEndOfTheLine = 0;
    var originalStringForRemoveCommentsOnTheEndOfTheLine = "";
    items57 = LoopParseFunc(code, "\n", "\r")
    for (let A_Index57 = 0; A_Index57 < items57.length + 0; A_Index57++) {
        const A_LoopField57 = items57[A_Index57 - 0];
        // Define the original string
        originalStringForRemoveCommentsOnTheEndOfTheLine = A_LoopField57;
        // Find the position of the keyword in the original string
        posForRemoveCommentsOnTheEndOfTheLine = InStr(originalStringForRemoveCommentsOnTheEndOfTheLine, " " + keyWordComment);
        if (SubStr(Trim(A_LoopField57), 1, StrLen(keyWordComment)) != keyWordComment) {
            if (posForRemoveCommentsOnTheEndOfTheLine > 0) {
                // Extract the part of the string before the keyword
                if (SubStr(StrLower(A_LoopField57), 1, StrLen(StrLower(keyWordForLoop))) != StrLower(keyWordForLoop)) {
                    beforeKeywordForRemoveCommentsOnTheEndOfTheLine = SubStr(originalStringForRemoveCommentsOnTheEndOfTheLine, 1, posForRemoveCommentsOnTheEndOfTheLine - 1);
                } else {
                    beforeKeywordForRemoveCommentsOnTheEndOfTheLine = A_LoopField57;
                }
                // Construct the new string with everything before the keyword
                newStringOutCode += beforeKeywordForRemoveCommentsOnTheEndOfTheLine + "\n";
            } else {
                newStringOutCode += A_LoopField57 + "\n";
            }
        } else {
            newStringOutCode += A_LoopField57 + "\n";
        }
    }
    code = StringTrimRight(newStringOutCode, 1);
    //MsgBox, % code
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var htCodeOutFixEnd = "";
    if (useEnd == "on") {
        items58 = LoopParseFunc(code, "\n", "\r")
        for (let A_Index58 = 0; A_Index58 < items58.length + 0; A_Index58++) {
            const A_LoopField58 = items58[A_Index58 - 0];
            if (StrLower(Trim(A_LoopField58)) == StrLower(keyWordEnd)) {
                htCodeOutFixEnd += str10 + "}" + "\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf)) {
                htCodeOutFixEnd += "\n}\n" + A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse)) {
                htCodeOutFixEnd += "\n}\n" + A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordForLoop))) == StrLower(keyWordForLoop)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordLoopInfinite))) == StrLower(keyWordLoopInfinite)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordSwitch))) == StrLower(keyWordSwitch)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordSwitchCase))) == StrLower(keyWordSwitchCase)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordSwitchDefault))) == StrLower(keyWordSwitchDefault)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordTry))) == StrLower(keyWordTry)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordCrew))) == StrLower(keyWordCrew)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordDefObj))) == StrLower(keyWordDefObj)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordMethod))) == StrLower(keyWordMethod)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)) {
                htCodeOutFixEnd += "\n}\n" + A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally)) {
                htCodeOutFixEnd += "\n}\n" + A_LoopField58 + "\n{\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc)) {
                htCodeOutFixEnd += A_LoopField58 + "\n{\n";
            } else {
                htCodeOutFixEnd += A_LoopField58 + "\n";
            }
        }
        code = StringTrimRight(htCodeOutFixEnd, 1);
    }
    if (useEnd == "off" && useCurlyBraces == "off") {
        htCodeOutFixEnd = "";
        items59 = LoopParseFunc(code, "\n", "\r")
        for (let A_Index59 = 0; A_Index59 < items59.length + 0; A_Index59++) {
            const A_LoopField59 = items59[A_Index59 - 0];
            if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordForLoop))) == StrLower(keyWordForLoop)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordLoopInfinite))) == StrLower(keyWordLoopInfinite)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordSwitch))) == StrLower(keyWordSwitch)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordSwitchCase))) == StrLower(keyWordSwitchCase)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordSwitchDefault))) == StrLower(keyWordSwitchDefault)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordTry))) == StrLower(keyWordTry)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordCrew))) == StrLower(keyWordCrew)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordDefObj))) == StrLower(keyWordDefObj)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordMethod))) == StrLower(keyWordMethod)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            }
            else if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc)) {
                htCodeOutFixEnd += A_LoopField59 + ":\n";
            } else {
                htCodeOutFixEnd += A_LoopField59 + "\n";
            }
        }
        code = StringTrimRight(htCodeOutFixEnd, 1);
    }
    if (useCurlyBraces == "off" && useEnd == "off") {
        code = AddCurlyBraces(code);
    }
    items60 = LoopParseFunc(code, "\n", "\r")
    for (let A_Index60 = 0; A_Index60 < items60.length + 0; A_Index60++) {
        const A_LoopField60 = items60[A_Index60 - 0];
        outTrimCode += Trim(A_LoopField60) + "\n";
    }
    code = StringTrimRight(outTrimCode, 1);
    // for converting c++ to js and py
    code = StrReplace(code, "{}", "[]");
    var outCodeFixBraces = "";
    for (let A_Index61 = 0; A_Index61 < 2 + 0; A_Index61++) {
        outCodeFixBraces = "";
        items62 = LoopParseFunc(code, "\n", "\r")
        for (let A_Index62 = 0; A_Index62 < items62.length + 0; A_Index62++) {
            const A_LoopField62 = items62[A_Index62 - 0];
            if (InStr(Trim(A_LoopField62), "{") && Trim(A_LoopField62) != "{") {
                outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField62), "{", "")) + "\n{\n";
            }
            else if (InStr(Trim(A_LoopField62), "}") && Trim(A_LoopField62) != "}") {
                outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField62), "}", "")) + "\n";
            } else {
                outCodeFixBraces += Trim(A_LoopField62) + "\n";
            }
        }
        code = StringTrimRight(outCodeFixBraces, 1);
    }
    //MsgBox, % code
    //;; main loop ;;;
    //;; main loop ;;;
    //;; main loop ;;;
    //;; main loop ;;;
    var didWeUseMainLabel = 0;
    var codeOutFixAndAddMainFunc = "";
    print(code);
    items63 = LoopParseFunc(code, "\n", "\r")
    for (let A_Index63 = 0; A_Index63 < items63.length + 0; A_Index63++) {
        const A_LoopField63 = items63[A_Index63 - 0];
        HTVMout = "0";
    }
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
    items64 = LoopParseFunc(str0)
    for (let A_Index64 = 0; A_Index64 < items64.length + 0; A_Index64++) {
        const A_LoopField64 = items64[A_Index64 - 0];
        str00 = Trim(A_LoopField64);
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
        items65 = LoopParseFunc(allArgs, "\n", "\r")
        for (let A_Index65 = 0; A_Index65 < items65.length + 0; A_Index65++) {
            const A_LoopField65 = items65[A_Index65 - 0];
            if (A_Index65 == 0) {
                argCODE = FileRead(Trim(A_LoopField65));
                argCODEfile = Trim(A_LoopField65);
            }
            else if (A_Index65 == 1) {
                argHTVMinstr = Trim(A_LoopField65);
            }
            else if (A_Index65 == 2) {
                argLangTo = Trim(A_LoopField65);
            } else {
                argHTVMinstrMOVE.push(Trim(A_LoopField65));
            }
        }
        print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        if (SubStrLastChars(argCODEfile, 4) == ".cpp" || SubStrLastChars(argCODEfile, 3) == ".py" || SubStrLastChars(argCODEfile, 3) == ".js" || SubStrLastChars(argCODEfile, 3) == ".go" || SubStrLastChars(argCODEfile, 4) == ".lua" || SubStrLastChars(argCODEfile, 3) == ".cs" || SubStrLastChars(argCODEfile, 5) == ".java" || SubStrLastChars(argCODEfile, 3) == ".kt" || SubStrLastChars(argCODEfile, 3) == ".rb" || SubStrLastChars(argCODEfile, 4) == ".nim" || SubStrLastChars(argCODEfile, 4) == ".ahk" || SubStrLastChars(argCODEfile, 6) == ".swift" || SubStrLastChars(argCODEfile, 5) == ".dart" || SubStrLastChars(argCODEfile, 3) == ".ts" || SubStrLastChars(argCODEfile, 6) == ".scala" || SubStrLastChars(argCODEfile, 7) == ".groovy") {
            if (argLangTo != "") {
                OUTCODE = compiler(argCODE, argHTVMinstr, "notHTVM", argLangTo);
            } else {
                OUTCODE = compiler(argCODE, argHTVMinstr, "notHTVM");
            }
        } else {
            if (argLangTo != "") {
                OUTCODE = compiler(argCODE, argHTVMinstr, "full", argLangTo);
            } else {
                OUTCODE = compiler(argCODE, argHTVMinstr, "full");
            }
        }
        print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        FileDelete(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        FileAppend(OUTCODE, StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
    }
    if (HTVM_getLang_HTVM() == "js") {
        print("JS");
    }
}
async function main() {
    HTVMv2();
}
main();