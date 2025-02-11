package main
import (
"fmt"
)

func LoopParseFunc(varString, delimiter1="", delimiter2="") {
    var items;
    if (delimiter1 == "" && delimiter2 == "") {
        // If no delimiters are provided, return a slice of characters
        items = []byte(varString);
    } else {
        // Construct the regular expression pattern for splitting the string
        pattern := fmt.Sprintf("[%s%s]+", delimiter1, delimiter2);
        // Split the string using the constructed pattern
        items = regexp.MustCompile(pattern).Split(varString, -1);
    }
    return items;
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


func main() {
    var var1 string
    var1 = "hello man whats up"
    var var2 string
    var2 = "hello\nman\nwhats\rup"
    items1 := LoopParseFunc(var1, " ")
    for A_Index1 , A_LoopField1 := range(items1) {
        A_LoopField1 := items1[A_Index1 - 0]
        print(A_LoopField1)
    }
    items2 := LoopParseFunc(var2, "\n", "\r")
    for A_Index2 , A_LoopField2 := range(items2) {
        A_LoopField2 := items2[A_Index2 - 0]
        print(A_LoopField2)
    }
}
