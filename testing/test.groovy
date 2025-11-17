

def LoopParseFunc(String varString, String delimiter1 = "", String delimiter2 = "") {
    def items = []
    if (delimiter1 == "" && delimiter2 == "") {
        // If no delimiters are provided, return an array of characters
        items = varString.toList()
    } else {
        // Construct the regular expression pattern for splitting the string
        def pattern = "[${delimiter1}${delimiter2}]"
        // Split the string using the constructed pattern
        items = varString.split(pattern)
    }
    return items
}

// Print function
def print = { message ->
    System.out.println(message)
}

// Convert various types to String
String STR(int value) {
    return value.toString()
}
// Convert various types to String
String STR(long value) {
    return value.toString()
}
String STR(float value) {
    return value.toString()
}
String STR(double value) {
    return value.toString()
}
String STR(boolean value) {
    return value ? "1" : "0"
}
String STR(String value) {
    return value
}

def HTVM_Append(arr, value) {
    arr.add(value)
}

def HTVM_Size(arr) {
    return arr.size()
}


// This is a preview of your language and how it will look.
// Here's how types will appear if you only define them:
varName1 = null
varName2 = null
varName3 = null
varName4 = null
varName5 = null
varName6 = null
varName7 = null
varName8 = null
// Alternatively, you can define them like this:
varName9 = 34
// Here's how to define a function with static types when converting to statically typed languages like:
// TypeScript, C++, Go, C#, Java, Kotlin, Nim, Swift, and Dart.
// However, even if you're not targeting a statically typed language (e.g. JavaScript or Python),
// the types will be stripped away automatically and the function will still work as expected.
def funcName1(paramVar1, paramVar2 = "", paramVar3 = false, paramVar4 = 1.5) {
    // This is how the global keyword works if we convert to Python and AutoHotKey.
    // But even if we don't, it will just be removed, so you can add it if you want to convert to Python and AutoHotKey as well.
    // Here's how if, else if, and else statements will look:
    if ((varName1 == paramVar1)) {
        print("varName1 is equal to paramVar1")
    }
    else if ((varName1 != paramVar1 || varName1 <= paramVar1)) {
        print("varName1 is less than or equal to paramVar1")
    } else {
        print("varName1 is NOT less than or equal to paramVar1 or something else")
    }
    // this is how the return keyword will look like in your lang
    return;
}
// This is where the main function will start. It's just a label, so don't worry.
funcName1(varName9)
// this is how a while loop works in your lang
var1 = false
while ((var1 == false)) {
    print("we are inside the while loop")
    var1 = true
}
print("we are outside the while loop")
// this is how to use a loop whit arrays
array123 = ["hey"]
HTVM_Append(array123, "hello")
HTVM_Append(array123, "how")
HTVM_Append(array123, "are")
HTVM_Append(array123, "you")
HTVM_Append(array123, "doing")
for (A_Index1 in 0..<HTVM_Size(array123)) {
    print("iteration: " + STR(A_Index1))
    print("Item: " + array123[A_Index1])
}
print("this is how the escape char looks like \nthis is a new line")
/*
this is a comment block
this is a comment block
*/
// this is how to use an AutoHotKey like Loop
for (A_Index2 in 0..<10) {
    if ((A_Index2 % 2 == 0)) {
        continue;
    }
    print(A_Index2)
}
// this is how to use an AutoHotKey like infinite Loop
for (int A_Index3 = 0; ; A_Index3++) {
    if ((A_Index3 == 5)) {
        break;
    } else {
        print(A_Index3)
    }
}
// this is how to use an AutoHotKey like Loop, parse
someText = "hello how are you doing\ntoday we are good."
def items4 = LoopParseFunc(someText, " ", "\n")
for (A_Index4 in 0..<items4.size()) {
    def A_LoopField4 = items4[A_Index4 - 0]
    print(A_LoopField4)
}
// Error Handling
try {
    throw new Exception("Something went wrong!")
}
catch (Exception e) {
    print(e.message)
}
finally {
    print("Finally block executed")
}
