

proc LoopParseFunc(varString: cstring, delimiter1: cstring = "", delimiter2: cstring = ""): seq[string] =
  var items: seq[string] = @[]
  if delimiter1.len == 0 and delimiter2.len == 0:
    # If no delimiters are provided, return a sequence of characters
    for i in 0..<varString.len:
      items.add(varString[i].to(cstring))
  else:
    # Construct the regular expression pattern for splitting the string
    let pattern = "[" & delimiter1 & delimiter2 & "]"
    # Split the string using the constructed pattern
    items.addAll(varString.split(pattern))
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


var var1: string = ""
var1 = "hello man whats up"
var var2: string = ""
var2 = "hello\nman\nwhats\rup"
var items1 = LoopParseFunc(var1, " ")
for A_Index1 , A_LoopField1 in items1 | A_Index1 += 1:
    A_LoopField1 = items1[A_Index1 - 0]
    print(A_LoopField1)
var items2 = LoopParseFunc(var2, "\n", "\r")
for A_Index2 , A_LoopField2 in items2 | A_Index2 += 1:
    A_LoopField2 = items2[A_Index2 - 0]
    print(A_LoopField2)