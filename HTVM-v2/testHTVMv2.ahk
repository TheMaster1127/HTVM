#EscapeChar \


; Print function for various types
print(value) {
        MsgBox % value
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



