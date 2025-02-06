#EscapeChar \


; Print function for various types
print(value) {
        MsgBox % value
}


szdfxc0() {
    return "hi"
}
szdfxc(var1 := "hi") {
    print(var1)
    print("hi2 void")
}
szdfxc1(var0, var1 := "hi", var2 := "hi2") {
    print(var0)
    print(var1)
    print(var2)
    print("hi2 void")
}
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
/*
waedsfdsaeds
aedsf
saedsfxawdsfdfsaw
fddf
sefdf
saersdsaersdgfd
*/
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
szdfxc2(var1 := "hi", var2 := "hi2") {
    print(var1)
    print(var2)
    print("hi2 void")
}




print(szdfxc0())
szdfxc()
szdfxc1(5)
szdfxc1(6, "hello")
szdfxc2()
szdfxc2("HI1")
szdfxc2("HI1", "HI2")
print("Hello, World!")
Loop, 5 {
    print(A_Index)
}