

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


# This is a preview of my language and how it looks like.
#OSP
OSPHTVMOSP_Movable_Vehicles_Car = [
"Movable.Vehicles.Car",
4,
100,
True,
]
OSPHTVMOSP_Movable_Vehicles_Bike = [
"Movable.Vehicles.Bike",
True,
100,
True,
]
def OSPHTVMOSP_Movable_Vehicles_move(this__OSP__this = None):
    if (this__OSP__this[0] == "Movable.Vehicles.Car"):
        if (OSPHTVMOSP_Movable_Vehicles_Car[2] > 0):
            print("The car is driving.")
            OSPHTVMOSP_Movable_Vehicles_Car[2] = OSPHTVMOSP_Movable_Vehicles_Car[2] - 10
        else:
            print("The car is out of fuel.")
            OSPHTVMOSP_Movable_Vehicles_Car[3] = False
    elif (this__OSP__this[0] == "Movable.Vehicles.Bike"):
        if (OSPHTVMOSP_Movable_Vehicles_Bike[2] > 0):
            print("The bike is pedaling.")
            OSPHTVMOSP_Movable_Vehicles_Bike[2] = OSPHTVMOSP_Movable_Vehicles_Bike[2] - 5
        else:
            print("The bike is out of energy.")
            OSPHTVMOSP_Movable_Vehicles_Bike[3] = False
OSPHTVMOSP_Movable_settings_GeneralSettings = [
"Movable.settings.GeneralSettings",
"normal",
50,
"1920x1080",
]
OSPHTVMOSP_Movable_settings_AudioSettings = [
"Movable.settings.AudioSettings",
70,
50,
40,
]
OSPHTVMOSP_Movable_settings_DisplaySettings = [
"Movable.settings.DisplaySettings",
True,
"16:9",
]
# General Settings Methods
def OSPHTVMOSP_Movable_actions_resetGeneralSettings(this__OSP__this = None):
    OSPHTVMOSP_Movable_settings_GeneralSettings[1] = STR("normal")
    OSPHTVMOSP_Movable_settings_GeneralSettings[2] = 50
    OSPHTVMOSP_Movable_settings_GeneralSettings[3] = STR("1920x1080")
    print("General settings reset to default.")
def OSPHTVMOSP_Movable_actions_printGeneralSettings(this__OSP__this = None):
    print("General Settings:")
    print("Difficulty: " + OSPHTVMOSP_Movable_settings_GeneralSettings[1])
    print("Volume: " + STR(OSPHTVMOSP_Movable_settings_GeneralSettings[2]))
    print("Resolution: " + OSPHTVMOSP_Movable_settings_GeneralSettings[3])
# Audio Settings Methods
def OSPHTVMOSP_Movable_actions_resetAudioSettings(this__OSP__this = None):
    OSPHTVMOSP_Movable_settings_AudioSettings[1] = 70
    OSPHTVMOSP_Movable_settings_AudioSettings[2] = 50
    OSPHTVMOSP_Movable_settings_AudioSettings[3] = 40
    print("Audio settings reset to default.")
def OSPHTVMOSP_Movable_actions_printAudioSettings(this__OSP__this = None):
    print("Audio Settings:")
    print("Master Volume: " + STR(OSPHTVMOSP_Movable_settings_AudioSettings[1]))
    print("Music Volume: " + STR(OSPHTVMOSP_Movable_settings_AudioSettings[2]))
    print("SFX Volume: " + STR(OSPHTVMOSP_Movable_settings_AudioSettings[3]))
# Display Settings Methods
def OSPHTVMOSP_Movable_actions_resetDisplaySettings(this__OSP__this = None):
    OSPHTVMOSP_Movable_settings_DisplaySettings[1] = True
    OSPHTVMOSP_Movable_settings_DisplaySettings[2] = STR("16:9")
    print("Display settings reset to default.")
def OSPHTVMOSP_Movable_actions_printDisplaySettings(this__OSP__this = None):
    print("Display Settings:")
    print("Fullscreen: " + STR(OSPHTVMOSP_Movable_settings_DisplaySettings[1]))
    print("Aspect Ratio: " + OSPHTVMOSP_Movable_settings_DisplaySettings[2])
