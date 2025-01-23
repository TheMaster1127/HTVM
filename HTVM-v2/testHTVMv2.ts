

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
    if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    } else {
        print(5+5);
    }
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    try {
        throw new Error("this is an ERROR HTVM v2");
    }
    catch (ee) {
        print(ee.message);
    }
    finally {
        print("finally finally finally finally");
    }
}
main();