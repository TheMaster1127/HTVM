
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


static string szdfxc0() {
    return "hi";
}
static void szdfxc(string var1 = "hi") {
    print(var1);
    print("hi2 void");
}
static void szdfxc1(int var0, string var1 = "hi", string var2 = "hi2") {
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
static void szdfxc2(string var1 = "hi", string var2 = "hi2") {
    print(var1);
    print(var2);
    print("hi2 void");
}


static void Main(string[] args) {
    

    print(szdfxc0());
    szdfxc();
    szdfxc1(5);
    szdfxc1(6, "hello");
    double var1;
    char var2;
    byte var3;
    ushort var4;
    uint var5;
    ulong var6;
    int var7;
    string var8;
    bool var9;
    float var10;
    sbyte var11;
    short var12;
    int var13;
    long var14;
    List<string> array1 = new List<string>();
    List<int> array2 = new List<int>();
    List<string> array3 = new List<string>();
    List<float> array4 = new List<float>();
    List<bool> array5 = new List<bool>();
    szdfxc2();
    szdfxc2("HI1");
    szdfxc2("HI1", "HI2");
    print("Hello, World!");
    for (int A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        print(A_Index1);
    }
}
}