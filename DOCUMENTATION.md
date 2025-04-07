# HTVM Documentation


1. [Introduction](#introduction-to-htvm)  
Understand why HTVM is the future of programming.

2. [OSP (Objectively Simplified Programming) Paradigm](#osp-objectively-simplified-programming-paradigm)  
Learn about the new paradigm that replaces traditional object-oriented programming.

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

9. [If, Else, Else If](#if-else-else-if)  
Learn how to control the flow of your program with conditional statements.

10. [Comments](#comments)  
Add clarity to your code by using comments to document and explain your code.

11. [Error Handling](#error-handling)  
Understand how to manage errors and handle exceptions in HTVM to make your programs more robust.

12. [Operators](#operators)  
Explore the logical and mathematical operators available in HTVM for performing calculations and comparisons.

13. [Assignment Operators](#assignment-operators)  
Learn how to use assignment operators for storing values and manipulating them in your code.

14. [Include](#include)  
Discover how to include external files and resources in your HTVM project for enhanced functionality.

15. [Extra Stuff](#extra-stuff)  
Explore additional unique features and utilities HTVM offers for greater flexibility and ease of use.

16. [Commands](#commands)  
Commands in HTVM are a simplified way to perform actions, similar to functions, but with a more compact, direct, and concise syntax for better efficiency.

17. [Built-in Functions](#built-in-functions)  
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
This isn’t just some hobby project. **HTVM Version 2 took over three months just for the parser.** And that was with prior experience from HTVM Version 1 and all the work put into previous languages like HT++, HTH, and HTpy. Every single language had to be carefully mapped out—loops, if-statements, try/catch blocks, functions, variables, types—**every detail had to be considered, tested, and tweaked.**  

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

## OSP (Objectively Simplified Programming) Paradigm  

[Go back](#htvm-documentation) 

OSP (Objectively Simplified Programming) is a paradigm designed to replace OOP since OOP was a mistake. To learn OSP you need to first forget everything about OOP. Forget about concepts like inheritance, polymorphism, encapsulation, private/public keywords and instances.

OSP eliminates the complexities of object-oriented programming.  

Here’s how OSP works:  
- **Hierarchies**:  
  - **Alliance**: The top-level structure, defined using the `alliance` keyword. 
  - **Crew**: Sub-levels within an alliance, defined using the `crew` keyword.  
  - **Method**: Functions defined within alliances or crews using the `method` keyword.  
  - **Object**: Objects are defined using the `def obj` keyword.  

- **Properties**:  
  - Defined within objects using the `porp` keyword.  


### **The `this` Keyword**:

- **Definition**:  
  The `this` keyword is a reference to the current object that invoked a method. In OSP, `this` is **explicitly required to refer to objects**, and **you must always specify the full path** of objects and their properties when using it. Additionally, `this` is **only valid within methods**, as it represents the object calling that specific method.

---

### **Key Rules**:
1. **Full Path Requirement**:  
   - In OSP, **you must always specify the full path** of objects and properties when using `this`.  
   - For example:  
     - **Correct**: `Movable.Vehicles.Car.fuel`  
     - **Incorrect**: `fuel`

2. **Only Inside Methods**:  
   - The `this` keyword can **only** be used inside a method. It refers to the object that invoked the method and provides context for operations on that object.  
   - Using `this` outside of a method will result in an error, as there is no calling object to reference.

---

### **Explanation Using the Example**:
```htvm
crew someCrew {
    method void move(this) {
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

```
- The `this` keyword in this method represents the specific object calling `move()`.  
  For instance:
  - If `this == "Movable.Vehicles.Car"`, the method knows the caller is the **Car object**, and it manipulates `Movable.Vehicles.Car` properties.
  - Similarly, if `this == "Movable.Vehicles.Bike"`, the method operates on the **Bike object**.

- If you try to use `this` **outside of any method**, it won’t work because `this` has no object context to refer to.  
For example:
``` htvm
def obj Car {
    prop int fuel := 100
    ; This will cause an error!
    print(this)
}

```

---

### **Why This Restriction Exists**:
1. **Object Context**:  
   - The `this` keyword needs a calling object to provide context. Without a method invocation, there’s no object to reference.

2. **Scope Control**:  
   - Limiting `this` to methods ensures clear and explicit usage, making code easier to understand and debug.

3. **Example: Calling a Method with an Object**:  
   - To use the `this` keyword, you must **pass the object name as a string**  when invoking the method:  
   ```htvm
   allianceName.crewName.move("allianceName.crewName.objName")
   ```
   - Here:
     - `allianceName` is the main alliance.
     - `crewName` is the crew containing the method `move`.
     - `objName` is the specific object being passed to the method. This allows `this` to refer to `objName` inside the method.

  ### Note: You can't define a method without a **crew**, **alliance**, or both. You need at least one.

---

## **You Don’t Need an Alliance or Crew to Define Objects**
- In OSP, you can define objects (`def obj`) directly without placing them inside an **alliance** or a **crew**.  
- This makes it flexible to create standalone objects when you don’t need a larger structure.  

### **Example: Standalone Object Definition**
```htvm
def obj Standalone {
    prop int value := 10
    prop str name := "Independent"
}

```

to access later just use:

```htvm
Standalone.value
Standalone.name
```

---

### **Methods in Alliances**
- Methods can also be defined directly in an **alliance**, without being part of a **crew** and the opposite is well.

### **Example: Method in an Alliance**
```htvm
alliance ExampleAlliance {
    method void greet(this) {
        print("Hello from ExampleAlliance!")
    }
}

```

to call greet just do:

```htvm
ExampleAlliance.greet()

```

## Global Accessibility:  
  - There are no scopes in OSP. As long as a variable or structure is defined above, it is accessible below. Everything is global, and the full path must always be used.  

## Arrays:  
  - When using arrays you can just define them as normal:

```htvm
def obj name {
    prop arr str prop1
    prop arr str prop2
    prop arr str prop3
    prop arr str prop4
}

```

### **Summary**:
- **Full Paths Always**: Explicit references, such as `Movable.Vehicles.Car.fuel`, are mandatory in OSP. Always use the full path to reference objects. This avoids ambiguity and ensures that each object is uniquely identified within the code.
- **Only Inside Methods**: The `this` keyword can only be used inside a method to refer to the calling object. It is not valid outside of a method because it requires the context of the method invocation to work correctly.
- **Promotes Clarity**: These rules ensure consistency, clarity, and unambiguous functionality in OSP. By restricting the use of `this` to methods and requiring full paths, the code remains explicit and easier to follow.
- **Helps with Debugging**: Since `this` is only valid inside methods, errors related to improper use are easier to detect. Using full paths also helps pinpoint issues more precisely by avoiding confusion with similarly named objects.
- **Encourages Best Practices**: These guidelines encourage a more structured and organized approach to coding in OSP, fostering a clearer and more maintainable codebase in larger projects.

---

## Note:

### Never use underscores when naming things in OSP. Otherwise, you can use them, but be cautious because underscores can be unstable.


#### Example of OSP

```htvm
alliance Movable {
    crew Vehicles {
        def obj Car {
            prop int door := 4
            prop int fuel := 100
            prop bool hasFUEL := true
        }
        def obj Bike {
            prop bool hasGears := true
            prop int energy := 100
            prop bool hasENERGY := true
        }
        method void move(this) {
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
        def obj GeneralSettings {
            prop str difficulty := "normal"
            prop int volume := 50
            prop str resolution := "1920x1080"
        }
        def obj AudioSettings {
            prop int masterVolume := 70
            prop int musicVolume := 50
            prop int sfxVolume := 40
        }
        def obj DisplaySettings {
            prop bool fullscreen := true
            prop str aspectRatio := "16:9"
        }
    }
    crew actions {
        ; General Settings Methods
        method void resetGeneralSettings(this) {
            Movable.settings.GeneralSettings.difficulty := STR("normal")
            Movable.settings.GeneralSettings.volume := 50
            Movable.settings.GeneralSettings.resolution := STR("1920x1080")
            print("General settings reset to default.")
        }
        method void printGeneralSettings(this) {
            print("General Settings:")
            print("Difficulty: " . Movable.settings.GeneralSettings.difficulty)
            print("Volume: " . STR(Movable.settings.GeneralSettings.volume))
            print("Resolution: " . Movable.settings.GeneralSettings.resolution)
        }
        ; Audio Settings Methods
        method void resetAudioSettings(this) {
            Movable.settings.AudioSettings.masterVolume := 70
            Movable.settings.AudioSettings.musicVolume := 50
            Movable.settings.AudioSettings.sfxVolume := 40
            print("Audio settings reset to default.")
        }
        method void printAudioSettings(this) {
            print("Audio Settings:")
            print("Master Volume: " . STR(Movable.settings.AudioSettings.masterVolume))
            print("Music Volume: " . STR(Movable.settings.AudioSettings.musicVolume))
            print("SFX Volume: " . STR(Movable.settings.AudioSettings.sfxVolume))
        }
        ; Display Settings Methods
        method void resetDisplaySettings(this) {
            Movable.settings.DisplaySettings.fullscreen := true
            Movable.settings.DisplaySettings.aspectRatio := STR("16:9")
            print("Display settings reset to default.")
        }
        method void printDisplaySettings(this) {
            print("Display Settings:")
            print("Fullscreen: " . STR(Movable.settings.DisplaySettings.fullscreen))
            print("Aspect Ratio: " . Movable.settings.DisplaySettings.aspectRatio)
        }
    }
    crew array {
        def obj name {
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

**OSP** simplifies programming while ensuring compatibility with all languages.

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
HTVM introduces a unique and flexible function call syntax that allows developers to call functions in multiple ways while maintaining simplicity and readability. This enhancement does not change the fundamental nature of functions in HTVM—they remain regular functions rather than methods. However, HTVM allows them to be called using dot notation for convenience.

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
  HTVM automatically converts these function calls into standard function calls durring conversion. This ensures that the underlying implementation remains consistent while providing developers with flexibility in how they write their code.

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

#### **Conclusion**  
This feature enhances HTVM's usability by providing developers with multiple ways to call functions. While functions remain standard, the optional dot notation and omission of parentheses make coding more intuitive and efficient.

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
- In **statically typed languages** (e.g., C++, Java), HTVM will convert it into a `std::vector<std::string>` / `string[]`.

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

---







### Loops

[Go back](#htvm-documentation)

Master the looping structures available in HTVM, such as the standard loop and infinite loops.

Example:
```htvm
Loop, 5 {
    print(A_Index)
}
```

---



### If, Else, Else If

[Go back](#htvm-documentation)

Learn how to control the flow of your program with conditional statements like **if**, **else**, and **else if**. These structures allow you to handle decisions and branching logic in your code effectively.

---



### Comments

[Go back](#htvm-documentation)

Add clarity to your code by using comments to document and explain your code. Comments are crucial for maintaining readability and ensuring that others can understand your thought process.

---



### Error Handling

[Go back](#htvm-documentation)

Understand how to manage errors and handle exceptions in HTVM to make your programs more robust. HTVM provides simple ways to catch and handle errors, helping you write more stable and reliable code.

---



### Operators

[Go back](#htvm-documentation)

Explore the logical and mathematical operators available in HTVM for performing calculations and comparisons. HTVM supports a wide range of operators to enable complex operations in your programs.

---



### Assignment Operators

[Go back](#htvm-documentation)

Learn how to use assignment operators for storing values and manipulating them in your code. Assignment operators in HTVM simplify the process of assigning and updating values in variables.

---



### Include

[Go back](#htvm-documentation)

Discover how to include external files and resources in your HTVM project for enhanced functionality. The **include** feature in HTVM allows you to integrate additional code or libraries into your project seamlessly.

---



### Extra Stuff

[Go back](#htvm-documentation)

Explore additional unique features and utilities HTVM offers for greater flexibility and ease of use. These features help make programming in HTVM even more powerful and efficient.

---



### Commands

[Go back](#htvm-documentation)

Commands in HTVM are a simplified way to perform actions, similar to functions, but with a more compact, direct, and concise syntax for better efficiency. Commands help streamline your code and reduce unnecessary complexity.

---


## Built-in Functions  

[Go back](#htvm-documentation) 

HTVM includes a variety of built-in functions organized into categories for convenience.

1. [Math Functions](#math-functions)
2. [String Functions](#string-functions)
3. [System Functions](#system-functions)
4. [File Functions](#file-functions)
5. [Io Functions](#io-functions)
6. [Gui Functions](#gui-functions)
7. [Other Functions](#other-functions)
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
| ACos | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| ASin | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| ATan | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Abs | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Ceil | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Cos | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Exp | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Floor | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Ln | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Log | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Mod | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Random | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Round | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Sin | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Sqrt | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Tan | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

---

### ACos

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ACos | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### ASin

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ASin | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### ATan

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ATan | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Abs

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Abs | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Ceil

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Ceil | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Cos

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Cos | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Exp

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Exp | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Floor

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Floor | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Ln

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Ln | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Log

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Log | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Mod

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Mod | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Random

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Random | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Round

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Round | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Sin

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Sin | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Sqrt

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Sqrt | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Tan

[Go back](#math-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Tan | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


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
| Asc | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Chr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| FLOAT | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| INT | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| InStr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| RegExMatch | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| RegExReplace | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| STR | Yes | Yes | Yes | Yes |Yes |Yes |Yes |No |No |Yes |Yes |Yes |Yes |Yes |Yes |
| Sort | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StrLen | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StrLower | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StrReplace | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StrSplit | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StrTitleCase | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StringTrimLeft | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| StringTrimRight | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| SubStr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Trim | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| countChars | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| getUrlParams | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| sortArr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| sortArrByLenOnly | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

---

### Asc

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Asc | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Chr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Chr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### FLOAT

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FLOAT | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### INT

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| INT | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### InStr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| InStr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### RegExMatch

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| RegExMatch | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### RegExReplace

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| RegExReplace | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### STR

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| STR | Yes | Yes | Yes | Yes |Yes |Yes |Yes |No |No |Yes |Yes |Yes |Yes |Yes |Yes |


---

### Sort

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Sort | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StrLen

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrLen | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StrLower

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrLower | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StrReplace

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrReplace | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StrSplit

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrSplit | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StrTitleCase

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StrTitleCase | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StringTrimLeft

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StringTrimLeft | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### StringTrimRight

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| StringTrimRight | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### SubStr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| SubStr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Trim

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Trim | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### countChars

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| countChars | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### getUrlParams

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| getUrlParams | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### sortArr

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| sortArr | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### sortArrByLenOnly

[Go back](#string-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| sortArrByLenOnly | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


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
| BuildInVars | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| ExitApp | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| HTVM_getLang_HTVM | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Sleep | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

---

### BuildInVars

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| BuildInVars | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### ExitApp

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| ExitApp | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### HTVM_getLang_HTVM

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| HTVM_getLang_HTVM | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Sleep

[Go back](#system-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Sleep | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


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


---

### FileAppendJs

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileAppendJs | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### FileCreateDir

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileCreateDir | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### FileDelete

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileDelete | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### FileExist

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileExist | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### FileRead

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileRead | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### FileRemoveDir

[Go back](#file-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| FileRemoveDir | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


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
| getDataFromAPI | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| input | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| print | Yes | Yes | Yes | Yes |Yes |Yes |Yes |No |No |Yes |Yes |Yes |Yes |Yes |Yes |

---

### GetParams

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| GetParams | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### RunCMD

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| RunCMD | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### getDataFromAPI

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| getDataFromAPI | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### input

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| input | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### print

[Go back](#io-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| print | Yes | Yes | Yes | Yes |Yes |Yes |Yes |No |No |Yes |Yes |Yes |Yes |Yes |Yes |


---

## Gui Functions

[Go back](#built-in-functions)

1. [GuiControl](#guicontrol)
2. [Gui_Button](#gui_button)
3. [Gui_CheckBox](#gui_checkbox)
4. [Gui_Color](#gui_color)
5. [Gui_DropDownList](#gui_dropdownlist)
6. [Gui_Edit](#gui_edit)
7. [Gui_Font](#gui_font)
8. [Gui_Font_Id](#gui_font_id)
9. [Gui_Hide](#gui_hide)
10. [Gui_Image](#gui_image)
11. [Gui_Move](#gui_move)
12. [Gui_Show](#gui_show)
13. [Gui_Size](#gui_size)
14. [Gui_Size_Id](#gui_size_id)
15. [Gui_Text](#gui_text)
16. [Gui_Toggle](#gui_toggle)
17. [Gui_Update](#gui_update)
18. [MsgBox](#msgbox)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| GuiControl | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Button | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_CheckBox | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Color | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_DropDownList | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Edit | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Font | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Font_Id | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Hide | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Image | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Move | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Show | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Size | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Size_Id | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Text | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Toggle | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| Gui_Update | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| MsgBox | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |

---

### GuiControl

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| GuiControl | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Button

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Button | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_CheckBox

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_CheckBox | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Color

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Color | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_DropDownList

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_DropDownList | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Edit

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Edit | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Font

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Font | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Font_Id

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Font_Id | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Hide

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Hide | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Image

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Image | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Move

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Move | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Show

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Show | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Size

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Size | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Size_Id

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Size_Id | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Text

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Text | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Toggle

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Toggle | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### Gui_Update

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| Gui_Update | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### MsgBox

[Go back](#gui-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| MsgBox | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

## Other Functions

[Go back](#built-in-functions)

1. [HTVM_v2_HTVM](#htvm_v2_htvm)
2. [MakeHotKey](#makehotkey)
3. [isWindows](#iswindows)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| HTVM_v2_HTVM | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| MakeHotKey | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| isWindows | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

---

### HTVM_v2_HTVM

[Go back](#other-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| HTVM_v2_HTVM | Yes | Yes | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### MakeHotKey

[Go back](#other-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| MakeHotKey | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### isWindows

[Go back](#other-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| isWindows | Yes | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

## Backend Functions

[Go back](#built-in-functions)

1. [addEndpoint](#addendpoint)
2. [createBackendInit](#createbackendinit)
3. [getDataFromEndpoint](#getdatafromendpoint)
4. [startServer](#startserver)

---

**HTVM built-in functions are designed to work mostly across C++, Python, JavaScript, Go, Lua, C#, Java, Kotlin, Ruby, Nim, AutoHotKey, Swift, Dart, TypeScript and Groovy with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++ and others and many other combinations, while others are available in all or some languages.**

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| addEndpoint | No | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| createBackendInit | No | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |
| getDataFromEndpoint | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |
| startServer | No | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |

---

### addEndpoint

[Go back](#backend-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| addEndpoint | No | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### createBackendInit

[Go back](#backend-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| createBackendInit | No | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

### getDataFromEndpoint

[Go back](#backend-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| getDataFromEndpoint | No | No | Yes | No |No |No |No |No |No |No |No |No |No |No |No |


---

### startServer

[Go back](#backend-functions)

**HTVM build-in functions availability.**

| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |
|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|
| startServer | No | Yes | No | No |No |No |No |No |No |No |No |No |No |No |No |


---

