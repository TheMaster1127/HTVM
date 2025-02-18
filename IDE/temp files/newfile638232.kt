

// Print function for various types
fun print(value: Any) {
  println(value)
}

fun <T> HTVM_Size(arr: List<T>): Int {
    return arr.size
}


fun main(args: Array<String>) {
    val arr123 = arrayListOf(1, 3, 5)
    for (A_Index1 in 0 until HTVM_Size(arr123) + 0) {
        print(arr123[A_Index1])
    }
    

}