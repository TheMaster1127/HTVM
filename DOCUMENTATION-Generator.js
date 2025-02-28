

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

function HTVM_getLang_HTVM() {
    return "js";
}


var instructionFileData = "";
var DOCS_params = "";
var DOCS_param1 = "";
var DOCS_param2 = "";
var DOCS_checkIfFuncNameExists = 0;
var OUTdocs_HTML = "";
var OUTdocs_MD = "";
function genDocs(mode) {
    var outDocs = "";
    if (Trim(instructionFileData) == "") {
        throw new Error("instructionFileData is empty");
        return "error: instructionFileData is empty!!!";
    }
    items1 = LoopParseFunc(instructionFileData, "\n", "\r")
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        outDocs = "test out in " + mode;
    }
    outDocs = "still in development!!! test out in " + mode;
    return outDocs;
}
if (HTVM_getLang_HTVM() != "js") {
    DOCS_params = Trim(GetParams());
    if (Trim(StrSplit(DOCS_params, "\n", 1)) == "") {
        print("Usage: <instruction_file> [function_name]" + Chr(10) + Chr(10) + "- <instruction_file>: Required. Generates DOCUMENTATION.md and DOCUMENTATION.html." + Chr(10) + "- [function_name]: Optional. If provided, checks whether the function exists and it does not output any files.");
        print("no params Exiting...");
        ExitApp();
    }
    items2 = LoopParseFunc(DOCS_params, "\n", "\r")
    for (let A_Index2 = 0; A_Index2 < items2.length + 0; A_Index2++) {
        const A_LoopField2 = items2[A_Index2 - 0];
        if (A_Index2 == 0) {
            print(A_LoopField2);
            DOCS_param1 = Trim(A_LoopField2);
        }
        if (A_Index2 == 1) {
            print(A_LoopField2);
            DOCS_param2 = Trim(A_LoopField2);
        }
    }
    if (!FileExist(DOCS_param1)) {
        print("the file doesn't exist!!!");
        ExitApp();
    }
    if (Trim(DOCS_param2) != "") {
        DOCS_checkIfFuncNameExists = 1;
    }
    if (DOCS_checkIfFuncNameExists == 1) {
        print("[function_name] still in development!!!");
        print("Exiting...");
        ExitApp();
    } else {
        instructionFileData = FileRead(Trim(DOCS_param1));
        OUTdocs_HTML = genDocs("html");
        OUTdocs_MD = genDocs("md");
        FileDelete("DOCUMENTATION.md");
        FileAppend(OUTdocs_MD, "DOCUMENTATION.md");
        print("Everything is saved in DOCUMENTATION.md");
        print("========================================");
        FileDelete("DOCUMENTATION.html");
        FileAppend(OUTdocs_HTML, "DOCUMENTATION.html");
        print("Everything is saved in DOCUMENTATION.html");
        print("========================================");
        print("Done!");
    }
}
// else add the full user instruction file in instructionFileData variable
// make sure to reset all vars
/*
var "";
var "";
var "";
var "";
var 0;
var "";
var "";
*/
// MAKE SURE to put the instruction file in instructionFileData variable!!!
// run genDocs("html") and the output will be text that needs to be saved in DOCUMENTATION.html
// run genDocs("md") and the output will be text that needs to be saved in DOCUMENTATION.md