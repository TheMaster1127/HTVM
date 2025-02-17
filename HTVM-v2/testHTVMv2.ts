

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
function func3(var1: string, var2: string = "hello", var3: string = "hello", var4: string = "hello"): void {
    print(var1 + " " + var2 + " " + var3 + " " + var4);
}
async function main(): Promise<void> {
    print(await func1("hi1"));
    await func2("hi2");
    func3("hi3");
    func3("hi3", "hello3");
    func3("hi3", "hello3", "QWAESDRTFG");
    func3("hi3", "hello3", "QWAESDRTFG", "WAESDRFTG44444");
    var var1: number;
    let myArr0: boolean[] = [];
    HTVM_Append(myArr0, true);
    HTVM_Append(myArr0, false);
    HTVM_Append(myArr0, true);
    let myArr: number[] = [5, 6, 7];
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
    if (var1 == 6) {
        print(var1);
    }
    else if (var1 == 7) {
        print(var1);
    }
    var var123: string = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn";
    let items4 = LoopParseFunc(var123, "\n", "\r")
    for (let A_Index4 = 0; A_Index4 < items4.length; A_Index4++) {
        let A_LoopField4 = items4[A_Index4 - 0];
        if (A_Index4 == 0) {
            print(A_Index4);
        }
        print(A_LoopField4);
    }
    print("==================");
    var var1234: string = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg";
    let items5 = LoopParseFunc(var1234, ",")
    for (let A_Index5 = 0; A_Index5 < items5.length; A_Index5++) {
        let A_LoopField5 = items5[A_Index5 - 0];
        if (A_Index5 == 0) {
            print(A_Index5);
        }
        print(A_LoopField5);
    }
    print("==================");
    var var12345: string = "hello";
    let items6 = LoopParseFunc(var12345);
    for (let A_Index6 = 0; A_Index6 < items6.length; A_Index6++) {
        let A_LoopField6 = items6[A_Index6 - 0];
        print(A_LoopField6);
    }
}
main();