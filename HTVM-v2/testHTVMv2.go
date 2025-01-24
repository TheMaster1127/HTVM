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
    // some comment
    for (true) {
        print("hi from HTVM v2 still in development")
        break
    }
    
    if () {
        WADSFDSASDFXGC
    } else if () {
        waedsfsawdsfx
    } else if () {    
    /*
    WAESFD
    WAQESR
    FRAWE
    DSFDSADSDF
    asfdx
    for A_Index1 := 0; A_Index1 < 5 + 0; A_Index1++ {
        print(A_Index1)
    }
    */
}
