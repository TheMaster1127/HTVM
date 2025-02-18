

// Print function for various types

int HTVM_Size<T>(List<T> arr) {
  return arr.length;
}


void main(List<String> arguments) {
    List<int> arr123 = [1, 3, 5];
    for (int A_Index1 = 0; A_Index1 < HTVM_Size(arr123) + 0; A_Index1++) {
        print(arr123[A_Index1]);
    }
    

}