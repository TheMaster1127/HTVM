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

// Append to a slice
func HTVM_Append[T any](arr *[]T, value T) {
    *arr = append(*arr, value)
}

// Get the size of a slice
func HTVM_Size[T any](arr []T) int {
    return len(arr)
}


func func1(var1 string) string {
    return var1 + var1
}
func func2(var1 string) {
    print(var1 + var1)
}
func func3(var1 string, __HTVM_V2_TO_GO_optionalParams__ ...interface{}) {
    var2 := "hello"
    if len(__HTVM_V2_TO_GO_optionalParams__) > 0 {
        var2 = __HTVM_V2_TO_GO_optionalParams__[0].(string)
    }
    print(var1 + " " + var2)
}
func main() {
    print(func1("hi1"))
    func2("hi2")
    func3("hi3")
    func3("hi3", "hello3")
    var var1 int
    var myArr0 []bool
    HTVM_Append(&myArr0, true)
    HTVM_Append(&myArr0, false)
    HTVM_Append(&myArr0, true)
    myArr := []int{5, 6, 7}
    for A_IndexA1 := 0; A_IndexA1 < 5 + 0; A_IndexA1++ {
        var1 = 6
        HTVM_Append(&myArr, A_IndexA1)
    }
    for A_IndexA2 := 0; A_IndexA2 < HTVM_Size(myArr) + 0; A_IndexA2++ {
        print(myArr[A_IndexA2])
    }
    for A_IndexA3 := 0; A_IndexA3 < HTVM_Size(myArr0) + 0; A_IndexA3++ {
        print(myArr0[A_IndexA3])
    }
    if var1 == 6 {
        print(var1)
    } else if var1 == 7 {
        print(var1)
    }
    var var123 string = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn"
    items4 := LoopParseFunc(var123, "\n", "\r")
    for A_IndexA4 , A_LoopFieldA4 := range items4 {
        if A_IndexA4 == 0 {
            print(A_IndexA4)
        }
        print(A_LoopFieldA4)
    }
    print("==================")
    var var1234 string = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg"
    items5 := LoopParseFunc(var1234, ",", "")
    for A_IndexA5 , A_LoopFieldA5 := range items5 {
        if A_IndexA5 == 0 {
            print(A_IndexA5)
        }
        print(A_LoopFieldA5)
    }
    print("==================")
    var var12345 string = "hello"
    items6 := LoopParseFunc(var12345, "", "")
    for _ , A_LoopFieldA6 := range items6 {
        print(A_LoopFieldA6)
    }
}