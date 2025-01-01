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

def StrLen(s: str) -> int:
    # Return the length of the given string
    return len(s)

def SubStr(s, startPos, length=None):
    if s is None or s == "":
        return ""
    if length is None or length == "":
        length = len(s) - startPos + 1
    if startPos < 1:
        startPos = len(s) + startPos
    return s[startPos - 1:startPos - 1 + length]


def SubStrLastChars(text, numOfChars):
    strLength = StrLen(text)
    if (numOfChars > strLength):
        return text
    textArr = []
    items1 = LoopParseFunc(text)
    for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
        textArr.append(A_LoopField1)
    LastOut = ""
    for A_Index2 in range(0, numOfChars + 0):
        LastOut = textArr[(strLength - A_Index2)] + LastOut
    return LastOut
print(SubStrLastChars("hello", 2))