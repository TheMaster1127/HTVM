

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

def HTVM_Append(arr, value)
  arr << value
end

def HTVM_Size(arr)
  arr.size
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
print(5+5 != 5 !SZDS() + "A+-+--+ != ADSF" + "WSADFD" + "qwadsf" + adsf >= 3 <= qwerd > qwretr < wdsdf = 5 != 8)
print("QWADSDF" + "qawdsf" || var1 ! var4 + "ASDFX" + !ADSFD("Qwads" + "QASD" + "aszd" < 6) ? false : true || nil && false)
print(HTVM_Size(aszd) HTVM_Append(aszd, HTVM_Size(aszd)))
Avar123 = StringTrimRight(STRRAWSD, 1)
if(var1 == 5 && var2w3erf < 6)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
var1 = 1
print((var1 == 1) ? "hello" : "bye")
var1 = 0
print((var1 == 1) ? "hello" : "bye")