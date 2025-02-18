package main
import (
"fmt"
"regexp"
)

func LoopParseFunc(varString string, delimiter1 string, delimiter2 string) []string {
    var items []string
    if delimiter1 == "" && delimiter2 == "" {
        // If no delimiters are provided, convert string to slice of strings
        items = make([]string, len(varString))
        for i, c := range varString {
            items[i] = string(c)
        }
    } else {
        // Construct the regular expression pattern for splitting the string
        pattern := fmt.Sprintf("[%s%s]+", delimiter1, delimiter2)
        // Split the string using the constructed pattern
        items = regexp.MustCompile(pattern).Split(varString, -1)
    }
    return items
}

func print(value interface{}) {
    fmt.Println(value)
}

func HTVM_Append[T any](arr *[]T, value T) {
    *arr = append(*arr, value)
}

func HTVM_Pop[T any](arr *[]T) {
    if len(*arr) > 0 {
        *arr = (*arr)[:len(*arr)-1]
    }
}

func HTVM_Size[T any](arr []T) int {
    return len(arr)
}

func HTVM_Insert[T any](arr *[]T, index int, value T) {
    if index >= 0 && index <= len(*arr) {
        *arr = append((*arr)[:index], append([]T{value}, (*arr)[index:]...)...)
    }
}

func HTVM_Remove[T any](arr *[]T, value T) {
    for i, v := range *arr {
        if v == value {
            *arr = append((*arr)[:i], (*arr)[i+1:]...)
            break
        }
    }
}

func HTVM_IndexOf[T comparable](arr []T, value T) int {
    for i, v := range arr {
        if v == value {
            return i
        }
    }
    return -1
}


// start






func func0(input string) {
    fmt.Println(input)
}






















