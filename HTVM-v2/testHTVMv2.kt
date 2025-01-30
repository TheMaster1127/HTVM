

// Print function for various types
fun print(value: Any) {
    when (value) {
        is String -> println(value)
        is Int, is Float, is Double -> println(value.toString())
        is Boolean -> println(if (value) "true" else "false")
        else -> println("Unsupported type")
    }
}


fun szdfxc0(): String {
    return "hi"
}
fun szdfxc() {
    print("hi2 void")
}
fun main(args: Array<String>) {
    print(szdfxc0())
    szdfxc()
    print("Hello, World!")
    for (A_Index1 in 0..5 + 0) {
        print(A_Index1)
    }
}
