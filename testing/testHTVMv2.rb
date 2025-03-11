

# Print function for various types
def print(value)
  if value.is_a?(String)
    puts value
  elsif value.is_a?(Numeric)
    puts value.to_s
  elsif value.is_a?(TrueClass) || value.is_a?(FalseClass)
    puts value ? "true" : "false"
  else
    puts "Unsupported type"
  end
end

def HTVM_Size(arr)
  arr.size
end


[][][][][] Movable_Vehicles_Car [][][][][]
[end][end][end][end][end] Movable_Vehicles_Car [end][end][end][end][end]
[][][][][] Movable_Vehicles_Bike [][][][][]
[end][end][end][end][end] Movable_Vehicles_Bike [end][end][end][end][end]
def OSPHTVMOSP_Movable_Vehicles_move(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
    if (this == "Movable.Vehicles.Car")
        if (Movable.Vehicles.Car.fuel > 0)
            print("The car is driving.")
            Movable.Vehicles.Car.fuel = Movable.Vehicles.Car.fuel - 10
        else
            print("The car is out of fuel.")
            Movable.Vehicles.Car.hasFUEL = false
        end
    elsif (this == "Movable.Vehicles.Bike")
        if (Movable.Vehicles.Bike.energy > 0)
            print("The bike is pedaling.")
            Movable.Vehicles.Bike.energy = Movable.Vehicles.Bike.energy - 5
        else
            print("The bike is out of energy.")
            Movable.Vehicles.Bike.hasENERGY = false
        end
    end
end
[][][][][] Movable_settings_GeneralSettings [][][][][]
[end][end][end][end][end] Movable_settings_GeneralSettings [end][end][end][end][end]
[][][][][] Movable_settings_AudioSettings [][][][][]
[end][end][end][end][end] Movable_settings_AudioSettings [end][end][end][end][end]
[][][][][] Movable_settings_DisplaySettings [][][][][]
[end][end][end][end][end] Movable_settings_DisplaySettings [end][end][end][end][end]
def OSPHTVMOSP_Movable_actions_resetGeneralSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
    Movable.settings.GeneralSettings.difficulty = STR("normal")
    Movable.settings.GeneralSettings.volume = 50
    Movable.settings.GeneralSettings.resolution = STR("1920x1080")
    print("General settings reset to default.")
end
def OSPHTVMOSP_Movable_actions_printGeneralSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
    print("General Settings:")
    print("Difficulty: " + Movable.settings.GeneralSettings.difficulty)
    print("Volume: " + STR(Movable.settings.GeneralSettings.volume))
    print("Resolution: " + Movable.settings.GeneralSettings.resolution)
end
def OSPHTVMOSP_Movable_actions_resetAudioSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
    Movable.settings.AudioSettings.masterVolume = 70
    Movable.settings.AudioSettings.musicVolume = 50
    Movable.settings.AudioSettings.sfxVolume = 40
    print("Audio settings reset to default.")
end
def OSPHTVMOSP_Movable_actions_printAudioSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
    print("Audio Settings:")
    print("Master Volume: " + STR(Movable.settings.AudioSettings.masterVolume))
    print("Music Volume: " + STR(Movable.settings.AudioSettings.musicVolume))
    print("SFX Volume: " + STR(Movable.settings.AudioSettings.sfxVolume))
end
def OSPHTVMOSP_Movable_actions_resetDisplaySettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
    Movable.settings.DisplaySettings.fullscreen = true
    Movable.settings.DisplaySettings.aspectRatio = STR("16:9")
    print("Display settings reset to default.")
end
def OSPHTVMOSP_Movable_actions_printDisplaySettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD)
    print("Display Settings:")
    print("Fullscreen: " + STR(Movable.settings.DisplaySettings.fullscreen))
    print("Aspect Ratio: " + Movable.settings.DisplaySettings.aspectRatio)
end
[][][][][] Movable_array_name [][][][][]
temp = []
[end][end][end][end][end] Movable_array_name [end][end][end][end][end]
def AWSDF()
    return "hi"
end
# Test vehicle movement
while (Movable.Vehicles.Car.hasFUEL == true && Movable.Vehicles.Bike.hasENERGY == true)
    Movable.Vehicles.move(Movable.Vehicles.Car)
    Movable.Vehicles.move(Movable.Vehicles.Bike)
    print("=====================================")
end
# Test settings manipulation
Movable.settings.GeneralSettings.difficulty = STR("hard")
Movable.settings.GeneralSettings.volume = 80
Movable.settings.GeneralSettings.resolution = STR("2560x1440")
Movable.settings.AudioSettings.masterVolume = 90
Movable.settings.AudioSettings.musicVolume = 60
Movable.settings.AudioSettings.sfxVolume = 50
Movable.settings.DisplaySettings.fullscreen = false
Movable.settings.DisplaySettings.aspectRatio = STR("21:9")
Movable.actions.printGeneralSettings()
Movable.actions.printAudioSettings()
Movable.actions.printDisplaySettings()
Movable.actions.resetGeneralSettings()
Movable.actions.resetAudioSettings()
Movable.actions.resetDisplaySettings()
Movable.actions.printGeneralSettings()
Movable.actions.printAudioSettings()
Movable.actions.printDisplaySettings()
# Test array manipulation
Movable.array.name.prop1.push("1text1")
Movable.array.name.prop1.push("1text2")
Movable.array.name.prop1.push("1text3")
Movable.array.name.prop2.push("2text1")
Movable.array.name.prop2.push("2text2")
Movable.array.name.prop2.push("2text3")
Movable.array.name.prop3.push("3text1")
Movable.array.name.prop3.push("3text2")
Movable.array.name.prop3.push("3text3")
Movable.array.name.prop4.push("4text1")
Movable.array.name.prop4.push("4text2")
Movable.array.name.prop4.push("4text3")
# why this
# cuz python used len(param) insed of param.len() so it meses up evrything
# if using OSP objects that have a dot (.) it doset work in python to get the lenght
# but for a name whit no dots it works
arrayTempOnlyGetSize1 = [Movable.array.name.prop1]
arrayTempOnlyGetSize2 = [Movable.array.name.prop2]
arrayTempOnlyGetSize3 = [Movable.array.name.prop3]
arrayTempOnlyGetSize4 = [Movable.array.name.prop4]
for a_index1 in 0...HTVM_Size(arrayTempOnlyGetSize1) + 0 do
    print(Movable.array.name.prop1[a_index1])
end
for a_index2 in 0...HTVM_Size(arrayTempOnlyGetSize2) + 0 do
    print(Movable.array.name.prop2[a_index2])
end
for a_index3 in 0...HTVM_Size(arrayTempOnlyGetSize3) + 0 do
    print(Movable.array.name.prop3[a_index3])
end
for a_index4 in 0...HTVM_Size(arrayTempOnlyGetSize4) + 0 do
    print(Movable.array.name.prop4[a_index4])
end