#EscapeChar \


; Print function for various types
print(value) {
        MsgBox % value
}


var1 := ""
var1 := "hello man whats up"
var2 := ""
var2 := "hello\nman\nwhats\rup"
Loop, Parse, var1 " " 
{

    print(A_LoopField)
}
Loop, Parse, var2 "\n" "\r" 
{

    print(A_LoopField)
}