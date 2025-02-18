import Foundation


func LoopParseFunc(_ varString: String, _ delimiter1: String = "", _ delimiter2: String = "") -> [String] {
    var items: [String] = []
    // If no delimiters are provided, return an array of characters
    if delimiter1.isEmpty && delimiter2.isEmpty {
        items = Array(varString).map { String($0) }
    } else {
        // Use the first delimiter for splitting the string
        let delimiter = delimiter1.isEmpty ? delimiter2 : delimiter1
        items = varString.split(separator: Character(delimiter)).map { String($0) }
    }
    return items
}

// Print function for various types

func HTVM_Append<T>(_ arr: inout [T], _ value: T) {
    arr.append(value)
}

func HTVM_Pop<T>(_ arr: inout [T]) {
    if !arr.isEmpty {
        arr.removeLast()
    }
}

func HTVM_Size<T>(_ arr: [T]) -> Int {
    return arr.count
}

func HTVM_Insert<T>(_ arr: inout [T], _ index: Int, _ value: T) {
    arr.insert(value, at: index)
}

func HTVM_Remove<T: Equatable>(_ arr: inout [T], _ value: T) {
    if let index = arr.firstIndex(of: value) {
        arr.remove(at: index)
    }
}

func HTVM_IndexOf<T: Equatable>(_ arr: [T], _ value: T) -> Int? {
    return arr.firstIndex(of: value)
}

// Function that throws an error with a string message
func ErrorMsg(_ message: String) throws {
    throw NSError(domain: "", code: 0, userInfo: [NSLocalizedDescriptionKey: message])
}


// start






















func func0(_ input: String) {
    print(input)
}






