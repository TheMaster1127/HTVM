#EscapeChar \


; Print function for various types
print(value) {
    if IsObject(value) {
        str := ""
        for index, element in value
            str .= element ", "
        MsgBox % Trim(str, ", ")  ; Remove trailing comma and space
    } else {
        MsgBox % value
    }
}

STR(value) {
    return value
}

HTVM_Append(arr, value) {
    arr.Push(value)
}

HTVM_Size(arr) {
    return arr.Length()
}


; This is a preview of your language and how it will look.
; Here's how types will appear if you only define them:
varName1 := ""
varName2 := ""
varName3 := ""
varName4 := ""
varName5 := ""
varName6 := ""
varName7 := ""
varName8 := ""
; Alternatively, you can define them like this:
varName9 := 34
; Here's how to define a function with static types when converting to statically typed languages like:
; TypeScript, C++, Go, C#, Java, Kotlin, Nim, Swift, and Dart.
; However, even if you're not targeting a statically typed language (e.g. JavaScript or Python),
; the types will be stripped away automatically and the function will still work as expected.
funcName1(paramVar1, paramVar2 := "", paramVar3 := false, paramVar4 := 1.5) {
    ; This is how the global keyword works if we convert to Python and AutoHotKey.
    ; But even if we don't, it will just be removed, so you can add it if you want to convert to Python and AutoHotKey as well.
    global varName5
    ; Here's how if, else if, and else statements will look:
    if (varName1 = paramVar1) {
        print("varName1 is equal to paramVar1")
    }
    else if (varName1 != paramVar1 || varName1 <= paramVar1) {
        print("varName1 is less than or equal to paramVar1")
    } else {
        print("varName1 is NOT less than or equal to paramVar1 or something else")
    }
    ; this is how the return keyword will look like in your lang
    return
}
; This is where the main function will start. It's just a label, so don't worry.
funcName1(varName9)
; this is how a while loop works in your lang
var1 := false
while (var1 = false) {
    print("we are inside the while loop")
    var1 := true
}
print("we are outside the while loop")
; this is how to use a loop whit arrays
array123 := ["hey"]
HTVM_Append(array123, "hello")
HTVM_Append(array123, "how")
HTVM_Append(array123, "are")
HTVM_Append(array123, "you")
HTVM_Append(array123, "doing")
Loop, % HTVM_Size(array123) {
    print("iteration: " . STR(A_Index))
    print("Item: " . array123[A_Index])
}
print("this is how the escape char looks like \nthis is a new line")
/*
this is a comment block
this is a comment block
*/
; this is how to use an AutoHotKey like Loop
Loop, 10 {
    if (A_Index THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR 2 = 0) {
        continue
    }
    print(A_Index)
}
; this is how to use an AutoHotKey like infinite Loop
Loop {
    if (A_Index = 5) {
        break
    } else {
        print(A_Index)
    }
}
; this is how to use an AutoHotKey like Loop, parse
someText := "hello how are you doing\ntoday we are good."
Loop, Parse, someText, " ", "\n" 
{
    print(A_LoopField)
}
; Error Handling
try {
    throw "Something went wrong!"
}
catch e {
    print(e)
}
finally {
    print("Finally block executed")
}
