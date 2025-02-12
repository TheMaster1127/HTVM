import strutils

proc LoopParseFunc(varString: cstring, delimiter1: cstring = "", delimiter2: cstring = ""): seq[string] =
  var items: seq[string] = @[]
  if delimiter1.len == 0 and delimiter2.len == 0:
    # If no delimiters are provided, return a sequence of characters
    for i in 0..<varString.len:
      items.add($varString[i])  # Use $ to convert char to string
  else:
    # Convert cstring to string directly
    let delim1Str = $delimiter1
    let delim2Str = $delimiter2
    # Construct the regular expression pattern for splitting the string
    let pattern = "[" & delim1Str & delim2Str & "]"
    # Split the string and add each item individually
    for item in ($varString).split(pattern):
      items.add(item)
  return items

# Print function for various types
proc print(value: auto) =  # Use 'auto' instead of 'untyped'
  # Nim uses when/elif for type checking, not case
  when value is string:
    echo value
  elif value is int or value is float:
    echo $value  # Use $ for string conversion in Nim
  elif value is bool:
    echo if value: "true" else: "false"
  else:
    echo "Unsupported type"

proc HTVM_Append[T](arr: var seq[T], value: T) =
  arr.add(value)

proc HTVM_Size[T](arr: seq[T]): int =
  return arr.len


var var1: int = 0
var myArr0: seq[bool] = @[]
HTVM_Append(myArr0, true)
HTVM_Append(myArr0, false)
HTVM_Append(myArr0, true)
var myArr: seq[int] = @[5, 6, 7]
for A_Index1 in 0..<5 + 0:
    var1 = 6
    HTVM_Append(myArr, A_Index1)
for A_Index2 in 0..<HTVM_Size(myArr) + 0:
    print(myArr[A_Index2])
for A_Index3 in 0..<HTVM_Size(myArr0) + 0:
    print(myArr0[A_Index3])
print(var1)
var var123: string = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn"
var items4 = LoopParseFunc(var123, "\n", "\r")
for A_Index4 , A_LoopField4 in items4:
    if (A_Index4 == 0):
        print(A_Index4)
    print(A_LoopField4)
print("==================")
var var1234: string = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg"
var items5 = LoopParseFunc(var1234, ",")
for A_Index5 , A_LoopField5 in items5:
    if (A_Index5 == 0):
        print(A_Index5)
    print(A_LoopField5)
