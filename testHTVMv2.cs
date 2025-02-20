
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
using System;
class Program
{


    public static string[] LoopParseFunc(string varString, string delimiter1 = "", string delimiter2 = "")
    {
        string[] items;
        if (string.IsNullOrEmpty(delimiter1) && string.IsNullOrEmpty(delimiter2))
        {
            // If no delimiters are provided, return an array of characters
            items = varString.ToCharArray().Select(c => c.ToString()).ToArray();
        }
        else
        {
            // Construct the regular expression pattern for splitting the string
            string pattern = "[" + Regex.Escape(delimiter1) + Regex.Escape(delimiter2) + "]+";
            // Split the string using the constructed pattern
            items = Regex.Split(varString, pattern);
        }
        return items;
    }

// Print function for various types
    public static void print(object value)
    {
        Console.WriteLine(value);
    }

public static void HTVM_Append<T>(List<T> arr, T value) {
    arr.Add(value);
}

public static int HTVM_Size<T>(List<T> arr) {
    return arr.Count;
}


static string func1(string var1) {
    return var1 + var1;
}
static void func2(string var1) {
    print(var1 + var1);
}
static void func3(string var1, string var2 = "hello") {
    print(var1 + " " + var2);
}
static void Main(string[] args) {
    print(func1("hi1"));
    func2("hi2");;
    func3("hi3");
    func3("hi3", "hello3");
    int var1 = 0;
    List<bool> myArr0 = new List<bool>();
    HTVM_Append(myArr0, true);
    HTVM_Append(myArr0, false);
    HTVM_Append(myArr0, true);
    List<int> myArr = new List<int> {5, 6, 7};
    for (int A_IndexA1 = 0; A_IndexA1 < 5 + 0; A_IndexA1++) {
        var1 = 6;
        HTVM_Append(myArr, A_IndexA1);
    }
    for (int A_IndexA2 = 0; A_IndexA2 < HTVM_Size(myArr) + 0; A_IndexA2++) {
        print(myArr[A_IndexA2]);
    }
    for (int A_IndexA3 = 0; A_IndexA3 < HTVM_Size(myArr0) + 0; A_IndexA3++) {
        print(myArr0[A_IndexA3]);
    }
    if (var1 == 6) {
        print(var1);
    }
    else if (var1 == 7) {
        print(var1);
    }
    string var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn";
    List<string> items4 = new List<string>(LoopParseFunc(var123, "\n", "\r"));
    for (int A_IndexA4 = 0; A_IndexA4 < items4.Count + 0; A_IndexA4++) {
        string A_LoopFieldA4 = items4[A_IndexA4 - 0];
        if (A_IndexA4 == 0) {
            print(A_IndexA4);
        }
        print(A_LoopFieldA4);
    }
    print("==================");
    string var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg";
    List<string> items5 = new List<string>(LoopParseFunc(var1234, ","));
    for (int A_IndexA5 = 0; A_IndexA5 < items5.Count + 0; A_IndexA5++) {
        string A_LoopFieldA5 = items5[A_IndexA5 - 0];
        if (A_IndexA5 == 0) {
            print(A_IndexA5);
        }
        print(A_LoopFieldA5);
    }
    print("==================");
    string var12345 = "hello";
    List<string> items6 = new List<string>(LoopParseFunc(var12345));
    for (int A_IndexA6 = 0; A_IndexA6 < items6.Count + 0; A_IndexA6++) {
        string A_LoopFieldA6 = items6[A_IndexA6 - 0];
        print(A_LoopFieldA6);
    }

}
}
