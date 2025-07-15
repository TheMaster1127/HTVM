# HTVM Documentation


1. [Introduction](#introduction-to-htvm)  
Understand why HTVM is the future of programming.

2. [OSP (Ordinal Struct Programming)](#osp-ordinal-struct-programming)  
Learn about OSP (Ordinal Struct Programming) a new way to use Structs.

3. [How Your Language Looks Like](#how-your-language-looks-like)  
Get to know how HTVM code is structured and its syntax style.

4. [Programming Blocks](#programming-blocks)  
HTVM introduces **programming blocks** that allow you to code in the target language seamlessly in your code. This feature is designed to handle cases where HTVM itself can't achieve something directly or when you'd prefer to rely on another language for specific tasks.

5. [Variables](#variables)  
Learn how to declare and use variables in HTVM for storing and manipulating data.

6. [Functions](#functions)  
Explore how to define and use functions for modular and reusable code.

7. [Arrays](#arrays)  
Dive into working with arrays, one of the most essential data structures in HTVM.

8. [Loops](#loops)  
Master the looping structures available in HTVM, such as the standard loop and infinite loops.

9. [Comments](#comments)  
Add clarity to your code by using comments to document and explain your code.

10. [GUI (Graphical User Interface with HTVM)](#gui-graphical-user-interface-with-htvm)  
Learn how to the GUI feature in HTVM that allows for the creation of graphical user interfaces specifically for **web browsers (JavaScript)**.

11. [Backend in HTVM](#backend-in-htvm)  
Learn how to use HTVM's Backend functionality that generates **Python** code using **Flask**.

12. [Error Handling](#error-handling)  
Understand how to manage errors and handle exceptions in HTVM to make your programs more robust.

13. [Include](#include)  
Discover how to include external files and resources in your HTVM project for enhanced functionality.

14. [Commands](#commands)  
Commands in HTVM are a simplified way to perform actions, similar to functions, but with a more compact, direct, and concise syntax for better efficiency.

15. [All Syntax](#all-syntax)  
This is all of your syntax.

16. [Built-in Functions](#built-in-functions)  
Explore the wide range of built-in functions categorized for ease of use.

---

## Introduction to HTVM

[Go back](#htvm-documentation) 

HTVM is a revolutionary tool designed to replace traditional programming. With HTVM, you can create your own programming language directly [here](https://themaster1127.github.io/HTVM/).


HTVM offers **extensive syntax customization**, giving you the freedom to tailor the language structure to your own preferences. Almost all of these customizations can be converted into 15 languages, providing flexibility while keeping things simple.

## Customization Features

### Code Block Delimiters

You can **customize the block delimiters**, which define the start and end of code blocks. You can use:

- Curly braces `{}` (default).
- **Other characters**, words, or even single letters, as long as the opening and closing delimiters are different from each other.

### Indentation Styles

You have the ability to choose between multiple **indentation styles**:

- **Pythonic indentation style**: This removes the need for block delimiters like curly braces, relying on indentation to define code blocks.
- **Lua indentation style**: Uses the customizable `end` keyword to close code blocks.

Both styles are fully customizable, and you can define your own keyword for closing blocks (such as `end`, or any other word).

### Toggleable Semicolons

Semicolons are **toggleable** in HTVM. By default, semicolons are not required to terminate statements, but you can enable the use of semicolons if you prefer them in your syntax. It's completely up to you whether or not to use them in your code.

### Parentheses Customization

For **conditional statements** like `if`, `else if`, and `while` loops, you can choose to **use or omit parentheses** around conditions. This customization allows you to streamline your code and make it more intuitive according to your preferences.

### Customizable Operators

HTVM allows you to **customize operators** to make your code more readable or suit your style. For example, instead of using `==` for equality, you can change it to a keyword like `is`. This means you can write more natural, human-readable code, such as:

- `if var1 is 5` (instead of `if var1 == 5`).

This flexibility extends across various operators, giving you full control over how your conditions and operations are structured.


## More Customization Options in HTVM

HTVM offers even **more customization** for your syntax and style. Here's a breakdown of additional features:

### Type Definition Styles

You can choose between **PostFix** or **Prefix** style for type definitions, similar to TypeScript:

- **PostFix**: Define the variable first, then the type after the colon (`var1: int`).
- **Prefix**: Define the type first, then the variable (`int var1`).

You can toggle between these styles depending on which one fits your preferred syntax better.

### Array Syntax Customization

HTVM lets you customize the array syntax by choosing between two options:

- **Regular braces** (`[]`): The default style for arrays.
- **Curly braces** (`{}`): If you prefer this style, you can toggle it on.

It's fully flexible, so you can use whichever syntax feels right for your code.

### Customizable Operators

HTVM extends **operator customizability** even further, allowing you to adjust a wide range of operators:

- **All operators**: You can customize **all operators**, including logical, comparison, and even **bitwise operators**.
- **Assignment operators**: You can customize assignment operators, such as `=`, to whatever you prefer (e.g., `is`, `set`, or any other single word).

However, remember that you are only allowed to use **one word** for customization—no spaces in operator names.

### Customizable Comments

Comments are also fully customizable:

- **Single-line comments**: Change the single-line comment syntax to whatever you like (e.g., `//`, `#`, or any word).
- **Multi-line comments**: Customize the syntax for multi-line comments, allowing for multiple words or characters if necessary.

### Custom Escape Characters

Escape characters can now be **customized**:

- **Escape character**: You are no longer limited to using just the backslash (`\`). You can choose any single character you want as your escape character—such as the backtick (`` ` ``) or something entirely different.

### Loop Index Customization

You can **change the index for regular loops**. By default, HTVM uses **zero-based indexing** for loops. However, you can change this for certain languages:

- **AutoHotKey and Lua**: By default, both of these languages use **one-based indexing** for arrays and loops.
- **Other languages**: It's important to note that **changing loop indices may cause issues** with some languages, as not all languages support customizable loop indexes. **Use caution** when making changes to this setting, especially when working with languages like Python, JavaScript, or C++.

HTVM allows for this change, but it’s recommended to keep the default zero-based indexing unless you’re specifically creating **meme languages** where the index may be something unconventional (like `-69` or `420`).

### Key Considerations for Indexing

- For **AutoHotKey** and **Lua**, the index starts at **one** by default.
- For **other languages**, **zero-based indexing** is the norm, so be mindful of this when converting to other languages.
  
If you are creating custom languages or experimenting with unconventional indexing, keep these limitations in mind to avoid potential issues when converting to other languages.

---


## Further Customization in HTVM

HTVM offers **even more customization options**, allowing you to tailor the language to your preferences, especially when it comes to types and arrays.

### Custom Type Names

HTVM allows you to **customize type names** to anything you like. For example:

- **Basic Types**: Instead of using the traditional `int`, you can use `number`, `i`, or any other word you prefer. The same goes for types like `double`, `char`, `boolean`, `float`, and more.
- **Integer Sizes**: You can change types like `int16` to `i16` or any naming convention you prefer.
  
**Important:** While you can use **multiple words** for type names, be cautious about potential conflicts in the parser. For instance, using common words that might be parsed as something else could lead to issues. Always ensure that the type names are unique and won't interfere with other syntax elements.

The available types you can customize include:

- **Void**: You can rename `void` to whatever you want.
- **Integers**: `int`, `int8`, `int16`, `int32`, `int64`, etc.
- **Unsigned Integers**: `uint8`, `uint16`, `uint32`, `uint64` (Note: be cautious when converting unsigned integers to Java, as Java doesn’t support them).
- **Floating Point**: `double`, `float`.
- **Character**: `char`.
- **String**: `string`.
- **Boolean**: `boolean`.

---

### Array Types Customization

In HTVM, you can customize the **array types** as well:

- **Four main array types**:
  - `arr str`: For arrays of strings.
  - `arr int`: For arrays of integers.
  - `arr float`: For arrays of floating-point numbers.
  - `arr bool`: For arrays of booleans.
  
- **Dynamic Arrays**: For dynamic-type languages, you can use the generic `array` keyword, but it defaults to a string array when converted to static type languages. This provides a flexible way to define arrays in your code.
  
**Note on Static vs. Dynamic Types**: In **static-type languages**, arrays are strictly defined, so if you use the `array` keyword, it will default to a **string array**. For **dynamic languages**, the array type is more flexible.

---

### Array Methods Customization

HTVM allows you to customize array methods with ease. These methods work by appending a dot (`.`) after the array, followed by the method name:

- **append**: Adds an element to the end of the array.
- **pop**: Removes the last element from the array.
- **size**: Retrieves the size (length) of the array.
- **insert**: Inserts an element at a specific index (not by value).
- **remove**: Removes an element at a specific index (not by value).
- **indexOf**: Finds the index of a value in the array.

These methods can be customized with different names or functionality if needed, making it easier to manipulate arrays according to your needs.

---

### Important Considerations

- **Java and Unsigned Integers**: Be careful when converting unsigned integers (`uint8`, `uint16`, etc.) to **Java**, as Java does not support unsigned integers. HTVM will **NOT** warn you when attempting this conversion.
- **Array Methods**: Ensure that you define methods like `insert` and `remove` clearly to avoid confusion with other types of array manipulations. Using the dot (`.`) ensures consistency and clarity in how methods are applied to arrays.

---

## Extensive Customization in HTVM

HTVM offers **wide-ranging customization options** to ensure the language suits your preferences, especially when it comes to keywords and functionality. You can customize several aspects of the language, ranging from basic variable declarations to control structures and even language-specific keywords.

### Customizing Keywords

HTVM allows you to customize many fundamental keywords that are used across different programming languages:

- **Variable Declarations**: Customize `var`, `let`, and `const` keywords. These are primarily used in **JavaScript** and **TypeScript**. 
  - The `const` keyword is supported in most languages, but in languages that don't have constants (e.g., **Python**, **AutoHotKey**, **Lua** and some more), it will be ignored, and the variable will be created as usual.
  
- **Boolean Keywords**: Change the `true` and `false` keywords to something else like `yeah` and `nah`. This customization provides flexibility in how logical values are represented.
  
- **Null Keyword**: You can also customize the `null` keyword, though be cautious—some languages do not support `null` in the same way (e.g., **Python**, **C++**, **AutoHotKey** and some more). For languages that don't support `null`, the value will simply be ignored or treated as an empty value.
  
- **End Keyword**: You can change the `end` keyword to something else. This is typically used for denoting the end of code blocks in various languages and is customizable in HTVM.

- **Global Keyword**: 
  - The `global` keyword works only in **Python** and **AutoHotKey**. It allows passing a global variable into a function and modifying it. In other languages, the `global` keyword will be ignored, but the variable will still be created.
  - You can also customize the `global` keyword to something else, keeping the functionality intact within supported languages.

---

### Main Label and Main Function Customization

HTVM allows you to **customize the main function label**. The main label refers to the starting point of your program, especially for languages like **C++** and many more but in **JavaScript** and **TypeScript** it's a bit different:

- **Main Label**: 
  - This is a customizable label where your main function is typically located. You can define a single word or even multiple words as the main label. The parser will ensure that the code below the label is treated as the main function's content. 
  - The main label is optional, and it’s simply a label—there’s no need to wrap the code in a block unless the language requires it (e.g., **Python** doesn’t need a `main` function, so the code will be placed directly beneath it).
  
- **Main Function**:
  - In **JavaScript** and **TypeScript**, you can toggle between an **async main function** and a regular one.
  - The language will default to creating asynchronous functions for all function definitions, but you can customize this behavior with the **async** keyword (which is also customizable to other terms if you prefer). Also, if you don’t use the main label keyword, the HTVM parser will assume that you haven't created any functions, and all the code will be placed in the main function if the target language has a main function.

---

### Function Customization

HTVM allows you to **customize various function-related keywords** to suit your needs:

- **Async Functions**: 
  - By default, all functions in HTVM are asynchronous. You can toggle this behavior or use the **asynchronous** keyword, which is customizable.
  - The **await** keyword can also be modified to something else (e.g., `wait`) to fit your naming preferences.
  
- **Loop Customization**: 
  - The loop syntax can be customized with terms like `A_Index` and `A_LoopField` to resemble **AutoHotKey**-style loops. These keywords provide a cleaner, more intuitive loop structure for those familiar with AutoHotKey.

---

### Important Considerations

- **Customizing Keywords**: When you customize keywords (e.g., `const`, `true`, `false`, `null`), ensure that they don’t conflict with existing language constructs. The parser will handle many of these customizations, but be aware of limitations in certain languages.
  
- **Global Variables**: The `global` keyword is supported in **Python** and **AutoHotKey**, but it will be ignored in other languages like **JavaScript** or **C++**. Ensure you understand how this will behave across different languages.

- **Async Functions in JavaScript/TypeScript**: This is especially useful for **JavaScript** and **TypeScript** but can be customized to suit your project’s needs.

---

HTVM provides a **high level of flexibility** for customizing how the language operates, allowing you to adapt it to the specific needs of your project. Whether you're working with variable declarations, loop structures, or customizing language-specific keywords, HTVM makes it easier to code in a way that feels natural to you.

---

## Advanced Customizations in HTVM

HTVM offers **advanced customizations** that allow you to control everything from ternary operators to error handling and even modularity with `include`. This flexibility makes it possible to tailor the language to your coding style and needs.

### Ternary Operator Customization

HTVM lets you customize the **ternary operator**:

- By default, HTVM uses the regular **C-style ternary operator** (`condition ? true : false`). This works in most languages, but certain languages (like **Go**) do not support this syntax.
- For languages that use a different syntax for ternary operators, HTVM will handle the conversion automatically, converting it to the appropriate format.
  - For example, **Python** uses the `condition if true else false` syntax.
  - HTVM will ensure that the ternary operator is properly converted, but if the target language does not support ternary operators, HTVM will generate a message and prevent execution in languages like **Go** where it won’t run. This ensures that you avoid runtime errors from unsupported syntax.

### Error Handling Customization

HTVM allows you to **customize error handling** as well:

- The `try`, `catch`, `finally`, and `throw` keywords are customizable, enabling you to tailor them to your preference.
- When using **throw**, you can customize the function name for the error message. This is how it works:
  - Type `throw`, followed by the function name (which is customizable), open parentheses, and inside the parentheses, you can pass a string that represents the error message.
  - Example:
    ```htvm
    throw ErrorMsg("Something went wrong!")

    ```
- **Conversion to Other Languages**:
  - HTVM converts error handling to most languages, but **Lua** and **Go** are exceptions. In those languages, the error handling structure is not supported, and HTVM will generate a string that alerts you about the lack of support.
  - HTVM does not provide error handling within itself. Instead, it relies on the target language to handle errors since HTVM assumes your code is flawless, and any issues should be identified by the language you're transpiling to.

### Include Keyword Customization

HTVM also supports **modularity** through the `include` keyword:

- The `include` keyword allows you to include other HTVM files at the top of your code.
- This is useful for organizing your code across multiple files or for reusing common functionality across different projects.
  - Example:
    ```htvm
    include "utility_functions.htvm"

    ```
- The `include` keyword is fully customizable, so you can change it to something else if preferred.

---

### Key Takeaways:

- **Ternary Operator**: Customizable to fit different syntaxes across languages, with automatic conversion. However, unsupported in **Go** and it will hardcode a message instead of running.
  
- **Error Handling**: Customizable for the `try`, `catch`, `finally`, and `throw` keywords, and the function name for error messages can also be customized. HTVM does not handle errors itself but relies on the target language’s error handling. However, unsupported languages like **Go** and **Lua** will hardcode a message instead of running.

- **Include**: Supports modularity by including external HTVM files, and the keyword itself is customizable.

These advanced customizations further enhance HTVM's flexibility, allowing you to adjust error handling, ternary operators, and file management to fit your needs. With these tools, HTVM can be tailored to suit your specific coding style and make your development process more efficient.

---

## Programming Blocks in HTVM

HTVM introduces **programming blocks** that allow you to **mix languages** seamlessly in your code. This feature is designed to handle cases where HTVM itself can't achieve something directly or when you'd prefer to rely on another language for specific tasks.

### How Programming Blocks Work

1. **Opening a Programming Block**: You can open a programming block for a specific target language with the following syntax:
    - One line to open the programming block.
    - Inside the block, you can write in the target language.
    - You close the block on a new line after your code.

Example:
```htvm
; This is a JavaScript programming block. It will stay intact and included in the JS output.
___js start
// this is now JavaScript code
console.log("==========================")
___js end

```

2. **Incorporating Blocks into HTVM Code**:
    - When you write in HTVM, you can seamlessly insert target-language code using programming blocks.
    - For example, if you're converting to **JavaScript**, you can open a **JavaScript programming block**, and the code inside will be converted directly to JavaScript and placed in the converted code without alteration.
    - If the HTVM code contains loops or other structures, the programming block code stays intact in the appropriate place during conversion.

3. **Multiple Programming Blocks**: You can use **multiple programming blocks** for different target languages, but they will be context-sensitive:
    - **For JavaScript**: The **Python programming block** will be ignored during conversion.
    - **For Python**: The **JavaScript programming block** will be ignored.
    - In other words, only the relevant programming block for the target language will be included in the final code.

Example:
- **JavaScript block** in HTVM:
```htvm
; Open JavaScript block
___js start
console.log("Hello, world!");
___js end
; End JavaScript block

```
- **Python block** in HTVM:
```htvm
; Open Python block
___py start
print("Hello, world!")
___py end
; End Python block

```
When converting to **JavaScript**, the Python block will disappear, and only the JavaScript block will be included.

4. **Reverse Programming Blocks**:
    - You can also open an **HTVM programming block** within other target language code (e.g., C++). The block will then be converted into HTVM-compatible code.
    - For example, if you're writing in C++ and need to use HTVM-specific functionality, you can insert an HTVM block, and it will be transpiled into C++ when you convert the code.
    - The process works by specifying the **target file** (e.g., `main.cpp`), and the HTVM block inside it will be converted based on the file's extension.

5. **Universal Programming Block**:
    - If two languages share the same syntax for a particular construct, HTVM allows you to use a **universal programming block**. This block can handle situations where HTVM cannot achieve the desired behavior but the syntax matches in multiple languages.
    - This is useful when the target languages have compatible syntax for specific code constructs but HTVM doesn't support them directly.

6. **Conversion and Functionality**:
    - During conversion, HTVM ensures that only the relevant programming block is preserved based on the target language. Unused blocks are omitted.
    - When converting code, HTVM will automatically include any necessary built-in functions or libraries for the target language, displaying them in the console.


### Key Advantages of Programming Blocks:

- **Flexibility**: Allows mixing HTVM with other languages for complex or specialized tasks.
- **Modularity**: Enables using language-specific libraries or features when HTVM cannot do the job.
- **Customizability**: Supports a wide range of languages, with options to adjust and adapt as needed.
- **Seamless Conversion**: Code stays in place, and HTVM ensures proper language-specific syntax is followed.

---

### Key Takeaways:
- **Programming blocks** allow writing code in another language directly within HTVM, which will be preserved during conversion to that language.
- Multiple programming blocks can be used, but only the relevant block will be included based on the target language.
- **Reverse programming blocks** allow you to insert HTVM code into other target language code.
- The **universal programming block** enables handling languages with similar syntax for specific constructs.


#### **And More...**  
- Go to [HTVM's website](https://themaster1127.github.io/HTVM) to explore all the syntax customizability and create your own language.

### **The Power of HTVM – Beyond Anything Else**  
This isn’t just some hobby project. **HTVM Version 2 took many months just for the parser.** And that was with prior experience from HTVM Version 1 and all the work put into previous languages like HT++, HTH, and HTpy. Every single language had to be carefully mapped out—loops, if-statements, try/catch blocks, functions, variables, types—**every detail had to be considered, tested, and tweaked.**  

And here’s the thing: **HTVM doesn’t just output to one language at a time—it can compile to multiple languages simultaneously.** That means you can write a single HTVM file and have it generate both JavaScript and Python code at the same time. That alone is something **almost no other tool in the world can do.**  

---

### **Programming Blocks – Total Control Over Your Code**  
And then we have **Programming Blocks.** These allow you to **write native code for the target language directly inside HTVM files**. So if you’re converting to JavaScript and need something that HTVM doesn’t handle natively, you can just open a **JavaScript Programming Block**, write JavaScript inside it, and it will only be included when compiling to JavaScript.  

But it gets even crazier—**you can have multiple programming blocks for different languages in the same file.** That means you can mix HTVM, JavaScript, Python, and C++ **all in one place** and still have everything work correctly.  

And if that wasn’t enough, there are **Reverse Programming Blocks**—which allow for even more insane levels of customization. Even if nobody uses them, **HTVM is so complete that the feature is still there.**  

---

### **The Future of Programming**  
HTVM **isn’t just a transpiler—it’s the future of programming.**  

This is a system that allows **anyone** to create their own syntax, define how they want their language to behave, and then generate fully functional code in fifteen different programming languages. No more being stuck with a single syntax or workflow—**HTVM lets you build programming your way.**  

Think about it. If you had to manually convert HTVM to fifteen different languages, it would take months just for a single feature. But **HTVM automates that entire process**—**once your syntax is defined, your language works across all targets instantly.**  

### **HTVM – The Future of Programming**  
This level of customization **doesn’t exist anywhere else.** No other system gives you this much control over how your language looks and feels. You’re not just writing code—you’re **designing your own programming experience.**  

HTVM isn’t just powerful—it’s **insane.** This is how programming should be.

**HTVM doesn’t force you into a fixed way of coding—it lets you create your own language and then outputs it into real programming languages.**  

HTVM **isn’t just another programming tool. It’s a revolution.**

---

## OSP (Ordinal Struct Programming)

[Go back](#htvm-documentation)

OSP (Ordinal Struct Programming) is HTVM's built-in approach for organizing data and related procedures using hierarchical namespaces and explicit path-based access. It focuses on **ordinal** positioning – meaning the unique location of structures within the defined hierarchy (`alliance`, `crew`). This feature offers an alternative for structuring code, particularly for those who prefer direct data manipulation and clear, absolute referencing over features like inheritance or encapsulation found in traditional OOP.

### What is a `struct` in HTVM OSP?

At its core, a `struct` in HTVM OSP is similar to structs in languages like C: it's a way to **group related data fields together under a single name**.

-   **Definition:** You define a struct using the `struct` keyword.
-   **Properties:** Inside a struct, you define its data fields using the `prop` keyword. Each `prop` holds a piece of data (like an integer, string, boolean, or even an array).
-   **Access:** Crucially, you *always* access struct properties using their **full, absolute path** starting from the top level (or the struct name if defined standalone). For example: `MyAlliance.MyCrew.MyStruct.myProp`.
-   **Global Nature:** Structs defined in OSP are globally accessible from any point in the code below their definition, using their full path.

```htvm
; Example of a simple, standalone struct
struct Configuration {
    prop str theme := "dark"
    prop int fontSize := 12
    prop bool spellCheck := true
}
; Accessing its properties later
; Access using the struct name as the path
print(Configuration.theme)
; Modifying a property
Configuration.fontSize := 14

```

### Optional Hierarchy: `alliance` and `crew`

While you can define simple `struct`s directly, OSP provides optional hierarchical keywords (`alliance` and `crew`) for better organization, especially in larger projects:

-   **`alliance`**: The top-level organizational container.
-   **`crew`**: A sub-level container within an `alliance` (or potentially nested within other crews, though nesting isn't shown in examples).

**Why use hierarchy?**

-   **Organization:** Group related structs and procedures together logically (e.g., all UI elements in a `GUI` crew, all vehicle data in a `Vehicles` crew).
-   **Avoiding Name Collisions:** If you had two different concepts both needing a `struct` named `Settings`, you could place them in different crews (e.g., `Audio.Settings` and `Video.Settings`) allowing them to coexist without conflict. Using `alliance` and `crew` acts like creating namespaces.

Most of the time, for simpler data organization, you might just need standalone `struct`s. Use `alliance` and `crew` when you need the extra structure to avoid naming hurdles and keep related components neatly grouped.

```htvm
alliance Game {
    crew Audio {
        ; This is Game.Audio.Settings
        struct Settings {
            prop int volume := 80
        }
    }
    crew Video {
        ; This is Game.Video.Settings - no collision!
        struct Settings {
            prop str resolution := "1920x1080"
        }
    }
}
; Access using the full path
print(Game.Audio.Settings.volume)
print(Game.Video.Settings.resolution)

```

### Procedures (`proc`)

Procedures are functions defined within the OSP hierarchy (`alliance` or `crew`) using the `proc` keyword. They are intended to perform actions related to the structs within their hierarchy.

-   **Association:** Defining a `proc` inside an `alliance` or `crew` links it semantically to that part of the hierarchy.
-   **Global Access:** Like structs, `proc`s are globally accessible via their full path (e.g., `MyAlliance.MyCrew.myProc`).
-   **Context (`this` Keyword):** Procedures can optionally accept a special parameter named `this` to understand *which* struct (identified by its path string) initiated the call.

### The `this` Keyword (Procedure Context)

The `this` keyword in OSP (Ordinal) is **different** from `this` in traditional OOP.

-   **Purpose:** It serves as an **optional input parameter for `proc`s**. When a `proc` is called with a struct's path string, `this` holds that **literal string value** inside the `proc`.
-   **Usage:** It allows a `proc` to perform different actions based on *which* struct path was passed to it. This is typically checked using simple string comparison (`if (this == "MyAlliance.MyCrew.MyStruct")`).
-   **Mechanism:** You must explicitly pass the **full path of the struct as a string** when calling the `proc` if you intend for that `proc` to use the `this` context.
-   **Limitation:** This string-based approach is explicit but requires careful maintenance. If you rename a `struct` or change the hierarchy, you **must** update all the corresponding string literals used in `proc` calls and within the `proc`'s `if/else if` checks. It doesn't automatically track the struct itself.

```htvm
alliance Movable {
    crew Vehicles {
        struct Car {
            prop int fuel := 100
        }
        struct Bike {
            prop int energy := 100
        }
        ; Proc using 'this' to know which struct called it
        ; 'this' will hold "Movable.Vehicles.Car" or "Movable.Vehicles.Bike"
        proc void checkStatus(this) {
            if (this = "Movable.Vehicles.Car") {
                ; Still use full path for access
                print("Checking Car fuel: " . Movable.Vehicles.Car.fuel)
            }
            else if (this = "Movable.Vehicles.Bike") {
                ; Still use full path
                print("Checking Bike energy: " . Movable.Vehicles.Bike.energy)
            }
            else {
                print("Unknown vehicle type passed to checkStatus: " . this)
            }
        }
    }
}
main
; Calling the proc with the context string
Movable.Vehicles.checkStatus("Movable.Vehicles.Car")
Movable.Vehicles.checkStatus("Movable.Vehicles.Bike")

```

### Key Rules Recap

1.  **Full Path Access:** Always use the full, absolute path to access `struct` properties (e.g., `Alliance.Crew.Struct.prop`).
2.  **`this` is Context String:** The `this` keyword, when used in a `proc`, holds the *path string* passed during the call. It's only valid inside `proc`s and requires explicit string comparison for conditional logic.

### Arrays in Structs

Arrays can be defined as properties within structs just like any other data type:

```htvm
struct name {
    prop arr str prop1
    prop arr str prop2
    prop arr str prop3
    prop arr str prop4
}

```

### Summary of OSP (Ordinal Struct Programming)

-   **Organizes** code using optional `alliance`/`crew` hierarchies and `struct` data containers.
-   **Emphasizes** explicit, **ordinal** (position-based) access via mandatory **full paths**.
-   Uses `struct` for data aggregation and `proc` for associated procedures within the hierarchy.
-   Offers an optional `this` keyword for `proc`s to receive the **calling struct's path as a string**, enabling context-specific actions via string comparison.
-   Provides **global accessibility** for all defined structs and procs via their full paths.
-   Serves as an **alternative structure** within HTVM, focusing on explicitness and hierarchy, potentially avoiding certain OOP complexities but introducing verbosity and reliance on string paths for context.

---

## Note:

### Never use underscores when naming things in OSP. Otherwise, you can use them, but be cautious because underscores can be unstable.

---

#### Example of OSP (Ordinal Struct Programming)

```htvm
alliance Movable {
    crew Vehicles {
        struct Car {
            prop int door := 4
            prop int fuel := 100
            prop bool hasFUEL := true
        }
        struct Bike {
            prop bool hasGears := true
            prop int energy := 100
            prop bool hasENERGY := true
        }
        proc void move(this) {
            global Movable.Vehicles.Car.fuel
            global Movable.Vehicles.Car.hasFUEL
            global Movable.Vehicles.Bike.energy
            global Movable.Vehicles.Bike.hasENERGY
            if (this = "Movable.Vehicles.Car") {
                if (Movable.Vehicles.Car.fuel > 0) {
                    print("The car is driving.")
                    Movable.Vehicles.Car.fuel := Movable.Vehicles.Car.fuel - 10
                }
                else {
                    print("The car is out of fuel.")
                    Movable.Vehicles.Car.hasFUEL := false
                }
            }
            else if (this = "Movable.Vehicles.Bike") {
                if (Movable.Vehicles.Bike.energy > 0) {
                    print("The bike is pedaling.")
                    Movable.Vehicles.Bike.energy := Movable.Vehicles.Bike.energy - 5
                }
                else {
                    print("The bike is out of energy.")
                    Movable.Vehicles.Bike.hasENERGY := false
                }
            }
        }
    }
    crew settings {
        struct GeneralSettings {
            prop str difficulty := "normal"
            prop int volume := 50
            prop str resolution := "1920x1080"
        }
        struct AudioSettings {
            prop int masterVolume := 70
            prop int musicVolume := 50
            prop int sfxVolume := 40
        }
        struct DisplaySettings {
            prop bool fullscreen := true
            prop str aspectRatio := "16:9"
        }
    }
    crew actions {
        ; General Settings Procs
        proc void resetGeneralSettings(this) {
            Movable.settings.GeneralSettings.difficulty := STR("normal")
            Movable.settings.GeneralSettings.volume := 50
            Movable.settings.GeneralSettings.resolution := STR("1920x1080")
            print("General settings reset to default.")
        }
        proc void printGeneralSettings(this) {
            print("General Settings:")
            print("Difficulty: " . Movable.settings.GeneralSettings.difficulty)
            print("Volume: " . STR(Movable.settings.GeneralSettings.volume))
            print("Resolution: " . Movable.settings.GeneralSettings.resolution)
        }
        ; Audio Settings Procs
        proc void resetAudioSettings(this) {
            Movable.settings.AudioSettings.masterVolume := 70
            Movable.settings.AudioSettings.musicVolume := 50
            Movable.settings.AudioSettings.sfxVolume := 40
            print("Audio settings reset to default.")
        }
        proc void printAudioSettings(this) {
            print("Audio Settings:")
            print("Master Volume: " . STR(Movable.settings.AudioSettings.masterVolume))
            print("Music Volume: " . STR(Movable.settings.AudioSettings.musicVolume))
            print("SFX Volume: " . STR(Movable.settings.AudioSettings.sfxVolume))
        }
        ; Display Settings Procs
        proc void resetDisplaySettings(this) {
            Movable.settings.DisplaySettings.fullscreen := true
            Movable.settings.DisplaySettings.aspectRatio := STR("16:9")
            print("Display settings reset to default.")
        }
        proc void printDisplaySettings(this) {
            print("Display Settings:")
            print("Fullscreen: " . STR(Movable.settings.DisplaySettings.fullscreen))
            print("Aspect Ratio: " . Movable.settings.DisplaySettings.aspectRatio)
        }
    }
    crew array {
        struct name {
            prop arr str prop1
            prop arr str prop2
            prop arr str prop3
            prop arr str prop4
        }
    }
}
main
; Test vehicle movement
while (Movable.Vehicles.Car.hasFUEL = true) and (Movable.Vehicles.Bike.hasENERGY = true) {
    Movable.Vehicles.move("Movable.Vehicles.Car")
    Movable.Vehicles.move("Movable.Vehicles.Bike")
    print("=====================================")
}
; Test settings manipulation
Movable.settings.GeneralSettings.difficulty := STR("hard")
Movable.settings.GeneralSettings.volume := 80
Movable.settings.GeneralSettings.resolution := STR("2560x1440")
Movable.settings.AudioSettings.masterVolume := 90
Movable.settings.AudioSettings.musicVolume := 60
Movable.settings.AudioSettings.sfxVolume := 50
Movable.settings.DisplaySettings.fullscreen := false
Movable.settings.DisplaySettings.aspectRatio := STR("21:9")
Movable.actions.printGeneralSettings()
Movable.actions.printAudioSettings()
Movable.actions.printDisplaySettings()
Movable.actions.resetGeneralSettings()
Movable.actions.resetAudioSettings()
Movable.actions.resetDisplaySettings()
Movable.actions.printGeneralSettings()
Movable.actions.printAudioSettings()
Movable.actions.printDisplaySettings()
; Test array manipulation
Movable.array.name.prop1.add("1text1")
Movable.array.name.prop1.add("1text2")
Movable.array.name.prop1.add("1text3")
Movable.array.name.prop2.add("2text1")
Movable.array.name.prop2.add("2text2")
Movable.array.name.prop2.add("2text3")
Movable.array.name.prop3.add("3text1")
Movable.array.name.prop3.add("3text2")
Movable.array.name.prop3.add("3text3")
Movable.array.name.prop4.add("4text1")
Movable.array.name.prop4.add("4text2")
Movable.array.name.prop4.add("4text3")
; Loop over and print
Loop, % Movable.array.name.prop1.size() {
    print(Movable.array.name.prop1[A_Index])
}
Loop, % Movable.array.name.prop2.size() {
    print(Movable.array.name.prop2[A_Index])
}
Loop, % Movable.array.name.prop3.size() {
    print(Movable.array.name.prop3[A_Index])
}
Loop, % Movable.array.name.prop4.size() {
    print(Movable.array.name.prop4[A_Index])
}

```

OSP (Ordinal Struct Programming) provides a structured, path-based approach to organizing data and procedures within HTVM, emphasizing explicit referencing.

---

### How Your Language Looks Like

[Go back](#htvm-documentation)

Get to know how HTVM code is structured and its syntax style. HTVM uses a clean, human-readable syntax that focuses on simplicity and ease of use. You can define your own syntax, making HTVM incredibly flexible and tailored to your needs.

Your language uses curly braces for indentation, square brackets for array definitions, parentheses around conditions in control flow statements (e.g., if, else if, while loops, like `if (condition)` or `while (condition)`), prefix type for variable definitions (similar to C-style type declaration, e.g., `int var1 = 5`).

Here is how it looks like:

```htvm
; This is how your language looks like.
; Here's how types will appear if you only define them:
int varName1
str varName2
bool varName3
float varName4
int8 varName5
int16 varName6
int32 varName7
int64 varName8
; Alternatively, you can define them like this:
int varName9 := 34
; Here is how to define a function with static types if you convert to C++.
; However, it will still work even if you are not converting to C++; types will be stripped away.
func void funcName1(int paramVar1, str paramVar2 := "", bool paramVar3 := false, float paramVar4 := 1.5) {
    ; This is how the global keyword works if we convert to Python.
    ; But even if we don't, it will just be removed, so you can add it if you want to convert to Python as well.
    global varName5
    ; Here's how if, else if, and else statements will look:
    if (varName1 = paramVar1) {
        print("varName1 is equal to paramVar1")
    }
    else if (varName1 != paramVar1 or varName1 <= paramVar1) {
        print("varName1 is less than or equal to paramVar1")
    }
    else {
        print("varName1 is NOT less than or equal to paramVar1 or something else")
    }
    ; this is how the return keyword will look like in your lang
    return
}
; This is where the main function will start. It's just a label, so don't worry.
main
funcName1(varName9)
; this is how a while loop works in your lang
bool var1 := false
while (var1 = false) {
    print("we are inside the while loop")
    var1 := true
}
print("we are outside the while loop")
; this is how to use a loop whit arrays
arr str array123 := ["hey"]
array123.add("hello")
array123.add("how")
array123.add("are")
array123.add("you")
array123.add("doing")
Loop, % array123.size() {
    print("iteration: " . STR(A_Index))
    print("Item: " . array123[A_Index])
}
print("this is how the escape char looks like `nthis is a new line")
'''1
this is a comment block
this is a comment block
'''2
; this is how to use an AutoHotKey like Loop
Loop, 10 {
    if (A_Index % 2 = 0) {
        continue
    }
    print(A_Index)
}
; this is how to use an AutoHotKey like infinite Loop
Loop {
    if (A_Index = 5) {
        break
    }
    else {
        print(A_Index)
    }
}
; this is how to use an AutoHotKey like Loop, parse
str someText := "hello how are you doing`ntoday we are good."
Loop, Parse, someText, " ", `n {
    print(A_LoopField)
}
; Error Handling
try {
    throw ErrorMsg("Something went wrong!")
}
catch (e) {
    print(e)
}
finally {
    print("Finally block executed")
}

```

### Advanced String Features

HTVM supports powerful string definition methods, including formatted strings (f-strings) and multiline strings for easier text handling.

*   **F-Strings (`f"..."`)**: Allow embedding variables and expressions directly within strings.
*   **Multiline Strings (`mls`...`mle`)**: Define strings that span multiple lines, preserving formatting (like newlines and indentation) exactly as written. Ideal for raw text, templates, or ASCII art.
*   **Multiline F-Strings (`fmls`...`mle`)**: Combine the benefits of multiline strings and f-strings, allowing embedded variables and expressions within a multiline block.

Here's how you can use them:

```htvm
int calculation := 10 + 5
str message := f"The result is: {calculation}. Double is: {calculation * 2}"
print("Regular F-String:")
print(message)
print("=========================")
; === Multiline String (Raw) Example ===
str ascii_cat := mls
 /\_/\
( o.o )
 > ^ <
mle
print("Multiline String (Raw):")
print(ascii_cat)
print("=========================")
; === Multiline F-String Example ===
str userName := "Alice"
int items := 3
int price := 25
str order_summary := fmls
Order Summary for: {userName}
Items purchased: {items}
Total cost: ${items * price}
Thank you for your order!
Newlines and indentation are preserved.
mle
print("Multiline F-String:")
print(order_summary)
print("=========================")

```

#### Summary: The Power of Advanced Strings

These advanced string features (`f`, `mls`, `fmls`) significantly enhance HTVM's usability and power. They eliminate the need for cumbersome string concatenation and complex formatting logic.

*   **Readability**: Code becomes much cleaner and easier to read, especially when dealing with templates, long text blocks, or dynamic content generation.
*   **Simplicity**: Constructing complex strings with embedded variables or preserving exact formatting is now straightforward and intuitive.
*   **Expressiveness**: HTVM becomes even more expressive, allowing you to focus on the logic rather than wrestling with string manipulation quirks.

This level of string handling flexibility is a testament to HTVM's design philosophy: providing powerful, convenient tools that adapt to the programmer's needs, ultimately making development faster and more enjoyable. It's another step towards making HTVM the future of simplified, yet powerful, programming.

---


### Programming Blocks

[Go back](#htvm-documentation)

Programming blocks in HTVM allow you to write code directly in the target language when HTVM itself cannot handle certain tasks. These blocks give you the flexibility to insert language-specific code into your HTVM project without disrupting the overall flow. There are two main use cases for programming blocks: single-language programming blocks and multi-language programming blocks.

#### **Single-Language Programming Block**

A single-language programming block allows you to write code directly in the target language. If you're converting HTVM code to, say, C++, you can open a programming block and write C++ code inside. This block will only be valid in the context of converting to C++ and will disappear when converting to another language.

**Example:**

```htvm
; Open a programming block for C++
___cpp start
// Write C++ code here
___cpp end

```

#### **Multiple-Language Programming Block**

HTVM also supports multiple-language programming blocks, where you can write code in different languages for the same functionality. For instance, if you're converting to both C++ and JavaScript, you can write separate blocks for each language but ensure the code behaves similarly in both.

**Example:**

```htvm
; Open a programming block for C++
___cpp start
// Write C++ code here
___cpp end
; Open a programming block for JavaScript
___js start
// Write JavaScript code here
___js end

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
- To open - `___inhtvm start`
- To close - `___inhtvm end`

3. Pass both the `.cpp` file and the HTVM instruction file to HTVM.

HTVM will:

- Replace the HTVM code with C++ (or the corresponding language).
- Display the libraries and built-in functions that need to be included.

---


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
int myInt := 42
int8 mySmallInt := -5
uint16 myPositiveInt := 500
float myFloat := 3.14
double myDouble := 2.718
char myChar := 'A'
str myText := "Hello, HTVM!"
bool myBool := true
; print all variables
print(myInt)
print(mySmallInt)
print(myPositiveInt)
print(myFloat)
print(myDouble)
print(myChar)
print(myText)
print(myBool)

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
const int x := 10

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
int myNumber := 5
___py start
myNumber += 10
___py end
; Will print 15 in Python
print(myNumber)

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
int sharedNumber := 20
___cpp start
sharedNumber += 5;
___cpp end
___py start
print(sharedNumber)  # ❌ This won't work because Python can't access C++ variables
___py end

```

To fix this, you need to **manually synchronize values** in each programming block.

---

### **Unsigned Integers & Java**  

- **Java does not support unsigned integers** (`uint8`, `uint16`, etc.).
- If you try to use them, **HTVM will not warn you**, but Java might throw errors.
- **Avoid using unsigned integers when converting to Java.**  

Example of bad practice:  

```htvm
uint32 myUnsigned := 500

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


### Functions

[Go back](#htvm-documentation)

Explore how to define and use functions for modular and reusable code. Functions in HTVM can be written easily, and the language supports efficient handling of function calls, parameters, and returns.

### **HTVM Functions**  

Functions in HTVM allow you to create reusable pieces of code. A function is defined using the `func` keyword, followed by the return type, the function name, and its parameters.

#### **Defining a Function**

```htvm
func int add(int a, int b) {
    return a + b
}

```

```htvm
func str addStringPlusInt(str a, int b) {
    return a . STR(b)
}

```

```htvm
func void greet() {
    print("Hello, world!")
}

``` 

Optional parameters example:

```htvm
str varName5 := "hi"
func str funcName1(int paramVar1, str paramVar2 := "", bool paramVar3 := false, float paramVar4 := 1.5) {
    ; This is how the global keyword works if we convert to Python.
    ; But even if we don't, it will just be removed, so you can add it if you want to convert to Python as well.
    global varName5
    ; this is how the return keyword will look like in your lang
    return STR(paramVar1)
}
; This is where the main function will start. It's just a label, so don't worry.
main
print(funcName1(5))

```

If you are converting to a dynamically typed language, the types will be stripped away automatically. However, for statically typed languages, you must include them.  

#### The `main` Function

In HTVM, the `main` function is required if you are using functions. It is defined as a simple label at the beginning of the program. If you do not include the `main` function, HTVM will insert it automatically at the top of the code. However, if you define any functions and do not include the `main` label, the program will not work as expected.

The `main` label is where the execution starts in languages that use a main function (like C++). In languages that do not require a `main` function (like Python), HTVM handles it automatically.

Here’s how it looks:

```htvm
func void greet() {
    print("Hello, world!")
}
; You can just use this label, and it's all handled for you
main
greet()

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
crew someCrew {
    struct someStruct {
        prop str someText := ""
    }
    proc str someProc(this) {
        print(this)
        return this
    }
}
main
"hqwesr".print
"hqwesr".print(
"hqwesr".print()
print("hawesd")
str var1 := " helLO "
var1 := Trim(StrLower(var1))
var1 := var1.StrLower.Trim
var1 := var1.StrLower(.Trim(
var1 := var1.StrLower(.Trim
var1 := var1.StrLower.Trim(
var1 := var1.StrLower().Trim()
var1 := var1.StrLower().Trim
var1 := var1.StrLower.Trim()
someCrew.someStruct.someText := var1
; for OSP you need to use () they are not optional unless it's not at the beginning of the line like this:
if (someCrew.someStruct.someText.someCrew.someProc = "hello") {
    print("hi")
}
; or
; We can't use someCrew.someStruct.someText.someCrew.someProc(
; We need to use () since it's not at the beginning of the line.
if (someCrew.someStruct.someText.someCrew.someProc() = "hello") {
    print("hi")
}
; or
if (someCrew.someProc(someCrew.someStruct.someText) = "hello") {
    print("hi")
}
; otherwise, if it's at the beginning of the line we need to use () for OSP
someCrew.someStruct.someText.someCrew.someProc()
; or you can use only 1 ( for extra fast typing
someCrew.someStruct.someText.someCrew.someProc(
; or
someCrew.someProc(someCrew.someStruct.someText)
; WARNING: If you are not calling it at the beginning of the line
; and you are inside an if statement or other places,
; don't use only 1 ( use both ().

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
| `arr int`     | Array of integers (regular size depends on the target language) |
| `arr float`   | Array of floating-point numbers |
| `arr bool`    | Array of booleans (true or false) |
| `arr str`  | Array of strings (text) |

> **Note:** In dynamic languages like JavaScript and Python, you can use arrays without explicitly defining the type. The type will be inferred or stripped out, depending on the language.

---

### **The Generic Array Type**  

In addition to the specific array types above, HTVM provides a more flexible **generic array** keyword which is `arr`. This allows you to create arrays without specifying a type. When you use this keyword:

- In **dynamically typed languages** (e.g., JavaScript, Python), HTVM will infer the type based on the values you assign.
- In **statically typed languages** (e.g., C++, Java), HTVM will convert it into a `std::vector&lt;std::string>` / `string[]`.

This provides flexibility, but also means you lose type checking, and you’ll need to ensure the elements in the array match the expected type.

Example (Dynamic Language):
```htvm
; In (e.g., JavaScript, Python), this will be inferred as an array of integers
arr myArray := [1, 2, 3, 4]

```

---

### **Array Methods in HTVM**

| **Method**                          | **Description**                                                                                |
|-------------------------------------|------------------------------------------------------------------------------------------------|
| `.add()`    | Adds an element to the end of the array.                                                       |
| `.pop()`       | Removes and returns the last element of the array.                                             |
| `.size()`      | Returns the number of elements in the array.                                                   |
| `.insert()`    | Inserts an element at a specific index.                                                        |
| `.rm()`    | Removes the element at the specified index.                                                    |
| `.indexOf()`   | Returns the index of the first occurrence of the specified element. Returns `-1` if not found. |

---

### **Array Methods in Detail**

HTVM provides a set of useful methods to manipulate arrays in your programs. These methods follow a consistent `.method()` syntax, making it easy to interact with arrays. Below are the array methods supported in HTVM:

1. **`.add()`**  

Adds an element to the end of the array.  
Example:
```htvm
arr int myArray := [1, 2, 3]
myArray.add(4)
; myArray is now [1, 2, 3, 4]
print(myArray)

```

2. **`.pop()`**  

Removes and returns the last element of the array.  
Example:
```htvm
arr int myArray := [1, 2, 3, 4]
myArray.pop()
; myArray is now [1, 2, 3]
print(myArray)

```

3. **`.size()`**  

Returns the number of elements in the array.  
Example:
```htvm
arr int myArray := [1, 2, 3]
; returns 3
print(myArray.size())

```

4. **`.insert()`** 
 
Inserts an element at a specific index. The index is the first argument, and the element to insert is the second argument.  
Example:
```htvm
arr int myArray := [1, 2, 3]
myArray.insert(1, 4)
; myArray is now [1, 4, 2, 3]
print(myArray)

```

5. **`.rm()`**  

Removes the element at the specified index.  
Example:
```htvm
arr int myArray := [1, 2, 3, 4]
myArray.rm(2)
; myArray is now [1, 2, 4]
print(myArray)

```

6. **`.indexOf()`**  

Returns the index of the first occurrence of the specified element. If the element is not found, it returns `-1`.  
Example:
```htvm
arr int myArray := [1, 2, 3, 2]
print(myArray.indexOf(2))
; returns 1

```

---

### **Example of Using Array Methods in HTVM**

```htvm
arr int myArray := [1, 2, 3]
myArray.add(4)
; Removes the element at index 1
myArray.rm(1)
; Inserts 5 at index 1
myArray.insert(1, 5)
; Output: [1, 5, 3, 4]
print(myArray)

```

In the example above, you can see how various methods like `.add()`, `.rm()`, and `.insert()` are used in sequence to manipulate the array.

---

### **Summary of Array Methods**

- **`.add()`**: Adds an element to the end of the array.
- **`.pop()`**: Removes and returns the last element of the array.
- **`.size()`**: Returns the size of the array.
- **`.insert(index, element)`**: Inserts an element at the specified index.
- **`.rm(index)`**: Removes the element at the specified index.
- **`.indexOf(element)`**: Finds the index of the first occurrence of the specified element.

---

### **Arrays in Programming Blocks**  

Just like variables, arrays can be accessed and modified inside **programming blocks**. Programming blocks in HTVM are directly written in the target language and do not undergo conversion. The following behaviors apply to arrays inside programming blocks:

- **Arrays persist across blocks**, meaning changes made to an array within a block are retained when the block ends.
- **Arrays are not scoped**—they are part of the target language’s code.
- **Different programming languages do not share arrays across blocks**, just like variables.

Example (Converting to Python):

```htvm
arr int myArray := [1, 2, 3]
___py start
myArray.append(4)  # Modifying the array inside the Python block
___py end
; Will print: [1, 2, 3, 4] if converted to python otherwise it will print [1, 2, 3]
print(myArray)

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
; In JavaScript, this will be an array with mixed types, but HTVM won't warn you
arr int myArray := [1, "two", 3]

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
arr int myArray := [1, 2, 3]
___cpp start
myArray.push_back(4);  // In C++, this works, but HTVM does not enforce immutability
___cpp end
; If we print this in HTVM, we will get:
;
; When converting to C++, we can't just print the array directly. However, in some other languages,
; we don't need to loop over the array to print it.
Loop, % myArray.size() {
    print(myArray[A_Index])
}
; If you convert this to any language other than C++ (cpp), it will print:
; 1
; 2
; 3

```

If you want immutability or similar behavior, you must handle it manually within programming blocks or by controlling logic in your code.

---

### **Arrays in Multiple Language Conversions**  

When converting to **multiple languages**, arrays function similarly to variables in programming blocks. However, you cannot directly **share arrays between different language blocks**. Each block is isolated in its respective language, so any array manipulations within one block will not affect another block.

Example (Invalid cross-language access):

```htvm
arr int myArray := [1, 2, 3]
___cpp start
myArray.push_back(4);  // Modifies the array in C++
___cpp end
___py start
# It will print [1, 2, 3]
print(myArray)  # ❌ This will not work because Python can't access the C++ array. 
# Since the C++ block is gone, it will only print [1, 2, 3].
___py end
; If converted to Python, it will print: [1, 2, 3]
; If converted to C++, it will print: [1, 2, 3, 4]
; If converted to another language, it will print: [1, 2, 3]
print(myArray)

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







### Loops

[Go back](#htvm-documentation)

### **Understanding Loops in HTVM**

HTVM supports multiple types of loops, inspired by AutoHotKey (AHK) syntax. These loops are designed to be simple and efficient, offering flexibility for various tasks. Let’s explore the **Regular Loop**, **Loop Parse**, **Infinite Loop**, and the **while loop**.

**Regular Loop** = `Loop,`

**Loop Parse** = `Loop, Parse,`

**Infinite Loop** = `Loop`

**While loop** = `while`

**continue** = `continue`

**break** = `break`

**A_Index** = `A_Index`

**A_LoopField** = `A_LoopField`


### **1. Regular Loop**

The `Loop,` keyword in HTVM is the simplest and most common type of loop. It runs a specified number of iterations, and you can use the `A_Index` keyword to track the current iteration number.

#### Example:

```htvm
; Regular loop example
Loop, 10 {
    if (A_Index % 2 = 0) {
        ; Skip even numbers
        continue
    }
    ; Output only odd numbers from 1 to 9
    print(A_Index)
}

```

In this loop, `A_Index` is used to track the current iteration number. The `continue` keyword is used to skip even numbers, so only odd numbers will be printed.

---

### **2. Loop Parse**

The `Loop, Parse,` is similar to AutoHotKey’s loop parsing method, where you can iterate over a string or text with different delimiters. In HTVM, `A_LoopField` is used to access the current field (or token) in the string being parsed.

#### **Example 1: Delimited by Space (" ")**

```htvm
; Loop Parse with space delimiter
str someText := "hello how are you doing today"
Loop, Parse, someText, " " {
    ; Output each word in the string separated by spaces
    print(A_LoopField)
}

```

In this example, the loop iterates over each word in the string `someText`, which is delimited by spaces. The `A_LoopField` holds the current word from the string.

#### **Example 2: Delimited by New Line**

```htvm
; Loop Parse with new line delimiter
str multiLineText := "line 1`nline 2`nline 3"
Loop, Parse, multiLineText, `n {
    ; Output each line of text
    print(A_LoopField)
}

```

Here, the loop splits the text by new lines, and `A_LoopField` holds each line individually.

#### **Example 3: Delimited by Carriage Return**

```htvm
; Loop Parse with carriage return delimiter
str textWithCarriageReturn := "line 1`rline 2`rline 3"
Loop, Parse, textWithCarriageReturn, `r {
    ; Output each line separated by carriage returns
    print(A_LoopField)
}

```

In this case, the text is delimited by carriage returns, and each line is printed separately.

#### **Example 4: Delimited by Both Space and New Line**

```htvm
; Loop Parse with space and new line delimiters
str mixedText := "hello world`nhow are you doing today"
Loop, Parse, mixedText, " ", `n {
    ; Output each word or line separated by spaces or new lines
    print(A_LoopField)
}

```

This example uses both a space and a new line as delimiters to split the string into tokens.

#### **Example 5: No delimited**

```htvm
; Loop Parse each character when using no delimiters
str word := "master"
Loop, Parse, word {
    ; Output each character
    print(A_LoopField)
}

```

This example uses no delimiters to parse each character.

---

### **3. Infinite Loop**

HTVM also supports infinite loops using the `Loop` keyword without a defined number of iterations. The loop will continue running until a `break` condition or manual termination occurs. The `continue` keyword can be used inside the infinite loop to skip the current iteration and continue with the next one.

#### Example (Infinite Loop):

```htvm
; Infinite Loop example
Loop {
    if (A_Index = 5) {
        ; Exit the loop when A_Index is 5
        break
    }
    else {
        ; Print the current value of A_Index
        print(A_Index)
    }
}

```

Here, the loop runs indefinitely, printing the current value of `A_Index`. When `A_Index` reaches 5, the loop breaks. You can also use `continue` to skip iterations as needed.

---

### **4. While Loop**

The `while` loop in HTVM works like a typical while loop in other languages. It continues to execute the loop body as long as the specified condition evaluates to true.

#### Example (While Loop):

```htvm
; While loop example
bool var1 := false
while (var1 = false) {
    print("we are inside the while loop")
    var1 := true
}
print("we are outside the while loop")

```

In this example, the `while` loop runs once because the condition is initially true, then changes `var1` to true, causing the loop to terminate.

---

### **Array Example in Loop**

HTVM also allows arrays, which can be used in loops for more complex tasks. Here’s an example that iterates over an array:

```htvm
; Array example in loop
arr123 := ["apple", "banana", "cherry"]
Loop, % arr123.size() {
    ; Output each element in the array
    print(arr123[A_Index])
}

```

In this case, the loop iterates through each element of the array `arr123` using `A_Index` to reference the array's index.

---

### **Variable Example in Loop**

With HTVM, you can also use variables to control loops. Here's an example:

```htvm
; Loop example with variable range
var1 := 5
Loop, % var1 {
    ; Output the current iteration
    print(A_Index)
}

```

This example shows how HTVM allows you to use variables like `var1` to control the number of iterations in the loop, with `A_Index` printing the current iteration number.

---

### **Key Notes:**
- **`A_Index`**: Used in all loops except for `while` loops.
- **`A_LoopField`**: Used only in `Loop, Parse,` to reference the current field.
- **`continue`**: Can be used in any loop to skip the current iteration and continue with the next one. When converting to Lua, place the `::continue` at the end of the loop, just before it ends.

---

### **Lua Conversion**

For the **Loop,**, **Loop, Parse,**, and **Loop** types, the Lua conversion looks like this:

```htvm
; Regular loop example
Loop, 10 {
    if (A_Index % 2 = 0) {
        continue
    }
    ; Output only odd numbers from 1 to 9
    print(A_Index)
    ::continue
}
print("=====================")
; Infinite loop example
Loop {
    if (A_Index % 2 = 0) {
        continue
    }
    ; Output only odd numbers from 1 to 9
    print(A_Index)
    if (A_Index = 9) {
        break
    }
    ::continue
}
print("=====================")
; Loop, Parse loop example
str var1 := "hello whats up bro how are you doing"
Loop, Parse, var1, " " {
    if (A_LoopField = "bro") {
        continue
    }
    ; 3 will never print
    print(A_Index)
    ::continue
}

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

This approach with `::continue` is used only for the 3 types of loops but NOT the `while` loop.

> **Note:** Lua does not support a native `continue` statement. To mimic this behavior, we use a labeled `goto`—specifically `goto continue`—followed by a `::continue::` label at the end of the loop.  
> This approach is **only required when converting to Lua**. If you're using HTVM with JavaScript, Python etc... as the target language, there's **no need to write or worry about `::continue`**—it's automatically ignored or excluded in those environments.

---

### **Conclusion**

In HTVM, we have three main types of loops:

1. **Regular Loop** - `Loop,` - Simple iteration over a specified number of times.
2. **Loop Parse** - `Loop, Parse,` - Iterates over fields in a string or text, with customizable delimiters.
3. **Infinite Loop** - `Loop` - A loop that runs indefinitely until broken manually or a condition is met.
4. **While Loop** - `while` - A standard loop that runs while a condition is true.

Each of these loops is intuitive and makes it easy to handle a variety of looping needs. Make sure to use `A_Index` and `A_LoopField` where appropriate, and use the `continue` keyword to control loop flow. When converting to Lua, remember to add `::continue` just before the loop ends.

---



### Comments

[Go back](#htvm-documentation)

## **Comments in HTVM**

Comments are essential for writing clear and maintainable code. They allow you to document your code without affecting how it runs. In HTVM, there are different types of comments: **Standalone Comments**, **Multi-line Comments**, **Inline Comments**, and **Comments in Programming Blocks**. Here's how each of them works:

---

### **Standalone Comments:**

**Standalone comments** are written on their own line and **will convert** properly when transforming to **other HTVM languages** or any target programming languages. These comments are perfect for leaving explanations or notes that need to be preserved across conversions.

```htvm
; ✅ This comment will convert to any HTVM language or target language conversion.
```

**💡 Tip:** Standalone comments are **ideal** when you need your notes to **convert** correctly across different languages and maintain clarity for others who may work with your code.

---

### **Multi-line Comments:**

**Multi-line comments** are used for writing longer explanations or comments that span multiple lines. They must **always start and end on their own lines**—you cannot place extra text before or after the opening and closing markers. Inside multi-line comments, you can write as much text as you want.

```htvm
'''1
This is a multi-line comment.
It will be preserved in all conversions.
'''2
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
print("some text") ; ❌ is comment will disappear when converting to another HTVM language or any target language.
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
; Create a container (div) - Options separated by spaces OR commas
gui [Option1:Value1] [Option2:Value2] ...
gui [Option1:Value1],[Option2:Value2],...

; Add a specific control element - ElementType followed by space/comma separated options
gui &lt;ElementType&gt; [Option1:Value1] [Option2:Value2] ...
gui &lt;ElementType&gt;,[Option1:Value1],[Option2:Value2],...
```

*   **`&lt;ElementType&gt;`**: Specifies the type of control to add (e.g., `button`, `text`, `edit`). If omitted, a container (`div`) is created.
*   **`[Options...]`**: A series of options defining the element's properties. **Options can be separated by SPACES or COMMAS.**

**Option Flexibility:**

1.  **Separators**: Options can be separated by **SPACES** or **COMMAS**. You can mix them.

```htvm
; Space separated is often cleaner also different style of defining values
gui button x:50 y100 w"200px" h:"30px"
; Comma separated also works
gui button,x:"50px",y:"100px",w:"200px",h:"30px"
```

2.  **Key-Value Format**: Use `key:value` or single-letter prefixes `kvalue`. Many aliases exist (see [Options & Aliases](#options--aliases)).
3.  **Case Insensitivity**: Option *keys* and element types are case-insensitive. Option *values* (like IDs, text content, callback names) are case-sensitive.
4.  **`add` Keyword**: Optional and ignored (`gui add button` is the same as `gui button`).
5.  **Grouping**: Options can span multiple lines using `{...}`, `[...]`, or `(...)` for readability. Separator rules (spaces or commas) still apply inside the group.

```htvm
; Single line with spaces
gui button x:"10px" y:"10px" w:"100px" h:"30px" id:"myBtn" callback:MyAction value:"Click"

; Multi-line grouping (using spaces within the lines)
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
; Single line modification
guicontrol [Option1:Value1] [Option2:Value2] ...
guicontrol [Option1:Value1],[Option2:Value2],...

; Multi-line modification using flexible grouping (), [], or {}
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
Button0:
; and the ID of the button is automatically assigned to button0
; for each element, it has a separate counter.
await MsgBox("You pressed the " . A_Id)
subout
; main func
main
gui button x50% y50%

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

*(See HTVM source (`guiParserStep4`) for a full alias list.)*

#### Exmaple:

```htvm
str saveEdit := ""
; Edit0 callback
Edit0:
saveEdit := A_Value
subout
; Button0 callback
Button0:
guiControl p"Gui1" i"text0" dsaveEdit
subout
; main func
main
w := "300px"
; define the gui window
gui pid:"Gui1" x50% y50% ww h200
; add elements
gui pid:"Gui1" text ww y27.5% d"Edit box text will be updated here..." css:"text-align: center;"
gui pid:"Gui1" edit x50% y45% ph:"Type something..."
gui pid:"Gui1" button x50% y65%

```

### Callbacks and State Management

Callbacks connect GUI events to HTVM logic (labels ending in `subout`). Logic **must start on the line AFTER the label**, not on the same line. Use `await` before functions like `MsgBox` that return Promises in JavaScript.

**Managing State (Input Example):**

To retrieve data entered by the user (e.g., in an `edit` field), store the data from the input's callback (`A_Value`) into a shared state, typically using global variables or an OSP struct. Using an OSP `struct` is often better for organization, but global variables work too.

**Getting Input Example (using OSP Struct - Recommended):**

```htvm
; Define an OSP struct to hold GUI state
struct UserInput {
    prop str name := ""
}
; Callback for the edit field (default name Edit0)
Edit0:
; Store current value from A_Value into the struct property
; NOTE: 'global' keyword is NOT needed here because the target is JavaScript
UserInput.name := A_Value
subout
; Callback for the button
ShowNameButton:
; Read the value from the struct property
await MsgBox("Hello, " . UserInput.name . "!")
subout
main
; Prepare string variables for dimensions and text
str editX_px := 10 . "px"
str editY_px := 10 . "px"
str editW_px := 200 . "px"
str editH_px := 30 . "px"
str btnX_px := 10 . "px"
str btnY_px := 50 . "px"
str btnW_px := 100 . "px"
str btnH_px := 30 . "px"
str placeholderText := "Enter your name"
str btnText := "Greet"
; Edit field uses default callback Edit0. Use SPACE separation.
gui edit x:editX_px y:editY_px w:editW_px h:editH_px placeholder:placeholderText id:"nameInput"
; Button uses explicit callback ShowNameButton. Use SPACE separation.
gui button x:btnX_px y:btnY_px w:btnW_px h:btnH_px value:btnText callback:ShowNameButton id:"greetButton"

```

**Callback Parameters:** `A_Id`, `A_Value`, `A_Event` provide context within the callback label.

### Examples

*(Using space separation, pre-concatenated units, OSP struct for state where beneficial, correct callback formatting, and await for MsgBox)*

**Example 1: Simple Input and Button (using OSP Struct)**

```htvm
; OSP Struct for state
struct FormData {
    prop str firstName := ""
    prop str lastName := ""
}
; Callbacks
Edit0:
FormData.firstName := A_Value
subout
Edit1:
FormData.lastName := A_Value
subout
ButtonOK:
; Use the struct properties
str greeting := "You entered " . FormData.firstName . " " . FormData.lastName . "."
await MsgBox(greeting)
subout
main
; Prepare string variables only where needed (e.g., for text with spaces)
str fNameLabel := "First name:"
str lNameLabel := "Last name:"
str fNamePlaceholder := "First Name..."
str lNamePlaceholder := "Last Name..."
str btnText := "Send"
str whiteColor := "white"
; Use hardcoded pre-formatted strings for simple values, variables for complex ones.
gui text x:"10px" y:"10px" w:"150px" h:"30px" value:fNameLabel color:whiteColor
gui edit x:"10px" y:"40px" w:"150px" h:"30px" placeholder:fNamePlaceholder id:"firstNameEdit"
gui text x:"10px" y:"100px" w:"150px" h:"30px" value:lNameLabel color:whiteColor
gui edit x:"10px" y:"130px" w:"150px" h:"30px" placeholder:lNamePlaceholder id:"lastNameEdit"
gui button x:"10px" y:"200px" w:"155px" h:"45px" value:btnText callback:ButtonOK id:"sendButton"

```

**Example 2: Sized Container (Hardcoded)**

```htvm
main
; Define text content in variable as it might contain spaces
str containerId := "mainContainer"
; Hardcode dimensions and colors directly
gui id:containerId width:"500px" height:"700px" backgroundColor:"#121212"
; Add elements inside, hardcoding simple positions/sizes
gui text parentId:containerId x:"10px" y:"10px" value:"This text is inside" color:"white"
gui button parentId:containerId x:"10px" y:"60px" width:"80%" height:"50px" value:"Wide Button"

```

**Example 3: Button Grid using Loops (Using A_Id)**

```htvm
; --- Callbacks ---
ButtonClicked:
; Use A_Id to identify which button was clicked
await MsgBox("You clicked on button with ID: " . A_Id)
subout
; --- Main Setup ---
main
columns := 3
rows := 3
btnWidth := 140
btnHeight := 40
gap := 10
startX := 10
startY := 10
str gridContainerId := "gridContainer"
containerW := startX + (columns * btnWidth) + ((columns - 1) * gap) + startX
containerH := startY + (rows * btnHeight) + ((rows - 1) * gap) + startY
str containerW_px := containerW . "px"
str containerH_px := containerH . "px"
str btnWidth_px := btnWidth . "px"
str btnHeight_px := btnHeight . "px"
str bgColor := "#333"
; define the grid container
gui id:gridContainerId x50% y50% width:containerW_px height:containerH_px backgroundColor:bgColor
currentX := startX
currentY := startY
btnCounter := 0
Loop, % columns {
    colIndex := A_Index
    Loop, % rows {
        btnCounter++
        str btnId := "gridBtn" . btnCounter
        str btnText := "Button" . btnCounter
        str currentX_px := currentX . "px"
        str currentY_px := currentY . "px"
        ; Use {} for better readability for the button options
        gui {
            button
            parentId:gridContainerId, id:btnId
            x:currentX_px, y:currentY_px, w:btnWidth_px, h:btnHeight_px
            value:btnText
            callback:ButtonClicked
        }
        currentY := currentY + btnHeight + gap
    }
    currentX := currentX + btnWidth + gap
    currentY := startY
}

```

**Example 4: Toggle, Dropdown, Picture Update (using OSP Struct)**

```htvm
; --- OSP Struct for state ---
struct AppState {
    prop str toggleState := "On"
    prop str selectedObject := ""
    prop bool errorInDropdown := false
}
; --- Callbacks ---
ToggleCallback:
AppState.toggleState := A_Value ? "On" : "Off"
await MsgBox("Toggle is now " . AppState.toggleState)
subout
; ------------------
; Default Picture callback — not needed, but when you click on it, it will call this:
; (optional)
Picture0:
; If you use one MsgBox like this, there's no need to use 'await' — unless you're using two MsgBoxes.
MsgBox, you clicked on the image
subout
; ------------------
DropdownCallback:
if (A_Value = "Select a object") {
    await MsgBox("Cannot select placeholder!")
    AppState.errorInDropdown := true
}
else {
    AppState.errorInDropdown := false
    AppState.selectedObject := A_Value
    await MsgBox("You selected: " . AppState.selectedObject)
}
subout
; ------------------
SaveButtonCallback:
if (AppState.errorInDropdown = true) {
    await MsgBox("Select valid object first.")
}
else {
    await MsgBox("Saving... Toggle:" . AppState.toggleState . ", Selection:" . AppState.selectedObject)
    str newImageUrl := "https://picsum.photos/200"
    ; Use SPACE separation for guicontrol options
    guicontrol id:"Image1" value:newImageUrl
}
subout
; --- Main GUI ---
main
; Variables for complex/reused values
str initialImageUrl := "https://i.ibb.co/Jpty1B8/305182938-1a0efe63-726e-49ca-a13c-d0ed627f2ea7.png"
str OptionBtest := "Option B"
str dropdownOptions := "Select a object|" . OptionBtest . "|Option C"
str saveBtnText := "Save changes"
; IDs
str toggleId := "myToggle"
str dropdownId := "myDropdown"
str saveBtnId := "saveButton"
str imageId := "Image1"
; Use hardcoded pre-formatted strings for simple dimensions/positions, space separated
gui toggle x10 y10 value:true id:toggleId callback:ToggleCallback
gui dropdown x210 y10 h30 value:dropdownOptions id:dropdownId callback:DropdownCallback
gui button x10 y50 w140 h40 value:saveBtnText id:saveBtnId callback:SaveButtonCallback
gui picture x10 y150 id:imageId value:initialImageUrl

```

**Example 5: Using `rawCss` for Styling**

```htvm
Button0:
MsgBox("You clicked on " . A_Id)
subout
main
; Define CSS styles in variables
str buttonStyles := "font-weight:bold;text-transform:uppercase;animation:spin 2s infinite linear;filter:hue-rotate(360deg);text-shadow:0 0 5px red,0 0 10px yellow,0 0 15px lime;"
str panelId := "styledPanel"
str buttonId := "styledButton"
str buttonText := "Styled Button"
; Create a container styled like a window using rawCss or css alias
gui {
    id:panelId x:"50px" y:"50px" w:"400px" h:"200px" backgroundColor:"#EEE"
    css:"border: 2px solid blue; padding: 15px; box-shadow: 5px 5px 10px #888888;"
}
; Add a button inside the panel with additional rawCss styles using the other style []
gui [
button
parentId:panelId
x20 y20 w150 h40
id:buttonId value:buttonText rawCss:buttonStyles
]

```

**Example 6: HTVM Simulated Numeric Adjuster Using Buttons and Input Field (0–100 Range)**

```htvm
sliderValue := 50
func  IncrementSlider() {
    sliderValue += 1
    if (sliderValue > 100) {
        sliderValue := 100
    }
    guiControl pid:"Gui1" i:"sliderValueText" d:sliderValue
    Button0()
}
func  DecrementSlider() {
    sliderValue -= 1
    if (sliderValue < 0) {
        sliderValue := 0
    }
    guiControl pid:"Gui1" i:"sliderValueText" d:sliderValue
    Button0()
}
Button0:
if (editText != "") {
    guiControl pid:"Gui1" i:"text0" d:editText
    sliderValue := INT(editText)
    editText := ""
}
else {
    guiControl pid:"Gui1" i:"text0" d:sliderValue
}
subout
editText := INT(sliderValue)
Edit0:
oldText := editText
if (Trim(A_Value) = "") {
    guiControl pid:"Gui1" i:"sliderValueText" d:""
}
else if (A_Value >= 0) and (A_Value <= 100) {
    editText := A_Value
}
else {
    MsgBox, ONLY USE NUMBRERS BETTWEN 0-100
    guiControl pid:"Gui1" i:"sliderValueText" d:oldText
}
subout
; main func
main
w := "300px"
gui {
    pid:"Gui1"
    x50%  ,,,,,,,,,,,,,,,,,,,,,
    y50%,
    ww ,
    h500
}
; add all elements
gui pid:"Gui1" text ww y25 d"Simulated Slider Value..." size:25 css:"text-align: center;"
gui pid:"Gui1" eedit, i"sliderValueText" x50% y125 d:sliderValue
gui pid:"Gui1" button x50% y225 d"Update Text"
gui pid:"Gui1" button x50% y325 d"Increase" callback:IncrementSlider
gui pid:"Gui1" button x50% y425 d"Decrease" callback:DecrementSlider

```

**Example 7: `Tic-tac-toe`**

```htvm
; ==================================
; Tic-Tac-Toe Game State Variables
; ==================================
arr str boardState := [" ", " ", " ", " ", " ", " ", " ", " ", " "]
str currentPlayer := "X"
bool gameIsOver := false
str gameStatus := "Player X's Turn"
; ==================================
; Helper Functions
; ==================================
; --- Checks if the current player has won ---
func bool CheckWin() {
    arr str winCombos := ["0,1,2", "3,4,5", "6,7,8", "0,3,6", "1,4,7", "2,5,8", "0,4,8", "2,4,6"]
    Loop, % winCombos.size() {
        combo := winCombos[A_Index]
        idx1_str := StrSplit(combo, ",", 1)
        idx2_str := StrSplit(combo, ",", 2)
        idx3_str := StrSplit(combo, ",", 3)
        idx1 := INT(idx1_str)
        idx2 := INT(idx2_str)
        idx3 := INT(idx3_str)
        if (boardState[idx1] = currentPlayer and boardState[idx2] = currentPlayer and boardState[idx3] = currentPlayer) {
            return true
        }
    }
    return false
}
; --- Checks if the game is a draw ---
func bool CheckDraw() {
    Loop, % boardState.size() {
        if (boardState[A_Index] = " ") {
            return false
        }
    }
    if (gameIsOver = false) {
        return true
    }
    return false
}
; --- Updates the status text display ---
func void UpdateStatusDisplay() {
    ; We can use () or [] or even mix them like [) or (] — yeah, HTVM is so flexible.
    guicontrol (
    parentId:"mainContainer"
    id:"statusText"
    value:gameStatus
    )
}
; --- Resets the game board and state ---
func void ResetBoard() {
    i := 0
    while (i < 9) {
        boardState[i] := " "
        i := i + 1
    }
    Loop, 9 {
        btnIndex := A_Index
        str btnIdToReset := "btn" . STR(btnIndex)
        str emptyVal := " "
        ; We can use [] or () or even mix them like [) or (] — yeah, HTVM is so flexible.
        guicontrol [
        parentId:"mainContainer"
        id:btnIdToReset
        value:emptyVal
        isEnabled:true
        ]
    }
    currentPlayer := "X"
    gameIsOver := false
    gameStatus := "Player X's Turn"
    UpdateStatusDisplay()
}
; ==================================
; GUI Callbacks
; ==================================
; --- Handles clicks on any of the 9 grid buttons ---
GridButtonClicked:
if (gameIsOver = true) {
    return
}
clickedId := A_Id
str indexStr := SubStr(clickedId, 4)
index := INT(indexStr)
if (boardState[index] != " ") {
    print("Cell already taken!")
    return
}
boardState[index] := currentPlayer
; We can also use a one-liner, no problem—but during a one-liner, we can't use {}, (), or [] since it's a single line.
guicontrol parentId:"mainContainer" id:clickedId value:currentPlayer isEnabled:false
if (CheckWin() = true) {
    gameIsOver := true
    gameStatus := "Player " . currentPlayer . " Wins!"
    UpdateStatusDisplay()
    return
}
if (CheckDraw() = true) {
    gameIsOver := true
    gameStatus := "It's a Draw!"
    UpdateStatusDisplay()
    return
}
if (currentPlayer = "X") {
    currentPlayer := "O"
}
else {
    currentPlayer := "X"
}
gameStatus := "Player " . currentPlayer . "'s Turn"
UpdateStatusDisplay()
subout
; --- Handles clicks on the Restart button ---
RestartGame:
ResetBoard()
subout
; ==================================
; Main GUI Setup
; ==================================
main
; --- Define GUI constants/variables ---
btnSize := 80
gap := 10
boardSize := (btnSize * 3) + (gap * 2)
containerPadding := 20
containerWidth := boardSize + (containerPadding * 2)
containerHeight := boardSize + 100 + (containerPadding * 2)
; Prepare strings with "px" units
str btnSize_px := btnSize . "px"
str containerWidth_px := containerWidth . "px"
str containerHeight_px := containerHeight . "px"
statusY_num := boardSize + containerPadding + 10
restartY_num := statusY_num + 40
str statusY_px := statusY_num . "px"
str restartY_px := restartY_num . "px"
str restartWidth_px := 150 . "px"
str restartHeight_px := 40 . "px"
str statusWidth_px := boardSize . "px"
str statusHeight_px := 30 . "px"
str containerPadding_px := containerPadding . "px"
; Colors and styles
str bgColor := "#282c34"
str textColor := "white"
str btnBgColor := "#61dafb"
str btnFontColor := "#282c34"
str btnFontSize_px := "40px"
str statusFontSize_px := "20px"
str restartBtnBgColor := "#f0ad4e"
str restartBtnFontColor := "white"
str restartBtnFontSize_px := "16px"
; Text variables
str restartText := "Restart Game"
; --- Create the main container ---
gui {
    id:"mainContainer"
    x50% y50%
    w:containerWidth_px h:containerHeight_px
    backgroundColor:bgColor
    rounding:10
}
; --- Create the Status Display Text ---
; *** UPDATED: Using multi-line grouping {} ***
; You can use comma or not doesn't matter use ,,,,,,,,,,,, doesn't matter use 5 spaces no problem use comments no problem either
gui {
    ; this means text
    text
    parentId:"mainContainer" id:"statusText"
    x:containerPadding_px, y:statusY_px, w:statusWidth_px, h:statusHeight_px
    value:gameStatus color:textColor
    ; Here we see there are no spaces for the option size—that's because spaces aren't allowed during an option.
    ; Use a variable or a workaround, but NO spaces.
    size:INT(statusFontSize_px)
    ; this is a css style for the text
    rawCss:"text-align:center;font-weight:bold;"
}
; --- Create the 3x3 Grid Buttons using nested Loops ---
currentX := containerPadding
currentY := containerPadding
btnCounter := 0
; Rows
Loop, 3 {
    row := A_Index
    ; Columns
    Loop, 3 {
        col := A_Index
        str btnId := "btn" . STR(btnCounter)
        str currentX_px := currentX . "px"
        str currentY_px := currentY . "px"
        str btnStyle := "font-size:" . btnFontSize_px . ";font-weight:bold;color:" . btnFontColor . ";"
        ; Adding the buttons
        gui {
            button
            parentId:"mainContainer"
            id:btnId
            x:currentX_px, y:currentY_px, w:btnSize_px, h:btnSize_px
            value:" "
            callback:GridButtonClicked
            backgroundColor:btnBgColor
            rounding:5, rawCss:btnStyle
        }
        currentX := currentX + btnSize + gap
        btnCounter := btnCounter + 1
    }
    ; Reset X for next row
    currentX := containerPadding
    ; Move Y down for next row
    currentY := currentY + btnSize + gap
}
; --- Create the Restart Button ---
; Center the restart button
str restartX_px := ((containerWidth - 150) / 2) . "px"
str restartBtnStyle := "font-size:" . restartBtnFontSize_px . ";font-weight:bold;"
; *** UPDATED: Using multi-line grouping {} ***
gui {
    button
    parentId:"mainContainer" id:"restartBtn"
    x:restartX_px y:restartY_px
    w:restartWidth_px h:restartHeight_px
    value:restartText callback:RestartGame
    backgroundColor:restartBtnBgColor color:restartBtnFontColor
    rounding:5 rawCss:restartBtnStyle
}
; --- Initial status update after GUI is built ---
UpdateStatusDisplay()
; --- End of Main ---

```

### Summary

HTVM's GUI system offers a simplified yet powerful way to build graphical user interfaces directly within your HTVM code, targeting **JavaScript web environments**. By using the intuitive `gui` command to define elements and containers, and `guicontrol` to modify them dynamically, you can build interactive web applications. The system leverages flexible option syntax (spaces, commas, shorthand, multi-line grouping) and automatically handles underlying HTML/CSS/JS generation, adhering to HTVM's philosophy of **reducing keystrokes and complexity**. Understanding the conditional requirement for `parentId` in `guicontrol` (it's only optional if no custom containers are defined) is key to correctly manipulating elements.

The `gui` and `guicontrol` features allows developers to focus on interface logic and layout using their custom HTVM syntax, bridging the gap between high-level design and functional web UIs.

---




### Backend in HTVM

[Go back](#htvm-documentation)

**⚠️ Language Limitation: Python Only (Flask)**

HTVM's Backend functionality generates **Python** code using **Flask**. It does **not** support other languages like JavaScript (Node.js) for backend generation. Use these commands only when targeting Python (`py`).

---

### Introduction

HTVM provides simple commands to create basic web backends in Python. This enables communication between your HTVM frontend (JavaScript GUI) and a server for tasks needing server-side logic or access. Communication is primarily plain text over HTTP (defaulting to POST).

### Backend Commands

Use these commands in your backend HTVM file (`.htvm` targeted for Python). They **must** use comma separators.

#### `fileinit, filename`

**Essential.** Initializes Flask and sets the root route (`/`) to serve your main frontend file.

*   **`filename`**: Name of your frontend file (e.g., `main.js`, `index.html`). Must be in the same directory as the generated Python script.
*   If `.js`, HTVM wraps it in basic HTML (with `sweetalert2`). If `.html`, served directly.
*   **Must be used before `endpoint,` or `port,`.**

*   **NOTE:** You don't have to use `fileinit, index.html` if you're just serving the default `index.html` file, since it will do that automatically.

---

#### `endpoint, route_or_label_name, [label_name_if_different], [method]`

Registers an HTVM label (backend logic block) as an HTTP endpoint.

*   **`route_or_label_name` (Mandatory):**
    *   If **only this parameter** is provided (besides the optional method), it serves as **both** the URL path (e.g., `/hello`) and the HTVM label name (e.g., `hello:`).
    *   If `label_name_if_different` is also provided, this parameter is treated solely as the URL path (e.g., `processData` becomes route `/processData`). No leading/trailing slashes needed here.
*   **`[label_name_if_different]` (Optional):** The exact HTVM label name (case-sensitive) if it's different from the URL route name. If omitted, the value from `route_or_label_name` is used.
*   **`[method]` (Optional):** HTTP method (`POST`, `GET`, etc.). Defaults to `POST`.

**Examples:**

Registers route "/myapi" linked to label "myapi:" (POST default)

`endpoint, myapi`

Registers route "/user/data" linked to label "GetUserData:" (GET method)

`endpoint, user/data, GetUserData, GET`

---

#### `port, port_number`

Specifies the network port the Flask server will listen on.

*   **`port_number`**: e.g., `5000`, `8080` etc.
*   Defaults to `8000` if omitted.

---

### Defining Backend Logic (Labels & `subout`)

Write endpoint logic within labeled blocks ending with `subout`. Logic **must start on the line after** the label.

*   **Labels**: Define the start (e.g., `myEndpoint:`). Matched with `route_or_label_name` in `endpoint,`.
*   **`A_Input`**: Variable holding plain text data from the frontend request body.
*   **Return Value**: **Must** `return` a **string** (the plain text response).
*   **`subout`**: Marks the end of the block.

```htvm
; Example backend logic block
processData:
; Log to server console (optional)
print("Backend received: " . A_Input)
; Leverage Python's string methods directly if needed
; HTVM won't interfere with '.upper()' as it's not HTVM syntax
str processed := A_Input.upper()
str resultString := "Backend processed (uppercase): " . processed
return resultString
subout

```

### Frontend-Backend Interaction (`callBackend`)

In your **frontend** HTVM code (JavaScript GUI), use the `callBackend` function.

*   **`async callBackend(endpointPath, textData, [method='POST'])`**:
    *   Sends plain text `textData` to `endpointPath` using `method`.
    *   **`endpointPath`**: Backend URL path. **Must start with a slash** (e.g., `"/hello"`).
    *   **`textData`**: String data to send.
    *   **`[method='POST']`** (Optional): HTTP method. Match backend definition. Defaults to `'POST'`.
    *   **Returns**: Promise resolving to the plain text response string. Use `await`.
    *   **Throws**: Error on network/server failure.

```htvm
; Example frontend callback (correct multi-line format)
SubmitButton:
str dataToSend := "Info from GUI"
; Send data to the '/processData' endpoint via POST
str responseFromServer := await callBackend("/processData", dataToSend)
await MsgBox("Backend replied: " . responseFromServer)
subout

```

### Example: Simple Backend & Frontend

**1. Backend Code (`backend.htvm`)**

```htvm
; --- Backend Logic ---
hello:
return "Backend received: [" . A_Input . "] - Response: Hello World!"
subout
process:
; Using Python's .upper() method directly on the input string
return "Data processed by backend: " . A_Input.upper()
subout
; --- Backend Setup (using commands with commas) ---
; Optional main label
main
; Route /hello -> label hello (POST default)
endpoint, hello
; Route /processData -> label process, explicitly POST
endpoint, processData, process, POST
; Serve frontend.js at /
fileinit, frontend.js
; Run on port 5678
port, 5678

```

**2. Frontend Code (`frontend.htvm` -> generates `frontend.js`)**

```htvm
; --- OSP Struct for state (Recommended) ---
struct InputState {
    prop str currentText := ""
}
; --- Callbacks ---
; -----------------------
; Default for edit
Edit0:
; No 'global' needed for JS target
InputState.currentText := A_Value
subout
; -----------------------
; Callback for first button
ButtonHello:
str respHello := await callBackend("/hello", InputState.currentText)
; Use SPACE separation for guicontrol
guicontrol id:"responseText" value:respHello
subout
; -----------------------
; Callback for second button
ButtonProcess:
str respProcess := await callBackend("/processData", InputState.currentText)
; Use SPACE separation for guicontrol
guicontrol id:"responseText" value:respProcess
subout
; -----------------------
; --- GUI Setup ---
main
; Prepare string vars only where needed, hardcode simple ones
str placeholderText := "Enter data..."
str btn1Text := "Call Hello"
str btn2Text := "Call Process"
str initialResponse := "Response..."
str editId := "inputEdit"
str helloBtnId := "helloBtn"
str processBtnId := "processBtn"
str responseTextId := "responseText"
str whiteColor := "white"
; Use SPACE separation for GUI options
; Uses Edit0
gui edit id:editId x10 y10 w200 h30 placeholder:placeholderText
gui button id:helloBtnId x10 y50 w95 h30 value:btn1Text callback:ButtonHello
gui button id:processBtnId x115 y50 w95 h30 value:btn2Text callback:ButtonProcess
gui text id:responseTextId x10 y90 w200 h30 value:initialResponse color:whiteColor

```

**To Run:**

1.  **Transpile Backend:** `HTVM backend.htvm HTVM-instructions.txt py`
2.  **Transpile Frontend:** `HTVM frontend.htvm HTVM-instructions.txt js`
3.  **Place Files:** Ensure `frontend.js` is in the same directory as `backend.py`.
4.  **Run Backend:** `python backend.py`
5.  **Access Frontend:** Open browser to `http://localhost:5678`. Interact with the GUI.

---

### Summary

HTVM's backend feature simplifies the creation of basic web servers using **Python and Flask**. By leveraging straightforward commands like `fileinit,`, `endpoint,`, and `port,`, developers can quickly set up routes that map to specific HTVM logic blocks defined by labels. This system facilitates communication between an HTVM JavaScript frontend (using the `callBackend` function) and the Python server, primarily through plain text requests and responses. This functionality provides a streamlined way to add server-side processing capabilities to HTVM projects without requiring extensive backend framework knowledge, aligning with HTVM's philosophy of simplifying development workflows.

---




### Error Handling

[Go back](#htvm-documentation)

Understand how to manage errors and handle exceptions in HTVM to make your programs more robust. HTVM provides simple ways to catch and handle errors, helping you write more stable and reliable code.

### Error Handling in HTVM

Error handling is an essential part of writing robust programs. In HTVM, you can handle errors using the `try`, `catch`, and `finally` keywords, similar to other modern programming languages. This allows you to handle exceptions effectively, ensuring that your program can gracefully recover or manage unexpected situations.

HTVM supports error handling, and even if certain target languages don't fully support `finally`, HTVM ensures that the structure remains intact during conversion. For unsupported features, HTVM provides an easy workaround by using **programming blocks**.

### HTVM Error Handling Syntax

| **HTVM Keyword**         | **Description**                                                                   | **Target Language Syntax**     |
|--------------------------|-----------------------------------------------------------------------------------|--------------------------------|
| `try`                    | Used to define the block of code where errors may occur.                          | `try`                          |
| Error message function   | Used to throw an error message.                                                   | `ErrorMsg("message")`          |
| `catch`                  | Used to catch and handle the error.                                               | `catch`                        |
| `finally`                | Used to define code that runs after `try`, regardless of whether an error occurs. | `finally`                      |

HTVM's error handling syntax is simple and intuitive. You can use `try` and `catch` to handle errors, and `finally` to ensure that some code is always executed at the end of the try block. Here's a quick overview:

```htvm
try {
    ; Your code that might throw an error
    throw ErrorMsg("Something went wrong!")
}
catch (e) {
    ; Handle the error, e contains the error message
    print("Caught error: " . e)
}
finally {
    ; Code that will always execute, regardless of an error
    print("Finally block executed")
}

```

or

```htvm
try {
    ; Your code that might throw an error
    throw ErrorMsg("Something went wrong!")
}
catch (e) {
    ; Handle the error, e contains the error message
    ; Calling the STR() function will convert e to a string since in some languages like C++ it's not a string.
    print("Caught error: " . STR(e))
}
finally {
    ; Code that will always execute, regardless of an error
    print("Finally block executed")
}

```

In the above example, the error message is customizable and should be a string. This allows you to define your own error messages in a way that fits your needs.

### Programming Blocks for Unsupported Features

For languages that do not support traditional error handling structures (such as `finally`), HTVM provides **programming blocks**. These allow you to write directly in the target language’s syntax, enabling you to implement your own error handling solutions or other programming structures. For example, if you're converting your HTVM code to Golang or Lua (which do not support `try`, `catch`, or `finally`), you can use programming blocks to write your custom error handling code in the respective language.

A programming block is a way to insert code directly in the target language, bypassing HTVM's standard syntax when necessary. This gives you full control over how your program handles exceptions and other language-specific behaviors.

### Error Handling Support in Target Languages

| Language     | `try` | `catch` | `finally`    | Notes                                                                                            |
|--------------|-------|---------|--------------|--------------------------------------------------------------------------------------------------|
| C++          | ✅     | ✅       | ❌         | No support for `finally`.                                                                        |
| Python       | ✅     | ✅       | ✅         | Full support for `try`, `catch`, and `finally`.                                                  |
| JavaScript   | ✅     | ✅       | ✅         | Full support for `try`, `catch`, and `finally`.                                                  |
| Go           | ❌     | ❌       | ❌         | No `try-catch-finally` support. Use programming blocks to implement custom error handling.       |
| Lua          | ❌     | ❌       | ❌         | No `try-catch-finally` support. Use programming blocks to implement custom error handling.       |
| C#           | ✅     | ✅       | ✅         | Full support for `try`, `catch`, and `finally`.                                                  |
| Java         | ✅     | ✅       | ✅         | Full support for `try`, `catch`, and `finally`.                                                  |
| Kotlin       | ✅     | ✅       | ✅         | Full support for `try`, `catch`, and `finally`.                                                  |
| Ruby         | ✅     | ✅       | ✅         | Full support for `try`, `catch`, and `finally`.                                                  |
| Nim          | ✅     | ✅       | ✅         | Full support for `try`, `catch`, and `finally`.                                                  |
| AutoHotKey   | ✅     | ✅       | ✅         | Full support for `try`, `catch`, and `finally`.                                                  |
| Swift        | ✅     | ✅       | ❌         | No support for `finally`.                                                                        |
| Dart         | ✅     | ✅       | ✅         | Full support for `try`, `catch`, and `finally`.                                                  |
| TypeScript   | ✅     | ✅       | ✅         | Full support for `try`, `catch`, and `finally`.                                                  |
| Groovy       | ✅     | ✅       | ✅         | Full support for `try`, `catch`, and `finally`.                                                  |

### Notes:

- **Golang and Lua**: These languages don't support traditional `try-catch-finally` blocks. If you try to use HTVM’s error handling in these languages, you will see placeholder strings inserted, which will result in errors. You can instead write custom error handling inside programming blocks in their respective languages.
  
- **C++ and Swift**: The `finally` block is not natively supported, but you can include it in your HTVM code, and HTVM will convert it to an if statement. You can still structure your code in a way that mimics `finally` behavior by ensuring that certain code kinda runs.

```cpp
try {
    // Your code that might throw an error
    throw std::runtime_error("Something went wrong!");
}
catch (const std::exception& e) {
    // Handle the error, e contains the error message
    print("Caught error: " + STR(e.what()));
}
if ("finally dosent exist in c++" == "finally dosent exist in c++") {
    // This simulates a finally block, but it's not guaranteed to behave like one in all cases
    // HTVM may treat this like a finally block, but behavior can vary across targets
    // Intended to run after try/catch, but not a true finally block
    print("Finally block executed");
}
```

```swift
do {
    // Your code that might throw an error
    try ErrorMsg("Something went wrong!")
}
catch let e as NSError {
    // Handle the error, e contains the error message
    print("Caught error: " + e.localizedDescription)
}
if ("finally dosent exist in swift" == "finally dosent exist in swift") {
    // This simulates a finally block, but it's not guaranteed to behave like one in all cases
    // HTVM may treat this like a finally block, but behavior can vary across targets
    // Intended to run after try/catch, but not a true finally block
    print("Finally block executed")
}
```

#### Since `Go` and `Lua` don't support `try-catch-finally`, it will look like this:

```go
GO DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK {
    // Your code that might throw an error
    GO DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK
}
GO DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK {
    // Handle the error, e contains the error message
    print("Caught error: " + STR(e))
}
GO DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK {
    // Code that will always execute, regardless of an error
    print("Finally block executed")
}
```

```lua
LUA DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK
    -- Your code that might throw an error
    LUA DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK
end
LUA DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK
    -- Handle the error, e contains the error message
    print("Caught error: " .. STR(e))
end
LUA DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK
    -- Code that will always execute, regardless of an error
    print("Finally block executed")
end
```

That means you can't use them when converting to `Go` and `Lua`. 

### Catch Block Syntax

The `catch` block syntax in HTVM is simple and flexible. You can write:

```htvm
catch (e) {
    ; Handle the error
}

```

- **e**: This is the error variable, which stores the error message. You can use any variable name here, but `e` is the most common and convenient choice.
- You don't need parentheses around `e` or other variable names, though you can use them if you prefer.

### Important Notes:

- **Error handling behavior across languages**: The behavior of `try`, `catch`, and `finally` blocks may not be exactly the same across all languages. Make sure to thoroughly test your code when converting between different target languages. While HTVM provides support for error handling in many languages, differences in implementation and behavior can arise.

---



### Include

[Go back](#htvm-documentation)

Discover how to include external files and resources in your HTVM project for enhanced functionality. The **include** feature in HTVM allows you to integrate additional code or libraries into your project seamlessly.

### Including Files in HTVM

In HTVM, the `include` keyword allows you to include another HTVM file within your code. This works in a very simple way: just use the `include` keyword followed by a string containing the file path. It's important to remember that this string must be static; you cannot use any operators or dynamic strings.

**Syntax**:

```htvm
include "path/to/file.htvm"

```

The included file will be appended to the top of your code. If there are other includes within the included file, those will be included as well, creating a chain of inclusions. Be careful of nesting too many includes, as it may lead to unexpected behavior.

In most cases, it's a good idea to specify the full file path if possible, though relative paths may work depending on where your files are located.

---

### The Main Label

The `main` keyword in HTVM is a special label used to define the starting point of your program. It is not required to be inside a programming block and can be used freely to mark the beginning of the main code execution.

The `main` keyword serves as a label and does not require any special syntax. You simply place your main code inside the block after the `main` label. When including code from another file, however, make sure that the `main` label appears immediately after any inclusion from other languages.

**Rules**:

- **Before `main`**: You can define functions and include code.
- **After `main`**: You **cannot** define functions—only the main body of your program should follow. While some target languages (like JavaScript) might technically allow nested functions or definitions after the main execution point begins, this is strongly discouraged and disallowed by HTVM's structure to maintain clarity and predictable behavior across conversions.

If you're including code from another language, make sure to remove any pre-existing `main` function from that file before including it. This ensures that the `main` label in HTVM is properly used to start your program's execution.

**Using HTVM without Function Definitions**: If you're using HTVM normally, without defining functions or including code from other languages or files, the `main` label becomes optional as the code execution implicitly starts from the top. But when including functions, HTVM files, or programming blocks with definitions, make sure to follow the structure outlined above (definitions before `main`, main execution logic after `main`) for proper execution.

---

### Using Programming Blocks

HTVM supports including code from other programming languages through programming blocks. To include code from another language, open a programming block and write the import or include statement in the respective syntax for the target language. Then close the block to finish.

**Example (Python)**

If you need to import a library in Python, you can write it like this inside a programming block:

```htvm
___py start
import math
___py end

```

In this case, `math` is a Python library that you can use within your HTVM code. If you want to use a function from the library, you would call it as `math.function_name()`.

**Example (JavaScript)**

For JavaScript, it might look like this:

```htvm
___js start
import { someFunction } from 'someLibrary';
___js end

```

**Example (C++)**

For C++, the inclusion might look like this:

```htvm
___cpp start
#include <iostream>
___cpp end

```

Each programming language has its own syntax for imports or includes, so be sure to use the correct syntax for the target language.

---

### Caching Functions

HTVM allows you to cache functions and reuse them across different projects. This process involves writing your functions in HTVM, converting them to the target language, and then including them in your HTVM code using programming blocks.

#### **Directly Caching Functions Using File Conversion**

One way to cache functions is by directly writing and saving them as separate files. When you convert these files, you can reuse them across your projects without manually importing specific libraries or using function names with prefixes.

Here’s how you can achieve this with Python:

1.  **Write your functions in HTVM**.

```htvm
func int add(int a, int b) {
    return a + b
}

```

2.  **Convert the functions to Python** and remove the `main` function (if applicable) from the converted Python file.

```python
def add(a, b):
    return a + b
```

3.  **Save the Python code as a separate file** (e.g., `functions.py`). This file should not include any `main` function.

4.  **Directly import and use the functions without needing to prefix them with a library name** by following Python's normal import syntax. This means that once the `functions.py` file is in the same directory as your HTVM project, you can import the function directly.

**Example (No library prefix)**:

5.  **If `functions.py` is in the same directory**

This import allows you to directly use `add` in your HTVM code without having to prefix it with the filename or a library name (i.e., no need for `functions.add()`).

Use the function as normal in your HTVM code using the following import:

```htvm
___py start
from functions import add
# Alternatively, to import everything directly (use with caution for namespace clarity):
# from functions import *
___py end
main
; Example call
print(add(2, 3))
; or
add(2, 3).print
; or
add(2, 3).print()
; Showcasing the power of functions called in different ways

```

By following this method, you can write functions in HTVM, convert them to Python (or any other language), and reuse them across different projects while keeping the syntax clean and free of unnecessary library names.

---

#### **Alternative: Inline Caching**

Instead of saving the converted Python (or other language) code to a separate file and importing it, you can directly paste the raw function definitions from the converted output into a programming block within your main HTVM file.

**Example (Python)**:

1.  Convert your HTVM functions (like `add`) to Python.
2.  Copy the resulting Python function definition(s).
3.  Paste them directly into a Python programming block in your main HTVM file:

```htvm
___py start
# Pasted directly from converted output
def add(a, b):
    return a + b
# You can paste multiple functions here
___py end
main
; Now 'add' is defined directly in the Python scope
; No import needed
; Example call
print(add(2, 3))
; or
add(2, 3).print
; or
add(2, 3).print()
; Showcasing the power of functions called in different ways

```

**Trade-offs**:
*   **Pro**: Keeps all code within a single HTVM file, potentially simplifying distribution or editing if you prefer not to manage separate files. No need to re-transpile the function source HTVM if you only modify the main HTVM file.
*   **Con**: Can make the main HTVM file very large and harder to navigate if you have many or complex functions. You lose the modularity of separate files.

Functions defined this way are directly available in the subsequent HTVM code (within the same target language context) without needing any `import` statements or library prefixes.

---

Or just add it as a built-in function if you use it often.
### Adding Built-In Functions

**Description**: Add custom built-in functions to your language by following simple syntax rules.

1.  Open `HTVM-instructions.txt`.
2.  Copy the last function block and paste it at the bottom.
3.  Follow these rules:
    *   **Language Specification**: Use `lang: cpp`, `lang: py`, `lang: js`, `lang: go`, `lang: lua`, `lang: cs`, `lang: java`, `lang: kt`, `lang: rb`, `lang: nim`, `lang: ahk`, `lang: swift`, `lang: dart`, `lang: ts`, or `lang: groovy` to define the language-specific implementation.
    *   **Function Name**: Use `name: functionName`.
    *   **Libraries**: List required libraries with a `|` delimiter. For example:
        *   **C++**: `libs: #include <iostream>|#include <cstdlib>`
        *   **JavaScript (not in a full .html file)**: `libs: import { readFileSync } from 'fs';|import { EventEmitter } from 'events';`
        *   **JavaScript (in a full .html file)**: `libs: <script src="https://cdn.jsdelivr.net/npm/sweetalert2@11"></script>`
        *   **JavaScript (in a full .html file for more than one)**: `libs: <script src="https://cdn.jsdelivr.net/npm/sweetalert2@11"></script>|<script src="myModule.js"></script>`
        *   For other languages, just use the same format. For `Go`, use `libs: )|"theLibName"`. The reason for using `)` is that in HTVM, it doesn't know when the import `()` ends, so we add the `)` as a placeholder. It ensures that the import is correctly handled and will be sorted out at the end. Also, don't worry about including the same lib multiple times, since HTVM will remove duplicates.
    *   **Description**:
        *   Format:
            ```
            description: string~~~[One-line description of the function]~~~Here is how the function looks:~~~```~~~[Function signature]~~~```
            ```
        *   Example:
            ```
            description: string~~~Sort is a function to sort elements based on various criteria like numeric, random, alphabetical order, etc.~~~Here is how the function looks:~~~```~~~Sort(string input, [string options = ""])~~~```
            ```
        Note: The ~~~ delimiters in the description section are placeholders that will be replaced with new lines in the final documentation.

**Here is how a built-in function in HTVM-instructions.txt looks like:**

```
func======================func==============
lang: cpp
name: Sleep
libs: #include <thread>|#include <chrono>
description: system~~~Sleep is a function that pauses execution for a specified number of milliseconds.~~~here is how the func looks like:~~~```~~~Sleep(int milliseconds)~~~```~~~
// Function to sleep for a specified number of milliseconds
void Sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
funcEND======================funcEND==============
```

4.  **ChatGPT Prompt for Function Descriptions:**
    To generate descriptions for functions, use the following ChatGPT prompt to ensure the response follows a specific format:

    **ChatGPT Prompt:**
    ```
    here is what you will do structly so i wil give you a func like something like this it can be in c++ py or js dosnet matter from what it is it what you must do is give me output in this format:

    MAKRE SURE IT SATRST WHIT description: and all in one code block

    description: string~~~StrTitleCase is a func balalbla bla bal~~~here is how the func looks like:~~~```htvm~~~StrTitleCase(string, [optanalName], string, [optanal], string, [optanal], [optanal])~~~```~~~

    it must be ```htvm not ```cpp or others IT MUST BE ```htvm

    all of the ~~~ and all the same format DONT change it only chamge words

    allways start like this description: category_name~~~

    the param dosnet have to be the same name juts a simlpe name no _ pls

    Use square brackets: When you mention the function or describe the parameters, put optional parameters in square brackets [ ]. This is the most common notation for optional parameters. For example:

    functionName(param1, [param2], [param3])
    This means that param2 and param3 are optional.
    Provide a description or note: You can also mention which parameters are optional in a description or a comment, such as:

    "The param2 and param3 parameters are optional."
    "The optional parameters are param2 and param3."
    Default values in code: If the function includes default values for parameters, you can also point this out. For example:

    functionName(param1, param2 = "default", param3 = 10)
    This means that param2 and param3 have default values and are optional.

    YOU MUST SPECIFY THE TYPE AS WELL like this

    funcName(int asd, str, waeds, bool, waedsf, arr str, waesdf, bool [awsesrs = false], bool [awsesrs = true])

    YOU MUST SPECIFY THE TYPE EVEN IF YOU DONT KNOW TRY TO GUESS HERE IS THE TYPE SYNTAX
    str
    int
    bool
    arr str
    func
    ... otherwize made them up

    respond in a ```txt all in one line

    so the ~~~ = to a new line ok ~~~ is a new line and the first one where we typed string is the category and it must alwas be one word the bets word for thet category like string math gui io files bla...
    THE description BUST BE ONLY IN ONE LINE
    here is func and replay in one line:
    ================================================

    // Function to sleep for a specified number of milliseconds
    void Sleep(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    ```

Open it in a text editor and make sure the response is in 1 line. Otherwise, if ChatGPT replies in more than one line, tell it:

```txt
I SAID REPLY IN ONE LINE
```

**Important**: Do not modify the first 162 lines of `HTVM-instructions.txt`.

---

### Important Notes on Library Usage and Conversions

HTVM is flexible, but there are some important things to keep in mind when working with external libraries or converting code between languages.

#### **Converting Libraries Between Languages**:

- You cannot use a Python library and convert it to JavaScript or any other languages. When including libraries, ensure that they are compatible with the target language. For example, if you want to use the `NumPy` library in Python, you cannot convert your code to JavaScript or C++ because the `NumPy` library won't work in those languages.

#### **Library-Specific Syntax**:

- When including libraries in HTVM, you’ll need to follow the target language's syntax. For example, if you're using Python libraries, you'll have to call them in Python syntax, such as `library_name.function_name()`. This can be cumbersome but is necessary for cross-language compatibility.

#### **Using HTVM Syntax with Other Languages**:

- You can use HTVM to emulate the syntax of another language, such as Lua, while still utilizing Python libraries like Pygame. However, this comes with some limitations—HTVM will allow you to write in a Lua-like style, but the built-in functions will remain HTVM functions, and not all features of the target language will be available.

---

### Final Considerations

- After using the `include` keyword, always ensure that the `main` label is placed underneath any includes or programming blocks containing definitions. **Do not** define functions after the `main` label in your HTVM code. While some target languages (like JavaScript) might technically allow nested functions after the main execution point, this is strongly discouraged and disallowed by HTVM's structure for clarity and predictable behavior.

- When including code from other languages that HTVM has converted, remove their `main` function to avoid conflicts. This is crucial for the proper execution of the HTVM program.

- If you frequently reuse the same set of functions across many projects (especially functions converted from HTVM or native language code), consider adding them as custom built-in functions by editing `HTVM-instructions.txt` (as described in the "Adding Built-In Functions" section) instead of repeatedly using `include` or inline caching via programming blocks. This can centralize your common utilities.

---



### Commands

[Go back](#htvm-documentation)

Commands in HTVM are a simplified way to perform actions, similar to functions, but with a more compact, direct, and concise syntax for better efficiency. Commands help streamline your code and reduce unnecessary complexity.

### Commands in HTVM

**What is a Command?**  
In HTVM, commands are simple, intuitive building blocks that you use to perform actions in your code. They are inspired by AutoHotKey commands, but in HTVM, they automatically convert into function calls, making the process seamless. These commands are designed to be straightforward and concise, so you don’t need to worry about the underlying complexity of function definitions. When you write a command, HTVM handles converting it into an appropriate function call behind the scenes, allowing you to focus on logic rather than syntax.

Each command can accept one or more parameters, depending on its functionality, and follows a consistent format for easy readability and use.

### Structure of a Command  
A basic command looks like this:

```htvm
command, parameter1, parameter2, ...
```

Commands support multiple parameters and follow a simple, comma-separated format. Behind the scenes, these commands are transformed into corresponding function calls, which execute the desired actions with minimal keystrokes.

**⚠️ Disclaimer:**  
This command syntax is structured and follows a defined format: a command name followed by a comma, then a space, then the next value, and so on — like `text, text, text`. It is different from how GUI definitions work in HTVM. GUI syntax is far more flexible and allows you to do insane stuff, while commands follow this more controlled, predictable pattern.

#### Rules

We can have `OUTVAR` which means it will be `OUTVAR = funcName(...)`
So if we have `commandName, OUTVAR, someParam` that will equal `OUTVAR = commandName(someParam)` 

If we have `INVAR` which means it will be `funcName(INVAR ...)`
So if we have `commandName, INVAR, someParam` that will equal `commandName(INVAR, someParam)` 

If we have `INOUTVAR` which means it will be `INOUTVAR = funcName(INOUTVAR ...)`
So if we have `commandName, INOUTVAR, someParam` that will equal `INOUTVAR = commandName(INOUTVAR, someParam)` 

If we have `'` which means it will be `funcName(someParam ...)`
So if we have `commandName, someParam` that will equal `commandName("someParam")` 
Basically, it means it will wrap it in double quotes ("").

If we have `lineTranspile` it means it will do a replace.  
So if we have `someText, lineTranspile, replacementText`,  
that means if you put on a single line alone: `someText`,  
that will simply be replaced with `replacementText`.  
And if we have ~~~ in the replacement, it will be replaced with actual new lines.

Example:
If we define `greetUser, lineTranspile, print("Hello!")~~~print("Welcome to HTVM.")`  
Then this:

```htvm
greetUser
```

Will become:

```htvm
print("Hello!")
print("Welcome to HTVM.")
```

> ⚠️ **Important**: You **cannot** use the following characters inside commands: `,` `|` `%` — these are reserved and will break the parsing.

> If we have `'`, it means the param will be wrapped in double quotes. You **don’t actually type `'` in your code** — it’s just used here in the command definition to mark that param.

### Available Commands  
Here are all the available commands in this HTVM language:



```htvm
StringTrimLeft, OUTVAR, INVAR, param1
```



```htvm
StringTrimRight, OUTVAR, INVAR, param1
```



```htvm
Random, OUTVAR, param1, param2
```



```htvm
Sleep, INVAR
```



```htvm
FileRead, OUTVAR, 'param1
```



```htvm
FileAppend, INVAR, 'param1
```



```htvm
FileDelete, 'INVAR
```



```htvm
Sort, INOUTVAR, 'param1
```



```htvm
MsgBox, 'param1
```



This was all of them.

### Customizing Commands in HTVM  
You can configure and customize the syntax of commands—along with the rest of your HTVM language—on the [HTVM Syntax Configurator website](#https://themaster1127.github.io/HTVM/web-ui/). That’s where you define how your custom HTVM language behaves, including how commands are recognized and structured.

### Summary  
This is a comprehensive guide to the commands in HTVM. With the goal of reducing keystrokes and inspired by AutoHotKey, HTVM provides an intuitive way to program with less effort.  
To configure and customize your HTVM language, visit the [HTVM Syntax Configurator website](#https://themaster1127.github.io/HTVM/web-ui/). There you can adjust the commands, see how to define them, and other elements to create your own language and fit your coding needs.

### HTVM Philosophy  
HTVM is built on the idea of simplifying the coding experience through **minimal keystrokes**. It’s not about being lazy—it’s about being efficient. Traditional programming languages often burden the developer with excessive syntax, repetitive structures, and unnecessary complexity.

HTVM flips that by giving you clean, readable code that does more with less. While some may argue that AI can write code for you, HTVM emphasizes control and creativity—two things that get lost when you offload everything to an AI. Besides, coding is fun. You should be able to enjoy it without the clutter.  

HTVM is trying to make you code with **fewer keystrokes**. Commands are a direct reflection of this philosophy—they let you express complex logic in just a few words, automatically converting into efficient function calls with minimal effort.

---





### All Syntax

[Go back](#htvm-documentation)

#### Here is all of the syntax in this language:

| kewWordName                                   | Syntax                               |
|-----------------------------------------------|-----------------------------------|
|  langToConvertTo  | cpp        |
|  langFileExtension  | htvm        |
|  commands  | StringTrimLeft,OUTVAR,INVAR,param1 &#124; StringTrimRight,OUTVAR,INVAR,param1 &#124; Random,OUTVAR,param1,param2 &#124; Sleep,INVAR &#124; FileRead,OUTVAR,'param1 &#124; FileAppend,INVAR,'param1 &#124; FileDelete,'INVAR &#124; Sort,INOUTVAR,'param1 &#124; MsgBox,'param1        |
|  keyWordAlliance  | alliance        |
|  keyWordCrew  | crew        |
|  keyWordProc  | proc        |
|  keyWordStruct  | struct        |
|  keyWordProp  | prop        |
|  keyWordThis  | this        |
|  keyWordInclude  | include        |
|  keyWordCodeInTheTranspiledLangStart  | ___start        |
|  keyWordCodeInTheTranspiledLangEnd  | ___end        |
|  keyWordCodeInTheTranspiledLangStartCPP  | ___cpp start        |
|  keyWordCodeInTheTranspiledLangEndCPP  | ___cpp end        |
|  keyWordCodeInTheTranspiledLangStartPY  | ___py start        |
|  keyWordCodeInTheTranspiledLangEndPY  | ___py end        |
|  keyWordCodeInTheTranspiledLangStartJS  | ___js start        |
|  keyWordCodeInTheTranspiledLangEndJS  | ___js end        |
|  keyWordCodeInTheTranspiledLangStartGO  | ___go start        |
|  keyWordCodeInTheTranspiledLangEndGO  | ___go end        |
|  keyWordCodeInTheTranspiledLangStartLUA  | ___lua start        |
|  keyWordCodeInTheTranspiledLangEndLUA  | ___lua end        |
|  keyWordCodeInTheTranspiledLangStartCS  | ___cs start        |
|  keyWordCodeInTheTranspiledLangEndCS  | ___cs end        |
|  keyWordCodeInTheTranspiledLangStartJAVA  | ___java start        |
|  keyWordCodeInTheTranspiledLangEndJAVA  | ___java end        |
|  keyWordCodeInTheTranspiledLangStartKT  | ___kt start        |
|  keyWordCodeInTheTranspiledLangEndKT  | ___kt end        |
|  keyWordCodeInTheTranspiledLangStartRB  | ___rb start        |
|  keyWordCodeInTheTranspiledLangEndRB  | ___rb end        |
|  keyWordCodeInTheTranspiledLangStartNIM  | ___nim start        |
|  keyWordCodeInTheTranspiledLangEndNIM  | ___nim end        |
|  keyWordCodeInTheTranspiledLangStartAHK  | ___ahk start        |
|  keyWordCodeInTheTranspiledLangEndAHK  | ___ahk end        |
|  keyWordCodeInTheTranspiledLangStartSWIFT  | ___swift start        |
|  keyWordCodeInTheTranspiledLangEndSWIFT  | ___swift end        |
|  keyWordCodeInTheTranspiledLangStartDART  | ___dart start        |
|  keyWordCodeInTheTranspiledLangEndDART  | ___dart end        |
|  keyWordCodeInTheTranspiledLangStartTS  | ___ts start        |
|  keyWordCodeInTheTranspiledLangEndTS  | ___ts end        |
|  keyWordCodeInTheTranspiledLangStartGROOVY  | ___groovy start        |
|  keyWordCodeInTheTranspiledLangEndGROOVY  | ___groovy end        |
|  keyWordCodeInTheTranspiledLangStartHTVM  | ___htvm start        |
|  keyWordCodeInTheTranspiledLangEndHTVM  | ___htvm end        |
|  keyWordCodeInHTVMstart  | ___inhtvm start        |
|  keyWordCodeInHTVMend  | ___inhtvm end        |
|  keyWordCurlyBraceOpen  | {        |
|  keyWordCurlyBraceClose  | }        |
|  keyWordNull  | null        |
|  keyWordTrue  | true        |
|  keyWordFalse  | false        |
|  keyWordVoid  | void        |
|  keyWordDouble  | double        |
|  keyWordChar  | char        |
|  keyWordUint8  | uint8        |
|  keyWordUint16  | uint16        |
|  keyWordUint32  | uint32        |
|  keyWordUint64  | uint64        |
|  keyWordINT  | int        |
|  keyWordSTR  | str        |
|  keyWordBOOL  | bool        |
|  keyWordFLOAT  | float        |
|  keyWordINT8  | int8        |
|  keyWordINT16  | int16        |
|  keyWordINT32  | int32        |
|  keyWordINT64  | int64        |
|  keyWordIF  | if        |
|  keyWordElseIf  | else if        |
|  keyWordElse  | else        |
|  keyWordWhileLoop  | while        |
|  keyWordLoopInfinite  | Loop        |
|  keyWordLoop  | Loop,        |
|  keyWordLoopParse  | Loop, Parse,        |
|  keyWordContinue  | continue        |
|  keyWordBreak  | break        |
|  keyWordFunc  | func        |
|  keyWordAwait  | await        |
|  keyWordAsync  | async        |
|  keyWordThrow  | throw        |
|  keyWordErrorMsg  | ErrorMsg        |
|  keyWordTry  | try        |
|  keyWordCatch  | catch        |
|  keyWordFinally  | finally        |
|  keyWordReturnStatement  | return        |
|  keyWordArrayAppend  | .add        |
|  keyWordArrayPop  | .pop        |
|  keyWordArraySize  | .size        |
|  keyWordArrayInsert  | .insert        |
|  keyWordArrayRemove  | .rm        |
|  keyWordArrayIndexOf  | .indexOf        |
|  keyWordArrayDefinition  | arr        |
|  keyWordArrayOfIntegersDefinition  | arr int        |
|  keyWordArrayOfStringsDefinition  | arr str        |
|  keyWordArrayOfFloatingPointNumbersDefinition  | arr float        |
|  keyWordArrayOfBooleansDefinition  | arr bool        |
|  keyWordVar  | var        |
|  keyWordLet  | let        |
|  keyWordConst  | const        |
|  keyWordEnd  | end        |
|  keyWordGlobal  | global        |
|  keyWordComment  | ;        |
|  keyWordCommentOpenMultiLine  | &#39;&#39;&#39;1        |
|  keyWordCommentCloseMultiLine  | &#39;&#39;&#39;2        |
|  keyWordEscpaeChar  | `        |
|  keyWordMainLabel  | main        |
|  keyWordConcat  | .        |
|  keyWordAdd  | +        |
|  keyWordSub  | -        |
|  keyWordMul  | *        |
|  keyWordDiv  | /        |
|  keyWordMod  | %        |
|  keyWordExp  | **        |
|  keyWordEqual  | =        |
|  keyWordStrictEqual  | ===        |
|  keyWordNotEqual  | !=        |
|  keyWordGreater  | &gt;        |
|  keyWordLess  | &lt;        |
|  keyWordGreaterEqual  | &gt;=        |
|  keyWordLessEqual  | &lt;=        |
|  keyWordAnd  | and        |
|  keyWordOr  | or        |
|  keyWordNot  | !        |
|  keyWordBitAnd  | &amp;        |
|  keyWordBitOr  | &#124;        |
|  keyWordBitXor  | ^        |
|  keyWordBitNot  | ~        |
|  keyWordShiftLeft  | &lt;&lt;        |
|  keyWordShiftRight  | &gt;&gt;        |
|  keyWordShiftUnsignedRight  | &gt;&gt;&gt;        |
|  keyWordAssign  | :=        |
|  keyWordAssignAdd  | +=        |
|  keyWordAssignConcat  | .=        |
|  keyWordAssignSub  | -=        |
|  keyWordAssignMul  | *=        |
|  keyWordAssignDiv  | /=        |
|  keyWordAssignMod  | %=        |
|  keyWordAssignShiftLeft  | &lt;&lt;=        |
|  keyWordAssignShiftRight  | &gt;&gt;=        |
|  keyWordLogicalAssignShiftRight  | &gt;&gt;&gt;=        |
|  keyWordAssignBitAnd  | &amp;=        |
|  keyWordAssignBitOr  | &#124;=        |
|  keyWordAssignBitXor  | ^=        |
|  keyWordTernary1  | ?        |
|  keyWordTernary2  | :        |
|  keyWordInc  | ++        |
|  keyWordDec  | --        |
|  AHKlikeLoopsIndexedAt  | 0        |
|  keyWordAIndex  | A_Index        |
|  keyWordALoopField  | A_LoopField        |
|  useCurlyBraces  | on        |
|  useEnd  | off        |
|  useSemicolon  | off        |
|  useParentheses  | on        |
|  usePrefixTypeForTypeDefinition  | on        |
|  usePostfixTypeForTypeDefinition  | off        |
|  usePythonicColonSyntax  | off        |
|  useCurlyBracesSyntaxForArrayDef  | off        |
|  useInJavaScriptAlwaysUseVar  | on        |
|  useJavaScriptInAfullHTMLfile  | off        |
|  useJavaScriptAmainFuncDef  | on        |
|  useJavaScriptAllFuncsAreAsync  | off        |
|  useJavaScriptAlwaysTripleEqual  | off        |


---


## Built-in Functions  

[Go back](#htvm-documentation) 

HTVM includes a variety of built-in functions organized into categories for convenience.

1. [Math Functions](#math-functions)
2. [String Functions](#string-functions)
3. [System Functions](#system-functions)
4. [File Functions](#file-functions)
5. [Io Functions](#io-functions)
6. [Other Functions](#other-functions)
7. [Gui Functions](#gui-functions)
8. [Backend Functions](#backend-functions)

---

## Math Functions

[Go back](#built-in-functions)

1. [ACos](#acos)
2. [ASin](#asin)
3. [ATan](#atan)
4. [Abs](#abs)
5. [Ceil](#ceil)
6. [Cos](#cos)
7. [Exp](#exp)
8. [Floor](#floor)
9. [Ln](#ln)
10. [Log](#log)
11. [Mod](#mod)
12. [Random](#random)
13. [Round](#round)
14. [Sin](#sin)
15. [Sqrt](#sqrt)
16. [Tan](#tan)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ACos | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| ASin | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| ATan | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Abs | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Ceil | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Cos | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Exp | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Floor | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Ln | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Log | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Mod | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Random | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Round | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Sin | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Sqrt | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Tan | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

---

### ACos

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ACos | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Calculates the arc cosine (inverse cosine) of a number. The input must be between -1 and 1, inclusive. The result is in radians.

Here is how to use it:

```htvm
float val1 := 0.5
float result1 := ACos(val1)
; Expected: approx 1.04719755
print("ACos(0.5) = " . STR(result1))
if (Abs(result1 - 1.04719755) > 0.00001) {
    print("ACos test 1 FAILED!")
}
; ----------------------------------------------------
float val2 := -1.0
float result2 := ACos(val2)
; Expected: approx 3.14159265 (pi)
print("ACos(-1.0) = " . STR(result2))
if (Abs(result2 - 3.14159265) > 0.00001) {
    print("ACos test 2 FAILED!")
}
; ----------------------------------------------------
; Example of an invalid input (behavior might vary by target language: error or NaN)
float val3 := 2.0
; This would typically result in NaN or an error
float result3 := ACos(val3)
print("ACos(2.0) = " . STR(result3))
```


---
### ASin

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ASin | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Calculates the arc sine (inverse sine) of a number. The input must be between -1 and 1, inclusive. The result is in radians.

Here is how to use it:

```htvm
float val1 := 0.5
float result1 := ASin(val1)
; Expected: approx 0.52359877
print("ASin(0.5) = " . STR(result1))
if (Abs(result1 - 0.52359877) > 0.00001) {
    print("ASin test 1 FAILED!")
}
; ----------------------------------------------------
float val2 := -1.0
float result2 := ASin(val2)
; Expected: approx -1.57079632 ( -pi / 2)
print("ASin(-1.0) = " . STR(result2))
if (Abs(result2 - (-1.57079632)) > 0.00001) {
    print("ASin test 2 FAILED!")
}
; ----------------------------------------------------
; Example of an invalid input (behavior might vary: error or NaN)
float val3 := 1.5
float result3 := ASin(val3)
print("ASin(1.5) = " . STR(result3))
```


---
### ATan

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ATan | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Calculates the arc tangent (inverse tangent) of a number. The result is in radians, ranging from -PI/2 to PI/2.

Here is how to use it:

```htvm
float val1 := 1.0
float result1 := ATan(val1)
; Expected: approx 0.78539816 (pi / 4)
print("ATan(1.0) = " . STR(result1))
if (Abs(result1 - 0.78539816) > 0.00001) {
    print("ATan test 1 FAILED!")
}
; ----------------------------------------------------
float val2 := 0.0
float result2 := ATan(val2)
; Expected: 0.0
print("ATan(0.0) = " . STR(result2))
if (Abs(result2 - 0.0) > 0.00001) {
    print("ATan test 2 FAILED!")
}
; ----------------------------------------------------
float val3 := -1.0
float result3 := ATan(val3)
; Expected: approx -0.78539816 (-pi / 4)
print("ATan(-1.0) = " . STR(result3))
if (Abs(result3 - (-0.78539816)) > 0.00001) {
    print("ATan test 3 FAILED!")
}
```


---
### Abs

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Abs | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Returns the absolute (non-negative) value of a number. For example, Abs(-5) is 5, and Abs(5) is 5.

Here is how to use it:

```htvm
float num1 := -10.5
float abs1 := Abs(num1)
; Expected: 10.5
print("Abs(-10.5) = " . STR(abs1))
if (abs1 != 10.5) {
    print("Abs test 1 FAILED!")
}
; ----------------------------------------------------
int num2 := 7
int abs2 := Abs(num2)
; Expected: 7
print("Abs(7) = " . STR(abs2))
if (abs2 != 7) {
    print("Abs test 2 FAILED!")
}
; ----------------------------------------------------
float num3 := 0.0
float abs3 := Abs(num3)
; Expected: 0.0
print("Abs(0.0) = " . STR(abs3))
if (abs3 != 0.0) {
    print("Abs test 3 FAILED!")
}
```


---
### Ceil

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Ceil | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Returns the smallest integer greater than or equal to the given number (rounds up to the nearest integer). For example, Ceil(4.2) is 5, and Ceil(-4.8) is -4.

Here is how to use it:

```htvm
float num1 := 4.2
float ceil1 := Ceil(num1)
; Expected: 5.0 (or 5 depending on language float/int conversion)
print("Ceil(4.2) = " . STR(ceil1))
if (ceil1 != 5.0) {
    print("Ceil test 1 FAILED!")
}
; ----------------------------------------------------
float num2 := -4.8
float ceil2 := Ceil(num2)
; Expected: -4.0
print("Ceil(-4.8) = " . STR(ceil2))
if (ceil2 != -4.0) {
    print("Ceil test 2 FAILED!")
}
; ----------------------------------------------------
float num3 := 7.0
float ceil3 := Ceil(num3)
; Expected: 7.0
print("Ceil(7.0) = " . STR(ceil3))
if (ceil3 != 7.0) {
    print("Ceil test 3 FAILED!")
}
```


---
### Cos

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Cos | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Calculates the cosine of an angle. The input angle must be in radians.

Here is how to use it:

```htvm
float pi := 3.1415926535
float angle1 := 0.0
float result1 := Cos(angle1)
; Expected: 1.0
print("Cos(0.0) = " . STR(result1))
if (Abs(result1 - 1.0) > 0.00001) {
    print("Cos test 1 FAILED!")
}
; ----------------------------------------------------
float angle2 := pi / 2.0
; 90 degrees
float result2 := Cos(angle2)
; Expected: approx 0.0
print("Cos(pi/2) = " . STR(result2))
if (Abs(result2 - 0.0) > 0.00001) {
    print("Cos test 2 FAILED!")
}
; ----------------------------------------------------
float angle3 := pi
; 180 degrees
float result3 := Cos(angle3)
; Expected: -1.0
print("Cos(pi) = " . STR(result3))
if (Abs(result3 - (-1.0)) > 0.00001) {
    print("Cos test 3 FAILED!")
}
```


---
### Exp

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Exp | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Calculates Euler's number 'e' (approx. 2.71828) raised to the power of the given number. Exp(1) is 'e', Exp(0) is 1.

Here is how to use it:

```htvm
float num1 := 1.0
float result1 := Exp(num1)
; Expected: approx 2.71828
print("Exp(1.0) = " . STR(result1))
if (Abs(result1 - 2.71828) > 0.00001) {
    print("Exp test 1 FAILED!")
}
; ----------------------------------------------------
float num2 := 0.0
float result2 := Exp(num2)
; Expected: 1.0
print("Exp(0.0) = " . STR(result2))
if (Abs(result2 - 1.0) > 0.00001) {
    print("Exp test 2 FAILED!")
}
; ----------------------------------------------------
float num3 := 2.0
float result3 := Exp(num3)
; Expected: approx 7.38905 (e*e)
print("Exp(2.0) = " . STR(result3))
if (Abs(result3 - 7.389056) > 0.00001) {
    print("Exp test 3 FAILED!")
}
```


---
### Floor

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Floor | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Returns the largest integer less than or equal to the given number (rounds down to the nearest integer). For example, Floor(4.8) is 4, and Floor(-4.2) is -5.

Here is how to use it:

```htvm
float num1 := 4.8
float floor1 := Floor(num1)
; Expected: 4.0 (or 4)
print("Floor(4.8) = " . STR(floor1))
if (floor1 != 4.0) {
    print("Floor test 1 FAILED!")
}
; ----------------------------------------------------
float num2 := -4.2
float floor2 := Floor(num2)
; Expected: -5.0
print("Floor(-4.2) = " . STR(floor2))
if (floor2 != -5.0) {
    print("Floor test 2 FAILED!")
}
; ----------------------------------------------------
float num3 := 7.0
float floor3 := Floor(num3)
; Expected: 7.0
print("Floor(7.0) = " . STR(floor3))
if (floor3 != 7.0) {
    print("Floor test 3 FAILED!")
}
```


---
### Ln

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Ln | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Calculates the natural logarithm (logarithm base 'e') of a number. The input must be a positive number.

Here is how to use it:

```htvm
float e_approx := 2.718281828
float val1 := e_approx
float result1 := Ln(val1)
; Expected: approx 1.0
print("Ln(e) = " . STR(result1))
if (Abs(result1 - 1.0) > 0.00001) {
    print("Ln test 1 FAILED!")
}
; ----------------------------------------------------
float val2 := 1.0
float result2 := Ln(val2)
; Expected: 0.0
print("Ln(1.0) = " . STR(result2))
if (Abs(result2 - 0.0) > 0.00001) {
    print("Ln test 2 FAILED!")
}
; ----------------------------------------------------
float val3 := 10.0
float result3 := Ln(val3)
; Expected: approx 2.302585
print("Ln(10.0) = " . STR(result3))
if (Abs(result3 - 2.302585) > 0.00001) {
    print("Ln test 3 FAILED!")
}
; ----------------------------------------------------
; Invalid input (0 or negative) would typically cause an error or return NaN/Infinity
float val4 := 0.0
print("Ln(0.0) = " . STR(Ln(val4)))
```


---
### Log

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Log | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Calculates the base-10 logarithm of a number. The input must be a positive number.

Here is how to use it:

```htvm
float val1 := 100.0
float result1 := Log(val1)
; Expected: 2.0
print("Log(100.0) = " . STR(result1))
if (Abs(result1 - 2.0) > 0.00001) {
    print("Log test 1 FAILED!")
}
; ----------------------------------------------------
float val2 := 1.0
float result2 := Log(val2)
; Expected: 0.0
print("Log(1.0) = " . STR(result2))
if (Abs(result2 - 0.0) > 0.00001) {
    print("Log test 2 FAILED!")
}
; ----------------------------------------------------
float val3 := 10000.0
float result3 := Log(val3)
; Expected: 4.0
print("Log(10000.0) = " . STR(result3))
if (Abs(result3 - 4.0) > 0.00001) {
    print("Log test 3 FAILED!")
}
; ----------------------------------------------------
; Invalid input (0 or negative) would typically cause an error or return NaN/Infinity
float val4 := 0.0
print("Log(0.0) = " . STR(Log(val4)))
```


---
### Mod

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Mod | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Calculates the modulus (remainder of a division) of two numbers: `dividend` Mod `divisor`. For example, `10 Mod 3` is 1. The modulus operation gives the remainder after division. Also in HTVM, you can still use the **modular operator** to calculate the remainder of a division.

Here is how to use it:

```htvm
; Test 1: Modulus with positive numbers
int dividend1 := 10
int divisor1 := 3
int result1 := Mod(dividend1, divisor1)
; Expected: 1
print("10 Mod 3 = " . STR(result1))
if (result1 != 1) {
    print("Mod test 1 FAILED!")
}
; ----------------------------------------------------
; Test 2: Modulus with larger dividend
int dividend2 := 17
int divisor2 := 5
int result2 := Mod(dividend2, divisor2)
; Expected: 2
print("17 Mod 5 = " . STR(result2))
if (result2 != 2) {
    print("Mod test 2 FAILED!")
}
; ----------------------------------------------------
; Test 3: Modulus with a negative dividend
int dividend3 := -10
int divisor3 := 3
int result3 := Mod(dividend3, divisor3)
; Note: Result with negative numbers can vary by language. Common result: -1 or 2
; For this test, let's assume a common behavior, but be aware it might differ.
print("Mod test 3 result for -10 Mod 3: " . STR(result3))
; ----------------------------------------------------
; Test 4: Modulus with a negative divisor
int dividend4 := 10
int divisor4 := -3
int result4 := Mod(dividend4, divisor4)
; Common result: 1 or -2
print("Mod test 4 result for 10 Mod -3: " . STR(result4))
; ----------------------------------------------------
; IMPORTANT: You can also use the modular operator like this:
int result1_percent := dividend1 % divisor1
; Expected: 1
print("10 % 3 = " . STR(result1_percent))
if (result1_percent != 1) {
    print("Percent Mod test 1 FAILED!")
}
; ----------------------------------------------------
int result2_percent := dividend2 % divisor2
; Expected: 2
print("17 % 5 = " . STR(result2_percent))
if (result2_percent != 2) {
    print("Percent Mod test 2 FAILED!")
}
; ----------------------------------------------------
int result3_percent := dividend3 % divisor3
; Common result: -1 or 2
print("Percent Mod test 3 result for -10 % 3: " . STR(result3_percent))
; ----------------------------------------------------
int result4_percent := dividend4 % divisor4
; Common result: 1 or -2
print("Percent Mod test 4 result for 10 % -3: " . STR(result4_percent))
; ----------------------------------------------------
; ----------------------------------------------------
; Even or Odd Number Check in a Loop (0 to 4)
; This loop checks if the numbers from 0 to 4 are even or odd
; This can be very useful in various scenarios
; ----------------------------------------------------
; Loop from 0 to 4
Loop, 5 {
    ; Check if the current index is even or odd
    if (A_Index % 2 = 0) {
        print(STR(A_Index) . " is even")
    }
    else {
        print(STR(A_Index) . " is odd")
    }
}
```


---
### Random

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Random | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Generates a pseudo-random integer between `min` and `max` (inclusive). Both `min` and `max` must be integers.

Here is how to use it:

```htvm
int minVal := 1
int maxVal := 10
Loop, 5 {
    int randNum := Random(minVal, maxVal)
    print("Random number between " . STR(minVal) . " and " . STR(maxVal) . ": " . STR(randNum))
    if (randNum < minVal or randNum > maxVal) {
        print("Random test FAILED! Number out of range: " . STR(randNum))
    }
}
print("--------------------")
; ----------------------------------------------------
int specificMin := 5
int specificMax := 5
int specificRand := Random(specificMin, specificMax)
print("Random number between 5 and 5: " . STR(specificRand))
; Expected: 5
if (specificRand != 5) {
    print("Random specific range test FAILED!")
}
```


---
### Round

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Round | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Rounds a number to the nearest integer. Numbers ending in .5 are typically rounded up (away from zero).

Here is how to use it:

```htvm
float num1 := 4.2
float round1 := Round(num1)
; Expected: 4.0 (or 4)
print("Round(4.2) = " . STR(round1))
if (round1 != 4.0) {
    print("Round test 1 FAILED!")
}
; ----------------------------------------------------
float num2 := 4.8
float round2 := Round(num2)
; Expected: 5.0
print("Round(4.8) = " . STR(round2))
if (round2 != 5.0) {
    print("Round test 2 FAILED!")
}
; ----------------------------------------------------
float num3 := 4.5
float round3 := Round(num3)
; Expected: 5.0 (common rounding rule)
print("Round(4.5) = " . STR(round3))
if (round3 != 5.0) {
    print("Round test 3 FAILED!")
}
; ----------------------------------------------------
float num4 := -4.5
float round4 := Round(num4)
; Expected: -5.0 (common rounding away from zero for .5) or -4.0 (round half to even)
; This behavior can vary, so the test is lenient.
print("Round(-4.5) result: " . STR(round4))
if (round4 != -4.0 and round4 != -5.0) {
    print("Round test 4 FAILED!")
}
```


---
### Sin

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Sin | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Calculates the sine of an angle. The input angle must be in radians.

Here is how to use it:

```htvm
float pi := 3.1415926535
float angle1 := 0.0
float result1 := Sin(angle1)
print("Sin(0.0) = " . STR(result1))
; Expected: 0.0
if (Abs(result1 - 0.0) > 0.00001) {
    print("Sin test 1 FAILED!")
}
; ----------------------------------------------------
float angle2 := pi / 2.0
; 90 degrees
float result2 := Sin(angle2)
print("Sin(pi/2) = " . STR(result2))
; Expected: 1.0
if (Abs(result2 - 1.0) > 0.00001) {
    print("Sin test 2 FAILED!")
}
; ----------------------------------------------------
float angle3 := pi
; 180 degrees
float result3 := Sin(angle3)
print("Sin(pi) = " . STR(result3))
; Expected: approx 0.0
if (Abs(result3 - 0.0) > 0.00001) {
    print("Sin test 3 FAILED!")
}
```


---
### Sqrt

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Sqrt | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Calculates the square root of a non-negative number. Inputting a negative number will typically result in NaN or an error.

Here is how to use it:

```htvm
float num1 := 9.0
float sqrt1 := Sqrt(num1)
print("Sqrt(9.0) = " . STR(sqrt1))
; Expected: 3.0
if (Abs(sqrt1 - 3.0) > 0.00001) {
    print("Sqrt test 1 FAILED!")
}
; ----------------------------------------------------
float num2 := 2.0
float sqrt2 := Sqrt(num2)
print("Sqrt(2.0) = " . STR(sqrt2))
; Expected: approx 1.41421356
if (Abs(sqrt2 - 1.41421356) > 0.00001) {
    print("Sqrt test 2 FAILED!")
}
; ----------------------------------------------------
float num3 := 0.0
float sqrt3 := Sqrt(num3)
print("Sqrt(0.0) = " . STR(sqrt3))
; Expected: 0.0
if (Abs(sqrt3 - 0.0) > 0.00001) {
    print("Sqrt test 3 FAILED!")
}
; ----------------------------------------------------
; Example of invalid input (behavior might vary: error or NaN)
float num4 := -4.0
float sqrt4 := Sqrt(num4)
print("Sqrt(-4.0) = " . STR(sqrt4))
```


---
### Tan

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Tan | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Calculates the tangent of an angle. The input angle must be in radians.

Here is how to use it:

```htvm
float pi := 3.1415926535
float angle1 := 0.0
float result1 := Tan(angle1)
print("Tan(0.0) = " . STR(result1))
; Expected: 0.0
if (Abs(result1 - 0.0) > 0.00001) {
    print("Tan test 1 FAILED!")
}
; ----------------------------------------------------
; 45 degrees
float angle2 := pi / 4.0
float result2 := Tan(angle2)
print("Tan(pi/4) = " . STR(result2))
; Expected: approx 1.0
if (Abs(result2 - 1.0) > 0.00001) {
    print("Tan test 2 FAILED!")
}
; ----------------------------------------------------
; Tan(pi/2) is undefined (approaches infinity). Behavior might vary.
float angle3 := pi / 2.0
float result3 := Tan(angle3)
print("Tan(pi/2) = " . STR(result3))
```


---
## String Functions

[Go back](#built-in-functions)

1. [Asc](#asc)
2. [Chr](#chr)
3. [FLOAT](#float)
4. [INT](#int)
5. [InStr](#instr)
6. [RegExMatch](#regexmatch)
7. [RegExReplace](#regexreplace)
8. [STR](#str)
9. [Sort](#sort)
10. [StrLen](#strlen)
11. [StrLower](#strlower)
12. [StrReplace](#strreplace)
13. [StrSplit](#strsplit)
14. [StrTitleCase](#strtitlecase)
15. [StringTrimLeft](#stringtrimleft)
16. [StringTrimRight](#stringtrimright)
17. [SubStr](#substr)
18. [Trim](#trim)
19. [countChars](#countchars)
20. [getUrlParams](#geturlparams)
21. [sortArr](#sortarr)
22. [sortArrByLenOnly](#sortarrbylenonly)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Asc | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Chr | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| FLOAT | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| INT | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| InStr | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| RegExMatch | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| RegExReplace | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| STR | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Sort | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| StrLen | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| StrLower | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| StrReplace | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| StrSplit | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| StrTitleCase | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| StringTrimLeft | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| StringTrimRight | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| SubStr | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Trim | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| countChars | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| getUrlParams | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| sortArr | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| sortArrByLenOnly | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

---

### Asc

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Asc | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Returns the ASCII (or Unicode) value of the first character in a string. If the string is empty, it typically returns -1 or an error depending on the language.

Here is how to use it:

```htvm
str char1 := "A"
int ascii1 := Asc(char1)
print("Asc('A') = " . STR(ascii1))
; Expected: 65
if (ascii1 != 65) {
    print("Asc test 1 FAILED!")
}
; ----------------------------------------------------
str char2 := "a"
int ascii2 := Asc(char2)
print("Asc('a') = " . STR(ascii2))
; Expected: 97
if (ascii2 != 97) {
    print("Asc test 2 FAILED!")
}
; ----------------------------------------------------
str char3 := " "
int ascii3 := Asc(char3)
print("Asc(' ') = " . STR(ascii3))
; Expected: 32
if (ascii3 != 32) {
    print("Asc test 3 FAILED!")
}
; ----------------------------------------------------
str emptyStr := ""
int asciiEmpty := Asc(emptyStr)
print("Asc('') = " . STR(asciiEmpty))
; Expected: -1 (or error)
if (asciiEmpty != -1) {
    print("Asc empty string test might need review for specific language behavior, got: " . STR(asciiEmpty))
}
```


---
### Chr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Chr | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Returns the character represented by the given ASCII (or Unicode) value. Input must be an integer.

Here is how to use it:

```htvm
int code1 := 65
str char1 := Chr(code1)
print("Chr(65) = '" . char1 . "'")
; Expected: 'A'
if (char1 != "A") {
    print("Chr test 1 FAILED!")
}
; ----------------------------------------------------
int code2 := 97
str char2 := Chr(code2)
print("Chr(97) = '" . char2 . "'")
; Expected: 'a'
if (char2 != "a") {
    print("Chr test 2 FAILED!")
}
; ----------------------------------------------------
int code3 := 32
str char3 := Chr(code3)
print("Chr(32) = '" . char3 . "'")
; Expected: ' ' (space)
if (char3 != " ") {
    print("Chr test 3 FAILED!")
}
; ----------------------------------------------------
; Example with a less common character (e.g., Euro sign if supported)
; Euro sign €
int code4 := 8364
str char4 := Chr(code4)
print("Chr(8364) = '" . char4 . "'")
; Expected: '€' (if supported by environment/font)
```


---
### FLOAT

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FLOAT | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Converts a string representation of a number into a floating-point number. If the string cannot be converted, it may throw an error or return a special value like NaN, depending on the target language.

Here is how to use it:

```htvm
str strNum1 := "123.45"
float float1 := FLOAT(strNum1)
print("FLOAT('123.45') = " . STR(float1))
; Expected: 123.45
if (Abs(float1 - 123.45) > 0.00001) {
    print("FLOAT test 1 FAILED!")
}
; ----------------------------------------------------
str strNum2 := "-0.5"
float float2 := FLOAT(strNum2)
print("FLOAT('-0.5') = " . STR(float2))
; Expected: -0.5
if (Abs(float2 - (-0.5)) > 0.00001) {
    print("FLOAT test 2 FAILED!")
}
; ----------------------------------------------------
str strNum3 := "789"
float float3 := FLOAT(strNum3)
; Integer string
print("FLOAT('789') = " . STR(float3))
; Expected: 789.0
if (Abs(float3 - 789.0) > 0.00001) {
    print("FLOAT test 3 FAILED!")
}
; ----------------------------------------------------
; Example of an invalid string (behavior might vary: error or NaN)
str invalidStr := "abc"
float floatInvalid := FLOAT(invalidStr)
print("FLOAT('abc') = " . STR(floatInvalid))
```


---
### INT

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| INT | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Converts a string representation of a number into an integer. If the string represents a floating-point number, the fractional part is typically truncated. If the string cannot be converted, it may throw an error or return 0/NaN.

Here is how to use it:

```htvm
str strNum1 := "123"
int int1 := INT(strNum1)
print("INT('123') = " . STR(int1))
; Expected: 123
if (int1 != 123) {
    print("INT test 1 FAILED!")
}
; ----------------------------------------------------
str strNum2 := "123.789"
; String with a float
int int2 := INT(strNum2)
print("INT('123.789') = " . STR(int2))
; Expected: 123 (truncation)
if (int2 != 123) {
    print("INT test 2 FAILED!")
}
; ----------------------------------------------------
str strNum3 := "-456"
int int3 := INT(strNum3)
print("INT('-456') = " . STR(int3))
; Expected: -456
if (int3 != -456) {
    print("INT test 3 FAILED!")
}
; ----------------------------------------------------
; Example of an invalid string (behavior might vary: error or 0/NaN)
str invalidStr := "xyz"
int intInvalid := INT(invalidStr)
print("INT('xyz') = " . STR(intInvalid))
```


---
### InStr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| InStr | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Searches for the first occurrence of a `needle` substring within a `haystack` string. Returns the 1-based starting position of `needle` if found, otherwise returns 0. Case-sensitivity depends on the target language's default string search behavior.

Here is how to use it:

```htvm
str haystack := "Hello, HTVM World! HTVM is cool."
str needle1 := "HTVM"
int pos1 := InStr(haystack, needle1)
print("Position of 'HTVM' in '" . haystack . "' is: " . STR(pos1))
; Expected: 8 (1-indexed-based)
if (pos1 != 8) {
    print("InStr test 1 FAILED!")
}
; ----------------------------------------------------
str needle2 := "World"
int pos2 := haystack.InStr(needle2)
print("Position of 'World' is: " . STR(pos2))
; Expected: 13 (1-indexed-based)
if (pos2 != 13) {
    print("InStr test 2 FAILED!")
}
; ----------------------------------------------------
str needle3 := "notfound"
int pos3 := InStr(haystack, needle3)
print("Position of 'notfound' is: " . STR(pos3))
; Expected: 0
if (pos3 != 0) {
    print("InStr test 3 FAILED!")
}
; ----------------------------------------------------
str needle4 := "hTvm"
; Test case-sensitivity (may vary by language)
int pos4 := InStr(haystack, needle4)
print("Position of 'hTvm' (case test) is: " . STR(pos4))
; Expected might be 0 if case-sensitive, or 8 if case-insensitive
```


---
### RegExMatch

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| RegExMatch | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Searches a `haystack` string for the first occurrence of a regular expression `pattern`. Returns the 1-based starting position of the match if found, otherwise returns 0. The regex syntax compatibility depends on the target language.

Here is how to use it:

```htvm
str text := "The year is 2024, and the price is $19.99."
; Matches four digits (year)
str pattern1 := "\d{4}"
int matchPos1 := RegExMatch(text, pattern1)
print("Position of year pattern: " . STR(matchPos1))
; Expected: 13 (for "2024")
if (matchPos1 != 13) {
    print("RegExMatch test 1 FAILED!")
}
; ----------------------------------------------------
; Matches a price like $xx.yy
str pattern2 := "\$[0-9]+\.[0-9]{2}"
int matchPos2 := text.RegExMatch(pattern2)
print("Position of price pattern: " . STR(matchPos2))
; Expected: 36 (for "$19.99")
if (matchPos2 != 36) {
    print("RegExMatch test 2 FAILED!")
}
; ----------------------------------------------------
; Pattern not in text
str pattern3 := "XYZ"
int matchPos3 := RegExMatch(text, pattern3)
print("Position of 'XYZ' pattern: " . STR(matchPos3))
; Expected: 0
if (matchPos3 != 0) {
    print("RegExMatch test 3 FAILED!")
}
; ----------------------------------------------------
; Check if a number exists in the text
str numText := "There are 42 apples."
; Matches any number
str numPattern := "\d+"
int numPos := RegExMatch(numText, numPattern)
print("Position of number in text: " . STR(numPos))
; Expected: 12 (for "42")
if (numPos > 0) {
    print("Number found in text.")
}
else {
    print("No number found in text.")
}
; ----------------------------------------------------
; Check if a string exists
str stringText := "The quick brown fox jumps over the lazy dog."
; Matches the word "fox"
str stringPattern := "fox"
int stringPos := RegExMatch(stringText, stringPattern)
print("Position of 'fox' in text: " . STR(stringPos))
; Expected: 17
if (stringPos > 0) {
    print("'fox' found in text.")
}
else {
    print("'fox' not found in text.")
}
; ----------------------------------------------------
; Check if a specific format (email) exists
str emailText := "Please contact support@domain.com for help."
; Matches an email format
str emailPattern := "[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}"
int emailPos := RegExMatch(emailText, emailPattern)
print("Position of email pattern: " . STR(emailPos))
; Expected: 23 (for "support@domain.com")
if (emailPos > 0) {
    print("Email found in text.")
}
else {
    print("No email found in text.")
}
```


---
### RegExReplace

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| RegExReplace | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Replaces occurrences of a regular expression `pattern` within an `inputStr` with a `replacement` string. Returns the modified string. The regex syntax and replacement capabilities depend on the target language.

Here is how to use it:

```htvm
str text := "Contact us at info@example.com or support@example.org for help."
str emailPattern := "[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}"
str replacement := "[REDACTED_EMAIL]"
str result1 := RegExReplace(text, emailPattern, replacement)
print("Original: " . text)
print("Redacted: " . result1)
; Expected: Contact us at [REDACTED_EMAIL] or [REDACTED_EMAIL] for help.
str expected1 := "Contact us at [REDACTED_EMAIL] or [REDACTED_EMAIL] for help."
if (result1 != expected1) {
    print("RegExReplace test 1 FAILED!")
}
; ----------------------------------------------------
str text2 := "The numbers are 123 and 456."
str digitPattern := "\d+"
; Matches one or more digits
str replacement2 := "###"
str result2 := text2.RegExReplace(digitPattern, replacement2)
print("Original: " . text2)
print("Numbers replaced: " . result2)
; Expected: The numbers are ### and ###.
str expected2 := "The numbers are ### and ###."
if (result2 != expected2) {
    print("RegExReplace test 2 FAILED!")
}
```


---
### STR

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| STR | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Converts a given value (number, boolean, or existing string) into its string representation. For booleans, `true` becomes "1" and `false` becomes "0" (or language equivalent). Helpful for concatenation or when a string is explicitly needed.

Here is how to use it:

```htvm
int num := 123
str strNum := STR(num)
print("STR(123) = '" . strNum . "'")
; Expected: '123'
if (strNum != "123") {
    print("STR int test FAILED!")
}
; ----------------------------------------------------
float flt := -45.67
str strFlt := STR(flt)
print("STR(-45.67) = '" . strFlt . "'")
; Expected: '-45.67' (or similar float string)
if (strFlt != "-45.67") {
    print("STR float test FAILED!")
}
; ----------------------------------------------------
bool bTrue := true
str strTrue := STR(bTrue)
print("STR(true) = '" . strTrue . "'")
; Expected: '1' (or 'true')
if (strTrue != "1" and strTrue != "true") {
    print("STR true test FAILED! Got: " . strTrue)
}
; ----------------------------------------------------
bool bFalse := false
str strFalse := STR(bFalse)
print("STR(false) = '" . strFalse . "'")
; Expected: '0' (or 'false')
if (strFalse != "0" and strFalse != "false") {
    print("STR false test FAILED! Got: " . strFalse)
}
; ----------------------------------------------------
str existingStr := "already_string"
str strExisting := STR(existingStr)
print("STR('already_string') = '" . strExisting . "'")
; Expected: 'already_string'
if (strExisting != "already_string") {
    print("STR existing string test FAILED!")
}
```


---
### Sort

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Sort | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Sorts lines or delimited items within a string. Options control sorting behavior: 'C' (case-sensitive), 'U' (unique items), 'R' (reverse order), 'N' (numeric sort), 'D`char`' (custom delimiter). Default delimiter is newline.

Here is how to use it:

```htvm
str list1 := "Charlie`nAlpha`nBravo"
str sorted1 := Sort(list1, "U")
print("Default sort (list1):`n" . sorted1)
; Expected: Alpha`nBravo`nCharlie (case-insensitive by default unless C option)
; Assuming case-insensitive default for test
; Note: Actual default might vary if underlying language sorts case-sensitively.
; ----------------------------------------------------
print("---")
str list2 := "10`n2`n100`n1"
str sorted2_alpha := Sort(list2, "U")
str sorted2_numeric := Sort(list2, "N")
print("Alpha sort (list2):`n" . sorted2_alpha)
; Expected: 1`n10`n100`n2
print("Numeric sort (list2):`n" . sorted2_numeric)
; Expected: 1`n2`n10`n100
if (sorted2_numeric != "1`n2`n10`n100") {
    print("Sort numeric test FAILED!")
}
; ----------------------------------------------------
print("---")
str list3 := "apple,banana,apple,orange"
str sorted3_unique_comma := Sort(list3, "UD,")
; Unique, comma-delimited
print("Unique comma sort (list3):`n" . sorted3_unique_comma)
; Expected: apple,banana,orange (order may vary for first two)
; A simple check for content rather than strict order for unique test:
if (InStr(sorted3_unique_comma, "apple") = 0 or InStr(sorted3_unique_comma, "banana") = 0 or InStr(sorted3_unique_comma, "orange") = 0 or countChars(sorted3_unique_comma, ",") != 2) {
    print("Sort unique comma test FAILED! Got: " . sorted3_unique_comma)
}
; ----------------------------------------------------
print("---")
str list4 := "Zebra`napple`nCAT"
str sorted4_case_reverse := Sort(list4, "CR")
print("Case-sensitive Reverse (list4):`n" . sorted4_case_reverse)
; Expected: apple`nZebra`nCAT (Z > C, a > Z)
; This expected order depends on specific sort implementation with mixed case.
; For testing, let's target a more predictable case-insensitive reverse.
str sorted4_insensitive_reverse := Sort(list4, "R")
; Assuming default is case-insensitive for this test
print("Case-insensitive Reverse (list4):`n" . sorted4_insensitive_reverse)
; Expected: Zebra`nCAT`napple
if (sorted4_insensitive_reverse != "Zebra`nCAT`napple") {
    print("Sort insensitive reverse test FAILED!")
}
```


---
### StrLen

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrLen | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Returns the length (number of characters) of a string.

Here is how to use it:

```htvm
str text1 := "Hello"
int len1 := StrLen(text1)
; Expected: 5
print("Length of '" . text1 . "' is: " . STR(len1))
if (len1 != 5) {
    print("StrLen test 1 FAILED!")
}
; ----------------------------------------------------
str text2 := ""
; Empty string
int len2 := text2.StrLen()
; Expected: 0
print("Length of '' is: " . STR(len2))
if (len2 != 0) {
    print("StrLen test 2 FAILED!")
}
; ----------------------------------------------------
str text3 := "HTVM `nRocks!"
; Contains a newline
int len3 := StrLen(text3)
; Expected: 12 (newline is one char)
print("Length of 'HTVM `nRocks!' is: " . STR(len3))
if (len3 != 12) {
    print("StrLen test 3 FAILED!")
}
```


---
### StrLower

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrLower | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Converts all uppercase characters in a string to lowercase. Non-alphabetic characters are unaffected.

Here is how to use it:

```htvm
str text1 := "HeLlO, WoRlD!"
str lower1 := StrLower(text1)
; Expected: 'hello, world!'
print("StrLower('" . text1 . "') = '" . lower1 . "'")
if (lower1 != "hello, world!") {
    print("StrLower test 1 FAILED!")
}
; ----------------------------------------------------
str text2 := "HTVM ROCKS 123!"
str lower2 := text2.StrLower
; Expected: 'htvm rocks 123!'
print("StrLower('" . text2 . "') = '" . lower2 . "'")
if (lower2 != "htvm rocks 123!") {
    print("StrLower test 2 FAILED!")
}
; ----------------------------------------------------
str text3 := "already lowercase"
str lower3 := StrLower(text3)
; Expected: 'already lowercase'
print("StrLower('" . text3 . "') = '" . lower3 . "'")
if (lower3 != "already lowercase") {
    print("StrLower test 3 FAILED!")
}
```


---
### StrReplace

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrReplace | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Replaces all occurrences of a `find` substring within an `originalString` with a `replaceWith` string. Returns the modified string.

Here is how to use it:

```htvm
str original1 := "Hello World, Hello HTVM!"
str find1 := "Hello"
str replace1 := "Greetings"
str result1 := StrReplace(original1, find1, replace1)
print("Replacing '" . find1 . "' in '" . original1 . "' with '" . replace1 . "': '" . result1 . "'")
; Expected: 'Greetings World, Greetings HTVM!'
if (result1 != "Greetings World, Greetings HTVM!") {
    print("StrReplace test 1 FAILED!")
}
; ----------------------------------------------------
str original2 := "one two three two one"
str find2 := "two"
str replace2 := "2"
str result2 := original2.StrReplace(find2, replace2)
print("Replacing '" . find2 . "' in '" . original2 . "' with '" . replace2 . "': '" . result2 . "'")
; Expected: 'one 2 three 2 one'
if (result2 != "one 2 three 2 one") {
    print("StrReplace test 2 FAILED!")
}
; ----------------------------------------------------
str original3 := "No change needed"
str find3 := "XYZ"
str replace3 := "ABC"
str result3 := StrReplace(original3, find3, replace3)
print("Replacing '" . find3 . "' in '" . original3 . "' (not found): '" . result3 . "'")
; Expected: 'No change needed'
if (result3 != "No change needed") {
    print("StrReplace test 3 FAILED!")
}
; ----------------------------------------------------
str original4 := "Remove this"
str find4 := " this"
str replace4 := ""
; Replace with empty string to delete
str result4 := StrReplace(original4, find4, replace4)
print("Deleting '" . find4 . "' from '" . original4 . "': '" . result4 . "'")
; Expected: 'Remove'
if (result4 != "Remove") {
    print("StrReplace test 4 (deletion) FAILED!")
}
```


---
### StrSplit

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrSplit | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Splits an `inputStr` by a `delimiter` and returns the Nth part (1-based index `num`). If `num` is out of range, or the delimiter is not found appropriately, it may return an empty string or cause an error depending on the language.

Here is how to use it:

```htvm
str data1 := "apple,banana,cherry,date"
str delimiter1 := ","
int partNum1 := 2
str fruit1 := StrSplit(data1, delimiter1, partNum1)
; Expected: 'banana'
print("Part " . STR(partNum1) . " of '" . data1 . "' with delimiter '" . delimiter1 . "' is: '" . fruit1 . "'")
if (fruit1 != "banana") {
    print("StrSplit test 1 FAILED!")
}
; ----------------------------------------------------
int partNum2 := 4
str fruit2 := data1.StrSplit(delimiter1, partNum2)
; Expected: 'date'
print("Part " . STR(partNum2) . " is: '" . fruit2 . "'")
if (fruit2 != "date") {
    print("StrSplit test 2 FAILED!")
}
; ----------------------------------------------------
int partNum3 := 1
str fruit3 := StrSplit(data1, delimiter1, partNum3)
; Expected: 'apple'
print("Part " . STR(partNum3) . " is: '" . fruit3 . "'")
if (fruit3 != "apple") {
    print("StrSplit test 3 FAILED!")
}
; ----------------------------------------------------
; Out of bounds
int partNum4 := 5
str fruit4 := StrSplit(data1, delimiter1, partNum4)
; Expected: '' (empty string)
print("Part " . STR(partNum4) . " (out of bounds) is: '" . fruit4 . "'")
if (fruit4 != "") {
    print("StrSplit test 4 (out of bounds) FAILED! Got: " . fruit4)
}
; ----------------------------------------------------
str data2 := "one;-;two;-;three"
str delimiter2 := ";-;"
int partNum5 := 3
str item5 := StrSplit(data2, delimiter2, partNum5)
; Expected: 'three'
print("Part " . STR(partNum5) . " of '" . data2 . "' with delimiter '" . delimiter2 . "' is: '" . item5 . "'")
if (item5 != "three") {
    print("StrSplit test 5 FAILED!")
}
```


---
### StrTitleCase

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrTitleCase | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Converts a string to title case, where the first letter of each word is capitalized and all other letters are lowercase. Words are generally delimited by spaces.

Here is how to use it:

```htvm
str text1 := "hello world example"
str title1 := StrTitleCase(text1)
; Expected: 'Hello World Example'
print("Title case of '" . text1 . "': '" . title1 . "'")
if (title1 != "Hello World Example") {
    print("StrTitleCase test 1 FAILED!")
}
; ----------------------------------------------------
str text2 := "HTVM is AWESOME"
str title2 := text2.StrTitleCase
; Expected: 'Htvm Is Awesome'
print("Title case of '" . text2 . "': '" . title2 . "'")
if (title2 != "Htvm Is Awesome") {
    print("StrTitleCase test 2 FAILED!")
}
; ----------------------------------------------------
str text3 := "Already Title Case"
str title3 := StrTitleCase(text3)
; Expected: 'Already Title Case'
print("Title case of '" . text3 . "': '" . title3 . "'")
if (title3 != "Already Title Case") {
    print("StrTitleCase test 3 FAILED!")
}
; ----------------------------------------------------
str text4 := " leading space"
str title4 := StrTitleCase(text4)
; Expected: ' Leading Space'
print("Title case of '" . text4 . "': '" . title4 . "'")
if (title4 != " Leading Space") {
    print("StrTitleCase test 4 FAILED!")
}
```


---
### StringTrimLeft

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StringTrimLeft | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Removes a specified number of characters (`numChars`) from the beginning (left side) of a string. If `numChars` is greater than the string length, the result might be an empty string or the original string depending on implementation.

Here is how to use it:

```htvm
str text1 := "HelloHTVM"
int charsToTrim1 := 5
str result1 := StringTrimLeft(text1, charsToTrim1)
; Expected: 'HTVM'
print("Trimming " . STR(charsToTrim1) . " chars from left of '" . text1 . "': '" . result1 . "'")
if (result1 != "HTVM") {
    print("StringTrimLeft test 1 FAILED!")
}
; ----------------------------------------------------
str text2 := "Goodbye"
int charsToTrim2 := 3
str result2 := text2.StringTrimLeft(charsToTrim2)
; Expected: 'dbye'
print("Trimming " . STR(charsToTrim2) . " chars from left of '" . text2 . "': '" . result2 . "'")
if (result2 != "dbye") {
    print("StringTrimLeft test 2 FAILED!")
}
; ----------------------------------------------------
str text3 := "Short"
int charsToTrim3 := 10
; More than length
str result3 := StringTrimLeft(text3, charsToTrim3)
; Expected: '' (or "Short", behavior might vary)
; For HTVM, typically it results in the same string if trim count exceeds length but it depends on the implementation.
print("Trimming " . STR(charsToTrim3) . " chars from left of '" . text3 . "': '" . result3 . "'")
; ----------------------------------------------------
int charsToTrim4 := 0
str result4 := StringTrimLeft(text1, charsToTrim4)
; Expected: 'HelloHTVM'
print("Trimming " . STR(charsToTrim4) . " chars from left of '" . text1 . "': '" . result4 . "'")
if (result4 != "HelloHTVM") {
    print("StringTrimLeft test 4 (zero trim) FAILED!")
}
```


---
### StringTrimRight

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StringTrimRight | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Removes a specified number of characters (`numChars`) from the end (right side) of a string. If `numChars` is greater than the string length, the result might be an empty string or the original string.

Here is how to use it:

```htvm
str text1 := "HTVMHello"
int charsToTrim1 := 5
str result1 := StringTrimRight(text1, charsToTrim1)
; Expected: 'HTVM'
print("Trimming " . STR(charsToTrim1) . " chars from right of '" . text1 . "': '" . result1 . "'")
if (result1 != "HTVM") {
    print("StringTrimRight test 1 FAILED!")
}
; ----------------------------------------------------
str text2 := "Welcome"
int charsToTrim2 := 3
str result2 := text2.StringTrimRight(charsToTrim2)
; Expected: 'Welc'
print("Trimming " . STR(charsToTrim2) . " chars from right of '" . text2 . "': '" . result2 . "'")
if (result2 != "Welc") {
    print("StringTrimRight test 2 FAILED!")
}
; ----------------------------------------------------
str text3 := "Tiny"
int charsToTrim3 := 10
; More than length
str result3 := StringTrimRight(text3, charsToTrim3)
; Expected: "Tiny" it will not Trim since it exceeds the character limit. But it depends on the language.
print("Trimming " . STR(charsToTrim3) . " chars from right of '" . text3 . "': '" . result3 . "'")
; ----------------------------------------------------
int charsToTrim4 := 0
str result4 := StringTrimRight(text1, charsToTrim4)
; Expected: 'HTVMHello'
print("Trimming " . STR(charsToTrim4) . " chars from right of '" . text1 . "': '" . result4 . "'")
if (result4 != "HTVMHello") {
    print("StringTrimRight test 4 (zero trim) FAILED!")
}
```


---
### SubStr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| SubStr | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Extracts a substring from a string. `startPos` is the 1-based starting position. `length` is optional; if omitted, it extracts to the end of the string. Negative `startPos` counts from the end of the string.

Here is how to use it:

```htvm
str text := "Hello, HTVM World!"
; ----------------------------------------------------
; Example 1: Basic substring
int start1 := 8
int len1 := 4
str sub1 := SubStr(text, start1, len1)
print("SubStr('" . text . "', " . STR(start1) . ", " . STR(len1) . ") = '" . sub1 . "'")
; Expected: 'HTVM'
if (sub1 != "HTVM") {
    print("SubStr test 1 FAILED!")
}
; ----------------------------------------------------
; Example 2: Substring to end
int start2 := 13
str sub2 := text.SubStr(start2)
print("SubStr('" . text . "', " . STR(start2) . ") = '" . sub2 . "'")
; Expected: 'World!'
if (sub2 != "World!") {
    print("SubStr test 2 FAILED!")
}
; ----------------------------------------------------
; Example 3: Negative start position
int start3 := -6
str sub3 := SubStr(text, start3)
print("SubStr('" . text . "', " . STR(start3) . ") = '" . sub3 . "'")
; Expected: 'World!'
if (sub3 != "World!") {
    print("SubStr test 3 FAILED!")
}
; ----------------------------------------------------
; Example 4: Negative start and specific length
int start4 := -6
int len4 := 5
str sub4 := SubStr(text, start4, len4)
print("SubStr('" . text . "', " . STR(start4) . ", " . STR(len4) . ") = '" . sub4 . "'")
; Expected: 'World'
if (sub4 != "World") {
    print("SubStr test 4 FAILED!")
}
; ----------------------------------------------------
; Example 5: Start position 1
int start5 := 1
int len5 := 5
str sub5 := SubStr(text, start5, len5)
print("SubStr('" . text . "', " . STR(start5) . ", " . STR(len5) . ") = '" . sub5 . "'")
; Expected: 'Hello'
if (sub5 != "Hello") {
    print("SubStr test 5 FAILED!")
}
```


---
### Trim

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Trim | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Removes all leading and trailing whitespace (spaces, tabs, newlines, etc.) from the input string. If the input string is empty or contains only whitespace, it returns an empty string. It's useful for cleaning up user input or data read from files before processing.

Here is how to use it:

```htvm
str text1 := "   Hello, HTVM!   "
str trimmed1 := Trim(text1)
print("Original 1: '" . text1 . "'")
print("Trimmed 1 : '" . trimmed1 . "'")
; Expected: 'Hello, HTVM!'
if (trimmed1 != "Hello, HTVM!") {
    print("Trim test 1 FAILED! Oh noes!")
}
; ----------------------------------------------------
str text2 := "`t`n  HTVM Rocks! `n`r"
str trimmed2 := text2.Trim()
print("Original 2: '" . text2 . "' (has tabs/newlines)")
print("Trimmed 2 : '" . trimmed2 . "'")
; Expected: 'HTVM Rocks!'
if (trimmed2 != "HTVM Rocks!") {
    print("Trim test 2 FAILED! Oh noes!")
}
; ----------------------------------------------------
str text3 := "   "
str trimmed3 := text3.Trim
print("Original 3: '" . text3 . "' (only spaces)")
print("Trimmed 3 : '" . trimmed3 . "'")
; Expected: ''
if (trimmed3 != "") {
    print("Trim test 3 FAILED! Oh noes!")
}
; ----------------------------------------------------
str text4 := "NoSpaces"
str trimmed4 := Trim(text4)
print("Original 4: '" . text4 . "'")
print("Trimmed 4 : '" . trimmed4 . "'")
; Expected: 'NoSpaces'
if (trimmed4 != "NoSpaces") {
    print("Trim test 4 FAILED! Oh noes!")
}
```


---
### countChars

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| countChars | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Counts the occurrences of a specific character (`theChar`) or a substring within a given `string`. Case-sensitivity depends on the target language.

Here is how to use it:

```htvm
str text1 := "hello world, hello htvm"
str charToCount1 := "h"
int count1 := countChars(text1, charToCount1)
print("Count of '" . charToCount1 . "' in '" . text1 . "' is: " . STR(count1))
; Expected: 3
if (count1 != 3) {
    print("countChars test 1 (single char) FAILED! Expected 2, Got: " . STR(count1))
}
; ----------------------------------------------------
str text2 := "banana"
str charToCount2 := "a"
int count2 := text2.countChars(charToCount2)
print("Count of '" . charToCount2 . "' in '" . text2 . "' is: " . STR(count2))
; Expected: 3
if (count2 != 3) {
    print("countChars test 2 FAILED!")
}
; ----------------------------------------------------
str text4 := "no_such_char_here"
str charToCount4 := "z"
int count4 := countChars(text4, charToCount4)
print("Count of '" . charToCount4 . "' in '" . text4 . "' is: " . STR(count4))
; Expected: 0
if (count4 != 0) {
    print("countChars test 4 FAILED!")
}
```


---
### getUrlParams

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| getUrlParams | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

(JavaScript Only) Extracts parameter values from the current URL's query string. It typically decodes and concatenates them, often separated by '&'. Primarily used in web browser environments for frontend logic.

Here is how to use it:

```htvm
; This function is JavaScript-specific and relies on browser environment.
; The example shows conceptual usage. To test, run in a browser with a URL like:
; http://example.com?name=Alice&topic=HTVM&mode=test
; This is not really possible to test
; This how you might use it:
str params := getUrlParams()
; Expected (if URL was ?name=Alice&project=HTVM&version=2): "Alice&HTVM&2" or similar
; Then you can do this:
; Example
params := "Alice&HTVM&2"
; Loop over the params
Loop, Parse, params, "&" {
    ; print each value
    print(A_LoopField)
}
```


---
### sortArr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| sortArr | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Sorts an array of strings in ascending order. It typically removes duplicate values before sorting, resulting in an array of unique, sorted strings. The sorting is usually case-insensitive by default, but this can vary by language.

Here is how to use it:

```htvm
arr str unsortedArr1 := ["Charlie", "Alpha", "Bravo", "alpha"]
arr str sortedArr1
sortedArr1 := sortArr(unsortedArr1)
print("Original Array 1: ")
Loop, % unsortedArr1.size() {
    print("  " . unsortedArr1[A_Index])
}
print("Sorted Unique Array 1: ")
Loop, % sortedArr1.size() {
    print("  " . sortedArr1[A_Index])
}
; Expected (case-sensitive): ["Alpha", "Bravo", "Charlie", "alpha"]
if (sortedArr1.size() != 4 or sortedArr1[0] != "Alpha" or sortedArr1[1] != "Bravo" or sortedArr1[2] != "Charlie" or sortedArr1[3] != "alpha") {
    print("sortArr test 1 FAILED!")
}
; ----------------------------------------------------
print("--------------------")
arr str unsortedArr2 := ["10", "2", "100", "1", "2"]
arr str sortedArr2
sortedArr2 := unsortedArr2.sortArr()
; Alternative call
print("Original Array 2: ")
Loop, % unsortedArr2.size() {
    print("  " . unsortedArr2[A_Index])
}
print("Sorted Unique Array 2 (lexicographical): ")
Loop, % sortedArr2.size() {
    print("  " . sortedArr2[A_Index])
}
; Expected (lexicographical, unique): ["1", "10", "100", "2"]
if (sortedArr2.size() != 4 or sortedArr2[0] != "1" or sortedArr2[1] != "10" or sortedArr2[2] != "100" or sortedArr2[3] != "2") {
    print("sortArr test 2 FAILED!")
}
```


---
### sortArrByLenOnly

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| sortArrByLenOnly | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Sorts an array of strings primarily by their length in descending order (longest strings first). If strings have the same length, their relative order might be preserved or sorted alphabetically, depending on the underlying sort stability and implementation.

Here is how to use it:

```htvm
arr str arr1 := ["a", "bb", "ccc", "dddd", "eeeee"]
; Should already be sorted by length descending
arr str sorted1
sorted1 := sortArrByLenOnly(arr1)
print("Original Array 1: eeeee, dddd, ccc, bb, a")
print("Sorted by Length Desc 1: ")
Loop, % sorted1.size() {
    print("  " . sorted1[A_Index])
}
if (sorted1[0] != "eeeee" or sorted1[4] != "a") {
    print("sortArrByLenOnly test 1 FAILED!")
}
; ----------------------------------------------------
print("--------------------")
arr str arr2 := ["short", "longer_word", "tiny", "very_long_length"]
arr str sorted2
sorted2 := arr2.sortArrByLenOnly()
print("Original Array 2: short, longer_word, tiny, very_long_length")
print("Sorted by Length Desc 2: ")
Loop, % sorted2.size() {
    print("  " . sorted2[A_Index])
}
; Expected: very_long_length, longer_word, short, tiny (order of same-length items may vary but probably alphabetically)
str expectedOrderStart := "very_long_length"
str expectedOrderEnd := "tiny"
if (sorted2[0] != expectedOrderStart or sorted2[3] != expectedOrderEnd) {
    print("sortArrByLenOnly test 2 FAILED! Check start/end elements.")
}
```


---
## System Functions

[Go back](#built-in-functions)

1. [BuildInVars](#buildinvars)
2. [ExitApp](#exitapp)
3. [HTVM_getLang_HTVM](#htvm_getlang_htvm)
4. [Sleep](#sleep)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| BuildInVars | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| ExitApp | Yes | Yes | No | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| HTVM_getLang_HTVM | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| Sleep | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

---

### BuildInVars

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| BuildInVars | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Retrieves various system-related, time-related, or environment-specific built-in variable values. The `varName` argument specifies which variable to get (e.g., "A_YYYY" for year, "A_ScreenWidth" for screen width, "A_TickCount" for milliseconds since program start). Availability of specific variables can depend on the target language and environment (e.g., screen dimensions are browser-specific).

Here is how to use it:

```htvm
; ==== Built-in Variables for BuildInVars() ====
; A_ScreenWidth  - Width of the window screen (browser only)
; A_ScreenHeight - Height of the window screen (browser only)
; A_LastKey      - Last key pressed by the user (browser only)
; A_TimeIdle     - Time the user has been idle (in ms or seconds)
; A_TickCount    - Current tick count (ms since the start)
; A_Now          - Local datetime string (full, locale-based)
; A_YYYY         - 4-digit current year
; A_MM           - 2-digit current month (01–12)
; A_DD           - 2-digit current day of month (01–31)
; A_MMMM         - Full month name (e.g. January)
; A_MMM          - Abbreviated month name (e.g. Jan)
; A_DDDD         - Full day name (e.g. Monday)
; A_DDD          - Abbreviated day name (e.g. Mon)
; A_Hour         - Current hour (00–23)
; A_Min          - Current minute (00–59)
; A_Sec          - Current second (00–59)
; A_Space        - Space character (" ")
; A_Tab          - Tab character ("\t")
; ==========================================================
; Some behavior may vary depending on the target language!!!
; Make sure to test your code thoroughly!!!
; ==========================================================
; Examples:
str currentYear := BuildInVars("A_YYYY")
print("Current Year (A_YYYY): " . currentYear)
; ----------------------------------------------------
str currentMonth := BuildInVars("A_MMMM")
print("Current Month (A_MMMM): " . currentMonth)
if (StrLen(currentMonth) < 3) {
    print("BuildInVars A_MMMM test FAILED! Month name too short.")
}
; ----------------------------------------------------
str tabChar := BuildInVars("A_Tab")
print("Space char (A_Tab): '" . tabChar . "'")
; ----------------------------------------------------
; Browser-specific example (will return empty or error in non-browser environments)
str screenWidth := BuildInVars("A_ScreenWidth")
print("Screen Width (A_ScreenWidth): " . screenWidth)
if (HTVM_getLang_HTVM() = "js" and screenWidth = "") {
    print("BuildInVars A_ScreenWidth test needs a browser!")
}
; ----------------------------------------------------
str tickCount1 := BuildInVars("A_TickCount")
print("TickCount 1: " . STR(tickCount1))
await Sleep(100)
str tickCount2 := BuildInVars("A_TickCount")
print("TickCount 2 (after 100ms sleep): " . STR(tickCount2))
; This will never be perfectly 100 because:
; 1. Awaiting Sleep(100) requests a **minimum** delay of 100ms, not an exact one.
; 2. The actual sleep time depends on the timing resolution of the environment or runtime (e.g. JavaScript timers, OS scheduler).
; 3. Some overhead is added due to:
;    - Executing BuildInVars("A_TickCount") before and after.
;    - Interpreter/runtime processing.
;    - Internal event loop mechanics if async is involved.
; 4. On some systems or browsers, sleep may overshoot significantly (e.g. 101–130ms).
if (INT(tickCount2) <= INT(tickCount1)) {
    print("BuildInVars A_TickCount test FAILED! Ticks did not increase.")
}
```


---
### ExitApp

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ExitApp | Yes | Yes | No | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Terminates the current program immediately. Any code following `ExitApp()` will not be executed. This function is not available in all target environments (e.g., standard web JavaScript).

Here is how to use it:

```htvm
print("Program is starting...")
; Set to true to test, false to continue
bool shouldExit := true
if (shouldExit = true) {
    print("Preparing to exit...")
    ; Note: The following line will only execute if ExitApp is NOT called or is unavailable.
    ; In a successful ExitApp call, "This line should not print..." will not appear.
    if (HTVM_getLang_HTVM() = "js") {
        ; ExitApp not typically available in a browser
        print("ExitApp is not available in this JavaScript environment. Skipping exit.")
    }
    else {
        print("Calling ExitApp()...")
        ExitApp()
        ; Test assertion
        print("This line SHOULD NOT PRINT if ExitApp worked!")
    }
}
print("Program continued (only if ExitApp was not called or not available).")
```


---
### HTVM_getLang_HTVM

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| HTVM_getLang_HTVM | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Returns a string indicating the current target language HTVM is configured to transpile to or is running in. For example, it might return "cpp", "py", "js", etc. Useful for writing conditional HTVM code based on the target environment.

Here is how to use it:

```htvm
str currentLang := HTVM_getLang_HTVM()
print("Current HTVM target language is: " . currentLang)
if (currentLang = "js") {
    print("This code is specific to JavaScript.")
}
else if (currentLang = "py") {
    print("This part runs if the target is Python.")
}
else if (currentLang = "cpp") {
    print("C++ specific logic here.")
}
else {
    print("Running in or targeting another language: " . currentLang)
}
; Test: The function should return a non-empty string.
if (StrLen(currentLang) = 0) {
    print("HTVM_getLang_HTVM test FAILED! Returned empty string.")
}
else {
    print("HTVM_getLang_HTVM test PASSED (returned a non-empty string).")
}
```


---
### Sleep

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Sleep | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Pauses the execution of the program for a specified number of `milliseconds` (integer).

Here is how to use it:

```htvm
print("Starting sleep test...")
str startTime := BuildInVars("A_TickCount")
print("Start TickCount: " . STR(startTime))
; Sleep for 1 second (1000 milliseconds)
int duration := 1000
await Sleep(duration)
str endTime := BuildInVars("A_TickCount")
print("End TickCount: " . STR(endTime))
int elapsed := INT(endTime) - INT(startTime)
print("Elapsed time: " . STR(elapsed) . " ms")
; Test if elapsed time is approximately the sleep duration
; Allow for some overhead (e.g., +/- 200ms for system timing inaccuracies)
if (elapsed >= (duration - 200) and elapsed <= (duration + 2000)) {
    print("Sleep test PASSED! (Elapsed time is close to " . STR(duration) . "ms)")
}
else {
    print("Sleep test FAILED! Elapsed: " . STR(elapsed) . "ms, Expected around: " . STR(duration) . "ms")
}
; ----------------------------------------------------
print("--- Another sleep for 500ms ---")
await Sleep(500)
print("Woke up after 500ms.")
```


---
## File Functions

[Go back](#built-in-functions)

1. [FileAppend](#fileappend)
2. [FileAppendJs](#fileappendjs)
3. [FileCreateDir](#filecreatedir)
4. [FileDelete](#filedelete)
5. [FileExist](#fileexist)
6. [FileRead](#fileread)
7. [FileRemoveDir](#fileremovedir)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileAppend | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| FileAppendJs | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| FileCreateDir | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| FileDelete | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| FileExist | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| FileRead | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| FileRemoveDir | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

---

### FileAppend

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileAppend | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

Appends `content` (string) to a file specified by `path` (string). Creates the file if it doesn't exist. Returns a boolean indicating success (true) or failure (false). Not available in standard browser JavaScript due to security restrictions; use `FileAppendJs` for browser downloads.

Here is how to use it:

```htvm
; This example assumes a non-browser environment where file system access is permitted.
str filePath := "test_append.txt"
str content1 := "First line for test_append.txt`n"
bool success1 := FileAppend(content1, filePath)
print("Append 1 to '" . filePath . "' success: " . STR(success1))
if (success1 = false and HTVM_getLang_HTVM() != "js") {
    print("FileAppend test 1 FAILED!")
}
; ----------------------------------------------------
str content2 := "Second line, appended.`n"
bool success2 := FileAppend(content2, filePath)
print("Append 2 to '" . filePath . "' success: " . STR(success2))
if (success2 = false and HTVM_getLang_HTVM() != "js") {
    print("FileAppend test 2 FAILED!")
}
; ----------------------------------------------------
; Optionally, read back and verify (if FileRead is available and working)
if (FileExist(filePath) = true and HTVM_getLang_HTVM() != "js") {
    str fileContent := FileRead(filePath)
    print("Content of '" . filePath . "':`n" . fileContent)
    str expectedContent := content1 . content2
    if (Trim(fileContent) != Trim(expectedContent)) {
        print("FileAppend content verification FAILED!")
    }
    else {
        print("FileAppend content verification PASSED.")
    }
    ; Clean up the test file
    FileDelete(filePath)
    print("Test file '" . filePath . "' deleted.")
}
else if (HTVM_getLang_HTVM() = "js") {
    print("FileAppend is not available in standard JS. Use FileAppendJs for browser downloads.")
}
```


---
### FileAppendJs

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileAppendJs | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

(JavaScript Only - Browser) Initiates a file download in the browser with the given `content` (string) and `filename` (string). This is how file "saving" or "appending" is typically handled in a browser environment due to security restrictions on direct file system access.

Here is how to use it:

```htvm
; This function is specific to JavaScript running in a web browser.
if (HTVM_getLang_HTVM() = "js") {
    print("Attempting to trigger download using FileAppendJs...")
    str fileContent := "This is content for the downloaded file.`n"
    str fileName := "downloaded_by_htvm.txt"
    FileAppendJs(fileContent, fileName)
    print("FileAppendJs called. If in a browser, a download for '" . fileName . "' should have started.")
    print("Note: This is a 'save as' operation, not a true append to an existing local file.")
    ; No direct way to "test" success other than observing browser behavior.
}
else {
    print("FileAppendJs is only for JavaScript browser environments. Skipping test.")
}
```


---
### FileCreateDir

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileCreateDir | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

Creates a new directory specified by `path` (string). If the directory already exists, it usually does nothing. If intermediate directories in the path do not exist, their creation might depend on the target language's implementation (some create them, some require them to exist). Not available in standard browser JavaScript.

Here is how to use it:

```htvm
; This example assumes a non-browser environment.
str dirPath := "test_htvm_dir"
print("Attempting to create directory: '" . dirPath . "'")
if (HTVM_getLang_HTVM() = "js") {
    print("FileCreateDir is not available in standard JS. Skipping test.")
}
else {
    FileCreateDir(dirPath)
    if (FileExist(dirPath) = true) {
        print("Directory '" . dirPath . "' created or already existed. PASSED.")
        ; Clean up
        FileRemoveDir(dirPath)
        if (FileExist(dirPath) = false) {
            print("Test directory '" . dirPath . "' cleaned up successfully.")
        }
        else {
            print("Cleanup of '" . dirPath . "' FAILED.")
        }
    }
    else {
        print("FileCreateDir test FAILED! Directory not found after creation attempt.")
    }
    ; ----------------------------------------------------
    str nestedDirPath := "parent_dir/child_dir"
    print("Attempting to create nested directory: '" . nestedDirPath . "'")
    ; Behavior for non-existent 'parent_dir' varies.
    FileCreateDir(nestedDirPath)
    if (FileExist(nestedDirPath) = true) {
        print("Nested directory '" . nestedDirPath . "' creation attempt finished. Check if it exists.")
        ; Try to clean up child
        FileRemoveDir(nestedDirPath)
        ; Try to clean up parent
        FileRemoveDir("parent_dir")
    }
    else {
        print("Nested directory '" . nestedDirPath . "' not found. This might be expected if parent was not auto-created.")
    }
}
```


---
### FileDelete

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileDelete | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

Deletes a file specified by `path` (string). Returns a boolean indicating success (true) or failure (false, e.g., if the file doesn't exist or due to permissions). Not available in standard browser JavaScript.

Here is how to use it:

```htvm
; This example assumes a non-browser environment.
str filePath := "file_to_delete.txt"
if (HTVM_getLang_HTVM() = "js") {
    print("FileDelete is not available in standard JS. Skipping test.")
}
else {
    ; Create a dummy file to delete
    FileAppend("Temporary content.", filePath)
    if (FileExist(filePath) = true) {
        print("Dummy file '" . filePath . "' created for deletion test.")
        bool deleteSuccess := FileDelete(filePath)
        print("Deletion of '" . filePath . "' success: " . STR(deleteSuccess))
        if (deleteSuccess = true and FileExist(filePath) = false) {
            print("FileDelete test PASSED.")
        }
        else {
            print("FileDelete test FAILED! File still exists or deletion reported failure.")
        }
    }
    else {
        print("Could not create dummy file for FileDelete test.")
    }
    ; Test deleting a non-existent file
    str nonExistentFile := "surely_this_does_not_exist.txt"
    bool deleteNonExistentSuccess := FileDelete(nonExistentFile)
    print("Attempting to delete non-existent file '" . nonExistentFile . "'. Success: " . STR(deleteNonExistentSuccess))
    if (deleteNonExistentSuccess = false) {
        print("FileDelete non-existent file test PASSED (reported failure as expected).")
    }
    else {
        print("FileDelete non-existent file test FAILED! (Reported success for non-existent file).")
    }
}
```


---
### FileExist

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileExist | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

Checks if a file or directory exists at the specified `path` (string). Returns `true` if it exists, `false` otherwise. Not available in standard browser JavaScript.

Here is how to use it:

```htvm
; This example assumes a non-browser environment.
; Placeholder, will attempt to use the script's own file if GetParams works.
str existingFilePath := ""
str nonExistentPath := "this_path_should_not_exist_12345.xyz"
if (HTVM_getLang_HTVM() = "js") {
    print("FileExist is not available in standard JS. Skipping test.")
}
else {
    ; Try to get path of the current script or a known file for a positive test
    ; This part is a bit tricky without knowing the execution context.
    ; For a simple test, we'll create and check a temporary file.
    str tempFileForExistTest := "temp_exist_test.txt"
    FileAppend("check", tempFileForExistTest)
    bool check1 := FileExist(tempFileForExistTest)
    print("FileExist('" . tempFileForExistTest . "') = " . STR(check1))
    if (check1 = true) {
        print("FileExist test 1 (existing file) PASSED.")
    }
    else {
        print("FileExist test 1 (existing file) FAILED!")
    }
    ; Cleanup
    FileDelete(tempFileForExistTest)
    bool check2 := FileExist(nonExistentPath)
    print("FileExist('" . nonExistentPath . "') = " . STR(check2))
    if (check2 = false) {
        print("FileExist test 2 (non-existent path) PASSED.")
    }
    else {
        print("FileExist test 2 (non-existent path) FAILED!")
    }
    ; Test with a directory
    str tempDirForExistTest := "temp_dir_exist_test"
    FileCreateDir(tempDirForExistTest)
    bool check3 := FileExist(tempDirForExistTest)
    print("FileExist('" . tempDirForExistTest . "' as directory) = " . STR(check3))
    if (check3 = true) {
        print("FileExist test 3 (existing directory) PASSED.")
    }
    else {
        print("FileExist test 3 (existing directory) FAILED!")
    }
    ; Cleanup
    FileRemoveDir(tempDirForExistTest)
}
```


---
### FileRead

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileRead | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

Reads the entire content of a file specified by `path` (string) and returns it as a string. If the file doesn't exist or cannot be read, it may throw an error or return an empty/special value depending on the language. Not available in standard browser JavaScript.

Here is how to use it:

```htvm
; This example assumes a non-browser environment.
str filePath := "test_read_file.txt"
str fileContentToWrite := "Hello from HTVM FileRead test!`nLine 2."
if (HTVM_getLang_HTVM() = "js") {
    print("FileRead is not available in standard JS. Skipping test.")
}
else {
    ; Create a file with known content
    FileAppend(fileContentToWrite, filePath)
    if (FileExist(filePath) = true) {
        print("Test file '" . filePath . "' created with content.")
        str readContent := FileRead(filePath)
        print("Content read from '" . filePath . "':`n" . readContent)
        ; Normalize newlines for comparison as different OS might handle them differently.
        str normalizedRead := StrReplace(Trim(readContent), "`r`n", "`n")
        str normalizedExpected := StrReplace(Trim(fileContentToWrite), "`r`n", "`n")
        if (normalizedRead = normalizedExpected) {
            print("FileRead test PASSED.")
        }
        else {
            print("FileRead test FAILED! Content mismatch.")
            print("Expected: '" . normalizedExpected . "'")
            print("Got     : '" . normalizedRead . "'")
        }
        ; Cleanup
        FileDelete(filePath)
    }
    else {
        print("Could not create test file for FileRead.")
    }
}
```


---
### FileRemoveDir

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileRemoveDir | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

Removes a directory specified by `path` (string). If the directory contains files or subdirectories, their removal depends on the target language's implementation (some remove recursively, some fail if not empty). Not available in standard browser JavaScript.

Here is how to use it:

```htvm
; This example assumes a non-browser environment.
str dirPath := "dir_to_remove"
if (HTVM_getLang_HTVM() = "js") {
    print("FileRemoveDir is not available in standard JS. Skipping test.")
}
else {
    ; Test 1: Remove an empty directory
    FileCreateDir(dirPath)
    if (FileExist(dirPath) = true) {
        print("Directory '" . dirPath . "' created for removal test.")
        FileRemoveDir(dirPath)
        if (FileExist(dirPath) = false) {
            print("FileRemoveDir test 1 (empty dir) PASSED.")
        }
        else {
            print("FileRemoveDir test 1 (empty dir) FAILED! Directory still exists.")
        }
    }
    else {
        print("Could not create directory for FileRemoveDir test 1.")
    }
    print("--------------------")
    ; Test 2: Attempt to remove a directory that might have content (behavior can vary)
    str nestedDirPath := "parent_for_remove/child_for_remove"
    ; Creates parent/child potentially
    FileCreateDir(nestedDirPath)
    FileAppend("dummy", nestedDirPath . "/file.txt")
    if (FileExist(nestedDirPath) = true) {
        print("Nested directory with file created: '" . nestedDirPath . "'")
        ; Attempt to remove parent
        FileRemoveDir("parent_for_remove")
        if (FileExist("parent_for_remove") = false) {
            print("FileRemoveDir test 2 (potentially non-empty parent) PASSED (removed).")
        }
        else {
            print("FileRemoveDir test 2 (potentially non-empty parent) FAILED or partially failed. Check if 'parent_for_remove' still exists.")
            ; Cleanup if needed and possible
            FileRemoveDir(nestedDirPath)
            FileRemoveDir("parent_for_remove")
        }
    }
    else {
        print("Could not create nested directory for FileRemoveDir test 2.")
    }
}
```


---
## Io Functions

[Go back](#built-in-functions)

1. [GetParams](#getparams)
2. [RunCMD](#runcmd)
3. [getDataFromAPI](#getdatafromapi)
4. [input](#input)
5. [print](#print)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| GetParams | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| RunCMD | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| getDataFromAPI | Yes | Yes | Yes | Yes |Yes |No |Yes |Yes |Yes |Yes |Yes |No |No |No |Yes |
| input | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |
| print | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

---

### GetParams

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| GetParams | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

Retrieves command-line arguments passed to the script. Returns them as a single string, with each argument typically on a new line, or formatted as absolute paths if they correspond to existing files/directories. Behavior and availability vary significantly by environment (e.g., not applicable in browsers).

Here is how to use it:

```htvm
; This function's output depends on how the script is executed with command-line arguments.
; For testing, you would run the compiled HTVM script like:
; (e.g., if Python) python your_script.py arg1 "argument two" path/to/a/file.txt
if (HTVM_getLang_HTVM() = "js") {
    print("GetParams is typically not applicable in standard JS browser environments. Skipping direct test.")
}
else {
    print("Retrieving command line parameters...")
    str allParams := GetParams()
    if (allParams = "") {
        print("No command line parameters were provided to the script, or function not fully supported in this context.")
    }
    else {
        print("Command Line Parameters Received:")
        print(allParams)
        print("--- End of Parameters ---")
        ; A simple "test" is to check if it returned something if args were expected.
        ; This requires manual verification by running with args.
        print("GetParams test: Review the output above. If you passed arguments, they should appear here.")
    }
}
; Example of how you might parse it in HTVM if it returns newline-separated args:
arr str paramsArray
if (allParams != "") {
    Loop, Parse, allParams, `n, `r {
        print("Param " . STR(A_Index + 1) . ": " . A_LoopField)
        if (A_LoopField != "") {
            paramsArray.add(A_LoopField)
        }
    }
    print("Parsed first param (if any): " . paramsArray[0])
}
```


---
### RunCMD

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| RunCMD | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

Executes a system command (shell command) and returns its standard output as a string. Error output might also be captured or cause an error depending on the implementation. Highly environment-dependent and not available in browsers.

Here is how to use it:

```htvm
; This function is highly dependent on the OS and environment.
; Not available in browser JS.
if (HTVM_getLang_HTVM() = "js") {
    print("RunCMD is not available in standard JS browser environments. Skipping test.")
}
else {
    str command := ""
    ; Assuming isWindows() built-in exists and works
    bool isWin := isWindows()
    if (isWin = true) {
        command := "echo Hello from HTVM on Windows"
    }
    else {
        ; Single quotes for Unix echo
        command := "echo 'Hello from HTVM on Unix-like'"
    }
    print("Executing command: " . command)
    str output := RunCMD(command)
    print("Output from command:")
    ; Trim to remove trailing newline from echo
    print(Trim(output))
    if (isWin = true and Trim(output) = "Hello from HTVM on Windows") {
        print("RunCMD test (Windows echo) PASSED.")
    }
    else if (isWin = false and Trim(output) = "Hello from HTVM on Unix-like") {
        print("RunCMD test (Unix echo) PASSED.")
    }
    else if (command != "") {
        print("RunCMD test FAILED or OS detection mismatch. Output was: '" . Trim(output) . "'")
    }
    else {
        print("RunCMD test skipped as command was empty.")
    }
    ; Example of a command that might list files (OS-dependent)
    str listCommand := ""
    if (isWin = true) {
        listCommand := "dir /b"
    }
    else {
        listCommand := "ls -a"
    }
    print("---")
    print("Attempting to list files with: " . listCommand)
    str fileListOutput := RunCMD(listCommand)
    print("File list output (first 200 chars): " . SubStr(fileListOutput, 1, 200) . "...")
    if (StrLen(fileListOutput) > 0) {
        print("RunCMD (list files) seems to have executed and produced output.")
    }
    else {
        print("RunCMD (list files) produced no output or failed.")
    }
}
```


---
### getDataFromAPI

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| getDataFromAPI | Yes | Yes | Yes | Yes |Yes |No |Yes |Yes |Yes |Yes |Yes |No |No |No |Yes |

Asynchronously fetches data from a given `url` (string). It's typically used for making HTTP GET requests to APIs that return JSON data. The function returns the fetched data (often parsed JSON, or raw text if JSON parsing fails/is not applicable). Handles basic errors and non-OK HTTP responses.

Here is how to use it:

```htvm
; This function is asynchronous.
async func void performApiCall() {
    ; Public test API
    str apiUrl := "https://jsonplaceholder.typicode.com/todos/1"
    print("Fetching data from: " . apiUrl)
    ; In HTVM, if the function is async (like getDataFromAPI often is for JS/Python),
    ; you might need an 'await' keyword if HTVM supports it directly for this function,
    ; or handle it via callbacks/promises depending on the target language details.
    ; For this example, we'll assume direct await is possible or handled by HTVM.
    str responseData := await getDataFromAPI(apiUrl)
    if (responseData != "") {
        print("API Response Data (raw):")
        print(responseData)
    }
}
main
await performApiCall()
```


---
### input

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| input | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Prompts the user with `promptText` (string) and waits for them to enter text, then returns the entered text as a string. In graphical environments, this might open a dialog box. In console environments, it reads from standard input.

Here is how to use it:

```htvm
print("Starting input test...")
str namePrompt := "Please enter your name: "
str userName := input(namePrompt)
if (userName != "") {
    print("Hello, " . userName . "! You entered: '" . userName . "'")
    ; Simple check
    if (userName = "TestUser") {
        print("Input test with 'TestUser' PASSED.")
    }
    else {
        print("Input received. For a full test, try entering 'TestUser'.")
    }
}
else {
    print("No input received or input was empty.")
    ; Specifically empty
    if (userName = "") {
        print("Input test (empty input) PASSED observation.")
    }
    else {
        print("Input test (empty input) FAILED observation, unexpected value for empty input.")
    }
}
; ------------------------------------------------
str agePrompt := "Enter your age: "
str ageStr := input(agePrompt)
if (ageStr != "") {
    ; Assuming INT() can handle conversion
    int ageNum := INT(ageStr)
    print("You entered age: " . STR(ageNum))
    if (ageNum > 0) {
        print("Age input seems valid.")
    }
}
else {
    print("No age input received.")
}
```


---
### print

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| print | Yes | Yes | Yes | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

The `print` function is a versatile utility for outputting data to the standard console. It accepts various data types including strings, numbers (integers, floats), and booleans. When given a boolean, it will print "1" for true and "0" for false (or the language-equivalent boolean string representation). For other types, it attempts to convert them to a string representation before printing. Each call to `print` typically appends a newline character, ensuring subsequent outputs appear on a new line.

Here is how to use it:

```htvm
; Example 1: Printing a string
str message := "Hello, HTVM!"
; Should print: Hello, HTVM!
print(message)
print("--------------------")
; ----------------------------------------------------
; Example 2: Printing an integer
int count := 100
; Should print: 100
print(count)
print("--------------------")
; ----------------------------------------------------
; Example 3: Printing a float
float piApprox := 3.14159
; Should print: 3.14159
print(piApprox)
print("--------------------")
; ----------------------------------------------------
; Example 4: Printing a boolean (true)
bool isActive := true
; Should print: 1 (or true, depending on language)
print(isActive)
print("--------------------")
; ----------------------------------------------------
; Example 5: Printing a boolean (false)
bool isDone := false
; Should print: 0 (or false, depending on language)
print(isDone)
print("--------------------")
; ----------------------------------------------------
; Example 6: Printing concatenated string and number
str label := "Score: "
int score := 42
; Should print: Score: 42
print(label . STR(score))
print("--------------------")
; ----------------------------------------------------
; Test: Printing a null-like value (if HTVM has 'null' keyword and print handles it)
str nullVar := null
; Behavior for null depends on language (e.g. "null", "", error)
print(nullVar)
```


---
## Other Functions

[Go back](#built-in-functions)

1. [MakeHotKey](#makehotkey)
2. [isWindows](#iswindows)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| MakeHotKey | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| isWindows | Yes | Yes | No | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

---

### MakeHotKey

[Go back](#other-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| MakeHotKey | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

(JavaScript Only - Browser) Registers a global hotkey (keyboard shortcut). When the specified `hotkey` combination (e.g., "ctrl+s", "alt+shift+h", "f5") is pressed, the provided `callback` function is executed. The callback usually receives information about the hotkey that was pressed.

Here is how to use it:

```htvm
; Initial player position
int playerX := 10
int playerY := 10
; -------------------------------------
; Function to handle arrow key presses and move the player
func  onArrowKeyPress(key) {
    print("You pressed: " . key)
    if (key = "arrowup") {
        playerY := playerY - 5
    }
    else if (key = "arrowdown") {
        playerY := playerY + 5
    }
    else if (key = "arrowleft") {
        playerX := playerX - 5
    }
    else if (key = "arrowright") {
        playerX := playerX + 5
    }
    guiControl p"gui1" id:"player" xplayerX+"px" yplayerY+"px"
}
; -------------------------------------
; Function to reset player position to default
func  resetPos() {
    playerX := 10
    playerY := 10
    guiControl p"gui1" id:"player" xplayerX+"px" yplayerY+"px"
}
; -------------------------------------
; Button0 click action
Button0:
MsgBox, HI
subout
; -------------------------------------
; GUI setup with player button
main
gui p"gui1" x50% y50% w500 h500
gui p"gui1" id:"player" button xplayerX+"px" yplayerY+"px" w50 h50
; -------------------------------------
; Arrow key hotkeys to move player
MakeHotKey("arrowup", onArrowKeyPress)
MakeHotKey("arrowdown", onArrowKeyPress)
MakeHotKey("arrowleft", onArrowKeyPress)
MakeHotKey("arrowright", onArrowKeyPress)
; -------------------------------------
; Hotkey to reset position
MakeHotKey("Alt+R", resetPos)
```


---
### isWindows

[Go back](#other-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| isWindows | Yes | Yes | No | Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |Yes |

Checks if the current operating system is Windows. Returns `true` if the OS is identified as Windows, `false` otherwise. Not reliably available or meaningful in browser JavaScript environments (where it would typically always be false or unavailable).

Here is how to use it:

```htvm
bool runningOnWindows := isWindows()
if (runningOnWindows = true) {
    print("This script is running on a Windows system.")
}
else {
    print("This script is NOT running on a Windows system (or function not fully supported in this env).")
}
; Test: The function should return a boolean.
if (runningOnWindows = true or runningOnWindows = false) {
    print("isWindows test PASSED (returned a boolean). Current value: " . STR(runningOnWindows))
}
else {
    print("isWindows test FAILED! Did not return a boolean.")
}
```


---
## Gui Functions

[Go back](#built-in-functions)

1. [MsgBox](#msgbox)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| MsgBox | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

---

### MsgBox

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| MsgBox | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

(JavaScript Only - Browser) Displays a message box (alert/dialog) to the user.

`text`: The main message.

`title` (optional string): The title of the message box.

`value` (optional int): A number that configures icons.

Icons: +16=Error, +32=Question, +48=Warning, +64=Info.

`timeout` (optional int): Auto-closes the box after `timeout` seconds.

Here is how to use it:

```htvm
; This function is JavaScript-specific and relies on a browser environment with SweetAlert2.
async func  RunMsgBoxTests() {
    await MsgBox("This is a simple OK message.", "Test 1")
    ; 48 = Warning Icon
    await MsgBox("Proceed with caution!", "Test 3: Warning Icon", 48)
    ; Timeout 2s
    await MsgBox("This will auto-close in 2 seconds.", "Test 5: Timeout", 0, 2)
    print("MsgBox tests complete. Check browser for dialogs.")
}
main
if (HTVM_getLang_HTVM() = "js") {
    print("MsgBox tests will attempt to show dialogs if in a browser.")
    await RunMsgBoxTests()
}
else {
    print("MsgBox is only for JavaScript browser environments. Skipping test.")
}
```


---
## Backend Functions

[Go back](#built-in-functions)

1. [callBackend](#callbackend)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| callBackend | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

---

### callBackend

[Go back](#backend-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| callBackend | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

(JavaScript Only) Asynchronously sends a request to a backend `endpoint` (string, e.g., "/api/data").

`textData` (string): The data to send in the request body (plain text).

`method` (optional string, default "POST"): The HTTP method (e.g., "GET", "POST", "PUT").

Returns a Promise that resolves with the plain text response from the backend. Used for frontend-backend communication.

Here is how to use it:

```htvm
; This function is JavaScript-specific for frontend-backend communication.
; It requires a running backend server that responds to the specified endpoints.
; -----------------------
; --- OSP Struct for state (Recommended) ---
struct InputState {
    prop str currentText := ""
}
; --- Callbacks ---
; -----------------------
; Default for edit
Edit0:
; No 'global' needed for JS target
InputState.currentText := A_Value
subout
; -----------------------
; Callback for first button
ButtonHello:
str respHello := await callBackend("/hello", InputState.currentText)
; Use SPACE separation for guicontrol
guicontrol id:"responseText" value:respHello
subout
; -----------------------
; Callback for second button
ButtonProcess:
str respProcess := await callBackend("/processData", InputState.currentText)
; Use SPACE separation for guicontrol
guicontrol id:"responseText" value:respProcess
subout
; -----------------------
; --- GUI Setup ---
main
; Prepare string vars only where needed, hardcode simple ones
str placeholderText := "Enter data..."
str btn1Text := "Call Hello"
str btn2Text := "Call Process"
str initialResponse := "Response..."
str editId := "inputEdit"
str helloBtnId := "helloBtn"
str processBtnId := "processBtn"
str responseTextId := "responseText"
str whiteColor := "white"
; Use SPACE separation for GUI options
; Uses Edit0
gui edit id:editId x10 y10 w200 h30 placeholder:placeholderText
gui button id:helloBtnId x10 y50 w95 h30 value:btn1Text callback:ButtonHello
gui button id:processBtnId x115 y50 w95 h30 value:btn2Text callback:ButtonProcess
gui text id:responseTextId x10 y90 w200 h30 value:initialResponse color:whiteColor
```


---
