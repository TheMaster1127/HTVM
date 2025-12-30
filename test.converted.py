

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


gloabal_var1 = 777777
gloabal_var2 = 7777778
def test1(var1):
    global gloabal_var1, gloabal_var2
    var_test1 = 7854
    # breakpoint was here
    input("(PRESS ENTER TO CONTINUE) - Breakpoint: 1" + Chr(10) + "============================================" + Chr(10) + "var1: " + STR(var1) + Chr(10) + "gloabal_var1: " + STR(gloabal_var1) + Chr(10) + "gloabal_var2: " + STR(gloabal_var2) + Chr(10) + "var_test1: " + STR(var_test1))
    return var1
def test2(var1):
    global gloabal_var2
    var_test2 = 6556
    var_test2 = 6556
    # breakpoint was here
    input("(PRESS ENTER TO CONTINUE) - Breakpoint: 2" + Chr(10) + "============================================" + Chr(10) + "var1: " + STR(var1) + Chr(10) + "gloabal_var2: " + STR(gloabal_var2) + Chr(10) + "var_test2: " + STR(var_test2))
    return var1
test1("wased")
test2("wasedderfg")
var1 = 0
# breakpoint was here
input("(PRESS ENTER TO CONTINUE) - Breakpoint: 3" + Chr(10) + "============================================" + Chr(10) + "var1: " + STR(var1))
for A_Index1 in range(0, 5):
    var1 += 1
    print(var1)
