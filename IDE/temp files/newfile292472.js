

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
    if (!InStr(line, matchString)) {
        print("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
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
    var isEnd = 0;
    var i1 = 0;
    for (let A_Index2 = 0; A_Index2 < lineArr.length + 0; A_Index2++) {
        if (A_Index2 == lineArr.length - 1) {
            isEnd = 1;
        }
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
        print(sildingLine);
        i1++;
    }
    return "0";
}
print(HTVMmatchStrRrplace("hi man", "hi", "hello"));
print(HTVMmatchStrRrplace("hi man", "man", "woman"));
print(HTVMmatchStrRrplace("func1(man.hello())", ".hello", ".mello"));
print(HTVMmatchStrRrplace("func1(var1 plus plus var2)", "plus plus", "+"));