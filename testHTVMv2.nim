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

proc HTVM_Append[T](arr: var seq[T], value: T) =
  arr.add(value)

proc HTVM_Size[T](arr: seq[T]): int =
  return arr.len


proc func1(var1: string): string =
    return var1 & var1
proc func2(var1: string) =
    print(var1 & var1)
proc func3(var1: string, var2: string = "hello") =
    print(var1 & " " & var2)
print(func1("hi1"))
func2("hi2")
func3("hi3")
func3("hi3", "hello3")
var var1: int = 0
var myArr0: seq[bool] = @[]
HTVM_Append(myArr0, true)
HTVM_Append(myArr0, false)
HTVM_Append(myArr0, true)
var myArr: seq[int] = @[5, 6, 7]
for A_IndexA1 in 0..<5 + 0:
    var1 = 6
    HTVM_Append(myArr, A_IndexA1)
for A_IndexA2 in 0..<HTVM_Size(myArr) + 0:
    print(myArr[A_IndexA2])
for A_IndexA3 in 0..<HTVM_Size(myArr0) + 0:
    print(myArr0[A_IndexA3])
if var1 == 6:
    print(var1)
elif var1 == 7:
    print(var1)
var var123: string = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn"
var items4 = LoopParseFunc(var123, "\n", "\r")
for A_IndexA4 , A_LoopFieldA4 in items4:
    if A_IndexA4 == 0:
        print(A_IndexA4)
    print(A_LoopFieldA4)
print("==================")
var var1234: string = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg"
var items5 = LoopParseFunc(var1234, ",")
for A_IndexA5 , A_LoopFieldA5 in items5:
    if A_IndexA5 == 0:
        print(A_IndexA5)
    print(A_LoopFieldA5)
print("==================")
var var12345: string = "hello"
var items6 = LoopParseFunc(var12345)
for A_IndexA6 , A_LoopFieldA6 in items6:
    print(A_LoopFieldA6)
