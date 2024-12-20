

function print(value) {
    console.log(value)
}


let theArr = [];
theArr.push(1);
theArr.push(2);
theArr.push(2);
theArr.push(3);
theArr.push(3);
theArr.push(3);
let tempArr = [];
let outArr = [];
var currnet = 0;
var found = 0;
for (let A_Index1 = 0; A_Index1 < theArr.length + 0; A_Index1++) {
    if (A_Index1 != 0) {
        currnet = A_Index1;
        for (let A_Index2 = 0; A_Index2 < tempArr.length + 0; A_Index2++) {
            if (tempArr[A_Index2] == theArr[currnet]) {
                found = 1;
                break;
            }
        }
        if (found != 1) {
            outArr.push(theArr[A_Index1]);
        }
        tempArr.push(theArr[A_Index1]);
        found = 0;
    } else {
        tempArr.push(theArr[A_Index1]);
        outArr.push(theArr[A_Index1]);
    }
}
print(outArr);