

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


def szdfxc0()
    return "hi"
end
def szdfxc()
    print("hi2 void")
end
print(szdfxc0())
szdfxc()
print("Hello, World!")
for A_Index1 in 0..5 + 0 do
    print(A_Index1)
end
