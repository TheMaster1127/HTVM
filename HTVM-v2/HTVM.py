import math
import os
import random
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

# Convert value to integer
def INT(value):
    try:
        # Try converting the value to an integer
        return int(float(value))
    except ValueError:
        # If conversion fails, raise a TypeError
        raise TypeError("Cannot convert to integer")

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

def FileDelete(path: str) -> bool:
    # Check if the file exists and remove it
    if os.path.exists(path):
        os.remove(path)
        return True
    return False

def FileAppend(content: str, path: str) -> bool:
    # Open the file in append mode and write the content
    try:
        with open(path, 'a') as file:
            file.write(content)
        return True
    except IOError:
        print("Error: Could not open the file for appending.")
        return False

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

def StrLower(string):
    return string.lower()

def StrSplit(inputStr, delimiter, num):
    parts = inputStr.split(delimiter)
    return parts[num - 1] if 0 < num <= len(parts) else ""

def Mod(dividend, divisor):
    return dividend % divisor

def Sort(var_name, options):
    # Determine delimiter based on options
    delimiter = '\n'
    if 'D' in options:
        delimiter = options[options.index('D') + 1]
    
    # Split the input variable by delimiter
    items = var_name.split(delimiter)
    
    # Remove empty items and strip whitespace
    items = [item.strip() for item in items if item.strip()]
    
    # Apply sorting based on options
    if 'N' in options:
        # Numeric sort
        items.sort(key=lambda x: int(x))
    elif 'Random' in options:
        # Random sort
        random.shuffle(items)
    else:
        # Default alphabetical sort
        items.sort(key=lambda x: x.lower() if 'C' not in options else x)
    
    # Reverse if 'R' option is present
    if 'R' in options:
        items.reverse()
    
    # Remove duplicates if 'U' option is present
    if 'U' in options:
        seen = set()
        unique_items = []
        for item in items:
            lower_item = item.lower() if 'C' not in options else item
            if lower_item not in seen:
                seen.add(lower_item)
                unique_items.append(item)
        items = unique_items
    
    # Join the sorted items back into a string
    sorted_var = delimiter.join(items)
    
    return sorted_var

def RegExReplace(inputStr, regexPattern, replacement):
    # Create a regular expression object using the provided pattern
    
    regex = re.compile(regexPattern, re.MULTILINE)  # re.MULTILINE for multi-line matching
    # Use the sub() method to perform the regex replacement
    resultStr = regex.sub(replacement, inputStr)
    # Return the modified string
    return resultStr

def RegExMatch(haystack, needle):
    match = re.search(needle, haystack)
    return match.start() + 1 if match else 0 # 1-based index or 0 if no match

def HTVM_getLang_HTVM():
    return "py"

noParams = False
allArgs = ""
# in allArgs will look like:
# full/path/code/
# HTVM-Instruction.txt file
# lang to convert to
# HTVM-Instruction.txt file MORE
# HTVM-Instruction.txt file MORE
# HTVM-Instruction.txt file MORE and more
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
def HTVM_v2_HTVM():
    global noParams
    params = Trim(GetParams())
    if (params == ""):
        noParams = True
       	print("Usage: HTVM <yourCodeFileName.yourExtension> <HTVM-instructions.txt> [optional LangToTranspileTo]\n\nOptions:\n  <yourCodeFileName.yourExtension>  The source code file to transpile.\n  <HTVM-instructions.txt>              The instructions file for transpilation.\n  [LangToTranspileTo]                Optional: Specify the target language (cpp, py, js, go, lua, cs, java, kt, rb, nim, ahk, swift, dart, ts, scala, groovy, htvm or <yourExtension>).\n\nExample:\n  HTVM main.htvm HTVM-instructions.txt cpp\n")
        return
    items1 = LoopParseFunc(params, "\n", "\r")
    for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
        allArgs += Trim(A_LoopField1) + "\n"
    allArgs = StringTrimRight(allArgs, 1)



