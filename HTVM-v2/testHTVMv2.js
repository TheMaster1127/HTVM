

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

// Function to simulate input() in JavaScript
function input(promptText) {
    // Display the prompt and get user input
    return prompt(promptText);
}

function HTVM_Append(arr, value) {
    arr.push(value);
}

function HTVM_Pop(arr) {
    arr.pop();
}

function HTVM_Size(arr) {
    return arr.length;
}

function HTVM_Insert(arr, index, value) {
    arr.splice(index, 0, value);
}

function HTVM_Remove(arr, value) {
    let index = arr.indexOf(value);
    if (index !== -1) arr.splice(index, 1);
}

function HTVM_IndexOf(arr, value) {
    return arr.indexOf(value);
}


// start




function func0(input) {
    console.log(input);
}
























function func1(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14) {
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
function func2(var1) {
    return var1;
}
function func3(var1) {
    return var1;
}
function func4(var1) {
    return var1;
}
function func5(var1) {
    return var1;
}
function func6(var1) {
    return var1;
}
function func7(var1) {
    return var1;
}
function func8(var1) {
    return var1;
}
function func9(var1) {
    return var1;
}
function func10(var1) {
    return var1;
}
function func11(var1) {
    return var1;
}
function func12(var1) {
    return var1;
}
function func13(var1) {
    return var1;
}
function func14(var1) {
    return var1;
}
function func15(var1) {
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
var var01 = 3.1234567891011;
var var02 = 'a';
var var03 = 25;
var var04 = 30;
var var05 = 35;
var var06 = 40n;
var var07 = 100;
var var08 = "hello var ouside";
var var09 = false;
var var010 = 3.14;
var var011 = 100;
var var012 = 200;
var var013 = 230;
var var014 = 80009n;
async function main() {
    var var_1;
    var var_2;
    var var_3;
    var var_4;
    var var_5;
    var var_6;
    var var_7;
    var var_8;
    var var_9;
    var var_10;
    var var_11;
    var var_12;
    var var_13;
    var var_14;
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
    var vars1 = false;
    var vars2 = 0;
    while (vars1 == false) {
        vars2++;
        print(vars2);
        if (vars2 == 6) {
            vars1 = true;
        }
    }
    for (let A_Index2 = 0; ; A_Index2++) {
        if (A_Index2 == 6) {
            break;
        } else {
            continue;
        }
        // this is only for lua
        ::continue::
    }
    var str1 = "hello 123 hello2";
    items3 = LoopParseFunc(str1, " ")
    for (let A_Index3 = 0; A_Index3 < items3.length + 0; A_Index3++) {
        const A_LoopField3 = items3[A_Index3 - 0];
        print(A_LoopField3);
    }
    print("==================");
    items4 = LoopParseFunc(str1)
    for (let A_Index4 = 0; A_Index4 < items4.length + 0; A_Index4++) {
        const A_LoopField4 = items4[A_Index4 - 0];
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
    let arr1 = ["hello1", "hello2"];
    let arr2 = [true, false];
    let arr3 = [3.13, 3.14];
    let arr4 = [1, 6, 2];
    let arr5 = ["real STR"];
    // Array operations
    HTVM_Append(arr1, "hello3");
    var sizeArr1 = HTVM_Size(arr1);
    print("the size of arr1 is:");
    print(sizeArr1);
    HTVM_Insert(arr1, 1, "hello?????");
    HTVM_Remove(arr1, 0);
    var idx1 = HTVM_IndexOf(arr1, "hello2");
    print("the index of arr1 for hello2 is:");
    print(idx1);
    HTVM_Pop(arr1);
    for (let A_Index5 = 0; A_Index5 < HTVM_Size(arr1) + 0; A_Index5++) {
        print(arr1[A_Index5]);
    }
    HTVM_Append(arr2, true);
    var sizeArr2 = HTVM_Size(arr2);
    print("the size of arr2 is:");
    print(sizeArr2);
    HTVM_Insert(arr2, 1, false);
    HTVM_Remove(arr2, 0);
    var idx2 = HTVM_IndexOf(arr2, true);
    print("the index of arr2 for true is:");
    print(idx2);
    HTVM_Pop(arr2);
    for (let A_Index6 = 0; A_Index6 < HTVM_Size(arr2) + 0; A_Index6++) {
        print(arr2[A_Index6]);
    }
    HTVM_Append(arr3, 6.489);
    var sizeArr3 = HTVM_Size(arr3);
    print("the size of arr3 is:");
    print(sizeArr3);
    HTVM_Insert(arr3, 1, 1.556);
    HTVM_Remove(arr3, 0);
    var idx3 = HTVM_IndexOf(arr3, 3.14);
    print("the index of arr3 for 3.14 is:");
    print(idx3);
    HTVM_Pop(arr3);
    for (let A_Index7 = 0; A_Index7 < HTVM_Size(arr3) + 0; A_Index7++) {
        print(arr3[A_Index7]);
    }
    HTVM_Append(arr4, 69);
    var sizeArr4 = HTVM_Size(arr4);
    print("the size of arr4 is:");
    print(sizeArr4);
    HTVM_Insert(arr4, 1, 420);
    HTVM_Remove(arr4, 0);
    var idx4 = HTVM_IndexOf(arr4, 69);
    print("the index of arr4 for 69 is:");
    print(idx4);
    HTVM_Pop(arr4);
    for (let A_Index8 = 0; A_Index8 < HTVM_Size(arr4) + 0; A_Index8++) {
        print(arr4[A_Index8]);
    }
    HTVM_Append(arr5, "hello3real");
    var sizeArr5 = HTVM_Size(arr5);
    print("the size of arr5 is:");
    print(sizeArr5);
    HTVM_Insert(arr5, 1, "hello?real????");
    HTVM_Remove(arr5, 0);
    var idx5 = HTVM_IndexOf(arr5, "hello3real");
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