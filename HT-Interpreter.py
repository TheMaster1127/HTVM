import math
import os
import re
import sys

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

def FileRead(path: str) -> str:
    # Check if the path is absolute, if not prepend the current working directory
    if not os.path.isabs(path):
        path = os.path.join(os.getcwd(), path)
    # Open and read the file content
    with open(path, 'r') as file:
        return file.read()

def StrLen(s: str) -> int:
    # Return the length of the given string
    return len(s)

def Chr(number: int) -> str:
    # Return the character corresponding to the Unicode code point, or an empty string if out of range
    return chr(number) if 0 <= number <= 0x10FFFF else ""

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

def Mod(dividend, divisor):
    return dividend % divisor

def GetParams():
    # Check if any command line arguments are provided
    if len(sys.argv) < 2:
        return ""
    # Store the provided command line arguments
    params = []
    for arg in sys.argv[1:]:
        if os.path.exists(arg):
            arg = os.path.abspath(arg)
        params.append(arg)
    return "\\n".join(params)

def RegExMatch(haystack, needle):
    match = re.search(needle, haystack)
    return match.start() + 1 if match else 0 # 1-based index or 0 if no match


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
str11 = ""
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
theIdNumOfThe34theVar = []
theIdNumOfThe34 = 0
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
    #print(outputTemp)
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
def expresionEvalHelp(expression):
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
        #print(innerExpression)
        # Evaluate the inner expression (this is where recursion handles nested parentheses)
        innerResult = expresionEvalHelp(innerExpression)
        # Replace the entire parentheses with the result
        expression = SubStr(expression, 1, startIndex - 1) + innerResult + SubStr(expression, endIndex)
    # Now evaluate the expression without parentheses
    return ExpresionEvalNoParentesis(expression)
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
def callFunc(funcParams):
    funcParamsOut = ""
    funcParams = Trim(funcParams)
    funcParams = StringTrimRight(funcParams, 1)
    funcName = ""
    items10 = LoopParseFunc(funcParams, " ")
    for A_Index10 , A_LoopField10 in enumerate(items10, start=0):
        if (A_Index10 == 0):
            funcName = Trim(A_LoopField10)
        if (A_Index10 > 1):
            funcParamsOut += A_LoopField10 + " "
    #print("debug funcname: " . funcName)
    funcParamsOut = StringTrimRight(funcParamsOut, 1)
    funcParams = Trim(StrReplace(Trim(funcParamsOut), " ", ""))
    funcParamsOut = ""
    if (funcName == "INT"):
        items11 = LoopParseFunc(funcParams, ",")
        for A_Index11 , A_LoopField11 in enumerate(items11, start=0):
            funcParamsOut += expresionEvalHelp(StringTrimRight(StringTrimLeft(A_LoopField11, 1), 1)) + "+"
    elif (funcName == "STR"):
        items12 = LoopParseFunc(funcParams, ",")
        for A_Index12 , A_LoopField12 in enumerate(items12, start=0):
            funcParamsOut += expresionEvalHelp(Chr(34) + A_LoopField12 + Chr(34)) + "+"
    elif (funcName == "print"):
        print(expresionEvalHelp(Trim(funcParams)))
        return "null"
    else:
        items13 = LoopParseFunc(funcParams, ",")
        for A_Index13 , A_LoopField13 in enumerate(items13, start=0):
            funcParamsOut += expresionEvalHelp(A_LoopField13) + "+"
    funcParamsOut = StringTrimRight(funcParamsOut, 1)
    return expresionEvalHelp(funcParamsOut)
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;; call func ;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
def expresionEval(expresion):
    #print("=========================")
    #print(expresion)
    #print("=========================")
    global theIdNumOfThe34
    global theIdNumOfThe34theVar
    HTpyCodeOUT754754 = ""
    areWEinSome34sNum = 0
    items14 = LoopParseFunc(expresion)
    for A_Index14 , A_LoopField14 in enumerate(items14, start=0):
        theIdNumOfThe34theVar.append("")
        theIdNumOfThe34theVar[A_Index14] = Chr(34)
    items15 = LoopParseFunc(expresion)
    for A_Index15 , A_LoopField15 in enumerate(items15, start=0):
        if (A_LoopField15 == Chr(34)):
            areWEinSome34sNum = areWEinSome34sNum + 1
        if (areWEinSome34sNum == 1):
            if (A_LoopField15 != Chr(34)):
                if (A_LoopField15 == Chr(96)):
                    theIdNumOfThe34theVar[theIdNumOfThe34] += Chr(92)
                else:
                    theIdNumOfThe34theVar[theIdNumOfThe34] += A_LoopField15
            else:
                theIdNumOfThe34 = theIdNumOfThe34 + 1
                HTpyCodeOUT754754 += "ihuiuuhuuhtheidFor|||||||||||asas|||||||||||theuhturtyphoutr|||||||||||" + str11 + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65)
        if (areWEinSome34sNum == 2 or areWEinSome34sNum == 0):
            if (A_LoopField15 != Chr(34)):
                HTpyCodeOUT754754 += A_LoopField15
            areWEinSome34sNum = 0
    expresion = HTpyCodeOUT754754
    for A_Index16 in range(0, theIdNumOfThe34 + 0):
        theIdNumOfThe34theVar[A_Index16 + 1] += Chr(34)
    for A_Index17 in range(0, theIdNumOfThe34 + 0):
        expresion = StrReplace(expresion, "ihuiuuhuuhtheidFor|||||||||||asas|||||||||||theuhturtyphoutr|||||||||||AA" + STR(A_Index17 + 1) + "AA", theIdNumOfThe34theVar[A_Index17 + 1])
    expresion = Trim(StrReplace(expresion, " ", ""))
    expresion = Trim(StrReplace(expresion, "(", " ( "))
    expresion = Trim(StrReplace(expresion, ")", " ) "))
    expresion = Trim(StrReplace(expresion, "+", " + "))
    expresion = Trim(StrReplace(expresion, "-", " - "))
    expresion = Trim(StrReplace(expresion, "/", " / "))
    expresion = Trim(StrReplace(expresion, "*", " * "))
    expresion = Trim(StrReplace(expresion, ",", " , "))
    expresionForFuncLookInF = []
    items18 = LoopParseFunc(expresion, " ")
    for A_Index18 , A_LoopField18 in enumerate(items18, start=0):
        expresionForFuncLookInF.append(A_LoopField18)
    expresionForFuncLookInF.append("")
    foundFunc = 0
    foundFunc2 = 0
    didWeSeeAfunc = 0
    countParentheses = 0
    countParenthesesOnceHelper = 0
    funcEndEnd = 0
    funcPosIndex1 = 0
    funcPosIndex2 = 0
    expresionReplaceHelper = ""
    expresionReplaceHelper1 = ""
    for A_Index19 in range(0, 20 + 0):
        foundFunc = 0
        foundFunc2 = 0
        didWeSeeAfunc = 0
        countParentheses = 0
        countParenthesesOnceHelper = 0
        funcEndEnd = 0
        funcPosIndex1 = 0
        funcPosIndex2 = 0
        items20 = LoopParseFunc(expresion, " ")
        for A_Index20 , A_LoopField20 in enumerate(items20, start=0):
            if (foundFunc == 1):
                if (RegExMatch(A_LoopField20, "^[A-Za-z_][A-Za-z0-9_]*$") and expresionForFuncLookInF[A_Index20 + 1] == "(" and foundFunc == 1):
                    foundFunc2 = 1
                    funcPosIndex1 = A_Index20
                    countParentheses = 0
                    countParenthesesOnceHelper = 0
                    #print("debug in: " + A_LoopField20)
                if (A_LoopField20 == "("):
                    countParentheses = countParentheses + 1
                    countParenthesesOnceHelper = countParenthesesOnceHelper + 1
                if (A_LoopField20 == ")"):
                    countParentheses = countParentheses - 1
                if (countParenthesesOnceHelper != 0):
                    if (countParentheses == 0):
                        funcEndEnd = 1
                        funcPosIndex2 = A_Index20
                        break
            # Check if the variable matches the regex pattern
            if (RegExMatch(A_LoopField20, "^[A-Za-z_][A-Za-z0-9_]*$") and expresionForFuncLookInF[A_Index20 + 1] == "(" and foundFunc == 0):
                foundFunc = 1
                funcPosIndex1 = A_Index20
                #print(A_LoopField20)
        if (foundFunc != 1):
            #print("no more funcs")
            expresion = Trim(expresion)
            expresion = Trim(expresionEvalHelp(expresion))
            # eval
            # eval
            # eval
            # eval
            # eval
            # eval
            break
        expresionReplaceHelper1 = ""
        expresionReplaceHelper = ""
        items21 = LoopParseFunc(expresion, " ")
        for A_Index21 , A_LoopField21 in enumerate(items21, start=0):
            if (A_Index21 >= funcPosIndex1 and A_Index21 < funcPosIndex2):
                expresionReplaceHelper1 += A_LoopField21 + " "
                #print("found: " . A_LoopField21)
            elif (A_Index21 == funcPosIndex2):
                expresionReplaceHelper1 += A_LoopField21 + " "
                #print("found: " . A_LoopField21)
                expresionReplaceHelper += callFunc(Trim(expresionReplaceHelper1)) + " "
            else:
                expresionReplaceHelper += A_LoopField21 + " "
        expresion = Trim(expresionReplaceHelper)
        #print("=========================")
        #print(expresion)
        #print("=========================")
        if (InStr(Trim(expresion), " ")):
            continue
        else:
            break
    # eval too
    # eval too
    # eval too
    # eval too
    expresion = Trim(expresion)
    # eval too
    expresion = Trim(expresionEvalHelp(expresion))
    return expresion
