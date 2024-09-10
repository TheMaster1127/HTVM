# HTVM

HTVM is a tool for creating and deploying new programming languages quickly. You define your language’s rules and syntax in a simple text file, and HTVM takes care of the rest. It generates the code needed for your language. HTVM supports transpiling to JavaScript, Python, and C++, making it easy to test and use your new language in different environments.

**HTVM** lets you create and deploy new programming languages efficiently. To configure your language:

1. **Syntax Configuration**: Adjust the syntax in `HT-instructions.txt`. Each line in this file corresponds to the same line in `instruction documentation.txt`, so line 10 in `instruction documentation.txt` matches line 10 in `HT-instructions.txt`.

2. **Code Writing**: Write your language code in `main.ht`. 

3. **Execution**: Use `HTVM.exe` or compile the C++ code to generate the output. Choose the target language by specifying `cpp`, `py`, or `js` on the first line of `HT-instructions.txt`.

4. **Built-in Functions**: Define built-in functions at the bottom of `HT-instructions.txt` by duplicating the relevant section.
