

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
    if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS")
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS")
    } else {
        print(5+5)
    }
    try {
        throw Exception("this is an ERROR HTVM v2")
    }
    catch (ee: Exception) {
        print(ee.message)
    }
    finally {
        print("finally finally finally finally")
    }
}