str0 = "nothing"
str00 = "nothing"
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
str12 = ""
str13 = ""
str14 = ""
int0 = 0
int1 = 0
int2 = 0
int3 = 0
int4 = 0
int5 = 0
int6 = 0
int7 = 0
argHTVMinstrMOVE = []
extraCodeReturned = ""
langToConvertTo = ""
langFileExtension = ""
commands = ""
keyWordAlliance = ""
keyWordCrew = ""
keyWordMethod = ""
keyWordDefObj = ""
keyWordPorp = ""
keyWordThis = ""
keyWordInclude = ""
keyWordIncludeInTheTranspiledLang = ""
keyWordCodeInTheTranspiledLangStart = ""
keyWordCodeInTheTranspiledLangEnd = ""
keyWordCodeInTheTranspiledLangStartCPP = ""
keyWordCodeInTheTranspiledLangEndCPP = ""
keyWordCodeInTheTranspiledLangStartPY = ""
keyWordCodeInTheTranspiledLangEndPY = ""
keyWordCodeInTheTranspiledLangStartJS = ""
keyWordCodeInTheTranspiledLangEndJS = ""
keyWordCodeInTheTranspiledLangStartGO = ""
keyWordCodeInTheTranspiledLangEndGO = ""
keyWordCodeInTheTranspiledLangStartLUA = ""
keyWordCodeInTheTranspiledLangEndLUA = ""
keyWordCodeInTheTranspiledLangStartCS = ""
keyWordCodeInTheTranspiledLangEndCS = ""
keyWordCodeInTheTranspiledLangStartJAVA = ""
keyWordCodeInTheTranspiledLangEndJAVA = ""
keyWordCodeInTheTranspiledLangStartKT = ""
keyWordCodeInTheTranspiledLangEndKT = ""
keyWordCodeInTheTranspiledLangStartRB = ""
keyWordCodeInTheTranspiledLangEndRB = ""
keyWordCodeInTheTranspiledLangStartNIM = ""
keyWordCodeInTheTranspiledLangEndNIM = ""
keyWordCodeInTheTranspiledLangStartAHK = ""
keyWordCodeInTheTranspiledLangEndAHK = ""
keyWordCodeInTheTranspiledLangStartSWIFT = ""
keyWordCodeInTheTranspiledLangEndSWIFT = ""
keyWordCodeInTheTranspiledLangStartDART = ""
keyWordCodeInTheTranspiledLangEndDART = ""
keyWordCodeInTheTranspiledLangStartTS = ""
keyWordCodeInTheTranspiledLangEndTS = ""
keyWordCodeInTheTranspiledLangStartSCALA = ""
keyWordCodeInTheTranspiledLangEndSCALA = ""
keyWordCodeInTheTranspiledLangStartGROOVY = ""
keyWordCodeInTheTranspiledLangEndGROOVY = ""
keyWordCodeInTheTranspiledLangStartHTVM = ""
keyWordCodeInTheTranspiledLangEndHTVM = ""
keyWordCodeInHTVMstart = ""
keyWordCodeInHTVMend = ""
keyWordCodeInOtherHTVMsyntaxStart = ""
keyWordCodeInOtherHTVMsyntaxEnd = ""
keyWordCurlyBraceOpen = ""
keyWordCurlyBraceClose = ""
keyWordNull = ""
keyWordTrue = ""
keyWordFalse = ""
keyWordVoid = ""
keyWordDouble = ""
keyWordChar = ""
keyWordUint8 = ""
keyWordUint16 = ""
keyWordUint32 = ""
keyWordUint64 = ""
keyWordINT = ""
keyWordSTR = ""
keyWordBOOL = ""
keyWordFLOAT = ""
keyWordINT8 = ""
keyWordINT16 = ""
keyWordINT32 = ""
keyWordINT64 = ""
keyWordIF = ""
keyWordElseIf = ""
keyWordElse = ""
keyWordSwitch = ""
keyWordSwitchCase = ""
keyWordSwitchDefault = ""
keyWordWhileLoop = ""
keyWordForLoop = ""
keyWordLoopInfinite = ""
keyWordLoop = ""
keyWordLoopParse = ""
keyWordContinue = ""
keyWordBreak = ""
keyWordFunc = ""
keyWordAwait = ""
keyWordAsync = ""
keyWordThrow = ""
keyWordErrorMsg = ""
keyWordTry = ""
keyWordCatch = ""
keyWordFinally = ""
keyWordReturnStatement = ""
keyWordArrayAppend = ""
keyWordArrayPop = ""
keyWordArraySize = ""
keyWordArrayInsert = ""
keyWordArrayRemove = ""
keyWordArrayIndexOf = ""
keyWordArrayDefinition = ""
keyWordArrayOfIntegersDefinition = ""
keyWordArrayOfStringsDefinition = ""
keyWordArrayOfFloatingPointNumbersDefinition = ""
keyWordArrayOfBooleansDefinition = ""
keyWordJavaScriptVar = ""
keyWordJavaScriptLet = ""
keyWordJavaScriptConst = ""
keyWordEnd = ""
keyWordGlobal = ""
keyWordComment = ""
keyWordCommentOpenMultiLine = ""
keyWordCommentCloseMultiLine = ""
keyWordEscpaeChar = ""
keyWordMainLabel = ""
keyWordConcat = ""
keyWordAdd = ""
keyWordSub = ""
keyWordMul = ""
keyWordDiv = ""
keyWordMod = ""
keyWordExp = ""
keyWordEqual = ""
keyWordStrictEqual = ""
keyWordNotEqual = ""
keyWordGreater = ""
keyWordLess = ""
keyWordGreaterEqual = ""
keyWordLessEqual = ""
keyWordAnd = ""
keyWordOr = ""
keyWordNot = ""
keyWordBitAnd = ""
keyWordBitOr = ""
keyWordBitXor = ""
keyWordBitNot = ""
keyWordShiftLeft = ""
keyWordShiftRight = ""
keyWordShiftUnsignedRight = ""
keyWordAssign = ""
keyWordAssignAdd = ""
keyWordAssignConcat = ""
keyWordAssignSub = ""
keyWordAssignMul = ""
keyWordAssignDiv = ""
keyWordAssignMod = ""
keyWordAssignShiftLeft = ""
keyWordAssignShiftRight = ""
keyWordAssignBitAnd = ""
keyWordAssignBitOr = ""
keyWordAssignBitXor = ""
keyWordTernary1 = ""
keyWordTernary2 = ""
keyWordInc = ""
keyWordDec = ""
AHKlikeLoopsIndexedAt = ""
keyWordAIndex = ""
keyWordALoopField = ""
keyWordAllianceEndExtraInfo = ""
keyWordCrewEndExtraInfo = ""
keyWordMethodEndExtraInfo = ""
keyWordDefObjEndExtraInfo = ""
keyWordIFEndExtraInfo = ""
keyWordElseIfEndExtraInfo = ""
keyWordElseEndExtraInfo = ""
keyWordSwitchEndExtraInfo = ""
keyWordSwitchCaseEndExtraInfo = ""
keyWordWhileLoopEndExtraInfo = ""
keyWordForLoopEndExtraInfo = ""
keyWordLoopInfiniteEndExtraInfo = ""
keyWordLoopEndExtraInfo = ""
keyWordLoopParseEndExtraInfo = ""
keyWordFuncEndExtraInfo = ""
keyWordTryEndExtraInfo = ""
keyWordCatchEndExtraInfo = ""
keyWordFinallyEndExtraInfo = ""
useFuncKeyWord = ""
useCurlyBraces = ""
useEnd = ""
useEndExtraInfo = ""
useSemicolon = ""
theSemicolon = ""
theColon = ""
useParentheses = ""
usePrefixTypeForTypeDefinition = ""
usePostfixTypeForTypeDefinition = ""
usePythonicColonSyntax = ""
useInJavaScriptAlwaysUseVar = ""
useJavaScriptInAfullHTMLfile = ""
useJavaScriptAmainFuncDef = ""
useJavaScriptAllFuncsAreAsync = ""
useJavaScriptAlwaysTripleEqual = ""
out_KeyWordsCommands = None
outTrimCode = None
htCode = None
outVarOperator = ""
lineDone = 0
areWeInAFuncFromInstructions = 0
areWeInAFuncFromInstructionsLineNum = 0
theCppVarForErrors = "jhku-dfsds-ds-d-ffdsf-sdfsfdsedsf"
theJSvarDeclaredVarsBugFix = "|"
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
def KeyWordsCommands(theCodeCommands, mode, keyWordsCommands, langToConvertTo):
    theCodeCommands = StrReplace(theCodeCommands, "%", "")
    if (mode == "check"):
        items1 = LoopParseFunc(keyWordsCommands, "|")
        for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
            items2 = LoopParseFunc(A_LoopField1, ",")
            for A_Index2 , A_LoopField2 in enumerate(items2, start=0):
                if (A_Index2 == 1):
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField2 + ", ")) == StrLower(A_LoopField2 + ", ")):
                        #MsgBox, true
                        return "true"
                if (A_Index2 == 1):
                    if (theCodeCommands == A_LoopField2):
                        #MsgBox, true
                        return "true"
        #MsgBox, false
        return "false"
    AIndex = 0
    if (mode == "transpile"):
        keyWordsCommandsNumLine = 1
        items3 = LoopParseFunc(keyWordsCommands, "|")
        for A_Index3 , A_LoopField3 in enumerate(items3, start=0):
            AIndex = A_Index3
            items4 = LoopParseFunc(A_LoopField3, ",")
            for A_Index4 , A_LoopField4 in enumerate(items4, start=0):
                if (A_Index4 == 1):
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField4 + ", ")) == StrLower(A_LoopField4 + ", ")):
                        #MsgBox, true
                        keyWordsCommandsNumLine = AIndex
                        break
                if (A_Index4 == 1):
                    #MsgBox, %theCodeCommands% = %A_LoopField4%
                    if (theCodeCommands == A_LoopField4):
                        #MsgBox, true
                        keyWordsCommandsNumLine = AIndex
                        break
        outConstuctTheOutFromTheCommands = ""
        outConstuctTheOutFromTheCommandsFucnName = ""
        outConstuctTheOutFromTheCommandsParams = ""
        outConstuctTheOutFromTheCommandsOutVar = ""
        outConstuctTheOutFromTheCommandsInVar = ""
        theCodeCommandNum = 1
        outConstuctTheOutFromTheCommandsLineTranspile = 0
        outConstuctTheOutFromTheCommandsLineTranspileText = ""
        semicolon = ""
        if (langToConvertTo != "py"):
            semicolon = ";"
        theCodeCommand = []
        theCodeCommands = Trim(theCodeCommands)
        items5 = LoopParseFunc(theCodeCommands, ",")
        for A_Index5 , A_LoopField5 in enumerate(items5, start=0):
            theCodeCommand.append(Trim(A_LoopField5))
            #MsgBox, % A_LoopField5
        items6 = LoopParseFunc(keyWordsCommands, "|")
        for A_Index6 , A_LoopField6 in enumerate(items6, start=0):
            if (keyWordsCommandsNumLine == A_Index6):
                #MsgBox, % A_LoopField6
                items7 = LoopParseFunc(A_LoopField6, ",")
                for A_Index7 , A_LoopField7 in enumerate(items7, start=0):
                    if (A_Index7 == 1):
                        outConstuctTheOutFromTheCommandsFucnName = A_LoopField7
                    elif (A_Index7 == 2):
                        #MsgBox, % A_LoopField7
                        if (A_LoopField7 == "lineTranspile"):
                            outConstuctTheOutFromTheCommandsLineTranspile = 1
                        if (A_LoopField7 == "OUTVAR"):
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum]
                        elif (A_LoopField7 == "INOUTVAR"):
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum]
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum]
                        elif (A_LoopField7 == "INVAR"):
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum]
                        else:
                            if (InStr(A_LoopField7, Chr(39))):
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", "
                            else:
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", "
                    elif (A_Index7 == 3):
                        if (outConstuctTheOutFromTheCommandsLineTranspile == 1):
                            outConstuctTheOutFromTheCommandsLineTranspileText = A_LoopField7
                        if (A_LoopField7 == "INVAR"):
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum]
                        else:
                            if (InStr(A_LoopField7, Chr(39))):
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", "
                            else:
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", "
                    else:
                        #MsgBox, % theCodeCommand[theCodeCommandNum]
                        if (InStr(A_LoopField7, Chr(39))):
                            if (Trim(theCodeCommand[theCodeCommandNum]) != ""):
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", "
                        else:
                            if (Trim(theCodeCommand[theCodeCommandNum]) != ""):
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", "
                    theCodeCommandNum = theCodeCommandNum + 1
                break
        outConstuctTheOutFromTheCommandsParams = StringTrimRight(outConstuctTheOutFromTheCommandsParams, 2)
        if (outConstuctTheOutFromTheCommandsOutVar != ""):
            if (outConstuctTheOutFromTheCommandsParams == ""):
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " = " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ")" + semicolon
            else:
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " = " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ", " + outConstuctTheOutFromTheCommandsParams + ")" + semicolon
        if (outConstuctTheOutFromTheCommandsOutVar == ""):
            if (outConstuctTheOutFromTheCommandsParams == ""):
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ")" + semicolon
            else:
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ", " + outConstuctTheOutFromTheCommandsParams + ")" + semicolon
        if (outConstuctTheOutFromTheCommandsLineTranspile == 1):
            outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsLineTranspileText
        outConstuctTheOutFromTheCommands = StrReplace(outConstuctTheOutFromTheCommands, "(, ", "( ")
        outConstuctTheOutFromTheCommands = StrReplace(outConstuctTheOutFromTheCommands, "(,", "(")
        return outConstuctTheOutFromTheCommands
    return "false"
def HTVMmatchStrRrplace(line, matchString, replaceString):
    lineOut = ""
    if (not InStr(line, matchString)):
        return line
    allDelimiters = " ()[].,;:'!&|=<>+-*/^%~" + Chr(34)
    lineArr = []
    items8 = LoopParseFunc(line)
    for A_Index8 , A_LoopField8 in enumerate(items8, start=0):
        lineArr.append(A_LoopField8)
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
    for A_Index9 in range(0, len(lineArr) + 0):
        char1 = ""
        char2 = ""
        char3 = ""
        char4 = ""
        isMatch = 0
        if (A_Index9 != 0):
            isStart = 0
        sildingLine = ""
        for A_Index10 in range(0, matchStringLEN + 0):
            if (A_Index10 + i1 <= len(lineArr) - 1):
                sildingLine += lineArr[A_Index10 + i1]
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
                for A_Index11 in range(0, len(allPosForReplacing) + 0):
                    if (i1 + 1 != allPosForReplacing[A_Index11]):
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
        for A_Index12 in range(0, len(allPosForReplacing) + 0):
            if (A_Index12 == 0):
                currentPos = allPosForReplacing[A_Index12]
            else:
                currentPos = allPosForReplacing[A_Index12] - (matchStringLEN - replaceStringLEN)
            onceEnd = 0
            items13 = LoopParseFunc(lineOut)
            for A_Index13 , A_LoopField13 in enumerate(items13, start=0):
                if (A_Index13 + 2 > currentPos and A_Index13 + 1 < currentPos + matchStringLEN):
                    onceEnd = onceEnd + 1
                    #print("DDDDDDDDDDD" . STR(A_Index13))
                    if (onceEnd == 1):
                        lineTEMP += replaceString
                else:
                    lineTEMP += A_LoopField13
            lineOut = lineTEMP
            lineTEMP = ""
            #print(lineTEMP)
            l2 = l2 + 1
    else:
        return line
    return lineOut
