

# Print function for various types
proc print(value: auto) =  # Use 'auto' instead of 'untyped'
  echo value

proc HTVM_Size[T](arr: seq[T]): int =
  return arr.len


var arr123: seq[int] = @[1, 3, 5]
for A_Index1 in 0..<HTVM_Size(arr123) + 0:
    print(arr123[A_Index1])

