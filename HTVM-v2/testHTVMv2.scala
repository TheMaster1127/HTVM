
object MainApp
{


// Print function for various types
  def print(value: Any): Unit = value match {
    case v: String => println(v)
    case v: Int => println(v)
    case v: Float => println(v)
    case v: Boolean => println(if (v) "true" else "false")
    case _ => println("Unsupported type")
  }

def HTVM_Append[T](arr: scala.collection.mutable.Buffer[T], value: T): Unit = {
  arr += value
}

def HTVM_Size[T](arr: Seq[T]): Int = arr.size


def main(args: Array[String]): Unit = {
    for (A_Index1 <- 0 to 20 + 0) {
        print("hello HTVM import")
        print("hello HTVM\nimport")
    }
    for (A_Index2 <- 0 to 6 + 0) {
        print("hello HTVM import")
        print("hello HTVM\nimport")
    }
    for (A_Index3 <- 0 to 5 + 0) {
        print("hello\" HTVM v2")
        print("hello HTVM\\v2\\\\s")
        print("hello HTVM\nv2")
        print("hello HTVM\\nv2")
        print(A_Index3)
        for (A_Index4 <- 0 to 5 + 0) {
            print("hello HTVM v2")
            print("hello HTVM\nv2")
            for (A_Index5 <- 0 to 5 + 0) {
                print("hello HTVM v2")
                print("hello HTVM\nv2")
                print(A_Index5)
            }
            print(A_Index4)
        }
    }
    qWAERSFD()
    qWAERSFD(waedsfd())
    print(5+5 != 5 !SZDS() + "A+-+--+ != ADSF" + "WSADFD" + "qwadsf" + adsf >= 3 <= qwerd > qwretr < wdsdf = 5 != 8)
    print(if "QWADSDF" + "qawdsf" || var1 ! var4 + "ASDFX" + !ADSFD("Qwads" + "QASD" + "aszd" < 6) false else true || null && false)
    print(HTVM_Size(aszd) HTVM_Append(aszd, HTVM_Size(aszd)))
    Avar123 = StringTrimRight(STRRAWSD, 1)
    if(var1 == 5 && var2w3erf < 6)
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    var1 = 1
    print(if (var1 == 1) "hello" else "bye")
    var1 = 0
    print(if (var1 == 1) "hello" else "bye")
    }
}