

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
function szdfxc(): void {
    print("hi2 void");
}
async function main(): Promise<void> {
    print(szdfxc0());
    szdfxc();
    print("Hello, World!");
    for (let A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        print(A_Index1);
    }
}
main();
