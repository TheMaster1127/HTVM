

// Print function
def print = { message ->
    System.out.print("$message\n\r")
}

def HTVM_Size(arr) {
    return arr.size()
}


def arr123 = [1, 3, 5]
for (A_Index1 in 0..<HTVM_Size(arr123) + 0) {
    print(arr123[A_Index1])
}

