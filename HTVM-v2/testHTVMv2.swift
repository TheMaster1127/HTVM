import Foundation


func LoopParseFunc(_ varString: String, _ delimiter1: String = "", _ delimiter2: String = "") -> [String] {
    var items: [String] = []
    if delimiter1.isEmpty && delimiter2.isEmpty {
        // If no delimiters are provided, return an array of characters
        items = Array(varString).map { String($0) }
    } else {
        // Construct the regular expression pattern for capturing content
        let pattern = "(?<=^|[\n\r])([^\\n\\r]+)(?=[\n\r]|$)"
        
        // Split the string using the constructed pattern
        let regex = try! NSRegularExpression(pattern: pattern, options: [])
        let range = NSRange(location: 0, length: varString.utf16.count)
        items = regex.matches(in: varString, options: [], range: range).map {
            (varString as NSString).substring(with: $0.range)
        }
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


func main() {
    var var1: Int
    var myArr0: [Bool] = []
    HTVM_Append(&myArr0, true)
    HTVM_Append(&myArr0, false)
    HTVM_Append(&myArr0, true)
    var myArr: [Int] = [5, 6, 7]
    for A_Index1 in 0 ..< 5 + 0 {
        var1 = 6
        HTVM_Append(&myArr, A_Index1)
    }
    for A_Index2 in 0 ..< HTVM_Size(myArr) + 0 {
        print(myArr[A_Index2])
    }
    for A_Index3 in 0 ..< HTVM_Size(myArr0) + 0 {
        print(myArr0[A_Index3])
    }
    print(var1)
    var var123: String = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn"
    var items4 = LoopParseFunc(var123, "\n", "\r")
    for (A_Index4 , A_LoopField4) in items4.enumerated() {
        if (A_Index4 == 0) {
            print(A_Index4)
        }
        print(A_LoopField4)
    }
    print("==================")
    var var1234: String = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg"
    var items5 = LoopParseFunc(var1234, ",")
    for (A_Index5 , A_LoopField5) in items5.enumerated() {
        if (A_Index5 == 0) {
            print(A_Index5)
        }
        print(A_LoopField5)
    }
}
main()