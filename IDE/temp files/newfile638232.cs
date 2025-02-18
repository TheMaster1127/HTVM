
using System.Collections.Generic;
using System;
class Program
{


// Print function for various types
    public static void print(object value)
    {
        Console.WriteLine(value);
    }

public static int HTVM_Size<T>(List<T> arr) {
    return arr.Count;
}


static void Main(string[] args) {
    static List<int> arr123 = new List<int> {1, 3, 5};
    for (int A_Index1 = 0; A_Index1 < HTVM_Size(arr123) + 0; A_Index1++) {
        print(arr123[A_Index1]);
    }
    

}
}