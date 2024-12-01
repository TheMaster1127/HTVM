import random
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

# Function to find the position of needle in haystack (str overload)
def InStr(haystack: str, needle: str) -> int:
    pos = haystack.find(needle)
    return pos + 1 if pos != -1 else 0

def Random(min: int, max: int) -> int:
    # Generate and return a random number within the specified range
    return random.randint(min, max)

def Trim(inputString):
    return inputString.strip() if inputString else ""

def StrReplace(originalString, find, replaceWith):
    return originalString.replace(find, replaceWith)

def RegExMatch(haystack, needle):
    match = re.search(needle, haystack)
    return match.start() + 1 if match else 0 # 1-based index or 0 if no match



def callFunc(funcParams):
    # just test
    return STR(Random(12345, 1234567))
def parseFunc(expresion):
    print("=========================")
    print(expresion)
    print("=========================")
    expresion = Trim(StrReplace(expresion, " ", ""))
    expresion = Trim(StrReplace(expresion, "(", " ( "))
    expresion = Trim(StrReplace(expresion, ")", " ) "))
    expresion = Trim(StrReplace(expresion, "+", " + "))
    expresion = Trim(StrReplace(expresion, "-", " - "))
    expresion = Trim(StrReplace(expresion, "/", " / "))
    expresion = Trim(StrReplace(expresion, "*", " * "))
    expresion = Trim(StrReplace(expresion, ",", " , "))
    expresionForFuncLookInF = []
    items1 = LoopParseFunc(expresion, " ")
    for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
        expresionForFuncLookInF.append(A_LoopField1)
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
    for A_Index2 in range(0, 20 + 0):
        foundFunc = 0
        foundFunc2 = 0
        didWeSeeAfunc = 0
        countParentheses = 0
        countParenthesesOnceHelper = 0
        funcEndEnd = 0
        funcPosIndex1 = 0
        funcPosIndex2 = 0
        items3 = LoopParseFunc(expresion, " ")
        for A_Index3 , A_LoopField3 in enumerate(items3, start=0):
            if (foundFunc == 1):
                if (RegExMatch(A_LoopField3, "^[A-Za-z_][A-Za-z0-9_]*$") and expresionForFuncLookInF[A_Index3 + 1] == "(" and foundFunc == 1):
                    foundFunc2 = 1
                    funcPosIndex1 = A_Index3
                    countParentheses = 0
                    countParenthesesOnceHelper = 0
                    print("debug in: " + A_LoopField3)
                if (A_LoopField3 == "("):
                    countParentheses = countParentheses + 1
                    countParenthesesOnceHelper = countParenthesesOnceHelper + 1
                if (A_LoopField3 == ")"):
                    countParentheses = countParentheses - 1
                if (countParenthesesOnceHelper != 0):
                    if (countParentheses == 0):
                        funcEndEnd = 1
                        funcPosIndex2 = A_Index3
                        break
            # Check if the variable matches the regex pattern
            if (RegExMatch(A_LoopField3, "^[A-Za-z_][A-Za-z0-9_]*$") and expresionForFuncLookInF[A_Index3 + 1] == "(" and foundFunc == 0):
                foundFunc = 1
                funcPosIndex1 = A_Index3
                #print(A_LoopField3)
        if (foundFunc != 1):
            print("no more funcs")
            expresion = Trim(expresion)
            # eval
            # eval
            # eval
            # eval
            # eval
            # eval
            break
        expresionReplaceHelper1 = ""
        expresionReplaceHelper = ""
        items4 = LoopParseFunc(expresion, " ")
        for A_Index4 , A_LoopField4 in enumerate(items4, start=0):
            if (A_Index4 >= funcPosIndex1 and A_Index4 < funcPosIndex2):
                expresionReplaceHelper1 += A_LoopField4 + " "
                print("found: " + A_LoopField4)
            elif (A_Index4 == funcPosIndex2):
                expresionReplaceHelper1 += A_LoopField4 + " "
                print("found: " + A_LoopField4)
                expresionReplaceHelper += callFunc(Trim(expresionReplaceHelper1)) + " "
            else:
                expresionReplaceHelper += A_LoopField4 + " "
        expresion = Trim(expresionReplaceHelper)
        print("=========================")
        print(expresion)
        print("=========================")
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
    return expresion
print(parseFunc("-5+func1(bar1, 5+5+(58+5/2--2), func2(VAR1234R, func3(func4(5))))"))