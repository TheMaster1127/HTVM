

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