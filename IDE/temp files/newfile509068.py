import math
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

# Convert value to float
def FLOAT(value):
    try:
        return float(value)
    except ValueError:
        raise TypeError("Cannot convert to float")

# Function to find the position of needle in haystack (str overload)
def InStr(haystack: str, needle: str) -> int:
    pos = haystack.find(needle)
    return pos + 1 if pos != -1 else 0

# used imput func

def Exp(value: float) -> float:
    return math.exp(value)

def Trim(inputString):
    return inputString.strip() if inputString else ""

def StrReplace(originalString, find, replaceWith):
    return originalString.replace(find, replaceWith)


#Shunting Yard Algorithm
str1 = ""
str2 = ""
str3 = ""
str4 = ""
str5 = ""
str6 = ""
str7 = ""
str8 = ""
str9 = ""
str10 = ""
int1 = 0
int2 = 0
int3 = 0
int4 = 0
int5 = 0
int6 = 0
int7 = 0
def  swapLast2StrArrayElement(theStrArray):
    # Check if the array has at least two elements
    if (len(theStrArray) < 2):
        return theStrArray
    # Get the indices of the last two elements
    lastIndex = len(theStrArray) - 1
    secondLastIndex = lastIndex - 1
    # Swap the last two elements
    temp = theStrArray[lastIndex]
    theStrArray[lastIndex] = theStrArray[secondLastIndex]
    theStrArray[secondLastIndex] = temp
    # Return the modified array
    return theStrArray
def  popFirstStrArrayElement(theStrArray):
    out123 = []
    for A_Index1 in range(0, len(theStrArray) + 0):
        if (A_Index1 > 0):
            out123.append(theStrArray[A_Index1])
    return out123
def expresionEval(expresion):
    expresionOut = ""
    holdingStack = []
    outputTemp = []
    solvingStack = []
    input = "0"
    arithmeticOperations = "-+*/"
    arithmeticOperationStrength = 0
    tempPopHoldingStack = ""
    indexOfexpresionLoop = 0
    expresion = StrReplace(expresion, " ", "")
    expresion = StrReplace(expresion, "-", " - ")
    expresion = StrReplace(expresion, "+", " + ")
    expresion = StrReplace(expresion, "*", " * ")
    expresion = StrReplace(expresion, "/", " / ")
    items2 = LoopParseFunc(expresion, " ")
    for A_Index2 , A_LoopField2 in enumerate(items2, start=0):
        indexOfexpresionLoop = A_Index2 + 1
        input = A_LoopField2
        if (InStr(arithmeticOperations, input) == 0):
            # numbers
            #print(input)
            outputTemp.append(input)
        else:
            # arithmeticOperation
            #print(input)
            if (len(holdingStack) == 0):
                holdingStack.append(input)
            else:
                if (InStr(arithmeticOperations, input) == InStr(arithmeticOperations, holdingStack[len(holdingStack) - 1])):
                    outputTemp.append(input)
                elif (InStr(arithmeticOperations, holdingStack[len(holdingStack) - 1]) < InStr(arithmeticOperations, input)):
                    holdingStack.append(input)
                else:
                    # what do we do
                    # add the last
                    for A_Index3 , value in enumerate(iter(int, 1), start=0):
                        if (len(holdingStack) > 0 and InStr(arithmeticOperations, holdingStack[len(holdingStack) - 1]) > InStr(arithmeticOperations, input)):
                            tempPopHoldingStack = holdingStack[len(holdingStack) - 1]
                            holdingStack.pop()
                            outputTemp.append(tempPopHoldingStack)
                        else:
                            break
                    holdingStack.append(input)
                # 2 else and 1 loop end
    if (len(holdingStack) != 0 or STR(len(holdingStack)) != ""):
        for A_Index4 in range(0, len(holdingStack) + 0):
            outputTemp.append(holdingStack[A_Index4])
    print(outputTemp)
    for A_Index5 , value in enumerate(iter(int, 1), start=0):
        if (len(outputTemp) == 0 or STR(len(outputTemp)) == ""):
            break
        tempPopHoldingStack = outputTemp[0]
        outputTemp = popFirstStrArrayElement(outputTemp)
        solvingStack.append(tempPopHoldingStack)
        if (InStr(arithmeticOperations, solvingStack[len(solvingStack) - 1]) != 0):
            solvingStack = swapLast2StrArrayElement(solvingStack)
            int1 = FLOAT(solvingStack[len(solvingStack) - 3])
            str2 = solvingStack[len(solvingStack) - 2]
            int3 = FLOAT(solvingStack[len(solvingStack) - 1])
            solvingStack.pop()
            solvingStack.pop()
            solvingStack.pop()
            if (str2 == "-"):
                int4 = int1 - int3
                solvingStack.append(STR(int4))
            if (str2 == "+"):
                int4 = int1 + int3
                solvingStack.append(STR(int4))
            if (str2 == "*"):
                int4 = int1 * int3
                solvingStack.append(STR(int4))
            if (str2 == "/"):
                int4 = int1 / int3
                solvingStack.append(STR(int4))
    expresionOut = solvingStack[len(solvingStack) - 1]
    if (Trim(expresionOut) == ""):
        expresionOut = "null"
    return expresionOut
print("Shunting Yard Algorithm")
expresion = "1+2*4-3"
print(expresionEval(expresion))
testExpresions = "3+5|12-4|7*3|18/6|4+92|10-23|15+3-2|87-9|6+8/4|32+5|18-4/2|6/3+8|14-62|5+9/3|75-3|8+43|9/3+42|12+6*2-3|16-4/2+3|1+2*4-3"
answersOfTheTestExpresions = "8|8|21|3|96|-13|16|78|8|37|16|10|-48|8|72|51|45|21|17|6"
testIndexTestExpresions = 0
TEMPanswersOfTheTestExpresions = ""
DidWePassTheTestExpresions = 1
DidWePassTheTestExpresionsCOUNT = 0
DidWePassTheTestExpresionsCOUNTMAX = 0
items6 = LoopParseFunc(testExpresions, "|")
for A_Index6 , A_LoopField6 in enumerate(items6, start=0):
    DidWePassTheTestExpresionsCOUNT = DidWePassTheTestExpresionsCOUNT + 1
    DidWePassTheTestExpresionsCOUNTMAX = DidWePassTheTestExpresionsCOUNTMAX + 1
    testIndexTestExpresions = A_Index6
    items7 = LoopParseFunc(answersOfTheTestExpresions, "|")
    for A_Index7 , A_LoopField7 in enumerate(items7, start=0):
        if (A_Index7 == testIndexTestExpresions):
            TEMPanswersOfTheTestExpresions = A_LoopField7
    print(STR(A_Index6 + 1) + " ===============================")
    print(A_LoopField6)
    print(expresionEval(A_LoopField6))
    if (FLOAT(expresionEval(A_LoopField6)) == FLOAT(TEMPanswersOfTheTestExpresions)):
        print("true")
    else:
        print("false")
        DidWePassTheTestExpresionsCOUNT = DidWePassTheTestExpresionsCOUNT - 1
        DidWePassTheTestExpresions = 0
print("==================================")
print("==================================")
if (DidWePassTheTestExpresions == 0):
    print("TestExpresions NOT PASSED!!! " + STR(DidWePassTheTestExpresionsCOUNT) + "/" + STR(DidWePassTheTestExpresionsCOUNTMAX))
else:
    print("TestExpresions PASSED!!!" + STR(DidWePassTheTestExpresionsCOUNT) + "/" + STR(DidWePassTheTestExpresionsCOUNTMAX))