

function print(value) {
    console.log(value)
}

function HTVM_getLang_HTVM() {
    return "js";
}



print("HTVM v2");
if (HTVM_getLang_HTVM() == "cpp") {
    print("CPP");
}
if (HTVM_getLang_HTVM() == "py") {
    print("PY");
}
if (HTVM_getLang_HTVM() == "js") {
    print("JS");
}