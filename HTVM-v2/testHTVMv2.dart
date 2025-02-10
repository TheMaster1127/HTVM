

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


void main(List<String> arguments) {
    String? var1;
    var1 = "hello man whats up";
    String? var2;
    var2 = "hello\nman\nwhats\rup";
    var items1 = LoopParseFunc(var1, " ");
    for (int A_Index1 = 0; A_Index1 < items1.length; A_Index1++) {
        var A_LoopField1 = items1[A_Index1 - 0];
        print(A_LoopField1);
    }
    var items2 = LoopParseFunc(var2, "\n", "\r");
    for (int A_Index2 = 0; A_Index2 < items2.length; A_Index2++) {
        var A_LoopField2 = items2[A_Index2 - 0];
        print(A_LoopField2);
    }
}
