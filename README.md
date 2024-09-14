# HTVM

HTVM is a tool for creating and deploying new programming languages quickly. You define your language’s rules and syntax in a simple text file, and HTVM takes care of the rest. It generates the code needed for your language. HTVM supports transpiling to JavaScript, Python, and C++, making it easy to test and use your new language in different environments.

**HTVM** lets you create and deploy new programming languages efficiently. To configure your language:

1. **Syntax Configuration**: Adjust the syntax in `HT-instructions.txt`. Each line in this file corresponds to the same line in `instruction documentation.txt`, so line 10 in `instruction documentation.txt` matches line 10 in `HT-instructions.txt`.

2. **Code Writing**: Write your language code in `main.ht`. 

3. **Execution**: Use `HTVM.exe` or compile the C++ code to generate the output. Choose the target language by specifying `cpp`, `py`, or `js` on the first line of `HT-instructions.txt`.

4. **Built-in Functions**: Define built-in functions at the bottom of `HT-instructions.txt` by duplicating the relevant section.

5. **IDE Integration**: Compile `IDE-generator.cpp` to produce `IDE-generator`. You can then run it with `HT-instructions.txt` to generate `IDE.html`, which includes an IDE with syntax highlighting and code completion features. Use `Ctrl+Shift+Alt+F` to format code and `Ctrl+Shift+Alt+G` to undo formatting. For normal undo operations, use `Ctrl+Z` like in a typical IDE.

## Usage

### On Windows

```
HTVM main.ht HT-instructions.txt
```

### On Linux

Compile `HTVM.cpp` and run it with the same arguments:

```
g++ HTVM.cpp -o HTVM
./HTVM main.ht HT-instructions.txt
```

### IDE Generation

Compile `IDE-generator.cpp` to produce `IDE-generator` and run:

```
./IDE-generator HT-instructions.txt
```

This will generate `IDE.html`, providing an IDE with features like syntax highlighting, code completion, and formatting options.

## Note

This project is still in development. More features will be added soon, including a website for easy instruction file generation and documentation.
