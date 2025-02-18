

def LoopParseFunc(varString, delimiter1 = "", delimiter2 = "")
    items = []
    if delimiter1.empty? && delimiter2.empty?
        # If no delimiters are provided, return an array of characters
        items = varString.chars
    else
        # Construct the regular expression pattern for splitting the string
        pattern = "[#{delimiter1}#{delimiter2}]+"
        # Split the string using the constructed pattern
        items = varString.split(Regexp.new(pattern))
    end
    return items
end

# Print function for various types
def print(value)
  if value.is_a?(String)
    puts value
  elsif value.is_a?(Numeric)
    puts value.to_s
  elsif value.is_a?(TrueClass) || value.is_a?(FalseClass)
    puts value ? "true" : "false"
  else
    puts "Unsupported type"
  end
end

def HTVM_Append(arr, value)
  arr << value
end

def HTVM_Pop(arr)
  arr.pop
end

def HTVM_Size(arr)
  arr.size
end

def HTVM_Insert(arr, index, value)
  arr.insert(index, value)
end

def HTVM_Remove(arr, value)
  arr.delete(value)
end

def HTVM_IndexOf(arr, value)
  arr.index(value) || -1
end


# start
















def func0(input)
    puts input
end












def func1(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14)
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
def func2(var1)
    return var1
end
def func3(var1)
    return var1
end
def func4(var1)
    return var1
end
def func5(var1)
    return var1
end
def func6(var1)
    return var1
end
def func7(var1)
    return var1
end
def func8(var1)
    return var1
end
def func9(var1)
    return var1
end
def func10(var1)
    return var1
end
def func11(var1)
    return var1
end
def func12(var1)
    return var1
end
def func13(var1)
    return var1
end
def func14(var1)
    return var1
end
def func15(var1)
    return var1
end
=begin
this
is
a
multy
line
comment
=end
# outside vars
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
# start
















func0("Hello World")












print("==================================")
for a_index1 in 0...5 + 0 do
    if (a_index1 == 0)
        print(a_index1)
    elsif (a_index1 == 1)
        print(a_index1)
    elsif (a_index1 == 2)
        print(a_index1)
    elsif (a_index1 == 3)
        print(a_index1)
    elsif (a_index1 == 4)
        print(a_index1)
    elsif (a_index1 == 5)
        print(a_index1)
    else
        print("HOW????")
        print(a_index1)
    end
end
vars1 = false
vars2 = 0
while (vars1 == false)
    vars2 += 1
    print(vars2)
    if (vars2 == 6)
        vars1 = true
    end
end
for a_index2 in 0..someLimit do
    if (a_index2 == 6)
        break
    else
        next
    end
    # this is only for lua
    ::continue::
end
str1 = "hello 123 hello2"
items3 = LoopParseFunc(str1, " ")
items3.each_with_index do |a_loopfield3 , a_index3|
    print(a_loopfield3)
end
print("==================")
items4 = LoopParseFunc(str1)
items4.each_with_index do |a_loopfield4 , a_index4|
    print(a_loopfield4)
    if (a_loopfield4 == "2")
        break
    else
        next
    end
    ::continue::
end
=begin
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
=end
arr1 = ["hello1", "hello2"]
arr2 = [true, false]
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
for a_index5 in 0...HTVM_Size(arr1) + 0 do
    print(arr1[a_index5])
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
for a_index6 in 0...HTVM_Size(arr2) + 0 do
    print(arr2[a_index6])
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
for a_index7 in 0...HTVM_Size(arr3) + 0 do
    print(arr3[a_index7])
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
for a_index8 in 0...HTVM_Size(arr4) + 0 do
    print(arr4[a_index8])
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
for a_index9 in 0...HTVM_Size(arr5) + 0 do
    print(arr5[a_index9])
end
=begin
keyWordThrow
keyWordErrorMsg
keyWordTry
keyWordCatch
keyWordFinally
=end
begin
    print("Trying...")
    raise "Something went wrong!"
rescue => e
    print("Caught an error:")
    print(e.message)
ensure
    print("This always runs, success or error.")
end
print("==============================================")