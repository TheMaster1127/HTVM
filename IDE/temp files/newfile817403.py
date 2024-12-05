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

def Trim(inputString):
    return inputString.strip() if inputString else ""

def StringTrimRight(input, numChars):
    return input[:-numChars] if numChars <= len(input) else input



def getFilesPathsAndStuff(command):
    files = ""
    filesOut = ""
    files = Trim(getDataFromEndpoint(Trim(command), "/getFilesPathsAndStuff"))
    items1 = LoopParseFunc(files, "\n", "\r")
    for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
        if (Trim(A_LoopField1) != ""):
            filesOut += Trim(A_LoopField1) + "\n"
    filesOut = StringTrimRight(filesOut, 1)
    return filesOut