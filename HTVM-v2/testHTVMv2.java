import java.util.ArrayList;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;
import java.util.*;
public class Main
{


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

public static <T> void HTVM_Append(ArrayList<T> arr, T value) {
    arr.add(value);
}

public static <T> int HTVM_Size(ArrayList<T> arr) {
    return arr.size();
}


public static String func1(String var1) {
    return var1 + var1;
}
public static void func2(String var1) {
    print(var1 + var1);
}
public static void func3(String var1, Object... __HTVM_V2_TO_JAVA_optionalParams__) {
    String var2 = "hello";
    if (__HTVM_V2_TO_JAVA_optionalParams__.length > 0) var2 = (String) __HTVM_V2_TO_JAVA_optionalParams__[0];
    print(var1 + " " + var2);
}
public static void main(String[] args) {
    print(func1("hi1"));
    func2("hi2");
    func3("hi3");
    func3("hi3", "hello3");
    int var1 = 0;
    ArrayList<Boolean> myArr0 = new ArrayList<>();
    HTVM_Append(myArr0, true);
    HTVM_Append(myArr0, false);
    HTVM_Append(myArr0, true);
    ArrayList<Integer> myArr = new ArrayList<>(List.of(5, 6, 7));
    for (int A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        var1 = 6;
        HTVM_Append(myArr, A_Index1);
    }
    for (int A_Index2 = 0; A_Index2 < HTVM_Size(myArr) + 0; A_Index2++) {
        print(myArr.get(A_Index2));
    }
    for (int A_Index3 = 0; A_Index3 < HTVM_Size(myArr0) + 0; A_Index3++) {
        print(myArr0.get(A_Index3));
    }
    if (var1 == 6) {
        print(var1);
    }
    else if (var1 == 7) {
        print(var1);
    }
    String var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn";
    String[] items4 = LoopParseFunc(var123, "\n", "\r");
    for (int A_Index4 = 0; A_Index4 < items4.length + 0; A_Index4++) {
        String A_LoopField4 = items4[A_Index4 - 0];
        if (A_Index4 == 0) {
            print(A_Index4);
        }
        print(A_LoopField4);
    }
    print("==================");
    String var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg";
    String[] items5 = LoopParseFunc(var1234, ",", "");
    for (int A_Index5 = 0; A_Index5 < items5.length + 0; A_Index5++) {
        String A_LoopField5 = items5[A_Index5 - 0];
        if (A_Index5 == 0) {
            print(A_Index5);
        }
        print(A_LoopField5);
    }
    print("==================");
    String var12345 = "hello";
    String[] items6 = LoopParseFunc(var12345, "", "");
    for (int A_Index6 = 0; A_Index6 < items6.length + 0; A_Index6++) {
        String A_LoopField6 = items6[A_Index6 - 0];
        print(A_LoopField6);
    }
}
}