def interpreter():
    HTIcode = ""
    params = GetParams()
    if (params == ""):
        print("Usage:\nHT-Interpreter yourFile.hti\nOr use -c to open console mode.")
        return
    fileName = ""
    fileName = Trim(params)
    print(fileName)
    consoleMode = 0
    if (fileName == "-c"):
        consoleMode = 1
    else:
        HTIcode = FileRead(Trim(fileName))
        HTIcode = StrReplace(HTIcode, Chr(13), "")
    consoleModeInput = ""
    consoleModeInputHelp = ""
    if (consoleMode == 1):
        for A_Index22 , value in enumerate(iter(int, 1), start=0):
            consoleModeInput = Trim(input(">>> "))
            if (consoleModeInput == "exit()"):
                break
            else:
                consoleModeInputHelp = Trim(expresionEval(consoleModeInput))
                if (consoleModeInputHelp != "null"):
                    print(consoleModeInputHelp)
    else:
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        items23 = LoopParseFunc(HTIcode, "\n", "\r")
        for A_Index23 , A_LoopField23 in enumerate(items23, start=0):
            if (Trim(A_LoopField23) != ""):
                expresionEval(Trim(A_LoopField23))
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; main ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
test1 = 0
if (test1 == 1):
    print("Shunting Yard Algorithm")
    expresion = "1+2*4-3"
    print(expresionEvalHelp(expresion))
    testExpresions = "3+5|12-4|7*3|18/6|4+92|10-23|15+3-2|87-9|6+8/4|32+5|18-4/2|6/3+8|14-62|5+9/3|75-3|8+43|9/3+42|12+6*2-3|16-4/2+3|1+2*4-3"
    answersOfTheTestExpresions = "8|8|21|3|96|-13|16|78|8|37|16|10|-48|8|72|51|45|21|17|6"
    testIndexTestExpresions = 0
    TEMPanswersOfTheTestExpresions = ""
    DidWePassTheTestExpresions = 1
    DidWePassTheTestExpresionsCOUNT = 0
    DidWePassTheTestExpresionsCOUNTMAX = 0
    items24 = LoopParseFunc(testExpresions, "|")
    for A_Index24 , A_LoopField24 in enumerate(items24, start=0):
        DidWePassTheTestExpresionsCOUNT = DidWePassTheTestExpresionsCOUNT + 1
        DidWePassTheTestExpresionsCOUNTMAX = DidWePassTheTestExpresionsCOUNTMAX + 1
        testIndexTestExpresions = A_Index24
        items25 = LoopParseFunc(answersOfTheTestExpresions, "|")
        for A_Index25 , A_LoopField25 in enumerate(items25, start=0):
            if (A_Index25 == testIndexTestExpresions):
                TEMPanswersOfTheTestExpresions = A_LoopField25
        print(STR(A_Index24 + 1) + " ===============================")
        print(A_LoopField24)
        print(expresionEvalHelp(A_LoopField24))
        if (FLOAT(expresionEvalHelp(A_LoopField24)) == FLOAT(TEMPanswersOfTheTestExpresions)):
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
    print(expresionEvalHelp("5+(5+5)*1"))
    print("6+((8/2+6+((8/2)*3+6+((8+6+((8/2+6+((8/2)*3+6+((8/2)*3)))*3)/2)*3)))*3)")
    print(expresionEvalHelp("6+((8/2+6+((8/2)*3+6+((8+6+((8/2+6+((8/2)*3+6+((8/2)*3)))*3)/2)*3)))*3)"))
    print("((3 + 5) * (10 - 4) / 2) + (-7 * (3 + 2)) - (4 / (6 - 2)) * -3")
    print(expresionEvalHelp("((3 + 5) * (10 - 4) / 2) + (-7 * (3 + 2)) - (4 / (6 - 2)) * -3"))
    print("-((1+2)/((6*-7)+(7*-4)/2)-3)")
    print(FLOAT(expresionEvalHelp("-((1+2)/((6*-7)+(7*-4)/2)-3)")))
    print("=-=-=-=-=-=-=-=-=-=-=-=-=-=")
    print("=-=-=-=-=-=-=-=-=-=-=-=-=-=")
    print("=-=-=-=-=-=-=-=-=-=-=-=-=-=")
    print(expresionEval("-5+func1(45+1, 5+5+(58+5/2--2), func2(56, func3(func4(5))))"))
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# runing the interpreter
interpreter()