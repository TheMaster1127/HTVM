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


def strReverse(theString):
    outStr = ""
    theArrStr = []
    items1 = LoopParseFunc(theString)
    for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
        theArrStr.append(A_LoopField1)
    for A_Index2 in range(0, len(theArrStr) + 0):
        outStr += theArrStr[len(theArrStr) - (A_Index2 + 1)]
    return outStr
def isPalindrome(theString):
    if (Trim(strReverse(theString)) == Trim(theString)):
        return True
    return False
print(isPalindrome("123"))
print(isPalindrome("121"))
print(isPalindrome("bob"))
