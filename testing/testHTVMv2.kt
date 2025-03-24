

// Print function for various types
fun print(value: Any) {
  println(value)
}

fun <T> HTVM_Size(arr: List<T>): Int {
    return arr.size
}


[][][][][] Movable_Vehicles_Car [][][][][]
[end][end][end][end][end] Movable_Vehicles_Car [end][end][end][end][end]
[][][][][] Movable_Vehicles_Bike [][][][][]
[end][end][end][end][end] Movable_Vehicles_Bike [end][end][end][end][end]
fun OSPHTVMOSP_Movable_Vehicles_move(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    if (this == "Movable.Vehicles.Car") {
        if (Movable.Vehicles.Car.fuel > 0) {
            print("The car is driving.")
            Movable.Vehicles.Car.fuel = Movable.Vehicles.Car.fuel - 10
        } else {
            print("The car is out of fuel.")
            Movable.Vehicles.Car.hasFUEL = false
        }
    }
    else if (this == "Movable.Vehicles.Bike") {
        if (Movable.Vehicles.Bike.energy > 0) {
            print("The bike is pedaling.")
            Movable.Vehicles.Bike.energy = Movable.Vehicles.Bike.energy - 5
        } else {
            print("The bike is out of energy.")
            Movable.Vehicles.Bike.hasENERGY = false
        }
    }
}
[][][][][] Movable_settings_GeneralSettings [][][][][]
[end][end][end][end][end] Movable_settings_GeneralSettings [end][end][end][end][end]
[][][][][] Movable_settings_AudioSettings [][][][][]
[end][end][end][end][end] Movable_settings_AudioSettings [end][end][end][end][end]
[][][][][] Movable_settings_DisplaySettings [][][][][]
[end][end][end][end][end] Movable_settings_DisplaySettings [end][end][end][end][end]
fun OSPHTVMOSP_Movable_actions_resetGeneralSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    Movable.settings.GeneralSettings.difficulty = STR("normal")
    Movable.settings.GeneralSettings.volume = 50
    Movable.settings.GeneralSettings.resolution = STR("1920x1080")
    print("General settings reset to default.")
}
fun OSPHTVMOSP_Movable_actions_printGeneralSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    print("General Settings:")
    print("Difficulty: " + Movable.settings.GeneralSettings.difficulty)
    print("Volume: " + STR(Movable.settings.GeneralSettings.volume))
    print("Resolution: " + Movable.settings.GeneralSettings.resolution)
}
fun OSPHTVMOSP_Movable_actions_resetAudioSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    Movable.settings.AudioSettings.masterVolume = 70
    Movable.settings.AudioSettings.musicVolume = 50
    Movable.settings.AudioSettings.sfxVolume = 40
    print("Audio settings reset to default.")
}
fun OSPHTVMOSP_Movable_actions_printAudioSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    print("Audio Settings:")
    print("Master Volume: " + STR(Movable.settings.AudioSettings.masterVolume))
    print("Music Volume: " + STR(Movable.settings.AudioSettings.musicVolume))
    print("SFX Volume: " + STR(Movable.settings.AudioSettings.sfxVolume))
}
fun OSPHTVMOSP_Movable_actions_resetDisplaySettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    Movable.settings.DisplaySettings.fullscreen = true
    Movable.settings.DisplaySettings.aspectRatio = STR("16:9")
    print("Display settings reset to default.")
}
fun OSPHTVMOSP_Movable_actions_printDisplaySettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    print("Display Settings:")
    print("Fullscreen: " + STR(Movable.settings.DisplaySettings.fullscreen))
    print("Aspect Ratio: " + Movable.settings.DisplaySettings.aspectRatio)
}
[][][][][] Movable_array_name [][][][][]
val temp = ArrayList<String>()
[end][end][end][end][end] Movable_array_name [end][end][end][end][end]
fun AWSDF(): String {
    return "hi"
}
fun main(args: Array<String>) {
    // Test vehicle movement
    while (Movable.Vehicles.Car.hasFUEL == true && Movable.Vehicles.Bike.hasENERGY == true) {
        Movable.Vehicles.move(Movable.Vehicles.Car)
        Movable.Vehicles.move(Movable.Vehicles.Bike)
        print("=====================================")
    }
    // Test settings manipulation
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
    // Test array manipulation
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
    // why this
    // cuz python used len(param) insed of param.len() so it meses up evrything
    // if using OSP objects that have a dot (.) it doset work in python to get the lenght
    // but for a name whit no dots it works
    val arrayTempOnlyGetSize1 = arrayListOf(Movable.array.name.prop1)
    val arrayTempOnlyGetSize2 = arrayListOf(Movable.array.name.prop2)
    val arrayTempOnlyGetSize3 = arrayListOf(Movable.array.name.prop3)
    val arrayTempOnlyGetSize4 = arrayListOf(Movable.array.name.prop4)
    for (A_Index1 in 0 until HTVM_Size(arrayTempOnlyGetSize1) + 0) {
        print(Movable.array.name.prop1[A_Index1])
    }
    for (A_Index2 in 0 until HTVM_Size(arrayTempOnlyGetSize2) + 0) {
        print(Movable.array.name.prop2[A_Index2])
    }
    for (A_Index3 in 0 until HTVM_Size(arrayTempOnlyGetSize3) + 0) {
        print(Movable.array.name.prop3[A_Index3])
    }
    for (A_Index4 in 0 until HTVM_Size(arrayTempOnlyGetSize4) + 0) {
        print(Movable.array.name.prop4[A_Index4])
    }
}