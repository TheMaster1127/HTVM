

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

def HTVM_Size(arr)
  arr.size
end


arr123 = [1, 3, 5]
for a_index1 in 0...HTVM_Size(arr123) + 0 do
    print(arr123[a_index1])
end

