

List<String> LoopParseFunc(String varString, [String delimiter1 = "", String delimiter2 = ""]) {
    List<String> items = [];
    if (delimiter1.isEmpty && delimiter2.isEmpty) {
        // If no delimiters are provided, return a list of characters
        items.addAll(varString.split(''));
    } else {
        // Construct the regular expression pattern for splitting the string
        String pattern = "[$delimiter1$delimiter2]+";
        // Split the string using the constructed pattern
        items.addAll(varString.split(RegExp(pattern)));
    }
    return items;
}

// Print function for various types

void HTVM_Append<T>(List<T> arr, T value) {
  arr.add(value);
}

void HTVM_Pop<T>(List<T> arr) {
  if (arr.isNotEmpty) arr.removeLast();
}

int HTVM_Size<T>(List<T> arr) {
  return arr.length;
}

void HTVM_Insert<T>(List<T> arr, int index, T value) {
  arr.insert(index, value);
}

void HTVM_Remove<T>(List<T> arr, int index) {
    if (index >= 0 && index < arr.length) {
        arr.removeAt(index);
    }
}

int HTVM_IndexOf<T>(List<T> arr, T value) {
  return arr.indexOf(value);
}


// start
























void func0(String input) {
  print(input);
}




void func1(double var1, String var2, int var3, int var4, int var5, BigInt var6, int var7, String var8, bool var9, double var10, int var11, int var12, int var13, int var14) {
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
double func2(double var1) {
    return var1;
}
String func3(String var1) {
    return var1;
}
int func4(int var1) {
    return var1;
}
int func5(int var1) {
    return var1;
}
int func6(int var1) {
    return var1;
}
BigInt func7(BigInt var1) {
    return var1;
}
int func8(int var1) {
    return var1;
}
String func9(String var1) {
    return var1;
}
bool func10(bool var1) {
    return var1;
}
double func11(double var1) {
    return var1;
}
int func12(int var1) {
    return var1;
}
int func13(int var1) {
    return var1;
}
int func14(int var1) {
    return var1;
}
int func15(int var1) {
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
double var01 = 3.1234567891011;
String var02 = 'a';
int var03 = 25;
int var04 = 30;
int var05 = 35;
BigInt var06 = BigInt.parse("40");
int var07 = 100;
String var08 = "hello var ouside";
bool var09 = false;
double var010 = 3.14;
int var011 = 100;
int var012 = 200;
int var013 = 230;
int var014 = 80009;
void testFuncVars() {
    const String constStrTest0 = "constStrTest0";
    String constStrTest00 = "constStrTest00";
    print(constStrTest0);
    var items1 = LoopParseFunc(constStrTest00);
    for (int A_Index1 = 0; A_Index1 < items1.length; A_Index1++) {
        var A_LoopField1 = items1[A_Index1 - 0];
        print(A_LoopField1);
    }
}
const String constStrTest = "constStrTest";
String letStrTest = "letStrTest";
String? varStrTest = "varStrTest";
void main(List<String> arguments) {
    const String constStrTest1 = "constStrTest1";
    String letStrTest1 = "letStrTest1";
    String? varStrTest1 = "varStrTest1";
    print(letStrTest);
    print(varStrTest);
    print(letStrTest1);
    print(varStrTest1);
    var items2 = LoopParseFunc(constStrTest);
    for (int A_Index2 = 0; A_Index2 < items2.length; A_Index2++) {
        var A_LoopField2 = items2[A_Index2 - 0];
        print(A_LoopField2);
    }
    print("==========================================");
    print("==========================================");
    print("==========================================");
    var items3 = LoopParseFunc(constStrTest1);
    for (int A_Index3 = 0; A_Index3 < items3.length; A_Index3++) {
        var A_LoopField3 = items3[A_Index3 - 0];
        print(A_LoopField3);
    }
    print("==========================================");
    print("==========================================");
    print("==========================================");
    double? var_1;
    String? var_2;
    int? var_3;
    int? var_4;
    int? var_5;
    BigInt? var_6;
    int? var_7;
    String? var_8;
    bool? var_9;
    double? var_10;
    int? var_11;
    int? var_12;
    int? var_13;
    int? var_14;
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
    String str1 = "hello 123 hello2";
    var items6 = LoopParseFunc(str1, " ");
    for (int A_Index6 = 0; A_Index6 < items6.length; A_Index6++) {
        var A_LoopField6 = items6[A_Index6 - 0];
        print(A_LoopField6);
    }
    print("==================");
    var items7 = LoopParseFunc(str1);
    for (int A_Index7 = 0; A_Index7 < items7.length; A_Index7++) {
        var A_LoopField7 = items7[A_Index7 - 0];
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
    List<String> arr1 = ["hello1", "hello2"];
    List<bool> arr2 = [true, false];
    List<double> arr3 = [3.13, 3.14];
    List<int> arr4 = [1, 6, 2];
    List<String> arr5 = ["real STR"];
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
        throw Exception("Something went wrong!");
    }
    catch (e) {
        print("Caught an error:");
        print(e);
    }
    finally {
        print("This always runs, success or error.");
    }
    print("==============================================");
}