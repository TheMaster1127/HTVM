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
}
