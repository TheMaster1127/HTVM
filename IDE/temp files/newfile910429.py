import re
import time

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

# Convert value to integer
def INT(value):
    try:
        # Try converting the value to an integer
        return int(float(value))
    except ValueError:
        # If conversion fails, raise a TypeError
        raise TypeError("Cannot convert to integer")

def Sleep(milliseconds: int) -> None:
    # Sleep for the specified number of milliseconds
    time.sleep(milliseconds / 1000)

# used imput func

def Trim(inputString):
    return inputString.strip() if inputString else ""

def StringTrimRight(input, numChars):
    return input[:-numChars] if numChars <= len(input) else input

def Mod(dividend, divisor):
    return dividend % divisor


def detectWin(board):
    arrPosPlayer1 = []
    arrPosPlayer2 = []
    temp1 = "player"
    items1 = LoopParseFunc(board, "|")
    for A_Index1 , A_LoopField1 in enumerate(items1, start=0):
        if (Trim(A_LoopField1) == "x"):
            arrPosPlayer1.append(1)
        else:
            arrPosPlayer1.append(0)
    items2 = LoopParseFunc(board, "|")
    for A_Index2 , A_LoopField2 in enumerate(items2, start=0):
        if (Trim(A_LoopField2) == "o"):
            arrPosPlayer2.append(1)
        else:
            arrPosPlayer2.append(0)
    for A_Index3 in range(0, 3 + 0):
        if (arrPosPlayer1[0 + (A_Index3 * 3)] == 1 and arrPosPlayer1[1 + (A_Index3 * 3)] == 1 and arrPosPlayer1[2 + (A_Index3 * 3)] == 1):
            return temp1 + " 1 won!!!"
    for A_Index4 in range(0, 3 + 0):
        if (arrPosPlayer1[A_Index4] == 1 and arrPosPlayer1[A_Index4 + 3] == 1 and arrPosPlayer1[A_Index4 + 6] == 1):
            return temp1 + " 1 won!!!"
    if (arrPosPlayer1[0] == 1 and arrPosPlayer1[4] == 1 and arrPosPlayer1[8] == 1):
        return temp1 + " 1 won!!!"
    if (arrPosPlayer1[2] == 1 and arrPosPlayer1[4] == 1 and arrPosPlayer1[6] == 1):
        return temp1 + " 1 won!!!"
    for A_Index5 in range(0, 3 + 0):
        if (arrPosPlayer2[0 + (A_Index5 * 3)] == 1 and arrPosPlayer2[1 + (A_Index5 * 3)] == 1 and arrPosPlayer2[2 + (A_Index5 * 3)] == 1):
            return temp1 + " 2 won!!!"
    for A_Index6 in range(0, 3 + 0):
        if (arrPosPlayer2[A_Index6] == 1 and arrPosPlayer2[A_Index6 + 3] == 1 and arrPosPlayer2[A_Index6 + 6] == 1):
            return temp1 + " 2 won!!!"
    if (arrPosPlayer2[0] == 1 and arrPosPlayer2[4] == 1 and arrPosPlayer2[8] == 1):
        return temp1 + " 2 won!!!"
    if (arrPosPlayer2[2] == 1 and arrPosPlayer2[4] == 1 and arrPosPlayer2[6] == 1):
        return temp1 + " 2 won!!!"
    return temp1 + "null"
tabel = "0|0|0|0|0|0|0|0|0"
tabelTemp = ""
turn = 0
pos = 0
tempHoldToPrint = ""
tempHoldToPrintINT = 0
error = 0
index = 0
for A_Index7 in range(0, 1000 + 0):
    index = index + 1
    if (Mod(index, 2)):
        for A_Index8 , value in enumerate(iter(int, 1), start=0):
            pos = INT(Trim(input("PLAYER 2 make a move from pos 1 to 9: ")))
            Sleep(10)
            if (pos <= 0 or pos >= 10):
                print("error cant play this move!!!")
            else:
                break
        tabelTemp = ""
        items9 = LoopParseFunc(tabel, "|")
        for A_Index9 , A_LoopField9 in enumerate(items9, start=0):
            if (A_Index9 + 1 == pos):
                if (Trim(A_LoopField9) == "x" or Trim(A_LoopField9) == "o"):
                    error = 1
                    index = index - 1
                    print("error cant play this move!!!")
                    break
                tabelTemp += "o|"
            else:
                tabelTemp += A_LoopField9 + "|"
        if (error == 0):
            error = 0
            tabel = StringTrimRight(tabelTemp, 1)
        else:
            error = 0
            continue
    else:
        for A_Index10 , value in enumerate(iter(int, 1), start=0):
            pos = INT(Trim(input("PLAYER 1 make a move from pos 1 to 9: ")))
            Sleep(10)
            if (pos <= 0 or pos >= 10):
                print("error cant play this move!!!")
            else:
                break
        tabelTemp = ""
        items11 = LoopParseFunc(tabel, "|")
        for A_Index11 , A_LoopField11 in enumerate(items11, start=0):
            if (A_Index11 + 1 == pos):
                if (Trim(A_LoopField11) == "x" or Trim(A_LoopField11) == "o"):
                    error = 1
                    index = index - 1
                    print("error cant play this move!!!")
                    break
                tabelTemp += "x|"
            else:
                tabelTemp += A_LoopField11 + "|"
        if (error == 0):
            error = 0
            tabel = StringTrimRight(tabelTemp, 1)
        else:
            error = 0
            continue
    tempHoldToPrint = ""
    tempHoldToPrintINT = 0
    items12 = LoopParseFunc(tabel, "|")
    for A_Index12 , A_LoopField12 in enumerate(items12, start=0):
        tempHoldToPrintINT = tempHoldToPrintINT + 1
        tempHoldToPrint += A_LoopField12 + "|"
        if (tempHoldToPrintINT == 3):
            tempHoldToPrintINT = 0
            tempHoldToPrint += "\n"
    tempHoldToPrint = StringTrimRight(tempHoldToPrint, 1)
    print(tempHoldToPrint)
    Sleep(10)
    if (detectWin(tempHoldToPrint) == "player 1 won!!!"):
        print("player 1 won!!!")
        break
    if (detectWin(tempHoldToPrint) == "player 2 won!!!"):
        print("player 2 won!!!")
        break
print("GAME OVER!!!")
