

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
  println(value)
}

fun STR(value: Any): String {
    return when (value) {
        is Int -> value.toString()
        is Long -> value.toString()
        is Float -> value.toString()
        is Double -> value.toString()
        is Boolean -> if (value) "1" else "0"
        is String -> value
        else -> value.toString()
    }
}

fun <T> HTVM_Append(arr: MutableList<T>, value: T) {
    arr.add(value)
}

fun <T> HTVM_Size(arr: List<T>): Int {
    return arr.size
}


// This is a preview of your language and how it will look.
// Here's how types will appear if you only define them:
var varName1: Int? = null
var varName2: String? = null
var varName3: Boolean? = null
var varName4: Float? = null
var varName5: Byte? = null
var varName6: Short? = null
var varName7: Int? = null
var varName8: Long? = null
// Alternatively, you can define them like this:
var varName9: Int = 34;
// Here's how to define a function with static types when converting to statically typed languages like:
// TypeScript, C++, Go, C#, Java, Kotlin, Nim, Swift, and Dart.
// However, even if you're not targeting a statically typed language (e.g. JavaScript or Python),
// the types will be stripped away automatically and the function will still work as expected.
fun funcName1(paramVar1: Int, paramVar2: String = "", paramVar3: Boolean = false, paramVar4: Float = 1.5f) {
    // This is how the global keyword works if we convert to Python and AutoHotKey.
    // But even if we don't, it will just be removed, so you can add it if you want to convert to Python and AutoHotKey as well.
    // Here's how if, else if, and else statements will look:
    if (varName1 == paramVar1) {
        print("varName1 is equal to paramVar1")
    }
    else if (varName1 != paramVar1 || varName1 <= paramVar1) {
        print("varName1 is less than or equal to paramVar1")
    } else {
        print("varName1 is NOT less than or equal to paramVar1 or something else")
    }
    // this is how the return keyword will look like in your lang
    return
}
// This is where the main function will start. It's just a label, so don't worry.
fun main(args: Array<String>) {
    funcName1(varName9)
    // this is how a while loop works in your lang
    var var1: Boolean = false;
    while (var1 == false) {
        print("we are inside the while loop")
        var1 = true
    }
    print("we are outside the while loop")
    // this is how to use a loop whit arrays
    var array123 = arrayListOf("hey")
    HTVM_Append(array123, "hello")
    HTVM_Append(array123, "how")
    HTVM_Append(array123, "are")
    HTVM_Append(array123, "you")
    HTVM_Append(array123, "doing")
    for (A_Index1 in 0 until HTVM_Size(array123)) {
        print("iteration: " + STR(A_Index1))
        print("Item: " + array123[A_Index1])
    }
    print("this is how the escape char looks like \nthis is a new line")
    /*
    this is a comment block
    this is a comment block
    */
    // this is how to use an AutoHotKey like Loop
    for (A_Index2 in 0 until 10) {
        if (A_Index2 % 2 == 0) {
            continue
        }
        print(A_Index2)
    }
    // this is how to use an AutoHotKey like infinite Loop
    for (A_Index3 in generateSequence(0) { it + 1 }) {
        if (A_Index3 == 5) {
            break
        } else {
            print(A_Index3)
        }
    }
    // this is how to use an AutoHotKey like Loop, parse
    var someText: String = "hello how are you doing\ntoday we are good.";
    val items4 = LoopParseFunc(someText, " ", "\n")
    for ((A_Index4 , A_LoopField4) in items4.withIndex()) {
        print(A_LoopField4)
    }
    // Error Handling
    try {
        throw Exception("Something went wrong!")
    }
    catch (e: Exception) {
        print(e.message)
    }
    finally {
        print("Finally block executed")
    }
    

}