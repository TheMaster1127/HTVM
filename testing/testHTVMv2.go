package main
import (
"fmt"
"strconv"
)

func print(value interface{}) {
    fmt.Println(value)
}

func STR(value interface{}) string {
    switch v := value.(type) {
    case int:
        return strconv.Itoa(v)
    case int64:
        return strconv.FormatInt(v, 10)
    case float64:
        return fmt.Sprintf("%f", v)
    case bool:
        if v {
            return "1"
        } else {
            return "0"
        }
    case string:
        return v
    default:
        return fmt.Sprintf("%v", v)
    }
}

// Append to a slice
func HTVM_Append[T any](arr *[]T, value T) {
    *arr = append(*arr, value)
}

// Get the size of a slice
func HTVM_Size[T any](arr []T) int {
    return len(arr)
}


var Movable_Vehicles_Car_door int = 4
var Movable_Vehicles_Car_fuel int = 100
var Movable_Vehicles_Car_hasFUEL bool = true
var Movable_Vehicles_Bike_hasGears bool = true
var Movable_Vehicles_Bike_energy int = 100
var Movable_Vehicles_Bike_hasENERGY bool = true
func OSPHTVMOSP_Movable_Vehicles_move(__HTVM_V2_TO_GO_optionalParams__ ...interface{}) {
    OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD := ""
    if len(__HTVM_V2_TO_GO_optionalParams__) > 0 {
        OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = __HTVM_V2_TO_GO_optionalParams__[0].(string)
    }
    if (OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD == "Movable.Vehicles.Car") {
        if (Movable_Vehicles_Car_fuel > 0) {
            print("The car is driving.")
            Movable_Vehicles_Car_fuel = Movable_Vehicles_Car_fuel - 10
        } else {
            print("The car is out of fuel.")
            Movable_Vehicles_Car_hasFUEL = false
        }
    } else if (OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD == "Movable.Vehicles.Bike") {
        if (Movable_Vehicles_Bike_energy > 0) {
            print("The bike is pedaling.")
            Movable_Vehicles_Bike_energy = Movable_Vehicles_Bike_energy - 5
        } else {
            print("The bike is out of energy.")
            Movable_Vehicles_Bike_hasENERGY = false
        }
    }
}
var Movable_settings_GeneralSettings_difficulty string = "normal"
var Movable_settings_GeneralSettings_volume int = 50
var Movable_settings_GeneralSettings_resolution string = "1920x1080"
var Movable_settings_AudioSettings_masterVolume int = 70
var Movable_settings_AudioSettings_musicVolume int = 50
var Movable_settings_AudioSettings_sfxVolume int = 40
var Movable_settings_DisplaySettings_fullscreen bool = true
var Movable_settings_DisplaySettings_aspectRatio string = "16:9"
func OSPHTVMOSP_Movable_actions_resetGeneralSettings(__HTVM_V2_TO_GO_optionalParams__ ...interface{}) {
    OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD := ""
    if len(__HTVM_V2_TO_GO_optionalParams__) > 0 {
        OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = __HTVM_V2_TO_GO_optionalParams__[0].(string)
    }
    Movable_settings_GeneralSettings_difficulty = STR("normal")
    Movable_settings_GeneralSettings_volume = 50
    Movable_settings_GeneralSettings_resolution = STR("1920x1080")
    print("General settings reset to default.")
}
func OSPHTVMOSP_Movable_actions_printGeneralSettings(__HTVM_V2_TO_GO_optionalParams__ ...interface{}) {
    OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD := ""
    if len(__HTVM_V2_TO_GO_optionalParams__) > 0 {
        OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = __HTVM_V2_TO_GO_optionalParams__[0].(string)
    }
    print("General Settings:")
    print("Difficulty: " + Movable_settings_GeneralSettings_difficulty)
    print("Volume: " + STR(Movable_settings_GeneralSettings_volume))
    print("Resolution: " + Movable_settings_GeneralSettings_resolution)
}
func OSPHTVMOSP_Movable_actions_resetAudioSettings(__HTVM_V2_TO_GO_optionalParams__ ...interface{}) {
    OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD := ""
    if len(__HTVM_V2_TO_GO_optionalParams__) > 0 {
        OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = __HTVM_V2_TO_GO_optionalParams__[0].(string)
    }
    Movable_settings_AudioSettings_masterVolume = 70
    Movable_settings_AudioSettings_musicVolume = 50
    Movable_settings_AudioSettings_sfxVolume = 40
    print("Audio settings reset to default.")
}
func OSPHTVMOSP_Movable_actions_printAudioSettings(__HTVM_V2_TO_GO_optionalParams__ ...interface{}) {
    OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD := ""
    if len(__HTVM_V2_TO_GO_optionalParams__) > 0 {
        OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = __HTVM_V2_TO_GO_optionalParams__[0].(string)
    }
    print("Audio Settings:")
    print("Master Volume: " + STR(Movable_settings_AudioSettings_masterVolume))
    print("Music Volume: " + STR(Movable_settings_AudioSettings_musicVolume))
    print("SFX Volume: " + STR(Movable_settings_AudioSettings_sfxVolume))
}
func OSPHTVMOSP_Movable_actions_resetDisplaySettings(__HTVM_V2_TO_GO_optionalParams__ ...interface{}) {
    OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD := ""
    if len(__HTVM_V2_TO_GO_optionalParams__) > 0 {
        OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = __HTVM_V2_TO_GO_optionalParams__[0].(string)
    }
    Movable_settings_DisplaySettings_fullscreen = true
    Movable_settings_DisplaySettings_aspectRatio = STR("16:9")
    print("Display settings reset to default.")
}
func OSPHTVMOSP_Movable_actions_printDisplaySettings(__HTVM_V2_TO_GO_optionalParams__ ...interface{}) {
    OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD := ""
    if len(__HTVM_V2_TO_GO_optionalParams__) > 0 {
        OSP_OSP_THIS_KEYWORD_HTVM_OSP_THIS_HTVM_KEYWORD = __HTVM_V2_TO_GO_optionalParams__[0].(string)
    }
    print("Display Settings:")
    print("Fullscreen: " + STR(Movable_settings_DisplaySettings_fullscreen))
    print("Aspect Ratio: " + Movable_settings_DisplaySettings_aspectRatio)
}
var Movable_array_name_prop1 []string
var Movable_array_name_prop2 []string
var Movable_array_name_prop3 []string
var Movable_array_name_prop4 []string
func main() {
    // Test vehicle movement
    for (Movable_Vehicles_Car_hasFUEL == true && Movable_Vehicles_Bike_hasENERGY == true) {
        OSPHTVMOSP_Movable_Vehicles_move("Movable.Vehicles.Car")
        OSPHTVMOSP_Movable_Vehicles_move("Movable.Vehicles.Bike")
        print("=====================================")
    }
    // Test settings manipulation
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
    // Test array manipulation
    HTVM_Append(&Movable_array_name_prop1, "1text1")
    HTVM_Append(&Movable_array_name_prop1, "1text2")
    HTVM_Append(&Movable_array_name_prop1, "1text3")
    HTVM_Append(&Movable_array_name_prop2, "2text1")
    HTVM_Append(&Movable_array_name_prop2, "2text2")
    HTVM_Append(&Movable_array_name_prop2, "2text3")
    HTVM_Append(&Movable_array_name_prop3, "3text1")
    HTVM_Append(&Movable_array_name_prop3, "3text2")
    HTVM_Append(&Movable_array_name_prop3, "3text3")
    HTVM_Append(&Movable_array_name_prop4, "4text1")
    HTVM_Append(&Movable_array_name_prop4, "4text2")
    HTVM_Append(&Movable_array_name_prop4, "4text3")
    for A_Index1 := 0; A_Index1 < HTVM_Size(Movable_array_name_prop1) + 0; A_Index1++ {
        print(Movable_array_name_prop1[A_Index1])
    }
    for A_Index2 := 0; A_Index2 < HTVM_Size(Movable_array_name_prop2) + 0; A_Index2++ {
        print(Movable_array_name_prop2[A_Index2])
    }
    for A_Index3 := 0; A_Index3 < HTVM_Size(Movable_array_name_prop3) + 0; A_Index3++ {
        print(Movable_array_name_prop3[A_Index3])
    }
    for A_Index4 := 0; A_Index4 < HTVM_Size(Movable_array_name_prop4) + 0; A_Index4++ {
        print(Movable_array_name_prop4[A_Index4])
    }
}
