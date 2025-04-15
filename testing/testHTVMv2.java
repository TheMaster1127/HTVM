
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;
import java.util.*;
public class Main
{


// Print function for various types
    public static void print(Object value) {
        System.out.println(value);
    }

public static String fstr(Object val) {
    return String.valueOf(val);
}


public static void main(String[] args) {
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
    float price = 19.99f;
    String order_summary = "Order Summary for: " + fstr(userName) + "\n\nItems purchased: " + fstr(items) + "\nTotal cost: $" + fstr(items * price) + "\n\nThank you for your order!\nNewlines and indentation are preserved.";
    print("Multiline F-String:");
    print(order_summary);
    print("=========================");

}
}