

function print(value) {
    console.log(value)
}

function fstr(val) {
    return String(val);
}


// === Regular F-String Example ===
var calculation = 10 + 5;
var message = "The result is: " + fstr(calculation) + ". Double is: " + fstr(calculation * 2) + "";
print("Regular F-String:");
print(message);
print("=========================");
// === Multiline String (Raw) Example ===
var ascii_cat = " /\\_/\\\n( o.o )\n > ^ <";
print("Multiline String (Raw):");
print(ascii_cat);
print("=========================");
// === Multiline F-String Example ===
var userName = "Alice";
var items = 3;
var price = 19.99;
var order_summary = "Order Summary for: " + fstr(userName) + "\n\nItems purchased: " + fstr(items) + "\nTotal cost: $" + fstr(items * price) + "\n\nThank you for your order!\nNewlines and indentation are preserved.";
print("Multiline F-String:");
print(order_summary);
print("=========================");