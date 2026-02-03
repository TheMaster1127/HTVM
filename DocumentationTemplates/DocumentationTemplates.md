============***1***============

1. [Introduction](#introduction-to-htvm)  
Understand why HTVM is the future of programming.

2. [OSP (Ordinal Struct Programming)](#osp-ordinal-struct-programming)  
Learn about OSP (Ordinal Struct Programming) a simple way to use Structs.

3. [How Your Language Looks Like](#how-your-language-looks-like)  
Get to know how HTVM code is structured and its syntax style.

4. [Programming Blocks](#programming-blocks)  
HTVM introduces **programming blocks** that allow you to code in the target language seamlessly in your code. This feature is designed to handle cases where HTVM itself can't achieve something directly or when you'd prefer to rely on another language for specific tasks.

5. [Variables](#variables)  
Learn how to declare and use variables in HTVM for storing and manipulating data.

6. [Functions](#functions)  
Explore how to define and use functions for modular and reusable code.

7. [Pattern Matching](#pattern-matching)  
HTVM provides a flexible and minimalist `when` block for pattern matching. It is designed to be highly intuitive, allowing you to write complex conditional logic with the least possible syntax and elegantly eliminating the verbosity of traditional `if-else` chains.

8. [Arrays](#arrays)  
Dive into working with arrays, one of the most essential data structures in HTVM.

9. [Loops](#loops)  
Master the looping structures available in HTVM, such as the standard loop and infinite loops.

10. [Comments](#comments)  
Add clarity to your code by using comments to document and explain your code.

11. [GUI (Graphical User Interface with HTVM)](#gui-graphical-user-interface-with-htvm)  
Learn how to the GUI feature in HTVM that allows for the creation of graphical user interfaces specifically for **web browsers (JavaScript)**.

12. [Backend in HTVM](#backend-in-htvm)  
Learn how to use HTVM's Backend functionality that generates **Python** code using **Flask**.

13. [Error Handling](#error-handling)  
Understand how to manage errors and handle exceptions in HTVM to make your programs more robust.

14. [Include](#include)  
Discover how to include external files and resources in your HTVM project for enhanced functionality.

15. [Commands](#commands)  
Commands in HTVM are a simplified way to perform actions, similar to functions, but with a more compact, direct, and concise syntax for better efficiency.

16. [All Syntax](#all-syntax)  
This is all of your syntax.

17. [Built-in Functions](#built-in-functions)  
Explore the wide range of built-in functions categorized for ease of use.

============&&&1&&&============
============***2***============

### How Your Language Looks Like

[Go back](#htvm-documentation)

Get to know how HTVM code is structured and its syntax style. HTVM uses a clean, human-readable syntax that focuses on simplicity and ease of use. You can define your own syntax, making HTVM incredibly flexible and tailored to your needs.

%%%sentence%%%

Here is how it looks like:

```htvm
%%%htvmSnippet12%%%

```

### Advanced String Features

HTVM supports powerful string definition methods, including formatted strings (f-strings) and multiline strings for easier text handling.

*   **F-Strings (`f"..."`)**: Allow embedding variables and expressions directly within strings.
*   **Multiline Strings (`mls`...`mle`)**: Define strings that span multiple lines, preserving formatting (like newlines and indentation) exactly as written. Ideal for raw text, templates, or ASCII art.
*   **Multiline F-Strings (`fmls`...`mle`)**: Combine the benefits of multiline strings and f-strings, allowing embedded variables and expressions within a multiline block.

Here's how you can use them:

```htvm
%%%htvmSnippet100%%%

```

#### Summary: The Power of Advanced Strings

These advanced string features (`f`, `mls`, `fmls`) significantly enhance HTVM's usability and power. They eliminate the need for cumbersome string concatenation and complex formatting logic.

*   **Readability**: Code becomes much cleaner and easier to read, especially when dealing with templates, long text blocks, or dynamic content generation.
*   **Simplicity**: Constructing complex strings with embedded variables or preserving exact formatting is now straightforward and intuitive.
*   **Expressiveness**: HTVM becomes even more expressive, allowing you to focus on the logic rather than wrestling with string manipulation quirks.

This level of string handling flexibility is a testament to HTVM's design philosophy: providing powerful, convenient tools that adapt to the programmer's needs, ultimately making development faster and more enjoyable. It's another step towards making HTVM the future of simplified, yet powerful, programming.

---
============&&&2&&&============


============***3***============

### Programming Blocks

[Go back](#htvm-documentation)

Programming blocks in HTVM allow you to write code directly in the target language when HTVM itself cannot handle certain tasks. These blocks give you the flexibility to insert language-specific code into your HTVM project without disrupting the overall flow. There are two main use cases for programming blocks: single-language programming blocks and multi-language programming blocks.

#### **Single-Language Programming Block**

A single-language programming block allows you to write code directly in the target language. If you're converting HTVM code to, say, C++, you can open a programming block and write C++ code inside. This block will only be valid in the context of converting to C++ and will disappear when converting to another language.

**Example:**

```htvm
%%%htvmSnippet13%%%

```

#### **Multiple-Language Programming Block**

HTVM also supports multiple-language programming blocks, where you can write code in different languages for the same functionality. For instance, if you're converting to both C++ and JavaScript, you can write separate blocks for each language but ensure the code behaves similarly in both.

**Example:**

```htvm
%%%htvmSnippet14%%%

```

When using multi-language blocks, the syntax and implementation might differ, but the core functionality should remain the same. This is a great way to ensure consistency across multiple target languages.

#### **Warning About AI-Generated Code**

**WARNING:** Be cautious when using AI-generated code. While AI can help speed up development, relying too heavily on it can be dangerous. You must understand the code you're incorporating into your project. **MAKE SURE YOU KNOW WHAT YOU'RE DOING BEFORE USING AI**. 

If you don't have a solid understanding of the concepts you're asking the AI to handle, it can harm your learning process. **It could also negatively affect your development as a programmer.** Are you truly understanding the code you’re working with, or just relying on AI to do the heavy lifting for you?

Use AI to *assist*, not replace your learning process. **Be careful and make sure you understand every line of code** before integrating it into your project. This is essential for becoming a proficient programmer.

#### **Reverse Programming Blocks**

Reverse programming blocks in HTVM allow you to write HTVM code in another file, which the HTVM compiler can recognize. These reverse blocks are helpful when you need to convert code written in HTVM into a target language while automatically including the necessary libraries and built-in functions.

The syntax for reverse programming blocks is the same as for regular programming blocks, but you'll write HTVM code inside files of supported languages (e.g., `.cpp`, `.js`, etc.). Once you pass both the source file (e.g., `main.cpp`) and the HTVM instruction file to HTVM, the compiler will automatically replace the HTVM code with the appropriate target language code.

HTVM will also ensure that all necessary libraries and built-in functions are included. It will automatically show you which libraries need to be included at the top of the file and which built-in functions you must import if they're not already part of the language's standard library.

**Example of reverse programming block:**

1. Create a `.cpp` file (or any supported language file).
2. Open the HTVM programming block using the syntax below:
- To open - `%%%htvmOpenPrgBlock%%%`
- To close - `%%%htvmClosePrgBlock%%%`

3. Pass both the `.cpp` file and the HTVM instruction file to HTVM.

HTVM will:

- Replace the HTVM code with C++ (or the corresponding language).
- Display the libraries and built-in functions that need to be included.

---
============&&&3&&&============

============***4***============

### Variables

[Go back](#htvm-documentation)

Learn how to declare and use variables in HTVM for storing and manipulating data. HTVM makes working with variables straightforward by providing flexible types and easy handling of data.


### **Variables in HTVM**  

A variable is a way to store and reference data in your code. In HTVM, you can use different variable types depending on your needs. Here are all the variable types supported by HTVM:  

| Type         | Description |
|-------------|------------|
| `int`       | Regular integer (size depends on the target language) |
| `int8`      | 8-bit signed integer |
| `int16`     | 16-bit signed integer |
| `int32`     | 32-bit signed integer |
| `int64`     | 64-bit signed integer |
| `uint8`     | 8-bit unsigned integer |
| `uint16`    | 16-bit unsigned integer |
| `uint32`    | 32-bit unsigned integer |
| `uint64`    | 64-bit unsigned integer |
| `float`     | Floating-point number (usually 32-bit) |
| `double`    | Double-precision floating-point number |
| `char`      | Single character |
| `string`    | Text string |
| `bool`      | Boolean (`true` or `false`) |

> **Note:** We won't mention arrays here because they have a separate section under.

---

### **HTVM Variable Example**  

Here’s a simple example of declaring and printing variables in HTVM:  

```htvm
%%%htvmSnippet15%%%

```

This will correctly convert to the target language with the appropriate syntax.

---

### **Static vs. Dynamic Typing in HTVM**  

HTVM itself is **neither statically typed nor dynamically typed**. It simply converts code to the target language, which may be either.  

| **Language**  | **Typing** |
|--------------|------------|
| JavaScript   | Dynamic    |
| Python       | Dynamic    |
| Lua          | Dynamic    |
| Ruby         | Dynamic    |
| Groovy       | Dynamic    |
| TypeScript   | Static     |
| C++          | Static     |
| Go (Golang)  | Static     |
| C#           | Static     |
| Java         | Static     |
| Kotlin       | Static     |
| Nim          | Static     |
| Swift        | Static     |
| Dart         | Static     |
| AutoHotKey   | Dynamic    |

- **For static languages**, you **must** use types; otherwise, the conversion will result in invalid code.
- **For dynamic languages**, you **can** use types, but HTVM will **strip them away** automatically.
- **HTVM does not provide type safety** – it will not warn you about type mismatches. You'll find out only when running the target language.

---

#### **`let` and `var` Keywords**

The `let` and `var` keywords in HTVM are mainly useful when converting to languages that support these keywords, like **JavaScript** and **TypeScript**. These keywords are used to define mutable variables, but outside of those specific languages, you can ignore them, as HTVM will convert them appropriately based on the target language.

---

### **The `const` Keyword**  

HTVM supports the `const` keyword, but it **does not enforce it** in any way. It simply converts it to the target language if the language supports `const`.  

| **Language**  | **Supports `const`?** |
|--------------|--------------------|
| JavaScript   | ✅ Yes |
| TypeScript   | ✅ Yes |
| C++          | ✅ Yes |
| Go (Golang)  | ✅ Yes |
| C#           | ✅ Yes |
| Java         | ✅ Yes |
| Kotlin       | ✅ Yes |
| Swift        | ✅ Yes |
| Dart         | ✅ Yes |
| Python       | ❌ No (ignored) |
| Lua          | ❌ No (ignored) |
| Ruby         | ❌ No (ignored) |
| Groovy       | ❌ No (ignored) |
| Nim          | ✅ Yes |
| AutoHotKey   | ❌ No (ignored) |

HTVM **does not check** whether you're violating `const`. If a language doesn’t support `const`, HTVM **removes it** without warning.

Example:  

```htvm
%%%htvmSnippet16%%%

```

- If converting to **C++**, this becomes `const int x = 10;`
- If converting to **Python**, this becomes `x = 10` (no `const`).
- If converting to **Java**, this becomes `final int x = 10;`
- ... etc.

---

### **Programming Blocks & Variable Scope**  

HTVM allows **programming blocks**, where you write code directly in a target language. These blocks **do not convert** – they remain as-is.

#### **Variable Accessibility in Programming Blocks**
- **HTVM variables can be accessed inside programming blocks.**
- **Modifications inside a block persist after the block.**
- **Programming blocks are not scoped – they are part of the converted language.**
- **However, different programming languages do not share scope.**  

Example (Converting to Python):  

```htvm
%%%htvmSnippet17%%%

```

This converts to:  

```python
myNumber = 5
myNumber += 10  # Python block stays intact
print(myNumber)  # 15
```

---

### **Multiple Programming Blocks & Limitations**  

#### **Single Language Conversion**
If you are converting to just **one language**, everything works as expected. Variables declared in HTVM can be used inside the programming block and modified.

#### **Multiple Language Conversion**
If you are converting to **multiple languages**, each programming block is isolated per language.  
- **You cannot access variables across different language blocks.**  
- You must **manually maintain the same logic** in each block.  

Example (Invalid cross-language access):  

```htvm
%%%htvmSnippet18%%%

```

To fix this, you need to **manually synchronize values** in each programming block.

---

### **Unsigned Integers & Java**  

- **Java does not support unsigned integers** (`uint8`, `uint16`, etc.).
- If you try to use them, **HTVM will not warn you**, but Java might throw errors.
- **Avoid using unsigned integers when converting to Java.**  

Example of bad practice:  

```htvm
%%%htvmSnippet19%%%

```

- **Works in C++** (`uint32_t myUnsigned = 500;`)
- **Might fail in Java since unsigned ints are converted to signed ones**

---

### **Summary**

- HTVM has multiple **variable types**, including integers, floats, chars, strings, and booleans.
- HTVM **converts to both static and dynamic languages** but does not enforce type safety.
- The `const` keyword is supported but **ignored** in languages that don’t use it.
- **Programming blocks do not convert** – they stay in the target language.
- **Variables persist inside programming blocks** but do not transfer between different language blocks.
- **Java does not support unsigned integers**, so try to avoid them when converting to Java.

---
============&&&4&&&============

============***5***============

### Functions

[Go back](#htvm-documentation)

Explore how to define and use functions for modular and reusable code. Functions in HTVM can be written easily, and the language supports efficient handling of function calls, parameters, and returns.

### **HTVM Functions**  

Functions %%%funcSentence%%%

#### **Defining a Function**

```htvm
%%%htvmSnippet32%%%

```

```htvm
%%%htvmSnippet33%%%

```

```htvm
%%%htvmSnippet34%%%

``` 

Optional parameters example:

```htvm
%%%htvmSnippet35%%%

```

If you are converting to a dynamically typed language, the types will be stripped away automatically. However, for statically typed languages, you must include them.  

#### The `main` Function

In HTVM, the `main` function is required if you are using functions. It is defined as a simple label at the beginning of the program. If you do not include the `main` function, HTVM will insert it automatically at the top of the code. However, if you define any functions and do not include the `main` label, the program will not work as expected.

The `main` label is where the execution starts in languages that use a main function (like C++). In languages that do not require a `main` function (like Python), HTVM handles it automatically.

Here’s how it looks:

```htvm
%%%htvmSnippet36%%%

```

- The `greet` function is defined before `main`.
- The `main` function calls `greet()` to execute the code.

If you do not define the `main` label, HTVM will automatically add it at the top of the code, but **you must include it if you are using functions** to ensure everything works correctly.

### **HTVM: Flexible Function Call Syntax**

#### **Overview**  
HTVM introduces a unique and flexible function call syntax that allows developers to call functions in multiple ways while maintaining simplicity and readability. This enhancement does not change the fundamental nature of functions in HTVM—they remain regular functions rather than methods. However, HTVM allows them to be called using dot notation for convenience. No programming language supports this level of freedom—this is a new invention: a flexible and freeing way to call HTVM functions.

#### **Features**

- **Traditional Function Calls**  
  Functions can be called using the standard syntax:  
  ```htvm
  StrLower(var1)
  Trim(var1)
  ```

- **Dot Notation for Function Calls**  
  HTVM allows functions to be called using dot notation for enhanced readability and convenience:  
  ```htvm
  var1.StrLower()
  var1.Trim()
  ```

- **Optional Parentheses**  
  When a function does not require additional parameters, parentheses can be omitted:  
  ```htvm
  var1.StrLower
  var1.Trim
  ```

- **Chained Function Calls**  
  Functions can be chained together using dot notation:  
  ```htvm
  var1.StrLower().Trim()
  ```

  Since parentheses are optional, the same operation can be written as:  
  ```htvm
  var1.StrLower.Trim
  ```

  It is also possible to mix both styles:  
  ```htvm
  var1.StrLower().Trim
  ```

- **Seamless Transpilation**  
  HTVM automatically converts these function calls into standard function calls during conversion. This ensures that the underlying implementation remains consistent while providing developers with flexibility in how they write their code.

#### **Examples**

### **Standard Function Calls**  
```htvm
StrLower(var1)
Trim(var1)
```

### **Dot Notation Function Calls**  
```htvm
var1.StrLower()
var1.Trim()
```

### **Dot Notation Without Parentheses**  
```htvm
var1.StrLower
var1.Trim
```

### **Chained Function Calls**  
```htvm
var1.StrLower().Trim()
```

### **Mixed Parentheses Usage**  
```htvm
var1.StrLower().Trim
```

### **Full Example with OSP**

```htvm
%%%htvmSnippet37%%%

```

---

#### This only works with HTVM built-in functions and user-defined functions.  
When using the `varName.funcName` format, HTVM will only convert it to a regular function call (`funcName(varName)`) **if** the function is either a built-in function in HTVM or explicitly defined by the user.

HTVM **does not care** whether the function is built-in in the target language (e.g. Python). If the function is not recognized by HTVM, it will not be converted — even if it's valid in the output language.

For example:
```py
strVar.upper()
```
- If `upper` is not a built-in HTVM function or user-defined in your code, HTVM will **not** convert this into `upper(strVar)` for Python.  
- It will stay as `strVar.upper()` or may cause unexpected output depending on the target.

---

#### **Conclusion**  
This feature enhances HTVM's usability by providing developers with multiple ways to call functions. While function calls remain standard behind the scenes, the optional dot notation and support for omitting parentheses make the syntax more intuitive, readable, and faster to write — especially in casual or repetitive scenarios.

---
============&&&5&&&============
============***6***============
### Pattern Matching

[Go back](#htvm-documentation)

HTVM provides a flexible and minimalist **`when`** block for pattern matching. It is designed to be highly intuitive, allowing you to write complex conditional logic with the least possible syntax and elegantly eliminating the verbosity of traditional `if-else` chains.

As a nod to developer convenience, HTVM includes a built-in alias: you can use **`wehn`** interchangeably with **`when`**, so a simple typo won't break your flow.

### A First Look at `when`

At a glance, the `when` block lets you handle different cases with unparalleled clarity. You can match against values, types, ranges, and lists all in one cohesive structure.

```htvm
%%%htvmSnippet74%%%

```

### The `->` Operator

The `->` operator is a core part of the `when` syntax. It serves a simple and clear purpose: to separate a pattern from its action.

Every pattern, from a single number to a complex expression, is followed by `->` to introduce the code that should run when the pattern matches. This creates a highly readable and consistent structure.

**Example:**

```htvm
%%%htvmSnippet75%%%

```

### Block Structures and `subout`

For actions that require multiple lines of code, you can start a new code block on the line immediately following the `->`.

The `subout` keyword is essential as it marks the end of the *entire* `when` or `wehn` structure, allowing for clear and predictable parsing, especially in nested scenarios.

```htvm
%%%htvmSnippet76%%%

```

### A Showcase of Pattern Types and Examples

Here is a comprehensive set of examples, starting with the basics and moving to more advanced use cases.

#### 1. Basic Value Matching

```htvm
%%%htvmSnippet77%%%

```

#### 2. Range Matching

```htvm
%%%htvmSnippet78%%%

```

#### 3. Expression-Based Matching (No Subject)

A `when` block can be used without a subject variable. This makes it a clean alternative to `if-else if` chains. This form is most powerful when you need to evaluate conditions that involve **several different variables**.

For example, identifying a starting sound in a word might depend on the first two letters. You cannot check both `firstLetter` and `secondLetter` on the same line using `when firstLetter`, so a subject-less `when` is ideal.

```htvm
%%%htvmSnippet79%%%

```

#### 4. Matching with Function Calls or Expressions

```htvm
%%%htvmSnippet80%%%

```

#### 5. Nested `when` Blocks

HTVM fully supports nesting `when` and `wehn` blocks for deep conditional logic.

```htvm
%%%htvmSnippet81%%%

```

#### 6. Input Validation Example

```htvm
%%%htvmSnippet82%%%

```

#### 7. Game State Logic Example

```htvm
%%%htvmSnippet83%%%

```

### Summary

*   **Keywords:** Use `when` or its alias `wehn` to start a pattern-matching block.
*   **The `->` Operator:** Separates a pattern from its action (e.g., `5 -> print("Five")`).
*   **Blocks:** Use `subout` which is required to explicitly end the entire `when` structure. For multi-line actions, begin a code block on the line after `->`.
*   **The `else` Branch:** This is an optional catch-all case that never uses the `->` operator. If omitted, and no other patterns match, execution simply continues after the `subout`.
*   **Rich Patterns:** HTVM supports a wide variety of patterns, including single values, ranges (`..`), multi-value lists (`,`), expressions, and the results of function calls.

### Notes and Best Practices

*   **Readability is Key:** The consistent use of `->` gives `when` blocks a predictable structure, making code easier to read and maintain across projects.
*   **Leverage the Optional `else`:** The fact that the `else` branch is not required is a powerful feature for writing concise code. Use it when you only need to act on a few specific cases and want to ignore all others.
*   **Embrace Nesting:** Don't be afraid to nest `when` blocks. It is often much cleaner and more readable than deeply nested `if` statements or complex boolean logic.

---
============&&&6&&&============
============***7***============
### Arrays

[Go back](#htvm-documentation)

Dive into working with arrays, one of the most essential data structures in HTVM. Arrays are simple to declare and manipulate, enabling you to store and process collections of data easily.

### **Arrays in HTVM**

Arrays in HTVM are collections of values stored in a single variable. Arrays can hold multiple values of the same type. HTVM supports a variety of array types and offers flexibility, especially in dynamic languages. Here's an overview of how arrays work in HTVM:

---

### **Supported Array Types**  

HTVM supports the following array types:

| Type        | Description |
|-------------|------------|
| `%%%doc_keyWordArrayOfIntegersDefinition%%%`     | Array of integers (regular size depends on the target language) |
| `%%%doc_keyWordArrayOfFloatingPointNumbersDefinition%%%`   | Array of floating-point numbers |
| `%%%doc_keyWordArrayOfBooleansDefinition%%%`    | Array of booleans (true or false) |
| `%%%doc_keyWordArrayOfStringsDefinition%%%`  | Array of strings (text) |

> **Note:** In dynamic languages like JavaScript and Python, you can use arrays without explicitly defining the type. The type will be inferred or stripped out, depending on the language.

---

### **The Generic Array Type**  

In addition to the specific array types above, HTVM provides a more flexible **generic array** keyword which is `%%%doc_keyWordArrayDefinition%%%`. This allows you to create arrays without specifying a type. When you use this keyword:

- In **dynamically typed languages** (e.g., JavaScript, Python), HTVM will infer the type based on the values you assign.
- In **statically typed languages** (e.g., C++, Java), HTVM will convert it into a `std::vector&lt;std::string>` / `string[]`.

This provides flexibility, but also means you lose type checking, and you’ll need to ensure the elements in the array match the expected type.

Example (Dynamic Language):
```htvm
%%%htvmSnippet20%%%

```

---

### **Array Methods in HTVM**

| **Method**                          | **Description**                                                                                |
|-------------------------------------|------------------------------------------------------------------------------------------------|
| `%%%doc_keyWordArrayAppend%%%()`    | Adds an element to the end of the array.                                                       |
| `%%%doc_keyWordArrayPop%%%()`       | Removes and returns the last element of the array.                                             |
| `%%%doc_keyWordArraySize%%%()`      | Returns the number of elements in the array.                                                   |
| `%%%doc_keyWordArrayInsert%%%()`    | Inserts an element at a specific index.                                                        |
| `%%%doc_keyWordArrayRemove%%%()`    | Removes the element at the specified index.                                                    |
| `%%%doc_keyWordArrayIndexOf%%%()`   | Returns the index of the first occurrence of the specified element. Returns `-1` if not found. |

---

### **Array Methods in Detail**

HTVM provides a set of useful methods to manipulate arrays in your programs. These methods follow a consistent `.method()` syntax, making it easy to interact with arrays. Below are the array methods supported in HTVM:

1. **`%%%doc_keyWordArrayAppend%%%()`**  

Adds an element to the end of the array.  
Example:
```htvm
%%%htvmSnippet21%%%

```

2. **`%%%doc_keyWordArrayPop%%%()`**  

Removes and returns the last element of the array.  
Example:
```htvm
%%%htvmSnippet22%%%

```

3. **`%%%doc_keyWordArraySize%%%()`**  

Returns the number of elements in the array.  
Example:
```htvm
%%%htvmSnippet23%%%

```

4. **`%%%doc_keyWordArrayInsert%%%()`** 
 
Inserts an element at a specific index. The index is the first argument, and the element to insert is the second argument.  
Example:
```htvm
%%%htvmSnippet24%%%

```

5. **`%%%doc_keyWordArrayRemove%%%()`**  

Removes the element at the specified index.  
Example:
```htvm
%%%htvmSnippet25%%%

```

6. **`%%%doc_keyWordArrayIndexOf%%%()`**  

Returns the index of the first occurrence of the specified element. If the element is not found, it returns `-1`.  
Example:
```htvm
%%%htvmSnippet26%%%

```

---

### **Example of Using Array Methods in HTVM**

```htvm
%%%htvmSnippet27%%%

```

In the example above, you can see how various methods like `.push()`, `.rm()`, and `.insert()` are used in sequence to manipulate the array.

---

### **Summary of Array Methods**

- **`%%%doc_keyWordArrayAppend%%%()`**: Adds an element to the end of the array.
- **`%%%doc_keyWordArrayPop%%%()`**: Removes and returns the last element of the array.
- **`%%%doc_keyWordArraySize%%%()`**: Returns the size of the array.
- **`%%%doc_keyWordArrayInsert%%%(index, element)`**: Inserts an element at the specified index.
- **`%%%doc_keyWordArrayRemove%%%(index)`**: Removes the element at the specified index.
- **`%%%doc_keyWordArrayIndexOf%%%(element)`**: Finds the index of the first occurrence of the specified element.

---

### **Arrays in Programming Blocks**  

Just like variables, arrays can be accessed and modified inside **programming blocks**. Programming blocks in HTVM are directly written in the target language and do not undergo conversion. The following behaviors apply to arrays inside programming blocks:

- **Arrays persist across blocks**, meaning changes made to an array within a block are retained when the block ends.
- **Arrays are not scoped**—they are part of the target language’s code.
- **Different programming languages do not share arrays across blocks**, just like variables.

Example (Converting to Python):

```htvm
%%%htvmSnippet28%%%

```

This will convert to:

```python
myArray = [1, 2, 3]
myArray.append(4)  # Python block stays intact
print(myArray)  # Output: [1, 2, 3, 4]
```

---

### **No Type Checking for Arrays**  

HTVM **does not perform type checking** for arrays. It will **not warn you** if you accidentally try to mix types within an array or if you make other mistakes related to array types. You will only notice errors during runtime in the target language.

Example:

```htvm
%%%htvmSnippet29%%%

```

In **JavaScript**, this would become:

```javascript
let myArray = [1, "two", 3];  // Valid in JavaScript, but mixed types
```

However, you might get unexpected results in a **statically typed language**, like **C++**.

---

### **No `const` Arrays**  

HTVM does not support **constant arrays** or array immutability like some languages might (e.g., `const` arrays in JavaScript). If you want to have immutable arrays, you will need to **use programming blocks** and ensure the logic prevents modification.

Example:

```htvm
%%%htvmSnippet30%%%


```

If you want immutability or similar behavior, you must handle it manually within programming blocks or by controlling logic in your code.

---

### **Arrays in Multiple Language Conversions**  

When converting to **multiple languages**, arrays function similarly to variables in programming blocks. However, you cannot directly **share arrays between different language blocks**. Each block is isolated in its respective language, so any array manipulations within one block will not affect another block.

Example (Invalid cross-language access):

```htvm
%%%htvmSnippet31%%%

```

You’ll need to manually synchronize arrays between programming blocks if needed.

---

### **Summary**  

- HTVM supports **integer arrays**, **floating-point arrays**, **boolean arrays**, and **string arrays**.
- **Array Methods in HTVM**
- HTVM offers a **generic array type**, which is flexible but removes type checking in dynamic languages.
- **Arrays in programming blocks persist**, but they are not scoped across blocks.
- **No type checking** is performed on arrays, so errors related to mismatched types will not be caught until runtime.
- **No support for constant arrays**—you need to manage immutability yourself using programming blocks.
- **Arrays cannot be shared across different language blocks** in multiple language conversions.

#### ⚠️ WARNING: We can't use nested arrays or multiline arrays (like arrays inside arrays or 2D/3D arrays). To achieve that, use a programming block.

---
============&&&7&&&============
============***8***============
### Loops

[Go back](#htvm-documentation)

### **Understanding Loops in HTVM**

HTVM supports multiple types of loops, inspired by AutoHotKey (AHK) syntax. These loops are designed to be simple and efficient, offering flexibility for various tasks. Let’s explore the **Regular Loop**, **Loop Parse**, **Infinite Loop**, and the **while loop**.

**Regular Loop** = `%%%doc_keyWordLoop%%%`

**Loop Parse** = `%%%doc_keyWordLoopParse%%%`

**Infinite Loop** = `%%%doc_keyWordLoopInfinite%%%`

**While loop** = `%%%doc_keyWordWhileLoop%%%`

**continue** = `%%%doc_keyWordContinue%%%`

**break** = `%%%doc_keyWordBreak%%%`

**A_Index** = `%%%doc_keyWordAIndex%%%`

**A_LoopField** = `%%%doc_keyWordALoopField%%%`


### **1. Regular Loop**

The `%%%doc_keyWordLoop%%%` keyword in HTVM is the simplest and most common type of loop. It runs a specified number of iterations, and you can use the `%%%doc_keyWordAIndex%%%` keyword to track the current iteration number.

#### Example:

```htvm
%%%htvmSnippet38%%%

```

In this loop, `%%%doc_keyWordAIndex%%%` is used to track the current iteration number. The `%%%doc_keyWordContinue%%%` keyword is used to skip even numbers, so only odd numbers will be printed.

---

### **2. Loop Parse**

The `%%%doc_keyWordLoopParse%%%` is similar to AutoHotKey’s loop parsing method, where you can iterate over a string or text with different delimiters. In HTVM, `%%%doc_keyWordALoopField%%%` is used to access the current field (or token) in the string being parsed.

#### **Example 1: Delimited by Space (" ")**

```htvm
%%%htvmSnippet39%%%

```

In this example, the loop iterates over each word in the string `someText`, which is delimited by spaces. The `%%%doc_keyWordALoopField%%%` holds the current word from the string.

#### **Example 2: Delimited by New Line**

```htvm
%%%htvmSnippet40%%%

```

Here, the loop splits the text by new lines, and `%%%doc_keyWordALoopField%%%` holds each line individually.

#### **Example 3: Delimited by Carriage Return**

```htvm
%%%htvmSnippet41%%%

```

In this case, the text is delimited by carriage returns, and each line is printed separately.

#### **Example 4: Delimited by Both Space and New Line**

```htvm
%%%htvmSnippet42%%%

```

This example uses both a space and a new line as delimiters to split the string into tokens.

#### **Example 5: No delimited**

```htvm
%%%htvmSnippet43%%%

```

This example uses no delimiters to parse each character.

---

### **3. Infinite Loop**

HTVM also supports infinite loops using the `%%%doc_keyWordLoopInfinite%%%` keyword without a defined number of iterations. The loop will continue running until a `%%%doc_keyWordBreak%%%` condition or manual termination occurs. The `%%%doc_keyWordContinue%%%` keyword can be used inside the infinite loop to skip the current iteration and continue with the next one.

#### Example (Infinite Loop):

```htvm
%%%htvmSnippet44%%%

```

Here, the loop runs indefinitely, printing the current value of `%%%doc_keyWordAIndex%%%`. When `%%%doc_keyWordAIndex%%%` reaches 5, the loop breaks. You can also use `%%%doc_keyWordContinue%%%` to skip iterations as needed.

---

### **4. While Loop**

The `%%%doc_keyWordWhileLoop%%%` loop in HTVM works like a typical while loop in other languages. It continues to execute the loop body as long as the specified condition evaluates to true.

#### Example (While Loop):

```htvm
%%%htvmSnippet45%%%

```

In this example, the `%%%doc_keyWordWhileLoop%%%` loop runs once because the condition is initially true, then changes `var1` to true, causing the loop to terminate.

---

### **Array Example in Loop**

HTVM also allows arrays, which can be used in loops for more complex tasks. Here’s an example that iterates over an array:

```htvm
%%%htvmSnippet46%%%

```

In this case, the loop iterates through each element of the array `arr123` using `%%%doc_keyWordAIndex%%%` to reference the array's index.

---

### **Variable Example in Loop**

With HTVM, you can also use variables to control loops. Here's an example:

```htvm
%%%htvmSnippet47%%%

```

This example shows how HTVM allows you to use variables like `var1` to control the number of iterations in the loop, with `%%%doc_keyWordAIndex%%%` printing the current iteration number.

---

### **Key Notes:**
- **`%%%doc_keyWordAIndex%%%`**: Used in all loops except for `%%%doc_keyWordWhileLoop%%%` loops.
- **`%%%doc_keyWordALoopField%%%`**: Used only in `%%%doc_keyWordLoopParse%%%` to reference the current field.
- **`%%%doc_keyWordContinue%%%`**: Can be used in any loop to skip the current iteration and continue with the next one. When converting to Lua, place the `::%%%doc_keyWordContinue%%%` at the end of the loop, just before it ends.

---

### **Lua Conversion**

For the **%%%doc_keyWordLoop%%%**, **%%%doc_keyWordLoopParse%%%**, and **%%%doc_keyWordLoopInfinite%%%** types, the Lua conversion looks like this:

```htvm
%%%htvmSnippet48%%%

```

In Lua, the conversion for these loops would use the `goto` statement to achieve the continue behavior. Here's how it would look in Lua:

```lua
function infinite_HTVM_Lua_Loop_HTVM()
    local i = 0
    return function()
        i = i + 1
        return i
    end
end

function LoopParseFunc(varString, delimiter1, delimiter2)
    local items = {}
    delimiter1 = delimiter1 or ""
    delimiter2 = delimiter2 or ""
    -- Changed: Don't escape the delimiters since we want them literal
    -- Just use them directly in the pattern
    if delimiter1 == "" and delimiter2 == "" then
        for i = 1, #varString do
            table.insert(items, varString:sub(i, i))
        end
    else
        -- Changed: Simplified pattern to directly match \n and \r
        local pattern = delimiter1 .. delimiter2
        for item in varString:gmatch("([^" .. pattern .. "]+)") do
            table.insert(items, item)
        end
    end
    return items
end

-- Regular loop example
for A_Index1 = 0 + 1 , 10 + 0 do
    if (A_Index1 % 2 == 0) then
        goto continue0
    end
    -- Output only odd numbers from 1 to 9
    print(A_Index1)
    ::continue0::
end

print("=====================")

-- Infinite loop example
for A_Index2 in infinite_HTVM_Lua_Loop_HTVM() do
    if (A_Index2 % 2 == 0) then
        goto continue1
    end
    -- Output only odd numbers from 1 to 9
    print(A_Index2)
    if (A_Index2 == 9) then
        break
    end
    ::continue1::
end

print("=====================")

-- Loop, Parse loop example
var1 = "hello whats up bro how are you doing"
items3 = LoopParseFunc(var1, " ")
for A_Index3 , A_LoopField3 in ipairs(items3) do
    A_LoopField3 = items3[A_Index3 - 0]
    if (A_LoopField3 == "bro") then
        goto continue2
    end
    -- 3 will never print
    print(A_Index3)
    ::continue2::
end
```

This approach with `::%%%doc_keyWordContinue%%%` is used only for the 3 types of loops but NOT the `%%%doc_keyWordWhileLoop%%%` loop.

> **Note:** Lua does not support a native `continue` statement. To mimic this behavior, we use a labeled `goto`—specifically `goto continue`—followed by a `::continue::` label at the end of the loop.  
> This approach is **only required when converting to Lua**. If you're using HTVM with JavaScript, Python etc... as the target language, there's **no need to write or worry about `::continue`**—it's automatically ignored or excluded in those environments.

---

### **Conclusion**

In HTVM, we have three main types of loops:

1. **Regular Loop** - `%%%doc_keyWordLoop%%%` - Simple iteration over a specified number of times.
2. **Loop Parse** - `%%%doc_keyWordLoopParse%%%` - Iterates over fields in a string or text, with customizable delimiters.
3. **Infinite Loop** - `%%%doc_keyWordLoopInfinite%%%` - A loop that runs indefinitely until broken manually or a condition is met.
4. **While Loop** - `%%%doc_keyWordWhileLoop%%%` - A standard loop that runs while a condition is true.

Each of these loops is intuitive and makes it easy to handle a variety of looping needs. Make sure to use `%%%doc_keyWordAIndex%%%` and `%%%doc_keyWordALoopField%%%` where appropriate, and use the `%%%doc_keyWordContinue%%%` keyword to control loop flow. When converting to Lua, remember to add `::%%%doc_keyWordContinue%%%` just before the loop ends.

---
============&&&8&&&============
============***9***============
### Comments

[Go back](#htvm-documentation)

## **Comments in HTVM**

Comments are essential for writing clear and maintainable code. They allow you to document your code without affecting how it runs. In HTVM, there are different types of comments: **Standalone Comments**, **Multi-line Comments**, **Inline Comments**, and **Comments in Programming Blocks**. Here's how each of them works:

---

### **Standalone Comments:**

**Standalone comments** are written on their own line and **will convert** properly when transforming to **other HTVM languages** or any target programming languages. These comments are perfect for leaving explanations or notes that need to be preserved across conversions.

```htvm
%%%hlepComments1%%%

```

**💡 Tip:** Standalone comments are **ideal** when you need your notes to **convert** correctly across different languages and maintain clarity for others who may work with your code.

---

### **Multi-line Comments:**

**Multi-line comments** are used for writing longer explanations or comments that span multiple lines. They must **always start and end on their own lines**—you cannot place extra text before or after the opening and closing markers. Inside multi-line comments, you can write as much text as you want.

```htvm
%%%hlepComments2%%%
```

#### **⚠️ Important Rules:**
- The opening of a multi-line comment **must always be on its own line**. 
- The closing of a multi-line comment **must always be on its own line**.
- **🚨 WARNING**: If you write **code** inside multi-line comments, that code **MAY get converted** during language conversion! ❗️
  - The code **won’t run**, but **it could still appear in the final code**! 
  - This means that if you have code inside multi-line comments, **be extra cautious**. If you don’t want the code to be accidentally included or converted, consider using **regular standalone comments** instead.

**💡 Tip:** If you want the code inside multi-line comments to be **preserved** and not accidentally converted during the conversion process, **use regular standalone comments** instead of multi-line comments for code explanation. **Regular standalone comments** are safer for maintaining the integrity of your code.

**⚠️ You can't use multiline comments inside a `Gui` code block.**

---

### **Inline Comments:**

**Inline comments** are written on the same line as your code. They’re useful for short explanations but **will disappear** when converting to **another HTVM language** or to other programming languages (e.g., **Python**, **JavaScript**, **C++**, **etc.**). This makes them **not recommended**, especially if you're working with code that will be converted, as they might carry important context that others won’t be able to see.

```htvm
%%%hlepComments3%%%
```

**⚠️ Important:** **Avoid** using inline comments whenever possible. Inline comments **will disappear** even when converting to another HTVM language. This is because they won’t be included in the converted code. If you rely on these comments for important context, it’s better to avoid using them. **Not recommended**, unless you know exactly what you’re doing, as it can lead to the loss of important information when others view or convert your code.

> *Note:* When converting code that includes Multiline Comments with commented-out code, the code will be converted into the target language as well. This ensures that even commented-out code is reflected in the converted language, making it easier for others to understand or reuse. This can be especially useful when converting to another HTVM language. For example, if someone is reading your code and has converted it to their own HTVM language, any commented-out code will be converted into their language, allowing them to read and understand what you intended to comment out. But only inside multiline comments will the code be converted into the target language.
>
> Regular Standalone Comments will also be converted, but only the comment keyword will be converted—nothing inside them will be converted. Only code inside Multiline Comments will be converted into the target language.
>
> But don’t worry, that code will not run because it’s just text, though it will be converted. This means you can use Multiline Comments to explain something without needing to include any code. Just plain text will work as well.

---

### **Comments in Programming Blocks:**

**Comments in programming blocks** must use the correct syntax for the target language. This is a **must**, not a best practice. You have to use the correct comment syntax based on the target language (e.g., **Python**, **JavaScript**, **C++**, **etc.**) inside their respective programming blocks.

```py
# This is a Python comment inside a Python programming block.
```

**⚠️ Important:** When working with **programming blocks**, make sure that you use the correct comment **syntax for that programming block language**. Otherwise, you may encounter issues in the code. Make sure you know which **characters** or **keywords** are used for comments in that language (for example, **#** for Python or **//** for JavaScript) to avoid mistakes.

---
============&&&9&&&============
============***10***============
### GUI (Graphical User Interface with HTVM)

[Go back](#htvm-documentation)

**⚠️ Language Limitation: JavaScript Only**

The GUI feature in HTVM allows for the creation of graphical user interfaces specifically for **web browsers (JavaScript)**. It generates the necessary HTML and JavaScript code. It **does not** support creating native GUIs for Python, C++, or other desktop environments. Using these commands when targeting non-JS languages will not work.

HTVM's GUI system lets you build interfaces with elements like buttons, text, edit fields, pictures, and more, using a simplified, flexible syntax designed for efficiency and fewer keystrokes. HTVM handles the basic HTML page setup implicitly when GUI commands are present.

### GUI Commands

HTVM uses two primary commands for building GUIs: `gui` for creating elements and containers, and `guicontrol` for modifying existing elements.

#### `gui` Command

This command is used to **add new elements** (like buttons, text) or **create container `div`s** to organize your layout.

**Syntax:**

```htvm
%%%doc_keyWordComment%%% Create a container (div) - Options separated by spaces OR commas
gui [Option1:Value1] [Option2:Value2] ...
gui [Option1:Value1],[Option2:Value2],...

%%%doc_keyWordComment%%% Add a specific control element - ElementType followed by space/comma separated options
gui &lt;ElementType&gt; [Option1:Value1] [Option2:Value2] ...
gui &lt;ElementType&gt;,[Option1:Value1],[Option2:Value2],...
```

*   **`&lt;ElementType&gt;`**: Specifies the type of control to add (e.g., `button`, `text`, `edit`). If omitted, a container (`div`) is created.
*   **`[Options...]`**: A series of options defining the element's properties. **Options can be separated by SPACES or COMMAS.**

**Option Flexibility:**

1.  **Separators**: Options can be separated by **SPACES** or **COMMAS**. You can mix them.

```htvm
%%%doc_keyWordComment%%% Space separated is often cleaner also different style of defining values
gui button x:50 y100 w"200px" h:"30px"
%%%doc_keyWordComment%%% Comma separated also works
gui button,x:"50px",y:"100px",w:"200px",h:"30px"
```

2.  **Key-Value Format**: Use `key:value` or single-letter prefixes `kvalue`. Many aliases exist (see [Options & Aliases](#options--aliases)).
3.  **Case Insensitivity**: Option *keys* and element types are case-insensitive. Option *values* (like IDs, text content, callback names) are case-sensitive.
4.  **`add` Keyword**: Optional and ignored (`gui add button` is the same as `gui button`).
5.  **Grouping**: Options can span multiple lines using `{...}`, `[...]`, or `(...)` for readability. Separator rules (spaces or commas) still apply inside the group.

```htvm
%%%doc_keyWordComment%%% Single line with spaces
gui button x:"10px" y:"10px" w:"100px" h:"30px" id:"myBtn" callback:MyAction value:"Click"

%%%doc_keyWordComment%%% Multi-line grouping (using spaces within the lines)
gui button {
    x:"10px" y:"10px"
    width:"100px" height:"30px"
    id:"myBtn"
    callback:MyAction
    value:"Click"
}
```

**Parenting & Default Container:**

*   Every element belongs inside a container.
*   If no `parentId` is specified when using the `gui` command to create an element, it is placed in the default background container (internally referred to as `div0`).
*   To place an element inside *your* custom container (e.g., one created with `gui id:"myPanel" ...`), you **must** use the `parentId:"myPanel"` option on the element being created.

#### `guicontrol` Command

Modifies properties of an **existing** GUI element.

**Syntax:**

```htvm
%%%doc_keyWordComment%%% Single line modification
guicontrol [Option1:Value1] [Option2:Value2] ...
guicontrol [Option1:Value1],[Option2:Value2],...

%%%doc_keyWordComment%%% Multi-line modification using flexible grouping (), [], or {}
guicontrol (
    Option1:Value1
    Option2:Value2
    ...
)
```

*   **`[Options...]`**: **SPACE or COMMA-SEPARATED** options.
    *   **MUST** include `id:&lt;element_id&gt;` (e.g., `id:"myButton"`) to target the element.
    *   **`parentId` Requirement (CRITICAL CLARIFICATION):**
        *   **Case 1: No Custom Containers Created:** If your entire script **only** adds elements directly to the background (never using `gui { id:"..." ... }` to create a custom container), then `parentId` is **optional** for `guicontrol`. HTVM will assume the target element is on the default background (`div0`).
        *   **Case 2: Custom Containers Exist:** As soon as you create **even one** custom container using `gui { id:"..." ... }`, the `parentId` option becomes **mandatory** for **all** `guicontrol` commands to avoid ambiguity.
            *   To target an element **inside** a custom container: Use `parentId:"containerId"`.
            *   To target an element that is still on the **default background** (or a top-level container itself): Don't use `parentId:"..."`.
    *   Other options specify the changes (e.g., `value:"NewText"`, `isVisible:false`).

**Mapping HTH Actions to HTVM Options (using `guicontrol`):**

*   **Move/Resize**: Use `x:`, `y:`, `width:`, `height:` options with pre-formatted string values (e.g., `x:varX_px`).
*   **Text**: Use `value:` (e.g., `guicontrol id:"myLabel",value:"New Text"`).
*   **Picture**: Use `value:` with a new URL (e.g., `guicontrol id:"myImage",value:"http://new.url/img.png"`).
*   **Hide/Show**: Use `isVisible:false` or `isVisible:true`.
*   **Enable/Disable**: Use `isEnabled:false` or `isEnabled:true`.
*   **Focus**: Use `focus:true`.
*   **Destroy**: Use `isDeleting:true`.
*   **Font**: Use `size:` for font size (e.g., `size:16`) and `color:` for text color (e.g., `color:"#FF0000"`). Use `rawCss:` for font family (e.g., `rawCss:"font-family:Courier;"`).

#### Multiple GUI Windows (`num:` prefix - *NOT SUPPORTED*)

HTVM **does not** use HTH's `Gui 2:`, `Gui 3:` syntax. Simulate multiple areas by:
1.  Creating container `div`s: `gui id:"window1",...`, `gui id:"window2",...`
2.  Placing elements inside using `parentId:"window1"` or `parentId:"window2"`.
3.  Toggling visibility using `guicontrol id:"window1",isVisible:false` etc.

### GUI Elements (Controls)

Add elements using `gui &lt;ElementType&gt; [Options...]`:

| Element Type | Description                                     | Default ID Format | Default Callback Format | Notes                                                                           |
| :----------- | :---------------------------------------------- | :---------------- | :---------------------- | :------------------------------------------------------------------------------ |
| `button`     | Clickable button                                | `button` + Counter  | `Button` + Counter      |                                                                                 |
| `text`       | Static text label                               | `text` + Counter    | `Text` + Counter        |                                                                                 |
| `edit`       | Text input field                                | `edit` + Counter    | `Edit` + Counter        | Use callback + global var/OSP struct to get value.                              |
| `picture`    | Image display (`&lt;img&gt;`)                         | `picture` + Counter | `Picture` + Counter     | `value` is URL. Local paths *not* auto-encoded.                               |
| `toggle`     | Checkbox / Switch                               | `toggle` + Counter  | `Toggle` + Counter      | `value` is `true`/`false`. `A_Value` in callback is boolean.                    |
| `rectangle`  | Colored rectangle (`&lt;div&gt;`)                     | `rectangle` + Counter | `Rectangle` + Counter | Use `backgroundColor`.                                                        |
| `circle`     | Colored circle (`&lt;div&gt;` + round border)         | `circle` + Counter  | `Circle` + Counter      | Use `backgroundColor`.                                                        |
| `video`      | Video player (`&lt;video&gt;`)                        | `video` + Counter   | `Video` + Counter       | `value` is URL (video file or YouTube embed).                                 |
| `dropdown`   | Select dropdown (`&lt;select&gt;`)                    | `dropdown` + Counter| `Dropdown` + Counter    | `value` is pipe separated options. **element1&#124;element2&#124;element3** |
| `iframe`     | Embed external content (`&lt;iframe&gt;`)             | `iframe` + Counter  | `Iframe` + Counter      | `value` is URL.                                                               |

(Counters start at 0 for each type, e.g., `button0`, `Button0`, `edit0`, `Edit0`...)

#### Exmaple:

```htvm
%%%htvmSnippet50%%%

```

### Options & Aliases 


Configure elements using **SPACE or COMMA-SEPARATED** options.

**Key Rules:**

1.  **Separators**: Use Spaces or Commas between options (`x:"10px" y:"10px"` or `x:"10px",y:"10px"`).
2.  **No Spaces in Direct Values**: Store values like `var1 + var2` in a variable (`str hw := var1 + var2`) and use `value:hw`.
3.  **Quote Literal IDs/ParentIDs**: Use quotes for string literals (`id:"myId"`). Do not quote variables (`id:myIdVar`).
4.  **Pre-concatenate Units**: For `x`, `y`, `width`, `height`, prepare string variables including `px` or `%` **before** using them in the command (e.g., `str width_px := myWidth . "px"`, then use `width:width_px`).
5.  **Case Sensitivity**: Keys/aliases/types are case-insensitive; values are case-sensitive.

**Common Options Table:**

| Canonical JS      | Purpose                     | Single-Letter Prefix | Colon Aliases (Examples)                    | Notes                                                                 |
| :---------------- | :-------------------------- | :------------------- | :------------------------------------------ | :-------------------------------------------------------------------- |
| `id`              | Unique Element Identifier   | `i`, `v`             | `id`, `elementId`, `eid`                    | String. **Quote if literal.** Defaults if omitted.                    |
| `parentId`        | ID of Container Element     | `p`                  | `parentId`, `pid`, `divId`                  | String. Defaults to `"div0"`. **Quote if literal.**                   |
| `x`               | Horizontal Position         | `x`                  | `x`, `xPos`, `xCoord`                       | **String var required (e.g., `myVarX_px`).** Supports `px` or `%`.    |
| `y`               | Vertical Position           | `y`                  | `y`, `yPos`, `yCoord`                       | **String var required (e.g., `myVarY_px`).** Supports `px` or `%`.    |
| `width`           | Element Width               | `w`                  | `width`, `wight`, `widh`                    | **String var required (e.g., `myVarW_px`).** Supports `px` or `%`.    |
| `height`          | Element Height              | `h`                  | `height`, `hight`, `heigth`                 | **String var required (e.g., `myVarH_px`).** Supports `px` or `%`.    |
| `zIndex`          | Stacking Order              | `z`                  | `zIndex`, `z-index`                         | Integer.                                                              |
| `value`           | Content/State             | `d`                  | `value`, `val`, `displayValue`              | Text/URL/Bool/Options. **Use variable for spaces/commas.**          |
| `placeholder`     | Placeholder text for Edit | `q`                  | `placeholder`, `plc`, `ph`, `grayText`      | String. **Use variable for spaces.**                                  |
| `callback`        | Function on Interaction     | `g`, `f`             | `callback`, `func`, `fn`, `call`            | String (HTVM Label Name). Defaults if omitted.                        |
| `backgroundColor` | Background Color            | `o`                  | `backgroundColor`, `bgColor`, `bg`, `bgc` | String (`"red"`, `"#FF0000"`). Auto-adds `#` for hex.                 |
| `color`           | Text/Foreground Color       | `c`                  | `color`, `clr`                              | String (`"blue"`, `"#00F"`). Auto-adds `#` for hex.                 |
| `rounding`        | Corner Rounding (px)        | `r`                  | `rounding`, `round`, `rnd`                  | Integer (pixels).                                                     |
| `border`          | Element Border              | `b`                  | `border`, `boder`, `outline`                | String (CSS syntax). **Use var for spaces.**                          |
| `rawCss`          | Additional CSS Styles       | `l`                  | `rawCss`, `css`, `style`, `luxury`          | String (CSS rules). **Use var for multiple.**                         |
| `size`            | Font Size (px)              | `s`                  | `size`, `sz`                                | Integer (pixels).                                                     |
| `isEnabled`       | Enable/Disable Interaction  | `a`                  | `isEnabled`, `isEnb`                        | Boolean (`true`/`false`).                                             |
| `isVisible`       | Show/Hide Element           | `u`                  | `isVisible`, `isVsb`                        | Boolean (`true`/`false`).                                             |
| `isDeleting`      | Remove Element from GUI   | `n`                  | `isDeleting`, `del`, `remove`, `rm`         | Boolean (`true`). Use with `guicontrol`.                              |
| `focus`           | Focus on an Element from GUI | `NONE`               | `focus`                                     | Boolean (`true`). Use with `guicontrol`.                              |

*(See HTVM source (`guiParserStep4`) for a full alias list.)*

#### Exmaple:

```htvm
%%%htvmSnippet51%%%

```

### Callbacks and State Management

Callbacks connect GUI events to HTVM logic (labels ending in `subout`). Logic **must start on the line AFTER the label**, not on the same line. Use `await` before functions like `MsgBox` that return Promises in JavaScript.

**Managing State (Input Example):**

To retrieve data entered by the user (e.g., in an `edit` field), store the data from the input's callback (`A_Value`) into a shared state, typically using global variables or an OSP struct. Using an OSP `struct` is often better for organization, but global variables work too.

**Getting Input Example (using OSP Struct - Recommended):**

```htvm
%%%htvmSnippet52%%%

```

**Callback Parameters:** `A_Id`, `A_Value`, `A_Event` provide context within the callback label.

### Examples

*(Using space separation, pre-concatenated units, OSP struct for state where beneficial, correct callback formatting, and await for MsgBox)*

**Example 1: Simple Input and Button (using OSP Struct)**

```htvm
%%%htvmSnippet53%%%

```

**Example 2: Sized Container (Hardcoded)**

```htvm
%%%htvmSnippet54%%%

```

**Example 3: Button Grid using Loops (Using A_Id)**

```htvm
%%%htvmSnippet55%%%

```

**Example 4: Toggle, Dropdown, Picture Update (using OSP Struct)**

```htvm
%%%htvmSnippet56%%%

```

**Example 5: Using `rawCss` for Styling**

```htvm
%%%htvmSnippet57%%%

```

**Example 6: HTVM Simulated Numeric Adjuster Using Buttons and Input Field (0–100 Range)**

```htvm
%%%htvmSnippet58%%%

```

**Example 7: `Tic-tac-toe`**

```htvm
%%%htvmSnippet59%%%

```

### Summary

HTVM's GUI system offers a simplified yet powerful way to build graphical user interfaces directly within your HTVM code, targeting **JavaScript web environments**. By using the intuitive `gui` command to define elements and containers, and `guicontrol` to modify them dynamically, you can build interactive web applications. The system leverages flexible option syntax (spaces, commas, shorthand, multi-line grouping) and automatically handles underlying HTML/CSS/JS generation, adhering to HTVM's philosophy of **reducing keystrokes and complexity**. Understanding the conditional requirement for `parentId` in `guicontrol` (it's only optional if no custom containers are defined) is key to correctly manipulating elements.

The `gui` and `guicontrol` features allows developers to focus on interface logic and layout using their custom HTVM syntax, bridging the gap between high-level design and functional web UIs.

---
============&&&10&&&============
============***11***============
### Liner

[Go back](#htvm-documentation)

### **The `Liner` Construct: A Weighted Condition Evaluator**

The `Liner` construct is a unique and powerful feature in HTVM designed for evaluating a series of boolean conditions in a clean, readable block. It acts as a "truthiness accumulator," calculating both a simple count and a weighted score of how many conditions in the list evaluate to `true`.

This is an ideal tool for scenarios where you need to check multiple prerequisites, such as game achievements, form validation, or AI decision-making, and get a quantifiable measure of success.

**Liner Block Start** = `Liner`

**Liner Block End** = `subout`

### **Syntax**

A `Liner` block starts with the `Liner` keyword followed by an optional name, and ends with `subout`. Inside the block, you list one condition per line.

Each condition can optionally be prefixed with a `weight:` to contribute to a weighted score. If no weight is provided, it defaults to `1`.

```htvm
Liner [OptionalName]
    "A condition with an explicit weight"
    [weight1]: [condition1]
    [weight2]: [condition2]
    "A condition with a default weight of 1"
    [condition3] 
subout
```

### **Contextual `A_` Variables**

After a `Liner` block is executed, the following global `A_` variables are populated with the results of the evaluation. **These variables are reset before each new `Liner` block runs.**

| Variable             | Description                                                                                              |
| :------------------- | :------------------------------------------------------------------------------------------------------- |
| `A_SUCCESS`          | An integer representing the raw count of conditions that evaluated to `true`.               |
| `A_SUCCESS_WEIGHTED` | An integer representing the sum of the weights of all conditions that evaluated to `true`. |
| `A_TOTAL_WEIGHT`     | An integer representing the sum of all possible weights for every condition listed in the block.         |
| `A_SUCCESS_ALL`      | A boolean that is `true` only if **every single condition** in the block was met.           |

### **Comprehensive Examples**

The true power of the `Liner` construct is in its versatility. Below are several examples demonstrating its use in different scenarios, from simple checklists to replacing complex conditional logic.

#### **Example 1: Basic Daily Checklist (No Weights)**

The simplest use of `Liner` is as a raw counter for completed tasks. Here, we're just checking off daily chores. The default weight for each item is `1`.
```htvm
%%%htvmSnippet84%%%

```
**Expected Output:**
*   `A_SUCCESS`: `3`
*   `A_TOTAL_WEIGHT`: `4`
*   `A_SUCCESS_ALL`: `false`

---

#### **Example 2: Form Validation with Weights**

Here, `Liner` is used to validate a user registration form. Some fields are critical (high weight), while others are optional (low weight). This allows for nuanced validation logic.

```htvm
%%%htvmSnippet85%%%

```
**Expected Output:**
*   `A_SUCCESS_WEIGHTED`: `20` (5 for username + 5 for password + 10 for terms)
*   `A_TOTAL_WEIGHT`: `21`
*   `A_SUCCESS_ALL`: `false` (because email is empty)
*   The final status will be "Registration successful."

---

#### **Example 3: Mixing Weighted and Unweighted Conditions**

You can freely mix conditions with explicit weights and those without. Any condition without a specified weight automatically defaults to a weight of `1`. This is useful for scenarios with a mix of high-priority and standard-priority checks.

In this example, we're checking if a player can open a legendary treasure chest.

```htvm
%%%htvmSnippet86%%%

```
**Execution Analysis:**
*   `hasLegendaryKey` is `true` (Weight 10) -> **Success**
*   `playerLevel >= 50` is `true` (Default Weight 1) -> **Success**
*   `isNightTime` is `false` (Default Weight 1) -> Failure
*   `hasGuildBuff` is `true` (Weight 2) -> **Success**

**Expected Output:**
*   `A_SUCCESS`: `3`
*   `A_SUCCESS_WEIGHTED`: `13` (10 + 1 + 2)
*   `A_TOTAL_WEIGHT`: `14` (10 + 1 + 1 + 2)
*   `A_SUCCESS_ALL`: `false`
*   The final result will be "The chest creaks open!" because the weighted score of 13 is greater than or equal to the required 11.

---new_osp := ""

#### **Example 4: Replacing Complex Weighted Logic**

This example shows how `Liner` drastically cleans up code that requires manual weighted scoring.

**Before (The Old, Cluttered Way):**
```htvm
%%%htvmSnippet87%%%

```

**After (The Clean, `Liner` Way):**
```htvm
%%%htvmSnippet88%%%

```
The `Liner` version is superior in every way. It's more readable, less error-prone (no manual score tracking or total weight calculation), and the logic is self-contained. Adding or removing conditions is trivial in the `Liner` block, whereas it requires careful modification of multiple lines in the manual approach.

### **Conclusion**

The `Liner` construct provides a clean, declarative syntax for a common but complex programming pattern. By abstracting the counting and weighting logic into the language itself, it allows you to write more expressive and maintainable code, perfectly embodying the HTVM philosophy of solving real-world problems with elegant, developer-centric tools.

---
============&&&11&&&============
============***12***============
# OSP (Ordinal Struct Programming)

[Go back](#htvm-documentation)

OSP is HTVM's built-in system for organizing data using **structs** and **instances**. It provides a clean, developer-friendly way to define data structures and create multiple independent copies of them with minimal syntax.

---

## Table of Contents

1. [Structs: The Basics](#structs-the-basics)
2. [Type Inference](#type-inference)
3. [Instances: Creating Data](#instances-creating-data)
4. [Arrays in Structs](#arrays-in-structs)
5. [Organization with `crew` and `alliance`](#organization-with-crew-and-alliance)
6. [Syntax Styles: New vs. Old](#syntax-styles-new-vs-old)
7. [The Formatter (Optional Tool)](#the-formatter-optional-tool)
8. [Complete Examples](#complete-examples)
9. [Common Patterns](#common-patterns)

---

## Structs: The Basics

A `struct` is a container for related data. You define it once, then create multiple independent **instances** of it.

**Basic struct definition:**

```htvm
struct Player
    health: 100
    mana: 50
subout
```

This defines a struct named `Player` with two properties: `health` and `mana`, both initialized to their respective values.

**Key rule:** Always close a struct with `subout` (curly braces are `NOT` allowed for the new syntax with `subout`).

---

## Type Inference

When you use the new syntax (colon-style with `subout`), HTVM automatically infers types from the initial values:

- **`int`** ← inferred from numeric values (e.g., `100`, `50`)
- **`str`** ← inferred from string values (e.g., `"hello"`)
- **`float`** ← inferred from floating-point values (e.g., `3.14`, `2.5`)

**Examples of inference:**

```htvm
struct Character
    name: "Warrior"           ; Inferred as str
    level: 5                  ; Inferred as int
    experience: 1250.75       ; Inferred as float
subout
```

### What About Booleans and Arrays?

**Booleans and arrays are NOT inferred.** You must use the `prop` keyword explicitly for these types:

```htvm
struct Player
    health: 100              ; Inferred as int
    prop bool isAlive        ; Must use prop for bool
    prop arr str inventory   ; Must use prop for arrays
subout
```

---

## Instances: Creating Data

⚠️ **CRITICAL BEFORE YOU START:** If you plan to use `instance` anywhere in your code, **NEVER use `crew` or `alliance` in that project.** Mixing them causes bugs. You must choose one approach: either instances with standalone structs, OR crews/alliances for organization (no instances at all).

An **instance** is an independent copy of a struct with its own data. You create instances using the `instance` keyword:

**Basic instance creation:**

```htvm
struct Player
    health: 100
    mana: 50
subout

main
    instance Player as hero
    instance Player as goblin
    hero.health := 200
    goblin.health := 30
    print("Hero health: " . STR(hero.health))
    print("Goblin health: " . STR(goblin.health))
```

**How it works:**

- `instance Player as hero` creates a new variable `hero` with all of `Player`'s properties
- Each instance is **completely independent** — modifying `hero.health` does NOT affect `goblin.health`
- All instances are **globally accessible** by their name (below the point of creation)
- Instance names become global variables that hold the struct's data

---

## Arrays in Structs

Arrays must be declared using the `prop` keyword. You cannot use type inference for arrays.

**Declaring array properties:**

```htvm
struct Inventory
    prop arr str items
    prop arr int quantities
subout

main
    instance Inventory as backpack
    backpack.items.add("sword")
    backpack.items.add("shield")
    backpack.quantities.add(1)
    backpack.quantities.add(1)
```

**Array methods:**

- **`.add(value)`** or **`.push(value)`** — Add an item to the array (both work the same)
- **`.size()`** — Get the array length
- **`[index]`** — Access element by index (zero-based)

**Complete array example:**

```htvm
struct Player
    health: 100
    prop arr str spells
subout

main
    instance Player as wizard
    wizard.spells.add("Fireball")
    wizard.spells.add("Ice Storm")
    wizard.spells.add("Lightning")
    
    Loop, % wizard.spells.size() {
        print(wizard.spells[A_Index])
    }
```

---

## Organization with `crew` and `alliance`

For larger projects, you can organize structs using `crew` and `alliance` containers:

- **`alliance`** — Top-level organizational container
- **`crew`** — Sub-container within an alliance (or standalone)

**Purpose:** Group related structs logically and avoid naming conflicts.

**Important:** Crew and alliance use `{}` syntax, not `subout`.

**Using `crew`:**

```htvm
crew Audio {
    struct Settings
        volume: 80
        pitch: 1.0
    subout
}

main
    ; Access the struct's default properties directly
    Audio.Settings.volume := 100
    print("Audio volume: " . STR(Audio.Settings.volume))
```

**Using `alliance`:**

```htvm
alliance Game {
    crew Entities {
        struct Player
            health: 100
            mana: 50
        subout
    }
    
    crew UI {
        struct Button
            x: 0
            y: 0
            label: "Click me"
        subout
    }
}

main
    ; Access struct properties using their full path
    Game.Entities.Player.health := 200
    Game.UI.Button.label := "Start Game"
    print("Player health: " . STR(Game.Entities.Player.health))
```

### ⚠️ CRITICAL: Never Mix Crew/Alliance with Instances

**If you use `instance` in your code, you CANNOT use `crew` or `alliance` anywhere in that same project.** This applies even to standalone structs. Mixing them causes bugs.

You must choose ONE approach:
- **Option A:** Use standalone structs + instances (NO crews/alliances anywhere)
- **Option B:** Use crews/alliances for organization (NO instances anywhere)

**This causes bugs:**
```htvm
crew Audio {
    struct Settings
        volume: 80
    subout
}

struct Player
    health: 100
subout

main
    ; DON'T mix them like this
    instance Player as hero  ; This will cause bugs if you have crew/alliance
    Audio.Settings.volume := 100
```

**Option A (instances only):**
```htvm
struct Player
    health: 100
subout

struct Settings
    volume: 80
subout

main
    instance Player as hero
    instance Settings as config
```

**Option B (crew/alliance only):**
```htvm
crew Audio {
    struct Settings
        volume: 80
    subout
}

crew Game {
    struct Player
        health: 100
    subout
}

main
    ; Access properties directly, no instances
    Game.Player.health := 200
    Audio.Settings.volume := 100
```

---

## Syntax Styles: New vs. Old

HTVM supports two syntax styles. You can use them separately or mix them in the same struct.

### New Style (Inference with `subout`):

```htvm
struct Player
    health: 100
    mana: 50
    name: "Hero"
subout
```

Clean, minimal, types inferred automatically.

### Old Style (Explicit with `prop` and `{}`):

```htvm
struct Player {
    prop int health := 100
    prop int mana := 50
    prop str name := "Hero"
}
```

Verbose, but explicit types.

### Mixed Style:

```htvm
struct Player
    health: 100
    name: "Hero"
    prop bool isAlive
    prop arr str inventory
subout
```

Use inference for simple types, `prop` for complex ones.

---

## The Formatter (Optional Tool)

The formatter is a **code beautification tool**. It is **completely optional** and does NOT affect compilation.

**What the formatter does:**

- Converts new syntax (`health: 100` with `subout`) to old syntax (`prop int health := 100` with `{}`)
- Adds explicit types to all properties
- Removes indentation from `main` blocks (standard formatting)
- Keeps instance declarations clean and unchanged

**Using the formatter:**

In HT-IDE, press `Ctrl+Shift+F` to format your code.

**Important:** You do NOT need to use the formatter. Your code compiles the same way with or without formatting.

### ⚠️ Important: You Don't Have to Convert Everything

After formatting, **you do NOT have to convert every struct back to inference syntax.** The old syntax with `{}` and `prop` keywords works fine and compiles without any issues.

**You can:**
- Keep some structs in old syntax (`{}` with `prop`)
- Convert only the structs you want to inference syntax
- Mix both syntaxes in the same file

**Example: Mixed syntax in one file:**
```htvm
; Old style (formatted) — perfectly fine to leave as-is
struct Audio {
    prop int volume := 80
    prop float pitch := 1.0
}

; New style (inference) — you converted this one
struct Player
    health: 100
    mana: 50
subout

; Another old style — no need to convert
struct Settings {
    prop str theme := "dark"
}
```

Both syntaxes compile identically. Convert only when you want to, not because you have to.

**If you want to selectively convert a struct back to new syntax:**

1. Remove the opening `{` and closing `}`
2. Add `subout` at the bottom
3. *Optional:* Remove `prop` keywords and explicit types (or keep them — both work)

Example of converting back:
```htvm
; Before (formatted style)
struct Player {
    prop int health := 100
    prop int mana := 50
}

; After (new inference style, prop removed)
struct Player
    health: 100
    mana: 50
subout
```

Or keep `prop` if you prefer (both are valid):

```htvm
; New style with prop kept
struct Player
    prop int health := 100
    prop int mana := 50
subout
```

**Bottom line:** Don't feel obligated to rewrite all your structs. The formatter output works fine as-is.

---

## Complete Examples

### Example 1: Simple Character System

```htvm
struct Character
    name: "Adventurer"
    level: 1
    experience: 0.0
    prop bool isAlive
subout

main
    instance Character as hero
    instance Character as enemy
    
    hero.level := 10
    hero.experience := 5000.5
    enemy.level := 5
    
    print("Hero: " . hero.name . " (Level " . STR(hero.level) . ")")
    print("Enemy: " . enemy.name . " (Level " . STR(enemy.level) . ")")
    print("Experience: " . STR(hero.experience))
```

### Example 2: Inventory System

```htvm
struct Item
    name: "Sword"
    value: 50
subout

struct Player
    name: "Warrior"
    gold: 1000
    prop arr str inventory
subout

main
    instance Player as adventurer
    
    adventurer.inventory.add("Iron Sword")
    adventurer.inventory.add("Shield")
    adventurer.inventory.add("Health Potion")
    
    print("Inventory:")
    Loop, % adventurer.inventory.size() {
        print("  - " . adventurer.inventory[A_Index])
    }
```

### Example 3: Multiple Standalone Structs

```htvm
struct Weapon
    name: "Sword"
    damage: 25
    durability: 100
subout

struct Character
    health: 100
    mana: 50
    strength: 15
subout

main
    instance Character as player
    instance Weapon as sword
    
    player.health := 75
    sword.damage := 30
    
    print("Player Health: " . STR(player.health))
    print("Weapon Damage: " . STR(sword.damage))
```

### Example 4: Arrays with Multiple Properties

```htvm
struct GameState
    currentLevel: 1
    prop arr str achievements
    prop arr int scores
    prop arr str playerNames
subout

main
    instance GameState as game
    
    game.achievements.add("First Kill")
    game.achievements.add("Level 10")
    game.achievements.add("Boss Defeated")
    
    game.scores.add(1000)
    game.scores.add(2500)
    game.scores.add(5000)
    
    game.playerNames.add("Hero")
    game.playerNames.add("Villain")
    game.playerNames.add("NPC")
    
    print("=== Achievements ===")
    Loop, % game.achievements.size() {
        print(game.achievements[A_Index])
    }
    
    print("=== Scores ===")
    Loop, % game.scores.size() {
        print("Score: " . STR(game.scores[A_Index]))
    }
```

---

## Common Patterns

### Pattern 1: Default Values with Instances

```htvm
struct Player
    health: 100
    mana: 50
subout

main
    instance Player as hero
    instance Player as goblin
    ; Both start with default values
    print("Hero: " . STR(hero.health))  ; 100
    print("Goblin: " . STR(goblin.health)) ; 100
    ; Then customize independently
    hero.health := 150
    goblin.health := 50
```

### Pattern 2: Mixed Property Types

```htvm
struct Settings
    volume: 75              ; int
    theme: "dark"          ; str
    brightness: 0.85       ; float
    prop bool soundEnabled  ; bool
    prop arr str languages ; array
subout
```

### Pattern 3: Array Properties with Multiple Instances

```htvm
struct Player
    name: "Hero"
    prop arr str inventory
    prop arr int stats
subout

main
    instance Player as hero
    instance Player as companion
    
    hero.inventory.add("Sword")
    hero.inventory.add("Shield")
    
    companion.inventory.add("Dagger")
    companion.stats.add(100)
    companion.stats.add(50)
```

### Pattern 4: Multiple Instances of the Same Struct

```htvm
struct Enemy
    health: 50
    damage: 10
subout

main
    instance Enemy as goblin1
    instance Enemy as goblin2
    instance Enemy as goblin3
    
    goblin1.health := 40
    goblin2.health := 55
    goblin3.health := 50
    
    print("Goblin 1 Health: " . STR(goblin1.health))
    print("Goblin 2 Health: " . STR(goblin2.health))
    print("Goblin 3 Health: " . STR(goblin3.health))
```

---

### Instance Independence

Each instance is a **completely independent copy** of the struct. Modifying one instance does NOT affect others.

```htvm
struct Item
    name: "Sword"
    quantity: 1
subout

main
    instance Item as item1
    instance Item as item2
    
    item1.quantity := 5
    print(item2.quantity)  ; Still 1, not affected
```

### No Constructor Arguments

You cannot pass initial values when creating an instance. All instances start with the struct's default values, which you can then modify.

```htvm
; This does NOT work:
; instance Player as hero with health = 200

; Instead, do this:
instance Player as hero
hero.health := 200
```

### Type Inference Limitations

Remember: **Only `int`, `str`, and `float` are inferred.** Everything else requires `prop`.

```htvm
struct Example
    count: 42              ; OK — inferred as int
    text: "hello"          ; OK — inferred as str
    ratio: 3.14            ; OK — inferred as float
    prop bool flag         ; Required — bool is not inferred
    prop arr str list      ; Required — arrays are not inferred
subout
```

---

## Summary

### The Golden Rule

**If you use `instance`, you CANNOT use `crew` or `alliance` anywhere in your project. Choose one approach.**

### Basic Rules

- **Structs** define data templates
- **Instances** create independent copies of standalone structs only
- **Type inference** keeps code clean (int, str, float only)
- **`prop`** keyword required for booleans, arrays, and explicit typing
- **`crew`/`alliance`** organize structs hierarchically (never with instances)
- **Formatter** is optional and just beautifies code
- **Scope** Only the global scope. If you define a struct inside a function or in main, it will not work and will cause issues.
- **Instances are completely independent**

### Critical Syntax Rules

1. **Curly braces are NOT allowed** when using new inference syntax with `subout`
2. **Never mix crew/alliance with instances** — pick one approach for your entire project
3. **Type inference** only works for `int`, `str`, `float` — everything else needs `prop`

### Quick Decision Guide

**Use instances if:**
- You need multiple independent copies of data
- You only use standalone structs
- You have NO crews/alliances in your project

**Use crews/alliances if:**
- You need to organize structs hierarchically
- You don't need multiple independent copies
- You'll never use the `instance` keyword

That's OSP! Simple, powerful, and ready for production.
============&&&12&&&============
============***13***============
# OSP (Ordinal Struct Programming)

[Go back](#htvm-documentation)

OSP is HTVM's built-in system for organizing data using **structs** and **instances**. It provides a clean, developer-friendly way to define data structures and create multiple independent copies of them with minimal syntax.

---

## Table of Contents

1. [Structs: The Basics](#structs-the-basics)
2. [Type Inference](#type-inference)
3. [Instances: Creating Data](#instances-creating-data)
4. [Arrays in Structs](#arrays-in-structs)
5. [Organization with `crew` and `alliance`](#organization-with-crew-and-alliance)
6. [Syntax Styles: New vs. Old](#syntax-styles-new-vs-old)
7. [The Formatter (Optional Tool)](#the-formatter-optional-tool)
8. [Complete Examples](#complete-examples)
9. [Common Patterns](#common-patterns)

---

## Structs: The Basics

A `struct` is a container for related data. You define it once, then create multiple independent **instances** of it.

**Basic struct definition:**

```htvm
struct Player
    health: 100
    mana: 50
subout
```

This defines a struct named `Player` with two properties: `health` and `mana`, both initialized to their respective values.

**Key rule:** Always close a struct with `subout` (curly braces are `NOT` allowed for the new syntax with `subout`).

---

## Type Inference

When you use the new syntax (colon-style with `subout`), HTVM automatically infers types from the initial values:

- **`int`** ← inferred from numeric values (e.g., `100`, `50`)
- **`str`** ← inferred from string values (e.g., `"hello"`)
- **`float`** ← inferred from floating-point values (e.g., `3.14`, `2.5`)

**Examples of inference:**

```htvm
struct Character
    name: "Warrior"           ; Inferred as str
    level: 5                  ; Inferred as int
    experience: 1250.75       ; Inferred as float
subout
```

### What About Booleans and Arrays?

**Booleans and arrays are NOT inferred.** You must use the `prop` keyword explicitly for these types:

```htvm
struct Player
    health: 100               ; Inferred as int
    prop isAlive: bool        ; Must use prop for bool
    prop inventory: arr str   ; Must use prop for arrays
subout
```

---

## Instances: Creating Data

⚠️ **CRITICAL BEFORE YOU START:** If you plan to use `instance` anywhere in your code, **NEVER use `crew` or `alliance` in that project.** Mixing them causes bugs. You must choose one approach: either instances with standalone structs, OR crews/alliances for organization (no instances at all).

An **instance** is an independent copy of a struct with its own data. You create instances using the `instance` keyword:

**Basic instance creation:**

```htvm
struct Player
    health: 100
    mana: 50
subout

main
    instance Player as hero
    instance Player as goblin
    hero.health := 200
    goblin.health := 30
    print("Hero health: " . STR(hero.health))
    print("Goblin health: " . STR(goblin.health))
```

**How it works:**

- `instance Player as hero` creates a new variable `hero` with all of `Player`'s properties
- Each instance is **completely independent** — modifying `hero.health` does NOT affect `goblin.health`
- All instances are **globally accessible** by their name (below the point of creation)
- Instance names become global variables that hold the struct's data

---

## Arrays in Structs

Arrays must be declared using the `prop` keyword. You cannot use type inference for arrays.

**Declaring array properties:**

```htvm
struct Inventory
    prop items: arr str
    prop quantities: arr int
subout

main
    instance Inventory as backpack
    backpack.items.add("sword")
    backpack.items.add("shield")
    backpack.quantities.add(1)
    backpack.quantities.add(1)
```

**Array methods:**

- **`.add(value)`** or **`.push(value)`** — Add an item to the array (both work the same)
- **`.size()`** — Get the array length
- **`[index]`** — Access element by index (zero-based)

**Complete array example:**

```htvm
struct Player
    health: 100
    prop spells: arr str
subout

main
    instance Player as wizard
    wizard.spells.add("Fireball")
    wizard.spells.add("Ice Storm")
    wizard.spells.add("Lightning")
    
    Loop, % wizard.spells.size() {
        print(wizard.spells[A_Index])
    }
```

---

## Organization with `crew` and `alliance`

For larger projects, you can organize structs using `crew` and `alliance` containers:

- **`alliance`** — Top-level organizational container
- **`crew`** — Sub-container within an alliance (or standalone)

**Purpose:** Group related structs logically and avoid naming conflicts.

**Important:** Crew and alliance use `{}` syntax, not `subout`.

**Using `crew`:**

```htvm
crew Audio {
    struct Settings
        volume: 80
        pitch: 1.0
    subout
}

main
    ; Access the struct's default properties directly
    Audio.Settings.volume := 100
    print("Audio volume: " . STR(Audio.Settings.volume))
```

**Using `alliance`:**

```htvm
alliance Game {
    crew Entities {
        struct Player
            health: 100
            mana: 50
        subout
    }
    
    crew UI {
        struct Button
            x: 0
            y: 0
            label: "Click me"
        subout
    }
}

main
    ; Access struct properties using their full path
    Game.Entities.Player.health := 200
    Game.UI.Button.label := "Start Game"
    print("Player health: " . STR(Game.Entities.Player.health))
```

### ⚠️ CRITICAL: Never Mix Crew/Alliance with Instances

**If you use `instance` in your code, you CANNOT use `crew` or `alliance` anywhere in that same project.** This applies even to standalone structs. Mixing them causes bugs.

You must choose ONE approach:
- **Option A:** Use standalone structs + instances (NO crews/alliances anywhere)
- **Option B:** Use crews/alliances for organization (NO instances anywhere)

**This causes bugs:**
```htvm
crew Audio {
    struct Settings
        volume: 80
    subout
}

struct Player
    health: 100
subout

main
    ; DON'T mix them like this
    instance Player as hero  ; This will cause bugs if you have crew/alliance
    Audio.Settings.volume := 100
```

**Option A (instances only):**
```htvm
struct Player
    health: 100
subout

struct Settings
    volume: 80
subout

main
    instance Player as hero
    instance Settings as config
```

**Option B (crew/alliance only):**
```htvm
crew Audio {
    struct Settings
        volume: 80
    subout
}

crew Game {
    struct Player
        health: 100
    subout
}

main
    ; Access properties directly, no instances
    Game.Player.health := 200
    Audio.Settings.volume := 100
```

---

## Syntax Styles: New vs. Old

HTVM supports two syntax styles. You can use them separately or mix them in the same struct.

### New Style (Inference with `subout`):

```htvm
struct Player
    health: 100
    mana: 50
    name: "Hero"
subout
```

Clean, minimal, types inferred automatically.

### Old Style (Explicit with `prop` and `{}`):

```htvm
struct Player {
    prop health: int := 100
    prop mana: int := 50
    prop name: str := "Hero"
}
```

Verbose, but explicit types.

### Mixed Style:

```htvm
struct Player
    health: 100
    name: "Hero"
    prop isAlive: bool
    prop inventory: arr str
subout
```

Use inference for simple types, `prop` for complex ones.

---

## The Formatter (Optional Tool)

The formatter is a **code beautification tool**. It is **completely optional** and does NOT affect compilation.

**What the formatter does:**

- Converts new syntax (`health: 100` with `subout`) to old syntax (`prop health: int := 100` with `{}`)
- Adds explicit types to all properties
- Removes indentation from `main` blocks (standard formatting)
- Keeps instance declarations clean and unchanged

**Using the formatter:**

In HT-IDE, press `Ctrl+Shift+F` to format your code.

**Important:** You do NOT need to use the formatter. Your code compiles the same way with or without formatting.

### ⚠️ Important: You Don't Have to Convert Everything

After formatting, **you do NOT have to convert every struct back to inference syntax.** The old syntax with `{}` and `prop` keywords works fine and compiles without any issues.

**You can:**
- Keep some structs in old syntax (`{}` with `prop`)
- Convert only the structs you want to inference syntax
- Mix both syntaxes in the same file

**Example: Mixed syntax in one file:**
```htvm
; Old style (formatted) — perfectly fine to leave as-is
struct Audio {
    prop volume: int := 80
    prop pitch: float := 1.0
}

; New style (inference) — you converted this one
struct Player
    health: 100
    mana: 50
subout

; Another old style — no need to convert
struct Settings {
    prop theme: str := "dark"
}
```

Both syntaxes compile identically. Convert only when you want to, not because you have to.

**If you want to selectively convert a struct back to new syntax:**

1. Remove the opening `{` and closing `}`
2. Add `subout` at the bottom
3. *Optional:* Remove `prop` keywords and explicit types (or keep them — both work)

Example of converting back:
```htvm
; Before (formatted style)
struct Player {
    prop health: int := 100
    prop mana: int := 50
}

; After (new inference style, prop removed)
struct Player
    health: 100
    mana: 50
subout
```

Or keep `prop` if you prefer (both are valid):

```htvm
; New style with prop kept
struct Player
    prop health: int := 100
    prop mana: int := 50
subout
```

**Bottom line:** Don't feel obligated to rewrite all your structs. The formatter output works fine as-is.

---

## Complete Examples

### Example 1: Simple Character System

```htvm
struct Character
    name: "Adventurer"
    level: 1
    experience: 0.0
    prop isAlive: bool
subout

main
    instance Character as hero
    instance Character as enemy
    
    hero.level := 10
    hero.experience := 5000.5
    enemy.level := 5
    
    print("Hero: " . hero.name . " (Level " . STR(hero.level) . ")")
    print("Enemy: " . enemy.name . " (Level " . STR(enemy.level) . ")")
    print("Experience: " . STR(hero.experience))
```

### Example 2: Inventory System

```htvm
struct Item
    name: "Sword"
    value: 50
subout

struct Player
    name: "Warrior"
    gold: 1000
    prop inventory: arr str
subout

main
    instance Player as adventurer
    
    adventurer.inventory.add("Iron Sword")
    adventurer.inventory.add("Shield")
    adventurer.inventory.add("Health Potion")
    
    print("Inventory:")
    Loop, % adventurer.inventory.size() {
        print("  - " . adventurer.inventory[A_Index])
    }
```

### Example 3: Multiple Standalone Structs

```htvm
struct Weapon
    name: "Sword"
    damage: 25
    durability: 100
subout

struct Character
    health: 100
    mana: 50
    strength: 15
subout

main
    instance Character as player
    instance Weapon as sword
    
    player.health := 75
    sword.damage := 30
    
    print("Player Health: " . STR(player.health))
    print("Weapon Damage: " . STR(sword.damage))
```

### Example 4: Arrays with Multiple Properties

```htvm
struct GameState
    currentLevel: 1
    prop achievements: arr str
    prop scores: arr int
    prop playerNames: arr str
subout

main
    instance GameState as game
    
    game.achievements.add("First Kill")
    game.achievements.add("Level 10")
    game.achievements.add("Boss Defeated")
    
    game.scores.add(1000)
    game.scores.add(2500)
    game.scores.add(5000)
    
    game.playerNames.add("Hero")
    game.playerNames.add("Villain")
    game.playerNames.add("NPC")
    
    print("=== Achievements ===")
    Loop, % game.achievements.size() {
        print(game.achievements[A_Index])
    }
    
    print("=== Scores ===")
    Loop, % game.scores.size() {
        print("Score: " . STR(game.scores[A_Index]))
    }
```

---

## Common Patterns

### Pattern 1: Default Values with Instances

```htvm
struct Player
    health: 100
    mana: 50
subout

main
    instance Player as hero
    instance Player as goblin
    ; Both start with default values
    print("Hero: " . STR(hero.health))  ; 100
    print("Goblin: " . STR(goblin.health)) ; 100
    ; Then customize independently
    hero.health := 150
    goblin.health := 50
```

### Pattern 2: Mixed Property Types

```htvm
struct Settings
    volume: 75               ; int
    theme: "dark"            ; str
    brightness: 0.85         ; float
    prop soundEnabled: bool  ; bool
    prop languages: arr str  ; array
subout
```

### Pattern 3: Array Properties with Multiple Instances

```htvm
struct Player
    name: "Hero"
    prop inventory: arr str
    prop stats: arr int
subout

main
    instance Player as hero
    instance Player as companion
    
    hero.inventory.add("Sword")
    hero.inventory.add("Shield")
    
    companion.inventory.add("Dagger")
    companion.stats.add(100)
    companion.stats.add(50)
```

### Pattern 4: Multiple Instances of the Same Struct

```htvm
struct Enemy
    health: 50
    damage: 10
subout

main
    instance Enemy as goblin1
    instance Enemy as goblin2
    instance Enemy as goblin3
    
    goblin1.health := 40
    goblin2.health := 55
    goblin3.health := 50
    
    print("Goblin 1 Health: " . STR(goblin1.health))
    print("Goblin 2 Health: " . STR(goblin2.health))
    print("Goblin 3 Health: " . STR(goblin3.health))
```

---

### Instance Independence

Each instance is a **completely independent copy** of the struct. Modifying one instance does NOT affect others.

```htvm
struct Item
    name: "Sword"
    quantity: 1
subout

main
    instance Item as item1
    instance Item as item2
    
    item1.quantity := 5
    print(item2.quantity)  ; Still 1, not affected
```

### No Constructor Arguments

You cannot pass initial values when creating an instance. All instances start with the struct's default values, which you can then modify.

```htvm
; This does NOT work:
; instance Player as hero with health = 200

; Instead, do this:
instance Player as hero
hero.health := 200
```

### Type Inference Limitations

Remember: **Only `int`, `str`, and `float` are inferred.** Everything else requires `prop`.

```htvm
struct Example
    count: 42               ; OK — inferred as int
    text: "hello"           ; OK — inferred as str
    ratio: 3.14             ; OK — inferred as float
    prop flag: bool         ; Required — bool is not inferred
    prop list: arr str      ; Required — arrays are not inferred
subout
```

---

## Summary

### The Golden Rule

**If you use `instance`, you CANNOT use `crew` or `alliance` anywhere in your project. Choose one approach.**

### Basic Rules

- **Structs** define data templates
- **Instances** create independent copies of standalone structs only
- **Type inference** keeps code clean (int, str, float only)
- **`prop`** keyword required for booleans, arrays, and explicit typing
- **`crew`/`alliance`** organize structs hierarchically (never with instances)
- **Formatter** is optional and just beautifies code
- **Scope** Only the global scope. If you define a struct inside a function or in main, it will not work and will cause issues.
- **Instances are completely independent**

### Critical Syntax Rules

1. **Curly braces are NOT allowed** when using new inference syntax with `subout`
2. **Never mix crew/alliance with instances** — pick one approach for your entire project
3. **Type inference** only works for `int`, `str`, `float` — everything else needs `prop`

### Quick Decision Guide

**Use instances if:**
- You need multiple independent copies of data
- You only use standalone structs
- You have NO crews/alliances in your project

**Use crews/alliances if:**
- You need to organize structs hierarchically
- You don't need multiple independent copies
- You'll never use the `instance` keyword

That's OSP! Simple, powerful, and ready for production.
============&&&13&&&============
============***14***============
# OSP (Ordinal Struct Programming)

[Go back](#htvm-documentation)

OSP is HTVM's built-in system for organizing data using **structs** and **instances**. It provides a clean, developer-friendly way to define data structures and create multiple independent copies of them with minimal syntax.

---

## Table of Contents

1. [Structs: The Basics](#structs-the-basics)
2. [Type Inference](#type-inference)
3. [Instances: Creating Data](#instances-creating-data)
4. [Arrays in Structs](#arrays-in-structs)
5. [Organization with `crew` and `alliance`](#organization-with-crew-and-alliance)
6. [Syntax Styles: New vs. Old](#syntax-styles-new-vs-old)
7. [The Formatter (Optional Tool)](#the-formatter-optional-tool)
8. [Complete Examples](#complete-examples)
9. [Common Patterns](#common-patterns)

---

## Structs: The Basics

A `struct` is a container for related data. You define it once, then create multiple independent **instances** of it.

**Basic struct definition:**

```htvm
struct Player
    health: 100
    mana: 50
subout
```

This defines a struct named `Player` with two properties: `health` and `mana`, both initialized to their respective values.

**Key rule:** Always close a struct with `subout` (the end kryword is `NOT` allowed for the new syntax with `subout`).

---

## Type Inference

When you use the new syntax (colon-style with `subout`), HTVM automatically infers types from the initial values:

- **`int`** ← inferred from numeric values (e.g., `100`, `50`)
- **`str`** ← inferred from string values (e.g., `"hello"`)
- **`float`** ← inferred from floating-point values (e.g., `3.14`, `2.5`)

**Examples of inference:**

```htvm
struct Character
    name: "Warrior"           ; Inferred as str
    level: 5                  ; Inferred as int
    experience: 1250.75       ; Inferred as float
subout
```

### What About Booleans and Arrays?

**Booleans and arrays are NOT inferred.** You must use the `prop` keyword explicitly for these types:

```htvm
struct Player
    health: 100              ; Inferred as int
    prop bool isAlive        ; Must use prop for bool
    prop arr str inventory   ; Must use prop for arrays
subout
```

---

## Instances: Creating Data

⚠️ **CRITICAL BEFORE YOU START:** If you plan to use `instance` anywhere in your code, **NEVER use `crew` or `alliance` in that project.** Mixing them causes bugs. You must choose one approach: either instances with standalone structs, OR crews/alliances for organization (no instances at all).

An **instance** is an independent copy of a struct with its own data. You create instances using the `instance` keyword:

**Basic instance creation:**

```htvm
struct Player
    health: 100
    mana: 50
subout

main
    instance Player as hero
    instance Player as goblin
    hero.health := 200
    goblin.health := 30
    print("Hero health: " . STR(hero.health))
    print("Goblin health: " . STR(goblin.health))
```

**How it works:**

- `instance Player as hero` creates a new variable `hero` with all of `Player`'s properties
- Each instance is **completely independent** — modifying `hero.health` does NOT affect `goblin.health`
- All instances are **globally accessible** by their name (below the point of creation)
- Instance names become global variables that hold the struct's data

---

## Arrays in Structs

Arrays must be declared using the `prop` keyword. You cannot use type inference for arrays.

**Declaring array properties:**

```htvm
struct Inventory
    prop arr str items
    prop arr int quantities
subout

main
    instance Inventory as backpack
    backpack.items.add("sword")
    backpack.items.add("shield")
    backpack.quantities.add(1)
    backpack.quantities.add(1)
```

**Array methods:**

- **`.add(value)`** or **`.push(value)`** — Add an item to the array (both work the same)
- **`.size()`** — Get the array length
- **`[index]`** — Access element by index (zero-based)

**Complete array example:**

```htvm
struct Player
    health: 100
    prop arr str spells
subout

main
    instance Player as wizard
    wizard.spells.add("Fireball")
    wizard.spells.add("Ice Storm")
    wizard.spells.add("Lightning")
    
    Loop, % wizard.spells.size()
        print(wizard.spells[A_Index])
    end
```

---

## Organization with `crew` and `alliance`

For larger projects, you can organize structs using `crew` and `alliance` containers:

- **`alliance`** — Top-level organizational container
- **`crew`** — Sub-container within an alliance (or standalone)

**Purpose:** Group related structs logically and avoid naming conflicts.

**Important:** Crew and alliance use end keyword syntax, not `subout`.

**Using `crew`:**

```htvm
crew Audio
    struct Settings
        volume: 80
        pitch: 1.0
    subout
end

main
    ; Access the struct's default properties directly
    Audio.Settings.volume := 100
    print("Audio volume: " . STR(Audio.Settings.volume))
```

**Using `alliance`:**

```htvm
alliance Game
    crew Entities
        struct Player
            health: 100
            mana: 50
        subout
    end
    
    crew UI
        struct Button
            x: 0
            y: 0
            label: "Click me"
        subout
    end
end

main
    ; Access struct properties using their full path
    Game.Entities.Player.health := 200
    Game.UI.Button.label := "Start Game"
    print("Player health: " . STR(Game.Entities.Player.health))
```

### ⚠️ CRITICAL: Never Mix Crew/Alliance with Instances

**If you use `instance` in your code, you CANNOT use `crew` or `alliance` anywhere in that same project.** This applies even to standalone structs. Mixing them causes bugs.

You must choose ONE approach:
- **Option A:** Use standalone structs + instances (NO crews/alliances anywhere)
- **Option B:** Use crews/alliances for organization (NO instances anywhere)

**This causes bugs:**
```htvm
crew Audio
    struct Settings
        volume: 80
    subout
end

struct Player
    health: 100
subout

main
    ; DON'T mix them like this
    instance Player as hero  ; This will cause bugs if you have crew/alliance
    Audio.Settings.volume := 100
```

**Option A (instances only):**
```htvm
struct Player
    health: 100
subout

struct Settings
    volume: 80
subout

main
    instance Player as hero
    instance Settings as config
```

**Option B (crew/alliance only):**
```htvm
crew Audio
    struct Settings
        volume: 80
    subout
end

crew Game
    struct Player
        health: 100
    subout
end

main
    ; Access properties directly, no instances
    Game.Player.health := 200
    Audio.Settings.volume := 100
```

---

## Syntax Styles: New vs. Old

HTVM supports two syntax styles. You can use them separately or mix them in the same struct.

### New Style (Inference with `subout`):

```htvm
struct Player
    health: 100
    mana: 50
    name: "Hero"
subout
```

Clean, minimal, types inferred automatically.

### Old Style (Explicit with `prop` and `end`):

```htvm
struct Player
    prop int health := 100
    prop int mana := 50
    prop str name := "Hero"
subout
```

Verbose, but explicit types.

### Mixed Style:

```htvm
struct Player
    health: 100
    name: "Hero"
    prop bool isAlive
    prop arr str inventory
subout
```

Use inference for simple types, `prop` for complex ones.

---

## The Formatter (Optional Tool)

The formatter is a **code beautification tool**. It is **completely optional** and does NOT affect compilation.

**What the formatter does:**

- Converts new syntax (`health: 100` with `subout`) to old syntax (`prop int health := 100` with `end`)
- Adds explicit types to all properties
- Removes indentation from `main` blocks (standard formatting)
- Keeps instance declarations clean and unchanged

**Using the formatter:**

In HT-IDE, press `Ctrl+Shift+F` to format your code.

**Important:** You do NOT need to use the formatter. Your code compiles the same way with or without formatting.

### ⚠️ Important: You Don't Have to Convert Everything

After formatting, **you do NOT have to convert every struct back to inference syntax.** The old syntax with end keyword and `prop` keywords works fine and compiles without any issues.

**You can:**
- Keep some structs in old syntax (end keyword with `prop`)
- Convert only the structs you want to inference syntax
- Mix both syntaxes in the same file

**Example: Mixed syntax in one file:**
```htvm
; Old style (formatted) — perfectly fine to leave as-is
struct Audio
    prop int volume := 80
    prop float pitch := 1.0
end

; New style (inference) — you converted this one
struct Player
    health: 100
    mana: 50
subout

; Another old style — no need to convert
struct Settings
    prop str theme := "dark"
end
```

Both syntaxes compile identically. Convert only when you want to, not because you have to.

**If you want to selectively convert a struct back to new syntax:**

1. Replace the end keyword whit `subout`
2. *Optional:* Remove `prop` keywords and explicit types (or keep them — both work)

Example of converting back:
```htvm
; Before (formatted style)
struct Player
    prop int health := 100
    prop int mana := 50
end

; After (new inference style, prop removed)
struct Player
    health: 100
    mana: 50
subout
```

Or keep `prop` if you prefer (both are valid):

```htvm
; New style with prop kept
struct Player
    prop int health := 100
    prop int mana := 50
subout
```

**Bottom line:** Don't feel obligated to rewrite all your structs. The formatter output works fine as-is.

---

## Complete Examples

### Example 1: Simple Character System

```htvm
struct Character
    name: "Adventurer"
    level: 1
    experience: 0.0
    prop bool isAlive
subout

main
    instance Character as hero
    instance Character as enemy
    
    hero.level := 10
    hero.experience := 5000.5
    enemy.level := 5
    
    print("Hero: " . hero.name . " (Level " . STR(hero.level) . ")")
    print("Enemy: " . enemy.name . " (Level " . STR(enemy.level) . ")")
    print("Experience: " . STR(hero.experience))
```

### Example 2: Inventory System

```htvm
struct Item
    name: "Sword"
    value: 50
subout

struct Player
    name: "Warrior"
    gold: 1000
    prop arr str inventory
subout

main
    instance Player as adventurer
    
    adventurer.inventory.add("Iron Sword")
    adventurer.inventory.add("Shield")
    adventurer.inventory.add("Health Potion")
    
    print("Inventory:")
    Loop, % adventurer.inventory.size()
        print("  - " . adventurer.inventory[A_Index])
    end
```

### Example 3: Multiple Standalone Structs

```htvm
struct Weapon
    name: "Sword"
    damage: 25
    durability: 100
subout

struct Character
    health: 100
    mana: 50
    strength: 15
subout

main
    instance Character as player
    instance Weapon as sword
    
    player.health := 75
    sword.damage := 30
    
    print("Player Health: " . STR(player.health))
    print("Weapon Damage: " . STR(sword.damage))
```

### Example 4: Arrays with Multiple Properties

```htvm
struct GameState
    currentLevel: 1
    prop arr str achievements
    prop arr int scores
    prop arr str playerNames
subout

main
    instance GameState as game
    
    game.achievements.add("First Kill")
    game.achievements.add("Level 10")
    game.achievements.add("Boss Defeated")
    
    game.scores.add(1000)
    game.scores.add(2500)
    game.scores.add(5000)
    
    game.playerNames.add("Hero")
    game.playerNames.add("Villain")
    game.playerNames.add("NPC")
    
    print("=== Achievements ===")
    Loop, % game.achievements.size()
        print(game.achievements[A_Index])
    end
    
    print("=== Scores ===")
    Loop, % game.scores.size()
        print("Score: " . STR(game.scores[A_Index]))
    end
```

---

## Common Patterns

### Pattern 1: Default Values with Instances

```htvm
struct Player
    health: 100
    mana: 50
subout

main
    instance Player as hero
    instance Player as goblin
    ; Both start with default values
    print("Hero: " . STR(hero.health))  ; 100
    print("Goblin: " . STR(goblin.health)) ; 100
    ; Then customize independently
    hero.health := 150
    goblin.health := 50
```

### Pattern 2: Mixed Property Types

```htvm
struct Settings
    volume: 75              ; int
    theme: "dark"           ; str
    brightness: 0.85        ; float
    prop bool soundEnabled  ; bool
    prop arr str languages  ; array
subout
```

### Pattern 3: Array Properties with Multiple Instances

```htvm
struct Player
    name: "Hero"
    prop arr str inventory
    prop arr int stats
subout

main
    instance Player as hero
    instance Player as companion
    
    hero.inventory.add("Sword")
    hero.inventory.add("Shield")
    
    companion.inventory.add("Dagger")
    companion.stats.add(100)
    companion.stats.add(50)
```

### Pattern 4: Multiple Instances of the Same Struct

```htvm
struct Enemy
    health: 50
    damage: 10
subout

main
    instance Enemy as goblin1
    instance Enemy as goblin2
    instance Enemy as goblin3
    
    goblin1.health := 40
    goblin2.health := 55
    goblin3.health := 50
    
    print("Goblin 1 Health: " . STR(goblin1.health))
    print("Goblin 2 Health: " . STR(goblin2.health))
    print("Goblin 3 Health: " . STR(goblin3.health))
```

---

### Instance Independence

Each instance is a **completely independent copy** of the struct. Modifying one instance does NOT affect others.

```htvm
struct Item
    name: "Sword"
    quantity: 1
subout

main
    instance Item as item1
    instance Item as item2
    
    item1.quantity := 5
    print(item2.quantity)  ; Still 1, not affected
```

### No Constructor Arguments

You cannot pass initial values when creating an instance. All instances start with the struct's default values, which you can then modify.

```htvm
; This does NOT work:
; instance Player as hero with health = 200

; Instead, do this:
instance Player as hero
hero.health := 200
```

### Type Inference Limitations

Remember: **Only `int`, `str`, and `float` are inferred.** Everything else requires `prop`.

```htvm
struct Example
    count: 42              ; OK — inferred as int
    text: "hello"          ; OK — inferred as str
    ratio: 3.14            ; OK — inferred as float
    prop bool flag         ; Required — bool is not inferred
    prop arr str list      ; Required — arrays are not inferred
subout
```

---

## Summary

### The Golden Rule

**If you use `instance`, you CANNOT use `crew` or `alliance` anywhere in your project. Choose one approach.**

### Basic Rules

- **Structs** define data templates
- **Instances** create independent copies of standalone structs only
- **Type inference** keeps code clean (int, str, float only)
- **`prop`** keyword required for booleans, arrays, and explicit typing
- **`crew`/`alliance`** organize structs hierarchically (never with instances)
- **Formatter** is optional and just beautifies code
- **Scope** Only the global scope. If you define a struct inside a function or in main, it will not work and will cause issues.
- **Instances are completely independent**

### Critical Syntax Rules

1. **End keyword is NOT allowed** when using new inference syntax with `subout`
2. **Never mix crew/alliance with instances** — pick one approach for your entire project
3. **Type inference** only works for `int`, `str`, `float` — everything else needs `prop`

### Quick Decision Guide

**Use instances if:**
- You need multiple independent copies of data
- You only use standalone structs
- You have NO crews/alliances in your project

**Use crews/alliances if:**
- You need to organize structs hierarchically
- You don't need multiple independent copies
- You'll never use the `instance` keyword

That's OSP! Simple, powerful, and ready for production.
============&&&14&&&============
============***15***============
# OSP (Ordinal Struct Programming)

[Go back](#htvm-documentation)

OSP is HTVM's built-in system for organizing data using **structs** and **instances**. It provides a clean, developer-friendly way to define data structures and create multiple independent copies of them with minimal syntax.

---

## Table of Contents

1. [Structs: The Basics](#structs-the-basics)
2. [Type Inference](#type-inference)
3. [Instances: Creating Data](#instances-creating-data)
4. [Arrays in Structs](#arrays-in-structs)
5. [Organization with `crew` and `alliance`](#organization-with-crew-and-alliance)
6. [Syntax Styles: New vs. Old](#syntax-styles-new-vs-old)
7. [The Formatter (Optional Tool)](#the-formatter-optional-tool)
8. [Complete Examples](#complete-examples)
9. [Common Patterns](#common-patterns)

---

## Structs: The Basics

A `struct` is a container for related data. You define it once, then create multiple independent **instances** of it.

**Basic struct definition:**

```htvm
struct Player
    health: 100
    mana: 50
subout
```

This defines a struct named `Player` with two properties: `health` and `mana`, both initialized to their respective values.

**Key rule:** Always close a struct with `subout` (the end kryword is `NOT` allowed for the new syntax with `subout`).

---

## Type Inference

When you use the new syntax (colon-style with `subout`), HTVM automatically infers types from the initial values:

- **`int`** ← inferred from numeric values (e.g., `100`, `50`)
- **`str`** ← inferred from string values (e.g., `"hello"`)
- **`float`** ← inferred from floating-point values (e.g., `3.14`, `2.5`)

**Examples of inference:**

```htvm
struct Character
    name: "Warrior"           ; Inferred as str
    level: 5                  ; Inferred as int
    experience: 1250.75       ; Inferred as float
subout
```

### What About Booleans and Arrays?

**Booleans and arrays are NOT inferred.** You must use the `prop` keyword explicitly for these types:

```htvm
struct Player
    health: 100               ; Inferred as int
    prop isAlive: bool        ; Must use prop for bool
    prop inventory: arr str   ; Must use prop for arrays
subout
```

---

## Instances: Creating Data

⚠️ **CRITICAL BEFORE YOU START:** If you plan to use `instance` anywhere in your code, **NEVER use `crew` or `alliance` in that project.** Mixing them causes bugs. You must choose one approach: either instances with standalone structs, OR crews/alliances for organization (no instances at all).

An **instance** is an independent copy of a struct with its own data. You create instances using the `instance` keyword:

**Basic instance creation:**

```htvm
struct Player
    health: 100
    mana: 50
subout

main
    instance Player as hero
    instance Player as goblin
    hero.health := 200
    goblin.health := 30
    print("Hero health: " . STR(hero.health))
    print("Goblin health: " . STR(goblin.health))
```

**How it works:**

- `instance Player as hero` creates a new variable `hero` with all of `Player`'s properties
- Each instance is **completely independent** — modifying `hero.health` does NOT affect `goblin.health`
- All instances are **globally accessible** by their name (below the point of creation)
- Instance names become global variables that hold the struct's data

---

## Arrays in Structs

Arrays must be declared using the `prop` keyword. You cannot use type inference for arrays.

**Declaring array properties:**

```htvm
struct Inventory
    prop items: arr str
    prop quantities: arr int
subout

main
    instance Inventory as backpack
    backpack.items.add("sword")
    backpack.items.add("shield")
    backpack.quantities.add(1)
    backpack.quantities.add(1)
```

**Array methods:**

- **`.add(value)`** or **`.push(value)`** — Add an item to the array (both work the same)
- **`.size()`** — Get the array length
- **`[index]`** — Access element by index (zero-based)

**Complete array example:**

```htvm
struct Player
    health: 100
    prop spells: arr str
subout

main
    instance Player as wizard
    wizard.spells.add("Fireball")
    wizard.spells.add("Ice Storm")
    wizard.spells.add("Lightning")
    
    Loop, % wizard.spells.size()
        print(wizard.spells[A_Index])
    end
```

---

## Organization with `crew` and `alliance`

For larger projects, you can organize structs using `crew` and `alliance` containers:

- **`alliance`** — Top-level organizational container
- **`crew`** — Sub-container within an alliance (or standalone)

**Purpose:** Group related structs logically and avoid naming conflicts.

**Important:** Crew and alliance use end keyword syntax, not `subout`.

**Using `crew`:**

```htvm
crew Audio
    struct Settings
        volume: 80
        pitch: 1.0
    subout
end

main
    ; Access the struct's default properties directly
    Audio.Settings.volume := 100
    print("Audio volume: " . STR(Audio.Settings.volume))
```

**Using `alliance`:**

```htvm
alliance Game
    crew Entities
        struct Player
            health: 100
            mana: 50
        subout
    end
    
    crew UI
        struct Button
            x: 0
            y: 0
            label: "Click me"
        subout
    end
end

main
    ; Access struct properties using their full path
    Game.Entities.Player.health := 200
    Game.UI.Button.label := "Start Game"
    print("Player health: " . STR(Game.Entities.Player.health))
```

### ⚠️ CRITICAL: Never Mix Crew/Alliance with Instances

**If you use `instance` in your code, you CANNOT use `crew` or `alliance` anywhere in that same project.** This applies even to standalone structs. Mixing them causes bugs.

You must choose ONE approach:
- **Option A:** Use standalone structs + instances (NO crews/alliances anywhere)
- **Option B:** Use crews/alliances for organization (NO instances anywhere)

**This causes bugs:**
```htvm
crew Audio
    struct Settings
        volume: 80
    subout
end

struct Player
    health: 100
subout

main
    ; DON'T mix them like this
    instance Player as hero  ; This will cause bugs if you have crew/alliance
    Audio.Settings.volume := 100
```

**Option A (instances only):**
```htvm
struct Player
    health: 100
subout

struct Settings
    volume: 80
subout

main
    instance Player as hero
    instance Settings as config
```

**Option B (crew/alliance only):**
```htvm
crew Audio
    struct Settings
        volume: 80
    subout
end

crew Game
    struct Player
        health: 100
    subout
end

main
    ; Access properties directly, no instances
    Game.Player.health := 200
    Audio.Settings.volume := 100
```

---

## Syntax Styles: New vs. Old

HTVM supports two syntax styles. You can use them separately or mix them in the same struct.

### New Style (Inference with `subout`):

```htvm
struct Player
    health: 100
    mana: 50
    name: "Hero"
subout
```

Clean, minimal, types inferred automatically.

### Old Style (Explicit with `prop` and `end`):

```htvm
struct Player
    prop health: int := 100
    prop mana: int := 50
    prop name: str := "Hero"
subout
```

Verbose, but explicit types.

### Mixed Style:

```htvm
struct Player
    health: 100
    name: "Hero"
    prop isAlive: bool
    prop inventory: arr str
subout
```

Use inference for simple types, `prop` for complex ones.

---

## The Formatter (Optional Tool)

The formatter is a **code beautification tool**. It is **completely optional** and does NOT affect compilation.

**What the formatter does:**

- Converts new syntax (`health: 100` with `subout`) to old syntax (`prop health: int := 100` with `end`)
- Adds explicit types to all properties
- Removes indentation from `main` blocks (standard formatting)
- Keeps instance declarations clean and unchanged

**Using the formatter:**

In HT-IDE, press `Ctrl+Shift+F` to format your code.

**Important:** You do NOT need to use the formatter. Your code compiles the same way with or without formatting.

### ⚠️ Important: You Don't Have to Convert Everything

After formatting, **you do NOT have to convert every struct back to inference syntax.** The old syntax with end keyword and `prop` keywords works fine and compiles without any issues.

**You can:**
- Keep some structs in old syntax (end keyword with `prop`)
- Convert only the structs you want to inference syntax
- Mix both syntaxes in the same file

**Example: Mixed syntax in one file:**
```htvm
; Old style (formatted) — perfectly fine to leave as-is
struct Audio
    prop volume: int := 80
    prop pitch: float := 1.0
end

; New style (inference) — you converted this one
struct Player
    health: 100
    mana: 50
subout

; Another old style — no need to convert
struct Settings
    prop theme: str := "dark"
end
```

Both syntaxes compile identically. Convert only when you want to, not because you have to.

**If you want to selectively convert a struct back to new syntax:**

1. Replace the end keyword whit `subout`
2. *Optional:* Remove `prop` keywords and explicit types (or keep them — both work)

Example of converting back:
```htvm
; Before (formatted style)
struct Player
    prop health: int := 100
    prop mana: int := 50
end

; After (new inference style, prop removed)
struct Player
    health: 100
    mana: 50
subout
```

Or keep `prop` if you prefer (both are valid):

```htvm
; New style with prop kept
struct Player
    prop health: int := 100
    prop mana: int := 50
subout
```

**Bottom line:** Don't feel obligated to rewrite all your structs. The formatter output works fine as-is.

---

## Complete Examples

### Example 1: Simple Character System

```htvm
struct Character
    name: "Adventurer"
    level: 1
    experience: 0.0
    prop isAlive: bool
subout

main
    instance Character as hero
    instance Character as enemy
    
    hero.level := 10
    hero.experience := 5000.5
    enemy.level := 5
    
    print("Hero: " . hero.name . " (Level " . STR(hero.level) . ")")
    print("Enemy: " . enemy.name . " (Level " . STR(enemy.level) . ")")
    print("Experience: " . STR(hero.experience))
```

### Example 2: Inventory System

```htvm
struct Item
    name: "Sword"
    value: 50
subout

struct Player
    name: "Warrior"
    gold: 1000
    prop inventory: arr str
subout

main
    instance Player as adventurer
    
    adventurer.inventory.add("Iron Sword")
    adventurer.inventory.add("Shield")
    adventurer.inventory.add("Health Potion")
    
    print("Inventory:")
    Loop, % adventurer.inventory.size()
        print("  - " . adventurer.inventory[A_Index])
    end
```

### Example 3: Multiple Standalone Structs

```htvm
struct Weapon
    name: "Sword"
    damage: 25
    durability: 100
subout

struct Character
    health: 100
    mana: 50
    strength: 15
subout

main
    instance Character as player
    instance Weapon as sword
    
    player.health := 75
    sword.damage := 30
    
    print("Player Health: " . STR(player.health))
    print("Weapon Damage: " . STR(sword.damage))
```

### Example 4: Arrays with Multiple Properties

```htvm
struct GameState
    currentLevel: 1
    prop achievements: arr str
    prop scores: arr int
    prop playerNames: arr str
subout

main
    instance GameState as game
    
    game.achievements.add("First Kill")
    game.achievements.add("Level 10")
    game.achievements.add("Boss Defeated")
    
    game.scores.add(1000)
    game.scores.add(2500)
    game.scores.add(5000)
    
    game.playerNames.add("Hero")
    game.playerNames.add("Villain")
    game.playerNames.add("NPC")
    
    print("=== Achievements ===")
    Loop, % game.achievements.size()
        print(game.achievements[A_Index])
    end
    
    print("=== Scores ===")
    Loop, % game.scores.size()
        print("Score: " . STR(game.scores[A_Index]))
    end
```

---

## Common Patterns

### Pattern 1: Default Values with Instances

```htvm
struct Player
    health: 100
    mana: 50
subout

main
    instance Player as hero
    instance Player as goblin
    ; Both start with default values
    print("Hero: " . STR(hero.health))  ; 100
    print("Goblin: " . STR(goblin.health)) ; 100
    ; Then customize independently
    hero.health := 150
    goblin.health := 50
```

### Pattern 2: Mixed Property Types

```htvm
struct Settings
    volume: 75               ; int
    theme: "dark"            ; str
    brightness: 0.85         ; float
    prop soundEnabled: bool  ; bool
    prop languages: arr str  ; array
subout
```

### Pattern 3: Array Properties with Multiple Instances

```htvm
struct Player
    name: "Hero"
    prop inventory: arr str
    prop stats: arr int 
subout

main
    instance Player as hero
    instance Player as companion
    
    hero.inventory.add("Sword")
    hero.inventory.add("Shield")
    
    companion.inventory.add("Dagger")
    companion.stats.add(100)
    companion.stats.add(50)
```

### Pattern 4: Multiple Instances of the Same Struct

```htvm
struct Enemy
    health: 50
    damage: 10
subout

main
    instance Enemy as goblin1
    instance Enemy as goblin2
    instance Enemy as goblin3
    
    goblin1.health := 40
    goblin2.health := 55
    goblin3.health := 50
    
    print("Goblin 1 Health: " . STR(goblin1.health))
    print("Goblin 2 Health: " . STR(goblin2.health))
    print("Goblin 3 Health: " . STR(goblin3.health))
```

---

### Instance Independence

Each instance is a **completely independent copy** of the struct. Modifying one instance does NOT affect others.

```htvm
struct Item
    name: "Sword"
    quantity: 1
subout

main
    instance Item as item1
    instance Item as item2
    
    item1.quantity := 5
    print(item2.quantity)  ; Still 1, not affected
```

### No Constructor Arguments

You cannot pass initial values when creating an instance. All instances start with the struct's default values, which you can then modify.

```htvm
; This does NOT work:
; instance Player as hero with health = 200

; Instead, do this:
instance Player as hero
hero.health := 200
```

### Type Inference Limitations

Remember: **Only `int`, `str`, and `float` are inferred.** Everything else requires `prop`.

```htvm
struct Example
    count: 42               ; OK — inferred as int
    text: "hello"           ; OK — inferred as str
    ratio: 3.14             ; OK — inferred as float
    prop flag: bool         ; Required — bool is not inferred
    prop list: arr str      ; Required — arrays are not inferred
subout
```

---

## Summary

### The Golden Rule

**If you use `instance`, you CANNOT use `crew` or `alliance` anywhere in your project. Choose one approach.**

### Basic Rules

- **Structs** define data templates
- **Instances** create independent copies of standalone structs only
- **Type inference** keeps code clean (int, str, float only)
- **`prop`** keyword required for booleans, arrays, and explicit typing
- **`crew`/`alliance`** organize structs hierarchically (never with instances)
- **Formatter** is optional and just beautifies code
- **Scope** Only the global scope. If you define a struct inside a function or in main, it will not work and will cause issues.
- **Instances are completely independent**

### Critical Syntax Rules

1. **End keyword is NOT allowed** when using new inference syntax with `subout`
2. **Never mix crew/alliance with instances** — pick one approach for your entire project
3. **Type inference** only works for `int`, `str`, `float` — everything else needs `prop`

### Quick Decision Guide

**Use instances if:**
- You need multiple independent copies of data
- You only use standalone structs
- You have NO crews/alliances in your project

**Use crews/alliances if:**
- You need to organize structs hierarchically
- You don't need multiple independent copies
- You'll never use the `instance` keyword

That's OSP! Simple, powerful, and ready for production.
============&&&15&&&============
============***16***============

============&&&16&&&============