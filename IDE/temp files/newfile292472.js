

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

function StringTrimRight(input, numChars) {
    return (numChars <= input.length) ? input.substring(0, input.length - numChars) : input;
}


async function HTVMmatchStrRrplace(line, matchString, replaceString) {
    var lineOut = "";
    if (!InStr(line, matchString)) {
        return line;
    }
    var allDelimiters = " ()[].,;:'!&|=<>+-*/^%~" + Chr(34);
    let lineArr = [];
    items1 = LoopParseFunc(line)
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        lineArr.push(A_LoopField1);
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
    for (let A_Index2 = 0; A_Index2 < lineArr.length + 0; A_Index2++) {
        char1 = "";
        char2 = "";
        char3 = "";
        char4 = "";
        isMatch = 0;
        if (A_Index2 != 0) {
            isStart = 0;
        }
        sildingLine = "";
        for (let A_Index3 = 0; A_Index3 < matchStringLEN + 0; A_Index3++) {
            if (A_Index3 + i1 <= lineArr.length - 1) {
                sildingLine += lineArr[A_Index3 + i1];
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
                for (let A_Index4 = 0; A_Index4 < allPosForReplacing.length + 0; A_Index4++) {
                    if (i1 + 1 != allPosForReplacing[A_Index4]) {
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
        for (let A_Index5 = 0; A_Index5 < allPosForReplacing.length + 0; A_Index5++) {
            if (A_Index5 == 0) {
                currentPos = allPosForReplacing[A_Index5];
            } else {
                currentPos = allPosForReplacing[A_Index5] - (matchStringLEN - replaceStringLEN);
            }
            onceEnd = 0;
            items6 = LoopParseFunc(lineOut)
            for (let A_Index6 = 0; A_Index6 < items6.length + 0; A_Index6++) {
                const A_LoopField6 = items6[A_Index6 - 0];
                if (A_Index6 + 2 > currentPos && A_Index6 + 1 < currentPos + matchStringLEN) {
                    onceEnd++;
                    //print("DDDDDDDDDDD" . STR(A_Index6))
                    if (onceEnd == 1) {
                        lineTEMP += replaceString;
                    }
                } else {
                    lineTEMP += A_LoopField6;
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
async function main() {
    var varQYTYWAEUSR = "";
    print(await HTVMmatchStrRrplace("hi man", "hi", "hello"));
    print(await HTVMmatchStrRrplace("hi man", "man", "woman"));
    print(await HTVMmatchStrRrplace("func1(man.hello()) func1(man.hello())", ".hello", ".mello"));
    print(await HTVMmatchStrRrplace("func1(var1 plus plus var2 plus plus var34)", "plus plus", "+"));
    print(await HTVMmatchStrRrplace("var1.add() + var12.add()", ".add()", ".push()"));
    print(await HTVMmatchStrRrplace("var1.add() + var12.add()", ".add()", ".pu()"));
    for (let A_Index7 = 0; A_Index7 < 10000 + 0; A_Index7++) {
        varQYTYWAEUSR += await HTVMmatchStrRrplace("hi man", "hi", "hello") + "\n";
        varQYTYWAEUSR += await HTVMmatchStrRrplace("hi man", "man", "woman") + "\n";
        varQYTYWAEUSR += await HTVMmatchStrRrplace("func1(man.hello()) func1(man.hello())", ".hello", ".mello") + "\n";
        varQYTYWAEUSR += await HTVMmatchStrRrplace("func1(var1 plus plus var2 plus plus var34)", "plus plus", "+") + "\n";
        varQYTYWAEUSR += await HTVMmatchStrRrplace("var1.add() + var12.add()", ".add()", ".push()") + "\n";
        varQYTYWAEUSR += await HTVMmatchStrRrplace("var1.add() + var12.add()", ".add()", ".pu()") + "\n";
    }
    varQYTYWAEUSR = StringTrimRight(varQYTYWAEUSR, 1);
}
main();
