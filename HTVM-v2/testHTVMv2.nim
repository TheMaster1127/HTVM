

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
print(szdfxc0())
szdfxc()
szdfxc1(5)
szdfxc1(6, "hello")
print("Hello, World!")
for A_Index1 in 0..5 + 0:
    print(A_Index1)