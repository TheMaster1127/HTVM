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
    GO DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK {
        GO DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK
    }
    GO DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK {
        print(ee)
    }
    GO DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK {
        print("finally finally finally finally")
    }
}
