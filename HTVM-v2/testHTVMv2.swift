import Foundation


// Print function for various types

// Function that throws an error with a string message
func ErrorMsg(_ message: String) throws {
    throw NSError(domain: "", code: 0, userInfo: [NSLocalizedDescriptionKey: message])
}


func main() {
    do {
        try ErrorMsg("this is an ERROR HTVM v2")
    }
    catch let ee as NSError {
        print(ee.localizedDescription)
    }
    if ("finally dosent exist in swift" == "finally dosent exist in swift") {
        print("finally finally finally finally")
    }
}
main()
