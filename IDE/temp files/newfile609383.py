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

# Convert value to string
def STR(value):
    if isinstance(value, (int, float)):
        return str(value)
    elif isinstance(value, bool):
        return "1" if value else "0"
    elif isinstance(value, str):
        return value  # If the value is already a string, return it as-is
    else:
        raise TypeError("Unsupported type")


# This is a preview of your language and how it will look.
# Here's how types will appear if you only define them:
varName1 = None
varName2 = None
varName3 = None
varName4 = None
varName5 = None
varName6 = None
varName7 = None
varName8 = None
# Alternatively, you can define them like this:
varName9 = 34
# Here is how to define a function with static types if you convert to C++.
# However, it will still work even if you are not converting to C++; types will be stripped away.
def funcName1(paramVar1, paramVar2 = "", paramVar3 = False, paramVar4 = 1.5):
    # This is how the global keyword works if we convert to Python.
    # But even if we don't, it will just be removed, so you can add it if you want to convert to Python as well.
    global varName5
    # Here's how if, else if, and else statements will look:
    if (varName1 == paramVar1):
        print("varName1 is equal to paramVar1")
    elif (varName1 != paramVar1 or varName1 <= paramVar1):
        print("varName1 is less than or equal to paramVar1")
    else:
        print("varName1 is NOT less than or equal to paramVar1 or something else")
    # this is how the return keyword will look like in your lang
    return
funcName1(varName9)
# this is how a while loop works in your lang
var1 = False
while (var1 == False):
    print("we are inside the while loop")
    var1 = True
print("we are outside the while loop")
# this is how to use a for loop
indexMax = 5
# this is how to use a for loop normal
for indexName in range(0, indexMax):
    print("iteration: " + STR(indexName))
# this is how to use a for loop whit arrays
array = []
array.append("hello")
array.append("how")
array.append("are")
array.append("you")
array.append("doing")
for indexName in range(0, len(array)):
    print("iteration: " + STR(indexName))
    print("Item: " + array[indexName])
print("this is how the escape char looks like \nthis is a new line")
"""
this is a comment block
this is a comment block
"""
# this is how to use an AutoHotKey like Loop
for A_Index1 in range(0, 10 + 0):
    if (A_Index1 % 2 == 0):
        continue
    print(A_Index1)
# this is how to use an AutoHotKey like infinite Loop
for A_Index2 , value in enumerate(iter(int, 1), start=0):
    if (A_Index2 == 5):
        break
    else:
        print(A_Index2)
# this is how to use an AutoHotKey like Loop, parse
someText = "hello how are you doing\ntoday we are good."
items3 = LoopParseFunc(someText, " ", "\n")
for A_Index3 , A_LoopField3 in enumerate(items3, start=0):
    print(A_LoopField3)
# Error Handling
try:
    raise Exception("Something went wrong!")
except Exception as e:
    print(e)
finally:
    print("Finally block executed")