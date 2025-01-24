

function print(value) {
    console.log(value)
}

// Convert value to string
function STR(value) {
    if (value === null || value === undefined) {
        return ""; // Return a string for null or undefined
    } else if (typeof value === 'number') {
        return value.toString();
    } else if (typeof value === 'boolean') {
        return value ? "1" : "0";
    } else if (typeof value === 'string') {
        return value; // Return the string as is
    } else {
        // Handle any unexpected types gracefully
        return String(value); // Convert any other type to a string
    }
}

function Trim(inputString) {
    return inputString ? inputString.trim() : "";
}

function StringTrimRight(input, numChars) {
    return (numChars <= input.length) ? input.substring(0, input.length - numChars) : input;
}

function HTVM_Append(arr, value) {
    arr.push(value);
}

function HTVM_Size(arr) {
    return arr.length;
}


async function main() {
    for (let A_Index1 = 0; A_Index1 < 20 + 0; A_Index1++) {
        print("hello HTVM import");
        print("hello HTVM\nimport");
    }
    for (let A_Index2 = 0; A_Index2 < 6 + 0; A_Index2++) {
        print("hello HTVM import");
        print("hello HTVM\nimport");
    }
    for (let A_Index3 = 0; A_Index3 < 5 + 0; A_Index3++) {
        print("hello\" HTVM v2");
        print("hello HTVM\\v2\\\\s");
        print("hello HTVM\nv2");
        print("hello HTVM\\nv2");
        print(A_Index3);
        for (let A_Index4 = 0; A_Index4 < 5 + 0; A_Index4++) {
            print("hello HTVM v2");
            print("hello HTVM\nv2");
            for (let A_Index5 = 0; A_Index5 < 5 + 0; A_Index5++) {
                print("hello HTVM v2");
                print("hello HTVM\nv2");
                print(A_Index5);
            }
            print(A_Index4);
        }
    }
    await qWAERSFD();
    qWAERSFD(await waedsfd());
    print(5+5 != 5 !SZDS() + "A+-+--+ != ADSF" + "WSADFD" + "qwadsf" + adsf >= 3 <= qwerd > qwretr < wdsdf == 5 != 8);
    print("QWADSDF" + "qawdsf" || var1 ! var4 + "ASDFX" + !ADSFD("Qwads" + "QASD" + "aszd" < 6) ? false : true || null && false);
    print(HTVM_Size(aszd) HTVM_Append(aszd, HTVM_Size(aszd)));
    Avar123 = StringTrimRight(STRRAWSD, 1);
    if(var1 == 5 && var2w3erf < 6);
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var1 = 1
    print((var1 == 1) ? "hello" : "bye");
    var1 = 0
    print((var1 == 1) ? "hello" : "bye");
    if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    } else {
        print(5+5);
    }
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    try {
        throw new Error("this is an ERROR HTVM v2");
    }
    catch (ee) {
        print(ee.message);
    }
    finally {
        print("finally finally finally finally");
    }
    // some comment
    while (true) {
        print("hi from HTVM v2 still in development");
        break;
    }
    /*
    WAESFD
    WAQESR
    FRAWE
    DSFDSADSDF
    asfdx
    for (let A_Index6 = 0; A_Index6 < 5 + 0; A_Index6++) {
        print(A_Index6);
    }
    */
}
main();