def SubStrLastChars(text, numOfChars):
    LastOut = ""
    NumOfChars = 0
    items14 = LoopParseFunc(text)
    for A_Index14 , A_LoopField14 in enumerate(items14, start=0):
        NumOfChars = NumOfChars + 1
    for A_Index15 in range(0, numOfChars + 0):
        NumOfChars = NumOfChars - 1
    items16 = LoopParseFunc(text)
    for A_Index16 , A_LoopField16 in enumerate(items16, start=0):
        if (A_Index16 >= NumOfChars):
            LastOut += A_LoopField16
    return LastOut
def ExtractDigits(inputString):
    digits = ""
    items17 = LoopParseFunc(inputString)
    for A_Index17 , A_LoopField17 in enumerate(items17, start=0):
        if (RegExMatch(A_LoopField17, "\\d")):
            digits += A_LoopField17
    return digits
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# Helper function to create spaces
def spaces(n):
    s = ""
    if (n != 0):
        for A_Index18 in range(0, n + 0):
            s += " "
    return s
# Define the function to check odd spaces at the beginning
def CheckOddLeadingSpaces(string123):
    # Initialize a variable to count the spaces
    spaceCount = 0
    # Loop through the string one character at a time
    items19 = LoopParseFunc(string123)
    for A_Index19 , A_LoopField19 in enumerate(items19, start=0):
        # Check if the current character is a space
        if (A_LoopField19 == Chr(32)):
            spaceCount = spaceCount + 1
        else:
            # When we hit a non-space character, break the loop
            break
    # Return true if the number of spaces is odd, false otherwise
    sdsfawasd = STR(Mod(spaceCount, 2) == 1)
    #MsgBox, % sdsfawasd
    return sdsfawasd
def LTrim(input):
    result = ""
    foundNonSpace = False
    items20 = LoopParseFunc(input)
    for A_Index20 , A_LoopField20 in enumerate(items20, start=0):
        if (A_LoopField20 != " " or foundNonSpace):
            result += A_LoopField20
            foundNonSpace = True
    return result
def getLastChar(strippedString):
    lastChar = None
    items21 = LoopParseFunc(strippedString)
    for A_Index21 , A_LoopField21 in enumerate(items21, start=0):
        lastChar = A_LoopField21
    return lastChar
def AddCurlyBraces(pythonCode):
    pythonCode = StrReplace(pythonCode, Chr(9), "    ")
    result = ""
    indentLevel = 0
    indent = 0
    line = 0
    stripped = 0
    items22 = LoopParseFunc(pythonCode, "\n", "\r")
    for A_Index22 , A_LoopField22 in enumerate(items22, start=0):
        line = A_LoopField22
        stripped = Trim(line)
        if (stripped == ""):
            result += line + "\n"
            continue
        # Count leading spaces
        indent = StrLen(line) - StrLen(LTrim(line))
        #MsgBox, % indent
        # Close braces for unindents
        for A_Index23 , value in enumerate(iter(int, 1), start=0):
            if (indentLevel <= indent):
                break
            indentLevel -= 4
            result += spaces(indentLevel) + "}\n"
        # Add opening brace for new blocks
        if (getLastChar(stripped) == ":" and SubStr(StrLower(Trim(A_LoopField22)), 1, StrLen(StrLower(keyWordComment))) != StrLower(keyWordComment)):
            result += SubStr(line, 1, -1) + " {\n"
            indentLevel += 4
        else:
            result += line + "\n"
    # Close any remaining open braces
    for A_Index24 , value in enumerate(iter(int, 1), start=0):
        if (indentLevel <= 0):
            break
        indentLevel -= 4
        result += spaces(indentLevel) + "}\n"
    return result
def RepeatSpaces(count):
    spaces = ""
    for A_Index25 in range(0, count + 0):
        spaces += Chr(32)
    return spaces
def indent_nested_curly_braces(input_string, modeCurlyBracesOn):
    indent_size = 4
    current_indent = 0
    result = ""
    trimmed_line = ""
    resultOut = ""
    #MsgBox, % input_string
    items26 = LoopParseFunc(input_string, "\n", "\r")
    for A_Index26 , A_LoopField26 in enumerate(items26, start=0):
        trimmed_line = Trim(A_LoopField26)
        if (trimmed_line == Chr(123)):
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n"
            current_indent = current_indent + indent_size
        elif (trimmed_line == Chr(125)):
            current_indent = current_indent - indent_size
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n"
        else:
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n"
    if (modeCurlyBracesOn == 0):
        resultOut = ""
        items27 = LoopParseFunc(result, "\n", "\r")
        for A_Index27 , A_LoopField27 in enumerate(items27, start=0):
            if (Trim(A_LoopField27) != "{" and Trim(A_LoopField27) != "}"):
                resultOut += A_LoopField27 + "\n"
        result = StringTrimRight(resultOut, 1)
    else:
        # format curly braces in a K&R style
        lookIntoFurture = []
        items28 = LoopParseFunc(result, "\n", "\r")
        for A_Index28 , A_LoopField28 in enumerate(items28, start=0):
            lookIntoFurture.append(Trim(A_LoopField28))
        lookIntoFurture.append(" ")
        resultOut = ""
        skipNext = 0
        items29 = LoopParseFunc(result, "\n", "\r")
        for A_Index29 , A_LoopField29 in enumerate(items29, start=0):
            skipNext = skipNext - 1
            if (skipNext <= 0):
                skipNext = 0
            if (Trim(lookIntoFurture[A_Index29 + 1]) == "{"):
                resultOut += A_LoopField29 + " {\n"
                skipNext = 2
            if (skipNext == 0):
                resultOut += A_LoopField29 + "\n"
        result = StringTrimRight(resultOut, 1)
        lookIntoFurture2 = []
        items30 = LoopParseFunc(result, "\n", "\r")
        for A_Index30 , A_LoopField30 in enumerate(items30, start=0):
            lookIntoFurture2.append(Trim(A_LoopField30))
        lookIntoFurture2.append(" ")
        resultOut = ""
        skipNext = 0
        addSpacesAtTheBegginig = None
        items31 = LoopParseFunc(result, "\n", "\r")
        for A_Index31 , A_LoopField31 in enumerate(items31, start=0):
            skipNext = skipNext - 1
            if (skipNext <= 0):
                skipNext = 0
            if (Trim(A_LoopField31) == "}" and Trim(lookIntoFurture2[A_Index31 + 1]) == "else {"):
                skipNext = 2
                addSpacesAtTheBegginig = ""
                items32 = LoopParseFunc(A_LoopField31)
                for A_Index32 , A_LoopField32 in enumerate(items32, start=0):
                    if (A_LoopField32 == " "):
                        if (A_LoopField32 != " "):
                            break
                        addSpacesAtTheBegginig += A_LoopField32
                resultOut += addSpacesAtTheBegginig + "} else {\n"
            if (skipNext == 0):
                resultOut += A_LoopField31 + "\n"
        result = StringTrimRight(resultOut, 1)
    resultOut = ""
    ALoopField = None
    items33 = LoopParseFunc(result, "\n", "\r")
    for A_Index33 , A_LoopField33 in enumerate(items33, start=0):
        if (CheckOddLeadingSpaces(A_LoopField33) == "1"):
            ALoopField = StringTrimLeft(A_LoopField33, 1)
            resultOut += ALoopField + "\n"
        else:
            resultOut += A_LoopField33 + "\n"
    result = StringTrimRight(resultOut, 1)
    # Return the result
    return result
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# path.path.path:propName1[str],propName2[bool],propName3[str array]|path.path.path:propName1[str],propName2[bool],propName3[str array]
OSPstrArrayStrALLobjInOSP = ""
HoldOSPdethodNamePath = ""
def findTypeOfOSPprop(fullARRAYstr, FromPath):
    outType = ""
    # if the fullARRAYstr is in this format
    # path.path.path:propName1[str],propName2[bool],propName3[str array]|path.path.path:propName1[str],propName2[bool],propName3[str array]
    outFormat = ""
    outFormatHELP1 = ""
    outFormatHELP2 = ""
    items34 = LoopParseFunc(fullARRAYstr, "|")
    for A_Index34 , A_LoopField34 in enumerate(items34, start=0):
        if (Trim(A_LoopField34) != ""):
            outFormatHELP1 = StrSplit(A_LoopField34, ":", 1)
            outFormatHELP2 = StrSplit(A_LoopField34, ":", 2)
            items35 = LoopParseFunc(outFormatHELP2, ",")
            for A_Index35 , A_LoopField35 in enumerate(items35, start=0):
                outFormat += outFormatHELP1 + "." + A_LoopField35 + "|"
    outFormat = StringTrimRight(outFormat, 1)
    items36 = LoopParseFunc(outFormat, "|")
    for A_Index36 , A_LoopField36 in enumerate(items36, start=0):
        if (Trim(A_LoopField36) != ""):
            if (StrSplit(Trim(A_LoopField36), "[", 1) == Trim(FromPath)):
                outType = StrSplit(Trim(A_LoopField36), "[", 2)
                outType = StringTrimRight(outType, 1)
                break
    if (outType == "vector<int>"):
        outType = "std::vector<int>&"
    elif (outType == "vector<string>"):
        outType = "std::vector<std::string>&"
    elif (outType == "vector<string>"):
        outType = "std::vector<std::string>&"
    elif (outType == "vector<float>"):
        outType = "std::vector<float>&"
    elif (outType == "vector<bool>"):
        outType = "std::vector<bool>&"
    elif (outType == Trim(keyWordINT)):
        outType = "int"
    elif (outType == Trim(keyWordSTR)):
        outType = "std::string"
    elif (outType == Trim(keyWordFLOAT)):
        outType = "float"
    elif (outType == Trim(keyWordBOOL)):
        outType = "bool"
    elif (outType == Trim(keyWordINT8)):
        outType = "int8_t"
    elif (outType == Trim(keyWordINT16)):
        outType = "int16_t"
    elif (outType == Trim(keyWordINT32)):
        outType = "int32_t"
    elif (outType == Trim(keyWordINT64)):
        outType = "int64_t"
    return outType
