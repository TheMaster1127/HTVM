

# used the print func


temp = []
OSPHTVMOSP_main1_crew1_obj1 = [
"main1.crew1.obj1",
5,
"hello",
temp,
]
OSPHTVMOSP_main1_crew1_obj2 = [
"main1.crew1.obj2",
6,
"hello2",
temp,
]
def OSPHTVMOSP_main1_crew1_method1(this__OSP__this = None):
    if (this__OSP__this[0] == "main1.crew1.obj1"):
        OSPHTVMOSP_main1_crew1_obj1[1] = OSPHTVMOSP_main1_crew1_obj1[1] + 1
    if (this__OSP__this[0] == "main1.crew1.obj2"):
        OSPHTVMOSP_main1_crew1_obj2[1] = OSPHTVMOSP_main1_crew1_obj2[1] + 1
OSPHTVMOSP_main1_crew1_method1(OSPHTVMOSP_main1_crew1_obj1)
OSPHTVMOSP_main1_crew1_method1(OSPHTVMOSP_main1_crew1_obj2)
print(OSPHTVMOSP_main1_crew1_obj1[1])
print(OSPHTVMOSP_main1_crew1_obj2[1])
