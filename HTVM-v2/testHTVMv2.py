

# used the print func


try:
    raise Exception("this is an ERROR HTVM v2")
except Exception as ee:
    print(ee)
finally:
    print("finally finally finally finally")