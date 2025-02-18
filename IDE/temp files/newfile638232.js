

function print(value) {
    console.log(value)
}

function HTVM_Size(arr) {
    return arr.length;
}


async function main() {
    let arr123 = [1, 3, 5];
    for (let A_Index1 = 0; A_Index1 < HTVM_Size(arr123) + 0; A_Index1++) {
        print(arr123[A_Index1]);
    }
    

}
main();