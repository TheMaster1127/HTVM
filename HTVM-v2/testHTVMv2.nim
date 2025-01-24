

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


# some comment
while (true):
    print("hi from HTVM v2 still in development")
    break
#[
WAESFD
WAQESR
FRAWE
DSFDSADSDF
asfdx
for A_Index1 in 0..5 + 0:
    print(A_Index1)
]#
