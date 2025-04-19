
using System.Collections.Generic;
using System;
class Program
{


// Print function for various types
    public static void print(object value)
    {
        Console.WriteLine(value);
    }

string fstr(object val) {
    return val?.ToString() ?? "null";
}


static void Main(string[] args) {
    // === Regular F-String Example ===
    int calculation = 10 + 5;
    string message = "The result is: " + fstr(calculation) + ". Double is: " + fstr(calculation * 2) + "";
    print("Regular F-String:");
    print(message);
    print("=========================");
    // === Multiline String (Raw) Example ===
    string ascii_cat = " /\\_/\\\n( o.o )\n > ^ <";
    print("Multiline String (Raw):");
    print(ascii_cat);
    print("=========================");
    // === Multiline F-String Example ===
    string userName = "Alice";
    int items = 3;
    float price = 19.99f;
    string order_summary = "Order Summary for: " + fstr(userName) + "\n\nItems purchased: " + fstr(items) + "\n\n\nTotal cost: $" + fstr(items * price) + "\n\nThank you for your order!\nNewlines and indentation are preserved.";
    print("Multiline F-String:");
    print(order_summary);
    print("=========================");

}
}