

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
    for (A_Index1 in 0..20 + 0) {
        print("hello HTVM import")
        print("hello HTVM\nimport")
    }
    for (A_Index2 in 0..6 + 0) {
        print("hello HTVM import")
        print("hello HTVM\nimport")
    }
    for (A_Index3 in 0..5 + 0) {
        print("hello\" HTVM v2")
        print("hello HTVM\\v2\\\\s")
        print("hello HTVM\nv2")
        print("hello HTVM\\nv2")
        print(A_Index3)
        for (A_Index4 in 0..5 + 0) {
            print("hello HTVM v2")
            print("hello HTVM\nv2")
            for (A_Index5 in 0..5 + 0) {
                print("hello HTVM v2")
                print("hello HTVM\nv2")
                print(A_Index5)
            }
            print(A_Index4)
        }
    }
    qWAERSFD()
    qWAERSFD(waedsfd())
    print(5+5 != 5 !SZDS() + "A+-+--+ != ADSF" + "WSADFD" + "qwadsf" + adsf >= 3 <= qwerd > qwretr < wdsdf == 5 != 8)
    print(if "QWADSDF" + "qawdsf" || var1 ! var4 + "ASDFX" + !ADSFD("Qwads" + "QASD" + "aszd" < 6) false else true || null && false)
    print(HTVM_Size(aszd) HTVM_Append(aszd, HTVM_Size(aszd)))
    Avar123 = StringTrimRight(STRRAWSD, 1)
    if(var1 == 5 && var2w3erf < 6)
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var1 = 1
    print(if (var1 == 1) "hello" else "bye")
    var1 = 0
    print(if (var1 == 1) "hello" else "bye")
    if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS")
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS")
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS")
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS")
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS")
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS")
    } else {
        print(5+5)
    }
    print("==========")
    print("==========")
    print("==========")
    print("==========")
    print("==========")
    print("==========")
    try {
        throw Exception("this is an ERROR HTVM v2")
    }
    catch (ee: Exception) {
        print(ee.message)
    }
    finally {
        print("finally finally finally finally")
    }
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
    for (A_Index6 in 0..5 + 0) {
        print(A_Index6)
    }
    */
}