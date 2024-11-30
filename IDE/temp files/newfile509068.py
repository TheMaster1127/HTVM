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

# used imput func

def Mod(dividend, divisor):
    return dividend % divisor


#Shunting Yard Algorithm
def expresionEval(expresion):
    expresionOut = "0"
    holdingStack = []
    outputTemp = []
    solvingStack = []
    input = "0"
    arithmeticOperations = "/*=-"
    arithmeticOperationStrength = 0
    indexOfexpresionLoop = 0
    items1 = LoopParseFunc(expresion)
    for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
        indexOfexpresionLoop = A_Index1 + 1
        input = A_LoopField1
        if (Mod(indexOfexpresionLoop, 2) == 1):
            # numbers
            print(input)
        else:
            # arithmeticOperation
            print(input)
    return expresionOut
print("Shunting Yard Algorithm")
expresion = "1+2*4-3"
print(expresionEval(expresion))
