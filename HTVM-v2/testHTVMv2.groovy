

// Print function
def print = { message ->
    System.out.print("$message\n")
}


for (A_Index1 in 0..5 + 0) {
    print("hello HTVM v2")
    print("hello HTVM\nv2")
    print(A_Index1)
    for (A_Index2 in 0..5 + 0) {
        print("hello HTVM v2")
        print("hello HTVM\nv2")
        for (A_Index3 in 0..5 + 0) {
            print("hello HTVM v2")
            print("hello HTVM\nv2")
            print(A_Index3)
        }
        print(A_Index2)
    }
}




