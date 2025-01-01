

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

function StrLen(s) {
    // Return the length of the given string
    return s.length;
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


async function SubStrLastChars(text, numOfChars) {
    var strLength = StrLen(text);
    if (numOfChars > strLength) {
        return text;
    }
    let textArr = [];
    items1 = LoopParseFunc(text)
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        textArr.push(A_LoopField1);
    }
    var LastOut = "";
    for (let A_Index2 = 0; A_Index2 < numOfChars + 0; A_Index2++) {
        LastOut = textArr[(strLength - A_Index2)] + LastOut;
    }
    return LastOut;
}
async function main() {
    print(await SubStrLastChars("hello", 2));
}
main();