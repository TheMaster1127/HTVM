

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

int HTVM_Size<T>(List<T> arr) {
  return arr.length;
}


String func1(String var1) {
    return var1 + var1;
}
void func2(String var1) {
    print(var1 + var1);
}
void func3(String var1, [String var2 = "hello", String var3 = "hello", String var4 = "hello"]) {
    print(var1 + " " + var2 + " " + var3 + " " + var4);
}
void main(List<String> arguments) {
    print(func1("hi1"));
    func2("hi2");
    func3("hi3");
    func3("hi3", "hello3");
    func3("hi3", "hello3", "QWAESDRTFG");
    func3("hi3", "hello3", "QWAESDRTFG", "WAESDRFTG44444");
    int? var1;
    List<bool> myArr0 = [];
    HTVM_Append(myArr0, true);
    HTVM_Append(myArr0, false);
    HTVM_Append(myArr0, true);
    List<int> myArr = [5, 6, 7];
    for (int A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        var1 = 6;
        HTVM_Append(myArr, A_Index1);
    }
    for (int A_Index2 = 0; A_Index2 < HTVM_Size(myArr) + 0; A_Index2++) {
        print(myArr[A_Index2]);
    }
    for (int A_Index3 = 0; A_Index3 < HTVM_Size(myArr0) + 0; A_Index3++) {
        print(myArr0[A_Index3]);
    }
    if (var1 == 6) {
        print(var1);
    }
    else if (var1 == 7) {
        print(var1);
    }
    String var123 = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn";
    var items4 = LoopParseFunc(var123, "\n", "\r");
    for (int A_Index4 = 0; A_Index4 < items4.length; A_Index4++) {
        var A_LoopField4 = items4[A_Index4 - 0];
        if (A_Index4 == 0) {
            print(A_Index4);
        }
        print(A_LoopField4);
    }
    print("==================");
    String var1234 = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg";
    var items5 = LoopParseFunc(var1234, ",");
    for (int A_Index5 = 0; A_Index5 < items5.length; A_Index5++) {
        var A_LoopField5 = items5[A_Index5 - 0];
        if (A_Index5 == 0) {
            print(A_Index5);
        }
        print(A_LoopField5);
    }
    print("==================");
    String var12345 = "hello";
    var items6 = LoopParseFunc(var12345);
    for (int A_Index6 = 0; A_Index6 < items6.length; A_Index6++) {
        var A_LoopField6 = items6[A_Index6 - 0];
        print(A_LoopField6);
    }
}
