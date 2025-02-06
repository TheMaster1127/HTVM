

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
fun szdfxc(var1: String = "hi") {
    print(var1)
    print("hi2 void")
}
fun szdfxc1(var0: Int, var1: String = "hi", var2: String = "hi2") {
    print(var0)
    print(var1)
    print(var2)
    print("hi2 void")
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
/*
waedsfdsaeds
aedsf
saedsfxawdsfdfsaw
fddf
sefdf
saersdsaersdgfd
*/
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
fun szdfxc2(var1: String = "hi", var2: String = "hi2") {
    print(var1)
    print(var2)
    print("hi2 void")
}


fun main(args: Array<String>) {
    

    print(szdfxc0())
    szdfxc()
    szdfxc1(5)
    szdfxc1(6, "hello")
    var var1: Double? = null
    var var2: Char? = null
    var var3: UByte? = null
    var var4: UShort? = null
    var var5: UInt? = null
    var var6: ULong? = null
    var var7: Int? = null
    var var8: String? = null
    var var9: Boolean? = null
    var var10: Float? = null
    var var11: Byte? = null
    var var12: Short? = null
    var var13: Int? = null
    var var14: Long? = null
    val array1 = ArrayList<String>()
    val array2 = ArrayList<Int>()
    val array3 = ArrayList<String>()
    val array4 = ArrayList<Float>()
    val array5 = ArrayList<Boolean>()
    szdfxc2()
    szdfxc2("HI1")
    szdfxc2("HI1", "HI2")
    print("Hello, World!")
    for (A_Index1 in 0..5 + 0) {
        print(A_Index1)
    }
}
