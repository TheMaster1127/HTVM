

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

function HTVM_Size<T>(arr: T[]): number {
    return arr.length;
}


function func1(var1: string): string {
    return var1 + var1;
}
function func2(var1: string): void {
    print(var1 + var1);
}
function func3(var1: string, var2: string = "hello"): void {
    print(var1 + " " + var2);
}
async function main(): Promise<void> {
    print(await func1("hi1"));
    await func2("hi2");;
    func3("hi3");
    func3("hi3", "hello3");
    var var1: number;
    var myArr0: boolean[] = [];
    HTVM_Append(myArr0, true);
    HTVM_Append(myArr0, false);
    HTVM_Append(myArr0, true);
    let myArr: number[] = [5, 6, 7];
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
    var var123: string = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn";
    let items4 = LoopParseFunc(var123, "\n", "\r")
    for (let A_IndexA4 = 0; A_IndexA4 < items4.length; A_IndexA4++) {
        let A_LoopFieldA4 = items4[A_IndexA4 - 0];
        if (A_IndexA4 == 0) {
            print(A_IndexA4);
        }
        print(A_LoopFieldA4);
    }
    print("==================");
    var var1234: string = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg";
    let items5 = LoopParseFunc(var1234, ",")
    for (let A_IndexA5 = 0; A_IndexA5 < items5.length; A_IndexA5++) {
        let A_LoopFieldA5 = items5[A_IndexA5 - 0];
        if (A_IndexA5 == 0) {
            print(A_IndexA5);
        }
        print(A_LoopFieldA5);
    }
    print("==================");
    var var12345: string = "hello";
    let items6 = LoopParseFunc(var12345);
    for (let A_IndexA6 = 0; A_IndexA6 < items6.length; A_IndexA6++) {
        let A_LoopFieldA6 = items6[A_IndexA6 - 0];
        print(A_LoopFieldA6);
    }
}
main();
