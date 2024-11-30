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

def StrLen(s: str) -> int:
    # Return the length of the given string
    return len(s)

def Exp(value: float) -> float:
    return math.exp(value)

def SubStr(s, startPos, length=None):
    if s is None or s == "":
        return ""
    if length is None or length == "":
        length = len(s) - startPos + 1
    if startPos < 1:
        startPos = len(s) + startPos
    return s[startPos - 1:startPos - 1 + length]

def Trim(inputString):
    return inputString.strip() if inputString else ""

def StrReplace(originalString, find, replaceWith):
    return originalString.replace(find, replaceWith)

def StringTrimLeft(input, numChars):
    return input[numChars:] if numChars <= len(input) else input

def StringTrimRight(input, numChars):
    return input[:-numChars] if numChars <= len(input) else input


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
float1 = 0.0
float2 = 0.0
float3 = 0.0
float4 = 0.0
float5 = 0.0
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
def ExpresionEvalNoParentesis(expresion):
    expresionOut = ""
    holdingStack = []
    outputTemp = []
    solvingStack = []
    input = "0"
    arithmeticOperations = "+-/*"
    arithmeticOperationStrength = 0
    tempPopHoldingStack = ""
    indexOfexpresionLoop = 0
    tempHoldingStackNumFIX = 0
    expresion = StrReplace(expresion, " ", "")
    expresion = StrReplace(expresion, "-", " - ")
    expresion = StrReplace(expresion, "+", " + ")
    expresion = StrReplace(expresion, "*", " * ")
    expresion = StrReplace(expresion, "/", " / ")
    expresion = StrReplace(expresion, "(", " ( ")
    expresion = StrReplace(expresion, ")", " ) ")
    addNegativeNums = ""
    addNegativeNumsFurture = []
    expresion = Trim(expresion)
    items2 = LoopParseFunc(expresion, " ")
    for A_Index2 , A_LoopField2 in enumerate(items2, start=0):
        addNegativeNumsFurture.append(A_LoopField2)
    skip = 0
    addNegativeNumsFurture.append("")
    items3 = LoopParseFunc(expresion, " ")
    for A_Index3 , A_LoopField3 in enumerate(items3, start=0):
        if (A_Index3 == 0 and A_LoopField3 == "-"):
            addNegativeNums += Trim(A_LoopField3) + addNegativeNumsFurture[A_Index3 + 1] + " "
            skip = 1
        elif (A_LoopField3 == "-" and (addNegativeNumsFurture[A_Index3 - 1] == "*" or addNegativeNumsFurture[A_Index3 - 1] == "/" or addNegativeNumsFurture[A_Index3 - 1] == "-" or addNegativeNumsFurture[A_Index3 - 1] == "+")):
            addNegativeNums += Trim(A_LoopField3) + addNegativeNumsFurture[A_Index3 + 1] + " "
            skip = 1
        else:
            if (skip != 1):
                addNegativeNums += A_LoopField3 + " "
                skip = 0
            else:
                skip = 0
    expresion = StringTrimRight(addNegativeNums, 1)
    expresion = Trim(expresion)
    #print("DEBUGGGGGGGGGGGG:" . expresion)
    output234543 = []
    items4 = LoopParseFunc(expresion, " ")
    for A_Index4 , A_LoopField4 in enumerate(items4, start=0):
        indexOfexpresionLoop = A_Index4 + 1
        input = A_LoopField4
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
                    for A_Index5 , value in enumerate(iter(int, 1), start=0):
                        if (len(holdingStack) > 0 and InStr(arithmeticOperations, holdingStack[len(holdingStack) - 1]) > InStr(arithmeticOperations, input)):
                            tempHoldingStackNumFIX = len(holdingStack)
                            for A_Index6 in range(0, tempHoldingStackNumFIX + 0):
                                tempPopHoldingStack = holdingStack[len(holdingStack) - 1]
                                holdingStack.pop()
                                outputTemp.append(tempPopHoldingStack)
                        else:
                            break
                    holdingStack.append(input)
                # 2 else and 1 loop end
    if (len(holdingStack) != 0 or STR(len(holdingStack)) != ""):
        for A_Index7 in range(0, len(holdingStack) + 0):
            if (Trim(holdingStack[len(holdingStack) - 1 - A_Index7]) != ""):
                outputTemp.append(holdingStack[len(holdingStack) - 1 - A_Index7])
    fixOutputTempRMparanesises = len(outputTemp)
    outputTemp2 = []
    for A_Index8 in range(0, fixOutputTempRMparanesises + 0):
        if (Trim(outputTemp[A_Index8]) != ""):
            outputTemp2.append(outputTemp[A_Index8])
    outputTemp = outputTemp2
    print(outputTemp)
    for A_Index9 , value in enumerate(iter(int, 1), start=0):
        if (len(outputTemp) == 0 or STR(len(outputTemp)) == ""):
            break
        tempPopHoldingStack = outputTemp[0]
        outputTemp = popFirstStrArrayElement(outputTemp)
        solvingStack.append(tempPopHoldingStack)
        if (InStr(arithmeticOperations, solvingStack[len(solvingStack) - 1]) != 0):
            solvingStack = swapLast2StrArrayElement(solvingStack)
            float1 = FLOAT(solvingStack[len(solvingStack) - 3])
            str2 = solvingStack[len(solvingStack) - 2]
            float3 = FLOAT(solvingStack[len(solvingStack) - 1])
            solvingStack.pop()
            solvingStack.pop()
            solvingStack.pop()
            if (str2 == "-"):
                float4 = float1 - float3
                solvingStack.append(STR(float4))
            if (str2 == "+"):
                float4 = float1 + float3
                solvingStack.append(STR(float4))
            if (str2 == "*"):
                float4 = float1 * float3
                solvingStack.append(STR(float4))
            if (str2 == "/"):
                float4 = float1 / float3
                solvingStack.append(STR(float4))
    expresionOut = Trim(solvingStack[len(solvingStack) - 1])
    if (SubStr(expresionOut, 1, 2) == "- "):
        expresionOut = StringTrimLeft(expresionOut, 2)
        expresionOut = "-" + expresionOut
    if (Trim(expresionOut) == ""):
        expresionOut = "null"
    return expresionOut
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
def expresionEval(expression):
    startIndex = 0
    endIndex = 0
    innerExpression = ""
    innerResult = ""
    openCount = 0
    char123 = ""
    # Remove spaces for consistency
    expression = StrReplace(expression, " ", "")
    # Loop until no more parentheses are left
    while (InStr(expression, "(")):
        # Find the position of the first '('
        startIndex = InStr(expression, "(")
        # Now, find the matching closing ')'
        openCount = 1
        endIndex = startIndex + 1
        # Loop to find the matching closing ')'
        while (openCount > 0 and endIndex <= StrLen(expression)):
            char123 = SubStr(expression, endIndex, 1)
            if (char123 == "("):
                openCount = openCount + 1
            elif (char123 == ")"):
                openCount = openCount - 1
            endIndex = endIndex + 1
        # Extract the inner expression
        innerExpression = SubStr(expression, startIndex + 1, endIndex - startIndex - 2)
        # Evaluate the inner expression (this is where recursion handles nested parentheses)
        innerResult = expresionEval(innerExpression)
        # Replace the entire parentheses with the result
        expression = SubStr(expression, 1, startIndex - 1) + innerResult + SubStr(expression, endIndex)
    # Now evaluate the expression without parentheses
    return ExpresionEvalNoParentesis(expression)
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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
items10 = LoopParseFunc(testExpresions, "|")
for A_Index10 , A_LoopField10 in enumerate(items10, start=0):
    DidWePassTheTestExpresionsCOUNT = DidWePassTheTestExpresionsCOUNT + 1
    DidWePassTheTestExpresionsCOUNTMAX = DidWePassTheTestExpresionsCOUNTMAX + 1
    testIndexTestExpresions = A_Index10
    items11 = LoopParseFunc(answersOfTheTestExpresions, "|")
    for A_Index11 , A_LoopField11 in enumerate(items11, start=0):
        if (A_Index11 == testIndexTestExpresions):
            TEMPanswersOfTheTestExpresions = A_LoopField11
    print(STR(A_Index10 + 1) + " ===============================")
    print(A_LoopField10)
    print(expresionEval(A_LoopField10))
    if (FLOAT(expresionEval(A_LoopField10)) == FLOAT(TEMPanswersOfTheTestExpresions)):
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
print("5+(5+5)*1")
print(expresionEval("5+(5+5)*1"))
print("6+((8/2+6+((8/2)*3+6+((8+6+((8/2+6+((8/2)*3+6+((8/2)*3)))*3)/2)*3)))*3)")
print(expresionEval("6+((8/2+6+((8/2)*3+6+((8+6+((8/2+6+((8/2)*3+6+((8/2)*3)))*3)/2)*3)))*3)"))
print("((3 + 5) * (10 - 4) / 2) + (-7 * (3 + 2)) - (4 / (6 - 2)) * -3")
print(expresionEval("((3 + 5) * (10 - 4) / 2) + (-7 * (3 + 2)) - (4 / (6 - 2)) * -3"))
print("-((1+2)/((6*-7)+(7*-4)/2)-3)")
print(FLOAT(expresionEval("-((1+2)/((6*-7)+(7*-4)/2)-3)")))