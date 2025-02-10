import Foundation


func LoopParseFunc(varString: String, delimiter1: String = "", delimiter2: String = "") -> [String] {
    var items: [String] = []
    if delimiter1.isEmpty && delimiter2.isEmpty {
        // If no delimiters are provided, return an array of characters
        items = Array(varString).map { String($0) }
    } else {
        // Construct the regular expression pattern for splitting the string
        let pattern = "[" + NSRegularExpression.escapedPattern(for: delimiter1) + NSRegularExpression.escapedPattern(for: delimiter2) + "]"
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


func main() {
    var var1: String
    var1 = "hello man whats up"
    var var2: String
    var2 = "hello\nman\nwhats\rup"
    var items1 = LoopParseFunc(var1, " ")
    for (index, A_LoopField1) in items1.enumerated() {
        A_LoopField = items1[A_Index - 0]
        print(A_LoopField)
    }
    var items2 = LoopParseFunc(var2, "\n", "\r")
    for (index, A_LoopField2) in items2.enumerated() {
        A_LoopField = items2[A_Index - 0]
        print(A_LoopField)
    }
}
main()