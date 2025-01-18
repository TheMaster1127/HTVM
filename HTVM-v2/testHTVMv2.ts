

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


async function main(): Promise<void> {
    for (let A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        print("hello HTVM v2");
        print("hello HTVM\nv2");
        print(A_Index1);
        for (let A_Index2 = 0; A_Index2 < 5 + 0; A_Index2++) {
            print("hello HTVM v2");
            print("hello HTVM\nv2");
            for (let A_Index3 = 0; A_Index3 < 5 + 0; A_Index3++) {
                print("hello HTVM v2");
                print("hello HTVM\nv2");
                print(A_Index3);
            }
            print(A_Index2);
        }
    }
    print(5+5 != 5 !SZDS() + "A+-+--+ != ADSF" + "WSADFD" + "qwadsf" + adsf >= 3 <= qwerd > qwretr < wdsdf = 5 != 8);
    print("QWADSDF" + "qawdsf" || var1 ! var4 + "ASDFX" + !ADSFD("Qwads" + "QASD" + "aszd" < 6) ? false : true || null && false);
    print(HTVM_Size(aszd) HTVM_Append(aszd, HTVM_Size(aszd)));
    Avar123 = StringTrimRight(STRRAWSD, 1);
    if(var1 == 5 && var2w3erf < 6);
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var1 = 1
    print((var1 == 1) ? "hello" : "bye");
    var1 = 0
    print((var1 == 1) ? "hello" : "bye");
}
main();