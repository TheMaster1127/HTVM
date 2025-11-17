
# start of utils.htvm
# in utils.htvm
def read(object):
    # some generic HTVM read logic
    return "read from " + object
# end of utils.htvm
f = open("my_file.txt", "r")
content = read(f)
# It IS now in the list!
# The parser now INCORRECTLY rewrites this to:
# read(f)
