

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
    

    

}
main();