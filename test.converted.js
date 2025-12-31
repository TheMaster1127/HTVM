

function print(value) {
    console.log(value)
}


async function main() {
    var A_SUCCESS = 0;
    var A_SUCCESS_WEIGHTED = 0;
    var A_TOTAL_WEIGHT = 4;
    var A_SUCCESS_ALL = false;
    // --- State Variables for Daily Chores ---
    var tookOutTrash = true;
    var fedTheCat = true;
    var checkedMail = false;
    var wateredPlants = true;
    // ---------------
    A_SUCCESS = 0;
    A_SUCCESS_WEIGHTED = 0;
    A_TOTAL_WEIGHT = 4;
    A_SUCCESS_ALL = false;
    if (tookOutTrash) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 1;
    }
    if (fedTheCat) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 1;
    }
    if (checkedMail) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 1;
    }
    if (wateredPlants) {
        A_SUCCESS++;
        A_SUCCESS_WEIGHTED += 1;
    }
    if (A_SUCCESS_WEIGHTED == A_TOTAL_WEIGHT) {
        A_SUCCESS_ALL = true;
    }
    // ---------------------------------
    print("--- Daily Chore Report ---");
    print("Tasks Completed: " + A_SUCCESS + " out of " + A_TOTAL_WEIGHT);
    // ---------------------------------
    if (A_SUCCESS_ALL) {
        print("Result: All chores done!");
    } else {
        print("Result: Still have tasks to do.");
    }
    

}
main();