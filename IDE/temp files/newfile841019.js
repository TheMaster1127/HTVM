

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

function Trim(inputString) {
    return inputString ? inputString.trim() : "";
}

function StringTrimRight(input, numChars) {
    return (numChars <= input.length) ? input.substring(0, input.length - numChars) : input;
}


async function main() {
    var htCode = "htCode";
    let fixGoManGoIsSoAnnoyingBroooFurure = [];
    items1 = LoopParseFunc(htCode, "\n", "\r")
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        fixGoManGoIsSoAnnoyingBroooFurure.push(A_LoopField1);
    }
    fixGoManGoIsSoAnnoyingBroooFurure.push(" ");
    var fixGoManGoIsSoAnnoyingBroooSkip = 0;
    var fixGoManGoIsSoAnnoyingBroooCount = 0;
    var fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
    var fixGoManGoIsSoAnnoyingBrooo = "";
    items2 = LoopParseFunc(htCode, "\n", "\r")
    for (let A_Index2 = 0; A_Index2 < items2.length + 0; A_Index2++) {
        const A_LoopField2 = items2[A_Index2 - 0];
        if (Trim(A_LoopField2) == "}" && SubStr(Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index2 + 1]), 1, StrLen("else if ")) == "else if ") {
            fixGoManGoIsSoAnnoyingBroooSkip = 1;
            items3 = LoopParseFunc(fixGoManGoIsSoAnnoyingBroooFurure[A_Index2 + 1])
            for (let A_Index3 = 0; A_Index3 < items3.length + 0; A_Index3++) {
                const A_LoopField3 = items3[A_Index3 - 0];
                if (A_LoopField3 == " ") {
                    fixGoManGoIsSoAnnoyingBroooCount++;
                } else {
                    break;
                }
            }
            for (let A_Index4 = 0; A_Index4 < fixGoManGoIsSoAnnoyingBroooCount + 0; A_Index4++) {
                fixGoManGoIsSoAnnoyingBroooCountSpaceses += " ";
            }
            fixGoManGoIsSoAnnoyingBrooo += fixGoManGoIsSoAnnoyingBroooCountSpaceses + "} " + Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index2 + 1]) + "\n";
        } else {
            if (fixGoManGoIsSoAnnoyingBroooSkip == 1) {
                fixGoManGoIsSoAnnoyingBroooSkip = 0;
                fixGoManGoIsSoAnnoyingBrooo += A_LoopField2 + "\n";
            }
        }
    }
    htCode = StringTrimRight(fixGoManGoIsSoAnnoyingBrooo, 1);
}
main();