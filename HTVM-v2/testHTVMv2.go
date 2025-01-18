package main
import (
"fmt"
)

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
    for A_Index1 := 0; A_Index1 < 5 + 0; A_Index1++ {
        print("hello HTVM v2")
        print("hello HTVM\nv2")
        print(A_Index1)
        for A_Index2 := 0; A_Index2 < 5 + 0; A_Index2++ {
            print("hello HTVM v2")
            print("hello HTVM\nv2")
            for A_Index3 := 0; A_Index3 < 5 + 0; A_Index3++ {
                print("hello HTVM v2")
                print("hello HTVM\nv2")
                print(A_Index3)
            }
            print(A_Index2)
        }
    }
    print(5+5 != 5 !SZDS() + "A+-+--+ != ADSF" + "WSADFD" + "qwadsf" + adsf >= 3 <= qwerd > qwretr < wdsdf = 5 != 8)
    print("QWADSDF" + "qawdsf" || var1 ! var4 + "ASDFX" + !ADSFD("Qwads" + "QASD" + "aszd" < 6) THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR false THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR true || nil && false)
    print(HTVM_Size(aszd) HTVM_Append(aszd, HTVM_Size(aszd)))
    Avar123 = StringTrimRight(STRRAWSD, 1)
    if(var1 == 5 && var2w3erf < 6)
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var1 = 1
    print((var1 == 1) THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR "hello" THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR "bye")
    var1 = 0
    print((var1 == 1) THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR "hello" THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR "bye")
}