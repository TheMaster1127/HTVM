

function print(value) {
    console.log(value)
}

// Convert value to string
function STR(value) {
    if (typeof value === 'number') {
        return value.toString();
    } else if (typeof value === 'boolean') {
        return value ? "1" : "0";
    } else if (typeof value === 'string') {
        return value; // Return the string as is
    } else {
        throw new TypeError("Unsupported type");
    }
}


// This is a preview of my language and how it looks like.
//OSP
let OSPHTVMOSP_Movable_Vehicles_Car = [
"Movable.Vehicles.Car",
4,
100,
true,
]
let OSPHTVMOSP_Movable_Vehicles_Bike = [
"Movable.Vehicles.Bike",
true,
100,
true,
]
async function OSPHTVMOSP_Movable_Vehicles_move(this__OSP__this = null) {
    if (this__OSP__this[0] == "Movable.Vehicles.Car") {
        if (OSPHTVMOSP_Movable_Vehicles_Car[2] > 0) {
            print("The car is driving.");
            OSPHTVMOSP_Movable_Vehicles_Car[2] = OSPHTVMOSP_Movable_Vehicles_Car[2] - 10;
        } else {
            print("The car is out of fuel.");
            OSPHTVMOSP_Movable_Vehicles_Car[3] = false;
        }
    }
    else if (this__OSP__this[0] == "Movable.Vehicles.Bike") {
        if (OSPHTVMOSP_Movable_Vehicles_Bike[2] > 0) {
            print("The bike is pedaling.");
            OSPHTVMOSP_Movable_Vehicles_Bike[2] = OSPHTVMOSP_Movable_Vehicles_Bike[2] - 5;
        } else {
            print("The bike is out of energy.");
            OSPHTVMOSP_Movable_Vehicles_Bike[3] = false;
        }
    }
}
let OSPHTVMOSP_Movable_settings_GeneralSettings = [
"Movable.settings.GeneralSettings",
"normal",
50,
"1920x1080",
]
let OSPHTVMOSP_Movable_settings_AudioSettings = [
"Movable.settings.AudioSettings",
70,
50,
40,
]
let OSPHTVMOSP_Movable_settings_DisplaySettings = [
"Movable.settings.DisplaySettings",
true,
"16:9",
]
// General Settings Methods
async function OSPHTVMOSP_Movable_actions_resetGeneralSettings(this__OSP__this = null) {
    OSPHTVMOSP_Movable_settings_GeneralSettings[1] = STR("normal");
    OSPHTVMOSP_Movable_settings_GeneralSettings[2] = 50;
    OSPHTVMOSP_Movable_settings_GeneralSettings[3] = STR("1920x1080");
    print("General settings reset to default.");
}
async function OSPHTVMOSP_Movable_actions_printGeneralSettings(this__OSP__this = null) {
    print("General Settings:");
    print("Difficulty: " + OSPHTVMOSP_Movable_settings_GeneralSettings[1]);
    print("Volume: " + STR(OSPHTVMOSP_Movable_settings_GeneralSettings[2]));
    print("Resolution: " + OSPHTVMOSP_Movable_settings_GeneralSettings[3]);
}
// Audio Settings Methods
async function OSPHTVMOSP_Movable_actions_resetAudioSettings(this__OSP__this = null) {
    OSPHTVMOSP_Movable_settings_AudioSettings[1] = 70;
    OSPHTVMOSP_Movable_settings_AudioSettings[2] = 50;
    OSPHTVMOSP_Movable_settings_AudioSettings[3] = 40;
    print("Audio settings reset to default.");
}
async function OSPHTVMOSP_Movable_actions_printAudioSettings(this__OSP__this = null) {
    print("Audio Settings:");
    print("Master Volume: " + STR(OSPHTVMOSP_Movable_settings_AudioSettings[1]));
    print("Music Volume: " + STR(OSPHTVMOSP_Movable_settings_AudioSettings[2]));
    print("SFX Volume: " + STR(OSPHTVMOSP_Movable_settings_AudioSettings[3]));
}
// Display Settings Methods
async function OSPHTVMOSP_Movable_actions_resetDisplaySettings(this__OSP__this = null) {
    OSPHTVMOSP_Movable_settings_DisplaySettings[1] = true;
    OSPHTVMOSP_Movable_settings_DisplaySettings[2] = STR("16:9");
    print("Display settings reset to default.");
}
async function OSPHTVMOSP_Movable_actions_printDisplaySettings(this__OSP__this = null) {
    print("Display Settings:");
    print("Fullscreen: " + STR(OSPHTVMOSP_Movable_settings_DisplaySettings[1]));
    print("Aspect Ratio: " + OSPHTVMOSP_Movable_settings_DisplaySettings[2]);
}
let temp = [];
let OSPHTVMOSP_Movable_array_name = [
"Movable.array.name",
temp,
temp,
temp,
temp,
]
async function main() {
    // Test vehicle movement
    while (OSPHTVMOSP_Movable_Vehicles_Car[3] == true && OSPHTVMOSP_Movable_Vehicles_Bike[3] == true) {
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
    OSPHTVMOSP_Movable_array_name[1].push("1text1");
    OSPHTVMOSP_Movable_array_name[1].push("1text2");
    OSPHTVMOSP_Movable_array_name[1].push("1text3");
    OSPHTVMOSP_Movable_array_name[2].push("2text1");
    OSPHTVMOSP_Movable_array_name[2].push("2text2");
    OSPHTVMOSP_Movable_array_name[2].push("2text3");
    OSPHTVMOSP_Movable_array_name[3].push("3text1");
    OSPHTVMOSP_Movable_array_name[3].push("3text2");
    OSPHTVMOSP_Movable_array_name[3].push("3text3");
    OSPHTVMOSP_Movable_array_name[4].push("4text1");
    OSPHTVMOSP_Movable_array_name[4].push("4text2");
    OSPHTVMOSP_Movable_array_name[4].push("4text3");
    // why this__OSP__this[0]
    // cuz python used len(param) insed of param.len() so it meses up evrything
    // if using OSP objects that have a dot (.) it doset work in python to get the lenght
    // but for a name whit no dots it works
    let arrayTempOnlyGetSize1 = OSPHTVMOSP_Movable_array_name[1];
    let arrayTempOnlyGetSize2 = OSPHTVMOSP_Movable_array_name[2];
    let arrayTempOnlyGetSize3 = OSPHTVMOSP_Movable_array_name[3];
    let arrayTempOnlyGetSize4 = OSPHTVMOSP_Movable_array_name[4];
    for (let A_Index1 = 0; A_Index1 < arrayTempOnlyGetSize1.length + 0; A_Index1++) {
        print(OSPHTVMOSP_Movable_array_name[1][A_Index1]);
    }
    for (let A_Index2 = 0; A_Index2 < arrayTempOnlyGetSize2.length + 0; A_Index2++) {
        print(OSPHTVMOSP_Movable_array_name[2][A_Index2]);
    }
    for (let A_Index3 = 0; A_Index3 < arrayTempOnlyGetSize3.length + 0; A_Index3++) {
        print(OSPHTVMOSP_Movable_array_name[3][A_Index3]);
    }
    for (let A_Index4 = 0; A_Index4 < arrayTempOnlyGetSize4.length + 0; A_Index4++) {
        print(OSPHTVMOSP_Movable_array_name[4][A_Index4]);
    }
}
main();