def REMOVELastSTRfromDOT(THESTR):
    THESTRout = ""
    if (Trim(THESTR) == ""):
        return ""
    count12345 = 0
    items37 = LoopParseFunc(THESTR, ".")
    for A_Index37 , A_LoopField37 in enumerate(items37, start=0):
        count12345 = count12345 + 1
    items38 = LoopParseFunc(THESTR, ".")
    for A_Index38 , A_LoopField38 in enumerate(items38, start=0):
        if (count12345 == A_Index38):
            break
        else:
            THESTRout += Trim(A_LoopField38) + "."
    THESTRout = StringTrimRight(THESTRout, 1)
    return THESTRout
#;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;
def replaceTheOSPpathsPY_JS(theSTR123, ALoopFieldIN):
    if (Trim(theSTR123) == ""):
        return ""
    if (Trim(ALoopFieldIN) == ""):
        return ""
    type = ""
    theSTR123out = ""
    ALoopField = ""
    ALoopField1 = ""
    ALoopField11 = ""
    if (InStr(ALoopFieldIN, "[")):
        # ALoopFieldIN
        # animalsKingdom.animals.Dog.typeOf2[2]
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1)
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 1)
        ALoopField11 = StrSplit(Trim(ALoopFieldIN), "[", 2)
        ALoopField1 = REMOVELastSTRfromDOT(ALoopField1) + "[" + ALoopField11
        # REMOVELastSTRfromDOT(param1)
        theSTR123 = StrReplace(theSTR123, Trim(ALoopField), "OSPHTVMOSP_" + StrReplace(ALoopField1, ".", "_"))
    else:
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1)
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 2)
        ALoopField1 = REMOVELastSTRfromDOT(StrSplit(Trim(ALoopFieldIN), "]", 1))
        ALoopField1 = "[" + Trim(StrSplit(ALoopField1, "[", 2)) + "]"
        theSTR123 = StrReplace(theSTR123, Trim(ALoopFieldIN), "OSPHTVMOSP_" + StrReplace(ALoopFieldIN, ".", "_"))
    #this__OSP__this
    theSTR123 = RegExReplace(theSTR123, "\\bthis\\b", "this__OSP__this[0]")
    theSTR123 = StrReplace(theSTR123, "OSPHTVMOSP_OSPHTVMOSP_", "OSPHTVMOSP_")
    return theSTR123
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
def replaceTheOSPpathsLEFT(theSTR123, ALoopFieldIN):
    if (Trim(theSTR123) == ""):
        return ""
    if (Trim(ALoopFieldIN) == ""):
        return ""
    type = ""
    theSTR123out = ""
    ALoopField = ""
    ALoopField1 = ""
    ALoopField11 = ""
    if (InStr(ALoopFieldIN, "[")):
        # ALoopFieldIN
        # animalsKingdom.animals.Dog.typeOf2[2]
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1)
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 1)
        ALoopField11 = StrSplit(Trim(ALoopFieldIN), "[", 2)
        ALoopField1 = REMOVELastSTRfromDOT(ALoopField1) + "[" + ALoopField11
        # REMOVELastSTRfromDOT(param1)
        theSTR123 = StrReplace(theSTR123, Trim(ALoopField), "OSPHTVMOSP_" + StrReplace(ALoopField1, ".", "_"))
    else:
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1)
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 2)
        ALoopField1 = REMOVELastSTRfromDOT(StrSplit(Trim(ALoopFieldIN), "]", 1))
        ALoopField1 = "[" + Trim(StrSplit(ALoopField1, "[", 2)) + "]"
        theSTR123 = StrReplace(theSTR123, Trim(ALoopFieldIN), "OSPHTVMOSP_" + StrReplace(ALoopFieldIN, ".", "_"))
    #this__OSP__this
    theSTR123 = RegExReplace(theSTR123, "\\bthis\\b", "std::any_cast<std::string>((*this__OSP__this)[0])")
    theSTR123 = StrReplace(theSTR123, "OSPHTVMOSP_OSPHTVMOSP_", "OSPHTVMOSP_")
    return theSTR123
def replaceTheOSPpathsRIGHT(theSTR123, ALoopFieldIN):
    if (Trim(theSTR123) == ""):
        return ""
    if (Trim(ALoopFieldIN) == ""):
        return ""
    type = ""
    theSTR123out = ""
    ALoopField = ""
    ALoopField1 = ""
    ALoopField11 = ""
    if (InStr(ALoopFieldIN, "[")):
        # ALoopFieldIN
        # animalsKingdom.animals.Dog.typeOf2[2]
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1)
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 1)
        ALoopField11 = StrSplit(Trim(ALoopFieldIN), "[", 2)
        ALoopField1 = REMOVELastSTRfromDOT(ALoopField1) + "[" + ALoopField11
        # REMOVELastSTRfromDOT(param1)
        type = findTypeOfOSPprop(OSPstrArrayStrALLobjInOSP, ALoopField)
        #MsgBox, % type
        theSTR123 = StrReplace(theSTR123, Trim(ALoopField), "std::any_cast<" + type + ">(OSPHTVMOSP_" + StrReplace(ALoopField1, ".", "_") + ")")
    else:
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1)
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 2)
        ALoopField1 = REMOVELastSTRfromDOT(StrSplit(Trim(ALoopFieldIN), "]", 1))
        ALoopField1 = "[" + Trim(StrSplit(ALoopField1, "[", 2)) + "]"
        theSTR123 = StrReplace(theSTR123, Trim(ALoopFieldIN), "OSPHTVMOSP_" + StrReplace(ALoopFieldIN, ".", "_"))
    #this__OSP__this
    theSTR123 = RegExReplace(theSTR123, "\\bthis\\b", "std::any_cast<std::string>((*this__OSP__this)[0])")
    theSTR123 = StrReplace(theSTR123, "OSPHTVMOSP_OSPHTVMOSP_", "OSPHTVMOSP_")
    return theSTR123
def CheckStringPosition(text, target, reference):
    posReference = SubStr(text, 1, StrLen(reference))
    posTarget = SubStr(text, 1, StrLen(target))
    # Check if both strings are found (not using InStr)
    if (posReference != "" and posTarget != ""):
        # Manually find the positions of the target and reference
        posTarget = RegExMatch(text, target)
        posReference = RegExMatch(text, reference)
        # Compare positions of target and reference
        if (posTarget < posReference):
            return "left"
        elif (posTarget > posReference):
            return "not left"
        else:
            return "uuh"
    else:
        return "One or both strings not found."
    return "huh"
def getIndexOfTheStrArrayStrOST(ALoopField, theSringOSPlineARRAYstrstrSTR):
    items39 = LoopParseFunc(theSringOSPlineARRAYstrstrSTR, "|")
    for A_Index39 , A_LoopField39 in enumerate(items39, start=0):
        if (Trim(StrSplit(A_LoopField39, ":", 1)) == Trim(ALoopField)):
            return STR(A_Index39)
    return "0"
