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

# Function to find the position of needle in haystack (str overload)
def InStr(haystack: str, needle: str) -> int:
    pos = haystack.find(needle)
    return pos + 1 if pos != -1 else 0

def StrLen(s: str) -> int:
    # Return the length of the given string
    return len(s)


def HTVMmatchStrRrplace(line, matchString, replaceString):
    lineOut = ""
    if (not InStr(line, matchString)):
        return line
    allDelimiters = " ()[]."
    lineArr = []
    items1 = LoopParseFunc(line)
    for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
        lineArr.append(A_LoopField1)
    matchStringLEN = StrLen(matchString)
    sildingLine = ""
    isStart = 1
    isEnd = 0
    i1 = 0
    hasFound = 0
    hasFound2 = 0
    for A_Index2 in range(0, 1 + 0):
        sildingLine = ""
        isStart = 1
        isEnd = 0
        i1 = 0
        hasFound = 0
        hasFound2 = 0
        for A_Index3 in range(0, len(lineArr) + 0):
            if (A_Index3 == len(lineArr) - 1):
                isEnd = 1
            if (A_Index3 != 0):
                isStart = 0
            sildingLine = ""
            for A_Index4 in range(0, matchStringLEN + 0):
                if (A_Index4 + i1 <= len(lineArr) - 1):
                    sildingLine += lineArr[A_Index4 + i1]
            if (StrLen(sildingLine) < matchStringLEN):
                break
            print("!!!!111111111!!!!!!: " + sildingLine)
            if (sildingLine == matchString):
                hasFound = 1
                print("!!!!2222222222!!!!!!: " + lineArr[i1 - 1])
                print("!!!!3333333333!!!!!!: " + lineArr[i1 + matchStringLEN])
            if (hasFound == 1):
                hasFound2 = 0
            i1 = i1 + 1
        if (hasFound == 0):
            return lineOut
    return lineOut
print(HTVMmatchStrRrplace("hi man", "hi", "hello"))
print(HTVMmatchStrRrplace("hi man", "man", "woman"))
print(HTVMmatchStrRrplace("func1(man.hello())", ".hello", ".mello"))
print(HTVMmatchStrRrplace("func1(var1 plus plus var2)", "plus plus", "+"))