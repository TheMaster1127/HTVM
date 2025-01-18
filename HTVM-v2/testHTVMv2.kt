

// Print function for various types
fun print(value: Any) {
    when (value) {
        is String -> println(value)
        is Int, is Float, is Double -> println(value.toString())
        is Boolean -> println(if (value) "true" else "false")
        else -> println("Unsupported type")
    }
}

fun <T> HTVM_Append(arr: MutableList<T>, value: T) {
    arr.add(value)
}

fun <T> HTVM_Size(arr: List<T>): Int {
    return arr.size
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
    print(5+5 != 5 !SZDS() + "A+-+--+ != ADSF" + "WSADFD" + "qwadsf" + adsf >= 3 <= qwerd > qwretr < wdsdf = 5 != 8)
    print(if "QWADSDF" + "qawdsf" || var1 ! var4 + "ASDFX" + !ADSFD("Qwads" + "QASD" + "aszd" < 6) false else true || null && false)
    print(HTVM_Size(aszd) HTVM_Append(aszd, HTVM_Size(aszd)))
    Avar123 = StringTrimRight(STRRAWSD, 1)
    if(var1 == 5 && var2w3erf < 6)
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var1 = 1
    print(if (var1 == 1) "hello" else "bye")
    var1 = 0
    print(if (var1 == 1) "hello" else "bye")
}