func func1(_ var1: Double, _ var2: Character, _ var3: UInt8, _ var4: UInt16, _ var5: UInt32, _ var6: UInt64, _ var7: Int, _ var8: String, _ var9: Bool, _ var10: Float, _ var11: Int8, _ var12: Int16, _ var13: Int32, _ var14: Int64) {
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
func func2(_ var1: Double) -> Double {
    return var1
}
func func3(_ var1: Character) -> Character {
    return var1
}
func func4(_ var1: UInt8) -> UInt8 {
    return var1
}
func func5(_ var1: UInt16) -> UInt16 {
    return var1
}
func func6(_ var1: UInt32) -> UInt32 {
    return var1
}
func func7(_ var1: UInt64) -> UInt64 {
    return var1
}
func func8(_ var1: Int) -> Int {
    return var1
}
func func9(_ var1: String) -> String {
    return var1
}
func func10(_ var1: Bool) -> Bool {
    return var1
}
func func11(_ var1: Float) -> Float {
    return var1
}
func func12(_ var1: Int8) -> Int8 {
    return var1
}
func func13(_ var1: Int16) -> Int16 {
    return var1
}
func func14(_ var1: Int32) -> Int32 {
    return var1
}
func func15(_ var1: Int64) -> Int64 {
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
var var01: Double = 3.1234567891011
var var02: Character = "a"
var var03: UInt8 = 25
var var04: UInt16 = 30
var var05: UInt32 = 35
var var06: UInt64 = 40
var var07: Int = 100
var var08: String = "hello var ouside"
var var09: Bool = false
var var010: Float = 3.14
var var011: Int8 = 100
var var012: Int16 = 200
var var013: Int32 = 230
var var014: Int64 = 80009
func main() {
    var var_1: Double = 0.00
    var var_2: Character = "a"
    var var_3: UInt8 = 0
    var var_4: UInt16 = 0
    var var_5: UInt32 = 0
    var var_6: UInt64 = 0
    var var_7: Int = 0
    var var_8: String = ""
    var var_9: Bool = false
    var var_10: Float = 0.00
    var var_11: Int8 = 0
    var var_12: Int16 = 0
    var var_13: Int32 = 0
    var var_14: Int64 = 0
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
    for A_Index1 in 0 ..< 5 + 0 {
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
    var vars1: Bool = false
    var vars2: Int = 0
    while (vars1 == false) {
        vars2 += 1
        print(vars2)
        if (vars2 == 6) {
            vars1 = true
        }
    }
    for A_Index2 in 0 ..< someLimit {
        if (A_Index2 == 6) {
            break
        } else {
            continue
        }
        // this is only for lua
        ::continue::
    }
    var str1: String = "hello 123 hello2"
    var items3 = LoopParseFunc(str1, " ")
    for (A_Index3 , A_LoopField3) in items3.enumerated() {
        print(A_LoopField3)
    }
    print("==================")
    var items4 = LoopParseFunc(str1)
    for (A_Index4 , A_LoopField4) in items4.enumerated() {
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
    var arr1: [String] = ["hello1", "hello2"]
    var arr2: [Bool] = [true, false]
    var arr3: [Float] = [3.13, 3.14]
    var arr4: [Int] = [1, 6, 2]
    var arr5: [String] = ["real STR"]
    // Array operations
    HTVM_Append(&arr1, "hello3")
    var sizeArr1: Int = HTVM_Size(arr1)
    print("the size of arr1 is:")
    print(sizeArr1)
    HTVM_Insert(&arr1, 1, "hello?????")
    HTVM_Remove(&arr1, 0)
    var idx1: Int = HTVM_IndexOf(arr1, "hello2")
    print("the index of arr1 for hello2 is:")
    print(idx1)
    HTVM_Pop(&arr1)
    for A_Index5 in 0 ..< HTVM_Size(arr1) + 0 {
        print(arr1[A_Index5])
    }
    HTVM_Append(&arr2, true)
    var sizeArr2: Int = HTVM_Size(arr2)
    print("the size of arr2 is:")
    print(sizeArr2)
    HTVM_Insert(&arr2, 1, false)
    HTVM_Remove(&arr2, 0)
    var idx2: Int = HTVM_IndexOf(arr2, true)
    print("the index of arr2 for true is:")
    print(idx2)
    HTVM_Pop(&arr2)
    for A_Index6 in 0 ..< HTVM_Size(arr2) + 0 {
        print(arr2[A_Index6])
    }
    HTVM_Append(&arr3, 6.489)
    var sizeArr3: Int = HTVM_Size(arr3)
    print("the size of arr3 is:")
    print(sizeArr3)
    HTVM_Insert(&arr3, 1, 1.556)
    HTVM_Remove(&arr3, 0)
    var idx3: Int = HTVM_IndexOf(arr3, 3.14)
    print("the index of arr3 for 3.14 is:")
    print(idx3)
    HTVM_Pop(&arr3)
    for A_Index7 in 0 ..< HTVM_Size(arr3) + 0 {
        print(arr3[A_Index7])
    }
    HTVM_Append(&arr4, 69)
    var sizeArr4: Int = HTVM_Size(arr4)
    print("the size of arr4 is:")
    print(sizeArr4)
    HTVM_Insert(&arr4, 1, 420)
    HTVM_Remove(&arr4, 0)
    var idx4: Int = HTVM_IndexOf(arr4, 69)
    print("the index of arr4 for 69 is:")
    print(idx4)
    HTVM_Pop(&arr4)
    for A_Index8 in 0 ..< HTVM_Size(arr4) + 0 {
        print(arr4[A_Index8])
    }
    HTVM_Append(&arr5, "hello3real")
    var sizeArr5: Int = HTVM_Size(arr5)
    print("the size of arr5 is:")
    print(sizeArr5)
    HTVM_Insert(&arr5, 1, "hello?real????")
    HTVM_Remove(&arr5, 0)
    var idx5: Int = HTVM_IndexOf(arr5, "hello3real")
    print("the index of arr5 for hello3real is:")
    print(idx5)
    HTVM_Pop(&arr5)
    for A_Index9 in 0 ..< HTVM_Size(arr5) + 0 {
        print(arr5[A_Index9])
    }
    /*
    keyWordThrow
    keyWordErrorMsg
    keyWordTry
    keyWordCatch
    keyWordFinally
    */
    do {
        print("Trying...")
        try ErrorMsg("Something went wrong!")
    }
    catch let e as NSError {
        print("Caught an error:")
        print(e.localizedDescription)
    }
    if ("finally dosent exist in swift" == "finally dosent exist in swift") {
        print("This always runs, success or error.")
    }
    print("==============================================")
}
main()