

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


var Enemy_health = 50;
var Enemy_damage = 10;
var goblin1_health = 50;
var goblin1_damage = 10;
var goblin2_health = 50;
var goblin2_damage = 10;
var goblin3_health = 50;
var goblin3_damage = 10;
async function main() {
    goblin1_health = 40;
    goblin2_health = 55;
    goblin3_health = 50;
    print("Goblin 1 Health: " + STR(goblin1_health));
    print("Goblin 2 Health: " + STR(goblin2_health));
    print("Goblin 3 Health: " + STR(goblin3_health));
    

}
main();