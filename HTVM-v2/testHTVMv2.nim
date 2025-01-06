

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


for A_Index1 in 0..5 + 0:
    print("hello HTVM v2")
    print("hello HTVM\nv2")
    print(A_Index1)
    for A_Index2 in 0..5 + 0:
        print("hello HTVM v2")
        print("hello HTVM\nv2")
        for A_Index3 in 0..5 + 0:
            print("hello HTVM v2")
            print("hello HTVM\nv2")
            print(A_Index3)
        print(A_Index2)
