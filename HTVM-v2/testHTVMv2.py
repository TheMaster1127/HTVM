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


var1 = None
var1 = "hello man whats up"
var2 = None
var2 = "hello\nman\nwhats\rup"
items1 = LoopParseFunc(var1, " ")
for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
    print(A_LoopField1)
items2 = LoopParseFunc(var2, "\n", "\r")
for A_Index2 , A_LoopField2 in enumerate(items2, start=0):
    print(A_LoopField2)