

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
def szdfxc(var1 = "hi")
    print(var1)
    print("hi2 void")
end
def szdfxc1(var0, var1 = "hi", var2 = "hi2")
    print(var0)
    print(var1)
    print(var2)
    print("hi2 void")
end
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
=begin
waedsfdsaeds
aedsf
saedsfxawdsfdfsaw
fddf
sefdf
saersdsaersdgfd
=end
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
def szdfxc2(var1 = "hi", var2 = "hi2")
    print(var1)
    print(var2)
    print("hi2 void")
end
print(szdfxc0())
szdfxc()
szdfxc1(5)
szdfxc1(6, "hello")
szdfxc2()
szdfxc2("HI1")
szdfxc2("HI1", "HI2")
print("Hello, World!")
for A_Index1 in 0..5 + 0 do
    print(A_Index1)
end