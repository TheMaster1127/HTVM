
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


static string szdfxc0() {
    return "hi";
}
static void szdfxc() {
    print("hi2 void");
}
static void Main(string[] args) {
    print(szdfxc0());
    szdfxc();
    print("Hello, World!");
    for (int A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        print(A_Index1);
    }
    }
}
