import java.util.ArrayList;
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

public static <T> void HTVM_Append(ArrayList<T> arr, T value) {
    arr.add(value);
}

public static <T> int HTVM_Size(ArrayList<T> arr) {
    return arr.size();
}


public static void main(String[] args) {
    int var1;
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
        print(myArr[A_Index2]);
    }
    for (int A_Index3 = 0; A_Index3 < HTVM_Size(myArr0) + 0; A_Index3++) {
        print(myArr0[A_Index3]);
    }
    print(var1);
    String var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn";
    List<String> items4 = LoopParseFunc(var123, "\n", "\r");
    for (A_LoopField4 : items4) {
        A_LoopField = items4[A_Index - 0]
        if (A_Index == 0) {
            print(A_Index);
        }
        print(A_LoopField);
    }
    print("==================");
    String var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg";
    List<String> items5 = LoopParseFunc(var1234, ",");
    for (A_LoopField5 : items5) {
        A_LoopField = items5[A_Index - 0]
        if (A_Index == 0) {
            print(A_Index);
        }
        print(A_LoopField);
    }
}
}
