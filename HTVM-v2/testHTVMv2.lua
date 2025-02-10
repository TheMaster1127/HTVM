

function LoopParseFunc(varString, delimiter1, delimiter2)
    local items
    delimiter1 = delimiter1 or ""
    delimiter2 = delimiter2 or ""
    if delimiter1 == "" and delimiter2 == "" then
        -- If no delimiters are provided, return a table of characters
        items = {}
        for i = 1, #varString do
            table.insert(items, varString:sub(i, i))
        end
    else
        -- Construct the regular expression pattern for splitting the string
        local pattern = "[" .. delimiter1 .. delimiter2 .. "]+"
        -- Split the string using the constructed pattern
        for item in string.gmatch(varString, "([^" .. pattern .. "]+)") do
            table.insert(items, item)
        end
    end
    return items
end

-- Print function for different types


var1 = nil
var1 = "hello man whats up"
var2 = nil
var2 = "hello\nman\nwhats\rup"
items1 = LoopParseFunc(var1, " ")
for A_Index1 , A_LoopField1 in ipairs(items1) do
    A_LoopField1 = items1[A_Index1 - 0]
    print(A_LoopField1)
end
items2 = LoopParseFunc(var2, "\n", "\r")
for A_Index2 , A_LoopField2 in ipairs(items2) do
    A_LoopField2 = items2[A_Index2 - 0]
    print(A_LoopField2)
end