

# Print function for various types
def print(value)
  if value.is_a?(String)
    puts value
  elsif value.is_a?(Numeric)
    puts value.to_s
  elsif value.is_a?(TrueClass) || value.is_a?(FalseClass)
    puts value ? "true" : "false"
  else
    puts "Unsupported type"
  end
end


if (5 == 5 && 6 - 6 == 0)
    print("MAAAAAAAAAAA<M<SJDIJSLDLS")
elseif (5 == 5 && 6 - 6 == 0)
    print("MAAAAAAAAAAA<M<SJDIJSLDLS")
else
    print(5+5)
end
begin
    raise "this is an ERROR HTVM v2"
rescue => ee
    print(ee.message)
ensure
    print("finally finally finally finally")
end
