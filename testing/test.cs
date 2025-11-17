
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

public static string STR(object value) {
    if (value is int)
        return value.ToString();
    else if (value is long)
        return value.ToString();
    else if (value is float)
        return value.ToString();
    else if (value is double)
        return value.ToString();
    else if (value is bool)
        return (bool)value ? "1" : "0";
    else if (value is string)
        return (string)value;
    else
        return value.ToString();
}

public static void HTVM_Append<T>(List<T> arr, T value) {
    arr.Add(value);
}

public static int HTVM_Size<T>(List<T> arr) {
    return arr.Count;
}


// This is a preview of your language and how it will look.
// Here's how types will appear if you only define them:
int varName1 = 0;
string varName2 = "";
bool varName3 = false;
float varName4 = 0.0f;
sbyte varName5 = 0;
short varName6 = 0;
int varName7 = 0;
long varName8 = 0L;
// Alternatively, you can define them like this:
int varName9 = 34;
// Here's how to define a function with static types when converting to statically typed languages like:
// TypeScript, C++, Go, C#, Java, Kotlin, Nim, Swift, and Dart.
// However, even if you're not targeting a statically typed language (e.g. JavaScript or Python),
// the types will be stripped away automatically and the function will still work as expected.
static void funcName1(int paramVar1, string paramVar2 = "", bool paramVar3 = false, float paramVar4 = 1.5f) {
    // This is how the global keyword works if we convert to Python and AutoHotKey.
    // But even if we don't, it will just be removed, so you can add it if you want to convert to Python and AutoHotKey as well.
    // Here's how if, else if, and else statements will look:
    if (varName1 == paramVar1) {
        print("varName1 is equal to paramVar1");
    }
    else if (varName1 != paramVar1 || varName1 <= paramVar1) {
        print("varName1 is less than or equal to paramVar1");
    } else {
        print("varName1 is NOT less than or equal to paramVar1 or something else");
    }
    // this is how the return keyword will look like in your lang
    return;
}
// This is where the main function will start. It's just a label, so don't worry.
static void Main(string[] args) {
    funcName1(varName9);
    // this is how a while loop works in your lang
    bool var1 = false;
    while (var1 == false) {
        print("we are inside the while loop");
        var1 = true;
    }
    print("we are outside the while loop");
    // this is how to use a loop whit arrays
    List<string> array123 = new List<string> {"hey"};
    HTVM_Append(array123, "hello");
    HTVM_Append(array123, "how");
    HTVM_Append(array123, "are");
    HTVM_Append(array123, "you");
    HTVM_Append(array123, "doing");
    for (int A_Index1 = 0; A_Index1 < HTVM_Size(array123); A_Index1++) {
        print("iteration: " + STR(A_Index1));
        print("Item: " + array123[A_Index1]);
    }
    print("this is how the escape char looks like \nthis is a new line");
    /*
    this is a comment block
    this is a comment block
    */
    // this is how to use an AutoHotKey like Loop
    for (int A_Index2 = 0; A_Index2 < 10; A_Index2++) {
        if (A_Index2 % 2 == 0) {
            continue;
        }
        print(A_Index2);
    }
    // this is how to use an AutoHotKey like infinite Loop
    for (int A_Index3 = 0; ; A_Index3++) {
        if (A_Index3 == 5) {
            break;
        } else {
            print(A_Index3);
        }
    }
    // this is how to use an AutoHotKey like Loop, parse
    string someText = "hello how are you doing\ntoday we are good.";
    List<string> items4 = new List<string>(LoopParseFunc(someText, " ", "\n"));
    for (int A_Index4 = 0; A_Index4 < items4.Count; A_Index4++) {
        string A_LoopField4 = items4[A_Index4 - 0];
        print(A_LoopField4);
    }
    // Error Handling
    try {
        throw new Exception("Something went wrong!");
    }
    catch (Exception e) {
        print(e.Message);
    }
    finally {
        print("Finally block executed");
    }
    

}
}