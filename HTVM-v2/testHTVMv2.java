
import java.util.*;
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
public static void szdfxc(Object... __HTVM_V2_TO_JAVA_optionalParams__) {
    String var1 = "hi";
    if (__HTVM_V2_TO_JAVA_optionalParams__.length > 0) var1 = (String) __HTVM_V2_TO_JAVA_optionalParams__[0];
    print(var1);
    print("hi2 void");
}
public static void szdfxc1(int var0, Object... __HTVM_V2_TO_JAVA_optionalParams__) {
    String var1 = "hi";
    String var2 = "hi2";
    if (__HTVM_V2_TO_JAVA_optionalParams__.length > 0) var1 = (String) __HTVM_V2_TO_JAVA_optionalParams__[0];
    if (__HTVM_V2_TO_JAVA_optionalParams__.length > 1) var2 = (String) __HTVM_V2_TO_JAVA_optionalParams__[1];
    print(var0);
    print(var1);
    print(var2);
    print("hi2 void");
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
/*
waedsfdsaeds
aedsf
saedsfxawdsfdfsaw
fddf
sefdf
saersdsaersdgfd
*/
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
public static void szdfxc2(Object... __HTVM_V2_TO_JAVA_optionalParams__) {
    String var1 = "hi";
    String var2 = "hi2";
    if (__HTVM_V2_TO_JAVA_optionalParams__.length > 0) var1 = (String) __HTVM_V2_TO_JAVA_optionalParams__[0];
    if (__HTVM_V2_TO_JAVA_optionalParams__.length > 1) var2 = (String) __HTVM_V2_TO_JAVA_optionalParams__[1];
    print(var1);
    print(var2);
    print("hi2 void");
}


public static void main(String[] args) {
    

    print(szdfxc0());
    szdfxc();
    szdfxc1(5);
    szdfxc1(6, "hello");
    double var1;
    char var2;
    byte  var3;
    short var4;
    int var5;
    long var6;
    int var7;
    String var8;
    boolean var9;
    float var10;
    byte var11;
    short var12;
    int var13;
    long var14;
    ArrayList<String> array1 = new ArrayList<>();
    ArrayList<Integer> array2 = new ArrayList<>();
    ArrayList<String> array3 = new ArrayList<>();
    ArrayList<Float> array4 = new ArrayList<>();
    ArrayList<Boolean> array5 = new ArrayList<>();
    szdfxc2();
    szdfxc2("HI1");
    szdfxc2("HI1", "HI2");
    print("Hello, World!");
    for (int A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        print(A_Index1);
    }
}
}
