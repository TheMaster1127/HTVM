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

def StrLen(s: str) -> int:
    # Return the length of the given string
    return len(s)

def Chr(number: int) -> str:
    # Return the character corresponding to the Unicode code point, or an empty string if out of range
    return chr(number) if 0 <= number <= 0x10FFFF else ""

def Trim(inputString):
    return inputString.strip() if inputString else ""

def StringTrimRight(input, numChars):
    return input[:-numChars] if numChars <= len(input) else input


def HTVMmatchStrRrplace(line, matchString, replaceString):
    lineOut = ""
    if (not InStr(line, matchString)):
        return line
    allDelimiters = " ()[].,;:'!&|=<>+-*/^%~" + Chr(34)
    lineArr = []
    items1 = LoopParseFunc(line)
    for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
        lineArr.append(A_LoopField1)
    matchStringLEN = StrLen(matchString)
    replaceStringLEN = StrLen(replaceString)
    allPosForReplacing = []
    sildingLine = ""
    isStart = 1
    i1 = 0
    hasFound = 0
    hasFound2 = 0
    isStartTrue = 0
    isEndTrue = 0
    # char1 is for text outside the start
    char1 = ""
    # char2 is for text inside the start
    char2 = ""
    # char3 is for text inside the end
    char3 = ""
    # char4 is for text outside the end
    char4 = ""
    isMatch = 0
    sildingLine = ""
    isStart = 1
    i1 = 0
    hasFound = 0
    hasFound2 = 0
    isStartTrue = 0
    isEndTrue = 0
    for A_Index2 in range(0, len(lineArr) + 0):
        char1 = ""
        char2 = ""
        char3 = ""
        char4 = ""
        isMatch = 0
        if (A_Index2 != 0):
            isStart = 0
        sildingLine = ""
        for A_Index3 in range(0, matchStringLEN + 0):
            if (A_Index3 + i1 <= len(lineArr) - 1):
                sildingLine += lineArr[A_Index3 + i1]
        if (StrLen(sildingLine) < matchStringLEN):
            break
        #print("!!!!111111111!!!!!!: " . sildingLine)
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;==================
        if (sildingLine == matchString):
            hasFound = 1
            if (isStart != 1):
                #print("!!!!2222222222!!!!!!: " . lineArr[i1 - 1])
                char1 = lineArr[i1 - 1]
                #print("!!!!2222222222.555555555!!!!!!: " . lineArr[i1])
                char2 = lineArr[i1]
            else:
                isStartTrue = 1
            if (i1 + matchStringLEN < len(lineArr)):
                #print("!!!!3333333333.5555555555!!!!!!: " . lineArr[i1 + matchStringLEN - 1])
                char3 = lineArr[i1 + matchStringLEN - 1]
                #print("!!!!3333333333!!!!!!: " . lineArr[i1 + matchStringLEN])
                char4 = lineArr[i1 + matchStringLEN]
            else:
                isEndTrue = 1
            if (InStr(allDelimiters, char1) or InStr(allDelimiters, char2)):
                isStartTrue = 1
            if (InStr(allDelimiters, char3) or InStr(allDelimiters, char4)):
                isEndTrue = 1
            if (isStartTrue == 1 and isEndTrue == 1):
                isMatch = 1
        #;;;;;;;;;;;;;;;;;;;===============
        if (isMatch == 1):
            if (len(allPosForReplacing) > 0):
                for A_Index4 in range(0, len(allPosForReplacing) + 0):
                    if (i1 + 1 != allPosForReplacing[A_Index4]):
                        allPosForReplacing.append(i1 + 1)
                        break
            else:
                allPosForReplacing.append(i1 + 1)
        i1 = i1 + 1
    lineTEMP = ""
    lineOut = line
    #print(allPosForReplacing)
    if (len(allPosForReplacing) > 0):
        # matchStringLEN
        # replaceStringLEN
        l2 = 0
        currentPos = 0
        onceEnd = 0
        for A_Index5 in range(0, len(allPosForReplacing) + 0):
            if (A_Index5 == 0):
                currentPos = allPosForReplacing[A_Index5]
            else:
                currentPos = allPosForReplacing[A_Index5] - (matchStringLEN - replaceStringLEN)
            onceEnd = 0
            items6 = LoopParseFunc(lineOut)
            for A_Index6 , A_LoopField6 in enumerate(items6, start=0):
                if (A_Index6 + 2 > currentPos and A_Index6 + 1 < currentPos + matchStringLEN):
                    onceEnd = onceEnd + 1
                    #print("DDDDDDDDDDD" . STR(A_Index6))
                    if (onceEnd == 1):
                        lineTEMP += replaceString
                else:
                    lineTEMP += A_LoopField6
            lineOut = lineTEMP
            lineTEMP = ""
            #print(lineTEMP)
            l2 = l2 + 1
    else:
        return line
    return lineOut
varQYTYWAEUSR = ""
print(HTVMmatchStrRrplace("hi man", "hi", "hello"))
print(HTVMmatchStrRrplace("hi man", "man", "woman"))
print(HTVMmatchStrRrplace("func1(man.hello()) func1(man.hello())", ".hello", ".mello"))
print(HTVMmatchStrRrplace("func1(var1 plus plus var2 plus plus var34)", "plus plus", "+"))
print(HTVMmatchStrRrplace("var1.add() + var12.add()", ".add()", ".push()"))
print(HTVMmatchStrRrplace("var1.add() + var12.add()", ".add()", ".pu()"))
for A_Index7 in range(0, 10000 + 0):
    varQYTYWAEUSR += HTVMmatchStrRrplace("hi man", "hi", "hello") + "\n"
    varQYTYWAEUSR += HTVMmatchStrRrplace("hi man", "man", "woman") + "\n"
    varQYTYWAEUSR += HTVMmatchStrRrplace("func1(man.hello()) func1(man.hello())", ".hello", ".mello") + "\n"
    varQYTYWAEUSR += HTVMmatchStrRrplace("func1(var1 plus plus var2 plus plus var34)", "plus plus", "+") + "\n"
    varQYTYWAEUSR += HTVMmatchStrRrplace("var1.add() + var12.add()", ".add()", ".push()") + "\n"
    varQYTYWAEUSR += HTVMmatchStrRrplace("var1.add() + var12.add()", ".add()", ".pu()") + "\n"
varQYTYWAEUSR = StringTrimRight(varQYTYWAEUSR, 1)