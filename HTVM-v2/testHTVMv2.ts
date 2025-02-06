

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


function szdfxc0(): string {
    return "hi";
}
function szdfxc(var1: string = "hi"): void {
    print(var1);
    print("hi2 void");
}
function szdfxc1(var0: number, var1: string = "hi", var2: string = "hi2"): void {
    print(var0);
    print(var1);
    print(var2);
    print("hi2 void");
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
/*
waedsfdsaeds
aedsf
saedsfxawdsfdfsaw
fddf
sefdf
saersdsaersdgfd
*/
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
function szdfxc2(var1: string = "hi", var2: string = "hi2"): void {
    print(var1);
    print(var2);
    print("hi2 void");
}


async function main(): Promise<void> {
    

    print(szdfxc0());
    szdfxc();
    szdfxc1(5);
    szdfxc1(6, "hello");
    var var1: number;
    var var2: string;
    var var3: number;
    var var4: number;
    var var5: number;
    var var6: bigint;
    var var7: number;
    var var8: string;
    var var9: boolean;
    var var10: number;
    var var11: number;
    var var12: number;
    var var13: number;
    var var14: bigint;
    var array1: string[] = [];
    var array2: number[] = [];
    var array3: string[] = [];
    var array4: number[] = [];
    var array5: boolean[] = [];
    szdfxc2();
    szdfxc2("HI1");
    szdfxc2("HI1", "HI2");
    print("Hello, World!");
    for (let A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        print(A_Index1);
    }
}
main();