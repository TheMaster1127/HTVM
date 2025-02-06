

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


proc szdfxc0(): string =
    return "hi"
proc szdfxc(var1: string = "hi") =
    print(var1)
    print("hi2 void")
proc szdfxc1(var0: int, var1: string = "hi", var2: string = "hi2") =
    print(var0)
    print(var1)
    print(var2)
    print("hi2 void")
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#[
waedsfdsaeds
aedsf
saedsfxawdsfdfsaw
fddf
sefdf
saersdsaersdgfd
]#
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
proc szdfxc2(var1: string = "hi", var2: string = "hi2") =
    print(var1)
    print(var2)
    print("hi2 void")




print(szdfxc0())
szdfxc()
szdfxc1(5)
szdfxc1(6, "hello")
var var1: float = 0.0
var var2: char = 'a'
var var3: uint8 = 0
var var4: uint16 = 0
var var5: uint32 = 0
var var6: uint64 = 0
var var7: int = 0
var var8: string = ""
var var9: bool = false
var var10: float = 0.0
var var11: int8 = 0
var var12: int16 = 0
var var13: int32 = 0
var var14: int64 = 0
let array1: seq[string] = @[]
let array2: seq[int] = @[]
let array3: seq[string] = @[]
let array4: seq[float64] = @[]
let array5: seq[bool] = @[]
szdfxc2()
szdfxc2("HI1")
szdfxc2("HI1", "HI2")
print("Hello, World!")
for A_Index1 in 0..5 + 0:
    print(A_Index1)