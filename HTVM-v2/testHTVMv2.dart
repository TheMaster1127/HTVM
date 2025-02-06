

// Print function for various types


String szdfxc0() {
    return "hi";
}
void szdfxc([String var1 = "hi"]) {
    print(var1);
    print("hi2 void");
}
void szdfxc1(int var0, [String var1 = "hi", String var2 = "hi2"]) {
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
void szdfxc2([String var1 = "hi", String var2 = "hi2"]) {
    print(var1);
    print(var2);
    print("hi2 void");
}


void main(List<String> arguments) {
    

    print(szdfxc0());
    szdfxc();
    szdfxc1(5);
    szdfxc1(6, "hello");
    szdfxc2();
    szdfxc2("HI1");
    szdfxc2("HI1", "HI2");
    print("Hello, World!");
    for (int A_Index1 = 0; A_Index1 < 5 + 0; A_Index1++) {
        print(A_Index1);
    }
}