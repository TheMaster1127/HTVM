

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

function HTVM_Append(arr, value) {
    arr.push(value);
}

function HTVM_Size(arr) {
    return arr.length;
}


async function main() {
    var var1;
    let myArr0 = [];
    HTVM_Append(myArr0, true);
    HTVM_Append(myArr0, false);
    HTVM_Append(myArr0, true);
    let myArr = [5, 6, 7];
    for (let A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        var1 = 6;
        HTVM_Append(myArr, A_Index1);
    }
    for (let A_Index2 = 0; A_Index2 < HTVM_Size(myArr) + 0; A_Index2++) {
        print(myArr[A_Index2]);
    }
    for (let A_Index3 = 0; A_Index3 < HTVM_Size(myArr0) + 0; A_Index3++) {
        print(myArr0[A_Index3]);
    }
    print(var1);
    var var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn";
    items4 = LoopParseFunc(var123, "\n", "\r")
    for (let A_Index4 = 0; A_Index4 < items4.length + 0; A_Index4++) {
        const A_LoopField4 = items4[A_Index4 - 0];
        if (A_Index4 == 0) {
            print(A_Index4);
        }
        print(A_LoopField4);
    }
    print("==================");
    var var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg";
    items5 = LoopParseFunc(var1234, ",");
    for (let A_Index5 = 0; A_Index5 < items5.length + 0; A_Index5++) {
        const A_LoopField5 = items5[A_Index5 - 0];
        if (A_Index5 == 0) {
            print(A_Index5);
        }
        print(A_LoopField5);
    }
}
main();
