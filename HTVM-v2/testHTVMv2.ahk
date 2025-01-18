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



Loop, 5 {
    print("hello HTVM v2")
    print("hello HTVM\nv2")
    print(A_Index)
    Loop, 5 {
        print("hello HTVM v2")
        print("hello HTVM\nv2")
        Loop, 5 {
            print("hello HTVM v2")
            print("hello HTVM\nv2")
            print(A_Index)
        }
        print(A_Index)
    }
}
print(5+5 != 5 !SZDS() . "A+-+--+ != ADSF" . "WSADFD" . "qwadsf" + adsf >= 3 <= qwerd > qwretr < wdsdf = 5 != 8)
print("QWADSDF" . "qawdsf" || var1 ! var4 . "ASDFX" . !ADSFD("Qwads" . "QASD" . "aszd" < 6) ? false : true || "" && false)
print(HTVM_Size(aszd) HTVM_Append(aszd, HTVM_Size(aszd)))
Avar123 = StringTrimRight(STRRAWSD, 1)
if(var1 = 5) && (var2w3erf < 6)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
var1 = 1
print((var1 = 1) ? "hello" : "bye")
var1 = 0
print((var1 = 1) ? "hello" : "bye")