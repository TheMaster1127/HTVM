

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

fun <T> HTVM_Pop(arr: MutableList<T>) {
    if (arr.isNotEmpty()) arr.removeAt(arr.lastIndex)
}

fun <T> HTVM_Size(arr: List<T>): Int {
    return arr.size
}

fun <T> HTVM_Insert(arr: MutableList<T>, index: Int, value: T) {
    arr.add(index, value)
}

fun <T> HTVM_Remove(arr: MutableList<T>, value: T) {
    arr.remove(value)
}

fun <T> HTVM_IndexOf(arr: List<T>, value: T): Int {
    return arr.indexOf(value)
}


// start














fun func0(input: String) {
    println(input)
}














fun func1(var1: Double, var2: Char, var3: UByte, var4: UShort, var5: UInt, var6: ULong, var7: Int, var8: String, var9: Boolean, var10: Float, var11: Byte, var12: Short, var13: Int, var14: Long) {
    print(var1)
    print(var2)
    print(var3)
    print(var4)
    print(var5)
    print(var6)
    print(var7)
    print(var8)
    print(var9)
    print(var10)
    print(var11)
    print(var12)
    print(var13)
    print(var14)
}
fun func2(var1: Double): Double {
    return var1
}
fun func3(var1: Char): Char {
    return var1
}
fun func4(var1: UByte): UByte {
    return var1
}
fun func5(var1: UShort): UShort {
    return var1
}
fun func6(var1: UInt): UInt {
    return var1
}
fun func7(var1: ULong): ULong {
    return var1
}
fun func8(var1: Int): Int {
    return var1
}
fun func9(var1: String): String {
    return var1
}
fun func10(var1: Boolean): Boolean {
    return var1
}
fun func11(var1: Float): Float {
    return var1
}
fun func12(var1: Byte): Byte {
    return var1
}
fun func13(var1: Short): Short {
    return var1
}
fun func14(var1: Int): Int {
    return var1
}
fun func15(var1: Long): Long {
    return var1
}
/*
this
is
a
multy
line
comment
*/
// outside vars
var var01: Double = 3.1234567891011;
var var02: Char = 'a';
var var03: UByte = 25u;
var var04: UShort = 30u;
var var05: UInt = 35u;
var var06: ULong = 40uL;
var var07: Int = 100;
var var08: String = "hello var ouside";
var var09: Boolean = false;
var var010: Float = 3.14f;
var var011: Byte = 100;
var var012: Short = 200;
var var013: Int = 230;
var var014: Long = 80009L;
fun main(args: Array<String>) {
    var var_1: Double? = null
    var var_2: Char? = null
    var var_3: UByte? = null
    var var_4: UShort? = null
    var var_5: UInt? = null
    var var_6: ULong? = null
    var var_7: Int? = null
    var var_8: String? = null
    var var_9: Boolean? = null
    var var_10: Float? = null
    var var_11: Byte? = null
    var var_12: Short? = null
    var var_13: Int? = null
    var var_14: Long? = null
    func1(var01, var02, var03, var04, var05, var06, var07, var08, var09, var010, var011, var012, var013, var014)
    var_1 = func2(var01)
    var_2 = func3(var02)
    var_3 = func4(var03)
    var_4 = func5(var04)
    var_5 = func6(var05)
    var_6 = func7(var06)
    var_7 = func8(var07)
    var_8 = func9(var08)
    var_9 = func10(var09)
    var_10 = func11(var010)
    var_11 = func12(var011)
    var_12 = func13(var012)
    var_13 = func14(var013)
    var_14 = func15(var014)
    print(var_1)
    print(var_2)
    print(var_3)
    print(var_4)
    print(var_5)
    print(var_6)
    print(var_7)
    print(var_8)
    print(var_9)
    print(var_10)
    print(var_11)
    print(var_12)
    print(var_13)
    print(var_14)
    // start
    

    

    

    

    

    

    

    func0("Hello World")
    

    

    

    

    

    

    

    print("==================================")
    for (A_Index1 in 0 until 5 + 0) {
        if (A_Index1 == 0) {
            print(A_Index1)
        }
        else if (A_Index1 == 1) {
            print(A_Index1)
        }
        else if (A_Index1 == 2) {
            print(A_Index1)
        }
        else if (A_Index1 == 3) {
            print(A_Index1)
        }
        else if (A_Index1 == 4) {
            print(A_Index1)
        }
        else if (A_Index1 == 5) {
            print(A_Index1)
        } else {
            print("HOW????")
            print(A_Index1)
        }
    }
    var vars1: Boolean = false;
    var vars2: Int = 0;
    while (vars1 == false) {
        vars2++;
        print(vars2)
        if (vars2 == 6) {
            vars1 = true
        }
    }
    for (A_Index2 in 0..someLimit) {
        if (A_Index2 == 6) {
            break
        } else {
            continue
        }
        // this is only for lua
        ::continue::
    }
    var str1: String = "hello 123 hello2";
    val items3 = LoopParseFunc(str1, " ")
    for ((A_Index3 , A_LoopField3) in items3.withIndex()) {
        print(A_LoopField3)
    }
    print("==================")
    val items4 = LoopParseFunc(str1)
    for ((A_Index4 , A_LoopField4) in items4.withIndex()) {
        print(A_LoopField4)
        if (A_LoopField4 == "2") {
            break
        } else {
            continue
        }
        ::continue::
    }
    /*
    keyWordArrayAppend
    keyWordArrayPop
    keyWordArraySize
    keyWordArrayInsert
    keyWordArrayRemove
    keyWordArrayIndexOf
    keyWordArrayDefinition
    keyWordArrayOfIntegersDefinition
    keyWordArrayOfStringsDefinition
    keyWordArrayOfFloatingPointNumbersDefinition
    keyWordArrayOfBooleansDefinition
    */
    val arr1 = arrayListOf("hello1", "hello2")
    val arr2 = arrayListOf(true, false)
    val arr3 = arrayListOf(3.13, 3.14)
    val arr4 = arrayListOf(1, 6, 2)
    val arr5 = arrayListOf("real STR")
    // Array operations
    HTVM_Append(arr1, "hello3")
    var sizeArr1: Int = HTVM_Size(arr1);
    print("the size of arr1 is:")
    print(sizeArr1)
    HTVM_Insert(arr1, 1, "hello?????")
    HTVM_Remove(arr1, 0)
    var idx1: Int = HTVM_IndexOf(arr1, "hello2");
    print("the index of arr1 for hello2 is:")
    print(idx1)
    HTVM_Pop(arr1)
    for (A_Index5 in 0 until HTVM_Size(arr1) + 0) {
        print(arr1[A_Index5])
    }
    HTVM_Append(arr2, true)
    var sizeArr2: Int = HTVM_Size(arr2);
    print("the size of arr2 is:")
    print(sizeArr2)
    HTVM_Insert(arr2, 1, false)
    HTVM_Remove(arr2, 0)
    var idx2: Int = HTVM_IndexOf(arr2, true);
    print("the index of arr2 for true is:")
    print(idx2)
    HTVM_Pop(arr2)
    for (A_Index6 in 0 until HTVM_Size(arr2) + 0) {
        print(arr2[A_Index6])
    }
    HTVM_Append(arr3, 6.489)
    var sizeArr3: Int = HTVM_Size(arr3);
    print("the size of arr3 is:")
    print(sizeArr3)
    HTVM_Insert(arr3, 1, 1.556)
    HTVM_Remove(arr3, 0)
    var idx3: Int = HTVM_IndexOf(arr3, 3.14);
    print("the index of arr3 for 3.14 is:")
    print(idx3)
    HTVM_Pop(arr3)
    for (A_Index7 in 0 until HTVM_Size(arr3) + 0) {
        print(arr3[A_Index7])
    }
    HTVM_Append(arr4, 69)
    var sizeArr4: Int = HTVM_Size(arr4);
    print("the size of arr4 is:")
    print(sizeArr4)
    HTVM_Insert(arr4, 1, 420)
    HTVM_Remove(arr4, 0)
    var idx4: Int = HTVM_IndexOf(arr4, 69);
    print("the index of arr4 for 69 is:")
    print(idx4)
    HTVM_Pop(arr4)
    for (A_Index8 in 0 until HTVM_Size(arr4) + 0) {
        print(arr4[A_Index8])
    }
    HTVM_Append(arr5, "hello3real")
    var sizeArr5: Int = HTVM_Size(arr5);
    print("the size of arr5 is:")
    print(sizeArr5)
    HTVM_Insert(arr5, 1, "hello?real????")
    HTVM_Remove(arr5, 0)
    var idx5: Int = HTVM_IndexOf(arr5, "hello3real");
    print("the index of arr5 for hello3real is:")
    print(idx5)
    HTVM_Pop(arr5)
    for (A_Index9 in 0 until HTVM_Size(arr5) + 0) {
        print(arr5[A_Index9])
    }
    /*
    keyWordThrow
    keyWordErrorMsg
    keyWordTry
    keyWordCatch
    keyWordFinally
    */
    try {
        print("Trying...")
        throw Exception("Something went wrong!")
    }
    catch (e: Exception) {
        print("Caught an error:")
        print(e.message)
    }
    finally {
        print("This always runs, success or error.")
    }
    print("==============================================")
}