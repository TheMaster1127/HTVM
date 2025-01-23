
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
    if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    } else {
        print(5+5);
    }
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    try {
        throw new Exception("this is an ERROR HTVM v2");
    }
    catch (Exception ee) {
        print(ee.Message);
    }
    finally {
        print("finally finally finally finally");
    }
    }
}