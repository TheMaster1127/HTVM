package main
import (
"fmt"
)

func print(value interface{}) {
    fmt.Println(value)
}

func HTVM_Size[T any](arr []T) int {
    return len(arr)
}


func main() {
    arr123 := []int{1, 3, 5}
    for A_Index1 := 0; A_Index1 < HTVM_Size(arr123) + 0; A_Index1++ {
        print(arr123[A_Index1])
    }
    

}