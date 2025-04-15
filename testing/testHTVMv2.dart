

// Print function for various types

String fstr(dynamic val) {
  return val.toString();
}


void main(List<String> arguments) {
    // === Regular F-String Example ===
    int calculation = 10 + 5;
    String message = "The result is: " + fstr(calculation) + ". Double is: " + fstr(calculation * 2) + "";
    print("Regular F-String:");
    print(message);
    print("=========================");
    // === Multiline String (Raw) Example ===
    String ascii_cat = " /\\_/\\\n( o.o )\n > ^ <";
    print("Multiline String (Raw):");
    print(ascii_cat);
    print("=========================");
    // === Multiline F-String Example ===
    String userName = "Alice";
    int items = 3;
    double price = 19.99;
    String order_summary = "Order Summary for: " + fstr(userName) + "\n\nItems purchased: " + fstr(items) + "\nTotal cost: $" + fstr(items * price) + "\n\nThank you for your order!\nNewlines and indentation are preserved.";
    print("Multiline F-String:");
    print(order_summary);
    print("=========================");
}