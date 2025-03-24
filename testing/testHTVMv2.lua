

-- Print function for different types

function STR(value)
    if type(value) == "number" then
        return tostring(value)
    elseif type(value) == "boolean" then
        return value and "1" or "0"
    elseif type(value) == "string" then
        return value
    else
        return tostring(value)
    end
end

function HTVM_Append(arr, value)
    table.insert(arr, value)
end

function HTVM_Size(arr)
    return #arr
end


Movable_Vehicles_Car_door = 4
Movable_Vehicles_Car_fuel = 100
Movable_Vehicles_Car_hasFUEL = true
Movable_Vehicles_Bike_hasGears = true
Movable_Vehicles_Bike_energy = 100
Movable_Vehicles_Bike_hasENERGY = true
function OSPHTVMOSP_Movable_Vehicles_move(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD or ""
if (OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD == "Movable.Vehicles.Car") then
    if (Movable_Vehicles_Car_fuel > 0) then
        print("The car is driving.")
        Movable_Vehicles_Car_fuel = Movable_Vehicles_Car_fuel - 10
    else
        print("The car is out of fuel.")
        Movable_Vehicles_Car_hasFUEL = false
    end
elseif (OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD == "Movable.Vehicles.Bike") then
    if (Movable_Vehicles_Bike_energy > 0) then
        print("The bike is pedaling.")
        Movable_Vehicles_Bike_energy = Movable_Vehicles_Bike_energy - 5
    else
        print("The bike is out of energy.")
        Movable_Vehicles_Bike_hasENERGY = false
    end
end
end
Movable_settings_GeneralSettings_difficulty = "normal"
Movable_settings_GeneralSettings_volume = 50
Movable_settings_GeneralSettings_resolution = "1920x1080"
Movable_settings_AudioSettings_masterVolume = 70
Movable_settings_AudioSettings_musicVolume = 50
Movable_settings_AudioSettings_sfxVolume = 40
Movable_settings_DisplaySettings_fullscreen = true
Movable_settings_DisplaySettings_aspectRatio = "16:9"
function OSPHTVMOSP_Movable_actions_resetGeneralSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD or ""
Movable_settings_GeneralSettings_difficulty = STR("normal")
Movable_settings_GeneralSettings_volume = 50
Movable_settings_GeneralSettings_resolution = STR("1920x1080")
print("General settings reset to default.")
end
function OSPHTVMOSP_Movable_actions_printGeneralSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD or ""
print("General Settings:")
print("Difficulty: " .. Movable_settings_GeneralSettings_difficulty)
print("Volume: " .. STR(Movable_settings_GeneralSettings_volume))
print("Resolution: " .. Movable_settings_GeneralSettings_resolution)
end
function OSPHTVMOSP_Movable_actions_resetAudioSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD or ""
Movable_settings_AudioSettings_masterVolume = 70
Movable_settings_AudioSettings_musicVolume = 50
Movable_settings_AudioSettings_sfxVolume = 40
print("Audio settings reset to default.")
end
function OSPHTVMOSP_Movable_actions_printAudioSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD or ""
print("Audio Settings:")
print("Master Volume: " .. STR(Movable_settings_AudioSettings_masterVolume))
print("Music Volume: " .. STR(Movable_settings_AudioSettings_musicVolume))
print("SFX Volume: " .. STR(Movable_settings_AudioSettings_sfxVolume))
end
function OSPHTVMOSP_Movable_actions_resetDisplaySettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD or ""
Movable_settings_DisplaySettings_fullscreen = true
Movable_settings_DisplaySettings_aspectRatio = STR("16:9")
print("Display settings reset to default.")
end
function OSPHTVMOSP_Movable_actions_printDisplaySettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD or ""
print("Display Settings:")
print("Fullscreen: " .. STR(Movable_settings_DisplaySettings_fullscreen))
print("Aspect Ratio: " .. Movable_settings_DisplaySettings_aspectRatio)
end
Movable_array_name_prop1 = {}
Movable_array_name_prop2 = {}
Movable_array_name_prop3 = {}
Movable_array_name_prop4 = {}
-- Test vehicle movement
while (Movable_Vehicles_Car_hasFUEL == true and Movable_Vehicles_Bike_hasENERGY == true) do
OSPHTVMOSP_Movable_Vehicles_move("Movable.Vehicles.Car")
OSPHTVMOSP_Movable_Vehicles_move("Movable.Vehicles.Bike")
print("=====================================")
end
-- Test settings manipulation
Movable_settings_GeneralSettings_difficulty = STR("hard")
Movable_settings_GeneralSettings_volume = 80
Movable_settings_GeneralSettings_resolution = STR("2560x1440")
Movable_settings_AudioSettings_masterVolume = 90
Movable_settings_AudioSettings_musicVolume = 60
Movable_settings_AudioSettings_sfxVolume = 50
Movable_settings_DisplaySettings_fullscreen = false
Movable_settings_DisplaySettings_aspectRatio = STR("21:9")
OSPHTVMOSP_Movable_actions_printGeneralSettings()
OSPHTVMOSP_Movable_actions_printAudioSettings()
OSPHTVMOSP_Movable_actions_printDisplaySettings()
OSPHTVMOSP_Movable_actions_resetGeneralSettings()
OSPHTVMOSP_Movable_actions_resetAudioSettings()
OSPHTVMOSP_Movable_actions_resetDisplaySettings()
OSPHTVMOSP_Movable_actions_printGeneralSettings()
OSPHTVMOSP_Movable_actions_printAudioSettings()
OSPHTVMOSP_Movable_actions_printDisplaySettings()
-- Test array manipulation
HTVM_Append(Movable_array_name_prop1, "1text1")
HTVM_Append(Movable_array_name_prop1, "1text2")
HTVM_Append(Movable_array_name_prop1, "1text3")
HTVM_Append(Movable_array_name_prop2, "2text1")
HTVM_Append(Movable_array_name_prop2, "2text2")
HTVM_Append(Movable_array_name_prop2, "2text3")
HTVM_Append(Movable_array_name_prop3, "3text1")
HTVM_Append(Movable_array_name_prop3, "3text2")
HTVM_Append(Movable_array_name_prop3, "3text3")
HTVM_Append(Movable_array_name_prop4, "4text1")
HTVM_Append(Movable_array_name_prop4, "4text2")
HTVM_Append(Movable_array_name_prop4, "4text3")
for A_Index1 = 0 + 1 , HTVM_Size(Movable_array_name_prop1) + 0 do
print(Movable_array_name_prop1[A_Index1])
end
for A_Index2 = 0 + 1 , HTVM_Size(Movable_array_name_prop2) + 0 do
print(Movable_array_name_prop2[A_Index2])
end
for A_Index3 = 0 + 1 , HTVM_Size(Movable_array_name_prop3) + 0 do
print(Movable_array_name_prop3[A_Index3])
end
for A_Index4 = 0 + 1 , HTVM_Size(Movable_array_name_prop4) + 0 do
print(Movable_array_name_prop4[A_Index4])
end