

function print(value) {
    console.log(value)
}

// Function to sort and remove duplicates
function sortArr(inputArray) {
    // Remove duplicates using Set and sort the array
    return [...new Set(inputArray)].sort();
}

// Function to sort an array of strings by length in descending order
function sortArrByLenOnly(array) {
    return array.sort((a, b) => b.length - a.length);
}


async function main() {
    let test = [];
    test.push("hello");
    test.push("+");
    test.push("+");
    test.push(".");
    test.push("!=");
    test.push("!");
    sortArrByLenOnly(test);
    for (let A_Index1 = 0; A_Index1 < test.length + 0; A_Index1++) {
        print(test[A_Index1]);
    }
}
main();
