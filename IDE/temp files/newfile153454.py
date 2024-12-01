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

def Trim(inputString):
    return inputString.strip() if inputString else ""

def StrReplace(originalString, find, replaceWith):
    return originalString.replace(find, replaceWith)

def RegExMatch(Haystack, NeedleRegEx, OutputVar=None, StartingPos=0):
    if Haystack is None or NeedleRegEx is None:
        return None
    regex = re.compile(NeedleRegEx)
    match = regex.search(Haystack)
    if match:
        if OutputVar is not None:
            OutputVar.append(match.group(0))
        return match.start() + 1
    else:
        return 0



def parseFunc(expresion):
    expresionOut = ""
    expresion = Trim(StrReplace(expresion, " ", ""))
    expresion = Trim(StrReplace(expresion, "(", " ( "))
    expresion = Trim(StrReplace(expresion, ")", " ) "))
    expresion = Trim(StrReplace(expresion, "+", " + "))
    expresion = Trim(StrReplace(expresion, "-", " - "))
    expresion = Trim(StrReplace(expresion, "/", " / "))
    expresion = Trim(StrReplace(expresion, "*", " * "))
    expresion = Trim(StrReplace(expresion, ",", " , "))
    expresionForFuncLookInF = ""
    items1 = LoopParseFunc(expresion, " ")
    for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
        expresionForFuncLookInF.append(A_LoopField1)
    expresionForFuncLookInF.append("")
    items2 = LoopParseFunc(expresion, " ")
    for A_Index2 , A_LoopField2 in enumerate(items2, start=0):
        # Check if the variable matches the regex pattern
        if (RegExMatch(A_LoopField2, "^[A-Za-z_][A-Za-z0-9_]*$")):
            print(A_LoopField2)
    return expresionOut
print(parseFunc("-5+func1(bar1, 5+5+(58+5/2--2), func2(VAR1234R, func3(func4(5))))"))