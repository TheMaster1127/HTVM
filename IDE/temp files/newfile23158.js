

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
    var text = "null + true";
    var wordToReplace = "null";
    var replaceWith = "nil";
    // Call the RegExReplace function
    print(RegExReplace(text, "(^|[^a-zA-Z0-9_])(" + wordToReplace + ")([^a-zA-Z0-9_]|$)", "$1" + replaceWith + "$3"));
}
main();
