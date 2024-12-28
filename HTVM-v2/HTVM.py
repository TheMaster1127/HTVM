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

def Exp(value: float) -> float:
    return math.exp(value)

def Trim(inputString):
    return inputString.strip() if inputString else ""

def StringTrimRight(input, numChars):
    return input[:-numChars] if numChars <= len(input) else input

def Mod(dividend, divisor):
    return dividend % divisor

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
argHTVMinstrMOVE = []
extraCodeReturned = ""
langToConvertTo = ""
langFileExtension = ""
def compiler(code, instructionFile, mode, langToConvertToParam = ""):
    extraCodeReturned = ""
    allInstructionFile = Trim(FileRead(instructionFile))
    items1 = LoopParseFunc(allInstructionFile, "\n", "\r")
    for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
        if (A_Index1 == 0):
            langToConvertTo = Trim(A_LoopField1)
        if (A_Index1 == 1):
            langFileExtension = Trim(A_LoopField1)
        if (A_Index1 == 2):
            commands = Trim(A_LoopField1)
        if (A_Index1 == 3):
            keyWordAlliance = Trim(A_LoopField1)
        if (A_Index1 == 4):
            keyWordCrew = Trim(A_LoopField1)
        if (A_Index1 == 5):
            keyWordMethod = Trim(A_LoopField1)
        if (A_Index1 == 6):
            keyWordDefObj = Trim(A_LoopField1)
        if (A_Index1 == 7):
            keyWordPorp = Trim(A_LoopField1)
        if (A_Index1 == 8):
            keyWordThis = Trim(A_LoopField1)
        if (A_Index1 == 9):
            keyWordInclude = Trim(A_LoopField1)
        if (A_Index1 == 10):
            keyWordIncludeInTheTranspiledLang = Trim(A_LoopField1)
        if (A_Index1 == 11):
            keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField1)
        if (A_Index1 == 12):
            keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField1)
        if (A_Index1 == 13):
            keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField1)
        if (A_Index1 == 14):
            keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField1)
        if (A_Index1 == 15):
            keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField1)
        if (A_Index1 == 16):
            keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField1)
        if (A_Index1 == 17):
            keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField1)
        if (A_Index1 == 18):
            keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField1)
        if (A_Index1 == 19):
            keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField1)
        if (A_Index1 == 20):
            keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField1)
        if (A_Index1 == 21):
            keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField1)
        if (A_Index1 == 22):
            keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField1)
        if (A_Index1 == 23):
            keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField1)
        if (A_Index1 == 24):
            keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField1)
        if (A_Index1 == 25):
            keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField1)
        if (A_Index1 == 26):
            keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField1)
        if (A_Index1 == 27):
            keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField1)
        if (A_Index1 == 28):
            keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField1)
        if (A_Index1 == 29):
            keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField1)
        if (A_Index1 == 30):
            keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField1)
        if (A_Index1 == 31):
            keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField1)
        if (A_Index1 == 32):
            keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField1)
        if (A_Index1 == 33):
            keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField1)
        if (A_Index1 == 34):
            keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField1)
        if (A_Index1 == 35):
            keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField1)
        if (A_Index1 == 36):
            keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField1)
        if (A_Index1 == 37):
            keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField1)
        if (A_Index1 == 38):
            keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField1)
        if (A_Index1 == 39):
            keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField1)
        if (A_Index1 == 40):
            keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField1)
        if (A_Index1 == 41):
            keyWordCodeInTheTranspiledLangStartSCALA = Trim(A_LoopField1)
        if (A_Index1 == 42):
            keyWordCodeInTheTranspiledLangEndSCALA = Trim(A_LoopField1)
        if (A_Index1 == 43):
            keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField1)
        if (A_Index1 == 44):
            keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField1)
        if (A_Index1 == 45):
            keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField1)
        if (A_Index1 == 46):
            keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField1)
        if (A_Index1 == 47):
            keyWordCodeInHTVMstart = Trim(A_LoopField1)
        if (A_Index1 == 48):
            keyWordCodeInHTVMend = Trim(A_LoopField1)
        if (A_Index1 == 49):
            keyWordCodeInOtherHTVMsyntaxStart = Trim(A_LoopField1)
        if (A_Index1 == 50):
            keyWordCodeInOtherHTVMsyntaxStart = Trim(A_LoopField1)
        if (A_Index1 == 51):
            keyWordCurlyBraceOpen = Trim(A_LoopField1)
        if (A_Index1 == 52):
            keyWordCurlyBraceClose = Trim(A_LoopField1)
        if (A_Index1 == 53):
            keyWordNull = Trim(A_LoopField1)
        if (A_Index1 == 54):
            keyWordTrue = Trim(A_LoopField1)
        if (A_Index1 == 55):
            keyWordFalse = Trim(A_LoopField1)
        if (A_Index1 == 56):
            keyWordVoid = Trim(A_LoopField1)
        if (A_Index1 == 57):
            keyWordDouble = Trim(A_LoopField1)
        if (A_Index1 == 58):
            keyWordChar = Trim(A_LoopField1)
        if (A_Index1 == 59):
            keyWordUint8 = Trim(A_LoopField1)
        if (A_Index1 == 60):
            keyWordUint16 = Trim(A_LoopField1)
        if (A_Index1 == 61):
            keyWordUint32 = Trim(A_LoopField1)
        if (A_Index1 == 62):
            keyWordUint64 = Trim(A_LoopField1)
        if (A_Index1 == 63):
            keyWordINT = Trim(A_LoopField1)
        if (A_Index1 == 64):
            keyWordSTR = Trim(A_LoopField1)
        if (A_Index1 == 65):
            keyWordBOOL = Trim(A_LoopField1)
        if (A_Index1 == 66):
            keyWordFLOAT = Trim(A_LoopField1)
        if (A_Index1 == 67):
            keyWordINT8 = Trim(A_LoopField1)
        if (A_Index1 == 68):
            keyWordINT16 = Trim(A_LoopField1)
        if (A_Index1 == 69):
            keyWordINT32 = Trim(A_LoopField1)
        if (A_Index1 == 70):
            keyWordINT64 = Trim(A_LoopField1)
        if (A_Index1 == 71):
            keyWordIF = Trim(A_LoopField1)
        if (A_Index1 == 72):
            keyWordElseIf = Trim(A_LoopField1)
        if (A_Index1 == 73):
            keyWordElse = Trim(A_LoopField1)
        if (A_Index1 == 74):
            keyWordSwitch = Trim(A_LoopField1)
        if (A_Index1 == 75):
            keyWordSwitchCase = Trim(A_LoopField1)
        if (A_Index1 == 76):
            keyWordSwitchDefault = Trim(A_LoopField1)
        if (A_Index1 == 77):
            keyWordWhileLoop = Trim(A_LoopField1)
        if (A_Index1 == 78):
            keyWordForLoop = Trim(A_LoopField1)
        if (A_Index1 == 79):
            keyWordLoopInfinite = Trim(A_LoopField1)
        if (A_Index1 == 80):
            keyWordLoop = Trim(A_LoopField1)
        if (A_Index1 == 81):
            keyWordLoopParse = Trim(A_LoopField1)
        if (A_Index1 == 82):
            keyWordContinue = Trim(A_LoopField1)
        if (A_Index1 == 83):
            keyWordBreak = Trim(A_LoopField1)
        if (A_Index1 == 84):
            keyWordFunc = Trim(A_LoopField1)
        if (A_Index1 == 85):
            keyWordAwait = Trim(A_LoopField1)
        if (A_Index1 == 86):
            keyWordAsync = Trim(A_LoopField1)
        if (A_Index1 == 87):
            keyWordThrow = Trim(A_LoopField1)
        if (A_Index1 == 88):
            keyWordErrorMsg = Trim(A_LoopField1)
        if (A_Index1 == 89):
            keyWordTry = Trim(A_LoopField1)
        if (A_Index1 == 90):
            keyWordCatch = Trim(A_LoopField1)
        if (A_Index1 == 91):
            keyWordFinally = Trim(A_LoopField1)
        if (A_Index1 == 92):
            keyWordReturnStatement = Trim(A_LoopField1)
        if (A_Index1 == 93):
            keyWordArrayAppend = Trim(A_LoopField1)
        if (A_Index1 == 94):
            keyWordArrayPop = Trim(A_LoopField1)
        if (A_Index1 == 95):
            keyWordArraySize = Trim(A_LoopField1)
        if (A_Index1 == 96):
            keyWordArrayInsert = Trim(A_LoopField1)
        if (A_Index1 == 97):
            keyWordArrayRemove = Trim(A_LoopField1)
        if (A_Index1 == 98):
            keyWordArrayIndexOf = Trim(A_LoopField1)
        if (A_Index1 == 99):
            keyWordArrayDefinition = Trim(A_LoopField1)
        if (A_Index1 == 100):
            keyWordArrayOfIntegersDefinition = Trim(A_LoopField1)
        if (A_Index1 == 101):
            keyWordArrayOfStringsDefinition = Trim(A_LoopField1)
        if (A_Index1 == 102):
            keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField1)
        if (A_Index1 == 103):
            keyWordArrayOfBooleansDefinition = Trim(A_LoopField1)
        if (A_Index1 == 104):
            keyWordJavaScriptVar = Trim(A_LoopField1)
        if (A_Index1 == 105):
            keyWordJavaScriptLet = Trim(A_LoopField1)
        if (A_Index1 == 106):
            keyWordJavaScriptConst = Trim(A_LoopField1)
        if (A_Index1 == 107):
            keyWordEnd = Trim(A_LoopField1)
        if (A_Index1 == 108):
            keyWordGlobal = Trim(A_LoopField1)
        if (A_Index1 == 109):
            keyWordComment = Trim(A_LoopField1)
        if (A_Index1 == 110):
            keyWordCommentOpenMultiLine = Trim(A_LoopField1)
        if (A_Index1 == 111):
            keyWordCommentCloseMultiLine = Trim(A_LoopField1)
        if (A_Index1 == 112):
            keyWordEscpaeChar = Trim(A_LoopField1)
        if (A_Index1 == 113):
            keyWordMainLabel = Trim(A_LoopField1)
        if (A_Index1 == 114):
            keyWordConcat = Trim(A_LoopField1)
        if (A_Index1 == 115):
            keyWordAdd = Trim(A_LoopField1)
        if (A_Index1 == 116):
            keyWordSub = Trim(A_LoopField1)
        if (A_Index1 == 117):
            keyWordMul = Trim(A_LoopField1)
        if (A_Index1 == 118):
            keyWordDiv = Trim(A_LoopField1)
        if (A_Index1 == 119):
            keyWordMod = Trim(A_LoopField1)
        if (A_Index1 == 120):
            keyWordExp = Trim(A_LoopField1)
        if (A_Index1 == 121):
            keyWordEqual = Trim(A_LoopField1)
        if (A_Index1 == 122):
            keyWordStrictEqual = Trim(A_LoopField1)
        if (A_Index1 == 123):
            keyWordNotEqual = Trim(A_LoopField1)
        if (A_Index1 == 124):
            keyWordGreater = Trim(A_LoopField1)
        if (A_Index1 == 125):
            keyWordLess = Trim(A_LoopField1)
        if (A_Index1 == 126):
            keyWordGreaterEqual = Trim(A_LoopField1)
        if (A_Index1 == 127):
            keyWordLessEqual = Trim(A_LoopField1)
        if (A_Index1 == 128):
            keyWordAnd = Trim(A_LoopField1)
        if (A_Index1 == 129):
            keyWordOr = Trim(A_LoopField1)
        if (A_Index1 == 130):
            keyWordNot = Trim(A_LoopField1)
        if (A_Index1 == 131):
            keyWordBitAnd = Trim(A_LoopField1)
        if (A_Index1 == 132):
            keyWordBitOr = Trim(A_LoopField1)
        if (A_Index1 == 133):
            keyWordBitXor = Trim(A_LoopField1)
        if (A_Index1 == 134):
            keyWordBitNot = Trim(A_LoopField1)
        if (A_Index1 == 135):
            keyWordShiftLeft = Trim(A_LoopField1)
        if (A_Index1 == 136):
            keyWordShiftRight = Trim(A_LoopField1)
        if (A_Index1 == 137):
            keyWordShiftUnsignedRight = Trim(A_LoopField1)
        if (A_Index1 == 138):
            keyWordAssign = Trim(A_LoopField1)
        if (A_Index1 == 139):
            keyWordAssignAdd = Trim(A_LoopField1)
        if (A_Index1 == 140):
            keyWordAssignConcat = Trim(A_LoopField1)
        if (A_Index1 == 141):
            keyWordAssignSub = Trim(A_LoopField1)
        if (A_Index1 == 142):
            keyWordAssignMul = Trim(A_LoopField1)
        if (A_Index1 == 143):
            keyWordAssignDiv = Trim(A_LoopField1)
        if (A_Index1 == 144):
            keyWordAssignMod = Trim(A_LoopField1)
        if (A_Index1 == 145):
            keyWordAssignShiftLeft = Trim(A_LoopField1)
        if (A_Index1 == 146):
            keyWordAssignShiftRight = Trim(A_LoopField1)
        if (A_Index1 == 147):
            keyWordAssignBitAnd = Trim(A_LoopField1)
        if (A_Index1 == 148):
            keyWordAssignBitOr = Trim(A_LoopField1)
        if (A_Index1 == 149):
            keyWordAssignBitXor = Trim(A_LoopField1)
        if (A_Index1 == 150):
            keyWordTernary1 = Trim(A_LoopField1)
        if (A_Index1 == 151):
            keyWordTernary2 = Trim(A_LoopField1)
        if (A_Index1 == 152):
            keyWordInc = Trim(A_LoopField1)
        if (A_Index1 == 153):
            keyWordDec = Trim(A_LoopField1)
        if (A_Index1 == 154):
            AHKlikeLoopsIndexedAt = Trim(A_LoopField1)
        if (A_Index1 == 155):
            keyWordAIndex = Trim(A_LoopField1)
        if (A_Index1 == 156):
            keyWordALoopField = Trim(A_LoopField1)
        if (A_Index1 == 157):
            keyWordAllianceEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 158):
            keyWordCrewEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 159):
            keyWordMethodEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 160):
            keyWordDefObjEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 161):
            keyWordIFEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 162):
            keyWordElseIfEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 163):
            keyWordElseEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 164):
            keyWordSwitchEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 165):
            keyWordSwitchCaseEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 166):
            keyWordWhileLoopEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 167):
            keyWordForLoopEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 168):
            keyWordLoopInfiniteEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 169):
            keyWordLoopEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 170):
            keyWordLoopParseEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 171):
            keyWordFuncEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 172):
            keyWordTryEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 173):
            keyWordCatchEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 174):
            keyWordFinallyEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 175):
            useFuncKeyWord = Trim(A_LoopField1)
        if (A_Index1 == 176):
            useCurlyBraces = Trim(A_LoopField1)
        if (A_Index1 == 177):
            useEnd = Trim(A_LoopField1)
        if (A_Index1 == 178):
            useEndExtraInfo = Trim(A_LoopField1)
        if (A_Index1 == 179):
            useSemicolon = Trim(A_LoopField1)
        if (A_Index1 == 180):
            useParentheses = Trim(A_LoopField1)
        if (A_Index1 == 181):
            usePrefixTypeForTypeDefinition = Trim(A_LoopField1)
        if (A_Index1 == 182):
            usePostfixTypeForTypeDefinition = Trim(A_LoopField1)
        if (A_Index1 == 183):
            usePythonicColonSyntax = Trim(A_LoopField1)
        if (A_Index1 == 184):
            useInJavaScriptAlwaysUseVar = Trim(A_LoopField1)
        if (A_Index1 == 185):
            useJavaScriptInAfullHTMLfile = Trim(A_LoopField1)
        if (A_Index1 == 186):
            useJavaScriptAmainFuncDef = Trim(A_LoopField1)
        if (A_Index1 == 187):
            useJavaScriptAllFuncsAreAsync = Trim(A_LoopField1)
        if (A_Index1 == 188):
            useJavaScriptAlwaysTripleEqual = Trim(A_LoopField1)
    if (Trim(langToConvertToParam) != ""):
        langToConvertTo = Trim(langToConvertToParam)
    isFullHTVMCode = 0
    if (Trim(mode) == "full"):
        isFullHTVMCode = 1
    else:
        isFullHTVMCode = 0
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
    code = Trim(code)
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
    print(code)
    print(instructionFile)
    print(mode)
    print(langToConvertTo)
    print("==================================")
    print("==================================")
    print("==================================")
    print("==================================")
    print("==================================")
    print(allInstructionFile)
    codeOutFix1 = ""
    items2 = LoopParseFunc(code, "\n", "\r")
    for A_Index2 , A_LoopField2 in enumerate(items2, start=0):
        codeOutFix1 += Trim(A_LoopField2) + "\n"
    codeOutFix1 = StringTrimRight(codeOutFix1, 1)
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
    items3 = LoopParseFunc(str0)
    for A_Index3 , A_LoopField3 in enumerate(items3, start=0):
        str00 = Trim(A_LoopField3)
        str00 = StringTrimRight(str00, 1)
    print("HTVM v2")
    if (HTVM_getLang_HTVM() == "cpp" or HTVM_getLang_HTVM() == "py"):
        if (HTVM_getLang_HTVM() == "cpp"):
            print("CPP")
        if (HTVM_getLang_HTVM() == "py"):
            print("PY")
        items4 = LoopParseFunc(allArgs, "\n", "\r")
        for A_Index4 , A_LoopField4 in enumerate(items4, start=0):
            if (A_Index4 == 0):
                argCODE = FileRead(Trim(A_LoopField4))
                argCODEfile = Trim(A_LoopField4)
            elif (A_Index4 == 1):
                argHTVMinstr = Trim(A_LoopField4)
            elif (A_Index4 == 2):
                argLangTo = Trim(A_LoopField4)
            else:
                argHTVMinstrMOVE.append(Trim(A_LoopField4))
        if (argLangTo != ""):
            OUTCODE = compiler(argCODE, argHTVMinstr, "full", argLangTo)
        else:
            OUTCODE = compiler(argCODE, argHTVMinstr, "full")
        FileDelete(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo)
        FileAppend(OUTCODE, StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo)
    if (HTVM_getLang_HTVM() == "js"):
        print("JS")
HTVMv2()