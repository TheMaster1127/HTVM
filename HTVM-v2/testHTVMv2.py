import re

def LoopParseFunc(var, delimiter1="", delimiter2=""):
    if not delimiter1 and not delimiter2:
        # If no delimiters are provided, return a list of characters
        items = list(var)
    else:
        # Construct the regular expression pattern for splitting the string
        pattern = r'[' + re.escape(delimiter1) + re.escape(delimiter2) + r']+'
        # Split the string using the constructed pattern
        items = re.split(pattern, var)
    return items

# used the print func

def HTVM_Append(arr, value):
    arr.append(value)

def HTVM_Size(arr):
    return len(arr)


var1 = None
myArr0 = []
HTVM_Append(myArr0, True)
HTVM_Append(myArr0, False)
HTVM_Append(myArr0, True)
myArr = [5, 6, 7]
for A_Index1 in range(0, 5 + 0):
    var1 = 6
    HTVM_Append(myArr, A_Index1)
for A_Index2 in range(0, HTVM_Size(myArr) + 0):
    print(myArr[A_Index2])
for A_Index3 in range(0, HTVM_Size(myArr0) + 0):
    print(myArr0[A_Index3])
print(var1)
var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn"
items4 = LoopParseFunc(var123, "\n", "\r")
for A_Index4 , A_LoopField4 in enumerate(items4, start=0):
    if (A_Index4 == 0):
        print(A_Index4)
    print(A_LoopField4)
print("==================")
var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg"
items5 = LoopParseFunc(var1234, ",")
for A_Index5 , A_LoopField5 in enumerate(items5, start=0):
    if (A_Index5 == 0):
        print(A_Index5)
    print(A_LoopField5)
