

function print(value) {
    console.log(value)
}

      // Function to simulate AutoHotkey's RegExReplace in JavaScript
      function RegExReplace(inputStr, regexPattern, replacement) {
          // Create a regular expression object using the provided pattern
          const regex = new RegExp(regexPattern, 'g'); // 'g' flag for global match
          // Use the replace() method to perform the regex replacement
          const resultStr = inputStr.replace(regex, replacement);
          // Return the modified string
          return resultStr;
      }


async function main() {
    var outCode = "var1 := ";
    // Example C++ ternary expressions
    var cpp_code = "day == SUNDAY ? 12 : 9";
    // Convert C++ ternary to Python ternary using RegExReplace
    var python_code = RegExReplace(cpp_code, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "$2 if $1 else $3");
    var nim_code = RegExReplace(cpp_code, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*)", "if $1: $2 else: $3");
    // Convert C++ ternary to Lua ternary-like expression using RegExReplace
    var lua_code = RegExReplace(cpp_code, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "($1) and $2 or $3");
    // Convert C++ ternary to Kotlin/Scala ternary-like expression using RegExReplace
    var kotlin_code = RegExReplace(cpp_code, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "if $1 $2 else $3");
    // Output the converted code for Python, Nim, Lua, and Kotlin/Scala
    print(outCode + python_code);
    print(outCode + nim_code);
    print(outCode + lua_code);
    print(outCode + kotlin_code);
}
main();