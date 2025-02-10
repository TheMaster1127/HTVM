

function LoopParseFunc(varString: string, delimiter1: string = "", delimiter2: string = ""): string[] {
    let items: string[];
    if (delimiter1 === "" && delimiter2 === "") {
        // If no delimiters are provided, return an array of characters
        items = [...varString];
    } else {
        // Construct the regular expression pattern for splitting the string
        const pattern = `[${delimiter1}${delimiter2}]+`;
        // Split the string using the constructed pattern
        items = varString.split(new RegExp(pattern));
    }
    return items;
}

// Print function for various types
function print(value: any): void {
    if (typeof value === "string") {
        console.log(value);
    } else if (typeof value === "number") {
        console.log(value.toString());
    } else if (typeof value === "boolean") {
        console.log(value ? "true" : "false");
    } else {
        console.log("Unsupported type");
    }
}


async function main(): Promise<void> {
    var var1: string;
    var1 = "hello man whats up";
    var var2: string;
    var2 = "hello\nman\nwhats\rup";
    let items1 = LoopParseFunc(var1, " ")
    for (let A_Index1 = 0; A_Index1 < items1.length; A_Index1++) {
        let A_LoopField1 = items1[A_Index1 - 0]
        print(A_LoopField1);
    }
    let items2 = LoopParseFunc(var2, "\n", "\r")
    for (let A_Index2 = 0; A_Index2 < items2.length; A_Index2++) {
        let A_LoopField2 = items2[A_Index2 - 0]
        print(A_LoopField2);
    }
}
main();