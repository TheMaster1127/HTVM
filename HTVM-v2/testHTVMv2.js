

function print(value) {
    console.log(value)
}


async function szdfxc0() {
    return "hi";
}
function szdfxc(var1 = "hi") {
    print(var1);
    print("hi2 void");
}
function szdfxc1(var0, var1 = "hi", var2 = "hi2") {
    print(var0);
    print(var1);
    print(var2);
    print("hi2 void");
}
async function main() {
    print(szdfxc0());
    szdfxc();
    szdfxc1(5);
    szdfxc1(6, "hello");
    print("Hello, World!");
    for (let A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        print(A_Index1);
    }
}
main();