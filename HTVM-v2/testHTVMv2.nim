

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
proc szdfxc() =
    print("hi2 void")
print(szdfxc0())
szdfxc()
print("Hello, World!")
for A_Index1 in 0..5 + 0:
    print(A_Index1)