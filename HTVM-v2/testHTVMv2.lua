

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


var1 = nil
myArr0 = {}
HTVM_Append(myArr0, true)
HTVM_Append(myArr0, false)
HTVM_Append(myArr0, true)
myArr = {5, 6, 7}
for A_Index1 = 0, 5 + 0 do
    var1 = 6
    HTVM_Append(myArr, A_Index1)
end
for A_Index2 = 0, HTVM_Size(myArr) + 0 do
    print(myArr[A_Index2])
end
for A_Index3 = 0, HTVM_Size(myArr0) + 0 do
    print(myArr0[A_Index3])
end
print(var1)
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
