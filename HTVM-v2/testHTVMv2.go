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
    print("Hello, World!")
    for A_Index1 := 0; A_Index1 < 5 + 0; A_Index1++ {
    }
    async func szdfxc(str1, str2, str3):str {
        print("hi1")
    }
    func szdfxc(str1, str2, str3):long long {
        print("hi2")
    }
}
