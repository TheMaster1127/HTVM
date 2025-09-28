

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

# used imput func

def Chr(number: int) -> str:
    # Return the character corresponding to the Unicode code point, or an empty string if out of range
    return chr(number) if 0 <= number <= 0x10FFFF else ""


input("(PRESS ENTER TO CONTINUE) - Breakpoint: 1" + Chr(10) + "============================================" + Chr(10) + "NO VARIABLES!!!" + Chr(10))
globalIntVartest123 = 425
input("(PRESS ENTER TO CONTINUE) - Breakpoint: 2" + Chr(10) + "============================================" + Chr(10) + "globalIntVartest123: " + STR(globalIntVartest123))
def test(var1234 = 54):
    global globalIntVartest123
    input("(PRESS ENTER TO CONTINUE) - Breakpoint: 3" + Chr(10) + "============================================" + Chr(10) + "globalIntVartest123: " + STR(globalIntVartest123) + Chr(10) + "var1234: " + STR(var1234))
    testFunc1 = 69
    testFunc2 = 692
    input("(PRESS ENTER TO CONTINUE) - Breakpoint: 4" + Chr(10) + "============================================" + Chr(10) + "globalIntVartest123: " + STR(globalIntVartest123) + Chr(10) + "globalIntVartest123: " + STR(globalIntVartest123) + Chr(10) + "var1234: " + STR(var1234) + Chr(10) + "testFunc1: " + STR(testFunc1) + Chr(10) + "testFunc2: " + STR(testFunc2))
    testFunc3 = 6923
    input("(PRESS ENTER TO CONTINUE) - Breakpoint: 5" + Chr(10) + "============================================" + Chr(10) + "globalIntVartest123: " + STR(globalIntVartest123) + Chr(10) + "globalIntVartest123: " + STR(globalIntVartest123) + Chr(10) + "globalIntVartest123: " + STR(globalIntVartest123) + Chr(10) + "var1234: " + STR(var1234) + Chr(10) + "testFunc1: " + STR(testFunc1) + Chr(10) + "testFunc2: " + STR(testFunc2) + Chr(10) + "testFunc3: " + STR(testFunc3))
    print(var1234)
input("(PRESS ENTER TO CONTINUE) - Breakpoint: 6" + Chr(10) + "============================================" + Chr(10) + "globalIntVartest123: " + STR(globalIntVartest123))
var1 = 5
var2 = 6
shakdaz = "swdesfdg"
var3 = 7
print("Hello world")
input("(PRESS ENTER TO CONTINUE) - Breakpoint: 7" + Chr(10) + "============================================" + Chr(10) + "globalIntVartest123: " + STR(globalIntVartest123) + Chr(10) + "globalIntVartest123: " + STR(globalIntVartest123) + Chr(10) + "var1: " + STR(var1) + Chr(10) + "var2: " + STR(var2) + Chr(10) + "shakdaz: " + STR(shakdaz) + Chr(10) + "var3: " + STR(var3))
test()
