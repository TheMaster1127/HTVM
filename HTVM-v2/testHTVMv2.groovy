

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


def var1
var1 = "hello man whats up"
def var2
var2 = "hello\nman\nwhats\rup"
def items1 = LoopParseFunc(var1, " ")
items1.eachWithIndex { A_LoopField1 , A_Index1 ->
print(A_LoopField1)
}
def items2 = LoopParseFunc(var2, "\n", "\r")
items2.eachWithIndex { A_LoopField2 , A_Index2 ->
print(A_LoopField2)
}