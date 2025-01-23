
public class Main
{


// Print function for various types
    public static void print(Object value) {
        if (value instanceof String) {
            System.out.println(value);
        } else if (value instanceof Integer || value instanceof Float || value instanceof Double) {
            System.out.println(value.toString());
        } else if (value instanceof Boolean) {
            System.out.println((Boolean) value ? "true" : "false");
        } else {
            System.out.println("Unsupported type");
        }
    }


public static void main(String[] args) {
    if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    }
    else if (5 == 5 && 6 - 6 == 0) {
        print("MAAAAAAAAAAA<M<SJDIJSLDLS");
    } else {
        print(5+5);
    }
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    print("==========");
    try {
        throw new Exception("this is an ERROR HTVM v2");
    }
    catch (Exception ee) {
        print(ee.getMessage());
    }
    finally {
        print("finally finally finally finally");
    }
    }
}