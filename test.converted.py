

# used the print func


A_SUCCESS = 0
A_SUCCESS_WEIGHTED = 0
A_TOTAL_WEIGHT = 4
A_SUCCESS_ALL = False
# --- State Variables for Daily Chores ---
tookOutTrash = True
fedTheCat = True
checkedMail = False
wateredPlants = True
# ---------------
A_SUCCESS = 0
A_SUCCESS_WEIGHTED = 0
A_TOTAL_WEIGHT = 4
A_SUCCESS_ALL = False
if (tookOutTrash):
    A_SUCCESS += 1
    A_SUCCESS_WEIGHTED += 1
if (fedTheCat):
    A_SUCCESS += 1
    A_SUCCESS_WEIGHTED += 1
if (checkedMail):
    A_SUCCESS += 1
    A_SUCCESS_WEIGHTED += 1
if (wateredPlants):
    A_SUCCESS += 1
    A_SUCCESS_WEIGHTED += 1
if (A_SUCCESS_WEIGHTED == A_TOTAL_WEIGHT):
    A_SUCCESS_ALL = True
# ---------------------------------
print("--- Daily Chore Report ---")
print("Tasks Completed: " + A_SUCCESS + " out of " + A_TOTAL_WEIGHT)
# ---------------------------------
if (A_SUCCESS_ALL):
    print("Result: All chores done!")
else:
    print("Result: Still have tasks to do.")
