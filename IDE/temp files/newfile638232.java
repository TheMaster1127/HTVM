import java.util.ArrayList;
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

public static <T> int HTVM_Size(ArrayList<T> arr) {
    return arr.size();
}


public static void main(String[] args) {
    ArrayList<Integer> arr123 = new ArrayList<>(List.of(1, 3, 5));
    for (int A_Index1 = 0; A_Index1 < HTVM_Size(arr123) + 0; A_Index1++) {
        print(arr123.get(A_Index1));
    }
    

}
}