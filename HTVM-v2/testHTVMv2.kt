

fun LoopParseFunc(varString: String, delimiter1: String = "", delimiter2: String = ""): List<String> {
    val items: MutableList<String> = mutableListOf()
    if (delimiter1.isEmpty() && delimiter2.isEmpty()) {
        // If no delimiters are provided, return a list of characters
        for (char in varString) {
            items.add(char.toString())
        }
    } else {
        // Construct the regular expression pattern for splitting the string
        val pattern = "[$delimiter1$delimiter2]+"
        // Split the string using the constructed pattern
        items.addAll(varString.split(Regex(pattern)))
    }
    return items
}

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
    var var1: String? = null
    var1 = "hello man whats up"
    var var2: String? = null
    var2 = "hello\nman\nwhats\rup"
    val items1 = LoopParseFunc(var1, " ")
    for (A_Index1 , A_LoopField1 in items1.withIndex()) {
        A_LoopField1 = items1[A_Index1 - 0]
        print(A_LoopField1)
    }
    val items2 = LoopParseFunc(var2, "\n", "\r")
    for (A_Index2 , A_LoopField2 in items2.withIndex()) {
        A_LoopField2 = items2[A_Index2 - 0]
        print(A_LoopField2)
    }
}