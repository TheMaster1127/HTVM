

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
    while (true) {
        print("hi from HTVM v2 still in development")
        break
    }
}
