

def LoopParseFunc(String varString, String delimiter1 = "", String delimiter2 = "") {
    def items = []
    if (delimiter1 == "" && delimiter2 == "") {
        // If no delimiters are provided, return an array of characters
        items = varString.toList()
    } else {
        // Construct the regular expression pattern for splitting the string
        def pattern = "[${delimiter1}${delimiter2}]"
        // Split the string using the constructed pattern
        items = varString.split(pattern)
    }
    return items
}

// Print function
def print = { message ->
    System.out.print("$message\n")
}

def HTVM_Append(arr, value) {
    arr.add(value)
}

def HTVM_Size(arr) {
    return arr.size()
}


def func1(var1) {
    return var1 + var1;
}
def func2(var1) {
    print(var1 + var1)
}
def func3(var1, var2 = "hello", var3 = "hello", var4 = "hello") {
    print(var1 + " " + var2 + " " + var3 + " " + var4)
}
print(func1("hi1"))
func2("hi2")
func3("hi3")
func3("hi3", "hello3")
func3("hi3", "hello3", "QWAESDRTFG")
func3("hi3", "hello3", "QWAESDRTFG", "WAESDRFTG44444")
def var1
def myArr0 = []
HTVM_Append(myArr0, true)
HTVM_Append(myArr0, false)
HTVM_Append(myArr0, true)
def myArr = [5, 6, 7]
for (A_Index1 in 0..<5 + 0) {
    var1 = 6
    HTVM_Append(myArr, A_Index1)
}
for (A_Index2 in 0..<HTVM_Size(myArr) + 0) {
    print(myArr[A_Index2])
}
for (A_Index3 in 0..<HTVM_Size(myArr0) + 0) {
    print(myArr0[A_Index3])
}
if (var1 == 6) {
    print(var1)
}
else if (var1 == 7) {
    print(var1)
}
def var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn"
def items4 = LoopParseFunc(var123, "\n", "\r")
items4.eachWithIndex { A_LoopField4 , A_Index4 ->
if (A_Index4 == 0) {
    A_LoopField4 = items4[A_Index4 - 0]
    print(A_Index4)
}
print(A_LoopField4)
}
print("==================")
def var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg"
def items5 = LoopParseFunc(var1234, ",")
items5.eachWithIndex { A_LoopField5 , A_Index5 ->
if (A_Index5 == 0) {
A_LoopField5 = items5[A_Index5 - 0]
print(A_Index5)
}
print(A_LoopField5)
}
print("==================")
def var12345 = "hello"
def items6 = LoopParseFunc(var12345)
items6.eachWithIndex { A_LoopField6 , A_Index6 ->
print(A_LoopField6)
}