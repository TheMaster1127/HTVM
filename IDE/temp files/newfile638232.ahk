#EscapeChar \


; Print function for various types
print(value) {
        MsgBox % value
}

HTVM_Size(arr) {
    return arr.Length()
}


arr123 := [1, 3, 5]
Loop, % HTVM_Size(arr123) {
    print(arr123[A_Index])
}

