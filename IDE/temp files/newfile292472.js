

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


async function HTVMmatchStrRrplace(line, matchString, replaceString) {
    var lineOut = "";
    if (!InStr(line, matchString)) {
        return line;
    }
    var allDelimiters = " ()[].";
    let lineArr = [];
    items1 = LoopParseFunc(line)
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        lineArr.push(A_LoopField1);
    }
    var matchStringLEN = StrLen(matchString);
    var sildingLine = "";
    var isStart = 1;
    var i1 = 0;
    var hasFound = 0;
    var hasFound2 = 0;
    for (let A_Index2 = 0; A_Index2 < 1 + 0; A_Index2++) {
        sildingLine = "";
        isStart = 1;
        i1 = 0;
        hasFound = 0;
        hasFound2 = 0;
        for (let A_Index3 = 0; A_Index3 < lineArr.length + 0; A_Index3++) {
            if (A_Index3 != 0) {
                isStart = 0;
            }
            sildingLine = "";
            for (let A_Index4 = 0; A_Index4 < matchStringLEN + 0; A_Index4++) {
                if (A_Index4 + i1 <= lineArr.length - 1) {
                    sildingLine += lineArr[A_Index4 + i1];
                }
            }
            if (StrLen(sildingLine) < matchStringLEN) {
                break;
            }
            print("!!!!111111111!!!!!!: " + sildingLine);
            if (sildingLine == matchString) {
                hasFound = 1;
                if (isStart != 1) {
                    print("!!!!2222222222!!!!!!: " + lineArr[i1 - 1]);
                    print("!!!!2222222222.555555555!!!!!!: " + lineArr[i1]);
                }
                if (i1 + matchStringLEN < lineArr.length) {
                    print("!!!!3333333333.5555555555!!!!!!: " + lineArr[i1 + matchStringLEN - 1]);
                    print("!!!!3333333333!!!!!!: " + lineArr[i1 + matchStringLEN]);
                }
            }
            if (hasFound == 1) {
                hasFound2 = 0;
            }
            i1++;
        }
        if (hasFound == 0) {
            return lineOut;
        }
    }
    return lineOut;
}
async function main() {
    print(await HTVMmatchStrRrplace("hi man", "hi", "hello"));
    print(await HTVMmatchStrRrplace("hi man", "man", "woman"));
    print(await HTVMmatchStrRrplace("func1(man.hello())", ".hello", ".mello"));
    print(await HTVMmatchStrRrplace("func1(var1 plus plus var2)", "plus plus", "+"));
}
main();