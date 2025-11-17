

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
    console.log(value);
}

function STR(value: any): string {
    if (typeof value === "number") {
        return value.toString();
    } else if (typeof value === "boolean") {
        return value ? "1" : "0";
    } else if (typeof value === "string") {
        return value;
    } else {
        return String(value);
    }
}

function HTVM_Append<T>(arr: T[], value: T): void {
    arr.push(value);
}

function HTVM_Size<T>(arr: T[]): number {
    return arr.length;
}


// This is a preview of your language and how it will look.
// Here's how types will appear if you only define them:
var varName1: number;
var varName2: string;
var varName3: boolean;
var varName4: number;
var varName5: number;
var varName6: number;
var varName7: number;
var varName8: bigint;
// Alternatively, you can define them like this:
var varName9: number = 34;
// Here's how to define a function with static types when converting to statically typed languages like:
// TypeScript, C++, Go, C#, Java, Kotlin, Nim, Swift, and Dart.
// However, even if you're not targeting a statically typed language (e.g. JavaScript or Python),
// the types will be stripped away automatically and the function will still work as expected.
function funcName1(paramVar1: number, paramVar2: string = "", paramVar3: boolean = false, paramVar4: number = 1.5): void {
    // This is how the global keyword works if we convert to Python and AutoHotKey.
    // But even if we don't, it will just be removed, so you can add it if you want to convert to Python and AutoHotKey as well.
    // Here's how if, else if, and else statements will look:
    if (varName1 == paramVar1) {
        print("varName1 is equal to paramVar1");
    }
    else if (varName1 != paramVar1 || varName1 <= paramVar1) {
        print("varName1 is less than or equal to paramVar1");
    } else {
        print("varName1 is NOT less than or equal to paramVar1 or something else");
    }
    // this is how the return keyword will look like in your lang
    return;
}
// This is where the main function will start. It's just a label, so don't worry.
async function main(): Promise<void> {
    funcName1(varName9);
    // this is how a while loop works in your lang
    var var1: boolean = false;
    while (var1 == false) {
        print("we are inside the while loop");
        var1 = true;
    }
    print("we are outside the while loop");
    // this is how to use a loop whit arrays
    let array123: string[] = ["hey"];
    HTVM_Append(array123, "hello");
    HTVM_Append(array123, "how");
    HTVM_Append(array123, "are");
    HTVM_Append(array123, "you");
    HTVM_Append(array123, "doing");
    for (let A_Index1 = 0; A_Index1 < HTVM_Size(array123); A_Index1++) {
        print("iteration: " + STR(A_Index1));
        print("Item: " + array123[A_Index1]);
    }
    print("this is how the escape char looks like \nthis is a new line");
    /*
    this is a comment block
    this is a comment block
    */
    // this is how to use an AutoHotKey like Loop
    for (let A_Index2 = 0; A_Index2 < 10; A_Index2++) {
        if (A_Index2 % 2 == 0) {
            continue;
        }
        print(A_Index2);
    }
    // this is how to use an AutoHotKey like infinite Loop
    for (let A_Index3 = 0; ; A_Index3++) {
        if (A_Index3 == 5) {
            break;
        } else {
            print(A_Index3);
        }
    }
    // this is how to use an AutoHotKey like Loop, parse
    var someText: string = "hello how are you doing\ntoday we are good.";
    let items4 = LoopParseFunc(someText, " ", "\n")
    for (let A_Index4 = 0; A_Index4 < items4.length; A_Index4++) {
        let A_LoopField4 = items4[A_Index4 - 0];
        print(A_LoopField4);
    }
    // Error Handling
    try {
        throw new Error("Something went wrong!");
    }
    catch (e) {
        print(e.message);
    }
    finally {
        print("Finally block executed");
    }
    

}
main();