func func1(var1 float64, var2 byte, var3 uint8, var4 uint16, var5 uint32, var6 uint64, var7 int, var8 string, var9 bool, var10 float32, var11 int8, var12 int16, var13 int32, var14 int64) {
    print(var1)
    print(var2)
    print(var3)
    print(var4)
    print(var5)
    print(var6)
    print(var7)
    print(var8)
    print(var9)
    print(var10)
    print(var11)
    print(var12)
    print(var13)
    print(var14)
}
func func2(var1 float64) float64 {
    return var1
}
func func3(var1 byte) byte {
    return var1
}
func func4(var1 uint8) uint8 {
    return var1
}
func func5(var1 uint16) uint16 {
    return var1
}
func func6(var1 uint32) uint32 {
    return var1
}
func func7(var1 uint64) uint64 {
    return var1
}
func func8(var1 int) int {
    return var1
}
func func9(var1 string) string {
    return var1
}
func func10(var1 bool) bool {
    return var1
}
func func11(var1 float32) float32 {
    return var1
}
func func12(var1 int8) int8 {
    return var1
}
func func13(var1 int16) int16 {
    return var1
}
func func14(var1 int32) int32 {
    return var1
}
func func15(var1 int64) int64 {
    return var1
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
var var01 float64 = 3.1234567891011
var var02 byte = 'a'
var var03 uint8 = 25
var var04 uint16 = 30
var var05 uint32 = 35
var var06 uint64 = 40
var var07 int = 100
var var08 string = "hello var ouside"
var var09 bool = false
var var010 float32 = 3.14
var var011 int8 = 100
var var012 int16 = 200
var var013 int32 = 230
var var014 int64 = 80009
func main() {
    var var_1 float64
    var var_2 byte
    var var_3 uint8
    var var_4 uint16
    var var_5 uint32
    var var_6 uint64
    var var_7 int
    var var_8 string
    var var_9 bool
    var var_10 float32
    var var_11 int8
    var var_12 int16
    var var_13 int32
    var var_14 int64
    func1(var01, var02, var03, var04, var05, var06, var07, var08, var09, var010, var011, var012, var013, var014)
    var_1 = func2(var01)
    var_2 = func3(var02)
    var_3 = func4(var03)
    var_4 = func5(var04)
    var_5 = func6(var05)
    var_6 = func7(var06)
    var_7 = func8(var07)
    var_8 = func9(var08)
    var_9 = func10(var09)
    var_10 = func11(var010)
    var_11 = func12(var011)
    var_12 = func13(var012)
    var_13 = func14(var013)
    var_14 = func15(var014)
    print(var_1)
    print(var_2)
    print(var_3)
    print(var_4)
    print(var_5)
    print(var_6)
    print(var_7)
    print(var_8)
    print(var_9)
    print(var_10)
    print(var_11)
    print(var_12)
    print(var_13)
    print(var_14)
    // start
    

    

    

    func0("Hello World")
    

    

    

    

    

    

    

    

    

    

    

    print("==================================")
    for A_Index1 := 0; A_Index1 < 5 + 0; A_Index1++ {
        if (A_Index1 == 0) {
            print(A_Index1)
        } else if (A_Index1 == 1) {
            print(A_Index1)
        } else if (A_Index1 == 2) {
            print(A_Index1)
        } else if (A_Index1 == 3) {
            print(A_Index1)
        } else if (A_Index1 == 4) {
            print(A_Index1)
        } else if (A_Index1 == 5) {
            print(A_Index1)
        } else {
            print("HOW????")
            print(A_Index1)
        }
    }
    var vars1 bool = false
    var vars2 int = 0
    for (vars1 == false) {
        vars2++;
        print(vars2)
        if (vars2 == 6) {
            vars1 = true
        }
    }
    for _ := 0; _ < someLimit; _++ {
        if (_ == 6) {
            break
        } else {
            continue
        }
        // this is only for lua
        ::continue::
    }
    var str1 string = "hello 123 hello2"
    items3 := LoopParseFunc(str1, " ", "")
    for _ , A_LoopField3 := range items3 {
        print(A_LoopField3)
    }
    print("==================")
    items4 := LoopParseFunc(str1, "", "")
    for _ , A_LoopField4 := range items4 {
        print(A_LoopField4)
        if (A_LoopField4 == "2") {
            break
        } else {
            continue
        }
        ::continue::
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
    arr1 := []string{"hello1", "hello2"}
    arr2 := []bool{true, false}
    arr3 := []float32{3.13, 3.14}
    arr4 := []int{1, 6, 2}
    arr5 := []string{"real STR"}
    // Array operations
    HTVM_Append(&arr1, "hello3")
    var sizeArr1 int = HTVM_Size(arr1)
    print("the size of arr1 is:")
    print(sizeArr1)
    HTVM_Insert(&arr1, 1, "hello?????")
    HTVM_Remove(&arr1, 0)
    var idx1 int = HTVM_IndexOf(arr1, "hello2")
    print("the index of arr1 for hello2 is:")
    print(idx1)
    HTVM_Pop(&arr1)
    for A_Index5 := 0; A_Index5 < HTVM_Size(arr1) + 0; A_Index5++ {
        print(arr1[A_Index5])
    }
    HTVM_Append(&arr2, true)
    var sizeArr2 int = HTVM_Size(arr2)
    print("the size of arr2 is:")
    print(sizeArr2)
    HTVM_Insert(&arr2, 1, false)
    HTVM_Remove(&arr2, 0)
    var idx2 int = HTVM_IndexOf(arr2, true)
    print("the index of arr2 for true is:")
    print(idx2)
    HTVM_Pop(&arr2)
    for A_Index6 := 0; A_Index6 < HTVM_Size(arr2) + 0; A_Index6++ {
        print(arr2[A_Index6])
    }
    HTVM_Append(&arr3, 6.489)
    var sizeArr3 int = HTVM_Size(arr3)
    print("the size of arr3 is:")
    print(sizeArr3)
    HTVM_Insert(&arr3, 1, 1.556)
    HTVM_Remove(&arr3, 0)
    var idx3 int = HTVM_IndexOf(arr3, 3.14)
    print("the index of arr3 for 3.14 is:")
    print(idx3)
    HTVM_Pop(&arr3)
    for A_Index7 := 0; A_Index7 < HTVM_Size(arr3) + 0; A_Index7++ {
        print(arr3[A_Index7])
    }
    HTVM_Append(&arr4, 69)
    var sizeArr4 int = HTVM_Size(arr4)
    print("the size of arr4 is:")
    print(sizeArr4)
    HTVM_Insert(&arr4, 1, 420)
    HTVM_Remove(&arr4, 0)
    var idx4 int = HTVM_IndexOf(arr4, 69)
    print("the index of arr4 for 69 is:")
    print(idx4)
    HTVM_Pop(&arr4)
    for A_Index8 := 0; A_Index8 < HTVM_Size(arr4) + 0; A_Index8++ {
        print(arr4[A_Index8])
    }
    HTVM_Append(&arr5, "hello3real")
    var sizeArr5 int = HTVM_Size(arr5)
    print("the size of arr5 is:")
    print(sizeArr5)
    HTVM_Insert(&arr5, 1, "hello?real????")
    HTVM_Remove(&arr5, 0)
    var idx5 int = HTVM_IndexOf(arr5, "hello3real")
    print("the index of arr5 for hello3real is:")
    print(idx5)
    HTVM_Pop(&arr5)
    for A_Index9 := 0; A_Index9 < HTVM_Size(arr5) + 0; A_Index9++ {
        print(arr5[A_Index9])
    }
    /*
    keyWordThrow
    keyWordErrorMsg
    keyWordTry
    keyWordCatch
    keyWordFinally
    */
    GO DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK {
        print("Trying...")
        GO DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK
    }
    GO DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK {
        print("Caught an error:")
        print(e)
    }
    GO DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK {
        print("This always runs, success or error.")
    }
    print("==============================================")
}