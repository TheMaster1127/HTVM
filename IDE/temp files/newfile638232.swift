import Foundation


// Print function for various types

func HTVM_Size<T>(_ arr: [T]) -> Int {
    return arr.count
}


func main() {
    var arr123: [Int] = [1, 3, 5]
    for A_Index1 in 0 ..< HTVM_Size(arr123) + 0 {
        print(arr123[A_Index1])
    }
    

}
main()