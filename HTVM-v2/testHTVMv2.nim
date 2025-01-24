

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


for A_Index1 in 0..20 + 0:
    print("hello HTVM import")
    print("hello HTVM\nimport")
for A_Index2 in 0..6 + 0:
    print("hello HTVM import")
    print("hello HTVM\nimport")
for A_Index3 in 0..5 + 0:
    print("hello\" HTVM v2")
    print("hello HTVM\\v2\\\\s")
    print("hello HTVM\nv2")
    print("hello HTVM\\nv2")
    print(A_Index3)
    for A_Index4 in 0..5 + 0:
        print("hello HTVM v2")
        print("hello HTVM\nv2")
        for A_Index5 in 0..5 + 0:
            print("hello HTVM v2")
            print("hello HTVM\nv2")
            print(A_Index5)
        print(A_Index4)
qWAERSFD()
qWAERSFD(waedsfd())
print(5+5 != 5 not SZDS() and "A+-+--+ != ADSF" and "WSADFD" and "qwadsf" + adsf >= 3 <= qwerd > qwretr < wdsdf == 5 != 8)
print(if "QWADSDF" and "qawdsf" || var1 ! var4 and "ASDFX" and not ADSFD("Qwads" and "QASD" and "aszd" < 6): false else: true || nil && false)
print(HTVM_Size(aszd) HTVM_Append(aszd, HTVM_Size(aszd)))
Avar123 = StringTrimRight(STRRAWSD, 1)
if(var1 == 5 and var2w3erf < 6)
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
var1 = 1
print(if (var1 == 1): "hello" else: "bye")
var1 = 0
print(if (var1 == 1): "hello" else: "bye")
if (5 == 5 and 6 - 6 == 0):
    print("MAAAAAAAAAAA<M<SJDIJSLDLS")
elif (5 == 5 and 6 - 6 == 0):
    print("MAAAAAAAAAAA<M<SJDIJSLDLS")
elif (5 == 5 and 6 - 6 == 0):
    print("MAAAAAAAAAAA<M<SJDIJSLDLS")
elif (5 == 5 and 6 - 6 == 0):
    print("MAAAAAAAAAAA<M<SJDIJSLDLS")
elif (5 == 5 and 6 - 6 == 0):
    print("MAAAAAAAAAAA<M<SJDIJSLDLS")
elif (5 == 5 and 6 - 6 == 0):
    print("MAAAAAAAAAAA<M<SJDIJSLDLS")
else:
    print(5+5)
print("==========")
print("==========")
print("==========")
print("==========")
print("==========")
print("==========")
try:
    raise newException(ValueError, "this is an ERROR HTVM v2")
except ValueError as ee:
    print(ee.msg)
finally:
    print("finally finally finally finally")
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
for A_Index6 in 0..5 + 0:
    print(A_Index6)
]#