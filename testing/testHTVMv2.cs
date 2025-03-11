
using System.Collections.Generic;
using System;
class Program
{


// Print function for various types
    public static void print(object value)
    {
        Console.WriteLine(value);
    }

public static int HTVM_Size<T>(List<T> arr) {
    return arr.Count;
}


[][][][][] Movable_Vehicles_Car [][][][][]
[end][end][end][end][end] Movable_Vehicles_Car [end][end][end][end][end]
[][][][][] Movable_Vehicles_Bike [][][][][]
[end][end][end][end][end] Movable_Vehicles_Bike [end][end][end][end][end]
static void OSPHTVMOSP_Movable_Vehicles_move(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    if (this == "Movable.Vehicles.Car") {
        if (Movable.Vehicles.Car.fuel > 0) {
            print("The car is driving.");
            Movable.Vehicles.Car.fuel = Movable.Vehicles.Car.fuel - 10;
        } else {
            print("The car is out of fuel.");
            Movable.Vehicles.Car.hasFUEL = false;
        }
    }
    else if (this == "Movable.Vehicles.Bike") {
        if (Movable.Vehicles.Bike.energy > 0) {
            print("The bike is pedaling.");
            Movable.Vehicles.Bike.energy = Movable.Vehicles.Bike.energy - 5;
        } else {
            print("The bike is out of energy.");
            Movable.Vehicles.Bike.hasENERGY = false;
        }
    }
}
[][][][][] Movable_settings_GeneralSettings [][][][][]
[end][end][end][end][end] Movable_settings_GeneralSettings [end][end][end][end][end]
[][][][][] Movable_settings_AudioSettings [][][][][]
[end][end][end][end][end] Movable_settings_AudioSettings [end][end][end][end][end]
[][][][][] Movable_settings_DisplaySettings [][][][][]
[end][end][end][end][end] Movable_settings_DisplaySettings [end][end][end][end][end]
static void OSPHTVMOSP_Movable_actions_resetGeneralSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    Movable.settings.GeneralSettings.difficulty = STR("normal");
    Movable.settings.GeneralSettings.volume = 50;
    Movable.settings.GeneralSettings.resolution = STR("1920x1080");
    print("General settings reset to default.");
}
static void OSPHTVMOSP_Movable_actions_printGeneralSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    print("General Settings:");
    print("Difficulty: " + Movable.settings.GeneralSettings.difficulty);
    print("Volume: " + STR(Movable.settings.GeneralSettings.volume));
    print("Resolution: " + Movable.settings.GeneralSettings.resolution);
}
static void OSPHTVMOSP_Movable_actions_resetAudioSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    Movable.settings.AudioSettings.masterVolume = 70;
    Movable.settings.AudioSettings.musicVolume = 50;
    Movable.settings.AudioSettings.sfxVolume = 40;
    print("Audio settings reset to default.");
}
static void OSPHTVMOSP_Movable_actions_printAudioSettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    print("Audio Settings:");
    print("Master Volume: " + STR(Movable.settings.AudioSettings.masterVolume));
    print("Music Volume: " + STR(Movable.settings.AudioSettings.musicVolume));
    print("SFX Volume: " + STR(Movable.settings.AudioSettings.sfxVolume));
}
static void OSPHTVMOSP_Movable_actions_resetDisplaySettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    Movable.settings.DisplaySettings.fullscreen = true;
    Movable.settings.DisplaySettings.aspectRatio = STR("16:9");
    print("Display settings reset to default.");
}
static void OSPHTVMOSP_Movable_actions_printDisplaySettings(OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD) {
    print("Display Settings:");
    print("Fullscreen: " + STR(Movable.settings.DisplaySettings.fullscreen));
    print("Aspect Ratio: " + Movable.settings.DisplaySettings.aspectRatio);
}
[][][][][] Movable_array_name [][][][][]
static List<string> temp = new List<string>();
[end][end][end][end][end] Movable_array_name [end][end][end][end][end]
static string AWSDF() {
    return "hi";
}
static void Main(string[] args) {
    // Test vehicle movement
    while (Movable.Vehicles.Car.hasFUEL == true && Movable.Vehicles.Bike.hasENERGY == true) {
        Movable.Vehicles.move(Movable.Vehicles.Car);
        Movable.Vehicles.move(Movable.Vehicles.Bike);
        print("=====================================");
    }
    // Test settings manipulation
    Movable.settings.GeneralSettings.difficulty = STR("hard");
    Movable.settings.GeneralSettings.volume = 80;
    Movable.settings.GeneralSettings.resolution = STR("2560x1440");
    Movable.settings.AudioSettings.masterVolume = 90;
    Movable.settings.AudioSettings.musicVolume = 60;
    Movable.settings.AudioSettings.sfxVolume = 50;
    Movable.settings.DisplaySettings.fullscreen = false;
    Movable.settings.DisplaySettings.aspectRatio = STR("21:9");
    Movable.actions.printGeneralSettings();
    Movable.actions.printAudioSettings();
    Movable.actions.printDisplaySettings();
    Movable.actions.resetGeneralSettings();
    Movable.actions.resetAudioSettings();
    Movable.actions.resetDisplaySettings();
    Movable.actions.printGeneralSettings();
    Movable.actions.printAudioSettings();
    Movable.actions.printDisplaySettings();
    // Test array manipulation
    Movable.array.name.prop1.push("1text1");
    Movable.array.name.prop1.push("1text2");
    Movable.array.name.prop1.push("1text3");
    Movable.array.name.prop2.push("2text1");
    Movable.array.name.prop2.push("2text2");
    Movable.array.name.prop2.push("2text3");
    Movable.array.name.prop3.push("3text1");
    Movable.array.name.prop3.push("3text2");
    Movable.array.name.prop3.push("3text3");
    Movable.array.name.prop4.push("4text1");
    Movable.array.name.prop4.push("4text2");
    Movable.array.name.prop4.push("4text3");
    // why this
    // cuz python used len(param) insed of param.len() so it meses up evrything
    // if using OSP objects that have a dot (.) it doset work in python to get the lenght
    // but for a name whit no dots it works
    List<string> arrayTempOnlyGetSize1 = new List<string> {Movable.array.name.prop1};
    List<string> arrayTempOnlyGetSize2 = new List<string> {Movable.array.name.prop2};
    List<string> arrayTempOnlyGetSize3 = new List<string> {Movable.array.name.prop3};
    List<string> arrayTempOnlyGetSize4 = new List<string> {Movable.array.name.prop4};
    for (int A_Index1 = 0; A_Index1 < HTVM_Size(arrayTempOnlyGetSize1) + 0; A_Index1++) {
        print(Movable.array.name.prop1[A_Index1]);
    }
    for (int A_Index2 = 0; A_Index2 < HTVM_Size(arrayTempOnlyGetSize2) + 0; A_Index2++) {
        print(Movable.array.name.prop2[A_Index2]);
    }
    for (int A_Index3 = 0; A_Index3 < HTVM_Size(arrayTempOnlyGetSize3) + 0; A_Index3++) {
        print(Movable.array.name.prop3[A_Index3]);
    }
    for (int A_Index4 = 0; A_Index4 < HTVM_Size(arrayTempOnlyGetSize4) + 0; A_Index4++) {
        print(Movable.array.name.prop4[A_Index4]);
    }

}
}