

function infinite_HTVM_Lua_Loop_HTVM()
    local i = 0
    return function()
        i = i + 1
        return i
    end
end

function LoopParseFunc(varString, delimiter1, delimiter2)
    local items = {}
    delimiter1 = delimiter1 or ""
    delimiter2 = delimiter2 or ""
    
    -- Changed: Don't escape the delimiters since we want them literal
    -- Just use them directly in the pattern
    if delimiter1 == "" and delimiter2 == "" then
        for i = 1, #varString do
            table.insert(items, varString:sub(i, i))
        end
    else
        -- Changed: Simplified pattern to directly match \n and \r
        local pattern = delimiter1 .. delimiter2
        for item in varString:gmatch("([^" .. pattern .. "]+)") do
            table.insert(items, item)
        end
    end
    return items
end

-- Print function for different types

function HTVM_Append(arr, value)
    table.insert(arr, value)
end

function HTVM_Pop(arr)
    table.remove(arr)
end

function HTVM_Size(arr)
    return #arr
end

function HTVM_Insert(arr, index, value)
    table.insert(arr, index, value)
end

function HTVM_Remove(arr, index)
    if index >= 1 and index <= #arr then
        table.remove(arr, index)
    end
end

function HTVM_IndexOf(arr, value)
    for i, v in ipairs(arr) do
        if v == value then
            return i
        end
    end
    return -1
end


-- start








function func0(input)
    print(input)
end




















function func1(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14)
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
end
function func2(var1)
    return var1
end
function func3(var1)
    return var1
end
function func4(var1)
    return var1
end
function func5(var1)
    return var1
end
function func6(var1)
    return var1
end
function func7(var1)
    return var1
end
function func8(var1)
    return var1
end
function func9(var1)
    return var1
end
function func10(var1)
    return var1
end
function func11(var1)
    return var1
end
function func12(var1)
    return var1
end
function func13(var1)
    return var1
end
function func14(var1)
    return var1
end
function func15(var1)
    return var1
end
--[[
this
is
a
multy
line
comment
]]
-- outside vars
var01 = 3.1234567891011
var02 = 'a'
var03 = 25
var04 = 30
var05 = 35
var06 = 40
var07 = 100
var08 = "hello var ouside"
var09 = false
var010 = 3.14
var011 = 100
var012 = 200
var013 = 230
var014 = 80009
function testFuncVars()
    constStrTest0 = "constStrTest0"
    constStrTest00 = "constStrTest00"
    print(constStrTest0)
    items1 = LoopParseFunc(constStrTest00)
    for A_Index1 , A_LoopField1 in ipairs(items1) do
        A_LoopField1 = items1[A_Index1 - 0]
        print(A_LoopField1)
    end
end
constStrTest = "constStrTest"
local letStrTest = "letStrTest"
varStrTest = "varStrTest"
constStrTest1 = "constStrTest1"
local letStrTest1 = "letStrTest1"
varStrTest1 = "varStrTest1"
print(letStrTest)
print(varStrTest)
print(letStrTest1)
print(varStrTest1)
items2 = LoopParseFunc(constStrTest)
for A_Index2 , A_LoopField2 in ipairs(items2) do
    A_LoopField2 = items2[A_Index2 - 0]
    print(A_LoopField2)
end
print("==========================================")
print("==========================================")
print("==========================================")
items3 = LoopParseFunc(constStrTest1)
for A_Index3 , A_LoopField3 in ipairs(items3) do
    A_LoopField3 = items3[A_Index3 - 0]
    print(A_LoopField3)
end
print("==========================================")
print("==========================================")
print("==========================================")
var_1 = nil
var_2 = nil
var_3 = nil
var_4 = nil
var_5 = nil
var_6 = nil
var_7 = nil
var_8 = nil
var_9 = nil
var_10 = nil
var_11 = nil
var_12 = nil
var_13 = nil
var_14 = nil
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
-- start








func0("Hello World")




















print("==================================")
for A_Index4 = 0 + 1 , 5 + 0 do
    if (A_Index4 == 0) then
        print(A_Index4)
    elseif (A_Index4 == 1) then
        print(A_Index4)
    elseif (A_Index4 == 2) then
        print(A_Index4)
    elseif (A_Index4 == 3) then
        print(A_Index4)
    elseif (A_Index4 == 4) then
        print(A_Index4)
    elseif (A_Index4 == 5) then
        print(A_Index4)
    else
        print("HOW????")
        print(A_Index4)
    end
end
vars1 = false
vars2 = 0
while (vars1 == false) do
    vars2 = vars2 + 1
    print(vars2)
    if (vars2 == 6) then
        vars1 = true
    end
end
for A_Index5 in infinite_HTVM_Lua_Loop_HTVM() do
    if (A_Index5 == 6) then
        break
    else
        goto continue0
    end
    -- this is only for lua
    ::continue0::
end
str1 = "hello 123 hello2"
items6 = LoopParseFunc(str1, " ")
for A_Index6 , A_LoopField6 in ipairs(items6) do
    A_LoopField6 = items6[A_Index6 - 0]
    print(A_LoopField6)
end
print("==================")
items7 = LoopParseFunc(str1)
for A_Index7 , A_LoopField7 in ipairs(items7) do
    A_LoopField7 = items7[A_Index7 - 0]
    print(A_LoopField7)
    if (A_LoopField7 == "2") then
        break
    else
        goto continue1
    end
    ::continue1::
end
--[[
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
]]
arr1 = {"hello1", "hello2"}
arr2 = {true, false}
arr3 = {3.13, 3.14}
arr4 = {1, 6, 2}
arr5 = {"real STR"}
-- Array operations
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
for A_Index8 = 0 + 1 , HTVM_Size(arr1) + 0 do
    print(arr1[A_Index8])
end
HTVM_Append(arr2, true)
sizeArr2 = HTVM_Size(arr2)
print("the size of arr2 is:")
print(sizeArr2)
HTVM_Insert(arr2, 1, false)
HTVM_Remove(arr2, 0)
idx2 = HTVM_IndexOf(arr2, true)
print("the index of arr2 for true is:")
print(idx2)
HTVM_Pop(arr2)
for A_Index9 = 0 + 1 , HTVM_Size(arr2) + 0 do
    print(arr2[A_Index9])
end
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
for A_Index10 = 0 + 1 , HTVM_Size(arr3) + 0 do
    print(arr3[A_Index10])
end
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
for A_Index11 = 0 + 1 , HTVM_Size(arr4) + 0 do
    print(arr4[A_Index11])
end
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
for A_Index12 = 0 + 1 , HTVM_Size(arr5) + 0 do
    print(arr5[A_Index12])
end
--[[
keyWordThrow
keyWordErrorMsg
keyWordTry
keyWordCatch
keyWordFinally
]]
LUA DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK
    print("Trying...")
    LUA DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK
end
LUA DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK
    print("Caught an error:")
    print(e)
end
LUA DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK
    print("This always runs, success or error.")
end
print("==============================================")
