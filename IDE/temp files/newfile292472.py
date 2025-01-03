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

# used imput func

def StrLen(s: str) -> int:
    # Return the length of the given string
    return len(s)

def Chr(number: int) -> str:
    # Return the character corresponding to the Unicode code point, or an empty string if out of range
    return chr(number) if 0 <= number <= 0x10FFFF else ""

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

def Mod(dividend, divisor):
    return dividend % divisor



# Helper function to create spaces
def spaces(n):
    s = ""
    if (n != 0):
        for A_Index1 in range(0, n + 0):
            s += " "
    return s
# Define the function to check odd spaces at the beginning
def CheckOddLeadingSpaces(string123):
    # Initialize a variable to count the spaces
    spaceCount = 0
    # Loop through the string one character at a time
    items2 = LoopParseFunc(string123)
    for A_Index2 , A_LoopField2 in enumerate(items2, start=0):
        # Check if the current character is a space
        if (A_LoopField2 == Chr(32)):
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
    items3 = LoopParseFunc(input)
    for A_Index3 , A_LoopField3 in enumerate(items3, start=0):
        if (A_LoopField3 != " " || foundNonSpace):
            result += A_LoopField3
            foundNonSpace = True
    return result
def getLastChar(strippedString):
    lastChar = None
    items4 = LoopParseFunc(strippedString)
    for A_Index4 , A_LoopField4 in enumerate(items4, start=0):
        lastChar = A_LoopField4
    return lastChar
def AddCurlyBraces(pythonCode):
    pythonCode = StrReplace(pythonCode, A_Tab, "    ")
    result = ""
    indentLevel = 0
    indent = None
    line = None
    stripped = None
    items5 = LoopParseFunc(pythonCode, "\n", "\r")
    for A_Index5 , A_LoopField5 in enumerate(items5, start=0):
        line = A_LoopField5
        stripped = Trim(line)
        if (stripped == ""):
            result += line + "\n"
            continue
        # Count leading spaces
        indent = StrLen(line) - StrLen(LTrim(line))
        #MsgBox, % indent
        # Close braces for unindents
        for A_Index6 , value in enumerate(iter(int, 1), start=0):
            if (indentLevel <= indent):
                break
            indentLevel -= 4
            result += spaces(indentLevel) + "}\n"
        # Add opening brace for new blocks
        if (getLastChar(stripped) == ":") && (SubStr(StrLower(Trim(A_LoopField5)), 1, StrLen(StrLower(keyWordComment))) != StrLower(keyWordComment)):
            result += SubStr(line, 1, -1) + " {\n"
            indentLevel += 4
        else:
            result += line + "\n"
    # Close any remaining open braces
    for A_Index7 , value in enumerate(iter(int, 1), start=0):
        if (indentLevel <= 0):
            break
        indentLevel -= 4
        result += spaces(indentLevel) + "}\n"
    return result
def RepeatSpaces(count):
    spaces = ""
    for A_Index8 in range(0, count + 0):
        spaces += Chr(32)
    return spaces
def indent_nested_curly_braces(input_string, modeCurlyBracesOn):
    indent_size = 4
    current_indent = 0
    result = None
    trimmed_line = None
    resultOut = None
    #MsgBox, % input_string
    items9 = LoopParseFunc(input_string, "\n", "\r")
    for A_Index9 , A_LoopField9 in enumerate(items9, start=0):
        trimmed_line = Trim(A_LoopField9)
        if (trimmed_line == Chr(123)):
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n"
            current_indent = current_indent + indent_size
        elif (trimmed_line == Chr(125)):
            current_indent = current_indent - indent_size
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n"
        else:
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n"
    if (modeCurlyBracesOn == 0):
        resultOut = None
        items10 = LoopParseFunc(result, "\n", "\r")
        for A_Index10 , A_LoopField10 in enumerate(items10, start=0):
            if (Trim(A_LoopField10) != "{") && (Trim(A_LoopField10) != "}"):
                resultOut += A_LoopField10 + "\n"
        result = StringTrimRight(resultOut, 1)
    else:
        # format curly braces in a K&R style
        lookIntoFurture = []
        items11 = LoopParseFunc(result, "\n", "\r")
        for A_Index11 , A_LoopField11 in enumerate(items11, start=0):
            lookIntoFurture += Trim(A_LoopField11)
        lookIntoFurture += " "
        resultOut = None
        skipNext = 0
        items12 = LoopParseFunc(result, "\n", "\r")
        for A_Index12 , A_LoopField12 in enumerate(items12, start=0):
            skipNext = skipNext - 1
            if (skipNext <= 0):
                skipNext = 0
            if (Trim(lookIntoFurture[A_Index12 + 1]) == "{"):
                resultOut += A_LoopField12 + " {\n"
                skipNext = 2
            if (skipNext == 0):
                resultOut += A_LoopField12 + "\n"
        result = StringTrimRight(resultOut, 1)
        lookIntoFurture2 = []
        items13 = LoopParseFunc(result, "\n", "\r")
        for A_Index13 , A_LoopField13 in enumerate(items13, start=0):
            lookIntoFurture2 += Trim(A_LoopField13)
        lookIntoFurture2 += " "
        resultOut = ""
        skipNext = 0
        addSpacesAtTheBegginig = None
        items14 = LoopParseFunc(result, "\n", "\r")
        for A_Index14 , A_LoopField14 in enumerate(items14, start=0):
            skipNext = skipNext - 1
            if (skipNext <= 0):
                skipNext = 0
            if (Trim(A_LoopField14) == "}") && (Trim(lookIntoFurture2[A_Index14 + 1]) == "else {"):
                skipNext = 2
                addSpacesAtTheBegginig = ""
                items15 = LoopParseFunc(A_LoopField14)
                for A_Index15 , A_LoopField15 in enumerate(items15, start=0):
                    if (A_LoopField15 == " "):
                        if (A_LoopField15 != " "):
                            break
                        addSpacesAtTheBegginig += A_LoopField15
                resultOut += addSpacesAtTheBegginig + "} else {\n"
            if (skipNext == 0):
                resultOut += A_LoopField14 + "\n"
        result = StringTrimRight(resultOut, 1)
    resultOut = ""
    ALoopField = None
    items16 = LoopParseFunc(result, "\n", "\r")
    for A_Index16 , A_LoopField16 in enumerate(items16, start=0):
        if (CheckOddLeadingSpaces(A_LoopField16) == "1"):
            ALoopField = StringTrimLeft(A_LoopField16, 1)
            resultOut += ALoopField + "\n"
        else:
            resultOut += A_LoopField16 + "\n"
    result = StringTrimRight(resultOut, 1)
    # Return the result
    return result