

def LoopParseFunc(String varString, String delimiter1 = "", String delimiter2 = "") {
    def items = []
    if (delimiter1 == "" && delimiter2 == "") {
        // If no delimiters are provided, return an array of characters
        items = varString.toList()
    } else {
        // Construct the regular expression pattern for splitting the string
        def pattern = "[${delimiter1}${delimiter2}]"
        // Split the string using the constructed pattern
        items = varString.split(pattern)
    }
    return items
}

// Print function
def print = { message ->
    System.out.print("$message\n\r")
}

def HTVM_Append(arr, value) {
    arr.add(value)
}

def HTVM_Pop(arr) {
    if (!arr.isEmpty()) arr.remove(arr.size() - 1)
}

def HTVM_Size(arr) {
    return arr.size()
}

def HTVM_Insert(arr, index, value) {
    arr.add(index, value)
}

def HTVM_Remove(arr, value) {
    arr.remove(value)
}

def HTVM_IndexOf(arr, value) {
    return arr.indexOf(value)
}


// start




























def func0(input) {
    println(input)
}
def func1(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14) {
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
def func2(var1) {
    return var1;
}
def func3(var1) {
    return var1;
}
def func4(var1) {
    return var1;
}
def func5(var1) {
    return var1;
}
def func6(var1) {
    return var1;
}
def func7(var1) {
    return var1;
}
def func8(var1) {
    return var1;
}
def func9(var1) {
    return var1;
}
def func10(var1) {
    return var1;
}
def func11(var1) {
    return var1;
}
def func12(var1) {
    return var1;
}
def func13(var1) {
    return var1;
}
def func14(var1) {
    return var1;
}
def func15(var1) {
    return var1;
}
/*
this
is
a
multy
line
comment
*/
// outside vars
def var01 = 3.1234567891011
def var02 = 'a'
def var03 = 25
def var04 = 30
def var05 = 35
def var06 = 40
def var07 = 100
def var08 = "hello var ouside"
def var09 = false
def var010 = 3.14
def var011 = 100
def var012 = 200
def var013 = 230
def var014 = 80009
def var_1
def var_2
def var_3
def var_4
def var_5
def var_6
def var_7
def var_8
def var_9
def var_10
def var_11
def var_12
def var_13
def var_14
func1(var01, var02, var03, var04, var05, var06, var07, var08, var09, var010, var011, var012, var013, var014)
var_1 = func2(var01)
var_2 = func3(var02)
var_3 = func4(var03)
var_4 = func5(var04)
var_5 = func6(var05)
var_6 = func7(var06)
var_7 = func8(var07)
var_8 = func9(var08)
var_9 = func10(var09)
var_10 = func11(var010)
var_11 = func12(var011)
var_12 = func13(var012)
var_13 = func14(var013)
var_14 = func15(var014)
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
// start




























func0("Hello World");
print("==================================")
for (A_Index1 in 0..<5 + 0) {
    if (A_Index1 == 0) {
        print(A_Index1)
    }
    else if (A_Index1 == 1) {
        print(A_Index1)
    }
    else if (A_Index1 == 2) {
        print(A_Index1)
    }
    else if (A_Index1 == 3) {
        print(A_Index1)
    }
    else if (A_Index1 == 4) {
        print(A_Index1)
    }
    else if (A_Index1 == 5) {
        print(A_Index1)
    } else {
        print("HOW????")
        print(A_Index1)
    }
}
def vars1 = false
def vars2 = 0
while (vars1 == false) {
    vars2++;
    print(vars2)
    if (vars2 == 6) {
        vars1 = true
    }
}
for (A_Index2 in 0..someLimit) {
    if (A_Index2 == 6) {
        break;
    } else {
        continue;
    }
    // this is only for lua
    ::continue::
}
def str1 = "hello 123 hello2"
def items3 = LoopParseFunc(str1, " ")
items3.eachWithIndex { A_LoopField3 , A_Index3 ->
print(A_LoopField3)
}
print("==================")
def items4 = LoopParseFunc(str1)
items4.eachWithIndex { A_LoopField4 , A_Index4 ->
print(A_LoopField4)
if (A_LoopField4 == "2") {
A_LoopField4 = items4[A_Index4 - 0]
break;
} else {
continue;
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
def arr1 = ["hello1", "hello2"]
def arr2 = [true, false]
def arr3 = [3.13, 3.14]
def arr4 = [1, 6, 2]
def arr5 = ["real STR"]
// Array operations
HTVM_Append(arr1, "hello3")
def sizeArr1 = HTVM_Size(arr1)
print("the size of arr1 is:")
print(sizeArr1)
HTVM_Insert(arr1, 1, "hello?????")
HTVM_Remove(arr1, 0)
def idx1 = HTVM_IndexOf(arr1, "hello2")
print("the index of arr1 for hello2 is:")
print(idx1)
HTVM_Pop(arr1)
for (A_Index5 in 0..<HTVM_Size(arr1) + 0) {
print(arr1[A_Index5])
}
HTVM_Append(arr2, true)
def sizeArr2 = HTVM_Size(arr2)
print("the size of arr2 is:")
print(sizeArr2)
HTVM_Insert(arr2, 1, false)
HTVM_Remove(arr2, 0)
def idx2 = HTVM_IndexOf(arr2, true)
print("the index of arr2 for true is:")
print(idx2)
HTVM_Pop(arr2)
for (A_Index6 in 0..<HTVM_Size(arr2) + 0) {
print(arr2[A_Index6])
}
HTVM_Append(arr3, 6.489)
def sizeArr3 = HTVM_Size(arr3)
print("the size of arr3 is:")
print(sizeArr3)
HTVM_Insert(arr3, 1, 1.556)
HTVM_Remove(arr3, 0)
def idx3 = HTVM_IndexOf(arr3, 3.14)
print("the index of arr3 for 3.14 is:")
print(idx3)
HTVM_Pop(arr3)
for (A_Index7 in 0..<HTVM_Size(arr3) + 0) {
print(arr3[A_Index7])
}
HTVM_Append(arr4, 69)
def sizeArr4 = HTVM_Size(arr4)
print("the size of arr4 is:")
print(sizeArr4)
HTVM_Insert(arr4, 1, 420)
HTVM_Remove(arr4, 0)
def idx4 = HTVM_IndexOf(arr4, 69)
print("the index of arr4 for 69 is:")
print(idx4)
HTVM_Pop(arr4)
for (A_Index8 in 0..<HTVM_Size(arr4) + 0) {
print(arr4[A_Index8])
}
HTVM_Append(arr5, "hello3real")
def sizeArr5 = HTVM_Size(arr5)
print("the size of arr5 is:")
print(sizeArr5)
HTVM_Insert(arr5, 1, "hello?real????")
HTVM_Remove(arr5, 0)
def idx5 = HTVM_IndexOf(arr5, "hello3real")
print("the index of arr5 for hello3real is:")
print(idx5)
HTVM_Pop(arr5)
for (A_Index9 in 0..<HTVM_Size(arr5) + 0) {
print(arr5[A_Index9])
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
throw new Exception("Something went wrong!")
}
catch (Exception e) {
print("Caught an error:")
print(e.message)
}
finally {
print("This always runs, success or error.")
}
print("==============================================")