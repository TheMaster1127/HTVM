

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


for A_Index1 in 0..5 + 0 do
    print("hello HTVM v2")
    print("hello HTVM\nv2")
    print(A_Index1)
    for A_Index2 in 0..5 + 0 do
        print("hello HTVM v2")
        print("hello HTVM\nv2")
        for A_Index3 in 0..5 + 0 do
            print("hello HTVM v2")
            print("hello HTVM\nv2")
            print(A_Index3)
        end
        print(A_Index2)
    end
end



