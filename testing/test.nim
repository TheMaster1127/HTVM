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

proc STR(value: auto): string =
  when value is int | int64 | float | float64:
    return $value
  elif value is bool:
    return if value: "1" else: "0"
  elif value is cstring:
    return $value
  else:
    return $value

proc HTVM_Append[T](arr: var seq[T], value: T) =
  arr.add(value)

proc HTVM_Size[T](arr: seq[T]): int =
  return arr.len


# This is a preview of your language and how it will look.
# Here's how types will appear if you only define them:
var varName1: int = 0
var varName2: string = ""
var varName3: bool = false
var varName4: float = 0.0
var varName5: int8 = 0
var varName6: int16 = 0
var varName7: int32 = 0
var varName8: int64 = 0
# Alternatively, you can define them like this:
var varName9: int = 34
# Here's how to define a function with static types when converting to statically typed languages like:
# TypeScript, C++, Go, C#, Java, Kotlin, Nim, Swift, and Dart.
# However, even if you're not targeting a statically typed language (e.g. JavaScript or Python),
# the types will be stripped away automatically and the function will still work as expected.
proc funcName1(paramVar1: int, paramVar2: string = "", paramVar3: bool = false, paramVar4: float = 1.5) =
    # This is how the global keyword works if we convert to Python and AutoHotKey.
    # But even if we don't, it will just be removed, so you can add it if you want to convert to Python and AutoHotKey as well.
    # Here's how if, else if, and else statements will look:
    if (varName1 == paramVar1):
        print("varName1 is equal to paramVar1")
    elif (varName1 != paramVar1 or varName1 <= paramVar1):
        print("varName1 is less than or equal to paramVar1")
    else:
        print("varName1 is NOT less than or equal to paramVar1 or something else")
    # this is how the return keyword will look like in your lang
    return
# This is where the main function will start. It's just a label, so don't worry.
funcName1(varName9)
# this is how a while loop works in your lang
var var1: bool = false
while (var1 == false):
    print("we are inside the while loop")
    var1 = true
print("we are outside the while loop")
# this is how to use a loop whit arrays
var array123: seq[string] = @["hey"]
HTVM_Append(array123, "hello")
HTVM_Append(array123, "how")
HTVM_Append(array123, "are")
HTVM_Append(array123, "you")
HTVM_Append(array123, "doing")
for A_Index1 in 0..<HTVM_Size(array123):
    print("iteration: " & STR(A_Index1))
    print("Item: " & array123[A_Index1])
print("this is how the escape char looks like \nthis is a new line")
#[
this is a comment block
this is a comment block
]#
# this is how to use an AutoHotKey like Loop
for A_Index2 in 0..<10:
    if (A_Index2 mod 2 == 0):
        continue
    print(A_Index2)
# this is how to use an AutoHotKey like infinite Loop
for A_Index3 in countup(0, high(int)):
    if (A_Index3 == 5):
        break
    else:
        print(A_Index3)
# this is how to use an AutoHotKey like Loop, parse
var someText: string = "hello how are you doing\ntoday we are good."
var items4 = LoopParseFunc(someText, " ", "\n")
for A_Index4 , A_LoopField4 in items4:
    print(A_LoopField4)
# Error Handling
try:
    raise newException(ValueError, "Something went wrong!")
except ValueError as e:
    print(e.msg)
finally:
    print("Finally block executed")
