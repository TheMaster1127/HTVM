
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
    }
}