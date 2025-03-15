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
    std::cout << value << std::endl;
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

void HTVM_Append(std::vector<std::string>& arr, const std::string& value) {
    arr.push_back(value);
}
void HTVM_Append(std::vector<std::string>& arr, const char* value) {
    arr.push_back(std::string(value));
}
void HTVM_Append(std::vector<int>& arr, int value) {
    arr.push_back(value);
}
void HTVM_Append(std::vector<float>& arr, float value) {
    arr.push_back(value);
}
void HTVM_Append(std::vector<bool>& arr, bool value) {
    arr.push_back(value);
}

size_t HTVM_Size(const std::vector<std::string>& arr) {
    return arr.size();
}
size_t HTVM_Size(const std::vector<int>& arr) {
    return arr.size();
}
size_t HTVM_Size(const std::vector<float>& arr) {
    return arr.size();
}
size_t HTVM_Size(const std::vector<bool>& arr) {
    return arr.size();
}


int Movable_Vehicles_Car_door = 4;
int Movable_Vehicles_Car_fuel = 100;
bool Movable_Vehicles_Car_hasFUEL = true;
bool Movable_Vehicles_Bike_hasGears = true;
int Movable_Vehicles_Bike_energy = 100;
bool Movable_Vehicles_Bike_hasENERGY = true;
void OSPHTVMOSP_Movable_Vehicles_move(std::string OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "") {
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
std::string Movable_settings_GeneralSettings_difficulty = "normal";
int Movable_settings_GeneralSettings_volume = 50;
std::string Movable_settings_GeneralSettings_resolution = "1920x1080";
int Movable_settings_AudioSettings_masterVolume = 70;
int Movable_settings_AudioSettings_musicVolume = 50;
int Movable_settings_AudioSettings_sfxVolume = 40;
bool Movable_settings_DisplaySettings_fullscreen = true;
std::string Movable_settings_DisplaySettings_aspectRatio = "16:9";
void OSPHTVMOSP_Movable_actions_resetGeneralSettings(std::string OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "") {
    Movable_settings_GeneralSettings_difficulty = STR("normal");
    Movable_settings_GeneralSettings_volume = 50;
    Movable_settings_GeneralSettings_resolution = STR("1920x1080");
    print("General settings reset to default.");
}
void OSPHTVMOSP_Movable_actions_printGeneralSettings(std::string OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "") {
    print("General Settings:");
    print("Difficulty: " + Movable_settings_GeneralSettings_difficulty);
    print("Volume: " + STR(Movable_settings_GeneralSettings_volume));
    print("Resolution: " + Movable_settings_GeneralSettings_resolution);
}
void OSPHTVMOSP_Movable_actions_resetAudioSettings(std::string OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "") {
    Movable_settings_AudioSettings_masterVolume = 70;
    Movable_settings_AudioSettings_musicVolume = 50;
    Movable_settings_AudioSettings_sfxVolume = 40;
    print("Audio settings reset to default.");
}
void OSPHTVMOSP_Movable_actions_printAudioSettings(std::string OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "") {
    print("Audio Settings:");
    print("Master Volume: " + STR(Movable_settings_AudioSettings_masterVolume));
    print("Music Volume: " + STR(Movable_settings_AudioSettings_musicVolume));
    print("SFX Volume: " + STR(Movable_settings_AudioSettings_sfxVolume));
}
void OSPHTVMOSP_Movable_actions_resetDisplaySettings(std::string OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "") {
    Movable_settings_DisplaySettings_fullscreen = true;
    Movable_settings_DisplaySettings_aspectRatio = STR("16:9");
    print("Display settings reset to default.");
}
void OSPHTVMOSP_Movable_actions_printDisplaySettings(std::string OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "") {
    print("Display Settings:");
    print("Fullscreen: " + STR(Movable_settings_DisplaySettings_fullscreen));
    print("Aspect Ratio: " + Movable_settings_DisplaySettings_aspectRatio);
}
std::vector<std::string> Movable_array_name_prop1;
std::vector<std::string> Movable_array_name_prop2;
std::vector<std::string> Movable_array_name_prop3;
std::vector<std::string> Movable_array_name_prop4;
int main(int argc, char* argv[]) {
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
    return 0;
}
