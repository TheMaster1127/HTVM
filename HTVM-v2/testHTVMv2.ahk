#EscapeChar \


; Print function for various types
print(value) {
        MsgBox % value
}


try {
    throw "this is an ERROR HTVM v2"
}
catch ee {
    print(ee)
}
finally {
    print("finally finally finally finally")
}
