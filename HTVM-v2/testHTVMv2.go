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
func szdfxc(__HTVM_V2_TO_GO_optionalParams__ ...interface{}) {
    var var1 interface{}
    if len(__HTVM_V2_TO_GO_optionalParams__) > 0 {
        var1 = __HTVM_V2_TO_GO_optionalParams__[0]
    } else {
        var1 = "hi"
    }
    print(var1)
    print("hi2 void")
}
func szdfxc1(var0 int, __HTVM_V2_TO_GO_optionalParams__ ...interface{}) {
    var var1, var2 interface{}
    if len(__HTVM_V2_TO_GO_optionalParams__) > 0 {
        var1 = __HTVM_V2_TO_GO_optionalParams__[0]
    } else {
        var1 = "hi"
    }
    if len(__HTVM_V2_TO_GO_optionalParams__) > 1 {
        var2 = __HTVM_V2_TO_GO_optionalParams__[1]
    } else {
        var2 = "hi2"
    }
    print(var0)
    print(var1)
    print(var2)
    print("hi2 void")
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
/*
waedsfdsaeds
aedsf
saedsfxawdsfdfsaw
fddf
sefdf
saersdsaersdgfd
*/
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
func szdfxc2(__HTVM_V2_TO_GO_optionalParams__ ...interface{}) {
    var var1, var2 interface{}
    if len(__HTVM_V2_TO_GO_optionalParams__) > 0 {
        var1 = __HTVM_V2_TO_GO_optionalParams__[0]
    } else {
        var1 = "hi"
    }
    if len(__HTVM_V2_TO_GO_optionalParams__) > 1 {
        var2 = __HTVM_V2_TO_GO_optionalParams__[1]
    } else {
        var2 = "hi2"
    }
    print(var1)
    print(var2)
    print("hi2 void")
}
func main() {
    print(szdfxc0())
    szdfxc()
    szdfxc1(5)
    szdfxc1(6, "hello")
    szdfxc2()
    szdfxc2("HI1")
    szdfxc2("HI1", "HI2")
    print("Hello, World!")
    for A_Index1 := 0; A_Index1 < 5 + 0; A_Index1++ {
        print(A_Index1)
    }
}