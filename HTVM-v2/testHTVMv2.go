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


func szdfxc0() string {
    return "hi"
}
func szdfxc() {
    print("hi2 void")
}
func main() {
    print(szdfxc0())
    szdfxc()
    print("Hello, World!")
    for A_Index1 := 0; A_Index1 < 5 + 0; A_Index1++ {
        print(A_Index1)
    }
}
