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

def Log(value: float) -> float:
    return math.log10(value)

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

def countChars(string, theChar):
    return string.count(theChar)

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
    global noParams, allArgs
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
argHTVMinstrMORE = []
isNotHTVMfileEXTRA_INT = 0
isNotHTVMfile2 = 0
isNotHTVMfileEXTRA_LIB_INFO = ""
isNotHTVMfileEXTRA_FUNCS_INFO = ""
programmingBlock_InTheTranspiledLang = []
programmingBlock_CPP = []
programmingBlock_PY = []
programmingBlock_JS = []
programmingBlock_GO = []
programmingBlock_LUA = []
programmingBlock_CS = []
programmingBlock_JAVA = []
programmingBlock_KT = []
programmingBlock_RB = []
programmingBlock_NIM = []
programmingBlock_AHK = []
programmingBlock_SWIFT = []
programmingBlock_DART = []
programmingBlock_TS = []
programmingBlock_GROOVY = []
programmingBlock_HTVM = []
programmingBlock_HTVMsyntax = []
fullLangAllOperators = []
fullLangAllOperators_HELP = []
fixExpertionLineFuncOnly = 0
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
keyWordCodeInTheTranspiledLangStartGROOVY = ""
keyWordCodeInTheTranspiledLangEndGROOVY = ""
keyWordCodeInTheTranspiledLangStartHTVM = ""
keyWordCodeInTheTranspiledLangEndHTVM = ""
keyWordCodeInHTVMstart = ""
keyWordCodeInHTVMend = ""
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
keyWordWhileLoop = ""
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
keyWordVar = ""
keyWordLet = ""
keyWordConst = ""
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
keyWordLogicalAssignShiftRight = ""
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
useFuncKeyWord = ""
useCurlyBraces = ""
useEnd = ""
useSemicolon = ""
theSemicolon = ""
theColon = ""
useParentheses = ""
usePrefixTypeForTypeDefinition = ""
usePostfixTypeForTypeDefinition = ""
usePythonicColonSyntax = ""
useCurlyBracesSyntaxForArrayDef = ""
useInJavaScriptAlwaysUseVar = ""
useJavaScriptInAfullHTMLfile = ""
useJavaScriptAmainFuncDef = ""
useJavaScriptAllFuncsAreAsync = ""
useJavaScriptAlwaysTripleEqual = ""
langToConvertTo_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
langFileExtension_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
commands_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAlliance_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCrew_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordMethod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordDefObj_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordPorp_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordThis_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordInclude_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStart_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartCPP_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndCPP_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartPY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndPY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartJS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndJS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartGO_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndGO_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartLUA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndLUA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartCS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndCS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartJAVA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndJAVA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartKT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndKT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartRB_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndRB_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartNIM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndNIM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartAHK_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndAHK_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartSWIFT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndSWIFT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartDART_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndDART_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartTS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndTS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartGROOVY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndGROOVY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangStartHTVM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInTheTranspiledLangEndHTVM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInHTVMstart_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCodeInHTVMend_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCurlyBraceOpen_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCurlyBraceClose_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordNull_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordTrue_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordFalse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordVoid_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordDouble_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordChar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordUint8_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordUint16_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordUint32_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordUint64_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordINT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordSTR_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordBOOL_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordFLOAT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordINT8_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordINT16_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordINT32_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordINT64_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordIF_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordElseIf_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordElse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordWhileLoop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordLoopInfinite_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordLoop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordLoopParse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordContinue_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordBreak_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordFunc_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAwait_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAsync_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordThrow_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordErrorMsg_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordTry_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCatch_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordFinally_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordReturnStatement_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordArrayAppend_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordArrayPop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordArraySize_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordArrayInsert_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordArrayRemove_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordArrayIndexOf_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordArrayDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordArrayOfIntegersDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordArrayOfStringsDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordArrayOfFloatingPointNumbersDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordArrayOfBooleansDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordVar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordLet_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordConst_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordGlobal_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordComment_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCommentOpenMultiLine_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordCommentCloseMultiLine_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordEscpaeChar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordMainLabel_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordConcat_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAdd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordSub_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordMul_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordDiv_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordMod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordExp_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordStrictEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordNotEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordGreater_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordLess_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordGreaterEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordLessEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordNot_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordBitAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordBitOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordBitXor_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordBitNot_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordShiftLeft_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordShiftUnsignedRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAssign_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAssignAdd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAssignConcat_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAssignSub_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAssignMul_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAssignDiv_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAssignMod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAssignShiftLeft_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAssignShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordLogicalAssignShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAssignBitAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAssignBitOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAssignBitXor_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordTernary1_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordTernary2_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordInc_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordDec_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
AHKlikeLoopsIndexedAt_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordAIndex_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
keyWordALoopField_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
useCurlyBraces_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
useEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
useSemicolon_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
useParentheses_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
usePrefixTypeForTypeDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
usePostfixTypeForTypeDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
usePythonicColonSyntax_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
useCurlyBracesSyntaxForArrayDef_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
useInJavaScriptAlwaysUseVar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
useJavaScriptInAfullHTMLfile_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
useJavaScriptAmainFuncDef_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
useJavaScriptAllFuncsAreAsync_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
useJavaScriptAlwaysTripleEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd"
out_KeyWordsCommands = ""
outTrimCode = ""
htCode = ""
outVarOperator = ""
lineDone = 0
areWeInAFuncFromInstructions = 0
areWeInAFuncFromInstructionsLineNum = 0
theTryCatchVarForErrors = "jhku-dfsds-ds-d-ffdsf-sdfsfdsedsf"
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
                if (A_Index2 == 0):
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField2 + ", ")) == StrLower(A_LoopField2 + ", ")):
                        #MsgBox, true
                        return "true"
                if (A_Index2 == 0):
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
                if (A_Index4 == 0):
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField4 + ", ")) == StrLower(A_LoopField4 + ", ")):
                        #MsgBox, true
                        keyWordsCommandsNumLine = AIndex
                        break
                if (A_Index4 == 0):
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
        theCodeCommandNum = 0
        outConstuctTheOutFromTheCommandsLineTranspile = 0
        outConstuctTheOutFromTheCommandsLineTranspileText = ""
        semicolon = ""
        if (langToConvertTo != "py" and langToConvertTo != "nim" and langToConvertTo != "ahk" and langToConvertTo != "go" and langToConvertTo != "lua" and langToConvertTo != "kt" and langToConvertTo != "rb" and langToConvertTo != "swift" and langToConvertTo != "groovy"):
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
                    if (A_Index7 == 0):
                        outConstuctTheOutFromTheCommandsFucnName = A_LoopField7
                    elif (A_Index7 == 1):
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
                    elif (A_Index7 == 2):
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
    allDelimiters = " ()[].,;:'!&|=<>+-*/^%~" + Chr(34) + Chr(9) + Chr(11)
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
    line = ""
    stripped = ""
    items22 = LoopParseFunc(pythonCode, "\n", "\r")
    for A_Index22 , A_LoopField22 in enumerate(items22, start=0):
        line = A_LoopField22
        stripped = Trim(line)
        if (stripped == ""):
            result += line + "\n"
            continue
        # Count leading spaces
        indent = StrLen(line) - StrLen(LTrim(line))
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
    culyOpenFix = "{"
    culyCloseFix = "}"
    if (langToConvertTo == langFileExtension_2):
        culyOpenFix = Trim(keyWordCurlyBraceOpen_2)
        culyCloseFix = Trim(keyWordCurlyBraceClose_2)
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
                resultOut += A_LoopField29 + " " + culyOpenFix + "\n"
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
            if (langToConvertTo != "lua" and langToConvertTo != "rb" and langToConvertTo != langFileExtension_2):
                if (Trim(A_LoopField31) == "}" and Trim(lookIntoFurture2[A_Index31 + 1]) == "else {"):
                    skipNext = 2
                    addSpacesAtTheBegginig = ""
                    items32 = LoopParseFunc(A_LoopField31)
                    for A_Index32 , A_LoopField32 in enumerate(items32, start=0):
                        if (A_LoopField32 == " "):
                            if (A_LoopField32 != " "):
                                break
                            addSpacesAtTheBegginig += StrReplace(A_LoopField32, "}", culyCloseFix)
                    resultOut += addSpacesAtTheBegginig + culyCloseFix + " else " + culyOpenFix + "\n"
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
    fixResultFIX = ""
    if (langToConvertTo == langFileExtension_2 and modeCurlyBracesOn == 1):
        items34 = LoopParseFunc(result, "\n", "\r")
        for A_Index34 , A_LoopField34 in enumerate(items34, start=0):
            if (Trim(A_LoopField34) == "}"):
                fixResultFIX += StrReplace(A_LoopField34, "}", culyCloseFix) + "\n"
            else:
                fixResultFIX += A_LoopField34 + "\n"
        result = StringTrimRight(fixResultFIX, 1)
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
    items35 = LoopParseFunc(fullARRAYstr, "|")
    for A_Index35 , A_LoopField35 in enumerate(items35, start=0):
        if (Trim(A_LoopField35) != ""):
            outFormatHELP1 = StrSplit(A_LoopField35, ":", 1)
            outFormatHELP2 = StrSplit(A_LoopField35, ":", 2)
            items36 = LoopParseFunc(outFormatHELP2, ",")
            for A_Index36 , A_LoopField36 in enumerate(items36, start=0):
                outFormat += outFormatHELP1 + "." + A_LoopField36 + "|"
    outFormat = StringTrimRight(outFormat, 1)
    items37 = LoopParseFunc(outFormat, "|")
    for A_Index37 , A_LoopField37 in enumerate(items37, start=0):
        if (Trim(A_LoopField37) != ""):
            if (StrSplit(Trim(A_LoopField37), "[", 1) == Trim(FromPath)):
                outType = StrSplit(Trim(A_LoopField37), "[", 2)
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
    items38 = LoopParseFunc(THESTR, ".")
    for A_Index38 , A_LoopField38 in enumerate(items38, start=0):
        count12345 = count12345 + 1
    items39 = LoopParseFunc(THESTR, ".")
    for A_Index39 , A_LoopField39 in enumerate(items39, start=0):
        if (count12345 == A_Index39):
            break
        else:
            THESTRout += Trim(A_LoopField39) + "."
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
    items40 = LoopParseFunc(theSringOSPlineARRAYstrstrSTR, "|")
    for A_Index40 , A_LoopField40 in enumerate(items40, start=0):
        if (Trim(StrSplit(A_LoopField40, ":", 1)) == Trim(ALoopField)):
            return STR(A_Index40)
    return "0"
def parserOSPgloabl(theSringOSPline, str123):
    str_1 = ""
    str_2 = ""
    str_3 = ""
    str_4 = ""
    str_5 = ""
    str_6 = ""
    HELPHoldOSPdethodNamePath = ""
    items41 = LoopParseFunc(theSringOSPline, "|")
    for A_Index41 , A_LoopField41 in enumerate(items41, start=0):
        str_1 += Trim(StrSplit(A_LoopField41, ":", 1)) + "\n"
        str_5 = Trim(StrSplit(A_LoopField41, ":", 1))
        str_6 = Trim(StrSplit(A_LoopField41, ":", 2))
        items42 = LoopParseFunc(str_6, ",")
        for A_Index42 , A_LoopField42 in enumerate(items42, start=0):
            str_1 += str_5 + "." + Trim(StrSplit(A_LoopField42, "[", 1)) + "[" + STR(A_Index42) + "]\n"
    str_1 += StrReplace(HELPHoldOSPdethodNamePath, "|", "\n")
    shortestLine = ""
    currentLine = ""
    currentLength = 0
    minLength = 0
    tempStr = ""
    # Sorting by repeatedly finding and appending the shortest line
    for A_Index43 , value in enumerate(iter(int, 1), start=0):
        # Initialize variables to track the shortest line in this pass
        shortestLine = ""
        minLength = 999999
        # Find the shortest line in str_1
        items44 = LoopParseFunc(str_1, "\n", "\r")
        for A_Index44 , A_LoopField44 in enumerate(items44, start=0):
            currentLine = A_LoopField44
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
        items45 = LoopParseFunc(str_1, "\n", "\r")
        for A_Index45 , A_LoopField45 in enumerate(items45, start=0):
            if (A_LoopField45 != shortestLine):
                tempStr += A_LoopField45 + "\n"
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
    items46 = LoopParseFunc(str_2, "\n", "\r")
    for A_Index46 , A_LoopField46 in enumerate(items46, start=0):
        lineCount = lineCount + 1
    # Reverse the order by re-parsing and appending lines in reverse order
    for A_Index47 in range(0, lineCount + 0):
        # Inner loop to find the (lineCount - A_Index47 + 1)-th line
        index = lineCount - A_Index47 + 1
        currentLine = ""
        lineNum = 0
        items48 = LoopParseFunc(str_2, "\n", "\r")
        for A_Index48 , A_LoopField48 in enumerate(items48, start=0):
            lineNum = lineNum + 1
            if (lineNum == index):
                currentLine = A_LoopField48
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
    items49 = LoopParseFunc(str_2, "\n", "\r")
    for A_Index49 , A_LoopField49 in enumerate(items49, start=0):
        if (SubStr(A_LoopField49, 1, StrLen(keyWordFunc)) != keyWordFunc):
            if (langToConvertTo == "cpp"):
                if (Trim(A_LoopField49) != ""):
                    if (InStr(str123, " += ")):
                        str6 = " += "
                        str1 = ""
                        str2 = ""
                        str3 = ""
                        str4 = ""
                        str5 = ""
                        str1 = Trim(StrSplit(str123, str6, 1))
                        str2 = Trim(StrSplit(str123, str6, 2))
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49))
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49))
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49))
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49))
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49))
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49))
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49))
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49))
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
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49))
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49))
                        str5 = str3 + str6 + str4
                        str123 = Trim(str5)
                    else:
                        str123 = replaceTheOSPpathsRIGHT(str123, A_LoopField49)
                    #;;;;
            else:
                if (Trim(A_LoopField49) != ""):
                    str123 = replaceTheOSPpathsPY_JS(str123, A_LoopField49)
    return str123
def isLineAconstruct(line):
    if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF)):
        return True
    elif (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf)):
        return True
    elif (StrLower(Trim(line)) == StrLower(keyWordElse) or StrLower(Trim(line)) == StrLower(keyWordElse + ":")):
        return True
    elif (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordElse))) == keyWordCurlyBraceClose + " " + StrLower(keyWordElse)):
        return True
    elif (SubStr(Trim(line), 1, StrLen(StrLower(keyWordElse) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordElse) + " " + keyWordCurlyBraceOpen):
        return True
    elif (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)):
        return True
    elif (StrLower(Trim(line)) == StrLower(keyWordLoopInfinite) or StrLower(Trim(line)) == StrLower(keyWordLoopInfinite + ":")):
        return True
    elif (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordLoopInfinite))) == keyWordCurlyBraceClose + " " + StrLower(keyWordLoopInfinite)):
        return True
    elif (SubStr(Trim(line), 1, StrLen(StrLower(keyWordLoopInfinite) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordLoopInfinite) + " " + keyWordCurlyBraceOpen):
        return True
    elif (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop)):
        return True
    elif (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)):
        return True
    elif (StrLower(Trim(line)) == StrLower(keyWordTry) or StrLower(Trim(line)) == StrLower(keyWordTry + ":")):
        return True
    elif (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordTry))) == keyWordCurlyBraceClose + " " + StrLower(keyWordTry)):
        return True
    elif (SubStr(Trim(line), 1, StrLen(StrLower(keyWordTry) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordTry) + " " + keyWordCurlyBraceOpen):
        return True
    elif (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance)):
        return True
    elif (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordCrew))) == StrLower(keyWordCrew)):
        return True
    elif (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordDefObj))) == StrLower(keyWordDefObj)):
        return True
    elif (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordMethod))) == StrLower(keyWordMethod)):
        return True
    elif (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)):
        return True
    elif (StrLower(Trim(line)) == StrLower(keyWordFinally) or StrLower(Trim(line)) == StrLower(keyWordFinally + ":")):
        return True
    elif (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordFinally))) == keyWordCurlyBraceClose + " " + StrLower(keyWordFinally)):
        return True
    elif (SubStr(Trim(line), 1, StrLen(StrLower(keyWordFinally) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordFinally) + " " + keyWordCurlyBraceOpen):
        return True
    elif (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc)):
        return True
    return False
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
def fixDoubleQuotes(line, isLast):
    out = ""
    if (isLast == 0):
        out = StrReplace(line, Chr(92) + Chr(92) + Chr(34), Chr(92) + Chr(34))
    else:
        line = StringTrimRight(line, 1)
        out = StrReplace(line, Chr(92) + Chr(92) + Chr(34), Chr(92) + Chr(34)) + Chr(34)
    return out
def fixArray1234(line):
    out = ""
    started = 0
    items50 = LoopParseFunc(line)
    for A_Index50 , A_LoopField50 in enumerate(items50, start=0):
        if (started == 1):
            if (StrLen(line) == A_Index50 + 1):
                return out
            out += A_LoopField50
        if (A_LoopField50 == "("):
            started = 1
    return out
def fixArray123(line, arrayMethodStr, mode):
    # mode 1 = Append
    # mode 2 = Pop
    # mode 3 = Size
    # mode 4 = Insert
    # mode 5 = Remove
    # mode 6 = IndexOf
    # HTVM_Append
    # HTVM_Pop
    # HTVM_Size
    # HTVM_Insert
    # HTVM_Remove
    # HTVM_IndexOf
    if (langToConvertTo != "swift"):
        if (mode == 1):
            return "HTVM_Append(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")"
        if (mode == 2):
            return "HTVM_Pop(" + StrSplit(line, ".", 1) + ")"
        if (mode == 3):
            return "HTVM_Size(" + StrSplit(line, ".", 1) + ")"
        if (mode == 4):
            return "HTVM_Insert(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")"
        if (mode == 5):
            return "HTVM_Remove(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")"
        if (mode == 6):
            return "HTVM_IndexOf(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")"
    else:
        if (mode == 1):
            return "HTVM_Append(&" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")"
        if (mode == 2):
            return "HTVM_Pop(&" + StrSplit(line, ".", 1) + ")"
        if (mode == 3):
            return "HTVM_Size(" + StrSplit(line, ".", 1) + ")"
        if (mode == 4):
            return "HTVM_Insert(&" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")"
        if (mode == 5):
            return "HTVM_Remove(&" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")"
        if (mode == 6):
            return "HTVM_IndexOf(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")"
    return line
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
def arrayParserTranspiler1(line, arrayMethodStr, mode):
    if (InStr(line, arrayMethodStr) == False):
        return line
    out = ""
    allDelimiters = " ()[],;:'!&|=<>+-*/^%~" + Chr(34) + Chr(9) + Chr(11)
    arrAll = []
    items51 = LoopParseFunc(line)
    for A_Index51 , A_LoopField51 in enumerate(items51, start=0):
        arrAll.append(A_LoopField51)
    i1 = 0
    tempHold = ""
    holdPos = 0
    holdPositions = []
    for A_Index52 in range(0, len(arrAll) + 0):
        tempHold = ""
        if (len(arrAll) - StrLen(arrayMethodStr) + 1 == i1):
            break
        for A_Index53 in range(0, StrLen(arrayMethodStr) + 0):
            tempHold += arrAll[A_Index53 + i1]
        i1 = i1 + 1
        #print(tempHold)
        if (tempHold == arrayMethodStr):
            holdPos = i1
            #print(holdPos)
            holdPositions.append(holdPos)
    #print("===========================================")
    holdPositionsTEMP = 0
    for A_Index54 in range(0, len(holdPositions) + 0):
        holdPositionsTEMP = holdPositions[A_Index54]
        i1 = len(arrAll)
        tempHold = ""
        for A_Index55 in range(0, len(arrAll) + 0):
            if (holdPositionsTEMP >= i1 + 1):
                if (InStr(allDelimiters, arrAll[i1]) == False):
                    tempHold += arrAll[i1 - 1]
                else:
                    break
            i1 = i1 - 1
        #print(await StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", ""))))
        holdPositions[A_Index54] = holdPositions[A_Index54] - StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", "")))
    #;;;;;;;;;;;;;;;;;;
    foundFirstParenthesis = 0
    ParenthesisStackOPEN = 0
    ParenthesisStackCLOSE = 0
    holdPositionsEnd = []
    holdPositionsTEMP = 0
    for A_Index56 in range(0, len(holdPositions) + 0):
        holdPositionsTEMP = holdPositions[A_Index56]
        i1 = 0
        tempHold = ""
        foundFirstParenthesis = 0
        ParenthesisStackOPEN = 0
        ParenthesisStackCLOSE = 0
        for A_Index57 in range(0, len(arrAll) + 0):
            if (holdPositionsTEMP < i1 + 1):
                if (arrAll[i1] == "("):
                    foundFirstParenthesis = 1
                if (arrAll[i1] == "(" and foundFirstParenthesis == 1):
                    ParenthesisStackOPEN = ParenthesisStackOPEN + 1
                if (arrAll[i1] == ")" and foundFirstParenthesis == 1):
                    ParenthesisStackCLOSE = ParenthesisStackCLOSE + 1
                tempHold += arrAll[i1 - 1]
                if (ParenthesisStackOPEN == ParenthesisStackCLOSE and foundFirstParenthesis == 1):
                    tempHold += arrAll[i1]
                    holdPositionsEnd.append(i1 + 1)
                    break
            i1 = i1 + 1
        #print(tempHold)
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    startPosReplace = 0
    endPosReplace = 0
    beenInside = 0
    holdDebug = ""
    holdDebugLen = 0
    canOut = 1
    for A_Index58 in range(0, len(holdPositions) + 0):
        startPosReplace = holdPositions[len(holdPositions) - A_Index58 - 1]
        endPosReplace = holdPositionsEnd[len(holdPositions) - A_Index58 - 1]
        holdDebug = ""
        beenInside = 0
        holdDebugLen = 0
        canOut = 1
        items59 = LoopParseFunc(line)
        for A_Index59 , A_LoopField59 in enumerate(items59, start=0):
            if (A_Index59 + 1 >= startPosReplace and A_Index59 + 1 <= endPosReplace):
                holdDebug += A_LoopField59
        holdDebugLen = StrLen(holdDebug)
        items60 = LoopParseFunc(line)
        for A_Index60 , A_LoopField60 in enumerate(items60, start=0):
            if (A_Index60 + 1 >= startPosReplace and A_Index60 + 1 <= endPosReplace):
                beenInside = beenInside + 1
            if (beenInside == 1):
                out += fixArray123(holdDebug, arrayMethodStr, mode)
                canOut = 0
            else:
                if (canOut == 0):
                    holdDebugLen = holdDebugLen - 1
                    if (holdDebugLen == 0):
                        canOut = 1
                if (canOut == 1):
                    out += A_LoopField60
        #print("|" . holdDebug . "|")
        line = out
        out = ""
    return line
def arrayParserTranspiler(line):
    # mode 1 = Append
    # mode 2 = Pop
    # mode 3 = Size
    # mode 4 = Insert
    # mode 5 = Remove
    # mode 6 = IndexOf
    if (langToConvertTo == langFileExtension_2):
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayAppend + "(", "." + keyWordArrayAppend_2 + "(")
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayPop + "(", "." + keyWordArrayPop_2 + "(")
        line = HTVMmatchStrRrplace(line, "." + keyWordArraySize + "(", "." + keyWordArraySize_2 + "(")
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayInsert + "(", "." + keyWordArrayInsert_2 + "(")
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayRemove + "(", "." + keyWordArrayRemove_2 + "(")
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayIndexOf + "(", "." + keyWordArrayIndexOf_2 + "(")
    else:
        line = arrayParserTranspiler1(line, keyWordArrayAppend + "(", 1)
        line = arrayParserTranspiler1(line, keyWordArrayPop + "(", 2)
        line = arrayParserTranspiler1(line, keyWordArraySize + "(", 3)
        line = arrayParserTranspiler1(line, keyWordArrayInsert + "(", 4)
        line = arrayParserTranspiler1(line, keyWordArrayRemove + "(", 5)
        line = arrayParserTranspiler1(line, keyWordArrayIndexOf + "(", 6)
    return line
