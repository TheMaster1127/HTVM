

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


async function func1(var1) {
    return var1 + var1;
}
async function func2(var1) {
    print(var1 + var1);
}
function func3(var1, var2 = "hello") {
    print(var1 + " " + var2);
}
async function main() {
    print(awaitA func1("hi1"));
    await func2("hi2");;
    func3("hi3");
    func3("hi3", "hello3");
    var var1;
    var myArr0 = [];
    HTVM_Append(myArr0, true);
    HTVM_Append(myArr0, false);
    HTVM_Append(myArr0, true);
    let myArr = [5, 6, 7];
    for (let A_IndexA1 = 0; A_IndexA1 < 5 + 0; A_IndexA1++) {
        var1 = 6;
        HTVM_Append(myArr, A_IndexA1);
    }
    for (let A_IndexA2 = 0; A_IndexA2 < HTVM_Size(myArr) + 0; A_IndexA2++) {
        print(myArr[A_IndexA2]);
    }
    for (let A_IndexA3 = 0; A_IndexA3 < HTVM_Size(myArr0) + 0; A_IndexA3++) {
        print(myArr0[A_IndexA3]);
    }
    if (var1 == 6) {
        print(var1);
    }
    else if (var1 == 7) {
        print(var1);
    }
    var var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn";
    items4 = LoopParseFunc(var123, "\n", "\r")
    for (let A_IndexA4 = 0; A_IndexA4 < items4.length + 0; A_IndexA4++) {
        const A_LoopFieldA4 = items4[A_IndexA4 - 0];
        if (A_IndexA4 == 0) {
            print(A_IndexA4);
        }
        print(A_LoopFieldA4);
    }
    print("==================");
    var var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg";
    items5 = LoopParseFunc(var1234, ",");
    for (let A_IndexA5 = 0; A_IndexA5 < items5.length + 0; A_IndexA5++) {
        const A_LoopFieldA5 = items5[A_IndexA5 - 0];
        if (A_IndexA5 == 0) {
            print(A_IndexA5);
        }
        print(A_LoopFieldA5);
    }
    print("==================");
    var var12345 = "hello";
    items6 = LoopParseFunc(var12345)
    for (let A_IndexA6 = 0; A_IndexA6 < items6.length + 0; A_IndexA6++) {
        const A_LoopFieldA6 = items6[A_IndexA6 - 0];
        print(A_LoopFieldA6);
    }
}
main();