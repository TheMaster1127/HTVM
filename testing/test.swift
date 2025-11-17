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

func STR(_ value: Any) -> String {
    if let value = value as? Int {
        return String(value)
    } else if let value = value as? Float {
        return String(value)
    } else if let value = value as? Double {
        return String(value)
    } else if let value = value as? Bool {
        return value ? "1" : "0"
    } else if let value = value as? String {
        return value
    } else {
        return "\(value)"
    }
}

func HTVM_Append<T>(_ arr: inout [T], _ value: T) {
    arr.append(value)
}

func HTVM_Size<T>(_ arr: [T]) -> Int {
    return arr.count
}

// Function that throws an error with a string message
func ErrorMsg(_ message: String) throws {
    throw NSError(domain: "", code: 0, userInfo: [NSLocalizedDescriptionKey: message])
}


// This is a preview of your language and how it will look.
// Here's how types will appear if you only define them:
var varName1: Int = 0
var varName2: String = ""
var varName3: Bool = false
var varName4: Float = 0.00
var varName5: Int8 = 0
var varName6: Int16 = 0
var varName7: Int32 = 0
var varName8: Int64 = 0
// Alternatively, you can define them like this:
var varName9: Int = 34
// Here's how to define a function with static types when converting to statically typed languages like:
// TypeScript, C++, Go, C#, Java, Kotlin, Nim, Swift, and Dart.
// However, even if you're not targeting a statically typed language (e.g. JavaScript or Python),
// the types will be stripped away automatically and the function will still work as expected.
func funcName1(_ paramVar1: Int, _ paramVar2: String = "", _ paramVar3: Bool = false, _ paramVar4: Float = 1.5) {
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
func main() {
    funcName1(varName9)
    // this is how a while loop works in your lang
    var var1: Bool = false
    while (var1 == false) {
        print("we are inside the while loop")
        var1 = true
    }
    print("we are outside the while loop")
    // this is how to use a loop whit arrays
    var array123: [String] = ["hey"]
    HTVM_Append(&array123, "hello")
    HTVM_Append(&array123, "how")
    HTVM_Append(&array123, "are")
    HTVM_Append(&array123, "you")
    HTVM_Append(&array123, "doing")
    for A_Index1 in 0 ..< HTVM_Size(array123) {
        print("iteration: " + STR(A_Index1))
        print("Item: " + array123[A_Index1])
    }
    print("this is how the escape char looks like \nthis is a new line")
    /*
    this is a comment block
    this is a comment block
    */
    // this is how to use an AutoHotKey like Loop
    for A_Index2 in 0 ..< 10 {
        if (A_Index2 % 2 == 0) {
            continue
        }
        print(A_Index2)
    }
    // this is how to use an AutoHotKey like infinite Loop
    for A_Index3 in 0... {
        if (A_Index3 == 5) {
            break
        } else {
            print(A_Index3)
        }
    }
    // this is how to use an AutoHotKey like Loop, parse
    var someText: String = "hello how are you doing\ntoday we are good."
    var items4 = LoopParseFunc(someText, " ", "\n")
    for (A_Index4 , A_LoopField4) in items4.enumerated() {
        print(A_LoopField4)
    }
    // Error Handling
    do {
        try ErrorMsg("Something went wrong!")
    }
    catch let e as NSError {
        print(e.localizedDescription)
    }
    if ("finally dosent exist in swift" == "finally dosent exist in swift") {
        print("Finally block executed")
    }
    

}
main()