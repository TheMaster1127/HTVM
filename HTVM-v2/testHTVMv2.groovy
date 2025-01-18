

// Print function
def print = { message ->
    System.out.print("$message\n")
}

def HTVM_Append(arr, value) {
    arr.add(value)
}

def HTVM_Size(arr) {
    return arr.size()
}


for (A_Index1 in 0..5 + 0) {
    print("hello HTVM v2")
    print("hello HTVM\nv2")
    print(A_Index1)
    for (A_Index2 in 0..5 + 0) {
        print("hello HTVM v2")
        print("hello HTVM\nv2")
        for (A_Index3 in 0..5 + 0) {
            print("hello HTVM v2")
            print("hello HTVM\nv2")
            print(A_Index3)
        }
        print(A_Index2)
    }
}
print(5+5 != 5 !SZDS() + "A+-+--+ != ADSF" + "WSADFD" + "qwadsf" + adsf >= 3 <= qwerd > qwretr < wdsdf = 5 != 8)
print("QWADSDF" + "qawdsf" || var1 ! var4 + "ASDFX" + !ADSFD("Qwads" + "QASD" + "aszd" < 6) ? false : true || null && false)
print(HTVM_Size(aszd) HTVM_Append(aszd, HTVM_Size(aszd)))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
var1 = 1
print((var1 == 1) ? "hello" : "bye")
var1 = 0
print((var1 == 1) ? "hello" : "bye")
