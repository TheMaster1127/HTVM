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

func HTVM_Size<T>(_ arr: [T]) -> Int {
    return arr.count
}


func func1(_ var1: String) -> String {
    return var1 + var1
}
func func2(_ var1: String) {
    print(var1 + var1)
}
func func3(_ var1: String, _ var2: String = "hello") {
    print(var1 + " " + var2)
}
func main() {
    print(func1("hi1"))
    func2("hi2")
    func3("hi3")
    func3("hi3", "hello3")
    var var1: Int = 0
    var myArr0: [Bool] = []
    HTVM_Append(&myArr0, true)
    HTVM_Append(&myArr0, false)
    HTVM_Append(&myArr0, true)
    var myArr: [Int] = [5, 6, 7]
    for A_IndexA1 in 0 ..< 5 + 0 {
        var1 = 6
        HTVM_Append(&myArr, A_IndexA1)
    }
    for A_IndexA2 in 0 ..< HTVM_Size(myArr) + 0 {
        print(myArr[A_IndexA2])
    }
    for A_IndexA3 in 0 ..< HTVM_Size(myArr0) + 0 {
        print(myArr0[A_IndexA3])
    }
    if var1 == 6 {
        print(var1)
    }
    else if var1 == 7 {
        print(var1)
    }
    var var123: String = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn"
    var items4 = LoopParseFunc(var123, "\n", "\r")
    for (A_IndexA4 , A_LoopFieldA4) in items4.enumerated() {
        if A_IndexA4 == 0 {
            print(A_IndexA4)
        }
        print(A_LoopFieldA4)
    }
    print("==================")
    var var1234: String = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg"
    var items5 = LoopParseFunc(var1234, ",")
    for (A_IndexA5 , A_LoopFieldA5) in items5.enumerated() {
        if A_IndexA5 == 0 {
            print(A_IndexA5)
        }
        print(A_LoopFieldA5)
    }
    print("==================")
    var var12345: String = "hello"
    var items6 = LoopParseFunc(var12345)
    for (A_IndexA6 , A_LoopFieldA6) in items6.enumerated() {
        print(A_LoopFieldA6)
    }
}
main()