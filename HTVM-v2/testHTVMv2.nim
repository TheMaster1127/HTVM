import strutils

proc LoopParseFunc(varString: string, delimiter1: string = "", delimiter2: string = ""): seq[string] =
  var items: seq[string] = @[]
  
  if delimiter1.len == 0 and delimiter2.len == 0:
    # If no delimiters are provided, return a sequence of characters
    for i in 0..<varString.len:
      items.add($varString[i])
  else:
    if delimiter2.len == 0:
      # If only one delimiter is provided, use simple split
      items = varString.split(delimiter1)
    else:
      # If both delimiters are provided, first split by delimiter1
      let tempItems = varString.split(delimiter1)
      # Then split each item by delimiter2 if needed
      for item in tempItems:
        let subItems = item.split(delimiter2)
        for subItem in subItems:
          if subItem.len > 0:  # Only add non-empty items
            items.add(subItem)
            
  return items

# Print function for various types
proc print(value: auto) =  # Use 'auto' instead of 'untyped'
  echo value

proc HTVM_Append[T](arr: var seq[T], value: T) =
  arr.add(value)

proc HTVM_Pop[T](arr: var seq[T]) =
  if arr.len > 0: arr.setLen(arr.len - 1)

proc HTVM_Size[T](arr: seq[T]): int =
  return arr.len

proc HTVM_Insert[T](arr: var seq[T], index: int, value: T) =
  if index >= 0 and index <= arr.len:
    arr.insert(value, index)  # Correct order

proc HTVM_Remove[T](arr: var seq[T], index: int) =
  if index >= 0 and index < arr.len:
    arr.delete(index)

proc HTVM_IndexOf[T](arr: seq[T], value: T): int =
  for i, v in arr:
    if v == value:
      return i
  return -1


# start


















proc func0(input: string) =
  echo input










proc func1(var1: float, var2: char, var3: uint8, var4: uint16, var5: uint32, var6: uint64, var7: int, var8: string, var9: bool, var10: float, var11: int8, var12: int16, var13: int32, var14: int64) =
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
proc func2(var1: float): float =
    return var1
proc func3(var1: char): char =
    return var1
proc func4(var1: uint8): uint8 =
    return var1
proc func5(var1: uint16): uint16 =
    return var1
proc func6(var1: uint32): uint32 =
    return var1
proc func7(var1: uint64): uint64 =
    return var1
proc func8(var1: int): int =
    return var1
proc func9(var1: string): string =
    return var1
proc func10(var1: bool): bool =
    return var1
proc func11(var1: float): float =
    return var1
proc func12(var1: int8): int8 =
    return var1
proc func13(var1: int16): int16 =
    return var1
proc func14(var1: int32): int32 =
    return var1
proc func15(var1: int64): int64 =
    return var1
#[
this
is
a
multy
line
comment
]#
# outside vars
var var01: float = 3.1234567891011
var var02: char = 'a'
var var03: uint8 = 25
var var04: uint16 = 30
var var05: uint32 = 35'u32
var var06: uint64 = 40'u64
var var07: int = 100
var var08: string = "hello var ouside"
var var09: bool = false
var var010: float = 3.14
var var011: int8 = 100
var var012: int16 = 200
var var013: int32 = 230
var var014: int64 = 80009
proc testFuncVars() =
    const constStrTest0: string = "constStrTest0"
    var constStrTest00: string = "constStrTest00"
    print(constStrTest0)
    var items1 = LoopParseFunc(constStrTest00)
    for A_Index1 , A_LoopField1 in items1:
        print(A_LoopField1)
const constStrTest: string = "constStrTest"
var letStrTest: string = "letStrTest";
var varStrTest: string = "varStrTest"
const constStrTest1: string = "constStrTest1"
var letStrTest1: string = "letStrTest1";
var varStrTest1: string = "varStrTest1"
print(letStrTest)
print(varStrTest)
print(letStrTest1)
print(varStrTest1)
var items2 = LoopParseFunc(constStrTest)
for A_Index2 , A_LoopField2 in items2:
    print(A_LoopField2)
print("==========================================")
print("==========================================")
print("==========================================")
var items3 = LoopParseFunc(constStrTest1)
for A_Index3 , A_LoopField3 in items3:
    print(A_LoopField3)
