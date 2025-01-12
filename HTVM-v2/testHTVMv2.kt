

// Print function for various types
fun print(value: Any) {
    when (value) {
        is String -> println(value)
        is Int, is Float, is Double -> println(value.toString())
        is Boolean -> println(if (value) "true" else "false")
        else -> println("Unsupported type")
    }
}


fun main(args: Array<String>) {
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
}