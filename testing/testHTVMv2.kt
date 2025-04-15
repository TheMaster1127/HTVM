

// Print function for various types
fun print(value: Any) {
  println(value)
}

fun fstr(val: Any?): String {
    return val.toString()
}


fun main(args: Array<String>) {
    // === Regular F-String Example ===
    var calculation: Int = 10 + 5;
    var message: String = "The result is: " + fstr(calculation) + ". Double is: " + fstr(calculation * 2) + "";
    print("Regular F-String:")
    print(message)
    print("=========================")
    // === Multiline String (Raw) Example ===
    var ascii_cat: String = " /\\_/\\\n( o.o )\n > ^ <";
    print("Multiline String (Raw):")
    print(ascii_cat)
    print("=========================")
    // === Multiline F-String Example ===
    var userName: String = "Alice";
    var items: Int = 3;
    var price: Float = 19.99f;
    var order_summary: String = "Order Summary for: " + fstr(userName) + "\n\nItems purchased: " + fstr(items) + "\nTotal cost: $" + fstr(items * price) + "\n\nThank you for your order!\nNewlines and indentation are preserved.";
    print("Multiline F-String:")
    print(order_summary)
    print("=========================")
}