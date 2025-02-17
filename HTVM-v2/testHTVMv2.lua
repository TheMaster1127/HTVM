

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

function HTVM_Size(arr)
    return #arr
end


function func1(var1)
    return var1 .. var1
end
function func2(var1)
    print(var1 .. var1)
end
function func3(var1, var2, var3, var4)
    var2 = var2 or "hello"
    var3 = var3 or "hello"
    var4 = var4 or "hello"
    print(var1 .. " " .. var2 .. " " .. var3 .. " " .. var4)
end
print(func1("hi1"))
func2("hi2")
func3("hi3")
func3("hi3", "hello3")
func3("hi3", "hello3", "QWAESDRTFG")
func3("hi3", "hello3", "QWAESDRTFG", "WAESDRFTG44444")
var1 = nil
myArr0 = {}
HTVM_Append(myArr0, true)
HTVM_Append(myArr0, false)
HTVM_Append(myArr0, true)
myArr = {5, 6, 7}
for A_Index1 = 0 + 1 , 5 + 0 do
    var1 = 6
    HTVM_Append(myArr, A_Index1)
end
for A_Index2 = 0 + 1 , HTVM_Size(myArr) + 0 do
    print(myArr[A_Index2])
end
for A_Index3 = 0 + 1 , HTVM_Size(myArr0) + 0 do
    print(myArr0[A_Index3])
end
if (var1 == 6) then
    print(var1)
elseif (var1 == 7) then
    print(var1)
end
var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn"
items4 = LoopParseFunc(var123, "\n", "\r")
for A_Index4 , A_LoopField4 in ipairs(items4) do
    A_LoopField4 = items4[A_Index4 - 0]
    if (A_Index4 == 0) then
        print(A_Index4)
    end
    print(A_LoopField4)
end
print("==================")
var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg"
items5 = LoopParseFunc(var1234, ",")
for A_Index5 , A_LoopField5 in ipairs(items5) do
    A_LoopField5 = items5[A_Index5 - 0]
    if (A_Index5 == 0) then
        print(A_Index5)
    end
    print(A_LoopField5)
end
print("==================")
var12345 = "hello"
items6 = LoopParseFunc(var12345)
for A_Index6 , A_LoopField6 in ipairs(items6) do
    A_LoopField6 = items6[A_Index6 - 0]
    print(A_LoopField6)
end