

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
function func3(var1, var2)
    var2 = var2 or "hello"
    print(var1 .. " " .. var2)
end
print(func1("hi1"))
func2("hi2")
func3("hi3")
func3("hi3", "hello3")
var1 = nil
myArr0 = {}
HTVM_Append(myArr0, true)
HTVM_Append(myArr0, false)
HTVM_Append(myArr0, true)
myArr = {5, 6, 7}
for A_IndexA1 = 0 + 1 , 5 + 0 do
    var1 = 6
    HTVM_Append(myArr, A_IndexA1)
end
for A_IndexA2 = 0 + 1 , HTVM_Size(myArr) + 0 do
    print(myArr[A_IndexA2])
end
for A_IndexA3 = 0 + 1 , HTVM_Size(myArr0) + 0 do
    print(myArr0[A_IndexA3])
end
if var1 == 6 then
    print(var1)
elseif var1 == 7 then
    print(var1)
end
var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn"
items4 = LoopParseFunc(var123, "\n", "\r")
for A_IndexA4 , A_LoopFieldA4 in ipairs(items4) do
    A_LoopFieldA4 = items4[A_IndexA4 - 0]
    if A_IndexA4 == 0 then
        print(A_IndexA4)
    end
    print(A_LoopFieldA4)
end
print("==================")
var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg"
items5 = LoopParseFunc(var1234, ",")
for A_IndexA5 , A_LoopFieldA5 in ipairs(items5) do
    A_LoopFieldA5 = items5[A_IndexA5 - 0]
    if A_IndexA5 == 0 then
        print(A_IndexA5)
    end
    print(A_LoopFieldA5)
end
print("==================")
var12345 = "hello"
items6 = LoopParseFunc(var12345)
for A_IndexA6 , A_LoopFieldA6 in ipairs(items6) do
    A_LoopFieldA6 = items6[A_IndexA6 - 0]
    print(A_LoopFieldA6)
end