def parserOSPgloabl(theSringOSPline, str123):
    str_1 = ""
    str_2 = ""
    str_3 = ""
    str_4 = ""
    str_5 = ""
    str_6 = ""
    HELPHoldOSPdethodNamePath = ""
    HELPHoldOSPdethodNamePath = StringTrimRight(HoldOSPdethodNamePath, 1)
    items40 = LoopParseFunc(theSringOSPline, "|")
    for A_Index40 , A_LoopField40 in enumerate(items40, start=0):
        str_1 += Trim(StrSplit(A_LoopField40, ":", 1)) + "\n"
        str_5 = Trim(StrSplit(A_LoopField40, ":", 1))
        str_6 = Trim(StrSplit(A_LoopField40, ":", 2))
        items41 = LoopParseFunc(str_6, ",")
        for A_Index41 , A_LoopField41 in enumerate(items41, start=0):
            str_1 += str_5 + "." + Trim(StrSplit(A_LoopField41, "[", 1)) + "[" + STR(A_Index41) + "]\n"
    str_1 += StrReplace(HELPHoldOSPdethodNamePath, "|", "\n")
    shortestLine = ""
    currentLine = ""
    currentLength = 0
    minLength = 0
    tempStr = ""
    # Sorting by repeatedly finding and appending the shortest line
    for A_Index42 , value in enumerate(iter(int, 1), start=0):
        # Initialize variables to track the shortest line in this pass
        shortestLine = ""
        minLength = 999999
        # Find the shortest line in str_1
        items43 = LoopParseFunc(str_1, "\n", "\r")
        for A_Index43 , A_LoopField43 in enumerate(items43, start=0):
            currentLine = A_LoopField43
            currentLength = StrLen(currentLine)
            if (currentLength < minLength):
                minLength = currentLength
                shortestLine = currentLine
        # If no shortest line is found, break (str_1 is empty)
        if (shortestLine == ""):
            break
        # Add the shortest line to the sorted result
        str_2 += shortestLine + "\n"
        # Rebuild str_1 without the shortest line
        tempStr = ""
        items44 = LoopParseFunc(str_1, "\n", "\r")
        for A_Index44 , A_LoopField44 in enumerate(items44, start=0):
            if (A_LoopField44 != shortestLine):
                tempStr += A_LoopField44 + "\n"
        tempStr = StringTrimRight(tempStr, 1)
        str_1 = tempStr
    # Trim the final trailing newline from str_2
    str_2 = StringTrimRight(str_2, 1)
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    # Initialize an empty result for the reversed lines
    reversedStr = ""
    # Count the number of lines
    lineCount = 0
    index = 0
    lineNum = 0
    items45 = LoopParseFunc(str_2, "\n", "\r")
    for A_Index45 , A_LoopField45 in enumerate(items45, start=0):
        lineCount = lineCount + 1
    # Reverse the order by re-parsing and appending lines in reverse order
    for A_Index46 in range(0, lineCount + 0):
        # Inner loop to find the (lineCount - A_Index46 + 1)-th line
        index = lineCount - A_Index46 + 1
        currentLine = ""
        lineNum = 0
        items47 = LoopParseFunc(str_2, "\n", "\r")
        for A_Index47 , A_LoopField47 in enumerate(items47, start=0):
            lineNum = lineNum + 1
            if (lineNum == index):
                currentLine = A_LoopField47
                break
        # Append the line in reverse order
        reversedStr += currentLine + "\n"
    # Trim the final trailing newline
    str_2 = StringTrimRight(reversedStr, 1)
    # Display the sorted result
    #MsgBox, % str_2
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #CheckStringPosition(text, target, reference)
    ALoopField = ""
    ALoopField1 = ""
    items48 = LoopParseFunc(str_2, "\n", "\r")
    for A_Index48 , A_LoopField48 in enumerate(items48, start=0):
        if (SubStr(A_LoopField48, 1, StrLen(keyWordFunc)) != keyWordFunc):
            if (langToConvertTo == "cpp"):
                if (Trim(A_LoopField48) != ""):
                    if (InStr(str123, " += ")):
                        str6 = " += "
                        str1 = ""
                        str2 = ""
                        str3 = ""
                        str4 = ""
                        str5 = ""
                        str1 = Trim(StrSplit(str123, str6, 1))
                        str2 = Trim(StrSplit(str123, str6, 2))
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48))
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48))
                        str5 = str3 + str6 + str4
                        str123 = Trim(str5)
                    elif (InStr(str123, " = ")):
                        str6 = " = "
                        str1 = ""
                        str2 = ""
                        str3 = ""
                        str4 = ""
                        str5 = ""
                        str1 = Trim(StrSplit(str123, str6, 1))
                        str2 = Trim(StrSplit(str123, str6, 2))
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48))
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48))
                        str5 = str3 + str6 + str4
                        str123 = Trim(str5)
                    elif (InStr(str123, " -= ")):
                        str6 = " -= "
                        str1 = ""
                        str2 = ""
                        str3 = ""
                        str4 = ""
                        str5 = ""
                        str1 = Trim(StrSplit(str123, str6, 1))
                        str2 = Trim(StrSplit(str123, str6, 2))
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48))
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48))
                        str5 = str3 + str6 + str4
                        str123 = Trim(str5)
                    elif (InStr(str123, " *= ")):
                        str6 = " *= "
                        str1 = ""
                        str2 = ""
                        str3 = ""
                        str4 = ""
                        str5 = ""
                        str1 = Trim(StrSplit(str123, str6, 1))
                        str2 = Trim(StrSplit(str123, str6, 2))
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48))
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48))
                        str5 = str3 + str6 + str4
                        str123 = Trim(str5)
                    elif (InStr(str123, " /= ")):
                        str6 = " /= "
                        str1 = ""
                        str2 = ""
                        str3 = ""
                        str4 = ""
                        str5 = ""
                        str1 = Trim(StrSplit(str123, str6, 1))
                        str2 = Trim(StrSplit(str123, str6, 2))
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField48))
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField48))
                        str5 = str3 + str6 + str4
                        str123 = Trim(str5)
                    else:
                        str123 = replaceTheOSPpathsRIGHT(str123, A_LoopField48)
                    #;;;;
            else:
                if (Trim(A_LoopField48) != ""):
                    str123 = replaceTheOSPpathsPY_JS(str123, A_LoopField48)
    return str123
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
def compiler(htCode, instructionFile, mode, langToConvertToParam = ""):
    extraCodeReturned = ""
    allInstructionFile = Trim(FileRead(instructionFile))
    items49 = LoopParseFunc(allInstructionFile, "\n", "\r")
    for A_Index49 , A_LoopField49 in enumerate(items49, start=0):
        if (A_Index49 == 0):
            langToConvertTo = Trim(A_LoopField49)
        if (A_Index49 == 1):
            langFileExtension = Trim(A_LoopField49)
        if (A_Index49 == 2):
            commands = Trim(A_LoopField49)
        if (A_Index49 == 3):
            keyWordAlliance = Trim(A_LoopField49)
        if (A_Index49 == 4):
            keyWordCrew = Trim(A_LoopField49)
        if (A_Index49 == 5):
            keyWordMethod = Trim(A_LoopField49)
        if (A_Index49 == 6):
            keyWordDefObj = Trim(A_LoopField49)
        if (A_Index49 == 7):
            keyWordPorp = Trim(A_LoopField49)
        if (A_Index49 == 8):
            keyWordThis = Trim(A_LoopField49)
        if (A_Index49 == 9):
            keyWordInclude = Trim(A_LoopField49)
        if (A_Index49 == 10):
            keyWordIncludeInTheTranspiledLang = Trim(A_LoopField49)
        if (A_Index49 == 11):
            keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField49)
        if (A_Index49 == 12):
            keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField49)
        if (A_Index49 == 13):
            keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField49)
        if (A_Index49 == 14):
            keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField49)
        if (A_Index49 == 15):
            keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField49)
        if (A_Index49 == 16):
            keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField49)
        if (A_Index49 == 17):
            keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField49)
        if (A_Index49 == 18):
            keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField49)
        if (A_Index49 == 19):
            keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField49)
        if (A_Index49 == 20):
            keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField49)
        if (A_Index49 == 21):
            keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField49)
        if (A_Index49 == 22):
            keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField49)
        if (A_Index49 == 23):
            keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField49)
        if (A_Index49 == 24):
            keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField49)
        if (A_Index49 == 25):
            keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField49)
        if (A_Index49 == 26):
            keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField49)
        if (A_Index49 == 27):
            keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField49)
        if (A_Index49 == 28):
            keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField49)
        if (A_Index49 == 29):
            keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField49)
        if (A_Index49 == 30):
            keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField49)
        if (A_Index49 == 31):
            keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField49)
        if (A_Index49 == 32):
            keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField49)
        if (A_Index49 == 33):
            keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField49)
        if (A_Index49 == 34):
            keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField49)
        if (A_Index49 == 35):
            keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField49)
        if (A_Index49 == 36):
            keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField49)
        if (A_Index49 == 37):
            keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField49)
        if (A_Index49 == 38):
            keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField49)
        if (A_Index49 == 39):
            keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField49)
        if (A_Index49 == 40):
            keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField49)
        if (A_Index49 == 41):
            keyWordCodeInTheTranspiledLangStartSCALA = Trim(A_LoopField49)
        if (A_Index49 == 42):
            keyWordCodeInTheTranspiledLangEndSCALA = Trim(A_LoopField49)
        if (A_Index49 == 43):
            keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField49)
        if (A_Index49 == 44):
            keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField49)
        if (A_Index49 == 45):
            keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField49)
        if (A_Index49 == 46):
            keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField49)
        if (A_Index49 == 47):
            keyWordCodeInHTVMstart = Trim(A_LoopField49)
        if (A_Index49 == 48):
            keyWordCodeInHTVMend = Trim(A_LoopField49)
        if (A_Index49 == 49):
            keyWordCodeInOtherHTVMsyntaxStart = Trim(A_LoopField49)
        if (A_Index49 == 50):
            keyWordCodeInOtherHTVMsyntaxEnd = Trim(A_LoopField49)
        if (A_Index49 == 51):
            keyWordCurlyBraceOpen = Trim(A_LoopField49)
        if (A_Index49 == 52):
            keyWordCurlyBraceClose = Trim(A_LoopField49)
        if (A_Index49 == 53):
            keyWordNull = Trim(A_LoopField49)
        if (A_Index49 == 54):
            keyWordTrue = Trim(A_LoopField49)
        if (A_Index49 == 55):
            keyWordFalse = Trim(A_LoopField49)
        if (A_Index49 == 56):
            keyWordVoid = Trim(A_LoopField49)
        if (A_Index49 == 57):
            keyWordDouble = Trim(A_LoopField49)
        if (A_Index49 == 58):
            keyWordChar = Trim(A_LoopField49)
        if (A_Index49 == 59):
            keyWordUint8 = Trim(A_LoopField49)
        if (A_Index49 == 60):
            keyWordUint16 = Trim(A_LoopField49)
        if (A_Index49 == 61):
            keyWordUint32 = Trim(A_LoopField49)
        if (A_Index49 == 62):
            keyWordUint64 = Trim(A_LoopField49)
        if (A_Index49 == 63):
            keyWordINT = Trim(A_LoopField49)
        if (A_Index49 == 64):
            keyWordSTR = Trim(A_LoopField49)
        if (A_Index49 == 65):
            keyWordBOOL = Trim(A_LoopField49)
        if (A_Index49 == 66):
            keyWordFLOAT = Trim(A_LoopField49)
        if (A_Index49 == 67):
            keyWordINT8 = Trim(A_LoopField49)
        if (A_Index49 == 68):
            keyWordINT16 = Trim(A_LoopField49)
        if (A_Index49 == 69):
            keyWordINT32 = Trim(A_LoopField49)
        if (A_Index49 == 70):
            keyWordINT64 = Trim(A_LoopField49)
        if (A_Index49 == 71):
            keyWordIF = Trim(A_LoopField49)
        if (A_Index49 == 72):
            keyWordElseIf = Trim(A_LoopField49)
        if (A_Index49 == 73):
            keyWordElse = Trim(A_LoopField49)
        if (A_Index49 == 74):
            keyWordSwitch = Trim(A_LoopField49)
        if (A_Index49 == 75):
            keyWordSwitchCase = Trim(A_LoopField49)
        if (A_Index49 == 76):
            keyWordSwitchDefault = Trim(A_LoopField49)
        if (A_Index49 == 77):
            keyWordWhileLoop = Trim(A_LoopField49)
        if (A_Index49 == 78):
            keyWordForLoop = Trim(A_LoopField49)
        if (A_Index49 == 79):
            keyWordLoopInfinite = Trim(A_LoopField49)
        if (A_Index49 == 80):
            keyWordLoop = Trim(A_LoopField49)
        if (A_Index49 == 81):
            keyWordLoopParse = Trim(A_LoopField49)
        if (A_Index49 == 82):
            keyWordContinue = Trim(A_LoopField49)
        if (A_Index49 == 83):
            keyWordBreak = Trim(A_LoopField49)
        if (A_Index49 == 84):
            keyWordFunc = Trim(A_LoopField49)
        if (A_Index49 == 85):
            keyWordAwait = Trim(A_LoopField49)
        if (A_Index49 == 86):
            keyWordAsync = Trim(A_LoopField49)
        if (A_Index49 == 87):
            keyWordThrow = Trim(A_LoopField49)
        if (A_Index49 == 88):
            keyWordErrorMsg = Trim(A_LoopField49)
        if (A_Index49 == 89):
            keyWordTry = Trim(A_LoopField49)
        if (A_Index49 == 90):
            keyWordCatch = Trim(A_LoopField49)
        if (A_Index49 == 91):
            keyWordFinally = Trim(A_LoopField49)
        if (A_Index49 == 92):
            keyWordReturnStatement = Trim(A_LoopField49)
        if (A_Index49 == 93):
            keyWordArrayAppend = Trim(A_LoopField49)
        if (A_Index49 == 94):
            keyWordArrayPop = Trim(A_LoopField49)
        if (A_Index49 == 95):
            keyWordArraySize = Trim(A_LoopField49)
        if (A_Index49 == 96):
            keyWordArrayInsert = Trim(A_LoopField49)
        if (A_Index49 == 97):
            keyWordArrayRemove = Trim(A_LoopField49)
        if (A_Index49 == 98):
            keyWordArrayIndexOf = Trim(A_LoopField49)
        if (A_Index49 == 99):
            keyWordArrayDefinition = Trim(A_LoopField49)
        if (A_Index49 == 100):
            keyWordArrayOfIntegersDefinition = Trim(A_LoopField49)
        if (A_Index49 == 101):
            keyWordArrayOfStringsDefinition = Trim(A_LoopField49)
        if (A_Index49 == 102):
            keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField49)
        if (A_Index49 == 103):
            keyWordArrayOfBooleansDefinition = Trim(A_LoopField49)
        if (A_Index49 == 104):
            keyWordJavaScriptVar = Trim(A_LoopField49)
        if (A_Index49 == 105):
            keyWordJavaScriptLet = Trim(A_LoopField49)
        if (A_Index49 == 106):
            keyWordJavaScriptConst = Trim(A_LoopField49)
        if (A_Index49 == 107):
            keyWordEnd = Trim(A_LoopField49)
        if (A_Index49 == 108):
            keyWordGlobal = Trim(A_LoopField49)
        if (A_Index49 == 109):
            keyWordComment = Trim(A_LoopField49)
        if (A_Index49 == 110):
            keyWordCommentOpenMultiLine = Trim(A_LoopField49)
        if (A_Index49 == 111):
            keyWordCommentCloseMultiLine = Trim(A_LoopField49)
        if (A_Index49 == 112):
            keyWordEscpaeChar = Trim(A_LoopField49)
        if (A_Index49 == 113):
            keyWordMainLabel = Trim(A_LoopField49)
        if (A_Index49 == 114):
            keyWordConcat = Trim(A_LoopField49)
        if (A_Index49 == 115):
            keyWordAdd = Trim(A_LoopField49)
        if (A_Index49 == 116):
            keyWordSub = Trim(A_LoopField49)
        if (A_Index49 == 117):
            keyWordMul = Trim(A_LoopField49)
        if (A_Index49 == 118):
            keyWordDiv = Trim(A_LoopField49)
        if (A_Index49 == 119):
            keyWordMod = Trim(A_LoopField49)
        if (A_Index49 == 120):
            keyWordExp = Trim(A_LoopField49)
        if (A_Index49 == 121):
            keyWordEqual = Trim(A_LoopField49)
        if (A_Index49 == 122):
            keyWordStrictEqual = Trim(A_LoopField49)
        if (A_Index49 == 123):
            keyWordNotEqual = Trim(A_LoopField49)
        if (A_Index49 == 124):
            keyWordGreater = Trim(A_LoopField49)
        if (A_Index49 == 125):
            keyWordLess = Trim(A_LoopField49)
        if (A_Index49 == 126):
            keyWordGreaterEqual = Trim(A_LoopField49)
        if (A_Index49 == 127):
            keyWordLessEqual = Trim(A_LoopField49)
        if (A_Index49 == 128):
            keyWordAnd = Trim(A_LoopField49)
        if (A_Index49 == 129):
            keyWordOr = Trim(A_LoopField49)
        if (A_Index49 == 130):
            keyWordNot = Trim(A_LoopField49)
        if (A_Index49 == 131):
            keyWordBitAnd = Trim(A_LoopField49)
        if (A_Index49 == 132):
            keyWordBitOr = Trim(A_LoopField49)
        if (A_Index49 == 133):
            keyWordBitXor = Trim(A_LoopField49)
        if (A_Index49 == 134):
            keyWordBitNot = Trim(A_LoopField49)
        if (A_Index49 == 135):
            keyWordShiftLeft = Trim(A_LoopField49)
        if (A_Index49 == 136):
            keyWordShiftRight = Trim(A_LoopField49)
        if (A_Index49 == 137):
            keyWordShiftUnsignedRight = Trim(A_LoopField49)
        if (A_Index49 == 138):
            keyWordAssign = Trim(A_LoopField49)
        if (A_Index49 == 139):
            keyWordAssignAdd = Trim(A_LoopField49)
        if (A_Index49 == 140):
            keyWordAssignConcat = Trim(A_LoopField49)
        if (A_Index49 == 141):
            keyWordAssignSub = Trim(A_LoopField49)
        if (A_Index49 == 142):
            keyWordAssignMul = Trim(A_LoopField49)
        if (A_Index49 == 143):
            keyWordAssignDiv = Trim(A_LoopField49)
        if (A_Index49 == 144):
            keyWordAssignMod = Trim(A_LoopField49)
        if (A_Index49 == 145):
            keyWordAssignShiftLeft = Trim(A_LoopField49)
        if (A_Index49 == 146):
            keyWordAssignShiftRight = Trim(A_LoopField49)
        if (A_Index49 == 147):
            keyWordAssignBitAnd = Trim(A_LoopField49)
        if (A_Index49 == 148):
            keyWordAssignBitOr = Trim(A_LoopField49)
        if (A_Index49 == 149):
            keyWordAssignBitXor = Trim(A_LoopField49)
        if (A_Index49 == 150):
            keyWordTernary1 = Trim(A_LoopField49)
        if (A_Index49 == 151):
            keyWordTernary2 = Trim(A_LoopField49)
        if (A_Index49 == 152):
            keyWordInc = Trim(A_LoopField49)
        if (A_Index49 == 153):
            keyWordDec = Trim(A_LoopField49)
        if (A_Index49 == 154):
            AHKlikeLoopsIndexedAt = Trim(A_LoopField49)
        if (A_Index49 == 155):
            keyWordAIndex = Trim(A_LoopField49)
        if (A_Index49 == 156):
            keyWordALoopField = Trim(A_LoopField49)
        if (A_Index49 == 157):
            keyWordAllianceEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 158):
            keyWordCrewEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 159):
            keyWordMethodEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 160):
            keyWordDefObjEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 161):
            keyWordIFEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 162):
            keyWordElseIfEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 163):
            keyWordElseEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 164):
            keyWordSwitchEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 165):
            keyWordSwitchCaseEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 166):
            keyWordWhileLoopEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 167):
            keyWordForLoopEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 168):
            keyWordLoopInfiniteEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 169):
            keyWordLoopEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 170):
            keyWordLoopParseEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 171):
            keyWordFuncEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 172):
            keyWordTryEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 173):
            keyWordCatchEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 174):
            keyWordFinallyEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 175):
            useFuncKeyWord = Trim(A_LoopField49)
        if (A_Index49 == 176):
            useCurlyBraces = Trim(A_LoopField49)
        if (A_Index49 == 177):
            useEnd = Trim(A_LoopField49)
        if (A_Index49 == 178):
            useEndExtraInfo = Trim(A_LoopField49)
        if (A_Index49 == 179):
            useSemicolon = Trim(A_LoopField49)
        if (A_Index49 == 180):
            useParentheses = Trim(A_LoopField49)
        if (A_Index49 == 181):
            usePrefixTypeForTypeDefinition = Trim(A_LoopField49)
        if (A_Index49 == 182):
            usePostfixTypeForTypeDefinition = Trim(A_LoopField49)
        if (A_Index49 == 183):
            usePythonicColonSyntax = Trim(A_LoopField49)
        if (A_Index49 == 184):
            useInJavaScriptAlwaysUseVar = Trim(A_LoopField49)
        if (A_Index49 == 185):
            useJavaScriptInAfullHTMLfile = Trim(A_LoopField49)
        if (A_Index49 == 186):
            useJavaScriptAmainFuncDef = Trim(A_LoopField49)
        if (A_Index49 == 187):
            useJavaScriptAllFuncsAreAsync = Trim(A_LoopField49)
        if (A_Index49 == 188):
            useJavaScriptAlwaysTripleEqual = Trim(A_LoopField49)
    if (Trim(langToConvertToParam) != ""):
        langToConvertTo = Trim(langToConvertToParam)
    isFullHTVMCode = 0
    isNotHTVMfile = 0
    if (Trim(mode) == "full"):
        isFullHTVMCode = 1
    else:
        isFullHTVMCode = 0
    if (Trim(mode) == "notHTVM"):
        isNotHTVMfile = 1
    else:
        isNotHTVMfile = 0
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    """
    if (langToConvertTo == "htvm"):
    if (langToConvertTo == "cpp"):
    if (langToConvertTo == "py"):
    if (langToConvertTo == "js"):
    if (langToConvertTo == "go"):
    if (langToConvertTo == "lua"):
    if (langToConvertTo == "cs"):
    if (langToConvertTo == "java"):
    if (langToConvertTo == "kt"):
    if (langToConvertTo == "rb"):
    if (langToConvertTo == "nim"):
    if (langToConvertTo == "ahk"):
    if (langToConvertTo == "swift"):
    if (langToConvertTo == "dart"):
    if (langToConvertTo == "ts"):
    if (langToConvertTo == "scala"):
    if (langToConvertTo == "groovy"):
    """
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    HTVMout = ""
    htCode = Trim(StrReplace(htCode, Chr(13), ""))
    if (langToConvertTo == "htvm"):
        HTVMout = "0"
    if (langToConvertTo == "cpp"):
        HTVMout = "0"
    if (langToConvertTo == "py"):
        HTVMout = "0"
    if (langToConvertTo == "js"):
        HTVMout = "0"
    if (langToConvertTo == "go"):
        HTVMout = "0"
    if (langToConvertTo == "lua"):
        HTVMout = "0"
    if (langToConvertTo == "cs"):
        HTVMout = "0"
    if (langToConvertTo == "java"):
        HTVMout = "0"
    if (langToConvertTo == "kt"):
        HTVMout = "0"
    if (langToConvertTo == "rb"):
        HTVMout = "0"
    if (langToConvertTo == "nim"):
        HTVMout = "0"
    if (langToConvertTo == "ahk"):
        HTVMout = "0"
    if (langToConvertTo == "swift"):
        HTVMout = "0"
    if (langToConvertTo == "dart"):
        HTVMout = "0"
    if (langToConvertTo == "ts"):
        HTVMout = "0"
    if (langToConvertTo == "scala"):
        HTVMout = "0"
    if (langToConvertTo == "groovy"):
        HTVMout = "0"
    code = ""
    print(htCode)
    code = htCode
    print(instructionFile)
    print(mode)
    print(langToConvertTo)
    print("==================================")
    print("==================================")
    print("==================================")
    print("==================================")
    print("==================================")
    #print(allInstructionFile)
    codeOutFix1 = ""
    items50 = LoopParseFunc(code, "\n", "\r")
    for A_Index50 , A_LoopField50 in enumerate(items50, start=0):
        codeOutFix1 += Trim(A_LoopField50) + "\n"
    code = StringTrimRight(codeOutFix1, 1)
    haveWeEverUsedAloop = 0
    lineDone = 0
    var1 = ""
    nothing = ""
    AindexcharLength = 1
    AindexcharLengthStr = ""
    theFixTextLoopNL = ""
    htCodeAcurlyBraceAddSomeVrasFixNL = 0
    htCodeLoopfixa = ""
    htCodeLoopfixa1 = ""
    str123 = ""
    out2 = ""
    myVar = ""
    lineYGI = ""
    line = ""
    line1 = ""
    line2 = ""
    line3 = ""
    itemsOut = ""
    var1out = ""
    theFixTextLoopLP = ""
    htCodeAcurlyBraceAddSomeVrasFixLP = 0
    AIndexLoopCurlyFix = 0
    sstr123 = ""
    fixLoopLokingFor = ""
    fixLoopLokingForfound = 0
    out1 = ""
    wasAtanyIfsElseAddAIndexLoopCurlyFix = 0
    inTarget = 0
    insideBracket = 0
    netsedCurly = 0
    eldLoopNestedBADlol = 0
    readyToEnd = 0
    endBracketDOntPutThere = 0
    dontSaveStr = 0
    weAreDoneHereCurly = 0
    DeleayOneCuzOfLoopParse = 0
    fixLoopLokingForNum = 0
    insdeAnestedLoopBAD = 0
    foundTheTopLoop = 0
    out4758686d86d86d86578991a = None
    ALoopField = ""
    out1z = ""
    insideBracket1 = 0
    netsedCurly1 = 0
    readyToEnd1 = 0
    strstysrstsytTRIMHELP = ""
    out4758686d86dgt8r754444444 = ""
    hold = 0
    holdText = ""
    ignore = 0
    htCodeOut1234565432 = ""
    out = ""
    s = ""
    skipLeftCuleyForFuncPLS = 0
    htCodeOUT754754 = ""
    areWEinSome34sNum = 0
    theIdNumOfThe34 = 0
    theIdNumOfThe34theVar = []
    ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = ""
    getAllCharForTheFurtureSoIcanAddEscapeChar = []
    removeNexFixkeyWordEscpaeChar = 0
    items51 = LoopParseFunc(code)
    for A_Index51 , A_LoopField51 in enumerate(items51, start=0):
        theIdNumOfThe34theVar.append("")
        theIdNumOfThe34theVar.append("")
    items52 = LoopParseFunc(code)
    for A_Index52 , A_LoopField52 in enumerate(items52, start=0):
        theIdNumOfThe34theVar[A_Index52] = theIdNumOfThe34theVar[A_Index52] + Chr(34)
        getAllCharForTheFurtureSoIcanAddEscapeChar.append(A_LoopField52)
    getAllCharForTheFurtureSoIcanAddEscapeChar.append(" ")
    ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuusgfgesrheidFor-aasdsas-theuhtuwaesphoutr" + Chr(34)
    OutFixDoubleQuotesInsideDoubleQuotes = ""
    fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0
    items53 = LoopParseFunc(code)
    for A_Index53 , A_LoopField53 in enumerate(items53, start=0):
        if (A_LoopField53 == keyWordEscpaeChar and getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index53] == Chr(34)):
            fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1
            OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes
        else:
            if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1):
                OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField53
            else:
                fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0
    code = StringTrimRight(OutFixDoubleQuotesInsideDoubleQuotes, 1)
    if (keyWordEscpaeChar != Chr(92)):
        code = StrReplace(code, Chr(92), Chr(92) + Chr(92))
    if (keyWordEscpaeChar == Chr(92)):
        items54 = LoopParseFunc(code)
        for A_Index54 , A_LoopField54 in enumerate(items54, start=0):
            if (A_LoopField54 == Chr(34)):
                areWEinSome34sNum = areWEinSome34sNum + 1
            if (areWEinSome34sNum == 1):
                if (A_LoopField54 != Chr(34)):
                    if (A_LoopField54 == keyWordEscpaeChar):
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92)
                    else:
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField54
                else:
                    theIdNumOfThe34 = theIdNumOfThe34 + 1
                    htCodeOUT754754 += "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65)
            if (areWEinSome34sNum == 2 or areWEinSome34sNum == 0):
                if (A_LoopField54 != Chr(34)):
                    htCodeOUT754754 += A_LoopField54
                areWEinSome34sNum = 0
    else:
        items55 = LoopParseFunc(code)
        for A_Index55 , A_LoopField55 in enumerate(items55, start=0):
            if (A_LoopField55 == Chr(34)):
                areWEinSome34sNum = areWEinSome34sNum + 1
            if (areWEinSome34sNum == 1):
                if (A_LoopField55 != Chr(34)):
                    if (A_LoopField55 == keyWordEscpaeChar and keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index55]):
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar
                        removeNexFixkeyWordEscpaeChar = 1
                    elif (A_LoopField55 == keyWordEscpaeChar):
                        if (removeNexFixkeyWordEscpaeChar != 1):
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92)
                        else:
                            removeNexFixkeyWordEscpaeChar = 0
                    else:
                        theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField55
                else:
                    theIdNumOfThe34 = theIdNumOfThe34 + 1
                    htCodeOUT754754 += "ihuiuuhuuhtheidFor-asdsas-theuhturtyphoutr-" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65)
            if (areWEinSome34sNum == 2 or areWEinSome34sNum == 0):
                if (A_LoopField55 != Chr(34)):
                    htCodeOUT754754 += A_LoopField55
                areWEinSome34sNum = 0
    code = htCodeOUT754754
    for A_Index56 in range(0, theIdNumOfThe34 + 0):
        theIdNumOfThe34theVar[A_Index56] = theIdNumOfThe34theVar[A_Index56] + Chr(34)
    code = StrReplace(code, Chr(13), "")
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    if (langToConvertTo != "py" and useSemicolon == "off"):
        theSemicolon = ";"
    else:
        theSemicolon = ""
    if (langToConvertTo != "py" and usePythonicColonSyntax == "off"):
        theColon = ""
    else:
        theColon = ":"
    beforeKeywordForRemoveCommentsOnTheEndOfTheLine = ""
    newStringOutCode = ""
    posForRemoveCommentsOnTheEndOfTheLine = 0
    originalStringForRemoveCommentsOnTheEndOfTheLine = ""
    items57 = LoopParseFunc(code, "\n", "\r")
    for A_Index57 , A_LoopField57 in enumerate(items57, start=0):
        # Define the original string
        originalStringForRemoveCommentsOnTheEndOfTheLine = A_LoopField57
        # Find the position of the keyword in the original string
        posForRemoveCommentsOnTheEndOfTheLine = InStr(originalStringForRemoveCommentsOnTheEndOfTheLine, " " + keyWordComment)
        if (SubStr(Trim(A_LoopField57), 1, StrLen(keyWordComment)) != keyWordComment):
            if (posForRemoveCommentsOnTheEndOfTheLine > 0):
                # Extract the part of the string before the keyword
                if (SubStr(StrLower(A_LoopField57), 1, StrLen(StrLower(keyWordForLoop))) != StrLower(keyWordForLoop)):
                    beforeKeywordForRemoveCommentsOnTheEndOfTheLine = SubStr(originalStringForRemoveCommentsOnTheEndOfTheLine, 1, posForRemoveCommentsOnTheEndOfTheLine - 1)
                else:
                    beforeKeywordForRemoveCommentsOnTheEndOfTheLine = A_LoopField57
                # Construct the new string with everything before the keyword
                newStringOutCode += beforeKeywordForRemoveCommentsOnTheEndOfTheLine + "\n"
            else:
                newStringOutCode += A_LoopField57 + "\n"
        else:
            newStringOutCode += A_LoopField57 + "\n"
    code = StringTrimRight(newStringOutCode, 1)
    #MsgBox, % code
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    htCodeOutFixEnd = ""
    if (useEnd == "on"):
        items58 = LoopParseFunc(code, "\n", "\r")
        for A_Index58 , A_LoopField58 in enumerate(items58, start=0):
            if (StrLower(Trim(A_LoopField58)) == StrLower(keyWordEnd)):
                htCodeOutFixEnd += str10 + "}" + "\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf)):
                htCodeOutFixEnd += "\n}\n" + A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse)):
                htCodeOutFixEnd += "\n}\n" + A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordForLoop))) == StrLower(keyWordForLoop)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordLoopInfinite))) == StrLower(keyWordLoopInfinite)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordSwitch))) == StrLower(keyWordSwitch)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordSwitchCase))) == StrLower(keyWordSwitchCase)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordSwitchDefault))) == StrLower(keyWordSwitchDefault)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordTry))) == StrLower(keyWordTry)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordCrew))) == StrLower(keyWordCrew)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordDefObj))) == StrLower(keyWordDefObj)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordMethod))) == StrLower(keyWordMethod)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)):
                htCodeOutFixEnd += "\n}\n" + A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally)):
                htCodeOutFixEnd += "\n}\n" + A_LoopField58 + "\n{\n"
            elif (SubStr(StrLower(Trim(A_LoopField58)), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc)):
                htCodeOutFixEnd += A_LoopField58 + "\n{\n"
            else:
                htCodeOutFixEnd += A_LoopField58 + "\n"
        code = StringTrimRight(htCodeOutFixEnd, 1)
    if (useEnd == "off" and useCurlyBraces == "off"):
        htCodeOutFixEnd = ""
        items59 = LoopParseFunc(code, "\n", "\r")
        for A_Index59 , A_LoopField59 in enumerate(items59, start=0):
            if (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordForLoop))) == StrLower(keyWordForLoop)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordLoopInfinite))) == StrLower(keyWordLoopInfinite)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordSwitch))) == StrLower(keyWordSwitch)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordSwitchCase))) == StrLower(keyWordSwitchCase)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordSwitchDefault))) == StrLower(keyWordSwitchDefault)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordTry))) == StrLower(keyWordTry)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordCrew))) == StrLower(keyWordCrew)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordDefObj))) == StrLower(keyWordDefObj)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordMethod))) == StrLower(keyWordMethod)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            elif (SubStr(StrLower(Trim(A_LoopField59)), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc)):
                htCodeOutFixEnd += A_LoopField59 + ":\n"
            else:
                htCodeOutFixEnd += A_LoopField59 + "\n"
        code = StringTrimRight(htCodeOutFixEnd, 1)
    if (useCurlyBraces == "off" and useEnd == "off"):
        code = AddCurlyBraces(code)
    items60 = LoopParseFunc(code, "\n", "\r")
    for A_Index60 , A_LoopField60 in enumerate(items60, start=0):
        outTrimCode += Trim(A_LoopField60) + "\n"
    code = StringTrimRight(outTrimCode, 1)
    # for converting c++ to js and py
    code = StrReplace(code, "{}", "[]")
    outCodeFixBraces = ""
    for A_Index61 in range(0, 2 + 0):
        outCodeFixBraces = ""
        items62 = LoopParseFunc(code, "\n", "\r")
        for A_Index62 , A_LoopField62 in enumerate(items62, start=0):
            if (InStr(Trim(A_LoopField62), "{") and Trim(A_LoopField62) != "{"):
                outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField62), "{", "")) + "\n{\n"
            elif (InStr(Trim(A_LoopField62), "}") and Trim(A_LoopField62) != "}"):
                outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField62), "}", "")) + "\n"
            else:
                outCodeFixBraces += Trim(A_LoopField62) + "\n"
        code = StringTrimRight(outCodeFixBraces, 1)
    #MsgBox, % code
    #;; main loop ;;;
    #;; main loop ;;;
    #;; main loop ;;;
    #;; main loop ;;;
    didWeUseMainLabel = 0
    codeOutFixAndAddMainFunc = ""
    print(code)
    items63 = LoopParseFunc(code, "\n", "\r")
    for A_Index63 , A_LoopField63 in enumerate(items63, start=0):
        HTVMout = "0"
    return HTVMout
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
def HTVMv2():
    argCODE = ""
    argCODEfile = ""
    argHTVMinstr = ""
    argLangTo = ""
    OUTCODE = "null"
    HTVM_v2_HTVM()
    if (noParams == True):
        return
    items64 = LoopParseFunc(str0)
    for A_Index64 , A_LoopField64 in enumerate(items64, start=0):
        str00 = Trim(A_LoopField64)
        str00 = StringTrimRight(str00, 1)
    print("HTVM v2")
    if (HTVM_getLang_HTVM() == "cpp" or HTVM_getLang_HTVM() == "py"):
        if (HTVM_getLang_HTVM() == "cpp"):
            print("CPP")
        if (HTVM_getLang_HTVM() == "py"):
            print("PY")
        items65 = LoopParseFunc(allArgs, "\n", "\r")
        for A_Index65 , A_LoopField65 in enumerate(items65, start=0):
            if (A_Index65 == 0):
                argCODE = FileRead(Trim(A_LoopField65))
                argCODEfile = Trim(A_LoopField65)
            elif (A_Index65 == 1):
                argHTVMinstr = Trim(A_LoopField65)
            elif (A_Index65 == 2):
                argLangTo = Trim(A_LoopField65)
            else:
                argHTVMinstrMOVE.append(Trim(A_LoopField65))
        print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo)
        if (SubStrLastChars(argCODEfile, 4) == ".cpp" or SubStrLastChars(argCODEfile, 3) == ".py" or SubStrLastChars(argCODEfile, 3) == ".js" or SubStrLastChars(argCODEfile, 3) == ".go" or SubStrLastChars(argCODEfile, 4) == ".lua" or SubStrLastChars(argCODEfile, 3) == ".cs" or SubStrLastChars(argCODEfile, 5) == ".java" or SubStrLastChars(argCODEfile, 3) == ".kt" or SubStrLastChars(argCODEfile, 3) == ".rb" or SubStrLastChars(argCODEfile, 4) == ".nim" or SubStrLastChars(argCODEfile, 4) == ".ahk" or SubStrLastChars(argCODEfile, 6) == ".swift" or SubStrLastChars(argCODEfile, 5) == ".dart" or SubStrLastChars(argCODEfile, 3) == ".ts" or SubStrLastChars(argCODEfile, 6) == ".scala" or SubStrLastChars(argCODEfile, 7) == ".groovy"):
            if (argLangTo != ""):
                OUTCODE = compiler(argCODE, argHTVMinstr, "notHTVM", argLangTo)
            else:
                OUTCODE = compiler(argCODE, argHTVMinstr, "notHTVM")
        else:
            if (argLangTo != ""):
                OUTCODE = compiler(argCODE, argHTVMinstr, "full", argLangTo)
            else:
                OUTCODE = compiler(argCODE, argHTVMinstr, "full")
        print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo)
        FileDelete(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo)
        FileAppend(OUTCODE, StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo)
    if (HTVM_getLang_HTVM() == "js"):
        print("JS")
HTVMv2()