
public class Main
{


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
    print("Hello, World!");
    for (int A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
    }
    }
}