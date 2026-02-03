

function print(value) {
    console.log(value)
}

// Convert value to string
function STR(value) {
    if (value === null || value === undefined) {
        return ""; // Return a string for null or undefined
    } else if (typeof value === 'number') {
        return value.toString();
    } else if (typeof value === 'boolean') {
        return value ? "1" : "0";
    } else if (typeof value === 'string') {
        return value; // Return the string as is
    } else {
        // Handle any unexpected types gracefully
        return String(value); // Convert any other type to a string
    }
}


var Player_health = 100;
var Player_mana = 50;
async function main() {
    hero_health = 200;
    goblin_health = 30;
    print("Hero health: " + STR(hero_health));
    print("Goblin health: " + STR(goblin_health));
    

}
main();