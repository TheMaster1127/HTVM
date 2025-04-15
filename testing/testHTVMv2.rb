

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

def fstr(val)
  val.to_s
end


# === Regular F-String Example ===
$calculation = 10 + 5
$message = "The result is: " + fstr($calculation) + ". Double is: " + fstr($calculation * 2) + ""
print("Regular F-String:")
print($message)
print("=========================")
# === Multiline String (Raw) Example ===
$ascii_cat = " /\\_/\\\n( o.o )\n > ^ <"
print("Multiline String (Raw):")
print($ascii_cat)
print("=========================")
# === Multiline F-String Example ===
$userName = "Alice"
$items = 3
$price = 19.99
$order_summary = "Order Summary for: " + fstr($userName) + "\n\nItems purchased: " + fstr($items) + "\nTotal cost: $" + fstr($items * $price) + "\n\nThank you for your order!\nNewlines and indentation are preserved."
print("Multiline F-String:")
print($order_summary)
print("=========================")