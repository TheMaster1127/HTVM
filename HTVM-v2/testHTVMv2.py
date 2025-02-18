import re

def LoopParseFunc(var, delimiter1="", delimiter2=""):
    if not delimiter1 and not delimiter2:
        # If no delimiters are provided, return a list of characters
        items = list(var)
    else:
        # Construct the regular expression pattern for splitting the string
        pattern = r'[' + re.escape(delimiter1) + re.escape(delimiter2) + r']+'
        # Split the string using the constructed pattern
        items = re.split(pattern, var)
    return items

# used the print func

# used imput func

def HTVM_Append(arr, value):
    arr.append(value)

def HTVM_Pop(arr):
    if arr:
        arr.pop()

def HTVM_Size(arr):
    return len(arr)

def HTVM_Insert(arr, index, value):
    arr.insert(index, value)

def HTVM_Remove(arr, value):
    if value in arr:
        arr.remove(value)

def HTVM_IndexOf(arr, value):
    return arr.index(value) if value in arr else -1


# start


def func0(input: str):
    print(input)


























def func1(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14):
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
def func2(var1):
    return var1
def func3(var1):
    return var1
def func4(var1):
    return var1
def func5(var1):
    return var1
def func6(var1):
    return var1
def func7(var1):
    return var1
def func8(var1):
    return var1
def func9(var1):
    return var1
def func10(var1):
    return var1
def func11(var1):
    return var1
def func12(var1):
    return var1
def func13(var1):
    return var1
def func14(var1):
    return var1
def func15(var1):
    return var1
"""
this
is
a
multy
line
comment
"""
# outside vars
var01 = 3.1234567891011
var02 = 'a'
var03 = 25
var04 = 30
var05 = 35
var06 = 40
var07 = 100
var08 = "hello var ouside"
var09 = False
var010 = 3.14
var011 = 100
var012 = 200
var013 = 230
var014 = 80009
var_1 = None
var_2 = None
var_3 = None
var_4 = None
var_5 = None
var_6 = None
var_7 = None
var_8 = None
var_9 = None
var_10 = None
var_11 = None
var_12 = None
var_13 = None
var_14 = None
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
# start


func0("Hello World")


























print("==================================")
for A_Index1 in range(0, 5 + 0):
    if (A_Index1 == 0):
        print(A_Index1)
    elif (A_Index1 == 1):
        print(A_Index1)
    elif (A_Index1 == 2):
        print(A_Index1)
    elif (A_Index1 == 3):
        print(A_Index1)
    elif (A_Index1 == 4):
        print(A_Index1)
    elif (A_Index1 == 5):
        print(A_Index1)
    else:
        print("HOW????")
        print(A_Index1)
vars1 = False
vars2 = 0
while (vars1 == False):
    vars2 += 1
    print(vars2)
    if (vars2 == 6):
        vars1 = True
for A_Index2 , value in enumerate(iter(int, 1), start=0):
    if (A_Index2 == 6):
        break
    else:
        continue
    # this is only for lua
    ::continue::
str1 = "hello 123 hello2"
items3 = LoopParseFunc(str1, " ")
for A_Index3 , A_LoopField3 in enumerate(items3, start=0):
    print(A_LoopField3)
print("==================")
items4 = LoopParseFunc(str1)
for A_Index4 , A_LoopField4 in enumerate(items4, start=0):
    print(A_LoopField4)
    if (A_LoopField4 == "2"):
        break
    else:
        continue
    ::continue::
"""
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
"""
arr1 = ["hello1", "hello2"]
arr2 = [True, False]
arr3 = [3.13, 3.14]
arr4 = [1, 6, 2]
arr5 = ["real STR"]
# Array operations
HTVM_Append(arr1, "hello3")
sizeArr1 = HTVM_Size(arr1)
print("the size of arr1 is:")
print(sizeArr1)
HTVM_Insert(arr1, 1, "hello?????")
HTVM_Remove(arr1, 0)
idx1 = HTVM_IndexOf(arr1, "hello2")
print("the index of arr1 for hello2 is:")
print(idx1)
HTVM_Pop(arr1)
for A_Index5 in range(0, HTVM_Size(arr1) + 0):
    print(arr1[A_Index5])
HTVM_Append(arr2, True)
sizeArr2 = HTVM_Size(arr2)
print("the size of arr2 is:")
print(sizeArr2)
HTVM_Insert(arr2, 1, False)
HTVM_Remove(arr2, 0)
idx2 = HTVM_IndexOf(arr2, True)
print("the index of arr2 for true is:")
print(idx2)
HTVM_Pop(arr2)
for A_Index6 in range(0, HTVM_Size(arr2) + 0):
    print(arr2[A_Index6])
HTVM_Append(arr3, 6.489)
sizeArr3 = HTVM_Size(arr3)
print("the size of arr3 is:")
print(sizeArr3)
HTVM_Insert(arr3, 1, 1.556)
HTVM_Remove(arr3, 0)
idx3 = HTVM_IndexOf(arr3, 3.14)
print("the index of arr3 for 3.14 is:")
print(idx3)
HTVM_Pop(arr3)
for A_Index7 in range(0, HTVM_Size(arr3) + 0):
    print(arr3[A_Index7])
HTVM_Append(arr4, 69)
sizeArr4 = HTVM_Size(arr4)
print("the size of arr4 is:")
print(sizeArr4)
HTVM_Insert(arr4, 1, 420)
HTVM_Remove(arr4, 0)
idx4 = HTVM_IndexOf(arr4, 69)
print("the index of arr4 for 69 is:")
print(idx4)
HTVM_Pop(arr4)
for A_Index8 in range(0, HTVM_Size(arr4) + 0):
    print(arr4[A_Index8])
HTVM_Append(arr5, "hello3real")
sizeArr5 = HTVM_Size(arr5)
print("the size of arr5 is:")
print(sizeArr5)
HTVM_Insert(arr5, 1, "hello?real????")
HTVM_Remove(arr5, 0)
idx5 = HTVM_IndexOf(arr5, "hello3real")
print("the index of arr5 for hello3real is:")
print(idx5)
HTVM_Pop(arr5)
for A_Index9 in range(0, HTVM_Size(arr5) + 0):
    print(arr5[A_Index9])
"""
keyWordThrow
keyWordErrorMsg
keyWordTry
keyWordCatch
keyWordFinally
"""
try:
    print("Trying...")
    raise Exception("Something went wrong!")
except Exception as e:
    print("Caught an error:")
    print(e)
finally:
    print("This always runs, success or error.")
print("==============================================")