def getFuncTypeConvert(type):
    theType = ""
    type = Trim(type)
    if (langToConvertTo == "cpp"):
        if (type == keyWordVoid):
            theType = "void"
        if (type == keyWordDouble):
            theType = "double"
        if (type == keyWordChar):
            theType = "char"
        if (type == keyWordUint8):
            theType = "uint8_t"
        if (type == keyWordUint16):
            theType = "uint16_t"
        if (type == keyWordUint32):
            theType = "uint32_t"
        if (type == keyWordUint64):
            theType = "uint64_t"
        if (type == keyWordINT):
            theType = "int"
        if (type == keyWordSTR):
            theType = "std::string"
        if (type == keyWordBOOL):
            theType = "bool"
        if (type == keyWordFLOAT):
            theType = "float"
        if (type == keyWordINT8):
            theType = "int8_t"
        if (type == keyWordINT16):
            theType = "int16_t"
        if (type == keyWordINT32):
            theType = "int32_t"
        if (type == keyWordINT64):
            theType = "int64_t"
        if (type == keyWordArrayDefinition):
            theType = "std::vector<void>"
        if (type == keyWordArrayOfIntegersDefinition):
            theType = "std::vector<int>"
        if (type == keyWordArrayOfStringsDefinition):
            theType = "std::vector<std::string>"
        if (type == keyWordArrayOfFloatingPointNumbersDefinition):
            theType = "std::vector<float>"
        if (type == keyWordArrayOfBooleansDefinition):
            theType = "std::vector<bool>"
    if (langToConvertTo == "py"):
        theType = ""
    if (langToConvertTo == "js"):
        theType = ""
    if (langToConvertTo == "go"):
        if (type == keyWordVoid):
            theType = ""
        if (type == keyWordDouble):
            theType = "float64"
        if (type == keyWordChar):
            theType = "byte"
        if (type == keyWordUint8):
            theType = "uint8"
        if (type == keyWordUint16):
            theType = "uint16"
        if (type == keyWordUint32):
            theType = "uint32"
        if (type == keyWordUint64):
            theType = "uint64"
        if (type == keyWordINT):
            theType = "int"
        if (type == keyWordSTR):
            theType = "string"
        if (type == keyWordBOOL):
            theType = "bool"
        if (type == keyWordFLOAT):
            theType = "float32"
        if (type == keyWordINT8):
            theType = "int8"
        if (type == keyWordINT16):
            theType = "int16"
        if (type == keyWordINT32):
            theType = "int32"
        if (type == keyWordINT64):
            theType = "int64"
        if (type == keyWordArrayDefinition):
            theType = "[]string"
        if (type == keyWordArrayOfIntegersDefinition):
            theType = "[]int"
        if (type == keyWordArrayOfStringsDefinition):
            theType = "[]string"
        if (type == keyWordArrayOfFloatingPointNumbersDefinition):
            theType = "[]float32"
        if (type == keyWordArrayOfBooleansDefinition):
            theType = "[]bool"
    if (langToConvertTo == "lua"):
        theType = ""
    if (langToConvertTo == "cs"):
        if (type == keyWordVoid):
            theType = "void"
        if (type == keyWordDouble):
            theType = "double"
        if (type == keyWordChar):
            theType = "char"
        if (type == keyWordUint8):
            theType = "byte"
        if (type == keyWordUint16):
            theType = "ushort"
        if (type == keyWordUint32):
            theType = "uint"
        if (type == keyWordUint64):
            theType = "ulong"
        if (type == keyWordINT):
            theType = "int"
        if (type == keyWordSTR):
            theType = "string"
        if (type == keyWordBOOL):
            theType = "bool"
        if (type == keyWordFLOAT):
            theType = "float"
        if (type == keyWordINT8):
            theType = "sbyte"
        if (type == keyWordINT16):
            theType = "short"
        if (type == keyWordINT32):
            theType = "int"
        if (type == keyWordINT64):
            theType = "long"
        if (type == keyWordArrayDefinition):
            theType = "List<string>"
        if (type == keyWordArrayOfIntegersDefinition):
            theType = "List<int>"
        if (type == keyWordArrayOfStringsDefinition):
            theType = "List<string>"
        if (type == keyWordArrayOfFloatingPointNumbersDefinition):
            theType = "List<float>"
        if (type == keyWordArrayOfBooleansDefinition):
            theType = "List<bool>"
    if (langToConvertTo == "java"):
        if (type == keyWordVoid):
            theType = "void"
        if (type == keyWordDouble):
            theType = "double"
        if (type == keyWordChar):
            theType = "char"
        if (type == keyWordUint8):
            theType = "byte "
        if (type == keyWordUint16):
            theType = "short"
        if (type == keyWordUint32):
            theType = "int"
        if (type == keyWordUint64):
            theType = "long"
        if (type == keyWordINT):
            theType = "int"
        if (type == keyWordSTR):
            theType = "String"
        if (type == keyWordBOOL):
            theType = "boolean"
        if (type == keyWordFLOAT):
            theType = "float"
        if (type == keyWordINT8):
            theType = "byte"
        if (type == keyWordINT16):
            theType = "short"
        if (type == keyWordINT32):
            theType = "int"
        if (type == keyWordINT64):
            theType = "long"
        if (type == keyWordArrayDefinition):
            theType = "ArrayList<String>"
        if (type == keyWordArrayOfIntegersDefinition):
            theType = "ArrayList<Integer>"
        if (type == keyWordArrayOfStringsDefinition):
            theType = "ArrayList<String>"
        if (type == keyWordArrayOfFloatingPointNumbersDefinition):
            theType = "ArrayList<Float>"
        if (type == keyWordArrayOfBooleansDefinition):
            theType = "ArrayList<Boolean>"
    if (langToConvertTo == "kt"):
        if (type == keyWordVoid):
            theType = ""
        if (type == keyWordDouble):
            theType = "Double"
        if (type == keyWordChar):
            theType = "Char"
        if (type == keyWordUint8):
            theType = "UByte"
        if (type == keyWordUint16):
            theType = "UShort"
        if (type == keyWordUint32):
            theType = "UInt"
        if (type == keyWordUint64):
            theType = "ULong"
        if (type == keyWordINT):
            theType = "Int"
        if (type == keyWordSTR):
            theType = "String"
        if (type == keyWordBOOL):
            theType = "Boolean"
        if (type == keyWordFLOAT):
            theType = "Float"
        if (type == keyWordINT8):
            theType = "Byte"
        if (type == keyWordINT16):
            theType = "Short"
        if (type == keyWordINT32):
            theType = "Int"
        if (type == keyWordINT64):
            theType = "Long"
        if (type == keyWordArrayDefinition):
            theType = "Array<String>"
        if (type == keyWordArrayOfIntegersDefinition):
            theType = "Array<Int>"
        if (type == keyWordArrayOfStringsDefinition):
            theType = "Array<String>"
        if (type == keyWordArrayOfFloatingPointNumbersDefinition):
            theType = "Array<Float>"
        if (type == keyWordArrayOfBooleansDefinition):
            theType = "Array<Boolean>"
    if (langToConvertTo == "rb"):
        theType = ""
    if (langToConvertTo == "nim"):
        if (type == keyWordVoid):
            theType = ""
        if (type == keyWordDouble):
            theType = "float"
        if (type == keyWordChar):
            theType = "char"
        if (type == keyWordUint8):
            theType = "uint8"
        if (type == keyWordUint16):
            theType = "uint16"
        if (type == keyWordUint32):
            theType = "uint32"
        if (type == keyWordUint64):
            theType = "uint64"
        if (type == keyWordINT):
            theType = "int"
        if (type == keyWordSTR):
            theType = "string"
        if (type == keyWordBOOL):
            theType = "bool"
        if (type == keyWordFLOAT):
            theType = "float"
        if (type == keyWordINT8):
            theType = "int8"
        if (type == keyWordINT16):
            theType = "int16"
        if (type == keyWordINT32):
            theType = "int32"
        if (type == keyWordINT64):
            theType = "int64"
        if (type == keyWordArrayDefinition):
            theType = "seq[string]"
        if (type == keyWordArrayOfIntegersDefinition):
            theType = "seq[int]"
        if (type == keyWordArrayOfStringsDefinition):
            theType = "seq[string]"
        if (type == keyWordArrayOfFloatingPointNumbersDefinition):
            theType = "seq[float64]"
        if (type == keyWordArrayOfBooleansDefinition):
            theType = "seq[bool]"
    if (langToConvertTo == "ahk"):
        theType = ""
    if (langToConvertTo == "swift"):
        if (type == keyWordVoid):
            theType = ""
        if (type == keyWordDouble):
            theType = "Double"
        if (type == keyWordChar):
            theType = "Character"
        if (type == keyWordUint8):
            theType = "UInt8"
        if (type == keyWordUint16):
            theType = "UInt16"
        if (type == keyWordUint32):
            theType = "UInt32"
        if (type == keyWordUint64):
            theType = "UInt64"
        if (type == keyWordINT):
            theType = "Int"
        if (type == keyWordSTR):
            theType = "String"
        if (type == keyWordBOOL):
            theType = "Bool"
        if (type == keyWordFLOAT):
            theType = "Float"
        if (type == keyWordINT8):
            theType = "Int8"
        if (type == keyWordINT16):
            theType = "Int16"
        if (type == keyWordINT32):
            theType = "Int32"
        if (type == keyWordINT64):
            theType = "Int64"
        if (type == keyWordArrayDefinition):
            theType = "[String]"
        if (type == keyWordArrayOfIntegersDefinition):
            theType = "[Int]"
        if (type == keyWordArrayOfStringsDefinition):
            theType = "[String]"
        if (type == keyWordArrayOfFloatingPointNumbersDefinition):
            theType = "[Float]"
        if (type == keyWordArrayOfBooleansDefinition):
            theType = "[Bool]"
    if (langToConvertTo == "dart"):
        if (type == keyWordVoid):
            theType = "void"
        if (type == keyWordDouble):
            theType = "double"
        if (type == keyWordChar):
            theType = "String"
        if (type == keyWordUint8):
            theType = "int"
        if (type == keyWordUint16):
            theType = "int"
        if (type == keyWordUint32):
            theType = "int"
        if (type == keyWordUint64):
            theType = "int"
        if (type == keyWordINT):
            theType = "int"
        if (type == keyWordSTR):
            theType = "String"
        if (type == keyWordBOOL):
            theType = "bool"
        if (type == keyWordFLOAT):
            theType = "double"
        if (type == keyWordINT8):
            theType = "int"
        if (type == keyWordINT16):
            theType = "int"
        if (type == keyWordINT32):
            theType = "int"
        if (type == keyWordINT64):
            theType = "int"
        if (type == keyWordArrayDefinition):
            theType = "List<String>"
        if (type == keyWordArrayOfIntegersDefinition):
            theType = "List<int>"
        if (type == keyWordArrayOfStringsDefinition):
            theType = "List<String>"
        if (type == keyWordArrayOfFloatingPointNumbersDefinition):
            theType = "List<double>"
        if (type == keyWordArrayOfBooleansDefinition):
            theType = "List<bool>"
    if (langToConvertTo == "ts"):
        if (type == keyWordVoid):
            theType = "void"
        if (type == keyWordDouble):
            theType = "number"
        if (type == keyWordChar):
            theType = "string"
        if (type == keyWordUint8):
            theType = "number"
        if (type == keyWordUint16):
            theType = "number"
        if (type == keyWordUint32):
            theType = "number"
        if (type == keyWordUint64):
            theType = "bigint"
        if (type == keyWordINT):
            theType = "number"
        if (type == keyWordSTR):
            theType = "string"
        if (type == keyWordBOOL):
            theType = "boolean"
        if (type == keyWordFLOAT):
            theType = "number"
        if (type == keyWordINT8):
            theType = "number"
        if (type == keyWordINT16):
            theType = "number"
        if (type == keyWordINT32):
            theType = "number"
        if (type == keyWordINT64):
            theType = "bigint"
        if (type == keyWordArrayDefinition):
            theType = "string[]"
        if (type == keyWordArrayOfIntegersDefinition):
            theType = "number[]"
        if (type == keyWordArrayOfStringsDefinition):
            theType = "string[]"
        if (type == keyWordArrayOfFloatingPointNumbersDefinition):
            theType = "number[]"
        if (type == keyWordArrayOfBooleansDefinition):
            theType = "boolean[]"
    if (langToConvertTo == "groovy"):
        theType = ""
    if (langToConvertTo == langFileExtension_2):
        # keyWordVoid
        # keyWordDouble
        # keyWordChar
        # keyWordUint8
        # keyWordUint16
        # keyWordUint32
        # keyWordUint64
        # keyWordINT
        # keyWordSTR
        # keyWordBOOL
        # keyWordFLOAT
        # keyWordINT8
        # keyWordINT16
        # keyWordINT32
        # keyWordINT64
        # keyWordArrayDefinition
        # keyWordArrayOfIntegersDefinition
        # keyWordArrayOfStringsDefinition
        # keyWordArrayOfFloatingPointNumbersDefinition
        # keyWordArrayOfBooleansDefinition
        if (type == keyWordVoid):
            theType = keyWordVoid_2
        if (type == keyWordDouble):
            theType = keyWordDouble_2
        if (type == keyWordChar):
            theType = keyWordChar_2
        if (type == keyWordUint8):
            theType = keyWordUint8_2
        if (type == keyWordUint16):
            theType = keyWordUint16_2
        if (type == keyWordUint32):
            theType = keyWordUint32_2
        if (type == keyWordUint64):
            theType = keyWordUint64_2
        if (type == keyWordINT):
            theType = keyWordINT_2
        if (type == keyWordSTR):
            theType = keyWordSTR_2
        if (type == keyWordBOOL):
            theType = keyWordBOOL_2
        if (type == keyWordFLOAT):
            theType = keyWordFLOAT_2
        if (type == keyWordINT8):
            theType = keyWordINT8_2
        if (type == keyWordINT16):
            theType = keyWordINT16_2
        if (type == keyWordINT32):
            theType = keyWordINT32_2
        if (type == keyWordINT64):
            theType = keyWordINT64_2
        if (type == keyWordArrayDefinition):
            theType = keyWordArrayDefinition_2
        if (type == keyWordArrayOfIntegersDefinition):
            theType = keyWordArrayOfIntegersDefinition_2
        if (type == keyWordArrayOfStringsDefinition):
            theType = keyWordArrayOfStringsDefinition_2
        if (type == keyWordArrayOfFloatingPointNumbersDefinition):
            theType = keyWordArrayOfFloatingPointNumbersDefinition_2
        if (type == keyWordArrayOfBooleansDefinition):
            theType = keyWordArrayOfBooleansDefinition_2
    return theType
def getTheLastWord(line):
    if (InStr(Trim(line), " ") == False):
        return line
    outNum = 0
    items61 = LoopParseFunc(line, " ")
    for A_Index61 , A_LoopField61 in enumerate(items61, start=0):
        outNum = outNum + 1
    items62 = LoopParseFunc(line, " ")
    for A_Index62 , A_LoopField62 in enumerate(items62, start=0):
        if (outNum == A_Index62 + 1):
            return A_LoopField62
    return line
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
def  GETfullLangAllOperators():
    fullLangAllOperators = []
    if (langToConvertTo == "cpp"):
        fullLangAllOperators.append("nullptr")
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("&&")
        fullLangAllOperators.append("||")
        fullLangAllOperators.append("!")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("|")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("~")
        fullLangAllOperators.append("<<")
        fullLangAllOperators.append(">>")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == "py"):
        fullLangAllOperators.append("None")
        fullLangAllOperators.append("True")
        fullLangAllOperators.append("False")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("**")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("is")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("and")
        fullLangAllOperators.append("or")
        fullLangAllOperators.append("not")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("|")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("~")
        fullLangAllOperators.append("<<")
        fullLangAllOperators.append(">>")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == "js"):
        fullLangAllOperators.append("null")
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("**")
        if (useJavaScriptAlwaysTripleEqual == "on"):
            fullLangAllOperators.append("===")
        else:
            fullLangAllOperators.append("==")
        fullLangAllOperators.append("===")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("&&")
        fullLangAllOperators.append("||")
        fullLangAllOperators.append("!")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("|")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("~")
        fullLangAllOperators.append("<<")
        fullLangAllOperators.append(">>")
        fullLangAllOperators.append(">>>")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == "go"):
        fullLangAllOperators.append("nil")
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("&&")
        fullLangAllOperators.append("||")
        fullLangAllOperators.append("!")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("|")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("<<")
        fullLangAllOperators.append(">>")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR")
    if (langToConvertTo == "lua"):
        fullLangAllOperators.append("nil")
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append("..")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("~=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("and")
        fullLangAllOperators.append("or")
        fullLangAllOperators.append("not")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("|")
        fullLangAllOperators.append("~")
        fullLangAllOperators.append("~")
        fullLangAllOperators.append("<<")
        fullLangAllOperators.append(">>")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == "cs"):
        fullLangAllOperators.append("null")
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("&&")
        fullLangAllOperators.append("||")
        fullLangAllOperators.append("!")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("|")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("~")
        fullLangAllOperators.append("<<")
        fullLangAllOperators.append(">>")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == "java"):
        fullLangAllOperators.append("null")
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("&&")
        fullLangAllOperators.append("||")
        fullLangAllOperators.append("!")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("|")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("~")
        fullLangAllOperators.append("<<")
        fullLangAllOperators.append(">>")
        fullLangAllOperators.append(">>>")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == "kt"):
        fullLangAllOperators.append("null")
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("===")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("&&")
        fullLangAllOperators.append("||")
        fullLangAllOperators.append("!")
        fullLangAllOperators.append("and")
        fullLangAllOperators.append("or")
        fullLangAllOperators.append("xor")
        fullLangAllOperators.append("inv")
        fullLangAllOperators.append("shl")
        fullLangAllOperators.append("shr")
        fullLangAllOperators.append("ushr")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == "rb"):
        fullLangAllOperators.append("nil")
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("**")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("&&")
        fullLangAllOperators.append("||")
        fullLangAllOperators.append("!")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("|")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("~")
        fullLangAllOperators.append("<<")
        fullLangAllOperators.append(">>")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == "nim"):
        fullLangAllOperators.append("nil")
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("and")
        fullLangAllOperators.append("or")
        fullLangAllOperators.append("not")
        fullLangAllOperators.append("and")
        fullLangAllOperators.append("or")
        fullLangAllOperators.append("xor")
        fullLangAllOperators.append("not")
        fullLangAllOperators.append("shl")
        fullLangAllOperators.append("shr")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == "ahk"):
        fullLangAllOperators.append(Chr(34) + "" + Chr(34))
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append(".")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("=")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("&&")
        fullLangAllOperators.append("||")
        fullLangAllOperators.append("!")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("|")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("~")
        fullLangAllOperators.append("<<")
        fullLangAllOperators.append(">>")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == "swift"):
        fullLangAllOperators.append("nil")
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("===")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("&&")
        fullLangAllOperators.append("||")
        fullLangAllOperators.append("!")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("|")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("~")
        fullLangAllOperators.append("<<")
        fullLangAllOperators.append(">>")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == "dart"):
        fullLangAllOperators.append("null")
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("===")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("&&")
        fullLangAllOperators.append("||")
        fullLangAllOperators.append("!")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("|")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("~")
        fullLangAllOperators.append("<<")
        fullLangAllOperators.append(">>")
        fullLangAllOperators.append(">>>")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == "ts"):
        fullLangAllOperators.append("null")
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("**")
        if (useJavaScriptAlwaysTripleEqual == "on"):
            fullLangAllOperators.append("===")
        else:
            fullLangAllOperators.append("==")
        fullLangAllOperators.append("===")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("&&")
        fullLangAllOperators.append("||")
        fullLangAllOperators.append("!")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("|")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("~")
        fullLangAllOperators.append("<<")
        fullLangAllOperators.append(">>")
        fullLangAllOperators.append(">>>")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == "groovy"):
        fullLangAllOperators.append("null")
        fullLangAllOperators.append("true")
        fullLangAllOperators.append("false")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("+")
        fullLangAllOperators.append("-")
        fullLangAllOperators.append("*")
        fullLangAllOperators.append("/")
        fullLangAllOperators.append("%")
        fullLangAllOperators.append("**")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("==")
        fullLangAllOperators.append("!=")
        fullLangAllOperators.append(">")
        fullLangAllOperators.append("<")
        fullLangAllOperators.append(">=")
        fullLangAllOperators.append("<=")
        fullLangAllOperators.append("&&")
        fullLangAllOperators.append("||")
        fullLangAllOperators.append("!")
        fullLangAllOperators.append("&")
        fullLangAllOperators.append("|")
        fullLangAllOperators.append("^")
        fullLangAllOperators.append("~")
        fullLangAllOperators.append("<<")
        fullLangAllOperators.append(">>")
        fullLangAllOperators.append(">>>")
        fullLangAllOperators.append("?")
        fullLangAllOperators.append(":")
    if (langToConvertTo == langFileExtension_2):
        fullLangAllOperators.append(keyWordNull_2)
        fullLangAllOperators.append(keyWordTrue_2)
        fullLangAllOperators.append(keyWordFalse_2)
        fullLangAllOperators.append(keyWordConcat_2)
        fullLangAllOperators.append(keyWordAdd_2)
        fullLangAllOperators.append(keyWordSub_2)
        fullLangAllOperators.append(keyWordMul_2)
        fullLangAllOperators.append(keyWordDiv_2)
        fullLangAllOperators.append(keyWordMod_2)
        fullLangAllOperators.append(keyWordExp_2)
        fullLangAllOperators.append(keyWordEqual_2)
        fullLangAllOperators.append(keyWordStrictEqual_2)
        fullLangAllOperators.append(keyWordNotEqual_2)
        fullLangAllOperators.append(keyWordGreater_2)
        fullLangAllOperators.append(keyWordLess_2)
        fullLangAllOperators.append(keyWordGreaterEqual_2)
        fullLangAllOperators.append(keyWordLessEqual_2)
        fullLangAllOperators.append(keyWordAnd_2)
        fullLangAllOperators.append(keyWordOr_2)
        fullLangAllOperators.append(keyWordNot_2)
        fullLangAllOperators.append(keyWordBitAnd_2)
        fullLangAllOperators.append(keyWordBitOr_2)
        fullLangAllOperators.append(keyWordBitXor_2)
        fullLangAllOperators.append(keyWordBitNot_2)
        fullLangAllOperators.append(keyWordShiftLeft_2)
        fullLangAllOperators.append(keyWordShiftRight_2)
        fullLangAllOperators.append(keyWordShiftUnsignedRight_2)
        fullLangAllOperators.append(keyWordTernary1_2)
        fullLangAllOperators.append(keyWordTernary2_2)
    return fullLangAllOperators
def  GETfullLangAllOperators_HELP():
    fullLangAllOperators_HELP = []
    fullLangAllOperators_HELP.append(keyWordNull)
    fullLangAllOperators_HELP.append(keyWordTrue)
    fullLangAllOperators_HELP.append(keyWordFalse)
    fullLangAllOperators_HELP.append(keyWordConcat)
    fullLangAllOperators_HELP.append(keyWordAdd)
    fullLangAllOperators_HELP.append(keyWordSub)
    fullLangAllOperators_HELP.append(keyWordMul)
    fullLangAllOperators_HELP.append(keyWordDiv)
    fullLangAllOperators_HELP.append(keyWordMod)
    fullLangAllOperators_HELP.append(keyWordExp)
    fullLangAllOperators_HELP.append(keyWordEqual)
    fullLangAllOperators_HELP.append(keyWordStrictEqual)
    fullLangAllOperators_HELP.append(keyWordNotEqual)
    fullLangAllOperators_HELP.append(keyWordGreater)
    fullLangAllOperators_HELP.append(keyWordLess)
    fullLangAllOperators_HELP.append(keyWordGreaterEqual)
    fullLangAllOperators_HELP.append(keyWordLessEqual)
    fullLangAllOperators_HELP.append(keyWordAnd)
    fullLangAllOperators_HELP.append(keyWordOr)
    fullLangAllOperators_HELP.append(keyWordNot)
    fullLangAllOperators_HELP.append(keyWordBitAnd)
    fullLangAllOperators_HELP.append(keyWordBitOr)
    fullLangAllOperators_HELP.append(keyWordBitXor)
    fullLangAllOperators_HELP.append(keyWordBitNot)
    fullLangAllOperators_HELP.append(keyWordShiftLeft)
    fullLangAllOperators_HELP.append(keyWordShiftRight)
    fullLangAllOperators_HELP.append(keyWordShiftUnsignedRight)
    fullLangAllOperators_HELP.append(keyWordTernary1)
    fullLangAllOperators_HELP.append(keyWordTernary2)
    return fullLangAllOperators_HELP
