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

def FileRead(path: str) -> str:
    # Check if the path is absolute, if not prepend the current working directory
    if not os.path.isabs(path):
        path = os.path.join(os.getcwd(), path)
    # Open and read the file content
    with open(path, 'r') as file:
        return file.read()

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

def StrLower(string):
    return string.lower()

def StrSplit(inputStr, delimiter, num):
    parts = inputStr.split(delimiter)
    return parts[num - 1] if 0 < num <= len(parts) else ""

def FileExist(path):
    return os.path.exists(path)

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

# Function to handle application termination
def ExitApp():
    os._exit(1)

# Function to sort and remove duplicates
def sortArr(input_list):
    """
    Function to sort a list of strings and remove duplicates.
    """
    return sorted(set(input_list))

def countChars(string, theChar):
    return string.count(theChar)


params = ""
param1 = ""
param2 = ""
params = Trim(GetParams())
if (Trim(params) == ""):
    print("no params Exiting...")
    ExitApp()
items1 = LoopParseFunc(params, "\n", "\r")
for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
    if (A_Index1 == 0):
        print(A_LoopField1)
        param1 = Trim(A_LoopField1)
    if (A_Index1 == 1):
        print(A_LoopField1)
        param2 = Trim(A_LoopField1)
if (!(FileExist(param1))):
    print("the file doesn't exist!!!")
    ExitApp()
checkIfFuncNameExists = 0
if (Trim(param2) != ""):
    checkIfFuncNameExists = 1
instructionFileData = ""
instructionFileData = FileRead(Trim(param1))
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
inFunc = 0
tempArrayInitOSP = []
OSPHTVMOSP_funcData = [
"funcData",
tempArrayInitOSP,
tempArrayInitOSP,
tempArrayInitOSP,
]
items2 = LoopParseFunc(instructionFileData, "\n", "\r")
for A_Index2 , A_LoopField2 in enumerate(items2, start=0):
    if (Trim(A_LoopField2) == "funcEND======================funcEND=============="):
        inFunc = 0
    if (inFunc == 1):
        if (SubStr(Trim(A_LoopField2), 1, 6) == "lang: "):
            OSPHTVMOSP_funcData[1].append(Trim(A_LoopField2))
        elif (SubStr(Trim(A_LoopField2), 1, 6) == "name: "):
            OSPHTVMOSP_funcData[2].append(Trim(A_LoopField2))
        elif (SubStr(Trim(A_LoopField2), 1, 13) == "description: "):
            OSPHTVMOSP_funcData[3].append(Trim(A_LoopField2))
    if (Trim(A_LoopField2) == "func======================func=============="):
        inFunc = 1
allFuncNames = sortArr(OSPHTVMOSP_funcData[2])
theFuncThatExistsIsCalled = ""
if (checkIfFuncNameExists == 1):
    exitedLoopCheckIfFuncNameExists = 0
    for A_Index3 in range(0, len(allFuncNames) + 0):
        if (StrLower(param2) == StrLower(Trim(StrSplit(allFuncNames[A_Index3], ":", 2)))):
            theFuncThatExistsIsCalled = Trim(StrSplit(allFuncNames[A_Index3], ":", 2))
            exitedLoopCheckIfFuncNameExists = 1
            break
    if (exitedLoopCheckIfFuncNameExists == 1):
        print("the func alredy exists!!! called: " + theFuncThatExistsIsCalled)
        ExitApp()
    else:
        print("the func dosent exists!!! YOU CAN USE IT")
        ExitApp()
# allFuncNames
allFuncNamesTemp = ""
tempDesc = ""
tempLang = ""
for A_Index4 in range(0, OSPHTVMOSP_funcData.len(name) + 0):
    #print(OSPHTVMOSP_funcData[2][A_Index4])
    allFuncNamesTemp = OSPHTVMOSP_funcData[2][A_Index4]
    tempLang = OSPHTVMOSP_funcData[1][A_Index4]
    tempDesc = OSPHTVMOSP_funcData[3][A_Index4]
    for A_Index5 in range(0, len(allFuncNames) + 0):
        if (Trim(allFuncNamesTemp) == Trim(StrSplit(allFuncNames[A_Index5], "|", 1))):
            if (countChars(allFuncNames[A_Index5], "|") == 0):
                allFuncNames[A_Index5] = allFuncNames[A_Index5] + "|" + Trim(tempDesc) + "|" + Trim(tempLang)
            else:
                allFuncNames[A_Index5] = allFuncNames[A_Index5] + "|" + Trim(tempLang)
allFuncs = []
tempstr = ""
isLangCpp = ""
isLangPy = ""
isLangJs = ""
allFuncsTempAdd = ""
isDescNull = 0
for A_Index6 in range(0, len(allFuncNames) + 0):
    print(allFuncNames[A_Index6])
    tempstr = Trim(allFuncNames[A_Index6])
    isDescNull = 0
    allFuncsTempAdd = ""
    isLangCpp = "No"
    isLangPy = "No"
    isLangJs = "No"
    items7 = LoopParseFunc(tempstr, "|")
    for A_Index7 , A_LoopField7 in enumerate(items7, start=0):
        if (SubStr(Trim(A_LoopField7), 1, 8) == "lang: js"):
            isLangJs = "Yes"
        elif (SubStr(Trim(A_LoopField7), 1, 8) == "lang: py"):
            isLangPy = "Yes"
        elif (SubStr(Trim(A_LoopField7), 1, 9) == "lang: cpp"):
            isLangCpp = "Yes"
        elif (SubStr(Trim(A_LoopField7), 1, 6) == "name: "):
            allFuncsTempAdd += Trim(A_LoopField7) + "|"
        elif (SubStr(Trim(A_LoopField7), 1, 13) == "description: "):
            allFuncsTempAdd += Trim(A_LoopField7) + "|"
        if (Trim(StrLower(A_LoopField7)) == "description: null"):
            isDescNull = 1
    if (isDescNull != 1):
        allFuncsTempAdd += isLangCpp + "|" + isLangPy + "|" + isLangJs
        allFuncs.append(allFuncsTempAdd)
for A_Index8 in range(0, 20 + 0):
    print("===========================================")
categories = []
theCurrentLine = ""
theCurrentDescCategory = ""
once = 0
didWeFindSameCategory = 0
for A_Index9 in range(0, len(allFuncs) + 0):
    print(allFuncs[A_Index9])
    once = once + 1
    theCurrentLine = Trim(allFuncs[A_Index9])
    theCurrentDescCategory = Trim(StrSplit(theCurrentLine, "|", 2))
    theCurrentDescCategory = Trim(StrSplit(theCurrentDescCategory, ":", 2))
    theCurrentDescCategory = Trim(StrLower(Trim(StrSplit(theCurrentDescCategory, "~~~", 1))))
    didWeFindSameCategory = 0
    if (once == 1):
        categories.append(theCurrentDescCategory + "\n" + theCurrentLine)
    else:
        for A_Index10 in range(0, len(categories) + 0):
            if (Trim(StrLower(StrSplit(categories[A_Index10], "\n", 1))) == Trim(theCurrentDescCategory)):
                didWeFindSameCategory = 1
                categories[A_Index10] = categories[A_Index10] + "\n" + theCurrentLine
                break
        if (didWeFindSameCategory == 0):
            categories.append(theCurrentDescCategory + "\n" + theCurrentLine)
for A_Index11 in range(0, 20 + 0):
    print("==========================")
for A_Index12 in range(0, len(categories) + 0):
    print(categories[A_Index12])