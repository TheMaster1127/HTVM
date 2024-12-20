

# used the print func


theArr = []
theArr.append(1)
theArr.append(2)
theArr.append(2)
theArr.append(3)
theArr.append(3)
theArr.append(3)
tempArr = []
outArr = []
currnet = 0
found = 0
for A_Index1 in range(0, len(theArr) + 0):
    if (A_Index1 != 0):
        currnet = A_Index1
        for A_Index2 in range(0, len(tempArr) + 0):
            if (tempArr[A_Index2] == theArr[currnet]):
                found = 1
                break
        if (found != 1):
            outArr.append(theArr[A_Index1])
        tempArr.append(theArr[A_Index1])
        found = 0
    else:
        tempArr.append(theArr[A_Index1])
        outArr.append(theArr[A_Index1])
print(outArr)