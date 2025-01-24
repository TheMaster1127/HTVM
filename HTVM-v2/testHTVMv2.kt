

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
    // some comment
    while (true) {
        print("hi from HTVM v2 still in development")
        break
    }
    /*
    WAESFD
    WAQESR
    FRAWE
    DSFDSADSDF
    asfdx
    for (A_Index1 in 0..5 + 0) {
        print(A_Index1)
    }
    */
}
