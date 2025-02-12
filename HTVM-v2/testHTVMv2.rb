

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

def HTVM_Size(arr)
  arr.size
end


var1 = nil
myArr0 = []
HTVM_Append(myArr0, true)
HTVM_Append(myArr0, false)
HTVM_Append(myArr0, true)
myArr = [5, 6, 7]
for A_Index1 in 0...5 + 0 do
    var1 = 6
    HTVM_Append(myArr, A_Index1)
end
for A_Index2 in 0...HTVM_Size(myArr) + 0 do
    print(myArr[A_Index2])
end
for A_Index3 in 0...HTVM_Size(myArr0) + 0 do
    print(myArr0[A_Index3])
end
print(var1)
var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn"
items4 = LoopParseFunc(var123, "\n", "\r")
items4.each_with_index do |A_LoopField4 , A_Index4|
    A_LoopField4 = items4[A_Index4 - 0]
    if (A_Index == 0)
        print(A_Index)
    end
    print(A_LoopField)
end
print("==================")
var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg"
items5 = LoopParseFunc(var1234, ",")
items5.each_with_index do |A_LoopField5 , A_Index5|
    A_LoopField5 = items5[A_Index5 - 0]
    if (A_Index == 0)
        print(A_Index)
    end
    print(A_LoopField)
end