print("==========================================")
print("==========================================")
print("==========================================")
var var_1: float = 0.0
var var_2: char = 'a'
var var_3: uint8 = 0
var var_4: uint16 = 0
var var_5: uint32 = 0
var var_6: uint64 = 0
var var_7: int = 0
var var_8: string = ""
var var_9: bool = false
var var_10: float = 0.0
var var_11: int8 = 0
var var_12: int16 = 0
var var_13: int32 = 0
var var_14: int64 = 0
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
for A_Index4 in 0..<5 + 0:
    if (A_Index4 == 0):
        print(A_Index4)
    elif (A_Index4 == 1):
        print(A_Index4)
    elif (A_Index4 == 2):
        print(A_Index4)
    elif (A_Index4 == 3):
        print(A_Index4)
    elif (A_Index4 == 4):
        print(A_Index4)
    elif (A_Index4 == 5):
        print(A_Index4)
    else:
        print("HOW????")
        print(A_Index4)
var vars1: bool = false
var vars2: int = 0
while (vars1 == false):
    vars2 += 1
    print(vars2)
    if (vars2 == 6):
        vars1 = true
for A_Index5 in countup(0, high(int)):
    if (A_Index5 == 6):
        break
    else:
        continue
    # this is only for lua
var str1: string = "hello 123 hello2"
var items6 = LoopParseFunc(str1, " ")
for A_Index6 , A_LoopField6 in items6:
    print(A_LoopField6)
print("==================")
var items7 = LoopParseFunc(str1)
for A_Index7 , A_LoopField7 in items7:
    print(A_LoopField7)
    if (A_LoopField7 == "2"):
        break
    else:
        continue
#[
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
]#
var arr1: seq[string] = @["hello1", "hello2"]
var arr2: seq[bool] = @[true, false]
var arr3: seq[float64] = @[3.13, 3.14]
var arr4: seq[int] = @[1, 6, 2]
var arr5: seq[string] = @["real STR"]
# Array operations
HTVM_Append(arr1, "hello3")
var sizeArr1: int = HTVM_Size(arr1)
print("the size of arr1 is:")
print(sizeArr1)
HTVM_Insert(arr1, 1, "hello?????")
HTVM_Remove(arr1, 0)
var idx1: int = HTVM_IndexOf(arr1, "hello2")
print("the index of arr1 for hello2 is:")
print(idx1)
HTVM_Pop(arr1)
for A_Index8 in 0..<HTVM_Size(arr1) + 0:
    print(arr1[A_Index8])
HTVM_Append(arr2, true)
var sizeArr2: int = HTVM_Size(arr2)
print("the size of arr2 is:")
print(sizeArr2)
HTVM_Insert(arr2, 1, false)
HTVM_Remove(arr2, 0)
var idx2: int = HTVM_IndexOf(arr2, true)
print("the index of arr2 for true is:")
print(idx2)
HTVM_Pop(arr2)
for A_Index9 in 0..<HTVM_Size(arr2) + 0:
    print(arr2[A_Index9])
HTVM_Append(arr3, 6.489)
var sizeArr3: int = HTVM_Size(arr3)
print("the size of arr3 is:")
print(sizeArr3)
HTVM_Insert(arr3, 1, 1.556)
HTVM_Remove(arr3, 0)
var idx3: int = HTVM_IndexOf(arr3, 3.14)
print("the index of arr3 for 3.14 is:")
print(idx3)
HTVM_Pop(arr3)
for A_Index10 in 0..<HTVM_Size(arr3) + 0:
    print(arr3[A_Index10])
HTVM_Append(arr4, 69)
var sizeArr4: int = HTVM_Size(arr4)
print("the size of arr4 is:")
print(sizeArr4)
HTVM_Insert(arr4, 1, 420)
HTVM_Remove(arr4, 0)
var idx4: int = HTVM_IndexOf(arr4, 69)
print("the index of arr4 for 69 is:")
print(idx4)
HTVM_Pop(arr4)
for A_Index11 in 0..<HTVM_Size(arr4) + 0:
    print(arr4[A_Index11])
HTVM_Append(arr5, "hello3real")
var sizeArr5: int = HTVM_Size(arr5)
print("the size of arr5 is:")
print(sizeArr5)
HTVM_Insert(arr5, 1, "hello?real????")
HTVM_Remove(arr5, 0)
var idx5: int = HTVM_IndexOf(arr5, "hello3real")
print("the index of arr5 for hello3real is:")
print(idx5)
HTVM_Pop(arr5)
for A_Index12 in 0..<HTVM_Size(arr5) + 0:
    print(arr5[A_Index12])
#[
keyWordThrow
keyWordErrorMsg
keyWordTry
keyWordCatch
keyWordFinally
]#
try:
    print("Trying...")
    raise newException(ValueError, "Something went wrong!")
except ValueError as e:
    print("Caught an error:")
    print(e.msg)
finally:
    print("This always runs, success or error.")
print("==============================================")