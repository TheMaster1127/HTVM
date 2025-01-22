

function print(value) {
    console.log(value)
}


async function main() {
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