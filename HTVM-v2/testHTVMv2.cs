
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

public static void HTVM_Pop<T>(List<T> arr) {
    if (arr.Count > 0) arr.RemoveAt(arr.Count - 1);
}

public static int HTVM_Size<T>(List<T> arr) {
    return arr.Count;
}

public static void HTVM_Insert<T>(List<T> arr, int index, T value) {
    arr.Insert(index, value);
}

public static void HTVM_Remove<T>(List<T> arr, int index)
{
    if (index >= 0 && index < arr.Count)
    {
        arr.RemoveAt(index);
    }
}

public static int HTVM_IndexOf<T>(List<T> arr, T value) {
    return arr.IndexOf(value);
}


// start










static void func0(string input) {
    Console.WriteLine(input);
}


















static void func1(double var1, char var2, byte var3, ushort var4, uint var5, ulong var6, int var7, string var8, bool var9, float var10, sbyte var11, short var12, int var13, long var14) {
    print(var1);
    print(var2);
    print(var3);
    print(var4);
    print(var5);
    print(var6);
    print(var7);
    print(var8);
    print(var9);
    print(var10);
    print(var11);
    print(var12);
    print(var13);
    print(var14);
}
static double func2(double var1) {
    return var1;
}
static char func3(char var1) {
    return var1;
}
static byte func4(byte var1) {
    return var1;
}
static ushort func5(ushort var1) {
    return var1;
}
static uint func6(uint var1) {
    return var1;
}
static ulong func7(ulong var1) {
    return var1;
}
static int func8(int var1) {
    return var1;
}
static string func9(string var1) {
    return var1;
}
static bool func10(bool var1) {
    return var1;
}
static float func11(float var1) {
    return var1;
}
static sbyte func12(sbyte var1) {
    return var1;
}
static short func13(short var1) {
    return var1;
}
static int func14(int var1) {
    return var1;
}
static long func15(long var1) {
    return var1;
}
/*
this
is
a
multy
line
comment
*/
// outside vars
static double var01 = 3.1234567891011;
static char var02 = 'a';
static byte var03 = 25;
static ushort var04 = 30;
static uint var05 = 35;
static ulong var06 = 40UL;
static int var07 = 100;
static string var08 = "hello var ouside";
static bool var09 = false;
static float var010 = 3.14f;
static sbyte var011 = 100;
static short var012 = 200;
static int var013 = 230;
static long var014 = 80009L;
static void testFuncVars() {
    const string constStrTest0 = "constStrTest0";
    string constStrTest00 = "constStrTest00";
    print(constStrTest0);
    List<string> items1 = new List<string>(LoopParseFunc(constStrTest00));
    for (int A_Index1 = 0; A_Index1 < items1.Count + 0; A_Index1++) {
        string A_LoopField1 = items1[A_Index1 - 0];
        print(A_LoopField1);
    }
}
const string constStrTest = "constStrTest";
static string letStrTest = "letStrTest";
static string varStrTest = "varStrTest";
static void Main(string[] args) {
    const string constStrTest1 = "constStrTest1";
    string letStrTest1 = "letStrTest1";
    string varStrTest1 = "varStrTest1";
    print(letStrTest);
    print(varStrTest);
    print(letStrTest1);
    print(varStrTest1);
    List<string> items2 = new List<string>(LoopParseFunc(constStrTest));
    for (int A_Index2 = 0; A_Index2 < items2.Count + 0; A_Index2++) {
        string A_LoopField2 = items2[A_Index2 - 0];
        print(A_LoopField2);
    }
    print("==========================================");
    print("==========================================");
    print("==========================================");
    List<string> items3 = new List<string>(LoopParseFunc(constStrTest1));
    for (int A_Index3 = 0; A_Index3 < items3.Count + 0; A_Index3++) {
        string A_LoopField3 = items3[A_Index3 - 0];
        print(A_LoopField3);
    }
    print("==========================================");
    print("==========================================");
    print("==========================================");
    double var_1 = 0.0;
    char var_2 = 'a';
    byte var_3 = 0;
    ushort var_4 = 0;
    uint var_5 = 0;
    ulong var_6 = 0UL;
    int var_7 = 0;
    string var_8 = "";
    bool var_9 = false;
    float var_10 = 0.0f;
    sbyte var_11 = 0;
    short var_12 = 0;
    int var_13 = 0;
    long var_14 = 0L;
    func1(var01, var02, var03, var04, var05, var06, var07, var08, var09, var010, var011, var012, var013, var014);
    var_1 = func2(var01);
    var_2 = func3(var02);
    var_3 = func4(var03);
    var_4 = func5(var04);
    var_5 = func6(var05);
    var_6 = func7(var06);
    var_7 = func8(var07);
    var_8 = func9(var08);
    var_9 = func10(var09);
    var_10 = func11(var010);
    var_11 = func12(var011);
    var_12 = func13(var012);
    var_13 = func14(var013);
    var_14 = func15(var014);
    print(var_1);
    print(var_2);
    print(var_3);
    print(var_4);
    print(var_5);
    print(var_6);
    print(var_7);
    print(var_8);
    print(var_9);
    print(var_10);
    print(var_11);
    print(var_12);
    print(var_13);
    print(var_14);
    // start
    

    

    

    

    

    func0("Hello World");
    

    

    

    

    

    

    

    

    

    print("==================================");
    for (int A_Index4 = 0; A_Index4 < 5 + 0; A_Index4++) {
        if (A_Index4 == 0) {
            print(A_Index4);
        }
        else if (A_Index4 == 1) {
            print(A_Index4);
        }
        else if (A_Index4 == 2) {
            print(A_Index4);
        }
        else if (A_Index4 == 3) {
            print(A_Index4);
        }
        else if (A_Index4 == 4) {
            print(A_Index4);
        }
        else if (A_Index4 == 5) {
            print(A_Index4);
        } else {
            print("HOW????");
            print(A_Index4);
        }
    }
    bool vars1 = false;
    int vars2 = 0;
    while (vars1 == false) {
        vars2++;
        print(vars2);
        if (vars2 == 6) {
            vars1 = true;
        }
    }
    for (int A_Index5 = 0; ; A_Index5++) {
        if (A_Index5 == 6) {
            break;
        } else {
            continue;
        }
        // this is only for lua
    }
    string str1 = "hello 123 hello2";
    List<string> items6 = new List<string>(LoopParseFunc(str1, " "));
    for (int A_Index6 = 0; A_Index6 < items6.Count + 0; A_Index6++) {
        string A_LoopField6 = items6[A_Index6 - 0];
        print(A_LoopField6);
    }
    print("==================");
    List<string> items7 = new List<string>(LoopParseFunc(str1));
    for (int A_Index7 = 0; A_Index7 < items7.Count + 0; A_Index7++) {
        string A_LoopField7 = items7[A_Index7 - 0];
        print(A_LoopField7);
        if (A_LoopField7 == "2") {
            break;
        } else {
            continue;
        }
    }
    /*
    keyWordArrayAppend
    keyWordArrayPop
    keyWordArraySize
    keyWordArrayInsert
    keyWordArrayRemove
    keyWordArrayIndexOf
    keyWordArrayDefinition
    keyWordArrayOfIntegersDefinition
    keyWordArrayOfStringsDefinition
    keyWordArrayOfFloatingPointNumbersDefinition
    keyWordArrayOfBooleansDefinition
    */
    List<string> arr1 = new List<string> {"hello1", "hello2"};
    List<bool> arr2 = new List<bool> {true, false};
    List<double> arr3 = new List<double> {3.13, 3.14};
    List<int> arr4 = new List<int> {1, 6, 2};
    List<string> arr5 = new List<string> {"real STR"};
    // Array operations
    HTVM_Append(arr1, "hello3");
    int sizeArr1 = HTVM_Size(arr1);
    print("the size of arr1 is:");
    print(sizeArr1);
    HTVM_Insert(arr1, 1, "hello?????");
    HTVM_Remove(arr1, 0);
    int idx1 = HTVM_IndexOf(arr1, "hello2");
    print("the index of arr1 for hello2 is:");
    print(idx1);
    HTVM_Pop(arr1);
    for (int A_Index8 = 0; A_Index8 < HTVM_Size(arr1) + 0; A_Index8++) {
        print(arr1[A_Index8]);
    }
    HTVM_Append(arr2, true);
    int sizeArr2 = HTVM_Size(arr2);
    print("the size of arr2 is:");
    print(sizeArr2);
    HTVM_Insert(arr2, 1, false);
    HTVM_Remove(arr2, 0);
    int idx2 = HTVM_IndexOf(arr2, true);
    print("the index of arr2 for true is:");
    print(idx2);
    HTVM_Pop(arr2);
    for (int A_Index9 = 0; A_Index9 < HTVM_Size(arr2) + 0; A_Index9++) {
        print(arr2[A_Index9]);
    }
    HTVM_Append(arr3, 6.489);
    int sizeArr3 = HTVM_Size(arr3);
    print("the size of arr3 is:");
    print(sizeArr3);
    HTVM_Insert(arr3, 1, 1.556);
    HTVM_Remove(arr3, 0);
    int idx3 = HTVM_IndexOf(arr3, 3.14);
    print("the index of arr3 for 3.14 is:");
    print(idx3);
    HTVM_Pop(arr3);
    for (int A_Index10 = 0; A_Index10 < HTVM_Size(arr3) + 0; A_Index10++) {
        print(arr3[A_Index10]);
    }
    HTVM_Append(arr4, 69);
    int sizeArr4 = HTVM_Size(arr4);
    print("the size of arr4 is:");
    print(sizeArr4);
    HTVM_Insert(arr4, 1, 420);
    HTVM_Remove(arr4, 0);
    int idx4 = HTVM_IndexOf(arr4, 69);
    print("the index of arr4 for 69 is:");
    print(idx4);
    HTVM_Pop(arr4);
    for (int A_Index11 = 0; A_Index11 < HTVM_Size(arr4) + 0; A_Index11++) {
        print(arr4[A_Index11]);
    }
    HTVM_Append(arr5, "hello3real");
    int sizeArr5 = HTVM_Size(arr5);
    print("the size of arr5 is:");
    print(sizeArr5);
    HTVM_Insert(arr5, 1, "hello?real????");
    HTVM_Remove(arr5, 0);
    int idx5 = HTVM_IndexOf(arr5, "hello3real");
    print("the index of arr5 for hello3real is:");
    print(idx5);
    HTVM_Pop(arr5);
    for (int A_Index12 = 0; A_Index12 < HTVM_Size(arr5) + 0; A_Index12++) {
        print(arr5[A_Index12]);
    }
    /*
    keyWordThrow
    keyWordErrorMsg
    keyWordTry
    keyWordCatch
    keyWordFinally
    */
    try {
        print("Trying...");
        throw new Exception("Something went wrong!");
    }
    catch (Exception e) {
        print("Caught an error:");
        print(e.Message);
    }
    finally {
        print("This always runs, success or error.");
    }
    print("==============================================");

}
}
