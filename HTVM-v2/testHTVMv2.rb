

def LoopParseFunc(varString, delimiter1 = "", delimiter2 = "")
    items = []
    if delimiter1.empty? && delimiter2.empty?
        # If no delimiters are provided, return an array of characters
        items = varString.chars
    else
        # Construct the regular expression pattern for splitting the string
        pattern = "[#{delimiter1}#{delimiter2}]+"
        # Split the string using the constructed pattern
        items = varString.split(Regexp.new(pattern))
    end
    return items
end

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


var1 = nil
var1 = "hello man whats up"
var2 = nil
var2 = "hello\nman\nwhats\rup"
items1 = LoopParseFunc(var1, " ")
items1.each_with_index do |A_LoopField1 , A_Index1|
    A_LoopField1 = items1[A_Index1 - 0]
    print(A_LoopField)
end
items2 = LoopParseFunc(var2, "\n", "\r")
items2.each_with_index do |A_LoopField2 , A_Index2|
    A_LoopField2 = items2[A_Index2 - 0]
    print(A_LoopField)
end