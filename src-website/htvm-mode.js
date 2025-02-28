

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

function Exp(value) {
    return Math.exp(value);
}

function Trim(inputString) {
    return inputString ? inputString.trim() : "";
}

function StrReplace(originalString, find, replaceWith) {
    return originalString.split(find).join(replaceWith);
}

function StringTrimRight(input, numChars) {
    return (numChars <= input.length) ? input.substring(0, input.length - numChars) : input;
}

function Mod(dividend, divisor) {
    return dividend % divisor;
}


allKeyWordsIn = ""; // Global variable to store the result
allKeyWordsOut = "";
allFunctionNamesString = ""; // Global string to store function names
async function getFunctionNames() {
    const url = 'https://raw.githubusercontent.com/TheMaster1127/HTVM/refs/heads/main/HTVM-instructions.txt';
    
    try {
        const response = await fetch(url);
        if (!response.ok) {
            throw new Error(`Network response was not ok: ${response.statusText}`);
        }
        const text = await response.text();
        
        // Split text by line and get lines starting from line 162
        const lines = text.split('\n').slice(162); // Line 162 starts at index 161
        
        // Extract function names that start with "name: "
        const functionNames = lines
            .map(line => line.trim()) // Trim each line
            .filter(line => line.startsWith("name: ")) // Only lines that start with "name: "
            .map(line => line.replace("name: ", "").trim()) // Get function name (remove "name: " part)
            .filter((value, index, self) => self.indexOf(value) === index); // Remove duplicates
        
        // Save the function names in the global variable
        allFunctionNamesString = functionNames.join('\n');
        
    } catch (error) {
        console.error('Error fetching the text file:', error);
    }
}
// Function to fetch the first 161 lines from a remote text file
async function fetchFirst161Lines(url) {
    try {
        const response = await fetch(url);
        if (!response.ok) {
            throw new Error(`Network response was not ok: ${response.statusText}`);
        }
        const text = await response.text();
        return text.split('\n').slice(0, 162).join('\n');
    } catch (error) {
        console.error('Error fetching the text file:', error);
        return null;
    }
}
// Main function to handle localStorage and data retrieval
async function getAllKeyWordsIn() {
    const id = new URLSearchParams(window.location.search).get('id');
    if (!id) {
        console.error('No ID found in the URL');
        return;
    }
    const storageKey = "htvm_lang_" + id;
    let storedData = localStorage.getItem(storageKey);
    
    // If the key exists, use localStorage data and return
    if (storedData !== null) {
        try {
            const arrayData = JSON.parse(storedData);
            if (Array.isArray(arrayData)) {
                allKeyWordsIn = arrayData.slice(0, 162).join('\n'); // Save in global variable
                return;
            } else {
                console.error('Stored data is not an array');
                return;
            }
        } catch (error) {
            console.error('Error parsing JSON from localStorage:', error);
            return;
        }
    }
    // If key is missing, fetch data from the remote file
    const url = 'https://raw.githubusercontent.com/TheMaster1127/HTVM/refs/heads/main/HTVM-instructions.txt';
    const fetchedData = await fetchFirst161Lines(url);
    if (fetchedData) {
        localStorage.setItem(storageKey, JSON.stringify(fetchedData.split('\n'))); // Store in localStorage
        allKeyWordsIn = fetchedData; // Save in global variable
    } else {
        console.error('Failed to fetch data from the remote file');
    }
}
async function getAllKeyWords() {
    await getAllKeyWordsIn();
    await getFunctionNames();
    var allKeyWordsIn_OUT = "";
    var allKeyWordsIn_OUT_TEMP = "";
    items1 = LoopParseFunc(allKeyWordsIn, "\n", "\r")
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        if (A_Index1 != 0 && A_Index1 != 1) {
            allKeyWordsIn_OUT += A_LoopField1 + "\n";
        }
    }
    allKeyWordsIn_OUT = StringTrimRight(allKeyWordsIn_OUT, 1);
    allKeyWordsOut = allKeyWordsIn_OUT;
}
let allFunctionNamesString2 = "";
(async function () {
    await getAllKeyWords();
    //console.log(allKeyWordsOut);
allFunctionNamesString2 = Trim(StrReplace(allFunctionNamesString, Chr(10), "|"));
//print("=============================")
//print(allFunctionNamesString2)
//print("=============================")
// Get the URL parameter 'id'
const urlParams = new URLSearchParams(window.location.search);
const id = urlParams.get('id');
// Check if 'id' is present in the URL
if (id) {
    // Create the key for localStorage
    const storageKey = `htvm_lang_${id}_allFunctionNamesString`;
    const storageKey2 = `htvm_lang_${id}_allKeyWordsOut`;
    // Save 'allFunctionNamesString2' to localStorage
    localStorage.setItem(storageKey, allFunctionNamesString2);
    localStorage.setItem(storageKey2, allKeyWordsOut);
} else {
    console.error('URL parameter "id" is missing.');
}
})();
// Define the HTVM mode for Ace Editor
ace.define("ace/mode/htvm", ["require", "exports", "module", "ace/lib/oop", "ace/mode/text", "ace/mode/text_highlight_rules"], function(require, exports, module) {
    var oop = require("ace/lib/oop");
    var TextMode = require("ace/mode/text").Mode;
    var TextHighlightRules = require("ace/mode/text_highlight_rules").TextHighlightRules;
    var HTVMHighlightRules = function() {
        
        //console.log(new URLSearchParams(window.location.search).get('id'));
let allFunctionNamesString3 = "";
let allKeyWordsOut3 = "";
// Get the URL parameter 'id'
const urlParams = new URLSearchParams(window.location.search);
const id = urlParams.get('id');
// Check if 'id' is present in the URL
if (id) {
    // Create the key for localStorage
    const storageKey = `htvm_lang_${id}_allFunctionNamesString`;
    const storageKey2 = `htvm_lang_${id}_allKeyWordsOut`;
    // Retrieve 'allFunctionNamesString' from localStorage
    allFunctionNamesString3 = localStorage.getItem(storageKey);
    allKeyWordsOut3 = localStorage.getItem(storageKey2);
} else {
    console.error('URL parameter "id" is missing.');
}
var builtInCommands_temp = "";
var htvmKeywords_temp = "";
var staticTypes_temp = "";
var builtInVars_temp = "";
var operators_temp = "";
var arrayMethods_temp = "";
var programmingBlocksAndImport_temp = "";
var htvm_trueFalseGlobalNull_temp = "";
var htvm_comment_temp = "";
var htvm_commentOpen1_temp = "";
var htvm_commentClose2_temp = "";
items2 = LoopParseFunc(allKeyWordsOut3, "\n", "\r")
for (let A_Index2 = 0; A_Index2 < items2.length + 0; A_Index2++) {
    const A_LoopField2 = items2[A_Index2 - 0];
    if (Trim(A_LoopField2) != "") {
        if (A_Index2 == 0) {
            items3 = LoopParseFunc(A_LoopField2, "|")
            for (let A_Index3 = 0; A_Index3 < items3.length + 0; A_Index3++) {
                const A_LoopField3 = items3[A_Index3 - 0];
                items4 = LoopParseFunc(A_LoopField3, ",");
                for (let A_Index4 = 0; A_Index4 < items4.length + 0; A_Index4++) {
                    const A_LoopField4 = items4[A_Index4 - 0];
                    builtInCommands_temp += Trim(A_LoopField4) + "|";
                }
            }
        }
        if (A_Index2 == 1 || A_Index2 == 2 || A_Index2 == 3 || A_Index2 == 4 || A_Index2 == 5 || A_Index2 == 64 || A_Index2 == 65 || A_Index2 == 66 || A_Index2 == 67 || A_Index2 == 68 || A_Index2 == 69 || A_Index2 == 70 || A_Index2 == 71 || A_Index2 == 72 || A_Index2 == 73 || A_Index2 == 74 || A_Index2 == 75 || A_Index2 == 76 || A_Index2 == 78 || A_Index2 == 79 || A_Index2 == 80 || A_Index2 == 81 || A_Index2 == 93 || A_Index2 == 94 || A_Index2 == 95 || A_Index2 == 96) {
            htvmKeywords_temp += A_LoopField2 + "|";
        }
        if (A_Index2 == 77) {
            allFunctionNamesString3 += "|" + Trim(A_LoopField2);
        }
        if (A_Index2 >= 49 && A_Index2 <= 63) {
            staticTypes_temp += A_LoopField2 + "|";
        }
        if (A_Index2 >= 88 && A_Index2 <= 92) {
            staticTypes_temp += A_LoopField2 + "|";
        }
        if (A_Index2 == 145 || A_Index2 == 146 || A_Index2 == 6) {
            builtInVars_temp += A_LoopField2 + "|";
        }
        if (A_Index2 >= 103 && A_Index2 <= 126) {
            operators_temp += A_LoopField2 + "|";
        }
        if (A_Index2 >= 140 && A_Index2 <= 141) {
            operators_temp += A_LoopField2 + "|";
        }
        if (A_Index2 >= 82 && A_Index2 <= 87) {
            arrayMethods_temp += Trim(StrReplace(A_LoopField2, ".", "")) + "|";
        }
        if (A_Index2 >= 7 && A_Index2 <= 43) {
            programmingBlocksAndImport_temp += A_LoopField2 + "|";
        }
        if (A_Index2 == 98) {
            htvm_comment_temp = Trim(A_LoopField2);
        }
        if (A_Index2 == 99) {
            htvm_commentOpen1_temp = Trim(A_LoopField2);
        }
        if (A_Index2 == 100) {
            htvm_commentClose2_temp = Trim(A_LoopField2);
        }
        if (A_Index2 == 46 || A_Index2 == 47 || A_Index2 == 48 || A_Index2 == 97) {
            htvm_trueFalseGlobalNull_temp += A_LoopField2 + "|";
        }
    }
}
builtInCommands_temp = StringTrimRight(builtInCommands_temp, 1);
htvmKeywords_temp = StringTrimRight(htvmKeywords_temp, 1);
staticTypes_temp = StringTrimRight(staticTypes_temp, 1);
builtInVars_temp = StringTrimRight(builtInVars_temp, 1);
operators_temp = StringTrimRight(operators_temp, 1);
arrayMethods_temp = StringTrimRight(arrayMethods_temp, 1);
programmingBlocksAndImport_temp = StringTrimRight(programmingBlocksAndImport_temp, 1);
htvm_trueFalseGlobalNull_temp = StringTrimRight(htvm_trueFalseGlobalNull_temp, 1);
var htvmKeywords = htvmKeywords_temp.replace(/[^A-Za-z0-9_|\s]/g, '').replace(/^\d+/g, '').replace(/\|+/g, '|').replace(/^(\|)+|(\|)+$/g, '');
var builtInCommands = builtInCommands_temp.replace(/[^A-Za-z0-9_|\s]/g, '').replace(/^\d+/g, '').replace(/\|+/g, '|').replace(/^(\|)+|(\|)+$/g, '');
var builtInFunctions = allFunctionNamesString3.replace(/[^A-Za-z0-9_|\s]/g, '').replace(/^\d+/g, '').replace(/\|+/g, '|').replace(/^(\|)+|(\|)+$/g, '');
var staticTypes = staticTypes_temp.replace(/[^A-Za-z0-9_|\s]/g, '').replace(/^\d+/g, '').replace(/\|+/g, '|').replace(/^(\|)+|(\|)+$/g, '');
var builtInVars = builtInVars_temp.replace(/[^A-Za-z0-9_|\s]/g, '').replace(/^\d+/g, '').replace(/\|+/g, '|').replace(/^(\|)+|(\|)+$/g, '');
var arrayMethods = arrayMethods_temp.replace(/[^A-Za-z0-9_|\s]/g, '').replace(/^\d+/g, '').replace(/\|+/g, '|').replace(/^(\|)+|(\|)+$/g, '');
var programmingBlocksAndImport = programmingBlocksAndImport_temp.replace(/[^A-Za-z0-9_|\s]/g, '').replace(/^\d+/g, '').replace(/\|+/g, '|').replace(/^(\|)+|(\|)+$/g, '');
var htvm_trueFalseGlobalNull = htvm_trueFalseGlobalNull_temp.replace(/[^A-Za-z0-9_|\s]/g, '').replace(/^\d+/g, '').replace(/\|+/g, '|').replace(/^(\|)+|(\|)+$/g, '');
var htvm_operators = operators_temp.replace(/[^A-Za-z0-9_|\s]/g, '').replace(/^\d+/g, '').replace(/\|+/g, '|').replace(/^(\|)+|(\|)+$/g, '');
        
        
        var htvm_comment = htvm_comment_temp;
        // Escape special characters in the comment symbol (just in case)
        var escapedComment = htvm_comment.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
        var htvm_commentOpen1 = htvm_commentOpen1_temp.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
        var htvm_commentClose2 = htvm_commentClose2_temp.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
        this.$rules = {
            start: [
                { token: "comment", regex: escapedComment + ".*$" },
                { token: "comment.block", regex: new RegExp(htvm_commentOpen1), next: "comment_block" },
                { token: "keyword", regex: "\\b(?:" + htvmKeywords + ")\\b" },
                { token: "command", regex: "\\b(?:" + builtInCommands + ")(?=\\,)" },
                { token: "functions", regex: "\\b(?:" + builtInFunctions + ")(?=\\()" },
                { token: "BuildInFunc", regex: "\\b(?:" + builtInVars + ")\\b" },
                { token: "arrayMethods", regex: "\\.(?:" + arrayMethods + ")\\b" },
                { token: "static_types", regex: "\\b(?:" + staticTypes + ")\\b" },
                { token: "programmingBlocksAndImport", regex: "\\b(?:" + programmingBlocksAndImport + ")\\b" },
                { token: "operators", regex: "\\b(?:" + htvm_operators + ")\\b" },
                { token: "trueANDfalse", regex: "\\b(?:" + htvm_trueFalseGlobalNull + ")\\b" },
                { token: "variables", regex: "\\b[a-zA-Z_][a-zA-Z0-9_]*\\b" },
                { token: "constant.numeric", regex: "\\b[0-9]+\\b" },
                { token: "braces_Open", regex: "\\{" },
                { token: "braces_Close", regex: "\\}" },
              { token: "string", regex: '".*?"' },
              // Multi-line comments
              {
                token: "comment.block", // Token for multi-line comments
               regex: new RegExp(htvm_commentOpen1),
                next: "comment_block",
              },
            ],
            comment_block: [
              {
                token: "comment.block",
                regex: new RegExp(htvm_commentClose2),
                next: "start", // Go back to the start state
              },
              {
                token: "comment.block",
                regex: /.*/, // Any other content within the comment
              },
            ],
          };
        };
  oop.inherits(HTVMHighlightRules, TextHighlightRules);
    var Mode = function() {
        this.HighlightRules = HTVMHighlightRules;
    };
    oop.inherits(Mode, TextMode);
    exports.Mode = Mode;
});