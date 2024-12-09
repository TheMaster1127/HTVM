

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


copyTemp1 = []
copyTemp2 = []
OSPHTVMOSP_someObj = [
"someObj",
copyTemp1,
]
OSPHTVMOSP_someObj2 = [
"someObj2",
copyTemp2,
]
OSPHTVMOSP_main1_main2_main3_main4_main1_main = [
"main1.main2.main3.main4.main1.main",
"hello BOWAH",
]
for A_Index1 in range(0, 7 + 0):
    OSPHTVMOSP_someObj[1].append("hello" + STR(A_Index1))
    OSPHTVMOSP_someObj2[1].append("hello" + STR(A_Index1))
print(OSPHTVMOSP_main1_main2_main3_main4_main1_main[1])
print(OSPHTVMOSP_someObj[1][5])
print(OSPHTVMOSP_someObj2[1][5])
