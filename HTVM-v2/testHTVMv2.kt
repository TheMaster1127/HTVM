

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

fun <T> HTVM_Append(arr: MutableList<T>, value: T) {
    arr.add(value)
}

fun <T> HTVM_Size(arr: List<T>): Int {
    return arr.size
}


fun func1(var1: String): String {
    return var1 + var1
}
fun func2(var1: String) {
    print(var1 + var1)
}
fun func3(var1: String, var2: String = "hello") {
    print(var1 + " " + var2)
}
fun main(args: Array<String>) {
    print(func1("hi1"))
    func2("hi2")
    func3("hi3")
    func3("hi3", "hello3")
    var var1: Int? = null
    val myArr0 = ArrayList<Boolean>()
    HTVM_Append(myArr0, true)
    HTVM_Append(myArr0, false)
    HTVM_Append(myArr0, true)
    val myArr = arrayListOf(5, 6, 7)
    for (A_IndexA1 in 0 until 5 + 0) {
        var1 = 6
        HTVM_Append(myArr, A_IndexA1)
    }
    for (A_IndexA2 in 0 until HTVM_Size(myArr) + 0) {
        print(myArr[A_IndexA2])
    }
    for (A_IndexA3 in 0 until HTVM_Size(myArr0) + 0) {
        print(myArr0[A_IndexA3])
    }
    if (var1 == 6) {
        print(var1)
    }
    else if (var1 == 7) {
        print(var1)
    }
    var var123: String = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn";
    val items4 = LoopParseFunc(var123, "\n", "\r")
    for ((A_IndexA4 , A_LoopFieldA4) in items4.withIndex()) {
        if (A_IndexA4 == 0) {
            print(A_IndexA4)
        }
        print(A_LoopFieldA4)
    }
    print("==================")
    var var1234: String = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg";
    val items5 = LoopParseFunc(var1234, ",")
    for ((A_IndexA5 , A_LoopFieldA5) in items5.withIndex()) {
        if (A_IndexA5 == 0) {
            print(A_IndexA5)
        }
        print(A_LoopFieldA5)
    }
    print("==================")
    var var12345: String = "hello";
    val items6 = LoopParseFunc(var12345)
    for ((A_IndexA6 , A_LoopFieldA6) in items6.withIndex()) {
        print(A_LoopFieldA6)
    }
}