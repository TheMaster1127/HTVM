

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


async function main(): Promise<void> {
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
    for (let A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        print(A_Index1);
    }
    */
}
main();
