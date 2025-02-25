

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

// Function to generate a random integer between min and max (inclusive)
function Random(min, max) {
    // Generate and return a random number within the specified range
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

function Sleep(milliseconds) {
    // Sleep for the specified number of milliseconds
    return new Promise(resolve => setTimeout(resolve, milliseconds));
}

function Chr(number) {
    // Return the character corresponding to the Unicode code point, or an empty string if out of range
    return (number >= 0 && number <= 0x10FFFF) ? String.fromCharCode(number) : "";
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
        const lines = text.split('\n').slice(161); // Line 162 starts at index 161
        
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
// Function to fetch the first 149 lines from a remote text file
async function fetchFirst149Lines(url) {
    try {
        const response = await fetch(url);
        if (!response.ok) {
            throw new Error(`Network response was not ok: ${response.statusText}`);
        }
        const text = await response.text();
        return text.split('\n').slice(0, 149).join('\n');
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
    let data = localStorage.getItem("htvm_lang_" + id);
    
    if (data) {
        try {
            const arrayData = JSON.parse(data);
            if (Array.isArray(arrayData)) {
                allKeyWordsIn = arrayData.slice(0, 149).join('\n'); // Save in global variable
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
    // If key doesn't exist, fetch data from the remote file
    const url = 'https://raw.githubusercontent.com/TheMaster1127/HTVM/refs/heads/main/HTVM-instructions.txt';
    const fetchedData = await fetchFirst149Lines(url);
    if (fetchedData) {
        localStorage.setItem("htvm_lang_" + id, JSON.stringify(fetchedData.split('\n'))); // Store in localStorage
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
console.log("================================================================")
console.log("================================================================")
console.log("================================================================")
console.log("================================================================")
let lines = allKeyWordsOut3.split('\n'); // Split the string into an array of lines
for (let i = 0; i < lines.length; i++) {
    console.log(i + ": " + lines[i]);
}
console.log("================================================================")
console.log("================================================================")
console.log("================================================================")
console.log("================================================================")
console.log("================================================================")
var makeAllKeyWords1 = "";
var makeAllKeyWords2 = "";
var makeAllKeyWords3 = "";
var makeAllKeyWords4 = "";
var makeAllKeyWords5 = "";
var makeAllKeyWords6 = "";
items2 = LoopParseFunc(allKeyWordsOut3, "\n", "\r")
for (let A_Index2 = 0; A_Index2 < items2.length + 0; A_Index2++) {
    const A_LoopField2 = items2[A_Index2 - 0];
    if (Trim(A_LoopField2) != "") {
        //if (A_Index2 = 1)
    }
}
        var htvmKeywords = "if|else if|else|def obj|prop|crew|alliance|method|while|for|Loop|Loop,|Loop, Parse,|continue|break|func|await|switch|case|throw|try|catch|finally|var|let|const|return|end";
        var builtInCommands = "StringTrimLeft|StringTrimRight|Random|Sleep|FileRead|FileAppend|FileDelete|Sort|MsgBox";
        var builtInFunctions = allFunctionNamesString3;
        var staticTypes = "int|str|void|bool|float|int8|int16|int32|int64|arr|arr int|arr str|arr float|arr bool";
        var builtInVars = "A_Index|A_LoopField|this";
        var arrayMethods = "add|pop|size|insert|rm|indexOf";
        var programmingBlocksAndImport = "___js start|___js end";
        this.$rules = {
            start: [
                { token: "comment", regex: ";.*$" },
                { token: "comment.block", regex: /'''1/, next: "comment_block" },
                { token: "keyword", regex: "\\b(?:" + htvmKeywords + ")\\b" },
                { token: "command", regex: "\\b(?:" + builtInCommands + ")(?=\\,)" },
                { token: "functions", regex: "\\b(?:" + builtInFunctions + ")(?=\\()" },
                { token: "BuildInFunc", regex: "\\b(?:" + builtInVars + ")\\b" },
                { token: "arrayMethods", regex: "\\.(?:" + arrayMethods + ")\\b" },
                { token: "static_types", regex: "\\b(?:" + staticTypes + ")\\b" },
                { token: "programmingBlocksAndImport", regex: "\\b(?:" + programmingBlocksAndImport + ")\\b" },
                { token: "operators", regex: "&&|\\|\\||and|or" },
                { token: "trueANDfalse", regex: "\\b(true|false|global)\\b" },
                { token: "variables", regex: "\\b[a-zA-Z_][a-zA-Z0-9_]*\\b" },
                { token: "constant.numeric", regex: "\\b[0-9]+\\b" },
                { token: "braces_Open", regex: "\\{" },
                { token: "braces_Close", regex: "\\}" },
              { token: "string", regex: '".*?"' },
              // Multi-line comments
              {
                token: "comment.block", // Token for multi-line comments
                regex: /'''1/, // Start of multi-line comment
                next: "comment_block",
              },
            ],
            comment_block: [
              {
                token: "comment.block",
                regex: /.*?'''2/, // End of multi-line comment
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