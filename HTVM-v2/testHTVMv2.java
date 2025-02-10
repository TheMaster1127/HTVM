
import java.util.*;
public class Main
{


public class LoopParseFunc {
    public static String[] LoopParseFunc(String varString, String delimiter1, String delimiter2) {
        String[] items;
        if (delimiter1.isEmpty() && delimiter2.isEmpty()) {
            // If no delimiters are provided, return an array of characters
            items = varString.split("");
        } else {
            // Construct the regular expression pattern for splitting the string
            String pattern = "[" + Pattern.quote(delimiter1) + Pattern.quote(delimiter2) + "]+";
            // Split the string using the constructed pattern
            items = varString.split(pattern);
        }
        return items;
    }
}

// Print function for various types
    public static void print(Object value) {
        if (value instanceof String) {
            System.out.println(value);
        } else if (value instanceof Integer || value instanceof Float || value instanceof Double) {
            System.out.println(value.toString());
        } else if (value instanceof Boolean) {
            System.out.println((Boolean) value ? "true" : "false");
        } else {
            System.out.println("Unsupported type");
        }
    }


public static void main(String[] args) {
    String var1;
    var1 = "hello man whats up";
    String var2;
    var2 = "hello\nman\nwhats\rup";
    List<String> items1 = LoopParseFunc(var1, " ");
    for (A_LoopField1 : items1) {
        A_LoopField = items1[A_Index - 0]
        print(A_LoopField);
    }
    List<String> items2 = LoopParseFunc(var2, "\n", "\r");
    for (A_LoopField2 : items2) {
        A_LoopField = items2[A_Index - 0]
        print(A_LoopField);
    }
}
}