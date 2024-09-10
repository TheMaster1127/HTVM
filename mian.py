

def MsgBox(value):
	print(value)



arr123 = []
arr123.append(6)
arr123.append(5)
arr123.append(58)
# You can use indentations if you want to. It's all optional.
for A_Index1 in range(1, len(arr123) + 1):
    MsgBox(arr123[A_Index1 - 1])
# You can use indentations if you want to. It's all optional.
for A_Index2 in range(1, 3 + 1):
    MsgBox(A_Index2)
# You can use indentations if you want to. It's all optional.
if arr123[1] == 5:
    MsgBox("yes")