def expressionParserTranspiler(expression):
    fixExpertionLineFuncOnlyTEXT_func = ""
    fixExpertionLineFuncOnlyTEXT_numDelete = 0
    if (fixExpertionLineFuncOnly == 1):
        fixExpertionLineFuncOnlyTEXT_func = StrSplit(expression, "(", 1)
        fixExpertionLineFuncOnlyTEXT_numDelete = StrLen(fixExpertionLineFuncOnlyTEXT_func) + 1
        expression = StringTrimLeft(expression, fixExpertionLineFuncOnlyTEXT_numDelete)
    if (langToConvertTo != "js" and langToConvertTo != "ts" and langToConvertTo != langFileExtension_2):
        expression = RegExReplace(expression, "\\b" + keyWordAwait + "\\b", "")
    for A_Index63 in range(0, 29 + 0):
        if (InStr(expression, fullLangAllOperators_HELP[A_Index63])):
            if (A_Index63 == 0 or A_Index63 == 1 or A_Index63 == 2):
                expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index63] + "\\b", fullLangAllOperators[A_Index63])
            else:
                if (A_Index63 == 19):
                    if (langToConvertTo == "py" or langToConvertTo == "lua" or langToConvertTo == "nim"):
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index63] + "\\b", "not")
                    else:
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index63] + "\\b", "!")
                    if (langToConvertTo == "py" or langToConvertTo == "lua" or langToConvertTo == "nim"):
                        expression = RegExReplace(expression, "!([\\w]+)", "not $1")
                    expression = StrReplace(expression, " not= ", " != ")
                else:
                    expression = StrReplace(expression, " " + fullLangAllOperators_HELP[A_Index63] + " ", " " + fullLangAllOperators[A_Index63] + " ")
                    if (A_Index63 == 28):
                        if (langToConvertTo == "py"):
                            # Convert C-like ternary to Python ternary using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "$2 if $1 else $3")
                        if (langToConvertTo == "nim"):
                            # Convert C-like ternary to Nim ternary using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*)", "if $1: $2 else: $3")
                        if (langToConvertTo == "lua"):
                            # Convert C-like ternary to Lua ternary-like expression using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "$1 and $2 or $3")
                        if (langToConvertTo == "kt"):
                            # Convert C-like ternary to Kotlin ternary-like expression using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "if $1 $2 else $3")
    if (langToConvertTo == "ahk"):
        if (InStr(expression, keyWordAIndex)):
            expression = RegExReplace(expression, "\\b" + keyWordAIndex + "\\b", "A_Index")
        if (InStr(expression, keyWordALoopField)):
            expression = RegExReplace(expression, "\\b" + keyWordALoopField + "\\b", "A_LoopField")
    if (langToConvertTo == langFileExtension_2):
        if (InStr(expression, keyWordAIndex)):
            expression = RegExReplace(expression, "\\b" + keyWordAIndex + "\\b", keyWordAIndex_2)
        if (InStr(expression, keyWordALoopField)):
            expression = RegExReplace(expression, "\\b" + keyWordALoopField + "\\b", keyWordALoopField_2)
    if (langToConvertTo != langFileExtension_2 and langToConvertTo != "ahk"):
        if (langToConvertTo == "py" or langToConvertTo == "lua" or langToConvertTo == "nim"):
            expression = StrReplace(expression, ") and (", " and ")
            expression = StrReplace(expression, ") or (", " or ")
        else:
            expression = StrReplace(expression, ") && (", " && ")
            expression = StrReplace(expression, ") || (", " || ")
    # extra for array methods
    expression = arrayParserTranspiler(expression)
    if (langToConvertTo == "cpp"):
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".what()")
    if (langToConvertTo == "js"):
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message")
    if (langToConvertTo == "cs"):
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".Message")
    if (langToConvertTo == "java"):
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".getMessage()")
    if (langToConvertTo == "kt"):
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message")
    if (langToConvertTo == "rb"):
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message")
    if (langToConvertTo == "nim"):
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".msg")
    if (langToConvertTo == "swift"):
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".localizedDescription")
    if (langToConvertTo == "ts"):
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message")
    if (langToConvertTo == "groovy"):
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message")
    if (fixExpertionLineFuncOnly == 1):
        expression = fixExpertionLineFuncOnlyTEXT_func + "(" + expression
    return expression
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
def compiler(htCode, allInstructionFile, mode, langToConvertToParam = ""):
    instructions = allInstructionFile
    items64 = LoopParseFunc(allInstructionFile, "\n", "\r")
    for A_Index64 , A_LoopField64 in enumerate(items64, start=0):
        if (A_Index64 == 0):
            langToConvertTo = Trim(A_LoopField64)
        if (A_Index64 == 1):
            langFileExtension = Trim(A_LoopField64)
        if (A_Index64 == 2):
            commands = Trim(A_LoopField64)
        if (A_Index64 == 3):
            keyWordAlliance = Trim(A_LoopField64) + " "
        if (A_Index64 == 4):
            keyWordCrew = Trim(A_LoopField64) + " "
        if (A_Index64 == 5):
            keyWordMethod = Trim(A_LoopField64) + " "
        if (A_Index64 == 6):
            keyWordDefObj = Trim(A_LoopField64) + " "
        if (A_Index64 == 7):
            keyWordPorp = Trim(A_LoopField64) + " "
        if (A_Index64 == 8):
            keyWordThis = Trim(A_LoopField64)
        if (A_Index64 == 9):
            keyWordInclude = Trim(A_LoopField64)
        if (A_Index64 == 10):
            keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField64)
        if (A_Index64 == 11):
            keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField64)
        if (A_Index64 == 12):
            keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField64)
        if (A_Index64 == 13):
            keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField64)
        if (A_Index64 == 14):
            keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField64)
        if (A_Index64 == 15):
            keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField64)
        if (A_Index64 == 16):
            keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField64)
        if (A_Index64 == 17):
            keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField64)
        if (A_Index64 == 18):
            keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField64)
        if (A_Index64 == 19):
            keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField64)
        if (A_Index64 == 20):
            keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField64)
        if (A_Index64 == 21):
            keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField64)
        if (A_Index64 == 22):
            keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField64)
        if (A_Index64 == 23):
            keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField64)
        if (A_Index64 == 24):
            keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField64)
        if (A_Index64 == 25):
            keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField64)
        if (A_Index64 == 26):
            keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField64)
        if (A_Index64 == 27):
            keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField64)
        if (A_Index64 == 28):
            keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField64)
        if (A_Index64 == 29):
            keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField64)
        if (A_Index64 == 30):
            keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField64)
        if (A_Index64 == 31):
            keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField64)
        if (A_Index64 == 32):
            keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField64)
        if (A_Index64 == 33):
            keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField64)
        if (A_Index64 == 34):
            keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField64)
        if (A_Index64 == 35):
            keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField64)
        if (A_Index64 == 36):
            keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField64)
        if (A_Index64 == 37):
            keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField64)
        if (A_Index64 == 38):
            keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField64)
        if (A_Index64 == 39):
            keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField64)
        if (A_Index64 == 40):
            keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField64)
        if (A_Index64 == 41):
            keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField64)
        if (A_Index64 == 42):
            keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField64)
        if (A_Index64 == 43):
            keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField64)
        if (A_Index64 == 44):
            keyWordCodeInHTVMstart = Trim(A_LoopField64)
        if (A_Index64 == 45):
            keyWordCodeInHTVMend = Trim(A_LoopField64)
        if (A_Index64 == 46):
            keyWordCurlyBraceOpen = Trim(A_LoopField64)
        if (A_Index64 == 47):
            keyWordCurlyBraceClose = Trim(A_LoopField64)
        if (A_Index64 == 48):
            keyWordNull = Trim(A_LoopField64)
        if (A_Index64 == 49):
            keyWordTrue = Trim(A_LoopField64)
        if (A_Index64 == 50):
            keyWordFalse = Trim(A_LoopField64)
        if (A_Index64 == 51):
            keyWordVoid = Trim(A_LoopField64)
        if (A_Index64 == 52):
            keyWordDouble = Trim(A_LoopField64)
        if (A_Index64 == 53):
            keyWordChar = Trim(A_LoopField64)
        if (A_Index64 == 54):
            keyWordUint8 = Trim(A_LoopField64)
        if (A_Index64 == 55):
            keyWordUint16 = Trim(A_LoopField64)
        if (A_Index64 == 56):
            keyWordUint32 = Trim(A_LoopField64)
        if (A_Index64 == 57):
            keyWordUint64 = Trim(A_LoopField64)
        if (A_Index64 == 58):
            keyWordINT = Trim(A_LoopField64)
        if (A_Index64 == 59):
            keyWordSTR = Trim(A_LoopField64)
        if (A_Index64 == 60):
            keyWordBOOL = Trim(A_LoopField64)
        if (A_Index64 == 61):
            keyWordFLOAT = Trim(A_LoopField64)
        if (A_Index64 == 62):
            keyWordINT8 = Trim(A_LoopField64)
        if (A_Index64 == 63):
            keyWordINT16 = Trim(A_LoopField64)
        if (A_Index64 == 64):
            keyWordINT32 = Trim(A_LoopField64)
        if (A_Index64 == 65):
            keyWordINT64 = Trim(A_LoopField64)
        if (A_Index64 == 66):
            keyWordIF = Trim(A_LoopField64) + " "
        if (A_Index64 == 67):
            keyWordElseIf = Trim(A_LoopField64) + " "
        if (A_Index64 == 68):
            keyWordElse = Trim(A_LoopField64)
        if (A_Index64 == 69):
            keyWordWhileLoop = Trim(A_LoopField64) + " "
        if (A_Index64 == 70):
            keyWordLoopInfinite = Trim(A_LoopField64)
        if (A_Index64 == 71):
            keyWordLoop = Trim(A_LoopField64) + " "
        if (A_Index64 == 72):
            keyWordLoopParse = Trim(A_LoopField64) + " "
        if (A_Index64 == 73):
            keyWordContinue = Trim(A_LoopField64)
        if (A_Index64 == 74):
            keyWordBreak = Trim(A_LoopField64)
        if (A_Index64 == 75):
            keyWordFunc = Trim(A_LoopField64) + " "
        if (A_Index64 == 76):
            keyWordAwait = Trim(A_LoopField64) + " "
        if (A_Index64 == 77):
            keyWordAsync = Trim(A_LoopField64) + " "
        if (A_Index64 == 78):
            keyWordThrow = Trim(A_LoopField64) + " "
        if (A_Index64 == 79):
            keyWordErrorMsg = Trim(A_LoopField64)
        if (A_Index64 == 80):
            keyWordTry = Trim(A_LoopField64)
        if (A_Index64 == 81):
            keyWordCatch = Trim(A_LoopField64) + " "
        if (A_Index64 == 82):
            keyWordFinally = Trim(A_LoopField64)
        if (A_Index64 == 83):
            keyWordReturnStatement = Trim(A_LoopField64) + " "
        if (A_Index64 == 84):
            keyWordArrayAppend = Trim(A_LoopField64)
        if (A_Index64 == 85):
            keyWordArrayPop = Trim(A_LoopField64)
        if (A_Index64 == 86):
            keyWordArraySize = Trim(A_LoopField64)
        if (A_Index64 == 87):
            keyWordArrayInsert = Trim(A_LoopField64)
        if (A_Index64 == 88):
            keyWordArrayRemove = Trim(A_LoopField64)
        if (A_Index64 == 89):
            keyWordArrayIndexOf = Trim(A_LoopField64)
        if (A_Index64 == 90):
            keyWordArrayDefinition = Trim(A_LoopField64)
        if (A_Index64 == 91):
            keyWordArrayOfIntegersDefinition = Trim(A_LoopField64)
        if (A_Index64 == 92):
            keyWordArrayOfStringsDefinition = Trim(A_LoopField64)
        if (A_Index64 == 93):
            keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField64)
        if (A_Index64 == 94):
            keyWordArrayOfBooleansDefinition = Trim(A_LoopField64)
        if (A_Index64 == 95):
            keyWordVar = Trim(A_LoopField64) + " "
        if (A_Index64 == 96):
            keyWordLet = Trim(A_LoopField64) + " "
        if (A_Index64 == 97):
            keyWordConst = Trim(A_LoopField64) + " "
        if (A_Index64 == 98):
            keyWordEnd = Trim(A_LoopField64)
        if (A_Index64 == 99):
            keyWordGlobal = Trim(A_LoopField64) + " "
        if (A_Index64 == 100):
            keyWordComment = Trim(A_LoopField64)
        if (A_Index64 == 101):
            keyWordCommentOpenMultiLine = Trim(A_LoopField64)
        if (A_Index64 == 102):
            keyWordCommentCloseMultiLine = Trim(A_LoopField64)
        if (A_Index64 == 103):
            keyWordEscpaeChar = Trim(A_LoopField64)
        if (A_Index64 == 104):
            keyWordMainLabel = Trim(A_LoopField64)
        if (A_Index64 == 105):
            keyWordConcat = Trim(A_LoopField64)
        if (A_Index64 == 106):
            keyWordAdd = Trim(A_LoopField64)
        if (A_Index64 == 107):
            keyWordSub = Trim(A_LoopField64)
        if (A_Index64 == 108):
            keyWordMul = Trim(A_LoopField64)
        if (A_Index64 == 109):
            keyWordDiv = Trim(A_LoopField64)
        if (A_Index64 == 110):
            keyWordMod = Trim(A_LoopField64)
        if (A_Index64 == 111):
            keyWordExp = Trim(A_LoopField64)
        if (A_Index64 == 112):
            keyWordEqual = Trim(A_LoopField64)
        if (A_Index64 == 113):
            keyWordStrictEqual = Trim(A_LoopField64)
        if (A_Index64 == 114):
            keyWordNotEqual = Trim(A_LoopField64)
        if (A_Index64 == 115):
            keyWordGreater = Trim(A_LoopField64)
        if (A_Index64 == 116):
            keyWordLess = Trim(A_LoopField64)
        if (A_Index64 == 117):
            keyWordGreaterEqual = Trim(A_LoopField64)
        if (A_Index64 == 118):
            keyWordLessEqual = Trim(A_LoopField64)
        if (A_Index64 == 119):
            keyWordAnd = Trim(A_LoopField64)
        if (A_Index64 == 120):
            keyWordOr = Trim(A_LoopField64)
        if (A_Index64 == 121):
            keyWordNot = Trim(A_LoopField64)
        if (A_Index64 == 122):
            keyWordBitAnd = Trim(A_LoopField64)
        if (A_Index64 == 123):
            keyWordBitOr = Trim(A_LoopField64)
        if (A_Index64 == 124):
            keyWordBitXor = Trim(A_LoopField64)
        if (A_Index64 == 125):
            keyWordBitNot = Trim(A_LoopField64)
        if (A_Index64 == 126):
            keyWordShiftLeft = Trim(A_LoopField64)
        if (A_Index64 == 127):
            keyWordShiftRight = Trim(A_LoopField64)
        if (A_Index64 == 128):
            keyWordShiftUnsignedRight = Trim(A_LoopField64)
        if (A_Index64 == 129):
            keyWordAssign = Trim(A_LoopField64)
        if (A_Index64 == 130):
            keyWordAssignAdd = Trim(A_LoopField64)
        if (A_Index64 == 131):
            keyWordAssignConcat = Trim(A_LoopField64)
        if (A_Index64 == 132):
            keyWordAssignSub = Trim(A_LoopField64)
        if (A_Index64 == 133):
            keyWordAssignMul = Trim(A_LoopField64)
        if (A_Index64 == 134):
            keyWordAssignDiv = Trim(A_LoopField64)
        if (A_Index64 == 135):
            keyWordAssignMod = Trim(A_LoopField64)
        if (A_Index64 == 136):
            keyWordAssignShiftLeft = Trim(A_LoopField64)
        if (A_Index64 == 137):
            keyWordAssignShiftRight = Trim(A_LoopField64)
        if (A_Index64 == 138):
            keyWordLogicalAssignShiftRight = Trim(A_LoopField64)
        if (A_Index64 == 139):
            keyWordAssignBitAnd = Trim(A_LoopField64)
        if (A_Index64 == 140):
            keyWordAssignBitOr = Trim(A_LoopField64)
        if (A_Index64 == 141):
            keyWordAssignBitXor = Trim(A_LoopField64)
        if (A_Index64 == 142):
            keyWordTernary1 = Trim(A_LoopField64)
        if (A_Index64 == 143):
            keyWordTernary2 = Trim(A_LoopField64)
        if (A_Index64 == 144):
            keyWordInc = Trim(A_LoopField64)
        if (A_Index64 == 145):
            keyWordDec = Trim(A_LoopField64)
        if (A_Index64 == 146):
            AHKlikeLoopsIndexedAt = Trim(A_LoopField64)
        if (A_Index64 == 147):
            keyWordAIndex = Trim(A_LoopField64)
        if (A_Index64 == 148):
            keyWordALoopField = Trim(A_LoopField64)
        if (A_Index64 == 149):
            useCurlyBraces = Trim(A_LoopField64)
        if (A_Index64 == 150):
            useEnd = Trim(A_LoopField64)
        if (A_Index64 == 151):
            useSemicolon = Trim(A_LoopField64)
        if (A_Index64 == 152):
            useParentheses = Trim(A_LoopField64)
        if (A_Index64 == 153):
            usePrefixTypeForTypeDefinition = Trim(A_LoopField64)
        if (A_Index64 == 154):
            usePostfixTypeForTypeDefinition = Trim(A_LoopField64)
        if (A_Index64 == 155):
            usePythonicColonSyntax = Trim(A_LoopField64)
        if (A_Index64 == 156):
            useCurlyBracesSyntaxForArrayDef = Trim(A_LoopField64)
        if (A_Index64 == 157):
            useInJavaScriptAlwaysUseVar = Trim(A_LoopField64)
        if (A_Index64 == 158):
            useJavaScriptInAfullHTMLfile = Trim(A_LoopField64)
        if (A_Index64 == 159):
            useJavaScriptAmainFuncDef = Trim(A_LoopField64)
        if (A_Index64 == 160):
            useJavaScriptAllFuncsAreAsync = Trim(A_LoopField64)
        if (A_Index64 == 161):
            useJavaScriptAlwaysTripleEqual = Trim(A_LoopField64)
    if (len(argHTVMinstrMORE) > 0):
        allInstructionFile_2 = Trim(FileRead(Trim(argHTVMinstrMORE[0])))
        items65 = LoopParseFunc(allInstructionFile_2, "\n", "\r")
        for A_Index65 , A_LoopField65 in enumerate(items65, start=0):
            if (A_Index65 == 0):
                langToConvertTo_2 = Trim(A_LoopField65)
            if (A_Index65 == 1):
                langFileExtension_2 = Trim(A_LoopField65)
            if (A_Index65 == 2):
                commands_2 = Trim(A_LoopField65)
            if (A_Index65 == 3):
                keyWordAlliance_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 4):
                keyWordCrew_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 5):
                keyWordMethod_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 6):
                keyWordDefObj_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 7):
                keyWordPorp_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 8):
                keyWordThis_2 = Trim(A_LoopField65)
            if (A_Index65 == 9):
                keyWordInclude_2 = Trim(A_LoopField65)
            if (A_Index65 == 10):
                keyWordCodeInTheTranspiledLangStart_2 = Trim(A_LoopField65)
            if (A_Index65 == 11):
                keyWordCodeInTheTranspiledLangEnd_2 = Trim(A_LoopField65)
            if (A_Index65 == 12):
                keyWordCodeInTheTranspiledLangStartCPP_2 = Trim(A_LoopField65)
            if (A_Index65 == 13):
                keyWordCodeInTheTranspiledLangEndCPP_2 = Trim(A_LoopField65)
            if (A_Index65 == 14):
                keyWordCodeInTheTranspiledLangStartPY_2 = Trim(A_LoopField65)
            if (A_Index65 == 15):
                keyWordCodeInTheTranspiledLangEndPY_2 = Trim(A_LoopField65)
            if (A_Index65 == 16):
                keyWordCodeInTheTranspiledLangStartJS_2 = Trim(A_LoopField65)
            if (A_Index65 == 17):
                keyWordCodeInTheTranspiledLangEndJS_2 = Trim(A_LoopField65)
            if (A_Index65 == 18):
                keyWordCodeInTheTranspiledLangStartGO_2 = Trim(A_LoopField65)
            if (A_Index65 == 19):
                keyWordCodeInTheTranspiledLangEndGO_2 = Trim(A_LoopField65)
            if (A_Index65 == 20):
                keyWordCodeInTheTranspiledLangStartLUA_2 = Trim(A_LoopField65)
            if (A_Index65 == 21):
                keyWordCodeInTheTranspiledLangEndLUA_2 = Trim(A_LoopField65)
            if (A_Index65 == 22):
                keyWordCodeInTheTranspiledLangStartCS_2 = Trim(A_LoopField65)
            if (A_Index65 == 23):
                keyWordCodeInTheTranspiledLangEndCS_2 = Trim(A_LoopField65)
            if (A_Index65 == 24):
                keyWordCodeInTheTranspiledLangStartJAVA_2 = Trim(A_LoopField65)
            if (A_Index65 == 25):
                keyWordCodeInTheTranspiledLangEndJAVA_2 = Trim(A_LoopField65)
            if (A_Index65 == 26):
                keyWordCodeInTheTranspiledLangStartKT_2 = Trim(A_LoopField65)
            if (A_Index65 == 27):
                keyWordCodeInTheTranspiledLangEndKT_2 = Trim(A_LoopField65)
            if (A_Index65 == 28):
                keyWordCodeInTheTranspiledLangStartRB_2 = Trim(A_LoopField65)
            if (A_Index65 == 29):
                keyWordCodeInTheTranspiledLangEndRB_2 = Trim(A_LoopField65)
            if (A_Index65 == 30):
                keyWordCodeInTheTranspiledLangStartNIM_2 = Trim(A_LoopField65)
            if (A_Index65 == 31):
                keyWordCodeInTheTranspiledLangEndNIM_2 = Trim(A_LoopField65)
            if (A_Index65 == 32):
                keyWordCodeInTheTranspiledLangStartAHK_2 = Trim(A_LoopField65)
            if (A_Index65 == 33):
                keyWordCodeInTheTranspiledLangEndAHK_2 = Trim(A_LoopField65)
            if (A_Index65 == 34):
                keyWordCodeInTheTranspiledLangStartSWIFT_2 = Trim(A_LoopField65)
            if (A_Index65 == 35):
                keyWordCodeInTheTranspiledLangEndSWIFT_2 = Trim(A_LoopField65)
            if (A_Index65 == 36):
                keyWordCodeInTheTranspiledLangStartDART_2 = Trim(A_LoopField65)
            if (A_Index65 == 37):
                keyWordCodeInTheTranspiledLangEndDART_2 = Trim(A_LoopField65)
            if (A_Index65 == 38):
                keyWordCodeInTheTranspiledLangStartTS_2 = Trim(A_LoopField65)
            if (A_Index65 == 39):
                keyWordCodeInTheTranspiledLangEndTS_2 = Trim(A_LoopField65)
            if (A_Index65 == 40):
                keyWordCodeInTheTranspiledLangStartGROOVY_2 = Trim(A_LoopField65)
            if (A_Index65 == 41):
                keyWordCodeInTheTranspiledLangEndGROOVY_2 = Trim(A_LoopField65)
            if (A_Index65 == 42):
                keyWordCodeInTheTranspiledLangStartHTVM_2 = Trim(A_LoopField65)
            if (A_Index65 == 43):
                keyWordCodeInTheTranspiledLangEndHTVM_2 = Trim(A_LoopField65)
            if (A_Index65 == 44):
                keyWordCodeInHTVMstart_2 = Trim(A_LoopField65)
            if (A_Index65 == 45):
                keyWordCodeInHTVMend_2 = Trim(A_LoopField65)
            if (A_Index65 == 46):
                keyWordCurlyBraceOpen_2 = Trim(A_LoopField65)
            if (A_Index65 == 47):
                keyWordCurlyBraceClose_2 = Trim(A_LoopField65)
            if (A_Index65 == 48):
                keyWordNull_2 = Trim(A_LoopField65)
            if (A_Index65 == 49):
                keyWordTrue_2 = Trim(A_LoopField65)
            if (A_Index65 == 50):
                keyWordFalse_2 = Trim(A_LoopField65)
            if (A_Index65 == 51):
                keyWordVoid_2 = Trim(A_LoopField65)
            if (A_Index65 == 52):
                keyWordDouble_2 = Trim(A_LoopField65)
            if (A_Index65 == 53):
                keyWordChar_2 = Trim(A_LoopField65)
            if (A_Index65 == 54):
                keyWordUint8_2 = Trim(A_LoopField65)
            if (A_Index65 == 55):
                keyWordUint16_2 = Trim(A_LoopField65)
            if (A_Index65 == 56):
                keyWordUint32_2 = Trim(A_LoopField65)
            if (A_Index65 == 57):
                keyWordUint64_2 = Trim(A_LoopField65)
            if (A_Index65 == 58):
                keyWordINT_2 = Trim(A_LoopField65)
            if (A_Index65 == 59):
                keyWordSTR_2 = Trim(A_LoopField65)
            if (A_Index65 == 60):
                keyWordBOOL_2 = Trim(A_LoopField65)
            if (A_Index65 == 61):
                keyWordFLOAT_2 = Trim(A_LoopField65)
            if (A_Index65 == 62):
                keyWordINT8_2 = Trim(A_LoopField65)
            if (A_Index65 == 63):
                keyWordINT16_2 = Trim(A_LoopField65)
            if (A_Index65 == 64):
                keyWordINT32_2 = Trim(A_LoopField65)
            if (A_Index65 == 65):
                keyWordINT64_2 = Trim(A_LoopField65)
            if (A_Index65 == 66):
                keyWordIF_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 67):
                keyWordElseIf_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 68):
                keyWordElse_2 = Trim(A_LoopField65)
            if (A_Index65 == 69):
                keyWordWhileLoop_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 70):
                keyWordLoopInfinite_2 = Trim(A_LoopField65)
            if (A_Index65 == 71):
                keyWordLoop_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 72):
                keyWordLoopParse_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 73):
                keyWordContinue_2 = Trim(A_LoopField65)
            if (A_Index65 == 74):
                keyWordBreak_2 = Trim(A_LoopField65)
            if (A_Index65 == 75):
                keyWordFunc_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 76):
                keyWordAwait_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 77):
                keyWordAsync_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 78):
                keyWordThrow_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 79):
                keyWordErrorMsg_2 = Trim(A_LoopField65)
            if (A_Index65 == 80):
                keyWordTry_2 = Trim(A_LoopField65)
            if (A_Index65 == 81):
                keyWordCatch_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 82):
                keyWordFinally_2 = Trim(A_LoopField65)
            if (A_Index65 == 83):
                keyWordReturnStatement_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 84):
                keyWordArrayAppend_2 = Trim(A_LoopField65)
            if (A_Index65 == 85):
                keyWordArrayPop_2 = Trim(A_LoopField65)
            if (A_Index65 == 86):
                keyWordArraySize_2 = Trim(A_LoopField65)
            if (A_Index65 == 87):
                keyWordArrayInsert_2 = Trim(A_LoopField65)
            if (A_Index65 == 88):
                keyWordArrayRemove_2 = Trim(A_LoopField65)
            if (A_Index65 == 89):
                keyWordArrayIndexOf_2 = Trim(A_LoopField65)
            if (A_Index65 == 90):
                keyWordArrayDefinition_2 = Trim(A_LoopField65)
            if (A_Index65 == 91):
                keyWordArrayOfIntegersDefinition_2 = Trim(A_LoopField65)
            if (A_Index65 == 92):
                keyWordArrayOfStringsDefinition_2 = Trim(A_LoopField65)
            if (A_Index65 == 93):
                keyWordArrayOfFloatingPointNumbersDefinition_2 = Trim(A_LoopField65)
            if (A_Index65 == 94):
                keyWordArrayOfBooleansDefinition_2 = Trim(A_LoopField65)
            if (A_Index65 == 95):
                keyWordVar_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 96):
                keyWordLet_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 97):
                keyWordConst_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 98):
                keyWordEnd_2 = Trim(A_LoopField65)
            if (A_Index65 == 99):
                keyWordGlobal_2 = Trim(A_LoopField65) + " "
            if (A_Index65 == 100):
                keyWordComment_2 = Trim(A_LoopField65)
            if (A_Index65 == 101):
                keyWordCommentOpenMultiLine_2 = Trim(A_LoopField65)
            if (A_Index65 == 102):
                keyWordCommentCloseMultiLine_2 = Trim(A_LoopField65)
            if (A_Index65 == 103):
                keyWordEscpaeChar_2 = Trim(A_LoopField65)
            if (A_Index65 == 104):
                keyWordMainLabel_2 = Trim(A_LoopField65)
            if (A_Index65 == 105):
                keyWordConcat_2 = Trim(A_LoopField65)
            if (A_Index65 == 106):
                keyWordAdd_2 = Trim(A_LoopField65)
            if (A_Index65 == 107):
                keyWordSub_2 = Trim(A_LoopField65)
            if (A_Index65 == 108):
                keyWordMul_2 = Trim(A_LoopField65)
            if (A_Index65 == 109):
                keyWordDiv_2 = Trim(A_LoopField65)
            if (A_Index65 == 110):
                keyWordMod_2 = Trim(A_LoopField65)
            if (A_Index65 == 111):
                keyWordExp_2 = Trim(A_LoopField65)
            if (A_Index65 == 112):
                keyWordEqual_2 = Trim(A_LoopField65)
            if (A_Index65 == 113):
                keyWordStrictEqual_2 = Trim(A_LoopField65)
            if (A_Index65 == 114):
                keyWordNotEqual_2 = Trim(A_LoopField65)
            if (A_Index65 == 115):
                keyWordGreater_2 = Trim(A_LoopField65)
            if (A_Index65 == 116):
                keyWordLess_2 = Trim(A_LoopField65)
            if (A_Index65 == 117):
                keyWordGreaterEqual_2 = Trim(A_LoopField65)
            if (A_Index65 == 118):
                keyWordLessEqual_2 = Trim(A_LoopField65)
            if (A_Index65 == 119):
                keyWordAnd_2 = Trim(A_LoopField65)
            if (A_Index65 == 120):
                keyWordOr_2 = Trim(A_LoopField65)
            if (A_Index65 == 121):
                keyWordNot_2 = Trim(A_LoopField65)
            if (A_Index65 == 122):
                keyWordBitAnd_2 = Trim(A_LoopField65)
            if (A_Index65 == 123):
                keyWordBitOr_2 = Trim(A_LoopField65)
            if (A_Index65 == 124):
                keyWordBitXor_2 = Trim(A_LoopField65)
            if (A_Index65 == 125):
                keyWordBitNot_2 = Trim(A_LoopField65)
            if (A_Index65 == 126):
                keyWordShiftLeft_2 = Trim(A_LoopField65)
            if (A_Index65 == 127):
                keyWordShiftRight_2 = Trim(A_LoopField65)
            if (A_Index65 == 128):
                keyWordShiftUnsignedRight_2 = Trim(A_LoopField65)
            if (A_Index65 == 129):
                keyWordAssign_2 = Trim(A_LoopField65)
            if (A_Index65 == 130):
                keyWordAssignAdd_2 = Trim(A_LoopField65)
            if (A_Index65 == 131):
                keyWordAssignConcat_2 = Trim(A_LoopField65)
            if (A_Index65 == 132):
                keyWordAssignSub_2 = Trim(A_LoopField65)
            if (A_Index65 == 133):
                keyWordAssignMul_2 = Trim(A_LoopField65)
            if (A_Index65 == 134):
                keyWordAssignDiv_2 = Trim(A_LoopField65)
            if (A_Index65 == 135):
                keyWordAssignMod_2 = Trim(A_LoopField65)
            if (A_Index65 == 136):
                keyWordAssignShiftLeft_2 = Trim(A_LoopField65)
            if (A_Index65 == 137):
                keyWordAssignShiftRight_2 = Trim(A_LoopField65)
            if (A_Index65 == 138):
                keyWordLogicalAssignShiftRight_2 = Trim(A_LoopField65)
            if (A_Index65 == 139):
                keyWordAssignBitAnd_2 = Trim(A_LoopField65)
            if (A_Index65 == 140):
                keyWordAssignBitOr_2 = Trim(A_LoopField65)
            if (A_Index65 == 141):
                keyWordAssignBitXor_2 = Trim(A_LoopField65)
            if (A_Index65 == 142):
                keyWordTernary1_2 = Trim(A_LoopField65)
            if (A_Index65 == 143):
                keyWordTernary2_2 = Trim(A_LoopField65)
            if (A_Index65 == 144):
                keyWordInc_2 = Trim(A_LoopField65)
            if (A_Index65 == 145):
                keyWordDec_2 = Trim(A_LoopField65)
            if (A_Index65 == 146):
                AHKlikeLoopsIndexedAt_2 = Trim(A_LoopField65)
            if (A_Index65 == 147):
                keyWordAIndex_2 = Trim(A_LoopField65)
            if (A_Index65 == 148):
                keyWordALoopField_2 = Trim(A_LoopField65)
            if (A_Index65 == 149):
                useCurlyBraces_2 = Trim(A_LoopField65)
            if (A_Index65 == 150):
                useEnd_2 = Trim(A_LoopField65)
            if (A_Index65 == 151):
                useSemicolon_2 = Trim(A_LoopField65)
            if (A_Index65 == 152):
                useParentheses_2 = Trim(A_LoopField65)
            if (A_Index65 == 153):
                usePrefixTypeForTypeDefinition_2 = Trim(A_LoopField65)
            if (A_Index65 == 154):
                usePostfixTypeForTypeDefinition_2 = Trim(A_LoopField65)
            if (A_Index65 == 155):
                usePythonicColonSyntax_2 = Trim(A_LoopField65)
            if (A_Index65 == 156):
                useCurlyBracesSyntaxForArrayDef_2 = Trim(A_LoopField65)
            if (A_Index65 == 157):
                useInJavaScriptAlwaysUseVar_2 = Trim(A_LoopField65)
            if (A_Index65 == 158):
                useJavaScriptInAfullHTMLfile_2 = Trim(A_LoopField65)
            if (A_Index65 == 159):
                useJavaScriptAmainFuncDef_2 = Trim(A_LoopField65)
            if (A_Index65 == 160):
                useJavaScriptAllFuncsAreAsync_2 = Trim(A_LoopField65)
            if (A_Index65 == 161):
                useJavaScriptAlwaysTripleEqual_2 = Trim(A_LoopField65)
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
    if (langToConvertTo == langFileExtension_2):
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
    if (langToConvertTo == "groovy"):
    """
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    HTVMout = ""
    htCode = Trim(StrReplace(htCode, Chr(13), ""))
    code = ""
    print(htCode)
    code = htCode
    print(mode)
    print(langToConvertTo)
    print("==================================")
    print("==================================")
    print("==================================")
    print("==================================")
    print("==================================")
    #print(allInstructionFile)
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
    # keyWordInclude
    # keyWordInclude
    # keyWordInclude
    allLibCODE = ""
    allLibCODEfix = ""
    allLibsWeSee = []
    allLibsWeSeeSEE = []
    allLibsWeSeeHOLD = ""
    doseCodeHaveLibs = 0
    doseCodeHaveLibs_HAS_SEEN = 0
    doseCodeHaveLibs_HAS_SEEN2 = 0
    if (isNotHTVMfile == 0):
        if (langToConvertTo != langFileExtension_2):
            if (InStr(code, StrLower(keyWordInclude + " "))):
                for A_Index66 in range(0, 10000 + 0):
                    doseCodeHaveLibs = 0
                    allLibCODE = ""
                    if (A_Index66 == 0):
                        items67 = LoopParseFunc(code, "\n", "\r")
                        for A_Index67 , A_LoopField67 in enumerate(items67, start=0):
                            if (SubStr(StrLower(Trim(A_LoopField67)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ")):
                                allLibsWeSee.append(StrReplace(StringTrimLeft(Trim(A_LoopField67), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""))
                                allLibsWeSeeSEE.append(StrReplace(StringTrimLeft(Trim(A_LoopField67), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""))
                                doseCodeHaveLibs = 1
                    else:
                        items68 = LoopParseFunc(code, "\n", "\r")
                        for A_Index68 , A_LoopField68 in enumerate(items68, start=0):
                            ALoopField = A_LoopField68
                            if (SubStr(StrLower(Trim(A_LoopField68)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ")):
                                doseCodeHaveLibs_HAS_SEEN = 0
                                for A_Index69 in range(0, len(allLibsWeSee) + 0):
                                    if (StrReplace(StringTrimLeft(Trim(ALoopField), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), "") == allLibsWeSee[A_Index69]):
                                        doseCodeHaveLibs_HAS_SEEN = 1
                                if (doseCodeHaveLibs_HAS_SEEN == 0):
                                    allLibsWeSee.append(StrReplace(StringTrimLeft(Trim(A_LoopField68), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""))
                                    allLibsWeSeeSEE.append(StrReplace(StringTrimLeft(Trim(A_LoopField68), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""))
                                    doseCodeHaveLibs = 1
                    for A_Index70 in range(0, len(allLibsWeSee) + 0):
                        allLibsWeSeeHOLD = allLibsWeSee[A_Index70]
                        doseCodeHaveLibs_HAS_SEEN2 = 0
                        for A_Index71 in range(0, len(allLibsWeSeeSEE) - allLibsWeSeelen(allLibsWeSeeSEE) + 0):
                            if (allLibsWeSeeHOLD == allLibsWeSeeSEE[A_Index71]):
                                doseCodeHaveLibs_HAS_SEEN2 = 1
                        if (doseCodeHaveLibs_HAS_SEEN2 == 0):
                            allLibCODE += FileRead(Trim(allLibsWeSee[len(allLibsWeSee) - A_Index70 - 1])) + "\n"
                        allLibsWeSee.pop()
                    allLibCODEfix = ""
                    items72 = LoopParseFunc(code, "\n", "\r")
                    for A_Index72 , A_LoopField72 in enumerate(items72, start=0):
                        if (SubStr(StrLower(Trim(A_LoopField72)), 1, StrLen(StrLower(keyWordInclude + " "))) != StrLower(keyWordInclude + " ")):
                            allLibCODEfix += A_LoopField72 + "\n"
                    code = StringTrimRight(allLibCODEfix, 1)
                    code = allLibCODE + code
                    if (doseCodeHaveLibs == 0):
                        break
        ALoopField = ""
    # keyWordInclude
    # keyWordInclude
    # keyWordInclude
    # PROGRAMMING BLOCK
    # PROGRAMMING BLOCK
    # PROGRAMMING BLOCK
    # PROGRAMMING BLOCK
    COUNT_programmingBlock_InTheTranspiledLang = 0
    COUNT_programmingBlock_CPP = 0
    COUNT_programmingBlock_PY = 0
    COUNT_programmingBlock_JS = 0
    COUNT_programmingBlock_GO = 0
    COUNT_programmingBlock_LUA = 0
    COUNT_programmingBlock_CS = 0
    COUNT_programmingBlock_JAVA = 0
    COUNT_programmingBlock_KT = 0
    COUNT_programmingBlock_RB = 0
    COUNT_programmingBlock_NIM = 0
    COUNT_programmingBlock_AHK = 0
    COUNT_programmingBlock_SWIFT = 0
    COUNT_programmingBlock_DART = 0
    COUNT_programmingBlock_TS = 0
    COUNT_programmingBlock_GROOVY = 0
    COUNT_programmingBlock_HTVM = 0
    COUNT_programmingBlock_HTVMsyntax = 0
    programmingBlocksTemp = ""
    inProgarmmingBlock = 0
    holdTempDataProgrammingBlockThenPutInArr = ""
    items73 = LoopParseFunc(code, "\n", "\r")
    for A_Index73 , A_LoopField73 in enumerate(items73, start=0):
        if (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEnd)):
            COUNT_programmingBlock_InTheTranspiledLang = COUNT_programmingBlock_InTheTranspiledLang + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(COUNT_programmingBlock_InTheTranspiledLang) + "AA\n"
            programmingBlock_InTheTranspiledLang.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndCPP)):
            COUNT_programmingBlock_CPP = COUNT_programmingBlock_CPP + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(COUNT_programmingBlock_CPP) + "AA\n"
            programmingBlock_CPP.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndPY)):
            COUNT_programmingBlock_PY = COUNT_programmingBlock_PY + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_PY-programmingBlock_PY-AA" + STR(COUNT_programmingBlock_PY) + "AA\n"
            programmingBlock_PY.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndJS)):
            COUNT_programmingBlock_JS = COUNT_programmingBlock_JS + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_JS-programmingBlock_JS-AA" + STR(COUNT_programmingBlock_JS) + "AA\n"
            programmingBlock_JS.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndGO)):
            COUNT_programmingBlock_GO = COUNT_programmingBlock_GO + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_GO-programmingBlock_GO-AA" + STR(COUNT_programmingBlock_GO) + "AA\n"
            programmingBlock_GO.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndLUA)):
            COUNT_programmingBlock_LUA = COUNT_programmingBlock_LUA + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(COUNT_programmingBlock_LUA) + "AA\n"
            programmingBlock_LUA.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndCS)):
            COUNT_programmingBlock_CS = COUNT_programmingBlock_CS + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_CS-programmingBlock_CS-AA" + STR(COUNT_programmingBlock_CS) + "AA\n"
            programmingBlock_CS.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndJAVA)):
            COUNT_programmingBlock_JAVA = COUNT_programmingBlock_JAVA + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(COUNT_programmingBlock_JAVA) + "AA\n"
            programmingBlock_JAVA.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndKT)):
            COUNT_programmingBlock_KT = COUNT_programmingBlock_KT + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_KT-programmingBlock_KT-AA" + STR(COUNT_programmingBlock_KT) + "AA\n"
            programmingBlock_KT.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndRB)):
            COUNT_programmingBlock_RB = COUNT_programmingBlock_RB + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_RB-programmingBlock_RB-AA" + STR(COUNT_programmingBlock_RB) + "AA\n"
            programmingBlock_RB.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndNIM)):
            COUNT_programmingBlock_NIM = COUNT_programmingBlock_NIM + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(COUNT_programmingBlock_NIM) + "AA\n"
            programmingBlock_NIM.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndAHK)):
            COUNT_programmingBlock_AHK = COUNT_programmingBlock_AHK + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(COUNT_programmingBlock_AHK) + "AA\n"
            programmingBlock_AHK.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndSWIFT)):
            COUNT_programmingBlock_SWIFT = COUNT_programmingBlock_SWIFT + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(COUNT_programmingBlock_SWIFT) + "AA\n"
            programmingBlock_SWIFT.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndDART)):
            COUNT_programmingBlock_DART = COUNT_programmingBlock_DART + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_DART-programmingBlock_DART-AA" + STR(COUNT_programmingBlock_DART) + "AA\n"
            programmingBlock_DART.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndTS)):
            COUNT_programmingBlock_TS = COUNT_programmingBlock_TS + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_TS-programmingBlock_TS-AA" + STR(COUNT_programmingBlock_TS) + "AA\n"
            programmingBlock_TS.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndGROOVY)):
            COUNT_programmingBlock_GROOVY = COUNT_programmingBlock_GROOVY + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(COUNT_programmingBlock_GROOVY) + "AA\n"
            programmingBlock_GROOVY.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangEndHTVM)):
            COUNT_programmingBlock_HTVM = COUNT_programmingBlock_HTVM + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(COUNT_programmingBlock_HTVM) + "AA\n"
            programmingBlock_HTVM.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInHTVMend)):
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            COUNT_programmingBlock_HTVMsyntax = COUNT_programmingBlock_HTVMsyntax + 1
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1)
            programmingBlocksTemp += "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(COUNT_programmingBlock_HTVMsyntax) + "AA\n"
            programmingBlock_HTVMsyntax.append(holdTempDataProgrammingBlockThenPutInArr)
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 0
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        elif (inProgarmmingBlock == 1):
            holdTempDataProgrammingBlockThenPutInArr += A_LoopField73 + "\n"
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStart)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartCPP)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartPY)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartJS)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartGO)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartLUA)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartCS)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartJAVA)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartKT)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartRB)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartNIM)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartAHK)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartSWIFT)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartDART)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartTS)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartGROOVY)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInTheTranspiledLangStartHTVM)):
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
        elif (Trim(StrLower(A_LoopField73)) == StrLower(keyWordCodeInHTVMstart)):
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            holdTempDataProgrammingBlockThenPutInArr = ""
            inProgarmmingBlock = 1
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        else:
            programmingBlocksTemp += A_LoopField73 + "\n"
    code = StringTrimRight(programmingBlocksTemp, 1)
    #programmingBlock_InTheTranspiledLang
    #programmingBlock_CPP
    #programmingBlock_PY
    #programmingBlock_JS
    #programmingBlock_GO
    #programmingBlock_LUA
    #programmingBlock_CS
    #programmingBlock_JAVA
    #programmingBlock_KT
    #programmingBlock_RB
    #programmingBlock_NIM
    #programmingBlock_AHK
    #programmingBlock_SWIFT
    #programmingBlock_DART
    #programmingBlock_TS
    #programmingBlock_GROOVY
    #programmingBlock_HTVM
    #programmingBlock_HTVMsyntax
    # PROGRAMMING BLOCK
    # PROGRAMMING BLOCK
    # PROGRAMMING BLOCK
    # PROGRAMMING BLOCK
    lookIntoTheNextLineForFuncWhitNoKeyWord = []
    didWeUseMainLabel = 0
    codeOutFixAndAddMainFunc = ""
    htCodeOutFixEnd = ""
    htCodeOutFixINT = 0
    htCodeOutFixINT2 = 0
    beforeKeywordForRemoveCommentsOnTheEndOfTheLine = ""
    newStringOutCode = ""
    posForRemoveCommentsOnTheEndOfTheLine = 0
    originalStringForRemoveCommentsOnTheEndOfTheLine = ""
    OutFixDoubleQuotesInsideDoubleQuotes = ""
    fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0
    htCodeOUT754754 = ""
    areWEinSome34sNum = 0
    theIdNumOfThe34 = 0
    theIdNumOfThe34theVar = []
    ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = ""
    getAllCharForTheFurtureSoIcanAddEscapeChar = []
    removeNexFixkeyWordEscpaeChar = 0
    if (isNotHTVMfile == 0):
        print("============programmingBlock_CPP==================")
        print("============programmingBlock_CPP==================")
        if (len(programmingBlock_CPP) > 0):
            for A_Index74 in range(0, len(programmingBlock_CPP) + 0):
                print(programmingBlock_CPP[A_Index74])
        print("============programmingBlock_CPP==================")
        print("============programmingBlock_CPP==================")
        items75 = LoopParseFunc(code)
        for A_Index75 , A_LoopField75 in enumerate(items75, start=0):
            theIdNumOfThe34theVar.append("")
            theIdNumOfThe34theVar.append("")
        items76 = LoopParseFunc(code)
        for A_Index76 , A_LoopField76 in enumerate(items76, start=0):
            theIdNumOfThe34theVar[A_Index76] = theIdNumOfThe34theVar[A_Index76] + Chr(34)
            getAllCharForTheFurtureSoIcanAddEscapeChar.append(A_LoopField76)
        getAllCharForTheFurtureSoIcanAddEscapeChar.append(" ")
        ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuusgfgesrheidFor--asdsas--theuhtuwaesphoutr" + Chr(34)
        items77 = LoopParseFunc(code)
        for A_Index77 , A_LoopField77 in enumerate(items77, start=0):
            if (A_LoopField77 == keyWordEscpaeChar and getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index77 + 1] == Chr(34)):
                fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1
                OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes
            else:
                if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1):
                    OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField77
                else:
                    fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0
        code = OutFixDoubleQuotesInsideDoubleQuotes
        if (keyWordEscpaeChar != Chr(92) and langToConvertTo != langFileExtension_2):
            code = StrReplace(code, Chr(92), Chr(92) + Chr(92))
        if (keyWordEscpaeChar == Chr(92) and langToConvertTo != langFileExtension_2):
            items78 = LoopParseFunc(code)
            for A_Index78 , A_LoopField78 in enumerate(items78, start=0):
                if (A_LoopField78 == Chr(34)):
                    areWEinSome34sNum = areWEinSome34sNum + 1
                if (areWEinSome34sNum == 1):
                    if (A_LoopField78 != Chr(34)):
                        if (A_LoopField78 == keyWordEscpaeChar and langToConvertTo != langFileExtension_2):
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92)
                        else:
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField78
                    else:
                        theIdNumOfThe34 = theIdNumOfThe34 + 1
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65)
                if (areWEinSome34sNum == 2 or areWEinSome34sNum == 0):
                    if (A_LoopField78 != Chr(34)):
                        htCodeOUT754754 += A_LoopField78
                    areWEinSome34sNum = 0
        else:
            items79 = LoopParseFunc(code)
            for A_Index79 , A_LoopField79 in enumerate(items79, start=0):
                if (A_LoopField79 == Chr(34)):
                    areWEinSome34sNum = areWEinSome34sNum + 1
                if (areWEinSome34sNum == 1):
                    if (A_LoopField79 != Chr(34)):
                        if (A_LoopField79 == keyWordEscpaeChar and keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index79 + 1] and langToConvertTo != langFileExtension_2):
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar
                            removeNexFixkeyWordEscpaeChar = 1
                        elif (A_LoopField79 == keyWordEscpaeChar and langToConvertTo != langFileExtension_2):
                            if (removeNexFixkeyWordEscpaeChar != 1):
                                theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92)
                            else:
                                removeNexFixkeyWordEscpaeChar = 0
                        else:
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField79
                    else:
                        theIdNumOfThe34 = theIdNumOfThe34 + 1
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65)
                if (areWEinSome34sNum == 2 or areWEinSome34sNum == 0):
                    if (A_LoopField79 != Chr(34)):
                        htCodeOUT754754 += A_LoopField79
                    areWEinSome34sNum = 0
        code = htCodeOUT754754
        for A_Index80 in range(0, theIdNumOfThe34 + 0):
            theIdNumOfThe34theVar[A_Index80] = theIdNumOfThe34theVar[A_Index80] + Chr(34)
        theIdNumOfThe34theVar.append(Chr(34))
        code = StrReplace(code, Chr(13), "")
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        if (langToConvertTo == langFileExtension_2):
            if (useSemicolon_2 == "on"):
                theSemicolon = ";"
            else:
                theSemicolon = ""
            if (usePythonicColonSyntax_2 == "off"):
                theColon = ""
            else:
                theColon = ":"
        else:
            if (langToConvertTo != "py" and langToConvertTo != "nim" and langToConvertTo != "ahk" and langToConvertTo != "go" and langToConvertTo != "lua" and langToConvertTo != "kt" and langToConvertTo != "rb" and langToConvertTo != "swift" and langToConvertTo != "groovy" and useSemicolon == "off"):
                theSemicolon = ";"
            else:
                theSemicolon = ""
            if (langToConvertTo != "py" and langToConvertTo != "nim" and usePythonicColonSyntax == "off"):
                theColon = ""
            else:
                theColon = ":"
        items81 = LoopParseFunc(code, "\n", "\r")
        for A_Index81 , A_LoopField81 in enumerate(items81, start=0):
            # Define the original string
            originalStringForRemoveCommentsOnTheEndOfTheLine = A_LoopField81
            # Find the position of the keyword in the original string
            posForRemoveCommentsOnTheEndOfTheLine = InStr(originalStringForRemoveCommentsOnTheEndOfTheLine, " " + keyWordComment)
            if (SubStr(Trim(A_LoopField81), 1, StrLen(keyWordComment)) != keyWordComment):
                if (posForRemoveCommentsOnTheEndOfTheLine > 0):
                    beforeKeywordForRemoveCommentsOnTheEndOfTheLine = A_LoopField81
                    # Construct the new string with everything before the keyword
                    newStringOutCode += beforeKeywordForRemoveCommentsOnTheEndOfTheLine + "\n"
                else:
                    newStringOutCode += A_LoopField81 + "\n"
            else:
                newStringOutCode += A_LoopField81 + "\n"
        code = StringTrimRight(newStringOutCode, 1)
        #MsgBox, % code
        if (useCurlyBraces == "on"):
            if (keyWordCurlyBraceOpen != "{"):
                items82 = LoopParseFunc(code, "\n", "\r")
                for A_Index82 , A_LoopField82 in enumerate(items82, start=0):
                    htCodeOutFixINT2 = 0
                    if (isLineAconstruct(Trim(A_LoopField82)) == True or Trim(A_LoopField82) == keyWordCurlyBraceOpen):
                        htCodeOutFixINT2 = 1
                    htCodeOutFixINT = 0
                    items83 = LoopParseFunc(A_LoopField82, " ")
                    for A_Index83 , A_LoopField83 in enumerate(items83, start=0):
                        htCodeOutFixINT = htCodeOutFixINT + 1
                    htCodeOutFixINT = htCodeOutFixINT - 1
                    items84 = LoopParseFunc(A_LoopField82, " ")
                    for A_Index84 , A_LoopField84 in enumerate(items84, start=0):
                        if (htCodeOutFixINT == A_Index84) && (htCodeOutFixINT2 == 1):
                            htCodeOutFixINT2 = 0
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField84, keyWordCurlyBraceOpen, "{") + " "
                        else:
                            htCodeOutFixEnd += A_LoopField84 + " "
                    htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1)
                    htCodeOutFixEnd += "\n"
                code = StringTrimRight(htCodeOutFixEnd, 1)
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            htCodeOutFixEnd = ""
            if (keyWordCurlyBraceClose != "}"):
                items85 = LoopParseFunc(code, "\n", "\r")
                for A_Index85 , A_LoopField85 in enumerate(items85, start=0):
                    htCodeOutFixINT2 = 0
                    if (isLineAconstruct(Trim(A_LoopField85)) == True or Trim(A_LoopField85) == keyWordCurlyBraceClose):
                        htCodeOutFixINT2 = 1
                    items86 = LoopParseFunc(A_LoopField85, " ")
                    for A_Index86 , A_LoopField86 in enumerate(items86, start=0):
                        if (htCodeOutFixINT2 == 1 or Trim(A_LoopField86) == keyWordCurlyBraceClose):
                            htCodeOutFixINT2 = 0
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField86, keyWordCurlyBraceClose, "}") + " "
                        else:
                            htCodeOutFixEnd += A_LoopField86 + " "
                    htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1)
                    htCodeOutFixEnd += "\n"
                code = StringTrimRight(htCodeOutFixEnd, 1)
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        htCodeOutFixEnd = ""
        if (useEnd == "on"):
            items87 = LoopParseFunc(code, "\n", "\r")
            for A_Index87 , A_LoopField87 in enumerate(items87, start=0):
                if (StrLower(Trim(A_LoopField87)) == StrLower(keyWordEnd)):
                    htCodeOutFixEnd += "}\n"
                elif (SubStr(StrLower(Trim(A_LoopField87)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF) and isLineAconstruct(Trim(A_LoopField87)) == True):
                    htCodeOutFixEnd += A_LoopField87 + "\n{\n"
                elif (SubStr(StrLower(Trim(A_LoopField87)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop) and isLineAconstruct(Trim(A_LoopField87)) == True):
                    htCodeOutFixEnd += A_LoopField87 + "\n{\n"
                elif (SubStr(StrLower(Trim(A_LoopField87)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf) and isLineAconstruct(Trim(A_LoopField87)) == True):
                    htCodeOutFixEnd += "\n}\n" + A_LoopField87 + "\n{\n"
                elif (SubStr(StrLower(Trim(A_LoopField87)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse) and isLineAconstruct(Trim(A_LoopField87)) == True):
                    htCodeOutFixEnd += "\n}\n" + A_LoopField87 + "\n{\n"
                elif (SubStr(StrLower(Trim(A_LoopField87)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch) and isLineAconstruct(Trim(A_LoopField87)) == True):
                    htCodeOutFixEnd += "\n}\n" + A_LoopField87 + "\n{\n"
                elif (SubStr(StrLower(Trim(A_LoopField87)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally) and isLineAconstruct(Trim(A_LoopField87)) == True):
                    htCodeOutFixEnd += "\n}\n" + A_LoopField87 + "\n{\n"
                elif (isLineAconstruct(Trim(A_LoopField87)) == True):
                    htCodeOutFixEnd += A_LoopField87 + "\n{\n"
                else:
                    htCodeOutFixEnd += A_LoopField87 + "\n"
            code = StringTrimRight(htCodeOutFixEnd, 1)
        if (usePythonicColonSyntax == "off"):
            if (useEnd == "off" and useCurlyBraces == "off"):
                htCodeOutFixEnd = ""
                items88 = LoopParseFunc(code, "\n", "\r")
                for A_Index88 , A_LoopField88 in enumerate(items88, start=0):
                    if (isLineAconstruct(Trim(A_LoopField88)) == True):
                        htCodeOutFixEnd += A_LoopField88 + ":\n"
                    else:
                        htCodeOutFixEnd += A_LoopField88 + "\n"
                code = StringTrimRight(htCodeOutFixEnd, 1)
        if (useCurlyBraces == "off" and useEnd == "off"):
            code = AddCurlyBraces(code)
        outTrimCode = ""
        items89 = LoopParseFunc(code, "\n", "\r")
        for A_Index89 , A_LoopField89 in enumerate(items89, start=0):
            outTrimCode += Trim(A_LoopField89) + "\n"
        code = StringTrimRight(outTrimCode, 1)
        # for converting c++ to js and py
        #code := StrReplace(code, "{}", "[]")
        outCodeFixBraces = ""
        for A_Index90 in range(0, 2 + 0):
            outCodeFixBraces = ""
            items91 = LoopParseFunc(code, "\n", "\r")
            for A_Index91 , A_LoopField91 in enumerate(items91, start=0):
                if (InStr(Trim(A_LoopField91), "{") and Trim(A_LoopField91) != "{"):
                    outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField91), "{", "")) + "\n{\n"
                elif (InStr(Trim(A_LoopField91), "}") and Trim(A_LoopField91) != "}"):
                    outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField91), "}", "")) + "\n"
                else:
                    outCodeFixBraces += Trim(A_LoopField91) + "\n"
            code = StringTrimRight(outCodeFixBraces, 1)
        htCodeOutFixEnd = ""
        if (usePythonicColonSyntax == "on"):
            items92 = LoopParseFunc(code, "\n", "\r")
            for A_Index92 , A_LoopField92 in enumerate(items92, start=0):
                if (isLineAconstruct(Trim(A_LoopField92)) == True):
                    htCodeOutFixEnd += StringTrimRight(A_LoopField92, 1) + "\n"
                else:
                    htCodeOutFixEnd += A_LoopField92 + "\n"
            code = StringTrimRight(htCodeOutFixEnd, 1)
        #;; main loop ;;;
        #;; main loop ;;;
        #;; main loop ;;;
        #;; main loop ;;;
        fullLangAllOperators = GETfullLangAllOperators()
        fullLangAllOperators_HELP = GETfullLangAllOperators_HELP()
        if (isNotHTVMfile2 == 0):
            items93 = LoopParseFunc(code, "\n", "\r")
            for A_Index93 , A_LoopField93 in enumerate(items93, start=0):
                if (StrLower(A_LoopField93) == StrLower(keyWordMainLabel)):
                    didWeUseMainLabel = 1
                    if (langToConvertTo == langFileExtension_2):
                        codeOutFixAndAddMainFunc += keyWordMainLabel_2 + Chr(10)
                    if (langToConvertTo == "cpp"):
                        codeOutFixAndAddMainFunc += "int main(int argc, char* argv[])\n{\n"
                    if (langToConvertTo == "js" and useJavaScriptAmainFuncDef == "on"):
                        codeOutFixAndAddMainFunc += "async function main()\n{\n"
                    if (langToConvertTo == "ts" and useJavaScriptAmainFuncDef == "on"):
                        codeOutFixAndAddMainFunc += "async function main(): Promise<void>\n{\n"
                    if (langToConvertTo == "go"):
                        codeOutFixAndAddMainFunc += "func main()\n{\n"
                    if (langToConvertTo == "cs"):
                        codeOutFixAndAddMainFunc += "static void Main(string[] args)\n{\n"
                    if (langToConvertTo == "java"):
                        codeOutFixAndAddMainFunc += "public static void main(String[] args)\n{\n"
                    if (langToConvertTo == "kt"):
                        codeOutFixAndAddMainFunc += "fun main(args: Array<String>)\n{\n"
                    if (langToConvertTo == "swift"):
                        codeOutFixAndAddMainFunc += "func main()\n{\n"
                    if (langToConvertTo == "dart"):
                        codeOutFixAndAddMainFunc += "void main(List<String> arguments)\n{\n"
                else:
                    codeOutFixAndAddMainFunc += A_LoopField93 + "\n"
            if (didWeUseMainLabel != 1 and langToConvertTo == "cpp"):
                codeOutFixAndAddMainFunc = "int main(int argc, char* argv[])\n{\n" + codeOutFixAndAddMainFunc
            if (didWeUseMainLabel != 1 and langToConvertTo == "js" and useJavaScriptAmainFuncDef == "on"):
                codeOutFixAndAddMainFunc = "async function main()\n{\n" + codeOutFixAndAddMainFunc
            if (didWeUseMainLabel != 1 and langToConvertTo == "ts" and useJavaScriptAmainFuncDef == "on"):
                codeOutFixAndAddMainFunc = "async function main(): Promise<void>\n{\n" + codeOutFixAndAddMainFunc
            if (didWeUseMainLabel != 1 and langToConvertTo == "go"):
                codeOutFixAndAddMainFunc = "func main()\n{\n" + codeOutFixAndAddMainFunc
            if (didWeUseMainLabel != 1 and langToConvertTo == "cs"):
                codeOutFixAndAddMainFunc = "static void Main(string[] args)\n{\n" + codeOutFixAndAddMainFunc
            if (didWeUseMainLabel != 1 and langToConvertTo == "java"):
                codeOutFixAndAddMainFunc = "public static void main(String[] args)\n{\n" + codeOutFixAndAddMainFunc
            if (didWeUseMainLabel != 1 and langToConvertTo == "kt"):
                codeOutFixAndAddMainFunc = "fun main(args: Array<String>)\n{\n" + codeOutFixAndAddMainFunc
            if (didWeUseMainLabel != 1 and langToConvertTo == "swift"):
                codeOutFixAndAddMainFunc = "func main()\n{\n" + codeOutFixAndAddMainFunc
            if (didWeUseMainLabel != 1 and langToConvertTo == "dart"):
                codeOutFixAndAddMainFunc = "void main(List<String> arguments)\n{\n" + codeOutFixAndAddMainFunc
            code = StringTrimRight(codeOutFixAndAddMainFunc, 1)
            # main loop
            # main loop
        items94 = LoopParseFunc(code, "\n", "\r")
        for A_Index94 , A_LoopField94 in enumerate(items94, start=0):
            lookIntoTheNextLineForFuncWhitNoKeyWord.append(A_LoopField94)
        lookIntoTheNextLineForFuncWhitNoKeyWord.append(" ")
        htCode = ""
        print("=======UP==========")
        print(code)
        print("=======DOWN==========")
        items95 = LoopParseFunc(code, "\n", "\r")
        for A_Index95 , A_LoopField95 in enumerate(items95, start=0):
            lineDone = 0
            if (SubStr(A_LoopField95, 1, StrLen(keyWordComment)) == keyWordComment):
                str1 = StringTrimLeft(A_LoopField95, StrLen(keyWordComment))
                if (langToConvertTo == langFileExtension_2):
                    htCode += keyWordComment_2 + str1 + Chr(10)
                if (langToConvertTo == "cpp"):
                    htCode += "//" + str1 + Chr(10)
                if (langToConvertTo == "py"):
                    htCode += "#" + str1 + Chr(10)
                if (langToConvertTo == "js"):
                    htCode += "//" + str1 + Chr(10)
                if (langToConvertTo == "go"):
                    htCode += "//" + str1 + Chr(10)
                if (langToConvertTo == "lua"):
                    htCode += "--" + str1 + Chr(10)
                if (langToConvertTo == "cs"):
                    htCode += "//" + str1 + Chr(10)
                if (langToConvertTo == "java"):
                    htCode += "//" + str1 + Chr(10)
                if (langToConvertTo == "kt"):
                    htCode += "//" + str1 + Chr(10)
                if (langToConvertTo == "rb"):
                    htCode += "#" + str1 + Chr(10)
                if (langToConvertTo == "nim"):
                    htCode += "#" + str1 + Chr(10)
                if (langToConvertTo == "ahk"):
                    htCode += ";" + str1 + Chr(10)
                if (langToConvertTo == "swift"):
                    htCode += "//" + str1 + Chr(10)
                if (langToConvertTo == "dart"):
                    htCode += "//" + str1 + Chr(10)
                if (langToConvertTo == "ts"):
                    htCode += "//" + str1 + Chr(10)
                if (langToConvertTo == "groovy"):
                    htCode += "//" + str1 + Chr(10)
            elif (Trim(A_LoopField95) == keyWordCommentOpenMultiLine):
                if (langToConvertTo == langFileExtension_2):
                    htCode += keyWordCommentOpenMultiLine_2 + Chr(10)
                if (langToConvertTo == "cpp"):
                    htCode += "/*" + Chr(10)
                if (langToConvertTo == "py"):
                    htCode += Chr(34) + Chr(34) + Chr(34) + Chr(10)
                if (langToConvertTo == "js"):
                    htCode += "/*" + Chr(10)
                if (langToConvertTo == "go"):
                    htCode += "/*" + Chr(10)
                if (langToConvertTo == "lua"):
                    htCode += "--[[" + Chr(10)
                if (langToConvertTo == "cs"):
                    htCode += "/*" + Chr(10)
                if (langToConvertTo == "java"):
                    htCode += "/*" + Chr(10)
                if (langToConvertTo == "kt"):
                    htCode += "/*" + Chr(10)
                if (langToConvertTo == "rb"):
                    htCode += "=begin" + Chr(10)
                if (langToConvertTo == "nim"):
                    htCode += "#[" + Chr(10)
                if (langToConvertTo == "ahk"):
                    htCode += "/*" + Chr(10)
                if (langToConvertTo == "swift"):
                    htCode += "/*" + Chr(10)
                if (langToConvertTo == "dart"):
                    htCode += "/*" + Chr(10)
                if (langToConvertTo == "ts"):
                    htCode += "/*" + Chr(10)
                if (langToConvertTo == "groovy"):
                    htCode += "/*" + Chr(10)
            elif (Trim(A_LoopField95) == keyWordCommentCloseMultiLine):
                if (langToConvertTo == langFileExtension_2):
                    htCode += keyWordCommentCloseMultiLine_2 + Chr(10)
                if (langToConvertTo == "cpp"):
                    htCode += "*/" + Chr(10)
                if (langToConvertTo == "py"):
                    htCode += Chr(34) + Chr(34) + Chr(34) + Chr(10)
                if (langToConvertTo == "js"):
                    htCode += "*/" + Chr(10)
                if (langToConvertTo == "go"):
                    htCode += "*/" + Chr(10)
                if (langToConvertTo == "lua"):
                    htCode += "]]" + Chr(10)
                if (langToConvertTo == "cs"):
                    htCode += "*/" + Chr(10)
                if (langToConvertTo == "java"):
                    htCode += "*/" + Chr(10)
                if (langToConvertTo == "kt"):
                    htCode += "*/" + Chr(10)
                if (langToConvertTo == "rb"):
                    htCode += "=end" + Chr(10)
                if (langToConvertTo == "nim"):
                    htCode += "]#" + Chr(10)
                if (langToConvertTo == "ahk"):
                    htCode += "*/" + Chr(10)
                if (langToConvertTo == "swift"):
                    htCode += "*/" + Chr(10)
                if (langToConvertTo == "dart"):
                    htCode += "*/" + Chr(10)
                if (langToConvertTo == "ts"):
                    htCode += "*/" + Chr(10)
                if (langToConvertTo == "groovy"):
                    htCode += "*/" + Chr(10)
            elif (SubStr(StrLower(Trim(A_LoopField95)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF)):
                str1 = Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordIF)))
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"))
                str1 = StringTrimRight(str1, 1)
                str1 = StringTrimLeft(str1, 1)
                if (langToConvertTo == langFileExtension_2):
                    if (usePythonicColonSyntax_2 == "on"):
                        if (useParentheses == "on"):
                            if (useParentheses_2 == "on"):
                                htCode += keyWordIF_2 + str1 + ":\n"
                            else:
                                htCode += keyWordIF_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":\n"
                        else:
                            if (useParentheses_2 == "on"):
                                htCode += keyWordIF_2 + "(" + str1 + "):\n"
                            else:
                                htCode += keyWordIF_2 + str1 + ":\n"
                    else:
                        if (useParentheses == "on"):
                            if (useParentheses_2 == "on"):
                                htCode += keyWordIF_2 + str1 + "\n"
                            else:
                                htCode += keyWordIF_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + "\n"
                        else:
                            if (useParentheses_2 == "on"):
                                htCode += keyWordIF_2 + "(" + str1 + ")\n"
                            else:
                                htCode += keyWordIF_2 + str1 + "\n"
                if (langToConvertTo == "cpp"):
                    if (useParentheses == "on"):
                        htCode += "if " + str1 + Chr(10)
                    else:
                        htCode += "if (" + str1 + ")" + Chr(10)
                if (langToConvertTo == "py"):
                    htCode += "if " + str1 + ":" + Chr(10)
                if (langToConvertTo == "js"):
                    if (useParentheses == "on"):
                        htCode += "if " + str1 + Chr(10)
                    else:
                        htCode += "if (" + str1 + ")" + Chr(10)
                if (langToConvertTo == "go"):
                    htCode += "if " + str1 + "\n"
                if (langToConvertTo == "lua"):
                    htCode += "if " + str1 + " then\n"
                if (langToConvertTo == "cs"):
                    if (useParentheses == "on"):
                        htCode += "if " + str1 + "\n"
                    else:
                        htCode += "if (" + str1 + ")\n"
                if (langToConvertTo == "java"):
                    if (useParentheses == "on"):
                        htCode += "if " + str1 + "\n"
                    else:
                        htCode += "if (" + str1 + ")\n"
                if (langToConvertTo == "kt"):
                    if (useParentheses == "on"):
                        htCode += "if " + str1 + "\n"
                    else:
                        htCode += "if (" + str1 + ")\n"
                if (langToConvertTo == "rb"):
                    htCode += "if " + str1 + "\n"
                if (langToConvertTo == "nim"):
                    htCode += "if " + str1 + ":\n"
                if (langToConvertTo == "ahk"):
                    if (useParentheses == "on"):
                        htCode += "if " + str1 + "\n"
                    else:
                        htCode += "if (" + str1 + ")\n"
                if (langToConvertTo == "swift"):
                    htCode += "if " + str1 + "\n"
                if (langToConvertTo == "dart"):
                    if (useParentheses == "on"):
                        htCode += "if " + str1 + "\n"
                    else:
                        htCode += "if (" + str1 + ")\n"
                if (langToConvertTo == "ts"):
                    if (useParentheses == "on"):
                        htCode += "if " + str1 + "\n"
                    else:
                        htCode += "if (" + str1 + ")\n"
                if (langToConvertTo == "groovy"):
                    htCode += "if " + str1 + "\n"
            elif (SubStr(StrLower(Trim(A_LoopField95)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf)):
                str1 = Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordElseIf)))
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"))
                str1 = StringTrimRight(str1, 1)
                str1 = StringTrimLeft(str1, 1)
                if (langToConvertTo == langFileExtension_2):
                    if (usePythonicColonSyntax_2 == "on"):
                        if (useParentheses == "on"):
                            if (useParentheses_2 == "on"):
                                htCode += keyWordElseIf_2 + str1 + ":\n"
                            else:
                                htCode += keyWordElseIf_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":\n"
                        else:
                            if (useParentheses_2 == "on"):
                                htCode += keyWordElseIf_2 + "(" + str1 + "):\n"
                            else:
                                htCode += keyWordElseIf_2 + str1 + ":\n"
                    else:
                        if (useParentheses == "on"):
                            if (useParentheses_2 == "on"):
                                htCode += keyWordElseIf_2 + str1 + "\n"
                            else:
                                htCode += keyWordElseIf_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + "\n"
                        else:
                            if (useParentheses_2 == "on"):
                                htCode += keyWordElseIf_2 + "(" + str1 + ")\n"
                            else:
                                htCode += keyWordElseIf_2 + str1 + "\n"
                if (langToConvertTo == "cpp"):
                    if (useParentheses == "on"):
                        htCode += "else if " + str1 + "\n"
                    else:
                        htCode += "else if (" + str1 + ")\n"
                if (langToConvertTo == "py"):
                    htCode += "elif " + str1 + ":\n"
                if (langToConvertTo == "js"):
                    if (useParentheses == "on"):
                        htCode += "else if " + str1 + "\n"
                    else:
                        htCode += "else if (" + str1 + ")\n"
                if (langToConvertTo == "go"):
                    htCode += "else if " + str1 + "\n"
                if (langToConvertTo == "lua"):
                    htCode += "elseif " + str1 + " then\n"
                if (langToConvertTo == "cs"):
                    if (useParentheses == "on"):
                        htCode += "else if " + str1 + "\n"
                    else:
                        htCode += "else if (" + str1 + ")\n"
                if (langToConvertTo == "java"):
                    if (useParentheses == "on"):
                        htCode += "else if " + str1 + "\n"
                    else:
                        htCode += "else if (" + str1 + ")\n"
                if (langToConvertTo == "kt"):
                    if (useParentheses == "on"):
                        htCode += "else if " + str1 + "\n"
                    else:
                        htCode += "else if (" + str1 + ")\n"
                if (langToConvertTo == "rb"):
                    htCode += "elsif " + str1 + "\n"
                if (langToConvertTo == "nim"):
                    htCode += "elif " + str1 + ":\n"
                if (langToConvertTo == "ahk"):
                    if (useParentheses == "on"):
                        htCode += "else if " + str1 + "\n"
                    else:
                        htCode += "else if (" + str1 + ")\n"
                if (langToConvertTo == "swift"):
                    htCode += "else if " + str1 + "\n"
                if (langToConvertTo == "dart"):
                    if (useParentheses == "on"):
                        htCode += "else if " + str1 + "\n"
                    else:
                        htCode += "else if (" + str1 + ")\n"
                if (langToConvertTo == "ts"):
                    if (useParentheses == "on"):
                        htCode += "else if " + str1 + "\n"
                    else:
                        htCode += "else if (" + str1 + ")\n"
                if (langToConvertTo == "groovy"):
                    htCode += "else if " + str1 + "\n"
            elif (StrLower(Trim(A_LoopField95)) == StrLower(keyWordElse) or StrLower(Trim(A_LoopField95)) == StrLower(keyWordElse + ":")):
                if (langToConvertTo == langFileExtension_2):
                    if (usePythonicColonSyntax_2 == "on"):
                        htCode += keyWordElse_2 + ":\n"
                    else:
                        htCode += keyWordElse_2 + "\n"
                if (langToConvertTo == "cpp"):
                    htCode += "else\n"
                if (langToConvertTo == "py"):
                    htCode += "else:\n"
                if (langToConvertTo == "js"):
                    htCode += "else\n"
                if (langToConvertTo == "go"):
                    htCode += "else\n"
                if (langToConvertTo == "lua"):
                    htCode += "else\n"
                if (langToConvertTo == "cs"):
                    htCode += "else\n"
                if (langToConvertTo == "java"):
                    htCode += "else\n"
                if (langToConvertTo == "kt"):
                    htCode += "else\n"
                if (langToConvertTo == "rb"):
                    htCode += "else\n"
                if (langToConvertTo == "nim"):
                    htCode += "else:\n"
                if (langToConvertTo == "ahk"):
                    htCode += "else\n"
                if (langToConvertTo == "swift"):
                    htCode += "else\n"
                if (langToConvertTo == "dart"):
                    htCode += "else\n"
                if (langToConvertTo == "ts"):
                    htCode += "else\n"
                if (langToConvertTo == "groovy"):
                    htCode += "else\n"
            elif (SubStr(StrLower(Trim(A_LoopField95)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)):
                str1 = Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordWhileLoop)))
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"))
                str1 = StringTrimRight(str1, 1)
                str1 = StringTrimLeft(str1, 1)
                if (langToConvertTo == langFileExtension_2):
                    if (usePythonicColonSyntax_2 == "on"):
                        if (useParentheses == "on"):
                            if (useParentheses_2 == "on"):
                                htCode += keyWordWhileLoop_2 + str1 + ":" + Chr(10)
                            else:
                                htCode += keyWordWhileLoop_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":" + Chr(10)
                        else:
                            if (useParentheses_2 == "on"):
                                htCode += keyWordWhileLoop_2 + "(" + str1 + "):" + Chr(10)
                            else:
                                htCode += keyWordWhileLoop_2 + str1 + ":" + Chr(10)
                    else:
                        if (useParentheses == "on"):
                            if (useParentheses_2 == "on"):
                                htCode += keyWordWhileLoop_2 + str1 + Chr(10)
                            else:
                                htCode += keyWordWhileLoop_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + Chr(10)
                        else:
                            if (useParentheses_2 == "on"):
                                htCode += keyWordWhileLoop_2 + "(" + str1 + ")" + Chr(10)
                            else:
                                htCode += keyWordWhileLoop_2 + str1 + Chr(10)
                if (langToConvertTo == "cpp"):
                    if (useParentheses == "on"):
                        htCode += "while " + str1 + Chr(10)
                    else:
                        htCode += "while (" + str1 + ")" + Chr(10)
                if (langToConvertTo == "py"):
                    htCode += "while " + str1 + ":" + Chr(10)
                if (langToConvertTo == "js"):
                    if (useParentheses == "on"):
                        htCode += "while " + str1 + Chr(10)
                    else:
                        htCode += "while (" + str1 + ")" + Chr(10)
                if (langToConvertTo == "go"):
                    htCode += "for " + str1 + Chr(10)
                if (langToConvertTo == "lua"):
                    htCode += "while " + str1 + " do" + Chr(10)
                if (langToConvertTo == "cs"):
                    if (useParentheses == "on"):
                        htCode += "while " + str1 + Chr(10)
                    else:
                        htCode += "while (" + str1 + ")" + Chr(10)
                if (langToConvertTo == "java"):
                    if (useParentheses == "on"):
                        htCode += "while " + str1 + Chr(10)
                    else:
                        htCode += "while (" + str1 + ")" + Chr(10)
                if (langToConvertTo == "kt"):
                    if (useParentheses == "on"):
                        htCode += "while " + str1 + "\n"
                    else:
                        htCode += "while (" + str1 + ")\n"
                if (langToConvertTo == "rb"):
                    htCode += "while " + str1 + "\n"
                if (langToConvertTo == "nim"):
                    htCode += "while " + str1 + ":\n"
                if (langToConvertTo == "ahk"):
                    if (useParentheses == "on"):
                        htCode += "while " + str1 + "\n"
                    else:
                        htCode += "while (" + str1 + ")\n"
                if (langToConvertTo == "swift"):
                    htCode += "while " + str1 + "\n"
                if (langToConvertTo == "dart"):
                    if (useParentheses == "on"):
                        htCode += "while " + str1 + "\n"
                    else:
                        htCode += "while (" + str1 + ")\n"
                if (langToConvertTo == "ts"):
                    if (useParentheses == "on"):
                        htCode += "while " + str1 + "\n"
                    else:
                        htCode += "while (" + str1 + ")\n"
                if (langToConvertTo == "groovy"):
                    htCode += "while " + str1 + "\n"
            elif (StrLower(Trim(A_LoopField95)) == StrLower(keyWordTry) or StrLower(Trim(A_LoopField95)) == StrLower(keyWordTry + ":")):
                if (langToConvertTo == langFileExtension_2):
                    if (usePythonicColonSyntax_2 == "on"):
                        htCode += keyWordTry_2 + ":\n"
                    else:
                        htCode += keyWordTry_2 + "\n"
                if (langToConvertTo == "cpp"):
                    htCode += "try\n"
                if (langToConvertTo == "py"):
                    htCode += "try:\n"
                if (langToConvertTo == "js"):
                    htCode += "try\n"
                if (langToConvertTo == "go"):
                    htCode += "GO DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK\n"
                if (langToConvertTo == "lua"):
                    htCode += "LUA DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK\n"
                if (langToConvertTo == "cs"):
                    htCode += "try\n"
                if (langToConvertTo == "java"):
                    htCode += "try\n"
                if (langToConvertTo == "kt"):
                    htCode += "try\n"
                if (langToConvertTo == "rb"):
                    htCode += "begin\n"
                if (langToConvertTo == "nim"):
                    htCode += "try:\n"
                if (langToConvertTo == "ahk"):
                    htCode += "try\n"
                if (langToConvertTo == "swift"):
                    htCode += "do\n"
                if (langToConvertTo == "dart"):
                    htCode += "try\n"
                if (langToConvertTo == "ts"):
                    htCode += "try\n"
                if (langToConvertTo == "groovy"):
                    htCode += "try\n"
            elif (SubStr(StrLower(Trim(A_LoopField95)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)):
                str1 = Trim(StrReplace(StrReplace(StringTrimLeft(A_LoopField95, StrLen(keyWordCatch)), "(", ""), ")", ""))
                theTryCatchVarForErrors = str1
                if (langToConvertTo == langFileExtension_2):
                    if (usePythonicColonSyntax_2 == "on"):
                        htCode += keyWordCatch_2 + "(" + str1 + "):\n"
                    else:
                        htCode += keyWordCatch_2 + "(" + str1 + ")\n"
                if (langToConvertTo == "cpp"):
                    htCode += "catch (const std::exception& " + str1 + ")\n"
                if (langToConvertTo == "py"):
                    htCode += "except Exception as " + str1 + ":\n"
                if (langToConvertTo == "js"):
                    htCode += "catch (" + str1 + ")\n"
                if (langToConvertTo == "go"):
                    htCode += "GO DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK\n"
                if (langToConvertTo == "lua"):
                    htCode += "LUA DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK\n"
                if (langToConvertTo == "cs"):
                    htCode += "catch (Exception " + str1 + ")\n"
                if (langToConvertTo == "java"):
                    htCode += "catch (Exception " + str1 + ")\n"
                if (langToConvertTo == "kt"):
                    htCode += "catch (" + str1 + ": Exception)\n"
                if (langToConvertTo == "rb"):
                    htCode += "rescue => " + str1 + "\n"
                if (langToConvertTo == "nim"):
                    htCode += "except ValueError as " + str1 + ":\n"
                if (langToConvertTo == "ahk"):
                    htCode += "catch " + str1 + "\n"
                if (langToConvertTo == "swift"):
                    htCode += "catch let " + str1 + " as NSError\n"
                if (langToConvertTo == "dart"):
                    htCode += "catch (" + str1 + ")\n"
                if (langToConvertTo == "ts"):
                    htCode += "catch (" + str1 + ")\n"
                if (langToConvertTo == "groovy"):
                    htCode += "catch (Exception " + str1 + ")\n"
            elif (StrLower(Trim(A_LoopField95)) == StrLower(keyWordFinally) or StrLower(Trim(A_LoopField95)) == StrLower(keyWordFinally + ":")):
                if (langToConvertTo == langFileExtension_2):
                    if (usePythonicColonSyntax_2 == "on"):
                        htCode += keyWordFinally_2 + ":\n"
                    else:
                        htCode += keyWordFinally_2 + "\n"
                if (langToConvertTo == "cpp"):
                    htCode += "if (" + Chr(34) + "finally dosent exist in c++" + Chr(34) + " == " + Chr(34) + "finally dosent exist in c++" + Chr(34) + ")\n"
                if (langToConvertTo == "py"):
                    htCode += "finally:\n"
                if (langToConvertTo == "js"):
                    htCode += "finally\n"
                if (langToConvertTo == "go"):
                    htCode += "GO DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK\n"
                if (langToConvertTo == "lua"):
                    htCode += "LUA DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK\n"
                if (langToConvertTo == "cs"):
                    htCode += "finally\n"
                if (langToConvertTo == "java"):
                    htCode += "finally\n"
                if (langToConvertTo == "kt"):
                    htCode += "finally\n"
                if (langToConvertTo == "rb"):
                    htCode += "ensure\n"
                if (langToConvertTo == "nim"):
                    htCode += "finally:\n"
                if (langToConvertTo == "ahk"):
                    htCode += "finally\n"
                if (langToConvertTo == "swift"):
                    htCode += "if (" + Chr(34) + "finally dosent exist in swift" + Chr(34) + " == " + Chr(34) + "finally dosent exist in swift" + Chr(34) + ")\n"
                if (langToConvertTo == "dart"):
                    htCode += "finally\n"
                if (langToConvertTo == "ts"):
                    htCode += "finally\n"
                if (langToConvertTo == "groovy"):
                    htCode += "finally\n"
            elif (SubStr(StrLower(Trim(A_LoopField95)), 1, StrLen(StrLower(keyWordThrow))) == StrLower(keyWordThrow)):
                str1 = expressionParserTranspiler(fixArray1234(Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordThrow)))))
                if (langToConvertTo == langFileExtension_2):
                    if (useSemicolon_2 == "on"):
                        htCode += keyWordThrow_2 + " " + keyWordErrorMsg + "(" + str1 + ");\n"
                    else:
                        htCode += keyWordThrow_2 + " " + keyWordErrorMsg + "(" + str1 + ")\n"
                if (langToConvertTo == "cpp"):
                    htCode += "throw std::runtime_error(" + str1 + ");\n"
                if (langToConvertTo == "py"):
                    htCode += "raise Exception(" + str1 + ")\n"
                if (langToConvertTo == "js"):
                    htCode += "throw new Error(" + str1 + ");\n"
                if (langToConvertTo == "go"):
                    htCode += "GO DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK\n"
                if (langToConvertTo == "lua"):
                    htCode += "LUA DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK\n"
                if (langToConvertTo == "cs"):
                    htCode += "throw new Exception(" + str1 + ");\n"
                if (langToConvertTo == "java"):
                    htCode += "throw new Exception(" + str1 + ");\n"
                if (langToConvertTo == "kt"):
                    htCode += "throw Exception(" + str1 + ")" + Chr(10)
                if (langToConvertTo == "rb"):
                    htCode += "raise " + str1 + Chr(10)
                if (langToConvertTo == "nim"):
                    htCode += "raise newException(ValueError, " + str1 + ")\n"
                if (langToConvertTo == "ahk"):
                    htCode += "throw " + str1 + "\n"
                if (langToConvertTo == "swift"):
                    htCode += "try ErrorMsg(" + str1 + ")\n"
                if (langToConvertTo == "dart"):
                    htCode += "throw Exception(" + str1 + ");\n"
                if (langToConvertTo == "ts"):
                    htCode += " throw new Error(" + str1 + ");\n"
                if (langToConvertTo == "groovy"):
                    htCode += "throw new Exception(" + str1 + ")\n"
            elif (StrLower(A_LoopField95) == StrLower(keyWordBreak) or StrLower(A_LoopField95) == StrLower(keyWordBreak + ";")):
                if (langToConvertTo == langFileExtension_2):
                    if (useSemicolon_2 == "on"):
                        htCode += keyWordBreak_2 + ";\n"
                    else:
                        htCode += keyWordBreak_2 + "\n"
                if (langToConvertTo == "cpp"):
                    htCode += "break;\n"
                if (langToConvertTo == "py"):
                    htCode += "break\n"
                if (langToConvertTo == "js"):
                    htCode += "break;\n"
                if (langToConvertTo == "go"):
                    htCode += "break\n"
                if (langToConvertTo == "lua"):
                    htCode += "break\n"
                if (langToConvertTo == "cs"):
                    htCode += "break;\n"
                if (langToConvertTo == "java"):
                    htCode += "break;\n"
                if (langToConvertTo == "kt"):
                    htCode += "break\n"
                if (langToConvertTo == "rb"):
                    htCode += "break\n"
                if (langToConvertTo == "nim"):
                    htCode += "break\n"
                if (langToConvertTo == "ahk"):
                    htCode += "break\n"
                if (langToConvertTo == "swift"):
                    htCode += "break;\n"
                if (langToConvertTo == "dart"):
                    htCode += "break;\n"
                if (langToConvertTo == "ts"):
                    htCode += "break;\n"
                if (langToConvertTo == "groovy"):
                    htCode += "break;\n"
            elif (StrLower(A_LoopField95) == StrLower(Trim(keyWordReturnStatement)) or StrLower(A_LoopField95) == StrLower(Trim(keyWordReturnStatement) + ";")):
                if (langToConvertTo == langFileExtension_2):
                    if (useSemicolon_2 == "on"):
                        htCode += keyWordReturnStatement_2 + ";\n"
                    else:
                        htCode += keyWordReturnStatement_2 + "\n"
                if (langToConvertTo == "cpp"):
                    htCode += "return;\n"
                if (langToConvertTo == "py"):
                    htCode += "return\n"
                if (langToConvertTo == "js"):
                    htCode += "return;\n"
                if (langToConvertTo == "go"):
                    htCode += "break\n"
                if (langToConvertTo == "lua"):
                    htCode += "return\n"
                if (langToConvertTo == "cs"):
                    htCode += "return;\n"
                if (langToConvertTo == "java"):
                    htCode += "return;\n"
                if (langToConvertTo == "kt"):
                    htCode += "return\n"
                if (langToConvertTo == "rb"):
                    htCode += "return\n"
                if (langToConvertTo == "nim"):
                    htCode += "return\n"
                if (langToConvertTo == "ahk"):
                    htCode += "return\n"
                if (langToConvertTo == "swift"):
                    htCode += "return;\n"
                if (langToConvertTo == "dart"):
                    htCode += "return;\n"
                if (langToConvertTo == "ts"):
                    htCode += "return;\n"
                if (langToConvertTo == "groovy"):
                    htCode += "return;\n"
            elif (SubStr(Trim(StrLower(A_LoopField95)), 1, StrLen(StrLower(keyWordReturnStatement))) == StrLower(keyWordReturnStatement)):
                str1 = Trim(expressionParserTranspiler(Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordReturnStatement)))))
                if (langToConvertTo == langFileExtension_2):
                    if (useSemicolon_2 == "on"):
                        htCode += keyWordReturnStatement_2 + str1 + ";\n"
                    else:
                        htCode += keyWordReturnStatement_2 + str1 + "\n"
                if (langToConvertTo == "cpp"):
                    htCode += "return " + str1 + ";\n"
                if (langToConvertTo == "py"):
                    htCode += "return " + str1 + "\n"
                if (langToConvertTo == "js"):
                    htCode += "return " + str1 + ";\n"
                if (langToConvertTo == "go"):
                    htCode += "return " + str1 + "\n"
                if (langToConvertTo == "lua"):
                    htCode += "return " + str1 + "\n"
                if (langToConvertTo == "cs"):
                    htCode += "return " + str1 + ";\n"
                if (langToConvertTo == "java"):
                    htCode += "return " + str1 + ";\n"
                if (langToConvertTo == "kt"):
                    htCode += "return " + str1 + "\n"
                if (langToConvertTo == "rb"):
                    htCode += "return " + str1 + "\n"
                if (langToConvertTo == "nim"):
                    htCode += "return " + str1 + "\n"
                if (langToConvertTo == "ahk"):
                    htCode += "return " + str1 + "\n"
                if (langToConvertTo == "swift"):
                    htCode += "return " + str1 + ";\n"
                if (langToConvertTo == "dart"):
                    htCode += "return " + str1 + ";\n"
                if (langToConvertTo == "ts"):
                    htCode += "return " + str1 + ";\n"
                if (langToConvertTo == "groovy"):
                    htCode += "return " + str1 + ";\n"
            elif (StrLower(A_LoopField95) == StrLower(keyWordContinue) or StrLower(A_LoopField95) == StrLower(keyWordContinue + ";")):
                if (langToConvertTo == langFileExtension_2):
                    if (useSemicolon_2 == "on"):
                        htCode += keyWordContinue_2 + ";\n"
                    else:
                        htCode += keyWordContinue_2 + "\n"
                if (langToConvertTo == "cpp"):
                    htCode += "continue;\n"
                if (langToConvertTo == "py"):
                    htCode += "continue\n"
                if (langToConvertTo == "js"):
                    htCode += "continue;\n"
                if (langToConvertTo == "go"):
                    htCode += "continue\n"
                if (langToConvertTo == "lua"):
                    htCode += "goto continue\n"
                if (langToConvertTo == "cs"):
                    htCode += "continue;\n"
                if (langToConvertTo == "java"):
                    htCode += "continue;\n"
                if (langToConvertTo == "kt"):
                    htCode += "continue\n"
                if (langToConvertTo == "rb"):
                    htCode += "next\n"
                if (langToConvertTo == "nim"):
                    htCode += "continue\n"
                if (langToConvertTo == "ahk"):
                    htCode += "continue\n"
                if (langToConvertTo == "swift"):
                    htCode += "continue;\n"
                if (langToConvertTo == "dart"):
                    htCode += "continue;\n"
                if (langToConvertTo == "ts"):
                    htCode += "continue;\n"
                if (langToConvertTo == "groovy"):
                    htCode += "continue;\n"
            elif (StrLower(A_LoopField95) == "::" + keyWordContinue + "::"):
                if (langToConvertTo == langFileExtension_2):
                    htCode += "::" + keyWordContinue_2 + "::\n"
                if (langToConvertTo == "lua"):
                    htCode += "::continue::\n"
            elif (StrLower(A_LoopField95) == StrLower(keyWordLoopInfinite) or StrLower(A_LoopField95) == StrLower(keyWordLoopInfinite + ":")):
                # infinity loops
                haveWeEverUsedAloop = 1
                lineDone = 1
                if (langToConvertTo == "py"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , value in enumerate(iter(int, 1), start=" + AHKlikeLoopsIndexedAt + "):"
                if (langToConvertTo == "js"):
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "cpp"):
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "go"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++"
                if (langToConvertTo == "lua"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + ", someLimit do"
                if (langToConvertTo == "cs"):
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "java"):
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "kt"):
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit)"
                if (langToConvertTo == "rb"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit do"
                if (langToConvertTo == "nim"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit:"
                if (langToConvertTo == "ahk"):
                    var1 = "Loop"
                if (langToConvertTo == "swift"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " ..< someLimit"
                if (langToConvertTo == "dart"):
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "ts"):
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "groovy"):
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit)"
                if (langToConvertTo == langFileExtension_2):
                    if (usePythonicColonSyntax_2 == "on"):
                        var1 = keyWordLoopInfinite_2 + ":"
                    else:
                        var1 = keyWordLoopInfinite_2
                nothing = ""
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing
                htCodeAcurlyBraceAddSomeVrasFixNL = 1
                lineDone = 1
                if (langToConvertTo != "ahk" and langToConvertTo != langFileExtension_2):
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n"
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength)
                AindexcharLength = AindexcharLength + 1
                htCode += htCodeLoopfixa1 + "\n" + var1 + "\n"
            elif (SubStr(Trim(StrLower(A_LoopField95)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop) and SubStr(Trim(StrLower(A_LoopField95)), 1, StrLen(StrLower(keyWordLoop)) + 2) != StrLower(keyWordLoop) + "% " and SubStr(Trim(StrLower(A_LoopField95)), 1, StrLen(StrLower(keyWordLoopParse))) != StrLower(keyWordLoopParse)):
                out2 = StringTrimLeft(A_LoopField95, StrLen(keyWordLoop))
                out2 = StrReplace(out2, ":", "")
                #MsgBox % out2
                #MsgBox, % out2
                out2 = Trim(out2)
                myVar = out2
                lineYGI = expressionParserTranspiler(myVar)
                line = lineYGI
                haveWeEverUsedAloop = 1
                #MsgBox, % line
                if (langToConvertTo == "py"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in range(" + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + "):"
                if (langToConvertTo == "js"):
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "cpp"):
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "go"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++"
                if (langToConvertTo == "lua"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + " do"
                if (langToConvertTo == "cs"):
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "java"):
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "kt"):
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")"
                if (langToConvertTo == "rb"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + " do"
                if (langToConvertTo == "nim"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ":"
                if (langToConvertTo == "ahk"):
                    var1 = "Loop, " + line
                if (langToConvertTo == "swift"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " ..< " + line + " + " + AHKlikeLoopsIndexedAt
                if (langToConvertTo == "dart"):
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "ts"):
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "groovy"):
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")"
                if (langToConvertTo == langFileExtension_2):
                    if (usePythonicColonSyntax_2 == "on"):
                        var1 = Trim(keyWordLoop_2) + " " + line + ":"
                    else:
                        var1 = Trim(keyWordLoop_2) + " " + line
                nothing = ""
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing
                htCodeAcurlyBraceAddSomeVrasFixNL = 1
                if (langToConvertTo != "ahk" and langToConvertTo != langFileExtension_2):
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n"
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength)
                AindexcharLength = AindexcharLength + 1
                lineDone = 1
                htCode += htCodeLoopfixa1 + "\n" + var1 + "\n"
            elif (SubStr(Trim(StrLower(A_LoopField95)), 1, StrLen(StrLower(keyWordLoop)) + 2) == StrLower(keyWordLoop) + "% "):
                out2 = StringTrimLeft(A_LoopField95, StrLen(keyWordLoop) + 2)
                out2 = StrReplace(out2, ":", "")
                #MsgBox % out2
                #MsgBox, % out2
                out2 = Trim(out2)
                myVar = out2
                lineYGI = expressionParserTranspiler(myVar)
                line = lineYGI
                haveWeEverUsedAloop = 1
                #MsgBox, % line
                if (langToConvertTo == "py"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in range(" + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + "):"
                if (langToConvertTo == "js"):
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "cpp"):
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "go"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++"
                if (langToConvertTo == "lua"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + " do"
                if (langToConvertTo == "cs"):
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "java"):
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "kt"):
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")"
                if (langToConvertTo == "rb"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + " do"
                if (langToConvertTo == "nim"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ":"
                if (langToConvertTo == "ahk"):
                    var1 = "Loop, % " + line
                if (langToConvertTo == "swift"):
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " ..< " + line + " + " + AHKlikeLoopsIndexedAt
                if (langToConvertTo == "dart"):
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "ts"):
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "groovy"):
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")"
                if (langToConvertTo == langFileExtension_2):
                    if (usePythonicColonSyntax_2 == "on"):
                        var1 = Trim(keyWordLoop_2) + " % " + line + ":"
                    else:
                        var1 = Trim(keyWordLoop_2) + " % " + line
                nothing = ""
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing
                htCodeAcurlyBraceAddSomeVrasFixNL = 1
                if (langToConvertTo != "ahk" and langToConvertTo != langFileExtension_2):
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n"
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength)
                AindexcharLength = AindexcharLength + 1
                lineDone = 1
                htCode += htCodeLoopfixa1 + "\n" + var1 + "\n"
            elif (SubStr(StrLower(A_LoopField95), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)):
                var1 = StringTrimLeft(A_LoopField95, StrLen(keyWordLoopParse))
                out2 = StrReplace(out2, ":", "")
                lineDone = 1
                line1 = Trim(StrSplit(var1, ",", 1))
                line1 = expressionParserTranspiler(line1)
                line2 = ""
                line3 = ""
                itemsOut = ""
                line2 = Trim(StrSplit(var1, ",", 2))
                line3 = Trim(StrSplit(var1, ",", 3))
                if (InStr(var1, keyWordEscpaeChar + ",")):
                    line2 = Chr(34) + "," + Chr(34)
                    if (langToConvertTo == "py"):
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                    if (langToConvertTo == "js"):
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");"
                    if (langToConvertTo == "cpp"):
                        itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");"
                    if (langToConvertTo == "go"):
                        itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ")"
                    if (langToConvertTo == "lua"):
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                    if (langToConvertTo == "cs"):
                        itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");"
                    if (langToConvertTo == "java"):
                        itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");"
                    if (langToConvertTo == "kt"):
                        itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                    if (langToConvertTo == "rb"):
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                    if (langToConvertTo == "nim"):
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                    if (langToConvertTo == "ahk"):
                        itemsOut = "\n"
                    if (langToConvertTo == "swift"):
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                    if (langToConvertTo == "dart"):
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                    if (langToConvertTo == "ts"):
                        itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                    if (langToConvertTo == "groovy"):
                        itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                else:
                    if (line2 == "" and line3 == ""):
                        # nothing so only each char
                        if (langToConvertTo == "py" or langToConvertTo == "js"):
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")"
                        if (langToConvertTo == "cpp"):
                            itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");"
                        if (langToConvertTo == "go"):
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ")"
                        if (langToConvertTo == "lua"):
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")"
                        if (langToConvertTo == "cs"):
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");"
                        if (langToConvertTo == "java"):
                            itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");"
                        if (langToConvertTo == "kt"):
                            itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")"
                        if (langToConvertTo == "rb"):
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")"
                        if (langToConvertTo == "nim"):
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")"
                        if (langToConvertTo == "ahk"):
                            itemsOut = "\n"
                        if (langToConvertTo == "swift"):
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")"
                        if (langToConvertTo == "dart"):
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")"
                        if (langToConvertTo == "ts"):
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")"
                        if (langToConvertTo == "groovy"):
                            itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")"
                    if (line2 != "" and line3 == ""):
                        if (InStr(line2, keyWordEscpaeChar)):
                            line2 = Chr(34) + line2 + Chr(34)
                        if (langToConvertTo == "py" or langToConvertTo == "js"):
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                        if (langToConvertTo == "cpp"):
                            itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");"
                        if (langToConvertTo == "go"):
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ")"
                        if (langToConvertTo == "lua"):
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                        if (langToConvertTo == "cs"):
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");"
                        if (langToConvertTo == "java"):
                            itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");"
                        if (langToConvertTo == "kt"):
                            itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                        if (langToConvertTo == "rb"):
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                        if (langToConvertTo == "nim"):
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                        if (langToConvertTo == "ahk"):
                            itemsOut = "\n"
                        if (langToConvertTo == "swift"):
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                        if (langToConvertTo == "dart"):
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                        if (langToConvertTo == "ts"):
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                        if (langToConvertTo == "groovy"):
                            itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")"
                    if (line2 != "" and line3 != ""):
                        if (InStr(line2, keyWordEscpaeChar)):
                            line2 = Chr(34) + line2 + Chr(34)
                        if (InStr(line3, keyWordEscpaeChar)):
                            line3 = Chr(34) + line3 + Chr(34)
                        if (langToConvertTo == "py" or langToConvertTo == "js"):
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")"
                        if (langToConvertTo == "cpp"):
                            itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");"
                        if (langToConvertTo == "go"):
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")"
                        if (langToConvertTo == "lua"):
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")"
                        if (langToConvertTo == "cs"):
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");"
                        if (langToConvertTo == "java"):
                            itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");"
                        if (langToConvertTo == "kt"):
                            itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")"
                        if (langToConvertTo == "rb"):
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")"
                        if (langToConvertTo == "nim"):
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")"
                        if (langToConvertTo == "ahk"):
                            itemsOut = "\n"
                        if (langToConvertTo == "swift"):
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")"
                        if (langToConvertTo == "dart"):
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")"
                        if (langToConvertTo == "ts"):
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")"
                        if (langToConvertTo == "groovy"):
                            itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")"
                    itemsOut = StrReplace(itemsOut, keyWordEscpaeChar, Chr(92))
                if (langToConvertTo == "py"):
                    var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in enumerate(items" + STR(AindexcharLength) + ", start=" + AHKlikeLoopsIndexedAt + "):"
                if (langToConvertTo == "js"):
                    var1out = itemsOut + "\n" + "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "cpp"):
                    var1out = itemsOut + "\n" + "for (size_t " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".size() + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "go"):
                    var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " := range(items" + STR(AindexcharLength) + ")"
                if (langToConvertTo == "lua"):
                    var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in ipairs(items" + STR(AindexcharLength) + ") do"
                if (langToConvertTo == "cs"):
                    var1out = itemsOut + "\n" + "foreach (var " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + ")"
                if (langToConvertTo == "java"):
                    var1out = itemsOut + "\n" + "for (" + keyWordALoopField + "" + STR(AindexcharLength) + " : items" + STR(AindexcharLength) + ")"
                if (langToConvertTo == "kt"):
                    var1out = itemsOut + "\n" + "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + ".withIndex())"
                if (langToConvertTo == "rb"):
                    var1out = itemsOut + "\n" + "items" + STR(AindexcharLength) + ".each_with_index do |" + keyWordALoopField + "" + STR(AindexcharLength) + " , " + keyWordAIndex + "" + STR(AindexcharLength) + "|"
                if (langToConvertTo == "nim"):
                    var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + " | " + keyWordAIndex + "" + STR(AindexcharLength) + " += 1:"
                if (langToConvertTo == "ahk"):
                    var1out = "Loop, Parse, " + line1 + " " + line2 + " " + line3
                if (langToConvertTo == "swift"):
                    var1out = itemsOut + "\n" + "for (index, " + keyWordALoopField + "" + STR(AindexcharLength) + ") in items" + STR(AindexcharLength) + ".enumerated()"
                if (langToConvertTo == "dart"):
                    var1out = itemsOut + "\n" + "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = 0; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "ts"):
                    var1out = itemsOut + "\n" + "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = 0; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)"
                if (langToConvertTo == "groovy"):
                    var1out = itemsOut + "\n" + "items" + STR(AindexcharLength) + ".eachWithIndex { " + keyWordALoopField + "" + STR(AindexcharLength) + " , " + keyWordAIndex + "" + STR(AindexcharLength) + " ->"
                nothing = ""
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing
                #
                #
                theFixTextLoopLP = ""
                if (langToConvertTo == "cpp"):
                    theFixTextLoopLP = "std::string " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];"
                if (langToConvertTo == "js"):
                    theFixTextLoopLP = "const " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];"
                if (langToConvertTo == "go"):
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " := items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]"
                if (langToConvertTo == "lua"):
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]"
                if (langToConvertTo == "cs"):
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]"
                if (langToConvertTo == "java"):
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]"
                if (langToConvertTo == "kt"):
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]"
                if (langToConvertTo == "rb"):
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]"
                if (langToConvertTo == "nim"):
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]"
                if (langToConvertTo == "ahk"):
                    theFixTextLoopLP = "\n"
                if (langToConvertTo == "swift"):
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]"
                if (langToConvertTo == "dart"):
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]"
                if (langToConvertTo == "ts"):
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]"
                if (langToConvertTo == "groovy"):
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]"
                htCodeAcurlyBraceAddSomeVrasFixLP = 1
                haveWeEverUsedAloop = 1
                if (langToConvertTo != "ahk" and langToConvertTo != langFileExtension_2):
                    htCodeLoopfixa += "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n"
                    htCodeLoopfixa1 = "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength)
                AindexcharLength = AindexcharLength + 1
                if (langToConvertTo == langFileExtension_2):
                    if (usePythonicColonSyntax_2 == "on"):
                        htCode += Trim(keyWordLoopParse_2) + " " + var1 + ":\n"
                    else:
                        htCode += Trim(keyWordLoopParse_2) + " " + var1 + Chr(10)
                else:
                    htCode += htCodeLoopfixa1 + Chr(10) + var1out + Chr(10)
            elif (SubStrLastChars(Trim(A_LoopField95), StrLen(keyWordInc)) == keyWordInc or SubStrLastChars(Trim(A_LoopField95), StrLen(keyWordInc + ";")) == keyWordInc + ";" and lineDone == 0):
                if (useSemicolon == "on"):
                    str1 = Trim(StringTrimRight(Trim(A_LoopField95), StrLen(keyWordInc + ";")))
                else:
                    str1 = Trim(StringTrimRight(Trim(A_LoopField95), StrLen(keyWordInc)))
                if (langToConvertTo == langFileExtension_2):
                    if (useSemicolon_2 == "on"):
                        htCode += str1 + keyWordInc_2 + ";" + Chr(10)
                    else:
                        htCode += str1 + keyWordInc_2 + Chr(10)
                if (langToConvertTo == "cpp"):
                    htCode += str1 + "++;" + Chr(10)
                if (langToConvertTo == "py"):
                    htCode += str1 + " += 1" + Chr(10)
                if (langToConvertTo == "js"):
                    htCode += str1 + "++;" + Chr(10)
                if (langToConvertTo == "go"):
                    htCode += str1 + "++;" + Chr(10)
                if (langToConvertTo == "lua"):
                    htCode += str1 + " = " + str1 + " + 1" + Chr(10)
                if (langToConvertTo == "cs"):
                    htCode += str1 + "++;" + Chr(10)
                if (langToConvertTo == "java"):
                    htCode += str1 + "++;" + Chr(10)
                if (langToConvertTo == "kt"):
                    htCode += str1 + "++;" + Chr(10)
                if (langToConvertTo == "rb"):
                    htCode += str1 + " += 1" + Chr(10)
                if (langToConvertTo == "nim"):
                    htCode += str1 + " += 1" + Chr(10)
                if (langToConvertTo == "ahk"):
                    htCode += str1 + "++" + Chr(10)
                if (langToConvertTo == "swift"):
                    htCode += str1 + "++;" + Chr(10)
                if (langToConvertTo == "dart"):
                    htCode += str1 + "++;" + Chr(10)
                if (langToConvertTo == "ts"):
                    htCode += str1 + "++;" + Chr(10)
                if (langToConvertTo == "groovy"):
                    htCode += str1 + "++;" + Chr(10)
            elif (SubStrLastChars(Trim(A_LoopField95), StrLen(keyWordDec)) == keyWordDec or SubStrLastChars(Trim(A_LoopField95), StrLen(keyWordDec + ";")) == keyWordDec + ";" and lineDone == 0):
                if (useSemicolon == "on"):
                    str1 = Trim(StringTrimRight(Trim(A_LoopField95), StrLen(keyWordDec + ";")))
                else:
                    str1 = Trim(StringTrimRight(Trim(A_LoopField95), StrLen(keyWordDec)))
                if (langToConvertTo == langFileExtension_2):
                    if (useSemicolon_2 == "on"):
                        htCode += str1 + keyWordDec_2 + ";" + Chr(10)
                    else:
                        htCode += str1 + keyWordDec_2 + Chr(10)
                if (langToConvertTo == "cpp"):
                    htCode += str1 + "--;" + Chr(10)
                if (langToConvertTo == "py"):
                    htCode += str1 + " -= 1" + Chr(10)
                if (langToConvertTo == "js"):
                    htCode += str1 + "--;" + Chr(10)
                if (langToConvertTo == "go"):
                    htCode += str1 + "--;" + Chr(10)
                if (langToConvertTo == "lua"):
                    htCode += str1 + " = " + str1 + " - 1\n"
                if (langToConvertTo == "cs"):
                    htCode += str1 + "--;" + Chr(10)
                if (langToConvertTo == "java"):
                    htCode += str1 + "--;" + Chr(10)
                if (langToConvertTo == "kt"):
                    htCode += str1 + "--;" + Chr(10)
                if (langToConvertTo == "rb"):
                    htCode += str1 + " -= 1" + Chr(10)
                if (langToConvertTo == "nim"):
                    htCode += str1 + " -= 1" + Chr(10)
                if (langToConvertTo == "ahk"):
                    htCode += str1 + "--" + Chr(10)
                if (langToConvertTo == "swift"):
                    htCode += str1 + "--;" + Chr(10)
                if (langToConvertTo == "dart"):
                    htCode += str1 + "--;" + Chr(10)
                if (langToConvertTo == "ts"):
                    htCode += str1 + "--;" + Chr(10)
                if (langToConvertTo == "groovy"):
                    htCode += str1 + "--;" + Chr(10)
            elif (SubStr(StrLower(Trim(A_LoopField95)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ") and langToConvertTo == langFileExtension_2):
                htCode += keyWordInclude_2 + " " + Trim(StringTrimLeft(Trim(A_LoopField95), StrLen(StrLower(keyWordInclude) + " "))) + "\n"
            elif (StrLower(A_LoopField95) == StrLower(keyWordGlobal) or StrLower(A_LoopField95) == StrLower(keyWordGlobal + ";")):
                if (langToConvertTo == "ahk"):
                    htCode += "global\n"
            elif (SubStr(StrLower(A_LoopField95), 1, StrLen(StrLower(keyWordAwait))) == StrLower(keyWordAwait)):
                str1 = StringTrimLeft(A_LoopField95, StrLen(keyWordAwait))
                #MsgBox, % A_LoopField95
                lineDone = 1
                fixExpertionLineFuncOnly = 1
                if (langToConvertTo == langFileExtension_2):
                    if (useSemicolon_2 == "on"):
                        str2 = expressionParserTranspiler(Trim(str1)) + ";"
                    else:
                        str2 = expressionParserTranspiler(Trim(str1))
                else:
                    if (langToConvertTo == "py" or langToConvertTo == "nim" or langToConvertTo == "ahk" or langToConvertTo == "go" or langToConvertTo == "lua" or langToConvertTo == "kt" or langToConvertTo == "rb" or langToConvertTo == "swift" or langToConvertTo == "groovy"):
                        if (SubStrLastChars(str1, 1) == ";"):
                            str1 = StringTrimRight(str1, 1)
                    str2 = expressionParserTranspiler(Trim(str1)) + ";"
                    if (langToConvertTo == "py" or langToConvertTo == "nim" or langToConvertTo == "ahk" or langToConvertTo == "go" or langToConvertTo == "lua" or langToConvertTo == "kt" or langToConvertTo == "rb" or langToConvertTo == "swift" or langToConvertTo == "groovy"):
                        if (SubStrLastChars(str2, 1) == ";"):
                            str2 = StringTrimRight(str2, 1)
                fixExpertionLineFuncOnly = 0
                if (langToConvertTo == "js" or langToConvertTo == "ts" or langToConvertTo == langFileExtension_2):
                    htCode += "await " + str2 + "\n"
                else:
                    htCode += str2 + "\n"
            elif (SubStr(StrLower(A_LoopField95), 1, StrLen(StrLower(keyWordGlobal))) == StrLower(keyWordGlobal)):
                str1 = StringTrimLeft(A_LoopField95, StrLen(keyWordGlobal))
                #MsgBox, % A_LoopField95
                str1 = StrReplace(str1, ";", "")
                lineDone = 1
                if (langToConvertTo == "py" or langToConvertTo == "ahk"):
                    str2 = "global " + str1
                else:
                    str2 = ""
                htCode += str2 + "\n"
            elif (A_LoopField95 == "sdghbuheaq8ehgfuowhPSAVBYOFXDSAWHPDIVHXDBOAUHIPXVBOAUHFXDPVOYaushdpzuoyvsdhpxuoazdsfpc"):
                lineDone = 1
                htCode += A_LoopField95 + Chr(10)
            elif (A_LoopField95 == "sdghbuheaq8ehgfuowhPSAVBYOFXDSAWHPDIVHXDBOAUHIPXVBOAUHFXDPVOYaushdpzuoyvsdhpxuoazdsfpc"):
                lineDone = 1
                htCode += A_LoopField95 + Chr(10)
            elif (A_LoopField95 == "sdghbuheaq8ehgfuowhPSAVBYOFXDSAWHPDIVHXDBOAUHIPXVBOAUHFXDPVOYaushdpzuoyvsdhpxuoazdsfpc"):
                lineDone = 1
                htCode += A_LoopField95 + Chr(10)
            elif (SubStr(StrLower(A_LoopField95), 1, StrLen(keyWordFunc)) == keyWordFunc or SubStr(StrLower(A_LoopField95), 1, StrLen(keyWordAsync + keyWordFunc)) == keyWordAsync + keyWordFunc and lineDone == 0):
                lineDone = 1
                if (SubStr(StrLower(A_LoopField95), 1, StrLen(keyWordAsync + keyWordFunc)) == keyWordAsync + keyWordFunc):
                    # is async
                    int1 = 1
                    str1 = Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordAsync + keyWordFunc)))
                else:
                    # is async
                    int1 = 0
                    str1 = Trim(StringTrimLeft(A_LoopField95, StrLen(keyWordFunc)))
                if (usePrefixTypeForTypeDefinition == "on"):
                    str2 = Trim(StrSplit(str1, "(", 1))
                    # func body
                    str1 = Trim(StringTrimLeft(str1, StrLen(str2)))
                    str1 = StringTrimRight(str1, 1)
                    # type of the func
                    str3 = Trim(StringTrimRight(str2, StrLen(StrSplit(str2, " ", countChars(str2, " ") + 1))))
                    # name of func
                    str2 = Trim(StrSplit(str2, " ", countChars(str2, " ") + 1))
                if (usePostfixTypeForTypeDefinition == "on"):
                    # name of func
                    str2 = Trim(StrSplit(str1, "(", 1))
                    # func body
                    str1 = Trim(StringTrimLeft(str1, StrLen(str2)))
                    # type of the func
                    str3 = Trim(StrSplit(str1, ")", countChars(str1, ")") + 1))
                    str3 = StringTrimLeft(str3, 1)
                    str1 = Trim(StringTrimRight(str1, StrLen(str3) + 2))
                str1 = StringTrimLeft(str1, 1)
                str3 = Trim(str3)
                if (Trim(str1) == ""):
                    if (langToConvertTo == langFileExtension_2):
                        if (int1 == 1):
                            if (usePrefixTypeForTypeDefinition_2 == "on"):
                                htCode += keyWordAsync + keyWordFunc + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10)
                            else:
                                htCode += keyWordAsync + keyWordFunc + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10)
                        else:
                            if (usePrefixTypeForTypeDefinition_2 == "on"):
                                htCode += keyWordFunc + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10)
                            else:
                                htCode += keyWordFunc + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10)
                    if (langToConvertTo == "cpp"):
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10)
                    if (langToConvertTo == "py"):
                        htCode += "def " + str2 + "():" + Chr(10)
                    if (langToConvertTo == "js"):
                        if (int1 == 1):
                            htCode += "async function " + str2 + "()" + Chr(10)
                        else:
                            htCode += "function " + str2 + "()" + Chr(10)
                    # Go
                    if (langToConvertTo == "go"):
                        if (str3 == keyWordVoid):
                            htCode += "func " + str2 + "()" + Chr(10)
                        else:
                            htCode += "func " + str2 + "() " + getFuncTypeConvert(str3) + Chr(10)
                    if (langToConvertTo == "lua"):
                        htCode += "function " + str2 + "()" + Chr(10)
                    if (langToConvertTo == "cs"):
                        htCode += "static " + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10)
                    if (langToConvertTo == "java"):
                        htCode += "public static " + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10)
                    if (langToConvertTo == "kt"):
                        if (str3 == keyWordVoid):
                            htCode += "fun " + str2 + "()" + Chr(10)
                        else:
                            htCode += "fun " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10)
                    if (langToConvertTo == "rb"):
                        htCode += "def " + str2 + "()" + Chr(10)
                    if (langToConvertTo == "nim"):
                        if (str3 == keyWordVoid):
                            htCode += "proc " + str2 + "() =" + Chr(10)
                        else:
                            htCode += "proc " + str2 + "(): " + getFuncTypeConvert(str3) + " =" + Chr(10)
                    if (langToConvertTo == "ahk"):
                        htCode += str2 + "()" + Chr(10)
                    if (langToConvertTo == "swift"):
                        if (str3 == keyWordVoid):
                            htCode += "func " + str2 + "()" + Chr(10)
                        else:
                            htCode += "func " + str2 + "() -> " + getFuncTypeConvert(str3) + Chr(10)
                    if (langToConvertTo == "dart"):
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10)
                    if (langToConvertTo == "ts"):
                        htCode += "function " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10)
                    if (langToConvertTo == "groovy"):
                        htCode += "def " + str2 + "()" + Chr(10)
                else:
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
                    items96 = LoopParseFunc(str1, ",")
                    for A_Index96 , A_LoopField96 in enumerate(items96, start=0):
                        print("|" + Trim(A_LoopField96) + "|")
                        if (InStr(Trim(A_LoopField96), " ")):
                            # there is space aka there is a type
                            if (InStr(A_LoopField96, " " + Trim(keyWordAssign) + " ") == False):
                                if (usePrefixTypeForTypeDefinition == "on"):
                                    # normal
                                    str6 = Trim(A_LoopField96)
                                    str7 = getTheLastWord(str6)
                                    str8 = getFuncTypeConvert(Trim(StringTrimRight(str6, StrLen(Trim(str7)) + 1)))
                                    # str5 .= str8 . " " . str7 . Chr(10)
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    # save to str5
                                    # str8 = the type
                                    # str7 = variable name
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                else:
                                    # not normal
                                    str6 = Trim(A_LoopField96)
                                    str7 = Trim(StrSplit(str6, ":", 2))
                                    str8 = getFuncTypeConvert(Trim(StrSplit(str6, ":", 1)))
                                    # str5 .= str7 . " :" . str8 . Chr(10)
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    # save to str5
                                    # str8 = the type
                                    # str7 = variable name
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                            else:
                                # optanal param
                                if (InStr(Trim(StrSplit(Trim(A_LoopField96), " " + Trim(keyWordAssign) + " ", 1)), " ")):
                                    # there is a type
                                    if (usePrefixTypeForTypeDefinition == "on"):
                                        # normal
                                        str6 = Trim(StrSplit(Trim(A_LoopField96), " " + Trim(keyWordAssign) + " ", 1))
                                        str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField96), " " + Trim(keyWordAssign) + " ", 2))))
                                        str7 = getTheLastWord(str6)
                                        str8 = getFuncTypeConvert(Trim(StringTrimRight(str6, StrLen(Trim(str7)) + 1)))
                                        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        #;;;;;;;;;;;;;;;; optanal param ;;;;;;;;;;;;;;;;;
                                        # save to str10
                                        # str8 = the type
                                        # str7 = variable name
                                        # str9 = after the keyWordAssign
                                        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        # str10
                                        # skipLeftCuleyForFuncPLS := 1
                                    else:
                                        # not normal
                                        str6 = Trim(StrSplit(Trim(A_LoopField96), " " + Trim(keyWordAssign) + " ", 1))
                                        str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField96), " " + Trim(keyWordAssign) + " ", 2))))
                                        str7 = Trim(StrSplit(str6, ":", 2))
                                        str8 = getFuncTypeConvert(Trim(StrSplit(str6, ":", 1)))
                                        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        #;;;;;;;;;;;;;;;; optanal param ;;;;;;;;;;;;;;;;;
                                        # save to str10
                                        # str8 = the type
                                        # str7 = variable name
                                        # str9 = after the keyWordAssign
                                        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        # str10
                                        # skipLeftCuleyForFuncPLS := 1
                                else:
                                    # there is no type
                                    str8 = Trim(StrSplit(Trim(A_LoopField96), " " + Trim(keyWordAssign) + " ", 1))
                                    str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField96), " " + Trim(keyWordAssign) + " ", 2))))
                                    # str10
                                    # skipLeftCuleyForFuncPLS := 1
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    #;;;;;;;;;;;;;;;; optanal param ;;;;;;;;;;;;;;;;;
                                    # save to str10
                                    # str8 = variable name
                                    # str9 = after the keyWordAssign
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                        else:
                            str5 += Trim(A_LoopField96) + Chr(10)
                    str5 = StringTrimRight(str5, 1)
            elif ((SubStr(Trim(A_LoopField95), -2) == ");" or SubStr(Trim(A_LoopField95), -1) == ")") and !(InStr(A_LoopField95, "int main(int argc, char* argv[])")) and !(InStr(A_LoopField95, "async function main()")) and lineDone == 0):
                lineDone = 1
                str1 = Trim(A_LoopField95)
                fixExpertionLineFuncOnly = 1
                if (langToConvertTo == langFileExtension_2):
                    if (useSemicolon_2 == "on"):
                        str2 = expressionParserTranspiler(Trim(str1)) + ";"
                    else:
                        str2 = expressionParserTranspiler(Trim(str1))
                else:
                    if (langToConvertTo == "py" or langToConvertTo == "nim" or langToConvertTo == "ahk" or langToConvertTo == "go" or langToConvertTo == "lua" or langToConvertTo == "kt" or langToConvertTo == "rb" or langToConvertTo == "swift" or langToConvertTo == "groovy"):
                        if (SubStrLastChars(str1, 1) == ";"):
                            str1 = StringTrimRight(str1, 1)
                    str2 = expressionParserTranspiler(Trim(str1)) + ";"
                    if (langToConvertTo == "py" or langToConvertTo == "nim" or langToConvertTo == "ahk" or langToConvertTo == "go" or langToConvertTo == "lua" or langToConvertTo == "kt" or langToConvertTo == "rb" or langToConvertTo == "swift" or langToConvertTo == "groovy"):
                        if (SubStrLastChars(str2, 1) == ";"):
                            str2 = StringTrimRight(str2, 1)
                fixExpertionLineFuncOnly = 0
                htCode += str2 + "\n"
            elif (KeyWordsCommands(A_LoopField95, "check", commands, langToConvertTo) == "true" and lineDone == 0):
                lineDone = 1
                if (langToConvertTo == langFileExtension_2):
                    htCode += A_LoopField95 + "\n"
                else:
                    out_KeyWordsCommands = KeyWordsCommands(A_LoopField95, "transpile", commands, langToConvertTo)
                    htCode += out_KeyWordsCommands + "\n"
            else:
                #print("else else else " . A_LoopField95)
                # this is THE else
                if (lineDone != 1):
                    if (skipLeftCuleyForFuncPLS != 1):
                        if (SubStr(Trim(StrLower(A_LoopField95)), 1, 1) == Chr(125)):
                            htCode += Chr(125) + "\n"
                        else:
                            if (htCodeAcurlyBraceAddSomeVrasFixLP == 1 and SubStr(Trim(StrLower(A_LoopField95)), 1, 1) == Chr(123)):
                                htCodeAcurlyBraceAddSomeVrasFixLP = 0
                                htCode += A_LoopField95 + "\n" + theFixTextLoopLP + "\n"
                            else:
                                if (htCodeAcurlyBraceAddSomeVrasFixNL == 1 and SubStr(Trim(StrLower(A_LoopField95)), 1, 1) == Chr(123)):
                                    htCodeAcurlyBraceAddSomeVrasFixNL = 0
                                    htCode += A_LoopField95 + "\n" + theFixTextLoopNL + "\n"
                                else:
                                    htCode += A_LoopField95 + "\n"
                    else:
                        skipLeftCuleyForFuncPLS = 0
        htCode = StringTrimRight(htCode, 1)
        #s
        #s
        #s
        if (langToConvertTo != "ahk" and langToConvertTo != langFileExtension_2):
            #s
            if (haveWeEverUsedAloop == 1):
                htCodeLoopfixa = StringTrimRight(htCodeLoopfixa, 1)
                #OutputDebug, |%htCodeLoopfixa%|
                AIndexLoopCurlyFix = 1
                items97 = LoopParseFunc(htCodeLoopfixa, "\n", "\r")
                for A_Index97 , A_LoopField97 in enumerate(items97, start=0):
                    sstr123 = A_LoopField97
                    fixLoopLokingFor = A_LoopField97
                    fixLoopLokingForfound = 1
                    out1 = StrSplit(sstr123 ,"|" , 1)
                    out2 = StrSplit(sstr123 ,"|" , 3)
                    #OutputDebug, |%out1%|
                    #OutputDebug, |%out2%|
                    wasAtanyIfsElseAddAIndexLoopCurlyFix = 0
                    if (out1 == "nl"):
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
                        out4758686d86d86d86578991a = ""
                        items98 = LoopParseFunc(htCode, "\n", "\r")
                        for A_Index98 , A_LoopField98 in enumerate(items98, start=0):
                            #MsgBox, dsfgsdefgesrdg1
                            #MsgBox, |%A_LoopField98%|`n|%fixLoopLokingFor%|
                            if (InStr(A_LoopField98, fixLoopLokingFor) and insdeAnestedLoopBAD != 1):
                                fixLoopLokingForNum = 1
                                #MsgBox, do we came here 1
                            if (SubStr(Trim(A_LoopField98), 1, 4) == "for " and weAreDoneHereCurly != 1 and insdeAnestedLoopBAD != 1 and fixLoopLokingForNum == 1):
                                s = StrSplit(A_LoopField98 ,"" + keyWordAIndex + "", 2)
                                out1z = s
                                s = StrSplit(out1z, " ", 1)
                                out1z = Trim(s)
                                #MsgBox, % out1z
                                #MsgBox, do we came here 2
                                fixLoopLokingForNum = 0
                                foundTheTopLoop = foundTheTopLoop + 1
                                inTarget = 1
                                #MsgBox, % A_LoopField98
                                dontSaveStr = 1
                                ALoopField = A_LoopField98
                                DeleayOneCuzOfLoopParse = 1
                                out4758686d86d86d86578991a += ALoopField + "\n"
                            if (inTarget == 1 and InStr(A_LoopField98, Chr(123)) and insdeAnestedLoopBAD != 1):
                                insideBracket = 1
                            if (insideBracket == 1 and InStr(A_LoopField98, Chr(123)) and insdeAnestedLoopBAD != 1):
                                netsedCurly = netsedCurly + 1
                            if (insideBracket == 1 and InStr(A_LoopField98, Chr(125)) and insdeAnestedLoopBAD != 1):
                                netsedCurly = netsedCurly - 1
                                readyToEnd = 1
                            if (SubStr(Trim(A_LoopField98), 1, 4) == "for " and insdeAnestedLoopBAD != 1 and foundTheTopLoop >= 2):
                                insdeAnestedLoopBAD = 1
                                insideBracket1 = 0
                                netsedCurly1 = 0
                            if (inTarget == 1):
                                foundTheTopLoop = foundTheTopLoop + 1
                            if (insdeAnestedLoopBAD == 1):
                                if (InStr(A_LoopField98, Chr(123))):
                                    insideBracket1 = 1
                                if (insideBracket1 == 1 and InStr(A_LoopField98, Chr(123))):
                                    netsedCurly1 = netsedCurly1 + 1
                                if (insideBracket1 == 1 and InStr(A_LoopField98, Chr(125))):
                                    netsedCurly1 = netsedCurly1 - 1
                                    readyToEnd1 = 1
                                if (InStr(A_LoopField98, Chr(125)) and readyToEnd1 == 1 and netsedCurly1 == 0 and insideBracket == 1):
                                    #MsgBox, % A_LoopField98
                                    eldLoopNestedBADlol = 1
                                out4758686d86d86d86578991a += A_LoopField98 + "\n"
                            if (inTarget == 1 and dontSaveStr != 1 and fixLoopLokingForNum != 1 and insdeAnestedLoopBAD != 1):
                                ALoopField = A_LoopField98
                                # Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z)
                                out4758686d86d86d86578991a += ALoopField + "\n"
                            if (inTarget == 1 and InStr(A_LoopField98, Chr(125)) and readyToEnd == 1 and netsedCurly == 0 and weAreDoneHereCurly == 0 and dontSaveStr != 1 and insdeAnestedLoopBAD != 1):
                                #MsgBox, % A_LoopField98
                                weAreDoneHereCurly = 1
                                inTarget = 0
                                endBracketDOntPutThere = 1
                            dontSaveStr = 0
                            if (inTarget != 1 and endBracketDOntPutThere != 1 and insdeAnestedLoopBAD != 1):
                                out4758686d86d86d86578991a += A_LoopField98 + "\n"
                            endBracketDOntPutThere = 0
                            if (eldLoopNestedBADlol == 1):
                                insdeAnestedLoopBAD = 0
                        strstysrstsytTRIMHELP = out4758686d86d86d86578991a
                        strstysrstsytTRIMHELP = StringTrimRight(strstysrstsytTRIMHELP, 1)
                        htCode = strstysrstsytTRIMHELP
                        #MsgBox, % htCode
                        wasAtanyIfsElseAddAIndexLoopCurlyFix = 1
                    else:
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
                        out4758686d86d86d86578991a = ""
                        items99 = LoopParseFunc(htCode, "\n", "\r")
                        for A_Index99 , A_LoopField99 in enumerate(items99, start=0):
                            if (InStr(A_LoopField99 , fixLoopLokingFor) and insdeAnestedLoopBAD != 1):
                                fixLoopLokingForNum = 1
                                #MsgBox, do we came here 3
                            if (SubStr(Trim(A_LoopField99), 1, 4) == "for " and weAreDoneHereCurly != 1 and insdeAnestedLoopBAD != 1 and fixLoopLokingForNum == 1):
                                s = StrSplit(A_LoopField99 ,"" + keyWordAIndex + "", 2)
                                out1z = s
                                s = StrSplit(out1z, " ", 1)
                                out1z = Trim(s)
                                #MsgBox, % out1z
                                fixLoopLokingForNum = 0
                                #MsgBox, do we came here 4
                                foundTheTopLoop = foundTheTopLoop + 1
                                inTarget = 1
                                #MsgBox, % A_LoopField99
                                dontSaveStr = 1
                                ALoopField = A_LoopField99
                                DeleayOneCuzOfLoopParse = 1
                                out4758686d86d86d86578991a += ALoopField + "\n"
                            if (inTarget == 1 and InStr(A_LoopField99, Chr(123)) and insdeAnestedLoopBAD != 1):
                                insideBracket = 1
                            if (insideBracket == 1 and InStr(A_LoopField99, Chr(123)) and insdeAnestedLoopBAD != 1):
                                netsedCurly = netsedCurly + 1
                            if (insideBracket == 1 and InStr(A_LoopField99, Chr(125)) and insdeAnestedLoopBAD != 1):
                                netsedCurly = netsedCurly - 1
                                readyToEnd = 1
                            if (SubStr(Trim(A_LoopField99), 1, 4) == "for " and insdeAnestedLoopBAD != 1 and foundTheTopLoop >= 2):
                                insdeAnestedLoopBAD = 1
                                insideBracket1 = 0
                                netsedCurly1 = 0
                            if (inTarget == 1):
                                foundTheTopLoop = foundTheTopLoop + 1
                            if (insdeAnestedLoopBAD == 1):
                                if (InStr(A_LoopField99, Chr(123))):
                                    insideBracket1 = 1
                                if (insideBracket1 == 1 and InStr(A_LoopField99, Chr(123))):
                                    netsedCurly1 = netsedCurly1 + 1
                                if (insideBracket1 == 1 and InStr(A_LoopField99, Chr(125))):
                                    netsedCurly1 = netsedCurly1 - 1
                                    readyToEnd1 = 1
                                if (InStr(A_LoopField99, Chr(125)) and readyToEnd1 == 1 and netsedCurly1 == 0 and insideBracket == 1):
                                    #MsgBox, % A_LoopField99
                                    eldLoopNestedBADlol = 1
                                out4758686d86d86d86578991a += A_LoopField99 + "\n"
                            if (inTarget == 1 and dontSaveStr != 1 and fixLoopLokingForNum != 1 and insdeAnestedLoopBAD != 1):
                                ALoopField = A_LoopField99
                                # Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z)
                                # Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordALoopField + "\\d*", "" + keyWordALoopField + "" + out1z)
                                out4758686d86d86d86578991a += ALoopField + "\n"
                            if ((inTarget == 1 and InStr(A_LoopField99, Chr(125)) and readyToEnd == 1 and netsedCurly == 0 and weAreDoneHereCurly == 0 and dontSaveStr != 1 and insdeAnestedLoopBAD != 1)):
                                #MsgBox, % A_LoopField99
                                weAreDoneHereCurly = 1
                                inTarget = 0
                                endBracketDOntPutThere = 1
                            dontSaveStr = 0
                            if (inTarget != 1 and endBracketDOntPutThere != 1 and insdeAnestedLoopBAD != 1):
                                out4758686d86d86d86578991a += A_LoopField99 + "\n"
                            endBracketDOntPutThere = 0
                            if (eldLoopNestedBADlol == 1):
                                insdeAnestedLoopBAD = 0
                        strstysrstsytTRIMHELP = out4758686d86d86d86578991a
                        strstysrstsytTRIMHELP = StringTrimRight(strstysrstsytTRIMHELP, 1)
                        htCode = strstysrstsytTRIMHELP
                        #MsgBox, % htCode
                        wasAtanyIfsElseAddAIndexLoopCurlyFix = 1
                    if (wasAtanyIfsElseAddAIndexLoopCurlyFix == 1):
                        AIndexLoopCurlyFix = AIndexLoopCurlyFix + 1
                        wasAtanyIfsElseAddAIndexLoopCurlyFix = 0
                out4758686d86dgt8r754444444 = ""
                hold = 0
                items100 = LoopParseFunc(htCode, "\n", "\r")
                for A_Index100 , A_LoopField100 in enumerate(items100, start=0):
                    ignore = 0
                    if (SubStr(Trim(A_LoopField100), 1, 4) == "for "):
                        if (hold == 1 and holdText == A_LoopField100):
                            ignore = 1
                        else:
                            holdText = A_LoopField100
                            hold = 1
                    if (not ignore):
                        out4758686d86dgt8r754444444 += A_LoopField100 + "\n"
                out4758686d86dgt8r754444444 = StringTrimRight(out4758686d86dgt8r754444444, 1)
                htCode = out4758686d86dgt8r754444444
            htCodeOut1234565432 = ""
            items101 = LoopParseFunc(htCode, "\n", "\r")
            for A_Index101 , A_LoopField101 in enumerate(items101, start=0):
                out = A_LoopField101
                if (not InStr(out, "|itsaersdtgtgfergsdgfsegdfsedAA|")):
                    htCodeOut1234565432 += out + "\n"
            htCode = StringTrimRight(htCodeOut1234565432, 1)
    else:
        htCode = code
    if (COUNT_programmingBlock_InTheTranspiledLang != 0):
        for A_Index102 in range(0, COUNT_programmingBlock_InTheTranspiledLang + 0):
            htCode = StrReplace(htCode, "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(A_Index102 + 1) + "AA", programmingBlock_InTheTranspiledLang[A_Index102])
    if (langToConvertTo == "cpp"):
        if (COUNT_programmingBlock_CPP != 0):
            for A_Index103 in range(0, COUNT_programmingBlock_CPP + 0):
                htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index103 + 1) + "AA", programmingBlock_CPP[A_Index103])
    else:
        if (COUNT_programmingBlock_CPP != 0):
            for A_Index104 in range(0, COUNT_programmingBlock_CPP + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index104 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCPP + "\n" + programmingBlock_CPP[A_Index104] + "\n" + keyWordCodeInTheTranspiledLangEndCPP)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index104 + 1) + "AA", "\n")
    if (langToConvertTo == "py"):
        if (COUNT_programmingBlock_PY != 0):
            for A_Index105 in range(0, COUNT_programmingBlock_PY + 0):
                htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index105 + 1) + "AA", programmingBlock_PY[A_Index105])
    else:
        if (COUNT_programmingBlock_PY != 0):
            for A_Index106 in range(0, COUNT_programmingBlock_PY + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index106 + 1) + "AA", keyWordCodeInTheTranspiledLangStartPY + "\n" + programmingBlock_PY[A_Index106] + "\n" + keyWordCodeInTheTranspiledLangEndPY)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index106 + 1) + "AA", "\n")
    if (langToConvertTo == "js"):
        if (COUNT_programmingBlock_JS != 0):
            for A_Index107 in range(0, COUNT_programmingBlock_JS + 0):
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index107 + 1) + "AA", programmingBlock_JS[A_Index107])
    else:
        if (COUNT_programmingBlock_JS != 0):
            for A_Index108 in range(0, COUNT_programmingBlock_JS + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index108 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJS + "\n" + programmingBlock_JS[A_Index108] + "\n" + keyWordCodeInTheTranspiledLangEndJS)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index108 + 1) + "AA", "\n")
    if (langToConvertTo == "go"):
        if (COUNT_programmingBlock_GO != 0):
            for A_Index109 in range(0, COUNT_programmingBlock_GO + 0):
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index109 + 1) + "AA", programmingBlock_GO[A_Index109])
    else:
        if (COUNT_programmingBlock_GO != 0):
            for A_Index110 in range(0, COUNT_programmingBlock_GO + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index110 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGO + "\n" + programmingBlock_GO[A_Index110] + "\n" + keyWordCodeInTheTranspiledLangEndGO)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index110 + 1) + "AA", "\n")
    if (langToConvertTo == "lua"):
        if (COUNT_programmingBlock_LUA != 0):
            for A_Index111 in range(0, COUNT_programmingBlock_LUA + 0):
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index111 + 1) + "AA", programmingBlock_LUA[A_Index111])
    else:
        if (COUNT_programmingBlock_LUA != 0):
            for A_Index112 in range(0, COUNT_programmingBlock_LUA + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index112 + 1) + "AA", keyWordCodeInTheTranspiledLangStartLUA + "\n" + programmingBlock_LUA[A_Index112] + "\n" + keyWordCodeInTheTranspiledLangEndLUA)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index112 + 1) + "AA", "\n")
    if (langToConvertTo == "cs"):
        if (COUNT_programmingBlock_CS != 0):
            for A_Index113 in range(0, COUNT_programmingBlock_CS + 0):
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index113 + 1) + "AA", programmingBlock_CS[A_Index113])
    else:
        if (COUNT_programmingBlock_CS != 0):
            for A_Index114 in range(0, COUNT_programmingBlock_CS + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index114 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCS + "\n" + programmingBlock_CS[A_Index114] + "\n" + keyWordCodeInTheTranspiledLangEndCS)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index114 + 1) + "AA", "\n")
    if (langToConvertTo == "java"):
        if (COUNT_programmingBlock_JAVA != 0):
            for A_Index115 in range(0, COUNT_programmingBlock_JAVA + 0):
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index115 + 1) + "AA", programmingBlock_JAVA[A_Index115])
    else:
        if (COUNT_programmingBlock_JAVA != 0):
            for A_Index116 in range(0, COUNT_programmingBlock_JAVA + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index116 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJAVA + "\n" + programmingBlock_JAVA[A_Index116] + "\n" + keyWordCodeInTheTranspiledLangEndJAVA)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index116 + 1) + "AA", "\n")
    if (langToConvertTo == "kt"):
        if (COUNT_programmingBlock_KT != 0):
            for A_Index117 in range(0, COUNT_programmingBlock_KT + 0):
                htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index117 + 1) + "AA", programmingBlock_KT[A_Index117])
    else:
        if (COUNT_programmingBlock_KT != 0):
            for A_Index118 in range(0, COUNT_programmingBlock_KT + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index118 + 1) + "AA", keyWordCodeInTheTranspiledLangStartKT + "\n" + programmingBlock_KT[A_Index118] + "\n" + keyWordCodeInTheTranspiledLangEndKT)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index118 + 1) + "AA", "\n")
    if (langToConvertTo == "rb"):
        if (COUNT_programmingBlock_RB != 0):
            for A_Index119 in range(0, COUNT_programmingBlock_RB + 0):
                htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index119 + 1) + "AA", programmingBlock_RB[A_Index119])
    else:
        if (COUNT_programmingBlock_RB != 0):
            for A_Index120 in range(0, COUNT_programmingBlock_RB + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index120 + 1) + "AA", keyWordCodeInTheTranspiledLangStartRB + "\n" + programmingBlock_RB[A_Index120] + "\n" + keyWordCodeInTheTranspiledLangEndRB)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index120 + 1) + "AA", "\n")
    if (langToConvertTo == "nim"):
        if (COUNT_programmingBlock_NIM != 0):
            for A_Index121 in range(0, COUNT_programmingBlock_NIM + 0):
                htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index121 + 1) + "AA", programmingBlock_NIM[A_Index121])
    else:
        if (COUNT_programmingBlock_NIM != 0):
            for A_Index122 in range(0, COUNT_programmingBlock_NIM + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index122 + 1) + "AA", keyWordCodeInTheTranspiledLangStartNIM + "\n" + programmingBlock_NIM[A_Index122] + "\n" + keyWordCodeInTheTranspiledLangEndNIM)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index122 + 1) + "AA", "\n")
    if (langToConvertTo == "ahk"):
        if (COUNT_programmingBlock_AHK != 0):
            for A_Index123 in range(0, COUNT_programmingBlock_AHK + 0):
                htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index123 + 1) + "AA", programmingBlock_AHK[A_Index123])
    else:
        if (COUNT_programmingBlock_AHK != 0):
            for A_Index124 in range(0, COUNT_programmingBlock_AHK + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index124 + 1) + "AA", keyWordCodeInTheTranspiledLangStartAHK + "\n" + programmingBlock_AHK[A_Index124] + "\n" + keyWordCodeInTheTranspiledLangEndAHK)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index124 + 1) + "AA", "\n")
    if (langToConvertTo == "swift"):
        if (COUNT_programmingBlock_SWIFT != 0):
            for A_Index125 in range(0, COUNT_programmingBlock_SWIFT + 0):
                htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index125 + 1) + "AA", programmingBlock_SWIFT[A_Index125])
    else:
        if (COUNT_programmingBlock_SWIFT != 0):
            for A_Index126 in range(0, COUNT_programmingBlock_SWIFT + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index126 + 1) + "AA", keyWordCodeInTheTranspiledLangStartSWIFT + "\n" + programmingBlock_SWIFT[A_Index126] + "\n" + keyWordCodeInTheTranspiledLangEndSWIFT)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index126 + 1) + "AA", "\n")
    if (langToConvertTo == "dart"):
        if (COUNT_programmingBlock_DART != 0):
            for A_Index127 in range(0, COUNT_programmingBlock_DART + 0):
                htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index127 + 1) + "AA", programmingBlock_DART[A_Index127])
    else:
        if (COUNT_programmingBlock_DART != 0):
            for A_Index128 in range(0, COUNT_programmingBlock_DART + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index128 + 1) + "AA", keyWordCodeInTheTranspiledLangStartDART + "\n" + programmingBlock_DART[A_Index128] + "\n" + keyWordCodeInTheTranspiledLangEndDART)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index128 + 1) + "AA", "\n")
    if (langToConvertTo == "ts"):
        if (COUNT_programmingBlock_TS != 0):
            for A_Index129 in range(0, COUNT_programmingBlock_TS + 0):
                htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index129 + 1) + "AA", programmingBlock_TS[A_Index129])
    else:
        if (COUNT_programmingBlock_TS != 0):
            for A_Index130 in range(0, COUNT_programmingBlock_TS + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index130 + 1) + "AA", keyWordCodeInTheTranspiledLangStartTS + "\n" + programmingBlock_TS[A_Index130] + "\n" + keyWordCodeInTheTranspiledLangEndTS)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index130 + 1) + "AA", "\n")
    if (langToConvertTo == "groovy"):
        if (COUNT_programmingBlock_GROOVY != 0):
            for A_Index131 in range(0, COUNT_programmingBlock_GROOVY + 0):
                htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index131 + 1) + "AA", programmingBlock_GROOVY[A_Index131])
    else:
        if (COUNT_programmingBlock_GROOVY != 0):
            for A_Index132 in range(0, COUNT_programmingBlock_GROOVY + 0):
                if (langToConvertTo == langFileExtension_2):
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index132 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGROOVY + "\n" + programmingBlock_GROOVY[A_Index132] + "\n" + keyWordCodeInTheTranspiledLangEndGROOVY)
                else:
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index132 + 1) + "AA", "\n")
    #;;;;;;;;;;
    if (langToConvertTo == langFileExtension_2):
        if (COUNT_programmingBlock_HTVM != 0):
            for A_Index133 in range(0, COUNT_programmingBlock_HTVM + 0):
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index133 + 1) + "AA", programmingBlock_HTVM[A_Index133])
    else:
        if (COUNT_programmingBlock_HTVM != 0):
            for A_Index134 in range(0, COUNT_programmingBlock_HTVM + 0):
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index134 + 1) + "AA", "\n")
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ADD_ALL_programmingBlock_HTVMsyntax = ""
    if (COUNT_programmingBlock_HTVMsyntax != 0):
        isNotHTVMfileEXTRA_INT = 1
        for A_Index135 in range(0, COUNT_programmingBlock_HTVMsyntax + 0):
            ADD_ALL_programmingBlock_HTVMsyntax += programmingBlock_HTVMsyntax[A_Index135] + "\n"
        ADD_ALL_programmingBlock_HTVMsyntax = StringTrimRight(ADD_ALL_programmingBlock_HTVMsyntax, 1)
        ADD_ALL_programmingBlock_HTVMsyntax = compiler(ADD_ALL_programmingBlock_HTVMsyntax, allInstructionFile, "full", langToConvertToParam)
        isNotHTVMfileEXTRA_INT = 0
        isNotHTVMfile2 = 1
        for A_Index136 in range(0, COUNT_programmingBlock_HTVMsyntax + 0):
            htCode = StrReplace(htCode, "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(A_Index136 + 1) + "AA", compiler(programmingBlock_HTVMsyntax[A_Index136], allInstructionFile, "full", langToConvertToParam))
        isNotHTVMfile2 = 0
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;
    #;;;;;;;;;;;;;;;;;;;;;;;;;;;
    if (isNotHTVMfile == 1):
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS")
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS")
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS")
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS")
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS")
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS")
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS")
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS")
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS")
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS")
        print("\n" + isNotHTVMfileEXTRA_LIB_INFO + "\n")
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed")
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed")
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed")
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed")
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed")
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed")
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed")
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed")
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed")
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed")
        print("\n" + isNotHTVMfileEXTRA_FUNCS_INFO + "\n")
        print("\n")
        print("\nYou must include all the libs from under the section and MAKE SURE your code doesn't already use them!!!")
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS")
        print("\nYou must copy-paste all the funcs from under the section and MAKE SURE your code doesn't already use them!!!")
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed\n")
        print("SCROLL UP!!!!!")
        print("SCROLL UP!!!!!")
        print("SCROLL UP!!!!!")
        print("Note: If you dont see any libs or built-in functions that you need to add, then that means you dont have to!")
        return htCode
    fixLuaAndRuby = ""
    if (langToConvertTo == langFileExtension_2):
        if (useCurlyBraces_2 == "off" and useEnd_2 == "off"):
            htCode = indent_nested_curly_braces(htCode, 0)
        else:
            htCode = indent_nested_curly_braces(htCode, 1)
        if (useEnd_2 == "on"):
            items137 = LoopParseFunc(htCode, "\n", "\r")
            for A_Index137 , A_LoopField137 in enumerate(items137, start=0):
                if (Trim(A_LoopField137) == keyWordCurlyBraceClose_2):
                    fixLuaAndRuby += StrReplace(A_LoopField137, keyWordCurlyBraceClose_2, Trim(keyWordEnd_2)) + "\n"
                elif (SubStrLastChars(A_LoopField137, 2) == " " + keyWordCurlyBraceOpen_2):
                    fixLuaAndRuby += StringTrimRight(A_LoopField137, 2) + "\n"
                else:
                    fixLuaAndRuby += A_LoopField137 + "\n"
            htCode = StringTrimRight(fixLuaAndRuby, 1)
        #;;;;;;;;;;
        #;;;;;;;;;;
    else:
        #;;;;;;;;;;
        #;;;;;;;;;;
        if (langToConvertTo == "py" or langToConvertTo == "nim"):
            htCode = indent_nested_curly_braces(htCode, 0)
        else:
            htCode = indent_nested_curly_braces(htCode, 1)
        if (langToConvertTo == "lua" or langToConvertTo == "rb"):
            items138 = LoopParseFunc(htCode, "\n", "\r")
            for A_Index138 , A_LoopField138 in enumerate(items138, start=0):
                if (Trim(A_LoopField138) == "}"):
                    fixLuaAndRuby += StrReplace(A_LoopField138, "}", "end") + "\n"
                elif (SubStrLastChars(A_LoopField138, 2) == " {"):
                    fixLuaAndRuby += StringTrimRight(A_LoopField138, 2) + "\n"
                else:
                    fixLuaAndRuby += A_LoopField138 + "\n"
            htCode = StringTrimRight(fixLuaAndRuby, 1)
    nextWordEndFix = []
    nextWordEndFixOut = ""
    if (langToConvertTo == "lua" or langToConvertTo == "rb"):
        items139 = LoopParseFunc(htCode, "\n", "\r")
        for A_Index139 , A_LoopField139 in enumerate(items139, start=0):
            nextWordEndFix.append(A_LoopField139)
        nextWordEndFix.append(" ")
        items140 = LoopParseFunc(htCode, "\n", "\r")
        for A_Index140 , A_LoopField140 in enumerate(items140, start=0):
            if (Trim(A_LoopField140) == "end" and SubStr(Trim(nextWordEndFix[A_Index140 + 1]), 1, StrLen("elseif ")) == "elseif " or Trim(A_LoopField140) == "end" and Trim(nextWordEndFix[A_Index140 + 1]) == "else"):
                nextWordEndFixOut += ""
            else:
                nextWordEndFixOut += A_LoopField140 + "\n"
        htCode = StringTrimRight(nextWordEndFixOut, 1)
    nextWordEndFixRB = []
    nextWordEndFixOut = ""
    if (langToConvertTo == "rb"):
        items141 = LoopParseFunc(htCode, "\n", "\r")
        for A_Index141 , A_LoopField141 in enumerate(items141, start=0):
            nextWordEndFixRB.append(A_LoopField141)
        nextWordEndFixRB.append(" ")
        items142 = LoopParseFunc(htCode, "\n", "\r")
        for A_Index142 , A_LoopField142 in enumerate(items142, start=0):
            if (Trim(A_LoopField142) == "end" and SubStr(Trim(nextWordEndFixRB[A_Index142 + 1]), 1, StrLen("rescue ")) == "rescue " or Trim(A_LoopField142) == "end" and Trim(nextWordEndFixRB[A_Index142 + 1]) == "ensure"):
                nextWordEndFixOut += ""
            else:
                nextWordEndFixOut += A_LoopField142 + "\n"
        htCode = StringTrimRight(nextWordEndFixOut, 1)
    if (langToConvertTo == "go"):
        fixGoManGoIsSoAnnoyingBroooFurure = []
        items143 = LoopParseFunc(htCode, "\n", "\r")
        for A_Index143 , A_LoopField143 in enumerate(items143, start=0):
            fixGoManGoIsSoAnnoyingBroooFurure.append(A_LoopField143)
        fixGoManGoIsSoAnnoyingBroooFurure.append(" ")
        fixGoManGoIsSoAnnoyingBroooSkip = 0
        fixGoManGoIsSoAnnoyingBroooCount = 0
        fixGoManGoIsSoAnnoyingBroooCountSpaceses = ""
        fixGoManGoIsSoAnnoyingBrooo = ""
        items144 = LoopParseFunc(htCode, "\n", "\r")
        for A_Index144 , A_LoopField144 in enumerate(items144, start=0):
            if (Trim(A_LoopField144) == "}" and SubStr(Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index144 + 1]), 1, StrLen("else if ")) == "else if "):
                fixGoManGoIsSoAnnoyingBroooSkip = 1
                fixGoManGoIsSoAnnoyingBroooCount = 0
                items145 = LoopParseFunc(fixGoManGoIsSoAnnoyingBroooFurure[A_Index144 + 1])
                for A_Index145 , A_LoopField145 in enumerate(items145, start=0):
                    if (A_LoopField145 == " "):
                        fixGoManGoIsSoAnnoyingBroooCount = fixGoManGoIsSoAnnoyingBroooCount + 1
                    else:
                        break
                fixGoManGoIsSoAnnoyingBroooCountSpaceses = ""
                for A_Index146 in range(0, fixGoManGoIsSoAnnoyingBroooCount + 0):
                    fixGoManGoIsSoAnnoyingBroooCountSpaceses += " "
                fixGoManGoIsSoAnnoyingBrooo += fixGoManGoIsSoAnnoyingBroooCountSpaceses + "} " + Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index144 + 1]) + "\n"
            else:
                if (fixGoManGoIsSoAnnoyingBroooSkip == 0):
                    fixGoManGoIsSoAnnoyingBrooo += A_LoopField144 + "\n"
                fixGoManGoIsSoAnnoyingBroooSkip = 0
        htCode = StringTrimRight(fixGoManGoIsSoAnnoyingBrooo, 1)
    areWeInAFuncFromInstructions = 0
    areWeInAFuncFromInstructionsLineNum = 0
    funcLangHolder = ""
    funcNameHolder = ""
    funcLibsHolder = ""
    funcFuncHolder = ""
    funcDescriptionHolder = ""
    allFuncLang = []
    allFuncNames = []
    allFuncLibs = []
    allFuncs = []
    allfuncDescription = []
    correctLang = 0
    items147 = LoopParseFunc(instructions, "\n", "\r")
    for A_Index147 , A_LoopField147 in enumerate(items147, start=0):
        if (Trim(A_LoopField147) == "funcEND======================funcEND=============="):
            areWeInAFuncFromInstructions = 0
            areWeInAFuncFromInstructionsLineNum = 0
            if (correctLang == 1 and InStr(htCode, Trim(funcNameHolder))):
                #MsgBox, % funcFuncHolder
                allFuncs.append(funcFuncHolder)
            correctLang = 0
            funcFuncHolder = ""
        if (areWeInAFuncFromInstructions == 1):
            if (areWeInAFuncFromInstructionsLineNum == 1):
                # name of the func
                funcLangHolder = StringTrimLeft(A_LoopField147, 5)
                if (Trim(funcLangHolder) == langToConvertTo):
                    allFuncLang.append(Trim(funcLangHolder))
                    correctLang = 1
            if (areWeInAFuncFromInstructionsLineNum == 2):
                # name of the func
                funcNameHolder = StringTrimLeft(A_LoopField147, 5)
                if (correctLang == 1 and InStr(htCode, Trim(funcNameHolder))):
                    allFuncNames.append(Trim(funcNameHolder))
            if (areWeInAFuncFromInstructionsLineNum == 3):
                # all libs
                funcLibsHolder = StringTrimLeft(A_LoopField147, 5)
                if (correctLang == 1 and InStr(htCode, Trim(funcNameHolder))):
                    allFuncLibs.append(Trim(funcLibsHolder))
            if (areWeInAFuncFromInstructionsLineNum == 4):
                # func description
                funcDescriptionHolder = StringTrimLeft(A_LoopField147, 12)
                if (correctLang == 1 and InStr(htCode, Trim(funcNameHolder))):
                    allfuncDescription.append(Trim(funcDescriptionHolder))
            if (areWeInAFuncFromInstructionsLineNum >= 5):
                # the full func
                if (correctLang == 1 and InStr(htCode, Trim(funcNameHolder))):
                    funcFuncHolder += A_LoopField147 + "\n"
            #MsgBox, % A_LoopField147
            areWeInAFuncFromInstructionsLineNum = areWeInAFuncFromInstructionsLineNum + 1
        if (Trim(A_LoopField147) == "func======================func=============="):
            areWeInAFuncFromInstructions = 1
            areWeInAFuncFromInstructionsLineNum = 1
            correctLang = 0
    #~ MsgBox, ===========================================================================
    #~ msgbox, % allFuncNames
    #~ MsgBox, ===========================================================================
    #~ msgbox, % allFuncLibs
    #~ MsgBox, ===========================================================================
    #~ msgbox, % allFuncLang
    #~ MsgBox, ===========================================================================
    #~ msgbox, % allFuncs
    #~ MsgBox, ===========================================================================
    if (isNotHTVMfile2 == 0):
        if (langToConvertTo == "cpp"):
            htCode = htCode + "\n    return 0;\n}"
            htCode = StrReplace(htCode, "int main(int argc, char* argv[]);", "int main(int argc, char* argv[])")
        if (langToConvertTo == "js" and useJavaScriptAmainFuncDef == "on"):
            htCode = htCode + "\n}\nmain();"
            htCode = StrReplace(htCode, "async function main();", "async function main()")
            htCode = StrReplace(htCode, "function async function main()", "async function main()")
        if (langToConvertTo == "ts" and useJavaScriptAmainFuncDef == "on"):
            htCode = htCode + "\n}\nmain();"
            htCode = StrReplace(htCode, "async function main(): Promise<void>;", "async function main(): Promise<void>")
            htCode = StrReplace(htCode, "function async function main(): Promise<void>", "async function main(): Promise<void>")
        if (langToConvertTo == "go"):
            htCode = htCode + "\n}"
            htCode = StrReplace(htCode, "func main();", "func main()")
        if (langToConvertTo == "cs"):
            htCode = htCode + "\n    }\n}"
            htCode = StrReplace(htCode, "static void Main(string[] args);", "static void Main(string[] args)")
        if (langToConvertTo == "java"):
            htCode = htCode + "\n    }\n}"
            htCode = StrReplace(htCode, "public static void main(String[] args);", "public static void main(String[] args)")
        if (langToConvertTo == "kt"):
            htCode = htCode + "\n}"
            htCode = StrReplace(htCode, "fun main(args: Array<String>);", "fun main(args: Array<String>)")
        if (langToConvertTo == "swift"):
            htCode = htCode + "\n}\nmain()"
            htCode = StrReplace(htCode, "func main();", "func main()")
            htCode = StrReplace(htCode, "func main() ->", "func main()")
        if (langToConvertTo == "dart"):
            htCode = htCode + "\n}"
            htCode = StrReplace(htCode, "void main(List<String> arguments);", "void main(List<String> arguments)")
    jsHTMLdownCode = "</script>\n</body>\n</html>"
    includeLibsInCppIf = 0
    allFuncsToPutAtTop = Chr(10)
    allLibsToPutAtTop = ""
    if (!(len(allFuncNames) <= 0)):
        for A_Index148 in range(0, len(allFuncNames) + 0):
            if (InStr(htCode, allFuncNames[A_Index148]) + "("):
                #MsgBox, % allFuncNames[A_Index148]
                allFuncsToPutAtTop += allFuncs[A_Index148] + "\n"
                if (Trim(allFuncLibs[A_Index148]) != "null"):
                    allLibsToPutAtTop += allFuncLibs[A_Index148] + "|"
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTop, 1)
        allLibsToPutAtTopTEMP = None
        items149 = LoopParseFunc(allLibsToPutAtTop, "|")
        for A_Index149 , A_LoopField149 in enumerate(items149, start=0):
            allLibsToPutAtTopTEMP += A_LoopField149 + "\n"
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTopTEMP, 1)
        includeLibsInCppIf = 1
        if (langToConvertTo == "cpp"):
            allLibsToPutAtTop = "#include <iostream>\n#include <sstream>\n#include <string>\n#include <cstdint>\n#include <algorithm>\n#include <vector>\n#include <any>\n#include <optional>\n" + allLibsToPutAtTop
        if (langToConvertTo == "cs"):
            allLibsToPutAtTop = "using System;\n" + allLibsToPutAtTop
        allLibsToPutAtTop = Sort(allLibsToPutAtTop, "U")
        allLibsToPutAtTop = StrReplace(allLibsToPutAtTop, "~~~", "\n")
        if (isNotHTVMfileEXTRA_INT == 1):
            isNotHTVMfileEXTRA_LIB_INFO = allLibsToPutAtTop
            isNotHTVMfileEXTRA_FUNCS_INFO = allFuncsToPutAtTop
        if (isNotHTVMfile2 == 0):
            if (langToConvertTo == "cs" or langToConvertTo == "java"):
                htCode = "\n" + allFuncsToPutAtTop + "\n" + htCode
            else:
                if (langToConvertTo != "js"):
                    htCode = allLibsToPutAtTop + "\n" + allFuncsToPutAtTop + "\n" + htCode
                else:
                    if (useJavaScriptInAfullHTMLfile != "on"):
                        htCode = allLibsToPutAtTop + "\n" + allFuncsToPutAtTop + "\n" + htCode
                    else:
                        htCode = "\n" + allFuncsToPutAtTop + "\n" + htCode
        if (langToConvertTo == "cs"):
            htCode = allLibsToPutAtTop + "\nclass Program\n{\n" + htCode
        if (langToConvertTo == "java"):
            htCode = allLibsToPutAtTop + "\npublic class Main\n{\n" + htCode
        if (langToConvertTo == "go"):
            htCode = "package main\nimport (\n" + htCode
    for A_Index150 in range(0, theIdNumOfThe34 + 0):
        if (theIdNumOfThe34 == A_Index150 + 1):
            if (langToConvertTo == langFileExtension_2):
                if (keyWordEscpaeChar_2 == "\\" and keyWordEscpaeChar != "\\"):
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index150 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index150 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34))
                else:
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index150 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index150 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34))
            else:
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index150 + 1) + Chr(65) + Chr(65), theIdNumOfThe34theVar[A_Index150 + 1] + Chr(34))
        else:
            if (langToConvertTo == langFileExtension_2):
                if (keyWordEscpaeChar_2 == "\\" and keyWordEscpaeChar != "\\"):
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index150 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index150 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2))
                else:
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index150 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index150 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2))
            else:
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index150 + 1) + Chr(65) + Chr(65), theIdNumOfThe34theVar[A_Index150 + 1])
    if (langToConvertTo == langFileExtension_2):
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, keyWordEscpaeChar_2 + Chr(34))
    else:
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, Chr(92) + Chr(34))
    htCode = StrReplace(htCode, "std::string(" + Chr(34) + Chr(34) + ";),", "std::string(" + Chr(34) + Chr(34) + "),")
    jsHTMLupCode = "<!doctype html>\n<html lang=" + Chr(34) + "en" + Chr(34) + ">\n    <head>\n        <meta charset=" + Chr(34) + "UTF-8" + Chr(34) + " />\n        <meta name=" + Chr(34) + "viewport" + Chr(34) + " content=" + Chr(34) + "width=device-width, initial-scale=1.0" + Chr(34) + " />\n        <title>HTVM</title>\n        <style>\n            body {\n                background-color: #202020;\n                font-family:\n                    " + Chr(34) + "Open Sans" + Chr(34) + ",\n                    -apple-system,\n                    BlinkMacSystemFont,\n                    " + Chr(34) + "Segoe UI" + Chr(34) + ",\n                    Roboto,\n                    Oxygen-Sans,\n                    Ubuntu,\n                    Cantarell,\n                    " + Chr(34) + "Helvetica Neue" + Chr(34) + ",\n                    Helvetica,\n                    Arial,\n                    sans-serif;\n            }\n        </style>\n" + allLibsToPutAtTop + "\n</head>\n    <body>\n<script>"
    if (isNotHTVMfile2 == 0):
        if (useJavaScriptInAfullHTMLfile == "on" and langToConvertTo == "js"):
            htCode = jsHTMLupCode + "\n" + htCode + "\n" + jsHTMLdownCode
        if (langToConvertTo == "cpp" and includeLibsInCppIf == 0):
            htCode = "#include <iostream>\n#include <sstream>\n#include <any>\n#include <string>\n#include <cstdint>\n#include <algorithm>\n#include <vector>\n\n" + htCode
        if (langToConvertTo == "cs"):
            htCode = "\n" + htCode
        if (langToConvertTo == "ahk"):
            htCode = "#EscapeChar \\\n" + htCode
        if (langToConvertTo == "swift"):
            htCode = "import Foundation\n" + htCode
        if (langToConvertTo == langFileExtension_2):
            if (SubStr(htCode, 1, 1) == "\n"):
                htCode = StringTrimLeft(htCode, 1)
    print(htCode)
    return htCode
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
    global allArgs
    argCODE = ""
    argCODEfile = ""
    argHTVMinstr = ""
    argLangTo = ""
    OUTCODE = "null"
    numOfParams = 0
    HTVM_v2_HTVM()
    if (noParams == True):
        return
    items151 = LoopParseFunc(str0)
    for A_Index151 , A_LoopField151 in enumerate(items151, start=0):
        str00 = Trim(A_LoopField151)
        str00 = StringTrimRight(str00, 1)
    print("HTVM v2")
    if (HTVM_getLang_HTVM() == "cpp" or HTVM_getLang_HTVM() == "py"):
        if (HTVM_getLang_HTVM() == "cpp"):
            print("CPP")
        if (HTVM_getLang_HTVM() == "py"):
            print("PY")
        items152 = LoopParseFunc(allArgs, "\n", "\r")
        for A_Index152 , A_LoopField152 in enumerate(items152, start=0):
            if (A_Index152 == 0):
                numOfParams = numOfParams + 1
                argCODE = FileRead(Trim(A_LoopField152))
                argCODEfile = Trim(A_LoopField152)
            elif (A_Index152 == 1):
                numOfParams = numOfParams + 1
                argHTVMinstr = Trim(A_LoopField152)
            elif (A_Index152 == 2):
                numOfParams = numOfParams + 1
                argLangTo = Trim(A_LoopField152)
            else:
                numOfParams = numOfParams + 1
                argHTVMinstrMORE.append(Trim(A_LoopField152))
        print("===============123431234===========start=====")
        for A_Index153 in range(0, len(argHTVMinstrMORE) + 0):
            print(argHTVMinstrMORE[A_Index153])
        print("===============123431234==========end======")
        print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo)
        if (SubStrLastChars(argCODEfile, 4) == ".cpp" or SubStrLastChars(argCODEfile, 3) == ".py" or SubStrLastChars(argCODEfile, 3) == ".js" or SubStrLastChars(argCODEfile, 3) == ".go" or SubStrLastChars(argCODEfile, 4) == ".lua" or SubStrLastChars(argCODEfile, 3) == ".cs" or SubStrLastChars(argCODEfile, 5) == ".java" or SubStrLastChars(argCODEfile, 3) == ".kt" or SubStrLastChars(argCODEfile, 3) == ".rb" or SubStrLastChars(argCODEfile, 4) == ".nim" or SubStrLastChars(argCODEfile, 4) == ".ahk" or SubStrLastChars(argCODEfile, 6) == ".swift" or SubStrLastChars(argCODEfile, 5) == ".dart" or SubStrLastChars(argCODEfile, 3) == ".ts" or SubStrLastChars(argCODEfile, 7) == ".groovy" or SubStrLastChars(argCODEfile, StrLen("." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)))) == "." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)) and numOfParams == 2):
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (SubStrLastChars(argCODEfile, 4) == ".cpp"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "cpp")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 3) == ".py"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "py")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 3) == ".js"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "js")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 3) == ".go"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "go")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 4) == ".lua"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "lua")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 3) == ".cs"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "cs")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 5) == ".java"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "java")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 3) == ".kt"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "kt")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 3) == ".rb"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "rb")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 4) == ".nim"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "nim")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 4) == ".ahk"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "ahk")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 6) == ".swift"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "swift")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 5) == ".dart"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "dart")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 3) == ".ts"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "ts")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, 7) == ".groovy"):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "groovy")
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            elif (SubStrLastChars(argCODEfile, StrLen("." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)))) == "." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2))):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)))
                FileDelete(Trim(argCODEfile))
                FileAppend(OUTCODE, Trim(argCODEfile))
                return
            else:
                print("INVALID LANG!!!")
                return
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            #;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        else:
            if (argLangTo != ""):
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "full", argLangTo)
            else:
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "full")
        print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo)
        if (langToConvertTo == "js" and useJavaScriptInAfullHTMLfile == "on"):
            FileDelete(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + "html")
            FileAppend(OUTCODE, StringTrimRight(argCODEfile, StrLen(langFileExtension)) + "html")
        else:
            FileDelete(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo)
            FileAppend(OUTCODE, StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo)
    if (HTVM_getLang_HTVM() == "js"):
        print("JS")
HTVMv2()