temp = []
OSPHTVMOSP_Movable_array_name = [
"Movable.array.name",
temp,
temp,
temp,
temp,
]
# Test vehicle movement
while (OSPHTVMOSP_Movable_Vehicles_Car[3] == True and OSPHTVMOSP_Movable_Vehicles_Bike[3] == True):
    OSPHTVMOSP_Movable_Vehicles_move(OSPHTVMOSP_Movable_Vehicles_Car)
    OSPHTVMOSP_Movable_Vehicles_move(OSPHTVMOSP_Movable_Vehicles_Bike)
    print("=====================================")
# Test settings manipulation
OSPHTVMOSP_Movable_settings_GeneralSettings[1] = STR("hard")
OSPHTVMOSP_Movable_settings_GeneralSettings[2] = 80
OSPHTVMOSP_Movable_settings_GeneralSettings[3] = STR("2560x1440")
OSPHTVMOSP_Movable_settings_AudioSettings[1] = 90
OSPHTVMOSP_Movable_settings_AudioSettings[2] = 60
OSPHTVMOSP_Movable_settings_AudioSettings[3] = 50
OSPHTVMOSP_Movable_settings_DisplaySettings[1] = False
OSPHTVMOSP_Movable_settings_DisplaySettings[2] = STR("21:9")
OSPHTVMOSP_Movable_actions_printGeneralSettings()
OSPHTVMOSP_Movable_actions_printAudioSettings()
OSPHTVMOSP_Movable_actions_printDisplaySettings()
OSPHTVMOSP_Movable_actions_resetGeneralSettings()
OSPHTVMOSP_Movable_actions_resetAudioSettings()
OSPHTVMOSP_Movable_actions_resetDisplaySettings()
OSPHTVMOSP_Movable_actions_printGeneralSettings()
OSPHTVMOSP_Movable_actions_printAudioSettings()
OSPHTVMOSP_Movable_actions_printDisplaySettings()
# Test array manipulation
OSPHTVMOSP_Movable_array_name[1].append("1text1")
OSPHTVMOSP_Movable_array_name[1].append("1text2")
OSPHTVMOSP_Movable_array_name[1].append("1text3")
OSPHTVMOSP_Movable_array_name[2].append("2text1")
OSPHTVMOSP_Movable_array_name[2].append("2text2")
OSPHTVMOSP_Movable_array_name[2].append("2text3")
OSPHTVMOSP_Movable_array_name[3].append("3text1")
OSPHTVMOSP_Movable_array_name[3].append("3text2")
OSPHTVMOSP_Movable_array_name[3].append("3text3")
OSPHTVMOSP_Movable_array_name[4].append("4text1")
OSPHTVMOSP_Movable_array_name[4].append("4text2")
OSPHTVMOSP_Movable_array_name[4].append("4text3")
# why this__OSP__this[0]
# cuz python used len(param) insed of param.len() so it meses up evrything
# if using OSP objects that have a dot (.) it doset work in python to get the lenght
# but for a name whit no dots it works
arrayTempOnlyGetSize1 = OSPHTVMOSP_Movable_array_name[1]
arrayTempOnlyGetSize2 = OSPHTVMOSP_Movable_array_name[2]
arrayTempOnlyGetSize3 = OSPHTVMOSP_Movable_array_name[3]
arrayTempOnlyGetSize4 = OSPHTVMOSP_Movable_array_name[4]
for A_Index1 in range(0, len(arrayTempOnlyGetSize1) + 0):
    print(OSPHTVMOSP_Movable_array_name[1][A_Index1])
for A_Index2 in range(0, len(arrayTempOnlyGetSize2) + 0):
    print(OSPHTVMOSP_Movable_array_name[2][A_Index2])
for A_Index3 in range(0, len(arrayTempOnlyGetSize3) + 0):
    print(OSPHTVMOSP_Movable_array_name[3][A_Index3])
for A_Index4 in range(0, len(arrayTempOnlyGetSize4) + 0):
    print(OSPHTVMOSP_Movable_array_name[4][A_Index4])