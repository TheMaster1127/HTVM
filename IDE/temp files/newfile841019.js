

function print(value) {
    console.log(value)
}


async function loop(count) {
    for (let A_Index1 = 0; A_Index1 < count + 0; A_Index1++) {
        print(A_Index1);
    }
}
async function main() {
    await loop(5 + 5);
}
main();
