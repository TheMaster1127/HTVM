#EscapeChar \


; Print function for various types
print(value) {
        MsgBox % value
}


szdfxc0() {
    return "hi"
}
szdfxc() {
    print("hi2 void")
}
print(szdfxc0())
szdfxc()
print("Hello, World!")
Loop, 5 {
    print(A_Index)
}
