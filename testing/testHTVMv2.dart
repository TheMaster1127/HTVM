

// Print function for various types

String STR(dynamic value) {
  if (value is int || value is double || value is num) {
    return value.toString();
  } else if (value is bool) {
    return value ? "1" : "0";
  } else if (value is String) {
    return value;
  } else {
    return value.toString();
  }
}

void HTVM_Append<T>(List<T> arr, T value) {
  arr.add(value);
}

int HTVM_Size<T>(List<T> arr) {
  return arr.length;
}


int Movable_Vehicles_Car_door = 4;
int Movable_Vehicles_Car_fuel = 100;
bool Movable_Vehicles_Car_hasFUEL = true;
bool Movable_Vehicles_Bike_hasGears = true;
int Movable_Vehicles_Bike_energy = 100;
bool Movable_Vehicles_Bike_hasENERGY = true;
void OSPHTVMOSP_Movable_Vehicles_move([String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = ""]) {
    if (OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD == "Movable.Vehicles.Car") {
        if (Movable_Vehicles_Car_fuel > 0) {
            print("The car is driving.");
            Movable_Vehicles_Car_fuel = Movable_Vehicles_Car_fuel - 10;
        } else {
            print("The car is out of fuel.");
            Movable_Vehicles_Car_hasFUEL = false;
        }
    }
    else if (OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD == "Movable.Vehicles.Bike") {
        if (Movable_Vehicles_Bike_energy > 0) {
            print("The bike is pedaling.");
            Movable_Vehicles_Bike_energy = Movable_Vehicles_Bike_energy - 5;
        } else {
            print("The bike is out of energy.");
            Movable_Vehicles_Bike_hasENERGY = false;
        }
    }
}
String Movable_settings_GeneralSettings_difficulty = "normal";
int Movable_settings_GeneralSettings_volume = 50;
String Movable_settings_GeneralSettings_resolution = "1920x1080";
int Movable_settings_AudioSettings_masterVolume = 70;
int Movable_settings_AudioSettings_musicVolume = 50;
int Movable_settings_AudioSettings_sfxVolume = 40;
bool Movable_settings_DisplaySettings_fullscreen = true;
String Movable_settings_DisplaySettings_aspectRatio = "16:9";
void OSPHTVMOSP_Movable_actions_resetGeneralSettings([String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = ""]) {
    Movable_settings_GeneralSettings_difficulty = STR("normal");
    Movable_settings_GeneralSettings_volume = 50;
    Movable_settings_GeneralSettings_resolution = STR("1920x1080");
    print("General settings reset to default.");
}
void OSPHTVMOSP_Movable_actions_printGeneralSettings([String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = ""]) {
    print("General Settings:");
    print("Difficulty: " + Movable_settings_GeneralSettings_difficulty);
    print("Volume: " + STR(Movable_settings_GeneralSettings_volume));
    print("Resolution: " + Movable_settings_GeneralSettings_resolution);
}
void OSPHTVMOSP_Movable_actions_resetAudioSettings([String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = ""]) {
    Movable_settings_AudioSettings_masterVolume = 70;
    Movable_settings_AudioSettings_musicVolume = 50;
    Movable_settings_AudioSettings_sfxVolume = 40;
    print("Audio settings reset to default.");
}
void OSPHTVMOSP_Movable_actions_printAudioSettings([String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = ""]) {
    print("Audio Settings:");
    print("Master Volume: " + STR(Movable_settings_AudioSettings_masterVolume));
    print("Music Volume: " + STR(Movable_settings_AudioSettings_musicVolume));
    print("SFX Volume: " + STR(Movable_settings_AudioSettings_sfxVolume));
}
void OSPHTVMOSP_Movable_actions_resetDisplaySettings([String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = ""]) {
    Movable_settings_DisplaySettings_fullscreen = true;
    Movable_settings_DisplaySettings_aspectRatio = STR("16:9");
    print("Display settings reset to default.");
}
void OSPHTVMOSP_Movable_actions_printDisplaySettings([String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = ""]) {
    print("Display Settings:");
    print("Fullscreen: " + STR(Movable_settings_DisplaySettings_fullscreen));
    print("Aspect Ratio: " + Movable_settings_DisplaySettings_aspectRatio);
}
List<String> Movable_array_name_prop1 = [];
List<String> Movable_array_name_prop2 = [];
List<String> Movable_array_name_prop3 = [];
List<String> Movable_array_name_prop4 = [];
void main(List<String> arguments) {
    // Test vehicle movement
    while (Movable_Vehicles_Car_hasFUEL == true && Movable_Vehicles_Bike_hasENERGY == true) {
        OSPHTVMOSP_Movable_Vehicles_move("Movable.Vehicles.Car");
        OSPHTVMOSP_Movable_Vehicles_move("Movable.Vehicles.Bike");
        print("=====================================");
    }
    // Test settings manipulation
    Movable_settings_GeneralSettings_difficulty = STR("hard");
    Movable_settings_GeneralSettings_volume = 80;
    Movable_settings_GeneralSettings_resolution = STR("2560x1440");
    Movable_settings_AudioSettings_masterVolume = 90;
    Movable_settings_AudioSettings_musicVolume = 60;
    Movable_settings_AudioSettings_sfxVolume = 50;
    Movable_settings_DisplaySettings_fullscreen = false;
    Movable_settings_DisplaySettings_aspectRatio = STR("21:9");
    OSPHTVMOSP_Movable_actions_printGeneralSettings();
    OSPHTVMOSP_Movable_actions_printAudioSettings();
    OSPHTVMOSP_Movable_actions_printDisplaySettings();
    OSPHTVMOSP_Movable_actions_resetGeneralSettings();
    OSPHTVMOSP_Movable_actions_resetAudioSettings();
    OSPHTVMOSP_Movable_actions_resetDisplaySettings();
    OSPHTVMOSP_Movable_actions_printGeneralSettings();
    OSPHTVMOSP_Movable_actions_printAudioSettings();
    OSPHTVMOSP_Movable_actions_printDisplaySettings();
    // Test array manipulation
    HTVM_Append(Movable_array_name_prop1, "1text1");
    HTVM_Append(Movable_array_name_prop1, "1text2");
    HTVM_Append(Movable_array_name_prop1, "1text3");
    HTVM_Append(Movable_array_name_prop2, "2text1");
    HTVM_Append(Movable_array_name_prop2, "2text2");
    HTVM_Append(Movable_array_name_prop2, "2text3");
    HTVM_Append(Movable_array_name_prop3, "3text1");
    HTVM_Append(Movable_array_name_prop3, "3text2");
    HTVM_Append(Movable_array_name_prop3, "3text3");
    HTVM_Append(Movable_array_name_prop4, "4text1");
    HTVM_Append(Movable_array_name_prop4, "4text2");
    HTVM_Append(Movable_array_name_prop4, "4text3");
    for (int A_Index1 = 0; A_Index1 < HTVM_Size(Movable_array_name_prop1) + 0; A_Index1++) {
        print(Movable_array_name_prop1[A_Index1]);
    }
    for (int A_Index2 = 0; A_Index2 < HTVM_Size(Movable_array_name_prop2) + 0; A_Index2++) {
        print(Movable_array_name_prop2[A_Index2]);
    }
    for (int A_Index3 = 0; A_Index3 < HTVM_Size(Movable_array_name_prop3) + 0; A_Index3++) {
        print(Movable_array_name_prop3[A_Index3]);
    }
    for (int A_Index4 = 0; A_Index4 < HTVM_Size(Movable_array_name_prop4) + 0; A_Index4++) {
        print(Movable_array_name_prop4[A_Index4]);
    }
}
