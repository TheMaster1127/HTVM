

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


var A_SUCCESS = 0;
var A_SUCCESS_WEIGHTED = 0;
var A_TOTAL_WEIGHT = 0;
var A_SUCCESS_ALL = false;
var myOwn_var1 = 5;
var myOwn_var2 = 6.54;
var myOwn2_var1 = 5;
var myOwn2_var2 = 6.54;
var myOwn3_var1 = 5;
var myOwn3_var2 = 6.54;
var myOwn4_var1 = 5;
var myOwn4_var2 = 6.54;
var myOwn5_var1 = 5;
var myOwn5_var2 = "hello";
async function main() {
    print(myOwn_var1);
    // ===================================
    // HTVM: LINER Demo – Game Fight Eligibility
    // ===================================
    // --- Variables ---
    var hasStrongWeapon = true;
    var hasShield = false;
    var health = 75;
    var gold = 120;
    var isBuffed = true;
    var enemyNearby = true;
    // --- LINER Block for Fight Eligibility ---
    A_SUCCESS = 0;
    A_SUCCESS_WEIGHTED = 0;
    A_TOTAL_WEIGHT = 16;
    A_SUCCESS_ALL = false;
    if (hasStrongWeapon) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 5;
    }
    if (hasShield) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 2;
    }
    if (health > 50) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 3;
    }
    if (gold >= 100) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 1;
    }
    if (isBuffed) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 2;
    }
    if (enemyNearby) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 3;
    }
    if (A_SUCCESS_WEIGHTED == A_TOTAL_WEIGHT) {
        A_SUCCESS_ALL = true;
    }
    // --- Output Results ---
    print("=== Fight Eligibility Evaluation ===");
    print("Raw success count: " + STR(A_SUCCESS));
    print("Weighted success: " + STR(A_SUCCESS_WEIGHTED));
    print("Total possible weight: " + STR(A_TOTAL_WEIGHT));
    print("All passed? " + STR(A_SUCCESS_ALL));
    // --- Single-condition LINER example ---
    A_SUCCESS = 0;
    A_SUCCESS_WEIGHTED = 0;
    A_TOTAL_WEIGHT = 1;
    A_SUCCESS_ALL = false;
    if (hasShield) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 1;
    }
    if (A_SUCCESS_WEIGHTED == A_TOTAL_WEIGHT) {
        A_SUCCESS_ALL = true;
    }
    print("=== Single-condition Check ===");
    print("Raw success count: " + STR(A_SUCCESS));
    print("Weighted success: " + STR(A_SUCCESS_WEIGHTED));
    print("Total possible weight: " + STR(A_TOTAL_WEIGHT));
    print("All passed? " + STR(A_SUCCESS_ALL));
    print(myOwn_var2);
    

}
main();