#EscapeChar \


; Print function for various types
print(value) {
        MsgBox % value
}

HTVM_Append(arr, value) {
    arr.Push(value)
}

HTVM_Pop(arr) {
    arr.RemoveAt(arr.MaxIndex())
}

HTVM_Size(arr) {
    return arr.Length()
}

HTVM_Insert(arr, index, value) {
    arr.InsertAt(index, value)
}

HTVM_Remove(arr, value) {
    for k, v in arr {
        if (v = value) {
            arr.RemoveAt(k)
            break
        }
    }
}

HTVM_IndexOf(arr, value) {
    for k, v in arr {
        if (v = value)
            return k
    }
    return -1
}


; start




















func0(input) {
    MsgBox, %input%
}








func1(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14) {
    print(var1)
    print(var2)
    print(var3)
    print(var4)
    print(var5)
    print(var6)
    print(var7)
    print(var8)
    print(var9)
    print(var10)
    print(var11)
    print(var12)
    print(var13)
    print(var14)
}
func2(var1) {
    return var1
}
func3(var1) {
    return var1
}
func4(var1) {
    return var1
}
func5(var1) {
    return var1
}
func6(var1) {
    return var1
}
func7(var1) {
    return var1
}
func8(var1) {
    return var1
}
func9(var1) {
    return var1
}
func10(var1) {
    return var1
}
func11(var1) {
    return var1
}
func12(var1) {
    return var1
}
func13(var1) {
    return var1
}
func14(var1) {
    return var1
}
func15(var1) {
    return var1
}
/*
this
is
a
multy
line
comment
*/
; outside vars
var01 := 3.1234567891011
var02 := "a"
var03 := 25
var04 := 30
var05 := 35
var06 := 40
var07 := 100
var08 := "hello var ouside"
var09 := false
var010 := 3.14
var011 := 100
var012 := 200
var013 := 230
var014 := 80009
var_1 := ""
var_2 := ""
var_3 := ""
var_4 := ""
var_5 := ""
var_6 := ""
var_7 := ""
var_8 := ""
var_9 := ""
var_10 := ""
var_11 := ""
var_12 := ""
var_13 := ""
var_14 := ""
func1(var01, var02, var03, var04, var05, var06, var07, var08, var09, var010, var011, var012, var013, var014)
var_1 := func2(var01)
var_2 := func3(var02)
var_3 := func4(var03)
var_4 := func5(var04)
var_5 := func6(var05)
var_6 := func7(var06)
var_7 := func8(var07)
var_8 := func9(var08)
var_9 := func10(var09)
var_10 := func11(var010)
var_11 := func12(var011)
var_12 := func13(var012)
var_13 := func14(var013)
var_14 := func15(var014)
print(var_1)
print(var_2)
print(var_3)
print(var_4)
print(var_5)
print(var_6)
print(var_7)
print(var_8)
print(var_9)
print(var_10)
print(var_11)
print(var_12)
print(var_13)
print(var_14)
; start




















func0("Hello World")








print("==================================")
Loop, 5 {
    if (A_Index = 0) {
        print(A_Index)
    }
    else if (A_Index = 1) {
        print(A_Index)
    }
    else if (A_Index = 2) {
        print(A_Index)
    }
    else if (A_Index = 3) {
        print(A_Index)
    }
    else if (A_Index = 4) {
        print(A_Index)
    }
    else if (A_Index = 5) {
        print(A_Index)
    } else {
        print("HOW????")
        print(A_Index)
    }
}
vars1 := false
vars2 := 0
while (vars1 = false) {
    vars2++
    print(vars2)
    if (vars2 = 6) {
        vars1 := true
    }
}
Loop {
    if (A_Index = 6) {
        break
    } else {
        continue
    }
    ; this is only for lua
    ::continue::
}
str1 := "hello 123 hello2"
Loop, Parse, str1, " " 
{

    print(A_LoopField)
}
print("==================")
Loop, Parse, str1 
{

    print(A_LoopField)
    if (A_LoopField = "2") {
        break
    } else {
        continue
    }
    ::continue::
}
/*
keyWordArrayAppend
keyWordArrayPop
keyWordArraySize
keyWordArrayInsert
keyWordArrayRemove
keyWordArrayIndexOf
keyWordArrayDefinition
keyWordArrayOfIntegersDefinition
keyWordArrayOfStringsDefinition
keyWordArrayOfFloatingPointNumbersDefinition
keyWordArrayOfBooleansDefinition
*/
arr1 := ["hello1", "hello2"]
arr2 := [true, false]
arr3 := [3.13, 3.14]
arr4 := [1, 6, 2]
arr5 := ["real STR"]
; Array operations
HTVM_Append(arr1, "hello3")
sizeArr1 := HTVM_Size(arr1)
print("the size of arr1 is:")
print(sizeArr1)
HTVM_Insert(arr1, 1, "hello?????")
HTVM_Remove(arr1, 0)
idx1 := HTVM_IndexOf(arr1, "hello2")
print("the index of arr1 for hello2 is:")
print(idx1)
HTVM_Pop(arr1)
Loop, % HTVM_Size(arr1) {
    print(arr1[A_Index])
}
HTVM_Append(arr2, true)
sizeArr2 := HTVM_Size(arr2)
print("the size of arr2 is:")
print(sizeArr2)
HTVM_Insert(arr2, 1, false)
HTVM_Remove(arr2, 0)
idx2 := HTVM_IndexOf(arr2, true)
print("the index of arr2 for true is:")
print(idx2)
HTVM_Pop(arr2)
Loop, % HTVM_Size(arr2) {
    print(arr2[A_Index])
}
HTVM_Append(arr3, 6.489)
sizeArr3 := HTVM_Size(arr3)
print("the size of arr3 is:")
print(sizeArr3)
HTVM_Insert(arr3, 1, 1.556)
HTVM_Remove(arr3, 0)
idx3 := HTVM_IndexOf(arr3, 3.14)
print("the index of arr3 for 3.14 is:")
print(idx3)
HTVM_Pop(arr3)
Loop, % HTVM_Size(arr3) {
    print(arr3[A_Index])
}
HTVM_Append(arr4, 69)
sizeArr4 := HTVM_Size(arr4)
print("the size of arr4 is:")
print(sizeArr4)
HTVM_Insert(arr4, 1, 420)
HTVM_Remove(arr4, 0)
idx4 := HTVM_IndexOf(arr4, 69)
print("the index of arr4 for 69 is:")
print(idx4)
HTVM_Pop(arr4)
Loop, % HTVM_Size(arr4) {
    print(arr4[A_Index])
}
HTVM_Append(arr5, "hello3real")
sizeArr5 := HTVM_Size(arr5)
print("the size of arr5 is:")
print(sizeArr5)
HTVM_Insert(arr5, 1, "hello?real????")
HTVM_Remove(arr5, 0)
idx5 := HTVM_IndexOf(arr5, "hello3real")
print("the index of arr5 for hello3real is:")
print(idx5)
HTVM_Pop(arr5)
Loop, % HTVM_Size(arr5) {
    print(arr5[A_Index])
}
/*
keyWordThrow
keyWordErrorMsg
keyWordTry
keyWordCatch
keyWordFinally



*/
try {
    print("Trying...")
    throw "Something went wrong!"
}
catch e {
    print("Caught an error:")
    print(e)
}
finally {
    print("This always runs, success or error.")
}
print("==============================================")
