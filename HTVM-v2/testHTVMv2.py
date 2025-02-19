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


def func1(var1):
    return var1 + var1
def func2(var1):
    print(var1 + var1)
def func3(var1, var2 = "hello"):
    print(var1 + " " + var2)
print(func1("hi1"))
func2("hi2")
func3("hi3")
func3("hi3", "hello3")
var1 = None
myArr0 = []
HTVM_Append(myArr0, True)
HTVM_Append(myArr0, False)
HTVM_Append(myArr0, True)
myArr = [5, 6, 7]
for A_IndexA1 in range(0, 5 + 0):
    var1 = 6
    HTVM_Append(myArr, A_IndexA1)
for A_IndexA2 in range(0, HTVM_Size(myArr) + 0):
    print(myArr[A_IndexA2])
for A_IndexA3 in range(0, HTVM_Size(myArr0) + 0):
    print(myArr0[A_IndexA3])
if var1 == 6:
    print(var1)
elif var1 == 7:
    print(var1)
var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn";
items4 = LoopParseFunc(var123, "\n", "\r")
for A_IndexA4 , A_LoopFieldA4 in enumerate(items4, start=0):
    if A_IndexA4 == 0:
        print(A_IndexA4)
    print(A_LoopFieldA4)
print("==================")
var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg";
items5 = LoopParseFunc(var1234, ",")
for A_IndexA5 , A_LoopFieldA5 in enumerate(items5, start=0):
    if A_IndexA5 == 0:
        print(A_IndexA5)
    print(A_LoopFieldA5)
print("==================")
var12345 = "hello";
items6 = LoopParseFunc(var12345)
for A_IndexA6 , A_LoopFieldA6 in enumerate(items6, start=0):
    print(A_LoopFieldA6)
