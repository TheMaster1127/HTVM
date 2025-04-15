package main
import (
"fmt"
)

func print(value interface{}) {
    fmt.Println(value)
}

func fstr(val interface{}) string {
    return fmt.Sprintf("%v", val)
}


func main() {
    // === Regular F-String Example ===
    var calculation int = 10 + 5
    var message string = "The result is: " + fstr(calculation) + ". Double is: " + fstr(calculation * 2) + ""
    print("Regular F-String:")
    print(message)
    print("=========================")
    // === Multiline String (Raw) Example ===
    var ascii_cat string = " /\\_/\\\n( o.o )\n > ^ <"
    print("Multiline String (Raw):")
    print(ascii_cat)
    print("=========================")
    // === Multiline F-String Example ===
    var userName string = "Alice"
    var items int = 3
    var price float64 = 19.99
    var order_summary string = "Order Summary for: " + fstr(userName) + "\n\nItems purchased: " + fstr(items) + "\nTotal cost: $" + fstr(items * price) + "\n\nThank you for your order!\nNewlines and indentation are preserved."
    print("Multiline F-String:")
    print(order_summary)
    print("=========================")
}