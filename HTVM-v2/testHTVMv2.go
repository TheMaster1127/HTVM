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
	switch v := value.(type) {
	case string:
		fmt.Println(v)
	case int, int32, int64:
		fmt.Println(fmt.Sprintf("%d", v))
	case float32, float64:
		fmt.Println(fmt.Sprintf("%f", v))
	case bool:
		fmt.Println(fmt.Sprintf("%v", v))
	default:
		fmt.Println("Unsupported type")
	}
}

func HTVM_Append[T any](arr *[]T, value T) {
    *arr = append(*arr, value)
}

func HTVM_Size[T any](arr []T) int {
    return len(arr)
}


func main() {
    var var1 int
    var myArr0 []bool
    HTVM_Append(&myArr0, true)
    HTVM_Append(&myArr0, false)
    HTVM_Append(&myArr0, true)
    myArr := []int{5, 6, 7}
    for A_Index1 := 0; A_Index1 < 5 + 0; A_Index1++ {
        var1 = 6
        HTVM_Append(&myArr, A_Index1)
    }
    for A_Index2 := 0; A_Index2 < HTVM_Size(myArr) + 0; A_Index2++ {
        print(myArr[A_Index2])
    }
    for A_Index3 := 0; A_Index3 < HTVM_Size(myArr0) + 0; A_Index3++ {
        print(myArr0[A_Index3])
    }
    print(var1)
    var var123 string = "sdf\naszdxgvh\newsrdt\nsdr\rdfgcvbnb\n\rsdxfgcvn"
    items4 := LoopParseFunc(var123, "\n", "\r")
    for A_Index4 , A_LoopField4 := range items4 {
        if (A_Index4 == 0) {
            print(A_Index4)
        }
        print(A_LoopField4)
    }
    print("==================")
    var var1234 string = "waesrdtg,qwerd,qwe rd,w esrd,wedr d,esrdgfesdrgsdrgf,sdrfg"
    items5 := LoopParseFunc(var1234, ",")
    for A_Index5 , A_LoopField5 := range items5 {
        if (A_Index5 == 0) {
            print(A_Index5)
        }
        print(A_LoopField5)
    }
}
