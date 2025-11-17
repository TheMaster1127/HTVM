

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

def STR(value)
  if value.is_a?(Integer) || value.is_a?(Float)
    return value.to_s
  elsif value.is_a?(TrueClass) || value.is_a?(FalseClass)
    return value ? "1" : "0"
  elsif value.is_a?(String)
    return value
  else
    return value.to_s
  end
end

def HTVM_Append(arr, value)
  arr << value
end

def HTVM_Size(arr)
  arr.size
end


# This is a preview of your language and how it will look.
# Here's how types will appear if you only define them:
$varName1 = nil
$varName2 = nil
$varName3 = nil
$varName4 = nil
$varName5 = nil
$varName6 = nil
$varName7 = nil
$varName8 = nil
# Alternatively, you can define them like this:
$varName9 = 34
# Here's how to define a function with static types when converting to statically typed languages like:
# TypeScript, C++, Go, C#, Java, Kotlin, Nim, Swift, and Dart.
# However, even if you're not targeting a statically typed language (e.g. JavaScript or Python),
# the types will be stripped away automatically and the function will still work as expected.
def funcName1(paramVar1, paramVar2 = "", paramVar3 = false, paramVar4 = 1.5)
    # This is how the global keyword works if we convert to Python and AutoHotKey.
    # But even if we don't, it will just be removed, so you can add it if you want to convert to Python and AutoHotKey as well.
    # Here's how if, else if, and else statements will look:
    if ($varName1 == paramVar1)
        print("varName1 is equal to paramVar1")
    elsif ($varName1 != paramVar1 || $varName1 <= paramVar1)
        print("varName1 is less than or equal to paramVar1")
    else
        print("varName1 is NOT less than or equal to paramVar1 or something else")
    end
    # this is how the return keyword will look like in your lang
    return
end
# This is where the main function will start. It's just a label, so don't worry.
funcName1($varName9)
# this is how a while loop works in your lang
$var1 = false
while ($var1 == false)
    print("we are inside the while loop")
    $var1 = true
end
print("we are outside the while loop")
# this is how to use a loop whit arrays
$array123 = ["hey"]
HTVM_Append($array123, "hello")
HTVM_Append($array123, "how")
HTVM_Append($array123, "are")
HTVM_Append($array123, "you")
HTVM_Append($array123, "doing")
for a_index1 in 0...HTVM_Size($array123) do
    print("iteration: " + STR(a_index1))
    print("Item: " + $array123[a_index1])
end
print("this is how the escape char looks like \nthis is a new line")
=begin
this is a comment block
this is a comment block
=end
# this is how to use an AutoHotKey like Loop
for a_index2 in 0...10 do
    if (a_index2 % 2 == 0)
        next
    end
    print(a_index2)
end
# this is how to use an AutoHotKey like infinite Loop
for a_index3 in 0..Float::INFINITY
    if (a_index3 == 5)
        break
    else
        print(a_index3)
    end
end
# this is how to use an AutoHotKey like Loop, parse
$someText = "hello how are you doing\ntoday we are good."
$items4 = LoopParseFunc($someText, " ", "\n")
$items4.each_with_index do |a_loopfield4 , a_index4|
    print(a_loopfield4)
end
# Error Handling
begin
    raise "Something went wrong!"
rescue => e
    print(e.message)
ensure
    print("Finally block executed")
end
