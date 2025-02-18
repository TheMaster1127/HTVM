

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

function HTVM_Append<T>(arr: T[], value: T): void {
    arr.push(value);
}

function HTVM_Pop<T>(arr: T[]): void {
    arr.pop();
}

function HTVM_Size<T>(arr: T[]): number {
    return arr.length;
}

function HTVM_Insert<T>(arr: T[], index: number, value: T): void {
    arr.splice(index, 0, value);
}

function HTVM_Remove<T>(arr: T[], value: T): void {
    const index = arr.indexOf(value);
    if (index !== -1) arr.splice(index, 1);
}

function HTVM_IndexOf<T>(arr: T[], value: T): number {
    return arr.indexOf(value);
}


// start


























function func0(input: string): void {
  console.log(input);
}


function func1(var1: number, var2: string, var3: number, var4: number, var5: number, var6: bigint, var7: number, var8: string, var9: boolean, var10: number, var11: number, var12: number, var13: number, var14: bigint): void {
    print(var1);
    print(var2);
    print(var3);
    print(var4);
    print(var5);
    print(var6);
    print(var7);
    print(var8);
    print(var9);
    print(var10);
    print(var11);
    print(var12);
    print(var13);
    print(var14);
}
function func2(var1: number): number {
    return var1;
}
function func3(var1: string): string {
    return var1;
}
function func4(var1: number): number {
    return var1;
}
function func5(var1: number): number {
    return var1;
}
function func6(var1: number): number {
    return var1;
}
function func7(var1: bigint): bigint {
    return var1;
}
function func8(var1: number): number {
    return var1;
}
function func9(var1: string): string {
    return var1;
}
function func10(var1: boolean): boolean {
    return var1;
}
function func11(var1: number): number {
    return var1;
}
function func12(var1: number): number {
    return var1;
}
function func13(var1: number): number {
    return var1;
}
function func14(var1: number): number {
    return var1;
}
function func15(var1: bigint): bigint {
    return var1;
}
/*
this
is
a
multy
line
comment
*/
// outside vars
var var01: number = 3.1234567891011;
var var02: string = 'a';
var var03: number = 25;
var var04: number = 30;
var var05: number = 35;
var var06: bigint = 40n;
var var07: number = 100;
var var08: string = "hello var ouside";
var var09: boolean = false;
var var010: number = 3.14;
var var011: number = 100;
var var012: number = 200;
var var013: number = 230;
var var014: bigint = 80009n;
async function main(): Promise<void> {
    var var_1: number;
    var var_2: string;
    var var_3: number;
    var var_4: number;
    var var_5: number;
    var var_6: bigint;
    var var_7: number;
    var var_8: string;
    var var_9: boolean;
    var var_10: number;
    var var_11: number;
    var var_12: number;
    var var_13: number;
    var var_14: bigint;
    func1(var01, var02, var03, var04, var05, var06, var07, var08, var09, var010, var011, var012, var013, var014);
    var_1 = func2(var01);
    var_2 = func3(var02);
    var_3 = func4(var03);
    var_4 = func5(var04);
    var_5 = func6(var05);
    var_6 = func7(var06);
    var_7 = func8(var07);
    var_8 = func9(var08);
    var_9 = func10(var09);
    var_10 = func11(var010);
    var_11 = func12(var011);
    var_12 = func13(var012);
    var_13 = func14(var013);
    var_14 = func15(var014);
    print(var_1);
    print(var_2);
    print(var_3);
    print(var_4);
    print(var_5);
    print(var_6);
    print(var_7);
    print(var_8);
    print(var_9);
    print(var_10);
    print(var_11);
    print(var_12);
    print(var_13);
    print(var_14);
    // start
    

    

    

    

    

    

    

    

    

    

    

    

    

    func0("Hello World");
    

    print("==================================");
    for (let A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        if (A_Index1 == 0) {
            print(A_Index1);
        }
        else if (A_Index1 == 1) {
            print(A_Index1);
        }
        else if (A_Index1 == 2) {
            print(A_Index1);
        }
        else if (A_Index1 == 3) {
            print(A_Index1);
        }
        else if (A_Index1 == 4) {
            print(A_Index1);
        }
        else if (A_Index1 == 5) {
            print(A_Index1);
        } else {
            print("HOW????");
            print(A_Index1);
        }
    }
    var vars1: boolean = false;
    var vars2: number = 0;
    while (vars1 == false) {
        vars2++;
        print(vars2);
        if (vars2 == 6) {
            vars1 = true;
        }
    }
    for (let A_Index2 = 0; A_Index2 < someLimit; A_Index2++) {
        if (A_Index2 == 6) {
            break;
        } else {
            continue;
        }
        // this is only for lua
        ::continue::
    }
    var str1: string = "hello 123 hello2";
    let items3 = LoopParseFunc(str1, " ")
    for (let A_Index3 = 0; A_Index3 < items3.length; A_Index3++) {
        let A_LoopField3 = items3[A_Index3 - 0];
        print(A_LoopField3);
    }
    print("==================");
    let items4 = LoopParseFunc(str1);
    for (let A_Index4 = 0; A_Index4 < items4.length; A_Index4++) {
        let A_LoopField4 = items4[A_Index4 - 0];
        print(A_LoopField4);
        if (A_LoopField4 == "2") {
            break;
        } else {
            continue;
        }
        ::continue::
    }
    /*
    keyWordArrayAppend
    keyWordArrayPop
    keyWordArraySize
    keyWordArrayInsert
    keyWordArrayRemove
    keyWordArrayIndexOf
    keyWordArrayDefinition
    keyWordArrayOfIntegersDefinition
    keyWordArrayOfStringsDefinition
    keyWordArrayOfFloatingPointNumbersDefinition
    keyWordArrayOfBooleansDefinition
    */
    let arr1: string[] = ["hello1", "hello2"];
    let arr2: boolean[] = [true, false];
    let arr3: number[] = [3.13, 3.14];
    let arr4: number[] = [1, 6, 2];
    let arr5: string[] = ["real STR"];
    // Array operations
    HTVM_Append(arr1, "hello3");
    var sizeArr1: number = HTVM_Size(arr1);
    print("the size of arr1 is:");
    print(sizeArr1);
    HTVM_Insert(arr1, 1, "hello?????");
    HTVM_Remove(arr1, 0);
    var idx1: number = HTVM_IndexOf(arr1, "hello2");
    print("the index of arr1 for hello2 is:");
    print(idx1);
    HTVM_Pop(arr1);
    for (let A_Index5 = 0; A_Index5 < HTVM_Size(arr1) + 0; A_Index5++) {
        print(arr1[A_Index5]);
    }
    HTVM_Append(arr2, true);
    var sizeArr2: number = HTVM_Size(arr2);
    print("the size of arr2 is:");
    print(sizeArr2);
    HTVM_Insert(arr2, 1, false);
    HTVM_Remove(arr2, 0);
    var idx2: number = HTVM_IndexOf(arr2, true);
    print("the index of arr2 for true is:");
    print(idx2);
    HTVM_Pop(arr2);
    for (let A_Index6 = 0; A_Index6 < HTVM_Size(arr2) + 0; A_Index6++) {
        print(arr2[A_Index6]);
    }
    HTVM_Append(arr3, 6.489);
    var sizeArr3: number = HTVM_Size(arr3);
    print("the size of arr3 is:");
    print(sizeArr3);
    HTVM_Insert(arr3, 1, 1.556);
    HTVM_Remove(arr3, 0);
    var idx3: number = HTVM_IndexOf(arr3, 3.14);
    print("the index of arr3 for 3.14 is:");
    print(idx3);
    HTVM_Pop(arr3);
    for (let A_Index7 = 0; A_Index7 < HTVM_Size(arr3) + 0; A_Index7++) {
        print(arr3[A_Index7]);
    }
    HTVM_Append(arr4, 69);
    var sizeArr4: number = HTVM_Size(arr4);
    print("the size of arr4 is:");
    print(sizeArr4);
    HTVM_Insert(arr4, 1, 420);
    HTVM_Remove(arr4, 0);
    var idx4: number = HTVM_IndexOf(arr4, 69);
    print("the index of arr4 for 69 is:");
    print(idx4);
    HTVM_Pop(arr4);
    for (let A_Index8 = 0; A_Index8 < HTVM_Size(arr4) + 0; A_Index8++) {
        print(arr4[A_Index8]);
    }
    HTVM_Append(arr5, "hello3real");
    var sizeArr5: number = HTVM_Size(arr5);
    print("the size of arr5 is:");
    print(sizeArr5);
    HTVM_Insert(arr5, 1, "hello?real????");
    HTVM_Remove(arr5, 0);
    var idx5: number = HTVM_IndexOf(arr5, "hello3real");
    print("the index of arr5 for hello3real is:");
    print(idx5);
    HTVM_Pop(arr5);
    for (let A_Index9 = 0; A_Index9 < HTVM_Size(arr5) + 0; A_Index9++) {
        print(arr5[A_Index9]);
    }
    /*
    keyWordThrow
    keyWordErrorMsg
    keyWordTry
    keyWordCatch
    keyWordFinally
    */
    try {
        print("Trying...");
        throw new Error("Something went wrong!");
    }
    catch (e) {
        print("Caught an error:");
        print(e.message);
    }
    finally {
        print("This always runs, success or error.");
    }
    print("==============================================");
}
main();
