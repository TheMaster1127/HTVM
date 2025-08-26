#include <algorithm>
#include <any>
#include <cstdint>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

// Print function for const char* specifically
void print(const char* value) {
    std::cout << std::string(value) << std::endl;  // Convert const char* to std::string
}
// Print function that converts all types to string if needed
template <typename T>
void print(const T& value) {
    if constexpr (std::is_same_v<T, std::string>) {
        std::cout << value << std::endl;
    } else if constexpr (std::is_same_v<T, char>) {
        std::cout << value << std::endl;
    } else if constexpr (std::is_same_v<T, int>) {
        std::cout << std::to_string(value) << std::endl;
    } else if constexpr (std::is_same_v<T, float>) {
        std::cout << std::to_string(value) << std::endl;
    } else if constexpr (std::is_same_v<T, double>) {
        std::cout << std::to_string(value) << std::endl;
    } else if constexpr (std::is_same_v<T, size_t>) {
        std::cout << std::to_string(value) << std::endl;
    } else if constexpr (std::is_same_v<T, bool>) {
        std::cout << (value ? "1" : "0") << std::endl;
    } else {
        std::cout << "Unsupported type" << std::endl;
    }
}

// Convert various types to std::string
std::string STR(int value) {
    return std::to_string(value);
}
// Convert various types to std::string
std::string STR(long long value) {
    return std::to_string(value);
}
std::string STR(float value) {
    return std::to_string(value);
}
std::string STR(double value) {
    return std::to_string(value);
}
std::string STR(size_t value) {
    return std::to_string(value);
}
std::string STR(bool value) {
    return value ? "1" : "0";
}
std::string STR(const char* value) {
    return std::string(value);
}


