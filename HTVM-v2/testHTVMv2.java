
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


public static String szdfxc0() {
    return "hi";
}
public static void szdfxc(String var1 = "hi") {
    print(var1);
    print("hi2 void");
}
public static void szdfxc1(int var0, String var1 = "hi", String var2 = "hi2") {
    print(var0);
    print(var1);
    print(var2);
    print("hi2 void");
}
public static void main(String[] args) {
    print(szdfxc0());
    szdfxc();
    szdfxc1(5);
    szdfxc1(6, "hello");
    print("Hello, World!");
    for (int A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        print(A_Index1);
    }
}
}