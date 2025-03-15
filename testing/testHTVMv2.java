import java.util.ArrayList;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;
import java.util.*;
public class Main
{


// Print function for various types
    public static void print(Object value) {
        System.out.println(value);
    }

public static String STR(Object value) {
    if (value instanceof Integer) {
        return value.toString();
    } else if (value instanceof Long) {
        return value.toString();
    } else if (value instanceof Float) {
        return value.toString();
    } else if (value instanceof Double) {
        return value.toString();
    } else if (value instanceof Boolean) {
        return (Boolean) value ? "1" : "0";
    } else if (value instanceof String) {
        return (String) value;
    } else {
        return value.toString();
    }
}

public static <T> void HTVM_Append(ArrayList<T> arr, T value) {
    arr.add(value);
}

public static <T> int HTVM_Size(ArrayList<T> arr) {
    return arr.size();
}


static int Movable_Vehicles_Car_door = 4;
static int Movable_Vehicles_Car_fuel = 100;
static boolean Movable_Vehicles_Car_hasFUEL = true;
static boolean Movable_Vehicles_Bike_hasGears = true;
static int Movable_Vehicles_Bike_energy = 100;
static boolean Movable_Vehicles_Bike_hasENERGY = true;
public static void OSPHTVMOSP_Movable_Vehicles_move(Object... __HTVM_V2_TO_JAVA_optionalParams__) {
    String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "";
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
static String Movable_settings_GeneralSettings_difficulty = "normal";
static int Movable_settings_GeneralSettings_volume = 50;
static String Movable_settings_GeneralSettings_resolution = "1920x1080";
static int Movable_settings_AudioSettings_masterVolume = 70;
static int Movable_settings_AudioSettings_musicVolume = 50;
static int Movable_settings_AudioSettings_sfxVolume = 40;
static boolean Movable_settings_DisplaySettings_fullscreen = true;
static String Movable_settings_DisplaySettings_aspectRatio = "16:9";
public static void OSPHTVMOSP_Movable_actions_resetGeneralSettings(Object... __HTVM_V2_TO_JAVA_optionalParams__) {
    String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "";
    Movable_settings_GeneralSettings_difficulty = STR("normal");
    Movable_settings_GeneralSettings_volume = 50;
    Movable_settings_GeneralSettings_resolution = STR("1920x1080");
    print("General settings reset to default.");
}
public static void OSPHTVMOSP_Movable_actions_printGeneralSettings(Object... __HTVM_V2_TO_JAVA_optionalParams__) {
    String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "";
    print("General Settings:");
    print("Difficulty: " + Movable_settings_GeneralSettings_difficulty);
    print("Volume: " + STR(Movable_settings_GeneralSettings_volume));
    print("Resolution: " + Movable_settings_GeneralSettings_resolution);
}
public static void OSPHTVMOSP_Movable_actions_resetAudioSettings(Object... __HTVM_V2_TO_JAVA_optionalParams__) {
    String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "";
    Movable_settings_AudioSettings_masterVolume = 70;
    Movable_settings_AudioSettings_musicVolume = 50;
    Movable_settings_AudioSettings_sfxVolume = 40;
    print("Audio settings reset to default.");
}
public static void OSPHTVMOSP_Movable_actions_printAudioSettings(Object... __HTVM_V2_TO_JAVA_optionalParams__) {
    String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "";
    print("Audio Settings:");
    print("Master Volume: " + STR(Movable_settings_AudioSettings_masterVolume));
    print("Music Volume: " + STR(Movable_settings_AudioSettings_musicVolume));
    print("SFX Volume: " + STR(Movable_settings_AudioSettings_sfxVolume));
}
public static void OSPHTVMOSP_Movable_actions_resetDisplaySettings(Object... __HTVM_V2_TO_JAVA_optionalParams__) {
    String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "";
    Movable_settings_DisplaySettings_fullscreen = true;
    Movable_settings_DisplaySettings_aspectRatio = STR("16:9");
    print("Display settings reset to default.");
}
public static void OSPHTVMOSP_Movable_actions_printDisplaySettings(Object... __HTVM_V2_TO_JAVA_optionalParams__) {
    String OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = "";
    print("Display Settings:");
    print("Fullscreen: " + STR(Movable_settings_DisplaySettings_fullscreen));
    print("Aspect Ratio: " + Movable_settings_DisplaySettings_aspectRatio);
}
static ArrayList<String> Movable_array_name_prop1 = new ArrayList<>();
static ArrayList<String> Movable_array_name_prop2 = new ArrayList<>();
static ArrayList<String> Movable_array_name_prop3 = new ArrayList<>();
static ArrayList<String> Movable_array_name_prop4 = new ArrayList<>();
public static void main(String[] args) {
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
        print(Movable_array_name_prop1.get(A_Index1));
    }
    for (int A_Index2 = 0; A_Index2 < HTVM_Size(Movable_array_name_prop2) + 0; A_Index2++) {
        print(Movable_array_name_prop2.get(A_Index2));
    }
    for (int A_Index3 = 0; A_Index3 < HTVM_Size(Movable_array_name_prop3) + 0; A_Index3++) {
        print(Movable_array_name_prop3.get(A_Index3));
    }
    for (int A_Index4 = 0; A_Index4 < HTVM_Size(Movable_array_name_prop4) + 0; A_Index4++) {
        print(Movable_array_name_prop4.get(A_Index4));
    }

}
}
