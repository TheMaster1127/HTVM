
using System.Collections.Generic;
using System;
class Program
{


// Print function for various types
    public static void print(object value)
    {
        if (value is string)
            Console.WriteLine(value);
        else if (value is int || value is float || value is double)
            Console.WriteLine(value.ToString());
        else if (value is bool)
            Console.WriteLine((bool)value ? "True" : "False");
        else
            Console.WriteLine("Unsupported type");
    }

public static void HTVM_Append<T>(List<T> arr, T value) {
    arr.Add(value);
}

public static int HTVM_Size<T>(List<T> arr) {
    return arr.Count;
}


static void Main(string[] args) {
    for (int A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        print("hello HTVM v2");
        print("hello HTVM\nv2");
        print(A_Index1);
        for (int A_Index2 = 0; A_Index2 < 5 + 0; A_Index2++) {
            print("hello HTVM v2");
            print("hello HTVM\nv2");
            for (int A_Index3 = 0; A_Index3 < 5 + 0; A_Index3++) {
                print("hello HTVM v2");
                print("hello HTVM\nv2");
                print(A_Index3);
            }
            print(A_Index2);
        }
    }
    print(5+5 != 5 !SZDS() + "A+-+--+ != ADSF" + "WSADFD" + "qwadsf" + adsf >= 3 <= qwerd > qwretr < wdsdf = 5 != 8);
    print("QWADSDF" + "qawdsf" || var1 ! var4 + "ASDFX" + !ADSFD("Qwads" + "QASD" + "aszd" < 6) ? false : true || null && false);
    print(HTVM_Size(aszd) HTVM_Append(aszd, HTVM_Size(aszd)));
    Avar123 = StringTrimRight(STRRAWSD, 1);
    if(var1 == 5 && var2w3erf < 6);
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var1 = 1
    print((var1 == 1) ? "hello" : "bye");
    var1 = 0
    print((var1 == 1) ? "hello" : "bye");
    }
}