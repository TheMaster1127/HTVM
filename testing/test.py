

# used the print func

# Convert value to string
def STR(value):
    if isinstance(value, (int, float)):
        return str(value)
    elif isinstance(value, bool):
        return "1" if value else "0"
    elif isinstance(value, str):
        return value  # If the value is already a string, return it as-is
    else:
        raise TypeError("Unsupported type")


A_SUCCESS = 0
A_SUCCESS_WEIGHTED = 0
A_TOTAL_WEIGHT = 0
A_SUCCESS_ALL = False
myOwn_var1 = 5
myOwn_var2 = 6.54
myOwn2_var1 = 5
myOwn2_var2 = 6.54
myOwn3_var1 = 5
myOwn3_var2 = 6.54
myOwn4_var1 = 5
myOwn4_var2 = 6.54
myOwn5_var1 = 5
myOwn5_var2 = "hello"
print(myOwn_var1)
# ===================================
# HTVM: LINER Demo – Game Fight Eligibility
# ===================================
# --- Variables ---
hasStrongWeapon = True
hasShield = False
health = 75
gold = 120
isBuffed = True
enemyNearby = True
# --- LINER Block for Fight Eligibility ---
A_SUCCESS = 0
A_SUCCESS_WEIGHTED = 0
A_TOTAL_WEIGHT = 16
A_SUCCESS_ALL = False
if (hasStrongWeapon):
    A_SUCCESS += 1
    A_SUCCESS_WEIGHTED += 5
if (hasShield):
    A_SUCCESS += 1
    A_SUCCESS_WEIGHTED += 2
if (health > 50):
    A_SUCCESS += 1
    A_SUCCESS_WEIGHTED += 3
if (gold >= 100):
    A_SUCCESS += 1
    A_SUCCESS_WEIGHTED += 1
if (isBuffed):
    A_SUCCESS += 1
    A_SUCCESS_WEIGHTED += 2
if (enemyNearby):
    A_SUCCESS += 1
    A_SUCCESS_WEIGHTED += 3
if (A_SUCCESS_WEIGHTED == A_TOTAL_WEIGHT):
    A_SUCCESS_ALL = True
# --- Output Results ---
print("=== Fight Eligibility Evaluation ===")
print("Raw success count: " + STR(A_SUCCESS))
print("Weighted success: " + STR(A_SUCCESS_WEIGHTED))
print("Total possible weight: " + STR(A_TOTAL_WEIGHT))
print("All passed? " + STR(A_SUCCESS_ALL))
# --- Single-condition LINER example ---
A_SUCCESS = 0
A_SUCCESS_WEIGHTED = 0
A_TOTAL_WEIGHT = 1
A_SUCCESS_ALL = False
if (hasShield):
    A_SUCCESS += 1
    A_SUCCESS_WEIGHTED += 1
if (A_SUCCESS_WEIGHTED == A_TOTAL_WEIGHT):
    A_SUCCESS_ALL = True
print("=== Single-condition Check ===")
print("Raw success count: " + STR(A_SUCCESS))
print("Weighted success: " + STR(A_SUCCESS_WEIGHTED))
print("Total possible weight: " + STR(A_TOTAL_WEIGHT))
print("All passed? " + STR(A_SUCCESS_ALL))
print(myOwn_var2)
