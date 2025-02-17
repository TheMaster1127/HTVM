

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


def func1(var1)
    return var1 + var1
end
def func2(var1)
    print(var1 + var1)
end
def func3(var1, var2 = "hello", var3 = "hello", var4 = "hello")
    print(var1 + " " + var2 + " " + var3 + " " + var4)
end
print(func1("hi1"))
func2("hi2")
func3("hi3")
func3("hi3", "hello3")
func3("hi3", "hello3", "QWAESDRTFG")
func3("hi3", "hello3", "QWAESDRTFG", "WAESDRFTG44444")
var1 = nil
myArr0 = []
HTVM_Append(myArr0, true)
HTVM_Append(myArr0, false)
HTVM_Append(myArr0, true)
myArr = [5, 6, 7]
for a_index1 in 0...5 + 0 do
    var1 = 6
    HTVM_Append(myArr, a_index1)
end
for a_index2 in 0...HTVM_Size(myArr) + 0 do
    print(myArr[a_index2])
end
for a_index3 in 0...HTVM_Size(myArr0) + 0 do
    print(myArr0[a_index3])
end
if (var1 == 6)
    print(var1)
elsif (var1 == 7)
    print(var1)
end
var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn"
items4 = LoopParseFunc(var123, "\n", "\r")
items4.each_with_index do |a_loopfield4 , a_index4|
    if (a_index4 == 0)
        print(a_index4)
    end
    print(a_loopfield4)
end
print("==================")
var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg"
items5 = LoopParseFunc(var1234, ",")
items5.each_with_index do |a_loopfield5 , a_index5|
    if (a_index5 == 0)
        print(a_index5)
    end
    print(a_loopfield5)
end
print("==================")
var12345 = "hello"
items6 = LoopParseFunc(var12345)
items6.each_with_index do |a_loopfield6 , a_index6|
    print(a_loopfield6)
end