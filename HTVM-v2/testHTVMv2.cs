
using System.Collections.Generic;
using System;
class Program
{


public string[] LoopParseFunc(string varString, string delimiter1 = "", string delimiter2 = "")
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
    string var1;
    var1 = "hello man whats up";
    string var2;
    var2 = "hello\nman\nwhats\rup";
    List<string> items1 = LoopParseFunc(var1, " ");
    foreach (var A_LoopField1 in items1) {
        A_LoopField1 = items1[A_Index1 - 0]
        print(A_LoopField);
    }
    List<string> items2 = LoopParseFunc(var2, "\n", "\r");
    foreach (var A_LoopField2 in items2) {
        A_LoopField2 = items2[A_Index2 - 0]
        print(A_LoopField);
    }
}
}