

// Print function
def print = { message ->
    System.out.print("$message\n")
}


try {
    throw new Exception("this is an ERROR HTVM v2")
}
catch (Exception ee) {
    print(ee.message)
}
finally {
    print("finally finally finally finally")
}