// This is a preview of my language and how it looks like.
//OSP
std::vector<std::any> OSPHTVMOSP_Movable_Vehicles_Car = {
std::string("Movable.Vehicles.Car"),
4,
100,
true,
};
std::vector<std::any> OSPHTVMOSP_Movable_Vehicles_Bike = {
std::string("Movable.Vehicles.Bike"),
true,
100,
true,
};
void OSPHTVMOSP_Movable_Vehicles_move(std::optional<std::vector<std::any>> this__OSP__this = std::nullopt) {
    if (std::any_cast<std::string>((*this__OSP__this)[0]) == "Movable.Vehicles.Car") {
        if (std::any_cast<int>(OSPHTVMOSP_Movable_Vehicles_Car[2]) > 0) {
            print("The car is driving.");
            OSPHTVMOSP_Movable_Vehicles_Car[2] = std::any_cast<int>(OSPHTVMOSP_Movable_Vehicles_Car[2]) - 10;
        } else {
            print("The car is out of fuel.");
            OSPHTVMOSP_Movable_Vehicles_Car[3] = false;
        }
    }
    else if (std::any_cast<std::string>((*this__OSP__this)[0]) == "Movable.Vehicles.Bike") {
        if (std::any_cast<int>(OSPHTVMOSP_Movable_Vehicles_Bike[2]) > 0) {
            print("The bike is pedaling.");
            OSPHTVMOSP_Movable_Vehicles_Bike[2] = std::any_cast<int>(OSPHTVMOSP_Movable_Vehicles_Bike[2]) - 5;
        } else {
            print("The bike is out of energy.");
            OSPHTVMOSP_Movable_Vehicles_Bike[3] = false;
        }
    }
}
std::vector<std::any> OSPHTVMOSP_Movable_settings_GeneralSettings = {
std::string("Movable.settings.GeneralSettings"),
std::string("normal"),
50,
std::string("1920x1080"),
};
std::vector<std::any> OSPHTVMOSP_Movable_settings_AudioSettings = {
std::string("Movable.settings.AudioSettings"),
70,
50,
40,
};
std::vector<std::any> OSPHTVMOSP_Movable_settings_DisplaySettings = {
std::string("Movable.settings.DisplaySettings"),
true,
std::string("16:9"),
};
// General Settings Methods
void OSPHTVMOSP_Movable_actions_resetGeneralSettings(std::optional<std::vector<std::any>> this__OSP__this = std::nullopt) {
    OSPHTVMOSP_Movable_settings_GeneralSettings[1] = STR("normal");
    OSPHTVMOSP_Movable_settings_GeneralSettings[2] = 50;
    OSPHTVMOSP_Movable_settings_GeneralSettings[3] = STR("1920x1080");
    print("General settings reset to default.");
}
void OSPHTVMOSP_Movable_actions_printGeneralSettings(std::optional<std::vector<std::any>> this__OSP__this = std::nullopt) {
    print("General Settings:");
    print("Difficulty: " + std::any_cast<std::string>(OSPHTVMOSP_Movable_settings_GeneralSettings[1]));
    print("Volume: " + STR(std::any_cast<int>(OSPHTVMOSP_Movable_settings_GeneralSettings[2])));
    print("Resolution: " + std::any_cast<std::string>(OSPHTVMOSP_Movable_settings_GeneralSettings[3]));
}
// Audio Settings Methods
void OSPHTVMOSP_Movable_actions_resetAudioSettings(std::optional<std::vector<std::any>> this__OSP__this = std::nullopt) {
    OSPHTVMOSP_Movable_settings_AudioSettings[1] = 70;
    OSPHTVMOSP_Movable_settings_AudioSettings[2] = 50;
    OSPHTVMOSP_Movable_settings_AudioSettings[3] = 40;
    print("Audio settings reset to default.");
}
void OSPHTVMOSP_Movable_actions_printAudioSettings(std::optional<std::vector<std::any>> this__OSP__this = std::nullopt) {
    print("Audio Settings:");
    print("Master Volume: " + STR(std::any_cast<int>(OSPHTVMOSP_Movable_settings_AudioSettings[1])));
    print("Music Volume: " + STR(std::any_cast<int>(OSPHTVMOSP_Movable_settings_AudioSettings[2])));
    print("SFX Volume: " + STR(std::any_cast<int>(OSPHTVMOSP_Movable_settings_AudioSettings[3])));
}
// Display Settings Methods
void OSPHTVMOSP_Movable_actions_resetDisplaySettings(std::optional<std::vector<std::any>> this__OSP__this = std::nullopt) {
    OSPHTVMOSP_Movable_settings_DisplaySettings[1] = true;
    OSPHTVMOSP_Movable_settings_DisplaySettings[2] = STR("16:9");
    print("Display settings reset to default.");
}
void OSPHTVMOSP_Movable_actions_printDisplaySettings(std::optional<std::vector<std::any>> this__OSP__this = std::nullopt) {
    print("Display Settings:");
    print("Fullscreen: " + STR(std::any_cast<bool>(OSPHTVMOSP_Movable_settings_DisplaySettings[1])));
    print("Aspect Ratio: " + std::any_cast<std::string>(OSPHTVMOSP_Movable_settings_DisplaySettings[2]));
}
std::vector<std::string> temp;
std::vector<std::any> OSPHTVMOSP_Movable_array_name = {
std::string("Movable.array.name"),
temp,
temp,
temp,
temp,
};
int main(int argc, char* argv[]) {
    // Test vehicle movement
    while (std::any_cast<bool>(OSPHTVMOSP_Movable_Vehicles_Car[3]) == true && std::any_cast<bool>(OSPHTVMOSP_Movable_Vehicles_Bike[3]) == true) {
        OSPHTVMOSP_Movable_Vehicles_move(OSPHTVMOSP_Movable_Vehicles_Car);
        OSPHTVMOSP_Movable_Vehicles_move(OSPHTVMOSP_Movable_Vehicles_Bike);
        print("=====================================");
    }
    // Test settings manipulation
    OSPHTVMOSP_Movable_settings_GeneralSettings[1] = STR("hard");
    OSPHTVMOSP_Movable_settings_GeneralSettings[2] = 80;
    OSPHTVMOSP_Movable_settings_GeneralSettings[3] = STR("2560x1440");
    OSPHTVMOSP_Movable_settings_AudioSettings[1] = 90;
    OSPHTVMOSP_Movable_settings_AudioSettings[2] = 60;
    OSPHTVMOSP_Movable_settings_AudioSettings[3] = 50;
    OSPHTVMOSP_Movable_settings_DisplaySettings[1] = false;
    OSPHTVMOSP_Movable_settings_DisplaySettings[2] = STR("21:9");
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
    std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[1]).push_back("1text1");
    std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[1]).push_back("1text2");
    std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[1]).push_back("1text3");
    std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[2]).push_back("2text1");
    std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[2]).push_back("2text2");
    std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[2]).push_back("2text3");
    std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[3]).push_back("3text1");
    std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[3]).push_back("3text2");
    std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[3]).push_back("3text3");
    std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[4]).push_back("4text1");
    std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[4]).push_back("4text2");
    std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[4]).push_back("4text3");
    // why std::any_cast<std::string>((*this__OSP__this)[0])
    // cuz python used len(param) insed of param.len() so it meses up evrything
    // if using OSP objects that have a dot (.) it doset work in python to get the lenght
    // but for a name whit no dots it works
    std::vector<std::string> arrayTempOnlyGetSize1 = std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[1]);
    std::vector<std::string> arrayTempOnlyGetSize2 = std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[2]);
    std::vector<std::string> arrayTempOnlyGetSize3 = std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[3]);
    std::vector<std::string> arrayTempOnlyGetSize4 = std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[4]);
    for (int A_Index1 = 0; A_Index1 < arrayTempOnlyGetSize1.size() + 0; A_Index1++) {
        print(std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[1])[A_Index1]);
    }
    for (int A_Index2 = 0; A_Index2 < arrayTempOnlyGetSize2.size() + 0; A_Index2++) {
        print(std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[2])[A_Index2]);
    }
    for (int A_Index3 = 0; A_Index3 < arrayTempOnlyGetSize3.size() + 0; A_Index3++) {
        print(std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[3])[A_Index3]);
    }
    for (int A_Index4 = 0; A_Index4 < arrayTempOnlyGetSize4.size() + 0; A_Index4++) {
        print(std::any_cast<std::vector<std::string>&>(OSPHTVMOSP_Movable_array_name[4])[A_Index4]);
    }
    return 0;
}