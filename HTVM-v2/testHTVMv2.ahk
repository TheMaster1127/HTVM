#EscapeChar \


; Print function for various types
print(value) {
        MsgBox % value
}

HTVM_Append(arr, value) {
    arr.Push(value)
}

HTVM_Size(arr) {
    return arr.Length()
}


var1 := ""
myArr0 := []
HTVM_Append(myArr0, true)
HTVM_Append(myArr0, false)
HTVM_Append(myArr0, true)
myArr := [5, 6, 7]
Loop, 5 {
    var1 := 6
    HTVM_Append(myArr, A_Index)
}
Loop, % HTVM_Size(myArr) {
    print(myArr[A_Index])
}
Loop, % HTVM_Size(myArr0) {
    print(myArr0[A_Index])
}
print(var1)
var123 := "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn"
Loop, Parse, var123, "\n", "\r" 
{

    if (A_Index = 0) {
        print(A_Index)
    }
    print(A_LoopField)
}
print("==================")
var1234 := "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg"
Loop, Parse, var1234, "\," 
{

    if (A_Index = 0) {
        print(A_Index)
    }
    print(A_LoopField)
}
