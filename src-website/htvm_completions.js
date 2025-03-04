

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

function Trim(inputString) {
    return inputString ? inputString.trim() : "";
}


let allKeyWordsIn = ""; // Global variable to store the result
let HTVM_Syntax_AutoComplete = []; // Global array for autocomplete
let allKeyWordsOut = "";
let allFunctionNamesString = ""; // Global string to store function names
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
    else
    {
        // If key is missing, fetch data from the remote file
    const url = 'https://raw.githubusercontent.com/TheMaster1127/HTVM/refs/heads/main/HTVM-instructions.txt';
    const fetchedData = await fetchFirst161Lines(url);
    if (fetchedData) 
    {
        localStorage.setItem(storageKey, JSON.stringify(fetchedData.split('\n'))); // Store in localStorage
        allKeyWordsIn = fetchedData; // Save in global variable
    } 
    else
    {
        console.error('Failed to fetch data from the remote file');
    } 
    }
}
async function getAllKeyWords() {
    await getAllKeyWordsIn();
    await getFunctionNames();
    const id = new URLSearchParams(window.location.search).get('id');
if (!id) {
    console.error('No ID found in the URL');
    return;
}
const storageKey = "htvm_lang_" + id;
let storedData = localStorage.getItem(storageKey);
// If the key exists, use localStorage data and return
if (storedData !== null) {
    allKeyWordsIn = JSON.parse(storedData);
    // Convert the array into a string (each index becomes a new line)
    allKeyWordsIn = allKeyWordsIn.join('\n'); // This turns the array into a string with each element on a new line
    // Now you can use the allKeyWordsIn string here for further processing
    //console.log(allKeyWordsIn);  // Example of using the resulting string
} else {
    console.error('No data found in localStorage for the given key');
}
    var allKeyWordsIn_OUT = "";
    var allKeyWordsIn_OUT_TEMP = "";
    items1 = LoopParseFunc(allKeyWordsIn, "\n", "\r")
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        if (A_Index1 != 0 && A_Index1 != 1) {
            if (A_Index1 == 149) {
                break;
            }
            if (A_Index1 == 2) {
                items2 = LoopParseFunc(A_LoopField1, "|")
                for (let A_Index2 = 0; A_Index2 < items2.length + 0; A_Index2++) {
                    const A_LoopField2 = items2[A_Index2 - 0];
                    items3 = LoopParseFunc(A_LoopField2, ",");
                    for (let A_Index3 = 0; A_Index3 < items3.length + 0; A_Index3++) {
                        const A_LoopField3 = items3[A_Index3 - 0];
                        if (A_Index3 == 0) {
                            allKeyWordsIn_OUT += A_LoopField3 + "\n";
                            break;
                        }
                    }
                }
            } else {
                allKeyWordsIn_OUT_TEMP = A_LoopField1;
                const isValidStart = /^[A-Za-z_]{2}/.test(allKeyWordsIn_OUT_TEMP);
                if (isValidStart) {
                    allKeyWordsIn_OUT += A_LoopField1 + "\n";
                }
            }
        }
    }
    allKeyWordsOut = allKeyWordsIn_OUT + allFunctionNamesString;
}
(async function () {
    await getAllKeyWords();
    //console.log(allKeyWordsOut);
    
    // Convert to the required format
    HTVM_Syntax_AutoComplete = allKeyWordsOut.split('\n')
        .map(line => line.trim()) // Trim each line
        .filter(line => line.length > 0) // Remove empty lines
        .map(line => ({ name: line })); // Convert to object format
})();
let Completer = {
    getCompletions: function (editor, session, pos, prefix, callback) {
        // If the prefix starts with "p", we allow autocompletion.
        if (prefix.startsWith("p")) {
            // Proceed with filtering completions
        } else {
            // If the prefix length is not more than 1, we return early
            if (prefix.length <= 1) {
                callback(null, []); // Empty array means no suggestions
                return;
            }
        }
        let prefixLower = prefix.toLowerCase();
        let filteredTables = HTVM_Syntax_AutoComplete.filter(function (table) {
            return table.name.toLowerCase().startsWith(prefixLower);
        });
        let limitedTables = filteredTables;
        // Return the filtered and mapped completions
        callback(
            null,
            limitedTables.map(function (table) {
                return {
                    caption: table.name,
                    value: table.name,
                };
            })
        );
    }
};
