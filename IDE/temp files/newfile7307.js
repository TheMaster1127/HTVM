

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

function Trim(inputString) {
    return inputString ? inputString.trim() : "";
}

function StrSplit(inputStr, delimiter, num) {
    const parts = inputStr.split(delimiter);
    return (num > 0 && num <= parts.length) ? parts[num - 1] : "";
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


var langToConvertTo = "py";
var keyWordArrayAppend = ".add";
var keyWordArrayPop = ".pop";
var keyWordArraySize = ".size";
var keyWordArrayInsert = ".inster";
var keyWordArrayRemove = ".rm";
var keyWordArrayIndexOf = ".indexOf";
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;; end
async function fixArray1234(line) {
    var out = "";
    var started = 0;
    items1 = LoopParseFunc(line)
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        if (started == 1) {
            if (StrLen(line) == A_Index1 + 1) {
                return out;
            }
            out += A_LoopField1;
        }
        if (A_LoopField1 == "(") {
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
    var out = "";
    var allDelimiters = " ()[],;:'!&|=<>+-*/^%~" + Chr(34) + Chr(9) + Chr(11);
    let arrAll = [];
    items2 = LoopParseFunc(line)
    for (let A_Index2 = 0; A_Index2 < items2.length + 0; A_Index2++) {
        const A_LoopField2 = items2[A_Index2 - 0];
        arrAll.push(A_LoopField2);
    }
    var i1 = 0;
    var tempHold = "";
    var holdPos = 0;
    let holdPositions = [];
    for (let A_Index3 = 0; A_Index3 < arrAll.length + 0; A_Index3++) {
        tempHold = "";
        if (arrAll.length - StrLen(arrayMethodStr) + 1 == i1) {
            break;
        }
        for (let A_Index4 = 0; A_Index4 < StrLen(arrayMethodStr) + 0; A_Index4++) {
            tempHold += arrAll[A_Index4 + i1];
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
    for (let A_Index5 = 0; A_Index5 < holdPositions.length + 0; A_Index5++) {
        holdPositionsTEMP = holdPositions[A_Index5];
        i1 = arrAll.length;
        tempHold = "";
        for (let A_Index6 = 0; A_Index6 < arrAll.length + 0; A_Index6++) {
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
        holdPositions[A_Index5] = holdPositions[A_Index5] - StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", "")));
    }
    //;;;;;;;;;;;;;;;;;;
    var foundFirstParenthesis = 0;
    var ParenthesisStackOPEN = 0;
    var ParenthesisStackCLOSE = 0;
    let holdPositionsEnd = [];
    holdPositionsTEMP = 0;
    for (let A_Index7 = 0; A_Index7 < holdPositions.length + 0; A_Index7++) {
        holdPositionsTEMP = holdPositions[A_Index7];
        i1 = 0;
        tempHold = "";
        foundFirstParenthesis = 0;
        ParenthesisStackOPEN = 0;
        ParenthesisStackCLOSE = 0;
        for (let A_Index8 = 0; A_Index8 < arrAll.length + 0; A_Index8++) {
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
    for (let A_Index9 = 0; A_Index9 < holdPositions.length + 0; A_Index9++) {
        startPosReplace = holdPositions[holdPositions.length - A_Index9 - 1];
        endPosReplace = holdPositionsEnd[holdPositions.length - A_Index9 - 1];
        holdDebug = "";
        beenInside = 0;
        holdDebugLen = 0;
        canOut = 1;
        items10 = LoopParseFunc(line)
        for (let A_Index10 = 0; A_Index10 < items10.length + 0; A_Index10++) {
            const A_LoopField10 = items10[A_Index10 - 0];
            if (A_Index10 + 1 >= startPosReplace && A_Index10 + 1 <= endPosReplace) {
                holdDebug += A_LoopField10;
            }
        }
        holdDebugLen = StrLen(holdDebug);
        items11 = LoopParseFunc(line)
        for (let A_Index11 = 0; A_Index11 < items11.length + 0; A_Index11++) {
            const A_LoopField11 = items11[A_Index11 - 0];
            if (A_Index11 + 1 >= startPosReplace && A_Index11 + 1 <= endPosReplace) {
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
                    out += A_LoopField11;
                }
            }
        }
        //print("|" . holdDebug . "|")
        var line = out;
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
    line = await arrayParserTranspiler1(line, keyWordArrayAppend + "(", 1);
    line = await arrayParserTranspiler1(line, keyWordArrayPop + "(", 2);
    line = await arrayParserTranspiler1(line, keyWordArraySize + "(", 3);
    line = await arrayParserTranspiler1(line, keyWordArrayInsert + "(", 4);
    line = await arrayParserTranspiler1(line, keyWordArrayRemove + "(", 5);
    line = await arrayParserTranspiler1(line, keyWordArrayIndexOf + "(", 6);
    return line;
}
async function main() {
    print(await arrayParserTranspiler("()()()arr123.size() + arr1234.indexOf(arr12.size() + arrr1234.add(5) + arrr1234.rm(2), arr12.size(), 2)"));
    print(await arrayParserTranspiler("arr123.size()"));
    print(await arrayParserTranspiler("arr123.size() + arr123.size() + arr123.size() + arr123.size()"));
    print(await arrayParserTranspiler("arr1234.size() + arr123.size() + arr12345.size() + arr12.size()"));
    print(await arrayParserTranspiler("arr12.size() + arr123.size() + arr1.size() + arr123.size()"));
    print(await arrayParserTranspiler("arr12.size() + arr123.size() + arr1.size() + arr12366.size()"));
}
main();
