

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
    print("Hello, World!");
    for (let A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
    }
}
main();