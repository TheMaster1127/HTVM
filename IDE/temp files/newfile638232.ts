

// Print function for various types
function print(value: any): void {
    console.log(value);
}

function HTVM_Size<T>(arr: T[]): number {
    return arr.length;
}


async function main(): Promise<void> {
    let arr123: number[] = [1, 3, 5];
    for (let A_Index1 = 0; A_Index1 < HTVM_Size(arr123) + 0; A_Index1++) {
        print(arr123[A_Index1]);
    }
    

}
main();